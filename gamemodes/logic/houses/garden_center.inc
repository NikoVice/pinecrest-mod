#define MAX_GARDEN              2500
#define MAX_GARDEN_CENTER       28
#define GARDEN_SEEDS_PRICE      250000

new totalgarden;

enum E_GARDEN_HOUSE_INFO
{
    gMySQLIDx,
    gType,
    gObject[2],
    gDay,
    gHouseIDx,
    gBizIDx,
    Float:gPos[6],
    Text3D:gText
};
new GardenInfo[MAX_GARDEN][E_GARDEN_HOUSE_INFO];

enum
{
    TYPE_GARDEN_HOUSE,
    TYPE_GARDEN_BIZ
}

enum E_GARDEN_CENTER
{
    GardenCenterIDx,
    GardenCenterName[32],
    GardenCenterObject,
    GardenCenterPrice,
    Float:GardenCenterPos
}

new GardenCenter[MAX_GARDEN_CENTER][E_GARDEN_CENTER] = {
    {1, "Новогодняя елка", 19076, 50000, {1.0}},
    {2, "Хвойное дерево", 655, 7500, {0.8}},
    {3, "Высокополигональное дерево", 732, 5000, {1.0}},
    {4, "Пальма с украшением", 3505, 25000, {1.0}},
    {5, "Клён", 713, 20000, {0.9}},
    {6, "Берёза", 774, 10000, {1.0}},
    {7, "Гледичия трёхколючковая", 726, 20000, {1.0}},
    {8, "Баобаб", 616, 20000, {1.0}},
    {9, "Берёза бумажная", 777, 15000, {1.0}},
    {10, "Сосна", 658, 10000, {0.9}},
    {11, "Ель", 656, 10000, {0.9}},
    {12, "Большая прямая пальма", 645, 15000, {0.9}},
    {13, "Клён сахарный", 778, 5000, {1.0}},
    {14, "Ива", 886, 5000, {1.0}},
    {15, "Рябина", 889, 5000, {1.0}},
    {16, "Густая невысокая сосна", 657, 5000, {0.9}},
    {17, "Аралия", 779, 5000, {1.0}},
    {18, "Лавочка", 1280, 2500, {0.5}},
    {19, "Лежак", 1255, 5000, {0.5}},
    {20, "Стол с лавочкой и зонтиком", 1281, 10000, {0.2}},
    {21, "Гриль", 19831, 10000, {1.0}},
    {22, "Телескоп", 2600, 15000, {0.2}},
    {23, "Спутниковая тарелка", 3031, 10000, {-0.2}},
    {24, "Миниган", 2985, 25000, {1.0}},
    {25, "Ракетная установка", 3267, 50000, {1.4}},
    {26, "Статуя CJ", 2745, 20000, {0.1}},
    {27, "Танцевальная площадка", 19128, 25000, {1.0}},
    {28, "Фонтан", 3515, 100000, {0.2}}
};

