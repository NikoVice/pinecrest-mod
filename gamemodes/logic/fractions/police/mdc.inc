CMD:mdc(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid) &&
        !IsPlayerFractionMedic(playerid)) return SendError(playerid, "Вы должны быть полицейским или медиком.");
    if(p_info[playerid][rang] < 2) return 1;
    new vehicleid = GetPlayerVehicleID(playerid);
    if(vehicleid == 0 || veh_info[vehicleid][v_npoId] != p_info[playerid][member] /*BUG:FIX && !IsPlayerInRangeOfPoint(playerid, 50.0, Factions[id][fPosX], Factions[id][fPosY], Factions[id][fPosZ])*/)
        return SendError(playerid, "Доступно только в транспорте.");//в HQ или

    if(p_info[playerid][fwork] == false) return SendError(playerid, "Сначала нужно выйти на дежурство.");
    if(IsPlayerFractionPolice(playerid))
    {
        if(IsPlayerUseMDC(playerid)) return MDC_Hide(playerid);
        if(IsTDVisible(playerid) != -1) return 1;
        if(p_temp[playerid][pCCTV]) return 1; // нельзя пока что использовать

        MdcInfo[playerid][mdcPage] = PAGE_NONE;
        MDC_Show(playerid);
        SelectTextDraw(playerid, 255);//-1 //0x6d856eFF //-1061109505
        return 1;
    }
    if(IsPlayerFractionMedic(playerid))
        Get_Calls(playerid);
    return 1;
}

CMD:calls(playerid, params[])
{
    if(!IsPlayerFractionPolice(playerid) &&
        !IsPlayerFractionMedic(playerid)) return SendError(playerid, "Вы должны быть полицейским или медиком.");
    if(p_info[playerid][rang] < 8) return 1;
    Get_Calls(playerid);
    return 1;
}

