/*
    Author: Vip_Uzer
    11.03.2023
*/

SetGangTerritory(gang_id, value)
{
    if(GROOVE <= gang_id <= VAGOS)
    {
        GangCountTerritory[gang_id-10] += value;

        GhettoKing_Update();
    }
}

GetGangTerritory(gang_id)
{
    if(!(GROOVE <= gang_id <= VAGOS)) return -1;
    return GangCountTerritory[gang_id-10];
}

SetGangGraffiti(gang_id, value)
{
    if(GROOVE <= gang_id <= VAGOS)
    {
        GangCountGraffiti[gang_id-10] += value;

        GhettoKing_Update();
    }
}

GetGangGraffiti(gang_id)
{
    if(!(GROOVE <= gang_id <= VAGOS)) return -1;
    return GangCountGraffiti[gang_id-10];
}

SetGangPC(gang_id, value)
{
    if(GROOVE <= gang_id <= VAGOS)
    {
        GangRegPC[gang_id-10] = value;
    }
}

GetGangPC(gang_id)
{
    if(!(GROOVE <= gang_id <= VAGOS)) return INVALID_MYSQL_ID;
    return GangRegPC[gang_id-10];
}

/////////////
//ghetto king

GhettoKing_Update()
{
    new max_count, temp_old = GhettoKingID;
    for(new i = GROOVE; i < VAGOS+1; i++)
    {
        if(GetGangTerritory(i)+GetGangGraffiti(i) > max_count)
        {
            max_count = GetGangTerritory(i)+GetGangGraffiti(i);
            GhettoKingID = i;
        }
    }
    if(temp_old != GhettoKingID && temp_old != -1)
        SendFractionMessage(temp_old, 0x33CC66FF, "[Ghetto King]: Ваша банда потеряла статус королей гетто.");
    if(GhettoKingID != temp_old && GhettoKingID != -1)
        SendFractionMessage(GhettoKingID, 0x33CC66FF, "[Ghetto King]: Ваша банда получила статус королей гетто.");
}

GhettoKing_SetTuning(vehicleid)
{
    switch(GetVehicleModelEx(vehicleid))
    {
        case 560://sultan
            AddAllTuneVehicle(vehicleid, 1138, 1032, 1169, 1141);
        case 536://blade
            AddAllTuneVehicle(vehicleid, 1103, 1105, 1107, 1108, 1181, 1183, 1108);
        case 567://savanna
            AddAllTuneVehicle(vehicleid, 1102, 1129, 1130, 1133, 1186, 1188);
        case 534://remington
            AddAllTuneVehicle(vehicleid, 1102, 1101, 1122, 1123, 1125, 1127, 1178, 1185);
        case 575://broadway
            AddAllTuneVehicle(vehicleid, 1042, 1043, 1175, 1175, 1174);
        case 565://flash
            AddAllTuneVehicle(vehicleid, 1046, 1050, 1054, 1150, 1153);
        case 535://slamvan
            AddAllTuneVehicle(vehicleid, 1110, 1112, 1114, 1116, 1117);
        case 562://elegy
            AddAllTuneVehicle(vehicleid, 1034, 1038, 1036, 1040, 1147, 1149, 1171);
        case 558://uranus
            AddAllTuneVehicle(vehicleid, 1088, 1090, 1092, 1094, 1164, 1166, 1168);
        case 559://jester
            AddAllTuneVehicle(vehicleid, 1066, 1068, 1158, 1161, 1173);
        case 561://stratum
            AddAllTuneVehicle(vehicleid, 1055, 1058, 1064, 1154, 1155);
        default:
        {
                AddAllTuneVehicle(vehicleid);
        
                if(GetVehicleModelEx(vehicleid) == 482)
                {
                    veh_info[vehicleid][v_attach_object][0] = CreateDynamicObject(19477,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                    SetDynamicObjectMaterialText(veh_info[vehicleid][v_attach_object][0], 0, "KING", 130, "Comic Sans MS", 60, 1, -1, 0, 0);
                    AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][0], vehicleid, 1.169, -1.030, -0.330, 0.000, -15.400, 0.000);
                    veh_info[vehicleid][v_attach_object][1] = CreateDynamicObject(19477,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                    SetDynamicObjectMaterialText(veh_info[vehicleid][v_attach_object][1], 0, "OF THE GHETTO", 130, "Comic Sans MS", 60, 1, -1, 0, 0);
                    AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][1], vehicleid, 1.172, -0.330, -0.339, 0.000, -13.700, 0.000);
                    veh_info[vehicleid][v_attach_object][2] = CreateDynamicObject(19477,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                    SetDynamicObjectMaterialText(veh_info[vehicleid][v_attach_object][2], 0, "OF THE GHETTO", 130, "Comic Sans MS", 60, 1, -1, 0, 0);
                    AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][2], vehicleid, -1.115, -1.809, -0.313, 0.000, -11.400, -179.600);
                    veh_info[vehicleid][v_attach_object][3] = CreateDynamicObject(19477,0.0,0.0,-1000.0,0.0,0.0,0.0,0,0,-1,300.0,300.0);
                    SetDynamicObjectMaterialText(veh_info[vehicleid][v_attach_object][3], 0, "KING", 130, "Comic Sans MS", 60, 1, -1, 0, 0);
                    AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][3], vehicleid, -1.120, -1.123, -0.316, 0.000, -12.000, 179.899);
                }
        }
    }
    SetVehicleObejcts(vehicleid, 1182);
    SetVehicleObejcts(vehicleid, 1176);

    SetVehicleObejcts(vehicleid, 2993);
    return 1;
}

