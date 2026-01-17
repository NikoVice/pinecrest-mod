
#define MAX_TICKETS 10
this::ShowCarsTickets(playerid, back)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "У данного транспорта нет неоплаченных штрафов.");
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "[#] Офицер\tЦена\tОписание\tДата");
    if(p_temp[playerid][list_type]) f(STRING_GLOBAL, "%s\n{bccd32}<<{FFFFFF}\t-\t-\t-", STRING_GLOBAL);

    new amount, reason[12], temp_v_mysql_id, date[24], officername[MAX_PLAYER_NAME];
    STRING_GLOBAL[0] = EOS;
    if(!back)
    {

        for(new i = 0; i < rows; i++)
        {
            cache_get_value_name_int(i, "amount", amount);
            cache_get_value_name(i, "reason", reason);
            cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "officer", officername);
            f(STRING_GLOBAL, "%s\n"I"[%d]"W" %s\t$%d\t%.50s...\t%s", STRING_GLOBAL, i+1+p_temp[playerid][list_type]*MAX_TICKETS, officername, amount, reason, date);
        }
    }
    else
    {
        for(new i = rows-1; i >= 0; i--)
        {
            cache_get_value_name_int(i, "amount", amount);
            cache_get_value_name(i, "reason", reason);
            cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][rows-1-i]);
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "officer", officername);
            f(STRING_GLOBAL, "%s\n"I"[%d]"W" %s\t$%d\t%.50s...\t%s", STRING_GLOBAL, rows-i+p_temp[playerid][list_type]*MAX_TICKETS, officername, amount, reason, date);
        }
    }
    cache_get_value_name_int(0, "vehicle", temp_v_mysql_id);
    if(CountVehicleTicketsID(temp_v_mysql_id) > MAX_TICKETS*(p_temp[playerid][list_type]+1)) f(STRING_GLOBAL, "%s\n{bccd32}>>\t-\t-\t-", STRING_GLOBAL);
    return ShowPlayerDialog(playerid, D_VEHICLE_FINES, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список неоплаченных штрафов", STRING_GLOBAL, "Выбрать", "Закрыть");
}

