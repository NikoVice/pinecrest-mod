#define MAX_GIFT_COINS                      15
#define MAX_GIFT_CHANGE_COINS               42
#define MAX_GIFT_PICKUP                     300

#if EVENT_HALLOWEEN == 1
    #define MAX_HALLOWEEN_QUEST_ID              5
    #define MAX_HALLOWEEN_FLOWERS               10
    #define MAX_HALLOWEEN_GRAVES                18


    new HalloweenQuest_FlowersPickups[MAX_HALLOWEEN_FLOWERS];
    new HalloweenQuest_Area[2];

    new Float:halloween_flowers_pos[MAX_HALLOWEEN_FLOWERS][3] =
    {
        {-374.9670,-1468.3671,26.3297},
        {-380.5574,-1451.9811,25.7266},
        {-382.3150,-1457.6118,25.7266},
        {-378.8122,-1449.2661,25.7266},
        {-370.0572,-1454.1592,26.2581},
        {-366.3579,-1439.6205,25.7266},
        {-371.2569,-1439.5127,25.7266},
        {-364.1330,-1428.0961,25.7266},
        {-407.2944,-1464.1315,25.7911},
        {-369.0352,-1416.8932,25.7266}
    };

    new Float:halloween_graves_pos[MAX_HALLOWEEN_GRAVES][3] =
    {
        {877.9863,-1117.4753,24.0668},
        {863.9548,-1118.2722,24.0528},
        {848.5793,-1118.6720,24.0458},
        {843.3802,-1111.2240,24.1767},
        {857.3218,-1110.9415,24.1895},
        {867.4222,-1111.0325,24.1879},
        {879.0673,-1110.5161,24.1892},
        {910.5658,-1096.2583,24.2969},
        {911.0994,-1085.7109,24.2969},
        {905.6352,-1079.9779,24.296},
        {889.1622,-1084.8011,24.2969},
        {878.4213,-1084.8042,24.2969},
        {862.8703,-1084.9703,24.2969},
        {857.6546,-1093.7355,24.2969},
        {843.2923,-1094.0364,24.3040},
        {843.3525,-1085.4911,24.2969},
        {857.5987,-1078.7721,24.296},
        {871.7813,-1078.6476,24.2969}
    };
#endif


new gift_area;
new gift_pickups_count;

