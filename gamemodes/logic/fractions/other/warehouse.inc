#define MAX_WAREHOUSE                   25
#define MAX_VEHICLE_PATRON_MATERIALS    25000
#define MAX_VEHICLE_DRUGS               25000
#define MAX_VEHICLE_MEDICINES           25000

new WarehousePlayerStatus[MAX_PLAYERS];
new WarehousePlayerIDx[MAX_PLAYERS];
new WarehousePlayerFraction[MAX_PLAYERS];

enum WAREHOUSE_INFO
{
    WarehouseIDx,
    WarehouseFraction,
    WarehouseMaterials,
    WarehouseCartridges,
    WarehouseStatus
};

new WarehouseInfo[MAX_WAREHOUSE][WAREHOUSE_INFO];

new WarehouseMedicines;
new Text3D:WarehouseText[6];
new WarehousePickup[3];

CreateWarehouseInfo()
{
    new a_mate = GetFractionWarehouse(NATIONAL_GUARD, fwMate), a_patron = GetFractionWarehouse(NATIONAL_GUARD, fwPatron);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Склад оружия\n\nМатериалы: "W"%d"I"\nПатроны: "W"%d", a_mate, a_patron);
    WarehouseText[0] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 1855.4067,-2106.2534,2001.5852, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Склад оружия\n\nМатериалы: "W"%d"I"\nПатроны: "W"%d", a_mate, a_patron);
    WarehouseText[1] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 2775.0317,-2524.9277,13.6729, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    // Сотрудник склада;
    CreateActor(61, 2719.3726,-2511.5076,13.6641,89.3141);
    CreateDynamic3DTextLabel("NPC: "I"Сотрудник склада", COLOR_WHITE, 2719.3726,-2511.5076,13.6641 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    WarehouseText[2] = CreateDynamic3DTextLabel("<< Гос. контракты на поставку патронов и материалов >>", COLOR_MAIN, 2718.6709,-2511.5359,13.6641, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ Медицинский склад ]\n\n[ Место для разгрузки медикаментов после разработки ]\n\nМедикаменты: "W"%d", WarehouseMedicines);
    WarehouseText[3] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 2718.6624, 745.8964, 1024.4215, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ Медицинский склад ]\n\n[ Место для загрузки медикаментов в транспортное средство ]\n\nМедикаменты: "W"%d", WarehouseMedicines);
    WarehouseText[4] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 1354.7454, 354.4463, 20.4991, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Склад оружия\n\nМатериалы: "W"%d"I"\nПатроны: "W"%d", a_mate, a_patron);
    WarehouseText[5] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 1855.4067,-2096.2322,2001.5852, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    WarehousePickup[0] = CreateDynamicPickup(2358, 23, 2775.0317,-2524.9277,13.6729);
    WarehousePickup[1] = CreateDynamicPickup(1239, 23, 2718.6709,-2511.5359,13.6641);
    WarehousePickup[2] = CreateDynamicPickup(1279, 23, 1354.7454, 354.4463, 20.4991);
    return 1;
}

UpdateWarehouseInfo(idx)
{
    switch(idx)
    {
        case 0:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Склад оружия\n\nМатериалы: "W"%d"I"\nПатроны: "W"%d", GetFractionWarehouse(NATIONAL_GUARD, fwMate), GetFractionWarehouse(NATIONAL_GUARD, fwPatron));
            UpdateDynamic3DTextLabelText(WarehouseText[0], COLOR_MAIN, STRING_GLOBAL);
            UpdateDynamic3DTextLabelText(WarehouseText[1], COLOR_MAIN, STRING_GLOBAL);
            UpdateDynamic3DTextLabelText(WarehouseText[5], COLOR_MAIN, STRING_GLOBAL);
        }
        case 1:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ Медицинский склад ]\n\n[ Место для разгрузки медикаментов после разработки ]\n\nМедикаменты: "W"%d", WarehouseMedicines);
            UpdateDynamic3DTextLabelText(WarehouseText[3], COLOR_MAIN, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ Медицинский склад ]\n\n[ Место для загрузки медикаментов в транспортное средство ]\n\nМедикаменты: "W"%d", WarehouseMedicines);
            UpdateDynamic3DTextLabelText(WarehouseText[4], COLOR_MAIN, STRING_GLOBAL);
        }
    }
    return 1;
}

