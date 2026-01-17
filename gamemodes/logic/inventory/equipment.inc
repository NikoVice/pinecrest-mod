/*
    Author: Vip Uzer
    Flin Mobile
    (c) November 2021 - ххх 2022
*/


equipment_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_EQUIPMENT_INFO:
        {
            Equipment_ClearSelectInfo(playerid);
            return 1;
        }
        case D_EQUIPMENT_DIVIDE:
        {
            new slot_id = GetPVarInt(playerid, #EQ_SELECT_SLOT)-1;
            Equipment_ClearSelectInfo(playerid);
            if(!response) return 1;
            if(slot_id == -1) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
            if(!(0 <= slot_id <= MAX_ALL_EQUIPMENT-1)) return SendError(playerid, "Не известная ошибка. Напишите на форум: EQ-10.01.22");
            if(InventoryPlayer[playerid][slot_id][inv_mysql_id] == INVALID_MYSQL_ID)
                return SendError(playerid, "Предмет не определен, обратитесь к администрации: 02042023 2207.");
            new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                itemType = ItemsInfo[itemID][iType];
            if(itemType == TYPE_ITEMS_INVENTORY && (itemID == 679 && TentIDx[playerid] == 679 || itemID == 680 && TentIDx[playerid] == 680))
                return SendError(playerid, "Для начала необходимо забрать свой переносной ларек.");
            new value = strval(inputtext);
            if(!strlen(inputtext) || !(1 <= value <= InventoryPlayer[playerid][slot_id][inv_amount]))
                return 1;
            InventoryDivide(playerid, slot_id, value);
            return 1;
        }
        case D_EQUIPMENT_SELECTED:
        {
            new slot_id = GetPVarInt(playerid, #EQ_SELECT_SLOT)-1,
                new_slot = GetPVarInt(playerid, #EQ_SELECT_SLOT_NEW)-1;
            Equipment_ClearSelectInfo(playerid);
            if(response)
            {
                if(slot_id == -1) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
                if(!(0 <= slot_id <= MAX_ALL_EQUIPMENT-1)) return SendError(playerid, "Не известная ошибка. Напишите на форум: EQ-10.01.22");
                if(InventoryPlayer[playerid][slot_id][inv_mysql_id] == INVALID_MYSQL_ID)
                return SendError(playerid, "Предмет не определен, обратитесь к администрации: 02042023 2206.");
                new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                    itemType = ItemsInfo[itemID][iType];
                if(itemType == TYPE_ITEMS_INVENTORY && (itemID == 679 && TentIDx[playerid] == 679 || itemID == 680 && TentIDx[playerid] == 680))
                    return SendError(playerid, "Для начала необходимо забрать свой переносной ларек.");

                if(new_slot == -1)
                    return SendError(playerid, "Новый слот не определен. Без спешки повторите действие.");
                if(listitem == 0)
                    Equipment_SlotChangePos(playerid, slot_id, new_slot);
                else if(listitem == 1)
                {
                    InventoryMerge(playerid, slot_id, new_slot);
                }
            }
            return 1;
        }
        case D_EQUIPMENT_PUT:
        {
            new slot_id = GetPVarInt(playerid, #EQ_SELECT_SLOT)-1;
            Equipment_ClearSelectInfo(playerid);
            if(!p_temp[playerid][TextDrawEquipment] ||
                !p_temp[playerid][TextDrawInventory] ||
                !(EQUIPMENT_INVENTORY_HOUSE <= p_temp[playerid][InterfaceID] < EQUIPMENT_INVENTORY_ALL))
                return 1;
            if(!response)
                return 1;
            if(slot_id == -1) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
            if(!(0 <= slot_id <= MAX_ALL_EQUIPMENT-1)) return SendError(playerid, "Не известная ошибка. Напишите на форум: EQ-06.12.21");
            if(InventoryPlayer[playerid][slot_id][inv_mysql_id] == INVALID_MYSQL_ID)
                return SendError(playerid, "Предмет не определен, обратитесь к администрации: 02042023 2204.");
            
            new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                count = 1;
            if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY && strlen(inputtext))
                count = strval(inputtext);
            SetPVarInt(playerid, #EQ_SLOT_ID, slot_id+1);
            SetPVarInt(playerid, #EQ_RELOAD, 1);
            SetPVarInt(playerid, #EQ_COUNT, count);

            LoadOtherInventoryData(playerid, p_temp[playerid][InterfaceID]);
            return 1;
        }
        case D_EQUIPMENT_TAKE:
        {
            new slot_id = GetPVarInt(playerid, #EQ_SELECT_SLOT)-1;
            Equipment_ClearSelectInfo(playerid);
            if(!p_temp[playerid][TextDrawEquipment] ||
                !p_temp[playerid][TextDrawInventory] ||
                !(EQUIPMENT_INVENTORY_HOUSE <= p_temp[playerid][InterfaceID] < EQUIPMENT_INVENTORY_ALL))
                return 1;
            if(!response)
                return 1;
            new max_slot, min_slot;
            GetSlotInfoInventory(playerid, p_temp[playerid][InterfaceID], max_slot, min_slot);
            if(min_slot >= max_slot) return 1;
            slot_id += min_slot+1;

            new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                count = 1;
            if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY && strlen(inputtext))
                count = strval(inputtext);

            SetPVarInt(playerid, #EQ_SLOT_ID, slot_id+1);
            SetPVarInt(playerid, #EQ_RELOAD, 2);
            SetPVarInt(playerid, #EQ_COUNT, count);

            LoadOtherInventoryData(playerid, p_temp[playerid][InterfaceID]);
            return 1;
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////
//TD:
Equipment_InitPage(playerid)
{
    p_temp[playerid][inv_list_page][0] =
    p_temp[playerid][inv_list_page][1] = 1;

    Equipment_DestroyMenu(playerid);
    Equipment_ClearSelectInfo(playerid);
}

Equipment_AccessoriesUse(playerid)
{
    if(p_temp[playerid][TextDrawInventory])
    {
        for(new i = MAX_PLAYER_ATTACHED_OBJECTS-1; i != -1; i--)
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][5+i], 0);
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][5+i], 0.0, 0.0, 0.0, -1.0);
            PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][5+i]);
        }
        new vehicleid = GetPlayerVehicleID(playerid), itemId, acc_slot;
        if(IsVehicleAccessories(playerid, vehicleid))
        {
            for(new i = MAX_ALL_EQUIPMENT-1; i != MAX_PLAYER_EQUIPMENT-1; i--)
            {
                itemId = InventoryPlayer[playerid][i][inv_item_id];
                if( InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
                    ItemsInfo[itemId][iType] == TYPE_ITEMS_VEHICLE_TUNE &&
                    InventoryPlayer[playerid][i][inv_acc_slot] != -1 &&
                    InventoryPlayer[playerid][i][inv_status_use] > 0)
                {
                    acc_slot = InventoryPlayer[playerid][i][inv_acc_slot];
                    if(0 <= acc_slot <= 9)
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][5+acc_slot], ItemsInfo[itemId][iModel] == 74 ? 0 : ItemsInfo[itemId][iModel]);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][5+acc_slot], ItemsInfo[itemId][iObjectPos][0], ItemsInfo[itemId][iObjectPos][1], ItemsInfo[itemId][iObjectPos][2], ItemsInfo[itemId][iObjectPos][3]);
                        PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][5+acc_slot]);
                    }
                    else printf("%s[%d]: CRASH VEHICLE ACCESSIRIES SLOT", get_name(playerid), p_info[playerid][ID]);
                }
            }
        }
        else
        {
            for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
            {
                if( InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
                    ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
                    InventoryPlayer[playerid][i][inv_acc_slot] != -1 &&
                    InventoryPlayer[playerid][i][inv_status_use] > 0)
                {
                    acc_slot = InventoryPlayer[playerid][i][inv_acc_slot];
                    itemId = InventoryPlayer[playerid][i][inv_item_id];
                    if(0 <= acc_slot <= 9)
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][5+acc_slot], ItemsInfo[itemId][iModel] == 74 ? 0 : ItemsInfo[itemId][iModel]);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][5+acc_slot], ItemsInfo[itemId][iObjectPos][0], ItemsInfo[itemId][iObjectPos][1], ItemsInfo[itemId][iObjectPos][2], ItemsInfo[itemId][iObjectPos][3]);
                        PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][5+acc_slot]);
                    }
                    else printf("%s[%d]: CRASH ACCESSIRIES SLOT", get_name(playerid), p_info[playerid][ID]);
                }
            }
        }
    }
}

