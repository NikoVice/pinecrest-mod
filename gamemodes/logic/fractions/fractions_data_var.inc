/*
    Author: Vip_Uzer
    Flin RolePlay (c) 2021
*/

#define MAX_FRACTIONS_VEHICLES 15
#define MAX_FRACTIONS_RANGS 10
enum
{
    fwMoney,
    fwDrugs,
    fwMate,
    fwPatron,
    fwFuel,
    fwRemp,
    fwHeal,
    fwMask,

    F_WAREHOUSE_ALL
}

enum
{
    fWareHouseStatus,           // Состояние доступа к складу
    fDoorStatus,                // Состояние доступа к дверям фракции
    fDressingStatus,            // Состояние доступа к пикапу одежды
    fFreezeCapture,             // Состояние заморозки фракции (Ghetto/Mafia)

    F_SETTINGS_ALL
}

enum {
    fVirtualWorld,             // Виртуальный мир
    fInterior,                 // Интерьер

    F_FIELD_ALL
}

enum {
    F_WOMAN_SKIN = 1,
    F_MAN_SKIN,
}

enum e_FractionsData
{
    fName[36],                                      // Название
    fType,                                          // Тип
    fCategory,                                      // Категория

    Float:fSpawnPos[4],                             // Место спавна
    Float:fDressingPos[3],                          // Пикап раздевалки
    Float:fWarehousePos[3],                         // Место склада
    fBaseField[F_FIELD_ALL],                        // Параметры базы в вирутальном мире/интерьере

    Float:fUnloadingPos[3],                         // Место разгрузки
    fUnloadingField[F_FIELD_ALL],                   // Параметры места разгрузки в вирутальном мире/интерьере

    fWomanSkin[MAX_FRACTIONS_RANGS],                        // Женские скины
    fManSkin[MAX_FRACTIONS_RANGS],                          // Мужские скины
    fPay[MAX_FRACTIONS_RANGS],                              // Зарплата
    fWarehouse[F_WAREHOUSE_ALL],                    // Состояние склада

    // Настройки
    fSettings[F_SETTINGS_ALL],                      // Настройки

    // Транспорт
    fVehModelsID[MAX_FRACTIONS_VEHICLES],           // ID моделей т/с
    fVehModelMaxCount[MAX_FRACTIONS_VEHICLES],      // Максимальное количество модели т/с
    fVehModelUseCount[MAX_FRACTIONS_VEHICLES],      // Количество используемых моделей т/с
    fVehAccessRank[MAX_FRACTIONS_VEHICLES],         // Ранг доступа к модели т/с
    Float:fVehSpawnPos[4],                          // Место спавна т/с
    fVehSpawnField[F_FIELD_ALL],                    // Параметры места спавна в вирутальном мире/интерьере

    // Не хранятся в базе
    Text3D:fWarehouseLabel,     // 3Dтекст: склад - f_3dtext
    fWarehouseCP,               // 3Dтекст: склад - f_cp
    Text3D:fUnloadingLabel,     // 3Dтекст: разгрузка
    fUnloadingPickup,           // Пикап: разгрузка
    fVehPickup,                 // Пикап: спавн автомобиля
    Text3D:fVehLabel,           // 3Dтекст: спавн автомобиля
    fDressingPickup,            // Пикап: раздевалка
};

new FractionsData[MAX_FRACTIONS][e_FractionsData];
new FractionsData_NameRang[MAX_FRACTIONS][MAX_FRACTIONS_RANGS][24]; // Названия рангов

#define GetFractionName(%0) FractionsData[%0][fName]

#define GetFractionWarehouse(%0,%1) FractionsData[%0][fWarehouse][%1]

#define SetFractionSettings(%0,%1,%2) FractionsData[%0][fSettings][%1] = %2,SaveFractionSettings(%0),UpdateInfoFractionWarehouse(%0)
#define GetFractionSettings(%0,%1) FractionsData[%0][fSettings][%1]

#define GetPlayerFractionRangName(%0) FractionsData_NameRang[p_info[%0][member]][p_info[%0][rang]-1]

#define GetFractionPay(%0) FractionsData[p_info[%0][member]][fPay][p_info[%0][rang]-1]

enum {
    F_WAREHOUSE,
    F_UNLOADING,
    F_VEHICLE_SPAWN,
    F_DRESSING,

    F_INIT_ALL
}

enum {
    FACTION_TYPE_NONE,
    FACTION_TYPE_GOS,
    FACTION_TYPE_CRIMINAL,
    FACTION_TYPE_SNN
};
enum {
    FACTION_CATEGORY_NONE,
    FACTION_CATEGORY_PD,
    FACTION_CATEGORY_FBI,
    FACTION_CATEGORY_MAFIA,
    FACTION_CATEGORY_GANG,
    FACTION_CATEGORY_MEDIC,
    FACTION_CATEGORY_ARMY,
    FACTION_CATEGORY_SNN,
    FACTION_CATEGORY_MAYOR,
    FACTION_CATEGORY_PRISON,
    FACTION_CATEGORY_LICENSE,
    FACTION_CATEGORY_BIKER
};
