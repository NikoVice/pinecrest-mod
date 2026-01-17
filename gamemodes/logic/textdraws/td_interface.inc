Interface_Show(playerid, interface_id)
{
    switch(interface_id)
    {
        case SERVICE_TUNE_INDEX:
        {
            SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "Выбор_цвета"); // главная слот

            ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_components", "Внешний_вид");  // иконка 1 слота
            ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_external", "Компоненты"); // иконка 2 слота
            ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_innovationtun", "Аксессуары"); // иконка 3 слота
            ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_suspension", "Подвеска"); // иконка 4 слота

            ServiceTune_UpdateTD_Closed(playerid, 363.5689);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if((1 <= i <= 4) || i == 0 || i == 15) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(i == 0 || i == 5 || i == 6 || i == 8 || i == 9 || i == 10 || 15 <= i <= 17) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_EXTERNAL:
        {
            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_components", "Внешний_Вид");

            ServiceTune_UpdateTD_Closed(playerid, 363.5689);

            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главный слот

            new td_str[5];
            f(td_str, "%d/4", p_temp[playerid][InterfacePage]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][0], td_str); // номер страницы

            switch(p_temp[playerid][InterfacePage])
            {
                case 1:
                {
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_azot", "Закись_азота");  // иконка 1 слота
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_prostavki_stupicu", "Диски"); // иконка 2 слота
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_spoiler", "Спойлер"); // иконка 3 слота
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_peredniy_bampber", "Передний_бампер"); // иконка 4 слота
                }
                case 2:
                {
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_zadniy_bamper", "Задний бампер");  // иконка 1 слота
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_hydravlik", "Гидравлика"); // иконка 2 слота
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_hood", "Капот"); // иконка 3 слота
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_ventelation", "Венталиционные отверстия"); // иконка 4 слота
                }
                case 3:
                {
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_fara", "Подфарники");  // иконка 1 слота
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_exhaust", "Выхлопная труба"); // иконка 2 слота
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_car_roof", "Крыша"); // иконка 3 слота
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_porog", "Пороги"); // иконка 4 слота
                }
                case 4:
                {
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_icon_balon", "Покрасочные работы");
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_icon_balon", "Тонировка");
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_icon_balon", "Цвет фар");
                    PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][14], "_"); // 4й слот
                }
            }
            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if((1 <= i <= 6) || i == 0 || i == 12 || i == 13) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(i == 5 || i == 6 || i == 8 || i >= 15) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
            if(p_temp[playerid][InterfacePage] == 4)
            {
                PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][1]);
                TextDrawHideForPlayer(playerid, TD_ServiceTune[4]);
            }
        }
        case SERVICE_TUNE_COMPONENTS:
        {
            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_external", "Компоненты");

            ServiceTune_UpdateTD_Closed(playerid, 363.5689);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главный слот

            new td_str[24];
            f(td_str, "%d/3", p_temp[playerid][InterfacePage]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][0], td_str); // номер страницы

            new vehicleid = GetPlayerVehicleID(playerid);
            switch(p_temp[playerid][InterfacePage])
            {
                case 1:
                {
                    f(td_str, "Подвеска (%d/3)", veh_info[vehicleid][v_twinturbo_data][tt_suspension]);
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_suspension", td_str);  // иконка 1 слота

                    f(td_str, "Трансмиссия (%d/3)", veh_info[vehicleid][v_twinturbo_data][tt_transmission]);
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_transmisson", td_str); // иконка 2 слота

                    f(td_str, "Турбонаддув (%d/3)", veh_info[vehicleid][v_twinturbo_data][tt_turbocharging]);
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_turbo", td_str); // иконка 3 слота

                    f(td_str, "Двигатель (%d/3)", veh_info[vehicleid][v_twinturbo_data][tt_engine]);
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_engine", td_str); // иконка 4 слота
                }
                case 2:
                {
                    f(td_str, "Стартер (%.1f)", veh_info[vehicleid][v_details][0]);
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_starter", td_str);  // иконка 1 слота

                    f(td_str, "Аккумулятор (%.1f)", veh_info[vehicleid][v_details][1]);
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_acamulator", td_str); // иконка 2 слота

                    f(td_str, "Топливная (%.1f)", veh_info[vehicleid][v_details][2]);
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_fuelsystem", td_str); // иконка 3 слота

                    f(td_str, "Сцепление (%.1f)", veh_info[vehicleid][v_details][3]);
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_clutch", td_str); // иконка 4 слота
                }
                case 3:
                {
                    f(td_str, "Замена двигателя (%.1f)", veh_info[vehicleid][v_details][4]);
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_repairengine", td_str);  // иконка 1 слота
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_info", "Информация о деталях"); // иконка 2 слота

                    PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][13], "_"); // 3й слот
                    PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][14], "_"); // 4й слот
                }
            }
            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if((1 <= i <= 6) || i == 0 || i == 12 || i == 13) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(i == 5 || i == 6 || i == 8 || i >= 15) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
            if(p_temp[playerid][InterfacePage] == 3)
            {
                PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][2]);
                PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][1]);
                TextDrawHideForPlayer(playerid, TD_ServiceTune[3]);
                TextDrawHideForPlayer(playerid, TD_ServiceTune[4]);
            }
        }
        
        case SERVICE_TUNE_ACCESSORIES: // show
        { // главная
            HideTextDrawForPlayer(playerid, TD_ID_SERVICE_TUNE);
            ShowDialogTuneObject(playerid);
            /*
            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_innovationtun", "Аксессуары");

            ServiceTune_UpdateTD_Closed(playerid, 363.5689);

            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главный слот

            new td_str[5];
            f(td_str, "%d/2", p_temp[playerid][InterfacePage]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][0], td_str); // номер страницы

            switch(p_temp[playerid][InterfacePage])
            {
                case 1:
                {
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_carroof_accesories", "Объекты на крыше");  // иконка 1 слота
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_trunk_accesories", "Объекты на багажнике"); // иконка 2 слота
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_hood_acessories", "Объекты на капоте"); // иконка 3 слота
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_flag_acessories", "Декорация в виде флага"); // иконка 4 слота
                }
                case 2:
                {
                    ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_spoiler", "Спойлеры");  // иконка 1 слота
                    ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_peredniy_bampber", "Передний бампер"); // иконка 2 слота
                    ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_zadniy_bamper", "Задний бампер"); // иконка 3 слота
                    ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_neon_acessories", "Неоновая подсветка"); // иконка 4 слота
                }
            }
            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if((1 <= i <= 6) || i == 0 || i == 12 || i == 13) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(i == 5 || i == 6 || i == 8 || i >= 15) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
            */
        }
        
        case SERVICE_TUNE_SUSPENSION:
        {
            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_suspension", "Подвеска");

            ServiceTune_UpdateTD_Closed(playerid, 363.5689);

            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главный слот

            ServiceTune_UpdateTD_Item(playerid, 4, "flin_sto:flin_sto_wheel_height", "Настройка размера диска");  // иконка 1 слота
            ServiceTune_UpdateTD_Item(playerid, 3, "flin_sto:flin_sto_wheel_width", "Настройка ширины диска"); // иконка 2 слота
            ServiceTune_UpdateTD_Item(playerid, 2, "flin_sto:flin_sto_prostavki_stupicu", "Проставки на ступицу"); // иконка 3 слота
            ServiceTune_UpdateTD_Item(playerid, 1, "flin_sto:flin_sto_rozval_shozdenie", "Развал-схождение"); // иконка 4 слота

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if((1 <= i <= 4) || i == 0 || i == 12 || i == 13) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(i == 0 || i == 5 || i == 6 || i == 8 || i >= 15) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_EXTERNAL_VIEW:
        {
            new tune_id = p_temp[playerid][p_listitem][1],
                vehicleid = GetPlayerVehicleID(playerid),
                till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");
            if(p_temp[playerid][p_listitem][0] != vehicleid)
                return Service_Error(playerid, "ID транспорта не совпадает с первоначальным, воспользуйтесь услугами автосервиса повторно.");

            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главная слот
            for(new i = 11; i != 15; i++) PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][i], "_"); // 1й слот

            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_right", "flin_sto:flin_sto_left");
            ServiceTune_UpdateTD_TextCenter(playerid, 405.0394); //397.0751 for razval

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%d", GetPriceTuneElement(tune_id, p_temp[playerid][shop_id]) * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            GetVehicleComponentName(p_temp[playerid][e_tListComponents][p_temp[playerid][shop_id]], STRING_GLOBAL);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 8 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 6 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
            p_temp[playerid][tune_default] = true;
            //p_temp[playerid][tune_object] = false;
        }
        case SERVICE_TUNE_ACCESSORIES_VIEW:
        {
            new tune_id = p_temp[playerid][p_listitem][2],
                vehicleid = GetPlayerVehicleID(playerid),
                vehmodel = GetVehicleModelEx(vehicleid)-400;
            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");
            if(vehmodel < 0) return Service_Error(playerid, "Не определен ID автомобиля, воспользуйтесь услугами автосервиса повторно.");
            if(p_temp[playerid][p_listitem][3] != vehicleid)
                return Service_Error(playerid, "ID транспорта не совпадает с первоначальным, воспользуйтесь услугами автосервиса повторно.");

            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главная слот
            for(new i = 11; i != 15; i++) PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][i], "_"); // 1й слот

            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_right", "flin_sto:flin_sto_left");
            ServiceTune_UpdateTD_TextCenter(playerid, 405.0394); //397.0751 for razval

            p_temp[playerid][shop_id] = 0;
            STRING_GLOBAL[0] = EOS;
            if(veh_info[vehicleid][v_family_id] != -1) f(STRING_GLOBAL, "%d/%d FC", TuneObjData[vehmodel][tune_id][0][uPrice] * till, TuneObjData[vehmodel][tune_id][0][uPriceFamilyCoins]);
            else f(STRING_GLOBAL, "%d", TuneObjData[vehmodel][tune_id][0][uPrice] * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], TuneObjData[vehmodel][tune_id][0][uName]);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 8 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 6 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
            p_temp[playerid][tune_default] = false;
            //p_temp[playerid][tune_object] = true;
        }
        case SERVICE_TUNE_COLOR_SELECT:
        {
            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_icon_balon", "Выбор_цвета");
            ServiceTune_UpdateTD_Closed(playerid, 298.8573);

            new vehicleid = GetPlayerVehicleID(playerid);
            if(p_temp[playerid][InterfacePage] == 0)
            {
                p_temp[playerid][p_listitem_int] = 0;
                ChangeVehicleColor(vehicleid, ServiceTune_Colors[0][st_ID], veh_info[vehicleid][v_color][1]);
                SendInfo(playerid, "Выберите первый цвет автомобиля и нажмите 'Приобрести' для выборого доп. цвета.");
                ServiceTune_UpdateTD_Colors(playerid);

                for(new i = 19; i != -1; i--)
                {
                    if(i < 16)
                    {
                        if(i == 0 ||  i == 8 || 11 <= i <= 13) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                        else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                    }
                    if(0 <= i <= 6 || i == 8 || i >= 11) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                    else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
                }
            }
            if(p_temp[playerid][InterfacePage] == 1)
            {
                SendInfo(playerid, "Выберите второй цвет автомобиля и нажмите 'Приобрести' для покупки.");
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], "5000");

                for(new i = 19; i != -1; i--)
                {
                    if(i < 16)
                    {
                        if(i == 0 || 8 <= i <= 13) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                        else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                    }
                    if(0 <= i <= 6 || i >= 11) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                    else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
                }

            }
        }
        case SERVICE_TUNE_COLOR_LIGHTS:
        {
            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_icon_balon", "Цвет фар");
            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_plus", "flin_sto:flin_sto_minus");
            ServiceTune_UpdateTD_TextCenter(playerid, 397.0751);

            p_temp[playerid][p_listitem_int] = 0;
            p_temp[playerid][p_listitem][5] = 1;
            ServiceTune_UpdateTD_Colors(playerid);

            new vehicleid = GetPlayerVehicleID(playerid),
                slot_id = p_temp[playerid][p_listitem_int],
                coef = p_temp[playerid][p_listitem][5];

            f(STRING_GLOBAL, "Насыщенность~n~%d%", p_temp[playerid][p_listitem][5]*10);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            new color_r, color_g, color_b;
            GetBitColorRGB(ServiceTune_Colors[slot_id][st_Color], color_r, color_g, color_b);

            color_r = floatround(coef*0.1*color_r);
            color_g = floatround(coef*0.1*color_g);
            color_b = floatround(coef*0.1*color_b);

            SetVehicleLightsColors(vehicleid, color_r, color_g, color_b);
            SetVehicleParamsVEx(vehicleid, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);

            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

            f(STRING_GLOBAL, "%d", PRICE_TUNE_COLOR_LIGHTS * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 8 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 6 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_TONING:
        {
            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

            if(p_temp[playerid][InterfaceID] != interface_id)
                ServiceTune_UpdateTD_Header(playerid, "flin_sto:flin_sto_icon_balon", "Тонировка");
            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_plus", "flin_sto:flin_sto_minus");
            ServiceTune_UpdateTD_TextCenter(playerid, 397.0751);

            p_temp[playerid][p_listitem_int] = 1;

            new vehicleid = GetPlayerVehicleID(playerid),
                toner_id = p_temp[playerid][p_listitem_int];

            f(STRING_GLOBAL, "Тонировка~n~%d", toner_id);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            SetVehicleToner(vehicleid, toner_id);

            f(STRING_GLOBAL, "%d", PRICE_TUNE_COLOR_LIGHTS * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 8 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 6 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_WHEEL_SIZE:
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главная слот
            for(new i = 11; i != 15; i++) PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][i], "_"); // 1й слот

            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_plus", "flin_sto:flin_sto_minus");
            ServiceTune_UpdateTD_TextCenter(playerid, 397.0751);

            if(g_VehHandlingInfo[vehicleid][hpWheelSize] < 0.5) g_VehHandlingInfo[vehicleid][hpWheelSize] = 0.5;
            f(STRING_GLOBAL, "Размер колес~n~%.2f", g_VehHandlingInfo[vehicleid][hpWheelSize]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

            f(STRING_GLOBAL, "%d", PRICE_TUNE_WHEEL_SIZE * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 8 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 6 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_WHEEL_WIDTH:
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главная слот
            for(new i = 11; i != 15; i++) PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][i], "_"); // 1й слот

            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_plus", "flin_sto:flin_sto_minus");
            ServiceTune_UpdateTD_TextCenter(playerid, 397.0751);

            if(g_VehVisualsInfo[vehicleid][vcWheelWidth] < 100) g_VehVisualsInfo[vehicleid][vcWheelWidth] = 100;
            SetVehicleWheelWidth(vehicleid, g_VehVisualsInfo[vehicleid][vcWheelWidth]);

            f(STRING_GLOBAL, "Ширина колес~n~%d", g_VehVisualsInfo[vehicleid][vcWheelWidth]/25);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

            f(STRING_GLOBAL, "%d", PRICE_TUNE_WHEEL_WIDTH * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 8 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 6 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_WHEEL_OFFSET_X:
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главная слот
            for(new i = 11; i != 15; i++) PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][i], "_"); // 1й слот

            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_plus", "flin_sto:flin_sto_minus");
            ServiceTune_UpdateTD_TextCenter(playerid, 397.0751);

            p_temp[playerid][p_listitem_int] = 0;
            ServiceTune_UpdateTD_Axle(playerid);

            f(STRING_GLOBAL, "Проставка на~n~%d см", g_VehVisualsInfo[vehicleid][vcWheelOffsetX][0]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

            f(STRING_GLOBAL, "%d", PRICE_TUNE_WHEEL_OFFSET_X * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 7 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 4 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case SERVICE_TUNE_WHEEL_ANGLE:
        {
            new vehicleid = GetPlayerVehicleID(playerid);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][19], "_"); // главная слот
            for(new i = 11; i != 15; i++) PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][i], "_"); // 1й слот

            ServiceTune_UpdateTD_Closed(playerid, 298.8573);
            ServiceTune_UpdateTD_Arrows(playerid, "flin_sto:flin_sto_plus", "flin_sto:flin_sto_minus");
            ServiceTune_UpdateTD_TextCenter(playerid, 397.0751);

            p_temp[playerid][p_listitem_int] = 0;
            ServiceTune_UpdateTD_Axle(playerid);

            f(STRING_GLOBAL, "Развал-схождение~n~%d", g_VehVisualsInfo[vehicleid][vcWheelAlignment][0]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

            new till = Service_GetTill(playerid);
            if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

            f(STRING_GLOBAL, "%d", PRICE_TUNE_WHEEL_ANGLE * till);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][8], STRING_GLOBAL);

            for(new i = 19; i != -1; i--)
            {
                if(i < 16)
                {
                    if(i == 0 || 7 <= i <= 12 || i == 14) TextDrawShowForPlayer(playerid, TD_ServiceTune[i]);
                    else TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
                }
                if(0 <= i <= 4 || 9 <= i <= 14 || i >= 18) PlayerTextDrawHide(playerid, PTD_ServiceTune[playerid][i]);
                else PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][i]);
            }
        }
        case PLAYER_MENU_INDEX:
        {
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 0, "flin_menu:flin_menu_houseicon_1", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 1, "flin_menu:flin_menu_assistanceicon_2", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 2, "flin_menu:flin_menu_caricon_3", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 3, "flin_menu:flin_menu_orgranizationicon_4", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 4, "flin_menu:flin_menu_offericon_5", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 5, "flin_menu:flin_menu_familyicon_6", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 6, "flin_menu:flin_menu_inventoryicon_7", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 7, "flin_menu:flin_menu_animicon_8", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 8, "flin_menu:flin_menu_bindericon_9", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 9, "flin_menu:flin_menu_donaticon_10", "_");

            //for(new i = 9; i != -1; i--) PlayerMenu_UpdateTD_ItemBg(playerid, i, true);
            for(new i = 1; i != -1; i--) PlayerTextDrawShow(playerid, PTD_PlayerMenu[playerid][i]);
        }
        case PLAYER_MENU_TARGET:
        {
            new count;
            foreach(new i: PlayerPlayersStream[playerid])
            {
                if(count >= 10) break;
                if(IsPlayerStream(5.0, playerid, i) && GetPlayerState(i) != PLAYER_STATE_SPECTATING)
                {
                    p_temp[playerid][p_listitem][count] = i;
                    count++;
                }
            }
            if(!count) return SendError(playerid, "Рядом с Вами никого нет.");
            p_temp[playerid][p_listitem_int] = -1;
            for(new i = 9; i != -1; i--)
            {
                new targetid = p_temp[playerid][p_listitem][i];
                if(!IsPlayerConnected(targetid) || i >= count)
                {
                    p_temp[playerid][p_listitem][i] = -1;
                    PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON_AND_TEXT, i, "_", "_");
                    //PlayerMenu_UpdateTD_ItemBg(playerid, i, false);
                }
                else
                {
                    f(STRING_GLOBAL, "%s~n~(ID: %d)", GetSurnameNick(targetid), targetid);
                    PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON_AND_TEXT, i, "flin_menu:flin_menu_usericon", STRING_GLOBAL);
                    //PlayerMenu_UpdateTD_ItemBg(playerid, i, true);
                }
            }
        }
        case PLAYER_MENU_TARGET_ACTION:
        {
            new idx = p_temp[playerid][p_listitem_int];
            if(idx == -1 || p_temp[playerid][p_listitem][idx] == -1) return 1;
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 0, "flin_menu:flin_menu_handicon_1", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 1, "flin_menu:flin_menu_passicon_2", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 2, "flin_menu:flin_menu_tradeicon_3", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 3, "flin_menu:flin_menu_licicon_4", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 4, "flin_menu:flin_menu_givemoneyicon_5", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 5, "flin_menu:flin_menu_medicon_6", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 6, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 7, "flin_menu:flin_menu_carpassicon_8", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 8, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 9, "flin_menu:flin_menu_keyicon_10", "_");

            /*
            for(new i = 9; i != -1; i--)
            {
                if(i == 8 || i == 6) PlayerMenu_UpdateTD_ItemBg(playerid, i, false);
                else PlayerMenu_UpdateTD_ItemBg(playerid, i, true);
            }
            */
        }
        case PLAYER_MENU_PROPERTY:
        {
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 0, "flin_menu:flin_menu_housesicon_1", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 1, "flin_menu:flin_menu_bussinesicon_2", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 2, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 3, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 4, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 5, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 6, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 7, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 8, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 9, "_", "_");

            /*
            for(new i = 9; i != -1; i--)
            {
                if(i == 3 || i > 4) PlayerMenu_UpdateTD_ItemBg(playerid, i, false);
                else PlayerMenu_UpdateTD_ItemBg(playerid, i, true);
            }
            */
        }
        case PLAYER_MENU_VEHICLE:
        {
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 0, "flin_menu:flin_menu_motoicon_1", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 1, "flin_menu:flin_menu_bikeicon_2", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 2, "flin_menu:flin_menu_tsicon_3", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 3, "flin_menu:flin_menu_watericon_4", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 4, "flin_menu:flin_menu_planeicon_5", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 5, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 6, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 7, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 8, "_", "_");
            PlayerMenu_UpdateTD_Item(playerid, PLAYER_MENU_TYPE_ICON, 9, "_", "_");
        }
        case ROULETTE_INDEX:
        {
            ClearPlayerRouletteTextDraw(playerid);
            Roulette_Render(playerid);
            Roulette_UpdateTD_Info(playerid, RouletteType[playerid]);
            Roulette_UpdateTD_HeaderButton(playerid, RouletteType[playerid]);
            Roulette_UpdateTD_Items(playerid, RouletteType[playerid]);
        }
        case CASE_INDEX:
        {
            ClearPlayerTextDrawCase(playerid);
            Case_Render(playerid);
            Case_UpdateTD_Info(playerid, CaseType[playerid]);
            Case_UpdateTD_Items(playerid, CaseType[playerid]);
        }
        case PHONE_INDEX:
        {
            Phone_UpdateTD_Background(playerid);
            Phone_Render(playerid);
            Phone_UpdateTD_Info(playerid);
        }

        case EQUIPMENT_INVENTORY_PLAYER:
        {
            Equipment_InitPage(playerid);

            if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                SetPVarInt(playerid, #VEHICLEID_ACCESSORIES, GetPlayerVehicleID(playerid));
                new vehicleid = GetPlayerVehicleID(playerid);
                if(IsVehicleAccessories(playerid, vehicleid))
                {
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
                        "SELECT * FROM `inventory` WHERE `owner_id` = %d AND `owner_type` = %d AND `status_use` > 0 LIMIT 15",
                            veh_info[vehicleid][v_mysql_id], INVENTORY_OWNER_TYPE_VEHICLE);
                    mysql_tquery(con_bd, STRING_GLOBAL, "LoadInfoVehicleAccessories", "iii", playerid, p_info[playerid][ID], vehicleid);
                }
            }
            else Equipment_AccessoriesUse(playerid);

            Equipment_Info(playerid);
            Equipment_Right(playerid, interface_id);
        }

        case EQUIPMENT_TRADE..EQUIPMENT_TRADE_READY:
        {
            Equipment_InitPage(playerid);
            Equipment_TradeUpdate(playerid, interface_id);

            Equipment_Right(playerid, interface_id);
            Equipment_Left(playerid, interface_id);
        }
        case MARKET_SELL, MARKET_BUY, EQUIPMENT_INVENTORY_HOUSE, EQUIPMENT_INVENTORY_FAMILY, EQUIPMENT_INVENTORY_BOOT, EQUIPMENT_INVENTORY_TRASHBOX:
        {
            Equipment_InitPage(playerid);

            Equipment_Right(playerid, interface_id);
            STRING_GLOBAL[0] = EOS;

            if(interface_id == EQUIPMENT_INVENTORY_BOOT ||
                interface_id == EQUIPMENT_INVENTORY_HOUSE ||
                interface_id == EQUIPMENT_INVENTORY_TRASHBOX ||
                interface_id == EQUIPMENT_INVENTORY_FAMILY)
            {
                LoadOtherInventoryData(playerid, interface_id);
            }
            else
                Equipment_Left(playerid, interface_id);
        }
    }
    p_temp[playerid][InterfaceID] = interface_id;
    return 1;
}

