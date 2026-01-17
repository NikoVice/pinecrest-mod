new Text:RouletteOther[55];
new Text:RouletteButton[6];
new PlayerText:RouletteItems[MAX_PLAYERS][16];
new PlayerText:RouletteItemsCount[MAX_PLAYERS][16];
new PlayerText:RouletteInfo[MAX_PLAYERS][3];

new RouletteTimer[MAX_PLAYERS]; // Таймер обновления;
new bool:RouletteTimerStart[MAX_PLAYERS]; // Статус старта таймера;
new bool:RouletteTimerEnd[MAX_PLAYERS]; // Статус завершения таймера;
new RouletteTimerIDx[MAX_PLAYERS]; // ID таймера;
new RoulettePosition[MAX_PLAYERS]; // ID ячейки, которая меняет цвет;
new RouletteWinIDx[MAX_PLAYERS]; // ID ячейки, которая должна выпасть;
new RouletteType[MAX_PLAYERS]; // Тип рулетки;

new RoulettePlayerItems[MAX_PLAYERS][3][16]; // Предметы игрока в рулетке;
new RoulettePlayerItemsCount[MAX_PLAYERS][3][16]; // Количество предметов игрока в рулетке;
new RoulettePlayerItemsIDx[MAX_PLAYERS][3][16]; // Доп. параметр предметов игрока в рулетке;

new RouletteSpin[3]; // Кол-во вращений;
new RouletteSpinCount[3]; // Кол-во вращений которые не обнуляется;

new RouletteStats[3][13]; // Статистика;

new RoulettePrice[3] = {250, 500, 1000}; // Стоимость рулетки;
new RoulettePriceUpdate[3] = {10, 25, 50}; // Стоимость обновления рулетки;

enum
{
	TYPE_ROULETTE_BRONZE,
	TYPE_ROULETTE_SILVER,
	TYPE_ROULETTE_GOLD
}

new RouletteNameType[3][12] = {"Bronze", "Silver", "Gold"};

GetNameRouletteWinItemsName(playerid)
{
	new idx = RouletteWinIDx[playerid], type = RouletteType[playerid], type_prize = RoulettePlayerItems[playerid][type][idx];
	switch(type_prize)
	{
		case TYPE_GIVE_ITEM_EXP, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY, TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
		{
			RouletteStats[type][RoulettePlayerItems[playerid][type][idx]] += RoulettePlayerItemsCount[playerid][type][idx];
			SetPlayerItem(playerid, 0, p_info[playerid][ID], RoulettePlayerItems[playerid][type][idx], RoulettePlayerItemsCount[playerid][type][idx]);
		}
		case TYPE_GIVE_ITEM_INVENTORY:
		{
			RouletteStats[type][TYPE_GIVE_ITEM_INVENTORY] += RoulettePlayerItemsCount[playerid][type][idx];
			SetPlayerItem(playerid, 0, p_info[playerid][ID], TYPE_GIVE_ITEM_INVENTORY, RoulettePlayerItemsCount[playerid][type][idx], RoulettePlayerItemsIDx[playerid][type][idx]);
		}
		case TYPE_GIVE_ITEM_ACCESSORIES:
		{
			RouletteStats[type][TYPE_GIVE_ITEM_ACCESSORIES] += ItemsInfo[RoulettePlayerItemsCount[playerid][type][idx]][iPrice]/6;
			SetPlayerItem(playerid, 0, p_info[playerid][ID], TYPE_GIVE_ITEM_ACCESSORIES, RoulettePlayerItemsCount[playerid][type][idx], .price = ItemsInfo[RoulettePlayerItemsCount[playerid][type][idx]][iPrice]/8000);
		}
		case TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
		{
			RouletteStats[type][RoulettePlayerItems[playerid][type][idx]] += ItemsInfo[RoulettePlayerItemsCount[playerid][type][idx]][iPrice] / 6;
			SetPlayerItem(playerid, 0, p_info[playerid][ID], RoulettePlayerItems[playerid][type][idx], RoulettePlayerItemsCount[playerid][type][idx], .price = ItemsInfo[RoulettePlayerItemsCount[playerid][type][idx]][iPrice]/8000);
		}
		case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
		{
			RouletteStats[type][RoulettePlayerItems[playerid][type][idx]] += GetVehicleData(RoulettePlayerItemsCount[playerid][type][idx], E_VD_PRICE) / 2;
			SetPlayerItem(playerid, 0, p_info[playerid][ID], RoulettePlayerItems[playerid][type][idx], RoulettePlayerItemsCount[playerid][type][idx], 0, 0);
		}
	}
	SaveRouletteStats(type);
	new str[256];
	format(str, sizeof(str), "%s", GetPrizeItemsName(RoulettePlayerItems[playerid][type][idx], RoulettePlayerItemsCount[playerid][type][idx], RoulettePlayerItemsIDx[playerid][type][idx]));
	if(type_prize == TYPE_GIVE_ITEM_U_MONEY || type_prize == TYPE_GIVE_ITEM_U_DONATE || type_prize == TYPE_GIVE_ITEM_U_SKIN || type_prize == TYPE_GIVE_ITEM_U_VEHICLE) SendMesAll(COLOR_LIGHTRED, "[РУЛЕТКА]: "W"%s [%d] выиграл %s.", get_name(playerid), playerid, str);
	return str;
}

ClearPlayerRouletteTextDraw(playerid, type = 0)
{
	if(type == 1)
	{
		p_temp[playerid][TextDrawRoulette] = false;
		RouletteType[playerid] = -1;
	}
	RouletteTimer[playerid] = 0;
	RouletteTimerStart[playerid] = false;
	RouletteTimerEnd[playerid] = false;
	if(RouletteTimerIDx[playerid] != 0 || IsValidTimer(RouletteTimerIDx[playerid])) KillTimer(RouletteTimerIDx[playerid]);
	RouletteTimerIDx[playerid] = 0;
	RoulettePosition[playerid] = -1;
	RouletteWinIDx[playerid] = -1;
	return 1;
}

SetPlayerRouletteItems(playerid, type)
{
	new
		max_count_prize[3][11] = {
			{2, 4, 1, 1, 1, 2, 1, 2, 0, 2, 0},
			{2, 4, 1, 1, 1, 2, 1, 2, 1, 2, 0},
			{1, 2, 1, 1, 1, 2, 2, 2, 1, 2, 1}
		},
		count_prize[11],
		check_count,
		idx,
		check
	;
	while(check_count < 16)
	{
		idx = random(11);
		if(count_prize[idx] != max_count_prize[type][idx])
		{
			SetPlayerRouletteItemsIDx(playerid, type, check, idx + 1);
			count_prize[idx]++;
			check_count++;
			check++;
		}
	}
	SavePlayerRouletteItems(playerid, type);
	return 1;
}

