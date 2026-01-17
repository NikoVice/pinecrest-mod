new PlayerText:Editor_PTD[MAX_PLAYERS][127];

enum
{
    EDITOR_HIDE_CANCEL,
    EDITOR_HIDE_SAVE
}

enum E_OBJECT_INFO
{
    oID,
    oSlot,
    oModel,
    oBone,
    Float:oOffsetX,
    Float:oOffsetY,
    Float:oOffsetZ,
    Float:oRotX,
    Float:oRotY,
    Float:oRotZ,
    Float:oScaleX,
    Float:oScaleY,
    Float:oScaleZ,
    Float:oStep,
    oMaterialColor1,
    oMaterialColor2,
    bool:oBlockSize
};

new ObjectInfo[MAX_PLAYERS][E_OBJECT_INFO];

ClearObjectInfo(playerid)
{
    ObjectInfo[playerid][oID] = 0;
    ObjectInfo[playerid][oSlot] = 0;
    ObjectInfo[playerid][oModel] = 0;
    ObjectInfo[playerid][oBone] = 1;
    ObjectInfo[playerid][oOffsetX] = 0.0;
    ObjectInfo[playerid][oOffsetY] = 0.0;
    ObjectInfo[playerid][oOffsetZ] = 0.0;
    ObjectInfo[playerid][oRotX] = 0.0;
    ObjectInfo[playerid][oRotY] = 0.0;
    ObjectInfo[playerid][oRotZ] = 0.0;
    ObjectInfo[playerid][oScaleX] = 1.0;
    ObjectInfo[playerid][oScaleY] = 1.0;
    ObjectInfo[playerid][oScaleZ] = 1.0;
    ObjectInfo[playerid][oMaterialColor1] = 0;
    ObjectInfo[playerid][oMaterialColor2] = 0;
    ObjectInfo[playerid][oStep] = 0.02;
    ObjectInfo[playerid][oBlockSize] = false;

    DeletePVar(playerid, #OI_OFFSET_X);
    DeletePVar(playerid, #OI_OFFSET_Y);
    DeletePVar(playerid, #OI_OFFSET_Z);

    DeletePVar(playerid, #OI_SCALE_X);
    return 1;
}

enum
{
    TYPE_UPDATE_CAMERA_INVALID,
    TYPE_UPDATE_CAMERA_LEFT,
    TYPE_UPDATE_CAMERA_RIGHT,
    
}

enum
{
    TYPE_OFFSET_X,
    TYPE_OFFSET_Y,
    TYPE_OFFSET_Z,
    TYPE_ROT_X,
    TYPE_ROT_Y,
    TYPE_ROT_Z,
    TYPE_SCALE
}

ReturnPlayerAttachedObject(playerid, slot_id)
{
    for(new i = 8; i != -1; i--)
    {
        if(i >= 6) InventoryPlayer[playerid][slot_id][inv_acc_pos][i] = 1.0;
        else InventoryPlayer[playerid][slot_id][inv_acc_pos][i] = 0.0;
    }
    InventoryPlayer[playerid][slot_id][inv_status_use] = 1;

    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "UPDATE `inventory` SET `status_use` = 1, `acc_pos` = '0.0|0.0|0.0|0.0|0.0|0.0|1.0|1.0|1.0' WHERE `mysql_id` = %d",
        InventoryPlayer[playerid][slot_id][inv_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    AttachPlayerAccessories(playerid, slot_id, .slot_use = InventoryPlayer[playerid][slot_id][inv_acc_slot]);
    return 1;
}

this::ShowPlayerEditor(playerid, slot_id, slot_use)
{
	if(IsTDVisible(playerid) != -1)
		return 1;
	
	new itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        new type = ItemsInfo[itemID][iAccessoriesType]-1,
            skin_idx = GetPlayerSkin(playerid);

        ObjectInfo[playerid][oID] = slot_id;
        ObjectInfo[playerid][oSlot] = InventoryPlayer[playerid][slot_id][inv_acc_slot];
        if(ObjectInfo[playerid][oSlot] == -1)
            return SendError(playerid, "Обьект под редактирование не найден. Обратитесь на форум в раздел багов.");

        ObjectInfo[playerid][oModel] = ItemsInfo[itemID][iModel];
        ObjectInfo[playerid][oBone] = ItemsInfo[itemID][iAccessoriesBone];

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accessories_coords` WHERE `type` = %d AND `skin_id` = %d LIMIT 1", type, skin_idx);
        mysql_pquery(con_bd, STRING_GLOBAL, "AccessoriesCoords", "ddd", playerid, p_info[playerid][ID], 7);
        return 1;
    }
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            attach_slot = GetFreeSlotVehicleAttach(vehicleid);
        if(vehicleid != GetPVarInt(playerid, #VEHICLEID_ACCESSORIES))
            return SendError(playerid, "Произошла ошибка 03-04-23.");
        if(slot_use == -1)
        {
            if(GetFreeSlotVehicleAttach(vehicleid) == -1)
                return SendError(playerid, "Больше нет свободных слотов для деталей тюнинга.");
        }
        else attach_slot = slot_use;

        ObjectInfo[playerid][oID] = slot_id;
        ObjectInfo[playerid][oSlot] = attach_slot;
        ObjectInfo[playerid][oModel] = ItemsInfo[itemID][iModel];

        if(InventoryPlayer[playerid][slot_id][inv_acc_pos][2] == 0.0) 
            InventoryPlayer[playerid][slot_id][inv_acc_pos][2] = 1.0;

        ObjectInfo[playerid][oOffsetX] = InventoryPlayer[playerid][slot_id][inv_acc_pos][0];
        ObjectInfo[playerid][oOffsetY] = InventoryPlayer[playerid][slot_id][inv_acc_pos][1];
        ObjectInfo[playerid][oOffsetZ] = InventoryPlayer[playerid][slot_id][inv_acc_pos][2];
        ObjectInfo[playerid][oRotX] = InventoryPlayer[playerid][slot_id][inv_acc_pos][3];
        ObjectInfo[playerid][oRotY] = InventoryPlayer[playerid][slot_id][inv_acc_pos][4];
        ObjectInfo[playerid][oRotZ] = InventoryPlayer[playerid][slot_id][inv_acc_pos][5];

        if(veh_info[vehicleid][v_attach_object][attach_slot] != INVALID_OBJECT_ID)
            DestroyDynamicObject(veh_info[vehicleid][v_attach_object][attach_slot]);

        veh_info[vehicleid][v_attach_object][attach_slot] = CreateDynamicObject(ObjectInfo[playerid][oModel], 
            ObjectInfo[playerid][oOffsetX], ObjectInfo[playerid][oOffsetY] , ObjectInfo[playerid][oOffsetZ], 
            ObjectInfo[playerid][oRotX], ObjectInfo[playerid][oRotY], ObjectInfo[playerid][oRotZ]);

        AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][attach_slot], vehicleid,
            ObjectInfo[playerid][oOffsetX], ObjectInfo[playerid][oOffsetY] , ObjectInfo[playerid][oOffsetZ],
            ObjectInfo[playerid][oRotX], ObjectInfo[playerid][oRotY], ObjectInfo[playerid][oRotZ]);
        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

        GetPlayerFacingAngle(playerid, p_temp[playerid][camera_angle]);

        LoadPlayerTextDrawEditor(playerid);
        for(new i = 0; i < 127; i++)
        PlayerTextDrawShow(playerid, Editor_PTD[playerid][i]);

        p_temp[playerid][TextDrawEditor] = true;
        UpdatePlayerEditorInfo(playerid);

        SelectTextDraw(playerid, -11206401);
        SetCameraForPlayer(playerid, CAMERA_ID_FRONT_LEFT);
        return 1;
    }
    SendError(playerid, "Ошибка редактирования позиций, откройте редактор заново.");
    return 1;
}

UpdatePlayerAttachedObject(playerid, type, idx)
{
    new slot_id = ObjectInfo[playerid][oID],
        itemID = InventoryPlayer[playerid][slot_id][inv_item_id];

    if(ItemsInfo[itemID][iType] != TYPE_ITEMS_ACCESSORIES && ItemsInfo[itemID][iType] != TYPE_ITEMS_VEHICLE_TUNE)
         return SendError(playerid, "Ошибка редактирования позиций, откройте редактор заново.");

    new 
        Float:fOffsetX = GetPVarFloat(playerid, #OI_OFFSET_X),
        Float:fOffsetY = GetPVarFloat(playerid, #OI_OFFSET_Y),
        Float:fOffsetZ = GetPVarFloat(playerid, #OI_OFFSET_Z),
        Float:fScaleX = GetPVarFloat(playerid, #OI_SCALE_X),
        Float:limite_coord_X = ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES ? 0.500000 : 2.0,
        Float:limite_coord_Y = ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES ? 0.500000 : 3.5,
        Float:limite_coord_Z = ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES ? 0.500000 : 2.5;

    switch(idx)
    {
        case TYPE_OFFSET_X:
        {
            if(type == TYPE_UPDATE_CAMERA_LEFT)
            {
                if(ObjectInfo[playerid][oOffsetX] - ObjectInfo[playerid][oStep] < (fOffsetX - limite_coord_X)) return SendError(playerid, "Вы превысили лимит, можно еще %.4f.", ObjectInfo[playerid][oOffsetX] - (fOffsetX - limite_coord_X));
                ObjectInfo[playerid][oOffsetX] -= ObjectInfo[playerid][oStep];
            }
            else
            {
                if(ObjectInfo[playerid][oOffsetX] + ObjectInfo[playerid][oStep] > (fOffsetX + limite_coord_X)) return SendError(playerid, "Вы превысили лимит, можно еще %.4f.", (fOffsetX + limite_coord_X) - ObjectInfo[playerid][oOffsetX]);
                ObjectInfo[playerid][oOffsetX] += ObjectInfo[playerid][oStep];
            }
        }
        case TYPE_OFFSET_Y:
        {
            if(type == TYPE_UPDATE_CAMERA_LEFT)
            {
                if(ObjectInfo[playerid][oOffsetY] - ObjectInfo[playerid][oStep] < (fOffsetY - limite_coord_Y)) return SendError(playerid, "Вы превысили лимит, можно еще %.4f.", ObjectInfo[playerid][oOffsetY] - (fOffsetY - limite_coord_Y));
                ObjectInfo[playerid][oOffsetY] -= ObjectInfo[playerid][oStep];
            }
            else
            {
                if(ObjectInfo[playerid][oOffsetY] + ObjectInfo[playerid][oStep] > (fOffsetY + limite_coord_Y)) return SendError(playerid, "Вы превысили лимит, можно еще %.4f.", (fOffsetY + limite_coord_Y) - ObjectInfo[playerid][oOffsetY]);
                ObjectInfo[playerid][oOffsetY] += ObjectInfo[playerid][oStep];
            }
        }
        case TYPE_OFFSET_Z:
        {
            if(type == TYPE_UPDATE_CAMERA_LEFT)
            {
                if(ObjectInfo[playerid][oOffsetZ] - ObjectInfo[playerid][oStep] < (fOffsetZ - limite_coord_Z)) return SendError(playerid, "Вы превысили лимит, можно еще %.4f.", ObjectInfo[playerid][oOffsetZ] - (fOffsetZ - limite_coord_Z));
                ObjectInfo[playerid][oOffsetZ] -= ObjectInfo[playerid][oStep];
            }
            else
            {
                if(ObjectInfo[playerid][oOffsetZ] + ObjectInfo[playerid][oStep] > (fOffsetZ + limite_coord_Z)) return SendError(playerid, "Вы превысили лимит, можно еще %.4f.", (fOffsetZ + limite_coord_Z) - ObjectInfo[playerid][oOffsetZ]);
                ObjectInfo[playerid][oOffsetZ] += ObjectInfo[playerid][oStep];
            }
        }
        case TYPE_ROT_X:
        {
            if(type == TYPE_UPDATE_CAMERA_LEFT)
            {
                ObjectInfo[playerid][oRotX] -= ObjectInfo[playerid][oStep];
                if(ObjectInfo[playerid][oRotX] < 0.0) ObjectInfo[playerid][oRotX] += 360.0;
            }
            else
            {
                ObjectInfo[playerid][oRotX] += ObjectInfo[playerid][oStep];
                if(ObjectInfo[playerid][oRotX] > 360.0) ObjectInfo[playerid][oRotX] -= 360.0;
            }
        }
        case TYPE_ROT_Y:
        {
            if(type == TYPE_UPDATE_CAMERA_LEFT)
            {
                ObjectInfo[playerid][oRotY] -= ObjectInfo[playerid][oStep];
                if(ObjectInfo[playerid][oRotY] < 0.0) ObjectInfo[playerid][oRotY] += 360.0;
            }
            else
            {
                ObjectInfo[playerid][oRotY] += ObjectInfo[playerid][oStep];
                if(ObjectInfo[playerid][oRotY] > 360.0) ObjectInfo[playerid][oRotY] -= 360.0;
            }
        }
        case TYPE_ROT_Z:
        {
            if(type == TYPE_UPDATE_CAMERA_LEFT)
            {
                ObjectInfo[playerid][oRotZ] -= ObjectInfo[playerid][oStep];
                if(ObjectInfo[playerid][oRotZ] < 0.0) ObjectInfo[playerid][oRotZ] += 360.0;
            }
            else
            {
                ObjectInfo[playerid][oRotZ] += ObjectInfo[playerid][oStep];
                if(ObjectInfo[playerid][oRotZ] > 360.0) ObjectInfo[playerid][oRotZ] -= 360.0;
            }
        }
        case TYPE_SCALE:
        {
            if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
            {
                if(SRV_ID && ObjectInfo[playerid][oBlockSize] == true) return SendError(playerid, "На данном аксессуаре нельзя редактировать размер.");
                if(type == TYPE_UPDATE_CAMERA_LEFT)
                {
                    if(SRV_ID && ObjectInfo[playerid][oScaleX] - ObjectInfo[playerid][oStep] < (fScaleX - 0.500000)) return SendError(playerid, "Вы превысили лимит, можно %.4f.", ObjectInfo[playerid][oScaleX] - (fScaleX - 0.500000));
                    ObjectInfo[playerid][oScaleX] -= ObjectInfo[playerid][oStep];
                    ObjectInfo[playerid][oScaleY] -= ObjectInfo[playerid][oStep];
                    ObjectInfo[playerid][oScaleZ] -= ObjectInfo[playerid][oStep];
                }
                else
                {
                    if(SRV_ID && ObjectInfo[playerid][oScaleX] + ObjectInfo[playerid][oStep] > (fScaleX + 0.500000)) return SendError(playerid, "Вы превысили лимит, можно %.4f.", (fScaleX + 0.500000) - ObjectInfo[playerid][oScaleX]);
                    ObjectInfo[playerid][oScaleX] += ObjectInfo[playerid][oStep];
                    ObjectInfo[playerid][oScaleY] += ObjectInfo[playerid][oStep];
                    ObjectInfo[playerid][oScaleZ] += ObjectInfo[playerid][oStep];
                }
            }
        }
    }

    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        new atype = ItemsInfo[itemID][iAccessoriesType]-1,
            idx_skin = GetPlayerSkin(playerid);
        if(slot_id < 0 || itemID < 0 || atype < 0 || idx_skin < 0)
            printf("CRASH_DETECT: %s | slot_id: %d / item_id %d / atype: %d / idx_skin %d",
                get_name(playerid), slot_id, itemID, atype, idx_skin);

        SetPlayerAttachedObject(playerid,
            ObjectInfo[playerid][oSlot], ObjectInfo[playerid][oModel], ObjectInfo[playerid][oBone],
            ObjectInfo[playerid][oOffsetX], ObjectInfo[playerid][oOffsetY], ObjectInfo[playerid][oOffsetZ],
            ObjectInfo[playerid][oRotX], ObjectInfo[playerid][oRotY], ObjectInfo[playerid][oRotZ],
            ObjectInfo[playerid][oScaleX], ObjectInfo[playerid][oScaleY], ObjectInfo[playerid][oScaleZ],
            AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acColorRBG],
            AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acColorRBG]);
    }

    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            attach_slot = ObjectInfo[playerid][oSlot];
        AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][attach_slot], vehicleid,
            ObjectInfo[playerid][oOffsetX], ObjectInfo[playerid][oOffsetY] , ObjectInfo[playerid][oOffsetZ],
            ObjectInfo[playerid][oRotX], ObjectInfo[playerid][oRotY], ObjectInfo[playerid][oRotZ]);
        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
    }
    UpdatePlayerEditorInfo(playerid);
    return 1;
}

CMD:editor(playerid, params[])
{
    ShowPlayerDialog(playerid, D_EDITOR_MENU, DIALOG_STYLE_LIST, ""I"Редактор объектов", ""I"[1]"W" Список аксессуаров\n"I"[2]"W" Информация", "Далее", "Отмена");
    return 1;
}

UpdatePlayerEditorInfo(playerid)
{
    if(p_temp[playerid][TextDrawEditor] == false) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента."), HidePlayerEditor(playerid, EDITOR_HIDE_CANCEL);

    new str[64];
    format(str, sizeof(str), "X: %.4f", ObjectInfo[playerid][oOffsetX]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][78], str);
    format(str, sizeof(str), "Y: %.4f", ObjectInfo[playerid][oOffsetY]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][64], str);
    format(str, sizeof(str), "Z: %.4f", ObjectInfo[playerid][oOffsetZ]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][92], str);
    format(str, sizeof(str), "RX: %.4f", ObjectInfo[playerid][oRotX]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][43], str);
    format(str, sizeof(str), "RY: %.4f", ObjectInfo[playerid][oRotY]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][29], str);
    format(str, sizeof(str), "RZ: %.4f", ObjectInfo[playerid][oRotZ]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][15], str);
    format(str, sizeof(str), "SIZE: %.4f", (ObjectInfo[playerid][oScaleX] + ObjectInfo[playerid][oScaleY] + ObjectInfo[playerid][oScaleZ]) / 3);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][1], str);
    format(str, sizeof(str), "STEP: %.4f", ObjectInfo[playerid][oStep]);
    PlayerTextDrawSetString(playerid, Editor_PTD[playerid][116], str);
    return 1;
}

HidePlayerEditor(playerid, type)
{
    new slot_id = ObjectInfo[playerid][oID],
        itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    if(type == EDITOR_HIDE_SAVE)
    {
        InventoryPlayer[playerid][slot_id][inv_acc_pos][0] = ObjectInfo[playerid][oOffsetX];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][1] = ObjectInfo[playerid][oOffsetY];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][2] = ObjectInfo[playerid][oOffsetZ];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][3] = ObjectInfo[playerid][oRotX];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][4] = ObjectInfo[playerid][oRotY];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][5] = ObjectInfo[playerid][oRotZ];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][6] = ObjectInfo[playerid][oScaleX];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][7] = ObjectInfo[playerid][oScaleY];
        InventoryPlayer[playerid][slot_id][inv_acc_pos][8] = ObjectInfo[playerid][oScaleZ];

        InventoryPlayer[playerid][slot_id][inv_status_use] = 2;

        if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "UPDATE `inventory` SET `status_use` = %d, `acc_pos` = '%f|%f|%f|%f|%f|%f|%f|%f|%f' WHERE `mysql_id` = %d",
                InventoryPlayer[playerid][slot_id][inv_status_use],
                InventoryPlayer[playerid][slot_id][inv_acc_pos][0], InventoryPlayer[playerid][slot_id][inv_acc_pos][1], InventoryPlayer[playerid][slot_id][inv_acc_pos][2],
                InventoryPlayer[playerid][slot_id][inv_acc_pos][3], InventoryPlayer[playerid][slot_id][inv_acc_pos][4], InventoryPlayer[playerid][slot_id][inv_acc_pos][5],
                InventoryPlayer[playerid][slot_id][inv_acc_pos][6], InventoryPlayer[playerid][slot_id][inv_acc_pos][7], InventoryPlayer[playerid][slot_id][inv_acc_pos][8],
                InventoryPlayer[playerid][slot_id][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
        {
            new vehicleid = GetPlayerVehicleID(playerid),
                old_slot_id = ObjectInfo[playerid][oID],
                new_slot_id = GetPVarInt(playerid, #EQ_TEMP_SLOT)-1,
                slot_use = ObjectInfo[playerid][oSlot];
            if(vehicleid != GetPVarInt(playerid, #VEHICLEID_ACCESSORIES))
                return 1;
            if(new_slot_id != -1)
            {
                DeletePVar(playerid, #EQ_TEMP_SLOT);
                //LOGIC: снимаем акс и выставляем на место того что одеваем
                Equipment_SlotChangePos(playerid, old_slot_id, new_slot_id);

                InventoryPlayer[playerid][old_slot_id][inv_acc_slot]      = -1;
                InventoryPlayer[playerid][old_slot_id][inv_status_use]    = 0;

                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
                    "UPDATE `inventory` SET `owner_id` = %d, `owner_type` = %d, `slot_id` = %d, `acc_slot` = %d, `status_use` = %d, `acc_pos` = '%f|%f|%f|%f|%f|%f|%f|%f|%f' WHERE `mysql_id` = %d",
                        p_info[playerid][ID], INVENTORY_OWNER_TYPE_PLAYER, InventoryPlayer[playerid][old_slot_id][inv_slot_id],
                        InventoryPlayer[playerid][old_slot_id][inv_acc_slot], InventoryPlayer[playerid][old_slot_id][inv_status_use],
                        InventoryPlayer[playerid][old_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][2],
                        InventoryPlayer[playerid][old_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][5],
                        InventoryPlayer[playerid][old_slot_id][inv_acc_pos][6], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][7], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][8],
                        InventoryPlayer[playerid][old_slot_id][inv_mysql_id]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
            else new_slot_id = slot_id;

            SendDebug(playerid, "(%d, %d, %f, %f, %f, %f, %f, %f),", GetVehicleModelEx(vehicleid), ItemsInfo[itemID][iModel], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][2], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][5]);

            InventoryPlayer[playerid][new_slot_id][inv_acc_slot] = slot_use;

            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "UPDATE `inventory` SET `owner_id` = %d, `owner_type` = %d, `slot_id` = %d, `acc_slot` = %d, `status_use` = %d, `acc_pos` = '%f|%f|%f|%f|%f|%f|%f|%f|%f' WHERE `mysql_id` = %d",
                veh_info[vehicleid][v_mysql_id], INVENTORY_OWNER_TYPE_VEHICLE, InventoryPlayer[playerid][new_slot_id][inv_slot_id],
                InventoryPlayer[playerid][new_slot_id][inv_acc_slot], InventoryPlayer[playerid][new_slot_id][inv_status_use],
                InventoryPlayer[playerid][new_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][2],
                InventoryPlayer[playerid][new_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][5],
                InventoryPlayer[playerid][new_slot_id][inv_acc_pos][6], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][7], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][8],
                InventoryPlayer[playerid][new_slot_id][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            Equipment_ClearSlot(playerid, new_slot_id);

            ShowTextDraw_Speedometr(playerid, true);

            DeletePVar(playerid, #VEHICLEID_ACCESSORIES);

            for(new i = MAX_PLAYER_EQUIPMENT; i < MAX_ALL_EQUIPMENT; i++)
            {
                Equipment_ClearSlot(playerid, i);
            }
        }
        SendAccess(playerid, "Вы установили позицию аксессуара %s.", ItemsInfo[itemID][iName]);
    }
    else 
    {
        new itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
        if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
        {
            AttachPlayerAccessories(playerid, slot_id, .slot_use = InventoryPlayer[playerid][slot_id][inv_acc_slot]);
        }
        else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
        {
            new vehicleid = GetPlayerVehicleID(playerid);

            new attach_slot = ObjectInfo[playerid][oSlot];
            DestroyDynamicObject(veh_info[vehicleid][v_attach_object][attach_slot]);
            veh_info[vehicleid][v_attach_object][attach_slot] = INVALID_OBJECT_ID;

            if(InventoryPlayer[playerid][slot_id][inv_status_use] == 2)
            {
                veh_info[vehicleid][v_attach_object][attach_slot] = CreateDynamicObject(ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iModel], 
                InventoryPlayer[playerid][slot_id][inv_acc_pos][0], InventoryPlayer[playerid][slot_id][inv_acc_pos][1], InventoryPlayer[playerid][slot_id][inv_acc_pos][2], 
                InventoryPlayer[playerid][slot_id][inv_acc_pos][3], InventoryPlayer[playerid][slot_id][inv_acc_pos][4], InventoryPlayer[playerid][slot_id][inv_acc_pos][5]);

                AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][attach_slot], vehicleid,
                    InventoryPlayer[playerid][slot_id][inv_acc_pos][0], InventoryPlayer[playerid][slot_id][inv_acc_pos][1], InventoryPlayer[playerid][slot_id][inv_acc_pos][2],
                    InventoryPlayer[playerid][slot_id][inv_acc_pos][3], InventoryPlayer[playerid][slot_id][inv_acc_pos][4], InventoryPlayer[playerid][slot_id][inv_acc_pos][5]);
            }
            Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

            DeletePVar(playerid, #VEHICLEID_ACCESSORIES);

            for(new i = MAX_PLAYER_EQUIPMENT; i < MAX_ALL_EQUIPMENT; i++)
            {
                Equipment_ClearSlot(playerid, i);
            }
        }
    }

    for(new i = 0; i < 127; i++)
    {
        if(Editor_PTD[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, Editor_PTD[playerid][i]);
            Editor_PTD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
    }
    ClearObjectInfo(playerid);
    p_temp[playerid][camera_angle] = 0.0;
    CancelSelectTextDraw(playerid);
    SetCameraBehindPlayer(playerid);

    p_temp[playerid][TextDrawEditor] = false;
    return 1;
}

LoadPlayerTextDrawEditor(playerid)
{
    Editor_PTD[playerid][0] = CreatePlayerTextDraw(playerid, 500.3330, 318.6776, "Box"); // size
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][0], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][0], 600.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][0], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][0], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][0], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][0], 0);

    Editor_PTD[playerid][1] = CreatePlayerTextDraw(playerid, 549.9998, 327.3034, "SIZE:_0.00"); // size
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][1], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][1], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][1], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][1], 0);

    Editor_PTD[playerid][2] = CreatePlayerTextDraw(playerid, 484.4664, 315.1181, "LD_Beat:chit"); // size left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][2], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][2], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][2], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][2], 0);

    Editor_PTD[playerid][3] = CreatePlayerTextDraw(playerid, 490.3330, 316.9776, "LD_SPAC:white"); // size left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][3], 23.3099, 33.2098);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][3], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][3], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][3], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][3], 0);

    Editor_PTD[playerid][4] = CreatePlayerTextDraw(playerid, 486.3330, 322.1177, "LD_SPAC:white"); // size left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][4], 23.0000, 28.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][4], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][4], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][4], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][4], 0);

    Editor_PTD[playerid][5] = CreatePlayerTextDraw(playerid, 463.3330, 296.8663, ""); // size left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][5], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][5], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][5], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][5], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][5], 0x00000000);

    Editor_PTD[playerid][6] = CreatePlayerTextDraw(playerid, 496.3330, 331.9107, "LD_SPAC:white"); // size left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][6], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][6], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][6], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][6], 0);

    Editor_PTD[playerid][7] = CreatePlayerTextDraw(playerid, 499.9999, 318.5924, "Box"); // size left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][7], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][7], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][7], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][7], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][7], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][7], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][7], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][7], true);

    Editor_PTD[playerid][8] = CreatePlayerTextDraw(playerid, 608.6334, 340.3218, "LD_Beat:chit"); // size right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][8], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][8], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][8], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][8], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][8], 0);

    Editor_PTD[playerid][9] = CreatePlayerTextDraw(playerid, 593.6666, 316.9776, "LD_SPAC:white"); // size right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][9], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][9], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][9], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][9], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][9], 0);

    Editor_PTD[playerid][10] = CreatePlayerTextDraw(playerid, 589.6666, 317.2174, "LD_SPAC:white"); // size right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][10], 24.0000, 32.9598);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][10], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][10], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][10], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][10], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][10], 0);

    Editor_PTD[playerid][11] = CreatePlayerTextDraw(playerid, 578.6666, 296.8663, ""); // size right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][11], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][11], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][11], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][11], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][11], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][11], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][11], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][11], 0x00000000);

    Editor_PTD[playerid][12] = CreatePlayerTextDraw(playerid, 594.9998, 331.9107, "LD_SPAC:white"); // size right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][12], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][12], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][12], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][12], 0);

    Editor_PTD[playerid][13] = CreatePlayerTextDraw(playerid, 603.3331, 318.5924, "Box"); // size right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][13], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][13], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][13], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][13], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][13], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][13], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][13], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][13], true);

    Editor_PTD[playerid][14] = CreatePlayerTextDraw(playerid, 500.3330, 273.8778, "Box"); // rz
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][14], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][14], 600.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][14], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][14], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][14], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][14], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][14], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][14], 0);

    Editor_PTD[playerid][15] = CreatePlayerTextDraw(playerid, 549.9998, 282.5038, "RZ:_0.00"); // rz
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][15], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][15], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][15], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][15], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][15], 0);

    Editor_PTD[playerid][16] = CreatePlayerTextDraw(playerid, 486.3330, 276.9554, "LD_SPAC:white"); // rz left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][16], 24.0000, 28.7299);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][16], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][16], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][16], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][16], 0);

    Editor_PTD[playerid][17] = CreatePlayerTextDraw(playerid, 484.4664, 270.3185, "LD_Beat:chit"); // rz left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][17], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][17], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][17], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][17], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][17], 0);

    Editor_PTD[playerid][18] = CreatePlayerTextDraw(playerid, 490.3330, 272.1777, "LD_SPAC:white"); // rz left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][18], 23.0000, 33.2397);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][18], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][18], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][18], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][18], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][18], 0);

    Editor_PTD[playerid][19] = CreatePlayerTextDraw(playerid, 463.3330, 252.0664, ""); // rz left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][19], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][19], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][19], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][19], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][19], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][19], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][19], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][19], 0x00000000);

    Editor_PTD[playerid][20] = CreatePlayerTextDraw(playerid, 496.3330, 287.1111, "LD_SPAC:white"); // rz left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][20], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][20], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][20], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][20], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][20], 0);

    Editor_PTD[playerid][21] = CreatePlayerTextDraw(playerid, 499.9999, 273.7926, "Box"); // rz left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][21], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][21], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][21], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][21], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][21], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][21], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][21], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][21], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][21], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][21], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][21], true);

    Editor_PTD[playerid][22] = CreatePlayerTextDraw(playerid, 589.6666, 272.1550, "LD_SPAC:white"); // rz right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][22], 24.0000, 33.4799);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][22], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][22], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][22], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][22], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][22], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][22], 0);

    Editor_PTD[playerid][23] = CreatePlayerTextDraw(playerid, 608.6334, 295.5220, "LD_Beat:chit"); // rz right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][23], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][23], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][23], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][23], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][23], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][23], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][23], 0);

    Editor_PTD[playerid][24] = CreatePlayerTextDraw(playerid, 593.6666, 272.1777, "LD_SPAC:white"); // rz right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][24], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][24], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][24], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][24], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][24], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][24], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][24], 0);

    Editor_PTD[playerid][25] = CreatePlayerTextDraw(playerid, 578.6666, 252.0664, ""); // rz right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][25], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][25], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][25], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][25], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][25], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][25], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][25], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][25], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][25], 0x00000000);

    Editor_PTD[playerid][26] = CreatePlayerTextDraw(playerid, 594.9998, 287.1111, "LD_SPAC:white"); // rz right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][26], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][26], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][26], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][26], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][26], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][26], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][26], 0);

    Editor_PTD[playerid][27] = CreatePlayerTextDraw(playerid, 603.3331, 273.7926, "Box"); // rz right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][27], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][27], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][27], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][27], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][27], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][27], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][27], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][27], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][27], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][27], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][27], true);

    Editor_PTD[playerid][28] = CreatePlayerTextDraw(playerid, 500.3330, 229.4924, "Box"); // ry
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][28], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][28], 601.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][28], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][28], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][28], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][28], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][28], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][28], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][28], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][28], 0);

    Editor_PTD[playerid][29] = CreatePlayerTextDraw(playerid, 549.9998, 238.1183, "RY:_0.00"); // ry
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][29], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][29], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][29], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][29], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][29], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][29], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][29], 0);

    Editor_PTD[playerid][30] = CreatePlayerTextDraw(playerid, 486.3330, 232.5700, "LD_SPAC:white"); // ry left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][30], 24.0000, 28.3798);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][30], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][30], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][30], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][30], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][30], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][30], 0);

    Editor_PTD[playerid][31] = CreatePlayerTextDraw(playerid, 484.4664, 225.9331, "LD_Beat:chit"); // ry left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][31], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][31], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][31], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][31], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][31], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][31], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][31], 0);

    Editor_PTD[playerid][32] = CreatePlayerTextDraw(playerid, 490.3330, 227.7924, "LD_SPAC:white"); // ry left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][32], 23.1100, 33.2196);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][32], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][32], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][32], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][32], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][32], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][32], 0);

    Editor_PTD[playerid][33] = CreatePlayerTextDraw(playerid, 463.3330, 207.6813, ""); // ry left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][33], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][33], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][33], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][33], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][33], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][33], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][33], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][33], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][33], 0x00000000);

    Editor_PTD[playerid][34] = CreatePlayerTextDraw(playerid, 496.3330, 242.7256, "LD_SPAC:white"); // ry left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][34], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][34], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][34], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][34], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][34], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][34], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][34], 0);

    Editor_PTD[playerid][35] = CreatePlayerTextDraw(playerid, 499.9999, 229.4073, "Box"); // ry left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][35], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][35], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][35], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][35], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][35], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][35], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][35], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][35], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][35], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][35], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][35], true);

    Editor_PTD[playerid][36] = CreatePlayerTextDraw(playerid, 608.6334, 251.1365, "LD_Beat:chit"); // ry right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][36], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][36], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][36], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][36], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][36], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][36], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][36], 0);

    Editor_PTD[playerid][37] = CreatePlayerTextDraw(playerid, 593.6666, 227.7924, "LD_SPAC:white"); // ry right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][37], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][37], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][37], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][37], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][37], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][37], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][37], 0);

    Editor_PTD[playerid][38] = CreatePlayerTextDraw(playerid, 589.6666, 227.9322, "LD_SPAC:white"); // ry right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][38], 23.2800, 33.0399);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][38], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][38], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][38], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][38], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][38], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][38], 0);

    Editor_PTD[playerid][39] = CreatePlayerTextDraw(playerid, 578.6665, 207.6813, ""); // ry right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][39], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][39], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][39], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][39], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][39], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][39], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][39], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][39], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][39], 0x00000000);

    Editor_PTD[playerid][40] = CreatePlayerTextDraw(playerid, 594.9998, 242.7256, "LD_SPAC:white"); // ry right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][40], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][40], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][40], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][40], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][40], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][40], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][40], 0);

    Editor_PTD[playerid][41] = CreatePlayerTextDraw(playerid, 603.3331, 229.4073, "Box"); // ry right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][41], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][41], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][41], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][41], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][41], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][41], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][41], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][41], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][41], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][41], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][41], true);

    Editor_PTD[playerid][42] = CreatePlayerTextDraw(playerid, 500.3330, 184.6927, "Box"); // rx
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][42], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][42], 601.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][42], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][42], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][42], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][42], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][42], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][42], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][42], 0);

    Editor_PTD[playerid][43] = CreatePlayerTextDraw(playerid, 549.9998, 193.3186, "RX:_0.00"); // rx
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][43], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][43], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][43], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][43], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][43], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][43], 0);

    Editor_PTD[playerid][44] = CreatePlayerTextDraw(playerid, 486.3330, 187.7702, "LD_SPAC:white"); // rx left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][44], 24.0000, 28.6499);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][44], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][44], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][44], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][44], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][44], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][44], 0);

    Editor_PTD[playerid][45] = CreatePlayerTextDraw(playerid, 484.4664, 181.1334, "LD_Beat:chit"); // rx left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][45], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][45], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][45], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][45], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][45], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][45], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][45], 0);

    Editor_PTD[playerid][46] = CreatePlayerTextDraw(playerid, 490.3330, 182.9927, "LD_SPAC:white"); // rx left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][46], 23.1200, 33.2196);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][46], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][46], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][46], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][46], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][46], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][46], 0);

    Editor_PTD[playerid][47] = CreatePlayerTextDraw(playerid, 463.3330, 162.8813, ""); // rx left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][47], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][47], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][47], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][47], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][47], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][47], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][47], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][47], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][47], 0x00000000);

    Editor_PTD[playerid][48] = CreatePlayerTextDraw(playerid, 496.3330, 197.9259, "LD_SPAC:white"); // rx left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][48], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][48], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][48], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][48], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][48], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][48], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][48], 0);

    Editor_PTD[playerid][49] = CreatePlayerTextDraw(playerid, 499.9999, 184.6076, "Box"); // rx left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][49], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][49], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][49], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][49], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][49], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][49], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][49], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][49], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][49], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][49], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][49], true);

    Editor_PTD[playerid][50] = CreatePlayerTextDraw(playerid, 608.6334, 206.3368, "LD_Beat:chit"); // rx right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][50], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][50], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][50], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][50], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][50], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][50], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][50], 0);

    Editor_PTD[playerid][51] = CreatePlayerTextDraw(playerid, 593.6666, 182.9927, "LD_SPAC:white"); // rx right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][51], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][51], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][51], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][51], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][51], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][51], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][51], 0);

    Editor_PTD[playerid][52] = CreatePlayerTextDraw(playerid, 589.6666, 183.0325, "LD_SPAC:white"); // rx right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][52], 23.1599, 33.2196);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][52], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][52], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][52], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][52], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][52], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][52], 0);

    Editor_PTD[playerid][53] = CreatePlayerTextDraw(playerid, 578.6665, 162.8813, ""); // rx right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][53], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][53], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][53], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][53], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][53], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][53], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][53], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][53], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][53], 0x00000000);

    Editor_PTD[playerid][54] = CreatePlayerTextDraw(playerid, 594.9998, 197.9259, "LD_SPAC:white"); // rx right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][54], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][54], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][54], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][54], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][54], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][54], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][54], 0);

    Editor_PTD[playerid][55] = CreatePlayerTextDraw(playerid, 603.3331, 184.6076, "Box"); // rx right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][55], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][55], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][55], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][55], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][55], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][55], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][55], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][55], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][55], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][55], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][55], true);

    Editor_PTD[playerid][56] = CreatePlayerTextDraw(playerid, 504.3330, 367.3853, "LD_SPAC:white"); // exit
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][56], 94.0000, 24.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][56], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][56], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][56], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][56], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][56], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][56], 0);

    Editor_PTD[playerid][57] = CreatePlayerTextDraw(playerid, 502.4664, 360.7484, "LD_Beat:chit"); // exit
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][57], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][57], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][57], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][57], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][57], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][57], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][57], 0);

    Editor_PTD[playerid][58] = CreatePlayerTextDraw(playerid, 593.9671, 385.9518, "LD_Beat:chit"); // exit
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][58], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][58], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][58], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][58], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][58], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][58], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][58], 0);

    Editor_PTD[playerid][59] = CreatePlayerTextDraw(playerid, 508.3330, 362.6076, "LD_SPAC:white"); // exit
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][59], 94.0000, 28.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][59], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][59], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][59], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][59], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][59], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][59], 0);

    Editor_PTD[playerid][60] = CreatePlayerTextDraw(playerid, 504.3330, 372.1481, "LD_SPAC:white"); // exit
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][60], 94.0000, 24.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][60], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][60], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][60], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][60], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][60], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][60], 0);

    Editor_PTD[playerid][61] = CreatePlayerTextDraw(playerid, 505.0000, 362.5628, "XXXXXXXXXXXXX~n~XXXXXXXXXXXXX~n~XXXXXXXXXXXXX~n~"); // пусто
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][61], 0.3490, 1.2388);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][61], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][61], -16777211);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][61], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][61], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][61], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][61], 0);

    Editor_PTD[playerid][62] = CreatePlayerTextDraw(playerid, 553.9998, 370.4443, "EXIT"); // пусто
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][62], 0.4032, 1.8071);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][62], 30.0000, 95.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][62], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][62], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][62], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][62], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][62], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][62], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][62], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][62], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][62], true);

    Editor_PTD[playerid][63] = CreatePlayerTextDraw(playerid, 37.3329, 227.4183, "Box"); // y
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][63], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][63], 145.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][63], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][63], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][63], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][63], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][63], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][63], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][63], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][63], 0);

    Editor_PTD[playerid][64] = CreatePlayerTextDraw(playerid, 86.9996, 236.0442, "Y:_0.00"); // y
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][64], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][64], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][64], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][64], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][64], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][64], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][64], 0);

    Editor_PTD[playerid][65] = CreatePlayerTextDraw(playerid, 23.3327, 230.4958, "LD_SPAC:white"); // y left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][65], 24.0000, 28.6899);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][65], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][65], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][65], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][65], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][65], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][65], 0);

    Editor_PTD[playerid][66] = CreatePlayerTextDraw(playerid, 21.4661, 223.8589, "LD_Beat:chit"); // y left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][66], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][66], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][66], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][66], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][66], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][66], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][66], 0);

    Editor_PTD[playerid][67] = CreatePlayerTextDraw(playerid, 27.3327, 225.7183, "LD_SPAC:white"); // y left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][67], 23.1000, 33.2299);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][67], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][67], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][67], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][67], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][67], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][67], 0);

    Editor_PTD[playerid][68] = CreatePlayerTextDraw(playerid, 0.3328, 205.6071, ""); // y left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][68], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][68], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][68], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][68], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][68], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][68], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][68], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][68], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][68], 0x00000000);

    Editor_PTD[playerid][69] = CreatePlayerTextDraw(playerid, 33.3329, 240.6515, "LD_SPAC:white"); // y left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][69], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][69], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][69], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][69], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][69], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][69], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][69], 0);

    Editor_PTD[playerid][70] = CreatePlayerTextDraw(playerid, 36.9998, 227.3332, "Box"); // y left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][70], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][70], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][70], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][70], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][70], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][70], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][70], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][70], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][70], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][70], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][70], true);

    Editor_PTD[playerid][71] = CreatePlayerTextDraw(playerid, 126.6666, 225.7955, "LD_SPAC:white"); // y right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][71], 24.0000, 33.4400);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][71], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][71], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][71], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][71], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][71], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][71], 0);

    Editor_PTD[playerid][72] = CreatePlayerTextDraw(playerid, 145.6334, 249.0623, "LD_Beat:chit"); // y right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][72], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][72], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][72], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][72], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][72], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][72], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][72], 0);

    Editor_PTD[playerid][73] = CreatePlayerTextDraw(playerid, 130.6665, 225.7183, "LD_SPAC:white"); // y right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][73], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][73], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][73], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][73], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][73], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][73], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][73], 0);

    Editor_PTD[playerid][74] = CreatePlayerTextDraw(playerid, 115.6660, 205.6071, ""); // y right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][74], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][74], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][74], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][74], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][74], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][74], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][74], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][74], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][74], 0x00000000);

    Editor_PTD[playerid][75] = CreatePlayerTextDraw(playerid, 131.9998, 240.6515, "LD_SPAC:white"); // y right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][75], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][75], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][75], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][75], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][75], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][75], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][75], 0);

    Editor_PTD[playerid][76] = CreatePlayerTextDraw(playerid, 140.3329, 227.3332, "Box"); // y right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][76], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][76], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][76], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][76], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][76], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][76], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][76], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][76], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][76], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][76], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][76], true);

    Editor_PTD[playerid][77] = CreatePlayerTextDraw(playerid, 37.3329, 182.6186, "Box"); // x
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][77], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][77], 140.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][77], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][77], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][77], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][77], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][77], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][77], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][77], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][77], 0);

    Editor_PTD[playerid][78] = CreatePlayerTextDraw(playerid, 86.9997, 191.2445, "X:_0.00"); // x
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][78], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][78], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][78], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][78], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][78], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][78], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][78], 0);

    Editor_PTD[playerid][79] = CreatePlayerTextDraw(playerid, 23.3330, 185.6961, "LD_SPAC:white"); // x left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][79], 24.0000, 28.4600);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][79], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][79], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][79], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][79], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][79], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][79], 0);

    Editor_PTD[playerid][80] = CreatePlayerTextDraw(playerid, 21.4664, 179.0592, "LD_Beat:chit"); // x left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][80], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][80], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][80], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][80], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][80], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][80], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][80], 0);

    Editor_PTD[playerid][81] = CreatePlayerTextDraw(playerid, 27.3327, 180.9185, "LD_SPAC:white"); // x left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][81], 23.1100, 33.4700);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][81], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][81], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][81], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][81], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][81], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][81], 0);

    Editor_PTD[playerid][82] = CreatePlayerTextDraw(playerid, 0.3327, 160.8072, ""); // x left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][82], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][82], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][82], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][82], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][82], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][82], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][82], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][82], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][82], 0x00000000);

    Editor_PTD[playerid][83] = CreatePlayerTextDraw(playerid, 33.3329, 195.8518, "LD_SPAC:white"); // x left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][83], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][83], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][83], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][83], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][83], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][83], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][83], 0);

    Editor_PTD[playerid][84] = CreatePlayerTextDraw(playerid, 36.9998, 182.5334, "Box"); // x left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][84], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][84], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][84], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][84], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][84], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][84], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][84], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][84], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][84], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][84], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][84], true);

    Editor_PTD[playerid][85] = CreatePlayerTextDraw(playerid, 126.6661, 181.0958, "LD_SPAC:white"); // x right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][85], 24.0000, 33.2899);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][85], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][85], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][85], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][85], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][85], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][85], 0);

    Editor_PTD[playerid][86] = CreatePlayerTextDraw(playerid, 145.6333, 204.2626, "LD_Beat:chit"); // x right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][86], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][86], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][86], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][86], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][86], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][86], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][86], 0);

    Editor_PTD[playerid][87] = CreatePlayerTextDraw(playerid, 130.6663, 180.9185, "LD_SPAC:white"); // x right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][87], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][87], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][87], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][87], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][87], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][87], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][87], 0);

    Editor_PTD[playerid][88] = CreatePlayerTextDraw(playerid, 115.6660, 160.8072, ""); // x right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][88], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][88], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][88], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][88], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][88], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][88], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][88], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][88], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][88], 0x00000000);

    Editor_PTD[playerid][89] = CreatePlayerTextDraw(playerid, 131.9996, 195.8518, "LD_SPAC:white"); // x right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][89], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][89], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][89], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][89], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][89], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][89], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][89], 0);

    Editor_PTD[playerid][90] = CreatePlayerTextDraw(playerid, 140.3329, 182.5334, "Box"); // x right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][90], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][90], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][90], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][90], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][90], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][90], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][90], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][90], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][90], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][90], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][90], true);

    Editor_PTD[playerid][91] = CreatePlayerTextDraw(playerid, 36.9995, 273.8778, "Box"); // z
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][91], 0.0000, 3.3485);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][91], 145.0000, 0.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][91], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][91], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][91], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][91], -5963681);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][91], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][91], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][91], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][91], 0);

    Editor_PTD[playerid][92] = CreatePlayerTextDraw(playerid, 86.6660, 282.5039, "Z:_0.00"); // z
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][92], 0.2720, 1.3262);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][92], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][92], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][92], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][92], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][92], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][92], 0);

    Editor_PTD[playerid][93] = CreatePlayerTextDraw(playerid, 22.9995, 276.9555, "LD_SPAC:white"); // z left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][93], 27.1000, 28.4600);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][93], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][93], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][93], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][93], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][93], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][93], 0);

    Editor_PTD[playerid][94] = CreatePlayerTextDraw(playerid, 21.1329, 270.3186, "LD_Beat:chit"); // z left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][94], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][94], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][94], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][94], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][94], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][94], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][94], 0);

    Editor_PTD[playerid][95] = CreatePlayerTextDraw(playerid, 26.9995, 272.1777, "LD_SPAC:white"); // z left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][95], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][95], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][95], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][95], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][95], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][95], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][95], 0);

    Editor_PTD[playerid][96] = CreatePlayerTextDraw(playerid, -0.0003, 252.0661, ""); // z left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][96], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][96], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][96], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][96], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][96], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][96], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][96], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][96], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][96], 0x00000000);

    Editor_PTD[playerid][97] = CreatePlayerTextDraw(playerid, 32.9995, 287.1112, "LD_SPAC:white"); // z left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][97], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][97], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][97], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][97], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][97], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][97], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][97], 0);

    Editor_PTD[playerid][98] = CreatePlayerTextDraw(playerid, 36.6665, 273.7926, "Box"); // z left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][98], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][98], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][98], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][98], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][98], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][98], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][98], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][98], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][98], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][98], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][98], true);

    Editor_PTD[playerid][99] = CreatePlayerTextDraw(playerid, 126.3330, 272.2552, "LD_SPAC:white"); // z right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][99], 24.0000, 33.4100);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][99], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][99], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][99], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][99], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][99], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][99], 0);

    Editor_PTD[playerid][100] = CreatePlayerTextDraw(playerid, 145.3000, 295.5220, "LD_Beat:chit"); // z right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][100], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][100], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][100], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][100], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][100], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][100], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][100], 0);

    Editor_PTD[playerid][101] = CreatePlayerTextDraw(playerid, 130.3334, 272.1777, "LD_SPAC:white"); // z right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][101], 23.1700, 27.9200);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][101], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][101], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][101], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][101], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][101], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][101], 0);

    Editor_PTD[playerid][102] = CreatePlayerTextDraw(playerid, 115.3330, 252.0661, ""); // z right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][102], 61.0000, 73.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][102], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][102], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][102], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][102], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][102], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][102], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][102], -90.0000, -90.0000, 180.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][102], 0x00000000);

    Editor_PTD[playerid][103] = CreatePlayerTextDraw(playerid, 131.6665, 287.1112, "LD_SPAC:white"); // z right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][103], 12.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][103], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][103], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][103], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][103], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][103], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][103], 0);

    Editor_PTD[playerid][104] = CreatePlayerTextDraw(playerid, 139.9998, 273.7926, "Box"); // z right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][104], 0.0000, 25.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][104], 25.0000, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][104], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][104], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][104], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][104], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][104], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][104], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][104], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][104], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][104], true);

    Editor_PTD[playerid][105] = CreatePlayerTextDraw(playerid, 22.9995, 322.5848, "LD_SPAC:white"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][105], 107.0000, 24.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][105], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][105], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][105], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][105], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][105], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][105], 0);

    Editor_PTD[playerid][106] = CreatePlayerTextDraw(playerid, 21.1329, 315.9482, "LD_Beat:chit"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][106], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][106], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][106], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][106], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][106], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][106], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][106], 0);

    Editor_PTD[playerid][107] = CreatePlayerTextDraw(playerid, 41.9667, 341.1516, "LD_Beat:chit"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][107], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][107], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][107], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][107], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][107], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][107], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][107], 0);

    Editor_PTD[playerid][108] = CreatePlayerTextDraw(playerid, 26.9995, 317.8074, "LD_SPAC:white"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][108], 106.0000, 28.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][108], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][108], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][108], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][108], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][108], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][108], 0);

    Editor_PTD[playerid][109] = CreatePlayerTextDraw(playerid, 22.9995, 327.3479, "LD_SPAC:white"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][109], 23.4799, 24.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][109], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][109], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][109], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][109], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][109], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][109], 0);

    Editor_PTD[playerid][110] = CreatePlayerTextDraw(playerid, 126.3330, 322.5848, "LD_SPAC:white"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][110], 27.2698, 24.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][110], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][110], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][110], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][110], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][110], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][110], 0);

    Editor_PTD[playerid][111] = CreatePlayerTextDraw(playerid, 124.4664, 315.9482, "LD_Beat:chit"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][111], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][111], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][111], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][111], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][111], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][111], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][111], 0);

    Editor_PTD[playerid][112] = CreatePlayerTextDraw(playerid, 145.3000, 341.1516, "LD_Beat:chit"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][112], 10.0000, 12.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][112], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][112], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][112], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][112], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][112], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][112], 0);

    Editor_PTD[playerid][113] = CreatePlayerTextDraw(playerid, 130.3332, 317.8074, "LD_SPAC:white"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][113], 23.1298, 25.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][113], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][113], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][113], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][113], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][113], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][113], 0);

    Editor_PTD[playerid][114] = CreatePlayerTextDraw(playerid, 46.6665, 327.3479, "LD_SPAC:white"); // step
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][114], 104.0000, 23.7199);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][114], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][114], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][114], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][114], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][114], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][114], 0);

    Editor_PTD[playerid][115] = CreatePlayerTextDraw(playerid, 24.0000, 316.9331, "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX~N~XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX~N~XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX~N~"); // пусто
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][115], 0.1967, 1.2847);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][115], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][115], -16777211);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][115], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][115], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][115], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][115], 0);

    Editor_PTD[playerid][116] = CreatePlayerTextDraw(playerid, 86.6660, 327.1065, "STEP:_0.00"); // step
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][116], 0.2720, 1.3262);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][116], 30.0000, 130.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][116], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][116], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][116], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][116], -16777216);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][116], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][116], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][116], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][116], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][116], true);

    Editor_PTD[playerid][117] = CreatePlayerTextDraw(playerid, 171.3666, 382.9036, "O___o"); // left
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][117], 0.9100, 5.5489);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][117], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][117], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][117], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][117], 2);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][117], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][117], 0);

    Editor_PTD[playerid][118] = CreatePlayerTextDraw(playerid, 175.0664, 397.6666, "LD_SPAC:white"); // left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][118], 67.3899, 27.6000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][118], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][118], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][118], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][118], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][118], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][118], 0);

    Editor_PTD[playerid][119] = CreatePlayerTextDraw(playerid, 202.0000, 409.7963, "LD_SPAC:white"); // left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][119], 17.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][119], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][119], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][119], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][119], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][119], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][119], 0);

    Editor_PTD[playerid][120] = CreatePlayerTextDraw(playerid, 173.5333, 376.1962, ""); // left
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][120], 52.0000, 70.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][120], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][120], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][120], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][120], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][120], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][120], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][120], 0.0000, 90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][120], 0x00000000);

    Editor_PTD[playerid][121] = CreatePlayerTextDraw(playerid, 208.6667, 399.0666, "Box"); // left (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][121], 0.0000, 30.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][121], 30.0000, 72.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][121], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][121], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][121], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][121], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][121], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][121], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][121], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][121], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][121], true);

    Editor_PTD[playerid][122] = CreatePlayerTextDraw(playerid, 382.0336, 382.9038, "O___o"); // right
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][122], 0.9100, 5.5489);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][122], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][122], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][122], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][122], 2);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][122], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][122], 0);

    Editor_PTD[playerid][123] = CreatePlayerTextDraw(playerid, 385.7334, 397.6668, "LD_SPAC:white"); // right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][123], 67.3899, 27.6000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][123], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][123], -5963521);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][123], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][123], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][123], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][123], 0);

    Editor_PTD[playerid][124] = CreatePlayerTextDraw(playerid, 408.3334, 409.7965, "LD_SPAC:white"); // right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][124], 17.0000, 3.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][124], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][124], -1);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][124], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][124], 4);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][124], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][124], 0);

    Editor_PTD[playerid][125] = CreatePlayerTextDraw(playerid, 401.3334, 376.2965, ""); // right
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][125], 52.0000, 70.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][125], 1);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][125], -1);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][125], 5);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][125], 0);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][125], 0);
    PlayerTextDrawSetPreviewModel(playerid, Editor_PTD[playerid][125], 19177);
    PlayerTextDrawSetPreviewRot(playerid, Editor_PTD[playerid][125], 0.0000, -90.0000, 0.0000, 1.0000);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][125], 0x00000000);

    Editor_PTD[playerid][126] = CreatePlayerTextDraw(playerid, 419.6668, 399.0668, "Box"); // right (box)
    PlayerTextDrawLetterSize(playerid, Editor_PTD[playerid][126], 0.0000, 30.0000);
    PlayerTextDrawTextSize(playerid, Editor_PTD[playerid][126], 30.0000, 72.0000);
    PlayerTextDrawAlignment(playerid, Editor_PTD[playerid][126], 2);
    PlayerTextDrawColor(playerid, Editor_PTD[playerid][126], -1);
    PlayerTextDrawUseBox(playerid, Editor_PTD[playerid][126], 1);
    PlayerTextDrawBoxColor(playerid, Editor_PTD[playerid][126], 0);
    PlayerTextDrawBackgroundColor(playerid, Editor_PTD[playerid][126], 255);
    PlayerTextDrawFont(playerid, Editor_PTD[playerid][126], 1);
    PlayerTextDrawSetProportional(playerid, Editor_PTD[playerid][126], 1);
    PlayerTextDrawSetShadow(playerid, Editor_PTD[playerid][126], 0);
    PlayerTextDrawSetSelectable(playerid, Editor_PTD[playerid][126], true);
    return 1;
}