Equipment_Info(playerid)
{
    if(p_temp[playerid][TextDrawEquipment])
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(IsVehicleAccessories(playerid, vehicleid))
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][16], GetVehicleModelEx(vehicleid));
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][16], -15.0, 0.0, -25.0, 1.5);

            f(STRING_GLOBAL, "%s", GetVehicleName(vehicleid));
        }
        else
        {
            f(STRING_GLOBAL, "ID:_%d", GetPlayerSkin(playerid));
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][16], GetPlayerSkin(playerid));
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][16], -15.0, 0.0, -25.0, 1.0);
        }
        PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][16]);

        PlayerTextDrawSetString(playerid, PTD_EquipmentPersonInfo[playerid][17], STRING_GLOBAL);
        PlayerTextDrawSetString(playerid, PTD_EquipmentPersonInfo[playerid][4], get_name(playerid));
    }
}

Equipment_SelectBox(playerid, new_selected_type = -1, new_selected_slot = -1)
{
    new old_selected_type = GetPVarInt(playerid, #EQ_SELECT_TYPE)-1,
        old_selected_slot = GetPVarInt(playerid, #EQ_SELECT_SLOT)-1;
    if(new_selected_type == -1 && old_selected_type == -1 && old_selected_slot == -1 && new_selected_slot == -1) return 1;
    if(new_selected_type == INVENTORY_SELECT_TYPE_RIGHT)
    {
        if(p_temp[playerid][TextDrawMarket]) return SendError(playerid, "Взаимодействие не доступно.");
        new_selected_slot += (p_temp[playerid][inv_list_page][0]-1)*20;

        if(old_selected_type == INVENTORY_SELECT_TYPE_RIGHT && new_selected_type == INVENTORY_SELECT_TYPE_RIGHT && 
            p_temp[playerid][TextDrawEquipmentMenu] &&
            (new_selected_slot-5 == old_selected_slot || new_selected_slot-10 == old_selected_slot))
        {
            SendDebug(playerid, "fix menu");
            return 1;
        }

        if(!p_temp[playerid][TextDrawTrade] &&
            p_temp[playerid][InterfaceID] != EQUIPMENT_INVENTORY_PLAYER &&
            InventoryPlayer[playerid][new_selected_slot][inv_mysql_id] == INVALID_MYSQL_ID)
            return 1;
    }
    if(new_selected_type == INVENTORY_SELECT_TYPE_LEFT)
    {
        if(p_temp[playerid][TextDrawInventory]) new_selected_slot += (p_temp[playerid][inv_list_page][1]-1)*20;
    }
    //Функционал когда уже выбран был до этого элемент
    if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER && new_selected_type != -1 && new_selected_slot != -1)
    {
        if(new_selected_slot >= p_info[playerid][inv_slots])
        {
            SendError(playerid, "Ячейки не доступны взаимодействия. Доступно: %d ячеек.", p_info[playerid][inv_slots]);
            Equipment_ClearSelectInfo(playerid);
            Equipment_DestroyMenu(playerid);
            return 1;
        }
        if(GetPVarInt(playerid, #EQ_SELECT_MYSQL_ID) != INVALID_MYSQL_ID)
        {
            Equipment_DestroyMenu(playerid);
            if(new_selected_type == INVENTORY_SELECT_TYPE_RIGHT && GetPVarInt(playerid, #EQ_SELECT_MYSQL_ID) == InventoryPlayer[playerid][new_selected_slot][inv_mysql_id])
                return Equipment_ClearSelectInfo(playerid);

            if(new_selected_type == INVENTORY_SELECT_TYPE_RIGHT && old_selected_type == INVENTORY_SELECT_TYPE_RIGHT &&
                GetPVarInt(playerid, #EQ_SELECT_MYSQL_ID) != InventoryPlayer[playerid][new_selected_slot][inv_mysql_id])
            {
                if( InventoryPlayer[playerid][old_selected_slot][inv_item_id] == InventoryPlayer[playerid][new_selected_slot][inv_item_id] &&
                    ItemsInfo[InventoryPlayer[playerid][old_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_INVENTORY &&
                    ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_INVENTORY &&
                    InventoryPlayer[playerid][new_selected_slot][inv_amount] != ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iMax] &&
                    InventoryPlayer[playerid][old_selected_slot][inv_amount] != ItemsInfo[InventoryPlayer[playerid][old_selected_slot][inv_item_id]][iMax])
                {
                    SetPVarInt(playerid, #EQ_CONTROL_BLOCK, true);
                    SetPVarInt(playerid, #EQ_SELECT_SLOT_NEW, new_selected_slot+1);
                    return ShowPlayerDialog(playerid, D_EQUIPMENT_SELECTED, DIALOG_STYLE_LIST, "Выберите действие..",
                        ""I"[1]"W" Переместить\n"I"[2]"W" Объединить", "Выбрать", "Отмена");
                }
                else
                    Equipment_SlotChangePos(playerid, old_selected_slot, new_selected_slot);
            }
            if(old_selected_type == INVENTORY_SELECT_TYPE_RIGHT && new_selected_type == INVENTORY_SELECT_TYPE_USE_ACC ||
                old_selected_type == INVENTORY_SELECT_TYPE_USE_ACC && new_selected_type == INVENTORY_SELECT_TYPE_RIGHT ||
                (new_selected_type == INVENTORY_SELECT_TYPE_USE_ACC && old_selected_type == INVENTORY_SELECT_TYPE_USE_ACC))
            {
                Equpment_AccessoriesActions(playerid, old_selected_type, new_selected_type, old_selected_slot, new_selected_slot);
            }
            Equipment_ClearSelectInfo(playerid);
            return 1;
        }
        else
        {
            new slot_id = new_selected_slot;
            if(new_selected_type == INVENTORY_SELECT_TYPE_USE_ACC)
                slot_id = Equipment_GetAccSlotUse(playerid, new_selected_slot);
            if(slot_id == -1 || InventoryPlayer[playerid][slot_id][inv_mysql_id] == INVALID_MYSQL_ID) return 1;
            SetPVarInt(playerid, #EQ_SELECT_MYSQL_ID, InventoryPlayer[playerid][slot_id][inv_mysql_id]);
        }
    }

    SetPVarInt(playerid, #EQ_SELECT_SLOT, new_selected_slot+1);
    SetPVarInt(playerid, #EQ_SELECT_TYPE, new_selected_type+1);

    if(new_selected_slot != -1)
    {
        switch(new_selected_type)
        {
            case INVENTORY_SELECT_TYPE_RIGHT:
            {
                if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER)
                {
                    new sButtonName[][] = {"USE", "INFO", "DIVIDE", "CLOSE"};
                    Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);

                    new isVehicleAccessories = GetPVarInt(playerid, #VEHICLEID_ACCESSORIES);

                    if((!isVehicleAccessories &&
                        (ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES ||
                        (old_selected_slot != -1 && ItemsInfo[InventoryPlayer[playerid][old_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES))) ||
                        (isVehicleAccessories && 
                        (ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE ||
                        (old_selected_slot != -1 && ItemsInfo[InventoryPlayer[playerid][old_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE))))
                    {
                        for(new i = 14; i != 4; i--)
                        {
                            if((!isVehicleAccessories && ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES) ||
                                (isVehicleAccessories && ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE))
                                PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][i], 0xfff60085);
                            else
                                PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][i], 454761471);
                            PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][i]);
                        }
                    }

                    if(new_selected_slot < 10)
                    {
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][new_selected_slot+10], false);
                        PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][new_selected_slot+10]);
                    }
                    if(new_selected_slot < 15)
                    {
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][new_selected_slot+5], false);
                        PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][new_selected_slot+5]);
                    }
                }
                if(p_temp[playerid][TextDrawTrade])
                {
                    if(p_temp[playerid][InterfaceID] == EQUIPMENT_TRADE) return SendInfo(playerid, "Нажмите ADD.");
                    if(EQUIPMENT_TRADE_BET_CAR <= p_temp[playerid][InterfaceID] <= EQUIPMENT_TRADE_BET_INVENTORY)
                    {
                        new sButtonName[][] = {"BET", "INFO", "CLOSE"};
                        Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);
                    }
                    if(p_temp[playerid][InterfaceID] == EQUIPMENT_TRADE_READY)
                    {
                        new sButtonName[][] = {"INFO", "CLOSE"};
                        Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);
                    }
                    /*
                    if(new_selected_slot < 10)
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][new_selected_slot+10], false);
                    if(new_selected_slot < 15)
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][new_selected_slot+5], false);
                    */
                }
                if( p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_HOUSE ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY)
                {
                    if(InventoryPlayer[playerid][new_selected_slot][inv_mysql_id] == INVALID_MYSQL_ID)
                        return 1;
                    new sButtonName[][] = {"BET", "INFO", "CLOSE"};
                    Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);

                    /*
                    if(new_selected_slot < 10)
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][new_selected_slot+10], false);
                    if(new_selected_slot < 15)
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][new_selected_slot+5], false);
                    */
                }
            }
            case INVENTORY_SELECT_TYPE_USE_ACC:
            {
                new sButtonName[][] = {"REMOVE", "INFO", "CLOSE"};
                Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);
            }
            case INVENTORY_SELECT_TYPE_LEFT:
            {
                if(p_temp[playerid][TextDrawTrade])
                {
                    if(new_selected_slot >= 10) return 1;
                    if(p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_READY)
                    {
                        if(gExchange[playerid][new_selected_slot][xType] == INVALID_EXCHANGE) ShowBetMenu(playerid);
                        else
                        {
                            new sButtonName[][] = {"UNBET", "INFO", "CLOSE"};
                            Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);
                        }
                    }
                    if(p_temp[playerid][InterfaceID] == EQUIPMENT_TRADE_READY)
                    {
                        if(gExchange[playerid][new_selected_slot][xType] == INVALID_EXCHANGE) return 1;
                        new sButtonName[][] = {"INFO", "CLOSE"};
                        Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);
                    }
                }
                if(p_temp[playerid][TextDrawMarket])
                {
                    new slot_id = p_temp[playerid][p_listitem][new_selected_slot];
                    if(slot_id == -1) return SendError(playerid, "Не известная ошибка 17.01-21:42. Повторите действие.");
                    if(p_temp[playerid][InterfaceID] == MARKET_BUY) ShowDialogMarketItemsSell(playerid, slot_id);
                    if(p_temp[playerid][InterfaceID] == MARKET_SELL) ShowDialogMarketItemsBuy(playerid, slot_id);
                }
                if( p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_HOUSE ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY)
                {
                    new sButtonName[][] = {"TAKE", "INFO", "CLOSE"};
                    Equipment_CreateMenu(playerid, new_selected_type, new_selected_slot, sizeof(sButtonName), sButtonName);

                }
            }
        }
    }
    return 1;
}

