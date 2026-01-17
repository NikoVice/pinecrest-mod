

new easter_area[2];

ShowEasterQuest_Main(playerid)
{
    if(p_info[playerid][event_quest_id] == MAX_EVENT_QUEST) return 1;
    if(p_info[playerid][level] < 3) return SendError(playerid, "У Вас нет 3 уровня.");
    switch(p_info[playerid][event_quest_id])
    {
        case 0: SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);
        case 1:
        {
            SetPlayerGPS(playerid, -383.5103,-1446.0826,25.7266, 6.0);

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Приветствую вас. Я Мая, и мне нужна ваша помощь.\n\
                Милый гость, мой дедушка совсем старый, не может нормально передвигаться, да и мне очень далеко.\n\
                Не мог бы ты нам помочь?\n\
                \n\
                Задание: Отправляйтесь на ферму и возьмите там молока, яиц и муки для бабушки Маи.", "ОК", "");

            p_info[playerid][event_quest_id] = 2;
            p_info[playerid][event_quest_stage] = 0;

            
        }
        case 2:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Приветствую тебя, что привело тебя к нам?\n\
                Ах вот как, тебе нужны продукты.. Ну, пожалуй помоги мне сперва, а там и получишь то что тебе нужно.\n\
                \n\
                Задание: Вам нужно собрать 10 ящиков апельсин.\n\
                Награда: "I"250 000$ и 25 FM", "ОК", "");
        }
        case 3:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Молодец! Ты выполнил мое первое поручение, теперь подои коров 5 раз.\n\
                \n\
                Задание: Вам нужно подоить коров 5 раз.\n\
                Награда: "I"150 000$ и 25 FM", "ОК", "");
        }
        case 4:
        {
            SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Ну что же, спасибо за помощь по хозяйству, держи свою муку, яица и молоко.\n\
                \n\
                Задание: Теперь отпавляйтесь к бабушке Мае что бы отдать ей продукты.", "ОК", "");

            p_info[playerid][event_quest_id] = 5;
            p_info[playerid][event_quest_stage] = 1;
        }
        case 5:
        {
            SetPlayerGPS(playerid, 995.0022,-2113.1335,13.0938, 6.0);

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Золотце мое, у меня вся краска уже потрескалась и высохла, будь добр съездить\n\
                в Тепличный Комплекс после чего найти там красители нескольких цветов.\n\
                \n\
                Задание: Отправляйтесь к Тепличному комплексу, после чего найдите там 5 красителя.\n\
                Награда: "I"250000$ и 50 FM", "ОК", "");

            ShowEasterQuest_Check(playerid);

            p_info[playerid][event_quest_id] = 6;
            p_info[playerid][event_quest_stage] = 0;
        }
        case 6:
        {
            SetPlayerGPS(playerid, 995.0022,-2113.1335,13.0938, 6.0);

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Золотце мое, у меня вся краска уже потрескалась и высохла, будь добр съездить\n\
                в Тепличный Комплекс после чего найти там красители нескольких цветов.\n\
                \n\
                Задание: Отправляйтесь к Тепличному комплексу, после чего найдите там 5 красителя.\n\
                Награда: "I"250000$ и 50 FM", "ОК", "");
        }
        case 7:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Охх, у меня тут новая беда, я разбила последние яйца. Не мог бы ты помочь мне?\n\
                \n\
                Задание: Вам нужно найти  10 штук яиц расбросаных по карте, если будет меньше придется искать еще.\n\
                Награда: "I"500000$ и 150 FM", "ОК", "");
        }
        case 8:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Отлично, сейчас бабушка начнет делать из них шедевры, я вот сделала парочку найди пока кого-то с кем можно проверить на прочность эти яйца.\n\
                \n\
                Задание: Вам нужно сыграть 10 раз в битьё яиц, после чего поиграть с ними (( /eggs ID ))\n\
                Награда: "I"150000$ и 50 FM", "ОК", "");
        }
        case 9:
        {
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Дитятко мое, съезди в ближайший магазин и купи мне пачку спичек, я не смогу без них растопить печь и приготовить пасху.\n\
                \n\
                Задание: Вам нужно купить и доставить бабуле Мае спички (/gps > Бизнесы > Ближайший супермаркет)\n\
                Награда: "I"50000$ и 50 FM", "ОК", "");
        }
        case 10:
        {
            new item_id = 580+random(4);
            if(!GivePlayerInventory(playerid, item_id)) return SendError(playerid, "В инвентаре нет места.");

            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Праздничный квест", ""W"\
                Хух, ну спасибо тебе большое! Все таки я не пропущу свой любимый праздник,\n\
                и смогу померяться силой со своими подругами с другой деревни.\n\
                Вот тебе "I"300 Flin Money"W" и уникальный аксессуар "I"\"Разноцветное Яйцо\".\n\
                "W"          Спасибо, добрый человек. С Пасхой вас!", "ОК", "");

            p_info[playerid][event_quest_stage] = 0;
            MysqlUpdatePlayerInt(playerid, "event_quest_stage", p_info[playerid][event_quest_stage]);

            p_info[playerid][event_quest_id] = MAX_EVENT_QUEST;
            MysqlUpdatePlayerInt(playerid, "event_quest_id", p_info[playerid][event_quest_id]);

            p_info[playerid][flinmoney] += 300;
            MysqlUpdatePlayerInt(playerid, "flinmoney", p_info[playerid][flinmoney]);

            SendInfo(playerid, "За выполнение задания Вам выдана награда в размере 300 Flin Money и уникальный аксессуар \"%s\".", ItemsInfo[item_id][iName]);
        }
    }
    SaveEventProggress(playerid);
    return 1;
}

