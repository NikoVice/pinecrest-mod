this::LoadDynamicAPB()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;
    if (!rows) return print("[APBS] Записи не найдены.");

    for(new i = 0; i < rows; i++)
    {
        cache_get_value_name_int(i, "id", ApbInfo[i][apbID]);
        cache_get_value_name(i, "charge", ApbInfo[i][apbCharge]);
        cache_get_value_name(i, "suspect", ApbInfo[i][apbSuspect]);
        cache_get_value_name(i, "officer", ApbInfo[i][apbOfficer]);
        cache_get_value_name(i, "date", ApbInfo[i][apbDate]);
        cache_get_value_name_int(i, "faction", ApbInfo[i][apbFaction]);
        ApbInfo[i][apbOn] = 1;
        total++;
    }
    printf("[APBS] Строк - %i. Загружено - %i. Затрачено: %i ms.", rows, total, GetTickCount()-time);
    return 1;
}

this::ApbCreate(apb)
{
    ApbInfo[apb][apbID] = cache_insert_id();
    ApbInfo[apb][apbOn] = 1;
    return 1;
}
/*
SetPlayerZond(playerid, step)
{
    if (step == 0)
    {
        if (p_temp[playerid][pZond] != 1) return 1;

        TogglePlayerSpectating(playerid, 0);
        DestroyPlayerObject(playerid, p_temp[playerid][pZondObj]);

        if (IsValidDynamic3DTextLabel(p_temp[playerid][pZondLabel]))
        {
            DestroyDynamic3DTextLabel(p_temp[playerid][pZondLabel]);
            p_temp[playerid][pZondLabel] = Text3D:INVALID_3DTEXT_ID;
        }

        DestroyDynamicActor(p_temp[playerid][pZondActor]);
        p_temp[playerid][pZondActor] = INVALID_ACTOR_ID;

        for(new i; i < 11; i++) TextDrawHideForPlayer(playerid, TD_ZondCam[i]);
        return 1;
    }

    new id = -1, Float: x, Float: y, Float: z, vw, interior;

    if ((id = GetNearOutsideBiz(playerid)) != -1 && (BizInfo[id][bizType] != BIZ_GAS_STATION && BizInfo[id][bizType] != BIZ_AUTOSALON && BizInfo[id][bizType] != BIZ_ADVERT && BizInfo[id][bizType] != BIZ_TUNING && BizInfo[id][bizType] != BIZ_LICENSE && BizInfo[id][bizType] != BIZ_BOATSALON && BizInfo[id][bizType] != BIZ_FLYSALON))
    {
        x = BizInfo[id][bizExitX];
        y = BizInfo[id][bizExitY];
        z = BizInfo[id][bizExitZ];
        vw = BizInfo[id][bizExitVW];
        interior = BizInfo[id][bizExitInt];
    }

    if (id == -1 && (id = GetNearOutsideHouse(playerid)) != -1)
    {
        x = HouseInfo[id][hExitX];
        y = HouseInfo[id][hExitY];
        z = HouseInfo[id][hExitZ];
        vw = HouseInfo[id][hExitVW];
        interior = HouseInfo[id][hExitInt];
    }

    if (id == -1 && (id = GetNearOutsideExtHouse(playerid)) != -1)
    {
        x = HouseInfo[id][hExtX][0];
        y = HouseInfo[id][hExtY][0];
        z = HouseInfo[id][hExtZ][0];
        vw = HouseInfo[id][hExtVW][0];
        interior = HouseInfo[id][hExtInt][0];
    }

    if (id == -1 && (id = GetNearApartmentOutside(playerid)) != -1)
    {
        x = ApartInfo[id][aExitX];
        y = ApartInfo[id][aExitY];
        z = ApartInfo[id][aExitZ];
        vw = ApartInfo[id][aExitVW];
        interior = ApartInfo[id][aExitInt];
    }

    if (id == -1) return 1;

    SavePlayerPos(playerid);
    GameTextForPlayer(playerid, "_", 1, 4);

    if (IsValidDynamic3DTextLabel(p_temp[playerid][pZondLabel]))
    {
        DestroyDynamic3DTextLabel(p_temp[playerid][pZondLabel]);
        p_temp[playerid][pZondLabel] = Text3D:INVALID_3DTEXT_ID;
     }

     new mes[128];

    format(mes, sizeof(mes),"(( %s использует зонд. ))", GetNameWithMask(playerid));
    p_temp[playerid][pZondLabel] = CreateDynamic3DTextLabel(mes, COLOR_MAIN, PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    p_temp[playerid][pZondActor] = CreateDynamicActor(GetPlayerSkin(playerid), PlayerInfo[playerid][pPosX], PlayerInfo[playerid][pPosY], PlayerInfo[playerid][pPosZ], PlayerInfo[playerid][pPosA], GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid));
    ApplyDynamicActorAnimation(p_temp[playerid][pZondActor], "BOMBER", "NULL", 0.0, 0, 0, 0, 0, 0);
    ApplyDynamicActorAnimation(p_temp[playerid][pZondActor], "BOMBER", "BOM_Plant_Loop", 4.1, 0, 0, 0, 1, 0);
    TogglePlayerSpectating(playerid, 1);
    p_temp[playerid][pZondObj] = CreatePlayerObject(playerid, 19300, x, y, z, 0.0, 0.0, 0.0);
    AttachCameraToPlayerObject(playerid, p_temp[playerid][pZondObj]);
    SetPlayerInterior(playerid, interior);
    SetPlayerVirtualWorld(playerid, vw);

    for(new i; i<11;i++) TextDrawShowForPlayer(playerid, TD_ZondCam[i]);

    p_temp[playerid][pZond] = 1;

    SendFactionMessage(FACTION_POLICE, COLOR_POLICECHAT, "* %s %s начал использовать /zond.", GetPlayerFractionRangName(playerid), get_name(playerid));

    return 1;
}

TracePlayer(playerid)
{
    new targetid = p_temp[playerid][pTracePlayer];
    p_temp[playerid][pTraceStage]++;

    if (p_temp[playerid][pTraceStage] < 9 && (!p_info[targetid][loggedIn] || PlayerInfo[targetid][pPhoneAirplane] != 0 || PlayerInfo[targetid][pPhoneOff] != 0 || 0 == GetPlayerNetwork(targetid)))
    {
        if(p_temp[playerid][pTraceGZ] != -1) GangZoneDestroy(p_temp[playerid][pTraceGZ]);

        p_temp[playerid][pTraceGZ] = -1;
        p_temp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
        p_temp[playerid][pTraceStage] = 0;
        SendError(playerid, "Сигнал потерян.");

        return 1;
    }

    new mulstatus[16], sevstatus[16], verstatus[16], mes[712];

    if (p_temp[playerid][pTraceDist][0] >= 1250.0) mulstatus = "{FF6347}СЛАБЫЙ";
    else if (p_temp[playerid][pTraceDist][0] < 1250.0) mulstatus = "{DABB3E}ХОРОШИЙ";

    if (p_temp[playerid][pTraceDist][1] >= 1250.0) sevstatus = "{FF6347}СЛАБЫЙ";
    else if (p_temp[playerid][pTraceDist][1] < 1250.0) sevstatus = "{DABB3E}ХОРОШИЙ";

    if (p_temp[playerid][pTraceDist][1] >= 1250.0) verstatus = "{FF6347}СЛАБЫЙ";
    else if (p_temp[playerid][pTraceDist][1] < 1250.0) verstatus = "{DABB3E}ХОРОШИЙ";

    if (p_temp[playerid][pTraceStage] < 9)
    {
        if (p_temp[playerid][pTraceStage] > 1) format(mes, sizeof(mes), "{AFAFAF}Получен %s {AFAFAF}сигнал в районе {FFFFFF}Mulholland{AFAFAF} ...\n", mulstatus);
        if (p_temp[playerid][pTraceStage] > 3) format(mes, sizeof(mes), "%s{AFAFAF}Получен %s {AFAFAF}сигнал в районе {FFFFFF}Mulholland{AFAFAF} ...\n", mes, sevstatus);
        if (p_temp[playerid][pTraceStage] > 5) format(mes, sizeof(mes), "%s{AFAFAF}Получен %s {AFAFAF}сигнал в районе {FFFFFF}Verona Beach{AFAFAF} ...",mes, verstatus);

        if (p_temp[playerid][pTraceStage] == 8)
        {
            new location[MAX_ZONE_NAME];
            GetPlayer2DZone(targetid, location, MAX_ZONE_NAME);

            new Float:x, Float:y, Float:z;

            if (GetPlayerVirtualWorld(targetid) || GetPlayerInterior(targetid))
            {
                x = PlayerInfo[targetid][pLocationPos][0];
                y = PlayerInfo[targetid][pLocationPos][1];
                z = PlayerInfo[targetid][pLocationPos][2];
            }
            else GetPlayerPos(targetid, x, y, z);

            format(mes, sizeof(mes), "%s\n{AFAFAF}... Отслеживание закончено.\n\n\nПриблизительное местонахождение: %s\nНомер телефона: %i / Владелец: %s", mes, location, PlayerInfo[targetid][pNumber], get_name(targetid));

            p_temp[playerid][pTraceGZ] = GangZoneCreate(x+65, y+65, x-65,y-65);
            GangZoneShowForPlayer(playerid, p_temp[playerid][pTraceGZ], 0xFF0000AA);
        }
        ShowPlayerDialog(playerid, D_SHOW_TRACE, DIALOG_STYLE_MSGBOX, "Система отслеживания, чтобы закрыть нажмите ESC", mes, "Закрыть", "");
    }

    if (p_temp[playerid][pTraceStage] > 600)
    {
        if (p_temp[playerid][pTraceGZ] != -1) GangZoneDestroy(p_temp[playerid][pTraceGZ]);
        p_temp[playerid][pTraceGZ] = -1;

        p_temp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
        p_temp[playerid][pTraceStage] = 0;
    }
    return 1;
}
*/
Add_Call(playerid, type, text[])
{
    new Float:x, Float:y, Float:z;

    GetPlayerPos(playerid,x, y, z);
    for(new i = 0; i != MAX_CALLS_AND_ARREST; i++)
    {
        if (CallInfo[i][callExists] != 0) continue;

        GetPlayerPos(playerid, CallInfo[i][callPosX], CallInfo[i][callPosY], CallInfo[i][callPosZ]);
        CallInfo[i][callType] = type;
        format(CallInfo[i][callText], 128, "%s", text);
        format(CallInfo[i][callDate], 32, "%s", GetFullDate());
        GetPlayer2DZone(playerid, CallInfo[i][callLocation], 128);


        //if (p_temp[playerid][pPayphone] == -1)
        //{
        format(CallInfo[i][callName], MAX_PLAYER_NAME, "%s", get_name(playerid));
        CallInfo[i][callPhone] = p_info[playerid][phone_number];
        /*}
        else
        {
            format(CallInfo[i][callName], MAX_PLAYER_NAME, "Таксофон");
            CallInfo[i][callPhone] = PayphoneInfo[p_temp[playerid][pPayphone]][phNumber];
        }*/
        CallInfo[i][callDelete] = timestamp + 1200;
        CallInfo[i][callExists] = 1;
        break;
    }
    return 1;
}