Equipment_ClearSelectInfo(playerid)
{
    if(p_temp[playerid][TextDrawInventory])
    {
        new selected_type = GetPVarInt(playerid, #EQ_SELECT_TYPE)-1;
        if(selected_type == INVENTORY_SELECT_TYPE_RIGHT && p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER)
        {
            for(new i = 14; i != 4; i--)
            {
                PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][i], 454761471);
                PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][i]);
            }
        }
        DeletePVar(playerid, #EQ_SELECT_MYSQL_ID);
        DeletePVar(playerid, #EQ_SELECT_SLOT_NEW);
    }
    DeletePVar(playerid, #EQ_CONTROL_BLOCK);

    DeletePVar(playerid, #EQ_SELECT_TYPE);
    DeletePVar(playerid, #EQ_SELECT_SLOT);
    return 1;
}

Equipment_Right(playerid, interface_id)
{
    switch(interface_id)
    {
        case EQUIPMENT_INVENTORY_PLAYER, EQUIPMENT_INVENTORY_HOUSE, EQUIPMENT_INVENTORY_BOOT, EQUIPMENT_INVENTORY_TRASHBOX, EQUIPMENT_INVENTORY_FAMILY, MARKET_SELL, MARKET_BUY:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], "INVENTORY");
            Equipment_InvRight(playerid);
        }
        case EQUIPMENT_TRADE..EQUIPMENT_TRADE_READY:
        {
            Equipment_TradeRight(playerid, interface_id);
        }
    }
    f(STRING_GLOBAL, "%d", p_temp[playerid][inv_list_page][0]);
    PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][51], STRING_GLOBAL);

}

Equipment_Left(playerid, interface_id)
{
    switch(interface_id)
    {
        case EQUIPMENT_TRADE..EQUIPMENT_TRADE_READY: Equipment_TradeLeft(playerid, interface_id);
        case MARKET_SELL, MARKET_BUY:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][4], interface_id == MARKET_SELL ? "SELL ITEMS" : "BUY ITEMS");
            Equipment_MarketLeft(playerid, interface_id);
        }
        case EQUIPMENT_INVENTORY_HOUSE:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][4], "HOUSE ITEMS");
            Equipment_InvLeft(playerid, interface_id);
        }
        case EQUIPMENT_INVENTORY_BOOT:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][4], "VEHICLES ITEMS");
            Equipment_InvLeft(playerid, interface_id);
        }
        case EQUIPMENT_INVENTORY_TRASHBOX:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][4], "TRASHBOX ITEMS");
            Equipment_InvLeft(playerid, interface_id);
        }
        case EQUIPMENT_INVENTORY_FAMILY:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][4], "FAMILY ITEMS");
            Equipment_InvLeft(playerid, interface_id);
        }
    }
    f(STRING_GLOBAL, "%d", p_temp[playerid][inv_list_page][1]);
    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][51], STRING_GLOBAL);
}

