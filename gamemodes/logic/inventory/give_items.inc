SetPlayerItem(playerid, type, userID, itemID, extraData1, extraData2 = 0, extraData3 = 0, price = 0, sell_block = 0)
{
    if(playerid != INVALID_PLAYER_ID)
    {
        if(type != 9) SendInfo(playerid, "Вы выиграли: %s.", GetPrizeItemsName(itemID, extraData1, extraData2, extraData3));

        switch(itemID)
        {
            case TYPE_GIVE_ITEM_EXP:
            {
                p_info[playerid][exp] += extraData1;
                PlayerLevelUpdateCheck(playerid);

                Log(LOG_player, INFO, "%s[%d](%s %s) забрал %s | #GiveItem",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData1, extraData2, extraData3));
                return 1;
            }
            case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
            {
                SetPlayerMoney(playerid, extraData1, true, "забрал /items");
                
                Log(LOG_player, INFO, "%s[%d](%s %s) забрал %s | #GiveItem",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData1, extraData2, extraData3));
                return 1;
            }
            case TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
            {
                p_info[playerid][flinmoney] += extraData1;
                MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

                Log(LOG_player, INFO, "%s[%d](%s %s) забрал %s | #GiveItem",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData1, extraData2, extraData3));
                return 1;
            }
            default:
            {
                SendInfo(playerid, "Чтобы забрать предмет, введите /items");
                Log(LOG_player, INFO, "%s[%d](%s %s) получил %s в /items. Тип: %d | #GetItem",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData1, extraData2, extraData3), type);
            }
        }
    }
    else
    {
        Log(LOG_player, INFO, "Номер аккаунта [%d] получил %s в /items. Тип: %d | #GetItem",
            userID, GetPrizeItemsName(itemID, extraData1, extraData2, extraData3), type);
    }
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `player_items` (`userID`, `itemID`, `extraData1`, `extraData2`, `extraData3`, `price`, `sell_block`, `time`) VALUES (%d, %d, %d, %d, %d, %d, %d, %d)",
        userID, itemID, extraData1, extraData2, extraData3, price, sell_block, (timestamp+2592000));
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