stock Interface_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    // Equipment
    if(p_temp[playerid][TextDrawEquipment])
    {
        if(GetPVarInt(playerid, #EQ_CONTROL_BLOCK)) return 1;
        for(new i = 5; i != 0; i--)
        {
            if(playertextid == PTD_EquipmentMenu[playerid][i])
            {
                //SendDebug(playerid, "CLICK MENU");
                new slot_id = GetPVarInt(playerid, #EQ_SELECT_SLOT)-1, type_id = GetPVarInt(playerid, #EQ_SELECT_TYPE)-1;
                if(slot_id == -1 || type_id == -1) return SendError(playerid, "Вы ничего не выбрали.");
                if(p_temp[playerid][TextDrawInventory] && p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER)
                {
                    Equipment_DestroyMenu(playerid);
                    if(1 <= i <= 3)
                    {
                        if(type_id == INVENTORY_SELECT_TYPE_RIGHT || type_id == INVENTORY_SELECT_TYPE_USE_ACC)
                        {
                            if(type_id == INVENTORY_SELECT_TYPE_USE_ACC)
                                slot_id = Equipment_GetAccSlotUse(playerid, slot_id);
                            new typeID = ItemsInfo[InventoryPlayer[playerid][slot_id][inv_item_id]][iType];
                            switch(typeID)
                            {
                                case TYPE_ITEMS_INVENTORY, TYPE_ITEMS_ACCESSORIES, TYPE_ITEMS_SKINS, TYPE_ITEMS_VEHICLE_TUNE:
                                {
                                    if(i == 1) UsePlayerEquipment(playerid, slot_id);
                                    if(i == 2) ShowPlayerEquipmentInfo(playerid, slot_id);
                                    if(i == 3) {
                                        if(typeID != TYPE_ITEMS_INVENTORY)
                                        {
                                            Equipment_ClearSelectInfo(playerid);
                                            return 1;
                                        }
                                        if(InventoryPlayer[playerid][slot_id][inv_amount] < 2) SendError(playerid, "Нужно в большом количестве для разделения.");
                                        else
                                        {
                                            SetPVarInt(playerid, #EQ_CONTROL_BLOCK, true);
                                            ShowPlayerDialog(playerid, D_EQUIPMENT_DIVIDE, DIALOG_STYLE_INPUT, ""I"Разделить", ""W"Введите количество для разделения:", "Да", "Нет");
                                            return 1;
                                        }
                                    }
                                }
                                default:
                                {
                                    Equipment_ClearSelectInfo(playerid);
                                    return SendError(playerid, "Тип предмета не определен.");
                                }
                            }
                            if(i == 1) Equipment_Update(playerid);
                        }
                    }
                    Equipment_ClearSelectInfo(playerid);
                }
                if(p_temp[playerid][TextDrawTrade])
                {
                    if(type_id == INVENTORY_SELECT_TYPE_RIGHT)
                        Equipment_TradeItemRight(playerid, p_temp[playerid][InterfaceID], slot_id, i);
                    if(type_id == INVENTORY_SELECT_TYPE_LEFT)
                    {
                        if(p_temp[playerid][InterfaceID] == EQUIPMENT_TRADE_READY && i == 1) i = 2;
                        if(i == 1)
                        {
                            ExchangeUnBet(playerid, slot_id);
                            if(slot_id < MAX_EXCHANGE-1)
                            {
                                for(new i = slot_id; i < MAX_EXCHANGE-1; i++)
                                {
                                    gExchange[playerid][i][xType] = gExchange[playerid][i+1][xType];
                                    gExchange[playerid][i][xItemID] = gExchange[playerid][i+1][xItemID];
                                    gExchange[playerid][i][xValue] = gExchange[playerid][i+1][xValue];

                                    if(gExchange[playerid][i][xType] == BET_CAR)
                                    {
                                        format(gExchange[playerid][i][xNumber], 16, gExchange[playerid][i+1][xNumber]);
                                        gExchange[playerid][i][xTwinTurbo] = gExchange[playerid][i+1][xTwinTurbo];
                                    }
                                    if(gExchange[playerid][i][xType] == BET_ACCESSORIES)
                                    {
                                        gExchange[playerid][i][xWear] = gExchange[playerid][i+1][xWear];
                                        gExchange[playerid][i][xMaterialColor][0] = gExchange[playerid][i+1][xMaterialColor][0];
                                        gExchange[playerid][i][xMaterialColor][1] = gExchange[playerid][i+1][xMaterialColor][1];
                                    }
                                    if(gExchange[playerid][i][xType] == INVALID_EXCHANGE) break;
                                }
                                if(gExchange[playerid][MAX_EXCHANGE-1][xType] != INVALID_EXCHANGE)
                                    ExchangeUnBet(playerid, MAX_EXCHANGE-1);
                            }
                            Equipment_TradeLeft(playerid, p_temp[playerid][InterfaceID]);
                        }
                        else if(i == 2) Equipment_TradeItemInfo(playerid, playerid, slot_id);
                    }
                    Equipment_DestroyMenu(playerid);
                    if(i != 2 && (p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_BET_INVENTORY && type_id != INVENTORY_SELECT_TYPE_RIGHT)) Equipment_ClearSelectInfo(playerid);
                }
                if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_HOUSE ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX ||
                    p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY)
                {
                    if(type_id == INVENTORY_SELECT_TYPE_RIGHT)
                    {
                        if(i == 1)
                        {
                            new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                                dialog_style = DIALOG_STYLE_MSGBOX;
                            
                            if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY && !IsAllowedFamilyItem(itemID))
                                return SendError(playerid, "Этот предмет запрещено хранить на семейном складе.");
                            
                            switch(ItemsInfo[itemID][iType])
                            {
                                case TYPE_ITEMS_INVENTORY:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите кол-во \"%s\" которое хотите положить:", ItemsInfo[itemID][iName]);
                                    dialog_style = DIALOG_STYLE_INPUT;
                                }
                                case TYPE_ITEMS_ACCESSORIES:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Подтвердите что Вы хотите положить \"%s\" [%.1f] (%s/%s), Premium: %s?",
                                        ItemsInfo[itemID][iName],
                                        InventoryPlayer[playerid][slot_id][inv_acc_wear],
                                        AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acName],
                                        AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acName],
                                        InventoryPlayer[playerid][slot_id][inv_acc_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
                                }
                                case TYPE_ITEMS_SKINS:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Подтвердите что Вы хотите положить \"%s\" [%.1f], Premium: %s?",
                                    ItemsInfo[itemID][iName],
                                    InventoryPlayer[playerid][slot_id][inv_skin_wear],
                                    InventoryPlayer[playerid][slot_id][inv_skin_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
                                }
                                case TYPE_ITEMS_VEHICLE_TUNE:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Подтвердите что Вы хотите положить \"%s\"?", ItemsInfo[itemID][iName]);
                                }
                            }
                            SetPVarInt(playerid, #EQ_CONTROL_BLOCK, true);
                            ShowPlayerDialog(playerid, D_EQUIPMENT_PUT, dialog_style, ""I"Положить товар", STRING_GLOBAL, "Далее", "Отмена");
                        }
                        else if(i == 2)
                        {
                            Equipment_ClearSelectInfo(playerid);
                            ShowPlayerEquipmentInfo(playerid, slot_id);
                        }
                    }
                    else if(type_id == INVENTORY_SELECT_TYPE_LEFT)
                    {
                        new max_slot, min_slot;
                        GetSlotInfoInventory(playerid, p_temp[playerid][InterfaceID], max_slot, min_slot);
                        if(min_slot >= max_slot) return SendError(playerid, "Произошла не известная ошибка 200223.");
                        slot_id += min_slot+1;
                        if(i == 1)
                        {
                            new itemID = InventoryPlayer[playerid][slot_id][inv_item_id],
                                dialog_style = DIALOG_STYLE_MSGBOX;
                            if(itemID == 0)
                                return SendError(playerid, "Предмет не определен.");

                            if(SRV_ID && p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX &&
                                InventoryPlayer[playerid][slot_id][inv_freeze_time] > timestamp)
                                    return SendError(playerid, "Данный предмет недавно выброшен и будет заблокирован еще %s.", ConvertTime(InventoryPlayer[playerid][slot_id][inv_freeze_time]-timestamp));

                            if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY && !IsAllowedFamilyItem(itemID))
                                return SendError(playerid, "Этот предмет запрещено хранить на семейном складе.");

                            STRING_GLOBAL[0] = EOS;
                            switch(ItemsInfo[itemID][iType])
                            {
                                case TYPE_ITEMS_INVENTORY:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите кол-во \"%s\" которое хотите взять:", ItemsInfo[itemID][iName]);
                                    dialog_style = DIALOG_STYLE_INPUT;
                                }
                                case TYPE_ITEMS_ACCESSORIES:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Подтвердите что Вы хотите взять \"%s\" [%.1f] (%s/%s), Premium: %s?",
                                        ItemsInfo[itemID][iName],
                                        InventoryPlayer[playerid][slot_id][inv_acc_wear],
                                        AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][0]][acName],
                                        AccessoriesColorInfo[InventoryPlayer[playerid][slot_id][inv_acc_mt][1]][acName],
                                        InventoryPlayer[playerid][slot_id][inv_acc_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
                                }
                                case TYPE_ITEMS_SKINS:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Подтвердите что Вы хотите взять \"%s\" [%.1f], Premium: %s?",
                                    ItemsInfo[itemID][iName],
                                    InventoryPlayer[playerid][slot_id][inv_skin_wear],
                                    InventoryPlayer[playerid][slot_id][inv_skin_premium] == 0 ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
                                }
                                case TYPE_ITEMS_VEHICLE_TUNE:
                                {
                                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Подтвердите что Вы хотите взять \"%s\"?", ItemsInfo[itemID][iName]);
                                }
                            }
                            SetPVarInt(playerid, #EQ_CONTROL_BLOCK, true);
                            ShowPlayerDialog(playerid, D_EQUIPMENT_TAKE, dialog_style, ""I"Взять товар", STRING_GLOBAL, "Далее", "Отмена");
                        }
                        else if(i == 2)
                        {
                            Equipment_ClearSelectInfo(playerid);
                            ShowPlayerEquipmentInfo(playerid, slot_id);
                        }
                    }
                    Equipment_DestroyMenu(playerid);
                }
                return 1;
            }
        }
        for(new i = 24; i != 4; i--)
        {
            if(playertextid == PTD_EquipmentRight[playerid][i])
            {
                //SendDebug(playerid, "CLICK ITEMS");
                Equipment_SelectBox(playerid, INVENTORY_SELECT_TYPE_RIGHT, i-5);
                return 1;
            }
        }
        if(p_temp[playerid][TextDrawTrade] || p_temp[playerid][TextDrawMarket] ||
            p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_HOUSE ||
            p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT ||
            p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX ||
            p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY)
        {
            for(new i = 24; i != 4; i--)
            {
                if(playertextid == PTD_EquipmentLeft[playerid][i])
                {
                    Equipment_SelectBox(playerid, INVENTORY_SELECT_TYPE_LEFT, i-5);
                    return 1;
                }
            }
        }
        if(playertextid == PTD_EquipmentLeft[playerid][47]) // Left <<;
        {
            if(p_temp[playerid][TextDrawTrade] || (p_temp[playerid][TextDrawInventory] && p_temp[playerid][InterfaceID] != EQUIPMENT_INVENTORY_TRASHBOX))
                return 1;

            if(p_temp[playerid][inv_list_page][1] <= 1)
                return SendError(playerid, "Вы находитесь на первой странице.");

            p_temp[playerid][inv_list_page][1]--;
            Equipment_Update(playerid);
        }
        else if(playertextid == PTD_EquipmentLeft[playerid][48]) // Left >>;
        {
            if(p_temp[playerid][TextDrawTrade] || (p_temp[playerid][TextDrawInventory] && p_temp[playerid][InterfaceID] != EQUIPMENT_INVENTORY_TRASHBOX))
                return 1;

            new max_pages;
            if(p_temp[playerid][TextDrawMarket])
                max_pages = floatround(float(MAX_PLAYER_EQUIPMENT)/20, floatround_ceil);

            if(p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX)
                max_pages = floatround(float(MAX_ALL_EQUIPMENT-MAX_PLAYER_EQUIPMENT)/20, floatround_ceil);

            if(p_temp[playerid][inv_list_page][1] >= max_pages)
                return SendError(playerid, "Вы находитесь на последней странице или ничего нет.");

            p_temp[playerid][inv_list_page][1]++;
            Equipment_Update(playerid);
        }
        else if(playertextid == PTD_EquipmentRight[playerid][47]) // Right <<;
        {
            if(p_temp[playerid][TextDrawTrade] && (p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_BET_CAR &&
                p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_BET_INVENTORY)) return 1;

            if(p_temp[playerid][inv_list_page][0] <= 1)
                return SendError(playerid, "Вы находитесь на первой странице.");

            p_temp[playerid][inv_list_page][0]--;
            Equipment_Update(playerid);
            return 1;
        }
        else if(playertextid == PTD_EquipmentRight[playerid][48]) // Right >>;
        {
            if(p_temp[playerid][TextDrawTrade] && (p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_BET_CAR &&
                p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_BET_INVENTORY)) return 1;

            new max_pages;
            if(p_temp[playerid][TextDrawInventory] ||
                p_temp[playerid][TextDrawMarket] ||
                (p_temp[playerid][TextDrawTrade] && p_temp[playerid][InterfaceID] == EQUIPMENT_TRADE_BET_INVENTORY))
                max_pages = floatround(float(p_info[playerid][inv_slots])/20, floatround_ceil);

            if(p_temp[playerid][InterfaceID] != EQUIPMENT_TRADE_BET_CAR)
            {
                if(p_temp[playerid][inv_list_page][0] >= max_pages)
                    return SendError(playerid, "Вы находитесь на последней странице или ничего нет.");
            }

            p_temp[playerid][inv_list_page][0]++;
            Equipment_Update(playerid);
            return 1;
        }
        else if(playertextid == PTD_EquipmentRight[playerid][52]) // Settings;
        {
            if(p_temp[playerid][InterfaceID] != EQUIPMENT_INVENTORY_PLAYER) return 1;
            SendInfo(playerid, "В разработке.");
            return 1;
        }
        else if(playertextid == PTD_EquipmentLeft[playerid][52])
        {
            if(p_temp[playerid][TextDrawTrade])
            {
                if(p_temp[playerid][InterfaceID] == EQUIPMENT_TRADE_READY)
                {
                    ShowPlayerDialog(playerid, D_EXCHANGE_READY, DIALOG_STYLE_MSGBOX, "ОСТАНОВИСЬ, ПОЧИТАЙ, ПОЖАЛУЙСТА!!!", ""W"Вы действительно хотите начать процесс обмена вкладами?\n\n\
                        "W"УВАЖАЕМЫЙ ИГРОК!\n\n\
                        ВНИМАТЕЛЬНО ПРОВЕРЯЙТЕ СОДЕРЖИМОЕ ОБМЕНА, В ОТОБРАЖЕНИИ ПРЕДМЕТОВ НЕТ НЕДОРАБОТОК И СИСТЕМА РАБОТАЕТ КОРРЕКТНО,\n\
                        ЕСЛИ КАКАЙ-ТО ПРЕДМЕТ СОДЕРЖИМОГО НЕ ОТОБРАЖАЕТСЯ - ПРОВЕРЬТЕ  ВЫБРАВ ПРЕДМЕТ ЕГО КЛИКНУВ ПО ЯЧЕЙКЕ ПРЕДМЕТА ПОТОМ КНОПКУ "I"INFO "W"(В меню которое появится).\n\n\
                        НАЖИМАЯ "A"\"ПОДТВЕРДИТЬ ОБМЕН\", {"#cLIGHTRED"}ВЫ СОГЛАШАЕТЕСЬ С ТЕМ, ЧТО ОЗНАКОМЛЕНЫ С ДАННЫМ ПРЕДУПРЕЖДЕНИЕМ И ОБМЕН НЕ ОСПАРИВАЕТСЯ НИ В КОЕМ СЛУЧАЕ!!!", "Далее", "Отмена");
                }
                else callcmd::ready(playerid, "/0");
            }
            return 1;
        }
        else if(playertextid == PTD_EquipmentRight[playerid][54]) // Exit;
        {
            if(p_temp[playerid][TextDrawInventory] && p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER) HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
            if(p_temp[playerid][TextDrawTrade]) callcmd::stopex(playerid, "/0");
            if(p_temp[playerid][TextDrawMarket]) HideTextDrawForPlayer(playerid, TD_ID_MARKET);
            if(p_temp[playerid][TextDrawEquipment] &&
                (p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_BOOT ||
                p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_HOUSE ||
                p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_TRASHBOX ||
                p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_FAMILY))
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
        }
        if(p_temp[playerid][TextDrawInventory] && p_temp[playerid][InterfaceID] == EQUIPMENT_INVENTORY_PLAYER)
        {
            for(new i = 14; i != 4; i--)
            {
                if(playertextid == PTD_EquipmentPersonInfo[playerid][i])
                {
                    Equipment_SelectBox(playerid, INVENTORY_SELECT_TYPE_USE_ACC, i-5);
                    return 1;
                }
            }
            if(playertextid == PTD_EquipmentPersonInfo[playerid][18]) // MENU;
            {
                callcmd::menu(playerid, "/0");
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
            }
            else if(playertextid == PTD_EquipmentPersonInfo[playerid][19]) // GPS;
            {
                callcmd::gps(playerid, "/0");
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
            }
            else if(playertextid == PTD_EquipmentPersonInfo[playerid][20]) // CARS;
            {
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
                callcmd::cars(playerid, "/0");
            }
            else if(playertextid == PTD_EquipmentPersonInfo[playerid][21]) // PHONE;
            {
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
                if(p_info[playerid][active_phone_id] == 0 || !GetInventoryAmount(playerid, p_info[playerid][active_phone_id]))
                {
                    STRING_GLOBAL = "[#] Название\tНаличие\tАктивность\n", STRING_MIN[0] = EOS;
                    for(new i = 674; i < 679; i++)
                    {
                        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%s\n", i-673, ItemsInfo[i][iName], GetInventoryAmount(playerid, i) == 1 ? "{"#cGREEN"}Есть"W"" : "{"#cLIGHTRED"}Нет"W"", p_info[playerid][active_phone_id] == i ? "{"#cGREEN"}Да"W"" : "{"#cLIGHTRED"}Нет"W"");
                        strcat(STRING_GLOBAL, STRING_MIN);
                    }
                    ShowPlayerDialog(playerid, D_PHONE_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Телефоны", STRING_GLOBAL, "Далее", "Отмена");
                }
                else SetTimerEx("ShowPlayerPhone", 500, false, "dd", playerid, p_info[playerid][active_phone_id]);

            }
            else if(playertextid == PTD_EquipmentPersonInfo[playerid][22]) // DONATE;
            {
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
                callcmd::donate(playerid, "/0");
            }
            else if(playertextid == PTD_EquipmentPersonInfo[playerid][23]) // FAMILY;
            {
                HideTextDrawForPlayer(playerid, TD_ID_INVENTORY_PLAYER);
                callcmd::family(playerid, "/0");
            }
        }
        return 1;
    }
    // Phone
    if(playertextid == PTD_Phone[playerid][1]) // Звонок;
    {
        if(p_temp[playerid][offphone] == true) return SendError(playerid, "У Вас выключен телефон, включите его.");
        ShowPlayerDialog(playerid, D_PHONE_CALL, DIALOG_STYLE_INPUT, ""I"Позвонить", ""W"\
        Введите номер гос. службы:\n\n\
        Полиция - "I"10"W"\n\
        Скорая помощь - "I"11"W"\n\
        Такси - "I"12"W"\n\
        Автомеханик - "I"13"W"\n\
        Радиоцентр [LS] - "I"14"W"\n\
        Радиоцентр [SF] - "I"15"W"\n\
        Радиоцентр [LV] - "I"16"W"\n\
        Мобильный банк - "I"17"W"\n\
        Баланс телефона - "I"18", "Далее", "Отмена");
        return 1;
    }
    else if(playertextid == PTD_Phone[playerid][3]) // Сообщения;
    {
        if(p_temp[playerid][offphone] == true) return SendError(playerid, "У Вас выключен телефон, включите его.");
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT t.`NickPlayer`, t.`NickTarget`, t.`Text`, t.`Read`, t.`Time` FROM `phone_messages` AS t JOIN (SELECT `NickPlayer`, `Text`, max(`Time`) as `mtime` FROM `phone_messages` WHERE `NickTarget` = '%s' GROUP BY `NickPlayer`, `NickTarget`, `Text`, `Read`, `Time`) as t1 ON t.NickPlayer= t1.NickPlayer AND t.`Time` = t1.`mtime` ORDER BY t.`Time` DESC LIMIT 20",
        get_name(playerid));
        mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayerMessages", "d", playerid);
        return 1;
    }
    else if(playertextid == PTD_Phone[playerid][2]) // Контакты;
    {
        if(p_temp[playerid][offphone] == true) return SendError(playerid, "У Вас выключен телефон, включите его.");
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `phone_contacts`.`NickTarget`, `phone_contacts`.`MissedCalls`, `accounts`.`phone_number`, `accounts`.`online`, `phone_contacts`.`BlackList` FROM `phone_contacts`, `accounts` WHERE `phone_contacts`.`NickPlayer` = '%s' AND `accounts`.`name` = `phone_contacts`.`NickTarget` ORDER BY `phone_contacts`.`BlackList` DESC LIMIT 20",
        get_name(playerid));
        mysql_tquery(con_bd, STRING_GLOBAL, "MysqlShowContacts", "d", playerid);
        return 1;
    }
    else if(playertextid == PTD_Phone[playerid][4]) // Настройки;
    {
        STRING_MIN[0] = EOS;
        format(STRING_MIN, sizeof(STRING_MIN), "\
        "I"[1]"W" %s телефон\n\
        "I"[2]"W" Убрать телефон", p_temp[playerid][offphone] ? "{"#cGREEN"}Включить"W"" : "{"#cLIGHTRED"}Выключить"W"");
        ShowPlayerDialog(playerid, D_PHONE_SETTINGS, DIALOG_STYLE_LIST, ""I"Настройки", STRING_MIN, "Далее", "Отмена");
        return 1;
    }
    // Case
    if(playertextid == PTD_Case[playerid][5]) // BACK;
    {
        if(CaseTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете изменить тип кейсов, в данный момент запущено открытие кейсов.");
        if(CaseType[playerid] <= 0) return SendError(playerid, "Вы находитесь на первом типе кейсов.");
        CaseType[playerid]--;
        Case_UpdateTD_Items(playerid, CaseType[playerid]);
        Case_UpdateTD_Info(playerid, CaseType[playerid]);
        return 1;
    }
    else if(playertextid == PTD_Case[playerid][4]) // NEXT;
    {
        if(CaseTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете изменить тип кейсов, в данный момент запущено открытие кейсов.");
        if(CaseType[playerid] >= MAX_CASE - 1) return SendError(playerid, "Вы находитесь на последнем типе кейсов.");
        CaseType[playerid]++;
        Case_UpdateTD_Items(playerid, CaseType[playerid]);
        Case_UpdateTD_Info(playerid, CaseType[playerid]);
        return 1;
    }
    else if(playertextid == PTD_Case[playerid][7]) // BUY;
    {
        new type = CaseType[playerid];

        STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"%s кейс", Case[type][CaseNameOne]);
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
        Введите желаемое кол-во %s кейсов для приобретения:\n\n\
        Стоимость 1 %s кейса: {"#cGREEN"}%d"W" Flin Money", Case[type][CaseNameTwo], Case[type][CaseNameThree], Case[type][CasePrice]);
        ShowPlayerDialog(playerid, D_CASE_BUY, DIALOG_STYLE_INPUT, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
        return 1;
    }
    else if(playertextid == PTD_Case[playerid][1]) // START;
    {
        StartPlayerCase(playerid);
        return 1;
    }
    else if(playertextid == PTD_Case[playerid][9]) // EXIT;
    {
        ShowPlayerDialog(playerid, D_CASE_EXIT, DIALOG_STYLE_MSGBOX, ""I"Выход", ""W"Вы действительно желаете выйти из открытия кейсов?\n\n{"#cLIGHTRED"}Обратите внимание! Если у Вас запущено открытие кейса, то он Вам не вернется.", "Да", "Нет");
        return 1;
    }
    // Roulette
    if(playertextid == PTD_Roulette[playerid][7]) // BRONZE;
    {
        if(RouletteTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете изменить тип рулетки, в данный момент она запущена.");
        if(RouletteType[playerid] == 0) return SendError(playerid, "У Вас уже выбрана BRONZE рулетка.");
        RouletteType[playerid] = 0;
        Roulette_UpdateTD_Items(playerid, RouletteType[playerid]);
        Roulette_UpdateTD_Info(playerid, RouletteType[playerid]);
        Roulette_UpdateTD_HeaderButton(playerid, RouletteType[playerid]);
        return 1;
    }
    else if(playertextid == PTD_Roulette[playerid][8]) // SILVER;
    {
        if(RouletteTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете изменить тип рулетки, в данный момент она запущена.");
        if(RouletteType[playerid] == 1) return SendError(playerid, "У Вас уже выбрана SILVER рулетка.");
        RouletteType[playerid] = 1;
        Roulette_UpdateTD_Items(playerid, RouletteType[playerid]);
        Roulette_UpdateTD_Info(playerid, RouletteType[playerid]);
        Roulette_UpdateTD_HeaderButton(playerid, RouletteType[playerid]);
        return 1;
    }
    else if(playertextid == PTD_Roulette[playerid][9]) // GOLD;
    {
        if(RouletteTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете изменить тип рулетки, в данный момент она запущена.");
        if(RouletteType[playerid] == 2) return SendError(playerid, "У Вас уже выбрана GOLD рулетка.");
        RouletteType[playerid] = 2;
        Roulette_UpdateTD_Items(playerid, RouletteType[playerid]);
        Roulette_UpdateTD_Info(playerid, RouletteType[playerid]);
        Roulette_UpdateTD_HeaderButton(playerid, RouletteType[playerid]);
        return 1;
    }
    else if(playertextid == PTD_Roulette[playerid][3]) // UPDATE;
    {
        if(RouletteTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете обновить призы в рулетке, в данный момент она запущена.");
        if(RouletteType[playerid] < 0 || RouletteType[playerid] > 2) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента."), HidePlayerRoulette(playerid);
        new type = RouletteType[playerid];
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
        Вы действительно желаете обновить призы в "I"%s"W" рулетке.\n\n\
        Стоимость обновления призов: "I"%d Flin Money", RouletteNameType[type], RoulettePriceUpdate[type]);
        ShowPlayerDialog(playerid, D_ROULETTE_UPDATE, DIALOG_STYLE_MSGBOX, ""I"Обновление призов", STRING_GLOBAL, "Да", "Нет");
        return 1;
    }
    else if(playertextid == PTD_Roulette[playerid][2]) // START;
    {
        StartPlayerRoulette(playerid);
        return 1;
    }
    else if(playertextid == PTD_Roulette[playerid][6]) // EXIT;
    {
        ShowPlayerDialog(playerid, D_ROULETTE_EXIT, DIALOG_STYLE_MSGBOX, ""I"Выход", ""W"Вы действительно желаете выйти из рулетки?\n\n{"#cLIGHTRED"}Обратите внимание! Если у Вас запущена рулетка, то она Вам не вернется.", "Да", "Нет");
        return 1;
    }
    // player menu
    for(new i = 21; i != 1; i--)
    {
        if(playertextid == PTD_PlayerMenu[playerid][i])
        {
            switch(p_temp[playerid][InterfaceID])
            {
                case PLAYER_MENU_INDEX:
                {
                    switch(i)
                    {
                        case 2: Interface_Show(playerid, PLAYER_MENU_PROPERTY);
                        case 3: Interface_Show(playerid, PLAYER_MENU_TARGET);
                        case 4: Interface_Show(playerid, PLAYER_MENU_VEHICLE);
                        case 5: callcmd::fraction(playerid, "/0");
                        case 6: callcmd::offer(playerid, "/0");
                        case 7: callcmd::family(playerid, "/0");
                        case 8: SetTimerEx("ShowInventory", 500, false, "d", playerid);
                        case 9: callcmd::anim(playerid, "/0");
                        case 10: callcmd::bind(playerid, "/0");
                        case 11: callcmd::donate(playerid, "/0");
                        default: return 1;
                    }
                    if(i > 4) HideTextDrawForPlayer(playerid, TD_ID_PLAYER_MENU);
                    return 1;
                }
                case PLAYER_MENU_TARGET:
                {
                    if(i < 12) return SendError(playerid, "Произошла не известная ошибка, сообщите на форум в раздел багов.");
                    p_temp[playerid][p_listitem_int] = i-12;
                    Interface_Show(playerid, PLAYER_MENU_TARGET_ACTION);
                    return 1;
                }
                case PLAYER_MENU_TARGET_ACTION:
                {
                    new targetid = p_temp[playerid][p_listitem][p_temp[playerid][p_listitem_int]];
                    if(!IsPlayerConnected(targetid))
                    {
                        Interface_Show(playerid, PLAYER_MENU_INDEX);
                        return SendError(playerid, "Игрок не в сети.");
                    }
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "%d", targetid);
                    switch(i)
                    {
                        case 2: callcmd::hi(playerid, STRING_GLOBAL);
                        case 3: callcmd::pass(playerid, STRING_GLOBAL);
                        case 4: callcmd::trade(playerid, STRING_GLOBAL);
                        case 5: callcmd::license(playerid, STRING_GLOBAL);
                        case 6: ShowPlayerDialog(playerid, D_PLAYER_MENU_TD_PAY, DIALOG_STYLE_INPUT, ""I"Сколько передать?", ""W"Введите сумму для передачи денег.", "Принять", "Отмена");//callcmd::pay(playerid, STRING_GLOBAL);
                        case 7: callcmd::medcard(playerid, STRING_GLOBAL);
                        case 8: return 1;
                        case 9: callcmd::carpass(playerid, STRING_GLOBAL);
                        case 10: return 1;
                        case 11: callcmd::key(playerid, STRING_GLOBAL);
                        default: return 1;
                    }
                    HideTextDrawForPlayer(playerid, TD_ID_PLAYER_MENU);
                    return 1;
                }
                case PLAYER_MENU_PROPERTY:
                {
                    switch(i)
                    {
                        case 2: callcmd::house(playerid, "/0");
                        case 3: callcmd::bizmenu(playerid, "/0");
                        default: return 1;
                    }
                    HideTextDrawForPlayer(playerid, TD_ID_PLAYER_MENU);
                    return 1;
                }
                case PLAYER_MENU_VEHICLE:
                {
                    new id_type = -1;
                    switch(i)
                    {
                        case 2: id_type = 1; // мото
                        case 3: id_type = 0; // велик
                        case 4..6: id_type = i-2;
                    }
                    if(id_type == -1) return 1;
                    STRING_GLOBAL[0] = EOS;
                    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `v_model`, `v_mysql_id`, `v_twinturbo`, `v_premium`, `v_number`, `v_bonus`, `v_sell_block` FROM `vehicle` WHERE `v_owner_id` = %d", p_info[playerid][ID]);
                    mysql_tquery(con_bd, STRING_GLOBAL, "list_player_vehicle","iii", playerid, id_type, 0);
                    HideTextDrawForPlayer(playerid, TD_ID_PLAYER_MENU);
                }
            }
        }
    }
    if(playertextid == PTD_PlayerMenu[playerid][1]) HideTextDrawForPlayer(playerid, TD_ID_PLAYER_MENU);
    //service tune
    if(playertextid == PTD_ServiceTune[playerid][7]) // Закрыть
    {
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_EXTERNAL_VIEW, SERVICE_TUNE_ACCESSORIES_VIEW, SERVICE_TUNE_TONING:
            {
                button_cancelbuy(playerid);
                return 1;
            }
            case SERVICE_TUNE_COLOR_SELECT, SERVICE_TUNE_COLOR_LIGHTS:
            {
                ServiceTune_HideTD_Colors(playerid);
                if(p_temp[playerid][InterfaceID] == SERVICE_TUNE_COLOR_SELECT)
                {
                    new vehicleid = GetPlayerVehicleID(playerid);
                    ChangeVehicleColor(vehicleid, veh_info[vehicleid][v_color][0], veh_info[vehicleid][v_color][1]);
                }
                Service_Exit(playerid);
                return 1;
            }
            default:
            {
                SetCameraBehindPlayer(playerid);
                Service_Exit(playerid);
                return 1;
            }
        }
    }
    if(playertextid == PTD_ServiceTune[playerid][16]) // <</+
    {
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_EXTERNAL_VIEW, SERVICE_TUNE_ACCESSORIES_VIEW: button_back(playerid);
            case SERVICE_TUNE_WHEEL_WIDTH:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(g_VehVisualsInfo[vehicleid][vcWheelWidth] >= 250) return SendError(playerid, "Достигнуто минимальное значение.");
                g_VehVisualsInfo[vehicleid][vcWheelWidth] += 25;
                f(STRING_GLOBAL, "Ширина колес~n~%d", g_VehVisualsInfo[vehicleid][vcWheelWidth]/25);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelWidth(vehicleid, g_VehVisualsInfo[vehicleid][vcWheelWidth]);
            }
            case SERVICE_TUNE_WHEEL_SIZE:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(g_VehHandlingInfo[vehicleid][hpWheelSize] >= 1.0) return SendError(playerid, "Достигнуто максимальное значение.");
                g_VehHandlingInfo[vehicleid][hpWheelSize] += 0.025;
                f(STRING_GLOBAL, "Размер колес~n~%.2f", g_VehHandlingInfo[vehicleid][hpWheelSize]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

                SetVehicleWheelSize(vehicleid, g_VehHandlingInfo[vehicleid][hpWheelSize]);
            }
            case SERVICE_TUNE_WHEEL_OFFSET_X:
            {
                new vehicleid = GetPlayerVehicleID(playerid),
                    slot_id = p_temp[playerid][p_listitem_int];
                if(g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id] >= 25) return SendError(playerid, "Достигнуто максимальное значение.");
                g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id] += 1;
                f(STRING_GLOBAL, "Проставка на~n~%d см", g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelOffsetX(vehicleid, slot_id, g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id]);
            }
            case SERVICE_TUNE_WHEEL_ANGLE:
            {
                new vehicleid = GetPlayerVehicleID(playerid),
                    slot_id = p_temp[playerid][p_listitem_int];
                if(g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id] >= 25) return SendError(playerid, "Достигнуто максимальное значение.");
                g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id] += 1;
                f(STRING_GLOBAL, "Развал-схождение~n~%d", g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelAngle(vehicleid, slot_id, g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id]);
            }
            case SERVICE_TUNE_COLOR_LIGHTS:
            {
                if(p_temp[playerid][p_listitem][5] >= 5) return SendError(playerid, "Достигнуто максимальное значение.");
                p_temp[playerid][p_listitem][5]++;
                new vehicleid = GetPlayerVehicleID(playerid),
                    coef = p_temp[playerid][p_listitem][5],
                    slot_id = p_temp[playerid][p_listitem_int],
                    color_r, color_g, color_b;
                GetBitColorRGB(ServiceTune_Colors[slot_id][st_Color], color_r, color_g, color_b);

                color_r = floatround(coef*0.1*color_r);
                color_g = floatround(coef*0.1*color_g);
                color_b = floatround(coef*0.1*color_b);
                SetVehicleLightsColors(vehicleid, color_r, color_g, color_b);

                SetVehicleParamsVEx(vehicleid, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);

                f(STRING_GLOBAL, "Насыщенность~n~%d%", p_temp[playerid][p_listitem][5]*10);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
            }
            case SERVICE_TUNE_TONING:
            {
                if(p_temp[playerid][p_listitem_int] >= 34) return SendError(playerid, "Достигнуто максимальное значение.");
                p_temp[playerid][p_listitem_int]++;
                new vehicleid = GetPlayerVehicleID(playerid),
                    toner_id = p_temp[playerid][p_listitem_int];

                SetVehicleToner(vehicleid, toner_id);

                f(STRING_GLOBAL, "Tонировка~n~%d", p_temp[playerid][p_listitem_int]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
            }
        }
        return 1;
    }
    if(playertextid == PTD_ServiceTune[playerid][17]) // >>/-
    {
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_EXTERNAL_VIEW, SERVICE_TUNE_ACCESSORIES_VIEW: button_next(playerid);
            case SERVICE_TUNE_WHEEL_WIDTH:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(g_VehVisualsInfo[vehicleid][vcWheelWidth] <= 100) return SendError(playerid, "Достигнуто минимальное значение.");
                g_VehVisualsInfo[vehicleid][vcWheelWidth] -= 25;
                f(STRING_GLOBAL, "Ширина колес~n~%d", g_VehVisualsInfo[vehicleid][vcWheelWidth]/25);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelWidth(vehicleid, g_VehVisualsInfo[vehicleid][vcWheelWidth]);
            }
            case SERVICE_TUNE_WHEEL_SIZE:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(g_VehHandlingInfo[vehicleid][hpWheelSize] <= 0.5) return SendError(playerid, "Достигнуто минимальное значение.");
                g_VehHandlingInfo[vehicleid][hpWheelSize] -= 0.025;
                f(STRING_GLOBAL, "Размер колес~n~%.2f", g_VehHandlingInfo[vehicleid][hpWheelSize]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelSize(vehicleid, g_VehHandlingInfo[vehicleid][hpWheelSize]);
            }
            case SERVICE_TUNE_WHEEL_OFFSET_X:
            {
                new vehicleid = GetPlayerVehicleID(playerid),
                    slot_id = p_temp[playerid][p_listitem_int];
                if(g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id] <= -40) return SendError(playerid, "Достигнуто минимальное значение.");
                g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id] -= 1;
                f(STRING_GLOBAL, "Проставка на~n~%d см", g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelOffsetX(vehicleid, slot_id, g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id]);
            }
            case SERVICE_TUNE_WHEEL_ANGLE:
            {
                new vehicleid = GetPlayerVehicleID(playerid),
                    slot_id = p_temp[playerid][p_listitem_int];
                if(g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id] <= -25) return SendError(playerid, "Достигнуто минимальное значение.");
                g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id] -= 1;
                f(STRING_GLOBAL, "Развал-схождение~n~%d", g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
                SetVehicleWheelAngle(vehicleid, slot_id, g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id]);
            }
            case SERVICE_TUNE_COLOR_LIGHTS:
            {
                if(p_temp[playerid][p_listitem][5] <= 1) return SendError(playerid, "Достигнуто минимальное значение.");
                p_temp[playerid][p_listitem][5]--;
                new vehicleid = GetPlayerVehicleID(playerid),
                    coef = p_temp[playerid][p_listitem][5],
                    slot_id = p_temp[playerid][p_listitem_int],
                    color_r, color_g, color_b;
                GetBitColorRGB(ServiceTune_Colors[slot_id][st_Color], color_r, color_g, color_b);

                color_r = floatround(coef*0.1*color_r);
                color_g = floatround(coef*0.1*color_g);
                color_b = floatround(coef*0.1*color_b);

                SetVehicleLightsColors(vehicleid, color_r, color_g, color_b);

                SetVehicleParamsVEx(vehicleid, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);

                f(STRING_GLOBAL, "Насыщенность~n~%d%", p_temp[playerid][p_listitem][5]*10);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
            }
            case SERVICE_TUNE_TONING:
            {
                if(p_temp[playerid][p_listitem_int] <= 1) return SendError(playerid, "Достигнуто минимальное значение.");
                p_temp[playerid][p_listitem_int]--;
                new vehicleid = GetPlayerVehicleID(playerid),
                    toner_id = p_temp[playerid][p_listitem_int];

                SetVehicleToner(vehicleid, toner_id);

                f(STRING_GLOBAL, "Тонировка~n~%d", p_temp[playerid][p_listitem_int]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
            }
        }
        return 1;
    }
    if(playertextid == PTD_ServiceTune[playerid][5] || playertextid == PTD_ServiceTune[playerid][6])
    {
        p_temp[playerid][p_listitem_int] = !p_temp[playerid][p_listitem_int];
        ServiceTune_UpdateTD_Axle(playerid);
        new slot_id = p_temp[playerid][p_listitem_int],
            vehicleid = GetPlayerVehicleID(playerid);
        if(p_temp[playerid][InterfaceID] == SERVICE_TUNE_WHEEL_OFFSET_X)
        {
            f(STRING_GLOBAL, "Проставка на~n~%d см", g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
        }
        if(p_temp[playerid][InterfaceID] == SERVICE_TUNE_WHEEL_ANGLE)
        {
            f(STRING_GLOBAL, "Развал-схождение~n~%d", g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id]);
            PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);
        }
        return 1;
    }
    for(new i = 11; i != -1; i--)
    {
        if(playertextid == PTD_ServiceTune_Color[playerid][i])
        {
            if(p_temp[playerid][InterfaceID] == SERVICE_TUNE_COLOR_LIGHTS && (i == 1 || i == 2))
                return SendError(playerid, "Эти цвета не доступны.");
            new old_id = p_temp[playerid][p_listitem_int],
                vehicleid = GetPlayerVehicleID(playerid);
            p_temp[playerid][p_listitem_int] = i;
            ServiceTune_UpdateTD_Colors(playerid, old_id);
            ServiceTune_UpdateTD_Colors(playerid, i);
            if(p_temp[playerid][InterfaceID] == SERVICE_TUNE_COLOR_SELECT)
            {
                new v_id1 = p_temp[playerid][p_listitem][5], v_id2 = p_temp[playerid][p_listitem_int];
                if(p_temp[playerid][InterfacePage] == 0) ChangeVehicleColor(vehicleid, ServiceTune_Colors[v_id2][st_ID], veh_info[vehicleid][v_color][1]);
                else if(p_temp[playerid][InterfacePage] == 1) ChangeVehicleColor(vehicleid, ServiceTune_Colors[v_id1][st_ID], ServiceTune_Colors[v_id2][st_ID]);
            }
            if(p_temp[playerid][InterfaceID] == SERVICE_TUNE_COLOR_LIGHTS)
            {
                new color_r, color_g, color_b, coef = p_temp[playerid][p_listitem][5];
                GetBitColorRGB(ServiceTune_Colors[i][st_Color], color_r, color_g, color_b);
                color_r = floatround(coef*0.1*color_r);
                color_g = floatround(coef*0.1*color_g);
                color_b = floatround(coef*0.1*color_b);

                SetVehicleLightsColors(vehicleid, color_r, color_g, color_b);
                SetVehicleParamsVEx(vehicleid, VEHICLE_PARAMS_ON, VEHICLE_PARAMS_ON, alarm, veh_info[vehicleid][v_lock], bonnet, boot, objective);
            }
            return 1;
        }
    }
    return 1;
}

