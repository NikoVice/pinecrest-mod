#define MAX_TRASH_BOX                   27
#define MAX_TRASH_BOX_ITEMS             3

enum E_TRASH_BOX
{
    tbStatus,
    tbObject,
    tbCheckpoint,
    Text3D:tbText,
    tbItems[MAX_TRASH_BOX_ITEMS],
    tbItemsIDx[MAX_TRASH_BOX_ITEMS],
    tbItemsCount[MAX_TRASH_BOX_ITEMS],
    Float:tbPos[6]
}

new TrashBoxInfo[MAX_TRASH_BOX][E_TRASH_BOX] =
{
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2203.02734, -2024.03845, 12.54950, 0.00000, 0.00000, 28.55992}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2206.05688, -2015.42102, 12.54950, 0.00000, 0.00000, 73.61993}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2196.77759, -2014.56628, 12.54950, 0.00000, 0.00000, 17.51984}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2200.65088, -2005.78137, 12.54950, 0.00000, 0.00000, 46.97988}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2192.18481, -2002.43079, 12.54950, 0.00000, 0.00000, 68.57986}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2174.87378, -1987.04553, 12.54950, 0.00000, 0.00000, 26.99990}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2168.78320, -1977.16541, 12.54950, 0.00000, 0.00000, 54.65995}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2157.86694, -1982.12524, 12.54950, 0.00000, 0.00000, 94.92001}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {2152.48291, -1990.67834, 12.54950, 0.00000, 0.00000, 202.91983}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1830.70007, 170.71481, 14.09260, 0.00000, 0.00000, -90.00000}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1840.48621, 166.51921, 14.09260, 0.00000, 0.00000, -39.35995}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1828.11194, 154.67255, 14.09260, 0.00000, 0.00000, -131.88033}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1826.70947, 137.06075, 14.09260, 0.00000, 0.00000, -204.83995}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1840.73438, 126.36861, 14.09260, 0.00000, 0.00000, -147.72098}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1838.06616, 119.66045, 14.09260, 0.00000, 0.00000, -82.56126}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1829.30054, 123.34190, 14.09260, 0.00000, 0.00000, -127.14131}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1823.56604, 131.69998, 14.09260, 0.00000, 0.00000, 47.99879}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {-1839.14893, 147.08984, 14.09260, 0.00000, 0.00000, -131.10118}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {105.13890, 1083.88281, 12.60848, 0.00000, 0.00000, -25.08001}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {101.12016, 1073.53784, 12.60848, 0.00000, 0.00000, 34.25999}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {101.71330, 1062.43213, 12.60850, 0.00000, 0.00000, -90.00000}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {100.17932, 1053.26489, 12.60848, 0.00000, 0.00000, 44.21988}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {117.91136, 1053.26965, 12.60848, 0.00000, 0.00000, 138.23958}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {125.43935, 1062.87756, 12.60848, 0.00000, 0.00000, 153.59953}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {124.02320, 1075.34448, 12.60848, 0.00000, 0.00000, 179.57915}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {97.54619, 1063.87366, 12.60848, 0.00000, 0.00000, 210.59900}},
    {0, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {97.49909, 1088.83740, 12.60848, 0.00000, 0.00000, 170.33972}}
};

CheckTrashBox()
{
    new trash_checked = -1;
    for(new i = MAX_TRASH_BOX; i != -1; i--)
    {
        trash_checked = random(MAX_TRASH_BOX);
        if(TrashBoxInfo[trash_checked][tbStatus] == 0) return CreateTrashBox(trash_checked);
    }
    return -1;
}

