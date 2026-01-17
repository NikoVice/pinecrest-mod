/*
    Listing Page System
    Special for Flin RolePlay
    Author: Vova Kravchuk aka Vip_Uzer
*/
#define LIST_OFFSET_MAX 25
// Dialog List [mysql/no mysql]
ShowPlayerList(playerid, list_idx)
{
    p_temp[playerid][list_page] = 1;
    p_temp[playerid][list_type] = list_idx;

    UpdatePlayerList(playerid);
}

UpdatePlayerList(playerid)
{
    STRING_GLOBAL[0] = EOS;
    switch(p_temp[playerid][list_type])
    {
        case LIST_ID_HOT_DEALS_SMALL_SIZED:
        {
            new page_id= p_temp[playerid][list_page]-1, count, percent_str[32],
                bool:bSearchPointEnter, idx, list_count;
            
            STRING_GLOBAL = "[#] Тип, Название\tСтоимость\tСкидка\n\
                "I"<< "W"Предыдущая страница\t \n"I">> "W"Следующая страница\t \n";

            for(new i = 0; i < MAX_DONATE; i++)
            {
                if(DonateInfo[i][dType] < TYPE_DONATE_ROULETTE) continue;
                if(DonateInfo[i][dStatus] == false) continue;
                if(count%25 == 0) idx = i;
                count++;
                if(count < page_id*LIST_OFFSET_MAX+1) continue;
                bSearchPointEnter = true;
                break;
            }
            if(!bSearchPointEnter)
            {
                if(!page_id)
                    return SendError(playerid, "Ничего нет...");
                page_id--;
                count = page_id*LIST_OFFSET_MAX+1;
                p_temp[playerid][list_page] = page_id;
            }
            count--;
            for(new i = idx; i < MAX_DONATE; i++)
            {
                if(DonateInfo[i][dType] < TYPE_DONATE_ROULETTE) continue;
                if(DonateInfo[i][dStatus] == false) continue;
                count++;
                if(count > page_id*LIST_OFFSET_MAX+25) break;
                format(percent_str, sizeof(percent_str), "{"#cLIGHTRED"}%.0f%%"W"", DonateInfo[i][dPercent]);
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d]"W" %s %s\t%s\t%s\n", STRING_GLOBAL, list_count+1+page_id*LIST_OFFSET_MAX, DonateName[DonateInfo[i][dType]], DonateInfo[i][dName], GetPlayerDonatePrice(i), percent_str);
                p_temp[playerid][p_listitem][list_count] = i;
                list_count++;
            }
            ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Горячие предложения", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case LIST_ID_PLAYER_ACCESSORIES:
        {
            new page = p_temp[playerid][list_page]-1, count;
            STRING_GLOBAL = "[#] Аксессуар\tСтатус\n\
                "I"<< "W"Предыдущая страница\t \n"I">> "W"Следующая страница\t \n";
            for(new i = 0; i < p_info[playerid][inv_slots]; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
                    (InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_ACCESSORIES)) continue;
                if(count < (page * 25)) continue;
                if(count >= (page * 25) + 25) break;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\n", STRING_GLOBAL, count+1,
                    ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iName],
                    (!InventoryPlayer[playerid][i][inv_status_use]) ? ("{e06666}[Неактивен]") : ("{93c47d}[Активен]"));
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Аксессуары", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case LIST_ID_PLAYER_SKINS:
        {
            new page_id = p_temp[playerid][list_page]-1, count;
            STRING_GLOBAL = "[#] Одежда\tСтатус\n\
                "I"<< "W"Предыдущая страница\t \n"I">> "W"Следующая страница\t \n";
            for(new i = 0; i < p_info[playerid][inv_slots]; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
                    (InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_SKINS)) continue;
                if(count < (page_id * 25)) continue;
                if(count >= (page_id * 25) + 25) break;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\n", STRING_GLOBAL, count+1,
                    ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iName],
                    (!InventoryPlayer[playerid][i][inv_status_use]) ? ("{e06666}[Неактивен]") : ("{93c47d}[Активен]"));
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Скины", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case LIST_ID_MARKET_BUY_INV, LIST_ID_MARKET_BUY_ACC, LIST_ID_MARKET_BUY_SKIN:
        {
            new page_id = p_temp[playerid][list_page]-1, id, count;
            STRING_GLOBAL = "[#] Предмет\t{"#cGREEN"}Количество\t{"#cRED"}Стоимость\n\
                "I"<< "W"Предыдущая страница\t \t \n"I">> "W"Следующая страница\t \t \n";

            new itemType;
            switch(p_temp[playerid][list_type])
            {
                case LIST_ID_MARKET_BUY_INV: itemType = TYPE_ITEMS_INVENTORY;
                case LIST_ID_MARKET_BUY_ACC: itemType = TYPE_ITEMS_ACCESSORIES;
                case LIST_ID_MARKET_BUY_SKIN: itemType = TYPE_ITEMS_SKINS;
            }

            new bool:bSearchPointEnter, idx, list_count, iFreeItems;
            for(new i = 0; i < sizeof(ItemsInfo); i++)
            {
                if(ItemsInfo[i][iType] != itemType) continue;
                if(count%25 == 0) idx = i;
                count++;
                if(count < page_id*LIST_OFFSET_MAX+1) continue;
                bSearchPointEnter = true;
                break;
            }
            if(!bSearchPointEnter)
            {
                if(!page_id)
                    return SendError(playerid, "Ничего нет...");
                page_id--;
                count = page_id*LIST_OFFSET_MAX+1;
                p_temp[playerid][list_page] = page_id;
            }
            count--;
            for(new i = idx; i < sizeof(ItemsInfo); i++)
            {
                if(ItemsInfo[i][iType] != itemType) continue;
                count++;
                if(count > page_id*LIST_OFFSET_MAX+25) break;
                iFreeItems = GetInventoryFreeItems(playerid, i);
                id = GetIDMarketBuyItem(playerid, i);
                if(id != -1)
                {
                    if(InventoryPlayer[playerid][id][inv_market_buy_amount] > iFreeItems)
                    {
                        InventoryPlayer[playerid][id][inv_market_buy_amount] = iFreeItems;
                        if(iFreeItems)
                            SendInfo(playerid, "Для \"%s\" обновлено число максимальной закупки.");
                        else
                        {
                            InventoryPlayer[playerid][id][inv_market_buy_price] = 0;
                            if(InventoryPlayer[playerid][id][inv_mysql_id] == INVALID_MYSQL_ID)
                                InventoryPlayer[playerid][id][inv_item_id] = 0;
                            SendError(playerid, "\"%s\" убран с закупки, нет места в инвентаре.", ItemsInfo[i][iName]);
                            f(STRING_GLOBAL, "%s"I"[%d]"W" {bcbcbc}%s\n", STRING_GLOBAL, count, ItemsInfo[i][iName]);
                            p_temp[playerid][p_listitem][list_count] = i;
                            list_count++;
                            continue;
                        }
                    }
                    f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d\t%d$ / %d$\n", STRING_GLOBAL, count,
                        ItemsInfo[i][iName], InventoryPlayer[playerid][id][inv_market_buy_amount],
                        InventoryPlayer[playerid][id][inv_market_buy_price],
                        InventoryPlayer[playerid][id][inv_market_buy_price]*InventoryPlayer[playerid][id][inv_market_buy_amount]);
                }
                else
                    f(STRING_GLOBAL, "%s"I"[%d]"W" {bcbcbc}%s\n", STRING_GLOBAL, count, ItemsInfo[i][iName]);
                p_temp[playerid][p_listitem][list_count] = i;
                list_count++;
            }
            ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Рынок", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case LIST_ID_ARA_SELL_ITEMS:
        {
            new itemID, page_id = p_temp[playerid][list_page]-1, count;
            STRING_GLOBAL = ""W"[#] Предмет\t"W"Количество\t"W"Стоимость за 1 ед.\n\
                "I"<< "W"Предыдущая страница\t \t \n"I">> "W"Следующая страница\t \t \n";

            new bool:bSearchPointEnter, idx, list_count,
                max_slot, min_slot;
            GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
            if(min_slot >= max_slot) return 0;
            min_slot++, max_slot++;

            for(new i = min_slot; i < max_slot; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID) continue;
                if(count%25 == 0) idx = i;
                count++;
                if(count < page_id*LIST_OFFSET_MAX+1) continue;
                bSearchPointEnter = true;
                break;
            }
            if(!bSearchPointEnter)
            {
                if(!page_id)
                    return SendError(playerid, "Ничего нет...");
                page_id--;
                count = page_id*LIST_OFFSET_MAX+1;
                p_temp[playerid][list_page] = page_id;
            }
            count--;
            for(new i = idx; i < max_slot; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID) continue;
                count++;
                if(count > page_id*LIST_OFFSET_MAX+25) break;
                itemID = InventoryPlayer[playerid][i][inv_item_id];
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t"W"%d\t"W"%d$\n", STRING_GLOBAL, count,
                    ItemsInfo[itemID][iName], GetInventoryAmount(playerid, itemID), ItemsInfo[itemID][iStateCost]);
                
                p_temp[playerid][p_listitem][list_count] = i;
                list_count++;
            }
            ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Продать вещи", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case LIST_ID_MARKET_SELL_ITEMS:
        {
            new itemID, page_id = p_temp[playerid][list_page]-1, count;
            STRING_GLOBAL = ""W"[#] Предмет\t{"#cGREEN"}Количество\t{"#cRED"}Стоимость\n\
                "I"<< "W"Предыдущая страница\t \t \n"I">> "W"Следующая страница\t \t \n";

            new bool:bSearchPointEnter, idx, list_count, iTotalAmount,
                max_slot, min_slot;
            GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
            if(min_slot >= max_slot) return 0;
            min_slot++, max_slot++;

            for(new i = min_slot; i < max_slot; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID) continue;
                itemID = InventoryPlayer[playerid][i][inv_item_id];
                if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY &&
                    !CheckSellMarketItemsAdd(playerid, itemID, i)) continue;
                if(count%25 == 0) idx = i;
                count++;
                if(count < page_id*LIST_OFFSET_MAX+1) continue;
                bSearchPointEnter = true;
                break;
            }
            if(!bSearchPointEnter)
            {
                if(!page_id)
                    return SendError(playerid, "Ничего нет...");
                page_id--;
                count = page_id*LIST_OFFSET_MAX+1;
                p_temp[playerid][list_page] = page_id;
            }
            count--;
            for(new i = idx; i < max_slot; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID) continue;
                itemID = InventoryPlayer[playerid][i][inv_item_id];
                if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY &&
                    !CheckSellMarketItemsAdd(playerid, itemID, i)) continue;
                count++;
                if(count > page_id*LIST_OFFSET_MAX+25) break;
                itemID = InventoryPlayer[playerid][i][inv_item_id];
                if(InventoryPlayer[playerid][i][inv_market_sell_amount] > 0)
                {
                    iTotalAmount = GetInventoryAmount(playerid, itemID);
                    if(InventoryPlayer[playerid][i][inv_market_sell_amount] > iTotalAmount)
                        InventoryPlayer[playerid][i][inv_market_sell_amount] = iTotalAmount;
                    f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d\t%d$ / %d$\n", STRING_GLOBAL, count,
                        ItemsInfo[itemID][iName], InventoryPlayer[playerid][i][inv_market_sell_amount], InventoryPlayer[playerid][i][inv_market_sell_price], InventoryPlayer[playerid][i][inv_market_sell_price]*InventoryPlayer[playerid][i][inv_market_sell_amount]);
                }
                else
                {
                    f(STRING_GLOBAL, "%s"I"[%d] {bcbcbc}%s\t \t \n", STRING_GLOBAL, count, ItemsInfo[itemID][iName]);
                }
                p_temp[playerid][p_listitem][list_count] = i;
                list_count++;
            }
            ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Рынок", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case LIST_ID_DONATE_HISTORY:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
                "SELECT `itemsCount`, `dateDelivered` FROM `unitpay_payments` WHERE `accountId` = %d AND `status` = 1 AND `delivered` = 1 ORDER BY `dateDelivered` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][ID], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_VEHICLE_NOTES:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = (SELECT `v_owner_id` FROM `vehicle` WHERE `v_mysql_id` = vehicle_note.vehicle_id)) as ownername, \
                (SELECT `name` FROM `accounts` WHERE id = vehicle_note.officer_id) AS officername FROM `vehicle_note` WHERE `vehicle_id` = %d ORDER BY `date` DESC LIMIT 25 OFFSET %d",
                GetPVarInt(playerid, #MDC_ID), (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FRACTION_ALL_MEMBERS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `name`, `rang`, `online`, `fwarn`, `lastenter` FROM `accounts` WHERE `member` = %d AND `admin` = 0 ORDER BY `id` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][member], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FRACTION_ONLINE_MEMBERS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `name`, `rang`, `fwarn`, `fwork` FROM `accounts` WHERE `member` = %d AND `online` > 0 AND `admin` = 0 ORDER BY `id` DESC LIMIT 25 OFFSET %d",
            p_info[playerid][member], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FRACTION_BLACKLIST:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT accounts.name AS f_bl_player_name, (SELECT name FROM `accounts` WHERE `id` = fraction_blacklist.f_bl_target_id) AS f_bl_target_name, fraction_blacklist.* FROM accounts \
                INNER JOIN fraction_blacklist ON accounts.id=fraction_blacklist.f_bl_player_id WHERE fraction_blacklist.f_bl_frac = %d ORDER BY `f_bl_date` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][member], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_WBOOK:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `log_fraction` WHERE `PlayerID` = %d AND `Member` = %d ORDER BY `ID` DESC LIMIT 25 OFFSET %d",
                p_info[p_temp[playerid][PlayerBook]][ID], p_temp[playerid][p_listitem_int], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FAMILY_OFFLINE_MEMBERS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `name`, `lastenter`, `family_rang`, `family_warn` FROM `accounts` WHERE `family_id` = %d AND `online` = 0 ORDER BY `id` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][family_id], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FAMILY_NOTIFY:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `family_notify` WHERE `id` = %d ORDER BY `date` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][family_id], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FAMILY_LOG:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `family_log` WHERE `id` = %d ORDER BY `date` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][family_id], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_FAMILY_BLACKLIST:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT accounts.name AS player_name, (SELECT name FROM `accounts` WHERE `id` = family_blacklist.target_id) AS target_name, family_blacklist.* FROM accounts \
                INNER JOIN family_blacklist ON accounts.id=family_blacklist.player_id WHERE family_blacklist.id = %d ORDER BY `date` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][family_id], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_TC_OFFLINE_MEMBERS:
        {
            new idx = p_temp[playerid][p_tc_id];
            switch(b_info[idx][_tip])
            {
                case B_TAXI:
                {
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `name`, `lastenter`, `taxi_rank`, `taxi_salary`, `taxi_salary_all` FROM `accounts` WHERE `taxi_idx` = %d AND `online` = 0 ORDER BY `id` DESC LIMIT 25 OFFSET %d",
                    p_info[playerid][taxi_idx], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
                }
                case B_TRUCKER:
                {
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `name`, `lastenter`, `tc_rank`, `tc_salary`, `tc_salary_all` FROM `accounts` WHERE `tc_idx` = %d AND `online` = 0 ORDER BY `id` DESC LIMIT 25 OFFSET %d",
                    p_info[playerid][tc_idx], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
                }
            }
        }
        case LIST_ID_WANTED_ONLINE:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `wanted` FROM `accounts` WHERE `wanted` > 0 AND `online` > 0 ORDER BY `wanted` DESC LIMIT 25 OFFSET %d",
                (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_WANTED_OFFLINE:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `wanted` FROM `accounts` WHERE `wanted` > 0 AND `online` = 0 ORDER BY `wanted` DESC LIMIT 25 OFFSET %d",
                (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_OFF_ADMINS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `admin`, `lastenter` FROM `accounts` WHERE `admin` > 0 AND `admin` < 10 AND `online` = 0 ORDER BY `admin` DESC LIMIT 25 OFFSET %d",
                (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_LEADERS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `leader`, `online`, `lastenter`, `phone_number` FROM `accounts` WHERE `leader` != 0 AND `admin` = 0 ORDER BY `leader` DESC LIMIT 25 OFFSET %d",
                (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_ZAMS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `member`, `rang`, `online`, `lastenter`, `phone_number` FROM `accounts` WHERE `member` != 0 AND `rang` = 9 AND `admin` = 0 ORDER BY `member` DESC LIMIT 25 OFFSET %d",
                (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_PROMOCODE:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `level`, `promocode_time`, `promocode_donate` FROM `accounts` WHERE `promocode_use` = %d ORDER BY `level` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][promocode_create], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_GIVE_ITEMS:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `player_items` WHERE `userID` = %d AND `time` > UNIX_TIMESTAMP(NOW()) ORDER BY `id` DESC LIMIT 25 OFFSET %d",
                p_info[playerid][ID], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_TIME_OWNER_BIZZ:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `b_mysql_id`, `b_name`, (SELECT `name` FROM `accounts` WHERE `id` = `b_user_id`) AS `owner`, `b_owned_at`, `b_paydays_received` FROM `biz` WHERE `b_user_id` != 0 ORDER BY `b_mysql_id` DESC LIMIT 25 OFFSET %d",
                (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_SERVER_FORUM:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT sf.*, \
                COALESCE(AVG(if(sfs.`rating` > 0, sfs.`rating`, NULL)), 0) avg_rating, \
                COUNT(sfs.newsid) AS views, \
                COALESCE((SELECT `rating` FROM `server_forum_stats` WHERE `newsid` = sf.`id` AND `userid` = %d), -1) AS user_rating \
                FROM `server_forum` sf \
                LEFT JOIN `server_forum_stats` sfs ON sf.`id` = sfs.`newsid` \
                GROUP BY sf.`id` \
                ORDER BY sf.`id` DESC LIMIT 25 OFFSET %d", p_info[playerid][ID], (p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX);
        }
        case LIST_ID_GHETTO_PC:
        {
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), 
                "SELECT `name`, `online`, `lastenter` FROM `accounts` WHERE `id` = %d; \
                SELECT `name`, `online`, `lastenter` FROM `accounts` WHERE `id` = %d; \
                SELECT `name`, `online`, `lastenter` FROM `accounts` WHERE `id` = %d; \
                SELECT `name`, `online`, `lastenter` FROM `accounts` WHERE `id` = %d; \
                SELECT `name`, `online`, `lastenter` FROM `accounts` WHERE `id` = %d",
                GetGangPC(GROOVE), GetGangPC(BALLAS),
                GetGangPC(RIFA), GetGangPC(AZTEC),
                GetGangPC(VAGOS));
        }
    }
    mysql_tquery(con_bd, STRING_GLOBAL, "PlayerTypeListInfo", "i", playerid);
    return 1;
}

