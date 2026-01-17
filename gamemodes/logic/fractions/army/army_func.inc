#define MAX_ARMY_POST 8

enum e_post
{
    Float:Post_X,
    Float:Post_Y,
    Float:Post_Z,
    Name[64],
    Area,
    Text3D:Post3D,
    PlayerID,
}
new post_info[MAX_ARMY_POST][e_post] =
{
    {2720.8401,-2507.2444,13.4869, "КПП #1", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2720.7222,-2408.7373,13.4609, "КПП #2", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2757.4070,-2530.3005,17.8729, "Оружейный завод", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2766.4414,-2432.5859,13.6484, "Склад #1", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2766.8518,-2482.7346,13.6484, "Склад #2", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2746.5244,-2461.2288,13.6667, "Штаб", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2725.5935,-2516.4873,29.6921, "Вышка #1", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID},
    {2726.3738,-2387.1548,29.6921, "Вышка #2", -1, INVALID_3DTEXT_ID, INVALID_PLAYER_ID}
};

Post_System_OnGameModeInit()
{
    for(new i; i < MAX_ARMY_POST; i++)
    {
        post_info[i][PlayerID] = INVALID_PLAYER_ID;
        post_info[i][Area] = CreateDynamicSphere(post_info[i][Post_X],post_info[i][Post_Y], post_info[i][Post_Z], 1.0, 0, 0, -1);
        UpdateAreaInfo(post_info[i][Area], TYPE_ARMY_POST, AREA_SUBTYPE_INVALID_ID, i);
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof STRING_GLOBAL, "Пост: "W"%s\n{"#cGREEN"}Свободен", post_info[i][Name]);
        post_info[i][Post3D] = CreateDynamic3DTextLabel(STRING_GLOBAL,COLOR_MAIN,post_info[i][Post_X],post_info[i][Post_Y],post_info[i][Post_Z],25.0,INVALID_PLAYER_ID,INVALID_PLAYER_ID,0,0,0,-1,100.0);
    }
}

Post_System_EnterArea(playerid, i)
{
    if(p_temp[playerid][army_post] != -1) return 1;
    post_info[i][PlayerID] = playerid;
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof STRING_GLOBAL, "Пост: "W"%s\n{"#cLIGHTRED"}%s", post_info[i][Name], get_name(playerid));
    UpdateDynamic3DTextLabelText(post_info[i][Post3D], -1, STRING_GLOBAL);
    p_temp[playerid][army_post] = i;
    p_temp[playerid][army_time] = 0;
    return 1;
}

Post_System_LeaveArea(playerid, i)
{
    post_info[i][PlayerID] = INVALID_PLAYER_ID;
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""W"%s\n{"#cGREEN"}Свободен", post_info[i][Name]);
    UpdateDynamic3DTextLabelText(post_info[i][Post3D], -1, STRING_GLOBAL);
    p_temp[playerid][army_post] = -1;
    p_temp[playerid][army_time] = 0;
}

