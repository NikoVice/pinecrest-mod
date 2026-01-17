/*
    Author: Vip Uzer
    Flin RolePlay
    (c) 2021
*/


/*
    Definitions
*/

forward AirBalloon_CreteCountDown(playerid, itemID);
public AirBalloon_CreteCountDown(playerid, itemID)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "AIR BALLOON SPAWN IN %d SECONDS", p_temp[playerid][airballoon_install_timer]);
    GameTextForPlayer(playerid, STRING_GLOBAL, 900, 3);
    p_temp[playerid][airballoon_install_timer]--;

    if(p_temp[playerid][airballoon_install_timer] <= 0)
    {
        KillTimer(GetPVarInt(playerid, !"create_air_balloon_timer_id"));
        DeletePVar(playerid, !"create_air_balloon_timer_id");

        GivePlayerInventory(playerid, 650, -2);
        GivePlayerInventory(playerid, 649, -2);

        RemovePlayerAccessories(playerid, false);

        new Float:x, Float:y, Float:z, Float:ang;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, ang);

        p_temp[playerid][airballoon_vehicleID] = CreateVehicleVEx(NPO_NONE, NPO_NONE, 487, x, y, z, ang, -1, -1, -1);
        LinkVehicleToInterior(p_temp[playerid][airballoon_vehicleID], 100);

        veh_info[p_temp[playerid][airballoon_vehicleID]][v_int] = 100;
        veh_info[p_temp[playerid][airballoon_vehicleID]][v_fuel] = 999.0;

        p_temp[playerid][airballoon_objectID] = CreateDynamicObject(ItemsInfo[itemID][iModel], x, y, z-1.0, 0.0, 0.0, 0.0);
        p_temp[playerid][airballoon_labelID] = CreateDynamic3DTextLabel(""I"[ Воздушный Шар ]\n\n"W"Чтобы занять пассажирское место нажмите \"G\"\n"W"Управление доступно только для владельца", -1, 0.0, 0.0, 0.0, 25.0, INVALID_PLAYER_ID, p_temp[playerid][airballoon_vehicleID], 0, 0, 0, -1);

        AttachDynamicObjectToVehicle(p_temp[playerid][airballoon_objectID], p_temp[playerid][airballoon_vehicleID], 0.0, -0.0, -1.0, 0.0, 0.0, -0.0);

        //p_temp[playerid][airballoon_area] = CreateDynamicSphere(x, y, z, 15.0);
        //UpdateAreaInfo(p_temp[playerid][airballoon_area], TYPE_AIRBALLOON_PLAYER, AREA_SUBTYPE_INVALID_ID, playerid);
        //AttachDynamicAreaToVehicle(p_temp[playerid][airballoon_area], p_temp[playerid][airballoon_vehicleID]);

        PutPlayerInVehicle(playerid, p_temp[playerid][airballoon_vehicleID], 0);

        SetVehicleParamsVEx(p_temp[playerid][airballoon_vehicleID], true, false, alarm, false, bonnet, boot, objective);
    }
    return 1;
}

DeletePlayerAirBalloon(playerid)
{
    if(p_temp[playerid][airballoon_objectID] != INVALID_OBJECT_ID)
        DestroyDynamicObject(p_temp[playerid][airballoon_objectID]);
    if(p_temp[playerid][airballoon_areaID] != -1)
        DestroyDynamicArea(p_temp[playerid][airballoon_areaID]);
    if(p_temp[playerid][airballoon_labelID] != INVALID_3DTEXT_ID)
        DestroyDynamic3DTextLabel(p_temp[playerid][airballoon_labelID]);
    if(p_temp[playerid][airballoon_vehicleID] != INVALID_VEHICLE_ID)
        DestroyVehicleVEx(p_temp[playerid][airballoon_vehicleID]);
    new timerID = GetPVarInt(playerid, !"create_air_balloon_timer_id");
    if(timerID != INVALID_TIMER_ID && IsValidTimer(timerID))
        KillTimer(timerID);
    ClearInfoPlayerAirBalloon(playerid);
    return 1;
}

ClearInfoPlayerAirBalloon(playerid)
{
    p_temp[playerid][airballoon_objectID] = INVALID_OBJECT_ID;
    p_temp[playerid][airballoon_install_timer] = -1;
    p_temp[playerid][airballoon_vehicleID] = INVALID_VEHICLE_ID;
    p_temp[playerid][airballoon_areaID] = -1;
    p_temp[playerid][airballoon_labelID] = INVALID_3DTEXT_ID;
    DeletePVar(playerid, !"create_air_balloon_timer_id");
    return 1;
}

CMD:airballoon(playerid, params[])
{
    ShowPlayerDialog(playerid, D_AIR_BALLOON_MENU, DIALOG_STYLE_LIST, ""I"Воздушный шар",
        ""I"[1]"W" Установить шар\n\
        "I"[2]"W" Убрать шар\n\
        "I"[3]"W" Информация", "Выбрать", "Отмена");
    return 1;
}
alias:airballoon("airb", "airbalon", "airballon");

CMD:createairballoon(playerid, params[])
{
    new player_balloon_object_id = p_temp[playerid][airballoon_objectID];
    if(player_balloon_object_id != INVALID_OBJECT_ID)
        return SendError(playerid, "Вы уже создали воздушный шар.");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendError(playerid, "Доступно только с ног.");

    if(AntiDMZone(playerid))
        return SendError(playerid, "Вы не можете использовать в \"Зеленой зоне\".");
    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        return SendError(playerid, "Вы не можете использовать в помещении.");

    CreatePlayerAirBalloon(playerid);
    return 1;
}