forward create_warehouse(idx);
public create_warehouse(idx)
{
    WarehouseInfo[idx][WarehouseIDx] = cache_insert_id();
    return 1;
}

forward load_warehouse();
public load_warehouse()
{
    new str[256], time = GetTickCount();
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            if(idx >= MAX_WAREHOUSE) break;
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iiiii",
            WarehouseInfo[idx][WarehouseIDx],
            WarehouseInfo[idx][WarehouseFraction],
            WarehouseInfo[idx][WarehouseMaterials],
            WarehouseInfo[idx][WarehouseCartridges],
            WarehouseInfo[idx][WarehouseStatus]);
        }
    }
    printf("[Warehouse System] Load: %d мс", GetTickCount()-time);
    return 1;
}

GetFreeWarehouseID()
{
    for(new i = 0; i < sizeof(WarehouseInfo); i++)
    {
        if(WarehouseInfo[i][WarehouseStatus] == 0) return i;
    }
    return -1;
}

CheckCreatedWarehouseID(idx)
{
    for(new i = 0; i < sizeof(WarehouseInfo); i++)
    {
        if(WarehouseInfo[i][WarehouseStatus] == 0) continue;
        if(WarehouseInfo[i][WarehouseFraction] == idx) return i;
    }
    return -1;
}

CreateWarehouse(playerid, fraction, materials, cartridges)
{
    if(GetFreeWarehouseID() == -1) return SendError(playerid, "В данный момент нет свободных мест под гос. контракты.");

    new idx = GetFreeWarehouseID();

    WarehouseInfo[idx][WarehouseFraction] = fraction;
    WarehouseInfo[idx][WarehouseMaterials] = materials;
    WarehouseInfo[idx][WarehouseCartridges] = cartridges;
    WarehouseInfo[idx][WarehouseStatus] = 1;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `warehouse` (`fraction`, `materials`, `cartridges`, `status`) VALUES (%d, %d, %d, %d)",
    WarehouseInfo[idx][WarehouseFraction], WarehouseInfo[idx][WarehouseMaterials], WarehouseInfo[idx][WarehouseCartridges], WarehouseInfo[idx][WarehouseStatus]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_warehouse", "i", idx);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] создал(-а) гос. контракт для поставки %d материал(-а/-ов) и %d патрон(-а/-ов).", get_name(playerid), playerid, WarehouseInfo[idx][WarehouseMaterials], WarehouseInfo[idx][WarehouseCartridges]);
    SendFractionMessage(fraction, 0x33CC66FF, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] создал(-а) гос. контракт для поставки %d материал(-а/-ов) и %d патрон(-а/-ов) для %s.", get_name(playerid), playerid, WarehouseInfo[idx][WarehouseMaterials], WarehouseInfo[idx][WarehouseCartridges], GetFractionName(p_info[playerid][member]));
    SendFractionMessage(NATIONAL_GUARD, 0x33CC66FF, STRING_GLOBAL);
    return 1;
}

SetProgressWarehouse(idx, materials, cartridges)
{
    if(WarehouseInfo[idx][WarehouseStatus] == 0) return 1;

    WarehouseInfo[idx][WarehouseMaterials] -= materials;
    WarehouseInfo[idx][WarehouseCartridges] -= cartridges;

    if(WarehouseInfo[idx][WarehouseMaterials] <= 0 || WarehouseInfo[idx][WarehouseCartridges] <= 0)
    {
        WarehouseInfo[idx][WarehouseIDx] = 0;
        WarehouseInfo[idx][WarehouseFraction] = 0;
        WarehouseInfo[idx][WarehouseMaterials] = 0;
        WarehouseInfo[idx][WarehouseCartridges] = 0;
        WarehouseInfo[idx][WarehouseStatus] = 0;

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `warehouse` WHERE `idx` = %d",
        idx);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `warehouse` SET `materials` = %d, `cartridges` = %d WHERE `idx` = %d",
        WarehouseInfo[idx][WarehouseMaterials], WarehouseInfo[idx][WarehouseCartridges], idx);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    return 1;
}

