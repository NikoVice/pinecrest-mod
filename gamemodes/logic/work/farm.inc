#define MAX_FARM_TREE           30
#define MAX_FARM_TREE_ORANGE    5
#define MAX_FARM_MILKER         10
#define MAX_FARM_WHEAT          90
#define MAX_FARM_WAREHOUSE      3

enum
{
    TYPE_FARM_TREE,
    TYPE_FARM_MILKER,
    TYPE_FARM_WHEAT,
    TYPE_FARM_PRODUCT,
    TYPE_FARM_WAREHOUSE
}

new pickup_farm[3];

new FarmJobName[5][32] = {
    "Сборщик апельсинов",
    "Дояр",
    "Водитель трактора",
    "Водитель комбайна",
    "Развозчик продуктов"
};

new FarmJobInfo[5][128] = {
    "Выходите на улицу, отправляйтесь на поле и собирайте апельсины с деревьев.",
    "Выходите на улицу, заходите в коровник и доите коров, но будьте осторожны, они могут испугаться.",
    "Выходите на улицу, берите трактор и отправляйтесь на поле для дальнейшего посева пшеницы.",
    "Выходите на улицу, берите комбайн и отправляйтесь на поле для дальнейшего сбора пшеницы.",
    "Выходите на улицу, берите продуктовоз, берите заказ и выполняйте его."
};

new Float:FarmJobPos[5][3] = {
    {-284.3218,-1517.4755,6.7385},
    {-402.8337,-1443.4399,25.7991},
    {-387.1915,-1428.0400,25.7266},
    {-382.7196,-1392.8700,23.3814},
    {-372.2232,-1445.9238,25.7266}
};

new FarmWarehouseName[3][32] = {
    "Склад апельсинов",
    "Склад молока",
    "Склад продуктов"
};

new FarmJobWarehouseInfo[4][128] = {
    "Возвращайтесь на поле и собирайте апельсины с деревьев.",
    "Возвращайтесь в коровник и продолжайте доить коров.",
    "Продолжайте искать места, где требуется посев или сбор пшеницы.",
    "Возвращайтесь на ферму, берите заказ и выполняйте его."
};

new Float:FarmJobWarehousePos[4][3] = {
    {-284.3218,-1517.4755,6.7385},
    {-402.8337,-1443.4399,25.7991},
    {0.0,0.0,0.0},
    {-375.0554,-1448.7446,25.9800}
};

new FarmSkill[5] = {0, 5, 10, 20, 30};

enum E_FARM_TREE_INFO
{
    ftObject,
    ftPlayerID,
    ftArea,
    ftRespawn[5],
    ftOrange[5],
    Text3D:ftText
}
new FarmTreeInfo[MAX_FARM_TREE][E_FARM_TREE_INFO];

enum E_FARM_MILKER_INFO
{
    fmObject,
    fmStatus, // 0 - дает молоко, 1 - не дает молоко
    Float:fmMood,
    fmPlayerID,
    fmPickup,
    fmArea,
    Text3D:fmText
}
new FarmMilkerInfo[MAX_FARM_MILKER][E_FARM_MILKER_INFO];

enum E_FARM_WHEAT_INFO
{
    fwObject,
    fwArea,
    fwRespawn, // 0 - нет, 1 - пшеница посажена, 2 - пшеница выросла
    Text3D:fwText
}
new FarmWheatInfo[MAX_FARM_WHEAT][E_FARM_WHEAT_INFO];

new Float:FarmTreePos[MAX_FARM_TREE][3] = {
    {-333.896697, -1468.431640, 10.810770},
    {-313.896697, -1468.431640, 6.670770},
    {-293.896697, -1468.431640, 2.890770},
    {-273.896697, -1468.431640, -0.709229},
    {-253.896697, -1468.431640, -0.569228},
    {-233.896697, -1468.431640, 0.410771},
    {-333.896697, -1488.431640, 10.190772},
    {-313.896697, -1488.431640, 7.490771},
    {-293.896697, -1488.431640, 3.730770},
    {-273.896697, -1488.431640, 0.242071},
    {-253.896697, -1488.431640, 1.546070},
    {-233.896697, -1488.431640, 2.290770},
    {-333.896697, -1508.431640, 10.390770},
    {-313.896697, -1508.431640, 7.470770},
    {-293.896697, -1508.431640, 3.990771},
    {-273.896697, -1508.431640, 0.502071},
    {-253.896697, -1508.431640, 1.846071},
    {-233.896697, -1508.431640, 2.630771},
    {-333.896697, -1528.431640, 10.950772},
    {-313.896697, -1528.431640, 7.890770},
    {-293.896697, -1528.431640, 4.310770},
    {-273.896697, -1528.431640, 0.302071},
    {-253.896697, -1528.431640, 1.666070},
    {-233.896697, -1528.431640, 2.510771},
    {-333.896697, -1548.431640, 11.870772},
    {-313.896697, -1548.431640, 7.990771},
    {-293.896697, -1548.431640, 4.170771},
    {-273.896697, -1548.431640, 0.002071},
    {-253.896697, -1548.431640, -0.813928},
    {-233.896697, -1548.431640, 0.930770}
};

new Float:FarmMilkerPos[MAX_FARM_MILKER][6] = {
    {-407.219726, -1444.662231, 24.736900, 0.000014, -0.000008, 94.999938},
    {-407.219726, -1448.663696, 24.736900, 0.000022, -0.000009, 94.999916},
    {-407.219726, -1452.665405, 24.736900, 0.000029, -0.000010, 94.999893},
    {-407.219726, -1456.665649, 24.736900, 0.000037, -0.000010, 94.999870},
    {-407.219726, -1460.666870, 24.736900, 0.000044, -0.000011, 94.999847},
    {-398.392181, -1461.924194, 24.736900, 0.000014, -0.000008, -85.000030},
    {-398.392181, -1457.922729, 24.736900, 0.000022, -0.000009, -85.000053},
    {-398.392181, -1453.921020, 24.736900, 0.000029, -0.000010, -85.000076},
    {-398.392181, -1449.920776, 24.736900, 0.000037, -0.000010, -85.000099},
    {-398.392181, -1445.919555, 24.736900, 0.000044, -0.000011, -85.000122}
};

