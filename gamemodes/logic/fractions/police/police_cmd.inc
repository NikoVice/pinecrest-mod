/* CMD:taser(playerid, params[])
{
    new faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD || !IsFactionDocs(faction))    return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(p_info[playerid][fwork] == false)                            return SendError(playerid, "Сначала нужно выйти на дежурство.");

    if(!p_temp[playerid][pTaser])
    {
        if(PlayerInfo[playerid][pPlayerWeapon] != 0) cmd::putgun(playerid, "");
        GivePlayerWeaponEx(playerid, 23, 1, 1, 0);
        p_temp[playerid][pTaser] = 1;
        SetPlayerChatBubble(playerid, "достает электрошокер c тактического пояса.", COLOR_PURPLE, 20.0, 4000);
        SM1(playerid, "Вы достали электрошокер.");
        return 1;
    }

    ResetPlayerWeapons(playerid);

    if(PlayerInfo[playerid][pPlayerWeapon] != 0) RemovePlayerAttachedObject(playerid, ATTACH_HANDS);

    PlayerInfo[playerid][pPlayerWeapon] = 0;
    PlayerInfo[playerid][pPlayerAmmo] = 0;
    PlayerInfo[playerid][pAmmoType] = 0;
    PlayerInfo[playerid][pWepSerial] = 0;

    p_temp[playerid][pTaser] = 0;
    SetPlayerChatBubble(playerid, "убирает электрошокер на тактический пояс.", COLOR_PURPLE, 20.0, 4000);
    SM1(playerid, "Вы убрали электрошокер.");
    return 1;
} 

CMD:trace(playerid, params[])
{
    new faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)  return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)    return SendError(playerid, "Сначала нужно выйти на дежурство.");

    new vehicleid = GetPlayerVehicleID(playerid);

    if(!IsPlayerInAnyVehicle(playerid))                return SendError(playerid, "Вы должны находиться в транспорте.");
    if(veh_info[vehicleid][v_npoId] != faction)    return SendError(playerid, "Вы не в служебном транспорте.");

    new trace, targetid;
    if(sscanf(params,"d", trace)) return SendInfo(playerid, "Введите: /trace [номер телефона]");
    if(p_temp[playerid][pTracePlayer] != INVALID_PLAYER_ID) return SendError(playerid, "Сначала выйдите из системы (/traceoff).");
    //if(trace == PlayerInfo[playerid][pNumber]) return 1;
    if((targetid = GetOwnerPhoneNumber(trace)) == INVALID_PLAYER_ID)    return SendError(playerid, "Указанный номер не найден в базе данных.");
    if(p_info[targetid][jail] != 0) return SendError(playerid, "Владелец этого номера находится под стражей.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "** HQ: %s %s отслеживает номер телефона %i. **", GetPlayerFractionRangName(playerid), get_name(playerid), trace);
    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

    //ShowPlayerDialog(playerid, D_SHOW_TRACE, DIALOG_STYLE_MSGBOX, ""I"Оповещение", ""W"Система отслеживания, чтобы закрыть нажмите ESC.\n\n{B4B5B7}Началось отслеживание . . .", "Закрыть", "");

    ShowPlayerDialog(playerid, D_SHOW_TRACE, DIALOG_STYLE_MSGBOX, ""I"Оповещение", ""W"Система отслеживания, чтобы закрыть нажмите ESC.\n\n{B4B5B7}Началось отслеживание . . .", "Закрыть", "")

    p_temp[playerid][pTracePlayer] = targetid;
    p_temp[playerid][pTraceStage] = 0;

    new Float:x, Float:y, Float:z;


    if(GetPlayerVirtualWorld(targetid) || GetPlayerInterior(targetid))
    {
        x = PlayerInfo[targetid][pLocationPos][0];
        y = PlayerInfo[targetid][pLocationPos][1];
        z = PlayerInfo[targetid][pLocationPos][2];
    }
    else GetPlayerPos(targetid, x, y, z);

    p_temp[playerid][pTraceDist][0] = GetDistanceBetweenPoints(x, y, z, 1459.3712, -783.0401, 93.6459);
    p_temp[playerid][pTraceDist][1] = GetDistanceBetweenPoints(x, y, z, 2667.2908, -1957.5245, 13.5469);
    p_temp[playerid][pTraceDist][2] = GetDistanceBetweenPoints(x, y, z, 923.6055, -1893.5146, 1.5319);
    return 1;
}

CMD:traceoff(playerid, params[])
{
    if(p_temp[playerid][pTracePlayer] == INVALID_PLAYER_ID)    return SendError(playerid, "Вы не находитесь в системе слежения.");

    if(p_temp[playerid][pTraceGZ] != -1) GangZoneDestroy(p_temp[playerid][pTraceGZ]);

    p_temp[playerid][pTraceGZ] = -1;
    p_temp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
    p_temp[playerid][pTraceStage] = 0;
    SendInfo(playerid, "Вы вышли из системы слежения.");
    return 1;
}
*/

CMD:ticket(playerid, params[])
{
    if(p_info[playerid][rang] < 5) return 1;
    new amount, reason[144], userid, faction = p_info[playerid][member];
    if(sscanf(params, "uds[144]", userid, amount, reason)) return SendInfo(playerid, "Введите: /ticket [ID/имя игрока] [сумма штрафа ($1-$5.000)] [причина]");
    if(userid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
    if(!IsPlayerStream(3.0, playerid, userid)) return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD && GetFactionCategory(faction) != FACTION_CATEGORY_FBI) return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(strlen(reason) < 1 || strlen(reason) > 63) return SendError(playerid, "Причина не более 63 символов.");
    if(!( 1<= amount <= 50000)) return SendError(playerid, "Сумма штрафа от $1 до $50000.");
    if(CountPlayerTicketsID(p_info[userid][ID]) > MAX_TICKETS) return SendError(playerid, "У игрока максимальное количество штрафов.");
    if(userid == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetPVarInt(userid,"BoneStol_ID")) return 1;

    SendAccess(playerid, "Вы выписали %s [%d] штрафную квитанцию в размере %d$. Причина: %s", get_name(userid), userid, amount, reason);
    SendAccess(userid, "%s [%d] выписал Вам штрафную квитанцию в размере %d$. Причина: %s", get_name(playerid), playerid, amount, reason);
    SendInfo(userid, "Для просмотра списка штрафов используйте \"/tickets\".");

    SetPlayerChatBubble(playerid, "выписал штрафную квитанцию", COLOR_PURPLE, 20.0, 4000);

    p_temp[playerid][pPoliceFines]++;
    GivePlayerTicket(playerid, userid, amount, reason);
    return 1;
}


