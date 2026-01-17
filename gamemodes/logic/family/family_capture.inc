

forward load_fz();
public load_fz()
{
    new str[256];
    for(new i = MAX_CAPTURE_FAMILY_ZONE-1; i != -1; i--)
    {
        fCapture_Info[i][fFamilyID][0] =
        fCapture_Info[i][fFamilyID][1] = INVALID_FAMILY_ID;
        fCapture_Info[i][fFamilyZoneID] = INVALID_CRIMINAL_ZONE_ID;
        fCapture_Info[i][fStatus] = FAMILY_ZONE_NONE;
    }

    new rows;
    cache_get_row_count(rows);

    new year, month, day;
    getdate(year, month, day);

    if(rows)
    {
        for(new idx = 0; idx < rows; idx++)
        {
            f_mysql_fetch_row_format(idx, str, cache_num_fields());
            sscanf(str, "p<|>iffffii",
            FamilyZone_Info[idx][fID],
            FamilyZone_Info[idx][fCoords][0],
            FamilyZone_Info[idx][fCoords][1],
            FamilyZone_Info[idx][fCoords][2],
            FamilyZone_Info[idx][fCoords][3],
            FamilyZone_Info[idx][fFamilyOwner],
            FamilyZone_Info[idx][fColorID]);
            FamilyZone_Info[idx][fID] = GangZoneCreate(FamilyZone_Info[idx][fCoords][0],FamilyZone_Info[idx][fCoords][1],FamilyZone_Info[idx][fCoords][2],FamilyZone_Info[idx][fCoords][3]);
            FamilyZone_Info[idx][fArea] = CreateDynamicRectangle(FamilyZone_Info[idx][fCoords][0],FamilyZone_Info[idx][fCoords][1],FamilyZone_Info[idx][fCoords][2],FamilyZone_Info[idx][fCoords][3], 0, 0, -1);
            UpdateAreaInfo(FamilyZone_Info[idx][fArea], TYPE_CRIMINAL_ZONE, AREA_SUBTYPE_FAMILY_ZONE, idx);
            count_family_zone++;

            if(day == 1)
            {
                FamilyZone_Info[idx][fFamilyOwner] = -1;
                FamilyZone_Info[idx][fColorID] = 0;
            }
            else
            {
                for(new i = family_count-1; i != -1; i--)
                {
                    if(FamilyZone_Info[idx][fFamilyOwner] == FamilyData[i][fMysqlID])
                    {
                        FamilyData[i][fCaptZoneCount]++;
                        break;
                    }
                }
            }
        }
    }
    printf("[%i штук] >> Загружены FamilyZone", count_family_zone);
    ///
    return 1;
}

