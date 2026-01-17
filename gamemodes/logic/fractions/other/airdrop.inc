new AirDropUse[MAX_PLAYERS];
new AirDropUseItems[MAX_PLAYERS];

enum AIRDROP_INFO
{
    AirDropStatus,
    AirDropContent[7],
    AirDropObject[2],
    AirDropTimer,
    Text3D:AirDropText,
    AirDropCheckpoint,
    Float:AirDropBoxPos[6],
    Float:AirDropParachutePos[6]
};

new AirDropInfo[][AIRDROP_INFO] = {
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-1286.60034, 2694.25586, 50.51720, 0.00000, 0.00000, 0.00000}, {-1286.62476, 2694.37427, 50.92990, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-221.15669, 2603.26563, 63.15940, 0.00000, 0.00000, 0.00000}, {-221.18340, 2603.28247, 63.58640, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {382.61960, 2539.47119, 16.99780, 0.00000, 0.00000, 0.00000}, {382.58801, 2539.53198, 17.40750, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {587.97638, 1669.63623, 7.44090, 0.00000, 0.00000, 0.00000}, {587.97028, 1669.66187, 7.84720, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {340.20050, 875.71722, 20.85330, 0.00000, 0.00000, 0.00000}, {340.18100, 875.74152, 21.25970, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-236.64426, 1216.33777, 20.19120, 0.00000, 0.00000, 0.00000}, {-236.66550, 1216.31506, 20.59890, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {53.72894, 1167.44482, 19.11280, 0.00000, 0.00000, 0.00000}, {53.71030, 1167.43237, 19.52190, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-1206.21948, 1824.35046, 42.17430, 0.00000, 0.00000, 0.00000}, {-1206.22205, 1824.40869, 42.58290, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-1929.69666, 2383.68848, 49.94680, 0.00000, 0.00000, 0.00000}, {-1929.71484, 2383.74683, 50.35610, 0.00000, 0.00000, 0.00000}},
    //{0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-523.89020, 2593.02051, 53.84380, 0.00000, 0.00000, 0.00000}, {-523.90759, 2593.11841, 54.25100, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-923.22601, 2021.72668, 61.36710, 0.00000, 0.00000, 0.00000}, {-923.21460, 2021.79761, 61.77450, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {-754.60101, 1639.83215, 27.61990, 0.00000, 0.00000, 0.00000}, {-754.63342, 1639.91602, 28.02880, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {681.55042, 1836.42871, 5.68820, 0.00000, 0.00000, 0.00000}, {681.49512, 1836.47083, 6.09710, 0.00000, 0.00000, 0.00000}},
    {0, {0, 0, 0, 0, 0, 0, 0}, {INVALID_OBJECT_ID, INVALID_OBJECT_ID}, 0, Text3D:INVALID_3DTEXT_ID, -1, {6.54712, 1526.40234, 13.19310, 0.00000, 0.00000, 0.00000}, {6.53460, 1526.42102, 13.60100, 0.00000, 0.00000, 0.00000}}
};

new AirDropIDx = -1;
new AirDropZone = -1;

GetFreeAirDropID()
{
    new airdrop_checked = -1;
    for(new i = sizeof(AirDropInfo)-1; i != -1; i--)
    {
        airdrop_checked = random(sizeof(AirDropInfo)-1);
        if(AirDropInfo[airdrop_checked][AirDropStatus] == 0) return airdrop_checked;
    }
    return -1;
}

CreateAirDrop()
{
    if(AirDropIDx != -1) return 1;
    new idx = GetFreeAirDropID();
    if(idx == -1) return 1;

    STRING_GLOBAL[0] = EOS;
    for(new i = 1; i < MAX_FRACTIONS; i++)
    {
        if(i > 6 && i < 15 || i == 23)
        {
            if(idx == -1) SendFractionMessage(i, 0x33CC66FF, "[F] [AirDrop Info]: Приземление AirDrop занимает две с половиной минуты.");
            else
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] [AirDrop Info]: AirDrop номер %d отправляется на землю.", idx);
                SendFractionMessage(i, 0x33CC66FF, STRING_GLOBAL);
                SendFractionMessage(i, 0x33CC66FF, "[F] [AirDrop Info]: Приземление AirDrop занимает две с половиной минуты.");
                SendFractionMessage(i, 0x33CC66FF, "[F] [AirDrop Info]: Примерное местоположение AirDrop отмечено на карте.");
            }
        }
    }

    AirDropInfo[idx][AirDropStatus] = 0;

    AirDropInfo[idx][AirDropContent][0] = RandomEx(500, 2500);
    AirDropInfo[idx][AirDropContent][1] = RandomEx(500, 2500);
    AirDropInfo[idx][AirDropContent][2] = RandomEx(250, 2500);
    AirDropInfo[idx][AirDropContent][3] = RandomEx(5, 10);
    AirDropInfo[idx][AirDropContent][4] = RandomEx(5, 10);
    AirDropInfo[idx][AirDropContent][5] = RandomEx(5, 10);
    AirDropInfo[idx][AirDropContent][6] = RandomEx(5, 10);

    if(AirDropInfo[idx][AirDropObject][0] != INVALID_OBJECT_ID) DestroyDynamicObject(AirDropInfo[idx][AirDropObject][0]);
    AirDropInfo[idx][AirDropObject][0] = CreateDynamicObject(2935, AirDropInfo[idx][AirDropBoxPos][0], AirDropInfo[idx][AirDropBoxPos][1], AirDropInfo[idx][AirDropBoxPos][2]+250.000000, AirDropInfo[idx][AirDropBoxPos][3], AirDropInfo[idx][AirDropBoxPos][4], AirDropInfo[idx][AirDropBoxPos][5], -1, -1, -1, 120.0, 120.0);

    if(AirDropInfo[idx][AirDropObject][1] != INVALID_OBJECT_ID) DestroyDynamicObject(AirDropInfo[idx][AirDropObject][1]);
    AirDropInfo[idx][AirDropObject][1] = CreateDynamicObject(19335, AirDropInfo[idx][AirDropParachutePos][0], AirDropInfo[idx][AirDropParachutePos][1], AirDropInfo[idx][AirDropParachutePos][2]+250.000000, AirDropInfo[idx][AirDropParachutePos][3], AirDropInfo[idx][AirDropParachutePos][4], AirDropInfo[idx][AirDropParachutePos][5], -1, -1, -1, 120.0, 120.0);

    AirDropInfo[idx][AirDropTimer] = 1049;

    AirDropIDx = idx;
    AirDropZone = GangZoneCreate(AirDropInfo[idx][AirDropBoxPos][0]-95, AirDropInfo[idx][AirDropBoxPos][1]-80, AirDropInfo[idx][AirDropBoxPos][0]+70, AirDropInfo[idx][AirDropBoxPos][1]+85);

    foreach(new i: Player)
    {
        if(!gang(i) && !mafia(i) && !biker(i)) continue;
        GangZoneShowForPlayer(i, AirDropZone, 0xFFFFFF65);
        GangZoneFlashForPlayer(i, AirDropZone, COLOR_RED);
    }

    new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;

    GetDynamicObjectPos(AirDropInfo[idx][AirDropObject][0], x, y, z);
    GetDynamicObjectRot(AirDropInfo[idx][AirDropObject][0], rx, ry, rz);
    MoveDynamicObject(AirDropInfo[idx][AirDropObject][0], x, y, z-250, 1.69, rx, ry, rz);

    GetDynamicObjectPos(AirDropInfo[idx][AirDropObject][1], x, y, z);
    GetDynamicObjectRot(AirDropInfo[idx][AirDropObject][1], rx, ry, rz);
    MoveDynamicObject(AirDropInfo[idx][AirDropObject][1], x, y, z-250, 1.69, rx, ry, rz);
    return 1;
}

