ShowBattlePass(playerid, type, idx = -1, first_parameter = -1)
{
    if(BattlePassTime == 0) return 1;
    #pragma unused idx
    #pragma unused first_parameter
    switch(type)
    {
        case BATTLEPASS_TYPE_SHOP:
        {
            STRING_GLOBAL = "[#] Название\tСтатус\tСтоимость\n";
            f(STRING_GLOBAL, "%s"W"\
            "I"[1]"W" Приобрести Battle Pass Premium\t%s\t%d Flin Money\n\
            "I"[2]"W" Приобрести ускоритель опыта\t%s\t%d Flin Money\n\
            "I"[3]"W" Приобрести уровни\t%s\t1 уровень - %d Flin Money",
            STRING_GLOBAL,
            p_info[playerid][battle_info][0] == 0 ? "{"#cRED"}Можно купить"W"" : "{"#cGREEN"}Куплен"W"", BATTLEPASS_PRICE_PREMIUM,
            p_info[playerid][battle_info][1] == 0 ? "{"#cRED"}Можно купить"W"" : "{"#cGREEN"}Куплен"W"", BATTLEPASS_PRICE_SPEED,
            GetPlayerBattlePassLevel(playerid), BATTLEPASS_PRICE_LVL);
            ShowPlayerDialog(playerid, D_BATTLEPASS_SHOP, DIALOG_STYLE_TABLIST_HEADERS, "{"#cPINK"}Battle Pass:"W" Магазин", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case BATTLEPASS_TYPE_ALL_REWARD:
        {
            STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
            new count;
            for(new i = 0; i < MAX_BATTLEPASS_REWARD; i++)
            {
                f(STRING_MIN, "%d. %s%s", i + 1, GetPlayerBattlePassRewardInfo(i), count == 2 ? "\n" : "\t");
                strcat(STRING_GLOBAL, STRING_MIN);
                count++;
                if(count == 3) count = 0;
            }
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST, "{"#cPINK"}Battle Pass:"W" Все награды", STRING_GLOBAL, "Закрыть", "");
        }
        case BATTLEPASS_TYPE_CHANGE:
        {
            STRING_GLOBAL = "[#] Название\tКоличество Battle Pass Coin\n", STRING_MIN[0] = EOS;
            for(new i = 0; i < MAX_CHANGE_BATTLEPASS_COINS; i++)
            {
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d\n", i + 1, GetBattlePassCoinsName(ChangeBattlePassCoins[i][cbcType], ChangeBattlePassCoins[i][cbcIDx]), ChangeBattlePassCoins[i][cbcPrice]);
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_BATTLEPASS_CHANGE, DIALOG_STYLE_TABLIST_HEADERS, "{"#cPINK"}Battle Pass:"W" Обмен Battle Pass Coin", STRING_GLOBAL, "Далее", "Отмена");
        }
        case BATTLEPASS_TYPE_TOP:
        {
            mysql_tquery(con_bd, "SELECT * FROM `accounts` WHERE `battle_lvl` != 1 ORDER BY `battle_lvl` DESC LIMIT 25", "ShowBattlePassTop", "d", playerid);
        }
        case BATTLEPASS_TYPE_STATS:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Тип: %s\n\n\
            Уровень: {"#cGREEN"}%d из %d"W"\n\
            Опыта: {"#cGREEN"}%d из %d"W"\n\
            Battle Pass Coin: {"#cGREEN"}%d"W"\n\n\
            Ускоритель опыта: %s",
            p_info[playerid][battle_info][0] == 0 ? "{"#cRED"}Обычный"W"" : "{"#cGREEN"}Premium"W"",
            p_info[playerid][battle_lvl], MAX_BATTLEPASS_REWARD,
            p_info[playerid][battle_info][2], GetPlayerBattlePassProgress(playerid),
            p_info[playerid][battle_info][4],
            p_info[playerid][battle_info][1] == 0 ? "{"#cRED"}Нет"W"" : "{"#cGREEN"}Есть"W"");
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"#cPINK"}Battle Pass:"W" Статистика", STRING_GLOBAL, "Закрыть", "");
        }
        case BATTLEPASS_TYPE_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i; i < sizeof(BattlePassInfoList); i++) strcat(STRING_GLOBAL, BattlePassInfoList[i]);
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"#cPINK"}Battle Pass:"W" Информация", STRING_GLOBAL, "Закрыть", "");
        }
    }
    return 1;
}

