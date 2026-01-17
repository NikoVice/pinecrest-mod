#define MAX_BOX                 200
#define MAX_BOX_COORDS          1000
#define MAX_BOX_ITEMS           5

new PlayerText:BoxOther[MAX_PLAYERS][16];
new PlayerText:BoxButton[MAX_PLAYERS][6];
new PlayerText:BoxItems[MAX_PLAYERS][5];
new PlayerText:BoxLight[MAX_PLAYERS][5];
new PlayerText:BoxItemsCount[MAX_PLAYERS][5];
new PlayerText:BoxText[MAX_PLAYERS][3];

enum E_BOX_INFO
{
    boxType,
    boxObject[9],
    boxArea,
    boxItems[MAX_BOX_ITEMS],
    boxItemsIDx[MAX_BOX_ITEMS],
    boxItemsCount[MAX_BOX_ITEMS],
    boxCoordsMySQLIDx
};
new BoxInfo[MAX_BOX][E_BOX_INFO];

new box_pickups_count;

enum
{
    TYPE_BOX_NONE,
    TYPE_BOX_WHITE,
    TYPE_BOX_PURPLE,
    TYPE_BOX_GOLD
}

forward LoadBoxCoords(idx);
public LoadBoxCoords(idx)
{
    if(cache_num_rows())
    {
        new mysql_idx, Float:x, Float:y, Float:z, Float:r, 
            type_list[20] = 
                {TYPE_BOX_WHITE, TYPE_BOX_WHITE, TYPE_BOX_WHITE, TYPE_BOX_WHITE, TYPE_BOX_WHITE,
                TYPE_BOX_WHITE, TYPE_BOX_WHITE, TYPE_BOX_WHITE, TYPE_BOX_WHITE, TYPE_BOX_WHITE,
                TYPE_BOX_PURPLE, TYPE_BOX_PURPLE, TYPE_BOX_PURPLE, TYPE_BOX_PURPLE, TYPE_BOX_PURPLE,
                TYPE_BOX_PURPLE, TYPE_BOX_PURPLE, TYPE_BOX_GOLD, TYPE_BOX_GOLD, TYPE_BOX_GOLD},
            type = type_list[random(sizeof(type_list))];
        cache_get_value_name_int(0, "id", mysql_idx);
        cache_get_value_name_float(0, "x", x);
        cache_get_value_name_float(0, "y", y);
        cache_get_value_name_float(0, "z", z);
        cache_get_value_name_float(0, "r", r);
        CreateBox(idx, mysql_idx, type, x, y, z, r);
    }
    else printf("[BOX SYSTEM]: Сундук %d не может быть создан, не найдены свободные координаты.");
    return 1;
}

CreateBox(idx, mysql_idx, type, Float:x, Float:y, Float:z, Float:r)
{
    BoxInfo[idx][boxType] = type;

    BoxInfo[idx][boxCoordsMySQLIDx] = mysql_idx;

    new Float: ox, Float: oy, Float: oz, Float: orx, Float: ory, Float: orz;
    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, -0.046997, -0.641967, 1.091118, -89.999992, 89.999992, 89.999992, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][0] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.820678, 1.078491, 1.091118, -89.999992, 90.000000, -89.999969, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][1] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, -0.047119, 1.077758, 1.091709, 0.000000, 450.039550, -89.960472, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][2] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.820800, -0.641235, 1.091709, -0.000000, 450.039550, 90.039497, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][3] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.692016, -0.004028, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][4] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.693969, 0.446655, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][5] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    BoxInfo[idx][boxArea] = CreateDynamicSphere(ox, oy, oz - 1.05, 2.5, -1, -1, -1);
    UpdateAreaInfo(BoxInfo[idx][boxArea], TYPE_BOX, AREA_SUBTYPE_INVALID_ID, idx);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][6] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.001953, 0.450683, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][7] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 1.291992, 0.228637, 0.561718, 0.000000, 0.000000, 90.000000, ox, oy, oz, orx, ory, orz);
    BoxInfo[idx][boxObject][8] = CreateDynamicObject(2680, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    switch(type)
    {
        case TYPE_BOX_WHITE:
        {
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][0], 0, 18029, "genintintsmallrest", "GB_restaursmll11", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][0], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][1], 0, 18029, "genintintsmallrest", "GB_restaursmll11", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][1], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][2], 0, 18029, "genintintsmallrest", "GB_restaursmll11", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][2], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][3], 0, 18029, "genintintsmallrest", "GB_restaursmll11", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][3], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][4], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][4], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][5], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][5], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][6], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][6], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][7], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][7], 1, 8480, "csrspalace01", "ceasersledge01_128", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][8], 1, 10763, "airport1_sfse", "ws_lightlens", 0x00000000);
        }
        case TYPE_BOX_PURPLE:
        {
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][0], 0, 14808, "lee_strip2", "strip_neon_Curtain", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][0], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][1], 0, 14808, "lee_strip2", "strip_neon_Curtain", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][1], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][2], 0, 14808, "lee_strip2", "strip_neon_Curtain", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][2], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][3], 0, 14808, "lee_strip2", "strip_neon_Curtain", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][3], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][4], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][4], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][5], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][5], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][6], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][6], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][7], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][7], 1, 6985, "vgnfremnt2", "striplightsblu_256", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][8], 1, 10763, "airport1_sfse", "ws_lightlens", 0x00000000);
        }
        case TYPE_BOX_GOLD:
        {
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][0], 0, 14808, "lee_strip2", "Strip_Gold", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][0], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][1], 0, 14808, "lee_strip2", "Strip_Gold", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][1], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][2], 0, 14808, "lee_strip2", "Strip_Gold", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][2], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][3], 0, 14808, "lee_strip2", "Strip_Gold", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][3], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][4], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][4], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][5], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][5], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][6], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][6], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][7], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][7], 1, 15040, "cuntcuts", "GB_pendantlmp01", 0x00000000);
            SetDynamicObjectMaterial(BoxInfo[idx][boxObject][8], 1, 10763, "airport1_sfse", "ws_lightlens", 0x00000000);
        }
    }

    GetBoxItems(idx, type);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `box_coords` SET `status` = 1 WHERE `id` = %d", mysql_idx);
    mysql_tquery(con_bd, STRING_GLOBAL);

    box_pickups_count++;
    return 1;
}

