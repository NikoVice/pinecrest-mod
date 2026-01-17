#define MAX_CHANGE_CIVIL_COINS      26

enum
{
    TYPE_CHANGE_ROULETTE,
    TYPE_CHANGE_ACCESSORIES,
    TYPE_CHANGE_INVENTORY,
    TYPE_CHANGE_SKIN,
    TYPE_CHANGE_COSTUME,
    TYPE_CHANGE_VEHICLE,
    TYPE_CHANGE_VIP
}

new ChangeCivilCoinsTypeName[7][12] = {"Рулетка", "Аксессуар", "Предмет", "Скин", "Костюм", "Транспорт", "VIP"};

enum E_CHANGE_CIVIL_COINS
{
    ChangeCivilCoinsType,
    ChangeCivilCoinsIDx,
    ChangeCivilCoinsPrice
}

new ChangeCivilCoins[MAX_CHANGE_CIVIL_COINS][E_CHANGE_CIVIL_COINS] = {
    {TYPE_CHANGE_ACCESSORIES, 545, 20000}, // Разноцветный воздушный шар #2;
	{TYPE_CHANGE_ACCESSORIES, 546, 20000}, // Разноцветный воздушный шар #3;
	{TYPE_CHANGE_ACCESSORIES, 279, 7000}, // Firefighter(Пожарный);
	{TYPE_CHANGE_ACCESSORIES, 240, 7000}, // The D.A(Лицензер);
    {TYPE_CHANGE_ACCESSORIES, 455, 3000}, // Шляпа цилиндр;
	{TYPE_CHANGE_ACCESSORIES, 460, 1000}, // Аксессуар Скейтборд;
	{TYPE_CHANGE_ACCESSORIES, 456, 1000}, // Балаклава;
	{TYPE_CHANGE_INVENTORY, 732, 30000}, // ADD VIP на 30 дн;
	{TYPE_CHANGE_INVENTORY, 677, 5000}, // Iphone Graphite
    {TYPE_CHANGE_INVENTORY, 737, 10000}, // Premium на скин;
	{TYPE_CHANGE_INVENTORY, 672, 600}, // Yakuza кейс;
	{TYPE_CHANGE_INVENTORY, 655, 300}, // Модный кейс;
	{TYPE_CHANGE_INVENTORY, 762, 300}, // Современная карта кладов;
	{TYPE_CHANGE_ROULETTE, 644, 1000}, // Gold Рулетка;
	{TYPE_CHANGE_ROULETTE, 643, 500}, // Silver Рулетка;
	{TYPE_CHANGE_ROULETTE, 642, 200}, // Bronze Рулетка;
	{TYPE_CHANGE_VEHICLE, 3236, 15000}, // Toyota Mark II;
	{TYPE_CHANGE_VEHICLE, 4764, 20000}, // Toyota Chaser;
	{TYPE_CHANGE_COSTUME, 12, 9000}, // Костюм 'Minecraft';
	{TYPE_CHANGE_COSTUME, 13, 7000}, // Костюм 'Brawl Stars';
	{TYPE_CHANGE_VIP, 1, 300}, // Vip Bronze 1 дн;
	{TYPE_CHANGE_VIP, 2, 500}, // Vip Silver 1 дн;
	{TYPE_CHANGE_VIP, 3, 750}, // Vip Gold 1 дн;
	{TYPE_CHANGE_VIP, 4, 1000}, // Vip Bronze 7 дн;
	{TYPE_CHANGE_VIP, 5, 1500}, // Vip Silver 7 дн;
	{TYPE_CHANGE_VIP, 6, 2000} // Vip Gold 7 дн;
};

ShowChangeCivilCoinsList(playerid)
{
    STRING_GLOBAL = "[#] Название\tКоличество гражданских монет\n", STRING_MIN[0] = EOS;
    for(new i = 0; i < MAX_CHANGE_CIVIL_COINS; i++)
    {
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\n", i + 1, GetChangeCivilCoinsName(ChangeCivilCoins[i][ChangeCivilCoinsType], ChangeCivilCoins[i][ChangeCivilCoinsIDx]), ChangeCivilCoins[i][ChangeCivilCoinsPrice]);
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_CHANGE_CIVIL_COINS_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Обмен гражданских монет", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

GetChangeCivilCoinsName(type, idx)
{
    new str[256];
    switch(type)
    {
        case TYPE_CHANGE_SKIN, TYPE_CHANGE_ACCESSORIES, TYPE_CHANGE_ROULETTE, TYPE_CHANGE_INVENTORY:
        {
            format(str, sizeof(str), "%s: %s", ChangeCivilCoinsTypeName[type], ItemsInfo[idx][iName]);
        }
        case TYPE_CHANGE_COSTUME:
        {
            format(str, sizeof(str), "%s: %s", ChangeCivilCoinsTypeName[type], CostumeName[idx]);
        }
        case TYPE_CHANGE_VEHICLE:
        {
            format(str, sizeof(str), "%s: %s", ChangeCivilCoinsTypeName[type], GetVehicleName(INVALID_VEHICLE_ID, idx));
        }
        case TYPE_CHANGE_VIP:
        {
            new days = 1;
            idx--;
            if(idx >= 3) 
            {
                days = 7;
                idx -= 3;
            }
            format(str, sizeof(str), "%s: %s на %d дн.", ChangeCivilCoinsTypeName[type], TypeVIPName[idx], days);
        }
        
    }
    return str;
}

new pickup_change_civil_coins;

ShowChangeCivilCoins(playerid)
{
    ShowPlayerDialog(playerid, D_CHANGE_CIVIL_COINS, DIALOG_STYLE_MSGBOX, ""I"Обмен гражданских монет", ""W"\
    В данном месте ты можешь обменять гражданские монеты на различные игровые предметы, а именно: "I" уникальные\n\
    аксессуары и уникальные скины."W"\n\n\
    Гражданские монеты выдаются каждый час, а также их можно приобрести на центральном рынке или в нашем магазине.\n\n\
    При нажатии "I"\"Далее\""W" откроется диалог с обменом гражданских монет на вышеперечисленные предметы. ", "Далее", "Отмена");
    return 1;
}

LoadChangeCivilCoins()
{
    // Обменщик гражданских монет;
    CreateActor(188, 1417.0363,-1707.5519,13.5469,270.1089);
    CreateDynamic3DTextLabel("NPC: "I"Обменщик гражданских монет", COLOR_WHITE, 1417.0363,-1707.5519,13.5469 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_change_civil_coins = CreatePickup(1239, 23, 1418.7518,-1707.5118,13.5469);
    CreateDynamic3DTextLabel("<< Обмен гражданских монет >>", COLOR_MAIN, 1418.7518,-1707.5118,13.5469, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateDynamicObject(1570, 1417.58142, -1707.07385, 13.78690, 0.00000, 0.00000, 90.00000);
    return 1;
}
