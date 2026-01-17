/*
    Author: Vip Uzer
    Flin Mobile
    (c) 8.10.2021-08.04.2022
*/
#define MAX_PLAYER_EQUIPMENT        100
#define MAX_ALL_EQUIPMENT           160 //

#define INVALID_SKIN_ID     0

enum
{
    INVENTORY_OWNER_TYPE_PLAYER,
    INVENTORY_OWNER_TYPE_VEHICLE,
    INVENTORY_OWNER_TYPE_HOUSE,
    INVENTORY_OWNER_TYPE_TRASHBOX,
    INVENTORY_OWNER_TYPE_FAMILY,
}

enum
{
    INVENTORY_SELECT_TYPE_RIGHT = 0,
    INVENTORY_SELECT_TYPE_USE_ACC,
    INVENTORY_SELECT_TYPE_LEFT
}

enum INVENTORY_INFO
{
    inv_mysql_id, // хд ад
    inv_slot_id, // якнр
    inv_item_id, // хд опедлерю
    inv_amount, // йнкхвеярбн
    inv_status_use, // хяонкэгсеряъ хкх мер
    // accessories
    inv_acc_slot,
    Float:inv_acc_wear, // wear
    inv_acc_mt[2],
    Float:inv_acc_pos[9], // pos
    inv_acc_premium,

    // skin
    Float:inv_skin_wear, // wear
    inv_skin_premium,

    // TEMP:
    inv_market_sell_amount, // йнкхвеярбн мю опндюфе
    inv_market_sell_price, // жемю гю 1 едхмхжс мю гюйсойе

    inv_market_buy_amount, // йнкхвеярбн мю гюйсойе
    inv_market_buy_price, // жемю гю 1 едхмхжс мю опндюфе

    inv_freeze_time, // ГЮЛНПНГЙЮ ОПЕДЛЕРЮ Б TRASHBOX
}
new InventoryPlayer[MAX_PLAYERS][MAX_ALL_EQUIPMENT][INVENTORY_INFO];
