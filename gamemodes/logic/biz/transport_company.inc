SendTransportCompanyMes(idx, type, color, str[])
{
    switch(type)
    {
        case 0:
        {
            foreach(new i : Player)
            {
                if(!p_info[i][loggedIn]) continue;
                if(p_info[i][taxi_idx] != idx) continue;
                SendMes(i, color, str);
            }
        }
        case 1:
        {
            foreach(new i : Player)
            {
                if(!p_info[i][loggedIn]) continue;
                if(p_info[i][tc_idx] != idx) continue;
                SendMes(i, color, str);
            }
        }
    }
    return 1;
}

enum
{
    TC_PLAYER_MENU = 1,
    TC_MINI_STATS,
    TC_INVITE,
    TC_UNINVITE,
    TC_HELP,
    TC_OWNER_MENU,
    TC_MAIN_STATS,
    TC_PERCENT,
    TC_FARE
}

ShowDialogBiz(playerid, dialog_id)
{
    new idx = p_temp[playerid][p_tc_id], type = b_info[idx][_tip];
    switch(dialog_id)
    {
        case TC_PLAYER_MENU:
        {
            ShowPlayerDialog(playerid, D_PLAYER_TC_MENU, DIALOG_STYLE_LIST, ""I"Меню", ""I"[1]"W" Информация\n"I"[2]"W" Устроиться на работу\n"I"[3]"W" Уволиться с работы\n"I"[4]"W" Помощь по работе", "Далее", "Отмена");
        }
        case TC_MINI_STATS:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Название: "I"%s [%d]"W"\n\
            Владелец: "I"%s"W"\n\
            Гос. стоимость: "I"%d$"W"\n\n\
            Процент взимаемый с сотрудников: "I"%d"W"\n", b_info[idx][_name], b_info[idx][b_mysql_id], b_info[idx][_owner], b_info[idx][_price], b_info[idx][_percent]);

            if(type == B_TAXI)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\
                Тарифы:\n\
                \tЭконом: "I"%d$"W"\n\
                \tКомфорт: "I"%d$"W"\n\
                \tМикроавтобус: "I"%d$"W"\n\
                \tБизнес: "I"%d$"W"\n", STRING_GLOBAL, b_info[idx][b_fare][0], b_info[idx][b_fare][1], b_info[idx][b_fare][2], b_info[idx][b_fare][3]);
            }

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация", STRING_GLOBAL, "Закрыть", "");
        }
        case TC_INVITE:
        {
            new temp_biz_id = GetPlayerBizzIDType(playerid, type);
            if(temp_biz_id != INVALID_BIZZ_ID)
            {
                if(temp_biz_id == idx) return SendError(playerid, "Вы уже владелец этого бизнеса.");
                SendError(playerid, "Вы владелец %s %s [%d].", type == B_TRUCKER ? "транспортной компании" : "таксопарка", b_info[temp_biz_id][_name], b_info[temp_biz_id][b_mysql_id]);
                return 1;
            }

            switch(type)
            {
                case B_TAXI:
                {
                    if(p_info[playerid][taxi_idx] != 0 && p_info[playerid][taxi_idx] != idx)
                    {
                        new temp_biz_id = p_info[playerid][taxi_idx];
                        SendError(playerid, "Вы уже работаете в таксопарке %s [%d].", b_info[temp_biz_id][_name], b_info[temp_biz_id][b_mysql_id]);
                        return 1;
                    }
                    if(p_info[playerid][taxi_idx] == idx) return SendError(playerid, "Вы уже работаете в этом таксопарке.");
                }
                case B_TRUCKER:
                {
                    if(p_info[playerid][tc_idx] != 0 && p_info[playerid][tc_idx] != idx)
                    {
                        new temp_biz_id = p_info[playerid][tc_idx];
                        SendError(playerid, "Вы уже работаете в транспортной компании %s [%d].", b_info[temp_biz_id][_name], b_info[temp_biz_id][b_mysql_id]);
                        return 1;
                    }
                    if(p_info[playerid][tc_idx] == idx) return SendError(playerid, "Вы уже работаете в этой транспортной компании.");
                }
            }

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Вы действительно хотите устроиться в \"%s\" %s?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Устроившись работать в эту %s без одобрения владельца или заместителя, Вы будете зарабатывать на 30 процентов меньше.", bizz_type_name[type], b_info[idx][_name]);

            ShowPlayerDialog(playerid, D_PLAYER_TC_INVITE, DIALOG_STYLE_MSGBOX, ""I"Устройство на работу", STRING_GLOBAL, "Да", "Нет");
        }
        case TC_UNINVITE:
        {
            new temp_biz_id = GetPlayerBizzIDType(playerid, type);
            if(temp_biz_id != INVALID_BIZZ_ID)
            {
                if(temp_biz_id == idx) return SendError(playerid, "Вы уже владелец этого бизнеса.");
                SendError(playerid, "Вы владелец %s %s [%d].", type == B_TRUCKER ? "транспортной компании" : "таксопарка", b_info[temp_biz_id][_name], b_info[temp_biz_id][b_mysql_id]);
                return 1;
            }

            switch(type)
            {
                case B_TAXI:
                {
                    if(p_info[playerid][taxi_idx] == 0) 
                        return SendError(playerid, "Вы не работаете в таксопарке.");
                    if(p_info[playerid][taxi_idx] != idx)
                    {
                        new temp_biz_id = p_info[playerid][taxi_idx];
                        SendError(playerid, "Вы работаете в таксопарке %s [%d].", b_info[temp_biz_id][_name], b_info[temp_biz_id][b_mysql_id]);
                        return 1;
                    }
                }
                case B_TRUCKER:
                {
                    if(p_info[playerid][tc_idx] == 0) 
                        return SendError(playerid, "Вы не работаете в транспортной компании.");
                    if(p_info[playerid][tc_idx] != idx)
                    {
                        new temp_biz_id = p_info[playerid][tc_idx];
                        SendError(playerid, "Вы работаете в транспортной компании %s [%d].", b_info[temp_biz_id][_name], b_info[temp_biz_id][b_mysql_id]);
                        return 1;
                    }
                }
            }

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Вы действительно хотите уволиться из \"%s\" %s?", bizz_type_name[type], b_info[idx][_name]);

            ShowPlayerDialog(playerid, D_PLAYER_TC_UNINVITE, DIALOG_STYLE_MSGBOX, ""I"Уволиться с работы", STRING_GLOBAL, "Да", "Нет");
        }
        case TC_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            if(type == B_TAXI) for(new i; i < sizeof(TaxiInfoList); i++) strcat(STRING_GLOBAL, TaxiInfoList[i]);
            else for(new i; i < sizeof(TruckInfoList); i++) strcat(STRING_GLOBAL, TruckInfoList[i]);

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Помощь по работе", STRING_GLOBAL, "Закрыть", "");
        }
        case TC_OWNER_MENU:
        {
            new bizz_id = GetPlayerBizzIDType(playerid, type);
            if(bizz_id == INVALID_BIZZ_ID)
                return SendError(playerid, "Вы не являетесь владельцем или заместителем в %s.", type == B_TAXI ? "таксопарке" : "транспортной компании");

            switch(type)
            {
                case B_TAXI:
                {
                    if(p_info[playerid][taxi_idx] != idx) return SendError(playerid, "Вы не работаете в этом таксопарке.");
                    if(p_info[playerid][taxi_rank] < 2) return SendError(playerid, "Вы не являетесь владельцем или заместителем в этом таксопарке.");
                }
                case B_TRUCKER:
                {
                    if(p_info[playerid][tc_idx] != idx) return SendError(playerid, "Вы не работаете в этой транспортной компании.");
                    if(p_info[playerid][tc_rank] < 2) return SendError(playerid, "Вы не являетесь владельцем или заместителем в этой транспортной компании.");
                }
            }
            /*
            if(b_info[idx][b_paydays_received] == -1)
            {
                SendError(playerid, "Действия над бизнесом заблокированы.");
                return SendInfo(playerid, "Имущество будет продано в 8 вечера в гос по причине недостаточного Вашего онлайна.");
            }
            */
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
            "I"[1]"W" Информация\n\
            "I"[2]"W" Сотрудники\n\
            "I"[3]"W" Изменить процент взимаемый с сотрудников\n\
            "I"[4]"W" Изменить тариф");

            ShowPlayerDialog(playerid, D_TC, DIALOG_STYLE_LIST, ""I"Управление", STRING_GLOBAL, "Далее", "Отмена");
        }
        case TC_MAIN_STATS:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Название: "I"%s [%d]"W"\n\
            Владелец: "I"%s"W"\n\
            Гос. стоимость: "I"%d$"W"\n\n\
            Процент взимаемый с сотрудников: "I"%d"W"\n", b_info[idx][_name], b_info[idx][b_mysql_id], b_info[idx][_owner], b_info[idx][_price], b_info[idx][_percent]);

            if(type == B_TAXI)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\
                Тарифы:\n\
                \tЭконом: "I"%d$"W"\n\
                \tКомфорт: "I"%d$"W"\n\
                \tМикроавтобус: "I"%d$"W"\n\
                \tБизнес: "I"%d$"W"\n", STRING_GLOBAL, b_info[idx][b_fare][0], b_info[idx][b_fare][1], b_info[idx][b_fare][2], b_info[idx][b_fare][3]);
            }

            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\
            Сотрудников: "I"%d"W"\n\n\
            Оплата в день: "I"%d$"W"\n\
            Количество оплаченных дней: "I"%d (%d час(-а/-ов))"W"\n\n\
            Денежных средств в кассе: "I"%d$", STRING_GLOBAL, GetBizMembersCount(idx), bizz_tax[type], b_info[idx][b_rent] / 24, b_info[idx][b_rent], b_info[idx][_bank]);

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация", STRING_GLOBAL, "Закрыть", "");
        }
        case TC_PERCENT:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Введите процент, который хотите взимать с сотрудников:\n\n\
            Процент на данный момент: "I"%d"W"\n\n\
            {"#cLIGHTRED"}Обратите внимание! Процент должен быть не менее 10 и не более 30.", b_info[idx][_percent]);

            ShowPlayerDialog(playerid, D_TC_PERCENT, DIALOG_STYLE_INPUT, ""I"Изменение процента", STRING_GLOBAL, "Далее", "Отмена");
        }
        case TC_FARE:
        {
            if(type != B_TAXI) return SendError(playerid, "Изменение тарифа доступно только в службе такси.");
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Введите тип и стоимость через запятую:\n\n\
            Информация о типах:\n\n\
            \t"I"[1]"W" Эконом.\n\
            \t"I"[2]"W" Комфорт.\n\
            \t"I"[3]"W" Микроавтобус.\n\
            \t"I"[4]"W" Бизнес.\n\n\
            Информация о стоимости:\n\n\
            \tЭконом: не менее "I"200$"W" и не более "I"400$."W"\n\
            \tКомфорт: не менее "I"250$"W" и не более "I"500$."W"\n\
            \tМикроавтобус: не менее "I"200$"W" и не более "I"400$."W"\n\
            \tБизнес: не менее "I"500$"W" и не более "I"1000$."W"\n\n\
            Тарифы на данный момент:\n\n\
            \tЭконом: "I"%d$."W"\n\
            \tКомфорт: "I"%d$."W"\n\
            \tМикроавтобус: "I"%d$."W"\n\
            \tБизнес: "I"%d$.", b_info[idx][b_fare][0], b_info[idx][b_fare][1], b_info[idx][b_fare][2], b_info[idx][b_fare][3]);

            ShowPlayerDialog(playerid, D_TC_FARE, DIALOG_STYLE_INPUT, ""I"Изменение тарифа", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

GetBizPercent(playerid, type, salary)
{
    if(p_info[playerid][taxi_percent] == 0 && p_info[playerid][tc_percent] == 0) return salary;
    new count;
    switch(type)
    {
        case TYPE_TC_TAXI: count = floatround(salary / 100 * p_info[playerid][taxi_percent], floatround_ceil);
        case TYPE_TC_TRUCKER: count = floatround(salary / 100 * p_info[playerid][tc_percent], floatround_ceil);
    }
    salary = salary - count;
    p_temp[playerid][fix_bug_biz_tc_salary] = count;
    return salary;
}

TransferBizMoney(playerid, type, money)
{
    if(p_info[playerid][taxi_idx] == 0 && p_info[playerid][tc_idx] == 0) return 1;
    new biz_id = type == TYPE_TC_TAXI ? p_info[playerid][taxi_idx] : p_info[playerid][tc_idx], mafia_money = (money / 100) * 20;

    if(b_info[biz_id][_prod] >= money / 100)
    {
        b_info[biz_id][_prod] -= money / 100;
        b_info[biz_id][_bank] += money - mafia_money;
        AddMafiaBank(biz_id, mafia_money);

        biz_finka[biz_id] += money;
        UpdateIntForFinanceBiz(biz_id, money);
    }

    switch(type)
    {
        case TYPE_TC_TAXI:
        {
            p_info[playerid][taxi_salary] += money;
            p_info[playerid][taxi_salary_all] += money;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_salary` = %d, `taxi_salary_all` = %d WHERE `id` = %d",
            p_info[playerid][taxi_salary], p_info[playerid][taxi_salary_all], p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        case TYPE_TC_TRUCKER:
        {
            p_info[playerid][tc_salary] += money;
            p_info[playerid][tc_salary_all] += money;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_salary` = %d, `tc_salary_all` = %d WHERE `id` = %d",
            p_info[playerid][tc_salary], p_info[playerid][tc_salary_all], p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

GetBizVehicleType(vehicleid)
{
    new type, vehicle_model = GetVehicleModelEx(vehicleid);
    switch(vehicle_model)
    {
        case 420, 438: type = 0;
        case 418, 482, 431, 437: type = 2;
        default:
        {
            switch(GetVehicleData(vehicle_model, E_VD_CLASS))
            {
                case VEHICLE_CLASS_NOPE: type = 0;
                case VEHICLE_CLASS_C, VEHICLE_CLASS_B: type = 1;
                default: type = 3;
            }
        }
    }
    return type;
}

GetBizMembersCount(idx)
{
    new string[256], Cache:cache, memberscount = 0;
    mysql_format(con_bd, string, sizeof(string), "SELECT COUNT(*) AS `memberscount` FROM `accounts` WHERE `%s` = %d", b_info[idx][_tip] == B_TAXI ? "taxi_idx" : "tc_idx", idx);
    cache = mysql_query(con_bd, string, true);
    if(cache_num_rows()) cache_get_value_name_int(0, "memberscount", memberscount);
    cache_delete(cache);
    return memberscount;
}

GetBizFare(idx, vehicleid)
{
    new fare, vehicle_model = GetVehicleModelEx(vehicleid);
    switch(vehicle_model)
    {
        case 420, 438: fare = b_info[idx][b_fare][0];
        case 418, 482, 431, 437: fare = b_info[idx][b_fare][2];
        default:
        {
            switch(GetVehicleData(vehicle_model, E_VD_CLASS))
            {
                case VEHICLE_CLASS_NOPE: fare = b_info[idx][b_fare][0];
                case VEHICLE_CLASS_C, VEHICLE_CLASS_B: fare = b_info[idx][b_fare][1];
                default: fare = b_info[idx][b_fare][3];
            }
        }
    }
    return fare;
}

forward OnPlayerSelectTransportCompany(playerid, type, idx, params[], first_parameter, scdparams[], second_parameter);
public OnPlayerSelectTransportCompany(playerid, type, idx, params[], first_parameter, scdparams[], second_parameter)
{
    switch(type)
    {
        case 1:
        {
            if(!cache_num_rows()) return UpdatePlayerList(playerid);
            new temp_username[MAX_PLAYER_NAME], temp_tc_rank, temp_tc_salary, temp_tc_salary_all, temp_lastenter[16];
            cache_get_value_name(0, "name", temp_username);
            switch(idx)
            {
                case TYPE_TC_TAXI:
                {
                    cache_get_value_name_int(0, "taxi_rank", temp_tc_rank);
                    cache_get_value_name_int(0, "taxi_salary", temp_tc_salary);
                    cache_get_value_name_int(0, "taxi_salary_all", temp_tc_salary_all);
                }
                case TYPE_TC_TRUCKER:
                {
                    cache_get_value_name_int(0, "tc_rank", temp_tc_rank);
                    cache_get_value_name_int(0, "tc_salary", temp_tc_salary);
                    cache_get_value_name_int(0, "tc_salary_all", temp_tc_salary_all);
                }
            }
            cache_get_value_name(0, "lastenter", temp_lastenter);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Ник: "I"%s"W"\n\
            Ранг: "I"%s [%d]"W"\n\n\
            Принесенный заработок сегодня: "I"$%d"W"\n\
            Принесенный заработок всего: "I"$%d"W"\n\n\
            Последний вход: "I"%s", temp_username, TransportCompanyRankName[temp_tc_rank], temp_tc_rank, temp_tc_salary, temp_tc_salary_all, temp_lastenter);
            ShowPlayerDialog(playerid, D_TC_MEMBERS_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о игроке", STRING_GLOBAL, "Назад", "" );
        }
        case 2:
        {
            if(!cache_num_rows()) return SendError(playerid, "Ничего не найдено.");
            new biz_id = p_temp[playerid][p_tc_id], temp_username[MAX_PLAYER_NAME], temp_tc_rank;
            cache_get_value_name(0, "name", temp_username);
            switch(idx)
            {
                case TYPE_TC_TAXI:
                {
                    cache_get_value_name_int(0, "taxi_rank", temp_tc_rank);
                    if(p_info[playerid][taxi_rank] < temp_tc_rank) return SendError(playerid, "У Вас слишком маленький ранг в таксопарке.");
                    if(first_parameter == b_info[biz_id][b_user_id]) return SendError(playerid, "Данный игрок владелец таксопарка.");
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_rank` = 0, `taxi_idx` = 0, `taxi_percent` = 0, `taxi_salary` = 0, `taxi_salary_all` = 0 WHERE `id` = %d", first_parameter);
                    mysql_tquery(con_bd, STRING_GLOBAL, "", "");
                    SendAccess(playerid, "Вы уволили %s из таксопарка.", temp_username);
                }
                case TYPE_TC_TRUCKER:
                {
                    cache_get_value_name_int(0, "tc_rank", temp_tc_rank);
                    if(p_info[playerid][tc_rank] < temp_tc_rank) return SendError(playerid, "У Вас слишком маленький ранг в транспортной компании.");
                    if(first_parameter == b_info[biz_id][b_user_id]) return SendError(playerid, "Данный игрок владелец транспортной компании.");
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_rank` = 0, `tc_idx` = 0, `tc_percent` = 0, `tc_salary` = 0, `tc_salary_all` = 0 WHERE `id` = %d", first_parameter);
                    mysql_tquery(con_bd, STRING_GLOBAL, "", "");
                    SendAccess(playerid, "Вы уволили %s из транспортной компании.", temp_username);
                }
            }
            UpdatePlayerList(playerid);
        }
        case 3:
        {
            if(!cache_num_rows()) return SendError(playerid, "Ничего не найдено.");
            new biz_id = p_temp[playerid][p_tc_id], temp_username[MAX_PLAYER_NAME], temp_tc_rank;
            cache_get_value_name(0, "name", temp_username);
            switch(idx)
            {
                case TYPE_TC_TAXI:
                {
                    cache_get_value_name_int(0, "taxi_rank", temp_tc_rank);
                    if(p_info[playerid][taxi_rank] < temp_tc_rank) return SendError(playerid, "У Вас слишком маленький ранг в таксопарке.");
                    if(first_parameter == b_info[biz_id][b_user_id]) return SendError(playerid, "Данный игрок владелец таксопарка.");
                    temp_tc_rank++;
                    if(temp_tc_rank > 2) temp_tc_rank = 1;
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_rank` = %d WHERE `id` = %d", temp_tc_rank, first_parameter);
                    mysql_tquery(con_bd, STRING_GLOBAL, "", "");
                    SendAccess(playerid, "Вы изменили %s ранг в таксопарке на \"%s\".", temp_username, TransportCompanyRankName[temp_tc_rank]);
                }
                case TYPE_TC_TRUCKER:
                {
                    cache_get_value_name_int(0, "tc_rank", temp_tc_rank);
                    if(p_info[playerid][tc_rank] < temp_tc_rank) return SendError(playerid, "У Вас слишком маленький ранг в транспортной компании.");
                    if(first_parameter == b_info[biz_id][b_user_id]) return SendError(playerid, "Данный игрок владелец транспортной компании.");
                    temp_tc_rank++;
                    if(temp_tc_rank > 2) temp_tc_rank = 1;
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_rank` = %d WHERE `id` = %d", temp_tc_rank, first_parameter);
                    mysql_tquery(con_bd, STRING_GLOBAL, "", "");
                    SendAccess(playerid, "Вы изменили %s ранг в транспортной компании на \"%s\".", temp_username, TransportCompanyRankName[temp_tc_rank]);
                }
            }
            UpdatePlayerList(playerid);
        }
    }
    return 1;
}

CMD:tcinvite(playerid, params[])
{
    if(sscanf(params, "iu", params[0], params[1])) return SendInfo(playerid, "Используйте: /tcinvite [тип (1 - таксопарк, 2 - транспортная компания)] [id игрока]");
    if(!(1 <= params[0] <= 2)) return SendError(playerid, "Тип должен быть не менее 1 и не более 2.");
    if(params[1] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(!IsPlayerStream(5.0, playerid, params[1]) || pSpectateId[params[1]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(GetPVarInt(params[1],"BoneStol_ID")) return 1;
    new biz_id = INVALID_BIZZ_ID, type;
    switch(params[0])
    {
        case 1:
        {
            if(p_info[playerid][taxi_idx] == 0) return SendError(playerid, "Вы не работаете в таксопарке.");
            if(p_info[playerid][taxi_rank] < 2) return SendError(playerid, "Вы не являетесь заместителем или владельцем в таксопарке.");
            if(p_info[playerid][taxi_idx] == p_info[params[1]][taxi_idx])
                return SendError(playerid, "Игрок уже работает в этом таксопарке.");
            if(p_info[params[1]][taxi_idx] != 0)
            {
                biz_id = p_info[params[1]][taxi_idx];
                SendError(playerid, "Данный игрок уже работает в таксопарке %s [%d].", b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
                return 1;
            }
            if(p_info[params[1]][level] < 2) return SendError(playerid, "У игрока нет 2-ого уровня.");
            type = B_TAXI;
            biz_id = GetPlayerBizzIDType(params[1], type);
            if(biz_id != INVALID_BIZZ_ID)
            {
                SendError(params[1], "Игрок владелец %s %s [%d].", type == B_TRUCKER ? "транспортной компании" : "таксопарка", b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
                return 1;
            }
            biz_id = p_info[playerid][taxi_idx];
            SendAccess(playerid, "Вы предложили %s [%d] устроиться в таксопарк %s [%d].", get_name(params[1]), params[1], b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            SendInfo(params[1], "%s [%d] предложил Вам устроиться в таксопарк %s [%d].", get_name(playerid), playerid, b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            SetFreeSlotOffer(params[1], playerid, OFFER_ID_INVITE_TAXI);
        }
        case 2:
        {
            if(p_info[playerid][tc_idx] == 0) return SendError(playerid, "Вы не работаете в транспортной компании.");
            if(p_info[playerid][tc_rank] < 2) return SendError(playerid, "Вы не являетесь заместителем или владельцем в транспортной компании.");
            if(p_info[playerid][tc_idx] == p_info[params[1]][tc_idx])
                return SendError(playerid, "Игрок уже работает в этой транспортной компании.");
            if(p_info[params[1]][tc_idx] != 0)
            {
                biz_id = p_info[params[1]][tc_idx];
                SendError(playerid, "Данный игрок уже работает в транспортной компании %s [%d].", b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
                return 1;
            }
            if(p_info[params[1]][level] < 10) return SendError(playerid, "У игрока нет 10-ого уровня.");
            type = B_TRUCKER;
            biz_id = GetPlayerBizzIDType(params[1], type);
            if(biz_id != INVALID_BIZZ_ID)
            {
                SendError(params[1], "Игрок владелец %s %s [%d].", type == B_TRUCKER ? "транспортной компании" : "таксопарка", b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
                return 1;
            }

            biz_id = p_info[playerid][tc_idx];
            SendAccess(playerid, "Вы предложили %s [%d] устроиться в транспортную компанию %s [%d].", get_name(params[1]), params[1], b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            SendInfo(params[1], "%s [%d] предложил Вам устроиться в транспортную компанию %s [%d].", get_name(playerid), playerid, b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            SetFreeSlotOffer(params[1], playerid, OFFER_ID_INVITE_TC);
        }
    }
    return 1;
}

CMD:tcuninvite(playerid, params[0])
{
    if(sscanf(params, "iu", params[0], params[1])) return SendInfo(playerid, "Используйте: /tcuninvite [тип (1 - таксопарк, 2 - транспортная компания)] [id игрока]");
    if(!(1 <= params[0] <= 2)) return SendError(playerid, "Тип должен быть не менее 1 и не более 2.");
    if(params[1] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(!IsPlayerStream(5.0, playerid, params[1]) || pSpectateId[params[1]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(GetPVarInt(params[1],"BoneStol_ID")) return 1;
    new biz_id;
    switch(params[0])
    {
        case 1:
        {
            if(p_info[playerid][taxi_idx] == 0) return SendError(playerid, "Вы не работаете в таксопарке.");
            if(p_info[playerid][taxi_rank] < 2) return SendError(playerid, "Вы не являетесь заместителем или владельцем в таксопарке.");
            if(p_info[playerid][taxi_idx] != p_info[params[1]][taxi_idx])
                return SendError(playerid, "Игрок не работает в этом таксопарке.");
            if(p_info[playerid][taxi_rank] <= p_info[params[1]][taxi_rank])
                return SendError(playerid, "У вас не достаточно возможностей.");

            if(p_temp[params[1]][rented_veh] != INVALID_VEHICLE_ID)
            {
                new vehicleid = p_temp[params[1]][rented_veh];
                if(veh_info[vehicleid][v_npoType] == NPO_JOB && (veh_info[vehicleid][v_npoId] == JOB_TC_TAXI || veh_info[vehicleid][v_npoId] == JOB_TC_TRUCK))
                {
                    EndPlayerJob(params[1]);
                }
            }
            p_info[params[1]][taxi_idx] = 0;
            p_info[params[1]][taxi_rank] = 0;
            p_info[params[1]][taxi_percent] = 0;
            p_info[params[1]][taxi_salary] = 0;
            p_info[params[1]][taxi_salary_all] = 0;
            SendAccess(playerid, "Вы уволили %s [%d] из таксопарка %s [%d].", get_name(params[1]), params[1], b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            SendInfo(params[1], "%s [%d] уволил Вас из таксопарка %s [%d].", get_name(playerid), playerid, b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_idx` = 0, `taxi_rank` = 0, `taxi_percent` = 0, `taxi_salary` = 0, `taxi_salary_all` = 0 WHERE `id` = %d",
            p_info[params[1]][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        case 2:
        {
            if(p_info[playerid][tc_idx] == 0) return SendError(playerid, "Вы не работаете в транспортной компании.");
            if(p_info[playerid][tc_rank] < 2) return SendError(playerid, "Вы не являетесь заместителем или владельцем в транспортной компании.");
            if(p_info[playerid][tc_idx] != p_info[params[1]][tc_idx])
                return SendError(playerid, "Игрок не работает в этой транспортной компании.");
            if(p_info[playerid][tc_rank] <= p_info[params[1]][tc_rank])
                return SendError(playerid, "У вас не достаточно возможностей.");
            if(p_temp[params[1]][rented_veh] != INVALID_VEHICLE_ID)
            {
                new vehicleid = p_temp[params[1]][rented_veh];
                if(veh_info[vehicleid][v_npoType] == NPO_JOB && (veh_info[vehicleid][v_npoId] == JOB_TC_TAXI || veh_info[vehicleid][v_npoId] == JOB_TC_TRUCK))
                {
                    EndPlayerJob(params[1]);
                }
            }
            p_info[params[1]][tc_idx] = 0;
            p_info[params[1]][tc_rank] = 0;
            p_info[params[1]][tc_percent] = 0;
            p_info[params[1]][tc_salary] = 0;
            p_info[params[1]][tc_salary_all] = 0;
            SendAccess(playerid, "Вы уволили %s [%d] из транспортной компании %s [%d].", get_name(params[1]), params[1], b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            SendInfo(params[1], "%s [%d] уволил Вас из транспортной компании %s [%d].", get_name(playerid), playerid, b_info[biz_id][_name], b_info[biz_id][b_mysql_id]);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_idx` = 0, `tc_rank` = 0, `tc_percent` = 0, `tc_salary` = 0, `tc_salary_all` = 0 WHERE `id` = %d",
            p_info[params[1]][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

CMD:tcgiverank(playerid, params[0])
{
    if(sscanf(params, "iui", params[0], params[1], params[2])) return SendInfo(playerid, "Используйте: /tcgiverank [тип (1 - таксопарк, 2 - транспортная компания)] [id игрока] [ранг]");
    if(!(1 <= params[0] <= 2)) return SendError(playerid, "Тип должен быть не менее 1 и не более 2.");
    if(params[1] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(!(1 <= params[2] <= 2)) return SendError(playerid, "Ранг должен быть не менее 1 и не более 2.");
    if(!IsPlayerStream(5.0, playerid, params[1]) || pSpectateId[params[1]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(GetPVarInt(params[1],"BoneStol_ID")) return 1;
    new biz_id;
    switch(params[0])
    {
        case 1:
        {
            if(p_info[playerid][taxi_idx] == 0) return SendError(playerid, "Вы не работаете в таксопарке.");
            if(p_info[playerid][taxi_rank] < 3) return SendError(playerid, "Вы не являетесь заместителем или владельцем в таксопарке.");
            if(p_info[playerid][taxi_idx] != p_info[params[1]][taxi_idx])
                return SendError(playerid, "Игрок не работает в этом таксопарке.");
            if(p_info[playerid][taxi_rank] <= p_info[params[1]][taxi_rank])
                return SendError(playerid, "У вас не достаточно возможностей.");

            p_info[params[1]][taxi_rank] = params[2];
            SendAccess(playerid, "Вы изменили %s [%d] ранг в транспортрой компании %s [%d] на %s [%d].", get_name(params[1]), params[1], b_info[biz_id][_name], b_info[biz_id][b_mysql_id], TransportCompanyRankName[p_info[params[1]][taxi_rank]], p_info[params[1]][taxi_rank]);
            SendInfo(params[1], "%s [%d] изменил Вам ранг в транспортрой компании %s [%d] на %s [%d].", get_name(playerid), playerid, b_info[biz_id][_name], b_info[biz_id][b_mysql_id], TransportCompanyRankName[p_info[params[1]][taxi_rank]], p_info[params[1]][taxi_rank]);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_rank` = %d WHERE `id` = %d",
            p_info[params[1]][taxi_rank], p_info[params[1]][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        case 2:
        {
            if(p_info[playerid][tc_idx] == 0) return SendError(playerid, "Вы не работаете в транспортной компании.");
            if(p_info[playerid][tc_rank] < 3) return SendError(playerid, "Вы не являетесь заместителем или владельцем в транспортной компании.");
            if(p_info[playerid][tc_idx] != p_info[params[1]][tc_idx])
                return SendError(playerid, "Игрок не работает в этой транспортной компании.");
            if(p_info[playerid][tc_rank] <= p_info[params[1]][tc_rank])
                return SendError(playerid, "У вас не достаточно возможностей.");

            p_info[params[1]][tc_rank] = params[2];
            SendAccess(playerid, "Вы изменили %s [%d] ранг в транспортрой компании %s [%d] на %s [%d].", get_name(params[1]), params[1], b_info[biz_id][_name], b_info[biz_id][b_mysql_id], TransportCompanyRankName[p_info[params[1]][tc_rank]], p_info[params[1]][tc_rank]);
            SendInfo(params[1], "%s [%d] изменил Вам ранг в транспортрой компании %s [%d] на %s [%d].", get_name(playerid), playerid, b_info[biz_id][_name], b_info[biz_id][b_mysql_id], TransportCompanyRankName[p_info[params[1]][tc_rank]], p_info[params[1]][tc_rank]);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_rank` = %d WHERE `id` = %d",
            p_info[params[1]][tc_rank], p_info[params[1]][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

CMD:ftc(playerid, params[])
{
    if(p_info[playerid][taxi_idx] == 0 && p_info[playerid][tc_idx] == 0) return SendError(playerid, "Вы не работаете в таксопарке или транспортной компании.");
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    new text[144];
    if(sscanf(params, "is[144]", params[0], text)) return SendInfo(playerid, "Используйте: /ftc [тип (1 - таксопарк, 2 - транспортная компания)] [текст]");
    if(params[0] < 1 || params[0] > 2) return SendError(playerid, "Тип не может быть менее 1 и более 2.");
    if(!(1 <= strlen(text) <= 60)) return SendError(playerid, "Длина введеного текста должна быть не менее 1 и не более 60 символов.");
    if(AdvertisingCheck(text)) return AdvertisingPunishment(playerid, text, 1);
    STRING_GLOBAL[0] = EOS;
    switch(params[0])
    {
        case 1:
        {
            new idx = p_info[playerid][taxi_idx];
            if(idx == 0) return SendError(playerid, "Вы не работаете в таксопарке.");
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[%s: %s [%d]]: %s [%d]: %s", bizz_type_name[b_info[idx][_tip]], b_info[idx][_name], b_info[idx][b_mysql_id], get_name(playerid), playerid, text);
            SendTransportCompanyMes(idx, 0, 0x33CC66FF, STRING_GLOBAL);
        }
        case 2:
        {
            new idx = p_info[playerid][tc_idx];
            if(idx == 0) return SendError(playerid, "Вы не работаете в транспортной компании.");
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[%s: %s [%d]]: %s [%d]: %s", bizz_type_name[b_info[idx][_tip]], b_info[idx][_name], b_info[idx][b_mysql_id], get_name(playerid), playerid, text);
            SendTransportCompanyMes(idx, 1, 0x33CC66FF, STRING_GLOBAL);
        }
    }
    return 1;
}

CMD:ftcb(playerid, params[])
{
    if(p_info[playerid][taxi_idx] == 0 && p_info[playerid][tc_idx] == 0) return SendError(playerid, "Вы не работаете в таксопарке или транспортной компании.");
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    new text[144];
    if(sscanf(params, "is[144]", params[0], text)) return SendInfo(playerid, "Используйте: /ftc [тип (1 - таксопарк, 2 - транспортная компания)] [текст]");
    if(params[0] < 1 || params[0] > 2) return SendError(playerid, "Ранг не может быть менее 1 и более 2.");
    if(!(1 <= strlen(params[1]) <= 60)) return SendError(playerid, "Длина введеного текста должна быть не менее 1 и не более 60 символов.");
    if(AdvertisingCheck(text)) return AdvertisingPunishment(playerid, text, 1);
    STRING_GLOBAL[0] = EOS;
    switch(params[0])
    {
        case 1:
        {
            new idx = p_info[playerid][taxi_idx];
            if(idx == 0) return SendError(playerid, "Вы не работаете в таксопарке.");
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "(( [%s: %s [%d]]: %s [%d]: %s ))", bizz_type_name[b_info[idx][_tip]], b_info[idx][_name], b_info[idx][b_mysql_id], get_name(playerid), playerid, text);
            SendTransportCompanyMes(idx, 0, 0x33CC66FF, STRING_GLOBAL);
        }
        case 2:
        {
            new idx = p_info[playerid][tc_idx];
            if(idx == 0) return SendError(playerid, "Вы не работаете в транспортной компании.");
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "(( [%s: %s [%d]]: %s [%d]: %s ))", bizz_type_name[b_info[idx][_tip]], b_info[idx][_name], b_info[idx][b_mysql_id], get_name(playerid), playerid, text);
            SendTransportCompanyMes(idx, 1, 0x33CC66FF, STRING_GLOBAL);
        }
    }
    return 1;
}

LoadVehicleTC()
{
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 400, 1278.5430, -1804.2871, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 400, 1278.5430, -1809.3669, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 418, 1278.5430, -1814.3669, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 418, 1278.5430, -1819.4070, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 420, 1278.5430, -1824.4470, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 420, 1278.5430, -1829.4670, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 438, 1278.5430, -1834.5070, 13.0431, 90.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 438, 1259.3604, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 1254.3405, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 1249.3204, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 1244.3004, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 1239.2604, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 1234.2205, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 1229.1804, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 1224.1604, -1833.0980, 13.0431, 0.0000, 6, 6, 600, 0, 105);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 1240.3895, -1819.3636, 13.0431, -90.0000, 6, 6, 600, 0, 105);

    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 400, -2184.3557, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 400, -2180.0957, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 418, -2175.8357, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 418, -2171.5757, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 420, -2167.3157, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 420, -2163.0557, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 438, -2163.0557, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 438, -2167.3157, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, -2171.5757, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, -2175.8357, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, -2180.0957, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, -2184.3557, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, -2214.1958, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, -2218.4558, 305.5224, 34.7753, 180.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, -2218.4558, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, -2214.1958, 294.1024, 34.7753, 0.0000, 6, 6, 600, 0, 106);

    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 400, 2845.4221, 1522.9749, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 400, 2845.4221, 1517.9550, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 418, 2845.4221, 1512.9150, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 418, 2845.4221, 1507.8550, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 420, 2845.4221, 1502.7950, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 420, 2845.4221, 1497.7750, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 438, 2845.4221, 1492.7550, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 438, 2845.4221, 1487.7350, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 2832.8821, 1487.7350, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 2832.8821, 1492.7550, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 2832.8821, 1497.7750, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 560, 2832.8821, 1502.7950, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 2832.8821, 1507.8550, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 2832.8821, 1512.9150, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 2832.8821, 1517.9550, 10.5464, 90.0000, 6, 6, 600, 0, 107);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TAXI, 415, 2832.8821, 1522.9749, 10.5464, 90.0000, 6, 6, 600, 0, 107);

    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -469.2543, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -474.2343, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -479.2143, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -484.1943, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -489.1743, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -494.1543, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -499.1343, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -504.1143, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -509.0943, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -514.0743, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -519.0543, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -524.0343, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -529.0143, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -533.9943, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -538.9743, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -543.9543, -473.1474, 25.9217, 180.0000, 1, 1, 600, 0, 108);

    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -227.9327, -230.4937, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -227.9327, -225.4537, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -227.9327, -220.4137, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -227.9327, -215.3737, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, -227.9327, -210.3337, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -227.9327, -205.2937, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -227.9327, -200.2537, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -227.9327, -195.2137, 1.8252, -90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -208.5127, -195.2137, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, -208.5127, -200.2537, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -208.5127, -205.2937, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -208.5127, -210.3337, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -208.5127, -215.3737, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -208.5127, -220.4137, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -208.5127, -225.4537, 1.8252, 90.0000, 1, 1, 600, 0, 109);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, -208.5127, -230.4937, 1.8252, 90.0000, 1, 1, 600, 0, 109);

    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, 49.6544, -260.2707, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, 49.9144, -255.2507, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, 50.3144, -250.2307, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, 50.6544, -245.2107, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 403, 50.9944, -240.1907, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, 51.3144, -235.1707, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, 51.6744, -230.1507, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, 51.9944, -225.1307, 2.0035, -94.0000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, 82.0847, -271.3165, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 514, 87.1047, -271.3365, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, 92.1247, -271.4365, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, 97.1447, -271.5965, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, 102.1647, -271.7365, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, 107.1847, -271.8365, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, 112.2047, -271.9565, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    CreateVehicleVEx(NPO_JOB, JOB_TC_TRUCK, 515, 117.2247, -272.0965, 2.0035, -1.5000, 1, 1, 600, 0, 110);
    return 1;
}