ShowGarden(playerid, type)
{
    switch(type)
    {
        case 0:
        {
            new h = GetPlayerHouseID(playerid);
            if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");

            if(GetGardenObject(TYPE_GARDEN_HOUSE, h) >= GetMaxGardenObject(TYPE_GARDEN_HOUSE, h)) return SendError(playerid, "На территории сада нет свободного места под объект.");
            STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
            for(new idx = 0; idx < sizeof(GardenCenter); idx++)
            {
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [Кол-во: %d]\n", idx + 1, GardenCenter[idx][GardenCenterName], h_info[h][h_garden_items][idx]);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_GARDEN_CREATE, DIALOG_STYLE_LIST, ""I"Установить объект", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "Garden:type", TYPE_GARDEN_HOUSE + 1);
        }
        case 1:
        {
            new h = GetPlayerHouseID(playerid);
            if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");

            new count = 0;
            STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
            for(new idx = 1; idx <= totalgarden; idx++)
            {
                if(GardenInfo[idx][gHouseIDx] != h) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [Осталось дней: %d]\n", count + 1, GardenCenter[GardenInfo[idx][gType]][GardenCenterName], GardenInfo[idx][gDay]);
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = idx;
                count++;
            }
            if(count == 0) return SendError(playerid, "На территории сада не найдено ни одного объекта.");
            ShowPlayerDialog(playerid, D_GARDEN_DESTROY, DIALOG_STYLE_LIST, ""I"Удалить объект", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "Garden:type", TYPE_GARDEN_HOUSE + 1);
        }
        case 2:
        {
            new b = GetPlayerBizzID(playerid);
            if(b == INVALID_BIZZ_ID) return SendError(playerid, "У Вас нет бизнеса.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, b_info[b][b_enter][0], b_info[b][b_enter][1], b_info[b][b_enter][2])) return SendError(playerid, "Вы слишком далеко от бизнеса.");

            if(GetGardenObject(TYPE_GARDEN_BIZ, b) >= GetMaxGardenObject(TYPE_GARDEN_BIZ, b)) return SendError(playerid, "На территории сада нет свободного места под объект.");
            STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
            for(new idx = 0; idx < sizeof(GardenCenter); idx++)
            {
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [Кол-во: %d]\n", idx + 1, GardenCenter[idx][GardenCenterName], b_info[b][b_garden_items][idx]);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_GARDEN_CREATE, DIALOG_STYLE_LIST, ""I"Установить объект", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "Garden:type", TYPE_GARDEN_BIZ + 1);
        }
        case 3:
        {
            new b = GetPlayerBizzID(playerid);
            if(b == INVALID_BIZZ_ID) return SendError(playerid, "У Вас нет бизнеса.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, b_info[b][b_enter][0], b_info[b][b_enter][1], b_info[b][b_enter][2])) return SendError(playerid, "Вы слишком далеко от бизнеса.");

            new count = 0;
            STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
            for(new idx = 1; idx <= totalgarden; idx++)
            {
                if(GardenInfo[idx][gBizIDx] != b) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [Осталось дней: %d]\n", count + 1, GardenCenter[GardenInfo[idx][gType]][GardenCenterName], GardenInfo[idx][gDay]);
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = idx;
                count++;
            }
            if(count == 0) return SendError(playerid, "На территории сада не найдено ни одного объекта.");
            ShowPlayerDialog(playerid, D_GARDEN_DESTROY, DIALOG_STYLE_LIST, ""I"Удалить объект", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "Garden:type", TYPE_GARDEN_BIZ + 1);
        }
    }
    return 1;
}

GetGardenObject(type, idx)
{
    new count = 0;
    switch(type)
    {
        case TYPE_GARDEN_HOUSE:
        {
            for(new i = 1; i <= totalgarden; i++)
            {
                if(GardenInfo[i][gHouseIDx] == idx) count++;
            }
        }
        case TYPE_GARDEN_BIZ:
        {
            for(new i = 1; i <= totalgarden; i++)
            {
                if(GardenInfo[i][gBizIDx] == idx) count++;
            }
        }
    }
    return count;
}

GetMaxGardenObject(type, idx)
{
    new count = 3;
    switch(type)
    {
        case TYPE_GARDEN_HOUSE:
        {
            new squar = h_info[idx][h_squar];
            switch(squar)
            {
                case 1: return 3;
                case 2: return 5;
                case 3: return 7;
                case 4: return 10;
            }
        }
        case TYPE_GARDEN_BIZ: return 10;
    }
    return count;
}

forward load_garden();
public load_garden()
{
    new time = GetTickCount(), str[512];
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iiiiiiffffff",
            GardenInfo[idx][gMySQLIDx],
            GardenInfo[idx][gType],
            GardenInfo[idx][gObject][0],
            GardenInfo[idx][gDay],
            GardenInfo[idx][gHouseIDx],
            GardenInfo[idx][gBizIDx],
            GardenInfo[idx][gPos][0],
            GardenInfo[idx][gPos][1],
            GardenInfo[idx][gPos][2],
            GardenInfo[idx][gPos][3],
            GardenInfo[idx][gPos][4],
            GardenInfo[idx][gPos][5]);

            GardenInfo[idx][gObject][1] = CreateDynamicObject(GardenInfo[idx][gObject], GardenInfo[idx][gPos][0], GardenInfo[idx][gPos][1], GardenInfo[idx][gPos][2], GardenInfo[idx][gPos][3], GardenInfo[idx][gPos][4], GardenInfo[idx][gPos][5], -1, -1, -1, 120.00, 120.00);
            totalgarden++;
        }
    }
    printf("Объектов в садах загружено: %d за %d мс", totalgarden, GetTickCount() - time);
}

forward create_garden(idx);
public create_garden(idx)
{
    GardenInfo[idx][gMySQLIDx] = cache_insert_id();
    return 1;
}

CreateGarden(playerid)
{
    new type = GetPVarInt(playerid, "LoadGardenType") - 1, i = GetPVarInt(playerid, "LoadGarden")-1, listitem = GetPVarInt(playerid, "LoadGardenListitem"), idx = GetPVarInt(playerid, "GardenObject");
    switch(type)
    {
        case TYPE_GARDEN_HOUSE:
        {
            new h = GetPlayerHouseID(playerid);
            if(h == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет дома.");
            if(h_info[h][h_garden_items][listitem] == 0) return SendError(playerid, "На складе нет данного объекта.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2])) return SendError(playerid, "Вы слишком далеко от дома.");
            if(GetGardenObject(TYPE_GARDEN_HOUSE, h) >= GetMaxGardenObject(TYPE_GARDEN_HOUSE, h)) return SendError(playerid, "На территории сада нет свободного места под объект.");
            GardenInfo[i][gHouseIDx] = h;
            GardenInfo[i][gBizIDx] = 0;

            h_info[h][h_garden_items][listitem]--;
            save_house(h);
        }
        case TYPE_GARDEN_BIZ:
        {
            new b = GetPlayerBizzID(playerid);
            if(b == INVALID_HOUSE_ID) return SendError(playerid, "У Вас нет бизнеса.");
            if(b_info[b][b_garden_items][listitem] == 0) return SendError(playerid, "На складе нет данного объекта.");
            if(!IsPlayerInRangeOfPoint(playerid, 25.0, b_info[b][b_enter][0], b_info[b][b_enter][1], b_info[b][b_enter][2])) return SendError(playerid, "Вы слишком далеко от бизнеса.");
            if(GetGardenObject(TYPE_GARDEN_BIZ, b) >= GetMaxGardenObject(TYPE_GARDEN_BIZ, b)) return SendError(playerid, "На территории сада нет свободного места под объект.");
            GardenInfo[i][gBizIDx] = b;
            GardenInfo[i][gHouseIDx] = 0;

            b_info[b][b_garden_items][listitem]--;
            save_bizz(b);
        }
    }

    DestroyObject(GardenInfo[i][gObject][1]);
    DeletePVar(playerid, "LoadGardenType");
    DeletePVar(playerid, "LoadGarden");
    DeletePVar(playerid, "LoadGardenListitem");
    DeletePVar(playerid, "GardenObject");

    new Float:PlPos[4];
    GetPlayerPos(playerid, PlPos[0], PlPos[1], PlPos[2]);
    GetPlayerFacingAngle(playerid, PlPos[3]);

    GardenInfo[i][gType] = listitem;
    GardenInfo[i][gObject][0] = idx;
    GardenInfo[i][gDay] = listitem < 17 ? 7 : 14;
    GardenInfo[i][gPos][0] = PlPos[0]+floatcos(PlPos[3]+90, degrees);
    GardenInfo[i][gPos][1] = PlPos[1]+floatsin(PlPos[3]+90, degrees);
    GardenInfo[i][gPos][2] = PlPos[2] - GardenCenter[listitem][GardenCenterPos];
    GardenInfo[i][gPos][3] = 0.0;
    GardenInfo[i][gPos][4] = 0.0;
    GardenInfo[i][gPos][5] = PlPos[3]+90;

    GardenInfo[i][gObject][1] = CreateDynamicObject(idx, GardenInfo[i][gPos][0], GardenInfo[i][gPos][1], GardenInfo[i][gPos][2], GardenInfo[i][gPos][3], GardenInfo[i][gPos][4], GardenInfo[i][gPos][5], -1, -1, -1, 120.00, 120.00);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `garden` (`type`, `object`, `day`, `house`, `biz`, `x`, `y`, `z`, `rx`, `ry`, `rz`) VALUES (%d, %d, %d, %d, %d, '%f', '%f', '%f', '%f', '%f', '%f')",
    GardenInfo[i][gType], GardenInfo[i][gObject][0], GardenInfo[i][gDay], GardenInfo[i][gHouseIDx], GardenInfo[i][gBizIDx], GardenInfo[i][gPos][0], GardenInfo[i][gPos][1], GardenInfo[i][gPos][2], GardenInfo[i][gPos][3], GardenInfo[i][gPos][4], GardenInfo[i][gPos][5]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_garden", "i", i);

    SendAccess(playerid, "Вы установили объект \"%s\".", GardenCenter[listitem][GardenCenterName]);
    return 1;
}

DestroyGarden(idx)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `garden` WHERE `id` = %d",
    GardenInfo[idx][gMySQLIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    GardenInfo[idx][gMySQLIDx] = 0;
    GardenInfo[idx][gType] = 0;
    GardenInfo[idx][gObject][0] = 0;
    GardenInfo[idx][gDay] = 0;
    GardenInfo[idx][gHouseIDx] = 0;
    GardenInfo[idx][gPos][0] = 0.0;
    GardenInfo[idx][gPos][1] = 0.0;
    GardenInfo[idx][gPos][2] = 0.0;
    GardenInfo[idx][gPos][3] = 0.0;
    GardenInfo[idx][gPos][4] = 0.0;
    GardenInfo[idx][gPos][5] = 0.0;
    if(IsValidDynamicObject(GardenInfo[idx][gObject][1])) DestroyDynamicObject(GardenInfo[idx][gObject][1]);
    if(IsValidDynamic3DTextLabel(GardenInfo[idx][gText])) DestroyDynamic3DTextLabel(GardenInfo[idx][gText]);
    return 1;
}

CMD:garden(playerid)
{
    ShowPlayerDialog(playerid, D_GARDEN, DIALOG_STYLE_LIST, ""I"Управление садом", ""I"[1]"W" Дом\n"I"[2]"W" Бизнес", "Далее", "Отмена");
    return 1;
}

CMD:dgardenhouse(playerid, params[0])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /dgardenhouse [id дома]");

    new
        houseId = strval(params);

    if(!(0 <= houseId < totalhouses))
        return SendError(playerid, "Неверный ID дома.");
    if(h_info[houseId][h_mysql_id] == INVALID_MYSQL_ID)
        return SendError(playerid, "Дом не задействован.");
    new count = 0;
    for(new i = 1; i <= totalgarden; i++)
    {
        if(GardenInfo[i][gHouseIDx] != houseId) continue;
        DestroyGarden(i);
        count++;
    }

    if(count == 0) return SendError(playerid, "На территории сада данного дома нет объектов.");

    if(h_info[houseId][h_user_id] != INVALID_MYSQL_ID)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, ""I"%s"W" удалил(-а) все объекты на территории сада Вашего дома.", get_name(playerid));
        AddNotify(h_info[houseId][h_user_id], STRING_GLOBAL);
    }

    SendAccess(playerid, "Вы удалили все объекты на территории сада дома %d.", houseId);

    Log(LOG_player, INFO, "%s[%d](%s %s) удалил объекты дома (%d) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", houseId);
    return 1;
}

