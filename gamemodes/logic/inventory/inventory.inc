new TentIDx[MAX_PLAYERS];

ShowPlayerInventory(playerid)
{
	if(IsTDVisible(playerid) != -1) return 1;
    ShowTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
	return 1;
}

GetInventoryAmount(playerid, item_id, type_inv = EQUIPMENT_INVENTORY_PLAYER)
{
    new iAmountItems, max_slot, min_slot;
    GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
    if(min_slot >= max_slot) return 0;
    if(min_slot < max_slot)
    {
        for(new i = max_slot; i != min_slot; i--)
        {
            if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && InventoryPlayer[playerid][i][inv_item_id] == item_id)
                iAmountItems += InventoryPlayer[playerid][i][inv_amount];
        }
    }
    return iAmountItems;
}

GetInventoryFreeItems(playerid, item_id, type_inv = EQUIPMENT_INVENTORY_PLAYER)
{
    new max_value, max_slot, min_slot;
    GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
    if(min_slot >= max_slot) return 0;
    for(new i = max_slot; i != min_slot; i--)
    {
        if( InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            InventoryPlayer[playerid][i][inv_item_id] == item_id &&
            ItemsInfo[item_id][iType] == TYPE_ITEMS_INVENTORY)
        {
            max_value += (ItemsInfo[item_id][iMax] - InventoryPlayer[playerid][i][inv_amount]);
        }
        if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID)
        {
            max_value += ItemsInfo[item_id][iMax];
        }
    }
    return max_value;
}

InventoryDivide(playerid, slot_id, value)
{
    new free_slot = GetFreeSlotInventory(playerid, EQUIPMENT_INVENTORY_PLAYER);
    if(free_slot == -1) return SendError(playerid, "В инвентаре нет свободного места.");
    if(InventoryPlayer[playerid][slot_id][inv_amount] < value)
        return SendError(playerid, "Произошла ошибка: 10.01.22-1444");
    if(value < 1)
        return SendError(playerid, "Произошла ошибка: 10.01.22-1445");
    //give
    InventoryPlayer[playerid][free_slot][inv_amount]     = value;
    InventoryPlayer[playerid][free_slot][inv_slot_id]    = free_slot;
    InventoryPlayer[playerid][free_slot][inv_item_id]    = InventoryPlayer[playerid][slot_id][inv_item_id];
    InventoryPlayer[playerid][free_slot][inv_status_use] = 0;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `inventory` (`slot_id`, `owner_id`, `owner_type`, `item_id`, `amount`) VALUES (%d, %d, %d, %d, %d)",
       InventoryPlayer[playerid][free_slot][inv_slot_id], p_info[playerid][ID], INVENTORY_OWNER_TYPE_PLAYER,
       InventoryPlayer[playerid][free_slot][inv_item_id], InventoryPlayer[playerid][free_slot][inv_amount]);
    mysql_tquery(con_bd, STRING_GLOBAL, "GetInventoryMysqlID", "iii", playerid, p_info[playerid][ID], free_slot);

    //take
    InventoryPlayer[playerid][slot_id][inv_amount] -= value;
    if(InventoryPlayer[playerid][slot_id][inv_amount] > 0)
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d",
            InventoryPlayer[playerid][slot_id][inv_amount], InventoryPlayer[playerid][slot_id][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
    }
    else
    {
        if(InventoryPlayer[playerid][slot_id][inv_amount] < 0) SendError(playerid, "Багоюз! Обратитесь на форум, дабы избежать бан! КОД: 1001-1500.");
        DropPlayerEquipment(playerid, slot_id);
        Equipment_Update(playerid);
    }
    Log(LOG_player, INFO, "%s[%d](%s %s) разделил <%s> из %d ед на %d ед. и %d ед. | #Inventory#Div",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iName],
        InventoryPlayer[playerid][slot_id][inv_amount]+value, InventoryPlayer[playerid][free_slot][inv_amount], value);
    return 1;
}

InventoryMerge(playerid, old_slot, new_slot)
{
    new iFreeItems = ItemsInfo[InventoryPlayer[playerid][new_slot][inv_item_id]][iMax]-InventoryPlayer[playerid][new_slot][inv_amount];

    if(iFreeItems >= InventoryPlayer[playerid][old_slot][inv_amount])
    {
        InventoryPlayer[playerid][new_slot][inv_amount] += InventoryPlayer[playerid][old_slot][inv_amount];
        InventoryPlayer[playerid][old_slot][inv_amount] = 0;

        if(InventoryPlayer[playerid][old_slot][inv_market_buy_price] > 0 || InventoryPlayer[playerid][old_slot][inv_market_buy_amount] > 0)
        {
            InventoryPlayer[playerid][new_slot][inv_market_buy_price] = InventoryPlayer[playerid][old_slot][inv_market_buy_price];
            InventoryPlayer[playerid][new_slot][inv_market_buy_amount] = InventoryPlayer[playerid][old_slot][inv_market_buy_amount];
        }
        if(InventoryPlayer[playerid][old_slot][inv_market_sell_price] > 0 || InventoryPlayer[playerid][old_slot][inv_market_sell_amount] > 0)
        {
            InventoryPlayer[playerid][new_slot][inv_market_sell_price] = InventoryPlayer[playerid][old_slot][inv_market_sell_price];
            InventoryPlayer[playerid][new_slot][inv_market_sell_amount] = InventoryPlayer[playerid][old_slot][inv_market_sell_amount];
        }

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d",
            InventoryPlayer[playerid][new_slot][inv_amount], InventoryPlayer[playerid][new_slot][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);

        DropPlayerEquipment(playerid, old_slot);
    }
    else
    {
        InventoryPlayer[playerid][new_slot][inv_amount] += iFreeItems;
        InventoryPlayer[playerid][old_slot][inv_amount] -= iFreeItems;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d;\
            UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d;",
            InventoryPlayer[playerid][new_slot][inv_amount], InventoryPlayer[playerid][new_slot][inv_mysql_id],
            InventoryPlayer[playerid][old_slot][inv_amount], InventoryPlayer[playerid][old_slot][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
    }
    Log(LOG_player, INFO, "%s[%d](%s %s) обьеденил <%s> в %d ед. | #Inventory#Uni",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        ItemsInfo[InventoryPlayer[playerid][new_slot][inv_item_id]][iName],
        InventoryPlayer[playerid][new_slot][inv_amount]);
    return 1;
}

GetFreeSlotInventory(playerid, type_inv)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
    max_slot++, min_slot++;
    if(min_slot >= max_slot) return -1;

    for(new i = min_slot; i < max_slot; i++)
    {
        if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID &&
            InventoryPlayer[playerid][i][inv_item_id] == 0 &&
            InventoryPlayer[playerid][i][inv_market_sell_price] == 0 &&
            InventoryPlayer[playerid][i][inv_market_buy_price] == 0)
        {
            return i;
        }
    }
    return -1;
}

