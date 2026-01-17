#define MAX_HUNTING_DEER            30
#define MAX_HUNTING_VEHICLE_DEER    5

new bool:HuntingStatus[MAX_PLAYERS];
new HuntingIDx[MAX_PLAYERS];
new HuntingVehicleIDx[MAX_PLAYERS];
new HuntingZone[MAX_PLAYERS];
new HuntingTimeCreteDeer[MAX_PLAYERS];
new HuntingTimeKillDeer[MAX_PLAYERS];
new HuntingCount[MAX_PLAYERS];
new HuntingObject[MAX_PLAYERS][5];

enum
{
    HUNTING_DEER_STATUS_NONE = 0,
    HUNTING_DEER_STATUS_CREATE,
    HUNTING_DEER_STATUS_DEATH,
    HUNTING_DEER_STATUS_TAKE,
    HUNTING_DEER_STATUS_TRUNK
}

enum E_HUNTING_INFO
{
    hObject, // -1 - нет объекта;
    hPickup, // -1 - нет пикапа;
    hArea[2], // -1 - нет зоны;
    hStatus,  // 0 - оленя нет, 1 - олень есть, 2 - олень мертвый;
    hPlayerID, // ID игрока, которому был создан олень;
    Float:hPos[6] // X, Y, Z объектов оленя;
};

new HuntingInfo[MAX_HUNTING_DEER][E_HUNTING_INFO] = {
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1629.46936, -2201.29590, 29.16830,   0.00000, 0.00000, 101.76040}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1572.63721, -2235.16211, 13.65530,   0.00000, 0.00000, -46.07990}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1571.22913, -2324.17261, 27.68640,   0.00000, 0.00000, -54.18010}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1520.28210, -2349.73291, 10.97970,   0.00000, 0.00000, 161.75929}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1464.80969, -2370.75122, 16.11810,   0.00000, 0.00000, 90.72010}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1480.39636, -2418.36157, 26.34890,   0.00000, 0.00000, 31.74000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1421.39429, -2351.90479, 26.86110,   0.00000, 0.00000, 112.62020}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1425.77136, -2289.86499, 29.69930,   0.00000, 0.00000, -122.70000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1425.57214, -2219.79517, 25.65070,   0.00000, 0.00000, 103.14030}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1473.15466, -2199.69849, 7.70260,   0.00000, 0.00000, 81.00000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1636.57837, -2310.64551, 58.69050,   0.00000, 0.00000, 0.00000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1556.92578, -2435.65552, 45.79320,   0.00000, 0.00000, 96.60010}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1461.07788, -2490.72363, 52.09920,   0.00000, 0.00000, 0.00000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1420.31384, -2414.15601, 31.24570,   0.00000, 0.00000, -183.18010}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1335.43762, -2378.84619, 32.56330,   0.00000, 0.00000, 18.06000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1375.13464, -2300.07178, 38.36720,   0.00000, 0.00000, 286.73859}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1721.39136, -2261.08984, 48.45200,   0.00000, 0.00000, 35.52000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1749.15234, -2232.90649, 60.22410,   0.00000, 0.00000, -74.28000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1736.24597, -2170.28906, 56.17960,   0.00000, 0.00000, -30.65940}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1779.67139, -2145.53613, 62.95090,   0.00000, 0.00000, 101.40020}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1783.99097, -2212.34863, 71.13100,   0.00000, 0.00000, 33.41980}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1842.77930, -2179.49878, 80.94830,   0.00000, 0.00000, 0.54000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1529.84155, -2116.16577, 16.60740,   0.00000, 0.00000, 23.34000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1548.08496, -2060.42041, 47.75440,   0.00000, 0.00000, -126.18010}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1586.46912, -2085.12085, 42.44210,   0.00000, 0.00000, -7.38010}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1640.29675, -2069.36328, 50.04360,   0.00000, 0.00000, -164.94000}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1609.17358, -2019.17151, 72.75030,   0.00000, 0.00000, 213.23830}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1501.56909, -2014.37573, 45.70280,   0.00000, 0.00000, 36.65990}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1598.62500, -1960.93787, 92.33380,   0.00000, 0.00000, -103.91980}},
    {INVALID_OBJECT_ID, -1, {-1, -1}, HUNTING_DEER_STATUS_NONE, INVALID_PLAYER_ID, {-1689.98364, -1973.01404, 101.46720,   0.00000, 0.00000, -30.54000}}
};

