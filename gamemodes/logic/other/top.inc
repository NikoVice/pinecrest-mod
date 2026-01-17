new pickup_top;

LoadTop()
{
    // Организатор списка;
    new actorid;
    actorid = CreateActor(187, 1552.6757,1134.9731,1038.6191,270.0000);
    SetActorVirtualWorld(actorid, 1);

    CreateDynamic3DTextLabel("NPC: "I"Организатор списка", COLOR_WHITE, 1552.6757,1134.9731,1038.6191 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_top = CreatePickup(1239, 23, 1553.3656,1135.1091,1038.6191, 1);
    CreateDynamic3DTextLabel("<< Обычный ТОП и Фракционный ТОП >>", COLOR_MAIN, 1553.3656,1135.1091,1038.6191, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

ShowPlayerTopListInfo(playerid, type)
{
    STRING_GLOBAL[0] = EOS;
    switch(type)
    {
        case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `p_game_time` != 0 ORDER BY `p_game_time` DESC LIMIT 25");
        case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `level` != 0 ORDER BY `level` DESC LIMIT 25");
        case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `money` + `bank` + `bank_deposit` != 0 ORDER BY `money` + `bank` + `bank_deposit` DESC LIMIT 25");
        case 3: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `donate_all_new` != 0 ORDER BY `donate_all_new` DESC LIMIT 25");
        case 4: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `bitcoin` != 0 ORDER BY `bitcoin` DESC LIMIT 25");
    }
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayerDialogTop", "ddd", playerid, -1, type);
    return 1;
}

ShowFractionTopTypeList(playerid, fraction)
{
    switch(fraction)
    {
        case 0:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Правительство", "\
            "I"[1]"W" Освобождение из тюрьмы\n\
            "I"[2]"W" Выдача паспортов\n\
            "I"[3]"W" Продажа лицензий на адвокатские услуги", "Далее", "Отмена");
        }
        case 1:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Полиция и ФБР", "\
            "I"[1]"W" Проведение аррестов\n\
            "I"[2]"W" Освобождение из тюрьмы\n\
            "I"[3]"W" Выдача розыска\n\
            "I"[4]"W" Снятие розыска\n\
            "I"[5]"W" Выписывание штрафов\n\
            "I"[6]"W" Проведение обысков\n\
            "I"[7]"W" Изъятие вещей\n\
            "I"[8]"W" Продажа лицензий на оружие\n\
            "I"[9]"W" Убийств членов нелегальных организаций", "Далее", "Отмена");
        }
        case 2:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Армия", "\
            "I"[1]"W" Загруженно патронов и материалов\n\
            "I"[2]"W" Разгруженно патронов и материалов\n\
            "I"[3]"W" Убийств членов нелегальных организаций", "Далее", "Отмена");
        }
        case 3:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Больница", "\
            "I"[1]"W" Лечение больных\n\
            "I"[2]"W" Лечение наркозависимых\n\
            "I"[3]"W" Проведение операций по смене пола\n\
            "I"[4]"W" Выдача мед. карт\n\
            "I"[5]"W" Загруженно медикаментов\n\
            "I"[6]"W" Разгруженно медикаментов", "Далее", "Отмена");
        }
        case 4:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Радиоцентр", "\
            "I"[1]"W" Отредактированно объявлений", "Далее", "Отмена");
        }
        case 5:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Банды", "\
            "I"[1]"W" Ограблений магазина\n\
            "I"[2]"W" Загруженно наркотиков\n\
            "I"[3]"W" Разгруженно наркотиков\n\
            "I"[4]"W" Загруженно патронов и материалов\n\
            "I"[5]"W" Разгруженно патронов и материалов\n\
            "I"[6]"W" Убийств на захватах территорий\n\
            "I"[7]"W" Смертей на захватах территорий\n\
            "I"[8]"W" Недельный топ {"#cRED"}[NEW]", "Далее", "Отмена");
        }
        case 6:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Мафии", "\
            "I"[1]"W" Ограблений банка\n\
            "I"[2]"W" Загруженно наркотиков\n\
            "I"[3]"W" Разгруженно наркотиков\n\
            "I"[4]"W" Загруженно патронов и материалов\n\
            "I"[5]"W" Разгруженно патронов и материалов\n\
            "I"[6]"W" Убийств на войне за бизнес\n\
            "I"[7]"W" Смертей на войне за бизнес", "Далее", "Отмена");
        }
        case 7:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Автошкола", "\
            "I"[1]"W" Продажа лицензий\n\
            "I"[2]"W" Продажа страховок", "Далее", "Отмена");
        }
        case 8:
        {
            ShowPlayerDialog(playerid, D_FRACTION_TOP_TYPE, DIALOG_STYLE_LIST, ""I"ТОП: Фракционный: Байкеры", "\
            "I"[1]"W" Ограблений банка\n\
            "I"[2]"W" Загруженно наркотиков\n\
            "I"[3]"W" Разгруженно наркотиков\n\
            "I"[4]"W" Загруженно патронов и материалов\n\
            "I"[5]"W" Разгруженно патронов и материалов\n\
            "I"[6]"W" Убийств на войне за бизнес\n\
            "I"[7]"W" Смертей на войне за бизнес", "Далее", "Отмена");
        }
    }
    return 1;
}

