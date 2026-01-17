UpdatePickupInfo(const pickupid, const PICKUP_TYPE, const PICKUP_SUBTYPE, const PICKUP_OBJECT_ID)
{
    gPickupInfo[pickupid][pickup_type] = PICKUP_TYPE;
    gPickupInfo[pickupid][pickup_subtype] = PICKUP_SUBTYPE;
    gPickupInfo[pickupid][pickup_object_id] = PICKUP_OBJECT_ID;
}

OnPlayerCheckDynamicPickup(playerid, pickupid)
{
    if(pickupid == -1) return 1;
    if(!IsPlayerInRangeOfPoint(playerid, 2.5, p_temp[playerid][PickupPosX], p_temp[playerid][PickupPosY], p_temp[playerid][PickupPosZ]))
    {
        p_temp[playerid][EventPickupID] = -1;
        return 1;
    }
    new playerState = GetPlayerState(playerid);
    switch(gPickupInfo[pickupid][pickup_type])
    {
        case TYPE_BANK:
        {
            new bankId = gPickupInfo[pickupid][pickup_object_id];
            switch(gPickupInfo[pickupid][pickup_subtype])
            {
                case PICKUP_SUBTYPE_BANK_ENTER:
                {
                    SetPlayerInterior(playerid, 1);
                    SetPlayerVirtualWorld(playerid, bankId);
                    SetPlayerPos(playerid, 2290.1907,-55.2788,1070.2646);
                    SetPlayerFacingAngle(playerid, 90.8015);
                    SetCameraBehindPlayer(playerid);
                }
                case PICKUP_SUBTYPE_BANK_EXIT:
                {
                    SetPlayerInterior(playerid, 0);
                    SetPlayerVirtualWorld(playerid, 0);
                    SetPlayerPos(playerid, BankInfo[bankId][bExit][0], BankInfo[bankId][bExit][1], BankInfo[bankId][bExit][2]);
                    SetPlayerFacingAngle(playerid, BankInfo[bankId][bExit][3]);
                    SetCameraBehindPlayer(playerid);
                }
                case PICKUP_SUBTYPE_BANK_MENU:
                {
                    ShowPlayerDialog(playerid, D_BANK_MENU, DIALOG_STYLE_LIST, ""I"Банковские услуги", ""I"[1]"W" {"#cLIGHTRED"}Снять"W" или {"#cGREEN"}положить"W" деньги\n"I"[2]"W" Перевести деньги\n"I"[3]"W" Оплатить дом\n"I"[4]"W" Оплатить бизнес\n"I"[5]"W" Пополнить баланс телефона\n"I"[6]"W" Банковский вклад\n"I"[7]"W" Пенсия\n"I"[8]"W" Штрафы\n{"#cLIGHTRED"}[9] Bitcoin", "Далее", "Отмена");
                }
            }
            return 1;
        }
        case TYPE_HOUSE:
        {
            new houseId = gPickupInfo[pickupid][pickup_object_id];
            p_temp[playerid][p_house_id] = houseId;
            switch(gPickupInfo[pickupid][pickup_subtype])
            {
                case PICKUP_SUBTYPE_HOUSE_ENTER:
                {
                    if(playerState != PLAYER_STATE_ONFOOT) return 1;
                    if(GetPlayerVirtualWorld(playerid) != 0) return 1;
                    if(p_temp[playerid][Work_ID] == ROBBER_WORK &&
                        RobberIDx[playerid] != -1 && houseId == RobberIDx[playerid]) return 1;
                    if(p_info[playerid][exchangePartner] != INVALID_PLAYER_ID) return 1;

                    STRING_GLOBAL[0] = EOS;
                    if(h_info[houseId][h_user_id] != INVALID_MYSQL_ID)
                    {
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                        Владелец: %s (%s) [Класс: %s]\n\
                        "I"[1]"W" Войти в дом: (%s)\n\
                        "I"[2]"W" Войти в подвал: (%s) (%s)\n\
                        "I"[3]"W" Войти в подпольное помещение: (%s) (%s)", h_info[houseId][h_owner], GetPlayerID(h_info[houseId][h_owner]) == INVALID_PLAYER_ID ? "{"#cLIGHTRED"}Offline"W"" : "{"#cGREEN"}Online"W"", house_class[h_info[houseId][h_squar]-1], h_info[houseId][h_lock] == 0 ? "{"#cGREEN"}Открыт"W"" : "{"#cLIGHTRED"}Закрыт"W"",
                        h_info[houseId][h_improve][BASEMENT] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"", h_info[houseId][h_attic_lock] == 0 ? "{"#cGREEN"}Открыт"W"" : "{"#cLIGHTRED"}Закрыт"W"",
                        h_info[houseId][h_improve][UNDERGROUND] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"", h_info[houseId][h_underground_lock] == 0 ? "{"#cGREEN"}Открыт"W"" : "{"#cLIGHTRED"}Закрыт"W"");

                        if(h_info[houseId][h_squar] > 1)
                            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\n"I"[3]"W" Войти в гараж: (%s)", STRING_GLOBAL, h_info[houseId][h_garage_lock] == 0 ? "{"#cGREEN"}Открыт"W"" : "{"#cLIGHTRED"}Закрыт"W"");
                        return ShowPlayerDialog(playerid, D_HOUSE_DOOR,DIALOG_STYLE_LIST, ""I"Дом занят", STRING_GLOBAL, "Далее", "Отмена");
                    }
                    else
                    {
                        new idx = p_temp[playerid][rob_house_idx];
                        if(idx != -1 && RobberyHouseContract[idx][rhcHouseIDx] == houseId)
                        {
                            if(h_info[houseId][h_lock] == 0)
                            {
                                SetPlayerHousePos(playerid, houseId, h_info[houseId][h_squar]-1, h_info[houseId][h_int]);
                                return 1;
                            }
                            else return SendError(playerid, "В данном доме закрыты двери, взломайте их с помощью команды /robbing");
                        }

                        if(p_temp[playerid][p_listitem_int] == houseId) return 1;

                        new cost_house = h_info[houseId][h_value], list_percent[3] = {95, 90, 85}, vip_idx = p_info[playerid][p_vip];
                        if(vip_idx) cost_house = ((h_info[houseId][h_value] / 100) * list_percent[vip_idx - 1]);

                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
                        Номер дома: %d\n\
                        Класс дома: %s\n\
                        Стоимость дома: %d$", houseId, house_class[h_info[houseId][h_squar]-1], cost_house);

                        return ShowPlayerDialog(playerid, D_HOUSE_DOOR, DIALOG_STYLE_MSGBOX, ""I"Дом свободен", STRING_GLOBAL, "Далее", "Отмена");
                    }
                }
                case PICKUP_SUBTYPE_HOUSE_EXIT:
                {
                    if(p_temp[playerid][h_buy_int] != -1)
                        return SendError(playerid, "Вы в режиме смены интерьера. Выйдите из него, чтобы покинуть дом.");
                    if(p_temp[playerid][h_repair_txtid] != -1)
                        return SendError(playerid, "Вы в режиме ремонта дома. Выйдите из него, чтобы покинуть дом.");
                    if(GetPlayerVirtualWorld(playerid) - 50 == -1 || GetPlayerVirtualWorld(playerid) - 50 > MAX_HOUSE) return SendError(playerid, "Код ошибки: 1004 (Обратитесь к администрации)");
                    p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
                    houseId = p_temp[playerid][p_house_id];
                    if(houseId == INVALID_HOUSE_ID) return SendError(playerid, "Код ошибки: 1005 (Обратитесь к администрации)");
                    if(playerState != PLAYER_STATE_ONFOOT) return 1;
                    ShowPlayerDialog(playerid, D_HOUSE_DOOR,DIALOG_STYLE_LIST,""I"Выход из дома",""I"[1]"W" На улицу\n"I"[2]"W" В подвал\n"I"[3]"W" В подпольное помещение\n"I"[4]"W" В гараж","Выбрать","Отмена");
                    return 1;
                }
                case PICKUP_SUBTYPE_HOUSE_G_DOOR:
                {
                    if(p_temp[playerid][h_repair_txtid] != -1)
                        return SendError(playerid, "Вы в режиме ремонта гаража. Выйдите из него, чтобы покинуть гараж.");
                    if(GetPlayerVirtualWorld(playerid) - 50 == -1 || GetPlayerVirtualWorld(playerid) - 50 > MAX_HOUSE) return SendError(playerid, "Код ошибки: 1004 (Обратитесь к администрации)");
                    p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
                    houseId = p_temp[playerid][p_house_id];
                    if(houseId == INVALID_HOUSE_ID) return SendError(playerid, "Код ошибки: 1005 (Обратитесь к администрации)");
                    if(playerState == PLAYER_STATE_ONFOOT)
                        return ShowPlayerDialog(playerid, D_GARAGE_DOOR,DIALOG_STYLE_LIST,""I"Выход из гаража",""I"[1]"W" На улицу\n"I"[2]"W" В дом\n"I"[3]"W" В подвал\n"I"[4]"W" В подпольное помещение","Выбрать","Отмена");
                }
                case PICKUP_SUBTYPE_HOUSE_B_DOOR:
                {
                    if(playerState != PLAYER_STATE_ONFOOT) return 1;
                    if(GetPlayerVirtualWorld(playerid) - 50 == -1 || GetPlayerVirtualWorld(playerid) - 50 > MAX_HOUSE) return SendError(playerid, "Код ошибки: 1004 (Обратитесь к администрации)");
                    p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
                    houseId = p_temp[playerid][p_house_id];
                    if(houseId == INVALID_HOUSE_ID) return SendError(playerid, "Код ошибки: 1005 (Обратитесь к администрации)");
                    ShowPlayerDialog(playerid, D_ATTIC_DOOR,DIALOG_STYLE_LIST,""I"Выход из дома",""I"[1]"W" На улицу\n"I"[2]"W" В дом\n"I"[3]"W" Подпольное помещение\n"I"[4]"W" В гараж","Выбрать","Отмена");
                    return 1;
                }
                case PICKUP_SUBTYPE_HOUSE_U_DOOR:
                {
                    if(playerState != PLAYER_STATE_ONFOOT) return 1;
                    if(GetPlayerVirtualWorld(playerid) - 50 == -1 || GetPlayerVirtualWorld(playerid) - 50 > MAX_HOUSE) return SendError(playerid, "Код ошибки: 1004 (Обратитесь к администрации)");
                    p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
                    houseId = p_temp[playerid][p_house_id];
                    if(houseId == INVALID_HOUSE_ID) return SendError(playerid, "Код ошибки: 1005 (Обратитесь к администрации)");
                    ShowPlayerDialog(playerid, D_ATTIC_DOOR,DIALOG_STYLE_LIST,""I"Выход из дома",""I"[1]"W" На улицу\n"I"[2]"W" В дом\n"I"[3]"W" Подвал\n"I"[4]"W" В гараж","Выбрать","Отмена");
                    return 1;
                }
                case PICKUP_SUBTYPE_HOUSE_BASEMENT:
                {
                    if(GetPlayerVirtualWorld(playerid) - 50 == -1 || GetPlayerVirtualWorld(playerid) - 50 > MAX_HOUSE) return SendError(playerid, "Код ошибки: 1004 (Обратитесь к администрации)");
                    new houseId = p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
                    if(houseId == INVALID_HOUSE_ID)
                        return SendError(playerid, "Код ошибки: 1010 (Обратитесь к администрации)");
                    if(h_info[houseId][h_user_id] != p_info[playerid][ID])
                        return SendError(playerid, "Вы не владелец дома.");
                    if(houseId+50 != GetPlayerVirtualWorld(playerid))
                        return SendError(playerid, "Пользоваться крафт-станком дома можно только находясь в нём.");
                    if(h_info[houseId][h_improve][BASEMENT] == 0) return 1;
                    if(p_info[playerid][key_h_rent] != -1 && (p_info[playerid][h_r_settings][R_BASEMENT] == 0 || p_info[playerid][key_h_rent]+50 != GetPlayerVirtualWorld(playerid))) return SendError(playerid, "Вы не можете пользоваться этой командой.");
                    ShowTextDrawForPlayer(playerid, TD_ID_CRAFT);
                    return 1;
                }
                case PICKUP_SUBTYPE_HOUSE_VC_ALL:
                {
                    ShowVideoCards(playerid, VIDEO_CARDS_TYPE_ALL);
                }
                case PICKUP_SUBTYPE_HOUSE_VC_ONE, PICKUP_SUBTYPE_HOUSE_VC_TWO, PICKUP_SUBTYPE_HOUSE_VC_THREE, PICKUP_SUBTYPE_HOUSE_VC_FOUR, PICKUP_SUBTYPE_HOUSE_VC_FIVE:
                {
                    new i = gPickupInfo[pickupid][pickup_subtype] - 8;
                    ShowVideoCards(playerid, VIDEO_CARDS_TYPE_RACK, i);
                    return 1;
                }
                case PICKUP_SUBTYPE_HOUSE_U_ALL:
                {
                    ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_ALL);
                }
                case PICKUP_SUBTYPE_HOUSE_U_ONE, PICKUP_SUBTYPE_HOUSE_U_TWO, PICKUP_SUBTYPE_HOUSE_U_THREE, PICKUP_SUBTYPE_HOUSE_U_FOUR, PICKUP_SUBTYPE_HOUSE_U_FIVE, PICKUP_SUBTYPE_HOUSE_U_SIX, PICKUP_SUBTYPE_HOUSE_U_SEVEN, PICKUP_SUBTYPE_HOUSE_U_EIGHT, PICKUP_SUBTYPE_HOUSE_U_NINE, PICKUP_SUBTYPE_HOUSE_U_TEN:
                {
                    new i = gPickupInfo[pickupid][pickup_subtype] - 14;
                    ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_ACTOR, i);
                    return 1;
                }
            }
        }
        case TYPE_BUSINESS:
        {
            new businessId = gPickupInfo[pickupid][pickup_object_id];
            if(playerState != PLAYER_STATE_ONFOOT && b_info[businessId][_tip] != B_CAR_SERVICE) return 1;
            p_temp[playerid][p_biz_id] = businessId;
            switch(gPickupInfo[pickupid][pickup_subtype])
            {
                case PICKUP_SUBTYPE_BUSINESS_ENTER:
                {
                    if(playerState != PLAYER_STATE_ONFOOT && b_info[businessId][_tip] != B_CAR_SERVICE) return 1;
                    if(GetPlayerVirtualWorld(playerid) != 0) return 1;
                    if(p_info[playerid][exchangePartner] != INVALID_PLAYER_ID) return 1;
                    if(b_info[businessId][b_user_id] == INVALID_MYSQL_ID)
                    {
                        if(p_temp[playerid][p_listitem_int] == businessId) return 1;
                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL,sizeof(STRING_GLOBAL), ""W"Стоимость: %d$\n\nЕсли Вы действительно желаете приобрести данный бизнес, нажмите \"Далее\", а если нет, нажмите \"Войти\".", b_info[businessId][_price]);
                        return ShowPlayerDialog(playerid, 36, DIALOG_STYLE_MSGBOX, ""I"Покупка бизнеса", STRING_GLOBAL, "Далее", "Войти");
                    }
                    SetPVarInt(playerid, "bID", businessId);
                    switch(b_info[businessId][_tip])
                    {
                        case B_FUEL, B_CAR_SERVICE, B_FOOD_STALL, B_POWER_STATION, B_TUNING, B_TANK_FARM, B_OIL_RIG, B_CAR_SHOWROOM, B_ARENDS_VEHICLE: return 1;
                    }

                    if(b_info[businessId][_enter] != 0 && p_info[playerid][level] > 3)
                    {
                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Стоимость входа: %d$\n\nЕсли Вы действительно желаете войти в данный бизнес, нажмите \"Далее\", а если нет, нажмите \"Отмена\".", b_info[businessId][_enter]);
                        ShowPlayerDialog(playerid, D_ENTER_BIZ, DIALOG_STYLE_MSGBOX, ""I"Вход в бизнес", STRING_GLOBAL, "Далее", "Отмена");
                    }
                    else
                    {
                        if(b_info[businessId][_tip] == B_BAR) SendInfo(playerid, "Чтобы играть в кости используйте /dice");

                        SetPlayerPos(playerid, b_info[businessId][b_exit][0],b_info[businessId][b_exit][1],b_info[businessId][b_exit][2]);
                        SetPlayerInterior(playerid, b_info[businessId][_int]), SetPlayerVirtualWorld(playerid, b_info[businessId][_world]);
                        SetCameraBehindPlayer(playerid);
                    }
                    return 1;
                }
                case PICKUP_SUBTYPE_BUSINESS_EXIT:
                {
                    if(b_info[businessId][_tip] == B_SHOP)
                    {
                        SetPlayerSkinEx(playerid);
                        p_temp[playerid][shop_id] = 0;
                    }
                    else if(b_info[businessId][_tip] == B_ACCESSORIES)
                    {
                        if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
                            RemovePlayerAttachedObject(playerid, 0);
                        AttachToPlayerAccOrCostume(playerid, INVALID_PLAYER_ID);
                        p_temp[playerid][shop_id] = 0;
                        DeletePVar(playerid,"SelectAccessoriesType");
                    }
                    else if(b_info[businessId][_tip] == B_GYM)
                    {
                        if(GetPVarInt(playerid, "GymTrainingStyde")) LeaveFromGym(playerid);
                        new sparring_id = p_temp[playerid][SparringID];
                        if(sparring_id != -1)
                        {
                            if(SparringData[sparring_id][sRound] == 0) CancelSparring(sparring_id);
                            else EndSparring(sparring_id, false);
                        }
                    }
                    new businessId = GetPVarInt(playerid, "bID");
                    SetPlayerPos(playerid, b_info[businessId][b_enter][0], b_info[businessId][b_enter][1], b_info[businessId][b_enter][2]);
                    SetPlayerFacingAngle(playerid, b_info[businessId][b_enter][3]);
                    SetPlayerInterior(playerid, 0);
                    SetPlayerVirtualWorld(playerid, 0);
                    return 1;
                }
                case PICKUP_SUBTYPE_BUSINESS_HOTEL:
                {
                    for(new idx_rooms; idx_rooms < MAX_HOTEL_ROOMS; idx_rooms++)
                    {
                        if(pickupid == hotel_rooms_info[businessId][idx_rooms][hr_pickup])
                        {
                            SetPVarInt(playerid, "hrID", idx_rooms);
                            if(hotel_rooms_info[businessId][idx_rooms][hr_user_id] == 0)
                            {
                                STRING_GLOBAL[0] = EOS;
                                f(STRING_GLOBAL, ""W"Владелец: Нет\nНомер: %d", idx_rooms);
                                ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Номер свободен", STRING_GLOBAL, "Отмена", "");
                            }
                            else
                            {
                                STRING_GLOBAL[0] = EOS;
                                f(STRING_GLOBAL, ""W"Владелец: %s\nНомер: %d", hotel_rooms_info[businessId][idx_rooms][hr_owner], idx_rooms);
                                ShowPlayerDialog(playerid, D_HOTEL_ROOMS_ENTER, DIALOG_STYLE_MSGBOX, ""I"Номер занят", STRING_GLOBAL, "Далее", "Отмена");
                            }
                            break;
                        }
                    }
                    return 1;
                }
                case PICKUP_SUBTYPE_BUSINESS_ROOM:
                {
                    new biz_id = GetPVarInt(playerid, "bID"), room_id = GetPVarInt(playerid, "hrID");
                    SetPlayerPos(playerid, hotel_rooms_pos[room_id][0], hotel_rooms_pos[room_id][1], hotel_rooms_pos[room_id][2]);
                    SetPlayerFacingAngle(playerid, hotel_rooms_pos[room_id][3]);
                    SetPlayerInterior(playerid, b_info[biz_id][_int]);
                    SetPlayerVirtualWorld(playerid, b_info[biz_id][_world]);
                }
            }
        }
        case TYPE_WORK_DRESSING:
        {
            new id = gPickupInfo[pickupid][pickup_object_id];

            if(GetFactionType(id) == FACTION_TYPE_GOS || GetFactionType(id) == FACTION_TYPE_SNN)
            {
                if(GetPlayerVirtualWorld(playerid) != FractionsData[id][fBaseField][fVirtualWorld]) return 1;
                if(id != p_info[playerid][member]) return 1;
                if(GetFactionCategory(id) == FACTION_CATEGORY_ARMY && (p_info[playerid][rang] < 3) && p_info[playerid][fwork] == true)
                    return 1;

                if(p_info[playerid][fwork] == true)
                {
                    if(p_info[playerid][member] == NATIONAL_GUARD && p_info[playerid][rang] == 1) return 1;

                    p_info[playerid][fwork] = false;
                    SetPlayerSkinEx(playerid);
                    SetPlayerColor(playerid, fraction_color[0]);
                    if(GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_PD || GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_FBI)
                        p_temp[playerid][StatusOnDuty] = 0;
                }
                else
                {
                    p_info[playerid][fwork] = true;
                    SetPlayerSkin(playerid, p_info[playerid][fskin]);
                    SetPlayerColor(playerid,  fraction_color[p_info[playerid][member]]);
                    if(GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_PD || GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_FBI)
                        p_temp[playerid][StatusOnDuty] = 1;
                }
                MysqlUpdatePlayerInt(playerid, "fwork", _:p_info[playerid][fwork]);
            }
            else
            {
                if(GetPlayerVirtualWorld(playerid) != FractionsData[id][fBaseField][fVirtualWorld]) return 1;
                if(id != p_info[playerid][member]) return 1;
                if(!GetFractionSettings(id, fDressingStatus) && p_info[playerid][rang] != 10) return SendError(playerid, "Лидер закрыл склад одежды.");
                p_temp[playerid][p_listitem_int] = playerid;
                ShowPlayerListTD(playerid, LIST_TD_ID_FRACTION_CHANGE_SKIN);
            }
            return 1;
        }
        case TYPE_MARKET:
        {
            if(SRV_ID && 1 <= p_info[playerid][admin] <= 9) return SendError(playerid, "Вы администратор, действие невозможно.");
            new id = gPickupInfo[pickupid][pickup_object_id];
            if(MarketInfo[id][mOwnerID] == INVALID_PLAYER_ID)
            {
                if(p_info[playerid][level] < 3) return SendError(playerid, "Арендовать палатку можно с 3 уровня.");
                if(p_temp[playerid][market_arend] != -1) return SendError(playerid, "У Вас уже есть арендованная палатка.");
                if(p_info[playerid][exchangePartner] != INVALID_PLAYER_ID) return SendError(playerid, "У Вас не законченный трейд.");
                ShowFreeMarket(playerid, id);
                p_temp[playerid][market_buy_idx] = id;
            }
            else
            {
                if(p_temp[playerid][market_arend] != -1 && p_temp[playerid][market_arend] == id) ShowPlayerControlMarket(playerid);
                else
                {
                    for(new i = MAX_MARKET_PLAYER_USE-1; i != -1; i--)
                    {
                        if(MarketInfo[id][mPlayerUse][i] == INVALID_PLAYER_ID)
                        {
                            MarketInfo[id][mPlayerUse][i] = playerid;
                            p_temp[playerid][market_buy_idx] = id;
                            break;
                        }
                    }
                    if(p_temp[playerid][market_buy_idx] == id) ShowPlayerDialog(playerid, D_MARKET_MENU, DIALOG_STYLE_LIST, ""I"Палатка", ""I"[1]"W" Список продаваемого товара\n"I"[2]"W" Список покупаемого товара", "Далее", "Отмена");
                    else SendError(playerid, "В палатке нет места, дождитесь ухода других покупателей.");
                }
            }
            return 1;
        }
        case TYPE_FRACTION_VEHICLE_SPAWN:
        {
            new frac_id = gPickupInfo[pickupid][pickup_object_id];
            if(p_info[playerid][member] != frac_id)
                return 1;
            STRING_GLOBAL = "#\tМодель/Ранг\tДоступных/Всего\n";
            for(new i; i < MAX_FRACTIONS_VEHICLES; i++)
            {
                if(FractionsData[frac_id][fVehModelsID][i] == 0) break;
                f(STRING_GLOBAL, "%s"I"[%d]"W"\t%s(%d)\t%d/%d\n", STRING_GLOBAL, i+1,
                    GetVehicleName(INVALID_VEHICLE_ID, FractionsData[frac_id][fVehModelsID][i]), FractionsData[frac_id][fVehAccessRank][i],
                    (FractionsData[frac_id][fVehModelMaxCount][i]-FractionsData[frac_id][fVehModelUseCount][i]),
                    FractionsData[frac_id][fVehModelMaxCount][i]);
            }
            STRING_MIN[0] = EOS;
            f(STRING_MIN, "Автомобили фракции: "I"%s", FractionsData[frac_id][fName]);
            ShowPlayerDialog(playerid, D_FRACTION_VEHICLE_SPAWN, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Выбрать", "Отмена");
        }
        case TYPE_ARENDS_VEHICLE:
        {
            if(playerState != PLAYER_STATE_ONFOOT) return 1;
            new bizz_id = 116+GetPlayerPositionCity(playerid)-1, count;
            STRING_GLOBAL = ""W"[#] Транспорт\t"W"Цена\t"W"Доступно/Всего\n";
            for(new i, j = sizeof(ArendsVehicleIDs); i < j; i++)
            {
                if(b_info[bizz_id][b_upgrade_class] < GetVehicleData(ArendsVehicleIDs[i], E_VD_CLASS)) 
                    break;
                if(ArendsVehicleMaxCount[bizz_id-116][i] == 0 || ArendsVehicleIDs[i] == 0) continue;

                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d$\t%d/%d\n", STRING_GLOBAL, count+1, 
                    GetVehicleName(INVALID_VEHICLE_ID, ArendsVehicleIDs[i]), 
                    (2500 * (GetVehicleData(ArendsVehicleIDs[i], E_VD_CLASS) + 1)),
                    ArendsVehicleMaxCount[bizz_id-116][i]-ArendsVehicleUseCount[bizz_id-116][i],
                    ArendsVehicleMaxCount[bizz_id-116][i]);

                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_AREND_VEHICLE_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Аренда транспорта", STRING_GLOBAL, "Да", "Нет");
            SetPVarInt(playerid, #AREND_VEH_ID, gPickupInfo[pickupid][pickup_object_id]+1);
            return 1;
        }
    }
    return 1;
}

