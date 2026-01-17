CMD:settings(playerid, params[])
{
    ShowPlayerSettings(playerid);
    return 1;
}

ShowPlayerSettings(playerid)
{
    ShowPlayerDialog(playerid, D_PLAYER_SETTINGS, DIALOG_STYLE_TABLIST, ""I"Настройки",
        ""I"[1]"W" Настройки аккаунта\n\
        "I"[2]"W" Настройки персонажа\n\
        "I"[3]"W" Настройки отображения и графики\n\
        "I"[4]"W" Настройки клиента\n\
        "I"[5]"W" Настройки чата", "Далее", "Отмена");
    return 1;
}

ShowPlayerSettingsHud(playerid)
{
    new status_hud[][] = {"{"#cLIGHTRED"}Выключено", "{"#cGREEN"}Включено"};
    STRING_GLOBAL = ""W"[#] Название\t"W"Статус\n";
    f(STRING_GLOBAL,
        "%s"I"[1] "W"Отображение чата\t%s\n\
        "I"[2] "W"Отображение карты\t%s\n\
        "I"[3] "W"Отображение никнеймов\t%s\n\
        "I"[4] "W"Отображение кнопок\t%s\n\
        "I"[5] "W"Отображение фиста/денег\t%s\n\
        "I"[6] "W"Отображение 3D текстов\t%s\n\
        "I"[7] "W"Все элементы\t{"#cLIGHTRED"}Выключить\n\
        "I"[8] "W"Все элементы\t{"#cGREEN"}Включить\n\
        "I"[9] "W"Затухание чата\t%s\n", STRING_GLOBAL,
        status_hud[p_info[playerid][p_settings][ELEMENT_CHAT]],
        status_hud[p_info[playerid][p_settings][ELEMENT_MAP]],
        status_hud[p_info[playerid][p_settings][ELEMENT_TAGS]],
        status_hud[p_info[playerid][p_settings][ELEMENT_BUTTONS]],
        status_hud[p_info[playerid][p_settings][ELEMENT_HUD]],
        status_hud[p_info[playerid][p_settings][ELEMENT_TEXTLABELS]],
        status_hud[p_info[playerid][p_settings][ELEMENT_CHAT_OUTTIME]]);
    ShowPlayerDialog(playerid, D_PLAYER_SETTINGS_HUD, DIALOG_STYLE_TABLIST_HEADERS, ""I"Настройка худа", STRING_GLOBAL, "Выбрать", "Отмена");
}

ShowPlayerSettingsChat(playerid)
{
    new status_chat[][] = {"{"#cLIGHTRED"}Выключен"W"","{"#cGREEN"}Включен"W""};
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
    "I"[1]"W" Очистить чат\n\
    "I"[2]"W" Объявления: %s\n\
    "I"[3]"W" Рабочий чат: %s\n\
    "I"[4]"W" Действия администрации: %s\n\
    "I"[5]"W" VIP чат: %s\n\
    "I"[6]"W" Фракционный чат: %s\n\
    "I"[7]"W" Семейный чат: %s",
    status_chat[p_info[playerid][p_settings][1]],
    status_chat[p_info[playerid][p_settings][0]],
    status_chat[p_info[playerid][p_settings][2]],
    status_chat[p_info[playerid][p_settings][3]],
    //new
    status_chat[p_info[playerid][p_settings][CHAT_FRACTION]],
    status_chat[p_info[playerid][p_settings][CHAT_FAMILY]]);
    ShowPlayerDialog(playerid, D_PLAYER_SETTINGS_CHAT, DIALOG_STYLE_LIST, ""I"Настройки чата", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

UpdatePlayerSetting(playerid)
{
    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_PLAYER_SETTINGS; i++)
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, p_info[playerid][p_settings][i], i == MAX_PLAYER_SETTINGS-1 ? "":"|");

    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `p_settings` = '%s' WHERE `id` = %d",
    STRING_GLOBAL, p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

CMD:crosshair(playerid, params[])
{
    if(SRV_ID) return 1;
    new id = strval(params);
    if(!(0 <= id <= 17)) return 1;
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "crosshair_%d", id);
    SendChangeAim(playerid, STRING_GLOBAL);
    return 1;
}

CMD:acctags(playerid)
{
    UpdateVisibleAccOrCostume(playerid);
    return 1;
}

UpdateVisibleAccOrCostume(playerid)
{
    p_info[playerid][p_settings][ACC_VISIBLE] ^= 1;
    SendAccess(playerid, "Вы %s отображение акксесуаров/костюмов на игроках.", p_info[playerid][p_settings][ACC_VISIBLE] == 0 ? "выключили" : "включили");
    UpdatePlayerSetting(playerid);

    if(!p_info[playerid][p_settings][ACC_VISIBLE])
    {
        foreach(new i: PlayerPlayersStream[playerid])
        {
            for(new slot = MAX_PLAYER_ATTACHED_OBJECTS-1; slot != -1; slot--)
            {
                if(IsPlayerAttachedObjectSlotUsed(i, slot)) RemoveAttachedObjectForPlayer(i, playerid, slot);
            }
        }
    }
    else
    {
        foreach(new i: PlayerPlayersStream[playerid]) AttachToPlayerAccOrCostume(i, playerid);
    }
    return 1;
}

MaskMail(const inputtext[], output[], Float:interest = 45.0)
{
	new len = strlen(inputtext), find = strfind(inputtext, "@"), hide = floatround(interest / 100.0 * find);

	for(new i; i < len; i++)
	{
		if(i > find || i > hide && i < find) output[i] = '*';
		else output[i] = inputtext[i];
	}
}

SendCodeMail(playerid, user_mail[])
{
    p_temp[playerid][random_code] = RandomEx(100000,999999);

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL,"%sНик: <strong>%s</strong><br/>Код: <strong>%d</strong>%s", Mail_Header, get_name(playerid), p_temp[playerid][random_code], Mail_Footer);
    SendMail(user_mail, "flin-rp.com", "flin-rp.com", STRING_GLOBAL, "b5b834bt");
    //SendMailArtem(MAILER_URL, "code_reg", mail_user, get_name(playerid), STRING_GLOBAL, p_temp[playerid][session_IP], "flin");
    SendInfo(playerid, "На Ваш E-Mail высланно письмо с кодом.");
}

IsMailConfirmed(playerid)
{
    return p_info[playerid][email_confirmed];
}