CheckAirDrop()
{
    if(AirDropIDx == -1) return 1;

    new idx = AirDropIDx;

    AirDropInfo[idx][AirDropTimer]--;

    if(AirDropInfo[idx][AirDropTimer] == 900)
    {
        STRING_GLOBAL[0] = EOS;
        for(new i = 1; i < MAX_FRACTIONS; i++)
        {
            if(i > 6 && i < 15 || i == 23)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] [AirDrop Info]: AirDrop номер %d приземлился на землю.", idx);
                SendFractionMessage(i, 0x33CC66FF, STRING_GLOBAL);
                SendFractionMessage(i, 0x33CC66FF, "[F] [AirDrop Info]: Примерное местоположение AirDrop отмечено на карте.");
            }
        }

        if(AirDropInfo[idx][AirDropObject][1] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(AirDropInfo[idx][AirDropObject][1]);
            AirDropInfo[idx][AirDropObject][1] = INVALID_OBJECT_ID;
        }
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ AirDrop ]\n\nОставшееся время: "W"%s", ConvertTime(AirDropInfo[idx][AirDropTimer]));
        AirDropInfo[idx][AirDropText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, AirDropInfo[idx][AirDropBoxPos][0], AirDropInfo[idx][AirDropBoxPos][1], AirDropInfo[idx][AirDropBoxPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

        AirDropInfo[idx][AirDropCheckpoint] = CreateDynamicCP(AirDropInfo[idx][AirDropBoxPos][0], AirDropInfo[idx][AirDropBoxPos][1], AirDropInfo[idx][AirDropBoxPos][2], 10.0, -1, -1, -1, 7.5);

        new area_data[2];
        area_data[1] = idx;
        area_data[0] = TYPE_ID_AIRDROP;
        Streamer_SetArrayData(STREAMER_TYPE_CP, AirDropInfo[idx][AirDropCheckpoint], E_STREAMER_EXTRA_ID, area_data);
    }
    else if(AirDropInfo[idx][AirDropTimer] == 0)
    {
        STRING_GLOBAL[0] = EOS;
        for(new i = 1; i < MAX_FRACTIONS; i++)
        {
            if(i > 6 && i < 15 || i == 23)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] [AirDrop Info]: AirDrop номер %d ликвидирован.", idx);
                SendFractionMessage(i, 0x33CC66FF, STRING_GLOBAL);
            }
        }

        AirDropInfo[idx][AirDropStatus] = 0;
        for(new i = 0; i < 7; i++) AirDropInfo[idx][AirDropContent][i] = 0;
        if(AirDropInfo[idx][AirDropObject][0] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(AirDropInfo[idx][AirDropObject][0]);
            AirDropInfo[idx][AirDropObject][0] = INVALID_OBJECT_ID;
        }
        if(AirDropInfo[idx][AirDropObject][1] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(AirDropInfo[idx][AirDropObject][1]);
            AirDropInfo[idx][AirDropObject][1] = INVALID_OBJECT_ID;
        }
        for(new i = 0; i < 2; i++) AirDropInfo[idx][AirDropObject][i] = -1;
        AirDropInfo[idx][AirDropTimer] = 0;
        if(AirDropInfo[idx][AirDropText] != INVALID_3DTEXT_ID)
        {
            DestroyDynamic3DTextLabel(AirDropInfo[idx][AirDropText]);
            AirDropInfo[idx][AirDropText] = INVALID_3DTEXT_ID;
        }
        if(IsValidDynamicCP(AirDropInfo[idx][AirDropCheckpoint])) DestroyDynamicCP(AirDropInfo[idx][AirDropCheckpoint]);
        AirDropIDx = -1;
        GangZoneStopFlashForAll(AirDropZone);
        GangZoneHideForAll(AirDropZone);
        GangZoneDestroy(AirDropZone);
        AirDropZone = -1;
        return 1;
    }
    else
    {
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[ AirDrop ]\n\nОставшееся время: "W"%s", ConvertTime(AirDropInfo[idx][AirDropTimer]));
        UpdateDynamic3DTextLabelText(AirDropInfo[idx][AirDropText], COLOR_MAIN, STRING_GLOBAL);
    }
    return 1;
}

ShowAirDropContent(playerid, idx)
{
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    new count;
    for(new i = 0; i < 7; i++)
    {
        if(AirDropInfo[idx][AirDropContent][i] == 0) continue;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [%d шт.]\n", count + 1, ItemsInfo[i + TRANSFER_ITEMS][iName], AirDropInfo[idx][AirDropContent][i]);
        strcat(STRING_GLOBAL, STRING_MIN);
        p_temp[playerid][p_listitem][count] = i;
        count++;
    }
    if(count == 0) return SendError(playerid, "В AirDrop ничего нет."), AirDropUse[playerid] = -1;
    ShowPlayerDialog(playerid, D_AIRDROP, DIALOG_STYLE_LIST, ""I"AirDrop", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

CMD:airdrop_create(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    CreateAirDrop();
    return 1;
}
