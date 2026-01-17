AddPlayerCossackRobbers(playerid, idx) // Добавление в команду;
{
	new scdplayerid;
	for(new i = 0; i < MAX_COSSACK_ROBBERS_PLAYERS; i++)
	{
		scdplayerid = CossackRobbersPlayers[idx][i];
		if(scdplayerid == playerid) break;
		if(scdplayerid == INVALID_PLAYER_ID)
		{
			if(p_info[playerid][level] < 2) return SendError(playerid, "Участвовать на мероприятиях можно со 2-ого уровня.");
			p_temp[playerid][cossack_robbers_register] = 1;
			p_temp[playerid][cossack_robbers_team] = idx;
			CossackRobbersPlayers[idx][i] = playerid;
			SendAccess(playerid, "Вы зарегистрировались на участие в казаках разбойниках в %s команде. Пожалуйста ожидайте.", idx == 0 ? "красной" : "синих");
			if(CheckPlayersCountCossackRobbers(CHECK_COSSACK_ROBBERS_MAX) == 1) StartCossackRobbers();
			break;
		}
	}
	return 1;
}

CheckPlayersCountCossackRobbers(idx = 0, sidx = 0) // Проверка на минимальное количество участников в обоих командах;
{
	new count[2];
	for(new i = 0, x = 0; i < MAX_COSSACK_ROBBERS_TEAM; i++)
	{
		for(x = 0; x < MAX_COSSACK_ROBBERS_PLAYERS; x++)
		{
			if(CossackRobbersPlayers[i][x] != INVALID_PLAYER_ID) count[i]++;
		}
	}
	if(idx == CHECK_COSSACK_ROBBERS_MIN && count[0] >= MIN_COSSACK_ROBBERS_PLAYERS && count[1] >= MIN_COSSACK_ROBBERS_PLAYERS) return 1;
	if(idx == CHECK_COSSACK_ROBBERS_MAX && count[0] == MAX_COSSACK_ROBBERS_PLAYERS && count[1] == MAX_COSSACK_ROBBERS_PLAYERS) return 1;
	if(idx == CHECK_COSSACK_ROBBERS_ALL) return count[sidx];
	return -1;
}

ClearPlayerCossackRobbers() // Очистка слотов;
{
	for(new i = 0, x = 0, scdplayerid = INVALID_PLAYER_ID; i < MAX_COSSACK_ROBBERS_TEAM; i++)
	{
		for(x = 0; x < MAX_COSSACK_ROBBERS_PLAYERS; x++)
		{
			scdplayerid = CossackRobbersPlayers[i][x];
			if(scdplayerid != INVALID_PLAYER_ID)
			{
				p_temp[scdplayerid][cossack_robbers_register] = 0;
				CossackRobbersPlayers[i][x] = INVALID_PLAYER_ID;
			}
		}
	}
	return 1;
}

