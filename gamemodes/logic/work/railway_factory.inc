new pickup_railway_factory[3];

new RailwayJobName[3][32] = {
    "Грузчик",
    "Водитель грузоподъемника",
    "Сварщик"
};

new RailwayJobInfo[3][128] = {
    "Выходите на улицу и разгружайте прицепы.",
    "Выходите на улицу, берите грузоподъемник и разгружайте прицепы.",
    "Отправляйтесь в цех и изготавливайте на станках рельсы."
};

new RailwaySkill[3] = {0, 15, 30};

new RailwayAreasLoad[12];
new RailwayAreasUnload[2];

new bool:RailwayWorkTableStat[12];

new Float:RailwayrWorkCPs[14][3] = {
    {2431.2156,-2521.1023,1013.6172},
    {2431.2151,-2524.7000,1013.6172},
    {2431.2129,-2529.3533,1013.6172},
    {2431.2148,-2532.9800,1013.6172},
    {2431.2085,-2539.7854,1013.6172},
    {2431.2083,-2543.4397,1013.6172},
    {2419.4460,-2543.4072,1013.6172},
    {2419.4463,-2539.8162,1013.6172},
    {2419.4463,-2532.9937,1013.6172},
    {2419.4402,-2529.3958,1013.6172},
    {2419.4399,-2524.7183,1013.6172},
    {2419.4404,-2521.1392,1013.6172},
    {2433.7041,-2507.9360,1013.6172},
    {2417.5815,-2507.9189,1013.6172}
};

LoadRailwayFactory()
{
    pickup_railway_factory[0] = CreatePickup(1318, 23, 2423.5457,-2578.2571,13.8536); // Железнодорожный завод (Вход);
    pickup_railway_factory[1] = CreatePickup(1318, 23, 2422.8950,-2561.1775,1013.6212,1); // Железнодорожный завод (Выход);
    pickup_railway_factory[2] = CreatePickup(1275, 23, 2419.6238,-2557.6926,1013.6212,1); // Железнодорожный завод (Устройство);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 2419.6238,-2557.6926,1013.6212, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    for(new i; i < 14; i++)
    {
        if(i < 12)
        {
            RailwayAreasLoad[i] = CreateDynamicSphere(RailwayrWorkCPs[i][0], RailwayrWorkCPs[i][1], RailwayrWorkCPs[i][2], 0.5, 1, 1, -1);
            UpdateAreaInfo(RailwayAreasLoad[i], TYPE_WORK_RAILWAY_FACTORY, AREA_SUBTYPE_INVALID_ID, i);
        }
        else
        {
            RailwayAreasUnload[i-12] = CreateDynamicSphere(RailwayrWorkCPs[i][0], RailwayrWorkCPs[i][1], RailwayrWorkCPs[i][2], 1.5, 1, 1, -1);
        }
    }
    return 1;
}

GetPlayerStartRailwayJob(playerid, idx)
{
    new str[128];
    if(p_info[playerid][job_skill][0] >= RailwaySkill[idx]) str = "{"#cGREEN"}Доступно"W"";
    else format(str, sizeof(str), "{"#cLIGHTRED"}Доступно с %d навыка"W"", RailwaySkill[idx]);
    return str;
}

forward OnPlayerRailwayReady(playerid, locat);
public OnPlayerRailwayReady(playerid, locat)
{
    RailwayWorkTableStat[locat] = false;
    if(playerid == INVALID_PLAYER_ID) return 1;
    if(!IsPlayerInDynamicArea(playerid, RailwayAreasLoad[locat])) return Fix_TogglePlayerControllable(playerid, true), SendError(playerid, "Вы отошли от станка.");
    p_temp[playerid][RailwayLocat] = 0;
    if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
    if(IsPlayerAttachedObjectSlotUsed(playerid, 2)) RemovePlayerAttachedObject(playerid, 2);
    Fix_TogglePlayerControllable(playerid, true);
    p_temp[playerid][RailwayCheck] ^= 1;
    ClearAnimations(playerid);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
    //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    SetPlayerAttachedObject(playerid, 1, 2960, 1, 0.182999, 0.557998, -0.050000, -0.099999, 99.600082, -4.100028, 0.190000, 0.561999, 0.448999);
    SendMes(playerid, COLOR_SEA_WAVE, "Вы изготовили рельсы. Отнесите их на склад.");

    new max_distance = 100000;
    new warehouse_id = -1;
    new here_distance;
    for(new i = 12; i < 14; i++)
    {
        here_distance = floatround(GetPlayerDistanceFromPoint(playerid, RailwayrWorkCPs[i][0], RailwayrWorkCPs[i][1], RailwayrWorkCPs[i][2]));
        if(here_distance < max_distance)
        {
            warehouse_id = i;
            max_distance = here_distance;
        }
    }
    if(max_distance == -1 || warehouse_id == -1) return 1;

    SetPlayerGPS(playerid, RailwayrWorkCPs[warehouse_id][0], RailwayrWorkCPs[warehouse_id][1], RailwayrWorkCPs[warehouse_id][2], 1.5);
    SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
    return 1;
}