GetBoxItems(idx, class)
{
    BoxInfo[idx][boxItems][0] = TYPE_GIVE_ITEM_EXP;
    BoxInfo[idx][boxItemsCount][0] = RandomEx(3, 5) * class;
    BoxInfo[idx][boxItems][1] = TYPE_GIVE_ITEM_MONEY;
    BoxInfo[idx][boxItemsCount][1] = RandomEx(2500, 5000) * class;

    new items_box_prize[7] = {647, 648, 649, 650, 651, 641, 645}; // Хлопок, лен, металл, древесина, камень, гражданские монеты;
    BoxInfo[idx][boxItems][2] = TYPE_GIVE_ITEM_INVENTORY;
    BoxInfo[idx][boxItemsIDx][2] = items_box_prize[random(sizeof(items_box_prize))];
    BoxInfo[idx][boxItemsCount][2] = RandomEx(5, 10) * class;

    switch(class)
    {
        case TYPE_BOX_WHITE:
        {
            if(random(100) < 30)
            {
                BoxInfo[idx][boxItems][3] = TYPE_GIVE_ITEM_ACCESSORIES;

                BoxInfo[idx][boxItemsIDx][3] = 0;
                new accessories_box_prize[21] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585}; // 250000$;
                BoxInfo[idx][boxItemsCount][3] = accessories_box_prize[random(sizeof(accessories_box_prize))];
            }
            else
            {
                BoxInfo[idx][boxItems][3] = TYPE_GIVE_ITEM_INVENTORY;

                BoxInfo[idx][boxItemsIDx][3] = items_box_prize[random(sizeof(items_box_prize))];
                BoxInfo[idx][boxItemsCount][3] = RandomEx(5, 10) * class;
            }

            if(random(100) < 30)
            {
                BoxInfo[idx][boxItems][4] = TYPE_GIVE_ITEM_SKIN;

                BoxInfo[idx][boxItemsIDx][4] = 0;
                new skin_box_prize[17] = {2, 7, 18, 24, 45, 67, 97, 101, 142, 144, 146, 154, 156, 176, 177, 220, 224}; // От 25000$ до 75000$;
                BoxInfo[idx][boxItemsCount][4] = skin_box_prize[random(sizeof(skin_box_prize))];
            }
            else
            {
                BoxInfo[idx][boxItems][4] = TYPE_GIVE_ITEM_INVENTORY;

                BoxInfo[idx][boxItemsIDx][4] = items_box_prize[random(sizeof(items_box_prize))];
                BoxInfo[idx][boxItemsCount][4] = RandomEx(5, 10) * class;
            }
        }
        case TYPE_BOX_PURPLE:
        {
            if(random(100) < 50)
            {
                BoxInfo[idx][boxItems][3] = TYPE_GIVE_ITEM_ACCESSORIES;

                BoxInfo[idx][boxItemsIDx][3] = 0;
                new accessories_box_prize[61] = {440, 441, 442, 446, 447, 448, 449, 450, 466, 467, 468, 469, 470, 471, 473, 474, 483, 487, 488, 494, 495, 496, 499, 502, 503, 514, 518, 522, 524, 526, 531, 532, 533, 535, 536, 538, 539, 550, 551, 552, 553, 554, 557, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 580, 581, 582, 583, 584}; // 500000$;
                BoxInfo[idx][boxItemsCount][3] = accessories_box_prize[random(sizeof(accessories_box_prize))];
           }
            else
            {
                BoxInfo[idx][boxItems][3] = TYPE_GIVE_ITEM_INVENTORY;

                BoxInfo[idx][boxItemsIDx][3] = items_box_prize[random(sizeof(items_box_prize))];
                BoxInfo[idx][boxItemsCount][3] = RandomEx(5, 10) * class;
            }

            if(random(100) < 50)
            {
                BoxInfo[idx][boxItems][4] = TYPE_GIVE_ITEM_SKIN;

                BoxInfo[idx][boxItemsIDx][4] = 0;
                new skin_box_prize[8] = {28, 60, 170, 180, 183, 184, 273, 298}; // От 75000$ до 125000$;
                BoxInfo[idx][boxItemsCount][4] = skin_box_prize[random(sizeof(skin_box_prize))];
            }
            else
            {
                BoxInfo[idx][boxItems][4] = TYPE_GIVE_ITEM_INVENTORY;

                BoxInfo[idx][boxItemsIDx][4] = items_box_prize[random(sizeof(items_box_prize))];
                BoxInfo[idx][boxItemsCount][4] = RandomEx(5, 10) * class;
            }
        }
        case TYPE_BOX_GOLD:
        {
            BoxInfo[idx][boxItems][0] = TYPE_GIVE_ITEM_INVENTORY;
            new casket_box_prize[26] = {718, 718, 718, 719, 719, 719, 720, 720, 720, 721, 721, 721, 722, 722, 722, 723, 723, 723, 724, 724, 724, 725, 725, 726, 727, 728};
            BoxInfo[idx][boxItemsIDx][0] = casket_box_prize[random(sizeof(casket_box_prize))];
            BoxInfo[idx][boxItemsCount][0] = 1;

            BoxInfo[idx][boxItems][1] = TYPE_GIVE_ITEM_INVENTORY;
            new other_box_prize[6] = {642, 642, 642, 643, 643, 644}; // Рулетки;
            BoxInfo[idx][boxItemsIDx][1] = other_box_prize[random(sizeof(other_box_prize))];
            BoxInfo[idx][boxItemsCount][1] = 1;

            BoxInfo[idx][boxItems][3] = TYPE_GIVE_ITEM_ACCESSORIES;
            BoxInfo[idx][boxItemsIDx][3] = 0;
            new accessories_box_prize[23] = {451, 452, 453, 460, 461, 462, 463, 475, 486, 501, 505, 506, 525, 527, 529, 548, 555, 573, 574, 575, 577, 578, 579}; // От 500000$ до 2000000$;
            BoxInfo[idx][boxItemsCount][3] = accessories_box_prize[random(sizeof(accessories_box_prize))];

            BoxInfo[idx][boxItems][4] = TYPE_GIVE_ITEM_SKIN;
            BoxInfo[idx][boxItemsIDx][4] = 0;
            new skin_box_prize[32] = {17, 19, 21, 22, 23, 29, 30, 33, 46, 47, 48, 76, 82, 83, 84, 91, 185, 214, 219, 228, 241, 242, 249, 289, 291, 292, 293, 294, 295, 296, 297, 299}; // От 125000$ до 645000$;
            BoxInfo[idx][boxItemsCount][4] = skin_box_prize[random(sizeof(skin_box_prize))];
        }
    }
    return 1;
}