stock Interface_OnClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == TD_ServiceTune[5])
    {
        if((p_temp[playerid][InterfaceID] == SERVICE_TUNE_ACCESSORIES && p_temp[playerid][InterfacePage] >= 2) ||
            (p_temp[playerid][InterfaceID] == SERVICE_TUNE_COMPONENTS && p_temp[playerid][InterfacePage] >= 3) ||
            p_temp[playerid][InterfacePage] >= 4)
            p_temp[playerid][InterfacePage] = 0;
        p_temp[playerid][InterfacePage]++;
        Interface_Show(playerid, p_temp[playerid][InterfaceID]);
        return 1;
    }
    if(clickedid == TD_ServiceTune[6])
    {
        p_temp[playerid][InterfacePage]--;
        if(p_temp[playerid][InterfacePage] <= 0)
            p_temp[playerid][InterfacePage] = p_temp[playerid][InterfaceID] == SERVICE_TUNE_ACCESSORIES ? 2 :
                                                p_temp[playerid][InterfaceID] == SERVICE_TUNE_COMPONENTS ? 3 : 4;
        Interface_Show(playerid, p_temp[playerid][InterfaceID]);
        return 1;
    }
    if(clickedid == TD_ServiceTune[11]) // Приобрести
    {
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_EXTERNAL_VIEW, SERVICE_TUNE_ACCESSORIES_VIEW: button_buy(playerid);
            case SERVICE_TUNE_COLOR_SELECT:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    new till = Service_GetTill(playerid);
                    if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                    new price = 5000 * till;

                    if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                    SendAccess(playerid, "Вы перекрасили транспортное средство в СТО.");

                    Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил перекраску на <%s>(%d)[%d] за %d$",
                        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                        GetVehicleName(vehicleid), GetVehicleModelEx(vehicleid), veh_info[vehicleid][v_mysql_id], price);

                    BuyPlayerService(playerid, price);

                    new v_id1 = p_temp[playerid][p_listitem][5], v_id2 = p_temp[playerid][p_listitem_int];
                    veh_info[vehicleid][v_color][0] = ServiceTune_Colors[v_id1][st_ID];
                    veh_info[vehicleid][v_color][1] = ServiceTune_Colors[v_id2][st_ID];

                    SaveVehicle(vehicleid);
                    if(GetVehicleModelEx(vehicleid) == 3610) SetVehicleHealth(vehicleid, 3000.0);
                    RepairVehicle(vehicleid);

                    ServiceTune_HideTD_Colors(playerid);
                    Interface_Show(playerid, SERVICE_TUNE_INDEX);
                }
                if(p_temp[playerid][InterfacePage] == 0)
                {
                    p_temp[playerid][InterfacePage]++;
                    new old_id= p_temp[playerid][p_listitem_int];
                    p_temp[playerid][p_listitem][5] = p_temp[playerid][p_listitem_int];
                    p_temp[playerid][p_listitem_int] = 0;
                    ServiceTune_UpdateTD_Colors(playerid, old_id);
                    ServiceTune_UpdateTD_Colors(playerid, 0);
                    Interface_Show(playerid, SERVICE_TUNE_COLOR_SELECT);
                }
                new v_id1 = p_temp[playerid][p_listitem][5], v_id2 = p_temp[playerid][p_listitem_int];
                ChangeVehicleColor(vehicleid, ServiceTune_Colors[v_id1][st_ID], ServiceTune_Colors[v_id2][st_ID]);
            }
            case SERVICE_TUNE_WHEEL_ANGLE:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                new price = PRICE_TUNE_WHEEL_ANGLE * till;

                if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                new vehicleid = GetPlayerVehicleID(playerid),
                    slot_id = p_temp[playerid][p_listitem_int];
                if(veh_info[vehicleid][v_wheel_alignment][slot_id] == g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id])
                    return SendError(playerid, "У Вас уже стоит данный элемент.");
                Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил развал-схождение на <%s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                    GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id], price);

                veh_info[vehicleid][v_wheel_alignment][slot_id] = g_VehVisualsInfo[vehicleid][vcWheelAlignment][slot_id];
                SetVehicleWheelAngle(vehicleid, slot_id, veh_info[vehicleid][v_wheel_alignment][slot_id]);
                BuyPlayerService(playerid, price);
                SaveVehicleVisual(vehicleid);
            }
            case SERVICE_TUNE_WHEEL_OFFSET_X:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                new price = PRICE_TUNE_WHEEL_OFFSET_X * till;

                if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                new vehicleid = GetPlayerVehicleID(playerid),
                    slot_id = p_temp[playerid][p_listitem_int];
                if(veh_info[vehicleid][v_wheel_offset_x][slot_id] == g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id])
                    return SendError(playerid, "У Вас уже стоит данный элемент.");
                Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил проставку на ступицу на <%s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                    GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id], price);

                SetVehicleWheelOffsetX(vehicleid, slot_id, g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id]);
                BuyPlayerService(playerid, price);

                veh_info[vehicleid][v_wheel_offset_x][slot_id] = g_VehVisualsInfo[vehicleid][vcWheelOffsetX][slot_id];
                SaveVehicleVisual(vehicleid);
            }
            case SERVICE_TUNE_WHEEL_WIDTH:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                new price = PRICE_TUNE_WHEEL_WIDTH * till;

                if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                new vehicleid = GetPlayerVehicleID(playerid);
                if(veh_info[vehicleid][v_wheel_width] == g_VehVisualsInfo[vehicleid][vcWheelWidth])
                    return SendError(playerid, "У Вас уже стоит данный элемент.");
                Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил ширину колес на <%s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                    GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id], price);

                SetVehicleWheelWidth(vehicleid, g_VehVisualsInfo[vehicleid][vcWheelWidth]);
                BuyPlayerService(playerid, price);

                veh_info[vehicleid][v_wheel_width] = g_VehVisualsInfo[vehicleid][vcWheelWidth];
                SaveVehicleVisual(vehicleid);
            }
            case SERVICE_TUNE_WHEEL_SIZE:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                new price = PRICE_TUNE_WHEEL_SIZE * till;

                if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                new vehicleid = GetPlayerVehicleID(playerid);
                if(veh_info[vehicleid][v_wheel_size] == g_VehHandlingInfo[vehicleid][hpWheelSize])
                    return SendError(playerid, "У Вас уже стоит данный элемент.");
                Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил высоту колес на <%s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                    GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id], price);

                veh_info[vehicleid][v_wheel_size] = g_VehHandlingInfo[vehicleid][hpWheelSize];

                SetVehicleWheelSize(vehicleid, veh_info[vehicleid][v_wheel_size]);
                BuyPlayerService(playerid, price);
                SaveVehicleVisual(vehicleid);
            }
            case SERVICE_TUNE_COLOR_LIGHTS:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                new price = PRICE_TUNE_COLOR_LIGHTS * till;

                if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                new vehicleid = GetPlayerVehicleID(playerid);
                if(g_VehVisualsInfo[vehicleid][vcLightsColor][0] == veh_info[vehicleid][v_lights_color][0] &&
                    g_VehVisualsInfo[vehicleid][vcLightsColor][1] == veh_info[vehicleid][v_lights_color][1] &&
                    g_VehVisualsInfo[vehicleid][vcLightsColor][2] == veh_info[vehicleid][v_lights_color][2])
                        return SendError(playerid, "У Вас уже стоит данный элемент.");

                Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил высоту колес на <%s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                    GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id], price);

                veh_info[vehicleid][v_lights_color][0] = g_VehVisualsInfo[vehicleid][vcLightsColor][0];
                veh_info[vehicleid][v_lights_color][1] = g_VehVisualsInfo[vehicleid][vcLightsColor][1];
                veh_info[vehicleid][v_lights_color][2] = g_VehVisualsInfo[vehicleid][vcLightsColor][2];

                SetVehicleLightsColors(vehicleid, veh_info[vehicleid][v_lights_color][0], veh_info[vehicleid][v_lights_color][1], veh_info[vehicleid][v_lights_color][2]);
                BuyPlayerService(playerid, price);
                SaveVehicleVisual(vehicleid);
            }

            case SERVICE_TUNE_TONING:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                new price = PRICE_TUNE_TONING * till;

                if(p_info[playerid][cash] < price) return SendError(playerid, "У Вас нет столько денег. Используйте /donate");
                new vehicleid = GetPlayerVehicleID(playerid);
                if(veh_info[vehicleid][v_toner] == p_temp[playerid][p_listitem_int])
                        return SendError(playerid, "У Вас уже стоит данный элемент.");

                Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] купил тонировку на <%s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
                    GetVehicleName(vehicleid), veh_info[vehicleid][v_model], veh_info[vehicleid][v_mysql_id], price);

                veh_info[vehicleid][v_toner] = p_temp[playerid][p_listitem_int];

                SetVehicleToner(vehicleid, veh_info[vehicleid][v_toner]);

                f(STRING_GLOBAL, "Тонировка~n~%d", p_temp[playerid][p_listitem_int]);
                PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15], STRING_GLOBAL);

                BuyPlayerService(playerid, price);
                SaveVehicleVisual(vehicleid);
            }
        }
        return 1;
    }
    if(clickedid == TD_ServiceTune[12]) // Назад <--
    {
        Service_TuningClear(playerid);
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_EXTERNAL_VIEW, SERVICE_TUNE_TONING: Interface_Show(playerid, SERVICE_TUNE_EXTERNAL);
            case SERVICE_TUNE_ACCESSORIES_VIEW: Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
            case SERVICE_TUNE_COLOR_SELECT, SERVICE_TUNE_COLOR_LIGHTS:
            {
                ServiceTune_HideTD_Colors(playerid);
                Interface_Show(playerid, SERVICE_TUNE_INDEX);
            }
            case SERVICE_TUNE_WHEEL_SIZE, SERVICE_TUNE_WHEEL_WIDTH, SERVICE_TUNE_WHEEL_OFFSET_X,SERVICE_TUNE_WHEEL_ANGLE: Interface_Show(playerid, SERVICE_TUNE_SUSPENSION);
            default: Interface_Show(playerid, SERVICE_TUNE_INDEX);
        }
        return 1;
    }
    if(clickedid == TD_ServiceTune[15]) // 0й слот - покраска
    {
        p_temp[playerid][InterfacePage] =
        p_temp[playerid][p_listitem_int] =
        p_temp[playerid][p_listitem][5] = 0;
        SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
        Interface_Show(playerid, SERVICE_TUNE_COLOR_SELECT);
    }
    if(clickedid == TD_ServiceTune[1]) // 1й слот
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            getmodel = GetVehicleModelEx(vehicleid);
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_INDEX:
            {
                new vehicleid = GetPlayerVehicleID(playerid);
                if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return SendError(playerid, "Данные компоненты доступны только автомобилям.");
                p_temp[playerid][InterfacePage] = 1;
                Interface_Show(playerid, SERVICE_TUNE_EXTERNAL);
            }
            case SERVICE_TUNE_EXTERNAL:
            {

                p_temp[playerid][p_listitem][0] = vehicleid;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    p_temp[playerid][p_listitem][1] = v_nitro;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_NITRO, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    p_temp[playerid][p_listitem][1] = v_pear_bumper;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_REAR_BUMPER, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 3)
                {
                    p_temp[playerid][p_listitem][1] = v_lamps;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_LAMPS, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 4)
                {
                    switch(getmodel)
                    {//Покрасочная работа MAX: 3
                        case 534, 535, 536, 558, 559, 561, 560, 562, 565, 567, 575, 576:
                        {
                            p_temp[playerid][p_listitem][1] = v_paintjob;
                            p_temp[playerid][p_listitem][5] = 3;
                        }
                        default: return SendError(playerid, "На данное транспортное средство нет покрасочных работ.");
                    }
                }
                if(p_temp[playerid][p_listitem][5] == -1) return SendError(playerid, "На данное транспортное средство нет деталей.");
                ShowPlayerDialog(playerid, D_TUNE_DEFAULT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            /*
            case SERVICE_TUNE_ACCESSORIES:
            {
                getmodel -= 400;
                if(getmodel < 0)
                    return SendError(playerid, "Вы должны быть в автомобиле.");
                if(getmodel > 203)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Автомобиль не поддерживается.");
                }
                if(GetVehicleData(getmodel, E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return Service_Error(playerid, "Пользоваться услугами автомастерской можно только на автомобилях.");
                if(p_temp[playerid][InterfacePage] == 1) p_temp[playerid][p_listitem][2] = 0;
                if(p_temp[playerid][InterfacePage] == 2) p_temp[playerid][p_listitem][2] = 4;

                if(GetMaxCountObjectTune(getmodel, p_temp[playerid][p_listitem][2]) == -1)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Нет доступных аксессуаров в этом разделе.");
                }
                p_temp[playerid][p_listitem][3] = vehicleid;

                ShowPlayerDialog(playerid, D_TUNE_OBJECT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            */
            case SERVICE_TUNE_COMPONENTS:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");
                STRING_GLOBAL[0] = EOS;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    if(veh_info[vehicleid][v_twinturbo_data][0] >= 3) return SendError(playerid, "Вы не можете улучшить выбранный компонент более 3-х раз.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W" Вы желаете обновить %s до %d из 3 этап(-а/-ов) за %d$?", name_twinturbo[0], veh_info[vehicleid][v_twinturbo_data][0]+1, GetTuningOtherPrice(playerid, vehicleid, 0) * till);
                    p_temp[playerid][p_listitem_int] = 0;
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    if(veh_info[vehicleid][v_details][0] == 100.0) return SendError(playerid, "Вы не можете заменить выбранный компонент если его состояние максимальное.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы желаете заменить %s за %d$?", name_details[0], ((GetTuningOtherPrice(playerid, vehicleid, 4) / 100) * floatround(100.0 - veh_info[vehicleid][v_details][0])) * till);
                    p_temp[playerid][p_listitem_int] = 4;
                }
                else if(p_temp[playerid][InterfacePage] == 3)
                {
                    if(veh_info[vehicleid][v_details][4] == 100.0) return SendError(playerid, "Вы не можете заменить выбранный компонент если его состояние максимальное.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы желаете заменить %s за %d$?", name_details[4], ((GetTuningOtherPrice(playerid, vehicleid, 8) / 100) * floatround(100.0 - veh_info[vehicleid][v_details][4])) * till);
                    p_temp[playerid][p_listitem_int] = 8;
                }
                ShowPlayerDialog(playerid, D_TUNE_OTHER_BUY, DIALOG_STYLE_MSGBOX, ""I"Дополнительные компоненты", STRING_GLOBAL, "Далее", "Отмена");
            }
            case SERVICE_TUNE_SUSPENSION:
            {
                SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
                Interface_Show(playerid, SERVICE_TUNE_WHEEL_SIZE);
            }
            default: return SendInfo(playerid, "В разработке.");
        }
    }
    if(clickedid == TD_ServiceTune[2]) // 2й слот
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            getmodel = GetVehicleModelEx(vehicleid);
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_INDEX:
            {
                p_temp[playerid][InterfacePage] = 1;
                Interface_Show(playerid, SERVICE_TUNE_COMPONENTS);
            }
            case SERVICE_TUNE_EXTERNAL:
            {
                if(GetVehicleData(getmodel, E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return Service_Error(playerid, "Пользоваться услугами автомастерской можно только на автомобилях.");
                p_temp[playerid][p_listitem][0] = vehicleid;
                p_temp[playerid][tune_default] = true;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    p_temp[playerid][p_listitem][1] = v_wheels;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_WHEELS, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    if(getmodel == 444 || getmodel == 556 || getmodel == 573)
                        return SendError(playerid, "На этот автомобиль нет гидравлики.");

                    p_temp[playerid][p_listitem][1] = v_hydraulics;
                    if(veh_info[vehicleid][v_tune][v_hydraulics] != 0) ShowPlayerDialog(playerid, D_TUNE_DEFAULT_ACT, DIALOG_STYLE_MSGBOX, ""I"Гидравлика", ""W"Вы желаете снять с транспортного средства гидравлику?", "Далее", "Отмена");
                    else
                    {
                        new till = Service_GetTill(playerid);
                        if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");

                        STRING_GLOBAL[0] = EOS;
                        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы желаете установить на транспортное средство гидравлику?\n\nСтоимость: %d$.", 200000 * till);
                        ShowPlayerDialog(playerid, D_TUNE_DEFAULT_ACT, DIALOG_STYLE_MSGBOX, ""I"Гидравлика", STRING_GLOBAL, "Далее", "Отмена");
                    }
                    return 1;
                }
                else if(p_temp[playerid][InterfacePage] == 3)
                {
                    p_temp[playerid][p_listitem][1] = v_exhausts;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_EXHAUST, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 4)
                {
                    if(!IsPlayerMobile(playerid))
                        return SendError(playerid, "Пока что работает только с телефона :(");
                    if(GetPlayerGameVersion(playerid) < CLIENT_VERSION_20022023)
                        return SendError(playerid, "Обновите кэш файлы до последней версии.");
                    if(!IsSupportsVehicleToner(getmodel)) 
                        return SendError(playerid, "Ваша модель Т/С не поддерживает тонировку.");
                    SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
                    Interface_Show(playerid, SERVICE_TUNE_TONING);
                    return 1;
                }
                if(p_temp[playerid][p_listitem][5] == -1) return SendError(playerid, "На данное транспортное средство нет деталей.");
                ShowPlayerDialog(playerid, D_TUNE_DEFAULT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            /*
            case SERVICE_TUNE_ACCESSORIES:
            {
                getmodel -= 400;
                if(getmodel < 0)
                    return SendError(playerid, "Вы должны быть в автомобиле.");
                if(getmodel > 203)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Автомобиль не поддерживается.");
                }
                if(GetVehicleData(getmodel, E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return Service_Error(playerid, "Пользоваться услугами автомастерской можно только на автомобилях.");
                if(p_temp[playerid][InterfacePage] == 1) p_temp[playerid][p_listitem][2] = 1;
                if(p_temp[playerid][InterfacePage] == 2) p_temp[playerid][p_listitem][2] = 5;

                if(GetMaxCountObjectTune(getmodel, p_temp[playerid][p_listitem][2]) == -1)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Нет доступных аксессуаров в этом разделе.");
                }
                p_temp[playerid][p_listitem][3] = vehicleid;

                ShowPlayerDialog(playerid, D_TUNE_OBJECT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            */
            case SERVICE_TUNE_COMPONENTS:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");
                STRING_GLOBAL[0] = EOS;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    if(veh_info[vehicleid][v_twinturbo_data][1] >= 3) return SendError(playerid, "Вы не можете улучшить выбранный компонент более 3-х раз.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W" Вы желаете обновить %s до %d из 3 этап(-а/-ов) за %d$?", name_twinturbo[1], veh_info[vehicleid][v_twinturbo_data][1]+1, GetTuningOtherPrice(playerid, vehicleid, 1) * till);
                    p_temp[playerid][p_listitem_int] = 1;
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    if(veh_info[vehicleid][v_details][1] == 100.0) return SendError(playerid, "Вы не можете заменить выбранный компонент если его состояние максимальное.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы желаете заменить %s за %d$?", name_details[1], ((GetTuningOtherPrice(playerid, vehicleid, 5) / 100) * floatround(100.0 - veh_info[vehicleid][v_details][1])) * till);
                    p_temp[playerid][p_listitem_int] = 5;
                }
                else if(p_temp[playerid][InterfacePage] == 3)
                {
                    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
                    for(new i, j = sizeof(info_details); i < j; i++)
                    {
                        format(STRING_MIN, sizeof(STRING_MIN), "%s\n", info_details[i]);
                        strcat(STRING_GLOBAL, STRING_MIN);
                    }
                    return ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Информация о деталях", STRING_GLOBAL, "Понял", "");
                }
                ShowPlayerDialog(playerid, D_TUNE_OTHER_BUY, DIALOG_STYLE_MSGBOX, ""I"Дополнительные компоненты", STRING_GLOBAL, "Далее", "Отмена");
            }
            case SERVICE_TUNE_SUSPENSION:
            {
                if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return Service_Error(playerid, "Пользоваться услугами автомастерской можно только на автомобилях.");
                SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
                Interface_Show(playerid, SERVICE_TUNE_WHEEL_WIDTH);
            }
            default: return SendInfo(playerid, "В разработке.");
        }
    }
    if(clickedid == TD_ServiceTune[3]) // 3й слот
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            getmodel = GetVehicleModelEx(vehicleid);
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_INDEX:
            {
                
                //SendError(playerid, "Раздел на переработке.");
                
                //if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) != VEHICLE_STATE_CAR)
                //        return SendError(playerid, "Данные компоненты доступны только автомобилям.");
                p_temp[playerid][InterfacePage] = 1;
                Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                
            }
            case SERVICE_TUNE_EXTERNAL:
            {
                p_temp[playerid][p_listitem][0] = vehicleid;
                p_temp[playerid][tune_default] = true;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    p_temp[playerid][p_listitem][1] = v_spoiler;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_SPOILER, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    p_temp[playerid][p_listitem][1] = v_hoods;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_HOOD, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 3)
                {
                    p_temp[playerid][p_listitem][1] = v_roofs;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_ROOF, getmodel);
                }
                else if(p_temp[playerid][InterfacePage] == 4)
                {
                    SetCameraForPlayer(playerid, CAMERA_ID_SIDE_RIGHT_BACK);
                    return Interface_Show(playerid, SERVICE_TUNE_COLOR_LIGHTS);
                }
                if(p_temp[playerid][p_listitem][5] == -1) return SendError(playerid, "На данное транспортное средство нет деталей.");
                ShowPlayerDialog(playerid, D_TUNE_DEFAULT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            /*
            case SERVICE_TUNE_ACCESSORIES:
            {
                getmodel -= 400;
                if(getmodel < 0)
                    return SendError(playerid, "Вы должны быть в автомобиле.");
                if(getmodel > 203)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Автомобиль не поддерживается.");
                }
                if(GetVehicleData(getmodel, E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return Service_Error(playerid, "Пользоваться услугами автомастерской можно только на автомобилях.");
                if(p_temp[playerid][InterfacePage] == 1) p_temp[playerid][p_listitem][2] = 2;
                if(p_temp[playerid][InterfacePage] == 2) p_temp[playerid][p_listitem][2] = 6;

                if(GetMaxCountObjectTune(getmodel, p_temp[playerid][p_listitem][2]) == -1)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Нет доступных аксессуаров в этом разделе.");
                }
                p_temp[playerid][p_listitem][3] = vehicleid;

                ShowPlayerDialog(playerid, D_TUNE_OBJECT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            */
            case SERVICE_TUNE_COMPONENTS:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");
                STRING_GLOBAL[0] = EOS;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    if(veh_info[vehicleid][v_twinturbo_data][2] >= 3) return SendError(playerid, "Вы не можете улучшить выбранный компонент более 3-х раз.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W" Вы желаете обновить %s до %d из 3 этап(-а/-ов) за %d$?", name_twinturbo[2], veh_info[vehicleid][v_twinturbo_data][2]+1, GetTuningOtherPrice(playerid, vehicleid, 2) * till);
                    p_temp[playerid][p_listitem_int] = 2;
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    if(veh_info[vehicleid][v_details][2] == 100.0) return SendError(playerid, "Вы не можете заменить выбранный компонент если его состояние максимальное.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы желаете заменить %s за %d$?", name_details[2], ((GetTuningOtherPrice(playerid, vehicleid, 6) / 100) * floatround(100.0 - veh_info[vehicleid][v_details][2])) * till);
                    p_temp[playerid][p_listitem_int] = 6;
                }
                ShowPlayerDialog(playerid, D_TUNE_OTHER_BUY, DIALOG_STYLE_MSGBOX, ""I"Дополнительные компоненты", STRING_GLOBAL, "Далее", "Отмена");
            }
            case SERVICE_TUNE_SUSPENSION:
            {
                SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
                Interface_Show(playerid, SERVICE_TUNE_WHEEL_OFFSET_X);
            }
            default: return SendInfo(playerid, "В разработке.");
        }
    }
    if(clickedid == TD_ServiceTune[4]) // 4й слот
    {
        new vehicleid = GetPlayerVehicleID(playerid),
            getmodel = GetVehicleModelEx(vehicleid);
        switch(p_temp[playerid][InterfaceID])
        {
            case SERVICE_TUNE_INDEX:
            {
                if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return SendError(playerid, "Данные компоненты доступны только автомобилям.");
                Interface_Show(playerid, SERVICE_TUNE_SUSPENSION);
            }
            case SERVICE_TUNE_EXTERNAL:
            {
                p_temp[playerid][p_listitem][0] = vehicleid;
                p_temp[playerid][tune_default] = true;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    p_temp[playerid][p_listitem][1] = v_front_bumper;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_FRONT_BUMPER, getmodel);
                    SetCameraForPlayer(playerid, CAMERA_ID_FRONT);
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    p_temp[playerid][p_listitem][1] = v_vents;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_VENT_RIGHT, getmodel);
                    SetCameraForPlayer(playerid, CAMERA_ID_FRONT);
                }
                else if(p_temp[playerid][InterfacePage] == 3)
                {
                    p_temp[playerid][p_listitem][1] = v_sideskirt;
                    p_temp[playerid][p_listitem][5] = GetMaxCountComponentTune(playerid, CARMODTYPE_SIDESKIRT, getmodel);
                    SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
                }
                if(p_temp[playerid][p_listitem][5] == -1) return SendError(playerid, "На данное транспортное средство нет деталей.");
                ShowPlayerDialog(playerid, D_TUNE_DEFAULT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            /*
            case SERVICE_TUNE_ACCESSORIES:
            {
                getmodel -= 400;
                if(getmodel < 0)
                    return SendError(playerid, "Вы должны быть в автомобиле.");
                if(getmodel > 203)
                    return SendError(playerid, "Автомобиль не поддерживается.");
                if(GetVehicleData(getmodel, E_VD_TYPE) != VEHICLE_STATE_CAR)
                    return Service_Error(playerid, "Пользоваться услугами автомастерской можно только на автомобилях.");
                if(p_temp[playerid][InterfacePage] == 1) p_temp[playerid][p_listitem][2] = 3;
                if(p_temp[playerid][InterfacePage] == 2) p_temp[playerid][p_listitem][2] = 7;

                if(GetMaxCountObjectTune(getmodel, p_temp[playerid][p_listitem][2]) == -1)
                {
                    if(p_temp[playerid][TextDrawServiceTune]) Interface_Show(playerid, SERVICE_TUNE_ACCESSORIES);
                    else ShowDialogTuneObject(playerid);
                    return SendError(playerid, "Нет доступных аксессуаров в этом разделе.");
                }
                p_temp[playerid][p_listitem][3] = vehicleid;

                //ShowPlayerDialog(playerid, D_TUNE_OBJECT_ACT, DIALOG_STYLE_LIST, ""I"Действие", ""I"[1]"W" Удалить текущий элемент\n"I"[2]"W" Купить новый элемент", "Далее", "Отмена");
            }
            */
            case SERVICE_TUNE_COMPONENTS:
            {
                new till = Service_GetTill(playerid);
                if(till == -1) return Service_Error(playerid, "Не найден ID автосервиса, воспользуйтесь услугами автосервиса повторно.");
                STRING_GLOBAL[0] = EOS;
                if(p_temp[playerid][InterfacePage] == 1)
                {
                    if(veh_info[vehicleid][v_twinturbo_data][3] >= 3) return SendError(playerid, "Вы не можете улучшить выбранный компонент более 3-х раз.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W" Вы желаете обновить %s до %d из 3 этап(-а/-ов) за %d$?", name_twinturbo[3], veh_info[vehicleid][v_twinturbo_data][3]+1, GetTuningOtherPrice(playerid, vehicleid, 3) * till);
                    p_temp[playerid][p_listitem_int] = 3;
                }
                else if(p_temp[playerid][InterfacePage] == 2)
                {
                    if(veh_info[vehicleid][v_details][3] == 100.0) return SendError(playerid, "Вы не можете заменить выбранный компонент если его состояние максимальное.");
                    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Вы желаете заменить %s за %d$?", name_details[3], ((GetTuningOtherPrice(playerid, vehicleid, 7) / 100) * floatround(100.0 - veh_info[vehicleid][v_details][3])) * till);
                    p_temp[playerid][p_listitem_int] = 7;
                }
                ShowPlayerDialog(playerid, D_TUNE_OTHER_BUY, DIALOG_STYLE_MSGBOX, ""I"Дополнительные компоненты", STRING_GLOBAL, "Далее", "Отмена");
            }
            case SERVICE_TUNE_SUSPENSION:
            {
                SetCameraForPlayer(playerid, CAMERA_ID_SIDE_LEFT_FRONT);
                Interface_Show(playerid, SERVICE_TUNE_WHEEL_ANGLE);
            }
            default: return SendInfo(playerid, "В разработке.");
        }
    }
    if(clickedid == TD_ServiceTune[8])
    {
        SetCameraForPlayer(playerid, p_temp[playerid][camera_id], 8.5, 3.0, true, TYPE_UPDATE_CAMERA_RIGHT);
    }
    return 1;
}