SetPlayerRouletteItemsIDx(playerid, type, idx, prize)
{
	RoulettePlayerItems[playerid][type][idx] = prize;
	switch(RoulettePlayerItems[playerid][type][idx])
	{
		case TYPE_GIVE_ITEM_EXP:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(1, 3);
				case TYPE_ROULETTE_SILVER: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(3, 5);
				case TYPE_ROULETTE_GOLD: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(5, 7);
			}
		}
		case TYPE_GIVE_ITEM_MONEY:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(5000, 10000);
				case TYPE_ROULETTE_SILVER: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(50000, 150000);
				case TYPE_ROULETTE_GOLD: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(150000, 300000);
			}
		}
		case TYPE_GIVE_ITEM_U_MONEY:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: RoulettePlayerItemsCount[playerid][type][idx] = 2500000;
				case TYPE_ROULETTE_SILVER: RoulettePlayerItemsCount[playerid][type][idx] = 5000000;
				case TYPE_ROULETTE_GOLD: RoulettePlayerItemsCount[playerid][type][idx] = 10000000;
			}
		}
		case TYPE_GIVE_ITEM_DONATE:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(1, 3);
				case TYPE_ROULETTE_SILVER: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(25, 50);
				case TYPE_ROULETTE_GOLD: RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(50, 75);
			}
		}
		case TYPE_GIVE_ITEM_U_DONATE:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: RoulettePlayerItemsCount[playerid][type][idx] = 2500;
				case TYPE_ROULETTE_SILVER: RoulettePlayerItemsCount[playerid][type][idx] = 5000;
				case TYPE_ROULETTE_GOLD: RoulettePlayerItemsCount[playerid][type][idx] = 10000;
			}
		}
		case TYPE_GIVE_ITEM_INVENTORY:
		{
            new prize_id[7] = {647, 648, 649, 650, 651, 641, 645},
                check_idx = random(7);
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE:
				{
					new prize_count[7][2] = {{1, 3}, {1, 3}, {1, 3}, {1, 3}, {1, 3}, {1, 3}, {1, 3}};

					RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(prize_count[check_idx][0], prize_count[check_idx][1]);
					RoulettePlayerItemsIDx[playerid][type][idx] = prize_id[check_idx];
				}
				case TYPE_ROULETTE_SILVER:
				{
					new prize_count[7][2] = {{5, 10}, {5, 10}, {5, 10}, {5, 10}, {5, 10}, {5, 10}, {5, 10}};

					RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(prize_count[check_idx][0], prize_count[check_idx][1]);
					RoulettePlayerItemsIDx[playerid][type][idx] = prize_id[check_idx];
				}
				case TYPE_ROULETTE_GOLD:
				{
					new prize_count[7][2] = {{10, 15}, {10, 15}, {10, 15}, {10, 15}, {10, 15}, {10, 15}, {10, 15}};

					RoulettePlayerItemsCount[playerid][type][idx] = RandomEx(prize_count[check_idx][0], prize_count[check_idx][1]);
					RoulettePlayerItemsIDx[playerid][type][idx] = prize_id[check_idx];
				}
			}
		}
		case TYPE_GIVE_ITEM_ACCESSORIES:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE:
				{
					new accessories_roulette_prize[29] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585, 596, 598, 599, 600, 601, 602, 603, 607}; // 250000$;
					RoulettePlayerItemsCount[playerid][type][idx] = accessories_roulette_prize[random(sizeof(accessories_roulette_prize))];
				}
				case TYPE_ROULETTE_SILVER:
				{
					new accessories_roulette_prize[79] = {440, 441, 442, 446, 447, 448, 449, 450, 466, 467, 468, 469, 470, 471, 473, 474, 483, 487, 488, 494, 495, 496, 499, 502, 503, 514, 518, 522, 524, 526, 531, 532, 533, 535, 536, 538, 539, 550, 551, 552, 553, 554, 557, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 580, 581, 582, 583, 584, 589, 590, 591, 592, 593, 594, 595, 604, 608, 611, 612, 615, 617, 619, 621, 622, 623, 624}; // 500000$;
					RoulettePlayerItemsCount[playerid][type][idx] = accessories_roulette_prize[random(sizeof(accessories_roulette_prize))];
				}
				case TYPE_ROULETTE_GOLD:
				{
					new accessories_roulette_prize[68] = {438, 439, 443, 444, 445, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 472, 475, 486, 497, 498, 500, 501, 504, 505, 506, 509, 510, 511, 512, 513, 515, 517, 525, 527, 529, 540, 548, 555, 556, 558, 559, 573, 574, 575, 576, 577, 578, 579, 586, 587, 588, 597, 605, 606, 609, 610, 613, 614, 616, 618, 620, 625, 626}; // От 500000$ до 2000000$;
					RoulettePlayerItemsCount[playerid][type][idx] = accessories_roulette_prize[random(sizeof(accessories_roulette_prize))];
				}
			}
		}
		case TYPE_GIVE_ITEM_SKIN:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE:
				{
					new skin_roulette_prize[17] = {2, 7, 18, 24, 45, 67, 97, 101, 142, 144, 146, 154, 156, 176, 177, 220, 224}; // От 25000$ до 75000$;
					RoulettePlayerItemsCount[playerid][type][idx] = skin_roulette_prize[random(sizeof(skin_roulette_prize))];
				}
				case TYPE_ROULETTE_SILVER:
				{
					new skin_roulette_prize[8] = {28, 60, 170, 180, 183, 184, 273, 298}; // От 75000$ до 125000$;
					RoulettePlayerItemsCount[playerid][type][idx] = skin_roulette_prize[random(sizeof(skin_roulette_prize))];
				}
				case TYPE_ROULETTE_GOLD:
				{
					new skin_roulette_prize[32] = {17, 19, 21, 22, 23, 29, 30, 33, 46, 47, 48, 76, 82, 83, 84, 91, 185, 214, 219, 228, 241, 242, 249, 289, 291, 292, 293, 294, 295, 296, 297, 299}; // От 125000$ до 645000$;
					RoulettePlayerItemsCount[playerid][type][idx] = skin_roulette_prize[random(sizeof(skin_roulette_prize))];
				}
			}
		}
		case TYPE_GIVE_ITEM_U_SKIN:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: return 1;
				case TYPE_ROULETTE_SILVER:
				{
					new skin_roulette_prize[15] = {1, 41, 42, 66, 90, 128, 132, 133, 157, 159, 201, 202, 206, 210, 234};
					RoulettePlayerItemsCount[playerid][type][idx] = skin_roulette_prize[random(sizeof(skin_roulette_prize))];
				}
				case TYPE_ROULETTE_GOLD:
				{
					new skin_roulette_prize[] = {11, 12, 16, 20, 26, 27, 32, 34, 35, 40, 43, 44, 50, 51, 52, 56, 57, 59, 61, 64, 65, 68, 69, 70, 71, 72, 73, 80, 81, 86, 92, 93, 94,
						98, 99, 100, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 131, 141, 143,
						147, 148, 149, 150, 153, 158, 161, 162, 163, 164, 165, 166, 167, 168, 169, 171, 172, 173, 174, 175, 179, 181, 182, 186, 187, 188, 189, 190, 191, 192, 193, 194,
						195, 198, 203, 204, 205, 208, 209, 211, 216, 217, 221, 222, 223, 225, 227, 229, 233, 235, 236, 240, 246, 247, 248, 250, 253, 254, 255, 258, 259, 260, 261, 262,
						263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 290, 300, 301, 302, 303, 304, 305,
						306, 307, 308, 309, 310, 742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761};
					RoulettePlayerItemsCount[playerid][type][idx] = skin_roulette_prize[random(sizeof(skin_roulette_prize))];
				}
			}
		}
		case TYPE_GIVE_ITEM_VEHICLE:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE:
				{
					new vehicle_roulette_prize[40] = {401, 404, 410, 419, 422, 436, 439, 458, 462, 466, 471, 473, 474, 478, 479, 481, 491, 492, 500, 507, 509, 510, 516, 517, 518, 526, 527, 529, 540, 542, 543, 545, 546, 547, 549, 585, 600, 604, 605, 473}; // От 25000$ до 100000$;
					RoulettePlayerItemsCount[playerid][type][idx] = vehicle_roulette_prize[random(sizeof(vehicle_roulette_prize))];
				}
				case TYPE_ROULETTE_SILVER:
				{
					new vehicle_roulette_prize[35] = {400, 405, 412, 418, 421, 426, 445, 467, 468, 475, 482, 489, 496, 505, 533, 534, 535, 536, 550, 551, 554, 555, 558, 562, 565, 566, 567, 575, 576, 579, 586, 587, 589, 602, 603}; // От 100000$ до 250000$;
					RoulettePlayerItemsCount[playerid][type][idx] = vehicle_roulette_prize[random(sizeof(vehicle_roulette_prize))];
				}
				case TYPE_ROULETTE_GOLD:
				{
					new vehicle_roulette_prize[51] = {402, 453, 461, 463, 472, 476, 477, 480, 506, 508, 512, 513, 559, 560, 561, 580, 581, 593, 595, 411, 415, 429, 446, 451, 452, 454, 469, 484, 487, 493, 511, 519, 521, 541, 453, 472, 595, 446, 452, 454, 484, 493, 476, 512, 513, 593, 469, 487, 511, 519, 553}; // От 500000$ до 2500000$;
					RoulettePlayerItemsCount[playerid][type][idx] = vehicle_roulette_prize[random(sizeof(vehicle_roulette_prize))];
				}
			}
		}
		case TYPE_GIVE_ITEM_U_VEHICLE:
		{
			switch(type)
			{
				case TYPE_ROULETTE_BRONZE: return 1;
				case TYPE_ROULETTE_SILVER: return 1;
				case TYPE_ROULETTE_GOLD:
				{
					new vehicle_roulette_prize[31] = {409, 424, 427, 434, 442, 470, 483, 490, 494, 495, 502, 503, 504, 522, 528, 568, 571, 573, 596, 597, 598, 599, 601, 430, 539, 417, 460, 488, 497, 548, 563};
					RoulettePlayerItemsCount[playerid][type][idx] = vehicle_roulette_prize[random(sizeof(vehicle_roulette_prize))];
				}
			}
		}
	}
	return 1;
}

this::ShowPlayerRoulette(playerid, type)
{
	if(ServerInfo[RouletteSystem] == 0) return SendError(playerid, "Рулетка отключена администрацией.");
	if(type < 0 || type > 2) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
    if(IsTDVisible(playerid) != -1) return 1;
    RouletteType[playerid] = type;
    if(p_info[playerid][p_settings][INTERFACE]) return ShowTextDrawForPlayer(playerid, TD_ID_ROULETTE);

	LoadPlayerRouletteTextDraw(playerid);
	ClearPlayerRouletteTextDraw(playerid);

	for(new i = 0; i < 55; i++)
	{
		TextDrawShowForPlayer(playerid, RouletteOther[i]);
		if(i < 16) ShowPlayerRouletteItems(playerid, type, i);
		if(i < 6) TextDrawShowForPlayer(playerid, RouletteButton[i]);
		if(i < 3) PlayerTextDrawShow(playerid, RouletteInfo[playerid][i]);
	}

	p_temp[playerid][TextDrawRoulette] = true;

	UpdatePlayerRouletteInfo(playerid);

	SelectTextDraw(playerid, -11206401);
	return 1;
}

