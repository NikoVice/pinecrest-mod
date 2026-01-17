enum
{
    TYPE_MARKET_SERVER,
    TYPE_MARKET_PLAYER
}

#define MAX_MARKET_PLAYER_USE 5

enum M_INFO
{
    mType,
    mOwnerID,
    Float:mPos[3],
    mPickup,
    Text3D:mText,
    mArea,
    mPlayerUse[MAX_MARKET_PLAYER_USE]
}

new MarketInfo[][M_INFO] = {
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1139.9873,-1440.3058,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 0
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1139.9860,-1446.2810,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 1
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1139.9857,-1452.3000,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 2
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1139.9871,-1458.2274,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 3
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1139.9868,-1464.3156,15.7761}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 4
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1132.1720,-1464.2854,15.7768}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 5
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1132.1710,-1458.2626,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 6
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1132.1709,-1452.3193,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 7
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1132.1710,-1446.3149,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 8
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1132.1708,-1440.2583,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 9
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1125.7092,-1440.2765,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 10
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1125.7094,-1446.2963,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 11
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1125.7091,-1452.3175,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 12
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1125.7094,-1458.3140,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 13
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1125.7090,-1464.2860,15.7900}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 14
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1116.9524,-1464.2982,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 15
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1116.9524,-1458.2664,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 16
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1116.9508,-1452.2941,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 17
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1116.9519,-1446.2258,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 18
    {TYPE_MARKET_SERVER, INVALID_PLAYER_ID, {1116.9509,-1440.2780,15.7969}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 19
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 20
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 21
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 22
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 23
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 24
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 25
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 26
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 27
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}}, // 28
    {TYPE_MARKET_PLAYER, INVALID_PLAYER_ID, {0.0,0.0,0.0}, -1, INVALID_3DTEXT_ID, -1, {INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID, INVALID_PLAYER_ID}} // 29
};

