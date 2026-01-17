enum
{
    H_FOOR_HALLWAY = 0, // пол прихожая 1 этаж
    H_FOOR_HALLWAY2, // пол прихожая 2 этаж
    H_FOOR_LIVING_ROOM, //пол гостинная
    H_FOOR_KITCHEN, //пол  кухня
    H_FOOR_BATHROOM, // пол ванная
    H_FOOR_CABINET, // пол кабинет
    H_FOOR_ROOM, // пол комната 1
    H_FOOR_BAR,
    H_FOOR_GYM,

    H_WALL_HALLWAY, // стена прихожая
    H_WALL_LIVING_ROOM, //стена  гостинная
    H_WALL_KITCHEN, //стена  кухня
    H_WALL_BATHROOM, // стена ванная
    H_WALL_CABINET,//стена кабинет
    H_WALL_BED, // стена кровать
    H_WALL_ROOM, //стена комната
    H_WALL_BAR,// стена бар
    H_WALL_GYM, //стена спортзал

    H_ROOF_HALLWAY, // потолок прихожая
    H_ROOF_LIVING_ROOM, //потолок  гостинная
    H_ROOF_KITCHEN, //потолок  кухня
    H_ROOF_BATHROOM, // потолок ванная
    H_ROOF_CABINET,//потолок кабинет
    H_ROOF_ROOM, //потолок комната
    H_ROOF_BALCONY, // потолок балкон
    H_ROOF_BAR, //потолок бар
    H_ROOF_GYM, // потолок спортзал

    H_ALL_MAPPING
}

enum
{
    G_FOOR,
    G_WALL,
    G_ROOF,
    G_ALL_MAPPING
}

new house_repair_name4[][] =
{
    "Пол: Прихожая", "Пол: Кухня", "Пол: Ванная", "Пол: Комната", "Пол: Бар", "Пол: Спортзал",
    "Стена: Прихожая", "Стена: Кухня", "Стена: Ванная", "Стена: Комната", "Стена: Бар", "Стена: Спортзал",
    "Потолок: Бар", "Потолок: Спортзал"
};
new house_repair_name3[][] =
{
    "Пол: Прихожая 1 этаж", "Пол: Гостинная 2 этаж", "Пол: Кухня", "Пол: Ванная", "Пол: Кабинет", "Пол: Комната",
    "Стена: Прихожая 1 этаж", "Стена: Гостинная 2 этаж", "Стена: Кухня", "Стена: Ванная", "Стена: Кабинет", "Стена: За кроватью", "Стена: Комната",
    "Потолок: Прихожая 1 этаж", "Потолок: Гостинная 2 этаж", "Потолок: Кухня", "Потолок: Ванная", "Потолок: Кабинет", "Потолок: Комната", "Потолок: Балкон"
};
new house_repair_name2[][] =
{
    "Пол: Прихожая", "Пол: Кухня", "Пол: Ванная",
    "Стена: Прихожая", "Стена: Кухня", "Стена: Ванная",
    "Потолок: Прихожая", "Потолок: Ванная"
};
new house_repair_name1[][] =
{
    "Пол: Прихожая", "Пол: Гостинная", "Пол: Кухня", "Пол: Ванная",
    "Стена: Прихожая", "Стена: Гостинная", "Стена: Кухня", "Стена: Ванная",
    "Потолок: Прихожая", "Потолок: Гостинная", "Потолок: Ванная"
};
new house_idx_repair[4][] =
{
    {
        H_FOOR_HALLWAY,H_FOOR_LIVING_ROOM,H_FOOR_KITCHEN,H_FOOR_BATHROOM,
        H_WALL_LIVING_ROOM, H_WALL_HALLWAY, H_WALL_KITCHEN, H_WALL_BATHROOM,
        H_ROOF_HALLWAY,H_ROOF_LIVING_ROOM,H_ROOF_BATHROOM
    },
    {
        H_FOOR_HALLWAY,H_FOOR_KITCHEN,H_FOOR_BATHROOM,
        H_WALL_HALLWAY,H_WALL_KITCHEN,H_WALL_BATHROOM,
        H_ROOF_HALLWAY,H_ROOF_BATHROOM
    },
    {
        H_FOOR_HALLWAY,H_FOOR_HALLWAY2,H_FOOR_KITCHEN,H_FOOR_BATHROOM,H_FOOR_CABINET,H_FOOR_ROOM,
        H_WALL_HALLWAY,H_WALL_LIVING_ROOM,H_WALL_KITCHEN,H_WALL_BATHROOM,H_WALL_CABINET,H_WALL_BED,H_WALL_ROOM,
        H_ROOF_HALLWAY,H_ROOF_LIVING_ROOM,H_ROOF_KITCHEN,H_ROOF_BATHROOM,H_ROOF_CABINET,H_ROOF_ROOM,H_ROOF_BALCONY
    },
    {
        H_FOOR_HALLWAY,H_FOOR_KITCHEN,H_FOOR_BATHROOM,H_FOOR_ROOM,H_FOOR_BAR,H_FOOR_GYM,
        H_WALL_HALLWAY,H_WALL_KITCHEN,H_WALL_BATHROOM,H_WALL_ROOM,H_WALL_BAR,H_WALL_GYM,
        H_ROOF_BAR,H_ROOF_GYM
    }
};

