#define MAX_PANEL                   5000 // Максимальное количество панелей;

#define MONEY_PANEL_OWNER_OFFLINE   2000 // В день: 48.000$;
#define MONEY_PANEL_OWNER_ONLINE    4000 // В день: 96.000$;

#define TAX_PANEL_OWNER_OFFLINE     1000 // В день: 24.000$;
#define TAX_PANEL_OWNER_ONLINE      500 // В день: 12.000$;

/*

    Информация о прибыли:
        [Игрок не в игре]: Грязная прибыль: 2000$ * 24 * 15 = 720.000$. Чистая прибыль: 720.000$ - 100.000$ - (1000 * 24 * 15) = 260.000$;
        [Игрок в игре]: Грязная прибыль: 4000$ * 24 * 15 = 1.440.000$. Чистая прибыль: 1.440.000$ - 100.000$ - (500 * 24 * 15) = 1.160.000$;

*/

new totalpanel;
new panel_warehouse = 100;

enum E_PANEL_HOUSE_INFO
{
    PanelHouseMySQLIDx, // MySQL ID;
    PanelHouseObject, // ID объекта;
    PanelHouseArea, // Зона;
    PanelHouseDay, // Кол-во дней;
    PanelHouseBreaking, // Поломка;
    PanelHouseBreakingPayDay, // Количество часов при поломке;
    PanelHouseRepair, // Заказ на ремонт;
    PanelHouseRepairPlayerID, // ID игрока, выполняющего заказ;
    PanelHouseWear, // Износ;
    PanelHouseMoney, // Деньги;
    PanelHouseTax, // Налог;
    PanelHouseIDx, // ID дома;
    Float:PanelHousePos[6], // Кординаты;
    Text3D:PanelHouseText // 3D текст;
};
new PanelHouseInfo[MAX_PANEL][E_PANEL_HOUSE_INFO];

enum
{
    PANEL_TYPE_CREATE,
    PANEL_TYPE_DESTROY,
    PANEL_TYPE_CONTROL,
    PANEL_TYPE_HELP,
    PANEL_TYPE_LIST
}