forward ShowBattlePassTop(playerid);
public ShowBattlePassTop(playerid)
{
    if(BattlePassTime == 0) return 1;
    if(cache_num_rows())
    {
        new data[144], nickname[32], p_battle_lvl, p_battle_lvl_task, p_battle_info[5];
        STRING_GLOBAL = "[#] Ник\tТип и уровень\tКатегория заданий\tУскоритель опыта\n", STRING_MIN[0] = EOS;
        for(new i; i < 25; i++)
        {
            if(i >= cache_num_rows()) break;
            cache_get_value_name(i, "name", nickname, MAX_PLAYER_NAME);
            cache_get_value_name_int(i, "battle_lvl", p_battle_lvl);
            cache_get_value_name_int(i, "battle_lvl_task", p_battle_lvl_task);
            cache_get_value_name(i, "battle_info", data); // 0|0|0|0|0
            sscanf(data, "p<|>a<i>[5]", p_battle_info);
            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s, %d уровень\t%d\t%s\n", i+1, nickname, p_battle_info[0] == 0 ? "{"#cGREEN"}Обычный"W"" : "{"#cRED"}Premium"W"", p_battle_lvl, p_battle_lvl_task, p_battle_info[1] == 0 ? "{"#cGREEN"}Нет"W"" : "{"#cRED"}Есть"W"");
            strcat(STRING_GLOBAL, STRING_MIN);
        }
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, "{"#cPINK"}Battle Pass:"W" Рейтинг", STRING_GLOBAL, "Закрыть", "");
    } else SendError(playerid, "Ничего не найдено.");
    return 1;
}

CheckPlayerBattlePass(playerid, idx)
{
    if(BattlePassTime == 0) return 1;
    if(p_info[playerid][battle_lvl] == MAX_BATTLEPASS_REWARD) return 1;
    for(new i = 0; i < MAX_PLAYER_BATTLEPASS_TASK; i++)
    {
        if(p_info[playerid][battle_task_active][i] == idx)
        {
            new max_progress = GetPlayerBattlePassTask(playerid, idx);
            if(p_info[playerid][battle_task][idx] == max_progress) return 1;
            p_info[playerid][battle_task][idx]++;
            if(p_info[playerid][battle_task][idx] == max_progress)
            {
                new max_value[3];
                SendMes(playerid, COLOR_GREEN, "[BATTLE PASS]:"W" Вы выполнили задание из Battle Pass.");

                max_value[0] = GetPlayerBattlePassReward(playerid, BattlePassTask[idx][bpReward][0]); // Battle Pass EXP;
                max_value[1] = BattlePassTask[idx][bpReward][1]; // Money;
                max_value[2] = GetPlayerBattlePassReward(playerid, BattlePassTask[idx][bpReward][2]); // Battle Pass Coin;

                if(p_info[playerid][battle_info][1] == 1) max_value[0] = max_value[0] * 2;
                new count = GetPlayerCount(playerid);
                if(count != 1)
                {
                    max_value[1] = max_value[1] * count;
                    max_value[2] = max_value[2] * count;
                }

                SetPlayerMoney(playerid, max_value[1], true, "BattlePass: выполнил задание");
                p_info[playerid][battle_info][4] += max_value[2];

                SendMes(playerid, COLOR_GREEN, "[BATTLE PASS]:"W" Награда: %d Battle Pass EXP, %d$ и %d Battle Pass Coin.", max_value[0], max_value[1], max_value[2]);

                UpdatePlayerBattlePassLevel(playerid, max_value[0]);
            }
            SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_TASK);

            if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(playerid, -1);
        }
    }
    return 1;
}