Phone_UpdateTD_Background(playerid)
{
    PlayerTextDrawDestroy(playerid, PTD_Phone[playerid][0]);

    new tmp_str[64];
    f(tmp_str, "flin_mobile:flin_mobile_type%d", p_info[playerid][active_phone_id]-674);

    PTD_Phone[playerid][0] = CreatePlayerTextDraw(playerid, 481.0000, 133.5955, tmp_str); // пусто
    PlayerTextDrawTextSize(playerid, PTD_Phone[playerid][0], 146.0000, 337.0000);
    PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][0], 1);
    PlayerTextDrawColor(playerid, PTD_Phone[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][0], 255);
    PlayerTextDrawFont(playerid, PTD_Phone[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][0], 0);

    PlayerTextDrawShow(playerid, PTD_Phone[playerid][0]);
}

Phone_Render(playerid)
{
    for(new i = 6; i != 0; i--) PlayerTextDrawShow(playerid, PTD_Phone[playerid][i]);
}

Phone_UpdateTD_Info(playerid)
{
    new str[64];

	format(str, sizeof(str), "%02d:%02d", timestamp_hour, timestamp_minute);
	PlayerTextDrawSetString(playerid, PTD_Phone[playerid][5], str);

	new month_name[12][12] = {"января", "февраля", "марта", "апреля", "мая", "июня", "июля", "августа", "сентября", "октября", "ноября", "декабря"};
	new day_name[7][12] = {"Чт", "Пт", "Сб", "Вс", "Пн", "Вт", "Ср"};

	new year, month, day;
	getdate(year, month, day);

	format(str, sizeof(str), "%s, %d %s", day_name[getDayEx()], day, month_name[month-1]);
	PlayerTextDrawSetString(playerid, PTD_Phone[playerid][6], str);
}

