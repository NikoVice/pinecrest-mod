new pickup_roadman;

CreateRoadCrash()
{
    if(RoadCrashIDx == -1) RoadCrashIDx = random(3);
    RoadCrashHash = random(1000000);
    new count[2];
    for(new i = 0; i < MAX_ROADCRASH; i++)
    {
        if(RoadCrashInfo[i][rcIDx] != RoadCrashIDx) continue;
        RoadCrashObjectIDx[count[0]] = CreateDynamicObject(RoadCrashInfo[i][rcModel], RoadCrashInfo[i][rcPos][0], RoadCrashInfo[i][rcPos][1], RoadCrashInfo[i][rcPos][2], RoadCrashInfo[i][rcPos][3], RoadCrashInfo[i][rcPos][4], RoadCrashInfo[i][rcPos][5], 0, 0, -1, 500.00, 500.00);
        if(count[0] >= 0 && count[0] < MAX_ROADCRASH_AREAS)
        {
            RoadCrashAreasIDx[count[1]] = CreateDynamicSphere(RoadCrashInfo[i][rcPos][0], RoadCrashInfo[i][rcPos][1], RoadCrashInfo[i][rcPos][2], 2.5, 0, 0, -1);
            UpdateAreaInfo(RoadCrashAreasIDx[count[1]], TYPE_ROADMAN, AREA_SUBTYPE_INVALID_ID, count[1]);
            count[1]++;
        }
        count[0]++;
    }
    SendMesAll(COLOR_LIGHTRED, "[ДОРОЖНЫЕ РАБОТЫ]: "W"В районе \"%s\" проходят дорожные работы.", RoadCrashName[RoadCrashIDx]);
    return 1;
}

DestroyRoadCrash()
{
    if(RoadCrashIDx == -1) return 1;
    for(new i = 0; i < MAX_ROADCRASH_OBJECT; i++)
    {
        if(i < MAX_ROADCRASH_AREAS && RoadCrashAreasIDx[i] != -1)
        {
            DestroyDynamicArea(RoadCrashAreasIDx[i]);
            RoadCrashAreasIDx[i] = -1;
        }
        if(RoadCrashObjectIDx[i] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(RoadCrashObjectIDx[i]);
            RoadCrashObjectIDx[i] = INVALID_OBJECT_ID;
        }
    }
    RoadCrashIDx++;
    if(RoadCrashIDx == MAX_ROADCRASH_MAP) RoadCrashIDx = 0;
    CreateRoadCrash();
    return 1;
}

CheckRoadCrash()
{
    new count = -1;
    for(new i = 0; i < MAX_ROADCRASH_AREAS; i++)
    {
        if(RoadCrashAreasIDx[i] != -1) count++;
    }
    return count;
}

