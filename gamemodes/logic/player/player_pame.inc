CMD:pame(playerid, params[])
{
    if(p_info[playerid][level] < 3) return SendError(playerid, "Доступно с 3 уровня.");
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    if(p_info[playerid][pame_time] > timestamp)
        return SendError(playerid, "Ставить описание персонажа можно раз в 1 час. Можно поставить через %s.", ConvertTime(p_info[playerid][pame_time]-timestamp));
    new result[128];
    if(sscanf(params, "s[128]", result)) return SendInfo(playerid, "/pame [описание]");
    if(!(3 <= strlen(result) < 128)) return SendInfo(playerid, "/pame [описание]");
    if(AdvertisingCheck(result)) return AdvertisingPunishment(playerid, result, 1);

    if(strlen(result) >= 40)
    {
        new str[128], n = 20;
        for(;n <= 80; n++) if(result[n] == ' ') break;
        strmid(str, result, n+1, 128, 128);
        strdel(result, n, 128);
        format(result, 128, "%s\n%s", result, str);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] Игрок %s[%d] поставил себе /pame:", get_name(playerid), playerid);
        SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] ... %s", result);
        SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

        format(p_info[playerid][pame_text], 128, result);
        PlayerPame_Update(playerid, true);
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A]  Игрок %s[%d] поставил себе /pame: %s", get_name(playerid), playerid, result);
        SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

        format(p_info[playerid][pame_text], 128, result);
        PlayerPame_Update(playerid, true);
    }
    p_info[playerid][pame_time] = timestamp+3600;
    MysqlUpdatePlayerInt(playerid, "pame_time", p_info[playerid][pame_time]);
    MysqlUpdatePlayerStr(playerid, "pame_text", p_info[playerid][pame_text]);
    SendInfo(playerid, "Вы успешно установили описание персонажа. Убрать: /pameoff");
    return true;
}
alias:pame("desk");

CMD:pameoff(playerid, params[])
{
    if(p_temp[playerid][pame_label] == Text3D:-1) return SendError(playerid, "У Вас не стоит описание персонажа.");
    PlayerPame_Delete(playerid);
    SendInfo(playerid, "Вы удалили описание персонажа.");
    return true;
}

CMD:dpame(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return true;
    new scdplayerid, reason[144];
    if(sscanf(params, "us[144]", scdplayerid, reason)) return SendInfo(playerid, "Используйте: /dpame [id игрока] [причина]");
    if(scdplayerid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(p_temp[scdplayerid][pame_label] == Text3D:-1) return SendError(playerid, "У игрока нет описания персонажа");
    PlayerPame_Delete(scdplayerid);
    SendInfo(scdplayerid, "Администратор %s[%d] удалил вам описание персонажа. Причина: %s", get_name(playerid), playerid, reason);
    SendInfo(playerid, "Вы удалили игроку %s[%d] описание персонажа. Причина: %s", get_name(scdplayerid), scdplayerid, reason);
    
    WriteAdminLog(TYPE_LOG_DPAME, playerid, get_name(scdplayerid), scdplayerid, reason);
    return 1;
}

CMD:mypame(playerid, params[])
{
    if(!strlen(p_info[playerid][pame_text]))
        return SendError(playerid, "У Вашего персонажа нет описания.");
    SendInfo(playerid, "Ваше описание персонажа: %s", p_info[playerid][pame_text]);
    return 1;
}

PlayerPame_Delete(playerid)
{
    if(p_temp[playerid][pame_label] != Text3D:-1)
    {
        DestroyDynamic3DTextLabel(p_temp[playerid][pame_label]);
        p_temp[playerid][pame_label] = Text3D:-1;
    }
    p_info[playerid][pame_text][0] = EOS;
    MysqlUpdatePlayerStr(playerid, "pame_text", p_info[playerid][pame_text]);
}

PlayerPame_Update(playerid, bool:addLabel)
{
    if(p_temp[playerid][pame_label] != Text3D:-1)
    {
        if(addLabel) UpdateDynamic3DTextLabelText(p_temp[playerid][pame_label], COLOR_GRAY, p_info[playerid][pame_text]);
        else
        {
            DestroyDynamic3DTextLabel(p_temp[playerid][pame_label]);
            p_temp[playerid][pame_label] = Text3D:-1;
        }
    }
    else
    {
        if(addLabel)
        {
            p_temp[playerid][pame_label] = CreateDynamic3DTextLabel(p_info[playerid][pame_text], COLOR_GRAY, 0.0, 0.0, -0.5, 15.0, playerid, .testlos = 1);
            foreach(new i: PlayerPlayersStream[playerid]) Streamer_ToggleItem(i, STREAMER_TYPE_3D_TEXT_LABEL, p_temp[playerid][pame_label], p_info[i][p_settings][PAME_LABEL]);
        }
    }
}

ToggleVisiblePameLabel(playerid)
{
    foreach(new i: PlayerPlayersStream[playerid])
    {
        if(p_temp[i][pame_label] != Text3D:-1)
            Streamer_ToggleItem(playerid, STREAMER_TYPE_3D_TEXT_LABEL, p_temp[i][pame_label], p_info[playerid][p_settings][PAME_LABEL]);
    }
    Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
}

CMD:pametags(playerid, params[])
{
    p_info[playerid][p_settings][PAME_LABEL] ^= 1;
    ToggleVisiblePameLabel(playerid);
    SendAccess(playerid, "Вы %s отображение описания персонажей.", p_info[playerid][p_settings][PAME_LABEL] == 0 ? "выключили" : "включили");
    UpdatePlayerSetting(playerid);
    return 1;
}