UpdatePlayerBattlePassLevel(playerid, count)
{
    if(BattlePassTime == 0) return 1;
    new max_value = GetPlayerBattlePassProgress(playerid);
    p_info[playerid][battle_info][2] += count;
    if(p_info[playerid][battle_info][2] >= max_value)
    {
        new balance = p_info[playerid][battle_info][2] - max_value;
        p_info[playerid][battle_lvl]++;
        if(p_info[playerid][battle_lvl] == MAX_BATTLEPASS_REWARD)
        {
            p_info[playerid][battle_info][3] = 0;
            for(new i = 0; i < MAX_BATTLEPASS_TASK; i++) p_info[playerid][battle_task][i] = 0;
            SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_TASK);
        }
        p_info[playerid][battle_info][2] = balance;
        SendMes(playerid, COLOR_GREEN, "[BATTLE PASS]:"W" Ваш уровень Battle Pass повышен.");
        new update_level = GetPlayerBattleTaskLevel(playerid);
        if(p_info[playerid][battle_lvl_task] != update_level)
        {
            p_info[playerid][battle_lvl_task] = update_level;
            UpdatePlayerBattlePassTask(playerid, true);
        }
    }
    SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_INFO);
    return 1;
}

UpdatePlayerBattlePassTask(playerid, bool:status = false)
{
    if(BattlePassTime == 0) return 1;
    new min_battle_task[5] = {0, 5, 10, 14, 20}, max_battle_task[5] = {4, 9, 13, 19, 25};
    if(status == false)
    {
        for(new i = 0; i < MAX_BATTLEPASS_TASK; i++)
        {
            if(i < MAX_PLAYER_BATTLEPASS_TASK) p_info[playerid][battle_task_active][i] = RandomEx(min_battle_task[i], max_battle_task[i]);
            p_info[playerid][battle_task][i] = 0;
        }
    }
    else
    {
        new idx;
        for(new i = 0; i < MAX_PLAYER_BATTLEPASS_TASK; i++)
        {
            idx = p_info[playerid][battle_task_active][i];
            if(p_info[playerid][battle_task][idx] >= BattlePassTask[idx][bpProgress] * (p_info[playerid][battle_lvl_task] - 1))
            {
                p_info[playerid][battle_task_active][i] = RandomEx(min_battle_task[i], max_battle_task[i]);
                p_info[playerid][battle_task][idx] = 0;
            }
        }
    }
    SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_TASK);
    return 1;
}

GetPlayerBattlePassProgress(playerid)
{
    if(BattlePassTime == 0) return 1;
    if(p_info[playerid][battle_lvl] == MAX_BATTLEPASS_REWARD) return 0;
    return MIN_BATTLEPASS_PROGRESS_LVL + ((p_info[playerid][battle_lvl] - 1) * MAX_BATTLEPASS_PROGRESS_LVL);
}

GetPlayerBattlePassTask(playerid, idx)
{
    if(BattlePassTime == 0) return 1;
    if(p_info[playerid][battle_lvl] == MAX_BATTLEPASS_REWARD) return 0;
    return BattlePassTask[idx][bpProgress] * p_info[playerid][battle_lvl_task];
}

GetPlayerBattleTaskLevel(playerid)
{
    if(BattlePassTime == 0) return 1;
    switch(p_info[playerid][battle_lvl])
    {
        case 1 .. 10: return 1;
        case 11 .. 20: return 2;
        case 21 .. 30: return 3;
        case 31 .. 40: return 4;
        case 41 .. 50: return 5;
        case 51 .. 60: return 6;
        case 61 .. 70: return 7;
        case 71 .. 80: return 8;
        case 81 .. 90: return 9;
        case 91 .. 100: return 10;
    }
    return 1;
}

GetPlayerBattlePassReward(playerid, count)
{
    if(BattlePassTime == 0) return 1;
    return count * p_info[playerid][battle_lvl_task];
}

GetPlayerBattlePassRewardButton(playerid, idx)
{
    new str[64] = "Забрать";
    if(p_info[playerid][battle_reward][idx] == 1) str = "Забрана";
    if(BattlePassReward[idx][bprStatus] == true && p_info[playerid][battle_info][0] == 0) str = "Для Premium";
    return str;
}