CreateMarket(playerid, type, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0)
{
    new string[144];
    switch(type)
    {
        case TYPE_MARKET_SERVER:
        {
            for(new i = 0; i < sizeof(MarketInfo); i++)
            {
                if(MarketInfo[i][mType] != TYPE_MARKET_SERVER) continue;
                MarketInfo[i][mPickup] = CreateDynamicPickup(1239, 23, MarketInfo[i][mPos][0], MarketInfo[i][mPos][1], MarketInfo[i][mPos][2]);
                UpdatePickupInfo(MarketInfo[i][mPickup], TYPE_MARKET, PICKUP_SUBTYPE_INVALID_ID, i);
                format(string, sizeof(string), "[Палатка #%d]\n\nДанная палатка свободна", i + 1);
                MarketInfo[i][mText] = CreateDynamic3DTextLabel(string, COLOR_MAIN, MarketInfo[i][mPos][0], MarketInfo[i][mPos][1], MarketInfo[i][mPos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
                MarketInfo[i][mArea] = CreateDynamicSphere(MarketInfo[i][mPos][0], MarketInfo[i][mPos][1], MarketInfo[i][mPos][2], 3.0, -1, -1, -1);
                UpdateAreaInfo(MarketInfo[i][mArea], TYPE_MARKET, AREA_SUBTYPE_MARKET, i);
            }
        }
        case TYPE_MARKET_PLAYER:
        {
            new i = GetFreeMarket();
            MarketInfo[i][mPos][0] = x;
            MarketInfo[i][mPos][1] = y;
            MarketInfo[i][mPos][2] = z;
            MarketInfo[i][mPickup] = CreateDynamicPickup(1239, 23, MarketInfo[i][mPos][0], MarketInfo[i][mPos][1], MarketInfo[i][mPos][2]);
            UpdatePickupInfo(MarketInfo[i][mPickup], TYPE_MARKET, PICKUP_SUBTYPE_INVALID_ID, i);
            format(string, sizeof(string), "[Переносной ларек #%d]\n\nАрендатор: "W"%s", i - 19, get_name(playerid));
            MarketInfo[i][mText] = CreateDynamic3DTextLabel(string, COLOR_MAIN, MarketInfo[i][mPos][0], MarketInfo[i][mPos][1], MarketInfo[i][mPos][2], 3.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
            MarketInfo[i][mArea] = CreateDynamicSphere(MarketInfo[i][mPos][0], MarketInfo[i][mPos][1], MarketInfo[i][mPos][2], 5.0, -1, -1, -1);
            UpdateAreaInfo(MarketInfo[i][mArea], TYPE_MARKET, AREA_SUBTYPE_MARKET, i);
            p_temp[playerid][market_buy_idx] = i;
            p_temp[playerid][market_arend] = i;
            MarketInfo[i][mOwnerID] = playerid;
            SendAccess(playerid, "Вы установили переносной ларек.");
            SendInfo(playerid, "Редактировать товар: /market");
        }
    }
    return 1;
}

DestroyMarket(idx)
{
    if(MarketInfo[idx][mType] == TYPE_MARKET_SERVER) return 1;
    MarketInfo[idx][mPos][0] = 0.0;
    MarketInfo[idx][mPos][1] = 0.0;
    MarketInfo[idx][mPos][2] = 0.0;
    if(MarketInfo[idx][mPickup] != -1) DestroyDynamicPickup(MarketInfo[idx][mPickup]);
    MarketInfo[idx][mPickup] = -1;
    if(MarketInfo[idx][mText] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(MarketInfo[idx][mText]);
    MarketInfo[idx][mText] = INVALID_3DTEXT_ID;
    if(MarketInfo[idx][mArea] != -1) DestroyDynamicArea(MarketInfo[idx][mArea]);
    MarketInfo[idx][mArea] = -1;
    return 1;
}

GetFreeMarket()
{
    new idx = -1;
    for(new i = 20; i < sizeof(MarketInfo); i++)
    {
        if(MarketInfo[i][mType] == TYPE_MARKET_SERVER) continue;
        if(MarketInfo[i][mOwnerID] == INVALID_PLAYER_ID) return i;
    }
    return idx;
}

UpdateMarket(idx)
{
    new string[144];
    if(MarketInfo[idx][mOwnerID] == INVALID_PLAYER_ID) format(string, sizeof(string), "[Палатка #%d]\n\nДанная палатка свободна", idx + 1);
    else format(string, sizeof(string), "[Палатка #%d]\n\nАрендатор: "W"%s", idx + 1, get_name(MarketInfo[idx][mOwnerID]));
    UpdateDynamic3DTextLabelText(MarketInfo[idx][mText], COLOR_MAIN, string);
    return 1;
}

ShowFreeMarket(playerid, idx)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
    Палатка "I"#%d"W"\n\n\
    Вы хотите начать продавать товар?", idx + 1);
    ShowPlayerDialog(playerid, D_MARKET_START, DIALOG_STYLE_MSGBOX, ""I"Палатка", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
// Функционал владельца:
ShowPlayerItemsSellMarket(playerid)
{
    ShowPlayerList(playerid, LIST_ID_MARKET_SELL_ITEMS);
    return 1;
}

ShowPlayerItemsBuyMarket(playerid, type, page = 0)
{
    if(!page) ShowPlayerList(playerid, type);
    else
    {
        p_temp[playerid][list_page] = page;
        p_temp[playerid][list_type] = type;
        UpdatePlayerList(playerid);
    }
    return 1;
}

ShowPlayerControlMarket(playerid)
{
    return ShowPlayerDialog(playerid, D_MARKET_CONTROL, DIALOG_STYLE_LIST, ""I"Управление палаткой", ""I"[1]"W" Продать товар\n"I"[2]"W" Купить товар\n"I"[3]"W" Закончить арендовать палатку", "Далее", "Отмена");
}
/////////////////////////////////////////////////////////////////
ShowItemsBuyMarket(playerid)
{
    // СПИСОК ПРОДАВАЕМОГО ТОВАРА
    ShowTextDrawForPlayer(playerid, TD_ID_MARKET);
    Interface_Show(playerid, MARKET_BUY);
    return 1;
}

ShowItemsSellMarket(playerid)
{
    // СПИСОК ЗАКУПАЕМОГО ТОВАРА
    ShowTextDrawForPlayer(playerid, TD_ID_MARKET);
    Interface_Show(playerid, MARKET_SELL);
    return 1;
}

MarketItemsSellAdd(playerid, slot_id, count, price)
{
    if(InventoryPlayer[playerid][slot_id][inv_market_sell_price] > 0)
        return SendError(playerid, "Товар уже выставлен на продажу.");

    InventoryPlayer[playerid][slot_id][inv_market_sell_price] = price;
    InventoryPlayer[playerid][slot_id][inv_market_sell_amount] = count;

    ShowPlayerItemsSellMarket(playerid);
    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выставил на рынке товар <Камень> 10 шт. за 100$
    Log(LOG_player, INFO, "%s[%d](%s %s) начал на рынке продажа товара <%s> %d ед. за %d$ | #MARKET",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iName], count, price);
    return 1;
}
MarketItemsSellTake(playerid, slot_id, count)
{
    if(InventoryPlayer[playerid][slot_id][inv_market_sell_price] < 1)
        return SendError(playerid, "Товар не выставлен на продажу.");

    InventoryPlayer[playerid][slot_id][inv_market_sell_amount] -= count;

    if(InventoryPlayer[playerid][slot_id][inv_market_sell_amount] == 0)
        InventoryPlayer[playerid][slot_id][inv_market_sell_price] = 0;

    ShowPlayerItemsSellMarket(playerid);
    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выставил на рынке товар <Камень> 10 шт. за 100$
    Log(LOG_player, INFO, "%s[%d](%s %s) отменил на рынке продажу товара <%s> %d ед.(осталось: %d ед.) | #MARKET",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iName], count, InventoryPlayer[playerid][slot_id][inv_market_sell_amount]);
    return 1;
}

OnPlayerLeaveFromMarket(playerid)
{
    if(p_temp[playerid][market_arend] == -1) return 1;
    new idx = p_temp[playerid][market_arend];
    p_temp[playerid][market_arend] = -1;
    if(MarketInfo[idx][mOwnerID] != playerid) return 1;
    MarketInfo[idx][mOwnerID] = INVALID_PLAYER_ID;

    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if(InventoryPlayer[playerid][i][inv_market_sell_amount] != 0 || InventoryPlayer[playerid][i][inv_market_sell_price] != 0)
        {
            InventoryPlayer[playerid][i][inv_market_sell_amount] =
            InventoryPlayer[playerid][i][inv_market_sell_price] = 0;
        }

        if(InventoryPlayer[playerid][i][inv_market_buy_amount] != 0 || InventoryPlayer[playerid][i][inv_market_buy_price] != 0)
        {
            if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID)
                InventoryPlayer[playerid][i][inv_item_id] = 0;
            InventoryPlayer[playerid][i][inv_market_buy_amount] =
            InventoryPlayer[playerid][i][inv_market_buy_price] = 0;
        }
    }

    new targetid;
    for(new i = MAX_MARKET_PLAYER_USE-1; i != -1; i--)
    {
        targetid = MarketInfo[idx][mPlayerUse][i];
        if(targetid == INVALID_PLAYER_ID) continue;
        MarketInfo[idx][mPlayerUse][i] = INVALID_PLAYER_ID;
        if(p_temp[targetid][market_buy_idx] == idx)
        {
            if(p_temp[targetid][TextDrawMarket])
                HideTextDrawForPlayer(targetid, TD_ID_MARKET);
            ShowPlayerDialog(targetid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Палатка", ""W"Арендатор покинул палатку.", "Закрыть", "");
            p_temp[targetid][market_buy_idx] = -1;
        }
    }

    SendAccess(playerid, "Вы %s.", MarketInfo[idx][mType] == TYPE_MARKET_SERVER ? "закончили арендовывать палатку" : "забрали переносной ларек");

    if(MarketInfo[idx][mType] == TYPE_MARKET_SERVER) UpdateMarket(idx);
    else
    {
        ClearTent(playerid, 1);
        DestroyMarket(idx);
    }
    return 1;
}

CMD:market(playerid, params[])
{
    if(p_temp[playerid][market_arend] == -1) return SendError(playerid, "У Вас нет арендованной палатки.");
    ShowPlayerControlMarket(playerid);
    return 1;
}
//////////////////////////////////////
CheckSellMarketItemsAdd(playerid, item_id, max_iterate)
{
    for(new i; i < max_iterate; i++)
    {
        if(InventoryPlayer[playerid][i][inv_item_id] == item_id) return 0;
    }
    return 1;
}

ShowDialogMarketItemsSellAdd(playerid, slot_id)
{
    STRING_GLOBAL[0] = EOS;
    new itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите кол-во \"%s\" и стоимость 1 ед. через запятую: \n\n"W"Пример: "I"2,5000 "W"(2 - штуки, 5000$ цена)", ItemsInfo[itemID][iName]);
    }
    else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите стоимость \"%s\" [%.1f] (%s/%s), Premium: %s:",
            ItemsInfo[itemID][iName],
            InventoryPlayer[playerid][slot_id][inv_acc_wear],
            AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acName],
            AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acName],
            InventoryPlayer[playerid][slot_id][inv_acc_premium] == 1 ? "Есть" : "Нет");
    }
    else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_SKINS)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите стоимость \"%s\" [%.1f], Premium: %s:",
        ItemsInfo[itemID][iName],
        InventoryPlayer[playerid][slot_id][inv_skin_wear],
        InventoryPlayer[playerid][slot_id][inv_skin_premium] == 1 ? "Есть" : "Нет");
    }
    else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите стоимость \"%s\":", ItemsInfo[itemID][iName]);
    }
    else return SendError(playerid, "Другие виды предметов пока не разработаны.");
    ShowPlayerDialog(playerid, D_MARKET_SELL_ITEM_ADD, DIALOG_STYLE_INPUT, ""I"Настройки товара", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

ShowDialogMarketItemsSellTake(playerid, slot_id)
{
    new dialog_style = -1, itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    STRING_GLOBAL[0] = EOS;
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите кол-во \"%s\" которое хотите забрать с продажи:",
        ItemsInfo[itemID][iName]);
        dialog_style = DIALOG_STYLE_INPUT;
    }
    else
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы действительно хотите \"%s\" забрать с продажи:",
            ItemsInfo[itemID][iName]);
        dialog_style = DIALOG_STYLE_MSGBOX;
    }
    ShowPlayerDialog(playerid, D_MARKET_SELL_ITEM_TAKE, dialog_style, ""I"Настройки товара", STRING_GLOBAL, "Далее", "Отмена");
}

