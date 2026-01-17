
///
#define MAX_EXCHANGE 10
#define INVALID_EXCHANGE -1
#define TRADE_VIRTUALWORLD 109950
enum
{
    BET_MONEY = 1,
    BET_CAR,
    BET_HOUSE,
    BET_BIZ,
    BET_INVENTORY,
    BET_ACCESSORIES,
    BET_VEHICLE_TUNE,
    BET_SKIN,
    BET_FAMILY,
    BET_COSTUME,
};

enum e_exchange
{
    xType,
    xItemID,
    xValue,

    // Cars:
    xNumber[16],
    xTwinTurbo,
    // Accessories & Skins:
    Float:xWear,
    xMaterialColor[2],
    xPremium
};
new gExchange[MAX_PLAYERS][MAX_EXCHANGE][e_exchange];

CMD:ttd(playerid, params[])
{
    if(SRV_ID) return 1;
    StartExchange(playerid, playerid);
    ShowTextDrawForPlayer(playerid, TD_ID_TRADE);
    return 1;
}

StartExchange(const firstid, const secondid)
{
    if(p_info[firstid][exchangePartner] != INVALID_PLAYER_ID || p_info[secondid][exchangePartner] != INVALID_PLAYER_ID)
        return 0;
    /*
    if(p_temp[playerid][TextDrawEquipment])
    {
        HideTextDrawForPlayer(playerid, TD_ID_INVENTORY);
    }
    */

    for(new i = MAX_EXCHANGE-1; i != -1; i--)
    {
        gExchange[firstid][i][xType] =
        gExchange[firstid][i][xItemID] =
        gExchange[firstid][i][xValue] = INVALID_EXCHANGE;

        gExchange[secondid][i][xType] =
        gExchange[secondid][i][xItemID] =
        gExchange[secondid][i][xValue] = INVALID_EXCHANGE;
    }

    DeletePVar(firstid, "EXCHANGE:ready");
    DeletePVar(secondid, "EXCHANGE:ready");
    DeletePVar(firstid, "EXCHANGE:confirmed");
    DeletePVar(secondid, "EXCHANGE:confirmed");

    p_info[firstid][exchangePartner] = secondid;
    p_info[secondid][exchangePartner] = firstid;

    //SetPlayerVirtualWorld(firstid, firstid + TRADE_VIRTUALWORLD);
    //SetPlayerVirtualWorld(secondid, firstid + TRADE_VIRTUALWORLD);

    if(p_info[firstid][exchangeText] != INVALID_3DTEXT_ID)
    {
        p_info[firstid][exchangeText] = INVALID_3DTEXT_ID;
        DestroyDynamic3DTextLabel(p_info[firstid][exchangeText]);
    }
    if(p_info[secondid][exchangeText] != INVALID_3DTEXT_ID)
    {
        p_info[secondid][exchangeText] = INVALID_3DTEXT_ID;
        DestroyDynamic3DTextLabel(p_info[secondid][exchangeText]);
    }

    p_info[firstid][exchangeText] = CreateDynamic3DTextLabel("ОБМЕН ИМУЩЕСТВОМ", 0xCCCCCCFF,
        -2161.2239,640.3857,1052.3817+1.6, 30.0,
        INVALID_PLAYER_ID, INVALID_VEHICLE_ID,
        streamer_TESTLOL, firstid + TRADE_VIRTUALWORLD);

    UpdateExchangeText(firstid);

    SendInfo(firstid, "Добавить/убрать предмет в обмен: /bet");
    //SendInfo(firstid, "Убрать предмет из обмен: /unbet");
    SendInfo(firstid, "Подтвердить обмен: /ready");
    SendInfo(firstid, "Отменить обмен: /stopex");

    SendInfo(secondid, "Добавить/убрать предмет в обмен: /bet");
    //SendInfo(secondid, "Убрать предмет из обмен: /unbet");
    SendInfo(secondid, "Подтвердить обмен: /ready");
    SendInfo(secondid, "Отменить обмен: /stopex");

    SendMes(firstid, COLOR_DARKORANGE, "[ОБНОВЛЕНИЕ]:"W" При продаже дома теперь отображается информация о солнечных панелях, видеокартах и рабочих.");
    SendMes(firstid, COLOR_DARKORANGE, "[ОБНОВЛЕНИЕ]:"W" Для просмотра информации нажмите \"INFO\" на добавленном доме.");
    SendMes(secondid, COLOR_DARKORANGE, "[ОБНОВЛЕНИЕ]:"W" При продаже дома теперь отображается информация о солнечных панелях, видеокартах и рабочих.");
    SendMes(secondid, COLOR_DARKORANGE, "[ОБНОВЛЕНИЕ]:"W" Для просмотра информации нажмите \"INFO\" на добавленном доме.");

    if(p_temp[firstid][TextDrawInventory])
    {
        if(EQUIPMENT_INVENTORY_PLAYER < p_temp[firstid][InterfaceID] < EQUIPMENT_INVENTORY_ALL)
            HideTextDrawForPlayer(firstid, TD_ID_INVENTORY_OTHER);
        if(p_temp[firstid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER)
            HideTextDrawForPlayer(firstid, TD_ID_INVENTORY_PLAYER);
    }

    if(p_temp[secondid][TextDrawInventory])
    {
        if(EQUIPMENT_INVENTORY_PLAYER < p_temp[secondid][InterfaceID] < EQUIPMENT_INVENTORY_ALL)
            HideTextDrawForPlayer(secondid, TD_ID_INVENTORY_OTHER);
        if(p_temp[secondid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER)
            HideTextDrawForPlayer(secondid, TD_ID_INVENTORY_PLAYER);
    }
    return 1;
}

AddExchangeBet(playerid, type, item_id = -1, value = 0, number[] = "", twinturbo = 0, Float:wear = 0.0, mc1 = 0, mc2 = 0, premium = 0)
{
    if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID)
        return 0;
    if(GetPVarInt(playerid, "EXCHANGE:ready"))
        return SendError(playerid, "Вы готовы, изменять вклад нельзя.");

    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        if(gExchange[playerid][i][xType] == BET_MONEY && type == BET_MONEY)
        {
            if(gExchange[playerid][i][xValue]+value > p_info[playerid][bank]) return SendError(playerid, "У Вас не достаточно денег в банке.");
            gExchange[playerid][i][xValue] += value;
            UpdateExchangeText(playerid);
            return SendAccess(playerid, "Вы добавили предмет в обмен.");
        }
        if(gExchange[playerid][i][xType] == BET_INVENTORY && type == BET_INVENTORY && gExchange[playerid][i][xItemID] == item_id)
        {
            if(gExchange[playerid][i][xValue]+value > GetInventoryAmount(playerid, item_id)) return SendError(playerid, "У Вас не достаточно количества данного предмета.");
            gExchange[playerid][i][xValue] += value;
            UpdateExchangeText(playerid);
            return SendAccess(playerid, "Вы добавили предмет в обмен.");
        }

        if(gExchange[playerid][i][xType] == type &&
            gExchange[playerid][i][xItemID] == item_id &&
            gExchange[playerid][i][xValue] == value)
            return SendError(playerid, "Вы уже добавили этот предмет во вклад.");
    }

    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        if(gExchange[playerid][i][xType] != INVALID_EXCHANGE)
            continue;
        gExchange[playerid][i][xType] = type;
        gExchange[playerid][i][xItemID] = item_id;
        gExchange[playerid][i][xValue] = value;

        if(gExchange[playerid][i][xType] == BET_CAR)
        {
            gExchange[playerid][i][xNumber] = EOS;
            format(gExchange[playerid][i][xNumber], 16, number);
            gExchange[playerid][i][xTwinTurbo] = twinturbo;
        }
        if(gExchange[playerid][i][xType] == BET_ACCESSORIES)
        {
            gExchange[playerid][i][xWear] = wear;
            gExchange[playerid][i][xMaterialColor][0] = mc1;
            gExchange[playerid][i][xMaterialColor][1] = mc2;
            gExchange[playerid][i][xPremium] = premium;
        }
        if(gExchange[playerid][i][xType] == BET_SKIN)
        {
            gExchange[playerid][i][xWear] = wear;
            gExchange[playerid][i][xPremium] = premium;
        }
        UpdateExchangeText(playerid);
        return SendInfo(playerid, "Вы добавили предмет в обмен.");
    }
    return SendAccess(playerid, "Во вкладе нет мест.");
}

cmd:stopex(const playerid, const params[])
{
    if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID)
        return 1;

    SendInfo(playerid, "%s [%d] отказался от обмена.", get_name(playerid), playerid);
    SendInfo(p_info[playerid][exchangePartner], "%s [%d] отказался от обмена.", get_name(playerid), playerid);
    EndExchange(playerid);
    return 1;
}

EndExchange(const playerid)
{
    if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID)
        return 0;
    new targetid = p_info[playerid][exchangePartner];

    DeletePVar(targetid, "EXCHANGE:ready");
    DeletePVar(playerid, "EXCHANGE:ready");

    DeletePVar(targetid, "EXCHANGE:confirmed");
    DeletePVar(playerid, "EXCHANGE:confirmed");

    DestroyDynamic3DTextLabel(p_info[playerid][exchangeText] != INVALID_3DTEXT_ID ?
        p_info[playerid][exchangeText] : p_info[targetid][exchangeText]);

    p_info[playerid][exchangeText] = INVALID_3DTEXT_ID;
    p_info[targetid][exchangeText] = INVALID_3DTEXT_ID;

    SendInfo(targetid, "Процесс обмена завершен.");
    SendInfo(playerid, "Процесс обмена завершен.");

    p_info[targetid][exchangePartner] = INVALID_PLAYER_ID;
    p_info[playerid][exchangePartner] = INVALID_PLAYER_ID;

    if(p_temp[playerid][TextDrawTrade]) HideTextDrawForPlayer(playerid, TD_ID_TRADE);
    if(p_temp[targetid][TextDrawTrade]) HideTextDrawForPlayer(targetid, TD_ID_TRADE);
    return 1;
}

