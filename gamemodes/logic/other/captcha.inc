CreateCaptchaForPlayer(playerid)
{
	new captcha_random,
        Float:captcha_letter[][] =
		{
        	{ 0.2415, 2.1537 },
        	{ 0.4750, 2.5333 },
        	{ 0.3390, 2.0480 },
        	{ 0.2355, 2.3760 },
        	{ 0.3725, 1.8364 },
        	{ 0.2339, 2.4400 }
		},
        captcha_pos[6][2],
		numbers[][] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" },
        num_id;

    p_temp[playerid][captcha][0] = EOS;

	for(new i; i < 6; i ++)
	{
		num_id = random(10);

        captcha_pos[i][0] = 270+random(5)+i*15;
        captcha_pos[i][1] = 120+random(30);

        if(p_temp[playerid][TextDrawCaptcha])
            PlayerTextDrawDestroy(playerid, PTD_Captcha[playerid][i]);

        captcha_random = random(6);
		PTD_Captcha[playerid][i] = CreatePlayerTextDraw(playerid, captcha_pos[i][0], captcha_pos[i][1], numbers[num_id]);
		PlayerTextDrawLetterSize(playerid, PTD_Captcha[playerid][i], captcha_letter[captcha_random][0], captcha_letter[captcha_random][1]);
		PlayerTextDrawAlignment(playerid, PTD_Captcha[playerid][i], 1);
		PlayerTextDrawColor(playerid, PTD_Captcha[playerid][i], -1);
		PlayerTextDrawFont(playerid, PTD_Captcha[playerid][i], 1);
		PlayerTextDrawSetProportional(playerid, PTD_Captcha[playerid][i], 1);
		PlayerTextDrawSetShadow(playerid, PTD_Captcha[playerid][i], 0);

		PlayerTextDrawShow(playerid, PTD_Captcha[playerid][i]);

		strcat(p_temp[playerid][captcha], numbers[num_id]);
	}

    //sSendDebug(playerid, "%s", p_temp[playerid][captcha]);
    return 1;
}
///////////////////////////////////////////////////////////////////////////////
Captcha_UpdateNumber(playerid)
{
    new natural_numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    shuffle(natural_numbers);

    for(new i = 9; i != -1; i--)
    {
        p_temp[playerid][p_listitem][i] = natural_numbers[i];
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "%d", natural_numbers[i]);
        PlayerTextDrawSetString(playerid, PTD_PinCode[playerid][i], STRING_GLOBAL);
    }
}
///////////////////////////////////////////////////////////////////////////////////
stock Captcha_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == Text:INVALID_TEXT_DRAW) return SelectTextDraw(playerid, -8708097);
    for(new i = 12; i != 2; i--)
    {
        if(clickedid == TD_PinCode[i])
        {
            if(strlen(p_temp[playerid][captcha_text]) > 9)
                return SendError(playerid, "Максимальная длина 10 символов.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%d", p_temp[playerid][p_listitem][i-3]);
            strcat(p_temp[playerid][captcha_text], STRING_GLOBAL);
            PlayerTextDrawSetString(playerid, PTD_PinCode[playerid][10], p_temp[playerid][captcha_text]);
            Captcha_UpdateNumber(playerid);
            break;
        }
    }
    if(clickedid == TD_PinCode[14])
    {
        if(strlen(p_temp[playerid][captcha_text]) <= 0) return 1;
        strdel(p_temp[playerid][captcha_text], strlen(p_temp[playerid][captcha_text])-1, strlen(p_temp[playerid][captcha_text]));
        PlayerTextDrawSetString(playerid, PTD_PinCode[playerid][10], p_temp[playerid][captcha_text]);
    }
    else if(clickedid == TD_PinCode[13])
    {
        if(p_temp[playerid][TextDrawCaptcha] != CAPTCHA_PIN_CODE && !strlen(p_temp[playerid][captcha_text]))
        {
            HideTextDraw_Captcha(playerid);
            p_temp[playerid][p_listitem_int] = -1;
            return 1;
        }
        switch(p_temp[playerid][TextDrawCaptcha])
        {
            case CAPTCHA_TRAINING_ID:
            {
                if(!strequals(p_temp[playerid][captcha], p_temp[playerid][captcha_text]))
                    return ShowTextDraw_Captcha(playerid, p_temp[playerid][TextDrawCaptcha]);
                HideTextDraw_Captcha(playerid);
                return 1;
            }
            case CAPTCHA_HOUSE_ID:
            {
                if(!strequals(p_temp[playerid][captcha], p_temp[playerid][captcha_text]))
                    return ShowTextDraw_Captcha(playerid, p_temp[playerid][TextDrawCaptcha]);
                HideTextDraw_Captcha(playerid);

                new h = p_temp[playerid][p_listitem_int],
                    h_class = h_info[h][h_squar]-1,
                    int_id = h_info[h][h_int];
                p_temp[playerid][p_listitem_int] = -1;

                if(h == INVALID_HOUSE_ID) return SendError(playerid, "Код ошибки: 1011A (Обратитесь к администрации)");
                if(h_class == -1) return SendError(playerid, "Код ошибки: 1011B (Обратитесь к администрации)");
                if(int_id == -1) return SendError(playerid, "Код ошибки: 1011C (Обратитесь к администрации)");
                if(h_info[h][h_delete] == 1) return SendError(playerid, "Данный дом нельзя приобрести.");
                if(h_info[h][h_auction_bet] != 0 || h_info[h][h_auction_time] != 0)
                    return SendError(playerid, "Дом находится на аукционе, приобрести его можно в риэлторском агентстве.");
                if(h_info[h][h_rob_house]) return SendError(playerid, "В данный момент этот дом грабят, дверь сломана.");
                if(h_info[h][h_user_id] != INVALID_MYSQL_ID)
                    return SendError(playerid, "У данного дома уже есть владелец.");
                new cost_house = h_info[h][h_value], list_percent[3] = {95, 90, 85}, vip_idx = p_info[playerid][p_vip];
                if(vip_idx) cost_house = ((h_info[h][h_value] / 100) * list_percent[vip_idx - 1]);
                if(p_info[playerid][cash] < cost_house)
                    return SendError(playerid, "У Вас не достаточно денег.");

                SetFreeSlotHouse(playerid, h);
                h_info[h][h_user_id] = p_info[playerid][ID];
                h_info[h][h_lock] = 1;
                h_info[h][h_garage_lock] = 1;
                h_info[h][h_rent] = 24;
                h_info[h][h_owned_at] = timestamp;
                h_info[h][h_paydays_received] = 0;
                //set default house new
                h_info[h][h_int] =
                h_info[h][h_improve][SUBSIDY] =
                h_info[h][h_improve][RENTERS] =
                h_info[h][h_improve][BASEMENT] =
                h_info[h][h_improve][UNDERGROUND] = 0;
                h_info[h][h_family_id] = -1;
                h_info[h][h_delete] = 0;
                h_info[h][h_delete_time] = 0;
                save_house_interior(h); // обнуление кастомный инты
                save_garage_interior(h);

                ClearInventoryItems(h_info[h][h_mysql_id], INVENTORY_OWNER_TYPE_HOUSE);

                strmid(h_info[h][h_owner], get_name(playerid), 0, strlen(get_name(playerid)), MAX_PLAYER_NAME);
                SetPlayerHousePos(playerid, h, h_class, h_info[h][h_int]);

                //lastlog(BUY_HOUSE_GOS,"покупка дома из госса", h_info[h][h_mysql_id], playerid, playerid, -cost_house);
                // [logs] реализовать получение версии клиента
                // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) купил дом (%d)[%d] из госса за %d$
                Log(LOG_player, INFO, "%s[%d](%s %s) купил дом (%d)[%d] из госа за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                    h, h_info[h][h_mysql_id], cost_house);

                SetPlayerMoney(playerid, -cost_house, true, "", h, h_info[h][h_mysql_id]);
                SendAccess(playerid, "Вы приобрели дом за %d$.", cost_house);
                p_info[playerid][spawn] = SPAWN_HOUSE;
                OnServerInfoForMoney[0] += cost_house;

                SetFractionWarehouse(MAYOR_LS, fwMoney, cost_house);

                update_house(h);
                save_house(h);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] купил дом №%d из госа", get_name(playerid), playerid, h);
                SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

                CheckPlayerMission(playerid, START_HOUSE);
                return 1;
            }
            case CAPTCHA_BIZZ_ID:
            {
                if(!strequals(p_temp[playerid][captcha], p_temp[playerid][captcha_text]))
                    return ShowTextDraw_Captcha(playerid, p_temp[playerid][TextDrawCaptcha]);
                HideTextDraw_Captcha(playerid);

                new bizz_id = p_temp[playerid][p_listitem_int];
                p_temp[playerid][p_listitem_int] = -1;

                if(GetFreeSlotBizz(playerid) == ALL_BUSY_SLOT_BIZZ)
                    return SendError(playerid, "У Вас нет свободного слота для бизнеса.");

                new cost_biz = b_info[bizz_id][_price], list_percent[3] = {95, 90, 85}, vip_idx = p_info[playerid][p_vip];
                if(vip_idx) cost_biz = ((b_info[bizz_id][_price] / 100) * list_percent[vip_idx - 1]);

                if(p_info[playerid][cash] < cost_biz)
                    return SendError(playerid, "У Вас нет столько денег. Используйте /donate");

                if(b_info[bizz_id][b_user_id] != INVALID_MYSQL_ID)
                    return SendError(playerid, "У бизнеса уже есть владелец.");

                if(b_info[bizz_id][b_auction_bet] != 0 || b_info[bizz_id][b_auction_time] != 0)
                    return SendError(playerid, "Бизнес находится на аукционе, приобрести его можно в риэлторском агентстве.");

                switch(b_info[bizz_id][_tip])
                {
                    case B_TAXI:
                    {
                        if(GetPlayerBizzIDType(playerid, B_TAXI) != INVALID_BIZZ_ID) return SendError(playerid, "У Вас уже есть таксопарк.");
                        p_info[playerid][taxi_rank] = 3;
                        p_info[playerid][taxi_idx] = bizz_id;
                        p_info[playerid][taxi_percent] = b_info[bizz_id][_percent];
                        p_info[playerid][taxi_salary] = 0;
                        p_info[playerid][taxi_salary_all] = 0;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `taxi_rank` = 3, `taxi_idx` = %d, `taxi_percent` = %d, `taxi_salary` = 0, `taxi_salary_all` = 0 WHERE `id` = %d",
                        p_info[playerid][taxi_idx], p_info[playerid][taxi_percent], p_info[playerid][ID]);
                        mysql_tquery(con_bd, STRING_GLOBAL);
                    }
                    case B_TRUCKER:
                    {
                        if(GetPlayerBizzIDType(playerid, B_TRUCKER) != INVALID_BIZZ_ID) return SendError(playerid, "У Вас уже есть транспортная компания.");
                        p_info[playerid][tc_rank] = 3;
                        p_info[playerid][tc_idx] = bizz_id;
                        p_info[playerid][tc_percent] = b_info[bizz_id][_percent];
                        p_info[playerid][tc_salary] = 0;
                        p_info[playerid][tc_salary_all] = 0;
                        STRING_GLOBAL[0] = EOS;
                        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `tc_rank` = 3, `tc_idx` = %d, `tc_percent` = %d, `tc_salary` = 0, `tc_salary_all` = 0 WHERE `id` = %d",
                        p_info[playerid][tc_idx], p_info[playerid][tc_percent], p_info[playerid][ID]);
                        mysql_tquery(con_bd, STRING_GLOBAL);
                    }
                }

                // [logs] реализовать получение версии клиента
                // Jeffrey_Collinz[2](127.0.0.1 PC/0.3.7-R2) купил бизнес <%s - %s>(%d)[%d] за %d$
                Log(LOG_player, INFO, "%s[%d](%s %s) купил бизнес <%s - %s>(%d)[%d] за %d$",
                    get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC",
                    b_info[bizz_id][_name], bizz_type_name[b_info[bizz_id][_tip]], bizz_id, b_info[bizz_id][b_mysql_id], cost_biz);

                b_info[bizz_id][b_owned_at] = timestamp;
                b_info[bizz_id][b_paydays_received] = 0;
                b_info[bizz_id][b_user_id] = p_info[playerid][ID];
                SetFreeSlotBizz(playerid, bizz_id);
                b_info[bizz_id][_till] = 1;
                OnServerInfoForMoney[1] += cost_biz;
                SetPlayerMoney(playerid, -cost_biz, true, "");
                strmid(b_info[bizz_id][_owner], get_name(playerid), 0, strlen(get_name(playerid)), 255);
                b_info[bizz_id][b_rent] = 24;
                b_info[bizz_id][_prod] = 500;
                b_info[bizz_id][_bank] = 0;

                b_info[bizz_id][_percent] = 10;
                b_info[bizz_id][b_fare][0] = 200;
                b_info[bizz_id][b_fare][1] = 250;
                b_info[bizz_id][b_fare][2] = 200;
                b_info[bizz_id][b_fare][3] = 500;

                b_info[bizz_id][b_upgrade_warehouse] = 0;
                b_info[bizz_id][b_upgrade_class] = 0;
                b_info[bizz_id][b_upgrade_tax] = 0;

                SendAccess(playerid, "Вы приобрели бизнес.");
                SendInfo(playerid, "Меню бизнеса: /bizmenu");
                update_bizz(bizz_id);
                save_bizz(bizz_id);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[A] %s[%d] купил бизнес №%d из госса", get_name(playerid), playerid, bizz_id);
                SendAdminMessage(COLOR_LIGHTRED, STRING_GLOBAL);

                SetFractionWarehouse(MAYOR_LS, fwMoney, b_info[bizz_id][_price]);
                return 1;
            }
            /*
            case CAPTCHA_REG_ID:
            {
                if(!strequals(p_temp[playerid][captcha], p_temp[playerid][captcha_text]))
                    return ShowTextDraw_Captcha(playerid, p_temp[playerid][TextDrawCaptcha]);
                HideTextDraw_Captcha(playerid);

                new strdate[24];
                new year,month,day;
                getdate(year, month, day);
                format(strdate, sizeof(strdate), "%d.%d.%d",day,month,year);

                //
                p_info[playerid][level] = 1;
                p_info[playerid][key_h_rent] = INVALID_HOUSE_ID;
                SetPlayerHouseID(playerid, INVALID_HOUSE_ID);
                SetPlayerBizzID(playerid, INVALID_BIZZ_ID);
                //
                SendMes(playerid, COLOR_ORANGE, "Аккаунт зарегистрирован.");
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `accounts` (`name`, `password`, `referral`, `regip`, `datareg`, `sex`, `mail`, `usepassword`, `source_reg`) VALUES ('%e', '%e', %d, '%e', '%e', %d, '%e', '1', %d)",
                    get_name(playerid), p_info[playerid][password], p_info[playerid][referral], p_temp[playerid][session_IP], strdate, p_info[playerid][sex], p_info[playerid][mail], p_temp[playerid][p_listitem_int]);
                mysql_tquery(con_bd, STRING_GLOBAL, "EndRegistretionPlayer", "i", playerid);

                p_info[playerid][spawn] = 0;
                p_temp[playerid][p_listitem_int] = -1;
            }
            */
            case CAPTCHA_PIN_CODE:
            {
                HideTextDraw_Captcha(playerid);
                if(strlen(p_info[playerid][google_code]) > 5)
                    return ShowPlayerDialog(playerid, D_GOOGLE_AUTH, DIALOG_STYLE_INPUT, ""I"Google Authenticator", ""W"Введите одноразовый код из приложения Google Authenticator, он состоит из цифр:", "Вход", "");
                LoadPlayerAccount(playerid);
            }
        }
    }
    return 1;
}
