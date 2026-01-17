new WarPlaneUse[MAX_PLAYERS];
new WarPlaneUseItems[MAX_PLAYERS];

enum WARPLANE_INFO
{
    WarPlaneStatus,
    WarPlaneContent[7],
    WarPlaneObject,
    WarPlaneTimer,
    Text3D:WarPlaneText,
    WarPlaneCheckpoint,
    Float:WarPlanePos[6]
};

new WarPlaneInfo[][WARPLANE_INFO] = {
    {0, {0, 0, 0, 0, 0, 0, 0}, INVALID_OBJECT_ID, 0, Text3D:INVALID_3DTEXT_ID, -1, {-1295.63147, 2694.40649, 54.96660, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, INVALID_OBJECT_ID, 0, Text3D:INVALID_3DTEXT_ID, -1, {-220.99135, 2603.71069, 67.61420, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, INVALID_OBJECT_ID, 0, Text3D:INVALID_3DTEXT_ID, -1, {582.93719, 1669.92908, 11.92360, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, INVALID_OBJECT_ID, 0, Text3D:INVALID_3DTEXT_ID, -1, {345.32404, 869.93701, 25.30190, 0.00000, 0.00000, 90.00000}},
    //{0, {0, 0, 0, 0, 0, 0, 0}, INVALID_OBJECT_ID, 0, Text3D:INVALID_3DTEXT_ID, -1, {-524.25952, 2596.35693, 58.32280, 0.00000, 0.00000, -45.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, INVALID_OBJECT_ID, 0, Text3D:INVALID_3DTEXT_ID, -1, {1.96433, 1528.70654, 17.66980, 0.00000, 0.00000, 0.00000}}
};

new WarPlaneIDx = -1;
new WarPlaneZone = -1;

GetFreeWarPlaneID()
{
    new warplane_checked = -1;
    for(new i = sizeof(WarPlaneInfo)-1; i != -1; i--)
    {
        warplane_checked = random(sizeof(WarPlaneInfo)-1);
        if(WarPlaneInfo[warplane_checked][WarPlaneStatus] == 0) return warplane_checked;
    }
    return -1;
}

CreateWarPlane()
{
    if(WarPlaneIDx != -1) return 1;
    new idx = GetFreeWarPlaneID();

    STRING_GLOBAL[0] = EOS;
    for(new i = 1; i < MAX_FRACTIONS; i++)
    {
        if(i == 5 || i > 6 && i < 15 || i == 20 || i == 23)
        {
            if(idx == -1) SendFractionMessage(i, 0x33CC66FF, "[F] [Военный самолет]: Падение военного самолета занимает две с половиной минуты.");
            else
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] [Военный самолет]: Военный самолет номер %d падает на землю.", idx);
                SendFractionMessage(i, 0x33CC66FF, STRING_GLOBAL);
                SendFractionMessage(i, 0x33CC66FF, "[F] [Военный самолет]: Падение военного самолета занимает две с половиной минуты.");
                SendFractionMessage(i, 0x33CC66FF, "[F] [Военный самолет]: Примерное местоположение военного самолета отмечено на карте.");
            }
        }
    }

    if(idx == -1) return 1;

    WarPlaneInfo[idx][WarPlaneStatus] = 0;

    WarPlaneInfo[idx][WarPlaneContent][0] = RandomEx(20000, 200000);
    WarPlaneInfo[idx][WarPlaneContent][1] = RandomEx(20000, 200000);
    WarPlaneInfo[idx][WarPlaneContent][2] = RandomEx(1000, 100000);
    WarPlaneInfo[idx][WarPlaneContent][3] = RandomEx(5, 10);
    WarPlaneInfo[idx][WarPlaneContent][4] = RandomEx(5, 10);
    WarPlaneInfo[idx][WarPlaneContent][5] = RandomEx(5, 10);
    WarPlaneInfo[idx][WarPlaneContent][6] = RandomEx(5, 10);

    if(WarPlaneInfo[idx][WarPlaneObject] != INVALID_OBJECT_ID) DestroyDynamicObject(WarPlaneInfo[idx][WarPlaneObject]);
    WarPlaneInfo[idx][WarPlaneObject] = CreateDynamicObject(1683, WarPlaneInfo[idx][WarPlanePos][0], WarPlaneInfo[idx][WarPlanePos][1], WarPlaneInfo[idx][WarPlanePos][2]+250.000000, WarPlaneInfo[idx][WarPlanePos][3], WarPlaneInfo[idx][WarPlanePos][4], WarPlaneInfo[idx][WarPlanePos][5], -1, -1, -1, 120.0, 120.0);

    WarPlaneInfo[idx][WarPlaneTimer] = 1049;

    WarPlaneIDx = idx;
    WarPlaneZone = GangZoneCreate(WarPlaneInfo[idx][WarPlanePos][0]-95, WarPlaneInfo[idx][WarPlanePos][1]-80, WarPlaneInfo[idx][WarPlanePos][0]+70, WarPlaneInfo[idx][WarPlanePos][1]+85);

    foreach(new i: Player)
    {
        if(!gang(i) && !mafia(i) && !biker(i) && !army(i)) continue;
        GangZoneShowForPlayer(i, WarPlaneZone, 0xFFFFFF65);
        GangZoneFlashForPlayer(i, WarPlaneZone, COLOR_RED);
    }

    new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;

    GetDynamicObjectPos(WarPlaneInfo[idx][WarPlaneObject], x, y, z);
    GetDynamicObjectRot(WarPlaneInfo[idx][WarPlaneObject], rx, ry, rz);
    MoveDynamicObject(WarPlaneInfo[idx][WarPlaneObject], x, y, z-250, 1.69, rx, ry, rz);
    return 1;
}

CheckWarPlane()
{
    if(WarPlaneIDx == -1) return 1;

    new idx = WarPlaneIDx;

    WarPlaneInfo[idx][WarPlaneTimer]--;

    if(WarPlaneInfo[idx][WarPlaneTimer] == 900)
    {
        STRING_GLOBAL[0] = EOS;
        for(new i = 1; i < MAX_FRACTIONS; i++)
        {
            if(i == 5 || i > 6 && i < 15 || i == 20 || i == 23)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] [Военный самолет]: Военный самолет номер %d упал на землю.", idx);
                SendFractionMessage(i, 0x33CC66FF, STRING_GLOBAL);
                SendFractionMessage(i, 0x33CC66FF, "[F] [Военный самолет]: Примерное местоположение военного самолета отмечено на карте.");
            }
        }

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ Военный самолет ]\n\nОставшееся время: "W"%s", ConvertTime(WarPlaneInfo[idx][WarPlaneTimer]));
        WarPlaneInfo[idx][WarPlaneText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, WarPlaneInfo[idx][WarPlanePos][0], WarPlaneInfo[idx][WarPlanePos][1], WarPlaneInfo[idx][WarPlanePos][2] + 2.5, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

        WarPlaneInfo[idx][WarPlaneCheckpoint] = CreateDynamicCP(WarPlaneInfo[idx][WarPlanePos][0], WarPlaneInfo[idx][WarPlanePos][1], WarPlaneInfo[idx][WarPlanePos][2], 15.0, -1, -1, -1, 7.5);

        new area_data[2];
        area_data[1] = idx;
        area_data[0] = TYPE_ID_WARPLANE;
        Streamer_SetArrayData(STREAMER_TYPE_CP, WarPlaneInfo[idx][WarPlaneCheckpoint], E_STREAMER_EXTRA_ID, area_data);
    }
    else if(WarPlaneInfo[idx][WarPlaneTimer] == 0)
    {
        STRING_GLOBAL[0] = EOS;
        for(new i = 1; i < MAX_FRACTIONS; i++)
        {
            if(i == 5 || i > 6 && i < 15 || i == 20 || i == 23)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] [Военный самолет]: Военный самолет номер %d ликвидирован.", idx);
                SendFractionMessage(i, 0x33CC66FF, STRING_GLOBAL);
            }
        }

        WarPlaneInfo[idx][WarPlaneStatus] = 0;
        for(new i = 0; i < 7; i++) WarPlaneInfo[idx][WarPlaneContent][i] = 0;
        if(WarPlaneInfo[idx][WarPlaneObject] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(WarPlaneInfo[idx][WarPlaneObject]);
            WarPlaneInfo[idx][WarPlaneObject] = INVALID_OBJECT_ID;
        }
        WarPlaneInfo[idx][WarPlaneTimer] = 0;
        if(WarPlaneInfo[idx][WarPlaneText] != INVALID_3DTEXT_ID)
        {
            DestroyDynamic3DTextLabel(WarPlaneInfo[idx][WarPlaneText]);
            WarPlaneInfo[idx][WarPlaneText] = INVALID_3DTEXT_ID;
        }
        if(IsValidDynamicCP(WarPlaneInfo[idx][WarPlaneCheckpoint])) DestroyDynamicCP(WarPlaneInfo[idx][WarPlaneCheckpoint]);
        WarPlaneIDx = -1;
        GangZoneStopFlashForAll(WarPlaneZone);
        GangZoneHideForAll(WarPlaneZone);
        GangZoneDestroy(WarPlaneZone);
        WarPlaneZone = -1;
        return 1;
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ Военный самолет ]\n\nОставшееся время: "W"%s", ConvertTime(WarPlaneInfo[idx][WarPlaneTimer]));
        UpdateDynamic3DTextLabelText(WarPlaneInfo[idx][WarPlaneText], COLOR_MAIN, STRING_GLOBAL);
    }
    return 1;
}

ShowWarPlaneContent(playerid, idx)
{
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    new count;
    for(new i = 0; i < 7; i++)
    {
        if(WarPlaneInfo[idx][WarPlaneContent][i] == 0) continue;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [%d шт.]\n", count + 1, ItemsInfo[i + TRANSFER_ITEMS][iName], WarPlaneInfo[idx][WarPlaneContent][i]);
        strcat(STRING_GLOBAL, STRING_MIN);
        p_temp[playerid][p_listitem][count] = i;
        count++;
    }
    if(count == 0) return SendError(playerid, "В военном самолете ничего нет."), WarPlaneUse[playerid] = -1;
    ShowPlayerDialog(playerid, D_WARPLANE, DIALOG_STYLE_LIST, ""I"Военный самолет", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:warplane_create(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    CreateWarPlane();
    return 1;
}
