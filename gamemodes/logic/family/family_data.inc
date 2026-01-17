/*
    Family System 2020
    Author: Vip_Uzer
*/

////////// family systems
forward load_family();
public load_family()
{
    new time = GetTickCount(),
        rows, data[256];
    cache_get_row_count(rows);
    if(rows)
    {
        for(new i; i < rows; i++)
        {
            family_count++;
            cache_get_value_name_int(i, "id", FamilyData[i][fMysqlID]);
            cache_get_value_name(i,"name", FamilyData[i][fName],21);
            cache_get_value_name_int(i, "owner_id", FamilyData[i][fOwnerID]);
            cache_get_value_name(i,"creating_date", FamilyData[i][fCreatingDate],12);

            cache_get_value_name_int(i, "money",FamilyData[i][fMoney]);
            cache_get_value_name_int(i, "level",FamilyData[i][fLevel]);
            cache_get_value_name_int(i, "exp",FamilyData[i][fExp]);
            cache_get_value_name_int(i, "season_exp",FamilyData[i][fSeasonExp]);
            cache_get_value_name_int(i, "type_id",FamilyData[i][fTypeID]);
            cache_get_value_name_int(i, "office",FamilyData[i][fOffice]);

            cache_get_value_name_int(i, "color_id", FamilyData[i][fColorID]);
            cache_get_value_name_int(i, "members_count", FamilyData[i][fMembersCount]);

            if(FamilyData[i][fMembersCount] < 0) FamilyData[i][fMembersCount] = 0;

            cache_get_value_name_int(i, "house_id", FamilyData[i][fHouseID]);

            new house_id = FamilyData[i][fHouseID];
            if(house_id != INVALID_HOUSE_ID)
            {
                if(h_info[house_id][h_family_id] == FamilyData[i][fMysqlID]) {
                    update_house(house_id);
                }
                else
                { // дом слетел значит отключаем семью от него
                    FamilyData[i][fHouseID] = INVALID_HOUSE_ID;

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `spawn` = 0 WHERE `spawn` = '3' AND `family_id` = %d",
                        FamilyData[i][fMysqlID]);
                    mysql_tquery (con_bd, STRING_GLOBAL);

                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `house_id` = -1 WHERE `id` = %d", FamilyData[i][fMysqlID]);
                    mysql_tquery (con_bd, STRING_GLOBAL);
                }
            }

            for(new j = MAX_FAMILY_VEHICLES-1; j != -1; j--)
                FamilyData[i][fVehicleID][j] = INVALID_VEHICLE_ID;

            cache_get_value_name(i, "rang_0", FAMILY_RANG[i][0], 16);
            cache_get_value_name(i, "rang_1", FAMILY_RANG[i][1], 16);
            cache_get_value_name(i, "rang_2", FAMILY_RANG[i][2], 16);
            cache_get_value_name(i, "rang_3", FAMILY_RANG[i][3], 16);
            cache_get_value_name(i, "rang_4", FAMILY_RANG[i][4], 16);
            cache_get_value_name(i, "rang_5", FAMILY_RANG[i][5], 16);
            cache_get_value_name(i, "rang_6", FAMILY_RANG[i][6], 16);
            cache_get_value_name(i, "rang_7", FAMILY_RANG[i][7], 16);
            cache_get_value_name(i, "rang_8", FAMILY_RANG[i][8], 16);
            cache_get_value_name(i, "rang_9", FAMILY_RANG[i][9], 16);

            cache_get_value_name(i, "settings_rangs", data); // настройка доступов по рангам
            sscanf(data, "p<|>a<i>[15]", FamilyData[i][fSettingRang]);

            cache_get_value_name(i, "skins", data); // ИДы СЛОТОВ ИДОВ СКИНОВ
            sscanf(data, "p<|>a<i>[15]", FamilyData[i][fSkinID]);

            cache_get_value_name(i, "skins_rangs_man", data); // ИДы СЛОТОВ ИДОВ СКИНОВ
            sscanf(data, "p<|>a<i>[10]", FamilyData[i][fSkinMan]);

            cache_get_value_name(i, "skins_rangs_woman", data); // ИДы СЛОТОВ ИДОВ СКИНОВ
            sscanf(data, "p<|>a<i>[10]", FamilyData[i][fSkinWoman]);

            for(new j = 9; j != -1; j --)
            {
                switch(FamilyData[i][fSkinID][j])
                {
                    case 799: FamilyData[i][fSkinID][j] = 746;
                    case 907: FamilyData[i][fSkinID][j] = 747;
                    case 793: FamilyData[i][fSkinID][j] = 740;
                    case 794: FamilyData[i][fSkinID][j] = 741;
                    case 795: FamilyData[i][fSkinID][j] = 742;
                    case 796: FamilyData[i][fSkinID][j] = 743;
                    case 797: FamilyData[i][fSkinID][j] = 744;
                    case 798: FamilyData[i][fSkinID][j] = 745;
                    case 908: FamilyData[i][fSkinID][j] = 748;
                    case 909: FamilyData[i][fSkinID][j] = 749;
                    case 965: FamilyData[i][fSkinID][j] = 750;
                    case 999: FamilyData[i][fSkinID][j] = 751;
                    case 1194: FamilyData[i][fSkinID][j] = 752;
                    case 1195: FamilyData[i][fSkinID][j] = 753;
                    case 1196: FamilyData[i][fSkinID][j] = 754;
                    case 1197: FamilyData[i][fSkinID][j] = 755;
                    case 1198: FamilyData[i][fSkinID][j] = 756;
                    case 1199: FamilyData[i][fSkinID][j] = 757;
                    case 1200: FamilyData[i][fSkinID][j] = 758;
                    case 1201: FamilyData[i][fSkinID][j] = 759;
                    case 1202: FamilyData[i][fSkinID][j] = 760;
                    case 1203: FamilyData[i][fSkinID][j] = 761;
                    //default: FamilyData[i][fSkinID][j] =  INVALID_SKIN_ID;
                }

                switch(FamilyData[i][fSkinMan][j])
                {
                    case 1..311: { }
                    case 799: FamilyData[i][fSkinMan][j] = 746;
                    case 907: FamilyData[i][fSkinMan][j] = 747;
                    case 793: FamilyData[i][fSkinMan][j] = 740;
                    case 794: FamilyData[i][fSkinMan][j] = 741;
                    case 795: FamilyData[i][fSkinMan][j] = 742;
                    case 796: FamilyData[i][fSkinMan][j] = 743;
                    case 797: FamilyData[i][fSkinMan][j] = 744;
                    case 798: FamilyData[i][fSkinMan][j] = 745;
                    case 908: FamilyData[i][fSkinMan][j] = 748;
                    case 909: FamilyData[i][fSkinMan][j] = 749;
                    case 965: FamilyData[i][fSkinMan][j] = 750;
                    case 999: FamilyData[i][fSkinMan][j] = 751;
                    case 1194: FamilyData[i][fSkinMan][j] = 752;
                    case 1195: FamilyData[i][fSkinMan][j] = 753;
                    case 1196: FamilyData[i][fSkinMan][j] = 754;
                    case 1197: FamilyData[i][fSkinMan][j] = 755;
                    case 1198: FamilyData[i][fSkinMan][j] = 756;
                    case 1199: FamilyData[i][fSkinMan][j] = 757;
                    case 1200: FamilyData[i][fSkinMan][j] = 758;
                    case 1201: FamilyData[i][fSkinMan][j] = 759;
                    case 1202: FamilyData[i][fSkinMan][j] = 760;
                    case 1203: FamilyData[i][fSkinMan][j] = 761;
                    //default: FamilyData[i][fSkinMan][j] =  INVALID_SKIN_ID;
                }

                switch(FamilyData[i][fSkinWoman][j])
                {
                    //case 1..311: { }
                    case 799: FamilyData[i][fSkinWoman][j] = 746;
                    case 907: FamilyData[i][fSkinWoman][j] = 747;
                    case 793: FamilyData[i][fSkinWoman][j] = 740;
                    case 794: FamilyData[i][fSkinWoman][j] = 741;
                    case 795: FamilyData[i][fSkinWoman][j] = 742;
                    case 796: FamilyData[i][fSkinWoman][j] = 743;
                    case 797: FamilyData[i][fSkinWoman][j] = 744;
                    case 798: FamilyData[i][fSkinWoman][j] = 745;
                    case 908: FamilyData[i][fSkinWoman][j] = 748;
                    case 909: FamilyData[i][fSkinWoman][j] = 749;
                    case 965: FamilyData[i][fSkinWoman][j] = 750;
                    case 999: FamilyData[i][fSkinWoman][j] = 751;
                    case 1194: FamilyData[i][fSkinWoman][j] = 752;
                    case 1195: FamilyData[i][fSkinWoman][j] = 753;
                    case 1196: FamilyData[i][fSkinWoman][j] = 754;
                    case 1197: FamilyData[i][fSkinWoman][j] = 755;
                    case 1198: FamilyData[i][fSkinWoman][j] = 756;
                    case 1199: FamilyData[i][fSkinWoman][j] = 757;
                    case 1200: FamilyData[i][fSkinWoman][j] = 758;
                    case 1201: FamilyData[i][fSkinWoman][j] = 759;
                    case 1202: FamilyData[i][fSkinWoman][j] = 760;
                    case 1203: FamilyData[i][fSkinWoman][j] = 761;
                    //default: FamilyData[i][fSkinWoman][j] =  INVALID_SKIN_ID;
                }
            }

            cache_get_value_name(i, "salary_rangs", data); // 0|0|0|0|0|0|0|0|0|0
            sscanf(data, "p<|>a<i>[10]", FamilyData[i][fSalaryRang]);

            UpdateFamilyType(i);

            FamilyData[i][fCaptureAllowed] = 0;
        }
        printf("[Загружено семей]: <%d>. Потрачено: <%i ms>.", rows, GetTickCount()-time);
    }
    else print("[Загружено семей]: <0>. Потрачено: <->.");
    return 1;
}

forward Family_Info(playerid, idx);
public Family_Info(playerid, idx)
{
    new rows, FamilyOwner[MAX_PLAYER_NAME];
    cache_get_row_count(rows);

    if(rows)
    {
        cache_get_value_name(0, "name", FamilyOwner, MAX_PLAYER_NAME);
        new family_online = GetFamilyOnline(idx);

        if(FamilyData[idx][fMembersCount] < 0) FamilyData[idx][fMembersCount] = 0;
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL,sizeof(STRING_GLOBAL),
            ""W"Название: "I"%s"W"\n\
            Тип: "I"%s"W"\n\
            Дата создания: "I"%s"W"\n\
            Владелец: "I"%s"W"\n\
            Онлайн: "I"%d"W" игрок(ов)\n\
            Состав: всего "I"%d"W" игрок(ов)\n\
            \n\
            Бюджет: "I"%d$"W"\n\
            Уровень: "I"%d (EXP: %d/%d)"W"\n\
            Сезонные очки: "I"%d"W"\n\
            Количество территорий: "I"%d из %d",
        FamilyData[idx][fName], FAMILY_TYPE_NAME[FamilyData[idx][fTypeID]], FamilyData[idx][fCreatingDate], FamilyOwner, family_online, FamilyData[idx][fMembersCount],
        FamilyData[idx][fMoney], FamilyData[idx][fLevel], FamilyData[idx][fExp], (FamilyData[idx][fLevel]+1)*COUNT_EXP_FAMILY,
        FamilyData[idx][fSeasonExp], FamilyData[idx][fCaptZoneCount], count_family_zone);
        ShowPlayerDialog(playerid, D_FAMILY_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о семье",STRING_GLOBAL,"Назад","");
    }
    return 1;
}

forward Create_Family(playerid, FamilyName[]);
public Create_Family(playerid, FamilyName[])
{
    new rows;
    cache_get_row_count(rows);
    if(rows)
    {
        SendError(playerid, "Название семьи уже используется.");
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "\
            "W"Создание семьи стоит: "I"500 Flin Money\n\
            "W"Всего семей: "I"%d\n\
            "W"Введите название семьи:\n\n\
            {AFAFAF}Допустимое значение количества символов от 3 до 20", family_count);
        return ShowPlayerDialog(playerid, D_FAMILY_CREATE, DIALOG_STYLE_INPUT, ""I"Создание семьи", STRING_GLOBAL, "Принять", "Назад");
    }
    if(p_info[playerid][flinmoney] < 500)
        return SendError(playerid, "У Вас нет столько Flin Money.");
    if(p_info[playerid][level] < 10)
        return SendError(playerid, "Создание семьи доступно с 10-ого уровня.");

    new year, month,day;
    getdate(year, month, day);
    format(FamilyData[family_count][fCreatingDate], 16, "%02d/%02d/%d", day, month,year);
    strmid (FamilyData[family_count][fName], FamilyName, 0, strlen(FamilyName), strlen(FamilyName)+5);
    FamilyData[family_count][fOwnerID] = p_info[playerid][ID];

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `family` (`name`, `owner_id`, `members_count`, `creating_date`, `level`, `exp`) VALUES ( '%s', %d, '1', '%s', '1', '1')",
        FamilyData[family_count][fName], FamilyData[family_count][fOwnerID], FamilyData[family_count][fCreatingDate]);
    mysql_tquery(con_bd, STRING_GLOBAL, "get_family_id", "ii", playerid, family_count);

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

    SendAccess(playerid, "Вы создали семью.");
    SendInfo(playerid, "Команды семьи: /mm > Команды > Семья");

    MysqlUpdatePlayerStr(playerid, "family_enter", FamilyData[family_count][fCreatingDate]);
    p_info[playerid][family_rang] = MAX_FAMILY_RANG;
    p_info[playerid][family_exp] =
    p_info[playerid][family_mute] = 0;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы успешно создали семью "I"%s"W".\n\nДля усправления используйте - /family\nБольше команд Вы найдете - /help", FamilyData[family_count][fName]);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Создание семьи", STRING_GLOBAL, "Закрыть", "");

    family_count++;
    save_player(playerid);
    return 1;
}

UpdateFamilyLabel(playerid, bool:addLabel)
{
    new family_idx = p_temp[playerid][family_game_id];
    if(family_idx == -1)
    {
        if(p_temp[playerid][family_label] != Text3D:-1)
        {
            DestroyDynamic3DTextLabel(p_temp[playerid][family_label]);
            p_temp[playerid][family_label] = Text3D:-1;
        }
        return 1;
    }
    if(p_temp[playerid][family_label] != Text3D:-1)
    {
        if(addLabel) UpdateDynamic3DTextLabelText(p_temp[playerid][family_label], FAMILY_COLORS[FamilyData[family_idx][fColorID]], FamilyData[family_idx][fName]);
        else
        {
            DestroyDynamic3DTextLabel(p_temp[playerid][family_label]);
            p_temp[playerid][family_label] = Text3D:-1;
        }
    }
    else
    {
        if(addLabel)
        {
            p_temp[playerid][family_label] = CreateDynamic3DTextLabel(FamilyData[family_idx][fName], FAMILY_COLORS[FamilyData[family_idx][fColorID]], 0.0, 0.0, -0.3, 20.0, playerid, .testlos = 1);
            foreach(new i: PlayerPlayersStream[playerid]) Streamer_ToggleItem(i, STREAMER_TYPE_3D_TEXT_LABEL, p_temp[playerid][family_label], p_info[i][p_settings][FAMILY_LABEL]);
        }
    }
    return 1;
}

ToggleVisibleFamilyLabel(playerid)
{
    foreach(new i: PlayerPlayersStream[playerid])
    {
        if(p_temp[i][family_label] != Text3D:-1)
            Streamer_ToggleItem(playerid, STREAMER_TYPE_3D_TEXT_LABEL, p_temp[i][family_label], p_info[playerid][p_settings][FAMILY_LABEL]);
    }
    Streamer_Update(playerid, STREAMER_TYPE_3D_TEXT_LABEL);
}

forward get_family_id(playerid, id);
public get_family_id(playerid, id)
{
    FamilyData[id][fMysqlID] = cache_insert_id();
    p_info[playerid][family_id] = FamilyData[id][fMysqlID];
    p_temp[playerid][family_game_id] = id;

    p_info[playerid][flinmoney] -= 500;
    MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

    UpdateFamilyLabel(playerid, true);
    return 1;
}

forward Rename_Family(playerid, inputtext[], family_idx);
public Rename_Family(playerid, inputtext[], family_idx)
{
    new rows;
    cache_get_row_count(rows);
    if(rows)
    {
        SendError(playerid, "Название семьи уже используется.");

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, 300, "\
            "W"Текущее название семьи: {FF9900}%s\n\n\
            "W"Введите новое название семьи:\n\n\
            {AFAFAF}Допустимое значение количества символов от 3 до 20",
            FamilyData[family_idx][fName]);

        return ShowPlayerDialog(playerid, D_FAMILY_RENAME, DIALOG_STYLE_INPUT, ""I"Смена названия семьи", STRING_GLOBAL, "Принять", "Назад");
    }
    if(p_info[playerid][flinmoney] < 100) return SendError(playerid, "Для смены названия семьи нужно 100 Flin Money.");

    p_info[playerid][flinmoney] -= 100;
    MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

    format(FamilyData[family_idx][fName], 21, inputtext);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] изменил название семьи на %s.", get_name(playerid), playerid, FamilyData[family_idx][fName]);
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `name` = '%e' WHERE `id` = %d", FamilyData[family_idx][fName], p_info[playerid][family_id]);
    mysql_tquery (con_bd, STRING_GLOBAL);

    new f_house_id = FamilyData[family_idx][fHouseID];
    if(f_house_id != INVALID_HOUSE_ID && h_info[f_house_id][h_family_id] == FamilyData[family_idx][fMysqlID]) update_house(f_house_id);

    foreach(new i: Player)
    {
        if(p_temp[i][family_game_id] == family_idx) UpdateFamilyLabel(i, true);
    }
    return 1;
}

GetFamilyIDFromHouseID(house_id) // получить ид семьи из ид дома
{
    if(h_info[house_id][h_family_id] != INVALID_HOUSE_ID)
    {
        for(new i = family_count-1; i != -1; i--)
        {
            //printf("%d == %d && %d == %d", FamilyData[i][fHouseID], h_info[house_id][h_mysql_id], h_info[house_id][h_family_id], FamilyData[i][fMysqlID]);
            if(FamilyData[i][fHouseID] == h_info[house_id][h_mysql_id] &&
                h_info[house_id][h_family_id] == FamilyData[i][fMysqlID]) return i;
        }
    }
    return -1;
}

forward FamilyOfflineMemberInfo(playerid);
public FamilyOfflineMemberInfo(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(rows)
    {
        new last_enter_date[16], member_name[MAX_PLAYER_NAME], invite_date[16], family_rang_id, family_warns, family_exps;
        cache_get_value_name(0, "name", member_name);
        cache_get_value_name_int(0, "family_rang", family_rang_id);
        cache_get_value_name_int(0, "family_exp", family_exps);
        cache_get_value_name_int(0, "family_warn", family_warns);
        cache_get_value_name(0, "family_enter", invite_date, 16);
        cache_get_value_name(0, "lastenter", last_enter_date);
        if(family_rang_id < 1) family_rang_id = 1;
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, ""W"Имя: "I"%s\n"W"Должность: "I"%s(%d)\n"W"Заработано: "I"%d EXP\n"W"Предупреждения: "I"%d\n\n"W"В семье с "I"%s"W"\nПоследний вход: "I"%s"W"",
            member_name, FAMILY_RANG[GetPlayerFamilyID(playerid)][family_rang_id-1], family_rang_id, family_exps, family_warns, invite_date, last_enter_date);
        ShowPlayerDialog(playerid, D_FAMILY_MEMBER_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация об игроке", STRING_GLOBAL, "Назад", "" );
    }
    if(!rows) UpdatePlayerList(playerid);
    return 1;
}

/// stock's familys
stock LoadPlayerFamilyID(playerid)
{
    if(p_info[playerid][family_id] != -1)
    {
        for(new i = family_count-1; i != -1; i--)
        {
            if(FamilyData[i][fMysqlID] == p_info[playerid][family_id])
            {
                p_temp[playerid][family_game_id] = i;
                return i;
            }
        }
        p_info[playerid][family_id] = -1;
    }
    return 1;
}

GetFamilyMaxCountVehicle(family_idx)
{
    if(family_idx == -1) return 0;
    new count_veh, f_house_id = FamilyData[family_idx][fHouseID];
    if(f_house_id != INVALID_HOUSE_ID)
    {
        count_veh += h_info[f_house_id][h_squar]+1;
        if(h_info[family_idx][h_air_pos][0] != 0.0 ||
            h_info[family_idx][h_air_pos][1] != 0.0) count_veh++;
        if(h_info[family_idx][h_boat_status]) count_veh++;
    }
    if(FamilyData[family_idx][fOffice] == 1)
        count_veh += 5;
    if(count_veh > MAX_FAMILY_VEHICLES) count_veh = MAX_FAMILY_VEHICLES;
    return count_veh;
}

SendFamilyMessage(family, string[], bool:IsLogged = true, bool:IsNotify = false)
{
    new send_string[256];
    if(IsLogged)
    {
        mysql_format(con_bd, send_string, sizeof(send_string), "INSERT INTO `family_log` (`id`, `text`, `date`) VALUES (%d, '%e', NOW())", FamilyData[family][fMysqlID], string);
        mysql_tquery(con_bd, send_string);
    }
    if(IsNotify)
    {
        mysql_format(con_bd, send_string, sizeof(send_string), "INSERT INTO `family_notify` (`id`, `text`, `date`) VALUES (%d, '%e', NOW())", FamilyData[family][fMysqlID], string);
        mysql_tquery(con_bd, send_string);
        f(send_string, "[%s] [NOTIFY] %s", FamilyData[family][fName], string);
    }
    else f(send_string, "[%s] %s", FamilyData[family][fName], string);
    foreach(new i : Player)
    {
        if((p_temp[i][family_game_id] == family && p_info[i][p_settings][CHAT_FAMILY]) || 
            (p_info[i][admin] > 0 && p_temp[i][tipster_family] == family && p_info[i][p_settings][CHAT_FAMILY]))
        {
            SendMes(i, FAMILY_COLORS[FamilyData[family][fColorID]], send_string);
        }
    }

}

