forward load_car_shop();
public load_car_shop()
{
    new rows, time = GetTickCount(), vehicleid, vehicle_model, temp_idx, count;
    cache_get_row_count(rows);
    if(rows)
    {
        for(new i = 0; i < rows; i++)
        {
            cache_get_value_name_int(i, "vehicle_model", CarShopInfo[i][csVehicleModel]);
            cache_get_value_name_int(i, "payday", CarShopInfo[i][csPayDay]);
            vehicle_model = CarShopInfo[i][csVehicleModel];
            temp_idx = vehicle_model - 400;
            if(vehicle_model > 0)
            {
                vehicleid = CreateVehicleVEx(NPO_PUB_SALON, NPO_NONE, vehicle_model, CarShopInfo[i][csPos][0], CarShopInfo[i][csPos][1], CarShopInfo[i][csPos][2], CarShopInfo[i][csPos][3], -1, -1, 600);
                CarShopInfo[i][csVehicleIDx] = vehicleid;
                veh_info[vehicleid][v_car_shop_idx] = i;
                LinkVehicleToInterior(vehicleid, 0);
                SetVehicleVirtualWorld(vehicleid, 0);
                STRING_GLOBAL[0] = EOS;
                if(GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_BOAT || GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_PLANE)
                {
                    f(STRING_GLOBAL, "Название: "I"%s (ID: %d)"W"\n\n\
                        Стоимость: "I"%d$"W"\n\n\
                        Класс: "I"%s"W"\n\
                        Тип: "I"%s"W"", GetVehicleName(vehicleid), GetVehicleData(temp_idx, E_VD_ID), GetVehicleData(temp_idx, E_VD_PRICE), vehicle_class_name[GetVehicleData(temp_idx, E_VD_CLASS)], vehicle_type_name[GetVehicleData(temp_idx, E_VD_TYPE)]);
                }
                else
                {
                    f(STRING_GLOBAL, "Название: "I"%s (ID: %d)"W"\n\n\
                        Стоимость: "I"%d$"W"\n\
                        Макс. скорость: "I"%d KM/H"W"\n\
                        Макс. вместимость бака: "I"%d"W"\n\n\
                        Класс: "I"%s"W"\n\
                        Тип: "I"%s"W"", GetVehicleName(vehicleid), GetVehicleData(temp_idx, E_VD_ID), GetVehicleData(temp_idx, E_VD_PRICE), floatround(GetVehicleData(temp_idx, E_VD_MAX_SPEED)), GetVehicleData(temp_idx, E_VD_MAX_FUEL), vehicle_class_name[GetVehicleData(temp_idx, E_VD_CLASS)], vehicle_type_name[GetVehicleData(temp_idx, E_VD_TYPE)]);
                }
                veh_info[vehicleid][v_text] = Create3DTextLabel(STRING_GLOBAL, COLOR_WHITE, 0.0, 0.0, 0.0, 10.0, 0, 1);
                Attach3DTextLabelToVehicle(veh_info[vehicleid][v_text], vehicleid, 0.0, 0.0, 1.5);
                count++;
            }
            else
            {
                CarShopInfo[i][csVehicleIDx] = INVALID_VEHICLE_ID;
            }
        }
    }
    UploadVehicleCarShop();
    printf("Автосалоны загружены: %d т/с за %d мс", count, GetTickCount() - time);
}

CheckVehicleCarShop()
{
    if(new_car_payday > 0) new_car_payday--;
    if(new_car_payday == 0)
    {
        new vehicle_model, biz_car_shop[MAX_CAR_SHOP] = {72, 71, 70, 69, 73, -1, -2};
        for(new i = 0; i < MAX_CAR_SHOP; i++)
        {
            vehicle_model = new_car_list[i];
            if(vehicle_model != -1) AddVehicleToCarShop(biz_car_shop[i], vehicle_model);
        }
        UploadVehicleCarShop();
    }
    for(new i = 0; i < MAX_CAR_SHOP_COORDS; i++)
    {
        if(CarShopInfo[i][csVehicleModel] == 0) continue;
        if(CarShopInfo[i][csPayDay] > 0)
        {
            CarShopInfo[i][csPayDay]--;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `car_shop` SET `payday` = %d WHERE `id` = %d",
            CarShopInfo[i][csPayDay], i + 1);
            mysql_tquery(con_bd, STRING_GLOBAL);

            if(CarShopInfo[i][csPayDay] == 0) DestroyCarShopVehicle(i);
        }
    }
    return 1;
}