////////////////////////////
#define MAX_HOUSE_INT 5
#define HOUSE_INT_ID_REPAIR 99
enum enum_int
{
    i_int,
    Float:i_spawn_pos[4]
}
new house_class[][] = {"Nope","C","B","A"};
new h_ints[4][5][enum_int] = {
    {
        {1,                     {243.9913,305.0812,999.1484,      270.0}},
        {10,                    {422.5714, 2536.7991, 10.0000,    90.0}},
        {1,                     {2218.4036,-1076.2747,1050.4844,  90.0}},
        {4,                     {242.8186,-1851.2277,3333.7964,   270.0}},
        {HOUSE_INT_ID_REPAIR,   {2228.4063,732.4332,1023.3484,    0.0}}
    }, //
    {
        {1,                     {223.1488, 1287.0756, 1082.1406,   0.0}},
        {5,                     {318.5709, 1114.7144, 1084.0,      170.0}},
        {12,                    {446.7668, 506.3195, 1001.4195,    0.0}},
        {1,                     {711.3050, 104.3360, 899.9125,     270.0}},
        {HOUSE_INT_ID_REPAIR,   {985.2796,1234.7854, 1024.2516,    90.0}}
    },
    {
        {6,                     {-68.7742, 1351.1971, 1080.2109,   0.0}},
        {4,                     {260.9900, 1284.2965, 1080.2578,   0.0}},
        {8,                     {2365.2434, -1135.5831, 1050.8826, 0.0}},
        {2,                     {1165.0944, -721.6221, 1089.0128,  180.0}},
        {HOUSE_INT_ID_REPAIR,   {-104.3197, 1268.5593, 1024.5990,  180.0}}

    },
    {
        {12,                    {2324.4883,-1149.5475,1050.7101,   0.0}},
        {9,                     {2317.8279,-1026.7283,1050.2178,   0.0}},
        {3,                     {1425.2622, -1481.1567, 106.9689,  90.0}},//самоделка
        {7,                     {225.6980,1021.5027,1084.0176,     0.0}},
        {HOUSE_INT_ID_REPAIR,   {324.8083,-433.0422,1000.9967,     0.0}}
    }
};

new interior_price[5] = {0, 100000, 250000, 500000, 1000000};

////////////////////////////////
#define MAX_HOUSE_RENTERS 5
#define MAX_HOUSE_UPGRADE 4
#define HOUSE_PICKUP_DEFAULT_ID       1318
#define MAX_HOUSE_UNDERGROUND_USE   5

enum // улучшения
{
    SUBSIDY,
    RENTERS,
    BASEMENT,
    UNDERGROUND
}

enum  // содежрание дома / гаража
{ // дом:
    MONEY,
    DRUGS,
    MATR,
    PATR, // гараж:
    REM_KIT = 0,
    CANISTR
}