////// Закупка:
GetIDMarketBuyItem(playerid, item_id)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot >= max_slot) return -1;
    for(new i = max_slot; i != min_slot; i--)
    {
        if( InventoryPlayer[playerid][i][inv_item_id] == item_id &&
            InventoryPlayer[playerid][i][inv_market_buy_amount] > 0 &&
            InventoryPlayer[playerid][i][inv_market_buy_price] > 0)
        {
            return i;
        }
    }
    return -1;
}

ShowDialogMarketItemsBuyAdd(playerid, item_id)
{
    STRING_GLOBAL[0] = EOS;
    if(ItemsInfo[item_id][iType] == TYPE_ITEMS_INVENTORY)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите кол-во \"%s\" и стоимость 1 ед. через запятую: \n\n"W"Пример: "I"2,5000 "W"(2 - штуки, 5000$ цена)", ItemsInfo[item_id][iName]);
    }
    else if(ItemsInfo[item_id][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите параметры для "I"\"%s\""W" через запятые:\n\n0 - Любой цвет\n", ItemsInfo[item_id][iName]);

        for(new i; i < sizeof(AccessoriesColorInfo); i++)
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s %d - {%06x}%s"W"\n", STRING_GLOBAL, i+1, i == 0 ? 0xFFFFFF : AccessoriesColorInfo[i][acColorRBG] & 0xFFFFFF, AccessoriesColorInfo[i][acName]);

        strcat(STRING_GLOBAL, "\n"W"Пример: "I"0,0,80,5000,0 "W"('0' - первый цвет, '0' - второй цвет, '80' - мин. процент износа, '5000' - цена, '0' - без премиума или '1' с премиумом)");
    }
    else if(ItemsInfo[item_id][iType] == TYPE_ITEMS_SKINS)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите параметры для \"%s\" через запятые:\n\nПример: "I"80,5000,0"W" ('80' - мин. процент износа, '5000' - цена, '0' - без премиума или '1' с премиумом)", ItemsInfo[item_id][iName]);
    }
    else if(ItemsInfo[item_id][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите стоимость для \"%s\":", ItemsInfo[item_id][iName]);
    }
    else return SendError(playerid, "Другие виды предметов пока не разработаны.");
    ShowPlayerDialog(playerid, D_MARKET_BUY_ITEM_ADD, DIALOG_STYLE_INPUT, ""I"Настройки товара", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

ShowDialogMarketItemsBuyTake(playerid, slot_id)
{
    new dialog_style = -1, itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
    STRING_GLOBAL[0] = EOS;
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите кол-во \"%s\" которое хотите забрать с закупки?", ItemsInfo[itemID][iName]);
        dialog_style = DIALOG_STYLE_INPUT;
    }
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES || ItemsInfo[itemID][iType] == TYPE_ITEMS_SKINS || ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы действительно хотите \"%s\" забрать с закупки?", ItemsInfo[itemID][iName]);
        dialog_style = DIALOG_STYLE_MSGBOX;
    }
    ShowPlayerDialog(playerid, D_MARKET_BUY_ITEM_TAKE, dialog_style, ""I"Настройки товара", STRING_GLOBAL, "Далее", "Отмена");
}