new Float:FarmWheatPos[MAX_FARM_WHEAT][6] = {
    {-327.86188, -1428.20825, 15.67920, 0.00000, 0.00000, 0.00000},
    {-312.86191, -1428.20825, 15.27920, 0.00000, 0.00000, 0.00000},
    {-297.86191, -1428.20825, 14.53920, 0.00000, 5.00000, 0.00000},
    {-282.86191, -1428.20825, 12.29920, 5.00000, 7.50000, 0.00000},
    {-267.86191, -1428.20825, 10.39920, 0.00000, 7.50000, 0.00000},
    {-252.86189, -1426.20825, 8.01920, 0.00000, 7.50000, 0.00000},
    {-237.86189, -1424.20825, 6.41920, 5.00000, 7.50000, 0.00000},
    {-222.86189, -1421.20825, 5.47920, 7.50000, 7.50000, 0.00000},
    {-207.86189, -1419.20825, 4.21920, 7.50000, 7.50000, 0.00000},
    {-192.86189, -1417.20825, 3.81920, 7.50000, 2.50000, 0.00000},
    {-177.86189, -1414.20825, 3.53920, 2.50000, 2.50000, 0.00000},
    {-162.86189, -1412.20825, 3.55920, 2.50000, 2.50000, 0.00000},
    {-165.86189, -1397.20825, 3.53920, 2.50000, 2.50000, 0.00000},
    {-180.86189, -1399.20825, 4.45920, 7.50000, 5.00000, 0.00000},
    {-195.86189, -1402.20825, 5.55920, 10.00000, 7.50000, 0.00000},
    {-210.86189, -1404.20825, 6.69920, 12.50000, 7.50000, 0.00000},
    {-225.86189, -1406.20825, 8.09920, 10.00000, 7.50000, 0.00000},
    {-240.86189, -1409.20825, 9.17920, 7.50000, 7.50000, 0.00000},
    {-255.86189, -1411.20825, 9.85920, 5.00000, 7.50000, 0.00000},
    {-270.86191, -1413.20825, 11.31920, 0.00000, 7.50000, 0.00000},
    {-285.86191, -1413.20825, 12.65920, 0.00000, 5.00000, 0.00000},
    {-300.86191, -1413.20825, 14.41920, 0.00000, 5.00000, 0.00000},
    {-315.86191, -1413.20825, 14.67920, 0.00000, 0.00000, 0.00000},
    {-329.16190, -1412.20825, 14.79920, 0.00000, 0.00000, 0.00000},
    {-326.36191, -1397.20825, 13.81920, 0.00000, 0.00000, 0.00000},
    {-314.36191, -1398.20825, 13.93920, 0.00000, 0.00000, 0.00000},
    {-299.36191, -1397.20825, 13.07920, -7.50000, 5.00000, 0.00000},
    {-284.36191, -1398.20825, 12.21920, -5.00000, 5.00000, 0.00000},
    {-269.36191, -1398.20825, 11.85920, 0.00000, 7.50000, 0.00000},
    {-254.36189, -1396.20825, 10.77920, 0.00000, 7.50000, 0.00000},
    {-239.36189, -1394.20825, 10.25920, 5.00000, 7.50000, 0.00000},
    {-224.36189, -1391.20825, 8.77920, 7.50000, 7.50000, 0.00000},
    {-209.36189, -1389.20825, 6.93920, 5.00000, 7.50000, 0.00000},
    {-194.36189, -1387.20825, 5.89920, 5.00000, 7.50000, 0.00000},
    {-179.36189, -1384.20825, 4.87920, 5.00000, 7.50000, 0.00000},
    {-167.36189, -1382.20825, 3.81920, 7.50000, 7.50000, 0.00000},
    {-194.36189, -1372.20825, 5.69920, 2.50000, 7.50000, 0.00000},
    {-209.36189, -1374.20825, 6.53920, 2.50000, 7.50000, 0.00000},
    {-224.36189, -1376.20825, 8.43920, 5.00000, 7.50000, 0.00000},
    {-239.36189, -1379.20825, 10.53920, 7.50000, 7.50000, 0.00000},
    {-254.36189, -1381.18835, 10.99920, 2.50000, 7.50000, 0.00000},
    {-269.36191, -1383.20825, 11.47920, -2.50000, 7.50000, 0.00000},
    {-284.36191, -1383.20825, 10.91920, 0.00000, 5.00000, 0.00000},
    {-299.36191, -1382.20825, 10.85920, -7.50000, 7.50000, 0.00000},
    {-314.36191, -1383.20825, 11.99920, -7.50000, 0.00000, 0.00000},
    {-326.36191, -1382.20825, 12.41920, 0.00000, 0.00000, 0.00000},
    {-323.36191, -1367.20825, 10.79920, -2.50000, 0.00000, 0.00000},
    {-311.36191, -1368.20825, 9.87920, -7.50000, 2.50000, 0.00000},
    {-296.36191, -1367.20825, 9.09920, 0.00000, 2.50000, 0.00000},
    {-281.36191, -1368.20825, 10.11920, -2.50000, -2.50000, 0.00000},
    {-266.36191, -1368.20825, 10.51920, -2.50000, 2.50000, 0.00000},
    {-251.36189, -1366.18835, 10.51920, -2.50000, 2.50000, 0.00000},
    {-236.36189, -1364.20825, 9.55920, -2.50000, 7.50000, 0.00000},
    {-221.36189, -1361.20825, 7.15920, 5.00000, 7.50000, 0.00000},
    {-206.36189, -1359.20825, 7.37920, 10.00000, 5.00000, 0.00000},
    {-192.51320, -1358.61230, 5.21920, 2.50000, 7.50000, 0.00000},
    {-190.51320, -1343.61230, 6.33920, 7.50000, 15.00000, 0.00000},
    {-204.36189, -1344.20825, 9.79920, 10.00000, 7.50000, 0.00000},
    {-219.36189, -1346.20825, 9.91920, 10.00000, -7.50000, 0.00000},
    {-234.36189, -1349.20825, 8.19920, -2.50000, 12.50000, 0.00000},
    {-249.36189, -1351.18835, 9.23920, -2.50000, 2.50000, 0.00000},
    {-264.36191, -1353.20825, 8.97920, -2.50000, 2.50000, 0.00000},
    {-279.36191, -1353.20825, 9.27920, 0.00000, 2.50000, 0.00000},
    {-294.36191, -1352.20825, 8.75920, 0.00000, 0.00000, 0.00000},
    {-309.36191, -1353.20825, 9.37920, 0.00000, 2.50000, 0.00000},
    {-321.36191, -1352.20825, 9.93920, -2.50000, 0.00000, 0.00000},
    {-321.36191, -1337.20825, 9.75920, 0.00000, 0.00000, 0.00000},
    {-309.36191, -1338.20825, 9.03920, 0.00000, 2.50000, 0.00000},
    {-294.36191, -1337.20825, 8.37920, 0.00000, 0.00000, 0.00000},
    {-279.36191, -1338.20825, 7.91920, 0.00000, 2.50000, 0.00000},
    {-264.36191, -1338.20825, 7.79920, 5.00000, -2.50000, 0.00000},
    {-249.36189, -1336.18835, 8.43920, 7.50000, 2.50000, 0.00000},
    {-234.36189, -1334.20825, 9.67920, 2.50000, -15.00000, 0.00000},
    {-219.36189, -1331.20825, 11.85920, 10.00000, 5.00000, 0.00000},
    {-204.36189, -1329.20825, 10.59920, 10.00000, 12.50000, 0.00000},
    {-190.51320, -1328.61230, 8.87920, 7.50000, 15.00000, 0.00000},
    {-179.36189, -1327.20825, 6.39920, 15.00000, 15.00000, 0.00000},
    {-167.36189, -1326.34827, 3.81920, 7.50000, 7.50000, 0.00000},
    {-165.36189, -1311.34827, 4.43920, 7.50000, 7.50000, 0.00000},
    {-177.36189, -1312.20825, 6.35920, 0.00000, 7.50000, 0.00000},
    {-188.51320, -1313.61230, 7.27920, -2.50000, 5.00000, 0.00000},
    {-202.36189, -1314.20825, 8.29920, 0.00000, 0.00000, 0.00000},
    {-217.36189, -1316.20825, 10.03920, -2.50000, 7.50000, 0.00000},
    {-232.36189, -1319.20825, 11.45920, 2.50000, -10.00000, 0.00000},
    {-247.36189, -1321.18835, 10.29920, 7.50000, -2.50000, 0.00000},
    {-262.36191, -1323.20825, 9.61920, 7.50000, -5.00000, 0.00000},
    {-277.36191, -1323.20825, 9.27920, 5.00000, -2.50000, 0.00000},
    {-292.36191, -1322.20825, 9.13920, 0.00000, 0.00000, 0.00000},
    {-307.36191, -1323.20825, 9.43920, 5.00000, 2.50000, 0.00000},
    {-319.36191, -1322.20825, 9.75920, 0.00000, 5.00000, 0.00000}
};

