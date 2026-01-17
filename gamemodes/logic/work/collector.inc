#define MAX_VEHICLE_COLLECTOR_COUNT         10
#define MAX_ATM                             18

new CollectorIDx[MAX_PLAYERS];
new CollectorVehicleIDx[MAX_PLAYERS];
new CollectorAttachedObject[MAX_PLAYERS];
new CollectorMembersParty[MAX_PLAYERS][3];
new CollectorParty[MAX_PLAYERS];

enum E_ATM_INFO
{
    aObject,
    aArea,
    aStatus,
    aCount,
    aPlayerID,
    Text3D:aText,
    Float:aPos[4]
}
new ATMInfo[MAX_ATM][E_ATM_INFO] = {
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {-2077.94897, -125.75760, 35.61730, 0.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {-1980.25842, 131.02927, 27.48340, 0.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {-2386.61597, 493.00250, 29.70720, 288.52161}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {-107.09090, -310.23792, 1.25230, 180.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {461.98920, -1508.86011, 30.76500, 351.46783}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {-2636.80640, 634.17188, 14.22720, 0.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {-153.47780, 1172.96216, 19.55880, 270.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {1595.39453, 1819.11182, 10.62090, 270.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {2469.70239, 1542.40186, 10.62130, 179.85010}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {2844.04346, 1286.18652, 11.21110, 270.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {2021.40881, 1016.92340, 10.57630, 90.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {1178.53259, -1305.28589, 13.64590, 90.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {1087.50085, -1803.97375, 13.41100, 270.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {1464.85950, -1750.20325, 15.22060, 270.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {1928.32190, -1780.85754, 13.32810, 180.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {2249.44214, -1667.21741, 15.28110, 254.82269}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {2270.13232, 51.34730, 26.12030, 0.00000}},
    {INVALID_OBJECT_ID, -1, 0, 0, INVALID_PLAYER_ID, Text3D:INVALID_3DTEXT_ID, {1146.52002, -1415.47205, 13.59030, -90.00000}}
};

CheckATM()
{
    for(new i = 0; i < MAX_ATM; i++)
    {
        if(ATMInfo[i][aStatus] == 1) ATMInfo[i][aStatus] = 0, ATMInfo[i][aCount] = 0;
    }
    return 1;
}

ShowPlayerATMList(playerid)
{
    new idx_city;
    STRING_GLOBAL = "[#] Местоположение\tСостояние\tСтатус\tРасстояние\n", STRING_MIN[0] = EOS;
    for(new i = 0; i < MAX_ATM; i++)
    {
        idx_city = GetCityName(ATMInfo[i][aPos][0], ATMInfo[i][aPos][1]);
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%s\t%.1f\n", i + 1, gSAZonesCity[idx_city], ATMInfo[i][aStatus] == 0 ? "{"#cLIGHTRED"}Требует заполнения"W"" : "{"#cGREEN"}Заполнен"W"", ATMInfo[i][aPlayerID] == INVALID_PLAYER_ID ? "{"#cYELLOW"}Готов к выполнению"W"" : "{"#cLIGHTRED"}Выполняется"W"", GetPlayerDistanceFromPoint(playerid, ATMInfo[i][aPos][0], ATMInfo[i][aPos][1], ATMInfo[i][aPos][2]));
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_ATM_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список банкоматов", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CheckPlayerCollector(playerid)
{
    new Float:x, Float:y, Float:z, vehicleid = CollectorVehicleIDx[playerid], atmid = CollectorIDx[playerid];
    DisablePlayerCheckpoint(playerid);
    switch(CollectorAttachedObject[playerid])
    {
        case 0:
        {
            CollectorAttachedObject[playerid] = 1;
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            SetPlayerAttachedObject(playerid, 1, 19624, 5, 0.264999, 0.096000, 0.073999, 2.500007, 109.800048, -175.999816, 1.000000, 1.000000, 1.000000);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            SendMes(playerid, COLOR_SEA_WAVE, "Вы взяли кейс с деньгами, перенесите его в багажник.");
            GetCoordBootVehicle(vehicleid, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 2.5);
        }
        case 1:
        {
            CollectorAttachedObject[playerid] = 0;
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            if(veh_info[vehicleid][v_collector_count] + 1 > MAX_VEHICLE_COLLECTOR_COUNT)
            {
                AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                SendError(playerid, "В транспортном средстве нет места под еще один кейс, отправляйтесь на заполнение банкомата.");
                SetPlayerCheckpoint(playerid, ATMInfo[atmid][aPos][0],ATMInfo[atmid][aPos][1],ATMInfo[atmid][aPos][2], 5.0);
                CollectorAttachedObject[playerid] = 2;
                return 1;
            }
            veh_info[vehicleid][v_collector_count]++;
            SendMes(playerid, COLOR_SEA_WAVE, "Вы положили кейс с деньгами в багажник, возьмите новый и перенесите ещё раз.");
            SetPlayerCheckpoint(playerid, 1362.6382,-1658.9019,13.4751, 2.5);
        }
        case 2:
        {
            CollectorAttachedObject[playerid] = 3;
            SendMes(playerid, COLOR_SEA_WAVE, "Вы прибыли к банкомату, берите кейс с деньгами из багажника и заполняйте банкомат.");
            GetCoordBootVehicle(vehicleid, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 2.5);
        }
        case 3:
        {
            if(!veh_info[vehicleid][v_collector_count])
            {
                AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                SendError(playerid, "В транспортном средстве нет кейсов с деньгами, отправляйтесь за зарплатой.");
                SetPlayerCheckpoint(playerid, 1362.6382,-1651.1910,13.4759, 5.0);
                CollectorAttachedObject[playerid] = 5;
                return 1;
            }
            CollectorAttachedObject[playerid] = 4;
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            SetPlayerAttachedObject(playerid, 1, 19624, 5, 0.264999, 0.096000, 0.073999, 2.500007, 109.800048, -175.999816, 1.000000, 1.000000, 1.000000);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            SendMes(playerid, COLOR_SEA_WAVE, "Вы взяли кейс с деньгами, отнесите его к банкомату.");
            SetPlayerCheckpoint(playerid, ATMInfo[atmid][aPos][0],ATMInfo[atmid][aPos][1],ATMInfo[atmid][aPos][2], 2.5);
        }
        case 4:
        {
            CollectorAttachedObject[playerid] = 3;
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
            if(ATMInfo[atmid][aCount] + 1 > MAX_VEHICLE_COLLECTOR_COUNT)
            {
                AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                SendError(playerid, "В банкомате нет места под еще один кейс, отправляйтесь за зарплатой.");
                SetPlayerCheckpoint(playerid, 1413.4751,-1696.8270,13.5395, 5.0);
                CollectorAttachedObject[playerid] = 5;
                return 1;
            }
            if(GetPlayerGiveCasket(200, 5) != -1) GivePlayerCasket(playerid, -1);
            ATMInfo[atmid][aCount]++;
            veh_info[vehicleid][v_collector_count]--;
            SendMes(playerid, COLOR_SEA_WAVE, "Вы положили кейс с деньгами, возьмите новый и перенесите ещё раз.");
            GetCoordBootVehicle(vehicleid, x, y, z);
            SetPlayerCheckpoint(playerid, x, y, z, 2.5);
        }
        case 5:
        {
            ATMInfo[atmid][aStatus] = 1;
            ATMInfo[atmid][aCount] = 0;
            ATMInfo[atmid][aPlayerID] = INVALID_PLAYER_ID;

            new idx = 1;

            for(new i = 0; i < 3; i++)
            {
                if(CollectorMembersParty[playerid][i] == INVALID_PLAYER_ID) continue;
                idx++;
            }

            new salary, idx_city = GetCityName(ATMInfo[atmid][aPos][0], ATMInfo[atmid][aPos][1]);

            switch(idx_city)
            {
                case 0, 6: salary = 3302;// LS
                case 1 .. 4: salary = 6604; // LV
                case 5, 7, 8: salary = 4953; // SF
            }

            if(idx > 1) salary = salary + ((salary / 100) * ((10 * idx) - 10));

            new newsalary = salary / idx;

            CollectorIDx[playerid] = -1;
            CollectorAttachedObject[playerid] = 0;

            UpdatePlayerWorkSkill(playerid, 13);
            SendMes(playerid, COLOR_BLUE, "Вы пополнили содержимое банкомата #%d.", atmid + 1);
            new reason_money = GetPlayerMoneySkill(playerid, newsalary, 13);

            new vehicle_salary;
            if(veh_info[vehicleid][v_temp_job] == JOB_COLLECTOR)
            {
                vehicle_salary = (reason_money / 100) * 20;
                reason_money += vehicle_salary;
            }

            if(CheckPlayerMaxSalarySkill(playerid, 13, reason_money))
            {
                SetPlayerMoney(playerid, reason_money, true, "зарплата инкассатор");
                OnServerInfoForMoney[16] += reason_money;
                SendMes(playerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);
                if(vehicle_salary) SendMes(playerid, COLOR_LIME, "За работу на личном транспортном средстве к заработной плате добавлено: {"#cLYELLOW"}%d$.", vehicle_salary);

                p_info[playerid][job_skill_salary][13] += reason_money;
            }
            else SendError(playerid, "За последний час игры было заработано максимальное количество денежных средств.");

            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];

            CheckPlayerMission(playerid, START_COLLECTOR);
            CheckPlayerMission(playerid, DAILY_COLLECTOR);
            CheckPlayerMission(playerid, ACHIEVEMENT_COLLECTOR);

            CheckPlayerFreelance(playerid, FREELANCE_COLLECTOR);
            CheckPlayerBattlePass(playerid, BATTLEPASS_COLLECTOR);

            UpdateFamilyLevel(playerid);
            UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_COLLECTOR); // Контракты: Инкассатор

            for(new i = 0; i < 3; i++)
            {
                if(CollectorMembersParty[playerid][i] == INVALID_PLAYER_ID) continue;
                if(IsPlayerConnected(CollectorMembersParty[playerid][i]))
                {
                    new scdplayerid = CollectorMembersParty[playerid][i];
                    DisablePlayerCheckpoint(scdplayerid);
                    CollectorIDx[scdplayerid] = -1;
                    CollectorVehicleIDx[scdplayerid] = INVALID_VEHICLE_ID;
                    CollectorAttachedObject[scdplayerid] = 0;

                    UpdatePlayerWorkSkill(scdplayerid, 13);
                    SendMes(scdplayerid, COLOR_BLUE, "Вы пополнили содержимое банкомата %d.", atmid);
                    new reason_money = GetPlayerMoneySkill(scdplayerid, newsalary, 13);

                    if(veh_info[vehicleid][v_temp_job] == JOB_COLLECTOR)
                    {
                        vehicle_salary = (reason_money / 100) * 20;
                        reason_money += vehicle_salary;
                    }

                    if(CheckPlayerMaxSalarySkill(scdplayerid, 13, reason_money))
                    {
                        SetPlayerMoney(scdplayerid, reason_money, true, "зарплата инкассатор");
                        OnServerInfoForMoney[16] += reason_money;
                        SendMes(scdplayerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);
                        if(vehicle_salary) SendMes(scdplayerid, COLOR_LIME, "За работу на личном транспортном средстве к заработной плате добавлено: {"#cLYELLOW"}%d$.", vehicle_salary);

                        p_info[scdplayerid][job_skill_salary][13] += reason_money;
                    }
                    else SendError(scdplayerid, "За последний час игры было заработано максимальное количество денежных средств.");

                    AntiCheatWarningTime[scdplayerid][2] = timestamp + AntiCheatWarningTime[scdplayerid][1];

                    CheckPlayerMission(scdplayerid, START_COLLECTOR);
                    CheckPlayerMission(scdplayerid, DAILY_COLLECTOR);
                    CheckPlayerMission(scdplayerid, ACHIEVEMENT_COLLECTOR);

                    CheckPlayerFreelance(scdplayerid, FREELANCE_COLLECTOR);
                    CheckPlayerBattlePass(scdplayerid, BATTLEPASS_COLLECTOR);

                    UpdateFamilyLevel(scdplayerid);
                    UpdateFamilyContract(scdplayerid, CONTRACT_FAMILY_ID_COLLECTOR); // Контракты: Инкассатор
                }
            }

            veh_info[vehicleid][v_collector_count] = 0;
        }
    }
    return 1;
}

new pickup_collector;

LoadCollector()
{
    CreateActor(71, 1358.8032,-1647.2524,13.5500,268.4930);
    CreateDynamic3DTextLabel("NPC: "I"Инкассатор", COLOR_WHITE, 1358.8032,-1647.2524,13.5500 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_collector = CreatePickup(1275, 23, 1359.4978,-1647.2091,13.4259);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 1359.4978,-1647.2091,13.4259, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    new areaid = CreateDynamicSphere(1362.6382,-1651.1910,13.4759, 2.5, -1, -1, -1);
    UpdateAreaInfo(areaid, TYPE_COLLECTOR, AREA_SUBTYPE_COLLECTOR_ATM);
    CreateDynamicPickup(19624, 23, 1362.6382,-1651.1910,13.4759);
    CreateDynamic3DTextLabel("<< Список банкоматов >>", COLOR_MAIN, 1362.6382,-1651.1910,13.4759, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    for(new i; i < MAX_ATM; i++)
    {
        ATMInfo[i][aObject] = CreateDynamicObject(2754, ATMInfo[i][aPos][0], ATMInfo[i][aPos][1], ATMInfo[i][aPos][2], 0.0, 0.0, ATMInfo[i][aPos][3], -1,-1,-1, 120.0, 120.0);
        ATMInfo[i][aArea] = CreateDynamicSphere(ATMInfo[i][aPos][0], ATMInfo[i][aPos][1], ATMInfo[i][aPos][2], 1.0, -1, -1, -1);
        UpdateAreaInfo(ATMInfo[i][aArea], TYPE_ATM, AREA_SUBTYPE_ATM, i);
        ATMInfo[i][aText] = CreateDynamic3DTextLabel("БАНКОМАТ", COLOR_MAIN, ATMInfo[i][aPos][0], ATMInfo[i][aPos][1], ATMInfo[i][aPos][2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
    }

    CreateVehicleVEx(NPO_JOB, JOB_COLLECTOR, 428, 1361.5685, -1634.6074, 13.4702, 180.0000, -1, -1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_COLLECTOR, 428, 1365.5685, -1634.6074, 13.4702, 180.0000, -1, -1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_COLLECTOR, 428, 1369.5685, -1634.6074, 13.4702, 180.0000, -1, -1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_COLLECTOR, 428, 1373.5685, -1634.6074, 13.4702, 180.0000, -1, -1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_COLLECTOR, 428, 1373.5685, -1659.9073, 13.4702, 0.0000, -1, -1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_COLLECTOR, 428, 1369.5685, -1659.9073, 13.4702, 0.0000, -1, -1, 600);
    return 1;
}
