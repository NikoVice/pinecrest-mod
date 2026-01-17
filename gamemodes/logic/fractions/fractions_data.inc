/*
    Author: Vip_Uzer
    Flin RolePlay (c) 2021
*/
forward LoadFractionsData();
public LoadFractionsData()
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return printf("Информация о фракциях не найдена.");
    new time = GetTickCount(), data[256];
    for(new i = 0; i < rows; i++)
    {
        cache_get_value_name(i,"name", FractionsData[i][fName]);
        //printf(FractionsData[i][fName]);
        cache_get_value_name_int(i,"type",FractionsData[i][fType]);
        cache_get_value_name_int(i,"category",FractionsData[i][fCategory]);

        cache_get_value_name(i, "spawn_pos", data);
        sscanf(data, "p<|>a<f>[4]", FractionsData[i][fSpawnPos]);

        cache_get_value_name(i, "dressing_pos", data);
        sscanf(data, "p<|>a<f>[3]", FractionsData[i][fDressingPos]);

        cache_get_value_name(i, "warehouse_pos", data);
        sscanf(data, "p<|>a<f>[3]", FractionsData[i][fWarehousePos]);

        cache_get_value_name(i, "base_field", data);
        sscanf(data, "p<|>a<i>[2]", FractionsData[i][fBaseField]);

        cache_get_value_name(i, "unloading_pos", data);
        sscanf(data, "p<|>a<f>[3]", FractionsData[i][fUnloadingPos]);

        cache_get_value_name(i, "unloading_field", data);
        sscanf(data, "p<|>a<i>[2]", FractionsData[i][fUnloadingField]);

        cache_get_value_name(i, "woman_skin", data);
        sscanf(data, "p<|>a<i>[10]", FractionsData[i][fWomanSkin]);

        cache_get_value_name(i, "man_skin", data);
        sscanf(data, "p<|>a<i>[10]", FractionsData[i][fManSkin]);

        cache_get_value_name(i, "pay", data);
        sscanf(data, "p<|>a<i>[10]", FractionsData[i][fPay]);

        cache_get_value_name(i, "rang_name", data);
        //sscanf(data, "p<|>a<s[24]>[10]", FractionsData_NameRang[i]);
        strexplode(FractionsData_NameRang[i], data, "|");

        cache_get_value_name(i, "warehouse", data);
        sscanf(data, "p<|>a<i>[8]", FractionsData[i][fWarehouse]);

        cache_get_value_name(i, "settings", data);
        sscanf(data, "p<|>a<i>[3]", FractionsData[i][fSettings]);

        cache_get_value_name(i, "veh_models_id", data);
        sscanf(data, "p<|>a<i>[15]", FractionsData[i][fVehModelsID]);

        cache_get_value_name(i, "veh_model_max_count", data);
        sscanf(data, "p<|>a<i>[15]", FractionsData[i][fVehModelMaxCount]);

        cache_get_value_name(i, "veh_access_rank", data);
        sscanf(data, "p<|>a<i>[15]", FractionsData[i][fVehAccessRank]);

        cache_get_value_name(i, "veh_spawn_pos", data);
        sscanf(data, "p<|>a<f>[4]", FractionsData[i][fVehSpawnPos]);

        cache_get_value_name(i, "veh_spawn_field", data);
        sscanf(data, "p<|>a<i>[2]", FractionsData[i][fVehSpawnField]);

        if(i > 0) for(new x; x < F_INIT_ALL; x++) FractionInit(i, x);
    }
    for(new bizz_id = totalbizz-1; bizz_id != -1; bizz_id--) update_bizz(bizz_id); //hotfix "Крыша: фракция";
    printf("[Загружено фракций]: <%d>. Потрачено: <%i ms>.", rows, GetTickCount()-time);
    return 1;
}