DestroyCarShopVehicle(i)
{
    CarShopInfo[i][csVehicleModel] = 0;

    if(CarShopInfo[i][csVehicleIDx] != INVALID_VEHICLE_ID)
    {
        DestroyVehicleVEx(CarShopInfo[i][csVehicleIDx]);
        CarShopInfo[i][csVehicleIDx] = INVALID_VEHICLE_ID;
    }

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `car_shop` SET `vehicle_model` = 0 WHERE `id` = %d", i + 1);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

GetVehicleCarShopIDx(class, type)
{
    new idx;
    for(new i = 0; i < 212; i++)
    {
        idx = random(212);
        if(class != -1 && class != -2 && gVehicleData[idx][E_VD_CLASS] != class) continue;
        if(gVehicleData[idx][E_VD_TYPE] != type) continue;
        if(gVehicleData[idx][E_VD_PRICE] > 5000000) continue;
        if(gVehicleData[idx][E_VD_CLASS] == VEHICLE_CLASS_UNIQUE) continue;
        return idx;
    }
    return idx;
}

UploadVehicleCarShop()
{
    new_car_list[0] = GetVehicleCarShopIDx(VEHICLE_CLASS_NOPE, VEHICLE_STATE_CAR) + 400;
    new_car_list[1] = GetVehicleCarShopIDx(VEHICLE_CLASS_C, VEHICLE_STATE_CAR) + 400;
    new_car_list[2] = GetVehicleCarShopIDx(VEHICLE_CLASS_B, VEHICLE_STATE_CAR) + 400;
    new_car_list[3] = GetVehicleCarShopIDx(VEHICLE_CLASS_A, VEHICLE_STATE_CAR) + 400;
    new_car_list[4] = GetVehicleCarShopIDx(-1, VEHICLE_STATE_MOTO) + 400;
    new_car_list[5] = GetVehicleCarShopIDx(-1, VEHICLE_STATE_PLANE) + 400;
    new_car_list[6] = GetVehicleCarShopIDx(-1, VEHICLE_STATE_BOAT) + 400;
    new_car_payday = MAX_PAY_DAY_CAR_SHOP;
    return 1;
}

AddVehicleToCarShop(idx, vehicle_model)
{
    new vehicleid;
    for(new i = 0; i < MAX_CAR_SHOP_COORDS; i++)
    {
        if(CarShopInfo[i][csBizIDx] != idx) continue;
        if(CarShopInfo[i][csVehicleModel] != 0) continue;
        CarShopInfo[i][csVehicleModel] = vehicle_model;
        CarShopInfo[i][csPayDay] = MAX_PAY_DAY_CAR_SHOP_DELETE;
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `car_shop` SET `vehicle_model` = %d, `payday` = %d WHERE `id` = %d",
        CarShopInfo[i][csVehicleModel], CarShopInfo[i][csPayDay], i + 1);
        mysql_tquery(con_bd, STRING_GLOBAL);
        vehicleid = CreateVehicleVEx(NPO_PUB_SALON, NPO_NONE, vehicle_model, CarShopInfo[i][csPos][0], CarShopInfo[i][csPos][1], CarShopInfo[i][csPos][2], CarShopInfo[i][csPos][3], -1, -1, 600);
        CarShopInfo[i][csVehicleIDx] = vehicleid;
        veh_info[vehicleid][v_car_shop_idx] = i;
        LinkVehicleToInterior(vehicleid, 0);
        SetVehicleVirtualWorld(vehicleid, 0);
        new temp_idx = vehicle_model - 400;
        STRING_GLOBAL[0] = EOS;
        if(GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_BOAT || GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_PLANE)
        {
            f(STRING_GLOBAL, "Название: "I"%s (ID: %d)"W"\n\n\
                Стоимость: "I"%d$"W"\n\n\
                Класс: "I"%s"W"\n\
                Тип: "I"%s"W"", GetVehicleName(vehicleid), GetVehicleData(temp_idx, E_VD_ID), GetVehicleData(temp_idx, E_VD_PRICE), vehicle_class_name[GetVehicleData(temp_idx, E_VD_CLASS)], vehicle_type_name[GetVehicleData(temp_idx, E_VD_TYPE)]);
        }
        else
        {
            f(STRING_GLOBAL, "Название: "I"%s (ID: %d)"W"\n\n\
                Стоимость: "I"%d$"W"\n\
                Макс. скорость: "I"%d KM/H"W"\n\
                Макс. вместимость бака: "I"%d"W"\n\n\
                Класс: "I"%s"W"\n\
                Тип: "I"%s"W"", GetVehicleName(vehicleid), GetVehicleData(temp_idx, E_VD_ID), GetVehicleData(temp_idx, E_VD_PRICE), floatround(GetVehicleData(temp_idx, E_VD_MAX_SPEED)), GetVehicleData(temp_idx, E_VD_MAX_FUEL), vehicle_class_name[GetVehicleData(temp_idx, E_VD_CLASS)], vehicle_type_name[GetVehicleData(temp_idx, E_VD_TYPE)]);
        }
        veh_info[vehicleid][v_text] = Create3DTextLabel(STRING_GLOBAL, COLOR_WHITE, 0.0, 0.0, 0.0, 10.0, 0, 1);
        Attach3DTextLabelToVehicle(veh_info[vehicleid][v_text], vehicleid, 0.0, 0.0, 1.5);
        break;
    }
    return 1;
}