forward GetInventoryMysqlID(playerid, mysql_id, slot_id);
public GetInventoryMysqlID(playerid, mysql_id, slot_id)
{
    if(p_info[playerid][ID] != mysql_id) return 1;
    InventoryPlayer[playerid][slot_id][inv_mysql_id] = cache_insert_id();

    new slot_skin_id = GetPVarInt(playerid, #INV_SKIN_USE)-1;
    if(slot_skin_id == slot_id)
    {
        SetPlayerSkinUse(playerid, slot_skin_id);
        DeletePVar(playerid, #INV_SKIN_USE);
    }

    Equipment_Update(playerid);
    return 1;
}
////////////////////////////////////////////////
/*
TransferPlayerSkins(playerid)
{
    new status_skin;
    for(new i; i < MAX_PLAYER_SKINS; i++)
    {
        if(p_info[playerid][skins][i] == 0) continue;
        status_skin = i == p_info[playerid][active_skin_id] ? 1 : 0;
        if(GivePlayerInventory(playerid, p_info[playerid][skins][i], .reason = "перенос из old inventory", .status_use = status_skin))
        {
            if(status_skin)
            {
                p_info[playerid][active_skin_id] = -1;
                MysqlUpdatePlayerInt(playerid, "active_skin_id", p_info[playerid][active_skin_id]);
            }
            p_info[playerid][skins][i] = 0;
        }
    }

    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_PLAYER_SKINS; i++) f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, p_info[playerid][skins][i], i == MAX_PLAYER_SKINS-1 ? "":"|");
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `skins` = '%s' WHERE `id` = %d", STRING_GLOBAL, p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}
*/

SetPlayerSkinUse(playerid, new_slot)
{
    if(!p_info[playerid][loggedIn]) return 1;

    if(p_temp[playerid][Work_ID] != NONE_WORK) 
        return SendError(playerid, "Во время работы нельзя менять скин.");

    if(ItemsInfo[InventoryPlayer[playerid][new_slot][inv_item_id]][iType] != TYPE_ITEMS_SKINS)
        return SendError(playerid, "Тип не соответствует одежде. Обратитесь на форум.");

    if(InventoryPlayer[playerid][new_slot][inv_status_use] == 0 && InventoryPlayer[playerid][new_slot][inv_skin_wear] == 0)
        return SendError(playerid, "Данная одежда слишком грязная, постирайте её в прачечной.");

    InventoryPlayer[playerid][new_slot][inv_status_use] = !InventoryPlayer[playerid][new_slot][inv_status_use];

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `status_use` = %d WHERE `mysql_id` = %d",
        InventoryPlayer[playerid][new_slot][inv_status_use], InventoryPlayer[playerid][new_slot][inv_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot < max_slot)
    {
        for(new i = max_slot; i != min_slot; i--)
        {
            if(i == new_slot) continue;
            if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
                ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_SKINS &&
                InventoryPlayer[playerid][i][inv_status_use] == 1)
            {
                InventoryPlayer[playerid][i][inv_status_use] = 0;

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `status_use` = %d WHERE `mysql_id` = %d",
                    InventoryPlayer[playerid][i][inv_status_use], InventoryPlayer[playerid][i][inv_mysql_id]);
                mysql_tquery(con_bd, STRING_GLOBAL);
                break;
            }
        }
    }
    SetPlayerSkinEx(playerid);

    Equipment_Update(playerid);
    Equipment_Info(playerid);
    return 1;
}

SetPlayerSkinEx(playerid)
{
    if(p_info[playerid][member] > 0 && p_info[playerid][fwork] == true)
    {
        if(p_info[playerid][fskin] <= 0) SetPlayerFractionSkin(playerid);
        else SetPlayerSkin(playerid, p_info[playerid][fskin]);
    }
    else
    {
        new family_idx = p_temp[playerid][family_game_id],
            family_rang_id = GetFamilyRang(playerid)-1,
            skin_id = GetFamilySkinID(p_info[playerid][sex], family_idx, family_rang_id);
        if(p_info[playerid][p_settings][SKIN_DEFAULT] == 1 && family_idx != -1 && skin_id != INVALID_SKIN_ID)
            SetPlayerSkin(playerid, skin_id);
        else
        {
            new skin_id = GetPlayerUseSkinID(playerid), playerState = GetPlayerState(playerid);
            if(skin_id == INVALID_SKIN_ID || 
                skin_id > 311 && (playerState != PLAYER_STATE_SPAWNED && 
                    playerState != PLAYER_STATE_SPECTATING && 
                    !(PLAYER_STATE_ONFOOT <= playerState <= PLAYER_STATE_ENTER_VEHICLE_PASSENGER)))
                skin_id = p_info[playerid][sex] == 2 ? 252 : 251;
            if(skin_id == 74) skin_id = 0;
            SetPlayerSkin(playerid, skin_id);
        }
    }
    if(p_temp[playerid][rob_house_idx] == -1 && 
        p_temp[playerid][rob_bank_idx] == -1 &&
        p_temp[playerid][rob_fuel_idx] == -1 &&
        p_temp[playerid][cossack_robbers_register] != 2)
        AttachToPlayerAccOrCostume(playerid, INVALID_PLAYER_ID);
    return 1;
}

GetPlayerUseSkinID(playerid)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot >= max_slot) return INVALID_SKIN_ID;//SendError(playerid, "Количество слотов инвентаря не определено.");
    for(new i = max_slot; i != min_slot; i--)
    {
        if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_SKINS &&
            InventoryPlayer[playerid][i][inv_status_use] != 0)
        return ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iModel];
    }
    return INVALID_SKIN_ID;
}
////////////////////////////////////////////////
UsePlayerInventoryItems(playerid, item_id)
{
	if(!GetInventoryAmount(playerid, item_id)) return SendError(playerid, "У Вас нет \"%s\".", ItemsInfo[item_id][iName]);
	switch(item_id)
	{
		case 627, 628, 634, 637, 635, 640, 641, 645, 647 .. 651, 682, 685 .. 687, 689 .. 691, 700 .. 717, 734: return SendError(playerid, "Данный предмет нельзя использовать.");
		case 629: callcmd::usedrugs(playerid, "/0");
		case 646: callcmd::cdrugs(playerid, "/0");
		case 630: callcmd::pour(playerid, "/0");
		case 631: callcmd::repaircar(playerid, "/0");
		case 632: callcmd::healme(playerid, "/0");
		case 633: callcmd::mask(playerid, "/0");
		case 636: callcmd::tie(playerid, "/0");
		case 638: callcmd::eat(playerid, "1");
		case 639: callcmd::eat(playerid, "2");
		case 642..644:
		{
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
			SetTimerEx("ShowPlayerRoulette", 500, false, "dd", playerid, item_id-(TRANSFER_ITEMS+15));
		}
		case 652: callcmd::smoke(playerid, "/0");
		case 653:
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
            callcmd::hookah(playerid, "/0");
        }
        case 654 .. 673:
		{
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
			SetTimerEx("ShowPlayerCase", 500, false, "dd", playerid, item_id-(TRANSFER_ITEMS+27));
		}
		case 674 .. 678:
		{
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
			SetTimerEx("ShowPlayerPhone", 500, false, "dd", playerid, item_id);
		}
		case 679, 680:
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
            callcmd::tent(playerid, "/0");
        }
		case 681: callcmd::ipremium(playerid, "/0");
		case 683: callcmd::reanimate(playerid, "/0");
		case 684: callcmd::fish(playerid, "/0");
		case 688: callcmd::fish(playerid, "/0");
		case 694:
        {
            HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
            callcmd::bonfire(playerid, "/0");
        }
		case 695: callcmd::drink(playerid, "1");
		case 696: callcmd::drink(playerid, "2");
		case 697: callcmd::drink(playerid, "3");
		case 698: callcmd::drink(playerid, "4");
		case 699: callcmd::drink(playerid, "5");
        case 718 .. 728: OnPlayerOpenCasket(playerid, item_id);
        case 729: AccessoriesPlayerList(playerid, ACCESSORIES_ID_PREMIUM);
        case 730:
        {
            if(!GivePlayerInventory(playerid, 730, -1)) return 1;
            if(p_info[playerid][battle_info][0] == 1) return SendError(playerid, "У Вас уже есть Premium.");
            p_info[playerid][battle_info][0] = 1;
            SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_INFO);
            SendAccess(playerid, "Вы активировали Battle Pass Premium.");
        }
        case 731:
        {
            if(!GivePlayerInventory(playerid, 731, -1)) return 1;
            if(p_info[playerid][battle_info][1] == 1) return SendError(playerid, "У Вас уже есть ускоритель опыта.");
            p_info[playerid][battle_info][1] = 1;
            SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_INFO);
            SendAccess(playerid, "Вы активировали ускоритель опыта.");
        }
        case 732:
        {
            if(p_info[playerid][p_vip] != 3) return SendError(playerid, "У Вас нет \"VIP Gold\" или выше. Приобрести: /donate");
            if(!GivePlayerInventory(playerid, 732, -1)) return 1;
            new list_idx[] = {721, 722, 723, 724, 725, 726, 727, 728}, items_idx = list_idx[random(sizeof(list_idx))], items_count = 10;
            if(!GivePlayerInventory(playerid, items_idx, items_count)) return SendError(playerid, "В инвентаре нет места.");
            SendMes(playerid, COLOR_YELLOW, "[ИНВЕНТАРЬ]: "W"В инвентарь добавлен предмет {"#cYELLOW"}\"%s\"."W" Количество: {"#cYELLOW"}%d.", ItemsInfo[items_idx][iName], items_count);
            SendMesAll(COLOR_LIGHTRED, "[ADD VIP]: "W"%s [%d] активировал(-а) ADD VIP на 30 дней.", get_name(playerid), playerid);
            if(p_info[playerid][p_add_vip] != 1) p_info[playerid][p_add_vip_time] = 0;
            p_info[playerid][p_add_vip] = 1;
            if(p_info[playerid][p_add_vip_time]) p_info[playerid][p_add_vip_time] += 86400 * 30;
            else p_info[playerid][p_add_vip_time] = (timestamp + (86400 * 30));
        }
        case 733:
        {
            if(!GivePlayerInventory(playerid, 733, -1)) return 1;
            SendMesAll(COLOR_LIGHTRED, "[МУЗЫКАЛЬНАЯ ПОДПИСКА]: "W"%s [%d] активировал(-а) музыкальную подписку на 30 дней.", get_name(playerid), playerid);
            p_info[playerid][p_flin_music] = 1;
            if(p_info[playerid][p_flin_music_time]) p_info[playerid][p_flin_music_time] += 86400 * 30;
            else p_info[playerid][p_flin_music_time] = (timestamp + (86400 * 30));
        }
        case 735, 736:
        {
            SetPVarInt(playerid, "LoadResourcesHouseIDx", item_id);
            HousePlayerList(playerid, HOUSE_ID_RESOURCES);
        }
        case 737: SkinsPlayerList(playerid, SKINS_ID_PREMIUM);
        case 738:
        {
            if(p_info[playerid][p_vip] != 3) return SendError(playerid, "У Вас нет \"VIP Gold\" или выше. Приобрести: /donate");
            if(!GivePlayerInventory(playerid, 738, -1)) return 1;
            new list_idx[] = {721, 722, 723, 724, 725, 726, 727, 728}, items_idx = list_idx[random(sizeof(list_idx))], items_count = 10;
            if(!GivePlayerInventory(playerid, items_idx, items_count)) return SendError(playerid, "В инвентаре нет места.");
            SendMes(playerid, COLOR_YELLOW, "[ИНВЕНТАРЬ]: "W"В инвентарь добавлен предмет {"#cYELLOW"}\"%s\"."W" Количество: {"#cYELLOW"}%d.", ItemsInfo[items_idx][iName], items_count);
            SendMesAll(COLOR_LIGHTRED, "[ADD VIP]: "W"%s [%d] активировал(-а) ADD VIP навсегда.", get_name(playerid), playerid);
            if(p_info[playerid][p_add_vip] != 1) p_info[playerid][p_add_vip_time] = 0;
            p_info[playerid][p_add_vip] = 1;
            if(p_info[playerid][p_add_vip_time]) p_info[playerid][p_add_vip_time] += 86400 * 3650;
            else p_info[playerid][p_add_vip_time] = (timestamp + (86400 * 3650));
        }
        case 762..764: ShowMapBox(playerid, item_id-762);
        case 894: return SendInfo(playerid, "Яица можно использовать в обменнике или сыграть в битье яиц. Подробнее: /eggs.");
		default: return SendError(playerid, "Произошла ошибка, повторите операцию.");
	}
	return 1;
}