CMD:fstatus(playerid, params[])
{
    new familyzone = GetFamilyZoneID(playerid);
    if(familyzone == INVALID_CRIMINAL_ZONE_ID)
        return SendError(playerid, "Вы не в зоне захвата территории.");
    if(FamilyZone_Info[familyzone][fFamilyOwner] == -1)
        return ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация о территории", ""W"Данная территория никакой семье не принадлежит.", "Понял", "");
    for(new i = family_count-1; i != -1; i--)
    {
        if(FamilyZone_Info[familyzone][fFamilyOwner] == FamilyData[i][fMysqlID])
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Данная территория принадлежит семье под названием: "I"%s(ID: %d)", FamilyData[i][fName], i);
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация о территории", STRING_GLOBAL, "Понял", "");
            break;
        }
    }
    return 1;
}
CMD:fcapture(playerid, params[])
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1)
        return 1;
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_CAPTURE])
        return SendError(playerid, "Захват территории доступен с %d ранга.", FamilyData[family_idx][fSettingRang][F_CAPTURE]);

    new familyzone;
    if(GetPlayerInterior(playerid) != 0)
        return 1;

    if(SRV_ID)
    {
        if(FamilyData[family_idx][fSeasonExp] < 5000)
            return SendError(playerid, "У Вашей семьи нет столько сезонных очков, нужно минимум 5000.");
        if(timestamp_hour < 12 || timestamp_hour > 23)
            return SendError(playerid, "Проводить захват территории разрешено с 12:00 до 23:00.");
        if(timestamp_minute < 30 || timestamp_minute > 35)
            return SendError(playerid, "Проводить захват территории разрешено с **:30 до **:35 в каждом часу.");
    }

    if(IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(GetPVarInt(playerid, "FLOOD:CAPTURE") > timestamp)
        return SendError(playerid, "Вы не можете так часто использовать команды.");
    SetPVarInt(playerid, "FLOOD:CAPTURE", timestamp+10);

    familyzone = GetFamilyZoneID(playerid);
    if(familyzone == INVALID_CRIMINAL_ZONE_ID)
        return SendError(playerid, "Вы не в зоне захвата территории.");

    new target_family = INVALID_FAMILY_ID;

    if(FamilyZone_Info[familyzone][fFamilyOwner] != -1)
    {
        for(new i = family_count-1; i != -1; i--)
        {
            if(FamilyData[i][fMysqlID] != INVALID_MYSQL_ID && FamilyZone_Info[familyzone][fFamilyOwner] == FamilyData[i][fMysqlID])
            {
                target_family = i;
                break;
            }
        }
    }

    if(SRV_ID)
    {
        if(GetFamilyOnline(family_idx) < 2)
            return SendError(playerid, "У Вашей семьи слишком мало игроков в игре.");

        if(FamilyZone_Info[familyzone][fFamilyOwner] == FamilyData[family_idx][fMysqlID])
            return SendError(playerid, "Данная территория принадлежит Вашей семье.");

        if(IsInFamilyAllowed(family_idx) != 0)
            return SendError(playerid, "Ваша семья в этом часе уже участвовала в битве за территорию.");

        if(IsInFamilyAllowed(target_family) != 0)
            return SendError(playerid, "Эта семья в этом часе уже участвовала в битве за территорию.");
        
        if(target_family == INVALID_FAMILY_ID)
        {
            FamilyZone_Info[familyzone][fFamilyOwner] = FamilyData[family_idx][fMysqlID];
            FamilyZone_Info[familyzone][fColorID] = FamilyData[family_idx][fColorID];
            FamilyData[family_idx][fCaptZoneCount]++;
            GangZoneStopFlashForAll(FamilyZone_Info[familyzone][fID]);
            GangZoneHideForAll(FamilyZone_Info[familyzone][fID]);
            GangZoneShowForAll(FamilyZone_Info[familyzone][fID], (FAMILY_COLORS[FamilyZone_Info[familyzone][fColorID]] & 0xFFFFFF00 | 0x25));
            family_save_fz(familyzone);

            FamilyData[family_idx][fCaptureAllowed] = 1;
            SendAccess(playerid, "Вы взяли территорию  под свой контроль.");
            return 1;
        }
        
        if(GetFamilyOnline(target_family) < 2)
            return SendError(playerid, "У %s слишком мало игроков в игре.", FamilyData[target_family][fName]);
    }
    new slot_id = GetFreeSlotFamilyCapture();
    if(slot_id == -1) return SendError(playerid, "Захват территории уже начался.");

    if(fCapture_Info[slot_id][fStatus] != FAMILY_ZONE_NONE)
        return SendError(playerid, "Захват территории уже начался.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s [%d] из \"%s\" начал захват территории \"%s\".", get_name(playerid), playerid, FamilyData[family_idx][fName], FamilyData[target_family][fName]);
    SendFamilyMessage(family_idx, STRING_GLOBAL);
    SendFamilyMessage(target_family, STRING_GLOBAL);
    SendFamilyMessage(family_idx, "Вы можете подготовиться, у Вас есть 1 минута.");
    SendFamilyMessage(target_family, "Вы можете подготовиться, у Вас есть 1 минута.");

    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    GangZoneFlashForAll(FamilyZone_Info[familyzone][fID], (FAMILY_COLORS[FamilyData[family_idx][fColorID]] & 0xFFFFFF00 | 0x65));

    fCapture_Info[slot_id][fFamilyZoneID] = familyzone;
    fCapture_Info[slot_id][fFamilyID][0] = family_idx;
    fCapture_Info[slot_id][fFamilyID][1] = target_family;
    fCapture_Info[slot_id][fTime] = (60*1);
    fCapture_Info[slot_id][fStatus] = FAMILY_ZONE_PREPARATION;

    FamilyData[family_idx][fCaptureAllowed] =
    FamilyData[target_family][fCaptureAllowed] = 1;

    InitTopList(family_idx, target_family, CAPTURE_ID_FAMILY, 11*60);

    foreach(new i:Player)
    {
        if(p_temp[i][family_game_id] == family_idx || p_temp[i][family_game_id] == target_family)
        {
            GangZoneFlashForPlayer(i, FamilyZone_Info[familyzone][fID], (FAMILY_COLORS[FamilyData[family_idx][fColorID]] & 0xFFFFFF00 | 0x65));

            p_temp[i][CaptureBizWarInfoInt][0] = 0;
            p_temp[i][CaptureBizWarInfoInt][1] = 0;
            p_temp[i][CaptureBizWarInfoFloat][0] = 0.0;
            p_temp[i][CaptureBizWarInfoFloat][1] = 0.0;

            ShowTextDrawForPlayer(i, TD_ID_CAPTURE);
            CaptureInfoUpdate(i, CAPTURE_ID_FAMILY, slot_id);
            SetPlayerColor(i, FAMILY_COLORS[FamilyData[p_temp[i][family_game_id]][fColorID]]);
        }
    }
    SetTimerEx("FamilyCaptureTimers", 1000, false, "i", slot_id);
    return 1;
}
alias:fcapture("fcapt");