OnPlayerOpenBox(playerid, idx)
{
    if(IsTDVisible(playerid) != -1) return 1;
    LoadPlayerBoxTextDraw(playerid);

    for(new i = 0; i < 16; i++)
    {
        PlayerTextDrawShow(playerid, BoxOther[playerid][i]);
        if(i < 6) PlayerTextDrawShow(playerid, BoxButton[playerid][i]);
        if(i < 5)
        {
            GetPlayerBoxItems(playerid, idx, i);
            PlayerTextDrawShow(playerid, BoxLight[playerid][i]);
            GetPlayerBoxItemsCount(playerid, idx, i);
        }
        if(i < 3) PlayerTextDrawShow(playerid, BoxText[playerid][i]);
    }

    new box_name[3][24] = {"СТАНДАРТНЫЙ", "ЭПИЧЕСКИЙ", "ЛЕГЕНДАРНЫЙ"};
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "%s", box_name[BoxInfo[idx][boxType] - 1]);
    PlayerTextDrawSetString(playerid, BoxText[playerid][1], STRING_GLOBAL);

    p_temp[playerid][TextDrawBox] = true;

    SelectTextDraw(playerid, -104911873);

    p_temp[playerid][BoxIDx] = idx;
    return 1;
}

GetPlayerBoxItems(playerid, idx, i)
{
    switch(BoxInfo[idx][boxItems][i])
    {
        case TYPE_GIVE_ITEM_EXP:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 1277);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 0.0000, 0.0000, 180.0000, 1.0000);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
        case TYPE_GIVE_ITEM_MONEY:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 1550);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 324.0000, 0.0000, 0.0000, 0.6934);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
        case TYPE_GIVE_ITEM_DONATE:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 1274);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 167.0000, 0.0000, 0.0000, 0.6621);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
        case TYPE_GIVE_ITEM_INVENTORY:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 1239);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 351.0000, 0.0000, 175.0000, 0.9384);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
        case TYPE_GIVE_ITEM_ACCESSORIES:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 1275);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 339.0000, 0.0000, 202.0000, 0.7194);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
        case TYPE_GIVE_ITEM_SKIN:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], BoxInfo[idx][boxItemsCount][i]);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 320.0000, 0.0000, 0.0000, 0.9489);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
        default:
        {
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 18631);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 280.000000, 0.000000, 0.000000, 0.662100);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);
        }
    }
    return 1;
}

GetPlayerBoxItemsCount(playerid, idx, i)
{
    new str[32];
    switch(BoxInfo[idx][boxItems][i])
    {
        case TYPE_GIVE_ITEM_EXP, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_DONATE:
        {
            format(str, sizeof(str), "%d", BoxInfo[idx][boxItemsCount][i]);
            PlayerTextDrawSetString(playerid, BoxItemsCount[playerid][i], str);
            PlayerTextDrawShow(playerid, BoxItemsCount[playerid][i]);
        }
        case TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
        {
            format(str, sizeof(str), "%s", ItemsInfo[BoxInfo[idx][boxItemsCount][i]][iName]);
            PlayerTextDrawSetString(playerid, BoxItemsCount[playerid][i], str);
            PlayerTextDrawShow(playerid, BoxItemsCount[playerid][i]);
        }
        case TYPE_GIVE_ITEM_INVENTORY:
        {
            format(str, sizeof(str), "%s", ItemsInfo[BoxInfo[idx][boxItemsIDx][i]][iName]);
            PlayerTextDrawSetString(playerid, BoxItemsCount[playerid][i], str);
            PlayerTextDrawShow(playerid, BoxItemsCount[playerid][i]);
        }
    }
    return 1;
}

ClearBoxItems(playerid, idx, i)
{
    BoxInfo[idx][boxItems][i] = 0;
    BoxInfo[idx][boxItemsIDx][i] = 0;
    BoxInfo[idx][boxItemsCount][i] = 0;

    new count = -1;
    for(new x = 0; x < MAX_BOX_ITEMS; x++)
    {
        if(BoxInfo[idx][boxItems][x] != 0) count++;
    }
    if(count == -1)
    {
        CheckPlayerMission(playerid, DAILY_BOX);
        CheckPlayerMission(playerid, ACHIEVEMENT_BOX);
        if(p_temp[playerid][TextDrawBox] == true) HidePlayerBox(playerid);
        DestroyBox(idx);
        return 1;
    }
    else
    {
        if(p_temp[playerid][TextDrawBox] == false) OnPlayerOpenBox(playerid, idx);
        else
        {
            PlayerTextDrawHide(playerid, BoxItems[playerid][i]);
            PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][i], 18631);
            PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][i], 280.000000, 0.000000, 0.000000, 0.662100);
            PlayerTextDrawShow(playerid, BoxItems[playerid][i]);

            if(BoxItemsCount[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, BoxItemsCount[playerid][i]);
                BoxItemsCount[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
        }
    }
    return 1;
}

DestroyBox(idx)
{
    for(new i = 0; i < 9; i++)
    {
        if(BoxInfo[idx][boxObject][i] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(BoxInfo[idx][boxObject][i]);
            BoxInfo[idx][boxObject][i] = INVALID_OBJECT_ID;
        }
        if(i < MAX_BOX_ITEMS)
        {
            BoxInfo[idx][boxItems][i] = 0;
            BoxInfo[idx][boxItemsIDx][i] = 0;
            BoxInfo[idx][boxItemsCount][i] = 0;
        }
    }
    if(BoxInfo[idx][boxArea] != -1)
    {
        DestroyDynamicArea(BoxInfo[idx][boxArea]);
        BoxInfo[idx][boxArea] = -1;
    }

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `box_coords` SET `status` = 0 WHERE `id` = %d",
    BoxInfo[idx][boxCoordsMySQLIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    BoxInfo[idx][boxCoordsMySQLIDx] = INVALID_MYSQL_ID;

    box_pickups_count--;
    return 1;
}

CMD:createboxcoords(playerid, params[])
{
    if(SRV_ID) return 1;

    if(GetPlayerInterior(playerid) != 0 || GetPlayerVirtualWorld(playerid) != 0) return 1;

    if(p_temp[playerid][CreateBoxObject][0] != INVALID_OBJECT_ID) return ShowPlayerDialog(playerid, D_CREATE_BOX, DIALOG_STYLE_MSGBOX, ""I"Сохранения координат для сундука", ""W"Вы хотите сохранить для сундука данные координаты?", "Да", "Нет");

    new Float:x, Float:y, Float:z, Float:r;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, r);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `box_coords` WHERE SQRT(POWER(x-%f,2)+POWER(y-%f,2)+POWER(z-%f,2)) < 50", x, y, z);
    mysql_tquery(con_bd, STRING_GLOBAL, "MySQLCheckCreateBoxCoords", "iffff", playerid, x, y, z, r);
    return 1;
}

