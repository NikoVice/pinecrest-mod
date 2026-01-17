#define MAX_RESOURCES_HOUSE         1000

new totalresourceshouse;
new cotton_warehouse = 100;
new linen_warehouse = 100;

enum E_RESOURCES_HOUSE_INFO
{
    rhIDx, // ID из базы;
    rhDay, // Количество дней;
    rhHouseIDx, // ID дома из базы;
    rhTime, // Время до выращивания;
    rhObject[2], // ID объекта;
    rhArea, // Арена;
    Float:rhPos[6], // Координаты;
    Text3D:rhText // 3D-текст;
};
new ResourcesHouseInfo[MAX_RESOURCES_HOUSE][E_RESOURCES_HOUSE_INFO];