forward PlayerItemCallback(playerid, mylsq_player_id, type);
public PlayerItemCallback(playerid, mylsq_player_id, type)
{
    if(p_info[playerid][ID] != mylsq_player_id)
        return SendError(playerid, "Произошла не известная ошибка - 060223 #5");
    new rows;
    cache_get_row_count(rows);
    if(!rows)
        return SendError(playerid, "Произошла ошибка (Item Item - #6). Сообщите в тех. раздел.");

    new itemID, extraData[3], price, sell_block, time_clear, mysql_item_id;
    cache_get_value_name_int(0, "id", mysql_item_id);
    cache_get_value_name_int(0, "itemID", itemID);
    cache_get_value_name_int(0, "extraData1", extraData[0]);
    cache_get_value_name_int(0, "extraData2", extraData[1]);
    cache_get_value_name_int(0, "extraData3", extraData[2]);
    cache_get_value_name_int(0, "price", price);
    cache_get_value_name_int(0, "sell_block", sell_block);
    cache_get_value_name_int(0, "time", time_clear);

    if(time_clear < timestamp)
        return SendError(playerid, "Предмет заблокирован, время использования закончилось.");

    if(extraData[0] == 0 && extraData[1] == 0 && extraData[2] == 0)
        return SendError(playerid, "Произошла ошибка (Item - #3). Сообщите в тех. раздел.");

    switch(type)
    {
        case TYPE_PLAYER_ITEM_GIVE:
        {
            switch(itemID)
            {
                case TYPE_GIVE_ITEM_EXP:
                {
                    p_info[playerid][exp] += extraData[0];
                    PlayerLevelUpdateCheck(playerid);
                }
                case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
                {
                    SetPlayerMoney(playerid, extraData[0], true, "забрал /items");
                }
                case TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
                {
                    p_info[playerid][flinmoney] += extraData[0];
                    MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

                    if(p_temp[playerid][TextDrawRoulette] == true) UpdatePlayerRouletteInfo(playerid);
                }
                case TYPE_GIVE_ITEM_INVENTORY:
                {
                    if(!GivePlayerInventory(playerid, extraData[1], extraData[0], .reason = "забрал /items"))
                        return 0;
                }
                case TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_ACCESSORIES:
                {
                    if(!GivePlayerInventory(playerid, extraData[0], .reason = "забрал /items"))
                        return 0;
                }
                case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
                {
                    AddVehicleToPlayer(playerid, extraData[0], sell_block == 0 ? extraData[1] : 4, price);
                }
                case TYPE_GIVE_ITEM_VIP:
                {
                    new temp_vip_idx = extraData[0] + 1;
                    if(p_info[playerid][p_vip] > 0 && temp_vip_idx < p_info[playerid][p_vip]) return SendError(playerid, "У Вас уже есть VIP статус уровнем выше.");
                    if(p_info[playerid][p_vip] != temp_vip_idx) p_info[playerid][p_vip_time] = 0;
                    p_info[playerid][p_vip] = temp_vip_idx;
                    if(p_info[playerid][p_vip_time]) p_info[playerid][p_vip_time] += 86400 * extraData[1];
                    else p_info[playerid][p_vip_time] = (timestamp + (86400 * extraData[1]));
                }
                default: return SendError(playerid, "Произошла ошибка (Prize - #1). Сообщите в тех. раздел.");
            }

            SendAccess(playerid, "Вы забрали: %s.", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]));

            Log(LOG_player, INFO, "%s[%d](%s %s) забрал %s | #GiveItem",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]));
        }
        case TYPE_PLAYER_ITEM_CONFIRM_SELL:
        {
            if(price <= 0 || sell_block)
            {
                UpdatePlayerList(playerid);
                return SendError(playerid, "Данный предмет нельзя продать.");
            }
            SetPVarInt(playerid, #MYSQL_ITEM_ID, mysql_item_id);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                Вы действительно хотите продать "I"%s"W" за "I"%d Flin Money?", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]), price);
            return ShowPlayerDialog(playerid, D_GIVE_ITEM_SELL, DIALOG_STYLE_MSGBOX, ""I"Продать приз", STRING_GLOBAL, "Да", "Нет");
        }
        case TYPE_PLAYER_ITEM_SELL:
        {
            if(price <= 0 || sell_block)
            {
                UpdatePlayerList(playerid);
                return SendError(playerid, "Данный предмет нельзя продать.");
            }
            switch(itemID)
            {
                case TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
                {
                    p_info[playerid][flinmoney] += price;
                    MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);
                }
                default: return SendError(playerid, "Произошла ошибка (Item - 0602). Сообщите в тех. раздел.");
            }

            SendAccess(playerid, "Вы продали приз %s за %d Flin Money.", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]), price);

            Log(LOG_player, INFO, "%s[%d](%s %s) продал %s за %d Flin Money | #SellItem",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]), price);
        }
        case TYPE_PLAYER_ITEM_DELETE:
        {
            SendAccess(playerid, "Вы удалили %s.", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]));

            Log(LOG_player, INFO, "%s[%d](%s %s) удалил предмет %s за %d Flin Money | #DeleteItem",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]), price);
        }
    }
    if(type != TYPE_PLAYER_ITEM_CONFIRM_SELL)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `player_items` WHERE `id` = %d LIMIT 1", mysql_item_id);
        mysql_tquery(con_bd, STRING_GLOBAL);
        if(itemID != TYPE_GIVE_ITEM_VEHICLE && itemID != TYPE_GIVE_ITEM_U_VEHICLE)
            UpdatePlayerList(playerid);
    }
    return 1;
}

GetPrizeItemsName(itemID, count, count2 = 0, count3 = 0)
{
    #pragma unused count3
    new str[256];
    switch(itemID)
    {
        case TYPE_GIVE_ITEM_EXP, TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE, TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
        {
            format(str, sizeof(str), "%s: %d", TypeGiveItemName[itemID], count);
        }
        case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
        {
            format(str, sizeof(str), "%s: %d$", TypeGiveItemName[itemID], count);
        }
        case TYPE_GIVE_ITEM_INVENTORY:
        {
            format(str, sizeof(str), "%s: %s %d ед.", TypeGiveItemName[itemID], ItemsInfo[count2][iName], count);
        }
        case TYPE_GIVE_ITEM_ACCESSORIES:
        {
            format(str, sizeof(str), "%s: %s", TypeGiveItemName[itemID], ItemsInfo[count][iName]);
        }
        case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
        {
            format(str, sizeof(str), "%s: %s", TypeGiveItemName[itemID], GetVehicleName(INVALID_VEHICLE_ID, count));
        }
        case TYPE_GIVE_ITEM_VIP:
        {
            format(str, sizeof(str), "%s: %s, %d дн.", TypeGiveItemName[itemID], TypeVIPName[count], count2);
        }
        default: str = "Нет";
    }
    return str;
}

CMD:items(playerid, params[])
{
    ShowPlayerList(playerid, LIST_ID_GIVE_ITEMS);
    return 1;
}

alias:items("priz", "playeritems", "item");