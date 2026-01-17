#define MAX_PROMOCODE_LEVEL             10

enum E_PROMOCODE_SETTINGS
{
    pPriz,
    Float:pPercent,
    pPrice,
    pActivation
};
new PromocodeSettings[MAX_PROMOCODE_LEVEL][E_PROMOCODE_SETTINGS] = {
    {100000, 2.0, 1000, 0},
    {125000, 2.0, 1000, 50},
    {150000, 3.0, 1000, 75},
    {175000, 3.0, 1000, 100},
    {200000, 4.0, 1000, 125},
    {225000, 4.0, 1000, 150},
    {250000, 5.0, 1000, 175},
    {275000, 5.0, 1000, 200},
    {300000, 6.0, 1000, 225},
    {325000, 6.0, 1000, 250}
};

new PromocodeName[MAX_PLAYERS][32];

enum
{
    TYPE_PROMOCODE_LEVEL,
    TYPE_PROMOCODE_ACTIVATION,
    TYPE_PROMOCODE_DONATE,
    TYPE_PROMOCODE_PRICE
}

new PromocodeInfo[MAX_PLAYERS][4];

enum
{
    PROMOCODE_MENU,
    PROMOCODE_ACTIVATION,
    PROMOCODE_CREATE,
    PROMOCODE_CONTROL,
    PROMOCODE_EDIT,
    PROMOCODE_LEVEL,
    PROMOCODE_UPDATE,
    PROMOCODE_BALANCE,
    PROMOCODE_GIVEDONATE,
    PROMOCODE_RATING
}