forward PlayerTypeListInfo(playerid);
public PlayerTypeListInfo(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows && p_temp[playerid][list_type] != LIST_ID_GHETTO_PC)
    {
        if(p_temp[playerid][list_page] <= 1)
        {
            if(p_temp[playerid][list_type] == LIST_ID_VEHICLE_NOTES)
            {
                STRING_GLOBAL = "[#] Владелец\tВыписал\tЗаметка\tДата\n\
                    "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n\
                    "I"+ "W"Добавить заметку\t-\t-\t-";
                return ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Меню выбора", STRING_GLOBAL, "Выбрать", "Назад" );
            }
            else return SendError(playerid, "Ничего не найдено.");
        }
        p_temp[playerid][list_page]--;
        SendError(playerid, "Вы находитесь на последней странице.");
        UpdatePlayerList(playerid);
        return 1;
    }
    new count = ((p_temp[playerid][list_page]-1)*LIST_OFFSET_MAX)+1;
    STRING_GLOBAL[0] = EOS;
    switch(p_temp[playerid][list_type])
    {
        case LIST_ID_SERVER_FORUM:
        {
            new fs_name[128], fs_date[24], fs_type, fs_views, fs_avg_rating, fs_name_type[][] = {"[Новость]", "[Опрос]"};
            STRING_GLOBAL = ""W"[#] Тип: Название\tДата\t"W"Просмотры/Рейтинг\n\
                "I"<< "W"Предыдущая страница\t-\n"I">> "W"Следующая страница\t-\n";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name_int(i, "type", fs_type);
                cache_get_value_name(i, "name", fs_name);
                cache_get_value_name(i, "date", fs_date);
                cache_get_value_name_int(i, "views", fs_views);
                cache_get_value_name_int(i, "avg_rating", fs_avg_rating);
                cache_get_value_name_int(i, "user_rating", p_temp[playerid][p_listitem][LIST_OFFSET_MAX+i]);
                if(p_temp[playerid][p_listitem][LIST_OFFSET_MAX+i] == -1) 
                    f(STRING_GLOBAL, "%s"I"[%d] {bcbcbc}%s: {bcbcbc}%s\t{bcbcbc}%s\t{bcbcbc}%d | %d/5\n", STRING_GLOBAL, count, 
                    fs_name_type[fs_type], fs_name, fs_date, fs_views, fs_avg_rating);
                else f(STRING_GLOBAL, "%s"I"[%d] "W"%s: "W"%s\t"W"%s\t"W"%d | %d/5\n", STRING_GLOBAL, count, 
                    fs_name_type[fs_type], fs_name, fs_date, fs_views, fs_avg_rating);
                count++;
            }
        }
        case LIST_ID_DONATE_HISTORY:
        {
            new fm_count, fm_date[24];
            STRING_GLOBAL = ""W"[#] Количество FM\t"W"Дата зачисления\n\
                "I"<< "W"Предыдущая страница\t-\n"I">> "W"Следующая страница\t-\n";
            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "itemsCount", fm_count);
                cache_get_value_name(i, "dateDelivered", fm_date);
                f(STRING_GLOBAL, "%s"I"[%d] "W"%d\t"W"%s\n", STRING_GLOBAL, count, fm_count, fm_date);
                count++;
            }
        }
        case LIST_ID_LEADERS:
        {
            new nickname[MAX_PLAYER_NAME], fraction_id, last_enter[16], status_online, pnumber;

            STRING_GLOBAL = ""W"[#] Фракция\t"W"Никнейм\t"W"Последний вход\t"W"Телефон\n\
                "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n";
            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "name", nickname, 24);
                cache_get_value_name_int(i, "leader", fraction_id);
                cache_get_value_name_int(i, "online", status_online);
                cache_get_value_name(i, "lastenter", last_enter, 16);
                cache_get_value_name_int(i, "phone_number", pnumber);
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d] {%06x}%s\t"W"%s\t"W"[%s]\t%d\n",
                    STRING_GLOBAL, count, fraction_color[fraction_id] >>> 8, GetFractionName(fraction_id), nickname, !status_online ? last_enter : "В сети", pnumber);
                count++;
            }
        }

        case LIST_ID_GHETTO_PC:
        {
            new nickname[MAX_PLAYER_NAME], last_enter[16], status_online;

            new result_count;
            cache_get_result_count(result_count);
            printf("we will now go through all %d results:", result_count);
            
            STRING_GLOBAL = ""W"[#] Фракция\t"W"Никнейм\t"W"Последний вход\n";

            for(new r; r < result_count; r++)
            {
                cache_set_result(r);
                rows = cache_num_rows();
                if(rows)
                {
                    for(new i; i < rows; i++)
                    {
                        cache_get_value_name(i, "name", nickname, 24);
                        cache_get_value_name_int(i, "online", status_online);
                        cache_get_value_name(i, "lastenter", last_enter);
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d] {%06x}%s\t"W"%s\t%s\n",
                            STRING_GLOBAL, count, fraction_color[10+r] >>> 8, GetFractionName(10+r), nickname, !status_online ? last_enter : "В сети");
                        count++;
                    }
                }
                else
                {
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d] {%06x}%s\t"W"-\n",
                        STRING_GLOBAL, count, fraction_color[10+r] >>> 8, GetFractionName(10+r));
                    count++;
                }
            }
        }
        case LIST_ID_ZAMS:
        {
            new nickname[MAX_PLAYER_NAME], fraction_id, last_enter[16], status_online, pnumber;

            STRING_GLOBAL = ""W"[#] Фракция\t"W"Никнейм\t"W"Последний вход\t"W"Телефон\n\
                "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n";
            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "name", nickname, 24);
                cache_get_value_name_int(i, "member", fraction_id);
                cache_get_value_name_int(i, "online", status_online);
                cache_get_value_name(i, "lastenter", last_enter, 16);
                cache_get_value_name_int(i, "phone_number", pnumber);
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d] {%06x}%s\t"W"%s\t"W"[%s]\t%d\n",
                    STRING_GLOBAL, count, fraction_color[fraction_id] >>> 8, GetFractionName(fraction_id), nickname, !status_online ? last_enter : "В сети", pnumber);
                count++;
            }
        }
        case LIST_ID_OFF_ADMINS:
        {
            new AdminsRangColor[] =
                {
                    0x993300AA, 0x33AA33AA, 0x33AA33AA, 0xFFFF00AA, 0xFF9900AA, // (5lvl)
                    0x0000BBAA, 0xAA3333AA, 0xAA3333AA, 0xAA3333AA, 0xAA3333AA // 10 rang
                },
                nickname[MAX_PLAYER_NAME], access_level, last_enter[16];
            STRING_GLOBAL = "[#] Никнейм\tУровень\tПоследний вход\n\
                "I"<< "W"Предыдущая страница\t-\t-\n"I">> "W"Следующая страница\t-\t-\n";

            for(new i; i < rows; i++)
            {
                cache_get_value_index(i, 0, nickname, 24);
                cache_get_value_index_int(i, 1, access_level);
                cache_get_value_index(i, 2, last_enter, 16);
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W"{%06x} %s\t"W"%d\t%s\n",
                    STRING_GLOBAL, count, AdminsRangColor[access_level-1] >>> 8, nickname, access_level, last_enter);
                count++;
            }
        }
        case LIST_ID_VEHICLE_NOTES:
        {
            new ownername[MAX_PLAYER_NAME], officername[MAX_PLAYER_NAME], date[20], text[256];

            STRING_GLOBAL = "[#] Владелец\tВыписал\tЗаметка\tДата\n\
                "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n\
                "I"+ "W"Добавить заметку\t-\t-\t-\n";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name(i, "ownername", ownername);
                cache_get_value_name(i, "officername", officername);
                cache_get_value_name(i, "text", text);
                cache_get_value_name(i, "date", date);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t"W"%s\t"W"%.20s%s\t"I"%s\n",
                    STRING_GLOBAL, count, ownername, officername, text, strlen(text) > 20 ? "...":"", date);
                count++;
            }
        }
        case LIST_ID_FRACTION_ONLINE_MEMBERS:
        {
            new getnickname[MAX_PLAYER_NAME],
                frac_rang, frac_warn, bool:status_work;

            STRING_GLOBAL = "[#] Ник\tРанг\tПредупреждения\tСтатус\n\
                "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name(i, "name", getnickname);
                cache_get_value_name_int(i, "rang", frac_rang);
                cache_get_value_name_int(i, "fwarn", frac_warn);
                cache_get_value_name_bool(i, "fwork", status_work);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s[%d]\t"W"%s(%d)\t%d\t%s\n", STRING_GLOBAL,
                    count, getnickname, GetPlayerUserID(p_temp[playerid][p_listitem][i]), GetFractionRangName(p_info[playerid][member], frac_rang), frac_rang, frac_warn,
                    (status_work && (GetFactionType(p_info[playerid][member]) == FACTION_TYPE_GOS ||
                        GetFactionType(p_info[playerid][member]) == FACTION_TYPE_SNN)) ? ("[Работает]") : GetFactionType(p_info[playerid][member]) == FACTION_TYPE_CRIMINAL ? "-" : ("[Не работает]"));
                count++;
            }
        }
        case LIST_ID_FRACTION_ALL_MEMBERS:
        {
            new getnickname[MAX_PLAYER_NAME], getlastonline[20],
                frac_rang, frac_warn, online_status;

            STRING_GLOBAL = "[#] Ник\tРанг\tПредупреждения\tПоследний вход\n\
                "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name(i, "name", getnickname);
                cache_get_value_name_int(i, "rang", frac_rang);
                cache_get_value_name_int(i, "online", online_status);
                cache_get_value_name_int(i, "fwarn", frac_warn);
                cache_get_value_name(i, "lastenter", getlastonline);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s%s\t"W"%s(%d)\t%d\t"I"%s\n", STRING_GLOBAL,
                    count, getnickname, online_status ? "{00b600}[Online]":"{ec453c}[Offline]", GetFractionRangName(p_info[playerid][member], frac_rang), frac_rang, frac_warn, getlastonline);
                count++;
            }
        }
        case LIST_ID_FRACTION_BLACKLIST:
        {
            new player_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME],
                bl_date[20], bl_reasons[32];
            STRING_GLOBAL = "[#] Добавил(-а)\tНик\tПричина\tДата\n\
                "I"<< "W"Предыдущая страница\t-\n"I">> "W"Следующая страница\t-\n";

            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "f_bl_player_name", player_name);
                cache_get_value_name(i, "f_bl_target_name", target_name);
                cache_get_value_name(i, "f_bl_date", bl_date);
                cache_get_value_name(i, "f_bl_reason", bl_reasons);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%s\t%s\n", STRING_GLOBAL, count, player_name, target_name, bl_reasons, bl_date);
                count++;
            }
        }
        case LIST_ID_WBOOK:
        {
            if(p_temp[playerid][p_listitem_int] == -1)
                return SendError(playerid, "Не известная ошибка, повторите попытку.");
            f(STRING_GLOBAL, "[#] Трудования книга\t%s:\t%s\t-\n\
            "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n",
                get_name(p_temp[playerid][PlayerBook]), GetFractionName(p_temp[playerid][p_listitem_int]));

            new PlayerType, PlayerRang, PlayerMember, PlayerTime[24], PlayerReason[60];
            for(new i; i < rows; i ++)
            {
                cache_get_value_name_int(i, "Member",         PlayerMember);
                cache_get_value_name_int(i, "Rang",         PlayerRang);
                cache_get_value_name_int(i, "Type",         PlayerType);
                cache_get_value_name(i,     "Reason",         PlayerReason, 60);
                cache_get_value_name(i,     "CreateData",     PlayerTime, 24);

                if(PlayerType == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" Вступил\tДата: "I"%s\t"W"-\t"W"-\n",
                    STRING_GLOBAL, count, PlayerTime);
                if(PlayerType == 1) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" Покинул\tДата: "I"%s\t"W"Ранг: "I"%d\t"W"Причина: "I"%s\n",
                    STRING_GLOBAL, count, PlayerTime, PlayerRang, PlayerReason);
                count++;
            }
        }
        case LIST_ID_FAMILY_OFFLINE_MEMBERS:
        {
            new family_nickname[MAX_PLAYER_NAME], getlastonline[16], family_rang_id, family_warns,
                family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1)
                return 1;
            STRING_GLOBAL = "[#] Ник\tРанг\tПредупреждения\tПоследний вход\n\
                "I"<< "W"Предыдущая страница\t-\t-\t-\n"I">> "W"Следующая страница\t-\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name(i, "name",  family_nickname, 20);
                cache_get_value_name_int(i, "family_rang", family_rang_id);
                cache_get_value_name_int(i, "family_warn", family_warns);
                cache_get_value_name(i, "lastenter", getlastonline, 16);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s(%d)\t%d\t"I"%s\n", STRING_GLOBAL,
                    count, family_nickname, FAMILY_RANG[family_idx][family_rang_id-1], family_rang_id, family_warns, getlastonline);
                count++;
            }
        }
        case LIST_ID_FAMILY_LOG, LIST_ID_FAMILY_NOTIFY:
        {
            new info_string[256], info_date[20];
            STRING_GLOBAL = "[#] Текст\tДата\n\
                "I"<< "W"Предыдущая страница\t-\n"I">> "W"Следующая страница\t-\n";

            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "text", info_string);
                cache_get_value_name(i, "date", info_date);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\n", STRING_GLOBAL, count, info_string, info_date);
                count++;
            }
        }
        case LIST_ID_FAMILY_BLACKLIST:
        {
            new player_name[MAX_PLAYER_NAME], target_name[MAX_PLAYER_NAME],
                bl_date[20], bl_reasons[32];
            STRING_GLOBAL = "[#] Добавил(-а)\tНик\tПричина\tДата\n\
                "I"<< "W"Предыдущая страница\t-\n"I">> "W"Следующая страница\t-\n";

            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "player_name", player_name);
                cache_get_value_name(i, "target_name", target_name);
                cache_get_value_name(i, "reason", bl_reasons);
                cache_get_value_name(i, "date", bl_date);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%s\t%s\n", STRING_GLOBAL, count, player_name, target_name, bl_reasons, bl_date);
                count++;
            }
        }
        case LIST_ID_TC_OFFLINE_MEMBERS:
        {
            new temp_nickname[MAX_PLAYER_NAME], temp_tc_rank, temp_tc_salary, temp_tc_salary_all, temp_lastenter[16];

            STRING_GLOBAL = "[#] Ник\tРанг\tПринесенный заработок\tПоследний вход\n\
                "I"<< "W"Предыдущая страница\t-\t-\n"I">> "W"Следующая страница\t-\t-\n"W"";

            new idx = p_temp[playerid][p_tc_id];

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name(i, "name",  temp_nickname, 20);
                switch(b_info[idx][_tip])
                {
                    case B_TAXI:
                    {
                        cache_get_value_name_int(i, "taxi_rank", temp_tc_rank);
                        cache_get_value_name_int(i, "taxi_salary", temp_tc_salary);
                        cache_get_value_name_int(i, "taxi_salary_all", temp_tc_salary_all);
                    }
                    case B_TRUCKER:
                    {
                        cache_get_value_name_int(i, "tc_rank", temp_tc_rank);
                        cache_get_value_name_int(i, "tc_salary", temp_tc_salary);
                        cache_get_value_name_int(i, "tc_salary_all", temp_tc_salary_all);
                    }
                }
                cache_get_value_name(i, "lastenter", temp_lastenter, 16);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s(%d)\tСегодня: %d$ | Всего: %d$\t"I"%s\n", STRING_GLOBAL, count, temp_nickname, TransportCompanyRankName[temp_tc_rank], temp_tc_rank, temp_tc_salary, temp_tc_salary_all, temp_lastenter);
                count++;
            }
        }
        case LIST_ID_WANTED_ONLINE, LIST_ID_WANTED_OFFLINE:
        {
            new temp_nickname[MAX_PLAYER_NAME], wanted_count;

            STRING_GLOBAL = "[#] Ник\tКоличество звезд\n\
                "I"<< "W"Предыдущая страница\t-\t-\n"I">> "W"Следующая страница\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "name",  temp_nickname, 20);
                cache_get_value_name_int(i, "wanted", wanted_count);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d\n", STRING_GLOBAL, count, temp_nickname, wanted_count);
                count++;
            }
        }
        case LIST_ID_PROMOCODE:
        {
            new temp_username[MAX_PLAYER_NAME], temp_level, temp_time[20], temp_donate;

            STRING_GLOBAL = "[#] Ник\tУровень\tДата использования\tЗаработано Flin Money\n\
                "I"<< "W"Предыдущая страница\t-\t-\n"I">> "W"Следующая страница\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name(i, "name",  temp_username, MAX_PLAYER_NAME);
                cache_get_value_name_int(i, "level", temp_level);
                cache_get_value_name(i, "promocode_time",  temp_time, 20);
                cache_get_value_name_int(i, "promocode_donate", temp_donate);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d\t%s\t%d\n", STRING_GLOBAL, count, temp_username, temp_level, temp_time, temp_donate);
                count++;
            }
        }
        case LIST_ID_GIVE_ITEMS:
        {
            new extraData[3], itemID, time_cleaner, date_time[6];

            STRING_GLOBAL = "[#] Предмет: Количество\tВремя удаления\n\
                "I"<< "W"Предыдущая страница\t-\t-\n"I">> "W"Следующая страница\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name_int(i, "itemID", itemID);
                cache_get_value_name_int(i, "extraData1", extraData[0]);
                cache_get_value_name_int(i, "extraData2", extraData[1]);
                cache_get_value_name_int(i, "extraData3", extraData[2]);
                cache_get_value_name_int(i, "extraData3", extraData[2]);
                cache_get_value_name_int(i, "time", time_cleaner);
                
                gmtime(time_cleaner, date_time[0],date_time[1],date_time[2],date_time[3],date_time[4],date_time[5]);
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%02d:%02d %02d/%02d/%02d\n", STRING_GLOBAL, count, 
                    GetPrizeItemsName(itemID, extraData[0], extraData[1], extraData[2]), 
                    date_time[3], date_time[4], date_time[2], date_time[1], date_time[0]);
                count++;
            }
        }
        case LIST_ID_TIME_OWNER_BIZZ:
        {
            new ownername[MAX_PLAYER_NAME], namebiz[64], owned_at, paydays_received,
                date_time[6];

            STRING_GLOBAL = "[#] Бизнес\tВладелец\tСтарт отсчёта\tНаигранные часы\n\
                "I"<< "W"Предыдущая страница\t-\t-\n"I">> "W"Следующая страница\t-\t-\n"W"";

            for(new i; i < rows; i++)
            {
                cache_get_value_name_int(i, "b_mysql_id", p_temp[playerid][p_listitem][i]);
                cache_get_value_name(i, "b_name", namebiz);
                cache_get_value_name(i, "owner", ownername);
                cache_get_value_name_int(i, "b_owned_at", owned_at);
                cache_get_value_name_int(i, "b_paydays_received", paydays_received);

                gmtime(owned_at, date_time[0],date_time[1],date_time[2],date_time[3],date_time[4],date_time[5]);

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s[%d]\t%s\t%02d:%02d %02d/%02d/%02d\t%d\n", STRING_GLOBAL, count+1, 
                    namebiz, p_temp[playerid][p_listitem][i], ownername, date_time[3], date_time[4], 
                    date_time[2], date_time[1], date_time[0], paydays_received);
                count++;
            }
        }
    }
    ShowPlayerDialog(playerid, D_DIALOG_LIST_TYPE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Flin RolePlay", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

// TD LIST [no mysql]
ShowPlayerListTD(playerid, list_id)
{
    for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
    p_temp[playerid][list_page] = 1;
    p_temp[playerid][list_type] = list_id;
    ShowTextDrawForPlayer(playerid, TD_ID_LIST_PAGE);
    UpdatePlayerListTD(playerid);
    return 1;
}

UpdatePlayerListTD(playerid)
{
    new page_id = p_temp[playerid][list_page]-1,
        list_id = p_temp[playerid][list_type],
        count = GetMaxCountTDList(playerid, list_id),
        count_td;
    if(page_id < 0) page_id = 0;
    if(count < 10) for(new i= 27; i != 19; i--) TextDrawHideForPlayer(playerid , TD_ListPage[i]);
    switch(list_id)
    {
        case LIST_TD_ID_DONATE_REAL_CARS, LIST_TD_ID_DONATE_VEHICLE, LIST_TD_ID_DONATE_SKIN, LIST_TD_ID_DONATE_REAL_SKIN, LIST_TD_ID_DONATE_ACCESSORIES, LIST_TD_ID_DONATE_VEHICLE_TUNE, LIST_TD_ID_DONATE_TENT:
        {
            new model_id,
                start_count, idx, price[2], dtype = -1,
                end_count = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL;
            count = 0;
            
            switch(list_id)
            {
                case LIST_TD_ID_DONATE_REAL_CARS: dtype = TYPE_DONATE_REAL_CARS;
                case LIST_TD_ID_DONATE_VEHICLE: dtype = TYPE_DONATE_VEHICLE;
                case LIST_TD_ID_DONATE_SKIN: dtype = TYPE_DONATE_SKIN;
                case LIST_TD_ID_DONATE_REAL_SKIN: dtype = TYPE_DONATE_REAL_SKIN;
                case LIST_TD_ID_DONATE_ACCESSORIES: dtype = TYPE_DONATE_ACCESSORIES;
                case LIST_TD_ID_DONATE_VEHICLE_TUNE: dtype = TYPE_DONATE_VEHICLE_TUNE;
                case LIST_TD_ID_DONATE_TENT: dtype = TYPE_DONATE_TENT;
            }
            if(dtype == -1) return 1;
    
            for(new i = 0, j = sizeof(DonateInfo); i < j; i++)
            {
                if(DonateInfo[i][dType] != dtype) continue;
                if(start_count < page_id*MAX_TD_LIST_CELL)
                {
                    start_count++;
                    continue;
                }
                if(start_count+count >= end_count) break;

                if(DonateInfo[i][dType] == TYPE_DONATE_REAL_SKIN || 
                    DonateInfo[i][dType] == TYPE_DONATE_TENT || 
                    DonateInfo[i][dType] == TYPE_DONATE_ACCESSORIES ||
                    DonateInfo[i][dType] == TYPE_DONATE_VEHICLE_TUNE)
                {
                    idx = DonateInfo[i][dIDx];
                    model_id = ItemsInfo[idx][iModel];
                    PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], ItemsInfo[idx][iObjectPos][0], ItemsInfo[idx][iObjectPos][1], ItemsInfo[idx][iObjectPos][2], ItemsInfo[idx][iObjectPos][3]); 
                }
                else
                {
                    model_id = DonateInfo[i][dIDx];
                    PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], -10.0, 0.0, 45.0, 1.0);
                }
                STRING_GLOBAL[0] = EOS;
                price[0] = DonateInfo[i][dPrice];
                price[1] = price[0] - floatround((price[0] / 100) * DonateInfo[i][dPercent]);
                if(DonateInfo[i][dStatus] == true) f(STRING_GLOBAL, "~b~%d FM ~w~> ~y~%d FM", price[0], price[1]);
                else f(STRING_GLOBAL, "%d FM", price[0]);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);

                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count], 0x00000005);
                if(list_id == LIST_TD_ID_DONATE_REAL_CARS || list_id == LIST_TD_ID_DONATE_VEHICLE) 
                    PlayerTextDrawSetPreviewVehCol(playerid, PTD_ListPage[playerid][count], 1, 3);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+10]);

                if(DonateInfo[i][dStatus] == true)
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "~w~Discount: ~r~%.0f%%", DonateInfo[i][dPercent]);
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+21], STRING_GLOBAL);
                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+21]);
                }
                else PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count+21]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count < MAX_TD_LIST_CELL)
            {
                for(new i = count; i < MAX_TD_LIST_CELL; i++)
                {
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+21]);
                    p_temp[playerid][p_listitem][i] = -1;
                }
            }
        }
        case LIST_TD_ID_HOT_DEALS_OVER_SIZED:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL003! Попробуйте еще раз.");
            new model_id,
                start_count, idx, price[2],
                end_count = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL;
            count = 0;

            for(new i = 0, j = sizeof(DonateInfo); i < j; i++)
            {
                if(DonateInfo[i][dType] > TYPE_DONATE_TENT) continue;
                if(DonateInfo[i][dStatus] == false) continue;
                if(start_count < page_id*MAX_TD_LIST_CELL)
                {
                    start_count++;
                    continue;
                }
                if(start_count+count >= end_count) break;
                
                if(DonateInfo[i][dType] == TYPE_DONATE_TENT || 
                    DonateInfo[i][dType] == TYPE_DONATE_ACCESSORIES ||
                    DonateInfo[i][dType] == TYPE_DONATE_VEHICLE_TUNE)
                {
                    idx = DonateInfo[i][dIDx];
                    model_id = ItemsInfo[idx][iModel];
                    PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], ItemsInfo[idx][iObjectPos][0], ItemsInfo[idx][iObjectPos][1], ItemsInfo[idx][iObjectPos][2], ItemsInfo[idx][iObjectPos][3]); 
                }
                else
                {
                    model_id = DonateInfo[i][dIDx];
                    PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], -10.0, 0.0, 45.0, 1.0);
                    if(DonateInfo[i][dType] == TYPE_DONATE_REAL_CARS || DonateInfo[i][dType] == TYPE_DONATE_VEHICLE) 
                        PlayerTextDrawSetPreviewVehCol(playerid, PTD_ListPage[playerid][count], 1, 3);
                }
                STRING_GLOBAL[0] = EOS;
                price[0] = DonateInfo[i][dPrice];
                price[1] = price[0] - floatround((price[0] / 100) * DonateInfo[i][dPercent]);
                if(DonateInfo[i][dStatus] == true) f(STRING_GLOBAL, "~b~%d FM ~w~> ~y~%d FM", price[0], price[1]);
                else f(STRING_GLOBAL, "%d FM", price[0]);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);

                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count], 0x00000005);
                
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+10]);

                if(DonateInfo[i][dStatus] == true)
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "~w~Discount: ~r~%.0f%%", DonateInfo[i][dPercent]);
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+21], STRING_GLOBAL);
                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+21]);
                }
                else PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count+21]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count < MAX_TD_LIST_CELL)
            {
                for(new i = count; i < MAX_TD_LIST_CELL; i++)
                {
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+21]);
                    p_temp[playerid][p_listitem][i] = -1;
                }
            }
        }
        /*
        case LIST_TD_ID_PRICE_ACCESSORIES:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL003! Попробуйте еще раз.");
            new model_id,
                start_count,
                end_count = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL;
            count = 0;

            for(new i = 0, j = sizeof(ItemsInfo); i < j; i++)
            {
                if(ItemsInfo[i][iType] != TYPE_ITEMS_ACCESSORIES) continue;
                if(start_count < page_id*MAX_TD_LIST_CELL)
                {
                    start_count++;
                    continue;
                }
                if(start_count+count >= end_count) break;

                model_id = ItemsInfo[i][iModel];

                PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "%d$", ItemsInfo[i][iPrice]);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);

                PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count], 0x00000005);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+10]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count < MAX_TD_LIST_CELL)
            {
                for(new i = count; i < MAX_TD_LIST_CELL; i++)
                {
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+21]);
                    p_temp[playerid][p_listitem][i] = -1;
                }
            }
        }
        */
        case LIST_TD_ID_BREAK:
        {
            new object_id;
            for(new i = page_id*MAX_TD_LIST_CELL, j = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL; i < j; i++)
            {
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count_td]);
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count_td+10]);
                if(i < count) {
                    object_id = BreakListObjectIDx[i];
                    PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count_td], object_id);
                    //if(object_id == 2899)
                    //    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], "CLOSED");
                    //else
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], "_");

                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count_td], 0.0, 0.0, 0.0, 1.0);
                    PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count_td], 0x00000005);

                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count_td]);
                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count_td+10]);
                }
                count_td++;
            }
        }
        case LIST_TD_ID_FAMILY_BUY_VEHICLE:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL002! Попробуйте еще раз.");

            new model_id,
                start_count,
                end_count = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL;
            count = 0;

            for(new i = 0, j = sizeof(gVehicleData); i < j; i++)
            {
                model_id = gVehicleData[i][E_VD_ID];
                if(model_id == 508) continue;
                if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_PLANE && (model_id != 469 && model_id != 487)) continue;
                if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE && 
                    (model_id != 427 && model_id != 470 && model_id != 490 && model_id != 528 && model_id != 573 && model_id != 596 &&
                    model_id != 597 && model_id != 598 && model_id != 599 && model_id != 601)) continue;
                
                if(start_count < page_id*MAX_TD_LIST_CELL)
                {
                    start_count++;
                    continue;
                }
                if(start_count+count >= end_count) break;
                
                PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE)
                {
                    new fc_price = GetVehicleData(model_id, E_VD_PRICE)/2000;
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "%d$~n~%d FC", GetVehicleData(model_id, E_VD_PRICE), fc_price);
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);
                }
                else if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS)
                {
                    new custom_id = GetSlotVehicleModelSync(model_id);
                    if(custom_id == -1) return SendError(playerid, "Не известная ошибка: RC0709");
                    new rc_price = customVehModels[custom_id][ModelPrice];
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "%d FM", rc_price);
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);
                }
                else
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "%d$", GetVehicleData(model_id, E_VD_PRICE));
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);
                }

                PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], -10.0, 0.0, 45.0, 1.0);
                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count], 0x00000005);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+10]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count < MAX_TD_LIST_CELL)
            {
                for(new i = count; i < MAX_TD_LIST_CELL; i++)
                {
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+21]);
                    p_temp[playerid][p_listitem][i] = -1;
                }
            }
            return 1;
        }
        case LIST_TD_ID_FRACTION_SET_SKIN:
        {
            new frac_id = GetPVarInt(playerid, #FRACTION_ID),
                sex_id = GetPVarInt(playerid, #SEX_ID),
                skin_idx;

            DeletePVar(playerid, #FRACTION_ID);
            DeletePVar(playerid, #SEX_ID);

            for(new i = 0; i < count; i++)
            {
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);

                skin_idx = sex_id == F_MAN_SKIN ? FractionsData[frac_id][fManSkin][i] : FractionsData[frac_id][fWomanSkin][i];

                PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][i], skin_idx);

                f(STRING_GLOBAL, "RANK: %d", i+1);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][i+10], STRING_GLOBAL);

                PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][i], 0.0, 0.0, 0.0, 1.0);
                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][i], 0x00000005);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][i]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][i+10]);

                p_temp[playerid][p_listitem][i] = skin_idx;
            }
        }
        case LIST_TD_ID_FRACTION_CHANGE_SKIN:
        {
            new frac_id = p_info[playerid][member],
                targetid = p_temp[playerid][p_listitem_int],
                old_skin,
                skin_idx;

            for(new i = 0;i < count; i++)
            {
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);

                skin_idx = p_info[targetid][sex] == 2 ? FractionsData[frac_id][fManSkin][i] : FractionsData[frac_id][fWomanSkin][i];
                if(old_skin == skin_idx) continue;
                old_skin = skin_idx;
                PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][i], skin_idx);
                if(p_info[targetid][fskin] == skin_idx)
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][i+10], "Active");
                else
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][i+10], "_");
                PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][i], 0.0, 0.0, 0.0, 1.0);
                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][i], 0x00000005);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][i]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][i+10]);

                p_temp[playerid][p_listitem][i] = skin_idx;
            }
        }
        case LIST_TD_ID_FAMILY_SELECT_SLOT, LIST_TD_ID_FAMILY_CHANGE_SKIN:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL002! Попробуйте еще раз.");
            new skin_idx,
                rang_id = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:rang"),
                sex_id = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:sex"),
                family_idx = GetPlayerFamilyID(playerid);
            for(new i = page_id*MAX_TD_LIST_CELL, j = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL; i < j; i++)
            {
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count_td]);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], "_");
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count_td+21]);
                if(i < count) {
                    skin_idx = FamilyData[family_idx][fSkinID][i];
                    if(skin_idx != INVALID_SKIN_ID)
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count_td], ItemsInfo[skin_idx][iModel]);
                        if(list_id == LIST_TD_ID_FAMILY_CHANGE_SKIN &&
                            ((sex_id == 2 && skin_idx == FamilyData[family_idx][fSkinMan][rang_id]) ||
                            (sex_id == 1 && skin_idx == FamilyData[family_idx][fSkinWoman][rang_id])))
                        {
                            PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], "Active");
                        }
                    }
                    else
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count_td], 18631);
                        PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], "Free Slot");
                    }
                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count_td], 0.0, 0.0, 0.0, 1.0);
                    PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count_td], 0x00000005);

                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count_td]);
                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count_td+10]);
                }
                count_td++;
            }
        }
        case LIST_TD_ID_FAMILY_BUY_SKIN:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL001! Попробуйте еще раз.");
            new sex_id = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:sex");
            for(new i = page_id*MAX_TD_LIST_CELL, j = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL; i < j; i++)
            {
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count_td]);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], "_");
                PlayerTextDrawHide(playerid, PTD_ListPage[playerid][count_td+21]);
                if(i < count) {
                    STRING_GLOBAL[0] = EOS;
                    if(sex_id == 1)
                    {
                        if(i < sizeof(skinBuyMale)-1)
                        {
                            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count_td], ItemsInfo[skinBuyMale[i]][iModel]);
                            f(STRING_GLOBAL, "%d$", ItemsInfo[skinBuyMale[i]][iPrice]);
                        }
                    }
                    else
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count_td], ItemsInfo[skinBuyMan[i]][iModel]);
                        f(STRING_GLOBAL, "%d$", ItemsInfo[skinBuyMan[i]][iPrice]);
                    }

                    PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count_td], 0.0, 0.0, 0.0, 1.0);
                    PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count_td+10], STRING_GLOBAL);
                    PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count_td], 0x00000005);

                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count_td]);
                    PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count_td+10]);
                }
                count_td++;
            }
        }

        case LIST_TD_ID_FAMILY_TRANSFER_SKIN:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL004! Попробуйте еще раз.");
            new model_id,
                start_count,
                end_count = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL;
            count = 0;

            new max_slot, min_slot;
            GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
            if(min_slot >= max_slot) return 0;
            min_slot++, max_slot++;

            new itemID;
            for(new i = min_slot, j = max_slot; i < j; i++)
            {
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID) continue;
                itemID = InventoryPlayer[playerid][i][inv_item_id];
                if(ItemsInfo[itemID][iType] != TYPE_ITEMS_SKINS) continue;
                if(start_count < page_id*MAX_TD_LIST_CELL)
                {
                    start_count++;
                    continue;
                }
                if(start_count+count >= end_count) break;

                model_id = ItemsInfo[itemID][iModel];
                PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], "_");

                PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count], 0x00000005);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+10]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count < MAX_TD_LIST_CELL)
            {
                for(new i = count; i < MAX_TD_LIST_CELL; i++)
                {
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+21]);
                    p_temp[playerid][p_listitem][i] = -1;
                }
            }
        }

        case LIST_TD_ID_VEHICLE_TUNE:
        {
            if(count == -1) return SendError(playerid, "Неизвестная ошибка: BUG-TDL003! Попробуйте еще раз.");
            new model_id,
                start_count,
                end_count = page_id*MAX_TD_LIST_CELL+MAX_TD_LIST_CELL;
            count = 0;

            for(new i = 0, j = sizeof(ItemsInfo); i < j; i++)
            {
                if(ItemsInfo[i][iType] != TYPE_ITEMS_VEHICLE_TUNE || ItemsInfo[i][iPrice] == 0) continue;
                if(start_count < page_id*MAX_TD_LIST_CELL)
                {
                    start_count++;
                    continue;
                }
                if(start_count+count >= end_count) break;

                model_id = ItemsInfo[i][iModel];
                PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][count], model_id);
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "%d$", ItemsInfo[i][iPrice]);
                PlayerTextDrawSetString(playerid, PTD_ListPage[playerid][count+10], STRING_GLOBAL);

                PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][count], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
                PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][count], 0x00000005);

                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_ListPage[playerid][count+10]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count < MAX_TD_LIST_CELL)
            {
                for(new i = count; i < MAX_TD_LIST_CELL; i++)
                {
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+10]);
                    PlayerTextDrawHide(playerid, PTD_ListPage[playerid][i+21]);
                    p_temp[playerid][p_listitem][i] = -1;
                }
            }
        }
        default: return 1;
    }
    return 1;
}