ShowWarehouse(playerid)
{
    new count = 0;
    STRING_GLOBAL = "[#] Название фракции\tМатериал(-а/-ов)\tПатрон(-а/-ов)\n", STRING_MIN[0] = EOS;
    for(new i = 0; i < sizeof(WarehouseInfo); i++)
    {
        if(WarehouseInfo[i][WarehouseStatus] == 0) continue;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\t%d\n", count + 1, GetFractionName(WarehouseInfo[i][WarehouseFraction]), WarehouseInfo[i][WarehouseMaterials], WarehouseInfo[i][WarehouseCartridges]);
        strcat(STRING_GLOBAL, STRING_MIN);
        p_temp[playerid][p_listitem][count] = i;
        count++;
    }
    if(!count) return SendError(playerid, "В данный момент нет гос. контрактов.");
    ShowPlayerDialog(playerid, D_WAREHOUSE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список гос. контрактов", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

ShowWarehouseInfo(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
    Введите количество патронов и материалов для поставки на склад организации:\n\n\
    Состояние склада:\n\n\
    \t— Патронов: {"#cGREEN"}%d"W"\n\
    \t— Материалов: {"#cGREEN"}%d"W"\n\n\
    Например: "I"Вводите 500 и на склад организации доставят 500 патронов и 500 материалов.",
    GetFractionWarehouse(NATIONAL_GUARD, fwMate), GetFractionWarehouse(NATIONAL_GUARD, fwPatron));
    ShowPlayerDialog(playerid, D_WAREHOUSE_CONTRACT, DIALOG_STYLE_INPUT, ""I"Гос. контракт на поставку патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:warehouse(playerid, params[])
{
    if(!army(playerid)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetVehicleModelEx(vehicleid) != 433) return SendError(playerid, "В данном транспортном средстве нет возможности перевозить материалы и патроны.");
    ShowWarehouse(playerid);
    return 1;
}

CMD:load(playerid, params[])
{
    if(!army(playerid) && !gang(playerid) && !mafia(playerid) && !biker(playerid) && !IsPlayerFractionMedic(playerid)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(IsPlayerInRangeOfPoint(playerid, 100.0, -575.4075,-1483.9923,10.5910) == 1)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(!gang(playerid) && !mafia(playerid) && !biker(playerid)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
        if(veh_info[vehicleid][v_model] != 478) return SendError(playerid, "В данном транспортном средстве нет возможности перевозить наркотики.");
        if(veh_info[vehicleid][v_loading] == 1) return SendError(playerid, "Транспортное средство уже в режиме загрузки.");
        if(veh_info[vehicleid][v_npoId] != p_info[playerid][member]) return SendError(playerid, "У Вас нет ключей от этого транспортного средства.");
        if(veh_info[vehicleid][v_engine] == 1) callcmd::en(playerid);

        new Float: VehiclePosX,
            Float: VehiclePosY,
            Float: VehiclePosZ,
            Float: VehiclePosR;

        GetVehicleZAngle(vehicleid, VehiclePosR);
        GetVehiclePos(vehicleid, VehiclePosX, VehiclePosY, VehiclePosZ);

        veh_info[vehicleid][v_loading] = 1;
        VehiclePosY = VehiclePosY - (5.0 * floatcos(VehiclePosR, degrees));
        VehiclePosX = VehiclePosX - (-5.0 * floatsin(VehiclePosR, degrees));
        veh_info[vehicleid][v_pickup] = CreateDynamicPickup(1279, 23, VehiclePosX, VehiclePosY, VehiclePosZ);
        UpdatePickupInfo(veh_info[vehicleid][v_pickup], TYPE_VEHICLE, PICKUP_SUBTYPE_INVALID_ID, vehicleid);

        if(veh_info[vehicleid][v_text] == INVALID_3DTEXT_ID)
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
            "W"Наркотики: "I"%d гр из %d гр",
            veh_info[vehicleid][v_drugs], MAX_VEHICLE_DRUGS);
            veh_info[vehicleid][v_text] = Create3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 0.0, 0.0, 0.0, 10.0, 0, 1);
            Attach3DTextLabelToVehicle(veh_info[vehicleid][v_text], vehicleid, 0.0, 0.0, 1.5);
        }
        RemovePlayerFromVehicle(playerid);
        return 1;
    }
    if(army(playerid) && IsPlayerInRangeOfPoint(playerid, 100.0, 2775.0317,-2524.9277,13.6729) == 1 ||
        (mafia(playerid) || gang(playerid) || biker(playerid)) && IsPlayerInRangeOfPoint(playerid, 100.0, 2775.0317,-2524.9277,13.6729) == 1 ||
        IsPlayerFractionMedic(playerid) && IsPlayerInRangeOfPoint(playerid, 100.0, 1354.7454, 354.4463, 20.4991) == 1)
    {
        if(GetVehicleModelEx(vehicleid) != 433 && GetVehicleModelEx(vehicleid) != 482 && GetVehicleModelEx(vehicleid) != 499) return SendError(playerid, "В данном транспортном средстве нет возможности перевозить материалы и патроны.");
        if(veh_info[vehicleid][v_loading] != 0) return SendError(playerid, "Транспортное средство уже находится в режиме загрузки.");
        if(veh_info[vehicleid][v_npoId] != p_info[playerid][member]) return SendError(playerid, "У Вас нет ключей от этого транспортного средства.");
        callcmd::en(playerid);

        new Float: VehiclePosX,
            Float: VehiclePosY,
            Float: VehiclePosZ,
            Float: VehiclePosR;
        GetVehicleZAngle(vehicleid, VehiclePosR);
        GetVehiclePos(vehicleid, VehiclePosX, VehiclePosY, VehiclePosZ);

        if(gang(playerid) || mafia(playerid) || biker(playerid))
        {
            veh_info[vehicleid][v_loading] = 2;
            VehiclePosY = VehiclePosY - (4.0 * floatcos(VehiclePosR, degrees));
            VehiclePosX = VehiclePosX - (-4.0 * floatsin(VehiclePosR, degrees));
            veh_info[vehicleid][v_pickup] = CreateDynamicPickup(2969, 23, VehiclePosX, VehiclePosY, VehiclePosZ - 0.5);
            UpdatePickupInfo(veh_info[vehicleid][v_pickup], TYPE_VEHICLE, PICKUP_SUBTYPE_INVALID_ID, vehicleid);
        }
        else if(army(playerid))
        {
            veh_info[vehicleid][v_loading] = 3;
            VehiclePosY = VehiclePosY - (6.0 * floatcos(VehiclePosR, degrees));
            VehiclePosX = VehiclePosX - (-6.0 * floatsin(VehiclePosR, degrees));
            veh_info[vehicleid][v_pickup] = CreateDynamicPickup(2969, 23, VehiclePosX, VehiclePosY, VehiclePosZ);
            UpdatePickupInfo(veh_info[vehicleid][v_pickup], TYPE_VEHICLE, PICKUP_SUBTYPE_INVALID_ID, vehicleid);
        }
        else if(IsPlayerFractionMedic(playerid))
        {
            veh_info[vehicleid][v_loading] = 4;
            VehiclePosY = VehiclePosY - (5.0 * floatcos(VehiclePosR, degrees));
            VehiclePosX = VehiclePosX - (-5.0 * floatsin(VehiclePosR, degrees));
            veh_info[vehicleid][v_pickup] = CreateDynamicPickup(1279, 23, VehiclePosX, VehiclePosY, VehiclePosZ);
            UpdatePickupInfo(veh_info[vehicleid][v_pickup], TYPE_VEHICLE, PICKUP_SUBTYPE_INVALID_ID, vehicleid);
        }

        if(veh_info[vehicleid][v_text] == INVALID_3DTEXT_ID)
        {
            STRING_GLOBAL[0] = EOS;
            if(army(playerid) || gang(playerid) || mafia(playerid) || biker(playerid)) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Патроны: "W"%d из %d"I"\nМатериалы: "W"%d из %d", veh_info[vehicleid][v_patron], MAX_VEHICLE_PATRON_MATERIALS, veh_info[vehicleid][v_materials], MAX_VEHICLE_PATRON_MATERIALS);
            else if(IsPlayerFractionMedic(playerid)) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Медикаменты: "W"%d из %d", veh_info[vehicleid][v_medicines], MAX_VEHICLE_MEDICINES);
            veh_info[vehicleid][v_text] = Create3DTextLabel(STRING_GLOBAL, COLOR_MAIN, 0.0, 0.0, 0.0, 10.0, 0, 1);
            Attach3DTextLabelToVehicle(veh_info[vehicleid][v_text], vehicleid, 0.0, 0.0, 3.0);
        }

        RemovePlayerFromVehicle(playerid);
        return 1;
    }
    SendError(playerid, "Вы слишком далеко от фракционного склада, нарко-фермы, военного склада и лаборатории.");
    return 1;
}

CMD:unload(playerid, params[])
{
    if(!army(playerid) && !gang(playerid) && !mafia(playerid) && !biker(playerid) && !IsPlayerFractionMedic(playerid)) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");

    new vehicleid = GetPlayerVehicleID(playerid);
    if(veh_info[vehicleid][v_patron] <= 0 && veh_info[vehicleid][v_materials] <= 0 && veh_info[vehicleid][v_medicines] <= 0 && veh_info[vehicleid][v_drugs] <= 0) return SendError(playerid, "В транспортном средстве нет патронов, материалов, медикаментов и наркотиков.");

    if(gang(playerid) || mafia(playerid) || biker(playerid))
    {
        if(IsPlayerInRangeOfPoint(playerid, 10.0, FractionsData[p_info[playerid][member]][fUnloadingPos][0], FractionsData[p_info[playerid][member]][fUnloadingPos][1], FractionsData[p_info[playerid][member]][fUnloadingPos][2]) == 0 && IsPlayerInRangeOfPoint(playerid, 25.0, 2167.2527,-1672.6479,15.0759) == 0) return SendError(playerid, "Вы слишком далеко от склада или наркопритона.");

        if(IsPlayerInRangeOfPoint(playerid, 15.0, 2167.2527,-1672.6479,15.0759))
        {
            if(DrugDenInfo[ddOwner] != p_info[playerid][member]) return SendError(playerid, "Наркопритон не принадлежит Вашей фракции.");

            new countOfDrugs = veh_info[vehicleid][v_drugs];
            //DrugDenInfo[ddSell][i] += veh_info[vehicleid][v_drugs][i];
            veh_info[vehicleid][v_drugs] = 0;

            SendAccess(playerid, "Вы выгрузили %d наркотиков на склад наркопритона.", countOfDrugs);

            SaveDrugDen();

            if(gang(playerid))
            {
                p_info[playerid][fracdata][20] += countOfDrugs;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, GANG_UDRUGS, countOfDrugs);

                p_info[playerid][ftop_gunload_drugs] += countOfDrugs;
                MysqlUpdatePlayerInt(playerid, "ftop_gunload_drugs", p_info[playerid][ftop_gunload_drugs]);
            }
            else if(mafia(playerid))
            {
                p_info[playerid][fracdata][25] += countOfDrugs;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, MAFIA_UDRUGS, countOfDrugs);

                p_info[playerid][ftop_munload_drugs] += countOfDrugs;
                MysqlUpdatePlayerInt(playerid, "ftop_munload_drugs", p_info[playerid][ftop_munload_drugs]);
            }
            else if(biker(playerid))
            {
                p_info[playerid][fracdata][30] += countOfDrugs;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, BIKER_UDRUGS, countOfDrugs);

                p_info[playerid][ftop_bunload_drugs] += countOfDrugs;
                MysqlUpdatePlayerInt(playerid, "ftop_bunload_drugs", p_info[playerid][ftop_bunload_drugs]);
            }

            UpdateFamilyLevel(playerid);
            return 1;
        }
        if(veh_info[vehicleid][v_patron] > 0)
        {
            new countOfPatron = veh_info[vehicleid][v_patron];

            SendAccess(playerid, "Вы выгрузили %d патронов на склад.", countOfPatron);

            SetFractionWarehouse(p_info[playerid][member], fwPatron, countOfPatron);
            veh_info[vehicleid][v_patron] = 0;

            if(gang(playerid))
            {
                p_info[playerid][fracdata][22] += countOfPatron;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, GANG_UMATERIALS, countOfPatron);

                p_info[playerid][ftop_gunload_materials] += countOfPatron;
                MysqlUpdatePlayerInt(playerid, "ftop_gunload_materials", p_info[playerid][ftop_gunload_materials]);
            }
            else if(mafia(playerid))
            {
                p_info[playerid][fracdata][27] += countOfPatron;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, MAFIA_UMATERIALS, countOfPatron);

                p_info[playerid][ftop_munload_materials] += countOfPatron;
                MysqlUpdatePlayerInt(playerid, "ftop_munload_materials", p_info[playerid][ftop_munload_materials]);
            }
            else if(biker(playerid))
            {
                p_info[playerid][fracdata][32] += countOfPatron;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, BIKER_UMATERIALS, countOfPatron);

                p_info[playerid][ftop_bunload_materials] += countOfPatron;
                MysqlUpdatePlayerInt(playerid, "ftop_bunload_materials", p_info[playerid][ftop_bunload_materials]);
            }

            UpdateFamilyLevel(playerid);
        }
        if(veh_info[vehicleid][v_materials] > 0)
        {
            new countOfMate = veh_info[vehicleid][v_materials];

            SendAccess(playerid, "Вы выгрузили %d материалов на склад.", countOfMate);

            SetFractionWarehouse(p_info[playerid][member], fwMate, countOfMate);
            veh_info[vehicleid][v_materials] = 0;

            if(gang(playerid))
            {
                p_info[playerid][fracdata][22] += countOfMate;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, GANG_UMATERIALS, countOfMate);

                p_info[playerid][ftop_gunload_materials] += countOfMate;
                MysqlUpdatePlayerInt(playerid, "ftop_gunload_materials", p_info[playerid][ftop_gunload_materials]);
            }
            else if(mafia(playerid))
            {
                p_info[playerid][fracdata][27] += countOfMate;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, MAFIA_UMATERIALS, countOfMate);

                p_info[playerid][ftop_munload_materials] += countOfMate;
                MysqlUpdatePlayerInt(playerid, "ftop_munload_materials", p_info[playerid][ftop_munload_materials]);
            }
            else if(biker(playerid))
            {
                p_info[playerid][fracdata][32] += countOfMate;
                SaveFracData(playerid);
                CheckPlayerMission(playerid, BIKER_UMATERIALS, countOfMate);

                p_info[playerid][ftop_bunload_materials] += countOfMate;
                MysqlUpdatePlayerInt(playerid, "ftop_bunload_materials", p_info[playerid][ftop_bunload_materials]);
            }

            UpdateFamilyLevel(playerid);
        }
        if(veh_info[vehicleid][v_drugs] > 0)
        {
            new member_idx = p_info[playerid][member], countOfDrugs = veh_info[vehicleid][v_drugs];
            veh_info[vehicleid][v_drugs] = 0;

            SetFractionWarehouse(member_idx, fwDrugs, countOfDrugs);

            SendAccess(playerid, "Вы выгрузили %d наркотиков на склад.", countOfDrugs);

            p_info[playerid][fracdata][20] += countOfDrugs;
            SaveFracData(playerid);

            CheckPlayerMission(playerid, HOSPITAL_UMEDICINES, countOfDrugs);
            UpdateFamilyLevel(playerid);
        }
    }
    else if(army(playerid))
    {
        if(WarehousePlayerStatus[playerid] == 0) return SendError(playerid, "У Вас нет гос. контракта на перевоз патронов и материалов.");
        if(WarehousePlayerFraction[playerid] == 0) return SendError(playerid, "У Вас нет гос. контракта на перевоз патронов и материалов.");

        new idx = WarehousePlayerIDx[playerid], fraction = WarehousePlayerFraction[playerid];

        if(IsPlayerInRangeOfPoint(playerid, 10.0, FractionsData[fraction][fUnloadingPos][0], FractionsData[fraction][fUnloadingPos][1], FractionsData[fraction][fUnloadingPos][2]))
        {
            new max_warehouse_patron = 500000, max_warehouse_materials = 500000;
            if(fraction == NATIONAL_GUARD) max_warehouse_patron = 1000000, max_warehouse_materials = 1000000;

            new countOfPatron = veh_info[vehicleid][v_patron], countOfMate = veh_info[vehicleid][v_materials];

            if(GetFractionWarehouse(fraction, fwPatron) + countOfPatron > max_warehouse_patron) countOfPatron = max_warehouse_patron - GetFractionWarehouse(fraction, fwPatron);
            if(GetFractionWarehouse(fraction, fwMate) + countOfMate > max_warehouse_materials) countOfMate = max_warehouse_materials - GetFractionWarehouse(fraction, fwMate);

            SetFractionWarehouse(fraction, fwPatron, countOfPatron);
            veh_info[vehicleid][v_patron] -= countOfPatron;

            SetFractionWarehouse(fraction, fwMate, countOfMate);
            veh_info[vehicleid][v_materials] -= countOfMate;

            p_info[playerid][fracdata][10] += countOfPatron + countOfMate;
            SaveFracData(playerid);

            CheckPlayerMission(playerid, ARMY_UMATERIALS, countOfPatron + countOfMate);

            UpdateFamilyLevel(playerid);

            p_info[playerid][ftop_aunload_materials] += countOfPatron + countOfMate;
            MysqlUpdatePlayerInt(playerid, "ftop_aunload_materials", p_info[playerid][ftop_aunload_materials]);

            WarehousePlayerStatus[playerid] = 0;
            WarehousePlayerIDx[playerid] = -1;
            WarehousePlayerFraction[playerid] = 0;

            SendAccess(playerid, "Вы разгрузили %d патронов и %d материалов на склад %s.", countOfPatron, countOfMate, GetFractionName(fraction));

            SetProgressWarehouse(idx, countOfMate, countOfPatron);
        } else SendError(playerid, "Вы слишком далеко от склада фракции, которая была указана в гос. контракте.");
    }
    else if(IsPlayerFractionMedic(playerid))
    {
        if(IsPlayerInRangeOfPoint(playerid, 10.0, FractionsData[p_info[playerid][member]][fUnloadingPos][0], FractionsData[p_info[playerid][member]][fUnloadingPos][1], FractionsData[p_info[playerid][member]][fUnloadingPos][2]) == 0) return SendError(playerid, "Вы слишком далеко от склада.");

        if(veh_info[vehicleid][v_medicines] > 0)
        {
            new countOfMedicines = veh_info[vehicleid][v_medicines];

            SendAccess(playerid, "Вы выгрузили %d медикаментов на склад.", countOfMedicines);

            SetFractionWarehouse(p_info[playerid][member], fwDrugs, countOfMedicines);
            veh_info[vehicleid][v_medicines] = 0;

            p_info[playerid][fracdata][16] += countOfMedicines;
            SaveFracData(playerid);
            CheckPlayerMission(playerid, HOSPITAL_UMEDICINES, countOfMedicines);

            UpdateFamilyLevel(playerid);

            p_info[playerid][ftop_hunload_medicines]++;
            MysqlUpdatePlayerInt(playerid, "ftop_hunload_medicines", p_info[playerid][ftop_hunload_medicines]);
        }
    }
    return 1;
}

CMD:end(playerid, params[])
{
    if(p_temp[playerid][LoadCount] != 0)
    {
        if(p_temp[playerid][LoadCount] != 0)
        {
            if(army(playerid))
            {
                SetFractionWarehouse(NATIONAL_GUARD, fwMate, 500);
                SetFractionWarehouse(NATIONAL_GUARD, fwPatron, 500);

                UpdateWarehouseInfo(0);
            }
            else if(IsPlayerFractionMedic(playerid))
            {
                WarehouseMedicines += 500;
                MysqlUpdateOtherInt("warehouse_medicines", WarehouseMedicines);

                UpdateWarehouseInfo(1);
            }
        }

        p_temp[playerid][LoadCount] = 0;

        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
        ClearAnimations(playerid);
        //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        SendAccess(playerid, "Вы выбросили все предметы.");
    }
    return 1;
}