UpdateExchangeText(playerid)
{
    if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID) return 0;
    if(p_temp[playerid][TextDrawTrade]) Equipment_TradeLeft(playerid, p_temp[playerid][InterfaceID]);
    return 1;
}

cmd:bet(const playerid, const params[])
{
    if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID)
        return SendError(playerid, "Вы не участвуете в обмене.");
    if(GetPVarInt(playerid, "EXCHANGE:ready"))
        return SendError(playerid, "Когда Вы готовы, Вам запрещено изменять вклад.");
    if(!p_temp[playerid][TextDrawTrade]) ShowTextDrawForPlayer(playerid, TD_ID_TRADE);
    else ShowBetMenu(playerid);
    return 1;
}

ExchangeUnBet(playerid, id)
{
    if(gExchange[playerid][id][xType] == INVALID_EXCHANGE)
        return SendError(playerid, "В слоте ничего не было.");

    gExchange[playerid][id][xType] =
    gExchange[playerid][id][xItemID] =
    gExchange[playerid][id][xValue] = INVALID_EXCHANGE;
    UpdateExchangeText(playerid);

    SetPVarInt(p_info[playerid][exchangePartner], "EXCHANGE:confirmed", false);
    SetPVarInt(playerid, "EXCHANGE:ready", false);
    SetPVarInt(p_info[playerid][exchangePartner], "EXCHANGE:ready", false);

    SendAccess(playerid, "Вы удалили предмет из вклада.");
    return 1;
}

ProccessExchange(const firstid) // Процесс обмена
{
    new secondid = p_info[firstid][exchangePartner];
    if(secondid == INVALID_PLAYER_ID)
        return 0;

    new status1 = CheckPlayerExchange(firstid), // Проверка имущества
        status2 = CheckPlayerExchange(secondid); // Проверка имущества

    if((status1 + status2) == 2)
    {
        ClearItemsExchange(firstid, secondid); // Очищение имущества, освобождение слотов
        //------------------------------------
        TransferExchange(firstid, secondid);
        TransferExchange(secondid, firstid);
        save_player(firstid);
        save_player(secondid);
        MysqlUpdatePlayerInt(firstid, "bank", p_info[firstid][bank]);
        MysqlUpdatePlayerInt(secondid, "bank", p_info[secondid][bank]);

        EndExchange(firstid);
    }
    return 1;
}

CheckPlayerExchange(const playerid)
{
    new count_exchange[2],
        targetid = p_info[playerid][exchangePartner];
    if(targetid == INVALID_PLAYER_ID)
        return 0;
    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        switch(gExchange[playerid][i][xType])
        {
            case BET_MONEY:
            {
                if(gExchange[playerid][i][xValue] > p_info[playerid][bank])
                    return ExchangeFailed(playerid, "Недостаточно денег.");
            }
            case BET_INVENTORY:
            {
                new itemID = gExchange[playerid][i][xItemID];
                if(gExchange[playerid][i][xValue] > GetInventoryAmount(playerid, itemID))
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "Недостаточно количества \"%s\".", ItemsInfo[itemID][iName]);
                    return ExchangeFailed(playerid, STRING_GLOBAL);
                }

                count_exchange[0] = gExchange[playerid][i][xValue];
                count_exchange[1] = GetExchangeCountType(targetid, gExchange[playerid][i][xType], itemID);

                new free_amount = GetInventoryFreeItems(targetid, itemID);
                //SendDebug(targetid, "item_id %d | free %d | bet: %d", itemID, free_amount, count_exchange[0]);
                if((free_amount+count_exchange[1]) < count_exchange[0])
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "Недостаточно места под \"%s\".", ItemsInfo[itemID][iName]);
                    return ExchangeFailed(targetid, STRING_GLOBAL);
                }
            }
            case BET_ACCESSORIES, BET_SKIN, BET_VEHICLE_TUNE:
            {
                new itemID = gExchange[playerid][i][xItemID];
                if(itemID < 1)
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "Недостаточно количества \"%s\".", ItemsInfo[itemID][iName]);
                    return ExchangeFailed(playerid, STRING_GLOBAL);
                }
                count_exchange[0] = GetExchangeCountType(playerid, gExchange[playerid][i][xType]);
                count_exchange[1] = GetExchangeCountType(targetid, gExchange[playerid][i][xType]);

                new free_amount = GetInventoryFreeItems(targetid, itemID);
                //SendDebug(targetid, "(%d+%d) < %d", free_amount, count_exchange[1], count_exchange[0]);
                if((free_amount+count_exchange[1]) < count_exchange[0])
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "Недостаточно места под \"%s\".", ItemsInfo[itemID][iName]);
                    return ExchangeFailed(playerid, STRING_GLOBAL);
                }
            }
            case BET_CAR:
            {
                if(GetSlotVehicleMarket(gExchange[playerid][i][xValue]) != -1) return ExchangeFailed(playerid, "Взаимодействие с транспортным средство невозможно, оно находится на авторынке.");
                if(GetPlayerVehicleMySQLID(playerid, gExchange[playerid][i][xValue]) != -1) return ExchangeFailed(playerid, "Транспорт заспавнен.");
                new modelid = gExchange[playerid][i][xItemID],
                    vehicle_class = GetVehicleData(modelid, E_VD_TYPE),
                    rows = GetPlayerCountCars(p_info[targetid][ID], vehicle_class),
                    count_limit = GetPlayerLimiteCars(targetid, vehicle_class);

                count_exchange[0] = GetExchangeCountType(playerid, BET_CAR, vehicle_class);
                count_exchange[1] = GetExchangeCountType(targetid, BET_CAR, vehicle_class);

                //SendDebug(targetid, "%s: [%d-%d] = %d + %d < %d", get_name(targetid), count_limit, rows, (count_limit-rows), count_exchange[1], count_exchange[0]);
                if(((count_limit-rows)+count_exchange[1]) < count_exchange[0])
                    return ExchangeFailed(targetid, "Нет доступных слотов для этого типа Т/С.");
            }
            case BET_HOUSE:
            {
                if(h_info[gExchange[playerid][i][xItemID]][h_user_id] != p_info[playerid][ID])
                    return ExchangeFailed(playerid, "Нет дома в этом слоте.");

                if(p_info[targetid][key_h_rent] != INVALID_HOUSE_ID)
                    return ExchangeFailed(targetid, "Уже есть дом или Вы где-то подселён.");
                if(GetPlayerHotelID(targetid, 0) != -1 || GetPlayerHotelID(targetid, 1) != -1)
                    return ExchangeFailed(targetid, "У Вас есть номер в отеле.");
                if(p_info[targetid][level] < 2)
                    return ExchangeFailed(targetid, "У Вас нет 2-ого уровня.");

                count_exchange[0] = GetExchangeCountType(playerid, BET_HOUSE);
                count_exchange[1] = GetExchangeCountType(targetid, BET_HOUSE);

                //SendAccess(playerid, "1: %d | 2: %d", GetFreeSlotHouse(playerid), count_exchange[1]);

                if((GetFreeSlotHouse(targetid)+count_exchange[1]) < count_exchange[0])
                    return ExchangeFailed(targetid, "Нет доступных слотов для дома.");
            }
            case BET_BIZ:
            {
                new idx = gExchange[playerid][i][xItemID];

                if(b_info[idx][b_user_id] != p_info[playerid][ID])
                    return ExchangeFailed(playerid, "нет бизнеса в этом слоте.");

                count_exchange[0] = GetExchangeCountType(playerid, BET_BIZ);
                count_exchange[1] = GetExchangeCountType(targetid, BET_BIZ);

                //SendAccess(playerid, "1: %d | 2: %d", GetFreeSlotBizz(playerid), count_exchange[1]);
                //if((GetFreeSlotBizz(playerid)+count_exchange[0]) < count_exchange[1])
                //    return ExchangeFailed(playerid, "Нет доступных слотов для бизнеса.");

                if((GetFreeSlotBizz(targetid)+count_exchange[1]) < count_exchange[0])
                    return ExchangeFailed(targetid, "Нет доступных слотов для бизнеса.");

                if(b_info[idx][_tip] == B_TAXI && GetPlayerBizzIDType(targetid, B_TAXI) != INVALID_BIZZ_ID)
                    return ExchangeFailed(targetid, "У Вас уже есть таксопарк.");
                if(b_info[idx][_tip] == B_TRUCKER && GetPlayerBizzIDType(targetid, B_TRUCKER) != INVALID_BIZZ_ID)
                    return ExchangeFailed(targetid, "У Вас уже есть транспортная компания.");
            }
            case BET_FAMILY:
            {
                new family_idx = gExchange[playerid][i][xItemID];
                if(p_info[playerid][family_id] == -1 || p_temp[playerid][family_game_id] != family_idx)
                    return ExchangeFailed(playerid, "У Вас нет семьи.");
                if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                    return ExchangeFailed(playerid, "Вы не владелец семьи.");
                if(FamilyData[family_idx][fHouseID] != INVALID_HOUSE_ID)
                    return ExchangeFailed(playerid, "У семьи имеется дом, передача не возможна.");

                count_exchange[0] = GetExchangeCountType(playerid, BET_FAMILY);
                count_exchange[1] = GetExchangeCountType(targetid, BET_FAMILY);

                if(p_info[targetid][family_id] != -1 && count_exchange[1] < count_exchange[0])
                    return ExchangeFailed(targetid, "У Вас уже есть семья.");
            }
            case BET_COSTUME:
            {
                new idx = gExchange[playerid][i][xItemID];
                if(p_info[playerid][costume][idx] != 1)
                    return ExchangeFailed(playerid, "У Вас нет костюма.");
                if(p_info[targetid][costume][idx] == 1)
                    return ExchangeFailed(playerid, "У игрока уже есть костюм.");
            }
        }
    }
    return 1;
}

