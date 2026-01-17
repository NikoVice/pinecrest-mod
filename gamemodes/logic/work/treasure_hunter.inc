LoadTreasureHunter()
{
    CreateActor(26, -1061.5729,-1195.4828,129.8281,264.8058);
    CreateDynamic3DTextLabel("NPC: "I"Кладоискатель", COLOR_WHITE, -1061.5729,-1195.4828,129.8281 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_treasure_hunter = CreatePickup(1275, 23, -1060.8900,-1195.4508,129.6736);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, -1060.8900,-1195.4508,129.6736, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    treasure_hunter_zone = GangZoneCreate(-1211, -1067, -995, -903);
    treasure_hunter_cube = CreateDynamicCuboid(-1211,-1067, 127.0, -995,-903, 177.0, -1, -1, -1);
    return 1;
}

SetPlayerTHunter(playerid)
{
    p_temp[playerid][t_hunter_status] = true; // Отображаем металлоискатель;
    p_temp[playerid][t_hunter_x] = -(1194.9597 - random(190)); // Координаты X;
    p_temp[playerid][t_hunter_y] = -(1064.3503 - random(152)); // Координаты Y;
    p_temp[playerid][t_hunter_z] = 129.2188; // Координаты Z;
    if(!SRV_ID) SetPlayerGPS(playerid, p_temp[playerid][t_hunter_x], p_temp[playerid][t_hunter_y], p_temp[playerid][t_hunter_z], 1.0);
    return 1;
}

UpdatePlayerTHunter(playerid)
{
	if(p_temp[playerid][TextDrawTHunterGPS] == false) return 1;
    if(p_temp[playerid][t_hunter_x] == 0 || p_temp[playerid][t_hunter_y] == 0 || p_temp[playerid][t_hunter_z] == 0) return PlayerTextDrawSetString(playerid, PTD_THunterGPS[playerid][6], "Distance: 0.0");
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "Distance: %.1f", GetPlayerDistanceFromPoint(playerid, p_temp[playerid][t_hunter_x], p_temp[playerid][t_hunter_y], p_temp[playerid][t_hunter_z]));
    PlayerTextDrawSetString(playerid, PTD_THunterGPS[playerid][6], STRING_GLOBAL);
	return 1;
}

CMD:tr(playerid, params[])
{
    if(p_temp[playerid][Work_ID] != TREASURE_HUNTER_WORK) return SendError(playerid, "Вы не работаете кладоискателем.");
    new Float:x = p_temp[playerid][t_hunter_x], Float:y = p_temp[playerid][t_hunter_y], Float:z = p_temp[playerid][t_hunter_z];
    if(p_temp[playerid][t_hunter_status] == false || x == 0 || y == 0 || z == 0) return SendError(playerid, "На карте нет отмеченного местоположения клада.");
    if(!IsPlayerInRangeOfPoint(playerid, 3.0, x, y, z)) return SendError(playerid, "Вы слишком далеко от местоположения клада.");
    HideTextDrawForPlayer(playerid, TD_ID_T_HUNTER_GPS);
    ShowTextDrawForPlayer(playerid, TD_ID_T_HUNTER_GAME);
    return 1;
}

THunter_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(p_temp[playerid][TextDrawTHunterGame] == false) return 1;

    if(playertextid == PTD_THunterGame[playerid][30]) // Инфо;
    {
        return 1;
    }
    else if(playertextid == PTD_THunterGame[playerid][32]) // Выход;
    {
        HideTextDrawForPlayer(playerid, TD_ID_T_HUNTER_GAME);
        return 1;
    }

    for(new i = 5; i < 30; i++)
    {
        if(playertextid == PTD_THunterGame[playerid][i])
        {
            if(p_temp[playerid][t_hunter_game] != -1) return 1;
            new idx = floatround(i / 5, floatround_ceil);
            if(p_temp[playerid][t_hunter_idx] == 0 && idx != 1) return SendError(playerid, "Вам необходимо начинать с первой линии.");
            if(p_temp[playerid][t_hunter_idx] > idx) return SendError(playerid, "Вам необходимо открывать ячейки на линии рядом с предыдущей открытой ячейкой или ниже.");
            
            if(p_temp[playerid][t_hunter_last] > 5 && i - p_temp[playerid][t_hunter_last] > 1 && i - p_temp[playerid][t_hunter_last] != 5) return SendError(playerid, "Вам необходимо открывать ячейки на линии рядом с предыдущей открытой ячейкой или ниже.");
            
            p_temp[playerid][t_hunter_last] = i;
            
            p_temp[playerid][t_hunter_idx] = idx;
            new x = p_temp[playerid][t_hunter_button_count];
            p_temp[playerid][t_hunter_button][x] = i;
            p_temp[playerid][t_hunter_button_count]++;

            switch(p_temp[playerid][t_hunter_button_count])
            {
                case 1 .. 3: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_NEXT, i); // 100 процентов далее;
                case 4 .. 6:
                {
                    switch(random(100))
                    {
                        case 0 .. 69: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_NEXT, i); // 70 процентов далее;
                        case 70 .. 84: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_PRIZE, i); // 15 процентов приз;
                        default: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_DYNAMITE, i); // 15 процентов динамит;
                    }
                }
                case 7 .. 9:
                {
                    switch(random(100))
                    {
                        case 0 .. 59: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_NEXT, i); // 60 процентов далее;
                        case 60 .. 89: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_PRIZE, i); // 30 процентов приз;
                        default: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_DYNAMITE, i); // 10 процентов динамит;
                    }
                }
                case 10 .. 12:
                {
                    switch(random(100))
                    {
                        case 0 .. 49: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_NEXT, i); // 50 процентов далее;
                        case 50 .. 94: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_PRIZE, i); // 45 процентов приз;
                        default: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_DYNAMITE, i); // 5 процентов динамит;
                    }
                }
                case 13 .. 15:
                {
                    switch(random(100))
                    {
                        case 0 .. 49: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_NEXT, i); // 50 процентов далее;
                        default: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_PRIZE, i); // 45 процентов приз;
                    }
                }
                default: SetPlayerTHunterButton(playerid, TYPE_T_HUNTER_BUTTON_PRIZE, i); // 100 процентов приз;
            }
            return 1;
        }
    }
    return 1;
}

