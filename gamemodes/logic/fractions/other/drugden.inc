


LoadDrugDen()
{
    // Барыга;
    new actorid;

    actorid = CreateActor(30, 1455.4324,-674.8237,1015.2120,5.6295);
    SetActorVirtualWorld(actorid, 1);
    CreateDynamic3DTextLabel("NPC: "I"Барыга", COLOR_WHITE, 1455.4324,-674.8237,1015.2120 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    actorid = CreateActor(30, 2163.6333,-1674.9763,15.0859,222.8429);
    CreateDynamic3DTextLabel("NPC: "I"Барыга", COLOR_WHITE, 2163.6333,-1674.9763,15.0859 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_drugden[0] = CreateDynamicPickup(1318, 23, 2165.9229,-1671.2035,15.0732);
    pickup_drugden[1] = CreateDynamicPickup(1318, 23, 1459.4323,-668.1552,1015.2104, 1);
    pickup_drugden[2] = CreatePickup(1239, 23, 1455.3331,-674.1303,1015.2120, 1);
    CreateDynamic3DTextLabel("<< Ассортимент наркопритона >>", COLOR_MAIN, 1455.3331,-674.1303,1015.2120, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    pickup_drugden[3] = CreatePickup(1239, 23, 2164.1455,-1675.4545,15.0859);
    CreateDynamic3DTextLabel("<< Ассортимент наркопритона >>", COLOR_MAIN, 2164.1455,-1675.4545,15.0859, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    return 1;
}

enum
{
    TYPE_DRUGDEN_SAVE_DEFAULT,
    TYPE_DRUGDEN_SAVE_WAREHOUSE
}

SaveDrugDen(type = TYPE_DRUGDEN_SAVE_DEFAULT)
{
    if(type == TYPE_DRUGDEN_SAVE_DEFAULT)
    {
        STRING_MIN[0] = EOS;
        format(STRING_MIN, sizeof(STRING_MIN), "Наркопритон\nПод контролем: "W"%s", GetFractionName(DrugDenInfo[ddOwner]));
        UpdateDynamic3DTextLabelText(DrugDenInfo[ddText], COLOR_MAIN, STRING_MIN);
    }

    STRING_MIN[0] = EOS;
    mysql_format(con_bd, STRING_MIN, sizeof(STRING_MIN), "UPDATE `other` SET `drugden` = '%d, %d, %d, %d, %d, %d'",
    DrugDenInfo[ddOwner], DrugDenInfo[ddCapture], DrugDenInfo[ddBuy][0], DrugDenInfo[ddBuy][1], DrugDenInfo[ddBuy][2], DrugDenInfo[ddSell]);
    mysql_tquery(con_bd, STRING_MIN);
    return 1;
}

new
    drugden_buy_idx[3] = {646, 692, 693},
    drugden_buy_price[3] = {2500, 250, 500},
    drugden_sell_price = 25
;

enum
{
    TYPE_DRUGDEN_MAIN,
    TYPE_DRUGDEN_BUY,
    TYPE_DRUGDEN_BUY_INPUT,
    TYPE_DRUGDEN_HELP,
    TYPE_DRUGDEN_STREET
}

ShowDrugDenMenu(playerid, type, first_parameter = 0)
{
    switch(type)
    {
        case TYPE_DRUGDEN_MAIN:
        {
            ShowPlayerDialog(playerid, D_DRUGDEN_MENU, DIALOG_STYLE_LIST, ""I"Наркопритон", ""I"[1]"W" Покупка товара\n"I"[2]"W" Информация для гровера", "Далее", "Отмена");
        }
        case TYPE_DRUGDEN_BUY:
        {
            new type, free_amount = GetInventoryFreeItems(playerid, type);
            STRING_GLOBAL = "[#] Название\tСтоимость\tНа складе\tДоступно для покупки\n", STRING_MIN[0] = EOS;
            for(new i = 0; i < sizeof(drugden_buy_idx); i++)
            {
                type = drugden_buy_idx[i];
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$\t%d\t%d\n", i + 1, ItemsInfo[type][iName], drugden_buy_price[i], DrugDenInfo[ddBuy][i], free_amount);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_DRUGDEN_BUY, DIALOG_STYLE_TABLIST_HEADERS, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
        }
        case TYPE_DRUGDEN_BUY_INPUT:
        {
            new type = drugden_buy_idx[first_parameter], free_amount = GetInventoryFreeItems(playerid, type);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите количество %s:\nСтоимость "I"%d$"W"\n\nНа складе: "I"%d"W"\n\nДоступно для покупки: "I"%d",
                ItemsInfo[type][iName], drugden_buy_price[first_parameter], DrugDenInfo[ddBuy][first_parameter], free_amount);
            ShowPlayerDialog(playerid, D_DRUGDEN_BUY_INPUT, DIALOG_STYLE_INPUT, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "DrugDenIDx", first_parameter);
        }
        case TYPE_DRUGDEN_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i; i < sizeof(DrugdenInfoList); i++) strcat(STRING_GLOBAL, DrugdenInfoList[i]);
            ShowPlayerDialog(playerid, D_DRUGDEN_MENU_BACK, DIALOG_STYLE_MSGBOX, ""I"Информация для гровера", STRING_GLOBAL, "Далее", "Отмена");
        }
        case TYPE_DRUGDEN_STREET:
        {
            new free_amount = GetInventoryFreeItems(playerid, 629);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите количество гр. наркотиков:\nСтоимость "I"%d$"W" за "I"гр."W"\n\nНа складе: "I"%d гр."W"\n\nДоступно для покупки: "I"%d гр.", drugden_sell_price, DrugDenInfo[ddSell], free_amount);
            ShowPlayerDialog(playerid, D_DRUGDEN_STREET, DIALOG_STYLE_INPUT, ""I"Покупка товара", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

CheckDrugDen()
{
    for(new i = 0; i < 3; i++)
    {
        if(DrugDenInfo[ddBuy][i] < 500)
        {
            DrugDenInfo[ddBuy][i] += RandomEx(10, 25);
            if(DrugDenInfo[ddBuy][i] > 500) DrugDenInfo[ddBuy][i] = 500;
        }
    }
    SaveDrugDen();
    return 1;
}