GetFreeSlotFamilyCapture()
{
    for(new i; i < MAX_CAPTURE_FAMILY_ZONE; i++)
    {
        if(fCapture_Info[i][fFamilyID][0] == INVALID_FAMILY_ID && fCapture_Info[i][fFamilyID][1] == INVALID_FAMILY_ID && fCapture_Info[i][fFamilyZoneID] == INVALID_CRIMINAL_ZONE_ID)
            return i;
    }
    return -1;
}

GetSlotFamilyCapture(family_one, family_two)
{
    if(family_one == -1) return -1;
    if(family_two == -1)
    {
        for(new i = MAX_CAPTURE_FAMILY_ZONE-1; i!= -1; i--)
        {
            if(fCapture_Info[i][fFamilyID][0] == family_one || fCapture_Info[i][fFamilyID][1] == family_one)
                return i;
        }
    }
    else
    {
        for(new i = MAX_CAPTURE_FAMILY_ZONE-1; i!= -1; i--)
        {
            if( (fCapture_Info[i][fFamilyID][0] == family_one && fCapture_Info[i][fFamilyID][1] == family_two) ||
                (fCapture_Info[i][fFamilyID][0] == family_two && fCapture_Info[i][fFamilyID][1] == family_one))
                return i;
        }
    }
    return -1;
}