AddCriminalRecord(playerid, const charge[], officer[], faction, arrest = 0)
{
    if (!strlen(charge)) return SendError(playerid, "Слишком короткое обвинение.");
    new query[256];
    mysql_format(con_bd, query, sizeof(query),"INSERT INTO `criminalrecords` (userid, charge, date, officer, faction, arrest) VALUES (%i, '%e', '%s', '%e', %i, %i)", p_info[playerid][ID], charge, GetFullDate(), officer, faction, arrest);
    mysql_tquery(con_bd, query);
    return 1;
}

Patrul_OnGameModeInit()
{
    for(new i; i != MAX_PATROL; i++)
    {
        PatrolInfo[0][i][patrulOfficer][0] = INVALID_PLAYER_ID;
        PatrolInfo[0][i][patrulOfficer][1] = INVALID_PLAYER_ID;
        PatrolInfo[1][i][patrulOfficer][0] = INVALID_PLAYER_ID;
        PatrolInfo[1][i][patrulOfficer][1] = INVALID_PLAYER_ID;
    }
    return 1;
}

GetPatrolID(playerid)
{
    return (IsPlayerFractionPolice(playerid))?(1):(0);
}
/*
StartChase(playerid)
{
    SetPVarInt(playerid, #Chase_Time, 300);
    SetPVarInt(playerid, #Chase_Timer, SetTimerEx("Chasing", 1000, true, "i", playerid));
    return 1;
}
*/
this::Chasing(playerid)
{
    if (GetPVarInt(playerid, #Chase_Time) > 1) {
        SetPVarInt(playerid, #Chase_Time, GetPVarInt(playerid, #Chase_Time) - 1);
    } else {
        KillTimer(GetPVarInt(playerid, #Chase_Timer));
        DeletePVar(playerid, #Chase_Time);
        DeletePVar(playerid, #Chase_Timer);

        foreach(new i : Player)
        {
            if (!p_info[i][loggedIn] || !IsPlayerFractionPolice(i))    continue;
            SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
        }
        return 1;
    }

    foreach(new i : Player)
    {
        if (!p_info[i][loggedIn] || !IsPlayerFractionPolice(i))    continue;
        if (!IsPlayerStream(30.0, i, playerid))
            SetPlayerMarkerForPlayer(i, playerid, 0xFFFFFF00);
        else
            SetPlayerMarkerForPlayer(i, playerid, 0xA52A2AFF);
    }

    return 1;
}
//=========================================================
br_system_PlayerDisconnect(playerid)
{
    for(new i = 0; i < MAX_PLAYER_BREAK; i++)
    {
        if(BreakObject[playerid][i] > 0)
        {
            if(BreakAreas[playerid][i] != 0) DestroyDynamicArea(BreakAreas[playerid][i]);
            DestroyDynamicObject(BreakObject[playerid][i]);
            Delete3DTextLabel(Break3DText[playerid][i]);
            BreakObject[playerid][i] = 0;
            BreakAreas[playerid][i] = 0;
        }
    }
}

Get_Calls(playerid)
{
    if (!IsPlayerFractionPolice(playerid) &&
        !IsPlayerFractionMedic(playerid)) return 1;

    new mes[512], count, type = (IsPlayerFractionMedic(playerid)) ? (2) : (1);

    for(new i = 0; i != MAX_CALLS_AND_ARREST; i++)
    {
        if (CallInfo[i][callExists] == 0 || (CallInfo[i][callType] != type && CallInfo[i][callType] != 3)) continue;
        format(mes, sizeof(mes), "%s"I"[%d]"W" %s (Номер: %i), %s\n", mes, count+1, CallInfo[i][callName], CallInfo[i][callPhone], CallInfo[i][callDate]);
        count++;
    }
    if (!count) return SendError(playerid, ""W"Нет доступных вызовов 911.");
    ShowPlayerDialog(playerid, D_CALLS_LIST, DIALOG_STYLE_LIST, ""I"MDC - Звонки в 911", mes, "Выбрать", "Назад");
    return 1;
}
