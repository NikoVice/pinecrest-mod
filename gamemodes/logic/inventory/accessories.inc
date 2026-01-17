UsePlayerAccessories(playerid, slot_id, acc_slot, statusUse)
{
    if(statusUse)
    {
        if(InventoryPlayer[playerid][slot_id][inv_acc_wear] <= 0)
            return SendError(playerid, "Данный аксессуар сломанный, отремонтировать его можно в мастерской одежды.");
        if(InventoryPlayer[playerid][slot_id][inv_acc_pos][0] != 0.0 && InventoryPlayer[playerid][slot_id][inv_acc_pos][1] != 0.0)
        {
            SetPVarInt(playerid, #USE_SLOT_ID, slot_id);
            SetPVarInt(playerid, #USE_ACC_SLOT, acc_slot);
            
            return ShowPlayerDialog(playerid, D_ACCESSORIES_SELECT, DIALOG_STYLE_LIST, ""I"Одеть акссесуар", ""I"[1]"W" На стандартных позициях\n"I"[2]"W" На ранее сохраненных", "Поставить", "Закрыть");
            // return Dialog_Open(playerid, Dialog:ACCESSORIES_SELECT_USE, DIALOG_STYLE_LIST, ""I"Одеть акссесуар", ""I"[1]"W" На стандартных позициях\n"I"[2]"W" На ранее сохраненных", "Поставить", "Закрыть");
        }
        InventoryPlayer[playerid][slot_id][inv_status_use] = statusUse;
        if(!AttachPlayerAccessories(playerid, slot_id, .slot_use = acc_slot))
            return 1;
        SendAccess(playerid, "Вы надели аксессуар, используйте /editor для редактирования.");
    }
    else
    {
        SendAccess(playerid, "Вы сняли аксессуар.");
        SetPlayerAccessoriesStatusUse(playerid, slot_id);
        Equipment_AccessoriesUse(playerid);
    }
    Equipment_Update(playerid);
    return 1;
}

/*DialogResponse:ACCESSORIES_SELECT_USE(playerid, response, listitem, inputtext[])
{
    new slot_id = GetPVarInt(playerid, #USE_SLOT_ID),
        acc_slot = GetPVarInt(playerid, #USE_ACC_SLOT);
    DeletePVar(playerid, #USE_SLOT_ID);
    DeletePVar(playerid, #USE_ACC_SLOT);
    if(!response) return 1;
    if(!(0 <= listitem <= 1)) return 1;
    InventoryPlayer[playerid][slot_id][inv_status_use] = listitem+1;
    if(!AttachPlayerAccessories(playerid, slot_id, .slot_use = acc_slot))
        return 1;
    SendAccess(playerid, "Вы надели аксессуар, используйте /editor для редактирования.");
    Equipment_Update(playerid);
    return 1;
} */

SetPlayerAccessoriesStatusUse(playerid, slot_id, statusUse = 0, acc_slot = -1)
{
    if(acc_slot == -1 && IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][slot_id][inv_acc_slot]))
        RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][slot_id][inv_acc_slot]);

    InventoryPlayer[playerid][slot_id][inv_status_use] = statusUse;
    InventoryPlayer[playerid][slot_id][inv_acc_slot] = acc_slot;

    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `status_use` = %d, `acc_slot` = %d WHERE `mysql_id` = %d",
        statusUse, acc_slot, InventoryPlayer[playerid][slot_id][inv_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

AttachPlayerAccessories(playerid, slot_id, forplayerid = INVALID_PLAYER_ID, slot_use = -1, whence = -1)
{
    if(p_temp[playerid][Work_ID] > NONE_WORK)
    {
        InventoryPlayer[playerid][slot_id][inv_status_use] = 0;
        SendError(playerid, "Вы не закончили рабочий день на прошлой работе.");
        return 0;
    }
    if(p_temp[playerid][rob_house_idx] != -1 || p_temp[playerid][rob_bank_idx] != -1 || p_temp[playerid][rob_fuel_idx] != -1)
    {
        InventoryPlayer[playerid][slot_id][inv_status_use] = 0;
        SendError(playerid, "Вы не закончили ограбление дома, банка или АЗС.");
        return 0;
    }

    if(slot_use == -1) slot_use = GetPlayerFreeSlotUseAccSlot(playerid);
    if(slot_use == -1)
    {
        InventoryPlayer[playerid][slot_id][inv_status_use] = 0;
        SendError(playerid, "Свободных слотов для акссесуара нет.");
        return 0;
    }

    new statusUse = InventoryPlayer[playerid][slot_id][inv_status_use];
    if(statusUse == 1)
    {
        new type_acc = ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iAccessoriesType]-1,
            skin_idx = GetPlayerSkin(playerid);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accessories_coords` WHERE `type` = %d AND `skin_id` = %d LIMIT 1", type_acc, skin_idx);
        mysql_pquery(con_bd, STRING_GLOBAL, "AttachPlayerAccessoriesCallback", "dddddd",
            playerid, p_info[playerid][ID], slot_id, forplayerid, slot_use, whence);

        //printf(STRING_GLOBAL);
    }
    if(statusUse == 2)
    {
        new Float:fOffsetX = InventoryPlayer[playerid][slot_id][inv_acc_pos][0], Float:fOffsetY = InventoryPlayer[playerid][slot_id][inv_acc_pos][1], Float:fOffsetZ = InventoryPlayer[playerid][slot_id][inv_acc_pos][2],
            Float:fRotX = InventoryPlayer[playerid][slot_id][inv_acc_pos][3], Float:fRotY = InventoryPlayer[playerid][slot_id][inv_acc_pos][4], Float:fRotZ = InventoryPlayer[playerid][slot_id][inv_acc_pos][5],
            Float:fScaleX = InventoryPlayer[playerid][slot_id][inv_acc_pos][6], Float:fScaleY = InventoryPlayer[playerid][slot_id][inv_acc_pos][7], Float:fScaleZ = InventoryPlayer[playerid][slot_id][inv_acc_pos][8];

        AttachPlayerAccessories_Final(playerid, slot_id, forplayerid, slot_use, whence, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
    }
    return 1;
}

forward AttachPlayerAccessoriesCallback(playerid, accounts_ID, slot_id, forplayerid, slot_use, whence);
public AttachPlayerAccessoriesCallback(playerid, accounts_ID, slot_id, forplayerid, slot_use, whence)
{
    if(p_info[playerid][ID] != accounts_ID)
        return 1;
    if(!cache_num_rows())
    {
        DeletePVar(playerid, #EQ_TEMP_SLOT);

        InventoryPlayer[playerid][slot_id][inv_status_use] = 0;
        if(IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][slot_id][inv_acc_slot]))
            RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][slot_id][inv_acc_slot]);
        SendError(playerid, "Вы не можете надеть данный аксессуар, он не подходит под ваш скин.");
        return 1;
    }

    new Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
        Float:fRotX, Float:fRotY, Float:fRotZ,
        Float:fScaleX, Float:fScaleY, Float:fScaleZ;

    cache_get_value_name_float(0, "fOffsetX", fOffsetX);
    cache_get_value_name_float(0, "fOffsetY", fOffsetY);
    cache_get_value_name_float(0, "fOffsetZ", fOffsetZ);

    cache_get_value_name_float(0, "fRotX", fRotX);
    cache_get_value_name_float(0, "fRotY", fRotY);
    cache_get_value_name_float(0, "fRotZ", fRotZ);

    cache_get_value_name_float(0, "fScaleX", fScaleX);
    cache_get_value_name_float(0, "fScaleY", fScaleY);
    cache_get_value_name_float(0, "fScaleZ", fScaleZ);

    AttachPlayerAccessories_Final(playerid, slot_id, forplayerid, slot_use, whence, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
    return 1;
}

AttachPlayerAccessories_Final(playerid, slot_id, forplayerid, slot_use, whence, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
    new statusUse = InventoryPlayer[playerid][slot_id][inv_status_use],
        accID = InventoryPlayer[playerid][slot_id][inv_item_id],
        mc1 = InventoryPlayer[playerid][slot_id][inv_acc_mt][0],
        mc2 = InventoryPlayer[playerid][slot_id][inv_acc_mt][1],
        model = ItemsInfo[accID][iModel],
        bone = ItemsInfo[accID][iAccessoriesBone];

    if(model < 0 || bone < 0 || accID < 0)
        printf("CRASH_DETECT: %s | typeAcc: %d / model: %d / bone: %d / accID: %d",
            get_name(playerid), model, bone, accID);

    new costume_id = GetPlayerAttachedCostume(playerid);
    if(costume_id != -1)
        TakePlayerAttachedCostume(playerid, costume_id, true);

    SetPlayerAttachedObject(playerid, slot_use, model, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, AccessoriesColorInfo[mc1][acColorRBG], AccessoriesColorInfo[mc2][acColorRBG]);
    SetPlayerAccessoriesStatusUse(playerid, slot_id, statusUse, slot_use);

    if(forplayerid != INVALID_PLAYER_ID && !p_info[forplayerid][p_settings][ACC_VISIBLE])
        RemoveAttachedObjectForPlayer(playerid, forplayerid, slot_use);
    else
    {
        foreach(new targetid: PlayerPlayersStream[playerid])
        {
            if(!p_info[targetid][p_settings][ACC_VISIBLE])
                RemoveAttachedObjectForPlayer(playerid, targetid, slot_use);
        }
    }

    if(whence > 0)
    {
        SendAccess(playerid, "Вы надели аксессуар, используйте /editor для редактирования.");

        new temp_slot = GetPVarInt(playerid, #EQ_TEMP_SLOT)-1;
        DeletePVar(playerid, #EQ_TEMP_SLOT);

        if(temp_slot != -1 && ((slot_id != temp_slot && whence == 1) || (whence == 2)))
        {
            InventoryPlayer[playerid][temp_slot][inv_status_use] = 0;
            InventoryPlayer[playerid][temp_slot][inv_acc_slot] = -1;

            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `status_use` = 0, `acc_slot` = -1 WHERE `mysql_id` = %d",
                InventoryPlayer[playerid][temp_slot][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
        }
    }
    Equipment_AccessoriesUse(playerid);
    return 1;
}

AttachToPlayerAccOrCostume(playerid, forplayerid)
{
    if(GetPlayerAttachedCostume(playerid) != -1) SetPlayerAttachedCostume(playerid, GetPlayerAttachedCostume(playerid), false, forplayerid);
    else
    {
        for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
        {
            if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
                ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
                InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
            AttachPlayerAccessories(playerid, i, forplayerid, .slot_use = InventoryPlayer[playerid][i][inv_acc_slot]);
        }
    }
    return 1;
}

RemovePlayerAccessories(playerid, bool:save_remove)
{
    new bool:isMessage;
    if(save_remove)
    {
        for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
        {
            if( InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
                ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
                InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
            SetPlayerAccessoriesStatusUse(playerid, i);
            isMessage = true;
        }
    }
    else
    {
        for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
        {
            if( InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
                ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
                InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
            if(IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][i][inv_acc_slot]))
                RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][i][inv_acc_slot]);
        }
    }
    if(isMessage && save_remove) SendAccess(playerid, "С Вас сняты все аксессуары.");
    return 1;
}

PlayPlayerBoomBoxOrColumn(playerid, type)
{
    new bool:bCheck = false;
    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if(ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
            InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
            InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
        if(InventoryPlayer[playerid][i][inv_item_id] != 487+type) continue;
        bCheck = true;
        break;
    }
    if(!bCheck)
        return SendError(playerid, "У Вас нет аксессуара \"%s\", либо он не используется.", type == 0 ? ("Колонка") : ("Бумбокс"));

    if(AntiDMZone(playerid))
        return SendError(playerid, "Не возможно установить в Зеленой Зоне");
    if(p_temp[playerid][music_area] != -1)
        return SendError(playerid, "Вы уже установили музыкальный проигрыватель, теперь включите его.");

    new Float:BBCoord[4];
    GetPlayerPos(playerid, BBCoord[0], BBCoord[1], BBCoord[2]);
    GetPlayerFacingAngle(playerid, BBCoord[3]);
    SetPVarFloat(playerid, "BBX", BBCoord[0]);
    SetPVarFloat(playerid, "BBY", BBCoord[1]);
    SetPVarFloat(playerid, "BBZ", BBCoord[2]);
    BBCoord[0] += (2 * floatsin(-BBCoord[3], degrees));
    BBCoord[1] += (2 * floatcos(-BBCoord[3], degrees));
    BBCoord[2] -= 1.0;
    foreach(new i:Player)
    {
        if(IsPlayerInDynamicArea(playerid, p_temp[i][music_area]))
            return SendError(playerid, "Вы не можете поставить музыкальный проигрыватель в этом месте.");
    }
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "поставил(-а) %s", type == 0 ? ("колонку") : ("бумбокс"));
    MeAction(playerid, STRING_GLOBAL);
    new object_idx[2] = {2102, 2226}, pInt = GetPlayerInterior(playerid), pWorld = GetPlayerVirtualWorld(playerid);
    p_temp[playerid][music_object] = CreateDynamicObject(object_idx[type], BBCoord[0], BBCoord[1], BBCoord[2], 0.0, 0.0, 0.0, pWorld,pInt);
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "%s\nУстановил(-а): %s", type == 0 ? ("Колонка") : ("Бумбокс"), get_name(playerid));
    p_temp[playerid][music_label] = CreateDynamic3DTextLabel(STRING_GLOBAL, -1, BBCoord[0], BBCoord[1], BBCoord[2]+0.5, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, pWorld, pInt);
    p_temp[playerid][music_area] = CreateDynamicSphere(BBCoord[0], BBCoord[1], BBCoord[2], 30.0, pWorld, pInt);
    UpdateAreaInfo(p_temp[playerid][music_area], TYPE_MUSIC, AREA_SUBTYPE_INVALID_ID, playerid);
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
    return 1;
}

PlayPlayerAirPods(playerid, audio_url[])
{
    new bool:bCheck = false;
    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if(ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
            InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
            InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
        if(!(387 <= InventoryPlayer[playerid][i][inv_item_id] <= 390)) continue;
        bCheck = true;
        break;
    }
    if(!bCheck) return SendError(playerid, "У Вас нет аксессуара наушники, либо он не используется.");
    SetPVarInt(playerid, "UseMusic", 1);
    PlayAudioStreamForPlayer(playerid, audio_url);
    return 1;
}

CheckPlayerAccessories(playerid)
{
    new bool:bIsUpdate = false;
    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if( InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
            ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
            InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
        if(InventoryPlayer[playerid][i][inv_acc_premium] == 1) continue;
        InventoryPlayer[playerid][i][inv_acc_wear] -= 0.2;
        if(InventoryPlayer[playerid][i][inv_acc_wear] <= 0.0)
        {
            bIsUpdate = true;
            InventoryPlayer[playerid][i][inv_acc_wear] = 0.0;
            SetPlayerAccessoriesStatusUse(playerid, i);
        }
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "UPDATE `inventory` SET `acc_wear` = %f WHERE `mysql_id` = %d",  InventoryPlayer[playerid][i][inv_acc_wear], InventoryPlayer[playerid][i][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL);
        if(bIsUpdate) SendInfo(playerid, "Аксессуар \"%s\" максимально испортился и был снят.", ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iName]);
    }
    Equipment_Update(playerid);
    if(bIsUpdate) SendInfo(playerid, "Чтобы отремонтировать аксессуар(-ы), отправляйтесь в мастерскую одежды.");
    return 1;
}

GetPriceRepairAccessories(idx, Float:amount)
{
    new Float:repair_price, acc_price = ItemsInfo[idx][iPrice];
    repair_price = ((100.0 - amount) / 0.2) * acc_price / 1000;
    return floatround(repair_price);
}

// person info - TD
Equipment_GetAccSlotUse(playerid, acc_slot)
{
    if(acc_slot == -1)
        return SendError(playerid, "Не известная ошибка 03.03.23 15:1");

    for(new i = MAX_ALL_EQUIPMENT-1; i != MAX_PLAYER_EQUIPMENT-1; i--)
    {
        if(ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE &&
            InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            InventoryPlayer[playerid][i][inv_acc_slot] == acc_slot &&
            InventoryPlayer[playerid][i][inv_status_use] > 0)
            return i;
    }

    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if(ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
            InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            InventoryPlayer[playerid][i][inv_acc_slot] == acc_slot &&
            InventoryPlayer[playerid][i][inv_status_use] > 0)
            return i;
    }
    return -1;
}

GetPlayerFreeSlotUseAccSlot(playerid)
{
    new array_sort[MAX_PLAYER_ATTACHED_OBJECTS], count;
    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if( InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
            InventoryPlayer[playerid][i][inv_acc_slot] == -1 ||
            ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES ||
            InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
        count = InventoryPlayer[playerid][i][inv_acc_slot];
        array_sort[count] = 1;
    }
    for(new i = MAX_PLAYER_ATTACHED_OBJECTS-1; i != -1; i--)
    {
        if(array_sort[i] == 1) continue;
        return i;
    }
    return -1;
}

PreviewShopAccessories(playerid)
{
    new skin_idx = GetPlayerSkin(playerid),
        iAccType = GetPVarInt(playerid, "SelectAccessoriesType");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accessories_coords` WHERE `type` = %d AND `skin_id` = %d LIMIT 1", iAccType, skin_idx);
    mysql_pquery(con_bd, STRING_GLOBAL, "AccessoriesCoords", "ddd", playerid, p_info[playerid][ID], 6);
    return 1;
}

forward AccessoriesCoords(playerid, accounts_ID, typeID);
public AccessoriesCoords(playerid, accounts_ID, typeID)
{
    if(p_info[playerid][ID] != accounts_ID)
        return 1;
    if(!cache_num_rows())
    {
        if(typeID == 6)
        {
            HideTextDrawForPlayer(playerid, TD_ID_SHOP);

            SetCameraBehindPlayer(playerid);
            if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
                RemovePlayerAttachedObject(playerid, 0);
            DeletePVar(playerid,"SelectAccessoriesType");
            p_temp[playerid][p_listitem_int] = -1;
            SendError(playerid, "В данной группе нет подходящего аксессуара для Вашего скина.");
        }
        return 1;
    }

    new Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ,
        Float:fRotX, Float:fRotY, Float:fRotZ,
        Float:fScaleX, Float:fScaleY, Float:fScaleZ;

    cache_get_value_name_float(0, "fOffsetX", fOffsetX);
    cache_get_value_name_float(0, "fOffsetY", fOffsetY);
    cache_get_value_name_float(0, "fOffsetZ", fOffsetZ);

    cache_get_value_name_float(0, "fRotX", fRotX);
    cache_get_value_name_float(0, "fRotY", fRotY);
    cache_get_value_name_float(0, "fRotZ", fRotZ);

    cache_get_value_name_float(0, "fScaleX", fScaleX);
    cache_get_value_name_float(0, "fScaleY", fScaleY);
    cache_get_value_name_float(0, "fScaleZ", fScaleZ);

    switch(typeID)
    {
        case 0:
            SetPlayerAttachedObject(playerid, 0, 19801, 2, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        case 1:
            SetPlayerAttachedObject(playerid, 1, 11745, 1, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        case 2:
            SetPlayerAttachedObject(playerid, 0, 19801, 2, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        case 3:
            SetPlayerAttachedObject(playerid, 1, 11745, 1, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        case 4:
            SetPlayerAttachedObject(playerid, 0, 19801, 2, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        case 5:
            SetPlayerAttachedObject(playerid, 1, 1650, 1, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
        case 6:
        {
            new idx = p_temp[playerid][p_listitem][p_temp[playerid][shop_id]],
                model = ItemsInfo[idx][iModel],
                bone = ItemsInfo[idx][iAccessoriesBone];

            if(IsPlayerAttachedObjectSlotUsed(playerid, 0)) RemovePlayerAttachedObject(playerid, 0);
            SetPlayerAttachedObject(playerid, 0, model, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%d$", ItemsInfo[idx][iPrice]);
            PlayerTextDrawSetString(playerid, PTD_Shop[playerid][10], STRING_GLOBAL);
        }
        case 7:
        {
            new slot_id = ObjectInfo[playerid][oID],
                statusUse = InventoryPlayer[playerid][slot_id][inv_status_use];

            if(statusUse == 1)
            {
                ObjectInfo[playerid][oOffsetX] = fOffsetX;
                ObjectInfo[playerid][oOffsetY] = fOffsetY;
                ObjectInfo[playerid][oOffsetZ] = fOffsetZ;
                ObjectInfo[playerid][oRotX] = fRotX;
                ObjectInfo[playerid][oRotY] = fRotY;
                ObjectInfo[playerid][oRotZ] = fRotZ;
                ObjectInfo[playerid][oScaleX] = fScaleX;
                ObjectInfo[playerid][oScaleY] = fScaleY;
                ObjectInfo[playerid][oScaleZ] = fScaleZ;
            }
            else
            {
                ObjectInfo[playerid][oOffsetX] = InventoryPlayer[playerid][slot_id][inv_acc_pos][0];
                ObjectInfo[playerid][oOffsetY] = InventoryPlayer[playerid][slot_id][inv_acc_pos][1];
                ObjectInfo[playerid][oOffsetZ] = InventoryPlayer[playerid][slot_id][inv_acc_pos][2];
                ObjectInfo[playerid][oRotX] = InventoryPlayer[playerid][slot_id][inv_acc_pos][3];
                ObjectInfo[playerid][oRotY] = InventoryPlayer[playerid][slot_id][inv_acc_pos][4];
                ObjectInfo[playerid][oRotZ] = InventoryPlayer[playerid][slot_id][inv_acc_pos][5];
                ObjectInfo[playerid][oScaleX] = InventoryPlayer[playerid][slot_id][inv_acc_pos][6];
                ObjectInfo[playerid][oScaleY] = InventoryPlayer[playerid][slot_id][inv_acc_pos][7];
                ObjectInfo[playerid][oScaleZ] = InventoryPlayer[playerid][slot_id][inv_acc_pos][8];
            }
            if((fScaleX + fScaleY + fScaleZ) / 3 <= 0.75) ObjectInfo[playerid][oBlockSize] = true;

            SetPVarFloat(playerid, #OI_OFFSET_X, fOffsetX);
            SetPVarFloat(playerid, #OI_OFFSET_Y, fOffsetY);
            SetPVarFloat(playerid, #OI_OFFSET_Z, fOffsetZ);

            SetPVarFloat(playerid, #OI_SCALE_X, fScaleX);

            GetPlayerFacingAngle(playerid, p_temp[playerid][camera_angle]);

            LoadPlayerTextDrawEditor(playerid);
            for(new i = 0; i < 127; i++)
                PlayerTextDrawShow(playerid, Editor_PTD[playerid][i]);

            p_temp[playerid][TextDrawEditor] = true;
            UpdatePlayerEditorInfo(playerid);

            SelectTextDraw(playerid, -11206401);
        
            SetCameraForPlayer(playerid, CAMERA_ID_FRONT, 2.5, 1.5);
        }
    }
    return 1;
}

CMD:coordtomysql(playerid)
{
    if(SRV_ID)
        return 1;
    SendDebug(playerid, "Стартуем..");
    new count;
    for(new i = 0; i < MAX_ACCESSORIES_TYPE; i++)
    {
        for(new j = 0; j < 312; j++)
        {
            if(AccessoriesCoords_OLD[i][j][0] == 0.0 &&
                AccessoriesCoords_OLD[i][j][1] == 0.0 &&
                AccessoriesCoords_OLD[i][j][2] == 0.0 &&
                AccessoriesCoords_OLD[i][j][3] == 0.0 &&
                AccessoriesCoords_OLD[i][j][4] == 0.0 &&
                AccessoriesCoords_OLD[i][j][5] == 0.0)
                continue;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
                INSERT INTO `accessories_coords` (`type`, `skin_id`, \
                `fOffsetX`, `fOffsetY`, `fOffsetZ`, `fRotX`, `fRotY`, `fRotZ`, `fScaleX`, `fScaleY`, `fScaleZ`) \
                VALUES (%d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f)",
                i, j,
                AccessoriesCoords_OLD[i][j][0],AccessoriesCoords_OLD[i][j][1],AccessoriesCoords_OLD[i][j][2],
                AccessoriesCoords_OLD[i][j][3],AccessoriesCoords_OLD[i][j][4],AccessoriesCoords_OLD[i][j][5],
                AccessoriesCoords_OLD[i][j][6],AccessoriesCoords_OLD[i][j][7],AccessoriesCoords_OLD[i][j][8]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            count++;
        }
    }
    SendDebug(playerid, "Всего создано %d записей с координатами акссесуаров.", count);
    return 1;
}