ShowHousePanel(playerid, type)
{
    new h = GetPlayerHouseID(playerid);
    if(type != PANEL_TYPE_LIST)
    {
        if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
        if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");
    }

    switch(type)
    {
        case PANEL_TYPE_CREATE:
        {
            if(GetHousePanelObject(h) >= GetHouseMaxPanelObject(h)) return SendError(playerid, "На территории дома нет свободного места под панель.");
            new h = GetPlayerHouseID(playerid);
            if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
            if(h_info[h][h_panel_items] == 0) return SendError(playerid, "На складе нет панели.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");
            if(GetHousePanelObject(h) >= GetHouseMaxPanelObject(h)) return SendError(playerid, "На территории дома нет свободного места под панель.");

            totalpanel++;
            SendMes(playerid, COLOR_SEA_WAVE, "С помощью кнопки ALT установите панель в желаемом месте.");
            PanelHouseInfo[totalpanel][PanelHouseObject] = CreateObject(1697, 0, 0, 0, 0, 0, 0);
            AttachObjectToPlayer(PanelHouseInfo[totalpanel][PanelHouseObject], playerid, 0, 1, 0.25, 0, 0, 180.0);
            SetPVarInt(playerid, "LoadPanel", totalpanel + 1);
        }
        case PANEL_TYPE_DESTROY, PANEL_TYPE_CONTROL:
        {
            new count = 0;
            STRING_GLOBAL = "[#] Осталось дней\tСостояние\tИзнос\tЗаработано | Налог\n", STRING_MIN[0] = EOS;
            for(new idx = 1; idx <= totalpanel; idx++)
            {
                if(PanelHouseInfo[idx][PanelHouseIDx] != h) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %d\t%s\t%d%%\t%d$ | %d$\n", count + 1, PanelHouseInfo[idx][PanelHouseDay], PanelHouseInfo[idx][PanelHouseBreaking] == 0 ? "{"#cGREEN"}Исправна"W"" : "{"#cLIGHTRED"}Требуется ремонт"W"", PanelHouseInfo[idx][PanelHouseWear], PanelHouseInfo[idx][PanelHouseMoney], PanelHouseInfo[idx][PanelHouseTax]);
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = idx;
                count++;
            }
            if(count == 0) return SendError(playerid, "На территории дома не найдено ни одной панели.");
            if(type == PANEL_TYPE_DESTROY) ShowPlayerDialog(playerid, D_PANEL_DESTROY, DIALOG_STYLE_TABLIST_HEADERS, ""I"Удалить панель", STRING_GLOBAL, "Далее", "Отмена");
            else ShowPlayerDialog(playerid, D_PANEL_CONTROL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Управление панелью", STRING_GLOBAL, "Далее", "Отмена");
        }
        case PANEL_TYPE_HELP:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация о панелях", ""W"\
            Солнечные панели - отличный вид пассивного заработка для владельцев домов. Сейчас ты узнаешь подробнее\n\
            о том, как они работают.\n\n\
            Для начала нужно приобрести панели в специализированном магазине. Их количество ограничено классом дома:\n\
            Nope-класс - 1, C-класс - 2, B-класс - 3 и A-класс - 4. После установки оборудование будет работать и приносить\n\
            доход.\n\n\
            Но не всё так просто, ведь срок годности панели - 15 дней, и в истечении этого срока возможны поломки. Чтобы\n\
            избежать полного удаления панели, необходимо устранить проблему в течение 24 часов. Именно для этого существуют\n\
            ремонтники солнечных панелей, которые должны починить преобразователи энергии в устройстве.\n\n\
            Каждый час за работу солнечных панелей поступают денежные средства и взимается налог. Если владелец дома находится\n\
            в игре более 20 минут за час, он получит удвоенную оплату, а налоговый вычет также снизится в 2 раза. К слову, уровень\n\
            заработка зависит от класса твоего дома:\n\
            Nope-класс - до 1.250.000$, C-класс - до 2.500.000$, B-класс - до 3.750.000$ и A-класс до 5.000.000$.", "Закрыть", "");
        }
        case PANEL_TYPE_LIST:
        {
            new count = 0, idx_city;
            STRING_GLOBAL = "[#] Местоположение\tСтатус\tРасстояние\n", STRING_MIN[0] = EOS;
            for(new idx = 1; idx <= totalpanel; idx++)
            {
                if(PanelHouseInfo[idx][PanelHouseBreaking] == 0) continue;
                if(PanelHouseInfo[idx][PanelHouseRepair] == 0) continue;
                idx_city = GetCityName(PanelHouseInfo[idx][PanelHousePos][0], PanelHouseInfo[idx][PanelHousePos][1]);
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%.1f\n", count + 1, gSAZonesCity[idx_city], PanelHouseInfo[idx][PanelHouseRepairPlayerID] == INVALID_PLAYER_ID ? "{"#cYELLOW"}Готов к выполнению"W"" : "{"#cLIGHTRED"}Выполняется"W"", GetPlayerDistanceFromPoint(playerid, PanelHouseInfo[idx][PanelHousePos][0], PanelHouseInfo[idx][PanelHousePos][1], PanelHouseInfo[idx][PanelHousePos][2]));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = idx;
                count++;
                if(count == 40) break;
            }
            if(!count) return SendError(playerid, "На данный момент нет заказов на ремонт солнечных панелей.");
            ShowPlayerDialog(playerid, D_PANEL_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список заказов", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

GetHousePanelObject(houseid)
{
    new count = 0;
    for(new idx = 1; idx <= totalpanel; idx++)
    {
        if(PanelHouseInfo[idx][PanelHouseIDx] == houseid) count++;
    }
    return count;
}

GetHouseMaxPanelObject(houseid)
{
    new squar = h_info[houseid][h_squar], idx = 1;
    switch(squar)
    {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        case 4: return 4;
    }
    return idx;
}

forward load_panel();
public load_panel()
{
    new time = GetTickCount(), str[512];
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iiiiiiiiiffffff",
            PanelHouseInfo[idx][PanelHouseMySQLIDx],
            PanelHouseInfo[idx][PanelHouseDay],
            PanelHouseInfo[idx][PanelHouseBreaking],
            PanelHouseInfo[idx][PanelHouseBreakingPayDay],
            PanelHouseInfo[idx][PanelHouseRepair],
            PanelHouseInfo[idx][PanelHouseWear],
            PanelHouseInfo[idx][PanelHouseMoney],
            PanelHouseInfo[idx][PanelHouseTax],
            PanelHouseInfo[idx][PanelHouseIDx],
            PanelHouseInfo[idx][PanelHousePos][0],
            PanelHouseInfo[idx][PanelHousePos][1],
            PanelHouseInfo[idx][PanelHousePos][2],
            PanelHouseInfo[idx][PanelHousePos][3],
            PanelHouseInfo[idx][PanelHousePos][4],
            PanelHouseInfo[idx][PanelHousePos][5]);

            PanelHouseInfo[idx][PanelHouseRepairPlayerID] = INVALID_PLAYER_ID;

            PanelHouseInfo[idx][PanelHouseObject] = CreateDynamicObject(1697, PanelHouseInfo[idx][PanelHousePos][0], PanelHouseInfo[idx][PanelHousePos][1], PanelHouseInfo[idx][PanelHousePos][2], PanelHouseInfo[idx][PanelHousePos][3], PanelHouseInfo[idx][PanelHousePos][4], PanelHouseInfo[idx][PanelHousePos][5], -1, -1, -1, 120.00, 120.00);
            PanelHouseInfo[idx][PanelHouseArea] = CreateDynamicSphere(PanelHouseInfo[idx][PanelHousePos][0], PanelHouseInfo[idx][PanelHousePos][1], PanelHouseInfo[idx][PanelHousePos][2], 7.5, -1, -1, -1);
            UpdateAreaInfo(PanelHouseInfo[idx][PanelHouseArea], TYPE_PANEL, AREA_SUBTYPE_PANEL, idx);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Солнечная панель\n\nДом: "W"%d"I"\nОсталось дней: "W"%d"I"\nСостояние: "W"%s"I"\nИзнос: "W"%d%%", PanelHouseInfo[idx][PanelHouseIDx], PanelHouseInfo[idx][PanelHouseDay], PanelHouseInfo[idx][PanelHouseBreaking] == 0 ? "{"#cGREEN"}Исправна"W"" : "{"#cLIGHTRED"}Требуется ремонт"W"", PanelHouseInfo[idx][PanelHouseWear]);
            PanelHouseInfo[idx][PanelHouseText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, PanelHouseInfo[idx][PanelHousePos][0], PanelHouseInfo[idx][PanelHousePos][1], PanelHouseInfo[idx][PanelHousePos][2]+1, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
            totalpanel++;
        }
    }
    printf("Панелей в домах загружено: %d за %d мс", totalpanel, GetTickCount() - time);
}

forward create_panel(idx);
public create_panel(idx)
{
    PanelHouseInfo[idx][PanelHouseMySQLIDx] = cache_insert_id();
    return 1;
}

CreatePanel(playerid)
{
    new h = GetPlayerHouseID(playerid);
    if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
    if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");

    new i = GetPVarInt(playerid, "LoadPanel")-1;

    if(h_info[h][h_panel_items] == 0) return SendError(playerid, "На складе нет панели.");

    DestroyObject(PanelHouseInfo[i][PanelHouseObject]);
    DeletePVar(playerid, "LoadPanel");

    new Float:PlPos[4];
    GetPlayerPos(playerid, PlPos[0], PlPos[1], PlPos[2]);
    GetPlayerFacingAngle(playerid, PlPos[3]);

    PanelHouseInfo[i][PanelHouseDay] = 15;
    PanelHouseInfo[i][PanelHouseBreaking] = 0;
    PanelHouseInfo[i][PanelHouseRepair] = 0;
    PanelHouseInfo[i][PanelHouseRepairPlayerID] = INVALID_PLAYER_ID;
    PanelHouseInfo[i][PanelHouseWear] = 0;
    PanelHouseInfo[i][PanelHouseMoney] = 0;
    PanelHouseInfo[i][PanelHouseTax] = 0;
    PanelHouseInfo[i][PanelHouseIDx] = h;
    PanelHouseInfo[i][PanelHousePos][0] = PlPos[0]+floatcos(PlPos[3]+90, degrees);
    PanelHouseInfo[i][PanelHousePos][1] = PlPos[1]+floatsin(PlPos[3]+90, degrees);
    PanelHouseInfo[i][PanelHousePos][2] = PlPos[2] + 0.25;
    PanelHouseInfo[i][PanelHousePos][3] = 0.0;
    PanelHouseInfo[i][PanelHousePos][4] = 0.0;
    PanelHouseInfo[i][PanelHousePos][5] = PlPos[3] + 180.0;

    PanelHouseInfo[i][PanelHouseObject] = CreateDynamicObject(1697, PanelHouseInfo[i][PanelHousePos][0], PanelHouseInfo[i][PanelHousePos][1], PanelHouseInfo[i][PanelHousePos][2], PanelHouseInfo[i][PanelHousePos][3], PanelHouseInfo[i][PanelHousePos][4], PanelHouseInfo[i][PanelHousePos][5], -1, -1, -1, 120.00, 120.00);
    PanelHouseInfo[i][PanelHouseArea] = CreateDynamicSphere(PanelHouseInfo[i][PanelHousePos][0], PanelHouseInfo[i][PanelHousePos][1], PanelHouseInfo[i][PanelHousePos][2], 7.5, -1, -1, -1);
    UpdateAreaInfo(PanelHouseInfo[i][PanelHouseArea], TYPE_PANEL, AREA_SUBTYPE_PANEL, i);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Солнечная панель\n\nДом: "W"%d"I"\nОсталось дней: "W"%d"I"\nСостояние: "W"%s"I"\nИзнос: "W"%d%%", PanelHouseInfo[i][PanelHouseIDx], PanelHouseInfo[i][PanelHouseDay], PanelHouseInfo[i][PanelHouseBreaking] == 0 ? "{"#cGREEN"}Исправна"W"" : "{"#cLIGHTRED"}Требуется ремонт"W"", PanelHouseInfo[i][PanelHouseWear]);
    PanelHouseInfo[i][PanelHouseText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, PanelHouseInfo[i][PanelHousePos][0], PanelHouseInfo[i][PanelHousePos][1], PanelHouseInfo[i][PanelHousePos][2]+1, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `panel` (`day`, `house`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES (%d, %d, '%f', '%f', '%f', '%f', '%f', '%f')",
    PanelHouseInfo[i][PanelHouseDay], PanelHouseInfo[i][PanelHouseIDx], PanelHouseInfo[i][PanelHousePos][0], PanelHouseInfo[i][PanelHousePos][1], PanelHouseInfo[i][PanelHousePos][2], PanelHouseInfo[i][PanelHousePos][3], PanelHouseInfo[i][PanelHousePos][4], PanelHouseInfo[i][PanelHousePos][5]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_panel", "i", i);

    h_info[h][h_panel_items]--;
    save_house(h);

    SendAccess(playerid, "Вы установили панель.");
    return 1;
}

DestroyPanel(idx)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `panel` WHERE `id` = %d",
    PanelHouseInfo[idx][PanelHouseMySQLIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    PanelHouseInfo[idx][PanelHouseMySQLIDx] = 0;
    PanelHouseInfo[idx][PanelHouseDay] = 0;
    PanelHouseInfo[idx][PanelHouseBreaking] = 0;
    PanelHouseInfo[idx][PanelHouseWear] = 0;
    PanelHouseInfo[idx][PanelHouseIDx] = 0;
    PanelHouseInfo[idx][PanelHousePos][0] = 0.0;
    PanelHouseInfo[idx][PanelHousePos][1] = 0.0;
    PanelHouseInfo[idx][PanelHousePos][2] = 0.0;
    PanelHouseInfo[idx][PanelHousePos][3] = 0.0;
    PanelHouseInfo[idx][PanelHousePos][4] = 0.0;
    PanelHouseInfo[idx][PanelHousePos][5] = 0.0;
    if(PanelHouseInfo[idx][PanelHouseObject] != INVALID_OBJECT_ID)
    {
        DestroyDynamicObject(PanelHouseInfo[idx][PanelHouseObject]);
        PanelHouseInfo[idx][PanelHouseObject] = INVALID_OBJECT_ID;
    }
    if(PanelHouseInfo[idx][PanelHouseText] != INVALID_3DTEXT_ID)
    {
        DestroyDynamic3DTextLabel(PanelHouseInfo[idx][PanelHouseText]);
        PanelHouseInfo[idx][PanelHouseText] = INVALID_3DTEXT_ID;
    }
    return 1;
}

CheckPanel()
{
    new houseid, userid, scdplayerid;
    for(new i = 1; i <= totalpanel; i++)
    {
        if(PanelHouseInfo[i][PanelHouseMySQLIDx] == 0) continue;

        houseid = PanelHouseInfo[i][PanelHouseIDx];
        userid = h_info[houseid][h_user_id];

        if(PanelHouseInfo[i][PanelHouseBreaking] == 0)
        {
            if(random(100) == 50)
            {
                PanelHouseInfo[i][PanelHouseBreaking] = 1;
                PanelHouseInfo[i][PanelHouseBreakingPayDay] = 0;
                PanelHouseInfo[i][PanelHouseWear] += 2;

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `panel` SET `breaking` = 1, `breakingpayday` = 0, `wear` = %d WHERE `id` = %d",
                PanelHouseInfo[i][PanelHouseWear], PanelHouseInfo[i][PanelHouseMySQLIDx]);
                mysql_tquery(con_bd, STRING_GLOBAL);

                if(PanelHouseInfo[i][PanelHouseWear] >= 100)
                {
                    if(userid != INVALID_MYSQL_ID)
                    {
                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Солнечная панель #%d у дома #%d была утилизирована\nпо причине износа.", PanelHouseInfo[i][PanelHouseMySQLIDx], PanelHouseInfo[i][PanelHouseIDx]);
                        AddNotify(userid, STRING_GLOBAL);
                    }
                    DestroyPanel(i);
                } 
                else UpdatePanel(i);
            }
            else
            {
                if(userid != INVALID_MYSQL_ID)
                {
                    scdplayerid = GetPlayerUserID(userid);
                    if(scdplayerid != INVALID_PLAYER_ID && p_info[scdplayerid][p_time_payday] >= 1200)
                    {
                        PanelHouseInfo[i][PanelHouseMoney] += MONEY_PANEL_OWNER_ONLINE;
                        PanelHouseInfo[i][PanelHouseTax] += TAX_PANEL_OWNER_ONLINE;
                    }
                    else
                    {
                        PanelHouseInfo[i][PanelHouseMoney] += MONEY_PANEL_OWNER_OFFLINE;
                        PanelHouseInfo[i][PanelHouseTax] += TAX_PANEL_OWNER_OFFLINE;
                    }

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `panel` SET `money` = %d, `tax` = %d WHERE `id` = %d",
                    PanelHouseInfo[i][PanelHouseMoney], PanelHouseInfo[i][PanelHouseTax], PanelHouseInfo[i][PanelHouseMySQLIDx]);
                    mysql_tquery(con_bd, STRING_GLOBAL);
                }
            }
        }
        else
        {
            PanelHouseInfo[i][PanelHouseBreakingPayDay]++;
            MysqlUpdatePanelInt(PanelHouseInfo[i][PanelHouseMySQLIDx], "breakingpayday", PanelHouseInfo[i][PanelHouseBreakingPayDay]);
            if(PanelHouseInfo[i][PanelHouseBreakingPayDay] == 24)
            {
                if(userid != INVALID_MYSQL_ID)
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Солнечная панель #%d у дома #%d была утилизирована\nпо причине неисправности на протяжении 24-х часов.", PanelHouseInfo[i][PanelHouseMySQLIDx], PanelHouseInfo[i][PanelHouseIDx]);
                    AddNotify(userid, STRING_GLOBAL);
                }
                DestroyPanel(i);
            }
        }
    }
    return 1;
}

CMD:panel(playerid, params[])
{
    HousePlayerList(playerid, HOUSE_ID_PANEL);
    return 1;
}

CMD:dpanel(playerid, params[0])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /dpanel [id дома]");

    new
        houseId = strval(params);

    if(!(0 <= houseId < totalhouses))
        return SendError(playerid, "Неверный ID дома.");
    if(h_info[houseId][h_mysql_id] == INVALID_MYSQL_ID)
        return SendError(playerid, "Дом не задействован.");
    new count = 0;
    for(new i = 1; i <= totalpanel; i++)
    {
        if(PanelHouseInfo[i][PanelHouseIDx] != houseId) continue;
        DestroyPanel(i);
        count++;
    }

    if(count == 0) return SendError(playerid, "На территории данного дома нет панелей.");

    if(h_info[houseId][h_user_id] != INVALID_MYSQL_ID)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, ""I"%s"W" удалил(-а) все панели на территории Вашего дома.", get_name(playerid));
        AddNotify(h_info[houseId][h_user_id], STRING_GLOBAL);
    }

    SendAccess(playerid, "Вы удалили все панели на территории дома %d.", houseId);

    Log(LOG_player, INFO, "%s[%d](%s %s) удалил панели дома (%d) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", houseId);
    return 1;
}

