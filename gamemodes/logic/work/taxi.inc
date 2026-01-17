#define MAX_TAXI_BOTS                       38

enum E_TAXI_BOTS
{
    tPlayerID,
    tActorIDx,
    Float:tActorPos[4]
};
new TaxiBots[MAX_TAXI_BOTS][E_TAXI_BOTS] = {
    {INVALID_PLAYER_ID, -1, {161.9602,-1745.2522,4.8522,3.4135}},
    {INVALID_PLAYER_ID, -1, {645.4164,-1599.0867,15.6719,88.3511}},
    {INVALID_PLAYER_ID, -1, {1037.8766,-1511.3749,13.5423,255.0460}},
    {INVALID_PLAYER_ID, -1, {1568.0991,-1879.9194,13.5469,0.3268}},
    {INVALID_PLAYER_ID, -1, {2060.0027,-1604.8474,13.5469,181.1218}},
    {INVALID_PLAYER_ID, -1, {2421.3813,-1991.8341,13.5469,90.9044}},
    {INVALID_PLAYER_ID, -1, {2751.5000,-1649.7042,13.0388,177.9885}},
    {INVALID_PLAYER_ID, -1, {2184.7468,-1376.4863,23.9911,181.4353}},
    {INVALID_PLAYER_ID, -1, {1706.9688,-1318.6753,13.5469,271.9895}},
    {INVALID_PLAYER_ID, -1, {1223.6838,-1162.8962,23.3695,90.8811}},
    {INVALID_PLAYER_ID, -1, {609.4760,-1230.1821,18.3426,25.7071}},
    {INVALID_PLAYER_ID, -1, {1046.0367,-945.2986,42.8423,189.2687}},
    {INVALID_PLAYER_ID, -1, {1872.2582,-1042.9006,23.8281,214.0457}},
    {INVALID_PLAYER_ID, -1, {2630.2771,-1055.1022,69.6051,2.5437}},
    {INVALID_PLAYER_ID, -1, {-2699.1016,-185.4676,4.3281,90.9280}},
    {INVALID_PLAYER_ID, -1, {-2413.7437,48.0118,35.1641,92.1813}},
    {INVALID_PLAYER_ID, -1, {-2594.2825,460.8757,14.6094,0.3737}},
    {INVALID_PLAYER_ID, -1, {-1811.3535,615.8490,35.1719,181.1455}},
    {INVALID_PLAYER_ID, -1, {-2538.9939,915.7531,64.9844,180.5188}},
    {INVALID_PLAYER_ID, -1, {-2131.7964,894.7578,80.0000,90.9046}},
    {INVALID_PLAYER_ID, -1, {-1610.2244,1236.5861,7.1875,142.2917}},
    {INVALID_PLAYER_ID, -1, {2257.6890,640.8840,10.8203,181.4588}},
    {INVALID_PLAYER_ID, -1, {1559.2830,1113.4869,10.8203,269.5063}},
    {INVALID_PLAYER_ID, -1, {2435.1770,1293.5328,10.8203,90.8815}},
    {INVALID_PLAYER_ID, -1, {1718.9421,1590.5938,10.3146,260.3730}},
    {INVALID_PLAYER_ID, -1, {999.7819,1930.9186,10.8203,271.6531}},
    {INVALID_PLAYER_ID, -1, {1935.0132,2184.8523,10.8125,91.1714}},
    {INVALID_PLAYER_ID, -1, {2357.1565,2520.9648,10.8203,181.0990}},
    {INVALID_PLAYER_ID, -1, {765.4368,-537.7651,16.3359,2.5671}},
    {INVALID_PLAYER_ID, -1, {265.2504,-64.2771,1.5781,181.7955}},
    {INVALID_PLAYER_ID, -1, {1273.8939,195.3293,19.5547,69.3312}},
    {INVALID_PLAYER_ID, -1, {2386.2776,18.7440,26.4844,272.6865}},
    {INVALID_PLAYER_ID, -1, {-2215.7419,-2414.2100,30.6250,234.7963}},
    {INVALID_PLAYER_ID, -1, {-2443.1938,2340.7607,4.9763,191.5559}},
    {INVALID_PLAYER_ID, -1, {-1471.4445,2593.4919,55.8359,2.3242}},
    {INVALID_PLAYER_ID, -1, {-793.0205,1484.6110,22.4150,1.4075}},
    {INVALID_PLAYER_ID, -1, {-43.0706,1090.6954,19.7422,359.8408}},
    {INVALID_PLAYER_ID, -1, {-208.3792,2708.8843,62.6875,178.7325}}
};