GetFamilyZoneID(playerid)
{
    new familyzone;
    familyzone = p_temp[playerid][CriminalZoneID];

    if(!(0 <= familyzone < MAX_FAMILY_ZONE) || !IsPlayerInDynamicArea(playerid, FamilyZone_Info[familyzone][fArea]))
        familyzone = INVALID_CRIMINAL_ZONE_ID;
    return familyzone;
}
///family capture
forward FamilyCaptureTimers(i);
public FamilyCaptureTimers(i)
{
    if(fCapture_Info[i][fTime] > 0)
    {
        fCapture_Info[i][fTime]--;
        foreach(new playerid: Player)
        {
            if(fCapture_Info[i][fFamilyID][0] == p_temp[playerid][family_game_id] || fCapture_Info[i][fFamilyID][1] == p_temp[playerid][family_game_id])
            {
                CaptureInfoUpdate(playerid, CAPTURE_ID_FAMILY, i, false);
            }
        }
        if(fCapture_Info[i][fTime] == 0)
        {
            if(fCapture_Info[i][fStatus] == FAMILY_ZONE_PREPARATION)
            {
                fCapture_Info[i][fStatus] = FAMILY_ZONE_CAPTURE;
                fCapture_Info[i][fTime] = (60*20);
                SendFamilyMessage(fCapture_Info[i][fFamilyID][0], "[F] Подготовка закончилась, начался захват территории.");
                SendFamilyMessage(fCapture_Info[i][fFamilyID][1], "[F] Подготовка закончилась, начался захват территории.");
            }
        }
        SetTimerEx("FamilyCaptureTimers", 1000,false, "i", i);
    }
    else
    {
        new bool:attack_family_is_zone = false;
        foreach(new playerid: Player)
        {
            if(fCapture_Info[i][fFamilyID][0] == p_temp[playerid][family_game_id] &&
                GetFamilyZoneID(playerid) == fCapture_Info[i][fFamilyZoneID])
            {
                attack_family_is_zone = true;
                break;
            }
        }

        STRING_GLOBAL[0] = EOS;
        if(attack_family_is_zone == true && ((fCapture_Info[i][fCount][0] > fCapture_Info[i][fCount][1]) || (!fCapture_Info[i][fCount][0] && !fCapture_Info[i][fCount][1])))
        {
            FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fFamilyOwner] = FamilyData[fCapture_Info[i][fFamilyID][0]][fMysqlID];
            FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fColorID] = FamilyData[fCapture_Info[i][fFamilyID][0]][fColorID];

            f(STRING_GLOBAL, "\"%s\" выиграла захват территории \"%s\".", FamilyData[fCapture_Info[i][fFamilyID][0]][fName], FamilyData[fCapture_Info[i][fFamilyID][1]][fName]);

            FamilyData[fCapture_Info[i][fFamilyID][0]][fCaptZoneCount]++;
            FamilyData[fCapture_Info[i][fFamilyID][1]][fCaptZoneCount]--;

        }
        else if(fCapture_Info[i][fCount][0] <= fCapture_Info[i][fCount][1])
        {
            FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fFamilyOwner] = FamilyData[fCapture_Info[i][fFamilyID][1]][fMysqlID];
            FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fColorID] = FamilyData[fCapture_Info[i][fFamilyID][1]][fColorID];

            f(STRING_GLOBAL, "\"%s\" отстояла территорию \"%s\".", FamilyData[fCapture_Info[i][fFamilyID][1]][fName], FamilyData[fCapture_Info[i][fFamilyID][0]][fName]);
        }
        SendFamilyMessage(fCapture_Info[i][fFamilyID][0], STRING_GLOBAL);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][1], STRING_GLOBAL);

        new best_id[4];
        foreach(new playerid : Player)
        {
            if(fCapture_Info[i][fFamilyID][0] != p_temp[playerid][family_game_id] && fCapture_Info[i][fFamilyID][1] != p_temp[playerid][family_game_id]) continue;

            if(p_temp[playerid][CaptureBizWarInfoInt][0] > p_temp[best_id[0]][CaptureBizWarInfoInt][0]) best_id[0] = playerid;
            if(p_temp[playerid][CaptureBizWarInfoInt][1] > p_temp[best_id[1]][CaptureBizWarInfoInt][1]) best_id[1] = playerid;
            if(p_temp[playerid][CaptureBizWarInfoFloat][0] > p_temp[best_id[2]][CaptureBizWarInfoFloat][0]) best_id[2] = playerid;
            if(p_temp[playerid][CaptureBizWarInfoFloat][1] > p_temp[best_id[3]][CaptureBizWarInfoFloat][1]) best_id[3] = playerid;

            HideTextDrawForPlayer(playerid, TD_ID_CAPTURE);
        }
        STRING_GLOBAL[0] = EOS;
        if(best_id[0] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по убийствам не определен.");
        else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по убийствам %s [%d] (%s). Количество: %d.", get_name(best_id[0]), best_id[0], FamilyData[GetPlayerFamilyID(best_id[0])][fName], p_temp[best_id[0]][CaptureBizWarInfoInt][0]);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][0], STRING_GLOBAL);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][1], STRING_GLOBAL);
        STRING_GLOBAL[0] = EOS;
        if(best_id[1] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по смертям не определен.");
        else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по смертям %s [%d] (%s). Количество: %d.", get_name(best_id[1]), best_id[1], FamilyData[GetPlayerFamilyID(best_id[1])][fName], p_temp[best_id[1]][CaptureBizWarInfoInt][1]);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][0], STRING_GLOBAL);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][1], STRING_GLOBAL);
        STRING_GLOBAL[0] = EOS;
        if(best_id[2] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по нанесенному урону не определен.");
        else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по нанесенному урону %s [%d] (%s). Количество: %0.2f.", get_name(best_id[2]), best_id[2], FamilyData[GetPlayerFamilyID(best_id[2])][fName], p_temp[best_id[2]][CaptureBizWarInfoFloat][0]);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][0], STRING_GLOBAL);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][1], STRING_GLOBAL);
        STRING_GLOBAL[0] = EOS;
        if(best_id[3] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по полученному урону не определен.");
        else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Лучший игрок на захвате по полученному урону %s [%d] (%s). Количество: %0.2f.", get_name(best_id[3]), best_id[3], FamilyData[GetPlayerFamilyID(best_id[3])][fName], p_temp[best_id[3]][CaptureBizWarInfoFloat][1]);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][0], STRING_GLOBAL);
        SendFamilyMessage(fCapture_Info[i][fFamilyID][1], STRING_GLOBAL);

        GangZoneStopFlashForAll(FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fID]);
        GangZoneHideForAll(FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fID]);
        GangZoneShowForAll(FamilyZone_Info[fCapture_Info[i][fFamilyZoneID]][fID], (FAMILY_COLORS[FamilyZone_Info[i][fColorID]] & 0xFFFFFF00 | 0x25));
        family_save_fz(fCapture_Info[i][fFamilyZoneID]);

        foreach(new playerid: Player)
        {
            if(PlayerFixZone[playerid] != 0)
            {
                PlayerFixZone[playerid] = 0;
                GangZoneStopFlashForPlayer(playerid, i);
            }
            if(fCapture_Info[i][fFamilyID][0] != p_temp[playerid][family_game_id] && fCapture_Info[i][fFamilyID][1] != p_temp[playerid][family_game_id]) continue;
            HideTextDrawForPlayer(playerid, TD_ID_CAPTURE);
        }
        fCapture_Info[i][fFamilyZoneID] = INVALID_CRIMINAL_ZONE_ID;

        FamilyData[fCapture_Info[i][fFamilyID][0]][fCaptureAllowed] =
        FamilyData[fCapture_Info[i][fFamilyID][1]][fCaptureAllowed] = 0;

        fCapture_Info[i][fCount][0] = 0;
        fCapture_Info[i][fCount][1] = 0;
        fCapture_Info[i][fStatus] = FAMILY_ZONE_NONE;//

        fCapture_Info[i][fFamilyID][0] = INVALID_FAMILY_ID;
        fCapture_Info[i][fFamilyID][1] = INVALID_FAMILY_ID;
    }
}