StartCossackRobbers() // Начало;
{
	CossackRobbersStart = false, CossackRobbersPasses = true;

	for(new i = 0, x = 0, scdplayerid = INVALID_PLAYER_ID, team = -1, idx = -1; i < MAX_COSSACK_ROBBERS_TEAM; i++)
	{
		for(x = 0; x < MAX_COSSACK_ROBBERS_PLAYERS; x++)
		{
			scdplayerid = CossackRobbersPlayers[i][x];
			if(scdplayerid != INVALID_PLAYER_ID)
			{
				p_temp[scdplayerid][UnFreezeFix] = 1;
				Fix_TogglePlayerControllable(scdplayerid, 0);
				p_temp[scdplayerid][UnFreezeTimerFix] = timestamp + 1;

				p_temp[scdplayerid][cossack_robbers_register] = 2;
				p_temp[scdplayerid][cossack_robbers_kills] = 0;
				p_temp[scdplayerid][cossack_robbers_deaths] = 0;
				p_temp[scdplayerid][cossack_robbers_give] = 0.0;
				p_temp[scdplayerid][cossack_robbers_take] = 0.0;

				team = p_temp[scdplayerid][cossack_robbers_team], idx = random(MAX_COSSACK_ROBBERS_POS);

				SetPlayerSkin(scdplayerid, CossackRobbersSkin[team]);
				SetPlayerPos(scdplayerid, CossackRobbersPos[CossackRobbersMap][team][idx][0] + random(1), CossackRobbersPos[CossackRobbersMap][team][idx][1] + random(1), CossackRobbersPos[CossackRobbersMap][team][idx][2]);
				SetPlayerFacingAngle(scdplayerid, CossackRobbersPos[CossackRobbersMap][team][idx][3]);
				SetCameraBehindPlayer(scdplayerid);

				SetPlayerInterior(scdplayerid, CossackRobbersMap);
				SetPlayerVirtualWorld(scdplayerid, 250);

				p_info[scdplayerid][pHealth] = 100.0;
				SetPlayerHealth(scdplayerid, 100.0);

				SetPlayerColor(scdplayerid, team == 0 ? COLOR_RED : COLOR_BLUE);

				ResetPlayerWeapons(scdplayerid);
				GivePlayerWeapon(scdplayerid, CossackRobbersWeapon, 9999);

				CheckPlayerMission(scdplayerid, DAILY_MP);
				CheckPlayerMission(scdplayerid, ACHIEVEMENT_MP);

				if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(scdplayerid, 722);

				GameTextForPlayer(scdplayerid, "~g~GO GO GO", 500, 3);

				ShowTextDrawForPlayer(scdplayerid, TD_ID_CAPTURE);
				CaptureInfoUpdate(scdplayerid, CAPTURE_ID_COSSACK_ROBBERS);

				if(GetPlayerAttachedCostume(scdplayerid) != -1)
				{
					SendInfo(scdplayerid, "С Вас снят костюм, он будет надет после завершения меоприятия.");
					TakePlayerAttachedCostume(scdplayerid, GetPlayerAttachedCostume(scdplayerid), false);
				}
				else RemovePlayerAccessories(scdplayerid, false);
			}
		}
	}
	CossackRobbersTime = 600;
	TeleportInMP = false;
	return 1;
}

EndCossackRobbers() // Конец;
{
	if(CossackRobbersPasses == true)
	{
		new team = TEAM_COSSACK_ROBBERS_RED;
		if(CossackRobbersKills[1] > CossackRobbersKills[0]) team = TEAM_COSSACK_ROBBERS_BLUE;

		new count;
		for(new i = 0; i < MAX_COSSACK_ROBBERS_PLAYERS; i++)
		{
			if(CossackRobbersPlayers[team][i] != INVALID_PLAYER_ID) count++;
		}

		SendMesAll(0xFFD700FF, "Внимание! "W"На Казаках-разбойниках победила команда %s. Приз: %d$.", team == 0 ? "красных" : "синих", PRIZE_COSSACK_ROBBERS);

		new prize = PRIZE_COSSACK_ROBBERS / count;

		for(new i = 0, x = 0, scdplayerid = INVALID_PLAYER_ID; i < MAX_COSSACK_ROBBERS_TEAM; i++)
		{
			for(x = 0; x < MAX_COSSACK_ROBBERS_PLAYERS; x++)
			{
				scdplayerid = CossackRobbersPlayers[i][x];
				if(scdplayerid != INVALID_PLAYER_ID)
				{
					SetPlayerHealth(scdplayerid, 100.0);
					SetPlayerInterior(scdplayerid, 0);
					SetPlayerVirtualWorld(scdplayerid, 0);
					SetPlayerPos(scdplayerid, 1421.7180,-1623.7816,13.5469);
					SetPlayerFacingAngle(scdplayerid, 270.0074);
					SetCameraBehindPlayer(scdplayerid);
					SetPlayerSkinEx(scdplayerid);
					if(p_temp[scdplayerid][cossack_robbers_team] == team) SetPlayerMoney(scdplayerid, prize, 1, "победа в Казаках-разбойниках");
					p_temp[scdplayerid][cossack_robbers_register] = 0;
					p_temp[scdplayerid][cossack_robbers_team] = 0;
					p_temp[scdplayerid][cossack_robbers_kills] = 0;
					p_temp[scdplayerid][cossack_robbers_deaths] = 0;
					p_temp[scdplayerid][cossack_robbers_give] = 0;
					p_temp[scdplayerid][cossack_robbers_take] = 0;
					ResetPlayerWeapons(scdplayerid);

					if((p_info[scdplayerid][member] != 0 && p_info[scdplayerid][fwork] == true)) SetPlayerColor(scdplayerid, fraction_color[p_info[scdplayerid][member]]);
					else SetPlayerColor(scdplayerid,  fraction_color[0]);
					if(p_info[scdplayerid][admin] > 0) SetPlayerColor(scdplayerid, 0xFFFFFF00);

					HideTextDrawForPlayer(scdplayerid, TD_ID_CAPTURE);
					CossackRobbersPlayers[i][x] = INVALID_PLAYER_ID;

					AttachToPlayerAccOrCostume(scdplayerid, INVALID_PLAYER_ID);
				}
			}
		}
		CossackRobbersKills[0] =
		CossackRobbersKills[1] = 0;
		CossackRobbersLeaders[0] =
		CossackRobbersLeaders[1] = INVALID_PLAYER_ID;
		CossackRobbersLeadersKills[0] =
		CossackRobbersLeadersKills[1] = 0;
		CossackRobbersTime = 0;
		CossackRobbersMap = 0;
		CossackRobbersWeapon = 22;
		CossackRobbersPasses = false;
	}
	return 1;
}