CreateTaxi(playerid)
{
    new rand = random(sizeof(TaxiBots)), index = -1;
    for(new i = 0, idx = -1; i < sizeof(TaxiBots) * 2; i++)
    {
        idx++;
        if (idx >= sizeof(TaxiBots)) idx = 0;
        if (TaxiBots[idx][tPlayerID] != INVALID_PLAYER_ID) continue;
        rand--;
        if(rand <= 0)
        {
            TaxiBots[idx][tPlayerID] = playerid;

            TaxiBots[idx][tActorIDx] = CreateActor(random(312), TaxiBots[idx][tActorPos][0], TaxiBots[idx][tActorPos][1], TaxiBots[idx][tActorPos][2], TaxiBots[idx][tActorPos][3]);
            SetActorHealth(TaxiBots[idx][tActorIDx], 100);
            SetActorVirtualWorld(TaxiBots[idx][tActorIDx], 0);
            SetActorInvulnerable(TaxiBots[idx][tActorIDx], true);
            ApplyActorAnimation(TaxiBots[idx][tActorIDx], "RIOT", "Riot_Chant", 4.1, 1, 0, 0, 0, 0);
            ApplyActorAnimation(TaxiBots[idx][tActorIDx], "RIOT", "Riot_Chant", 4.1, 1, 0, 0, 0, 0);
            index = idx;
            break;
        }
    }
    if(index == -1)
    {
        p_temp[playerid][taxi_bots_idx] = 0;
        p_temp[playerid][taxi_bots_timer] = 10;
        return 1;
    }
    p_temp[playerid][taxi_bots_idx] = index + 1;
    p_temp[playerid][taxi_bots_timer] = 600;
    p_temp[playerid][taxi_bots_gps_idx] = 0;

    new Float:distance = GetPlayerDistanceFromPoint(playerid, TaxiBots[index][tActorPos][0], TaxiBots[index][tActorPos][1], TaxiBots[index][tActorPos][2]);

    new salary = 0;

    if(distance < 500.0) salary = 1005;
    else if(distance > 500.0 && distance < 1000.0) salary = 1611;
    else if(distance > 1000.0 && distance < 1500.0) salary = 2213;
    else if(distance > 1500.0 && distance < 2000.0) salary = 2821;
    else if(distance > 2000.0 && distance < 2500.0) salary = 3424;
    else if(distance > 2500.0 && distance < 3000.0) salary = 4033;
    else if(distance > 3000.0 && distance < 3500.0) salary = 4635;
    else if(distance > 3500.0) salary = 5244;

    new time = floatround(distance) / 500 * 20;

    p_temp[playerid][taxi_bots_salary] = salary;
    AntiCheatWarningTime[playerid][0] = timestamp + time;

    SetPlayerRaceCheckpoint(playerid, 1, TaxiBots[index][tActorPos][0], TaxiBots[index][tActorPos][1], TaxiBots[index][tActorPos][2], 0, 0, 0, 5);
    SendMes(playerid, COLOR_BLUE, "Сообщение от диспетчера: "W"На территории {"#cBLUE"}\"San Andreas\""W" появился новый вызов.");
    SendMes(playerid, COLOR_LIME, "Местоположение клиента отмечено на Вашем GPS навигаторе.");
    SendMes(playerid, COLOR_SEA_WAVE, "У Вас есть 10 минут чтобы добраться до местоположения клиента.");
    return 1;
}

CheckTaxi(playerid)
{
    if(p_temp[playerid][taxi_bots_idx] == 0) return 1;
    new idx = p_temp[playerid][taxi_bots_idx] - 1;
    if(TaxiBots[idx][tActorIDx] != -1)
    {
        DestroyActor(TaxiBots[idx][tActorIDx]);
        TaxiBots[idx][tActorIDx] = -1;
    }

    new index = random(sizeof(frac_info));

    p_temp[playerid][taxi_bots_gps_idx] = index + 1;
    p_temp[playerid][taxi_bots_timer] = 600;

    SetPlayerRaceCheckpoint(playerid, 1, frac_info[index][gps_x], frac_info[index][gps_y], frac_info[index][gps_z], 0, 0, 0, 5);
    SendMes(playerid, COLOR_BLUE, "Вы взяли пассажира, отвезите его.");
    SendMes(playerid, COLOR_LIME, "Место назначения: "W"\"%s\".", frac_info[index][gps_t]);
    SendMes(playerid, COLOR_SEA_WAVE, "У Вас есть 10 минут чтобы добраться до точки назначения.");

    new Float:distance = GetPlayerDistanceFromPoint(playerid, frac_info[index][gps_x], frac_info[index][gps_y], frac_info[index][gps_z]);

    new salary = 0;

    if(distance < 500.0) salary = 724;
    else if(distance > 500.0 && distance < 1000.0) salary = 1161;
    else if(distance > 1000.0 && distance < 1500.0) salary = 1594;
    else if(distance > 1500.0 && distance < 2000.0) salary = 2032;
    else if(distance > 2000.0 && distance < 2500.0) salary = 2467;
    else if(distance > 2500.0 && distance < 3000.0) salary = 2905;
    else if(distance > 3000.0 && distance < 3500.0) salary = 3339;
    else if(distance > 3500.0) salary = 3777;

    new time = floatround(distance) / 500 * 20;

    p_temp[playerid][taxi_bots_salary] += salary;
    AntiCheatWarningTime[playerid][0] = timestamp + time;
    return 1;
}

DestroyTaxi(playerid)
{
    if(p_temp[playerid][taxi_bots_idx] == 0) return 1;
    new idx = p_temp[playerid][taxi_bots_idx] - 1;
    TaxiBots[idx][tPlayerID] = INVALID_PLAYER_ID;
    if(TaxiBots[idx][tActorIDx] != -1)
    {
        DestroyActor(TaxiBots[idx][tActorIDx]);
        TaxiBots[idx][tActorIDx] = -1;
    }
    return 1;
}