CMD:posts(playerid, params[])
{
    if(!army(playerid))
        return 1;
    STRING_GLOBAL = "[#] Название\tСтатус\n";
    for(new i = p_info[playerid][member] == NATIONAL_GUARD ? 0 : 9; i < MAX_ARMY_POST; i++)
    {
        if(p_info[playerid][member] == NATIONAL_GUARD && i == 9) break;
        if(post_info[i][PlayerID] != INVALID_PLAYER_ID) f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t{"#cLIGHTRED"}}%s\n", STRING_GLOBAL, i+1, post_info[i][Name], get_name(post_info[i][PlayerID]));
        else f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t{"#cGREEN"}Свободен\n", STRING_GLOBAL, i+1, post_info[i][Name]);
    }
    ShowPlayerDialog(playerid, D_ARMY_POST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Выберите пост", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

new pickup_gun_factory;

new GunFactoryAreasLoad[8];
new GunFactoryAreasUnload[2];

new bool:GunFactoryWorkTableStat[8];

new Float:GunFactoryrWorkCPs[10][3] = {
    {1839.1101,-2103.7122,2001.5852},
    {1835.4397,-2103.7070,2001.5852},
    {1828.6132,-2103.7134,2001.5852},
    {1825.0178,-2103.7063,2001.5852},
    {1824.9716,-2098.7939,2001.5852},
    {1828.5626,-2098.7881,2001.5852},
    {1835.4169,-2098.7952,2001.5852},
    {1839.0266,-2098.7878,2001.5852},
    {1855.4067,-2106.2534,2001.5852},
    {1855.4067,-2096.2322,2001.5852}
};

LoadGunFactory()
{
    pickup_gun_factory = CreatePickup(1275, 23, 1825.3202,-2116.5701,2001.5852,1); // Оружейный завод (Устройство);
    CreateDynamic3DTextLabel("<< Устройство на работу >>", COLOR_MAIN, 1825.3202,-2116.5701,2001.5852, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

    for(new i; i < 10; i++)
    {
        if(i < 8)
        {
            GunFactoryAreasLoad[i] = CreateDynamicSphere(GunFactoryrWorkCPs[i][0], GunFactoryrWorkCPs[i][1], GunFactoryrWorkCPs[i][2], 0.5, 1, 1, -1);
            UpdateAreaInfo(GunFactoryAreasLoad[i], TYPE_WORK_GUN_FACTORY, AREA_SUBTYPE_INVALID_ID, i);
        }
        else
        {
            GunFactoryAreasUnload[i-8] = CreateDynamicSphere(GunFactoryrWorkCPs[i][0], GunFactoryrWorkCPs[i][1], GunFactoryrWorkCPs[i][2], 1.5, 1, 1, -1);
        }
    }
    return 1;
}

forward OnPlayerGunFactoryReady(playerid, locat);
public OnPlayerGunFactoryReady(playerid, locat)
{
    GunFactoryWorkTableStat[locat] = false;
    if(playerid == INVALID_PLAYER_ID) return 1;
    if(!IsPlayerInDynamicArea(playerid, GunFactoryAreasLoad[locat])) return SendError(playerid, "Вы отошли от станка.");
    p_temp[playerid][GunFactoryLocat] = 0;
    if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
    if(IsPlayerAttachedObjectSlotUsed(playerid, 2)) RemovePlayerAttachedObject(playerid, 2);
    Fix_TogglePlayerControllable(playerid, true);
    p_temp[playerid][GunFactoryCheck] ^= 1;
    ClearAnimations(playerid);
    ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.1, 1, 0, 0, 1, 1);
    //SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    SetPlayerAttachedObject(playerid, 1, 2358, 6, 0.0, 0.10, -0.2, -110.0, 0.0, 78.0, 1.000000, 1.000000, 1.000000);
    SendMes(playerid, COLOR_SEA_WAVE, "Вы изготовили оружие. Отнесите их на склад.");

    new max_distance = 100000;
    new warehouse_id = -1;
    new here_distance;
    for(new i = 8; i < 10; i++)
    {
        here_distance = floatround(GetPlayerDistanceFromPoint(playerid, GunFactoryrWorkCPs[i][0], GunFactoryrWorkCPs[i][1], GunFactoryrWorkCPs[i][2]));
        if(here_distance < max_distance)
        {
            warehouse_id = i;
            max_distance = here_distance;
        }
    }
    if(max_distance == -1 || warehouse_id == -1) return 1;

    SetPlayerGPS(playerid, GunFactoryrWorkCPs[warehouse_id][0], GunFactoryrWorkCPs[warehouse_id][1], GunFactoryrWorkCPs[warehouse_id][2], 1.5);
    SendMes(playerid, COLOR_BLUE, "Место обозначено на GPS навигаторе.");
    return 1;
}