Case_UpdateTD_ItemBG(playerid, idx, name_bg_item[])
{
    PlayerTextDrawDestroy(playerid, PTD_Case[playerid][idx]);

    new Float:td_pos[][] =
    {
        {229.8000, 119.6576},
        {274.6000, 119.6576},
        {319.4996, 119.6576},
        {364.5996, 119.6576},
        {229.8000, 175.5066},
        {274.6000, 175.5066},
        {319.4996, 175.5066},
        {364.5996, 175.5066},
        {229.8000, 231.7554},
        {274.6000, 231.7554},
        {319.4996, 231.7554},
        {364.5996, 231.7554},
        {229.8000, 288.0043},
        {274.6000, 288.0043},
        {319.4996, 288.0043},
        {364.5996, 288.0043}
    };

    PTD_Case[playerid][idx] = CreatePlayerTextDraw(playerid, td_pos[idx-10][0], td_pos[idx-10][1], name_bg_item);
    PlayerTextDrawTextSize(playerid, PTD_Case[playerid][idx], 45.0000, 56.0000);
    PlayerTextDrawAlignment(playerid, PTD_Case[playerid][idx], 1);
    PlayerTextDrawColor(playerid, PTD_Case[playerid][idx], -2);
    PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][idx], 255);
    PlayerTextDrawFont(playerid, PTD_Case[playerid][idx], 4);
    PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][idx], 0);
    PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][idx], 0);

    PlayerTextDrawShow(playerid, PTD_Case[playerid][idx]);
}

