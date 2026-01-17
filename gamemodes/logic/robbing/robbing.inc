ClearRobbingMiniGame(playerid)
{
    p_temp[playerid][robbing_mini_game_type] = ROBBING_TYPE_NONE;
    p_temp[playerid][robbing_mini_game_sub_type] = 0;
    p_temp[playerid][robbing_mini_game_timer] = 0;
    p_temp[playerid][robbing_mini_game_check] = 0;
    p_temp[playerid][robbing_mini_game_button] = 0;
    p_temp[playerid][robbing_mini_game_error] = 0;
    p_temp[playerid][robbing_mini_game_idx] = 0;
    return 1;
}

StartRobbingMiniGame(playerid, type, sub_type, time, idx = -1)
{
    p_temp[playerid][robbing_mini_game_type] = type;
    p_temp[playerid][robbing_mini_game_sub_type] = sub_type;
    p_temp[playerid][robbing_mini_game_timer] = time;
    p_temp[playerid][robbing_mini_game_check] = 10;
    p_temp[playerid][robbing_mini_game_button] = random(4);
    p_temp[playerid][robbing_mini_game_idx] = idx;
    ShowTextDrawForPlayer(playerid, TD_ID_ROBBING);
    return 1;
}

SuccessRobbingMiniGame(playerid)
{
    STRING_GLOBAL[0] = EOS;
    switch(p_temp[playerid][robbing_mini_game_type])
    {
        case ROBBING_TYPE_HOUSE:
        {
            new idx = p_temp[playerid][rob_house_idx], houseid = RobberyHouseContract[idx][rhcHouseIDx];
            switch(p_temp[playerid][robbing_mini_game_sub_type])
            {
                case ROB_HOUSE_ITEMS_ELECTRO_JAMMER:
                {
                    h_info[houseid][h_rob_house_block] = 1;
                    SendAccess(playerid, "Вы заглушили сигнал.");
                    SendInfo(playerid, "Теперь при взломе двери не сработает сигнализация.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] заглушил(-а) сигнал.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_MASTER_KEY:
                {
                    CallingPoliceToRobberyHouse(idx, houseid);
                    h_info[houseid][h_lock] = 0;
                    SendAccess(playerid, "Вы взломали дверь.");
                    new scdplayerid;
                    for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
                    {
                        scdplayerid = RobberyHouseContract[idx][rhcPlayerID][i];
                        if(scdplayerid != INVALID_PLAYER_ID)
                        {
                            SendInfo(scdplayerid, "Началось ограбление дома.");
                            SendInfo(scdplayerid, "Заходите в дом и вынесите как можно больше объектов интерьера.");
                            SendInfo(scdplayerid, "В любой момент можно скрыться, дабы обезопасить себя и награбленное.");
                            CheckPlayerMission(scdplayerid, DAILY_ROBBING);
                            CheckPlayerMission(scdplayerid, ACHIEVEMENT_ROBBING);
                        }
                    }
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] взломал(-а) дверь.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_SCRAP:
                {
                    CallingPoliceToRobberyHouse(idx, houseid);
                    h_info[houseid][h_lock] = 0;
                    SendAccess(playerid, "Вы взломали дверь.");
                    new scdplayerid;
                    for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
                    {
                        scdplayerid = RobberyHouseContract[idx][rhcPlayerID][i];
                        if(scdplayerid != INVALID_PLAYER_ID)
                        {
                            SendInfo(scdplayerid, "Началось ограбление дома.");
                            SendInfo(scdplayerid, "Заходите в дом и вынесите как можно больше объектов интерьера.");
                            SendInfo(scdplayerid, "В любой момент можно скрыться, дабы обезопасить себя и награбленное.");
                            CheckPlayerMission(scdplayerid, DAILY_ROBBING);
                            CheckPlayerMission(scdplayerid, ACHIEVEMENT_ROBBING);
                        }
                    }
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] взломал(-а) дверь.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_TOOLS:
                {
                    if(RobberyHouseContract[idx][rhcSafe] == INVALID_OBJECT_ID) return SendError(playerid, "Сейф уже взломан.");
                    if(RobberyHouseContract[idx][rhcSafe] != INVALID_OBJECT_ID)
                    {
                        DestroyDynamicObject(RobberyHouseContract[idx][rhcSafe]);
                        RobberyHouseContract[idx][rhcSafe] = INVALID_OBJECT_ID;
                    }
                    new money = RobberyHouseContract[idx][rhcPrice] * 2, new_money = RandomEx(money / 2, money);
                    RobberyHouseContract[idx][rhcKush] += new_money;
                    new temp_rob_kush = RobberyHouseContract[idx][rhcKush];
                    SendAccess(playerid, "Вы взломали сейф с %d$. Общий куш: %d$.", new_money, temp_rob_kush);
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] взломал(-а) сейф с %d$. Общий куш: %d$.", get_name(playerid), playerid, new_money, temp_rob_kush);
                }
                case ROB_HOUSE_ITEMS_OBJECT:
                {
                    new i = p_temp[playerid][robbing_mini_game_idx];
                    HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
                    if(RobberyHouseContract[idx][rhcObject][i] == INVALID_OBJECT_ID || RobberyHouseContract[idx][rhcArea][i] == -1) return SendError(playerid, "Данного предмета уже нет.");
                    if(SetFreeRobHouseObject(playerid, idx, i) == -1) return SendError(playerid, "В Вашей сумке нет места.");
                    if(RobberyHouseContract[idx][rhcObject][i] != INVALID_OBJECT_ID)
                    {
                        DestroyDynamicObject(RobberyHouseContract[idx][rhcObject][i]);
                        RobberyHouseContract[idx][rhcObject][i] = INVALID_OBJECT_ID;
                    }
                    if(RobberyHouseContract[idx][rhcArea][i] != -1)
                    {
                        DestroyDynamicArea(RobberyHouseContract[idx][rhcArea][i]);
                        RobberyHouseContract[idx][rhcArea][i] = -1;
                    }
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] положил(-а) \"%s\" в сумку.", get_name(playerid), playerid, RobberyHouseItems[i][rhiName]);
                }
            }
            SendRobberyHouseMessage(idx, 0xDEB887FF, STRING_GLOBAL);
            HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
        }
        case ROBBING_TYPE_BANK:
        {
            new idx = p_temp[playerid][rob_bank_idx], bankid = RobberyBankContract[idx][rbcBankIDx];
            switch(p_temp[playerid][robbing_mini_game_sub_type])
            {
                case ROB_BANK_ITEMS_EXPLODE:
                {
                    if(BankInfo[bankid][bDoor] != INVALID_OBJECT_ID)
                    {
                        DestroyDynamicObject(BankInfo[bankid][bDoor]);
                        BankInfo[bankid][bDoor] = INVALID_OBJECT_ID;
                    }
                    SendAccess(playerid, "Вы взломали дверь в хранилище взрывчаткой.");
                    new scdplayerid;
                    for(new i = 0; i < MAX_ROBBERY_BANK_PLAYER; i++)
                    {
                        scdplayerid = RobberyBankContract[idx][rbcPlayerID][i];
                        if(scdplayerid != INVALID_PLAYER_ID)
                        {
                            p_temp[scdplayerid][rob_bank_timer] = 1;
                            p_temp[scdplayerid][rob_bank_timer_max] = 600;
                            SendInfo(scdplayerid, "Началось ограбление хранилища. У Вас есть 10 минут.");
                            SendInfo(scdplayerid, "Заходите в хранилище и ждите заполнения сумки.");
                            SendInfo(scdplayerid, "В любой момент можно скрыться, дабы обезопасить себя и награбленное.");
                            CheckPlayerMission(scdplayerid, DAILY_ROBBING);
                            CheckPlayerMission(scdplayerid, ACHIEVEMENT_ROBBING);
                        }
                    }
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] взломал(-а) дверь в хранилище взрывчаткой.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_GAS:
                {
                    RobberyBankContract[idx][rbcAnticall][ROB_BANK_ANTICALL_GAS] = 1;
                    SendAccess(playerid, "Вы разбросали слезоточивый газ.");
                    SendInfo(playerid, "Посетители банка теперь не смогут вызвать сотрудников полицейского департамента.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] разбросал(-а) слезоточивый газ.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_NUMBER:
                {
                    RobberyBankContract[idx][rbcSecrecy][ROB_BANK_SECRECY_NUMBER] = 1;
                    SendAccess(playerid, "Вы установили перебитые номера.");
                    SendInfo(playerid, "Сотрудники полицейского департамента теперь не смогут определить арендатора транспортного средства.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) перебитые номера.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_METAL:
                {
                    RobberyBankContract[idx][rbcSecrecy][ROB_BANK_SECRECY_METAL] = 1;
                    SendAccess(playerid, "Вы установили металлодетектор.");
                    SendInfo(playerid, "Взрывчатка с краской теперь не сработает и все накраденное можно сдать без потерь.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) металлодетектор.", get_name(playerid), playerid);
                    RobberyBankContract[idx][rbcMetalUse] = 0;
                }
                case ROB_BANK_ITEMS_WT:
                {
                    RobberyBankContract[idx][rbcAnticall][ROB_BANK_ANTICALL_WT] = 1;
                    SendAccess(playerid, "Вы установили рацию.");
                    SendInfo(playerid, "Сотрудникам полицейского департамента теперь не будет отправлено сообщение об ограблении банка.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) рацию.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_BLOOD:
                {
                    RobberyBankContract[idx][rbcSecrecy][ROB_BANK_SECRECY_BLOOD] = 1;
                    SendAccess(playerid, "Вы разлили кровь.");
                    SendInfo(playerid, "Сотрудникам полицейского департамента теперь будет сложно выйти на след грабителей.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] разлил(-а) кровь.", get_name(playerid), playerid);
                }
            }
            SendRobberyBankMessage(idx, 0xDEB887FF, STRING_GLOBAL);
            HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
        }
        case ROBBING_TYPE_FUEL:
        {
            new idx = p_temp[playerid][rob_fuel_idx];
            switch(p_temp[playerid][robbing_mini_game_sub_type])
            {
                case ROB_FUEL_ITEMS_ELECTRO_JAMMER:
                {
                    RobberyFuelContract[idx][rfcAnticall] = 1;
                    SendAccess(playerid, "Вы установили электронную глушилку.");
                    SendInfo(playerid, "Сотрудникам полицейского департамента теперь не будет отправлено сообщение об ограблении АЗС.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) электронную глушилку.", get_name(playerid), playerid);
                }
                case ROB_FUEL_ITEMS_NUMBER:
                {
                    RobberyFuelContract[idx][rfcSecrecy] = 1;
                    SendAccess(playerid, "Вы установили перебитые номера.");
                    SendInfo(playerid, "Сотрудники полицейского департамента теперь не смогут определить арендатора транспортного средства.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) перебитые номера.", get_name(playerid), playerid);
                }
                case ROB_FUEL_ITEMS_PUMP:
                {
                    SendAccess(playerid, "Вы установили насос.");
                    SendInfo(playerid, "Для работоспособности насоса необходимо установить шланг.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) насос.", get_name(playerid), playerid);
                }
                case ROB_FUEL_ITEMS_HOSE:
                {
                    SendAccess(playerid, "Вы установили шланг.");
                    SendInfo(playerid, "С помощью шланга теперь можно сливать топливо с АЗС.");
                    new scdplayerid;
                    for(new i = 0; i < MAX_ROBBERY_FUEL_PLAYER; i++)
                    {
                        scdplayerid = RobberyFuelContract[idx][rfcPlayerID][i];
                        if(scdplayerid != INVALID_PLAYER_ID)
                        {
                            p_temp[scdplayerid][rob_fuel_timer] = 1;
                            p_temp[scdplayerid][rob_fuel_timer_max] = 600;
                            SendInfo(scdplayerid, "Началось ограбление АЗС. У Вас есть 10 минут.");
                            SendInfo(scdplayerid, "Оставайтесь возле АЗС и заполняйте канистры.");
                            SendInfo(scdplayerid, "В любой момент можно скрыться, дабы обезопасить себя и награбленное.");
                            CheckPlayerMission(scdplayerid, DAILY_ROBBING);
                            CheckPlayerMission(scdplayerid, ACHIEVEMENT_ROBBING);
                        }
                    }
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] установил(-а) шланг.", get_name(playerid), playerid);
                }
            }
            SendRobberyFuelMessage(idx, 0xDEB887FF, STRING_GLOBAL);
            HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
        }
    }
    return 1;
}

FailedRobbingMiniGame(playerid)
{
    STRING_GLOBAL[0] = EOS;
    switch(p_temp[playerid][robbing_mini_game_type])
    {
        case ROBBING_TYPE_HOUSE:
        {
            new idx = p_temp[playerid][rob_house_idx], houseid = RobberyHouseContract[idx][rhcHouseIDx];
            switch(p_temp[playerid][robbing_mini_game_sub_type])
            {
                case ROB_HOUSE_ITEMS_ELECTRO_JAMMER:
                {
                    CallingPoliceToRobberyHouse(idx, houseid);
                    SendInfo(playerid, "Вы не смогли заглушить сигнал.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) заглушить сигнал.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_MASTER_KEY:
                {
                    CallingPoliceToRobberyHouse(idx, houseid);
                    RobberyHouseContract[idx][rhcItemsStart][3] = 1;
                    SendInfo(playerid, "Вы не смогли взломать дверь.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) взломать дверь.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_SCRAP:
                {
                    CallingPoliceToRobberyHouse(idx, houseid);
                    RobberyHouseContract[idx][rhcItemsStart][4] = 1;
                    SendAccess(playerid, "Вы не смогли взломать дверь.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) взломать дверь.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_TOOLS:
                {
                    CallingPoliceToRobberyHouse(idx, houseid);
                    SendInfo(playerid, "Вы не смогли взломать сейф.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) взломать сейф.", get_name(playerid), playerid);
                }
                case ROB_HOUSE_ITEMS_OBJECT:
                {
                    new i = p_temp[playerid][robbing_mini_game_idx];
                    SendInfo(playerid, "Вы не смогли взять \"%s\".", RobberyHouseItems[i][rhiName]);
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) взять \"%s\".", get_name(playerid), playerid, RobberyHouseItems[i][rhiName]);
                }
            }
            SendRobberyHouseMessage(idx, 0xDEB887FF, STRING_GLOBAL);
            HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
        }
        case ROBBING_TYPE_BANK:
        {
            new idx = p_temp[playerid][rob_bank_idx], bankid = RobberyBankContract[idx][rbcBankIDx];
            switch(p_temp[playerid][robbing_mini_game_sub_type])
            {
                case ROB_BANK_ITEMS_EXPLODE:
                {
                    CallingPoliceToRobberyBank(idx, bankid);
                    RobberyBankContract[idx][rbcItemsStart][2] = 1;
                    SendInfo(playerid, "Вы не смогли взломать дверь в хранилище взрывчаткой.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) взломать дверь в хранилище взрывчаткой.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_GAS:
                {
                    SendInfo(playerid, "Вы не смогли разбросать слезоточивый газ.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) разбросать слезоточивый газ.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_NUMBER:
                {
                    SendInfo(playerid, "Вы не смогли установить перебитые номера.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить перебитые номера.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_METAL:
                {
                    SendInfo(playerid, "Вы не смогли установить металлодетектор.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить металлодетектор.", get_name(playerid), playerid);
                    RobberyBankContract[idx][rbcMetalUse] = 0;
                }
                case ROB_BANK_ITEMS_WT:
                {
                    CallingPoliceToRobberyBank(idx, bankid);
                    SendInfo(playerid, "Вы не смогли установить рацию.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить рацию.", get_name(playerid), playerid);
                }
                case ROB_BANK_ITEMS_BLOOD:
                {
                    SendInfo(playerid, "Вы не смогли разлить кровь.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) разлить кровь.", get_name(playerid), playerid);
                }
            }
            SendRobberyBankMessage(idx, 0xDEB887FF, STRING_GLOBAL);
            HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
        }
        case ROBBING_TYPE_FUEL:
        {
            new idx = p_temp[playerid][rob_fuel_idx], fuelid = RobberyFuelContract[idx][rfcFuelIDx];
            switch(p_temp[playerid][robbing_mini_game_sub_type])
            {
                case ROB_FUEL_ITEMS_ELECTRO_JAMMER:
                {
                    CallingPoliceToRobberyFuel(idx, fuelid);
                    SendInfo(playerid, "Вы не смогли установить электронную глушилку.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить электронную глушилку.", get_name(playerid), playerid);
                }
                case ROB_FUEL_ITEMS_NUMBER:
                {
                    SendInfo(playerid, "Вы не смогли установить перебитые номера.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить перебитые номера.", get_name(playerid), playerid);
                }
                case ROB_FUEL_ITEMS_PUMP:
                {
                    CallingPoliceToRobberyFuel(idx, fuelid);
                    RobberyFuelContract[idx][rfcItemsStart][7] = 1;
                    SendInfo(playerid, "Вы не смогли установить насос.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить насос.", get_name(playerid), playerid);
                }
                case ROB_FUEL_ITEMS_HOSE:
                {
                    RobberyFuelContract[idx][rfcItemsStart][8] = 1;
                    SendInfo(playerid, "Вы не смогли установить шланг.");
                    f(STRING_GLOBAL, "[ROBBERY] %s [%d] не смог(-ла) установить шланг.", get_name(playerid), playerid);
                }
            }
            SendRobberyFuelMessage(idx, 0xDEB887FF, STRING_GLOBAL);
            HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
        }
    }
    return 1;
}

Robbing_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(p_temp[playerid][TextDrawRobberyRobbing] == false) return 1;

    if(playertextid == PTD_Robbing[playerid][1]) // Закрыть;
    {
        FailedRobbingMiniGame(playerid);
        return 1;
    }

    for(new i = 6; i < 10; i++)
    {
        if(playertextid == PTD_Robbing[playerid][i])
        {
            if(p_temp[playerid][robbing_mini_game_button] == i - 6)
            {
                p_temp[playerid][robbing_mini_game_check] = 5;
                p_temp[playerid][robbing_mini_game_button] = random(4);

                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "HA„M…ЏE:_%s", robbing_mini_game[p_temp[playerid][robbing_mini_game_button]]);
                PlayerTextDrawSetString(playerid, PTD_Robbing[playerid][4], STRING_GLOBAL);
            }
            else
            {
                p_temp[playerid][robbing_mini_game_error]++;
                SendError(playerid, "Неверная клавиша. Ошибок: %d из %d.", p_temp[playerid][robbing_mini_game_error], MAX_ROBBING_MINI_GAME_ERROR);
                if(p_temp[playerid][robbing_mini_game_error] == MAX_ROBBING_MINI_GAME_ERROR)
                {
                    SendError(playerid, "Вы допустили максимальное количество ошибок, попробуйте заново.");
                    HideTextDrawForPlayer(playerid, TD_ID_ROBBING);
                }
            }
            return 1;
        }
    }
    return 1;
}

CMD:robbing(playerid, params[])
{
    if(p_temp[playerid][rob_house_idx] != -1) return ShowRobberyHouse(playerid, ROBBERY_HOUSE_MENU);
    if(p_temp[playerid][rob_bank_idx] != -1) return ShowRobberyBank(playerid, ROBBERY_BANK_MENU);
    if(p_temp[playerid][rob_fuel_idx] != -1) return ShowRobberyFuel(playerid, ROBBERY_FUEL_MENU);
    SendError(playerid, "Вы не участвуете в ограблении дома, банка или АЗС.");
    return 1;
}

CMD:robbing_stats(playerid, params[])
{
	if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;

    RobbingInfoForMoney[6] = 0;
    RobbingInfoForMoney[7] = 0;
    RobbingInfoForMoney[6] = (RobbingInfoForMoney[0] + RobbingInfoForMoney[2] + RobbingInfoForMoney[4]);
    RobbingInfoForMoney[7] = (RobbingInfoForMoney[1] + RobbingInfoForMoney[3] + RobbingInfoForMoney[5]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
    [#] Наименование\tПараметр\n\
    "I"[1]"W" Ушло денежных средств всего:\t%d$\n\
    "I"[2]"W" Пришло денежных средств всего:\t%d$\n\
    "I"[3]"W" Ушло денежных средств в домах:\t%d$\n\
    "I"[4]"W" Пришло денежных средств в домах:\t%d$\n\
    "I"[5]"W" Ушло денежных средств в банках:\t%d$\n\
    "I"[6]"W" Пришло денежных средств в банках:\t%d$\n\
    "I"[7]"W" Ушло денежных средств в азс:\t%d$\n\
    "I"[8]"W" Пришло денежных средств в азс:\t%d$",
    RobbingInfoForMoney[6], RobbingInfoForMoney[7],
    RobbingInfoForMoney[0], RobbingInfoForMoney[1],
    RobbingInfoForMoney[2], RobbingInfoForMoney[3],
    RobbingInfoForMoney[4], RobbingInfoForMoney[5]);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Статистика денежных средств в ограблениях", STRING_GLOBAL, "Закрыть", "");
    return 1;
}