ShowDialogPromocode(playerid, dialog_id, first_parameter = 0)
{
    switch(dialog_id)
    {
        case PROMOCODE_MENU: ShowPlayerDialog(playerid, D_PROMOCODE_MENU, DIALOG_STYLE_LIST, ""I"Промокод", ""I"[1]"W" Активировать промокод\n"I"[2]"W" Управление промокодом\n"I"[3]"W" Рейтинг промокодов", "Далее", "Отмена");
        case PROMOCODE_ACTIVATION:
        {
            if(p_info[playerid][promocode_use]) return ShowDialogPromocode(playerid, PROMOCODE_MENU), SendError(playerid, "У Вас уже активирован промокод.");
            ShowPlayerDialog(playerid, D_PROMOCODE_ACTIVATION, DIALOG_STYLE_INPUT, ""I"Промокод", ""W"На нашем проекте действует система промокодов от других игроков.\nЗнаешь один из них? Введи его в строку ниже, чтобы получить бонус.", "Далее", "Отмена");
        }
        case PROMOCODE_CONTROL:
        {
            if(p_info[playerid][promocode_create])
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `promocode` WHERE `id` = %d",
                p_info[playerid][promocode_create]);
                mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerSelectPromocode", "dd", playerid, 2);
            }
            else
            {
                ShowPlayerDialog(playerid, D_PROMOCODE_CREATE, DIALOG_STYLE_INPUT, ""I"Создать промокод", ""W"\
                На нашем проекте действует система "I"промокодов."W" Любой игрок может "I"создать"W"\n\
                персональный код, который будет "I"приносить прибыль"W" тебе и человеку, который\n\
                активирует его.\n\n\
                Всего существует "I"10"W" уровней промокода. Создать его можно за "I"Flin Money."W"\n\n\
                При достижении определенного количества активаций уровень можно повысить,\n\
                а с ним "I"повысятся"W" и "I"награды"W" за ввод кода.\n\n\
                Стоимость создания промокода зависит от количества символов в нём.\n\n\
                Требования к коду: "I"только латиница, цифры и #, максимальное значение - до 14 символов."W"\n\n\
                Промокод с 1 символом - "I"2500 Flin Money"W"\n\
                Промокод от 2 до 3 символов - "I"2000 Flin Money"W"\n\
                Промокод от 4 до 5 символов- "I"1500 Flin Money"W"\n\
                Промокод от 6 до 7 символов - "I"1000 Flin Money"W"\n\
                Промокод от 8 до 14 символов - "I"500 Flin Money", "Далее", "Отмена");
            }
        }
        case PROMOCODE_CREATE:
        {
            ShowPlayerDialog(playerid, D_PROMOCODE_CREATE, DIALOG_STYLE_INPUT, ""I"Создать промокод", ""W"\
            На нашем проекте действует система "I"промокодов."W" Любой игрок может "I"создать"W"\n\
            персональный код, который будет "I"приносить прибыль"W" тебе и человеку, который\n\
            активирует его.\n\n\
            Всего существует "I"10"W" уровней промокода. Создать его можно за "I"Flin Money."W"\n\n\
            При достижении определенного количества активаций уровень можно повысить,\n\
            а с ним "I"повысятся"W" и "I"награды"W" за ввод кода.\n\n\
            Стоимость создания промокода зависит от количества символов в нём.\n\n\
            Требования к коду: "I"только латиница, цифры и #, максимальное значение - до 14 символов."W"\n\n\
            Промокод с 1 символом - "I"2500 Flin Money"W"\n\
            Промокод от 2 до 3 символов - "I"2000 Flin Money"W"\n\
            Промокод от 4 до 5 символов- "I"1500 Flin Money"W"\n\
            Промокод от 6 до 7 символов - "I"1000 Flin Money"W"\n\
            Промокод от 8 до 14 символов - "I"500 Flin Money", "Далее", "Отмена");
        }
        case PROMOCODE_EDIT:
        {
            ShowPlayerDialog(playerid, D_PROMOCODE_EDIT, DIALOG_STYLE_INPUT, ""I"Изменить название промокода", ""W"\
            Не нравится название твоего промокода? Его всегда можно изменить! Придумай новый код и введи\n\
            его в строку ниже. Однако учти, что это будет стоить определённого количества "I"Flin Money."W"\n\n\
            Стоимость изменения промокода зависит от количества символов в нём.\n\n\
            Требования к коду: "I"только латиница, цифры и #, максимальное значение - до 14 символов."W"\n\n\
            Промокод с 1 символом - "I"2500 Flin Money"W"\n\
            Промокод от 2 до 3 символов - "I"2000 Flin Money"W"\n\
            Промокод от 4 до 5 символов- "I"1500 Flin Money"W"\n\
            Промокод от 6 до 7 символов - "I"1000 Flin Money"W"\n\
            Промокод от 8 до 14 символов - "I"500 Flin Money", "Далее", "Отмена");
        }
        case PROMOCODE_LEVEL:
        {
            STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""I"1 уровень\tНаграда: $%d, %.2f%% от доната.\n\n", PromocodeSettings[0][pPriz], PromocodeSettings[0][pPercent]);
            for(new i = 1; i < MAX_PROMOCODE_LEVEL; i++)
            {
                format(STRING_MIN, sizeof(STRING_MIN), "%s\
                %d уровень\tНаграда: $%d, %.2f%% от доната\tКоличество активаций: %d\n\
                \t\tСтоимость: %d Flin Money\n\n", PromocodeInfo[playerid][TYPE_PROMOCODE_LEVEL] >= i + 1 ? ""I"" : "{"#cGRAY"}", i + 1, PromocodeSettings[i][pPriz], PromocodeSettings[i][pPercent], PromocodeSettings[i][pActivation], PromocodeSettings[i][pPrice]);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"Промокод: "W"%s "I"Количество активаций: "W"%d", PromocodeName[playerid], PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION]);
            ShowPlayerDialog(playerid, D_PROMOCODE_LEVEL, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Повысить", "Отмена");
        }
        case PROMOCODE_UPDATE:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Ты повысил свой промокод до "I"%d"W" уровня за "I"%d"W" Flin Money. Продолжай развивать свой промокод!", PromocodeInfo[playerid][TYPE_PROMOCODE_LEVEL], first_parameter);
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"Промокод: "W"%s "I"Количество активаций: "W"%d", PromocodeName[playerid], PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION]);
            ShowPlayerDialog(playerid, D_PROMOCODE_BACK_CONTROL, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Закрыть", "");
        }
        case PROMOCODE_BALANCE:
        {
            if(!PromocodeInfo[playerid][TYPE_PROMOCODE_DONATE]) return ShowDialogPromocode(playerid, PROMOCODE_CONTROL), SendError(playerid, "На балансе Вашего промокода нет Flin Money.");
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            С доната игроков, активировавших твой промокод, тебе "I"отчисляется"W" определенный процент.\n\
            На данный момент для вывода тебе доступно "I"%d"W" Flin Money."W"\n\n\
            Хочешь зачислить их на свой аккаунт?", PromocodeInfo[playerid][TYPE_PROMOCODE_DONATE]);
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"Промокод: "W"%s "I"Количество активаций: "W"%d", PromocodeName[playerid], PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION]);
            ShowPlayerDialog(playerid, D_PROMOCODE_BALANCE, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Да", "Нет");
        }
        case PROMOCODE_GIVEDONATE:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Ты получил "I"%d"W" Flin Money в виде процентов с доната игроков, активировавших твой промокод!", first_parameter);
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"Промокод: "W"%s "I"Количество активаций: "W"%d", PromocodeName[playerid], PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION]);
            ShowPlayerDialog(playerid, D_PROMOCODE_BACK_CONTROL, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Закрыть", "");
        }
        case PROMOCODE_RATING: mysql_tquery(con_bd, "SELECT * FROM `promocode` ORDER BY `activation` DESC LIMIT 25", "OnPlayerSelectPromocode", "dd", playerid, 4);
    }
    return 1;
}