Case_UpdateTD_Items(playerid, type)
{
    for(new idx = 15; idx != -1; idx--)
    {
        PlayerTextDrawSetString(playerid, PTD_Case[playerid][42+idx], "_");
        switch(Case[type][CasePrize][idx])
        {
            case TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Case[playerid][26+idx], Case[type][CasePrizeCount][idx]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Case[playerid][26+idx], 0.0000, 0.0000, 0.0000, 1.2000);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][26+idx]);
            }
            case TYPE_GIVE_ITEM_ACCESSORIES:
            {
                new i = Case[type][CasePrizeCount][idx];
                PlayerTextDrawSetPreviewModel(playerid, PTD_Case[playerid][26+idx], ItemsInfo[i][iModel]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Case[playerid][26+idx], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][26+idx]);
            }
            case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Case[playerid][26+idx], Case[type][CasePrizeCount][idx]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Case[playerid][26+idx], -45.0000, 0.0000, -45.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][26+idx]);
            }
            case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Case[playerid][26+idx], 1550);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Case[playerid][26+idx], 0.0000, 0.0000, 0.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][26+idx]);
                new str[32];
                format(str, sizeof(str), "%d", Case[type][CasePrizeCount][idx]);
                PlayerTextDrawSetString(playerid, PTD_Case[playerid][42+idx], str);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][42+idx]);
            }
            case TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Case[playerid][26+idx], 1274);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Case[playerid][26+idx], 0.0000, 0.0000, 0.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][26+idx]);
                new str[32];
                format(str, sizeof(str), "%d", Case[type][CasePrizeCount][idx]);
                PlayerTextDrawSetString(playerid, PTD_Case[playerid][42+idx], str);
                PlayerTextDrawShow(playerid, PTD_Case[playerid][42+idx]);
            }
        }
    }
    return 1;
}