ShowEasterQuest_Check(playerid)
{
    if(p_info[playerid][event_quest_id] == MAX_EVENT_QUEST) return 1;
    switch(p_info[playerid][event_quest_id])
    {
        case 2:
        {
            if(0 <= p_info[playerid][event_quest_stage] < 10)
            {
                p_info[playerid][event_quest_stage]++;
                if(p_info[playerid][event_quest_stage] == 10)
                {
                    SetPlayerMoney(playerid, 250000, true, "EASTER: квест 1");
                    p_info[playerid][flinmoney] += 25;

                    p_info[playerid][event_quest_id] = 3;
                    p_info[playerid][event_quest_stage] = 0;

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 250000$ и 25 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);
                }
                else SendInfo(playerid, "Прогресс выполнения задания: %d из 10.", p_info[playerid][event_quest_stage]);
            }
        }
        case 3:
        {
            if(0 <= p_info[playerid][event_quest_stage] < 5)
            {
                p_info[playerid][event_quest_stage]++;
                if(p_info[playerid][event_quest_stage] == 5)
                {
                    SetPlayerMoney(playerid, 150000, true, "EASTER: квест 2");
                    p_info[playerid][flinmoney] += 25;

                    p_info[playerid][event_quest_id] = 4;
                    p_info[playerid][event_quest_stage] = 1;

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 150000$ и 25 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);
                }
                else SendInfo(playerid, "Прогресс выполнения задания: %d из 5.", p_info[playerid][event_quest_stage]);
            }
        }
        case 4:
        {
            if(p_info[playerid][event_quest_stage] == 1)
            {
                p_info[playerid][event_quest_id] = 5;
                p_info[playerid][event_quest_stage] = 1;
            }
        }
        case 5:
        {
            if(p_info[playerid][event_quest_stage] == 1)
            {
                SetPlayerMoney(playerid, 250000, true, "EASTER: квест 3");
                p_info[playerid][flinmoney] += 50;
                //награда за задание 1
                p_info[playerid][event_quest_id] = 6;
                p_info[playerid][event_quest_stage] = 0;

                SendAccess(playerid, "Поздравляем, Вы выполнили первое задание бабушки Маи.");
                SendInfo(playerid, "Награда за выполнение задания: 250000$ и 50 Flin Money.");

                SendInfo(playerid, "Приступайте к следующему заданию.");
            }
        }
        case 6:
        {
            if(0 <= p_info[playerid][event_quest_stage] < 5)
            {
                p_info[playerid][event_quest_stage]++;
                if(p_info[playerid][event_quest_stage] == 5)
                {
                    SetPlayerMoney(playerid, 250000, true, "EASTER: квест 4");
                    p_info[playerid][flinmoney] += 50;

                    p_info[playerid][event_quest_id] = 7;
                    p_info[playerid][event_quest_stage] = 0;

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 250000$ и 50 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);
                }
                else 
                {
                    SendAccess(playerid, "Поздравляем, вы нашли краситель нужный бабушке Мае, продолжайте работу.");
                    SendInfo(playerid, "Прогресс выполнения задания: %d из 5.", p_info[playerid][event_quest_stage]);
                }
            }
        }
        case 7:
        {
            if(p_info[playerid][event_quest_stage] >= 10)
            {
                SetPlayerMoney(playerid, 500000, true, "EASTER: квест 5");
                p_info[playerid][flinmoney] += 150;

                p_info[playerid][event_quest_id] = 8;
                p_info[playerid][event_quest_stage] = 0;

                SendAccess(playerid, "Вы выполнили задание.");
                SendInfo(playerid, "Награда за выполнение задания: 500000$ и 150 Flin Money.");
                SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);
            }
            else SendInfo(playerid, "Прогресс выполнения задания: %d из 10.", p_info[playerid][event_quest_stage]);
        }
        case 8:
        {
            if(0 <= p_info[playerid][event_quest_stage] < 10)
            {
                p_info[playerid][event_quest_stage]++;
                if(p_info[playerid][event_quest_stage] >= 10)
                {
                    SetPlayerMoney(playerid, 150000, true, "EASTER: квест 6");
                    p_info[playerid][flinmoney] += 50;

                    p_info[playerid][event_quest_id] = 9;
                    p_info[playerid][event_quest_stage] = 0;

                    SendAccess(playerid, "Вы выполнили задание.");
                    SendInfo(playerid, "Награда за выполнение задания: 150000$ и 50 Flin Money.");
                    SendInfo(playerid, "Отправляйтесь квестовому персонажу, чтобы получить следующее задание.");
                    SetPlayerGPS(playerid, 1103.8134,-299.8510,73.9851, 6.0);
                }
                else SendInfo(playerid, "Прогресс выполнения задания: %d из 10.", p_info[playerid][event_quest_stage]);
            }
        }
        case 9:
        {
            if(p_info[playerid][event_quest_stage] == 1)
            {
                SetPlayerMoney(playerid, 50000, true, "EASTER: квест 7");
                p_info[playerid][flinmoney] += 50;

                SendAccess(playerid, "Вы выполнили задание.");
                SendInfo(playerid, "Награда за выполнение задания: 50000$ и 50 Flin Money.");

                p_info[playerid][event_quest_id] = 10;
                p_info[playerid][event_quest_stage] = 0;
            }
        }
    }
    SaveEventProggress(playerid);
    return 1;
}

