/*
    Author: Vip_Uzer | t.me/vip_uzer
    04.01.2023
*/

stock TG_ShowMainPanel(playerid)
{
    if(!IsTGConfirmed(playerid))
        return SendError(playerid, "У Вас не подтверждена защита Telegram.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "{00FF7F}» {ffffff}Тип: {0099CC}%s\n{00FF7F}» {ffffff}Сменить тип защиты\n{ff0000}» {ffffff}Отключить привязку", p_info[playerid][tg_auth] == 0 ? "Запрашивать всегда" : "Запрашивать при смене IP адреса");
    ShowPlayerDialog(playerid, D_TG_MAIN_PANEL, DIALOG_STYLE_LIST, ""I"Защита Telegram", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

stock TG_ShowDialogAuth(playerid)
{
    new iTGCode = random(8999)+1000;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tg_code` = %d, `tg_session` = 8 WHERE `id` = %d", iTGCode, p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "TG_SendRequestCallback", "ddd", playerid, iTGCode, 1);

    ShowPlayerDialog(playerid, D_TG_AUTH_WINDOW, DIALOG_STYLE_MSGBOX, ""I"Защита Telegram", !"{0099CC}TG Security{ffffff} – система которая направлена на обеспечение безопасности Вашего аккаунта.\n\nПодтвердите вход нажав соответствующую кнопку в диалоге с группой.\nДалее нажмите на кнопку 'Далее'", !"Далее", "");
    return 1;
}

forward TG_SendRequestCallback(playerid, iTGCode, iTGType);
public  TG_SendRequestCallback(playerid, iTGCode, iTGType)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "uid=%d&name=%s&s=%d&tg=%d&t=%d&c=%d",
        p_info[playerid][ID], get_name(playerid), SRV_ID, p_info[playerid][tg_userid], iTGType, iTGCode);

    STRING_MIN[0] = EOS;
    f(STRING_MIN, "%s/bot/tg/send_mod.php", ServerInfo[SecurityBotURL]);
    HTTP(playerid, HTTP_POST, STRING_MIN, STRING_GLOBAL, "TG_SendRequests");
    return 1;
}

forward TG_SendRequests(index, response_code, data[]);
public TG_SendRequests(index, response_code, data[])
{
    if(!(200 <= response_code <= 299))
    {
        if(!strequals(data, "ok"))
        {
            printf("HTTP_ERROR: %s", data);
            if(strequals(data, "error_send_post") || // - ошибка отправки с мода значений с параметров POST
                strequals(data, "error_mysql_bot")) // - ошибка соедиенения сайта с базой мода
            {
                SendError(index, "Связь с промежуточным сервером прервана или недоступна. Сообщите администрации!");
                if(!p_info[index][loggedIn])
                {
                    SendInfo(index, "Авторизация произошла автоматически.");
                    LoadPlayerAccount(index);
                }
                else
                {
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL,sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tg_code` = 0, `tg_session` = 0 WHERE `id` = %d", p_info[index][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);
                    ShowPlayerDialog(index, -1, 0, " ", " ", " ", " " ) ; // hide all dialogs
                }
                if(ServerInfo[TGSecurity])
                {
                    ServerInfo[TGSecurity] = 0;
                    MysqlUpdateOtherInt("TGSecurity", ServerInfo[TGSecurity]);

                    HTTP(-1, HTTP_POST, "dimkov.online/tg/send.php", "t=2",""); // Оповещаем через бота что Telegram умер.
                }
            }
            if(strequals(data, "error_send_deny")) // ошибка когда пользователь запретил отправку сообщений от сообщества
            {
                SendError(index, "Вы запретили сообществу отправлять Вам сообщения.");
                SendInfo(index, "Разрешите сообщения что бы можно было продолжить.");
            }
        }
    }
    return 1;
}

