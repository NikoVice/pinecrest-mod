mdc_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        ////////////////////////////
        case D_MDC_LICENSES_CONFIRM:
        {
            if(!response) return SelectTextDraw(playerid, 255);
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `name`, `Lic`, `Lic_Warn` FROM `accounts` WHERE `id` = %i LIMIT 1", GetPVarInt(playerid, #MDC_ID));
            mysql_tquery(con_bd, STRING_GLOBAL, "MDC_LICENSES_INFO", "i", playerid);
            return 1;
        }
        case D_MDC_LICENSES_MENU:
        {
            if(!response) return SelectTextDraw(playerid, 255);
            new lic_id = p_temp[playerid][p_listitem_int];
            p_temp[playerid][p_listitem][0] = listitem;
            STRING_GLOBAL[0] = EOS;
            switch(listitem)
            {
                case 0: f(STRING_GLOBAL, ""W"Вы действительно хотите "I"изъять "W"лицензию "W"на "I"%s?", name_license[lic_id]);
                case 1: f(STRING_GLOBAL, ""W"Вы действительно хотите выдать "I"предупреждение "W"на лицензию "I"%s?", name_license[lic_id]);
                case 2: f(STRING_GLOBAL, ""W"Вы действительно хотите снять "I"предупреждение "W"на лицензию "I"%s?", name_license[lic_id]);
                case 3: f(STRING_GLOBAL, ""W"Вы действительно хотите занести в "I"черный список "W"на лицензию "I"%s?", name_license[lic_id]);
                case 4: f(STRING_GLOBAL, ""W"Вы действительно хотите убрать из "I"черного списка "W"на лицензию "I"%s?", name_license[lic_id]);
                default: return 1;
            }
            ShowPlayerDialog(playerid, D_MDC_LICENSES_CONFIRM, DIALOG_STYLE_MSGBOX, ""I"Подтверждение", STRING_GLOBAL, "Да", "Нет");
            return 1;
        }
        case D_MDC_LICENSES:
        {
            if(!response) return SelectTextDraw(playerid, 255);
            p_temp[playerid][p_listitem_int] = listitem;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""I"%s", name_license[listitem]);
            ShowPlayerDialog(playerid, D_MDC_LICENSES_MENU, DIALOG_STYLE_LIST, STRING_GLOBAL,
                ""I"[1]"W" Аннулировать\n"I"[2]"W" Выдать предупреждение\n"I"[3]"W" Снять предупреждение\n"I"[4]"W" Добавить в черный список\n"I"[5]"W" Убрать из черного списка", "Выбрать", "Назад" );
            return 1;
        }
        case D_MDC_RECORD_INFO:
        {
            SelectTextDraw(playerid, 255);
            return 1;
        }
        case D_MDC_SEARCH_PERSON:
        {
            if(!response) return 1;

            new fix_listitem;
            if(sscanf(inputtext, "u", fix_listitem)) return SendError(playerid, "Вы ничего не ввели."), ShowPlayerDialog(playerid, D_MDC_SEARCH_PERSON, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск по ID", ""W"ПОИСК ПО ID\n\nВведите ID:", "Ввод", "Отмена");
            if(fix_listitem == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден."), ShowPlayerDialog(playerid, D_MDC_SEARCH_PERSON, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск по ID", ""W"ПОИСК ПО ID\n\nВведите ID:", "Ввод", "Отмена");
            if(fix_listitem == playerid) return SendError(playerid, "Вы ввели свой ID."), ShowPlayerDialog(playerid, D_MDC_SEARCH_PERSON, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск по ID", ""W"ПОИСК ПО ID\n\nВведите ID:", "Ввод", "Отмена");

                //mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `id` = %i LIMIT 1", p_info[fix_listitem][ID]);
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT a.`name`, a.`id`, i.`item_id`, a.`Lic`, a.`active_house_id`, a.`phone_number`, a.`jail` \
                FROM `accounts` AS a \
                LEFT JOIN `inventory` AS i ON a.`id` = i.`owner_id` \
                WHERE a.`id` = %d AND i.status_use = 1 AND i.`item_id` < 311 LIMIT 1", p_info[fix_listitem][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL, "MDCSearchPersonInfo", "i", playerid);
            return 1;
        }

        case D_MDC_SEARCH_VEHICLE_TYPE:
        {
            if(!response)    return 1;

            switch(listitem)
            {
                case 0:
                {
                    ShowPlayerDialog(playerid, D_MDC_SEARCH_VEHICLE_PLAYER, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск автомобиля", ""W"ПОИСК ИНФОРМАЦИИ О ТС\n\nВведите имя:\n\nФорма ввода: Имя_Фамилия (( или ID игрока ))", "Ввод", "Назад");
                }
                case 1:
                {
                    ShowPlayerDialog(playerid, D_MDC_SEARCH_VEHICLE_NUMBER, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск автомобиля", ""W"ПОИСК ИНФОРМАЦИИ О ТС\n\nВведите номерной знак:\n\n(( Номер Т/С, можно ввести часть ))", "Ввод", "Назад");
                }
            }

            return 1;
        }

        case D_MDC_SEARCH_VEHICLE_PLAYER:
        {
            if(!response)
                return ShowPlayerDialog(playerid, D_MDC_SEARCH_VEHICLE_TYPE, DIALOG_STYLE_LIST, ""I"MDC  - Поиск транспортного средства", ""I"[1]"W" Поиск транспортного средства по владельцу\n"I"[2]"W" Поиск транспортного средства по номеру", "Выбрать", "Назад");

            new userid,
                query[256];

            if(sscanf(inputtext, "u", userid))
                return ShowPlayerDialog(playerid, D_MDC_SEARCH, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск автомобиля", ""W"ПОИСК ИНФОРМАЦИИ О ТС\n\nВведите имя:\n\nФорма ввода: Имя_Фамилия (( или ID игрока ))", "Ввод", "Назад");

            DeletePVar(playerid, #MAX_MDC_PAGE);
            MdcInfo[playerid][mdcListPage] = 0;

            if(userid == INVALID_PLAYER_ID || !p_info[userid][loggedIn])
            {
                mysql_format(con_bd, query, sizeof(query), "SELECT `id` FROM `accounts` WHERE `name` = '%e' LIMIT 1", inputtext);
                mysql_tquery(con_bd, query, "MDCSearchVehiclesList_GetID", "ii", playerid, 1);
                return 1;
            }

            mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` = %i AND `v_number` != 'NULL'", p_info[userid][ID]);
            mysql_tquery(con_bd, query, "MDCSearchVehiclesList", "ii", playerid, 1);
            return 1;
        }

        case D_MDC_SEARCH_VEHICLE_NUMBER:
        {
            if(!response)
                return ShowPlayerDialog(playerid, D_MDC_SEARCH_VEHICLE_TYPE, DIALOG_STYLE_LIST, ""I"MDC  - Поиск транспортного средства", ""I"[1]"W" Поиск транспортного средства по владельцу\n"I"[2]"W" Поиск транспортного средства по номеру", "Выбрать", "Назад");

            if(!strlen(inputtext) || strlen(inputtext) > 8 || strlen(inputtext) < 3 ||
                strfind(inputtext, "N", true) != -1 ||
                strfind(inputtext, "U", true) != -1 ||
                strfind(inputtext, "L", true) != -1)
            {
                PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

                for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
                for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

                for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
                for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
                for(new d = 0; d < 12; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

                MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
                return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
            }
            DeletePVar(playerid, #MAX_MDC_PAGE);
            MdcInfo[playerid][mdcListPage] = 0;

            SetPVarString(playerid, #MDC_SEARCH_VEHICLE_NUM, inputtext);
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], inputtext);

            new query[256];
            mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` != 0 AND `v_number` LIKE '%%%e%%'", inputtext);
            mysql_tquery(con_bd, query, "MDCSearchVehiclesList", "ii", playerid, 0);
            return 1;
        }
        case D_MDC_RECORD_ADD:
        {
            if(!response) return 1;
            new targetid = GetPlayerUserID(GetPVarInt(playerid, #MDC_ID));
            if(targetid == INVALID_PLAYER_ID) return 1;
            if(strlen(inputtext) < 1 || strlen(inputtext) > 64)
                return ShowPlayerDialog(playerid, D_MDC_RECORD_ADD, DIALOG_STYLE_INPUT, ""I"MDC - Предъявление обвинения", ""W"ПРЕДЪЯВЛЕНИЕ ОБВИНЕНИЙ\n\nВведите текст обвинения: (( Преступление / 64 символов))", "Ввод", "Отмена");

            AddCriminalRecord(targetid, inputtext, get_name(playerid), p_info[playerid][member]);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "[WANTED] Обвиняемый: %s, Обвинитель: %s Преступление: %s.", get_name(targetid), get_name(playerid), inputtext);
            SendFractionMessage(POLICE_LS, 0x33CC66FF, STRING_GLOBAL);
            SendFractionMessage(POLICE_SF, 0x33CC66FF, STRING_GLOBAL);
            SendFractionMessage(POLICE_LV, 0x33CC66FF, STRING_GLOBAL);
            SendFractionMessage(POLICE_RC, 0x33CC66FF, STRING_GLOBAL);
            SendFractionMessage(FBI_TEAM, 0x33CC66FF, STRING_GLOBAL);

            SendAccess(playerid, "Обвиняемый успешно добавлен в розыск.");
            return 1;
        }
        case D_MDC_ADD_NOTE:
        {
            if(!response) return 1;
            if(strlen(inputtext) < 1 || strlen(inputtext) > 127) return ShowPlayerDialog(playerid, D_MDC_ADD_NOTE, DIALOG_STYLE_INPUT, ""I"MDC  - Добавление записи о ТС", ""W"ДОБАВЛЕНИЕ ЗАПИСИ О ТС\n\nВведите текст заметки:", "Ввод", "Назад");

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `vehicle_note` (`vehicle_id`, `officer_id`, `text`, `date`) VALUES (%d, %d, '%s', NOW())", GetPVarInt(playerid, #MDC_ID), p_info[playerid][ID], inputtext);
            mysql_tquery(con_bd, STRING_GLOBAL);
            UpdatePlayerList(playerid);
            return 1;
        }
        case D_MDC_VEHICLE_NOTE:
        {
            if(!response)
            {
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `vehicle_note` WHERE `id` = %d", p_temp[playerid][p_listitem_int]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
            UpdatePlayerList(playerid);
            return 1;
        }

        case D_MDC_ROSTER_CHANGE:
        {
            if(!response) return 1;
            if(isnull(inputtext)) return ShowPlayerDialog(playerid, D_MDC_ROSTER_CHANGE, DIALOG_STYLE_INPUT, ""I"Изменить позывной", ""W"Введите новый позывной:", "Принять", "Отмена");
            if(CheckTextDrawString(inputtext)) return SendError(playerid, "Использовать кириллицу или спец. символы нельзя.");

            callcmd::callsign(playerid, inputtext);
            MDC_PAGE(playerid, PAGE_ROSTER);
            return 1;
        }
        case D_APB_MENU:
        {
            if(!response) return 1;
            switch(listitem) {
                case 0:
                {
                    p_temp[playerid][list_page] = 0;
                    APB_List(playerid); // list
                }
                case 1: { // add
                    new apb = -1;
                    for(new i = 0; i < MAX_APBS; i++)
                    {
                        if(ApbInfo[i][apbOn] != 0) continue;
                        apb = i;
                        break;
                    }
                    if(apb == -1) return SendError(playerid, "Нет места для новой APB заметки.");

                    SetPVarInt(playerid, #MDC_ID, apb);
                    ShowPlayerDialog(playerid, D_APB_CREATE_FIRST, DIALOG_STYLE_INPUT, ""I"Создание APB", ""W"Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Далее", "Отмена");
                }
                case 2: ShowPlayerDialog(playerid, D_APB_SEARCH_BY_NAME, DIALOG_STYLE_INPUT, ""I"APB - Поиск по имени", ""W"Введите имя или часть имени для поиска:", "Ввод", "Назад");
                case 3: ShowPlayerDialog(playerid, D_APB_SEARCH_BY_CHARGE, DIALOG_STYLE_INPUT, ""I"APB - Поиск по описанию", ""W"Введите слово или часть слова для поиска:", "Ввод", "Назад");
            }
            return 1;
        }

        case D_APB_LIST_ACTIONS:
        {
            if(!response) return APB_Menu(playerid);

            if(p_temp[playerid][list_page]) {        //if not first page
                if(listitem == 0) {
                    p_temp[playerid][list_page]--;
                    return APB_List(playerid);
                } else if(listitem == MAX_DIALOG_LIST+1) {
                    p_temp[playerid][list_page]++;
                    return APB_List(playerid);
                }
            } else {                                 //if it's a first page
                if(listitem == MAX_DIALOG_LIST) {
                    p_temp[playerid][list_page]++;
                    return APB_List(playerid);
                }
            }

            new temp_listitem = p_temp[playerid][list_page] > 0 ? 1 : 0;
            new mes[256], i_apb = p_temp[playerid][list_page]*MAX_DIALOG_LIST+(listitem)-temp_listitem;
            SetPVarInt(playerid, #MDC_ID, i_apb);

            format(mes, sizeof(mes), ""W"#%i\n\n"W"Подозреваемый:"I"\t %s\n"W"Описание:"I"\t\t %s\n\n"W"Добавил:"I"\t\t %s\n"W"Дата:"I"\t\t\t %s\n", ApbInfo[i_apb][apbID]+90214, ApbInfo[i_apb][apbSuspect], ApbInfo[i_apb][apbCharge], ApbInfo[i_apb][apbOfficer], ApbInfo[i_apb][apbDate]);
            ShowPlayerDialog(playerid, D_APB_DETAILS, DIALOG_STYLE_MSGBOX, ""I"Редактирование APB", mes, "Изменить", "Отмена");
            return 1;
        }
        case D_APB_CREATE_FIRST:
        {
            if(!response) return DeletePVar(playerid, #MDC_ID);
            if(strlen(inputtext) < 1 || strlen(inputtext) > 23) return ShowPlayerDialog(playerid, D_APB_CREATE_FIRST, DIALOG_STYLE_INPUT, ""I"Создание APB", ""W"Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Далее", "Отмена");
            new apb = GetPVarInt(playerid, #MDC_ID);

            format(ApbInfo[apb][apbOfficer], MAX_PLAYER_NAME, "%s", get_name(playerid));
            format(ApbInfo[apb][apbSuspect], MAX_PLAYER_NAME, "%s", inputtext);

            ApbInfo[apb][apbFaction] = p_info[playerid][member];
            format(ApbInfo[apb][apbDate], 32, "%s", GetFullDate());

            ShowPlayerDialog(playerid, D_APB_CREATE_SECOND, DIALOG_STYLE_INPUT, ""I"Создание APB", ""W"Введите описание подозреваемого:\n- Максимальное кол-во символов: 128", "Готово", "Назад");
            return 1;
        }

        case D_APB_CREATE_SECOND:
        {
            if(!response) return ShowPlayerDialog(playerid, D_APB_CREATE_FIRST, DIALOG_STYLE_INPUT, ""I"Создание APB", ""W"Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Далее", "Отмена");
            if(strlen(inputtext) < 1 || strlen(inputtext) > 127) return ShowPlayerDialog(playerid, D_APB_CREATE_SECOND, DIALOG_STYLE_INPUT, ""I"Создание APB", ""W"Введите описание подозреваемого:\n- Максимальное кол-во символов: 128", "Готово", "Назад");

            new apb = GetPVarInt(playerid, #MDC_ID);
            format(ApbInfo[apb][apbCharge], 128, "%s", inputtext);

            SendAccess(playerid, "Вы создали APB заметку [NUM: %i].", apb+1);

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "* HQ: %s %s добавил новую APB заметку, номер %i.", GetPlayerFractionRangName(playerid), get_name(playerid), apb+1);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `apbs` (faction, charge, suspect, officer, date) VALUES (%i, '%s', '%s', '%s', '%s')", ApbInfo[apb][apbFaction], ApbInfo[apb][apbCharge], ApbInfo[apb][apbSuspect], get_name(playerid), GetFullDate());
            mysql_tquery(con_bd, STRING_GLOBAL, "ApbCreate", "i", apb);

            DeletePVar(playerid, #MDC_ID);

            APB_Menu(playerid);
            /*
            MdcInfo[playerid][mdcPage] = PAGE_NONE;
            MDC_PAGE(playerid, PAGE_APB);
            */
            return 1;
        }

        case D_APB_SEARCH_BY_NAME:
        {
            if(!response)    return APB_Menu(playerid);

            new count,
                str[72+(32+30+4+3+2+25)*18] = "[#] Дата\tОфицер\tПодозреваемый\tОписание\n";

            for(new i = MAX_APBS-1; i >= 0; i--)
            {
                if(ApbInfo[i][apbOn] != 0 && strfind(ApbInfo[i][apbSuspect], inputtext, true) != -1)
                {
                    if(count < 18)
                    {
                        format(str, sizeof(str), "%s"I"[%d]"W" %s\t%s\t%s\t%.30s%s\n", str, i + 1, ApbInfo[i][apbDate], ApbInfo[i][apbOfficer], ApbInfo[i][apbSuspect], ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 30)?(".."):(""));
                        MdcInfo[count][mdcList] = i;
                    }
                    count++;
                }
            }

            if(!count) return ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_LIST, ""I"APB - Поиск по имени", ""W"Нет APB для отображения...", ">>>", "");

            ShowPlayerDialog(playerid, D_APB_SEARCH_NAME_ACTIONS, DIALOG_STYLE_TABLIST_HEADERS, ""I"APB - Поиск по имени", str, ">>>", "Назад");
            return 1;
        }

        case D_APB_SEARCH_NAME_ACTIONS:
        {
            if(!response) return APB_Menu(playerid);

            new mes[256], i_apb = MdcInfo[listitem][mdcList];
            SetPVarInt(playerid, #MDC_ID, i_apb);

            format(mes, sizeof(mes), ""I"#%i\n\n"I"Подозреваемый:"W"\t %s\n"I"Описание:"W"\t\t %s\n\n"I"Добавил:"W"\t\t %s\n"I"Дата:"W"\t\t\t %s\n", ApbInfo[i_apb][apbID]+90214, ApbInfo[i_apb][apbSuspect], ApbInfo[i_apb][apbCharge], ApbInfo[i_apb][apbOfficer], ApbInfo[i_apb][apbDate]);
            ShowPlayerDialog(playerid, D_APB_DETAILS, DIALOG_STYLE_MSGBOX, ""I"Редактирование APB", mes, "Изменить", "Отмена");
            return 1;
        }

        case D_APB_SEARCH_BY_CHARGE:
        {
            if(!response)    return APB_Menu(playerid);

            new count,
                str[72+(32+30+4+3+2+25)*18] = "[#] Дата\tОфицер\tПодозреваемый\tОписание\n";

            for(new i = MAX_APBS-1; i >= 0; i--)
            {
                if(ApbInfo[i][apbOn] != 0 && strfind(ApbInfo[i][apbCharge], inputtext, true) != -1)
                {
                    if(count < 18)
                    {
                        format(str, sizeof(str), "%s"I"[%d]"W" %s\t%s\t%s\t%.30s%s\n", str, i + 1, ApbInfo[i][apbDate], ApbInfo[i][apbOfficer], ApbInfo[i][apbSuspect], ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 30)?(".."):(""));
                        MdcInfo[count][mdcList] = i;
                    }
                    count++;
                }
            }

            if(!count) return ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_LIST, ""I"APB - Поиск по имени", ""W"Нет APB для отображения...", ">>>", "");

            ShowPlayerDialog(playerid, D_APB_SEARCH_CHARGE_ACTIONS, DIALOG_STYLE_TABLIST_HEADERS, ""I"APB - Поиск по имени", str, ">>>", "Назад");
            return 1;
        }

        case D_APB_SEARCH_CHARGE_ACTIONS:
        {
            if(!response) return APB_Menu(playerid);

            new mes[256], i_apb = MdcInfo[listitem][mdcList];
            SetPVarInt(playerid, #MDC_ID, i_apb);

            format(mes, sizeof(mes), ""I"#%i\n\n"I"Подозреваемый:"W"\t %s\n"I"Описание:"W"\t\t %s\n\n"I"Добавил:"W"\t\t %s\n"I"Дата:"W"\t\t\t %s\n", ApbInfo[i_apb][apbID]+90214, ApbInfo[i_apb][apbSuspect], ApbInfo[i_apb][apbCharge], ApbInfo[i_apb][apbOfficer], ApbInfo[i_apb][apbDate]);
            ShowPlayerDialog(playerid, D_APB_DETAILS, DIALOG_STYLE_MSGBOX, ""I"Редактирование APB", mes, "Изменить", "Отмена");
            return 1;
        }
        case D_APB_DETAILS:
        {
            if(!response) return APB_List(playerid);
            return ShowPlayerDialog(playerid, D_APB_OPTIONS, DIALOG_STYLE_LIST, ""I"Редактирование APB", ""I"[1]"W" Править строку 'подозреваемый'\n"I"[2]"W" Править строку 'описание'\n"I"[3]"W" Удалить", "Выбрать", "Назад");
        }

        case D_APB_OPTIONS:
        {
            if(!response) return APB_List(playerid);
            switch(listitem)
            {
                case 0: ShowPlayerDialog(playerid, D_APB_EDIT_NAME, DIALOG_STYLE_INPUT, ""I"Редактирование APB", ""W"Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Готово", "Назад");
                case 1: ShowPlayerDialog(playerid, D_APB_EDIT_CHARGE, DIALOG_STYLE_INPUT, ""I"Редактирование APB", ""W"Введите описание подозреваемого:\n- Максимальное кол-во символов: 128", "Готово", "Назад");
                case 2: ShowPlayerDialog(playerid, D_APB_DELETE, DIALOG_STYLE_MSGBOX, ""I"Подтверждение", ""W"Вы действительно хотите удалить APB?", "Да", "Нет");
            }
            return 1;
        }
        case D_APB_EDIT_NAME:
        {
            if(!response) return ShowPlayerDialog(playerid, D_APB_DETAILS, DIALOG_STYLE_LIST, ""I"Редактирование APB", ""I"[1]"W" Править строку 'подозреваемый'\n"I"[2]"W" Править строку 'описание'\n"I"[3]"W" Удалить", "Выбрать", "Назад");
            if(strlen(inputtext) < 1 || strlen(inputtext) > 127) return ShowPlayerDialog(playerid, D_APB_EDIT_NAME, DIALOG_STYLE_INPUT, ""I"Редактирование APB", ""W"Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Готово", "Назад");
            new number = GetPVarInt(playerid, #MDC_ID);

            SendAccess(playerid, "Вы изменили APB заметку номер %i.", number);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "* HQ: %s %s изменил APB номер %i.", GetPlayerFractionRangName(playerid), get_name(playerid), number);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

            format(ApbInfo[number][apbSuspect], MAX_PLAYER_NAME, inputtext);
            format(ApbInfo[number][apbOfficer], MAX_PLAYER_NAME, "%s", get_name(playerid));
            ApbInfo[number][apbFaction] = p_info[playerid][member];

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd,STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `apbs` SET `suspect` = '%e', `officer` = '%e' WHERE `id` = %i",
                ApbInfo[number][apbSuspect], ApbInfo[number][apbOfficer], ApbInfo[number][apbID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"#%i\n\n"W"Подозреваемый:"I"\t %s\n"W"Описание:"I"\t\t %s\n\n"W"Добавил:"I"\t\t %s\n"W"Дата:"I"\t\t\t %s\n", ApbInfo[number][apbID]+90214, ApbInfo[number][apbSuspect], ApbInfo[number][apbCharge], ApbInfo[number][apbOfficer], ApbInfo[number][apbDate]);
            ShowPlayerDialog(playerid, D_APB_DETAILS, DIALOG_STYLE_MSGBOX, ""I"Редактирование APB", STRING_GLOBAL, "Изменить", "Отмена");

            DeletePVar(playerid, #MDC_ID);
            return 1;
        }

        case D_APB_DELETE:
        {
            if(!response) return 1;
            new number = GetPVarInt(playerid, #MDC_ID);
            if(!ApbInfo[number][apbOn]) return SendError(playerid, "APB заметка не найдена.");

            SendAccess(playerid, "Вы очистили APB заметку номер %i.", number);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "* HQ: %s %s удалил APB заметку номер %i.", GetPlayerFractionRangName(playerid), get_name(playerid), number);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `apbs` WHERE `id` = %i", ApbInfo[number][apbID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            ApbInfo[number][apbOn] =
            ApbInfo[number][apbID] = 0;
            APB_List(playerid);
            return 1;
        }
        case D_APB_EDIT_CHARGE:
        {
            if(!response) return ShowPlayerDialog(playerid, D_APB_OPTIONS, DIALOG_STYLE_TABLIST, ""I"Редактирование APB", ""I"[1]"W" Править строку 'подозреваемый'\n"I"[2]"W" Править строку 'описание'\n"I"[3]"W" Удалить", "Выбрать", "Назад");
            if(strlen(inputtext) < 1 || strlen(inputtext) > 127) return ShowPlayerDialog(playerid, D_APB_EDIT_CHARGE, DIALOG_STYLE_INPUT, ""I"Редактирование APB", ""W"Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Готово", "Назад");
            new number = GetPVarInt(playerid, #MDC_ID);

            SendAccess(playerid, "Вы изменили APB заметку [NUM: %i].", number);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "* HQ: %s %s изменил APB номер %i.", GetPlayerFractionRangName(playerid), get_name(playerid), number);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

            format(ApbInfo[number][apbCharge], 128, "%s", inputtext);
            format(ApbInfo[number][apbOfficer], MAX_PLAYER_NAME, "%s", get_name(playerid));
            ApbInfo[number][apbFaction] = p_info[playerid][member];

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd,STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `apbs` SET `charge` = '%e', `officer` = '%e' WHERE `id` = %i",
                ApbInfo[number][apbCharge], ApbInfo[number][apbOfficer], ApbInfo[number][apbID]);
            mysql_tquery(con_bd, STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""I"#%i\n\n"I"Подозреваемый:"W"\t %s\n"I"Описание:"W"\t\t %s\n\n"I"Добавил:"W"\t\t %s\n"I"Дата:"W"\t\t\t %s\n", ApbInfo[number][apbID]+90214, ApbInfo[number][apbSuspect], ApbInfo[number][apbCharge], ApbInfo[number][apbOfficer], ApbInfo[number][apbDate]);
            ShowPlayerDialog(playerid, D_APB_DETAILS, DIALOG_STYLE_MSGBOX, ""I"Редактирование APB", STRING_GLOBAL, "Изменить", "Отмена");

            DeletePVar(playerid, #MDC_ID);
            return 1;
        }

        case D_CALLS_LIST:
        {
            if(!response)                        return 1;
            if(!IsPlayerFractionPolice(playerid) &&
                !IsPlayerFractionMedic(playerid)/* &&
                !IsPlayerFactionFire(playerid)*/) return 1;

            new mes[512], count, type = (IsPlayerFractionMedic(playerid)/* || IsPlayerFactionFire(playerid)*/)?(2):(1);

            for(new i = 0; i != MAX_CALLS_AND_ARREST; i++)
            {
                if(!CallInfo[i][callExists]) continue;
                if(CallInfo[i][callType] != 3) {
                    if(CallInfo[i][callType] != type) continue;
                }

                if(listitem == count)
                {
                    new statusmes[65];
                    if(CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
                    else format(statusmes, sizeof(statusmes), "{A9C4E4}Вызов не принят{B4B5B7}");

                    format(mes, sizeof(mes), "{B4B5B7}911-ИНФОРМАЦИЯ О ЗВОНКЕ - #%i\n\n\
                                            Звонок от:\t\t%s\n\
                                            Номер телефона:\t%i\n\
                                            Ситуация:\t\t%s\n\
                                            Местоположение:\t%s\n\
                                            Дата:\t\t\t%s\n\n\
                                            Статус:\t\t\t%s\n\
                                            На вызов откликнулись %i раз(-а)",
                    i+1, CallInfo[i][callName], CallInfo[i][callPhone], CallInfo[i][callText], CallInfo[i][callLocation], CallInfo[i][callDate], statusmes, CallInfo[i][callAccept]);

                    ShowPlayerDialog(playerid, D_CALL_INFO, DIALOG_STYLE_MSGBOX, ""I"MDC - Информация о звонке", mes, "Опции", "Назад");
                    SetPVarInt(playerid, #last_call, i);
                    return 1;
                }
                count++;
            }
            return 1;
        }
        case D_CALL_INFO:
        {
            if(!response) return Get_Calls(playerid);
            ShowPlayerDialog(playerid, D_CALL_INFO_RESPOND, DIALOG_STYLE_LIST, ""I"MDC - Информация о звонке", ""I"[1]"W" Принять вызов\n"I"[2]"W" Отклонить вызов", "Выбрать", "Назад");
            return 1;
        }
        case D_CALL_INFO_RESPOND:
        {
            if(!response)
                return 1;

            if(!IsPlayerFractionPolice(playerid) &&
                !IsPlayerFractionMedic(playerid))// &&
                //!IsPlayerFactionFire(playerid))
                return 1;

            new type = (IsPlayerFractionMedic(playerid)/* || IsPlayerFractionFire(playerid)*/)? (2) : (1),
                id = GetPVarInt(playerid, #last_call);

            if(!CallInfo[id][callExists]) return 1;
            if(CallInfo[id][callType] != 3) {
                if(CallInfo[id][callType] != type) return 1;
            }

            if(!listitem)
            {
                if(p_temp[playerid][pPatrol])
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "* [%s] %s %s [%s] принял вызов в 911. #%i.", GetFractionName(p_info[playerid][member]), GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][p_temp[playerid][pPatrol]-1][patrulName], id+1);
                    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
                }
                else
                {
                    STRING_GLOBAL[0] = EOS;
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "* [%s] %s %s принял вызов в 911. #%i.", GetFractionName(p_info[playerid][member]), GetPlayerFractionRangName(playerid), get_name(playerid), id+1);
                    SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
                }

                if(p_temp[playerid][pPatrol]) format(CallInfo[id][callAcceptBy], 64, "Принято %s (%s)", get_name(playerid), PatrolInfo[GetPatrolID(playerid)][p_temp[playerid][pPatrol]-1][patrulName]);
                else format(CallInfo[id][callAcceptBy], 64, "Принято %s", get_name(playerid));

                SetPlayerGPS(playerid, CallInfo[id][callPosX],CallInfo[id][callPosY],CallInfo[id][callPosZ], 3.0);
                //Waypoint_Set(playerid, CallInfo[id][callPosX],CallInfo[id][callPosY],CallInfo[id][callPosZ], 3.0);

                CallInfo[id][callAccept]++;
                p_temp[playerid][pPoliceCalls]++;

                CallInfo[id][callExists] = 0;
                CallInfo[id][callType] = 0;
                CallInfo[id][callAccept] = 0;
            }
            else
            {
                //SendFactionMessage(FACTION_POLICE, COLOR_LSPD, "* [%s] %s %s удалил вызов в 911. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetRankName(playerid), GetNameEx(playerid), id+1);
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL),  "* [%s] %s %s удалил вызов в 911. #%i.", GetFractionName(p_info[playerid][member]), GetPlayerFractionRangName(playerid), get_name(playerid), id+1);
                SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

                SendAccess(playerid, "Вызов [ID: %i] был удален.", id+1);
                CallInfo[id][callExists] = 0;
                CallInfo[id][callType] = 0;
                CallInfo[id][callAccept] = 0;

                MDC_PAGE(playerid, PAGE_MAIN);
            }
            return 1;
        }
    }
    return 1;
}
