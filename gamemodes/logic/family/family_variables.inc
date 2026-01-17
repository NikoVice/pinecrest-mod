/*
    Family System 2020
    Author: Vip_Uzer
*/

#define MAX_FAMILY          500
#define MAX_FAMILY_RANG     10
#define MAX_FAMILY_MEMBERS  10
#define COUNT_EXP_FAMILY    25
#define INVALID_FAMILY_ID   -1

//#define INVALID_CRIMINAL_ZONE_ID      -1
#define MAX_FAMILY_ZONE             100
#define FAMILY_ZONE_NONE            0
#define FAMILY_ZONE_PREPARATION     1
#define FAMILY_ZONE_CAPTURE         2

#define MAX_CAPTURE_FAMILY_ZONE     5

#define IsInFamilyAllowed(%0)       FamilyData[%0][fCaptureAllowed]

new count_family_zone;
enum fZoneInfo
{
    fID,
    Float:fCoords[4],
    fFamilyOwner,
    fColorID,
    fArea
}
new FamilyZone_Info[MAX_FAMILY_ZONE][fZoneInfo];

enum e_fCapture_Info {
    fFamilyZoneID,
    fFamilyID[2],
    fCount[2],
    fTime,
    fStatus
}
new fCapture_Info[MAX_CAPTURE_FAMILY_ZONE][e_fCapture_Info];

new FAMILY_RANG[MAX_FAMILY][MAX_FAMILY_RANG][16];
#define GetNameRangFamily(%0) FAMILY_RANG[p_temp[%0][family_game_id]][p_info[%0][family_rang]-1]
#define GetPlayerFamilyID(%0) p_temp[%0][family_game_id]
#define GetFamilyRang(%0) p_info[%0][family_rang]

enum
{
    F_INVITE,
    F_UNINVITE,
    F_VEHICLE,
    F_MUTE,
    F_UNMUTE,
    F_WARN,
    F_UNWARN,
    F_SET_RANG,
    F_LOG,
    F_BLACKLIST,
    F_SKINS,
    F_NOTIFY,
    F_INVENTORY,
    F_CAPTURE,
    F_FREE_SLOT2,
    F_ALL_COUNT
}

enum
{
    BLACKLIST_OFFLINE_ADD = 1,
    BLACKLIST_OFFLINE_CLEAR,
    BLACKLIST_CLEAR
}

#define MAX_FAMILY_CONTRACTS 5
#define MAX_FAMILY_VEHICLES 12

#define MAX_FAMILY_SKINS 15
enum e_family
{
    fMysqlID,
    fName[21],
    fColorID,
    fOwnerID,
    fCreatingDate[12],
    fMembersCount,
    fHouseID,
    fVehicleID[MAX_FAMILY_VEHICLES],
    fMoney,
    fLevel,
    fExp,
    fSeasonExp,
    fTypeID,
    fOffice,
    fContractProgress[MAX_FAMILY_CONTRACTS],
    fSalaryRang[MAX_FAMILY_RANG],
    fSettingRang[F_ALL_COUNT],
    fSkinID[MAX_FAMILY_SKINS],
    fSkinMan[MAX_FAMILY_RANG],
    fSkinWoman[MAX_FAMILY_RANG],
    fNotifyAntiFlood,
    fCaptureAllowed,
    fCaptZoneCount,
    Text3D:fLabel,
}
new FamilyData[MAX_FAMILY][e_family], //
    family_count = 0,//кол-во семей.
    FAMILY_TYPE_NAME[][] = {"Группировка", "Семья", "Компания"},
    FAMILY_COLORS[22] = {0xFFFFFFFF, 0xFFD39BFF, 0xFFFF00FF, 0x54FF9FFF, 0x98F5FFFF, 0x269BD8FF, 0xE75480FF, 0x00FFFFFF, 0xF5DEB3FF, 0x000CFFFF, 0x2A52BEFF, 0x3FDA07FF, 0xFFFFFFFF, 0xFF6347FF, 0xFF6347FF, 0x00C0FFFF, 0xFFFF00FF, 0xC3C3C3FF, 0xFFCC33FF, 0x33CC00FF, 0xFF8300FF, 0xA9C4E4FF},
    FAMILY_DIALOG_COLORS[22][12] = {"FFFFFF", "FFD39B", "FFFF00", "54FF9F", "98F5FF", "269BD8", "E75480", "00FFFF", "F5DEB3", "000CFF", "2A52BE", "3FDA07", "FFFFFF", "FF6347", "FF6347", "00C0FF", "FFFF00", "C3C3C3", "FFCC33", "33CC00", "FF8300", "A9C4E4"},
    FamilyPickup[4],
    FamilyGarageArea[2],
    CREATE_FIMILY;//пикап создания семьи в мэрии