LoadRoadman()
{
    CreateActor(260, 1083.3939,-1226.5360,15.8203,270.2774);
    CreateDynamic3DTextLabel("NPC: "I"Ремонтник дорог", COLOR_WHITE, 1083.3939,-1226.5360,15.8203 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_roadman = CreatePickup(1275, 23, 1084.0977,-1226.5072,15.8203);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN,1084.0977,-1226.5072,15.8203, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    for(new i = 0; i < MAX_ROADCRASH_TRASH; i++)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "%s\n\nНажмите ALT чтобы положить мешок с мусором", RoadTrashName[i]);
        CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN,RoadTrashCoords[i][0], RoadTrashCoords[i][1], RoadTrashCoords[i][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);
        CreateDynamicPickup(2060, 23, RoadTrashCoords[i][0], RoadTrashCoords[i][1], RoadTrashCoords[i][2]);
    }

    CreateRoadCrash();

    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1109.8462, -1227.2166, 15.4150, 180.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1105.8462, -1227.2166, 15.4150, 180.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1101.8462, -1227.2166, 15.4150, 180.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1097.8462, -1227.2166, 15.4150, 180.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1093.8462, -1227.2166, 15.4150, 180.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1109.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1105.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1101.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1097.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1093.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1089.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ROADMAN, 554, 1085.8462, -1248.7566, 15.4150, 0.0000, 1, 6, 600);

    new tmpobjid;

    // Свалка SF;

    tmpobjid = CreateDynamicObject(16304, -1831.55371, 133.37740, 13.41470, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16304, -1833.14038, 148.12003, 13.16470, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16304, -1831.22913, 160.96342, 12.96470, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);

    tmpobjid = CreateDynamicObject(3171, -1836.50623, 170.68170, 14.10560, 0.00000, 0.00000, 90.00000, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(3626, -1824.74451, 170.68170, 15.58880, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(3722, -1822.64600, 144.22104, 18.48510, 0.00000, 0.00000, 2.04003, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(5291, -1848.97156, 142.61244, 24.96040, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(18248, -1824.50354, 122.41235, 22.14600, 0.00000, 0.00000, 135.84009, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(1358, -1840.40015, 116.74010, 15.30660, 0.00000, 0.00000, 90.00000, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(12957, -1821.69836, 127.45556, 14.82650, 0.00000, 0.00000, 180.00000, -1, -1, -1, 500.00, 500.00);

    // Свалка LV;

    tmpobjid = CreateDynamicObject(16667, 104.55601, 1049.76416, 12.61000, 0.00000, 0.00000, 177.30011, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16667, 96.92258, 1080.46912, 12.61000, 0.00000, 0.00000, 80.17999, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16667, 128.18904, 1067.98779, 12.61000, 0.00000, 0.00000, -83.41991, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(18248, 97.50090, 1058.97998, 20.64280, 0.00000, 0.00000, -5.22000, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(16304, 111.97440, 1062.70398, 12.00390, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16304, 116.60608, 1082.94373, 12.14390, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16304, 109.64448, 1074.09839, 11.42390, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);
    tmpobjid = CreateDynamicObject(16304, 119.12200, 1069.03418, 11.22390, 0.00000, 0.00000, 0.00000, -1, -1, -1, 500.00, 500.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 5122, "ground3_las2", "Was_scrpyd_tires_pile", 0x00000000);

    tmpobjid = CreateDynamicObject(1358, 103.03944, 1082.04102, 13.79760, 0.00000, 0.00000, 128.64021, -1, -1, -1, 500.00, 500.00);
    tmpobjid = CreateDynamicObject(12957, 102.55168, 1056.97925, 13.33980, 0.00000, 0.00000, 43.08012, -1, -1, -1, 500.00, 500.00);
    return 1;
}

CMD:road(playerid, params[])
{
    if(p_info[playerid][job] != JOB_ROADMAN) return SendError(playerid, "Вы не работаете ремонтником дорог.");
    if(p_temp[playerid][Work_ID] != ROADMAN_WORK) return SendError(playerid, "Вы не начали рабочий день.");
    new vehicleid = p_temp[playerid][rented_veh];
    if(vehicleid == INVALID_VEHICLE_ID) return SendError(playerid, "У Вас нет арендованного рабочего транспортного средства.");
    if(veh_info[vehicleid][v_npoType] != NPO_JOB || veh_info[vehicleid][v_npoId] != JOB_ROADMAN) return SendError(playerid, "У Вас нет арендованного рабочего транспортного средства.");
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "[#] Название\tРасстоине\n\
    "I"[1]"W" Начать загрузку\n\
    "I"[2]"W" Начать разгрузку\n\
    "I"[3]"W" Дорожные работы\t%.1f\n\
    "I"[4]"W" Свалка [LS]\t%.1f\n\
    "I"[5]"W" Свалка [SF]\t%.1f\n\
    "I"[6]"W" Свалка [LV]\t%.1f",
    GetPlayerDistanceFromPoint(playerid, RoadCrashCoords[RoadCrashIDx][0], RoadCrashCoords[RoadCrashIDx][1], RoadCrashCoords[RoadCrashIDx][2]),
    GetPlayerDistanceFromPoint(playerid, RoadTrashCoords[0][0], RoadCrashCoords[0][1], RoadCrashCoords[0][2]),
    GetPlayerDistanceFromPoint(playerid, RoadTrashCoords[1][0], RoadCrashCoords[1][1], RoadCrashCoords[1][2]),
    GetPlayerDistanceFromPoint(playerid, RoadTrashCoords[2][0], RoadCrashCoords[2][1], RoadCrashCoords[2][2]));
    ShowPlayerDialog(playerid, D_ROADMAN, DIALOG_STYLE_TABLIST_HEADERS, ""I"Ремонтник дорог", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}