LoadCossackRobbers()
{
	for(new i = 0, x = 0; i < MAX_COSSACK_ROBBERS_TEAM; i++)
	{
		for(x = 0; x < MAX_COSSACK_ROBBERS_PLAYERS; x++)
		{
			CossackRobbersPlayers[i][x] = INVALID_PLAYER_ID;
		}
	}
	CossackRobbersKills[0] =
	CossackRobbersKills[1] = 0;
	CossackRobbersLeaders[0] =
	CossackRobbersLeaders[1] = INVALID_PLAYER_ID;
	CossackRobbersLeadersKills[0] =
	CossackRobbersLeadersKills[1] = 0;

	// КАСС;
	CreateDynamicObject(11011, 2556.61328, 2789.34326, 13.78100, 0.00000, 0.00000, -90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3887, 2509.49341, 2826.79712, 17.88990, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11444, 2579.29639, 2810.30981, 9.80450, 0.00000, 0.00000, 180.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11441, 2558.38696, 2845.25781, 9.80830, 0.00000, 0.00000, -45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11446, 2561.45117, 2815.67749, 9.80580, 0.00000, 0.00000, 180.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11442, 2596.95508, 2831.33716, 9.80790, 0.00000, 0.00000, -45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11443, 2555.44995, 2826.58276, 9.80930, 0.00000, 0.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11445, 2607.73779, 2822.50977, 9.79060, 0.00000, 0.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11458, 2579.79639, 2840.45093, 9.78950, 0.00000, 0.00000, -45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(18260, 2568.78296, 2830.79297, 11.37720, 0.00000, 0.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3631, 2571.15674, 2815.93652, 10.42230, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, 2583.94116, 2827.81201, 10.52700, 0.00000, 0.00000, 45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11441, 2587.22852, 2820.78345, 9.80830, 0.00000, 0.00000, 45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, 2575.07715, 2822.87646, 10.52700, 0.00000, 0.00000, -45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3631, 2571.15674, 2815.93652, 11.58230, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11442, 2531.95508, 2842.38086, 9.80790, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11443, 2519.47021, 2837.88867, 9.80930, 0.00000, 0.00000, 45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11446, 2534.77100, 2813.51978, 9.80580, 0.00000, 0.00000, 180.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, 2536.08423, 2832.81787, 10.52700, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11445, 2522.45166, 2791.55273, 9.79060, 0.00000, 0.00000, -45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, 2513.62451, 2796.58569, 10.52700, 0.00000, 0.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	// Полигон;
	CreateDynamicObject(11441, -1072.88403, 1077.03967, 2341.04541, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11446, -1027.97876, 1041.47852, 2340.83398, 2.50000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11442, -1102.82642, 1074.87061, 2341.12842, 0.00000, 2.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11443, -1089.13818, 1093.25012, 2341.84229, -8.00000, -8.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11445, -1033.87329, 1026.11194, 2341.85229, 5.00000, 2.50000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11458, -1025.00671, 1091.74731, 2341.95239, -5.00000, -5.00000, -90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, -1022.45752, 1062.81995, 2342.97925, 3.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11441, -1109.63757, 1055.28650, 2341.77905, 3.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11458, -1090.25977, 1031.60645, 2341.92700, 4.00000, -3.00000, 90.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, -1071.65393, 1055.06140, 2343.77539, 0.00000, -3.00000, -45.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, -1092.34424, 1080.12976, 2341.91333, -5.00000, 5.00000, 141.17970, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(12957, -1056.75977, 1049.76526, 2343.61084, -4.00000, -5.00000, -157.85930, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(11442, -999.70520, 1061.97229, 2341.41309, 2.00000, 0.00000, -90.00000, 250, -1, -1, 300.00, 300.00);
	CreateObject(3938, -974.55469, 1059.44531, 2344.77344, 0.00000, 0.00000, 180.00000, 300.00);
	CreateDynamicObject(3940, -974.44531, 1041.53906, 2347.14844, 0.00000, 0.00000, 180.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1596, -973.56250, 1046.07031, 2353.96875, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3950, -991.28912, 1059.63281, 2341.63281, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3925, -1009.75781, 1079.04688, 2340.84375, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3954, -1027.93750, 1070.98438, 2341.33594, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3953, -1024.56250, 1059.04688, 2342.94531, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3952, -1038.98438, 1035.01563, 2343.26563, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3947, -1071.19531, 1059.64063, 2343.26563, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3957, -1071.38281, 1050.05469, 2342.78125, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3949, -1070.12500, 1059.64063, 2343.01563, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3956, -1083.69531, 1071.85938, 2341.96875, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateObject(3960, -1130.85938, 1059.44531, 2345.51563, 0.00000, 0.00000, 0.00000, 300.00);
	CreateDynamicObject(3932, -1131.94531, 1029.14063, 2346.40625, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3941, -1132.10938, 1077.74219, 2347.90625, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(1596, -1132.69531, 1073.99219, 2354.75000, 0.00000, 0.00000, 180.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3933, -1052.60156, 1063.25781, 2347.07813, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3924, -1086.09375, 1061.18750, 2360.57031, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3958, -1142.00781, 1001.91412, 2348.42188, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3951, -1071.19531, 1059.64063, 2343.26563, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3939, -975.04688, 1089.65625, 2345.65625, 0.00000, 0.00000, 180.00000, 250, -1, -1, 300.00, 300.00);
	CreateDynamicObject(3955, -1042.64063, 1072.64063, 2343.85938, 0.00000, 0.00000, 0.00000, 250, -1, -1, 300.00, 300.00);

	for(new i = 0, x = 0, pickupid, idx; i < MAX_COSSACK_ROBBERS_MAP; i++)
	{
		for(x = 0; x < MAX_COSSACK_ROBBERS_PICKUP; x++)
		{
			idx = random(2);
			pickupid = CreateDynamicPickup(idx == 0 ? 1242 : 1240, 3, CossackRobbersPickup[i][x][0], CossackRobbersPickup[i][x][1], CossackRobbersPickup[i][x][2], 250);
			UpdatePickupInfo(pickupid, TYPE_COSSACK_ROBBERS, idx == 0 ? PICKUP_SUBTYPE_COS_ROB_A : PICKUP_SUBTYPE_COS_ROB_H, -1);
		}
	}
	return 1;
}