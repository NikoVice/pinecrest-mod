ShowUndergroundBots(playerid, type, idx = -1)
{
    new houseId;
    if(type < UNDERGROUND_TYPE_NPC)
    {
        houseId = p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
        if(houseId == INVALID_HOUSE_ID)
            return SendError(playerid, "Код ошибки: 1009 (Обратитесь к администрации)");
        if(h_info[houseId][h_user_id] != p_info[playerid][ID])
            return SendError(playerid, "Вы не владелец дома.");
        if(houseId+50 != GetPlayerVirtualWorld(playerid))
            return SendError(playerid, "Управлять рабочими и просматривать их можно только находясь в подвале.");
        if(h_info[houseId][h_improve][UNDERGROUND] == 0) return SendError(playerid, "В доме нет подпольного помещения, приобретите его в меню улучшений дома.");
        if(p_info[playerid][key_h_rent] != -1) return SendError(playerid, "Управлять рабочими и просматривать их может только владелец дома.");
    }

    switch(type)
    {
        case UNDERGROUND_B_TYPE_ALL: // Обзор всех рабочих;
        {
            new count;
            STRING_GLOBAL = "Название | Станок | Состояние\tОбразование\tПредметов\tВоздух | Смазка | Сытость | Материалы\tНалог | Зарплата\n";
            for(new i = 1; i <= totalundergroundbots; i++)
            {
                if(UndergroundBotsInfo[i][ubHouseIDx] != houseId) continue;
                f(STRING_GLOBAL, "%sР: %d | С: %d | %s\t%s\t%d\t%.2f%% | %.2f%% | %.2f%% | %.2f%%\t%d$ | %d$\n", STRING_GLOBAL,
                count + 1, count + 1, UndergroundBotsInfo[i][ubStatus] == 0 ? "{"#cLIGHTRED"}На паузе"W"": "{"#cGREEN"}Работает"W"", UndergroundBotsName[UndergroundBotsInfo[i][ubEducation] - 1], UndergroundBotsInfo[i][ubItems], UndergroundBotsInfo[i][ubAir], UndergroundBotsInfo[i][ubLubricant], UndergroundBotsInfo[i][ubSatiety], UndergroundBotsInfo[i][ubMaterials],
                UndergroundBotsInfo[i][ubTax], UndergroundBotsInfo[i][ubSalary]);
                count++;
            }
            if(count == 0) return SendError(playerid, "Ничего не найдено.");
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Обзор всех рабочих", STRING_GLOBAL, "ОК", "");
        }
        case UNDERGROUND_B_TYPE_ACTOR: // Рабочий;
        {
            new count[2];
            STRING_GLOBAL = "Название | Станок\tОбразование\tПредметов\tВоздух | Смазка | Сытость | Материалы\tНалог | Зарплата\n";
            for(new i = 1; i <= totalundergroundbots; i++)
            {
                if(UndergroundBotsInfo[i][ubHouseIDx] != houseId) continue;
                count[0]++;
                if(count[0] - 1 == idx)
                {
                    f(STRING_GLOBAL, "%sРабочий #%d | %d\t%s\t%d\t%.2f%% | %.2f%% | %.2f%% | %.2f%%\t%d$ | %d$\n", STRING_GLOBAL,
                    count[0], count[0], UndergroundBotsName[UndergroundBotsInfo[i][ubEducation] - 1], UndergroundBotsInfo[i][ubItems], UndergroundBotsInfo[i][ubAir], UndergroundBotsInfo[i][ubLubricant], UndergroundBotsInfo[i][ubSatiety], UndergroundBotsInfo[i][ubMaterials],
                    UndergroundBotsInfo[i][ubTax], UndergroundBotsInfo[i][ubSalary]);
                    p_temp[playerid][p_listitem][count[1]] = i;
                    count[1]++;
                    break;
                }
            }
            if(count[1] == 0) return SendError(playerid, "Ничего не найдено.");
            ShowPlayerDialog(playerid, D_UNDERGROUND_ACTOR, DIALOG_STYLE_TABLIST_HEADERS, ""I"Управление рабочим", STRING_GLOBAL, "Далее", "Отмена");
            p_temp[playerid][underground_actor] = idx;
        }
        case UNDERGROUND_B_TYPE_CONTROL: // Управление рабочим;
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "\
            "I"[1]"W" %s\n\
            "I"[2]"W" Забрать предметы (%d шт.)\n\
            "I"[3]"W" Оплатить налог (%d$)\n\
            "I"[4]"W" Оплатить зарплату (%d$)\n\
            "I"[5]"W" Договор с электростанцией (%d$ в час)\n\
            "I"[6]"W" Очистить станок балончиком со сжатым воздухом\n\
            "I"[7]"W" Смазать станок\n\
            "I"[8]"W" Покормить рабочего\n\
            "I"[9]"W" Выдать материалы для изготовления вещей\n\
            "I"[10]"W" Повысить образование рабочего\n\
            "I"[11]"W" Информация о подпольном помещении",
            UndergroundBotsInfo[idx][ubStatus] == 0 ? "Запустить рабочего" : "Остановить рабочего",
            UndergroundBotsInfo[idx][ubItems],
            UndergroundBotsInfo[idx][ubTax],
            UndergroundBotsInfo[idx][ubSalary],
            (b_info[UndergroundBotsInfo[idx][ubBizIDx]][_till] * POWER_STATION_PRICE) * UndergroundBotsInfo[idx][ubEducation]);
            ShowPlayerDialog(playerid, D_UNDERGROUND_CONTROL, DIALOG_STYLE_LIST, ""I"Управление рабочим", STRING_GLOBAL, "Далее", "Отмена");
            p_temp[playerid][underground_idx] = idx;
        }
        case UNDERGROUND_B_TYPE_ITEMS: // Забрать предметы;
        {
            if(UndergroundBotsInfo[idx][ubItems] == 0) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего нет предметов.");
            if(UndergroundBotsInfo[idx][ubTax] != 0) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего есть неоплаченный налог.");
            if(UndergroundBotsInfo[idx][ubSalary] != 0) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего есть неоплаченная заработная плата.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"У выбранного рабочего сейчас изготовлено "I"\"%s\""W" в количестве "I"%d шт."W"\n\n\
            Вы действительно хотите забрать предметы?", ItemsInfo[underground_items[UndergroundBotsInfo[idx][ubEducation] - 1]][iName], UndergroundBotsInfo[idx][ubItems]);
            ShowPlayerDialog(playerid, D_UNDERGROUND_ITEMS, DIALOG_STYLE_MSGBOX, ""I"Забрать предметы", STRING_GLOBAL, "Да", "Нет");
        }
        case UNDERGROUND_B_TYPE_TAX: // Оплатить налог;
        {
            if(UndergroundBotsInfo[idx][ubTax] == 0) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего нет неоплаченного налога.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"У выбранного рабочего сейчас налог: "I"%d$."W"\n\n\
            Вы действительно хотите оплатить налог?", UndergroundBotsInfo[idx][ubTax]);
            ShowPlayerDialog(playerid, D_UNDERGROUND_TAX, DIALOG_STYLE_MSGBOX, ""I"Оплатить налог", STRING_GLOBAL, "Да", "Нет");
        }
        case UNDERGROUND_B_TYPE_SALARY: // Оплатить зарплату;
        {
            if(UndergroundBotsInfo[idx][ubSalary] == 0) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего нет неоплаченной заработной платы.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"У выбранного рабочего сейчас зарплата: "I"%d$."W"\n\n\
            Вы действительно хотите оплатить зарплату?", UndergroundBotsInfo[idx][ubSalary]);
            ShowPlayerDialog(playerid, D_UNDERGROUND_SALARY, DIALOG_STYLE_MSGBOX, ""I"Оплатить зарплату", STRING_GLOBAL, "Да", "Нет");
        }
        case UNDERGROUND_B_TYPE_P_STATION: // Изменить электростанцию;
        {
            if(UndergroundBotsInfo[idx][ubTax] != 0) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего есть налог, оплатите его.");
            new count;
            STRING_GLOBAL[0] = EOS;
            for(new i; i < totalbizz; i++)
            {
                if(b_info[i][b_mysql_id] == INVALID_MYSQL_ID) continue;
                if(b_info[i][_tip] != B_POWER_STATION) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s (%d$ в час)\n", STRING_GLOBAL, count + 1, b_info[i][_name], b_info[i][_till] * POWER_STATION_PRICE * UndergroundBotsInfo[idx][ubEducation]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_UNDERGROUND_POWER_STATION, DIALOG_STYLE_LIST, ""I"Выбор электростанции", STRING_GLOBAL, "Далее", "Отмена");
        }
        case UNDERGROUND_B_TYPE_EDUCATION: // Повысить образование рабочего;
        {
            new temp_education = UndergroundBotsInfo[idx][ubEducation];
            if(temp_education == 3) return ShowUndergroundBots(playerid, UNDERGROUND_B_TYPE_CONTROL, idx), SendError(playerid, "У выбранного рабочего высшее образование.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            На данный момент образование рабочего "I"\"%s\"."W"\n\
            За один час работы приносит "I"\"%s\"."W"\n\n\
            Чем выше образование рабочего, тем больше предметов он изготавливает в час.\n\
            Для повышения образования требуется микросхема для станка, её можно приобрести\n\
            на центральном рынке или скрафтить в подвале дома и "I"%d$."W"\n\n\
            Шанс вероятности улучшения повышения образования:\n\
            На средне-специальное образование: 50%%\n\
            На высшее образование: 25%%\n\n\
            У Вас "I"%d"W" микросхем.\n\n\
            Вы хотите повысить образование рабочего?", UndergroundBotsName[temp_education - 1], ItemsInfo[underground_items[temp_education - 1]][iName], UNDERGROUND_BOTS_EDUCATION_PRICE * temp_education, GetInventoryAmount(playerid, 710));
            ShowPlayerDialog(playerid, D_UNDERGROUND_UPGRADE, DIALOG_STYLE_MSGBOX, ""I"Улучшение станка", STRING_GLOBAL, "Да", "Нет");
        }
        case UNDERGROUND_B_TYPE_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i; i < sizeof(UndergroundBotsInfoList); i++) strcat(STRING_GLOBAL, UndergroundBotsInfoList[i]);
            ShowPlayerDialog(playerid, D_UNDERGROUND_HELP, DIALOG_STYLE_MSGBOX, ""I"Подпольное помещение", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case UNDERGROUND_TYPE_NPC:
        {
            ShowPlayerDialog(playerid, D_UNDERGROUND_NPC, DIALOG_STYLE_LIST, ""I"Ара"W"", 
                ""I"[1]"W" Информация об складе одежды\n\
                "I"[2]"W" Информация об подпольном помещении\n\
                "I"[3]"W" Купить материалы для рабочих\n\
                "I"[4]"W" Продать ящики с одеждой\n\
                "I"[5]"W" Продать вещи из инвентаря", "Далее", "Отмена");
            return 1;
        }
        case UNDERGROUND_TYPE_NPC_BUY:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите приобрести "I"\"%s\""W" за "I"%d$?"W"\n\n\
            У Вас "I"%d шт. \"%s\".", ItemsInfo[717][iName], ItemsInfo[717][iPrice], GetInventoryAmount(playerid, 717), ItemsInfo[717][iName]);
            ShowPlayerDialog(playerid, D_UNDERGROUND_NPC_BUY, DIALOG_STYLE_MSGBOX, ""I"Купить материалы для рабочих", STRING_GLOBAL, "Да", "Нет");
            return 1;
        }
        case UNDERGROUND_TYPE_NPC_SELL:
        {
            STRING_GLOBAL = "[#] Название\tКоличество ящиков\tСтоимость\n", STRING_MIN[0] = EOS;
            new items_idx;
            for(new i = 0; i < 3; i++)
            {
                items_idx = underground_items[i];
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d шт.\t%d$\n", i + 1, ItemsInfo[items_idx][iName], GetInventoryAmount(playerid, items_idx), ItemsInfo[items_idx][iPrice]);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_UNDERGROUND_NPC_SELL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Продать ящики с одеждой", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
    }
    return 1;
}