GetExchangeCountType(playerid, ex_type, ex_subtype = -1)
{
    new count_ex_type;
    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        if((ex_type == BET_ACCESSORIES || ex_type == BET_SKIN || ex_type == BET_VEHICLE_TUNE) && 
            (gExchange[playerid][i][xType] == BET_ACCESSORIES || gExchange[playerid][i][xType] == BET_SKIN || gExchange[playerid][i][xType] == BET_VEHICLE_TUNE))
        {
            count_ex_type++;
        }
        else
        {
            if(gExchange[playerid][i][xType] == ex_type)
            {
                if(ex_subtype == -1) count_ex_type++;
                if(ex_type == BET_INVENTORY && gExchange[playerid][i][xItemID] == ex_subtype)
                {
                    count_ex_type = gExchange[playerid][i][xValue];
                    break;
                }
                if(ex_type == BET_CAR)
                {
                    if(GetVehicleData(gExchange[playerid][i][xItemID], E_VD_TYPE) == ex_subtype) count_ex_type++;
                }
            }
        }
    }
    return count_ex_type;
}
ExchangeFailed(const playerid, const reason[])
{
    new targetid = p_info[playerid][exchangePartner];
    UpdateExchangeText(playerid);
    if(targetid != INVALID_PLAYER_ID)
    {
        SendError(playerid, "При обмене с %s [%d]. Причина: %s", get_name(targetid), targetid, reason);
        SendError(targetid, "При обмене с %s [%d]. Причина: %s", get_name(playerid), playerid, reason);
        DeletePVar(targetid, "EXCHANGE:confirmed");
        DeletePVar(targetid, "EXCHANGE:ready");
    }
    DeletePVar(playerid, "EXCHANGE:ready");
    DeletePVar(playerid, "EXCHANGE:confirmed");
    return 0;
}

ClearItemsExchange(const firstid, const secondid)
{
    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        switch(gExchange[firstid][i][xType])
        {
            case BET_MONEY:
            {
                p_info[firstid][bank] -= gExchange[firstid][i][xValue];
                MysqlUpdatePlayerInt(firstid, "bank", p_info[firstid][bank]);

                if(p_info[firstid][bank] < 0)
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] переводил %s[%d]: %d$ | ЗАБАГАЛИ TRADE(!!!)",  get_name(firstid), firstid, get_name(secondid), secondid, gExchange[firstid][i][xItemID]);
                    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда | деньги')",
                        get_name(secondid), timestamp + (30 * 86400));
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда | деньги')",
                        get_name(firstid), timestamp + (30 * 86400));
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    Kick(secondid);
                    Kick(firstid);
                }
            }
            case BET_INVENTORY:
            {
                GivePlayerInventory(firstid, gExchange[firstid][i][xItemID], -gExchange[firstid][i][xValue]);
                //    return ExchangeFailed(firstid, "Не удалось обнулить значение.");
            }
            case BET_ACCESSORIES, BET_SKIN, BET_VEHICLE_TUNE:
            {
                DropPlayerEquipment(firstid, gExchange[firstid][i][xValue]);
            }
            case BET_HOUSE:
            {
                new house_id = gExchange[firstid][i][xItemID];
                ClearOwnerHouse(firstid, house_id);
            }
            case BET_BIZ:
            {
                new bizz_id = gExchange[firstid][i][xItemID];
                ClearOwnerBizz(firstid, bizz_id);
            }

            case BET_FAMILY:
            {
                new family_idx = gExchange[firstid][i][xItemID];
                p_info[firstid][family_rang] =
                p_info[firstid][family_warn] =
                p_info[firstid][family_mute] = 0;
                p_info[firstid][family_id] =
                p_temp[firstid][family_game_id] = -1;
                FamilyData[family_idx][fOwnerID] = INVALID_MYSQL_ID;
            }
            case BET_COSTUME:
            {
                new idx = gExchange[firstid][i][xItemID];
                p_info[firstid][costume][idx] = 0;
                if(p_info[firstid][costume_use][idx] == 1) TakePlayerAttachedCostume(firstid, idx, true);
                else SavePlayerCostume(firstid);
            }
        }
        switch(gExchange[secondid][i][xType])
        {
            case BET_MONEY:
            {
                p_info[secondid][bank] -= gExchange[secondid][i][xValue];
                MysqlUpdatePlayerInt(secondid, "bank", p_info[secondid][bank]);

                if(p_info[secondid][bank] < 0)
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] переводил %s[%d]: %d$ | ЗАБАГАЛИ TRADE(!!!)",  get_name(secondid), secondid, get_name(firstid), firstid, gExchange[secondid][i][xItemID]);
                    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда / деньги')",
                        get_name(firstid), timestamp + (30 * 86400));
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда / деньги')",
                        get_name(secondid), timestamp + (30 * 86400));
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    Kick(firstid);
                    Kick(secondid);
                }
            }
            case BET_INVENTORY:
            {
                GivePlayerInventory(secondid, gExchange[secondid][i][xItemID], -gExchange[secondid][i][xValue]);
                //    return ExchangeFailed(secondid, "Не удалось обнулить значение.");
            }
            case BET_SKIN, BET_ACCESSORIES, BET_VEHICLE_TUNE:
            {
                DropPlayerEquipment(secondid, gExchange[secondid][i][xValue]);
            }
            case BET_HOUSE:
            {
                new house_id = gExchange[secondid][i][xItemID];
                ClearOwnerHouse(secondid, house_id);
            }
            case BET_BIZ:
            {
                new bizz_id = gExchange[secondid][i][xItemID];
                ClearOwnerBizz(secondid, bizz_id);
            }
            case BET_FAMILY:
            {
                new family_idx = gExchange[secondid][i][xItemID];
                p_info[secondid][family_rang] =
                p_info[secondid][family_warn] =
                p_info[secondid][family_mute] = 0;
                p_info[secondid][family_id] =
                p_temp[secondid][family_game_id] = -1;
                FamilyData[family_idx][fOwnerID] = INVALID_MYSQL_ID;
            }
            case BET_COSTUME:
            {
                new idx = gExchange[secondid][i][xItemID];
                p_info[secondid][costume][idx] = 0;
                if(p_info[secondid][costume_use][idx] == 1) TakePlayerAttachedCostume(secondid, idx, true);
                else SavePlayerCostume(secondid);
            }
        }
    }
}