LoadGift()
{
    CreateActor(159, 1119.2559,-315.5169,73.9919,90.0);
    CreateDynamic3DTextLabel("NPC: "I"Организатор празднования", COLOR_WHITE, 1119.2559,-315.5169,73.9919 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    gift_area = CreateDynamicSphere(1116.8174,-315.4333,73.9922, 2.5, 0, 0);
    CreateDynamicPickup(1318, 23, 1116.8174,-315.4333,73.9922, 0, 0);
    CreateDynamic3DTextLabel("<< Нажмите "W"ALT{"#cMAIN"} >>", COLOR_MAIN, 1116.8174,-315.4333,73.9922, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    /*
    new tmpobjid;
    tmpobjid = CreateDynamicObject(896, 1459.273925, -1701.423950, 15.152876, 0.000000, 0.000000, 136.699966, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
    tmpobjid = CreateDynamicObject(901, 1460.560302, -1700.199829, 12.970724, 180.000000, -103.700088, 34.400005, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(898, 1457.137207, -1696.567626, 18.827135, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
    tmpobjid = CreateDynamicObject(898, 1455.070678, -1703.265258, 14.827129, 0.000000, 0.000000, 81.399993, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12871, "ce_ground01", "rocktbrn128", 0x00000000);
    tmpobjid = CreateDynamicObject(19479, 1464.840209, -1706.714355, 17.230102, -69.800102, 90.000000, -122.100013, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19479, 1459.509277, -1710.823974, 15.933913, -69.800102, 90.000000, -179.900009, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19479, 1460.690795, -1706.778076, 20.350423, 24.400009, 117.300033, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19481, 1461.275634, -1699.217529, 13.575349, 0.000000, 90.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19481, 1465.561401, -1695.746704, 9.840781, 105.899963, -155.699996, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19481, 1456.609252, -1690.655517, 8.276656, 105.899963, -155.699996, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19481, 1446.678955, -1699.524169, 7.744031, 112.399871, 90.999977, 81.099998, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(734, 1461.862670, -1711.908081, 12.204889, 0.000000, 0.000000, -0.499998, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 3630, "compthotrans_la", "sanpedock994", 0x00000000);
    tmpobjid = CreateDynamicObject(19341, 1463.974487, -1699.292114, 20.526645, -33.556720, 509.337646, -20.373210, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    tmpobjid = CreateDynamicObject(19342, 1464.387329, -1699.901855, 19.922142, -33.556720, 494.737670, -20.373210, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14495, "sweetshall", "mcstraps_door1", 0x00000000);
    tmpobjid = CreateDynamicObject(19314, 1464.285400, -1699.934326, 20.079469, -43.060176, 138.185989, -34.558906, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14495, "sweetshall", "mcstraps_door1", 0x00000000);
    tmpobjid = CreateDynamicObject(19314, 1464.387084, -1699.681030, 19.894304, 26.489265, -154.894378, 167.311630, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14495, "sweetshall", "mcstraps_door1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1462.860351, -1699.934082, 18.557781, 12.993927, 358.490478, 18.539224, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1462.461669, -1700.441528, 19.230871, -51.921772, -430.398651, -101.596015, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1461.815429, -1700.306396, 19.641336, -22.155918, -464.371887, -153.816848, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1461.854492, -1699.890625, 19.653150, -2.255640, -467.771728, -169.560623, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1462.339111, -1699.289672, 18.942115, 53.279315, -62.198814, 108.848365, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1462.442138, -1699.185546, 18.542398, 45.581851, 338.144531, 57.330947, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(701, 1464.095336, -1699.393554, 20.714336, -33.556720, 404.737670, -20.373210, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 4992, "airportdetail", "sm_Agave_1", 0xFF000000);
    tmpobjid = CreateDynamicObject(701, 1463.936279, -1699.209716, 20.890707, -17.552270, 391.160156, -50.942436, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 4992, "airportdetail", "sm_Agave_1", 0xFF000000);
    tmpobjid = CreateDynamicObject(701, 1464.169311, -1699.736450, 20.181905, -17.552270, 391.160156, -50.942436, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 4992, "airportdetail", "sm_Agave_1", 0xFF000000);
    tmpobjid = CreateDynamicObject(19341, 1463.038452, -1689.284179, 14.207429, -5.547008, 460.212768, -38.289966, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    tmpobjid = CreateDynamicObject(19342, 1463.770019, -1689.893920, 14.178445, -5.547008, 445.612792, -38.289966, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14495, "sweetshall", "mcstraps_door1", 0x00000000);
    tmpobjid = CreateDynamicObject(19314, 1463.582885, -1689.926391, 14.190419, -4.263845, 96.657722, -52.887527, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14495, "sweetshall", "mcstraps_door1", 0x00000000);
    tmpobjid = CreateDynamicObject(19314, 1463.792114, -1689.673095, 14.161652, 6.206322, -102.911270, 151.438934, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14495, "sweetshall", "mcstraps_door1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1463.954833, -1689.926147, 12.139097, -6.584165, 308.475738, 21.571029, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1463.176757, -1690.433593, 12.220339, 0.899053, -421.110809, -97.122123, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1462.462036, -1690.298461, 11.946257, 5.925003, -417.960540, -146.677230, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1462.475708, -1689.882690, 11.984662, 7.001033, -415.073059, -171.917633, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1463.335449, -1689.281738, 11.949786, 1.354249, -47.162315, 101.140678, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(1298, 1463.717895, -1689.177612, 11.794177, -2.701941, 312.433563, 67.777084, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 15040, "cuntcuts", "cszerocupboard", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(701, 1462.959838, -1689.385620, 14.416357, -5.547008, 355.612792, -38.289966, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 4992, "airportdetail", "sm_Agave_1", 0xFF000000);
    tmpobjid = CreateDynamicObject(701, 1462.723510, -1689.201782, 14.393817, 24.492067, 357.389221, -48.687324, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 4992, "airportdetail", "sm_Agave_1", 0xFF000000);
    tmpobjid = CreateDynamicObject(701, 1463.431518, -1689.728515, 14.158295, 24.492067, 357.389221, -48.687324, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 4992, "airportdetail", "sm_Agave_1", 0xFF000000);
    tmpobjid = CreateDynamicObject(19791, 1460.552368, -1693.579467, 3.568027, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19791, 1460.552368, -1686.998535, 3.558027, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19791, 1460.552368, -1708.930664, 3.568027, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19791, 1459.631469, -1708.930664, 3.562026, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19791, 1459.631469, -1686.989746, 3.562026, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19791, 1459.631469, -1696.969604, 3.562026, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1460.510009, -1685.698486, 13.696166, 17.700000, 0.000000, -26.700000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 17101, "cuntwlandse", "des_crackeddirt1", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1460.652343, -1685.412963, 13.661980, -20.599996, 0.000000, -26.700000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 17101, "cuntwlandse", "des_crackeddirt1", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1460.806274, -1685.717895, 13.625470, -20.599996, 0.000000, -123.200004, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 17101, "cuntwlandse", "des_crackeddirt1", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1459.312133, -1683.899780, 13.696166, 17.699996, 0.000007, -107.499961, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 17101, "cuntwlandse", "des_crackeddirt1", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1459.616699, -1683.994628, 13.661980, -20.600000, 0.000007, -107.499961, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 17101, "cuntwlandse", "des_crackeddirt1", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1459.340332, -1684.195312, 13.625470, -20.600000, -0.000003, 155.999984, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 17101, "cuntwlandse", "des_crackeddirt1", 0x00000000);
    tmpobjid = CreateDynamicObject(2589, 1459.203247, -1690.758422, 19.875549, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_floor2", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16060, "des_trees", "sm_bark_light", 0x00000000);
    tmpobjid = CreateDynamicObject(2589, 1460.429199, -1690.522827, 20.225557, 0.000000, 0.000000, 53.699985, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_floor2", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16060, "des_trees", "sm_bark_light", 0x00000000);
    tmpobjid = CreateDynamicObject(2589, 1459.204589, -1689.946655, 23.065555, 0.000000, 0.000000, 143.699981, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_floor2", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16060, "des_trees", "sm_bark_light", 0x00000000);
    tmpobjid = CreateDynamicObject(18782, 1498.791381, -1682.279418, 13.856097, 0.000000, 0.000000, -180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(906, 1500.938110, -1710.493041, 10.660292, -27.499977, -67.400054, 163.099945, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19717, 1499.987792, -1699.924438, 13.703476, 7.299998, 107.500068, -180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19342, 1497.952514, -1710.868652, 14.142732, -31.599977, 87.700012, -35.000022, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14718, "lasmall1int2", "washmchne_1", 0x00000000);
    tmpobjid = CreateDynamicObject(19342, 1500.002563, -1709.991455, 14.281259, -144.400146, 80.800018, -75.000053, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14718, "lasmall1int2", "washmchne_1", 0x00000000);
    tmpobjid = CreateDynamicObject(19739, 1498.528930, -1709.776489, 12.857410, 7.900458, -4.701323, 124.647659, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19738, 1495.812866, -1705.720947, 12.720839, -11.900456, -1.998614, -56.452308, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(2410, 1500.369018, -1712.757568, 13.551778, 0.000000, 0.000000, 135.500030, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 19130, "matarrows", "red-2-2", 0x00000000);
    tmpobjid = CreateDynamicObject(19717, 1494.172973, -1692.901977, 14.063335, 23.000000, 169.899978, -142.900054, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19717, 1494.163818, -1712.308959, 14.076736, 23.000000, 119.399971, 80.699905, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19672, 1491.863891, -1707.777099, 10.783916, -34.699993, -25.100004, 174.399993, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19672, 1493.761596, -1685.436035, 11.323621, -34.699993, -25.100004, 145.699981, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1494.415649, -1685.856933, 13.229704, 0.000000, 0.000000, -52.400001, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1492.777954, -1690.892700, 13.349706, 0.000000, 0.000000, -52.400001, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(2410, 1500.318847, -1712.709228, 13.551778, 0.000000, 0.000000, 120.899978, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 19130, "matarrows", "red-2-2", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1494.614990, -1693.277343, 13.309705, 0.000000, 0.000000, -114.099983, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1500.242431, -1696.505371, 13.309705, 0.000000, 0.000000, 151.000015, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19752, 1497.215087, -1684.410766, 12.621271, -5.199252, 1.003636, -56.108909, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19752, 1497.329711, -1684.362182, 13.966716, -1.000000, -185.199966, -146.199859, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19764, 1498.719116, -1690.032836, 12.711058, 5.199297, 718.995666, 123.891098, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19764, 1498.834594, -1689.984252, 14.066075, 4.387916, 182.966659, 78.831825, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19764, 1497.656494, -1695.827392, 12.732869, 6.694026, 357.195556, 80.837348, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19764, 1497.802124, -1695.918457, 14.082804, 6.711248, 182.762283, 35.611354, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19752, 1494.104980, -1700.712768, 12.915024, -2.899633, 1.001046, -56.149269, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19752, 1494.174926, -1700.694580, 14.264479, -1.000000, -182.899948, -146.199859, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19738, 1496.117675, -1705.551269, 12.646785, 19.199548, -1.498614, -56.352317, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19739, 1495.881835, -1705.705932, 14.242559, -2.999530, -181.001327, 123.747673, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19738, 1498.638183, -1709.840087, 14.155589, 2.999542, -178.998703, -56.252319, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19739, 1498.830810, -1709.696533, 12.707572, -15.699538, -4.101324, 123.647674, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1498.757324, -1700.278442, 13.309705, 0.000000, 0.000000, 140.499954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1494.013061, -1710.765502, 13.309705, 0.000000, 0.000000, 140.499954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1496.432495, -1712.954467, 13.219703, 0.000000, 0.000000, 122.999931, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1492.826660, -1707.164550, 13.159702, 0.000000, 0.000000, 122.999931, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(829, 1492.206787, -1703.897460, 13.159702, 0.000000, 0.000000, 65.799942, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(8947, 1482.002807, -1665.844848, 10.528910, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(8947, 1477.711425, -1665.858520, 10.507902, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1467.922241, -1673.141723, 13.011404, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1465.511596, -1670.732543, 13.014406, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1465.511596, -1660.971801, 13.014406, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1472.922241, -1673.141723, 13.011404, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1477.911254, -1673.141723, 13.011404, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1482.910400, -1673.141723, 13.011404, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1487.911132, -1673.141723, 13.011404, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1491.797851, -1673.134887, 13.017407, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1467.922241, -1658.568969, 13.011404, 0.000015, 0.000000, 89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1472.922241, -1658.568969, 13.011404, 0.000015, 0.000000, 89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1477.911254, -1658.568969, 13.011404, 0.000015, 0.000000, 89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1482.910400, -1658.568969, 13.011404, 0.000015, 0.000000, 89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1487.911132, -1658.568969, 13.011404, 0.000015, 0.000000, 89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1491.797851, -1658.562133, 13.017407, 0.000015, 0.000000, 89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1494.201049, -1660.971801, 13.014406, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1494.201049, -1665.961181, 13.014406, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1494.203979, -1670.716308, 13.022409, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1467.296997, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1470.756835, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1474.217163, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1477.676635, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1481.137329, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1484.597412, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1488.058349, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1491.518066, -1673.137573, 14.295209, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1492.393798, -1673.134643, 14.297210, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1467.296997, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1470.756835, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1474.217163, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1477.676635, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1481.137329, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1484.597412, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1488.058349, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1491.518066, -1658.585937, 14.295209, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1492.393798, -1658.583007, 14.297210, -0.000015, 0.000000, -89.999954, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1465.566650, -1671.426269, 14.295209, -0.000007, 0.000000, -179.999969, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1465.566650, -1668.833862, 14.295209, -0.000007, 0.000000, -179.999969, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1465.566650, -1660.312744, 14.295209, -0.000007, 0.000000, -179.999969, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1465.571533, -1662.891235, 14.296210, -0.000007, 0.000000, -179.999969, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1465.514526, -1662.228149, 13.019408, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(19866, 1465.514526, -1669.558715, 13.019408, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 12814, "factorycunte", "newall3_16c128", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1494.125122, -1671.403930, 14.297210, -0.000007, 0.000000, 0.000022, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1494.125122, -1667.953247, 14.297210, -0.000007, 0.000000, 0.000022, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1494.125122, -1664.493041, 14.297210, -0.000007, 0.000000, 0.000022, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1494.125122, -1661.031738, 14.297210, -0.000007, 0.000000, 0.000022, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(3850, 1494.130004, -1660.167968, 14.299211, -0.000007, 0.000000, 0.000022, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 13861, "lahills_wiresnshit3", "sjmornfnce", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1474.948852, -1645.006591, 12.935081, 0.000002, 0.000007, 20.500001, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(3873, 1479.398193, -1639.555297, -4.227933, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 2, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1477.566162, -1638.999267, 11.545077, -0.000008, 0.000011, -14.599997, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1477.064697, -1646.418334, 5.975087, -0.000007, 0.000002, -67.299980, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "vegaspalm01_128", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1477.449340, -1638.968750, 11.545077, -0.000008, 0.000011, -14.599997, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1474.892700, -1645.027587, 12.935081, 0.000002, 0.000007, 20.500001, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1476.394775, -1649.480224, 11.315070, 0.000009, 0.000010, 64.099952, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1476.368408, -1649.534179, 11.315070, 0.000009, 0.000010, 64.099952, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(16401, 1479.683715, -1647.012329, 11.801495, 0.000007, 9.100006, 89.999977, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 716, "gta_tree_bevhills", "trunk5", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1485.382202, -1641.820922, 4.245081, 0.000005, 0.000005, 44.899932, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "vegaspalm01_128", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1482.503173, -1649.996704, 11.315070, 0.000016, 0.000007, 112.499946, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1482.525878, -1650.052368, 11.315070, 0.000016, 0.000007, 112.499946, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1484.148803, -1645.760986, 8.985049, 0.000018, 0.000000, 168.199874, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1484.207397, -1645.773437, 8.985049, 0.000018, 0.000000, 168.199874, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1485.060058, -1642.514282, 13.295095, 0.000013, -0.000005, -139.300079, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1485.105468, -1642.475463, 13.295095, 0.000013, -0.000005, -139.300079, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1482.461425, -1639.250488, 12.025090, 0.000006, -0.000008, -112.100036, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1482.483886, -1639.195312, 12.025090, 0.000006, -0.000008, -112.100036, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1474.760864, -1641.474731, 12.025090, -0.000000, -0.000004, -54.800071, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 914, "industrialext", "CJ_SPEC", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(769, 1474.726684, -1641.426147, 12.025090, -0.000000, -0.000004, -54.800071, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 716, "gta_tree_bevhills", "trunk5", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
    tmpobjid = CreateDynamicObject(19342, 1478.546752, -1644.742187, 13.777462, -40.800006, 100.200042, 2.899999, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14718, "lasmall1int2", "washmchne_1", 0x00000000);
    tmpobjid = CreateDynamicObject(19342, 1480.584960, -1644.774169, 13.764633, -137.999969, 85.300048, 172.299926, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14718, "lasmall1int2", "washmchne_1", 0x00000000);
    tmpobjid = CreateDynamicObject(7597, 1479.388916, -1641.305786, 6.182365, 0.000000, 0.000000, 57.500007, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 716, "gta_tree_bevhills", "trunk5", 0x00000000);
    tmpobjid = CreateDynamicObject(3510, 1498.603149, -1702.186157, 13.328663, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(3510, 1495.013305, -1688.186279, 13.128661, 0.000000, 0.000000, -33.699996, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 18901, "matclothes", "hatmap3", 0x00000000);
    tmpobjid = CreateDynamicObject(19480, 1479.207275, -1702.235229, 13.055120, 0.000000, 90.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14612, "ab_abattoir_box", "ab_bloodfloor", 0xFF000000);
    tmpobjid = CreateDynamicObject(18782, 1478.758544, -1690.933593, 13.421810, -8.499999, 3.699999, -145.300003, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 3980, "cityhall_lan", "sl_LAbedingsoil", 0x00000000);
    tmpobjid = CreateDynamicObject(18846, 1478.863647, -1691.437377, 12.277091, -4.500000, -21.499996, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2963, "freezrx", "freeze_door", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 2963, "freezrx", "freeze_door", 0x00000000);
    tmpobjid = CreateDynamicObject(18846, 1476.244262, -1688.345092, 12.234207, -4.500000, 41.399997, -32.900005, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2963, "freezrx", "freeze_door", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 2963, "freezrx", "freeze_door", 0x00000000);
    tmpobjid = CreateDynamicObject(19345, 1481.267578, -1686.671142, 13.796487, -130.199996, 30.899990, 33.300014, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 19574, "sampfruits", "apple2", 0x00000000);
    tmpobjid = CreateDynamicObject(2407, 1481.318237, -1686.238403, 13.500845, 58.000133, 20.900005, -35.599998, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 19574, "sampfruits", "apple2", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(11735, 1481.255737, -1685.579223, 13.396553, -75.300010, -1.399999, -169.700027, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 19574, "sampfruits", "apple2", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(11735, 1481.585571, -1685.669677, 13.359004, -28.100000, -73.000083, 81.500015, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 19574, "sampfruits", "apple2", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(19345, 1481.079467, -1686.245727, 13.668022, -138.299987, 33.399978, -35.599994, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14718, "lasmall1int2", "washmchne_1", 0x00000000);
    tmpobjid = CreateDynamicObject(19482, 1480.138549, -1673.560424, 21.697019, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HAPPY", 130, "Ariel", 150, 1, 0xFFFFA500, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, 1480.138549, -1673.510375, 21.697019, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HAPPY", 130, "Ariel", 150, 1, 0xF0000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, 1480.138549, -1673.440307, 21.697019, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HAPPY", 130, "Ariel", 150, 1, 0xFF000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, 1480.138549, -1673.380249, 21.697019, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HAPPY", 130, "Ariel", 150, 1, 0xFF000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19479, 1479.990356, -1673.606201, 20.552877, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HALLOWEEN", 130, "Segoe Script", 80, 1, 0xFFFF0000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19479, 1479.990356, -1673.546142, 20.552877, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HALLOWEEN", 130, "Segoe Script", 80, 1, 0xF0000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19479, 1479.990356, -1673.456054, 20.552877, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HALLOWEEN", 130, "Segoe Script", 80, 1, 0xF0000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19479, 1479.990356, -1673.385986, 20.552877, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "HALLOWEEN", 130, "Segoe Script", 80, 1, 0xF0000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, 1476.878784, -1673.420288, 21.706998, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "\"", 130, "Webdings", 199, 0, 0xFF000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19482, 1482.788818, -1673.420288, 22.076992, 18.499992, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterialText(tmpobjid, 0, "\"", 130, "Webdings", 199, 0, 0xFF000000, 0x00000000, 1);
    tmpobjid = CreateDynamicObject(19089, 1483.390380, -1673.489379, 22.428096, 0.000000, -134.899948, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(19089, 1476.822631, -1673.489379, 22.460771, 0.000000, 137.799972, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(16101, 1488.583740, -1673.477539, 16.765047, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(16101, 1488.583740, -1673.477539, 16.765047, -180.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(16101, 1471.872558, -1673.477539, 16.995052, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(16101, 1471.872558, -1673.477539, 16.995052, 180.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
    tmpobjid = CreateDynamicObject(3092, 1489.257080, -1662.189575, 14.153971, 0.298991, -0.799000, 151.201049, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 10839, "aircarpkbarier_sfse", "glass_64a", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(3092, 1476.877807, -1669.218872, 13.943966, 0.298995, -0.799007, 151.201049, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 10839, "aircarpkbarier_sfse", "glass_64a", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(3092, 1470.247680, -1662.671875, 14.026257, 11.492075, 5.453569, 85.855117, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 10839, "aircarpkbarier_sfse", "glass_64a", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(707, 1504.666870, -1621.125610, 12.588316, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 825, "gta_proc_bigbush", "veg_bush4", 0xFF000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 716, "gta_tree_bevhills", "vegaspalm01_128", 0x00000000);
    tmpobjid = CreateDynamicObject(707, 1458.176147, -1617.705444, 12.588316, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 1, 825, "gta_proc_bigbush", "veg_bush4", 0xFF000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 716, "gta_tree_bevhills", "vegaspalm01_128", 0x00000000);
    tmpobjid = CreateDynamicObject(2906, 1488.415649, -1666.757202, 14.829555, -8.798994, -66.599006, 159.298950, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2589, "ab_ab", "ab_carcass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(2907, 1488.686645, -1666.629150, 14.584554, -84.099998, -0.000073, 173.398895, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2589, "ab_ab", "ab_carcass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(2906, 1488.949584, -1666.667114, 14.578554, -60.098995, -115.600006, -133.699005, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2589, "ab_ab", "ab_carcass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(19163, 1488.643676, -1666.589111, 15.096554, -0.000003, 0.000006, -24.998994, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2589, "ab_ab", "ab_carcass", 0x00000000);
    tmpobjid = CreateDynamicObject(2905, 1488.764648, -1666.635131, 13.931555, -71.499000, 272.999023, -2.798976, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 2589, "ab_ab", "ab_carcass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(2905, 1488.544677, -1666.716186, 13.896555, -87.699981, 94.799812, 175.198776, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 14612, "ab_abattoir_box", "ab_bloodfloor", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(1974, 1488.650634, -1666.618164, 15.104554, -0.000007, -0.000001, -97.598976, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(1974, 1488.620605, -1666.614135, 15.104554, -0.000007, -0.000001, -97.598976, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(1974, 1488.629638, -1666.625122, 15.024554, -0.000007, -0.000001, -97.598976, -1, -1, -1, 120.00, 120.00);
    SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0xFFFFFFFF);

    tmpobjid = CreateDynamicObject(734, 1461.782592, -1711.998168, 12.204889, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1464.710449, -1699.960327, 19.690830, -33.556720, 404.737670, -20.373210, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1464.617065, -1700.232055, 19.873123, -33.556720, 404.737670, -20.373210, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1464.589111, -1700.225097, 19.976900, -33.556720, 404.737670, -20.373210, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1464.718627, -1699.877319, 19.730611, -33.556720, 404.737670, -20.373210, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1464.148315, -1689.952392, 14.299940, -5.547008, 355.612792, -38.289966, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1463.946289, -1690.224121, 14.333657, -5.547008, 355.612792, -38.289966, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1463.846313, -1690.217163, 14.373088, -5.547008, 355.612792, -38.289966, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19577, 1464.121337, -1689.869384, 14.330224, -5.547008, 355.612792, -38.289966, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(1457, 1460.453247, -1684.993041, 15.058023, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(804, 1492.842895, -1697.058837, 14.452299, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(804, 1498.842529, -1698.849609, 14.452299, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(804, 1492.582519, -1709.348144, 14.452299, 0.000000, 0.000000, -180.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(804, 1492.582519, -1684.268066, 14.452299, 0.000000, 0.000000, -270.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(12961, 1479.934082, -1665.819946, 14.064234, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(16052, 1465.617919, -1665.901000, 15.093156, 0.000000, 0.000000, -270.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(734, 1468.423461, -1670.909301, 11.594887, 0.000000, 0.000000, -88.799995, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(734, 1491.158081, -1662.005249, 10.464879, 0.000000, 0.000000, -148.899993, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(624, 1501.046875, -1701.932861, 12.177225, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(634, 1497.224975, -1695.528198, 13.339480, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(634, 1494.644531, -1686.788085, 13.339480, 0.000000, 0.000000, -45.499992, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(634, 1502.386962, -1694.082885, 13.039477, 0.000000, 0.000000, -45.499992, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(634, 1493.807739, -1713.829223, 13.179478, 0.000000, 0.000000, -45.499992, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(624, 1492.416870, -1694.152832, 11.907220, 0.000000, 0.000000, -107.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(18717, 1478.678100, -1690.910156, 11.668449, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(18717, 1475.906982, -1688.450317, 12.018447, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(18726, 1478.657836, -1691.678833, 11.043993, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19033, 1481.245605, -1686.647460, 13.848713, 10.599998, -54.200004, 95.900001, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19033, 1481.298217, -1686.647460, 13.842958, -13.599999, -54.000019, 59.900012, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(18736, 1487.802001, -1661.548339, 15.058971, -89.801185, 179.997787, 66.797874, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(18736, 1475.422729, -1668.577636, 14.848966, -89.801185, 179.998657, 66.798736, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(18736, 1470.372314, -1661.003540, 14.766702, -77.277046, 292.390655, 114.470268, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1488.095703, -1709.424438, 13.335329, 0.000007, -0.000002, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.998657, -1709.662353, 13.353329, -10.598992, -79.599006, 55.998966, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.810668, -1709.576660, 13.365329, -10.600007, -107.800003, -144.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.894409, -1709.584350, 13.159331, -25.998992, -94.098999, 34.998970, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.917480, -1709.694091, 13.151329, -23.000003, -68.499992, -115.499000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.889160, -1709.563842, 13.165329, -2.499006, 99.400001, -136.399017, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.928466, -1709.700683, 13.152330, 9.400004, -297.799011, 52.098968, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.841796, -1709.647216, 13.252330, -25.099990, -280.299987, 37.298969, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19528, 1488.087280, -1709.427490, 13.516329, 0.000007, -93.199996, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1469.040527, -1709.405883, 13.335329, 0.000012, 0.000002, 125.998924, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.266479, -1709.527954, 13.353329, -10.598984, -79.598999, 139.798934, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.161010, -1709.705688, 13.365329, -10.600011, -107.800010, -60.200016, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.177734, -1709.623168, 13.159331, -25.998989, -94.098991, 118.798919, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.289306, -1709.612060, 13.151329, -23.000009, -68.499992, -31.699022, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.156738, -1709.626220, 13.165329, -2.499011, 99.399993, -52.599033, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.296997, -1709.601928, 13.152330, 9.400009, -297.799011, 135.898925, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.234619, -1709.682373, 13.252330, -25.099985, -280.299987, 121.098922, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1488.095703, -1699.304077, 13.335329, 0.000012, 0.000002, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.998657, -1699.541992, 13.353329, -10.598984, -79.598999, 55.998954, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.810668, -1699.456298, 13.365329, -10.600011, -107.800010, -144.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.894409, -1699.463989, 13.159331, -25.998989, -94.098991, 34.998973, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.917480, -1699.573730, 13.151329, -23.000009, -68.499992, -115.498977, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.889160, -1699.443481, 13.165329, -2.499011, 99.399993, -136.399017, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.928466, -1699.580322, 13.152330, 9.400009, -297.799011, 52.098957, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.841796, -1699.526855, 13.252330, -25.099985, -280.299987, 37.298961, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1469.040527, -1699.285522, 13.335329, 0.000018, -0.000001, 125.998901, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.266479, -1699.407592, 13.353329, -10.598979, -79.599006, 139.798934, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.161010, -1699.585327, 13.365329, -10.600017, -107.800003, -60.200004, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.177734, -1699.502807, 13.159331, -25.998981, -94.098999, 118.798896, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.289306, -1699.491699, 13.151329, -23.000011, -68.499984, -31.699018, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.156738, -1699.505859, 13.165329, -2.499017, 99.400001, -52.599021, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.296997, -1699.481567, 13.152330, 9.400013, -297.799011, 135.898925, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.234619, -1699.562011, 13.252330, -25.099979, -280.299987, 121.098899, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19528, 1469.042602, -1699.294189, 13.516329, 0.000018, -93.199996, 125.998901, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1488.095703, -1688.133300, 13.335329, 0.000017, 0.000008, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.998657, -1688.371215, 13.353329, -10.598978, -79.598991, 55.998943, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.810668, -1688.285522, 13.365329, -10.600015, -107.800018, -144.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.894409, -1688.293212, 13.159331, -25.998985, -94.098983, 34.998973, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.917480, -1688.402954, 13.151329, -23.000015, -68.499992, -115.498962, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.889160, -1688.272705, 13.165329, -2.499017, 99.399986, -136.399017, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.928466, -1688.409545, 13.152330, 9.400013, -297.799011, 52.098957, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.841796, -1688.356079, 13.252330, -25.099981, -280.299987, 37.298961, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19528, 1488.087280, -1688.136352, 13.516329, 0.000017, -93.199981, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1469.040527, -1688.114746, 13.335329, 0.000024, -0.000006, 125.998878, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.266479, -1688.236816, 13.353329, -10.598974, -79.599014, 139.798934, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.161010, -1688.414550, 13.365329, -10.600023, -107.799995, -60.199993, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.177734, -1688.332031, 13.159331, -25.998973, -94.099006, 118.798873, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.289306, -1688.320922, 13.151329, -23.000013, -68.499977, -31.699010, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.156738, -1688.335083, 13.165329, -2.499023, 99.400009, -52.599021, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.296997, -1688.310791, 13.152330, 9.400018, -297.799011, 135.898910, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1469.234619, -1688.391235, 13.252330, -25.099973, -280.299987, 121.098876, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19528, 1469.042602, -1688.123413, 13.516329, 0.000024, -93.200004, 125.998878, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1488.095703, -1674.080322, 13.335329, 0.000022, 0.000014, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.998657, -1674.318237, 13.353329, -10.598970, -79.598983, 55.998935, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.810668, -1674.232543, 13.365329, -10.600020, -107.800025, -144.000000, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.894409, -1674.240234, 13.159331, -25.998981, -94.098976, 34.998977, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.917480, -1674.349975, 13.151329, -23.000020, -68.499992, -115.498939, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.889160, -1674.219726, 13.165329, -2.499022, 99.399978, -136.399017, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.928466, -1674.356567, 13.152330, 9.400018, -297.799011, 52.098957, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1487.841796, -1674.303100, 13.252330, -25.099977, -280.299987, 37.298961, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19528, 1488.087280, -1674.083374, 13.516329, 0.000022, -93.199974, 42.198974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(19320, 1472.722167, -1674.061767, 13.335329, 0.000036, -0.000015, 125.998832, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.948120, -1674.183837, 13.353329, -10.598963, -79.599029, 139.798934, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.842651, -1674.361572, 13.365329, -10.600035, -107.799980, -60.199974, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.859375, -1674.279052, 13.159331, -25.998958, -94.099021, 118.798828, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.970947, -1674.267944, 13.151329, -23.000017, -68.499961, -31.699001, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.838378, -1674.282104, 13.165329, -2.499035, 99.400024, -52.599021, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.978637, -1674.257812, 13.152330, 9.400029, -297.799011, 135.898864, -1, -1, -1, 120.00, 120.00);
    tmpobjid = CreateDynamicObject(11742, 1472.916259, -1674.338256, 13.252330, -25.099962, -280.299987, 121.098831, -1, -1, -1, 120.00, 120.00);
    */

    #if EVENT_HALLOWEEN == 1
        for(new i = 0; i < MAX_HALLOWEEN_FLOWERS; i++) HalloweenQuest_FlowersPickups[i] = CreateDynamicPickup(325, 2, halloween_flowers_pos[i][0], halloween_flowers_pos[i][1], halloween_flowers_pos[i][2], -1, -1, -1);

        HalloweenQuest_Area[0] = CreateDynamicSphere(-384.9199,-1468.6221,26.2581, 2.5, -1, -1, -1);
        CreatePickup(1318, 23, -384.9199,-1468.6221,26.2581);
        CreateDynamic3DTextLabel("<< Нажмите "W"ALT{"#cMAIN"} >>", COLOR_MAIN, -384.9199,-1468.6221,26.2581, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

        HalloweenQuest_Area[1] = CreateDynamicSphere(1108.4924,-2294.9304,1022.6520, 2.5, -1, -1, -1);
        CreatePickup(1318, 23, 1108.4924,-2294.9304,1022.6520, -1);
        CreateDynamic3DTextLabel("<< Нажмите "W"ALT{"#cMAIN"} >>", COLOR_MAIN, 1108.4924,-2294.9304,1022.6520, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

        tmpobjid = CreateObject(19552, 1118.898925, -2258.509521, 1021.652038, 0.000000, 0.000000, 0.000000, 120.00);
        SetObjectMaterial(tmpobjid, 0, 14709, "lamidint2", "mp_apt1_floor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1147.682861, -2216.138671, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1150.813232, -2212.986816, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1150.892822, -2216.138671, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1144.607910, -2219.211425, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(1569, 1148.513549, -2213.014648, 1021.652038, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_barndoor2", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1154.102783, -2216.138671, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1157.063232, -2212.986816, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1154.102783, -2222.388671, 1023.342468, 0.000000, 89.999977, 179.999862, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1154.102783, -2228.638671, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1138.357910, -2219.211425, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.107910, -2219.211425, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1125.857910, -2219.211425, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1144.607910, -2216.001464, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.357910, -2216.001464, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.107910, -2216.001464, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1125.857910, -2216.001464, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1150.892822, -2225.494628, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1147.818359, -2222.421386, 1023.342468, -0.000007, 90.000000, -89.999984, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1141.568359, -2222.421386, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.494262, -2225.494628, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1138.494262, -2231.744628, 1023.342468, 0.000000, 89.999992, 179.999908, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1138.494262, -2237.994628, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1135.284301, -2225.494628, 1023.342468, 0.000000, 89.999992, 179.999908, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1135.284301, -2231.744628, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1132.210571, -2222.421386, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1119.547485, -2222.285644, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1116.474609, -2219.211425, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1110.224609, -2219.211425, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1119.607910, -2216.001464, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1113.357910, -2216.001464, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1107.107910, -2216.001464, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1100.857910, -2216.001464, 1023.342468, -0.000020, 90.000000, -89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.607910, -2216.001464, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.918945, -2217.683105, 1023.342468, -0.000006, 90.000000, 0.000075, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.151123, -2222.284423, 1023.342468, -0.000004, 90.000015, 0.000029, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1103.974609, -2225.461425, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1100.820922, -2222.284423, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1103.974609, -2218.229248, 1023.342468, -0.000004, 90.000015, 0.000029, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.747070, -2219.210937, 1023.342468, 0.000007, 90.000000, 89.999984, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.918945, -2223.933105, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.918945, -2230.183105, 1023.342468, -0.000006, 90.000000, 0.000075, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1150.939208, -2231.777099, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1144.689208, -2231.777099, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1104.039672, -2256.846679, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.694213, -2263.003173, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1101.063598, -2262.876464, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.722167, -2256.770019, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1094.647949, -2259.843750, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1097.899169, -2263.053710, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.825195, -2266.127685, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1091.615234, -2266.127685, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1088.542602, -2263.053710, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1088.397949, -2259.843750, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1088.094360, -2261.867187, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1151.070190, -2264.297607, 1023.342468, 0.000012, 90.000007, -0.000059, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1154.144409, -2267.370849, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1144.685546, -2261.312988, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1147.860229, -2267.748046, 1023.342468, 0.000012, 89.999992, 179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1147.818359, -2270.580810, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1154.102783, -2266.138671, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1154.102783, -2272.388671, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1154.102783, -2278.638671, 1023.342468, 0.000000, 89.999977, 179.999862, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1148.824462, -2283.008789, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.899169, -2269.200683, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.689208, -2272.410644, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1101.034912, -2272.377685, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.763183, -2275.483642, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1088.542602, -2269.200439, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1091.614990, -2275.483642, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1088.405029, -2272.370605, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1088.405029, -2278.620605, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1094.744873, -2278.616699, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1101.034912, -2288.087646, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1091.586303, -2281.783691, 1023.342468, -0.000014, 89.999992, -89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.689208, -2275.473632, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1148.824462, -2289.258789, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1133.216674, -2283.008789, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1142.540771, -2286.082031, 1023.342468, -0.000001, 90.000000, -90.000015, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.210571, -2234.818359, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1135.341796, -2238.028320, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1147.818359, -2228.567138, 1023.342468, 0.000020, 90.000000, 89.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1141.568359, -2228.567138, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.473388, -2225.361083, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1113.311889, -2228.504150, 1023.342468, -0.000004, 90.000015, 0.000029, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.238525, -2231.577880, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1107.165405, -2228.504150, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1125.960571, -2222.421386, 1023.342468, -0.000007, 90.000000, -89.999984, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1122.887573, -2225.494384, 1023.342468, 0.000000, 89.999992, 179.999908, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1119.723388, -2228.571044, 1023.342468, -0.000020, 90.000000, -89.999923, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.650024, -2231.645019, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(6959, 1137.194335, -2275.632080, 1026.430175, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "backstageceiling1_128", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(6959, 1137.194335, -2235.632080, 1026.430175, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "backstageceiling1_128", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(6959, 1095.854125, -2275.632080, 1026.430175, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "backstageceiling1_128", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(2662, 1095.014770, -2217.600341, 1023.513061, 0.000007, 0.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14787, "ab_sfgymbits02", "ab_gymMark01", 0x00000000);
        tmpobjid = CreateDynamicObject(19741, 1129.136474, -2231.744628, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1125.926513, -2231.744628, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1122.852783, -2234.818359, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.602783, -2234.818359, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.210571, -2228.671630, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_woodflloorsplat", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.210571, -2225.461669, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_woodflloorsplat", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1134.273437, -2227.055175, 1023.342468, 0.000000, 89.999992, 179.999908, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_woodflloorsplat", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(3092, 1133.964965, -2227.048828, 1025.243652, 0.000007, 0.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 1, 1982, "new_cabinets", "meat1", 0x00000000);
        tmpobjid = CreateDynamicObject(19477, 1133.662231, -2227.151367, 1021.662048, 0.000000, 90.000007, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14612, "ab_abattoir_box", "ab_bloodfloor", 0xAAFFFFFF);
        tmpobjid = CreateDynamicObject(19482, 1134.200805, -2227.081298, 1022.452697, 89.999992, 270.000000, -90.000007, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14612, "ab_abattoir_box", "ab_bloodfloor", 0xAAFFFFFF);
        tmpobjid = CreateDynamicObject(3078, 1132.316284, -2227.107421, 1023.652099, 69.999992, -89.999969, -0.000050, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterialText(tmpobjid, 0, "WRONG ROAD", 120, "Segoe Script", 30, 1, 0xF0FF0000, 0x00000000, 1);
        tmpobjid = CreateDynamicObject(19741, 1128.199707, -2225.449707, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1125.916503, -2228.601562, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.142822, -2234.818359, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1103.955444, -2231.634521, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1100.881103, -2228.561279, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1097.807128, -2231.634521, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.724609, -2225.461425, 1023.342468, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1094.631103, -2231.782958, 1023.342468, -0.000007, 90.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1100.892822, -2234.818359, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1097.755737, -2237.994628, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1104.038330, -2238.028320, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1100.965698, -2241.102294, 1023.342468, -0.000006, 90.000000, 0.000075, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(1369, 1105.022827, -2233.961181, 1022.242492, 0.000006, -0.000003, 119.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
        SetDynamicObjectMaterial(tmpobjid, 2, 13295, "ce_terminal", "Gen_Metal", 0xFF808080);
        SetDynamicObjectMaterial(tmpobjid, 3, 18247, "cw_junkyarddigcs_t", "Was_scrpyd_axle_end", 0x00000000);
        SetDynamicObjectMaterial(tmpobjid, 4, 18245, "cw_junkyardmachin", "Was_scrpyd_baler_gen_ed", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1122.171997, -2227.902099, 1022.062377, -0.000009, -89.999984, -15.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1122.280761, -2227.793212, 1022.062377, 0.000020, 90.000000, 109.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1122.108154, -2227.814453, 1021.901184, 0.000018, 89.999969, 134.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1122.188720, -2227.733642, 1021.901184, -0.000033, -89.999977, -44.999958, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(19741, 1136.290771, -2286.082031, 1023.342468, 0.000028, 90.000000, 89.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1141.704223, -2231.744628, 1023.342468, 0.000000, 89.999992, 179.999908, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.755737, -2244.244628, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1113.529174, -2237.892578, 1023.342468, -0.000006, 90.000000, 0.000074, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.319213, -2241.101318, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.245971, -2238.024414, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1129.091796, -2238.028320, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1126.017822, -2241.102050, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1122.807861, -2237.979736, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1135.341796, -2244.175781, 1023.342468, 0.000012, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1129.091796, -2244.175781, 1023.342468, 0.000012, 90.000000, 89.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.416259, -2241.101562, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1141.515869, -2241.101562, 1023.342468, 0.000007, 90.000015, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.484008, -2247.385742, 1023.342468, 0.000004, 90.000000, -90.000015, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.234008, -2247.385742, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1141.626220, -2247.384033, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1144.699707, -2244.311523, 1023.342468, 0.000007, 90.000015, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1144.187011, -2242.825439, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1122.807861, -2244.229736, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1122.807861, -2250.479736, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1126.017822, -2250.463867, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1129.091796, -2247.389892, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1129.091796, -2253.537109, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1135.341796, -2253.537109, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.502441, -2255.028564, 1023.342468, 0.000012, 89.999992, 179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1129.091796, -2256.747070, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1135.292480, -2259.824462, 1023.342468, 0.000012, 90.000007, -0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1132.219238, -2256.750976, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1141.576904, -2258.103027, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1144.650268, -2255.028564, 1023.342468, 0.000012, 90.000007, -0.000059, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1147.826904, -2254.893066, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.435546, -2261.312988, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1147.860229, -2261.498046, 1023.342468, 0.000012, 90.000007, -0.000059, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1151.070190, -2258.047607, 1023.342468, 0.000012, 89.999992, 179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFC0C0C0);
        tmpobjid = CreateDynamicObject(19741, 1154.076904, -2254.893066, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1150.892822, -2273.653564, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1147.818359, -2276.726074, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1144.744018, -2273.653564, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1144.744018, -2267.403564, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1141.593139, -2264.242187, 1023.342468, -0.000007, 90.000015, -89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1138.324096, -2273.653564, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1141.534057, -2270.524902, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1138.324096, -2267.403564, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1135.343139, -2264.242187, 1023.342468, 0.000007, 90.000015, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1151.898803, -2279.936035, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1141.534057, -2276.774902, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1145.614501, -2283.008789, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1142.540771, -2279.936035, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1135.114135, -2276.774902, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1136.290771, -2279.936035, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1135.114135, -2267.314941, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1132.041503, -2273.700927, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1132.041503, -2270.388183, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1122.807861, -2256.729736, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1119.734252, -2259.803222, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1122.944213, -2263.003173, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1126.017578, -2259.822021, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1116.602783, -2240.967041, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.602783, -2244.177001, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1119.748779, -2242.728271, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_woodflloorsplat", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1113.529174, -2247.251220, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.352783, -2250.378906, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1107.250610, -2247.168945, 1023.342468, 0.000006, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1110.324218, -2244.096191, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.183593, -2247.477050, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1100.965698, -2247.352294, 1023.342468, -0.000007, 89.999984, -179.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.755737, -2250.494628, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1104.040161, -2250.426757, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_woodflloorsplat", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1100.869018, -2253.636718, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1107.183593, -2253.727050, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1116.670043, -2256.729736, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.444213, -2263.003173, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1113.460083, -2256.729736, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.387329, -2259.803222, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1115.243164, -2253.593017, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1128.967163, -2267.314941, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1125.757202, -2267.314941, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1127.551513, -2264.157226, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1125.791503, -2273.700927, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1119.609375, -2267.314941, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1122.683105, -2270.388183, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.433105, -2267.178222, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1116.433105, -2273.519287, 1023.342468, 0.000012, 90.000007, -0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1119.541503, -2273.700927, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1113.291503, -2273.700927, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1113.258178, -2267.314941, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.183959, -2270.389404, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1107.112060, -2267.314697, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.108032, -2266.073242, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.181274, -2262.999267, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1104.137329, -2259.803222, 1023.342468, 0.000004, 90.000000, -90.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1103.898071, -2262.961181, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1103.898071, -2269.211181, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.041503, -2273.700927, 1023.342468, 0.000019, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1103.898071, -2275.461181, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1145.662597, -2289.291992, 1023.342468, -0.000009, 90.000000, -89.999992, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1139.412597, -2289.291992, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1133.162597, -2289.291992, 1023.342468, -0.000009, 90.000000, -89.999992, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1130.006713, -2286.131835, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1126.932495, -2283.057617, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1130.063232, -2279.847656, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1123.858398, -2286.131835, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1126.932495, -2289.196533, 1023.342468, 0.000019, 90.000000, -90.000083, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1120.648437, -2286.131835, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1120.648437, -2292.381835, 1023.342468, 0.000000, 90.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1123.801025, -2292.406494, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1126.879272, -2290.202636, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1117.572143, -2283.057617, 1023.342468, 0.000019, 90.000000, -90.000083, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1101.034912, -2281.837646, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1097.763183, -2281.733642, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1094.689208, -2284.808349, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1097.890869, -2288.018310, 1023.342468, 0.000020, 90.000000, 89.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1095.104248, -2285.588378, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1126.990478, -2276.774902, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1123.780517, -2276.774902, 1023.342468, 0.000000, 90.000007, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1120.707519, -2279.847656, 1023.342468, 0.000035, 90.000000, 269.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1106.967163, -2279.847656, 1023.342468, 0.000019, 90.000000, -90.000099, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1103.894042, -2276.774658, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1104.190063, -2283.057617, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1114.497924, -2286.131835, 1023.342468, 0.000000, 90.000015, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1114.457519, -2279.847656, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1112.437133, -2279.843750, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1108.112182, -2283.053710, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1114.497924, -2292.381835, 1023.342468, 0.000000, 90.000015, -0.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1111.185424, -2286.131835, 1023.342468, 0.000000, 90.000015, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1110.159545, -2295.597412, 1023.342468, 0.000000, 90.000030, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1113.232421, -2292.523925, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1108.111450, -2289.204589, 1023.342468, 0.000019, 90.000000, -90.000083, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(19741, 1106.949584, -2292.354248, 1023.342468, 0.000000, 90.000015, -179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1108.851562, -2295.445068, 1023.342468, 0.000035, 90.000000, 89.999870, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(11714, 1108.553710, -2295.386718, 1022.892395, 0.000007, 0.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5986, "chateau_lawn", "doorkb_1_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1151.886230, -2213.666748, 1022.062377, -0.000006, -89.999984, 134.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1151.737548, -2213.706787, 1022.062377, 0.000019, 90.000000, -100.000061, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1151.808349, -2213.789062, 1021.901184, 0.000015, 89.999961, -75.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1151.862060, -2213.773925, 1021.901184, -0.000030, -89.999969, 104.999961, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(854, 1138.544433, -2226.479003, 1021.852233, 0.000000, 0.000000, -35.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14709, "lamidint2", "mp_apt1_floor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(2810, 1137.135986, -2226.377929, 1020.895690, 0.000000, -30.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1982, "new_cabinets", "meat1", 0x00000000);
        SetDynamicObjectMaterial(tmpobjid, 1, 1982, "new_cabinets", "meat1", 0x00000000);
        tmpobjid = CreateDynamicObject(19482, 1153.634399, -2231.318115, 1025.403930, 0.000000, -18.000000, -45.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterialText(tmpobjid, 0, "", 130, "Webdings", 120, 0, 0xFFFFFFFF, 0x00000000, 1);
        tmpobjid = CreateDynamicObject(19339, 1143.195922, -2217.621093, 1022.012390, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 19793, "firewood1", "firewood2", 0x00000000);
        SetDynamicObjectMaterial(tmpobjid, 1, 3502, "vgsncircon", "woodsuport2_128", 0x00000000);
        SetDynamicObjectMaterial(tmpobjid, 2, 3502, "vgsncircon", "woodsuport2_128", 0x00000000);
        tmpobjid = CreateDynamicObject(19741, 1144.631713, -2216.138671, 1023.342468, 0.000000, 90.000022, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(11742, 1104.724487, -2216.718261, 1022.062377, -0.000000, -89.999992, 134.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1104.575805, -2216.758300, 1022.062377, 0.000012, 90.000000, -100.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1104.646606, -2216.840576, 1021.901184, 0.000009, 89.999961, -75.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1104.700317, -2216.825439, 1021.901184, -0.000024, -89.999969, 104.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(2316, 1096.354980, -2231.019531, 1022.002380, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 1, 14571, "chinese_furn", "ab_tv_noise", 0x00000000);
        tmpobjid = CreateDynamicObject(2906, 1096.533691, -2230.724609, 1021.906921, 0.000000, -45.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5406, "jeffers5a_lae", "gangshop13_LAe", 0x00000000);
        tmpobjid = CreateDynamicObject(1518, 1095.854492, -2231.860351, 1023.122863, 0.000000, 5.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 2, 14571, "chinese_furn", "ab_tv_noise", 0x00000000);
        tmpobjid = CreateDynamicObject(1518, 1096.851440, -2231.860351, 1023.035461, 0.000000, -5.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 2, 1692, "moregenroofstuff", "skylight_scum", 0x00000000);
        tmpobjid = CreateDynamicObject(1518, 1096.386962, -2231.860351, 1023.838012, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 2, 19115, "sillyhelmets", "sillyhelmet3", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1098.412475, -2235.573486, 1022.062377, 0.000003, -90.000000, 134.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1098.263793, -2235.613525, 1022.062377, 0.000004, 90.000000, -100.000015, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1098.334594, -2235.695800, 1021.901184, 0.000000, 89.999961, -75.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1098.388305, -2235.680664, 1021.901184, -0.000015, -89.999969, 104.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2261.560302, 1022.702514, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2261.119873, 1023.252746, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2262.000732, 1023.012512, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2262.391113, 1023.592834, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2260.639404, 1023.813049, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2262.660156, 1024.153320, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2262.129638, 1023.963134, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2261.108642, 1023.732910, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2261.839355, 1023.502685, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11712, 1088.170532, -2260.668212, 1023.052551, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 1929, "kbroul2", "oliveash_256", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1089.179199, -2269.841552, 1022.062377, 0.000017, -90.000022, 159.999847, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1089.061279, -2269.940673, 1022.062377, -0.000015, 90.000000, -74.999992, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1089.160278, -2269.985351, 1021.901184, -0.000018, 89.999969, -50.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1089.202514, -2269.948730, 1021.901184, 0.000003, -89.999977, 129.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(19527, 1093.208740, -2274.791503, 1022.602478, 0.000000, 90.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 18996, "mattextures", "bluefoil", 0x00000000);
        SetDynamicObjectMaterial(tmpobjid, 1, 18996, "mattextures", "lava1", 0x00000000);
        tmpobjid = CreateDynamicObject(19741, 1101.034912, -2266.127685, 1023.342468, -0.000007, 89.999984, -179.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19741, 1107.213623, -2256.679199, 1023.342468, -0.000006, 90.000000, 0.000060, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 5520, "bdupshouse_lae", "sw_woodflloor", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(19477, 1119.132202, -2242.634277, 1021.656066, 0.000000, 90.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14612, "ab_abattoir_box", "ab_bloodfloor", 0xAAFFFFFF);
        tmpobjid = CreateDynamicObject(1569, 1107.201049, -2249.517333, 1021.652038, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(1569, 1107.201049, -2249.517333, 1021.652038, 0.000000, 0.000000, 50.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 17933, "carter_mainmap", "mp_apt1_brokedoor", 0xFFFFFFFF);
        tmpobjid = CreateDynamicObject(11742, 1107.191040, -2248.659667, 1023.192749, 0.000000, 90.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1107.191040, -2248.489501, 1023.192749, 0.000000, 270.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(2728, 1106.210571, -2258.438964, 1023.332458, -90.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterialText(tmpobjid, 0, "d", 130, "Webdings", 199, 0, 0xAAFFFFFF, 0x00000000, 1);
        tmpobjid = CreateDynamicObject(2728, 1106.200561, -2258.368896, 1023.822937, -270.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterialText(tmpobjid, 0, "L", 140, "Wingdings", 80, 0, 0xFF000000, 0x00000000, 1);
        tmpobjid = CreateDynamicObject(19838, 1125.765747, -2275.016113, 1023.601135, 89.999992, 179.999984, -90.000007, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 701, "badlands", "sm_des_bush1", 0x00000000);
        tmpobjid = CreateDynamicObject(19838, 1124.765869, -2275.016113, 1023.601135, 89.999992, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 701, "badlands", "sm_des_bush1", 0x00000000);
        tmpobjid = CreateDynamicObject(19838, 1125.276367, -2275.016113, 1024.081542, 0.000000, 0.000007, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 701, "badlands", "sm_des_bush1", 0x00000000);
        tmpobjid = CreateDynamicObject(18880, 1125.275512, -2274.976074, 1022.681396, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 2, 18882, "hugebowls", "metalplate1", 0x00000000);
        tmpobjid = CreateDynamicObject(1575, 1125.265502, -2275.066162, 1024.181640, 0.000007, 90.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 11391, "hubprops2_sfse", "blackbag", 0x00000000);
        tmpobjid = CreateDynamicObject(19944, 1126.010620, -2290.767822, 1022.822387, 90.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14415, "carter_block_2", "mp_gs_woodpanel1", 0x00000000);
        tmpobjid = CreateDynamicObject(19944, 1125.990600, -2290.767822, 1022.822387, 90.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 10765, "airportgnd_sfse", "black64", 0x00000000);
        tmpobjid = CreateDynamicObject(19944, 1124.673950, -2291.051269, 1021.671813, 180.000000, 0.000000, 240.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 14415, "carter_block_2", "mp_gs_woodpanel1", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1125.979492, -2290.905517, 1023.732604, 0.000000, 90.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1125.979492, -2290.625244, 1023.732604, 0.000000, 270.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1123.615966, -2235.519775, 1022.062377, 0.000003, -90.000000, 134.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1123.467285, -2235.559814, 1022.062377, 0.000004, 90.000000, -100.000015, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1123.538085, -2235.642089, 1021.901184, 0.000000, 89.999961, -75.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1123.591796, -2235.626953, 1021.901184, -0.000015, -89.999969, 104.999916, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1139.003784, -2241.822509, 1022.062377, 0.000009, -90.000007, 134.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1138.855102, -2241.862548, 1022.062377, -0.000001, 90.000000, -99.999992, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1138.925903, -2241.944824, 1021.901184, -0.000004, 89.999961, -75.000045, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1138.979614, -2241.929687, 1021.901184, -0.000009, -89.999969, 104.999893, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.947998, -2254.319824, 1022.062377, 0.000027, -90.000022, 89.999900, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.814697, -2254.242919, 1022.062377, -0.000023, 89.999992, -144.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.806396, -2254.351318, 1021.901184, -0.000027, 89.999961, -120.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.855102, -2254.378417, 1021.901184, 0.000012, -89.999969, 59.999847, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.647705, -2265.371826, 1022.062377, 0.000035, -90.000022, 89.999877, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.514404, -2265.294921, 1022.062377, -0.000027, 89.999984, -144.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.506103, -2265.403320, 1021.901184, -0.000034, 89.999961, -119.999977, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1137.554809, -2265.430419, 1021.901184, 0.000018, -89.999961, 59.999835, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1153.528320, -2268.014404, 1022.062377, 0.000043, -90.000022, 89.999855, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1153.395019, -2267.937500, 1022.062377, -0.000031, 89.999977, -144.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1153.386718, -2268.045898, 1021.901184, -0.000040, 89.999961, -119.999954, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1153.435424, -2268.072998, 1021.901184, 0.000025, -89.999954, 59.999824, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1132.558227, -2280.745605, 1022.062377, 0.000049, -90.000022, 89.999832, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1132.424926, -2280.668701, 1022.062377, -0.000036, 89.999969, -144.999938, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1132.416625, -2280.777099, 1021.901184, -0.000047, 89.999961, -119.999931, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1132.465332, -2280.804199, 1021.901184, 0.000031, -89.999946, 59.999824, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1111.770141, -2286.755126, 1022.062377, 0.000049, -90.000022, -90.000137, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1111.903442, -2286.832031, 1022.062377, -0.000036, 89.999969, 35.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1111.911743, -2286.723632, 1021.901184, -0.000047, 89.999961, 60.000030, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1111.863037, -2286.696533, 1021.901184, 0.000031, -89.999946, -120.000144, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1095.791625, -2287.265625, 1022.062377, 0.000043, -90.000022, -90.000114, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1095.924926, -2287.342529, 1022.062377, -0.000031, 89.999977, 35.000038, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1095.933227, -2287.234130, 1021.901184, -0.000040, 89.999961, 60.000019, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(11742, 1095.884521, -2287.207031, 1021.901184, 0.000025, -89.999954, -120.000122, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 2127, "cj_kitchen", "CJ_RED", 0x00000000);
        tmpobjid = CreateDynamicObject(6959, 1095.854125, -2235.632080, 1026.430175, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "backstageceiling1_128", 0xFFAFAFAF);
        tmpobjid = CreateDynamicObject(6959, 1137.194335, -2195.643066, 1026.430175, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        SetDynamicObjectMaterial(tmpobjid, 0, 7555, "bballcpark1", "backstageceiling1_128", 0xFFAFAFAF);

        tmpobjid = CreateDynamicObject(19320, 1122.359619, -2227.983398, 1021.982299, 0.000009, 0.000018, 44.999984, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1122.335449, -2227.959228, 1022.212524, 0.000009, -89.999977, 44.999984, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1122.317260, -2228.040039, 1019.841064, 0.000009, 0.000018, 44.999984, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1151.764404, -2213.502441, 1021.982299, 0.000012, 0.000015, -164.999908, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1151.773193, -2213.535644, 1022.212524, 0.000012, -89.999977, -164.999908, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1151.829467, -2213.474609, 1019.841064, 0.000012, 0.000015, -164.999908, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19944, 1143.195922, -2217.621093, 1022.332702, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(3525, 1144.385375, -2216.722900, 1023.622497, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(3525, 1144.385375, -2218.514648, 1023.622497, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1104.602661, -2216.553955, 1021.982299, 0.000011, 0.000009, -164.999862, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1104.611450, -2216.587158, 1022.212524, 0.000011, -89.999984, -164.999862, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1104.667724, -2216.526123, 1019.841064, 0.000011, 0.000009, -164.999862, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1098.290649, -2235.409179, 1021.982299, 0.000009, 0.000000, -164.999816, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1098.299438, -2235.442382, 1022.212524, 0.000009, -89.999992, -164.999816, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1098.355712, -2235.381347, 1019.841064, 0.000009, 0.000000, -164.999816, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19527, 1089.848632, -2261.466308, 1021.652038, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2905, 1089.750000, -2261.375732, 1022.282104, 55.900012, 0.000000, 39.099998, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2908, 1089.969360, -2261.531494, 1022.463684, -60.000000, 90.000000, 300.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(950, 1089.057861, -2262.750976, 1021.842224, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(950, 1090.377685, -2262.750976, 1021.842224, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1088.999267, -2269.744140, 1021.982299, 0.000000, -0.000018, -139.999755, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1089.021362, -2269.770507, 1022.212524, 0.000000, -90.000015, -139.999755, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1089.046630, -2269.691406, 1019.841064, 0.000000, -0.000018, -139.999755, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2907, 1119.549560, -2242.509033, 1021.982360, -90.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2905, 1119.219604, -2242.599121, 1021.782165, 0.000000, 90.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2905, 1119.219604, -2242.388916, 1021.782165, 0.000000, 90.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2908, 1119.476074, -2242.479003, 1022.509338, -110.000000, 90.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(341, 1118.895751, -2242.526611, 1022.460205, 0.000000, 40.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2060, 1125.265502, -2275.016113, 1022.681396, -0.000007, 90.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2060, 1125.265502, -2275.016113, 1023.581115, -0.000007, 90.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(2060, 1125.265502, -2275.016113, 1023.581115, 89.999992, 89.999992, -89.999992, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(841, 1125.453002, -2274.859375, 1021.742126, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1125.201171, -2275.213867, 1020.250976, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1123.494140, -2235.355468, 1021.982299, 0.000009, 0.000000, -164.999816, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1123.502929, -2235.388671, 1022.212524, 0.000009, -89.999992, -164.999816, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1123.559204, -2235.327636, 1019.841064, 0.000009, 0.000000, -164.999816, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1138.881958, -2241.658203, 1021.982299, 0.000007, -0.000004, -164.999771, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1138.890747, -2241.691406, 1022.212524, 0.000007, -90.000000, -164.999771, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1138.947021, -2241.630371, 1019.841064, 0.000007, -0.000004, -164.999771, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1137.977905, -2254.117431, 1021.982299, 0.000003, -0.000027, 150.000198, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1137.960815, -2254.146972, 1022.212524, 0.000003, -90.000022, 150.000198, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1138.043823, -2254.143554, 1019.841064, 0.000003, -0.000027, 150.000198, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1137.677612, -2265.169433, 1021.982299, 0.000007, -0.000034, 150.000152, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1137.660522, -2265.198974, 1022.212524, 0.000007, -90.000030, 150.000152, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1137.743530, -2265.195556, 1019.841064, 0.000007, -0.000034, 150.000152, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1153.558227, -2267.812011, 1021.982299, 0.000012, -0.000040, 150.000106, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1153.541137, -2267.841552, 1022.212524, 0.000012, -90.000038, 150.000106, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1153.624145, -2267.838134, 1019.841064, 0.000012, -0.000040, 150.000106, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1132.588134, -2280.543212, 1021.982299, 0.000014, -0.000047, 150.000061, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1132.571044, -2280.572753, 1022.212524, 0.000014, -90.000045, 150.000061, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1132.654052, -2280.569335, 1019.841064, 0.000014, -0.000047, 150.000061, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1111.740234, -2286.957519, 1021.982299, 0.000014, -0.000047, -29.999942, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1111.757324, -2286.927978, 1022.212524, 0.000014, -90.000045, -29.999942, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1111.674316, -2286.931396, 1019.841064, 0.000014, -0.000047, -29.999942, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19320, 1095.761718, -2287.468017, 1021.982299, 0.000012, -0.000040, -29.999937, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(19528, 1095.778808, -2287.438476, 1022.212524, 0.000012, -90.000038, -29.999937, -1, -1, -1, 120.00, 120.00);
        tmpobjid = CreateDynamicObject(18688, 1095.695800, -2287.441894, 1019.841064, 0.000012, -0.000040, -29.999937, -1, -1, -1, 120.00, 120.00);
    #endif
    return 1;
}


CMD:takegift(playerid, params[])
{
    if(p_info[playerid][gift_check] != 1) return SendError(playerid, "У Вас нет наград за празднование.");
    new idx = p_info[playerid][gift_idx], gift_prize_money[10] = {2500000, 2250000, 2000000, 1750000, 1500000, 1250000, 1000000, 750000, 500000, 250000};
    new accessories_idx = 510, money = gift_prize_money[idx];
    if(!GivePlayerInventory(playerid, accessories_idx, .reason = "/takegift")) return 1;
    SetPlayerMoney(playerid, money, true, "/takegift");
    SendAccess(playerid, "Вам выдан аксессуар \"%s\" и %d$.", ItemsInfo[accessories_idx][iName], money);
    p_info[playerid][gift_check] = 2;
    MysqlUpdatePlayerInt(playerid, "gift_check", p_info[playerid][gift_check]);

    Log(LOG_player, INFO, "%s[%d](%s %s) забрал награду за празднование, уникальный аксессуар %s и %d$",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", ItemsInfo[accessories_idx][iName], money);
    return 1;
}


GiveGiftGiftPrize()
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `gift` != 0 ORDER BY `gift` DESC LIMIT 10");
    new Cache:result = mysql_query(con_bd, STRING_GLOBAL);
    if(cache_num_rows())
    {
        new _id;
        for(new i; i < 10; i++)
        {
            if(i >= cache_num_rows()) break;
            cache_get_value_name_int(i, "id", _id);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `gift_check` = 1, `gift_idx` = %d WHERE `id` = %d",
            i, _id);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return cache_delete(result);
}

forward ShowInfoGift(playerid);
public ShowInfoGift(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
    Дорогие друзья! Мы поздравляем Вас с "I"Пасхой!"W" В связи с этим мы проводим небольшой праздник.\n\
    Ведь именно за счёт любимых игроков мы отмечаем этот праздник и готовы продолжать отмечать его вновь.\n\n\
    С "I"14 апреля по 30 апреля"W" на праздничной площади можно пройти "I"тематический квест."W" Кроме этого, за каждый\n\
    час игры выдается "I"пасхальные яйца,"W" которые можно обменять на новые уникальные предметы на "I"праздничной площади."W"\n\
    Получить яйцо можно не только каждый час, но и "I"при нахождении яиц. За нахождение схрона яиц выдается "I"5-10 шт,\n\
    "W" а расположены они в укромных местах. По окончанию празднования "I"будут определены 10 игроков,"W" которые нашли\n\
    наибольшее количество схронов. Каждый из этих игроков получит денежное вознаграждение в размере:\n\
    "I"1 место"W" — 5.000.000$, "I"2 место"W" — 4.500.000$, "I"3 место"W" — 4.000.000$, "I"4 место"W" — 3.500.000$, "I"5 место"W" — 3.000.000$,\n\
    "I"6 место"W" — 2.500.000$, "I"7 место"W" — 2.000.000$, "I"8 место"W" — 1.500.000$, "I"9 место"W" — 1.000.000$ и "I"10 место"W" — 500.000$.\n\n\
    Яиц в инвентаре: "I"%d шт."W"\n\
    Всего найдено мест с яцами: "I"%d шт.", GetInventoryAmount(playerid, 894), p_info[playerid][gift]);
    ShowPlayerDialog(playerid, D_GIFT, DIALOG_STYLE_MSGBOX, ""I"Празднование  Пасхи", STRING_GLOBAL, "ТОП-10", "Закрыть");
    return 1;
}

CMD:gift(playerid, params[])
{
    ShowInfoGift(playerid);
    return 1;
}

enum E_CHANGE_GIFT_COINS
{
    cbcType,
    cbcIDx,
    cbcPrice,
    cbcMax
}

new ChangeGiftCoinsWarehouse[MAX_GIFT_CHANGE_COINS];

new ChangeGiftCoins[MAX_GIFT_CHANGE_COINS][E_CHANGE_GIFT_COINS] = {
    {TYPE_CHANGE_VEHICLE, 431, 2500, 5}, // Coach;
    {TYPE_CHANGE_VEHICLE, 437, 2500, 5}, // Bus;
    {TYPE_CHANGE_VEHICLE, 525, 2500, 5}, // Towtruck;
    {TYPE_CHANGE_VEHICLE, 428, 2500, 5}, // Securicar;
    {TYPE_CHANGE_VEHICLE, 407, 2500, 5}, // Firetruck LA;
    {TYPE_CHANGE_VEHICLE, 544, 2500, 5}, // Firetruck LA;
    {TYPE_CHANGE_VEHICLE, 552, 2500, 5}, // Utility Van;
    {TYPE_CHANGE_VEHICLE, 403, 2500, 5}, // Linerunner;
    {TYPE_CHANGE_VEHICLE, 514, 2500, 5}, // Tanker;
    {TYPE_CHANGE_VEHICLE, 515, 2500, 5}, // Roadtrain;
	{TYPE_CHANGE_VEHICLE, 5090, 3000, 5}, // VAZ 2102;
	{TYPE_CHANGE_VEHICLE, 5095, 3000, 5}, // УАЗ;
	{TYPE_CHANGE_VEHICLE, 4763, 3200, 5}, // Tesla Cybertruck;
    {TYPE_CHANGE_ROULETTE, 644, 100, 250}, // Gold рулетка;
    {TYPE_CHANGE_ROULETTE, 643, 50, 500}, // Silver рулетка;
    {TYPE_CHANGE_ROULETTE, 642, 25, 1000}, // Bronze рулетка;
    {TYPE_CHANGE_ACCESSORIES, 558, 500, 10}, // ПНВ #1;
    {TYPE_CHANGE_ACCESSORIES, 559, 500, 10}, // ПНВ #2;
    {TYPE_CHANGE_ACCESSORIES, 586, 500, 10}, // Нимб;
    {TYPE_CHANGE_ACCESSORIES, 587, 500, 10}, // Крылья;
    {TYPE_CHANGE_ACCESSORIES, 464, 500, 10}, // Попугай;
    {TYPE_CHANGE_ACCESSORIES, 438, 400, 10}, // Чемодан Rockstar;
    {TYPE_CHANGE_ACCESSORIES, 445, 400, 10}, // Бронежилет S. W. A. T;
    {TYPE_CHANGE_ACCESSORIES, 626, 400, 10}, // Карлсон;
    {TYPE_CHANGE_ACCESSORIES, 620, 400, 10}, // Мельница;
    {TYPE_CHANGE_ACCESSORIES, 625, 300, 10}, // Шаурма;
    {TYPE_CHANGE_ACCESSORIES, 605, 300, 10}, // Нож в голове;
    {TYPE_CHANGE_ACCESSORIES, 606, 300, 10}, // Туалетная бумага;
	{TYPE_CHANGE_ACCESSORIES, 618, 300, 10}, // Костюм бегемота;
    {TYPE_CHANGE_ACCESSORIES, 451, 200, 10}, // Доска Rockstar;
    {TYPE_CHANGE_ACCESSORIES, 452, 200, 10}, // Разноцветная доска;
    {TYPE_CHANGE_ACCESSORIES, 453, 200, 10}, // Доска с пальмами;
    {TYPE_CHANGE_ACCESSORIES, 458, 100, 10}, // Белый шлем S. W. A. T;
    {TYPE_CHANGE_ACCESSORIES, 459, 100, 10}, // Черный шлем S. W. A. T;
    {TYPE_CHANGE_ACCESSORIES, 876, 1000, 10}, // Мигалка скорой помощи (деталь тюнинга);
	{TYPE_CHANGE_ACCESSORIES, 888, 750, 10}, // Леденец (деталь тюнинга);
	{TYPE_CHANGE_ACCESSORIES, 879, 750, 10}, // Знак 'Продается'(деталь тюнинга);
	{TYPE_CHANGE_ACCESSORIES, 889, 500, 10}, // Cердце (деталь тюнинга);	
    {TYPE_CHANGE_SKIN, 760, 3500, 5}, // Real Skins "ID:1202";
	{TYPE_CHANGE_SKIN, 746, 2500, 5}, // Real Skins "ID:799";
	{TYPE_CHANGE_SKIN, 755, 2000, 5}, // Real Skins "ID:1197";
	{TYPE_CHANGE_SKIN, 754, 2000, 5} // Real Skins "ID:1196";
};

ShowGiftChangeCoins(playerid)
{
    STRING_GLOBAL = "[#] Название\tКоличество яиц\tКоличество на складе\n", STRING_MIN[0] = EOS;
    for(new i = 0; i < MAX_GIFT_CHANGE_COINS; i++)
    {
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\t%d из %d\n", i + 1, GetChangeCivilCoinsName(ChangeGiftCoins[i][cbcType], ChangeGiftCoins[i][cbcIDx]), GetChangeGiftCoinsPrice(i), ChangeGiftCoinsWarehouse[i], ChangeGiftCoins[i][cbcMax]);
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_GIFT_CHANGE_COINS, DIALOG_STYLE_TABLIST_HEADERS, ""I"Обмен яиц", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}


GetChangeGiftCoinsPrice(idx)
{
    new price = ChangeGiftCoins[idx][cbcPrice], check = ChangeGiftCoins[idx][cbcMax] - ChangeGiftCoinsWarehouse[idx];
    price = price + (price / ChangeGiftCoins[idx][cbcMax]) * check;
    return price;
}

enum E_GIFT_INFO
{
    //gObject[26],
    gPickup,
    gArea,
    gCoordsMySQLIDx
};
new GiftInfo[MAX_GIFT_PICKUP][E_GIFT_INFO];

forward MySQLLoadGiftCoords(idx);
public MySQLLoadGiftCoords(idx)
{
    if(cache_num_rows())
    {
        new mysql_idx, Float:x, Float:y, Float:z, Float:r;
        cache_get_value_name_int(0, "id", mysql_idx);
        cache_get_value_name_float(0, "x", x);
        cache_get_value_name_float(0, "y", y);
        cache_get_value_name_float(0, "z", z);
        cache_get_value_name_float(0, "r", r);
        CreateGift(idx, mysql_idx, x, y, z, r);
        //printf("[GIFT]: %f,%f,%f", x, y, z);
    } else printf("[GIFT SYSTEM]: Яйцо %d не может быть создан, не найдены свободные координаты.");
    return 1;
}

CreateGift(idx, mysql_idx, Float:x, Float:y, Float:z, Float:r)
{
    #pragma unused r

    GiftInfo[idx][gCoordsMySQLIDx] = mysql_idx;

    /*
    new Float: ox, Float: oy, Float: oz, Float: orx, Float: ory, Float: orz;

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.026167, -0.225817, 0.104819, 0.000023, 179.999984, -28.500082, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][0] = CreateDynamicObject(19341, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][0], 0, 3922, "bistro", "mp_snow", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.026167, -0.225817, 0.874839, 0.000023, 179.999984, -28.500082, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][1] = CreateDynamicObject(19343, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][1], 0, 3922, "bistro", "mp_snow", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.034879, -0.220981, 1.514853, 0.000018, 179.999984, -28.500082, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][2] = CreateDynamicObject(2242, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][2], 0, 3922, "bistro", "mp_snow", 0xFFFFFFFF);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.349311, -0.391303, 0.957724, 89.999992, 31.255779, -149.755767, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][3] = CreateDynamicObject(1923, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][3], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.335864, -0.384125, 1.081747, 70.999938, 179.999908, 61.500171, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][4] = CreateDynamicObject(1923, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][4], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.303958, -0.366461, 1.185751, 60.099967, 179.999923, 61.500118, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][5] = CreateDynamicObject(1923, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][5], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.026167, -0.225817, 1.144735, -0.000018, 359.999969, 151.500030, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][6] = CreateDynamicObject(2242, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][6], 0, 2127, "cj_kitchen", "CJ_RED", 0xFFFFFFFF);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.203832, 0.303055, 1.212973, -0.000017, -180.000000, 151.499923, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][7] = CreateDynamicObject(19475, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][7], 0, 4810, "griffobs_las", "sm_pinetreebit", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.354836, -0.725392, 1.202963, 0.000017, 180.000000, -28.500082, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][8] = CreateDynamicObject(19475, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][8], 0, 4810, "griffobs_las", "sm_pinetreebit", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.149686, -0.403941, 1.515951, 89.999992, -148.744186, -149.755767, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][9] = CreateDynamicObject(322, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][9], 0, 14803, "bdupsnew", "Bdup2_wallpaperC", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.230769, -0.251412, 1.616415, 69.299903, -180.000015, 85.100036, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][10] = CreateDynamicObject(1923, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][10], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.155737, -0.402704, 1.612874, 69.299942, 179.999908, 40.600070, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][11] = CreateDynamicObject(1923, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][11], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.057159, -0.278349, 1.457724, -89.999992, 147.548873, 29.048856, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][12] = CreateDynamicObject(1509, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][12], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.024842, -0.317587, 1.467733, -89.999992, 147.548873, 29.048856, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][13] = CreateDynamicObject(1509, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][13], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.096448, -0.185752, 1.467733, -89.999992, 147.548873, 29.048856, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][14] = CreateDynamicObject(1509, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][14], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.081221, -0.234575, 1.457724, -89.999992, 147.548873, 29.048856, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][15] = CreateDynamicObject(1509, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][15], 0, 2749, "cj_hair", "cj_spec", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.493667, -0.996694, -0.002812, 0.000000, 0.000000, 30.000000, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][16] = CreateDynamicObject(19918, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][16], 0, 19058, "xmasboxes", "wrappingpaper1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.656132, -0.695432, 1.327186, 0.000000, 0.000000, 79.000000, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][17] = CreateDynamicObject(627, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][17], 0, 654, "gta_tree_oldpine", "tree19Mi", 0xFF90EE90);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.493667, -0.996694, 0.225187, 0.000000, 0.000000, 70.000000, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][18] = CreateDynamicObject(19918, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][18], 0, 19058, "xmasboxes", "wrappingpaper20", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.000000, 0.000000, 0.000000, 0.000037, 179.999969, 89.999885, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][19] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][19], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][19], 1, 3922, "bistro", "mp_snow", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.660888, -0.001951, -0.001996, 0.000037, 179.999969, 89.999885, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][20] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][20], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][20], 1, 3922, "bistro", "mp_snow", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.923667, -0.436694, -0.002812, 0.000015, -0.000003, 139.999938, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][21] = CreateDynamicObject(19918, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][21], 0, 19058, "xmasboxes", "wrappingpaper28", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, 0.000000, -0.798828, 0.000000, 0.000029, 179.999969, 89.999908, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][22] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][22], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][22], 1, 3922, "bistro", "mp_snow", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.660888, -0.800781, -0.001996, 0.000029, 179.999969, 89.999908, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][23] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][23], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][23], 1, 3922, "bistro", "mp_snow", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.923667, -0.436694, 0.225187, 0.000009, -0.000012, 179.999862, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][24] = CreateDynamicObject(19918, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(GiftInfo[idx][gObject][24], 0, 19058, "xmasboxes", "wrappingpaper16", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 90.0, -0.032700, -0.220851, 1.709555, -0.000023, 0.000023, 151.500030, ox, oy, oz, orx, ory, orz);
    GiftInfo[idx][gObject][25] = CreateDynamicObject(19352, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    */

    GiftInfo[idx][gPickup] = CreateDynamicPickup(19341+random(4), 23, x, y, z, 0, 0, -1, 25.0);

    GiftInfo[idx][gArea] = CreateDynamicSphere(x, y, z, 2.5, 0, 0, -1);
    UpdateAreaInfo(GiftInfo[idx][gArea], TYPE_GIFT, AREA_SUBTYPE_INVALID_ID, idx);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `box_coords` SET `status` = 1 WHERE `id` = %d",
    mysql_idx);
    mysql_tquery(con_bd, STRING_GLOBAL);

    gift_pickups_count++;

    //printf("/tpcor %f,%f,%f 0,0", x,y+3,z);
    return 1;
}

OnPlayerOpenGift(playerid, idx)
{
    new aggs = 10+random(MAX_GIFT_COINS);
    if(!GivePlayerInventory(playerid, 894, aggs)) return SendError(playerid, "В инвентаре нет места.");
    p_info[playerid][gift]++;
    MysqlUpdatePlayerInt(playerid, "gift", p_info[playerid][gift]);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
        Ты нашел клад пасхальных яиц."W"\n\n\
        Яиц в инвентаре: "I"%d шт."W"\n\n\
        Всего найдено тайников яиц: "I"%d шт.", aggs, GetInventoryAmount(playerid, 894), p_info[playerid][gift]);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Тайник с яицами", STRING_GLOBAL, "Закрыть", "");
    DestroyGift(idx);

    if(p_info[playerid][event_quest_id] == 7)
    {
        p_info[playerid][event_quest_stage] += aggs;
        ShowEasterQuest_Check(playerid);
    }
    return 1;
}

DestroyGift(idx)
{
    /*
    for(new i = 0; i < 26; i++)
    {
        if(GiftInfo[idx][gObject][i] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(GiftInfo[idx][gObject][i]);
            GiftInfo[idx][gObject][i] = INVALID_OBJECT_ID;
        }
    }
    */

    DestroyDynamicPickup(GiftInfo[idx][gPickup]);
    GiftInfo[idx][gPickup] = -1;
    
    DestroyDynamicArea(GiftInfo[idx][gArea]);
    GiftInfo[idx][gArea] = -1;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `box_coords` SET `status` = 0 WHERE `id` = %d",
    GiftInfo[idx][gCoordsMySQLIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    GiftInfo[idx][gCoordsMySQLIDx] = 0;

    gift_pickups_count--;
    return 1;
}

forward OnPlayerShowListSearchGift(playerid);
public OnPlayerShowListSearchGift(playerid)
{
    if(!cache_num_rows())
        return SendError(playerid, "Ничего не найдено.");
    new nickname[32], iGift;
    STRING_GLOBAL = ""W"[#] Ник\tКоличество найденных мест с яицами\n", STRING_MIN[0] = EOS;
    for(new i; i < 25; i++)
    {
        if(i >= cache_num_rows()) break;
        cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
        cache_get_value_name_int(i, "gift", iGift);
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\n", i+1, nickname, iGift);
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП 10 игроков", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

#if EVENT_HALLOWEEN == 1
    HalloweenQuest_Main(playerid)
    {
        switch(p_info[playerid][halloween_id])
        {
            case 1:
            {
                ShowPlayerDialog(playerid, D_HALLOWEEN_QUEST_MAIN, DIALOG_STYLE_MSGBOX, ""I"Сладость или гадость!", ""W"\
                    Хай! Хеллоуин в самом разгаре и у меня есть для тебя парочка заданий.\n\
                    За выполнение каждого буду вознаграждать тебя.\n\n\
                    Итак, первое: тебе нужно обойти несколько домов и попросить у хозяев конфеты.\n\
                    Я тебе дам мешок для конфет и яйца — все это тебе пригодится.\n\
                    Как соберешь достаточно конфет, возвращайся ко мне.\n\n\
                    Награда за квест: "I"100000$ и 50 Flin Money", "Далее", "Отмена");
            }
            case 2:
            {
                ShowPlayerDialog(playerid, D_HALLOWEEN_QUEST_MAIN, DIALOG_STYLE_MSGBOX, ""I"Визит усопших", ""W"\
                    Следующее задание для тебя будет не такое веселое как это: тебе нужно нарвать\n\
                    3 букета цветов в поле (поищи на ферме) и вознести их к могилам родственников\n\
                    на кладбище. Ведь помнить своих предков — очень важно.\n\n\
                    Награда за квест: "I"50000$ и 25 Flin Money", "Далее", "Отмена");
            }
            case 3:
            {
                ShowPlayerDialog(playerid, D_HALLOWEEN_QUEST_MAIN, DIALOG_STYLE_MSGBOX, ""I"Пора собирать урожай!", ""W"\
                    Сегодня последний день сбора урожая, ведь ночью в него могут вселиться злые духи.\n\
                    Съезди на ферму и помоги работникам собрать урожай.\n\n\
                    Награда за квест: "I"50000$ и 25 Flin Money", "Далее", "Отмена");
            }
            case 4:
            {
                ShowPlayerDialog(playerid, D_HALLOWEEN_QUEST_MAIN, DIALOG_STYLE_MSGBOX, ""I"Поиграем?", ""W"\
                    Поработал? Теперь можно и развеяться! В Хеллоуин принято играть в азартные игры и\n\
                    выпивать. Так что, съезди в казино и сделай хотя бы одну ставку. А по дороге назад\n\
                    купи себе выпивки в любом баре.\n\n\
                    Награда за квест: "I"50000$", "Далее", "Отмена");
            }
            case 5:
            {
                ShowPlayerDialog(playerid, D_HALLOWEEN_QUEST_MAIN, DIALOG_STYLE_MSGBOX, ""I"Выхода нет?", ""W"\
                    Напоследок у меня для тебя есть довольно непростая задача. Отправляйся на место,\n\
                    отмеченное на карте, и реши мою головоломку. И помни: скоро рассвет, а выход есть.\n\n\
                    Награда за квест: "I"100000$, 50 Flin Money и уникальный аксессуар \"Маска демона\".", "Далее", "Отмена");
            }
        }
        return 1;
    }

    HalloweenQuest_Check(playerid)
    {
        switch(p_info[playerid][halloween_id])
        {
            case 1:
            {
                if(p_info[playerid][halloween_progress] < 3)
                {
                    new houseId = random(totalhouses-2)+1;
                    SetPVarInt(playerid, "HALLOWEEN:HOUSE_ID", houseId);
                    if(p_temp[playerid][p_GPS] == true) CancelPlayerGPS(playerid);
                    SetPlayerCheckpoint(playerid, h_info[houseId][h_enter][0], h_info[houseId][h_enter][1], h_info[houseId][h_enter][2], 1.5);
                    SendInfo(playerid, "Для сбора конфет отправляйтесь на место, отмеченное на GPS навигаторе.");
                    SendInfo(playerid, "Прогресс выполнения задания: %d из 3.", p_info[playerid][halloween_progress]);
                }
                else
                {
                    SetPlayerMoney(playerid, 100000, true, "HALLOWEEN: квест 1");
                    p_info[playerid][flinmoney] += 50;

                    p_info[playerid][halloween_id] = 2;
                    p_info[playerid][halloween_progress] = 0;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `halloween_id` = %d, `halloween_progress` = %d, `flinmoney` = %d WHERE `id` = %d",
                    p_info[playerid][halloween_id], p_info[playerid][halloween_progress], p_info[playerid][flinmoney], p_info[playerid][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 100000$ и 50 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 0.0, 0.0, 0.0);
                }
            }
            case 2:
            {
                if(p_info[playerid][halloween_progress] < 3)
                {
                    if(p_info[playerid][halloween_progress] == 0)
                    {
                        SendInfo(playerid, "Для сбора конфет отправляйтесь на место, отмеченное на GPS навигаторе.");
                        SetPlayerGPS(playerid, -385.1386,-1456.9720,25.7266, 2.5);
                    }
                    SendInfo(playerid, "Прогресс выполнения задания: %d из 3.", p_info[playerid][halloween_progress]);
                }
                else if(3 <= p_info[playerid][halloween_progress] < 6)
                {
                    new graver_id = random(MAX_HALLOWEEN_GRAVES);
                    SetPVarInt(playerid, "HALLOWEEN:GRAVER_ID", graver_id+1);
                    if(p_temp[playerid][p_GPS] == true) CancelPlayerGPS(playerid);
                    SetPlayerCheckpoint(playerid, halloween_graves_pos[graver_id][0], halloween_graves_pos[graver_id][1], halloween_graves_pos[graver_id][2], 2.5);
                    if(p_info[playerid][halloween_progress] == 3) SendInfo(playerid, "Для возложения цветов отправляйтесь на место, отмеченное на GPS навигаторе.");
                    SendInfo(playerid, "Прогресс выполнения задания: %d из 3.", p_info[playerid][halloween_progress] - 3);
                }
                else
                {
                    SetPlayerMoney(playerid, 50000, true, "HALLOWEEN: квест 1");
                    p_info[playerid][flinmoney] += 25;

                    p_info[playerid][halloween_id] = 3;
                    p_info[playerid][halloween_progress] = 0;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `halloween_id` = %d, `halloween_progress` = %d, `flinmoney` = %d WHERE `id` = %d",
                    p_info[playerid][halloween_id], p_info[playerid][halloween_progress], p_info[playerid][flinmoney], p_info[playerid][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 50000$ и 25 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 0.0, 0.0, 0.0, 6.0);
                }
            }
            case 3:
            {
                if(p_info[playerid][halloween_progress] >= 10)
                {
                    SetPlayerMoney(playerid, 50000, true, "HALLOWEEN: квест 3");
                    p_info[playerid][flinmoney] += 25;

                    p_info[playerid][halloween_id] = 4;
                    p_info[playerid][halloween_progress] = 0;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `halloween_id` = %d, `halloween_progress` = %d, `flinmoney` = %d WHERE `id` = %d",
                    p_info[playerid][halloween_id], p_info[playerid][halloween_progress], p_info[playerid][flinmoney], p_info[playerid][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 50000$ и 25 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 0.0, 0.0, 0.0, 6.0);
                }
                else if(p_info[playerid][halloween_progress] == 0)
                {
                    SendInfo(playerid, "Для помощи рабочим отправляйтесь на место, обозначенное на GPS навигаторе.");
                    SetPlayerGPS(playerid, -385.1386,-1456.9720,25.7266, 2.5);
                }
                else SendInfo(playerid, "Прогресс выполнения задания: %d из 10.", p_info[playerid][halloween_progress]);
            }
            case 4:
            {
                if(p_info[playerid][halloween_progress] >= 2)
                {
                    SetPlayerMoney(playerid, 50000, true, "HALLOWEEN: квест 4");

                    p_info[playerid][halloween_id] = 5;
                    p_info[playerid][halloween_progress] = 0;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `halloween_id` = %d, `halloween_progress` = %d, `flinmoney` = %d WHERE `id` = %d",
                    p_info[playerid][halloween_id], p_info[playerid][halloween_progress], p_info[playerid][flinmoney], p_info[playerid][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 50000$.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 0.0, 0.0, 0.0, 6.0);
                }
                //else SendInfo(playerid, "Прогресс выполнения задания: %d из 3.", p_info[playerid][halloween_progress]);
            }
            case 5:
            {
                if(p_info[playerid][halloween_progress] == 0)
                {
                    SendInfo(playerid, "Для прохождения последнего задания отправляйтесь на место, отмеченное на GPS навигаторе.");
                    SetPlayerGPS(playerid, -385.0632,-1469.8419,25.7266, 2.5);
                }
                else if(p_info[playerid][halloween_progress] == 1)
                {
                    SendInfo(playerid, "Найдите выход из этого проклятого лабиринта.");
                }
                else if(p_info[playerid][halloween_progress] == 2)
                {
                    SetPlayerMoney(playerid, 100000, true, "HALLOWEEN: квест 5");
                    p_info[playerid][flinmoney] += 50;
                    SetPlayerItem(playerid, 8, p_info[playerid][ID], TYPE_GIVE_ITEM_ACCESSORIES, 486);

                    p_info[playerid][halloween_id] = MAX_HALLOWEEN_QUEST_ID + 1;
                    p_info[playerid][halloween_progress] = 0;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `halloween_id` = %d, `halloween_progress` = %d, `flinmoney` = %d WHERE `id` = %d",
                    p_info[playerid][halloween_id], p_info[playerid][halloween_progress], p_info[playerid][flinmoney], p_info[playerid][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 100000$, 50 Flin Money и уникальный аксессуар \"Маска демона\".");
                    SendInfo(playerid, "Вы выполнили все задания, продолжайте празднование с сбором тыкв.");
                }
            }
        }
        return 1;
    }
#endif


CMD:testgift(playerid, params[])
{
    if(SRV_ID) return 1;
    ShowPlayerDialog(playerid, D_EASTER, DIALOG_STYLE_LIST, ""I"Празднование Пасхи", ""I"[1]"W" Праздничный квест\n"I"[2]"W" Обменять яица\n"I"[3]"W" Информация о праздновании и сборе яиц\n"I"[4]"W" Список игроков", "Далее", "Отмена");
    return 1;
}
/*
CMD:creategift(playerid, params[])
{
    if(SRV_ID || p_info[playerid][admin] < 10) return 1;

    if(gift_pickups_count < MAX_GIFT_PICKUP)
    {
        for(new i = 0; i < MAX_GIFT_PICKUP; i++)
        {
            if(GiftInfo[i][gCoordsMySQLIDx] == 0)
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `box_coords` WHERE `status` = 0 ORDER BY RAND() LIMIT 1");
                mysql_tquery(con_bd, STRING_GLOBAL, "MySQLLoadGiftCoords", "i", i);
                break;
            }
        }
    }
    return 1;
}
*/

CMD:resetgift(playerid)
{
    if(!FD(playerid) || p_info[playerid][admin] < 10)
        return 1;
    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_GIFT_CHANGE_COINS; i++)
    {
        ChangeGiftCoinsWarehouse[i] = ChangeGiftCoins[i][cbcMax];
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, ChangeGiftCoinsWarehouse[i], i == MAX_GIFT_CHANGE_COINS-1 ? "":",");
    }
    MysqlUpdateOtherStr("change_gift_coins_warehouse", STRING_GLOBAL);
    return 1;
}