LoadEaster()
{
    CreateDynamicObject(14875,1117.8599900,-323.6040000,73.8100000,0.0000000,0.0000000,184.0000000); //object(kylie_hay1) (1)
    CreateDynamicObject(14875,1108.8671900,-304.4003900,73.8100000,0.0000000,0.0000000,0.0000000); //object(kylie_hay1) (2)
    CreateDynamicObject(3374,1058.2790500,-292.8800000,74.4860000,0.0000000,0.0000000,282.0000000); //object(sw_haybreak02) (1)
    CreateDynamicObject(12957,1066.9619100,-291.4668000,73.8630000,0.0000000,0.0000000,0.0000000); //object(sw_pickupwreck01) (1)
    CreateDynamicObject(849,1114.0639600,-304.8550100,73.2920000,0.0000000,0.0000000,0.0000000); //object(cj_urb_rub_3) (1)
    CreateDynamicObject(3302,1110.0550500,-323.1810000,73.0760000,0.0000000,0.0000000,308.0000000); //object(cxrf_corpanel) (1)
    CreateDynamicObject(1358,1102.7441400,-323.0898400,74.1960000,0.0000000,0.0000000,73.9980000); //object(cj_skip_rubbish) (1)
    CreateDynamicObject(1463,1105.8144500,-301.9150400,73.8610000,0.0000000,0.0000000,0.0000000); //object(dyn_woodpile2) (1)
    CreateDynamicObject(678,1095.5644500,-295.8945300,72.9920000,0.0000000,0.0000000,0.0000000); //object(sm_des_agave2) (1)
    CreateDynamicObject(678,1095.5119600,-295.8360000,72.9920000,0.0000000,0.0000000,0.0000000); //object(sm_des_agave2) (2)
    CreateDynamicObject(678,1101.2750200,-293.9310000,72.9920000,0.0000000,0.0000000,0.0000000); //object(sm_des_agave2) (3)
    CreateDynamicObject(678,1114.8439900,-325.8309900,72.9920000,0.0000000,0.0000000,0.0000000); //object(sm_des_agave2) (4)
    CreateDynamicObject(678,1119.6650400,-310.9070100,72.9920000,0.0000000,0.0000000,0.0000000); //object(sm_des_agave2) (5)
    CreateDynamicObject(3861,1118.8330100,-315.4677700,74.1650000,0.0000000,0.0000000,270.0000000); //object(marketstall01_sfxrf) (1)
    CreateDynamicObject(19636,1118.1070600,-314.5199900,73.8110000,0.0000000,0.0000000,286.0000000); //object(redapplescrate1) (1)
    CreateDynamicObject(1357,1116.9830300,-323.2749900,73.2590000,0.0000000,0.0000000,224.0000000); //object(cj_fruitcrate3) (1)
    CreateDynamicObject(1428,1105.8170200,-303.6680000,74.5600000,0.0000000,0.0000000,2.0000000); //object(dyn_ladder) (1)
    CreateDynamicObject(2856,1117.8060300,-316.6830100,73.8110000,0.0000000,0.0000000,300.0000000); //object(gb_foodwrap02) (1)
    CreateDynamicObject(2096,1105.5200200,-316.0480000,73.7420000,0.0000000,0.0000000,132.0000000); //object(cj_rockingchair) (1)
    CreateDynamicObject(2813,1118.3830600,-316.6210000,73.8110000,0.0000000,0.0000000,248.0000000); //object(gb_novels01) (1)
    CreateDynamicObject(3065,1098.0410200,-314.4400000,75.6320000,0.0000000,0.0000000,0.0000000); //object(bball_col) (1)
    CreateDynamicObject(2895,1096.5479700,-295.3949900,73.2570000,0.0000000,0.0000000,0.0000000); //object(fun_flower_law) (1)
    CreateDynamicObject(2895,1098.6739500,-293.8760100,73.2570000,0.0000000,0.0000000,76.0000000); //object(fun_flower_law) (3)

    CreateActor(197, 1103.8134,-299.8510,73.9851,123.4677);
    CreateDynamic3DTextLabel("NPC: "I"Бабуля Мая", COLOR_WHITE, 1103.8134,-299.8510,73.9851 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    CreateActor(161, -383.5103,-1446.0826,25.7266,51.1338);
    CreateDynamic3DTextLabel("NPC: "I"Владелец фермы", COLOR_WHITE, -383.5103,-1446.0826,25.7266 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

    easter_area[0] = CreateDynamicSphere(1103.8134,-299.8510,73.9851, 1.5, 0, 0);
    easter_area[1] = CreateDynamicSphere(-383.5103,-1446.0826,25.7266, 1.5, 0, 0);
    return 1;
}

SaveEventProggress(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof STRING_GLOBAL, "UPDATE `accounts` SET `event_quest_id` = %d, `event_quest_stage` = %d, `flinmoney` = %d WHERE `id` = %d",
        p_info[playerid][event_quest_id], p_info[playerid][event_quest_stage], p_info[playerid][flinmoney], p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);
}


CMD:eggs(playerid, params[])
{
    if(sscanf(params, "ud", params[0], params[1]))
        return SendInfo(playerid, "Введите: /eggs [id игрока] [ставка яиц]");
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не в сети.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой никы.");
    if(!IsPlayerStream(6.0, playerid, params[0]))
        return SendError(playerid, "Игрок слишком далеко.");
    if(GetInventoryAmount(params[0], 894) < params[1])
        return SendError(playerid, "У этого игрока нет столько яиц.");
    if(p_temp[params[0]][aggs_targetid] != INVALID_PLAYER_ID)
        return SendError(playerid, "У игрока уже есть предложение.");
    if(p_temp[playerid][aggs_targetid] != INVALID_PLAYER_ID)
        return SendError(playerid, "У Вас уже есть предложение.");
    if(params[1] < 2 || params[1] > 100)
        return SendError(playerid, "Минимальная ставка 2 максимальная 100.");

    SendAccess(playerid, "Вы предложили %s сыграть в битьё яиц. Ставка %d яиц.", get_name(params[0]), params[1]);
    SendInfo(playerid, "чтобы отменить: "I"/neggs (либо N)");

    SendInfo(params[0], "%s предлагает сыграть в битьё яиц. Ставка %d яиц.", get_name(playerid), params[1]);
    SendInfo(params[0], "Введите: "I"/yeggs (либо нажмите Y) "W"чтобы согласиться "I"/neggs (либо N) "W"для отказа.");

    p_temp[params[0]][aggs_targetid] = playerid;
    p_temp[playerid][aggs_targetid] = params[0];
    p_temp[params[0]][aggs_response] = 1;

    p_temp[params[0]][aggs_count] =
    p_temp[playerid][aggs_count] = params[1];
    return true;
}
cmd:neggs(playerid, params[])
{
    new targetid = p_temp[playerid][aggs_targetid];
    if(targetid == INVALID_PLAYER_ID || !p_temp[playerid][aggs_count])
        return 1;

    SendInfo(playerid, "Вы отказались от игры в битьё яиц.");
    SendInfo(targetid, "%s отказался от игры в битьё яиц.", get_name(playerid));

    EndAggs(playerid);
    return 1;
}

cmd:yeggs(playerid, params[])
{
    new targetid = p_temp[playerid][aggs_targetid];
    if(targetid == INVALID_PLAYER_ID || !p_temp[playerid][aggs_response])
        return 1;

    new bones[2],
        aggs_win = p_temp[playerid][aggs_count];

    if(GetInventoryAmount(playerid, 894) < aggs_win)
    {
        EndAggs(playerid);
        EndAggs(targetid);

        SendError(playerid, "Игра не может быть совершена, у Вас нет столько яиц.");
        SendError(targetid, "Игра не может быть совершена, у игрока нет столько яиц.");
        return 1;
    }
    if(GetInventoryAmount(targetid, 894) < aggs_win)
    {
        EndAggs(playerid);
        EndAggs(targetid);

        SendError(targetid, "Игра не может быть совершена, у Вас нет столько яиц.");
        SendError(playerid, "Игра не может быть совершена, у игрока нет столько яиц.");
        return 1;
    }

    bones[0] = random(12)+1;
    bones[1] = random(12)+1;

    if(bones[0] > bones[1])
    {
        SendInfo(playerid, "К сожалению, Вы проиграли.");
        SendInfo(targetid, "Поздравляем, Вы выиграли.");

        GivePlayerInventory(playerid, 894, -aggs_win);
        GivePlayerInventory(targetid, 894, (aggs_win-1));
    }
    if(bones[0] < bones[1])
    {
        SendInfo(targetid, "К сожалению, Вы проиграли.");
        SendInfo(playerid, "Поздравляем, Вы выиграли.");

        GivePlayerInventory(targetid, 894, -aggs_win);
        GivePlayerInventory(playerid, 894, (aggs_win-1));
    }
    if(bones[0] == bones[1])
    {
        SendInfo(playerid, "Игра закончилась в ничью.");
        SendInfo(targetid, "Игра закончилась в ничью.");
    }

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "%s и %s ударились яицами", get_name(targetid), get_name(playerid));
    ProxDetector(30.0, playerid, STRING_GLOBAL, 0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA);


    p_temp[playerid][aggs_response] = 0;

    EndAggs(playerid);
    EndAggs(targetid);

    if(p_info[playerid][event_quest_id] == 8)
        ShowEasterQuest_Check(playerid);

    if(p_info[targetid][event_quest_id] == 8)
        ShowEasterQuest_Check(targetid);

    return 1;
}
EndAggs(playerid)
{
    if(p_temp[playerid][aggs_targetid] == INVALID_PLAYER_ID) return 1;
    new targetid = p_temp[playerid][aggs_targetid];

    p_temp[playerid][aggs_targetid] =
    p_temp[targetid][aggs_targetid] = INVALID_PLAYER_ID;

    p_temp[targetid][aggs_count] =
    p_temp[playerid][aggs_count] =

    p_temp[targetid][aggs_response] =
    p_temp[playerid][aggs_response] = 0;
    return 1;
}