CMD:vehiclefine(playerid, params[])
{
    if(p_info[playerid][rang] < 7) return 1;
    if(GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_PD && GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_FBI) return SendError(playerid, "Вы должны быть офицером полиции.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    new amount, vehicleid = GetNearVehicle(playerid, 1.5), reason[144];
    if(sscanf(params, "is[144]", amount, reason)) return SendInfo(playerid, "Введите: /vfine [сумма штрафа ($1-$5.000)] [причина] (стоять прям у автомобиля!)");
    if(vehicleid < 1) return SendError(playerid, "Вы должны находиться рядом с транспортом.");
    if(strequals(veh_info[vehicleid][v_number], "NULL") || !veh_info[vehicleid][v_mysql_id] ||  !veh_info[vehicleid][v_owner_id])
        return SendError(playerid, "Транспортное средство не было найдено.");
    if(strlen(reason) < 1 || strlen(reason) > 63) return SendError(playerid, "Причина не более 63 символов.");
    if(amount < 1 || amount > 5000) return SendError(playerid, "Сумма штрафа не менее $1 и не более $5.000.");
    if(CountVehicleTicketsID(vehicleid) > MAX_TICKETS) return SendError(playerid, "На данном транспортном средстве максимальное количество штрафов.");

    SetPlayerChatBubble(playerid, "выписал штрафную квитанцию", COLOR_PURPLE, 20.0, 4000);

    new userid = GetPlayerUserID(veh_info[vehicleid][v_owner_id]);
    if(userid != INVALID_PLAYER_ID)
    {
        SendInfo(userid, "%s %s выписал штраф на Ваш %s на сумму $%s. Причина: \"%s\".", GetPlayerFractionRangName(playerid), get_name(playerid), GetVehicleName(vehicleid), ConvertNumber(amount), reason);
        SendInfo(userid, "Для просмотра списка штрафов на транспортном средстве используйте /vtickets.");
    }

    SendAccess(playerid, "Вы выписали штрафную квитанцию \"%s\" на %s на сумму $%s.", reason, GetVehicleName(vehicleid), ConvertNumber(amount));
    p_temp[playerid][pPoliceFines]++;
    GiveVehicleTicket(playerid, vehicleid, amount, reason);
    return 1;
}
alias:vehiclefine("/vfine");

CMD:checkfines(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(p_info[playerid][rang] < 3) return SendError(playerid, "Доступно с 3 ранга.");
    new userid;
    if(sscanf(params, "u", userid)) return SendInfo(playerid, "/checkfines [ID/имя игрока]");
    if(userid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
    if(!IsPlayerStream(3.0, playerid, userid)) return SendError(playerid, "Игрок далеко от Вас.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `tickets` WHERE `userid` = %i AND `paid` =0 LIMIT %i", p_info[userid][ID], MAX_TICKETS);
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayersTickets", "ii", playerid, 0);

    SetPVarInt(playerid, #tickets_show, p_info[userid][ID]);
    SetPVarInt(playerid, #ticketsuse, 1);
    return 1;
}

CMD:checkvfines(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве (/duty).");

    new vehicleid;
    if(isnull(params)) return SendInfo(playerid, "/checkvfines [гос. номер транспортного средства (/checknumber)]");
    if(strlen(params) > 12) return SendError(playerid, "Данного транспортного номера не существует.");
    if((vehicleid = FindVehicleByPlate(params)) == -1) return SendError(playerid, "Транспортное средство не было найдено.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `tickets` WHERE `vehicle`= %i AND `paid` = 0 LIMIT %i", veh_info[vehicleid][v_mysql_id], MAX_TICKETS);
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayersTickets", "i", playerid);

    SetPVarInt(playerid, #tickets_show, vehicleid);
    SetPVarInt(playerid, #ticketsuse, 1);
    return 1;
}
/*
ALTX:doorram("/dram");
CMD:doorram(playerid, params[])
{
    if(PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || p_temp[playerid][pTaserTime] || p_temp[playerid][pCuffed] || PhoneInfo[playerid][current_page] == PAGE_NOTIFICATION || PlayerInfo[playerid][pJailed] != 0)
        return SendError(playerid, "Вы не можете использовать данную функцию прямо сейчас.");

    new building;
    switch(GetNearBuilding(playerid)) {
        case 0: {
            building = GetNearInsideHouse(playerid);
            if(building == -1)    return 1;

            for(new i = 0; i < MAX_FURNITURE; i++)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 1.5, HFurn[building][i][fPosX], HFurn[building][i][fPosY], HFurn[building][i][fPosZ]) || !HFurn[building][i][fOn] || !isHouseDoor(HFurn[building][i][fModel]))
                {
                    continue;
                }
                if(HFurn[building][i][fOpened])    return SendWarningMessage(playerid, "Дверь и так открыта.");

                cmd::server_ame(playerid, "выбивает дверь с ноги");
                ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,0,1,1);

                SetTimerEx("DoorRamEnd", 1000, false, "iiii", 0, building, i, playerid);
                break;
            }
        }
        case 1: {
            building = GetNearInsideBiz(playerid);
            if(building == -1)    return 1;

            for(new i = 0; i < MAX_FURNITURE; i++)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 1.5, BFurn[building][i][fPosX], BFurn[building][i][fPosY], BFurn[building][i][fPosZ]) || !BFurn[building][i][fOn] || !isHouseDoor(BFurn[building][i][fModel]))
                {
                    continue;
                }
                if(BFurn[building][i][fOpened])    return SendWarningMessage(playerid, "Дверь и так открыта.");

                cmd::server_ame(playerid, "выбивает дверь с ноги");
                ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,0,1,1);

                SetTimerEx("DoorRamEnd", 1000, false, "iiii", 1, building, i, playerid);
                break;
            }
        }
        case 2: {
            building = GetNearInsideGarage(playerid);
            if(building == -1)    return 1;

            for(new i = 0; i < MAX_FURNITURE; i++)
            {
                if(!IsPlayerInRangeOfPoint(playerid, 1.5, GFurn[building][i][fPosX], GFurn[building][i][fPosY], GFurn[building][i][fPosZ]) || !GFurn[building][i][fOn] || !isHouseDoor(GFurn[building][i][fModel]))
                {
                    continue;
                }
                if(GFurn[building][i][fOpened])    return SendWarningMessage(playerid, "Дверь и так открыта.");

                cmd::server_ame(playerid, "выбивает дверь с ноги");
                ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,0,1,1);

                SetTimerEx("DoorRamEnd", 1000, false, "iiii", 2, building, i, playerid);
                break;
            }
        }
    }
    return 1;
}

this::DoorRamEnd(type, building, i, playerid)
{
    switch(type)
    {
        case 0: {
            HFurn[building][i][fLocked] = 0;
            HFurn[building][i][fOpened] = 1;

            MoveDynamicObject(HFurn[building][i][fObject], HFurn[building][i][fPosX], HFurn[building][i][fPosY], HFurn[building][i][fPosZ], 1.5, HFurn[building][i][fPosRX], HFurn[building][i][fPosRY], HFurn[building][i][fPosRZ]-90.0);

        }
        case 1: {
            BFurn[building][i][fLocked] = 0;
            BFurn[building][i][fOpened] = 1;

            MoveDynamicObject(BFurn[building][i][fObject], BFurn[building][i][fPosX], BFurn[building][i][fPosY], BFurn[building][i][fPosZ], 1.5, BFurn[building][i][fPosRX], BFurn[building][i][fPosRY], BFurn[building][i][fPosRZ]-90.0);
        }
        case 2: {
            GFurn[building][i][fLocked] = 0;
            GFurn[building][i][fOpened] = 1;

            MoveDynamicObject(GFurn[building][i][fObject], GFurn[building][i][fPosX], GFurn[building][i][fPosY], GFurn[building][i][fPosZ], 1.5, GFurn[building][i][fPosRX], GFurn[building][i][fPosRY], GFurn[building][i][fPosRZ]-90.0);
        }
    }

    ClearAnimations(playerid);
    GameTextForPlayer(playerid, "~w~ВЫ ~y~ВЫБИЛИ~w~ ДВЕРЬ", 1000, 1);
    return 1;
}

CMD:ram(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)                                                      return SendError(playerid, "Сначала нужно выйти на дежурство.");

    new slot;

    if(sscanf(params, "i", slot))
    {
        SendHelpMessage(playerid, "/ram [действие]");
        SendSyntaxMessage(playerid, "1 - Вскрыть отмычкой | 2 - Выбить | 3 - Взорвать с помощью C4 | 4 - Вскрыть дверь ТС ");
    }

    if(slot < 1 || slot > 4)                        return 1;
    if(slot < 4 && PlayerInfo[playerid][pRank] < 4)    return SendError(playerid, "Данный тип взлома доступен с 4 ранга.");
    if(p_temp[playerid][pRamType])                    return SendError(playerid, "Вы уже взламываете дверь.");

    new location[MAX_ZONE_NAME];
    GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

    if(slot == 4) {
        new vehicle = GetNearVehicle(playerid, 2.0);
        if(!vehicle)                              return SendError(playerid, "Рядом с Вами нет автомобиля.");

        if(VehicleInfo[vehicle][carLocked] == 0)  return SendError(playerid, "Замок ТС открыт.");
        if(VehicleInfo[vehicle][carOwnerID] == 0) return SendError(playerid, "Транспорт принадлежит госудраству.");

        cmd::server_ame(playerid, "взламывает дверной замок с помощью отмычки.");
        ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);

        p_temp[playerid][pRamType] = 1;
        p_temp[playerid][pRamTime] = 30;
        p_temp[playerid][pRamHouse] = -1;
        p_temp[playerid][pRamBiz] = -1;
        p_temp[playerid][pRamGarage] = -1;
        p_temp[playerid][pRamVeh] = vehicle;
        return 1;
    }

    new id = -1;
    if((id = GetNearOutsideHouse(playerid)) != -1)
    {
        if(!HouseInfo[id][hOwnerID])                                    return SendError(playerid, "Дом принадлежит госудраству.");
        if(!HouseInfo[id][hLocked] || HouseInfo[id][hDDoor])            return SendError(playerid, "Дверь уже открыта.");

        switch(slot)
        {
            case 1:
            {
                cmd::server_ame(playerid, "взламывает дверной замок с помощью отмычки.");
                ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);

                p_temp[playerid][pRamType] = slot;
                p_temp[playerid][pRamTime] = 30;
                p_temp[playerid][pRamHouse] = id;
                p_temp[playerid][pRamBiz] = -1;
                p_temp[playerid][pRamGarage] = -1;
                p_temp[playerid][pRamVeh] = -1;
            }
            case 2:
            {
                cmd::server_ame(playerid, "выбивает дверь с ноги.");
                ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,1,1,1);
                HouseInfo[id][hLocked] = 0;
                HouseInfo[id][hDDoor] = 1;
                Save_House(id);
                UpdateHouseDoor(id);
                GameTextForPlayer(playerid, "~w~ВЫ ~y~ВЫБИЛИ~w~ ДВЕРЬ", 1000, 1);
                InfoMSG(playerid, "НАЖМИТЕ ~y~\"F\"~w~ ИЛИ ВВЕДИТЕ ~y~/ENTER", 2);

                new query[128];
                format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] выбил дверь (/ram) дом [H_MYSQL: %i]", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), HouseInfo[id][hID]);
                insert_log(query, RAM_LOG, 5, PlayerInfo[playerid][pAccID], 0);
            }
            case 3:
            {
                cmd::server_ame(playerid, "устанавливает C4 на дверь.");
                OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
                p_temp[playerid][pRamObj] = CreateDynamicObject(1654, HouseInfo[id][hPosX], HouseInfo[id][hPosY], HouseInfo[id][hPosZ]-0.8, 0.0, 0.0, 90.0, HouseInfo[id][hPosInt], HouseInfo[id][hPosVW]);
                p_temp[playerid][pRamType] = slot;
                p_temp[playerid][pRamTime] = 10;
                p_temp[playerid][pRamHouse] = id;
                p_temp[playerid][pRamBiz] = -1;
                p_temp[playerid][pRamGarage] = -1;
                p_temp[playerid][pRamVeh] = -1;
            }
        }
        return 1;
    }

    else if((id = GetNearOutsideBiz(playerid)) != -1)
    {
        if(BizInfo[id][bizType] == BIZ_GAS_STATION || BizInfo[id][bizType] == BIZ_AUTOSALON || BizInfo[id][bizType] == BIZ_BOATSALON || BizInfo[id][bizType] == BIZ_FLYSALON || BizInfo[id][bizType] == BIZ_TUNING || BizInfo[id][bizType] == BIZ_ADVERT || BizInfo[id][bizType] == BIZ_LICENSE) return 1;
        if(!BizInfo[id][bizOwnerID])                            return SendError(playerid, "Бизнес принадлежит госудраству.");
        if(!BizInfo[id][bizLocked] || BizInfo[id][bizDDoor])    return SendError(playerid, "Дверь уже открыта.");

        switch(slot)
        {
            case 1:
            {
                cmd::server_ame(playerid, "взламывает дверной замок с помощью отмычки.");
                ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);
                p_temp[playerid][pRamType] = slot;
                p_temp[playerid][pRamTime] = 30;
                p_temp[playerid][pRamHouse] = -1;
                p_temp[playerid][pRamBiz] = id;
                p_temp[playerid][pRamGarage] = -1;
                p_temp[playerid][pRamVeh] = -1;
            }
            case 2:
            {
                cmd::server_ame(playerid, "выбивает дверь с ноги.");
                ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,1,1,1);
                BizInfo[id][bizLocked] = 0;
                BizInfo[id][bizDDoor] = 1;
                Save_Business(id);
                UpdateBusinessDoor(id);
                GameTextForPlayer(playerid, "~w~ВЫ ~y~ВЫБИЛИ~w~ ДВЕРЬ", 1000, 1);
                InfoMSG(playerid, "НАЖМИТЕ ~y~\"F\"~w~ ИЛИ ВВЕДИТЕ ~y~/ENTER", 2);

                new query[128];
                format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] выбил дверь (/ram) бизнес [B_MYSQL: %i]", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), BizInfo[id][bizID]);
                insert_log(query, RAM_LOG, 6, PlayerInfo[playerid][pAccID], 0);
            }
            case 3:
            {
                cmd::server_ame(playerid, "устанавливает C4 на дверь.");
                OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
                p_temp[playerid][pRamObj] = CreateDynamicObject(1654, BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ]-0.8, 0.0, 0.0, 90.0, BizInfo[id][bizPosVW], BizInfo[id][bizPosInt]);
                p_temp[playerid][pRamType] = slot;
                p_temp[playerid][pRamTime] = 10;
                p_temp[playerid][pRamHouse] = -1;
                p_temp[playerid][pRamBiz] = id;
                p_temp[playerid][pRamGarage] = -1;
                p_temp[playerid][pRamVeh] = -1;
            }
        }
        return 1;
    }

    else if((id = GetNearOutsideGarage(playerid)) != -1)
    {
        if(!GarageInfo[id][garageOwner])                                    return SendError(playerid, "Гараж принадлежит госудраству.");
        if(!GarageInfo[id][garageLocked] || GarageInfo[id][garageDDoor])    return SendError(playerid, "Дверь уже открыта.");

        switch(slot)
        {
            case 1:
            {
                cmd::server_ame(playerid, "взламывает дверной замок с помощью отмычки.");
                ApplyAnimation(playerid,"OTB","betslp_lkabt", 4.0, 1, 0, 0, 0, 0);
                p_temp[playerid][pRamType] = slot;
                p_temp[playerid][pRamTime] = 30;
                p_temp[playerid][pRamHouse] = -1;
                p_temp[playerid][pRamBiz] = -1;
                p_temp[playerid][pRamGarage] = id;
                p_temp[playerid][pRamVeh] = -1;
            }
            case 2:
            {
                cmd::server_ame(playerid, "выбивает дверь с ноги.");
                ApplyAnimation(playerid,"FIGHT_E","FightKick_B",4.1,0,1,1,1,1);
                GarageInfo[id][garageLocked] = 0;
                GarageInfo[id][garageDDoor] = 1;
                Save_Garage(id);
                UpdateGarageDoor(id);
                GameTextForPlayer(playerid, "~w~ВЫ ~y~ВЫБИЛИ~w~ ДВЕРЬ", 1000, 1);
                InfoMSG(playerid, "НАЖМИТЕ ~y~\"F\"~w~ ИЛИ ВВЕДИТЕ ~y~/ENTER", 2);

                new query[128];
                format(query, sizeof(query), "%s [MYSQL: %i | IP: %s] выбил дверь (/ram) гаража [B_MYSQL: %i]", GetName(playerid), PlayerInfo[playerid][pID], q_GetPlayerIP(playerid), GarageInfo[id][garageID]);
                insert_log(query, RAM_LOG, 6, PlayerInfo[playerid][pAccID], 0);
            }
            case 3:
            {
                cmd::server_ame(playerid, "устанавливает C4 на дверь.");
                OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
                p_temp[playerid][pRamObj] = CreateDynamicObject(1654, GarageInfo[id][garagePlayer_Enter][0], GarageInfo[id][garagePlayer_Enter][1], GarageInfo[id][garagePlayer_Enter][2]-0.8, 0.0, 0.0, 90.0, GarageInfo[id][garageEnterVW], GarageInfo[id][garageEnterInt]);
                p_temp[playerid][pRamType] = slot;
                p_temp[playerid][pRamTime] = 10;
                p_temp[playerid][pRamHouse] = -1;
                p_temp[playerid][pRamBiz] = id;
                p_temp[playerid][pRamGarage] = id;
                p_temp[playerid][pRamVeh] = -1;
            }
        }
        return 1;
    }
    else if(slot == 2) cmd::doorram(playerid, "");

    return 1;
}

CMD:frisktrunk(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid))    return 1;
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Сначала нужно выйти на дежурство.");

    new vehicle = GetNearVehicle(playerid, 4.0);
    if(vehicle == 0)                                                                                                                            return SendError(playerid, "Рядом с Вами нет ТС.");
    if(IsADontTrunk(vehicle) || IsAPlane(vehicle) || IsABiker(vehicle) || IsAHelicopter(vehicle) || IsABoat(vehicle) || IsABicycle(vehicle))    return SendError(playerid, "У этого транспорта нет багажника.");
    if(!IsPlayerInAnyVehicle(playerid) && VehicleInfo[vehicle][carTrunkLock] == 0)                                                                return SendError(playerid, "Багажник этого транспортного средства закрыт.");
    if(veh_info[vehicle][v_npoId] && veh_info[vehicle][v_npoId] != p_info[playerid][member])                                     return SendError(playerid, "Вы не можете обыскать это ТС.");

    if(!IsNearTrunk(vehicle, playerid, 2.0))     return SendError(playerid, "Вы не около багажника.");

    PrintVehInv(playerid, vehicle, 1);
    return 1;
}

CMD:friskgb(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return 1;
    if(p_info[playerid][fwork] == false)     return SendError(playerid, "Сначала нужно выйти на дежурство.");

    new vehicle = GetPlayerVehicleID(playerid);
    if(!vehicle && !IsPlayerInAnyVehicle(playerid))                                                                                                        return SendError(playerid, "Вы дожны быть в транспорте.");
    if(veh_info[vehicle][v_npoId] && veh_info[vehicle][v_npoId] != p_info[playerid][member] && VehicleInfo[vehicle][carOwnerID] != 0) return SendError(playerid, "Вы не можете обыскать это ТС.");

    PrintGBInv(playerid, vehicle, 1);
    return 1;
}

CMD:friskprop(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return 1;
    if(p_info[playerid][fwork] == false)     return SendError(playerid, "Сначала нужно выйти на дежурство.");

    new houseid;

    if((houseid = GetNearHouse(playerid)) == -1)                    return SendError(playerid, "Вы не рядом с домом.");
    if(HouseInfo[houseid][hOwnerID] == PlayerInfo[playerid][pID])    return SendError(playerid, "Данный дом принадлежит Вам.");
    if(!IsPlayerInsideHouse(playerid, houseid))                        return SendError(playerid, "Вы должны находиться в доме.");

    PrintHouseInv(playerid, houseid, 1);
    return 1;
}

CMD:frisk(playerid, params[])
{
    if(PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || p_temp[playerid][pTaserTime] || p_temp[playerid][pCuffed] || PhoneInfo[playerid][current_page] == PAGE_NOTIFICATION || PlayerInfo[playerid][pJailed] != 0)
        return SendError(playerid, "Вы не можете использовать данную функцию прямо сейчас.");

    new userid;

    if(sscanf(params, "u", userid))                                         return SendHelpMessage(playerid, "/frisk [ID/имя игрока]");
    if(!p_info[userid][loggedIn])                                             return SendError(playerid, "Игрок не в сети.");
    if(userid == playerid)                                                 return 1;
    if(!PlayerNearPlayer(3.0, playerid, userid))                         return SendNotNearPlayer(playerid);
    if(p_temp[userid][pFriskPlayer] == playerid)                             return SendError(playerid, "Вы уже предложили обыск игроку.");
    if(IsPlayerFractionPolice(playerid) && p_info[playerid][fwork] == false) return PrintInvEx(playerid, userid);

    SendWarningMessage(playerid, "Дождитесь пока игрок примет или отклонит Ваше предложение на обыск.");
    SendSyntaxMessage(userid, "Игрок %s хочет вас обыскать.",get_name(playerid));
    SendHelpMessage(userid, "Введите {ffc46a}/friskapprove{FFFFFF}, чтобы принять действие или {ffc46a}/cancelfrisk{FFFFFF}, чтобы отклонить предложение.");

    p_temp[userid][pFriskPlayer] = playerid;
    SetPVarInt(userid, #accept_time, timestamp + 30);
    return 1;
}

CMD:friskapprove(playerid, params[])
{
    if(p_temp[playerid][pFriskPlayer] == INVALID_PLAYER_ID)    return SendError(playerid, "Вам никто не предлагал провести обыск.");

    new userid = p_temp[playerid][pFriskPlayer];

    p_temp[playerid][pFriskPlayer] = INVALID_PLAYER_ID;

    if(!PlayerNearPlayer(3.0, playerid, userid))    return SendNotNearPlayer(playerid);

    SendSyntaxMessage(playerid, "Вы позволили игроку %s провести обыск над собой.",get_name(userid));

    PrintInvEx(playerid, userid);
    return 1;
}

CMD:cancelfrisk(playerid, params[])
{
    if(p_temp[playerid][pFriskPlayer] == INVALID_PLAYER_ID)    return SendError(playerid, "Вам никто не предлагал провести обыск.");

    new userid = p_temp[playerid][pFriskPlayer];

    p_temp[playerid][pFriskPlayer] = INVALID_PLAYER_ID;
    SendSyntaxMessage(playerid, "Вы отклонили предложение %s на проведение обыска.",GetNameWithMask(userid));
    SendSyntaxMessage(userid, "Игрок %s отклонил(-а) Ваше предложение на проведение обыска.",GetNameWithMask(playerid));
    return 1;
}

CMD:setnumber(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Вы должны быть полицейским.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!vehicleid || VehicleInfo[vehicleid][carFaction] != p_info[playerid][member])    return SendError(playerid, "Вы не во фракционном транспорте.");
    new number[24];
    format(number, sizeof(number), "%s", GetVehicleNumber());
    new query[128];
    mysql_format(con_bd, query, sizeof(query), "SELECT `number` FROM `vehicle` WHERE `v_number` = '%e'", number);
    mysql_tquery(con_bd, query, "PoliceSetPlate", "iis", playerid, vehicleid, number);
    return 1;
}

CMD:zond(playerid, params[])
{
    if(p_temp[playerid][pZond] != 0)        return SetPlayerZond(playerid, 0);
    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(!PlayerInfo[playerid][pSwatDuty])    return SendError(playerid, "Данная функция доступна S.W.A.T.");

    SetPlayerZond(playerid, 1);
    return 1;
}

CMD:flashbang(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(!PlayerInfo[playerid][pSwatDuty])    return SendError(playerid, "Данная функция доступна S.W.A.T.");

    new id = -1;

    if((id = GetNearOutsideBiz(playerid)) != -1 && (BizInfo[id][bizType] != BIZ_AUTOSALON && BizInfo[id][bizType] != BIZ_ADVERT && BizInfo[id][bizType] != BIZ_TUNING && BizInfo[id][bizType] != BIZ_LICENSE && BizInfo[id][bizType] != BIZ_BOATSALON && BizInfo[id][bizType] != BIZ_FLYSALON))
    {
        if(BizInfo[id][bizLocked])    return GameTextForPlayer(playerid, "~r~ЗАКРЫТО!", 2500, 1);

        SendFactionMessage(FACTION_POLICE, COLOR_POLICECHAT, "* %s %s использовал светошумовую гранату.", GetPlayerFractionRangName(playerid), get_name(playerid));
        cmd::me(playerid, "сняв с пояса забрасывает светошумовую гранату внутрь здания.");

        foreach(new i : Player)
        {
            if(!IsPlayerLogged(i) || !IsPlayerBizInside(i, id)) continue;

            SendSyntaxMessage(i, "Вы были ослеплены светошумовой гранатой.");
            GameTextForPlayer(i, "~r~!!! ВЫ БЫЛИ ОСЛЕПЛЕНЫ !!!~n~~n~~n~!!! ВЫ БЫЛИ ОСЛЕПЛЕНЫ !!!~n~~n~~n~!!! ВЫ БЫЛИ ОСЛЕПЛЕНЫ !!!", 12000, 3);
            SetPlayerWeather(i, 36);
            SetPlayerTime(i, 22, 0);
            StopPlayerAnims(i);
            FreezePlayer(i);
            SetPlayerDrunkLevel(i, 50000);
            p_temp[i][pFlashTime] = 15;
        }
        return 1;
    }
    if((id = GetNearOutsideHouse(playerid)) != -1)
    {
        if(HouseInfo[id][hLocked])    return GameTextForPlayer(playerid, "~r~ЗАКРЫТО!", 2500, 1);

        SendFactionMessage(FACTION_POLICE, COLOR_POLICECHAT, "* %s %s использовал светошумовую гранату.", GetPlayerFractionRangName(playerid), get_name(playerid));
        cmd::me(playerid, "сняв с пояса забрасывает светошумовую гранату внутрь здания.");
        foreach(new i : Player)
        {
            if(!IsPlayerLogged(i) || !IsPlayerInsideHouse(i, id)) continue;

            SendSyntaxMessage(i, "Вы были ослеплены светошумовой гранатой.");
            GameTextForPlayer(i, "~r~!!! YOU WERE FLASHBANGED !!!~n~~n~~n~!!! YOU WERE FLASHBANGED !!!~n~~n~~n~!!! YOU WERE FLASHBANGED !!!", 12000, 3);
            SetPlayerWeather(i, 36);
            SetPlayerTime(i, 22, 0);
            StopPlayerAnims(i);
            FreezePlayer(i);
            SetPlayerDrunkLevel(i, 50000);
            p_temp[i][pFlashTime] = 15;
        }
        return 1;
    }

    SendError(playerid, "Используйте у входа в дом/бизнес.");
    return 1;
}*/

CMD:callsign(playerid, params[])
{
    new faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)    return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве.");
    if(p_temp[playerid][pPatrol])
    {
        new id = p_temp[playerid][pPatrol]-1;

        p_temp[playerid][pPatrol] = 0;

        if(id < 0 || id >= MAX_PATROL || !PatrolInfo[GetPatrolID(playerid)][id][patrulExists])    return 1;

        if(PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == playerid)                                                                                             PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] = INVALID_PLAYER_ID;
        if(PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] == playerid)                                                                                             PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] = INVALID_PLAYER_ID;
        if(PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == INVALID_PLAYER_ID && PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] == INVALID_PLAYER_ID)    PatrolInfo[GetPatrolID(playerid)][id][patrulExists] = 0;

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[DISP] %s %s вышел из патруля под маркировкой %s", GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][id][patrulName]);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
        return 1;
    }
    if(isnull(params)) return SendInfo(playerid, "/callsign [маркировка]");
    for(new i; i != MAX_PATROL; i++)
    {
        if(!PatrolInfo[GetPatrolID(playerid)][i][patrulExists] || !strequals(params, PatrolInfo[GetPatrolID(playerid)][i][patrulName]))     continue;

        if(PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][0] != INVALID_PLAYER_ID && PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][1] != INVALID_PLAYER_ID)    return SendError(playerid, "Данный патруль уже скомплектован.");

        if(PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][0] == INVALID_PLAYER_ID)
            PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][0] = playerid;
        else
            PatrolInfo[GetPatrolID(playerid)][i][patrulOfficer][1] = playerid;

        p_temp[playerid][pPatrol] = i+1;

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[DISP] %s %s присоединился к патрулю под маркировкой %s", GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][i][patrulName]);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
        return 1;
    }

    new id = -1;
    for(new i; i != MAX_PATROL; i++)
    {
        if(PatrolInfo[GetPatrolID(playerid)][i][patrulExists]) continue;

        id = i;
        break;
    }

    if(id == -1) return SendError(playerid, "Достигнуто максимальное кол-во патрулей.");

    p_temp[playerid][pPatrol] = id+1;
    PatrolInfo[GetPatrolID(playerid)][id][patrulExists] = 1;
    format(PatrolInfo[GetPatrolID(playerid)][id][patrulName], 32, "%s", params);
    PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][0] = playerid;
    PatrolInfo[GetPatrolID(playerid)][id][patrulOfficer][1] = INVALID_PLAYER_ID;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[DISP] %s %s вышел в патруль под маркировкой %s", GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][id][patrulName]);
    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
    return 1;
}
/*
CMD:meg(playerid, params[])
{
    new vehicle = GetPlayerVehicleID(playerid);

    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским.");
    if(veh_info[vehicle][v_npoId] != p_info[playerid][member])                    return SendError(playerid, "Доступно только в транспорте LSPD/SASD.");


    new type;
    if(sscanf(params, "i", type))
    {
        new _mes[447] = "1. This is the Los Santos Police Department; Stay where you all are!\n2. This is Buzzard 1, we are taking ground fire!\n3. Four bangers in blue 4door heading back into South Central.\n";

        strcat(_mes, "4. Mayday, mayday! Buzzard 1 is going down!\n5. This is the LSPD do not, HEY! WHAT THE FUCK? TOO LOW, YOU'LL KILL US ALL!\n6. LSPD, stop right... are you insane? You'll kill us all!\n7. This is the Los Santos Police Department; Everybody stay where you are.");
        ShowPlayerDialog(playerid, MPCarVoice, DIALOG_STYLE_LIST, ""I"Мегафон", _mes, "Выбрать", "Отмена");
        return SendHelpMessage(playerid, "/meg [ид звука 1 - 7]");
    }
    MegaphoneSoundVoice(playerid, type);
    return 1;
}

CMD:revoke(playerid, params[])
{
    new userid, type[24], faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)                    return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)                return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(sscanf(params, "us[24]", userid, type))        return SendHelpMessage(playerid, "/revoke [ID/имя игрока] [carlic | flylic | weapons]");
    if(userid == playerid)                            return 1;
    if(!p_info[userid][loggedIn])                        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(4.0, playerid, userid))    return SendNotNearPlayer(playerid);

    if(strequals(type, "carlic"))
    {
        if(!p_info[userid][Lic][LIC_CAR])    return SendError(playerid, "У игрока нет водительского удостоверения.");

        new mes[128];
        format(mes, sizeof(mes), "забирает у %s водительское удостоверение.", GetNameWithMask(userid));
        cmd::me(playerid, mes);

        SendSyntaxMessage(userid, "Ваше водительское удостоверение было отобрано %s.", GetNameWithMask(playerid));
        p_info[userid][Lic][LIC_CAR] = 0;
        SQL_SetInteger("users", "carlic", 0, PlayerInfo[userid][pID]);
        return 1;
    }

    else if(strequals(type, "flylic"))
    {
        if(!p_info[userid][Lic][LIC_PLANE])    return SendError(playerid, "У игрока нет лицензии на полеты.");

        new mes[128];
        format(mes, sizeof(mes), "забирает у %s лицензию на полеты.", GetNameWithMask(userid));
        cmd::me(playerid, mes);

        SendSyntaxMessage(userid, "Ваша лицензия на полеты была отобрана %s.", GetNameWithMask(playerid));
        p_info[userid][Lic][LIC_PLANE] = 0;
        SQL_SetInteger("users", "flylic", 0, PlayerInfo[userid][pID]);
        return 1;
    }

    else if(strequals(type, "weapons"))
    {

        new count = -1;
        for(new i = 0; i < MAX_INV_SLOTS; i++)
        {
            if(playeritems[hz[playerid][i][pInvItem]][itemType] == ITEM_TYPE_WEAPON)
            {
                count = i;
                break;
            }
        }
        if(count == -1 && !PlayerInfo[playerid][pPlayerWeapon])    return SendError(playerid, "У игрока нет оружия");

        new mes[128];
        format(mes, sizeof(mes), "забирает у %s оружие.", get_name(userid));
        cmd::me(playerid, mes);

        SendWarningMessage(userid, "Всё Ваше оружие было отобрано %s.", get_name(playerid));
        ResetPlayerWeaponsEx(userid, 0);
        return 1;
    }
    else
    {
        SendHelpMessage(playerid, "/revoke [ID/имя игрока] [carlic | flylic | weapons]");
    }
    return 1;
}

CMD:detain(playerid, params[])
{
    new userid, faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD || !IsFactionDocs(faction))
        return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(sscanf(params, "u", userid))
        return SendHelpMessage(playerid, "/detain [ID/имя игрока]");
    if(userid == playerid)
        return 1;
    if(p_info[playerid][fwork] == false)
        return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(!IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Вы должны находиться в транспорте.");
    if(!p_info[userid][loggedIn])
        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(10.0, playerid, userid))
        return SendNotNearPlayer(playerid);
    if(!IsPlayerInAnyVehicle(userid) || veh_info[GetPlayerVehicleID(userid)][v_npoId] != p_info[playerid][member]) return SendError(playerid, "Игрок не находится в специальном транспорте.");

    new mes[128];

    if(!IsPlayerFreeze(userid))
    {
        format(mes, sizeof(mes), "блокирует все двери %s.", get_name(userid));
        Fix_TogglePlayerControllable(userid, 0);
    }
    else
    {
        format(mes, sizeof(mes), "%s разблокировал все двери.", get_name(userid));
        Fix_TogglePlayerControllable(userid, 1);
    }
    cmd::me(playerid, mes);
    return 1;
}
CMD:arrest(playerid, params[])
{
    new userid, time, info[128], faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)                        return SendError(playerid, "Вы должны быть полицейским.");
    if(sscanf(params, "uds[128]", userid, time, info))    return SendHelpMessage(playerid, "/arrest [ID/имя игрока] [время (минуты)] [причина]");
    if(p_info[playerid][fwork] == false)                    return SendError(playerid, "Вы должны находиться на дежурстве.");

    new arrestid = 0;

    if((arrestid = GetArrestID(playerid)) == 0)        return SendError(playerid, "Вы должны находиться у камер.");
    if(!p_info[userid][loggedIn])                        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))    return SendNotNearPlayer(playerid);
    if(userid == playerid)                            return SendError(playerid, "Вы не можете использовать данное действие на себе.");
    if(PlayerInfo[userid][pJailed])                    return SendError(playerid, "Игрок уже находится под арестом.");
    if(time < 1 || time > 60)                        return SendError(playerid, "Время ареста не может превышать от 1 до 60 минут.");

    Add_Arrest(playerid, userid, time);
    PlayerInfo[userid][pJailed] = arrestid;
    PlayerInfo[userid][pJailTime] = time * 60;
    PlayerInfo[userid][pArrested]++;
    SQL_SetInteger("users", "arrested", PlayerInfo[userid][pArrested], PlayerInfo[userid][pID]);
    AddCriminalRecord(userid, info, get_name(playerid), p_info[playerid][member], 1);

    PutPlayerInPrison(userid);
    SendError(userid, "Вы были арестованы. Время: %s минут.", ConvertNumber(time));
    p_temp[playerid][pPoliceJails]++;
    return 1;
}


CMD:prison(playerid, params[])
{
    return SendError(playerid, "Тюрьма пока отключена.");
    new userid, time, info[128], faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD || !IsFactionDocs(faction))        return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(sscanf(params, "uds[128]", userid, time, info))                return SendHelpMessage(playerid, "/prison [ID/имя игрока] [время(минуты)] [причина]");
    if(p_info[playerid][fwork] == false)                                return SendError(playerid, "Вы должны находится на дежурстве.");
    if(!PlayerToPoint(5.0, playerid, 241.6535,-315.2582,947.9460))    return SendError(playerid, "Вы не в тюрьме.");
    if(!p_info[userid][loggedIn])                                        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))                    return SendNotNearPlayer(playerid);
    if(time < 1 || time > 1000)                                        return SendError(playerid, "Время от 1 до 1000 минут.");
    if(userid == playerid)                                            return 1;

    PlayerInfo[userid][pPrisoned] = random(sizeof(prison_sadoc));
    PlayerInfo[userid][pJailed] = PRISON_JAIL;
    PlayerInfo[userid][pJailTime] = time * 60;
    PlayerInfo[userid][pIsolateTime] = 0;
    SendSyntaxMessage(userid, "Вы были посажены в тюрьму. Время: %s минут.", ConvertNumber(time));
    SendSyntaxMessage(userid, "Ваш номер заключённого - A%i(/myprisonnumber).", PlayerInfo[userid][pPrisoned]+100);
    return 1;
}

CMD:checknumber(playerid, params[])
{
    new faction = p_info[playerid][member];
    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)                        return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)                    return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)    return SendError(playerid, "Вы должны быть рядом с транспортным средством.");

    new vehicle;

    if((vehicle = GetNearVehicle(playerid, 2.5)) == 0)    return SendError(playerid, "Рядом с Вами нет транспортных средств.");

    if(VehicleInfo[vehicle][carRegistered] == 0)    SendSyntaxMessage(playerid, "Гос. номер транспортного средства %s не зарегистрировано.", GetVehicleName(vehicle));
    else                                            SendSyntaxMessage(playerid, "Гос. номер транспортного средства %s %s.", GetVehicleName(vehicle), VehicleInfo[vehicle][carPlate]);

    return 1;
}

CMD:cuff(playerid, params[])
{
    new userid, faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)                    return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(sscanf(params, "u", userid))                    return SendHelpMessage(playerid, "/cuff [ID/имя игрока]");
    if(p_info[playerid][fwork] == false)                return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(!p_info[userid][loggedIn])                        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))    return SendNotNearPlayer(playerid);
    if(userid == playerid)                            return 1;
    if(p_temp[userid][pCuffed])                        return SendError(playerid, "Игрок уже в наручниках.");
    if(p_temp[userid][pTaserTime])                    return SendError(playerid, "Игрок оглушен или без сознания.");

    GameTextForPlayer(userid, "~r~Cuffed", 2500, 3);
    p_temp[userid][pCuffed] = 1;
    SendSyntaxMessage(userid, "%s заключил(а) Вас в наручники.", GetNameWithMask(playerid));
    SendSyntaxMessage(playerid, "Вы заключили в наручники %s.", GetNameWithMask(userid));
    SetPlayerAttachedObject(userid, ATTACH_HANDS, 19418,6,0.003999,0.028000,-0.018000,-12.900005,0.000000,-65.100006,0.878000,1.890999,1.652001);
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_CUFFED);
    return 1;
}

CMD:uncuff(playerid, params[])
{
    new userid, faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)                    return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");
    if(sscanf(params, "u", userid))                    return SendHelpMessage(playerid, "/uncuff [ID/имя игрока]");
    if(p_info[playerid][fwork] == false)                return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(!p_info[userid][loggedIn])                        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))    return SendNotNearPlayer(playerid);
    if(userid == playerid)                            return 1;
    if(!p_temp[userid][pCuffed])                        return SendError(playerid, "Игрок не в наручниках.");

    p_temp[userid][pCuffed] = 0;
    SendSyntaxMessage(userid, "%s снял(а) с Вас наручники.", GetNameWithMask(playerid));
    SendSyntaxMessage(playerid, "Вы сняли наручники с %s.", GetNameWithMask(userid));
    RemovePlayerAttachedObject(userid, ATTACH_HANDS);
    SetPlayerSpecialAction(userid, SPECIAL_ACTION_NONE);
    return 1;
}

ALTX:chase("/clist", "/sitleader");
CMD:chase(playerid, params[])
{
    new faction = p_info[playerid][member];
    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)        return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)    return SendError(playerid, "Вы должны быть на дежурстве (/duty).");

    new userid;
    if(sscanf(params, "u", userid))                    return SendHelpMessage(playerid, "/chase [ID/имя игрока]");
    if(!p_info[userid][loggedIn])                        return SendError(playerid, "Игрок не в сети.");
    if(userid == playerid)                            return 1;
    if(GetPVarInt(playerid, #Chase_Time) > 1)        return SendError(playerid, "За %s [ID:%i] уже идёт погоня.", GetNameWithMask(userid), userid);
    if(!PlayerNearPlayer(15.0, playerid, userid))    return SendNotNearPlayer(playerid);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "(( HQ: %s %s начал погоню за %s [ID:%i]. ))", GetPlayerFractionRangName(playerid), get_name(playerid), GetNameWithMask(userid), userid);
    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

    StartChase(userid);
    return 1;
}

CMD:siren(playerid, params[])
{
    new faction = p_info[playerid][member], vehicle = GetPlayerVehicleID(playerid), model = GetVehicleModel(vehicle), siren_id;

    if(!IsFactionLegal(faction))                                            return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы/парамедиком/правительстве.");
    if(veh_info[vehicle][v_npoId] != p_info[playerid][member])    return SendError(playerid, "Вы должны быть в служебном транспорте.");
    if(sscanf(params, "i", siren_id))                                        return SendHelpMessage(playerid, "/siren [1-3]");
    if(siren_id < 1 || siren_id > 3)                                        return SendError(playerid, "Неправильный ID сирены: 1-3.");

    if(siren_id == 1)
    {
        if(IsValidDynamicObject(VehicleInfo[vehicle][carSiren][0]))
        {
            SendSyntaxMessage(playerid, "Сирена снята.");
            DestroyDynamicObject(VehicleInfo[vehicle][carSiren][0]);
            VehicleInfo[vehicle][carSiren][0] = INVALID_OBJECT_ID;
            return 1;
        }

        if(model != 560 && model != 541 && model != 525 && model != 426 && model != 579 && model != 415 && model != 554 && model != 546 && model != 566 && model != 561 && model != 547 && model != 482)
        {
            return SendError(playerid, "Сирену можно поставить только на Sultan/Bullet/Towtruck/Premier/Huntley/Cheetah/Yosemite/Intruder/Tahoma/Stratum/Primo/Burrito.");
        }

        VehicleInfo[vehicle][carSiren][0] = CreateDynamicObject((model != 525)?(18646):(19419), 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
        switch(model)
        {
            case 560: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.571924, 0.068632, 0.860007, 0.000000, 0.000000, -181.148086);
            case 541: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.442310, -0.091429, 0.670001, 0.000000, -2.299999, -178.874786);
            case 426: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.570416, -0.012622, 0.890005, 0.000000, 0.000000, -91.267646);
            case 525: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.0, -0.485, 1.36, 0.000000, 0.000000, 180.0);
            case 579: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.640568, -0.021741, 1.260003, 0.000000, 0.000000, -90.153976);
            case 415: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.424245, -0.241412, 0.640021, 3.000001, -3.499999, -181.499969);
            case 554: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.734659, 0.117240, 1.059349, -4.199999, 0.000000, -87.859664);
            case 546: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.591740, -0.153342, 0.870005, 0.000000, 0.000000, -269.351074);
            case 566: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.660138, 0.024635, 0.869999, 0.000000, 0.000000, -88.731002);
            case 561: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.428671, 0.080074, 0.850004, -2.799999, 0.000000, -88.665367);
            case 547: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.530513, 0.002143, 0.916606, -3.899999, 0.000000, -89.768531);
            case 482: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][0], vehicle, 0.515804, 0.702674, 0.950006, 0.000000, 0.000000, -92.038864);
        }

        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
        return SendSyntaxMessage(playerid, "Сирена установлена.");
    }

    else if(siren_id == 2)
    {
        if(IsValidDynamicObject(VehicleInfo[vehicle][carSiren][1]))
        {
            SendSyntaxMessage(playerid, "Сирена снята.");
            DestroyDynamicObject(VehicleInfo[vehicle][carSiren][1]);
            VehicleInfo[vehicle][carSiren][1] = INVALID_OBJECT_ID;
            return 1;
        }

        if(model != 560 && model != 426 && model != 579 && model != 566 && model != 561 && model != 547 && model != 546)
        {
            return SendError(playerid, "Сирену можно поставить только на Sultan/Premier/Huntley/Tahoma/Stratum/Primo/Intruder.");
        }

        VehicleInfo[vehicle][carSiren][1] = CreateDynamicObject(19419, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
        switch(model)
        {
            case 560: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.000000, -1.289999, 0.394999, 0.000000, 0.000000, 0.000000);
            case 426: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.000000, -1.669998, 0.349999, 0.000000, 0.000000, 0.000000);
            case 579: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.005192, -2.445963, 0.521951, 0.000000, 0.000000, -359.884796);
            case 566: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.009878, -1.681756, 0.400007, 0.000000, 0.000000, -0.010757);
            case 561: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, -0.004864, -2.317730, 0.249995, 0.000000, 0.000000, -0.192703);
            case 547: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, -0.001344, -1.571307, 0.400003, 0.000000, 0.000000, -0.468620);
            case 546: AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][1], vehicle, 0.014445, -1.771190, 0.340004, 0.000000, 0.000000, -359.851013);
        }
        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
        return SendSyntaxMessage(playerid, "Сирена установлена.");
    }

    else if(siren_id == 3)
    {
        if(IsValidDynamicObject(VehicleInfo[vehicle][carSiren][2]))
        {
            SendSyntaxMessage(playerid, "Сирена снята.");
            DestroyDynamicObject(VehicleInfo[vehicle][carSiren][2]);
            VehicleInfo[vehicle][carSiren][2] = INVALID_OBJECT_ID;
            DestroyDynamicObject(VehicleInfo[vehicle][carSiren][3]);
            VehicleInfo[vehicle][carSiren][3] = INVALID_OBJECT_ID;
            DestroyDynamicObject(VehicleInfo[vehicle][carSiren][4]);
            VehicleInfo[vehicle][carSiren][4] = INVALID_OBJECT_ID;
            return 1;
        }

        if(model != 541 && model != 415 && model != 560)    return SendError(playerid, "Сирену можно поставить только на Bullet/Cheetah/Sultan.");

        if(model == 541)
        {
            VehicleInfo[vehicle][carSiren][2] = CreateDynamicObject(19620, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][2], vehicle, 0.000000, 0.000000, 0.659999, 0.000000, 0.000000, -359.823394);
            VehicleInfo[vehicle][carSiren][3] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][3], vehicle, 0.006984, -2.280384, -0.190001, 0.000000, 0.000000, -359.824523);
            VehicleInfo[vehicle][carSiren][4] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][4], vehicle, -0.007443, 2.430286, -0.070001, 0.000000, 0.000000, -180.024566);
        }
        if(model == 415)
        {
            VehicleInfo[vehicle][carSiren][2] = CreateDynamicObject(19620, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][2], vehicle, 0.000475, -0.270263, 0.630008, 0.000000, 0.000000, -359.899139);
            VehicleInfo[vehicle][carSiren][3] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][3], vehicle, -0.005538, 2.660761, -0.210004, 0.000000, 0.000000, -180.099121);
            VehicleInfo[vehicle][carSiren][4] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][4], vehicle, 0.003255, -2.460503, -0.140003, 0.000000, 0.000000, 0.266403);
        }
        if(model == 560)
        {
            VehicleInfo[vehicle][carSiren][2] = CreateDynamicObject(19620, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][2], vehicle, -0.000927, 0.110103, 0.870014, 0.000000, 0.000000, -359.517333);
            VehicleInfo[vehicle][carSiren][3] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][3], vehicle, 0.004800, -2.370894, 0.105430, 0.000000, 0.000000, -359.912292);
            VehicleInfo[vehicle][carSiren][4] = CreateDynamicObject(19797, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1, -1, -1, 300.0);
            AttachDynamicObjectToVehicle(VehicleInfo[vehicle][carSiren][4], vehicle, -0.003252, 2.561954, 0.050001, 0.000000, 0.000000, -179.912200);
        }

        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
        return SendSyntaxMessage(playerid, "Сирена установлена.");
    }
    return 1;
}

CMD:licenseweapon(playerid, params[])
{
    new userid, price;

    if(sscanf(params, "ui", userid, price))            return SendHelpMessage(playerid, "/licenseweapon [ID/имя игрока] [стоимость]");
    if(IsPlayerFractionPolice(playerid))                return SendError(playerid, "Вы должны состоять в LSPD.");
    if(PlayerInfo[playerid][pAuthwep] != 1)            return SendError(playerid, "У Вас нет полномочий выдавать лицензии на оружие.");
    if(price < 1 || price > 10000)                    return SendError(playerid, "Стоимость от $1 до $10000.");
    if(!p_info[userid][loggedIn])                        return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))    return SendNotNearPlayer(playerid);
    if(PlayerInfo[userid][pWepLic] != 0)            return SendError(playerid, "У игрока уже есть лицензия на оружие.");
    if(p_temp[userid][pWepPlayer] == playerid)        return SendError(playerid, "Вы уже предложили игроку приобрести лицензию.");

    p_temp[userid][pWepPlayer] = playerid;
    p_temp[userid][pWepPrice] = price;
    SetPVarInt(userid, #accept_time, timestamp + 30);
    SendSyntaxMessage(userid, "%s %s предлагает Вам приобрести лицензию на оружие за $%i. (Нажмите Y чтобы купить лицензию)", GetPlayerFractionRangName(playerid), get_name(playerid), price);
    SendSyntaxMessage(playerid, "Вы предложили %s приобрести лицензию на оружие за $%i.", get_name(userid), price);
    return 1;
}

CMD:authweapon(playerid, params[])
{
    new userid;

    if(sscanf(params, "u", userid))                                        return SendHelpMessage(playerid, "/authweapon [ID/имя игрока]");
    if(IsPlayerFractionPolice(playerid))                            return SendError(playerid, "Вы должны состоять в LSPD.");
    if(!isLeader(playerid))                                                return SendError(playerid, "Вы не лидер фракции.");
    if(!p_info[userid][loggedIn])                                            return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))                        return SendNotNearPlayer(playerid);
    if(PlayerInfo[userid][pFaction] != p_info[playerid][member])    return SendError(playerid, "Игрок не состоит в Вашей организации.");

    if(PlayerInfo[userid][pAuthwep] == 0)
    {
        PlayerInfo[userid][pAuthwep] = 1;
        SendSyntaxMessage(userid, "%s %s выдал(а) Вам полномочия выдавать лицензии на оружие.", GetPlayerFractionRangName(playerid), get_name(playerid));
        SendSyntaxMessage(playerid, "Вы выдали полномочия выдавать лицензии на оружие %s.", get_name(userid));
        return 1;
    }

    PlayerInfo[userid][pAuthwep] = 0;
    SendSyntaxMessage(userid, "%s %s забрал(а) у Вас полномочия выдавать лицензии на оружие", GetPlayerFractionRangName(playerid), get_name(playerid));
    SendSyntaxMessage(playerid, "Вы забрали полномочия выдавать лицензии на оружие %s.", get_name(userid));
    return 1;
}

CMD:authswat(playerid, params[])
{
    new userid;

    if(sscanf(params, "u", userid))                                                            return SendHelpMessage(playerid, "/authswat [ID/имя игрока]");
    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским.");
    if(!isLeader(playerid))                                                                    return SendError(playerid, "Вы не лидер фракции.");
    if(!p_info[userid][loggedIn])                                                                return SendError(playerid, "Игрок не в сети.");
    if(!PlayerNearPlayer(3.0, playerid, userid))                                            return SendNotNearPlayer(playerid);
    if(PlayerInfo[userid][pFaction] != p_info[playerid][member])                        return SendError(playerid, "Игрок не состоит в Вашей организации.");

    if(PlayerInfo[userid][pSwat] == 0)
    {
        PlayerInfo[userid][pSwat] = 1;
        SendSyntaxMessage(userid, "%s %s выдал(а) полномочия сотрудника группы захвата S.W.A.T", GetPlayerFractionRangName(playerid), get_name(playerid));
        SendSyntaxMessage(playerid, "Вы выдали полномочия %s S.W.A.T.", get_name(userid));
        return 1;
    }

    PlayerInfo[userid][pSwat] = 0;
    SendSyntaxMessage(userid, "%s %s забрал(а) полномочия сотрудника группы захвата S.W.A.T", GetPlayerFractionRangName(playerid), get_name(playerid));
    SendSyntaxMessage(playerid, "Вы забрали полномочия %s S.W.A.T.", get_name(userid));
    return 1;
}

ALTX:rope("/br");
CMD:rope(playerid, params[])
{
    new faction = p_info[playerid][member], vehicle = GetPlayerVehicleID(playerid);

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD)            return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)        return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(!PlayerInfo[playerid][pSwatDuty])    return SendError(playerid, "Данная функция доступна S.W.A.T.");
    if(GetPVarInt(playerid, #SWATROPE))    return 1;
    if(IsPlayerInAnyVehicle(playerid))        return SendError(playerid, "Вы должны находиться в ветролете.");
    if(IsAHelicopter(vehicle))                return SendError(playerid, "Вы должны находиться в ветролете.");
    if(!GetPlayerVehicleSeat(playerid))    return SendError(playerid, "Вы должны быть на пассажирском сиденье.");

    OnPlayerCallRappelling(playerid);
    return 1;
}
*/

