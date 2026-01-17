/*
    Auto Market
	Author: Vip_Uzer
    Flin RolePlay 2021
*/
new VEHICLE_MARKET_CUBE,
    pickup_market_vehicle;

new area_market_vehicle_new[2];
new area_market_vehicle_pickup;

enum e_auc_veh
{
    Float:a_vX,
    Float:a_vY,
    Float:a_vZ,
    Float:a_vR,
    a_vTransportID,
    a_vPrice,
    a_vArea,
    Text3D:a_vText,
    a_vObject,
}
#define MAX_VEHICLE_MARKET_SLOTS 22

new VehicleMarket[MAX_VEHICLE_MARKET_SLOTS][e_auc_veh] =
{
    {302.00, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {295.75, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {289.50, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {283.25, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {277.00, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {270.75, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {264.50, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {258.25, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {252.00, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {245.75, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {239.50, -1792.50, 5.09, 180.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},

    {302.00, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {295.75, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {289.50, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {283.25, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {277.00, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {270.75, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {264.50, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {258.25, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {252.00, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {245.75, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID},
    {239.50, -1805.95, 5.0900, 0.0000, INVALID_VEHICLE_ID, 0, -1, INVALID_3DTEXT_ID, INVALID_OBJECT_ID}
};

VehicleMarket_OnGameModeInit()
{
    CreateDynamicPickup(1318, 23, 1087.2070,-1375.6184,13.5087, 0, 0, -1);
    CreateDynamic3DTextLabel("Авторынок\nНажмите "W"ALT"I" для входа или въезда", COLOR_MAIN, 1087.2070,-1375.6184,13.5087, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    area_market_vehicle_new[0] = CreateDynamicSphere(1087.2070,-1375.6184,13.5087, 5.0, 0, 0, -1);
    area_market_vehicle_new[1] = CreateDynamicSphere(1387.1472,-2080.4038,2004.2123, 5.0);

    area_market_vehicle_pickup = CreateDynamicPickup(1318, 23, 1383.1820,-2082.6594,2004.5033, -1, -1, -1);
    /*
    VehicleMarket[21][a_vObject] = CreateDynamicObject(2662, 239.591888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[20][a_vObject] = CreateDynamicObject(2662, 245.841888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[19][a_vObject] = CreateDynamicObject(2662, 252.091888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[18][a_vObject] = CreateDynamicObject(2662, 258.341888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[17][a_vObject] = CreateDynamicObject(2662, 264.591888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[16][a_vObject] = CreateDynamicObject(2662, 270.841888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[15][a_vObject] = CreateDynamicObject(2662, 277.091888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[14][a_vObject] = CreateDynamicObject(2662, 283.341888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[13][a_vObject] = CreateDynamicObject(2662, 289.591888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[12][a_vObject] = CreateDynamicObject(2662, 295.841888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[11][a_vObject] = CreateDynamicObject(2662, 302.091888, -1802.389770, 4.859294, -9.999999, -0.000023, 179.999710, -1, -1, -1, 120.00, 120.00);

    VehicleMarket[0][a_vObject] = CreateDynamicObject(2662, 302.051849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[1][a_vObject] = CreateDynamicObject(2662, 295.801849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[2][a_vObject] = CreateDynamicObject(2662, 289.551849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[3][a_vObject] = CreateDynamicObject(2662, 283.301849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[4][a_vObject] = CreateDynamicObject(2662, 277.051849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[5][a_vObject] = CreateDynamicObject(2662, 270.801849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[6][a_vObject] = CreateDynamicObject(2662, 264.551849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[7][a_vObject] = CreateDynamicObject(2662, 258.301849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[8][a_vObject] = CreateDynamicObject(2662, 252.051849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[9][a_vObject] = CreateDynamicObject(2662, 245.801849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);
    VehicleMarket[10][a_vObject] = CreateDynamicObject(2662, 239.551849, -1795.984985, 4.859294, -9.999999, 0.000029, 0.000004, -1, -1, -1, 120.00, 120.00);

    for(new i; i < MAX_VEHICLE_MARKET_SLOTS; i++)
    {
        VehicleMarket[i][a_vArea] = CreateDynamicSphere(VehicleMarket[i][a_vX], VehicleMarket[i][a_vY], VehicleMarket[i][a_vZ], 3.15, 0, 0, -1);
        UpdateAreaInfo(VehicleMarket[i][a_vArea], TYPE_MARKET_VEHICLE, AREA_SUBTYPE_INVALID_ID, i);
        VehicleMarket[i][a_vTransportID] = INVALID_VEHICLE_ID;
        VehicleMarket[i][a_vText] = CreateDynamic3DTextLabel("Авторынок\n"W"Место под аренду свободно", COLOR_MAIN, VehicleMarket[i][a_vX], VehicleMarket[i][a_vY], VehicleMarket[i][a_vZ]+1.5, 4.5,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL, 0, 0, -1);
        SetDynamicObjectMaterialText(VehicleMarket[i][a_vObject], 0, "Авторынок\nМесто под\nаренду свободно", 130, "Verdana", 50, 1, 0xFF000000, 0x00000000, 1);
    }

    VEHICLE_MARKET_CUBE = CreateDynamicCuboid(233.9352,-1810.9824, 4.0, 307.9921,-1788.2775, 8.6, -1, -1, -1); // Авторынок;

    pickup_market_vehicle = CreateDynamicPickup(1239, 23, 237.3232,-1799.1952,4.9789, 0, 0, -1);
    CreateDynamic3DTextLabel("<< Авторынок >>", COLOR_MAIN, 237.3232,-1799.1952,4.9789+0.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(294, 235.2546,-1799.1952,4.9789, 270.0);
    CreateDynamic3DTextLabel("NPC: "I"Владелец авторынка", COLOR_WHITE, 235.2546,-1799.1952,4.9789 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    */
    return 1;
}

VehicleMarket_BetShowDialog(playerid, vehicleid)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""W"Вы собираетесь выставить транспорт %s на авторынок?\nЦена аренды: "I"%d$ (0.5# гос. стоимости)\n\
    "W"Введите цену от половины гос. стоимости до полной*2 (ГОС: %d)\nПример: "I"500000 - цена.", GetVehicleName(vehicleid), GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_PRICE)/200, GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_PRICE));
    ShowPlayerDialog(playerid, D_VEHICLE_MARKET_BET, DIALOG_STYLE_INPUT, ""I"Выставить на авторынок", STRING_GLOBAL, "Ввести", "Отмена");
    return 1;
}

VehicleMarket_UnBet(playerid, vehicleid)
{
    if(vehicleid == INVALID_VEHICLE_ID) return 1;
    if(!IsPlayerInDynamicArea(playerid, VEHICLE_MARKET_CUBE)) return 1;
    if(veh_info[vehicleid][v_mysql_id] == 0)
        return SendError(playerid, "Произошла не известная ошибка, сообщите на форум в тех. раздел.");
    new pos_id = -1;
    for(new i = MAX_VEHICLE_MARKET_SLOTS-1; i != -1; i--)
    {
        if(VehicleMarket[i][a_vTransportID] == vehicleid)
        {
            pos_id = i;
            break;
        }
    }
    if(pos_id == -1) return 1;

    SetVehiclePos(vehicleid, veh_info[vehicleid][v_pos][0], veh_info[vehicleid][v_pos][1], veh_info[vehicleid][v_pos][2]);
    SetVehicleZAngle(vehicleid, veh_info[vehicleid][v_pos][3]);
    VehicleMarket_Clear(pos_id);

    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2)[$12345] забрал <Infernus>(411)[1550] с авторынка
    Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] забрал <%s>(%d)[%d] с авторынка",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
        GetVehicleName(vehicleid), GetVehicleModelEx(vehicleid), veh_info[vehicleid][v_mysql_id]);
    return 1;
}

GetSlotVehicleMarket(vehicle_mysql_id)
{
    if(vehicle_mysql_id == INVALID_MYSQL_ID) return -1;
    for(new i = MAX_VEHICLE_MARKET_SLOTS-1; i != -1; i--)
    {
        if(VehicleMarket[i][a_vTransportID] != INVALID_VEHICLE_ID &&
            veh_info[VehicleMarket[i][a_vTransportID]][v_mysql_id] == vehicle_mysql_id)
            return i;
    }
    return -1;
}

VehicleMarket_Clear(id)
{
    VehicleMarket[id][a_vTransportID] = INVALID_VEHICLE_ID;
    VehicleMarket[id][a_vPrice] = 0;
    UpdateDynamic3DTextLabelText(VehicleMarket[id][a_vText], COLOR_MAIN, "Авторынок\n"W"Место под аренду свободно");
    SetDynamicObjectMaterialText(VehicleMarket[id][a_vObject], 0, "Авторынок\nМесто под\nаренду свободно", 130, "Verdana", 50, 1, 0xFF000000, 0x00000000, 1);
}
/*
VehicleMarket_PlayerLeave(playerid)
{
    new bool:isMessage, vehicleid;
    for(new i = MAX_VEHICLE_MARKET_SLOTS-1; i != -1; i--)
    {
        vehicleid = VehicleMarket[i][a_vTransportID];
        if(IsPlayerOwnerVehicle(playerid, vehicleid))
        {
            SetVehiclePos(vehicleid, veh_info[vehicleid][v_pos][0], veh_info[vehicleid][v_pos][1], veh_info[vehicleid][v_pos][2]);
            SetVehicleZAngle(vehicleid, veh_info[vehicleid][v_pos][3]);
            VehicleMarket_Clear(i);
            isMessage = true;
        }
        if(isMessage)
            SendInfo(playerid, "Вы покинули территорию АвтоРынка, аренда отменена.");
    }
}
*/
