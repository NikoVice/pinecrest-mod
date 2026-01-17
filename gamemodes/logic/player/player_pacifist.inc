
/*
    Pacifist mode
    Author: Vip_Uzer
*/

// playerid - тот кто получает урон
// issuerid - тот кто выдает урон
PacifistMode(playerid, issuerid)
{
    if(p_info[playerid][p_settings][PACIFIST_MODE])
    {
        if(GetFactionType(p_info[issuerid][member]) == FACTION_TYPE_GOS && p_info[issuerid][fwork] == true) return 1;
        if(GetFactionType(p_info[playerid][member]) == FACTION_TYPE_CRIMINAL)
        {
            PacifistModeToggle(playerid, 0);
            return 1;
        }
        if(GetFactionType(p_info[issuerid][member]) == FACTION_TYPE_CRIMINAL)
        {
            PacifistModeToggle(issuerid, 0);
            return 1;
        }
        if(GetPlayerVirtualWorld(playerid) == 0 && 
            (GetGangZoneID(playerid) != INVALID_CRIMINAL_ZONE_ID || GetFamilyZoneID(playerid) != INVALID_CRIMINAL_ZONE_ID))
            return 1;
        if(p_info[playerid][wanted] != 0)
        {
            PacifistModeToggle(playerid, 0);
            return 1;
        }
        if(p_info[issuerid][wanted] != 0)
        {
            PacifistModeToggle(issuerid, 0);
            return 1;
        }
        if( player_lobby_status[playerid] == true ||
            p_temp[playerid][DuelID] != INVALID_PLAYER_ID ||
            GetPlayerStatusCapture(playerid) != CAPTURE_ID_NONE ||
            p_temp[playerid][SparringID] != -1 ||
            RegisterDerby[playerid] != 0 ||
            RegisterPaintBall[playerid] != 0 ||
            p_temp[playerid][cossack_robbers_register] != 0 ||
            RegisterRace[playerid] != 0) return 1;
        GameTextForPlayer(issuerid, "~r~Pacifist Mode", 1000, 3);
        return 0;
    }
    return 1;
}

PacifistModeToggle(playerid, toggle)
{
    p_info[playerid][p_settings][PACIFIST_MODE] = toggle;
    UpdatePlayerSetting(playerid);
}
CMD:pacifist(playerid, params[])
{
    if(p_temp[playerid][pacifist_time] > timestamp) return SendError(playerid, "Использовать можно раз в 15 секунд.");
    if(!p_info[playerid][p_settings][PACIFIST_MODE])
    {
        if(GetFactionType(p_info[playerid][member]) == FACTION_TYPE_CRIMINAL)
            return SendError(playerid, "Криминальным структурам не доступно.");
        if(GetFactionType(p_info[playerid][member]) == FACTION_TYPE_GOS && p_info[playerid][fwork] == true)
            return SendError(playerid, "Закончите рабочий день чтобы активировать режим.");
        if(p_info[playerid][wanted] != 0)
            return SendError(playerid, "Вы в розыске, режим не доступен.");
    }
    p_temp[playerid][pacifist_time] = timestamp+15;
    PacifistModeToggle(playerid, !p_info[playerid][p_settings][PACIFIST_MODE]);
    SendAccess(playerid, "Вы %s режим пацифиста.", p_info[playerid][p_settings][PACIFIST_MODE] == 0 ? "выключили" : "включили");
    return 1;
}

CMD:pacifistinfo(playerid, params[])
{
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Пацифист режим", "\
        "W"Активировав ("E"/pacifist"W") данный режим - Вы получаете "I"неуязвимость"W"\n\
        от выстрелов с оружия(!) других игроков, кроме сотрудников гос. структур.\n\
        При этом Вы сами теряете  доступ к возможности использовать оружие.\n\
        \n\
        Режим автоматически активируется для игроков первого и второго уровня без фракции.\n\
        Для игроков выше уровней предусмотрена подсказка после входа в игру.\n\
        Ограниничение между включениям и отключения режима - 15 секунд.\n\
        \n\
        Режим имеет ряд ограничений: его не могут использовать участники криминальных структур\n\
        и сотрудники государственных организаций во время рабочего дня.\n\
        Режим автоматически выключится если: получить розыск, попасть на территорию Ghetto, Family Zones.\n\
        В режиме пацифиста недоступна маска (/mask).\n\
        Режим не работает если: вы участвуете в спарринге, мероприятиях.", "Понял", "");
    return 1;
}
