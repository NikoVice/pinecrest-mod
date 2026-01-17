#define MAX_MECHANICS_BOTS                  42

enum E_MECHANICS_BOTS
{
    mPlayerID,
    mVehicleIDx,
    mActorIDx,
    Float:mVehiclePos[4],
    Float:mActorPos[4]
};
new MechanicsBots[MAX_MECHANICS_BOTS][E_MECHANICS_BOTS] = {
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2859.4919, -2050.9243, 10.6138, 45.0000}, {2857.9651,-2052.3044,10.9307,44.8579}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2447.4778, -1979.1316, 13.2453, 0.0000}, {2445.6057,-1978.9614,13.5469,357.5909}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2052.5713, -1904.1094, 13.2264, 180.0000}, {2054.3616,-1904.0444,13.5469,181.4724}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1391.5775, -2242.1506, 13.2268, 0.0000}, {1389.7291,-2242.2205,13.5469,0.9303}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1801.5032, -1636.8704, 13.1845, -90.0000}, {1801.6583,-1635.0090,13.5161,267.6400}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2298.0554, -1645.9900, 14.4773, -90.0000}, {2298.0112,-1644.1958,14.7500,271.0867}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2478.3628, -1526.4849, 23.7205, 0.0000}, {2476.5229,-1526.2632,23.9947,0.0978}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2702.5095, -1061.1853, 69.0554, 90.0000}, {2702.5442,-1063.1016,69.3708,88.4350}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2205.5474, -1172.9730, 25.4052, -90.0000}, {2205.5513,-1170.9980,25.7266,270.7734}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1727.9778, -1321.5656, 13.2253, 90.0000}, {1727.8262,-1323.3644,13.5859,87.4951}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {892.6170, -1657.8954, 13.2468, 180.0000}, {894.9083,-1657.8472,13.5469,182.0992}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1015.5469, -1346.9523, 13.0194, 45.0000}, {1014.1783,-1348.3287,13.3660,45.1713}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1104.0979, -934.0840, 42.8583, -45.0000}, {1102.6134,-932.7737,43.1888,317.1472}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {769.6431, -1333.6204, 13.2505, 180.0000}, {771.6498,-1333.5815,13.5424,180.2426}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {334.3803, -1789.1676, 4.6096, 180.0000}, {336.3387,-1789.1899,4.9069,178.6525}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-1760.0336, -183.0282, 3.2455, 0.0000}, {-1762.0219,-182.8996,3.5547,356.9409}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2119.7710, -85.2010, 35.0142, 180.0000}, {-2117.5500,-85.0926,35.3203,182.7260}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2352.1943, -124.8716, 35.0149, 180.0000}, {-2350.1995,-124.7695,35.3125,178.6759}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2783.9019, -282.1750, 6.7110, 180.0000}, {-2782.0188,-282.2368,7.0391,179.5925}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2691.7009, 267.8922, 4.0105, 0.0000}, {-2693.5916,267.8585,4.3359,2.5194}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2592.2561, 660.8062, 27.4917, -90.0000}, {-2592.2009,662.7203,27.8125,269.8569}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2503.9395, 741.5189, 34.7134, 180.0000}, {-2501.8335,741.6022,35.0223,179.3026}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2512.7786, 1209.7230, 37.1207, -90.0000}, {-2512.6968,1211.7921,37.4283,270.7736}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2366.6260, 1025.7317, 50.3930, 180.0000}, {-2364.5444,1025.7836,50.6953,179.9059}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-1651.8751, 1311.3878, 6.7050, 135.0000}, {-1650.2623,1309.6298,7.0319,134.7855}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {-2265.0796, 148.9870, 34.8254, 90.0000}, {-2265.1938,147.0814,35.1641,90.2917}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1913.2089, 708.4154, 10.5178, 0.0000}, {1911.3413,708.5220,10.8203,359.7609}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2636.7393, 730.2416, 10.5150, 0.0000}, {2634.6270,730.2854,10.8203,359.1342}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2813.2546, 896.6038, 10.4427, 0.0000}, {2811.2021,896.4399,10.7578,359.1342}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2450.9836, 1327.0642, 10.4965, 0.0000}, {2449.0051,1327.0826,10.8203,1.3275}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2107.1672, 1440.8002, 10.5165, 90.0000}, {2107.0835,1438.8071,10.8203,93.1352}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2207.5898, 1787.3708, 10.5385, 3.0000}, {2205.4114,1787.2238,10.8203,1.3277}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2463.0371, 1990.8618, 10.4793, 0.0000}, {2460.8049,1990.9387,10.8203,2.5810}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2611.4263, 2279.4392, 10.5157, 90.0000}, {2611.2844,2277.4429,10.8203,87.8084}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2891.3684, 2379.5720, 10.5174, 90.0000}, {2891.4282,2377.6958,10.8203,89.9784}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2104.3916, 2206.4963, 10.5161, 0.0000}, {2102.1714,2206.4475,10.8203,358.8209}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2103.6431, 2052.8672, 10.4985, 90.0000}, {2103.5974,2050.9504,10.8203,87.8084}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {2141.9958, 1009.8024, 10.5191, -90.0000}, {2142.0874,1011.7183,10.8203,268.9624}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1583.8544, 729.0276, 10.5185, -90.0000}, {1583.7771,731.1225,10.8203,272.0268}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1367.9891, 1173.4072, 10.5162, -90.0000}, {1368.0306,1175.3459,10.8203,270.1701}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1059.6058, 1939.2643, 10.5363, 180.0000}, {1061.6890,1939.3231,10.8130,177.1092}},
    {INVALID_PLAYER_ID, INVALID_VEHICLE_ID, -1, {1460.8309, 2374.3848, 10.5190, 180.0000}, {1463.0928,2374.4343,10.8203,177.0858}}
};