forward MySQLCheckCreateBoxCoords(playerid, Float:x, Float:y, Float:z, Float:r);
public MySQLCheckCreateBoxCoords(playerid, Float:x, Float:y, Float:z, Float:r)
{
    //if(cache_num_rows()) return SendError(playerid, "Рядом с данным местом уже есть координаты для сундука.");

    p_temp[playerid][CreateBoxCoords][0] = x;
    p_temp[playerid][CreateBoxCoords][1] = y;
    p_temp[playerid][CreateBoxCoords][2] = z;
    p_temp[playerid][CreateBoxCoords][3] = r;

    x = x + (2.5 * floatsin(-r, degrees));
    y = y + (2.5 * floatcos(-r, degrees));

    new Float: ox, Float: oy, Float: oz, Float: orx, Float: ory, Float: orz;
    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, -0.046997, -0.641967, 1.091118, -89.999992, 89.999992, 89.999992, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][0] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][0], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][0], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.820678, 1.078491, 1.091118, -89.999992, 90.000000, -89.999969, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][1] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][1], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][1], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, -0.047119, 1.077758, 1.091709, 0.000000, 450.039550, -89.960472, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][2] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][2], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][2], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.820800, -0.641235, 1.091709, -0.000000, 450.039550, 90.039497, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][3] = CreateDynamicObject(19925, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][3], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][3], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.692016, -0.004028, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][4] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][4], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][4], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.693969, 0.446655, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][5] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][5], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][5], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][6] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][6], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][6], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 0.001953, 0.450683, 0.000000, 0.000000, 0.000000, 0.000000, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][7] = CreateDynamicObject(19930, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][7], 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
    SetDynamicObjectMaterial(p_temp[playerid][CreateBoxObject][7], 1, 10350, "oc_flats_gnd_sfs", "ws_woodfence1", 0x00000000);

    GetObjectOffset(x, y, z, 0.000000, 0.000007, r - 180.0, 1.291992, 0.228637, 0.561718, 0.000000, 0.000000, 90.000000, ox, oy, oz, orx, ory, orz);
    p_temp[playerid][CreateBoxObject][8] = CreateDynamicObject(2680, ox, oy, oz - 1.05, orx, ory, orz, -1, -1, -1, 25.00, 25.00);

    SetPlayerPos(playerid, x - (2.5 * floatsin(-r, degrees)), y - (2.5 * floatcos(-r, degrees)), z + 1.5);

    SendInfo(playerid, "Вы начали процесс сохранения координат для сундука. Осмотритесь, правильно ли расположен сундук или нет.");
    SendInfo(playerid, "Для завершения процесса сохранения координат для сундука, введите /createboxcoords");

    return 1;
}

ClearPlayerCreateBoxInfo(playerid)
{
    for(new i = 0; i < 9; i++)
    {
        if(i < 4) p_temp[playerid][CreateBoxCoords][i] = 0.0;
        if(p_temp[playerid][CreateBoxObject][i] != INVALID_OBJECT_ID)
        {
            DestroyDynamicObject(p_temp[playerid][CreateBoxObject][i]);
            p_temp[playerid][CreateBoxObject][i] = INVALID_OBJECT_ID;
        }
    }
    return 1;
}

