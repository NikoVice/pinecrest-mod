enum
{
    WALK_DEFAUL,
    WALK_NORMAL,
    WALK_GANGSTA,
    WALK_GANGSTA2,
    WALK_OLD,
    WALK_FAT_OLD,
    WALK_WUZI,
    WALK_LADY,
    WALK_LADY2,
    WALK_WHORE,
    WALK_WHORE2,
    WALK_DRUNK,
    WALK_ALL
}
new name_walk_style[WALK_ALL][] =
    {"Обычная", "Гражданская", "Гангстерская 1", "Гангстерская 2", "Старика", "Старухи", "Слепого", "Женская", "Деловая женская", "Секси женщина", "Секси женщина 2", "Пьяного"};
new name_anim_walk_style[WALK_ALL][] =
    {"WALK_player", "WALK_civi", "WALK_gang1", "WALK_gang2", "WALK_old",  "WALK_fatold", "Walk_Wuzi", "WOMAN_walknorm", "WOMAN_walkbusy", "WOMAN_walkpro", "WOMAN_walksexy", "WALK_drunk"};

CMD:walkstyle(playerid, params[])
{
    STRING_GLOBAL[0] = EOS;
    for(new i, j = sizeof(name_walk_style); i < j; i++) f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i+1, name_walk_style[i]);
    f(STRING_GLOBAL, "%s"I"[%d]"W" Важная информация", STRING_GLOBAL, sizeof(name_walk_style)+1);
    ShowPlayerDialog(playerid, D_STYLE_WALK, DIALOG_STYLE_LIST, ""I"Стили походки", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;
}
alias:walkstyle("ws", "stylewalk");

CMD:walk(playerid, params[])
{
    p_info[playerid][p_settings][STATUS_WALK_STYLE] ^= 1;
    if(!p_info[playerid][p_settings][STATUS_WALK_STYLE] && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) ClearAnimations(playerid);
    UpdatePlayerSetting(playerid);
    SendAccess(playerid, "Вы %s свой стиль походки %s.", !p_info[playerid][p_settings][STATUS_WALK_STYLE] ? "выключили" : "включили", name_walk_style[p_info[playerid][p_settings][WALK_STYLE_ID]]);
    return 1;
}
alias:walk("wl");

forward WalkAnimTimer(playerid);
public WalkAnimTimer(playerid)
{
    if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;
    if(GetPlayerWeapon(playerid) != 0) return SendError(playerid, "Стиль походки доступен без оружия в руках.");

    new keys, updown, leftright;
    GetPlayerKeys(playerid,keys,updown,leftright);

    new walk_id = p_info[playerid][p_settings][WALK_STYLE_ID];
    KillTimer(p_temp[playerid][walk_time]);
    if((!IsPlayerMobile(playerid) &&
            ((keys & KEY_WALK && updown & KEY_UP) ||
            (keys & KEY_WALK && updown & KEY_DOWN)  ||
            (keys & KEY_WALK && leftright & KEY_LEFT) ||
            (keys & KEY_WALK && leftright & KEY_RIGHT)))
        || (IsPlayerMobile(playerid) && updown != 0)
    )
    {
        ApplyAnimation(playerid,"PED", name_anim_walk_style[walk_id], 4.1, 1, 1, 1, 1, 0, 1);
        ApplyAnimation(playerid,"PED", name_anim_walk_style[walk_id], 4.1, 1, 1, 1, 1, 1, 0);
        p_temp[playerid][walk_time] = SetTimerEx("WalkAnimTimer",200,0,"d",playerid);
    }
    else ApplyAnimation(playerid,"PED", name_anim_walk_style[walk_id], 4.0,0,0,0,0,1);
    return 1;
}

PressKeyWalk(playerid, newkeys, oldkeys)
{
    if (((newkeys & KEY_WALK && newkeys & KEY_UP) || (newkeys & KEY_WALK && newkeys & KEY_DOWN) || (newkeys & KEY_WALK && newkeys & KEY_LEFT) || (newkeys & KEY_WALK && newkeys & KEY_RIGHT))
        || ((oldkeys & KEY_WALK && newkeys & KEY_UP) || (oldkeys & KEY_WALK && newkeys & KEY_DOWN) || (oldkeys & KEY_WALK && newkeys & KEY_LEFT) || (oldkeys & KEY_WALK && newkeys & KEY_RIGHT))
        || ((newkeys & KEY_WALK && oldkeys & KEY_UP) || (newkeys & KEY_WALK && oldkeys & KEY_DOWN) || (newkeys & KEY_WALK && oldkeys & KEY_LEFT) || (newkeys & KEY_WALK && oldkeys & KEY_RIGHT)))
    p_temp[playerid][walk_time] = SetTimerEx("WalkAnimTimer",200,0,"d",playerid);
}

static
    LastUpDown[MAX_PLAYERS],
    LastLeftRight[MAX_PLAYERS];

public OnPlayerUpdate(playerid)
{
    if(p_info[playerid][p_settings][STATUS_WALK_STYLE] && IsPlayerMobile(playerid) && GetPlayerState(playerid) == PLAYER_STATE_ONFOOT && !p_info[playerid][d_start_addiction])
    {
        new keys, ud, lr, walk_id = p_info[playerid][p_settings][WALK_STYLE_ID];
        GetPlayerKeys(playerid, keys, ud, lr);

        if(LastUpDown[playerid] != ud || LastLeftRight[playerid] != lr)
        {
            if(ud < 100 && ud != 0 && ud > -100 || lr < 100 && lr != 0 && lr < -100)
            {
                ApplyAnimation(playerid,"PED", name_anim_walk_style[walk_id], 6.0, 1, 1, 1, 1, 0, 1);
                p_temp[playerid][walk_time] = SetTimerEx("WalkAnimTimer",200,0,"d",playerid);
            }
        }
        LastUpDown[playerid] = ud;
        LastLeftRight[playerid] = lr;
    }
    #if defined walkstyle_OnPlayerUpdate
        return walkstyle_OnPlayerUpdate(playerid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate walkstyle_OnPlayerUpdate
#if defined walkstyle_OnPlayerUpdate
    forward walkstyle_OnPlayerUpdate(playerid);
#endif
