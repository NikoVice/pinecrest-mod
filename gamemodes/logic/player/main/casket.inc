GivePlayerCasket(playerid, idx = -1, count = 1)
{
	if(idx == -1)
	{
		new prize_idx[] = {721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 721, 724, 725, 726, 727, 728}, x = random(sizeof(prize_idx)), items_idx = prize_idx[x];
		if(GivePlayerInventory(playerid, items_idx, count))
		{
			SendMes(playerid, COLOR_YELLOW, "[ИНВЕНТАРЬ]: "W"В инвентарь добавлен предмет {"#cYELLOW"}\"%s\"."W" Количество: {"#cYELLOW"}%d.", ItemsInfo[items_idx][iName], count);
		}
	}
	else
	{
		if(GivePlayerInventory(playerid, idx, count))
		{
			SendMes(playerid, COLOR_YELLOW, "[ИНВЕНТАРЬ]: "W"В инвентарь добавлен предмет {"#cYELLOW"}\"%s\"."W" Количество: {"#cYELLOW"}%d.", ItemsInfo[idx][iName], count);
		}
	}
	return 1;
}

GetCasketInfo(idx)
{
	STRING_MIN[0] = EOS;
	f(STRING_MIN, ""W"\
	При открытии данного ларца возможно выпадение\n\
	"I"уникальных наград:"W"\n\n");
	switch(idx)
	{
		case 718:
		{
			strcat(STRING_MIN, "\
			Rolls-Royce Phantom\n\
			Porsche Panamero Turbo\n\
			Bentley Continental\n\
			Bentley Bentayga\n\n");
		}
		case 719:
		{
			strcat(STRING_MIN, "\
			Mercedes G63 AMG 6x6 [Бронированный]\n\
			Bugatti Chiron\n\
			Mercedes G63\n\
			Mercedes-Maybach\n\n");
		}
		case 720:
		{
			strcat(STRING_MIN, "\
			Mercedes W124\n\
			Mercedes 230\n\
			Mercedes 190E\n\
			Toyota Mark II\n\n");
		}
		case 721:
		{
			strcat(STRING_MIN, "\
			Tesla Model S\n\
			Nissan GTR\n\
			Lexus LX570\n\
			Land Cruiser 200\n\n");
		}
		case 722:
		{
			strcat(STRING_MIN, "\
			Ferrari Pista 488\n\
			McLaren 720s\n\
			McLaren 600LT\n\
			Aston Martin Vantage\n\n");
		}
		case 723:
		{
			strcat(STRING_MIN, "\
			Range Rover SVR\n\
			Cadillac Escalade\n\
			Lexus LX570\n\
			Land Cruiser 200\n\
			Jeep Grand Cherokee\n\n");
		}
		case 724:
		{
			strcat(STRING_MIN, "\
			Audi RS7\n\
			BMW E39\n\
			Mercedes C63 AMG\n\
			Lexus IS\n\
			Camry XV 70\n\
			Tesla Cybertruck\n\
			Audi 3\n\
			Mercedes W124\n\
			Mercedes 230\n\
			Mercedes 190E\n\
			Toyota Celica\n\
			Toyota Chaser\n\
			Toyota Mark II\n\n");
		}
		case 725:
		{
			strcat(STRING_MIN, "\
			Tesla Model S\n\
			Nissan GTR\n\
			Cadillac Escalade\n\
			Mercedes E63 AMG S\n\
			Lexus LX570\n\
			Mercedes AMG GT63\n\
			Land Cruiser 200\n\
			BMW X5M\n\
			BMW M5 F90\n\
			Audi R8\n\
			BMW M4 F82\n\
			Jeep Grand Cherokee\n\
			BMW M5 E60\n\n");
		}
		case 726:
		{
			strcat(STRING_MIN, "\
			Mercedes G63 AMG 6x6\n\
			Rolls-Royce Phantom\n\
			Ferrari Pista 488\n\
			McLaren 720s\n\
			Bugatti Chiron\n\
			Porsche Panamero Turbo\n\
			McLaren 600LT\n\
			Bentley Continental\n\
			Bentley Bentayga\n\
			Aston Martin Vantage\n\
			Mercedes G63\n\
			Mercedes-Maybach\n\
			BMW M8\n\
			Range Rover SVR\n\
			Lexus LC\n\n");
		}
		case 727:
		{
			strcat(STRING_MIN, "\
			ПНВ # 1\n\
			ПНВ # 2\n\
			Карлсон\n\
			Нимб\n\
			Крылья\n\
			Бронежилет S. W. A. T\n\
			Полицейский щит\n\
			Попугай\n\
			Петух\n\
			Чемодан Rockstar\n\
			Шляпа цилиндр\n\
			Шляпа волшебника\n\
			Кейс\n\
			Красный кейс\n\
			Голова CJ\n\n");
		}
		case 728:
		{
			strcat(STRING_MIN, "\
			ID: 125 - vmaff2\n\
			ID: 113 - mafboss\n\
			ID: 288 - dsher\n\
			ID: 287 - army\n\
			ID: 286 - fbi\n\
			ID: 285 - swat\n\
			ID: 283 - csher\n\
			ID: 261 - wmycd1\n\
			ID: 240 - swmyri\n\
			ID: 165 - wmomib\n\
			ID: 70 - wmosci\n\
			ID: 61 - wmyplt\n\
			ID: 120 - triboss\n\
			ID: 62 - wmopj\n\
			ID: 49 - omokung\n\
			ID: 277 - lafd1\n\
			ID: 278 - lvfd1\n\
			ID: 279 - sffd1\n\n");
		}
	}
	strcat(STRING_MIN, "\
	Список основных наград:\n\n\
	\t— ADD VIP на 30 дней\n\
	\t— Premium на транспортное средство\n\
	\t— Premium на аксессуар\n\
	\t— Premium на скин\n\
	\t— Battle Pass Premium\n\
	\t— ускоритель опыта Battle Pass\n\
	\t— бронзовые рулетки\n\
	\t— серебряные рулетки\n\
	\t— золотые рулетки\n\
	\t— денежные средства\n\
	\t— очки опыта\n\
	\t— аптечка");
	return STRING_MIN;
}

OnPlayerOpenCasket(playerid, idx)
{
	new prize_name[64], max_random = 9990, price = ItemsInfo[idx][iPrice];
	if(((p_info[playerid][p_vip] == 3 && p_info[playerid][level] >= 100) || p_info[playerid][p_add_vip] == 1) && totalcasket[0] < MAX_CASKET_DAY && totalcasket[3] < MAX_CASKET_PAYDAY)
	{
		switch(price)
		{
			case 25000: max_random = 9992;
			case 50000: max_random = 9994;
			case 75000: max_random = 9996;
			case 100000: max_random = 9998;
			case 150000: max_random = 10000;
		}
	}
	switch(random(max_random))
	{
		case 0 .. 9989:
		{
			max_random = 9980;

			if((p_info[playerid][p_vip] == 3 && p_info[playerid][level] >= 50) || p_info[playerid][p_add_vip] == 1 && totalcasket[1] < MAX_CASKET_MED_PAYDAY)
			{
				switch(price)
				{
					case 25000: max_random = 9984;
					case 50000: max_random = 9988;
					case 75000: max_random = 9992;
					case 100000: max_random = 9996;
					case 150000: max_random = 10000;
				}
			}

			switch(random(max_random))
			{
				case 0 .. 2999: // Денежные средства;
				{
					new count = RandomEx(7500, 15000);
					f(prize_name, "%d$", count);
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_MONEY, count);
				}
				case 3000 .. 6999: // Аптечка;
				{
					new count = RandomEx(5, 10);
					f(prize_name, "Аптечка: %d шт", count);
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, count, 632);
				}
				case 7000 .. 8999: // Очки опыта;
				{
					new count = RandomEx(5, 10);
					f(prize_name, "Очки опыта: %d шт", count);
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_EXP, count);
				}
				case 9000 .. 9979: // Bronze рулетка;
				{
					prize_name = "Bronze рулетка";
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 642);
				}
				default:
				{
					switch(random(241))
					{
						case 0 .. 99:
						{
							prize_name = "Premium на скин";
							SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 737);
						}
						case 100 .. 149:
						{
							prize_name = "Premium на аксессуар";
							SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 729);
						}
						case 150 .. 189: // Ускоритель опыта Battle Pass;
						{
							prize_name = "Ускоритель опыта Battle Pass";
							SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 731);
						}
						case 190 .. 219: // Battle Pass Premium;
						{
							prize_name = "Battle Pass Premium";
							SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 730);
						}
						case 220 .. 239:
						{
							prize_name = "Premium на транспортное средство";
							SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 681);
						}
						default:
						{
							prize_name = "ADD VIP";
							SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, 1, 732);
						}
					}
					totalcasket[1]++;
				}
			}
		}
		default:
		{
			new win_idx = -1;
			switch(idx)
			{
				case 718: // Ларец гос. служащего;
				{
					new prize_idx[] = {4546, 3349, 3201, 3200}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 719: // Нелегальный ларец;
				{
					new prize_idx[] = {3610, 3215, 3870, 3239}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 720: // Ларец новичка;
				{
					new prize_idx[] = {3883, 3784, 3611, 3236}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 721: // Ларец освоившегося;
				{
					new prize_idx[] = {3245, 3974, 3235, 3231}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 722: // Развлекательный ларец;
				{
					new prize_idx[] = {3222, 3248, 3219, 3194}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 723: // Семейный ларец;
				{
					new prize_idx[] = {3429, 3217, 3235, 3231, 3227}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 724: // Start Car Box;
				{
					new prize_idx[] = {3199, 3202, 3254, 3234, 3218, 4763, 3195, 3883, 3784, 3611, 4766, 4764, 3236}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 725: // Medium Car Box;
				{
					new prize_idx[] = {3245, 3974, 3217, 3247, 3235, 3205, 3231, 3211, 3208, 3197, 3204, 3227, 3206}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 726: // Super Car Box;
				{
					new prize_idx[] = {3610, 4546, 3222, 3248, 3215, 3349, 3219, 3201, 3200, 3194, 3870, 3239, 3210, 3429, 3233}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_VEHICLE, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 727: // Ларец с аксессуарами;
				{
					new prize_idx[] = {558, 559, 626, 586, 587, 445, 512, 464, 576, 438, 455, 454, 465, 513, 555}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_ACCESSORIES, prize_idx[x]);
					win_idx = prize_idx[x];
				}
				case 728: // Ларец со скинами;
				{
					new prize_idx[] = {125, 113, 288, 287, 286, 285, 283, 261, 240, 165, 70, 61, 120, 62, 49, 277, 278, 279}, x = random(sizeof(prize_idx));
					SetPlayerItem(playerid, 11, p_info[playerid][ID], TYPE_GIVE_ITEM_U_SKIN, prize_idx[x]);
					win_idx = prize_idx[x];
				}
			}
			if(idx == 727 || idx == 728) f(prize_name, "%s", ItemsInfo[win_idx][iName]);
			else f(prize_name, "%s", GetVehicleName(INVALID_VEHICLE_ID, win_idx));
			SendMesAll(COLOR_LIGHTRED, "[ЛАРЦЫ]: "W"%s [%d] открыл(-а) \"%s\" и выиграл \"%s\".", get_name(playerid), playerid, ItemsInfo[idx][iName], prize_name);
			totalcasket[0]++;
			totalcasket[3]++;
		}
	}
	GivePlayerInventory(playerid, idx, -1);
	return 1;
}

CMD:test_one(playerid, params[])
{
	if(SRV_ID) return 1;
	GivePlayerCasket(playerid, -1);
	return 1;
}

GetPlayerGiveCasket(idx, i)
{
	if(totalcasket[2] == MAX_GIVE_PAYDAY_CASKET) return -1;
	if(random(idx) < i)
	{
		totalcasket[2]++;
		return 1;
	}
	return -1;
}