Case_UpdateTD_Info(playerid, type)
{
    new str[64];
    if(p_temp[playerid][TextDrawCase] == false || type == -1) {
        HidePlayerCase(playerid);
        return SendError(playerid, "Произошла ошибка при обновлении информации, откройте открытие кейсов заново.");
    }
    format(str, sizeof(str), "%s", Case[type][CaseNameOne]);
    PlayerTextDrawSetString(playerid, PTD_Case[playerid][6], str);
    format(str, sizeof(str), "%d", p_info[playerid][flinmoney]);
    PlayerTextDrawSetString(playerid, PTD_Case[playerid][3], str);
    format(str, sizeof(str), "%d", GetInventoryAmount(playerid, TRANSFER_ITEMS+type+27));
    PlayerTextDrawSetString(playerid, PTD_Case[playerid][2], str);
    format(str, sizeof(str), "%d", Case[type][CasePrice]);
    PlayerTextDrawSetString(playerid, PTD_Case[playerid][8], str);
    return 1;
}

Case_Render(playerid)
{
    for(new i = 9; i != -1; i--) PlayerTextDrawShow(playerid, PTD_Case[playerid][i]);
    for(new i = 25; i != 9; i--) PlayerTextDrawShow(playerid, PTD_Case[playerid][i]);
}

//-------------
Roulette_UpdateTD_ItemBG(playerid, idx, name_bg_item[])
{
    PlayerTextDrawDestroy(playerid, PTD_Roulette[playerid][idx]);

    new Float:td_pos[][] =
    {
        {139.8000, 166.4488},
        {185.3999, 166.4488},
        {230.1999, 166.4488},
        {275.7998, 166.4488},
        {320.9996, 166.4488},
        {366.1997, 166.4488},
        {410.9996, 166.4488},
        {456.5999, 166.4488},
        {139.7998, 227.1777},
        {185.3999, 227.1777},
        {230.5997, 227.1777},
        {275.7998, 227.1777},
        {320.5997, 227.1777},
        {366.1994, 227.1777},
        {411.3995, 227.1777},
        {456.1994, 227.1777}
    };

    PTD_Roulette[playerid][idx] = CreatePlayerTextDraw(playerid, td_pos[idx-10][0], td_pos[idx-10][1], name_bg_item);
    PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][idx], 43.0000, 53.0000);
    PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][idx], 1);
    PlayerTextDrawColor(playerid, PTD_Roulette[playerid][idx], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][idx], 255);
    PlayerTextDrawFont(playerid, PTD_Roulette[playerid][idx], 4);
    PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][idx], 0);
    PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][idx], 0);

    PlayerTextDrawShow(playerid, PTD_Roulette[playerid][idx]);
}