MDC_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(playertextid == MDC_UI[playerid][14]) // X
    {
        MDC_Hide(playerid);
        return 1;
    }

    if(playertextid == MDC_BACK[playerid])
    {
        if(MdcInfo[playerid][mdcBack] == PAGE_LOOKUP_VEHICLES_LIST)
        {

            new query[256];
            if(GetPVarInt(playerid, #MDC_OWNER_ID)) mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` = %i AND `v_mysql_id` >= %i AND `v_number` != 'NULL' LIMIT 4", GetPVarInt(playerid, #MDC_OWNER_ID), MdcInfo[playerid][mdcList][0]);
            else
            {
                new numbers[24];
                GetPVarString(playerid, #MDC_SEARCH_VEHICLE_NUM, numbers, 24);
                mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` != 0 AND `v_mysql_id` >= %i AND `v_number` LIKE '%%%e%%' LIMIT 4", MdcInfo[playerid][mdcList][0], numbers);
            }
            mysql_tquery(con_bd, query, "MDCSearchVehiclesList", "ii", playerid, GetPVarInt(playerid, #MDC_OWNER_ID));
        }
        else if(MdcInfo[playerid][mdcBack] == PAGE_LOOKUP_VEHICLE)
        {
            new query[164];
            mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` = %i AND `v_number` != 'NULL' LIMIT 1", GetPVarInt(playerid, #MDC_ID));
            mysql_tquery(con_bd, query, "MDCSearchVehicle", "ii", playerid, 0);
        }
        else if(MdcInfo[playerid][mdcBack] == PAGE_LOOKUP_PERSON)
        {
            new query[64];
            mysql_format(con_bd, query, sizeof(query), "SELECT a.`name`, a.`id`, i.`item_id`, a.`Lic`, a.`active_house_id`, a.`phone_number`, a.`jail` \
                FROM `accounts` AS a \
                LEFT JOIN `inventory` AS i ON a.`id` = i.`owner_id` \
                WHERE a.`id` = %d AND i.status_use = 1 AND i.`item_id` < 311 LIMIT 1", GetPVarInt(playerid, #MDC_ID));
            mysql_tquery(con_bd, query, "MDCSearchPersonInfo", "i", playerid);
            MdcInfo[playerid][mdcListPage] = 0;
        }
        else if(MdcInfo[playerid][mdcBack] == PAGE_MENU)
        {
            Update_MDC(playerid, PAGE_MENU);

            for(new j = 0; j < 16; j++)
            {
                if(MdcInfo[playerid][mdcList][j] != -1)
                    PlayerTextDrawShow(playerid, MDC_LIST[playerid][j]);
            }

            if(MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
                MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
            else
                MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_VEHICLE;
        }
        else if(MdcInfo[playerid][mdcBack] == PAGE_MEMBERS)
        {
            Update_MDC(playerid, PAGE_MEMBERS);
            MDC_ShowMembersMenu(playerid);
        }
        return 1;
    }

    if(playertextid == MDC_UI[playerid][2]) // "ГЛАВНАЯ");
    {
        MDC_PAGE(playerid, PAGE_MAIN);
        return 1;
    }
    if(playertextid == MDC_UI[playerid][3]) // "ПОИСК");
    {
        MDC_PAGE(playerid, PAGE_LOOKUP);
        return 1;
    }

    if(playertextid == MDC_UI[playerid][4]) // "ВЫЗОВЫ");
    {
        //SendInfo(playerid, "В разработке.");
        //MDC_PAGE(playerid, PAGE_CALLS);
        MDC_PAGE(playerid, PAGE_MAIN);
        Get_Calls(playerid);
        return 1;
    }

    if(playertextid == MDC_UI[playerid][5]) // "СОТРУДНИКИ");
    {
        MDC_PAGE(playerid, PAGE_MEMBERS);
        return 1;
    }

    if(playertextid == MDC_UI[playerid][6]) // "APB");
    {
        if(p_info[playerid][rang] < 3) return SendError(playerid, "Доступно с 3 ранга.");
        APB_Menu(playerid);
        //MDC_PAGE(playerid, PAGE_APB);
        return 1;
    }

    if(playertextid == MDC_UI[playerid][7]) // "ЮНИТЫ");
    {
        MDC_PAGE(playerid, PAGE_ROSTER);
        return 1;
    }

    if(playertextid == MDC_UI[playerid][8]) // "CCTV");
    {
        if(p_info[playerid][rang] < 3) return SendError(playerid, "Доступно с 3 ранга.");
        MDC_PAGE(playerid, PAGE_CCTV);
        return 1;
    }

    if(playertextid == MDC_LOOKUP_SEARCH[playerid][0]) // "ИМЯ");
    {
        /*if(MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            new apb = -1;

            for(new i = MAX_APBS-1; i >= 0; i--)
            {
                if(ApbInfo[i][apbOn] != 0) continue;

                apb = i;
                break;
            }

            if(apb == -1)    return SendError(playerid, "Нет места для новой APB заметки.");

            SetPVarInt(playerid, #MDC_ID, apb);
            ShowPlayerDialog(playerid, D_APB_CREATE_FIRST, DIALOG_STYLE_INPUT, ""I"Создание APB", ""W""Введите имя подозреваемого:\n- Максимальное кол-во символов: 24", "Далее", "Отмена");
        }
        else
        {*/
        PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF); // ИМЯ

        PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF); // ТС

        for(new i = 0; i < 2; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);

        MdcInfo[playerid][mdcSearch] = 0;
        //}
        return 1;
    }

    if(playertextid == MDC_LOOKUP_SEARCH[playerid][1]) // "ТС");
    {
        /*
        if(MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            if(MdcInfo[playerid][mdcSearch])
            {
                PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "BY NAME");
                MdcInfo[playerid][mdcSearch] = 0;

                PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF);
                PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF); // ТС
            }
            else
            {
                PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "BY TEXT");
                MdcInfo[playerid][mdcSearch] = 1;

                PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
                PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF); // ТС
            }
        }
        else
        {*/
        PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF);
        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF); // ИМЯ

        PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF);
        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF); // ТС

        for(new i = 0; i < 2; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);

        MdcInfo[playerid][mdcSearch] = 1;
        //}
        return 1;
       }

    if(playertextid == MDC_LOOKUP_SEARCH[playerid][2]) // "ВВОД");
    {
        /*
        if(MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            if(!MdcInfo[playerid][mdcSearch])
                ShowPlayerDialog(playerid, D_MDC_APB_SEARCH_NAME, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск по имени", ""W""ведите имя или часть имени для поиска:", "Ввод", "Назад");
            else
                ShowPlayerDialog(playerid, D_MDC_APB_SEARCH_CHARGE, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск по описанию", ""W"Введите слово или часть слова для поиска:", "Ввод", "Назад");
        }
        else
        {*/
        if(!MdcInfo[playerid][mdcSearch])
            ShowPlayerDialog(playerid, D_MDC_SEARCH_PERSON, DIALOG_STYLE_INPUT, ""I"MDC  - Поиск по ID", ""W"ПОИСК ПО ID\n\nВведите ID:", "Ввод", "Назад");
        else
            ShowPlayerDialog(playerid, D_MDC_SEARCH_VEHICLE_TYPE, DIALOG_STYLE_LIST, ""I"MDC  - Поиск транспортного средства", ""I"[1]"W" Поиск транспортного средства по владельцу\n"I"[2]"W" Поиск транспортного средства по номеру", "Выбрать", "Назад");
        //}
        return 1;
    }

    if(playertextid == MDC_LOOKUP_SEARCH[playerid][3]) // "СБРОСИТЬ");
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "______________");
        PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

        SetPVarInt(playerid, #MDC_APB_S, 0);

        /*
        if(MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            MDC_PAGE(playerid, PAGE_APB);
        }
        else
        {*/
        for(new h = 0; h < 6; h++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLE[playerid][h]);

        for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
        for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
        for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

        for(new j = 0; j < 2; j++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][j]);
        for(new k = 0; k < 12; k++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][k]);

        MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
        //}

        MdcInfo[playerid][mdcListPage] = 0;

        return 1;
    }

    if(playertextid == MDC_LOOKUP_PERSON[playerid][4])
    {
        if(MdcInfo[playerid][mdcPage] == PAGE_MEMBERS_MAP) {
            new targetid = p_temp[playerid][MDC_BODYCAM], targetState = GetPlayerState(targetid);
            if(targetid == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
            if(p_info[targetid][rang] >= p_info[playerid][rang])
                return SendError(playerid, "Ваш ранг должен быть меньше ранга этого офицера.");
            if( targetState == PLAYER_STATE_SPECTATING ||
                targetState == PLAYER_STATE_SPAWNED ||
                targetState == PLAYER_STATE_WASTED) return 1;
            if(IsPlayerInAnyVehicle(playerid)) {
                SetPVarInt(playerid, #CCTV_VEH, GetPlayerVehicleID(playerid));
                SetPVarInt(playerid, #CCTV_VEH_SEAT, GetPlayerVehicleSeat(playerid));
                RemovePlayerFromVehicle(playerid);
            }
            pSpectateId[playerid] = targetid;
            if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
            {
                GetPlayerPos(playerid, pPosBeforeSpectateX[playerid], pPosBeforeSpectateY[playerid], pPosBeforeSpectateZ[playerid]);
                pInteriorBeforeSpectate[playerid] = GetPlayerInterior(playerid);
                pVirtualWorldBeforeSpectate[playerid] = GetPlayerVirtualWorld(playerid);
                SetPVarInt(playerid, !"spawn_after_spectate_mode", 2);
            }
            if(MdcInfo[playerid][mdcPage] != PAGE_NONE) {
                SetPVarInt(playerid, #BODY_MDC_USE, 1);
                MDC_Hide(playerid);
            }

            TogglePlayerSpectating(playerid, 1);
            if(IsPlayerInAnyVehicle(targetid))
                PlayerSpectateVehicle(playerid, GetPlayerVehicleID(targetid));
            else
                PlayerSpectatePlayer(playerid, targetid);

            SetPlayerInterior(playerid, GetPlayerInterior(targetid));
            SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

            SendInfo(playerid, "Введите /specoff, чтобы закончить наблюдать.");
        }
        else ShowPlayerDialog(playerid, D_MDC_RECORD_ADD, DIALOG_STYLE_INPUT, ""I"MDC - Предъявление обвинения", ""W"ПРЕДЪЯВЛЕНИЕ ОБВИНЕНИЙ\n\nВведите текст обвинения: (( Преступление / 64 символов))", "Ввод", "Отмена");
        return 1;
    }

    if(playertextid == MDC_LOOKUP_PERSON[playerid][5])
    {
        if(p_info[playerid][rang] < 4) return SendError(playerid, "Доступно с 4 ранга.");
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `Lic`, `Lic_Warn` FROM `accounts` WHERE `id` = %i", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(con_bd, STRING_GLOBAL, "MDC_LICENSES_LIST", "i", playerid);
        return 1;
    }

    if(playertextid == MDC_LOOKUP_PERSON[playerid][6]) // Просмотр штрафов
    {
        p_temp[playerid][list_type] = 0;
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `tickets` WHERE `userid`= %i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayersTickets", "ii", playerid, 0);

        SetPVarInt(playerid, #tickets_show, GetPVarInt(playerid, #MDC_ID));
        SetPVarInt(playerid, #ticketsuse, 1);
        return 1;
    }

    if(playertextid == MDC_LOOKUP_PERSON[playerid][7]) // СУДИМОСТИ
    {
        p_temp[playerid][list_type] = 0;
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `criminalrecords` WHERE `userid`= %i ORDER BY `id` DESC LIMIT %d", GetPVarInt(playerid, #MDC_ID), MAX_TICKETS);
        mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayersRecords", "ii", playerid, 0);

        /*
        MdcInfo[playerid][mdcListPage] = 0;

        new Float:countticket = CountPlayerRecordsID(GetPVarInt(playerid, #MDC_ID));
        countticket = countticket/16;
        SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countticket, floatround_ceil));
        */
        return 1;
    }

    if(playertextid == MDC_LOOKUP_PERSON[playerid][10]) // НЕДВИЖИМОСТЬ
    {
        //if(MdcInfo[playerid][mdcCreated] != 0)  return 1;

        new query[255];
        mysql_format(con_bd, query, sizeof(query), "SELECT * FROM `accounts` WHERE `id` = %i", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(con_bd, query, "MDC_MAP", "i", playerid);
        return 1;
    }

    for(new k = 1; k < 6; k++)
    {
        if(playertextid == MDC_OTHER_ADDRESS[playerid][k])
        {
            new strhouse[80],
                Float:map_kY = -0.04795376,
                Float:map_kX = 0.0469,

                Float:map_sX = 333.999420,
                Float:map_sY = 295.181152,

                Float:corX, Float:corY,
                area;

            new dot = MdcInfo[playerid][mdcList][k-1];
            if(h_info[dot][h_enter][0] >= 0.000000)
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit2");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit4");
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][0]);
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][1]);

                map_kX = 0.0469;
                map_sX = 333.999420;

                corX = h_info[dot][h_enter][0] * map_kX + map_sX;
                corY = h_info[dot][h_enter][1] * map_kY + map_sY;
            }
            else
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit1");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit3");
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][0]);
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][1]);

                map_kX = -0.0469;
                map_sX = 480.066314;

                corX = map_sX - h_info[dot][h_enter][0] * map_kX;
                corY = h_info[dot][h_enter][1] * map_kY + map_sY;
            }

            area = GetZonaName(h_info[dot][h_enter][0], h_info[dot][h_enter][1]);
            format(strhouse, sizeof(strhouse), "%s %d,~n~San Andreas", gSAZones[area][SAZONE_NAME], dot);
            PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][4], strhouse);

            PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][2]);
            MDC_ADDRESS[playerid][2] = PlayerText:INVALID_TEXT_DRAW;

            MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, corX, corY, "hud:radar_propertyG");
            PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 5.000000, 6.000000);
            PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
            PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][2]);
        }
    }

    for(new i = 0; i < 4; i++)
    {
        if(playertextid == MDC_VEH_LIST_CLICK[playerid][i])
        {
            new query[156];
            mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_mysql_id` = %i LIMIT 1", MdcInfo[playerid][mdcList][i]);
            mysql_tquery(con_bd, query, "MDCSearchVehicle", "ii", playerid, 0);

            Update_MDC(playerid, PAGE_LOOKUP_VEHICLE);
            return 1;
        }
    }

    if(playertextid == MDC_LOOKUP_VEHICLES_ARROWS[playerid][1]) //+
    {
        new query[256];
        if(MdcInfo[playerid][mdcPage] == PAGE_LOOKUP_VEHICLES_LIST)
        {
            if(MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            if(GetPVarInt(playerid, #MDC_OWNER_ID)) mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id =vehicle.v_owner_id ) as ownername FROM `vehicle` WHERE `v_owner_id` = %i AND `v_mysql_id` > %i AND `v_number` != 'NULL' LIMIT 4", GetPVarInt(playerid, #MDC_OWNER_ID), MdcInfo[playerid][mdcList][3]);
            else
            {
                new numbers[24];
                GetPVarString(playerid, #MDC_SEARCH_VEHICLE_NUM, numbers, 24);
                mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` != 0 AND `v_mysql_id` > %i AND `v_number` LIKE '%%%e%%' LIMIT 4", MdcInfo[playerid][mdcList][3], numbers);
            }
            mysql_tquery(con_bd, query, "MDCSearchVehiclesList", "ii", playerid, GetPVarInt(playerid, #MDC_OWNER_ID));

            MdcInfo[playerid][mdcListPage]++;
            return 1;
        }
        /*
        else if(MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            if(MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][apb]);

            new count,
                string[256],
                text[128];

            GetPVarString(playerid, #MDC_APB_TEXT, text, 128);

            for(new i = MdcInfo[4][mdcList]-1; i >= 0; i--)
            {
                if(ApbInfo[i][apbOn] == 0) continue;

                if(count < 5)
                {
                    if(GetPVarInt(playerid, #MDC_APB_S))
                        if(strfind(ApbInfo[i][apbCharge], text, true) != -1) continue;

                    format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
                    PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][count*4+1], string);

                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
                }
                else break;
                count++;
            }

            MdcInfo[playerid][mdcListPage]++;

            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        else if(MdcInfo[playerid][mdcPage] == PAGE_CALLS)
        {
            if(MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][apb]);

            new
                count,
                string[256]
            ;

            for(new i = MdcInfo[4][mdcList]-1; i >= 0; i--)
            {
                if(CallInfo[i][callExists] == 0) continue;

                if(count < 5)
                {
                    new statusmes[65];
                    if(CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
                    else format(statusmes, sizeof(statusmes), "~r~ВЫЗОВ НЕ ПРИНЯТ");

                    switch(CallInfo[i][callType])
                    {
                        case 1: format(string, sizeof(string), "SAPD");
                        case 2: format(string, sizeof(string), "SAFD");
                        case 3: format(string, sizeof(string), "SAPD, SAFD");
                    }

                    format(string, sizeof(string), "%s (Тел. %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s",
                        CallInfo[i][callName],
                        CallInfo[i][callPhone],
                        string,
                        CallInfo[i][callLocation],
                        CallInfo[i][callText],
                        (strlen(CallInfo[i][callText]) > 60)?(" .."):(""),
                        CallInfo[i][callDate],
                        statusmes
                    );
                    PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][count*4+1], string);

                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_CALLS_TD[playerid][j]);
                    if(CallInfo[i][callAccept]) PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][count*4+2]);
                }
                else break;
                count++;
            }

            MdcInfo[playerid][mdcListPage]++;

            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }*/
        else if(MdcInfo[playerid][mdcPage] == PAGE_CCTV)
        {
            if(MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            MdcInfo[playerid][mdcListPage]++;

            mysql_format(con_bd, query, sizeof(query), "SELECT * FROM `cctvs` WHERE `id` > %i ORDER BY `id` DESC LIMIT 16", MdcInfo[playerid][mdcList][15]);
            mysql_tquery(con_bd, query, "MDC_ShowCCTVMenu", "ii", playerid, 0);
            return 1;
        }
        else if(MdcInfo[playerid][mdcPage] == PAGE_ROSTER)
        {
            if(MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            MdcInfo[playerid][mdcListPage]++;

            MDC_ShowRosterMenu(playerid);
            return 1;
        }
    }
    if(playertextid == MDC_LOOKUP_VEHICLES_ARROWS[playerid][2]) //--
    {
        if(!MdcInfo[playerid][mdcListPage]) return 1;
        new query[256];
        if(MdcInfo[playerid][mdcPage] == PAGE_LOOKUP_VEHICLES_LIST)
        {
            if(GetPVarInt(playerid, #MDC_OWNER_ID)) mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` = %i AND `v_mysql_id` < %i AND `v_number` != 'NULL' LIMIT 4", GetPVarInt(playerid, #MDC_OWNER_ID), MdcInfo[playerid][mdcList][0]);
            else
            {
                new numbers[24];
                GetPVarString(playerid, #MDC_SEARCH_VEHICLE_NUM, numbers, 24);
                mysql_format(con_bd, query, sizeof(query), "(SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` != 0 AND `v_mysql_id` < %d AND `v_number` LIKE '%%%e%%' ORDER BY `v_mysql_id` DESC LIMIT 4) ORDER BY `v_mysql_id` ASC", MdcInfo[playerid][mdcList][0], numbers);
            }
            mysql_tquery(con_bd, query, "MDCSearchVehiclesList", "ii", playerid, GetPVarInt(playerid, #MDC_OWNER_ID));
            MdcInfo[playerid][mdcListPage]--;
            return 1;
        }
        /*
        else if(MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][apb]);

            new count,
                string[256],
                text[128];
            GetPVarString(playerid, #MDC_APB_TEXT, text, 128);

            for(new i = MdcInfo[0][mdcList]+1; i != MAX_APBS; i++)
            {
                if(ApbInfo[i][apbOn] == 0) continue;

                if(count < 5)
                {
                    if(GetPVarInt(playerid, #MDC_APB_S))
                        if(strfind(ApbInfo[i][apbCharge], text, true) != -1) continue;

                    format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
                    PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][17 - count*4], string);

                    MdcInfo[4-count][mdcList] = i;

                    for(new j = 19 - count*4; j > 19 - (count+1)*4; j--) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
                }
                else break;
                count++;
            }
            MdcInfo[playerid][mdcListPage]--;

            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        else if(MdcInfo[playerid][mdcPage] == PAGE_CALLS)
        {
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][apb]);

            new
                count,
                string[256]
            ;

            for(new i = MdcInfo[0][mdcList]+5; i != MAX_CALLS_AND_ARREST; i--)
            {
                if(CallInfo[i][callExists] == 0) continue;

                new statusmes[65];
                if(CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
                else format(statusmes, sizeof(statusmes), "~r~ВЫЗОВ НЕ ПРИНЯТ");

                switch(CallInfo[i][callType])
                {
                    case 1: format(string, sizeof(string), "SAPD");
                    case 2: format(string, sizeof(string), "SAFD");
                    case 3: format(string, sizeof(string), "SAPD, SAFD");
                }

                if(count < 5)
                {
                    format(string, sizeof(string), "%s (Тел. %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s",
                        CallInfo[i][callName],
                        CallInfo[i][callPhone],
                        string,
                        CallInfo[i][callLocation],
                        CallInfo[i][callText],
                        (strlen(CallInfo[i][callText]) > 60)?(" .."):(""),
                        CallInfo[i][callDate],
                        statusmes
                    );
                    PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][count*4+1], string);

                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_CALLS_TD[playerid][j]);
                    if(CallInfo[i][callAccept]) PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][count*4+2]);
                }
                else break;
                count++;
            }

            MdcInfo[playerid][mdcListPage]--;

            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        */
        else if(MdcInfo[playerid][mdcPage] == PAGE_CCTV)
        {
            MdcInfo[playerid][mdcListPage]--;

            mysql_format(con_bd, query, sizeof(query), "SELECT * FROM `cctvs` WHERE `id` < %i LIMIT 16", MdcInfo[playerid][mdcList][0]);
            mysql_tquery(con_bd, query, "MDC_ShowCCTVMenu", "ii", playerid, 1);
            return 1;
        }
        else if(MdcInfo[playerid][mdcPage] == PAGE_ROSTER)
        {
            MdcInfo[playerid][mdcListPage]--;
            MDC_ShowRosterMenu(playerid);
            return 1;
        }
    }

    if(playertextid == MDC_LOOKUP_VEHICLE[playerid][5]) // ОБЬЯВИТЬ ТС В РОЗЫСК
    {
        if(p_info[playerid][rang] < 4) return SendError(playerid, "Доступно с 4 ранга.");
        new query[164];
        mysql_format(con_bd, query, sizeof(query), "SELECT `v_wanted`, `v_number`, `v_model` FROM `vehicle` WHERE `v_mysql_id` = %d LIMIT 1", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(con_bd, query, "MDC_Veh_Wanted", "i", playerid);
        return 1;
    }
    if(playertextid == MDC_LOOKUP_VEHICLE[playerid][4]) //ДОБАВИТЬ ЗАМЕТКУ");
    {
        if(p_info[playerid][rang] < 3) return SendError(playerid, "Доступно с 3 ранга.");
        ShowPlayerList(playerid, LIST_ID_VEHICLE_NOTES);
        return 1;
    }

    if(playertextid == MDC_LOOKUP_VEHICLE[playerid][3]) // Просмотр штрафов
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `tickets` WHERE `vehicle`= %i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(con_bd, STRING_GLOBAL, "ShowCarsTickets", "ii", playerid, 0);

        SetPVarInt(playerid, #tickets_show, GetPVarInt(playerid, #MDC_ID));
        SetPVarInt(playerid, #ticketsuse, 1);
        return 1;
    }

    for(new j = 0; j < 16; j++)
    {
        if(playertextid == MDC_LIST[playerid][j])
        {
            /*
            new query[156];
            if(MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
            {
                if(GetPVarInt(playerid, #MDC_FINE))
                {
                    mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id =tickets.userid) as ownername FROM `tickets` WHERE `userid`=%i AND `id`=%i LIMIT 1",
                        GetPVarInt(playerid, #MDC_ID),
                        MdcInfo[playerid][mdcList][j]
                    );
                    return mysql_tquery(con_bd, query, "MDC_ShowInfo", "i", playerid);
                }
                else
                {
                    mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id =criminalrecords.userid) as ownername FROM `criminalrecords` WHERE `userid`=%i AND `id`=%i LIMIT 1",
                        GetPVarInt(playerid, #MDC_ID),
                        MdcInfo[playerid][mdcList][j]
                    );
                    return mysql_tquery(con_bd, query, "MDC_ShowInfo", "i", playerid);
                }

            }
            else if(MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_VEHICLE)
            {
                mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `v_model` FROM `vehicle` WHERE id = tickets.vehicle) as vehiclemodel FROM `tickets` WHERE `vehicle`=%i AND `id`=%i LIMIT 1",
                    GetPVarInt(playerid, #MDC_ID),
                    MdcInfo[playerid][mdcList][j]);
                return mysql_tquery(con_bd, query, "MDC_ShowInfo", "i", playerid);
            }
            */
            if(MdcInfo[playerid][mdcPage] == PAGE_CCTV)
            {
                /*
                new factionid = p_info[playerid][member];
                if(!IsPlayerInRangeOfPoint(playerid, 30.0, Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ])) {
                    return SendError(playerid, "Данная функция доступна только в HQ.");
                }
                */
                new command[10], id;
                for(new cam = 0; cam < MAX_CCTV; cam++)
                {
                    if(CCTVInfo[cam][tvID] == MdcInfo[playerid][mdcList][j])
                    {
                        id = cam;
                        break;
                    }
                }
                if(id < 0 || id > MAX_CCTV-1 || !CCTVInfo[id][tvObjectOn]) return SendError(playerid, "Камера не найдена.");
                if(CCTVInfo[id][tvBreak]) {
                    SetPlayerGPS(playerid, CCTVInfo[id][tvPosX],CCTVInfo[id][tvPosY],CCTVInfo[id][tvPosZ], 3.0);
                    //Waypoint_Set(playerid, CCTVInfo[id][tvPosX],CCTVInfo[id][tvPosY],CCTVInfo[id][tvPosZ], 3.0);
                    return SendError(playerid, "Камера неисправна.");
                }

                format(command, sizeof(command), "show %i", id);
                callcmd::cctv(playerid, command);
            }
            return 1;
        }
    }

    for(new r = 0; r < 18; r++)
    {
        if(playertextid == MDC_TD_MENU[playerid][r])
        {
            if(MdcInfo[playerid][mdcPage] == PAGE_ROSTER)
            {
                new count = -1;
                for(new i = 0; i != MAX_PATROL; i++)
                {
                    if(!PatrolInfo[GetPatrolID(playerid)][i][patrulExists]) continue;

                    count++;
                    if(r == count) break;
                    if(i == MAX_PATROL-1) return 1;
                }

                if(count == -1) return 1;

                if(p_temp[playerid][pPatrol])
                {
                    callcmd::callsign(playerid, "/0");
                    return MDC_PAGE(playerid, PAGE_ROSTER);
                }

                new roster = MdcInfo[playerid][mdcList][count];
                if(roster > 18) return SendError(playerid, "Перезагрузите страницу.");

                if(PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] == INVALID_PLAYER_ID &&
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][1] == INVALID_PLAYER_ID)
                        return 1;
                if(PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] != INVALID_PLAYER_ID &&
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][1] != INVALID_PLAYER_ID)
                        return SendError(playerid, "Данный патруль уже скомплектован.");

                if(PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] == INVALID_PLAYER_ID) {
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] = playerid;
                } else {
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][1] = playerid;
                }
                p_temp[playerid][pPatrol] = roster+1;

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[DISP] %s %s присоединился к патрулю под маркировкой %s", GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][roster][patrulName]);
                SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

                MDC_PAGE(playerid, PAGE_ROSTER);
            }
            else if(MdcInfo[playerid][mdcPage] == PAGE_MEMBERS) {
                if(p_info[playerid][rang] < 8) return SendError(playerid, "Доступно с 8 ранга.");
                new targetid = MdcInfo[playerid][mdcList][r];
                if(!p_info[targetid][loggedIn] ||
                    p_info[targetid][member] != p_info[playerid][member]) return 1;
                if(p_info[targetid][fwork] == true)
                    MEMBERS_MAP(playerid, targetid);
            }
            return 1;
        }
    }

    if(playertextid == MDC_TD_LEFT_PANEL[playerid][1])
    {
        if(MdcInfo[playerid][mdcMenu] == PAGE_ROSTER) {
            if(p_temp[playerid][pPatrol])
            {
                callcmd::callsign(playerid, "/0");
                MDC_PAGE(playerid, PAGE_ROSTER);
            }
            else ShowPlayerDialog(playerid, D_MDC_ROSTER_CHANGE, DIALOG_STYLE_INPUT, ""I"Изменить позывной", ""W"Введите новый позывной:", "Принять", "Отмена");
        }
        else if(MdcInfo[playerid][mdcMenu] == PAGE_MEMBERS) {
            if(p_temp[playerid][StatusOnDuty] == 1) {
                p_temp[playerid][StatusOnDuty] = 2;
                foreach(new i: Player)
                {
                    if(p_info[i][loggedIn] == 1 && pSpectateId[i] == playerid) TogglePlayerSpectating(i, 0);
                }
            }
            else p_temp[playerid][StatusOnDuty] = 1;
            MDC_ShowMembersMenu(playerid);
        }
        return 1;
    }
    /*
    for(new apb = 0; apb < 5; apb++)
    {
        if(playertextid == MDC_APB_TD[playerid][2+4*apb]) // Детали
        {
            new
                mes[256],
                i_apb = MdcInfo[apb][mdcList]
            ;

            SetPVarInt(playerid, #MDC_ID, apb);

            format(mes, sizeof(mes),
            "{a9c4e4}#%i\n\n\
            {a9c4e4}Подозреваемый:{ffffff}\t %s\n\
            {a9c4e4}Описание:{ffffff}\t\t %s\n\n\
            {a9c4e4}Добавил:{ffffff}\t\t %s\n\
            {a9c4e4}Дата:{ffffff}\t\t\t %s\n",
            ApbInfo[i_apb][apbID]+90214,
            ApbInfo[i_apb][apbSuspect],
            ApbInfo[i_apb][apbCharge],
            ApbInfo[i_apb][apbOfficer],
            ApbInfo[i_apb][apbDate]);

            ShowPlayerDialog(playerid, D_MDC_APB_DETAIL, DIALOG_STYLE_MSGBOX, ""I"APB", mes, "Изменить", "Отмена");
        }
        else if(playertextid == MDC_APB_TD[playerid][3+4*apb]) // Удалить
        {
            SetPVarInt(playerid, #MDC_ID, MdcInfo[apb][mdcList]);
            ShowPlayerDialog(playerid, D_APB_DELETE, DIALOG_STYLE_MSGBOX, ""I"Подтверждение", ""W"Вы действительно хотите удалить APB?", "Да", "Нет");
        }
        else if(playertextid == MDC_CALLS_TD[playerid][2+4*apb]) // handle
        {
            new string[512], id = MdcInfo[apb][mdcList];

            if(p_temp[playerid][pPatrol])
            {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "* [%s] %s %s [%s] принял вызов в 911. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetPlayerFractionRangName(playerid), get_name(playerid), PatrolInfo[GetPatrolID(playerid)][p_temp[playerid][pPatrol]-1][patrulName], id+1);
                SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "* [%s] %s %s принял вызов в 911. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetPlayerFractionRangName(playerid), get_name(playerid), id+1);
                SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
            }

            Waypoint_Set(playerid, CallInfo[id][callPosX],CallInfo[id][callPosY],CallInfo[id][callPosZ], 3.0);

            CallInfo[id][callAccept]++;
            p_temp[playerid][pPoliceCalls]++;

            switch(CallInfo[id][callType])
            {
                case 1: format(string, sizeof(string), "SAPD");
                case 2: format(string, sizeof(string), "SAFD");
                case 3: format(string, sizeof(string), "SAPD, SAFD");
            }

            if(p_temp[playerid][pPatrol]) format(CallInfo[id][callAcceptBy], 64, "Handled by %s (%s)", get_name(playerid), PatrolInfo[GetPatrolID(playerid)][p_temp[playerid][pPatrol]-1][patrulName]);
            else                          format(CallInfo[id][callAcceptBy], 64, "Handled by %s", get_name(playerid));

            format(string, sizeof(string), "%s (Ph. %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s", CallInfo[id][callName], CallInfo[id][callPhone], string, CallInfo[id][callLocation], CallInfo[id][callText], (strlen(CallInfo[id][callText]) > 60)?(" .."):(""), CallInfo[id][callDate], CallInfo[id][callAcceptBy]);
            PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][apb*4+1], string);

            PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][apb*4 + 2]);
        }
        else if(playertextid == MDC_CALLS_TD[playerid][3+4*apb]) // details
        {
            new
                mes[512],
                id = MdcInfo[apb][mdcList]//, type = (PlayerInfo[playerid][pFaction] == LSFD)?(2):(1)
            ;

            new statusmes[65];
            if(CallInfo[id][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[id][callAcceptBy]);
            else format(statusmes, sizeof(statusmes), "{A9C4E4}Вызов не принят");

            format(mes, sizeof(mes), "{B4B5B7}911-ИНФОРМАЦИЯ О ЗВОНКЕ - #%i\n\n\
                                    Звонок от:\t\t%s\n\
                                    Номер телефона:\t%i\n\
                                    Ситуация:\t\t%s\n\
                                    Местоположение:\t%s\n\
                                    Дата:\t\t\t%s\n\n\
                                    Статус:\t\t\t%s\n\
                                    На вызов откликнулись %i раз(-а)",
            id+1, CallInfo[id][callName], CallInfo[id][callPhone], CallInfo[id][callText], CallInfo[id][callLocation], CallInfo[id][callDate], statusmes, CallInfo[id][callAccept]);

            ShowPlayerDialog(playerid, D_CALLS_LIST, DIALOG_STYLE_MSGBOX, ""I"MDC - Информация о звонке", mes, "Опции", "Назад");
            SetPVarInt(playerid, #last_call, id);
        }
    }
    */
    return 1;
}