ShowPlayerRouletteItems(playerid, type, idx)
{
	switch(RoulettePlayerItems[playerid][type][idx])
	{
		case TYPE_GIVE_ITEM_EXP:
		{
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], 1277);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], 0.0000, 0.0000, 180.0000, 1.0000);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
			new str[32];
			format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
			PlayerTextDrawSetString(playerid, RouletteItemsCount[playerid][idx], str);
			PlayerTextDrawShow(playerid, RouletteItemsCount[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
		{
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], 1550);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], 0.0000, 0.0000, 0.0000, 1.0000);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
			new str[32];
			format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
			PlayerTextDrawSetString(playerid, RouletteItemsCount[playerid][idx], str);
			PlayerTextDrawShow(playerid, RouletteItemsCount[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
		{
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], 1274);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], 0.0000, 0.0000, 0.0000, 1.0000);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
			new str[32];
			format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
			PlayerTextDrawSetString(playerid, RouletteItemsCount[playerid][idx], str);
			PlayerTextDrawShow(playerid, RouletteItemsCount[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_INVENTORY:
		{
			new i = RoulettePlayerItemsIDx[playerid][type][idx];
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], ItemsInfo[i][iModel]);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
			new str[32];
			format(str, sizeof(str), "%d", RoulettePlayerItemsCount[playerid][type][idx]);
			PlayerTextDrawSetString(playerid, RouletteItemsCount[playerid][idx], str);
			PlayerTextDrawShow(playerid, RouletteItemsCount[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_ACCESSORIES:
		{
			new i = RoulettePlayerItemsCount[playerid][type][idx];
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], ItemsInfo[i][iModel]);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
		{
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], RoulettePlayerItemsCount[playerid][type][idx]);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], 0.0000, 0.0000, 0.0000, 1.2000);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
		{
			PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][idx], RoulettePlayerItemsCount[playerid][type][idx]);
			PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][idx], -45.0000, 0.0000, -45.0000, 1.0000);
			PlayerTextDrawShow(playerid, RouletteItems[playerid][idx]);
		}
	}
	return 1;
}

UpdatePlayerRouletteInfo(playerid)
{
	new str[64], type = RouletteType[playerid];
	if(p_temp[playerid][TextDrawRoulette] == false || type < 0 || type > 2) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента."), HidePlayerRoulette(playerid);
	format(str, sizeof(str), "%d Flin Money", RoulettePriceUpdate[type]);
	PlayerTextDrawSetString(playerid, RouletteInfo[playerid][0], str);
	format(str, sizeof(str), "%d", p_info[playerid][flinmoney]);
	PlayerTextDrawSetString(playerid, RouletteInfo[playerid][1], str);
	format(str, sizeof(str), "%d", GetInventoryAmount(playerid, TRANSFER_ITEMS+type+15));
	PlayerTextDrawSetString(playerid, RouletteInfo[playerid][2], str);
	return 1;
}

GetPlayerRoulettePositionIDx(playerid, type_roulette, type_prize)
{
	new i = -1, idx;
	while(i == -1)
	{
		idx = random(16);
		if(RoulettePlayerItems[playerid][type_roulette][idx] == type_prize)
		{
			i = idx;
			break;
		}
	}
	return idx;
}

GetPlayerRouletteWinIDx(playerid, type)
{
	switch(type)
	{
		case TYPE_ROULETTE_BRONZE:
		{
			RouletteSpin[type]++;
			if(RouletteSpin[type] > 5000) RouletteSpin[type] = 0;

			RouletteSpinCount[type]++;

			SaveRouletteSpin();

			switch(RouletteSpin[type])
			{
				case 2499, 5000:
				{
					if(random(5) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_DONATE);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_MONEY);
				}
				case 500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_ACCESSORIES);
				case 250, 750, 1250, 1750, 2250, 2750, 3250, 3750, 4250, 4750:
				{
					if(random(10) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_VEHICLE);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_SKIN);
				}
				default:
				{
					switch(random(1000))
					{
						case 0 .. 493: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_INVENTORY);
						case 494 .. 988: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_EXP);
						default:
						{
							if(random(10) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_DONATE);
							else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_MONEY);
						}
					}
				}
			}
		}
		case TYPE_ROULETTE_SILVER:
		{
			RouletteSpin[type]++;
			if(RouletteSpin[type] > 500) RouletteSpin[type] = 0;

			RouletteSpinCount[type]++;

			SaveRouletteSpin();

			switch(RouletteSpin[type])
			{
				case 500:
				{
					if(random(3) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_DONATE);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_MONEY);
				}
				case 250: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_SKIN);
				case 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_ACCESSORIES);
				case 20, 60, 100, 140, 180, 220, 260, 300, 340, 380, 420, 460:
				{
					if(random(5) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_VEHICLE);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_SKIN);
				}
				default:
				{
					switch(random(1000))
					{
						case 0 .. 493: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_INVENTORY);
						case 494 .. 988: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_EXP);
						default:
						{
							if(random(5) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_DONATE);
							else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_MONEY);
						}
					}
				}
			}
		}
		case TYPE_ROULETTE_GOLD:
		{
			RouletteSpin[type]++;
			if(RouletteSpin[type] > 1000) RouletteSpin[type] = 0;

			RouletteSpinCount[type]++;

			SaveRouletteSpin();

			switch(RouletteSpin[type])
			{
				case 1000:
				{
					if(random(1) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_DONATE);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_MONEY);
				}
				case 750:
				{
					if(random(3) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_SKIN);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_U_VEHICLE);
				}
				case 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600, 640, 680, 720, 760, 800, 840, 880, 920, 960:
				{
					if(random(3) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_ACCESSORIES);
					else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_VEHICLE);
				}
				case 20, 60, 100, 140, 180, 220, 260, 300, 340, 380, 420, 460, 500, 540, 580, 620, 660, 700, 740, 780, 820, 860, 900, 940, 980: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_SKIN);
				default:
				{
					switch(random(1000))
					{
						case 0 .. 493: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_INVENTORY);
						case 494 .. 988: return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_EXP);
						default:
						{
							if(random(2) == 0) return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_DONATE);
							else return GetPlayerRoulettePositionIDx(playerid, type, TYPE_GIVE_ITEM_MONEY);
						}
					}
				}
			}
		}
	}
	return 1;
}

StartPlayerRoulette(playerid)
{
	if(ServerInfo[RouletteSystem] == 0) return SendError(playerid, "Рулетка отключена администрацией."), HidePlayerRoulette(playerid);
	new type = RouletteType[playerid];
	if(type < 0 || type > 2) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента."), HidePlayerRoulette(playerid);
	if(RouletteTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете запустить рулетку, в данный момент она запущена.");
	if(GetInventoryAmount(playerid, TRANSFER_ITEMS+type+15) == 0)
	{
		SendError(playerid, "У Вас нет %s рулетки.", RouletteNameType[type]);
		HidePlayerRoulette(playerid);
		switch(type)
		{
			case TYPE_ROULETTE_BRONZE:
			{
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
				Введите желаемое кол-во рулеток для приобретения:\n\n\
				Стоимость 1 рулетки: {"#cGREEN"}%d"W" Flin Money", RoulettePrice[0]);
				ShowPlayerDialog(playerid, D_ROULETTE_BRONZE_BUY, DIALOG_STYLE_INPUT, ""I"Bronze рулетка", STRING_GLOBAL, "Далее", "Отмена");
			}
			case TYPE_ROULETTE_SILVER:
			{
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
				Введите желаемое кол-во рулеток для приобретения:\n\n\
				Стоимость 1 рулетки: {"#cGREEN"}%d"W" Flin Money", RoulettePrice[1]);
				ShowPlayerDialog(playerid, D_ROULETTE_SILVER_BUY, DIALOG_STYLE_INPUT, ""I"Silver рулетка", STRING_GLOBAL, "Далее", "Отмена");
			}
			case TYPE_ROULETTE_GOLD:
			{
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
				Введите желаемое кол-во рулеток для приобретения:\n\n\
				Стоимость 1 рулетки: {"#cGREEN"}%d"W" Flin Money", RoulettePrice[2]);
				ShowPlayerDialog(playerid, D_ROULETTE_GOLD_BUY, DIALOG_STYLE_INPUT, ""I"Gold рулетка", STRING_GLOBAL, "Далее", "Отмена");
			}
		}
		return 1;
	}
	GivePlayerInventory(playerid, TRANSFER_ITEMS+type+15, -1);

	if(p_info[playerid][p_settings][INTERFACE]) Roulette_UpdateTD_Info(playerid, type);
    else UpdatePlayerRouletteInfo(playerid);
	new rand = 16 * RandomEx(2, 5), idx = GetPlayerRouletteWinIDx(playerid, type) + rand;
	RouletteTimer[playerid] = idx + 1;
	RouletteTimerStart[playerid] = true;
	RouletteTimerEnd[playerid] = false;
	RoulettePosition[playerid] = 0;
	RouletteWinIDx[playerid] = idx - rand;
	RouletteTimerIDx[playerid] = SetTimerEx("CheckPlayerRoulette", 100, true, "i", playerid);
	return 1;
}

forward CheckPlayerRoulette(playerid);
public CheckPlayerRoulette(playerid)
{
	if(RouletteTimerIDx[playerid] == 0) return 1;
	if(p_temp[playerid][TextDrawRoulette] == true || p_temp[playerid][TextDrawRoulette] == true)
	{
		if(RouletteTimer[playerid] > 0)
		{
			RouletteTimer[playerid]--;

			if(RouletteTimerEnd[playerid] == false)
			{
				if(RouletteTimerStart[playerid] == false)
				{
					if(RoulettePosition[playerid] - 1 < 0)
					{
                        if(p_info[playerid][p_settings][INTERFACE]) Roulette_UpdateTD_ItemBG(playerid, 25, "flin_roulette:flin_roulette_slot");
                        else {
                            PlayerTextDrawHide(playerid, RouletteItems[playerid][15]);
                            PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][15], 168430335);
                            PlayerTextDrawShow(playerid, RouletteItems[playerid][15]);
                        }
                    }
                    else
                    {
                        if(p_info[playerid][p_settings][INTERFACE]) Roulette_UpdateTD_ItemBG(playerid, 10+RoulettePosition[playerid]-1, "flin_roulette:flin_roulette_slot");
                        else {
                            PlayerTextDrawHide(playerid, RouletteItems[playerid][RoulettePosition[playerid]-1]);
                            PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][RoulettePosition[playerid]-1], 168430335);
                            PlayerTextDrawShow(playerid, RouletteItems[playerid][RoulettePosition[playerid]-1]);
                        }
                    }
                }

				if(RouletteTimerStart[playerid] == true) RouletteTimerStart[playerid] = false;

                if(p_info[playerid][p_settings][INTERFACE]) Roulette_UpdateTD_ItemBG(playerid, 10+RoulettePosition[playerid], "flin_roulette:flin_roulette_slot_use");
                else {
                    PlayerTextDrawHide(playerid, RouletteItems[playerid][RoulettePosition[playerid]]);
                    PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][RoulettePosition[playerid]], -25287937);
                    PlayerTextDrawShow(playerid, RouletteItems[playerid][RoulettePosition[playerid]]);
                }

				RoulettePosition[playerid]++;
				if(RoulettePosition[playerid] == 16) RoulettePosition[playerid] = 0;

				if(RouletteTimer[playerid] == 0)
				{
					RouletteTimer[playerid] = 3;
					RouletteTimerEnd[playerid] = true;

					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
					Вы выиграли: "I"%s", GetNameRouletteWinItemsName(playerid));
					ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Приз", STRING_GLOBAL, "ОК", "");
				}
			}
			else
			{
				if(RouletteTimer[playerid] == 0)
				{
					if(RoulettePosition[playerid] - 1 < 0)
					{
						if(p_info[playerid][p_settings][INTERFACE]) Roulette_UpdateTD_ItemBG(playerid, 25, "flin_roulette:flin_roulette_slot");
                        else {
                            PlayerTextDrawHide(playerid, RouletteItems[playerid][15]);
                            PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][15], 168430335);
                            PlayerTextDrawShow(playerid, RouletteItems[playerid][15]);
                        }
                    }
                    else
                    {
                        if(p_info[playerid][p_settings][INTERFACE]) Roulette_UpdateTD_ItemBG(playerid, 10+RoulettePosition[playerid]-1, "flin_roulette:flin_roulette_slot");
                        else {
                            PlayerTextDrawHide(playerid, RouletteItems[playerid][RoulettePosition[playerid]-1]);
                            PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][RoulettePosition[playerid]-1], 168430335);
                            PlayerTextDrawShow(playerid, RouletteItems[playerid][RoulettePosition[playerid]-1]);
                        }
                    }

					RouletteTimerEnd[playerid] = false;

					KillTimer(RouletteTimerIDx[playerid]);
					RouletteTimerIDx[playerid] = 0;
				}
			}
		}
	}
	return 1;
}