this::ShowCarTicket(playerid)
{
    if(!cache_num_rows())
        return 1;
    new fetch[128], vehicleid = GetPlayerVehicleID(playerid), fractionid;
    if(vehicleid == 0) return SendError(playerid, "Вы не в автомобиле.");
    cache_get_value_name_int(0, "id", p_temp[playerid][p_listitem_int]);
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "{a9c4e4}Нарушитель:\t\t {ffffff}%s\n", GetVehicleName(vehicleid));

    cache_get_value_name(0, "officer", fetch);
    f(STRING_GLOBAL, "%s{a9c4e4}Оштрафовал:\t\t {ffffff}%s ", STRING_GLOBAL, fetch);

    cache_get_value_name_int(0, "faction", fractionid);
    f(STRING_GLOBAL, "%s[%s]\n", STRING_GLOBAL, GetFractionName(fractionid));

    cache_get_value_name_int(0, "amount", p_temp[playerid][p_listitem][0]);
    f(STRING_GLOBAL, "%s{a9c4e4}Сумма:\t\t\t {ffffff}$%i{a9c4e4}\n", STRING_GLOBAL, p_temp[playerid][p_listitem][0]);

    cache_get_value_name(0, "date", fetch);
    f(STRING_GLOBAL, "%s{a9c4e4}Дата:\t\t\t {ffffff}%s\n\n", STRING_GLOBAL, fetch);

    cache_get_value_name(0, "reason", fetch);
    f(STRING_GLOBAL, "%s{a9c4e4}Описание:{ffffff}\n%s", STRING_GLOBAL, fetch);

    if(IsPlayerFractionPolice(playerid) && p_info[playerid][fwork] == true && GetPVarInt(playerid, #ticketsuse) && p_temp[playerid][ATM_STATUS] == false)
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Подробности штрафа", STRING_GLOBAL, "Закрыть", "");
    else ShowPlayerDialog(playerid, D_VEHICLE_FINES_TAKE, DIALOG_STYLE_MSGBOX, ""I"Подробности штрафа", STRING_GLOBAL, "Забрать", "Назад");
    return 1;
}

this::ShowPlayersTickets(playerid, back)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "У Вас нет неоплаченных штрафов.");
    STRING_GLOBAL = "[#] Офицер\tЦена\tОписание\tДата";
    if(p_temp[playerid][list_type]) f(STRING_GLOBAL, "%s\n{bccd32}<<{FFFFFF}", STRING_GLOBAL);
    new amount, reason[12], date[24], officername[MAX_PLAYER_NAME];
    //p_temp[playerid][fine_count] = 0;
    if(!back)
    {
        for(new i = 0; i < rows; i++)
        {
            cache_get_value_name_int(i, "amount", amount);
            cache_get_value_name(i, "reason", reason);
            cache_get_value_name(i, "officer", officername);
            cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
            cache_get_value_name(i, "date", date);
            f(STRING_GLOBAL, "%s\n"I"[%d]"W" %s\t%i$\t%.50s...\t%s", STRING_GLOBAL, i+1+p_temp[playerid][list_type]*MAX_TICKETS, officername, amount, reason, date);
            //p_temp[playerid][fine_count] += amount;
        }
    }
    else
    {
        for(new i = rows-1; i >= 0; i--)
        {
            cache_get_value_name_int(i, "amount", amount);
            cache_get_value_name(i, "reason", reason);
            cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][rows-1-i]);
            cache_get_value_name(i, "date", date);
            f(STRING_GLOBAL, "%s\n"I"[%d]"W" %s\t%i$\t%.50s...\t%s", STRING_GLOBAL, rows-i+p_temp[playerid][list_type]*MAX_TICKETS, officername, amount, reason, date);
            //p_temp[playerid][fine_count] += amount;
        }
    }
    if(CountPlayerTicketsID(GetPVarInt(playerid, #tickets_show)) > MAX_TICKETS*(p_temp[playerid][list_type]+1)) f(STRING_GLOBAL, "%s\n{bccd32}>>", STRING_GLOBAL);
    //if(p_temp[playerid][ATM_STATUS] != false)
    //    f(STRING_GLOBAL, "%s\nОплатить все штрафы(на странице): %d$ ", STRING_GLOBAL, p_temp[playerid][fine_count]);
    ShowPlayerDialog(playerid, D_PLAYER_FINES, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список неоплаченных штрафов", STRING_GLOBAL, "Выбрать", "Закрыть");
    return 1;
}

this::ShowPlayerTicket(playerid)
{
    if(!cache_num_rows()) return 1;
    new fetch[128], ownername[MAX_PLAYER_NAME], fractionid;
    STRING_GLOBAL[0] = EOS;
    cache_get_value_name_int(0, "id", p_temp[playerid][p_listitem_int]);

    cache_get_value_name(0, "ownername", ownername);
    f(STRING_GLOBAL, "{a9c4e4}Нарушитель:\t\t {ffffff}%s\n", ownername);

    cache_get_value_name(0, "officer", fetch);
    f(STRING_GLOBAL, "%s{a9c4e4}Оштрафовал:\t\t {ffffff}%s ", STRING_GLOBAL, fetch);

    cache_get_value_name_int(0, "faction", fractionid);
    f(STRING_GLOBAL, "%s[%s]\n", STRING_GLOBAL, GetFractionName(fractionid));

    cache_get_value_name_int(0, "amount", p_temp[playerid][p_listitem][0]);
    f(STRING_GLOBAL, "%s{a9c4e4}Сумма:\t\t\t {ffffff}$%i\n", STRING_GLOBAL, p_temp[playerid][p_listitem][0]);

    cache_get_value_name(0, "date", fetch);
    f(STRING_GLOBAL, "%s{a9c4e4}Дата:\t\t\t {ffffff}%s\n\n", STRING_GLOBAL, fetch);

    cache_get_value_name(0, "reason", fetch);
    f(STRING_GLOBAL, "%s{a9c4e4}Описание:{ffffff}\n%s", STRING_GLOBAL, fetch);

    if(IsPlayerFractionPolice(playerid) && p_info[playerid][fwork] == true && GetPVarInt(playerid, #ticketsuse) && p_temp[playerid][ATM_STATUS] == false)
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Подробности штрафа", STRING_GLOBAL, "Закрыть", "");
    else if(p_temp[playerid][ATM_STATUS] == true) ShowPlayerDialog(playerid, D_PLAYER_FINES_PAY, DIALOG_STYLE_MSGBOX, ""I"Подробности штрафа", STRING_GLOBAL, "Оплатить", "Назад");
    return 1;
}
#define MAX_PLAYER_FINE 20
GivePlayerTicket(officerid, playerid, amount, reason[], iscam = 0)
{
    new fine_amount = CountPlayerTickets(playerid);
    if(fine_amount < MAX_PLAYER_FINE)
    {
        STRING_GLOBAL[0] = EOS;
        if(!iscam)
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `tickets` (userid, officer, faction, amount, reason, `paid`, date) VALUES (%i, '%e', %i, %i, '%e', '0', '%s')", p_info[playerid][ID], get_name(officerid), p_info[officerid][member], amount, reason, GetFullDate());
        else
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `tickets` (userid, officer, faction, amount, reason, `paid`, date) VALUES (%i, 'Camera', 1, %i, '%e', '0', '%s')", p_info[playerid][ID], amount, reason, GetFullDate());
        mysql_tquery(con_bd, STRING_GLOBAL);
    }
    else
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid != 0 && GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_VELO_MOPED && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
        {
            RemovePlayerFromVehicle(playerid);
            SetVehicleToRespawn(vehicleid);
            SendError(playerid, "У Вас превышен лимит штрафов. Мопед был изьят.");
        }
        else
        {
            SendError(playerid, "У Вас превышен лимит штрафов. Ваши права были изьяты.");
            p_info[playerid][Lic][LIC_CAR] =
            p_info[playerid][Lic][LIC_MOTO] = 0;
            p_info[playerid][Lic_Time][LIC_CAR] =
            p_info[playerid][Lic_Time][LIC_MOTO] = 0;
            OnPlayerUpdateLicData(playerid);
            if(vehicleid != 0) RemovePlayerFromVehicle(playerid);
        }
    }


    return 1;
}

GiveVehicleTicket(officerid, vehicle, amount, reason[], iscam = 0)
{
    STRING_GLOBAL[0] = EOS;
    if(!iscam)
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `tickets` (vehicle, officer, faction, amount, reason, `paid`, date) VALUES (%i, '%e', %i, %i, '%e', '0', '%s')", veh_info[vehicle][v_mysql_id], get_name(officerid), p_info[officerid][member], amount, reason, GetFullDate());
    else
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `tickets` (vehicle, officer, faction, amount, reason, `paid`, date) VALUES (%i, 'Speed Camera', 3, %i, '%e', '0', '%s')", veh_info[vehicle][v_mysql_id], amount, reason, GetFullDate());
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

DeleteVehicleTickets(vehicle)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `tickets` WHERE `vehicle`=%i", veh_info[vehicle][v_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

DeletePlayerTickets(playerid)
{
    STRING_MIN[0] = EOS;
    mysql_format(con_bd, STRING_MIN, sizeof(STRING_MIN), "DELETE FROM `tickets` WHERE `userid`=%i", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_MIN);
    return 1;
}

CountPlayerTickets(playerid)
{
    new query[128], count;
    mysql_format(con_bd, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `userid` = %i AND `paid` = 0", p_info[playerid][ID]);
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

CountPlayerTicketsID(userid)
{
    new query[128], count;
    mysql_format(con_bd, query, sizeof query, "SELECT COUNT(id) AS total FROM `tickets` WHERE `userid` = %d AND `paid` = 0", userid);
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

CountVehicleTickets(vehicle)
{
    new query[128], count;
    mysql_format(con_bd, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `vehicle` = %i AND `paid` = 0", veh_info[vehicle][v_mysql_id]);
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

CountVehicleTicketsID(mysql_vehicle)
{
    new query[128], count;
    mysql_format(con_bd, query, sizeof(query), "SELECT COUNT(id) AS total FROM `tickets` WHERE `vehicle` = %i AND `paid` = 0", mysql_vehicle);
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

this::VehicleFineTook(playerid)
{
    SendAccess(playerid, "Вы забрали штраф из своего транспортного средства.");
    MeAction(playerid, "забрал(а) штраф из своего транспортного средства");
    return 1;
}

CMD:tickets(playerid, params[])
{
    p_temp[playerid][list_type] = 0;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `tickets` WHERE `userid`=%i AND `paid` =0 ORDER BY `id` DESC LIMIT %i", p_info[playerid][ID], MAX_TICKETS);
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayersTickets", "ii", playerid, 0);
    return 1;
}
alias:tickets("fines");

CMD:vtickets(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!vehicleid) return SendError(playerid, "Вы не в автомобиле");
    if(!IsPlayerOwnerVehicle(playerid, vehicleid))
        return SendError(playerid, "Вы не являетесь владельцем этого транспортного средства.");

    p_temp[playerid][list_type] = 0;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `paid` =0 ORDER BY `id` DESC LIMIT %i", veh_info[vehicleid][v_mysql_id], MAX_TICKETS);
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowCarsTickets", "i", playerid);
    return 1;
}
alias:vtickets("vticket");

CMD:delplayertickets(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;
    new userid;
    if(sscanf(params, "u", userid)) return SendInfo(playerid, "/delplayertickets [ID/имя игрока]");
    if(userid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");

    DeletePlayerTickets(userid);
    SendAccess(playerid, "Вы отчистили все штрафы игроку - %s.", get_name(userid));
    SendAccess(userid, "Администратор %s отчистил(а) Вам все штрафы.", get_name(playerid));
    return 1;
}

CMD:delvehtickets(playerid, params[])
{
    if(p_info[playerid][admin] < 2) return 1;
    new vehid;
    if(sscanf(params, "i", vehid)) return SendInfo(playerid, "/delvehtickets [ID транспорта]");

    DeleteVehicleTickets(vehid);
    SendAccess(playerid, "Вы отчистили все штрафы - %s [ID:%i].", GetVehicleName(vehid), vehid);
    return 1;
}


/*

forward GetFine(playerid);
public GetFine(playerid)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "У Вас нет штрафов.");
    p_temp[playerid][p_listitem_int] = 0;
    new text_fine[128], date_fine[20], amount;
    STRING_GLOBAL = "[#] Причина штрафа\tСумма\tДата\n";
    for(new i; i < rows; i++)
    {
        if(i >= 20) break;
        cache_get_value_name_int(i, "mysql_id", p_temp[playerid][p_listitem][i]);
        cache_get_value_name(i, "reason", text_fine, 128);
        cache_get_value_name_int(i, "amount", amount);
        cache_get_value_name(i, "date", date_fine, 20);
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d$\t%s\n", STRING_GLOBAL, i+1, text_fine, amount, date_fine);
        p_temp[playerid][p_listitem_int] += amount;
    }
    f(STRING_GLOBAL, "%s"I"[%d]"W" Оплатить все штрафы\t%d$\t-", STRING_GLOBAL, rows+1, p_temp[playerid][p_listitem_int]);
    p_temp[playerid][p_listitem_int] = rows;
    ShowPlayerDialog(playerid, D_FINE_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Штрафы", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
*/