TransferExchange(const from, const to)
{
    if(from == to || p_info[from][ID] == p_info[to][ID])
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d]%s[%d] ЗАБАГАЛ ТРЕЙД И БЫЛ ЗАБЛОКИРОВАН",  get_name(from), from, get_name(to), to);
        SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда / получатель он же отправитель')",
            get_name(to), timestamp + (30 * 86400));
        mysql_tquery(con_bd, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда / получатель он же отправитель')",
            get_name(from), timestamp + (30 * 86400));
        mysql_tquery(con_bd, STRING_GLOBAL);

        Kick(to);
        Kick(from);
        return 1;
    }
    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        switch(gExchange[from][i][xType])
        {
            case BET_MONEY:
            {
                if(p_info[from][bank] < 0 || p_info[to][bank] < 0)
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] переводил %s[%d]: %d$ | ЗАБАГАЛИ TRADE(!!!)",  get_name(from), from, get_name(to), to, gExchange[from][i][xItemID]);
                    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда . деньги')",
                        get_name(to), timestamp + (30 * 86400));
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('System', '%e', NOW(), '%d', 'Багоюз трейда . деньги')",
                        get_name(from), timestamp + (30 * 86400));
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    Kick(to);
                    Kick(from);
                }

                new tax = GetTaxCount(to, gExchange[from][i][xValue], TAX_TRADE);
                p_info[to][bank] += (gExchange[from][i][xValue]-tax);
                MysqlUpdatePlayerInt(to, "bank", p_info[to][bank]);

                Log(LOG_player, INFO, "%s[%d](%s %s)[BANK: %d$ | MONEY: %d$] отправил через банк деньги %s[%d](%s %s)[BANK: %d$ | MONEY: %d$] в сумме %d$. Налог: %d$ | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC", p_info[from][bank], p_info[from][cash],
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC", p_info[to][bank], p_info[to][cash],
                    gExchange[from][i][xValue]-tax, tax);

                Log(LOG_player, INFO, "%s[%d](%s %s)[BANK: %d$ | MONEY: %d$] получил через банк деньги от %s[%d](%s %s)[BANK: %d$ | MONEY: %d$] в сумме %d$. Налог: %d$ | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC", p_info[to][bank], p_info[to][cash],
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC", p_info[from][bank], p_info[from][cash],
                    gExchange[from][i][xValue]-tax, tax);

                //p_info[from][bank] -= gExchange[from][i][xItemID];
                //MysqlUpdatePlayerInt(from, "bank", p_info[from][bank]);

                SetFractionWarehouse(MAYOR_LS, fwMoney, tax);
            }
            case BET_CAR:
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE vehicle SET v_owner_id = %d WHERE `v_mysql_id` = %d",
                    p_info[to][ID], gExchange[from][i][xValue]);
                mysql_tquery(con_bd, STRING_GLOBAL);

                CheckPlayerMission(to, START_VEHICLE);

                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) перевел Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) т/с <Infernus>(%d)[%d]
                Log(LOG_player, INFO, "%s[%d](%s %s) перевел %s[%d](%s %s) транспортное средство <%s>(%d)[%d] | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    GetVehicleName(INVALID_VEHICLE_ID, gExchange[from][i][xItemID]), gExchange[from][i][xItemID], gExchange[from][i][xItemID]);

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) т/с <Infernus>(%d)[%d]
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) транспортное средство <%s>(%d)[%d] | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    GetVehicleName(INVALID_VEHICLE_ID, gExchange[from][i][xItemID]), gExchange[from][i][xItemID], gExchange[from][i][xItemID]);
            }
            case BET_HOUSE:
            {
                new house_id = gExchange[from][i][xItemID];
                ClearOwnerHouse(from, house_id);
                SetFreeSlotHouse(to, house_id);

                p_info[from][spawn] = SPAWN_DEFAULT;
                h_info[house_id][h_user_id] = p_info[to][ID];
                strmid(h_info[house_id][h_owner], get_name(to), 0, strlen(get_name(to)), MAX_PLAYER_NAME);
                h_info[house_id][h_owned_at] = timestamp;
                h_info[house_id][h_paydays_received] = 0;

                new targetid;
                for(new i; i <= h_info[house_id][h_squar]; i++)
                {
                    if(h_info[house_id][h_r_user_id][i] != INVALID_MYSQL_ID)
                    {
                        targetid = GetPlayerUserID(h_info[house_id][h_user_id]);
                        house_rent_leave(house_id, i);
                        if(targetid != INVALID_PLAYER_ID) SendInfo(targetid, "Владелец дома продал его, Вы были выселены.");
                    }
                }

                new family_idx = GetFamilyIDFromHouseID(house_id);
                if(family_idx != -1)
                {
                    DeleteFamilyVehicle(family_idx);

                    FamilyData[family_idx][fHouseID] = INVALID_HOUSE_ID;
                    h_info[house_id][h_family_id] = -1;

                    SendFamilyMessage(family_idx, "Дом семьи был продан владелецем.");
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `house_id` = -1 WHERE `id` = %d", FamilyData[family_idx][fMysqlID]);
                    mysql_tquery (con_bd, STRING_GLOBAL);
                }

                h_info[house_id][h_delete] = 0;
                h_info[house_id][h_delete_time] = 0;

                update_house(house_id);
                save_house(house_id);
                // -----===== [ Покупка дома ] =====-----
                CheckPlayerMission(to, START_HOUSE);

                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) перевел Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) дом (%d)[%d]
                Log(LOG_player, INFO, "%s[%d](%s %s) перевел %s[%d](%s %s) дом (%d)[%d] | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    house_id, h_info[house_id][h_mysql_id]);

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) дом (%d)[%d]
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) дом (%d)[%d] | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    house_id, h_info[house_id][h_mysql_id]);

                //lastlog(BUY_HOUSE_PLAYER,"обмен дома у игрока [БИРЖА]", h_info[house_id][h_mysql_id], to, from, 0);
                //lastlog(SELL_HOUSE_PLAYER,"обмен дома игроку [БИРЖА]", h_info[house_id][h_mysql_id], from, to, 0);
            }
            case BET_BIZ:
            {
                new bizz_id = gExchange[from][i][xItemID];
                ClearOwnerBizz(from, bizz_id);
                SetFreeSlotBizz(to, bizz_id);

                switch(b_info[bizz_id][_tip])
                {
                    case B_TAXI:
                    {
                        p_info[from][taxi_rank] = 0;
                        p_info[from][taxi_idx] = 0;
                        p_info[from][taxi_percent] = 0;
                        p_info[from][taxi_salary] = 0;
                        p_info[from][taxi_salary_all] = 0;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_rank` = 0, `taxi_idx` = 0, `taxi_percent` = 0, `taxi_salary` = 0, `taxi_salary_all` = 0 WHERE `id` = %d",
                            p_info[from][ID]);
                        mysql_tquery(con_bd, STRING_GLOBAL);

                        p_info[to][taxi_rank] = 3;
                        p_info[to][taxi_idx] = bizz_id;
                        p_info[to][taxi_percent] = b_info[bizz_id][_percent];
                        p_info[to][taxi_salary] = 0;
                        p_info[to][taxi_salary_all] = 0;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_rank` = '3', `taxi_idx` = %d, `taxi_percent` = %d, `taxi_salary` = 0, `taxi_salary_all` = 0 WHERE `id` = %d",
                            p_info[to][taxi_idx], p_info[to][taxi_percent], p_info[to][ID]);
                        mysql_tquery(con_bd, STRING_GLOBAL);
                    }
                    case B_TRUCKER:
                    {
                        p_info[from][tc_rank] = 0;
                        p_info[from][tc_idx] = 0;
                        p_info[from][tc_percent] = 0;
                        p_info[from][tc_salary] = 0;
                        p_info[from][tc_salary_all] = 0;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc` = 0, `tc_rank` = 0, `tc_idx` = 0, `tc_percent` = 0, `tc_salary` = 0, `tc_salary_all` = 0 WHERE `id` = %d",
                        p_info[from][ID]);
                        mysql_tquery(con_bd, STRING_GLOBAL);

                        p_info[to][tc_rank] = 3;
                        p_info[to][tc_idx] = bizz_id;
                        p_info[to][tc_percent] = b_info[bizz_id][_percent];
                        p_info[to][tc_salary] = 0;
                        p_info[to][tc_salary_all] = 0;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_rank` = '3', `tc_idx` = %d, `tc_percent` = %d, `tc_salary` = 0, `tc_salary_all` = 0 WHERE `id` = %d",
                        p_info[to][tc_idx], p_info[to][tc_percent], p_info[to][ID]);
                        mysql_tquery(con_bd, STRING_GLOBAL);
                    }
                }
                b_info[bizz_id][b_owned_at] = timestamp;
                b_info[bizz_id][b_paydays_received] = 0;
                b_info[bizz_id][b_user_id] = p_info[to][ID];
                strmid(b_info[bizz_id][_owner], get_name(to), 0, strlen(get_name(to)), MAX_PLAYER_NAME);
                update_bizz(bizz_id);
                save_bizz(bizz_id);

                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) перевел Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) бизнес <%s %s>(%d)[%d]
                Log(LOG_player, INFO, "%s[%d](%s %s) перевел %s[%d](%s %s) бизнес <%s %s>(%d)[%d] | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    b_info[bizz_id][_name], bizz_type_name[b_info[bizz_id][_tip]], bizz_id, b_info[bizz_id][b_mysql_id]);

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) бизнес <%s %s>(%d)[%d]
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) бизнес <%s %s>(%d)[%d] | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    b_info[bizz_id][_name], bizz_type_name[b_info[bizz_id][_tip]], bizz_id, b_info[bizz_id][b_mysql_id]);

                //lastlog(BUY_BIZZ_PLAYER,"обмен бизнеса у игрока [БИРЖА]", b_info[bizz_id][b_mysql_id], from, to, 0);
                //lastlog(SELL_BIZZ_PLAYER,"обмен бизнеса игроку  [БИРЖА]", b_info[bizz_id][b_mysql_id], to, from, 0);
            }
            case BET_INVENTORY, BET_VEHICLE_TUNE:
            {
                new itemID = gExchange[from][i][xItemID];

                if(gExchange[from][i][xType] == BET_INVENTORY)
                    GivePlayerInventory(to, itemID, gExchange[from][i][xValue]);
                else GivePlayerInventory(to, itemID, 1);

                Log(LOG_player, INFO, "%s[%d](%s %s)[%d] отправил <%s> %s[%d](%s %s)[%d] в количестве %d ед. | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC", ItemsInfo[itemID][iName],
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC", itemID);

                Log(LOG_player, INFO, "%s[%d](%s %s)[%d] получил <%s> от %s[%d](%s %s)[%d] в количестве %d ед. | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",  ItemsInfo[itemID][iName],
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC", itemID);
            }
            case BET_SKIN:
            {
                new skin_id = gExchange[from][i][xItemID], premium = gExchange[from][i][xPremium];
                GivePlayerInventory(to, skin_id, .wear = gExchange[from][i][xWear], .premium = premium);

                new wear[5];
                f(wear, "%.1f", gExchange[from][i][xWear]);
                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) перевел Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) скин (%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) перевел %s[%d](%s %s) <%s>(%d) [%s], Premium: %s | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    ItemsInfo[skin_id][iName], skin_id, wear, premium == 0 ? "Нет" : "Есть");

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) скин (%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) <%s>(%d) [%s], Premium: %s | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    ItemsInfo[skin_id][iName], skin_id, wear, premium == 0 ? "Нет" : "Есть");
            }
            case BET_ACCESSORIES:
            {
                new accessories_id = gExchange[from][i][xItemID], mc1 = gExchange[from][i][xMaterialColor][0], mc2 = gExchange[from][i][xMaterialColor][1], premium = gExchange[from][i][xPremium];
                GivePlayerInventory(to, accessories_id, 1, gExchange[from][i][xWear], mc1, mc2, .premium = premium);

                new wear[5];
                f(wear, "%.1f", gExchange[from][i][xWear]);
                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) передал Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) аксессуар <%s>(%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) передал %s[%d](%s %s) <%s>(%d) [%s] (%s/%s), Premium: %s | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    ItemsInfo[accessories_id][iName], accessories_id, wear, AccessoriesColorInfo[mc1][acName], AccessoriesColorInfo[mc2][acName],
                    premium == 0 ? "Нет" : "Есть");

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) аксессуар <%s>(%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) <%s>(%d) [%s] (%s/%s), Premium: %s | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    ItemsInfo[accessories_id][iName], accessories_id, wear, AccessoriesColorInfo[mc1][acName], AccessoriesColorInfo[mc2][acName],
                    premium == 0 ? "Нет" : "Есть");
            }
            case BET_FAMILY:
            {
                new family_idx = gExchange[from][i][xItemID];

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] передал %s[%d] владение семьей.", get_name(from), from, get_name(to), to);
                SendFamilyMessage(family_idx, STRING_GLOBAL);

                FamilyData[family_idx][fOwnerID] = p_info[to][ID];
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `family` SET `owner_id` = %d WHERE `id` = %d",
                    FamilyData[family_idx][fOwnerID], FamilyData[family_idx][fMysqlID]);
                mysql_tquery(con_bd, STRING_GLOBAL);

                p_info[to][family_id] = FamilyData[family_idx][fMysqlID];
                p_info[to][family_rang] = MAX_FAMILY_RANG;
                p_info[to][family_warn] =
                p_info[to][family_mute] = 0;
                p_temp[to][family_game_id] = family_idx;

                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) передал Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) аксессуар <%s>(%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) передал %s[%d](%s %s) семью <%s>(%d)[%d] | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    FamilyData[family_idx][fName], family_idx, FamilyData[family_idx][fMysqlID]);

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) аксессуар <%s>(%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) семью <%s>(%d)[%d] | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    FamilyData[family_idx][fName], family_idx, FamilyData[family_idx][fMysqlID]);
            }
            case BET_COSTUME:
            {
                new costume_id = gExchange[from][i][xItemID];
                GivePlayerCostume(to, costume_id);
                // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1) передал Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) костюм <%s>(%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) передал %s[%d](%s %s) костюм <%s>(%d) | #TRADE",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    CostumeName[costume_id], costume_id);

                // Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2) получил от Hardi_Devidson[1](192.168.1.1 - Offline) костюм <%s>(%d)
                Log(LOG_player, INFO, "%s[%d](%s %s) получил от %s[%d](%s %s) костюм <%s>(%d) | #TRADE",
                    get_name(to), p_info[to][ID], p_temp[to][session_IP], IsPlayerMobile(to) ? "Mobile": "PC",
                    get_name(from), p_info[from][ID], p_temp[from][session_IP], IsPlayerMobile(from) ? "Mobile": "PC",
                    CostumeName[costume_id], costume_id);
            }
        }
    }
    return 1;
}