// Fraction Warehouse
SetFractionWarehouse(fraction_id, type_id, value)
{
    if(type_id == fwMoney)
    {
        if(0 <= FractionsData[fraction_id][fWarehouse][type_id] + value <= 999_999_999)
            FractionsData[fraction_id][fWarehouse][type_id] += value;
    }
    else
    {
        new newvalue = GetFractionWarehouse(fraction_id, type_id) + value;
        if(fraction_id == NATIONAL_GUARD)
        {
            if(type_id == fwPatron && newvalue > 2000000) newvalue = 2000000;
            if(type_id == fwMate && newvalue > 2000000) newvalue = 2000000;
            if(type_id == fwDrugs && newvalue > 50000) newvalue = 50000;
        }
        else
        {
            if(type_id == fwPatron && newvalue > 500000) newvalue = 500000;
            if(type_id == fwMate && newvalue > 500000) newvalue = 500000;
            if(type_id == fwDrugs && newvalue > 50000) newvalue = 50000;
        }
        FractionsData[fraction_id][fWarehouse][type_id] = newvalue;
    }
    SaveFractionWarehouse(fraction_id);
    UpdateInfoFractionWarehouse(fraction_id);
}

SaveFractionWarehouse(fraction_id)
{
    new strFWarehouse[64];
    for(new i; i < F_WAREHOUSE_ALL; i++)
    {
        f(strFWarehouse, "%s%d%s", strFWarehouse, GetFractionWarehouse(fraction_id, i), i == F_WAREHOUSE_ALL-1 ? "":"|");
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `warehouse` = '%s' WHERE `id` = %d", strFWarehouse, fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

UpdateInfoFractionWarehouse(id)
{
    new string_label[512];
    switch(id)
    {
        case POLICE_LS, POLICE_SF, POLICE_LV, FBI_TEAM, POLICE_RC:
        {
            f(string_label,"Склад %s\n\nМатериалы: "W"%d кг."I"\nПатроны: "W"%d шт."I"\nБаланс: "W"%d$",
                GetFractionName(id),GetFractionWarehouse(id, fwMate),GetFractionWarehouse(id, fwPatron), GetFractionWarehouse(id, fwMoney));
        }
        case NATIONAL_GUARD:
        {
            f(string_label,"Склад %s\n\nМатериалы: "W"%d кг."I"\nПатроны: "W"%d шт."I"\nМедикаменты: "W"%d шт."I"\nБаланс: "W"%d$",
                GetFractionName(id),GetFractionWarehouse(id, fwMate),GetFractionWarehouse(id, fwPatron), GetFractionWarehouse(id, fwDrugs), GetFractionWarehouse(id, fwMoney));
        }
        case RADIO_LS, RADIO_SF, RADIO_LV:
        {
            f(string_label,"Склад %s\n\nБаланс: "W"%d$",
                GetFractionName(id), GetFractionWarehouse(id, fwMoney));
        }
        case MAFIA_RM..MAFIA_YAKUDZA, BIKER, MAFIA_IRAN:
        {
            f(string_label,"Склад %s\n\nБизнесов: "I"%d шт."I"\n\nМатериалы: "W"%d кг."I"\nПатроны: "W"%d шт."I"\nНаркотики: "W"%d гр."I"\nБаланс: "W"%d$."I"\nКанистры: "W"%d шт."I"\nРем. комплекты: "W"%d шт."I"\nАптечки: "W"%d шт."I"\nМаски: "W"%d шт."I"\n\nСтатус: "W"%s",
            GetFractionName(id), GetMafiaCountBizz(id), GetFractionWarehouse(id, fwMate),GetFractionWarehouse(id, fwPatron), GetFractionWarehouse(id, fwDrugs), GetFractionWarehouse(id, fwMoney), GetFractionWarehouse(id, fwFuel), GetFractionWarehouse(id, fwRemp), GetFractionWarehouse(id, fwHeal), GetFractionWarehouse(id, fwMask), GetFractionSettings(id, fWareHouseStatus) ? ("{008000}Открыт"):("{FF0000}Закрыт"));
        }
        case GROOVE..VAGOS:
        {
            f(string_label,"Склад %s\n\nГраффити: "W"%d шт."I"\nТерриторий: "W"%d шт."I"\n\nМатериалы: "W"%d кг."I"\nПатроны: "W"%d шт."I"\nНаркотики: "W"%d гр."I"\nБаланс: "W"%d$."I"\nКанистры: "W"%d шт."I"\nРем. комплекты: "W"%d шт."I"\nАптечки: "W"%d шт."I"\nМаски: "W"%d шт."I"\n\nСтатус: "W"%s",
            GetFractionName(id), GetGangGraffiti(id), GetGangTerritory(id), GetFractionWarehouse(id, fwMate), GetFractionWarehouse(id, fwPatron), GetFractionWarehouse(id, fwDrugs), GetFractionWarehouse(id, fwMoney), GetFractionWarehouse(id, fwFuel), GetFractionWarehouse(id, fwRemp), GetFractionWarehouse(id, fwHeal), GetFractionWarehouse(id, fwMask), GetFractionSettings(id, fWareHouseStatus) ? ("{008000}Открыт"):("{FF0000}Закрыт"));
        }
        case MEDIC_LS, MEDIC_SF, MEDIC_LV:
        {
            f(string_label,"Склад %s\n\nМедикаменты: "W"%d шт."I"\nБаланс: "W"%d$.",
                GetFractionName(id),GetFractionWarehouse(id, fwDrugs), GetFractionWarehouse(id, fwMoney));
        }
        case MAYOR_LS:
        {
            f(string_label,"%s\n\nКазна: "W"%d$."I"\n\nМатериалы: "W"%d кг."I"\nПатроны: "W"%d шт.",
                GetFractionName(id), GetFractionWarehouse(id, fwMoney), GetFractionWarehouse(id, fwMate),GetFractionWarehouse(id, fwPatron));
        }
        case PRISON:
        {
            f(string_label,"Склад %s\n\nМатериалы: "W"%d кг."I"\nПатроны: "W"%d шт.", GetFractionName(id), GetFractionWarehouse(id, fwMate), GetFractionWarehouse(id, fwPatron));
        }
        case LICENSE:
        {
            f(string_label,"Склад %s\n\nБаланс: "W"%d$", GetFractionName(id), GetFractionWarehouse(id, fwMoney));
        }
        default: return 1;
    }
    UpdateDynamic3DTextLabelText(FractionsData[id][fWarehouseLabel], COLOR_MAIN, string_label);
    return 1;
}
// Fraction Settings
SaveFractionSettings(fraction_id)
{
    new strFSettings[64];
    for(new i; i < F_SETTINGS_ALL; i++)
    {
        f(strFSettings, "%s%d%s", strFSettings, GetFractionSettings(fraction_id, i), i == F_SETTINGS_ALL-1 ? "":"|");
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `settings` = '%s' WHERE `id` = %d", strFSettings, fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

// Fraction
FractionInit(fraction_id, type_id, bool:isUpdate = false)
{
    if(!(1 <= fraction_id < MAX_FRACTIONS)) return 1;
    switch(type_id)
    {
        case F_WAREHOUSE:
        {
            new area_data[2], Float:fix_cp;
            if(fraction_id == NATIONAL_GUARD || fraction_id == LICENSE ||
                GetFactionCategory(fraction_id) == FACTION_CATEGORY_GANG ||
                GetFactionCategory(fraction_id) == FACTION_CATEGORY_SNN ||
                GetFactionCategory(fraction_id) == FACTION_CATEGORY_MEDIC) fix_cp = 1.0;

            if(isUpdate)
            {
                if(IsValidDynamic3DTextLabel(FractionsData[fraction_id][fWarehouseLabel]))
                    DestroyDynamic3DTextLabel(FractionsData[fraction_id][fWarehouseLabel]);
                if(IsValidDynamicCP(FractionsData[fraction_id][fWarehouseCP]))
                    DestroyDynamicCP(FractionsData[fraction_id][fWarehouseCP]);
                    //Streamer_RemoveArrayData(STREAMER_TYPE_CP, FractionsData[fraction_id][fWarehouseCP], E_STREAMER_EXTRA_ID, 0);
            }
            FractionsData[fraction_id][fWarehouseLabel] = CreateDynamic3DTextLabel("-", COLOR_MAIN, FractionsData[fraction_id][fWarehousePos][0], FractionsData[fraction_id][fWarehousePos][1], FractionsData[fraction_id][fWarehousePos][2]+0.5, 25.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL, FractionsData[fraction_id][fBaseField][fVirtualWorld], FractionsData[fraction_id][fBaseField][fInterior]);
            FractionsData[fraction_id][fWarehouseCP] = CreateDynamicCP(FractionsData[fraction_id][fWarehousePos][0], FractionsData[fraction_id][fWarehousePos][1], FractionsData[fraction_id][fWarehousePos][2]-fix_cp,1.3, FractionsData[fraction_id][fBaseField][fVirtualWorld], FractionsData[fraction_id][fBaseField][fInterior], -1, 10.0);

            area_data[1] = fraction_id, area_data[0] = TYPE_ID_FRAC;
            Streamer_SetArrayData(STREAMER_TYPE_CP, FractionsData[fraction_id][fWarehouseCP], E_STREAMER_EXTRA_ID, area_data);

            UpdateInfoFractionWarehouse(fraction_id);
        }
        case F_UNLOADING:
        {
            if(isUpdate)
            {
                if(IsValidDynamicPickup(FractionsData[fraction_id][fUnloadingPickup]))
                    DestroyDynamicPickup(FractionsData[fraction_id][fUnloadingPickup]);
                if(IsValidDynamic3DTextLabel(FractionsData[fraction_id][fUnloadingLabel]))
                    DestroyDynamic3DTextLabel(FractionsData[fraction_id][fUnloadingLabel]);
            }
            FractionsData[fraction_id][fUnloadingPickup] = CreateDynamicPickup(1239, 23, FractionsData[fraction_id][fUnloadingPos][0], FractionsData[fraction_id][fUnloadingPos][1], FractionsData[fraction_id][fUnloadingPos][2], FractionsData[fraction_id][fUnloadingField][fVirtualWorld], FractionsData[fraction_id][fUnloadingField][fInterior]);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "Место разгрузки на склад\n%s", GetFractionName(fraction_id));
            FractionsData[fraction_id][fUnloadingLabel] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FractionsData[fraction_id][fUnloadingPos][0], FractionsData[fraction_id][fUnloadingPos][1], FractionsData[fraction_id][fUnloadingPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, FractionsData[fraction_id][fUnloadingField][fVirtualWorld], FractionsData[fraction_id][fUnloadingField][fInterior]);
        }
        case F_VEHICLE_SPAWN:
        {
            if(isUpdate)
            {
                if(IsValidDynamicPickup(FractionsData[fraction_id][fVehPickup]))
                    DestroyDynamicPickup(FractionsData[fraction_id][fVehPickup]);
                if(IsValidDynamic3DTextLabel(FractionsData[fraction_id][fVehLabel]))
                    DestroyDynamic3DTextLabel(FractionsData[fraction_id][fVehLabel]);
            }
            FractionsData[fraction_id][fVehPickup] = CreateDynamicPickup(19134, 23,
                FractionsData[fraction_id][fVehSpawnPos][0], FractionsData[fraction_id][fVehSpawnPos][1], FractionsData[fraction_id][fVehSpawnPos][2],
                FractionsData[fraction_id][fVehSpawnField][fVirtualWorld], FractionsData[fraction_id][fVehSpawnField][fInterior]);
            UpdatePickupInfo(FractionsData[fraction_id][fVehPickup], TYPE_FRACTION_VEHICLE_SPAWN, PICKUP_SUBTYPE_INVALID_ID, fraction_id);

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""I"Автомобильный гараж: "W"%s\n\n"I"Нажмите ALT", FractionsData[fraction_id][fName]);
            FractionsData[fraction_id][fVehLabel]  = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FractionsData[fraction_id][fVehSpawnPos][0], FractionsData[fraction_id][fVehSpawnPos][1], FractionsData[fraction_id][fVehSpawnPos][2],
                20.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL, FractionsData[fraction_id][fVehSpawnField][fVirtualWorld], FractionsData[fraction_id][fVehSpawnField][fInterior], -1);
        }
        case F_DRESSING:
        {
            if(isUpdate)
            {
                if(IsValidDynamicPickup(FractionsData[fraction_id][fDressingPickup]))
                    DestroyDynamicPickup(FractionsData[fraction_id][fDressingPickup]);
            }
            FractionsData[fraction_id][fDressingPickup] = CreateDynamicPickup(1275, 23, FractionsData[fraction_id][fDressingPos][0], FractionsData[fraction_id][fDressingPos][1], FractionsData[fraction_id][fDressingPos][2], FractionsData[fraction_id][fBaseField][fVirtualWorld], FractionsData[fraction_id][fBaseField][fInterior]);
            UpdatePickupInfo(FractionsData[fraction_id][fDressingPickup], TYPE_WORK_DRESSING, PICKUP_SUBTYPE_INVALID_ID, fraction_id);
        }
    }
    return 1;
}

SetPlayerFractionSpawn(playerid)
{
    new fraction_id = p_info[playerid][member];
    SetPlayerInterior(playerid, FractionsData[fraction_id][fBaseField][fInterior]);
    SetPlayerVirtualWorld(playerid, FractionsData[fraction_id][fBaseField][fVirtualWorld]);
    SetPlayerPos(playerid, FractionsData[fraction_id][fSpawnPos][0], FractionsData[fraction_id][fSpawnPos][1], FractionsData[fraction_id][fSpawnPos][2]);
    SetPlayerFacingAngle(playerid, FractionsData[fraction_id][fSpawnPos][3]);
    SetCameraBehindPlayer(playerid);
    return 1;
}

SetPlayerFractionSkin(playerid)
{
    if(p_info[playerid][sex] == 2) p_info[playerid][fskin] = FractionsData[p_info[playerid][member]][fManSkin][p_info[playerid][rang]-1];
    else p_info[playerid][fskin] = FractionsData[p_info[playerid][member]][fWomanSkin][p_info[playerid][rang]-1];
    SetPlayerSkin(playerid, p_info[playerid][fskin]);
    p_info[playerid][fwork] = true;
    MysqlUpdatePlayerInt(playerid, "fwork", _:p_info[playerid][fwork]);
    if(GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_PD || GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_FBI)
        p_temp[playerid][StatusOnDuty] = 1;
    return 1;
}

GetFactionType(factionid){
    if(!(0 <= factionid < MAX_FRACTIONS)) return -1;
    return FractionsData[factionid][fType];
}

GetFactionCategory(factionid) {
    if(!(0 <= factionid < MAX_FRACTIONS)) return -1;
    return FractionsData[factionid][fCategory];
}

GetFractionNameType(fraction_id)
{
    new strNameType[24];
    switch(FractionsData[fraction_id][fType])
    {
        case FACTION_TYPE_GOS: strunpack(strNameType, "Госс");
        case FACTION_TYPE_CRIMINAL: strunpack(strNameType, "Криминал");
        case FACTION_TYPE_SNN: strunpack(strNameType, "СМИ");
        default: strunpack(strNameType, "Invalid type");
    }
    return strNameType;
}

GetFractionNameCategory(fraction_id)
{
    new strNameCategory[24];
    switch(FractionsData[fraction_id][fCategory])
    {
        case FACTION_CATEGORY_PD: strunpack(strNameCategory, "Полиция");
        case FACTION_CATEGORY_FBI: strunpack(strNameCategory, "ФБР");
        case FACTION_CATEGORY_MAFIA: strunpack(strNameCategory, "Мафия");
        case FACTION_CATEGORY_GANG: strunpack(strNameCategory, "Банда");
        case FACTION_CATEGORY_MEDIC: strunpack(strNameCategory, "Медики");
        case FACTION_CATEGORY_ARMY: strunpack(strNameCategory, "Армия");
        case FACTION_CATEGORY_SNN: strunpack(strNameCategory, "СМИ");
        case FACTION_CATEGORY_MAYOR: strunpack(strNameCategory, "Мэрия");
        case FACTION_CATEGORY_PRISON: strunpack(strNameCategory, "Фед. тюрьма");
        case FACTION_CATEGORY_LICENSE: strunpack(strNameCategory, "Лицензеры");
        case FACTION_CATEGORY_BIKER: strunpack(strNameCategory, "Байкеры");
        default: strunpack(strNameCategory, "Invalid category");
    }
    return strNameCategory;
}

GetFractionRangName(fraction_id, rang_id)
{
    if(!(1 <= fraction_id < MAX_FRACTIONS) || !(1 <= rang_id <= MAX_FRACTIONS_RANGS)) return FractionsData_NameRang[0][0];
    return FractionsData_NameRang[fraction_id][rang_id-1];
}

CMD:fractionsettings(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    new fraction_id;
    if(sscanf(params, "i", fraction_id)) return SendInfo(playerid, "Используйте: /fractionsettings [fraction ID]");
    if(!(1 <= fraction_id < MAX_FRACTIONS)) return SendInfo(playerid, "Используйте: /fractionsettings [fraction ID]");

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL,"\
        Название %s:\t[Изменить]\n\
        Тип: %s\t[Изменить]\n\
        Категория %s:\t[Изменить]\n\
        Спавн фракции:\t[Изменить]\n\
        Раздевалка:\t[Изменить]\n\
        Склад:\t[Изменить]\n\
        Вирт.мир/интерьер:\t[%d|%d]\n\
        Место разгрузки:\t[Изменить]\n\
        Вирт.мир/интерьер:\t[%d|%d]\n\
        Женские скины:\t[Подробнее|Изменить]\n\
        Мужские скины:\t[Подробнее|Изменить]\n\
        Зарплаты:\t[Подробнее|Изменить]\n\
        Названия рангов:\t[Подробнее|Изменить]\n\
        Состояние склада:\t[Подробнее|Изменить]\n\
        Настройки:\t[Подробнее|Изменить]\n\
        Транспорт:\t[Подробнее|Изменить]",
        GetFractionName(fraction_id),
        GetFractionNameType(fraction_id),
        GetFractionNameCategory(fraction_id),
        FractionsData[fraction_id][fBaseField][fVirtualWorld],
        FractionsData[fraction_id][fBaseField][fInterior],
        FractionsData[fraction_id][fUnloadingField][fVirtualWorld],
        FractionsData[fraction_id][fUnloadingField][fInterior]);
    ShowPlayerDialog(playerid, D_FRACTION_DATA_MENU, DIALOG_STYLE_TABLIST, "Настройки фракции", STRING_GLOBAL, "Выбрать", "Отмена");

    p_temp[playerid][p_listitem_int] = fraction_id;
    return 1;
}
alias:fractionsettings("fsettings", "fset");