// IMPOUND COORDINATES (CHANGE HERE)
#define IMPOUNDX (-1209.9501)
#define IMPOUNDY (-1064.3761)
#define IMPOUNDZ (128.2656)

CMD:impound(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_PD) return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(veh_info[vehicleid][v_model] != 525) return SendError(playerid, "Вы должны находиться в эвакуаторе.");
    if(!IsTrailerAttachedToVehicle(vehicleid)) return SendError(playerid, "К эвакуатору ничего не прицеплено.");

    new trailer = GetVehicleTrailer(vehicleid);
    if(!veh_info[trailer][v_mysql_id]) return SendError(playerid, "Отправлять на штрафстоянку можно только личный транспорт.");
    if(!PlayerToPoint(10.0, playerid, IMPOUNDX, IMPOUNDY, IMPOUNDZ)) return SendError(playerid, "Вы слишком далеко от штраф-стоянки.");

    DetachTrailerFromVehicle(vehicleid);
    GetVehiclePos(trailer, veh_info[trailer][v_pos][0], veh_info[trailer][v_pos][1], veh_info[trailer][v_pos][2]);
    GetVehicleZAngle(trailer, veh_info[trailer][v_pos][3]);

    SendAccess(playerid, "%s отправлен на штрафстоянку.", GetVehicleName(trailer));
    SetVehicleParamsVEx(trailer, false, false, alarm, false, bonnet, boot, objective);
    veh_info[trailer][v_impound] = 1;
    SaveVehicle(trailer);
    foreach(new i : Player)
    {
        if(!p_info[i][loggedIn] || p_info[i][ID] != veh_info[trailer][v_owner_id]) continue;
        SendInfo(i, "Ваш %s был прикреплен и отправлен на штрафстоянку %s %s.", GetVehicleName(trailer), GetPlayerFractionRangName(playerid), get_name(playerid));
        break;
    }
    return 1;
}