CMD:destroyairballoon(playerid, params[])
{
    if(p_temp[playerid][airballoon_objectID] == INVALID_OBJECT_ID)
        return SendError(playerid, "Вы ещё не запустили воздушный шар.");

    DeletePlayerAirBalloon(playerid);
    SendError(playerid, "Вы завершили полёт.");
    return 1;
}

CreatePlayerAirBalloon(playerid)
{
    new player_balloon_object_id = p_temp[playerid][airballoon_objectID];
    if(player_balloon_object_id != INVALID_OBJECT_ID)
        return SendError(playerid, "Вы уже создали воздушный шар.");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendError(playerid, "Доступно только с ног.");
    new airballon_ID = -1;
    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
            InventoryPlayer[playerid][i][inv_status_use] != 0 &&
            (541 <= InventoryPlayer[playerid][i][inv_item_id] <= 547))
        {
            airballon_ID = InventoryPlayer[playerid][i][inv_item_id];
            break;
        }
    }
    if(airballon_ID == -1)
        return SendError(playerid, "У Вас нет аксессуара воздушного шара или он не одет.");

    if(GetInventoryAmount(playerid, 650) < 2)
        return SendError(playerid, "У Вас нет древесины.");
    if(GetInventoryAmount(playerid, 649) < 2)
        return SendError(playerid, "У Вас нет метала.");
    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        return SendError(playerid, "Установить шар можно только на улице.");

    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 1, 1, 0, 0);

    if(p_temp[playerid][airballoon_objectID] != INVALID_OBJECT_ID)
        return 1;
    if(p_temp[playerid][airballoon_install_timer] != -1)
        return 1;

    p_temp[playerid][airballoon_install_timer] = 5;
    new timerId = SetTimerEx("AirBalloon_CreteCountDown", 1000, true, "ii", playerid, airballon_ID);
    SetPVarInt(playerid, !"create_air_balloon_timer_id", timerId);
    return 1;
}

/*
CMD:supreme(playerid, params[])
{
    if(p_info[playerid][admin] < 10) return 1;
    SupremeInstall(GetPlayerVehicleID(playerid));
    return 1;
}

stock SupremeInstall(vehicleid)
{
	new supreme;
    supreme = CreateDynamicObject(1547,0.0,0.0,-1000.0,0.0,0.0,0.0,-1,-1,-1,300.0,300.0);
    SetDynamicObjectMaterial(supreme, 0, 3031, "wngdishx", "metal_leg", 0);
    SetDynamicObjectMaterial(supreme, 1, 4552, "ammu_lan2", "newall4-4", 0);
    SetDynamicObjectMaterialText(supreme, 0, "SUPREME", 40, "Ariel", 24, 1, -1, 16711680, 1);

	switch(GetVehicleModel(vehicleid))
	{
		case 451:
		{
			AttachDynamicObjectToVehicle(supreme, vehicleid, -0.026, -1.473, 0.422, 19.399, 0.600, 0.599);
		}
		case 402:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.778, 0.429, 22.900, 0.000, 0.000);
		}
		case 477:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, 0.009, -2.372, 0.331, 2.299, 0.000, 0.000);
		}
		case 411:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.009, -1.015, 0.548, 24.400, 0.000, 0.000);
		}
		case 541:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.010, -1.266, 0.471, 12.999, 0.000, 0.000);
		}
		case 445:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.691, 0.547, 37.299, 0.000, 0.000);
		}
		case 419:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, 0.000, -1.990, 0.231, 3.699, 0.000, 0.000);
		}
		case 495:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.480, -2.249, -0.097, 88.799, 0.000, 0.000);
		}
		case 506:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.607, 0.376, 16.799, 0.000, 0.000);
		}
		case 415:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.901, 0.290, 5.099, 0.000, 0.000);
		}
		case 559:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.010, -1.851, 0.464, 15.600, 0.000, 0.000);
		}
		case 560:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.180, 0.662, 29.200, 0.000, 0.000);
		}
		case 434:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.973, -0.056, 69.400, 0.000, 0.000);
		}
		case 421:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.667, 0.463, 35.700, 0.000, 0.000);
		}
		case 533:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, 0.000, -2.411, 0.260, 0.000, 0.000, 0.000);
		}
		case 400:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.030, -2.220, 0.416, 65.099, 0.000, 0.000);
		}
		case 429:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.030, -1.531, 0.320, 0.000, 0.000, 0.000);
		}
		case 503:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -2.332, 0.274, 7.399, 0.000, 0.000);
		}
		case 562:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.193, 0.621, 31.400, 0.000, 0.000);
		}
		case 502:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, -0.020, -1.778, 0.382, 31.199, 0.000, 0.000);
		}
		case 579:
		{
	    	AttachDynamicObjectToVehicle(supreme, vehicleid, -0.010, -2.838, 0.361, 75.099, 0.000, 0.800);
		}
		case 409:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, 0.000, -2.691, 0.527, 49.099, 0.000, 0.000);
		}
		case 494:
		{
		    AttachDynamicObjectToVehicle(supreme, vehicleid, 0.979, -2.497, -0.088, 81.899, -4.599, 90.800);
		}
		default:
		{
			DestroyDynamicObject(supreme);
		}
	}
	return true;
}
*/