SetFractionSpawnPos(playerid, fraction_id)
{
    GetPlayerPos(playerid, FractionsData[fraction_id][fSpawnPos][0], FractionsData[fraction_id][fSpawnPos][1], FractionsData[fraction_id][fSpawnPos][2]);
    GetPlayerFacingAngle(playerid, FractionsData[fraction_id][fSpawnPos][3]);

    FractionsData[fraction_id][fBaseField][fVirtualWorld] = GetPlayerVirtualWorld(playerid);
    FractionsData[fraction_id][fBaseField][fInterior] = GetPlayerInterior(playerid);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `spawn_pos` = '%f|%f|%f|%f', `base_field` = '%d|%d' WHERE `id` = %d",
        FractionsData[fraction_id][fSpawnPos][0], FractionsData[fraction_id][fSpawnPos][1], FractionsData[fraction_id][fSpawnPos][2], FractionsData[fraction_id][fSpawnPos][3],
        FractionsData[fraction_id][fBaseField][fVirtualWorld], FractionsData[fraction_id][fBaseField][fInterior], fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

SetFractionDressingPos(playerid, fraction_id)
{
    GetPlayerPos(playerid, FractionsData[fraction_id][fDressingPos][0], FractionsData[fraction_id][fDressingPos][1], FractionsData[fraction_id][fDressingPos][2]);

    FractionInit(fraction_id, F_DRESSING, true);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `dressing_pos` = '%f|%f|%f' WHERE `id` = %d",
        FractionsData[fraction_id][fDressingPos][0], FractionsData[fraction_id][fDressingPos][1], FractionsData[fraction_id][fDressingPos][2], fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

SetFractionWarehousePos(playerid, fraction_id)
{
    GetPlayerPos(playerid, FractionsData[fraction_id][fWarehousePos][0], FractionsData[fraction_id][fWarehousePos][1], FractionsData[fraction_id][fWarehousePos][2]);

    FractionInit(fraction_id, F_WAREHOUSE, true);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `warehouse_pos` = '%f|%f|%f' WHERE `id` = %d",
        FractionsData[fraction_id][fWarehousePos][0], FractionsData[fraction_id][fWarehousePos][1], FractionsData[fraction_id][fWarehousePos][2], fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

SetFractionUnloadingPos(playerid, fraction_id)
{
    GetPlayerPos(playerid, FractionsData[fraction_id][fUnloadingPos][0], FractionsData[fraction_id][fUnloadingPos][1], FractionsData[fraction_id][fUnloadingPos][2]);

    FractionsData[fraction_id][fUnloadingField][fVirtualWorld] = GetPlayerVirtualWorld(playerid);
    FractionsData[fraction_id][fUnloadingField][fInterior] = GetPlayerInterior(playerid);

    FractionInit(fraction_id, F_UNLOADING, true);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `unloading_pos` = '%f|%f|%f', `unloading_field` = '%d|%d' WHERE `id` = %d",
        FractionsData[fraction_id][fUnloadingPos][0], FractionsData[fraction_id][fUnloadingPos][1], FractionsData[fraction_id][fUnloadingPos][2],
        FractionsData[fraction_id][fUnloadingField][fVirtualWorld], FractionsData[fraction_id][fUnloadingField][fInterior], fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

SetFractionVehSpawnPos(playerid, fraction_id)
{
    GetPlayerPos(playerid, FractionsData[fraction_id][fVehSpawnPos][0], FractionsData[fraction_id][fVehSpawnPos][1], FractionsData[fraction_id][fVehSpawnPos][2]);
    GetPlayerFacingAngle(playerid, FractionsData[fraction_id][fVehSpawnPos][3]);

    FractionsData[fraction_id][fVehSpawnField][fVirtualWorld] = GetPlayerVirtualWorld(playerid);
    FractionsData[fraction_id][fVehSpawnField][fInterior] = GetPlayerInterior(playerid);

    FractionInit(fraction_id, F_VEHICLE_SPAWN, true);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `veh_spawn_pos` = '%f|%f|%f|%f', `veh_spawn_field` = '%d|%d' WHERE `id` = %d",
        FractionsData[fraction_id][fVehSpawnPos][0], FractionsData[fraction_id][fVehSpawnPos][1], FractionsData[fraction_id][fVehSpawnPos][2], FractionsData[fraction_id][fVehSpawnPos][3],
        FractionsData[fraction_id][fVehSpawnField][fVirtualWorld], FractionsData[fraction_id][fVehSpawnField][fInterior], fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}
// Fraction Settings Skins
ShowFractionSkins(playerid, fraction_id, sex_id)
{
    SetPVarInt(playerid, #FRACTION_ID, fraction_id);
    SetPVarInt(playerid, #SEX_ID, sex_id);
    ShowPlayerListTD(playerid, LIST_TD_ID_FRACTION_SET_SKIN);
}

ShowDialogFractionSkins(playerid)
{
    new fraction_id = p_temp[playerid][p_listitem][30], td_idx = p_temp[playerid][p_listitem][32];
    f(STRING_GLOBAL, "Введите ID скина для %s(%d)", GetFractionRangName(fraction_id, td_idx+1), td_idx+1);
    ShowPlayerDialog(playerid, D_FRACTION_SET_SKIN, DIALOG_STYLE_INPUT, "Смена скина", STRING_GLOBAL, "Ввести", "Отмена");
    return 1;
}

SaveFractionSkins(fraction_id, sex_id)
{
    new strFSkins[128];
    for(new i; i < MAX_FRACTIONS_RANGS; i++)
    {
        f(strFSkins, "%s%d%s", strFSkins,
            sex_id == F_MAN_SKIN ? FractionsData[fraction_id][fManSkin][i] : FractionsData[fraction_id][fWomanSkin][i],
            i == MAX_FRACTIONS_RANGS-1 ? "":"|");
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `%s` = '%s' WHERE `id` = %d",
        sex_id == F_MAN_SKIN ? "man_skin" : "woman_skin", strFSkins, fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

SetFractionPays(playerid)
{
    new fraction_id = p_temp[playerid][p_listitem_int], list_id = p_temp[playerid][p_listitem][31];
    f(STRING_GLOBAL, ""W"Введите новую зарплату для "I"%s(%d - %d$)",
        GetFractionRangName(fraction_id, list_id+1), list_id+1, FractionsData[fraction_id][fPay][list_id]);
    ShowPlayerDialog(playerid, D_FRACTION_SET_PAY, DIALOG_STYLE_INPUT, ""I"Сменить зарплату", STRING_GLOBAL, "Выбрать","Назад");
    return 1;
}

SaveFractionPay(fraction_id)
{
    new strFPay[128];
    for(new i; i < MAX_FRACTIONS_RANGS; i++)
    {
        f(strFPay, "%s%d%s", strFPay, FractionsData[fraction_id][fPay][i], i == MAX_FRACTIONS_RANGS-1 ? "":"|");
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `pay` = '%s' WHERE `id` = %d", strFPay, fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

SetFractionNameRangs(playerid)
{
    new fraction_id = p_temp[playerid][p_listitem_int], list_id = p_temp[playerid][p_listitem][31];
    f(STRING_GLOBAL, ""W"Введите новое название для ранга "I"%s(%d)",
        GetFractionRangName(fraction_id, list_id+1), list_id+1);
    ShowPlayerDialog(playerid, D_FRACTION_SET_NAME_RANG, DIALOG_STYLE_INPUT, ""I"Сменить название ранга", STRING_GLOBAL, "Выбрать","Назад");
    return 1;
}

SaveFractionNameRang(fraction_id)
{
    new strFRangs[256];
    for(new i; i < MAX_FRACTIONS_RANGS; i++)
    {
        f(strFRangs, "%s%s%s", strFRangs, GetFractionRangName(fraction_id, i+1), i == MAX_FRACTIONS_RANGS-1 ? "":"|");
    }
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `rang_name` = '%s' WHERE `id` = %d", strFRangs, fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
}

forward SetFractionRangDefault(fraction_id);
public SetFractionRangDefault(fraction_id)
{
    if(!cache_num_rows()) return 1;
    new data[256];
    cache_get_value_name(0, "rang_name_default", data);
    strexplode(FractionsData_NameRang[fraction_id], data, "|");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `rang_name` = `rang_name_default` WHERE `id` = %d", fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

forward FractionPlayerChangeRang(playerid, player_mysql_id);
public FractionPlayerChangeRang(playerid, player_mysql_id)
{
    if(!cache_num_rows()) return SendError(playerid, "Ничего не найдено.");
    new rang_id, sex_id, member_name[MAX_PLAYER_NAME];
    cache_get_value_name(0, "name", member_name);
    cache_get_value_name_int(0, "rang", rang_id);
    cache_get_value_name_int(0, "sex", sex_id);

    if(rang_id >= p_info[playerid][rang])
        return SendError(playerid, "У Вас слишком маленький ранг.");

    p_temp[playerid][p_listitem_int] = player_mysql_id;
    p_temp[playerid][p_listitem][0] = EOS;
    format(p_temp[playerid][p_listitem], MAX_PLAYER_NAME, "%s", member_name);

    SetPVarInt(playerid, "change_rang_sex", sex_id);

    SendInfo(playerid, "Выберите новый ранг для "I"%s "W"от 1 до %d.", member_name, p_info[playerid][rang]-1);
    STRING_GLOBAL[0] = EOS;
    for(new i; i < p_info[playerid][rang]-1; i++)
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s(%d)\n", STRING_GLOBAL, i+1, GetFractionRangName(p_info[playerid][member], i+1), i+1);
    ShowPlayerDialog(playerid, D_FRACTION_OFF_CHANGE_RANG, DIALOG_STYLE_LIST, ""I"Выберите новый ранг", STRING_GLOBAL, "Выбрать","Назад");
    return 1;
}

SetFractionWarehouseValue(playerid)
{
    ShowPlayerDialog(playerid, D_FRACTION_SET_WAREHOUSE, DIALOG_STYLE_INPUT, ""I"Сменить количество", ""W"Введите новое значение", "Выбрать","Назад");
    return 1;
}