MarketItemsBuyAdd(playerid, item_id, count, price, wear, color1, color2, premium)
{
    new free_slot = -1;
    if(ItemsInfo[item_id][iType] == TYPE_ITEMS_INVENTORY)
    {
        for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
        {
            if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID && InventoryPlayer[playerid][i][inv_item_id] == item_id)
            {
                free_slot = i;
                break;
            }
        }
    }
    if(free_slot == -1) free_slot = GetFreeSlotInventory(playerid, EQUIPMENT_INVENTORY_PLAYER);
    if(free_slot == -1) return SendError(playerid, "В инвентаре нет свободного места.");

    if(InventoryPlayer[playerid][free_slot][inv_market_buy_price] > 0)
        return SendError(playerid, "Товар уже выставлен на закупку.");

    InventoryPlayer[playerid][free_slot][inv_item_id] = item_id;
    InventoryPlayer[playerid][free_slot][inv_market_buy_price] = price;
    InventoryPlayer[playerid][free_slot][inv_market_buy_amount] = count;

    if(ItemsInfo[item_id][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        InventoryPlayer[playerid][free_slot][inv_acc_wear] = wear;
        InventoryPlayer[playerid][free_slot][inv_acc_premium] = premium;
        InventoryPlayer[playerid][free_slot][inv_acc_mt][0] = color1;
        InventoryPlayer[playerid][free_slot][inv_acc_mt][1] = color2;
        InventoryPlayer[playerid][free_slot][inv_status_use] = 0;
        InventoryPlayer[playerid][free_slot][inv_acc_slot] = -1;
    }
    if(ItemsInfo[item_id][iType] == TYPE_ITEMS_SKINS)
    {
        InventoryPlayer[playerid][free_slot][inv_skin_wear] = wear;
        InventoryPlayer[playerid][free_slot][inv_skin_premium] = premium;
    }

    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выставил на рынке товар <Камень> 10 шт. за 100$
    Log(LOG_player, INFO, "%s[%d](%s %s) начал на рынке закупку товара <%s> %d ед. за %d$ | #MARKET",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        ItemsInfo[InventoryPlayer[playerid][free_slot][inv_item_id]][iName], count, price);

    ShowPlayerItemsBuyMarket(playerid,  p_temp[playerid][list_type], p_temp[playerid][list_page]);
    return 1;
}
MarketItemsBuyTake(playerid, slot_id, count)
{
    if(!InventoryPlayer[playerid][slot_id][inv_market_buy_price])
        return SendError(playerid, "Товар не выставлен на продажу.");

    InventoryPlayer[playerid][slot_id][inv_market_buy_amount] -= count;

    if(!InventoryPlayer[playerid][slot_id][inv_market_buy_amount])
    {
        InventoryPlayer[playerid][slot_id][inv_market_buy_price] = 0;
        if(InventoryPlayer[playerid][slot_id][inv_mysql_id] == INVALID_MYSQL_ID)
            Equipment_ClearSlot(playerid, slot_id);
    }

    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выставил на рынке товар <Камень> 10 шт. за 100$
    Log(LOG_player, INFO, "%s[%d](%s %s) отменил на рынке закупку товара <%s> %d ед.(осталось: %d ед.) | #MARKET",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iName], count, InventoryPlayer[playerid][slot_id][inv_market_buy_amount]);

    ShowPlayerItemsBuyMarket(playerid,  p_temp[playerid][list_type], p_temp[playerid][list_page]);
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Интерфейс покупателя:
Equipment_MarketLeft(playerid, type_id)
{
    new idx = p_temp[playerid][market_buy_idx];
    if(idx == -1)
    {
        ClearPlayerMarketUse(playerid);
        return SendError(playerid, "Палатка не определена. Подойдите заново к ней.");
    }
    new targetid = MarketInfo[idx][mOwnerID];
    if(targetid == INVALID_PLAYER_ID)
    {
        ClearPlayerMarketUse(playerid);
        return SendError(playerid, "Данная палатка не имеет арендатора.");
    }

    for(new i = 19; i != -1; i--)
    {
        Equipment_TDClearSlotLeft(playerid, i);
        PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][5+i]);
    }

    new itemId, pageID = p_temp[playerid][inv_list_page][1]-1, count, list_count,
        max_slot, min_slot;
    GetSlotInfoInventory(targetid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot >= max_slot) return 0;
    min_slot++, max_slot++;
    for(new i = min_slot; i < max_slot; i++)
    {
        if((type_id == MARKET_BUY &&
            (InventoryPlayer[targetid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
            !InventoryPlayer[targetid][i][inv_market_sell_amount])) ||
            (type_id == MARKET_SELL && !InventoryPlayer[targetid][i][inv_market_buy_amount])) continue;
        count++;
        if(count < pageID*20+1) continue;
        if(count > pageID*20+20) break;

        itemId = InventoryPlayer[targetid][i][inv_item_id];
        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+list_count], ItemsInfo[itemId][iModel] == 74 ? 0 : ItemsInfo[itemId][iModel]);
        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+list_count], ItemsInfo[itemId][iObjectPos][0], ItemsInfo[itemId][iObjectPos][1], ItemsInfo[itemId][iObjectPos][2], ItemsInfo[itemId][iObjectPos][3]);

        if(ItemsInfo[itemId][iType] == TYPE_ITEMS_INVENTORY)
            f(STRING_GLOBAL, "%d$", type_id == MARKET_BUY ? InventoryPlayer[targetid][i][inv_market_sell_price] : InventoryPlayer[targetid][i][inv_market_buy_price]);
        else if(ItemsInfo[itemId][iType] == TYPE_ITEMS_ACCESSORIES || ItemsInfo[itemId][iType] == TYPE_ITEMS_SKINS || ItemsInfo[itemId][iType] == TYPE_ITEMS_VEHICLE_TUNE)
            f(STRING_GLOBAL, "ID: %d", itemId);
        PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+list_count], STRING_GLOBAL);

        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+list_count], true);
        PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][5+list_count]);

        p_temp[playerid][p_listitem][list_count] = i;
        list_count++;
    }
    return 1;
}