UpdateFamilyType(idx)
{
    FamilyData[idx][fTypeID] = 0;
    if(FamilyData[idx][fHouseID] != INVALID_HOUSE_ID) FamilyData[idx][fTypeID] = 1;
    if(FamilyData[idx][fOffice] == 1) FamilyData[idx][fTypeID] = 2;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `type_id` = %d WHERE `id` = %d", FamilyData[idx][fTypeID], FamilyData[idx][fMysqlID]);
    mysql_tquery (con_bd, STRING_GLOBAL);
    return 1;
}

///command's family
CMD:family(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_online = 0,
        family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
    foreach(new i: Player)
    {
        if(p_info[playerid][family_id] == p_info[i][family_id]) family_online++;
    }
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "\
        "I"[1]"W" Информация \t \n\
        "I"[2]"W" Инвентарь семьи\t \n\
        "I"[3]"W" Настройки \t \n\
        "I"[4]"W" Бюджет: \t"I"%d$\n\
        "I"[5]"W" Оповещения \t \n\
        "I"[6]"W" Оффлайн состав \t \n\
        "I"[7]"W" Члены онлайн: \t"I"%d"W" человек(а)\n\
        "I"[8]"W" Сезонный топ \t \n\
        "I"[9]"W" FAQ: {"#cRED"}Как повышается уровень?"W"\n\
        "I"[10]{"#cRED"} Покинуть семью\n", FamilyData[family_idx][fMoney], family_online);
    ShowPlayerDialog(playerid, D_FAMILY_MENU, DIALOG_STYLE_TABLIST, ""I"Меню семьи", STRING_GLOBAL, "Выбор", "Выход");
    return 1;
}