SetPlayerTHunterButton(playerid, type, idx)
{
    switch(type)
    {
        case TYPE_T_HUNTER_BUTTON_NEXT:
        {
            PlayerTextDrawHide(playerid, PTD_THunterGame[playerid][idx]);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][idx], -2739457);
            PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][idx], false);
            PlayerTextDrawShow(playerid, PTD_THunterGame[playerid][idx]);
        }
        case TYPE_T_HUNTER_BUTTON_DYNAMITE:
        {
            PlayerTextDrawHide(playerid, PTD_THunterGame[playerid][idx]);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][idx], 5);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][idx], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][idx], -454761471);
            PlayerTextDrawSetPreviewModel(playerid, PTD_THunterGame[playerid][idx], 1654);
            PlayerTextDrawSetPreviewRot(playerid, PTD_THunterGame[playerid][idx], 0.000000, 0.000000, 0.000000, 1.000000);
            PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][idx], false);
            PlayerTextDrawShow(playerid, PTD_THunterGame[playerid][idx]);
            ShowPlayerDialog(playerid, D_TREASURE_HUNTER, DIALOG_STYLE_MSGBOX, ""I"Кладоискатель"W" » {"#cLIGHTRED"}Динамит", ""W"К сожалению, Вы откопали динамит. Вам\nнеобходимо начинать всё сначала.", "Закрыть", "");
            p_temp[playerid][t_hunter_game] = TYPE_T_HUNTER_BUTTON_DYNAMITE;
        }
        case TYPE_T_HUNTER_BUTTON_PRIZE:
        {
            PlayerTextDrawHide(playerid, PTD_THunterGame[playerid][idx]);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][idx], 5);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][idx], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][idx], -454761471);
            PlayerTextDrawSetPreviewModel(playerid, PTD_THunterGame[playerid][idx], 1274);
            PlayerTextDrawSetPreviewRot(playerid, PTD_THunterGame[playerid][idx], 0.0000, 0.0000, 0.0000, 1.0000);
            PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][idx], false);
            PlayerTextDrawShow(playerid, PTD_THunterGame[playerid][idx]);
            ShowPlayerDialog(playerid, D_TREASURE_HUNTER, DIALOG_STYLE_MSGBOX, ""I"Кладоискатель"W" » {"#cLIGHTRED"}Деньги", ""W"Поздравляем, Вы нашли деньги!", "Закрыть", "");
            p_temp[playerid][t_hunter_game] = TYPE_T_HUNTER_BUTTON_PRIZE;

            new reason_money = GetPlayerMoneySkill(playerid, 2500, 22);
            if(CheckPlayerMaxSalarySkill(playerid, 22, reason_money))
            {
                SetPlayerMoney(playerid, reason_money, true, "зарплата кладоискатель");
                OnServerInfoForMoney[17] += reason_money;
                SendAccess(playerid, "Вы нашли сокровища.");
                SendMes(playerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.", reason_money);

                p_info[playerid][job_skill_salary][22] += reason_money;
            }
            else SendError(playerid, "За последний час игры было заработано максимальное количество денежных средств.");

            UpdatePlayerWorkSkill(playerid, 22);

            CheckPlayerMission(playerid, START_THUNTER);
            CheckPlayerMission(playerid, DAILY_THUNTER);
            CheckPlayerMission(playerid, ACHIEVEMENT_THUNTER);

            CheckPlayerFreelance(playerid, FREELANCE_THUNTER);
            CheckPlayerBattlePass(playerid, BATTLEPASS_THUNTER);

            UpdateFamilyLevel(playerid);
            UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_THUNTER); // Контракты: Кладоискатель
        }
    }
    return 1;
}

UpdatePlayerTHunterButton(playerid)
{
    for(new i = 0, x; i < 15; i++)
    {
        x = p_temp[playerid][t_hunter_button][i];
        if(x != -1)
        {
            PlayerTextDrawHide(playerid, PTD_THunterGame[playerid][x]);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][x], 4);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][x], 454761471);
            PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][x], true);
            PlayerTextDrawShow(playerid, PTD_THunterGame[playerid][x]);
        }
    }
    return 1;
}

ClearTHunterButton(playerid)
{
    p_temp[playerid][t_hunter_idx] = 0;
    p_temp[playerid][t_hunter_last] = -1;
    p_temp[playerid][t_hunter_button][0] =
    p_temp[playerid][t_hunter_button][1] =
    p_temp[playerid][t_hunter_button][2] =
    p_temp[playerid][t_hunter_button][3] =
    p_temp[playerid][t_hunter_button][4] =
    p_temp[playerid][t_hunter_button][5] =
    p_temp[playerid][t_hunter_button][6] =
    p_temp[playerid][t_hunter_button][7] =
    p_temp[playerid][t_hunter_button][8] =
    p_temp[playerid][t_hunter_button][9] =
    p_temp[playerid][t_hunter_button][10] =
    p_temp[playerid][t_hunter_button][11] =
    p_temp[playerid][t_hunter_button][12] =
    p_temp[playerid][t_hunter_button][13] =
    p_temp[playerid][t_hunter_button][14] = -1;
    p_temp[playerid][t_hunter_button_count] = 0;
    return 1;
}