Equipment_InvRight(playerid)
{
    new count = (p_temp[playerid][inv_list_page][0]-1)*20,
        itemId, statusUse;
    for(new i; i < 20; i++)
    {
        if(count+i >= p_info[playerid][inv_slots]) Equipment_TDClearSlotRight(playerid, i);
        else if(InventoryPlayer[playerid][count+i][inv_mysql_id] == INVALID_MYSQL_ID)
        {
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][i+5], true);
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][i+5], 0);
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][i+5], 0.000000, 0.000000, 0.000000, 50.000000);
            PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][i+25], "_");
        }
        else
        {
            itemId = InventoryPlayer[playerid][count+i][inv_item_id];
            statusUse = InventoryPlayer[playerid][count+i][inv_status_use];

            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][i+5], true); 
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][i+5], ItemsInfo[itemId][iModel] == 74 ? 0 : ItemsInfo[itemId][iModel]);
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][i+5], ItemsInfo[itemId][iObjectPos][0], ItemsInfo[itemId][iObjectPos][1], ItemsInfo[itemId][iObjectPos][2], ItemsInfo[itemId-1][iObjectPos][3]);

            switch(ItemsInfo[itemId][iType])
            {
                case TYPE_ITEMS_INVENTORY:
                {
                    f(STRING_GLOBAL, "%d", InventoryPlayer[playerid][count+i][inv_amount]);
                    PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][i+25], STRING_GLOBAL);
                }
                default:
                    PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][i+25], statusUse ? "USE" : "_");
            }
        }
        PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][i+5]);
    }
    return 1;
}

forward Equipment_Update(playerid);
public Equipment_Update(playerid)
{
    if(p_temp[playerid][TextDrawEquipment])
    {
        Equipment_Right(playerid, p_temp[playerid][InterfaceID]);
        Equipment_Left(playerid, p_temp[playerid][InterfaceID]);
        Equipment_DestroyMenu(playerid);
    }
    return 1;
}

DropPlayerEquipment(playerid, slot_id)
{
    new mysql_id = InventoryPlayer[playerid][slot_id][inv_mysql_id];
    Equipment_ClearSlot(playerid, slot_id);
    if(mysql_id == INVALID_MYSQL_ID)
        return 0;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `inventory` WHERE mysql_id = %d", mysql_id);
    mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
    return 1;
}

Equipment_ClearSlot(playerid, slot_id)
{
    if(p_info[playerid][loggedIn])
    {
        if(InventoryPlayer[playerid][slot_id][inv_mysql_id] != INVALID_MYSQL_ID)
        {
            if(ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
                InventoryPlayer[playerid][slot_id][inv_status_use] != 0 &&
                InventoryPlayer[playerid][slot_id][inv_acc_slot] != -1 &&
                IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][slot_id][inv_acc_slot]))
                RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][slot_id][inv_acc_slot]);

            if(InventoryPlayer[playerid][slot_id][inv_item_id] == 653)
                ClearHookah(playerid, 1);

            if(ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iType] == TYPE_ITEMS_SKINS &&
                InventoryPlayer[playerid][slot_id][inv_status_use] != 0)
            {
                InventoryPlayer[playerid][slot_id][inv_status_use] = 0;
                SetPlayerSkinEx(playerid);
            }
        }
    }
    InventoryPlayer[playerid][slot_id][inv_mysql_id] = INVALID_MYSQL_ID;
    InventoryPlayer[playerid][slot_id][inv_acc_slot] = -1;
    InventoryPlayer[playerid][slot_id][inv_status_use] =
    InventoryPlayer[playerid][slot_id][inv_amount] =
    InventoryPlayer[playerid][slot_id][inv_item_id] =
    InventoryPlayer[playerid][slot_id][inv_market_buy_price] =
    InventoryPlayer[playerid][slot_id][inv_market_buy_amount] =
    InventoryPlayer[playerid][slot_id][inv_market_sell_price] =
    InventoryPlayer[playerid][slot_id][inv_market_sell_amount] = 
    InventoryPlayer[playerid][slot_id][inv_freeze_time] = 0;
}