ClearHunting(idx)
{
    if(HuntingInfo[idx][hObject] != INVALID_OBJECT_ID)
    {
        SetObjectPos(HuntingInfo[idx][hObject], HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2] - 5.0);
        SetObjectRot(HuntingInfo[idx][hObject], HuntingInfo[idx][hPos][3], HuntingInfo[idx][hPos][4], HuntingInfo[idx][hPos][5]);
    }
    if(HuntingInfo[idx][hPickup] != -1)
    {
        DestroyDynamicPickup(HuntingInfo[idx][hPickup]);
        HuntingInfo[idx][hPickup] = -1;
    }
    if(HuntingInfo[idx][hArea][1] != -1)
    {
        DestroyDynamicArea(HuntingInfo[idx][hArea][1]);
        HuntingInfo[idx][hArea][1] = -1;
    }
    HuntingInfo[idx][hStatus] = HUNTING_DEER_STATUS_NONE;
    HuntingInfo[idx][hPlayerID] = INVALID_PLAYER_ID;
    return 1;
}

new Float:HuntingVehicleDeerPos[MAX_HUNTING_VEHICLE_DEER][6] = {
    {0.000, -1.071, -0.220, 90.000, 0.000, -90.000},
    {-0.082, -1.764, -0.220, 90.000, 0.000, 70.000},
    {0.243, -1.201, -0.050, 90.000, 0.000, -30.000},
    {0.111, -1.900, -0.050, 90.000, 0.000, 20.000},
    {0.101, -1.489, 0.100, 90.000, 0.000, 90.000}
};

enum
{
    HUNTING_TYPE_CLEAR_ALL = 0,
    HUNTING_TYPE_CLEAR_START,
    HUNTING_TYPE_CLEAR_FINISH,
    HUNTING_TYPE_CLEAR_SELL
}

ClearPlayerHunting(playerid, type = HUNTING_TYPE_CLEAR_ALL)
{
    if(type == HUNTING_TYPE_CLEAR_ALL || type == HUNTING_TYPE_CLEAR_FINISH) HuntingStatus[playerid] = false;
    if(type == HUNTING_TYPE_CLEAR_FINISH && HuntingIDx[playerid] != -1)
    {
        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
        ClearHunting(HuntingIDx[playerid]);
    }
    HuntingIDx[playerid] = -1;
    if(type != HUNTING_TYPE_CLEAR_SELL) HuntingVehicleIDx[playerid] = INVALID_VEHICLE_ID;
    if(type != HUNTING_TYPE_CLEAR_ALL && HuntingZone[playerid] != -1) GangZoneDestroy(HuntingZone[playerid]);
    HuntingZone[playerid] = -1;
    HuntingTimeCreteDeer[playerid] = 0;
    HuntingTimeKillDeer[playerid] = 0;
    HuntingCount[playerid] = 0;
    for(new i = 0; i < MAX_HUNTING_VEHICLE_DEER; i++)
    {
        if((type == HUNTING_TYPE_CLEAR_FINISH || type == HUNTING_TYPE_CLEAR_SELL) && HuntingObject[playerid][i] != INVALID_OBJECT_ID) DestroyDynamicObject(HuntingObject[playerid][i]);
        HuntingObject[playerid][i] = INVALID_OBJECT_ID;
    }
    return 1;
}