ShowFractionTopListInfo(playerid, idx, type)
{
    STRING_GLOBAL[0] = EOS;
    switch(idx)
    {
        case 0:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_unarrest` != 0 ORDER BY `ftop_unarrest` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_givepass` != 0 ORDER BY `ftop_givepass` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_selllawyerlic` != 0 ORDER BY `ftop_selllawyerlic` DESC LIMIT 25");
            }
        }
        case 1:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_arrest` != 0 ORDER BY `ftop_arrest` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_unkpz` != 0 ORDER BY `ftop_unkpz` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_su` != 0 ORDER BY `ftop_su` DESC LIMIT 25");
                case 3: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_unsu` != 0 ORDER BY `ftop_unsu` DESC LIMIT 25");
                case 4: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_ticket` != 0 ORDER BY `ftop_ticket` DESC LIMIT 25");
                case 5: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_frisk` != 0 ORDER BY `ftop_frisk` DESC LIMIT 25");
                case 6: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_take` != 0 ORDER BY `ftop_take` DESC LIMIT 25");
                case 7: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_sellgunlic` != 0 ORDER BY `ftop_sellgunlic` DESC LIMIT 25");
                case 8: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_pkills` != 0 ORDER BY `ftop_pkills` DESC LIMIT 25");
            }
        }
        case 2:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_aload_materials` != 0 ORDER BY `ftop_aload_materials` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_aunload_materials` != 0 ORDER BY `ftop_aunload_materials` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_akills` != 0 ORDER BY `ftop_akills` DESC LIMIT 25");
            }
        }
        case 3:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_heal` != 0 ORDER BY `ftop_heal` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_heal_drugs` != 0 ORDER BY `ftop_heal_drugs` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_sex` != 0 ORDER BY `ftop_sex` DESC LIMIT 25");
                case 3: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_medcard` != 0 ORDER BY `ftop_medcard` DESC LIMIT 25");
                case 4: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_hload_medicines` != 0 ORDER BY `ftop_hload_medicines` DESC LIMIT 25");
                case 5: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_hunload_medicines` != 0 ORDER BY `ftop_hunload_medicines` DESC LIMIT 25");
            }
        }
        case 4:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_edit` != 0 ORDER BY `ftop_edit` DESC LIMIT 25");
            }
        }
        case 5:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_rob_shop` != 0 ORDER BY `ftop_rob_shop` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_gload_drugs` != 0 ORDER BY `ftop_gload_drugs` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_gunload_drugs` != 0 ORDER BY `ftop_gunload_drugs` DESC LIMIT 25");
                case 3: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_gload_materials` != 0 ORDER BY `ftop_gload_materials` DESC LIMIT 25");
                case 4: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_gunload_materials` != 0 ORDER BY `ftop_gunload_materials` DESC LIMIT 25");
                case 5: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_gkills` != 0 ORDER BY `ftop_gkills` DESC LIMIT 25");
                case 6: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_gdeaths` != 0 ORDER BY `ftop_gdeaths` DESC LIMIT 25");
                case 7: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `member` > 0 AND `ftop_gkills_week` != 0 ORDER BY `ftop_gkills_week` DESC LIMIT 10");
            }
        }
        case 6:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_rob_bank` != 0 ORDER BY `ftop_rob_bank` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_mload_drugs` != 0 ORDER BY `ftop_mload_drugs` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_munload_drugs` != 0 ORDER BY `ftop_munload_drugs` DESC LIMIT 25");
                case 3: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_mload_materials` != 0 ORDER BY `ftop_mload_materials` DESC LIMIT 25");
                case 4: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_munload_materials` != 0 ORDER BY `ftop_munload_materials` DESC LIMIT 25");
                case 5: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_mbkills` != 0 ORDER BY `ftop_mbkills` DESC LIMIT 25");
                case 6: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_mbdeaths` != 0 ORDER BY `ftop_mbdeaths` DESC LIMIT 25");
            }
        }
        case 7:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_selllic` != 0 ORDER BY `ftop_selllic` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_sellinsurance` != 0 ORDER BY `ftop_sellinsurance` DESC LIMIT 25");
            }
        }
        case 8:
        {
            switch(type)
            {
                case 0: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_rob_bank` != 0 ORDER BY `ftop_rob_bank` DESC LIMIT 25");
                case 1: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_bload_drugs` != 0 ORDER BY `ftop_bload_drugs` DESC LIMIT 25");
                case 2: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_bunload_drugs` != 0 ORDER BY `ftop_bunload_drugs` DESC LIMIT 25");
                case 3: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_bload_materials` != 0 ORDER BY `ftop_bload_materials` DESC LIMIT 25");
                case 4: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_bunload_materials` != 0 ORDER BY `ftop_bunload_materials` DESC LIMIT 25");
                case 5: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_mbkills` != 0 ORDER BY `ftop_mbkills` DESC LIMIT 25");
                case 6: mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `ftop_mbdeaths` != 0 ORDER BY `ftop_mbdeaths` DESC LIMIT 25");
            }
        }
    }
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayerDialogTop", "ddd", playerid, idx, type);
    return 1;
}

