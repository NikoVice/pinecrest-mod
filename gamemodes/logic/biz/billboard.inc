#define MAX_BILLBOARD           24
#define MAX_BILLBOARD_COLOR     14

#define BILLBOARD_PRICE_RENT    10000

enum E_BB_INFO
{
    bbMySQLID,
    bbPlayerID,
    bbDays,
    bbName[32],
    bbText[256],
    bbMaterialSize,
    bbFontFace,
    bbFontSize,
    bbFontBold,
    bbFontColor,
    bbBackColor,
    bbTextAligment,
    bbObject[2]
};
new BillboardInfo[MAX_BILLBOARD][E_BB_INFO];

new Float:BillboardPos[MAX_BILLBOARD][12] = {
    {1529.41589, -1736.75378, 25.22300, 0.00000, 0.00000, 90.00000,     1529.09766, -1738.18091, 33.89480, 0.00000, 0.00000, 110.67000},
    {1434.72937, -1704.88086, 25.22300, 0.00000, 0.00000, 180.00000,    1436.16174, -1705.18713, 33.89480, 0.00000, 0.00000, 200.67000},
    {-1994.05396, -70.11350, 46.88510, 0.00000, 0.00000, 0.00000,       -1995.48926, -69.84170, 55.55350, 0.00000, 0.00000, 20.67000},
    {2610.82886, -2380.88354, 25.25990, 0.00000, 0.00000, 180.00000,    2610.49414, -2380.56787, 34.90190, 0.00000, 0.00000, 200.70000},
    {1128.62122, -1390.80945, 25.22300, 0.00000, 0.00000, -90.00000,    1128.82666, -1389.38049, 33.88630, 0.00000, 0.00000, -69.33000},
    {290.68750, -1576.89465, 44.77570, 0.00000, 0.00000, 258.30011,     291.24951, -1575.54224, 53.43240, 0.00000, 0.00000, -81.05200},
    {1790.66895, -1810.09607, 25.18900, 0.00000, 0.00000, 90.00000,    1790.66895, -1810.76672, 33.83750, 0.00000, 0.00000, 110.69990},
    {1019.26147, -1984.68042, 23.51440, 0.00000, 0.00000, 45.00000,     1018.23090, -1985.62695, 33.34950, 0.00000, 0.00000, 65.64020},
    {1523.79565, 87.34520, 40.27720, 0.00000, 0.00000, 73.74020,        1522.98145, 86.07610, 48.94890, 0.00000, 0.00000, 94.40000},
    {-1978.81653, 1091.87256, 67.32530, 0.00000, 0.00000, -45.00000,    -1979.66174, 1093.08765, 75.96670, 0.00000, 0.00000, -24.34000},
    {1441.29065, -1604.22961, 25.22300, 0.00000, 0.00000, -225.00000,   1442.08374, -1605.50110, 33.89480, 0.00000, 0.00000, 155.66400},
    {2013.60962, 875.19849, 20.07380, 0.00000, 0.00000, -45.00000,      2012.76184, 876.40771, 28.74650, 0.00000, 0.00000, -24.36000},
    {2122.42090, 1751.18835, 22.46000, 0.00000, 0.00000, 225.00000,     2123.50000, 1752.03418, 31.13530, 0.00000, 0.00000, 245.52010},
    {80.38210, -1512.23877, 16.33470, 0.00000, 0.00000, -45.00000,      79.50810, -1511.05737, 24.99890, 0.00000, 0.00000, -24.36000},
    {1727.96167, -700.50763, 58.04490, 0.00000, 0.00000, -135.00000,    1729.20728, -699.72278, 66.74170, 0.00000, 0.00000, 245.70010},
    {-1786.56885, -616.31549, 28.09020, 0.00000, 0.00000, -45.00000,    -1787.46851, -615.15033, 36.76410, 0.00000, 0.00000, -24.32000},
    {1829.35388, 874.92242, 20.07380, 0.00000, 0.00000, -135.00000,     1830.56885, 875.75580, 28.74650, 0.00000, 0.00000, -114.36010},
    {1210.59375, -1323.60522, 25.18130, 0.00000, 0.00000, 180.00000,    1212.03369, -1323.98767, 33.84000, 0.00000, 0.00000, 200.66600},
    {-2540.46509, 598.50482, 31.30300, 0.00000, 0.00000, 180.00000,     -2539.03979, 598.74939, 39.97990, 0.00000, 0.00000, -159.34950},
    {1607.75586, 1877.71411, 22.46770, 0.00000, 0.00000, -90.00000,     1607.97900, 1879.16479, 31.12700, 0.00000, 0.00000, -69.36000},
    {1154.49768, -1723.03064, 25.60330, 0.00000, 0.00000, -90.00000,    1154.75598, -1721.57922, 34.26790, 0.00000, 0.00000, -69.36010},
    {-2049.50513, 128.43640, 40.50720, 0.00000, 0.00000, 45.00000,      -2050.71338, 127.59980, 49.17810, 0.00000, 0.00000, 65.68000},
    {2792.38550, 1328.25452, 22.51000, 0.00000, 0.00000, -45.00000,     2791.54712, 1329.48010, 31.17160, 0.00000, 0.00000, -24.32000},
    {1861.42761, -1871.54883, 25.18970, 0.00000, 0.00000, 180.00000,    1862.86023, -1871.75867, 33.85400, 0.00000, 0.00000, -159.36000}
};

