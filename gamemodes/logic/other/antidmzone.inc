#define MAX_ANTI_DM_ZONE    100
enum
{
    STATUS_ANTIDM_NONE = 200500,
    STATUS_ANTIDM_POS1,
    STATUS_ANTIDM_POS2,
    STATUS_ANTIDM_GO_OBJECT,
    STATUS_ANTIDM_OBJECT
}
enum e_DMInfo
{
    dmMysqlID,
    dmType,
Float:dmX1,
Float:dmY1,
Float:dmZ1,
Float:dmX2,
Float:dmY2,
Float:dmZ2,
Float:dmInfoX,
Float:dmInfoY,
Float:dmInfoZ,
Float:dmInfoRZ,
Text3D:dm3DLabel,
    dmRadius,
    dmObject,
    dmArea,
    dmVW,
    dmInt,
    dmFlag[MAX_FRACTIONS],
};
new AntiDMInfo[MAX_ANTI_DM_ZONE][e_DMInfo],
    count_antidm;


CMD:dmzone(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    ShowPlayerDialog(playerid, D_ANTIDM_MENU, DIALOG_STYLE_LIST,""I"DM ZONE",""I"[1]"W" Добавить\n"I"[2]"W" Удалить\n"I"[3]"W" Настройки ДМ-зоны","Выбрать","Закрыть");
    return 1;
}

CMD:dmpos(playerid, params[])
{
    new Float:pPos_x, Float:pPos_y, Float:pPos_z;
    GetPlayerPos(playerid, pPos_x, pPos_y, pPos_z);
    if(p_temp[playerid][p_listitem_int] == STATUS_ANTIDM_GO_OBJECT)
    {
        if(!IsPlayerToSquare(playerid, AntiDMInfo[count_antidm][dmX1], AntiDMInfo[count_antidm][dmY1], AntiDMInfo[count_antidm][dmX2], AntiDMInfo[count_antidm][dmY2]))
            return SendError(playerid, "Поставить знак можно только в квадрате Анти ДМ зоны. Рома не тупи.");
        new object_anti_dm = CreateDynamicObject(19973, pPos_x+(random(1)), pPos_y+random(1), pPos_z-1.2, 0.0, 0.0, 0.0);
        EditDynamicObject(playerid, object_anti_dm);
        p_temp[playerid][p_listitem_int] = STATUS_ANTIDM_OBJECT;
        return 1;
    }
    if(p_temp[playerid][p_listitem_int] == STATUS_ANTIDM_POS1)
    {
        AntiDMInfo[count_antidm][dmX1] = pPos_x;
        AntiDMInfo[count_antidm][dmY1] = pPos_y;
        AntiDMInfo[count_antidm][dmZ1] = pPos_z;
        SendInfo(playerid, "Первые координаты установлены, теперь установите вторые под углом 45 градусов(!!!), повторите команду.");
        p_temp[playerid][p_listitem_int] = STATUS_ANTIDM_POS2;
        return 1;
    }
    if(p_temp[playerid][p_listitem_int] == STATUS_ANTIDM_POS2)
    {
        AntiDMInfo[count_antidm][dmX2] = pPos_x;
        AntiDMInfo[count_antidm][dmY2] = pPos_y;
        AntiDMInfo[count_antidm][dmZ2] = pPos_z;
        SendInfo(playerid, "Вторые координаты установлены, теперь выберите место где будет знак информации и повторите команду.");
        p_temp[playerid][p_listitem_int] = STATUS_ANTIDM_GO_OBJECT;
    }
    new Float:tmp_coord;
    if(AntiDMInfo[count_antidm][dmX1] > AntiDMInfo[count_antidm][dmX2])
    {
        tmp_coord = AntiDMInfo[count_antidm][dmX1];
        AntiDMInfo[count_antidm][dmX1] = AntiDMInfo[count_antidm][dmX2];
        AntiDMInfo[count_antidm][dmX2] = tmp_coord;
    }
    if(AntiDMInfo[count_antidm][dmY1] > AntiDMInfo[count_antidm][dmY2])
    {
        tmp_coord = AntiDMInfo[count_antidm][dmY1];
        AntiDMInfo[count_antidm][dmY1] = AntiDMInfo[count_antidm][dmY2];
        AntiDMInfo[count_antidm][dmY2] = tmp_coord;
    }
    if(AntiDMInfo[count_antidm][dmZ1] > AntiDMInfo[count_antidm][dmZ2])
    {
        tmp_coord = AntiDMInfo[count_antidm][dmZ1];
        AntiDMInfo[count_antidm][dmZ1] = AntiDMInfo[count_antidm][dmZ2];
        AntiDMInfo[count_antidm][dmZ2] = tmp_coord;
    }
    return 1;
}