CheckUndergroundBots()
{
    new price, salary, max_salary;
    for(new i = 1; i <= totalundergroundbots; i++)
    {
        if(UndergroundBotsInfo[i][ubMySQLIDx] == 0) continue;
        if(UndergroundBotsInfo[i][ubStatus] == 0) continue;

        price = (b_info[UndergroundBotsInfo[i][ubBizIDx]][_till] * POWER_STATION_PRICE) * UndergroundBotsInfo[i][ubEducation];

        salary = UNDERGROUND_BOTS_PRICE * UndergroundBotsInfo[i][ubEducation];

        max_salary = max_underground_bots_salary[UndergroundBotsInfo[i][ubEducation] - 1];

        if(UndergroundBotsInfo[i][ubAir] - 0.4 >= 0 && UndergroundBotsInfo[i][ubLubricant] - 0.4 >= 0 && UndergroundBotsInfo[i][ubSatiety] - 4.0 >= 0 && UndergroundBotsInfo[i][ubMaterials] - 10.0 >= 0 && UndergroundBotsInfo[i][ubItems] < MAX_UNDERGROUND_BOTS_ITEMS && UndergroundBotsInfo[i][ubTax] < MAX_UNDERGROUND_BOTS_TAX && UndergroundBotsInfo[i][ubSalary] < max_salary && price > 0 && salary > 0)
        {
            UndergroundBotsInfo[i][ubAir] -= 0.4;
            UndergroundBotsInfo[i][ubLubricant] -= 0.4;
            UndergroundBotsInfo[i][ubSatiety] -= 4.0;
            UndergroundBotsInfo[i][ubMaterials] -= 10.0;
            UndergroundBotsInfo[i][ubItems]++;
            UndergroundBotsInfo[i][ubTax] += price;
            UndergroundBotsInfo[i][ubSalary] += salary;

            if(UndergroundBotsInfo[i][ubItems] > MAX_UNDERGROUND_BOTS_ITEMS)
            {
                UndergroundBotsInfo[i][ubStatus] = 0;
                UndergroundBotsInfo[i][ubItems] = MAX_UNDERGROUND_BOTS_ITEMS;
            }
            if(UndergroundBotsInfo[i][ubTax] > MAX_UNDERGROUND_BOTS_TAX)
            {
                UndergroundBotsInfo[i][ubStatus] = 0;
                UndergroundBotsInfo[i][ubTax] = MAX_UNDERGROUND_BOTS_TAX;
            }
            if(UndergroundBotsInfo[i][ubSalary] > max_salary)
            {
                UndergroundBotsInfo[i][ubStatus] = 0;
                UndergroundBotsInfo[i][ubSalary] = max_salary;
            }

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `underground` SET `air` = '%f', `lubricant` = '%f', `satiety` = '%f', `materials` = '%f', `tax` = %d, `salary` = %d, `items` = %d, `status` = %d WHERE `id` = %d",
            UndergroundBotsInfo[i][ubAir], UndergroundBotsInfo[i][ubLubricant], UndergroundBotsInfo[i][ubSatiety], UndergroundBotsInfo[i][ubMaterials], UndergroundBotsInfo[i][ubTax], UndergroundBotsInfo[i][ubSalary], UndergroundBotsInfo[i][ubItems], UndergroundBotsInfo[i][ubStatus], UndergroundBotsInfo[i][ubMySQLIDx]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        else
        {
            UndergroundBotsInfo[i][ubStatus] = 0;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `underground` SET `status` = 0 WHERE `id` = %d",
            UndergroundBotsInfo[i][ubMySQLIDx]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

GetHouseUndergroundBots(houseid)
{
    new count = 0;
    for(new idx = 1; idx <= totalundergroundbots; idx++)
    {
        if(UndergroundBotsInfo[idx][ubHouseIDx] == houseid) count++;
    }
    return count;
}

GetMaxHouseUndergroundBots(houseid)
{
    new squar = h_info[houseid][h_squar], idx = 1;
    switch(squar)
    {
        case 1: return 4;
        case 2: return 6;
        case 3: return 8;
        case 4: return 10;
    }
    return idx;
}

forward load_undergroundbots();
public load_undergroundbots()
{
    new time = GetTickCount(), str[1024], biz_idx[] = {100, 101, 102};
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iiiffffiiiii",
            UndergroundBotsInfo[idx][ubMySQLIDx],
            UndergroundBotsInfo[idx][ubStatus],
            UndergroundBotsInfo[idx][ubEducation],
            UndergroundBotsInfo[idx][ubAir],
            UndergroundBotsInfo[idx][ubLubricant],
            UndergroundBotsInfo[idx][ubSatiety],
            UndergroundBotsInfo[idx][ubMaterials],
            UndergroundBotsInfo[idx][ubTax],
            UndergroundBotsInfo[idx][ubSalary],
            UndergroundBotsInfo[idx][ubItems],
            UndergroundBotsInfo[idx][ubHouseIDx],
            UndergroundBotsInfo[idx][ubBizIDx]);
            UndergroundBotsInfo[idx][ubActor] = -1;
            if((b_info[UndergroundBotsInfo[totalundergroundbots][ubBizIDx]][_till] * UNDERGROUND_BOTS_PRICE) * UndergroundBotsInfo[idx][ubEducation] <= 0)
            {
                UndergroundBotsInfo[totalundergroundbots][ubBizIDx] = biz_idx[random(2)];
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `underground` SET `biz` = %d WHERE `id` = %d",
                UndergroundBotsInfo[totalundergroundbots][ubBizIDx], UndergroundBotsInfo[totalundergroundbots][ubMySQLIDx]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
            totalundergroundbots++;
        }
    }
    CreateActor(220, 1154.7012,-1440.1923,15.7969,87.7707);
    CreateDynamic3DTextLabel("NPC: "I"Владелец рынка вещей Ара", COLOR_WHITE, 1154.7012,-1440.1923,15.7969 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    underground_area = CreateDynamicSphere(1154.0009,-1440.2372,15.7969, 2.5, -1, -1, -1);
    UpdateAreaInfo(underground_area, TYPE_UNDERGROUND, AREA_SUBTYPE_INVALID_ID);
    CreatePickup(1239, 23, 1154.0009,-1440.2372,15.7969);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1154.0009,-1440.2372,15.7969, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    printf("Рабочие в домах загружено: %d за %d мс", totalundergroundbots, GetTickCount() - time);
}

forward create_undergroundbots(idx);
public create_undergroundbots(idx)
{
    UndergroundBotsInfo[idx][ubMySQLIDx] = cache_insert_id();
    return 1;
}

DestroyUndergroundBots(idx)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `underground` WHERE `id` = %d",
    UndergroundBotsInfo[idx][ubMySQLIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    UndergroundBotsInfo[idx][ubMySQLIDx] = 0;
    UndergroundBotsInfo[idx][ubStatus] = 0;
    UndergroundBotsInfo[idx][ubEducation] = 1;
    UndergroundBotsInfo[idx][ubAir] = 0.0;
    UndergroundBotsInfo[idx][ubLubricant] = 0.0;
    UndergroundBotsInfo[idx][ubSatiety] = 0.0;
    UndergroundBotsInfo[idx][ubMaterials] = 0.0;
    UndergroundBotsInfo[idx][ubTax] = 0;
    UndergroundBotsInfo[idx][ubSalary] = 0;
    UndergroundBotsInfo[idx][ubItems] = 0;
    UndergroundBotsInfo[idx][ubHouseIDx] = 0;
    UndergroundBotsInfo[idx][ubBizIDx] = 0;
    return 1;
}

LoadUndergroundBots(playerid, houseid)
{
    new count;
    for(new i = MAX_HOUSE_UNDERGROUND_USE-1; i != -1; i--)
    {
        if(h_info[houseid][h_underground_player_use][i] != INVALID_PLAYER_ID) count++;
    }
    if(count == 0)
    {
        new count, actorid, virt_world = houseid+50;
        for(new i = 1; i <= totalundergroundbots; i++)
        {
            if(UndergroundBotsInfo[i][ubHouseIDx] != houseid) continue;
            if(UndergroundBotsInfo[i][ubActor] != -1) continue;
            actorid = CreateActor(144, UndergroundBotsPos[count][0], UndergroundBotsPos[count][1], UndergroundBotsPos[count][2], UndergroundBotsPos[count][3]);
            UndergroundBotsInfo[i][ubActor] = actorid;
            ApplyActorAnimation(actorid, "POLICE", "CopTraf_Come", 4.1,1,0,0,0,0);
            ApplyActorAnimation(actorid, "POLICE", "CopTraf_Come", 4.1,1,0,0,0,0);
            SetActorVirtualWorld(actorid, virt_world);
            count++;
        }
    }

    for(new i = MAX_HOUSE_UNDERGROUND_USE-1; i != -1; i--)
    {
        if(h_info[houseid][h_underground_player_use][i] == INVALID_PLAYER_ID)
        {
            h_info[houseid][h_underground_player_use][i] = playerid;
            p_temp[playerid][underground_use] = houseid;
            break;
        }
    }
    if(p_temp[playerid][underground_use] == houseid) return 1;
    return 0;
}

UnloadUndergroundBots(playerid)
{
    new houseid = p_temp[playerid][underground_use];
    if(houseid == -1) return 1;

    for(new i = MAX_HOUSE_UNDERGROUND_USE-1; i != -1; i--)
    {
        if(h_info[houseid][h_underground_player_use][i] == playerid)
        {
            h_info[houseid][h_underground_player_use][i] = INVALID_PLAYER_ID;
            p_temp[playerid][underground_use] = -1;
            break;
        }
    }

    new count;
    for(new i = MAX_HOUSE_UNDERGROUND_USE-1; i != -1; i--)
    {
        if(h_info[houseid][h_underground_player_use][i] != INVALID_PLAYER_ID) count++;
    }
    if(count == 0)
    {
        new actorid;
        for(new i = 1; i <= totalundergroundbots; i++)
        {
            if(UndergroundBotsInfo[i][ubHouseIDx] != houseid) continue;
            actorid = UndergroundBotsInfo[i][ubActor];
            if(actorid == -1) continue;
            DestroyActor(actorid);
            UndergroundBotsInfo[i][ubActor] = -1;
        }
    }
    return 1;
}

CMD:test_underground(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckUndergroundBots();
    return 1;
}
