ShowRobberyHouse(playerid, type, idx = -1, first_parameter = -1)
{
    switch(type)
    {
        case ROBBERY_HOUSE_NPC_1:
        {
            ShowPlayerDialog(playerid, D_ROB_HOUSE_NPC_1, DIALOG_STYLE_LIST, ""I"Вадим", "\
            "I"[1]"W" Информация об ограблениях\n\
            "I"[2]"W" Список контрактов\n\
            "I"[3]"W" Текущий контракт", "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_INFO:
        {
            ShowPlayerDialog(playerid, D_ROB_HOUSE_INFO, DIALOG_STYLE_MSGBOX, ""I"Вадим", ""W"\
            Привет! Меня зовут "I"Вадим,"W" я — "I"информатор,"W" который имеет глаза во всех спец. службах и без какого-либо\n\
            труда, подскажу что и где плохо лежит.\n\n\
            Я готов предоставить тебе информацию о домах, которые можно ограбить, но за это тебе "I"придётся заплатить."W"\n\n\
            Ограбить дом не так-то просто, ты сможешь ограбить его сам или пригласить до "I"3-х подельников."W"\n\n\
            После передачи информации, необходимо будет приобрести предметы для ограбления и арендовать\n\
            транспортное средство. Координаты где это можно будет сделать, ты получишь после оплаты контракта.\n\n\
            Контракты делятся на два типа — "I"обычный и премиальный."W" Обычный доступен всем игрокам, а премиальный —\n\
            только для игроков, обладающих "I"VIP Gold."W" В премиальных контрактах есть возможность "I"взлома сейфа."W"\n\n\
            Приобрести контракт можно с "I"12:00"W" до "I"22:00."W" Они появляются каждый час.\n\n\
            Процесс ограбления довольно сложный, ибо в некоторых домах может быть сигнализация и при взломе она\n\
            сработает. Это можно избежать, но тебе нужно будет хорошо спланировать ограбление и обзавестись "I"всеми\n\
            необходимыми предметами."W"\n\n\
            После начала ограбления, тебе и твоим подельникам предстоит найти объекты интерьера и собрать их в сумки,\n\
            а затем погрузить в транспортное средство. Всего в домах находится "I"15 предметов."W"\n\n\
            По завершению ограбления необходимо перевести все предметы на чёрный рынок и продать их.\n\n\
            Стоимость предметов для ограбления и предметов интерьера зависит от класса дома, чем выше, тем дороже\n\
            стоимость предметов и объектов интерьера.", "Закрыть", "");
        }
        case ROBBERY_HOUSE_LIST:
        {
            if(p_temp[playerid][rob_house_idx] != -1) return ShowRobberyHouse(playerid, ROBBERY_HOUSE_NPC_1), SendError(playerid, "Вы уже участвуете в ограблении дома.");
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            new count;
            STRING_GLOBAL = "[#] Тип контракта\tСтоимость\n";
            for(new i = 0; i < MAX_ROBBERY_HOUSE_CONTRACT; i++)
            {
                if(RobberyHouseContract[i][rhcStatus] != 1) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d$\n", STRING_GLOBAL, count + 1, RobberyHouseContract[i][rhcType] == 0 ? "Обычный" : "{"#cYELLOW"}Премиальный"W"", RobberyHouseContract[i][rhcPrice]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0)
            {
                SendError(playerid, "На данный момент нет контрактов, они появляются каждый час.");
                return ShowRobberyHouse(playerid, ROBBERY_HOUSE_NPC_1);
            }
            ShowPlayerDialog(playerid, D_ROB_HOUSE_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список контрактов", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_CONTRACT:
        {
            if(idx == -1) return 1;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Тип: %s\n\
            Стоимость: {"#cGREEN"}%d$"W"\n\
            Номер дома: {"#cGRAY"}Скрыто", RobberyHouseContract[idx][rhcType] == 0 ? "Обычный" : "{"#cYELLOW"}Премиальный"W"", RobberyHouseContract[idx][rhcPrice]);
            ShowPlayerDialog(playerid, D_ROB_HOUSE_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Информация о контракте", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "RobberyHouse:idx", idx);
        }
        case ROBBERY_HOUSE_CONTRACT_START:
        {
            ShowPlayerDialog(playerid, D_ROB_HOUSE_CONTRACT_START, DIALOG_STYLE_MSGBOX, ""I"Пояснение к контракту", ""W"\
            В случае неудачного ограбления, денежные средства тебе "I"никто не вернет!"W"\n\n\
            На выполнение контракта отводится "I"1 час,"W" не затягивай!\n\n\
            Если ты согласен со всеми условиями, нажми "I"\"Далее\"."W" После этого с тебя\n\
            "I"спишутся деньги"W" за контракт и ты сможешь пригласить в ограбление до "I"3-х\n\
            подельников"W" с помощью команды "I"/robbing\n\n\
            {"#cLIGHTRED"}Обратите внимание! Исход ограбления зависит только от тебя!", "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_CONTRACT_INFO:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Время до завершения контракта: "I"%s"W"\n\
            Тип ограбления: %s\n\
            Номер дома: "I"%d"W"\n\
            Стоимость контракта: "I"%d$"W"\n\n\
            Машина для ограбления: %s", ConvertTime(RobberyHouseContract[idx][rhcTime]), RobberyHouseContract[idx][rhcType] == 0 ? "{"#cGREEN"}Обычный"W"" : "{"#cYELLOW"}Премиальный"W"", RobberyHouseContract[idx][rhcHouseIDx], RobberyHouseContract[idx][rhcPrice], RobberyHouseContract[idx][rhcVehicleIDx] == INVALID_VEHICLE_ID ? "{"#cLIGHTRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
            ShowPlayerDialog(playerid, D_ROB_HOUSE_CONTRACT_INFO, DIALOG_STYLE_MSGBOX, ""I"Текущий контракт", STRING_GLOBAL, "Закрыть", "");
        }
        case ROBBERY_HOUSE_MENU:
        {
            if(p_temp[playerid][rob_house_idx] == -1)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.5, 1413.4436,-1487.6085,20.4344)) ShowRobberyHouse(playerid, ROBBERY_HOUSE_NPC_1);
                SendError(playerid, "У Вас нет активного контракта.");
                return 1;
            }
            STRING_GLOBAL[0] = EOS;
            ShowPlayerDialog(playerid, D_ROB_HOUSE_MENU, DIALOG_STYLE_LIST, ""I"Меню ограбления", "\
            "I"[1]"W" Информация о контракте\n\
            "I"[2]"W" Информация о текущих участниках ограбления\n\
            "I"[3]"W" Использовать предметы\n\
            "I"[4]"W" Найти Владимира\n\
            "I"[5]"W" Найти дом\n\
            {"#cYELLOW"}[6] Использовать сумку\n\
            {"#cGREEN"}[7] Начать ограбление\n\
            "I"[6]"W" Список награбленного\n\
            "I"[7]"W" Продлить контракт\n\
            "I"[8]"W" Найти потерянную сумку\n\
            "I"[9]"W" Покинуть ограбление\n\
            {"#cLIGHTRED"}[10] Завершить контракт", "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_PLAYER:
        {
            STRING_GLOBAL[0] = EOS;
            new scdplayerid;
            for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
            {
                scdplayerid = RobberyHouseContract[idx][rhcPlayerID][i];
                if(scdplayerid == INVALID_PLAYER_ID) continue;
                f(STRING_GLOBAL, "%s"W"Грабитель "I"#%d"W" — %s\n\n", STRING_GLOBAL, i + 1, get_name(scdplayerid));
            }
            strcat(STRING_GLOBAL, "\
            Ты можешь пойти на ограбление сам, а можешь позвать до 4-х подельников,\n\
            если ты хочешь позвать их, введи их ID в строке ниже, но отменить это действие\n\
            невозможно.");
            ShowPlayerDialog(playerid, D_ROB_HOUSE_PLAYER, DIALOG_STYLE_INPUT, ""I"Информация о текущих участниках ограбления", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_USE:
        {
            STRING_GLOBAL = "[#] Название\tНаличие\n";
            for(new i = 0; i < MAX_ROBBERY_HOUSE_ITEMS_START; i++)
            {
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\n", STRING_GLOBAL, i + 1, RobberyHouseItemsStart[i][rhisName], RobberyHouseContract[idx][rhcItemsStart][i] == 0 ? "{"#cLIGHTRED"}Не имеется"W"" : "{"#cGREEN"}Имеется"W"");
            }
            ShowPlayerDialog(playerid, D_ROB_HOUSE_USE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Использовать предметы", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_START:
        {
            ShowPlayerDialog(playerid, D_ROB_HOUSE_START, DIALOG_STYLE_MSGBOX, ""I"Начать ограбление", ""W"\
            Вы действительно хотите начать ограбление?\n\n\
            После начала, участники ограбления должны будут использовать купленные предметы и ограбить дом.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Отменить это действие невозможно.", "Да", "Нет");
        }
        case ROBBERY_HOUSE_ITEMS_LIST:
        {
            STRING_GLOBAL = ""W"";
            if(RobberyHouseContract[idx][rhcVehicleIDx] != INVALID_VEHICLE_ID)
            {
                strcat(STRING_GLOBAL, "В машине:\n");
                new items_idx;
                for(new i = 0; i < MAX_ROBBERY_HOUSE_ITEMS; i++)
                {
                    items_idx = RobberyHouseContract[idx][rhcVehicleItems][i];
                    if(items_idx == -1) continue;
                    f(STRING_GLOBAL, "%s— %s\n", STRING_GLOBAL, RobberyHouseItems[items_idx][rhiName]);
                }
            }
            new scdplayerid, items_idx;
            for(new i = 0, x = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
            {
                scdplayerid = RobberyHouseContract[idx][rhcPlayerID][i];
                if(scdplayerid == INVALID_PLAYER_ID) continue;
                f(STRING_GLOBAL, "%s%sУ %s:\n", i == 0 ? "" : "\n", STRING_GLOBAL, get_name(scdplayerid));
                for(x = 0; x < MAX_ROBBERY_HOUSE_PLAYER_ITEMS; x++)
                {
                    items_idx = p_temp[scdplayerid][rob_house_backup_items][x];
                    if(items_idx == -1) continue;
                    f(STRING_GLOBAL, "%s— %s\n", STRING_GLOBAL, RobberyHouseItems[items_idx][rhiName]);
                }
            }
            strcat(STRING_GLOBAL, "\n{"#cLIGHTRED"}\
            Обратите внимание! При выходе из игры с предметами или при смерти все предметы будут утеряны!\n\
            Обратите внимание! Транспортное средство могут конфисковать сотрудники полицейского департамента!");
            ShowPlayerDialog(playerid, D_ROB_HOUSE_ITEMS_LIST, DIALOG_STYLE_MSGBOX, ""I"Список награбленного", STRING_GLOBAL, "Отмена", "");
        }
        case ROBBERY_HOUSE_EXTEND_CONTRACT:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Если по каким-то причинам ты не успеваешь выполнить контракт, можешь его продлить,\n\
            но обойдется тебе это в "I"%d$."W"\n\n\
            Вы действительно хотите продлить контракт?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Продлить контракт можно 1 раз!"W"", RobberyHouseContract[idx][rhcPrice] / 2);
            ShowPlayerDialog(playerid, D_ROB_HOUSE_EXTEND_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Продлить контракт", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_HOUSE_LEAVE:
        {
            ShowPlayerDialog(playerid, D_ROB_HOUSE_LEAVE, DIALOG_STYLE_MSGBOX, ""I"Покинуть ограбление", ""W"\
            Вы действительно хотите покинуть ограбление?\n\
            Вещи, которые находятся в Вашей сумке будут утеряны.\n\n\
            {"#cLIGHTRED"}Обратите внимание! Отменить это действие будет невозможно!", "Да", "Нет");
        }
        case ROBBERY_HOUSE_DELETE:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите завершить контракт на ограбление?\n\n\
            Ваш бонус за скрытность составил: "I"%d$."W"\n\n\
            Доля каждого составит: "I"%d$.", GetRobberyHouseSecrecy(idx), GetRobberyHouseShare(idx));
            ShowPlayerDialog(playerid, D_ROB_HOUSE_DELETE, DIALOG_STYLE_MSGBOX, ""I"Завершить контракт", STRING_GLOBAL, "Да", "Нет");
        }
        case ROBBERY_HOUSE_NPC_2:
        {
            if(p_temp[playerid][rob_house_idx] == -1) return SendError(playerid, "Вы не участвуете в ограблении дома.");
            ShowPlayerDialog(playerid, D_ROB_HOUSE_NPC_2, DIALOG_STYLE_LIST, ""I"Владимир", "\
            "I"[1]"W" Продать награбленные предметы\n\
            "I"[2]"W" Приобрести предметы для ограбления\n\
            "I"[3]"W" Арендовать фургон", "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_NPC_2_SELL:
        {
            if(p_temp[playerid][rob_house_backup] == 0) return SendError(playerid, "У Вас нет сумки.");
            new houseid = RobberyHouseContract[idx][rhcHouseIDx];
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            STRING_GLOBAL = "[#] Название\tСтоимость\n";
            new items_idx, count;
            for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER_ITEMS; i++)
            {
                items_idx = p_temp[playerid][rob_house_backup_items][i];
                if(items_idx == -1) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%d$\t%d\n", STRING_GLOBAL, count + 1, RobberyHouseItems[items_idx][rhiName], RobberyHouseItems[items_idx][rhiPrice] * h_info[houseid][h_squar]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0) return ShowRobberyHouse(playerid, ROBBERY_HOUSE_NPC_2), SendError(playerid, "В Вашей сумке ничего нет.");
            ShowPlayerDialog(playerid, D_ROB_HOUSE_NPC_2_SELL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Чёрный рынок", STRING_GLOBAL, "Продать", "Отмена");
        }
        case ROBBERY_HOUSE_NPC_2_BUY:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i = 0; i < MAX_ROBBERY_HOUSE_ITEMS_START; i++)
            {
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i + 1, RobberyHouseItemsStart[i][rhisName]);
            }
            ShowPlayerDialog(playerid, D_ROB_HOUSE_NPC_2_BUY, DIALOG_STYLE_LIST, ""I"Предметы для ограбления", STRING_GLOBAL, "Далее", "Отмена");
        }
        case ROBBERY_HOUSE_NPC_2_BUY_ACT:
        {
            new houseid = RobberyHouseContract[idx][rhcHouseIDx];
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Название предмета: "I"%s"W"\n\n\
            Описание:\n\n\
            %s\n\n\
            Стоимость: "I"%d$"W"\n\n\
            Вы действительно хотите приобрести данный предмет?", RobberyHouseItemsStart[first_parameter][rhisName], RobberyHouseItemsStart[first_parameter][rhisInfo], RobberyHouseItemsStart[first_parameter][rhisPrice] * h_info[houseid][h_squar]);
            STRING_MIN[0] = EOS;
            f(STRING_MIN, ""I"%s", RobberyHouseItemsStart[first_parameter][rhisName]);
            ShowPlayerDialog(playerid, D_ROB_HOUSE_NPC_2_BUY_ACT, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Да", "Нет");
            SetPVarInt(playerid, "RobberyHouse:items_buy", first_parameter);
        }
        case ROBBERY_HOUSE_NPC_2_R_VEHICLE:
        {
            new houseid = RobberyHouseContract[idx][rhcHouseIDx], price = RENT_PRICE_ROBBERY_VEHICLE * h_info[houseid][h_squar];
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Вы действительно хотите арендовать транспортное средство \"%s\" для ограбления за %d$?\n\n\
            {"#cLIGHTRED"}Обратите внимание! С его помощью можно перевозить 15 награбленных предметов!\n\
            Обратите внимание! Остерегайтесь сотрудников полицейского департамента, они могут нейтрализовать его!", GetVehicleName(INVALID_VEHICLE_ID, MODEL_ROBBERY_VEHICLE), price);
            ShowPlayerDialog(playerid, D_ROB_HOUSE_NPC_2_RENT_VEHICLE, DIALOG_STYLE_MSGBOX, ""I"Арендовать транспортное средство", STRING_GLOBAL, "Да", "Нет");
        }
    }
    return 1;
}

GetFreRobberyHousePlayer(idx)
{
    for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
    {
        if(RobberyHouseContract[idx][rhcPlayerID][i] == INVALID_PLAYER_ID) return i;
    }
    return -1;
}

SendRobberyHouseMessage(rob_id, color, string[])
{
    foreach(new i:Player)
    {
        if(p_temp[i][rob_house_idx] == rob_id)
        {
            SendMes(i, color, string);
        }
    }
    return 1;
}

LoadRobberyHouse()
{
    CreateActor(112, 1413.4130,-1486.8986,20.4349,174.7395);
    CreateDynamic3DTextLabel("NPC: "I"Вадим", COLOR_WHITE, 1413.4130,-1486.8986,20.4349 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(33, 2322.7756,-1222.9293,22.6376,272.0149);
    CreateDynamic3DTextLabel("NPC: "I"Владимир", COLOR_WHITE, 2322.7756,-1222.9293,22.6376 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_house_area[0] = CreateDynamicSphere(1413.4436,-1487.6085,20.4344, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_house_area[0], TYPE_ROB_HOUSE, AREA_SUBTYPE_ROB_HOUSE_NPC_1);
    CreatePickup(1239, 23, 1413.4436,-1487.6085,20.4344);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 1413.4436,-1487.6085,20.4344, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    rob_house_area[1] = CreateDynamicSphere(2323.4768,-1222.8743,22.6349, 2.5, -1, -1, -1);
    UpdateAreaInfo(rob_house_area[1], TYPE_ROB_HOUSE, AREA_SUBTYPE_ROB_HOUSE_NPC_2);
    CreatePickup(1239, 23, 2323.4768,-1222.8743,22.6349);
    CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, 2323.4768,-1222.8743,22.6349, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

CMD:load_hcontract(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 10) return 1;

    for(new i = 0; i < MAX_ROBBERY_HOUSE_CONTRACT; i++)
    {
        if(RobberyHouseContract[i][rhcStatus] == 0) CreateRobberyHouseContract(i);
    }

    SendAccess(playerid, "Вы создали максимальное количество контрактов для ограбления домов.");
    return 1;
}

CheckRobberyHouseContract()
{
    new scdplayerid, money;
    for(new i = 0, idx = 0; i < MAX_ROBBERY_HOUSE_CONTRACT; i++)
    {
        if(RobberyHouseContract[i][rhcStatus] > 1)
        {
            RobberyHouseContract[i][rhcTime]--;
            if(RobberyHouseContract[i][rhcTime] == 0)
            {
                money = GetRobberyHouseShare(i);
                for(idx = 0; idx < MAX_ROBBERY_HOUSE_PLAYER; idx++)
                {
                    scdplayerid = RobberyHouseContract[i][rhcPlayerID][idx];
                    if(scdplayerid != INVALID_PLAYER_ID)
                    {
                        RobberyHouseContract[i][rhcPlayerID][idx] = INVALID_PLAYER_ID;
                        ClearRobberyHouse(scdplayerid, 1);
                        ClearRobberyHouseBackup(scdplayerid, 1);
                        SetPlayerSkinEx(scdplayerid);
                        maskOFF(scdplayerid);
                        SetPlayerMoney(scdplayerid, money, true, "завершено время ограбления");
                        RobbingInfoForMoney[1] += money;
                        SendInfo(scdplayerid, "Время на выполнение контракта вышло.");
                        SendInfo(scdplayerid, "Вы заработали: %d$.", money);
                    }
                }
                DestroyRobberyHouseContract(i);
            }
        }
    }
    return 1;
}

CheckRobberyHouseContractList()
{
    new count, max_count = random(2);
    for(new i = 0; i < MAX_ROBBERY_HOUSE_CONTRACT; i++)
    {
        if(RobberyHouseContract[i][rhcStatus] == 0)
        {
            CreateRobberyHouseContract(i);
            count++;
        }
        if(count == max_count) break;
    }
    return 1;
}

CreateRobberyHouseContract(idx)
{
    new i = GetFreeRobberyHouse();
    if(i == -1) return 1;
    new rob_house_type[8] = {0, 0, 1, 1, 1, 1, 1, 1};
    RobberyHouseContract[idx][rhcStatus] = 1;
    RobberyHouseContract[idx][rhcType] = rob_house_type[random(6)];
    RobberyHouseContract[idx][rhcHouseIDx] = i;
    RobberyHouseContract[idx][rhcHouseSignaling] = 0;
    RobberyHouseContract[idx][rhcVehicleIDx] = INVALID_VEHICLE_ID;
    for(new x = 0; x < MAX_ROBBERY_HOUSE_ITEMS; x++)
    {
        RobberyHouseContract[idx][rhcVehicleItems][x] = -1;
        RobberyHouseContract[idx][rhcObject][x] = INVALID_OBJECT_ID;
        RobberyHouseContract[idx][rhcArea][x] = -1;
        if(x < MAX_ROBBERY_HOUSE_ITEMS_START) RobberyHouseContract[idx][rhcItemsStart][x] = 0;
        if(x < MAX_ROBBERY_HOUSE_PLAYER) RobberyHouseContract[idx][rhcPlayerID][x] = INVALID_PLAYER_ID;
    }
    RobberyHouseContract[idx][rhcPrice] = GetRobberyHouseConctartPrice(i);
    RobberyHouseContract[idx][rhcTime] = 0;
    RobberyHouseContract[idx][rhcTimeUpdate] = 0;
    RobberyHouseContract[idx][rhcOwnerID] = INVALID_MYSQL_ID;
    RobberyHouseContract[idx][rhcKush] = 0;
    RobberyHouseContract[idx][rhcSafe] = INVALID_OBJECT_ID;

    h_info[i][h_rob_house] = 1;
    h_info[i][h_lock] = 1;
    h_info[i][h_rob_house_block] = 0;
    return 1;
}

DestroyRobberyHouseContract(idx)
{
    RobberyHouseContract[idx][rhcStatus] = 0;
    RobberyHouseContract[idx][rhcType] = 0;
    new houseid = RobberyHouseContract[idx][rhcHouseIDx];
    RobberyHouseContract[idx][rhcHouseIDx] = 0;
    RobberyHouseContract[idx][rhcHouseSignaling] = 0;
    if(RobberyHouseContract[idx][rhcVehicleIDx] != INVALID_VEHICLE_ID) DestroyVehicleVEx(RobberyHouseContract[idx][rhcVehicleIDx]);
    RobberyHouseContract[idx][rhcVehicleIDx] = INVALID_VEHICLE_ID;
    for(new x = 0; x < MAX_ROBBERY_HOUSE_ITEMS; x++)
    {
        RobberyHouseContract[idx][rhcVehicleItems][x] = -1;
        if(RobberyHouseContract[idx][rhcObject][x] != INVALID_OBJECT_ID) DestroyDynamicObject(RobberyHouseContract[idx][rhcObject][x]);
        RobberyHouseContract[idx][rhcObject][x] = INVALID_OBJECT_ID;
        if(RobberyHouseContract[idx][rhcArea][x] != -1) DestroyDynamicArea(RobberyHouseContract[idx][rhcArea][x]);
        RobberyHouseContract[idx][rhcArea][x] = -1;
        if(x < MAX_ROBBERY_HOUSE_ITEMS_START) RobberyHouseContract[idx][rhcItemsStart][x] = 0;
        if(x < MAX_ROBBERY_HOUSE_PLAYER) RobberyHouseContract[idx][rhcPlayerID][x] = INVALID_PLAYER_ID;
    }
    RobberyHouseContract[idx][rhcPrice] = 0;
    RobberyHouseContract[idx][rhcTime] = 0;
    RobberyHouseContract[idx][rhcTimeUpdate] = 0;
    RobberyHouseContract[idx][rhcOwnerID] = INVALID_MYSQL_ID;
    RobberyHouseContract[idx][rhcKush] = 0;
    if(RobberyHouseContract[idx][rhcSafe] != INVALID_OBJECT_ID) DestroyDynamicObject(RobberyHouseContract[idx][rhcSafe]);
    RobberyHouseContract[idx][rhcSafe] = INVALID_OBJECT_ID;

    h_info[houseid][h_rob_house] = 0;
    h_info[houseid][h_rob_house_block] = 0;
    return 1;
}

CreateRobberyHouseObject(idx, houseid)
{
    new class;
    for(new i = 0; i < MAX_ROBBERY_HOUSE_ITEMS; i++)
    {
        class = h_info[houseid][h_squar] - 1;
        if(RobberyHouseContract[idx][rhcObject][i] != INVALID_OBJECT_ID) DestroyDynamicObject(RobberyHouseContract[idx][rhcObject][i]);
        RobberyHouseContract[idx][rhcObject][i] = CreateDynamicObject(RobberyHouseItems[i][rhiModel], RobberyHouseObjectPos[class][i][0], RobberyHouseObjectPos[class][i][1], RobberyHouseObjectPos[class][i][2], RobberyHouseObjectPos[class][i][3], RobberyHouseObjectPos[class][i][4], RobberyHouseObjectPos[class][i][5], houseid + 50, HOUSE_INT_ID_REPAIR, -1, 120.00, 120.00);
        if(RobberyHouseContract[idx][rhcArea][i] != -1) DestroyDynamicArea(RobberyHouseContract[idx][rhcArea][i]);
        RobberyHouseContract[idx][rhcArea][i] = CreateDynamicSphere(RobberyHouseObjectPos[class][i][0], RobberyHouseObjectPos[class][i][1], RobberyHouseObjectPos[class][i][2], 1.5, houseid + 50, HOUSE_INT_ID_REPAIR, -1);
        UpdateAreaInfo(RobberyHouseContract[idx][rhcArea][i], TYPE_ROB_HOUSE, AREA_SUBTYPE_ROB_HOUSE_OBJECT, i, idx);
    }
    if(RobberyHouseContract[idx][rhcType] == 1)
    {
        if(RobberyHouseContract[idx][rhcSafe] != INVALID_OBJECT_ID) DestroyDynamicObject(RobberyHouseContract[idx][rhcSafe]);
        RobberyHouseContract[idx][rhcSafe] = CreateDynamicObject(19619, RobberyHouseSafePos[class][0], RobberyHouseSafePos[class][1], RobberyHouseSafePos[class][2], RobberyHouseSafePos[class][3], RobberyHouseSafePos[class][4], RobberyHouseSafePos[class][5], houseid + 50, HOUSE_INT_ID_REPAIR, -1, 120.00, 120.00);
    }
    return 1;
}

GetFreeRobberyHouse()
{
    for(new i = totalhouses-1; i != -1; i--)
    {
        if(h_info[i][h_mysql_id] == INVALID_MYSQL_ID ||
            h_info[i][h_delete] == 1 ||
            h_info[i][h_int] != 4 ||
            h_info[i][h_rob_house] != 0) continue;
        if(random(3) != 1) continue;
        return i;
    }
    return -1;
}

GetRobberyHouseConctartPrice(idx)
{
    return h_info[idx][h_squar] * RENT_PRICE_ROBBERY_CONTRACT;
}

GetRobberyHouseSecrecy(idx)
{
    if(RobberyHouseContract[idx][rhcHouseSignaling] == 0)
    {
        new count[2];
        for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
        {
            if(RobberyHouseContract[idx][rhcPlayerID][i] != INVALID_PLAYER_ID) count[0]++;
            if(RobberyHouseContract[idx][rhcSkin][i] != 0) count[1]++;
        }
        if(count[0] == count[1])
        {
            return floatround(RobberyHouseContract[idx][rhcKush] * 0.20);
        }
    }
    return 0;
}

GetRobberyHouseShare(idx)
{
    new count;
    for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
    {
        if(RobberyHouseContract[idx][rhcPlayerID][i] != INVALID_PLAYER_ID) count++;
    }
    new kush = RobberyHouseContract[idx][rhcKush] + GetRobberyHouseSecrecy(idx);
    if(kush <= 0) return 0;
    else return kush / count;
}

ClearRobberyHouse(playerid, type = -1)
{
    p_temp[playerid][rob_house_idx] = -1;
    p_temp[playerid][rob_house_backup] = 0;
    p_temp[playerid][rob_house_backup_items][0] =
    p_temp[playerid][rob_house_backup_items][1] =
    p_temp[playerid][rob_house_backup_items][2] = -1;
    if(type != -1)
    {
        for(new i = 0; i < 10; i++) if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
    }
    return 1;
}

ClearRobberyHouseBackup(playerid, type = -1)
{
    p_temp[playerid][rob_house_backup_items][3] =
    p_temp[playerid][rob_house_backup_items][4] =
    p_temp[playerid][rob_house_backup_items][5] = -1;
    if(type != -1)
    {
        if(p_temp[playerid][rob_house_backup_pickup] != -1) DestroyDynamicPickup(p_temp[playerid][rob_house_backup_pickup]);
        if(p_temp[playerid][rob_house_backup_area] != -1) DestroyDynamicArea(p_temp[playerid][rob_house_backup_area]);
    }
    p_temp[playerid][rob_house_backup_pickup] = -1;
    p_temp[playerid][rob_house_backup_area] = -1;
    p_temp[playerid][rob_house_backup_pos][0] =
    p_temp[playerid][rob_house_backup_pos][1] =
    p_temp[playerid][rob_house_backup_pos][2] = 0.0;
    return 1;
}

SetFreeRobHouseObject(playerid, rob_idx, idx)
{
    for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER_ITEMS; i++)
    {
        if(p_temp[playerid][rob_house_backup_items][i] == -1)
        {
            p_temp[playerid][rob_house_backup_items][i] = idx;
            SendAccess(playerid, "Вы подобрали предмет \"%s\". Количество предметов в сумке: %d из %d.", RobberyHouseItems[idx][rhiName], MAX_ROBBERY_HOUSE_PLAYER_ITEMS - GetFreeRobHouseObject(playerid), MAX_ROBBERY_HOUSE_PLAYER_ITEMS);
            if(GetFreeRobHouseObject(playerid) == 0)
            {
                SendInfo(playerid, "В Вашей сумке нет места, отнесите её %s.", RobberyHouseContract[rob_idx][rhcVehicleIDx] == INVALID_VEHICLE_ID ? "на продажу к Владимиру" : "в транспортное средство");
                if(RobberyHouseContract[rob_idx][rhcVehicleIDx] != INVALID_VEHICLE_ID) SendInfo(playerid, "Чтобы разгрузить сумку, введите /robbing возле багажника.");
            }
            return 1;
        }
    }
    return -1;
}

GetFreeRobHouseObject(playerid)
{
    new count;
    for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER_ITEMS; i++)
    {
        if(p_temp[playerid][rob_house_backup_items][i] == -1) count++;
    }
    return count;
}

GetPlayerRobberyHouse(playerid)
{
    for(new i = 0; i < MAX_ROBBERY_HOUSE_CONTRACT; i++)
    {
        if(RobberyHouseContract[i][rhcOwnerID] == p_info[playerid][ID])
        {
            RobberyHouseContract[i][rhcPlayerID][0] = playerid;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "[ROBBERY] %s [%d] в игре.", get_name(playerid), playerid);
            SendRobberyHouseMessage(i, 0xDEB887FF, STRING_GLOBAL);
            p_temp[playerid][rob_house_idx] = i;
            if(RobberyHouseContract[i][rhcStatus] == 3) p_temp[playerid][rob_house_backup] = 1;
            return i;
        }
    }
    return -1;
}

CallingPoliceToRobberyHouse(idx, houseid)
{
    if(h_info[houseid][h_rob_house_signaling] == 1 && h_info[houseid][h_rob_house_block] == 0)
    {
        SendRobberyHouseMessage(idx, 0xDEB887FF, "[ROBBERY] В доме сработала сигнализация, сообщение отправлено сотрудникам полицейского департамента!");
        RobberyHouseContract[idx][rhcHouseSignaling] = 1;
        foreach(new i : gFactionPlayers[FBI_TEAM || POLICE_LS || POLICE_SF || POLICE_LV || POLICE_RC])
        {
            if(p_info[i][fwork] == true)
            {
                SendMes(i, COLOR_DARKORANGE, "[ОГРАБЛЕНИЕ ДОМА]: "W"Грабители в доме #%d, остановите грабителей! Место отмечено на GPS!", houseid);
                SetPlayerGPS(i, h_info[idx][h_enter][0], h_info[idx][h_enter][1], h_info[idx][h_enter][2], 5.0);
            }
        }
        new scdplayerid;
        for(new i = 0; i < MAX_ROBBERY_HOUSE_PLAYER; i++)
        {
            scdplayerid = RobberyHouseContract[idx][rhcPlayerID][i];
            if(scdplayerid != INVALID_PLAYER_ID)
            {
                if(p_info[scdplayerid][wanted] < 6)
                {
                    p_info[scdplayerid][wanted] = 6;
                    SetPlayerWantedLevel(scdplayerid, p_info[scdplayerid][wanted]);
                    SendInfo(scdplayerid, "В доме сработала сигнализация, Вы объявлены в розыск.");
                }
            }
        }
    }
    return 1;
}