AddAllTuneVehicle(vehicleid, ...)
{
    new j = numargs();
    do VEx_AddVehicleComponent(vehicleid, getarg(--j));
    while(j > 1);

    VEx_AddVehicleComponent(vehicleid, 1073+random(14));
    VEx_AddVehicleComponent(vehicleid, 1010);

    if(GetVehicleComponentInSlot(vehicleid, CARMODTYPE_HYDRAULICS)) return;
   	VEx_AddVehicleComponent(vehicleid,1087);
}
// cmd:
CMD:capture(playerid, params[])
{
    if(!gang(playerid))
        return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(p_info[playerid][rang] < 6)
        return SendError(playerid, "Вы не можете пользоваться этой командой.");

    new gangzone, faction_playerid = p_info[playerid][member];

    if(GetPlayerInterior(playerid) != 0)
        return 1;

    if(GetPVarInt(playerid, "FLOOD:CAPTURE") > timestamp)
        return SendError(playerid, "Вы не можете так часто использовать команды.");
    SetPVarInt(playerid, "FLOOD:CAPTURE", timestamp+3);

    if(SRV_ID != 0)
    {
        if(timestamp_hour < 14 || timestamp_hour > 23)
            return SendError(playerid, "Проводить захват территории разрешено с 14:00 до 23:00.");
        if(timestamp_minute < 00 || timestamp_minute > 10)
            return SendError(playerid, "Проводить захват территории разрешено с **:00 до **:10.");
    }

    if(GetFractionSettings(faction_playerid, fFreezeCapture) != 0)
        return SendError(playerid, "Ваша фракция уже проводила захват территории.");
    if(IsPlayerInAnyVehicle(playerid))
        return SendError(playerid, "Вы находитесь в транспортном средстве.");

    gangzone = GetGangZoneID(playerid);
    if(gangzone == INVALID_CRIMINAL_ZONE_ID)
        return SendError(playerid, "Вы не на территории гетто.");
    if(IsGangRespawn(gangzone))
        return SendError(playerid, "Эта территория является респауном банды.");

    if(GangZone_Info[gangzone][g_Fraction] == 15)
        return SendError(playerid, "Вы не можете начать захват территории в этом месте.");
    if(GangZone_Info[gangzone][g_Fraction] == faction_playerid)
        return SendError(playerid, "Данная территория принадлежит Вашей банде.");

    if(gangzone == 39 && DrugDenInfo[ddCapture] > timestamp)
    {
        SendError(playerid, "Захват данной территории возможен через %s.", ConvertTime(DrugDenInfo[ddCapture] - timestamp, 1));
        return 1;
    }

    if(GetFractionSettings(GangZone_Info[gangzone][g_Fraction], fFreezeCapture) > 1)
        return SendError(playerid, "Данная банда заморожена.");
    if(GetFractionSettings(faction_playerid, fFreezeCapture) > 1)
        return SendError(playerid, "Ваша банда заморожена.");

    if(GetFractionSettings(GangZone_Info[gangzone][g_Fraction], fFreezeCapture) != 0)
        return SendError(playerid, "Эта банда недавно проводила захват территории.");
    
    if(GetFractionSettings(GangZone_Info[gangzone][g_Fraction], fFreezeCapture) > 0 ||
        GetFractionSettings(faction_playerid, fFreezeCapture) > 0)
        return SendError(playerid, "Захват территории уже начался.");

    if(SRV_ID != 0)
    {
        if(GetFractionOnline(faction_playerid) < 2)
            return SendError(playerid, "У Вашей банде слишком мало игроков в игре.");
        if(GetFractionOnline(GangZone_Info[gangzone][g_Fraction]) < 2)
        {
            SendError(playerid, "У \"%s\" слишком мало игроков в игре.", GetFractionName(GangZone_Info[gangzone][g_Fraction]));
            return 1;
        }
    }

    new idx;
    if(Capture_Info[0][gFaction][0] == 0 || Capture_Info[0][gFaction][1] == 0)
        idx = 0;
    else if(Capture_Info[1][gFaction][0] == 0 || Capture_Info[1][gFaction][1] == 0)
        idx = 1;
    else return SendError(playerid, "Захват территории уже начался.");

    if(Capture_Info[idx][gStatus] != GANG_ZONE_NONE)
        return SendError(playerid, "Захват территории уже начался.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s [%d] из \"%s\" начал захват территории \"%s\".", get_name(playerid), playerid, GetFractionName(p_info[playerid][member]), GetFractionName(GangZone_Info[gangzone][g_Fraction]));
    SendFractionMessage(faction_playerid, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(GangZone_Info[gangzone][g_Fraction], 0x33CC66FF, STRING_GLOBAL);

    SendFractionMessage(faction_playerid, 0x33CC66FF, "[F] Вы можете подготовиться, у Вас есть 1 минута.");
    SendFractionMessage(GangZone_Info[gangzone][g_Fraction], 0x33CC66FF, "[F] Вы можете подготовиться, у Вас есть 1 минута.");
    
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    GangZoneFlashForAll(GangZone_Info[gangzone][gID], fraction_color[p_info[playerid][member]]);

    Capture_Info[idx][gGangZoneID] = gangzone;
    Capture_Info[idx][gFaction][0] = faction_playerid;
    Capture_Info[idx][gFaction][1] = GangZone_Info[gangzone][g_Fraction];
    Capture_Info[idx][gTime] = (60*1);
    Capture_Info[idx][gStatus] = GANG_ZONE_PREPARATION;

    SetFractionSettings(faction_playerid, fFreezeCapture, 1);
    SetFractionSettings(GangZone_Info[gangzone][g_Fraction], fFreezeCapture, 1);

    InitTopList(faction_playerid, GangZone_Info[gangzone][g_Fraction], CAPTURE_ID_GANG, 21*60);

    foreach(new i:Player)
    {
        if(p_info[i][member] == Capture_Info[idx][gFaction][0] || p_info[i][member] == Capture_Info[idx][gFaction][1])
        {
            ShowTextDrawForPlayer(i, TD_ID_CAPTURE);
            CaptureInfoUpdate(i, CAPTURE_ID_GANG, idx);
        }
    }
    SetTimerEx("CaptureTimers", 1000, false, "i", idx);
    return 1;
}

CMD:gmap(playerid, params[])
{
    if(gang(playerid) == 0) return SendError(playerid, "Вы не можете пользоваться этой командой.");

    new string_zone[12];
    switch(GetGangTerritory(p_info[playerid][member]))
    {
        case 0, 5..10, 15..20, 25..30, 35..40, 45..50: string_zone = "территорий";
        case 1, 21, 31, 41: string_zone = "территорию";
        case 2..4, 22..24, 32..34, 42..44: string_zone = "территории";
    }

    SendInfo(playerid, "Под контролем Вашей фракции %d %s.", GetGangTerritory(p_info[playerid][member]), string_zone);
    return 1;
}

CMD:ggraffiti(playerid, params[])
{
    if(gang(playerid) == 0) return SendError(playerid, "Вы не можете пользоваться этой командой.");

    SendInfo(playerid, "Под контролем Вашей фракции %d граффити.", GetGangGraffiti(p_info[playerid][member]));
    return 1;
}

CMD:geject(playerid, params[])
{
    if(!gang(playerid))
        return SendError(playerid, "Вы не можете пользоваться этой командой.");

    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /geject [id игрока]");

    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");

    new player_state = GetPlayerState(playerid);
    if(player_state == PLAYER_STATE_WASTED || GetPlayerState(params[0]) == PLAYER_STATE_WASTED)
        return 1;

    if(player_state != PLAYER_STATE_ONFOOT)
        return SendError(playerid, "Вы должны находиться на ногах, чтобы выполнить данное действие.");

    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок слишком далеко от Вас.");

    if(!IsPlayerInAnyVehicle(params[0]))
        return SendError(playerid, "Игрок не в траспортном средстве.");

    new playerid_zoneid = GetGangZoneID(playerid),
        target_zoneid = GetGangZoneID(params[0]);

    if(gang(playerid) && gang(params[0]) && playerid_zoneid != INVALID_CRIMINAL_ZONE_ID && target_zoneid != INVALID_CRIMINAL_ZONE_ID)
    {
        new faction_playerid = p_info[playerid][member], faction_target = p_info[params[0]][member];
        if(faction_playerid != faction_target)
        {
            new i = GetCaptureID(faction_playerid, faction_target);
            if(i == -1) return SendError(playerid, "Вытащить можно только членов вражеской банды во время капта.");
            
            new string[60 - 4 + MAX_PLAYER_NAME*2];
            format(string, sizeof(string), "{B17FC8}%s вытащил %s из транспортного средства.", get_name(playerid), get_name(params[0]));
            SendDistanceChat(playerid, 20.0, string);

            GameTextForPlayer(params[0], "~n~~n~~n~~n~~n~~n~~n~~n~~n~~n~~r~EJECTED", 3000, 3);
            RemovePlayerFromVehicle(params[0]);

            if(p_info[playerid][p_settings][ROLEPLAY] == 1)
            {
                DoAction(playerid, "Дверь машины закрыта.");
                MeAction(playerid, "открыв дверь автомобиля ухватился за человека в машине...");
                MeAction(playerid, "...затем вытолкнул его из автомобиля закрыв за собой дверь");
            }
        }
    }
    return 1;
}

CMD:gonline(playerid, params[])
{
    STRING_GLOBAL[0] = EOS;
    STRING_GLOBAL = ""W"Фракция\t"W"В сети\n";
    for(new i; i < MAX_FRACTIONS; i++)
    {
        if(GetFactionType(i) != FACTION_TYPE_CRIMINAL) continue;
        f(STRING_GLOBAL, "%s {%06x}%s\t%d\n", STRING_GLOBAL, 
            fraction_color[i] >>> 8, GetFractionName(i), Iter_Count(gFactionPlayers[i]));
    }
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Состав криминала онлайн", STRING_GLOBAL, "Закрыть", "");
    return 1;
}
alias:gonline("gmembers", "ghetto", "mafia");

GetCaptureID(fraction_one, fraction_two)
{
    new id = -1;
    if((Capture_Info[0][gFaction][0] == fraction_one || Capture_Info[0][gFaction][1] == fraction_one)
        && (Capture_Info[0][gFaction][0] == fraction_two || Capture_Info[0][gFaction][1] == fraction_two))
        id = 0;
    if((Capture_Info[1][gFaction][0] == fraction_one || Capture_Info[1][gFaction][1] == fraction_one)
        && (Capture_Info[1][gFaction][0] == fraction_two || Capture_Info[1][gFaction][1] == fraction_two))
        id = 1;
    return id;
}

IsGangRespawn(gangzone)
{
    switch(gangzone)
    {
        case 85, 79, /*aztec*/
            46, 37,  /*groove*/
            95,94,   /*ballas*/
            101, 92, /*vagos*/
            61, 70: /*rifa*/
                return 1;
    }
    return 0;
}

IsGangSpawnKill(playerid)
{
    for(new i = VAGOS; i != GROOVE-1; i--)
    {
        if(IsPlayerInDynamicArea(playerid, GangSpawnKillZone[i-10])) 
            return i;
    }
    return 0;
}

CMD:gregpc(playerid, params[])
{
    if(sscanf(params, "u", params[0]))
    {
        ShowPlayerList(playerid, LIST_ID_GHETTO_PC);
        if(gang(playerid) && p_info[playerid][rang] >= 9)
            SendInfo(playerid, "Что бы зарегистрировать введите ID игрока.");
        return 1;
    }
    if(!gang(playerid) || p_info[playerid][rang] < 9)
    {
        ShowPlayerList(playerid, LIST_ID_GHETTO_PC);
        return SendError(playerid, "Регистрация ПК доступна только для замов и лидеров банд.");
    }

    if(SRV_ID)
    {
        if(!(16 <= timestamp_hour <= 22))
            return SendError(playerid, "Регистрировать ПК можно с 16 до 23 часов.");
        if(!(21 <= timestamp_minute <= 59))
            return SendError(playerid, "Регистрировать ПК можно с **:20 до **:00 минут каждого часа.");
    }

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не в сети.");

    if(p_info[playerid][member] != p_info[params[0]][member])
        return SendError(playerid, "Игрок не в вашей банде.");

    SetGangPC(p_info[playerid][member], p_info[params[0]][ID]);
    SendAccess(playerid, "Вы зарегистрировали %s ПК игроком на капте.", get_name(params[0]));
    SendAccess(params[0], "%s зарегистрировал Вас ПК игроком на капте.", get_name(playerid));
    return 1;
}

CMD:ganginfo(playerid)
{
    STRING_GLOBAL[0] = EOS;
    for(new i = GROOVE; i < VAGOS+1; i++)
    {
        f(STRING_GLOBAL, "%s"W"- {%06x}%s\n", STRING_GLOBAL, fraction_color[i] >>> 8, GetFractionName(i));
    }
    ShowPlayerDialog(playerid, D_GANGINFO, DIALOG_STYLE_LIST, ""I"Информация о банде", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;
}
alias:ganginfo("ginfo", "gmembersinfo");

this::GangInfoCallback(playerid, gang_id)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return SendError(playerid, "Ничего не найдено.");
    new iTotalMember;
    cache_get_value_name_int(0, "total", iTotalMember);

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, 
        ""W"Банда: {%06x}%s\n\
        "W"Количетство территрий: "I"%d\n\
        "W"Количество граффити: "I"%d\n\
        "W"Количество бандитов: "I"%d", 
            fraction_color[gang_id] >>> 8, GetFractionName(gang_id), GetGangTerritory(gang_id), GetGangGraffiti(gang_id), iTotalMember);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация о банде", STRING_GLOBAL, "Понял", "");
    return 1;
}

/*load_ghetto_war()
{
    if(SRV_ID != 2)
    {
        CreateActor(102, 2018.2439,-1126.3993,25.0101,180.0);
        CreateDynamic3DTextLabel("NPC: "I"Лидер Ballas", COLOR_WHITE, 2018.2439,-1126.3993,25.0101 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
        ghetto_bots[0] = CreateDynamicSphere(2018.2439,-1126.3993,25.0101, 2.5, 0, 0);
        UpdateAreaInfo(ghetto_bots[0], TYPE_GHETTOWAR, AREA_SUBTYPE_INVALID_ID, 0);

        CreateActor(174, 2801.9299,-1967.9025,13.5469,262.2592);
        CreateDynamic3DTextLabel("NPC: "I"Лидер Rifa", COLOR_WHITE, 2801.9299,-1967.9025,13.5469 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
        ghetto_bots[1] = CreateDynamicSphere(2801.9299,-1967.9025,13.5469, 2.5, 0, 0);
        UpdateAreaInfo(ghetto_bots[1], TYPE_GHETTOWAR, AREA_SUBTYPE_INVALID_ID, 1);
    } 
} */