forward TG_SessionCallback(playerid, type_session);
public TG_SessionCallback(playerid, type_session)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Не известная ошибка. Код 221-1122.");

    new tg_session;
    cache_get_value_name_int(0, "tg_session", tg_session);

    if(type_session == 1)
    {
        if(!(1 <= tg_session <= 2)) return ShowPlayerDialog(playerid, D_TG_AUTH_WINDOW, DIALOG_STYLE_MSGBOX, ""I"Защита Telegram", !"{0099CC}Telegram Security{ffffff} – система которая направлена на обеспечение безопасности Вашего аккаунта.\n\nПодтвердите вход нажав соответствующую кнопку в диалоге с группой.\nДалее нажмите на кнопку 'Далее'", !"Далее", "");
        else
        {
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tg_session` = 0, WHERE `id` = %d", p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            if(tg_session == 1) LoadPlayerAccount(playerid);
            else
            {
                SendError(playerid, "Вход был заблокирован владельцем аккаунта, сессия сброшена.");
                Kick(playerid);
            }
        }
    }
    if(type_session == 3)
    {
        if(!(5 <= tg_session <= 6)) return TG_ShowDialogDecline(playerid);
        else
        {
            if(tg_session == 5)
            {
                p_info[playerid][tg_userid] =
                p_info[playerid][tg_auth] =
                p_info[playerid][tg_confirmed] = 0;

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tg_userid` = 0, `tg_auth` = 0,  `tg_confirmed` = 0, `tg_code` = 0, `tg_session` = 0 WHERE `id` = %d", p_info[playerid][ID]);
                mysql_tquery(con_bd, STRING_GLOBAL);
                SendAccess(playerid, "Вы успешно отвязали аккаунт Telegram.");
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tg_session` = 0, WHERE `id` = %d", p_info[playerid][ID]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
        }
    }
    return 1;
}

forward TG_Confirmed_Callback(playerid, confirm_code);
public TG_Confirmed_Callback(playerid, confirm_code)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Не известная ошибка. Код 121-1122.");

    new iTGCode, iUserID;
    cache_get_value_name_int(0, "tg_code", iTGCode);
    if(iTGCode != confirm_code) return TG_ShowDialogLink(playerid);

    cache_get_value_name_int(0, "tg_userid", iUserID);

    p_info[playerid][tg_userid] = iUserID;
    p_info[playerid][tg_auth] = 0;
    p_info[playerid][tg_confirmed] = 1;

    SendAccess(playerid, "Вы успешно привязали аккаунт Telegram.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL,sizeof(STRING_GLOBAL),"UPDATE `accounts` SET `tg_confirmed` = 1, `tg_session` = 1, `tg_auth` = 0 WHERE `id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

TG_ShowDialogLink(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "{ffffff}Чтобы привязать Ваш профиль Telegram к игровому аккаунту:\n\n\
        {00FF7F}+ {ffffff}Введите {ffcc00}/start %s{ffffff}\n\
        в личные сообщения с нашей официальной группой (%s), и следуйте инструкциям.\n\
        {ff0000}[!] {ffffff}Вводить свои данные следует именно в личные сообщения с сообществом\n\n\
        После всех выполненных действий в ВК, вы получите код который необходимо ввести ниже:", get_name(playerid), TG_URL);
    ShowPlayerDialog(playerid, D_TG_CONFIRMATION_LINK, DIALOG_STYLE_INPUT, ""I"Защита Telegram", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

TG_ShowDialogDecline(playerid)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "{ffffff}Чтобы отвязать Ваш профиль Telegram:\n\n\
        {00FF7F}– {ffffff}Нажмите 'подтвердить'{ffffff}\n\
        в личные сообщения с нашей официальной группой, а после процедуры нужно нажать \"Далее\"\n\n\
        {ff0000}[!] {ffffff}Вводить свои данные следует именно в личные сообщения с сообществом");

    ShowPlayerDialog(playerid, D_TG_CONFIRMATION_DECLINE, DIALOG_STYLE_MSGBOX, ""I"Защита Telegram", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

IsTGConfirmed(playerid)
{
    if(p_info[playerid][tg_userid] && p_info[playerid][tg_confirmed] == 1) return 1;
    return 0;
}
