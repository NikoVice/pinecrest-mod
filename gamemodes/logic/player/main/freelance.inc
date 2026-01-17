ShowFreelance(playerid, type, idx = -1, first_parameter = -1)
{
    #pragma unused first_parameter
    switch(type)
    {
        case FREELANCE_TYPE_NPC:
        {
            ShowPlayerDialog(playerid, D_FREELANCE_NPC, DIALOG_STYLE_LIST, ""I"Работодатель Михаил", "\
            "I"[1]"W" Информация об бирже труда\n\
            "I"[2]"W" Список задач\n\
            "I"[3]"W" Текущая задача\n\
            "I"[4]"W" Личная статистика\n\
            "I"[5]"W" Рейтинг работников\n\
            "I"[6]"W" Арендовать рабочего для подпольного помещения", "Далее", "Отмена");
        }
        case FREELANCE_TYPE_INFO:
        {
            ShowPlayerDialog(playerid, D_FREELANCE_INFO, DIALOG_STYLE_MSGBOX, ""I"Работодатель Михаил", ""W"\
            Привет! Меня зовут "I"Михаил,"W" я — "I"работодатель,"W" который предоставляет различные задачи\n\
            по всем работам.\n\n\
            Задачи делятся на категории, всего их 5. Чем выше категория — тем "I"сложнее задача"W" и\n\
            "I"больше награды"W" за её выполнение.\n\n\
            На выполнение задачи "I"отводится определенное время,"W" за которое её необходимо выполнить.\n\n\
            Завершив выполнение задачи, тебе будет выдано "I"вознаграждение."W" После этого, если захочешь\n\
            выполнить новые задачи снова, возвращайся ко мне.\n\n\
            Игрокам, обладающим "I"VIP Gold"W" начисляется в два раза больше наград.", "Закрыть", "");
        }
        case FREELANCE_TYPE_LIST:
        {
            if(p_temp[playerid][freelance_idx] != -1) return ShowFreelance(playerid, FREELANCE_TYPE_NPC), SendError(playerid, "Вы уже выполняете задачу.");
            for(new i; i < 100; i++) p_temp[playerid][p_listitem][i] = -1;
            new count, task_idx;
            STRING_GLOBAL = "[#] Награда\tВремя на выполнение\tКатегория\n";
            for(new i = 0; i < MAX_FREELANCE_CONTRACT; i++)
            {
                if(FreelanceContract[i][fcStatus] != 1) continue;
                task_idx = FreelanceContract[i][fcTaskIDx];
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%d\n", STRING_GLOBAL, count + 1, GetPlayerFreelanceReward(playerid, i, task_idx), ConvertTime(FreelanceContract[i][fcTime]), FreelanceContract[i][fcCategory]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            if(count == 0)
            {
                SendError(playerid, "На данный момент нет задач, они появляются каждый час.");
                return ShowFreelance(playerid, FREELANCE_TYPE_NPC);
            }
            ShowPlayerDialog(playerid, D_FREELANCE_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список задач", STRING_GLOBAL, "Далее", "Отмена");
        }
        case FREELANCE_TYPE_CONTRACT:
        {
            new task_idx = FreelanceContract[idx][fcTaskIDx];
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Задача: "I"%s"W"\n\
            Необходимое количество: {"#cBLUE"}%d"W"\n\n\
            Награда: %s\n\n\
            Время на выполнение задачи: {"#cLIGHTRED"}%s"W"\n\
            Категория: {"#cYELLOW"}%d"W"\n\n\
            Вы действительно хотите начать выполнение этой задачи?", FreelanceTask[task_idx][ftText], GetFreelanceProgress(idx, task_idx), GetPlayerFreelanceReward(playerid, idx, task_idx), ConvertTime(FreelanceContract[idx][fcTime]), FreelanceContract[idx][fcCategory]);
            ShowPlayerDialog(playerid, D_FREELANCE_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Информация о задаче", STRING_GLOBAL, "Да", "Нет");
            SetPVarInt(playerid, "Freelance:idx", idx);
        }
        case FREELANCE_TYPE_CONTRACT_START:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Для получения награды за выполнение задачи, её необходимо выполнить в срок!\n\n\
            На выполнение задачи отводится "I"%s,"W" не затягивай!\n\n\
            Если ты согласен со всеми условиями, нажми "I"\"Далее\"."W" После этого ты сможешь\n\
            "I"подробно ознакомиться"W" со всем с помощью команды "I"/freelance"W"\n\n\
            {"#cLIGHTRED"}Обратите внимание! Если задача будет выполнена не полностью, награда не будет выдана!", ConvertTime(FreelanceContract[idx][fcTime]));
            ShowPlayerDialog(playerid, D_FREELANCE_CONTRACT_START, DIALOG_STYLE_MSGBOX, ""I"Пояснение к задаче", STRING_GLOBAL, "Далее", "Отмена");
        }
        case FREELANCE_TYPE_CONTRACT_INFO:
        {
            if(idx == -1) return 1;
            new task_idx = FreelanceContract[idx][fcTaskIDx];
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Задача: "I"%s"W"\n\
            Прогресс: {"#cBLUE"}%d из %d"W"\n\n\
            Награда: %s\n\n\
            Время на выполнение задачи: {"#cLIGHTRED"}%s"W"\n\
            Категория: {"#cYELLOW"}%d", FreelanceTask[task_idx][ftText], FreelanceContract[idx][fcProgress], GetFreelanceProgress(idx, task_idx), GetPlayerFreelanceReward(playerid, idx, task_idx), ConvertTime(FreelanceContract[idx][fcTime]), FreelanceContract[idx][fcCategory]);
            ShowPlayerDialog(playerid, D_FREELANCE_CONTRACT_INFO, DIALOG_STYLE_MSGBOX, ""I"Текущая задача", STRING_GLOBAL, "Закрыть", "");
        }
        case FREELANCE_TYPE_STATS:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Категория: {"#cYELLOW"}%d из 5."W"\n\
            Всего выполненных задач: {"#cBLUE"}%d"W"\n\n\
            Заработано {"#cGREEN"}%d$ и %d Flin Money"W" выполняя различные задачи.", p_info[playerid][freelance_lvl], p_info[playerid][freelance_success], p_info[playerid][freelance_money], p_info[playerid][freelance_fm]);
            ShowPlayerDialog(playerid, D_FREELANCE_STATS_INFO, DIALOG_STYLE_MSGBOX, ""I"Личная статистика", STRING_GLOBAL, "Закрыть", "");
        }
        case FREELANCE_TYPE_TOP:
        {
            mysql_tquery(con_bd, "SELECT * FROM `accounts` WHERE `freelance_success` != 0 ORDER BY `freelance_success` DESC LIMIT 25", "ShowFreelanceTop", "d", playerid);
        }
        case FREELANCE_TYPE_MENU:
        {
            if(p_temp[playerid][freelance_idx] == -1)
            {
                if(IsPlayerInRangeOfPoint(playerid, 2.5, 2349.8655,1586.4042,1010.8090)) ShowFreelance(playerid, FREELANCE_TYPE_NPC);
                SendError(playerid, "У Вас нет активной задачи.");
                return 1;
            }
            STRING_GLOBAL[0] = EOS;
            ShowPlayerDialog(playerid, D_FREELANCE_MENU, DIALOG_STYLE_LIST, ""I"Меню задачи", "\
            "I"[1]"W" Информация о задаче\n\
            "I"[2]"W" Найти место выполнения\n\
            "I"[3]"W" Найти работодателя\n\
            "I"[4]"W" Продлить время на выполнение задачи\n\
            {"#cLIGHTRED"}[5] Завершить выполнение задачи", "Далее", "Отмена");
        }
        case FREELANCE_TYPE_EXTEND_CONTRACT:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Если по каким-то причинам ты не успеваешь выполнить задачу, можешь продлить\n\
            время выполнение задачи, но обойдется тебе это в "I"%d$."W"\n\n\
            Вы действительно хотите продлить выполнение задачи?\n\n\
            {"#cLIGHTRED"}Обратите внимание! Продлить выполнение задачи можно 1 раз!"W"", FreelanceTask[idx][ftPrice]);
            ShowPlayerDialog(playerid, D_FREELANCE_EXTEND_CONTRACT, DIALOG_STYLE_MSGBOX, ""I"Продлить время на выполнение задачи", STRING_GLOBAL, "Да", "Нет");
        }
        case FREELANCE_TYPE_DELETE:
        {
            ShowPlayerDialog(playerid, D_FREELANCE_DELETE, DIALOG_STYLE_MSGBOX, ""I"Завершить выполнение задачи", ""W"Вы действительно хотите завершить выполнение задачи?", "Да", "Нет");
        }
    }
    return 1;
}

LoadFreelance()
{
    CreateDynamicObject(1557, 1496.89722, -1580.10254, 12.59610, 0.00000, 0.00000, 0.00000);
    CreateDynamicObject(1557, 1499.91736, -1580.10046, 12.59610, 0.00000, 0.00000, 180.00000);

    new actorid = CreateActor(181, 2351.4375,1586.4545,1010.7941,88.3737);
    SetActorVirtualWorld(actorid, 111);
    CreateDynamic3DTextLabel("NPC: "I"Михаил", COLOR_WHITE, 2351.4375,1586.4545,1010.7941 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreatePickup(1239, 23, 2349.8655,1586.4042,1010.8090, 111);
    return 1;
}

CMD:freelance(playerid, params[])
{
    ShowFreelance(playerid, FREELANCE_TYPE_MENU);
    return 1;
}

CMD:load_frcontract(playerid, params[])
{
    if(!FD(playerid) && p_info[playerid][admin] < 10) return 1;

    for(new i = 0; i < MAX_FREELANCE_CONTRACT; i++)
    {
        if(FreelanceContract[i][fcStatus] == 0) CreateFreelanceContract(i);
    }

    SendAccess(playerid, "Вы создали максимальное количество контрактов для биржи труда.");
    return 1;
}

CheckFreelanceContract()
{
    new scdplayerid;
    for(new i = 0; i < MAX_FREELANCE_CONTRACT; i++)
    {
        if(FreelanceContract[i][fcStatus] == 2)
        {
            FreelanceContract[i][fcTime]--;
            if(FreelanceContract[i][fcTime] == 0)
            {
                scdplayerid = FreelanceContract[i][fcOwnerID];
                if(scdplayerid != INVALID_PLAYER_ID)
                {
                    FreelanceContract[i][fcAccountID] = INVALID_MYSQL_ID;
                    FreelanceContract[i][fcOwnerID] = INVALID_PLAYER_ID;
                    ClearPlayerFreelance(scdplayerid);
                    SendInfo(scdplayerid, "Время на выполнение контракта вышло.");
                }
                DestroyFreelanceContract(i);
            }
        }
    }
    return 1;
}

CheckFreelanceContractList()
{
    new count, max_count = random(5);
    for(new i = 0; i < MAX_FREELANCE_CONTRACT; i++)
    {
        if(FreelanceContract[i][fcStatus] == 0)
        {
            CreateFreelanceContract(i);
            count++;
        }
        if(count == max_count) break;
    }
    return 1;
}

CreateFreelanceContract(idx)
{
    FreelanceContract[idx][fcStatus] = 1;
    FreelanceContract[idx][fcCategory] = 1 + random(4);
    FreelanceContract[idx][fcAccountID] = INVALID_MYSQL_ID;
    FreelanceContract[idx][fcOwnerID] = INVALID_PLAYER_ID;
    new task_idx = random(MAX_FREELANCE_TASK);
    FreelanceContract[idx][fcTime] = FreelanceTask[task_idx][ftTime] * FreelanceContract[idx][fcCategory];
    FreelanceContract[idx][fcTimeUpdate] = 0;
    FreelanceContract[idx][fcTaskIDx] = task_idx;
    FreelanceContract[idx][fcProgress] = 0;
    return 1;
}

DestroyFreelanceContract(idx)
{
    FreelanceContract[idx][fcStatus] = 0;
    FreelanceContract[idx][fcCategory] = 0;
    FreelanceContract[idx][fcAccountID] = INVALID_MYSQL_ID;
    FreelanceContract[idx][fcOwnerID] = INVALID_PLAYER_ID;
    FreelanceContract[idx][fcTime] = 0;
    FreelanceContract[idx][fcTimeUpdate] = 0;
    FreelanceContract[idx][fcTaskIDx] = 0;
    FreelanceContract[idx][fcProgress] = 0;
    return 1;
}

GetPlayerFreelanceReward(playerid, i, idx) // i - ID контракта, idx - ID задания;
{ // Узнать приз в зависимости от категории;
    new str[128] = "{"#cGREEN"}", freelance_reward_name[2][12] = {"$", "Flin Money"}, count, price[2];
    for(new x = 0; x < 2; x++)
    {
        if(FreelanceTask[idx][ftReward][x] == 0) continue;
        if(x == 0)
        {
            price[1] = FreelanceTask[idx][ftReward][x] * FreelanceContract[i][fcCategory];

            if(p_info[playerid][p_vip])
            {
                if(p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 3) price[0] = price[1] * 3;
                else
                {
                    switch(p_info[playerid][p_vip])
                    {
                        case 1: price[0] = price[1] + ((price[1] / 100) * 25);
                        case 2: price[0] = price[1] + ((price[1] / 100) * 50);
                        case 3: price[0] = price[1] + price[1];
                    }
                }
            } else price[0] = FreelanceTask[idx][ftReward][x] * FreelanceContract[i][fcCategory];
        } else price[0] = FreelanceTask[idx][ftReward][x] * FreelanceContract[i][fcCategory];
        if(count == 0) format(str, sizeof(str), "%s %d %s", str, price[0], freelance_reward_name[x]);
        else format(str, sizeof(str), "%s + %d %s", str, price[0], freelance_reward_name[x]);
        count++;
    }
    strcat(str, ""W"");
    return str;
}

GetFreelanceProgress(i, idx) // i - ID контракта, idx - ID задания;
{ // Узнать приз в зависимости от категории;
    return FreelanceTask[idx][ftProgress] * FreelanceContract[i][fcCategory];
}

ClearPlayerFreelance(playerid)
{
    p_temp[playerid][freelance_idx] = -1;
    return 1;
}

GetPlayerFreelance(playerid)
{
    for(new i = 0; i < MAX_FREELANCE_CONTRACT; i++)
    {
        if(FreelanceContract[i][fcAccountID] == p_info[playerid][ID])
        {
            FreelanceContract[i][fcOwnerID] = playerid;
            p_temp[playerid][freelance_idx] = i;
            return i;
        }
    }
    return -1;
}

CheckPlayerFreelance(playerid, idx, count = 1)
{
    new i = p_temp[playerid][freelance_idx];
    if(i == -1) return 1;
    new task_idx = FreelanceContract[i][fcTaskIDx];
    if(task_idx != idx) return 1;

    FreelanceContract[i][fcProgress] += count;
    if(FreelanceContract[i][fcProgress] >= GetFreelanceProgress(i, task_idx))
    {
        p_info[playerid][freelance_success]++;
        MysqlUpdatePlayerInt(playerid, "freelance_success", p_info[playerid][freelance_success]);
        if(p_info[playerid][freelance_lvl] < 5 && p_info[playerid][freelance_success]%100 == 0)
        {
            p_info[playerid][freelance_lvl]++;
            MysqlUpdatePlayerInt(playerid, "freelance_lvl", p_info[playerid][freelance_lvl]);
        }

        SendAccess(playerid, "Вы выполнили задачу: %s.", FreelanceTask[task_idx][ftText]);
        SendInfo(playerid, "Награда за выполнение задания: %s.", GetPlayerFreelanceReward(playerid, i, task_idx));

        GivePlayerFreelanceReward(playerid, i, task_idx);

        ClearPlayerFreelance(playerid);
        DestroyFreelanceContract(i);

        CheckPlayerMission(playerid, DAILY_FTASK);
        CheckPlayerMission(playerid, ACHIEVEMENT_FTASK);

        if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(playerid, -1);
    }
    return 1;
}

GivePlayerFreelanceReward(playerid, idx, task_idx)
{
    new count;
    if(FreelanceTask[task_idx][ftReward][0] != 0)
    {
        count = FreelanceTask[task_idx][ftReward][0] * FreelanceContract[idx][fcCategory];

        new bizid = 111;
        if(b_info[bizid][_prod] >= ((count / 100) * 25) / 100)
        {
            b_info[bizid][_prod] -= ((count / 100) * 25) / 100;
            b_info[bizid][_bank] += ((count / 100) * 25) - ((count / 100) * 2);
            AddMafiaBank(bizid, (count / 100) * 2);

            biz_finka[bizid] += ((count / 100) * 25) - ((count / 100) * 2);
            UpdateIntForFinanceBiz(bizid, ((count / 100) * 25) - ((count / 100) * 2));
        }

        if(p_info[playerid][p_vip])
        {
            if(p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) count = count * 3;
            else
            {
                switch(p_info[playerid][p_vip])
                {
                    case 1: count = count + ((count / 100) * 25);
                    case 2: count = count + ((count / 100) * 50);
                    case 3: count = count + count;
                }
            }
        } else count = FreelanceTask[task_idx][ftReward][0] * FreelanceContract[idx][fcCategory];

        OnServerInfoForMoney[19] += count;
        SetPlayerMoney(playerid, count, true, "выполнил задачу %s <%s>", FreelanceTask[task_idx][ftText]);

        p_info[playerid][freelance_money] += count;
        MysqlUpdatePlayerInt(playerid, "freelance_money", p_info[playerid][freelance_money]);
    }
    if(FreelanceTask[task_idx][ftReward][1] != 0)
    {
        count = FreelanceTask[task_idx][ftReward][1] * FreelanceContract[idx][fcCategory];

        p_info[playerid][flinmoney] += count;
        MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

        p_info[playerid][freelance_fm] += count;
        MysqlUpdatePlayerInt(playerid, "freelance_fm", p_info[playerid][freelance_fm]);

        Log(LOG_player, INFO, "%s[%d](%s %s) выполнил задачу %s награда %d Flin Money",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            FreelanceTask[task_idx][ftText], count);
    }
    return 1;
}

forward ShowFreelanceTop(playerid);
public ShowFreelanceTop(playerid)
{
    if(cache_num_rows())
    {
        new nickname[32], p_freelance_lvl, p_freelance_success, p_freelance_money, p_freelance_fm;
        STRING_GLOBAL = "[#] Ник\tКатегория\tВыполненных задач\tЗаработано $ и Flin Money\n", STRING_MIN[0] = EOS;
        for(new i; i < 25; i++)
        {
            if(i >= cache_num_rows()) break;
            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
            cache_get_value_name_int(i, "freelance_lvl", p_freelance_lvl);
            cache_get_value_name_int(i, "freelance_success", p_freelance_success);
            cache_get_value_name_int(i, "freelance_money", p_freelance_money);
            cache_get_value_name_int(i, "freelance_fm", p_freelance_fm);
            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\t%d\t%d$ и %d Flin Money\n", i+1, nickname, p_freelance_lvl, p_freelance_success, p_freelance_money, p_freelance_fm);
            strcat(STRING_GLOBAL, STRING_MIN);
        }
        ShowPlayerDialog(playerid, D_FREELANCE_STATS_INFO, DIALOG_STYLE_TABLIST_HEADERS, ""I"Рейтинг работников", STRING_GLOBAL, "Далее", "Отмена");
    } else ShowFreelance(playerid, FREELANCE_TYPE_NPC), SendError(playerid, "Ничего не найдено.");
    return 1;
}

GetPlayerFreelanceCoords(playerid, idx)
{
    if(IsPlayerInAnyVehicle(playerid))
    {
        new vehicleid = GetPlayerVehicleID(playerid);

        if(veh_info[vehicleid][v_npoType] == NPO_JOB &&
            (veh_info[vehicleid][v_npoId] == JOB_BUS || veh_info[vehicleid][v_npoId] == JOB_PIZZABOY ||
            veh_info[vehicleid][v_npoId] == JOB_COLLECTOR || veh_info[vehicleid][v_npoId] == JOB_FIREMAN ||
            veh_info[vehicleid][v_npoId] == JOB_CONSTRUCTION_FORKLIFT || veh_info[vehicleid][v_npoId] == JOB_ROBBER ||
            veh_info[vehicleid][v_npoId] == JOB_TRAIN || veh_info[vehicleid][v_npoId] == JOB_TRAM ||
            veh_info[vehicleid][v_npoId] == JOB_PILOT || veh_info[vehicleid][v_npoId] == JOB_RAILWAY_FACTORY_FORKLIFT ||
            veh_info[vehicleid][v_npoId] == JOB_HUNTING || veh_info[vehicleid][v_npoId] == JOB_PANEL) ||
            veh_info[vehicleid][v_temp_job] == JOB_BUS || veh_info[vehicleid][v_temp_job] == JOB_COLLECTOR ||
            veh_info[vehicleid][v_temp_job] == JOB_FIREMAN || veh_info[vehicleid][v_temp_job] == JOB_PILOT) return 1;
    }

    if(p_temp[playerid][Work_ID] == CONSTRUCTION_WORK || p_temp[playerid][Work_ID] == LABORATORY_WORK ||
        p_temp[playerid][Work_ID] == SPACE_WORK || p_temp[playerid][Work_ID] == RAILWAY_WORK ||
        p_temp[playerid][Work_ID] == FARM_WORK || p_temp[playerid][Work_ID] == COLLECTOR_WORK ||
        p_temp[playerid][Work_ID] == ROBBER_WORK || p_temp[playerid][Work_ID] == CAR_FACTORY_WORK) return 1;

    if(TheftCarGPS[playerid] != false) return 1;

    if(FreelanceTask[idx][ftCoords][0] == 0.0 && FreelanceTask[idx][ftCoords][1] == 0.0 && FreelanceTask[idx][ftCoords][2] == 0)
    {
        new Float:FreelanceCoords[8][4], FreelanceIDx = -1, FreelanceMaxIDx, bool:FreelanceCheckSuccess;
        new max_distance = 100000, here_distance = -1;
        switch(idx)
        {
            case 9: // Водитель автобуса;
            {
                FreelanceCoords[0][0] = 1104.3624, FreelanceCoords[0][1] = -1740.9139, FreelanceCoords[0][2] = 13.4631;
                FreelanceCoords[1][0] = -1980.3877, FreelanceCoords[1][1] = 97.5302, FreelanceCoords[1][2] = 27.6875;
                FreelanceCoords[2][0] = 2778.9050, FreelanceCoords[2][1] = 1283.0614, FreelanceCoords[2][2] = 10.7500;
                FreelanceCoords[3][0] = 1665.4716, FreelanceCoords[3][1] = -1113.7278, FreelanceCoords[3][2] = 23.9063;

                FreelanceMaxIDx = 4, FreelanceCheckSuccess = true;
            }
            case 10: // Транспортные компании;
            {
                FreelanceCoords[0][0] = -478.446, FreelanceCoords[0][1] = -513.438, FreelanceCoords[0][2] = 25.5178;
                FreelanceCoords[1][0] = -229.097, FreelanceCoords[1][1] = -251.117, FreelanceCoords[1][2] = 1.42188;
                FreelanceCoords[2][0] = 58.7898, FreelanceCoords[2][1] = -263.999, FreelanceCoords[2][2] = 1.57812;

                FreelanceMaxIDx = 3, FreelanceCheckSuccess = true;
            }
            case 13: // Пожарный;
            {
                FreelanceCoords[0][0] = 1756.2947, FreelanceCoords[0][1] = -1455.3763, FreelanceCoords[0][2] = 13.5469;
                FreelanceCoords[1][0] = -2014.3455, FreelanceCoords[1][1] = 83.9995, FreelanceCoords[1][2] = 27.6799;
                FreelanceCoords[2][0] = 1760.9218, FreelanceCoords[2][1] = 2060.6863, FreelanceCoords[2][2] = 10.9766;

                FreelanceMaxIDx = 3, FreelanceCheckSuccess = true;
            }
            case 14: // Машинист поезда;
            {
                FreelanceCoords[0][0] = 1778.0112, FreelanceCoords[0][1] = -1953.6497, FreelanceCoords[0][2] = 14.8756;
                FreelanceCoords[1][0] = -1942.1152, FreelanceCoords[1][1] = 142.9281, FreelanceCoords[1][2] = 27.0006;
                FreelanceCoords[2][0] = 1474.9150, FreelanceCoords[2][1] = 2632.2500, FreelanceCoords[2][2] = 12.1256;
                FreelanceCoords[3][0] = 2864.7500, FreelanceCoords[3][1] = 1299.6431, FreelanceCoords[3][2] = 12.1256;

                FreelanceMaxIDx = 4, FreelanceCheckSuccess = true;
            }
            case 16: // Пилот;
            {
                FreelanceCoords[0][0] = 1645.9452, FreelanceCoords[0][1] = -2430.2759, FreelanceCoords[0][2] = 13.5547;
                FreelanceCoords[1][0] = -1223.0778, FreelanceCoords[1][1] = -162.3596, FreelanceCoords[1][2] = 14.1484;
                FreelanceCoords[2][0] = 1525.8293, FreelanceCoords[2][1] = 1782.4193, FreelanceCoords[2][2] = 10.8203;

                FreelanceMaxIDx = 3, FreelanceCheckSuccess = true;
            }
        }

        if(FreelanceCheckSuccess == true)
        {
            for(new i = 0; i < FreelanceMaxIDx; i++)
            {
                here_distance = (!IsPlayerInAnyVehicle(playerid)) ? floatround(GetPlayerDistanceFromPoint(playerid, FreelanceCoords[i][0], FreelanceCoords[i][1], FreelanceCoords[i][2])) : floatround(GetVehicleDistanceFromPoint(GetPlayerVehicleID(playerid), FreelanceCoords[i][0], FreelanceCoords[i][1], FreelanceCoords[i][2]));
                if(here_distance < max_distance)
                {
                    FreelanceIDx = i;
                    max_distance = here_distance;
                }
            }
            if(max_distance == -1 || FreelanceIDx == -1) return 1;
            SetPlayerGPS(playerid, FreelanceCoords[FreelanceIDx][0], FreelanceCoords[FreelanceIDx][1], FreelanceCoords[FreelanceIDx][2], 5.0);
            new Float:distance = GetPlayerDistanceFromPoint(playerid, FreelanceCoords[FreelanceIDx][0], FreelanceCoords[FreelanceIDx][1], FreelanceCoords[FreelanceIDx][2]);
            SendInfo(playerid, "Место начала задания отмечено на GPS навигаторе. Расстояние: %.0f метров.", distance);
        }
    }
    else
    {
        SetPlayerGPS(playerid, FreelanceTask[idx][ftCoords][0], FreelanceTask[idx][ftCoords][1], FreelanceTask[idx][ftCoords][2], 5.0);
        new Float:distance = GetPlayerDistanceFromPoint(playerid, FreelanceTask[idx][ftCoords][0], FreelanceTask[idx][ftCoords][1], FreelanceTask[idx][ftCoords][2]);
        SendInfo(playerid, "Место начала задания отмечено на GPS навигаторе. Расстояние: %.0f метров.", distance);
    }
    return 1;
}
