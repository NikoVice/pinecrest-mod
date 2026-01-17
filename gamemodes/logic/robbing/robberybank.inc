ShowRobberyBank(playerid, type, idx = -1, first_parameter = -1)
{
    switch(type)
    {
        case ROBBERY_BANK_NPC_1:
        {
            ShowPlayerDialog(playerid, D_ROB_BANK_NPC_1, DIALOG_STYLE_LIST, ""I"Вилли", "\
            "I"[1]"W" Информация об ограблениях\n\
            "I"[2]"W" Список контрактов\n\
            "I"[3]"W" Текущий контракт", "Далее", "Отмена");
        }
        case ROBBERY_BANK_INFO:
        {
            ShowPlayerDialog(playerid, D_ROB_BANK_INFO, DIALOG_STYLE_MSGBOX, ""I"Вилли", ""W"\
            Привет! Меня зовут "I"Вилли,"W" я — "I"информатор,"W" который имеет глаза во всех спец. службах и без какого-либо труда, подскажу\n\
            что и где плохо лежит.\n\n\
            Я готов предоставить тебе информацию о банках, которые можно ограбить, но за это тебе "I"придётся заплатить."W"\n\n\
            Ограбить банк не так-то просто, ты не сможешь ограбить его сам, тебе понадобится "I"4 подельника."W"\n\n\
            После передачи информации, необходимо будет приобрести предметы для ограбления и арендовать транспортное\n\
            средство. Координаты где это можно будет сделать, ты получишь после оплаты контракта.\n\n\
            Контракты делятся на два типа — "I"обычный и премиальный."W" Обычный доступен всем игрокам, а премиальный — только\n\
            для игроков, обладающих "I"VIP Gold."W" В премиальных контрактах есть возможность "I"кражи золотых слитков."W"\n\n\
            Приобрести контракт можно с "I"12:00"W" до "I"22:00."W" Они появляются каждый час.\n\n\
            Процесс ограбления довольно сложный, ибо во всех банках есть сигнализация и при взломе хранилища она сработает.\n\
            Это можно избежать, но тебе нужно будет хорошо спланировать ограбление и обзавестись "I"всеми необходимыми предметами."W"\n\n\
            После начала ограбления, тебе и твоим подельникам собирать деньги и золотые слитки в сумки, а затем погрузить в\n\
            транспортное средство.\n\n\
            По завершению ограбления необходимо перевести всё награбленное на пирс и продать его.\n\n\
            Золотые слитки стоят хороших денег, постарайся перенести их как можно больше, если хочешь неплохо подзаработать.", "Закрыть", "");
        }
        case ROBBERY_BANK_LIST:
        {
            if(p_temp[playerid][rob_bank_idx] != -1) return ShowRobberyBank(playerid, ROBBERY_BANK_NPC_1), SendError(playerid, "Вы уже участвуете в ограблении банка.");
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            new count;
            STRING_GLOBAL = "[#] Тип контракта\tСтоимость\n";
            for(new i = 0; i < MAX_ROBBERY_BANK_CONTRACT; i++)
            {
                if(RobberyBankContract[i][rbcStatus] != 1) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d$\n", STRING_GLOBAL, count + 1, RobberyBankContract[i][rbcType] == 0 ? "Обычный" : "{"#cYELLOW"}Премиальный"W"", RobberyBankContract[i][rbcPrice]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0)
            {
                SendError(playerid, "На данный момент нет контрактов, они появляются каждый час.");
                return ShowRobberyBank(playerid, ROBBERY_BANK_NPC_1);
            }
            ShowPlayerDialog(playerid, D_ROB_BANK_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список контрактов", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_BANK_CONTRACT:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Тип: %s\n\
            Стоимость: {"#cGREEN"}%d$"W"\n\
            Местоположение: {"#cGRAY"}%s", RobberyBankContract[idx][rbcType] == 0 ? "Обычный" : "{"#cYELLOW"}Премиальный"W"", RobberyBankContract[idx][rbcPrice], BankInfo[RobberyBankContract[idx][rbcBankIDx]][bName]);
            ShowPlayerDialog(playerid, D_ROB_BANK_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Информация о контракте", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "RobberyBank:idx", idx);
        }
        case ROBBERY_BANK_CONTRACT_START:
        {
            ShowPlayerDialog(playerid, D_ROB_BANK_CONTRACT_START, DIALOG_STYLE_MSGBOX, ""I"Пояснение к контракту", ""W"\
            В случае неудачного ограбления, денежные средства тебе "I"никто не вернет!"W"\n\n\
            На выполнение контракта отводится "I"1 час,"W" не затягивай!\n\n\
            Если ты согласен со всеми условиями, нажми "I"\"Далее\"."W" После этого с тебя\n\
            "I"спишутся деньги"W" за контракт и ты сможешь пригласить в ограбление до "I"5-ти\n\
            подельников"W" с помощью команды "I"/robbing\n\n\
            {"#cLIGHTRED"}Обратите внимание! Исход ограбления зависит только от тебя!", "Далее", "Отмена");
        }
        case ROBBERY_BANK_CONTRACT_INFO:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Время до завершения контракта: "I"%s"W"\n\
            Тип ограбления: %s\n\
            Местоположение: "I"%s"W"\n\
            Стоимость контракта: "I"%d$"W"\n\n\
            Машина для ограбления: %s", ConvertTime(RobberyBankContract[idx][rbcTime]), RobberyBankContract[idx][rbcType] == 0 ? "{"#cGREEN"}Обычный"W"" : "{"#cYELLOW"}Премиальный"W"", BankInfo[RobberyBankContract[idx][rbcBankIDx]][bName], RobberyBankContract[idx][rbcPrice], RobberyBankContract[idx][rbcVehicleIDx] == INVALID_VEHICLE_ID ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
            ShowPlayerDialog(playerid, D_ROB_BANK_CONTRACT_INFO, DIALOG_STYLE_MSGBOX, ""I"Текущий контракт", STRING_GLOBAL, "Закрыть", "");
        }
        case ROBBERY_BANK_MENU:
        {
            if(p_temp[playerid][rob_bank_idx] == -1)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.5, 1413.4436,-1487.6085,20.4344)) ShowRobberyBank(playerid, ROBBERY_BANK_NPC_1);
                SendError(playerid, "У Вас нет активного контракта.");
                return 1;
            }
            ShowPlayerDialog(playerid, D_ROB_BANK_MENU, DIALOG_STYLE_TABLIST_HEADERS, ""I"Меню ограбления", "\
            [#] Название\tПредназначение\n\
            "I"[1]"W" Информация о контракте\n\
            "I"[2]"W" Информация о текущих участниках ограбления\n\
            "I"[3]"W" Использовать предметы\n\
            "I"[4]"W" Найти Вилли\tГлава\n\
            "I"[5]"W" Найти Роберта\tОружейник\n\
            "I"[6]"W" Найти Майкла\tВодитель\n\
            "I"[7]"W" Найти Джона\tРазработчик\n\
            "I"[8]"W" Найти Доминика\tШухер\n\
            "I"[9]"W" Найти Джека\tВсе\n\
            "I"[10]"W" Найти банк\n\
            {"#cYELLOW"}[11] Использовать сумку"W"\tВсе\n\
            {"#cGREEN"}[12] Начать ограбление"W"\tГлава\n\
            "I"[13]"W" Список награбленного\n\
            "I"[14]"W" Продлить контракт\n\
            "I"[15]"W" Найти потерянную сумку\n\
            "I"[16]"W" Покинуть ограбление\n\
            {"#cLIGHTRED"}[17] Завершить контракт", "Далее", "Отмена");
        }
        case ROBBERY_BANK_PLAYER:
        {
            STRING_GLOBAL[0] = EOS;
            new scdplayerid, temp_name[MAX_PLAYER_NAME];
            for(new i = 0; i < MAX_ROBBERY_BANK_PLAYER; i++)
            {
                scdplayerid = RobberyBankContract[idx][rbcPlayerID][i];
                if(scdplayerid != INVALID_PLAYER_ID) f(temp_name, "%s", get_name(scdplayerid));
                else temp_name = "Нет";
                f(STRING_GLOBAL, "%s"W"%s [%d] — %s\n\n", STRING_GLOBAL, RobberyBankPlayer[i][rbpName], i + 1, temp_name);
            }
            strcat(STRING_GLOBAL, "\
            Ограбить банк можно только с командой, ты можешь позвать до 5-ти подельников,\n\
            если ты хочешь позвать их, введи их ID в строке ниже и должность через запятую,\n\
            но отменить это действие невозможно.");
            ShowPlayerDialog(playerid, D_ROB_BANK_PLAYER, DIALOG_STYLE_INPUT, ""I"Информация о текущих участниках ограбления", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_BANK_USE:
        {
            STRING_GLOBAL = "[#] Название\tНаличие\tПредназначение\n";
            new temp_rob_bank_rank, scdplayerid, str[128];
            for(new i = 0; i < MAX_ROBBERY_BANK_ITEMS_START; i++)
            {
                temp_rob_bank_rank = RobberyBankItemsStart[i][rbiType];
                scdplayerid = RobberyBankContract[idx][rbcPlayerID][temp_rob_bank_rank];
                if(scdplayerid == INVALID_PLAYER_ID) str = "Все";
                else f(str, "%s", get_name(scdplayerid));
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%s\n", STRING_GLOBAL, i + 1, RobberyBankItemsStart[i][rbiName], RobberyBankContract[idx][rbcItemsStart][i] == 0 ? "{"#cLIGHTRED"}Не имеется"W"" : "{"#cGREEN"}Имеется"W"", str);
            }
            ShowPlayerDialog(playerid, D_ROB_BANK_USE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Использовать предметы", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_BANK_START:
        {
            ShowPlayerDialog(playerid, D_ROB_BANK_START, DIALOG_STYLE_MSGBOX, ""I"Начать ограбление", ""W"\
            Вы действительно хотите начать ограбление?\n\n\
            После начала, участники ограбления должны будут использовать купленные предметы и очистить хранилище.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Отменить это действие невозможно.", "Да", "Нет");
            return 1;
        }
        case ROBBERY_BANK_ITEMS_LIST:
        {
            STRING_GLOBAL = ""W"";
            if(RobberyBankContract[idx][rbcVehicleIDx] != INVALID_VEHICLE_ID)
            {
                f(STRING_GLOBAL, "%sВ машине:\n— %d$ и %d кг. золота\n\n", STRING_GLOBAL, RobberyBankContract[idx][rbcVehicleItems][0], RobberyBankContract[idx][rbcVehicleItems][1]);
            }
            new scdplayerid;
            for(new i = 0; i < MAX_ROBBERY_BANK_PLAYER; i++)
            {
                scdplayerid = RobberyBankContract[idx][rbcPlayerID][i];
                if(scdplayerid == INVALID_PLAYER_ID) continue;
                f(STRING_GLOBAL, "%sУ %s %d$ и %d кг. золота\n", STRING_GLOBAL, get_name(scdplayerid), p_temp[scdplayerid][rob_bank_backup_items][0], p_temp[scdplayerid][rob_bank_backup_items][1]);
            }
            strcat(STRING_GLOBAL, "\n{"#cLIGHTRED"}\
            Обратите внимание! При выходе из игры с предметами или при смерти все предметы будут утеряны!\n\
            Обратите внимание! Транспортное средство могут конфисковать сотрудники полицейского департамента!");
            ShowPlayerDialog(playerid, D_ROB_BANK_ITEMS_LIST, DIALOG_STYLE_MSGBOX, ""I"Список награбленного", STRING_GLOBAL, "Отмена", "");
        }
        case ROBBERY_BANK_EXTEND_CONTRACT:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Если по каким-то причинам ты не успеваешь выполнить контракт, можешь его продлить,\n\
            но обойдется тебе это в "I"%d$."W"\n\n\
            Вы действительно хотите продлить контракт?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Продлить контракт можно 1 раз!"W"", RobberyBankContract[idx][rbcPrice] / 2);
            ShowPlayerDialog(playerid, D_ROB_BANK_EXTEND_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Продлить контракт", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_BANK_LEAVE:
        {
            ShowPlayerDialog(playerid, D_ROB_BANK_LEAVE, DIALOG_STYLE_MSGBOX, ""I"Покинуть ограбление", ""W"\
            Вы действительно хотите покинуть ограбление?\n\
            Вещи, которые находятся в Вашей сумке будут утеряны.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Отменить это действие будет невозможно!", "Да", "Нет");
        }
        case ROBBERY_BANK_DELETE:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите завершит196: "I"%d$."W"\n\n\
            Доля каждого составит: "I"%d$.", GetRobberyBankSecrecy(idx), GetRobberyBankShare(idx));
            ShowPlayerDialog(playerid, D_ROB_BANK_DELETE, DIALOG_STYLE_MSGBOX, ""I"Завершить контракт", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_BANK_NPC_BUY:
        {
            if(p_temp[playerid][rob_bank_rank] != idx) return SendError(playerid, "Вы не являетесь поддельником в ограблении банка на должности \"%s\".", RobberyBankPlayer[idx][rbpName]);
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            new count;
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < MAX_ROBBERY_BANK_ITEMS_START; i++)
            {
                if(RobberyBankItemsStart[i][rbiType] != idx) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, count + 1, RobberyBankItemsStart[i][rbiName]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_ROB_BANK_NPC_BUY, DIALOG_STYLE_LIST, ""I"Предметы для ограбления", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "RobberyBank:items_idx", idx);
        }
        case ROBBERY_BANK_NPC_BUY_ACT:
        {
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Название предмета: "I"%s"W"\n\n\
            Описание:\n\n\
            %s\n\n\
            Стоимость: "I"%d$"W"\n\n\
            Вы действительно хотите приобрести данный предмет?", RobberyBankItemsStart[first_parameter][rbiName], RobberyBankItemsStart[first_parameter][rbiInfo], RobberyBankItemsStart[first_parameter][rbiPrice]);
            STRING_MIN[0] = EOS;
            f(STRING_MIN, ""I"%s", RobberyBankItemsStart[first_parameter][rbiName]);
            ShowPlayerDialog(playerid, D_ROB_BANK_NPC_BUY_ACT, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Да", "Нет");
            SetPVarInt(playerid, "RobberyBank:items_buy", first_parameter);
        }
        case ROBBERY_BANK_NPC_2:
        {
            if(p_temp[playerid][rob_bank_rank] != 2) return SendError(playerid, "Вы не являетесь поддельником в ограблении банка на должности \"%s\".", RobberyBankPlayer[2][rbpName]);
            ShowPlayerDialog(playerid, D_ROB_BANK_NPC_2, DIALOG_STYLE_LIST, ""I"Майкл", ""I"[1]"W" Арендовать фургон\n"I"[2]"W" Предметы для ограбления", "Далее", "Отмена");
        }
        case ROBBERY_BANK_NPC_2_R_VEHICLE:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите арендовать транспортное средство \"%s\" для ограбления за %d$?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Остерегайтесь сотрудников полицейского департамента, они могут нейтрализовать его!", GetVehicleName(INVALID_VEHICLE_ID, MODEL_ROBBERY_VEHICLE), RENT_PRICE_ROBBERY_B_VEHICLE);
            ShowPlayerDialog(playerid, D_ROB_BANK_NPC_2_RENT_VEHICLE, DIALOG_STYLE_MSGBOX, ""I"Арендовать транспортное средство", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_BANK_NPC_3:
        {
            if(p_temp[playerid][rob_bank_backup] == 0) return SendError(playerid, "У Вас нет сумки.");
            new temp_rob_bank_money = p_temp[playerid][rob_bank_backup_items][0], temp_rob_bank_gold = p_temp[playerid][rob_bank_backup_items][1];
            if(temp_rob_bank_money == 0 && temp_rob_bank_gold == 0) return SendError(playerid, "В Вашей сумке ничего нет.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"Вы действительно хотите сбыть %d$ и %d кг. золота?", temp_rob_bank_money, temp_rob_bank_gold);
            ShowPlayerDialog(playerid, D_ROB_BANK_NPC_3, DIALOG_STYLE_MSGBOX, ""I"Джек", STRING_GLOBAL, "Да", "Нет");
        }
    }
    return 1;
}

SendRobberyBankMessage(rob_id, color, string[])
{
    foreach(new i:Player)
    {
        if(p_temp[i][rob_bank_idx] == rob_id)
        {
            SendMes(i, color, string);
        }
    }
    return 1;
}

LoadRobberyBank()
{
    for(new i = 0; i < MAX_BANK; i++)
    {
        BankInfo[i][bPickup][0] = CreateDynamicPickup(1318, 23, BankInfo[i][bEnter][0], BankInfo[i][bEnter][1], BankInfo[i][bEnter][2]);
        UpdatePickupInfo(BankInfo[i][bPickup][0], TYPE_BANK, PICKUP_SUBTYPE_BANK_ENTER, i);
        BankInfo[i][bPickup][1] = CreateDynamicPickup(1318, 23, 2291.9282,-55.2634,1070.2646, i);
        UpdatePickupInfo(BankInfo[i][bPickup][1], TYPE_BANK, PICKUP_SUBTYPE_BANK_EXIT, i);
        STRING_MIN[0] = EOS;
        f(STRING_MIN, "<< %s >>", BankInfo[i][bName]);
        CreateDynamic3DTextLabel(STRING_MIN, COLOR_MAIN, BankInfo[i][bEnter][0], BankInfo[i][bEnter][1], BankInfo[i][bEnter][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
        CreateDynamicMapIcon(BankInfo[i][bEnter][0], BankInfo[i][bEnter][1], BankInfo[i][bEnter][2], 52, 0, -1, -1, -1, 100.0);

        BankInfo[i][bDoor] = CreateDynamicObject(1965, 2273.014892, -63.320343, 1070.637451, 0.000000, 0.000000, 0.000000, i, -1, -1, 120.00, 120.00); 
        SetDynamicObjectMaterial(BankInfo[i][bDoor], 0, 3272, "ele_substation", "des_substa_bit1", 0x00000000);
    }

    bank_pickup[0] = CreateDynamicPickup(1239, 23, 2281.1985,-59.2736,1070.2646, -1, -1, -1);
    UpdatePickupInfo(bank_pickup[0], TYPE_BANK, PICKUP_SUBTYPE_BANK_MENU, -1);
    bank_pickup[1] = CreateDynamicPickup(1239, 23, 2277.6594,-55.2652,1070.2646, -1, -1, -1);
    UpdatePickupInfo(bank_pickup[1], TYPE_BANK, PICKUP_SUBTYPE_BANK_MENU, -1);
    bank_pickup[2] = CreateDynamicPickup(1239, 23, 2281.1960,-51.4121,1070.2646, -1, -1, -1);
    UpdatePickupInfo(bank_pickup[2], TYPE_BANK, PICKUP_SUBTYPE_BANK_MENU, -1);

    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 2281.1985,-59.2736,1070.2646, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 2277.6594,-55.2652,1070.2646, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 2281.1960,-51.4121,1070.2646, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    CreateActor(20, 1720.9973,-1636.8557,20.2114,1.3301);
    CreateDynamic3DTextLabel("NPC: "I"Вилли", COLOR_WHITE, 1720.9973,-1636.8557,20.2114 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(293, 926.2789,-1299.1449,13.5469,359.7635);
    CreateDynamic3DTextLabel("NPC: "I"Роберт", COLOR_WHITE, 926.2789,-1299.1449,13.5469 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(285, 1632.7174,-1521.0094,13.6072,174.9419);
    CreateDynamic3DTextLabel("NPC: "I"Майкл", COLOR_WHITE, 1632.7174,-1521.0094,13.6072 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(29, 1359.2649,-1720.8241,8.5988,357.8835);
    CreateDynamic3DTextLabel("NPC: "I"Джон", COLOR_WHITE, 1359.2649,-1720.8241,8.5988 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(274, 1131.9821,-1346.5168,13.9910,319.3432);
    CreateDynamic3DTextLabel("NPC: "I"Доминик", COLOR_WHITE, 1131.9821,-1346.5168,13.9910 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(57, 382.1550,-2013.1368,7.8359,176.3890);
    CreateDynamic3DTextLabel("NPC: "I"Джек", COLOR_WHITE, 382.1550,-2013.1368,7.8359 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_bank_area[0] = CreateDynamicSphere(1721.0063,-1636.1530,20.2115, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_bank_area[0], TYPE_ROB_BANK, AREA_SUBTYPE_ROB_BANK_NPC_1);
    CreatePickup(1239, 23, 1721.0063,-1636.1530,20.2115);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1721.0063,-1636.1530,20.2115, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_bank_area[1] = CreateDynamicSphere(926.2943,-1298.4442,13.5469, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_bank_area[1], TYPE_ROB_BANK, AREA_SUBTYPE_ROB_BANK_NPC_2);
    CreatePickup(1239, 23, 926.2943,-1298.4442,13.5469);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 926.2943,-1298.4442,13.5469, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_bank_area[2] = CreateDynamicSphere(1632.7802,-1521.7112,13.6076, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_bank_area[2], TYPE_ROB_BANK, AREA_SUBTYPE_ROB_BANK_NPC_3);
    CreatePickup(1239, 23, 1632.7802,-1521.7112,13.6076);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1632.7802,-1521.7112,13.6076, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_bank_area[3] = CreateDynamicSphere(1359.2579,-1720.1215,8.5869, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_bank_area[3], TYPE_ROB_BANK, AREA_SUBTYPE_ROB_BANK_NPC_4);
    CreatePickup(1239, 23, 1359.2579,-1720.1215,8.5869);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1359.2579,-1720.1215,8.5869, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_bank_area[4] = CreateDynamicSphere(1132.4374,-1345.9816,13.9844, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_bank_area[4], TYPE_ROB_BANK, AREA_SUBTYPE_ROB_BANK_NPC_5);
    CreatePickup(1239, 23, 1132.4374,-1345.9816,13.9844);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1132.4374,-1345.9816,13.9844, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_bank_area[5] = CreateDynamicSphere(382.1675,-2013.8407,7.8359, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_bank_area[4], TYPE_ROB_BANK, AREA_SUBTYPE_ROB_BANK_NPC_5);
    CreatePickup(1239, 23, 382.1675,-2013.8407,7.8359);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 382.1675,-2013.8407,7.8359, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateDynamic3DTextLabel("Ограбление банка\n\n"W"Место для установки взрывчатки", COLOR_MAIN, 2273.6716,-62.5555,1070.2646, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    CreateDynamic3DTextLabel("Ограбление банка\n\n"W"Место для выброса слезоточивый газа", COLOR_MAIN, 2291.6636,-50.4572,1070.2646, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    CreateDynamic3DTextLabel("Ограбление банка\n\n"W"Место для установки металлодетектора", COLOR_MAIN, 2268.4270,-60.1049,1070.2646, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    CreateDynamic3DTextLabel("Ограбление банка\n\n"W"Место для установки рации", COLOR_MAIN, 2288.3367,-49.8459,1070.2646, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    CreateDynamic3DTextLabel("Ограбление банка\n\n"W"Место для разлива крови", COLOR_MAIN, 2283.9617,-55.2992,1070.2646, 2.5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

CMD:load_bcontract(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 10) return 1;

    for(new i = 0; i < MAX_ROBBERY_BANK_CONTRACT; i++)
    {
        if(RobberyBankContract[i][rbcStatus] == 0) CreateRobberyBankContract(i);
    }

    SendAccess(playerid, "Вы создали максимальное количество контрактов для ограбления банка.");
    return 1;
}

CheckRobberyBankContract()
{
    new scdplayerid, money;
    for(new i = 0, idx = 0; i < MAX_ROBBERY_BANK_CONTRACT; i++)
    {
        if(RobberyBankContract[i][rbcStatus] > 1)
        {
            RobberyBankContract[i][rbcTime]--;
            if(RobberyBankContract[i][rbcTime] == 0)
            {
                money = GetRobberyBankShare(i);
                for(idx = 0; idx < MAX_ROBBERY_BANK_PLAYER; idx++)
                {
                    scdplayerid = RobberyBankContract[i][rbcPlayerID][idx];
                    if(scdplayerid != INVALID_PLAYER_ID)
                    {
                        RobberyBankContract[i][rbcPlayerID][idx] = INVALID_PLAYER_ID;
                        ClearRobberyBank(scdplayerid, 1);
                        ClearRobberyBankBackup(scdplayerid, 1);
                        SetPlayerSkinEx(scdplayerid);
                        maskOFF(scdplayerid);
                        SetPlayerMoney(scdplayerid, money, true, "завершено время ограбления банка");
                        RobbingInfoForMoney[3] += money;
                        SendInfo(scdplayerid, "Время на выполнение контракта вышло.");
                        SendInfo(scdplayerid, "Вы заработали: %d$.", money);
                    }
                }
                DestroyRobberyBankContract(i);
            }
        }
    }
    return 1;
}

CheckRobberyBankContractList()
{
    new count, max_count = random(2);
    for(new i = 0; i < MAX_ROBBERY_BANK_CONTRACT; i++)
    {
        if(RobberyBankContract[i][rbcStatus] == 0)
        {
            CreateRobberyBankContract(i);
            count++;
        }
        if(count == max_count) break;
    }
    return 1;
}

CreateRobberyBankContract(idx)
{
    new i = GetFreeRobberyBank();
    if(i == -1) return 1;
    RobberyBankContract[idx][rbcStatus] = 1;
    new rob_bank_type[8] = {1, 1, 2, 2, 2, 2, 2, 2};
    RobberyBankContract[idx][rbcType] = rob_bank_type[random(6)];
    RobberyBankContract[idx][rbcBankIDx] = i;
    RobberyBankContract[idx][rbcBankSignaling] = 0;
    RobberyBankContract[idx][rbcVehicleIDx] = INVALID_VEHICLE_ID;
    RobberyBankContract[idx][rbcVehicleNumber] = 0;
    for(new x = 0; x < MAX_ROBBERY_BANK_ITEMS_START; x++)
    {
        RobberyBankContract[idx][rbcItemsStart][x] = 0;
        if(x < MAX_ROBBERY_BANK_VEHICLE_ITEMS) RobberyBankContract[idx][rbcVehicleItems][x] = 0;
        if(x < MAX_ROBBERY_BANK_PLAYER) RobberyBankContract[idx][rbcPlayerID][x] = INVALID_PLAYER_ID;
        if(x < MAX_ROBBERY_BANK_SECRECY) RobberyBankContract[idx][rbcSecrecy][x] = 0;
        if(x < MAX_ROBBERY_BANK_ANTICALL) RobberyBankContract[idx][rbcAnticall][x] = 0;
    }
    RobberyBankContract[idx][rbcPrice] = 100000;
    RobberyBankContract[idx][rbcTime] = 0;
    RobberyBankContract[idx][rbcTimeUpdate] = 0;
    RobberyBankContract[idx][rbcOwnerID] = INVALID_MYSQL_ID;
    RobberyBankContract[idx][rbcKush] = 0;
    RobberyBankContract[idx][rbcMetalUse] = 0;

    BankInfo[i][bRobbery] = 1;
    return 1;
}

DestroyRobberyBankContract(idx)
{
    RobberyBankContract[idx][rbcStatus] = 0;
    RobberyBankContract[idx][rbcType] = 0;
    new bankid = RobberyBankContract[idx][rbcBankIDx];
    RobberyBankContract[idx][rbcBankIDx] = 0;
    RobberyBankContract[idx][rbcBankSignaling] = 0;
    if(RobberyBankContract[idx][rbcVehicleIDx] != INVALID_VEHICLE_ID) DestroyVehicleVEx(RobberyBankContract[idx][rbcVehicleIDx]);
    RobberyBankContract[idx][rbcVehicleIDx] = INVALID_VEHICLE_ID;
    RobberyBankContract[idx][rbcVehicleNumber] = 0;
    for(new x = 0; x < MAX_ROBBERY_BANK_ITEMS_START; x++)
    {
        RobberyBankContract[idx][rbcItemsStart][x] = 0;
        if(x < MAX_ROBBERY_BANK_VEHICLE_ITEMS) RobberyBankContract[idx][rbcVehicleItems][x] = 0;
        if(x < MAX_ROBBERY_BANK_PLAYER) RobberyBankContract[idx][rbcPlayerID][x] = INVALID_PLAYER_ID;
        if(x < MAX_ROBBERY_BANK_SECRECY) RobberyBankContract[idx][rbcSecrecy][x] = 0;
        if(x < MAX_ROBBERY_BANK_ANTICALL) RobberyBankContract[idx][rbcAnticall][x] = 0;
    }
    RobberyBankContract[idx][rbcPrice] = 0;
    RobberyBankContract[idx][rbcTime] = 0;
    RobberyBankContract[idx][rbcTimeUpdate] = 0;
    RobberyBankContract[idx][rbcOwnerID] = INVALID_MYSQL_ID;
    RobberyBankContract[idx][rbcKush] = 0;
    RobberyBankContract[idx][rbcMetalUse] = 0;

    if(BankInfo[bankid][bDoor] == INVALID_OBJECT_ID)
    {
        BankInfo[bankid][bDoor] = CreateDynamicObject(1965, 2273.014892, -63.320343, 1070.637451, 0.000000, 0.000000, 0.000000, bankid, -1, -1, 120.00, 120.00); 
        SetDynamicObjectMaterial(BankInfo[bankid][bDoor], 0, 3272, "ele_substation", "des_substa_bit1", 0x00000000);
    }

    BankInfo[bankid][bRobbery] = 0;
    return 1;
}

GetFreeRobberyBank()
{
    new bank_checked = -1;
    for(new i = MAX_BANK - 1; i != -1; i--)
    {
        bank_checked = random(MAX_BANK);
        if(BankInfo[bank_checked][bRobbery] == 0) return bank_checked;
    }
    return -1;
}

GetRobberyBankSecrecy(idx)
{
    if(RobberyBankContract[idx][rbcBankSignaling] == 0)
    {
        new count;
        for(new i = 0; i < MAX_ROBBERY_BANK_SECRECY; i++)
        {
            if(RobberyBankContract[idx][rbcSecrecy][i] == 1) count++;
        }
        if(count == MAX_ROBBERY_BANK_SECRECY)
        {
            return floatround(RobberyBankContract[idx][rbcKush] * 0.20);
        }
    }
    return 0;
}

GetRobberyBankShare(idx)
{
    new count;
    for(new i = 0; i < MAX_ROBBERY_BANK_PLAYER; i++)
    {
        if(RobberyBankContract[idx][rbcPlayerID][i] != INVALID_PLAYER_ID) count++;
    }
    new kush = RobberyBankContract[idx][rbcKush] + GetRobberyBankSecrecy(idx);
    if(kush == 0) return 0;
    else return kush / count;
}

ClearRobberyBank(playerid, type = -1)
{
    p_temp[playerid][rob_bank_idx] = -1;
    p_temp[playerid][rob_bank_backup] = 0;
    p_temp[playerid][rob_bank_backup_items][0] =
    p_temp[playerid][rob_bank_backup_items][1] = 0;
    p_temp[playerid][rob_bank_timer] = 0;
    p_temp[playerid][rob_bank_timer_max] = 0;
    if(type != -1)
    {
        for(new i = 0; i < 10; i++) if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
    }
    return 1;
}

ClearRobberyBankBackup(playerid, type = -1)
{
    p_temp[playerid][rob_bank_backup_items][2] =
    p_temp[playerid][rob_bank_backup_items][3] = 0;
    if(type != -1)
    {
        if(p_temp[playerid][rob_bank_backup_pickup] != -1) DestroyDynamicPickup(p_temp[playerid][rob_bank_backup_pickup]);
        if(p_temp[playerid][rob_bank_backup_area] != -1) DestroyDynamicArea(p_temp[playerid][rob_bank_backup_area]);
    }
    p_temp[playerid][rob_bank_backup_pickup] = -1;
    p_temp[playerid][rob_bank_backup_area] = -1;
    p_temp[playerid][rob_bank_backup_pos][0] =
    p_temp[playerid][rob_bank_backup_pos][1] =
    p_temp[playerid][rob_bank_backup_pos][2] = 0.0;
    return 1;
}

GetPlayerRobberyBank(playerid)
{
    for(new i = 0; i < MAX_ROBBERY_BANK_CONTRACT; i++)
    {
        if(RobberyBankContract[i][rbcOwnerID] == p_info[playerid][ID])
        {
            RobberyBankContract[i][rbcPlayerID][0] = playerid;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "[ROBBERY] %s [%d] в игре.", get_name(playerid), playerid);
            SendRobberyBankMessage(i, 0xDEB887FF, STRING_GLOBAL);
            p_temp[playerid][rob_bank_idx] = i;
            p_temp[playerid][rob_bank_rank] = 0;
            if(RobberyBankContract[i][rbcStatus] == 3) p_temp[playerid][rob_bank_backup] = 1;
            return i;
        }
    }
    return -1;
}

CallingPoliceToRobberyBank(idx, bankid)
{
    SendRobberyBankMessage(idx, 0xDEB887FF, "[ROBBERY] В банке сработала сигнализация, сообщение отправлено сотрудникам полицейского департамента!");
    RobberyBankContract[idx][rbcBankSignaling] = 1;
    foreach(new i : gFactionPlayers[FBI_TEAM || POLICE_LS || POLICE_SF || POLICE_LV || POLICE_RC])
    {
        if(p_info[i][fwork] == true)
        {
            SendMes(i, COLOR_DARKORANGE, "[ОГРАБЛЕНИЕ БАНКА]: "W"Грабители в банке %s, остановите грабителей! Место отмечено на GPS!", BankInfo[bankid][bName]);
            SetPlayerGPS(i, BankInfo[bankid][bEnter][0], BankInfo[bankid][bEnter][1], BankInfo[bankid][bEnter][2], 5.0);
        }
    }
    new scdplayerid;
    for(new i = 0; i < MAX_ROBBERY_BANK_PLAYER; i++)
    {
        scdplayerid = RobberyBankContract[idx][rbcPlayerID][i];
        if(scdplayerid != INVALID_PLAYER_ID)
        {
            if(p_info[scdplayerid][wanted] < 6)
            {
                p_info[scdplayerid][wanted] = 6;
                SetPlayerWantedLevel(scdplayerid, p_info[scdplayerid][wanted]);
                SendInfo(scdplayerid, "В банке сработала сигнализация, Вы объявлены в розыск.");
            }
        }
    }
    return 1;
}