Equipment_CreateMenu(playerid, type_id, slot_id, items, button_name[][])
{
    Equipment_DestroyMenu(playerid);
    if(p_temp[playerid][TextDrawEquipmentMenu]) return SendError(playerid, "Произошла не известная ошибка: EL-211121.");

    //right side
    new Float:item_width = 36.0, Float:item_height = 43.0, Float:inventory_width = 188.0, Float:bottom_height = 34.0,
        Float:distance_between_items = 1.0, Float:borders_inv = 2.0, items_inv_rows = 4, items_inv_columns = 5, Float:header = 19.0,
        Float:acc_item_width = 25.0, Float:acc_item_height = 33.0, Float:menu_button_height = 22.5, Float:menu_button_width = 43.0,
        Float:inventory_height = header+(borders_inv*2)+(item_height*items_inv_rows)+(distance_between_items*(items_inv_rows-1))+3+bottom_height,
        Float:start_x = 640.0/2-(inventory_width*2+3)/2+inventory_width+3, Float:start_y = 448.0/2-inventory_height/2+45;

    new col_num = slot_id%items_inv_columns,
    row_num = (slot_id%items_inv_rows-col_num < 0) ? (slot_id%items_inv_rows-col_num+4) : (slot_id%items_inv_rows-col_num);

	if (IsPlayerMobile(playerid)) menu_button_height = 28.125;

    if(type_id == INVENTORY_SELECT_TYPE_USE_ACC)
    {
        if (slot_id%2 != 0 && slot_id > 3)
            col_num = 0, row_num = -((slot_id-1)/2-4);
        else if (slot_id%2 == 0 && slot_id > 3)
            col_num = 3, row_num = -(slot_id/2-4);
        else
            row_num = 3, col_num = -(slot_id-3);

        item_height = acc_item_height, item_width = acc_item_width;
        start_x = start_x-3-(borders_inv*2+acc_item_width*4+3*distance_between_items);
        menu_button_width = 32.0;
    }
    if(type_id == INVENTORY_SELECT_TYPE_LEFT) start_x = start_x-inventory_width-3;

    new Float:menu_list_height = items*menu_button_height+(items+1)*distance_between_items,
    Float:menu_list_width = menu_button_width+2*distance_between_items,
    Float:selected_slot_coord_X = start_x+borders_inv+col_num*(item_width+distance_between_items),
    Float:selected_slot_coord_Y = start_y+header+borders_inv+row_num*(item_height+distance_between_items);

    PTD_EquipmentMenu[playerid][0] = CreatePlayerTextDraw(playerid, selected_slot_coord_X-((menu_button_width+2*distance_between_items)-item_width)/2.0,
        selected_slot_coord_Y + 0.75*item_height, "LD_SPAC:white"); // background
    PlayerTextDrawTextSize(playerid, PTD_EquipmentMenu[playerid][0], menu_list_width, menu_list_height);
    PlayerTextDrawAlignment(playerid, PTD_EquipmentMenu[playerid][0], 1);
    PlayerTextDrawColor(playerid, PTD_EquipmentMenu[playerid][0], 0x000000ff);
    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentMenu[playerid][0], 255);
    PlayerTextDrawFont(playerid, PTD_EquipmentMenu[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, PTD_EquipmentMenu[playerid][0], 0);
    PlayerTextDrawShow(playerid, PTD_EquipmentMenu[playerid][0]);

    for(new i = 1; i < 6; i++){
        if(i == 5 || i < items)
        {
            PTD_EquipmentMenu[playerid][i] = CreatePlayerTextDraw(playerid, selected_slot_coord_X-((menu_button_width+2*distance_between_items)-item_width)/2.0+distance_between_items,
                selected_slot_coord_Y+0.75*item_height+distance_between_items+((i == 5 ? items : i)-1)*(menu_button_height+distance_between_items), "LD_SPAC:white"); // background
            PlayerTextDrawTextSize(playerid, PTD_EquipmentMenu[playerid][i], menu_button_width, menu_button_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentMenu[playerid][i], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentMenu[playerid][i], (i == 5) ? 0xd55444FF : 842150655);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentMenu[playerid][i], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentMenu[playerid][i], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentMenu[playerid][i], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentMenu[playerid][i], true);
            PlayerTextDrawShow(playerid, PTD_EquipmentMenu[playerid][i]);

            if(type_id == INVENTORY_SELECT_TYPE_USE_ACC)
            {
                PTD_EquipmentMenu[playerid][i+5] = CreatePlayerTextDraw(playerid, selected_slot_coord_X+distance_between_items-((menu_button_width+2*distance_between_items)-item_width)/2.0+menu_button_width/2,
                        selected_slot_coord_Y+0.75*item_height+distance_between_items+((i == 5 ? items : i)-1)*(menu_button_height+distance_between_items)+4, i == 5 ? button_name[items-1] : button_name[i-1]);
                PlayerTextDrawLetterSize(playerid, PTD_EquipmentMenu[playerid][i+5], 0.75*0.2475, 0.75*1.74);
            }
            else
            {
                PTD_EquipmentMenu[playerid][i+5] = CreatePlayerTextDraw(playerid, selected_slot_coord_X+distance_between_items-((menu_button_width+2*distance_between_items)-item_width)/2.0+menu_button_width/2,
                        selected_slot_coord_Y+0.75*item_height+distance_between_items+((i == 5 ? items : i)-1)*(menu_button_height+distance_between_items)+2, i == 5 ? button_name[items-1] : button_name[i-1]);
                PlayerTextDrawLetterSize(playerid, PTD_EquipmentMenu[playerid][i+5], 0.2475, 1.74*(IsPlayerMobile(playerid) ? 1.25 : 1.0));
            }

            /*
            PTD_EquipmentMenu[playerid][i+5] = CreatePlayerTextDraw(playerid, selected_slot_coord_X+distance_between_items-((menu_button_width+2*distance_between_items)-item_width)/2.0+menu_button_width/2,
                selected_slot_coord_Y+0.75*item_height+distance_between_items+((i == 5 ? items : i)-1)*(menu_button_height+distance_between_items)+2, i == 5 ? button_name[items-1] : button_name[i-1]);
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentMenu[playerid][i+5], 1.5*0.165000, 1.5*1.160000);
            */
            PlayerTextDrawTextSize(playerid, PTD_EquipmentMenu[playerid][i+5], 0.000000, 41.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentMenu[playerid][i+5], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentMenu[playerid][i+5], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentMenu[playerid][i+5], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentMenu[playerid][i+5], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentMenu[playerid][i+5], 2);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentMenu[playerid][i+5], 1);
            PlayerTextDrawShow(playerid, PTD_EquipmentMenu[playerid][i+5]);
        }
        else
        {
            PTD_EquipmentMenu[playerid][i] = CreatePlayerTextDraw(playerid,  0.0, 0.0, "_");
            PlayerTextDrawHide(playerid, PTD_EquipmentMenu[playerid][i]);

            PTD_EquipmentMenu[playerid][i+5] = CreatePlayerTextDraw(playerid, 0.0, 0.0, "_");
            PlayerTextDrawHide(playerid, PTD_EquipmentMenu[playerid][i+5]);
        }
    }
    p_temp[playerid][TextDrawEquipmentMenu] = true;
    return 1;
}