family_save_fz(idx)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family_zone` SET `family` = %d, `colorid` = %d WHERE `id` = %d",
        FamilyZone_Info[idx][fFamilyOwner], FamilyZone_Info[idx][fColorID], idx+1);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

CheckFamilyDamage(playerid, damagedid, Float:amount)
{
    if(damagedid != INVALID_PLAYER_ID && (GetPlayerFamilyID(playerid) != -1 && GetPlayerFamilyID(damagedid) != -1))
    {
        new family_playerid = p_temp[playerid][family_game_id];
        new family_damagedid = p_temp[damagedid][family_game_id];
        if(family_playerid != family_damagedid)
        {
            new i = GetSlotFamilyCapture(family_playerid, family_damagedid);
            if(i != -1 && fCapture_Info[i][fStatus] == FAMILY_ZONE_CAPTURE)
            {
                new family_zoneid = fCapture_Info[i][fFamilyZoneID];
                if(family_zoneid != INVALID_CRIMINAL_ZONE_ID &&
                    IsPlayerCaptureZone(damagedid, FamilyZone_Info[family_zoneid][fCoords][0], FamilyZone_Info[family_zoneid][fCoords][1], FamilyZone_Info[family_zoneid][fCoords][2], FamilyZone_Info[family_zoneid][fCoords][3]))
                {
                    p_temp[damagedid][CaptureBizWarInfoFloat][0] += amount;
                    p_temp[playerid][CaptureBizWarInfoFloat][1] += amount;
                }
            }
        }
    }
}

CheckFamilyKills(playerid, killerid, reason)
{
    if(killerid != INVALID_PLAYER_ID && GetPlayerFamilyID(playerid) != -1 && GetPlayerFamilyID(killerid) != -1)
    {
        new family_playerid = p_temp[playerid][family_game_id];
        new family_killerid = p_temp[killerid][family_game_id];
        if(family_playerid != family_killerid)
        {
            new i = GetSlotFamilyCapture(family_playerid, family_killerid);
            if(i != -1 && fCapture_Info[i][fStatus] == FAMILY_ZONE_CAPTURE)
            {
                new family_zoneid = fCapture_Info[i][fFamilyZoneID];
                if(family_zoneid != INVALID_CRIMINAL_ZONE_ID &&
                    IsPlayerCaptureZone(killerid, FamilyZone_Info[family_zoneid][fCoords][0], FamilyZone_Info[family_zoneid][fCoords][1], FamilyZone_Info[family_zoneid][fCoords][2], FamilyZone_Info[family_zoneid][fCoords][3]))
                {
                    //new idx;
                    if(fCapture_Info[i][fFamilyID][0] == family_killerid)
                        fCapture_Info[i][fCount][0]++;// idx = i == 0 ? 0 : 2;
                    else
                        fCapture_Info[i][fCount][1]++;// idx = i == 0 ? 1 : 3;

                    p_temp[killerid][CaptureBizWarInfoInt][0]++;
                    p_temp[playerid][CaptureBizWarInfoInt][1]++;

                    AddTopList(killerid);

                    foreach(new idx: Player)
                    {
                        if(p_temp[idx][family_game_id] == family_playerid || p_temp[idx][family_game_id] == family_killerid)
                            SendDeathMessageToPlayer(idx, killerid, playerid, reason);
                            //AddToKillList(idx, playerid, killerid, reason);
                    }
                }
            }
        }
    }
}

ShowFamilyZone(playerid)
{
    for(new i = count_family_zone-1; i != -1; i--)
    {
        GangZoneShowForPlayer(playerid, FamilyZone_Info[i][fID], (FamilyZone_Info[i][fFamilyOwner] != -1) ? (FAMILY_COLORS[FamilyZone_Info[i][fColorID]] & 0xFFFFFF00 | 0x65) : (0xFFFFFF90));
    }
}

GiveFamilyPay()
{
    for(new i = family_count-1; i != -1; i--)
    {
        FamilyData[i][fCaptureAllowed] = 0;
        if(FamilyData[i][fCaptZoneCount] > 0)
        {
            FamilyData[i][fMoney] += FamilyData[i][fCaptZoneCount]*500;
        }
    }
}

cmd:fftest(playerid, params[])
{
    if(SRV_ID == 0 && p_info[playerid][admin] > 6)
    {
        GiveFamilyPay();
        SendInfo(playerid, "Обнуление успешное.");
    }
    return 1;
}

CMD:fzcolor(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /fzcolor [gameID family](/familylist)");
    if(!(0 <= params[0] < family_count)) return 1;
    new familyzone = GetFamilyZoneID(playerid);
    if(familyzone == -1) return SendError(playerid, "Вы не находитесь на семейной территории.");

    if(FamilyZone_Info[familyzone][fFamilyOwner] != -1)
    {
        for(new i = family_count-1; i != -1; i--)
        {
            if(FamilyZone_Info[familyzone][fFamilyOwner] == FamilyData[i][fMysqlID])
            {
                FamilyData[i][fCaptZoneCount]--;
                break;
            }
        }
    }

    FamilyZone_Info[familyzone][fFamilyOwner] = FamilyData[params[0]][fMysqlID];
    FamilyZone_Info[familyzone][fColorID] = FamilyData[params[0]][fColorID];

    FamilyData[params[0]][fCaptZoneCount]++;

    GangZoneStopFlashForAll(FamilyZone_Info[familyzone][fID]);
    GangZoneHideForAll(FamilyZone_Info[familyzone][fID]);
    GangZoneShowForAll(FamilyZone_Info[familyzone][fID], (FAMILY_COLORS[FamilyZone_Info[familyzone][fColorID]] & 0xFFFFFF00 | 0x25));
    family_save_fz(familyzone);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] изменил владение семейной территории %d.", get_name(playerid), playerid, familyzone);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) установил контроль family территории %d для %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", familyzone, FamilyData[params[0]][fName]);
    return 1;
}

CMD:wipefz(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /wipefz [gameID family](/familylist)");
    if(!(0 <= params[0] < family_count)) return 1;
    new count_zone;
    for(new i = count_family_zone-1; i != -1; i--)
    {
        if(FamilyZone_Info[i][fFamilyOwner] == FamilyData[params[0]][fMysqlID])
        {
            FamilyData[params[0]][fCaptZoneCount]--;
            FamilyZone_Info[i][fFamilyOwner] = -1;
            FamilyZone_Info[i][fColorID] = 0;

            GangZoneStopFlashForAll(FamilyZone_Info[i][fID]);
            GangZoneHideForAll(FamilyZone_Info[i][fID]);
            GangZoneShowForAll(FamilyZone_Info[i][fID], (FAMILY_COLORS[FamilyZone_Info[i][fColorID]] & 0xFFFFFF00 | 0x25));
            family_save_fz(i);
            count_zone++;
        }
    }
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] обнулил владеление семейных территорий %s.", get_name(playerid), playerid, FamilyData[params[0]][fName]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) обнулил семье %s территории: %d шт. | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        FamilyData[params[0]][fName], count_zone);
    return 1;
}
