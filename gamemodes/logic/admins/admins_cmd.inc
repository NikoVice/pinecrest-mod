/*
    Admins Command.
	Flin RolePlay
	2020 Author Vip_Uzer
*/

CMD:newnick(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Используйте: /newnick [никнейм]");
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `new_name` FROM `log_name` WHERE `old_name` = '%s' LIMIT 1", params[0]);
    new Cache:result = mysql_query(con_bd, STRING_GLOBAL);
    if(cache_num_rows() == 0)
    {
        cache_delete(result);
        return SendError(playerid, "Ник не был сменен.");
    }
    new nickname[MAX_PLAYER_NAME];
    cache_get_value_index(0, 0, nickname);
    cache_delete(result);
    SendAccess(playerid, "Ник %s был сменен на ник: "E"%s", params[0], nickname);
    return 1;
}

CMD:editproperty(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "is[24]", params[0], params[1])) {
        SendInfo(playerid, "Используйте: /editproperty [typeid] [никнейм]");
        SendInfo(playerid, "types: 1-house, 2-biz, 3 - cars, 4 - inventory, 5-bank, 6 - depozit, 7 - bitcoin, 8 - family");
        return 1;
    }
    if(!( 1 <= params[0] <= 7)) {
        SendInfo(playerid, "Используйте: /editproperty [typeid] [никнейм]");
        SendInfo(playerid, "types: 1-house, 2-biz, 3 - cars, 4 - inventory, 5-bank, 6 - depozit, 7 - bitcoin, 8 - family");
        return 1;
    }
    if(!(3 <= strlen(params[1]) <= 24)) {
        SendInfo(playerid, "Используйте: /editproperty [typeid] [никнейм]");
        SendInfo(playerid, "types: 1-house, 2-biz, 3 - cars, 4 - inventory, 5-bank, 6 - depozit, 7 - bitcoin, 8 - family");
        return 1;
    }

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1", params[1]);
    mysql_tquery(con_bd, STRING_GLOBAL, "EditPlayerProperty_GetAccount", "iis", playerid, params[0], params[1]);
    return 1;
}