CMD:dgardenbiz(playerid, params[0])
{
    if(p_info[playerid][admin] < 4)
        return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /dgardenbiz [id бизнеа]");

    new
        bizId = strval(params);

    if(!(0 <= bizId < totalbizz))
        return SendError(playerid, "Неверный ID дома.");
    if(b_info[bizId][b_mysql_id] == INVALID_MYSQL_ID)
        return SendError(playerid, "Бизнес не задействован.");
    new count = 0;
    for(new i = 1; i <= totalgarden; i++)
    {
        if(GardenInfo[i][gBizIDx] != bizId) continue;
        DestroyGarden(i);
        count++;
    }

    if(count == 0) return SendError(playerid, "На территории сада данного бизнеса нет объектов.");

    if(b_info[bizId][b_user_id] != INVALID_MYSQL_ID)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, ""I"%s"W" удалил(-а) все объекты на территории бизнеса Вашего дома.", get_name(playerid));
        AddNotify(h_info[bizId][h_user_id], STRING_GLOBAL);
    }

    SendAccess(playerid, "Вы удалили все объекты на территории сада бизнеса %d.", bizId);

    Log(LOG_player, INFO, "%s[%d](%s %s) удалил объекты бизнеса (%d) | #AdminLogs",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", bizId);
    return 1;
}