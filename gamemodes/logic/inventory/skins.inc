#define PRICE_WASH_SKINS            1000

enum
{
    SKINS_ID_REPAIR,
    SKINS_ID_PREMIUM
}

CheckPlayerSkins(playerid)
{
    new bool:bIsUpdate = false;
    for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
    {
        if( InventoryPlayer[playerid][i][inv_mysql_id] == INVALID_MYSQL_ID ||
            ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] != TYPE_ITEMS_SKINS ||
            InventoryPlayer[playerid][i][inv_status_use] == 0) continue;
        if(InventoryPlayer[playerid][i][inv_skin_premium] == 1) continue;
        InventoryPlayer[playerid][i][inv_skin_wear] -= 0.2;
        if(InventoryPlayer[playerid][i][inv_skin_wear] <= 0.0)
        {
            bIsUpdate = true;
            InventoryPlayer[playerid][i][inv_skin_wear] = 0.0;
            InventoryPlayer[playerid][i][inv_status_use] = 0;
            SetPlayerSkinEx(playerid);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `inventory` SET `status_use` = %d WHERE `mysql_id` = %d",
                InventoryPlayer[playerid][i][inv_status_use], InventoryPlayer[playerid][i][inv_mysql_id]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL),
            "UPDATE `inventory` SET `skin_wear` = %f WHERE `mysql_id` = %d",  InventoryPlayer[playerid][i][inv_skin_wear], InventoryPlayer[playerid][i][inv_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL);
        if(bIsUpdate) SendInfo(playerid, "Одежда \"%s\" максимально загрязнилась и была снята.", ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iName]);
    }
    Equipment_Update(playerid);
    if(bIsUpdate) SendInfo(playerid, "Чтобы постирать одежду, отправляйтесь в прачечную.");
    return 1;
}

GetPriceWashSkins(Float:amount)
{
    new Float:repair_price;
    repair_price = (100.0 - amount) * PRICE_WASH_SKINS;
    return floatround(repair_price);
}