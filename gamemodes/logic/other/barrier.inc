enum E_BARRIERS
{
	bObject,
	bModel,
	Float:bPos[6],
	bFraction,
	bTimer
}

new BarriersInfo[][E_BARRIERS] = {
	{INVALID_OBJECT_ID, 968, {1544.68005, -1630.84265, 13.10100,   0.00000, 90.00000, 90.00000}, 1, 0}, // Полиция ЛС;
	{INVALID_OBJECT_ID, 968, {-1572.20654, 658.73291, 6.86560,   0.00000, 90.00000, 90.00000}, 2, 0}, // Полиция СФ #1;
	{INVALID_OBJECT_ID, 968, {-1701.43103, 687.66730, 24.61510,   0.00000, -90.00000, 90.00000}, 2, 0}, // Полиция СФ #2;
	{INVALID_OBJECT_ID, 968, {2238.20117, 2450.32593, 10.60010,   0.00000, 90.00000, 90.00000}, 3, 0}, // Полиция ЛВ #1;
	{INVALID_OBJECT_ID, 968, {2344.91699, 2422.92236, 10.54980,   0.00000, -90.00000, 180.00000}, 3, 0}, // Полиция ЛВ #2;
	{INVALID_OBJECT_ID, 968, {-2436.92310, 495.42380, 29.74400,   0.00000, 90.00000, 25.00000}, 4, 0}, // ФБР;
	{INVALID_OBJECT_ID, 968, {1266.58496, -1842.47302, 13.18410,   0.00000, 90.00000, 0.00000}, 105, 0}, // Taxi LS #1;
	{INVALID_OBJECT_ID, 968, {1210.28479, -1842.47302, 13.18410,   0.00000, 90.00000, 0.00000}, 105, 0}, // Taxi LS #2;
	{INVALID_OBJECT_ID, 968, {-2196.61548, 309.17319, 34.85700,   0.00000, -90.00000, 0.00000}, 106, 0}, // Taxi SF;
	{INVALID_OBJECT_ID, 968, {2810.20972, 1492.99414, 10.64380,   0.00000, -90.00000, 90.00000}, 107, 0}, // Taxi LV;
	{INVALID_OBJECT_ID, 968, {-494.54599, -561.73218, 25.30500,   0.00000, 90.00000, 0.00000}, 108, 0}, // Trucker #1;
	{INVALID_OBJECT_ID, 968, {-228.18120, -272.85049, 1.16970,   0.00000, -90.00000, 127.00000}, 109, 0}, // Trucker #2;
	{INVALID_OBJECT_ID, 968, {76.12270, -221.90900, 1.38710,   0.00000, -90.00000, -1.20000}, 110, 0}, // Trucker #3;
	{INVALID_OBJECT_ID, 968, {2720.114990, -2408.770019, 13.150919, -0.000007, -90.000000, -89.999977}, 5, 0}, // Национальная гвардия #1;
	{INVALID_OBJECT_ID, 968, {2720.235107, -2507.356201, 13.150919, -0.000029, -90.000000, -89.999908}, 5, 0} // Национальная гвардия #2;
};

CheckBarrier()
{
	for(new i = 0; i < sizeof(BarriersInfo); i++)
	{
		if(BarriersInfo[i][bTimer] < 1) continue;
		BarriersInfo[i][bTimer]--;
		if(BarriersInfo[i][bTimer] < 1)
		{
			BarriersInfo[i][bObject] = CreateDynamicObject(BarriersInfo[i][bModel], BarriersInfo[i][bPos][0], BarriersInfo[i][bPos][1], BarriersInfo[i][bPos][2], BarriersInfo[i][bPos][3], BarriersInfo[i][bPos][4], BarriersInfo[i][bPos][5], -1, -1, -1, 120.0, 120.0);
		}
		/*if(BarriersInfo[i][bTimer] < 1) MoveDynamicObject(BarriersInfo[i][bObject], BarriersInfo[i][bPos][0], BarriersInfo[i][bPos][1], BarriersInfo[i][bPos][2], 0.05, BarriersInfo[i][bPos][3], BarriersInfo[i][bPos][4], BarriersInfo[i][bPos][5]);*/
	}
}

LoadBarrier()
{
	for(new i; i < sizeof(BarriersInfo); i++)
	{
		BarriersInfo[i][bObject] = CreateDynamicObject(BarriersInfo[i][bModel], BarriersInfo[i][bPos][0], BarriersInfo[i][bPos][1], BarriersInfo[i][bPos][2], BarriersInfo[i][bPos][3], BarriersInfo[i][bPos][4], BarriersInfo[i][bPos][5], -1, -1, -1, 120.0, 120.0);
	}
}

SearchBarrier(playerid)
{
	for(new i = 0; i < sizeof(BarriersInfo); i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 7.5, BarriersInfo[i][bPos][0], BarriersInfo[i][bPos][1], BarriersInfo[i][bPos][2]))
		{
			new idx = p_info[playerid][member];
			if(BarriersInfo[i][bFraction] < 100 && BarriersInfo[i][bFraction] == idx ||
				BarriersInfo[i][bFraction] > 100 && (BarriersInfo[i][bFraction] == p_info[playerid][taxi_idx] || BarriersInfo[i][bFraction] == p_info[playerid][tc_idx]) ||
				GetFactionCategory(idx) == FACTION_CATEGORY_FBI ||
				GetFactionCategory(idx) == FACTION_CATEGORY_MAYOR && p_info[playerid][rang] > 4 ||
				BarriersInfo[i][bFraction] == 5 && (gang(playerid) || mafia(playerid) || biker(playerid)))
			{
				if(BarriersInfo[i][bTimer] > 0) return SendError(playerid, "Шлагбаум уже открыт.");
				if(BarriersInfo[i][bObject] != INVALID_OBJECT_ID)
                {
                    DestroyDynamicObject(BarriersInfo[i][bObject]);
                    BarriersInfo[i][bObject] = INVALID_OBJECT_ID;
                }
				/*MoveDynamicObject(BarriersInfo[i][bObject], BarriersInfo[i][bPos][0], BarriersInfo[i][bPos][1], BarriersInfo[i][bPos][2] + 0.05, 0.05, 0.00, 0.00, BarriersInfo[i][bPos][5]);*/
				BarriersInfo[i][bTimer] = 10;
				SendAccess(playerid, "Вы открыли шлагбаум, он закроется через %d сек.", BarriersInfo[i][bTimer]);
				break;
			}
			else return SendError(playerid, "У Вас нет возможности открыть этот шлагбаум.");
		}
	}
	return 1;
}

CMD:gate(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) SearchBarrier(playerid);
    return 1;
}