alias:family("union");
CMD:finvite(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid);
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_INVITE])
        return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /finvite [id игрока]");
    else if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    else if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    else if(p_info[params[0]][family_id] != -1) return SendError(playerid, "Игрок уже состоит в семье.");
    else if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    else if(GetPVarInt(params[0],"BoneStol_ID")) return 1;
    //else if(FamilyData[family_idx][fMembersCount] >= FamilyData[family_idx][fLevel]*MAX_FAMILY_MEMBERS) return SendError(playerid, "В семье нет места, повышайте уровень семьи чтобы расширить количество мест.");

    new Cache:result, fbl_reason[50];
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `reason` FROM `family_blacklist` WHERE `target_id` = %d AND `id` = %d LIMIT 1", p_info[params[0]][ID], p_info[playerid][family_id]);
    result = mysql_query(con_bd, STRING_GLOBAL);
    if(cache_num_rows() != 0)
    {
        cache_get_value_name(0, "reason", fbl_reason);
        cache_delete(result);
        return SendError(playerid, "Данный игрок в черном списке семьи по причине: %s.", fbl_reason);
    }
    cache_delete(result);

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""W"Вы хотите предложить "I"%s "W"вступить в семью \"%s\"", get_name(params[0]), FamilyData[family_idx][fName]);
    ShowPlayerDialog(playerid, D_OFFER_PLAYER, DIALOG_STYLE_MSGBOX, ""I"Принять в семью", STRING_GLOBAL, "Далее", "Отмена");
    SetOfferData(playerid, params[0], OFFER_ID_INVITE_FAMILY);
    return 1;
}
alias:finvite("uinvite");
alias:funinvite("uuninvite");
CMD:funinvite(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid), reason[144];
    if(sscanf(params, "us[144]", params[0], reason)) return SendInfo(playerid, "Используйте: /funinvite [id игрока] [причина]");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(p_info[playerid][family_id] != p_info[params[0]][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_UNINVITE]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(GetFamilyRang(playerid) <= GetFamilyRang(params[0]) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(FamilyData[family_idx][fOwnerID] == p_info[params[0]][ID]) return SendError(playerid, "Применить данное действие к лидеру нельзя.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);

    Log(LOG_player, INFO, "%s[%d](%s %s) был уволен %s[%d](%s %s) из %s | #Family",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", FamilyData[family_idx][fName]);

    Log(LOG_player, INFO, "%s[%d](%s %s) уволил %s[%d](%s %s) из %s | #Family",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC", FamilyData[family_idx][fName]);

    LeaveFamily(playerid, params[0], reason);
    return 1;
}

CMD:ffcars(playerid, params[])
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
    new f_house_id = FamilyData[family_idx][fHouseID],
        f_office = FamilyData[family_idx][fOffice];
    if(f_house_id == -1 && f_office != 1)
        return callcmd::family(playerid, "/0"), SendError(playerid, "У семьи нет дома или офиса.");
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_model`, `v_mysql_id` FROM `vehicle` WHERE `v_family_id` = %d", FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "list_family_vehicle", "ii", playerid, family_idx);
    return 1;
}
alias:ffcars("familycars");

CMD:ffindcar(playerid, params[])
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /ffindcar [id (1-%d)]", GetFamilyMaxCountVehicle(family_idx));
    params[0]--;
    if(!(0 <= params[0] < MAX_FAMILY_VEHICLES))
    {
        SendInfo(playerid, "Используйте: /ffindcar [id (1-%d)] ", GetFamilyMaxCountVehicle(family_idx));
        return 1;
    }
    if(FamilyData[family_idx][fVehicleID][params[0]] == INVALID_VEHICLE_ID) return SendError(playerid, "Транспортное средство не созданно.");

    if(IsGPSVisable(playerid) != -1) return 1;

    new Float:POS[3];
    GetVehiclePos(FamilyData[family_idx][fVehicleID][params[0]], POS[0], POS[1], POS[2]);

    new Float:distance = GetPlayerDistanceFromPoint(playerid, POS[0], POS[1], POS[2]);

    if(p_temp[playerid][TaxiGPS] == true)
    {
        if(GetPlayerTaxiDriver(playerid) == INVALID_PLAYER_ID) return SendError(playerid, "В такси нет водителя.");

        new driverid = GetPlayerTaxiDriver(playerid);
        p_temp[playerid][TaxiGPS] = false;
        SetPlayerGPS(driverid, POS[0], POS[1], POS[2], 5.0);

        SendInfo(driverid, "%s обозначил место назначения. Расстояние: %.0f метров.", get_name(playerid), distance);
        return 1;
    }
    if(p_temp[playerid][p_GPS] == true) CancelPlayerGPS(playerid);

    SetPlayerGPS(playerid, POS[0], POS[1], POS[2], 5.0);
    SendInfo(playerid, "\"Транспорт\" отмечен на GPS навигаторе. Расстояние: %.0f метров.", distance);
    return 1;
}

LeaveFamily(playerid, target, reason[])
{
    if(!IsPlayerConnected(target) || target == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");

    new family_idx = GetPlayerFamilyID(playerid);

    if(p_info[target][ID] == FamilyData[family_idx][fOwnerID])
        return SendError(playerid, "Игрок лидер семьи.");
    if(p_info[playerid][family_id] != p_info[target][family_id]) 
        return SendError(playerid, "Игрок не состоит в семье.");

    SendInfo(target, "%s выгнал(а) Вас из семьи. Причина: %s", get_name(playerid), reason);
    SendAccess(playerid, "Вы выгнали %s из семьи. Причина: %s", get_name(target), reason);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] выгнал %s[%d] из семьи. Причина: %s", get_name(playerid), playerid, get_name(target), target, reason);
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    FamilyData[family_idx][fMembersCount]--;
    p_info[target][family_id] = -1;
    p_temp[target][family_game_id] = -1;
    p_info[target][family_rang] =
    p_info[target][family_exp] =
    p_info[target][family_mute] =
    p_info[target][family_warn] = 0;

    MysqlUpdatePlayerStr(target, "family_enter", "-");
    UpdateFamilyLabel(target, false);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `members_count` = %d WHERE `id` = %d",
        FamilyData[family_idx][fMembersCount], FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    SetPlayerSkinEx(target);
    return 1;
}

CMD:frang(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
    if(sscanf(params, "ui", params[0], params[1])) return SendInfo(playerid, "Используйте: /frang [id игрока] [ранг]");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_SET_RANG])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetFamilyRang(playerid) <= GetFamilyRang(params[0]) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(p_info[playerid][family_id] != p_info[params[0]][family_id]) return SendError(playerid, "Игрок не состоит в семье.");

    if(!(1 <= params[1] <= GetFamilyRang(playerid)-1))
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "Введите новый ранг для %s от 1 до %d, текущий: %s (%d).",
            get_name(params[0]), GetFamilyRang(playerid)-1, GetNameRangFamily(params[0]), GetFamilyRang(params[0])-1);
        return SendInfo(playerid, STRING_GLOBAL);
    }
    p_info[params[0]][family_rang] = params[1];
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] изменил ранг %s[%d] на %s.", get_name(playerid), playerid, get_name(params[0]), params[0], GetNameRangFamily(params[0]));
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    SetPlayerSkinEx(params[0]);

    Log(LOG_player, INFO, "%s[%d](%s %s) был повышен/понижен %s[%d](%s %s) на %d ранг в %s | #Family",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", FamilyData[family_idx][fName]);

    Log(LOG_player, INFO, "%s[%d](%s %s) повысил/понизил %s[%d](%s %s) на %d ранг в %s | #Family",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC", FamilyData[family_idx][fName]);
    return 1;
}
CMD:ffmute(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid), reason[144];
    if(sscanf(params, "uis[144]", params[0], params[1], reason)) return SendInfo(playerid, "Используйте: /ffmute [id игрока] [кол-во минут] [причина]");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_MUTE])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetFamilyRang(playerid) <= GetFamilyRang(params[0]) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(p_info[playerid][family_id] != p_info[params[0]][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
    if(FamilyData[family_idx][fOwnerID] == p_info[params[0]][ID])
        return SendError(playerid, "Применить данное действие к лидеру нельзя.");
    if(!(1 <= params[1] <= 120)) return SendError(playerid, "Кол-во минут блокировки семейного чата не может быть менее 1 и более 120.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 1);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] выдал блокировку семейного чата %s[%d] на %d %s. Причина: %s", get_name(playerid), playerid, get_name(params[0]), params[0], params[1], Declension_ReturnWord(params[1], "минуту", "минуты", "минут"), reason);
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    p_info[params[0]][family_mute] = params[1] * 60;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s выдал Вам молчанку в семье на %d. Причина: %s", get_name(playerid), Declension_ReturnWord(params[1], "минуту", "минуты", "минут"), reason);
    SendInfo(params[0], STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Вы выдали %s молчанку в семье на %d. Причина: %s", get_name(params[0]), Declension_ReturnWord(params[1], "минуту", "минуты", "минут"), reason);
    SendAccess(playerid, STRING_GLOBAL);
    return 1;
}
CMD:ffunmute(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid), reason[144];
    if(sscanf(params, "us[144]", params[0], reason)) return SendInfo(playerid, "Используйте: /ffunmute [id игрока] [причина]");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_UNMUTE])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetFamilyRang(playerid) <= GetFamilyRang(params[0]) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(p_info[playerid][family_id] != p_info[params[0]][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
    if(FamilyData[family_idx][fOwnerID] == p_info[params[0]][ID])
        return SendError(playerid, "Применить данное действие к лидеру нельзя.");
    if(p_info[params[0]][family_mute] == 0) return SendError(playerid, "У игрока нет блокировки семейного чата.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 1);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] снял блокировку семейного чата %s[%d]. Причина: %s", get_name(playerid), playerid, get_name(params[0]), params[0], reason);
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    p_info[params[0]][family_mute] = 0;

    SendInfo(params[0], "%s снял Вам молчанку в семье. Причина: %s", get_name(playerid), reason);
    SendAccess(playerid, "Вы снял %s молчанку в семье. Причина: %s", get_name(params[0]), reason);
    return 1;
}
CMD:ffwarn(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid), reason[144];
    if(sscanf(params, "us[144]", params[0], reason)) return SendInfo(playerid, "Используйте: /ffwarn [id игрока] [причина]");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_WARN])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetFamilyRang(playerid) <= GetFamilyRang(params[0])  && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(FamilyData[family_idx][fOwnerID] == p_info[params[0]][ID])
        return SendError(playerid, "Применить данное действие к лидеру нельзя.");
    if(p_info[playerid][family_id] != p_info[params[0]][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 1);

    p_info[params[0]][family_warn] += 1;
    if(p_info[params[0]][family_warn] >= 3)
        LeaveFamily(playerid,  params[0], "3 предупреждения");
    else
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] выдал предупреждение %s[%d] (%d из 3). Причина: %s", get_name(playerid), playerid, get_name(params[0]), params[0], p_info[params[0]][family_warn], reason);
        SendFamilyMessage(family_idx, STRING_GLOBAL);
    }

    SendInfo(params[0], "%s выдал Вам предупреждение в семье. Причина: %s", get_name(playerid), reason);
    SendAccess(playerid, "Вы выдали %s предупреждение в семье. Причина: %s", get_name(params[0]), reason);
    return 1;
}
CMD:ffunwarn(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    new family_idx = GetPlayerFamilyID(playerid), reason[144];
    if(sscanf(params, "us[144]", params[0], reason)) return SendInfo(playerid, "Используйте: /ffunwarn [id игрока] [причина]");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_UNWARN])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetFamilyRang(playerid) <= GetFamilyRang(params[0])  && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    if(p_info[playerid][family_id] != p_info[params[0]][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
    if(FamilyData[family_idx][fOwnerID] == p_info[params[0]][ID])
        return SendError(playerid, "Применить данное действие к лидеру нельзя.");
    if(p_info[params[0]][family_warn] <= 0) return SendError(playerid, "У игрока нет предупреждения в семье.");
    if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 1);

    p_info[params[0]][family_warn] -= 1;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] снял предупреждение %s[%d] (%d из 3). Причина: %s", get_name(playerid), playerid, get_name(params[0]), params[0], p_info[params[0]][family_warn], reason);
    SendFamilyMessage(family_idx, STRING_GLOBAL);

    SendInfo(params[0], "%s снял Вам предупреждение в семье. Причина: %s", get_name(playerid), reason);
    SendAccess(playerid, "Вы сняли %s предупреждение в семье. Причина: %s", get_name(params[0]), reason);
    return 1;
}
CMD:k(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    if(!p_info[playerid][p_settings][CHAT_FAMILY]) return SendError(playerid, "У Вас отключен семейный чат.");
    if(strlen(params) < 1 || strlen(params) > 80) return SendError(playerid, "Кол-во символов в сообщении не может быть менее 1 и более 80.");
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    if(p_info[playerid][family_mute] > 0) return SendError(playerid, "У Вас в семье блокировка чата.");
    if(AdvertisingCheck(params)) return AdvertisingPunishment(playerid, params, 1);
    new family_idx = GetPlayerFamilyID(playerid);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s %s[%d]: %s", GetNameRangFamily(playerid), get_name(playerid), playerid, params);
    SendFamilyMessage(family_idx, STRING_GLOBAL, false);
    SetPlayerChatBubble(playerid, "Сказал(-а) что-то в рацию",COLOR_PURPLE,30.0,10000);
    return 1;
}
alias:k("u");
alias:kb("ub");
CMD:kb(playerid, params[])
{
    if(p_info[playerid][family_id] == -1) return SendError(playerid, "Вы не состоите в семье.");
    if(strlen(params) < 1 || strlen(params) > 80) return SendError(playerid, "Кол-во символов в сообщении не может быть менее 1 и более 80.");
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    if(p_info[playerid][family_mute] > 0) return SendError(playerid, "У Вас блокировка чата семье.");
    if(AdvertisingCheck(params)) return AdvertisingPunishment(playerid, params, 1);
    new family_idx = GetPlayerFamilyID(playerid);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "(( %s %s[%d]: %s ))", GetNameRangFamily(playerid), get_name(playerid), playerid, params);
    SendFamilyMessage(family_idx, STRING_GLOBAL, false);
    SetPlayerChatBubble(playerid, "Сказал(-а) что-то в рацию",COLOR_PURPLE,30.0,10000);
    return 1;
}

Destroy_Family(playerid, family_idx)
{
    if(GetPlayerFamilyID(playerid) == family_idx)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] покинул семью по собственному желанию.", get_name(playerid), playerid);
        SendFamilyMessage(family_idx, STRING_GLOBAL);
        SendAccess(playerid, "Вы покинули семью по собственному желанию.");
        SendInfo(playerid, "Семья расформирована.");
    }
    else {

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Администратор %s[%d] удалил семью.", get_name(playerid), playerid);
        SendFamilyMessage(family_idx, STRING_GLOBAL);
    }
    foreach(new i: Player)
    {
        if(p_temp[i][family_game_id] == family_idx)
        {
            p_temp[i][family_game_id] =
            p_info[i][family_id] = -1;
            p_info[i][family_rang] =
            p_info[i][family_exp] =
            p_info[i][family_mute] = 0;
            if(p_info[i][spawn] == SPAWN_FAMILY)
            {
                p_info[i][spawn] = SPAWN_DEFAULT;
                SendInfo(i, "Ваше новое место появления \"Автовокзал\".");
                SendInfo(i, "Изменить место появления: /setspawn");
            }
        }
    }
    DeleteFamilyVehicle(family_idx);

    if(FamilyData[family_idx][fHouseID] != INVALID_HOUSE_ID)
    {
        new h_idx = FamilyData[family_idx][fHouseID];
        h_info[h_idx][h_family_id] = -1;
        FamilyData[family_idx][fHouseID] = INVALID_HOUSE_ID;
        save_house(h_idx);
        update_house(h_idx);
    }

    ClearInventoryItems(FamilyData[family_idx][fOwnerID], INVENTORY_OWNER_TYPE_FAMILY);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `family_id` = -1, `family_rang` = 0, `family_enter` = '-', `spawn` = 0 WHERE `family_id` = %d",
    FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "DELETE FROM `family` WHERE `id` = %d", FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "DELETE FROM `vehicle` WHERE `v_family_id` = %d", FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    strmid (FamilyData[family_idx][fName], "DELETE", 0, strlen("DELETE"), strlen("DELETE")+5);
    FamilyData[family_idx][fOwnerID] = INVALID_MYSQL_ID;
    FamilyData[family_idx][fMysqlID] = -1;
    return 1;
}

cmd:destroyfamily(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(!(3 <= strlen(params) <= 64)) return SendError(playerid, "Название семью должно быть не менее 3 и не более 64 символов.");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `family` WHERE `name` = '%e' LIMIT 1", params);
    mysql_tquery(con_bd, STRING_GLOBAL, "Delete_Family", "d", playerid);
    return 1;
}

CMD:familytags(playerid, params[])
{
    p_info[playerid][p_settings][FAMILY_LABEL] ^= 1;
    ToggleVisibleFamilyLabel(playerid);
    SendAccess(playerid, "Вы %s отображение название семей.", p_info[playerid][p_settings][FAMILY_LABEL] == 0 ? "выключили" : "включили");
    UpdatePlayerSetting(playerid);
    return 1;
}

forward Delete_Family(playerid);
public Delete_Family(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return SendError(playerid, "Ничего не найдено.");
    new fMysqlIDx;
    cache_get_value_name_int(0, "id", fMysqlIDx);

    for(new i = family_count-1; i != -1; i--)
    {
        if(FamilyData[i][fMysqlID] == fMysqlIDx)
        {
            SendAccess(playerid, "Вы удалили семью \"%s\".", FamilyData[i][fName]);
            Destroy_Family(playerid, i);
            break;
        }
    }
    return 1;
}

CMD:vpark(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(vehicleid == INVALID_VEHICLE_ID) return 1;
    if(GetPlayerFamilyID(playerid) == -1 || p_info[playerid][family_id] == -1)
        return SendError(playerid, "Вы не состоите в семье.");
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
        return SendError(playerid, "Вы должны быть за рулем.");

    new family_idx = GetPlayerFamilyID(playerid), fhouse_id = FamilyData[family_idx][fHouseID];
    if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Парковать транспортное средство может только лидер семьи.");
    if(fhouse_id == INVALID_HOUSE_ID) return SendError(playerid, "У семьи нет дома.");

    if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_BOAT || GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_PLANE)
        return SendError(playerid, "На данном Т/С данное действие не возможно.");

    if(veh_info[vehicleid][v_family_id] != GetPlayerFamilyID(playerid))
        return SendError(playerid, "Это транспортное средство не является семейным.");

    if(IsPlayerInRangeOfPoint(playerid, 50.0, h_info[fhouse_id][h_enter][0],h_info[fhouse_id][h_enter][1], h_info[fhouse_id][h_enter][2])
        || GetPlayerVirtualWorld(playerid) == FamilyData[family_idx][fHouseID]+50 || GetPlayerVirtualWorld(playerid) == family_idx)
    {
        SendAccess(playerid, "Вы изменили место парковки транспортного средства.");

        veh_info[vehicleid][v_int] = GetPlayerInterior(playerid);
        veh_info[vehicleid][v_virt] = GetPlayerVirtualWorld(playerid);
        GetVehiclePos(vehicleid, veh_info[vehicleid][v_pos][0], veh_info[vehicleid][v_pos][1], veh_info[vehicleid][v_pos][2]);
        GetVehicleZAngle(vehicleid, veh_info[vehicleid][v_pos][3]);
        SaveVehicle(vehicleid);
    }
    else SendError(playerid, "Вы слишком далеко от семейного дома.");
    return 1;
}
forward list_family_vehicle(playerid, family_idx);
public list_family_vehicle(playerid, family_idx)
{
    new rows, model, status[36], max_count = GetFamilyMaxCountVehicle(family_idx);
    cache_get_row_count(rows);

    STRING_GLOBAL[0] = EOS;
    for(new i; i < rows; i++)
    {
        if(i >= max_count)
        {
            SendError(playerid, "Транспорта больше чем доступных слотов, увеличьте слоты или продайте какой-то.");
            break;
        }
        cache_get_value_int(i, "v_model", model);
        cache_get_value_int(i, "v_mysql_id", p_temp[playerid][p_listitem_cars][i]);

        status = "{"#cLIGHTRED"}(Не используется)";
        for(new j = MAX_FAMILY_VEHICLES-1; j != -1; j--)
        {
            new vehicleid = FamilyData[family_idx][fVehicleID][j];
            if(vehicleid != INVALID_VEHICLE_ID && veh_info[vehicleid][v_mysql_id] == p_temp[playerid][p_listitem_cars][i])
            {
                status = "{"#cGREEN"}(Используется)";
                break;
            }
        }
        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"I"[%d]"W" %s (ID: %d)\t\t%s\n", STRING_GLOBAL, i+1,  GetVehicleName(INVALID_VEHICLE_ID, model), model, status);
    }
    if(rows < max_count)
    {
        for(new i = rows, j = max_count; i < j; i++)
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"I"[%d]"W" Нет\n", STRING_GLOBAL, i+1);
    }
    p_temp[playerid][loadcar_max] = rows;
    ShowPlayerDialog(playerid, D_FAMILY_EDIT_VEHICLE, DIALOG_STYLE_LIST, ""I"Управление транспортом семьи", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
forward load_vehicle_family(playerid);
public load_vehicle_family(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows)
        return SendError(playerid, "Транспортные средства не найдены, обратитесь в тех. раздел.");
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1)
        return SendError(playerid, "Вы не в семьи.");
    new fhouse_id = FamilyData[family_idx][fHouseID];
    if(fhouse_id == INVALID_HOUSE_ID && FamilyData[family_idx][fOffice] != 1)
        return SendError(playerid, "У семьи нет дома или офиса, загрузка не возможна.");

    new temp_v_virt, temp_v_int,
        model_id, Float:vpos[4], vcolor[2],
        max_count = GetFamilyMaxCountVehicle(family_idx);

    new slot_id = -1;
    for(new i; i < max_count; i++)
    {
        if(FamilyData[family_idx][fVehicleID][i] == INVALID_VEHICLE_ID)
        {
            slot_id = i;
            break;
        }
    }
    if(slot_id == -1)
        return SendError(playerid, "Нет свободного слота для загрузки");

    if(FamilyData[family_idx][fVehicleID][slot_id] == INVALID_VEHICLE_ID)
    {
        cache_get_value_name_int(0, "v_model", model_id);
        cache_get_value_name_float(0, "v_pos_0", vpos[0]);
        cache_get_value_name_float(0, "v_pos_1", vpos[1]);
        cache_get_value_name_float(0, "v_pos_2", vpos[2]);
        cache_get_value_name_float(0, "v_pos_3", vpos[3]);
        cache_get_value_name_int(0, "v_color_0", vcolor[0]);
        cache_get_value_name_int(0, "v_color_1", vcolor[1]);

        cache_get_value_name_int(0, "v_virt", temp_v_virt);
        cache_get_value_name_int(0, "v_int", temp_v_int);

        if(temp_v_virt > 0 && fhouse_id+50 != temp_v_virt && family_idx != temp_v_virt)
        {
            new pos_player_id = GetPlayerPositionCity(playerid) - 1,
                Float:restore_pos_veh[][] =
                {
                    {560.2803,  -1285.4069, 16.8732, 0.0},
                    {-1990.1384, 268.1804, 34.9027, 270.0},
                    {2142.4277, 1397.9630, 10.5574, 180.0}
                };

            vpos[0] = restore_pos_veh[pos_player_id][0];
            vpos[1] = restore_pos_veh[pos_player_id][1];
            vpos[2] = restore_pos_veh[pos_player_id][2];
            vpos[3] = restore_pos_veh[pos_player_id][3];

            temp_v_int = 0;
            temp_v_virt = 0;
            SendError(playerid, "Транспортное средство отправлено на ближайшее парковочное место.");
        }
        if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_PLANE && h_info[fhouse_id][h_air_pos][0] != vpos[0])
        {
            if(h_info[fhouse_id][h_air_pos][0] != 0.0 || h_info[fhouse_id][h_air_pos][1] != 0.0)
            {
                vpos[0] = h_info[fhouse_id][h_air_pos][0];
                vpos[1] = h_info[fhouse_id][h_air_pos][1];
                vpos[2] = h_info[fhouse_id][h_air_pos][2];
                vpos[3] = h_info[fhouse_id][h_air_pos][3];
                SendInfo(playerid, "Ваш вертолет был перепаркован возле нового дома.");
            }
            else
            {
                new pos_player_id = GetPlayerPositionCity(playerid) - 1,
                    Float:restore_pos_veh[][] =
                    {
                        {1977.8097,-2257.7625,13.6469, 90.0},
                        {-1366.0973,-177.4680,14.2484, 0.0},
                        {1563.2028,1645.7520,10.9203, 180.0}
                    };
                vpos[0] = restore_pos_veh[pos_player_id][0];
                vpos[1] = restore_pos_veh[pos_player_id][1];
                vpos[2] = restore_pos_veh[pos_player_id][2];
                vpos[3] = restore_pos_veh[pos_player_id][3];
            }
            temp_v_int = 0;
            temp_v_virt = 0;
            SendError(playerid, "Ваш вертолет был отправлен на ближайший аэродром.");
        }
        if(p_info[playerid][cash] < 50) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
        SetPlayerMoney(playerid, -50, true, "доставка т/с семьи");

        FamilyData[family_idx][fVehicleID][slot_id] = CreateVehicleVEx(NPO_FAMILY, NPO_NONE, model_id, vpos[0], vpos[1], vpos[2], vpos[3], vcolor[0], vcolor[1], 450);
        new vehicleid = FamilyData[family_idx][fVehicleID][slot_id];

        veh_info[vehicleid][v_int] = temp_v_int;
        veh_info[vehicleid][v_virt] = temp_v_virt;

        cache_get_value_name_int(0, "v_mysql_id", veh_info[vehicleid][v_mysql_id]);
        cache_get_value_name_int(0, "v_premium", veh_info[vehicleid][v_premium]);
        cache_get_value_name_int(0, "v_owner_id", veh_info[vehicleid][v_owner_id]);

        cache_get_value_name_int(0, "v_lock", veh_info[vehicleid][v_lock]);
        cache_get_value_name_float(0, "v_fuel", veh_info[vehicleid][v_fuel]);
        cache_get_value_name_int(0, "v_twinturbo", veh_info[vehicleid][v_twinturbo]);

        new data[256];
        cache_get_value_name(0, "v_twinturbo_data", data); // 0|0|0|0
        sscanf(data, "p<|>a<i>[4]", veh_info[vehicleid][v_twinturbo_data]);

        cache_get_value_name(0, "v_number", veh_info[vehicleid][v_number], 16);

        if(!strequals(veh_info[vehicleid][v_number], "NULL"))
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%s", veh_info[vehicleid][v_number]);
            veh_info[vehicleid][v_number_text] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_GRAY, vpos[0], vpos[1], vpos[2] + 1.5, 20.0, INVALID_PLAYER_ID, vehicleid);
        } 
        else
            veh_info[vehicleid][v_number_text] = CreateDynamic3DTextLabel("TRANSIT", COLOR_GRAY, vpos[0], vpos[1], vpos[2] + 1.5, 20.0, INVALID_PLAYER_ID, vehicleid);

        cache_get_value_name(0, "v_details", data); // 100.0|100.0|100.0|100.0|100.0
        sscanf(data, "p<|>a<f>[5]", veh_info[vehicleid][v_details]);

        cache_get_value_name_int(0, "v_insurance", veh_info[vehicleid][v_insurance]);
        veh_info[vehicleid][v_family_id] = family_idx;
        cache_get_value_name_int(0, "v_family_rang", veh_info[vehicleid][v_family_rang]);
        if(veh_info[vehicleid][v_family_rang] < 1) veh_info[vehicleid][v_family_rang] = 1;

        ///tuning
        cache_get_value_name_int(0, "v_tun_0", veh_info[vehicleid][v_tune][v_hydraulics]);
        cache_get_value_name_int(0, "v_tun_1", veh_info[vehicleid][v_tune][v_nitro]);
        cache_get_value_name_int(0, "v_tun_2", veh_info[vehicleid][v_tune][v_wheels]);
        cache_get_value_name_int(0, "v_tun_3", veh_info[vehicleid][v_tune][v_front_bumper]);
        cache_get_value_name_int(0, "v_tun_4", veh_info[vehicleid][v_tune][v_pear_bumper]);
        cache_get_value_name_int(0, "v_tun_5", veh_info[vehicleid][v_tune][v_spoiler]);
        cache_get_value_name_int(0, "v_tun_6", veh_info[vehicleid][v_tune][v_paintjob]);
        cache_get_value_name_int(0, "v_tun_7", veh_info[vehicleid][v_tune][v_lamps]);
        cache_get_value_name_int(0, "v_tun_8", veh_info[vehicleid][v_tune][v_exhausts]);
        cache_get_value_name_int(0, "v_tun_9", veh_info[vehicleid][v_tune][v_roofs]);
        cache_get_value_name_int(0, "v_tun_10", veh_info[vehicleid][v_tune][v_hoods]);
        cache_get_value_name_int(0, "v_tun_11", veh_info[vehicleid][v_tune][v_sideskirt]);
        cache_get_value_name_int(0, "v_tun_12", veh_info[vehicleid][v_tune][v_vents]);

        cache_get_value_name(0, "v_attach_data", data); // -1|-1|-1|-1|-1|-1|-1|-1
        sscanf(data, "p<|>a<i>[8]", veh_info[vehicleid][v_attach_data]);

        //visual tuning
        cache_get_value_name_int(0, "v_wheel_width", veh_info[vehicleid][v_wheel_width]);
        cache_get_value_name_float(0, "v_wheel_size", veh_info[vehicleid][v_wheel_size]);
        cache_get_value_name_int(0, "v_wheel_offset_x_0", veh_info[vehicleid][v_wheel_offset_x][0]);
        cache_get_value_name_int(0, "v_wheel_offset_x_1", veh_info[vehicleid][v_wheel_offset_x][1]);
        cache_get_value_name_int(0, "v_wheel_alignment_0", veh_info[vehicleid][v_wheel_alignment][0]);
        cache_get_value_name_int(0, "v_wheel_alignment_1", veh_info[vehicleid][v_wheel_alignment][1]);
        cache_get_value_name_int(0, "v_lights_color_0", veh_info[vehicleid][v_lights_color][0]);
        cache_get_value_name_int(0, "v_lights_color_1", veh_info[vehicleid][v_lights_color][1]);
        cache_get_value_name_int(0, "v_lights_color_2", veh_info[vehicleid][v_lights_color][2]);
        cache_get_value_name_int(0, "v_toner", veh_info[vehicleid][v_toner]);
        if(veh_info[vehicleid][v_wheel_width] != 0) SetVehicleWheelWidth(vehicleid, veh_info[vehicleid][v_wheel_width]);
        if(veh_info[vehicleid][v_wheel_size] != 0.0) SetVehicleWheelSize(vehicleid, veh_info[vehicleid][v_wheel_size]);
        if(veh_info[vehicleid][v_wheel_offset_x][0] != 0) SetVehicleWheelOffsetX(vehicleid, 0, veh_info[vehicleid][v_wheel_offset_x][0]);
        if(veh_info[vehicleid][v_wheel_offset_x][1] != 0) SetVehicleWheelOffsetX(vehicleid, 1, veh_info[vehicleid][v_wheel_offset_x][1]);
        if(veh_info[vehicleid][v_wheel_alignment][0] != 0) SetVehicleWheelAngle(vehicleid, 0, veh_info[vehicleid][v_wheel_alignment][0]);
        if(veh_info[vehicleid][v_wheel_alignment][1] != 0) SetVehicleWheelAngle(vehicleid, 1, veh_info[vehicleid][v_wheel_alignment][1]);
        if(veh_info[vehicleid][v_lights_color][0] != 0 || veh_info[vehicleid][v_lights_color][1] != 0 || veh_info[vehicleid][v_lights_color][2] != 0)
            SetVehicleLightsColors(vehicleid, veh_info[vehicleid][v_lights_color][0], veh_info[vehicleid][v_lights_color][1], veh_info[vehicleid][v_lights_color][2]);

        if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_CAR)
        {
            for (new i; i < v_all-1; i++){
                if(veh_info[vehicleid][v_tune][i] !=0) {
                    VEx_AddVehicleComponent (vehicleid, veh_info[vehicleid][v_tune][i]);
                    if(i == v_sideskirt || i == v_vents) VEx_AddVehicleComponent (vehicleid, veh_info[vehicleid][v_tune][i]);
                }
            }
            if(veh_info[vehicleid][v_tune][v_paintjob] != 0) ChangeVehiclePaintjob(vehicleid, veh_info[vehicleid][v_tune][v_paintjob]-1);
        }
        LoadVehicleAccessories(playerid, vehicleid);

        SendAccess(playerid, "Семейное транспортное средство создано.");
        SendInfo(playerid, "Найти транспортное средство: /ffindcar");
        SendInfo(playerid, "Загрузить или выгрузить транспортное средство: /family");

        LinkVehicleToInterior(vehicleid, veh_info[vehicleid][v_int]);
        SetVehicleVirtualWorld(vehicleid, veh_info[vehicleid][v_virt]);
    }
    return true;
}

DeleteFamilyVehicle(family_idx, vehicleid = INVALID_VEHICLE_ID)
{
    if(vehicleid == INVALID_VEHICLE_ID)
    {
        for(new i = MAX_FAMILY_VEHICLES-1; i != -1; i--)
        {
            vehicleid = FamilyData[family_idx][fVehicleID][i];
            if(vehicleid != INVALID_VEHICLE_ID)
            {
                SaveVehicle(vehicleid);
                SaveVehicleDetails(vehicleid);
                FamilyData[family_idx][fVehicleID][i] = INVALID_VEHICLE_ID;
                veh_info[vehicleid][v_family_id] = -1;
                veh_info[vehicleid][v_family_rang] = 0;
                DestroyVehicleVEx(vehicleid);
            }
        }
    }
    else
    {
        for(new i = MAX_FAMILY_VEHICLES-1; i != -1; i--)
        {
            if(FamilyData[family_idx][fVehicleID][i] == vehicleid)
            {
                SaveVehicle(vehicleid);
                SaveVehicleDetails(vehicleid);
                veh_info[vehicleid][v_family_id] = -1;
                veh_info[vehicleid][v_family_rang] = 0;
                DestroyVehicleVEx(vehicleid);
                FamilyData[family_idx][fVehicleID][i] = INVALID_VEHICLE_ID;
                break;
            }
        }
    }
}

CreateFamilyVehicle(playerid, vehicleid)
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1 || vehicleid == INVALID_VEHICLE_ID) return 1;
    new mysql_id = INVALID_MYSQL_ID;
    for(new i = MAX_FAMILY_VEHICLES-1; i != -1; i-- )
    {
        if(FamilyData[family_idx][fVehicleID][i] == vehicleid)
        {
            mysql_id = veh_info[vehicleid][v_mysql_id];

            SaveVehicle(vehicleid);
            SaveVehicleDetails(vehicleid);
            veh_info[vehicleid][v_family_id] = -1;
            veh_info[vehicleid][v_family_rang] = 0;
            DestroyVehicleVEx(vehicleid);
            FamilyData[family_idx][fVehicleID][i] = INVALID_VEHICLE_ID;
            break;
        }
    }
    if(mysql_id != INVALID_MYSQL_ID)
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `vehicle` WHERE `v_mysql_id` = %d LIMIT 1", mysql_id);
        mysql_tquery(con_bd, STRING_GLOBAL, "load_vehicle_family", "i", playerid);
    }
    return 1;
}

MysqlUpdateFamilyRang(family_idx)
{
    if(family_idx == -1) return 1;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET \
    `rang_0` = '%e', `rang_1` = '%e', `rang_2` = '%e', `rang_3` = '%e', `rang_4` = '%e', `rang_5` = '%e', `rang_6` = '%e', \
    `rang_7` = '%e', `rang_8` = '%e', `rang_9` = '%e' WHERE `id` = %d",
        FAMILY_RANG[family_idx][0], FAMILY_RANG[family_idx][1], FAMILY_RANG[family_idx][2], FAMILY_RANG[family_idx][3], FAMILY_RANG[family_idx][4],
        FAMILY_RANG[family_idx][5], FAMILY_RANG[family_idx][6], FAMILY_RANG[family_idx][7], FAMILY_RANG[family_idx][8], FAMILY_RANG[family_idx][9],
    FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

MysqlUpdateFamilyAccessRang(family_idx)
{
    if(family_idx == -1) return 1;

    STRING_GLOBAL[0] = EOS;
    for(new i; i < F_ALL_COUNT; i++)
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, FamilyData[family_idx][fSettingRang][i], i == F_ALL_COUNT-1 ? "":"|");

    f(STRING_GLOBAL, "UPDATE `family` SET `settings_rangs` = '%s' WHERE `id` = %d", STRING_GLOBAL, FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_FAMILY_RANG; i++)
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, FamilyData[family_idx][fSalaryRang][i], i == MAX_FAMILY_RANG-1 ? "":"|");

    f(STRING_GLOBAL, "UPDATE `family` SET `salary_rangs` = '%s' WHERE `id` = %d", STRING_GLOBAL, FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}


MysqlUpdateFamilySkins(family_idx)
{
    if(family_idx == -1) return 1;

    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_FAMILY_SKINS; i++)
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, FamilyData[family_idx][fSkinID][i], i == MAX_FAMILY_SKINS-1 ? "":"|");
    f(STRING_GLOBAL, "UPDATE `family` SET `skins` = '%s' WHERE `id` = %d", STRING_GLOBAL, FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_FAMILY_RANG; i++)
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, FamilyData[family_idx][fSkinMan][i], i == MAX_FAMILY_RANG-1 ? "":"|");
    f(STRING_GLOBAL, "UPDATE `family` SET `skins_rangs_man` = '%s' WHERE `id` = %d", STRING_GLOBAL, FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_FAMILY_RANG; i++)
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, FamilyData[family_idx][fSkinWoman][i], i == MAX_FAMILY_RANG-1 ? "":"|");
    f(STRING_GLOBAL, "UPDATE `family` SET `skins_rangs_woman` = '%s' WHERE `id` = %d", STRING_GLOBAL, FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

UpdateFamilyLevel(playerid, f_exp = 1)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return 1;
    p_info[playerid][family_exp] += f_exp;
    FamilyData[family_idx][fExp] += f_exp;
    FamilyData[family_idx][fSeasonExp] += f_exp;
    if(FamilyData[family_idx][fExp] >= (FamilyData[family_idx][fLevel]+1)*COUNT_EXP_FAMILY)
    {
        FamilyData[family_idx][fLevel] += 1;
        FamilyData[family_idx][fExp] = 0;
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `family` SET `level` = %d, `exp` = %d, `season_exp` = %d WHERE `id` = %d",
        FamilyData[family_idx][fLevel], FamilyData[family_idx][fExp], FamilyData[family_idx][fSeasonExp], FamilyData[family_idx][fMysqlID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

family_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_FAMILY_CREATE: //by Vip_Uzer
        {
            if(!response) return 1;
            if(family_count >= MAX_FAMILY-1)
                return SendError(playerid, "Количество семей превышает лимиты.");

            STRING_GLOBAL[0] = EOS;
            if(!strlen(inputtext))
            {
                SendError(playerid, "Название семьи должно быть не менее 3 символов и не более 20.");

                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "\
                        "W"Создание семьи стоит: "I"500 Flin Money\n\
                        "W"Всего семей: {FF9900}%d\n\
                        "W"Введите название семьи:\n\n\
                        {AFAFAF}Допустимое значение количества символов от 3 до 20", family_count);

                return ShowPlayerDialog(playerid, D_FAMILY_CREATE, DIALOG_STYLE_INPUT, ""I"Создание семьи", STRING_GLOBAL, "Принять", "Назад");
            }

            if(!(3 <= strlen(inputtext) <= 20))
            {
                SendError(playerid, "Название семьи должно быть не менее 3 символов и не более 20.");

                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "\
                    "W"Создание семьи стоит: "I"500 Flin Money\n\
                    "W"Всего семей: {FF9900}%d\n\
                    "W"Введите название семьи:\n\n\
                    {AFAFAF}Допустимое значение количества символов от 3 до 20", family_count);

                return ShowPlayerDialog(playerid, D_FAMILY_CREATE, DIALOG_STYLE_INPUT, ""I"Создание семьи", STRING_GLOBAL, "Принять", "Назад");
            }
            if(p_info[playerid][flinmoney] < 500)
                return SendError(playerid, "У Вас нет столько Flin Money.");

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `family` WHERE `name` = '%e'", inputtext);
            mysql_tquery(con_bd, STRING_GLOBAL, "Create_Family", "ds", playerid, inputtext);
            return 1;
        }
        case D_FAMILY_MENU:
        {
            if(!response) return 1;
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1)
                return 1;
            switch(listitem)
            {
                case 0:
                {
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name` FROM `accounts` WHERE `id` = %d", FamilyData[family_idx][fOwnerID]);
                    mysql_tquery(con_bd, STRING_GLOBAL, "Family_Info", "ii", playerid, family_idx);
                }
                case 1: callcmd::faminv(playerid);
                case 2: ShowPlayerDialog(playerid, D_FAMILY_SETTINGS, DIALOG_STYLE_LIST, ""I"Настройки", "\
                    "I"[1]"W" Имущество и транспорт семьи\n\
                    "I"[2]"W" Журнал действий\n\
                    "I"[3]"W" Ранги\n\
                    "I"[4]"W" Одежда\n\
                    "I"[5]"W" Черный список\n\
                    "I"[6]"W" Изменить цвет рации (20 семейных монет)\n\
                    "I"[7]"W" Сменить название семьи (100 Flin Money)\n\
                    "I"[8]"W" Отправить оповещение", "Принять", "Назад");
                case 3: ShowDialogFamilyMoney(playerid);
                case 4: ShowPlayerList(playerid, LIST_ID_FAMILY_NOTIFY);
                case 5:
                {
                    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_SET_RANG]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    ShowPlayerList(playerid, LIST_ID_FAMILY_OFFLINE_MEMBERS);
                }
                case 6:
                {
                    new count;
                    STRING_GLOBAL[0] = EOS;
                    STRING_GLOBAL = "[#] Ник\tДолжность\t-\n";
                    foreach(new i: Player)
                    {
                        if(count >= 75)
                        {
                            SendError(playerid, "Выведено первых 75 игроков в сети.");
                            break;
                        }
                        if(p_temp[i][family_game_id] == family_idx)
                        {
                            if(p_info[i][family_mute]) f(STRING_GLOBAL, "%s"I"[%d]"W" %s[%d]\t"I"%s(%d)\t{"#cLIGHTRED"}(Mute: %d)\n",
                                STRING_GLOBAL, count+1, get_name(i), i, GetNameRangFamily(i), p_info[i][family_rang], p_info[i][family_mute]);
                            else f(STRING_GLOBAL, "%s"I"[%d]"W" %s[%d]\t"I"%s(%d)\t-\n",
                                STRING_GLOBAL, count+1, get_name(i), i, GetNameRangFamily(i), p_info[i][family_rang]);
                            p_temp[playerid][p_listitem][count] = i;
                            count++;
                        }
                    }
                    ShowPlayerDialog(playerid, D_FAMILY_MEMBER_ONLINE,DIALOG_STYLE_TABLIST_HEADERS, ""I"Игроки онлайн", STRING_GLOBAL, "Выбрать","Назад");
                }
                case 7: mysql_tquery(con_bd, "SELECT `name`, `level`, `exp`, `season_exp` FROM `family` WHERE `season_exp` > 0 ORDER BY `season_exp` DESC LIMIT 10;", "Family_TOP", "d", playerid);
                case 8:
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, ""W"\
                        Уровень семьи повышается при начислении опыта, он выдается при некоторых действиях:\n\n\
                        — Во время PayDay, если есть VIP;\n\
                        — Во время победы в поединках;\n\
                        — Во время загрузки патронов и материалов в транспортные средства;\n\
                        — Во время разгрузки патронов и материалов из транспортных средств;\n\
                        — Во время обыска (/frisk);\n\
                        — Во время освобождения из тюрьмы (/unkpz);\n\
                        — Во время загрузки наркотиков и медикаментов в транспортные средства;\n\
                        — Во время разгрузки наркотиков и медикаментов из транспортных средств;\n\
                        — Во время снятия розыска (/clear);\n\
                        — Во время выдачи розыска (/su);\n\
                        — Во время ареста (/arrest);\n\
                        — Во время освобождения из тюрьмы (/unarrest);\n\
                        — Во время продажи лицензий на оружие (/sellgunlic);\n\
                        — Во время лечения от наркозависимости (/healaddict);\n\
                        — Во время продажи мед. карты (/givemc);\n\
                        — Во время лечения игрока (/heal);\n\
                        — Во время смены пола (/setsex);\n\
                        — Во время продажи лицензий (/selllic);\n\
                        — Во время изъятия вещей (/take);\n\
                        — Во время выписывания штрафов (/ticket);\n\
                        — На всех первоначальных и основных работах.");
                    ShowPlayerDialog(playerid, D_FAMILY_INFO, DIALOG_STYLE_MSGBOX, ""I"FAQ: {"#cLIGHTRED"}Как повышается уровень семьи?"W"", STRING_GLOBAL, "ОК", "");
                }
                case 9: ShowPlayerDialog(playerid, D_FAMILY_LEAVE, DIALOG_STYLE_MSGBOX, ""I"Покинуть семью", ""W"Внимание! Если Вы являетесь главой семьи - она удалится!\n\nВы действительно хотите покинуть семью?","Да","Нет");
            }
            return 1;
        }
        case D_FAMILY_PROPERTY:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid),
                f_house_id = FamilyData[family_idx][fHouseID],
                f_office = FamilyData[family_idx][fOffice];
            switch(listitem)
            {
                case 0:
                {
                    if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Изменять настройки может только лидер семьи.");
                    if(GetFreeSlotHouse(playerid) == p_info[playerid][house_slots] || p_info[playerid][key_h_rent] != INVALID_HOUSE_ID)
                        return SendError(playerid, "У Вас нет дома.");

                    STRING_GLOBAL[0] = EOS;
                    if(f_house_id == -1) format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
                            ""W"У Вашего семьи "R"нет дома"W"\n\n\
                            "E"Внимание! "W"Прежде чем привязать дом к семьи ознакомьтесь:\n\n\
                            Преимущества семейного дома:\n\
                            "I"- "W"Возможность появления в доме семьи всем ее членам!\n\
                            "I"- "W"Возможность семейного автопарка, количество машин зависит от класса дома!\n\n\
                            "R"P.S. "W"Одновременно проживать в доме семью и подселенцы не могут!\n\
                            Подселенцы будут выселены если они есть!\n\
                            "W"Чтобы сделать Ваш дом семейным, нажмите - "I"'Принять'\n\
                            "W"Цена 'привязки': "I"200 000$ и 40 семейных монет");
                    else{
                        if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID] || f_house_id != GetPlayerHouseID(playerid))
                            return 1;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
                            ""W"У Вашего семьи "A"имеется дом "I"(№%i)"W"\n\n\
                            "R"Внимание! "W"Все Преимущества потеряются, а ресурсы отстануться в доме (кроме машин семьи)\n\
                            Чтобы отвязать дом от семьи, нажмите - "I"\"Принять\"\n\
                            "R"ВАЖНО: Деньги за привязку не возвращаются!", f_house_id);
                    }
                    ShowPlayerDialog(playerid, D_FAMILY_SET_HOUSE, DIALOG_STYLE_MSGBOX, ""I"Управление домом семьи", STRING_GLOBAL, "Принять", "Назад");
                    return 1;
                }
                case 1:
                {
                    if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Изменять настройки может только лидер семьи.");
                    if(FamilyData[family_idx][fLevel] < 10)
                        return SendError(playerid, "Нужен 10 уровень семьи.");
                    if(f_office == 1)
                        return SendError(playerid, "У Вас уже есть офис.");

                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
                        ""W"У Вашей семьи {F04245}нет офиса"W"\n\n\
                        "E"Внимание! "W"Прежде чем привязать офис к семьи ознакомьтесь:\n\n\
                        Преимущества офиса:\n\
                        "I"- "W"Возможность заработка на 'контрактах'!\n\
                        "I"- "W"Появляется офис в бизнес-сити!\n\
                        "I"- "W"Возможность расширения автопарка (+10 автомобилей)!\n\
                        "W"Цена 'привязки': "I"2 000 000$ и 400 семейных монет");

                    ShowPlayerDialog(playerid, D_FAMILY_SET_OFFICE, DIALOG_STYLE_MSGBOX, ""I"Управление офисом семьи", STRING_GLOBAL, "Принять", "Назад");
                    return 1;
                }
            case 2:
                {
                    if(f_house_id == -1 && f_office != 1) return SendError(playerid, "У семьи нет дома или офиса.");
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_model`, `v_mysql_id` FROM `vehicle` WHERE `v_family_id` = %d", FamilyData[family_idx][fMysqlID]);
                    mysql_tquery(con_bd, STRING_GLOBAL, "list_family_vehicle", "ii", playerid, family_idx);
                }
            }
            return 1;
        }
        case D_FAMILY_SETTINGS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            switch(listitem)
            {
                case 0: ShowPlayerDialog(playerid, D_FAMILY_PROPERTY, DIALOG_STYLE_LIST, ""I"Имущество", ""I"[1]"W" Дом [200 000$ и 40 семейных монет]\n"I"[2]"W" Офис [2 000 000$ и 400 семейных монет]\n"I"[3]"W" Автопарк", "Выбор", "Отмена");
                case 1:
                {
                    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_LOG])
                        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    ShowPlayerList(playerid, LIST_ID_FAMILY_LOG);
                }
                case 2:
                {
                    if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Изменять настройки рангов может только лидер семьи.");
                    ShowPlayerDialog(playerid, D_FAMILY_SETTING_RANGS, DIALOG_STYLE_LIST, ""I"Управление рангами семьи", ""I"[1]"W" Сменить название ранга\n"I"[2]"W" Выставить настройки рангов\n"I"[3]"W" Выставить зарплату рангов", "Принять", "Назад");
                }
                case 3:
                {
                    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_SKINS])
                        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    ShowPlayerDialog(playerid, D_FAMILY_SETTING_SKINS, DIALOG_STYLE_LIST, ""I"Управление скинами семьи", ""I"[1]"W" Сменить скин ранга\n"I"[2]"W" Купить скин в магазине одежды\n"I"[3]"W" Отдать свой скин в семью", "Принять", "Назад");
                }
                case 4: callcmd::fblacklist(playerid, "/0");
                case 5:
                {
                    if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Изменять цвет чата может только лидер семьи.");
                    STRING_GLOBAL[0] = EOS;
                    for(new i, j = sizeof FAMILY_DIALOG_COLORS; i < j; i++ )
                        format(STRING_GLOBAL,sizeof(STRING_GLOBAL),"%s{%s}%d. --- [Пример]\n", STRING_GLOBAL, FAMILY_DIALOG_COLORS[i], i+1);
                    ShowPlayerDialog(playerid, D_FAMILY_SET_COLOR, DIALOG_STYLE_LIST, ""I"Цвет чата",STRING_GLOBAL,"Выбрать","Назад");
                }
                case 6:
                {
                    if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Изменять название может только лидер семьи.");
                    if(p_info[playerid][flinmoney] < 100) return SendError(playerid, "У Вас нет столько Flin Money.");
                    ShowPlayerDialog(playerid, D_FAMILY_RENAME,DIALOG_STYLE_INPUT, ""I"Название семьи",""W"Введите новое название семьи:","Далее","Закрыть");
                }
                case 7:
                {
                    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_NOTIFY])
                        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    if(FamilyData[family_idx][fNotifyAntiFlood] > timestamp)
                        return SendError(playerid, "Отправить следующее оповещение можно не раньше чем через: %s", ConvertTime(FamilyData[family_idx][fNotifyAntiFlood]-timestamp));
                    ShowPlayerDialog(playerid, D_FAMILY_SEND_NOTIFY, DIALOG_STYLE_INPUT, ""I"Введите оповещение",""W"Введите оповещение которое хотите разослать участникам семьи:","Далее","Закрыть");
                }
            }
            return 1;
        }
        case D_FAMILY_SEND_NOTIFY:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            if(FamilyData[family_idx][fNotifyAntiFlood] > timestamp)
                        return SendError(playerid, "Отправить следующее оповещение можно не раньше чем через: %s", ConvertTime(FamilyData[family_idx][fNotifyAntiFlood]-timestamp));
            if(!(3 <= strlen(inputtext) <= 60))
                return ShowPlayerDialog(playerid, D_FAMILY_SEND_NOTIFY,DIALOG_STYLE_INPUT, ""I"Введите оповещение", ""W"Введите оповещение которое хотите разослать участникам семьи:","Далее","Закрыть");
            FamilyData[family_idx][fNotifyAntiFlood] = timestamp+3600;

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%s: %s", get_name(playerid), inputtext);
            SendFamilyMessage(family_idx, STRING_GLOBAL, false, true);
            return 1;
        }
        case D_FAMILY_SETTING_SKINS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_SKINS])
                        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
            switch(listitem)
            {
                case 0:
                {
                    STRING_GLOBAL[0] = EOS;
                    for(new i; i < MAX_FAMILY_RANG; i++)
                    f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, FAMILY_RANG[family_idx][i], i+1);
                    ShowPlayerDialog(playerid, D_FAMILY_RANG_LIST_SKINS, DIALOG_STYLE_LIST, ""I"Выберите ранг для смены", STRING_GLOBAL, "Выбрать","Назад");
                }
                case 1:
                {
                    ShowPlayerDialog(playerid, D_FAMILY_SELECT_SEX_SKINS, DIALOG_STYLE_LIST, ""I"Купить скин", ""I"[1]"W" Женский\n"I"[2]"W" Мужской", "Выбрать","Назад");
                    p_temp[playerid][p_listitem_int] = LIST_TD_ID_FAMILY_SELECT_SLOT;
                }
                case 2:
                {
                    ShowPlayerListTD(playerid, LIST_TD_ID_FAMILY_SELECT_SLOT);
                }
            }
            return 1;
        }
        case D_FAMILY_RANG_LIST_SKINS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            SetPVarInt(playerid, "FAMILY_CHANGE_SKIN:rang", listitem);

            ShowPlayerDialog(playerid, D_FAMILY_SELECT_SEX_SKINS, DIALOG_STYLE_LIST, ""I"Сменить скин", ""I"[1]"W" Женский\n"I"[2]"W" Мужской", "Выбрать","Назад");
            p_temp[playerid][p_listitem_int] = LIST_TD_ID_FAMILY_CHANGE_SKIN;
            return 1;
        }
        case D_FAMILY_SELECT_SEX_SKINS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            SetPVarInt(playerid, "FAMILY_CHANGE_SKIN:sex", listitem + 1);
            ShowPlayerListTD(playerid, p_temp[playerid][p_listitem_int]);
            return 1;
        }
        case D_FAMILY_BUY_SKINS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            new item_id = p_temp[playerid][change_skin_idx];
            if(item_id == -1)
                return SendError(playerid, "Неизвестная ошибка: BUG-F005! Попробуйте еще раз.");

            new price_skin = ItemsInfo[item_id][iPrice];
            if(!price_skin)
                return SendError(playerid, "Данный скин не продается в магазине одежды.");

            new slot_idx = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:idx")-1;
            DeletePVar(playerid, "FAMILY_CHANGE_SKIN:idx");
            if(slot_idx == -1)
                return SendError(playerid, "Неизвестная ошибка: BUG-F006! Попробуйте еще раз.");
            if(p_info[playerid][cash] < price_skin)
                return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
            for(new i = MAX_FAMILY_SKINS-1; i != -1; i--)
            {
                if(FamilyData[family_idx][fSkinID][i] == item_id)
                    return SendError(playerid, "Данный скин уже куплен для семьи.");
            }
            FamilyData[family_idx][fSkinID][slot_idx] = item_id;
            SetPlayerMoney(playerid, -price_skin, true, "купил скин (%d) в семью", ItemsInfo[item_id][iModel]);
            MysqlUpdateFamilySkins(family_idx);
            SendAccess(playerid, "Вы купили скин #%d за %d$.", item_id, price_skin);

            p_temp[playerid][p_listitem][0] =
            p_temp[playerid][p_listitem][1] =
            p_temp[playerid][p_listitem][2] =
            p_temp[playerid][p_listitem][3] = -1;
            callcmd::family(playerid, "/0");
            return 1;
        }

        case D_FAMILY_TRANSFER_SKINS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            
            new i = p_temp[playerid][p_listitem_int],
                item_id = InventoryPlayer[playerid][i][inv_item_id];
            if(item_id <= 0)
                return SendError(playerid, "Неизвестная ошибка: BUG-F105! Попробуйте еще раз.");

            if(ItemsInfo[item_id][iType] != TYPE_ITEMS_SKINS)
                return SendError(playerid, "Выбранный предмет не является скином.");

            new slot_idx = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:idx")-1;
            DeletePVar(playerid, "FAMILY_CHANGE_SKIN:idx");
            if(slot_idx == -1)
                return SendError(playerid, "Неизвестная ошибка: BUG-F006! Попробуйте еще раз.");

            new skin_price = 50000, fc_price = 10;
            if(item_id > 311) 
            {
                skin_price *= 10; 
                fc_price *= 5;
            }
            if(p_info[playerid][cash] < skin_price)
                return SendError(playerid, "У Вас нет столько денег. Используйте /donate");

            if(GetInventoryAmount(playerid, 645) < fc_price)
                return SendError(playerid, "У Вас нет столько семейных монет, нужно %d FC.", fc_price);

            if(ItemsInfo[item_id][iModel] == 0 || ItemsInfo[item_id][iModel] == 74)
                return SendError(playerid, "Скин CJ нельзя передать в семью.");

            for(new i = MAX_FAMILY_SKINS-1; i != -1; i--)
            {
                if(FamilyData[family_idx][fSkinID][i] == item_id)
                    return SendError(playerid, "Данный скин уже есть в семьи.");
            }
            DropPlayerEquipment(playerid, i);

            SetPlayerMoney(playerid, -skin_price, true, "передал скин (%d) в семью", ItemsInfo[item_id][iModel]);
            GivePlayerInventory(playerid, 645, -fc_price);

            FamilyData[family_idx][fSkinID][slot_idx] = item_id;
            MysqlUpdateFamilySkins(family_idx);
            SendAccess(playerid, "Вы передали скин %s в семью.", ItemsInfo[item_id][iName]);

            p_temp[playerid][p_listitem][0] =
            p_temp[playerid][p_listitem][1] =
            p_temp[playerid][p_listitem][2] =
            p_temp[playerid][p_listitem][3] = -1;
            callcmd::family(playerid, "/0");
            return 1;
        }

        case D_FAMILY_SET_OFFICE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            if(FamilyData[family_idx][fLevel] < 10)
                return SendError(playerid, "Нужен 10 уровень семьи.");
            if(p_info[playerid][cash] < 2_000_000)
                return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
            if(GetInventoryAmount(playerid, 645) < 400)
                return SendError(playerid, "У Вас нет столько семейных монет.");

            GivePlayerInventory(playerid, 645, -400);
            SetPlayerMoney(playerid, -2_000_000, true, "привязал офис к семье");

            FamilyData[family_idx][fOffice] = 1;
            SendAccess(playerid, "Вы купили офис для семьи.");

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[%s] У семьи теперь есть офис.", FamilyData[family_idx][fName]);
            SendFamilyMessage(family_idx, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `office` = 1 WHERE `id` = %d",  FamilyData[family_idx][fMysqlID]);
            mysql_tquery (con_bd, STRING_GLOBAL);

            UpdateFamilyType(family_idx);
            return 1;
        }
        case D_FAMILY_SETTING_RANGS:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            switch(listitem)
            {
                case 0:
                {
                    STRING_GLOBAL[0] = EOS;
                    for(new i; i < MAX_FAMILY_RANG; i++)
                        f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, FAMILY_RANG[family_idx][i], i+1);
                    ShowPlayerDialog(playerid, D_FAMILY_LIST_RANG,DIALOG_STYLE_LIST, ""I"Выберите ранг для смены", STRING_GLOBAL, "Выбрать","Назад");
                }
                case 1:
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "\
                        "I"[1]"W" Принимать с: "I"%s(%d)\n\
                        "I"[2]"W" Увольнять с: "I"%s(%d)\n\
                        "I"[3]"W" Управление автопарком(продать и тд.): "I"%s(%d)\n\
                        "I"[4]"W" Выдавать бан чата: "I"%s(%d)\n\
                        "I"[5]"W" Снимать бан чата: "I"%s(%d)\n\
                        "I"[6]"W" Выдавать выговор: "I"%s(%d)\n\
                        "I"[7]"W" Снимать выговор: "I"%s(%d)\n\
                        "I"[8]"W" Управление повышениями: "I"%s(%d)\n\
                        "I"[9]"W" Доступ к журналу действий: "I"%s(%d)\n\
                        "I"[10]"W" Управление черным списком: "I"%s(%d)\n\
                        "I"[11]"W" Управление скинами: "I"%s(%d)\n\
                        "I"[12]"W" Управление оповещениями: "I"%s(%d)\n\
                        "I"[13]"W" Доступ к складу: "I"%s(%d)\n\
                        "I"[14]"W" Доступ к /fcapture: "I"%s(%d)",
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_INVITE]-1], FamilyData[family_idx][fSettingRang][F_INVITE],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_UNINVITE]-1], FamilyData[family_idx][fSettingRang][F_UNINVITE],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_VEHICLE]-1], FamilyData[family_idx][fSettingRang][F_VEHICLE],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_MUTE]-1], FamilyData[family_idx][fSettingRang][F_MUTE],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_UNMUTE]-1], FamilyData[family_idx][fSettingRang][F_UNMUTE],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_WARN]-1], FamilyData[family_idx][fSettingRang][F_WARN],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_UNWARN]-1], FamilyData[family_idx][fSettingRang][F_UNWARN],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_SET_RANG]-1], FamilyData[family_idx][fSettingRang][F_SET_RANG],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_LOG]-1], FamilyData[family_idx][fSettingRang][F_LOG],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_BLACKLIST]-1], FamilyData[family_idx][fSettingRang][F_BLACKLIST],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_SKINS]-1], FamilyData[family_idx][fSettingRang][F_SKINS],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_NOTIFY]-1], FamilyData[family_idx][fSettingRang][F_NOTIFY],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_INVENTORY]-1], FamilyData[family_idx][fSettingRang][F_INVENTORY],
                        FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][F_CAPTURE]-1], FamilyData[family_idx][fSettingRang][F_CAPTURE]);
                    ShowPlayerDialog(playerid, D_FAMILY_ACCESS_RANG,DIALOG_STYLE_LIST, ""I"Выберите ранг для смены", STRING_GLOBAL, "Выбрать","Назад");
                }
                case 2:
                {
                    STRING_GLOBAL[0] = EOS;
                    for(new i; i < MAX_FAMILY_RANG; i++)
                        f(STRING_GLOBAL, "%s"I"[%d]"W" Зарплата для ранга "I"%s(%d): %d$\n", STRING_GLOBAL, i+1,
                            FAMILY_RANG[family_idx][i], i+1, FamilyData[family_idx][fSalaryRang][i]);
                    ShowPlayerDialog(playerid, D_FAMILY_LIST_RANG_SALARY,DIALOG_STYLE_LIST, ""I"Выберите ранг для смены", STRING_GLOBAL, "Выбрать","Назад");
                }
            }
            return 1;
        }
        case D_FAMILY_LIST_RANG_SALARY:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(!(0 <= listitem < MAX_FAMILY_RANG)) return callcmd::family(playerid, "/0");
            p_temp[playerid][p_listitem_int] = listitem;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""W"Введите новую зарплату этого ранга, текущая для %s(%d): %d$",
                FAMILY_RANG[family_idx][listitem], listitem+1, FamilyData[family_idx][fSalaryRang][listitem]);
            ShowPlayerDialog(playerid, D_FAMILY_NEW_SALARY_RANK,DIALOG_STYLE_INPUT, ""I"Введите новую зарплату", STRING_GLOBAL, "Выбрать","Назад");
            return 1;
        }
        case D_FAMILY_NEW_SALARY_RANK:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new salary,
                family_idx = GetPlayerFamilyID(playerid),
                idx = p_temp[playerid][p_listitem_int];
            if(sscanf(inputtext, "i", salary))
            {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""W"Введите новую зарплату этого ранга, текущая для %s(%d): %d$",
                    FAMILY_RANG[family_idx][idx], idx+1, FamilyData[family_idx][fSalaryRang][idx]);
                ShowPlayerDialog(playerid, D_FAMILY_NEW_SALARY_RANK,DIALOG_STYLE_INPUT, ""I"Введите новую зарплату", STRING_GLOBAL, "Выбрать","Назад");
                return 1;
            }
            if(!(0 <= salary <= 25_000)) {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""W"Введите новую зарплату этого ранга, текущая для %s(%d): %d$",
                    FAMILY_RANG[family_idx][idx], idx+1, FamilyData[family_idx][fSalaryRang][idx]);
                ShowPlayerDialog(playerid, D_FAMILY_NEW_SALARY_RANK,DIALOG_STYLE_INPUT, ""I"Введите новую зарплату", STRING_GLOBAL, "Выбрать","Назад");
                return 1;
            }
            FamilyData[family_idx][fSalaryRang][idx] = salary;
            MysqlUpdateFamilyAccessRang(family_idx);

            SendAccess(playerid, "Новая зарплата для ранга %s(%d): %d$.", FAMILY_RANG[family_idx][idx], idx+1, FamilyData[family_idx][fSalaryRang][idx]);
            p_temp[playerid][p_listitem_int] = -1;
            return 1;
        }
        case D_FAMILY_ACCESS_RANG:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1)  return 1;
            if(!(0 <= listitem < F_ALL_COUNT)) return 1;
            p_temp[playerid][p_listitem_int] = listitem;
            
            if(!(1 <= FamilyData[family_idx][fSettingRang][listitem] <= 10))
                FamilyData[family_idx][fSettingRang][listitem] = 10;

            SendInfo(playerid,"Выберите новый ранг для доступа к этому разделу от 1 до %d, текущий: %s(%d)", GetFamilyRang(playerid), FAMILY_RANG[family_idx][FamilyData[family_idx][fSettingRang][listitem]-1], FamilyData[family_idx][fSettingRang][listitem]);

            STRING_GLOBAL[0] = EOS;
            for(new i; i < GetFamilyRang(playerid); i++)
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, FAMILY_RANG[family_idx][i], i+1);
            ShowPlayerDialog(playerid, D_FAMILY_NEW_ACCESS_RANG, DIALOG_STYLE_LIST, ""I"Выберите ранг для смены", STRING_GLOBAL, "Выбрать","Назад");
            return 1;
        }
        case D_FAMILY_NEW_ACCESS_RANG:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid), idx = p_temp[playerid][p_listitem_int];
            if(family_idx == -1 || idx == -1) return 1;
            SendAccess(playerid, "Вы изменили настройки.");
            FamilyData[family_idx][fSettingRang][idx] = listitem+1;
            MysqlUpdateFamilyAccessRang(family_idx);
            p_temp[playerid][p_listitem_int] = -1;
            return 1;
        }
        case D_FAMILY_LIST_RANG:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            SetPVarInt(playerid, "FAMILY_CHANGE_SKIN:rang", listitem);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""I"%s", FAMILY_RANG[family_idx][listitem]);
            ShowPlayerDialog(playerid, D_FAMILY_CHANGE_NAME_RANK,DIALOG_STYLE_INPUT, STRING_GLOBAL, ""W"Введите новое название для ранга, от 4 до 16 символов, без цифр и запрещенных знаков:", "Выбрать","Назад");
            return 1;
        }
        case D_FAMILY_CHANGE_NAME_RANK:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            new fix_listitem = GetPVarInt(playerid, "FAMILY_CHANGE_SKIN:rang");
            if(strlen(inputtext) < 4 || strlen(inputtext) > 16)
            {
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, ""I"%s", FAMILY_RANG[family_idx][fix_listitem]);
                ShowPlayerDialog(playerid, D_FAMILY_CHANGE_NAME_RANK,DIALOG_STYLE_INPUT, STRING_GLOBAL, ""W"Введите новое название для ранга, от 4 до 16 символов, без цифр и запрещенных знаков:", "Выбрать","Назад");
                return 1;
            }
            if(IsTextNums(inputtext, _, _))
            {
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, ""I"%s", FAMILY_RANG[family_idx][fix_listitem]);
                ShowPlayerDialog(playerid, D_FAMILY_CHANGE_NAME_RANK,DIALOG_STYLE_INPUT, STRING_GLOBAL, ""W"Введите новое название для ранга, от 4 до 16 символов, без цифр и запрещенных знаков:", "Выбрать","Назад");
                return 1;
            }
            for(new i = strlen(inputtext)-1; i != -1; i--)
            {
                switch(inputtext[i])
                {
                    case 'а'..'я', 'a'..'z', 'А'..'Я', 'A'..'Z', ' ': continue;
                    default: {
                        STRING_GLOBAL[0] = EOS;
                        f(STRING_GLOBAL, ""I"%s", FAMILY_RANG[family_idx][fix_listitem]);
                        ShowPlayerDialog(playerid, D_FAMILY_CHANGE_NAME_RANK,DIALOG_STYLE_INPUT, STRING_GLOBAL, ""W"Введите новое название для ранга, от 4 до 16 символов, без цифр и запрещенных знаков:", "Выбрать","Назад");
                        return 1;
                    }
                }
            }

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] изменил название ранга %s на %s.", get_name(playerid), playerid, FAMILY_RANG[family_idx][fix_listitem], inputtext);
            SendFamilyMessage(family_idx, STRING_GLOBAL);

            strmid(FAMILY_RANG[family_idx][fix_listitem], inputtext, 0, strlen(inputtext), 16);
            MysqlUpdateFamilyRang(family_idx);
            DeletePVar(playerid, "FAMILY_CHANGE_SKIN:rang");
            return 1;
        }
        case D_FAMILY_LEAVE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            if(FamilyData[family_idx][fOwnerID] == p_info[playerid][ID])
                Destroy_Family(playerid, GetPlayerFamilyID(playerid));
            else
            {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] покинул семью по собственному желанию.", get_name(playerid), playerid);
                SendFamilyMessage(family_idx, STRING_GLOBAL);

                SendAccess(playerid, "Вы покинули семью по собственному желанию.");
                FamilyData[family_idx][fMembersCount]--;

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `members_count` = %d WHERE `id` = %d", FamilyData[family_idx][fMembersCount], FamilyData[family_idx][fMysqlID]);
                mysql_tquery(con_bd, STRING_GLOBAL);

                p_info[playerid][family_id] = -1;
                p_temp[playerid][family_game_id] = -1;
                p_info[playerid][family_rang] = 0;
                MysqlUpdatePlayerInt(playerid, "family_enter", EOS);
            }
            UpdateFamilyLabel(playerid, false);
            return 1;
        }
        case D_FAMILY_INFO: return callcmd::family(playerid, "/0");
        case D_FAMILY_SET_COLOR:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Изменить цвет чата может только лидер семьи.");
            if(GetInventoryAmount(playerid, 645) < 20)
                    return SendError(playerid, "У Вас нет столько семейных монет.");
            GivePlayerInventory(playerid, 645, -20);
            //Log(LOG_update, INFO, "Игрок %s [%d] обменял 5 семейных монет на смену цвета чата семьи %s.",
            //    get_name(playerid), p_info[playerid][ID], FamilyData[family_idx][fName]);

            FamilyData[family_idx][fColorID] = listitem;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `color_id` = %d WHERE `id` = %d",
            FamilyData[family_idx][fColorID], FamilyData[family_idx][fMysqlID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] изменил цвет чата семьи.", get_name(playerid), playerid);
            SendFamilyMessage(family_idx, STRING_GLOBAL);

            foreach(new i: Player)
            {
                if(p_temp[i][family_game_id] == family_idx) UpdateFamilyLabel(i, true);
            }
            return 1;
        }
        case D_FAMILY_RENAME:
        {
            if(!response) return 1;
            new family_idx = GetPlayerFamilyID(playerid);
            STRING_GLOBAL[0] = EOS;
            if(!strlen(inputtext))
            {
                SendError(playerid, "Название должно быть не менее 3 и не более 20 символов.");

                format(STRING_GLOBAL, sizeof STRING_GLOBAL, "\
                    "W"Текущее название семьи: {FF9900}%s\n\n\
                    "W"Введите новое название семьи:\n\n\
                    {AFAFAF}Допустимое значение количества символов от 3 до 20",
                    FamilyData[family_idx][fName]);

                return ShowPlayerDialog(playerid, D_FAMILY_RENAME, DIALOG_STYLE_INPUT, ""I"Смена названия семьи", STRING_GLOBAL, "Принять", "Назад");
            }

            if(!(3 <= strlen(inputtext) <= 20))
            {
                SendError(playerid, "Название должно быть не менее 3 и не более 20 символов.");

                format(STRING_GLOBAL, 300, "\
                    "W"Текущее название семьи: {FF9900}%s\n\n\
                    "W"Введите новое название семьи:\n\n\
                    {AFAFAF}Допустимое значение количества символов от 3 до 20",
                    FamilyData[family_idx][fName]);

                return ShowPlayerDialog(playerid, D_FAMILY_RENAME, DIALOG_STYLE_INPUT, ""I"Смена названия семьи", STRING_GLOBAL, "Принять", "Назад");
            }

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `family` WHERE `name` = '%e'",
            inputtext);
            mysql_tquery(con_bd, STRING_GLOBAL, "Rename_Family", "dsd", playerid, inputtext, family_idx);
        }
        case D_FAMILY_SET_HOUSE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(FamilyData[family_idx][fHouseID] == INVALID_HOUSE_ID) HousePlayerList(playerid, HOUSE_ID_FAMILY);
            else
            {
                new f_house_id = FamilyData[family_idx][fHouseID];
                if(f_house_id == INVALID_HOUSE_ID) return SendError(playerid, "Неизвестная ошибка: BUG-F001! Попробуйте еще раз.");
                h_info[f_house_id][h_family_id] = - 1;
                FamilyData[family_idx][fHouseID] = INVALID_HOUSE_ID;
                SendAccess(playerid, "Вы отвязали дом от семьи.");

                save_house(f_house_id);
                update_house(f_house_id);

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `house_id` = -1 WHERE `id` = %d", FamilyData[family_idx][fMysqlID]);
                mysql_tquery (con_bd, STRING_GLOBAL);
                UpdateFamilyType(family_idx);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] отвязал семейный дом (%d)[%d].", get_name(playerid), playerid, f_house_id, h_info[f_house_id][h_mysql_id]);
                SendFamilyMessage(family_idx, STRING_GLOBAL);
            }
            return 1;
        }
        case D_FAMILY_MEMBER_ONLINE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            if(listitem < 0 || listitem > 50) return callcmd::family(playerid, "/0");
            if(!IsPlayerConnected(p_temp[playerid][p_listitem][listitem]) || p_temp[playerid][p_listitem][listitem] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
            p_temp[playerid][p_listitem_int] = p_temp[playerid][p_listitem][listitem];
            ShowPlayerDialog(playerid, D_FAMILY_MEMBER_ONLINE_SET, DIALOG_STYLE_LIST, ""I"Выбор действия",""I"[1]"W" Сменить ранг\n"I"[2]"W" Выгнать из семьи","Выбрать","Назад");
        }
        case D_FAMILY_MEMBER_ONLINE_SET:
        {
            if(!response) {
                callcmd::family(playerid, "/0");
                p_temp[playerid][p_listitem_int] = -1;
                return 1;
            }
            new giveplayerid = p_temp[playerid][p_listitem_int];
            p_temp[playerid][p_listitem_int] = -1;
            if(!IsPlayerConnected(giveplayerid) || giveplayerid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
            new family_idx = GetPlayerFamilyID(playerid);
            switch(listitem)
            {
                case 0:
                {
                    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_SET_RANG]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    if(giveplayerid == playerid) return SendError(playerid, "Вы не можете изменить себе ранг.");
                    if(p_info[playerid][family_id] != p_info[giveplayerid][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
                    if(!IsPlayerConnected(giveplayerid)) return SendError(playerid, "Игрок не найден.");

                    SendInfo(playerid, "Выберите новый ранг для %s от 1 до %d, текущий: %s(%d).", get_name(giveplayerid), GetFamilyRang(playerid)-1, GetNameRangFamily(giveplayerid), GetFamilyRang(giveplayerid));
                    STRING_GLOBAL[0] = EOS;
                    for(new i; i < GetFamilyRang(playerid)-1; i++)
                        f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, FAMILY_RANG[family_idx][i], i+1);
                    ShowPlayerDialog(playerid, D_FAMILY_CHANGE_ACCESS_RANK, DIALOG_STYLE_LIST, ""I"Выберите новый ранг", STRING_GLOBAL, "Выбрать","Назад");

                    p_temp[playerid][p_listitem_int] = giveplayerid;
                }
                case 1:
                {
                    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_UNINVITE])
                        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    if(giveplayerid == playerid) return SendError(playerid, "Вы ввели свой ID.");
                    if(GetFamilyRang(playerid) <= GetFamilyRang(giveplayerid) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID]) return SendError(playerid, "У Вас слишком маленький ранг в семье.");
                    if(FamilyData[family_idx][fOwnerID] == p_info[giveplayerid][ID])
                        return SendError(playerid, "Игрок лидер семьи.");

                    p_temp[playerid][p_listitem_int] = giveplayerid;
                    ShowPlayerDialog(playerid, D_FAMILY_REASON_UNINVITE,DIALOG_STYLE_INPUT, ""I"Причина увольнения", ""I"Введите причину для увольнения:", "Выбрать","Назад");
                }
            }
            return 1;
        }
        case D_FAMILY_REASON_UNINVITE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            if(strlen(inputtext) < 1 || strlen(inputtext) > 16)
                return ShowPlayerDialog(playerid, D_FAMILY_REASON_UNINVITE, DIALOG_STYLE_INPUT, ""I"Причина увольнения", ""I"Введите причину для увольнения:", "Выбрать","Назад");
            LeaveFamily(playerid, p_temp[playerid][p_listitem_int], inputtext);
            p_temp[playerid][p_listitem_int] = -1;
            return 1;
        }
        case D_FAMILY_CHANGE_ACCESS_RANK:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new giveplayerid = p_temp[playerid][p_listitem_int],
                family_idx = GetPlayerFamilyID(playerid);
            if(!IsPlayerConnected(giveplayerid))
                return SendError(playerid, "Игрок не в сети.");
            if(p_info[giveplayerid][family_rang] >= GetFamilyRang(playerid) &&
                p_info[playerid][ID] != FamilyData[family_idx][fOwnerID])
                return SendError(playerid, "У Вас слишком маленький ранг в семье.");
            if(p_info[giveplayerid][ID] == FamilyData[family_idx][fOwnerID])
                return SendError(playerid, "Игрок лидер семьи.");
            if(p_info[playerid][family_id] != p_info[giveplayerid][family_id]) return SendError(playerid, "Игрок не состоит в семье.");
            listitem++;
            if(!(1 <= listitem <= GetFamilyRang(playerid)-1))
                return SendError(playerid, "У вас нет прав на выдачу ранга этого уровня.");
            p_info[giveplayerid][family_rang] = listitem;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] изменил ранг %s[%d] на "I"%s(%d).", get_name(playerid), playerid, get_name(giveplayerid), giveplayerid, GetNameRangFamily(giveplayerid), p_info[giveplayerid][family_rang]);
            SendFamilyMessage(family_idx, STRING_GLOBAL);
            return 1;
        }
        // Управление членами семьи offline
        case D_FAMILY_MEMBER_MENU:
        {
            if(!response) return UpdatePlayerList(playerid);
            new family_idx = GetPlayerFamilyID(playerid), list_id = p_temp[playerid][p_listitem_int];
            if(family_idx == -1)
                return 1;
            if(!(0 <= list_id < 25)) return SendError(playerid, "Неизвестная ошибка: BUG-F002! Попробуйте еще раз.");
            new player_mysql_id = p_temp[playerid][p_listitem][list_id];
            if(player_mysql_id <= INVALID_MYSQL_ID) return SendError(playerid, "Неизвестная ошибка: BUG-F003! Попробуйте еще раз.");
            if(GetPlayerUserID(player_mysql_id) != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");
            switch(listitem)
            {
                case 0:
                {
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `family_enter`, `family_rang`, `family_exp`, `family_warn`, `lastenter` FROM `accounts` WHERE `id` = %d LIMIT 1", player_mysql_id);
                    mysql_tquery(con_bd, STRING_GLOBAL, "FamilyOfflineMemberInfo", "i", playerid);
                }
                case 1:
                {
                    new Cache:result, member_rang_id, member_name[MAX_PLAYER_NAME];
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `family_rang` FROM `accounts` WHERE `id` = %d LIMIT 1", player_mysql_id);
                    result = mysql_query(con_bd, STRING_GLOBAL);
                    if(cache_num_rows() != 0)
                    {
                        cache_get_value_name(0, "name", member_name);
                        cache_get_value_name_int(0, "family_rang", member_rang_id);

                        if(member_rang_id >= GetFamilyRang(playerid))
                            return SendError(playerid, "У Вас слишком маленький ранг в семье.");

                        if(player_mysql_id == FamilyData[family_idx][fOwnerID])
                            return SendError(playerid, "Игрок лидер семьи.");

                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `family_id` = -1, `family_warn` = 0, `family_rang` = -1, `family_enter` = '-' WHERE `id` = %d LIMIT 1", player_mysql_id);
                        mysql_tquery(con_bd, STRING_GLOBAL);

                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] выгнал %s из семьи в оффлайне.", get_name(playerid), playerid, member_name);
                        SendFamilyMessage(family_idx, STRING_GLOBAL);

                        FamilyData[family_idx][fMembersCount]--;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `members_count` = %d WHERE `id` = %d",
                            FamilyData[family_idx][fMembersCount], p_info[playerid][family_id]);
                        mysql_tquery(con_bd, STRING_GLOBAL);

                        UpdatePlayerList(playerid);
                    }
                    else SendError(playerid, "Ничего не найдено.");
                    cache_delete(result);
                }
                case 2:
                {
                    new Cache: result, family_rang_id, member_name[MAX_PLAYER_NAME], family_warns;
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `family_rang`, `family_warn` FROM `accounts` WHERE `id` = %d LIMIT 1", player_mysql_id);
                    result = mysql_query(con_bd, STRING_GLOBAL);
                    if(cache_num_rows() != 0)
                    {
                        cache_get_value_name(0, "name", member_name);
                        cache_get_value_name_int(0, "family_rang", family_rang_id);
                        cache_get_value_name_int(0, "family_warn", family_warns);

                        if(family_rang_id >= GetFamilyRang(playerid) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                            return SendError(playerid, "У Вас слишком маленький ранг в семье.");

                        if(player_mysql_id == FamilyData[family_idx][fOwnerID] &&  FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                            return SendError(playerid, "Игрок лидер семьи.");

                        if(++family_warns >= 3)
                        {
                            STRING_GLOBAL[0] = EOS;
                            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `family_id` = -1, `family_warn` = 0, `family_rang` = -1, `family_enter` = '-' WHERE `id` = %d LIMIT 1", player_mysql_id);
                            mysql_tquery(con_bd, STRING_GLOBAL);

                            STRING_GLOBAL[0] = EOS;
                            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] выгнал %s из семьи в оффлайне за 3 предупреждения.", get_name(playerid), playerid, member_name);
                            SendFamilyMessage(family_idx, STRING_GLOBAL);

                            FamilyData[family_idx][fMembersCount]--;
                            STRING_GLOBAL[0] = EOS;
                            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `members_count` = %d WHERE `id` = %d",
                                FamilyData[family_idx][fMembersCount], p_info[playerid][family_id]);
                            mysql_tquery(con_bd, STRING_GLOBAL);
                        }
                        else
                        {
                            STRING_GLOBAL[0] = EOS;
                            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `family_warn` = %d WHERE `id` = %d LIMIT 1", family_warns, player_mysql_id);
                            mysql_tquery(con_bd, STRING_GLOBAL);

                            STRING_GLOBAL[0] = EOS;
                            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] выдал %s предупреждения в оффлайне.", get_name(playerid), playerid, member_name);
                            SendFamilyMessage(family_idx, STRING_GLOBAL);
                        }

                    }
                    else SendError(playerid, "Ничего не найдено.");
                    cache_delete(result);
                }
                case 3:
                {
                    new Cache: result, family_rang_id, member_name[MAX_PLAYER_NAME];
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `family_rang` FROM `accounts` WHERE `id` = %d LIMIT 1", player_mysql_id);
                    result = mysql_query(con_bd, STRING_GLOBAL);
                    if(cache_num_rows() != 0)
                    {
                        cache_get_value_name(0, "name", member_name);
                        cache_get_value_name_int(0, "family_rang", family_rang_id);

                        if(family_rang_id >= GetFamilyRang(playerid) && FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                            return SendError(playerid, "У Вас слишком маленький ранг в семье.");

                        if(player_mysql_id == FamilyData[family_idx][fOwnerID] &&  FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                            return SendError(playerid, "Игрок лидер семьи.");

                        p_temp[playerid][p_listitem_int] = player_mysql_id;
                        p_temp[playerid][p_listitem][0] = EOS;
                        format(p_temp[playerid][p_listitem], MAX_PLAYER_NAME, "%s", member_name);

                        SendInfo(playerid, "Выберите новый ранг для "I"%s "W"от 1 до %d.", member_name, GetFamilyRang(playerid)-1);
                        STRING_GLOBAL[0] = EOS;
                        for(new i; i < GetFamilyRang(playerid)-1; i++)
                            f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, FAMILY_RANG[family_idx][i], i+1);
                        ShowPlayerDialog(playerid, D_FAMILY_OFF_CHANGE_RANG, DIALOG_STYLE_LIST, ""I"Выберите новый ранг", STRING_GLOBAL, "Выбрать","Назад");
                    }
                    else SendError(playerid, "Ничего не найдено.");
                    cache_delete(result);
                }
            }
        }
        case D_FAMILY_OFF_CHANGE_RANG:
        {
            if(!response) return 1;
            new player_mysql_id = p_temp[playerid][p_listitem_int];
            if(player_mysql_id <= INVALID_MYSQL_ID) return SendError(playerid, "Неизвестная ошибка: BUG-F004! Попробуйте еще раз.");
            if(GetPlayerUserID(player_mysql_id) != INVALID_PLAYER_ID) return SendError(playerid, "Игрок в игре.");
            if(!(1 <= listitem+1 <= GetFamilyRang(playerid)-1)) return 1;

            new family_idx = GetPlayerFamilyID(playerid);
            SendAccess(playerid, "Вы изменили ранг на %s.", FAMILY_RANG[family_idx][listitem]);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `family_rang` = %d WHERE `id` = %d LIMIT 1", listitem+1, player_mysql_id);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] поменял ранг %s на "I"%s(%d) "W"в оффлайне.",
                get_name(playerid), playerid, p_temp[playerid][p_listitem], FAMILY_RANG[family_idx][listitem], listitem+1);
            SendFamilyMessage(family_idx, STRING_GLOBAL);

            UpdatePlayerList(playerid);
            p_temp[playerid][p_listitem_int] = -1;
            return 1;
        }
        case D_FAMILY_MEMBER_INFO:
        {
            ShowPlayerDialog(playerid, D_FAMILY_MEMBER_MENU, DIALOG_STYLE_LIST, ""I"Меню", ""I"[1]"W" Информация об игроке\n"I"[2]"W" Выгнать из семьи\n"I"[3]"W" Выдать предупреждение\n"I"[4]"W" Сменить ранг", "Выбрать", "Назад" );
            return 1;
        }
        case D_FAMILY_EDIT_VEHICLE:
        {
            if(!response) return callcmd::family(playerid, "/0");

            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1)
                return SendError(playerid, "Вы не в семьи.");
            new index_list = p_temp[playerid][p_listitem_cars][listitem],
                fhouse_id = FamilyData[family_idx][fHouseID];
            p_temp[playerid][p_listitem_cars][listitem] = -1;
            if(fhouse_id == INVALID_HOUSE_ID) return SendError(playerid, "У семьи нет дома.");
            new max_count = GetFamilyMaxCountVehicle(family_idx);
            if(listitem >= GetFamilyMaxCountVehicle(family_idx))
                return SendError(playerid, "Доступно всего %d cлотов для одновременной загрузки Т/С.", max_count);
            if(listitem >= p_temp[playerid][loadcar_max])
            {// если слот пустой
                if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
                    return SendError(playerid, "Вы находитесь в транспортном средстве.");

                if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_VEHICLE])
                    return SendError(playerid, "У Вас слишком маленький ранг в семье.");

                /*
                new getLevel[5] = {1, 3, 5, 10, 15,};
                if(FamilyData[family_idx][fLevel] < getLevel[listitem] && SRV_ID != 0)
                    return SendError(playerid, "У семьи должен быть не менее %d уровнень для доступа к этой ячейке Т/С.", getLevel[listitem]);
                */

                ShowPlayerDialog(playerid, D_FAMILY_BUY_VEHICLE, DIALOG_STYLE_LIST, "Добавление транспорта", 
                    ""I"[1]"W" Купить из автосалона\n"I"[2]"W" Выбрать из личного Т/С", "Далее", "Отмена");
            }
            else
            { // если слот не пустой
                new vehicleid;
                p_temp[playerid][family_car_id] = INVALID_VEHICLE_ID;
                for(new i = MAX_FAMILY_VEHICLES-1; i != -1; i--)
                {
                    vehicleid = FamilyData[family_idx][fVehicleID][i];
                    if(vehicleid != INVALID_VEHICLE_ID && index_list == veh_info[vehicleid][v_mysql_id])
                    {
                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""W"Модель машины: "I"%s\n", GetVehicleName(vehicleid));
                        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"W"Цвет машины 1: "I"%d\n", STRING_GLOBAL, veh_info[vehicleid][v_color][0]);
                        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "%s"W"Цвет машины 2: "I"%d\n", STRING_GLOBAL, veh_info[vehicleid][v_color][1]);
                        ShowPlayerDialog(playerid, D_FAMILY_INFO_VEHICLE, DIALOG_STYLE_MSGBOX, ""I"Машина семьи | Информация", STRING_GLOBAL, "Изменить", "Отмена");
                        p_temp[playerid][family_car_id] = vehicleid;
                        return 1;
                    }
                }
                if(p_temp[playerid][family_car_id] == INVALID_VEHICLE_ID)
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `vehicle` WHERE `v_mysql_id` = %d LIMIT 1", index_list);
                    mysql_tquery(con_bd, STRING_GLOBAL, "load_vehicle_family","i", playerid);
                }
            }
            return 1;
        }
        case D_FAMILY_BUY_VEHICLE:
        {
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            if(!response) return callcmd::family(playerid, "/0");
            if(!listitem) ShowPlayerListTD(playerid, LIST_TD_ID_FAMILY_BUY_VEHICLE);
            else ShowPlayerDialog(playerid, D_FAMILY_TRANSFER_VEHICLE_LIST, DIALOG_STYLE_LIST, ""I"Транспорт", ""I"[1]"W" Велик\n"I"[2]"W" Мото\n"I"[3]"W" Автомобиль\n"I"[4]"W" Водный\n"I"[5]"W" Воздушный", "Выбрать", "Отмена");
            return 1;
        }
        case D_FAMILY_TRANSFER_VEHICLE_LIST:
        {
            if(!response) return callcmd::family(playerid, "/0");
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_model`, `v_mysql_id`, `v_twinturbo`, `v_premium`, `v_bonus`, `v_sell_block`, `v_number` FROM `vehicle` WHERE `v_owner_id` = %d",
            p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL, "list_player_vehicle", "iii", playerid, listitem, 1);
        }
        case D_FAMILY_BUY_VEHICLE_ACT:
        {
            new model_id = p_temp[playerid][family_car_select],
                family_idx = GetPlayerFamilyID(playerid),
                max_count = GetFamilyMaxCountVehicle(family_idx);

            p_temp[playerid][family_car_select] = 0;
            p_temp[playerid][p_listitem][30] = -1;
            if(model_id < 400 || family_idx == -1) return 1;
            if(!response) return callcmd::family(playerid, "/0");

            new slot_id = -1;
            for(new i; i < max_count; i++)
            {
                if(FamilyData[family_idx][fVehicleID][i] == INVALID_VEHICLE_ID)
                {
                    slot_id = i;
                    break;
                }
            }
            if(slot_id == -1)
                return SendError(playerid, "Нет свободного слота для покупки.");

            if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return SendError(playerid, "Вы должны быть рядом с домом.");
            new fhouse_id = FamilyData[family_idx][fHouseID];
            if(fhouse_id == INVALID_HOUSE_ID) return SendError(playerid, "У семьи нет дома.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[fhouse_id][h_enter][0],h_info[fhouse_id][h_enter][1], h_info[fhouse_id][h_enter][2]) &&
                !IsPlayerInRangeOfPoint(playerid, 50.0, 1625.9551,2201.6763,1022.0529))
                    return SendError(playerid, "Вы слишком далеко от дома или подземной парковки офиса.");
            if(GetVehicleData(model_id, E_VD_ID) == 508 ||
                (GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_PLANE && (GetVehicleData(model_id, E_VD_ID) != 469 && GetVehicleData(model_id, E_VD_ID) != 487)))
                return SendError(playerid, "Не доступно к покупке.");

            new car_price;
            switch(GetVehicleData(model_id, E_VD_CLASS))
            {
                case VEHICLE_CLASS_UNIQUE: car_price = GetVehicleData(model_id, E_VD_PRICE);
                case VEHICLE_CLASS_REAL_CARS:
                {
                    new custom_id = GetSlotVehicleModelSync(model_id);
                    if(custom_id == -1) return SendError(playerid, "Не известная ошибка: RC0709");
                    car_price = customVehModels[custom_id][ModelPrice];
                }
                default: car_price = GetVehicleData(model_id, E_VD_PRICE);
            }
            if(GetVehicleData(model_id, E_VD_CLASS) != VEHICLE_CLASS_REAL_CARS &&
                p_info[playerid][cash] < car_price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");

            new fc_price;
            if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE)
            {
                fc_price = GetVehicleData(model_id, E_VD_PRICE)/2000;
                if(GetInventoryAmount(playerid, 645) < fc_price)
                    return SendError(playerid, "У Вас нет столько семейных монет, нужно %d FC.", fc_price);
            }

            if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS)
            {
                new custom_id = GetSlotVehicleModelSync(model_id);
                if(custom_id == -1) return SendError(playerid, "Не известная ошибка: RC0709");
                if(p_info[playerid][flinmoney] < car_price)
                    return SendError(playerid, "У Вас нет столько Flin Money.");
            }

            new car_id, color_veh = random(6),
                Float:x, Float:y, Float:z, Float:a;
            switch(GetVehicleData(model_id, E_VD_TYPE))
            {
                case VEHICLE_STATE_BOAT:
                {
                    if(h_info[fhouse_id][h_boat_status] == 0)
                        return SendError(playerid, "У Вашей семьи нет дома с выходом на пирс.");
                    if(GetFamilyLimiteCars(FamilyData[family_idx][fMysqlID], VEHICLE_STATE_BOAT) > 0)
                        return SendError(playerid, "У Вашей семьи уже есть лодка.");
                    new rand = random(sizeof(FT_boat_pos)-1);
                    x = FT_boat_pos[rand][0];
                    y = FT_boat_pos[rand][1];
                    z = FT_boat_pos[rand][2];
                    a = FT_boat_pos[rand][3];
                }
                case VEHICLE_STATE_PLANE:
                {
                    if(fhouse_id == INVALID_HOUSE_ID || (h_info[fhouse_id][h_air_pos][0] == 0.0 && h_info[fhouse_id][h_air_pos][1] == 0.0))
                        return SendError(playerid, "У Вашей семьи нет дома с вертолетной площадкой.");
                    if(GetFamilyLimiteCars(FamilyData[family_idx][fMysqlID], VEHICLE_STATE_PLANE) > 0)
                        return SendError(playerid, "У Вашей семьи уже есть вертолет.");
                    x = h_info[fhouse_id][h_air_pos][0];
                    y = h_info[fhouse_id][h_air_pos][1];
                    z = h_info[fhouse_id][h_air_pos][2];
                    a = h_info[fhouse_id][h_air_pos][3];
                }
                default:
                {
                    GetPlayerPos(playerid, x, y, z);
                    GetPlayerFacingAngle(playerid, a);
                    SendInfo(playerid, "Припарковать транспортное средство: /vpark");
                }
            }

            if(fc_price)
                GivePlayerInventory(playerid, 645, -fc_price);

            car_id = CreateVehicleVEx(NPO_FAMILY, NPO_NONE, model_id, x, y, z, a, color_veh, color_veh, 600);
            FamilyData[family_idx][fVehicleID][slot_id] = car_id;

            if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS)
            {
                p_info[playerid][flinmoney] -= car_price;
                MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

                Log(LOG_player, INFO, "%s[%d](%s %s) приобретение Real Cars транспорта <%s>(%d) за %d FM в семью %s | #Family",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                GetVehicleName(INVALID_VEHICLE_ID, model_id), model_id, car_price, FamilyData[family_idx][fName]);
            }
            else
            {
                SetPlayerMoney(playerid, -car_price, true, "семьи: купил т/с <%s>(%d)", GetVehicleName(INVALID_VEHICLE_ID, model_id), model_id);

                if(GetVehicleData(model_id, E_VD_TYPE) != VEHICLE_STATE_BOAT && GetVehicleData(model_id, E_VD_TYPE) != VEHICLE_STATE_PLANE && GetVehicleData(model_id, E_VD_TYPE) != VEHICLE_STATE_TRAIN)
                {
                    new price;
                    switch(GetVehicleData(model_id, E_VD_CLASS))
                    {
                        case VEHICLE_CLASS_NOPE: price = (car_price/100) * 15; // Цены от 25000$ до 50000$. | Мин. прибыль 12500$. Макс прибыль: 25000$. /
                        case VEHICLE_CLASS_C: price = (car_price/100) * 10; // Цены от 100000$ до 250000$. | Мин. прибыль 25000$. Макс прибыль: 62500$. /
                        case VEHICLE_CLASS_B: price = (car_price/100) * 5; // Цены от 500000$ до 1000000$. | Мин. прибыль 50000$. Макс прибыль: 100000$. /
                        case VEHICLE_CLASS_A: price = (car_price/100) * 3; // Цены от 1500000$ до 2500000$. | Мин. прибыль 75000$. Макс прибыль: 125000$. /
                    }
                    new biz_id = GetBizzIDCarsRoom(GetVehicleData(model_id, E_VD_CLASS)+1);
                    if(biz_id != -1 && b_info[biz_id][_prod] >= price/100)
                    {
                        b_info[biz_id][_prod] -= price/100;
                        b_info[biz_id][_bank] += (price/100) * 90;
                        AddMafiaBank(biz_id, price/10);

                        biz_finka[biz_id] += (price/100) * 90;
                        UpdateIntForFinanceBiz(biz_id, (price/100) * 90);
                    }

                    SetFractionWarehouse(MAYOR_LS, fwMoney, price);
                }
            }

            veh_info[car_id][v_lock] = 1;
            for(new i = 0; i < 5; i++) veh_info[car_id][v_details][i] = 100.0;
            format(veh_info[car_id][v_number], 16, "NULL");
            veh_info[car_id][v_fuel] = GetVehicleData(GetVehicleModelEx(car_id), E_VD_MAX_FUEL);
            veh_info[car_id][v_owner_id] = INVALID_MYSQL_ID;

            veh_info[car_id][v_family_id] = family_idx;
            veh_info[car_id][v_family_rang] = 1;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `vehicle` \
                (`v_owner_id`, `v_model`, `v_pos_0`, `v_pos_1`, `v_pos_2`, `v_pos_3`, `v_lock`, `v_fuel`, `v_color_0`, `v_color_1`, `v_int`, `v_virt`, `v_family_id`, `v_family_rang`) VALUES \
                (%d, %d, %f, %f, %f, %f, %d, %f, %d, %d, %d, %d, %d, %d)",
                veh_info[car_id][v_owner_id], veh_info[car_id][v_model], x, y, z, a, veh_info[car_id][v_lock],
                veh_info[car_id][v_fuel], color_veh, color_veh, veh_info[car_id][v_int],
                veh_info[car_id][v_virt], p_info[playerid][family_id], veh_info[car_id][v_family_rang]);
            mysql_tquery(con_bd, STRING_GLOBAL, "get_vehicle_id", "ii", playerid, car_id);

            if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS) SendAccess(playerid, "Вы приобрели транспортное средство \"%s\" за %d FM.", GetVehicleName(car_id), car_price);
            else if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE) SendAccess(playerid, "Вы приобрели транспортное средство \"%s\" за %d$ и %d FC.", GetVehicleName(car_id), car_price, fc_price);
            else SendAccess(playerid, "Вы приобрели транспортное средство \"%s\" за %d$.", GetVehicleName(car_id), car_price);

            if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_CAR || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_MOTO)
                PutPlayerInVehicle(playerid, car_id, 0);
            return 1;
        }

        case D_FAMILY_TRANSFER_VEHICLE_MENU:
        {
            new vehicle_model = p_temp[playerid][p_listitem][listitem];
            p_temp[playerid][p_listitem][listitem] = -1;
            for(new i; i < p_temp[playerid][loadcar_max]; i++) p_temp[playerid][p_listitem][i] = -1;
            if(!response) return 1;
            if(listitem >= p_temp[playerid][loadcar_max]) return SendError(playerid, "В данном слоте ничего нет.");
            else
            {
                if(listitem == -1) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
                if(p_temp[playerid][p_listitem_cars][listitem] == -1) return ShowPlayerDialog(playerid, D_FAMILY_TRANSFER_VEHICLE_LIST, DIALOG_STYLE_LIST, ""I"Транспорт", ""I"[1]"W" Велик\n"I"[2]"W" Мото\n"I"[3]"W" Автомобиль\n"I"[4]"W" Водный\n"I"[5]"W" Воздушный", "Выбрать", "Отмена");
                new family_idx = GetPlayerFamilyID(playerid);
                if(family_idx == -1) return 1;
                new index_list = p_temp[playerid][p_listitem_cars][listitem],
                    vehicleid = GetPlayerVehicleMySQLID(playerid, index_list, E_PLAYER_VEHICLES_VALUE:E_VEHICLIE_ID);
                p_temp[playerid][p_listitem_cars][listitem] = -1;
                if(vehicleid == -1)
                {
                    new price = GetVehicleData(vehicle_model, E_VD_PRICE)/10, fc_price;
                    if(GetVehicleData(vehicle_model, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE || GetVehicleData(vehicle_model, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS)
                        fc_price = GetVehicleData(vehicle_model, E_VD_PRICE)/100000;
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, ""W"Вы действительно хотите передать личный Т/С в семью "I"%s?\n\n\
                        "W"Название: "I"%s (ID: %d)\n", FamilyData[family_idx][fName], GetVehicleName(INVALID_VEHICLE_ID, vehicle_model), vehicle_model);

                    if(GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_CAR || GetVehicleData(vehicle_model, E_VD_TYPE) == VEHICLE_STATE_MOTO)
                        f(STRING_GLOBAL, "%s"W"Макс. скорость: "I"%d KM/H"W"\nМакс. вместимость бака: "I"%d"W"\n", STRING_GLOBAL, floatround(GetVehicleData(vehicle_model, E_VD_MAX_SPEED)), GetVehicleData(vehicle_model, E_VD_MAX_FUEL));
                    f(STRING_GLOBAL, "%s\n"W"Класс: "I"%s"W"\nТип: "I"%s"W"", STRING_GLOBAL, vehicle_class_name[GetVehicleData(vehicle_model, E_VD_CLASS)], vehicle_type_name[GetVehicleData(vehicle_model, E_VD_TYPE)]);

                    f(STRING_GLOBAL, "%s"W"\n\n{"#cLIGHTRED"}Обратите внимание!"W" Стоимость передачи: "I"%d$ и %d семейных монет"W"\n", STRING_GLOBAL, price, fc_price);
                    ShowPlayerDialog(playerid, D_FAMILY_TRANSFER_VEHICLE_ACT, DIALOG_STYLE_MSGBOX, ""I"Передача Т/С семеье", STRING_GLOBAL, "Далее", "Отмена");
                    SetPVarInt(playerid, "FamilyTransfer:mysql_idx", index_list);
                    return 1;
                }
                if(index_list == veh_info[vehicleid][v_mysql_id])
                {
                    SendError(playerid, "Данное транспортное средство уже загружено.");
                    SendInfo(playerid, "Используйте /cars чтобы выгрузить его с сервера.");
                    return 1;
                }
                
            }
            return 1;
        }
        case D_FAMILY_TRANSFER_VEHICLE_ACT:
        {
            new index_list = GetPVarInt(playerid, "FamilyTransfer:mysql_idx");
            DeletePVar(playerid, "FamilyTransfer:mysql_idx");
            if(!response)
                return callcmd::family(playerid, "/0");

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `vehicle` WHERE `v_mysql_id` = %d AND `v_owner_id` = %d LIMIT 1",
            index_list, p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL, "OnFamilyVehicleTransfer", "i", playerid);
            return 1;
        }
        case D_FAMILY_INFO_VEHICLE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            ShowPlayerDialog(playerid, D_FAMILY_MENU_VEHICLE, DIALOG_STYLE_LIST, ""I"Изменение машин семьи", "\
                "I"[1]"W" Заспавнить т/с\n\
                "I"[2]"W" Найти т/с\n\
                "I"[3]"W" Изменить позицию автомобиля\n\
                "I"[4]"W" Модернизация автомобиля\n\
                "I"[5]"W" Сменить ранг доступа к автомобилю\n\
                "I"[6]"W" Продать т/с (за 50# от гос.цены)\n\
                "I"[7]"W" Выгрузить т/с из сервера", "Выбрать", "Отмена");
            return 1;
        }
        case D_FAMILY_MENU_VEHICLE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_VEHICLE] && listitem != 0) {
                SendError(playerid, "У Вас слишком маленький ранг в семье.");
                callcmd::family(playerid, "/0");
                return 1;
            }

            if(family_idx == -1) return callcmd::family(playerid, "/0");
            new vehicleid = p_temp[playerid][family_car_id];
            if(vehicleid == INVALID_VEHICLE_ID || !IsValidVehicle(vehicleid) ||
                veh_info[vehicleid][v_family_id] == -1) return 1;
            switch(listitem)
            {
                case 0: {
                    if(!IsVehicleOccupied(vehicleid))
                    {
                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] отправил на место парковки \"%s\".", get_name(playerid), playerid, GetVehicleName(vehicleid));
                        SendFamilyMessage(family_idx, STRING_GLOBAL);

                        CreateFamilyVehicle(playerid,vehicleid);
                    }
                    else SendError(playerid, "Транспортное средство используется.");
                }
                case 1:
                {
                    if(IsValidVehicle(vehicleid))
                    {
                        for(new i; i < MAX_PLAYER_VEHICLES; i++)
                        {
                            if(FamilyData[family_idx][fVehicleID][i] == vehicleid)
                            {
                                STRING_GLOBAL[0] = EOS;
                                f(STRING_GLOBAL, "%d", i+1);
                                callcmd::ffindcar(playerid, STRING_GLOBAL);
                                break;
                            }
                        }
                    }
                }
                case 2:
                {
                    if(GetPlayerVehicleID(playerid) != vehicleid)
                        return SendError(playerid, "Вы должны находиться в транспортном средстве.");
                    SendInfo(playerid, "Чтобы припарковать транспортное средство: /vpark");
                }
                case 3: return SendInfo(playerid, "Отправляйтесь в СТО для тюнинга транспортного средства. (/gps)");
                case 4:
                {
                    new fvehrang = veh_info[vehicleid][v_family_rang];
                    if(fvehrang < 1)
                    {
                        fvehrang =
                        veh_info[vehicleid][v_family_rang] = 1;
                    }
                    SendInfo(playerid,"Введите новый ранг для доступа к этому автомобилю от 1 до %d, текущий: %s(%d)",  GetFamilyRang(playerid), FAMILY_RANG[family_idx][fvehrang-1], fvehrang);

                    STRING_GLOBAL[0] = EOS;
                    for(new i; i < GetFamilyRang(playerid); i++)
                        f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, FAMILY_RANG[family_idx][i], i+1);
                    ShowPlayerDialog(playerid, D_FAMILY_NEW_VEHICLE_RANG, DIALOG_STYLE_LIST, ""I"Выберите ранг для смены", STRING_GLOBAL, "Выбрать","Назад");
                    p_temp[playerid][family_car_id] = vehicleid;
                }
                case 5:
                {
                    if(IsValidVehicle(vehicleid))
                    {
                        if(GetPlayerVehicleID(playerid) != vehicleid)
                            return SendError(playerid, "Вы должны находиться в транспортном средстве.");
                        if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                            return SendError(playerid, "Продавать транспорт семьи может только лидер.");
                        new price = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_PRICE)/2;
                        SetPlayerMoney(playerid, price, true, "семьи: продал т/с <%s>(%d)[%d]", GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id]);

                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] продал транспортное средство \"%s\".", get_name(playerid), playerid, GetVehicleName(vehicleid));
                        SendFamilyMessage(family_idx, STRING_GLOBAL);

                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `vehicle` WHERE `v_mysql_id` = %d LIMIT 1", veh_info[vehicleid][v_mysql_id]);
                        mysql_tquery(con_bd, STRING_GLOBAL);

                        ClearInventoryItems(veh_info[vehicleid][v_mysql_id], INVENTORY_OWNER_TYPE_VEHICLE);

                        DestroyVehicleVEx(vehicleid);
                        SendAccess(playerid, "Вы продали транспортное средство.");

                        for(new i; i < MAX_PLAYER_VEHICLES; i++)
                        {
                            if(FamilyData[family_idx][fVehicleID][i] == vehicleid)
                            {
                                FamilyData[family_idx][fVehicleID][i] = INVALID_VEHICLE_ID;
                                break;
                            }
                        }

                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_model`, `v_mysql_id` FROM `vehicle` WHERE `v_family_id` = %d",
                            FamilyData[family_idx][fMysqlID]);
                        mysql_tquery(con_bd, STRING_GLOBAL, "list_family_vehicle", "ii", playerid, family_idx);
                    }
                }
                case 6:
                {
                    SaveVehicle(vehicleid);
                    DestroyVehicleVEx(vehicleid);
                }
            }
            return 1;
        }

        case D_FAMILY_NEW_VEHICLE_RANG:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid),
                vehicleid = p_temp[playerid][family_car_id];
            if(family_idx == -1 || vehicleid == INVALID_VEHICLE_ID) return 1;
            if(!(0 <= listitem < GetFamilyRang(playerid))) return 1;
            SendAccess(playerid, "Вы изменили ранг для транспортного средства.");
            veh_info[vehicleid][v_family_rang] = listitem+1;
            SaveVehicle(vehicleid);
            p_temp[playerid][family_car_id] = INVALID_VEHICLE_ID;
            return 1;
        }
        case D_FAMILY_SPAWN_VEHICLE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            new vehicleid = p_temp[playerid][family_car_id];
            if(vehicleid == INVALID_VEHICLE_ID || !IsValidVehicle(vehicleid) ||
                veh_info[vehicleid][v_family_id] == -1) return 1;
            if(IsVehicleOccupied(vehicleid)) return SendError(playerid, "Транспортное средство используется.");
            SendAccess(playerid, "Транспортное средство отправлено на место парковки.");
            CreateFamilyVehicle(playerid,vehicleid);
            p_temp[playerid][family_car_id] = INVALID_VEHICLE_ID;
            return 1;
        }

        case D_FAMILY_CHANGE_COLOR_VEHICLE:
        {
            if(!response) return callcmd::family(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            new id_color_one, id_color_two;
            if(sscanf(inputtext, "p<,>ii", id_color_one, id_color_two)) return ShowPlayerDialog(playerid, D_FAMILY_CHANGE_COLOR_VEHICLE,DIALOG_STYLE_INPUT,""I"Изменение машин семьи | Цвета",""W"Введите в окошко желаемый цвет автомобиля, через запятую:\nПример: 1,15", "Ввод", "Отмена");
            if( (id_color_one < 0 || id_color_one > 126) || (id_color_two < 0 || id_color_two > 126))
            {
                SendError(playerid, "Цвет может быть не менее 0 и не более 126.");
                return ShowPlayerDialog(playerid, D_FAMILY_CHANGE_COLOR_VEHICLE, DIALOG_STYLE_INPUT, ""I"Изменение машин семьи | Цвета",""W"Введите в окошко желаемый цвет автомобиля, через запятую:\nПример: 1,15", "Ввод", "Отмена");
            }
            new vehicleid = p_temp[playerid][family_car_id];
            if(vehicleid == INVALID_VEHICLE_ID || !IsValidVehicle(vehicleid) ||
                veh_info[vehicleid][v_family_id] == -1) return 1;
            veh_info[vehicleid][v_color][0] = id_color_one;
            veh_info[vehicleid][v_color][1] = id_color_two;
            SendAccess(playerid, "Вы изменили цвет транспортного средства.");
            CreateFamilyVehicle(playerid, vehicleid);
            SaveVehicle(vehicleid);
            p_temp[playerid][family_car_id] = INVALID_VEHICLE_ID;
            return 1;
        }
        case D_FAMILY_GARAGE_AREA:
        {
            if(!response) return 1;
            new vehicleid = GetPlayerVehicleID(playerid);
            if(vehicleid == INVALID_VEHICLE_ID || !IsValidVehicle(vehicleid)) return 1;
            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
            if(IsPlayerInRangeOfPoint(playerid, 3.0, 274.5413,-1584.7179,32.7532))
            {
                new family_idx = GetPlayerFamilyID(playerid);
                if(p_info[playerid][family_id] == -1 ||
                    family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
                if(FamilyData[family_idx][fOffice] != 1) return SendError(playerid, "У Вашей семьи нет офиса.");
                if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) >= VEHICLE_STATE_BOAT) return 1;

                TeleportVehicleToPos(vehicleid, 1625.9551,2201.6763,1022.0529+0.2, 270.0, family_idx, family_idx);
                SetCameraBehindPlayer(playerid);
                return 1;
            }

            if(IsPlayerInRangeOfPoint(playerid, 3.0, 1625.9551,2201.6763,1022.0529))
            {
                if(GetPlayerVirtualWorld(playerid) == p_temp[playerid][parking_id]+5000)
                {
                    new park_id = p_temp[playerid][parking_id];
                    p_temp[playerid][parking_id] = -1;
                    TeleportVehicleToPos(vehicleid, ParkData[park_id][p_enter][0], ParkData[park_id][p_enter][1], ParkData[park_id][p_enter][2]+0.2, ParkData[park_id][p_enter][3], 0, 0);
                }
                else if(GetPlayerVirtualWorld(playerid) == 5500) TeleportVehicleToPos(vehicleid, 1087.2070,-1375.6184,13.5087, 270.0000, 0, 0);
                else TeleportVehicleToPos(vehicleid, 274.5413,-1584.7179,32.753+0.2, 90.0, 0,0);
                SetCameraBehindPlayer(playerid);
                return 1;
            }
            return 1;
        }
        case D_MARKET_AREA_EXIT:
        {
            if(!response) return 1;
            new vehicleid = GetPlayerVehicleID(playerid);
            if(vehicleid == INVALID_VEHICLE_ID || !IsValidVehicle(vehicleid)) return 1;
            if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return 1;
            if(IsPlayerInRangeOfPoint(playerid, 5.0, 1387.1472,-2080.4038,2004.2123))
            {
                if(GetPlayerVirtualWorld(playerid) == 5500) TeleportVehicleToPos(vehicleid, 1087.2070,-1375.6184,13.5087, 270.0000, 0, 0);
                SetCameraBehindPlayer(playerid);
                return 1;
            }
            return 1;
        }
        case D_FAMILY_CONTRACTS_LIST:
        {
            if(!response) return 1;
            if(listitem == MAX_FAMILY_CONTRACTS)
            {
                ShowPlayerDialog(playerid, D_FAMILY_CONTRACTS_INFO, DIALOG_STYLE_MSGBOX, ""I"Что такое Контракты?",
                    ""I"Контракты - "W"это гос. заказы на выполнения\n\
                    разного рода заданий за определенное время\n\n\
                    Так же у вас будет конкуренция, чтобы победить нужно\n\
                    опередить конкурентов и вложиться в отведенное время.", "Понял", "");
            }
            if(listitem < MAX_FAMILY_CONTRACTS)
            {
                if(FamilyContractData[listitem][fID] == CONTRACT_FAMILY_ID_NONE) return ShowFamilyContracts(playerid);
                p_temp[playerid][p_listitem_int] = listitem;
                new id_contr = FamilyContractData[listitem][fID];
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, ""W"Условия контракта:\n"I"%s\n"W"Награда: "I"%d EXP, %d$", CONRACT_FAMILY_INIT[id_contr][fDescription], CONRACT_FAMILY_INIT[id_contr][fExp], CONRACT_FAMILY_INIT[id_contr][fMoney]);
                ShowPlayerDialog(playerid, D_FAMILY_CONTRACTS_DETALS, DIALOG_STYLE_MSGBOX, ""I"Контракты", STRING_GLOBAL, "Рейтинг", "Назад");
            }
            return 1;
        }
        case D_FAMILY_MONEY:
        {
            new fix_listitem,
                family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return 1;
            if(sscanf(inputtext, "i", fix_listitem) || fix_listitem == 0)
                return callcmd::family(playerid, "/0");

            if(!(1 <= fix_listitem <= 999_999_999))
                return ShowDialogFamilyMoney(playerid);

            if(!response)
            {
                if(FamilyData[family_idx][fOwnerID] != p_info[playerid][ID])
                    return SendError(playerid, "Снимать бюджет семьи может только лидер.");
                if(!(1 <= fix_listitem <= FamilyData[family_idx][fMoney]))
                    return ShowDialogFamilyMoney(playerid);
                if(p_info[playerid][p_limite_bank_count] + fix_listitem > 5_000_000) 
                {
                    SendError(playerid, "Кол-во денежных средств превышает лимит.");
                    SendInfo(playerid, "На сегодняшний день для отправки или получения Вам доступно %d$.", 5_000_000-p_info[playerid][p_limite_bank_count]);
                    return 1;
                }
                p_info[playerid][p_limite_bank_count] += fix_listitem;
                MysqlUpdatePlayerInt(playerid, "p_limite_bank_count", p_info[playerid][p_limite_bank_count]);

                FamilyData[family_idx][fMoney] -= fix_listitem;
                SetPlayerMoney(playerid, fix_listitem, true, "снятие с баланса семьи");
                SendAccess(playerid, "Вы сняли %d$ с баланса семьи. Бюджет: %d$.", fix_listitem, FamilyData[family_idx][fMoney]);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] взял с бюджета %d$", get_name(playerid), playerid, fix_listitem);
                SendFamilyMessage(family_idx, STRING_GLOBAL);
            }
            else
            {
                if(!(1 <= fix_listitem <= p_info[playerid][cash]))
                    return ShowDialogFamilyMoney(playerid);
                if(FamilyData[family_idx][fMoney]+fix_listitem >= 50_000_000)
                    return SendError(playerid, "Положить можно только 50 000 000$ в сумме.");

                FamilyData[family_idx][fMoney] += fix_listitem;
                SetPlayerMoney(playerid, -fix_listitem, true, "положил на баланс семьи");
                SendAccess(playerid, "Вы положили %d$ на баланс семьи. Бюджет: %d$.", fix_listitem, FamilyData[family_idx][fMoney]);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] положил в бюджет %d$", get_name(playerid), playerid, fix_listitem);
                SendFamilyMessage(family_idx, STRING_GLOBAL);
            }

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `money` = %d WHERE `id` = %d",
                FamilyData[family_idx][fMoney], FamilyData[family_idx][fMysqlID]);
            mysql_tquery (con_bd, STRING_GLOBAL);
            return 1;
        }
        case D_FAMILY_CONTRACTS_DETALS:
        {
            if(!response) return ShowFamilyContracts(playerid);
            new family_idx = GetPlayerFamilyID(playerid),
                idx = p_temp[playerid][p_listitem_int];
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `contract_progress_%d` FROM `family` WHERE `office` > 0 ORDER BY `office` DESC LIMIT 10;", idx);
            mysql_tquery(con_bd, STRING_GLOBAL, "TOP_Contract_Family", "ddd", playerid, family_idx, idx);
            return 1;
        }
        case D_FAMILY_CONTRACTS_INFO: return ShowFamilyContracts(playerid);
        case D_FAMILY_ENTER:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    SetPlayerPos(playerid, 1865.7856,2221.9958,1032.3591); //внутри
                    SetPlayerFacingAngle(playerid, 270.0);
                    SetPlayerInterior(playerid, GetPlayerFamilyID(playerid));
                    SetPlayerVirtualWorld(playerid, GetPlayerFamilyID(playerid));
                }
                case 1:
                {
                    SetPlayerPos(playerid, 1634.0942,2201.4160,1022.3360); //гараж
                    SetPlayerFacingAngle(playerid, 90.0);
                    SetPlayerInterior(playerid, GetPlayerFamilyID(playerid));
                    SetPlayerVirtualWorld(playerid, GetPlayerFamilyID(playerid));
                }
            }
            return 1;
        }
        case D_FAMILY_EXIT:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    SetPlayerPos(playerid, 292.9750,-1600.8701,32.7800); // двор
                    SetPlayerFacingAngle(playerid, 0.0);
                    SetPlayerInterior(playerid, 0);
                    SetPlayerVirtualWorld(playerid, 0);
                }
                case 1:
                {
                    SetPlayerPos(playerid, 1634.0942,2201.4160,1022.3360); //гараж
                    SetPlayerFacingAngle(playerid, 90.0);
                    SetPlayerInterior(playerid, GetPlayerFamilyID(playerid));
                    SetPlayerVirtualWorld(playerid, GetPlayerFamilyID(playerid));
                }
            }
            return 1;
        }
        case D_FAMILY_GARAGE:
        {
            if(!response) return 1;
            switch(listitem)
            {
                case 0:
                {
                    SetPlayerPos(playerid, 1865.7856,2221.9958,1032.3591); //внутри
                    SetPlayerFacingAngle(playerid, 270.0);
                    SetPlayerInterior(playerid, GetPlayerFamilyID(playerid));
                    SetPlayerVirtualWorld(playerid, GetPlayerFamilyID(playerid));
                }
                case 1:
                {
                    SetPlayerPos(playerid, 292.9750,-1600.8701,32.7800); // двор
                    SetPlayerFacingAngle(playerid, 0.0);
                    SetPlayerInterior(playerid, 0);
                    SetPlayerVirtualWorld(playerid, 0);
                }
            }
            return 1;
        }
        case D_FAMILY_BLACKLIST_MENU:
        {
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
            if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_BLACKLIST])
                return SendError(playerid, "У Вас слишком маленький ранг в семье.");
            if(!response) return 1;
            switch(listitem)
            {
                case 0: ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_ADD, DIALOG_STYLE_INPUT, ""I"Занести в черный список", ""W"Введите ник игрока и причину через запятую:", "Далее", "Отмена");
                case 1: ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_DELETE, DIALOG_STYLE_INPUT, ""I"Вынести из черного списка", ""W"Введите ник игрока:", "Далее", "Отмена");
                case 2: ShowPlayerList(playerid, LIST_ID_FAMILY_BLACKLIST);
            }
            return 1;
        }
        case D_FAMILY_BLACKLIST_ADD:
        {
            if(!response) return callcmd::fblacklist(playerid, "/0");
            new family_idx = GetPlayerFamilyID(playerid);
            if(family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
            if(strlen(inputtext) < 3 || strlen(inputtext) > 56) return ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_ADD, DIALOG_STYLE_INPUT, ""I"Занести в черный список", ""W"Введите ник игрока и причину через запятую:", "Далее", "Отмена"), SendError(playerid, "Причина должна быть не менее 3 и не более 32 символов.");
            new target_name[MAX_PLAYER_NAME], reason[144];
            if(sscanf(inputtext, "p<,>s[24]s[144]", target_name, reason)) return ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_ADD, DIALOG_STYLE_INPUT, ""I"Занести в черный список", ""W"Введите ник игрока и причину через запятую:", "Далее", "Отмена"), SendError(playerid, "Вы ничего не ввели.");
            if(AdvertisingCheck(reason)) return AdvertisingPunishment(playerid, reason, 0);
            if(GetPlayerID(target_name) == INVALID_PLAYER_ID)
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `name` = '%e' LIMIT 1", target_name);
                mysql_tquery(con_bd, STRING_GLOBAL, "Family_BlackListEvent", "ddss", playerid, BLACKLIST_OFFLINE_ADD, target_name, reason);
            }
            else
            {
                new tragetid = GetPlayerID(target_name);
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `family_blacklist` (`id`, `player_id`, `target_id`, `date`, `reason`) VALUES (%d, %d, %d, NOW(), '%s')",
                    p_info[playerid][family_id], p_info[playerid][ID], p_info[tragetid][ID], reason);
                mysql_tquery(con_bd, STRING_GLOBAL);

                SendInfo(tragetid, "%s внес Вас в черный список семьи.", get_name(playerid));
                SendAccess(playerid, "Вы внесли %s в черный список семьи.", get_name(tragetid));

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] внес %s[%d] в черный список. Причина: %s", get_name(playerid), playerid, get_name(tragetid), tragetid, reason);
                SendFamilyMessage(family_idx, STRING_GLOBAL);
            }
        }
        case D_FAMILY_BLACKLIST_DELETE:
        {
            if(!response) return callcmd::blacklist(playerid, "/0");
            new target_name[MAX_PLAYER_NAME];
            if(strlen(inputtext) < 3 || strlen(inputtext) > 24) return ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_DELETE, DIALOG_STYLE_INPUT, ""I"Вынести из черного списка", ""W"Введите ник игрока:", "Далее", "Отмена"), SendError(playerid, "Вы ничего не ввели.");
            if(sscanf(inputtext, "s[24]", target_name)) return ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_DELETE, DIALOG_STYLE_INPUT, ""I"Вынести из черного списка", ""W"Введите ник игрока:", "Далее", "Отмена"), SendError(playerid, "Вы ничего не ввели.");
            new targetid = GetPlayerID(target_name);
            if(targetid == INVALID_PLAYER_ID)
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `name` = '%e' LIMIT 1", target_name);
                mysql_tquery(con_bd, STRING_GLOBAL, "Family_BlackListEvent", "dds", playerid, BLACKLIST_OFFLINE_CLEAR, target_name);
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `family_blacklist` WHERE `target_id` = %d AND `id` = %d", p_info[targetid][ID], p_info[playerid][family_id]);
                mysql_tquery(con_bd, STRING_GLOBAL, "Family_BlackListEvent", "ddsdd", playerid, BLACKLIST_CLEAR, target_name, -1, p_info[targetid][ID]);
            }
        }
    }
    return 1;
}

forward Family_TOP(playerid);
public Family_TOP(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return SendError(playerid, "Ничего не найдено."), callcmd::family(playerid, "/0");

    new f_exp, f_level, f_name[21], f_season_exp;
    STRING_GLOBAL = "[#] Название\tУровень\tСезонные очки\n";
    for(new i; i < rows; i ++)
    {
        cache_get_value_name(i, "name", f_name, 21);
        cache_get_value_name_int(i, "exp", f_exp);
        cache_get_value_name_int(i, "level", f_level);
        cache_get_value_name_int(i, "season_exp", f_season_exp);

        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%d (EXP: %d из %d)\t%d\n", STRING_GLOBAL, i+1, f_name, f_level, f_exp, (f_level+1)*COUNT_EXP_FAMILY, f_season_exp);
    }
    ShowPlayerDialog(playerid, D_FAMILY_INFO, DIALOG_STYLE_TABLIST_HEADERS, ""I"ТОП семей", STRING_GLOBAL, "ОК", "");
    return 1;
}

forward Family_Season();
public Family_Season()
{
    new rows;
    cache_get_row_count(rows);
    if(rows > 0)
    {
        new f_id, owner_family_id,
            prizemoney[3] = {3000000, 2000000, 1000000};
        for(new i; i < rows; i ++)
        {
            cache_get_value_int(i, "id", f_id);
            cache_get_value_int(i, "owner_id", owner_family_id);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `accounts` WHERE `family_id` = %d && `id` != %d", f_id, owner_family_id);
            mysql_tquery(con_bd, STRING_GLOBAL, "Family_GivePrize", "ddd", i, f_id);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `money` = `money` + %d WHERE `id` = %d",
            prizemoney[i], owner_family_id);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "___________ "I"ПОЗДРАВЛЯЕМ ___________\n"W"Ваше семью заняла в сезонном серовнование: "I"%d "W"место.\n\
                За это Вы получаете награду: "I"%d$",
                i+1, prizemoney[i]);
            AddNotify(owner_family_id, STRING_GLOBAL);
        }
    }
    mysql_tquery(con_bd, "UPDATE `family` SET `season_exp` = 0 WHERE 1", "", "");
    return 1;
}

forward Family_GivePrize(f_top, f_id);
public Family_GivePrize(f_top, f_id)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return 1;
    new mysql_user_id,
        prizemoney[3] = {30000, 20000, 10000},
        prizeitems[3] = {2500, 1500, 500},
        prizeheal[3] = {15, 10, 5}; //приз по местам 1/2/3
    for(new i; i < rows; i++)
    {
        cache_get_value_int(i, "id", mysql_user_id);

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `money` = `money` + %d, `inventory_items_1` = `inventory_items_1` + %d, `inventory_items_0` = `inventory_items_0` + %d, `inventory_items_2` = `inventory_items_2` + %d WHERE `id` = %d",
        prizemoney[f_top], prizeitems[f_top], prizeitems[f_top], prizeitems[f_top], prizeheal[f_top], mysql_user_id);
        mysql_tquery(con_bd, STRING_GLOBAL);

        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "___________ "I"ПОЗДРАВЛЯЕМ ___________\n"W"Ваше семью заняла в сезонном серовнование: "I"%d "W"место.\n\
            За это Вы получаете награду: "I"%d$\n"W"Матр./Патр./Нарк.: "I"%d "W"шт.\nАптечки "I"%d",
            f_top+1, prizemoney[f_top], prizeitems[f_top], prizeheal[f_top]);
        AddNotify(mysql_user_id, STRING_GLOBAL);
    }
    return 1;
}
/// log system family

/////////////////////////////////////////////////////
// blacklist family
CMD:fblacklist(playerid, params[])
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return SendError(playerid, "Вы не состоите в семье.");
    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_BLACKLIST])
        return SendError(playerid, "У Вас слишком маленький ранг в семье.");
    ShowPlayerDialog(playerid, D_FAMILY_BLACKLIST_MENU, DIALOG_STYLE_LIST, ""I"Черный список", ""I"[1]"W" Занести в черный список\n"I"[2]"W" Вынести из черного списка\n"I"[3]"W" Посмотреть черный список", "Далее", "Отмена");
    return 1;
}
alias:fblacklist("blacklistfamily", "familyblacklist", "blfamily", "fbl");

forward Family_BlackListEvent(playerid, type, target_nickname[], reason[], clear_mysql_id);
public Family_BlackListEvent(playerid, type, target_nickname[], reason[], clear_mysql_id)
{
    switch(type)
    {
        case BLACKLIST_OFFLINE_ADD:
        {
            if(!cache_num_rows()) return SendError(playerid, "Игрок не найден в базе данных.");
            new target_mysql_id;
            cache_get_value_name_int(0, "id", target_mysql_id);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `family_blacklist` (`id`, `player_id`, `target_id`, `date`, `reason`) VALUES (%d, %d, %d, NOW(), '%s')", p_info[playerid][family_id], p_info[playerid][ID], target_mysql_id, reason);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s внес(-ла) %s в черный список. Причина: %s", get_name(playerid), target_nickname, reason);
            SendFamilyMessage(GetPlayerFamilyID(playerid), STRING_GLOBAL);
        }
        case BLACKLIST_OFFLINE_CLEAR:
        {
            if(!cache_num_rows()) return SendError(playerid, "Игрок не найден в базе данных.");
            new target_mysql_id;
            cache_get_value_name_int(0, "id", target_mysql_id);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `family_blacklist` WHERE `target_id` = %d AND `id` = %d",
                target_mysql_id, p_info[playerid][family_id]);
            mysql_tquery(con_bd, STRING_GLOBAL, "Family_BlackListEvent", "ddsdd", playerid, BLACKLIST_CLEAR, target_nickname, -1, target_mysql_id);
        }
        case BLACKLIST_CLEAR:
        {
            if(!cache_num_rows()) return SendError(playerid, "Игрок не в черном списке.");
            new targetid = GetPlayerID(target_nickname);
            if(targetid != INVALID_PLAYER_ID) SendInfo(targetid, "%s убрал Вас из черного списка.", get_name(playerid));

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `family_blacklist` WHERE `target_id` = %d AND `id` = %d", clear_mysql_id, p_info[playerid][family_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            SendAccess(playerid, "Вы убрали %s из черного списка семьи.", target_nickname);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s[%d] убрал %s [%d] из черного списка семьи.", get_name(playerid), playerid, target_nickname, targetid);
            SendFamilyMessage(GetPlayerFamilyID(playerid), STRING_GLOBAL);
        }
    }
    return 1;
}

/////////////////////////////////////////////
// Family Skin Slots
GetFamilySkinID(sex_id, family_idx, slot_id)
{
    if(family_idx == -1 || !(0 <= slot_id <= MAX_FAMILY_RANG-1)) return INVALID_SKIN_ID;
    new item_id = sex_id == 1 ? FamilyData[family_idx][fSkinWoman][slot_id] : FamilyData[family_idx][fSkinMan][slot_id];
    if(ItemsInfo[item_id][iType] != TYPE_ITEMS_SKINS) return INVALID_SKIN_ID;
    return ItemsInfo[item_id][iModel];
}
/////////////////////////////////////////////
// Family Vehicle
GetFamilyLimiteCars(mysql_id, car_type)
{
    new Cache: result, rows;
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `vehicle` WHERE `v_family_id` = %d", mysql_id);
    result = mysql_query(con_bd, STRING_GLOBAL);
    rows = cache_num_rows();
    new count;
    if(rows)
    {
        new temp_v_model;
        for(new i = rows-1; i != 1; i--)
        {
            cache_get_value_int(i, "v_model", temp_v_model);
            if(GetVehicleData(temp_v_model, E_VD_TYPE) == car_type) count++;
        }
    }
    cache_delete(result);
    return count;
}

GetFamilyOnline(family_ids)
{
    new family_online;
    foreach(new i: Player)
    {
        if(p_temp[i][family_game_id] == family_ids) family_online++;
    }
    return family_online;
}

ShowDialogFamilyMoney(playerid)
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return 1;
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, ""I"Бюджет: "I"%d$\n", FamilyData[family_idx][fMoney]);
    ShowPlayerDialog(playerid, D_FAMILY_MONEY, DIALOG_STYLE_INPUT, STRING_GLOBAL, ""W"Введите количество денег:", "Положить", "Снять");
    return 1;
}


IsAllowedFamilyItem(item_id)
{
    new allowed_items[] = {627, 628, 629, 630, 631, 632, 633, 638, 639, 645, 695, 696, 697, 698, 698};
    for(new i = sizeof(allowed_items)-1; i != -1; i--)
    {
        if(allowed_items[i] == item_id) return 1;
    }
    return 0;
}

forward OnFamilyVehicleTransfer(playerid);
public OnFamilyVehicleTransfer(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return SendError(playerid, "Транспорт не обнаружен.");


    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) 
        return SendError(playerid, "Вы не состоите в семье.");
    new max_count = GetFamilyMaxCountVehicle(family_idx);

    new slot_id = -1;
    for(new i; i < max_count; i++)
    {
        if(FamilyData[family_idx][fVehicleID][i] == INVALID_VEHICLE_ID)
        {
            slot_id = i;
            break;
        }
    }
    if(slot_id == -1)
        return SendError(playerid, "Нет свободного слота для передачи.");

    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0) return SendError(playerid, "Вы должны быть на улице.");
    
    new fhouse_id = FamilyData[family_idx][fHouseID];
    if(fhouse_id == INVALID_HOUSE_ID) return SendError(playerid, "У семьи нет дома.");

    if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[fhouse_id][h_enter][0],h_info[fhouse_id][h_enter][1], h_info[fhouse_id][h_enter][2]) &&
        !IsPlayerInRangeOfPoint(playerid, 50.0, 1625.9551,2201.6763,1022.0529))
        return SendError(playerid, "Вы слишком далеко от дома или подземной парковки офиса.");

    new temp_v_mysql_id, temp_v_premium, temp_v_insurance,
        temp_v_virt, temp_v_int, temp_v_bonus, temp_v_sell_block, temp_v_number[16],
        model_id,
        v_color1,
        v_color2,
        data[256];

    cache_get_value_name_int(0, "v_mysql_id",temp_v_mysql_id);

    if(GetPlayerVehicleMySQLID(playerid, temp_v_mysql_id) != -1) return 1;
    
    cache_get_value_name_int(0, "v_virt", temp_v_virt);
    cache_get_value_name_int(0, "v_int", temp_v_int);

    cache_get_value_name_int(0, "v_model", model_id);
    cache_get_value_name_int(0, "v_color_0", v_color1);
    cache_get_value_name_int(0, "v_color_1", v_color2);
    cache_get_value_name_int(0, "v_premium", temp_v_premium);
    cache_get_value_name_int(0, "v_insurance", temp_v_insurance);
    cache_get_value_name_int(0, "v_bonus", temp_v_bonus);
    cache_get_value_name_int(0, "v_sell_block", temp_v_sell_block);
    cache_get_value_name(0, "v_number", temp_v_number, 16);

    if(temp_v_bonus != 0) 
        return SendError(playerid, "Вы не можете передать семье бонусное транспортное средство.");
    if(temp_v_sell_block != 0)
        return SendError(playerid, "Вы не можете передать семье подарочное транспортное средство.");

    if(GetVehicleData(model_id, E_VD_ID) == 508 ||
        (GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_PLANE && (GetVehicleData(model_id, E_VD_ID) != 469 && GetVehicleData(model_id, E_VD_ID) != 487)))
        return SendError(playerid, "Не доступно к покупке.");

    if(temp_v_insurance == 0 && (GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_VELO_MOPED || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_MOTO || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_CAR))
        return SendError(playerid, "На транспортном средстве должна быть страховка.");
    if(strequals(temp_v_number, "NULL") && (GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_VELO_MOPED || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_MOTO || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_CAR))
        return SendError(playerid, "На транспортном средстве должны быть номера.");

    new car_price = GetVehicleData(model_id, E_VD_PRICE)/10;
    if(p_info[playerid][cash] < car_price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");

    new fc_price; 
    if(GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_UNIQUE || 
        GetVehicleData(model_id, E_VD_CLASS) == VEHICLE_CLASS_REAL_CARS)
    {
        fc_price = GetVehicleData(model_id, E_VD_PRICE)/100000;
        if(GetInventoryAmount(playerid, 645) < fc_price)
            return SendError(playerid, "У Вас нет столько семейных монет, нужно %d FC.", fc_price);
    }
    new Float:x, Float:y, Float:z, Float:a;
    switch(GetVehicleData(model_id, E_VD_TYPE))
    {
        case VEHICLE_STATE_BOAT:
        {
            if(h_info[fhouse_id][h_boat_status] == 0)
                return SendError(playerid, "У Вашей семьи нет дома с выходом на пирс.");
            if(GetFamilyLimiteCars(FamilyData[family_idx][fMysqlID], VEHICLE_STATE_BOAT) > 0)
                return SendError(playerid, "У Вашей семьи уже есть лодка.");
            new rand = random(sizeof(FT_boat_pos)-1);
            x = FT_boat_pos[rand][0];
            y = FT_boat_pos[rand][1];
            z = FT_boat_pos[rand][2];
            a = FT_boat_pos[rand][3];
        }
        case VEHICLE_STATE_PLANE:
        {
            if(fhouse_id == INVALID_HOUSE_ID || (h_info[fhouse_id][h_air_pos][0] == 0.0 && h_info[fhouse_id][h_air_pos][1] == 0.0))
                return SendError(playerid, "У Вашей семьи нет дома с вертолетной площадкой.");
            if(GetFamilyLimiteCars(FamilyData[family_idx][fMysqlID], VEHICLE_STATE_PLANE) > 0)
                return SendError(playerid, "У Вашей семьи уже есть вертолет.");
            x = h_info[fhouse_id][h_air_pos][0];
            y = h_info[fhouse_id][h_air_pos][1];
            z = h_info[fhouse_id][h_air_pos][2];
            a = h_info[fhouse_id][h_air_pos][3];
        }
        default:
        {
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);
            SendInfo(playerid, "Припарковать транспортное средство: /vpark");
        }
    }
    
    SetPlayerMoney(playerid, -car_price, true, "передал семье свой Т/С");
    GivePlayerInventory(playerid, 645, -fc_price);

    new vehicleid = CreateVehicleVEx(NPO_FAMILY, NPO_NONE, model_id, x,y,z, a, v_color1, v_color2, 600);
    FamilyData[family_idx][fVehicleID][slot_id] = vehicleid;

    veh_info[vehicleid][v_virt] = temp_v_virt;
    veh_info[vehicleid][v_int] = temp_v_int;
    veh_info[vehicleid][v_mysql_id] = temp_v_mysql_id;
    veh_info[vehicleid][v_premium] = temp_v_premium;
    veh_info[vehicleid][v_insurance] = temp_v_insurance;
    veh_info[vehicleid][v_bonus] = temp_v_bonus;
    veh_info[vehicleid][v_sell_block] = temp_v_sell_block;

    veh_info[vehicleid][v_owner_id] = INVALID_MYSQL_ID;

    veh_info[vehicleid][v_family_id] = family_idx;
    veh_info[vehicleid][v_family_rang] = 1;

    cache_get_value_name_int(0, "v_lock", veh_info[vehicleid][v_lock]);
    cache_get_value_name_float(0, "v_fuel", veh_info[vehicleid][v_fuel]);
    cache_get_value_name_int(0, "v_twinturbo", veh_info[vehicleid][v_twinturbo]);

    cache_get_value_name(0, "v_twinturbo_data", data); // 0|0|0|0
    sscanf(data, "p<|>a<i>[4]", veh_info[vehicleid][v_twinturbo_data]);

    cache_get_value_name(0, "v_number", veh_info[vehicleid][v_number], 16);

    cache_get_value_name(0, "v_details", data); // 100.0|100.0|100.0|100.0|100.0
    sscanf(data, "p<|>a<f>[5]", veh_info[vehicleid][v_details]);

    cache_get_value_name_int(0, "v_insurance_time", veh_info[vehicleid][v_insurance_time]);
    cache_get_value_name_int(0, "v_wanted", veh_info[vehicleid][v_wanted]);
    cache_get_value_name_int(0, "v_impound", veh_info[vehicleid][v_impound]);

    cache_get_value_name_int(0, "v_tun_0", veh_info[vehicleid][v_tune][v_hydraulics]);
    cache_get_value_name_int(0, "v_tun_1", veh_info[vehicleid][v_tune][v_nitro]);
    cache_get_value_name_int(0, "v_tun_2", veh_info[vehicleid][v_tune][v_wheels]);
    cache_get_value_name_int(0, "v_tun_3", veh_info[vehicleid][v_tune][v_front_bumper]);
    cache_get_value_name_int(0, "v_tun_4", veh_info[vehicleid][v_tune][v_pear_bumper]);
    cache_get_value_name_int(0, "v_tun_5", veh_info[vehicleid][v_tune][v_spoiler]);
    cache_get_value_name_int(0, "v_tun_6", veh_info[vehicleid][v_tune][v_paintjob]);
    cache_get_value_name_int(0, "v_tun_7", veh_info[vehicleid][v_tune][v_lamps]);
    cache_get_value_name_int(0, "v_tun_8", veh_info[vehicleid][v_tune][v_exhausts]);
    cache_get_value_name_int(0, "v_tun_9", veh_info[vehicleid][v_tune][v_roofs]);
    cache_get_value_name_int(0, "v_tun_10", veh_info[vehicleid][v_tune][v_hoods]);
    cache_get_value_name_int(0, "v_tun_11", veh_info[vehicleid][v_tune][v_sideskirt]);
    cache_get_value_name_int(0, "v_tun_12", veh_info[vehicleid][v_tune][v_vents]);

    cache_get_value_name(0, "v_attach_data", data); // -1|-1|-1|-1|-1|-1|-1|-1
    sscanf(data, "p<|>a<i>[8]", veh_info[vehicleid][v_attach_data]);

    cache_get_value_name_int(0, "v_wheel_width", veh_info[vehicleid][v_wheel_width]);
    cache_get_value_name_float(0, "v_wheel_size", veh_info[vehicleid][v_wheel_size]);
    cache_get_value_name_int(0, "v_wheel_offset_x_0", veh_info[vehicleid][v_wheel_offset_x][0]);
    cache_get_value_name_int(0, "v_wheel_offset_x_1", veh_info[vehicleid][v_wheel_offset_x][1]);
    cache_get_value_name_int(0, "v_wheel_alignment_0", veh_info[vehicleid][v_wheel_alignment][0]);
    cache_get_value_name_int(0, "v_wheel_alignment_1", veh_info[vehicleid][v_wheel_alignment][1]);
    cache_get_value_name_int(0, "v_lights_color_0", veh_info[vehicleid][v_lights_color][0]);
    cache_get_value_name_int(0, "v_lights_color_1", veh_info[vehicleid][v_lights_color][1]);
    cache_get_value_name_int(0, "v_lights_color_2", veh_info[vehicleid][v_lights_color][2]);
    cache_get_value_name_int(0, "v_toner", veh_info[vehicleid][v_toner]);
    if(veh_info[vehicleid][v_wheel_width] != 0) SetVehicleWheelWidth(vehicleid, veh_info[vehicleid][v_wheel_width]);
    if(veh_info[vehicleid][v_wheel_size] != 0.0) SetVehicleWheelSize(vehicleid, veh_info[vehicleid][v_wheel_size]);
    if(veh_info[vehicleid][v_wheel_offset_x][0] != 0) SetVehicleWheelOffsetX(vehicleid, 0, veh_info[vehicleid][v_wheel_offset_x][0]);
    if(veh_info[vehicleid][v_wheel_offset_x][1] != 0) SetVehicleWheelOffsetX(vehicleid, 1, veh_info[vehicleid][v_wheel_offset_x][1]);
    if(veh_info[vehicleid][v_wheel_alignment][0] != 0) SetVehicleWheelAngle(vehicleid, 0, veh_info[vehicleid][v_wheel_alignment][0]);
    if(veh_info[vehicleid][v_wheel_alignment][1] != 0) SetVehicleWheelAngle(vehicleid, 1, veh_info[vehicleid][v_wheel_alignment][1]);
    if(veh_info[vehicleid][v_lights_color][0] != 0 || veh_info[vehicleid][v_lights_color][1] != 0 || veh_info[vehicleid][v_lights_color][2] != 0)
        SetVehicleLightsColors(vehicleid, veh_info[vehicleid][v_lights_color][0], veh_info[vehicleid][v_lights_color][1], veh_info[vehicleid][v_lights_color][2]);
    if(veh_info[vehicleid][v_toner] != 0)
        SetVehicleToner(vehicleid, veh_info[vehicleid][v_toner]);

    if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_CAR)
    {
        for (new i; i < v_all-1; i++){
            if(veh_info[vehicleid][v_tune][i] !=0) {
                VEx_AddVehicleComponent (vehicleid, veh_info[vehicleid][v_tune][i]);
                if(i == v_sideskirt || i == v_vents) VEx_AddVehicleComponent (vehicleid, veh_info[vehicleid][v_tune][i]);
            }
        }
        if(veh_info[vehicleid][v_tune][v_paintjob] != 0) ChangeVehiclePaintjob(vehicleid, veh_info[vehicleid][v_tune][v_paintjob]-1);
    }
    veh_info[vehicleid][v_int] =
    veh_info[vehicleid][v_virt] = 0;
    
    LinkVehicleToInterior(vehicleid, 0);
    SetVehicleVirtualWorld(vehicleid, 0);

    veh_info[vehicleid][v_lock] =
    veh_info[vehicleid][v_engine] = 0;
    SetVehicleParamsVEx(vehicleid, veh_info[vehicleid][v_engine], veh_info[vehicleid][v_light], alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);

    if(fc_price) SendAccess(playerid, "Вы передали транспортное средство \"%s\" за %d$ и %d FC.", GetVehicleName(vehicleid), car_price, fc_price);
    else SendAccess(playerid, "Вы передали транспортное средство \"%s\" за %d$.", GetVehicleName(vehicleid), car_price);

    if(GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_CAR || GetVehicleData(model_id, E_VD_TYPE) == VEHICLE_STATE_MOTO)
        PutPlayerInVehicle(playerid, vehicleid, 0);

    LoadVehicleAccessories(playerid, vehicleid);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), 
        "UPDATE `vehicle` SET `v_pos_0` = '%f', `v_pos_1` = '%f', `v_pos_2` = '%f', `v_pos_3` = '%f', \
        `v_int` = %d, `v_virt` = %d, `v_owner_id` = %d, `v_family_id` = %d, `v_family_rang` = %d WHERE `v_mysql_id` = %d",
        x, y, z, a, veh_info[vehicleid][v_int], veh_info[vehicleid][v_virt],
        veh_info[vehicleid][v_owner_id], FamilyData[family_idx][fMysqlID], veh_info[vehicleid][v_family_rang], temp_v_mysql_id);
    mysql_tquery(con_bd, STRING_GLOBAL);

    // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) выставил <%s>(%d)[%d] на авторынке за %d$
    Log(LOG_player, INFO, "%s[%d](%s %s) передал семье <%s> т/с: <%s>(%d)[%d] за %d$ и %d FC",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        FamilyData[family_idx][fName],
        GetVehicleName(vehicleid), model_id, veh_info[vehicleid][v_mysql_id], car_price, fc_price);
    return 1;
}

CMD:famonline(playerid)
{
    STRING_GLOBAL[0] = EOS;
    new family_one, family_two;
    for(new i; i < MAX_CAPTURE_FAMILY_ZONE; i++)
    {
        family_one = fCapture_Info[i][fFamilyID][0];
        family_two = fCapture_Info[i][fFamilyID][1];
        if(family_one != INVALID_FAMILY_ID && family_two != INVALID_FAMILY_ID)
            f(STRING_GLOBAL, "%s"I"[%d] {%06x}%s "W"(Online: %d) VS {%06x}%s "W"(Online: %d)\n", STRING_GLOBAL, i+1, 
                FAMILY_COLORS[FamilyData[family_one][fColorID]], FamilyData[family_one][fName], GetFamilyOnline(family_one),
                FAMILY_COLORS[FamilyData[family_two][fColorID]], FamilyData[family_one][fName], GetFamilyOnline(family_two));
        else
            f(STRING_GLOBAL, "%s"I"[%d]"W" -\n", STRING_GLOBAL, i+1);
    }
    if(!strlen(STRING_GLOBAL)) return SendError(playerid, "Сейчас семьи не участвуют в войне.");
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "Количество онлайна семей:", STRING_GLOBAL, "Окей", "");
    return 1;
}