CreateTrashBox(idx)
{
    TrashBoxInfo[idx][tbStatus] = 1;

    if(TrashBoxInfo[idx][tbObject] != INVALID_OBJECT_ID) DestroyDynamicObject(TrashBoxInfo[idx][tbObject]);
    TrashBoxInfo[idx][tbObject] = CreateDynamicObject(2972, TrashBoxInfo[idx][tbPos][0], TrashBoxInfo[idx][tbPos][1], TrashBoxInfo[idx][tbPos][2], TrashBoxInfo[idx][tbPos][3], TrashBoxInfo[idx][tbPos][4], TrashBoxInfo[idx][tbPos][5], -1, -1, -1, 120.0, 120.0);

    TrashBoxInfo[idx][tbCheckpoint] = CreateDynamicCP(TrashBoxInfo[idx][tbPos][0], TrashBoxInfo[idx][tbPos][1], TrashBoxInfo[idx][tbPos][2], 10.0, -1, -1, -1, 2.5);

    new area_data[2];
    area_data[1] = idx;
    area_data[0] = TYPE_ID_TRASH_BOX;
    Streamer_SetArrayData(STREAMER_TYPE_CP, TrashBoxInfo[idx][tbCheckpoint], E_STREAMER_EXTRA_ID, area_data);

    TrashBoxInfo[idx][tbText] = CreateDynamic3DTextLabel("Ящик с предметами", COLOR_MAIN, TrashBoxInfo[idx][tbPos][0], TrashBoxInfo[idx][tbPos][1], TrashBoxInfo[idx][tbPos][2] + 2.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    TrashBoxInfo[idx][tbItems][0] = TYPE_GIVE_ITEM_MONEY;
    TrashBoxInfo[idx][tbItemsCount][0] = random(100) == 0 ? 100000 : RandomEx(5000, 15000);

    TrashBoxInfo[idx][tbItems][1] = TYPE_GIVE_ITEM_INVENTORY;
    new inv_items_idx[] = {627, 628, 629, 630, 631, 632, 633, 647, 648, 649, 650, 651}, inv_items_count[][] = {{100, 250}, {100, 250}, {25, 50}, {5, 10}, {5, 10}, {5, 10}, {5, 10}, {10, 25}, {10, 25}, {5, 10}, {5, 10}, {5, 10}}, inv_items_check = random(sizeof(inv_items_idx) - 1);
    TrashBoxInfo[idx][tbItemsIDx][1] = inv_items_idx[inv_items_check];
    TrashBoxInfo[idx][tbItemsCount][1] = RandomEx(inv_items_count[inv_items_check][0], inv_items_count[inv_items_check][1]);

    if(random(100) < 50)
    {
        TrashBoxInfo[idx][tbItems][2] = TYPE_GIVE_ITEM_SKIN;
        new inv_skins_idx[] = {2, 7, 18, 24, 45, 67, 97, 101, 142, 144, 146, 154, 156, 176, 177, 220, 224}; // От 25000$ до 75000$;
        TrashBoxInfo[idx][tbItemsCount][2] = inv_skins_idx[random(sizeof(inv_skins_idx) - 1)];
    }
    else
    {
        TrashBoxInfo[idx][tbItems][2] = TYPE_GIVE_ITEM_ACCESSORIES;
        new inv_accessories_idx[] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585, 596, 598, 599, 600, 601, 602, 603, 607}; // 250000$;
        TrashBoxInfo[idx][tbItemsCount][2] = inv_accessories_idx[random(sizeof(inv_accessories_idx) - 1)];
    }

    //if(!SRV_ID) SendMesAll(-1, "TRASH BOX: %d (%f, %f, %f)", idx, TrashBoxInfo[idx][tbPos][0], TrashBoxInfo[idx][tbPos][1], TrashBoxInfo[idx][tbPos][2]);
    return 1;
}

ShowTrashBoxContent(playerid, idx)
{
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    new count;
    for(new i = 0; i < 3; i++)
    {
        if(TrashBoxInfo[idx][tbItems][i] == 0) continue;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\n", count + 1, GetPrizeItemsName(TrashBoxInfo[idx][tbItems][i], TrashBoxInfo[idx][tbItemsCount][i], TrashBoxInfo[idx][tbItemsIDx][i]));
        strcat(STRING_GLOBAL, STRING_MIN);
        p_temp[playerid][p_listitem][count] = i;
        count++;
    }
    if(count == 0) return SendError(playerid, "В ящике ничего нет."), p_temp[playerid][trash_box_use] = -1;
    ShowPlayerDialog(playerid, D_TRASH_BOX, DIALOG_STYLE_LIST, ""I"Ящик с предметами", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

DestroyTrashBox(idx)
{
    new count;
    for(new i = 0; i < MAX_TRASH_BOX_ITEMS; i++)
    {
        if(TrashBoxInfo[idx][tbItems][i] == 0) count++;
    }
    if(count == MAX_TRASH_BOX_ITEMS)
    {
        TrashBoxInfo[idx][tbStatus] = 0;
        if(TrashBoxInfo[idx][tbObject] != INVALID_OBJECT_ID) DestroyDynamicObject(TrashBoxInfo[idx][tbObject]);
        TrashBoxInfo[idx][tbObject] = INVALID_OBJECT_ID;
        if(IsValidDynamicCP(TrashBoxInfo[idx][tbCheckpoint])) DestroyDynamicCP(TrashBoxInfo[idx][tbCheckpoint]);
        TrashBoxInfo[idx][tbCheckpoint] = -1;
        if(TrashBoxInfo[idx][tbText] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(TrashBoxInfo[idx][tbText]);
        TrashBoxInfo[idx][tbText] = Text3D:INVALID_3DTEXT_ID;
        return 1;
    }
    return -1;
}

CMD:createtrashbox(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckTrashBox();
    return 1;
}