HidePlayerRoulette(playerid)
{
	if(p_info[playerid][p_settings][INTERFACE]) return HideTextDrawForPlayer(playerid, TD_ID_ROULETTE);
	for(new i = 0; i < 55; i++)
	{
		TextDrawHideForPlayer(playerid, RouletteOther[i]);
		if(i < 16)
		{
			if(RouletteItems[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, RouletteItems[playerid][i]);
				RouletteItems[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
			}
			if(RouletteItemsCount[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, RouletteItemsCount[playerid][i]);
				RouletteItemsCount[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
		if(i < 6) TextDrawHideForPlayer(playerid, RouletteButton[i]);
		if(i < 3 && RouletteInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, RouletteInfo[playerid][i]);
			RouletteInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	ClearPlayerRouletteTextDraw(playerid, 1);
	CancelSelectTextDraw(playerid);
	return 1;
}

SaveRouletteSpin()
{
	new string[32];

	format(string, sizeof(string), "%i, %i, %i",
	RouletteSpin[0], RouletteSpin[1], RouletteSpin[2]);
	MysqlUpdateOtherStr("roulette_spin", string);

	format(string, sizeof(string), "%i, %i, %i",
	RouletteSpinCount[0], RouletteSpinCount[1], RouletteSpinCount[2]);
	MysqlUpdateOtherStr("roulette_spin_count", string);
	return 1;
}

SaveRouletteStats(type)
{
	new string[256], mysql_name[3][24] = {"roulette_stats_bronze", "roulette_stats_silver", "roulette_stats_gold"};

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	RouletteStats[type][0], RouletteStats[type][1], RouletteStats[type][2], RouletteStats[type][3], RouletteStats[type][4], RouletteStats[type][5],
	RouletteStats[type][6], RouletteStats[type][7], RouletteStats[type][8], RouletteStats[type][9], RouletteStats[type][10], RouletteStats[type][11],
	RouletteStats[type][12]);
	MysqlUpdateOtherStr(mysql_name[type], string);
	return 1;
}

CheckPlayerRouletteItems(playerid)
{
	for(new idx = 0; idx < 3; idx++)
	{
		for(new i = 0; i < 16; i++)
		{
			if(RoulettePlayerItems[playerid][idx][i] == 0)
			{
				SetPlayerRouletteItems(playerid, idx);
				break;
			}
		}
	}
	return 1;
}

SavePlayerRouletteItems(playerid, type)
{
	new
		string[256],
		mysql_name_items[3][32] = {"roulette_items_bronze", "roulette_items_silver", "roulette_items_gold"},
		mysql_name_items_count[3][32] = {"roulette_items_count_bronze", "roulette_items_count_silver", "roulette_items_count_gold"},
		mysql_name_items_idx[3][32] = {"roulette_items_idx_bronze", "roulette_items_idx_silver", "roulette_items_idx_gold"}
	;

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	RoulettePlayerItems[playerid][type][0], RoulettePlayerItems[playerid][type][1], RoulettePlayerItems[playerid][type][2], RoulettePlayerItems[playerid][type][3], RoulettePlayerItems[playerid][type][4], RoulettePlayerItems[playerid][type][5], RoulettePlayerItems[playerid][type][6], RoulettePlayerItems[playerid][type][7],
	RoulettePlayerItems[playerid][type][8], RoulettePlayerItems[playerid][type][9], RoulettePlayerItems[playerid][type][10], RoulettePlayerItems[playerid][type][11], RoulettePlayerItems[playerid][type][12], RoulettePlayerItems[playerid][type][13], RoulettePlayerItems[playerid][type][14], RoulettePlayerItems[playerid][type][15]);
	MysqlUpdatePlayerStr(playerid, mysql_name_items[type], string);

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	RoulettePlayerItemsCount[playerid][type][0], RoulettePlayerItemsCount[playerid][type][1], RoulettePlayerItemsCount[playerid][type][2], RoulettePlayerItemsCount[playerid][type][3], RoulettePlayerItemsCount[playerid][type][4], RoulettePlayerItemsCount[playerid][type][5], RoulettePlayerItemsCount[playerid][type][6], RoulettePlayerItemsCount[playerid][type][7],
	RoulettePlayerItemsCount[playerid][type][8], RoulettePlayerItemsCount[playerid][type][9], RoulettePlayerItemsCount[playerid][type][10], RoulettePlayerItemsCount[playerid][type][11], RoulettePlayerItemsCount[playerid][type][12], RoulettePlayerItemsCount[playerid][type][13], RoulettePlayerItemsCount[playerid][type][14], RoulettePlayerItemsCount[playerid][type][15]);
	MysqlUpdatePlayerStr(playerid, mysql_name_items_count[type], string);

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	RoulettePlayerItemsIDx[playerid][type][0], RoulettePlayerItemsIDx[playerid][type][1], RoulettePlayerItemsIDx[playerid][type][2], RoulettePlayerItemsIDx[playerid][type][3], RoulettePlayerItemsIDx[playerid][type][4], RoulettePlayerItemsIDx[playerid][type][5], RoulettePlayerItemsIDx[playerid][type][6], RoulettePlayerItemsIDx[playerid][type][7],
	RoulettePlayerItemsIDx[playerid][type][8], RoulettePlayerItemsIDx[playerid][type][9], RoulettePlayerItemsIDx[playerid][type][10], RoulettePlayerItemsIDx[playerid][type][11], RoulettePlayerItemsIDx[playerid][type][12], RoulettePlayerItemsIDx[playerid][type][13], RoulettePlayerItemsIDx[playerid][type][14], RoulettePlayerItemsIDx[playerid][type][15]);
	MysqlUpdatePlayerStr(playerid, mysql_name_items_idx[type], string);
	return 1;
}

LoadRouletteTextDraw()
{
	RouletteOther[0] = TextDrawCreate(225.2494, 114.9029, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[0], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[0], 1);
	TextDrawColor(RouletteOther[0], -25287937);
	TextDrawBackgroundColor(RouletteOther[0], 255);
	TextDrawFont(RouletteOther[0], 4);
	TextDrawSetProportional(RouletteOther[0], 0);
	TextDrawSetShadow(RouletteOther[0], 0);

	RouletteOther[1] = TextDrawCreate(236.2993, 118.2956, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[1], 166.0000, 51.9295);
	TextDrawAlignment(RouletteOther[1], 1);
	TextDrawColor(RouletteOther[1], -25287937);
	TextDrawBackgroundColor(RouletteOther[1], 255);
	TextDrawFont(RouletteOther[1], 4);
	TextDrawSetProportional(RouletteOther[1], 0);
	TextDrawSetShadow(RouletteOther[1], 0);

	RouletteOther[2] = TextDrawCreate(392.4324, 115.0400, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[2], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[2], 1);
	TextDrawColor(RouletteOther[2], -25287937);
	TextDrawBackgroundColor(RouletteOther[2], 255);
	TextDrawFont(RouletteOther[2], 4);
	TextDrawSetProportional(RouletteOther[2], 0);
	TextDrawSetShadow(RouletteOther[2], 0);

	RouletteOther[3] = TextDrawCreate(228.3827, 125.0363, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[3], 180.6996, 45.1194);
	TextDrawAlignment(RouletteOther[3], 1);
	TextDrawColor(RouletteOther[3], -25287937);
	TextDrawBackgroundColor(RouletteOther[3], 255);
	TextDrawFont(RouletteOther[3], 4);
	TextDrawSetProportional(RouletteOther[3], 0);
	TextDrawSetShadow(RouletteOther[3], 0);

	RouletteOther[4] = TextDrawCreate(228.6159, 118.9393, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[4], 15.8099, 16.8199);
	TextDrawAlignment(RouletteOther[4], 1);
	TextDrawColor(RouletteOther[4], 336860415);
	TextDrawBackgroundColor(RouletteOther[4], 255);
	TextDrawFont(RouletteOther[4], 4);
	TextDrawSetProportional(RouletteOther[4], 0);
	TextDrawSetShadow(RouletteOther[4], 0);

	RouletteOther[5] = TextDrawCreate(237.7657, 121.8320, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[5], 162.6295, 48.3899);
	TextDrawAlignment(RouletteOther[5], 1);
	TextDrawColor(RouletteOther[5], 336860415);
	TextDrawBackgroundColor(RouletteOther[5], 255);
	TextDrawFont(RouletteOther[5], 4);
	TextDrawSetProportional(RouletteOther[5], 0);
	TextDrawSetShadow(RouletteOther[5], 0);

	RouletteOther[6] = TextDrawCreate(393.8992, 119.0764, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[6], 15.3399, 16.7800);
	TextDrawAlignment(RouletteOther[6], 1);
	TextDrawColor(RouletteOther[6], 336860415);
	TextDrawBackgroundColor(RouletteOther[6], 255);
	TextDrawFont(RouletteOther[6], 4);
	TextDrawSetProportional(RouletteOther[6], 0);
	TextDrawSetShadow(RouletteOther[6], 0);

	RouletteOther[7] = TextDrawCreate(231.2492, 128.6732, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[7], 175.3408, 41.4794);
	TextDrawAlignment(RouletteOther[7], 1);
	TextDrawColor(RouletteOther[7], 336860415);
	TextDrawBackgroundColor(RouletteOther[7], 255);
	TextDrawFont(RouletteOther[7], 4);
	TextDrawSetProportional(RouletteOther[7], 0);
	TextDrawSetShadow(RouletteOther[7], 0);

	RouletteOther[8] = TextDrawCreate(145.3663, 170.2290, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[8], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[8], 1);
	TextDrawColor(RouletteOther[8], -25287937);
	TextDrawBackgroundColor(RouletteOther[8], 255);
	TextDrawFont(RouletteOther[8], 4);
	TextDrawSetProportional(RouletteOther[8], 0);
	TextDrawSetShadow(RouletteOther[8], 0);

	RouletteOther[9] = TextDrawCreate(154.7666, 173.5402, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[9], 327.2893, 99.0000);
	TextDrawAlignment(RouletteOther[9], 1);
	TextDrawColor(RouletteOther[9], -25287937);
	TextDrawBackgroundColor(RouletteOther[9], 255);
	TextDrawFont(RouletteOther[9], 4);
	TextDrawSetProportional(RouletteOther[9], 0);
	TextDrawSetShadow(RouletteOther[9], 0);

	RouletteOther[10] = TextDrawCreate(471.8995, 170.4369, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[10], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[10], 1);
	TextDrawColor(RouletteOther[10], -25287937);
	TextDrawBackgroundColor(RouletteOther[10], 255);
	TextDrawFont(RouletteOther[10], 4);
	TextDrawSetProportional(RouletteOther[10], 0);
	TextDrawSetShadow(RouletteOther[10], 0);

	RouletteOther[11] = TextDrawCreate(145.3663, 255.7344, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[11], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[11], 1);
	TextDrawColor(RouletteOther[11], -25287937);
	TextDrawBackgroundColor(RouletteOther[11], 255);
	TextDrawFont(RouletteOther[11], 4);
	TextDrawSetProportional(RouletteOther[11], 0);
	TextDrawSetShadow(RouletteOther[11], 0);

	RouletteOther[12] = TextDrawCreate(471.8995, 255.7420, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[12], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[12], 1);
	TextDrawColor(RouletteOther[12], -25287937);
	TextDrawBackgroundColor(RouletteOther[12], 255);
	TextDrawFont(RouletteOther[12], 4);
	TextDrawSetProportional(RouletteOther[12], 0);
	TextDrawSetShadow(RouletteOther[12], 0);

	RouletteOther[13] = TextDrawCreate(148.6165, 180.4440, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[13], 340.0899, 84.6203);
	TextDrawAlignment(RouletteOther[13], 1);
	TextDrawColor(RouletteOther[13], -25287937);
	TextDrawBackgroundColor(RouletteOther[13], 255);
	TextDrawFont(RouletteOther[13], 4);
	TextDrawSetProportional(RouletteOther[13], 0);
	TextDrawSetShadow(RouletteOther[13], 0);

	RouletteOther[14] = TextDrawCreate(149.0330, 174.2588, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[14], 14.5895, 16.2199);
	TextDrawAlignment(RouletteOther[14], 1);
	TextDrawColor(RouletteOther[14], 336860415);
	TextDrawBackgroundColor(RouletteOther[14], 255);
	TextDrawFont(RouletteOther[14], 4);
	TextDrawSetProportional(RouletteOther[14], 0);
	TextDrawSetShadow(RouletteOther[14], 0);

	RouletteOther[15] = TextDrawCreate(157.5332, 176.7698, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[15], 321.8739, 92.3283);
	TextDrawAlignment(RouletteOther[15], 1);
	TextDrawColor(RouletteOther[15], 336860415);
	TextDrawBackgroundColor(RouletteOther[15], 255);
	TextDrawFont(RouletteOther[15], 4);
	TextDrawSetProportional(RouletteOther[15], 0);
	TextDrawSetShadow(RouletteOther[15], 0);

	RouletteOther[16] = TextDrawCreate(472.7662, 174.0664, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[16], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[16], 1);
	TextDrawColor(RouletteOther[16], 336860415);
	TextDrawBackgroundColor(RouletteOther[16], 255);
	TextDrawFont(RouletteOther[16], 4);
	TextDrawSetProportional(RouletteOther[16], 0);
	TextDrawSetShadow(RouletteOther[16], 0);

	RouletteOther[17] = TextDrawCreate(148.9331, 254.3191, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[17], 15.2594, 17.8397);
	TextDrawAlignment(RouletteOther[17], 1);
	TextDrawColor(RouletteOther[17], 336860415);
	TextDrawBackgroundColor(RouletteOther[17], 255);
	TextDrawFont(RouletteOther[17], 4);
	TextDrawSetProportional(RouletteOther[17], 0);
	TextDrawSetShadow(RouletteOther[17], 0);

	RouletteOther[18] = TextDrawCreate(151.3834, 183.6734, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[18], 334.6747, 79.0988);
	TextDrawAlignment(RouletteOther[18], 1);
	TextDrawColor(RouletteOther[18], 336860415);
	TextDrawBackgroundColor(RouletteOther[18], 255);
	TextDrawFont(RouletteOther[18], 4);
	TextDrawSetProportional(RouletteOther[18], 0);
	TextDrawSetShadow(RouletteOther[18], 0);

	RouletteOther[19] = TextDrawCreate(472.7662, 254.8713, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[19], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[19], 1);
	TextDrawColor(RouletteOther[19], 336860415);
	TextDrawBackgroundColor(RouletteOther[19], 255);
	TextDrawFont(RouletteOther[19], 4);
	TextDrawSetProportional(RouletteOther[19], 0);
	TextDrawSetShadow(RouletteOther[19], 0);

	RouletteOther[20] = TextDrawCreate(242.7660, 145.4635, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[20], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[20], 1);
	TextDrawColor(RouletteOther[20], -1907281153);
	TextDrawBackgroundColor(RouletteOther[20], 255);
	TextDrawFont(RouletteOther[20], 4);
	TextDrawSetProportional(RouletteOther[20], 0);
	TextDrawSetShadow(RouletteOther[20], 0);

	RouletteOther[21] = TextDrawCreate(251.8168, 148.1510, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[21], 34.0000, 21.8299);
	TextDrawAlignment(RouletteOther[21], 1);
	TextDrawColor(RouletteOther[21], -1907281153);
	TextDrawBackgroundColor(RouletteOther[21], 255);
	TextDrawFont(RouletteOther[21], 4);
	TextDrawSetProportional(RouletteOther[21], 0);
	TextDrawSetShadow(RouletteOther[21], 0);

	RouletteOther[22] = TextDrawCreate(278.4682, 145.4635, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[22], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[22], 1);
	TextDrawColor(RouletteOther[22], -1907281153);
	TextDrawBackgroundColor(RouletteOther[22], 255);
	TextDrawFont(RouletteOther[22], 4);
	TextDrawSetProportional(RouletteOther[22], 0);
	TextDrawSetShadow(RouletteOther[22], 0);

	RouletteOther[23] = TextDrawCreate(245.4331, 153.0773, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[23], 46.4095, 17.0200);
	TextDrawAlignment(RouletteOther[23], 1);
	TextDrawColor(RouletteOther[23], -1907281153);
	TextDrawBackgroundColor(RouletteOther[23], 255);
	TextDrawFont(RouletteOther[23], 4);
	TextDrawSetProportional(RouletteOther[23], 0);
	TextDrawSetShadow(RouletteOther[23], 0);

	RouletteOther[24] = TextDrawCreate(293.1690, 145.4635, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[24], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[24], 1);
	TextDrawColor(RouletteOther[24], -1448498689);
	TextDrawBackgroundColor(RouletteOther[24], 255);
	TextDrawFont(RouletteOther[24], 4);
	TextDrawSetProportional(RouletteOther[24], 0);
	TextDrawSetShadow(RouletteOther[24], 0);

	RouletteOther[25] = TextDrawCreate(302.2199, 148.1510, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[25], 34.0000, 21.8299);
	TextDrawAlignment(RouletteOther[25], 1);
	TextDrawColor(RouletteOther[25], -1448498689);
	TextDrawBackgroundColor(RouletteOther[25], 255);
	TextDrawFont(RouletteOther[25], 4);
	TextDrawSetProportional(RouletteOther[25], 0);
	TextDrawSetShadow(RouletteOther[25], 0);

	RouletteOther[26] = TextDrawCreate(328.8713, 145.4635, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[26], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[26], 1);
	TextDrawColor(RouletteOther[26], -1448498689);
	TextDrawBackgroundColor(RouletteOther[26], 255);
	TextDrawFont(RouletteOther[26], 4);
	TextDrawSetProportional(RouletteOther[26], 0);
	TextDrawSetShadow(RouletteOther[26], 0);

	RouletteOther[27] = TextDrawCreate(295.8359, 153.0773, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[27], 46.4095, 17.0200);
	TextDrawAlignment(RouletteOther[27], 1);
	TextDrawColor(RouletteOther[27], -1448498689);
	TextDrawBackgroundColor(RouletteOther[27], 255);
	TextDrawFont(RouletteOther[27], 4);
	TextDrawSetProportional(RouletteOther[27], 0);
	TextDrawSetShadow(RouletteOther[27], 0);

	RouletteOther[28] = TextDrawCreate(343.3721, 145.4635, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[28], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[28], 1);
	TextDrawColor(RouletteOther[28], -22740737);
	TextDrawBackgroundColor(RouletteOther[28], 255);
	TextDrawFont(RouletteOther[28], 4);
	TextDrawSetProportional(RouletteOther[28], 0);
	TextDrawSetShadow(RouletteOther[28], 0);

	RouletteOther[29] = TextDrawCreate(352.4229, 148.1510, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[29], 34.0000, 21.8299);
	TextDrawAlignment(RouletteOther[29], 1);
	TextDrawColor(RouletteOther[29], -22740737);
	TextDrawBackgroundColor(RouletteOther[29], 255);
	TextDrawFont(RouletteOther[29], 4);
	TextDrawSetProportional(RouletteOther[29], 0);
	TextDrawSetShadow(RouletteOther[29], 0);

	RouletteOther[30] = TextDrawCreate(379.0744, 145.4635, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[30], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[30], 1);
	TextDrawColor(RouletteOther[30], -22740737);
	TextDrawBackgroundColor(RouletteOther[30], 255);
	TextDrawFont(RouletteOther[30], 4);
	TextDrawSetProportional(RouletteOther[30], 0);
	TextDrawSetShadow(RouletteOther[30], 0);

	RouletteOther[31] = TextDrawCreate(346.0392, 153.0773, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[31], 46.4095, 17.0200);
	TextDrawAlignment(RouletteOther[31], 1);
	TextDrawColor(RouletteOther[31], -22740737);
	TextDrawBackgroundColor(RouletteOther[31], 255);
	TextDrawFont(RouletteOther[31], 4);
	TextDrawSetProportional(RouletteOther[31], 0);
	TextDrawSetShadow(RouletteOther[31], 0);

	RouletteOther[32] = TextDrawCreate(319.6863, 126.7276, "ROULETTE");
	TextDrawLetterSize(RouletteOther[32], 0.2581, 1.6000);
	TextDrawAlignment(RouletteOther[32], 2);
	TextDrawColor(RouletteOther[32], -1);
	TextDrawBackgroundColor(RouletteOther[32], 255);
	TextDrawFont(RouletteOther[32], 2);
	TextDrawSetProportional(RouletteOther[32], 1);
	TextDrawSetShadow(RouletteOther[32], 0);

	RouletteOther[33] = TextDrawCreate(285.8840, 126.1277, "0");
	TextDrawLetterSize(RouletteOther[33], 0.3125, 1.7299);
	TextDrawAlignment(RouletteOther[33], 2);
	TextDrawColor(RouletteOther[33], -1);
	TextDrawBackgroundColor(RouletteOther[33], 255);
	TextDrawFont(RouletteOther[33], 2);
	TextDrawSetProportional(RouletteOther[33], 1);
	TextDrawSetShadow(RouletteOther[33], 0);

	RouletteOther[34] = TextDrawCreate(353.4883, 126.1277, "0");
	TextDrawLetterSize(RouletteOther[34], 0.3125, 1.7299);
	TextDrawAlignment(RouletteOther[34], 2);
	TextDrawColor(RouletteOther[34], -1);
	TextDrawBackgroundColor(RouletteOther[34], 255);
	TextDrawFont(RouletteOther[34], 2);
	TextDrawSetProportional(RouletteOther[34], 1);
	TextDrawSetShadow(RouletteOther[34], 0);

	RouletteOther[35] = TextDrawCreate(284.2839, 129.8650, ":");
	TextDrawLetterSize(RouletteOther[35], 0.1479, 0.8899);
	TextDrawAlignment(RouletteOther[35], 2);
	TextDrawColor(RouletteOther[35], -1);
	TextDrawBackgroundColor(RouletteOther[35], 255);
	TextDrawFont(RouletteOther[35], 2);
	TextDrawSetProportional(RouletteOther[35], 1);
	TextDrawSetShadow(RouletteOther[35], 0);

	RouletteOther[36] = TextDrawCreate(285.8840, 129.7834, ":");
	TextDrawLetterSize(RouletteOther[36], 0.1479, 0.8899);
	TextDrawAlignment(RouletteOther[36], 2);
	TextDrawColor(RouletteOther[36], -1);
	TextDrawBackgroundColor(RouletteOther[36], 255);
	TextDrawFont(RouletteOther[36], 2);
	TextDrawSetProportional(RouletteOther[36], 1);
	TextDrawSetShadow(RouletteOther[36], 0);

	RouletteOther[37] = TextDrawCreate(352.8883, 124.1724, ".");
	TextDrawLetterSize(RouletteOther[37], 0.2578, 1.4759);
	TextDrawAlignment(RouletteOther[37], 2);
	TextDrawColor(RouletteOther[37], -1);
	TextDrawBackgroundColor(RouletteOther[37], 255);
	TextDrawFont(RouletteOther[37], 2);
	TextDrawSetProportional(RouletteOther[37], 1);
	TextDrawSetShadow(RouletteOther[37], 0);

	RouletteOther[38] = TextDrawCreate(225.2494, 311.4136, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[38], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[38], 1);
	TextDrawColor(RouletteOther[38], -25287937);
	TextDrawBackgroundColor(RouletteOther[38], 255);
	TextDrawFont(RouletteOther[38], 4);
	TextDrawSetProportional(RouletteOther[38], 0);
	TextDrawSetShadow(RouletteOther[38], 0);

	RouletteOther[39] = TextDrawCreate(236.2993, 276.0043, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[39], 166.0000, 51.9295);
	TextDrawAlignment(RouletteOther[39], 1);
	TextDrawColor(RouletteOther[39], -25287937);
	TextDrawBackgroundColor(RouletteOther[39], 255);
	TextDrawFont(RouletteOther[39], 4);
	TextDrawSetProportional(RouletteOther[39], 0);
	TextDrawSetShadow(RouletteOther[39], 0);

	RouletteOther[40] = TextDrawCreate(392.4324, 311.4511, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[40], 20.0000, 20.0000);
	TextDrawAlignment(RouletteOther[40], 1);
	TextDrawColor(RouletteOther[40], -25287937);
	TextDrawBackgroundColor(RouletteOther[40], 255);
	TextDrawFont(RouletteOther[40], 4);
	TextDrawSetProportional(RouletteOther[40], 0);
	TextDrawSetShadow(RouletteOther[40], 0);

	RouletteOther[41] = TextDrawCreate(228.3827, 275.9450, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[41], 180.6996, 45.1194);
	TextDrawAlignment(RouletteOther[41], 1);
	TextDrawColor(RouletteOther[41], -25287937);
	TextDrawBackgroundColor(RouletteOther[41], 255);
	TextDrawFont(RouletteOther[41], 4);
	TextDrawSetProportional(RouletteOther[41], 0);
	TextDrawSetShadow(RouletteOther[41], 0);

	RouletteOther[42] = TextDrawCreate(228.8495, 310.4136, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[42], 14.3500, 17.1497);
	TextDrawAlignment(RouletteOther[42], 1);
	TextDrawColor(RouletteOther[42], 336860415);
	TextDrawBackgroundColor(RouletteOther[42], 255);
	TextDrawFont(RouletteOther[42], 4);
	TextDrawSetProportional(RouletteOther[42], 0);
	TextDrawSetShadow(RouletteOther[42], 0);

	RouletteOther[43] = TextDrawCreate(237.0324, 276.1044, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[43], 164.5973, 48.5704);
	TextDrawAlignment(RouletteOther[43], 1);
	TextDrawColor(RouletteOther[43], 336860415);
	TextDrawBackgroundColor(RouletteOther[43], 255);
	TextDrawFont(RouletteOther[43], 4);
	TextDrawSetProportional(RouletteOther[43], 0);
	TextDrawSetShadow(RouletteOther[43], 0);

	RouletteOther[44] = TextDrawCreate(394.9324, 309.8507, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[44], 13.8099, 17.5699);
	TextDrawAlignment(RouletteOther[44], 1);
	TextDrawColor(RouletteOther[44], 336860415);
	TextDrawBackgroundColor(RouletteOther[44], 255);
	TextDrawFont(RouletteOther[44], 4);
	TextDrawSetProportional(RouletteOther[44], 0);
	TextDrawSetShadow(RouletteOther[44], 0);

	RouletteOther[45] = TextDrawCreate(231.0827, 275.9632, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[45], 175.3497, 42.5704);
	TextDrawAlignment(RouletteOther[45], 1);
	TextDrawColor(RouletteOther[45], 336860415);
	TextDrawBackgroundColor(RouletteOther[45], 255);
	TextDrawFont(RouletteOther[45], 4);
	TextDrawSetProportional(RouletteOther[45], 0);
	TextDrawSetShadow(RouletteOther[45], 0);

	RouletteOther[46] = TextDrawCreate(293.1690, 283.6718, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[46], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[46], 1);
	TextDrawColor(RouletteOther[46], -25287937);
	TextDrawBackgroundColor(RouletteOther[46], 255);
	TextDrawFont(RouletteOther[46], 4);
	TextDrawSetProportional(RouletteOther[46], 0);
	TextDrawSetShadow(RouletteOther[46], 0);

	RouletteOther[47] = TextDrawCreate(302.2199, 276.0585, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[47], 34.0000, 21.8299);
	TextDrawAlignment(RouletteOther[47], 1);
	TextDrawColor(RouletteOther[47], -25287937);
	TextDrawBackgroundColor(RouletteOther[47], 255);
	TextDrawFont(RouletteOther[47], 4);
	TextDrawSetProportional(RouletteOther[47], 0);
	TextDrawSetShadow(RouletteOther[47], 0);

	RouletteOther[48] = TextDrawCreate(328.8713, 283.6718, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[48], 16.0000, 17.0599);
	TextDrawAlignment(RouletteOther[48], 1);
	TextDrawColor(RouletteOther[48], -25287937);
	TextDrawBackgroundColor(RouletteOther[48], 255);
	TextDrawFont(RouletteOther[48], 4);
	TextDrawSetProportional(RouletteOther[48], 0);
	TextDrawSetShadow(RouletteOther[48], 0);

	RouletteOther[49] = TextDrawCreate(295.8359, 275.9847, "LD_SPAC:white");
	TextDrawTextSize(RouletteOther[49], 46.4095, 17.0200);
	TextDrawAlignment(RouletteOther[49], 1);
	TextDrawColor(RouletteOther[49], -25287937);
	TextDrawBackgroundColor(RouletteOther[49], 255);
	TextDrawFont(RouletteOther[49], 4);
	TextDrawSetProportional(RouletteOther[49], 0);
	TextDrawSetShadow(RouletteOther[49], 0);

	RouletteOther[50] = TextDrawCreate(233.3166, 285.0664, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[50], 30.0000, 30.0000);
	TextDrawAlignment(RouletteOther[50], 1);
	TextDrawColor(RouletteOther[50], -25287937);
	TextDrawBackgroundColor(RouletteOther[50], 255);
	TextDrawFont(RouletteOther[50], 4);
	TextDrawSetProportional(RouletteOther[50], 0);
	TextDrawSetShadow(RouletteOther[50], 0);

	RouletteOther[51] = TextDrawCreate(247.9167, 293.1665, "FM");
	TextDrawLetterSize(RouletteOther[51], 0.2953, 1.2058);
	TextDrawAlignment(RouletteOther[51], 2);
	TextDrawColor(RouletteOther[51], -1);
	TextDrawBackgroundColor(RouletteOther[51], 255);
	TextDrawFont(RouletteOther[51], 0);
	TextDrawSetProportional(RouletteOther[51], 1);
	TextDrawSetShadow(RouletteOther[51], 0);

	RouletteOther[52] = TextDrawCreate(374.3251, 284.0292, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[52], 30.0000, 30.0000);
	TextDrawAlignment(RouletteOther[52], 1);
	TextDrawColor(RouletteOther[52], -25287937);
	TextDrawBackgroundColor(RouletteOther[52], 255);
	TextDrawFont(RouletteOther[52], 4);
	TextDrawSetProportional(RouletteOther[52], 0);
	TextDrawSetShadow(RouletteOther[52], 0);

	RouletteOther[53] = TextDrawCreate(477.2752, 318.7789, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[53], 42.0000, 40.0000);
	TextDrawAlignment(RouletteOther[53], 1);
	TextDrawColor(RouletteOther[53], -25287937);
	TextDrawBackgroundColor(RouletteOther[53], 255);
	TextDrawFont(RouletteOther[53], 4);
	TextDrawSetProportional(RouletteOther[53], 0);
	TextDrawSetShadow(RouletteOther[53], 0);

	RouletteOther[54] = TextDrawCreate(480.8417, 322.3901, "LD_BEAT:chit");
	TextDrawTextSize(RouletteOther[54], 35.0000, 33.0000);
	TextDrawAlignment(RouletteOther[54], 1);
	TextDrawColor(RouletteOther[54], 336860415);
	TextDrawBackgroundColor(RouletteOther[54], 255);
	TextDrawFont(RouletteOther[54], 4);
	TextDrawSetProportional(RouletteOther[54], 0);
	TextDrawSetShadow(RouletteOther[54], 0);

	RouletteButton[0] = TextDrawCreate(269.3833, 151.3294, "BRONZE"); // Bronze;
	TextDrawLetterSize(RouletteButton[0], 0.2581, 1.6000);
	TextDrawTextSize(RouletteButton[0], 15.0000, 47.0000);
	TextDrawAlignment(RouletteButton[0], 2);
	TextDrawColor(RouletteButton[0], -1);
	TextDrawBackgroundColor(RouletteButton[0], 255);
	TextDrawFont(RouletteButton[0], 2);
	TextDrawSetProportional(RouletteButton[0], 1);
	TextDrawSetShadow(RouletteButton[0], 0);
	TextDrawSetSelectable(RouletteButton[0], true);

	RouletteButton[1] = TextDrawCreate(319.6863, 151.3294, "SILVER"); // Silver;
	TextDrawLetterSize(RouletteButton[1], 0.2581, 1.6000);
	TextDrawTextSize(RouletteButton[1], 15.0000, 47.0000);
	TextDrawAlignment(RouletteButton[1], 2);
	TextDrawColor(RouletteButton[1], -1);
	TextDrawBackgroundColor(RouletteButton[1], 255);
	TextDrawFont(RouletteButton[1], 2);
	TextDrawSetProportional(RouletteButton[1], 1);
	TextDrawSetShadow(RouletteButton[1], 0);
	TextDrawSetSelectable(RouletteButton[1], true);

	RouletteButton[2] = TextDrawCreate(369.7893, 151.3294, "GOLD"); // Gold;
	TextDrawLetterSize(RouletteButton[2], 0.2581, 1.6000);
	TextDrawTextSize(RouletteButton[2], 15.0000, 47.0000);
	TextDrawAlignment(RouletteButton[2], 2);
	TextDrawColor(RouletteButton[2], -1);
	TextDrawBackgroundColor(RouletteButton[2], 255);
	TextDrawFont(RouletteButton[2], 2);
	TextDrawSetProportional(RouletteButton[2], 1);
	TextDrawSetShadow(RouletteButton[2], 0);
	TextDrawSetSelectable(RouletteButton[2], true);

	RouletteButton[3] = TextDrawCreate(319.5527, 278.1369, "UPDATE"); // Update;
	TextDrawLetterSize(RouletteButton[3], 0.2581, 1.6000);
	TextDrawTextSize(RouletteButton[3], 15.0000, 47.0000);
	TextDrawAlignment(RouletteButton[3], 2);
	TextDrawColor(RouletteButton[3], -1);
	TextDrawBackgroundColor(RouletteButton[3], 255);
	TextDrawFont(RouletteButton[3], 2);
	TextDrawSetProportional(RouletteButton[3], 1);
	TextDrawSetShadow(RouletteButton[3], 0);
	TextDrawSetSelectable(RouletteButton[3], true);

	RouletteButton[4] = TextDrawCreate(355.4165, 263.7073, ""); // Start;
	TextDrawTextSize(RouletteButton[4], 70.0000, 70.0000);
	TextDrawAlignment(RouletteButton[4], 1);
	TextDrawColor(RouletteButton[4], -1);
	TextDrawBackgroundColor(RouletteButton[4], -256);
	TextDrawFont(RouletteButton[4], 5);
	TextDrawSetProportional(RouletteButton[4], 0);
	TextDrawSetShadow(RouletteButton[4], 0);
	TextDrawSetSelectable(RouletteButton[4], true);
	TextDrawSetPreviewModel(RouletteButton[4], 19177);
	TextDrawSetPreviewRot(RouletteButton[4], 0.0000, -90.0000, 0.0000, 1.0000);

	RouletteButton[5] = TextDrawCreate(488.4169, 329.8164, "LD_BEAT:cross"); // Exit;
	TextDrawTextSize(RouletteButton[5], 20.0000, 18.0000);
	TextDrawAlignment(RouletteButton[5], 1);
	TextDrawColor(RouletteButton[5], -1);
	TextDrawBackgroundColor(RouletteButton[5], 255);
	TextDrawFont(RouletteButton[5], 4);
	TextDrawSetProportional(RouletteButton[5], 0);
	TextDrawSetShadow(RouletteButton[5], 0);
	TextDrawSetSelectable(RouletteButton[5], true);
	return 1;
}

LoadPlayerRouletteTextDraw(playerid)
{
	RouletteItems[playerid][0] = CreatePlayerTextDraw(playerid, 155.8972, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][0], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][0], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][0], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][0], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][0], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][1] = CreatePlayerTextDraw(playerid, 196.6472, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][1], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][1], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][1], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][1], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][1], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][2] = CreatePlayerTextDraw(playerid, 237.3972, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][2], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][2], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][2], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][2], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][2], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][3] = CreatePlayerTextDraw(playerid, 278.1473, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][3], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][3], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][3], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][3], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][3], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][3], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][4] = CreatePlayerTextDraw(playerid, 318.8973, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][4], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][4], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][4], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][4], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][4], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][5] = CreatePlayerTextDraw(playerid, 359.6473, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][5], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][5], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][5], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][5], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][5], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][6] = CreatePlayerTextDraw(playerid, 400.3973, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][6], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][6], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][6], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][6], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][6], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][6], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][7] = CreatePlayerTextDraw(playerid, 441.1473, 182.3343, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][7], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][7], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][7], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][7], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][7], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][7], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][8] = CreatePlayerTextDraw(playerid, 155.8972, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][8], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][8], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][8], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][8], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][8], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][8], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][9] = CreatePlayerTextDraw(playerid, 196.6472, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][9], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][9], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][9], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][9], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][9], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][9], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][10] = CreatePlayerTextDraw(playerid, 237.3972, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][10], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][10], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][10], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][10], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][10], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][10], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][10], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][11] = CreatePlayerTextDraw(playerid, 278.1473, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][11], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][11], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][11], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][11], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][11], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][11], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][12] = CreatePlayerTextDraw(playerid, 318.8973, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][12], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][12], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][12], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][12], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][12], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][12], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][13] = CreatePlayerTextDraw(playerid, 359.6473, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][13], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][13], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][13], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][13], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][13], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][13], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][14] = CreatePlayerTextDraw(playerid, 400.3973, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][14], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][14], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][14], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][14], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][14], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][14], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][14], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItems[playerid][15] = CreatePlayerTextDraw(playerid, 441.1473, 223.7368, "");
	PlayerTextDrawTextSize(playerid, RouletteItems[playerid][15], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, RouletteItems[playerid][15], 1);
	PlayerTextDrawColor(playerid, RouletteItems[playerid][15], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItems[playerid][15], 168430335);
	PlayerTextDrawFont(playerid, RouletteItems[playerid][15], 5);
	PlayerTextDrawSetProportional(playerid, RouletteItems[playerid][15], 0);
	PlayerTextDrawSetShadow(playerid, RouletteItems[playerid][15], 0);
	PlayerTextDrawSetPreviewModel(playerid, RouletteItems[playerid][15], 18631);
	PlayerTextDrawSetPreviewRot(playerid, RouletteItems[playerid][15], 0.0000, 0.0000, 0.0000, 1.0000);

	RouletteItemsCount[playerid][0] = CreatePlayerTextDraw(playerid, 176.3665, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][0], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][0], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][0], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][0], 0);

	RouletteItemsCount[playerid][1] = CreatePlayerTextDraw(playerid, 217.1690, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][1], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][1], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][1], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][1], 0);

	RouletteItemsCount[playerid][2] = CreatePlayerTextDraw(playerid, 257.9714, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][2], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][2], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][2], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][2], 0);

	RouletteItemsCount[playerid][3] = CreatePlayerTextDraw(playerid, 298.7741, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][3], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][3], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][3], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][3], 0);

	RouletteItemsCount[playerid][4] = CreatePlayerTextDraw(playerid, 339.5765, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][4], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][4], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][4], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][4], 0);

	RouletteItemsCount[playerid][5] = CreatePlayerTextDraw(playerid, 380.3789, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][5], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][5], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][5], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][5], 0);

	RouletteItemsCount[playerid][6] = CreatePlayerTextDraw(playerid, 421.1816, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][6], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][6], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][6], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][6], 0);

	RouletteItemsCount[playerid][7] = CreatePlayerTextDraw(playerid, 461.9841, 213.5148, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][7], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][7], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][7], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][7], 0);

	RouletteItemsCount[playerid][8] = CreatePlayerTextDraw(playerid, 176.3665, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][8], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][8], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][8], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][8], 0);

	RouletteItemsCount[playerid][9] = CreatePlayerTextDraw(playerid, 217.1690, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][9], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][9], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][9], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][9], 0);

	RouletteItemsCount[playerid][10] = CreatePlayerTextDraw(playerid, 257.9714, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][10], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][10], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][10], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][10], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][10], 0);

	RouletteItemsCount[playerid][11] = CreatePlayerTextDraw(playerid, 298.7741, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][11], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][11], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][11], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][11], 0);

	RouletteItemsCount[playerid][12] = CreatePlayerTextDraw(playerid, 339.5765, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][12], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][12], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][12], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][12], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][12], 0);

	RouletteItemsCount[playerid][13] = CreatePlayerTextDraw(playerid, 380.3789, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][13], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][13], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][13], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][13], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][13], 0);

	RouletteItemsCount[playerid][14] = CreatePlayerTextDraw(playerid, 421.1816, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][14], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][14], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][14], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][14], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][14], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][14], 0);

	RouletteItemsCount[playerid][15] = CreatePlayerTextDraw(playerid, 461.9841, 255.0173, "_");
	PlayerTextDrawLetterSize(playerid, RouletteItemsCount[playerid][15], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, RouletteItemsCount[playerid][15], 2);
	PlayerTextDrawColor(playerid, RouletteItemsCount[playerid][15], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteItemsCount[playerid][15], 255);
	PlayerTextDrawFont(playerid, RouletteItemsCount[playerid][15], 2);
	PlayerTextDrawSetProportional(playerid, RouletteItemsCount[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, RouletteItemsCount[playerid][15], 0);

	RouletteInfo[playerid][0] = CreatePlayerTextDraw(playerid, 319.5527, 303.5386, "_"); // Стоимость обновления;
	PlayerTextDrawLetterSize(playerid, RouletteInfo[playerid][0], 0.1720, 1.3099);
	PlayerTextDrawAlignment(playerid, RouletteInfo[playerid][0], 2);
	PlayerTextDrawColor(playerid, RouletteInfo[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteInfo[playerid][0], 255);
	PlayerTextDrawFont(playerid, RouletteInfo[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, RouletteInfo[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, RouletteInfo[playerid][0], 0);

	RouletteInfo[playerid][1] = CreatePlayerTextDraw(playerid, 260.8695, 293.3865, "_"); // Кол-во Flin Money;
	PlayerTextDrawLetterSize(playerid, RouletteInfo[playerid][1], 0.1720, 1.3099);
	PlayerTextDrawAlignment(playerid, RouletteInfo[playerid][1], 1);
	PlayerTextDrawColor(playerid, RouletteInfo[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteInfo[playerid][1], 255);
	PlayerTextDrawFont(playerid, RouletteInfo[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, RouletteInfo[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, RouletteInfo[playerid][1], 0);

	RouletteInfo[playerid][2] = CreatePlayerTextDraw(playerid, 376.7763, 293.3865, "_"); // Кол-во рулеток;
	PlayerTextDrawLetterSize(playerid, RouletteInfo[playerid][2], 0.1720, 1.3099);
	PlayerTextDrawAlignment(playerid, RouletteInfo[playerid][2], 3);
	PlayerTextDrawColor(playerid, RouletteInfo[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, RouletteInfo[playerid][2], 255);
	PlayerTextDrawFont(playerid, RouletteInfo[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, RouletteInfo[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, RouletteInfo[playerid][2], 0);
	return 1;
}

CMD:roulette_stats(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
	if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Используйте: /roulette_stats [type]");

	STRING_GLOBAL = "[#] Название\tКоличество\n", STRING_MIN[0] = EOS;

	for(new i = 1; i < sizeof(TypeGiveItemName); i++)
	{
		format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s:\t%d\n", i, TypeGiveItemName[i], RouletteStats[params[0]][i]);
		strcat(STRING_GLOBAL, STRING_MIN);
	}

	/*
		Стоимость:
			Уникальный аксессуар, скин и уникальный скин: 25 процентов от стоимости;
			Транспортное средство и уникальное транспортное средство: 50 процентов от стоимости.
	*/

	new
		spent_donate = RouletteSpinCount[params[0]] * RoulettePrice[params[0]],
		received_donate = (RouletteStats[params[0]][2] / 2000) + (RouletteStats[params[0]][3] / 2000) + RouletteStats[params[0]][4] + RouletteStats[params[0]][5] + (RouletteStats[params[0]][7] / 2000) + (RouletteStats[params[0]][8] / 2000) + (RouletteStats[params[0]][9] / 2000) + (RouletteStats[params[0]][10] / 2000) + (RouletteStats[params[0]][11] / 2000);

	format(STRING_MIN, sizeof(STRING_MIN), "\
	Вращений:\t%d\n\
	Потрачено игроком:\t%d Flin Money\n\
	Получено игроком, если все перевести в Flin Money:\t%d Flin Money\n\
	Потрачено игроком на обновление призов:\t%d Flin Money\n\
	Чистая прибыль:\t%d Flin Money",
	RouletteSpinCount[params[0]],
	spent_donate,
	received_donate,
	RouletteStats[params[0]][12], (spent_donate - received_donate) + RouletteStats[params[0]][12]);
	strcat(STRING_GLOBAL, STRING_MIN);

	ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Статистика рулетки", STRING_GLOBAL, "ОК", "");
	return 1;
}