cmd:ready(const playerid, const params[])
{
    new targetid = p_info[playerid][exchangePartner];
    if(targetid == INVALID_PLAYER_ID)
        return SendError(playerid, "Вы не участвуете в обмене.");

    if(GetPVarInt(targetid, "EXCHANGE:ready"))
    {
        SetPVarInt(playerid, "EXCHANGE:ready", true);
        if(p_temp[playerid][TextDrawTrade]) Interface_Show(playerid, EQUIPMENT_TRADE_READY);
        else
        {
            ShowTextDrawForPlayer(playerid, TD_ID_TRADE);
            Interface_Show(playerid, EQUIPMENT_TRADE_READY);
        }
        if(p_temp[targetid][TextDrawTrade]) Interface_Show(targetid, EQUIPMENT_TRADE_READY);
        else
        {
            ShowTextDrawForPlayer(targetid, TD_ID_TRADE);
            Interface_Show(targetid, EQUIPMENT_TRADE_READY);
        }
        return 1;
    }

    if(GetPVarInt(playerid, "EXCHANGE:ready"))
    {
        SetPVarInt(playerid, "EXCHANGE:ready", false);
        SendInfo(playerid, "Вы отменили готовность провести обмен.");
        SendInfo(targetid, "%s [%d] не готов провести обмен.", get_name(playerid), playerid);
        UpdateExchangeText(playerid);
        return 1;
    }

    SetPVarInt(playerid, "EXCHANGE:ready", true);
    SendInfo(playerid, "Вы готовы провести обмен.");
    SendInfo(targetid, "%s [%d] готов провести обмен.", get_name(playerid), playerid);

    UpdateExchangeText(playerid);
    if(p_temp[playerid][TextDrawTrade]) HideTextDrawForPlayer(playerid, TD_ID_TRADE);
    return 1;
}

ShowBetMenu(const playerid)
{
    SetPVarInt(playerid, #EQ_CONTROL_BLOCK, true);
    ShowPlayerDialog(playerid, D_EXCHANGE_BET, DIALOG_STYLE_LIST, ""I"Выберите тип вклада", "\
        "I"[1]"W" Деньги\n\
        "I"[2]"W" Транспорт\n\
        "I"[3]"W" Дом\n\
        "I"[4]"W" Бизнес\n\
        "I"[6]"W" Предмет инвентаря\n\
        "I"[7]"W" Семья\n\
        "I"[8]"W" Костюмы", "Добавить", "Отмена");
}

ShowBetMoney(playerid)
{
    SetPVarInt(playerid,  #EQ_CONTROL_BLOCK, true);
    ShowPlayerDialog(playerid, D_EXCHANGE_BET_MONEY, DIALOG_STYLE_INPUT,
        ""I"Вклад: деньги",
        ""W"Введите сумму, которую Вы хотите добавить в свой вклад:\nминимальная — $1000; максимальная — $500 000 000.\n"\
        "Деньги будут списаны с Вашего банковского счета.",
        "Добавить", "Отмена");
}

ShowBetAmountInventory(playerid, id)
{
    SetPVarInt(playerid,  #EQ_CONTROL_BLOCK, true);
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""W"Введите количество \"%s\", которое Вы хотите добавить в свой вклад:\nминимальная — 1 ед.; максимальная — %d ед.",
        ItemsInfo[id][iName], GetInventoryAmount(playerid, id));
    ShowPlayerDialog(playerid, D_EXCHANGE_BET_INVENTORY, DIALOG_STYLE_INPUT,""I"Вклад: инвентарь",STRING_GLOBAL, "Добавить", "Отмена");
}

ShowExchangeBetCar(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "SELECT `v_model`, `v_mysql_id`, `v_bonus`, `v_sell_block`, `v_number` FROM `vehicle` WHERE `v_owner_id` = %d AND `v_bonus` = 0 LIMIT 20 OFFSET %d",
        p_info[playerid][ID], (p_temp[playerid][inv_list_page][0]-1)*20);
    mysql_tquery(con_bd, STRING_GLOBAL, "TradeListRightCars", "i", playerid);
}

forward TradeListRightCars(const playerid);
public TradeListRightCars(const playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows)
    {
        if(p_temp[playerid][inv_list_page][0] <= 1)
        {
            p_temp[playerid][inv_list_page][0] = 1;
            Interface_Show(playerid, EQUIPMENT_TRADE);
            SendError(playerid, "У Вас нет предметов выбранного типа.");
        }
        else
        {
            p_temp[playerid][inv_list_page][0]--;
            SendError(playerid, "Вы находитесь на последней странице.");

            f(STRING_GLOBAL, "%d", p_temp[playerid][inv_list_page][0]);
            PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][51], STRING_GLOBAL);
            return 1;
        }
    }
    new status_used[36], model;
    for(new i; i < 20; i++)
    {
        if(i < rows)
        {
            cache_get_value_name_int(i, "v_model", model);
            cache_get_value_name_int(i, "v_mysql_id", p_temp[playerid][p_listitem_cars][i]);

            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+i], true);
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], model);
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], -10.0, 0.0, 45.0, 1.0);
            f(status_used, "ID: %d", model);
            PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], status_used);
        }
        else Equipment_TDClearSlotRight(playerid, i);
        PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+i]);
    }
    return 1;
}

forward LoadBetCar(const playerid);
public LoadBetCar(const playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows)
        return SendError(playerid, "Ничего не найдено.");

    new model, mysql, twinturbo, insurance, number[16];
    cache_get_value_name_int(0, "v_model", model);
    cache_get_value_name_int(0, "v_mysql_id", mysql);
    cache_get_value_name_int(0, "v_twinturbo", twinturbo);
    cache_get_value_name_int(0, "v_insurance", insurance);
    cache_get_value_name(0, "v_number", number, 16);

    if(insurance == 0 && (GetVehicleData(model, E_VD_TYPE) == VEHICLE_STATE_VELO_MOPED || GetVehicleData(model, E_VD_TYPE) == VEHICLE_STATE_MOTO || GetVehicleData(model, E_VD_TYPE) == VEHICLE_STATE_CAR))
        return SendError(playerid, "На транспортном средстве должна быть страховка.");

    AddExchangeBet(playerid, BET_CAR, model, mysql, number, twinturbo);
    return 1;
}