CheckPlayerHunting(playerid)
{
    if(HuntingTimeCreteDeer[playerid] > 0 && HuntingIDx[playerid] == -1 && HuntingCount[playerid] < MAX_HUNTING_VEHICLE_DEER)
    {
        HuntingTimeCreteDeer[playerid]--;
        if(HuntingTimeCreteDeer[playerid] == 0)
        {
            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && p_temp[playerid][rented_veh] != INVALID_VEHICLE_ID)
            {
                if(veh_info[p_temp[playerid][rented_veh]][v_npoId] == JOB_HUNTING)
                {
                    if(GetPlayerVehicleID(playerid) == p_temp[playerid][rented_veh])
                    {
                        new idx = GetFreeHuntingID();
                        if(idx == -1)
                        {
                            HuntingTimeCreteDeer[playerid] = RandomEx(15, 30);
                            return 1;
                        }
                        HuntingIDx[playerid] = idx;
                        SetPlayerHunting(playerid);
                    }
                }
            }
            else HuntingTimeCreteDeer[playerid] = RandomEx(15, 30);
        }
    }
    if(HuntingTimeKillDeer[playerid] > 0 && HuntingIDx[playerid] != -1)
    {
        HuntingTimeKillDeer[playerid]--;
        if(HuntingTimeKillDeer[playerid] == 0)
        {
            SendMes(playerid, COLOR_DARKORANGE, "Время не нейтрализацию оленя вышло.");
            SendMes(playerid, COLOR_SEA_WAVE, "Ожидайте информации о местоположениях следующих оленей.");
            new idx = HuntingIDx[playerid];
            ClearHunting(idx);
            HuntingIDx[playerid] = -1;
            HuntingTimeCreteDeer[playerid] = RandomEx(15, 30);
            if(HuntingZone[playerid] != -1) GangZoneDestroy(HuntingZone[playerid]);
            HuntingZone[playerid] = -1;
        }
    }
    return 1;
}

GetFreeHuntingID()
{
    new hunting_checked = -1;
    for(new i = MAX_HUNTING_DEER - 1; i != -1; i--)
    {
        hunting_checked = random(MAX_HUNTING_DEER - 1);
        if(HuntingInfo[hunting_checked][hStatus] == HUNTING_DEER_STATUS_NONE) return hunting_checked;
    }
    return -1;
}