new pickup_panel;

LoadPanel()
{
    CreateActor(26, 1021.8068,-1433.9285,13.5469,190.5049);
    CreateDynamic3DTextLabel("NPC: "I"Ремонтник панелей", COLOR_WHITE, 1021.8068,-1433.9285,13.5469 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_panel = CreatePickup(1275, 23, 1021.7979,-1434.6167,13.5469);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 1021.7979,-1434.6167,13.5469, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    new areaid = CreateDynamicSphere(956.7352,-1449.2498,13.5149, 10.0, -1, -1, -1);
    UpdateAreaInfo(areaid, TYPE_PANEL, AREA_SUBTYPE_PANEL_LIST);
    CreateDynamicPickup(19134, 23, 956.7352,-1449.2498,13.5149);
    CreateDynamic3DTextLabel("<< Список заказов >>", COLOR_MAIN, 956.7352,-1449.2498,13.5149, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    CreateDynamicObject(3175, 1022.75018, -1432.38013, 12.44070,   0.00000, 0.00000, 90.00000);

    CreateVehicleVEx(NPO_JOB, JOB_PANEL, 578, 982.2202, -1436.8103, 14.0611, 180.0000, 1, 1, 300);
    CreateVehicleVEx(NPO_JOB, JOB_PANEL, 578, 996.3402, -1436.8103, 14.0611, 180.0000, 1, 1, 300);
    CreateVehicleVEx(NPO_JOB, JOB_PANEL, 578, 1026.1383, -1451.5428, 14.0611, 90.0000, 1, 1, 300);
    CreateVehicleVEx(NPO_JOB, JOB_PANEL, 578, 1005.4484, -1458.0017, 14.0611, 0.0000, 1, 1, 300);
    CreateVehicleVEx(NPO_JOB, JOB_PANEL, 578, 998.3084, -1458.0017, 14.0611, 0.0000, 1, 1, 300);
    return 1;
}

UpdatePanel(idx)
{
    if(PanelHouseInfo[idx][PanelHouseText] == INVALID_3DTEXT_ID) return 1;
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Солнечная панель\n\nДом: "W"%d"I"\nОсталось дней: "W"%d"I"\nСостояние: "W"%s"I"\nИзнос: "W"%d%%", PanelHouseInfo[idx][PanelHouseIDx], PanelHouseInfo[idx][PanelHouseDay], PanelHouseInfo[idx][PanelHouseBreaking] == 0 ? "{"#cGREEN"}Исправна"W"" : "{"#cLIGHTRED"}Требуется ремонт"W"", PanelHouseInfo[idx][PanelHouseWear]);
    UpdateDynamic3DTextLabelText(PanelHouseInfo[idx][PanelHouseText], COLOR_MAIN, STRING_GLOBAL);
    return 1;
}

MysqlUpdatePanelInt(idx, const field[], const data)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `panel` SET `%s` = %d WHERE `id` = %d",
    field, data, idx);
    mysql_tquery(con_bd, STRING_GLOBAL, "", "");
    return 1;
}

CMD:test_2(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckPanel();
    return 1;
}