forward trade_info_vehicle(playerid);
public trade_info_vehicle(playerid)
{
    if(INVALID_PLAYER_ID == playerid)
        return 1;
    if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID)
        return 1;
    new rows;
    cache_get_row_count(rows);
    if(!rows)
        return SendError(playerid, "Нет транспортного средства.");

    new veh_number[16] = "НЕТ НОМЕРОВ", veh_model, veh_premium, temp_insurance, temp_v_owner_id;
    STRING_GLOBAL[0] = EOS;

    cache_get_value_name_int(0, "v_owner_id", temp_v_owner_id);
    cache_get_value_name(0, "v_number", veh_number, 16);
    if(strequals(veh_number, "NULL")) veh_number = "НЕТ НОМЕРОВ";
    cache_get_value_name_int(0, "v_model", veh_model);
    cache_get_value_name_int(0, "v_premium", veh_premium);
    cache_get_value_name_int(0, "v_insurance", temp_insurance);

    new data[144], veh_turbo[4], Float:veh_details[5];
    cache_get_value_name(0, "v_twinturbo_data", data); // 0|0|0|0
    sscanf(data, "p<|>a<i>[4]", veh_turbo);

    cache_get_value_name(0, "v_details", data); // 100.0|100.0|100.0|100.0|100.0
    sscanf(data, "p<|>a<f>[5]", veh_details);

    new vehicleupgrade = veh_turbo[tt_suspension] + veh_turbo[tt_transmission] + veh_turbo[tt_turbocharging] + veh_turbo[tt_engine];
    new Float:vehiclemaxspeed = GetVehicleData(veh_model, E_VD_MAX_SPEED) * (1.0 + (vehicleupgrade * 0.1));
    if(vehiclemaxspeed > 270.0) vehiclemaxspeed = 270.0;

    new targetid = p_info[playerid][exchangePartner];

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""W"Технический паспорт:\n\nМодель: "I"%s\n\
        "W"Владелец: "I"%s\n\
        "W"Номерной знак: "I"%s"W"\n\
        "W"Страховка: "I"%s", GetVehicleName(INVALID_VEHICLE_ID, veh_model), get_name(temp_v_owner_id == p_info[playerid][ID] ? playerid : targetid), veh_number,
        temp_insurance == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
    f(STRING_GLOBAL, "%s\n\n\
        "W"Технические характеристики:\n\n\
        Подвеска: %d из 3\n\
        Трансмиссия: %d из 3\n\
        Турбонаддув: %d из 3\n\
        Двигатель: %d из 3\n\n\
        Состояние стартера: %.1f\n\
        Состояние аккумулятора: %.1f\n\
        Состояние топливной системы: %.1f\n\
        Состояние сцепления: %.1f\n\
        Состояние двигателя: %.1f\n\n\
        Макс. скорость: %d KM/H\n\
        Макс. скорость с тюнингом: %d KM/H\n\n\
        Премиум: %s", STRING_GLOBAL,
        veh_turbo[tt_suspension], veh_turbo[tt_transmission],
        veh_turbo[tt_turbocharging], veh_turbo[tt_engine],
        veh_details[0], veh_details[1], veh_details[2],
        veh_details[3], veh_details[4], floatround(GetVehicleData(veh_model, E_VD_MAX_SPEED)),
        floatround(vehiclemaxspeed), (veh_premium == 1) ? ("{"#cGREEN"}Есть"W"") : ("{"#cLIGHTRED"}Нет"W""));
    ShowPlayerDialog(playerid, D_EXCHANGE_PREVIEW_INFO, DIALOG_STYLE_MSGBOX, ""W"Информация: "I"Т/С", STRING_GLOBAL, "Назад", "");
    return 1;
}

Equipment_TradeRight(playerid, type_id)
{
    switch(type_id)
    {
        case EQUIPMENT_TRADE_BET_CAR:
        {
            if(!IsPlayerInDynamicArea(playerid, VEHICLE_MARKET_CUBE)) return SendError(playerid, "Вы должны быть на территории авторынка.");
            ShowExchangeBetCar(playerid);
        }
        case EQUIPMENT_TRADE_BET_HOUSE:
        {
            new str[36] = "_", house_id;
            for(new i; i < 20; i++)
            {
                if(i < p_info[playerid][house_slots])
                {
                    house_id = GetPlayerHouseID(playerid, i);
                    if(house_id != INVALID_HOUSE_ID)
                    {
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+i], true);
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 19522);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                        f(str, "ID: %d", house_id);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    else Equipment_TDClearSlotRight(playerid, i);
                }
                else Equipment_TDClearSlotRight(playerid, i);
                PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+i]);
            }
        }
        case EQUIPMENT_TRADE_BET_BIZ:
        {
            new str[36] = "_", bizz_id;
            for(new i; i < 20; i++)
            {
                if(i < p_info[playerid][bizz_slots])
                {
                    bizz_id = GetPlayerBizzID(playerid, i);
                    if(bizz_id != INVALID_BIZZ_ID)
                    {
                        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+i], true);
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 1274);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                        f(str, "ID: %d", bizz_id);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    else Equipment_TDClearSlotRight(playerid, i);
                }
                else Equipment_TDClearSlotRight(playerid, i);
                PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+i]);
            }
        }
        case EQUIPMENT_TRADE_BET_INVENTORY:
        {
            new itemId, start = ((p_temp[playerid][inv_list_page][0]-1)*20), count;
            for(new i = start; i < start+20; i++)
            {
                if(i >= p_info[playerid][inv_slots]) break;
                if(InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID)
                {
                    Equipment_TDClearSlotRight(playerid, count);
                    PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+count]);
                    count++;
                    continue;
                }
                itemId = InventoryPlayer[playerid][i][inv_item_id];

                PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+count], true);
                PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+count], ItemsInfo[itemId][iModel] == 74 ? 0 : ItemsInfo[itemId][iModel]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+count], ItemsInfo[itemId][iObjectPos][0], ItemsInfo[itemId][iObjectPos][1], ItemsInfo[itemId][iObjectPos][2], ItemsInfo[itemId][iObjectPos][3]);
                PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+count]);

                if(ItemsInfo[itemId][iType] == TYPE_ITEMS_INVENTORY)
                    f(STRING_GLOBAL, "%d", InventoryPlayer[playerid][i][inv_amount]);
                else
                    f(STRING_GLOBAL, "ID: %d", itemId);
                PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+count], STRING_GLOBAL);
                count++;
            }
        }
        case EQUIPMENT_TRADE_READY:
        {
            new targetid = p_info[playerid][exchangePartner];
            if(targetid == INVALID_PLAYER_ID) return 1;
            new str[24];
            for(new i; i < 10; i++)
            {
                Equipment_TDClearSlotRight(playerid, 10+i);
                PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][15+i]);

                PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+i], true);
                switch(gExchange[targetid][i][xType])
                {
                    case BET_CAR:
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], gExchange[targetid][i][xItemID]);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], -10.0, 0.0, 45.0, 1.0);

                        f(str, "ID: %d", gExchange[targetid][i][xItemID]);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    case BET_HOUSE:
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 19522);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                        f(str, "ID: %d", gExchange[targetid][i][xItemID]);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    case BET_BIZ:
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 1274);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                        f(str, "ID: %d", gExchange[targetid][i][xItemID]);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    case BET_INVENTORY, BET_ACCESSORIES, BET_SKIN, BET_VEHICLE_TUNE:
                    {
                        new idx = gExchange[targetid][i][xItemID];
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], ItemsInfo[idx][iModel]);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], ItemsInfo[idx][iObjectPos][0], ItemsInfo[idx][iObjectPos][1], ItemsInfo[idx][iObjectPos][2], ItemsInfo[idx][iObjectPos][3]);
                        if(ItemsInfo[idx][iType] == TYPE_ITEMS_INVENTORY)
                            f(str, "%d", gExchange[targetid][i][xValue]);
                        else
                            f(str, "ID: %d", idx);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    case BET_COSTUME:
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 1275);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                    }
                    case BET_FAMILY:
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 1277);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], 0.0000, 0.0000, 180.0000, 1.0000);
                    }
                    case BET_MONEY:
                    {
                        PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+i], 1212);
                        PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+i], -45.0000, 0.0000, 45.0000, 1.0000);
                        f(str, "%d$", gExchange[targetid][i][xValue]);
                        PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][25+i], str);
                    }
                    default: Equipment_TDClearSlotRight(playerid, i);
                }
                PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+i]);
            }
        }
        default:
        {
            for(new i = 19; i != -1; i--)
            {
                Equipment_TDClearSlotRight(playerid, i);
                PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][5+i]);
            }
        }
    }
    return 1;
}