CMD:tow(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_PD) return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false) return SendError(playerid, "Вы должны быть на дежурстве.");
    if(veh_info[vehicleid][v_model] != 525) return SendError(playerid, "Вы должны находиться в эвакуаторе.");
    if(IsTrailerAttachedToVehicle(vehicleid))
    {
        DetachTrailerFromVehicle(vehicleid);
        return SendError(playerid, "Ранее прицепленное транспортное средство было оцеплено.");
    }
    new target_vehicle;
    new Float:px, Float:py, Float:pz;
    GetPlayerPos(playerid, px, py, pz);
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (i != INVALID_VEHICLE_ID && veh_info[i][v_model] != 525)
		{
			if (GetVehicleDistanceFromPoint(i, px, py, pz) <= 5.0 && GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(i))
			{
				target_vehicle = i;
                break;
			}
		}
	}
    if(target_vehicle < 1) return SendError(playerid, "Данный транспорт должен находиться рядом с Вашим транспортом.");
    if(GetVehicleData(GetVehicleModelEx(target_vehicle), E_VD_TYPE) != VEHICLE_STATE_CAR) return SendError(playerid, "Данный транспорт нельзя зацепить.");

    AttachTrailerToVehicle(vehicleid, target_vehicle);
    SendAccess(playerid, "Вы зацепили %s. Используйте /tow - отцепить.", GetVehicleName(target_vehicle));
    return 1;
}
/*
CMD:apb(playerid, params[])
{
    new action[24], secoption[153];

    if(GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_PD)        return SendError(playerid, "Вы должны быть офицером полиции.");
    if(p_info[playerid][fwork] == false)    return SendError(playerid, "Вы должны быть на дежурстве (/duty).");

    if(sscanf(params, "s[24]S()[153]", action, secoption))
    {
        SendInfo(playerid, "/apb [действие]");
        SendInfo(playerid, "clear / show / list");
        return 1;
    }

    if(strequals(action, "list"))
    {
        new count;

        for(new i = 0; i != MAX_APBS; i++)
        {
            if(ApbInfo[i][apbOn] == 0) continue;

            if(strlen(ApbInfo[i][apbCharge]) > 64)    SendClientMessage(playerid, COLOR_LIGHTRED, "APB %i:{FFFFFF} %.64s ... (%s)", i, ApbInfo[i][apbCharge], ApbInfo[i][apbSuspect]);
            else                                    SendClientMessage(playerid, COLOR_LIGHTRED, "APB %i:{FFFFFF} %s (%s)", i, ApbInfo[i][apbCharge], ApbInfo[i][apbSuspect]);

            count++;
        }

        if(!count)    return SendError(playerid, "APB заметок не найдено.");

        return 1;
    }
    else if(strequals(action, "show"))
    {
        new number;

        if(sscanf(secoption, "i", number))    return SendInfo(playerid, "/apb show [номер APB]");
        if(!ApbInfo[number][apbOn])            return SendError(playerid, "APB заметка не найдена.");

        SendClientMessage(playerid, -1, "____________________________________");
        SendClientMessage(playerid, COLOR_LIGHTRED, "Подозреваемый:{FFFFFF} %s", ApbInfo[number][apbSuspect]);

        if(strlen(ApbInfo[number][apbCharge]) > 64)
        {
            SendClientMessage(playerid, COLOR_LIGHTRED, "Описание:{FFFFFF} %.64s ...", ApbInfo[number][apbCharge]);
            SendClientMessage(playerid, -1, "... %s", ApbInfo[number][apbCharge][64]);
        }
        else
        {
            SendClientMessage(playerid, COLOR_LIGHTRED, "Описание:{FFFFFF} %s", ApbInfo[number][apbCharge]);
        }

        SendClientMessage(playerid, COLOR_LIGHTRED, "Добавил:{FFFFFF} %s, %s.", ApbInfo[number][apbOfficer], GetFractionName(ApbInfo[number][apbFaction]));
        SendClientMessage(playerid, -1, "____________________________________");
    }
    else if(strequals(action, "clear"))
    {
        new number;

        if(sscanf(secoption, "i", number))    return SendInfo(playerid, "/apb clear [номер APB]");
        if(!ApbInfo[number][apbOn])            return SendError(playerid, "APB заметка не найдена.");

        SendAccess(playerid, "Вы очистили APB заметку номер %i.", number);

        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "* HQ: %s %s удалил APB заметку номер %i.", GetPlayerFractionRangName(playerid), get_name(playerid), number);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

        new query[128];
        mysql_format(con_bd, query, sizeof(query), "DELETE FROM `apbs` WHERE `id` = %i", ApbInfo[number][apbID]);
        mysql_tquery(con_bd, query);

        ApbInfo[number][apbOn] =
        ApbInfo[number][apbID] = 0;
    }
    return 1;
}
*/
/*
CMD:toll(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)                                                        return SendError(playerid, "Вы должны быть на дежурстве (/duty).");

    if(isnull(params))
    {
        SendInfo(playerid, "/toll [параметр]");
        SendAccess(playerid, COLOR_GRAD2, "close/open - Закрывает/Открывает все шлагбаумы.");
        //SCM(playerid, COLOR_GRAD2, "0 - Открывает/закрывает шлагбаумы у тоннеля Richman.");
        //SCM(playerid, COLOR_GRAD2, "0 - Открывает/закрывает шлагбаумы Flint County.");
        SendAccess(playerid, COLOR_GRAD2, "0 - Открывает/закрывает шлагбаумы автомагистрали в Las Venturas.");
        SendAccess(playerid, COLOR_GRAD2, "1 - Blueberry(правый мост) - открывает/закрывает шлагбаумы на правом мосту в Blueberry.");
        SendAccess(playerid, COLOR_GRAD2, "2 - Blueberry(левый мост) - открывает/закрывает шлагбаумы на левом мосту в Blueberry.");
        return 1;
    }

    if(L_a_RequestAllowedCop > timestamp)    return SendError(playerid, "Вам нужно подождать %i секунд.", L_a_RequestAllowedCop - timestamp);

    if(strequals(params, "open"))
    {
        if(PlayerInfo[playerid][pRank] < 10)    return SendError(playerid, "Данная функция доступна с 10 ранга.");

        for(new i; i != MAX_TOLLS; i++)
        {
            aTolls[i][E_tLocked] = 0;
        }

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "** HQ: %s %s открыл для въезда и выезда все шлагбаумы. **", GetPlayerFractionRangName(playerid), get_name(playerid));
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

        L_a_RequestAllowedCop = timestamp + TOLL_DELAY_COP;
        return 1;
    }
    else if(strequals(params, "close"))
    {
        if(PlayerInfo[playerid][pRank] < 10)    return SendError(playerid, "Данная функция доступна с 10 ранга.");

        for(new i; i != MAX_TOLLS; i++)
        {
            aTolls[i][E_tLocked] = 1;
            Toll_CloseToll(i);
        }

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "** HQ: %s %s закрыл для въезда и выезда все шлагбаумы. **", GetPlayerFractionRangName(playerid), get_name(playerid));
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

        L_a_RequestAllowedCop = timestamp + TOLL_DELAY_COP;
        return 1;
    }

    new id = strval(params);

    if(id < 0 || id > 4)                return SendHelpMessage(playerid, "/toll [номер шлагбаума]");
    if(PlayerInfo[playerid][pRank] < 4)    return SendError(playerid, "Данная функция доступна со 2 ранга.");

    if(!IsPlayerInRangeOfPoint(playerid, TOLL_OPEN_DISTANCE, toll_gate_pos[id][0], toll_gate_pos[id][1], toll_gate_pos[id][2]) && !IsPlayerInRangeOfPoint(playerid, TOLL_OPEN_DISTANCE, toll_gate_pos[id+1][0], toll_gate_pos[id+1][1], toll_gate_pos[id+1][2]))
    {
        return SendError(playerid, "Вы должны находиться возле этих шлагбаумов.");
    }

    new toll_name[3][28] = {"автомагистрали Las Venturas", "на правом мосту Blueberry", "на левом мосту Blueberry"};

    if(aTolls[id][E_tLocked] == 0)
    {
        aTolls[id][E_tLocked] = 1;
        Toll_CloseToll(id);
        aTolls[id+1][E_tLocked] = 1;
        Toll_CloseToll(id+1);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "** HQ: %s %s закрыл для въезда и выезда шлагбаумы %s. **", GetPlayerFractionRangName(playerid), get_name(playerid), toll_name[id]);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
    }
    else
    {
        aTolls[id][E_tLocked] = 0;
        aTolls[id+1][E_tLocked] = 0;
        //SendFactionMessage(FACTION_POLICE, COLOR_POLICECHAT, "** HQ: %s %s закрыл для въезда и выезда шлагбаумы %s. **", GetPlayerFractionRangName(playerid), get_name(playerid), toll_name[id]);
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "** HQ: %s %s открыл для въезда и выезда шлагбаумы %s. **", GetPlayerFractionRangName(playerid), get_name(playerid), toll_name[id]);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
    }

    L_a_RequestAllowedCop = timestamp + TOLL_DELAY_COP;
    return 1;
}

ALTX:government("/gov");
CMD:government(playerid, params[])
{
    if(PlayerInfo[playerid][pMutedTime] > 0)    return SendError(playerid, "Ваш локальный чат заблокирован системой.");
    if(isnull(params))                            return SendHelpMessage(playerid, "(/gov)ernment [сообщение]");

    new faction = p_info[playerid][member], rank = PlayerInfo[playerid][pRank];

    if(!faction || IsFactionLegal(faction))                        return SendError(playerid, "Вы не состоите в силовой структуре.");
    if(!isLeader(playerid) && rank != Factions[faction][fRanks]-1)    return SendError(playerid, "Доступно только лидеру.");
    if(PlayerInfo[playerid][pSettings] & togGov)                    return SendError(playerid, "Сначала включите показ правительственных новостей.");

    foreach(new i : Player)
    {
        if(!IsPlayerLogged(i) || (PlayerInfo[i][pSettings] & togGov))    continue;

        if(strlen(params) > MAXLEN)
        {
            new pos = MAXLEN;

            if(pos < MAXLEN-1) pos = MAXLEN;

            SendClientMessage(i, COLOR_LSPD, "[Объявление Правительства] %.*s ...", pos, params);
            SendClientMessage(i, COLOR_LSPD, "[Объявление Правительства] ... %s", params[pos]);
        }
        else
        {
            SendClientMessage(i, COLOR_LSPD, "[Объявление Правительства] %s", params);
        }
    }
    return 1;
}

CMD:duty(playerid, params[])
{
    new faction = p_info[playerid][member];

    if(!faction || !IsFactionLegal(faction))                                return 1;
    if(!IsPlayerAtUniform(playerid) && !IsPlayerAtSecondUniform(playerid))    return SendError(playerid, "Вы не в раздевалке/в служебном транспорте.");

    ShowPlayerDialog(playerid, DutyMenu, DIALOG_STYLE_LIST, ""I"Дежурство", ""I"[1]"W" Выйти на службу\n"I"[2]"W" Форма\n"I"[3]"W" Снаряжение\n"I"[4]"W" Обновить бронежилет\n"I"[5]"W" Обновить здоровье", "Выбрать", "Отмена");
    return 1;
}

CMD:color(playerid, params[])
{
    new faction = p_info[playerid][member];

    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)        return SendError(playerid, "Вы должны быть на дежурстве (/duty).");
    if(PlayerInfo[playerid][pRank] < 5)        return SendError(playerid, "Вам недоступна данная функция.");

    if(GetPlayerColor(playerid) != RemoveAlpha(Factions[faction][fColor]))
    {
        SetPlayerColor(playerid, RemoveAlpha(Factions[faction][fColor]));
        SendSyntaxMessage(playerid, "Вы изменили цвет ника.");
    }
    else
    {
        SetPlayerColor(playerid, TEAM_HIT_COLOR);
        SendSyntaxMessage(playerid, "Вы изменили цвет ника.");
    }
    return 1;
}

CMD:lift(playerid, params[])
{
    if(!IsPlayerInRangeOfPoint(playerid, 2.0, 2268.0640,2448.2449,3.5313) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2781.0559,-1056.2823,1028.4969) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2874.6665,-940.6707,1035.9259) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2872.8813,-1072.9934,1037.1782)) return 1;

    ShowPlayerDialog(playerid, LSPDElevator, DIALOG_STYLE_LIST, ""I"Лифт", ""I"[1]"W" Гараж\n"I"[2]"W" Первый этаж\n"I"[3]"W" Второй этаж\n"I"[4]"W" Спортивный зал", "Выбрать", "Отмена");
    return 1;
}

CMD:ane(playerid, params[])
{
    new
        vehicle = GetPlayerVehicleID(playerid),
        userid
    ;

    if(!IsPlayerFractionPolice(playerid))
        return SendError(playerid, "Вы должны быть полицейским.");
    if(veh_info[vehicle][v_npoId] != p_info[playerid][member] && !PlayerToPoint(5.0, playerid, 96.8945,-76.5486,1001.6760))
        return SendError(playerid, "Доступно только в полицейском участке или в транспорте LSPD/SASD.");
    if(sscanf(params, "i", userid))
        return SendHelpMessage(playerid, "/ane [номер вызова]");
    if(!p_info[userid][loggedIn] || p_temp[userid][pCallOn] != 1)
        return SendError(playerid, "Вызов под таким номером не найден.");

    if(p_temp[playerid][pPatrol])    SendFactionMessage(FACTION_POLICE, COLOR_LSPD, "* %s %s [%s] принял вызов по горячей линии. #%i.", GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][p_temp[playerid][pPatrol]-1][patrulName], userid);
    else                            SendFactionMessage(FACTION_POLICE, COLOR_LSPD, "* %s %s принял вызов по горячей линии. #%i.", GetPlayerFractionRangName(playerid), get_name(playerid), userid);

    Waypoint_Set(playerid, p_temp[userid][pCallPosX], p_temp[userid][pCallPosY], p_temp[userid][pCallPosZ], 3.0);
    p_temp[userid][pCallOn] = 0;

    p_temp[playerid][pPoliceCalls]++;
    return 1;
}

ALTX:spike("/sp");
CMD:spike(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским.");
    if(p_info[playerid][fwork] == false)                                                        return SendError(playerid, "Вы должны быть на дежурстве (/duty).");

    new option[16], secoption[128];

    if(sscanf(params, "s[16]S()[128]", option, secoption))
    {
        SendHelpMessage(playerid, "/spike [create / remove / remall]");
        return 1;
    }

    if(strequals(option, "create"))
    {
        if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)    return SendError(playerid, "Вы должны быть вне помещений.");
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)            return SendError(playerid, "Вы не должны находиться в транспорте.");

        new Float:x, Float:y, Float:z, Float:a, location[MAX_ZONE_NAME];

        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        if(CreateStrip(x, y, z, a) == -1)    return SendError(playerid, "Достигнуто максимальное кол-во шипов.");

        GetPlayer2DZone(playerid, location, MAX_ZONE_NAME);

        SendFactionMessage(FACTION_POLICE, COLOR_LSPD, "* HQ: %s %s установил шипы на дороге %s.", GetPlayerFractionRangName(playerid), get_name(playerid), location);
        return 1;
    }

    if(strequals(option, "remove"))
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)    return SendError(playerid, "Вы не должны находиться в транспорте.");

        for(new i = 0; i < MAX_SPIKE; i++)
        {
            if(!SpikeInfo[i][sCreated] || IsPlayerInRangeOfPoint(playerid, 4.0, SpikeInfo[i][sX], SpikeInfo[i][sY], SpikeInfo[i][sZ])) continue;

            SpikeInfo[i][sCreated] = 0;
            SpikeInfo[i][sX] =
            SpikeInfo[i][sY] =
            SpikeInfo[i][sZ] = 0.0;

            if(IsValidDynamicObject(SpikeInfo[i][sObject]))
            {
                DestroyDynamicObject(SpikeInfo[i][sObject]);
                SpikeInfo[i][sObject] = INVALID_OBJECT_ID;
            }

            SendSyntaxMessage(playerid, "Вы убрали шипы [ID: %i].", i);
            break;
        }
        return 1;
    }

    else if(strequals(option, "remall"))
    {
        for(new i = 0; i < MAX_SPIKE; i++)
        {
            if(!SpikeInfo[i][sCreated]) continue;

            SpikeInfo[i][sCreated] = 0;
            SpikeInfo[i][sX] =
            SpikeInfo[i][sY] =
            SpikeInfo[i][sZ] = 0.0;

            if(IsValidDynamicObject(SpikeInfo[i][sObject]))
            {
                DestroyDynamicObject(SpikeInfo[i][sObject]);
                SpikeInfo[i][sObject] = INVALID_OBJECT_ID;
            }
        }

        SendFactionMessage(FACTION_POLICE, COLOR_LSPD, "* HQ: Все шипы на дорогах были удалены %s %s", GetPlayerFractionRangName(playerid), get_name(playerid));
        return 1;
    }

    else
    {
        SendHelpMessage(playerid, "/spike [create / remove / remall]");
    }
    return 1;
}

CMD:prisonlist(playerid, params[])
{
    new faction = p_info[playerid][member];

    if(GetFactionCategory(faction) != FACTION_CATEGORY_PD )    return SendError(playerid, "Вы должны быть полицейским/сотрудником тюрьмы.");


    if(GetFactionCategory(faction) == FACTION_CATEGORY_PD)
    {
        SendClientMessage(playerid, COLOR_GREEN, "Список заключённых в участке:");

        foreach(new i : Player)
        {        //(PlayerInfo[i][pJailed] != LSPD_JAIL && PlayerInfo[i][pJailed] != PALOMINO_JAIL)
            if(!IsPlayerLogged(i) || PlayerInfo[i][pJailed] != PALOMINO_JAIL) continue;

            SendClientMessage(playerid, COLOR_GRAD2, "%s | Время заключения: %s сек.", get_name(i), ConvertNumber(PlayerInfo[i][pJailTime]));
        }
        return 1;
    }

    return 1;
}
*/