CMD:car_shop(playerid, params[])
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""W"\
    На сервере есть "I"%d"W" автосалонов, каждые "I"%d"W" час(-а/-ов) в них появляются транспортные средства.\n\n\
    После поступления транспортного средства в автосалон, для приобретения оно будет доступно в течении "I"%d"W" час(-а/-ов).\n\
    По истечению времени оно будет удалено из автосалона, а на его место поступит новое транспортное средство.\n\n\
    Ближайшее поступление через "I"%d"W" час(-а/-ов):", MAX_CAR_SHOP, MAX_PAY_DAY_CAR_SHOP, MAX_PAY_DAY_CAR_SHOP_DELETE, new_car_payday);
    new vehicle_model;
    for(new i = 0; i < MAX_CAR_SHOP; i++)
    {
        vehicle_model = new_car_list[i];
        if(vehicle_model != -1)
        {
            f(STRING_GLOBAL, "%s\n\n%s - %s [ID: "I"%d"W"]", STRING_GLOBAL, car_shop_name[i], GetVehicleName(INVALID_VEHICLE_ID, vehicle_model), vehicle_model);
        }
    }
    strcat(STRING_GLOBAL, "\n\n{"#cLIGHTRED"}Обратите внимание! Если на территории автосалона не будет хватать места под новое транспортное средство, оно не появится!");
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация об автосалонах", STRING_GLOBAL, "Закрыть", "");
    return 1;
}

CMD:car_shop_check(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckVehicleCarShop();
    return 1;
}

GetBizzIDCarsRoom(classId)
{
    for(new i = totalbizz-1; i != -1; i--)
    {
        if(b_info[i][_tip] == B_CAR_SHOWROOM && b_info[i][_world] == classId)
            return i;
    }
    return -1;
}

RC_ShowRoom_OnGameModeInit()
{
    new vehicleid, count[2];
    for(new i = MAX_VEH_MODELS_REPLACE-1; i != -1; i--)
    {
        vehicleid = CreateVehicleVEx(NPO_PUB_SALON, NPO_CUSTOM_VEH, customVehModels[i][CustomID], car_showroom_pos[count[0]][0], car_showroom_pos[count[0]][1], car_showroom_pos[count[0]][2], car_showroom_pos[count[0]][3], 1, 1, 600);
        LinkVehicleToInterior(vehicleid, 1);
        SetVehicleVirtualWorld(vehicleid, count[1]);
        count[0]++;
        if(count[0] == 13)
        {
            count[0] = 0;
            count[1]++;
        }

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Название: "I"%s (ID: %d)"W"\n\n\
            Стоимость: "I"%d FM"W"\n\
            Макс. скорость: "I"%d KM/H"W"\n\
            Макс. вместимость бака: "I"%d"W"\n\n\
            Класс: "I"Real Cars"W"\n\
            Тип: "I"%s"W"",
            GetVehicleName(INVALID_VEHICLE_ID, customVehModels[i][CustomID]), customVehModels[i][CustomID],
            customVehModels[i][ModelPrice], floatround(customVehModels[i][ModelMaxSpeed]-50.0),
            GetVehicleData(customVehModels[i][ModelID], E_VD_MAX_FUEL), vehicle_type_name[GetVehicleData(customVehModels[i][ModelID], E_VD_TYPE)]);
        RC_ShowRoom_3DText[i] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 0.0, 0.0, 3.0, 10.0, INVALID_PLAYER_ID, vehicleid, streamer_TESTLOL, 3000);
    }

    RC_DoorPickup[0] = CreateDynamicPickup(19132, 23, 2174.2466,1398.1404,11.0625, 0);
    RC_DoorPickup[1] = CreateDynamicPickup(19132, 23, 1308.7643,-50.4123,2002.4956, -1);

    CreateDynamic3DTextLabel("Автосалон\nReal Cars", COLOR_WHITE, 2174.2466,1398.1404,11.0625, 30.0);
}

CMD:addcarshop(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    if(sscanf(params, "ii", params[0], params[1])) return SendInfo(playerid, "Используйте: /addcarshowroom [id транспорта] [id автосалона]");
    if(params[0] < 400 || params[0] > 610) return SendError(playerid, "ID транспорта должен быть не менее 400 и не более 610.");
    if(params[1] < 1 || params[1] > 7) return SendError(playerid, "ID автосалона должен быть не менее 1 и не более 7.");
    new biz_car_shop[MAX_CAR_SHOP] = {69, 70, 71, 72, 73, -1, -2}, idx = biz_car_shop[params[1] - 1];
    AddVehicleToCarShop(idx, params[0]);
    SendAccess(playerid, "Вы добавили в автосалон %d - %s.", idx, GetVehicleName(INVALID_VEHICLE_ID, params[0]));
    return 1;
}