GetPlayerBattlePassRewardModel(playerid, idx, i)
{
    if(BattlePassTime == 0) return 1;
    switch(BattlePassReward[i][bprType])
    {
        case BATTLEPASS_TYPE_MONEY:
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][idx], 1212);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][idx], 90.0000, 0.0000, 0.0000, 1.0000);
        }
        case BATTLEPASS_TYPE_DONATE:
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][idx], 1274);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][idx], 0.0000, 0.0000, 0.0000, 1.5000);
        }
        case BATTLEPASS_TYPE_VIP:
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][idx], 1247);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][idx], 0.0000, 0.0000, 0.0000, 1.5000);
        }
        case BATTLEPASS_TYPE_SKIN:
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][idx], ItemsInfo[BattlePassReward[i][bprCount][0]][iModel]);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][idx], 0.0000, 0.0000, 0.0000, 1.5500);
        }
        case BATTLEPASS_TYPE_ACC, BATTLEPASS_TYPE_INVENTORY:
        {
            new temp_idx = BattlePassReward[i][bprCount][0];
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][idx], ItemsInfo[temp_idx][iModel]);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][idx], ItemsInfo[temp_idx][iObjectPos][0], ItemsInfo[temp_idx][iObjectPos][1], ItemsInfo[temp_idx][iObjectPos][2], ItemsInfo[temp_idx][iObjectPos][3] + 0.60);
        }
        case BATTLEPASS_TYPE_VEHICLE:
        {
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][idx], BattlePassReward[i][bprCount][0]);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][idx], -25.0000, 0.0000, 45.0000, 1.2500);
        }
    }
    return 1;
}

GetPlayerBattlePassRewardInfo(idx)
{
    new str[64];
    switch(BattlePassReward[idx][bprType])
    {
        case BATTLEPASS_TYPE_MONEY: f(str, "%d$", BattlePassReward[idx][bprCount][0]);
        case BATTLEPASS_TYPE_DONATE: f(str, "%d Flin Money", BattlePassReward[idx][bprCount][0]);
        case BATTLEPASS_TYPE_VIP: f(str, "VIP: %s, Дней: %d", TypeVIPName[BattlePassReward[idx][bprCount][0]], BattlePassReward[idx][bprCount][1]);
        case BATTLEPASS_TYPE_SKIN, BATTLEPASS_TYPE_ACC, BATTLEPASS_TYPE_INVENTORY: f(str, "%s", ItemsInfo[BattlePassReward[idx][bprCount][0]][iName]);
        case BATTLEPASS_TYPE_VEHICLE: f(str, "%s", GetVehicleName(INVALID_VEHICLE_ID, BattlePassReward[idx][bprCount][0]));
    }
    return str;
}

