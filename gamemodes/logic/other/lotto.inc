GetPlayerLottoPrize(type, price)
{
    new idx = -1;
    switch(type)
    {
        case TYPE_GIVE_ITEM_SKIN:
        {
            new skin_list[34] = {28, 273, 29, 48, 21, 23, 33, 22, 30, 47, 242, 241, 185, 19, 297, 293, 292, 291, 82, 83, 84, 289, 17, 46, 228, 295, 294, 296, 299, 249, 76, 219, 91, 214};
            return skin_list[random(sizeof(skin_list) - 1)];
        }
        case TYPE_GIVE_ITEM_VEHICLE:
        {
            if(price > 2500000) price = 2500000;
            for(new i, j = sizeof(gVehicleData); i < j; i++)
            {
                if(GetVehicleData(i, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS || GetVehicleData(i, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE || GetVehicleData(i, E_VD_TYPE) == VEHICLE_STATE_TRAIN) continue;
                if(GetVehicleData(i, E_VD_PRICE) >= price / 2 && GetVehicleData(i, E_VD_PRICE) <= price) return GetVehicleData(i, E_VD_ID);
            }
        }
    }
    return idx;
}

forward lotto_results();
public lotto_results()
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return 1;
    new temp_mysql_id, nickNameWin[MAX_PLAYER_NAME], playerid = INVALID_PLAYER_ID;
    cache_get_value_int(random(rows), "id", temp_mysql_id);

    foreach(new i: Player)
    {
        if(!p_info[i][loggedIn]) continue;
        if(p_info[i][lotto] != 0) p_info[i][lotto] = 0;

        if(p_info[i][ID] == temp_mysql_id)
        {
            f(nickNameWin, "%s", get_name(i));
            playerid = i;
        }
    }

    if(playerid == INVALID_PLAYER_ID)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name` FROM `accounts` WHERE `id` = %d LIMIT 1", temp_mysql_id);
        new Cache:result = mysql_query(con_bd, STRING_GLOBAL);

        if(cache_num_rows() == 0)
        {
            cache_delete(result);
            return 1;
        }

        cache_get_value_name(0, "name", nickNameWin, MAX_PLAYER_NAME);
        cache_delete(result);
    }

    new type = random(2) == 0 ? TYPE_GIVE_ITEM_SKIN : TYPE_GIVE_ITEM_VEHICLE, idx = GetPlayerLottoPrize(type, rows * 50000);

    mysql_tquery(con_bd, "UPDATE `accounts` SET `lotto` = 0 WHERE `lotto` > 0", "", "");

    if(idx != -1)
    {
        if(playerid != INVALID_PLAYER_ID)
        {
            SetPlayerItem(playerid, 3, p_info[playerid][ID], type, idx);
            SendMesAll(0xFFD700FF, "Внимание! "W"Победитель лотереи становится %s. Выигрыш: %s.", get_name(playerid), GetPrizeItemsName(type, idx));
        }
        else
        {
            SetPlayerItem(INVALID_PLAYER_ID, 3, temp_mysql_id, type, idx);

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Поздравляем, вы победили в лотереи. "W"Выигрыш: "I"%s.", GetPrizeItemsName(type, idx));
            AddNotify(temp_mysql_id, STRING_GLOBAL);

            SendMesAll(0xFFD700FF, "Внимание! "W"Победитель лотереи становится %s. Выигрыш: %s.", nickNameWin, GetPrizeItemsName(type, idx));
        }
    } else SendMesAll(0xFFD700FF, "Внимание! "W"Победитель лотереи не определен.");
    return 1;
}

CMD:lottohelp(playerid, params[])
{
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация о лотереи", ""W"\
    Лотерея — это организованная азартная игра, при которой распределение выгод и убытков зависит от\n\
    случайного выбора того или иного номера, который обычно указан на лотерейном билете.\n\n\
    Приобрести её можно в "I"\"Магазине 24/7\""W" за "I"50000$."W"\n\n\
    Каждый день в "I"20:30"W" по МСК случайным образом определяется победитель, который получает\n\
    случайный приз в виде транспортного средства или скина, стоимость которого зависит от потраченных\n\
    денежных средств на приобретение билета.", "ОК", "");
    return 1;
}