forward EditPlayerProperty_GetAccount(playerid, property_type_id, nickname[]);
public EditPlayerProperty_GetAccount(playerid, property_type_id, nickname[])
{
    if(!cache_num_rows())
        return SendError(playerid, "Игрока с таким ником в базе данных не найдено.");

    cache_get_value_name_int(0, "id", p_temp[playerid][p_listitem_int]);

    if(GetPlayerUserID(p_temp[playerid][p_listitem_int]) != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок в сети.");

    STRING_GLOBAL[0] = EOS;
    switch(property_type_id)
    {
        case 1: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `house` WHERE `h_user_id` = %d LIMIT 30", p_temp[playerid][p_listitem_int]);
        case 2: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `biz` WHERE `b_user_id` = %d LIMIT 30", p_temp[playerid][p_listitem_int]);
        case 3: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_model`, `v_mysql_id`, `v_twinturbo`, `v_premium`, `v_number` FROM `vehicle` WHERE `v_owner_id` = %d LIMIT 30", p_temp[playerid][p_listitem_int]);
        case 4: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT a.`inv_slots`, i.`mysql_id`, i.`item_id`, i.`amount`, i.`acc_wear`, i.`acc_mt1`, i.`acc_mt2` FROM `inventory` AS i LEFT JOIN `accounts` AS a ON a.`id` = i.`owner_id` WHERE i.`owner_id` = %d AND `owner_type` = 0 LIMIT %d", p_temp[playerid][p_listitem_int], MAX_PLAYER_EQUIPMENT);
        case 5: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `bank` FROM `accounts` WHERE `id` = %d LIMIT 1", p_temp[playerid][p_listitem_int]);
        case 6: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `bank_deposit` FROM `accounts` WHERE `id` = %d LIMIT 1", p_temp[playerid][p_listitem_int]);
        case 7: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `bitcoin` FROM `accounts` WHERE `id` = %d LIMIT 1", p_temp[playerid][p_listitem_int]);
        case 8: format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `name` FROM `family` WHERE `owner_id` = %d LIMIT 30", p_temp[playerid][p_listitem_int]);
        default: return 1;
    }
    mysql_tquery(con_bd, STRING_GLOBAL, "EditProperty_GetInfo", "iis", playerid, property_type_id, nickname);
    return 1;
}
alias:editproperty("editprop", "epr");

forward EditProperty_GetInfo(playerid, property_type_id, nickname[]);
public EditProperty_GetInfo(playerid, property_type_id, nickname[])
{
    new rows, fmt_str[144];
    cache_get_row_count(rows);
    STRING_GLOBAL[0] = EOS;
    switch(property_type_id)
    {
        case 1:
        {
            if(!rows) return SendError(playerid, "У игрока нет домов.");
            new tmp_mysql_id, tmp_h_class;
            for(new idx; idx < rows; idx++)
            {
                p_temp[playerid][p_listitem][idx] = -1;
                cache_get_value_name_int(idx, "h_mysql_id", tmp_mysql_id);
                cache_get_value_name_int(idx, "h_squar", tmp_h_class);
                if(tmp_h_class < 1) tmp_h_class = 1;
                format(fmt_str, sizeof fmt_str, ""I"[%d]"W" Дом (ID: %d) [Класс: %s] \n", idx+1, tmp_mysql_id, house_class[tmp_h_class-1]);
                strcat(STRING_GLOBAL, fmt_str);
                p_temp[playerid][p_listitem][idx] = tmp_mysql_id;
            }
            f(fmt_str, ""I"Дома %s(%d)", nickname, rows);
            ShowPlayerDialog(playerid, D_EDITHOUSE_LIST, DIALOG_STYLE_LIST, fmt_str, STRING_GLOBAL, "Выбрать", "Отмена");
        }
        case 2:
        {
            if(!rows) return SendError(playerid, "У игрока нет бизнесов.");
            new tmp_mysql_id, bizz_name[24];
            for(new idx; idx < rows; idx++)
            {
                p_temp[playerid][p_listitem][idx] = -1;
                cache_get_value_name_int(idx, "b_mysql_id", tmp_mysql_id);
                cache_get_value_name(idx, "b_name", bizz_name,24);

                format(fmt_str, sizeof fmt_str, ""I"[%d]"W" Бизнес (ID: %d) [%s] \n", idx+1, tmp_mysql_id, bizz_name);
                strcat(STRING_GLOBAL, fmt_str);
                p_temp[playerid][p_listitem][idx] = tmp_mysql_id;
            }
            f(fmt_str, ""I"Бизнесы %s(%d)", nickname, rows);
            ShowPlayerDialog(playerid, D_EDITBIZZ_LIST, DIALOG_STYLE_LIST, fmt_str, STRING_GLOBAL, "Выбрать", "Отмена");
        }
        case 3:
        {
            if(!rows) return SendError(playerid, "У игрока нет транспортных средств.");

            new status_used[36],
                //veh_number[16] = "НЕТ НОМЕРОВ",
                modelid,
                twinturbo,
                premium;
            static const twinturbo_status[][] = {"", "[{ffff00}TT"W"]"};
            static const premium_status[][] = {"", "[{ffff00}PREMIUM"W"]"};
            for(new idx; idx < rows; idx++)
            {
                p_temp[playerid][p_listitem_cars][idx] = -1;
                cache_get_value_name_int(idx, "v_model", modelid);
                //cache_get_value_name(idx, "v_number", veh_number, 16);
                //if(strequals(veh_number, "NULL")) veh_number = "НЕТ НОМЕРОВ";
                cache_get_value_name_int(idx, "v_twinturbo", twinturbo);
                cache_get_value_name_int(idx, "v_premium", premium);
                cache_get_value_name_int(idx, "v_mysql_id", p_temp[playerid][p_listitem_cars][idx]);

                /*if(GetSlotVehicleMarket(p_temp[playerid][p_listitem_cars][idx]) != -1) format(status_used, sizeof status_used, ""A"[На авторынке]");*/
                format(fmt_str, sizeof fmt_str, ""I"[%d]"W" %s(ID: %d) %s %s  %s\n", idx+1, GetVehicleName(INVALID_VEHICLE_ID, modelid), modelid, twinturbo_status[twinturbo], premium_status[premium], /*veh_number,*/ status_used);
                strcat(STRING_GLOBAL, fmt_str);
            }
            p_temp[playerid][loadcar_max] = rows;
            f(fmt_str, ""I"Транспорт %s(%d)", nickname, rows);
            ShowPlayerDialog(playerid, D_EDITCARS_LIST, DIALOG_STYLE_LIST, fmt_str, STRING_GLOBAL, "Выбрать", "Отмена");
        }
        case 4:
        {
            //if(!rows) return SendError(playerid, "У игрока нет предметов в инвентаре.");
            new itemID, itemAmount, Float:accWear, accMt1, accMt2;
            STRING_GLOBAL[0] = EOS;
            if(rows)
            {
                for(new i; i < rows; i++)
                {
                    p_temp[playerid][p_listitem][i] = -1;
                    if(i < rows)
                    {
                        cache_get_value_name_int(i, "mysql_id", p_temp[playerid][p_listitem][i]);
                        cache_get_value_name_int(i, "item_id", itemID);

                        if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY)
                        {
                            cache_get_value_name_int(i, "amount", itemAmount);
                            f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d ед.\n", STRING_GLOBAL, i+1, ItemsInfo[itemID][iName], itemAmount);
                        }
                        else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
                        {
                            cache_get_value_name_float(i, "acc_wear", accWear);
                            cache_get_value_name_int(i, "acc_mt1", accMt1);
                            cache_get_value_name_int(i, "acc_mt2", accMt2);
                            f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t[%.1f] (%s/%s)\n", STRING_GLOBAL, i+1, ItemsInfo[itemID][iName], accWear, AccessoriesColorInfo[accMt1][acName], AccessoriesColorInfo[accMt2][acName]);
                        }
                        else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_SKINS || ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
                            f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t \n", STRING_GLOBAL, i+1, ItemsInfo[itemID][iName]);
                    }

                }
            }
            new all_slots;
            cache_get_value_name_int(0, "inv_slots", all_slots);
            if(rows < all_slots || !rows)
            {
                p_temp[playerid][p_listitem][rows] = -1;
                f(STRING_GLOBAL, "%s"I"[%d]"W" Выдать предмет\t \n", STRING_GLOBAL, rows+1);
            }
            f(fmt_str, ""I"%s | Count: %d (Slots: %d | Free: %d)", nickname, rows, all_slots, all_slots-rows);
            ShowPlayerDialog(playerid, D_EDITINV_LIST, DIALOG_STYLE_TABLIST, fmt_str, STRING_GLOBAL, "Выбрать", "Отмена");
        }
        case 5:
        {
            new bank_money;
            cache_get_value_int(0, "bank", bank_money);
            f(fmt_str, ""I"Банк: %d", nickname, bank_money);
            p_temp[playerid][p_listitem][40] = bank_money;
            ShowPlayerDialog(playerid, D_EDITBANK_MENU, DIALOG_STYLE_INPUT, fmt_str, ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
        }
        case 6:
        {
            new bank_money;
            cache_get_value_int(0, "bank_deposit", bank_money);
            f(fmt_str, ""I"Банк депозит: %d", nickname, bank_money);
            p_temp[playerid][p_listitem][40] = bank_money;
            ShowPlayerDialog(playerid, D_EDITDEPOSIT_MENU, DIALOG_STYLE_INPUT, fmt_str, ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
        }
        case 7:
        {
            new iBitcoin;
            cache_get_value_int(0, "bitcoin", iBitcoin);
            f(fmt_str, ""I"Банк депозит: %d", nickname, iBitcoin);
            p_temp[playerid][p_listitem][40] = iBitcoin;
            ShowPlayerDialog(playerid, D_EDITBITCOIN_MENU, DIALOG_STYLE_INPUT, fmt_str, ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
        }
        case 8:
        {
            if(!rows) return SendError(playerid, "Игрок не является владельцем.");
            new getname[64];
            cache_get_value_int(0, "id", p_temp[playerid][p_listitem][40]);
            cache_get_value_name(0, "name", getname);
            ShowPlayerDialog(playerid, D_EDITFAMILY, DIALOG_STYLE_LIST, getname, ""I"[1]"W" Сменить владельца\n"I"[2]"W" Забрать", "Выбрать", "Отмена");
        }
    }
    return 1;
}

editproperty_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
    {
        //family
        case D_EDITFAMILY:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0: ShowPlayerDialog(playerid, D_EDITFAMILY_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Смена владельца", ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
                case 1:
                {
                    new idx = -1;
                    for(new i = family_count-1; i != -1; i--)
                    {
                        if(p_temp[playerid][p_listitem][40] == FamilyData[i][fMysqlID])
                        {
                            idx = i;
                            break;
                        }
                    }
                    if(idx == -1) return SendError(playerid, "Семья не обнаружена.");

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `family_rang` = '0', `family_id` = '-1' WHERE `id` = %d",
                        FamilyData[idx][fOwnerID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `family` SET `owner_id` = 1 WHERE `id` = %d", FamilyData[idx][fMysqlID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    FamilyData[idx][fOwnerID] = 1;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `family_rang` = '10', `family_id` = %d WHERE `id` = 1", FamilyData[idx][fMysqlID]);
                    mysql_tquery(con_bd, STRING_GLOBAL);
                }
            }
            return 1;
        }
        case D_EDITFAMILY_CHANGE_OWNER:
        {
            if(!response) return 1;
            if(strlen(inputtext) < 3 || strlen(inputtext) > 24)
                return ShowPlayerDialog(playerid, D_EDITFAMILY_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Смена владельца", ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
            new idx = -1;
            for(new i = family_count-1; i != -1; i--)
            {
                if(p_temp[playerid][p_listitem][40] == FamilyData[i][fMysqlID])
                {
                    idx = i;
                    break;
                }
            }
            if(idx == -1) return SendError(playerid, "Семья не обнаружена.");
            
            new player_mysql_id = INVALID_MYSQL_ID, targetid = GetPlayerID(inputtext);
            if(targetid == INVALID_PLAYER_ID)
            {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%s' LIMIT 1", inputtext);
                new Cache:result = mysql_query(con_bd, STRING_GLOBAL);
                if(cache_num_rows() == 0)
                {
                    SendError(playerid, "Игрока с таким ником в базе данных не найдено.");
                    ShowPlayerDialog(playerid, D_EDITFAMILY_CHANGE_OWNER, DIALOG_STYLE_INPUT, "Смена владельца", ""W"Введите ник нового владельца", "Выбрать", "Отмена");
                    cache_delete(result);
                    return 1;
                }
                cache_get_value_name_int(0, "id", player_mysql_id);
                cache_delete(result);
            }
            else
            {
                player_mysql_id = p_info[targetid][ID];
                p_info[targetid][family_rang] = 10;
                p_info[targetid][family_id] = FamilyData[idx][fMysqlID];
                SendAccess(targetid, "Администратор %s назначил Вас владельцем семьи: %s", get_name(playerid), FamilyData[idx][fName]);
            }

            if(player_mysql_id == INVALID_MYSQL_ID) return 1;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `family` SET `owner_id` = %d WHERE `id` = %d",
                player_mysql_id, FamilyData[idx][fMysqlID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `family_rang` = '10', `family_id` = %d WHERE `id` = %d",
                FamilyData[idx][fMysqlID], player_mysql_id);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `family_rang` = '1' WHERE `family_id` = %d AND `family_rang` > 9",
                FamilyData[idx][fMysqlID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            FamilyData[idx][fOwnerID] = player_mysql_id;
    
            SendAccess(playerid, "Вы сменили владельца семьи.");
            return 1;
        }
        // bitcoin
        case D_EDITBITCOIN_MENU:
        {
            if(!response) return 1;
            if(!strlen(inputtext))
                return ShowPlayerDialog(playerid, D_EDITDEPOSIT_MENU, DIALOG_STYLE_INPUT, ""I"Bitcoin", ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
            new iBitcoin = strval(inputtext);
            if(!(0 <= (p_temp[playerid][p_listitem][40]+iBitcoin) <= 1000))
                return ShowPlayerDialog(playerid, D_EDITDEPOSIT_MENU, DIALOG_STYLE_INPUT, ""I"Bitcoin", ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
            p_temp[playerid][p_listitem][40] += iBitcoin;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `bitcoin` = %d WHERE `id` = %d",
                p_temp[playerid][p_listitem][40], p_temp[playerid][p_listitem_int]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            SendAccess(playerid, "Новое значение Bitcoin: %d$", p_temp[playerid][p_listitem][40]);
            return 1;
        }
        // bank deposit
        case D_EDITDEPOSIT_MENU:
        {
            if(!response) return 1;
            if(!strlen(inputtext))
                return ShowPlayerDialog(playerid, D_EDITDEPOSIT_MENU, DIALOG_STYLE_INPUT, ""I"Банк депозит", ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
            new bank_money = strval(inputtext);
            if(!(0 <= (p_temp[playerid][p_listitem][40]+bank_money) <= 999_000_000))
                return ShowPlayerDialog(playerid, D_EDITDEPOSIT_MENU, DIALOG_STYLE_INPUT, ""I"Банк депозит", ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
            p_temp[playerid][p_listitem][40] += bank_money;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `bank_deposit` = %d WHERE `id` = %d",
                p_temp[playerid][p_listitem][40], p_temp[playerid][p_listitem_int]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            SendAccess(playerid, "Новое значение банк депозит: %d$", p_temp[playerid][p_listitem][40]);
            return 1;
        }
        // bank
        case D_EDITBANK_MENU:
        {
            if(!response) return 1;
            if(!strlen(inputtext))
                return ShowPlayerDialog(playerid, D_EDITDEPOSIT_MENU, DIALOG_STYLE_INPUT, ""I"Банк", ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
            new bank_money = strval(inputtext);
            if(!(0 <= (p_temp[playerid][p_listitem][40]+bank_money) <= 1_999_000_000))
                return ShowPlayerDialog(playerid, D_EDITBANK_MENU, DIALOG_STYLE_INPUT, ""I"Банк", ""W"Выдать или забрать(- перед числом):", "Выбрать", "Отмена");
            p_temp[playerid][p_listitem][40] += bank_money;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `bank` = %d WHERE `id` = %d",
                p_temp[playerid][p_listitem][40], p_temp[playerid][p_listitem_int]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            SendAccess(playerid, "Новое значение банк: %d$", p_temp[playerid][p_listitem][40]);
            return 1;
        }
        // inventory
        case D_EDITINV_LIST:
        {
            if(!response) return 1;
            if(p_info[playerid][admin] < 7) return 1;
            if(p_temp[playerid][p_listitem][listitem] == -1)
                ShowDialogEditInventoryGive(playerid);
            else
            {
                SetPVarInt(playerid, #EPR_INV_MYSQL, p_temp[playerid][p_listitem][listitem]);
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `item_id`, `amount` FROM `inventory` WHERE `mysql_id` = %d LIMIT 1", p_temp[playerid][p_listitem][listitem]);
                mysql_tquery(con_bd, STRING_GLOBAL, "EditInventory_Menu", "i", playerid);
            }
            return 1;
        }
        case D_EDITINV_GIVE:
        {
            if(!response)
                return 1;
            if(!strlen(inputtext))
                return ShowDialogEditInventoryGive(playerid);
            new extra[4];
            if(sscanf(inputtext, "p<,>iI(-1)I(-1)I(-1)", extra[0], extra[1], extra[2], extra[3]))
                return ShowDialogEditInventoryGive(playerid);

            if(!(1 <= extra[0] <= MAX_ITEMS-1))
                return ShowDialogEditInventoryGive(playerid);

            new ownerID = p_temp[playerid][p_listitem_int];
            if(ownerID <= 0) return 1;

            if(ItemsInfo[extra[0]][iType] == TYPE_ITEMS_INVENTORY || ItemsInfo[extra[0]][iType] == TYPE_ITEMS_VEHICLE_TUNE)
            {   //give items
                if(!(1 <= extra[1] <= ItemsInfo[extra[0]][iMax]))
                {
                    SendError(playerid, "Выдать за раз можно не меньше 1 и не больше вмещаемой в один слот (%d)", ItemsInfo[extra[0]][iMax]);
                    return ShowDialogEditInventoryGive(playerid);
                }
            }
            else if(ItemsInfo[extra[0]][iType] == TYPE_ITEMS_ACCESSORIES)
            {   //give accessories
                if(!(0 <= extra[1] <= 100))
                {
                    SendError(playerid, "Процент износа должен быть от 0 до 100.");
                    return ShowDialogEditInventoryGive(playerid);
                }
                if(!(0 <= extra[2] <= sizeof(AccessoriesColorInfo)-1) || !(0 <= extra[3] <= sizeof(AccessoriesColorInfo)-1))
                {
                    SendError(playerid, "Цвет должен быть от 0 до %d.", sizeof(AccessoriesColorInfo)-1);
                    return ShowDialogEditInventoryGive(playerid);
                }
                
            }

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `slot_id`, (SELECT `inv_slots` FROM `accounts` WHERE `id` = %d) AS inv_slots FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d ORDER BY `slot_id` ASC",
                ownerID, ownerID, INVENTORY_OWNER_TYPE_PLAYER);

            mysql_tquery(con_bd, STRING_GLOBAL, "AdminGiveInvCallback", "iiiiii", playerid, ownerID, extra[0], extra[1], extra[2], extra[3]);
            return 1;
        }
        case D_EDITITEM_MENU:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemAmount = GetPVarInt(playerid, #EPR_INV_AMOUNT),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!listitem || !response)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_AMOUNT);
                DeletePVar(playerid, #EPR_INV_MYSQL);
            }
            if(!response || p_info[playerid][admin] < 7) return 1;
            STRING_GLOBAL[0] = EOS;
            switch(listitem)
            {
                case 0:
                {
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `inventory` WHERE mysql_id = %d", itemMySQL);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы удалили \"%s\" %d ед.", ItemsInfo[itemID][iName], itemAmount);

                    Log(LOG_player, INFO, "Admin: %s[%d](%s %s) удалил offline[%d] %s %d ед. | #EPR",
                        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                        p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], itemAmount);

                    p_temp[playerid][p_listitem_int] = -1;
                }
                case 1:
                {
                    f(STRING_GLOBAL, ""W"Введите сколько добавить:\n\nДоступно места в слоте: "I"%d ед.", ItemsInfo[itemID][iMax]-itemAmount);
                    return ShowPlayerDialog(playerid, D_EDITITEM_ADD, DIALOG_STYLE_INPUT, ""I"Редактирование предмета", STRING_GLOBAL, "Ввести", "Отмена");
                }
                case 2:
                {
                    f(STRING_GLOBAL, ""W"Введите новое значение:\n\nМаксимально вмещается в слоте: "I"%d ед.", ItemsInfo[itemID][iMax]);
                    ShowPlayerDialog(playerid, D_EDITITEM_NEW_VALUE, DIALOG_STYLE_INPUT, ""I"Редактирование предмета", STRING_GLOBAL, "Ввести", "Отмена");
                }
            }
            return 1;
        }
        case D_EDITITEM_NEW_VALUE:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemAmount = GetPVarInt(playerid, #EPR_INV_AMOUNT),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_AMOUNT);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                return 1;
            }
            new value = strval(inputtext);
            STRING_GLOBAL[0] = EOS;
            if(!strlen(inputtext) || !(1 <= value <= ItemsInfo[itemID][iMax]))
            {
                f(STRING_GLOBAL, ""W"Введите новое значение:\n\nМаксимально вмещается в слоте: "I"%d ед.", ItemsInfo[itemID][iMax]);
                return ShowPlayerDialog(playerid, D_EDITITEM_NEW_VALUE, DIALOG_STYLE_INPUT, ""I"Редактирование предмета", STRING_GLOBAL, "Ввести", "Отмена");
            }
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = %d WHERE `mysql_id` = %d", value, itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы установили \"%s\" значение %d ед. вместо %d ед.", ItemsInfo[itemID][iName], value, itemAmount);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_AMOUNT);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) установил offline[%d] %s %d ед. вместо %d ед. | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], value, itemAmount);
            return 1;
        }
        case D_EDITITEM_ADD:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemAmount = GetPVarInt(playerid, #EPR_INV_AMOUNT),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7 || ItemsInfo[itemID][iMax]-itemAmount < 1)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_AMOUNT);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                if(response && ItemsInfo[itemID][iMax]-itemAmount < 1) SendError(playerid, "В слоте нет места.");
                return 1;
            }
            new value = strval(inputtext);
            if(!strlen(inputtext) || !(1 <= value <= ItemsInfo[itemID][iMax]-itemAmount))
            {
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, ""W"Введите сколько добавить:\n\nДоступно места в слоте: "I"%d ед.", ItemsInfo[itemID][iMax]-itemAmount);
                return ShowPlayerDialog(playerid, D_EDITITEM_ADD, DIALOG_STYLE_INPUT, ""I"Редактирование предмета", STRING_GLOBAL, "Ввести", "Отмена");
            }
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `amount` = `amount` + %d WHERE `mysql_id` = %d", value, itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы выдали \"%s\" %d ед. | Новое значение слота: %d ед.", ItemsInfo[itemID][iName], value, itemAmount+value);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_AMOUNT);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) выдал offline[%d] %s %d ед. новое значение %d ед. | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], value, itemAmount+value);
            return 1;
        }
        case D_EDITACC_MENU:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);


            if(!listitem || !response)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_AMOUNT);
                DeletePVar(playerid, #EPR_INV_MYSQL);
            }
            if(!response || p_info[playerid][admin] < 7) return 1;
            STRING_GLOBAL[0] = EOS;
            switch(listitem)
            {
                case 0:
                {
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `inventory` WHERE mysql_id = %d", itemMySQL);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы удалили \"%s\".", ItemsInfo[itemID][iName]);

                    Log(LOG_player, INFO, "Admin: %s[%d](%s %s) удалил offline[%d] %s | #EPR",
                        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                        p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName]);

                    p_temp[playerid][p_listitem_int] = -1;
                }
                case 1: ShowPlayerDialog(playerid, D_EDITACC_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", ""W"Введите новое значение:", "Ввести", "Отмена");
                case 2: ShowPlayerDialog(playerid, D_EDITACC_WEAR, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", ""W"Введите новое значение:\n\nОт 0 до 100.", "Ввести", "Отмена");
                case 3,4:
                {
                    new color_str[256];
                    for(new i; i < sizeof(AccessoriesColorInfo); i++)
                    format(color_str, sizeof(color_str), "%s %d - {%06x}%s"W"\n", color_str, i, i == 0 ? 0xFFFFFF : AccessoriesColorInfo[i][acColorRBG] & 0xFFFFFF, AccessoriesColorInfo[i][acName]);

                    f(STRING_GLOBAL, ""W"Выберите цвет:\n%s\n\n"W"Введите новое значение:", color_str);
                    if(listitem == 3) ShowPlayerDialog(playerid, D_EDITACC_MT1, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", STRING_GLOBAL, "Ввести", "Отмена");
                    else ShowPlayerDialog(playerid, D_EDITACC_MT2, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", STRING_GLOBAL, "Ввести", "Отмена");
                }
            }
            return 1;
        }
        case D_EDITACC_MODELID:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                return 1;
            }

            new value = strval(inputtext);
            if(!strlen(inputtext) || !(1 <= value <= MAX_ITEMS-1))
                return ShowPlayerDialog(playerid, D_EDITACC_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", ""W"Введите новое значение:", "Ввести", "Отмена");
            if(ItemsInfo[value][iType] != TYPE_ITEMS_ACCESSORIES)
            {
                SendError(playerid, "Введенный ID не соответствует аксессуару.");
                return ShowPlayerDialog(playerid, D_EDITACC_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", ""W"Введите новое значение:", "Ввести", "Отмена");
            }

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `item_id` = %d WHERE `mysql_id` = %d", value, itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили \"%s\" состояние на \"%s\"", ItemsInfo[itemID][iName], ItemsInfo[value][iName]);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) сменил offline[%d] с %s на %s | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], ItemsInfo[value][iName]);
            return 1;
        }
        case D_EDITACC_WEAR:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                return 1;
            }

            new value = strval(inputtext);
            if(!strlen(inputtext) || !(0 <= value <= 100))
                return ShowPlayerDialog(playerid, D_EDITACC_WEAR, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", ""W"Введите новое значение:\n\nОт 0 до 100.", "Ввести", "Отмена");

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `acc_wear` = %f WHERE `mysql_id` = %d", float(value), itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили для \"%s\" состояние на %d", ItemsInfo[itemID][iName], value);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) сменил состояние offline[%d] на %d.0 | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], value);
            return 1;
        }
        case D_EDITACC_MT1:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                return 1;
            }

            new value = strval(inputtext);
            if(!strlen(inputtext) || !(0 <= value <= sizeof(AccessoriesColorInfo)-1))
            {
                new color_str[256];
                for(new i; i < sizeof(AccessoriesColorInfo); i++)
                format(color_str, sizeof(color_str), "%s %d - {%06x}%s"W"\n", color_str, i, i == 0 ? 0xFFFFFF : AccessoriesColorInfo[i][acColorRBG] & 0xFFFFFF, AccessoriesColorInfo[i][acName]);

                f(STRING_GLOBAL, "Выберите цвет:\n%s\n\n"W"Введите новое значение:", color_str);
                return ShowPlayerDialog(playerid, D_EDITACC_MT1, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", STRING_GLOBAL, "Ввести", "Отмена");
            }
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `acc_mt1` = %d WHERE `mysql_id` = %d", value, itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили для \"%s\" цвет #1 на %s", ItemsInfo[itemID][iName], AccessoriesColorInfo[value][acName]);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) сменил цвет #1 offline[%d] на %s | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], AccessoriesColorInfo[value][acName]);
            return 1;
        }
        case D_EDITACC_MT2:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                return 1;
            }

            new value = strval(inputtext);
            if(!strlen(inputtext) || !(0 <= value <= sizeof(AccessoriesColorInfo)-1))
            {
                new color_str[256];
                for(new i; i < sizeof(AccessoriesColorInfo); i++)
                format(color_str, sizeof(color_str), "%s %d - {%06x}%s"W"\n", color_str, i, i == 0 ? 0xFFFFFF : AccessoriesColorInfo[i][acColorRBG] & 0xFFFFFF, AccessoriesColorInfo[i][acName]);

                f(STRING_GLOBAL, "Выберите цвет:\n%s\n\n"W"Введите новое значение:", color_str);
                return ShowPlayerDialog(playerid, D_EDITACC_MT2, DIALOG_STYLE_INPUT, ""I"Редактирование аксессуара", STRING_GLOBAL, "Ввести", "Отмена");
            }
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `acc_mt2` = %d WHERE `mysql_id` = %d", value, itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили для \"%s\" цвет #2 на %s", ItemsInfo[itemID][iName], AccessoriesColorInfo[value][acName]);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) сменил цвет #2 offline[%d] на %s | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], AccessoriesColorInfo[value][acName]);
            return 1;
        }
        case D_EDITSKIN_MENU:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!listitem || !response)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_AMOUNT);
                DeletePVar(playerid, #EPR_INV_MYSQL);
            }
            if(!response || p_info[playerid][admin] < 7) return 1;
            STRING_GLOBAL[0] = EOS;
            switch(listitem)
            {
                case 0:
                {
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `inventory` WHERE mysql_id = %d", itemMySQL);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы удалили \"%s\".", ItemsInfo[itemID][iName]);

                    Log(LOG_player, INFO, "Admin: %s[%d](%s %s) удалил offline[%d] %s | #EPR",
                        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                        p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName]);

                    p_temp[playerid][p_listitem_int] = -1;
                }
                case 1: ShowPlayerDialog(playerid, D_EDITSKIN_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование скина", ""W"Введите новое значение:", "Ввести", "Отмена");
            }
            return 1;
        }
        case D_EDITSKIN_MODELID:
        {
            new itemID = GetPVarInt(playerid, #EPR_INV_ITEMID),
                itemMySQL = GetPVarInt(playerid, #EPR_INV_MYSQL);

            if(!response || p_info[playerid][admin] < 7)
            {
                DeletePVar(playerid, #EPR_INV_ITEMID);
                DeletePVar(playerid, #EPR_INV_MYSQL);
                return 1;
            }

            new value = strval(inputtext);
            if(!strlen(inputtext) || !(1 <= value <= MAX_ITEMS-1))
                return ShowPlayerDialog(playerid, D_EDITSKIN_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование скина", ""W"Введите новое значение:", "Ввести", "Отмена");
            if(ItemsInfo[value][iType] != TYPE_ITEMS_SKINS)
            {
                SendError(playerid, "Введенный ID не соответствует скину.");
                return ShowPlayerDialog(playerid, D_EDITACC_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование скина", ""W"Введите новое значение:", "Ввести", "Отмена");
            }

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `item_id` = %d WHERE `mysql_id` = %d", value, itemMySQL);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили \"%s\" состояние на \"%s\"", ItemsInfo[itemID][iName], ItemsInfo[value][iName]);

            DeletePVar(playerid, #EPR_INV_ITEMID);
            DeletePVar(playerid, #EPR_INV_MYSQL);

            Log(LOG_player, INFO, "Admin: %s[%d](%s %s) сменил offline[%d] с %s на %s | #EPR",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                p_temp[playerid][p_listitem_int], ItemsInfo[itemID][iName], ItemsInfo[value][iName]);
            return 1;
        }
        // bizz
        case D_EDITBIZZ_LIST:
        {
            if(!response) return 1;
            if(p_info[playerid][admin] < 7) return 1;
            p_temp[playerid][p_listitem_int] = listitem;
            ShowPlayerDialog(playerid, D_EDITBIZZ_MENU, DIALOG_STYLE_LIST, ""I"Редактирование бизнеса",
                ""I"[1]"W" Телепортироваться к бизнесу\n"I"[2]"W" Забрать бизнес(Слить в гос)\n"I"[3]"W" Сменить владельца", "Выбрать", "Отмена");
            return 1;
        }
        case D_EDITBIZZ_MENU:
        {
            if(p_info[playerid][admin] < 7) return 1;
            new idx = p_temp[playerid][p_listitem][p_temp[playerid][p_listitem_int]];
            switch(listitem)
            {
                case 0:
                {
                    SetPlayerVirtualWorld(playerid, 0);
                    SetPlayerInterior(playerid, 0);
                    SetPlayerPos(playerid,b_info[idx][b_enter][0], b_info[idx][b_enter][1], b_info[idx][b_enter][2]);
                }
                case 1:
                {
                    b_info[idx][b_owned_at] = timestamp;
                    b_info[idx][b_paydays_received] = 10;
                    b_info[idx][b_user_id] = 1;
                    strmid(b_info[idx][_owner], "Flin Game", 0, strlen("Flin Game"), MAX_PLAYER_NAME);
                    update_bizz(idx);
                    save_bizz(idx);
                    SendAccess(playerid, "Вы забрали бизнес.");
                }
                case 2: ShowPlayerDialog(playerid, D_EDITBIZZ_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование бизнеса",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
            }
        }
        case D_EDITBIZZ_CHANGE_OWNER:
        {
            if(!response) return 1;
            if(strlen(inputtext) < 3 || strlen(inputtext) > 24)
                return ShowPlayerDialog(playerid, D_EDITBIZZ_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование бизнеса",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%s' LIMIT 1",
            inputtext);
            new Cache:result = mysql_query(con_bd, STRING_GLOBAL);
            if(cache_num_rows() == 0)
            {
                SendError(playerid, "Игрока с таким ником в базе данных не найдено.");
                ShowPlayerDialog(playerid, D_EDITBIZZ_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование бизнеса",
                    ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
                cache_delete(result);
                return 1;
            }
            new player_mysql_id;
            cache_get_value_name_int(0, "id", player_mysql_id);

            new idx = p_temp[playerid][p_listitem][p_temp[playerid][p_listitem_int]];

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `biz` SET `b_user_id` = %d WHERE `b_mysql_id` = %d",
            player_mysql_id, b_info[idx][b_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            b_info[idx][b_owned_at] = timestamp;
            b_info[idx][b_paydays_received] = 0;
            b_info[idx][b_user_id] = player_mysql_id;
            strmid(b_info[idx][_owner], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
            update_bizz(idx);
            save_bizz(idx);

            SendAccess(playerid, "Вы сменили владельца бизнеса.");
            return 1;
        }
        // house
        case D_EDITHOUSE_LIST:
        {
            if(!response) return 1;
            if(p_info[playerid][admin] < 7) return 1;
            p_temp[playerid][p_listitem_int] = listitem;
            ShowPlayerDialog(playerid, D_EDITHOUSE_MENU, DIALOG_STYLE_LIST, ""I"Редактирование Т/С",
                ""I"[1]"W" Телепортироваться к дому\n"I"[2]"W" Забрать дом(Слить в гос)\n"I"[3]"W" Сменить владельца", "Выбрать", "Отмена");
            return 1;
        }
        case D_EDITHOUSE_MENU:
        {
            if(p_info[playerid][admin] < 7) return 1;
            new idx = p_temp[playerid][p_listitem][p_temp[playerid][p_listitem_int]];
            switch(listitem)
            {
                case 0:
                {
                    SetPlayerVirtualWorld(playerid, 0);
                    SetPlayerInterior(playerid, 0);
                    SetPlayerPos(playerid,h_info[idx][h_enter][0], h_info[idx][h_enter][1], h_info[idx][h_enter][2]);
                }
                case 1:
                {
                    h_info[idx][h_user_id] = 1;
                    strmid(h_info[idx][h_owner], "Flin Game", 0, strlen("Flin Game"), MAX_PLAYER_NAME);
                    update_house(idx);
                    save_house(idx);
                    SendAccess(playerid, "Вы забрали дом.");
                }
                case 2: ShowPlayerDialog(playerid, D_EDITHOUSE_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование дома",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
            }
        }
        case D_EDITHOUSE_CHANGE_OWNER:
        {
            if(!response) return 1;
            if(strlen(inputtext) < 3 || strlen(inputtext) > 24)
                return ShowPlayerDialog(playerid, D_EDITHOUSE_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование дома",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%s' LIMIT 1",
            inputtext);
            new Cache:result = mysql_query(con_bd, STRING_GLOBAL);
            if(cache_num_rows() == 0)
            {
                SendError(playerid, "Игрока с таким ником в базе данных не найдено.");
                ShowPlayerDialog(playerid, D_EDITHOUSE_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование дома",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
                cache_delete(result);
                return 1;
            }
            new player_mysql_id;
            cache_get_value_name_int(0, "id", player_mysql_id);

            new idx = p_temp[playerid][p_listitem][p_temp[playerid][p_listitem_int]];

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `house` SET `h_user_id` = %d WHERE `h_mysql_id` = %d",
            player_mysql_id, h_info[idx][h_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            h_info[idx][h_user_id] = player_mysql_id;
            strmid(h_info[idx][h_owner], inputtext, 0, strlen(inputtext), MAX_PLAYER_NAME);
            update_house(idx);
            save_house(idx);

            SendAccess(playerid, "Вы сменили владельца дома.");
            return 1;
        }
        /// cars
        case D_EDITCARS_MENU:
        {
            if(!response) return 1;
            if(p_info[playerid][admin] < 7) return 1;
            switch(listitem)
            {
                case 0:
                {
                    new vehicle_mysql_id = p_temp[playerid][p_listitem_cars][p_temp[playerid][p_listitem_int]];
                    EditCars_DestroyVehicle(vehicle_mysql_id);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `vehicle` SET `v_owner_id` = 1 WHERE `v_mysql_id` = %d",
                    vehicle_mysql_id);
                    mysql_tquery(con_bd, STRING_GLOBAL);

                    SendAccess(playerid, "Вы удалили транспортное средство.");
                }
                case 1: ShowPlayerDialog(playerid, D_EDITCARS_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование Т/С",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
                case 2: ShowPlayerDialog(playerid, D_EDITCARS_CHANGE_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование Т/С",
                            ""W"Введите новый ид модели:", "Выбрать", "Отмена");
            }
            return 1;
        }
        case D_EDITCARS_CHANGE_OWNER:
        {
            if(!response) return 1;
            if(strlen(inputtext) < 3 || strlen(inputtext) > 24)
                return ShowPlayerDialog(playerid, D_EDITCARS_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование Т/С",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%s' LIMIT 1",
            inputtext);
            new Cache:result = mysql_query(con_bd, STRING_GLOBAL);
            if(cache_num_rows() == 0)
            {
                SendError(playerid, "Игрока с таким ником в базе данных не найдено.");
                ShowPlayerDialog(playerid, D_EDITCARS_CHANGE_OWNER, DIALOG_STYLE_INPUT, ""I"Редактирование Т/С",
                            ""W"Введите ник нового владельца:", "Выбрать", "Отмена");
                cache_delete(result);
                return 1;
            }
            new player_mysql_id;
            cache_get_value_name_int(0, "id", player_mysql_id);

            new vehicle_mysql_id = p_temp[playerid][p_listitem_cars][p_temp[playerid][p_listitem_int]];
            EditCars_DestroyVehicle(vehicle_mysql_id);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `vehicle` SET `v_owner_id` = %d WHERE `v_mysql_id` = %d",
            player_mysql_id, vehicle_mysql_id);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили владельца транспортного средства.");
            return 1;
        }
        case D_EDITCARS_CHANGE_MODELID:
        {
            if(!response) return 1;
            new vehicle_model_id;
            if(sscanf(inputtext, "i", vehicle_model_id))
                return ShowPlayerDialog(playerid, D_EDITCARS_CHANGE_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование Т/С", ""W"Введите новый ид модели:", "Выбрать", "Отмена");
            if(!(400 <= vehicle_model_id <= 611))
            {
                SendError(playerid, "Не верный ИД модели.");
                return ShowPlayerDialog(playerid, D_EDITCARS_CHANGE_MODELID, DIALOG_STYLE_INPUT, ""I"Редактирование Т/С",
                            ""W"Введите новый ид модели:", "Выбрать", "Отмена");
            }
            new vehicle_mysql_id = p_temp[playerid][p_listitem_cars][p_temp[playerid][p_listitem_int]];
            EditCars_DestroyVehicle(vehicle_mysql_id);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `vehicle` SET `v_model` = %d WHERE `v_mysql_id` = %d",
            vehicle_model_id, vehicle_mysql_id);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы сменили модель транспортного средства.");
            return 1;
        }
        case D_EDITCARS_LIST:
        {
            if(!response) return 1;
            if(p_info[playerid][admin] < 7) return 1;
            p_temp[playerid][p_listitem_int] = listitem;
            ShowPlayerDialog(playerid, D_EDITCARS_MENU, DIALOG_STYLE_LIST, ""I"Редактирование Т/С",
                ""I"[1]"W" Забрать Т/С(Удалить)\n"I"[2]"W" Сменить владельца\n"I"[3]"W" Сменить модель", "Выбрать", "Отмена");
            return 1;
        }
    }
    return 1;
}

forward AdminGiveInvCallback(playerid, ownerID, item_id, extra1, extra2, extra3);
public AdminGiveInvCallback(playerid, ownerID, item_id, extra1, extra2, extra3)
{
    new iSlots[MAX_PLAYER_EQUIPMENT], free_slot = 0;
    new rows = cache_num_rows();
    if(rows)
    {
        new iInvSlots;
        cache_get_value_name_int(0, "inv_slots", iInvSlots);
        if(rows >= iInvSlots) return SendError(playerid, "У игрока нет свободных слотов для выдачи предмета.");
        for(new i; i < rows; i++)
        {
            if(rows >= MAX_PLAYER_EQUIPMENT-1) break;
            cache_get_value_name_int(i, "slot_id", iSlots[i]);
            if(free_slot == iSlots[i]) 
                free_slot = iSlots[i]+1;
        }
    }

    new _amount = 1, _mc1 = 0, _mc2 = 0, 
        Float:_acc_wear = 100.0, Float:_skin_wear = 100.0,
        _acc_premium = 0, _skin_premium = 0;

    if(ItemsInfo[item_id][iType] == TYPE_ITEMS_INVENTORY)
    {
        if(!(1 <= extra1 <= ItemsInfo[item_id][iMax]))
        {
            SendError(playerid, "Выдать за раз можно не меньше 1 и не больше вмещаемой в один слот (%d)", ItemsInfo[item_id][iMax]);
            return ShowDialogEditInventoryGive(playerid);
        }
        //give items
        _amount = extra1;
        SendAccess(playerid, "Вы выдали \"%s\" %d ед.", ItemsInfo[item_id][iName], extra1);

        Log(LOG_player, INFO, "Admin: %s[%d](%s %s) выдал offline[%d] %s %d ед. | #EPR",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            ownerID, ItemsInfo[item_id][iName], extra1);
    }
    else if(ItemsInfo[item_id][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        if(!(0 <= extra1 <= 100))
        {
            SendError(playerid, "Процент износа должен быть от 0 до 100.");
            return ShowDialogEditInventoryGive(playerid);
        }
        if(!(0 <= extra2 <= sizeof(AccessoriesColorInfo)-1) || !(0 <= extra3 <= sizeof(AccessoriesColorInfo)-1))
        {
            SendError(playerid, "Цвет должен быть от 0 до %d.", sizeof(AccessoriesColorInfo)-1);
            return ShowDialogEditInventoryGive(playerid);
        }
        _acc_wear = float(extra1);
        _mc1 = extra2;
        _mc2 = extra3;
        //give accessories
        SendAccess(playerid, "Вы выдали \"%s\" [%.1f] (%s/%s).", ItemsInfo[item_id][iName], float(extra1), AccessoriesColorInfo[extra2][acName], AccessoriesColorInfo[extra3][acName]);

        Log(LOG_player, INFO, "Admin: %s[%d](%s %s) выдал offline[%d] %s (%d.0 %s/%s). | #EPR",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            ownerID, ItemsInfo[item_id][iName], extra1, AccessoriesColorInfo[extra2][acName], AccessoriesColorInfo[extra3][acName]);
    }
    else if(ItemsInfo[item_id][iType] == TYPE_ITEMS_SKINS || ItemsInfo[item_id][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        //give skin adn vehicle tune
        SendAccess(playerid, "Вы выдали \"%s\".", ItemsInfo[item_id][iName]);

        Log(LOG_player, INFO, "Admin: %s[%d](%s %s) выдал offline[%d] %s | #EPR",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            ownerID, ItemsInfo[item_id][iName]);
    }
    else
        return SendError(playerid, "Другие типы не добавлены, пишите Вове.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "INSERT INTO `inventory` (`slot_id`, `owner_id`, `owner_type`, `item_id`, `amount`, `acc_mt1`, `acc_mt2`, `acc_wear`, `skin_wear`, `inv_acc_premium`, `inv_skin_premium`) \
            VALUES (%d, %d, %d, %d, %d, %d, %d, %f, %f, %d, %d)",
        free_slot, ownerID, INVENTORY_OWNER_TYPE_PLAYER,
        item_id, _amount, _mc1, _mc2, _acc_wear, _skin_wear, _acc_premium, _skin_premium);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

ShowDialogEditInventoryGive(playerid)
{
    STRING_GLOBAL[0] = EOS;
    new color_str[256];
    for(new i; i < sizeof(AccessoriesColorInfo); i++)
        format(color_str, sizeof(color_str), "%s %d - {%06x}%s"W"\n", color_str, i, i == 0 ? 0xFFFFFF : AccessoriesColorInfo[i][acColorRBG] & 0xFFFFFF, AccessoriesColorInfo[i][acName]);

    f(STRING_GLOBAL, ""W"Пример предмет:\n\
        "I"- ID, количество\n\
        \n\
        "W"Пример аксессуары:\n\
        "I"- ID, состояние, цвет #1, цвет #2\n\
        \n\
        "W"Цвета:\n%s\n\
        "W"Пример скины:\n\
        "I"- ID", color_str);
    return ShowPlayerDialog(playerid, D_EDITINV_GIVE, DIALOG_STYLE_INPUT, ""I"Выдача предмета", STRING_GLOBAL, "Выбрать", "Отмена");
}

EditCars_DestroyVehicle(vehicle_mysql_id)
{
    foreach(new v: Vehicle)
    {
        if(veh_info[v][v_mysql_id] == vehicle_mysql_id)
        {
            SaveVehicle(v);
            SaveVehicleDetails(v);

            DestroyVehicleVEx(v);
            break;
        }
    }
}

forward EditInventory_Menu(playerid);
public EditInventory_Menu(playerid)
{
    if(!cache_num_rows())
        return SendError(playerid, "Предмет не найден.");
    new itemID;
    cache_get_value_name_int(0, "item_id", itemID);
    SetPVarInt(playerid, #EPR_INV_ITEMID, itemID);
    if(ItemsInfo[itemID][iType] == TYPE_ITEMS_INVENTORY)
    {
        new itemAmount;
        cache_get_value_name_int(0, "amount", itemAmount);
        SetPVarInt(playerid, #EPR_INV_AMOUNT, itemAmount);
        ShowPlayerDialog(playerid, D_EDITITEM_MENU, DIALOG_STYLE_LIST, ""I"Редактирование предмета",
            ""I"[1]"W" Удалить\n\
            "I"[2]"W" Добавить\n\
            "I"[3]"W" Установить новое значение", "Выбрать", "Отмена");
    }
    else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_ACCESSORIES)
    {
        ShowPlayerDialog(playerid, D_EDITACC_MENU, DIALOG_STYLE_LIST, ""I"Редактирование аксессуара",
            ""I"[1]"W" Удалить\n\
            "I"[2]"W" Сменить модель\n\
            "I"[3]"W" Сменить состояние\n\
            "I"[4]"W" Сменить цвет #1\n\
            "I"[5]"W" Сменить цвет #2", "Выбрать", "Отмена");
    }
    else if(ItemsInfo[itemID][iType] == TYPE_ITEMS_SKINS || ItemsInfo[itemID][iType] == TYPE_ITEMS_VEHICLE_TUNE)
    {
        ShowPlayerDialog(playerid, D_EDITSKIN_MENU, DIALOG_STYLE_LIST, ""I"Редактирование скина",
             ""I"[1]"W" Удалить\n"I"[2]"W" Сменить модель", "Выбрать", "Отмена");
    }
    else SendError(playerid, "ID предмета не определено.");
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////
CMD:vmute(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /vmute [id]");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
    // VoiceChat_MutePlayer(params[0]);
    SendAccess(playerid, "Вы замутили войс чат игроку %s", get_name(params[0]));
    SendInfo(params[0], "%s замутил Вам войс чат", get_name(playerid));
    return 1;
}

CMD:vunmute(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /vunmute [id]");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
    // VoiceChat_UnMutePlayer(params[0]);
    SendAccess(playerid, "Вы размутили войс чат игроку %s", get_name(params[0]));
    SendInfo(params[0], "%s размутил Вам войс чат", get_name(playerid));
    return 1;
}

CMD:sethousetofamily(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    new house_id, family_idx;
    if(sscanf(params, "ii", house_id, family_idx)) return SendInfo(playerid, "Используйте: /sethousetofamily [houseID] [familyID]");
    if(!( 0 <= house_id < totalhouses)) return SendInfo(playerid, "Используйте: /sethousetofamily [houseID] [familyID]");
    if(!( 0 <= family_idx < family_count)) return SendInfo(playerid, "Используйте: /sethousetofamily [houseID] [familyID]");
    if(h_info[house_id][h_mysql_id] == INVALID_MYSQL_ID) return SendError(playerid, "Дом не задействован.");
    h_info[house_id][h_family_id] = FamilyData[family_idx][fMysqlID]; //Привязываем к дому << >> ИД БД семьи
    FamilyData[family_idx][fHouseID] = house_id; // Привязываем к семьи << >> ИД игры ДОМА

    SendAccess(playerid, "Вы сделали дом семейным.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] привязал к семье дом: №%d.", get_name(playerid), playerid, h_info[house_id][h_mysql_id]);
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    update_house(house_id);
    save_house(house_id);

    new targetid;
    for(new i; i <= h_info[house_id][h_squar]; i++)
    {
        if(h_info[house_id][h_r_user_id][i] != INVALID_MYSQL_ID)
        {
            targetid = GetPlayerUserID(h_info[house_id][h_r_user_id][i]);
            house_rent_leave(house_id, i);
            if(targetid != INVALID_PLAYER_ID) SendInfo(targetid, "Владелец дома сделал его семейным, Вы выселены.");
        }
    }

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `spawn` = 0 WHERE `spawn` = '3' AND `family_id` = %d",
        FamilyData[family_idx][fMysqlID]);
    mysql_tquery (con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `house_id` = %d WHERE `id` = %d",
        h_info[house_id][h_mysql_id], FamilyData[family_idx][fMysqlID]);
    mysql_tquery (con_bd, STRING_GLOBAL);

    UpdateFamilyType(family_idx);
    return 1;
}

CMD:wipebiz(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    mafia_count[0] =
    mafia_count[1] =
    mafia_count[2] =
    mafia_count[3] = 0;
    new idx, mafia_ids[] = {MAFIA_RM, MAFIA_LCN, MAFIA_YAKUDZA, BIKER, MAFIA_IRAN};
    for(new i = totalbizz-1; i != -1; i--)
    {
        if(b_info[i][b_mysql_id] == INVALID_MYSQL_ID) continue;
        if(idx >= 4) idx = 0;
        b_info[i][b_mafia] = mafia_ids[idx];
        save_bizz(i);
        update_bizz(i);
        MafiaCountBizz(mafia_ids[idx], 1);
        idx++;
    }
    return 1;
}

CMD:stopcapt(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;

    new gangzone = GetGangZoneID(playerid);
    if(gangzone == INVALID_CRIMINAL_ZONE_ID)
        return SendError(playerid, "Вы не на территории гетто.");
    if(IsGangRespawn(gangzone))
        return SendError(playerid, "Эта территория является респауном банды.");

    new i;
    if(Capture_Info[0][gGangZoneID] == gangzone)
        i = 0;
    else if(Capture_Info[1][gGangZoneID] == gangzone)
        i = 1;
    else return SendError(playerid, "Здесь не проходит капт.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Администратор %s[%d] остановил капт.", get_name(playerid), playerid);
    SendFractionMessage(Capture_Info[i][gFaction][0], 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(Capture_Info[i][gFaction][1], 0x33CC66FF, STRING_GLOBAL);

    GangZoneStopFlashForAll(GangZone_Info[Capture_Info[i][gGangZoneID]][gID]);
    GangZoneHideForAll(GangZone_Info[Capture_Info[i][gGangZoneID]][gID]);
    GangZoneShowForAll(GangZone_Info[Capture_Info[i][gGangZoneID]][gID], fraction_color[GangZone_Info[Capture_Info[i][gGangZoneID]][g_Fraction]]);

    foreach(new targetid: Player)
    {
        HideTextDrawForPlayer(targetid, TD_ID_CAPTURE);
        
        if(PlayerFixZone[targetid] != 0)
        {
            PlayerFixZone[targetid] = 0;
            GangZoneStopFlashForPlayer(targetid, i);
        }
    }

    Capture_Info[i][gGangZoneID] = INVALID_CRIMINAL_ZONE_ID;

    SetFractionSettings(Capture_Info[i][gFaction][0], fFreezeCapture, 0);
    SetFractionSettings(Capture_Info[i][gFaction][1], fFreezeCapture, 0);

    SetGangPC(Capture_Info[i][gFaction][0], INVALID_MYSQL_ID);
    SetGangPC(Capture_Info[i][gFaction][1], INVALID_MYSQL_ID);

    Capture_Info[i][gCount][0] = 0;
    Capture_Info[i][gCount][1] = 0;
    //Capture_Info[i][gTime][1] = timestamp+(60*50);
    Capture_Info[i][gStatus] = GANG_ZONE_NONE;//

    Capture_Info[i][gFaction][0] = 0;
    Capture_Info[i][gFaction][1] = 0;

    SendInfo(playerid, "Вы успешно остановили капт.");
    return 1;
}
alias:stopcapt("endcapt", "stopcapture");

CMD:stopbizwar(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;
    if(BizWar_Info[bWarTime] <= 0) return SendError(playerid, "В данный момент не проходит захват бизнеса.");
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] Администратор %s[%d] остановил захват бизнеса.", get_name(playerid), playerid);
    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

    foreach(new targetid: Player)
    {
        if(p_info[targetid][member] == BizWar_Info[bMafia][0] || p_info[targetid][member] == BizWar_Info[bMafia][1])
            HideTextDrawForPlayer(targetid, TD_ID_CAPTURE);
    }

    BizWar_Info[bMafia][0] = 0;
    BizWar_Info[bMafia][1] = 0;

    GangZoneStopFlashForAll(biz_war_gangzone);
    GangZoneHideForAll(biz_war_gangzone);
    GangZoneDestroy(biz_war_gangzone);
    biz_war_gangzone = -1;

    BizWar_Info[bWarTime] = 0;
    BizWar_Info[bCount][0] = 0;
    BizWar_Info[bCount][1] = 0;

    SendInfo(playerid, "Вы успешно остановили захват бизнеса.");
    return 1;
}

CMD:flip(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 1) return 1;
    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда недоступна хелперам.");

    new vehicleid;

    if(sscanf(params, "u", params[0]))
    {
        params[0] = playerid;
        SendInfo(playerid, "Используйте: /flip [ID игрока]");
    }
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не в сети.");
    if(GetPlayerState(params[0]) != PLAYER_STATE_DRIVER && GetPlayerState(params[0]) != PLAYER_STATE_PASSENGER)
        return SendError(playerid, "Игрок должен находиться в транспортном средстве.");

    SendAccess(playerid, "Вы перевернули транспортное средство %s [%d].", get_name(params[0]), params[0]);

    vehicleid = GetPlayerVehicleID(params[0]);

    new Float:fa, Float:x, Float:y, Float:z;
    GetVehicleRotationQuat(vehicleid, fa, x, y, z);
    GetVehicleZAngle(vehicleid, fa);
    SetVehicleZAngle(vehicleid, fa);
    return 1;
}

CMD:fixveh(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 2)
        return 1;

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /fixveh недоступна для хелперов.");

    new vehicleid = GetPlayerVehicleID(playerid);
    if(vehicleid == INVALID_VEHICLE_ID)
        return SendError(playerid, "Вы должны находиться в транспортном средстве.");

    if(GetVehicleModelEx(vehicleid) == 3610) SetVehicleHealth(vehicleid, 3000.0);
    RepairVehicle(vehicleid);
    SendAccess(playerid, "Вы отремонтировали транспортное средство.");
    return 1;
}

CMD:fixvehr(playerid, params[])
{
    if(p_info[playerid][admin] < 3 && p_info[playerid][youtube_adm] < 2)
        return 1;

    new Float:radius;
    if(sscanf(params, "f", radius)) return SendInfo(playerid, "Используйте: /fixvehr [радиус]");

    if(!(1.0 <= radius <= 100.0))
        return SendError(playerid, "Радиус должен быть не менее 1.0 и не более 100.0.");

    new
        Float:x,
        Float:y,
        Float:z;

    foreach(new i: Vehicle)
    {
        GetVehiclePos(i, x, y, z);

        if(IsPlayerInRangeOfPoint(playerid, radius, x, y, z))
        {
            if(GetVehicleModelEx(i) == 3610) SetVehicleHealth(i, 3000.0);
            RepairVehicle(i);
        }
    }

    SendAccess(playerid, "Вы отремонтировали транспортные средства в радиусе %0.2f.", radius);
    return 1;
}

CMD:fuelcars(playerid, params[])
{
    if(p_info[playerid][admin] < 5)
        return 1;

    foreach(new i: Vehicle)
        veh_info[i][v_fuel] = GetVehicleData(GetVehicleModelEx(i), E_VD_MAX_FUEL);

    SendAccess(playerid, "Вы заправили все транспортные средства.");
    return 1;
}

CMD:gethere(playerid, params[])
{
    if(p_info[playerid][admin] < 2 && p_info[playerid][youtube_adm] < 3 && p_temp[playerid][premiumgamer] != PREMIUM_GAME)
        return 1;

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /gethere [id игрока]");

    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!FD(playerid) && FD(params[0]))
        return 1;

    if(p_info[playerid][admin] < 3 && p_info[params[0]][admin] > 2 || FD(params[0]))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    if(GetPlayerState(playerid) == PLAYER_STATE_WASTED || GetPlayerState(params[0]) == PLAYER_STATE_WASTED)
        return 1;

    if(pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок находится в режиме наблюдения.");

    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(playerid, x, y, z);

    if(IsPlayerInAnyVehicle(params[0]))
    {
        TeleportVehicleToPos(GetPlayerVehicleID(params[0]), x + 1.0, y, z, 0.0, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
    }
    else
    {
        SetPlayerPos(params[0], x + 1.0, y, z);
        SetPlayerInterior(params[0], GetPlayerInterior(playerid));
        SetPlayerVirtualWorld(params[0], GetPlayerVirtualWorld(playerid));
    }

    UnloadUndergroundBots(params[0]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] телепортировал %s [%d] к себе.", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);

    SendAccess(playerid, "Вы телепортировали %s [%d] к себе.", get_name(params[0]), params[0]);
    SendInfo(params[0], "Администратор %s [%d] телепортировал Вас к себе.", get_name(playerid), playerid);

    Log(LOG_player, INFO, "%s[%d](%s %s) телепортировал к себе %s[%d](%s %s) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC");
    return 1;
}
alias:gethere("gh");

CMD:goto(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 2 && p_temp[playerid][premiumgamer] != PREMIUM_GAME)
        return 1;

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /goto недоступна для хелперов.");

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /goto [id игрока]");

    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!FD(playerid) && FD(params[0]))
        return 1;

    if(GetPlayerState(playerid) == PLAYER_STATE_WASTED || GetPlayerState(params[0]) == PLAYER_STATE_WASTED)
        return 1;

    if(pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок находится в режиме наблюдения.");

    if(p_info[playerid][admin] < p_info[params[0]][admin]) return 1;

    new
        Float:x,
        Float:y,
        Float:z;

    GetPlayerPos(params[0], x, y, z);

    if(IsPlayerInAnyVehicle(playerid))
    {
        TeleportVehicleToPos(GetPlayerVehicleID(playerid), x + 1.0, y, z, 0.0, GetPlayerInterior(params[0]), GetPlayerVirtualWorld(params[0]));
    }
    else
    {
        SetPlayerPos(playerid, x + 1.0, y, z);
        SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
        SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
    }

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] телепортировался %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);

    SendAccess(playerid, "Вы телепортировались к %s [%d].", get_name(params[0]), params[0]);
    SendInfo(params[0], "Администратор %s [%d] телепортировался к Вам.", get_name(playerid), playerid);

    Log(LOG_player, INFO, "%s[%d](%s %s) телепортировал к себе %s[%d](%s %s) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC");
    return 1;
}
alias:goto("g");

CMD:ptp(playerid, params[])
{
    if(p_info[playerid][admin] < 2 && p_info[playerid][youtube_adm] < 3)
        return 1;

    if(sscanf(params, "uu", params[0], params[1])) return SendInfo(playerid, "Используйте: /ptp [id игрока (кого)] [id игрока (к кому)]");

    if(params[0] == INVALID_PLAYER_ID || params[1] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(params[0] == params[1])
        return SendError(playerid, "Вы ввели одинаковые ID.");

    if(p_info[playerid][admin] < 3 && p_info[params[0]][admin] > 2 || FD(params[0]))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    new
        Float:x,
        Float:y,
        Float:z,
        player2_interior = GetPlayerInterior(params[1]),
        player2_world = GetPlayerVirtualWorld(params[1]);

    GetPlayerPos(params[1], x, y, z);

    if(IsPlayerInAnyVehicle(params[0]))
    {
        TeleportVehicleToPos(GetPlayerVehicleID(params[0]), x + 1.0, y, z, 0.0, player2_interior, player2_world, true);
    }
    else
    {
        SetPlayerPos(params[0], x + 1.0, y, z);
        SetPlayerInterior(params[0], player2_interior);
        SetPlayerVirtualWorld(params[0], player2_world);
    }

    UnloadUndergroundBots(params[0]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Вы телепортировали %s [%d] к %s [%d].", get_name(params[0]), params[0], get_name(params[1]), params[1]);
    SendAccess(playerid, STRING_GLOBAL);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] телепортировали Вас к %s [%d].", get_name(playerid), playerid, get_name(params[1]), params[1]);
    SendInfo(params[0], STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] телепортировал %s [%d] к %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0], get_name(params[1]), params[1]);
    SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) телепортировал %s[%d](%s %s) к %s[%d](%s %s) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC",
        get_name(params[1]), p_info[params[1]][ID], p_temp[params[1]][session_IP], IsPlayerMobile(params[1]) ? "Mobile": "PC");
    return 1;
}

CMD:hp(playerid, params[])
{
	if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 1 && p_temp[playerid][premiumgamer] != PREMIUM_GAME)
        return false;
	new vehicleid = GetPlayerVehicleID(playerid);
	SetPlayerHealth(playerid, 100.0);
	if(vehicleid  > 0)
	{
		SendInfo(playerid, "Вы пополнили HP и починили автомобиль.");
        if(GetVehicleModelEx(vehicleid) == 3610) SetVehicleHealth(vehicleid, 3000.0);
		RepairVehicle(vehicleid);
	}
	else
		SendInfo(playerid, "Вы пополнили HP.");
	return true;
}

CMD:freeze(playerid, params[])
{
    if(p_info[playerid][admin] < 2 && p_info[playerid][youtube_adm] < 3)
        return 1;

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда недоступна хелперам.");

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /freeze [id игрока]");

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(p_info[playerid][admin] < p_info[params[0]][admin])
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] заморозил %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    Fix_TogglePlayerControllable(params[0], 0);

    SendAccess(playerid, "Вы заморозили %s [%d].", get_name(params[0]), params[0]);
    SendInfo(params[0], "Администратор %s [%d] заморозил Вас.", get_name(playerid), playerid);

    WriteAdminLog(TYPE_LOG_FREEZE, playerid, get_name(params[0]), params[0]);
    return 1;
}
CMD:unfreeze(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 2)
        return 1;

    if(p_info[playerid][helper] == 0) return SendError(playerid, "Команда недоступна хелперам.");


    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /unfreeze [id игрока]");

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] разморозил %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    Fix_TogglePlayerControllable(params[0], 1);

    SendAccess(playerid, "Вы разморозили %s [%d].", get_name(params[0]), params[0]);
    SendInfo(params[0], "Администратор %s [%d] разморозил Вас.", get_name(playerid), playerid);

    WriteAdminLog(TYPE_LOG_UNFREEZE, playerid, get_name(params[0]), params[0]);
    return 1;
}
CMD:freezer(playerid, params[])
{
    if(p_info[playerid][admin] < 3 && p_info[playerid][youtube_adm] < 3) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /freezer [радиус]");
    if(params[0] > 100 || params[0] < 0) return SendError(playerid, "Радиус должен быть не менее 0 и не более 100.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] заморозил игроков в радиусе %d.", get_name(playerid), playerid, params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы заморозили игроков в радиусе %d.", params[0]);

    foreach(new i: Player)
    {
        if(!IsPlayerStream(params[0], playerid, i) || p_info[playerid][admin] < p_info[i][admin] || playerid == i) continue;
        SendInfo(i, "Администратор %s [%d] заморозил Вас.", get_name(playerid), playerid);
        Fix_TogglePlayerControllable(i, 0);
    }

    Log(LOG_player, INFO, "%s[%d](%s %s) заморозил игроков в радиусе %d | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[0]);
    return 1;
}
CMD:unfreezer(playerid, params[])
{
    if(p_info[playerid][admin] < 3 && p_info[playerid][youtube_adm] < 2) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /unfreezer [радиус]");
    if(params[0] > 100 || params[0] < 0) return SendError(playerid, "Радиус должен быть не менее 0 и не более 100.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] разморозил игроков в радиусе %d.", get_name(playerid), playerid, params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы разморозили игроков в радиусе %d.", params[0]);

    foreach(new i: Player)
    {
        if(!IsPlayerStream(params[0], playerid, i) || p_info[playerid][admin] < p_info[i][admin]) continue;
        SendInfo(i, "Администратор %s [%d] разморозил Вас.", get_name(playerid), playerid);
        Fix_TogglePlayerControllable(i, 1);
    }

    Log(LOG_player, INFO, "%s[%d](%s %s) разморозил игроков в радиусе %d | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[0]);
    return 1;
}
CMD:setamr(playerid, params[])
{
    if(p_info[playerid][admin] < 3 && p_info[playerid][youtube_adm] < 3) return 1;
    if(sscanf(params, "ii", params[0], params[1])) return SendInfo(playerid, "Используйте: /setamr [радиус] [кол-во брони]");
    if(params[0] > 100 || params[0] < 0) return SendError(playerid, "Радиус должен быть не менее 0 и не более 100.");
    if(params[1] > 100 || params[1] < 0) return SendError(playerid, "Кол-во брони должно быть не менее 0 и не более 100.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] выдал %d брони в радиусе %d.", get_name(playerid), playerid, params[1], params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы выдали %d брони в радиусе %d.", params[1], params[0]);

    foreach(new i: Player)
    {
        if(!IsPlayerStream(params[0], playerid, i) || p_info[playerid][admin] < p_info[i][admin]) continue;
        SendInfo(i, "Администратор %s [%d] выдал Вам %d брони.", get_name(playerid), playerid, params[1]);
        SetPlayerArmour(i, params[1]);
    }

    Log(LOG_player, INFO, "%s[%d](%s %s) выдал %d брони в радиусе %d | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[1], params[0]);
    return 1;
}
CMD:kick(playerid, params[])
{
    if(p_info[playerid][admin] < 2 && p_info[playerid][youtube_adm] < 4)
        return 1;

    new target, reason[144];
    if(sscanf(params, "us[144]", target, reason)) return SendInfo(playerid, "Используйте: /kick [id игрока] [причина]");

    if(target == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(p_info[target][admin] >= p_info[playerid][admin] || FD(target))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;

    //if(GetPVarInt(target, "BoneStol_ID")) return SendError(playerid, "Данный игрок в казино за столом, действие невозможно.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] кикнул %s [%d]. Причина: %s", get_name(playerid), playerid, get_name(target), target, reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    a_info[playerid][a_kick] = 1;
    MysqlUpdateAdminInt(playerid, "a_kick", a_info[playerid][a_kick]);
    WriteAdminLog(TYPE_LOG_KICK, playerid, get_name(target), target, reason);

    p_temp[target][dissconect_id] = 0;
    //p_info[target][p_countUseCheat] = 3;

    if(p_temp[target][premiumgamer] == PREMIUM_GAME)
        SendInfo(target, "[AdminBan] kick: %s", get_name(playerid));

    Kick(target);
    return 1;
}

CMD:ban(playerid, params[])
{
    if(p_info[playerid][admin] < 3)
        return 1;

    new target, days, reason[144];
    if(sscanf(params, "uis[144]", target, days, reason)) return SendInfo(playerid, "Используйте: /ban [id игрока] [кол-во дней] [причина]");

    if(target == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= days <= 30))
        return SendError(playerid, "Кол-во дней блокировки должно быть не менее 1 и не более 30.");

    if(p_info[target][admin] >= p_info[playerid][admin] || FD(target))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 7)) return 1;

    if(GetPVarInt(target, "BoneStol_ID")) return SendError(playerid, "Данный игрок в казино за столом, действие невозможно.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] заблокировал %s [%d] на %d %s. Причина: %s", get_name(playerid), playerid, get_name(target), target, days, Declension_ReturnWord(days, "день", "дня", "дней"), reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    new year, month, day;
    getdate(year, month, day);

    new unbandate;
    if(p_info[target][p_vip])
    {
        if(p_info[target][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) unbandate = (((days * 86400) / 100) * 60) + timestamp;
        else
        {
            switch(p_info[target][p_vip])
            {
                case 1: unbandate = (((days * 86400) / 100) * 90) + timestamp;
                case 2: unbandate = (((days * 86400) / 100) * 80) + timestamp;
                case 3: unbandate = (((days * 86400) / 100) * 70) + timestamp;
            }
        }
    }
    else unbandate = (days * 86400) + timestamp;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('%e', '%e', NOW(), %d, '%e')",
    get_name(playerid), get_name(target), unbandate, reason);
    mysql_tquery(con_bd, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_BAN, playerid, get_name(target), target, reason);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Внимание! Вас только что {"#cLIGHTRED"}забанили.\n\
        "W"Вас забанил(а): {"#cLIGHTRED"}%s\n\
        "W"Время: {"#cLIGHTRED"}%02d:%02d:%02d\n\
        "W"Дата: {"#cLIGHTRED"}%d.%d.%d\n\
        "W"Причина: {"#cLIGHTRED"}%s\n\
        "W"Разбан через: {"#cLIGHTRED"}%d дней\n\n\
        Форум поддержки: {"#cLIGHTRED"}"FORUM_URL"\n"W"Форум > Жалобы > {"#cLIGHTRED"}Жалобы на администрацию",
        get_name(playerid),
        timestamp_hour, timestamp_minute, timestamp_second,
        year, month, day,
        reason,
        days);
    ShowPlayerDialog(target,D_NULL,DIALOG_STYLE_MSGBOX, ""I"Информация", STRING_GLOBAL,"Закрыть","");

    if(p_info[target][warn] > 2) p_info[target][warn] = 0;
    p_temp[target][dissconect_id] = 2;

    if(p_temp[target][premiumgamer] == PREMIUM_GAME)
        SendInfo(target, "[AdminBan] ban: %s", get_name(playerid));

    Kick(target);

    a_info[playerid][a_ban] = 1;
    MysqlUpdateAdminInt(playerid, "a_ban", a_info[playerid][a_ban]);
    return true;
}

CMD:sban(playerid, params[])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    new target, days, reason[144];
    if(sscanf(params, "uis[144]", target, days, reason)) return SendInfo(playerid, "Используйте: /sban [id игрока] [кол-во дней] [причина]");

    if(target == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= days <= 30))
        return SendError(playerid, "Кол-во дней должно быть не менее 1 и не более 30.");

    if(p_info[target][admin] >= p_info[playerid][admin] || FD(target))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 7)) return 1;

    if(GetPVarInt(target, "BoneStol_ID")) return SendError(playerid, "Данный игрок в казино за столом, действие невозможно.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] скрыто заблокировал %s [%d] на %d %s. Причина: %s", get_name(playerid), playerid, get_name(target), target, days, Declension_ReturnWord(days, "день", "дня", "дней"), reason);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_SBAN, playerid, get_name(target), target, reason);

    if(FD(target)) return 1;

    new unbandate;
    if(p_info[target][p_vip])
    {
        if(p_info[target][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) unbandate = (((days * 86400) / 100) * 60) + timestamp;
        else
        {
            switch(p_info[target][p_vip])
                {
                    case 1: unbandate = (((days * 86400) / 100) * 90) + timestamp;
                    case 2: unbandate = (((days * 86400) / 100) * 80) + timestamp;
                    case 3: unbandate = (((days * 86400) / 100) * 70) + timestamp;
                }
            }
    } 
    else unbandate = (days * 86400) + timestamp;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('%e', '%e', NOW(), %d, '%e')",
    get_name(playerid), get_name(target), unbandate, reason);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "  Nik [%s]  R-IP [%s]  L-IP [%s]  IP [%s]", get_name(target), p_info[target][regIP], p_temp[target][session_IP], p_temp[target][session_IP]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    p_temp[target][dissconect_id] = 2;
    Kick(target);
    return 1;
}

CMD:offban(playerid, params[])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    new nickname[MAX_PLAYER_NAME], days, reason[144];
    if(sscanf(params, "s[24]is[144]", nickname, days, reason)) return SendInfo(playerid, "Используйте: /offban [никнейм] [кол-во дней] [причина]");

    if(!(1 <= days <= 30))
        return SendError(playerid, "Кол-во дней должно быть не менее 1 и не более 30.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 7)) return 1;

    if(strcmp(nickname, FD1, true) == 0 ||
        strcmp(nickname, FD2, true) == 0 ||
        strcmp(nickname, FD3, true) == 0 ||
        strcmp(nickname, FD4, true) == 0)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] заблокировал %s на %d %s. Причина: %s",
            get_name(playerid),
            playerid,
            nickname,
            days,
            Declension_ReturnWord(days, "день", "дня", "дней"),
            reason);

        SendMes(playerid, COLOR_LIGHTRED, STRING_GLOBAL);

        new give_id;
        sscanf(FD1, "i", give_id);
        if(give_id != INVALID_PLAYER_ID)
        {
            SendInfo(give_id, "Администратор %s [%d] пытался заблокировать Вас.", get_name(playerid), playerid);
        }
        return 1;
    }

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `table_ban` WHERE `Name_Player` = '%e' LIMIT 1",
    nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "OffBan", "issi",playerid,nickname,reason,days);

    a_info[playerid][a_offban] = 1;
    MysqlUpdateAdminInt(playerid, "a_offban", a_info[playerid][a_offban]);
    return 1;
}

forward OffBan(playerid,tmp[],reason[], days);
public OffBan(playerid,tmp[],reason[], days)
{
    if(cache_num_rows() > 0)
        return SendError(playerid, "Игрок уже заблокирован.");

    new unbandate;

    unbandate = timestamp + days*86400;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `table_ban` (`Name_Admin`, `Name_Player`, `Ban_Data`, `Unban_Data`, `Ban_Reason`) VALUES ('%e', '%e', NOW(), %d, '%e')",
    get_name(playerid), tmp, unbandate, reason);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] заблокировал %s на %d %s. Причина: %s", get_name(playerid), playerid, tmp, days, Declension_ReturnWord(days, "день", "дня", "дней"), reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_OFFBAN, playerid, tmp, INVALID_PLAYER_ID, reason);
    return 1;
}

CMD:msg(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(!(1 <= strlen(params) <= 80)) return SendError(playerid, "Кол-во символов не может быть менее 1 и более 80.");
    if(AdvertisingCheck(params)) return AdvertisingPunishment(playerid, params, 0);

    // Проверяем счетчик;
    if(GetPVarInt(playerid, "MSGAntiAttack") > 20) return OnPlayerSystemBan(playerid, "MSG-ATTACK");
    // Обновляем счетчик;
    SetPVarInt(playerid, "MSGAntiAttack", GetPVarInt(playerid, "MSGAntiAttack") + 4);

    SendMesAll(0xFFD700FF, "Администратор %s [%d]: "W"%s", get_name(playerid), playerid, params);

    Log(LOG_player, INFO, "%s[%d](%s %s) написал в /msg: %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params);
    return 1;
}

CMD:skick(playerid, params[])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    new target, reason[144];
    if(sscanf(params, "us[144]", target, reason)) return SendInfo(playerid, "Используйте: /skick [id игрока] [причина]");

    if(target == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине кика не может быть менее 1 и более 32.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;

    if(p_info[target][admin] >= p_info[playerid][admin] || FD(target))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");
    
    if(GetPVarInt(target, "BoneStol_ID")) return SendError(playerid, "Данный игрок в казино за столом, действие невозможно.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] скрытно кикнул %s [%d]. Причина: %s", get_name(playerid), playerid, get_name(target), target, reason);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_SKICK, playerid, get_name(target), target, reason);
    p_temp[target][dissconect_id] = 0;

    if(p_temp[target][premiumgamer] == PREMIUM_GAME)
        SendInfo(target, "[AdminBan] skick: %s", get_name(playerid));

    Kick(target);
    return 1;
}

CMD:unwarn(playerid, params[])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /unwarn [id игрока]");

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(0 == p_info[params[0]][warn])
        return SendError(playerid, "У игрока нет предупреждений.");

    p_info[params[0]][warn] -= 1;
    p_info[params[0]][warn_time] = 0;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `warn` = %d, `warn_time` = %d WHERE `id` = %d",
    p_info[params[0]][warn], p_info[params[0]][warn_time], p_info[params[0]][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] снял предупреждение %s [%d]. Предупреждений: %d.", get_name(playerid), playerid, get_name(params[0]), params[0], p_info[params[0]][warn]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы сняли %s [%d] предупреждение.", get_name(params[0]), params[0]);
    SendInfo(params[0], "Администратор %s [%d] снял Вам предупреждение.", get_name(playerid), playerid);
    return 1;
}

CMD:fwarn(playerid, params[])
{
    if(p_info[playerid][admin] < 5 && p_info[playerid][rang] < 9 && p_info[playerid][member] != MAYOR_LS) return 1;

    new target, reason[144];
    if(sscanf(params, "us[144]", target, reason)) return SendInfo(playerid, "Используйте: /fwarn [id игрока] [причина]");

    if(target == INVALID_PLAYER_ID || target == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(p_info[playerid][member] == MAYOR_LS && p_info[target][member] != MAYOR_LS)
    {
        switch(p_info[playerid][rang])
        {
            case 8:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_PD)
                    return SendError(playerid, "Игрок не состоит в полиции.");
            }
            case 7:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_ARMY)
                    return SendError(playerid, "Игрок не состоит в армии.");
            }
            case 6:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_MEDIC)
                    return SendError(playerid, "Игрок не состоит в больнице.");
            }
            case 5:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_SNN)
                    return SendError(playerid, "Игрок не состоит в радиоцентре.");
            }
            default: return SendError(playerid, "Вы не министр.");
        }
    }
    else
    {
        if(p_info[playerid][rang] <= p_info[target][rang]) return SendError(playerid, "У Вас слишком маленький ранг во фракции.");
        if(p_info[playerid][rang] < 9) return SendError(playerid, "Вы не можете пользоваться этой командой.");
        if(p_info[target][member] != p_info[playerid][member]) return SendError(playerid, "Игрок не состоит во фракции.");
    }
    if( p_info[target][leader] != 0 && p_info[playerid][admin] < 5) return SendError(playerid, "Лидеру невозможно выдать предупреждение");

    p_info[target][fwarn] += 1;
    if(p_info[target][fwarn] >= 3)
    {
        if(GetPlayerStatusCapture(target))
            HideTextDrawForPlayer(target, TD_ID_CAPTURE);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `log_fraction` (`PlayerID`, `Member`, `Rang`, `Type`, `Reason`) VALUES (%d, %d, %d, '1', '3 предупреждения')",
        p_info[target][ID], p_info[target][member], p_info[target][rang]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        /*
        p_info[target][ftop_gkills_week] = 
        p_info[target][ftop_gdeaths_week] = 0;
        p_info[target][ftop_gdamagegive_week] = 
        p_info[target][ftop_gdamagetake_week] = 0;
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `ftop_gkills_week` = 0, `ftop_gdeaths_week`  = 0, `ftop_gdamagegive_week` = 0.0, `ftop_gdamagetake_week` = 0.0 WHERE `id` = %d", p_info[target][ID]);
        mysql_tquery(con_bd, STRING_GLOBAL);
        */
    
        Iter_Remove(gFactionPlayers[p_info[target][member]], target);
        p_info[target][member] = 0;
        p_info[target][rang] = 0;
        p_info[target][fskin] = 0;
        Iter_Add(gFactionPlayers[p_info[target][member]], target);
        if(GetPlayerHouseID(target) != INVALID_HOUSE_ID) p_info[target][spawn] = 2;
        else p_info[target][spawn] = 0;
        p_info[target][fwork] = false;
        SetPlayerSkinEx(target);
        SetPlayerColor(target, fraction_color[0]);
        if(GetFactionCategory(p_info[target][member]) == FACTION_CATEGORY_PD || GetFactionCategory(p_info[target][member]) == FACTION_CATEGORY_FBI)
            p_temp[target][StatusOnDuty] = 0;
        save_player(target);

        f_ResetPlayerWeapons(target);

        SendInfo(target, "%s [%d] уволил Вас из фракции. Причина: %s", get_name(playerid), playerid, reason);
        SendAccess(playerid, "Вы уволили %s [%d] из фракции. Причина: %s", get_name(target), target, reason);
        return 1;
    }
    else
    {
        SendInfo(target, "%s [%d] выдал Вам предупреждение во фракции. Причина: %s", get_name(playerid), playerid, reason);
        SendAccess(playerid, "Вы выдали %s [%d] предупреждение во фракции.", get_name(target), target);
    }
    return 1;
}

CMD:funwarn(playerid, params[])
{
    if(p_info[playerid][admin] < 5 && p_info[playerid][rang] < 9 && p_info[playerid][member] != MAYOR_LS) return 1;

    new target, reason[144];
    if(sscanf(params, "us[144]", target, reason)) return SendInfo(playerid, "Используйте: /funwarn [id игрока] [причина]");

    if(target == INVALID_PLAYER_ID || target == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(p_info[playerid][member] == MAYOR_LS && p_info[target][member] != MAYOR_LS)
    {
        switch(p_info[playerid][rang])
        {
            case 8:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_PD)
                    return SendError(playerid, "Игрок не состоит в полиции.");
            }
            case 7:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_ARMY)
                    return SendError(playerid, "Игрок не состоит в армии.");
            }
            case 6:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_MEDIC)
                    return SendError(playerid, "Игрок не состоит в больнице.");
            }
            case 5:
            {
                if(GetFactionCategory(p_info[target][member]) != FACTION_CATEGORY_SNN)
                    return SendError(playerid, "Игрок не состоит в радиоцентре.");
            }
            default: return SendError(playerid, "Вы не министр.");
        }
    }
    else
    {
        if(p_info[playerid][rang] <= p_info[target][rang]) return SendError(playerid, "У Вас слишком маленький ранг во фракции.");
        if(p_info[playerid][rang] < 9) return SendError(playerid, "Вы не можете пользоваться этой командой.");
        if(p_info[target][member] != p_info[playerid][member]) return SendError(playerid, "Игрок не состоит во фракции.");
    }
    if(p_info[target][fwarn] <= 0)
        return SendError(playerid, "У игрока нет предупреждений.");

    p_info[target][fwarn] -= 1;

    SendAccess(playerid, "Вы сняли с %s [%d] предупреждение во фракции. Причина: %s", get_name(target), target, reason);
    SendInfo(target, "%s [%d] снял с Вас предупреждение во фракции. Причина: %s", get_name(playerid), playerid, reason);
    return 1;
}

CMD:awarn(playerid, params[])
{
    if( p_info[playerid][admin] < 5)
        return 1;

    new target, reason[144];
    if(sscanf(params, "us[144]", target, reason)) return SendInfo(playerid, "Используйте: /awarn [id игрока] [причина]");

    if(target == INVALID_PLAYER_ID || target == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(p_info[target][admin] < 1)
        return SendError(playerid, "Игрок не администратор.");

    if(p_info[playerid][admin] <= p_info[target][admin])
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    p_info[target][fwarn] += 1;
    if(p_info[target][fwarn] >= 3)
    {
        Iter_Remove(gAdmins, target);

        p_info[target][admin_pass] =
        p_info[target][admin] =
        p_info[target][youtube_adm] = 0;
        save_player(playerid);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `admin_logs` WHERE `name` = '%e'",
        get_name(target));
        mysql_tquery(con_bd, STRING_GLOBAL);

        SendInfo(target, "Администратор %s [%d] снял Вас с должности администратора. Причина: %s", get_name(playerid), playerid, reason);
        SendAccess(playerid, "Вы сняли %s [%d] с должности администратора. Причина: %s", get_name(target), target, reason);
    }
    else SendInfo(target, "Администратор %s [%d] выдал Вам админ. предупреждение. Причина: %s", get_name(playerid), playerid, reason);
    SendAccess(playerid, "Вы выдали %s [%d] админ. предупреждение. Причина: %s", get_name(target), target, reason);
    return 1;
}

CMD:aunwarn(playerid, params[])
{
    if( p_info[playerid][admin] < 5)
        return 1;

    new target, reason[144];
    if(sscanf(params, "us[144]", target, reason)) return SendInfo(playerid, "Используйте: /aunwarn [id игрока] [причина]");

    if(target == INVALID_PLAYER_ID || target == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(p_info[playerid][admin] <= p_info[target][admin])
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    if(p_info[target][fwarn] <= 0)
        return SendError(playerid, "У игрока нет предупреждений.");

    p_info[target][fwarn] -= 1;

    WriteAdminLog(TYPE_LOG_UNWARN, playerid, get_name(target), target, reason);

    SendAccess(playerid, "Вы сняли %s [%d] админ. предупреждение. Причина: %s", get_name(target), target, reason);
    SendInfo(target, "Администратор %s [%d] снял Вам админ. предупреждение. Причина: %s", get_name(playerid), playerid, reason);
    return 1;
}

CMD:warn(playerid, params[])
{
    if(p_info[playerid][admin] < 3)
        return 1;

    new target, days, reason[144];
    if(sscanf(params, "uis[144]", target, days, reason)) return SendInfo(playerid, "Используйте: /warn [id игрока] [кол-во дней] [причина]");

    if(target == INVALID_PLAYER_ID || target == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(!(1 <= days <= 7))
        return SendError(playerid, "Кол-во дней не может быть менее 1 и более 7.");

    if(p_info[target][admin] >= p_info[playerid][admin] || FD(target))
        return SendError(playerid, "У Вас слишком маленький уровень администратора.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 5)) return 1;

    if(GetPVarInt(target, "BoneStol_ID")) return SendError(playerid, "Данный игрок в казино за столом, действие невозможно.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `log_fraction` (`PlayerID`, `Member`, `Rang`, `Type`, `Reason`) VALUES (%d, %d, %d, '1', 'Предупреждение администрации')",
    p_info[target][ID], p_info[target][member], p_info[target][rang]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    if(GetPlayerStatusCapture(target))
        HideTextDrawForPlayer(target, TD_ID_CAPTURE);

    p_info[target][warn] += 1;
    p_info[target][leader] = 0;
    p_info[target][rang] = 0;
    Iter_Remove(gFactionPlayers[p_info[target][member]], target);
    p_info[target][member] = 0;
    Iter_Add(gFactionPlayers[p_info[target][member]], target);

    p_info[target][fwork] = false;

    /*
    p_info[target][ftop_gkills_week] = 
    p_info[target][ftop_gdeaths_week] = 0;
    p_info[target][ftop_gdamagegive_week] = 
    p_info[target][ftop_gdamagetake_week] = 0;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `ftop_gkills_week` = 0, `ftop_gdeaths_week`  = 0, `ftop_gdamagegive_week` = 0.0, `ftop_gdamagetake_week` = 0.0 WHERE `id` = %d", p_info[target][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    */

    if(p_info[target][warn] >= 3)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] заблокировал %s [%d] на 3 дня. Причина: 3 предупреждения.", get_name(playerid), playerid, get_name(target), target);
        SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "        Причина 3-его предупреждения: %s", reason);
        SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] заблокировал Вас на 3 дня | [3 предупреждения]. Причина: %s", get_name(playerid), playerid, reason);
        SendInfo(target, STRING_GLOBAL);

        f(STRING_GLOBAL,"%d %d %s", target, 3, reason);
        callcmd::ban(playerid, STRING_GLOBAL);
        return 1;
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал предупреждение %s [%d] на %d %s (%d из 3). Причина: %s", get_name(playerid), playerid, get_name(target), target, days, Declension_ReturnWord(days, "день", "дня", "дней"), p_info[target][warn], reason);
        SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

        if(p_info[target][p_vip])
        {
            if(p_info[target][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) p_info[target][warn_time] = (((days * 86400) / 100) * 60) + timestamp;
            else
            {
                switch(p_info[target][p_vip])
                {
                    case 1: p_info[target][warn_time] = (((days * 86400) / 100) * 90) + timestamp;
                    case 2: p_info[target][warn_time] = (((days * 86400) / 100) * 80) + timestamp;
                    case 3: p_info[target][warn_time] = (((days * 86400) / 100) * 70) + timestamp;
                }
            }
        } else p_info[target][warn_time] = (days * 86400) + timestamp;

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал Вам предупреждение на %d %s [%d/3]. Причина: %s", get_name(playerid), playerid, days, Declension_ReturnWord(days, "день", "дня", "дней"), p_info[target][warn], reason);
        SendInfo(target, STRING_GLOBAL);
    }

    a_info[playerid][a_warn] = 1;
    MysqlUpdateAdminInt(playerid, "a_warn", a_info[playerid][a_warn]);
    WriteAdminLog(TYPE_LOG_WARN, playerid, get_name(target), target, reason);

    p_temp[target][dissconect_id] = 1;

    if(p_temp[target][premiumgamer] == PREMIUM_GAME)
        SendInfo(target, "[AdminBan] warn: %s", get_name(playerid));

    Kick(target);
    return 1;
}
CMD:mute(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 4)
        return 1;
    
    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /mute недоступна для хелперов.");

    new target, minutes, reason[144];
    if(sscanf(params, "uis[144]", target, minutes, reason)) return SendInfo(playerid, "Используйте: /mute [id игрока] [кол-во минут] [причина]");

    if(target == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= minutes <= 300))
        return SendError(playerid, "Кол-во минут блокировки чата не может быть менее 1 и более 300.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал блокировку чата %s [%d] на %d %s. Причина: %s",
        get_name(playerid), playerid, get_name(target), target, minutes, Declension_ReturnWord(minutes, "минуту", "минуты", "минут"), reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    a_info[playerid][a_mute] = 1;
    MysqlUpdateAdminInt(playerid, "a_mute", a_info[playerid][a_mute]);

    if(p_info[target][p_vip])
    {
        if(p_info[target][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) p_info[target][mute] = ((minutes * 60) / 100) * 60;
        else
        {
            switch(p_info[target][p_vip])
            {
                case 1: p_info[target][mute] = ((minutes * 60) / 100) * 90;
                case 2: p_info[target][mute] = ((minutes * 60) / 100) * 80;
                case 3: p_info[target][mute] = ((minutes * 60) / 100) * 70;
            }
        }
    } else p_info[target][mute] = minutes * 60;


    // VoiceChat_MutePlayer(target);

    WriteAdminLog(TYPE_LOG_MUTE, playerid, get_name(target), target, reason);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал Вам блокировку чата на %d %s. Причина: %s",get_name(playerid), playerid, minutes, Declension_ReturnWord(minutes, "минуту", "минуты", "минут"), reason);
    SendInfo(target, STRING_GLOBAL);
    SendInfo(target, "Оставшееся кол-во времени до снятия блокировки чата: /time");
    return 1;
}
CMD:unmute(playerid, params[])
{
    if(p_info[playerid][admin] < 1)
        return 1;

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /unmute [id игрока]");

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /unmute недоступна для хелперов.");

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(0 == p_info[params[0]][mute])
        return SendError(playerid, "Игрок не имеет блокировки чата.");

    p_info[params[0]][mute] = 0;
    // VoiceChat_UnMutePlayer(params[0]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] снял блокировку чата %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_UNMUTE, playerid, get_name(params[0]), params[0]);

    SendAccess(playerid, "Вы сняли %s [%d] блокировку чата.", get_name(params[0]), params[0]);
    SendInfo(params[0], "Администратор %s [%d] снял Вам блокировку чата.", get_name(playerid), playerid);
    return 1;
}

CMD:rmute(playerid, params[])
{
    if(p_info[playerid][admin] < 1)
        return 1;

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /rmute недоступна для хелперов.");

    new target, minutes, reason[144];
    if(sscanf(params, "uis[144]", target, minutes, reason)) return SendInfo(playerid, "Используйте: /rmute [id игрока] [кол-во минут] [причина]");

    if(target == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(!(1 <= minutes <= 120))
        return SendError(playerid, "Кол-во минут блокировки репорта не может быть менее 1 и более 120.");

    if(!(1 <= strlen(reason) <= 32))
        return SendError(playerid, "Кол-во символов в причине не может быть менее 1 и более 32.");

    p_info[target][rmute] = minutes*60;
    save_player(target);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал блокировку репорта %s [%d] на %d %s. Причина: %s", get_name(playerid), playerid, get_name(target), target, minutes, Declension_ReturnWord(minutes, "минуту", "минуты", "минут"), reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    a_info[playerid][a_mute]++;
    MysqlUpdateAdminInt(playerid, "a_mute", a_info[playerid][a_mute]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал Вам блокировку репорта на %d %s. Причина: %s", get_name(playerid), playerid, minutes, Declension_ReturnWord(minutes, "минуту", "минуты", "минут"), reason);
    SendInfo(target, STRING_GLOBAL);
    return 1;
}
CMD:unrmute(playerid, params[])
{
    if(p_info[playerid][admin] < 1)
        return 1;

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /unrmute недоступна для хелперов.");

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /unrmute [id игрока]");

    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");

    if(0 == p_info[params[0]][rmute])
        return SendError(playerid, "Игрок не имеет блокировки репорта.");

    p_info[params[0]][rmute] = 0;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] снял блокировку репорта %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы сняли %s [%d] блокировку репорта.", p_info[params[0]][name], params[0]);
    SendInfo(playerid, "Администратор %s [%d] снял Вам блокировку репорта.", get_name(playerid), playerid);
    return 1;
}

CMD:unban(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    new nickname[MAX_PLAYER_NAME], reason[144];
    if(sscanf(params, "s[24]s[144]", nickname, reason)) return SendInfo(playerid, "Используйте: /unban [NickName] [Причина]");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `table_ban` WHERE `Name_Player`= '%e' LIMIT 1", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "un_ban", "iss", playerid, nickname, reason);
    return 1;
}

forward un_ban(playerid, names[], reason[]);
public un_ban(playerid, names[], reason[])
{
    if(!cache_num_rows())
        return SendError(playerid, "Игрок не заблокирован.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `table_ban` WHERE `Name_Player` = '%e'",
    names);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] разблокировал %s.", get_name(playerid), playerid, names);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    new str_reason[64];
    format(str_reason, sizeof(str_reason), "Причина: %s", reason);
    WriteAdminLog(TYPE_LOG_UNBAN, playerid, names, INVALID_PLAYER_ID, str_reason);
    return 1;
}
CMD:veh(playerid, params[])
{
    if(p_info[playerid][admin] < 4 && p_info[playerid][youtube_adm] < 3) return 1;
    new Float: pos[3];
    if(sscanf(params, "iii", params[0], params[1], params[2])) return SendInfo(playerid, "Используйте: /veh [id] [цвет № 1] [цвет № 2]");
    if(params[0] < 400 || (SRV_ID && p_info[playerid][admin] <= 4 && params[0] > 610)) return SendError(playerid, "ID модели должен быть не менее 400 и не более 610.");
    //if(params[0] < 400 || params[1] > 610) return SendInfo(playerid, "Используйте: /veh [id] [цвет № 1] [цвет № 2]");
    if(params[0] == 432 || params[0] == 520 || params[0] == 425) return SendError(playerid, "Данный транспорт нельзя создать.");
    GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
    new car = CreateVehicleVEx(NPO_NONE, NPO_NONE, params[0],pos[0],pos[1]+0.5,pos[2],90.0000000,params[1],params[2], 600);
    LinkVehicleToInterior(car, GetPlayerInterior(playerid));
    veh_info[car][v_admin] = 1;
    veh_info[car][v_lock] = 0;
    veh_info[car][v_fuel] = GetVehicleData(GetVehicleModelEx(car), E_VD_MAX_FUEL);

    Log(LOG_player, INFO, "%s[%d](%s %s) создал т/с <%s>(%d) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        GetVehicleName(car), GetVehicleModelEx(car));

    if(p_temp[playerid][premiumgamer] == PREMIUM_GAME)
    {
        for(new i; i != LIC_ALL; i++)
        {
            p_info[playerid][Lic][i] = 1;
            p_info[playerid][Lic_Warn][i] = 0;
            p_info[playerid][Lic_Time][i] = 8760;
        }
        OnPlayerUpdateLicData(playerid);
        PutPlayerInVehicle(playerid, car, 0);
    }
    return 1;
}
CMD:setskin(playerid, params[])
{
    if(p_info[playerid][admin] < 4 && p_info[playerid][youtube_adm] < 3 && p_temp[playerid][premiumgamer] != PREMIUM_GAME) return 1;
    if(sscanf(params, "ui", params[0], params[1])) return SendInfo(playerid, "Используйте: /setskin [id игрока] [id скина]");
    if(!IsPlayerConnected(params[0]) || params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(SRV_ID && !FD(playerid))
    {
        switch(params[1])
        {
            case 1..73, 75..311, 793..799, 907..909, 965, 999, 1194..1203: {}
            default: return SendError(playerid, "Неверный ID скина.");
        }
    }

    SendAccess(playerid, "Вы выдали %s [%d] временный скин %d.", get_name(params[0]), params[0], params[1]);
    SendInfo(params[0], "Администратор %s [%d] выдал Вам временный скин %d.", get_name(playerid), playerid, params[1]);

    SetPlayerSkin(params[0], params[1]);
    return 1;
}


CMD:recon(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 2)
        return 1;

    if(p_info[playerid][helper] == 1) return SendError(playerid, "Вам недоступна команда.");

    if(p_info[playerid][loggedIn] != 1)
        return SendError(playerid, "Вы не авторизованы.");

    if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
        return 1;

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /re [id игрока]");

    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");

    if(!FD(playerid) && FD(params[0]))
        return 1;

    if(pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок находится в режиме наблюдения.");

    if(pSpectateId[playerid] != INVALID_PLAYER_ID)
        pSpectatorId[pSpectateId[playerid]] = INVALID_PLAYER_ID;

    if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && 
        p_info[playerid][admin] > 0 &&
        !GetPVarInt(playerid, !"spawn_after_spectate_mode"))
            ShowTextDrawForPlayer(playerid, TD_ID_RECON_INFO);

    if(p_info[playerid][admin] < 5)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] начал следить за %s [%d].", get_name(playerid), playerid, get_name(params[0]), params[0]);
        SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);
    }
    SendAccess(playerid, "Вы начали следить за %s [%d].", get_name(params[0]), params[0]);

    if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
    {
        GetPlayerPos(playerid, pPosBeforeSpectateX[playerid], pPosBeforeSpectateY[playerid], pPosBeforeSpectateZ[playerid]);
        pInteriorBeforeSpectate[playerid] = GetPlayerInterior(playerid);
        pVirtualWorldBeforeSpectate[playerid] = GetPlayerVirtualWorld(playerid);
        SetPVarInt(playerid, !"spawn_after_spectate_mode", 2);
    }
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));
    SetPlayerInterior(playerid, GetPlayerInterior(params[0]));

    pSpectateId[playerid] = params[0];
    pSpectatorId[params[0]] = playerid;

    TogglePlayerSpectating(playerid, 1);

    if(IsPlayerInAnyVehicle(params[0]))
        PlayerSpectateVehicle(playerid, GetPlayerVehicleID(params[0]), SPECTATE_MODE_NORMAL);
    else
        PlayerSpectatePlayer(playerid, params[0], SPECTATE_MODE_NORMAL);

    if(p_temp[params[0]][premiumgamer] == PREMIUM_GAME)
        SendInfo(params[0], "[AdminRecon] start /re: %s", get_name(playerid));
    return 1;
}
alias:recon("re", "spectate", "spec");

CMD:reconoff(playerid, params[])
{
    if(GetPlayerState(playerid) == PLAYER_STATE_WASTED)
        return 1;
    if(pSpectateId[playerid] == INVALID_PLAYER_ID)
        return SendError(playerid, "Вы не находитесь в режиме наблюдения.");
    TogglePlayerSpectating(playerid, 0);

    if((p_info[playerid][admin] > 0 || p_info[playerid][youtube_adm] >= 2) && !GetPVarInt(playerid, #BODY_MDC_USE))
    {
        HideTextDrawForPlayer(playerid, TD_ID_RECON_INFO);
        HideTextDrawForPlayer(playerid, TD_ID_RECON_PANEL);
    }
    if(GetPVarInt(playerid, #BODY_MDC_USE))
    {
        MDC_PAGE(playerid, PAGE_MEMBERS);
        if(GetPVarInt(playerid, #CCTV_VEH)) SetTimerEx("CCTV_VEH_TIMER", 1000, false, "i", playerid);
        DeletePVar(playerid, #BODY_MDC_USE);
    }
    if(p_temp[pSpectateId[playerid]][premiumgamer] == PREMIUM_GAME)
        SendInfo(pSpectateId[playerid], "[AdminRecon] end /re: %s", get_name(playerid));

    pSpectatorId[pSpectateId[playerid]] = INVALID_PLAYER_ID;
    pSpectateId[playerid] = INVALID_PLAYER_ID;

    SendAccess(playerid, "Вы вышли из режима слежения.");


    return 1;
}
alias:reconoff("reoff", "spectateoff", "specoff");

////bots functions:
CMD:bregip(playerid, params[])
{
    if(p_temp[playerid][premiumgamer] != PREMIUM_GAME) return 1;
    if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Используйте: /bregip [IP]");
    format(p_info[playerid][regIP], 16, params[0]);
    MysqlUpdatePlayerStr(playerid, "regip", p_info[playerid][regIP]);
    SendInfo(playerid, "[BOT] New regip: %s", params[0]);
    return 1;
}

CMD:bip(playerid, params[])
{
    if(p_temp[playerid][premiumgamer] != PREMIUM_GAME) return 1;
    if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Используйте: /bip [IP]");
    format(p_temp[playerid][session_IP], 16, params[0]);
    MysqlUpdatePlayerStr(playerid, "lastip", p_temp[playerid][session_IP]);
    SendInfo(playerid, "[BOT] New lastip: %s", params[0]);
    return 1;
}
////////////////////

CMD:makeadmin(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 7)
        return 1;

    new target, admin_level;
    if(sscanf(params, "ui", target, admin_level)) return SendInfo(playerid, "Используйте: /makeadmin [id игрока] [уровень]");

    if(target == INVALID_PLAYER_ID || !IsPlayerConnected(target))
        return SendError(playerid, "Игрок не найден.");

    if(!(0 <= admin_level <= 10))
        return SendError(playerid, "Уровень администратора не может быть менее 0 или более 10.");

    if(p_info[playerid][admin] < 10 && admin_level > 4)
        return SendError(playerid, "Уровень администратора не может быть менее 0 или более 4.");

    if(p_info[target][admin] == admin_level)
        return SendError(playerid, "Уровень администратора не может быть равен текущему.");

    if(admin_level == 0) // игрок сейчас админ и мы его снимаем с админки
    {
        if(p_info[target][admin] < 1)
            return SendError(playerid, "Игрок не администратор.");
        if(p_info[target][admin] >= p_info[playerid][admin])
            return SendError(playerid, "Уровень администратора выше чем Ваш.");

        Iter_Remove(gAdmins, target);

        p_info[target][admin_pass] = 0;

        SendAccess(playerid, "Вы сняли %s [%d] с должности администратора.", get_name(target), target);
        SendInfo(target, "Администратор %s [%d] снял Вас с должности администратора.", get_name(playerid), playerid);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `admin_logs` WHERE `name` = '%e'",
        get_name(target));
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    else // игрок сейчас не админ и мы его назначаем администратором, либо повышаем уровень администратора
    {
        SendAccess(playerid, "Вы назначили %s [%d] на должность администратора %d уровня.", get_name(target), target, admin_level);
        SendInfo(target, "Администратор %s [%d] назначил Вас на должность администратора %d уровня.", get_name(playerid), playerid, admin_level);

        if(p_info[target][admin] == 0) // игрок не админ и мы его назначаем
        {
            if(0 == Iter_Contains(gAdmins, target))
                Iter_Add(gAdmins, target);

            p_info[target][admin_pass] = 100000 + random(899999);
            SendInfo(target, "Ваш пароль от панели администратора: %d.", p_info[target][admin_pass]);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `admin_logs` WHERE `name` = '%e'",
            get_name(target));
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `admin_logs` (`name`) VALUES ('%e')",
            get_name(target));
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }

    p_info[target][admin] = admin_level;
    save_player(target);
    return 1;
}

CMD:checktesters(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 7)
        return 1;

    CHECK_TESTERS = !CHECK_TESTERS;
    SendInfo(playerid, "Вы %s проверку тестеров.", (CHECK_TESTERS == false) ? ("отключили") : ("включили"));
    return 1;
}

CMD:deladmin(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 6)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /deladmin [никнейм]");

    if(GetPlayerID(params) != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок в игре.");


    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `admin` FROM `accounts` WHERE `name` = '%e' LIMIT 1", params);
    mysql_tquery(con_bd, STRING_GLOBAL, "DeleteAdmin_Callback", "is", playerid, params);
    return 1;
}

forward DeleteAdmin_Callback(playerid, nickname[]);
public DeleteAdmin_Callback(playerid, nickname[])
{
    if(!cache_num_rows())
        return SendError(playerid, "Игрок не администратор.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `admin` = 0, `admin_pass` = 0 WHERE `name` = '%e' LIMIT 1", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `admin_logs` WHERE `name` = '%e'", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] снял %s с должности администратора.", get_name(playerid), playerid, nickname);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы сняли %s с должности администратора.", nickname);
    return 1;
}

CMD:templeader(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;
    p_temp[playerid][p_listitem][39] = playerid;
    STRING_GLOBAL[0] = EOS;
    for (new i = 1; i < MAX_FRACTIONS; i++)
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i, GetFractionName(i));

    STRING_MIN[0] = EOS;
    format(STRING_MIN, sizeof(STRING_MIN), ""I"%s", get_name(playerid));
    ShowPlayerDialog(playerid, D_MAKE_LEADER, DIALOG_STYLE_LIST, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:makeleader(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return true;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /makeleader [id игрока]");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(p_info[params[0]][member]) return SendError(playerid, "Игрок во фракции.");
    if(p_info[params[0]][warn]) return SendError(playerid, "У игрока есть предупреждение.");
    p_temp[playerid][p_listitem][39] = params[0];
    STRING_GLOBAL[0] = EOS;
    for (new i = 1; i < MAX_FRACTIONS; i ++)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i, GetFractionName(i));
    }
    STRING_MIN[0] = EOS;
    format(STRING_MIN, sizeof(STRING_MIN), ""I"%s", get_name(params[0]));
    ShowPlayerDialog(playerid, D_MAKE_LEADER, DIALOG_STYLE_LIST, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:create(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""I"[1]"W" Создать дом\tCоздано: %d\n"I"[2]"W" Создать бизнес\tСоздано: %d",totalhouses,totalbizz);
    return ShowPlayerDialog(playerid, D_CREATE, DIALOG_STYLE_LIST, ""I"Меню создания", STRING_GLOBAL, "Выбор","Закрыть");
}

CMD:apanel(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;
    ShowApanelDialog(playerid);
    return 1;
}

CMD:phone_buy_number(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10)
        return 1;

    if(PhoneBuyNumber == false) return SendError(playerid, "Очереди на приобретение номера телефонов нет.");

    PhoneBuyNumber = false;

    SendInfo(playerid, "Вы очистили очередь на приобретение номера телефона.");
    return 1;
}

ShowApanelDialog(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
    "I"[1]"W" Стоимость игровой валюты\t%d$\n\
    "I"[2]"W" Кол-во опыта\t%d EXP\n\
    "I"[3]"W" Настройка античита\t[OLD]\n\
    "I"[4]"W" Настройка античита\t[VAC]\n\
    "I"[5]"W" Зарплаты на работах\t%d\n\
    "I"[6]"W" Курс FM\t%d\n\
    "I"[7]"W" Сделать PayDay\n\
    "I"[8]"W" Настройки сервера",
    ServerInfo[Donate], ServerInfo[Experian], ServerInfo[Salary], ServerInfo[DonationMultiplier]);
    ShowPlayerDialog(playerid, D_APANEL, DIALOG_STYLE_TABLIST, ""I"Панель администратора", STRING_GLOBAL, "Принять", "Отмена");
    return 1;
}

ShowDialogServerInfo(playerid)
{
    new SI_NameStatusUse[][] = {"{"#cRED"}[Отключено]", "{"#cGREEN"}[Включено]"},
        SI_NameStatus[][] = {"{"#cRED"}[Отключено]", "{"#cGREEN"}[Включено]", "{"#cBLUE"}[Только PC]", "{"#cBLUE"}[Только Mobile]"};
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
        "I"[1]"W" Почтовый ящик \t%s\n\
        "I"[2]"W" Регистрация через E-Mail\t%s\n\
        "I"[3]"W" Регистрация на сервере\t%s\n\
        "I"[4]"W" Блокировка INVALID CLIENT\t%s\n\
        "I"[5]"W" Roulette System\t%s\n\
        "I"[6]"W" Case System\t%s\n\
        "I"[7]"W" Отображение REAL CARS\t%s\n\
        "I"[8]"W" Отображение NEW SKINS\t%s\n\
        "I"[9]"W" AntiDM System\t%s\n\
        "I"[10]"W" Заморозка при DM\t%s\n\
        "I"[11]"W" Мусорные баки\t%s\n\
        "I"[12]"W" VK Security\t%s\n\
        "I"[13]"W" TG Security\t%s\n\
        "I"[14]"W" SECURITY BOT URL\t%0.5s...\n\
        "I"[15]"W" Monitoring BizzOnline\t%s\n\
        "I"[16]"W" Авто-логин по SecretID\t%s",
        SI_NameStatusUse[ServerInfo[MailerStatus]],
        SI_NameStatus[ServerInfo[RegistrationMail]],
        SI_NameStatus[ServerInfo[RegistrationStatus]],
        SI_NameStatusUse[ServerInfo[BlockInvalidClient]],
        SI_NameStatusUse[ServerInfo[RouletteSystem]],
        SI_NameStatusUse[ServerInfo[CaseSystem]],
        SI_NameStatusUse[ServerInfo[RealCarsStatus]],
        SI_NameStatusUse[ServerInfo[RealSkinsStatus]],
        SI_NameStatusUse[ServerInfo[AntiDMSystem]],
        SI_NameStatusUse[ServerInfo[FreezeOnDM]],
        SI_NameStatusUse[ServerInfo[TrashSystem]],
        SI_NameStatusUse[ServerInfo[VKSecurity]],
        SI_NameStatusUse[ServerInfo[TGSecurity]],
        ServerInfo[SecurityBotURL],
        SI_NameStatusUse[ServerInfo[OnlineBizzSystem]],
        SI_NameStatusUse[ServerInfo[AutoLoginUID]]
    );
    ShowPlayerDialog(playerid, D_APANEL_SERVER_SETTINGS, DIALOG_STYLE_TABLIST, ""I"Настройки сервера", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:setoffpass(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;

    new player_name[MAX_PLAYER_NAME];
    new player_main[32];
    if(sscanf(params, "s[24]s[32]", player_name, player_main)) return SendInfo(playerid, "Используйте: /setoffpass [никнейм] [пароль]");
    if(strlen(player_main) < 6 || strlen(player_main) > 15) return SendInfo(playerid, "Пароль должен быть не менее 6 и не более 15 символов.");

    bcrypt_hash(player_main, BCRYPT_COST, "OnPasswordHashedCMD", "ds", playerid, player_name);
    return 1;
}
forward OnPasswordHashedCMD(playerid, player_name[]);
public OnPasswordHashedCMD(playerid, player_name[])
{
    new hash[BCRYPT_HASH_LENGTH + 1];
    bcrypt_get_hash(hash);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `password` = '%e' WHERE `name` = '%e' LIMIT 1",
    hash, player_name);
    mysql_tquery(con_bd, STRING_GLOBAL);

    SendAccess(playerid, "Вы изменили %s пароль.", player_name);

    Log(LOG_player, INFO, "%s[%d](%s %s) изменил %s пароль от аккаунта | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        player_name);
    return 1;
}

CMD:setoffmail(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;

    new player_name[MAX_PLAYER_NAME];
    new newmail[32];
    if(sscanf(params, "s[24]s[32]", player_name, newmail)) return SendInfo(playerid, "Используйте: /setoffmail [никнейм] [почта]");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `mail` = '%e'", newmail);
    mysql_tquery(con_bd, STRING_GLOBAL, "CheckUseEMail", "dss", playerid, player_name, newmail);
    return 1;
}

forward CheckUseEMail(playerid, player_name[], newmail[]);
public CheckUseEMail(playerid, player_name[], newmail[])
{
    new rows;
    cache_get_row_count(rows);
    if(rows) return SendError(playerid, "Почта уже используется.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `mail` = '%e' WHERE `name` = '%e' LIMIT 1", newmail, player_name);
    mysql_tquery(con_bd, STRING_GLOBAL);

    SendAccess(playerid, "Вы изменили %s почту на %s.", player_name, newmail);

    Log(LOG_player, INFO, "%s[%d](%s %s) изменил %s почту на %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        player_name, newmail);
    return 1;
}

CMD:admin(playerid, params[])
{
    if(p_info[playerid][admin] < 1)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /a [текст]");

    STRING_GLOBAL[0] = EOS;
    if(p_info[playerid][helper] == 1) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[H-1] %s [%d]: %s", get_name(playerid), playerid, params);  
    else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A-%d] %s [%d]: %s", p_info[playerid][admin], get_name(playerid), playerid, params);
    SendAdminMessage(0x84CC33FF, STRING_GLOBAL);
    return 1;
}

alias:admin("a");
CMD:tphouse(playerid, params[])
{
    if(p_info[playerid][admin] < 3)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /tph(ouse) [id дома]");

    new
        houseId = strval(params);

    if(!(0 <= houseId < totalhouses) || h_info[houseId][h_mysql_id] == INVALID_MYSQL_ID)
        return SendError(playerid, "Неверный ID дома.");

    SetPlayerPos(playerid, h_info[houseId][h_enter][0] + 1.0, h_info[houseId][h_enter][1], h_info[houseId][h_enter][2]);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerInterior(playerid, 0);

    SendAccess(playerid, "Вы телепортировались к дому.");
    return 1;
}
alias:tphouse("tph");

CMD:tpbiz(playerid, params[])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /tpbiz [id бизнеса]");

    new
        bizz_id = strval(params);

    if(!(0 <= bizz_id < totalbizz) || b_info[bizz_id][b_mysql_id] == INVALID_MYSQL_ID)
        return SendError(playerid, "Неверный ID бизнеса.");

    SetPlayerPos(playerid, b_info[bizz_id][b_enter][0] + 1.0, b_info[bizz_id][b_enter][1], b_info[bizz_id][b_enter][2]);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerInterior(playerid, 0);

    SendAccess(playerid, "Вы телепортированы к бизнесу.");
    return 1;
}

CMD:checksecurity(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Используйте: /checksecurity [никнейм]");
    if(!(3 <= strlen(params[0]) <= 20)) return  SendInfo(playerid, "Используйте: /checksecurity [никнейм]");
    new targetid = GetPlayerID(params[0]);
    if(targetid != INVALID_PLAYER_ID)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, ""I"%s\n\n\
            "W"E-Mail: %s | %s\n\
            "W"Google Auth: %s\n\
            "W"Вконтакте: %s\n\
            "W"Telegram: %s", params[0], 
            p_info[params[0]][mail], !IsMailConfirmed(targetid) ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено",
            strlen(p_info[targetid][google_code]) < 5 ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено",
            !IsVKConfirmed(targetid) ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено",
            !IsTGConfirmed(targetid) ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено");
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация по игроку:", STRING_GLOBAL, "Далее", "Отмена");
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `mail`, `email_confirmed`, `google_code`, `vk_userid`, `vk_confirmed`, `tg_userid`, `tg_confirmed` FROM `accounts` WHERE `name` = '%e' LIMIT 1", params[0]);
        mysql_tquery(con_bd, STRING_GLOBAL, "GetPlayerSecurityInfo", "is", playerid, params[0]);
    }
    Log(LOG_player, INFO, "%s[%d](%s %s) просмотрел инфу о защитеаккаунта %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[0]);
    return 1;
}

forward GetPlayerSecurityInfo(playerid, nickname[24]);
public GetPlayerSecurityInfo(playerid, nickname[24])
{
    if(p_info[playerid][admin] < 7) return 1;

    new _mail[64], _google_code[32], _email_confirmed, _vk_userid, _vk_confirmed, _tg_userid, _tg_confirmed;

    cache_get_value_name(0,"mail", _mail, 64);
    cache_get_value_name(0,"google_code", _google_code, 32);
    cache_get_value_name_int(0,"email_confirmed", _email_confirmed);
    cache_get_value_name_int(0,"vk_userid", _vk_userid);
    cache_get_value_name_int(0,"vk_confirmed",_vk_confirmed);
    cache_get_value_name_int(0,"tg_userid", _tg_userid);
    cache_get_value_name_int(0,"tg_confirmed", _tg_confirmed);

    new _vk, _tg;
    if(_vk_confirmed != 0 && _vk_userid != 0) _vk = 1;
    if(_tg_confirmed != 0 && _tg_userid != 0) _tg = 1;

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""I"%s\n\n\
        "W"E-Mail: %s | %s\n\
        "W"Google Auth: %s\n\
        "W"Вконтакте: %s\n\
        "W"Telegram: %s", nickname, _mail,
        _email_confirmed == 0 ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено",
        strlen(_google_code) < 5 ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено",
        _vk == 0 ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено",
        _tg == 0 ? "{"#cLIGHTRED"}Не подключено" : "{33CC66}Подключено");
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация по игроку:", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:delsecurity(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "s[24]", params[0])) return SendInfo(playerid, "Используйте: /delsecurity [никнейм]");
    if(!(3 <= strlen(params[0]) <= 20)) return  SendInfo(playerid, "Используйте: /delsecurity [никнейм]");
    new targetid = GetPlayerID(params[0]);
    if(targetid != INVALID_PLAYER_ID)
    {
        p_info[targetid][mail][0] = EOS;
        p_info[targetid][google_code][0] = EOS;
        p_info[targetid][email_confirmed] =
        p_info[targetid][vk_userid] = 
        p_info[targetid][vk_confirmed] = 
        p_info[targetid][tg_userid] = 
        p_info[targetid][tg_confirmed] = 0;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), 
            "UPDATE `accounts` SET `mail` = '', `email_confirmed` = 0, `google_code` = '', `vk_userid` = 0, `vk_confirmed` = 0, `tg_userid` = 0, `tg_confirmed` = 0 WHERE `id` = %d", p_info[targetid][ID]);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), 
            "UPDATE `accounts` SET `mail` = '', `email_confirmed` = 0, `google_code` = '', `vk_userid` = 0, `vk_confirmed` = 0, `tg_userid` = 0, `tg_confirmed` = 0 WHERE `name` = '%e'", params[0]);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    SendAccess(playerid, "Вы удалили защиту с аккаунта %s", params[0]);

    Log(LOG_player, INFO, "%s[%d](%s %s) удалил защиту с аккаунта %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[0]);
    return 1;
}

CMD:setname(playerid, params[])
{
    if(p_info[playerid][admin] < 3)
        return 1;

    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /setname [id игрока]");
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не в сети.");
    if(GetPVarType(params[0], "CHANGE_NICK:FREE") != 1)
        return SendError(playerid, "Игрок не подавал заявление на изменение никнейма.");

    SendInfo(playerid, "Попробуйте обновленную версию: /changename.");

    new new_nickname[MAX_PLAYER_NAME+1];
    GetPVarString(params[0], "NewNickName", new_nickname, MAX_PLAYER_NAME);
    DeletePVar(params[0], "NewNickName");

    if(!(3 <= strlen(new_nickname) <= 20))
        return SendError(playerid, "Игрок ввел неверный ник.");
    ClearChangeNick(params[0]);

    SendMesAll(0xFFD700FF, "Внимание! "W"%s [%d] изменил никнейм на %s.", get_name(params[0]), params[0], new_nickname);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] одобрил заявление на изменение никнейма %s [%d] на %s.", get_name(playerid), playerid, get_name(params[0]), params[0], new_nickname);
    SendAdminMessage(0x33CC66FF, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_SETNICK, playerid, get_name(params[0]), params[0]);
    SetPlayerNickName(params[0], new_nickname);
    return 1;
}

CMD:changename(playerid)
{
    if(p_info[playerid][admin] < 3)
        return 1;

    new new_nickname[MAX_PLAYER_NAME+1];
    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_CHANGE_NICK; i++)
    {
        if(ChangeNickName[i] != INVALID_PLAYER_ID)
        {
            GetPVarString(ChangeNickName[i], "NewNickName", new_nickname, MAX_PLAYER_NAME);
            f(STRING_GLOBAL, "%s"I"[%d]"W" %s >> %s\n", STRING_GLOBAL, i+1, get_name(ChangeNickName[i]), new_nickname);
        }
        else
            f(STRING_GLOBAL, "%s"I"[%d]"W" -\n", STRING_GLOBAL, i+1);
    }
    ShowPlayerDialog(playerid, D_CHANGENICK_LIST, DIALOG_STYLE_LIST, ""I"Смена ника", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;

}

SetChangeNick(playerid)
{
    for(new i; i < MAX_CHANGE_NICK; i++)
    {
        if(ChangeNickName[i] == INVALID_PLAYER_ID)
        {
            ChangeNickName[i] = playerid;
            return 1;
        }
    }
    return 0;
}

ClearChangeNick(playerid = INVALID_PLAYER_ID)
{
    if(playerid == INVALID_PLAYER_ID)
    {
        for(new i = MAX_CHANGE_NICK-1; i != -1; i--)
        {
            ChangeNickName[i] = INVALID_PLAYER_ID;
        }
    }
    else 
    {
        for(new i = MAX_CHANGE_NICK-1; i != -1; i--)
        {
            if(ChangeNickName[i] == playerid)
            {
                ChangeNickName[i] = INVALID_PLAYER_ID;
                break;
            }
        }
    }
}

CMD:ahelp(playerid, params[])
{
    if(p_info[playerid][admin] != 0)
    {
        ShowPlayerDialog(playerid, D_AHELP, DIALOG_STYLE_LIST, ""I"Команды администратора", "\
            "I"[1]"W" Уровень - 1\n\
            "I"[2]"W" Уровень - 2\n\
            "I"[3]"W" Уровень - 3\n\
            "I"[4]"W" Уровень - 4\n\
            "I"[5]"W" Уровень - 5\n\
            "I"[6]"W" Уровень - 6\n\
            "I"[7]"W" Уровень - 7", "Далее", "Отмена");
    }
    return 1;
}

cmd:sba(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    new bizzId;
    if(sscanf(params, "i", bizzId)) return SendInfo(playerid, "Используйте: /sba [bizzId]");
    if(bizzId < 0 || bizzId > MAX_BIZZ) return 1;

    new Float:pAng;
    GetPlayerFacingAngle(playerid, pAng);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `biz` SET `b_enterA` = '%f' WHERE `b_mysql_id` = %d",
        pAng, b_info[bizzId][b_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    SendAdminMessage(COLOR_RED, STRING_GLOBAL);

    b_info[bizzId][b_enter][3] = pAng;

    save_bizz(bizzId);
    update_bizz(bizzId);

    SendAccess(playerid, "Вы изменили угол поворота выхода.");
    return 1;
}

cmd:sha(playerid, params[])
{
    if(/*!FD(playerid) || */p_info[playerid][admin] < 10) return 1;
    new houseId;
    if(sscanf(params, "i", houseId)) return SendInfo(playerid, "Используйте: /sha [houseID]");
    if(houseId < 0 || houseId > MAX_HOUSE) return 1;

    new Float:pAng;
    GetPlayerFacingAngle(playerid, pAng);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `house` SET `h_entera` = '%f' WHERE `h_mysql_id` = %d",
    pAng, h_info[houseId][h_mysql_id]);
    SendAdminMessage(COLOR_RED, STRING_GLOBAL);

    //if(SRV_ID == 0) WriteLog("zhouse", STRING_GLOBAL);
    h_info[houseId][h_enter][3] = pAng;

    save_house(houseId);
    update_house(houseId);

    SendAccess(playerid, "Вы изменили угол поворота выхода.");
    return 1;
}

cmd:addhousegate(playerid, params[])
{
    if(/*!FD(playerid) || */p_info[playerid][admin] < 10) return 1;
    new houseId;
    if(sscanf(params, "i", houseId)) return SendInfo(playerid, "Используйте: /addhousegate [houseID]");
    if(houseId < 0 || houseId > MAX_HOUSE) return 1;
    if(totalgatehouse >= 14) return SendError(playerid, "LIMIT 15 gate house!!!");
    new Float:pos_PLAYER[3],
        Float:pos_A;

    GetPlayerPos(playerid, pos_PLAYER[0], pos_PLAYER[1], pos_PLAYER[2]);

    GetPlayerFacingAngle(playerid, pos_A);
    new objectid = CreateDynamicObject(19912,
        pos_PLAYER[0] + (1.0 * floatsin(-pos_A, degrees)),
        pos_PLAYER[1] + (1.0 * floatcos(-pos_A, degrees)),
        pos_PLAYER[2], 0.0, 0.0, 0.0, -1, -1, -1, 120.0, 120.0);
    p_temp[playerid][p_listitem][10] = objectid;
    p_temp[playerid][p_listitem][11] = houseId;
    EditDynamicObject(playerid, objectid);
    return 1;
}

CMD:addhouseft(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    new house_id, boat_status, Float:pX, Float:pY, Float:pZ, Float:pAng;
    if(sscanf(params, "ii", house_id, boat_status)) return SendInfo(playerid, "Используйте: /addhouseft [id дома] [boat: -1]");
    if(house_id < 0 || house_id > totalhouses) return 1;
    if(h_info[house_id][h_mysql_id] == INVALID_MYSQL_ID) return SendError(playerid, "Дом не задействован.");
    GetPlayerPos(playerid,pX,pY,pZ);
    GetPlayerFacingAngle(playerid, pAng);

    h_info[house_id][h_air_pos][0] = pX;
    h_info[house_id][h_air_pos][1] = pY;
    h_info[house_id][h_air_pos][2] = pZ;
    h_info[house_id][h_air_pos][3] = pAng;

    if(boat_status != -1) h_info[house_id][h_boat_status] = 1;
    save_house(house_id);
    update_house(house_id);

    SendAccess(playerid, "Вы изменили настройки допов для Flin Town.");
    return 1;
}

CMD:timeownerbizz(playerid)
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;
    ShowPlayerList(playerid, LIST_ID_TIME_OWNER_BIZZ);
    return 1;
}
alias:timeownerbizz("towb");

CMD:auninvite(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /auninvite [id игрока]");
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не в сети.");
    if(p_info[params[0]][member] <= 0) return SendError(playerid, "Игрок не состоит во фракции.");

    if(GetPlayerStatusCapture(params[0]))
        HideTextDrawForPlayer(params[0], TD_ID_CAPTURE);

    if(GetFactionCategory(p_info[params[0]][member]) == FACTION_CATEGORY_PD || GetFactionCategory(p_info[params[0]][member]) == FACTION_CATEGORY_FBI)
            p_temp[params[0]][StatusOnDuty] = 0;

    if(p_info[params[0]][leader] > 0)
    {
        SendAccess(playerid, "Вы сняли %s [%d] с должности лидера фракции \"%s\".", get_name(params[0]), params[0], GetFractionName(p_info[params[0]][member]));
        SendInfo(params[0], "Администратор %s [%d] снял Вас с должности фракции \"%s\".", get_name(playerid), playerid, GetFractionName(p_info[params[0]][member]));
    }
    else
    {
        SendAccess(playerid, "Вы уволили %s [%d] из фракции \"%s\".", get_name(params[0]), params[0], GetFractionName(p_info[params[0]][member]));
        SendInfo(params[0], "Администратор %s [%d] уволил Вас из фракции \"%s\".", get_name(playerid), playerid, GetFractionName(p_info[params[0]][member]));
    }
    Log(LOG_player, INFO, "%s[%d](%s %s) был уволен %s[%d](%s %s) из %s | #Fraction #AdminLogs",
    get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC",
    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", GetFractionName(p_info[params[0]][member]));

    Log(LOG_player, INFO, "%s[%d](%s %s) уволил %s[%d](%s %s) из %s | #Fraction #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC", GetFractionName(p_info[params[0]][member]));

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] уволил %s [%d] из фракции \"%s\".", get_name(playerid), playerid, get_name(params[0]), params[0], GetFractionName(p_info[params[0]][member]));
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    if(!p_info[params[0]][admin])
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `log_fraction` (`PlayerID`, `Member`, `Rang`, `Type`, `Reason`) VALUES (%d, %d, %d, '1', 'Уволил Администратор')",
        p_info[params[0]][ID], p_info[params[0]][member], p_info[params[0]][rang]);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    /*
    p_info[params[0]][ftop_gkills_week] = 
    p_info[params[0]][ftop_gdeaths_week] = 0;
    p_info[params[0]][ftop_gdamagegive_week] = 
    p_info[params[0]][ftop_gdamagetake_week] = 0;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `ftop_gkills_week` = 0, `ftop_gdeaths_week`  = 0, `ftop_gdamagegive_week` = 0.0, `ftop_gdamagetake_week` = 0.0 WHERE `id` = %d", p_info[params[0]][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    */
    Iter_Remove(gFactionPlayers[p_info[params[0]][member]], params[0]);
    p_info[params[0]][member] = 0;
    p_info[params[0]][leader] = 0;
    p_info[params[0]][rang] = 0;
    p_info[params[0]][fskin] = 0;
    Iter_Add(gFactionPlayers[p_info[params[0]][member]], params[0]);
    if(GetPlayerHouseID(params[0]) != INVALID_HOUSE_ID) p_info[params[0]][spawn] = 2;
    else p_info[params[0]][spawn] = 0;
    p_info[params[0]][fwork] = false;
    SetPlayerSkinEx(params[0]);
    SetPlayerColor(params[0], fraction_color[0]);
    if(GetFactionCategory(p_info[params[0]][member]) == FACTION_CATEGORY_PD || GetFactionCategory(p_info[params[0]][member]) == FACTION_CATEGORY_FBI)
        p_temp[params[0]][StatusOnDuty] = 0;
    save_player(params[0]);

    WriteAdminLog(TYPE_LOG_UVAL, playerid, get_name(params[0]), params[0]);
    f_ResetPlayerWeapons(params[0]);
    return 1;
}

cmd:familylist(playerid, params[])
{
    if(p_info[playerid][admin] < 1) return 1;
    p_temp[playerid][p_listitem_int] = 0;
    STRING_GLOBAL[0] = EOS;
    for(new i = 0; i < family_count; i++) {
        if(i >= 50) break;
        if(FamilyData[i][fMysqlID] == -1) continue;
        f(STRING_GLOBAL,  "%s"I"[%d] {0ee33e}%s "W"(Game ID: "I"%d"W")\n", STRING_GLOBAL, i+1, FamilyData[i][fName], i);
        p_temp[playerid][p_listitem_int]++;
    }
    STRING_MIN[0] = EOS;
    format(STRING_MIN, sizeof STRING_MIN, ""I"Семьи сервера. (Количество: %d)", family_count);
    ShowPlayerDialog(playerid, D_FAMILY_LIST, DIALOG_STYLE_LIST, STRING_MIN, STRING_GLOBAL, "Дальше", "Отмена");
    return 1;
}

CMD:setfamilymoney(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "ii", params[0], params[1])) return SendInfo(playerid, "Используйте: /setfamilymoney [family id] [new value]");

    if(!(0 <= params[0] < family_count)) return SendInfo(playerid, "Используйте: /setfamilymoney [family id] [new value]");

    if(!(-999_000_000 <= params[1] <= 999_000_000))
        return SendInfo(playerid, "Используйте: /setfamilymoney [family id] [new value]");
    if(!(0 <= FamilyData[params[0]][fMoney]+params[1] <= 50_000_000))
    {
        if(params[1]) SendError(playerid, "Положить можно только 50 000 000$ в сумме.");
        else SendError(playerid, "На счету нет такой суммы денег.");
        return SendInfo(playerid, "Используйте: /setfamilymoney [family id] [new value]");
    }
    FamilyData[params[0]][fMoney] += params[1];
    SendAccess(playerid, "Вы %s %d$ семье %s. Бюджет: %d$.", params[1] > 0 ? "добавили" : "сняли", params[1], FamilyData[params[0]][fName], FamilyData[params[0]][fMoney]);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `money` = %d WHERE `id` = %d",
        FamilyData[params[0]][fMoney], FamilyData[params[0]][fMysqlID]);
    mysql_tquery (con_bd, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) %s %d$ в семье %s. Бюджет %d$ | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[1] > 0 ? "выдал" : "забрал", params[1], FamilyData[params[0]][fName], FamilyData[params[0]][fMoney]);
    return 1;
}

CMD:setfamilysexp(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "ii", params[0], params[1])) return SendInfo(playerid, "Используйте: /setfamilysexp [family id] [new value]");

    if(!(0 <= params[0] < family_count)) return SendInfo(playerid, "Используйте: /setfamilysexp [family id] [new value]");

    if(!(-50_000 <= params[1] <= 50_000))
        return SendInfo(playerid, "Используйте: /setfamilysexp [family id] [new value]");
    if(!(0 <= FamilyData[params[0]][fSeasonExp]+params[1] <= 50_000))
    {
        if(params[1]) SendError(playerid, "Выдать можно только 50 000 в сумме.");
        else SendError(playerid, "У семьи нет столько Season EXP.");
        return SendInfo(playerid, "Используйте: /setfamilysexp [family id] [new value]");
    }
    FamilyData[params[0]][fSeasonExp] += params[1];
    SendAccess(playerid, "Вы %s %d Season EXP семье %s. Всего Season EXP: %d.", params[1] > 0 ? "добавили" : "сняли", params[1], FamilyData[params[0]][fName], FamilyData[params[0]][fSeasonExp]);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `season_exp` = %d WHERE `id` = %d",
        FamilyData[params[0]][fSeasonExp], FamilyData[params[0]][fMysqlID]);
    mysql_tquery (con_bd, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) %s %d Season EXP семье %s. Всего Season EXP: %d | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[1] > 0 ? "выдал" : "забрал", params[1], FamilyData[params[0]][fName], FamilyData[params[0]][fSeasonExp]);
    return 1;
}

CMD:gm(playerid)
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 1) return 1;
    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда /gm недоступна для хелперов.");
    p_temp[playerid][gm_mode] = !p_temp[playerid][gm_mode];
    SendAccess(playerid, "Вас теперь %s убить от оружия!", p_temp[playerid][gm_mode] ? "не могут" : "могут");
    return 1;
}

CMD:givecar(playerid, params[])
{
    if(p_info[playerid][admin] < 2 && p_info[playerid][youtube_adm] < 3) return 1;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /givecar [id]");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
    if(GetPlayerInterior(params[0]) != 0 || GetPlayerVirtualWorld(params[0]) != 0)
        return SendError(playerid, "Игрок находится в виртуальном мире или интерьере.");
    new Float: pos[3];
    GetPlayerPos(params[0], pos[0], pos[1], pos[2]);
    new car_id = CreateVehicleVEx(NPO_TEMPCAR, NPO_NONE, 462, pos[0],pos[1]+0.5,pos[2],90.0000000, 1, 1, 600);
    LinkVehicleToInterior(car_id, GetPlayerInterior(params[0]));
    
    if(p_temp[playerid][rented_veh] != INVALID_VEHICLE_ID)
    {
        new vehicleid = p_temp[playerid][rented_veh];
        if(IsPlayerRentedVehicle(playerid, vehicleid))
        {
            DestroyVehicleVEx(vehicleid);
            if(veh_info[vehicleid][v_temp_job])
            {
                veh_info[vehicleid][v_temp_job] = 0;
                new scdplayerid = veh_info[vehicleid][v_used_key_ID];
                if(scdplayerid != INVALID_PLAYER_ID) EndPlayerJob(scdplayerid);
            }
            veh_info[vehicleid][v_rented_ID] = INVALID_MYSQL_ID;
            veh_info[vehicleid][v_used_key_ID] = INVALID_PLAYER_ID;
        }
        p_temp[playerid][rented_veh] = INVALID_VEHICLE_ID;
    }

    veh_info[car_id][v_lock] = 0;
    veh_info[car_id][v_color] = 1;
    veh_info[car_id][v_model] = 462;
    veh_info[car_id][v_fuel] = GetVehicleData(GetVehicleModelEx(car_id), E_VD_MAX_FUEL);
    for(new i; i < 5; i++) veh_info[car_id][v_details][i] = 100.0;
    format(veh_info[car_id][v_number], 16, "NULL");
    veh_info[car_id][v_int] =
    veh_info[car_id][v_virt] =
    veh_info[car_id][v_insurance] =
    veh_info[car_id][v_insurance_time] = 0;
    veh_info[car_id][v_rented_ID] = p_info[playerid][ID];
    veh_info[car_id][v_used_key_ID] = playerid;
    veh_info[car_id][v_engine] = 1;

    p_temp[playerid][rented_veh] = car_id;
    SetVehicleParamsVEx(car_id, veh_info[car_id][v_engine], veh_info[car_id][v_light], alarm, veh_info[car_id][v_lock], bonnet, boot, objective);

    SendInfo(params[0], "Администратор %s[%d] выдал вам временный арендный т/с: скутер.", get_name(playerid), playerid);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] выдал %s[%d] временный т/с: скутер.", get_name(playerid), playerid, get_name(params[0]), params[0]);
    SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);
    return 1;
}

CMD:jetpack(playerid)
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 1) return 1;
    if(p_info[playerid][helper] == 1) return SendError(playerid, "Команда недоступна хелперам.");
    SetPlayerSpecialAction(playerid, 
        GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USEJETPACK ? SPECIAL_ACTION_USEJETPACK : SPECIAL_ACTION_NONE);
    return 1;
}


CMD:offgetstats(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;
    if(isnull(params) || strlen(params) > 20) return SendInfo(playerid, "Используйте: /offgetstats [никнейм]");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `level`, `admin`, `warn`, `money`, `bank`, `bank_deposit`, \
    `leader`, `member`, `rang`, `regip`, `datareg`, `lastip`, `lastenter`, `online`, \
    `p_time_today`, `p_time_yesterday`, `p_afk_today`, `p_afk_yesterday`, `p_game_time`, `bitcoin` FROM `accounts` WHERE `name` = '%e' LIMIT 1",
    params);
    mysql_tquery(con_bd, STRING_GLOBAL, "AGetStats", "is", playerid, params);
    Log(LOG_player, INFO, "%s[%d](%s %s) посмотрел статистику %s offline | #AdminCheck",
    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
    params);
    return 1;
}

forward AGetStats(playerid, name_[]);
public AGetStats(playerid, name_[])
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Ничего не найдено.");

    new level_,awarn,money,id,
        leader_,member_,rank,admlevel,bank_, bank_deposit_, bitcoin_, regip_[MAX_IP_LENGTH], regdata_[16], lastip_[MAX_IP_LENGTH], l_online, lastenter_[16],
        _p_time_today, _p_time_yesterday, _p_afk_today, _p_afk_yesterday, _p_game_time;
    //
    cache_get_value_name_int(0,"id",id);
    cache_get_value_name_int(0,"level",level_);
    cache_get_value_name_int(0,"admin",admlevel);
    cache_get_value_name_int(0,"warn",awarn);
    cache_get_value_name_int(0,"money",money);
    cache_get_value_name_int(0,"bank",bank_);
    cache_get_value_name_int(0,"bank_deposit",bank_deposit_);
    cache_get_value_name_int(0,"bitcoin",bitcoin_);
    cache_get_value_name_int(0,"leader",leader_);
    cache_get_value_name_int(0,"member",member_);
    cache_get_value_name_int(0,"rang",rank);
    cache_get_value_name(0,"regip",regip_,MAX_IP_LENGTH);
    cache_get_value_name(0,"datareg",regdata_,16);
    cache_get_value_name(0,"lastip",lastip_,MAX_IP_LENGTH);
    cache_get_value_name(0,"lastenter",lastenter_,16);
    cache_get_value_name_int(0,"online",l_online);
    cache_get_value_name_int(0,"p_time_today", _p_time_today);
    cache_get_value_name_int(0,"p_time_yesterday", _p_time_yesterday);
    cache_get_value_name_int(0,"p_afk_today", _p_afk_today);
    cache_get_value_name_int(0,"p_afk_yesterday", _p_afk_yesterday);
    cache_get_value_name_int(0,"p_game_time", _p_game_time);

    if(admlevel == 15) admlevel = 0;

    new text[144];

    STRING_GLOBAL[0] = EOS;
    format(text,144,"Номер аккаунта:      \t%i\n",id);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Name:      \t\t%s\n\n",name_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Level:      \t\t%d\n",level_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Admin:      \t\t%d\n",admlevel);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Warns:      \t\t%d\n",awarn);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Money:      \t\t%d\n",money);
    strcat(STRING_GLOBAL, text);
    format(text,144,"%Bank:          \t\t%d\n",bank_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"%Bank Deposit:          \t%d\n",bank_deposit_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"%Bitcoin:              \t\t%d\n",bitcoin_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Leader:      \t\t%s\n", leader_ > 0 ? "Yes" : "No");
    strcat(STRING_GLOBAL, text);
    format(text,144,"Member:      \t\t%s\n", GetFractionName(member_));
    strcat(STRING_GLOBAL, text);
    format(text,144,"Rang:      \t\t%s [%d]\n", GetFractionRangName(member_, rank), rank);
    strcat(STRING_GLOBAL, text);
    format(text,144,"R-IP:      \t\t%s\n",regip_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Reg-Data:      \t\t%s\n",regdata_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"L-IP:      \t\t%s\n",lastip_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"L-Enter:      \t\t%s\n",lastenter_);
    strcat(STRING_GLOBAL, text);
    format(text,144,"Online:\t\t\t%s\n\n",(l_online != 0)?("Yes"):("No"));
    strcat(STRING_GLOBAL, text);
    format(text,144,"Отыграно за сегодня:\t\t\t%s\n", ConvertTime(_p_time_today));
    strcat(STRING_GLOBAL, text);
    format(text,144,"Отыграно за вчера:\t\t\t%s\n", ConvertTime(_p_time_yesterday));
    strcat(STRING_GLOBAL, text);
    format(text,144,"AFK за сегодня:\t\t\t%s\n", ConvertTime(_p_afk_today));
    strcat(STRING_GLOBAL, text);
    format(text,144,"AFK за вчера:\t\t\t\t%s\n", ConvertTime(p_afk_yesterday));
    strcat(STRING_GLOBAL, text);
    format(text,144,"Отыграно всего:\t\t\t%s\n\n", ConvertTime(_p_game_time));
    strcat(STRING_GLOBAL, text);
    strcat(STRING_GLOBAL, "{FF6347}* Если R-IP и L-IP не равны,\nтребуется проверить аккаунт на взлом");
    ShowPlayerDialog(playerid,D_NULL,DIALOG_STYLE_MSGBOX, ""I"Оффлайн Статистика персонажа",STRING_GLOBAL,"Готово","");
    return 1;
}

CMD:offgiveflin(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;

    new nickname[MAX_PLAYER_NAME], g_flin;
    if(sscanf(params,"is[24]", g_flin, nickname)) return SendInfo(playerid, "Используйте: /offgiveflin [кол-во Flin Money] [никнейм]");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "SelectFromTableForFlin","iis", playerid, g_flin, nickname);
    return 1;
}

CMD:offgivemoney(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;

    new nickname[MAX_PLAYER_NAME], g_money;
    if(sscanf(params, "is[24]", g_money, nickname)) return SendInfo(playerid, "Используйте: /offgivemoney [кол-во денежных средств] [никнейм]");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `money` FROM `accounts` WHERE `name` = '%e' LIMIT 1", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "SelectFromTableForMoney","iis", playerid, g_money, nickname);
    return 1;
}

forward SelectFromTableForFlin(playerid, g_flin, nickname[]);
public SelectFromTableForFlin(playerid, g_flin, nickname[])
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Ничего не найдено.");

    new id;
    sscanf(nickname, "u", id);
    if(id != INVALID_PLAYER_ID)
    {
        p_info[id][flinmoney] += g_flin;
        MysqlUpdatePlayerInt(id, "flinmoney", p_info[id][flinmoney]);
        SendInfo(id, "Администратор %s [%d] выдал Вам %d Flin Money.", get_name(playerid), playerid, g_flin);

        // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выдал ФМ
        Log(LOG_player, INFO, "%s[%d](%s %s) выдал %s[%d](%s %s) %d FM",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            get_name(id), p_info[id][ID], p_temp[id][session_IP], IsPlayerMobile(id) ? "Mobile": "PC",
            g_flin);
    }
    else {
        cache_get_value_index_int(0,0,id);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `flinmoney` = `flinmoney` + %d WHERE `id` = %d",
        g_flin, id);
        mysql_tquery(con_bd, STRING_GLOBAL);

        Log(LOG_player, INFO, "%s[%d](%s %s) выдал %s[%d](Offline) %d FM",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            nickname, id, g_flin);
    }
    SendAccess(playerid, "Вы выдали %s %d FM.", nickname, g_flin);
    return 1;
}

forward SelectFromTableForMoney(playerid, g_money, nickname[]);
public SelectFromTableForMoney(playerid, g_money, nickname[])
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Ничего не найдено.");

    new giveid, mysql_id, player_money;
    sscanf(nickname, "u", giveid);
    if(giveid != INVALID_PLAYER_ID)
    {
        SendInfo(giveid, "Администратор %s [%d] выдал Вам %d$.", get_name(playerid), playerid, g_money);
        SetPlayerMoney(giveid, g_money, true, "администратор %s[%d](%s %s) выдал %d$", get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile":"PC", g_money);
    }
    else {
        cache_get_value_index_int(0,0,mysql_id);
        cache_get_value_index_int(0,1, player_money);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `money` = `money` + %d WHERE `id` = %d",
        g_money, mysql_id);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    SendAccess(playerid, "Вы выдали %s %d$.", nickname, g_money);

    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выдал 130000$ оффлайн денег Vip_Uzer[1][$123334]
    Log(LOG_player, INFO, "%s[%d](%s %s) выдал %d$ оффлайн денег %s[%d][$%d]",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        g_money, nickname, giveid != INVALID_PLAYER_ID ? p_info[giveid][ID] : mysql_id,
        giveid != INVALID_PLAYER_ID ? p_info[giveid][cash]-g_money : player_money);
    return 1;
}
CMD:delacc(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /delacc [никнейм]");

    if(strequals(params, FD1))
        return SendError(playerid, "Вы не можете пользоваться этой командой.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1",
    params);
    mysql_tquery(con_bd, STRING_GLOBAL, "SelectFromTableForDelete", "is", playerid, params);
    return 1;
}

this::SelectFromTableForDelete(playerid, const account_dell[])
{
    if(0 == cache_num_rows())
        return SendError(playerid, "Игрок не найден в базе данных.");

    new
        ingame_id = GetPlayerID(account_dell),
        account_id = 0;

    if(ingame_id != INVALID_PLAYER_ID)
    {
        SendInfo(ingame_id, "Администратор %s [%d] удалил Ваш аккаунт.", get_name(playerid), playerid);

        Kick(ingame_id);
    }

    cache_get_value_name_int(0, "id", account_id);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `name` = '%s_BACKUP' WHERE `id` = %d",
    account_dell, account_id);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] удалил аккаунт %s.", get_name(playerid), playerid, account_dell);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы удалили аккаунт %s.", account_dell);

    WriteAdminLog(TYPE_LOG_DELACC, playerid, account_dell, INVALID_PLAYER_ID);
    return 1;
}

CMD:transferacc(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /transferacc [никнейм]");

    if(strequals(params, FD1))
        return SendError(playerid, "Вы не можете пользоваться этой командой.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1",
    params);
    mysql_tquery(con_bd, STRING_GLOBAL, "SelectFromTableForTransfer", "is", playerid, params);
    return 1;
}

this::SelectFromTableForTransfer(playerid, const nickname_transfer[])
{
    if(!cache_num_rows())
        return SendError(playerid, "Игрок не найден в базе данных.");

    new
        ingame_id = GetPlayerID(nickname_transfer),
        account_id = 0;

    if(ingame_id != INVALID_PLAYER_ID)
    {
        SendInfo(ingame_id, "Администратор %s [%d] переносит Ваш аккаунт с другого проекта.", get_name(playerid), playerid);
        Kick(ingame_id);
    }

    cache_get_value_name_int(0, "id", account_id);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `level` = `level` + 10, `money` = `money` + 500000, `p_vip` = 1, `p_vip_time` = `p_vip_time` + (SELECT UNIX_TIMESTAMP())+7*86000, `passport` = 1, `passport_time` = 336, `med_card` = 1, `med_card_time` = 336, `Lic` = '1|1|1|1|1|1|1|1|1', `Lic_Warn` = '0|0|0|0|0|0|0|0|0', `Lic_Time` = '336|336|336|336|336|336|336|336|336' WHERE `id` = %d",
        account_id);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] перенес аккаунт %s с другого проекта.", get_name(playerid), playerid, nickname_transfer);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    SendAccess(playerid, "Вы перенесли аккаунт %s с другого проекта.", nickname_transfer);

    WriteAdminLog(TYPE_LOG_TRANSFER, playerid, nickname_transfer, INVALID_PLAYER_ID);
    return 1;
}




CMD:weather(playerid, params[])
{
    if(SRV_ID != 0 && (!FD(playerid) || p_info[playerid][admin] < 6)) return 1;
    new weather_id;
    if(sscanf(params, "i", weather_id))
        return SendInfo(playerid, "Используйте: /weather [id погоды]");

    if(!(0 <= weather_id <= 47))
        return SendError(playerid, "ID погоды должен быть не менее 0 и не более 47.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] изменил номер погоды на %d.", get_name(playerid), playerid, weather_id);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    Default_Weather = weather_id;
    SetWeather(Default_Weather);
    return 1;
}

CMD:offjail(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    new nickname[MAX_PLAYER_NAME], reason[144], time;
    if(sscanf(params, "s[24]is[144]", nickname, time, reason)) return SendInfo(playerid, "Используйте: /offjail [никнейм] [кол-во минут] [причина]");
    new paramss;
    sscanf(nickname, "u", paramss);
    if(paramss != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");
    if(!(1 <= time <= 300)) return SendError(playerid, "Кол-во минут не может быть менее 1 и более 300.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e'", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "offjail_callback", "issd", playerid, nickname, reason, time);
    a_info[playerid][a_offjail] = 1;
    MysqlUpdateAdminInt(playerid, "a_offjail", a_info[playerid][a_offjail]);
    return 1;
}

forward offjail_callback(playerid, Nick[],Reason[], Time);
public offjail_callback(playerid, Nick[],Reason[], Time)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Игрок не найден.");
    new mysql_user_id;
    cache_get_value_name_int(0,"id",mysql_user_id);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] посадил в тюрьму %s на %d %s. Причина: %s", get_name(playerid), playerid, Nick, Time, Declension_ReturnWord(Time, "минуту", "минуты", "минут"), Reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);
    AddNotify(mysql_user_id, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `jail_time` = `jail_time` + %d, `jail` = '6' WHERE `id` = %d LIMIT 1", Time*60, mysql_user_id);
    mysql_tquery(con_bd, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_OFFJAIL, playerid, Nick, INVALID_PLAYER_ID, Reason);
    return 1;
}

CMD:offunjail(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    new nickname[MAX_PLAYER_NAME], reason[144];
    if(sscanf(params, "s[24]s[144]", nickname, reason)) return SendInfo(playerid, "Используйте: /offunjail [никнейм] [причина]");
    new targetid;
    sscanf(nickname, "u", targetid);
    if(targetid != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e'", nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "offunjail_callback", "iss", playerid, nickname, reason);
    a_info[playerid][a_offjail] = 1;
    MysqlUpdateAdminInt(playerid, "a_offjail", a_info[playerid][a_offjail]);
    return 1;
}

forward offunjail_callback(playerid, Nick[],Reason[]);
public offunjail_callback(playerid, Nick[],Reason[])
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Игрок не найден.");
    new mysql_user_id;
    cache_get_value_name_int(0,"id",mysql_user_id);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выпустил из тюрьмы %s. Причина: %s", get_name(playerid), playerid, Nick);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);
    AddNotify(mysql_user_id, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `jail_time` = 0, `jail` = '0' WHERE `id` = %d", mysql_user_id);
    mysql_tquery(con_bd, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_OFFJAIL, playerid, Nick, INVALID_PLAYER_ID, Reason);
    return 1;
}
CMD:offunwarn(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(isnull(params) || strlen(params) > 20) return SendInfo(playerid, "Используйте: /offunwarn [никнейм]");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `warn` FROM `accounts` WHERE `name` = '%e'",
    params);
    mysql_tquery(con_bd, STRING_GLOBAL, "un_warn_player", "is",playerid,params);
    return 1;
}

forward un_warn_player(playerid,Nick[]);
public un_warn_player(playerid,Nick[])
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Игрок не найден.");
    new count_warns;
    cache_get_value_index_int(0,0,count_warns);
    if(!count_warns) return SendError(playerid, "У игрока нет предупреждений.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `warn` = 0, `warn_time` = 0 WHERE `name` = '%e' LIMIT 1", Nick);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] снял предупреждение с %s.", get_name(playerid), playerid, Nick);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_OFFUNWARN, playerid, Nick, INVALID_PLAYER_ID);
    return 1;
}

CMD:offwarn(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;

    new nickname[MAX_PLAYER_NAME], reason[144], days;

    if(sscanf(params, "s[24]is[144]", nickname, days, reason))
        return SendInfo(playerid, "Используйте: /offwarn [никнейм] [кол-во дней] [причина]");
    new paramss;
    sscanf(nickname, "u", paramss);
    if(paramss != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");
    if(!(1 <= days <= 7)) return SendError(playerid, "Кол-во дней предупреждения не может быть менее 1 и более 7.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 5)) return 1;

    if(!strcmp(nickname, FD1) || !strcmp(nickname, FD2))
    {
        SendInfo(playerid, "С Вас были сняты права администратора.");
        Iter_Remove(gAdmins, playerid);
        p_info[playerid][admin] = 0;
        p_info[playerid][admin_pass] = 0;
        Kick(playerid);
        return 1;
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `warn`, `id` FROM `accounts` WHERE `name` = '%e'",
    nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "offwarn", "issd", playerid, nickname, reason, days);
    a_info[playerid][a_offwarn] = 1;
    MysqlUpdateAdminInt(playerid, "a_offwarn", a_info[playerid][a_offwarn]);
    return 1;
}

forward offwarn(playerid, Nick[],Reason[], days);
public offwarn(playerid, Nick[],Reason[], days)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Игрок не найден.");
    new count_warns, mysql_user_id;
    cache_get_value_name_int(0,"warn",count_warns);
    cache_get_value_name_int(0,"id",mysql_user_id);
    if((count_warns+1) < 3)
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `warn` = %d, `leader` = 0, `member` = 0, `rang` = 0, `warn_time` = %d, `fwork` = 0 WHERE `id` = %d LIMIT 1",
        (count_warns+1), timestamp + (86400 * 7), mysql_user_id);
        mysql_tquery(con_bd, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал предупреждение %s на %d %s (%d из 3). Причина: %s", get_name(playerid), playerid, Nick, days, Declension_ReturnWord(days, "день", "дня", "дней"), (count_warns+1), Reason);
        SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);
        AddNotify(mysql_user_id, STRING_GLOBAL);

        WriteAdminLog(TYPE_LOG_OFFWARN, playerid, Nick, INVALID_PLAYER_ID, Reason);
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `warn` = 0, `warn_time` = 0 WHERE `id` = %d", mysql_user_id);
        mysql_tquery(con_bd, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `table_ban` WHERE `Name_Player` = '%e' LIMIT 1", Nick);
        mysql_tquery(con_bd, STRING_GLOBAL, "OffBan", "issi",playerid,Nick,Reason,7);
    }
    return 1;
}

CMD:offmute(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;

    new nickname[MAX_PLAYER_NAME], time, reason[144];
    if(sscanf(params, "s[24]is[144]", nickname, time, reason)) return SendInfo(playerid, "Используйте: /offmute [никнейм] [кол-во минут] [причина]");
    new paramss;
    sscanf(nickname, "u", paramss);
    if(paramss != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");
    if(!(1 <= time <= 300)) return SendError(playerid, "Кол-во минут блокировки чата не может быть менее 1 и более 300.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e'",
    nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "offmute", "issd", playerid, nickname, reason, time);
    a_info[playerid][a_offmute] = 1;
    MysqlUpdateAdminInt(playerid, "a_offmute", a_info[playerid][a_offmute]);
    return 1;
}

forward offmute(playerid, Nick[],Reason[], Time);
public offmute(playerid, Nick[],Reason[], Time)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Игрок не найден.");
    new mysql_user_id;
    cache_get_value_name_int(0,"id",mysql_user_id);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] выдал блокировку чата %s на %d %s. Причина: %s", get_name(playerid), playerid, Nick, Time, Declension_ReturnWord(Time, "минуту", "минуты", "минут"), Reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);
    AddNotify(mysql_user_id, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_OFFMUTE, playerid, Nick, INVALID_PLAYER_ID, Reason);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `mute` = `mute` + %d WHERE `name` = '%e' LIMIT 1",
    Time*60, Nick);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

CMD:offunmute(playerid, params[])
{
    if(p_info[playerid][admin]<4) return 1;

    new nickname[MAX_PLAYER_NAME], reason[144];

    if(sscanf(params, "s[24]s[144]", nickname, reason)) return SendInfo(playerid, "Используйте: Используйте: /offunmute [никнейм] [причина]");
    new paramss;
    sscanf(nickname, "u", paramss);
    if(paramss != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");

    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
    if(IsAAdminAttack(playerid, 3)) return 1;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e'",
    nickname);
    mysql_tquery(con_bd, STRING_GLOBAL, "offunmute", "iss", playerid, nickname, reason);
    a_info[playerid][a_offmute] = 1;
    MysqlUpdateAdminInt(playerid, "a_offmute", a_info[playerid][a_offmute]);
    return 1;
}

forward offunmute(playerid, Nick[],Reason[]);
public offunmute(playerid, Nick[],Reason[])
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Игрок не найден.");
    new mysql_user_id;
    cache_get_value_name_int(0,"id",mysql_user_id);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s [%d] снял блокировку чата %s. Причина: %s", get_name(playerid), playerid, Nick, Reason);
    SendAdminMessageForServer(COLOR_LIGHTRED, STRING_GLOBAL);
    AddNotify(mysql_user_id, STRING_GLOBAL);

    WriteAdminLog(TYPE_LOG_OFFMUTE, playerid, Nick, INVALID_PLAYER_ID, Reason);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `mute` = 0 WHERE `name` = '%e' LIMIT 1",
    Nick);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

CMD:sethpr(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /sethpr [радиус]");
    if(params[0] > 100 || params[0] < 1) return SendError(playerid, "Радиус должен быть не менее 1 и не более 100.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] восстановил здоровье в радиусе %d.", get_name(playerid), playerid, params[0]);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    foreach(new i: Player)
    {
        if(!p_info[i][loggedIn]) continue;
        if(!IsPlayerStream(params[0], i, playerid)) continue;
        SetPlayerHealth(i, 100.00);
        p_info[i][satiety] =
        p_info[i][thirst] = 100.0;
        SendInfo(i, "Администратор %s [%d] восстановил Вам здоровье.", get_name(playerid), playerid);
    }

    SendAccess(playerid, "Вы восстановили игрокам в радиусе %d здоровье.", params[0]);
    return 1;
}

CMD:pgetip(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;
    if(isnull(params) || strlen(params) > 16) return SendInfo(playerid, "Используйте: Используйте: /pgetip [ip адрес]");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `regip`, `lastip`, `level`, `money` FROM `accounts` WHERE `lastip` = '%e' OR `regip` = '%e'",
    params, params);
    mysql_tquery(con_bd, STRING_GLOBAL, "p_get_ip", "is",playerid, params);

    return 1;
}
forward p_get_ip(playerid, params[]);
public p_get_ip(playerid, params[])
{
    new rows = cache_num_rows();
    if(rows)
    {
        new name_[MAX_PLAYER_NAME+1], text[144], regip_[16], ip[16], cash_, level_;

        STRING_GLOBAL[0] = EOS;
        STRING_GLOBAL = "{5891C6}Имя\t\t\t\tРег.IP\t\t\t\tLast IP\t\t\tУровень\t\tДеньги\n"W"";
        for(new i; i < rows; i++)
        {
            cache_get_value_name(i,"name",name_,MAX_PLAYER_NAME+1);
            cache_get_value_name(i,"regip",regip_,MAX_IP_LENGTH);
            cache_get_value_name(i,"lastip",ip,MAX_IP_LENGTH);
            cache_get_value_name_int(i,"level",level_);
            cache_get_value_name_int(i,"money",cash_);


            format(text, 144, "%s\t\t%s\t\t%s\t\t%i\t\t%i$\n", name_, regip_, ip, level_, cash_);
            strcat(STRING_GLOBAL, text);
            if(i == (rows - 1))
            {
                format(text, 144, "Всего аккаунтов: %d", rows);
                strcat(STRING_GLOBAL, text);
            }
        }
        new str[128];
        format(str, sizeof(str), ""I"Аккаунты с IP-адресом: %s", params);
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, str, STRING_GLOBAL, "Закрыть", "");

    }
    else SendError(playerid, "Ничего не найдено.");
    return 1;
}

CMD:delvehr(playerid, params[])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /delvehr [радиус]");
    if(params[0] < 1 || params[0] > 25) return SendError(playerid, "Радиус должен быть не менее 1 и не более 25.");
    new Float:pX,
        Float:pY,
        Float:pZ;
    foreach(new v: Vehicle)
    {
        if(IsVehicleOccupied(v)) continue;
        if(veh_info[v][v_thief_ID] != INVALID_PLAYER_ID) continue;
        GetVehiclePos(v,pX,pY,pZ);
        if(PlayerToPoint(params[0], playerid, pX,pY,pZ))
        {
            SaveVehicle(v);
            SaveVehicleDetails(v);
            DestroyVehicleVEx(v);
        }
    }
    SendAccess(playerid, "Вы удалили транспортные средства в радиусе %d.", params[0]);
    return 1;
}
CMD:ooc(playerid, params[])
{
    if(p_info[playerid][admin] < 2)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /o [текст]");

    if(AdvertisingCheck(params)) return AdvertisingPunishment(playerid, params, 0);

    // Проверяем счетчик;
    if(GetPVarInt(playerid, "OOCAntiAttack") > 20) return OnPlayerSystemBan(playerid, "OOC-ATTACK");
    // Обновляем счетчик;
    SetPVarInt(playerid, "OOCAntiAttack", GetPVarInt(playerid, "OOCAntiAttack") + 4);

    SendMesAll(0xFFFFFFFF, "<< [OOC] %s[%d]: %s >>", get_name(playerid), playerid, params);

    Log(LOG_player, INFO, "%s[%d](%s %s) написал в /ooc: %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params);
    return 1;
}

CMD:spveh(playerid, params[])
{
    if(p_info[playerid][admin] < 3)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /spveh [id транспортного средства]");

    new vehicle = strval(params);
    if(vehicle == INVALID_VEHICLE_ID || !IsValidVehicle(vehicle))
        return SendError(playerid, "Неверный ID транспортного средства.");

    if(IsVehicleOccupied(vehicle))
        return SendError(playerid, "Транспортное средство используется.");

    if(GetSlotVehicleMarket(veh_info[vehicle][v_mysql_id]) != -1)
        return SendError(playerid, "Взаимодействие с транспортным средство невозможно, оно находится на авторынке.");

    SetVehicleToRespawn(vehicle);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] отправил на спавн Т/С %s[%d].", get_name(playerid), playerid, GetVehicleName(vehicle), vehicle);
    SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) отправил на спавн Т/С %s[%d] | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        GetVehicleName(vehicle), vehicle);
    return 1;
}

CMD:spvehr(playerid, params[])
{
    if(p_info[playerid][admin] < 3)
        return 1;

    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /spvehr [радиус]");
    if(params[0] < 1 || params[0] > 150) return SendError(playerid, "Радиус должен быть не менее 1 и не более 150.");
    new Float:pX,
        Float:pY,
        Float:pZ;

    for(new v = 1, j = GetVehiclePoolSize(); v <= j; v++)
    {
        if(IsVehicleOccupied(v)) continue;
        GetVehiclePos(v,pX,pY,pZ);
        if(PlayerToPoint(params[0], playerid, pX,pY,pZ)) SetVehicleToRespawn(v);
    }

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] транспортные средства в радиусе %d на парковочные места.", get_name(playerid), playerid, params[0]);
    SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);

    Log(LOG_player, INFO, "%s[%d](%s %s) отправил на спавн Т/С в радиусе %d | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        params[0]);
    return 1;
}

CMD:infomoney(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;

    OnServerInfoForMoney[50] = 0;
    OnServerInfoForMoney[51] = 0;
    OnServerInfoForMoney[50] = (OnServerInfoForMoney[0] + OnServerInfoForMoney[1] + OnServerInfoForMoney[2] + OnServerInfoForMoney[6] + OnServerInfoForMoney[10] + OnServerInfoForMoney[11] + OnServerInfoForMoney[12] + OnServerInfoForMoney[13] + OnServerInfoForMoney[14] + OnServerInfoForMoney[18] + OnServerInfoForMoney[23] + OnServerInfoForMoney[24] + OnServerInfoForMoney[20] + OnServerInfoForMoney[36] + OnServerInfoForMoney[37] + OnServerInfoForMoney[38] + OnServerInfoForMoney[40] + OnServerInfoForMoney[41]);
    OnServerInfoForMoney[51] = (OnServerInfoForMoney[3] + OnServerInfoForMoney[5] + OnServerInfoForMoney[4] + OnServerInfoForMoney[8] + OnServerInfoForMoney[7] + OnServerInfoForMoney[28] + OnServerInfoForMoney[26] + OnServerInfoForMoney[27] + OnServerInfoForMoney[16] + OnServerInfoForMoney[17] + OnServerInfoForMoney[19] + OnServerInfoForMoney[21] + OnServerInfoForMoney[22] + OnServerInfoForMoney[25] + OnServerInfoForMoney[15] + OnServerInfoForMoney[9] + OnServerInfoForMoney[29] + OnServerInfoForMoney[30] + OnServerInfoForMoney[31] + OnServerInfoForMoney[32] + OnServerInfoForMoney[33] + OnServerInfoForMoney[34] + OnServerInfoForMoney[35] + OnServerInfoForMoney[39]);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
    [#] Наименование\tПараметр\n\
    "I"[1]"W" Ушло денежных средств:\t%d$\n\
    "I"[2]"W" Пришло денежных средств:\t%d$\n\
    "I"[3]"W" Налоги:\tПодробности в диалоге", OnServerInfoForMoney[50], OnServerInfoForMoney[51]);
    ShowPlayerDialog(playerid, D_FINANC_INFO, DIALOG_STYLE_TABLIST_HEADERS, ""I"Статистика денежных средств", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
CMD:arep(playerid, params[])
{
    if(p_info[playerid][admin] < 1 && p_info[playerid][youtube_adm] < 4) 
        return 1;
    ShowPlayer_Admin_Report_List(playerid);
    return 1;
}
alias:arep("srep");
CMD:report(playerid, params[])
{
    if(GetPVarInt(playerid, "Flood:Report") > timestamp)
        return SendError(playerid, "Отправлять репорт можно раз в 30 секунд.");

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /report [текст]");

    if(GetPVarInt(playerid, "report_id")-1 != -1)
        return SendError(playerid, "Вы уже отправили репорт.");

    if(p_info[playerid][rmute] > 0)
        return SendError(playerid, "У Вас блокировка репорта.");

    if(!(1 <= strlen(params) <= 90))
        return SendError(playerid, "Кол-во символов в сообщении не может быть менее 1 и более 100.");

    for(new i; i < MAX_ADMIN_REPORTS; i++)
    {
        if(aReportInfo[i][rWhenWroted_Time] > timestamp) continue;

        SetPVarInt(playerid, "Flood:Report", timestamp+30);

        if(aReportInfo[i][rPlayerID] != INVALID_PLAYER_ID)
        {
            SendInfo(aReportInfo[i][rPlayerID], "Ваша жалоба или сообщение для администрации было удалено системой.");
            DeletePVar(aReportInfo[i][rPlayerID], "report_id");
        }

        SendAccess(playerid, "Жалоба отправлена администрации сервера.");
        SendInfo(playerid, "Текст: %s", params);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] [REPORT] %s [%d]: {E3B72E}%s", get_name(playerid), playerid, params);
        SendAdminMessage(0xD35B25FF, STRING_GLOBAL);

        aReportInfo[i][rID] = i;
        aReportInfo[i][rPlayerID] = playerid;
        aReportInfo[i][rWhenWroted_Time] = timestamp+300;
        aReportInfo[i][rIsTooked] = false;

        format(aReportInfo[i][rText], MAX_ADMIN_REPORT_TEXT_LENGTH, "%s", params);
        format(aReportInfo[i][rWhenWroted_Text], 10, "%02d:%02d:%02d", timestamp_hour, timestamp_minute, timestamp_second);
        SetPVarInt(playerid, "report_id", i+1);

        Log(LOG_player, INFO, "%s[%d](%s %s) написал в /report: %s | #AdminLogs",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            params);
        return true;
    }
    SendError(playerid, "У администрации большое количество репортов, подождите.");
    return 1;
}
alias:report("vopros");
ShowPlayer_Admin_Report_Answer(playerid, report_id)
{
    if(report_id == -1) return ShowPlayer_Admin_Report_List(playerid);
    if(aReportInfo[report_id][rPlayerID] == INVALID_PLAYER_ID) return ShowPlayer_Admin_Report_List(playerid);
    SetPVarInt(playerid, "report_id_to_answer", report_id);
    SetPVarInt(playerid, "report_playerid", aReportInfo[report_id][rPlayerID]);
    aReportInfo[report_id][rIsTooked] = true;
    new dialog_header_text[] = ""I"%d. "W"%s [%d]",
        dialog_string_text[] =
            ""W"Жалоба/сообщение: %s\n\n\
            Отправил: %s\n | %s\n\n\
            Введите Ваш ответ в диалоговое поле ниже:\n\n\
            Для слежки за отправителем введите: {"#cLIGHTRED"}re"W"\n\
            Или: {"#cLIGHTRED"}re ID"W" если за кем-то другим.";
    new dialog_header[sizeof(dialog_header_text) + (-2+2) + (-2+MAX_PLAYER_NAME) + (-2+2) + (-2+2)],
        dialog_string[sizeof(dialog_string_text) + (-2+MAX_ADMIN_REPORT_TEXT_LENGTH) + (-2+MAX_PLAYER_NAME) + (-2+10)];
    format(dialog_header, sizeof(dialog_header), dialog_header_text, report_id+1, get_name(aReportInfo[report_id][rPlayerID]), aReportInfo[report_id][rPlayerID]);
    format(dialog_string, sizeof(dialog_string), dialog_string_text, aReportInfo[report_id][rText], get_name(aReportInfo[report_id][rPlayerID]), aReportInfo[report_id][rWhenWroted_Text]);
    ShowPlayerDialog(playerid, D_REPORT_ANS, DIALOG_STYLE_INPUT, dialog_header, dialog_string, "Далее", "Отмена");
    return 1;
}

CMD:agetip(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;
    if(isnull(params) || strlen(params) > 20) return SendInfo(playerid, "Используйте: /agetip [никнейм]");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `regip`, `lastip` FROM `accounts` WHERE `name` = '%e' LIMIT 1",
        params);
    mysql_tquery(con_bd, STRING_GLOBAL, "AGetIp", "is", playerid, params);
    return 1;
}

forward AGetIp(i, akk[]);
public AGetIp(i, akk[])
{
    new preg[MAX_IP_LENGTH], pip[MAX_IP_LENGTH];
    new rows = cache_num_rows();
    if(!rows) return SendError(i, "Ничего не найдено.");
    cache_get_value_name(0, "regip", preg, MAX_IP_LENGTH);
    cache_get_value_name(0, "lastip", pip, MAX_IP_LENGTH);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Никнейм: %s | Рег. IP: %s | Послед. IP: %s | IP: %s", akk, preg, pip, preg);
    SendInfo(i, STRING_GLOBAL);
    return 1;
}

CMD:tp(playerid, params[])
{
    if(p_info[playerid][admin] < 2 && p_info[playerid][youtube_adm] < 1 && p_temp[playerid][premiumgamer] != PREMIUM_GAME)
        return 1;
    callcmd::gps(playerid, "/0");
    p_temp[playerid][gps_admin] = 1000+playerid;
    return 1;
}

CMD:apoint(playerid, params[])
{
    if(p_info[playerid][admin] < 1)
        return 1;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /apoint [id]");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");

    callcmd::gps(playerid, "/0");
    p_temp[playerid][gps_admin] = params[0];
    return 1;
}
alias:apoint("agps");

CMD:gzcolor(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /gzcolor [id фракции] (15 - neutral)");
    if(!(10 <= params[0] <= 15)) return SendInfo(playerid, "Используйте: /gzcolor [id фракции] (15 - neutral)");
    new gangzone = GetGangZoneID(playerid);
    if(gangzone == INVALID_CRIMINAL_ZONE_ID)
        return SendError(playerid, "Вы не на территории Ghetto.");
    
    if(gangzone == 39)
    {
        DrugDenInfo[ddOwner] = params[0];
        SaveDrugDen();
    }

    if(GangZone_Info[gangzone][g_Fraction] != 15) SetGangTerritory(GangZone_Info[gangzone][g_Fraction], -1);
    GangZone_Info[gangzone][g_Fraction] = params[0];
    if(params[0] != 15) SetGangTerritory(GangZone_Info[gangzone][g_Fraction], 1);

    GangZoneStopFlashForAll(GangZone_Info[gangzone][gID]);
    GangZoneHideForAll(GangZone_Info[gangzone][gID]);
    GangZoneShowForAll(GangZone_Info[gangzone][gID],(GangZone_Info[gangzone][g_Fraction] != 15) ? (fraction_color[GangZone_Info[gangzone][g_Fraction]]) : (0xFFFFFF65));

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] изменил владение территории %d.", get_name(playerid), playerid, gangzone);
    SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

    save_gz(gangzone);

    Log(LOG_player, INFO, "%s[%d](%s %s) установил контроль ghetto территории %d для %s | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", gangzone, GetFractionName(params[0]));
    return 1;
}

CMD:ffreeze(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    new count;
    STRING_GLOBAL[0] = EOS;
    STRING_GLOBAL = ""W"Фракция\t"W"Статус\n";
    for(new i; i < MAX_FRACTIONS; i++)
    {
        if(GetFactionType(i) != FACTION_TYPE_CRIMINAL) continue;
        f(STRING_GLOBAL, "%s {%06x}%s\t%s\n", STRING_GLOBAL, 
            fraction_color[i] >>> 8, GetFractionName(i), GetFractionSettings(i, fFreezeCapture) > 1 ? "{"#cLIGHTRED"}Заморожена" : "{"#cGREEN"}Разморожено");
        p_temp[playerid][p_listitem][count] = i;
        count++;
    }
    ShowPlayerDialog(playerid, D_FRACTION_FREEZE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Панель состояния фракции", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;
}
alias:ffreeze("gfreeze", "gfreez", "mfreez", "mfreeze");

CMD:atipster(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;

    STRING_GLOBAL[0] = EOS;
    STRING_GLOBAL = ""I"[1]"W" Отключить прослушку\n";
    for (new i = 1; i < MAX_FRACTIONS; i ++)
    {
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i + 1, GetFractionName(i));
    }
    ShowPlayerDialog(playerid, D_ATIPSTER, DIALOG_STYLE_LIST, ""I"Прослушка фракций", STRING_GLOBAL, "Принять", "Отмена");
    return 1;
}

CMD:famtipster(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /famtipster [family id(/familylist)](-1 off)");
    if(!(-1 <= params[0] < family_count)) return SendInfo(playerid, "Используйте: /setfamilymoney [family id(/familylist)](-1 off)");
    if(p_temp[playerid][tipster_family] == params[0]) return 1;

    p_temp[playerid][tipster_family] = params[0];
    if(params[0] != -1)
    {
        SendAccess(playerid, "Вы начали прослушку семьи %s", FamilyData[params[0]][fName]);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s [%d] начал прослушку семьи %s.", get_name(playerid), playerid, FamilyData[params[0]][fName]);
        SendAdminMessage(0xA3A3A3FF, STRING_GLOBAL);
    }
    else SendAccess(playerid, "Вы прекратили прослушки семьи.");
    return 1;
}

CMD:createpromo(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 7)
        return 1;

    new sNick[MAX_PLAYER_NAME], sPromo[144];
    if(sscanf(params, "s[24]s[144]", sNick, sPromo)) return SendInfo(playerid, "Используйте: /createpromo [nickname] [promo]");

    if(GetPlayerID(sNick) != INVALID_PLAYER_ID) 
        return SendError(playerid, "Игрок в сети.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1", sNick);
    mysql_tquery(con_bd, STRING_GLOBAL, "AdminCreatePromo_CheckNick", "iss", playerid, sNick, sPromo);

    return 1;
}

this::AdminCreatePromo_CheckNick(playerid, sNick[], sPromo[])
{
    if(!cache_num_rows())
        return SendError(playerid, "Игрок не найден в базе данных.");

    new iID;
    cache_get_value_index_int(0, 0, iID);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), 
        "SELECT * FROM `promocode` WHERE `name` = '%e' OR `ownerid` = %d LIMIT 1", sPromo, iID);
    mysql_tquery(con_bd, STRING_GLOBAL, "AdminCreatePromo_CheckPromo", "iiss", playerid, iID, sNick, sPromo);
    return 1;
}

this::AdminCreatePromo_CheckPromo(playerid, mysqlID, sNick[], sPromo[])
{
    if(cache_num_rows())
        return SendError(playerid, "У игрока уже есть промокод или данный промокод создан.");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `promocode` (`name`, `ownerid`, `owner`) VALUES ('%e', %d, '%e')",
        sPromo, mysqlID, sNick);
    mysql_tquery(con_bd, STRING_GLOBAL, "AdminCreatePromo_Create", "iiss", playerid, mysqlID, sNick, sPromo);
    return 1;
}

this::AdminCreatePromo_Create(playerid, mysqlID, sNick[], sPromo[])
{
    new time[32], year, month, day;
    getdate(year, month, day);
    format(time, sizeof(time), "%02d/%02d/%d %02d:%02d:%02d", day, month, year, timestamp_hour, timestamp_minute, timestamp_second);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `promocode_create` = %d, `promocode_time` = '%e' WHERE `id` = %d",
        cache_insert_id(), time, mysqlID);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы создали промокод "I"%s"W" для "I"%s.", sPromo, sNick);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Создание промокода", STRING_GLOBAL, "ОК", "");

    Log(LOG_player, INFO, "%s[%d](%s %s) создал промокод %s для %s | #AdminLogs #Promocode",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        sPromo, sNick);
    return 1;
}

CMD:createfam(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 7)
        return 1;

    if(family_count >= MAX_FAMILY-1)
            return SendError(playerid, "Количество семей превышает лимиты.");

    new sNick[MAX_PLAYER_NAME], sFamilyName[144];
    if(sscanf(params, "s[24]s[144]", sNick, sFamilyName)) return SendInfo(playerid, "Используйте: /createfam [nickname] [family name]");

    if(GetPlayerID(sNick) != INVALID_PLAYER_ID) 
        return SendError(playerid, "Игрок в сети.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1", sNick);
    mysql_tquery(con_bd, STRING_GLOBAL, "AdminCreateFamily_CheckNick", "iss", playerid, sNick, sFamilyName);
    return 1;
}

this::AdminCreateFamily_CheckNick(playerid, sNick[], sFamilyName[])
{
    if(!cache_num_rows())
        return SendError(playerid, "Игрок не найден в базе данных.");

    new iID;
    cache_get_value_index_int(0, 0, iID);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), 
        "SELECT * FROM `family` WHERE `name` = '%e' OR `owner_id` = %d LIMIT 1", sFamilyName, iID);
    mysql_tquery(con_bd, STRING_GLOBAL, "AdminCreateFamily_CheckFamily", "iiss", playerid, iID, sNick, sFamilyName);
    return 1;
}

this::AdminCreateFamily_CheckFamily(playerid, mysqlID, sNick[], sFamilyName[])
{
    if(cache_num_rows())
        return SendError(playerid, "У игрока уже есть своя семья или данная семья создана.");

    new year, month,day;
    getdate(year, month, day);
    format(FamilyData[family_count][fCreatingDate], 16, "%02d/%02d/%d", day, month,year);
    strmid (FamilyData[family_count][fName], sFamilyName, 0, strlen(sFamilyName), strlen(sFamilyName)+5);

    FamilyData[family_count][fOwnerID] = mysqlID;

    for(new i = MAX_FAMILY_VEHICLES-1; i != -1; i--)
            FamilyData[family_count][fVehicleID][i] = INVALID_VEHICLE_ID;

    FamilyData[family_count][fColorID] =
    FamilyData[family_count][fSeasonExp] =
    FamilyData[family_count][fTypeID] =
    FamilyData[family_count][fOffice] =
    FamilyData[family_count][fCaptZoneCount] =
    FamilyData[family_count][fMoney] =
    FamilyData[family_count][fCaptureAllowed] = 0;

    FamilyData[family_count][fMembersCount] = 1;
    FamilyData[family_count][fHouseID] = INVALID_HOUSE_ID;

    FamilyData[family_count][fLevel] =
    FamilyData[family_count][fExp] = 1;

    format(FAMILY_RANG[family_count][0],16,"Новичок");
    format(FAMILY_RANG[family_count][1],16,"Свояк");
    format(FAMILY_RANG[family_count][2],16,"Прошаренный");
    format(FAMILY_RANG[family_count][3],16,"Бывалый");
    format(FAMILY_RANG[family_count][4],16,"Местный");
    format(FAMILY_RANG[family_count][5],16,"Брат");
    format(FAMILY_RANG[family_count][6],16,"Трудяга");
    format(FAMILY_RANG[family_count][7],16,"Смотрящий");
    format(FAMILY_RANG[family_count][8],16,"Заместитель");
    format(FAMILY_RANG[family_count][9],16,"Отец");

    for(new i = F_ALL_COUNT-1; i != -1; i--)
    {
        FamilyData[family_count][fSettingRang][i] = MAX_FAMILY_RANG;
        if(i < MAX_FAMILY_RANG)
        {
            FamilyData[family_count][fSkinID][i] =
            FamilyData[family_count][fSkinMan][i] =
            FamilyData[family_count][fSkinWoman][i] = 0;
        }
    }
    UpdateFamilyType(family_count);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `family` (`name`, `owner_id`, `members_count`, `creating_date`, `level`, `exp`) VALUES ( '%s', %d, '1', '%s', '1', '1')",
        FamilyData[family_count][fName], FamilyData[family_count][fOwnerID], FamilyData[family_count][fCreatingDate]);
    mysql_tquery(con_bd, STRING_GLOBAL, "AdminCreateFamily_Create", "iiss", playerid, mysqlID, sNick, sFamilyName);
    return 1;
}

this::AdminCreateFamily_Create(playerid, mysqlID, sNick[], sFamilyName[])
{
    FamilyData[family_count][fMysqlID] = cache_insert_id();

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `family_id` = %d, `family_rang` = 10, \
         `family_exp` = 0, `family_mute` = 0, `family_enter` = '%e' WHERE `id` = %d",
        FamilyData[family_count][fMysqlID], FamilyData[family_count][fCreatingDate], mysqlID);
    mysql_tquery(con_bd, STRING_GLOBAL);

    family_count++;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы успешно создали семью "I"%s"W" для "I"%s", sFamilyName, sNick);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Создание семьи", STRING_GLOBAL, "Закрыть", "");

    Log(LOG_player, INFO, "%s[%d](%s %s) создал cемью %s для %s | #AdminLogs #Family",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        sFamilyName, sNick);
    return 1;
}