#define INVALID_MYSQL_ID  0
#define INVALID_HOUSE_ID        -1
#define ALL_BUSY_SLOT_HOUSE     0
enum
{
    HOUSE_ID_SELECT = 1,
    //HOUSE_ID_EXCHANGE,
    HOUSE_ID_MENU,
    HOUSE_ID_RENT,
    HOUSE_ID_GPS,
    HOUSE_ID_SPAWN,
    HOUSE_ID_FAMILY,
    HOUSE_ID_GARDEN_CENTER,
    HOUSE_ID_GARDEN,
    HOUSE_ID_PANEL_STORE,
    HOUSE_ID_PANEL,
    HOUSE_ID_CARD_STORE,
    HOUSE_ID_UNDERGROUND_BOTS,
    HOUSE_ID_RESOURCES,
    HOUSE_ID_RESOURCES_BACK
}

enum house_info
{
    h_mysql_id,

    h_user_id,
    h_owner[MAX_PLAYER_NAME],

    Float:h_enter[4],
    // Float:h_exit[3],
    Float:c_pos[4],
    h_rent,
    h_value,
    h_int,
    h_lock,
    h_squar,
    Text3D:h_text,
    h_icon,
    // h_visible,
    /*h_area_enter,
    h_area_exit,*/
    h_pickup_enter,

    //garage
    //h_garage_count,
    h_garage_lock,
    h_garage_door,
    Float:h_garage_enter[4],
    h_garage_area[2],
    Text3D:h_garage_text,
    ////////////// attic's
    h_attic_lock,
    Text3D:h_attic_text,
    h_underground_lock,
    //h_attic_pickup,
    /// house upgrade
    h_improve[MAX_HOUSE_UPGRADE],
    // renter's
    h_r_user_id[MAX_HOUSE_RENTERS],
    h_r_price[MAX_HOUSE_RENTERS],
    h_r_days[MAX_HOUSE_RENTERS],
    //inv:
    //h_inventory_use,
    ///////////////////
    h_family_id,
    h_job_time,
    //аукцион auction
    h_auction_bet,
    h_auction_user_id,
    h_auction_time,
    h_mapping[96],
    h_mapping_id[H_ALL_MAPPING],
    h_mapping_timer,
    h_garage_map[50],
    h_garage_id[G_ALL_MAPPING],
    h_robbery,
    h_robbery_count,
    h_rob_house,
    h_rob_house_block,
    h_rob_house_signaling,
    h_owned_at,// В какую дату-время этим имуществом завладел кто-то
    h_paydays_received, //- Сколько пейдеев было начислено на это имущество
    h_gate,
    h_gate_timer,
    Float:h_gate_pos[4],
    Float:h_air_pos[4],
    h_boat_status,
    h_garden_items[28],
    h_panel_items,
    h_underground_player_use[MAX_HOUSE_UNDERGROUND_USE],
    h_delete,
    h_delete_time
}
new h_info[MAX_HOUSE][house_info],
    totalhouses,
    totalgatehouse,
    gate_house_idx[15];

new Float:FT_boat_pos[][4] =
{
    {1404.8771,-255.7975,-0.5038,180.0},
    {1389.9329,-255.3264,-0.5064,180.0},
    {1364.1569,-254.8517,-0.4505,180.0},
    {1350.3713,-254.3148,-0.1547,180.0},
    {1350.9528,-236.6710,-0.4867, 90.0},
    {1421.3016,-245.8557,-0.4759,270.0}
};

// система гаража
#define GARAGE_REPAIR_ID 100500
enum e_garage
{
    Float:g_pX,
    Float:g_pY,
    Float:g_pZ,
    Float:g_pR,
    Float:g_vX,
    Float:g_vY,
    Float:g_vZ,
    Float:g_vR
}
new g_info[3][e_garage] =
{
    {1327.0442,1561.8470,1010.9263,    280.0,   1340.5094,1561.8335,1010.6350, 80.0},
    {1370.8177,-20.7691,2000.8523,     270.0,   1389.6838,-29.2114,2000.5612, 0.0},
    {1403.4880,-23.1413,1000.9189,     90.0,    1371.4640,-23.0004,1000.8998, 270.0}
};
//
new
    house_door_exit_pickup[sizeof(h_ints)*MAX_HOUSE_INT],
    house_garage_exit_pickup[sizeof g_info],
    house_garage_exit_area[sizeof g_info];