enum
{//Контракты
    CONTRACT_FAMILY_ID_NONE = -1,
    CONTRACT_FAMILY_ID_RAILWAY,
    CONTRACT_FAMILY_ID_CAR_FACTORY,
    CONTRACT_FAMILY_ID_FARM,
    CONTRACT_FAMILY_ID_CONSTRUCTION,
    CONTRACT_FAMILY_ID_SPACE,
    CONTRACT_FAMILY_ID_ROBBER,
    CONTRACT_FAMILY_ID_THEFT_CAR,
    CONTRACT_FAMILY_ID_GHOUSES,
    CONTRACT_FAMILY_ID_PIZZABOY,
    CONTRACT_FAMILY_ID_TAXI,
    CONTRACT_FAMILY_ID_BUS,
    CONTRACT_FAMILY_ID_MECHANIC,
    CONTRACT_FAMILY_ID_ROADMAN,
    CONTRACT_FAMILY_ID_COLLECTOR,
    CONTRACT_FAMILY_ID_FIRE,
    CONTRACT_FAMILY_ID_TRUCKER,
    CONTRACT_FAMILY_ID_TRAIN,
    CONTRACT_FAMILY_ID_TRAM,
    CONTRACT_FAMILY_ID_PILOT,
    CONTRACT_FAMILY_ID_PANEL,
    CONTRACT_FAMILY_ID_ELECTRIC,
    CONTRACT_FAMILY_ID_OIL,
    CONTRACT_FAMILY_ID_THUNTER,
    CONTRACT_FAMILY_ID_FISH,
    CONTRACT_FAMILY_ID_HUNTER,
    CONTRACT_FAMILY_ID_ALL
}
enum e_FAMILY_CONTRACTS
{
    fID, // тип
    fName[64], // название
    fDescription[160], // описание
    fProgress, // очков для прохождения
    fMoney, // деньги
    fExp, // выдается за прохождение
    fTime // время на прохождение
}
new CONRACT_FAMILY_INIT[][e_FAMILY_CONTRACTS] = {
    {CONTRACT_FAMILY_ID_RAILWAY, "Железнодорожный завод", "Перенести 50 металла, древесины или рельс работая на железнодорожном заводе", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_CAR_FACTORY, "Автомобильный завод", "Выполнить 50 этапов сборки работая на автомобильном заводе", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_FARM, "Ферма", "Выполнить 50 задач работая ферме", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_CONSTRUCTION, "Строитель", "Доставить 50 стройматериалов на стройке", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_SPACE, "Космонавт", "Добыть 50 ископаемых в космосе", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_ROBBER, "Грабитель", "Вынести 50 предметов из дома работая грабителем", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_THEFT_CAR, "Автоугон", "Угнать 50 автомобилей работая на автоугоне", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_GHOUSES, "Работник теплицы", "Сорвать 50 цветов в тепличном комплексе", 50, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_PIZZABOY, "Развозчик пиццы", "Выполнить 25 заказов работая развозчиком пиццы", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_TAXI, "Водитель такси", "Доставить 25 клиентов работая водителем такси", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_BUS, "Водитель автобуса", "Проехать 25 маршрутов работая водителем автобуса", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_MECHANIC, "Автомеханик", "Починить 25 автомобилей работая автомехаником", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_ROADMAN, "Ремонтник дорог", "Перенести 50 мешков с мусором работая ремонтником дорог", 50, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_COLLECTOR, "Инкассатор", "Выполнить 25 заказов работая инкассатором", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_FIRE, "Пожарный", "Ликвидировать 25 пожаров работая пожарным", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_TRUCKER, "Дальнобойщик", "Выполнить 25 заказов работая дальнобойщиком", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_TRAIN, "Машинист поезда", "Проехать 25 рейсов работая машинистом поезда", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_TRAM, "Водитель трамвая", "Проехать 25 рейсов работая водителем трамвая", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_PILOT, "Пилот", "Пролететь 25 рейсов работая пилотом", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_PANEL, "Ремонтник панелей", "Отремонтировать 25 солнечных панелей работая ремонтником солнечных панелей", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_ELECTRIC, "Электрик", "Отремонтировать или ограбить 25 ЛЭП работая электриком", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_OIL, "Нефтяник", "Выполнить 25 заказов работая нефтяником", 25, 30000, 100, 60},
    {CONTRACT_FAMILY_ID_OIL, "Кладоискатель", "Найти 25 сокровищ", 25, 15000, 100, 30},
    {CONTRACT_FAMILY_ID_FISH, "Рыболов", "Поймать на пирсе 25 рыб", 25, 15000, 50, 30},
    {CONTRACT_FAMILY_ID_HUNTER, "Охотник", "Убить возле домика охотника 25 оленей", 25, 15000, 50, 30}
};
enum e_CONTRACT_FAMILY
{
    fID,
    fTime
}
new FamilyContractData[MAX_FAMILY_CONTRACTS][e_CONTRACT_FAMILY];