Equipment_DestroyMenu(playerid)
{
    if(p_temp[playerid][TextDrawEquipmentMenu])
    {
        for(new i = 10; i != -1; i--)
        {
            if(PTD_EquipmentMenu[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, PTD_EquipmentMenu[playerid][i]);
                PTD_EquipmentMenu[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
        }
        p_temp[playerid][TextDrawEquipmentMenu] = false;
    }
}

Equpment_AccessoriesActions(playerid, old_selected_type, new_selected_type, old_selected_slot, new_selected_slot)
{
    new playerState = GetPlayerState(playerid);
    if(old_selected_type == INVENTORY_SELECT_TYPE_RIGHT && new_selected_type == INVENTORY_SELECT_TYPE_USE_ACC)
    {
        if(ItemsInfo[InventoryPlayer[playerid][old_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES)
        {
            if(playerState == PLAYER_STATE_DRIVER)
                return SendError(playerid, "Вы должны быть не за рулем автомобиля.");
            new new_slot = Equipment_GetAccSlotUse(playerid, new_selected_slot);

            if(InventoryPlayer[playerid][old_selected_slot][inv_status_use] != 0)
                SetPlayerAccessoriesStatusUse(playerid, old_selected_slot);

            SetPVarInt(playerid, #EQ_TEMP_SLOT, new_slot+1);
            InventoryPlayer[playerid][old_selected_slot][inv_status_use] = 1;
            AttachPlayerAccessories(playerid, old_selected_slot, .slot_use = new_selected_slot, .whence = 1);
        }
        else if(ItemsInfo[InventoryPlayer[playerid][old_selected_slot][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE)
        {
            if(playerState != PLAYER_STATE_DRIVER)
                return SendError(playerid, "Вы должны быть за рулем автомобиля.");

            new new_slot = Equipment_GetAccSlotUse(playerid, new_selected_slot);
            if(new_slot != -1)
                SetPVarInt(playerid, #EQ_TEMP_SLOT, new_slot+1);

            UseVehicleAccessories(playerid, old_selected_slot, new_selected_slot);
        }
        else return SendError(playerid, "Одеть можно только акссесуар.");
    }
    if(old_selected_type == INVENTORY_SELECT_TYPE_USE_ACC && new_selected_type == INVENTORY_SELECT_TYPE_USE_ACC)
    {
        new new_slot = Equipment_GetAccSlotUse(playerid, new_selected_slot);
        Equipment_AccessoriesChangePos(playerid, old_selected_slot, new_selected_slot, new_slot != -1 ? true : false);
    }
    if(old_selected_type == INVENTORY_SELECT_TYPE_USE_ACC && new_selected_type == INVENTORY_SELECT_TYPE_RIGHT)
    {
        new old_slot = Equipment_GetAccSlotUse(playerid, old_selected_slot);
        if(ItemsInfo[InventoryPlayer[playerid][old_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES)
        {
            if(playerState == PLAYER_STATE_DRIVER)
                return SendError(playerid, "Вы должны быть не за рулем автомобиля.");
            if(InventoryPlayer[playerid][new_selected_slot][inv_mysql_id] == INVALID_MYSQL_ID)
            {
                SetPlayerAccessoriesStatusUse(playerid, old_slot);
                Equipment_SlotChangePos(playerid, old_slot, new_selected_slot);
            }
            else
            {
                if(InventoryPlayer[playerid][new_selected_slot][inv_mysql_id] == InventoryPlayer[playerid][old_slot][inv_mysql_id])
                    return 1;
                if(ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES)
                    return SendError(playerid, "Заменить можно только на акссесуар.");

                if(InventoryPlayer[playerid][new_selected_slot][inv_status_use] != 0)
                    SetPlayerAccessoriesStatusUse(playerid, new_selected_slot);

                SetPVarInt(playerid, #EQ_TEMP_SLOT, old_slot+1);
                InventoryPlayer[playerid][new_selected_slot][inv_status_use] = 1;
                AttachPlayerAccessories(playerid, new_selected_slot, .slot_use = old_selected_slot, .whence = 2);
            }
        }
        else if(ItemsInfo[InventoryPlayer[playerid][old_slot][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE)
        {
            if(playerState != PLAYER_STATE_DRIVER)
                return SendError(playerid, "Вы должны быть за рулем автомобиля.");
            new old_slot = Equipment_GetAccSlotUse(playerid, old_selected_slot);
            if(InventoryPlayer[playerid][new_selected_slot][inv_mysql_id] == INVALID_MYSQL_ID)
            {
                DeleteVehicleAccessories(playerid, old_slot, new_selected_slot);
            }
            else
            {
                if(InventoryPlayer[playerid][new_selected_slot][inv_mysql_id] == InventoryPlayer[playerid][old_slot][inv_mysql_id])
                    return SendError(playerid, "Ошибка 30.03.23 23:32.");
                if(ItemsInfo[InventoryPlayer[playerid][new_selected_slot][inv_item_id]][iType] != TYPE_ITEMS_VEHICLE_TUNE)
                    return SendError(playerid, "Заменить можно только на акссесуар.");

                if(playerState != PLAYER_STATE_DRIVER)
                return SendError(playerid, "Вы должны быть за рулем автомобиля.");

                new old_slot = Equipment_GetAccSlotUse(playerid, old_selected_slot);
                if(old_slot != -1)
                    SetPVarInt(playerid, #EQ_TEMP_SLOT, old_slot+1);

                UseVehicleAccessories(playerid, new_selected_slot, old_selected_slot);
            }
        }
        else return 1;
    }
    Equipment_Update(playerid);
    return 1;
}

Equipment_SlotChangePos(playerid, old_slot, new_slot)
{
    if(InventoryPlayer[playerid][old_slot][inv_mysql_id] != InventoryPlayer[playerid][new_slot][inv_mysql_id])
    {
        new mysqlID = INVALID_MYSQL_ID, itemID,
            amount, statusUse, accSlot, accMT1, accMT2,
            Float:accWear, Float:accPos[9],
            buyPrice, buyAmount,
            sellPrice, sellAmount,
            Float:skinWear, premium_acc, premium_skin;

        itemID = InventoryPlayer[playerid][new_slot][inv_item_id];
        buyPrice = InventoryPlayer[playerid][new_slot][inv_market_buy_price];
        buyAmount = InventoryPlayer[playerid][new_slot][inv_market_buy_amount];

        if(InventoryPlayer[playerid][new_slot][inv_mysql_id] != INVALID_MYSQL_ID)
        {
            mysqlID = InventoryPlayer[playerid][new_slot][inv_mysql_id];
            amount = InventoryPlayer[playerid][new_slot][inv_amount];
            statusUse = InventoryPlayer[playerid][new_slot][inv_status_use];
            accSlot = InventoryPlayer[playerid][new_slot][inv_acc_slot];
            accMT1 = InventoryPlayer[playerid][new_slot][inv_acc_mt][0];
            accMT2 = InventoryPlayer[playerid][new_slot][inv_acc_mt][1];
            accWear = InventoryPlayer[playerid][new_slot][inv_acc_wear];
            skinWear = InventoryPlayer[playerid][new_slot][inv_skin_wear];
            premium_acc = InventoryPlayer[playerid][new_slot][inv_acc_premium];
            premium_skin = InventoryPlayer[playerid][new_slot][inv_skin_premium];
            for(new i = 8; i != -1; i--) accPos[i] = InventoryPlayer[playerid][new_slot][inv_acc_pos][i];

            sellPrice = InventoryPlayer[playerid][new_slot][inv_market_sell_price];
            sellAmount = InventoryPlayer[playerid][new_slot][inv_market_sell_amount];
        }

        InventoryPlayer[playerid][new_slot][inv_mysql_id]       = InventoryPlayer[playerid][old_slot][inv_mysql_id];
        InventoryPlayer[playerid][new_slot][inv_slot_id]        = new_slot;
        InventoryPlayer[playerid][new_slot][inv_item_id]        = InventoryPlayer[playerid][old_slot][inv_item_id];
        InventoryPlayer[playerid][new_slot][inv_amount]         = InventoryPlayer[playerid][old_slot][inv_amount];
        InventoryPlayer[playerid][new_slot][inv_status_use]     = InventoryPlayer[playerid][old_slot][inv_status_use];
        InventoryPlayer[playerid][new_slot][inv_acc_slot]       = InventoryPlayer[playerid][old_slot][inv_acc_slot];
        InventoryPlayer[playerid][new_slot][inv_acc_mt][0]      = InventoryPlayer[playerid][old_slot][inv_acc_mt][0];
        InventoryPlayer[playerid][new_slot][inv_acc_mt][1]      = InventoryPlayer[playerid][old_slot][inv_acc_mt][1];
        InventoryPlayer[playerid][new_slot][inv_acc_wear]       = InventoryPlayer[playerid][old_slot][inv_acc_wear];
        InventoryPlayer[playerid][new_slot][inv_skin_wear]      = InventoryPlayer[playerid][old_slot][inv_skin_wear];
        InventoryPlayer[playerid][new_slot][inv_acc_premium]    = InventoryPlayer[playerid][old_slot][inv_acc_premium];
        InventoryPlayer[playerid][new_slot][inv_skin_premium]   = InventoryPlayer[playerid][old_slot][inv_skin_premium];
        for(new i = 8; i != -1; i--) InventoryPlayer[playerid][new_slot][inv_acc_pos][i] = InventoryPlayer[playerid][old_slot][inv_acc_pos][i];

        InventoryPlayer[playerid][new_slot][inv_market_buy_price] = InventoryPlayer[playerid][old_slot][inv_market_buy_price];
        InventoryPlayer[playerid][new_slot][inv_market_buy_amount] = InventoryPlayer[playerid][old_slot][inv_market_buy_amount];
        InventoryPlayer[playerid][new_slot][inv_market_sell_price] = InventoryPlayer[playerid][old_slot][inv_market_sell_price];
        InventoryPlayer[playerid][new_slot][inv_market_sell_amount] = InventoryPlayer[playerid][old_slot][inv_market_sell_amount];

        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `slot_id` = %d WHERE `mysql_id` = %d",
            InventoryPlayer[playerid][new_slot][inv_slot_id], InventoryPlayer[playerid][new_slot][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        if(mysqlID != INVALID_MYSQL_ID)
        {
            InventoryPlayer[playerid][old_slot][inv_mysql_id]       = mysqlID;
            InventoryPlayer[playerid][old_slot][inv_slot_id]        = old_slot;
            InventoryPlayer[playerid][old_slot][inv_item_id]        = itemID;
            InventoryPlayer[playerid][old_slot][inv_amount]         = amount;
            InventoryPlayer[playerid][old_slot][inv_acc_slot]       = accSlot;
            InventoryPlayer[playerid][old_slot][inv_status_use]     = statusUse;
            InventoryPlayer[playerid][old_slot][inv_acc_mt][0]      = accMT1;
            InventoryPlayer[playerid][old_slot][inv_acc_mt][1]      = accMT2;
            InventoryPlayer[playerid][old_slot][inv_acc_wear]       = accWear;
            InventoryPlayer[playerid][old_slot][inv_skin_wear]      = skinWear;
            InventoryPlayer[playerid][old_slot][inv_acc_premium]    = premium_acc;
            InventoryPlayer[playerid][old_slot][inv_skin_premium]   = premium_skin;
            for(new i = 8; i != -1; i--) InventoryPlayer[playerid][old_slot][inv_acc_pos][i] = accPos[i];

            InventoryPlayer[playerid][old_slot][inv_market_sell_price]  = sellPrice;
            InventoryPlayer[playerid][old_slot][inv_market_sell_amount] = sellAmount;

            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `slot_id` = %d WHERE `mysql_id` = %d",
                InventoryPlayer[playerid][old_slot][inv_slot_id], InventoryPlayer[playerid][old_slot][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            if(ItemsInfo[InventoryPlayer[playerid][old_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
                InventoryPlayer[playerid][old_slot][inv_status_use] > 0)
                AttachPlayerAccessories(playerid, old_slot, .slot_use = accSlot);
        }
        else Equipment_ClearSlot(playerid, old_slot);

        if(buyPrice > 0 && buyAmount > 0)
        {
            InventoryPlayer[playerid][old_slot][inv_item_id] = itemID;
            InventoryPlayer[playerid][old_slot][inv_market_buy_price]  = buyPrice;
            InventoryPlayer[playerid][old_slot][inv_market_buy_amount] = buyAmount;
        }

        if(ItemsInfo[InventoryPlayer[playerid][new_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
            InventoryPlayer[playerid][new_slot][inv_status_use] > 0)
            AttachPlayerAccessories(playerid, new_slot, .slot_use = InventoryPlayer[playerid][new_slot][inv_acc_slot]);

        Equipment_Update(playerid);
    }
}

Equipment_AccessoriesChangePos(playerid, old_slot_use, new_slot_use, bool:isExchange)
{
    new old_slot_id = Equipment_GetAccSlotUse(playerid, old_slot_use),
        new_slot_id = Equipment_GetAccSlotUse(playerid, new_slot_use);

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && 
        ItemsInfo[InventoryPlayer[playerid][old_slot_id][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid != GetPVarInt(playerid, #VEHICLEID_ACCESSORIES)) return 1;

        DestroyDynamicObject(veh_info[vehicleid][v_attach_object][old_slot_use]);
        veh_info[vehicleid][v_attach_object][old_slot_use] = INVALID_OBJECT_ID;

        InventoryPlayer[playerid][old_slot_id][inv_acc_slot] = new_slot_use;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `acc_slot` = %d WHERE `mysql_id` = %d",
            new_slot_use, InventoryPlayer[playerid][old_slot_id][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        if(isExchange &&
            ItemsInfo[InventoryPlayer[playerid][new_slot_id][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE)
        {
            DestroyDynamicObject(veh_info[vehicleid][v_attach_object][new_slot_use]);
            veh_info[vehicleid][v_attach_object][new_slot_use] = INVALID_OBJECT_ID;

            InventoryPlayer[playerid][new_slot_id][inv_acc_slot] = old_slot_use;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `acc_slot` = %d WHERE `mysql_id` = %d",
                old_slot_use, InventoryPlayer[playerid][new_slot_id][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            veh_info[vehicleid][v_attach_object][old_slot_use] = CreateDynamicObject(ItemsInfo[InventoryPlayer[playerid][new_slot_id][inv_item_id]][iModel], 
            InventoryPlayer[playerid][new_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][2], 
            InventoryPlayer[playerid][new_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][5]);

            AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][old_slot_use], vehicleid,
                InventoryPlayer[playerid][new_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][2],
                InventoryPlayer[playerid][new_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][new_slot_id][inv_acc_pos][5]);
        }

        veh_info[vehicleid][v_attach_object][new_slot_use] = CreateDynamicObject(ItemsInfo[InventoryPlayer[playerid][old_slot_id][inv_item_id]][iModel], 
        InventoryPlayer[playerid][old_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][2], 
        InventoryPlayer[playerid][old_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][5]);

        AttachDynamicObjectToVehicle(veh_info[vehicleid][v_attach_object][new_slot_use], vehicleid,
            InventoryPlayer[playerid][old_slot_id][inv_acc_pos][0], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][1], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][2],
            InventoryPlayer[playerid][old_slot_id][inv_acc_pos][3], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][4], InventoryPlayer[playerid][old_slot_id][inv_acc_pos][5]);

        Streamer_Update(playerid, STREAMER_TYPE_OBJECT);

        Equipment_AccessoriesUse(playerid);
    }
    if(ItemsInfo[InventoryPlayer[playerid][old_slot_id][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        if(!isExchange)
        {
            if(IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][old_slot_id][inv_acc_slot])) RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][old_slot_id][inv_acc_slot]);
            if(!AttachPlayerAccessories(playerid, old_slot_id, .slot_use = new_slot_use)) return 1;
        }
        else
        {
            if(ItemsInfo[InventoryPlayer[playerid][new_slot_id][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES)
            {
                if(IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][old_slot_id][inv_acc_slot]))
                    RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][old_slot_id][inv_acc_slot]);
                if(IsPlayerAttachedObjectSlotUsed(playerid, InventoryPlayer[playerid][new_slot_id][inv_acc_slot]))
                    RemovePlayerAttachedObject(playerid, InventoryPlayer[playerid][new_slot_id][inv_acc_slot]);

                if(!AttachPlayerAccessories(playerid, new_slot_id, .slot_use = old_slot_use)) return 1;
                if(!AttachPlayerAccessories(playerid, old_slot_id, .slot_use = new_slot_use)) return 1;
            }
        }
    }
    return 1;
}

Equipment_TDClearSlotRight(playerid, i)
{
    PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+i], false);
    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 0);
    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 0.0000, 50.0000);
    PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], "_");
}

Equipment_TDClearSlotLeft(playerid, i)
{
    PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+i], false);
    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 0);
    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], 0.0000, 0.0000, 0.0000, 50.0000);
    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], "_");
}

/////////////////////////////////////////////////////////////////////////////
ShowPlayerEquipmentInfo(playerid, slot_id)
{
    new itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    if(!itemID) return SendError(playerid, "ID предмета не определено.");
    SetPVarInt(playerid,  #EQ_CONTROL_BLOCK, true);
    STRING_GLOBAL[0] = EOS;
    switch(ItemsInfo[itemID][iType])
    {
        case TYPE_ITEMS_INVENTORY:
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                Название: "I"%s"W"\n\n\
                Количество: "I"%d шт."W"\n\n\
                Описание:\n\n%s",
                ItemsInfo[itemID][iName], InventoryPlayer[playerid][slot_id][inv_amount], ItemsInfo[itemID][iInfo]);

            switch(itemID)
            {
                case 718 .. 728:
                {
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\n\n%s\n\n{"#cLIGHTRED"}Рекомендуемая стоимость исходя из шансов выпадения и способа получения: "W"%d$.\n\n{"#cLIGHTRED"}Шанс выпадения уникального приза: "W"%.2f процента.", STRING_GLOBAL, GetCasketInfo(itemID), ItemsInfo[itemID][iPrice], ItemsInfo[itemID][iCasketChance]);
                }
                case 730, 731:
                {
                    strcat(STRING_GLOBAL, "\n\n");
                    for(new i; i < sizeof(BattlePassInfoList); i++) strcat(STRING_GLOBAL, BattlePassInfoList[i]);
                }
                case 732, 738:
                {
                    strcat(STRING_GLOBAL, "\n\n");
                    for(new i; i < sizeof(ADDVIPInfo); i++) strcat(STRING_GLOBAL, ADDVIPInfo[i]);
                }
            }
        }
        case TYPE_ITEMS_ACCESSORIES:
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                Название: "I"\"%s\""W"\n\
                Состояние: "I"%.1f"W"\n\n\
                Цвет #1: {%06x}%s"W"\n\
                Цвет #2: {%06x}%s"W"\n\n\
                Стоимость: "I"%d$"W"\n\n\
                Премиум: "I"%s"W"\n\n\
                Описание:\n\n%s",
                ItemsInfo[itemID][iName],
                InventoryPlayer[playerid][slot_id][inv_acc_wear],
                InventoryPlayer[playerid][slot_id][inv_acc_mt][0] == 0 ? 0xFFFFFF : AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acColorRBG] & 0xFFFFFF,
                AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acName],
                InventoryPlayer[playerid][slot_id][inv_acc_mt][1] == 0 ? 0xFFFFFF : AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acColorRBG] & 0xFFFFFF,
                AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acName],
                ItemsInfo[itemID][iPrice], InventoryPlayer[playerid][slot_id][inv_acc_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"", ItemsInfo[itemID][iInfo]);
        }
        case TYPE_ITEMS_SKINS:
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                Название: "I"\"%s\""W"\n\
                Состояние: "I"%.1f"W"\n\n\
                Премиум: "I"%s"W"\n\n\
                Стоимость: "I"%d$"W"\n\n\
                Описание:\n\n%s",
                ItemsInfo[itemID][iName],
                InventoryPlayer[playerid][slot_id][inv_skin_wear],
                InventoryPlayer[playerid][slot_id][inv_skin_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"",
                ItemsInfo[itemID][iPrice],
                ItemsInfo[itemID][iInfo]);
        }
        case TYPE_ITEMS_VEHICLE_TUNE:
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                Название: "I"%s"W"\n\n\
                Описание:\n\n%s",
                ItemsInfo[itemID][iName], ItemsInfo[itemID][iInfo]);
        }
    }
    ShowPlayerDialog(playerid, D_EQUIPMENT_INFO, DIALOG_STYLE_MSGBOX, ""I"Содержимое", STRING_GLOBAL, "Закрыть", "");
    return 1;
}