SetPlayerHunting(playerid)
{
    new idx = HuntingIDx[playerid];
    switch(HuntingInfo[idx][hStatus])
    {
        case HUNTING_DEER_STATUS_NONE:
        {
            SendMes(playerid, COLOR_BLUE, "На территории охотничьего лагеря обнаружен олень. Расстояние: "W"%.0f{"#cBLUE"} метров.", GetPlayerDistanceFromPoint(playerid, HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2]));
            SendMes(playerid, COLOR_LIME, "Оленя недавно видели в одном из районов леса, оно отмечено в GPS навигаторе.");
            SendMes(playerid, COLOR_SEA_WAVE, "У Вас есть 3 минуты чтобы нейтрализовать оленя.");
            SendMes(playerid, COLOR_LIME, "Для нейтрализации оленя воспользуйтесь оружием, но не подходите близко, иначе спугнете его.");
            if(HuntingZone[playerid] != -1) GangZoneDestroy(HuntingZone[playerid]);
            HuntingZone[playerid] = GangZoneCreate(HuntingInfo[idx][hPos][0]-95, HuntingInfo[idx][hPos][1]-80, HuntingInfo[idx][hPos][0]+70, HuntingInfo[idx][hPos][1]+85);
            GangZoneShowForPlayer(playerid, HuntingZone[playerid], COLOR_BLACK);
            GangZoneFlashForPlayer(playerid, HuntingZone[playerid], COLOR_RED);
            HuntingTimeKillDeer[playerid] = 180;
            if(HuntingInfo[idx][hObject] != INVALID_OBJECT_ID)
            {
                SetObjectPos(HuntingInfo[idx][hObject], HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2]);
                SetObjectRot(HuntingInfo[idx][hObject], HuntingInfo[idx][hPos][3], HuntingInfo[idx][hPos][4], HuntingInfo[idx][hPos][5]);
            }
            HuntingInfo[idx][hStatus] = HUNTING_DEER_STATUS_CREATE;
            HuntingInfo[idx][hPlayerID] = playerid;
        }
        case HUNTING_DEER_STATUS_CREATE:
        {
            SendMes(playerid, COLOR_SEA_WAVE, "Вы нейтрализовали оленя, заберите его и положите в багажник.");
            if(HuntingInfo[idx][hObject] != INVALID_OBJECT_ID)
            {
                SetObjectPos(HuntingInfo[idx][hObject], HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2] - 5.0);
                SetObjectRot(HuntingInfo[idx][hObject], HuntingInfo[idx][hPos][3], HuntingInfo[idx][hPos][4], HuntingInfo[idx][hPos][5]);
            }
            if(HuntingInfo[idx][hPickup] != -1) DestroyDynamicPickup(HuntingInfo[idx][hPickup]);
            HuntingInfo[idx][hPickup] = CreateDynamicPickup(19315, 23, HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2]);
            if(HuntingInfo[idx][hArea][1] != -1) DestroyDynamicArea(HuntingInfo[idx][hArea][1]);
            HuntingInfo[idx][hArea][1] = CreateDynamicSphere(HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2], 2.5, -1, -1, -1);
            UpdateAreaInfo(HuntingInfo[idx][hArea][1], TYPE_HUNTING, AREA_SUBTYPE_HUNTING_DEER, idx);
            HuntingInfo[idx][hStatus] = HUNTING_DEER_STATUS_DEATH;
            if(HuntingZone[playerid] != -1)
            {
                GangZoneDestroy(HuntingZone[playerid]);
                HuntingZone[playerid] = -1;
            }

            CheckPlayerMission(playerid, START_HUNTING);
            CheckPlayerMission(playerid, DAILY_HUNTING);
            CheckPlayerMission(playerid, ACHIEVEMENT_HUNTING);

            CheckPlayerFreelance(playerid, FREELANCE_HUNTING);
            CheckPlayerBattlePass(playerid, BATTLEPASS_HUNTING);

            UpdateFamilyLevel(playerid);
            UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_HUNTER); // Контракты: Охота
        }
        case HUNTING_DEER_STATUS_DEATH:
        {
            if(HuntingInfo[idx][hPickup] != -1)
            {
                DestroyDynamicPickup(HuntingInfo[idx][hPickup]);
                HuntingInfo[idx][hPickup] = -1;
            }
            if(HuntingInfo[idx][hArea][1] != -1)
            {
                DestroyDynamicArea(HuntingInfo[idx][hArea][1]);
                HuntingInfo[idx][hArea][1] = -1;
            }
            SendMes(playerid, COLOR_SEA_WAVE, "Вы взяли оленя, положите его в багажник.");
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
            SetPlayerAttachedObject(playerid, 1, 19315, 1, 0.111000, 0.507999, 0.185999, -3.399998, 88.400009, -174.499969, 1.000000, 1.000000, 1.000000);
            HuntingInfo[idx][hStatus] = HUNTING_DEER_STATUS_TAKE;
            new vehicleid = HuntingVehicleIDx[playerid], Float:x, Float:y, Float:z;
            GetCoordBootVehicle(vehicleid, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 2.5);
        }
        case HUNTING_DEER_STATUS_TAKE:
        {
            DisablePlayerCheckpoint(playerid);
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            HuntingInfo[idx][hStatus] = HUNTING_DEER_STATUS_NONE;
            if(HuntingCount[playerid] + 1 > MAX_HUNTING_VEHICLE_DEER)
            {
                SetPlayerGPS(playerid, -1331.0237,-2175.0942,24.7060, 6.0);
                SendMes(playerid, COLOR_DARKORANGE, "В багажнике нет места, отвезите оленей в охотничий лагерь и продайте их.");
                SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
                HuntingIDx[playerid] = -1;
                return 1;
            }
            SendMes(playerid, COLOR_BLUE, "Вы положили оленя в багажник.");
            new vehicleid = HuntingVehicleIDx[playerid], deer_idx = HuntingCount[playerid];
            if(HuntingObject[playerid][deer_idx] != INVALID_OBJECT_ID) DestroyDynamicObject(HuntingObject[playerid][deer_idx]);
            HuntingObject[playerid][deer_idx] = CreateDynamicObject(19315, 0, 0, 0, 0, 0, 0);
            AttachDynamicObjectToVehicle(HuntingObject[playerid][deer_idx], vehicleid, HuntingVehicleDeerPos[deer_idx][0], HuntingVehicleDeerPos[deer_idx][1], HuntingVehicleDeerPos[deer_idx][2], HuntingVehicleDeerPos[deer_idx][3], HuntingVehicleDeerPos[deer_idx][4], HuntingVehicleDeerPos[deer_idx][5]);
            HuntingIDx[playerid] = -1;
            HuntingCount[playerid]++;
            HuntingTimeCreteDeer[playerid] = RandomEx(15, 30);
            SendMes(playerid, COLOR_LYELLOW, "Всего оленей в багажнике: {"#cLIME"}%d{"#cLYELLOW"} из {"#cLIME"}%d.", HuntingCount[playerid], MAX_HUNTING_VEHICLE_DEER);
            if(HuntingCount[playerid] == MAX_HUNTING_VEHICLE_DEER)
            {
                SetPlayerGPS(playerid, -1331.0237,-2175.0942,24.7060, 6.0);
                SendMes(playerid, COLOR_DARKORANGE, "В багажнике нет места, отвезите оленей в охотничий лагерь и продайте их.");
                SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
                return 1;
            }
            else SendMes(playerid, COLOR_SEA_WAVE, "Ожидайте информации о местоположениях следующих оленей.");
        }
    }
    return 1;
}