CreateDMZ(playerid)
{
    AntiDMInfo[count_antidm][dmInt] = GetPlayerInterior(playerid);
    AntiDMInfo[count_antidm][dmVW] = GetPlayerVirtualWorld(playerid);

    if(AntiDMInfo[count_antidm][dmType] == 0)
    {
        AntiDMInfo[count_antidm][dmArea] = CreateDynamicSphere(AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ], AntiDMInfo[count_antidm][dmRadius], AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt] , -1);
        UpdateAreaInfo(AntiDMInfo[count_antidm][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, count_antidm);
    }
    else
    {
        AntiDMInfo[count_antidm][dmRadius] = 0;
        AntiDMInfo[count_antidm][dmArea] = CreateDynamicCube(AntiDMInfo[count_antidm][dmX1], AntiDMInfo[count_antidm][dmY1], AntiDMInfo[count_antidm][dmZ1]-10.0, AntiDMInfo[count_antidm][dmX2], AntiDMInfo[count_antidm][dmY2], AntiDMInfo[count_antidm][dmZ2]+10.0, AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt] , -1);
        UpdateAreaInfo(AntiDMInfo[count_antidm][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, count_antidm);
    }

    AntiDMInfo[count_antidm][dm3DLabel] = CreateDynamic3DTextLabel("[ Зеленая зона ]\nЗдесь запрещено драться", COLOR_MAIN, AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ]+2.0, 15.0,INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt],-1);
    AntiDMInfo[count_antidm][dmObject] = CreateDynamicObject(19973, AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ], 0.0, 0.0, AntiDMInfo[count_antidm][dmInfoRZ], AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt]);
    for(new i = MAX_FRACTIONS-1; i != -1; i--) AntiDMInfo[count_antidm][dmFlag][i] = 0;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL,
        "INSERT INTO `antidm_info` (`X1`, `Y1`, `Z1`, `X2`, `Y2`, `Z2`, `infoX`, `infoY`, `infoZ`, `infoRZ`, `radius`, `type`, `virt`,`int`) VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', %d,%d,%d,%d)",
        AntiDMInfo[count_antidm][dmX1], AntiDMInfo[count_antidm][dmY1], AntiDMInfo[count_antidm][dmZ1],
        AntiDMInfo[count_antidm][dmX2], AntiDMInfo[count_antidm][dmY2], AntiDMInfo[count_antidm][dmZ2],
        AntiDMInfo[count_antidm][dmInfoX], AntiDMInfo[count_antidm][dmInfoY], AntiDMInfo[count_antidm][dmInfoZ], AntiDMInfo[count_antidm][dmInfoRZ],
        AntiDMInfo[count_antidm][dmRadius], AntiDMInfo[count_antidm][dmType], AntiDMInfo[count_antidm][dmVW], AntiDMInfo[count_antidm][dmInt]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_antidm", "i", count_antidm);
    return true;
}
forward create_antidm(id);
public create_antidm(id)
{
    AntiDMInfo[id][dmMysqlID] = cache_insert_id();
    count_antidm++;
    return 1;
}