OnDialogResponseTDList(playerid, td_idx)
{
    if(p_temp[playerid][list_type] != LIST_TD_ID_FAMILY_SELECT_SLOT &&
        p_temp[playerid][list_type] != LIST_TD_ID_VEHICLE_TUNE) //no bug!
        HideTextDrawForPlayer(playerid, TD_ID_LIST_PAGE);
    new idx = td_idx;
    td_idx += (p_temp[playerid][list_page]-1)*MAX_TD_LIST_CELL;
    new list_id = p_temp[playerid][list_type];
    switch(list_id)
    {
        case LIST_TD_ID_DONATE_REAL_CARS, LIST_TD_ID_DONATE_VEHICLE, LIST_TD_ID_DONATE_SKIN, LIST_TD_ID_DONATE_REAL_SKIN, LIST_TD_ID_DONATE_ACCESSORIES, LIST_TD_ID_DONATE_VEHICLE_TUNE, LIST_TD_ID_DONATE_TENT, LIST_TD_ID_HOT_DEALS_OVER_SIZED:
        {
            new i = p_temp[playerid][p_listitem][idx];
            if(i < 0) return 1;
            new price = DonateInfo[i][dPrice];
            if(DonateInfo[i][dStatus] == true) price = price - floatround((price / 100) * DonateInfo[i][dPercent]);
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""W"Вы действительно хотите приобрести %s \"%s\" за %d Flin Money?", DonateName[DonateInfo[i][dType]], DonateInfo[i][dName], price);
            ShowPlayerDialog(playerid, D_DONATE_BUY, DIALOG_STYLE_MSGBOX, ""I"Донат", STRING_MIN, "Да", "Нет");
            p_temp[playerid][donate_parameter][0] = i;
            p_temp[playerid][donate_parameter][1] = price;
        }
        /*
        case LIST_TD_ID_PRICE_ACCESSORIES:
        {
            new i = p_temp[playerid][p_listitem][idx];
            if(!(0 <= i <= sizeof(ItemsInfo)-1) || ItemsInfo[i][iType] != TYPE_ITEMS_ACCESSORIES) return 1;
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""W"Название: "I"%s\n"W"Стоимость: "I"%d$\n", ItemsInfo[i][iName], ItemsInfo[i][iPrice]);
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Стоимость аксессуаров", STRING_MIN, "Назад", "");
        }
        */

        case LIST_TD_ID_VEHICLE_TUNE:
        {
            new i = p_temp[playerid][p_listitem][idx];
            if(!(0 <= i <= MAX_ITEMS-1) || ItemsInfo[i][iType] != TYPE_ITEMS_VEHICLE_TUNE || ItemsInfo[i][iPrice] == 0) return 1;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Вы действительно хотите приобрести "I"\"%s\" "W"за "I"%d$ "W"?\n\n\
                После покупки деталь появится у вас инвентаре, после чего вы можете ее одеть "I"(/inv в Т/С).", ItemsInfo[i][iName], ItemsInfo[i][iPrice]);
            ShowPlayerDialog(playerid, D_SERVICE_BUY_VEHICLE_TUNE, DIALOG_STYLE_MSGBOX, ""I"Деталь тюнинга", STRING_GLOBAL, "Купить", "Отмена");
            p_temp[playerid][p_listitem_int] = i;
        }

        case LIST_TD_ID_BREAK:
        {
            new total = 0;
            for(new i = 0; i < MAX_PLAYER_BREAK; i++)
            {
                if(BreakObject[playerid][i] == 0)
                {
                    SendInfo(playerid, "С помощью кнопки ALT установите ограждение в желаемом месте.");
                    BreakObject[playerid][i] = CreateObject(BreakListObjectIDx[td_idx], 0, 0, 0, 0, 0, 0);
                    AttachObjectToPlayer(BreakObject[playerid][i], playerid, 0, 1, -BreakListCoord[td_idx], 0, 0, 90);
                    SetPVarInt(playerid, "LoadBreak", i+1);
                    SetPVarInt(playerid, "LoadBreakListitem", td_idx);
                    SetPVarInt(playerid, "BreakObject", BreakListObjectIDx[td_idx]);
                    total++;
                    break;
                }
            }
            if(total == 0) return SendError(playerid, "Вы не можете поставить больше объектов.");
        }
        case LIST_TD_ID_FAMILY_BUY_VEHICLE:
        {
            new i = p_temp[playerid][p_listitem][idx];
            if(!(0 <= i <= sizeof(gVehicleData)-1)) return 1;
            new model_id = gVehicleData[i][E_VD_ID];
            if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE && 
                    (gVehicleData[i][E_VD_ID] != 427 &&
                    gVehicleData[i][E_VD_ID] != 470 &&
                    gVehicleData[i][E_VD_ID] != 490 &&
                    gVehicleData[i][E_VD_ID] != 528 &&
                    gVehicleData[i][E_VD_ID] != 573 &&
                    gVehicleData[i][E_VD_ID] != 596 &&
                    gVehicleData[i][E_VD_ID] != 597 &&
                    gVehicleData[i][E_VD_ID] != 598 &&
                    gVehicleData[i][E_VD_ID] != 599 &&
                    gVehicleData[i][E_VD_ID] != 601))
                return SendError(playerid, "Не доступно к покупке.");
            if(model_id == 508 || (GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_PLANE && (model_id != 469 && model_id != 487)))
                return SendError(playerid, "Не доступно к покупке.");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            new houseId = FamilyData[family_idx][fHouseID];
            if(houseId == INVALID_HOUSE_ID) return SendError(playerid, "У семьи нет дома.");
            if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_BOAT && h_info[houseId][h_boat_status] == 0)
                return SendError(playerid, "У Вашей семьи нет дома с выходом на пирс.");
            if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_PLANE && (h_info[houseId][h_air_pos][0] == 0.0 && h_info[houseId][h_air_pos][1] == 0.0))
                return SendError(playerid, "У Вашей семьи нет дома с вертолетной площадкой.");

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Название: "I"%s (ID: %d)", GetVehicleName(INVALID_VEHICLE_ID, model_id), model_id);

            if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE)
            {
                new fc_price = GetVehicleData(model_id, E_VD_PRICE)/2000;
                f(STRING_GLOBAL, "%s"W"\n\nСтоимость: "I"%d$ и %d семейных монет"W"\n", STRING_GLOBAL, GetVehicleData(model_id, E_VD_PRICE), fc_price);
            }
            else if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS)
            {
                new custom_id = GetSlotVehicleModelSync(model_id);
                if(custom_id == -1) return SendError(playerid, "Не известная ошибка: RC0709");
                new rc_price = customVehModels[custom_id][ModelPrice];
                f(STRING_GLOBAL, "%s"W"\n\nСтоимость: "I"%d FM\n", STRING_GLOBAL, rc_price);
            }
            else f(STRING_GLOBAL, "%s"W"\n\nСтоимость: "I"%d$"W"\n", STRING_GLOBAL, GetVehicleData(model_id, E_VD_PRICE));

            if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_CAR || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_MOTO)
                f(STRING_GLOBAL, "%s"W"Макс. скорость: "I"%d KM/H"W"\nМакс. вместимость бака: "I"%d"W"\n", STRING_GLOBAL, floatround(GetVehicleData(model_id, E_VD_MAX_SPEED)), GetVehicleData(model_id, E_VD_MAX_FUEL));
            f(STRING_GLOBAL, "%s\n"W"Класс: "I"%s"W"\nТип: "I"%s"W"", STRING_GLOBAL, vehicle_class_name[GetVehicleData(model_id, E_VD_CLASS)], vehicle_type_name[GetVehicleData(model_id, E_VD_TYPE)]);
            ShowPlayerDialog(playerid, D_FAMILY_BUY_VEHICLE_ACT, DIALOG_STYLE_MSGBOX, ""I"Покупка транспорта", STRING_GLOBAL, "Далее", "Отмена");
            p_temp[playerid][family_car_select] = model_id;
            p_temp[playerid][p_listitem][30] = td_idx;
        }
        case LIST_TD_ID_FRACTION_SET_SKIN:
        {
            p_temp[playerid][p_listitem][32] = td_idx;
            ShowDialogFractionSkins(playerid);
        }
        case LIST_TD_ID_FRACTION_CHANGE_SKIN:
        {
            new target = p_temp[playerid][p_listitem_int];
            p_temp[playerid][p_listitem_int] = -1;
            new skin_id = p_temp[playerid][p_listitem][td_idx];
            if(skin_id == 0 || skin_id == -1 || !IsPlayerConnected(target)) return 1;
            if(skin_id == p_info[target][fskin]) return SendError(playerid, "У игрока этот скин.");
            p_info[target][fskin] = skin_id;
            if(p_info[target][fwork] == true) SetPlayerSkinEx(playerid);
            SendAccess(playerid, "Вы изменили %s фракционный скин на %d.", get_name(target), skin_id);
            SendInfo(target, "%s изменили Вам фракционный скин на %d.", get_name(playerid), skin_id);
        }
        case LIST_TD_ID_FAMILY_CHANGE_SKIN:
        {
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            new skin_idx = FamilyData[family_idx][fSkinID][td_idx],
                rang_id = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:rang"),
                sex_id = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:sex");
            DeletePVar(playerid, "FAMILY_CHANGE_SKIN:rang");
            DeletePVar(playerid, "FAMILY_CHANGE_SKIN:sex");
            if(ItemsInfo[skin_idx][iType] != TYPE_ITEMS_SKINS)
                return SendError(playerid, "Купленого скина в этой ячейке нет.");
            if(rang_id == -1) return SendError(playerid, "Обновите лаунчер! [DEBUG:1001]");
            if(sex_id == 1)
            {
                if(!IsSkinFemale(ItemsInfo[skin_idx][iModel]))
                    return SendError(playerid, "Вы пытаетесь выдать мужской скин в женский слот.");
                FamilyData[family_idx][fSkinWoman][rang_id] = skin_idx;
            }
            else
            {
                if(IsSkinFemale(ItemsInfo[skin_idx][iModel]))
                    return SendError(playerid, "Вы пытаетесь выдать женский скин в мужской слот.");
                FamilyData[family_idx][fSkinMan][rang_id] = skin_idx;
            }
            foreach(new i: Player)
            {
                if(p_info[i][family_id] != p_info[playerid][family_id] ||
                    GetFamilyRang(i)-1 != rang_id ||
                    sex_id != p_info[i][sex] ||
                    p_info[i][fwork] == true ||
                    p_info[i][p_settings][SKIN_DEFAULT] == 0) continue;
                SetPlayerSkinEx(i);
            }
            MysqlUpdateFamilySkins(family_idx);
            SendAccess(playerid, "Вы выбрали новый скин для ранга %s(%d).", FAMILY_RANG[family_idx][rang_id], rang_id+1);
        }
        case LIST_TD_ID_FAMILY_SELECT_SLOT:
        {
            if(td_idx > 14) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
            new skin_idx = FamilyData[p_temp[playerid][family_game_id]][fSkinID][td_idx];
            if(skin_idx != INVALID_SKIN_ID) SendInfo(playerid, "У семьи в этом слоте есть скин %d, он будет заменен.", skin_idx);

            SetPVarInt(playerid, "FAMILY_CHANGE_SKIN:idx", td_idx+1);
            ShowPlayerListTD(playerid, GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:sex") ? LIST_TD_ID_FAMILY_BUY_SKIN : LIST_TD_ID_FAMILY_TRANSFER_SKIN);
        }
        case LIST_TD_ID_FAMILY_BUY_SKIN:
        {
            new sex_id = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:sex");
            DeletePVar(playerid, "FAMILY_CHANGE_SKIN:sex");
            p_temp[playerid][change_skin_idx] = sex_id == 1 ? skinBuyMale[td_idx] :skinBuyMan[td_idx]; //skin id
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Вы действительно хотите купить данный скин за "I"%d$", sex_id == 1 ? ItemsInfo[skinBuyMale[td_idx]][iPrice] : ItemsInfo[skinBuyMan[td_idx]][iPrice]);
            ShowPlayerDialog(playerid, D_FAMILY_BUY_SKINS, DIALOG_STYLE_MSGBOX, ""I"Купить скин", STRING_GLOBAL, "Да","Отмена");
        }
        case LIST_TD_ID_FAMILY_TRANSFER_SKIN:
        {
            new i = p_temp[playerid][p_listitem][td_idx];
            if(i == -1) return 1;
            p_temp[playerid][p_listitem_int] = i;
            new item_id = InventoryPlayer[playerid][i][inv_item_id];

            if(item_id <= 0)
                return SendError(playerid, "Неизвестная ошибка: BUG-F105! Попробуйте еще раз.");
            if(ItemsInfo[item_id][iType] != TYPE_ITEMS_SKINS)
                return SendError(playerid, "Неизвестная ошибка: BUG-F205! Попробуйте еще раз.");

            new skin_price = 50000, fc_price = 10;
            if(item_id > 311) 
            {
                skin_price *= 10; 
                fc_price *= 5;
            }
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Вы действительно хотите передать данный скин "I"%s "W"в семью?\n\n\
                Цена передачи: %d$ и %d FC", ItemsInfo[item_id][iName], skin_price, fc_price);
            ShowPlayerDialog(playerid, D_FAMILY_TRANSFER_SKINS, DIALOG_STYLE_MSGBOX, ""I"Передача скина", STRING_GLOBAL, "Да","Отмена");
        }
    }
    return 1;
}
//Обработчик нажатия "Отмена"
CancelButtonTDList(playerid)
{
    HideTextDrawForPlayer(playerid, TD_ID_LIST_PAGE);
    switch(p_temp[playerid][list_type])
    {
        case LIST_TD_ID_DONATE_REAL_CARS, LIST_TD_ID_DONATE_VEHICLE, LIST_TD_ID_DONATE_SKIN, LIST_TD_ID_DONATE_REAL_SKIN, LIST_TD_ID_DONATE_ACCESSORIES, LIST_TD_ID_DONATE_VEHICLE_TUNE, LIST_TD_ID_DONATE_TENT, LIST_TD_ID_HOT_DEALS_OVER_SIZED: callcmd::donate(playerid, "/0");
        case LIST_TD_ID_VEHICLE_TUNE:
        {
            ShowTextDrawForPlayer(playerid, TD_ID_SERVICE_TUNE);
        }
    }
    return 1;
}

