#define MAX_TRASH    25

enum E_T_INFO
{
    tPlayerUse,
    tArea,
    tObject,
    Float:tPos[6]
}

new TrashInfo[MAX_TRASH][E_T_INFO] = {
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2416.24096, -2577.92456, 13.43282, 0.00000, 0.00000, -180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2385.51758, -2265.81812, 13.32580, 0.00000, 0.00000, 45.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1268.91467, -1326.07141, 13.25970, 0.00000, 0.00000, -90.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1043.24683, 1052.81995, 9.93500, 0.00000, 0.00000, -56.82010}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1792.14575, -2053.17749, 13.31480, 0.00000, 0.00000, 180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2500.34058, -1455.28772, 23.77950, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1163.48669, -1781.62256, 13.35560, 0.00000, 0.00000, 180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {-1981.02246, 154.19279, 27.44070, 0.00000, 0.00000, -90.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2824.47070, 1281.13916, 10.51730, 0.00000, 0.00000, 90.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1416.61841, -1721.51965, 13.30740, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {-2040.90283, -83.53671, 35.07740, 0.00000, 0.00000, -90.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2693.09204, -2366.28784, 13.43080, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1106.94287, -1415.21167, 13.34940, 0.00000, 0.00000, 180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {297.31769, -1590.74756, 32.40290, 0.00000, 1.70000, 171.95990}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1800.06921, -1741.36279, 13.32520, 0.00000, 0.00000, 180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1034.37597, -1974.58850, 12.85109, 0.00000, 0.00000, 180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {-1988.86511, 1103.22217, 53.01080, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2025.92566, 1020.51398, 10.57880, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2179.17432, 1699.65662, 10.80330, 0.00000, 0.00000, -90.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1764.66797, -1936.30750, 13.33520, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {1503.01245, -1583.23914, 13.32580, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {-2231.70508, 262.33859, 35.09210, 0.00000, 0.00000, 0.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2367.14038, 2391.18726, 10.61770, 0.00000, 0.00000, 180.00000}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {-70.86250, -1139.93823, 0.86660, 0.00000, 0.00000, 155.87910}},
    {INVALID_PLAYER_ID, -1, INVALID_OBJECT_ID, {2275.42505, 598.01282, 7.51670, 0.00000, 0.00000, 0.00000}}
};

LoadTrash()
{
    for(new i = 0; i < MAX_TRASH; i++)
    {
        TrashInfo[i][tObject] = CreateDynamicObject(3035, TrashInfo[i][tPos][0], TrashInfo[i][tPos][1], TrashInfo[i][tPos][2], TrashInfo[i][tPos][3], TrashInfo[i][tPos][4], TrashInfo[i][tPos][5], -1, -1, -1, 120.0, 120.0);

        TrashInfo[i][tArea] = CreateDynamicSphere(TrashInfo[i][tPos][0], TrashInfo[i][tPos][1], TrashInfo[i][tPos][2], 2.5, -1, -1, -1);
        UpdateAreaInfo(TrashInfo[i][tArea], TYPE_TRASH, AREA_SUBTYPE_TRASH, i);
    }
    return 1;
}

PlayerUsesTrash(playerid)
{
    if(IsTDVisible(playerid) != -1) return 1;
    new trashbox = p_temp[playerid][trash_id];
    if(!(0 <= trashbox < sizeof(TrashInfo)))
    {
        p_temp[playerid][trash_id] = -1;
        return SendError(playerid, "Мусорный бак не определен, повторите попытку.");
    }
    /*
    if(TrashInfo[trashbox][tPlayerUse] != INVALID_PLAYER_ID)
        return SendError(playerid, "Мусорный бак уже кем-то используется.");
    */
    if(!ServerInfo[TrashSystem])
        return SendError(playerid, "Мусорки временно отключены и заработают через 1-2 дня.");

    //TrashInfo[trashbox][tPlayerUse] = playerid;
    ShowTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
    Interface_Show(playerid, EQUIPMENT_INVENTORY_TRASHBOX);
    return 1;
}

CMD:tptrash(playerid, params[])
{
    if(SRV_ID) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /tptrash [id]");
    new i = params[0];
    SetPlayerPos(playerid, TrashInfo[i][tPos][0], TrashInfo[i][tPos][1], TrashInfo[i][tPos][2]);
    return 1;
}