HidePlayerBox(playerid)
{
    for(new i = 0; i < 16; i++)
    {
        if(BoxOther[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, BoxOther[playerid][i]);
            BoxOther[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
        if(i < 6 && BoxButton[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, BoxButton[playerid][i]);
            BoxButton[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
        if(i < 5)
        {
            if(BoxItems[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, BoxItems[playerid][i]);
                BoxItems[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
            if(BoxLight[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, BoxLight[playerid][i]);
                BoxLight[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
            if(BoxItemsCount[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, BoxItemsCount[playerid][i]);
                BoxItemsCount[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
        }
        if(i < 3 && BoxText[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
        {
            PlayerTextDrawDestroy(playerid, BoxText[playerid][i]);
            BoxText[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        }
    }
    p_temp[playerid][TextDrawBox] = false;
    CancelSelectTextDraw(playerid);
    return 1;
}

LoadPlayerBoxTextDraw(playerid)
{
    BoxOther[playerid][0] = CreatePlayerTextDraw(playerid, 229.033203, 254.140701, "particle:lamp_shad_64");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][0], 184.000000, 19.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][0], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][0], 255);
    PlayerTextDrawFont(playerid, BoxOther[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][0], 0);

    BoxOther[playerid][1] = CreatePlayerTextDraw(playerid, 319.500000, 142.970306, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][1], -197.000000, 29.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][1], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][1], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][1], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][1], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][1], 0.000000, 360.000000, 90.000000, 0.927900);

    BoxOther[playerid][2] = CreatePlayerTextDraw(playerid, 321.333312, 159.147903, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][2], 199.000000, 205.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][2], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][2], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][2], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][2], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][2], 0.000000, 360.000000, 91.000000, 1.303400);

    BoxOther[playerid][3] = CreatePlayerTextDraw(playerid, 321.333312, 159.147903, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][3], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][3], -216.000000, 205.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][3], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][3], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][3], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][3], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][3], 0.000000, 360.000000, 91.000000, 1.303400);

    BoxOther[playerid][4] = CreatePlayerTextDraw(playerid, 319.166595, 143.314804, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][4], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][4], 187.000000, 28.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][4], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][4], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][4], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][4], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][4], 0.000000, 360.000000, 90.000000, 0.927900);

    BoxOther[playerid][5] = CreatePlayerTextDraw(playerid, 201.333206, 179.488601, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][5], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][5], 224.000000, 56.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][5], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][5], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][5], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][5], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][5], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][5], 19941);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][5], 0.000000, 0.000000, 91.000000, 0.521300);

    BoxOther[playerid][6] = CreatePlayerTextDraw(playerid, 212.633300, 146.288604, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][6], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][6], 412.000000, 114.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][6], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][6], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][6], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][6], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][6], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][6], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][6], 282.000000, 360.000000, 90.000000, 1.522400);

    BoxOther[playerid][7] = CreatePlayerTextDraw(playerid, 247.700103, 155.929504, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][7], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][7], 184.000000, 48.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][7], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][7], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][7], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][7], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][7], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][7], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][7], 282.000000, 360.000000, 90.000000, 1.522400);

    BoxOther[playerid][8] = CreatePlayerTextDraw(playerid, 216.033203, 100.659202, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][8], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][8], 207.000000, 138.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][8], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][8], -2139062017);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][8], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][8], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][8], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][8], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][8], 307.000000, 0.000000, 91.000000, 1.793400);

    BoxOther[playerid][9] = CreatePlayerTextDraw(playerid, 416.699493, 106.314697, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][9], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][9], -195.000000, 129.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][9], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][9], -2139062017);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][9], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][9], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][9], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][9], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][9], 307.000000, 0.000000, 91.000000, 1.793400);

    BoxOther[playerid][10] = CreatePlayerTextDraw(playerid, 219.366500, 87.070098, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][10], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][10], 384.000000, 114.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][10], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][10], -4865);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][10], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][10], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][10], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][10], 2988);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][10], 282.000000, 360.000000, 90.000000, 1.522400);

    BoxOther[playerid][11] = CreatePlayerTextDraw(playerid, -40.999900, 102.318298, "");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][11], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][11], 719.000000, 305.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][11], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][11], -1676570);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][11], 0);
    PlayerTextDrawFont(playerid, BoxOther[playerid][11], 5);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][11], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxOther[playerid][11], 19198);
    PlayerTextDrawSetPreviewRot(playerid, BoxOther[playerid][11], 269.000000, 0.000000, 0.000000, 0.839200);

    BoxOther[playerid][12] = CreatePlayerTextDraw(playerid, 238.366500, 109.785102, "particle:lamp_shad_64");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][12], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][12], 170.000000, 112.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][12], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][12], -2096990);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][12], 255);
    PlayerTextDrawFont(playerid, BoxOther[playerid][12], 4);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][12], 0);

    BoxOther[playerid][13] = CreatePlayerTextDraw(playerid, 276.866302, 326.733306, "LD_BEAT:chit");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][13], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][13], 27.000000, 32.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][13], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][13], -104911873);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][13], 255);
    PlayerTextDrawFont(playerid, BoxOther[playerid][13], 4);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][13], 0);

    BoxOther[playerid][14] = CreatePlayerTextDraw(playerid, 337.132904, 326.733093, "LD_BEAT:chit");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][14], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][14], 27.000000, 32.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][14], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][14], -104911873);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][14], 255);
    PlayerTextDrawFont(playerid, BoxOther[playerid][14], 4);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][14], 0);

    BoxOther[playerid][15] = CreatePlayerTextDraw(playerid, 337.132904, 326.733093, "LD_BEAT:chit");
    PlayerTextDrawLetterSize(playerid, BoxOther[playerid][15], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxOther[playerid][15], 27.000000, 32.000000);
    PlayerTextDrawAlignment(playerid, BoxOther[playerid][15], 1);
    PlayerTextDrawColor(playerid, BoxOther[playerid][15], -104911873);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][15], 0);
    PlayerTextDrawSetOutline(playerid, BoxOther[playerid][15], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxOther[playerid][15], 255);
    PlayerTextDrawFont(playerid, BoxOther[playerid][15], 4);
    PlayerTextDrawSetProportional(playerid, BoxOther[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, BoxOther[playerid][15], 0);

    BoxButton[playerid][0] = CreatePlayerTextDraw(playerid, 283.733001, 170.762802, "LD_BEAT:chit"); // Item Button #1;
    PlayerTextDrawLetterSize(playerid, BoxButton[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxButton[playerid][0], 69.000000, 80.000000);
    PlayerTextDrawAlignment(playerid, BoxButton[playerid][0], 1);
    PlayerTextDrawColor(playerid, BoxButton[playerid][0], 505290495);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BoxButton[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxButton[playerid][0], 255);
    PlayerTextDrawFont(playerid, BoxButton[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, BoxButton[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][0], 0);
    PlayerTextDrawSetSelectable(playerid, BoxButton[playerid][0], true);

    BoxButton[playerid][1] = CreatePlayerTextDraw(playerid, 348.733001, 170.762802, "LD_BEAT:chit"); // Item Button #2;
    PlayerTextDrawLetterSize(playerid, BoxButton[playerid][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxButton[playerid][1], 69.000000, 80.000000);
    PlayerTextDrawAlignment(playerid, BoxButton[playerid][1], 1);
    PlayerTextDrawColor(playerid, BoxButton[playerid][1], 505290495);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BoxButton[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxButton[playerid][1], 255);
    PlayerTextDrawFont(playerid, BoxButton[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, BoxButton[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, BoxButton[playerid][1], true);

    BoxButton[playerid][2] = CreatePlayerTextDraw(playerid, 218.733001, 170.762802, "LD_BEAT:chit"); // Item Button #3;
    PlayerTextDrawLetterSize(playerid, BoxButton[playerid][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxButton[playerid][2], 69.000000, 80.000000);
    PlayerTextDrawAlignment(playerid, BoxButton[playerid][2], 1);
    PlayerTextDrawColor(playerid, BoxButton[playerid][2], 505290495);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BoxButton[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxButton[playerid][2], 255);
    PlayerTextDrawFont(playerid, BoxButton[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, BoxButton[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, BoxButton[playerid][2], true);

    BoxButton[playerid][3] = CreatePlayerTextDraw(playerid, 251.066299, 229.251693, "LD_BEAT:chit"); // Item Button #4;
    PlayerTextDrawLetterSize(playerid, BoxButton[playerid][3], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxButton[playerid][3], 69.000000, 80.000000);
    PlayerTextDrawAlignment(playerid, BoxButton[playerid][3], 1);
    PlayerTextDrawColor(playerid, BoxButton[playerid][3], 505290495);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, BoxButton[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxButton[playerid][3], 255);
    PlayerTextDrawFont(playerid, BoxButton[playerid][3], 4);
    PlayerTextDrawSetProportional(playerid, BoxButton[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, BoxButton[playerid][3], true);

    BoxButton[playerid][4] = CreatePlayerTextDraw(playerid, 316.733001, 229.251693, "LD_BEAT:chit"); // Item Button #5;
    PlayerTextDrawLetterSize(playerid, BoxButton[playerid][4], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxButton[playerid][4], 69.000000, 80.000000);
    PlayerTextDrawAlignment(playerid, BoxButton[playerid][4], 1);
    PlayerTextDrawColor(playerid, BoxButton[playerid][4], 505290495);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, BoxButton[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxButton[playerid][4], 255);
    PlayerTextDrawFont(playerid, BoxButton[playerid][4], 4);
    PlayerTextDrawSetProportional(playerid, BoxButton[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, BoxButton[playerid][4], true);

    BoxButton[playerid][5] = CreatePlayerTextDraw(playerid, 290.499908, 332.010894, "LD_SPAC:white"); // Item Button > EXIT;
    PlayerTextDrawLetterSize(playerid, BoxButton[playerid][5], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxButton[playerid][5], 61.000000, 21.389900);
    PlayerTextDrawAlignment(playerid, BoxButton[playerid][5], 1);
    PlayerTextDrawColor(playerid, BoxButton[playerid][5], -104911873);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, BoxButton[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxButton[playerid][5], 255);
    PlayerTextDrawFont(playerid, BoxButton[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, BoxButton[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, BoxButton[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, BoxButton[playerid][5], true);

    BoxItems[playerid][0] = CreatePlayerTextDraw(playerid, 302.833007, 192.048202, ""); // Item #1;
    PlayerTextDrawLetterSize(playerid, BoxItems[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxItems[playerid][0], 32.000000, 40.000000);
    PlayerTextDrawAlignment(playerid, BoxItems[playerid][0], 1);
    PlayerTextDrawColor(playerid, BoxItems[playerid][0], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BoxItems[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxItems[playerid][0], 0);
    PlayerTextDrawFont(playerid, BoxItems[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, BoxItems[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][0], 18631);
    PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][0], 280.000000, 0.000000, 0.000000, 0.662100);

    BoxItems[playerid][1] = CreatePlayerTextDraw(playerid, 367.833007, 192.048202, ""); // Item #2;
    PlayerTextDrawLetterSize(playerid, BoxItems[playerid][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxItems[playerid][1], 32.000000, 40.000000);
    PlayerTextDrawAlignment(playerid, BoxItems[playerid][1], 1);
    PlayerTextDrawColor(playerid, BoxItems[playerid][1], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BoxItems[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxItems[playerid][1], 0);
    PlayerTextDrawFont(playerid, BoxItems[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, BoxItems[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][1], 18631);
    PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][1], 280.000000, 0.000000, 0.000000, 0.662100);

    BoxItems[playerid][2] = CreatePlayerTextDraw(playerid, 237.832901, 192.048202, ""); // Item #3;
    PlayerTextDrawLetterSize(playerid, BoxItems[playerid][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxItems[playerid][2], 32.000000, 40.000000);
    PlayerTextDrawAlignment(playerid, BoxItems[playerid][2], 1);
    PlayerTextDrawColor(playerid, BoxItems[playerid][2], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BoxItems[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxItems[playerid][2], 0);
    PlayerTextDrawFont(playerid, BoxItems[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, BoxItems[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][2], 18631);
    PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][2], 280.000000, 0.000000, 0.000000, 0.662100);

    BoxItems[playerid][3] = CreatePlayerTextDraw(playerid, 270.166503, 250.537094, ""); // Item #4;
    PlayerTextDrawLetterSize(playerid, BoxItems[playerid][3], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxItems[playerid][3], 32.000000, 40.000000);
    PlayerTextDrawAlignment(playerid, BoxItems[playerid][3], 1);
    PlayerTextDrawColor(playerid, BoxItems[playerid][3], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, BoxItems[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxItems[playerid][3], 0);
    PlayerTextDrawFont(playerid, BoxItems[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, BoxItems[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][3], 18631);
    PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][3], 280.000000, 0.000000, 0.000000, 0.662100);

    BoxItems[playerid][4] = CreatePlayerTextDraw(playerid, 335.833190, 250.537094, ""); // Item #5;
    PlayerTextDrawLetterSize(playerid, BoxItems[playerid][4], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxItems[playerid][4], 32.000000, 40.000000);
    PlayerTextDrawAlignment(playerid, BoxItems[playerid][4], 1);
    PlayerTextDrawColor(playerid, BoxItems[playerid][4], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, BoxItems[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxItems[playerid][4], 0);
    PlayerTextDrawFont(playerid, BoxItems[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, BoxItems[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, BoxItems[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxItems[playerid][4], 18631);
    PlayerTextDrawSetPreviewRot(playerid, BoxItems[playerid][4], 280.000000, 0.000000, 0.000000, 0.662100);

    BoxLight[playerid][0] = CreatePlayerTextDraw(playerid, 282.433105, 165.799804, "");
    PlayerTextDrawLetterSize(playerid, BoxLight[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxLight[playerid][0], 74.000000, 88.000000);
    PlayerTextDrawAlignment(playerid, BoxLight[playerid][0], 1);
    PlayerTextDrawColor(playerid, BoxLight[playerid][0], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BoxLight[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxLight[playerid][0], 0);
    PlayerTextDrawFont(playerid, BoxLight[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, BoxLight[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxLight[playerid][0], 2992);
    PlayerTextDrawSetPreviewRot(playerid, BoxLight[playerid][0], 280.000000, 0.000000, 0.000000, 0.547200);

    BoxLight[playerid][1] = CreatePlayerTextDraw(playerid, 347.433105, 165.799804, "");
    PlayerTextDrawLetterSize(playerid, BoxLight[playerid][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxLight[playerid][1], 74.000000, 88.000000);
    PlayerTextDrawAlignment(playerid, BoxLight[playerid][1], 1);
    PlayerTextDrawColor(playerid, BoxLight[playerid][1], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BoxLight[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxLight[playerid][1], 0);
    PlayerTextDrawFont(playerid, BoxLight[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, BoxLight[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxLight[playerid][1], 2992);
    PlayerTextDrawSetPreviewRot(playerid, BoxLight[playerid][1], 280.000000, 0.000000, 0.000000, 0.547200);

    BoxLight[playerid][2] = CreatePlayerTextDraw(playerid, 217.433105, 165.799804, "");
    PlayerTextDrawLetterSize(playerid, BoxLight[playerid][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxLight[playerid][2], 74.000000, 88.000000);
    PlayerTextDrawAlignment(playerid, BoxLight[playerid][2], 1);
    PlayerTextDrawColor(playerid, BoxLight[playerid][2], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BoxLight[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxLight[playerid][2], 0);
    PlayerTextDrawFont(playerid, BoxLight[playerid][2], 5);
    PlayerTextDrawSetProportional(playerid, BoxLight[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][2], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxLight[playerid][2], 2992);
    PlayerTextDrawSetPreviewRot(playerid, BoxLight[playerid][2], 280.000000, 0.000000, 0.000000, 0.547200);

    BoxLight[playerid][3] = CreatePlayerTextDraw(playerid, 249.766403, 224.288696, "");
    PlayerTextDrawLetterSize(playerid, BoxLight[playerid][3], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxLight[playerid][3], 74.000000, 88.000000);
    PlayerTextDrawAlignment(playerid, BoxLight[playerid][3], 1);
    PlayerTextDrawColor(playerid, BoxLight[playerid][3], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, BoxLight[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxLight[playerid][3], 0);
    PlayerTextDrawFont(playerid, BoxLight[playerid][3], 5);
    PlayerTextDrawSetProportional(playerid, BoxLight[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][3], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxLight[playerid][3], 2992);
    PlayerTextDrawSetPreviewRot(playerid, BoxLight[playerid][3], 280.000000, 0.000000, 0.000000, 0.547200);

    BoxLight[playerid][4] = CreatePlayerTextDraw(playerid, 315.433105, 224.288696, "");
    PlayerTextDrawLetterSize(playerid, BoxLight[playerid][4], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, BoxLight[playerid][4], 74.000000, 88.000000);
    PlayerTextDrawAlignment(playerid, BoxLight[playerid][4], 1);
    PlayerTextDrawColor(playerid, BoxLight[playerid][4], -3126017);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, BoxLight[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxLight[playerid][4], 0);
    PlayerTextDrawFont(playerid, BoxLight[playerid][4], 5);
    PlayerTextDrawSetProportional(playerid, BoxLight[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, BoxLight[playerid][4], 0);
    PlayerTextDrawSetPreviewModel(playerid, BoxLight[playerid][4], 2992);
    PlayerTextDrawSetPreviewRot(playerid, BoxLight[playerid][4], 280.000000, 0.000000, 0.000000, 0.547200);

    BoxItemsCount[playerid][0] = CreatePlayerTextDraw(playerid, 317.899902, 218.507400, "_"); // Item Count #1;
    PlayerTextDrawLetterSize(playerid, BoxItemsCount[playerid][0], 0.202550, 0.88570);
    PlayerTextDrawAlignment(playerid, BoxItemsCount[playerid][0], 2);
    PlayerTextDrawColor(playerid, BoxItemsCount[playerid][0], -1469906689);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BoxItemsCount[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxItemsCount[playerid][0], -103265537);
    PlayerTextDrawFont(playerid, BoxItemsCount[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, BoxItemsCount[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][0], 0);

    BoxItemsCount[playerid][1] = CreatePlayerTextDraw(playerid, 382.899902, 218.507400, "_"); // Item Count #2;
    PlayerTextDrawLetterSize(playerid, BoxItemsCount[playerid][1], 0.202550, 0.88570);
    PlayerTextDrawAlignment(playerid, BoxItemsCount[playerid][1], 2);
    PlayerTextDrawColor(playerid, BoxItemsCount[playerid][1], -1469906689);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BoxItemsCount[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxItemsCount[playerid][1], -103265537);
    PlayerTextDrawFont(playerid, BoxItemsCount[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, BoxItemsCount[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][1], 0);

    BoxItemsCount[playerid][2] = CreatePlayerTextDraw(playerid, 252.899902, 218.507400, "_"); // Item Count #3;
    PlayerTextDrawLetterSize(playerid, BoxItemsCount[playerid][2], 0.202550, 0.88570);
    PlayerTextDrawAlignment(playerid, BoxItemsCount[playerid][2], 2);
    PlayerTextDrawColor(playerid, BoxItemsCount[playerid][2], -1469906689);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BoxItemsCount[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxItemsCount[playerid][2], -103265537);
    PlayerTextDrawFont(playerid, BoxItemsCount[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, BoxItemsCount[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][2], 0);

    BoxItemsCount[playerid][3] = CreatePlayerTextDraw(playerid, 285.233398, 276.996185, "_"); // Item Count #4;
    PlayerTextDrawLetterSize(playerid, BoxItemsCount[playerid][3], 0.202550, 0.88570);
    PlayerTextDrawAlignment(playerid, BoxItemsCount[playerid][3], 2);
    PlayerTextDrawColor(playerid, BoxItemsCount[playerid][3], -1469906689);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, BoxItemsCount[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxItemsCount[playerid][3], -103265537);
    PlayerTextDrawFont(playerid, BoxItemsCount[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, BoxItemsCount[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][3], 0);

    BoxItemsCount[playerid][4] = CreatePlayerTextDraw(playerid, 350.900085, 276.996185, "_"); // Item Count #5;
    PlayerTextDrawLetterSize(playerid, BoxItemsCount[playerid][4], 0.202550, 0.88570);
    PlayerTextDrawAlignment(playerid, BoxItemsCount[playerid][4], 2);
    PlayerTextDrawColor(playerid, BoxItemsCount[playerid][4], -1469906689);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, BoxItemsCount[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxItemsCount[playerid][4], -103265537);
    PlayerTextDrawFont(playerid, BoxItemsCount[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, BoxItemsCount[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, BoxItemsCount[playerid][4], 0);

    BoxText[playerid][0] = CreatePlayerTextDraw(playerid, 318.899902, 111.485099, "СУНДУК С СОКРОВИЩАМИ");
    PlayerTextDrawLetterSize(playerid, BoxText[playerid][0], 0.466100, 1.965000);
    PlayerTextDrawAlignment(playerid, BoxText[playerid][0], 2);
    PlayerTextDrawColor(playerid, BoxText[playerid][0], -1469906689);
    PlayerTextDrawSetShadow(playerid, BoxText[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, BoxText[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxText[playerid][0], -103265537);
    PlayerTextDrawFont(playerid, BoxText[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, BoxText[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, BoxText[playerid][0], 0);

    BoxText[playerid][1] = CreatePlayerTextDraw(playerid, 320.433013, 127.248199, "FLIN_MOBILE");
    PlayerTextDrawLetterSize(playerid, BoxText[playerid][1], 0.376800, 1.574900);
    PlayerTextDrawAlignment(playerid, BoxText[playerid][1], 2);
    PlayerTextDrawColor(playerid, BoxText[playerid][1], -577765121);
    PlayerTextDrawSetShadow(playerid, BoxText[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, BoxText[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, BoxText[playerid][1], -103265537);
    PlayerTextDrawFont(playerid, BoxText[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, BoxText[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, BoxText[playerid][1], 0);

    BoxText[playerid][2] = CreatePlayerTextDraw(playerid, 320.933105, 334.770202, "ВЫЙТИ");
    PlayerTextDrawLetterSize(playerid, BoxText[playerid][2], 0.377000, 1.583400);
    PlayerTextDrawAlignment(playerid, BoxText[playerid][2], 2);
    PlayerTextDrawColor(playerid, BoxText[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, BoxText[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, BoxText[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, BoxText[playerid][2], 255);
    PlayerTextDrawFont(playerid, BoxText[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, BoxText[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, BoxText[playerid][2], 0);
    return 1;
}

// MapBox 
ShowMapBox(playerid, map_id)
{
    if(!GetInventoryAmount(playerid, 762+map_id))
        return SendError(playerid, "У вас нет %s.", ItemsInfo[762+map_id][iName]);

    new array_valid_box[MAX_BOX], iAllTotalBox, array_gold_box[MAX_BOX], iAllGoldBox;
    for(new i = MAX_BOX-1; i != -1; i--)
    {
        if(iAllTotalBox >= box_pickups_count) break;
        if(BoxInfo[i][boxCoordsMySQLIDx] == INVALID_MYSQL_ID) continue;
        if(map_id == 2 && BoxInfo[i][boxType] == TYPE_BOX_GOLD && random(2) == 0) continue;
        array_valid_box[iAllTotalBox] = i;
        iAllTotalBox++;
        if(BoxInfo[i][boxType] == TYPE_BOX_GOLD)
        {
            array_gold_box[iAllGoldBox] = i;
            iAllGoldBox++;
        }
    }

    if(!iAllTotalBox)
        return SendError(playerid, "Кладов не найдено. Попробуйте попозже.");
    HideMapZone(playerid);

    new box_id, Float:object_pos[2];
    
    if(map_id == 0 && iAllGoldBox > 0 && random(100) > 10)
        box_id = array_gold_box[random(iAllGoldBox)];
    else 
        box_id = array_valid_box[random(iAllTotalBox)];

    Streamer_GetFloatData(STREAMER_TYPE_AREA, BoxInfo[box_id][boxArea], E_STREAMER_X, object_pos[0]);
    Streamer_GetFloatData(STREAMER_TYPE_AREA, BoxInfo[box_id][boxArea], E_STREAMER_Y, object_pos[1]);

    new iWidth = 500,
		iHeight = 500,
	    radiusmap[3] = {150, 350, 500},
		Float:factormap[3] = {0.2, 0.7, 1.5},
        Float:position_width,
		Float:position_latitude;

	position_width = iWidth-(iWidth/radiusmap[map_id]*factormap[map_id])+object_pos[0];
	position_latitude = iHeight-(iHeight/radiusmap[map_id]*factormap[map_id])+object_pos[1];

	p_temp[playerid][MapTypeZone] = GangZoneCreate(object_pos[0]-radiusmap[map_id], object_pos[1]-radiusmap[map_id], position_width, position_latitude);
	GangZoneShowForPlayer(playerid, p_temp[playerid][MapTypeZone], 0xFFFFFF65);
    GangZoneFlashForPlayer(playerid, p_temp[playerid][MapTypeZone], 0x00000065);

    p_temp[playerid][MapTypeTime] = 120;
    p_temp[playerid][MapTypeID] = 1;

    GivePlayerInventory(playerid, 762+map_id, -1);

	SendInfo(playerid, "На карте отмечена мигающая зона в течении 2 минут, в которой находится выбранный клад.");
    return 1;
}

HideMapZone(playerid, bool:disconnect = false)
{
    if(p_temp[playerid][MapTypeZone] != 0)
    {
        GangZoneDestroy(p_temp[playerid][MapTypeZone]);

        p_temp[playerid][MapTypeZone] =
        p_temp[playerid][MapTypeTime] = 0;
        
        if(p_temp[playerid][MapTypeID] == 1)
            p_temp[playerid][MapTypeID] = 0;
        else if(p_temp[playerid][MapTypeID] == 2 && IsPlayerConnected(p_temp[playerid][MapTypeArgs]))
        {
            if(!disconnect) CreatePoliceMapZone(playerid);
            else 
            {
                p_temp[playerid][MapTypeID] = 0;
                p_temp[playerid][MapTypeArgs] = INVALID_PLAYER_ID;
            }
        }
        else p_temp[playerid][MapTypeArgs] = INVALID_PLAYER_ID;
    }
    return 1;
}

CMD:mapbox(playerid, params[])
{
    if(sscanf(params, "d", params[0]))
        return SendInfo(playerid, "Используйте: /mapbox [1-3] (1-Новая|2-Обычная|3-Старая)");
    if(!(1 <= params[0] <= 3))
        return SendInfo(playerid, "Используйте: /mapbox [1-3] (1-Новая|2-Обычная|3-Старая)");
    ShowMapBox(playerid, params[0]-1);
    return 1;
}