Equipment_TradeLeft(playerid, interface_id)
{
    new bool:block_button;
    for(new i = 0; i < MAX_EXCHANGE; i++)
    {
        PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][15+i], false);
        PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][15+i]);
        PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][15+i], "_");

        PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], "_");
        if(gExchange[playerid][i][xType] == INVALID_EXCHANGE)
        {
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+i], false);
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 0);
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], 0.000000, 0.000000, 0.000000, -1.000000);
            if(interface_id != EQUIPMENT_TRADE_READY && !block_button)
            {
                PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+i], true);
                PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], "Add");
                block_button = true;
            }
        }
        else
        {
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+i], true);
            new str[12];
            switch(gExchange[playerid][i][xType])
            {
                case BET_CAR:
                {
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], gExchange[playerid][i][xItemID]);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], -10.0, 0.0, 45.0, 1.0);

                    f(str, "ID: %d", gExchange[playerid][i][xItemID]);
                    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], str);
                }
                case BET_HOUSE:
                {
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 19522);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                    f(str, "ID: %d", gExchange[playerid][i][xItemID]);
                    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], str);
                }
                case BET_BIZ:
                {
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 1274);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                    f(str, "ID: %d", gExchange[playerid][i][xItemID]);
                    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], str);
                }
                case BET_INVENTORY, BET_ACCESSORIES, BET_SKIN, BET_VEHICLE_TUNE:
                {
                    new idx = gExchange[playerid][i][xItemID];
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], ItemsInfo[idx][iModel]);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], ItemsInfo[idx][iObjectPos][0], ItemsInfo[idx][iObjectPos][1], ItemsInfo[idx][iObjectPos][2], ItemsInfo[idx][iObjectPos][3]);
                    if(ItemsInfo[idx][iType] == TYPE_ITEMS_INVENTORY)
                        f(str, "%d", gExchange[playerid][i][xValue]);
                    else
                        f(str, "ID: %d", idx);
                    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], str);
                }
                case BET_COSTUME:
                {
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 1275);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], 0.0000, 0.0000, 0.0000, 1.0000);
                }
                case BET_FAMILY:
                {
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 1277);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], 0.0000, 0.0000, 180.0000, 1.0000);
                }
                case BET_MONEY:
                {
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+i], 1212);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+i], -45.0000, 0.0000, 45.0000, 1.0000);
                    f(str, "%d$", gExchange[playerid][i][xValue]);
                    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][25+i], str);
                }
            }
        }
        PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][5+i]);
    }
    return 1;
}

Equipment_TradeUpdate(playerid, interface_id)
{
    switch(interface_id)
    {
        case EQUIPMENT_TRADE:
        {
            PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][4], "Your contribution"); // Ваш вклад
            PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], "_"); // Игрока вклад
        }
        case EQUIPMENT_TRADE_BET_INVENTORY: PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], "Your items"); //"Ваш инвентарь");
        case EQUIPMENT_TRADE_BET_HOUSE: PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], "Your houses"); //"Ваши дома");
        case EQUIPMENT_TRADE_BET_BIZ: PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], "Your business"); //"Ваши бизнесы");
        case EQUIPMENT_TRADE_BET_CAR: PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], "Your cars"); //"Ваши Т/С");
        case EQUIPMENT_TRADE_READY:
        {
            if(p_info[playerid][exchangePartner] == INVALID_PLAYER_ID)
                return ExchangeFailed(playerid, "Второй игрок не в сети.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "Contribution %s", get_name(p_info[playerid][exchangePartner]));
            PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][4], STRING_GLOBAL);
        }
    }
    PlayerTextDrawSetString(playerid, PTD_EquipmentLeft[playerid][51], "1");
    PlayerTextDrawSetString(playerid, PTD_EquipmentRight[playerid][51], "1");
    return 1;
}