enum
{
    HUNTING_MENU,
    HUNTING_HELP
}

ShowDialogHunting(playerid, type)
{
    switch(type)
    {
        case HUNTING_MENU:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
            "I"[1]"W" %s разрешение на охоту\n\
            "I"[2]"W" Информация о охоте", HuntingStatus[playerid] == false ? "{"#cGREEN"}Получить"W"" : "{"#cLIGHTRED"}Вернуть"W"");
            ShowPlayerDialog(playerid, D_HUNTING_MENU, DIALOG_STYLE_LIST, ""I"Охотничий лагерь", STRING_GLOBAL, "Далее", "Отмена");
        }
        case HUNTING_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i; i < sizeof(HuntingInfoList); i++) strcat(STRING_GLOBAL, HuntingInfoList[i]);
            ShowPlayerDialog(playerid, D_HUNTING_MENU_BACK, DIALOG_STYLE_MSGBOX, ""I"Помощь по охоте", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
    }
    return 1;
}

new pickup_hunting;

LoadHunting()
{
    CreateActor(33, -1314.4869,-2210.4937,25.7308,340.2966);
    CreateDynamic3DTextLabel("NPC: "I"Владелец охотничьего лагеря", COLOR_WHITE, -1314.4869,-2210.4937,25.7308 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_hunting = CreatePickup(1239, 23, -1314.2607,-2209.8271,25.7308);
    CreateDynamic3DTextLabel("<< Начало и завершение охоты >>", COLOR_MAIN, -1314.2607,-2209.8271,25.7308, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    new areaid = CreateDynamicSphere(-1331.0237,-2175.0942,24.7060, 2.5, -1, -1, -1);
    UpdateAreaInfo(areaid, TYPE_HUNTING, AREA_SUBTYPE_HUNTING_WAREHOUSE);
    CreateDynamicPickup(19135, 23, -1331.0237,-2175.0942,24.7060);
    CreateDynamic3DTextLabel("<< Продажа оленей >>", COLOR_MAIN, -1331.0237,-2175.0942,24.7060, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    for(new i = 0; i < MAX_HUNTING_DEER; i++)
    {
        HuntingInfo[i][hObject] = CreateObject(19315, HuntingInfo[i][hPos][0], HuntingInfo[i][hPos][1], HuntingInfo[i][hPos][2] - 5.0, HuntingInfo[i][hPos][3], HuntingInfo[i][hPos][4], HuntingInfo[i][hPos][5], 120.00);
        HuntingInfo[i][hArea][0] = CreateDynamicSphere(HuntingInfo[i][hPos][0], HuntingInfo[i][hPos][1], HuntingInfo[i][hPos][2], 15.0, -1, -1, -1);
        UpdateAreaInfo(HuntingInfo[i][hArea][0], TYPE_HUNTING, AREA_SUBTYPE_HUNTING_ZONE, i);
    }

    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1302.016,-2194.500,24.748,339.632, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1305.238,-2193.253,24.720,339.715, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1308.427,-2192.076,24.722,340.146, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1291.728,-2183.335,24.729,118.814, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1290.164,-2189.929,24.727,110.267, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1300.779,-2201.769,24.731,340.011, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1311.753,-2176.782,24.721,180.324, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1322.187,-2173.847,24.701,179.736, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1342.671,-2173.919,24.730,181.102, 238, 238, 600);
    CreateVehicleVEx(NPO_JOB, JOB_HUNTING, 422, -1287.572,-2198.802,24.726,100.297, 238, 238, 600);
    return 1;
}