CMD:repaircam(playerid, params[])
{
    if(GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_PD &&
        GetFactionCategory(p_info[playerid][member]) != FACTION_CATEGORY_FBI) return SendError(playerid, "Вы должны быть полицейским.");

    new camid = GetNearestCamera(playerid, 10.0);
    if(camid == -1) return SendError(playerid, "Вы должны быть рядом с камерой видеонаблюдения.");
    if(!CCTVInfo[camid][tvBreak]) return SendError(playerid, "Эта камера не нуждается в починке.");

    SetCameraBreakState(camid, 0);
    SendAccess(playerid, "Вы починили камеру видеонаблюдения [ID: %i | %s].", camid, CCTVInfo[camid][tvName]);
    return 1;
}
alias:repaircam("/rcam");

CMD:su(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid) || p_info[playerid][rang] < 2)
        return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(p_info[playerid][jail_time] > 0)
        return SendError(playerid, "Вы находитесь в тюрьме.");
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /su [id игрока]");
    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");
    if(IsPlayerFractionPolice(params[0]) && p_info[playerid][member] != FBI_TEAM)
        return SendError(playerid, "Игрок состоит в гос. фракции.");
    if(p_info[params[0]][jail] > 0)
        return SendError(playerid, "Игрок находится в тюрьме.");
    if(p_info[params[0]][wanted] >= 6)
        return SendError(playerid, "Игрок имеет максимальный уровень розыска.");
    if(GetFractionWarehouse(p_info[playerid][member], fwMate) < 25)
        return SendError(playerid, "На складе недостаточно материалов.");

    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_SUSPECT_REASON; i++)
    {
        f(STRING_GLOBAL,"%s"I"[%d]"W" %s\n",STRING_GLOBAL, i+1, suspect_player[i][suspect_name_folder]);
    }
    ShowPlayerDialog(playerid,D_SUSPECT_MENU,DIALOG_STYLE_LIST, ""I"Выберите раздел",STRING_GLOBAL,"Выбрать","Закрыть");
    p_temp[playerid][p_listitem][5] = params[0];
    return 1;
}