GetMaxCountTDList(playerid, list_id)
{
    switch(list_id)
    {
        //case LIST_TD_ID_PRICE_ACCESSORIES: return MAX_COUNT_ACCESSORIES_ITEMS;
        case LIST_TD_ID_BREAK: return MAX_PLAYER_BREAK;
        case LIST_TD_ID_FAMILY_BUY_VEHICLE: return MAX_MODELS_VEHICLES;
        case LIST_TD_ID_FRACTION_CHANGE_SKIN, LIST_TD_ID_FRACTION_SET_SKIN: return MAX_FRACTIONS_RANGS;
        case LIST_TD_ID_FAMILY_SELECT_SLOT, LIST_TD_ID_FAMILY_CHANGE_SKIN: return MAX_FAMILY_SKINS;
        case LIST_TD_ID_FAMILY_BUY_SKIN:
        {
            new sex_id = p_temp[playerid][p_listitem][1];
            return sex_id == 1 ? sizeof(skinBuyMale)-1 : sizeof(skinBuyMan)-1;
        }
        case LIST_TD_ID_DONATE_REAL_CARS: return MAX_VEH_MODELS_REPLACE;
        case LIST_TD_ID_DONATE_VEHICLE: return MAX_COUNT_DONATE_VEHICLE;
        case LIST_TD_ID_DONATE_SKIN: return MAX_COUNT_DONATE_SKIN;
        case LIST_TD_ID_DONATE_REAL_SKIN: return MAX_COUNT_DONATE_REAL_SKIN;
        case LIST_TD_ID_DONATE_ACCESSORIES: return MAX_COUNT_DONATE_ACCESSORIES;
        case LIST_TD_ID_DONATE_VEHICLE_TUNE: return MAX_COUNT_DONATE_VEHICLE_TUNE;
        case LIST_TD_ID_DONATE_TENT: return MAX_COUNT_DONATE_TENT;
        case LIST_TD_ID_HOT_DEALS_OVER_SIZED: return GetMaxCountDonateHotDeals(HOT_DEALS_TYPE_OVER_SIZED);
        case LIST_TD_ID_VEHICLE_TUNE: return MAX_COUNT_VEHICLE_TUNE;
        case LIST_TD_ID_FAMILY_TRANSFER_SKIN: return GetCountPlayerSkins(playerid);
    }
    return -1;
}

