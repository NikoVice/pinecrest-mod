/*
    Author: Vip_Uzer | vk.com/vip_uzer
    21.11.2022
*/

stock VK_ShowMainPanel(playerid)
{
    if(!IsVKConfirmed(playerid))
        return SendError(playerid, "У Вас не подтверждена защита ВКонтакте.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "{00FF7F}» {ffffff}Тип: {0099CC}%s\n{00FF7F}» {ffffff}Сменить тип защиты\n{ff0000}» {ffffff}Отключить привязку", p_info[playerid][vk_auth] == 0 ? "Запрашивать всегда" : "Запрашивать при смене IP адреса");
    ShowPlayerDialog(playerid, D_VK_MAIN_PANEL, DIALOG_STYLE_LIST, ""I"Защита ВКонтакте", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

stock VK_ShowDialogAuth(playerid)
{
    new iVKCode = random(8999)+1000;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `vk_code` = %d, `vk_session` = 8 WHERE `id` = %d", iVKCode, p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "VK_SendRequestCallback", "ddd", playerid, iVKCode, 1);

    ShowPlayerDialog(playerid, D_VK_AUTH_WINDOW, DIALOG_STYLE_MSGBOX, ""I"Защита ВКонтакте", !"{0099CC}VK Security{ffffff} – система которая направлена на обеспечение безопасности Вашего аккаунта.\n\nПодтвердите вход нажав соответствующую кнопку в диалоге с группой.\nДалее нажмите на кнопку 'Далее'", !"Далее", "");
    return 1;
}

forward VK_SendRequestCallback(playerid, iVKCode, iVKType);
public  VK_SendRequestCallback(playerid, iVKCode, iVKType)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "uid=%d&name=%s&s=%d&vk=%d&t=%d&c=%d",
        p_info[playerid][ID], get_name(playerid), SRV_ID, p_info[playerid][vk_userid], iVKType, iVKCode);

    STRING_MIN[0] = EOS;
    f(STRING_MIN, "%s/bot/vk/send_mod.php", ServerInfo[SecurityBotURL]);
    HTTP(playerid, HTTP_POST, STRING_MIN, STRING_GLOBAL, "VK_SendRequests");
    return 1;
}

forward VK_SendRequests(index, response_code, data[]);
public VK_SendRequests(index, response_code, data[])
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
                    if(ServerInfo[TGSecurity] && IsTGConfirmed(index) && (!p_info[index][tg_auth] || (p_info[index][tg_auth] && !strequals(p_temp[index][session_IP], p_info[index][lastIP]))))
                        return TG_ShowDialogAuth(index);
                    SendInfo(index, "Авторизация произошла автоматически.");
                    LoadPlayerAccount(index);
                }
                else
                {
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL,sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `vk_code` = 0, `vk_session` = 0 WHERE `id` = %d", p_info[index][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);
                    ShowPlayerDialog(index, -1, 0, " ", " ", " ", " " ) ; // hide all dialogs
                }
                if(ServerInfo[VKSecurity])
                {
                    ServerInfo[VKSecurity] = 0;
                    MysqlUpdateOtherInt("VKSecurity", ServerInfo[VKSecurity]);

                    HTTP(-1, HTTP_POST, "dimkov.online/vk/send.php", "t=2",""); // Оповещаем через бота что ВК умер.
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

forward VK_SessionCallback(playerid, type_session);
public VK_SessionCallback(playerid, type_session)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Не известная ошибка. Код 221-1122.");

    new vk_session;
    cache_get_value_name_int(0, "vk_session", vk_session);

    if(type_session == 1)
    {
        if(!(1 <= vk_session <= 2)) return ShowPlayerDialog(playerid, D_VK_AUTH_WINDOW, DIALOG_STYLE_MSGBOX, ""I"Защита ВКонтакте", !"{0099CC}VK Security{ffffff} – система которая направлена на обеспечение безопасности Вашего аккаунта.\n\nПодтвердите вход нажав соответствующую кнопку в диалоге с группой.\nДалее нажмите на кнопку 'Далее'", !"Далее", "");
        else
        {
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `vk_session` = 0 WHERE `id` = %d", p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            if(vk_session == 1)
            {
                if(ServerInfo[TGSecurity] && IsTGConfirmed(playerid) && (!p_info[playerid][tg_auth] || (p_info[playerid][tg_auth] && !strequals(p_temp[playerid][session_IP], p_info[playerid][lastIP]))))
                    return TG_ShowDialogAuth(playerid);
                LoadPlayerAccount(playerid);
            }
            else
            {
                SendError(playerid, "Вход был заблокирован владельцем аккаунта, сессия сброшена.");
                Kick(playerid);
            }
        }
    }
    if(type_session == 3)
    {
        if(!(5 <= vk_session <= 6)) return VK_ShowDialogDecline(playerid);
        else
        {
            if(vk_session == 5)
            {
                p_info[playerid][vk_userid] =
                p_info[playerid][vk_auth] =
                p_info[playerid][vk_confirmed] = 0;

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `vk_userid` = 0, `vk_auth` = 0,  `vk_confirmed` = 0, `vk_code` = 0, `vk_session` = 0 WHERE `id` = %d", p_info[playerid][ID]);
                mysql_tquery(con_bd, STRING_GLOBAL);
                SendAccess(playerid, "Вы успешно отвязали аккаунт ВКонтакте.");
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `vk_session` = 0 WHERE `id` = %d", p_info[playerid][ID]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
        }
    }
    return 1;
}

forward VK_Confirmed_Callback(playerid, confirm_code);
public VK_Confirmed_Callback(playerid, confirm_code)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Не известная ошибка. Код 121-1122.");

    new iVKCode, iUserID;
    cache_get_value_name_int(0, "vk_code", iVKCode);
    if(iVKCode != confirm_code) return VK_ShowDialogLink(playerid);

    cache_get_value_name_int(0, "vk_userid", iUserID);

    p_info[playerid][vk_userid] = iUserID;
    p_info[playerid][vk_auth] = 0;
    p_info[playerid][vk_confirmed] = 1;

    SendAccess(playerid, "Вы успешно привязали аккаунт ВКонтакте.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL,sizeof(STRING_GLOBAL),"UPDATE `accounts` SET `vk_confirmed` = 1, `vk_session` = 1, `vk_auth` = 0 WHERE `id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

VK_ShowDialogLink(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL,sizeof(STRING_GLOBAL), "{ffffff}Чтобы привязать Ваш профиль ВКонтакте к игровому аккаунту:\n\n\
        {00FF7F}+ {ffffff}Введите {ffcc00}/start %s{ffffff}\n\
        в личные сообщения с нашей официальной группой (%s), и следуйте инструкциям.\n\
        {ff0000}[!] {ffffff}Вводить свои данные следует именно в личные сообщения с сообществом\n\n\
        После всех выполненных действий в ВК, вы получите код который необходимо ввести ниже:", get_name(playerid), VK_URL);
    ShowPlayerDialog(playerid, D_VK_CONFIRMATION_LINK, DIALOG_STYLE_INPUT, ""I"Защита ВКонтакте", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

VK_ShowDialogDecline(playerid)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "{ffffff}Чтобы отвязать Ваш профиль ВКонтакте:\n\n\
        {00FF7F}– {ffffff}Нажмите 'подтвердить'{ffffff}\n\
        в личные сообщения с нашей официальной группой, а после процедуры нужно нажать \"Далее\"\n\n\
        {ff0000}[!] {ffffff}Вводить свои данные следует именно в личные сообщения с сообществом");

    ShowPlayerDialog(playerid, D_VK_CONFIRMATION_DECLINE, DIALOG_STYLE_MSGBOX, ""I"Защита ВКонтакте", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

IsVKConfirmed(playerid)
{
    if(p_info[playerid][vk_userid] && p_info[playerid][vk_confirmed] == 1) return 1;
    return 0;
}