forward OnPlayerSelectPromocode(playerid, type, count, params[], first_parameter, scdparams[], second_parameter);
public OnPlayerSelectPromocode(playerid, type, count, params[], first_parameter, scdparams[], second_parameter)
{
    switch(type)
    {
        case 1:
        {
            if(cache_num_rows())
            {
                ShowDialogPromocode(playerid, PROMOCODE_CREATE);
                return SendError(playerid, "Промокод с таким названием уже существует.");
            }
            if(p_info[playerid][flinmoney] < count) return SendError(playerid, "У Вас нет столько Flin Money.");
            format(PromocodeName[playerid], 32, "%s", params);
            PromocodeInfo[playerid][TYPE_PROMOCODE_PRICE] = count;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `promocode` (`name`, `ownerid`, `owner`) VALUES ('%e', %d, '%e')",
            params, p_info[playerid][ID], get_name(playerid));
            mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerCreatePromocode", "d", playerid);
        }
        case 2:
        {
            if(!cache_num_rows()) return ShowDialogPromocode(playerid, PROMOCODE_MENU), SendError(playerid, "Промокод не найден, возможно он был удален.");
            cache_get_value_name(0, "name", PromocodeName[playerid], 32);
            cache_get_value_name_int(0, "level", PromocodeInfo[playerid][TYPE_PROMOCODE_LEVEL]);
            cache_get_value_name_int(0, "activation", PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION]);
            cache_get_value_name_int(0, "donate", PromocodeInfo[playerid][TYPE_PROMOCODE_DONATE]);
            STRING_GLOBAL = "[#] Наименование\tПараметр\n";
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"W"\
            "I"[1]"W" Название промокода: "I"%s\t{"#cYELLOW"}Изменить название...\n\
            "I"[2]"W" Уровень промокода: "I"%d\t{"#cGREEN"}Повысить уровень...\n\
            "I"[3]"W" Количество активаций: "I"%d\t{"#cBLUE"}Список игроков...\n\
            "I"[4]"W" Баланс Flin Money: "I"%d\t{"#cLIGHTRED"}Забрать Flin Money...", STRING_GLOBAL, PromocodeName[playerid], PromocodeInfo[playerid][TYPE_PROMOCODE_LEVEL], PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION], PromocodeInfo[playerid][TYPE_PROMOCODE_DONATE]);
            STRING_MIN[0] = EOS;
            format(STRING_MIN, sizeof(STRING_MIN), ""I"Промокод: "W"%s "I"Количество активаций: "W"%d", PromocodeName[playerid], PromocodeInfo[playerid][TYPE_PROMOCODE_ACTIVATION]);
            ShowPlayerDialog(playerid, D_PROMOCODE_CONTROL, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
        }
        case 3:
        {
            new temp_idx = p_info[playerid][promocode_use];
            if(!cache_num_rows())
            {
                if(temp_idx == 0) ShowDialogPromocode(playerid, PROMOCODE_ACTIVATION);
                return SendError(playerid, "Промокод не найден, возможно он был удален.");
            }
            new temp_mysql_id, temp_level, temp_name[32];
            cache_get_value_name_int(0, "id", temp_mysql_id);
            cache_get_value_name_int(0, "level", temp_level);
            cache_get_value_name(0, "name", temp_name, 32);
            new temp_priz = PromocodeSettings[temp_level - 1][pPriz];
            if(temp_idx == 0)
            {
                p_info[playerid][promocode_use] = temp_mysql_id;
                MysqlUpdatePlayerInt(playerid, "promocode_use", p_info[playerid][promocode_use]);
                new time[32], year, month, day;
                getdate(year, month, day);
                format(time, sizeof(time), "%02d/%02d/%d %02d:%02d:%02d", day, month, year, timestamp_hour, timestamp_minute, timestamp_second);
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `promocode_use` = %d, `promocode_time` = '%e' WHERE `id` = %d",
                p_info[playerid][promocode_use], time, p_info[playerid][ID]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
            if(p_info[playerid][level] >= 5)
            {
                if(p_info[playerid][promocode_prize]) return ShowDialogPromocode(playerid, PROMOCODE_MENU), SendError(playerid, "Вам уже выдана награда за промокод.");
                p_info[playerid][promocode_prize] = 1;
                MysqlUpdatePlayerInt(playerid, "promocode_prize", p_info[playerid][promocode_prize]);
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `promocode` SET `activation` = `activation` + 1 WHERE `id` = %d",
                temp_mysql_id);
                mysql_tquery(con_bd, STRING_GLOBAL);
                SetPlayerMoney(playerid, temp_priz, true, "активация промокода <%s>", temp_name);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы активировали промокод "I"%s"W" и достигли 5-ого уровня.\n\nВаша награда: "I"$%d"W"\n\nПриятной игры, спасибо что выбрали нас!", params, temp_priz);
                ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Активация промокода", STRING_GLOBAL, "Закрыть", "");
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы успешно активировали промокод "I"%s"W"\n\nВаша награда по достижению 5-ого уровня: "I"$%d"W"\n\nПриятной игры, спасибо что выбрали нас!", temp_name, temp_priz);
                ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Активация промокода", STRING_GLOBAL, "Закрыть", "");
            }
        }
        case 4:
        {
            if(!cache_num_rows()) return ShowDialogPromocode(playerid, PROMOCODE_MENU), SendError(playerid, "Промокоды не найдены.");
            new temp_username[MAX_PLAYER_NAME], temp_promocode[16], temp_level, temp_activation;
            STRING_GLOBAL = "[#] Промокод\tУровень\tАктиваций\tСоздатель\n", STRING_MIN[0] = EOS;
            for(new i; i < 25; i++)
            {
                if(i >= cache_num_rows()) break;
                cache_get_value_name(i, "owner", temp_username, MAX_PLAYER_NAME);
                cache_get_value_name(i, "name", temp_promocode, 16);
                cache_get_value_name_int(i, "level", temp_level);
                cache_get_value_name_int(i, "activation", temp_activation);
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d из %d\t%d шт.\t%s\n", i+1, temp_promocode, temp_level, MAX_PROMOCODE_LEVEL, temp_activation, temp_username);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_PROMOCODE_BACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"Рейтинг промокодов", STRING_GLOBAL, "Далее", "Отмена");
        }
        case 5:
        {
            if(cache_num_rows()) return ShowDialogPromocode(playerid, PROMOCODE_EDIT), SendError(playerid, "Промокод с таким названием уже существует.");
            if(p_info[playerid][flinmoney] < count) return SendError(playerid, "У Вас нет столько Flin Money.");
            format(PromocodeName[playerid], 32, "%s", params);
            PromocodeInfo[playerid][TYPE_PROMOCODE_PRICE] = count;
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `promocode` SET `name` = '%e' WHERE `id` = %d",
            params, p_info[playerid][promocode_create]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы изменили промокод на "I"%s"W"\n\nРазвивайте его, чтобы получать еще больше бонусов от его активаций!", params);
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Создание промокода", STRING_GLOBAL, "ОК", "");
        }
        case 6:
        {
            if(!cache_num_rows()) return 1;
            new temp_mysql_id, temp_level;
            cache_get_value_name_int(0, "id", temp_mysql_id);
            cache_get_value_name_int(0, "level", temp_level);
            new Float:temp_percent = PromocodeSettings[temp_level - 1][pPercent], temp_donate = floatround(count / 100 * temp_percent);
            p_info[playerid][promocode_donate] += temp_donate;
            MysqlUpdatePlayerInt(playerid, "promocode_donate", p_info[playerid][promocode_donate]);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `promocode` SET `donate` = `donate` + %d WHERE `id` = %d",
            temp_donate, temp_mysql_id);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

forward OnPlayerCreatePromocode(playerid);
public OnPlayerCreatePromocode(playerid)
{
    new price = PromocodeInfo[playerid][TYPE_PROMOCODE_PRICE];
    if(p_info[playerid][flinmoney] < price) return SendError(playerid, "У Вас нет столько Flin Money.");
    PromocodeInfo[playerid][TYPE_PROMOCODE_PRICE] = 0;
    p_info[playerid][flinmoney] -= price;
    p_info[playerid][promocode_create] = cache_insert_id();
    new time[32], year, month, day;
    getdate(year, month, day);
    format(time, sizeof(time), "%02d/%02d/%d %02d:%02d:%02d", day, month, year, timestamp_hour, timestamp_minute, timestamp_second);
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `flinmoney` = %d, `promocode_create` = %d, `promocode_time` = '%e' WHERE `id` = %d",
    p_info[playerid][flinmoney], p_info[playerid][promocode_create], time, p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы создали промокод "I"%s"W"\n\nРазвивайте его, чтобы получать еще больше бонусов от его активаций!", PromocodeName[playerid]);
    ShowPlayerDialog(playerid, D_PROMOCODE_BACK_CONTROL, DIALOG_STYLE_MSGBOX, ""I"Создание промокода", STRING_GLOBAL, "ОК", "");

    Log(LOG_player, INFO, "%s[%d](%s %s) создал(-а) промокод %s за %d Flin Money | #Promocode",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
        PromocodeName[playerid], price);
    return 1;
}

CMD:promocode(playerid, params[])
{
    ShowDialogPromocode(playerid, PROMOCODE_MENU);
    return 1;
}
