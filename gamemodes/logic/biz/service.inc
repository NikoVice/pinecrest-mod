enum  e_ServiceTune_Colors
{
    st_Name[48],
    st_ID,
    Float:st_TD_X,
    Float:st_TD_Y,
    st_Color
};

new ServiceTune_Colors[12][e_ServiceTune_Colors] =
{
    {"flin_sto:flin_sto_whitecolor",        1,      13.7993, 206.7689,       0xFFFFFFFF}, // белый
    {"flin_sto:flin_sto_blackcolor",        0,      53.3992, 206.7689,       0x333333FF}, // черный
    {"flin_sto:flin_sto_graycolor",         9,      92.5994, 206.7689,       0x909090FF}, // серый
    {"flin_sto:flin_sto_redcolor",          3,      132.5993, 206.7689,      0xff0000FF}, //красный
    {"flin_sto:flin_sto_orangecolor",       123,    13.3992, 254.0578,       0xffa500FF}, // оранжевый
    {"flin_sto:flin_sto_yellowcolor",       6,      53.3992, 254.0578,       0xffff00FF}, // жолтый
    {"flin_sto:flin_sto_greencolor",        86,     93.3992, 254.0578,       0x008000FF}, // зеленый
    {"flin_sto:flin_sto_berezeviycolor",    16,     132.5993, 254.0578,      0x40e0d0FF}, // березовый
    {"flin_sto:flin_sto_bluecolor",         2,      13.7994, 301.3467,       0x00b8ffFF}, // гулобой
    {"flin_sto:flin_sto_sbluecolor",        108,    53.7994, 300.8489,       0x0000FFFF}, // синий
    {"flin_sto:flin_sto_purplecolor",       5,      92.5995, 301.3467,       0x800080FF}, // фиолетовый
    {"flin_sto:flin_sto_pinkcolor",         126,    132.5995, 300.8489,      0xFFA7B6FF} // розовый
};

#define PRICE_TUNE_WHEEL_SIZE       100000
#define PRICE_TUNE_WHEEL_WIDTH      100000
#define PRICE_TUNE_WHEEL_OFFSET_X   100000
#define PRICE_TUNE_WHEEL_ANGLE      100000
#define PRICE_TUNE_COLOR_LIGHTS     100000
#define PRICE_TUNE_TONING           100000

BuyPlayerService(playerid, price)
{
    new bizid = p_temp[playerid][service_idx], newprice = floatround(price * 0.15), biz_money = (newprice / 100) * 90, mafia_money = (newprice / 100) * 10;

    if(b_info[bizid][_prod] >= biz_money / 100)
    {
        b_info[bizid][_prod] -= biz_money / 100;
        b_info[bizid][_bank] += biz_money - mafia_money;
        AddMafiaBank(bizid, mafia_money);

        biz_finka[bizid] += biz_money - mafia_money;
        UpdateIntForFinanceBiz(bizid, biz_money - mafia_money);
    }

    OnServerInfoForMoney[10] += price;
    SetPlayerMoney(playerid, -price, true, "услуги автомастерской");
    CheckPlayerMission(playerid, START_SERVICE);
    UpdateFamilyLevel(playerid);
    return 1;
}

