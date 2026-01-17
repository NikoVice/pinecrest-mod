enum
{
    TYPE_GIVE_ITEM_EXP = 1,
    TYPE_GIVE_ITEM_MONEY, // 2
    TYPE_GIVE_ITEM_U_MONEY, // 3
    TYPE_GIVE_ITEM_DONATE, // 4
    TYPE_GIVE_ITEM_U_DONATE, // 5
    TYPE_GIVE_ITEM_INVENTORY, // 6
    TYPE_GIVE_ITEM_ACCESSORIES, // 7
    TYPE_GIVE_ITEM_SKIN, // 8
    TYPE_GIVE_ITEM_U_SKIN, // 9
    TYPE_GIVE_ITEM_VEHICLE, // 10
    TYPE_GIVE_ITEM_U_VEHICLE, // 11
    TYPE_GIVE_ITEM_VIP, // 12
}

enum
{
    TYPE_PLAYER_ITEM_GIVE,
    TYPE_PLAYER_ITEM_CONFIRM_SELL,
    TYPE_PLAYER_ITEM_SELL,
    TYPE_PLAYER_ITEM_DELETE,
}

new TypeGiveItemName[13][64] = {"Нет", "Очки опыта", "Деньги", "Уникальное количество денег", "Flin Money", "Уникальное количество Flin Money", "Предмет инвентаря", "Уникальный аксессуар", "Скин", "Уникальный скин", "Транспортное средство", "Уникальное транспортное средство", "VIP"};

new TypeVIPName[3][12] = {"Bronze", "Silver", "Gold"};