CMD:break(playerid, params[])
{
    //if(SRV_ID != 0) return SendError(playerid, "Функция находиться на исправлении. Будет добавлено: 22-23 августа.");
    if(!IsPlayerFractionPolice(playerid)) return 1;
    if(GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_PD && p_info[playerid][rang] < 7) return SendError(playerid, "Вы не можете использовать эту команду.");
    if(p_info[playerid][member] == FBI_TEAM && p_info[playerid][rang] < 4) return SendError(playerid, "Вы не можете использовать эту команду.");
    if(IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return SendError(playerid, "Данную команду нельзя использовать в интерьере.");
    if(IsPlayerToSquare(playerid, 2118.8, -2741.6, 2887.8, -2147.6)) return SendError(playerid, "Здесь запрещено устанавливать ограждения.");
    if(GetPVarInt(playerid, "LoadBreak") > 0) return SendError(playerid, "Вы уже устанавливаете объект.");
    ShowPlayerListTD(playerid, LIST_TD_ID_BREAK);
    return 1;
}
alias:break("spike");
CMD:dbreak(playerid, params[])
{
    if(IsPlayerFractionPolice(playerid))
    {
        if((p_info[playerid][member] == POLICE_LS || p_info[playerid][member] == POLICE_SF || p_info[playerid][member] == POLICE_LV) && p_info[playerid][rang] <= 4) return SendError(playerid, "Вы не можете использовать эту команду.");
        if(p_info[playerid][member] == FBI_TEAM && p_info[playerid][rang] <= 2) return SendError(playerid, "Вы не можете использовать эту команду.");
        if(IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Вы находитесь в транспортном средстве.");
        if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Введите: /dbreak [id]");
        if(params[0] < 1 || params[0] > 10) return SendError(playerid, "ID должен быть от 1 до 10.");
        params[0]--;
        if(BreakObject[playerid][params[0]] > 0)
        {
            if(BreakAreas[playerid][params[0]] != 0) DestroyDynamicArea(BreakAreas[playerid][params[0]]);

            DestroyDynamicObject(BreakObject[playerid][params[0]]);
            Delete3DTextLabel(Break3DText[playerid][params[0]]);
            BreakObject[playerid][params[0]] = 0;
            BreakAreas[playerid][params[0]] = 0;
            SendAccess(playerid, "Вы удалили объект.");
        }
        else SendError(playerid, "Объект не найден.");
    }
    else SendError(playerid, "Вы не можете использовать эту команду.");
    return 1;
}

CMD:panic(playerid)
{
    if(!IsPlayerFractionPolice(playerid))
        return 1;
    if(!GetPVarInt(playerid, "CALL:SERVICES"))
    {
        new Float:pos[3];
        GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] запрашивает поддержку. Он сейчас в \"%s\", район \"%s\".(( Принять вызов: /to %d ))", get_name(playerid), playerid, gSAZonesCity[GetCityName(pos[0],pos[1])][SAZONE_NAME], gSAZones[GetZonaName(pos[0],pos[1])][SAZONE_NAME], playerid);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

        SetPVarInt(playerid, "CALL:SERVICES", 5);
        SendAccess(playerid, "Вы вызвали подкрепление.");
    }
    else 
    {
        DeletePVar(playerid, "CALL:SERVICES");

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] отменил запрос поддержки.", get_name(playerid), playerid);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

        foreach(new i: Player)
        {
            if(p_temp[i][panic_target_id] == playerid)
            {
                CancelPlayerGPS(i);
            }
        }
        SendAccess(playerid, "Вы отменили вызов подкрепления.");
    }
    return 1;
}
alias:panic("bk", "pc");

CMD:tazer(playerid, params[])
{
    new targetid;
    if(sscanf(params, "u", targetid)) return SendInfo(playerid, "Используйте: /tazer [id игрока]");
    if(IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(targetid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(!IsPlayerStream(8.0, playerid, targetid)) return SendError(playerid, "Вы слишком далеко от игрока.");
    if(p_info[targetid][p_afkTime] > 2) return SendError(playerid, "Данный игрок в AFK.");
    if(GetPlayerState(targetid) != PLAYER_STATE_ONFOOT) return SendError(playerid, "Игрок не на ногах.");
    if((!IsPlayerFractionPolice(playerid) && !army(playerid) && p_info[playerid][member] != MAYOR_LS && p_info[playerid][member] != PRISON)
    || p_info[playerid][rang] < 1 && p_info[playerid][member] != MAYOR_LS
    || p_info[playerid][fwork] == false
    || p_info[playerid][member] == MAYOR_LS && p_info[playerid][rang] > 2
    || p_info[playerid][member] == PRISON && p_info[playerid][rang] < 3) return true;

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "оглушил(-а) %s на 15 секунд", get_name(targetid));
    MeAction(playerid, STRING_GLOBAL);
    SetPlayerSpecialAction(targetid, SPECIAL_ACTION_HANDSUP);

    Fix_TogglePlayerControllable(targetid, 0);

    p_temp[targetid][UnFreezeFix] = 1;
    p_temp[targetid][UnFreezeTimerFix] = timestamp + 15;

    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        DoAction(playerid, "Электрошокер весит на поясном держателе.");
        MeAction(playerid, "протянув руку к поясу, сцепил оттуда \"Tazer-X-26\", затем перезарядил его");
        DoAction(playerid, "Произошла перезарядка оружия.");
        MeAction(playerid, "нацелившись на преступника - сделал выстрел в грудь и в ногу");
        DoAction(playerid, "Преступник был оглушен электрошокером.");
    }
    return true;
}

CMD:ctazer(playerid)
{
    if((!IsPlayerFractionPolice(playerid) && !army(playerid) && p_info[playerid][member] != MAYOR_LS && p_info[playerid][member] != PRISON)
        || p_info[playerid][rang] < 1 && p_info[playerid][member] != MAYOR_LS
        || p_info[playerid][fwork] == false
        || p_info[playerid][member] == MAYOR_LS && p_info[playerid][rang] > 2
        || p_info[playerid][member] == PRISON && p_info[playerid][rang] < 3) return true;
    
    new slot = WEAPON_Slot[WEAPON_DEAGLE];

    if(GetPVarInt(playerid, #CTAZER))
    {
        SendAccess(playerid, "Вы переключились на \"Deagle\".");

        f_GivePlayerWeapon(playerid, WEAPON_DEAGLE, GetPVarInt(playerid, #CTAZER)-1, false);
        DeletePVar(playerid, #CTAZER);

        if(!p_info[playerid][Ammo][slot]) return 1;

        if(p_info[playerid][p_settings][ROLEPLAY] == 1)
        {
            DoAction(playerid, "Электрошокер в руке.");
            MeAction(playerid, "убирает электрошокер на тактический пояс, затем вынимает из кобуры пистолет.");
            DoAction(playerid, "Пистолет в руке.");
        }
    }
    else
    {
        SetPVarInt(playerid, #CTAZER, p_info[playerid][Ammo][slot]+1);
        
        f_GivePlayerWeapon(playerid, WEAPON_SILENCED, 10, false);

        SendAccess(playerid, "Вам выдан \"Tazer\" с 10 зарядами.");

        if(p_info[playerid][p_settings][ROLEPLAY] == 1)
        {
            DoAction(playerid, "Электрошокер весит на тактическом поясе.");
            MeAction(playerid, "протянув руку к поясу, сцепил оттуда электрошокер.");
            DoAction(playerid, "Электрошокер в руке.");
        }
    }
    return true;
}

CMD:stroboscopes(playerid)
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Доступно только для PD/FBI.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsValidVehicle(vehicleid)) return 1;
    new vehicle_model = GetVehicleModelEx(vehicleid);
    if(GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_CAR)
    {
        if(veh_info[vehicleid][v_npoType] == NPO_FACTION &&
            (GetFactionCategory(veh_info[vehicleid][v_npoId]) == FACTION_CATEGORY_PD || GetFactionCategory(veh_info[vehicleid][v_npoId]) == FACTION_CATEGORY_FBI))
        {
            STRING_GLOBAL[0] = EOS;
            if(veh_info[vehicleid][v_strob_timer] != INVALID_TIMER_ID)
            {
                KillTimer(veh_info[vehicleid][v_strob_timer]);
                veh_info[vehicleid][v_strob_timer] = INVALID_TIMER_ID;

                GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
                UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);

                format(STRING_GLOBAL, sizeof(STRING_GLOBAL),"%s выключил(а) страбоскопы", get_name(playerid));
                distance_chat(playerid,10.0,0xDE92FFFF,STRING_GLOBAL);
            }
            else
            {
                veh_info[vehicleid][v_strob_timer] = SetTimerEx("VehicleStroboscopes", 300, true, "i", vehicleid);
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL),"%s выключил(а) страбоскопы", get_name(playerid));
                distance_chat(playerid,10.0,0xDE92FFFF,STRING_GLOBAL);
            }
        }
        else SendError(playerid, "Доступно только для транспорта PD/FBI.");
    }
    return 1;
}
alias:stroboscopes("strob", "strobes");

this::VehicleStroboscopes(vehicleid)
{
    veh_info[vehicleid][v_light] = 1;
    SetVehicleParamsVEx(vehicleid, veh_info[vehicleid][v_engine], veh_info[vehicleid][v_light], alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);
    veh_info[vehicleid][v_strob_status] = veh_info[vehicleid][v_strob_status] == 1 ? 4 : 1;
    GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
    UpdateVehicleDamageStatus(vehicleid, panels, doors, veh_info[vehicleid][v_strob_status], tires);
    return 1;
}

CMD:siren(playerid)
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Доступно только для PD/FBI.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsValidVehicle(vehicleid)) return 1;
    new vehicle_model = GetVehicleModelEx(vehicleid);
    if(GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_CAR)
    {
        if(veh_info[vehicleid][v_npoType] == NPO_FACTION &&
            (GetFactionCategory(veh_info[vehicleid][v_npoId]) == FACTION_CATEGORY_PD || GetFactionCategory(veh_info[vehicleid][v_npoId]) == FACTION_CATEGORY_FBI))
        {
            if(IsSupportVehicleInstallSiren(vehicleid, vehicle_model))
            {
                if(p_info[playerid][p_settings][ROLEPLAY] == 1)
                {
                    DoAction(playerid, "Мигалка в руке.");
                    MeAction(playerid, "протянув к крыше автомобиля, установил мигалку на крышу.");
                    DoAction(playerid, "Мигалка на крыше.");
                }
                SetVehicleObejcts(vehicleid, 18646);

                SendInfo(playerid, "Что бы снять маленьку мигалку введите: /unsiren");
            }
            else SendError(playerid, "Данный Т/С не поддерживает такую функцию или уже есть мигалка.");
        }
        else SendError(playerid, "Одевать можно только на автомобили PD/FBI.");
    }
    else SendError(playerid, "Одевать можно только на автомобили.");
    return 1;
}

IsSupportVehicleInstallSiren(vehicleid, vehicle_model)
{
    new specialVehs[] = {416,427,596,597,598,599};

    for(new i = sizeof(specialVehs)-1; i != -1; i--)
    {
        if(vehicle_model == specialVehs[i])
            return 0;
    }

    new sirenIDs[] = {19620, 19419, 19420, 11701, 18646};
    for(new j = MAX_VEHICLE_OBJECT_ATTACH-1; j != -1; j--)
    {
        if(veh_info[vehicleid][v_attach_object][j] == INVALID_OBJECT_ID) continue;
        for(new i = sizeof(sirenIDs)-1; i != -1; i--)
        {
            if(GetDynamicObjectModelID(veh_info[vehicleid][v_attach_object][j]) == sirenIDs[i])
                return 0;
        }
    }
    return 1;
}

CMD:unsiren(playerid)
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Доступно только для PD/FBI.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsValidVehicle(vehicleid)) return 1;
    new vehicle_model = GetVehicleModelEx(vehicleid);
    if(GetVehicleData(vehicle_model, E_VD_TYPE) != VEHICLE_STATE_CAR)
        return SendError(playerid, "Работает только на автомобилях.");
    if(veh_info[vehicleid][v_npoType] == NPO_FACTION &&
        (GetFactionCategory(veh_info[vehicleid][v_npoId]) == FACTION_CATEGORY_PD || GetFactionCategory(veh_info[vehicleid][v_npoId]) == FACTION_CATEGORY_FBI))
    {
        for(new i = MAX_VEHICLE_OBJECT_ATTACH-1; i != -1; i--)
        {
            if(veh_info[vehicleid][v_attach_object][i] != INVALID_OBJECT_ID && GetDynamicObjectModelID(veh_info[vehicleid][v_attach_object][i]) == 18646)
            {
                DestroyDynamicObject(veh_info[vehicleid][v_attach_object][i]);
                veh_info[vehicleid][v_attach_object][i] = INVALID_OBJECT_ID;
 
                if(p_info[playerid][p_settings][ROLEPLAY] == 1)
                {
                    DoAction(playerid, "Мигалка на крыше.");
                    MeAction(playerid, "протянув руку к крыше автомобиля, снял мигалку с крыши.");
                    DoAction(playerid, "Мигалка в руке.");
                }
                return 1;
            }
        }
        SendError(playerid, "На данный Т/С не установлена маленькая мигалка.");
    }
    else SendError(playerid, "Одевать можно только на автомобили PD/FBI.");
    return 1;
}