SaveVehicleVisual(vehicleid)
{
    if(vehicleid == INVALID_VEHICLE_ID) return 1;
    if(veh_info[vehicleid][v_mysql_id] == 0) return 1;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `vehicle` SET `v_wheel_width` = %d, `v_wheel_size` = '%f', \
        `v_wheel_offset_x_0` = %d, `v_wheel_offset_x_1` = %d, `v_wheel_alignment_0` = %d, `v_wheel_alignment_1` = %d, \
        `v_lights_color_0` = %d, `v_lights_color_1` = %d, `v_lights_color_2` = %d, `v_toner` = %d WHERE `v_mysql_id` = %d",
    veh_info[vehicleid][v_wheel_width], veh_info[vehicleid][v_wheel_size], veh_info[vehicleid][v_wheel_offset_x][0], veh_info[vehicleid][v_wheel_offset_x][1],
    veh_info[vehicleid][v_wheel_alignment][0], veh_info[vehicleid][v_wheel_alignment][1], veh_info[vehicleid][v_lights_color][0], veh_info[vehicleid][v_lights_color][1],
    veh_info[vehicleid][v_lights_color][2], veh_info[vehicleid][v_toner], veh_info[vehicleid][v_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

Service_TuningClear(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(vehicleid == INVALID_VEHICLE_ID) return 1;

    p_temp[playerid][shop_id] = 0;
    p_temp[playerid][p_listitem][0] =
    p_temp[playerid][p_listitem][1] =
    p_temp[playerid][p_listitem][2] =
    p_temp[playerid][p_listitem][3] =
    p_temp[playerid][p_listitem][4] =
    p_temp[playerid][p_listitem][5] = -1;
    p_temp[playerid][tune_default] = false;

    switch(p_temp[playerid][InterfaceID])
    {
        case SERVICE_TUNE_EXTERNAL_VIEW:
        {
            for(new i; i < 13; i++) RemoveVehicleComponent(vehicleid, GetVehicleComponentInSlot(vehicleid, i));
            RemoveVehicleComponent(vehicleid, GetVehicleComponentInSlot(vehicleid, CARMODTYPE_WHEELS));
            ChangeVehiclePaintjob(vehicleid, 3);

            for (new i; i < v_all-1; i++) if(veh_info[vehicleid][v_tune][i] != 0 ) VEx_AddVehicleComponent (vehicleid, veh_info[vehicleid][v_tune][i]);
            if(veh_info[vehicleid][v_tune][v_paintjob] != 0) ChangeVehiclePaintjob(vehicleid, veh_info[vehicleid][v_tune][v_paintjob]-1);
        }
        case SERVICE_TUNE_ACCESSORIES_VIEW:
        {
            Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
        }
        case SERVICE_TUNE_WHEEL_SIZE:
        {
            ResetHandlingAttributes(vehicleid);
            if(veh_info[vehicleid][v_wheel_size] != 0.0)
                SetVehicleWheelSize(vehicleid, veh_info[vehicleid][v_wheel_size]);
        }
        case SERVICE_TUNE_WHEEL_WIDTH, SERVICE_TUNE_WHEEL_OFFSET_X, SERVICE_TUNE_WHEEL_ANGLE, SERVICE_TUNE_COLOR_LIGHTS:
        {
            ResetVehicleVisuals(vehicleid);
            if(veh_info[vehicleid][v_wheel_width] != 0)
                SetVehicleWheelWidth(vehicleid, veh_info[vehicleid][v_wheel_width]);

            if(veh_info[vehicleid][v_wheel_offset_x][0] != 0)
                SetVehicleWheelOffsetX(vehicleid, 0, veh_info[vehicleid][v_wheel_offset_x][0]);

            if(veh_info[vehicleid][v_wheel_offset_x][1] != 0)
                SetVehicleWheelOffsetX(vehicleid, 1, veh_info[vehicleid][v_wheel_offset_x][1]);

            if(veh_info[vehicleid][v_wheel_alignment][0] != 0)
                SetVehicleWheelAngle(vehicleid, 0, veh_info[vehicleid][v_wheel_alignment][0]);

            if(veh_info[vehicleid][v_wheel_alignment][1] != 0)
                SetVehicleWheelAngle(vehicleid, 1, veh_info[vehicleid][v_wheel_alignment][1]);

            if(g_VehVisualsInfo[vehicleid][vcLightsColor][0] != 0 &&
                    g_VehVisualsInfo[vehicleid][vcLightsColor][1] != 0 &&
                    g_VehVisualsInfo[vehicleid][vcLightsColor][2] != 0)
                SetVehicleLightsColors(vehicleid, veh_info[vehicleid][v_lights_color][0], veh_info[vehicleid][v_lights_color][1], veh_info[vehicleid][v_lights_color][2]);
        }
        case SERVICE_TUNE_COLOR_SELECT:
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            ChangeVehicleColor(vehicleid, veh_info[vehicleid][v_color][0], veh_info[vehicleid][v_color][1]);
        }
    }
    return 1;
}

Service_Exit(playerid)//, error_text[], szErrorText = sizeof(error_text))
{
    new bizid = p_temp[playerid][service_idx];
    p_temp[playerid][service_idx] = -1;

    Service_TuningClear(playerid);

    if(p_temp[playerid][TextDrawServiceTune]) HideTextDrawForPlayer(playerid, TD_ID_SERVICE_TUNE);
    if(p_temp[playerid][TextDrawShopUse]) HideTextDrawForPlayer(playerid, TD_ID_SHOP);

    switch(bizid)
    {
        case 103: bizid = 0;
        case 104: bizid = 1;
        default: bizid = 0;
    }

    new Float:Service_ExitPos[][] =
    {
        {-2092.8777,94.9183,35.0292,89.9304}, // SF #1
        {-1786.8678,1205.2743,24.8339,179.9738} // SF #2
    };
    if(GetPlayerVehicleID(playerid) != 0) TeleportVehicleToPos(GetPlayerVehicleID(playerid), Service_ExitPos[bizid][0], Service_ExitPos[bizid][1], Service_ExitPos[bizid][2]+0.2, Service_ExitPos[bizid][3], 0, 0, true);
    else
    {
        SetPlayerPos(playerid, Service_ExitPos[bizid][0], Service_ExitPos[bizid][1], Service_ExitPos[bizid][2]+0.2);
        SetPlayerFacingAngle(playerid, Service_ExitPos[bizid][3]);
        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);
    }
    SetCameraBehindPlayer(playerid);
    return 1;
}