GetPlayerBattlePassLevel(playerid)
{
    new str[64], temp_level = p_info[playerid][battle_lvl];
    if(temp_level == MAX_BATTLEPASS_REWARD) str = "{"#cGREEN"}Максимальный уровень"W"";
    else f(str, "{"#cRED"}Уровней доступно: %d"W"", MAX_BATTLEPASS_REWARD - temp_level);
    return str;
}

GetBattlePassCoinsName(type, idx)
{
    new str[256];
    switch(type)
    {
        case TYPE_CHANGE_ACCESSORIES, TYPE_CHANGE_ROULETTE:
        {
            format(str, sizeof(str), "%s: %s", ChangeBattlePassCoinsTypeName[type], ItemsInfo[idx][iName]);
        }
        case TYPE_CHANGE_SKIN:
        {
            format(str, sizeof(str), "%s: %d", ChangeBattlePassCoinsTypeName[type], idx);
        }
        case TYPE_CHANGE_COSTUME:
        {
            format(str, sizeof(str), "%s: %s", ChangeBattlePassCoinsTypeName[type], CostumeName[idx]);
        }
    }
    return str;
}

GivePlayerBattlePassReward(playerid, idx, i)
{
    if(BattlePassTime == 0) return 1;
    if(p_info[playerid][battle_reward][idx] == 1) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]:"W" Вы уже забрали эту награду.");
    if(BattlePassReward[idx][bprStatus] == true && p_info[playerid][battle_info][0] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]:"W" Данная награда доступна только для владельцев Battle Pass Premium.");
    if(p_info[playerid][battle_lvl] < idx + 1) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]:"W" Данная награда доступна на %d уровне Battle Pass.", idx + 1);

    new battle_reward_type[7] = {TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_VIP, TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_INVENTORY}, type = BattlePassReward[idx][bprType];

    if(type == TYPE_GIVE_ITEM_INVENTORY) SetPlayerItem(playerid, 10, p_info[playerid][ID], battle_reward_type[BattlePassReward[idx][bprType]], BattlePassReward[idx][bprCount][1], BattlePassReward[idx][bprCount][0]);
    else SetPlayerItem(playerid, 10, p_info[playerid][ID], battle_reward_type[BattlePassReward[idx][bprType]], BattlePassReward[idx][bprCount][0], BattlePassReward[idx][bprCount][1]);

    p_info[playerid][battle_reward][idx] = 1;

    PlayerTextDrawSetString(playerid, PTD_BattlePassRewardText[playerid][i], GetPlayerBattlePassRewardButton(playerid, idx));

    SavePlayerBattlePass(playerid, BATTLEPASS_TYPE_REWARD, idx);
    return 1;
}

ShowPlayerBattlePass(playerid, idx)
{
    if(BattlePassTime == 0) return 1;
    new count;
    switch(idx)
    {
        case BATTLEPASS_TYPE_SHOW_REWARD:
        {
            p_temp[playerid][battle_items_list_reward][p_temp[playerid][battle_list][0]] = p_temp[playerid][battle_last_idx][0];
            for(new i = p_temp[playerid][battle_last_idx][0]; i < MAX_BATTLEPASS_REWARD; i++)
            {
                PlayerTextDrawShow(playerid, PTD_BattlePassRewardMain[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_BattlePassRewardButton[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_BattlePassRewardText[playerid][count]);
                PlayerTextDrawSetString(playerid, PTD_BattlePassRewardText[playerid][count], GetPlayerBattlePassRewardButton(playerid, i));
                GetPlayerBattlePassRewardModel(playerid, count, i);
                PlayerTextDrawShow(playerid, PTD_BattlePassRewardModel[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_BattlePassRewardInfo[playerid][count]);
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "%d уровень~n~~g~%s", i + 1, GetPlayerBattlePassRewardInfo(i));
                PlayerTextDrawSetString(playerid, PTD_BattlePassRewardInfo[playerid][count], STRING_GLOBAL);
                p_temp[playerid][p_listitem][count] = i;
                p_temp[playerid][battle_last_idx][0] = i + 1;
                count++;
                if(count == 3) break;
            }
        }
        case BATTLEPASS_TYPE_SHOW_TASK:
        {
            p_temp[playerid][battle_items_list_task][p_temp[playerid][battle_list][1]] = p_temp[playerid][battle_last_idx][1];
            new temp_task_active, temp_task, temp_task_reward;
            for(new i = p_temp[playerid][battle_last_idx][1]; i < MAX_PLAYER_BATTLEPASS_TASK; i++)
            {
                PlayerTextDrawShow(playerid, PTD_BattlePassTaskMain[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_BattlePassTaskName[playerid][count]);
                PlayerTextDrawShow(playerid, PTD_BattlePassTaskInfo[playerid][count]);
                temp_task_active = p_info[playerid][battle_task_active][i], temp_task = p_info[playerid][battle_task][temp_task_active];
                temp_task_reward = GetPlayerBattlePassReward(playerid, BattlePassTask[temp_task_active][bpReward][0]);
                if(p_info[playerid][battle_info][1] == 1) temp_task_reward = temp_task_reward * 2;
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "~b~%s~w~~n~~n~Прогресс: ~y~%d/%d~w~~n~~n~Награда: ~g~%d EXP,~n~%d$, %d COIN", BattlePassTask[temp_task_active][bpName], temp_task, GetPlayerBattlePassTask(playerid, temp_task_active), temp_task_reward, BattlePassTask[temp_task_active][bpReward][1], GetPlayerBattlePassReward(playerid, BattlePassTask[temp_task_active][bpReward][2]));
                PlayerTextDrawSetString(playerid, PTD_BattlePassTaskName[playerid][count], STRING_GLOBAL);
                PlayerTextDrawSetString(playerid, PTD_BattlePassTaskInfo[playerid][count], BattlePassTask[temp_task_active][bpText]);
                p_temp[playerid][battle_last_idx][1] = i + 1;
                count++;
                if(count == 3) break;
            }
        }
    }
    return 1;
}

UpdatePlayerBattlePass(playerid, idx)
{
    if(BattlePassTime == 0) return 1;
    if(p_temp[playerid][TextDrawBattlePass] == false) return 1;
    switch(idx)
    {
        case BATTLEPASS_TYPE_UPDATE_STATS:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "~g~%d УРОВЕНЬ~w~~n~ОПЫТ: ~b~%d/%d~w~~n~~n~ДО ПОЛУЧЕНИЯ~n~ОПЫТА: ~y~%s", p_info[playerid][battle_lvl], p_info[playerid][battle_info][2], GetPlayerBattlePassProgress(playerid), ConvertTime(MAX_BATTLEPASS_EXP_TIME - p_info[playerid][battle_info][3], 1));
            PlayerTextDrawSetString(playerid, PTD_BattlePassInfo[playerid][2], STRING_GLOBAL);
        }
        case BATTLEPASS_TYPE_UPDATE_LIST:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%d/%d", p_temp[playerid][battle_list][0] + 1, MAX_BATTLEPASS_LIST_REWARD);
            PlayerTextDrawSetString(playerid, PTD_BattlePassInfo[playerid][3], STRING_GLOBAL);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%d/%d", p_temp[playerid][battle_list][1] + 1, MAX_BATTLEPASS_LIST_TASK);
            PlayerTextDrawSetString(playerid, PTD_BattlePassInfo[playerid][4], STRING_GLOBAL);
        }
    }
    return 1;
}