Equipment_TradeItemRight(playerid, interface_id, slot_id, button_id)
{
    switch(interface_id)
    {
        case EQUIPMENT_TRADE_BET_CAR:
        {
            if(!IsPlayerInDynamicArea(playerid, VEHICLE_MARKET_CUBE)) return SendError(playerid, "Вы должны быть на территории авторынка.");
            new index_list = p_temp[playerid][p_listitem_cars][slot_id];
            if(button_id == 1)
            {
                if(GetPlayerVehicleMySQLID(playerid, index_list) != -1)
                    return SendError(playerid, "Вы не выгрузили транспортное средство.");
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `vehicle` WHERE `v_mysql_id` = %d AND `v_owner_id` = %d", index_list, p_info[playerid][ID]);
                mysql_tquery(con_bd, STRING_GLOBAL, "LoadBetCar", "i", playerid);
            }
            else if(button_id == 2)
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_owner_id`, `v_number`, `v_model`, `v_premium`, `v_insurance`, `v_twinturbo_data`, `v_details` FROM `vehicle` WHERE `v_mysql_id` = %d", index_list);
                mysql_tquery(con_bd, STRING_GLOBAL, "trade_info_vehicle", "i", playerid);
            }
        }
        case EQUIPMENT_TRADE_BET_HOUSE:
        {
            new house_id = GetPlayerHouseID(playerid, slot_id);
            if(house_id == INVALID_HOUSE_ID)
                return SendError(playerid, "У Вас нет дома в этом слоте.");
            if(button_id == 1)
            {
                if(h_info[house_id][h_auction_bet] != 0 || h_info[house_id][h_auction_time] != 0)
                    return SendError(playerid, "Дом находится на аукционе, добавить в трейд нельзя.");
                AddExchangeBet(playerid, BET_HOUSE, house_id);
            }
            else if(button_id == 2)
            {
                if(p_temp[playerid][TextDrawTrade]) HideTextDrawForPlayer(playerid, TD_ID_TRADE);
                p_temp[playerid][pos_VW] = GetPlayerVirtualWorld(playerid);
                p_temp[playerid][pos_INT] = GetPlayerInterior(playerid);
                new idx = GetPlayerHouseID(playerid, slot_id);
                GetPlayerPos(playerid, p_temp[playerid][pos_X], p_temp[playerid][pos_Y], p_temp[playerid][pos_Z]);

                SetPlayerInterior(playerid,0);
                Fix_TogglePlayerControllable(playerid, false);
                SetPlayerPos(playerid,h_info[idx][h_enter][0], h_info[idx][h_enter][1], h_info[idx][h_enter][2]);

                new Float:hx, Float:hy, Float:hz, Float:ha,
                Float:hx2, Float:hy2;
                ha = h_info[idx][h_enter][3];
                hx = h_info[idx][h_enter][0] + 1.0 * floatsin(-ha, degrees); //смещение от Х вперед!
                hy = h_info[idx][h_enter][1] + 1.0 * floatcos(-ha, degrees); //смещение от Y вперед! в сторону куда смотрим(!)
                hz = h_info[idx][h_enter][2]+0.5;

                hx2 = hx - 12.0 * floatsin(ha, degrees);
                hy2 = hy + 6.0 * floatcos(ha, degrees);

                InterpolateCameraPos(playerid,hx,hy,hz,hx2,hy2,hz+2.2, 3500);
                InterpolateCameraLookAt(playerid,hx,hy,hz, hx,hy,hz, 3500);

                SetTimerEx("fixCameraProperty", 3510, 0, "iiifff", 2, playerid, idx, hx2,hy2,hz+2.2);
            }
        }
        case EQUIPMENT_TRADE_BET_BIZ:
        {
            new bizz_id = GetPlayerBizzID(playerid, slot_id);
            if(bizz_id == INVALID_HOUSE_ID)
                return SendError(playerid, "У Вас нет бизнеса в этом слоте.");
            if(button_id == 1)
            {
                if(b_info[bizz_id][b_auction_bet] != 0 || b_info[bizz_id][b_auction_time] != 0)
                    return SendError(playerid, "Бизнес находится на аукционе, нельзя добавить в трейд.");
                AddExchangeBet(playerid, BET_BIZ, bizz_id);
            }
            else if(button_id == 2)
            {
                if(p_temp[playerid][TextDrawTrade]) HideTextDrawForPlayer(playerid, TD_ID_TRADE);
                p_temp[playerid][pos_VW] = GetPlayerVirtualWorld(playerid);
                p_temp[playerid][pos_INT] = GetPlayerInterior(playerid);
                new idx = GetPlayerBizzID(playerid, slot_id);
                GetPlayerPos(playerid, p_temp[playerid][pos_X], p_temp[playerid][pos_Y], p_temp[playerid][pos_Z]);

                SetPlayerInterior(playerid,0);
                Fix_TogglePlayerControllable(playerid, false);
                SetPlayerPos(playerid,b_info[idx][b_enter][0], b_info[idx][b_enter][1], b_info[idx][b_enter][2]);

                new Float:hx, Float:hy, Float:hz, Float:ha,
                    Float:hx2, Float:hy2;
                ha = b_info[idx][b_enter][3];
                hx = b_info[idx][b_enter][0] + 1.0 * floatsin(-ha, degrees); //смещение от Х вперед!
                hy = b_info[idx][b_enter][1] + 1.0 * floatcos(-ha, degrees); //смещение от Y вперед! в сторону куда смотрим(!)
                hz = b_info[idx][b_enter][2]+0.5;

                hx2 = hx - 12.0 * floatsin(ha, degrees);
                hy2 = hy + 6.0 * floatcos(ha, degrees);

                InterpolateCameraPos(playerid,hx,hy,hz,hx2,hy2,hz+2.2, 3500);
                InterpolateCameraLookAt(playerid,hx,hy,hz, hx,hy,hz, 3500);

                SetTimerEx("fixCameraProperty", 3510, 0, "iiifff", 3, playerid, idx, hx2,hy2,hz+2.2);
            }
        }
        case EQUIPMENT_TRADE_BET_INVENTORY:
        {
            if(InventoryPlayer[playerid][slot_id][inv_mysql_id] == INVALID_MYSQL_ID) return SendError(playerid, "Ничего не найдено.");
            new itemID = InventoryPlayer[playerid][slot_id][inv_item_id];
            if(button_id == 1)
            {
                if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY)
                {
                    if(itemID == 679 && TentIDx[playerid] == 679 || itemID == 680 && TentIDx[playerid] == 680)
                        return SendError(playerid, "Для начала необходимо забрать свой переносной ларек.");
                    SetPVarInt(playerid, #EQ_SELECT_SLOT, slot_id+1);
                    ShowBetAmountInventory(playerid, itemID);
                }
                else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
                    AddExchangeBet(playerid, BET_ACCESSORIES, itemID, slot_id, .wear = InventoryPlayer[playerid][slot_id][inv_acc_wear], .mc1 = InventoryPlayer[playerid][slot_id][inv_acc_mt][0], .mc2 = InventoryPlayer[playerid][slot_id][inv_acc_mt][1], .premium = InventoryPlayer[playerid][slot_id][inv_acc_premium]);
                else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_SKINS)
                {
                    if(itemID <= 0 || itemID == 74 ||
                        itemID == 252 || itemID == 90 || itemID == 251) return SendError(playerid, "Этот скин нельзя обменять.");
                    AddExchangeBet(playerid, BET_SKIN, itemID, slot_id, .wear = InventoryPlayer[playerid][slot_id][inv_skin_wear], .premium = InventoryPlayer[playerid][slot_id][inv_skin_premium]);
                }
                else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
                {
                    AddExchangeBet(playerid, BET_VEHICLE_TUNE, itemID, slot_id);
                }
            }
            else if(button_id == 2)
            {
                STRING_GLOBAL[0] = EOS;
                if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY || ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
                {
                    f(STRING_GLOBAL, ""W"\"%s\": "I"%d ед. ;\n"W"", ItemsInfo[itemID][iName], InventoryPlayer[playerid][slot_id][inv_amount]);
                }
                else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
                {
                    f(STRING_GLOBAL, ""W""I"\"%s\": [%.1f] (%s/%s);\nPremium: "I"%s;\n"W"Гос. цена: "I"%d$",
                        ItemsInfo[itemID][iName],
                        InventoryPlayer[playerid][slot_id][inv_acc_wear],
                        AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acName],
                        AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acName],
                        InventoryPlayer[playerid][slot_id][inv_acc_premium] == 1 ? "Есть" : "Нет",
                        ItemsInfo[itemID][iPrice]);
                }
                else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_SKINS)
                {
                    f(STRING_GLOBAL, ""W"Скин "I"№%d: [%.1f];\nPremium: "I"%s;\n"W"Гос. цена: "I"%d$",
                    itemID,
                    InventoryPlayer[playerid][slot_id][inv_skin_wear],
                    InventoryPlayer[playerid][slot_id][inv_skin_premium] == 1 ? "Есть" : "Нет",
                    ItemsInfo[itemID][iPrice]);
                }
                ShowPlayerDialog(playerid, D_EXCHANGE_PREVIEW_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о предмете", STRING_GLOBAL, "Назад", "");
            }
        }
        case EQUIPMENT_TRADE_READY:
        {
            if(button_id == 1) Equipment_TradeItemInfo(playerid, p_info[playerid][exchangePartner], slot_id);
        }
    }
    return 1;
}

Equipment_TradeItemInfo(playerid, targetid, slot_id)
{
    if(slot_id >= MAX_EXCHANGE) return 1;
    if(targetid == INVALID_PLAYER_ID)
        return ExchangeFailed(playerid, "Второй игрок не в сети.");
    new idx = gExchange[targetid][slot_id][xItemID];

    p_temp[playerid][pos_X] =
    p_temp[playerid][pos_Y] =
    p_temp[playerid][pos_Z] = 0.0;

    p_temp[playerid][pos_VW] = GetPlayerVirtualWorld(playerid);
    p_temp[playerid][pos_INT] = GetPlayerInterior(playerid);
    switch(gExchange[targetid][slot_id][xType])
    {
        case INVALID_EXCHANGE: return 1;
        case BET_HOUSE:
        {
            if(p_temp[playerid][TextDrawTrade]) HideTextDrawForPlayer(playerid, TD_ID_TRADE);

            GetPlayerPos(playerid, p_temp[playerid][pos_X], p_temp[playerid][pos_Y], p_temp[playerid][pos_Z]);

            Fix_TogglePlayerControllable(playerid, false);
            SetPlayerInterior(playerid,0);
            SetPlayerVirtualWorld(playerid, playerid+1);

            SetPlayerPos(playerid,h_info[idx][h_enter][0], h_info[idx][h_enter][1], h_info[idx][h_enter][2]);

            new Float:hx, Float:hy, Float:hz, Float:ha,
                Float:hx2, Float:hy2;
            ha = h_info[idx][h_enter][3];
            hx = h_info[idx][h_enter][0] + 1.0 * floatsin(-ha, degrees); //смещение от Х вперед!
            hy = h_info[idx][h_enter][1] + 1.0 * floatcos(-ha, degrees); //смещение от Y вперед! в сторону куда смотрим(!)
            hz = h_info[idx][h_enter][2]+0.5;

            hx2 = hx-12.0 * floatsin(ha, degrees);
            hy2 = hy + 6.0 * floatcos(ha, degrees);

            InterpolateCameraPos(playerid,hx,hy,hz,hx2,hy2,hz+2.2, 3500);
            InterpolateCameraLookAt(playerid,hx,hy,hz, hx,hy,hz, 3500);

            SetTimerEx("fixCameraProperty", 3510, 0, "iiifff", 2, playerid, idx, hx2,hy2,hz+2.2);
        }
        case BET_BIZ:
        {
            if(p_temp[playerid][TextDrawTrade]) HideTextDrawForPlayer(playerid, TD_ID_TRADE);

            GetPlayerPos(playerid, p_temp[playerid][pos_X], p_temp[playerid][pos_Y], p_temp[playerid][pos_Z]);

            Fix_TogglePlayerControllable(playerid, false);
            SetPlayerInterior(playerid,0);
            SetPlayerVirtualWorld(playerid, playerid+1);

            SetPlayerPos(playerid,b_info[idx][b_enter][0], b_info[idx][b_enter][1], b_info[idx][b_enter][2]);

            new Float:hx, Float:hy, Float:hz, Float:ha,
                Float:hx2, Float:hy2;
            ha = b_info[idx][b_enter][3];
            hx = b_info[idx][b_enter][0] + 1.0 * floatsin(-ha, degrees); //смещение от Х вперед!
            hy = b_info[idx][b_enter][1] + 1.0 * floatcos(-ha, degrees); //смещение от Y вперед! в сторону куда смотрим(!)
            hz = b_info[idx][b_enter][2]+0.5;

            hx2 = hx-12.0 * floatsin(ha, degrees);
            hy2 = hy + 6.0 * floatcos(ha, degrees);

            InterpolateCameraPos(playerid,hx,hy,hz,hx2,hy2,hz+2.2, 3500);
            InterpolateCameraLookAt(playerid,hx,hy,hz, hx,hy,hz, 3500);

            SetTimerEx("fixCameraProperty", 3510, 0, "iiifff", 3, playerid, idx, hx2,hy2,hz+2.2);
        }
        case BET_CAR:
        {
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_owner_id`, `v_number`, `v_model`, `v_premium`, `v_bonus`, `v_sell_block`, `v_insurance`, `v_twinturbo_data`, `v_details` FROM `vehicle` WHERE `v_mysql_id` = %d AND `v_bonus` = 0", gExchange[targetid][slot_id][xValue]);
            mysql_tquery(con_bd, STRING_GLOBAL, "trade_info_vehicle", "i", playerid);
        }
        case BET_SKIN, BET_ACCESSORIES, BET_INVENTORY, BET_VEHICLE_TUNE:
        {
            STRING_GLOBAL[0] = EOS;
            if(ItemsInfo[idx][iType] == TYPE_ITEMS_INVENTORY || ItemsInfo[idx][iType] == BET_VEHICLE_TUNE)
                f(STRING_GLOBAL, ""W"Предмет: "I"%d ед. \"%s\";\n"W"", gExchange[targetid][slot_id][xValue], ItemsInfo[idx][iName]);
            else if(ItemsInfo[idx][iType] == TYPE_ITEMS_ACCESSORIES)
                f(STRING_GLOBAL, ""W"Аксессуар "I"%s [%.1f] (%s/%s);\n"W"Premium: "I"%s;\n"W"Гос. цена: "I"%d$", ItemsInfo[idx][iName], gExchange[targetid][slot_id][xWear], AccessoriesColorInfo[gExchange[targetid][slot_id][xMaterialColor][0]][acName], AccessoriesColorInfo[gExchange[targetid][slot_id][xMaterialColor][1]][acName], gExchange[targetid][slot_id][xPremium] == 0 ? "Нет" : "Есть", ItemsInfo[idx][iPrice]);
            else if(ItemsInfo[idx][iType] == TYPE_ITEMS_SKINS)
                f(STRING_GLOBAL, ""W"Скин "I"№%d [%.1f];\n"W"Premium: "I"%s;\n"W"Гос. цена: "I"%d$", idx, gExchange[targetid][slot_id][xWear], gExchange[targetid][slot_id][xPremium] == 0 ? "Нет" : "Есть", ItemsInfo[idx][iPrice]);
            ShowPlayerDialog(playerid, D_EXCHANGE_PREVIEW_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о предмете", STRING_GLOBAL, "Назад", "");
        }
        case BET_FAMILY:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Семья "I"%s", FamilyData[gExchange[targetid][slot_id][xItemID]][fName]);
            ShowPlayerDialog(playerid, D_EXCHANGE_PREVIEW_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация: Семья", STRING_GLOBAL, "Назад", "");
        }
        case BET_COSTUME:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Костюм "I"%s; "W"цена: "I"%d FM", CostumeName[gExchange[targetid][slot_id][xItemID]], CostumePrice[gExchange[targetid][slot_id][xItemID]]);
            ShowPlayerDialog(playerid, D_EXCHANGE_PREVIEW_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация: Костюм", STRING_GLOBAL, "Назад", "");
        }
        default: return 1;//PreviewExchange(playerid);
    }
    return 1;
}