Service_Enter(playerid)
{
    if(GetPlayerVirtualWorld(playerid) == playerid+1000 && GetPlayerInterior(playerid) == 0) 
        return 1;
    if(!IsPlayerInAnyVehicle(playerid)) 
        return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(SRV_ID)
    {
        if(!IsPlayerOwnerVehicle(playerid, vehicleid) && veh_info[vehicleid][v_family_id] == -1) 
            return SendError(playerid, "Вы должны находиться в своем личном или семейном транспортном средстве.");
        if(veh_info[vehicleid][v_family_id] != -1 && GetPlayerFamilyID(playerid) != -1 && GetFamilyRang(playerid) < FamilyData[GetPlayerFamilyID(playerid)][fSettingRang][F_VEHICLE])
            return SendError(playerid, "У Вас слишком маленький ранг в семье для услуг СТО.");
        if(veh_info[vehicleid][v_bonus] != 0) 
            return SendError(playerid, "Вы не можете тюнинговать бонусное транспортное средство.");
        if(veh_info[vehicleid][v_insurance] == 0 && veh_info[vehicleid][v_family_id] == -1 && (GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_VELO_MOPED || GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_MOTO || GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_CAR))
            return SendError(playerid, "На транспортном средстве должна быть страховка.");
        if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) != VEHICLE_STATE_CAR && GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) != VEHICLE_STATE_MOTO)
            return SendError(playerid, "Пользоваться услугами автомастерской можно только на автомобилях и мотоциклах.");
    }
    if(GetVehicleModelEx(vehicleid) > 611 && !p_info[playerid][p_settings][INTERFACE])
        return SendError(playerid, "Тюнинг на Real Cars доступен только с включенной графикой.");
    if(IsTDVisible(playerid) != -1) 
        return 1;

    new Float:vehpos_X, Float:vehpos_Y, Float:vehpos_Z;
    GetVehiclePos(vehicleid, vehpos_X, vehpos_Y, vehpos_Z);

    for(new i = 0, targetid; i < 8; i++)
    {
        targetid = veh_info[vehicleid][v_passenger][i];
        if(targetid != INVALID_PLAYER_ID && targetid != playerid)
        {
            SetPlayerPos(targetid, vehpos_X, vehpos_Y, vehpos_Z+1);
            veh_info[vehicleid][v_passenger][i] = INVALID_PLAYER_ID;
        }
    }
    new showtime = GetPlayerPing(playerid) < 80 ? 500 : 1000;
    GameTextForPlayer(playerid, "~g~LOADING...", showtime, 3);
    TeleportVehicleToPos(vehicleid, 1096.998, 1523.042, 5.547+0.2, 290.0, 0, playerid+1000, false);
    SetPlayerVirtualWorld(playerid, playerid+1000);
    SetPlayerInterior(playerid, 0);
    SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
    SetTimerEx("Fix_ServiceEnter", showtime, false, "ii", playerid, vehicleid);
    return 1;
}

forward Fix_ServiceEnter(playerid, vehicleid);
public Fix_ServiceEnter(playerid, vehicleid)
{
    if(!p_info[playerid][p_settings][INTERFACE])
    {
        ShowDialogTuneMain(playerid);
        SendMes(playerid, COLOR_DARKORANGE, "У Вас не включены интерфейсы, без них отображаются не все возможности тюнинг-центра.");
    }
    else
    {
        ShowTextDrawForPlayer(playerid, TD_ID_SERVICE_TUNE);
        SendMes(playerid, COLOR_DARKORANGE, "При возникновении проблем с интерфейсами, отключите их в настройках.");
    }
    SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
}

Service_Error(playerid, error_text[])
{
    Service_Exit(playerid);
    SendError(playerid, error_text);
    return 1;
}

Service_GetTill(playerid)
{
    new bizid = p_temp[playerid][service_idx];
    return b_info[bizid][_till];
}

CMD:tuning(playerid, params[])
{
    if(IsPlayerInRangeOfPoint(playerid, 10.0, -2091.6614,95.0424,35.0294)) p_temp[playerid][service_idx] = 103;
    else if(IsPlayerInRangeOfPoint(playerid, 10.0, -1786.7810,1206.5242,24.8338)) p_temp[playerid][service_idx] = 104;
    else p_temp[playerid][service_idx] = -1;
    if(p_temp[playerid][service_idx] != -1)
    {
        Service_Enter(playerid);
        return 1;
    } else SendError(playerid, "Вы слишком далеко от тюнинг центра.");
    return 1;
}