UsePlayerEquipment(playerid, slot_id)
{
    new itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    switch(ItemsInfo[itemID][iType])
    {
        case TYPE_ITEMS_INVENTORY:
        {
            UsePlayerInventoryItems(playerid, itemID);
        }
        case TYPE_ITEMS_ACCESSORIES:
        {
            UsePlayerAccessories(playerid, slot_id, InventoryPlayer[playerid][slot_id][inv_acc_slot], !InventoryPlayer[playerid][slot_id][inv_status_use]);
        }
        case TYPE_ITEMS_SKINS:
        {
            SetPlayerSkinUse(playerid, slot_id);
        }
        case TYPE_ITEMS_VEHICLE_TUNE:
        {
            UseVehicleAccessories(playerid, slot_id, -1);
        }
    }
}
////////////////////////////////////////////////////////////////////////
Equipment_InvLeft(playerid, type_inv)
{
    if(type_inv == EQUIPMENT_INVENTORY_HOUSE)
    {
        if(p_temp[playerid][p_house_id] == INVALID_HOUSE_ID)
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
            return SendError(playerid, "Код ошибки: 1995 (Обратитесь к администрации)");
        }
    }
    else if(type_inv == EQUIPMENT_INVENTORY_BOOT)
    {
        if(!GetPVarInt(playerid, #VEHICLEID_BOOT))
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
            return SendError(playerid, "Код ошибки: 1996 (Обратитесь к администрации)");
        }
    }
    else if(type_inv == EQUIPMENT_INVENTORY_TRASHBOX)
    {
        if(!(0 <= p_temp[playerid][trash_id] < sizeof(TrashInfo)))
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
            return SendError(playerid, "Код ошибки: 1997 (Обратитесь к администрации)");
        }
    }
    else if(type_inv == EQUIPMENT_INVENTORY_FAMILY)
    {
        if(GetPlayerFamilyID(playerid) == -1)
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
            return SendError(playerid, "Код ошибки: 1998 (Обратитесь к администрации)");
        }
    }

    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
    if(min_slot >= max_slot) return SendError(playerid, "Произошла не известная ошибка 242158");
    min_slot++;

    min_slot += (p_temp[playerid][inv_list_page][1]-1)*20;

    new itemId, amount;
    for(new i = 19; i != -1; i--)
    {
        if(InventoryPlayer[playerid][min_slot+i][inv_mysql_id] == INVALID_MYSQL_ID)
        {
            Equipment_TDClearSlotLeft(playerid, i);
            PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][5+i]);
            continue;
        }
        itemId = InventoryPlayer[playerid][min_slot+i][inv_item_id];
        amount = InventoryPlayer[playerid][min_slot+i][inv_amount];

        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], ItemsInfo[itemId][iModel] == 74 ? 0 : ItemsInfo[itemId][iModel]);
        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], ItemsInfo[itemId][iObjectPos][0], ItemsInfo[itemId][iObjectPos][1], ItemsInfo[itemId][iObjectPos][2], ItemsInfo[itemId][iObjectPos][3]);

        if(ItemsInfo[itemId][iType] == TYPE_ITEMS_INVENTORY)
            f(STRING_GLOBAL, "%s%d", InventoryPlayer[playerid][min_slot+i][inv_freeze_time] > timestamp ? "~r~" : "", amount);
        else
            f(STRING_GLOBAL, "%sID: %d", InventoryPlayer[playerid][min_slot+i][inv_freeze_time] > timestamp ? "~r~" : "", itemId);
        PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], STRING_GLOBAL);

        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+i], true);
        PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][5+i]);
    }
    return 1;
}