forward ShowPlayerDialogTop(playerid, idx, type);
public ShowPlayerDialogTop(playerid, idx, type)
{
    switch(idx)
    {
        case -1:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], player_p_game_time;
                        STRING_GLOBAL = "[#] Ник\tОтыгранное время\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "p_game_time", player_p_game_time);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\n", i+1, nickname, ConvertTime(player_p_game_time));
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_PLAYER_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Обычный: Отыгранное время", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], player_level;
                        STRING_GLOBAL = "[#] Ник\tУровень\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "level", player_level);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\n", i+1, nickname, player_level);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_PLAYER_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Обычный: Уровень", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], player_money, player_bank, player_bank_deposit;
                        STRING_GLOBAL = "[#] Ник\tДеньги\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "money", player_money);
                            cache_get_value_name_int(i, "bank", player_bank);
                            cache_get_value_name_int(i, "bank_deposit", player_bank_deposit);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$\n", i+1, nickname, player_money + player_bank + player_bank_deposit);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_PLAYER_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Обычный: Деньги", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 3:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32];
                        STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\n", i+1, nickname);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_PLAYER_TOP_BACK, DIALOG_STYLE_LIST, ""I"ТОП: Обычный: Донат", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 4:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], player_bitcoin;
                        STRING_GLOBAL = "[#] Ник\tBitcoin\tВ $\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "bitcoin", player_bitcoin);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\t%d$\n", i+1, nickname, player_bitcoin, player_bitcoin * floatround(curs_btc * 0.95, floatround_ceil));
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_PLAYER_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Обычный: Bitcoin", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 0:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_unarrest;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tОсвобождение из тюрьмы\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_unarrest", fraction_ftop_unarrest);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_unarrest);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мэрия: Освобождение из тюрьмы", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_givepass;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tВыдача паспортов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_givepass", fraction_ftop_givepass);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_givepass);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мэрия: Выдача паспортов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_selllawyerlic;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПродажа лицензий на адвокатские услуги\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_selllawyerlic", fraction_ftop_selllawyerlic);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_selllawyerlic);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мэрия: Продажа лицензий на адвокатские услуги", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 1:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_arrest;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПроведение аррестов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_arrest", fraction_ftop_arrest);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_arrest);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Проведение аррестов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_unkpz;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tОсвобождение из тюрьмы\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_unkpz", fraction_ftop_unkpz);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_unkpz);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Освобождение из тюрьмы", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_su;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tВыдача розыска\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_su", fraction_ftop_su);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_su);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Выдача розыска", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 3:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_unsu;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tСнятие розыска\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_unsu", fraction_ftop_unsu);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_unsu);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Снятие розыска", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 4:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_ticket;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tВыписывание штрафов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_ticket", fraction_ftop_ticket);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_ticket);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Выписывание штрафов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 5:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_frisk;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПроведение обысков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_frisk", fraction_ftop_frisk);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_frisk);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Проведение обысков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 6:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_take;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tИзъятие вещей\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_take", fraction_ftop_take);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_take);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Изъятие вещей", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 7:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_sellgunlic;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПродажа лицензий на оружие\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_sellgunlic", fraction_ftop_sellgunlic);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_sellgunlic);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Продажа лицензий на оружие", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 8:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_pkills;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tУбийств членов нелегальных организаций\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_pkills", fraction_ftop_pkills);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_pkills);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Полиция и ФБР: Убийств членов нелегальных организаций", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 2:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_aload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_aload_materials", fraction_ftop_aload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_aload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Армия: Загруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_aunload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_aunload_materials", fraction_ftop_aunload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_aunload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Армия: Разгруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_akills;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tУбийств членов нелегальных организаций\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_akills", fraction_ftop_akills);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_akills);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Армия: Убийств членов нелегальных организаций", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 3:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_heal;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЛечение больных\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_heal", fraction_ftop_heal);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_heal);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Больница: Лечение больных", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_heal_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЛечение наркозависимых\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_heal_drugs", fraction_ftop_heal_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_heal_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Больница: Лечение наркозависимых", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_sex;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПроведение операций по смене пола\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_sex", fraction_ftop_sex);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_sex);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Больница: Проведение операций по смене пола", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 3:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_medcard;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tВыдача мед. карт\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_medcard", fraction_ftop_medcard);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_medcard);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Больница: Выдача мед. карт", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 4:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_hload_medicines;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно медикаментов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_hload_medicines", fraction_ftop_hload_medicines);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_hload_medicines);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Больница: Загруженно медикаментов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 5:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_hunload_medicines;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно медикаментов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_hunload_medicines", fraction_ftop_hunload_medicines);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_hunload_medicines);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Больница: Разгруженно медикаментов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 4:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_edit;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tОтредактированно объявлений\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_edit", fraction_ftop_edit);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_edit);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Радио: Отредактированно объявлений", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 5:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_rob_shop;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tОграблений магазина\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_rob_shop", fraction_ftop_rob_shop);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_rob_shop);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Ограблений магазина", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_gload_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно наркотиков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_gload_drugs", fraction_ftop_gload_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_gload_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Загруженно наркотиков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_gunload_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно наркотиков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_gunload_drugs", fraction_ftop_gunload_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_gunload_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Разгруженно наркотиков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 3:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_gload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_gload_materials", fraction_ftop_gload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_gload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Загруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 4:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_gunload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_gunload_materials", fraction_ftop_gunload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_gunload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Разгруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 5:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_gkills;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tУбийств на захватах территорий\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_gkills", fraction_ftop_gkills);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_gkills);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Убийств на захватах территорий", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 6:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_gdeaths;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tСмертей на захватах территорий\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_gdeaths", fraction_ftop_gdeaths);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_gdeaths);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Банды: Смертей на захватах территорий", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 7,8:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, 
                            fraction_ftop_gkills_week,
                            fraction_ftop_gdeaths_week,
                            Float:fraction_ftop_gdamagegive_week,
                            Float:fraction_ftop_gdamagetake_week;

                        STRING_GLOBAL = ""W"[#] Ник\t"W"Фракция на данный момент\t"W"Убийств/Смертей\t"W"Нанесенный/полученный урон\n";
                        for(new i; i < 10; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);

                            cache_get_value_name_int(i, "ftop_gkills_week", fraction_ftop_gkills_week);
                            cache_get_value_name_int(i, "ftop_gdeaths_week", fraction_ftop_gdeaths_week);
                            cache_get_value_name_float(i, "ftop_gdamagegive_week", fraction_ftop_gdamagegive_week);
                            cache_get_value_name_float(i, "ftop_gdamagetake_week", fraction_ftop_gdamagetake_week);

                            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%s\t%d/%d\t%0.2f/%0.2f\n", STRING_GLOBAL, i+1, nickname, 
                                GetFractionName(fraction_member), fraction_ftop_gkills_week, fraction_ftop_gdeaths_week,
                                fraction_ftop_gdamagegive_week, fraction_ftop_gdamagetake_week);
                        }
                        f(STRING_GLOBAL, "%s"I"[#] "W"Ваша статистика:\t \t%d/%d\t%0.2f/%0.2f", STRING_GLOBAL, 
                            p_info[playerid][ftop_gkills_week], p_info[playerid][ftop_gdeaths_week],
                            p_info[playerid][ftop_gdamagegive_week], p_info[playerid][ftop_gdamagetake_week]);
                        ShowPlayerDialog(playerid, type == 7 ? D_FRACTION_TOP_BACK : D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Банды: Недельный топ", STRING_GLOBAL, "Далее", "Отмена");
                    }
                    else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 6:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_rob_bank;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tОграблений банка\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_rob_bank", fraction_ftop_rob_bank);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_rob_bank);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Ограблений банка", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_mload_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно наркотиков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_mload_drugs", fraction_ftop_mload_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_mload_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Загруженно наркотиков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_munload_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно наркотиков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_munload_drugs", fraction_ftop_munload_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_munload_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Разгруженно наркотиков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 3:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_mload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_mload_materials", fraction_ftop_mload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_mload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Загруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 4:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_munload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_munload_materials", fraction_ftop_munload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_munload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Разгруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 5:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_mbkills;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tУбийств на войне за бизнес\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_mbkills", fraction_ftop_mbkills);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_mbkills);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Убийств на войне за бизнес", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 6:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_mbdeaths;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tСмертей на войне за бизнес\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_mbdeaths", fraction_ftop_mbdeaths);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_mbdeaths);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Мафии: Смертей на войне за бизнес", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 7:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_selllic;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПродажа лицензий\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_selllic", fraction_ftop_selllic);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_selllic);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Автошкола: Продажа лицензий", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_sellinsurance;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tПродажа страховок\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_sellinsurance", fraction_ftop_sellinsurance);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_sellinsurance);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Автошкола: Продажа страховок", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
        case 8:
        {
            switch(type)
            {
                case 0:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_rob_bank;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tОграблений банка\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_rob_bank", fraction_ftop_rob_bank);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_rob_bank);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Ограблений банка", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 1:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_bload_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно наркотиков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_bload_drugs", fraction_ftop_bload_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_bload_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Загруженно наркотиков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 2:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_bunload_drugs;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно наркотиков\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_bunload_drugs", fraction_ftop_bunload_drugs);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_bunload_drugs);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Разгруженно наркотиков", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 3:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_bload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tЗагруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_bload_materials", fraction_ftop_bload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_bload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Загруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 4:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_bunload_materials;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tРазгруженно патронов и материалов\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_bunload_materials", fraction_ftop_bunload_materials);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_bunload_materials);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Разгруженно патронов и материалов", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 5:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_mbkills;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tУбийств на войне за бизнес\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_mbkills", fraction_ftop_mbkills);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_mbkills);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Убийств на войне за бизнес", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
                case 6:
                {
                    if(cache_num_rows())
                    {
                        new nickname[32], fraction_member, fraction_ftop_mbdeaths;
                        STRING_GLOBAL = "[#] Ник\tОрганизация на данный момент\tСмертей на войне за бизнес\n", STRING_MIN[0] = EOS;
                        for(new i; i < 25; i++)
                        {
                            if(i >= cache_num_rows()) break;
                            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
                            cache_get_value_name_int(i, "member", fraction_member);
                            cache_get_value_name_int(i, "ftop_mbdeaths", fraction_ftop_mbdeaths);
                            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%d\n", i+1, nickname, GetFractionName(fraction_member), fraction_ftop_mbdeaths);
                            strcat(STRING_GLOBAL, STRING_MIN);
                        }
                        ShowPlayerDialog(playerid, D_FRACTION_TOP_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП: Фракционный: Байкеры: Смертей на войне за бизнес", STRING_GLOBAL, "Далее", "Отмена");
                    } else SendError(playerid, "Ничего не найдено.");
                }
            }
        }
    }
    return 1;
}
