#define MAX_VEHICLE_ROBBERY_COUNT           10

new RobberIDx[MAX_PLAYERS];
new RobberVehicleIDx[MAX_PLAYERS];
new RobberAttachedObject[MAX_PLAYERS];
new RobberMembersParty[MAX_PLAYERS][3];
new RobberParty[MAX_PLAYERS];

enum RR_INFO
{
    rrObject,
    Float:rrPos[9]
};

new RobberInfo[][RR_INFO] = {
    {19624, {-0.200999, 0.089999, 0.227999, 7.900002, -74.999969, -0.699999, 1.000000, 1.000000, 1.000000}},
    {14772, {0.095000, 0.176000, 0.177999, -83.599937, 2.000003, 99.399993, 1.000000, 1.000000, 1.000000}},
    {2226,  {0.135999, 0.005000, 0.145998, -80.799995, 1.000001, 107.300056, 1.000000, 1.000000, 1.000000}},
    {2103,  {0.128000, 0.016000, 0.111998, -79.600028, 3.700002, 107.499946, 1.000000, 1.000000, 1.000000}},
    {19317, {-0.023999, 0.067000, -0.321000, -172.899993, -18.699998, 5.700000, 1.000000, 1.000000, 1.000000}},
    {19318, {-0.023999, 0.067000, -0.321000, -172.899993, -18.699998, 5.700000, 1.000000, 1.000000, 1.000000}},
    {19319, {-0.023999, 0.067000, -0.321000, -172.899993, -18.699998, 5.700000, 1.000000, 1.000000, 1.000000}},
    {2404,  {0.048999, 0.047999, 0.089998, -169.199951, -19.399999, 5.500001, 1.000000, 1.000000, 1.000000}},
    {2405,  {0.048999, 0.047999, 0.089998, -169.199951, -19.399999, 5.500001, 1.000000, 1.000000, 1.000000}},
    {2406,  {0.048999, 0.047999, 0.089998, -169.199951, -19.399999, 5.500001, 1.000000, 1.000000, 1.000000}},
    {2102,  {0.156000, -0.007000, 0.123998, -80.699996, 1.500000, 108.199989, 1.000000, 1.000000, 1.000000}},
    {11743, {0.237000, -0.001000, 0.096999, -80.800010, -2.499996, 106.699989, 1.000000, 1.000000, 1.000000}},
    {2149,  {0.104999, 0.147999, 0.180999, -80.600006, 4.600001, 107.599975, 1.000000, 1.000000, 1.000000}}
};