HidePlayerBattlePass(playerid, idx)
{
    if(BattlePassTime == 0) return 1;
    if(p_temp[playerid][TextDrawBattlePass] == false) return 1;
    switch(idx)
    {
        case BATTLEPASS_TYPE_HIDE_REWARD:
        {
            for(new i = 0; i < 100; i++)
            {
                p_temp[playerid][p_listitem][i] = -1;
                if(i < 3)
                {
                    PlayerTextDrawHide(playerid, PTD_BattlePassRewardMain[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_BattlePassRewardButton[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_BattlePassRewardText[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_BattlePassRewardModel[playerid][i]);
                    PlayerTextDrawHide(playerid, PTD_BattlePassRewardInfo[playerid][i]);
                }
            }
        }
        case BATTLEPASS_TYPE_HIDE_TASK:
        {
            for(new i = 0; i < 3; i++)
            {
                PlayerTextDrawHide(playerid, PTD_BattlePassTaskMain[playerid][i]);
                PlayerTextDrawHide(playerid, PTD_BattlePassTaskName[playerid][i]);
                PlayerTextDrawHide(playerid, PTD_BattlePassTaskInfo[playerid][i]);
            }
        }
    }
    return 1;
}

SavePlayerBattlePass(playerid, type, first_parameter = -1)
{
    if(BattlePassTime == 0) return 1;
    switch(type)
    {
        case BATTLEPASS_TYPE_INFO:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `battle_lvl` = %d, `battle_lvl_task` = %d, `battle_info` = '%d|%d|%d|%d|%d' WHERE `id` = %d",
            p_info[playerid][battle_lvl], p_info[playerid][battle_lvl_task], p_info[playerid][battle_info][0], p_info[playerid][battle_info][1], p_info[playerid][battle_info][2],
            p_info[playerid][battle_info][3], p_info[playerid][battle_info][4], p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        case BATTLEPASS_TYPE_TASK:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `battle_task_active` = '%d|%d|%d|%d|%d', `battle_task` = '%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d' WHERE `id` = %d",
            p_info[playerid][battle_task_active][0], p_info[playerid][battle_task_active][1], p_info[playerid][battle_task_active][2], p_info[playerid][battle_task_active][3], p_info[playerid][battle_task_active][4],
            p_info[playerid][battle_task][0], p_info[playerid][battle_task][1], p_info[playerid][battle_task][2], p_info[playerid][battle_task][3], p_info[playerid][battle_task][4],
            p_info[playerid][battle_task][5], p_info[playerid][battle_task][6], p_info[playerid][battle_task][7], p_info[playerid][battle_task][8], p_info[playerid][battle_task][9],
            p_info[playerid][battle_task][10], p_info[playerid][battle_task][11], p_info[playerid][battle_task][12], p_info[playerid][battle_task][13], p_info[playerid][battle_task][14],
            p_info[playerid][battle_task][15], p_info[playerid][battle_task][16], p_info[playerid][battle_task][17], p_info[playerid][battle_task][18], p_info[playerid][battle_task][19],
            p_info[playerid][battle_task][20], p_info[playerid][battle_task][21], p_info[playerid][battle_task][22], p_info[playerid][battle_task][23], p_info[playerid][battle_task][24], p_info[playerid][ID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        case BATTLEPASS_TYPE_REWARD:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `battlepass_reward` SET `status` = %d WHERE `user_id` = %d AND `reward_id` = %d",
                p_info[playerid][battle_reward][first_parameter], p_info[playerid][ID], first_parameter);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

forward OnPlayerLoadBattlePass(playerid);
public OnPlayerLoadBattlePass(playerid)
{
    if(BattlePassTime == 0) return 1;
    new rows;
    cache_get_row_count(rows);
    if(rows)
    {
        for(new i; i < MAX_BATTLEPASS_REWARD; i++)
        {
            cache_get_value_name_int(i, "status", p_info[playerid][battle_reward][i]);
        }
    }
    if(rows < MAX_BATTLEPASS_REWARD)
    {
        new scdplayerid = p_info[playerid][ID], neededRewardCount = MAX_BATTLEPASS_REWARD - rows;
        for(new i = 0; i < neededRewardCount; i++)
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `battlepass_reward` (`user_id`, `reward_id`, `status`) VALUES (%d, %d, 0)",
            scdplayerid, rows);
            mysql_tquery(con_bd, STRING_GLOBAL);
            p_info[playerid][battle_reward][i] = 0;
            rows++;
        }
    }
    return 1;
}

BP_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if(BattlePassTime == 0) return 1;
    if(p_temp[playerid][TextDrawBattlePass] == false) return 1;

    if(playertextid == PTD_BattlePassMain[playerid][4]) // Магазин;
    {
        ShowBattlePass(playerid, BATTLEPASS_TYPE_SHOP);
        return 1;
    }
    else if(playertextid == PTD_BattlePassMain[playerid][5]) // Все награды;
    {
        ShowBattlePass(playerid, BATTLEPASS_TYPE_ALL_REWARD);
        return 1;
    }
    else if(playertextid == PTD_BattlePassMain[playerid][6]) // Обмен Coin;
    {
        ShowBattlePass(playerid, BATTLEPASS_TYPE_CHANGE);
        return 1;
    }
    else if(playertextid == PTD_BattlePassMain[playerid][7]) // Рейтинг;
    {
        ShowBattlePass(playerid, BATTLEPASS_TYPE_TOP);
        return 1;
    }
    else if(playertextid == PTD_BattlePassMain[playerid][8]) // Статистика;
    {
        ShowBattlePass(playerid, BATTLEPASS_TYPE_STATS);
        return 1;
    }
    else if(playertextid == PTD_BattlePassMain[playerid][9]) // Информация;
    {
        ShowBattlePass(playerid, BATTLEPASS_TYPE_HELP);
        return 1;
    }
    else if(playertextid == PTD_BattlePassMain[playerid][16]) // Закрыть;
    {
        HideTextDrawForPlayer(playerid, TD_ID_BATTLEPASS);
        return 1;
    }
    else if(playertextid == PTD_BattlePassButton[playerid][0]) // Влево задания;
    {
        if(p_temp[playerid][battle_list][1] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]: "W"Вы находитесь на первой странице.");
        p_temp[playerid][battle_list][1]--;
        p_temp[playerid][battle_last_idx][1] = p_temp[playerid][battle_items_list_task][p_temp[playerid][battle_list][1]];

        HidePlayerBattlePass(playerid, BATTLEPASS_TYPE_HIDE_TASK);
        ShowPlayerBattlePass(playerid, BATTLEPASS_TYPE_SHOW_TASK);
        UpdatePlayerBattlePass(playerid, BATTLEPASS_TYPE_UPDATE_LIST);
        return 1;
    }
    else if(playertextid == PTD_BattlePassButton[playerid][1]) // Вправо задания;
    {
        if(p_temp[playerid][battle_list][1] == MAX_BATTLEPASS_LIST_TASK - 1) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]: "W"Вы находитесь на последней странице.");
        p_temp[playerid][battle_list][1]++;
        HidePlayerBattlePass(playerid, BATTLEPASS_TYPE_HIDE_TASK);
        ShowPlayerBattlePass(playerid, BATTLEPASS_TYPE_SHOW_TASK);
        UpdatePlayerBattlePass(playerid, BATTLEPASS_TYPE_UPDATE_LIST);
        return 1;
    }
    else if(playertextid == PTD_BattlePassButton[playerid][4]) // Влево награды;
    {
        if(p_temp[playerid][battle_list][0] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]: "W"Вы находитесь на первой странице.");
        p_temp[playerid][battle_list][0]--;
        p_temp[playerid][battle_last_idx][0] = p_temp[playerid][battle_items_list_reward][p_temp[playerid][battle_list][0]];

        HidePlayerBattlePass(playerid, BATTLEPASS_TYPE_HIDE_REWARD);
        ShowPlayerBattlePass(playerid, BATTLEPASS_TYPE_SHOW_REWARD);
        UpdatePlayerBattlePass(playerid, BATTLEPASS_TYPE_UPDATE_LIST);
        return 1;
    }
    else if(playertextid == PTD_BattlePassButton[playerid][5]) // Вправо награды;
    {
        if(p_temp[playerid][battle_list][0] == MAX_BATTLEPASS_LIST_REWARD - 1) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]: "W"Вы находитесь на последней странице.");
        p_temp[playerid][battle_list][0]++;
        HidePlayerBattlePass(playerid, BATTLEPASS_TYPE_HIDE_REWARD);
        ShowPlayerBattlePass(playerid, BATTLEPASS_TYPE_SHOW_REWARD);
        UpdatePlayerBattlePass(playerid, BATTLEPASS_TYPE_UPDATE_LIST);
        return 1;
    }
    for(new i = 0; i < 3; i++)
    {
        if(playertextid == PTD_BattlePassRewardButton[playerid][i])
        {
            new idx = p_temp[playerid][p_listitem][i];
            if(idx == -1) return 1;
            if(p_info[playerid][battle_reward][idx] == 1) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]:"W" Вы уже забрали эту награду.");
            if(BattlePassReward[idx][bprStatus] == true && p_info[playerid][battle_info][0] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]:"W" Данная награда доступна только для владельцев Battle Pass Premium.");
            if(p_info[playerid][battle_lvl] < idx + 1) return SendMes(playerid, COLOR_DARKORANGE, "[BATTLE PASS]:"W" Данная награда доступна на %d уровне Battle Pass.", idx + 1);
            GivePlayerBattlePassReward(playerid, idx, i);
        }
    }
    return 1;
}

CMD:bp(playerid, params[])
{
    if(BattlePassTime == 0) return 1;
    ShowTextDrawForPlayer(playerid, TD_ID_BATTLEPASS);
    return 1;
}