CMD:inventory(playerid, params[])
{
    //if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER) return SendError(playerid, "В транспортном средстве нельзя пользоваться инвентарем.");
	ShowPlayerInventory(playerid);
	return 1;
}
alias:inventory("inv", "acc", "accessories", "skin", "skins");

LoadPlayerInventory(playerid)
{
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "SELECT * FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d ORDER BY `slot_id` ASC", p_info[playerid][ID], INVENTORY_OWNER_TYPE_PLAYER);
    mysql_tquery(con_bd, STRING_GLOBAL, "LoadInventoryData", "iii", playerid, p_info[playerid][ID], EQUIPMENT_INVENTORY_PLAYER);
}

forward LoadInventoryData(playerid, mysql_id, type_inv);
public LoadInventoryData(playerid, mysql_id, type_inv)
{
    if(p_info[playerid][ID] != mysql_id) return 1;

    new rows;
    cache_get_row_count(rows);
    if(rows)
    {
        new data[128], temp_slot,
            max_slot, min_slot;
        GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
        if(min_slot >= max_slot) return 0;
        min_slot++, max_slot++;
        for(new i; i < rows; i++)
        {
            cache_get_value_name_int(i, "slot_id", temp_slot);
            if(temp_slot >= max_slot)
            {
                SendError(playerid, "Не возможно загрузить информацию слот: %d", temp_slot);
                continue;
            }
            InventoryPlayer[playerid][temp_slot][inv_slot_id] = temp_slot;
            cache_get_value_name_int(i, "mysql_id",         InventoryPlayer[playerid][temp_slot][inv_mysql_id]);
            cache_get_value_name_int(i, "item_id",          InventoryPlayer[playerid][temp_slot][inv_item_id]);
            cache_get_value_name_int(i, "amount",           InventoryPlayer[playerid][temp_slot][inv_amount]);
 
            if(ItemsInfo[InventoryPlayer[playerid][temp_slot][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES)
            {
                cache_get_value_name_int(i, "status_use",       InventoryPlayer[playerid][temp_slot][inv_status_use]);
                cache_get_value_name_int(i, "acc_slot",         InventoryPlayer[playerid][temp_slot][inv_acc_slot]);
 
                cache_get_value_name_int(i, "acc_mt1",          InventoryPlayer[playerid][temp_slot][inv_acc_mt][0]);
                cache_get_value_name_int(i, "acc_mt2",          InventoryPlayer[playerid][temp_slot][inv_acc_mt][1]);
                cache_get_value_name_float(i, "acc_wear",       InventoryPlayer[playerid][temp_slot][inv_acc_wear]);

                cache_get_value_name_int(i, "inv_acc_premium",  InventoryPlayer[playerid][temp_slot][inv_acc_premium]);

                cache_get_value_name(i, "acc_pos", data);
                sscanf(data, "p<|>a<f>[9]",                     InventoryPlayer[playerid][temp_slot][inv_acc_pos]);
            }
            else if(ItemsInfo[InventoryPlayer[playerid][temp_slot][inv_item_id]][iType] == TYPE_ITEMS_SKINS)
            {
                cache_get_value_name_int(i, "status_use",       InventoryPlayer[playerid][temp_slot][inv_status_use]);
                cache_get_value_name_float(i, "skin_wear",      InventoryPlayer[playerid][temp_slot][inv_skin_wear]);

                cache_get_value_name_int(i, "inv_skin_premium", InventoryPlayer[playerid][temp_slot][inv_skin_premium]);
            }
            else if(ItemsInfo[InventoryPlayer[playerid][temp_slot][inv_item_id]][iType] == TYPE_ITEMS_VEHICLE_TUNE)
            {
                cache_get_value_name_int(i, "status_use",       InventoryPlayer[playerid][temp_slot][inv_status_use]);
                if(InventoryPlayer[playerid][temp_slot][inv_status_use] != 0) 
                    SendDebug(playerid, "BUG status_use vehicle acc: mysq_id - %d", InventoryPlayer[playerid][temp_slot][inv_mysql_id]);
                cache_get_value_name_int(i, "acc_slot",         InventoryPlayer[playerid][temp_slot][inv_acc_slot]);
                if(InventoryPlayer[playerid][temp_slot][inv_acc_slot] != -1) 
                    SendDebug(playerid, "BUG acc_slot vehicle acc: mysq_id - %d", InventoryPlayer[playerid][temp_slot][inv_mysql_id]);

                cache_get_value_name(i, "acc_pos", data);
                sscanf(data, "p<|>a<f>[9]",                     InventoryPlayer[playerid][temp_slot][inv_acc_pos]);
            }
            cache_get_value_name_int(i, "freeze_time",          InventoryPlayer[playerid][temp_slot][inv_freeze_time]);
        }
        if(max_slot < MAX_ALL_EQUIPMENT)
        {
            for(new i = max_slot; i < MAX_ALL_EQUIPMENT; i++)
                Equipment_ClearSlot(playerid, i);
        }
    }
    if(type_inv == EQUIPMENT_INVENTORY_PLAYER)
        SetPlayerSkinEx(playerid);
    else
    {
        Equipment_Left(playerid, type_inv);
        new reload = GetPVarInt(playerid, #EQ_RELOAD);
        if(reload)
        {
            new slot_id = GetPVarInt(playerid, #EQ_SLOT_ID)-1,
                count = GetPVarInt(playerid, #EQ_COUNT);
            
            DeletePVar(playerid, #EQ_RELOAD);
            DeletePVar(playerid, #EQ_COUNT);
            DeletePVar(playerid, #EQ_SLOT_ID);
            
            if(slot_id < 0)
            {
                printf("crash: %s slot_id %d", get_name(playerid), slot_id);
                return SendError(playerid, "Не известная ошибка 250223");
            }
            //SendDebug(playerid, "mysql ID SELECT: %d", InventoryPlayer[playerid][slot_id][inv_mysql_id]);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `inventory` WHERE `mysql_id` = %d", InventoryPlayer[playerid][slot_id][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL, "IsValidItemDataBase", "iiiii", reload-1, playerid, p_info[playerid][ID], slot_id, count);
        }
    }
    return 1;
}

GivePlayerInventory(playerid, id, amount = 1, Float:wear = 100.0, mc1 = 0, mc2 = 0, reason[] = "", status_use = 0, type_inv = EQUIPMENT_INVENTORY_PLAYER, premium = 0)
{
    if(!(1 <= id < MAX_ITEMS))
    {
        SendError(playerid, "Не верный ID предмета.");
        return 0;
    }
    if(!(EQUIPMENT_INVENTORY_PLAYER <= type_inv < EQUIPMENT_INVENTORY_ALL))
    {
        SendError(playerid, "Не определен тип инвентаря.");
        return 0;
    }
    switch(ItemsInfo[id][iType])
    {
        case TYPE_ITEMS_INVENTORY, TYPE_ITEMS_VEHICLE_TUNE:
        {
            if(!ProcessChangePlayerInventory(playerid, id, amount, type_inv))
            {
                if(amount > 0) SendError(playerid, "В инвентаре нет места для предмета.");
                return 0;
            }
            if(type_inv == EQUIPMENT_INVENTORY_PLAYER && strlen(reason) != 0)
                Log(LOG_player, INFO, "%s[%d](%s %s) %s <%s> %d ед. за <%s> | #Inventory#Change",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                    amount < 0 ? "потерял" : "получил", ItemsInfo[id][iName], abs(amount), reason);
        }
        case TYPE_ITEMS_ACCESSORIES:
        {
            if(amount > 0)
            {
                if(!ProcessGivePlayerAccessories(playerid, id, wear, mc1, mc2, type_inv, premium))
                {
                    SendError(playerid, "В инвентаре нет места для аксессуара.");
                    return 0;
                }
                if(type_inv == EQUIPMENT_INVENTORY_PLAYER && strlen(reason) != 0)
                    Log(LOG_player, INFO, "%s[%d](%s %s) получил <%s>(%d) [%.1f] (%s/%s) за <%s> | #Inventory#Change",
                        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                        ItemsInfo[id][iName], id, wear, AccessoriesColorInfo[mc1][acName], AccessoriesColorInfo[mc2][acName], reason);
            }
            else
            {
                new max_slot, min_slot;
                GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
                if(min_slot >= max_slot) return 0;
                for(new i = max_slot; i != min_slot; i--)
                {
                    if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && InventoryPlayer[playerid][i][inv_item_id] == id)
                    {
                        DropPlayerEquipment(playerid, i);
                        return 1;
                    }
                }
                return 0;
            }
        }
        case TYPE_ITEMS_SKINS:
        {
            if(amount > 0)
            {
                if(!ProcessGivePlayerSkins(playerid, id, wear, status_use, type_inv, premium))
                {
                    SendError(playerid, "В инвентаре нет места для скина.");
                    return 0;
                }
                if(type_inv == EQUIPMENT_INVENTORY_PLAYER && strlen(reason) != 0)
                    Log(LOG_player, INFO, "%s[%d](%s %s) получил <%s>(%d) за <%s> | #Inventory#Change",
                        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                        ItemsInfo[id][iName], id, reason);
            }
            else
            {
                new max_slot, min_slot;
                GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
                if(min_slot >= max_slot) return 0;
                for(new i = max_slot; i != min_slot; i--)
                {
                    if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && InventoryPlayer[playerid][i][inv_item_id] == id)
                    {
                        DropPlayerEquipment(playerid, i);
                        return 1;
                    }
                }
                return 0;
            }
        }
        /*
        case TYPE_ITEMS_VEHICLE_TUNE:
        {
            if(!ProcessGiveVehicleTune(playerid, id, type_inv))
            {
                if(amount > 0) SendError(playerid, "В инвентаре нет места для предмета.");
                return 0;
            }
            if(type_inv == EQUIPMENT_INVENTORY_PLAYER && strlen(reason) != 0)
                Log(LOG_player, INFO, "%s[%d](%s %s) %s <%s> %d ед. за <%s> | #Inventory#Change",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                    amount < 0 ? "потерял" : "получил", ItemsInfo[id][iName], abs(amount), reason);
        }
        */
    }
    return 1;
}

ProcessChangePlayerInventory(playerid, item_id, amount, type_inv)
{
    if(amount == 0) return 0;
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, type_inv, max_slot, min_slot);
    if(min_slot >= max_slot) return 0;

    new iAmountItems, iTempAmount, iInvCells, arraySlots[MAX_ALL_EQUIPMENT],
        ownerID, ownerType;
    if(amount > 0) // код для выдачи предметов инвентаря
    {
        for(new i = max_slot; i != min_slot; i--)
        {
            if((InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID &&
                    (InventoryPlayer[playerid][i][inv_item_id] == 0 || InventoryPlayer[playerid][i][inv_item_id] == item_id)
                ) || (InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && InventoryPlayer[playerid][i][inv_item_id] == item_id))
            {
                iTempAmount = ItemsInfo[item_id][iMax]-InventoryPlayer[playerid][i][inv_amount];
                if(iTempAmount != 0)
                {
                    iAmountItems += iTempAmount;
                    arraySlots[iInvCells] = i;
                    iInvCells++;
                }
            }
        }
        if(amount > iAmountItems) return 0;
        for(new i = iInvCells-1; i != -1; i--)
        {
            iTempAmount = ItemsInfo[item_id][iMax]-InventoryPlayer[playerid][arraySlots[i]][inv_amount];
            if(amount < iTempAmount) iTempAmount = amount;
            InventoryPlayer[playerid][arraySlots[i]][inv_amount] += iTempAmount;
            amount -= iTempAmount;

            if(InventoryPlayer[playerid][arraySlots[i]][inv_mysql_id] == INVALID_MYSQL_ID)
            {
                InventoryPlayer[playerid][arraySlots[i]][inv_slot_id]    = arraySlots[i];
                InventoryPlayer[playerid][arraySlots[i]][inv_item_id]    = item_id;
                InventoryPlayer[playerid][arraySlots[i]][inv_status_use] =
                InventoryPlayer[playerid][arraySlots[i]][inv_freeze_time]    = 0;
                switch(type_inv)
                {
                    case EQUIPMENT_INVENTORY_PLAYER:
                    {
                        ownerID = p_info[playerid][ID];
                        ownerType = INVENTORY_OWNER_TYPE_PLAYER;
                    }
                    case EQUIPMENT_INVENTORY_HOUSE:
                    {
                        ownerID = p_temp[playerid][p_house_id];
                        ownerType = INVENTORY_OWNER_TYPE_HOUSE;
                    }
                    case EQUIPMENT_INVENTORY_BOOT:
                    {
                        ownerID = veh_info[GetPVarInt(playerid, #VEHICLEID_BOOT)][v_mysql_id];
                        ownerType = INVENTORY_OWNER_TYPE_VEHICLE;
                    }
                    case EQUIPMENT_INVENTORY_TRASHBOX:
                    {
                        ownerID = p_temp[playerid][trash_id];
                        ownerType = INVENTORY_OWNER_TYPE_TRASHBOX;
                        InventoryPlayer[playerid][arraySlots[i]][inv_freeze_time] = timestamp+(random(6)+2)*3600;
                    }
                    case EQUIPMENT_INVENTORY_FAMILY:
                    {
                        ownerID = p_info[playerid][family_id];
                        ownerType = INVENTORY_OWNER_TYPE_FAMILY;
                    }
                }

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `inventory` (`slot_id`, `owner_id`, `owner_type`, `item_id`, `amount`, `freeze_time`) VALUES (%d, %d, %d, %d, %d, %d)",
                   InventoryPlayer[playerid][arraySlots[i]][inv_slot_id], ownerID, ownerType,
                   InventoryPlayer[playerid][arraySlots[i]][inv_item_id], InventoryPlayer[playerid][arraySlots[i]][inv_amount],
                   InventoryPlayer[playerid][arraySlots[i]][inv_freeze_time]);
                mysql_tquery(con_bd, STRING_GLOBAL, "GetInventoryMysqlID", "iii", playerid, p_info[playerid][ID], arraySlots[i]);
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d",
                    InventoryPlayer[playerid][arraySlots[i]][inv_amount], InventoryPlayer[playerid][arraySlots[i]][inv_mysql_id]);
                mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
            }
            if(amount == 0) break;
        }
        if(amount > 0) {
            SendError(playerid, "Произошла не известная ошибка: 090122.");
            return 0;
        }
    }
    else
    { // для отнимания предметов инвентаря
        for(new i = max_slot; i != min_slot; i--)
        {
            if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && InventoryPlayer[playerid][i][inv_item_id] == item_id)
            {
                iAmountItems += InventoryPlayer[playerid][i][inv_amount];
                arraySlots[iInvCells] = i;
                iInvCells++;
            }
        }
        amount = abs(amount);
        if(iAmountItems < amount)
        {
            SendError(playerid, "В инвентаре нет достаточного количества предметов.");
            return 0;
        }
        for(new i = iInvCells-1; i != -1; i--)
        {
            iTempAmount = InventoryPlayer[playerid][arraySlots[i]][inv_amount];
            if(amount < iTempAmount) iTempAmount = amount;
            InventoryPlayer[playerid][arraySlots[i]][inv_amount] -= iTempAmount;
            amount -= iTempAmount;

            if(InventoryPlayer[playerid][arraySlots[i]][inv_amount] == 0)
                DropPlayerEquipment(playerid, arraySlots[i]);
            else
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d",
                    InventoryPlayer[playerid][arraySlots[i]][inv_amount], InventoryPlayer[playerid][arraySlots[i]][inv_mysql_id]);
                mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
            }
            if(amount == 0) break;
        }
        if(amount != 0) {
            SendError(playerid, "Произошла не известная ошибка: 19.01-17:00.");
            return 0;
        }
    }
    return 1;
}

ProcessGivePlayerAccessories(playerid, accessories_idx, Float:wear, mc1, mc2, type_inv, premium)
{
    new free_slot = GetFreeSlotInventory(playerid, type_inv);
    if(free_slot == -1) return 0;
    InventoryPlayer[playerid][free_slot][inv_slot_id]       = free_slot;
    InventoryPlayer[playerid][free_slot][inv_item_id]       = accessories_idx;
    InventoryPlayer[playerid][free_slot][inv_amount]        = 1;
    InventoryPlayer[playerid][free_slot][inv_status_use]    = 0;
    InventoryPlayer[playerid][free_slot][inv_acc_slot]      = -1;
    InventoryPlayer[playerid][free_slot][inv_acc_mt][0]     = mc1;
    InventoryPlayer[playerid][free_slot][inv_acc_mt][1]     = mc2;
    InventoryPlayer[playerid][free_slot][inv_acc_wear]      = wear;
    InventoryPlayer[playerid][free_slot][inv_skin_wear]     = 100.0;
    InventoryPlayer[playerid][free_slot][inv_acc_premium]   = premium;
    InventoryPlayer[playerid][free_slot][inv_skin_premium]  = 0;
    InventoryPlayer[playerid][free_slot][inv_freeze_time]   = 0;
    for(new i = 8; i != -1; i--) InventoryPlayer[playerid][free_slot][inv_acc_pos][i] = 0.0;

    new ownerID, ownerType;
    switch(type_inv)
    {
        case EQUIPMENT_INVENTORY_PLAYER:
        {
            ownerID = p_info[playerid][ID];
            ownerType = INVENTORY_OWNER_TYPE_PLAYER;
        }
        case EQUIPMENT_INVENTORY_HOUSE:
        {
            ownerID = p_temp[playerid][p_house_id];
            ownerType = INVENTORY_OWNER_TYPE_HOUSE;
        }
        case EQUIPMENT_INVENTORY_BOOT:
        {
            ownerID = veh_info[GetPVarInt(playerid, #VEHICLEID_BOOT)][v_mysql_id];
            ownerType = INVENTORY_OWNER_TYPE_VEHICLE;
        }
        case EQUIPMENT_INVENTORY_TRASHBOX:
        {
            ownerID = p_temp[playerid][trash_id];
            ownerType = INVENTORY_OWNER_TYPE_TRASHBOX;
            InventoryPlayer[playerid][free_slot][inv_freeze_time] = timestamp+(random(6)+2)*3600;
        }
        case EQUIPMENT_INVENTORY_FAMILY:
        {
            ownerID = p_info[playerid][family_id];
            ownerType = INVENTORY_OWNER_TYPE_FAMILY;
        }
    }

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "INSERT INTO `inventory` (`slot_id`, `owner_id`, `owner_type`, `item_id`, `amount`, `acc_mt1`, `acc_mt2`, `acc_wear`, `skin_wear`, `inv_acc_premium`, `inv_skin_premium`, `freeze_time`) \
            VALUES (%d, %d, %d, %d, %d, %d, %d, %f, 100.0, %d, 0, %d)",
        InventoryPlayer[playerid][free_slot][inv_slot_id], ownerID, ownerType,
        accessories_idx, InventoryPlayer[playerid][free_slot][inv_amount], mc1, mc2, InventoryPlayer[playerid][free_slot][inv_acc_wear], InventoryPlayer[playerid][free_slot][inv_acc_premium],
        InventoryPlayer[playerid][free_slot][inv_freeze_time]);
    mysql_tquery(con_bd, STRING_GLOBAL, "GetInventoryMysqlID", "iii", playerid, p_info[playerid][ID], free_slot);
    return 1;
}

ProcessGivePlayerSkins(playerid, skin_id, Float:wear, status_use, type_inv, premium)
{
    new free_slot = GetFreeSlotInventory(playerid, type_inv);
    if(free_slot == -1) return 0;
    InventoryPlayer[playerid][free_slot][inv_slot_id]       = free_slot;
    InventoryPlayer[playerid][free_slot][inv_item_id]       = skin_id;
    InventoryPlayer[playerid][free_slot][inv_amount]        = 1;
    InventoryPlayer[playerid][free_slot][inv_acc_slot]      = -1;
    InventoryPlayer[playerid][free_slot][inv_status_use]    =
    InventoryPlayer[playerid][free_slot][inv_acc_mt][0]     =
    InventoryPlayer[playerid][free_slot][inv_acc_mt][1]     = 0;
    InventoryPlayer[playerid][free_slot][inv_acc_wear]      = 100.0;
    InventoryPlayer[playerid][free_slot][inv_skin_wear]     = wear;
    InventoryPlayer[playerid][free_slot][inv_acc_premium]   = 0;
    InventoryPlayer[playerid][free_slot][inv_skin_premium]  = premium;
    InventoryPlayer[playerid][free_slot][inv_freeze_time]   = 0;
    for(new i = 8; i != -1; i--) InventoryPlayer[playerid][free_slot][inv_acc_pos][i] = 0.0;

    new ownerID, ownerType;
    switch(type_inv)
    {
        case EQUIPMENT_INVENTORY_PLAYER:
        {
            ownerID = p_info[playerid][ID];
            ownerType = INVENTORY_OWNER_TYPE_PLAYER;
        }
        case EQUIPMENT_INVENTORY_HOUSE:
        {
            ownerID = p_temp[playerid][p_house_id];
            ownerType = INVENTORY_OWNER_TYPE_HOUSE;
        }
        case EQUIPMENT_INVENTORY_BOOT:
        {
            ownerID = veh_info[GetPVarInt(playerid, #VEHICLEID_BOOT)][v_mysql_id];
            ownerType = INVENTORY_OWNER_TYPE_VEHICLE;
        }
        case EQUIPMENT_INVENTORY_TRASHBOX:
        {
            ownerID = p_temp[playerid][trash_id];
            ownerType = INVENTORY_OWNER_TYPE_TRASHBOX;
            InventoryPlayer[playerid][free_slot][inv_freeze_time] = timestamp+(random(6)+2)*3600;
        }
        case EQUIPMENT_INVENTORY_FAMILY:
        {
            ownerID = p_info[playerid][family_id];
            ownerType = INVENTORY_OWNER_TYPE_FAMILY;
        }
    }

    if(status_use)
        SetPVarInt(playerid, #INV_SKIN_USE, free_slot+1);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "INSERT INTO `inventory` (`slot_id`, `owner_id`, `owner_type`, `item_id`, `amount`, `acc_mt1`, `acc_mt2`, `acc_wear`, `skin_wear`, `inv_acc_premium`, `inv_skin_premium`, `freeze_time`) \
            VALUES (%d, %d, %d, %d, %d, 0, 0, 100.0, %f, 0, %d, %d)",
        InventoryPlayer[playerid][free_slot][inv_slot_id], ownerID, ownerType,
        skin_id, InventoryPlayer[playerid][free_slot][inv_amount], InventoryPlayer[playerid][free_slot][inv_skin_wear], InventoryPlayer[playerid][free_slot][inv_skin_premium],
        InventoryPlayer[playerid][free_slot][inv_freeze_time]);
    mysql_tquery(con_bd, STRING_GLOBAL, "GetInventoryMysqlID", "iii", playerid, p_info[playerid][ID], free_slot);
    return 1;
}

/*
ProcessGiveVehicleTune(playerid, tune_id, type_inv)
{
    new free_slot = GetFreeSlotInventory(playerid, type_inv);
    if(free_slot == -1) return 0;
    InventoryPlayer[playerid][free_slot][inv_slot_id]       = free_slot;
    InventoryPlayer[playerid][free_slot][inv_item_id]       = tune_id;
    InventoryPlayer[playerid][free_slot][inv_amount]        = 1;
    InventoryPlayer[playerid][free_slot][inv_acc_slot]      = -1;
    InventoryPlayer[playerid][free_slot][inv_status_use]    =
    InventoryPlayer[playerid][free_slot][inv_acc_mt][0]     =
    InventoryPlayer[playerid][free_slot][inv_acc_mt][1]     = 0;
    InventoryPlayer[playerid][free_slot][inv_acc_wear]      = 100.0;
    InventoryPlayer[playerid][free_slot][inv_skin_wear]     = 100.0;
    InventoryPlayer[playerid][free_slot][inv_acc_premium]   = 0;
    InventoryPlayer[playerid][free_slot][inv_skin_premium]  = 0;
    InventoryPlayer[playerid][free_slot][inv_freeze_time]   = 0;
    for(new i = 8; i != -1; i--) InventoryPlayer[playerid][free_slot][inv_acc_pos][i] = 0.0;

    new ownerID, ownerType;
    switch(type_inv)
    {
        case EQUIPMENT_INVENTORY_PLAYER:
        {
            ownerID = p_info[playerid][ID];
            ownerType = INVENTORY_OWNER_TYPE_PLAYER;
        }
        case EQUIPMENT_INVENTORY_HOUSE:
        {
            ownerID = p_temp[playerid][p_house_id];
            ownerType = INVENTORY_OWNER_TYPE_HOUSE;
        }
        case EQUIPMENT_INVENTORY_BOOT:
        {
            ownerID = veh_info[GetPVarInt(playerid, #VEHICLEID_BOOT)][v_mysql_id];
            ownerType = INVENTORY_OWNER_TYPE_VEHICLE;
        }
        case EQUIPMENT_INVENTORY_TRASHBOX:
        {
            ownerID = p_temp[playerid][trash_id];
            ownerType = INVENTORY_OWNER_TYPE_TRASHBOX;
            InventoryPlayer[playerid][free_slot][inv_freeze_time] = timestamp+(random(6)+2)*3600;
        }
        case EQUIPMENT_INVENTORY_FAMILY:
        {
            ownerID = p_info[playerid][family_id];
            ownerType = INVENTORY_OWNER_TYPE_FAMILY;
        }
    }

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "INSERT INTO `inventory` (`slot_id`, `owner_id`, `owner_type`, `item_id`, `amount`, `acc_mt1`, `acc_mt2`, `acc_wear`, `skin_wear`, `inv_acc_premium`, `inv_skin_premium`, `freeze_time`) \
            VALUES (%d, %d, %d, %d, %d, 0, 0, 100.0, %f, 0, %d, %d)",
        InventoryPlayer[playerid][free_slot][inv_slot_id], ownerID, ownerType,
        tune_id, InventoryPlayer[playerid][free_slot][inv_amount], InventoryPlayer[playerid][free_slot][inv_skin_wear], InventoryPlayer[playerid][free_slot][inv_skin_premium],
        InventoryPlayer[playerid][free_slot][inv_freeze_time]);
    mysql_tquery(con_bd, STRING_GLOBAL, "GetInventoryMysqlID", "iii", playerid, p_info[playerid][ID], free_slot);
    return 1;
}
*/

GetSlotInfoInventory(playerid, type_inv, &max_slot, &min_slot)
{
    max_slot = -1, min_slot = -1;
    switch(type_inv)
    {
        case EQUIPMENT_INVENTORY_PLAYER:
        {
            max_slot = p_info[playerid][inv_slots]-1;
        }
        case EQUIPMENT_INVENTORY_HOUSE:
        {
            new houseId = p_temp[playerid][p_house_id];
            if(houseId != INVALID_HOUSE_ID)
            {
                max_slot = MAX_PLAYER_EQUIPMENT+h_info[houseId][h_squar]*5-1;
                min_slot = MAX_PLAYER_EQUIPMENT-1;
            }
            else SendError(playerid, "Код ошибки: 1095 (Обратитесь к администрации)");
        }
        case EQUIPMENT_INVENTORY_BOOT:
        {
            new vehicleid = GetPVarInt(playerid, #VEHICLEID_BOOT);
            if(vehicleid != INVALID_VEHICLE_ID)
            {
                max_slot = MAX_PLAYER_EQUIPMENT;
                new vehicle_class = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_CLASS);
                switch(vehicle_class)
                {
                    case VEHICLE_CLASS_NOPE, VEHICLE_CLASS_C, VEHICLE_CLASS_B: max_slot += (vehicle_class+1)*5-1;
                    default: max_slot += 20-1;
                }
                min_slot = MAX_PLAYER_EQUIPMENT-1;
            }
            else SendError(playerid, "Код ошибки: 1096 (Обратитесь к администрации)");
        }
        case EQUIPMENT_INVENTORY_TRASHBOX:
        {
            new trashbox = p_temp[playerid][trash_id];
            if(trashbox != -1)
            {
                max_slot = MAX_ALL_EQUIPMENT-1;
                min_slot = MAX_PLAYER_EQUIPMENT-1;
            }
            else SendError(playerid, "Код ошибки: 1097 (Обратитесь к администрации)");
        }
        case EQUIPMENT_INVENTORY_FAMILY:
        {
            if(p_info[playerid][family_id] != -1)
            {
                max_slot = MAX_PLAYER_EQUIPMENT+20-1;
                min_slot = MAX_PLAYER_EQUIPMENT-1;
            }
            else SendError(playerid, "Код ошибки: 1098 (Обратитесь к администрации)");
        }
        default: return 1;
    }
    if(min_slot >= max_slot) SendError(playerid, "Неверное количество слотов инвентаря.");
    return 1;
}

ClearInventoryItems(owner_id, type_owner)
{
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d", owner_id, type_owner);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

forward IsValidItemDataBase(type_valid, playerid, mysql_id, slot_id, count);
public IsValidItemDataBase(type_valid, playerid, mysql_id, slot_id, count)
{
    if(p_info[playerid][ID] != mysql_id)
        return 1;
    new rows;
    cache_get_row_count(rows);
    if(!rows)
    {
        SendError(playerid, "Предмет не обнаружен. Скорее всего его уже нет в этом месте.");
    }
    else
    {
        cache_get_value_name_int(0, "mysql_id",         InventoryPlayer[playerid][slot_id][inv_mysql_id]);
        cache_get_value_name_int(0, "item_id",          InventoryPlayer[playerid][slot_id][inv_item_id]);
        cache_get_value_name_int(0, "amount",           InventoryPlayer[playerid][slot_id][inv_amount]);

        //SendDebug(playerid, "slot_id %d | mysql: %d", InventoryPlayer[playerid][slot_id][inv_mysql_id]);

        if(ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES)
        {
            cache_get_value_name_int(0, "status_use",       InventoryPlayer[playerid][slot_id][inv_status_use]);
            cache_get_value_name_int(0, "acc_slot",         InventoryPlayer[playerid][slot_id][inv_acc_slot]);
    
            cache_get_value_name_int(0, "acc_mt1",          InventoryPlayer[playerid][slot_id][inv_acc_mt][0]);
            cache_get_value_name_int(0, "acc_mt2",          InventoryPlayer[playerid][slot_id][inv_acc_mt][1]);
            cache_get_value_name_float(0, "acc_wear",       InventoryPlayer[playerid][slot_id][inv_acc_wear]);

            cache_get_value_name_int(0, "inv_acc_premium",  InventoryPlayer[playerid][slot_id][inv_acc_premium]);

            new data[128];
            cache_get_value_name(0, "acc_pos", data);
            sscanf(data, "p<|>a<f>[9]",                     InventoryPlayer[playerid][slot_id][inv_acc_pos]);
        }
        else if(ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iType] == TYPE_ITEMS_SKINS)
        {
            cache_get_value_name_int(0, "status_use",       InventoryPlayer[playerid][slot_id][inv_status_use]);
            cache_get_value_name_float(0, "skin_wear",      InventoryPlayer[playerid][slot_id][inv_skin_wear]);

            cache_get_value_name_int(0, "inv_skin_premium", InventoryPlayer[playerid][slot_id][inv_skin_premium]);
        }
        cache_get_value_name_int(0, "freeze_time",          InventoryPlayer[playerid][slot_id][inv_freeze_time]);

        switch(type_valid)
        {
            case 0: // put
            {
                if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT)
                {
                    new vehicleid = GetPVarInt(playerid, #VEHICLEID_BOOT),
                        Float:w_pos_x, Float:w_pos_y, Float:w_pos_z;
                    GetCoordBootVehicle(vehicleid, w_pos_x, w_pos_y, w_pos_z);
                    if(!IsPlayerInRangeOfPoint(playerid,2.5,w_pos_x, w_pos_y, w_pos_z))
                        return HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
                }
                new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                    itemType = ItemsInfo[itemID][iType];
                if(itemType == TYPE_ITEMS_INVENTORY && (itemID == 679 && TentIDx[playerid] == 679 || itemID == 680 && TentIDx[playerid] == 680))
                    return SendError(playerid, "Для начала необходимо забрать свой переносной ларек.");

                if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY && !IsAllowedFamilyItem(itemID))
                    return SendError(playerid, "Этот предмет запрещено хранить на семейном складе.");

                if(count < 1 || !(1 <= count <= GetInventoryAmount(playerid, itemID)))
                    return SendError(playerid, "У вас не достаточное количество предмета.");

                if(count > GetInventoryFreeItems(playerid, itemID, p_temp[playerid][InterfaceID]))
                    return SendError(playerid, "Не достаточно места чтобы положить.");

                if(itemType == TYPE_ITEMS_INVENTORY)
                {
                    if(count <= InventoryPlayer[playerid][slot_id][inv_amount])
                        InventoryPlayer[playerid][slot_id][inv_amount] -= count;
                    else
                    {
                        new temp_count = InventoryPlayer[playerid][slot_id][inv_amount];
                        InventoryPlayer[playerid][slot_id][inv_amount] = 0;
                        GivePlayerInventory(playerid, itemID, -(count-temp_count), .type_inv = EQUIPMENT_INVENTORY_PLAYER);
                    }

                    if(InventoryPlayer[playerid][slot_id][inv_amount] == 0) 
                        DropPlayerEquipment(playerid, slot_id);
                    else
                    {
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d",
                            InventoryPlayer[playerid][slot_id][inv_amount], InventoryPlayer[playerid][slot_id][inv_mysql_id]);
                        mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
                    }
                    if(!GivePlayerInventory(playerid, itemID, count, .type_inv = p_temp[playerid][InterfaceID]))
                        return 1;
                }
                else
                {
                    if(itemType == TYPE_ITEMS_ACCESSORIES)
                    {
                        new Float:wear = InventoryPlayer[playerid][slot_id][inv_acc_wear],
                            mc1 = InventoryPlayer[playerid][slot_id][inv_acc_mt][0],
                            mc2 = InventoryPlayer[playerid][slot_id][inv_acc_mt][1],
                            premium = InventoryPlayer[playerid][slot_id][inv_acc_premium];
                        if(!GivePlayerInventory(playerid, itemID, count, wear, mc1, mc2, .type_inv = p_temp[playerid][InterfaceID], .premium = premium))
                            return 1;
                    }
                    else if(itemType == TYPE_ITEMS_SKINS)
                    {
                        new Float:wear = InventoryPlayer[playerid][slot_id][inv_skin_wear],
                            premium = InventoryPlayer[playerid][slot_id][inv_skin_premium];
                        if(!GivePlayerInventory(playerid, itemID, count, .wear = wear, .type_inv = p_temp[playerid][InterfaceID], .premium = premium))
                            return 1;
                    }
                    else if(itemType == TYPE_ITEMS_VEHICLE_TUNE)
                    {
                        if(!GivePlayerInventory(playerid, itemID, count, .type_inv = p_temp[playerid][InterfaceID]))
                            return 1;
                    }
                    DropPlayerEquipment(playerid, slot_id);
                }

                switch(p_temp[playerid][InterfaceID])
                {
                    case EQUIPMENT_INVENTORY_HOUSE:
                    {
                        Log(LOG_player, INFO, "%s[%d](%s %s) положил %s %d ед. в <дом>[%d] | #Inventory#Put",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, h_info[p_temp[playerid][p_house_id]][h_mysql_id]);
                    }
                    case EQUIPMENT_INVENTORY_BOOT:
                    {
                        new vehicleid = GetPVarInt(playerid, #VEHICLEID_BOOT);
                        Log(LOG_player, INFO, "%s[%d](%s %s) положил %s %d ед. в т/с <%s>(%d)[%d] | #Inventory#Put",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, GetVehicleName(vehicleid), GetVehicleModelEx(vehicleid), veh_info[vehicleid][v_mysql_id]);
                    }
                    case EQUIPMENT_INVENTORY_TRASHBOX:
                    {
                        new trashbox = p_temp[playerid][trash_id];
                        Log(LOG_player, INFO, "%s[%d](%s %s) положил %s %d ед. в <мусорный ящик>(%d) | #Inventory#Put",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, trashbox);
                    }
                    case EQUIPMENT_INVENTORY_FAMILY:
                    {
                        new family_idx = GetPlayerFamilyID(playerid);
                        Log(LOG_player, INFO, "%s[%d](%s %s) положил %s %d ед. в семью <%s>(%d) | #Inventory#Put",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, FamilyData[family_idx][fName], FamilyData[family_idx][fMysqlID]);

                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] положил на склад %s: %d ед.", get_name(playerid), playerid, ItemsInfo[itemID][iName], count);
                        SendFamilyMessage(family_idx, STRING_GLOBAL);
                    }
                }
            }
            case 1: // take
            {
                //SendDebug(playerid, "take succes");
                if(slot_id == -1) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
                if(!(0 <= slot_id <= MAX_ALL_EQUIPMENT-1)) return SendError(playerid, "Не известная ошибка. Напишите на форум: EQ-06.12.21");
                if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT)
                {
                    new vehicleid = GetPVarInt(playerid, #VEHICLEID_BOOT),
                        Float:w_pos_x, Float:w_pos_y, Float:w_pos_z;
                    GetCoordBootVehicle(vehicleid, w_pos_x, w_pos_y, w_pos_z);
                    if(!IsPlayerInRangeOfPoint(playerid,2.5,w_pos_x, w_pos_y, w_pos_z))
                        return HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
                }

                new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                    itemType = ItemsInfo[itemID][iType];
                if(itemType == TYPE_ITEMS_INVENTORY && (itemID == 679 && TentIDx[playerid] == 679 || itemID == 680 && TentIDx[playerid] == 680))
                    return SendError(playerid, "Для начала необходимо забрать свой переносной ларек.");

                if(count < 1 || !(1 <= count <= GetInventoryAmount(playerid, itemID, p_temp[playerid][InterfaceID])))
                    return SendError(playerid, "Не достаточное количество предмета.");
                if(count > GetInventoryFreeItems(playerid, itemID))
                    return SendError(playerid, "Не достаточно места чтобы положить.");

                if(SRV_ID && p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX &&
                    InventoryPlayer[playerid][slot_id][inv_freeze_time] > timestamp)
                        return SendError(playerid, "Данный предмет недавно выброшен и будет заблокирован еще %s.", ConvertTime(InventoryPlayer[playerid][slot_id][inv_freeze_time]-timestamp));

                if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY && !IsAllowedFamilyItem(itemID))
                    return SendError(playerid, "Этот предмет запрещено хранить на семейном складе.");

                if(itemType == TYPE_ITEMS_INVENTORY)
                {
                    if(count <= InventoryPlayer[playerid][slot_id][inv_amount])
                        InventoryPlayer[playerid][slot_id][inv_amount] -= count;
                    else
                    {
                        new temp_count = InventoryPlayer[playerid][slot_id][inv_amount];
                        InventoryPlayer[playerid][slot_id][inv_amount] = 0;
                        GivePlayerInventory(playerid, itemID, -(count-temp_count), .type_inv = p_temp[playerid][InterfaceID]);
                    }
                    if(InventoryPlayer[playerid][slot_id][inv_amount] == 0)
                        DropPlayerEquipment(playerid, slot_id);
                    else
                    {
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d",
                            InventoryPlayer[playerid][slot_id][inv_amount], InventoryPlayer[playerid][slot_id][inv_mysql_id]);
                        mysql_tquery(con_bd, STRING_GLOBAL, "Equipment_Update", "i", playerid);
                    }
                    if(!GivePlayerInventory(playerid, itemID, count, .type_inv = EQUIPMENT_INVENTORY_PLAYER))
                        return 1;
                }
                else
                {
                    if(itemType == TYPE_ITEMS_ACCESSORIES)
                    {
                        new Float:wear = InventoryPlayer[playerid][slot_id][inv_acc_wear],
                            mc1 = InventoryPlayer[playerid][slot_id][inv_acc_mt][0],
                            mc2 = InventoryPlayer[playerid][slot_id][inv_acc_mt][1],
                            premium = InventoryPlayer[playerid][slot_id][inv_acc_premium];
                        if(!GivePlayerInventory(playerid, itemID, count, wear, mc1, mc2, .type_inv = EQUIPMENT_INVENTORY_PLAYER, .premium = premium))
                            return 1;
                    }
                    else if(itemType == TYPE_ITEMS_SKINS)
                    {
                        new Float:wear = InventoryPlayer[playerid][slot_id][inv_skin_wear],
                            premium = InventoryPlayer[playerid][slot_id][inv_skin_premium];
                        if(!GivePlayerInventory(playerid, itemID, count, wear, .type_inv = EQUIPMENT_INVENTORY_PLAYER, .premium = premium))
                            return 1;
                    }
                    else if(itemType == TYPE_ITEMS_VEHICLE_TUNE)
                    {
                        if(!GivePlayerInventory(playerid, itemID, count, .type_inv = EQUIPMENT_INVENTORY_PLAYER))
                            return 1;
                    }
                    DropPlayerEquipment(playerid, slot_id);
                }

                switch(p_temp[playerid][InterfaceID])
                {
                    case EQUIPMENT_INVENTORY_HOUSE:
                    {
                        Log(LOG_player, INFO, "%s[%d](%s %s) взял %s %d ед. из <дом>[%d] | #Inventory#Take",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, h_info[p_temp[playerid][p_house_id]][h_mysql_id]);
                    }
                    case EQUIPMENT_INVENTORY_BOOT:
                    {
                        new vehicleid = GetPVarInt(playerid, #VEHICLEID_BOOT);
                        Log(LOG_player, INFO, "%s[%d](%s %s) взял %s %d ед. из т/с <%s>(%d)[%d] | #Inventory#Take",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, GetVehicleName(vehicleid), GetVehicleModelEx(vehicleid), veh_info[vehicleid][v_mysql_id]);
                    }
                    case EQUIPMENT_INVENTORY_TRASHBOX:
                    {
                        new trashbox = p_temp[playerid][trash_id];
                        Log(LOG_player, INFO, "%s[%d](%s %s) взял %s %d ед. из <мусорный ящик>(%d) | #Inventory#Take",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, trashbox);
                    }
                    case EQUIPMENT_INVENTORY_FAMILY:
                    {
                        new family_idx = GetPlayerFamilyID(playerid);
                        Log(LOG_player, INFO, "%s[%d](%s %s) взял %s %d ед. из семьи <%s>(%d) | #Inventory#Put",
                            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                            ItemsInfo[itemID][iName], count, FamilyData[family_idx][fName], FamilyData[family_idx][fMysqlID]);
                    
                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] взял на складе %s: %d ед.", get_name(playerid), playerid, ItemsInfo[itemID][iName], count);
                        SendFamilyMessage(family_idx, STRING_GLOBAL);
                    }
                }
            }
        }
    }
    Equipment_Update(playerid);
    //LoadOtherInventoryData(playerid, p_temp[playerid][InterfaceID]);
    return 1;
}

cmd:cleartrashbox(playerid, params[])
{
    if(p_info[playerid][admin] < 6) return 1;
    for(new i = MAX_TRASH-1; i != -1; i--) ClearInventoryItems(i, INVENTORY_OWNER_TYPE_TRASHBOX);
    return 1;
}

LoadOtherInventoryData(playerid, interface_id)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(max_slot < MAX_ALL_EQUIPMENT)
    {
        for(new i = MAX_ALL_EQUIPMENT-1; i != max_slot; i--) Equipment_ClearSlot(playerid, i);
    }
    if(interface_id == EQUIPMENT_INVENTORY_BOOT)
    {
        new vehicleid = GetPVarInt(playerid, #VEHICLEID_BOOT);
        if(vehicleid > 0)
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "SELECT * FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d AND `status_use` = 0 ORDER BY `slot_id` ASC",
                veh_info[vehicleid][v_mysql_id], INVENTORY_OWNER_TYPE_VEHICLE);
            mysql_tquery(con_bd, STRING_GLOBAL, "LoadInventoryData", "iii", playerid, p_info[playerid][ID], interface_id);
        }
    }
    else if(interface_id == EQUIPMENT_INVENTORY_HOUSE)
    {
        new houseId = p_temp[playerid][p_house_id];
        if(houseId != INVALID_HOUSE_ID)
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "SELECT * FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d ORDER BY `slot_id` ASC",
                h_info[houseId][h_mysql_id], INVENTORY_OWNER_TYPE_HOUSE);
            mysql_tquery(con_bd, STRING_GLOBAL, "LoadInventoryData", "iii", playerid, p_info[playerid][ID], interface_id);
        }
    }
    else if(interface_id == EQUIPMENT_INVENTORY_TRASHBOX)
    {
        new trashbox = p_temp[playerid][trash_id];
        if(0 <= trashbox < sizeof(TrashInfo))
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "SELECT * FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d ORDER BY `slot_id` ASC",
               trashbox, INVENTORY_OWNER_TYPE_TRASHBOX);
            mysql_tquery(con_bd, STRING_GLOBAL, "LoadInventoryData", "iii", playerid, p_info[playerid][ID], interface_id);
        }
    }
    else if(interface_id == EQUIPMENT_INVENTORY_FAMILY)
    {
        new family_db_id = p_info[playerid][family_id];
        if(family_db_id != -1)
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "SELECT * FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d ORDER BY `slot_id` ASC",
               family_db_id, INVENTORY_OWNER_TYPE_FAMILY);
            mysql_tquery(con_bd, STRING_GLOBAL, "LoadInventoryData", "iii", playerid, p_info[playerid][ID], interface_id);
        }
    }
}