GetSizeofMaxInfo()
{
    for(new i = sizeof(DonateInfo)-1; i != -1; i--)
    {
        if(DonateInfo[i][dType] == TYPE_DONATE_VEHICLE) 
            MAX_COUNT_DONATE_VEHICLE++;
        if(DonateInfo[i][dType] == TYPE_DONATE_SKIN) 
            MAX_COUNT_DONATE_SKIN++;
        if(DonateInfo[i][dType] == TYPE_DONATE_REAL_SKIN) 
            MAX_COUNT_DONATE_REAL_SKIN++;
        if(DonateInfo[i][dType] == TYPE_DONATE_ACCESSORIES) 
            MAX_COUNT_DONATE_ACCESSORIES++;
        if(DonateInfo[i][dType] == TYPE_DONATE_VEHICLE_TUNE) 
            MAX_COUNT_DONATE_VEHICLE_TUNE++;
        if(DonateInfo[i][dType] == TYPE_DONATE_TENT) 
            MAX_COUNT_DONATE_TENT++;
    }

    for(new i = MAX_ITEMS-1; i != -1; i--)
    {
        if(ItemsInfo[i][iType] == TYPE_ITEMS_VEHICLE_TUNE && ItemsInfo[i][iPrice] != 0)
            MAX_COUNT_VEHICLE_TUNE++;
    }

}

GetMaxCountDonateHotDeals(type = -1)
{
    if(type == HOT_DEALS_TYPE_OVER_SIZED) return MAX_COUNT_HOT_DEALS_OVER_SIZED;
    if(type == HOT_DEALS_TYPE_SMALL_SIZED) return MAX_COUNT_HOT_DEALS_SMALL_SIZED;
    return MAX_COUNT_HOT_DEALS_OVER_SIZED+MAX_COUNT_HOT_DEALS_SMALL_SIZED;
}

GetCountPlayerSkins(playerid)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot >= max_slot) return 0;
    new count, itemID;
    for(new i = max_slot; i != min_slot; i--)
    {
        if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID) continue;
        itemID = InventoryPlayer[playerid][i][inv_item_id];
        if(ItemsInfo[itemID][iType] != TYPE_ITEMS_SKINS) continue;
        count++;
    }
    return count;
}