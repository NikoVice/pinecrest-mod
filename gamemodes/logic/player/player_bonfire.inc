
CreateBonfire(playerid)
{
    if(GetInventoryAmount(playerid, 694) < 1)
        return SendError(playerid, "У Вас нет спичек.");
    if(GetInventoryAmount(playerid, 650) < 2)
        return SendError(playerid, "У Вас нет древесины.");
    if(GetPlayerVirtualWorld(playerid) != 0 || GetPlayerInterior(playerid) != 0)
        return SendError(playerid, "Зажечь костер можно только на улице.");
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
        return SendError(playerid, "Доступно только с ног.");
    if(AntiDMZone(playerid))
        return SendError(playerid, "Вы не можете зажечь костер в \"Зеленой зоне\".");

    DoAction(playerid, "Спички в правой руке.");
    MeAction(playerid, "плавным движением руки пытается поджечь дрова");
    DoAction(playerid, "Дрова лежат на земле.");
    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,0,1,1,1,1);

    SetTimerEx("timer_CreateBonfire", 2000, false, "d", playerid);
    return 1;
}


forward timer_CreateBonfire(playerid);
public timer_CreateBonfire(playerid)
{
    if(GivePlayerInventory(playerid, 694, -1))
    {
        new chance = random(6);
        if(chance >= 4)
        {
            SendInfo(playerid, "Не удалось зажечь огонь: %s.", chance == 4 ? "ветер затушил спичку" : chance == 4 ? "спичка сырая" : "спичка сломалась");
        }
        else
        {
            GivePlayerInventory(playerid, 650, -2);
            new Float:x, Float:y, Float:z, Float:angle;
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, angle);

            x += (1 * floatsin(-angle, degrees));
            y += (1 * floatcos(-angle, degrees));

            p_temp[playerid][bonfire_object] = CreateDynamicObject(19632, x, y, z-1.0, 0.0,0.0, angle, -1, -1, -1);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Костер\nЗаж(-ег/-гла): "I"%s", get_name(playerid));
            p_temp[playerid][bonfire_label] = CreateDynamic3DTextLabel(STRING_GLOBAL, -1, x, y, z, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1);
            p_temp[playerid][bonfire_timer] = 180;

            SendAccess(playerid, "Вы зажгли костер.");
        }
    }
}

DestroyBonfire(playerid, type = 0)
{
    if(p_temp[playerid][bonfire_label] != INVALID_3DTEXT_ID)
    {
        DestroyDynamic3DTextLabel(p_temp[playerid][bonfire_label]);
        p_temp[playerid][bonfire_label] = INVALID_3DTEXT_ID;
    }
    if(p_temp[playerid][bonfire_object] != INVALID_OBJECT_ID)
    {
        DestroyDynamicObject(p_temp[playerid][bonfire_object]);
        p_temp[playerid][bonfire_object] = INVALID_OBJECT_ID;
    }
    p_temp[playerid][bonfire_timer] = 0;
    if(type == 1) SendInfo(playerid, "Костер потух.");
    if(type == 2)
    {
        MeAction(playerid, "потушил костер");
        DoAction(playerid, "костер потушен.");
    }
    return 1;
}

CMD:bonfire(playerid, params[])
{
    ShowPlayerDialog(playerid, D_BONFIRE_MENU, DIALOG_STYLE_LIST, ""I"Огонь", ""I"[1]"W" Зажечь\n"I"[2]"W" Затушить\n"I"[3]"W" Приготовить сэндвич\n"I"[4]"W" Приготовить бургер", "Далее", "Отмена");
    return 1;
}
/*
CMD:dfire(playerid, params[])
{
    if(p_info[playerid][admin] < 3) return 1;
    foreach(new i: Player)
    {
        if(HookahArea[i] == -1) continue;
        if(IsPlayerInRangeOfPoint(playerid, 5.0, HookahPos[i][0], HookahPos[i][1], HookahPos[i][2]))
        {
            ClearHookah(i, 1);
            break;
        }
    }
    return 1;
}
*/
