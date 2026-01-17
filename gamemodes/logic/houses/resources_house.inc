GetResourecesHouse(houseid)
{
    new count = 0;
    for(new idx = 1; idx <= totalresourceshouse; idx++)
    {
        if(ResourcesHouseInfo[idx][rhHouseIDx] == houseid) count++;
    }
    return count;
}

GetMaxResourcesHouse(houseid)
{
    new squar = h_info[houseid][h_squar];
    switch(squar)
    {
        case 1..4: squar++;
        default: squar = 2;
    }
    return squar;
}

forward load_resources_house();
public load_resources_house()
{
    new time = GetTickCount(), str[512];
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iiiiiffffff",
            ResourcesHouseInfo[idx][rhIDx],
            ResourcesHouseInfo[idx][rhHouseIDx],
            ResourcesHouseInfo[idx][rhDay],
            ResourcesHouseInfo[idx][rhTime],
            ResourcesHouseInfo[idx][rhObject][0],
            ResourcesHouseInfo[idx][rhPos][0],
            ResourcesHouseInfo[idx][rhPos][1],
            ResourcesHouseInfo[idx][rhPos][2],
            ResourcesHouseInfo[idx][rhPos][3],
            ResourcesHouseInfo[idx][rhPos][4],
            ResourcesHouseInfo[idx][rhPos][5]);

            ResourcesHouseInfo[idx][rhObject][1] = CreateDynamicObject(ResourcesHouseInfo[idx][rhObject][0], ResourcesHouseInfo[idx][rhPos][0], ResourcesHouseInfo[idx][rhPos][1], ResourcesHouseInfo[idx][rhPos][2], ResourcesHouseInfo[idx][rhPos][3], ResourcesHouseInfo[idx][rhPos][4], ResourcesHouseInfo[idx][rhPos][5], -1, -1, -1, 120.00, 120.00);
            ResourcesHouseInfo[idx][rhArea] = CreateDynamicSphere(ResourcesHouseInfo[idx][rhPos][0], ResourcesHouseInfo[idx][rhPos][1], ResourcesHouseInfo[idx][rhPos][2], 1.0, -1, -1, -1);
            UpdateAreaInfo(ResourcesHouseInfo[idx][rhArea], TYPE_RESOURCES, ResourcesHouseInfo[idx][rhObject][0] == 19473 ? AREA_SUBTYPE_RESOURCES_H_COTTON : AREA_SUBTYPE_RESOURCES_H_LINEN, idx);
            STRING_MIN[0] = EOS;
            if(ResourcesHouseInfo[idx][rhTime] == 6) STRING_MIN = "Можно собрать";
            else f(STRING_MIN, "Можно собрать через "W"%d"I" час(-а/-ов)", 6 - ResourcesHouseInfo[idx][rhTime]);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s [%d]\n\nДом: "W"%d"I"\nОсталось %d дней\n%s", ResourcesHouseInfo[idx][rhObject][0] == 19473 ? "Хлопок" : "Лен", ResourcesHouseInfo[idx][rhIDx], ResourcesHouseInfo[idx][rhHouseIDx], ResourcesHouseInfo[idx][rhDay], STRING_MIN);
            ResourcesHouseInfo[idx][rhText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, ResourcesHouseInfo[idx][rhPos][0], ResourcesHouseInfo[idx][rhPos][1], ResourcesHouseInfo[idx][rhPos][2] + 1.0, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
            totalresourceshouse++;
        }
    }
    printf("Грядок в садах загружено: %d за %d мс", totalresourceshouse, GetTickCount() - time);
}

forward create_resources_house(idx);
public create_resources_house(idx)
{
    ResourcesHouseInfo[idx][rhIDx] = cache_insert_id();
    return 1;
}