CMD:tipster(playerid, params[])
{
    new param[32];
    if(p_info[playerid][member] != FBI_TEAM) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(sscanf(params, "s[32]s()[64]", param, params))
    {
        SendInfo(playerid, "Используйте: /tipster [действие]");
        SendInfo(playerid, "GET - Взять жучок");
        SendInfo(playerid, "SET - Установить жучок");
        SendInfo(playerid, "REMOVE - Деактивировать жучок");
        SendInfo(playerid, "LISTEN - Начать или завершить прослушивание чата фракции");
        return true;
    }
    if(!strcmp(param, "get", true))
    {
        if(p_info[playerid][rang] < 6) return SendError(playerid, "Вы не можете пользоваться этой командой.");
        new vehicleid = GetPlayerVehicleID(playerid);
        if(veh_info[vehicleid][v_npoType] != NPO_FACTION || veh_info[vehicleid][v_npoId] != FBI_TEAM) return SendError(playerid, "Вы должны находиться в специализированном транспортном средстве.");
        if(p_info[playerid][tipster] > 0) return SendError(playerid, "У Вас уже есть жучок.");
        p_info[playerid][tipster] = 1;
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s [%d] взял жучок.", get_name(playerid), playerid);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
    }
    else if(!strcmp(param, "set", true))
    {
        new ammo;
        if(p_info[playerid][rang] < 6) return SendError(playerid, "Вы не можете пользоваться этой командой.");
        if(sscanf(params, "u", ammo)) return SendInfo(playerid, "Используйте: /tipster SET [id игрока]");
        if(!p_info[playerid][tipster]) return SendError(playerid, "У Вас нет жучка.");
        if(!IsPlayerStream(5.0, playerid, ammo) || pSpectateId[ammo] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
        if(tipsteron != -1) return SendError(playerid, "Жучок уже прикреплен.");
        if(!p_info[ammo][member]) return SendError(playerid, "Игрок не состоит во фракции.");
        p_info[playerid][tipster] = 0;
        tipsteron = p_info[ammo][member];
        tipsterplayer = ammo;

        SendAccess(playerid, "Вы активировали прослушивающее устройство.");

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s [%d] установил жучок на %s [%d]. Подключиться: /tipster listen", get_name(playerid), playerid, get_name(ammo), ammo);
        SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
    }
    else if(!strcmp(param, "remove", true))
    {
        if(p_info[playerid][rang] < 6) return SendError(playerid, "Вы не можете пользоваться этой командой.");
        if(tipsteron == -1) return SendError(playerid, "Вы не активировали прослушивающее устройство.");
        tipsteron = -1;
        tipsterplayer = -1;
        SendAccess(playerid, "Вы деактивировали прослушивающее устройство.");
    }
    else if(!strcmp(param, "listen", true))
    {
        if(tipsteron == -1) return SendError(playerid, "Вы не активировали прослушивающее устройство.");
        if(!p_info[playerid][tipsterlisten])
        {
            p_info[playerid][tipsterlisten] = 1;
            SendAccess(playerid, "Вы включили прослушивающее устройство.");
        }
        else
        {
            p_info[playerid][tipsterlisten] = 0;
            SendAccess(playerid, "Вы отключили прослушивающее устройство.");
        }
    }
    return true;
}

CMD:find(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid) || p_info[playerid][rang] < 3) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    else if(sscanf(params, "u", params[0])) 
    {
        if(p_temp[playerid][MapTypeID] == 2)
        {
            if(IsPlayerConnected(p_temp[playerid][MapTypeArgs])) 
                SendAccess(playerid, "Вы прекратили погоню за %s", get_name(p_temp[playerid][MapTypeArgs]));
            p_temp[playerid][MapTypeID] = 0;
            HideMapZone(playerid);
            return 1;
        }
        return SendInfo(playerid, "Используйте: /find [id игрока]");
    }
    else if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    else if(p_info[playerid][member] != FBI_TEAM && p_info[params[0]][wanted] < 1) return SendError(playerid, "Игрок не в розыске.");
    if(GetPlayerVirtualWorld(params[0]) != 0 || GetPlayerInterior(params[0]) != 0)
        return SendError(playerid, "Человек находится в помещении.");
    
    if(p_temp[playerid][MapTypeID] == 2)
    {
        if(IsPlayerConnected(p_temp[playerid][MapTypeArgs])) 
            SendAccess(playerid, "Вы прекратили погоню за %s", get_name(p_temp[playerid][MapTypeArgs]));
        p_temp[playerid][MapTypeID] = 0;
        HideMapZone(playerid);
        return 1;
    }

    if(p_temp[playerid][MapTypeID] != 0)
        return SendError(playerid, "У вас уже отмечена какая-то зона карте, подождите.");
    
    p_temp[playerid][MapTypeID] = 2;
    p_temp[playerid][MapTypeArgs] = params[0];

    SendAccess(playerid, "На карте отмечена зона где был замечен в последний раз %s [%d].", get_name(params[0]), params[0]);
    SendInfo(playerid, "Когда игрок попадет в поле вашего зрения, начните погоню за ним: /z %d", params[0]);

    CreatePoliceMapZone(playerid);

    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        DoAction(playerid, "Планшет весит на поясе и он отключен.");
        MeAction(playerid, "вытащил из пояса планшет, затем активировал его");
        DoAction(playerid, "Планшет активирован.");
        MeAction(playerid, "зашел в базу данных Министерства, после ввел данные в базу о нарушителе");
        MeAction(playerid, "получив координаты нарушителя, закрыл базу");
        DoAction(playerid, "Данные были введены и сохранены.");
    }
    return 1;
}

CreatePoliceMapZone(playerid)
{
    new Float:POS[3];
    GetPlayerPos(p_temp[playerid][MapTypeArgs], POS[0], POS[1], POS[2]);

    new iWidth = 250,
        iHeight = 250,
        radiusmap = 50,
        Float:factormap = 0.1,
        Float:position_width,
        Float:position_latitude;

    position_width = iWidth-(iWidth/radiusmap*factormap)+POS[0];
    position_latitude = iHeight-(iHeight/radiusmap*factormap)+POS[1];

    p_temp[playerid][MapTypeZone] = GangZoneCreate(POS[0]-radiusmap, POS[1]-radiusmap, position_width, position_latitude);
    GangZoneShowForPlayer(playerid, p_temp[playerid][MapTypeZone], 0xFFFFFF65);
    GangZoneFlashForPlayer(playerid, p_temp[playerid][MapTypeZone], 0x00000065);

    p_temp[playerid][MapTypeTime] = 20;
}

CMD:spy(playerid, params[])
{
    if(p_info[playerid][member] != FBI_TEAM || p_info[playerid][fwork] == false) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(p_temp[playerid][BeingInSpace] == true || p_temp[playerid][SpaceFlightStatus] == true) return SendError(playerid, "Нельзя маскироваться в космосе.");
    if(p_info[playerid][rang] < 4) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(GetPVarInt(playerid,"spy_fbi"))
    {
        SendAccess(playerid, "Вы сняли маскировку.");
        SetPlayerSkin(playerid, p_info[playerid][fskin]);
        SetPlayerColor(playerid, fraction_color[p_info[playerid][member]]);
        DeletePVar(playerid,"spy_fbi");
        p_temp[playerid][SpyStatus] = -1;
        p_temp[playerid][SpyRang] = 0;

        if(p_info[playerid][p_settings][ROLEPLAY] == 1)
        {
            DoAction(playerid, "Сумка с формой в правой руке.");
            MeAction(playerid, "осмотрев содержимое сумки вытащил из нее нужную форму, после чего переоделся");
        }
        return 1;
    }

    STRING_GLOBAL[0] = EOS;
    for (new i; i < MAX_FRACTIONS; i ++)
    {
        if(i != MAX_FRACTIONS-1) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"%s[%i]  %s\n", STRING_GLOBAL, i+1, GetFractionName(i));
        else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"%s[%i]  %s\n\n\nВведите ID фракции, ID ранга чтобы надеть нужную маскировку!", STRING_GLOBAL, i+1, GetFractionName(i));
    }
    ShowPlayerDialog(playerid, D_FBI_SPY, DIALOG_STYLE_INPUT, ""I"Выберите фракцию", STRING_GLOBAL, "Выбрать", "Закрыть");
    return 1;
}

CMD:addtime(playerid, params[])
{
    if((!IsPlayerFractionPolice(playerid) && p_info[playerid][member] != PRISON) || p_info[playerid][rang] < 5) return 1;
    if(sscanf(params, "ui", params[0], params[1])) return SendInfo(playerid, "Используйте: /addtime [id игрока] [время]");
    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid) return SendError(playerid, "Игрок не найден.");
    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(!p_info[params[0]][jail_time] && !p_info[params[0]][jail]) return SendError(playerid, "Игрок не в тюрьме.");
    if(p_info[params[0]][jail] == 6) return 1;
    if(!(1 <= params[1] <= 30)) return SendError(playerid, "Время должно быть не менее 1 и не более 30.");
    if(p_info[params[0]][jail_time]+params[1] > 3600) return SendError(playerid, "У игрока максимальный срок.");
    switch(p_info[params[0]][p_vip])
    {
        case 1: p_info[params[0]][jail_time] += ((params[1] * 60) / 100) * 90;
        case 2: p_info[params[0]][jail_time] += ((params[1] * 60) / 100) * 80;
        case 3: p_info[params[0]][jail_time] += ((params[1] * 60) / 100) * 70;
        default: p_info[params[0]][jail_time] += params[1]*60;
    }
    SendAccess(playerid, "Вы добавили %s [%d] +%d минут времени к заключению.", get_name(params[0]), params[0], params[1]);
    SendInfo(params[0], "%s [%d] +%d минут времени к заключению.", get_name(playerid), playerid, params[1]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] добавил %s [%d] +%d минут времени к заключению.", get_name(playerid), playerid, get_name(params[0]), params[0], params[1]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);
    return 1;
}

CMD:unkpz(playerid, params[])
{
    if((!IsPlayerFractionPolice(playerid) && p_info[playerid][member] != PRISON) || p_info[playerid][rang] < 8) return true;
    else if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /unkpz [id игрока]");
    else if(!IsPlayerConnected(params[0])) return SendError(playerid, "Игрок не найден.");
    else if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    else if(!p_info[params[0]][jail_time] && !p_info[params[0]][jail]) return SendError(playerid, "Игрок не в тюрьме.");
    else if(p_info[params[0]][jail] == 6) return 1;

    SendAccess(playerid, "Вы выпустили %s [%d] из тюрьмы.", get_name(params[0]), params[0]);
    SendInfo(params[0], "%s [%d] выпустил Вас из тюрьмы.", get_name(playerid), playerid);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] выпустил %s [%d] из тюрьмы.", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    p_info[params[0]][jail_time] = 1;

    p_info[playerid][fracdata][2]++;
    SaveFracData(playerid);

    CheckPlayerMission(playerid, POLICE_UNKPZ);

    UpdateFamilyLevel(playerid);

    p_info[playerid][ftop_unkpz]++;
    MysqlUpdatePlayerInt(playerid, "ftop_unkpz", p_info[playerid][ftop_unkpz]);

    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        DoAction(playerid, "Камера закрыта.");
        DoAction(playerid, "Ключ от камеры лежит в кармане.");
        MeAction(playerid, "движением правой руки вытащил из кармана ключ от камеры...");
        MeAction(playerid, "...после чего протянул правую руку к замку, а затем повернул ключ...");
        MeAction(playerid, "...на 360 градусов тем самым открыв камеру и освободив человека");
    }
    return 1;
}

CMD:udo(playerid, params[])
{
    if((!IsPlayerFractionPolice(playerid) && !army(playerid) && p_info[playerid][member] != PRISON && p_info[playerid][member] != RADIO_LS && p_info[playerid][member] != RADIO_SF && p_info[playerid][member] != RADIO_LV) || p_info[playerid][fwork] != true) return 1;
    else if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /udo [id игрока]");
    else if(!IsPlayerConnected(params[0])) return SendError(playerid, "Игрок не найден.");
    else if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    else if(GetPVarInt(params[0], "BoneStol_ID")) return 1;

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""W"Вы хотите предложить "I"%s "W"посмотреть Ваше удостоверение.", get_name(params[0]));
    ShowPlayerDialog(playerid, D_OFFER_PLAYER, DIALOG_STYLE_MSGBOX, ""I"Удостоверение", STRING_GLOBAL, "Далее", "Отмена");
    SetOfferData(playerid, params[0], OFFER_ID_SHOW_CERTIFICATE);
    return 1;
}

CMD:clearall(playerid, params[])
{
    if(p_info[playerid][admin] >= 4) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    foreach(new i: Player)
    {
        if(!p_info[i][loggedIn]) continue;
        SetPlayerWantedLevel(i,0);
        p_info[i][wanted] = 0;
    }
    return 1;
}

CMD:arrest(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid))
        return SendError(playerid, "Вы не можете пользоваться этой командой.");

    if(sscanf(params, "u", params[0]))
        return SendInfo(playerid, "Используйте: /arrest [id игрока]");

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(params[0] == playerid)
        return SendError(playerid, "Вы ввели свой ID.");

    if(p_info[params[0]][wanted] < 1)
        return SendError(playerid, "Игрок не в розыске.");
    new arrest_id = arrest(playerid);
    if(arrest_id == -1)
        return SendError(playerid, "Вы слишком далеко от места ареста.");
    if(arrest_id != arrest(params[0]))
        return SendError(playerid, "Игрок слишком далеко от места ареста.");
    if(GetPlayerState(params[0]) == PLAYER_STATE_SPECTATING)
        return SendError(playerid, "Игрок слишком далеко от места ареста.");
    if(p_info[params[0]][p_afkTime] > 2)
        return SendError(playerid, "Данный игрок в AFK.");

    PlayerPlaySound(params[0], 17004, 0.0, 0.0, 0.0);

    SendInfo(playerid, "Вы арестовали %s [%d] на %s.", get_name(params[0]), params[0], ConvertTime(GetPlayerWantedLevel(params[0])*600, 1));
    SendInfo(params[0], "%s [%d] арестовал Вас на %s.", get_name(playerid), playerid, ConvertTime(GetPlayerWantedLevel(params[0])*600, 1));

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s [%d] арестовал %s [%d] на %s.", get_name(playerid), playerid, get_name(params[0]), params[0], ConvertTime(GetPlayerWantedLevel(params[0])*600, 1));
    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

    ResetPlayerWeapons(params[0]);

    new list_percent[3] = {90, 80, 70}, vip_idx = p_info[params[0]][p_vip];
    if(vip_idx) p_info[params[0]][jail_time] = ((600 * p_info[params[0]][wanted]) / 100) * list_percent[vip_idx - 1];
    else p_info[params[0]][jail_time] = 600 * p_info[params[0]][wanted];

    if(arrest_id == 1)
    {
        SetPlayerInterior(params[0], 1);
        SetPlayerVirtualWorld(params[0], 1);
        switch(random(5))
        {
            case 0: SetPlayerPos(params[0], 2594.8792,2120.9707,1048.2335), SetPlayerFacingAngle(params[0], 269.1924);
            case 1: SetPlayerPos(params[0], 2594.5432,2124.9297,1048.2335), SetPlayerFacingAngle(params[0], 267.9159);
            case 2: SetPlayerPos(params[0], 2594.8469,2128.9121,1048.2335), SetPlayerFacingAngle(params[0], 269.5059);
            case 3: SetPlayerPos(params[0], 2594.8542,2132.9133,1048.2335), SetPlayerFacingAngle(params[0], 268.2526);
            case 4: SetPlayerPos(params[0], 2598.8616,2136.0291,1048.2335), SetPlayerFacingAngle(params[0], 177.6983);
        }
        p_info[params[0]][jail] = 1;
    }
    if(arrest_id == 2)
    {
        SetPlayerInterior(params[0], 1);
        SetPlayerVirtualWorld(params[0], 2);
        switch(random(5))
        {
            case 0: SetPlayerPos(params[0], 2594.8792,2120.9707,1048.2335), SetPlayerFacingAngle(params[0], 269.1924);
            case 1: SetPlayerPos(params[0], 2594.5432,2124.9297,1048.2335), SetPlayerFacingAngle(params[0], 267.9159);
            case 2: SetPlayerPos(params[0], 2594.8469,2128.9121,1048.2335), SetPlayerFacingAngle(params[0], 269.5059);
            case 3: SetPlayerPos(params[0], 2594.8542,2132.9133,1048.2335), SetPlayerFacingAngle(params[0], 268.2526);
            case 4: SetPlayerPos(params[0], 2598.8616,2136.0291,1048.2335), SetPlayerFacingAngle(params[0], 177.6983);
        }
        p_info[params[0]][jail] = 2;
    }
    if(arrest_id == 3)
    {
        SetPlayerInterior(params[0], 1);
        SetPlayerVirtualWorld(params[0], 3);
        switch(random(5))
        {
            case 0: SetPlayerPos(params[0], 2594.8792,2120.9707,1048.2335), SetPlayerFacingAngle(params[0], 269.1924);
            case 1: SetPlayerPos(params[0], 2594.5432,2124.9297,1048.2335), SetPlayerFacingAngle(params[0], 267.9159);
            case 2: SetPlayerPos(params[0], 2594.8469,2128.9121,1048.2335), SetPlayerFacingAngle(params[0], 269.5059);
            case 3: SetPlayerPos(params[0], 2594.8542,2132.9133,1048.2335), SetPlayerFacingAngle(params[0], 268.2526);
            case 4: SetPlayerPos(params[0], 2598.8616,2136.0291,1048.2335), SetPlayerFacingAngle(params[0], 177.6983);
        }
        p_info[params[0]][jail] = 3;
    }
    if(arrest_id == 4)
    {
        SetPlayerInterior(params[0], 1);
        SetPlayerVirtualWorld(params[0], 4);
        switch(random(5))
        {
            case 0: SetPlayerPos(params[0], 2594.8792,2120.9707,1048.2335), SetPlayerFacingAngle(params[0], 269.1924);
            case 1: SetPlayerPos(params[0], 2594.5432,2124.9297,1048.2335), SetPlayerFacingAngle(params[0], 267.9159);
            case 2: SetPlayerPos(params[0], 2594.8469,2128.9121,1048.2335), SetPlayerFacingAngle(params[0], 269.5059);
            case 3: SetPlayerPos(params[0], 2594.8542,2132.9133,1048.2335), SetPlayerFacingAngle(params[0], 268.2526);
            case 4: SetPlayerPos(params[0], 2598.8616,2136.0291,1048.2335), SetPlayerFacingAngle(params[0], 177.6983);
        }
        p_info[params[0]][jail] = 4;
    }

    if(p_info[params[0]][jail_time] > 1200) p_info[params[0]][jail] = 5;

    save_player(params[0]);

    p_info[params[0]][wanted] = 0;
    SetPlayerWantedLevel(params[0], p_info[params[0]][wanted]);

    SendInfo(params[0], "Информация о сроке: /time");

    DeletePVar(params[0],"PlayerCuffed");
    SetPlayerCuffed(params[0], false);
    Fix_TogglePlayerControllable(params[0], 1);
    SetPlayerWantedLevel(params[0], 0);

    p_info[playerid][fracdata][1]++;
    SaveFracData(playerid);

    CheckPlayerMission(playerid, POLICE_ARREST);

    UpdateFamilyLevel(playerid);

    p_info[playerid][ftop_arrest]++;
    MysqlUpdatePlayerInt(playerid, "ftop_arrest", p_info[playerid][ftop_arrest]);

    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        DoAction(playerid, "На левом плече весит рация.");
        MeAction(playerid, "протянув руку к плечу, нажал на кнопку рации, затем начал диктовать данные о преступнике");
        DoAction(playerid, "Данные были переданы диспетчеру.");
        MeAction(playerid, "нажав на кнопку, перестал говорить в рацию, затем вытащил из пояса планшет, активировал его");
        DoAction(playerid, "Планшет активирован.");
        MeAction(playerid, "зашел в базу данных Министерства, после ввел данные в базу о нарушителе, закрыл базу");
        DoAction(playerid, "Данные были введены и сохранены.");
        DoAction(playerid, "Из департамента вышло двое офицеров, которые и забрали с собой задерженного.");
    }
    return 1;
}