CreateMechanic(playerid)
{
    new rand = random(sizeof(MechanicsBots)), index = -1, vehicle_model_idx[22] = {400, 411, 415, 421, 426, 429, 434, 439, 445, 451, 475, 478,  541, 542, 558, 559, 560, 561, 562, 565, 566, 567}, vehicle_model, vehicleid;
    for(new i = 0, idx = -1; i < sizeof(MechanicsBots) * 2; i++)
    {
        idx++;
        if (idx >= sizeof(MechanicsBots)) idx = 0;
        if (MechanicsBots[idx][mPlayerID] != INVALID_PLAYER_ID) continue;
        rand--;
        if(rand <= 0)
        {
            MechanicsBots[idx][mPlayerID] = playerid;

            vehicle_model = vehicle_model_idx[random(sizeof(vehicle_model_idx))];

            MechanicsBots[idx][mVehicleIDx] = CreateVehicleVEx(NPO_MECHANIC_CAR, JOB_MECHANIC_CAR, vehicle_model, MechanicsBots[idx][mVehiclePos][0], MechanicsBots[idx][mVehiclePos][1], MechanicsBots[idx][mVehiclePos][2], MechanicsBots[idx][mVehiclePos][3], random(128), random(128), 3600);

            vehicleid = MechanicsBots[idx][mVehicleIDx];
            veh_info[vehicleid][v_lock] = 1;
            veh_info[vehicleid][v_color] = 1;
            veh_info[vehicleid][v_model] = vehicle_model;
            veh_info[vehicleid][v_fuel] = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_MAX_FUEL);
            for(new i; i < 5; i++) veh_info[vehicleid][v_details][i] = 100.0;
            format(veh_info[vehicleid][v_number], 16, "NULL");
            veh_info[vehicleid][v_int] =
            veh_info[vehicleid][v_virt] =
            veh_info[vehicleid][v_insurance] =
            veh_info[vehicleid][v_insurance_time] = 0;

            veh_info[vehicleid][v_rented_ID] = INVALID_MYSQL_ID;
            veh_info[vehicleid][v_used_key_ID] =
            veh_info[vehicleid][v_thief_ID] = INVALID_PLAYER_ID;

            veh_info[vehicleid][v_engine] = 0;
            SetVehicleParamsVEx(vehicleid, false, false, alarm, true, bonnet, boot, objective);

            SetVehicleHealth(vehicleid, 300.0);
            UpdateVehicleDamageStatus(vehicleid, 0, 7, 0, 15);

            LinkVehicleToInterior(vehicleid, 0);
            SetVehicleVirtualWorld(vehicleid, 0);

            MechanicsBots[idx][mActorIDx] = CreateActor(random(312), MechanicsBots[idx][mActorPos][0], MechanicsBots[idx][mActorPos][1], MechanicsBots[idx][mActorPos][2], MechanicsBots[idx][mActorPos][3]);
            SetActorHealth(MechanicsBots[idx][mActorIDx], 100);
            SetActorVirtualWorld(MechanicsBots[idx][mActorIDx], 0);
            SetActorInvulnerable(MechanicsBots[idx][mActorIDx], true);
            ApplyActorAnimation(MechanicsBots[idx][mActorIDx], "RIOT", "Riot_Chant", 4.1, 1, 0, 0, 0, 0);
            ApplyActorAnimation(MechanicsBots[idx][mActorIDx], "RIOT", "Riot_Chant", 4.1, 1, 0, 0, 0, 0);
            index = idx;
            break;
        }
    }
    if(index == -1)
    {
        p_temp[playerid][mechanic_idx] = 0;
        p_temp[playerid][mechanic_timer] = 10;
        return 1;
    }
    p_temp[playerid][mechanic_idx] = index + 1;
    p_temp[playerid][mechanic_timer] = 600;

    new Float:distance = GetPlayerDistanceFromPoint(playerid, MechanicsBots[index][mVehiclePos][0], MechanicsBots[index][mVehiclePos][1], MechanicsBots[index][mVehiclePos][2]);

    new salary = 0;

    if(distance < 500.0) salary = 657;
    else if(distance > 500.0 && distance < 1000.0) salary = 1053;
    else if(distance > 1000.0 && distance < 1500.0) salary = 1447;
    else if(distance > 1500.0 && distance < 2000.0) salary = 1844;
    else if(distance > 2000.0 && distance < 2500.0) salary = 2238;
    else if(distance > 2500.0 && distance < 3000.0) salary = 2636;
    else if(distance > 3000.0 && distance < 3500.0) salary = 3030;
    else if(distance > 3500.0) salary = 3428;

    new time = floatround(distance) / 500 * 20;

    p_temp[playerid][mechanic_salary] = salary;
    AntiCheatWarningTime[playerid][0] = timestamp + time;

    SetPlayerRaceCheckpoint(playerid, 1, MechanicsBots[index][mVehiclePos][0], MechanicsBots[index][mVehiclePos][1], MechanicsBots[index][mVehiclePos][2], 0, 0, 0, 5);
    SendMes(playerid, COLOR_BLUE, "Сообщение от \"ГЛОНАСС\": "W"На территории {"#cBLUE"}\"San Andreas\""W" обнаружено возгорание транспортного средства.");
    SendMes(playerid, COLOR_LIME, "Местоположение пожара отмечено на Вашем GPS навигаторе.");
    SendMes(playerid, COLOR_SEA_WAVE, "У Вас есть 10 минут чтобы добраться до местоположения транспортного средства и ликвидировать возгорание.");
    return 1;
}