SetRobberyHouseCheckpoint(playerid, idx = -1)
{
    if(p_temp[playerid][p_GPS] == true) CancelPlayerGPS(playerid);

    new houseid = GetFreeRobberHouseID();
    if(houseid == -1) return SendError(playerid, "В штате нет доступных домов для ограбления, попробуйте в следующем часе.");

    if(idx == -1) h_info[houseid][h_robbery] = 1;
    else houseid = idx;

    new Float:distance = GetPlayerDistanceFromPoint(playerid, h_info[houseid][h_enter][0], h_info[houseid][h_enter][1], h_info[houseid][h_enter][2]);

    if(idx == -1)
    {
        if(AntiCheatWarningTime[playerid][2] > timestamp) return SendError(playerid, "Вы не можете брать заказы так часто, подождите.");
        RobberIDx[playerid] = houseid;
        new time = floatround(distance) / 500 * 30;
        AntiCheatWarningTime[playerid][0] = timestamp + time;
        AntiCheatWarningTime[playerid][1] = time;
    }

    SendMes(playerid, COLOR_WHITE, "\"Дом № %d\"{"#cBLUE"} отмечен на GPS навигаторе. Расстояние: "W"%.0f{"#cBLUE"} метров.", houseid, distance);
    SetPlayerCheckpoint(playerid, h_info[houseid][h_enter][0], h_info[houseid][h_enter][1], h_info[houseid][h_enter][2], 2.5);

    for(new i = 0; i < 3; i++)
    {
        new scdplayerid = RobberMembersParty[playerid][i];
        if(scdplayerid != INVALID_PLAYER_ID)
        {
            if(IsPlayerConnected(scdplayerid))
            {
                if(idx == -1)
                {
                    new time = floatround(distance) / 500 * 30;
                    AntiCheatWarningTime[scdplayerid][0] = timestamp + time;
                    AntiCheatWarningTime[scdplayerid][1] = time;
                }

                new vehicleid = p_temp[playerid][rented_veh];

                RobberIDx[scdplayerid] = houseid;
                RobberVehicleIDx[scdplayerid] = vehicleid;

                SendMes(scdplayerid, COLOR_WHITE, "\"Дом № %d\"{"#cBLUE"} отмечен на GPS навигаторе. Расстояние: "W"%.0f{"#cBLUE"}", houseid, distance);
                SetPlayerCheckpoint(scdplayerid, h_info[houseid][h_enter][0], h_info[houseid][h_enter][1], h_info[houseid][h_enter][2], 2.5);
            }
        }
    }
    return 1;
}

CheckPlayerRobbery(playerid)
{
    if(RobberAttachedObject[playerid] == 0)
    {
        DisablePlayerCheckpoint(playerid);
        new houseid = RobberIDx[playerid];
        if(h_info[houseid][h_robbery_count] == 0)
        {
            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
            SendMes(playerid, COLOR_DARKORANGE, "В доме больше нет предметов, отправляйтесь на сбыт предметов.");
            SetPlayerCheckpoint(playerid, 1751.4620,-2056.3772,13.8308, 5.0);
            RobberAttachedObject[playerid] = 2;
            return 1;
        }
        h_info[houseid][h_robbery_count]--;
        RobberAttachedObject[playerid] = 1;
        new idx = random(sizeof(RobberInfo));
        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
        SetPlayerAttachedObject(playerid, 1, RobberInfo[idx][rrObject], 5, RobberInfo[idx][rrPos][0], RobberInfo[idx][rrPos][1], RobberInfo[idx][rrPos][2], RobberInfo[idx][rrPos][3], RobberInfo[idx][rrPos][4], RobberInfo[idx][rrPos][5], RobberInfo[idx][rrPos][6], RobberInfo[idx][rrPos][7], RobberInfo[idx][rrPos][8]);
        ClearAnimations(playerid);
        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 0, 1, 1, 0, 0, 1);
        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        SendMes(playerid, COLOR_SEA_WAVE, "Вы взяли предмет из дома, отнесите его в транспортное средство.");
        new vehicleid = RobberVehicleIDx[playerid];
        new Float:x, Float:y, Float:z;
        GetCoordBootVehicle(vehicleid, x, y, z);
        SetPlayerCheckpoint(playerid, x, y, z, 2.5);
    }
    else if(RobberAttachedObject[playerid] == 1)
    {
        DisablePlayerCheckpoint(playerid);
        new vehicleid = RobberVehicleIDx[playerid];
        RobberAttachedObject[playerid] = 0;
        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
        ClearAnimations(playerid);
        ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        if(veh_info[vehicleid][v_robbery_count] + 1 > MAX_VEHICLE_ROBBERY_COUNT)
        {
            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
            SendMes(playerid, COLOR_DARKORANGE, "В транспортном средстве нет места под еще один предмет, отправляйтесь на сбыт предметов.");
            SetPlayerCheckpoint(playerid, 1751.4620,-2056.3772,13.8308, 5.0);
            RobberAttachedObject[playerid] = 2;
            return 1;
        }

        veh_info[vehicleid][v_robbery_count]++;
        new houseid = RobberIDx[playerid];
        SendMes(playerid, COLOR_SEA_WAVE, "Вы положили предмет в транспортное средство, отправляйтесь в дом за новым предметом.");
        SetPlayerCheckpoint(playerid, h_info[houseid][h_enter][0], h_info[houseid][h_enter][1], h_info[houseid][h_enter][2], 2.5);

        if(GetPlayerGiveCasket(200, 5) != -1) GivePlayerCasket(playerid, 720);

        UpdatePlayerWorkSkill(playerid, 5);

        CheckPlayerMission(playerid, START_ROBBER);
        CheckPlayerMission(playerid, DAILY_ROBBER);
        CheckPlayerMission(playerid, ACHIEVEMENT_ROBBER);

        CheckPlayerFreelance(playerid, FREELANCE_ROBBER);
        CheckPlayerBattlePass(playerid, BATTLEPASS_ROBBER);

        UpdateFamilyLevel(playerid);
        UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_ROBBER); // Контракты: Грабитель
    }
    else if(RobberAttachedObject[playerid] == 2)
    {
        new vehicleid = RobberVehicleIDx[playerid], idx = 1;

        for(new i = 0; i < 3; i++)
        {
            if(RobberMembersParty[playerid][i] == INVALID_PLAYER_ID) continue;
            idx++;
        }

        new salary = veh_info[vehicleid][v_robbery_count] * (187 + random(187));

        if(idx > 1) salary = salary + ((salary / 100) * ((10 * idx) - 10));

        new newsalary = salary / idx;

        DisablePlayerCheckpoint(playerid);
        RobberIDx[playerid] = -1;
        RobberAttachedObject[playerid] = 0;

        SendMes(playerid, COLOR_BLUE, "Вы сбыли краденные предметы.");
        new reason_money = GetPlayerMoneySkill(playerid, newsalary, 5);

        if(CheckPlayerMaxSalarySkill(playerid, 5, reason_money))
        {
            SetPlayerMoney(playerid, reason_money, true, "зарплата грабитель");
            OnServerInfoForMoney[16] += reason_money;
            SendMes(playerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);

            p_info[playerid][job_skill_salary][5] += reason_money;
        }
        else SendError(playerid, "За последний час игры было заработано максимальное количество денежных средств.");

        SendMes(playerid, COLOR_SEA_WAVE, "Отправляйтесь за новым заказом.");
        SetPlayerGPS(playerid, 1798.6187,-2050.9958,13.5696, 6.0);

        for(new i = 0; i < 3; i++)
        {
            if(RobberMembersParty[playerid][i] == INVALID_PLAYER_ID) continue;
            if(IsPlayerConnected(RobberMembersParty[playerid][i]))
            {
                new scdplayerid = RobberMembersParty[playerid][i];
                DisablePlayerCheckpoint(scdplayerid);
                RobberIDx[scdplayerid] = -1;
                RobberVehicleIDx[scdplayerid] = INVALID_VEHICLE_ID;
                RobberAttachedObject[scdplayerid] = 0;

                SendMes(scdplayerid, COLOR_BLUE, "Вы сбыли краденные предметы.");
                new reason_money = GetPlayerMoneySkill(scdplayerid, newsalary, 5);

                if(CheckPlayerMaxSalarySkill(scdplayerid, 5, reason_money))
                {
                    SetPlayerMoney(scdplayerid, reason_money, true, "зарплата грабитель");
                    OnServerInfoForMoney[16] += reason_money;
                    SendMes(scdplayerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);

                    p_info[scdplayerid][job_skill_salary][5] += reason_money;
                }
                else SendError(scdplayerid, "За последний час игры было заработано максимальное количество денежных средств.");

                SendMes(scdplayerid, COLOR_SEA_WAVE, "Отправляйтесь за новым заказом.");
                SetPlayerGPS(scdplayerid, 1798.6187,-2050.9958,13.5696, 6.0);
            }
        }

        veh_info[vehicleid][v_robbery_count] = 0;
    }
    return 1;
}

GetFreeRobberHouseID()
{
    new houseid_checked = -1;
    for(new i = totalhouses-1; i != -1; i--)
    {
        if(h_info[i][h_mysql_id] == INVALID_MYSQL_ID) continue;
        if(h_info[i][h_delete] == 1) continue;
        houseid_checked = random(totalhouses-1);
        if(h_info[houseid_checked][h_robbery] == 0) return houseid_checked;
    }
    return -1;
}
