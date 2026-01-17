ShowRobberyFuel(playerid, type, idx = -1, first_parameter = -1)
{
    switch(type)
    {
        case ROBBERY_FUEL_NPC_1:
        {
            ShowPlayerDialog(playerid, D_ROB_FUEL_NPC_1, DIALOG_STYLE_LIST, ""I"Макавелли", "\
            "I"[1]"W" Информация об ограблениях\n\
            "I"[2]"W" Список контрактов\n\
            "I"[3]"W" Текущий контракт", "Далее", "Отмена");
        }
        case ROBBERY_FUEL_INFO:
        {
            ShowPlayerDialog(playerid, D_ROB_FUEL_INFO, DIALOG_STYLE_MSGBOX, ""I"Макавелли", ""W"\
            Привет! Меня зовут "I"Макавелли,"W" я — "I"информатор,"W" который имеет глаза во всех спец. службах и без какого-либо труда, подскажу\n\
            что и где плохо лежит.\n\n\
            Я готов предоставить тебе информацию о АЗС, которые можно ограбить, но за это тебе "I"придётся заплатить."W"\n\n\
            Ограбить АЗС не так-то просто, ты не сможешь ограбить его сам, тебе понадобится "I"3 подельника."W"\n\n\
            После передачи информации, необходимо будет приобрести предметы для ограбления и арендовать транспортное средство.\n\
            Координаты где это можно будет сделать, ты получишь после оплаты контракта.\n\n\
            Контракты делятся на два типа — "I"обычный и премиальный."W" Обычный доступен всем игрокам, а премиальный — только для\n\
            игроков, обладающих "I"VIP Gold."W" В премиальных контрактах есть возможность переносить "I"в два раза больше топлива в канистрах."W"\n\n\
            Приобрести контракт можно с "I"12:00"W" до "I"22:00."W" Они появляются каждый час.\n\n\
            Процесс ограбления довольно сложный, ибо во всех АЗС есть сигнализация и при установке насоса она сработает. Это\n\
            можно избежать, но тебе нужно будет хорошо спланировать ограбление и обзавестись "I"всеми необходимыми предметами."W"\n\n\
            После начала ограбления, тебе и твоим подельникам предстоит сливать топливо с АЗС в канистры, а затем погрузить его\n\
            в транспортное средство.\n\n\
            По завершению ограбления необходимо перевести всё награбленное топливо на нефтебазу и продать его.", "Закрыть", "");
        }
        case ROBBERY_FUEL_LIST:
        {
            if(p_temp[playerid][rob_fuel_idx] != -1) return ShowRobberyFuel(playerid, ROBBERY_FUEL_NPC_1), SendError(playerid, "Вы уже участвуете в ограблении АЗС.");
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            new count;
            STRING_GLOBAL = "[#] Тип контракта\tСтоимость\n";
            for(new i = 0; i < MAX_ROBBERY_FUEL_CONTRACT; i++)
            {
                if(RobberyFuelContract[i][rfcStatus] != 1) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d$\n", STRING_GLOBAL, count + 1, RobberyFuelContract[i][rfcType] == 0 ? "Обычный" : "{"#cYELLOW"}Премиальный"W"", RobberyFuelContract[i][rfcPrice]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0)
            {
                SendError(playerid, "На данный момент нет контрактов, они появляются каждый час.");
                return ShowRobberyFuel(playerid, ROBBERY_FUEL_NPC_1);
            }
            ShowPlayerDialog(playerid, D_ROB_FUEL_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список контрактов", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_FUEL_CONTRACT:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Тип: %s\n\
            Стоимость: {"#cGREEN"}%d$"W"\n\
            Местоположение: {"#cGRAY"}%s", RobberyFuelContract[idx][rfcType] == 0 ? "Обычный" : "{"#cYELLOW"}Премиальный"W"", RobberyFuelContract[idx][rfcPrice], b_info[RobberyFuelContract[idx][rfcFuelIDx]][_name]);
            ShowPlayerDialog(playerid, D_ROB_FUEL_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Информация о контракте", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "RobberyFuel:idx", idx);
        }
        case ROBBERY_FUEL_CONTRACT_START:
        {
            ShowPlayerDialog(playerid, D_ROB_FUEL_CONTRACT_START, DIALOG_STYLE_MSGBOX, ""I"Пояснение к контракту", ""W"\
            В случае неудачного ограбления, денежные средства тебе "I"никто не вернет!"W"\n\n\
            На выполнение контракта отводится "I"1 час,"W" не затягивай!\n\n\
            Если ты согласен со всеми условиями, нажми "I"\"Далее\"."W" После этого с тебя\n\
            "I"спишутся деньги"W" за контракт и ты сможешь пригласить в ограбление до "I"3-х\n\
            подельников"W" с помощью команды "I"/robbing\n\n\
            {"#cLIGHTRED"}Обратите внимание! Исход ограбления зависит только от тебя!", "Далее", "Отмена");
        }
        case ROBBERY_FUEL_CONTRACT_INFO:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Время до завершения контракта: "I"%s"W"\n\
            Тип ограбления: %s\n\
            Название АЗС: "I"%s"W"\n\
            Стоимость контракта: "I"%d$"W"\n\n\
            Машина для ограбления: %s", ConvertTime(RobberyFuelContract[idx][rfcTime]), RobberyFuelContract[idx][rfcType] == 0 ? "{"#cGREEN"}Обычный"W"" : "{"#cYELLOW"}Премиальный"W"", b_info[RobberyFuelContract[idx][rfcFuelIDx]][_name], RobberyFuelContract[idx][rfcPrice], RobberyFuelContract[idx][rfcVehicleIDx] == INVALID_VEHICLE_ID ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
            ShowPlayerDialog(playerid, D_ROB_FUEL_CONTRACT_INFO, DIALOG_STYLE_MSGBOX, ""I"Текущий контракт", STRING_GLOBAL, "Закрыть", "");
        }
        case ROBBERY_FUEL_MENU:
        {
            if(p_temp[playerid][rob_fuel_idx] == -1)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.5, 1413.4436,-1487.6085,20.4344)) ShowRobberyFuel(playerid, ROBBERY_FUEL_NPC_1);
                SendError(playerid, "У Вас нет активного контракта.");
                return 1;
            }
            ShowPlayerDialog(playerid, D_ROB_FUEL_MENU, DIALOG_STYLE_TABLIST_HEADERS, ""I"Меню ограбления", "\
            [#] Название\tПредназначение\n\
            "I"[1]"W" Информация о контракте\n\
            "I"[2]"W" Информация о текущих участниках ограбления\n\
            "I"[3]"W" Использовать предметы\n\
            "I"[4]"W" Найти Макавелли\tГлава\n\
            "I"[5]"W" Найти Криса\tВодитель\n\
            "I"[6]"W" Найти Сантьяго\tОружейный барон\n\
            "I"[7]"W" Найти Дрейка\tЗаправщик\n\
            "I"[8]"W" Найти Эндрю\tВсе\n\
            "I"[9]"W" Найти АЗС\n\
            {"#cYELLOW"}[10] Использовать канистру"W"\tВсе\n\
            {"#cGREEN"}[11] Начать ограбление"W"\tГлава\n\
            "I"[12]"W" Список награбленного\n\
            "I"[13]"W" Продлить контракт\n\
            "I"[14]"W" Найти потерянную канистру\n\
            "I"[15]"W" Покинуть ограбление\n\
            {"#cLIGHTRED"}[16] Завершить контракт", "Далее", "Отмена");
        }
        case ROBBERY_FUEL_PLAYER:
        {
            STRING_GLOBAL[0] = EOS;
            new scdplayerid, temp_name[MAX_PLAYER_NAME];
            for(new i = 0; i < MAX_ROBBERY_FUEL_PLAYER; i++)
            {
                scdplayerid = RobberyFuelContract[idx][rfcPlayerID][i];
                if(scdplayerid != INVALID_PLAYER_ID) f(temp_name, "%s", get_name(scdplayerid));
                else temp_name = "Нет";
                f(STRING_GLOBAL, "%s"W"%s [%d] — %s\n\n", STRING_GLOBAL, RobberyFuelPlayer[i][rfpName], i + 1, temp_name);
            }
            strcat(STRING_GLOBAL, "\
            Ограбить АЗС можно только с командой, ты можешь позвать до 4-х подельников,\n\
            если ты хочешь позвать их, введи их ID в строке ниже и должность через запятую,\n\
            но отменить это действие невозможно.");
            ShowPlayerDialog(playerid, D_ROB_FUEL_PLAYER, DIALOG_STYLE_INPUT, ""I"Информация о текущих участниках ограбления", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_FUEL_USE:
        {
            STRING_GLOBAL = "[#] Название\tНаличие\tПредназначение\n";
            new temp_rob_fuel_rank, scdplayerid, str[128];
            for(new i = 0; i < MAX_ROBBERY_FUEL_ITEMS_START; i++)
            {
                temp_rob_fuel_rank = RobberyFuelItemsStart[i][rfiType];
                scdplayerid = RobberyFuelContract[idx][rfcPlayerID][temp_rob_fuel_rank];
                if(scdplayerid == INVALID_PLAYER_ID) str = "Все";
                else f(str, "%s", get_name(scdplayerid));
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%s\n", STRING_GLOBAL, i + 1, RobberyFuelItemsStart[i][rfiName], RobberyFuelContract[idx][rfcItemsStart][i] == 0 ? "{"#cLIGHTRED"}Не имеется"W"" : "{"#cGREEN"}Имеется"W"", str);
            }
            ShowPlayerDialog(playerid, D_ROB_FUEL_USE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Использовать предметы", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_FUEL_START:
        {
            ShowPlayerDialog(playerid, D_ROB_FUEL_START, DIALOG_STYLE_MSGBOX, ""I"Начать ограбление", ""W"\
            Вы действительно хотите начать ограбление?\n\n\
            После начала, участники ограбления должны будут использовать купленные предметы и слить топливо с АЗС.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Отменить это действие невозможно.", "Да", "Нет");
            return 1;
        }
        case ROBBERY_FUEL_ITEMS_LIST:
        {
            STRING_GLOBAL = ""W"";
            if(RobberyFuelContract[idx][rfcVehicleIDx] != INVALID_VEHICLE_ID)
            {
                f(STRING_GLOBAL, "%sВ машине:\n— %d литров топлива\n\n", STRING_GLOBAL, RobberyFuelContract[idx][rfcVehicleItems]);
            }
            new scdplayerid;
            for(new i = 0; i < MAX_ROBBERY_FUEL_PLAYER; i++)
            {
                scdplayerid = RobberyFuelContract[idx][rfcPlayerID][i];
                if(scdplayerid == INVALID_PLAYER_ID) continue;
                f(STRING_GLOBAL, "%sУ %s %d литров топлива\n", STRING_GLOBAL, get_name(scdplayerid), p_temp[scdplayerid][rob_fuel_backup_items][0]);
            }
            strcat(STRING_GLOBAL, "\n{"#cLIGHTRED"}\
            Обратите внимание! При выходе из игры с топливом или при смерти все топливом будет утеряно!\n\
            Обратите внимание! Транспортное средство могут конфисковать сотрудники полицейского департамента!");
            ShowPlayerDialog(playerid, D_ROB_FUEL_ITEMS_LIST, DIALOG_STYLE_MSGBOX, ""I"Список награбленного", STRING_GLOBAL, "Отмена", "");
        }
        case ROBBERY_FUEL_EXTEND_CONTRACT:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Если по каким-то причинам ты не успеваешь выполнить контракт, можешь его продлить,\n\
            но обойдется тебе это в "I"%d$."W"\n\n\
            Вы действительно хотите продлить контракт?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Продлить контракт можно 1 раз!"W"", RobberyFuelContract[idx][rfcPrice] / 2);
            ShowPlayerDialog(playerid, D_ROB_FUEL_EXTEND_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Продлить контракт", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_FUEL_LEAVE:
        {
            ShowPlayerDialog(playerid, D_ROB_FUEL_LEAVE, DIALOG_STYLE_MSGBOX, ""I"Покинуть ограбление", ""W"\
            Вы действительно хотите покинуть ограбление?\n\
            Топливо, которые находится в Вашей канистре будет утеряно.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Отменить это действие будет невозможно!", "Да", "Нет");
        }
        case ROBBERY_FUEL_DELETE:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите завершить контракт на ограбление?\n\n\
            Ваш бонус за скрытность составил: "I"%d$."W"\n\n\
            Доля каждого составит: "I"%d$.", GetRobberyFuelSecrecy(idx), GetRobberyFuelShare(idx));
            ShowPlayerDialog(playerid, D_ROB_FUEL_DELETE, DIALOG_STYLE_MSGBOX, ""I"Завершить контракт", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_FUEL_NPC_BUY:
        {
            if(p_temp[playerid][rob_fuel_rank] != idx) return SendError(playerid, "Вы не являетесь поддельником в ограблении АЗС на должности \"%s\".", RobberyFuelPlayer[idx][rfpName]);
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            new count;
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < MAX_ROBBERY_FUEL_ITEMS_START; i++)
            {
                if(RobberyFuelItemsStart[i][rfiType] != idx) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, count + 1, RobberyFuelItemsStart[i][rfiName]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_ROB_FUEL_NPC_BUY, DIALOG_STYLE_LIST, ""I"Предметы для ограбления", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "RobberyFuel:items_idx", idx);
        }
        case ROBBERY_FUEL_NPC_BUY_ACT:
        {
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Название предмета: "I"%s"W"\n\n\
            Описание:\n\n\
            %s\n\n\
            Стоимость: "I"%d$"W"\n\n\
            Вы действительно хотите приобрести данный предмет?", RobberyFuelItemsStart[first_parameter][rfiName], RobberyFuelItemsStart[first_parameter][rfiInfo], RobberyFuelItemsStart[first_parameter][rfiPrice]);
            STRING_MIN[0] = EOS;
            f(STRING_MIN, ""I"%s", RobberyFuelItemsStart[first_parameter][rfiName]);
            ShowPlayerDialog(playerid, D_ROB_FUEL_NPC_BUY_ACT, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Да", "Нет");
            SetPVarInt(playerid, "RobberyFuel:items_buy", first_parameter);
        }
        case ROBBERY_FUEL_NPC_2:
        {
            if(p_temp[playerid][rob_fuel_rank] != 2) return SendError(playerid, "Вы не являетесь поддельником в ограблении АЗС на должности \"%s\".", RobberyFuelPlayer[2][rfpName]);
            ShowPlayerDialog(playerid, D_ROB_FUEL_NPC_2, DIALOG_STYLE_LIST, ""I"Крис", ""I"[1]"W" Арендовать фургон\n"I"[2]"W" Предметы для ограбления", "Далее", "Отмена");
        }
        case ROBBERY_FUEL_NPC_2_R_VEHICLE:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите арендовать транспортное средство \"%s\" для ограбления за %d$?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Остерегайтесь сотрудников полицейского департамента, они могут нейтрализовать его!", GetVehicleName(INVALID_VEHICLE_ID, MODEL_ROBBERY_VEHICLE), RENT_PRICE_ROBBERY_B_VEHICLE);
            ShowPlayerDialog(playerid, D_ROB_FUEL_NPC_2_RENT_VEHICLE, DIALOG_STYLE_MSGBOX, ""I"Арендовать транспортное средство", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_FUEL_NPC_3:
        {
            if(p_temp[playerid][rob_fuel_backup] == 0) return SendError(playerid, "У Вас нет канистры.");
            new temp_rob_fuel_liters = p_temp[playerid][rob_fuel_backup_items][0];
            if(temp_rob_fuel_liters == 0) return SendError(playerid, "В Вашей канистре ничего нет.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Вы действительно хотите сбыть %d литров топлива?", temp_rob_fuel_liters);
            ShowPlayerDialog(playerid, D_ROB_FUEL_NPC_3, DIALOG_STYLE_MSGBOX, ""I"Джек", STRING_GLOBAL, "Да", "Нет");
        }
    }
    return 1;
}

SendRobberyFuelMessage(rob_id, color, string[])
{
    foreach(new i:Player)
    {
        if(p_temp[i][rob_fuel_idx] == rob_id)
        {
            SendMes(i, color, string);
        }
    }
    return 1;
}

LoadRobberyFuel()
{
    CreateActor(8, 1661.3865,-1394.4701,13.5469,180.0000);
    CreateDynamic3DTextLabel("NPC: "I"Макавелли", COLOR_WHITE, 1661.3865,-1394.4701,13.5469 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(50, 2199.0400,-1972.5449,13.5581,180.1580);
    CreateDynamic3DTextLabel("NPC: "I"Крис", COLOR_WHITE, 2199.0400,-1972.5449,13.5581 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(188, 827.0447,-1346.6532,13.5398,91.4838);
    CreateDynamic3DTextLabel("NPC: "I"Сантьяго", COLOR_WHITE, 827.0447,-1346.6532,13.5398 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(249, -1020.4516,-697.2528,32.0126,0.0000);
    CreateDynamic3DTextLabel("NPC: "I"Дрейк", COLOR_WHITE, -1020.4516,-697.2528,32.0126 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(101, 287.8708,1398.3359,10.5859,91.0208);
    CreateDynamic3DTextLabel("NPC: "I"Эндрю", COLOR_WHITE, 287.8708,1398.3359,10.5859 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_fuel_area[0] = CreateDynamicSphere(1661.4196,-1395.1777,13.5469, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_fuel_area[0], TYPE_ROB_FUEL, AREA_SUBTYPE_ROB_FUEL_NPC_1);
    CreatePickup(1239, 23, 1661.4196,-1395.1777,13.5469);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1661.4196,-1395.1777,13.5469, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_fuel_area[1] = CreateDynamicSphere(2199.0745,-1973.2469,13.5581, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_fuel_area[1], TYPE_ROB_FUEL, AREA_SUBTYPE_ROB_FUEL_NPC_2);
    CreatePickup(1239, 23, 2199.0745,-1973.2469,13.5581);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 2199.0745,-1973.2469,13.5581, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_fuel_area[2] = CreateDynamicSphere(826.3442,-1346.7013,13.5334, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_fuel_area[2], TYPE_ROB_FUEL, AREA_SUBTYPE_ROB_FUEL_NPC_3);
    CreatePickup(1239, 23, 826.3442,-1346.7013,13.5334);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 826.3442,-1346.7013,13.5334, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_fuel_area[3] = CreateDynamicSphere(-1020.4773,-696.5507,32.0078, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_fuel_area[3], TYPE_ROB_FUEL, AREA_SUBTYPE_ROB_FUEL_NPC_4);
    CreatePickup(1239, 23, -1020.4773,-696.5507,32.0078);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, -1020.4773,-696.5507,32.0078, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_fuel_area[4] = CreateDynamicSphere(287.1633,1398.2845,10.5859, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_fuel_area[4], TYPE_ROB_FUEL, AREA_SUBTYPE_ROB_FUEL_NPC_5);
    CreatePickup(1239, 23, 287.1633,1398.2845,10.5859);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 287.1633,1398.2845,10.5859, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

CMD:load_fcontract(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 10) return 1;

    for(new i = 0; i < MAX_ROBBERY_FUEL_CONTRACT; i++)
    {
        if(RobberyFuelContract[i][rfcStatus] == 0) CreateRobberyFuelContract(i);
    }

    SendAccess(playerid, "Вы создали максимальное количество контрактов для ограбления АЗС.");
    return 1;
}

CheckRobberyFuelContract()
{
    new scdplayerid, money;
    for(new i = 0, idx = 0; i < MAX_ROBBERY_FUEL_CONTRACT; i++)
    {
        if(RobberyFuelContract[i][rfcStatus] > 1)
        {
            RobberyFuelContract[i][rfcTime]--;
            if(RobberyFuelContract[i][rfcTime] == 0)
            {
                money = GetRobberyFuelShare(i);
                for(idx = 0; idx < MAX_ROBBERY_FUEL_PLAYER; idx++)
                {
                    scdplayerid = RobberyFuelContract[i][rfcPlayerID][idx];
                    if(scdplayerid != INVALID_PLAYER_ID)
                    {
                        RobberyFuelContract[i][rfcPlayerID][idx] = INVALID_PLAYER_ID;
                        ClearRobberyFuel(scdplayerid, 1);
                        ClearRobberyFuelBackup(scdplayerid, 1);
                        SetPlayerSkinEx(scdplayerid);
                        maskOFF(scdplayerid);
                        SetPlayerMoney(scdplayerid, money, true, "завершено время ограбления АЗС");
                        RobbingInfoForMoney[5] += money;
                        SendInfo(scdplayerid, "Время на выполнение контракта вышло.");
                        SendInfo(scdplayerid, "Вы заработали: %d$.", money);
                    }
                }
                DestroyRobberyFuelContract(i);
            }
        }
    }
    return 1;
}

CheckRobberyFuelContractList()
{
    new count, max_count = random(2);
    for(new i = 0; i < MAX_ROBBERY_FUEL_CONTRACT; i++)
    {
        if(RobberyFuelContract[i][rfcStatus] == 0)
        {
            CreateRobberyFuelContract(i);
            count++;
        }
        if(count == max_count) break;
    }
    return 1;
}

CreateRobberyFuelContract(idx)
{
    new i = GetFreeRobberyFuel();
    if(i == -1) return 1;
    new rob_fuel_type[8] = {1, 1, 2, 2, 2, 2, 2, 2};
    RobberyFuelContract[idx][rfcStatus] = 1;
    RobberyFuelContract[idx][rfcType] = rob_fuel_type[random(6)];
    RobberyFuelContract[idx][rfcFuelIDx] = i;
    RobberyFuelContract[idx][rfcFuelSignaling] = 0;
    RobberyFuelContract[idx][rfcVehicleIDx] = INVALID_VEHICLE_ID;
    RobberyFuelContract[idx][rfcVehicleNumber] = 0;
    RobberyFuelContract[idx][rfcVehicleItems] = 0;
    RobberyFuelContract[idx][rfcAnticall] = 0;
    RobberyFuelContract[idx][rfcSecrecy] = 0;
    for(new x = 0; x < MAX_ROBBERY_FUEL_ITEMS_START; x++)
    {
        RobberyFuelContract[idx][rfcItemsStart][x] = 0;
        if(x < MAX_ROBBERY_FUEL_PLAYER) RobberyFuelContract[idx][rfcPlayerID][x] = INVALID_PLAYER_ID;
    }
    RobberyFuelContract[idx][rfcPrice] = 50000;
    RobberyFuelContract[idx][rfcTime] = 0;
    RobberyFuelContract[idx][rfcTimeUpdate] = 0;
    RobberyFuelContract[idx][rfcOwnerID] = INVALID_MYSQL_ID;
    RobberyFuelContract[idx][rfcKush] = 0;

    b_info[i][_robbery] = 1;
    return 1;
}

DestroyRobberyFuelContract(idx)
{
    RobberyFuelContract[idx][rfcStatus] = 0;
    RobberyFuelContract[idx][rfcType] = 0;
    new fuelid = RobberyFuelContract[idx][rfcFuelIDx];
    RobberyFuelContract[idx][rfcFuelIDx] = 0;
    RobberyFuelContract[idx][rfcFuelSignaling] = 0;
    if(RobberyFuelContract[idx][rfcVehicleIDx] != INVALID_VEHICLE_ID) DestroyVehicleVEx(RobberyFuelContract[idx][rfcVehicleIDx]);
    RobberyFuelContract[idx][rfcVehicleIDx] = INVALID_VEHICLE_ID;
    RobberyFuelContract[idx][rfcVehicleNumber] = 0;
    RobberyFuelContract[idx][rfcVehicleItems] = 0;
    RobberyFuelContract[idx][rfcAnticall] = 0;
    RobberyFuelContract[idx][rfcSecrecy] = 0;
    for(new x = 0; x < MAX_ROBBERY_FUEL_ITEMS_START; x++)
    {
        RobberyFuelContract[idx][rfcItemsStart][x] = 0;
        if(x < MAX_ROBBERY_FUEL_PLAYER) RobberyFuelContract[idx][rfcPlayerID][x] = INVALID_PLAYER_ID;
    }
    RobberyFuelContract[idx][rfcPrice] = 0;
    RobberyFuelContract[idx][rfcTime] = 0;
    RobberyFuelContract[idx][rfcTimeUpdate] = 0;
    RobberyFuelContract[idx][rfcOwnerID] = INVALID_MYSQL_ID;
    RobberyFuelContract[idx][rfcKush] = 0;

    b_info[fuelid][_robbery] = 0;
    return 1;
}

GetFreeRobberyFuel()
{
    new fuel_checked = -1;
    for(new i = totalbizz - 1; i != -1; i--)
    {
        fuel_checked = random(totalbizz);
        if(b_info[fuel_checked][_tip] != 4) continue;
        if(b_info[fuel_checked][_robbery] == 0) return fuel_checked;
    }
    return -1;
}

GetRobberyFuelSecrecy(idx)
{
    new kush;
    if(RobberyFuelContract[idx][rfcFuelSignaling] == 0)
    {
        if(RobberyFuelContract[idx][rfcSecrecy] == 1)
        {
            kush = RobberyFuelContract[idx][rfcKush];
            if(kush == 0) return 0;
            else return floatround(kush * 0.20);
        }
    }
    return 0;
}

GetRobberyFuelShare(idx)
{
    new count;
    for(new i = 0; i < MAX_ROBBERY_FUEL_PLAYER; i++)
    {
        if(RobberyFuelContract[idx][rfcPlayerID][i] != INVALID_PLAYER_ID) count++;
    }
    new kush = RobberyFuelContract[idx][rfcKush] + GetRobberyFuelSecrecy(idx);
    if(kush == 0) return 0;
    else return kush / count;
}

ClearRobberyFuel(playerid, type = -1)
{
    p_temp[playerid][rob_fuel_idx] = -1;
    p_temp[playerid][rob_fuel_backup] = 0;
    p_temp[playerid][rob_fuel_backup_items][0] = 0;
    p_temp[playerid][rob_fuel_timer] = 0;
    p_temp[playerid][rob_fuel_timer_max] = 0;
    if(type != -1)
    {
        for(new i = 0; i < 10; i++) if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
    }
    return 1;
}

ClearRobberyFuelBackup(playerid, type = -1)
{
    p_temp[playerid][rob_fuel_backup_items][1] = 0;
    if(type != -1)
    {
        if(p_temp[playerid][rob_fuel_backup_pickup] != -1) DestroyDynamicPickup(p_temp[playerid][rob_fuel_backup_pickup]);
        if(p_temp[playerid][rob_fuel_backup_area] != -1) DestroyDynamicArea(p_temp[playerid][rob_fuel_backup_area]);
    }
    p_temp[playerid][rob_fuel_backup_pickup] = -1;
    p_temp[playerid][rob_fuel_backup_area] = -1;
    p_temp[playerid][rob_fuel_backup_pos][0] =
    p_temp[playerid][rob_fuel_backup_pos][1] =
    p_temp[playerid][rob_fuel_backup_pos][2] = 0.0;
    return 1;
}

GetPlayerRobberyFuel(playerid)
{
    for(new i = 0; i < MAX_ROBBERY_FUEL_CONTRACT; i++)
    {
        if(RobberyFuelContract[i][rfcOwnerID] == p_info[playerid][ID])
        {
            RobberyFuelContract[i][rfcPlayerID][0] = playerid;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "[ROBBERY] %s [%d] в игре.", get_name(playerid), playerid);
            SendRobberyFuelMessage(i, 0xDEB887FF, STRING_GLOBAL);
            p_temp[playerid][rob_fuel_idx] = i;
            p_temp[playerid][rob_fuel_rank] = 0;
            if(RobberyFuelContract[i][rfcStatus] == 3) p_temp[playerid][rob_fuel_backup] = 1;
            return i;
        }
    }
    return -1;
}

CallingPoliceToRobberyFuel(idx, fuelid)
{
    SendRobberyFuelMessage(idx, 0xDEB887FF, "[ROBBERY] На АЗС сработала сигнализация, сообщение отправлено сотрудникам полицейского департамента!");
    RobberyFuelContract[idx][rfcFuelSignaling] = 1;
    foreach(new i : gFactionPlayers[FBI_TEAM || POLICE_LS || POLICE_SF || POLICE_LV || POLICE_RC])
    {
        if(p_info[i][fwork] == true)
        {
            SendMes(i, COLOR_DARKORANGE, "[ОГРАБЛЕНИЕ АЗС]: "W"Грабители на АЗС %s, остановите грабителей! Место отмечено на GPS!", b_info[fuelid][_name]);
            SetPlayerGPS(i, b_info[fuelid][b_enter][0], b_info[fuelid][b_enter][1], b_info[fuelid][b_enter][2], 5.0);
        }
    }
    new scdplayerid;
    for(new i = 0; i < MAX_ROBBERY_FUEL_PLAYER; i++)
    {
        scdplayerid = RobberyFuelContract[idx][rfcPlayerID][i];
        if(scdplayerid != INVALID_PLAYER_ID)
        {
            if(p_info[scdplayerid][wanted] < 6)
            {
                p_info[scdplayerid][wanted] = 6;
                SetPlayerWantedLevel(scdplayerid, p_info[scdplayerid][wanted]);
                SendInfo(scdplayerid, "В АЗС сработала сигнализация, Вы объявлены в розыск.");
            }
        }
    }
    return 1;
}