new TentObjectIDx[MAX_PLAYERS];
new Float:TentPos[MAX_PLAYERS][3];

SetupTent(playerid, objectid, Float: x, Float: y, Float: z, Float: angle, object_world, object_int)
{
    if(GetFreeMarket() == -1) return SendError(playerid, "Количество переносных ларьков на сервере превышает допустимое.");

    TentPos[playerid][0] = x, TentPos[playerid][1] = y, TentPos[playerid][2] = z;

    TentIDx[playerid] = tent_idx[objectid == 1340 ? 0 : 1];

    new Float: ox, Float: oy, Float: oz, Float: orx, Float: ory, Float: orz;
    GetObjectOffset(x, y, z, 0.000000, 0.000007, angle - 180.0, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, objectid == 1340 ? -90.00000 : 0.00000, ox, oy, oz, orx, ory, orz);
    TentObjectIDx[playerid] = CreateDynamicObject(objectid, ox, oy, oz - (objectid == 1340 ? 0.0 : 1.0), orx, ory, orz, object_world, object_int);

    CreateMarket(playerid, TYPE_MARKET_PLAYER, ox+floatcos(angle+90, degrees), oy+floatsin(angle+90, degrees), oz);
    return 1;
}

ClearTent(playerid, type = 0)
{
    if(type == 1)
    {
        TentIDx[playerid] = -1;
        if(TentObjectIDx[playerid] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(TentObjectIDx[playerid]);
            TentObjectIDx[playerid] = INVALID_OBJECT_ID;
        }
        for(new i = 0; i < 3; i++) TentPos[playerid][i] = 0.0;
        return 1;
    }
    TentIDx[playerid] = -1;
    TentObjectIDx[playerid] = INVALID_OBJECT_ID;
    for(new i = 0; i < 3; i++) TentPos[playerid][i] = 0.0;
    return 1;
}

CMD:tent(playerid, params[])
{
    if(GetInventoryAmount(playerid, 679) == 0 && GetInventoryAmount(playerid, 680) == 0)
        return SendError(playerid, "У Вас нет переносного ларька.");
    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        return SendError(playerid, "Пользоваться переносным ларьком можно на улице.");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendError(playerid, "Доступно только с ног.");
    /*if(AntiDMZone(playerid))
        return SendError(playerid, "Вы не можете установить переносной ларек в \"Зеленой зоне\".");*/
    ShowPlayerDialog(playerid, D_TENT, DIALOG_STYLE_LIST, ""I"Переносной ларек", ""I"[1]"W" Установить\n"I"[2]"W" Забрать", "Далее", "Отмена");
    return 1;
}
