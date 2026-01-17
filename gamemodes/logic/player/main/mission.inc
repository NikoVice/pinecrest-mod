CMD:mission(playerid, params[])
{
    ShowPlayerDialog(playerid, D_MISSION, DIALOG_STYLE_LIST, ""I"Задания, достижения и награды", "\
    "I"[1]"W" Начальные задания\n\
    "I"[2]"W" Ежедневные задания\n\
    "I"[3]"W" Фракционные задания\n\
    "I"[4]"W" Достижения\n\
    "I"[5]"W" Информация о начальных заданиях\n\
    "I"[6]"W" Информация о ежедневных и фракционных заданиях\n\
    "I"[7]"W" Информация о достижениях\n\
    "I"[8]"W" Ежедневные награды\n\
    "I"[9]"W" Бесплатная рулетка", "Далее", "Отмена");
    return 1;
}

alias:mission("quest", "dquest", "event", "bonus");

ShowPlayerMission(playerid, type, idx)
{
    new count;
    switch(type)
    {
        case MISSION_TYPE_START_TASK:
        {
            STRING_MIN[0] = EOS, STRING_GLOBAL = "[#] Задание\tНаграда\tПрогресс\n";
            for(new i = idx; i < MAX_MISSION; i++)
            {
                if(Mission[i][mType] != type) continue;
                if(Mission[i][mFractionID] != 0 && Mission[i][mFractionID] != GetPlayerFractionType(playerid)) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" {"#cGRAY"}[%s]"W" %s\t%s\t%s\n", count + 1, Mission[i][mCategory], Mission[i][mText], GetPlayerMissionReward(playerid, i, true), GetPlayerMissionProgress(playerid, type, i));
                strcat(STRING_GLOBAL, STRING_MIN);
                count++;
                MissionDialogListitem[playerid][1] = count;
                if(count == 16) break;
            }
            if(idx == 0) strcat(STRING_GLOBAL, ">> Следующая страница"), MissionDialogListitem[playerid][0] = 0;
            else strcat(STRING_GLOBAL, "<< Предыдущая страница"), MissionDialogListitem[playerid][0] = 1;
            ShowPlayerDialog(playerid, D_MISSION_START_TASK, DIALOG_STYLE_TABLIST_HEADERS, ""I"Начальные задания", STRING_GLOBAL, "Далее", "Отмена");
            SendInfo(playerid, "Для более подробной информации нажмите на необходимое задание.");
            SendInfo(playerid, "Узнать местоположение начала задания можно нажав на него.");
        }
        case MISSION_TYPE_DAILY_TASK:
        {
            STRING_MIN[0] = EOS, STRING_GLOBAL = "[#] Задание\tНаграда\tПрогресс\n";
            for(new i = idx; i < MAX_MISSION; i++)
            {
                if(Mission[i][mType] != type) continue;
                if(Mission[i][mFractionID] != 0) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" {"#cGRAY"}[%s]"W" %s\t%s\t%s\n", count + 1, Mission[i][mCategory], Mission[i][mText], GetPlayerMissionReward(playerid, i, true), GetPlayerMissionProgress(playerid, type, i));
                strcat(STRING_GLOBAL, STRING_MIN);
                count++;
                MissionDialogListitem[playerid][1] = count;
                if(count == 16) break;
            }
            if(idx == 32) strcat(STRING_GLOBAL, ">> Следующая страница"), MissionDialogListitem[playerid][0] = 0;
            else strcat(STRING_GLOBAL, "<< Предыдущая страница"), MissionDialogListitem[playerid][0] = 1;
            ShowPlayerDialog(playerid, D_MISSION_DAILY_TASK, DIALOG_STYLE_TABLIST_HEADERS, ""I"Ежедневные задания", STRING_GLOBAL, "Далее", "Отмена");
            SendInfo(playerid, "Для более подробной информации нажмите на необходимое задание.");
            SendInfo(playerid, "Узнать местоположение начала задания можно нажав на него.");
        }
        case MISSION_TYPE_ACHIEVEMENT:
        {
            STRING_MIN[0] = EOS, STRING_GLOBAL = "[#] Достижение\tНаграда\tПрогресс\n";
            for(new i = idx; i < MAX_MISSION; i++)
            {
                if(Mission[i][mType] != type) continue;
                if(Mission[i][mFractionID] != 0 && Mission[i][mFractionID] != GetPlayerFractionType(playerid)) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" {"#cGRAY"}[%s]"W" %s\t%s\t%s\n", count + 1, Mission[i][mCategory], Mission[i][mText], GetPlayerMissionReward(playerid, i, true), GetPlayerMissionProgress(playerid, type, i));
                strcat(STRING_GLOBAL, STRING_MIN);
                count++;
                MissionDialogListitem[playerid][1] = count;
                if(count == 16) break;
            }
            if(idx == 100) strcat(STRING_GLOBAL, ">> Следующая страница"), MissionDialogListitem[playerid][0] = 0;
            else strcat(STRING_GLOBAL, "<< Предыдущая страница"), MissionDialogListitem[playerid][0] = 1;
            ShowPlayerDialog(playerid, D_MISSION_ACHIEVEMENT, DIALOG_STYLE_TABLIST_HEADERS, ""I"Достижения", STRING_GLOBAL, "Далее", "Отмена");
            SendInfo(playerid, "Для более подробной информации нажмите на необходимое достижение.");
            SendInfo(playerid, "Узнать местоположение начала достижения можно нажав на него.");
        }
        case MISSION_INFO_START_TASK:
        {
            new listitem = (MissionDialogListitem[playerid][0] == 0 ? 0 : 17) + idx;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Категория: "I"%s"W"\n\
            Задача: "I"%s"W"\n\
            Награда: "I"%s"W"\n\
            Прогресс: "I"%s", Mission[listitem][mCategory], Mission[listitem][mText], GetPlayerMissionReward(playerid, listitem), GetPlayerMissionProgress(playerid, MISSION_TYPE_START_TASK, listitem));
            ShowPlayerDialog(playerid, D_MISSION_START_TASK_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о начальном задании", STRING_GLOBAL, "Далее", "Отмена");
            GetPlayerMissionCoords(playerid, MISSION_TYPE_START_TASK, listitem);
        }
        case MISSION_INFO_DAILY_TASK:
        {
            new listitem = (MissionDialogListitem[playerid][0] == 0 ? 33 : 48) + idx;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Категория: "I"%s"W"\n\
            Задача: "I"%s"W"\n\
            Награда: "I"%s"W"\n\
            Прогресс: "I"%s", Mission[listitem][mCategory], Mission[listitem][mText], GetPlayerMissionReward(playerid, listitem), GetPlayerMissionProgress(playerid, MISSION_TYPE_DAILY_TASK, listitem));
            ShowPlayerDialog(playerid, D_MISSION_DAILY_TASK_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о ежедневном задании", STRING_GLOBAL, "Далее", "Отмена");
            GetPlayerMissionCoords(playerid, MISSION_TYPE_DAILY_TASK, listitem);
        }
        case MISSION_INFO_ACHIEVEMENT:
        {
            new listitem = (MissionDialogListitem[playerid][0] == 0 ? 102 : 117) + idx;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Категория: "I"%s"W"\n\
            Задача: "I"%s"W"\n\
            Следующий статус: "I"%s"W"\n\
            Награда: "I"%s"W"\n\
            Прогресс: "I"%s", Mission[listitem][mCategory], Mission[listitem][mText], GetPlayerMissionRank(playerid, listitem), GetPlayerMissionReward(playerid, listitem), GetPlayerMissionProgress(playerid, MISSION_TYPE_ACHIEVEMENT, listitem));
            ShowPlayerDialog(playerid, D_MISSION_ACHIEVEMENT_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о достижении", STRING_GLOBAL, "Далее", "Отмена");
            GetPlayerMissionCoords(playerid, MISSION_TYPE_ACHIEVEMENT, listitem);
        }
        case MISSION_TYPE_DAILY_FRACTION:
        {
            if(p_info[playerid][member] == 0) return SendError(playerid, "Вы не состоите во фракции.");
            STRING_MIN[0] = EOS, STRING_GLOBAL = "[#] Задание\tНаграда\tПрогресс\n";
            for(new i = idx; i < MAX_MISSION; i++)
            {
                if(Mission[i][mType] != MISSION_TYPE_DAILY_TASK) continue;
                if(Mission[i][mFractionID] < 1 || Mission[i][mFractionID] != GetPlayerFractionType(playerid)) continue;
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%s\n", count + 1, Mission[i][mText], GetPlayerMissionReward(playerid, i, true), GetPlayerMissionProgress(playerid, MISSION_TYPE_DAILY_TASK, i));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_MISSION_DAILY_FRACTION, DIALOG_STYLE_TABLIST_HEADERS, ""I"Фракционные задания", STRING_GLOBAL, "Далее", "Отмена");
            SendInfo(playerid, "Для более подробной информации нажмите на необходимое задание.");
            SendInfo(playerid, "Узнать местоположение начала задания можно нажав на него.");
        }
        case MISSION_INFO_DAILY_FRACTION:
        {
            new listitem = idx;
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
            Категория: "I"%s"W"\n\
            Задача: "I"%s"W"\n\
            Награда: "I"%s"W"\n\
            Прогресс: "I"%s", Mission[listitem][mCategory], Mission[listitem][mText], GetPlayerMissionReward(playerid, listitem), GetPlayerMissionProgress(playerid, MISSION_TYPE_DAILY_TASK, listitem));
            ShowPlayerDialog(playerid, D_MISSION_DAILY_FRACTION_INFO, DIALOG_STYLE_MSGBOX, ""I"Информация о фракционном задании", STRING_GLOBAL, "Далее", "Отмена");
            GetPlayerMissionCoords(playerid, MISSION_TYPE_DAILY_FRACTION, listitem);
        }
    }
    return 1;
}

GetPlayerMissionRank(playerid, idx)
{
    new str[128];
    if(p_info[playerid][achievement][idx - 102] == MAX_MISSION_ACHIEVEMENT_RANK) str = "{"#cGREEN"}Максимальный{"#cWHITE"}";
    else format(str, sizeof(str), "{"#cMAIN"}%s %d уровня{"#cWHITE"}", Mission[idx][mRank], p_info[playerid][achievement][idx - 102] + 1);
    return str;
}

GetPlayerMissionReward(playerid, idx, bool:status = false)
{
    new str[128] = "{"#cGREEN"}", mission_reward_name[4][12] = {"EXP", "$", "Flin Money", "Mission EXP"}, count, price[2];
    for(new i = 0; i < 4; i++)
    {
        if(Mission[idx][mReward][i] == 0) continue;
        if(status == true && i == 3) continue;
        if(i == 1)
        {
            price[1] = Mission[idx][mReward][i];
            if(p_info[playerid][p_vip])
            {
                if(p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) price[0] = price[1] * 3;
                else
                {
                    switch(p_info[playerid][p_vip])
                    {
                        case 1: price[0] = price[1] + ((price[1] / 100) * 25);
                        case 2: price[0] = price[1] + ((price[1] / 100) * 50);
                        case 3: price[0] = price[1] + price[1];
                    }
                }
            } else price[0] = Mission[idx][mReward][i];
        } else price[0] = Mission[idx][mReward][i];
        if(count == 0) format(str, sizeof(str), "%s %d %s", str, price[0], mission_reward_name[i]);
        else format(str, sizeof(str), "%s + %d %s", str, price[0], mission_reward_name[i]);
        count++;
    }
    strcat(str, ""W"");
    return str;
}

GetPlayerMissionProgress(playerid, type, idx)
{
    new str[64];
    switch(type)
    {
        case MISSION_TYPE_START_TASK:
        {
            new Float:percent = (float(p_info[playerid][quest][idx]) / float(Mission[idx][mProgress])) * 100;
            if(p_info[playerid][quest][idx] < Mission[idx][mProgress]) format(str, sizeof(str), "{"#cLIGHTRED"}[%d / %d] (%.1f%%){"#cWHITE"}", p_info[playerid][quest][idx], Mission[idx][mProgress], percent);
            else str = "{"#cGREEN"}Выполнено{"#cWHITE"}";
        }
        case MISSION_TYPE_DAILY_TASK:
        {
            new Float:percent = (float(p_info[playerid][mission][idx - 33]) / float(Mission[idx][mProgress])) * 100;
            if(p_info[playerid][mission][idx - 33] < Mission[idx][mProgress]) format(str, sizeof(str), "{"#cLIGHTRED"}[%d / %d] (%.1f%%){"#cWHITE"}", p_info[playerid][mission][idx - 33], Mission[idx][mProgress], percent);
            else str = "{"#cGREEN"}Выполнено{"#cWHITE"}";
        }
        case MISSION_TYPE_ACHIEVEMENT:
        {
            new Float:percent = (p_info[playerid][achievement_progress][idx - 102] / Mission[idx][mProgress]) * 100;
            if(p_info[playerid][achievement_progress][idx - 102] < Mission[idx][mProgress] && p_info[playerid][achievement][idx - 102] != MAX_MISSION_ACHIEVEMENT_RANK) format(str, sizeof(str), "{"#cLIGHTRED"}[%d / %d] (%.1f%%){"#cWHITE"}", p_info[playerid][achievement_progress][idx - 102], Mission[idx][mProgress], percent);
            else str = "{"#cGREEN"}Выполнено{"#cWHITE"}";
        }
    }
    return str;
}

ShowPlayerMissionInfo(playerid, type)
{
    STRING_GLOBAL[0] = EOS;
    switch(type)
    {
        case MISSION_TYPE_START_TASK:
        {
            ShowPlayerDialog(playerid, D_MISSION_BACK, DIALOG_STYLE_MSGBOX, ""I"Начальные задания", "{"#cWHITE"}\
            Каждый игрок после регистрации может выполнять начальные задания и получать за них следующие награды:\n\n\
            {"#cMAIN"}[1]{"#cWHITE"} Игровые деньги;\n\
            {"#cMAIN"}[2]{"#cWHITE"} Очки опыта (EXP);\n\
            {"#cMAIN"}[3]{"#cWHITE"} Flin Money.\n\n\
            Задания можно выполнять в любое время, ведь их прогресс сохраняется. Все задания активны и Ваша задача\n\
            заключается в их выполнении.", "Далее", "Отмена");
        }
        case MISSION_TYPE_DAILY_TASK:
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "{"#cWHITE"}\
            Каждый игрок ежедневно может выполнять различные задания и получать за них следующие награды:\n\n\
            {"#cMAIN"}[1]{"#cWHITE"} Игровые деньги;\n\
            {"#cMAIN"}[2]{"#cWHITE"} Очки опыта (EXP);\n\
            {"#cMAIN"}[3]{"#cWHITE"} Flin Money;\n\
            {"#cMAIN"}[4]{"#cWHITE"} Mission EXP.\n\n\
            Помимо обычных заданий, которые доступны всем игрокам, игрок может выполнять задания той фракции,\n\
            в которой он состоит.\n\n\
            Задания необходимо выполнять до {"#cMAIN"}05:00,{"#cWHITE"} после чего их прогресс обновляется и их можно выполнять заново.\n\
            Все задания активны и Ваша задача заключается в их выполнении.\n\n\
            За каждое задание выдается {"#cMAIN"}Mission EXP.{"#cWHITE"} Собрав {"#cMAIN"}%d Mission EXP{"#cWHITE"} в день, Вам будет выдана награда: {"#cMAIN"}%d Flin Money.{"#cWHITE"}\n\n\
            Если Вы соберете {"#cMAIN"}%d{"#cWHITE"} ежедневных наград подряд, получая по {"#cMAIN"}%d Mission EXP,{"#cWHITE"} Вас ждёт следующая награда: {"#cMAIN"}%d Flin Money.{"#cWHITE"}\n\n\
            {"#cLIGHTRED"}Обратите внимание! Если в один из дней Вы не получите ежедневный бонус за сбор %d Mission EXP, то недельный\n\
            прогресс будет обнулен.{"#cWHITE"}\n\n\
            На данный момент у Вас: {"#cMAIN"}%d из %d Mission EXP{"#cWHITE"}\n\
            Вы получили суточных призов подряд: {"#cMAIN"}%d из %d раз(-а)",
            MAX_MISSION_EXP, MISSION_PRIZE_FOR_MIN_DAYS_FLIN_MONEY, MAX_MISSION_DAYS, MAX_MISSION_EXP,
            MISSION_PRIZE_FOR_MAX_DAYS_FLIN_MONEY, MAX_MISSION_EXP, p_info[playerid][mission_exp], MAX_MISSION_EXP, p_info[playerid][mission_days], MAX_MISSION_DAYS);
            ShowPlayerDialog(playerid, D_MISSION_BACK, DIALOG_STYLE_MSGBOX, ""I"Ежедневные и фракционные задания", STRING_GLOBAL, "Далее", "Отмена");
        }
        case MISSION_TYPE_ACHIEVEMENT:
        {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "{"#cWHITE"}\
            Система достижений - аналог системы начальных и ежедневных заданий.\n\n\
            В отличии от системы начальных и ежедневных заданий, достижения могут быть получены {"#cMAIN"}в любое время{"#cWHITE"} за всю\n\
            продолжительность игры на сервере. Получать достижения значительно сложнее, но за это Вы будете зарабатывать более\n\
            {"#cMAIN"}значимые награды.{"#cWHITE"}\n\n\
            Достижения имеют {"#cMAIN"}%d уровней статуса,{"#cWHITE"} после выполнения каждого уровня, Вы сможете повторно выполнять их. За\n\
            выполнение каждого уровня, помимо обычных наград, Вам будет выдаваться {"#cMAIN"}Bronze рулетка,{"#cWHITE"} но есть вероятность\n\
            выдачи {"#cMAIN"}Silver{"#cWHITE"} и {"#cMAIN"}Gold рулетки.",
            MAX_MISSION_ACHIEVEMENT_RANK);
            ShowPlayerDialog(playerid, D_MISSION_BACK, DIALOG_STYLE_MSGBOX, ""I"Достижения", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

CheckPlayerMission(playerid, idx, count = 1)
{
    switch(Mission[idx][mType])
    {
        case MISSION_TYPE_START_TASK:
        {
            if(p_info[playerid][quest][idx] == Mission[idx][mProgress]) return 1;
            p_info[playerid][quest][idx] += count;
            if(p_info[playerid][quest][idx] >= Mission[idx][mProgress])
            {
                p_info[playerid][quest][idx] = Mission[idx][mProgress];
                SendAccess(playerid, "Вы выполнили задание: %s.", Mission[idx][mText]);
                SendInfo(playerid, "Награда за выполнение задания: %s.", GetPlayerMissionReward(playerid, idx));
                GivePlayerMissionReward(playerid, idx);
                if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(playerid, -1);
            }
        }
        case MISSION_TYPE_DAILY_TASK:
        {
            if(p_info[playerid][mission][idx - 33] == Mission[idx][mProgress]) return 1;
            p_info[playerid][mission][idx - 33] += count;
            if(p_info[playerid][mission][idx - 33] >= Mission[idx][mProgress])
            {
                p_info[playerid][mission][idx - 33] = Mission[idx][mProgress];
                SendAccess(playerid, "Вы выполнили задание: %s.", Mission[idx][mText]);
                SendInfo(playerid, "Награда за выполнение задания: %s.", GetPlayerMissionReward(playerid, idx));
                GivePlayerMissionReward(playerid, idx);
                if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(playerid, -1);
                CheckPlayerMission(playerid, DAILY_DTASK);
                CheckPlayerMission(playerid, ACHIEVEMENT_DTASK);
            }
        }
        case MISSION_TYPE_ACHIEVEMENT:
        {
            if(p_info[playerid][achievement][idx - 102] == MAX_MISSION_ACHIEVEMENT_RANK) return 1;
            p_info[playerid][achievement_progress][idx - 102] += count;
            if(p_info[playerid][achievement_progress][idx - 102] >= Mission[idx][mProgress])
            {
                p_info[playerid][achievement][idx - 102] += 1;
                p_info[playerid][achievement_progress][idx - 102] = 0;
                SendAccess(playerid, "Вы выполнили достижение: %s.", Mission[idx][mText]);
                SendInfo(playerid, "Награда за выполнение достижения: %s.", GetPlayerMissionReward(playerid, idx));
                GivePlayerMissionReward(playerid, idx);
                if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(playerid, -1);

                new i = 642;
                switch(random(100))
                {
                    case 0 .. 95: i = 642;
                    case 96 .. 98: i = 643;
                    default: i = 644;
                }
                if(!GivePlayerInventory(playerid, i))
                    return 1;
                SendAccess(playerid, "Вам выдана %s рулетка.", RouletteNameType[i-15-TRANSFER_ITEMS]);

                Log(LOG_player, INFO, "%s[%d](%s %s) получил %s рулетку за выполнение достижения | #FreeRoulette",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", RouletteNameType[i-15-TRANSFER_ITEMS]);
            }
        }
    }
    SavePlayerMission(playerid, Mission[idx][mType]);
    return 1;
}

GivePlayerMissionReward(playerid, idx)
{
    new count, mission_type_name[3][32] = {"начальное задание", "ежедневное задание", "достижение"}, type = Mission[idx][mType];
    if(Mission[idx][mReward][0] != 0)
    {
        count = Mission[idx][mReward][0];
        p_info[playerid][exp] += count;
        PlayerLevelUpdateCheck(playerid);

        Log(LOG_player, INFO, "%s[%d](%s %s) выполнил %s %s награда %d EXP",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            mission_type_name[type], Mission[idx][mText], count);
    }
    if(Mission[idx][mReward][1] != 0)
    {
        count = Mission[idx][mReward][1];

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
        }

        OnServerInfoForMoney[19] += count;
        SetPlayerMoney(playerid, count, true, "выполнил %s <%s>", mission_type_name[type], Mission[idx][mText]);
    }
    if(Mission[idx][mReward][2] != 0)
    {
        count = Mission[idx][mReward][2];
        p_info[playerid][flinmoney] += count;
        MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

        Log(LOG_player, INFO, "%s[%d](%s %s) выполнил %s %s награда %d Flin Money",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            mission_type_name[type], Mission[idx][mText], count);
    }
    if(Mission[idx][mReward][3] != 0 && p_info[playerid][mission_exp] < MAX_MISSION_EXP)
    {
        count = Mission[idx][mReward][3];
        p_info[playerid][mission_exp] += count;

        Log(LOG_player, INFO, "%s[%d](%s %s) выполнил %s %s награда %d Mission EXP",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
            mission_type_name[type], Mission[idx][mText], count);

        if(p_info[playerid][mission_exp] >= MAX_MISSION_EXP)
        {
            p_info[playerid][mission_days] += 1;
            p_info[playerid][mission_exp] = 30;
            if(p_info[playerid][mission_days] >= MAX_MISSION_DAYS)
            {
                p_info[playerid][mission_days] = 0;

                p_info[playerid][flinmoney] += MISSION_PRIZE_FOR_MAX_DAYS_FLIN_MONEY;
                MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

                Log(LOG_player, INFO, "%s[%d](%s %s) собрал %d Mission EXP за %d дней награда %d Flin Money",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                    MAX_MISSION_EXP, MAX_MISSION_DAYS, MISSION_PRIZE_FOR_MAX_DAYS_FLIN_MONEY);

                SendAccess(playerid, "Вы собрали %d Mission EXP на протяжении %d дней.", MAX_MISSION_EXP, MAX_MISSION_DAYS);
                SendInfo(playerid, "Ваша награда: %d Flin Money.", MISSION_PRIZE_FOR_MAX_DAYS_FLIN_MONEY);
                SendInfo(playerid, "На протяжении %d дней собирайте по %d Mission EXP и получите %d Flin Money.", MAX_MISSION_DAYS, MAX_MISSION_EXP, MISSION_PRIZE_FOR_MAX_DAYS_FLIN_MONEY);
            }
            else
            {
                p_info[playerid][flinmoney] += MISSION_PRIZE_FOR_MIN_DAYS_FLIN_MONEY;
                MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

                Log(LOG_player, INFO, "%s[%d](%s %s) собрал %d Mission EXP за 1 день награда %d Flin Money",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                    MAX_MISSION_EXP, MISSION_PRIZE_FOR_MIN_DAYS_FLIN_MONEY);

                SendAccess(playerid, "Вы собрали %d Mission EXP за день.", MAX_MISSION_EXP);
                SendInfo(playerid, "Ваша награда: %d Flin Money.", MISSION_PRIZE_FOR_MIN_DAYS_FLIN_MONEY);
                SendInfo(playerid, "На протяжении %d дней собирайте по %d Mission EXP и получите %d Flin Money.", MAX_MISSION_DAYS, MAX_MISSION_EXP, MISSION_PRIZE_FOR_MAX_DAYS_FLIN_MONEY);
            }
        }
    }
    return 1;
}

GetPlayerMissionCoords(playerid, type, idx)
{
    if(IsGPSVisable(playerid) != -1) return 1;

    new mission_type_name[3][32] = {"начального задания", "ежедневного задания", "достижения"};
    if(Mission[idx][mCoords][0] == 0.0 && Mission[idx][mCoords][1] == 0.0 && Mission[idx][mCoords][2] == 0)
    {
        new Float:MissionCoords[8][4], MissionIDx = -1, MissionMaxIDx, bool:MissionCheckSuccess;
        new max_distance = 100000, here_distance = -1;
        switch(idx)
        {
            case 2: // Магазины одежды;
            {
                for(new i = 21; i < 24; i++)
                {
                    MissionCoords[i - 21][0] = b_info[i][b_enter][0];
                    MissionCoords[i - 21][1] = b_info[i][b_enter][1];
                    MissionCoords[i - 21][2] = b_info[i][b_enter][2];
                }

                MissionMaxIDx = 4, MissionCheckSuccess = true;
            }
            case 11: // Отели;
            {
                for(new i = 63; i < 68; i++)
                {
                    MissionCoords[i - 63][0] = b_info[i][b_enter][0];
                    MissionCoords[i - 63][1] = b_info[i][b_enter][1];
                    MissionCoords[i - 63][2] = b_info[i][b_enter][2];
                }

                MissionMaxIDx = 3, MissionCheckSuccess = true;
            }
            case 12: // Автосалоны;
            {
                MissionCoords[0][0] = 542.1884, MissionCoords[0][1] = -1289.3267, MissionCoords[0][2] = 17.2422;
                MissionCoords[1][0] = -1968.6368, MissionCoords[1][1] = 293.9742, MissionCoords[1][2] = 35.1719;
                MissionCoords[2][0] = -1639.8495, MissionCoords[2][1] = 1203.1735, MissionCoords[2][2] = 7.2325;
                MissionCoords[3][0] = 2200.8508, MissionCoords[3][1] = 1392.4738, MissionCoords[3][2] = 10.8203;

                MissionMaxIDx = 4, MissionCheckSuccess = true;
            }
            case 13: // СТО;
            {
                MissionCoords[0][0] = -2089.12, MissionCoords[0][1] = 84.2703, MissionCoords[0][2] = 35.3134;
                MissionCoords[1][0] = -1799.94, MissionCoords[1][1] = 1200.37, MissionCoords[1][2] = 25.1194;

                MissionMaxIDx = 2, MissionCheckSuccess = true;
            }
            case 14, 37, 101: // Водитель автобуса;
            {
                MissionCoords[0][0] = 1104.3624, MissionCoords[0][1] = -1740.9139, MissionCoords[0][2] = 13.4631;
                MissionCoords[1][0] = -1980.3877, MissionCoords[1][1] = 97.5302, MissionCoords[1][2] = 27.6875;
                MissionCoords[2][0] = 2778.9050, MissionCoords[2][1] = 1283.0614, MissionCoords[2][2] = 10.7500;
                MissionCoords[3][0] = 1665.4716, MissionCoords[3][1] = -1113.7278, MissionCoords[3][2] = 23.9063;

                MissionMaxIDx = 4, MissionCheckSuccess = true;
            }
            case 15, 38, 102: // Службы такси;
            {
                MissionCoords[0][0] = 1274.26, MissionCoords[0][1] = -1802.19, MissionCoords[0][2] = 13.3915;
                MissionCoords[1][0] = -2202.92, MissionCoords[1][1] = 298.249, MissionCoords[1][2] = 35.1172;
                MissionCoords[2][0] = 2822.39, MissionCoords[2][1] = 1519.42, MissionCoords[2][2] = 10.9081;

                MissionMaxIDx = 3, MissionCheckSuccess = true;
            }
            case 16, 39, 103: // Транспортные компании;
            {
                MissionCoords[0][0] = -478.446, MissionCoords[0][1] = -513.438, MissionCoords[0][2] = 25.5178;
                MissionCoords[1][0] = -229.097, MissionCoords[1][1] = -251.117, MissionCoords[1][2] = 1.42188;
                MissionCoords[2][0] = 58.7898, MissionCoords[2][1] = -263.999, MissionCoords[2][2] = 1.57812;

                MissionMaxIDx = 3, MissionCheckSuccess = true;
            }
            case 17, 40, 104: // Автомеханик;
            {
                MissionCoords[0][0] = 1640.1200, MissionCoords[0][1] = -1116.8104, MissionCoords[0][2] = 23.9063;
                MissionCoords[1][0] = -2023.4312, MissionCoords[1][1] = 156.8808, MissionCoords[1][2] = 28.8359;
                MissionCoords[2][0] = 2137.6318, MissionCoords[2][1] = 953.3112, MissionCoords[2][2] = 10.6803;

                MissionMaxIDx = 3, MissionCheckSuccess = true;
            }
            case 20, 43, 107: // Пожарный;
            {
                MissionCoords[0][0] = 1756.2947, MissionCoords[0][1] = -1455.3763, MissionCoords[0][2] = 13.5469;
                MissionCoords[1][0] = -2014.3455, MissionCoords[1][1] = 83.9995, MissionCoords[1][2] = 27.6799;
                MissionCoords[2][0] = 1760.9218, MissionCoords[2][1] = 2060.6863, MissionCoords[2][2] = 10.9766;

                MissionMaxIDx = 3, MissionCheckSuccess = true;
            }
            case 21, 44, 108: // Машинист поезда;
            {
                MissionCoords[0][0] = 1778.0112, MissionCoords[0][1] = -1953.6497, MissionCoords[0][2] = 14.8756;
                MissionCoords[1][0] = -1942.1152, MissionCoords[1][1] = 142.9281, MissionCoords[1][2] = 27.0006;
                MissionCoords[2][0] = 1474.9150, MissionCoords[2][1] = 2632.2500, MissionCoords[2][2] = 12.1256;
                MissionCoords[3][0] = 2864.7500, MissionCoords[3][1] = 1299.6431, MissionCoords[3][2] = 12.1256;

                MissionMaxIDx = 4, MissionCheckSuccess = true;
            }
            case 23, 46, 110: // Пилот;
            {
                MissionCoords[0][0] = 1645.9452, MissionCoords[0][1] = -2430.2759, MissionCoords[0][2] = 13.5547;
                MissionCoords[1][0] = -1223.0778, MissionCoords[1][1] = -162.3596, MissionCoords[1][2] = 14.1484;
                MissionCoords[2][0] = 1525.8293, MissionCoords[2][1] = 1782.4193, MissionCoords[2][2] = 10.8203;

                MissionMaxIDx = 3, MissionCheckSuccess = true;
            }
            case 26: // Дом;
            {
                MissionCoords[0][0] = b_info[58][b_enter][0];
                MissionCoords[0][1] = b_info[58][b_enter][1];
                MissionCoords[0][2] = b_info[58][b_enter][2];

                MissionIDx = 0, MissionCheckSuccess = true;
            }
            case 51: // Бары;
            {
                for(new i = 24; i < 31; i++)
                {
                    MissionCoords[i - 24][0] = b_info[i][b_enter][0];
                    MissionCoords[i - 24][1] = b_info[i][b_enter][1];
                    MissionCoords[i - 24][2] = b_info[i][b_enter][2];
                }

                MissionMaxIDx = 8, MissionCheckSuccess = true;
            }
        }

        if(MissionCheckSuccess == true)
        {
            for(new i = 0; i < MissionMaxIDx; i++)
            {
                here_distance = (!IsPlayerInAnyVehicle(playerid)) ? floatround(GetPlayerDistanceFromPoint(playerid, MissionCoords[i][0], MissionCoords[i][1], MissionCoords[i][2])) : floatround(GetVehicleDistanceFromPoint(GetPlayerVehicleID(playerid), MissionCoords[i][0], MissionCoords[i][1], MissionCoords[i][2]));
                if(here_distance < max_distance)
                {
                    MissionIDx = i;
                    max_distance = here_distance;
                }
            }
            if(max_distance == -1 || MissionIDx == -1) return 1;
            SetPlayerGPS(playerid, MissionCoords[MissionIDx][0], MissionCoords[MissionIDx][1], MissionCoords[MissionIDx][2], 5.0);
            new Float:distance = GetPlayerDistanceFromPoint(playerid, MissionCoords[MissionIDx][0], MissionCoords[MissionIDx][1], MissionCoords[MissionIDx][2]);
            SendInfo(playerid, "Место начала %s отмечено на GPS навигаторе. Расстояние: %.0f метров.", mission_type_name[type], distance);
        }
    }
    else
    {
        SetPlayerGPS(playerid, Mission[idx][mCoords][0], Mission[idx][mCoords][1], Mission[idx][mCoords][2], 5.0);
        new Float:distance = GetPlayerDistanceFromPoint(playerid, Mission[idx][mCoords][0], Mission[idx][mCoords][1], Mission[idx][mCoords][2]);
        SendInfo(playerid, "Место начала %s отмечено на GPS навигаторе. Расстояние: %.0f метров.", mission_type_name[type], distance);
    }
    return 1;
}

SavePlayerMission(playerid, type)
{
    switch(type)
    {
        case MISSION_TYPE_START_TASK:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",
            p_info[playerid][quest][0], p_info[playerid][quest][1], p_info[playerid][quest][2], p_info[playerid][quest][3], p_info[playerid][quest][4], p_info[playerid][quest][5], p_info[playerid][quest][6], p_info[playerid][quest][7],
            p_info[playerid][quest][8], p_info[playerid][quest][9], p_info[playerid][quest][10], p_info[playerid][quest][11], p_info[playerid][quest][12], p_info[playerid][quest][13], p_info[playerid][quest][14], p_info[playerid][quest][15],
            p_info[playerid][quest][16], p_info[playerid][quest][17], p_info[playerid][quest][18], p_info[playerid][quest][19], p_info[playerid][quest][20], p_info[playerid][quest][21], p_info[playerid][quest][22], p_info[playerid][quest][23],
            p_info[playerid][quest][24], p_info[playerid][quest][25], p_info[playerid][quest][26], p_info[playerid][quest][27], p_info[playerid][quest][28], p_info[playerid][quest][29], p_info[playerid][quest][30], p_info[playerid][quest][31],
            p_info[playerid][quest][32]);
            MysqlUpdatePlayerStr(playerid, "quest", STRING_GLOBAL);
        }
        case MISSION_TYPE_DAILY_TASK:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d||%d|%d|%d|%d",
            p_info[playerid][mission][0], p_info[playerid][mission][1], p_info[playerid][mission][2], p_info[playerid][mission][3], p_info[playerid][mission][4], p_info[playerid][mission][5], p_info[playerid][mission][6], p_info[playerid][mission][7],
            p_info[playerid][mission][8], p_info[playerid][mission][9], p_info[playerid][mission][10], p_info[playerid][mission][11], p_info[playerid][mission][12], p_info[playerid][mission][13], p_info[playerid][mission][14], p_info[playerid][mission][15],
            p_info[playerid][mission][16], p_info[playerid][mission][17], p_info[playerid][mission][18], p_info[playerid][mission][19], p_info[playerid][mission][20], p_info[playerid][mission][21], p_info[playerid][mission][22], p_info[playerid][mission][23],
            p_info[playerid][mission][24], p_info[playerid][mission][25], p_info[playerid][mission][26], p_info[playerid][mission][27], p_info[playerid][mission][28], p_info[playerid][mission][29], p_info[playerid][mission][30], p_info[playerid][mission][31],
            p_info[playerid][mission][32], p_info[playerid][mission][33], p_info[playerid][mission][34], p_info[playerid][mission][35], p_info[playerid][mission][36], p_info[playerid][mission][37], p_info[playerid][mission][38], p_info[playerid][mission][39],
            p_info[playerid][mission][40], p_info[playerid][mission][41], p_info[playerid][mission][42], p_info[playerid][mission][43], p_info[playerid][mission][44], p_info[playerid][mission][45], p_info[playerid][mission][46], p_info[playerid][mission][47],
            p_info[playerid][mission][48], p_info[playerid][mission][49], p_info[playerid][mission][50], p_info[playerid][mission][51], p_info[playerid][mission][52], p_info[playerid][mission][53], p_info[playerid][mission][54], p_info[playerid][mission][55],
            p_info[playerid][mission][56], p_info[playerid][mission][57], p_info[playerid][mission][58], p_info[playerid][mission][59], p_info[playerid][mission][60], p_info[playerid][mission][61], p_info[playerid][mission][62], p_info[playerid][mission][63],
            p_info[playerid][mission][64], p_info[playerid][mission][65], p_info[playerid][mission][66], p_info[playerid][mission][67], p_info[playerid][mission][68]);
            MysqlUpdatePlayerStr(playerid, "mission", STRING_GLOBAL);

            MysqlUpdatePlayerInt(playerid, "mission_exp", p_info[playerid][mission_exp]);

            MysqlUpdatePlayerInt(playerid, "mission_days", p_info[playerid][mission_days]);
        }
        case MISSION_TYPE_ACHIEVEMENT:
        {
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",
            p_info[playerid][achievement][0], p_info[playerid][achievement][1], p_info[playerid][achievement][2], p_info[playerid][achievement][3], p_info[playerid][achievement][4], p_info[playerid][achievement][5], p_info[playerid][achievement][6], p_info[playerid][achievement][7],
            p_info[playerid][achievement][8], p_info[playerid][achievement][9], p_info[playerid][achievement][10], p_info[playerid][achievement][11], p_info[playerid][achievement][12], p_info[playerid][achievement][13], p_info[playerid][achievement][14], p_info[playerid][achievement][15],
            p_info[playerid][achievement][16], p_info[playerid][achievement][17], p_info[playerid][achievement][18], p_info[playerid][achievement][19], p_info[playerid][achievement][20], p_info[playerid][achievement][21], p_info[playerid][achievement][22], p_info[playerid][achievement][23],
            p_info[playerid][achievement][24], p_info[playerid][achievement][25], p_info[playerid][achievement][26], p_info[playerid][achievement][27], p_info[playerid][achievement][28], p_info[playerid][achievement][29], p_info[playerid][achievement][30]);
            MysqlUpdatePlayerStr(playerid, "achievement", STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",
            p_info[playerid][achievement_progress][0], p_info[playerid][achievement_progress][1], p_info[playerid][achievement_progress][2], p_info[playerid][achievement_progress][3], p_info[playerid][achievement_progress][4], p_info[playerid][achievement_progress][5], p_info[playerid][achievement_progress][6], p_info[playerid][achievement_progress][7],
            p_info[playerid][achievement_progress][8], p_info[playerid][achievement_progress][9], p_info[playerid][achievement_progress][10], p_info[playerid][achievement_progress][11], p_info[playerid][achievement_progress][12], p_info[playerid][achievement_progress][13], p_info[playerid][achievement_progress][14], p_info[playerid][achievement_progress][15],
            p_info[playerid][achievement_progress][16], p_info[playerid][achievement_progress][17], p_info[playerid][achievement_progress][18], p_info[playerid][achievement_progress][19], p_info[playerid][achievement_progress][20], p_info[playerid][achievement_progress][21], p_info[playerid][achievement_progress][22], p_info[playerid][achievement_progress][23],
            p_info[playerid][achievement_progress][24], p_info[playerid][achievement_progress][25], p_info[playerid][achievement_progress][26], p_info[playerid][achievement_progress][27], p_info[playerid][achievement_progress][28], p_info[playerid][achievement_progress][29], p_info[playerid][achievement_progress][30]);
            MysqlUpdatePlayerStr(playerid, "achievement_progress", STRING_GLOBAL);
        }
    }
    return 1;
}

new pickup_mission[4];

stock LoadPlayerMission()
{
    // Организатор заданий;
    CreateActor(289, 1158.2439,-1752.5525,13.6016,135.7993);
    CreateDynamic3DTextLabel("NPC: "I"Организатор заданий", COLOR_WHITE, 1158.2439,-1752.5525,13.6016 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    // Организатор заданий;
    CreateActor(289, -1962.8013,121.7079,27.6875,85.2648);
    CreateDynamic3DTextLabel("NPC: "I"Организатор заданий", COLOR_WHITE, -1962.8013,121.7079,27.6875 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    // Организатор заданий;
    CreateActor(289, 2842.7947,1286.5234,11.3906,0.0000);
    CreateDynamic3DTextLabel("NPC: "I"Организатор заданий", COLOR_WHITE, 2842.7947,1286.5234,11.3906 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    // Организатор заданий;
    CreateActor(289, 1769.1130,-1898.4370,13.5749,41.8941);
    CreateDynamic3DTextLabel("NPC: "I"Организатор заданий", COLOR_WHITE, 1769.1130,-1898.4370,13.5749 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_mission[0] = CreatePickup(1239, 23, 1157.8712,-1752.9755,13.6065);
    CreateDynamic3DTextLabel("<< Задания для новичков >>", COLOR_MAIN, 1157.8712,-1752.9755,13.6065, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_mission[1] = CreatePickup(1239, 23, -1963.5011,121.6856,27.6875);
    CreateDynamic3DTextLabel("<< Задания для новичков >>", COLOR_MAIN, -1963.5011,121.6856,27.6875, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_mission[2] = CreatePickup(1239, 23, 2842.7937,1287.2238,11.3906);
    CreateDynamic3DTextLabel("<< Задания для новичков >>", COLOR_MAIN, 2842.7937,1287.2238,11.3906, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    pickup_mission[3] = CreatePickup(1239, 23, 1768.7162,-1898.0386,13.5746);
    CreateDynamic3DTextLabel("<< Задания для новичков >>", COLOR_MAIN, 1768.7162,-1898.0386,13.5746, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}