Roulette_UpdateTD_Items(playerid, type)
{
    for(new idx = 15; idx != -1; idx--)
    {
        PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][42+idx], "_");
        switch(RoulettePlayerItems[playerid][type][idx])
        {
            case TYPE_GIVE_ITEM_EXP:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], 1277);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], 0.0000, 0.0000, 180.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
                new str[32];
                format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
                PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][42+idx], str);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][42+idx]);
            }
            case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], 1550);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], 0.0000, 0.0000, 0.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
                new str[32];
                format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
                PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][42+idx], str);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][42+idx]);
            }
            case TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], 1274);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], 0.0000, 0.0000, 0.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
                new str[32];
                format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
                PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][42+idx], str);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][42+idx]);
            }
            case TYPE_GIVE_ITEM_INVENTORY:
            {
                new i = RoulettePlayerItemsIDx[playerid][type][idx];
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], ItemsInfo[i][iModel]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
                new str[32];
                format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
                PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][42+idx], str);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][42+idx]);
            }
            case TYPE_GIVE_ITEM_ACCESSORIES:
            {
                new i = RoulettePlayerItemsCount[playerid][type][idx];
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], ItemsInfo[i][iModel]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
            }
            case TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], RoulettePlayerItemsCount[playerid][type][idx]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], 0.0000, 0.0000, 0.0000, 1.2000);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
            }
            case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
            {
                PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][26+idx], RoulettePlayerItemsCount[playerid][type][idx]);
                PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][26+idx], -45.0000, 0.0000, -45.0000, 1.0000);
                PlayerTextDrawShow(playerid, PTD_Roulette[playerid][26+idx]);
            }
        }
    }
	return 1;
}

Roulette_UpdateTD_HeaderButton(playerid, type)
{
    for(new i = 9; i != 6; i--)
    {
        PlayerTextDrawDestroy(playerid, PTD_Roulette[playerid][i]);

        if(i == 9)
            PTD_Roulette[playerid][9] = CreatePlayerTextDraw(playerid, 346.1997, 127.1242, type == 2 ? "flin_roulette:flin_roulette_gold_use" : "flin_roulette:flin_roulette_gold");
        if(i == 8)
            PTD_Roulette[playerid][8] = CreatePlayerTextDraw(playerid, 293.7998, 127.1242, type == 1 ? "flin_roulette:flin_roulette_silver_use" : "flin_roulette:flin_roulette_silver");
        if(i == 7)
            PTD_Roulette[playerid][7] = CreatePlayerTextDraw(playerid, 240.9998, 127.1242, type == 0 ? "flin_roulette:flin_roulette_bronze_use" : "flin_roulette:flin_roulette_bronze");

        PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][i], 53.0000, 38.0000);
        PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][i], 1);
        PlayerTextDrawColor(playerid, PTD_Roulette[playerid][i], -1);
        PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][i], 255);
        PlayerTextDrawFont(playerid, PTD_Roulette[playerid][i], 4);
        PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][i], 0);
        PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][i], 0);
        PlayerTextDrawSetSelectable(playerid, PTD_Roulette[playerid][i], true);

        PlayerTextDrawShow(playerid, PTD_Roulette[playerid][i]);
    }
}

Roulette_UpdateTD_Info(playerid, type)
{
    new str[64];
    if(p_temp[playerid][TextDrawRoulette] == false || type == -1) return SendError(playerid, "Произошла ошибка при обновлении информации, откройте рулетку заново.");
    format(str, sizeof(str), "Обновить за %d FM", RoulettePriceUpdate[type]);
    PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][5], str);
    format(str, sizeof(str), "%d", p_info[playerid][flinmoney]);
    PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][4], str);
    format(str, sizeof(str), "%d", GetInventoryAmount(playerid, TRANSFER_ITEMS+type+15));
    PlayerTextDrawSetString(playerid, PTD_Roulette[playerid][1], str);
    return 1;
}

Roulette_Render(playerid)
{
    for(new i = 6; i != -1; i--) PlayerTextDrawShow(playerid, PTD_Roulette[playerid][i]);
    for(new i = 25; i != 9; i--) PlayerTextDrawShow(playerid, PTD_Roulette[playerid][i]);
}

// 
PlayerMenu_UpdateTD_Item(playerid, type_item, item_id, item_name[], item_text[])
{
    if(type_item == PLAYER_MENU_TYPE_ICON)
    {
        new Float:td_item_pos_icon[10][2] =
        {
            {295.3999, 81.82640},
            {348.2000, 105.2220},
            {243.7998, 105.2220},
            {379.3998, 164.9552},
            {210.5998, 163.4618},
            {378.1998, 230.1640},
            {209.3999, 229.6663},
            {348.9999, 283.4263},
            {242.1999, 282.9285},
            {296.6000, 310.8039}
        };
        PlayerTextDrawDestroy(playerid, PTD_PlayerMenu[playerid][2+item_id]);

        PTD_PlayerMenu[playerid][2+item_id] = CreatePlayerTextDraw(playerid, td_item_pos_icon[item_id][0], td_item_pos_icon[item_id][1], item_name); // icons
        PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][2+item_id], 47.0000, 55.0000);
        PlayerTextDrawAlignment(playerid, PTD_PlayerMenu[playerid][2+item_id], 1);
        PlayerTextDrawColor(playerid, PTD_PlayerMenu[playerid][2+item_id], -1);
        PlayerTextDrawBackgroundColor(playerid, PTD_PlayerMenu[playerid][2+item_id], 255);
        PlayerTextDrawFont(playerid, PTD_PlayerMenu[playerid][2+item_id], 4);
        PlayerTextDrawSetProportional(playerid, PTD_PlayerMenu[playerid][2+item_id], 0);
        PlayerTextDrawSetShadow(playerid, PTD_PlayerMenu[playerid][2+item_id], 0);
        PlayerTextDrawSetSelectable(playerid, PTD_PlayerMenu[playerid][2+item_id], true);

        PlayerTextDrawHide(playerid, PTD_PlayerMenu[playerid][12+item_id]);
        PlayerTextDrawHide(playerid, PTD_PlayerMenu[playerid][22+item_id]);
        PlayerTextDrawShow(playerid, PTD_PlayerMenu[playerid][2+item_id]);
    }
    else
    {
        new Float:td_item_pos[10][2] =
        {
            {313.2000, 88.2974},
            {370.1998, 115.6752},
            {257.3996, 115.6752},
            {396.5994, 171.4264},
            {228.9996, 170.9286},
            {396.5994, 240.1197},
            {227.7996, 239.6217},
            {367.3992, 292.8841},
            {258.1994, 292.8840},
            {314.9996, 321.2575}
        };
        PlayerTextDrawDestroy(playerid, PTD_PlayerMenu[playerid][22+item_id]);

        PTD_PlayerMenu[playerid][22+item_id] = CreatePlayerTextDraw(playerid, td_item_pos[item_id][0], td_item_pos[item_id][1], item_name);
        PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][22+item_id], 9.0000, 11.0000);
        PlayerTextDrawAlignment(playerid, PTD_PlayerMenu[playerid][22+item_id], 1);
        PlayerTextDrawColor(playerid, PTD_PlayerMenu[playerid][22+item_id], -1);
        PlayerTextDrawBackgroundColor(playerid, PTD_PlayerMenu[playerid][22+item_id], 255);
        PlayerTextDrawFont(playerid, PTD_PlayerMenu[playerid][22+item_id], 4);
        PlayerTextDrawSetProportional(playerid, PTD_PlayerMenu[playerid][22+item_id], 0);
        PlayerTextDrawSetShadow(playerid, PTD_PlayerMenu[playerid][22+item_id], 0);

        PlayerTextDrawSetString(playerid, PTD_PlayerMenu[playerid][12+item_id], item_text);

        PlayerTextDrawShow(playerid, PTD_PlayerMenu[playerid][12+item_id]);
        PlayerTextDrawShow(playerid, PTD_PlayerMenu[playerid][22+item_id]);
        PlayerTextDrawHide(playerid, PTD_PlayerMenu[playerid][2+item_id]);
    }
}
// Service Tune
ServiceTune_UpdateTD_Axle(playerid)
{
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][5]);
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][6]);

    PTD_ServiceTune[playerid][5] = CreatePlayerTextDraw(playerid, 562.5999, 229.6661, !p_temp[playerid][p_listitem_int] ? "flin_sto:flin_sto_podveska_down" : "flin_sto:flin_sto_podveska_down_choose"); // нижняя ось
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][5], 51.0000, 29.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][5], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][5], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][5], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][5], true);

    PTD_ServiceTune[playerid][6] = CreatePlayerTextDraw(playerid, 562.5999, 189.8441, p_temp[playerid][p_listitem_int] ? "flin_sto:flin_sto_podveska_up" : "flin_sto:flin_sto_podveska_up_choose"); // верхняя ось
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][6], 51.0000, 29.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][6], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][6], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][6], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][6], 0);
    PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][6], true);

    PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][5]);
    PlayerTextDrawShow(playerid, PTD_ServiceTune[playerid][6]);
}

ServiceTune_HideTD_Colors(playerid)
{
    for(new i = 11; i != -1; i--) PlayerTextDrawDestroy(playerid, PTD_ServiceTune_Color[playerid][i]);
}

ServiceTune_UpdateTD_Colors(playerid, td_id = -1)
{
    STRING_GLOBAL[0] = EOS;
    if(td_id == -1)
    {
        for(new i = 11; i != -1; i--)
        {
            if(i == p_temp[playerid][p_listitem_int]) f(STRING_GLOBAL, "%sx", ServiceTune_Colors[i][st_Name]);
            else f(STRING_GLOBAL, "%s", ServiceTune_Colors[i][st_Name]);

            PTD_ServiceTune_Color[playerid][i] = CreatePlayerTextDraw(playerid, ServiceTune_Colors[i][st_TD_X], ServiceTune_Colors[i][st_TD_Y], STRING_GLOBAL); // test color
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune_Color[playerid][i], 54.0000, 64.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune_Color[playerid][i], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune_Color[playerid][i], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune_Color[playerid][i], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune_Color[playerid][i], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune_Color[playerid][i], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune_Color[playerid][i], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune_Color[playerid][i], true);

            PlayerTextDrawShow(playerid, PTD_ServiceTune_Color[playerid][i]);
        }
    }
    else
    {
        PlayerTextDrawDestroy(playerid, PTD_ServiceTune_Color[playerid][td_id]);
        if(td_id == p_temp[playerid][p_listitem_int]) f(STRING_GLOBAL, "%sx", ServiceTune_Colors[td_id][st_Name]);
        else f(STRING_GLOBAL, "%s", ServiceTune_Colors[td_id][st_Name]);
        PTD_ServiceTune_Color[playerid][td_id] = CreatePlayerTextDraw(playerid, ServiceTune_Colors[td_id][st_TD_X], ServiceTune_Colors[td_id][st_TD_Y], STRING_GLOBAL); // test color
        PlayerTextDrawTextSize(playerid, PTD_ServiceTune_Color[playerid][td_id], 54.0000, 64.0000);
        PlayerTextDrawAlignment(playerid, PTD_ServiceTune_Color[playerid][td_id], 1);
        PlayerTextDrawColor(playerid, PTD_ServiceTune_Color[playerid][td_id], -1);
        PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune_Color[playerid][td_id], 255);
        PlayerTextDrawFont(playerid, PTD_ServiceTune_Color[playerid][td_id], 4);
        PlayerTextDrawSetProportional(playerid, PTD_ServiceTune_Color[playerid][td_id], 0);
        PlayerTextDrawSetShadow(playerid, PTD_ServiceTune_Color[playerid][td_id], 0);
        PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune_Color[playerid][td_id], true);

        PlayerTextDrawShow(playerid, PTD_ServiceTune_Color[playerid][td_id]);
    }
}

ServiceTune_UpdateTD_TextCenter(playerid, Float:td_pos_y)
{
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][15]);
    PTD_ServiceTune[playerid][15] = CreatePlayerTextDraw(playerid, 321.9996, td_pos_y, "test~n~123"); // пусто
    PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][15], 0.4000, 1.6000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][15], 2);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][15], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][15], 1);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][15], 0);
}

ServiceTune_UpdateTD_Header(playerid, name_icon_service_td[], name_service_td[])
{
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][9]);

    PTD_ServiceTune[playerid][9] = CreatePlayerTextDraw(playerid, 67.4000, 175.9064, name_icon_service_td); // иконка заглавной
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][9], 26.0000, 32.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][9], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][9], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][9], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][9], 0);

    PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][10], name_service_td); // заглавный текст
}

ServiceTune_UpdateTD_Arrows(playerid, name_td_left[], name_td_right[])
{
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][16]);
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][17]);

    PTD_ServiceTune[playerid][16] = CreatePlayerTextDraw(playerid, 367.3998, 381.4884, name_td_left); // minus/left
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][16], 55.0000, 64.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][16], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][16], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][16], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][16], 0);
    PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][16], true);

    PTD_ServiceTune[playerid][17] = CreatePlayerTextDraw(playerid, 218.9996, 381.4887, name_td_right); // plus/right
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][17], 55.0000, 64.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][17], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][17], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][17], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][17], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][17], 0);
    PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][17], true);
}

ServiceTune_UpdateTD_Item(playerid, td_id, name_icon_item_td[], name_item_td[])
{
    PlayerTextDrawSetString(playerid, PTD_ServiceTune[playerid][15-td_id], name_item_td); // 1й слот

    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][td_id]);

    new Float:td_serivetunelist_pos[] = {353.1152, 308.8132, 264.5110, 220.2088};
    PTD_ServiceTune[playerid][td_id] = CreatePlayerTextDraw(playerid, 28.2000, td_serivetunelist_pos[td_id-1], name_icon_item_td);
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][td_id], 26.0000, 32.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][td_id], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][td_id], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][td_id], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][td_id], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][td_id], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][td_id], 0);
}

ServiceTune_UpdateTD_Closed(playerid, Float:td_pos_y)
{
    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][7]);

    PTD_ServiceTune[playerid][7] = CreatePlayerTextDraw(playerid, 573.7993, td_pos_y, "flin_sto:flin_sto_close"); // закрыть тд
    PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][7], 50.0000, 63.0000);
    PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][7], 1);
    PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][7], 255);
    PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][7], 4);
    PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][7], 0);
    PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][7], true);
}

this::ShowInventory(playerid)
{
    callcmd::inventory(playerid, "/0");
    return 1;
}
/*
forward Fix_ShowCraft(playerid);
public Fix_ShowCraft(playerid)
{
    callcmd::craft(playerid, "/0");
    return 1;
}
*/
