#define MAX_FLOWERS_GREEN_HOUSES        42

new Float:FlowersGreenHousesPos[MAX_FLOWERS_GREEN_HOUSES][6] =
{
    {969.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {971.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {973.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {975.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {977.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {979.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {981.011962, -2179.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {969.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {971.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {973.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {975.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {977.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {979.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {981.011962, -2171.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {969.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {971.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {973.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {975.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {977.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {979.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {981.011962, -2163.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {969.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {971.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {973.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {975.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {977.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {979.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {981.011962, -2155.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {969.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {971.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {973.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {975.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {977.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {979.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {981.011962, -2147.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {969.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {971.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {973.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {975.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {977.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {979.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000},
    {981.011962, -2139.159912, 12.723735, 0.000000, 0.000022, 0.000000}
};

enum E_FLOWERS_GREEN_HOUSES
{
    fPlayerID,
    fObject,
    fArea,
    fRespawn,
    Text3D:fText
};
new FlowersGreenHousesInfo[MAX_FLOWERS_GREEN_HOUSES][E_FLOWERS_GREEN_HOUSES];

CreateFlowers(idx)
{
    FlowersGreenHousesInfo[idx][fPlayerID] = INVALID_PLAYER_ID;
    FlowersGreenHousesInfo[idx][fRespawn] = 1;
    FlowersGreenHousesInfo[idx][fObject] = CreateDynamicObject(802, FlowersGreenHousesPos[idx][0], FlowersGreenHousesPos[idx][1], FlowersGreenHousesPos[idx][2], FlowersGreenHousesPos[idx][3], FlowersGreenHousesPos[idx][4], FlowersGreenHousesPos[idx][5], -1, -1, -1, 120.0, 120.0);
    FlowersGreenHousesInfo[idx][fArea] = CreateDynamicSphere(FlowersGreenHousesPos[idx][0], FlowersGreenHousesPos[idx][1], FlowersGreenHousesPos[idx][2], 1.0, -1, -1, -1);
    UpdateAreaInfo(FlowersGreenHousesInfo[idx][fArea], TYPE_GREEN_HOUSES, AREA_SUBTYPE_GH_FLOWERS, idx);
    SetDynamicObjectMaterial(FlowersGreenHousesInfo[idx][fObject], 0, 14816, "whore_furn", "WH_flowers1", 0x00000000);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Цветы\n\nСостояние: %s\nСтатус: %s", FlowersGreenHousesInfo[idx][fRespawn] == 0 ? "{"#cYELLOW"}Растет"I"" : "{"#cGREEN"}Можно собрать"I"", FlowersGreenHousesInfo[idx][fPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободно"I"" : "{"#cLIGHTRED"}Занято");
    FlowersGreenHousesInfo[idx][fText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FlowersGreenHousesPos[idx][0], FlowersGreenHousesPos[idx][1], FlowersGreenHousesPos[idx][2] + 1, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
    return 1;
}

CheckFlowers(idx)
{
    if(FlowersGreenHousesInfo[idx][fRespawn] == 0) SetDynamicObjectMaterial(FlowersGreenHousesInfo[idx][fObject], 0, 14816, "whore_furn", "WH_flowers1", 0x00000000);
    else SetDynamicObjectMaterial(FlowersGreenHousesInfo[idx][fObject], 0, 806, "gta_proc_rushes", "gras03Si", 0x00000000);
    FlowersGreenHousesInfo[idx][fRespawn] ^= 1;
    UpdateFlowers(idx);
    return 1;
}

UpdateFlowers(idx)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Цветы\n\nСостояние: %s\nСтатус: %s", FlowersGreenHousesInfo[idx][fRespawn] == 0 ? "{"#cYELLOW"}Растет"I"" : "{"#cGREEN"}Можно собрать"I"", FlowersGreenHousesInfo[idx][fPlayerID] == INVALID_PLAYER_ID ? "{"#cGREEN"}Свободно"I"" : "{"#cLIGHTRED"}Занято");
    UpdateDynamic3DTextLabelText(FlowersGreenHousesInfo[idx][fText], COLOR_MAIN, STRING_GLOBAL);
    return 1;
}

new pickup_ghouses;

LoadGreenHouses()
{
    CreateActor(44, 1002.5026,-2129.3123,13.2389,77.3836);
    CreateDynamic3DTextLabel("NPC: "I"Работник теплицы", COLOR_WHITE, 1002.5026,-2129.3123,13.2389 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_ghouses = CreatePickup(1275, 23, 1001.9818,-2129.1440,13.0938);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 1001.9818,-2129.1440,13.0938, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    new areaid = CreateDynamicSphere(999.1111,-2156.2717,13.0938, 2.5, -1, -1, -1);
    UpdateAreaInfo(areaid, TYPE_GREEN_HOUSES, AREA_SUBTYPE_GH_WAREHOUSE);
    CreateDynamicPickup(19134, 23, 999.1111,-2156.2717,13.0938);

    for(new i = 0; i < MAX_FLOWERS_GREEN_HOUSES; i++) CreateFlowers(i);

    new tmpobjid;

    tmpobjid = CreateDynamicObject(3362, 1000.255798, -2168.481933, 11.833745, 0.000000, -0.000014, 164.999908, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3502, "vgsncircon", "woodsuport1_128", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3063, "col_wall1x", "ab_wood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 9902, "coastground", "pierbuild_roof1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 3, 12946, "ce_bankalley1", "newindow13", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 4, 3374, "ce_farmxref", "sw_barndoor2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 5, 3698, "comedbarrio1_la", "compdoor1_LAe", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2177.991455, 9.463747, -89.999992, 90.000015, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2180.307373, 9.462745, -89.999992, -89.999946, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3246, 1000.793273, -2151.545166, 12.063749, 0.000000, 0.000000, -7.500000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3502, "vgsncircon", "woodsuport1_128", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3502, "vgsncircon", "woodsuport1_128", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 9902, "coastground", "pierbuild_roof1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 3, 14755, "sfhss2", "ah_rotwindow", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 4, 5520, "bdupshouse_lae", "compdoor4_LAe", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 5, 10606, "cluckbell_sfs", "ws_reinforcedbutwonky_small", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 1007.136535, -2118.926513, 13.533738, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2169.991455, 9.463747, -89.999992, 90.000015, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2172.307373, 9.462745, -89.999992, -89.999946, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(759, 981.375366, -2122.165771, 12.053749, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2161.991455, 9.463747, -89.999992, 90.000015, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2164.307373, 9.462745, -89.999992, -89.999946, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(1458, 997.756713, -2181.126220, 12.313755, 0.000000, 0.000000, -140.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 1, 14888, "gf6", "mp_millie_woodwall", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 3, 3241, "conhooses", "des_woodfence1", 0x00000000);
    tmpobjid = CreateDynamicObject(1452, 1003.826293, -2159.617675, 13.140094, -3.000000, 1.000000, -90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3374, "ce_farmxref", "sw_barnwood4", 0x00000000);
    tmpobjid = CreateDynamicObject(13206, 992.042175, -2185.718017, 12.093750, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 14888, "gf6", "mp_millie_wood", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3193, "cxref_desert", "sw_woodslat01", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2153.991455, 9.463747, -89.999992, 90.000015, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2156.307373, 9.462745, -89.999992, -89.999946, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2145.991455, 9.463747, -89.999992, 90.000015, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2148.307373, 9.462745, -89.999992, -89.999946, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2137.991455, 9.463747, -89.999992, 90.000015, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(3432, 975.078369, -2140.307373, 9.462745, -89.999992, -89.999946, 89.999961, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 17075, "cuntwlandwest", "desertstones256forestmix", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 16055, "des_quarry", "des_quarryrd", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 982.155700, -2118.926513, 13.533738, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 974.030639, -2123.187744, 13.533738, 0.000000, -0.000007, -124.600036, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 968.142822, -2131.720458, 13.533738, 0.000000, -0.000007, -124.600036, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 962.795104, -2140.570800, 13.533738, 0.000000, -0.000007, -117.700019, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 960.123229, -2150.332519, 13.533738, 0.000000, -0.000007, -92.900062, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 959.597839, -2160.687988, 13.533738, 0.000000, -0.000007, -92.900062, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 960.404541, -2170.940429, 13.533738, 0.000000, -0.000007, -78.100120, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 964.489929, -2180.229492, 13.533738, 0.000000, -0.000007, -54.400039, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 972.281005, -2186.454101, 13.533738, 0.000000, -0.000007, -22.800035, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 981.839843, -2190.469238, 13.533738, 0.000000, -0.000007, -22.800035, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 991.801696, -2192.479003, 13.533738, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(8674, 1002.163146, -2192.479003, 13.533738, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9902, "coastground", "coasty_fencet_sfe", 0x00000000);
    tmpobjid = CreateDynamicObject(3260, 998.828613, -2183.601318, 13.073744, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1407, "break_f_w", "CJ_SLATEDWOOD", 0x00000000);
    tmpobjid = CreateDynamicObject(3260, 996.838806, -2183.601318, 13.073744, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1407, "break_f_w", "CJ_SLATEDWOOD", 0x00000000);
    tmpobjid = CreateDynamicObject(3286, 981.011718, -2185.501953, 16.763740, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 14776, "genintintcarint3", "Metal2_256128", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 2917, "a51_crane", "quarry_conv_belt_struct", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.207885, -2183.957763, 11.663740, -89.999992, 179.999984, 90.000007, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 982.607360, -2183.943847, 12.969749, -89.999992, 179.999984, 90.000007, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 983.883056, -2183.963623, 12.337982, 50.000011, 0.000045, 89.999954, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 983.763244, -2183.955322, 12.234665, 39.999954, -0.000070, -89.999786, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 981.995788, -2174.852294, 10.993736, -89.999992, 29.675956, 119.675918, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.027282, -2176.147460, 12.222204, -2.999991, 270.000000, 179.999832, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19598, "sfbuilding1", "darkwood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 981.781311, -2174.862304, 11.983746, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 981.752563, -2174.843994, 12.251032, 19.999916, 0.000071, -89.999847, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 981.804748, -2174.852294, 12.101642, 69.999984, -0.000247, 90.000152, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19835, 982.490478, -2177.443603, 12.153750, 0.000000, -89.999992, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3272, "ele_substation", "des_substa_bit2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "ventb128", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 981.995788, -2166.852294, 10.993736, -89.999992, 29.675956, 119.675918, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.027282, -2168.147460, 12.222204, -2.999991, 270.000000, 179.999832, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19598, "sfbuilding1", "darkwood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 981.781311, -2166.862304, 11.983746, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 981.752563, -2166.843994, 12.251032, 19.999916, 0.000071, -89.999847, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 981.804748, -2166.852294, 12.101642, 69.999984, -0.000247, 90.000152, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19835, 982.490478, -2169.443603, 12.153750, 0.000000, -89.999992, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3272, "ele_substation", "des_substa_bit2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "ventb128", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 981.995788, -2158.852294, 10.993736, -89.999992, 29.675956, 119.675918, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.027282, -2160.147460, 12.222204, -2.999991, 270.000000, 179.999832, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19598, "sfbuilding1", "darkwood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 981.781311, -2158.862304, 11.983746, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 981.752563, -2158.843994, 12.251032, 19.999916, 0.000071, -89.999847, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 981.804748, -2158.852294, 12.101642, 69.999984, -0.000247, 90.000152, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19835, 982.490478, -2161.443603, 12.153750, 0.000000, -89.999992, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3272, "ele_substation", "des_substa_bit2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "ventb128", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 981.995788, -2150.852294, 10.993736, -89.999992, 29.675956, 119.675918, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.027282, -2152.147460, 12.222204, -2.999991, 270.000000, 179.999832, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19598, "sfbuilding1", "darkwood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 981.781311, -2150.862304, 11.983746, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 981.752563, -2150.843994, 12.251032, 19.999916, 0.000071, -89.999847, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 981.804748, -2150.852294, 12.101642, 69.999984, -0.000247, 90.000152, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19835, 982.490478, -2153.443603, 12.153750, 0.000000, -89.999992, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3272, "ele_substation", "des_substa_bit2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "ventb128", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 981.995788, -2142.852294, 10.993736, -89.999992, 29.675956, 119.675918, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.027282, -2144.147460, 12.222204, -2.999991, 270.000000, 179.999832, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19598, "sfbuilding1", "darkwood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 981.781311, -2142.862304, 11.983746, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 981.752563, -2142.843994, 12.251032, 19.999916, 0.000071, -89.999847, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 981.804748, -2142.852294, 12.101642, 69.999984, -0.000247, 90.000152, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19835, 982.490478, -2145.443603, 12.153750, 0.000000, -89.999992, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3272, "ele_substation", "des_substa_bit2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "ventb128", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 981.995788, -2134.852294, 10.993736, -89.999992, 29.675956, 119.675918, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19759, 983.027282, -2136.147460, 12.222204, -2.999991, 270.000000, 179.999832, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19598, "sfbuilding1", "darkwood1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(2709, 981.781311, -2134.862304, 11.983746, 0.000000, 0.000014, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
    tmpobjid = CreateDynamicObject(19836, 981.752563, -2134.843994, 12.251032, 19.999916, 0.000071, -89.999847, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 7103, "vgnplantgen", "metalwheel4_128", 0x00000000);
    tmpobjid = CreateDynamicObject(19610, 981.804748, -2134.852294, 12.101642, 69.999984, -0.000247, 90.000152, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19835, 982.490478, -2137.443603, 12.153750, 0.000000, -89.999992, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 3272, "ele_substation", "des_substa_bit2", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 16640, "a51", "ventb128", 0x00000000);
    tmpobjid = CreateDynamicObject(760, 963.203002, -2175.214599, 12.043746, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(12957, 1002.113220, -2162.553710, 12.783764, 0.000000, 0.000000, -120.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 1, 1259, "billbrd", "bluemetal02", 0x00000000);
    tmpobjid = CreateDynamicObject(1357, 996.495422, -2149.958740, 12.363756, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sjmlawarplt", 0x00000000);
    tmpobjid = CreateDynamicObject(1358, 1002.455261, -2143.400878, 13.273771, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 1, 18996, "mattextures", "garbagepile1", 0x00000000);
    tmpobjid = CreateDynamicObject(851, 1003.175476, -2157.123779, 12.323755, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 10987, "coveredpath_sfs", "ws_sheetwood", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 18293, "cs_mountain", "ffbranch_mountdirt", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(1448, 960.999267, -2168.326904, 12.163750, 0.000000, 0.000000, -10.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sjmlawarplt", 0x00000000);
    tmpobjid = CreateDynamicObject(19736, 1005.897338, -2128.784667, 15.174336, -16.000000, 0.000000, 70.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 18246, "cw_junkyard2cs_t", "Was_scrpyd_trailer_front", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 18246, "cw_junkyard2cs_t", "Was_scrpyd_carhood", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 4, 18246, "cw_junkyard2cs_t", "Was_scrpyd_trailer_join", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 6, 18246, "cw_junkyard2cs_t", "Was_scrpyd_trailer_door", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 7, 1736, "cj_ammo", "CJ_WHEEL1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 8, 18246, "cw_junkyard2cs_t", "Was_scrpyd_carhood", 0x00000000);
    tmpobjid = CreateDynamicObject(16317, 979.662841, -2126.774658, 9.433744, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 5462, "glenpark6_lae", "dirty256", 0x00000000);
    tmpobjid = CreateDynamicObject(18074, 982.830627, -2187.090576, 9.903738, 90.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(18074, 982.830627, -2186.990478, 9.903738, 90.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    tmpobjid = CreateDynamicObject(19718, 997.947570, -2171.412841, 10.133739, -90.000000, -0.000014, 164.999908, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(19718, 997.878295, -2171.676269, 10.273740, -90.000000, -0.000014, 164.999908, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3272, "ele_substation", "lasjmpow92", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    tmpobjid = CreateDynamicObject(759, 990.767028, -2161.854736, 12.463754, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(870, 992.690551, -2173.328125, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(870, 987.460083, -2152.097900, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(870, 997.940185, -2160.218750, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(1449, 997.185424, -2170.415039, 12.583757, 0.000000, 0.000000, -105.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sjmlawarplt", 0x00000000);
    tmpobjid = CreateDynamicObject(759, 978.664916, -2128.707031, 12.473748, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(1448, 960.999267, -2168.326904, 12.303753, 0.000000, 0.000000, 20.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3630, "compthotrans_la", "sjmlawarplt", 0x00000000);
    tmpobjid = CreateDynamicObject(3168, 1004.389160, -2129.358398, 12.043747, 0.000000, 0.000000, -20.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 18246, "cw_junkyard2cs_t", "Was_scrpyd_trailer_front", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 18246, "cw_junkyard2cs_t", "Was_scrpyd_carhood", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 4, 18246, "cw_junkyard2cs_t", "Was_scrpyd_trailer_join", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 6, 18246, "cw_junkyard2cs_t", "Was_scrpyd_trailer_door", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 7, 1736, "cj_ammo", "CJ_WHEEL1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 8, 18246, "cw_junkyard2cs_t", "Was_scrpyd_carhood", 0x00000000);
    tmpobjid = CreateDynamicObject(746, 987.525634, -2121.206298, 12.123749, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 17685, "landcoast_lae2", "rockwall2_LAe2", 0x00000000);
    tmpobjid = CreateDynamicObject(11734, 1002.847351, -2127.165283, 12.123749, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 14415, "carter_block_2", "mp_gs_woodpanel1", 0x00000000);
    tmpobjid = CreateDynamicObject(1670, 1002.712036, -2127.944824, 12.943750, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 1486, "break_bar", "CJ_bottle", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 3, 2958, "cut_beer", "bottles_kb1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 6, 1486, "break_bar", "CJ_bottle2", 0x00000000);
    tmpobjid = CreateDynamicObject(1431, 1003.774658, -2125.592529, 12.613759, 0.000000, 0.000000, 70.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 9583, "bigshap_sfw", "freight_crate7", 0x00000000);
    tmpobjid = CreateDynamicObject(1407, 984.217529, -2121.336914, 12.803750, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3083, "billbox", "ADDWOOD", 0x00000000);
    tmpobjid = CreateDynamicObject(1407, 984.217529, -2126.007812, 12.803750, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3083, "billbox", "ADDWOOD", 0x00000000);
    tmpobjid = CreateDynamicObject(1407, 984.217529, -2130.682373, 12.803750, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3083, "billbox", "ADDWOOD", 0x00000000);
    tmpobjid = CreateDynamicObject(760, 974.042846, -2134.180419, 12.043746, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(759, 1002.035461, -2137.806640, 12.053749, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(759, 1005.495666, -2121.754638, 12.053749, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(870, 994.960021, -2140.417236, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(870, 986.779785, -2135.585205, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(870, 998.560241, -2124.444335, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(14402, 992.825195, -2131.501953, 12.793749, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
    tmpobjid = CreateDynamicObject(635, 997.126953, -2152.118164, 14.805842, -2.300000, -90.000000, -7.500000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
    SetDynamicObjectMaterial(tmpobjid, 1, 3502, "vgsncircon", "woodsuport1_128", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 2, 9902, "coastground", "pierbuild_roof1", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 3, 14755, "sfhss2", "ah_rotwindow", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 4, 5520, "bdupshouse_lae", "compdoor4_LAe", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 5, 10606, "cluckbell_sfs", "ws_reinforcedbutwonky_small", 0x00000000);
    tmpobjid = CreateDynamicObject(3529, 1000.634521, -2170.662597, 13.443744, 0.000000, 0.000000, -15.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3502, "vgsncircon", "woodsuport2_128", 0x00000000);
    tmpobjid = CreateDynamicObject(18725, 1000.634521, -2170.662597, 14.993755, 0.000000, 0.000000, -15.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 3502, "vgsncircon", "woodsuport2_128", 0x00000000);
    tmpobjid = CreateDynamicObject(870, 964.829833, -2167.090087, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(870, 961.849731, -2155.618896, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(870, 965.359924, -2140.427490, 12.213751, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 849, "junkpiles", "CJgrass", 0xFFFFFFFF);
    tmpobjid = CreateDynamicObject(1458, 962.012695, -2149.947509, 12.313755, 0.000000, 0.000000, -140.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 1, 14888, "gf6", "mp_millie_woodwall", 0x00000000);
    SetDynamicObjectMaterial(tmpobjid, 3, 3241, "conhooses", "des_woodfence1", 0x00000000);
    tmpobjid = CreateDynamicObject(2662, 961.081848, -2162.577636, 14.230326, 0.000000, 3.000000, 85.000000, -1, -1, -1, 120.00, 120.00); 
    SetDynamicObjectMaterial(tmpobjid, 0, 16051, "oldwest", "snakefarmsign", 0x00000000);

    tmpobjid = CreateDynamicObject(3261, 979.569335, -2179.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.569335, -2179.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.569335, -2179.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.569335, -2179.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 967.569335, -2179.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.587402, -2179.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.587402, -2179.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.587402, -2179.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.587402, -2179.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 982.587402, -2179.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 968.331665, -2175.677490, 12.715935, -89.999992, 72.068916, 72.068878, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 970.331665, -2175.677490, 12.715935, -89.999992, 72.068916, 72.068878, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 972.331665, -2175.677490, 12.715935, -89.999992, 72.068916, 72.068878, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.569335, -2171.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.569335, -2171.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.569335, -2171.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.569335, -2171.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 967.569335, -2171.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.587402, -2171.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.587402, -2171.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.587402, -2171.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.587402, -2171.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 982.587402, -2171.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 977.142150, -2167.677490, 12.715935, -89.999992, 80.820144, 80.820106, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 979.142150, -2167.677490, 12.715935, -89.999992, 80.820144, 80.820106, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.569335, -2163.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.569335, -2163.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.569335, -2163.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.569335, -2163.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 967.569335, -2163.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.587402, -2163.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.587402, -2163.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.587402, -2163.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.587402, -2163.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 982.587402, -2163.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.569335, -2155.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.569335, -2155.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.569335, -2155.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.569335, -2155.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 967.569335, -2155.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.587402, -2155.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.587402, -2155.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.587402, -2155.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.587402, -2155.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 982.587402, -2155.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1478, 998.073913, -2166.368164, 12.579198, -3.000014, -5.000000, -104.999954, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 971.656372, -2151.605957, 12.715935, -89.999992, 77.917587, 92.917510, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 973.588256, -2151.088378, 12.715935, -89.999992, 77.917587, 92.917510, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.569335, -2147.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.569335, -2147.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.569335, -2147.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.569335, -2147.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 967.569335, -2147.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.587402, -2147.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.587402, -2147.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.587402, -2147.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.587402, -2147.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 982.587402, -2147.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 968.331665, -2143.677490, 12.715935, -89.999992, 72.068916, 72.068878, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 970.331665, -2143.677490, 12.715935, -89.999992, 72.068916, 72.068878, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 972.331665, -2143.677490, 12.715935, -89.999992, 72.068916, 72.068878, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.569335, -2139.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.569335, -2139.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.569335, -2139.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.569335, -2139.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 967.569335, -2139.190185, 12.593750, -0.000007, 0.000000, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 970.587402, -2139.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 973.587402, -2139.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 976.587402, -2139.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 979.587402, -2139.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3261, 982.587402, -2139.190185, 12.595748, 0.000022, 179.999969, 89.999923, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(14873, 993.047851, -2187.460937, 12.853746, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(14873, 987.477172, -2187.460937, 12.849745, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 986.773010, -2184.741943, 12.815937, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(12922, 994.648315, -2118.911132, 15.413750, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1454, 988.513000, -2184.741943, 12.815937, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(18609, 1000.681091, -2181.087646, 13.662402, -4.399998, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(337, 982.859375, -2181.177001, 12.720312, 0.000000, 170.000000, 100.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1217, 1001.030395, -2173.128906, 12.493746, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(933, 962.075073, -2170.666259, 12.013748, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1327, 995.948852, -2151.880126, 12.073748, -0.000007, 90.000015, -89.999946, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1327, 996.069458, -2151.830322, 12.703763, -0.000000, 90.000015, -67.499984, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(924, 1001.248535, -2131.864990, 12.273754, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1462, 1002.361389, -2141.884277, 12.093750, 0.000000, 0.000000, -180.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1338, 995.846679, -2153.951660, 12.773761, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(926, 998.054016, -2165.635253, 12.343754, -0.000000, 0.000029, -9.999998, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(928, 998.508911, -2164.676025, 12.363756, -0.000000, 0.000029, -9.999998, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(16317, 1003.893798, -2175.666748, 9.583747, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(16317, 991.623352, -2160.735839, 9.583747, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3425, 975.665283, -2128.645019, 23.064382, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(762, 993.455139, -2201.200683, 14.221550, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(16101, 1001.725036, -2124.177246, 4.753746, 0.000007, 0.000001, 69.999984, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(16101, 999.721679, -2129.677001, 4.753746, 0.000007, 0.000001, 69.999984, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(2725, 1002.738769, -2128.047363, 12.483757, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(2673, 1002.351074, -2126.611816, 12.183752, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(843, 970.953918, -2132.768798, 12.603757, 0.000000, 0.000000, 40.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(16317, 995.215881, -2130.452636, 9.583747, 0.000000, 0.000000, -30.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1728, 996.946166, -2145.900878, 12.093750, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(1453, 997.915100, -2145.143798, 12.613754, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(918, 998.865844, -2145.197021, 12.443757, 0.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00); 
    tmpobjid = CreateDynamicObject(3927, 960.999389, -2162.379394, 13.439355, 0.000000, 3.000000, 85.000000, -1, -1, -1, 120.00, 120.00); 
    return 1;
}