DestroyMechanic(playerid)
{
    if(p_temp[playerid][mechanic_idx] == 0) return 1;
    new idx = p_temp[playerid][mechanic_idx] - 1;
    MechanicsBots[idx][mPlayerID] = INVALID_PLAYER_ID;
    if(MechanicsBots[idx][mActorIDx] != -1)
    {
        DestroyActor(MechanicsBots[idx][mActorIDx]);
        MechanicsBots[idx][mActorIDx] = -1;
    }
    if(MechanicsBots[idx][mVehicleIDx] != INVALID_VEHICLE_ID)
    {
        DestroyVehicleVEx(MechanicsBots[idx][mVehicleIDx]);
        MechanicsBots[idx][mVehicleIDx] = INVALID_VEHICLE_ID;
    }
    return 1;
}

CMD:mcontract(playerid, params[])
{
    if(p_info[playerid][job] != JOB_MECHANIC) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    else if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    else if(!IsPlayerRentedVehicle(playerid, GetPlayerVehicleID(playerid))) return SendError(playerid, "Вы должны находиться в специализированном транспортном средстве.");
    new stringer[208];
    for(new idx; idx < totalbizz; idx++)
    {
        if(b_info[idx][b_mysql_id] == INVALID_MYSQL_ID) continue;
        if(IsPlayerInRangeOfPoint(playerid,5.0,b_info[idx][b_enter][0],b_info[idx][b_enter][1],b_info[idx][b_enter][2]) )
        {
            if(/*b_info[idx][b_user_id] != INVALID_MYSQL_ID && */b_info[idx][_tip] == B_FUEL)
            {
                format(stringer, 208, ""W"Стоимость 1 литра: "I"%d$"W"\n\nВведите кол-во бензина, которое желаете приобрести:\n\n{"#cLIGHTRED"}Обратите внимание! Кол-во литров должно быть не менее 100 и не более 1000.", BIZZ_FILL_PRICE * b_info[idx][_till]);
                ShowPlayerDialog(playerid,D_MEH_CONTRACT,DIALOG_STYLE_INPUT, ""I"Закупка топлива",stringer,"Купить","Отмена");

                SetPVarInt(playerid,"bID",idx);
                return 1;
            }
        }
    }
    SendError(playerid, "Вы слишком далеко от заправки.");
    return 1;
}

CMD:mfuel(playerid, params[])
{
    if(p_info[playerid][job] != JOB_MECHANIC) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    else if(sscanf(params, "uii", params[0], params[1], params[2])) return SendInfo(playerid, "Используйте: /mfill [id игрока] [кол-во топлива] [стоимость]");
    else if(params[2] < 10 || params[2] > 1000) return SendError(playerid, "Стоимость должна быть не менее 10$ и не более 1000$.");
    else if(GetPVarInt(playerid,"toplivo") < params[1]) return SendError(playerid, "У Вас нет столько топлива.");
    else if(!IsPlayerConnected(params[0])) return SendError(playerid, "Игрок не найден.");
    else if(!IsPlayerStream(7.5, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    else if(GetPlayerState(params[0]) != PLAYER_STATE_DRIVER) return SendError(playerid, "Игрок должен находиться в транспортном средстве.");
    else if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    else if(p_temp[playerid][rented_veh] != GetPlayerVehicleID(playerid)) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    else if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    new target_vehicle = GetPlayerVehicleID(params[0]);
    if(target_vehicle == INVALID_VEHICLE_ID || !IsValidVehicle(target_vehicle))
        return SendError(playerid, "Игрок не находится в транспортном средстве.");

    SendAccess(playerid, "Вы предложили %s [%d] заправить транспортное средство на %d литров за %d$.", get_name(params[0]), params[0], params[1], params[2]);
    SendInfo(params[0], "%s [%d] предложил Вам заправить транспортное средство на %d литров за %d$.", get_name(playerid), playerid, params[1], params[2]);

    SetFreeSlotOffer(params[0], playerid, OFFER_ID_VEHICLE_REFILL, params[2], params[1], target_vehicle);
    return 1;
}

CMD:mrepair(playerid, params[])
{
    if(p_info[playerid][job] != JOB_MECHANIC) return SendError(playerid, "Вы не можете пользоваться этой командой.");

    new target, price;
    if(sscanf(params, "ui", target, price)) return SendInfo(playerid, "Используйте: /mrepair [id игрока] [стоимость]");
    if(target == INVALID_PLAYER_ID || target == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!(50 <= price <= 1500))
        return SendError(playerid, "Стоимость ремонта транспортного средства не может быть менее 50$ и более 1500$.");

    if(!IsPlayerStream(7.5, playerid, target) || pSpectateId[target] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок слишком далеко от Вас.");

    if(GetPlayerVehicleID(playerid) != p_temp[playerid][rented_veh])
        return SendError(playerid, "Вы не в рабочем транспортном средстве.");

    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendError(playerid, "Вы должны находиться за рулем транспорта..");

    new target_vehicle = GetPlayerVehicleID(target);
    if(target_vehicle == INVALID_VEHICLE_ID || !IsValidVehicle(target_vehicle))
        return SendError(playerid, "Игрок не находится в транспортном средстве.");

    if(GetPlayerState(target) != PLAYER_STATE_DRIVER)
        return SendError(playerid, "Игрок не является водителем транспортного средства.");

    SendAccess(playerid, "Вы предложили %s [%d] отремонтировать транспортное средство за %d$.", get_name(target), target, price);
    SendInfo(target, "%s [%d] предложил Вам отремонтировать транспортное средство за %d$.", get_name(playerid), playerid, price);

    SetFreeSlotOffer(target, playerid, OFFER_ID_VEHICLE_REPAIR, price, target_vehicle);
    return 1;
}