new BillboardFontFaceName[21][32] = {"Arial", "Courier New", "Callibri", "Engravers MT", "Fixedsys", "Comic Sans MS", "Georgia", "Impact", "Lucida Console", "Lucida Sans Unicode", "Palatino Linotype", "Tahoma", "Times New Roman", "Trebuchet MS", "Verdana", "Monotype Corsiva", "Franklin Gothic Medium", "Segoe UI", "Segoe Script", "Palatino Linotype", "Arial Black"};
new BillboardMaterialSizeName[14][32] = {"32 x 32 (10)", "64 x 32 (20)", "64 x 64 (30)", "128 x 32 (40)", "128 x 64 (50)", "128 x 128 (60)", "256 x 32 (70)", "256 x 64 (80)", "256 x 128 (90)", "256 x 256 (100)", "512 x 64 (110)", "512 x 128 (120)", "512 x 256 (130)", "512 x 512 (140)"};
new BillboardAligmentName[3][32] = {"По левому краю", "По центру", "По правому краю"};

enum E_BBC_INFO
{
    bbcName[32],
    bbcColorRBG
};
new BillboardColorInfo[MAX_BILLBOARD_COLOR][E_BBC_INFO] = {
    {"Белый", 0xFFFFFFFF},
    {"Чёрный", 0xFF000000},
    {"Серый", 0xFF808080},
    {"Красный", 0xFFFF0000},
    {"Жёлтый", 0xFFFFFF00},
    {"Зелёный", 0xFF008000},
    {"Синий", 0xFF0000FF},
    {"Голубой", 0xFF00FFFF},
    {"Коричневый", 0xFF8B4513},
    {"Оранжевый", 0xFFFFA500},
    {"Фиолетовый", 0xFF800080},
    {"Шоколадный", 0xFFD2691E},
    {"Розовый", 0xFFFF1493},
    {"Лайм", 0xFF00FF00}
};

