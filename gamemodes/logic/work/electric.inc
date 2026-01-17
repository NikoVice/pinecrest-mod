CheckPowerLines()
{
    for(new i = 0; i < MAX_POWER_LINES; i++)
    {
        if(PowerLinesInfo[i][plPlayerID] == INVALID_PLAYER_ID)
        {
            if(PowerLinesInfo[i][plBreaking] == false && random(2) == 0) PowerLinesInfo[i][plBreaking] = true;
            else if(PowerLinesInfo[i][plBreaking] == true && random(2) == 0) PowerLinesInfo[i][plBreaking] = false;
            if(PowerLinesInfo[i][plMetal] < MAX_VEHICLE_POWER_LINES_COUNT) PowerLinesInfo[i][plMetal] = MAX_VEHICLE_POWER_LINES_COUNT;
            UpdatePowerLines(i);
        }
    }
    return 1;
}

ShowPlayerPowerLines(playerid, idx)
{
    for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
    new idx_city, count;
    STRING_GLOBAL = "[#] Номер\tМестоположение\tРасстояние\n", STRING_MIN[0] = EOS;
    switch(idx)
    {
        case POWER_LINES_TYPE_REPAIR:
        {
            for(new i = 0; i < MAX_POWER_LINES; i++)
            {
                if(PowerLinesInfo[i][plPlayerID] != INVALID_PLAYER_ID) continue;
                if(PowerLinesInfo[i][plBreaking] == false) continue;
                idx_city = GetCityName(PowerLinesInfo[i][plPos][0], PowerLinesInfo[i][plPos][1]);
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" Номер ЛЭП: %d\t%s\t%.1f\n", count + 1, i, gSAZonesCity[idx_city], GetPlayerDistanceFromPoint(playerid, PowerLinesInfo[i][plPos][0], PowerLinesInfo[i][plPos][1], PowerLinesInfo[i][plPos][2]));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0) return SendError(playerid, "Ничего не найдено.");
            ShowPlayerDialog(playerid, D_POWER_LINES, DIALOG_STYLE_TABLIST_HEADERS, ""I"ЛЭП, которым необходим ремонт", STRING_GLOBAL, "Далее", "Отмена");
        }
        case POWER_LINES_TYPE_ROBBING:
        {
            for(new i = 0; i < MAX_POWER_LINES; i++)
            {
                if(PowerLinesInfo[i][plPlayerID] != INVALID_PLAYER_ID) continue;
                if(PowerLinesInfo[i][plBreaking] == true) continue;
                if(PowerLinesInfo[i][plMetal] < MAX_VEHICLE_POWER_LINES_COUNT) continue;
                idx_city = GetCityName(PowerLinesInfo[i][plPos][0], PowerLinesInfo[i][plPos][1]);
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%.1f\n", count + 1, gSAZonesCity[idx_city], GetPlayerDistanceFromPoint(playerid, PowerLinesInfo[i][plPos][0], PowerLinesInfo[i][plPos][1], PowerLinesInfo[i][plPos][2]));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0) return SendError(playerid, "Ничего не найдено.");
            ShowPlayerDialog(playerid, D_POWER_LINES, DIALOG_STYLE_TABLIST_HEADERS, ""I"ЛЭП, которые можно ограбить", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

CheckPlayerElectric(playerid)
{
    new Float:x, Float:y, Float:z, vehicleid = ElectricVehicleIDx[playerid], idx = ElectricIDx[playerid];
    DisablePlayerCheckpoint(playerid);
    switch(ElectricType[playerid])
    {
        case POWER_LINES_TYPE_REPAIR:
        {
            StartElectricMiniGame(playerid, ELECTRIC_TYPE_REPAIR, 10);
        }
        default:
        {
            if(PowerLinesInfo[idx][plRobbing] < MAX_POWER_LINES_STAGE) StartElectricMiniGame(playerid, ELECTRIC_TYPE_ROBBING, 10);
            else
            {
                switch(ElectricAttachedObject[playerid])
                {
                    case 0:
                    {
                        if(PowerLinesInfo[idx][plMetal] == 0)
                        {
                            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                            SendError(playerid, "В ЛЭП больше нет ящиков с металлоломом, отправляйтесь на разгрузку.");
                            SetPlayerCheckpoint(playerid, 2076.8025,-2006.6671,13.5469, 2.5);
                            ElectricAttachedObject[playerid] = 2;
                            return 1;
                        }

                        PowerLinesInfo[idx][plMetal]--;
                        if(PowerLinesInfo[idx][plMetal] < 0) PowerLinesInfo[idx][plMetal] = 0;
                        UpdatePowerLines(idx);
                        ElectricAttachedObject[playerid] = 1;
                        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
                        SetPlayerAttachedObject(playerid, 1, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0, 1.000000, 1.000000, 1.000000);
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
                        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
                        SendMes(playerid, COLOR_SEA_WAVE, "Вы взяли ящик с металлоломом, перенесите его в багажник.");
                        GetCoordBootVehicle(vehicleid, x, y, z);
                        SetPlayerCheckpoint(playerid, x, y, z, 2.5);
                    }
                    case 1:
                    {
                        ElectricAttachedObject[playerid] = 0;
                        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
                        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                        if(veh_info[vehicleid][v_electric_count] + 1 > MAX_VEHICLE_POWER_LINES_COUNT)
                        {
                            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                            SendError(playerid, "В транспортном средстве нет места под еще один ящик с металлоломом, отправляйтесь на разгрузку.");
                            SetPlayerCheckpoint(playerid, 2076.8025,-2006.6671,13.5469, 2.5);
                            ElectricAttachedObject[playerid] = 2;
                            return 1;
                        }
                        veh_info[vehicleid][v_electric_count]++;
                        SendMes(playerid, COLOR_SEA_WAVE, "Вы положили ящик с металлоломом в багажник, возьмите новый и перенесите ещё раз.");
                        SetPlayerCheckpoint(playerid, PowerLinesInfo[idx][plPos][0], PowerLinesInfo[idx][plPos][1], PowerLinesInfo[idx][plPos][2], 2.5);
                    }
                    case 2:
                    {
                        ElectricAttachedObject[playerid] = 3;
                        SendMes(playerid, COLOR_SEA_WAVE, "Вы прибыли к складу, берите ящики с металлоломом из багажника и заполняйте склад.");
                        GetCoordBootVehicle(vehicleid, x, y, z);
                        SetPlayerCheckpoint(playerid, x, y, z, 2.5);
                    }
                    case 3:
                    {
                        if(!veh_info[vehicleid][v_electric_count])
                        {
                            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                            SendError(playerid, "В транспортном средстве нет ящиком с металлоломом, отправляйтесь за зарплатой.");
                            SetPlayerCheckpoint(playerid, -65.1904,-1120.8057,1.0781, 2.5);
                            ElectricAttachedObject[playerid] = 5;
                            return 1;
                        }
                        ElectricAttachedObject[playerid] = 4;
                        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
                        SetPlayerAttachedObject(playerid, 1, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0, 1.000000, 1.000000, 1.000000);
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
                        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
                        SendMes(playerid, COLOR_SEA_WAVE, "Вы взяли ящик с металлоломом, отнесите его на склад.");
                        SetPlayerCheckpoint(playerid, 2076.8025,-2006.6671,13.5469, 2.5);
                    }
                    case 4:
                    {
                        ElectricAttachedObject[playerid] = 3;
                        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
                        ClearAnimations(playerid);
                        ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
                        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
                        if(!veh_info[vehicleid][v_electric_count])
                        {
                            AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];
                            SendError(playerid, "В транспортном средстве больше нет ящиков с металлоломом, отправляйтесь за зарплатой.");
                            SetPlayerCheckpoint(playerid, 1413.4751,-1696.8270,13.5395, 2.5);
                            ElectricAttachedObject[playerid] = 5;
                            return 1;
                        }
                        if(GetPlayerGiveCasket(200, 5) != -1) GivePlayerCasket(playerid, -1);
                        veh_info[vehicleid][v_electric_count]--;
                        SendMes(playerid, COLOR_SEA_WAVE, "Вы положили ящик с металлоломом, возьмите новый и перенесите ещё раз.");
                        GetCoordBootVehicle(vehicleid, x, y, z);
                        SetPlayerCheckpoint(playerid, x, y, z, 2.5);
                    }
                    case 5:
                    {
                        GiveElectricSalary(playerid);

                        veh_info[vehicleid][v_electric_count] = 0;
                    }
                }
            }
        }
    }
    return 1;
}

new pickup_electric;

LoadPowerLines()
{
    CreateActor(50, -76.8532,-1136.7375,1.0781,66.4638);
    CreateDynamic3DTextLabel("NPC: "I"Электрик", COLOR_WHITE, -76.8532,-1136.7375,1.0781 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_electric = CreatePickup(1275, 23, -77.5057,-1136.4799,1.0781);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, -77.5057,-1136.4799,1.0781, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    for(new i; i < MAX_POWER_LINES; i++)
    {
        CreatePickup(1239, 23, PowerLinesInfo[i][plPos][0], PowerLinesInfo[i][plPos][1], PowerLinesInfo[i][plPos][2]);
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "ЛЭП: "W"#%d"I"\n\nСостояние: "W"%s"I"\nСтатус: "W"%s"I"\n\nЭтапов ремонта: "W"%d из %d"I"\nЭтапов взлома: "W"%d из %d"I"\nЯщиков с металлоломом: "W"%d из %d", i, PowerLinesInfo[i][plBreaking] == false ? "{"#cGREEN"}Исправна"W"" : "{"#cLIGHTRED"}Требует ремонта"W"", PowerLinesInfo[i][plPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободна"W"" : "{"#cLIGHTRED"}Используется"W"", PowerLinesInfo[i][plRepair], MAX_POWER_LINES_STAGE, PowerLinesInfo[i][plRobbing], MAX_POWER_LINES_STAGE, PowerLinesInfo[i][plMetal], MAX_VEHICLE_POWER_LINES_COUNT);
        PowerLinesInfo[i][plText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, PowerLinesInfo[i][plPos][0], PowerLinesInfo[i][plPos][1], PowerLinesInfo[i][plPos][2] + 5.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
    }

    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 552, -77.5291, -1106.8051, 0.6970, 160.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 552, -73.6291, -1108.3051, 0.6970, 160.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 552, -69.7291, -1109.8051, 0.6970, 160.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 552, -65.8291, -1111.3051, 0.6970, 160.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 552, -81.0634, -1137.0530, 0.6970, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 552, -85.1634, -1135.1530, 0.6970, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -65.1954, -1144.3551, 1.1124, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -61.1954, -1146.2551, 1.1124, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -57.1954, -1148.1552, 1.1124, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -53.1954, -1150.0551, 1.1124, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -49.1954, -1151.9552, 1.1124, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -45.1954, -1153.8551, 1.1124, -25.0000, 1, 1, 600);
    CreateVehicleVEx(NPO_JOB, JOB_ELECTRIC, 609, -41.1954, -1155.7551, 1.1124, -25.0000, 1, 1, 600);
    return 1;
}

ClearElectricMiniGame(playerid)
{
    p_temp[playerid][electric_mini_game_type] = ELECTRIC_TYPE_NONE;
    p_temp[playerid][electric_mini_game_timer] = 0;
    p_temp[playerid][electric_mini_game_check] = 0;
    p_temp[playerid][electric_mini_game_button] = 0;
    p_temp[playerid][electric_mini_game_error] = 0;
    return 1;
}

StartElectricMiniGame(playerid, type, time)
{
    p_temp[playerid][electric_mini_game_type] = type;
    p_temp[playerid][electric_mini_game_timer] = time;
    p_temp[playerid][electric_mini_game_check] = 10;
    p_temp[playerid][electric_mini_game_button] = random(2);
    ShowTextDrawForPlayer(playerid, TD_ID_ELECTRIC);
    return 1;
}

SuccessElectricMiniGame(playerid)
{
    new idx = ElectricIDx[playerid];
    switch(p_temp[playerid][electric_mini_game_type])
    {
        case ELECTRIC_TYPE_REPAIR:
        {
            PowerLinesInfo[idx][plRepair]++;
            if(PowerLinesInfo[idx][plRepair] >= MAX_POWER_LINES_STAGE)
            {
                GiveElectricSalary(playerid);
                HideTextDrawForPlayer(playerid, TD_ID_ELECTRIC);
            }
            else
            {
                p_temp[playerid][electric_mini_game_timer] = 10;
                SendMes(playerid, COLOR_LYELLOW, "Вы отремонтировали {"#cLIME"}%d из %d{"#cLYELLOW"} частей ЛЭП.", PowerLinesInfo[idx][plRepair], MAX_POWER_LINES_STAGE);
            }
            UpdatePowerLines(idx);
        }
        case ELECTRIC_TYPE_ROBBING:
        {
            PowerLinesInfo[idx][plRobbing]++;
            if(PowerLinesInfo[idx][plRobbing] >= MAX_POWER_LINES_STAGE)
            {
                if(PowerLinesInfo[idx][plRobbing] > MAX_POWER_LINES_STAGE) PowerLinesInfo[idx][plRobbing] = MAX_POWER_LINES_STAGE;
                SendMes(playerid, COLOR_LYELLOW, "Вы отключили {"#cLIME"}%d из %d{"#cLYELLOW"} частей ЛЭП.", PowerLinesInfo[idx][plRobbing], MAX_POWER_LINES_STAGE);
                SendMes(playerid, COLOR_SEA_WAVE, "Вам необходимо загружать ящики с металлоломом в багажник.");
                CancelPlayerGPS(playerid);
                SetPlayerCheckpoint(playerid, PowerLinesInfo[idx][plPos][0], PowerLinesInfo[idx][plPos][1], PowerLinesInfo[idx][plPos][2], 2.5);

                for(new i = 0; i < 3; i++)
                {
                    new scdplayerid = ElectricMembersParty[playerid][i];
                    if(scdplayerid != INVALID_PLAYER_ID)
                    {
                        if(IsPlayerConnected(scdplayerid))
                        {
                            SendMes(scdplayerid, COLOR_SEA_WAVE, "Вам необходимо загружать ящики с металлоломом в багажник.");
                            CancelPlayerGPS(scdplayerid);
                            SetPlayerCheckpoint(scdplayerid, PowerLinesInfo[idx][plPos][0], PowerLinesInfo[idx][plPos][1], PowerLinesInfo[idx][plPos][2], 2.5);
                        }
                    }
                }

                HideTextDrawForPlayer(playerid, TD_ID_ELECTRIC);
            }
            else
            {
                p_temp[playerid][electric_mini_game_timer] = 10;
                SendMes(playerid, COLOR_LYELLOW, "Вы отключили {"#cLIME"}%d из %d{"#cLYELLOW"} частей ЛЭП.", PowerLinesInfo[idx][plRobbing], MAX_POWER_LINES_STAGE);
            }
            UpdatePowerLines(idx);
        }
    }
    return 1;
}

FailedElectricMiniGame(playerid)
{
    new idx = ElectricIDx[playerid];
    if(idx != -1)
    {
        CreateExplosion(PowerLinesInfo[idx][plPos][0], PowerLinesInfo[idx][plPos][1], PowerLinesInfo[idx][plPos][2] + 2.5, 7, 5.0);
        PowerLinesInfo[idx][plRepair] = 0;
    }
    p_temp[playerid][electric_mini_game_timer] = 10;
    p_temp[playerid][electric_mini_game_check] = 10;
    p_temp[playerid][electric_mini_game_error] = 0;
    return 1;
}

Electric_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(p_temp[playerid][TextDrawElectric] == false) return 1;

    if(playertextid == PTD_Electric[playerid][8]) // Закрыть;
    {
        HideTextDrawForPlayer(playerid, TD_ID_ELECTRIC);
        CancelPlayerGPS(playerid);
        new idx = ElectricIDx[playerid];
        if(idx != -1) SetPlayerCheckpoint(playerid, PowerLinesInfo[idx][plPos][0], PowerLinesInfo[idx][plPos][1], PowerLinesInfo[idx][plPos][2], 2.5);
        SetPVarInt(playerid, "USE_OnPlayerEnterCheckpoint", timestamp + 5);
        return 1;
    }

    for(new i = 12; i < 14; i++)
    {
        if(playertextid == PTD_Electric[playerid][i])
        {
            if(p_temp[playerid][electric_mini_game_button] == i - 12)
            {
                p_temp[playerid][electric_mini_game_check] = 5;
                p_temp[playerid][electric_mini_game_button] = random(2);

                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "НАЖМИТЕ НА %s ПРОВОД", p_temp[playerid][electric_mini_game_button] == 0 ? "~r~КРАСНЫЙ~w~" : "~b~СИНИЙ~w~");
                PlayerTextDrawSetString(playerid, PTD_Electric[playerid][6], STRING_GLOBAL);
            }
            else
            {
                p_temp[playerid][electric_mini_game_error]++;
                SendError(playerid, "Неверный провод. Ошибок: %d из %d.", p_temp[playerid][electric_mini_game_error], MAX_ELECTRIC_MINI_GAME_ERROR);
                if(p_temp[playerid][electric_mini_game_error] == MAX_ELECTRIC_MINI_GAME_ERROR)
                {
                    SendError(playerid, "Вы допустили максимальное количество ошибок, попробуйте заново.");
                    FailedElectricMiniGame(playerid);
                }
            }
            return 1;
        }
    }
    return 1;
}

UpdatePowerLines(idx)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "ЛЭП: "W"%d"I"\n\nСостояние: "W"%s"I"\nСтатус: "W"%s"I"\n\nЭтапов ремонта: "W"%d из %d"I"\nЭтапов взлома: "W"%d из %d"I"\nЯщиков с металлоломом: "W"%d из %d", idx, PowerLinesInfo[idx][plBreaking] == false ? "{"#cGREEN"}Исправна"W"" : "{"#cLIGHTRED"}Требует ремонта"W"", PowerLinesInfo[idx][plPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободна"W"" : "{"#cLIGHTRED"}Используется"W"", PowerLinesInfo[idx][plRepair], MAX_POWER_LINES_STAGE, PowerLinesInfo[idx][plRobbing], MAX_POWER_LINES_STAGE, PowerLinesInfo[idx][plMetal], MAX_VEHICLE_POWER_LINES_COUNT);
    UpdateDynamic3DTextLabelText(PowerLinesInfo[idx][plText], COLOR_MAIN, STRING_GLOBAL);
    return 1;
}

GiveElectricSalary(playerid)
{
    new idx = ElectricIDx[playerid], vehicleid = ElectricVehicleIDx[playerid], type = ElectricType[playerid];
    if(idx == -1) return 1;

    PowerLinesInfo[idx][plBreaking] = type == 0 ? false : true;
    PowerLinesInfo[idx][plRepair] = 0;
    PowerLinesInfo[idx][plRobbing] = 0;
    PowerLinesInfo[idx][plMetal] = MAX_VEHICLE_POWER_LINES_COUNT;
    PowerLinesInfo[idx][plPlayerID] = INVALID_PLAYER_ID;

    new index = 1;

    for(new i = 0; i < 3; i++)
    {
        if(ElectricMembersParty[playerid][i] == INVALID_PLAYER_ID) continue;
        index++;
    }

    new salary = type == 0 ? 2333 : 15333;

    if(index > 1) salary = salary + ((salary / 100) * ((10 * index) - 10));

    new newsalary = salary / index;

    ElectricIDx[playerid] = -1;
    ElectricAttachedObject[playerid] = 0;

    UpdatePlayerWorkSkill(playerid, 20);
    new reason_money = GetPlayerMoneySkill(playerid, newsalary, 20),
        vehicle_salary;
    if(veh_info[vehicleid][v_temp_job] == JOB_ELECTRIC)
    {
        vehicle_salary = (reason_money / 100) * 20;
        reason_money += vehicle_salary;
    }

    SendMes(playerid, COLOR_BLUE, "Вы завершили %s.", type == 0 ? "ремонтные работы" : "ограбление");

    if(CheckPlayerMaxSalarySkill(playerid, 20, reason_money))
    {
        SetPlayerMoney(playerid, reason_money, true, "зарплата электрик");
        OnServerInfoForMoney[16] += reason_money;
        SendMes(playerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);
        if(vehicle_salary) SendMes(playerid, COLOR_LIME, "За работу на личном транспортном средстве к заработной плате добавлено: {"#cLYELLOW"}%d$.", vehicle_salary);

        p_info[playerid][job_skill_salary][20] += reason_money;
    }
    else SendError(playerid, "За последний час игры было заработано максимальное количество денежных средств.");

    AntiCheatWarningTime[playerid][2] = timestamp + AntiCheatWarningTime[playerid][1];

    CheckPlayerMission(playerid, START_ELECTRIC);
    CheckPlayerMission(playerid, DAILY_ELECTRIC);
    CheckPlayerMission(playerid, ACHIEVEMENT_ELECTRIC);

    CheckPlayerFreelance(playerid, FREELANCE_ELECTRIC);
    CheckPlayerBattlePass(playerid, BATTLEPASS_ELECTRIC);

    UpdateFamilyLevel(playerid);
    UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_ELECTRIC); // Контракты: Электрик

    for(new i = 0; i < 3; i++)
    {
        if(ElectricMembersParty[playerid][i] == INVALID_PLAYER_ID) continue;
        if(IsPlayerConnected(ElectricMembersParty[playerid][i]))
        {
            new scdplayerid = ElectricMembersParty[playerid][i];
            DisablePlayerCheckpoint(scdplayerid);
            ElectricIDx[scdplayerid] = -1;
            ElectricVehicleIDx[scdplayerid] = INVALID_VEHICLE_ID;
            ElectricAttachedObject[scdplayerid] = 0;

            SendMes(scdplayerid, COLOR_BLUE, "Вы завершили %s.", type == 0 ? "ремонтные работы" : "ограбление");

            UpdatePlayerWorkSkill(scdplayerid, 20);
            new reason_money = GetPlayerMoneySkill(scdplayerid, newsalary, 20);

            if(veh_info[vehicleid][v_temp_job] == JOB_ELECTRIC)
            {
                vehicle_salary = (reason_money / 100) * 20;
                reason_money += vehicle_salary;
            }

            if(CheckPlayerMaxSalarySkill(scdplayerid, 20, reason_money))
            {
                SetPlayerMoney(scdplayerid, reason_money, true, "зарплата электрик");
                OnServerInfoForMoney[16] += reason_money;
                SendMes(scdplayerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);
                if(vehicle_salary) SendMes(scdplayerid, COLOR_LIME, "За работу на личном транспортном средстве к заработной плате добавлено: {"#cLYELLOW"}%d$.", vehicle_salary);

                p_info[scdplayerid][job_skill_salary][20] += reason_money;
            }
            else SendError(scdplayerid, "За последний час игры было заработано максимальное количество денежных средств.");

            AntiCheatWarningTime[scdplayerid][2] = timestamp + AntiCheatWarningTime[scdplayerid][1];

            CheckPlayerMission(scdplayerid, START_ELECTRIC);
            CheckPlayerMission(scdplayerid, DAILY_ELECTRIC);
            CheckPlayerMission(scdplayerid, ACHIEVEMENT_ELECTRIC);

            CheckPlayerFreelance(scdplayerid, FREELANCE_ELECTRIC);
            CheckPlayerBattlePass(scdplayerid, BATTLEPASS_ELECTRIC);

            UpdateFamilyLevel(scdplayerid);
            UpdateFamilyContract(scdplayerid, CONTRACT_FAMILY_ID_ELECTRIC); // Контракты: Электрик

            HideTextDrawForPlayer(scdplayerid, TD_ID_ELECTRIC);
        }
    }
    return 1;
}

CMD:pl(playerid, params[])
{
    if(p_info[playerid][job] != JOB_ELECTRIC) return SendError(playerid, "Вы не работаете электриком.");
    if(p_temp[playerid][Work_ID] != ELECTRIC_WORK) return SendError(playerid, "Вы не начали рабочий день.");
    new vehicleid = p_temp[playerid][rented_veh];
    if(vehicleid == INVALID_VEHICLE_ID) return SendError(playerid, "У Вас нет арендованного рабочего транспортного средства.");
    if(veh_info[vehicleid][v_npoType] != NPO_JOB && veh_info[vehicleid][v_npoId] != JOB_ELECTRIC && veh_info[vehicleid][v_temp_job] != JOB_ELECTRIC) return SendError(playerid, "У Вас нет арендованного рабочего транспортного средства.");
    if(ElectricIDx[playerid] != -1) return SendError(playerid, "У Вас уже есть контракт с ЛЭП.");
    ShowPlayerPowerLines(playerid, ElectricType[playerid]);
    return 1;
}

CMD:pl_test(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckPowerLines();
    return 1;
}