ShowDialogMarketItemsSell(playerid, slot_id)
{
    new idx = p_temp[playerid][market_buy_idx];
    if(idx == -1)
    {
        ClearPlayerMarketUse(playerid);
        return SendError(playerid, "Палатка не определена. Подойдите к ней заново.");
    }
    new targetid = MarketInfo[idx][mOwnerID];
    if(targetid == INVALID_PLAYER_ID)
    {
        ClearPlayerMarketUse(playerid);
        return SendError(playerid, "Данная палатка не имеет арендатора.");
    }
    STRING_GLOBAL[0] = EOS;

    new item_id = InventoryPlayer[targetid][slot_id][inv_item_id],
        item_type = ItemsInfo[item_id][iType];
    p_temp[playerid][market_buy_items][0] = item_id;
    p_temp[playerid][market_buy_items][1] = InventoryPlayer[targetid][slot_id][inv_market_sell_price];
    if(InventoryPlayer[targetid][slot_id][inv_market_sell_amount] < 1 ||
        InventoryPlayer[targetid][slot_id][inv_market_sell_price] < 1)
        return SendError(playerid, "Предмет не обнаружено."), ShowItemsBuyMarket(playerid), p_temp[playerid][market_buy_items][0] = -1;
    if(item_type == TYPE_ITEMS_NONE) return SendError(playerid, "Предмет не обнаружено."), ShowItemsBuyMarket(playerid), p_temp[playerid][market_buy_items][0] = -1;
    else if(item_type == TYPE_ITEMS_INVENTORY)
    {
        f(STRING_GLOBAL,
            ""W"Название: "I"\"%s\""W"\n\
            Кол-во: "I"%d"W"\n\
            Стоимость "I"1 "W"ед.: "I"%d$"W"\n\n\
            Введите кол-во ед., которое хотите приобрести:",
            ItemsInfo[item_id][iName],
            InventoryPlayer[targetid][slot_id][inv_market_sell_amount],
            InventoryPlayer[targetid][slot_id][inv_market_sell_price]);
        ShowPlayerDialog(playerid, D_MARKET_BUY_ITEM, DIALOG_STYLE_INPUT, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
    }
    else if(item_type == TYPE_ITEMS_ACCESSORIES)
    {
        f(STRING_GLOBAL,
            ""W"Название: "I"\"%s\"\n\
            Состояние: "I"%.1f"W"\n\
            Цвет #1: {%06x}%s"W"\n\
            Цвет #2: {%06x}%s"W"\n\
            Премиум: "I"%s"W"\n\
            Стоимость: "I"%d$",
            ItemsInfo[item_id][iName],
            InventoryPlayer[targetid][slot_id][inv_acc_wear],
            InventoryPlayer[targetid][slot_id][inv_acc_mt][0] == 0 ? 0xFFFFFF : AccessoriesColorInfo[InventoryPlayer[targetid][slot_id][inv_acc_mt][0]][acColorRBG] & 0xFFFFFF,
            AccessoriesColorInfo[InventoryPlayer[targetid][slot_id][inv_acc_mt][0]][acName],
            InventoryPlayer[targetid][slot_id][inv_acc_mt][1] == 0 ? 0xFFFFFF : AccessoriesColorInfo[InventoryPlayer[targetid][slot_id][inv_acc_mt][1]][acColorRBG] & 0xFFFFFF,
            AccessoriesColorInfo[InventoryPlayer[targetid][slot_id][inv_acc_mt][1]][acName],
            InventoryPlayer[targetid][slot_id][inv_acc_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"",
            InventoryPlayer[targetid][slot_id][inv_market_sell_price]);
        ShowPlayerDialog(playerid, D_MARKET_BUY_ITEM, DIALOG_STYLE_MSGBOX, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
    }
    else if(item_type == TYPE_ITEMS_SKINS)
    {
        f(STRING_GLOBAL,
            ""W"Название: "I"\"%s\""W"\n\
            Состояние: "I"%.1f"W"\n\
            Премиум: "I"%s"W"\n\
            Стоимость: "I"%d$",
            ItemsInfo[item_id][iName],
            InventoryPlayer[targetid][slot_id][inv_skin_wear],
            InventoryPlayer[targetid][slot_id][inv_skin_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"",
            InventoryPlayer[targetid][slot_id][inv_market_sell_price]);
        ShowPlayerDialog(playerid, D_MARKET_BUY_ITEM, DIALOG_STYLE_MSGBOX, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
    }
    else if(item_type == TYPE_ITEMS_VEHICLE_TUNE)
    {
        f(STRING_GLOBAL,
            ""W"Название: "I"\"%s\""W"\n\
            Стоимость: "I"%d$",
            ItemsInfo[item_id][iName],
            InventoryPlayer[targetid][slot_id][inv_market_sell_price]);
        ShowPlayerDialog(playerid, D_MARKET_BUY_ITEM, DIALOG_STYLE_MSGBOX, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
    }
    return 1;
}

ShowDialogMarketItemsBuy(playerid, slot_id)
{
    new idx = p_temp[playerid][market_buy_idx];
    if(idx == -1)
    {
        ClearPlayerMarketUse(playerid);
        return SendError(playerid, "Палатка не определена. Подойдите к ней заново.");
    }
    new targetid = MarketInfo[idx][mOwnerID];
    if(targetid == INVALID_PLAYER_ID)
    {
        ClearPlayerMarketUse(playerid);
        return SendError(playerid, "Данная палатка не имеет арендатора.");
    }
    STRING_GLOBAL[0] = EOS;
    new item_id = InventoryPlayer[targetid][slot_id][inv_item_id],
        item_type = ItemsInfo[item_id][iType];
    p_temp[playerid][market_buy_items][0] = item_id;
    p_temp[playerid][market_buy_items][1] = InventoryPlayer[targetid][slot_id][inv_market_buy_price];

    if(InventoryPlayer[targetid][slot_id][inv_market_buy_amount] < 1 ||
        InventoryPlayer[targetid][slot_id][inv_market_buy_price] < 1)
        return SendError(playerid, "Предмет не обнаружено."), ShowItemsBuyMarket(playerid), p_temp[playerid][market_buy_items][0] = -1;
    if(item_type == TYPE_ITEMS_NONE) return SendError(playerid, "Предмет не обнаружено."), ShowItemsSellMarket(playerid), p_temp[playerid][market_buy_items][0] = -1;
    else if(item_type == TYPE_ITEMS_INVENTORY)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Название: "I"%s"W"\n\
            Кол-во: "I"%d"W"\n\
            Стоимость "I"1 "W"ед.: "I"%d$"W"\n\n\
            Введите кол-во ед., которое хотите продать:",
            ItemsInfo[item_id][iName],
            InventoryPlayer[targetid][slot_id][inv_market_buy_amount],
            InventoryPlayer[targetid][slot_id][inv_market_buy_price]);
        ShowPlayerDialog(playerid, D_MARKET_SELL_ITEM, DIALOG_STYLE_INPUT, ""I"Продать товар", STRING_GLOBAL, "Далее", "Отмена");
    }
    else if(item_type == TYPE_ITEMS_ACCESSORIES)
    {
        new Float:wear = InventoryPlayer[targetid][slot_id][inv_acc_wear],
            mc1 = InventoryPlayer[targetid][slot_id][inv_acc_mt][0],
            mc2 = InventoryPlayer[targetid][slot_id][inv_acc_mt][1];

        new color1[16] = "Любой", color2[16] = "Любой";
        if(mc1 != 0) f(color1, "%s", AccessoriesColorInfo[mc1-1][acName]);
        if(mc2 != 0) f(color2, "%s", AccessoriesColorInfo[mc2-1][acName]);
        f(STRING_GLOBAL, ""W"Название: "I"\"%s\""W"\n\
            Состояние: "I"%.1f"W"\n\
            Цвет #1: {%06x}%s"W"\n\
            Цвет #2: {%06x}%s"W"\n\
            Премиум: "I"%s"W"\n\
            Стоимость: "I"%d$",
            ItemsInfo[item_id][iName],
            wear,
            mc1 == 0 ? 0xFFFFFF : AccessoriesColorInfo[mc1-1][acColorRBG] & 0xFFFFFF,
            color1,
            mc2 == 0 ? 0xFFFFFF : AccessoriesColorInfo[mc2-1][acColorRBG] & 0xFFFFFF,
            color2,
            InventoryPlayer[targetid][slot_id][inv_acc_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"",
            InventoryPlayer[targetid][slot_id][inv_market_buy_price]);
        ShowPlayerDialog(playerid, D_MARKET_SELL_ITEM, DIALOG_STYLE_MSGBOX, ""I"Продать товар", STRING_GLOBAL, "Далее", "Отмена");
    }
    else if(item_type == TYPE_ITEMS_SKINS)
    {
        new Float:wear = InventoryPlayer[targetid][slot_id][inv_skin_wear];
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Название: "I"%s"W"\n\
            Состояние: "I"%.1f"W"\n\
            Премиум: "I"%s"W"\n\
            Стоимость: "I"%d$",
            ItemsInfo[item_id][iName],
            wear,
            InventoryPlayer[targetid][slot_id][inv_skin_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"",
            InventoryPlayer[targetid][slot_id][inv_market_buy_price]);
        ShowPlayerDialog(playerid, D_MARKET_SELL_ITEM, DIALOG_STYLE_MSGBOX, ""I"Продать товар", STRING_GLOBAL, "Далее", "Отмена");
    }
    else if(item_type == TYPE_ITEMS_VEHICLE_TUNE)
    {
        f(STRING_GLOBAL,
            ""W"Название: "I"\"%s\""W"\n\
            Стоимость: "I"%d$",
            ItemsInfo[item_id][iName],
            InventoryPlayer[targetid][slot_id][inv_market_sell_price]);
        ShowPlayerDialog(playerid, D_MARKET_SELL_ITEM, DIALOG_STYLE_MSGBOX, ""I"Продать товар", STRING_GLOBAL, "Далее", "Отмена");
    }
    return 1;
}

MarketSearchSlotAccessories(playerid, item_id, Float:wear, mc1, mc2, premium)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot >= max_slot) return -1;
    for(new i = max_slot; i != min_slot; i--)
    {
        if( InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            InventoryPlayer[playerid][i][inv_item_id] == item_id &&
            floatcmp(InventoryPlayer[playerid][i][inv_acc_wear], wear) != -1 &&
            (mc1 == 0 || InventoryPlayer[playerid][i][inv_acc_mt][0]+1 == mc1) &&
            (mc2 == 0 || InventoryPlayer[playerid][i][inv_acc_mt][1]+1 == mc2) &&
            InventoryPlayer[playerid][i][inv_acc_premium] == premium)
                return i;
    }
    return -1;
}

MarketSearchSlotSkins(playerid, item_id, Float:wear, premium)
{
    new max_slot, min_slot;
    GetSlotInfoInventory(playerid, EQUIPMENT_INVENTORY_PLAYER, max_slot, min_slot);
    if(min_slot >= max_slot) return -1;
    for(new i = max_slot; i != min_slot; i--)
    {
        if( InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
            InventoryPlayer[playerid][i][inv_item_id] == item_id &&
            floatcmp(InventoryPlayer[playerid][i][inv_skin_wear], wear) != -1 &&
            InventoryPlayer[playerid][i][inv_skin_premium] == premium)
                return i;
    }
    return -1;
}

CMD:returnmarket(playerid, params[])
{
    if(p_temp[playerid][market_arend] != -1) return SendError(playerid, "Вы арендуете палатку, откажитесь от аренды и повторите операцию.");
    if(GetPVarInt(playerid, "LimitReturnMarket") > timestamp) return SendError(playerid, "Вы не можете так часто использовать команду.");
    SetPVarInt(playerid, "LimitReturnMarket", timestamp+10);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `market` WHERE `m_mysql_id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "ReturnPlayerMarketItemsMysql", "i", playerid);
    return 1;
}

ClearPlayerMarketUse(playerid)
{
    new id = p_temp[playerid][market_buy_idx];
    if(id != -1)
    {
        for(new i = MAX_MARKET_PLAYER_USE-1; i != -1; i--)
        {
            if(MarketInfo[id][mPlayerUse][i] == playerid)
            {
                MarketInfo[id][mPlayerUse][i] = INVALID_PLAYER_ID;
                break;
            }
        }
        p_temp[playerid][market_buy_idx] = -1;
    }
    if(p_temp[playerid][TextDrawMarket])
        HideTextDrawForPlayer(playerid, TD_ID_MARKET);
    return 1;
}