CreateResourcesHouse(playerid)
{
    new i = GetPVarInt(playerid, "LoadResourcesHouse")-1, idx = GetPVarInt(playerid, "LoadResourcesHouseIDx");
    DeletePVar(playerid, "LoadResourcesHouse");
    DeletePVar(playerid, "LoadResourcesHouseIDx");
    if(i < 0) return 1;
    new h = GetPlayerHouseID(playerid);
    if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
    if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");

    if(!GetInventoryAmount(playerid, idx)) return SendError(playerid, "У Вас нет семян данного типа.");

    DestroyObject(ResourcesHouseInfo[i][rhObject][1]);

    new Float:PlPos[4];
    GetPlayerPos(playerid, PlPos[0], PlPos[1], PlPos[2]);
    GetPlayerFacingAngle(playerid, PlPos[3]);

    ResourcesHouseInfo[i][rhHouseIDx] = h;
    ResourcesHouseInfo[i][rhDay] = 15;
    ResourcesHouseInfo[i][rhTime] = 0;
    ResourcesHouseInfo[i][rhObject][0] = ItemsInfo[idx][iModel];
    ResourcesHouseInfo[i][rhPos][0] = PlPos[0]+floatcos(PlPos[3]+90, degrees);
    ResourcesHouseInfo[i][rhPos][1] = PlPos[1]+floatsin(PlPos[3]+90, degrees);
    ResourcesHouseInfo[i][rhPos][2] = PlPos[2] - 0.8;
    ResourcesHouseInfo[i][rhPos][3] = 0.0;
    ResourcesHouseInfo[i][rhPos][4] = 0.0;
    ResourcesHouseInfo[i][rhPos][5] = PlPos[3]+90;

    ResourcesHouseInfo[i][rhObject][1] = CreateDynamicObject(ResourcesHouseInfo[i][rhObject][0], ResourcesHouseInfo[i][rhPos][0], ResourcesHouseInfo[i][rhPos][1], ResourcesHouseInfo[i][rhPos][2], ResourcesHouseInfo[i][rhPos][3], ResourcesHouseInfo[i][rhPos][4], ResourcesHouseInfo[i][rhPos][5], -1, -1, -1, 120.00, 120.00);
    ResourcesHouseInfo[i][rhArea] = CreateDynamicSphere(ResourcesHouseInfo[i][rhPos][0], ResourcesHouseInfo[i][rhPos][1], ResourcesHouseInfo[i][rhPos][2], 1.0, -1, -1, -1);
    UpdateAreaInfo(ResourcesHouseInfo[i][rhArea], TYPE_RESOURCES, ResourcesHouseInfo[i][rhObject][0] == 19473 ? AREA_SUBTYPE_RESOURCES_H_COTTON : AREA_SUBTYPE_RESOURCES_H_LINEN, i);
    STRING_MIN[0] = EOS;
    if(ResourcesHouseInfo[i][rhTime] == 6) STRING_MIN = "Можно собрать";
    else f(STRING_MIN, "Можно собрать через "W"%d"I" час(-а/-ов)", 6 - ResourcesHouseInfo[i][rhTime]);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s [%d]\n\nДом: "W"%d"I"\nОсталось %d дней\n%s", ResourcesHouseInfo[i][rhObject][0] == 19473 ? "Хлопок" : "Лен", ResourcesHouseInfo[i][rhIDx], ResourcesHouseInfo[i][rhHouseIDx], ResourcesHouseInfo[i][rhDay], STRING_MIN);
    ResourcesHouseInfo[i][rhText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, ResourcesHouseInfo[i][rhPos][0], ResourcesHouseInfo[i][rhPos][1], ResourcesHouseInfo[i][rhPos][2] + 1.0, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `resources_house` (`house`, `time`, `object`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES (%d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f')",
    ResourcesHouseInfo[i][rhHouseIDx], ResourcesHouseInfo[i][rhTime], ResourcesHouseInfo[i][rhObject][0], ResourcesHouseInfo[i][rhPos][0], ResourcesHouseInfo[i][rhPos][1], ResourcesHouseInfo[i][rhPos][2], ResourcesHouseInfo[i][rhPos][3], ResourcesHouseInfo[i][rhPos][4], ResourcesHouseInfo[i][rhPos][5]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_resources_house", "i", i);

    GivePlayerInventory(playerid, idx, -1);

    SendAccess(playerid, "Вы использовали \"%s\".", ItemsInfo[idx][iName]);
    return 1;
}

DestroyResourcesHouse(idx)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `resources_house` WHERE `id` = %d", ResourcesHouseInfo[idx][rhIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    if(ResourcesHouseInfo[idx][rhIDx] != 0)
    {
        DestroyDynamicObject(ResourcesHouseInfo[idx][rhObject][1]);
        DestroyDynamicArea(ResourcesHouseInfo[idx][rhArea]);
        DestroyDynamic3DTextLabel(ResourcesHouseInfo[idx][rhText]);
    }

    ResourcesHouseInfo[idx][rhIDx] =
    ResourcesHouseInfo[idx][rhDay] =
    ResourcesHouseInfo[idx][rhHouseIDx] =
    ResourcesHouseInfo[idx][rhTime] =
    ResourcesHouseInfo[idx][rhArea] =
    ResourcesHouseInfo[idx][rhObject][0] = 
    ResourcesHouseInfo[idx][rhObject][1] = 0;
    ResourcesHouseInfo[idx][rhText] = INVALID_3DTEXT_ID;
    for(new i = 5; i != -1; i--)
        ResourcesHouseInfo[idx][rhPos][i] = 0.0;
    return 1;
}

CheckResourcesHouse()
{
    for(new i = 1; i < MAX_RESOURCES_HOUSE; i++)
    {
        if(ResourcesHouseInfo[i][rhHouseIDx] == 0) continue;
        if(ResourcesHouseInfo[i][rhTime] == 6) continue;
        ResourcesHouseInfo[i][rhTime]++;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `resources_house` SET `time` = %d WHERE `id` = %d",
        ResourcesHouseInfo[i][rhTime], ResourcesHouseInfo[i][rhIDx]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        STRING_MIN[0] = EOS;
        if(ResourcesHouseInfo[i][rhTime] == 6) STRING_MIN = "Можно собрать";
        else f(STRING_MIN, "Можно собрать через "W"%d"I" час(-а/-ов)", 6 - ResourcesHouseInfo[i][rhTime]);
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\n\nДом: "W"%d"I"\nОсталось %d дней\n%s",
            ResourcesHouseInfo[i][rhObject][0] == 19473 ? "Хлопок" : "Лен", ResourcesHouseInfo[i][rhHouseIDx], ResourcesHouseInfo[i][rhDay], STRING_MIN);
        UpdateDynamic3DTextLabelText(ResourcesHouseInfo[i][rhText], COLOR_MAIN, STRING_GLOBAL);
    }
    return 1;
}

CMD:reshouse(playerid, params[])
{
    ShowPlayerDialog(playerid, D_RES_HOUSE, DIALOG_STYLE_LIST, ""I"Управление семенами", ""I"[1]"W" Посадить хлопок\n"I"[2]"W" Посадить лен\n"I"[3]"W" Забрать семена", "Далее", "Отмена");
    return 1;
}

CMD:testres(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckResourcesHouse();
    return 1;
}

CMD:dresoureces(playerid, params[0])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /dresoureces [id дома]");

    new
        houseId = strval(params);

    if(!(0 <= houseId < totalhouses))
        return SendError(playerid, "Неверный ID дома.");
    if(h_info[houseId][h_mysql_id] == INVALID_MYSQL_ID)
        return SendError(playerid, "Дом не задействован.");

    new count = 0;
    for(new i = 1; i <= totalresourceshouse; i++)
    {
        if(ResourcesHouseInfo[i][rhHouseIDx] != houseId) continue;
        DestroyResourcesHouse(i);
        count++;
    }

    if(count == 0) return SendError(playerid, "На территории сада данного дома нет грядок.");

    if(h_info[houseId][h_user_id] != INVALID_MYSQL_ID)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, ""I"%s"W" удалил(-а) все грядки на территории сада Вашего дома.", get_name(playerid));
        AddNotify(h_info[houseId][h_user_id], STRING_GLOBAL);
    }

    SendAccess(playerid, "Вы удалили все грядки на территории сада дома %d.", houseId);

    Log(LOG_player, INFO, "%s[%d](%s %s) удалил грядки дома (%d) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", houseId);
    return 1;
}