UsePlayerEating(playerid, type)
{
    if(type == 0)
    {
        new itemIDs[] = {638, 639};
        for(new i = sizeof(itemIDs)-1; i != -1; i--)
        {
            if(GetInventoryAmount(playerid, itemIDs[i]) < 1)
                continue;
            GivePlayerInventory(playerid, itemIDs[i], -1);

            if(floatcmp(floatadd(p_info[playerid][satiety], 40.0), 100.0) == 1) p_info[playerid][satiety] = 100.0;
            else p_info[playerid][satiety] += 50.0;

            if(GetPlayerDisease(playerid, 1, 10, 2) == 1) // Шанс 20 процентов;
            {
                p_info[playerid][Disease][1]++;
                SendInfo(playerid, "У Вас появилось новое заболевание - диарея %d степени.", p_info[playerid][Disease][1]);
            }
            return 1;
        }
    }
    else
    {
        new itemIDs[] = {695, 696, 697, 698};
        for(new i = sizeof(itemIDs)-1; i != -1; i--)
        {
            if(GetInventoryAmount(playerid, itemIDs[i]) < 1)
                continue;
            GivePlayerInventory(playerid, itemIDs[i], -1);

            new Float:thirst_count[5] = {20.0, 40.0, 60.0, 80.0}, 
                Float:count = thirst_count[i];

            if(floatcmp(floatadd(p_info[playerid][thirst], count), 100.0) == 1) p_info[playerid][thirst] = 100.0;
            else p_info[playerid][thirst] += count;

            return 1;
        }
    }
    return 0;
}