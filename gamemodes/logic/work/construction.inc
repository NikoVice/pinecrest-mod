new pickup_construction;

new ConstructionJobName[2][32] = {
    "Грузчик",
    "Водитель грузоподъемника"
};

new ConstructionJobInfo[2][128] = {
    "Отправляйтесь на склад, берите стройматериалы и переносите их.",
    "Берите грузоподъмник, отпарвляйтесь на склад и перевозите стройматериалы."
};

new Float:ConstructionWarehousePos[3][3] = {
    {1273.4385,-1326.4064,13.6443},
    {1275.1168,-1307.9821,13.6373},
    {1275.2415,-1293.5662,13.6443}
};

new Float:ConstructionPedPos[4][3] = {
    {1285.3892,-1323.5607,13.7324},
    {1307.9537,-1340.8572,18.7392},
    {1285.3892,-1323.5607,23.7324},
    {1307.9537,-1340.8572,28.7260}
};

new Float:ConstructionVehiclePos[2][3] = {
    {1275.7214,-1357.2610,13.3942},
    {1301.7279,-1380.9591,13.4604}
};

new ConstructionSkill[5] = {0, 15, 30};

LoadConstruction()
{
    CreateVehicleVEx(NPO_JOB, JOB_CONSTRUCTION_FORKLIFT, 530, 1295.8730, -1365.3390, 13.2225, 180.0000, 1, 1, 100);
    CreateVehicleVEx(NPO_JOB, JOB_CONSTRUCTION_FORKLIFT, 530, 1298.8730, -1365.3390, 13.2225, 180.0000, 1, 1, 100);
    CreateVehicleVEx(NPO_JOB, JOB_CONSTRUCTION_FORKLIFT, 530, 1301.8730, -1365.3390, 13.2225, 180.0000, 1, 1, 100);
    CreateVehicleVEx(NPO_JOB, JOB_CONSTRUCTION_FORKLIFT, 530, 1304.8730, -1365.3390, 13.2225, 180.0000, 1, 1, 100);
    CreateVehicleVEx(NPO_JOB, JOB_CONSTRUCTION_FORKLIFT, 530, 1307.8730, -1365.3390, 13.2225, 180.0000, 1, 1, 100);

    pickup_construction = CreatePickup(1275, 23, 1283.0593,-1339.5493,13.7324); // Устройство;
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 1283.0593,-1339.5493,13.7324, 20.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    // Владелец стройки;
    CreateActor(33, 1283.6487,-1339.5048,13.7324,89.9129);
    CreateDynamic3DTextLabel("NPC: "I"Владелец стройки", COLOR_WHITE, 1283.6487,-1339.5048,13.7324 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

GetPlayerStartConstructionJob(playerid, idx)
{
    new str[128];
    if(p_info[playerid][job_skill][3] >= ConstructionSkill[idx]) str = "{"#cGREEN"}Доступно"W"";
    else format(str, sizeof(str), "{"#cLIGHTRED"}Доступно с %d навыка"W"", ConstructionSkill[idx]);
    return str;
}