forward load_billboard();
public load_billboard()
{
    new time = GetTickCount(), rows;

    cache_get_row_count(rows);
    if(rows)
    {
        for(new idx; idx < rows; idx++)
        {
            cache_get_value_name_int(idx, "id", BillboardInfo[idx][bbMySQLID]);
            cache_get_value_name_int(idx, "playerid", BillboardInfo[idx][bbPlayerID]);
            cache_get_value_name_int(idx, "days", BillboardInfo[idx][bbDays]);
            cache_get_value_name(idx, "name", BillboardInfo[idx][bbName]);
            cache_get_value_name(idx, "text", BillboardInfo[idx][bbText]);
            cache_get_value_name_int(idx, "materialsize", BillboardInfo[idx][bbMaterialSize]);
            cache_get_value_name_int(idx, "fontface", BillboardInfo[idx][bbFontFace]);
            cache_get_value_name_int(idx, "fontsize", BillboardInfo[idx][bbFontSize]);
            cache_get_value_name_int(idx, "fontbold", BillboardInfo[idx][bbFontBold]);
            cache_get_value_name_int(idx, "fontcolor", BillboardInfo[idx][bbFontColor]);
            cache_get_value_name_int(idx, "backcolor", BillboardInfo[idx][bbBackColor]);
            cache_get_value_name_int(idx, "textaligment", BillboardInfo[idx][bbTextAligment]);

            BillboardInfo[idx][bbObject][0] = CreateDynamicObject(1309, BillboardPos[idx][0], BillboardPos[idx][1], BillboardPos[idx][2], BillboardPos[idx][3], BillboardPos[idx][4], BillboardPos[idx][5], -1, -1, -1, 300.00, 300.00);

            BillboardInfo[idx][bbObject][1] = CreateDynamicObject(8331, BillboardPos[idx][6], BillboardPos[idx][7], BillboardPos[idx][8], BillboardPos[idx][9], BillboardPos[idx][10], BillboardPos[idx][11], -1, -1, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(BillboardInfo[idx][bbObject][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", BillboardColorInfo[BillboardInfo[idx][bbBackColor]][bbcColorRBG]);

            for(new i = strlen(BillboardInfo[idx][bbText]); i > -1; i--)
            {
                if(BillboardInfo[idx][bbText][i] == '/') BillboardInfo[idx][bbText][i] = '\n';
                if(BillboardInfo[idx][bbText][i] == '(') BillboardInfo[idx][bbText][i] = '{';
                if(BillboardInfo[idx][bbText][i] == ')') BillboardInfo[idx][bbText][i] = '}';
            }

            SetDynamicObjectMaterialText(BillboardInfo[idx][bbObject][1], 0, BillboardInfo[idx][bbText], BillboardInfo[idx][bbMaterialSize], BillboardFontFaceName[BillboardInfo[idx][bbFontFace]], BillboardInfo[idx][bbFontSize], BillboardInfo[idx][bbFontBold], BillboardColorInfo[BillboardInfo[idx][bbFontColor]][bbcColorRBG], BillboardColorInfo[BillboardInfo[idx][bbBackColor]][bbcColorRBG], BillboardInfo[idx][bbTextAligment]);
        }
    }
    printf("Данные билбордов загружены за %d мс", GetTickCount()-time);
    return 1;
}

enum
{
    BB_LIST = 1,
    BB_LIST_RENT,
    BB_LIST_SETTINGS,
    BB_LIST_TEXT,
    BB_LIST_MATERIAL_SIZE,
    BB_LIST_FONT_FACE,
    BB_LIST_FONT_SIZE,
    BB_LIST_FONT_COLOR,
    BB_LIST_BACK_COLOR,
    BB_LIST_TEXT_ALIGMENT,
    BB_LIST_RENT_DAYS,
    BB_LIST_CANCEL_RENT,
    BB_LIST_HELP,
    BB_LIST_DEMO
}

ShowDialogBillboard(playerid, idx, dialog_id, first_parameter = 0)
{
    switch(dialog_id)
    {
        case BB_LIST:
        {
            new str[128];
            STRING_GLOBAL = "[#] Местоположение\tСтатус\n";
            for(new i = 0; i < MAX_BILLBOARD; i++)
            {
                if(BillboardInfo[i][bbDays]) format(str, sizeof(str), "{"#cLIGHTRED"}Арендован на %d дн."W"", BillboardInfo[i][bbDays]);
                else str = "{"#cGREEN"}Свободен"W"";
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%s\n", STRING_GLOBAL, i + 1, BillboardInfo[i][bbName], str);
            }
            ShowPlayerDialog(playerid, D_BILLBOARD, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список билбордов", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_RENT:
        {
            SetPlayerBillboardCamera(playerid, first_parameter);
            new till = b_info[idx][_till];
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Вы действительно хотите арендовать данный билборд?\n\n\
            Укажите количество дней {"#cBLUE"}(максимум 7):"W"\n\n\
            Стоимость 1 дня аренды: {"#cGREEN"}%d$:", BILLBOARD_PRICE_RENT * till);
            ShowPlayerDialog(playerid, D_BILLBOARD_RENT, DIALOG_STYLE_INPUT, ""I"Аренда билборда", STRING_GLOBAL, "Да", "Нет");
            SetPVarInt(playerid, "BILLBOARD:idx", first_parameter);
        }
        case BB_LIST_SETTINGS:
        {
            SetPlayerBillboardCamera(playerid, first_parameter);
            STRING_GLOBAL = "[#] Параметр\tЗначение\n";
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
            %s"I"[1]"W" Текст объявления:\t{"#cGREEN"}Изменить..."W"\n\
            "I"[2]"W" Размер шрифта:\t%d\n\
            "I"[3]"W" Шрифт:\t%s\n\
            "I"[4]"W" Размер текста:\t%d\n\
            "I"[5]"W" Жирный шрифт:\t%s\n\
            "I"[6]"W" Цвет текста:\t%s\n\
            "I"[7]"W" Цвет фона:\t%s\n\
            "I"[8]"W" Выравнивание:\t%s\n\
            "I"[9]"W" Срок аренды:\t{"#cGREEN"}%d дн."W"\n\
            "I"[10]"W" Аренда {"#cBLUE"}активна:\t{"#cLIGHTRED"}Разорвать договор...\n\
            "I"[11]"W" Помощь по размещению рекламы:\t{"#cYELLOW"}Подробнее...\n\
            "I"[12]"W" Предпросмотр:\t{"#cBLUE"}Демонстрация...",
            STRING_GLOBAL,
            BillboardInfo[first_parameter][bbMaterialSize],
            BillboardFontFaceName[BillboardInfo[first_parameter][bbFontFace]],
            BillboardInfo[first_parameter][bbFontSize],
            BillboardInfo[first_parameter][bbFontBold] == 0 ? "Выключен" : "Включен",
            BillboardColorInfo[BillboardInfo[first_parameter][bbFontColor]][bbcName],
            BillboardColorInfo[BillboardInfo[first_parameter][bbBackColor]][bbcName],
            BillboardAligmentName[BillboardInfo[first_parameter][bbTextAligment]],
            BillboardInfo[first_parameter][bbDays]);
            ShowPlayerDialog(playerid, D_BILLBOARD_SETTINGS, DIALOG_STYLE_TABLIST_HEADERS, ""I"Настройки билборда", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_TEXT:
        {
            ShowPlayerDialog(playerid, D_BILLBOARD_TEXT, DIALOG_STYLE_INPUT, ""I"Изменить текст объявления", ""W"\
            Введите текст объявления в поле ниже. Максимальная длина текста {"#cGREEN"}100 символов (включая специальные)."W"\n\
            Настоятельно рекомендуем прочитать {"#cBLUE"}помощь по размещению рекламы,"W" которая находится в прошлом диалоге.", "Далее", "Отмена");
        }
        case BB_LIST_MATERIAL_SIZE:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < sizeof(BillboardMaterialSizeName); i++)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i + 1, BillboardMaterialSizeName[i]);
            }
            ShowPlayerDialog(playerid, D_BILLBOARD_MATERIAL_SIZE, DIALOG_STYLE_LIST, ""I"Размер шрифта", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_FONT_FACE:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < sizeof(BillboardFontFaceName); i++)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i + 1, BillboardFontFaceName[i]);
            }
            ShowPlayerDialog(playerid, D_BILLBOARD_FONT_FACE, DIALOG_STYLE_LIST, ""I"Шрифт", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_FONT_SIZE:
        {
            ShowPlayerDialog(playerid, D_BILLBOARD_FONT_SIZE, DIALOG_STYLE_INPUT, ""I"Размер текста", ""W"Укажите размер текста (от 1 до 255):", "Далее", "Отмена");
        }
        case BB_LIST_FONT_COLOR:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < sizeof(BillboardColorInfo); i++)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s{%06x} %s\n", STRING_GLOBAL, BillboardColorInfo[i][bbcColorRBG] & 0xFFFFFF, BillboardColorInfo[i][bbcName]);
            }
            ShowPlayerDialog(playerid, D_BILLBOARD_FONT_COLOR, DIALOG_STYLE_LIST, ""I"Цвет текста", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_BACK_COLOR:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < sizeof(BillboardColorInfo); i++)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s{%06x} %s\n", STRING_GLOBAL, BillboardColorInfo[i][bbcColorRBG] & 0xFFFFFF, BillboardColorInfo[i][bbcName]);
            }
            ShowPlayerDialog(playerid, D_BILLBOARD_BACK_COLOR, DIALOG_STYLE_LIST, ""I"Цвет фона", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_TEXT_ALIGMENT:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < sizeof(BillboardAligmentName); i++)
            {
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i + 1, BillboardAligmentName[i]);
            }
            ShowPlayerDialog(playerid, D_BILLBOARD_TEXT_ALIGMENT, DIALOG_STYLE_LIST, ""I"Выравнивание", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BB_LIST_RENT_DAYS:
        {
            new till = b_info[idx][_till];
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            На сколько Вы хотите продлить аренду Вашего билборда?\n\n\
            Договор аренды можно заключить {"#cLIGHTRED"}максимум"W" на 7 дней.\n\n\
            Стоимость 1 дня аренды: {"#cGREEN"}%d$", BILLBOARD_PRICE_RENT * till);
            ShowPlayerDialog(playerid, D_BILLBOARD_RENT_DAYS, DIALOG_STYLE_INPUT, ""I"Продление аренды", STRING_GLOBAL, "Да", "Нет");
        }
        case BB_LIST_CANCEL_RENT:
        {
            ShowPlayerDialog(playerid, D_BILLBOARD_CANCEL_RENT, DIALOG_STYLE_MSGBOX, ""I"Разорвать договор аренды", ""W"\
            Вы действительно хотите {"#cLIGHTRED"}разорвать"W" договор аренды билборда?\n\n\
            Рекламное агентство не компенсирует расходы за уже оплаченные дни.", "Да", "Нет");
        }
        case BB_LIST_HELP:
        {
            ShowPlayerDialog(playerid, D_BILLBOARD_HELP, DIALOG_STYLE_MSGBOX, ""I"Помощь по размещению рекламы", ""W"\
            Всего имеется 24 билборда доступных для аренды. Арендатор может {"#cLIGHTRED"}настраивать"W" рекламное объявления\n\
            с помощью разных настроек.\n\n\
            Текст объявления может содержать {"#cGREEN"}специальные символы:"W"\n\n\
            \t/ - перенос строки\n\
            \t(......) - цветовой RGB код. Вставьте его перед текстом, чтобы изменить цвет нужного фрагмента\n\n\
            Более подробную информацию Вы можете узнать в Интернете с помощью запроса {"#cYELLOW"}\"Цвета RGB\".", "Закрыть", "");
        }
        case BB_LIST_DEMO:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Предпросмотр", ""W"\
            Вы начали {"#cBLUE"}предпросмотр"W" билборда.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Вас автоматически вернет в настройки билборда через 15 сек.", "ОК", "");
            p_temp[playerid][billboard_status] = true;
            p_temp[playerid][billboard_timer] = 15;
        }
    }
    return 1;
}

SetBillboardText(idx)
{
    if(idx < 0 || idx > MAX_BILLBOARD - 1) return 1;

    SetDynamicObjectMaterial(BillboardInfo[idx][bbObject][1], 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", BillboardColorInfo[BillboardInfo[idx][bbBackColor]][bbcColorRBG]);

    for(new i = strlen(BillboardInfo[idx][bbText]); i > -1; i--)
    {
        if(BillboardInfo[idx][bbText][i] == '/') BillboardInfo[idx][bbText][i] = '\n';
        if(BillboardInfo[idx][bbText][i] == '(') BillboardInfo[idx][bbText][i] = '{';
        if(BillboardInfo[idx][bbText][i] == ')') BillboardInfo[idx][bbText][i] = '}';
    }

    SetDynamicObjectMaterialText(BillboardInfo[idx][bbObject][1], 0, BillboardInfo[idx][bbText], BillboardInfo[idx][bbMaterialSize], BillboardFontFaceName[BillboardInfo[idx][bbFontFace]], BillboardInfo[idx][bbFontSize], BillboardInfo[idx][bbFontBold], BillboardColorInfo[BillboardInfo[idx][bbFontColor]][bbcColorRBG], BillboardColorInfo[BillboardInfo[idx][bbBackColor]][bbcColorRBG], BillboardInfo[idx][bbTextAligment]);
    return 1;
}

ClearBillboardText(idx)
{
    BillboardInfo[idx][bbPlayerID] = 0;
    BillboardInfo[idx][bbDays] = 0;
    format(BillboardInfo[idx][bbText], 128, "(008000)Рекламное место свободно///(FFA500)Обращайтесь в рекламное/агентство");
    BillboardInfo[idx][bbMaterialSize] = 130;
    BillboardInfo[idx][bbFontFace] = 20;
    BillboardInfo[idx][bbFontSize] = 42;
    BillboardInfo[idx][bbFontBold] = 1;
    BillboardInfo[idx][bbFontColor] = 0;
    BillboardInfo[idx][bbBackColor] = 0;
    BillboardInfo[idx][bbTextAligment] = 1;

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `billboard` SET `playerid` = 0, `days` = 0, `text` = '%s', `materialsize` = 130, `fontface` = 20, `fontsize` = 42, `fontbold` = 1, `fontcolor` = 0, `backcolor` = 0, `textaligment` = 1 WHERE `id` = %d",
    BillboardInfo[idx][bbText], BillboardInfo[idx][bbMySQLID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    SetBillboardText(idx);
    return 1;
}

CheckBillboard()
{
    for(new i = 0; i < MAX_BILLBOARD; i++)
    {
        if(BillboardInfo[i][bbPlayerID] != 0)
        {
            BillboardInfo[i][bbDays]--;
            MysqlUpdateBillboardInt(i, "days", BillboardInfo[i][bbDays]);
            if(BillboardInfo[i][bbDays] == 0) ClearBillboardText(i);
        }
    }
    return 1;
}

SetPlayerBillboardCamera(playerid, idx)
{
    SetPlayerPos(playerid, BillboardPos[idx][0], BillboardPos[idx][1], BillboardPos[idx][2] - 10.0);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, playerid);

    Fix_TogglePlayerControllable(playerid, 0);

    new Float:xr, Float:yr;

    xr = BillboardPos[idx][0] - 25.0 * floatsin(BillboardPos[idx][5] - 90.0, degrees);
    yr = BillboardPos[idx][1] + 25.0 * floatcos(BillboardPos[idx][5] - 90.0, degrees);

    SetPlayerCameraPos(playerid, xr, yr, BillboardPos[idx][2] + 7.5);
    SetPlayerCameraLookAt(playerid, BillboardPos[idx][0], BillboardPos[idx][1], BillboardPos[idx][2] + 7.6);
    return 1;
}

MysqlUpdateBillboardInt(idx, field[], data[])
{
    new string[256];
    mysql_format(con_bd, string, sizeof(string), "UPDATE `billboard` SET `%s` = %d WHERE `id` = %d",
    field, data, BillboardInfo[idx][bbMySQLID]);
    mysql_tquery(con_bd, string, "", "");
    return 1;
}

MysqlUpdateBillboardStr(idx, field[], data[])
{
    new string[256];
    mysql_format(con_bd, string, sizeof(string), "UPDATE `billboard` SET `%s` = '%s' WHERE `id` = %d",
    field, data, BillboardInfo[idx][bbMySQLID]);
    mysql_tquery(con_bd, string, "", "");
    return 1;
}

CMD:dbillboard(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    for(new i = 0; i < MAX_BILLBOARD; i++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 25.0, BillboardPos[i][0], BillboardPos[i][1], BillboardPos[i][2]))
        {
            ClearBillboardText(i);
            SendAccess(playerid, "Вы отменили аренду билборда \"%s\".", BillboardInfo[i][bbName]);
            Log(LOG_player, INFO, "%s[%d](%s %s) отменил аренду билборда \"%s\" | #AdminLogs",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", BillboardInfo[i][bbName]);
            return 1;
        }
    }
    SendError(playerid, "Рядом с Вами нет билборда.");
    return 1;
}
