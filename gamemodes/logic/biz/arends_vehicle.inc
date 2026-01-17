#define MAX_ARENDS_POINT 21

new ArendsVehiclePickup[MAX_ARENDS_POINT];

new Float:ArendsVehicleCoords[MAX_ARENDS_POINT][4] = {
    {1449.3015,-1738.2214,13.5469,270.0},
    {1492.7488,-1586.5427,13.5469,90.0},
    {1769.4507,-1738.0508,13.5469,270.0},
    {2710.5588,-2399.3975,13.6328,90.0},
    {1211.5239,-1324.1768,13.5592, 0.0},
    {1042.7292,-1926.1542,13.1651,180.0},
    {-85.5495,79.3438,3.1172,60.4685},
    {1421.1068,-1644.6998,13.3714,270.0},
    {552.6696,-1289.0306,17.2482,0.0},
    {-2054.3489,-86.2508,35.3203,270.0},
    {-1983.1230,176.0852,27.6799,0.0},
    {-1899.5249,-1700.4644,21.7500,180.0},
    {-2260.0820,245.9765,35.3203,270.0},
    {-2638.8367,629.7920,14.4531,180.0},
    {-1989.8403,272.4617,35.1719,270.0},
    {2833.9548,1303.5906,10.7781,0.0},
    {2376.7632,2407.6814,10.8203,270.0},
    {1622.3491,1850.6174,10.8203,180.0},
    {2036.4670,1018.0894,10.8203,180.0},
    {2165.0247,1665.7498,10.8203,90.0},
    {2122.4382,1386.7543,10.8203,0.0}
};

new Float:ArendsVehicleActors[MAX_ARENDS_POINT][4] = {
    {1450.4329,-1741.1062,13.5469,0.0},
    {1492.5066,-1584.1981,13.5469,180.0},
    {1769.3979,-1740.4594,13.5469,0.0},
    {2710.4763,-2397.2532,13.6328,180.0},
    {1214.8385,-1323.8097,13.5668,90.0},
    {1040.2076,-1926.0723,13.1325,270.0},
    {-81.3953,77.2863,3.1172,64.4248},
    {1422.1061,-1641.3982,13.5469,270.0},
    {556.3373,-1290.7108,17.2482,0.0},
    {-2054.0522,-83.4507,35.3203,270.0},
    {-1979.6571,177.1433,27.6875,90.0},
    {-1895.5923,-1700.6986,21.7500,180.0},
    {-2259.6138,242.6985,35.3203,270.0},
    {-2635.9612,629.6531,14.4531,180.0},
    {-1989.2494,275.6457,35.1719,270.0},
    {2834.6243,1299.7843,10.7791,90.0},
    {2372.0557,2406.9360,10.8203,0.0},
    {1625.8845,1852.2435,10.8203,180.0},
    {2032.0530,1018.0901,10.8203,270.0},
    {2170.0693,1668.2007,10.8203,90.0},
    {2118.8472,1386.4711,10.8125,0.0}
};

new Float:ArendsVehiclePickupPos[MAX_ARENDS_POINT][3] = {
    {1450.3926,-1740.3357,13.5469},
    {1492.5159,-1584.9670,13.5469},
    {1769.3801,-1739.6899,13.5469},
    {2710.5237,-2398.0222,13.6328},
    {1214.0641,-1323.8000,13.5668},
    {1040.9778,-1926.0620,13.1421},
    {-82.1240,77.5445,3.1096},
    {1422.8768,-1641.4307,13.5469},
    {556.3027,-1289.9424,17.2482},
    {-2053.2854,-83.4237,35.3203},
    {-1980.4293,177.0927,27.6875},
    {-1895.6208,-1701.4701,21.7500},
    {-2258.8430,242.7432,35.3203},
    {-2635.9590,628.8842,14.4531},
    {-1988.4797,275.6391,35.1719},
    {2833.8555,1299.7998,10.7779},
    {2372.0503,2407.7046,10.8203},
    {1625.8629,1851.4752,10.8203},
    {2032.8256,1018.0967,10.8203},
    {2169.2981,1668.2407,10.8203},
    {2118.8777,1387.3669,10.8125}
};

new ArendsVehicleIDs[21],
    ArendsVehicleMaxCount[3][21], // ћаксимальное количество модели т/с
    ArendsVehicleUseCount[3][21]; //  оличество используемых моделей т/с

GetVehicleArendsVehicleIDs(class)
{
    ArendsVehicleIDs[0] = 462;
    for(new j = 2; j != -1; j--) 
    {
        ArendsVehicleUseCount[j][0] = 0;
        ArendsVehicleMaxCount[j][0] = 10;
    }

    new type_count_class,
        count = (5*class)+1,
        RandomIDs[4] = {4, 3, 1, 1},
        UseCount[4] = {5, 3, 2, 1};
    for(new i = 0; i < 212; i++)
    {
        if(GetVehicleData(i, E_VD_CLASS) != class)
            continue;
        if(GetVehicleData(i, E_VD_TYPE) != VEHICLE_STATE_CAR && GetVehicleData(i, E_VD_TYPE) != VEHICLE_STATE_MOTO)
            continue;
        if(GetVehicleData(i, E_VD_PRICE) > 5000000)
            continue;
        if(random(RandomIDs[class]) != 0) 
            continue;
        ArendsVehicleIDs[count] = GetVehicleData(i, E_VD_ID);

        for(new j = 2; j != -1; j--) 
        {
            ArendsVehicleUseCount[j][count] = 0;
            ArendsVehicleMaxCount[j][count] = UseCount[class];
        }
        count++;
        type_count_class++;
        if(type_count_class == 5) 
            break;
    }
}

LoadArendsVehicle()
{
    new ActorSkinsID[] = {23, 24, 25, 30, 46, 60, 72};
    for(new i = MAX_ARENDS_POINT-1; i != -1; i--)
    {
        CreateActor(ActorSkinsID[random(sizeof(ActorSkinsID)-1)], ArendsVehicleActors[i][0], ArendsVehicleActors[i][1], ArendsVehicleActors[i][2], ArendsVehicleActors[i][3]);

        ArendsVehiclePickup[i] = CreateDynamicPickup(19133, 23, ArendsVehiclePickupPos[i][0], ArendsVehiclePickupPos[i][1], ArendsVehiclePickupPos[i][2]);
        UpdatePickupInfo(ArendsVehiclePickup[i], TYPE_ARENDS_VEHICLE, PICKUP_SUBTYPE_INVALID_ID, i);
    }
    return 1;
}

GetArendsVehicleID(modelid)
{
    for(new i = 20; i != -1; i--)
    {
        if(ArendsVehicleIDs[i] == modelid)
            return i;
    }
    return -1;
}