this::LoadDynamicAntiDM()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;
    if (!rows) return print("[ANTI-DM] Записи не найдены.");
    new data[128];
    for(new i; i < rows; i++)
    {
        cache_get_value_name_int(i, "id", AntiDMInfo[i][dmMysqlID]);
        cache_get_value_name_float(i, "X1", AntiDMInfo[i][dmX1]);
        cache_get_value_name_float(i, "Y1", AntiDMInfo[i][dmY1]);
        cache_get_value_name_float(i, "Z1", AntiDMInfo[i][dmZ1]);
        cache_get_value_name_float(i, "X2", AntiDMInfo[i][dmX2]);
        cache_get_value_name_float(i, "Y2", AntiDMInfo[i][dmY2]);
        cache_get_value_name_float(i, "Z2", AntiDMInfo[i][dmZ2]);
        cache_get_value_name_float(i, "infoX", AntiDMInfo[i][dmInfoX]);
        cache_get_value_name_float(i, "infoY", AntiDMInfo[i][dmInfoY]);
        cache_get_value_name_float(i, "infoZ", AntiDMInfo[i][dmInfoZ]);
        cache_get_value_name_float(i, "infoRZ", AntiDMInfo[i][dmInfoRZ]);
        cache_get_value_name_int(i, "radius", AntiDMInfo[i][dmRadius]);
        cache_get_value_name_int(i, "type", AntiDMInfo[i][dmType]);
        cache_get_value_name_int(i, "int", AntiDMInfo[i][dmInt]);
        cache_get_value_name_int(i, "virt", AntiDMInfo[i][dmVW]);

        cache_get_value_name(i, "flags", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
        sscanf(data, "p<|>a<i>[26]", AntiDMInfo[i][dmFlag]);

        if(AntiDMInfo[i][dmType] == 0)
        {
            AntiDMInfo[i][dmArea] = CreateDynamicSphere(AntiDMInfo[i][dmInfoX], AntiDMInfo[i][dmInfoY], AntiDMInfo[i][dmInfoZ], AntiDMInfo[i][dmRadius], AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt] , -1);
            UpdateAreaInfo(AntiDMInfo[i][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, i);
        }
        else
        {
            AntiDMInfo[i][dmRadius] = 0;
            AntiDMInfo[i][dmArea] = CreateDynamicCube(AntiDMInfo[i][dmX1], AntiDMInfo[i][dmY1], AntiDMInfo[i][dmZ1]-10.0, AntiDMInfo[i][dmX2], AntiDMInfo[i][dmY2], AntiDMInfo[i][dmZ2]+10.0, AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt] , -1);
            UpdateAreaInfo(AntiDMInfo[i][dmArea], TYPE_GREENZONE, AREA_SUBTYPE_INVALID_ID, i);
        }

        new count;
        STRING_GLOBAL[0] = EOS;
        for(new d; d < MAX_FRACTIONS; d++)
        {
            if(AntiDMInfo[i][dmFlag][d] == 0) continue;
            f(STRING_GLOBAL,"%s"W"[%d]"I" %s\n",STRING_GLOBAL, count+1, GetFractionName(d));
            count++;
		}
		if(!count) strcat(STRING_GLOBAL,"[ Зеленая зона ]\nЗдесь запрещено драться");
		else f(STRING_GLOBAL,"[ Зеленая зона ]\nЗдесь разрешено драться только:\n%s", STRING_GLOBAL);

        AntiDMInfo[i][dm3DLabel] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, AntiDMInfo[i][dmInfoX],AntiDMInfo[i][dmInfoY],AntiDMInfo[i][dmInfoZ]+2.0, 15.0,INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt],-1);
        AntiDMInfo[i][dmObject] = CreateDynamicObject(19973, AntiDMInfo[i][dmInfoX], AntiDMInfo[i][dmInfoY], AntiDMInfo[i][dmInfoZ], 0.0, 0.0, AntiDMInfo[i][dmInfoRZ], AntiDMInfo[i][dmVW], AntiDMInfo[i][dmInt]);
        count_antidm++;
    }
    printf("[AntiDM] Строк - %i. Загружено - %i. Затрачено: %i ms.", rows, total, GetTickCount()-time);
    return 1;
}