arrest(playerid)
{
    if(playerid == INVALID_PLAYER_ID) return -1;
    if(IsPlayerInRangeOfPoint(playerid, 10.0, 1600.7494,-1415.6863,2007.1520) || IsPlayerInRangeOfPoint(playerid, 25.0, 2599.2146,2126.8960,1048.2335) && GetPlayerVirtualWorld(playerid) == 1) return 1;
    else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1589.6727,716.3749,-5.2422) || IsPlayerInRangeOfPoint(playerid, 25.0, 2599.2146,2126.8960,1048.2335) && GetPlayerVirtualWorld(playerid) == 2) return 2;
    else if(IsPlayerInRangeOfPoint(playerid, 10.0, 2282.3247,2430.0518,3.2734) || IsPlayerInRangeOfPoint(playerid, 25.0, 2599.2146,2126.8960,1048.2335) && GetPlayerVirtualWorld(playerid) == 3) return 3;
    else if(IsPlayerInRangeOfPoint(playerid, 10.0, 634.0763,-571.7414,16.3359) || IsPlayerInRangeOfPoint(playerid, 25.0, 2599.2146,2126.8960,1048.2335) && GetPlayerVirtualWorld(playerid) == 4) return 4;
    return -1;
}

CMD:z(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid) || p_info[playerid][rang] < 2)
        return SendError(playerid, "Вы не можете пользоваться этой командой.");

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /z [id игрока]");

    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!IsPlayerStreamedIn(params[0], playerid))
        return SendError(playerid, "Игрок находится вне поля Вашего зрения.");

    if(p_info[params[0]][wanted] < 1)
        return SendError(playerid, "Игрок не в розыске.");

    if(p_temp[params[0]][chase_followerId] != INVALID_PLAYER_ID)
        return SendError(playerid, "Полиция уже ведет погоню за данным игроком.");

    if(p_temp[playerid][chase_targetId] != INVALID_PLAYER_ID)
    {
        new chase_target = p_temp[playerid][chase_targetId];
        if(chase_target == params[0])
            return SendError(playerid, "Вы уже ведете погоню за данным игроком.");

        p_temp[params[0]][chase_followerId] = INVALID_PLAYER_ID;

        SendInfo(chase_target, "Полицейский закончил погоню за Вами.");
        SendAccess(playerid, "Вы закончили погоню за %s [%d].", get_name(chase_target), chase_target);

        p_temp[playerid][chase_targetId] = INVALID_PLAYER_ID;
        DisablePlayerCheckpoint(playerid);
    }

    p_temp[playerid][chase_targetId] = params[0];

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s [%d] начал погоню за %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendFractionMessage(POLICE_LS, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(POLICE_SF, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(POLICE_LV, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(POLICE_RC, 0x33CC66FF, STRING_GLOBAL);

    SendAccess(playerid, "Вы начали погоню за %s [%d].", get_name(params[0]), params[0]);
    SendInfo(params[0], "Полицейский начал погоню за Вами. Вы можете сдаться или скрыться.");
    p_temp[params[0]][chase_followerId] = playerid;
    return 1;
}
CMD:cuff(playerid, params[])
{
    if((IsPlayerFractionPolice(playerid) && p_info[playerid][rang] > 1) ||
        (p_info[playerid][member] == MAYOR_LS && p_info[playerid][rang] < 3) ||
        (p_info[playerid][member] == PRISON && GetPlayerVirtualWorld(playerid) > 0))
    {
        if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /cuff [id игрока]");
        if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
            return SendError(playerid, "Игрок не найден.");
        if(distance(playerid, params[0]) > 3.0 || GetPlayerState(params[0]) == PLAYER_STATE_SPECTATING)
            return SendError(playerid, "Игрок слишком Далеко от Вас.");
        if(p_info[params[0]][p_afkTime] > 2)
            return SendError(playerid, "Данный игрок в AFK.");
        if(IsPlayerInAnyVehicle(params[0]))
            return SendError(playerid, "Игрок находится в транспортном средстве.");
        if(gos(params[0]) && p_info[playerid][member] != FBI_TEAM)
            return SendError(playerid, "Игрок состоит в гос. фракции.");
        if(GetPVarInt(params[0],"PlayerCuffed") == 1)
            return SendError(playerid, "Игрок уже в наручниках.");
        if(GetFractionWarehouse(p_info[playerid][member], fwMate) < 50)
            return SendError(playerid, "На складе недостаточно материалов.");
        if(p_info[playerid][jail] != 0)
            return SendError(playerid, "Вы находитесь в тюрьме.");
        if(p_info[params[0]][jail] != 0)
            return SendError(playerid, "Игрок находится в тюрьме.");

        new string[52 - 8 + MAX_PLAYER_NAME*2];
        SetFractionWarehouse(p_info[playerid][member], fwMate, -50);

        format(string, sizeof(string), "{B17FC8}%s %s одел наручники на %s.", p_info[playerid][member] != MAYOR_LS ? "Полицейский" : "Охранник", get_name(playerid), get_name(params[0]));
        SendDistanceChat(playerid, 20.0, string);

        GameTextForPlayer(params[0], "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~CUFFED", 3000, 3);

        SetPVarInt(params[0],"PlayerCuffed",1);
        SetPlayerCuffed(params[0], true);
        Fix_TogglePlayerControllable(params[0], 0);

        if(p_info[playerid][p_settings][ROLEPLAY] == 1)
        {
            DoAction(playerid, "Наручники весят на поясном держателе.");
            MeAction(playerid, "протянул правую руку к поясу, затем движением руки снял с пояса наручники...");
            MeAction(playerid, "...затем быстрым движением рук начал надевать наручник на руки человека");
        }
    }
    else SendError(playerid, "Вы не можете пользоваться этой командой.");
    return 1;
}
CMD:uncuff(playerid, params[])
{
    if((IsPlayerFractionPolice(playerid) && p_info[playerid][rang] > 1) ||
        (p_info[playerid][member] == MAYOR_LS && p_info[playerid][rang] < 3) ||
        (p_info[playerid][member] == PRISON && GetPlayerVirtualWorld(playerid) > 0))
    {
        if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /uncuff [id игрока]");

        if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
            return SendError(playerid, "Игрок не найден.");

        if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID)
            return SendError(playerid, "Игрок слишком далеко от Вас.");

        if(!GetPVarInt(params[0],"PlayerCuffed"))
            return SendError(playerid, "Игрок не в наручниках.");

        if(p_info[playerid][jail] != 0)
            return SendError(playerid, "Вы находитесь в тюрьме.");
        if(p_info[params[0]][jail] != 0)
            return SendError(playerid, "Игрок находится в тюрьме.");

        new
            string[46 - 4 + MAX_PLAYER_NAME*2];

        format(string, sizeof(string), "{B17FC8}Полицейский %s cнимает наручники с %s.", get_name(playerid), get_name(params[0]));
        SendDistanceChat(playerid, 20.0, string);

        GameTextForPlayer(params[0], "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~g~UNCUFFED", 3000, 3);

        DeletePVar(params[0],"PlayerCuffed");
        SetPlayerCuffed(params[0], false);
        ClearAnimations(params[0]);
        Fix_TogglePlayerControllable(params[0], 1);

        if(p_info[playerid][p_settings][ROLEPLAY] == 1)
        {
            DoAction(playerid, "Ключ от наручников лежит в кармане.");
            MeAction(playerid, "движением правой руки вытащил из кармана ключ от наручников...");
            MeAction(playerid, "...после чего протянул руку к наручникам, а затем повернул ключ на 360 градусов...");
            MeAction(playerid, "...тем самым освободив человека от наручников");
        }
    } else SendError(playerid, "Вы не можете пользоваться этой командой.");
    return 1;
}

CMD:demote(playerid, params[])
{
    if(((p_info[playerid][member] == FBI_TEAM && p_info[playerid][rang] >= 7) || (p_info[playerid][member] == MAYOR_LS && p_info[playerid][rang] >= 9)) && p_info[playerid][fwork] == true)
    {
        if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /demote [id игрока]");
        if(params[0] == INVALID_PLAYER_ID || playerid == params[0])
            return SendError(playerid, "Игрок не найден.");
        if(!IsPlayerFractionPolice(params[0]) && !army(params[0]))
            return SendError(playerid, "Игрок не состоит в полиции и армии.");
        if(p_info[params[0]][leader] != NONE_FRACTION)
            return SendError(playerid, "Игрок лидер фракции.");

        p_info[params[0]][rang]--;
        if(p_info[params[0]][rang] <= 0)
        {
            switch(p_info[params[0]][member])
            {
                case NATIONAL_GUARD:
                {
                    p_info[params[0]][rang] =
                    p_info[params[0]][member] = 0;
                    SetPlayerArmour(params[0], 0);
                    SpawnPlayer(params[0]);
                    ResetPlayerWeapons(params[0]);
                    SendAccess(playerid, "Вы уволили %s [%d] из армии.", get_name(params[0]), params[0]);
                    SendInfo(params[0], "%s [%d] уволил Вас из армии.", get_name(playerid), playerid);
                }
                case POLICE_LS..POLICE_LV, POLICE_RC:
                {
                    p_info[params[0]][member] = NATIONAL_GUARD;
                    p_info[params[0]][rang] = 3;
                    SendAccess(playerid, "Вы перевели %s [%d] в армию.", get_name(params[0]), params[0]);
                    SendInfo(params[0], "%s [%d] перевел Вас в армию.", get_name(playerid), playerid);
                    SpawnPlayer(params[0]);
                }
            }
        } else {
            SendAccess(playerid, "Вы понизили %s [%d] до %d ранга.", get_name(params[0]), params[0], p_info[params[0]][rang]);
            SendInfo(params[0], "%s [%d] понизил Вас до %d ранга.", get_name(playerid), playerid, p_info[params[0]][rang]);
        }
    } else SendError(playerid, "Вы не можете пользоваться этой командой.");
    return 1;
}

CMD:convoy(playerid, params[])
{
    new string[80];
    if(!IsPlayerFractionPolice(playerid) && (p_info[playerid][member] != MAYOR_LS || p_info[playerid][rang] > 2) && (p_info[playerid][member] != PRISON || p_info[playerid][rang] < 2)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(GetPVarInt(playerid,"Convoy") > 0)
    {
        f(string, "{B17FC8}%s %s отпустил %s", p_info[playerid][member] != MAYOR_LS ? "Полицейский" : "Охранник", get_name(playerid), get_name(GetPVarInt(playerid, "Convoy")-1));
        SendDistanceChat(playerid, 20.0, string);
        SetPVarInt(GetPVarInt(playerid, "Convoy")-1,"Conv",0);
        SetPVarInt(GetPVarInt(playerid, "Convoy")-1,"Ved", 0);
        DeletePVar(playerid, "Convoy");
        return 1;
    }
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /convoy [id игрока]");
    if(IsPlayerInAnyVehicle(playerid)) return SendError(playerid, "Вы находитесь в транспортном средстве.");
    if(!IsPlayerConnected(params[0])) return SendError(playerid, "Игрок не найден.");
    if(playerid == params[0]) return SendError(playerid, "Вы ввели свой ID.");
    if(IsPlayerFractionPolice(params[0])) return SendError(playerid, "Игрок состоит в гос. организации.");
    if(IsPlayerInAnyVehicle(params[0])) return SendError(playerid, "Игрок находится в транспортном средстве.");
    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(GetPVarInt(params[0],"Conv") == 1) return SendError(playerid, "Игрок уже под конвоем.");
    if(!GetPVarInt(params[0],"PlayerCuffed")) return SendError(playerid, "Игрок должен быть в наручниках.");
    if(p_info[playerid][jail] != 0) return SendError(playerid, "Вы находитесь в тюрьме.");
    if(p_info[params[0]][jail] != 0) return SendError(playerid, "Игрок находится в тюрьме.");
    f(string, "{B17FC8}%s %s ведет за собой %s", p_info[playerid][member] != MAYOR_LS ? "Полицейский" : "Охранник", get_name(playerid), get_name(params[0]));
    SendDistanceChat(playerid, 20.0, string);
    ClearAnimations(params[0]);
    Fix_TogglePlayerControllable(params[0], 1);
    SetPVarInt(params[0],"Conv",1);
    SetPVarInt(params[0],"Ved", playerid);
    SetPVarInt(playerid, "Convoy", params[0]+1);
    SendInfo(playerid, "Управление конвоем: /convoy");

    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        MeAction(playerid, "ухватился правой рукой за шею нарушителя, после чего повел его за собой");
    }
    return true;
}


//alias:meg("m");
CMD:m(playerid, params[])
{
    if(p_temp[playerid][tGag] == true) return SendError(playerid, "У Вас кляп.");
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    if(!IsPlayerFractionPolice(playerid) && !IsPlayerFractionMedic(playerid)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(!(1 <= strlen(params) <= 80)) return SendError(playerid, "Длина введеного текста должна быть не менее 1 и не более 80 символов.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
    {
        if(!cop_car(vehicleid) && !medic_car(vehicleid))
            return SendError(playerid, "Вы должны находиться в специализированном транспортном средстве.");
    }
    else
    {
        foreach(new i: Vehicle)
        {
            if(!cop_car(vehicleid) && !medic_car(vehicleid)) continue;
            if(!IsPlayerInRangeOfVehicle(playerid, 5.0, i) || GetVehicleVirtualWorld(i) != GetPlayerVirtualWorld(playerid)) continue;
            vehicleid = i;
            break;
        }
    }

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "[Рупор] %s: {FFEE00}%s", get_name(playerid), params);
    SendDistanceChat(playerid, 50.0, STRING_GLOBAL);

    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        DoAction(playerid, "На груди служащего весит рупор.");
        MeAction(playerid, "сцепив с груди рупор, активировал его, затем начал в него кричать");
    }
    return true;
}
CMD:wanted(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(p_info[playerid][p_settings][ROLEPLAY] == 1)
    {
        DoAction(playerid, "Планшет весит на поясе и он отключен.");
        MeAction(playerid, "вытащил из пояса планшет, затем активировал его");
        DoAction(playerid, "Планшет активирован.");
        MeAction(playerid, "зашел в базу данных Министерства, после чего открыл данные о федеральных нарушителях");
    }

    ShowPlayerDialog(playerid, D_WANTED_MENU, DIALOG_STYLE_LIST, "Все кто в сети\nВсе кто не в сети", "Список подозреваемых", "Далее", "Отмена");
    return true;
}

CMD:unarm(playerid)
{
    new Float:armour;
    GetPlayerArmour(playerid, armour);
    if(armour > 0.0)
    {
        SetPlayerArmour(playerid, 0.0);
        SendAccess(playerid, "Вы сняли бронежилет.");
    }
    return 1;
}
alias:unarm("unarmour");