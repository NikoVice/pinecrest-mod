#define MAX_TAX 16

enum
{
    TAX_TAKE_BANK,
    TAX_PUT_BANK,
    TAX_TRANSFER_BANK,
    TAX_PHONE_BALANCE_ADD,
    TAX_PHONE_BALANCE_GIVE,
    TAX_SELL_ARMY_SKIN,
    TAX_SELL_GUN,
    TAX_CHANGE_VEH_NUMBER,
    TAX_SELL_VEH_NUMBER,
    TAX_CHANGE_CAR,
    TAX_ITEMS_SELL,
    TAX_TRADE,
    TAX_CHANGE_SIM_PHONE,
    TAX_SELL_SIM_PHONE,
    TAX_MARKET_SELL,
    TAX_MARKET_BUY
}

enum TAX_INFO
{
    tType,
    tName[64],
    Float:tTax,
    tCount
};

new TaxInfo[MAX_TAX][TAX_INFO] = {
    {TAX_TAKE_BANK, "Снятие с банковского счета", {0.02}, 0},
    {TAX_PUT_BANK, "Пополнение банковского счета", {0.02}, 0},
    {TAX_TRANSFER_BANK, "Перевод через банковский счет", {0.02}, 0},
    {TAX_PHONE_BALANCE_ADD, "Пополнение балана телефона", {0.02}, 0},
    {TAX_PHONE_BALANCE_GIVE, "Пополнение балана телефона игроку", {0.02}, 0},
    {TAX_SELL_ARMY_SKIN, "Продажа военной формы", {0.02}, 0},
    {TAX_SELL_GUN, "Продажа оружия", {0.02}, 0},
    {TAX_CHANGE_VEH_NUMBER, "Обмен транспортными номерами с доплатой", {0.02}, 0},
    {TAX_SELL_VEH_NUMBER, "Продажа транспортных номеров", {0.02}, 0},
    {TAX_CHANGE_CAR, "Обмен транспортных средств", {0.02}, 0},
    {TAX_ITEMS_SELL, "Продажа предметов инвентаря", {0.02}, 0},
    {TAX_TRADE, "Трейд", {0.02}, 0},
    {TAX_CHANGE_SIM_PHONE, "Обмен СИМ-карт с доплатой", {0.02}, 0},
    {TAX_SELL_SIM_PHONE, "Продажа СИМ-карт", {0.02}, 0},
    {TAX_MARKET_SELL, "Продажа на центральном рынке", {0.02}, 0},
    {TAX_MARKET_BUY, "Закупка на центральном рынке", {0.02}, 0}
};

GetTaxCount(playerid, count, idx, type = 0)
{
    new tax = floatround(count * TaxInfo[idx][tTax]);
    if(type == 0) TaxInfo[idx][tCount] += tax;

    if(p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) tax = tax/2;
    return tax;
}

CMD:tax(playerid, params[])
{
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    for(new i = 0; i < MAX_TAX; i++)
    {
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s (%f)\n", i + 1, TaxInfo[i][tName], TaxInfo[i][tTax]);
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_LIST, ""I"Налоги", STRING_GLOBAL, "Отмена", "");
    return 1;
}