new Float:FarmWarehousePos[3][6] = {
    {-211.6588,-1482.2583,8.7177},
    {-391.0122,-1461.2251,25.9963},
    {-375.0554,-1448.7446,25.9800}
};

enum E_FARM_WAREHOUSE_INFO
{
    fwarArea,
    fwarPickup,
    fwarCount,
    Text3D:fwarText
}
new FarmWarehouseInfo[MAX_FARM_WAREHOUSE][E_FARM_WAREHOUSE_INFO];

LoadFarm()
{
    for(new i = 0; i < MAX_FARM_WHEAT; i++)
    {
        if(i < MAX_FARM_MILKER) CreateFarm(TYPE_FARM_MILKER, i);
        if(i < MAX_FARM_TREE) CreateFarm(TYPE_FARM_TREE, i);
        CreateFarm(TYPE_FARM_WHEAT, i);
    }

    CreateVehicleVEx(NPO_JOB, JOB_FARM_TRACTOR, 531, -382.4862, -1434.0293, 25.6551, 90.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_TRACTOR, 531, -382.4862, -1431.0293, 25.6551, 90.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_TRACTOR, 531, -382.4862, -1428.0293, 25.6551, 90.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_TRACTOR, 531, -382.4862, -1425.0293, 25.6551, 90.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_TRACTOR, 531, -382.4862, -1422.0293, 25.6551, 90.0000, 238, 238, 100);

    CreateVehicleVEx(NPO_JOB, JOB_FARM_COMBINE, 532, -395.9600, -1391.1758, 24.1284, -144.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_COMBINE, 532, -388.4005, -1385.7129, 24.1284, -144.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_COMBINE, 532, -380.9186, -1380.2455, 24.1284, -144.0000, 238, 238, 100);

    CreateVehicleVEx(NPO_JOB, JOB_FARM_PRODUCT, 478, -385.0050, -1416.1647, 25.6351, 90.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_PRODUCT, 478, -368.5103, -1445.8958, 25.6351, 90.0000, 238, 238, 100);
    CreateVehicleVEx(NPO_JOB, JOB_FARM_PRODUCT, 478, -393.1656, -1446.2883, 25.6351, 0.0000, 238, 238, 100);

    pickup_farm[0] = CreatePickup(1318, 23, -385.0114,-1461.7563,26.2581); // Устройство, вход;
    pickup_farm[1] = CreatePickup(1318, 23, 1824.8857,1569.6603,1510.9063,1); // Устройство, выход;
    pickup_farm[2] = CreatePickup(1275, 23, 1832.0790,1567.6595,1510.9143,1); // Устройство;
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 1832.0790,1567.6595,1510.9143, 20.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    // Владелец фермы;
    new actorid = CreateActor(33, 1833.4464,1567.7045,1510.9063,91.7503);
    SetActorVirtualWorld(actorid, 1);
    CreateDynamic3DTextLabel("NPC: "I"Владелец фермы", COLOR_WHITE, 1833.4464,1567.7045,1510.9063 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

CreateFarm(type, idx)
{
    switch(type)
    {
        case TYPE_FARM_TREE:
        {
            FarmTreeInfo[idx][ftPlayerID] = INVALID_PLAYER_ID;

            FarmTreeInfo[idx][ftObject] = CreateDynamicObject(673, FarmTreePos[idx][0], FarmTreePos[idx][1], FarmTreePos[idx][2], 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
            SetDynamicObjectMaterial(FarmTreeInfo[idx][ftObject], 0, 825, "gta_proc_bigbush", "veg_bush4", 0x00000000);
            SetDynamicObjectMaterial(FarmTreeInfo[idx][ftObject], 1, 19793, "firewood1", "firewood1", 0x00000000);
            FarmTreeInfo[idx][ftArea] = CreateDynamicSphere(FarmTreePos[idx][0], FarmTreePos[idx][1], FarmTreePos[idx][2] + 2.5, 2.5, -1, -1, -1);
            UpdateAreaInfo(FarmTreeInfo[idx][ftArea], TYPE_WORK_FARM_TREE, AREA_SYBTYPE_FARM_TREE, idx);

            FarmTreeInfo[idx][ftOrange][0] = CreateDynamicObject(19574, FarmTreePos[idx][0] - (- 0.432067), FarmTreePos[idx][1] + (- 2.122925), FarmTreePos[idx][2] + 6.91113, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
            FarmTreeInfo[idx][ftOrange][1] = CreateDynamicObject(19574, FarmTreePos[idx][0] + (- 2.027985), FarmTreePos[idx][1] + (- 1.722534), FarmTreePos[idx][2] + 6.431119, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
            FarmTreeInfo[idx][ftOrange][2] = CreateDynamicObject(19574, FarmTreePos[idx][0] + (- 1.317597), FarmTreePos[idx][1] - (- 1.377807), FarmTreePos[idx][2] + 6.391119, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
            FarmTreeInfo[idx][ftOrange][3] = CreateDynamicObject(19574, FarmTreePos[idx][0] - (- 0.652679), FarmTreePos[idx][1] - (- 1.578003), FarmTreePos[idx][2] + 5.911108, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
            FarmTreeInfo[idx][ftOrange][4] = CreateDynamicObject(19574, FarmTreePos[idx][0] - (- 2.482849), FarmTreePos[idx][1] + (- 0.283692), FarmTreePos[idx][2] + 6.421115, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Апельсиновое дерево\n\nАпельсинов на дереве: "W"%d{"#cMAIN"}\n\nСтатус: "W"%s", GetFarmCount(TYPE_FARM_TREE, idx), FarmTreeInfo[idx][ftPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободно"W"" : "{"#cLIGHTRED"}Занято"W"");
            FarmTreeInfo[idx][ftText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FarmTreePos[idx][0], FarmTreePos[idx][1], FarmTreePos[idx][2] + 5.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
        }
        case TYPE_FARM_MILKER:
        {
            FarmMilkerInfo[idx][fmPlayerID] = INVALID_PLAYER_ID;
            FarmMilkerInfo[idx][fmMood] = 100.0;

            FarmMilkerInfo[idx][fmObject] = CreateDynamicObject(19833, FarmMilkerPos[idx][0], FarmMilkerPos[idx][1], FarmMilkerPos[idx][2], FarmMilkerPos[idx][3], FarmMilkerPos[idx][4], FarmMilkerPos[idx][5], -1, -1, -1, 120.0, 120.0);
            FarmMilkerInfo[idx][fmPickup] = CreateDynamicPickup(19135, 23, FarmMilkerPos[idx][0] + floatcos(FarmMilkerPos[idx][5] + 180, degrees), FarmMilkerPos[idx][1] + floatsin(FarmMilkerPos[idx][5] + 180, degrees), FarmMilkerPos[idx][2] + 0.75);
            FarmMilkerInfo[idx][fmArea] = CreateDynamicSphere(FarmMilkerPos[idx][0] + floatcos(FarmMilkerPos[idx][5] + 180, degrees), FarmMilkerPos[idx][1] + floatsin(FarmMilkerPos[idx][5] + 180, degrees), FarmMilkerPos[idx][2], 1.25, -1, -1, -1);
            UpdateAreaInfo(FarmMilkerInfo[idx][fmArea], TYPE_WORK_FARM_MILKER, AREA_SUBTYPE_INVALID_ID, idx);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Место для дойки коровы\n\nСтатус: "W"%s", FarmMilkerInfo[idx][fmPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободно"W"" : "{"#cLIGHTRED"}Занято"W"");
            FarmMilkerInfo[idx][fmText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FarmMilkerPos[idx][0] + floatcos(FarmMilkerPos[idx][5] + 180, degrees), FarmMilkerPos[idx][1] + floatsin(FarmMilkerPos[idx][5] + 180, degrees), FarmMilkerPos[idx][2] + 0.75, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
            return 1;
        }
        case TYPE_FARM_WHEAT:
        {
            FarmWheatInfo[idx][fwRespawn] = 0;

            FarmWheatInfo[idx][fwArea] = CreateDynamicSphere(FarmWheatPos[idx][0], FarmWheatPos[idx][1], FarmWheatPos[idx][2], 5.0, -1, -1, -1);
            UpdateAreaInfo(FarmWheatInfo[idx][fwArea], TYPE_WORK_FARM_WHEAT, AREA_SUBTYPE_FARM_WHEAT, idx);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Пшеница\n\nСтатус: "W"%s", GetFarmStatus(idx));
            FarmWheatInfo[idx][fwText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FarmWheatPos[idx][0], FarmWheatPos[idx][1], FarmWheatPos[idx][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
        }
        case TYPE_FARM_PRODUCT: return 1;
        case TYPE_FARM_WAREHOUSE:
        {
            FarmWarehouseInfo[idx][fwarArea] = CreateDynamicSphere(FarmWarehousePos[idx][0], FarmWarehousePos[idx][1], FarmWarehousePos[idx][2] + 2.5, 5.0, -1, -1, -1);
            UpdateAreaInfo(FarmWarehouseInfo[idx][fwarArea], TYPE_WORK_FARM_W_TREE + idx, AREA_SYBTYPE_FARM_W_TREE + idx, idx);
            FarmWarehouseInfo[idx][fwarPickup] = CreateDynamicPickup(19135, 23, FarmWarehousePos[idx][0], FarmWarehousePos[idx][1], FarmWarehousePos[idx][2]);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\n\nСостояние: "W"%d", FarmWarehouseName[idx], FarmWarehouseInfo[idx][fwarCount]);
            FarmWarehouseInfo[idx][fwarText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FarmWarehousePos[idx][0], FarmWarehousePos[idx][1], FarmWarehousePos[idx][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
        }
    }
    return 1;
}

GetFarmCount(type, idx)
{
    new count;
    switch(type)
    {
        case TYPE_FARM_TREE:
        {
            for(new i = 0; i < MAX_FARM_TREE_ORANGE; i++)
            {
                if(FarmTreeInfo[idx][ftOrange][i] != INVALID_OBJECT_ID) count++;
            }
        }
        case TYPE_FARM_MILKER, TYPE_FARM_WHEAT, TYPE_FARM_PRODUCT, TYPE_FARM_WAREHOUSE: return 0;
    }
    return count;
}

GetFarmStatus(idx)
{
    new str[128], name_status[3][84] = {"{"#cLIGHTRED"}Необходима посадка"W"", "{"#cYELLOW"}Растет"W"", "{"#cGREEN"}Можно собрать"W""};
    format(str, sizeof(str), "%s", name_status[FarmWheatInfo[idx][fwRespawn]]);
    return str;
}

UpdateFarm(type, idx)
{
    switch(type)
    {
        case TYPE_FARM_TREE:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Апельсиновое дерево\n\nАпельсинов на дереве: "W"%d{"#cMAIN"}\n\nСтатус: "W"%s", GetFarmCount(TYPE_FARM_TREE, idx), FarmTreeInfo[idx][ftPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободно"W"" : "{"#cLIGHTRED"}Занято"W"");
            UpdateDynamic3DTextLabelText(FarmTreeInfo[idx][ftText], COLOR_MAIN, STRING_GLOBAL);
        }
        case TYPE_FARM_MILKER:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Место для дойки коровы\n\nСтатус: "W"%s", FarmMilkerInfo[idx][fmPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободно"W"" : "{"#cLIGHTRED"}Занято"W"");
            UpdateDynamic3DTextLabelText(FarmMilkerInfo[idx][fmText], COLOR_MAIN, STRING_GLOBAL);
        }
        case TYPE_FARM_WHEAT:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Пшеница\n\nСтатус: "W"%s", GetFarmStatus(idx));
            UpdateDynamic3DTextLabelText(FarmWheatInfo[idx][fwText], COLOR_MAIN, STRING_GLOBAL);

            if(FarmWheatInfo[idx][fwObject] != INVALID_OBJECT_ID)
            {
                DestroyDynamicObject(FarmWheatInfo[idx][fwObject]);
                FarmWheatInfo[idx][fwObject] = INVALID_OBJECT_ID;
            }

            switch(FarmWheatInfo[idx][fwRespawn])
            {
                case 1: FarmWheatInfo[idx][fwObject] = CreateDynamicObject(826, FarmWheatPos[idx][0], FarmWheatPos[idx][1], FarmWheatPos[idx][2] - 2.5, FarmWheatPos[idx][3], FarmWheatPos[idx][4], FarmWheatPos[idx][5], -1, -1, -1, 120.0, 120.0);
                case 2: FarmWheatInfo[idx][fwObject] = CreateDynamicObject(826, FarmWheatPos[idx][0], FarmWheatPos[idx][1], FarmWheatPos[idx][2], FarmWheatPos[idx][3], FarmWheatPos[idx][4], FarmWheatPos[idx][5], -1, -1, -1, 120.0, 120.0);
            }
        }
        case TYPE_FARM_PRODUCT: return 1;
        case TYPE_FARM_WAREHOUSE:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\n\nСостояние: "W"%d", FarmWarehouseName[idx], FarmWarehouseInfo[idx][fwarCount]);
            UpdateDynamic3DTextLabelText(FarmWarehouseInfo[idx][fwarText], COLOR_MAIN, STRING_GLOBAL);
        }
    }
    return 1;
}

CheckFarm(type)
{
    switch(type)
    {
        case TYPE_FARM_TREE:
        {
            for(new i = 0, idx = 0; i < MAX_FARM_TREE; i++)
            {
                for(idx = 0; idx < MAX_FARM_TREE_ORANGE; idx++)
                {
                    if(FarmTreeInfo[i][ftRespawn][idx] == 1)
                    {
                        FarmTreeInfo[i][ftRespawn][idx] = 0;
                        switch(idx)
                        {
                            case 0:
                            {
                                if(FarmTreeInfo[i][ftOrange][0] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmTreeInfo[i][ftOrange][0]);
                                FarmTreeInfo[i][ftOrange][0] = CreateDynamicObject(19574, FarmTreePos[i][0] - (- 0.432067), FarmTreePos[i][1] + (- 2.122925), FarmTreePos[i][2] + 6.91113, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
                            }
                            case 1:
                            {
                                if(FarmTreeInfo[i][ftOrange][1] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmTreeInfo[i][ftOrange][1]);
                                FarmTreeInfo[i][ftOrange][1] = CreateDynamicObject(19574, FarmTreePos[i][0] + (- 2.027985), FarmTreePos[i][1] + (- 1.722534), FarmTreePos[i][2] + 6.431119, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
                            }
                            case 2:
                            {
                                if(FarmTreeInfo[i][ftOrange][2] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmTreeInfo[i][ftOrange][2]);
                                FarmTreeInfo[i][ftOrange][2] = CreateDynamicObject(19574, FarmTreePos[i][0] + (- 1.317597), FarmTreePos[i][1] - (- 1.377807), FarmTreePos[i][2] + 6.391119, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
                            }
                            case 3:
                            {
                                if(FarmTreeInfo[i][ftOrange][3] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmTreeInfo[i][ftOrange][3]);
                                FarmTreeInfo[i][ftOrange][3] = CreateDynamicObject(19574, FarmTreePos[i][0] - (- 0.652679), FarmTreePos[i][1] - (- 1.578003), FarmTreePos[i][2] + 5.911108, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
                            }
                            case 4:
                            {
                                if(FarmTreeInfo[i][ftOrange][4] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmTreeInfo[i][ftOrange][4]);
                                FarmTreeInfo[i][ftOrange][4] = CreateDynamicObject(19574, FarmTreePos[i][0] - (- 2.482849), FarmTreePos[i][1] + (- 0.283692), FarmTreePos[i][2] + 6.421115, 0.00000, 0.00000, 0.00000, -1, -1, -1, 120.0, 120.0);
                            }
                        }
                        UpdateFarm(TYPE_FARM_TREE, i);
                    }
                }
            }
        }
        case TYPE_FARM_MILKER:
        {
            for(new i = 0; i < MAX_FARM_MILKER; i++)
            {
                if(FarmMilkerInfo[i][fmStatus] == 1)
                {
                    if(FarmMilkerInfo[i][fmObject] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmMilkerInfo[i][fmObject]);
                    FarmMilkerInfo[i][fmObject] = CreateDynamicObject(19833, FarmMilkerPos[i][0], FarmMilkerPos[i][1], FarmMilkerPos[i][2], FarmMilkerPos[i][3], FarmMilkerPos[i][4], FarmMilkerPos[i][5], -1, -1, -1, 120.0, 120.0);
                    FarmMilkerInfo[i][fmStatus] = 0;
                }
            }
            return 1;
        }
        case TYPE_FARM_WHEAT:
        {
            for(new i = 0; i < MAX_FARM_WHEAT; i++)
            {
                if(FarmWheatInfo[i][fwRespawn] == 1)
                {
                    FarmWheatInfo[i][fwRespawn] = 2;
                    UpdateFarm(TYPE_FARM_WHEAT, i);
                }
            }
        }
        case TYPE_FARM_PRODUCT: return 1;
        case TYPE_FARM_WAREHOUSE:
        {
            if(FarmWarehouseInfo[2][fwarCount] < 10000000)
                FarmWarehouseInfo[2][fwarCount] += 30000000;

            new count = FarmWarehouseInfo[0][fwarCount] + FarmWarehouseInfo[1][fwarCount] + 1;
            FarmWarehouseInfo[0][fwarCount] = 0;
            MysqlUpdateOtherInt("farm_warehouse_tree", FarmWarehouseInfo[0][fwarCount]);
            UpdateFarm(TYPE_FARM_WAREHOUSE, 0);
            FarmWarehouseInfo[1][fwarCount] = 0;
            MysqlUpdateOtherInt("farm_warehouse_milker", FarmWarehouseInfo[1][fwarCount]);
            UpdateFarm(TYPE_FARM_WAREHOUSE, 1);
            FarmWarehouseInfo[2][fwarCount] += count * 2;
            MysqlUpdateOtherInt("farm_warehouse_product", FarmWarehouseInfo[2][fwarCount]);
            UpdateFarm(TYPE_FARM_WAREHOUSE, 2);
        }
    }
    return 1;
}

GetPlayerStartFarmJob(playerid, idx)
{
    new str[128];
    if(p_info[playerid][job_skill][2] >= FarmSkill[idx]) str = "{"#cGREEN"}Доступно"W"";
    else format(str, sizeof(str), "{"#cLIGHTRED"}Доступно с %d навыка"W"", FarmSkill[idx]);
    return str;
}

forward AttachedTrailerToVehicleFarm(playerid);
public AttachedTrailerToVehicleFarm(playerid)
{
    if(!p_temp[playerid][FarmTrailerTimer]) return 1;
    new vehicleid = GetPlayerVehicleID(playerid);
    AttachTrailerToVehicle(p_temp[playerid][FarmTrailer], vehicleid);
    SendMes(playerid, COLOR_SEA_WAVE, "Отправляйтесь на поле, найдите места где нет пшеницы и посадите её.");
    KillTimer(p_temp[playerid][FarmTrailerTimer]);
    Fix_TogglePlayerControllable(playerid, true);
    p_temp[playerid][FarmTrailerTimer] = 0;
    return 1;
}

ShowPlayerFarm(playerid)
{
    new count;
    STRING_GLOBAL = "[#] Название бизнеса\tКол-во товара\tЗарплата\n";
    for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
    for(new idx = 0; idx < totalbizz; idx++)
    {
        if(b_info[idx][b_order] == 0) continue;
        if(b_info[idx][b_order_player_id] != INVALID_PLAYER_ID) continue;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%d\t%d$\n", STRING_GLOBAL, count + 1, b_info[idx][_name], b_info[idx][b_order], b_info[idx][b_order]);
        p_temp[playerid][p_listitem][count] = idx;
        count++;
    }
    if(count == 0) return SendError(playerid, "На данный момент нет заказов по доставке товара.");
    ShowPlayerDialog(playerid, D_FARM_PRODUCT, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список заказов", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CheckPlayerFarm(playerid, type, idx)
{
    switch(type)
    {
        case TYPE_FARM_TREE:
        {
            for(new i = 0; i < MAX_FARM_TREE_ORANGE; i++)
            {
                if(FarmTreeInfo[idx][ftOrange][i] != INVALID_OBJECT_ID)
                {
                    DestroyDynamicObject(FarmTreeInfo[idx][ftOrange][i]);
                    FarmTreeInfo[idx][ftOrange][i] = INVALID_OBJECT_ID;
                    FarmTreeInfo[idx][ftRespawn][i] = 1;
                    break;
                }
            }
            UpdateFarm(TYPE_FARM_TREE, idx);
            p_temp[playerid][FarmCheck]++;
            SendMes(playerid, COLOR_LYELLOW, "Вы собрали {"#cLIME"}%d шт.{"#cLYELLOW"} апельсинов из {"#cLIME"}%d шт.{"#cLYELLOW"} Для повторного действия нажмите \"ALT\".", p_temp[playerid][FarmCheck], MAX_FARM_TREE_ORANGE);
            if(p_temp[playerid][FarmCheck] == MAX_FARM_TREE_ORANGE)
            {
                SetPlayerGPS(playerid, FarmWarehousePos[0][0], FarmWarehousePos[0][1], FarmWarehousePos[0][2], 5.0);
                SendMes(playerid, COLOR_SEA_WAVE, "Вы собрали достаточное количество апельсинов, отнесите их на склад.");
                SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
                if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
                ClearAnimations(playerid);
                ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
                //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
                SetPlayerAttachedObject(playerid, 1, 19638, 1, 0.019000, 0.470999, 0.014998, -41.200008, 96.599739, -45.699985, 1.000000, 1.000000, 1.000000);
                return 1;
            }
            if(GetFarmCount(TYPE_FARM_TREE, idx) == 0) SendMes(playerid, COLOR_DARKORANGE, "На дереве больше нет апельсинов, отправляйтесь к другому дереву и продолжайте сбор.");
        }
        case TYPE_FARM_MILKER:
        {
            p_temp[playerid][FarmCheck]++;
            SetPlayerGPS(playerid, FarmWarehousePos[1][0], FarmWarehousePos[1][1], FarmWarehousePos[1][2], 5.0);
            SendMes(playerid, COLOR_SEA_WAVE, "Вы надоили полное ведро молока, отнесите его на склад.");
            SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
            SetPlayerAttachedObject(playerid, 1, 19468, 1, 0.135999, 0.470999, -0.028002, -13.000015, 94.299896, 173.299957, 2.366001, 2.558001, 1.010000);
        }
        case TYPE_FARM_WHEAT, TYPE_FARM_PRODUCT, TYPE_FARM_WAREHOUSE: return 1;
    }
    return 1;
}

CheckPlayerFarmWarehouse(playerid, type, idx = 0)
{
    if(type >= TYPE_FARM_WAREHOUSE) return 1;

    new reason_money;
    switch(type)
    {
        case TYPE_FARM_TREE, TYPE_FARM_MILKER:
        {
            if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);

            new
                factor[2] = {10, 10},
                salary[2] = {333, 292},
                count = p_temp[playerid][FarmCheck] * factor[type];

            FarmWarehouseInfo[type][fwarCount] += count;

            UpdateFarm(TYPE_FARM_WAREHOUSE, type);

            if(type == TYPE_FARM_TREE) MysqlUpdateOtherInt("farm_warehouse_tree", FarmWarehouseInfo[0][fwarCount]);
            else MysqlUpdateOtherInt("farm_warehouse_milker", FarmWarehouseInfo[1][fwarCount]);

            p_temp[playerid][FarmCount] += count;

            SendMes(playerid, COLOR_LYELLOW, "Вы перенесли {"#cLIME"}%d %s.", count, type == TYPE_FARM_TREE ? "кг. апельсинов" : "литров молока");
            SendMes(playerid, COLOR_LYELLOW, "Всего перенесено {"#cLIME"}%d %s.", p_temp[playerid][FarmCount], type == TYPE_FARM_TREE ? "кг. апельсинов" : "литров молока");

            reason_money = GetPlayerMoneySkill(playerid, salary[type], 2);

            p_temp[playerid][FarmCheck] = 0;

            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "putdwn", 4.0, 0, 1, 1, 0, 0, 1);
            //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

            CheckPlayerBot(playerid, 5);

            #if EASTER_STATUS == 1
                if((type == TYPE_FARM_TREE && p_info[playerid][event_quest_id] == 2) || (type == TYPE_FARM_MILKER && p_info[playerid][event_quest_id] == 3))
                {
                    ShowEasterQuest_Check(playerid);
                }
            #endif
        }
        case TYPE_FARM_WHEAT:
        {
            new salary[3] = {83, 0, 93},
                respawn = FarmWheatInfo[idx][fwRespawn];

            p_temp[playerid][FarmCount]++;

            SendMes(playerid, COLOR_LYELLOW, "Вы %s пшеницу.", respawn == 0 ? "посадили" : "собрали");
            reason_money = GetPlayerMoneySkill(playerid, salary[respawn], 2);
            FarmWheatInfo[idx][fwRespawn]++;
            if(FarmWheatInfo[idx][fwRespawn] > 2) FarmWheatInfo[idx][fwRespawn] = 0;
            UpdateFarm(TYPE_FARM_WHEAT, idx);

            CheckPlayerBot(playerid, 10);
        }
        case TYPE_FARM_PRODUCT:
        {
            for(new i = 0; i < 5; i++)
            {
                if(p_temp[playerid][FarmObject][i] != INVALID_OBJECT_ID)
                {
                    DestroyDynamicObject(p_temp[playerid][FarmObject][i]);
                    p_temp[playerid][FarmObject][i] = INVALID_OBJECT_ID;
                }
            }

            new count = b_info[idx][b_order];

            SendMes(playerid, COLOR_BLUE, "Вы доставили %d товара в \"%s\".", count, b_info[idx][_name]);

            reason_money = GetPlayerMoneySkill(playerid, count/2, 2);

            p_temp[playerid][FarmBizIDx] = -1;
            p_temp[playerid][FarmCount] += count;

            b_info[idx][_prod] += count;
            b_info[idx][b_order] -= count;
            if(b_info[idx][b_order] < 0) b_info[idx][b_order] = 0;
            b_info[idx][b_order_player_id] = INVALID_PLAYER_ID;
            save_bizz(idx);
        }
    }

    if(CheckPlayerMaxSalarySkill(playerid, 2, reason_money))
    {
        SetPlayerMoney(playerid, reason_money, true, "зарплата ферма");
        OnServerInfoForMoney[17] += reason_money;
        p_temp[playerid][FarmSalary] += reason_money;
        SendMes(playerid, COLOR_LYELLOW, "К Вашей зарплате добавлено: {"#cLIME"}%d$.{"#cLYELLOW"} Заработано всего: {"#cLIME"}%d$.", reason_money, p_temp[playerid][FarmSalary]);

        p_info[playerid][job_skill_salary][2] += reason_money;
    }
    else SendError(playerid, "За последний час игры было заработано максимальное количество денежных средств.");

    if(random(type == TYPE_FARM_WHEAT ? 2000 : 200) < 5) GivePlayerCasket(playerid, 720);

    SendMes(playerid, COLOR_SEA_WAVE, FarmJobWarehouseInfo[type]);
    if(FarmJobWarehousePos[type][0] != 0.0 && FarmJobWarehousePos[type][1] != 0.0 && FarmJobWarehousePos[type][2] != 0.0)
    {
        SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
        SetPlayerGPS(playerid, FarmJobWarehousePos[type][0], FarmJobWarehousePos[type][1], FarmJobWarehousePos[type][2], 5.0);
    }

    UpdatePlayerWorkSkill(playerid, 2);

    CheckPlayerMission(playerid, START_FARM);
    CheckPlayerMission(playerid, DAILY_FARM);
    CheckPlayerMission(playerid, ACHIEVEMENT_FARM);

    CheckPlayerFreelance(playerid, FREELANCE_FARM);
    CheckPlayerBattlePass(playerid, BATTLEPASS_FARM);

    UpdateFamilyLevel(playerid);
    UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_FARM); // Контракты: Фермы

    #if EVENT_HALLOWEEN == 1
    if(p_info[playerid][halloween_id] == 3 && p_info[playerid][halloween_progress] < 10)
    {
        p_info[playerid][halloween_progress]++;
        MysqlUpdatePlayerInt(playerid, "halloween_progress", p_info[playerid][halloween_progress]);
        HalloweenQuest_Check(playerid);
    }
    #endif

    STRING_GLOBAL[0] = EOS;
    if(p_info[playerid][p_settings][INTERFACE])
    {
        f(STRING_GLOBAL, "%d", p_temp[playerid][FarmCount]);
        PlayerTextDrawSetString(playerid, PTD_NewSalary[playerid][2], STRING_GLOBAL);
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "%d$", p_temp[playerid][FarmSalary]);
        PlayerTextDrawSetString(playerid, PTD_NewSalary[playerid][1], STRING_GLOBAL);
    }
    else
    {
        f(STRING_GLOBAL, "Progress: %d", p_temp[playerid][FarmCount]);
        PlayerTextDrawSetString(playerid, PTD_Salary[playerid][5], STRING_GLOBAL);
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "%d$", p_temp[playerid][FarmSalary]);
        PlayerTextDrawSetString(playerid, PTD_Salary[playerid][6], STRING_GLOBAL);
    }
    return 1;
}

CMD:farm_warehouse(playerid, params[0])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /farm_warehouse [кол-во]");
    if(params[0] < 1 || params[0] > 10000000) return SendError(playerid, "Количество должно быть не менее 1 и не более 10000000.");

    FarmWarehouseInfo[2][fwarCount] += params[0];
    UpdateFarm(TYPE_FARM_WAREHOUSE, 2);
    MysqlUpdateOtherInt("farm_warehouse_product", FarmWarehouseInfo[2][fwarCount]);

    SendAccess(playerid, "Вы добавили на склад продуктов %d продуктов.", params[0]);
    return 1;
}
