new Text:CaseOther[58];
new Text:CaseButton[5];
new PlayerText:CaseItems[MAX_PLAYERS][16];
new PlayerText:CaseItemsCount[MAX_PLAYERS][16];
new PlayerText:CaseInfo[MAX_PLAYERS][4];

new CaseTimer[MAX_PLAYERS]; // Таймер обновления;
new bool:CaseTimerStart[MAX_PLAYERS]; // Статус старта таймера;
new bool:CaseTimerEnd[MAX_PLAYERS]; // Статус завершения таймера;
new CaseTimerIDx[MAX_PLAYERS]; // ID таймера;
new CasePosition[MAX_PLAYERS]; // ID ячейки, которая меняет цвет;
new CaseWinIDx[MAX_PLAYERS]; // ID ячейки, которая должна выпасть;
new CaseType[MAX_PLAYERS]; // Тип рулетки;

new CaseOpen[20]; // Кол-во открытий;
new CaseOpenCount[20]; // Кол-во открытий которые не обнуляется;

new CaseStats[20][12]; // Статистика;

#define MAX_CASE	20

enum E_CASE
{
	CaseNameOne[32],
	CaseNameTwo[32],
	CaseNameThree[32],
	CaseNameFour[32],
	CasePrize[16],
	CasePrizeCount[16],
	CasePrice
}

new Case[MAX_CASE][E_CASE] = {
	{
		"Гражданский", "гражданских", "гражданского", "Civil",
		{TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{434, 522, 424, 495, 494, 502, 503, 568, 600000, 550000, 500000, 450000, 400000, 350000, 300000, 250000},
		250
	},
	{
		"Модный", "модных", "модного", "Fashion",
		{TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{558, 559, 586, 587, 464, 576, 438, 465, 513, 445, 472, 529, 450000, 400000, 350000, 300000},
		300
	},
	{
		"Стильный", "стильных", "стильного", "Stylish",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{208, 117, 118, 277, 278, 279, 253, 262, 268, 50, 49, 62, 450000, 400000, 350000, 300000},
		300
	},
	{
		"Автомобильный", "автомобильных", "автомобильного", "Car",
		{TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{573, 490, 470, 528, 601, 427, 599, 596, 597, 598, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Правительственный", "правительственных", "правительственного", "Mayor",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{147, 68, 227, 57, 187, 98, 71, 650000, 600000, 550000, 500000, 450000, 400000, 350000, 300000, 250000},
		250
	},
	{
		"Полицейский", "полицейских", "полицейского", "Police",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{311, 310, 283, 288, 285, 282, 280, 281, 267, 266, 265, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"ФБР", "ФБР", "ФБР", "FBI",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{165, 166, 163, 164, 286, 309, 307, 306, 850000, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Армейский", "армейских", "армейского", "Army",
		{TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{548, 563, 497, 433, 61, 255, 179, 287, 191, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Медицинский", "медицинских", "медицинского", "Medic",
		{TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{416, 70, 276, 275, 274, 308, 148, 900000, 850000, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Новостной", "новостных", "новостного", "News",
		{TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{488, 582, 261, 223, 186, 217, 170, 250, 188, 263, 225, 224, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Автошкольный", "автошкольных", "автошкольного", "Autoschool",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{240, 189, 171, 59, 194, 172, 950000, 900000, 850000, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Grove", "Grove", "Grove", "Grove",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{270, 86, 271, 149, 269, 107, 106, 105, 65, 500000, 450000, 400000, 350000, 300000, 250000, 200000},
		200
	},
	{
		"Ballas", "Ballas", "Ballas", "Ballas",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{104, 102, 103, 195, 750000, 700000, 650000, 600000, 550000, 500000, 450000, 400000, 350000, 300000, 250000, 200000},
		200
	},
	{
		"Rifa", "Rifa", "Rifa", "Rifa",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{173, 174, 175, 56, 750000, 700000, 650000, 600000, 550000, 500000, 450000, 400000, 350000, 300000, 250000, 200000},
		200
	},
	{
		"Aztecas", "Aztecas", "Aztecas", "Aztecas",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{115, 116, 114, 193, 750000, 700000, 650000, 600000, 550000, 500000, 450000, 400000, 350000, 300000, 250000, 200000},
		200
	},
	{
		"Vagos", "Vagos", "Vagos", "Vagos",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{110, 109, 108, 190, 750000, 700000, 650000, 600000, 550000, 500000, 450000, 400000, 350000, 300000, 250000, 200000},
		200
	},
	{
		"Russian Mafia", "Russian Mafia", "Russian Mafia", "RM",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{125, 46, 126, 111, 272, 112, 216, 233, 850000, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"La Cosa Nostra", "La Cosa Nostra", "La Cosa Nostra", "LCN",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{113, 223, 124, 127, 98, 93, 40, 900000, 850000, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Yakuza", "Yakuza", "Yakuza", "Yakuza",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{120, 294, 186, 123, 122, 121, 263, 169, 12, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	},
	{
		"Biker", "Biker", "Biker", "Biker",
		{TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_U_SKIN, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_MONEY},
		{248, 254, 100, 181, 246, 64, 198, 131, 850000, 800000, 750000, 700000, 650000, 600000, 550000, 500000},
		500
	}
};

ShowPlayerCaseList(playerid)
{
	STRING_GLOBAL = "[#] Название\tСтоимость\n", STRING_MIN[0] = EOS;
	for(new i = 0; i < MAX_CASE; i++)
	{
		format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d Flin Money\n", i + 1, Case[i][CaseNameOne], Case[i][CasePrice]);
		strcat(STRING_GLOBAL, STRING_MIN);
	}
	ShowPlayerDialog(playerid, D_CASE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Кейсы", STRING_GLOBAL, "Далее", "Отмена");
	return 1;
}

GetNameCaseWinItemsName(playerid)
{
	new idx = CaseWinIDx[playerid], type = CaseType[playerid];
    switch(Case[type][CasePrize][idx])
	{
		case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY, TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
		{
			CaseStats[type][Case[type][CasePrize][idx]] += Case[type][CasePrizeCount][idx];
			SetPlayerItem(playerid, 1, p_info[playerid][ID], Case[type][CasePrize][idx], Case[type][CasePrizeCount][idx]);
		}
		case TYPE_GIVE_ITEM_ACCESSORIES:
		{
			CaseStats[type][TYPE_GIVE_ITEM_ACCESSORIES] += ItemsInfo[Case[type][CasePrizeCount][idx]][iPrice] / 6;
			SetPlayerItem(playerid, 1, p_info[playerid][ID], TYPE_GIVE_ITEM_ACCESSORIES, Case[type][CasePrizeCount][idx], .price = ItemsInfo[Case[type][CasePrizeCount][idx]][iPrice] / 8000);
		}
		case TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
		{
			CaseStats[type][Case[type][CasePrize][idx]] += ItemsInfo[Case[type][CasePrizeCount][idx]][iPrice] / 6;
			SetPlayerItem(playerid, 1, p_info[playerid][ID], Case[type][CasePrize][idx], Case[type][CasePrizeCount][idx], .price = ItemsInfo[Case[type][CasePrizeCount][idx]][iPrice] / 8000);
		}
		case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
		{
			CaseStats[type][Case[type][CasePrize][idx]] += GetVehicleData(Case[type][CasePrizeCount][idx], E_VD_PRICE) / 2;
			SetPlayerItem(playerid, 1, p_info[playerid][ID], Case[type][CasePrize][idx], Case[type][CasePrizeCount][idx]);
		}
	}
	SaveCaseStats(type);
	new str[256];
	format(str, sizeof(str), "%s", GetPrizeItemsName(Case[type][CasePrize][idx], Case[type][CasePrizeCount][idx]));
	return str;
}

ClearPlayerTextDrawCase(playerid, type = 0)
{
	if(type == 1)
	{
		p_temp[playerid][TextDrawCase] = false;
		CaseType[playerid] = -1;
	}
	CaseTimer[playerid] = 0;
	CaseTimerStart[playerid] = false;
	CaseTimerEnd[playerid] = false;
	if(CaseTimerIDx[playerid] != 0 || IsValidTimer(CaseTimerIDx[playerid])) KillTimer(CaseTimerIDx[playerid]);
	CaseTimerIDx[playerid] = 0;
	CasePosition[playerid] = -1;
	CaseWinIDx[playerid] = -1;
	return 1;
}

this::ShowPlayerCase(playerid, type)
{
	if(!ServerInfo[CaseSystem]) return SendError(playerid, "Кейсы отключены администрацией.");
	if(type < 0 || type > 19) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
    if(IsTDVisible(playerid) != -1) return 1;
    CaseType[playerid] = type;
    if(p_info[playerid][p_settings][INTERFACE]) return ShowTextDrawForPlayer(playerid, TD_ID_CASE);

	LoadPlayerTextDrawCase(playerid);
	ClearPlayerTextDrawCase(playerid);

	for(new i = 0; i < 58; i++)
	{
		TextDrawShowForPlayer(playerid, CaseOther[i]);
		if(i < 16) ShowPlayerCaseItems(playerid, type, i);
		if(i < 5) TextDrawShowForPlayer(playerid, CaseButton[i]);
		if(i < 4) PlayerTextDrawShow(playerid, CaseInfo[playerid][i]);
	}

	p_temp[playerid][TextDrawCase] = true;
	UpdatePlayerCaseInfo(playerid);

	SelectTextDraw(playerid, -11206401);
	return 1;
}

ShowPlayerCaseItems(playerid, type, idx)
{
	switch(Case[type][CasePrize][idx])
	{
		case TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_U_SKIN:
		{
			PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][idx], Case[type][CasePrizeCount][idx]);
			PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][idx], 0.0000, 0.0000, 0.0000, 1.2000);
			PlayerTextDrawShow(playerid, CaseItems[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_ACCESSORIES:
		{
			new i = Case[type][CasePrizeCount][idx];
			PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][idx], ItemsInfo[i][iModel]);
			PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][idx], ItemsInfo[i][iObjectPos][0], ItemsInfo[i][iObjectPos][1], ItemsInfo[i][iObjectPos][2], ItemsInfo[i][iObjectPos][3]);
			PlayerTextDrawShow(playerid, CaseItems[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_U_VEHICLE:
		{
			PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][idx], Case[type][CasePrizeCount][idx]);
			PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][idx], -45.0000, 0.0000, -45.0000, 1.0000);
			PlayerTextDrawShow(playerid, CaseItems[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_U_MONEY:
		{
			PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][idx], 1550);
			PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][idx], 0.0000, 0.0000, 0.0000, 1.0000);
			PlayerTextDrawShow(playerid, CaseItems[playerid][idx]);
			new str[32];
			format(str, sizeof(str), "%d", Case[type][CasePrizeCount][idx]);
			PlayerTextDrawSetString(playerid, CaseItemsCount[playerid][idx], str);
			PlayerTextDrawShow(playerid, CaseItemsCount[playerid][idx]);
		}
		case TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_U_DONATE:
		{
			PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][idx], 1274);
			PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][idx], 0.0000, 0.0000, 0.0000, 1.0000);
			PlayerTextDrawShow(playerid, CaseItems[playerid][idx]);
			new str[32];
			format(str, sizeof(str), "%d", Case[type][CasePrizeCount][idx]);
			PlayerTextDrawSetString(playerid, CaseItemsCount[playerid][idx], str);
			PlayerTextDrawShow(playerid, CaseItemsCount[playerid][idx]);
		}
	}
	return 1;
}

UpdatePlayerCaseInfo(playerid)
{
	new str[64], type = CaseType[playerid];
	if(p_temp[playerid][TextDrawCase] == false || type < 0 || type > 19) return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента."), HidePlayerCase(playerid);
	format(str, sizeof(str), "%s", Case[type][CaseNameFour]);
	PlayerTextDrawSetString(playerid, CaseInfo[playerid][0], str);
	format(str, sizeof(str), "%d", p_info[playerid][flinmoney]);
	PlayerTextDrawSetString(playerid, CaseInfo[playerid][1], str);
	format(str, sizeof(str), "%d", GetInventoryAmount(playerid, TRANSFER_ITEMS+type+27));
	PlayerTextDrawSetString(playerid, CaseInfo[playerid][2], str);
	format(str, sizeof(str), "%d Flin Money", Case[type][CasePrice]);
	PlayerTextDrawSetString(playerid, CaseInfo[playerid][3], str);
	return 1;
}

GetPlayerCasePositionIDx(type_case, type_prize, idx_prize)
{
	new i = -1, idx;
	while(i == -1)
	{
		idx = random(16);
		if(Case[type_case][CasePrize][idx] == type_prize && Case[type_case][CasePrizeCount][idx] == idx_prize)
		{
			i = idx;
			break;
		}
	}
	return idx;
}

GetPlayerCaseWinIDx(type)
{
	switch(type)
	{
		case 0: // Гражданский;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 45) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 45:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 434);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 522);
				}
				case 30:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 424);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 495);
				}
				case 15:
				{
					switch(random(4))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 494);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 502);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 503);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 568);
					}
				}
				default:
				{
					switch(random(86))
					{
						case 0 .. 24: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 25 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 45 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 60 .. 69: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 70 .. 76: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						case 77 .. 81: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 82 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
					}
				}
			}
		}
		case 1: // Модный;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20:
				{
					switch(random(6))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 558);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 559);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 586);
						case 3: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 587);
						case 4: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 464);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 576);
					}
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 438);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 465);
				}
				case 10:
				{
					switch(random(4))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 513);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 445);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 472);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_ACCESSORIES, 529);
					}
				}
				default:
				{
					switch(random(16))
					{
						case 0 .. 6: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 7 .. 11: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 12 .. 14: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
					}
				}
			}
		}
		case 2: // Стильный;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 25) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 25: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 208);
				case 20:
				{
					switch(random(5))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 117);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 118);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 277);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 278);
					}
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 279);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 253);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 262);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 268);
				}
				case 5:
				{
					switch(random(4))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 50);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 49);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 62);
					}
				}
				default:
				{
					switch(random(16))
					{
						case 0 .. 6: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 7 .. 11: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 12 .. 14: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
					}
				}
			}
		}
		case 3: // Автомобильный;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 45) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 45: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 573);
				case 30:
				{
					switch(random(5))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 490);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 470);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 528);
						case 3: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 601);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 427);
					}
				}
				case 15:
				{
					switch(random(4))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 599);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 596);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 597);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 598);
					}
				}
				default:
				{
					switch(random(41))
					{
						case 0 .. 14: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 15 .. 24: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 25 .. 31: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 32 .. 36: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 37 .. 39: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
					}
				}
			}
		}
		case 4: // Правительственный;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 147);
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 68);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 227);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 57);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 187);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 98);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 71);
				}
				default:
				{
					switch(random(151))
					{
						case 0 .. 34: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 35 .. 64: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 65 .. 89: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 90 .. 109: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 110 .. 124: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						case 125 .. 134: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 135 .. 141: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 142 .. 146: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 147 .. 149: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
					}
				}
			}
		}
		case 5: // Полицейский;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 25) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 25:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 311);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 310);
				}
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 283);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 288);
				}
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 285);
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 282);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 280);
				}
				case 5:
				{
					switch(random(4))
					{
						case 0: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 281);
						case 1: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 267);
						case 2: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 266);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 265);
					}
				}
				default:
				{
					switch(random(26))
					{
						case 0 .. 9: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 10 .. 16: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 17 .. 21: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 22 .. 24: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
					}
				}
			}
		}
		case 6: // ФБР;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 165);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 309);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 166);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 307);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 163);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 164);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 286);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 306);
				}
				default:
				{
					switch(random(86))
					{
						case 0 .. 24: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 25 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 45 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 60 .. 69: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 70 .. 76: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 77 .. 81: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						case 82 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 850000);
					}
				}
			}
		}
		case 7: // Армейский;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 25) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 25:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 548);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 563);
				}
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 433);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 497);
				}
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 61);
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 255);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 179);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 287);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 191);
				}
				default:
				{
					switch(random(61))
					{
						case 0 .. 19: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 20 .. 34: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 35 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 45 .. 51: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 52 .. 56: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 57 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
					}
				}
			}
		}
		case 8: // Медицинский;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 25) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 25: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 416);
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 70);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 308);
				}
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 276);
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 275);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 274);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 148);
				}
				default:
				{
					switch(random(116))
					{
						case 0 .. 29: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 30 .. 54: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 55 .. 74: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 75 .. 89: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 90 .. 99: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 100 .. 106: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						case 107 .. 111: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
						case 112 .. 114: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 850000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 900000);
					}
				}
			}
		}
		case 9: // Новостной;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 30) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 30:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 488);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_VEHICLE, 582);
				}
				case 25:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 261);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 263);
				}
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 223);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 225);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 186);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 217);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 170);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 250);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 188);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 224);
				}
				default:
				{
					switch(random(20))
					{
						case 0 .. 9: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 10 .. 14: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 15 .. 17: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
					}
				}
			}
		}
		case 10: // Автошкольный;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 240);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 194);
				}
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 189);
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 171);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 59);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 172);
				}
				default:
				{
					switch(random(151))
					{
						case 0 .. 34: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 35 .. 64: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 65 .. 89: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 90 .. 109: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 110 .. 124: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 125 .. 134: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						case 135 .. 141: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
						case 142 .. 146: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 850000);
						case 147 .. 149: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 900000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 950000);
					}
				}
			}
		}
		case 11: // Grove;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 25) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 25: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 270);
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 86);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 271);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 149);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 269);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 107);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 106);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 105);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 65);
				}
				default:
				{
					switch(random(61))
					{
						case 0 .. 19: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 200000);
						case 20 .. 34: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 35 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 45 .. 51: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 52 .. 56: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 57 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
					}
				}
			}
		}
		case 12: // Ballas;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 15) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 104);
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 102);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 103);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 195);
				}
				default:
				{
					switch(random(236))
					{
						case 0 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 200000);
						case 45 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 85 .. 119: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 120 .. 149: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 150 .. 174: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 175 .. 194: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						case 195 .. 209: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 210 .. 219: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 220 .. 226: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 227 .. 231: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 232 .. 234: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
					}
				}
			}
		}
		case 13: // Rifa;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 15) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 173);
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 174);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 175);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 56);
				}
				default:
				{
					switch(random(236))
					{
						case 0 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 200000);
						case 45 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 85 .. 119: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 120 .. 149: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 150 .. 174: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 175 .. 194: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						case 195 .. 209: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 210 .. 219: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 220 .. 226: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 227 .. 231: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 232 .. 234: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
					}
				}
			}
		}
		case 14: // Aztecas;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 15) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 115);
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 116);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 114);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 193);
				}
				default:
				{
					switch(random(236))
					{
						case 0 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 200000);
						case 45 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 85 .. 119: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 120 .. 149: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 150 .. 174: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 175 .. 194: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						case 195 .. 209: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 210 .. 219: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 220 .. 226: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 227 .. 231: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 232 .. 234: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
					}
				}
			}
		}
		case 15: // Vagos;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 15) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 15: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 110);
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 109);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 108);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 190);
				}
				default:
				{
					switch(random(236))
					{
						case 0 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 200000);
						case 45 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 250000);
						case 85 .. 119: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 300000);
						case 120 .. 149: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 350000);
						case 150 .. 174: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 400000);
						case 175 .. 194: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 450000);
						case 195 .. 209: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 210 .. 219: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 220 .. 226: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 227 .. 231: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 232 .. 234: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
					}
				}
			}
		}
		case 16: // RM;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 125);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 216);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 46);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 126);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 111);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 272);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 112);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 233);
				}
				default:
				{
					switch(random(86))
					{
						case 0 .. 24: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 25 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 45 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 60 .. 69: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 70 .. 76: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 77 .. 81: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						case 82 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 850000);
					}
				}
			}
		}
		case 17: // LCN;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 113);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 93);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 223);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 124);
				}
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 127);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 98);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 40);
				}
				default:
				{
					switch(random(116))
					{
						case 0 .. 29: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 30 .. 54: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 55 .. 74: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 75 .. 89: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 90 .. 99: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 100 .. 106: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						case 107 .. 111: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
						case 112 .. 114: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 850000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 900000);
					}
				}
			}
		}
		case 18: // Yakuza;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 25) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 25:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 120);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 263);
				}
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 294);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 169);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 186);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 123);
				}
				case 10: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 122);
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 121);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 12);
				}
				default:
				{
					switch(random(61))
					{
						case 0 .. 19: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 20 .. 34: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 35 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 45 .. 51: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 52 .. 56: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 57 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
					}
				}
			}
		}
		case 19: // Biker;
		{
			CaseOpen[type]++;
			if(CaseOpen[type] > 20) CaseOpen[type] = 0;

			CaseOpenCount[type]++;

			SaveCaseOpen();

			switch(CaseOpen[type])
			{
				case 20:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 248);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 246);
				}
				case 15:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 254);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 64);
				}
				case 10:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 100);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 198);
				}
				case 5:
				{
					if(random(2) == 0) return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 181);
					else return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_U_SKIN, 131);
				}
				default:
				{
					switch(random(86))
					{
						case 0 .. 24: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 500000);
						case 25 .. 44: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 550000);
						case 45 .. 59: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 600000);
						case 60 .. 69: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 650000);
						case 70 .. 76: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 700000);
						case 77 .. 81: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 750000);
						case 82 .. 84: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 800000);
						default: return GetPlayerCasePositionIDx(type, TYPE_GIVE_ITEM_MONEY, 850000);
					}
				}
			}
		}
	}
	return 1;
}

StartPlayerCase(playerid)
{
	if(!ServerInfo[CaseSystem]) {
		HidePlayerCase(playerid);
		return SendError(playerid, "Открытие кейсов отключено администрацией.");
	}
	if(CaseTimerIDx[playerid] != 0) return SendError(playerid, "Вы не можете запустить открытие кейсов, в данный момент запущено открытие кейсов.");
	new type = CaseType[playerid];
    if(!(0 <= type <= 19))
        return SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента."), HidePlayerCase(playerid);
	if(GetInventoryAmount(playerid, TRANSFER_ITEMS+type+27) == 0)
	{
		SendError(playerid, "У Вас нет %s кейса.", Case[type][CaseNameThree]);
		STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
		format(STRING_MIN, sizeof(STRING_MIN), ""I"%s кейс", Case[type][CaseNameOne]);
		format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
		Введите желаемое кол-во %s кейсов для приобретения:\n\n\
		Стоимость 1 %s кейса: {"#cGREEN"}%d"W" Flin Money", Case[type][CaseNameTwo], Case[type][CaseNameThree], Case[type][CasePrice]);
		ShowPlayerDialog(playerid, D_CASE_BUY, DIALOG_STYLE_INPUT, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
		return 1;
	}
	GivePlayerInventory(playerid, TRANSFER_ITEMS+type + 27, -1);

	if(p_info[playerid][p_settings][INTERFACE]) Case_UpdateTD_Info(playerid, type);
    else UpdatePlayerCaseInfo(playerid);
	new rand = 16 * RandomEx(2, 5), idx = GetPlayerCaseWinIDx(type) + rand;
	CaseTimer[playerid] = idx + 1;
	CaseTimerStart[playerid] = true;
	CaseTimerEnd[playerid] = false;
	CasePosition[playerid] = 0;
	CaseWinIDx[playerid] = idx - rand;
	CaseTimerIDx[playerid] = SetTimerEx("CheckPlayerCase", 100, true, "i", playerid);
	return 1;
}

forward CheckPlayerCase(playerid);
public CheckPlayerCase(playerid)
{
	if(CaseTimerIDx[playerid] == 0) return 1;
	if(p_temp[playerid][TextDrawCase] == true)
	{
		if(CaseTimer[playerid] > 0)
		{
			CaseTimer[playerid]--;

			if(CaseTimerEnd[playerid] == false)
			{
				if(CaseTimerStart[playerid] == false)
				{
					if(CasePosition[playerid] - 1 < 0)
					{
                        if(p_info[playerid][p_settings][INTERFACE]) Case_UpdateTD_ItemBG(playerid, 25, "flin_case:flin_case_slot");
                        else {
                            PlayerTextDrawHide(playerid, CaseItems[playerid][15]);
                            PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][15], 168430335);
                            PlayerTextDrawShow(playerid, CaseItems[playerid][15]);
                        }
    				}
					else
					{
                        if(p_info[playerid][p_settings][INTERFACE]) Case_UpdateTD_ItemBG(playerid, 10+CasePosition[playerid]-1, "flin_case:flin_case_slot");
                        else {
                            PlayerTextDrawHide(playerid, CaseItems[playerid][CasePosition[playerid] - 1]);
                            PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][CasePosition[playerid] - 1], 168430335);
                            PlayerTextDrawShow(playerid, CaseItems[playerid][CasePosition[playerid] - 1]);
                        }
                    }
				}

				if(CaseTimerStart[playerid] == true) CaseTimerStart[playerid] = false;

                if(p_info[playerid][p_settings][INTERFACE]) Case_UpdateTD_ItemBG(playerid, 10+CasePosition[playerid], "flin_case:flin_case_slot_use");
                else {
                    PlayerTextDrawHide(playerid, CaseItems[playerid][CasePosition[playerid]]);
                    PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][CasePosition[playerid]], -25287937);
                    PlayerTextDrawShow(playerid, CaseItems[playerid][CasePosition[playerid]]);
                }

				CasePosition[playerid]++;
				if(CasePosition[playerid] == 16) CasePosition[playerid] = 0;

				if(CaseTimer[playerid] == 0)
				{
					CaseTimer[playerid] = 3;
					CaseTimerEnd[playerid] = true;

					STRING_GLOBAL[0] = EOS;
					format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
					Вы выиграли: "I"%s", GetNameCaseWinItemsName(playerid));
					ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Приз", STRING_GLOBAL, "ОК", "");
				}
			}
			else
			{
				if(CaseTimer[playerid] == 0)
				{
					if(CasePosition[playerid] - 1 < 0)
					{
                        if(p_info[playerid][p_settings][INTERFACE]) Case_UpdateTD_ItemBG(playerid, 25, "flin_case:flin_case_slot");
                        else {
                            PlayerTextDrawHide(playerid, CaseItems[playerid][15]);
                            PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][15], 168430335);
                            PlayerTextDrawShow(playerid, CaseItems[playerid][15]);
                        }
    				}
					else
					{
                        if(p_info[playerid][p_settings][INTERFACE]) Case_UpdateTD_ItemBG(playerid, 10+CasePosition[playerid]-1, "flin_case:flin_case_slot");
                        else {
                            PlayerTextDrawHide(playerid, CaseItems[playerid][CasePosition[playerid] - 1]);
                            PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][CasePosition[playerid] - 1], 168430335);
                            PlayerTextDrawShow(playerid, CaseItems[playerid][CasePosition[playerid] - 1]);
                        }
                    }

					CaseTimerEnd[playerid] = false;

					KillTimer(CaseTimerIDx[playerid]);
					CaseTimerIDx[playerid] = 0;
				}
			}
		}
	}
	return 1;
}

HidePlayerCase(playerid)
{
	if(p_info[playerid][p_settings][INTERFACE]) return HideTextDrawForPlayer(playerid, TD_ID_CASE);
	for(new i = 0; i < 58; i++)
	{
		TextDrawHideForPlayer(playerid, CaseOther[i]);
		if(i < 16)
		{
			if(CaseItems[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, CaseItems[playerid][i]);
				CaseItems[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
			}
			if(CaseItemsCount[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
			{
				PlayerTextDrawDestroy(playerid, CaseItemsCount[playerid][i]);
				CaseItemsCount[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
			}
		}
		if(i < 5) TextDrawHideForPlayer(playerid, CaseButton[i]);
		if(i < 4 && CaseInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, CaseInfo[playerid][i]);
			CaseInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	ClearPlayerTextDrawCase(playerid, 1);
	CancelSelectTextDraw(playerid);
	return 1;
}

SaveCaseOpen()
{
	new string[32];

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	CaseOpen[0], CaseOpen[1], CaseOpen[2], CaseOpen[3], CaseOpen[4],
	CaseOpen[5], CaseOpen[6], CaseOpen[7], CaseOpen[8], CaseOpen[9],
	CaseOpen[10], CaseOpen[11], CaseOpen[12], CaseOpen[13], CaseOpen[14],
	CaseOpen[15], CaseOpen[16], CaseOpen[17], CaseOpen[18], CaseOpen[19]);
	MysqlUpdateOtherStr("case_open", string);

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	CaseOpenCount[0], CaseOpenCount[1], CaseOpenCount[2], CaseOpenCount[3], CaseOpenCount[4],
	CaseOpenCount[5], CaseOpenCount[6], CaseOpenCount[7], CaseOpenCount[8], CaseOpenCount[9],
	CaseOpenCount[10], CaseOpenCount[11], CaseOpenCount[12], CaseOpenCount[13], CaseOpenCount[14],
	CaseOpenCount[15], CaseOpenCount[16], CaseOpenCount[17], CaseOpenCount[18], CaseOpenCount[19]);
	MysqlUpdateOtherStr("case_open_count", string);
	return 1;
}

SaveCaseStats(type)
{
	new string[256], mysql_name[32];

	format(mysql_name, sizeof(mysql_name), "case_stats_%d", type);

	format(string, sizeof(string), "%i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i, %i",
	CaseStats[type][0], CaseStats[type][1], CaseStats[type][2], CaseStats[type][3], CaseStats[type][4], CaseStats[type][5],
	CaseStats[type][6], CaseStats[type][7], CaseStats[type][8], CaseStats[type][9], CaseStats[type][10], CaseStats[type][11]);
	MysqlUpdateOtherStr(mysql_name, string);
	return 1;
}

LoadTextDrawCase()
{
	CaseOther[0] = TextDrawCreate(224.3992, 136.7207, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[0], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[0], 1);
	TextDrawColor(CaseOther[0], -25287937);
	TextDrawBackgroundColor(CaseOther[0], 255);
	TextDrawFont(CaseOther[0], 4);
	TextDrawSetProportional(CaseOther[0], 0);
	TextDrawSetShadow(CaseOther[0], 0);

	CaseOther[1] = TextDrawCreate(224.3992, 303.4490, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[1], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[1], 1);
	TextDrawColor(CaseOther[1], -25287937);
	TextDrawBackgroundColor(CaseOther[1], 255);
	TextDrawFont(CaseOther[1], 4);
	TextDrawSetProportional(CaseOther[1], 0);
	TextDrawSetShadow(CaseOther[1], 0);

	CaseOther[2] = TextDrawCreate(387.8092, 136.7207, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[2], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[2], 1);
	TextDrawColor(CaseOther[2], -25287937);
	TextDrawBackgroundColor(CaseOther[2], 255);
	TextDrawFont(CaseOther[2], 4);
	TextDrawSetProportional(CaseOther[2], 0);
	TextDrawSetShadow(CaseOther[2], 0);

	CaseOther[3] = TextDrawCreate(387.8092, 303.4490, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[3], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[3], 1);
	TextDrawColor(CaseOther[3], -25287937);
	TextDrawBackgroundColor(CaseOther[3], 255);
	TextDrawFont(CaseOther[3], 4);
	TextDrawSetProportional(CaseOther[3], 0);
	TextDrawSetShadow(CaseOther[3], 0);

	CaseOther[4] = TextDrawCreate(227.6493, 147.1096, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[4], 16.8201, 165.1846);
	TextDrawAlignment(CaseOther[4], 1);
	TextDrawColor(CaseOther[4], -25287937);
	TextDrawBackgroundColor(CaseOther[4], 255);
	TextDrawFont(CaseOther[4], 4);
	TextDrawSetProportional(CaseOther[4], 0);
	TextDrawSetShadow(CaseOther[4], 0);

	CaseOther[5] = TextDrawCreate(387.6589, 147.1096, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[5], 16.8201, 167.0137);
	TextDrawAlignment(CaseOther[5], 1);
	TextDrawColor(CaseOther[5], -25287937);
	TextDrawBackgroundColor(CaseOther[5], 255);
	TextDrawFont(CaseOther[5], 4);
	TextDrawSetProportional(CaseOther[5], 0);
	TextDrawSetShadow(CaseOther[5], 0);

	CaseOther[6] = TextDrawCreate(234.3993, 139.8314, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[6], 163.9761, 17.2201);
	TextDrawAlignment(CaseOther[6], 1);
	TextDrawColor(CaseOther[6], -25287937);
	TextDrawBackgroundColor(CaseOther[6], 255);
	TextDrawFont(CaseOther[6], 4);
	TextDrawSetProportional(CaseOther[6], 0);
	TextDrawSetShadow(CaseOther[6], 0);

	CaseOther[7] = TextDrawCreate(234.8161, 302.9042, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[7], 163.9761, 17.2201);
	TextDrawAlignment(CaseOther[7], 1);
	TextDrawColor(CaseOther[7], -25287937);
	TextDrawBackgroundColor(CaseOther[7], 255);
	TextDrawFont(CaseOther[7], 4);
	TextDrawSetProportional(CaseOther[7], 0);
	TextDrawSetShadow(CaseOther[7], 0);

	CaseOther[8] = TextDrawCreate(228.1488, 140.7682, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[8], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[8], 1);
	TextDrawColor(CaseOther[8], 336860415);
	TextDrawBackgroundColor(CaseOther[8], 255);
	TextDrawFont(CaseOther[8], 4);
	TextDrawSetProportional(CaseOther[8], 0);
	TextDrawSetShadow(CaseOther[8], 0);

	CaseOther[9] = TextDrawCreate(228.3488, 302.4595, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[9], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[9], 1);
	TextDrawColor(CaseOther[9], 336860415);
	TextDrawBackgroundColor(CaseOther[9], 255);
	TextDrawFont(CaseOther[9], 4);
	TextDrawSetProportional(CaseOther[9], 0);
	TextDrawSetShadow(CaseOther[9], 0);

	CaseOther[10] = TextDrawCreate(388.9588, 140.7682, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[10], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[10], 1);
	TextDrawColor(CaseOther[10], 336860415);
	TextDrawBackgroundColor(CaseOther[10], 255);
	TextDrawFont(CaseOther[10], 4);
	TextDrawSetProportional(CaseOther[10], 0);
	TextDrawSetShadow(CaseOther[10], 0);

	CaseOther[11] = TextDrawCreate(388.9588, 302.4595, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[11], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[11], 1);
	TextDrawColor(CaseOther[11], 336860415);
	TextDrawBackgroundColor(CaseOther[11], 255);
	TextDrawFont(CaseOther[11], 4);
	TextDrawSetProportional(CaseOther[11], 0);
	TextDrawSetShadow(CaseOther[11], 0);

	CaseOther[12] = TextDrawCreate(230.7496, 150.0914, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[12], 167.0000, 160.0000);
	TextDrawAlignment(CaseOther[12], 1);
	TextDrawColor(CaseOther[12], 336860415);
	TextDrawBackgroundColor(CaseOther[12], 255);
	TextDrawFont(CaseOther[12], 4);
	TextDrawSetProportional(CaseOther[12], 0);
	TextDrawSetShadow(CaseOther[12], 0);

	CaseOther[13] = TextDrawCreate(390.8593, 148.9098, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[13], 11.0000, 161.5668);
	TextDrawAlignment(CaseOther[13], 1);
	TextDrawColor(CaseOther[13], 336860415);
	TextDrawBackgroundColor(CaseOther[13], 255);
	TextDrawFont(CaseOther[13], 4);
	TextDrawSetProportional(CaseOther[13], 0);
	TextDrawSetShadow(CaseOther[13], 0);

	CaseOther[14] = TextDrawCreate(235.8329, 143.5502, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[14], 160.5879, 10.0000);
	TextDrawAlignment(CaseOther[14], 1);
	TextDrawColor(CaseOther[14], 336860415);
	TextDrawBackgroundColor(CaseOther[14], 255);
	TextDrawFont(CaseOther[14], 4);
	TextDrawSetProportional(CaseOther[14], 0);
	TextDrawSetShadow(CaseOther[14], 0);

	CaseOther[15] = TextDrawCreate(236.4329, 304.6156, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[15], 159.5090, 11.8198);
	TextDrawAlignment(CaseOther[15], 1);
	TextDrawColor(CaseOther[15], 336860415);
	TextDrawBackgroundColor(CaseOther[15], 255);
	TextDrawFont(CaseOther[15], 4);
	TextDrawSetProportional(CaseOther[15], 0);
	TextDrawSetShadow(CaseOther[15], 0);

	CaseOther[16] = TextDrawCreate(224.3992, 360.9523, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[16], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[16], 1);
	TextDrawColor(CaseOther[16], -25287937);
	TextDrawBackgroundColor(CaseOther[16], 255);
	TextDrawFont(CaseOther[16], 4);
	TextDrawSetProportional(CaseOther[16], 0);
	TextDrawSetShadow(CaseOther[16], 0);

	CaseOther[17] = TextDrawCreate(387.8092, 360.9523, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[17], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[17], 1);
	TextDrawColor(CaseOther[17], -25287937);
	TextDrawBackgroundColor(CaseOther[17], 255);
	TextDrawFont(CaseOther[17], 4);
	TextDrawSetProportional(CaseOther[17], 0);
	TextDrawSetShadow(CaseOther[17], 0);

	CaseOther[18] = TextDrawCreate(227.6493, 323.3200, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[18], 17.0000, 47.6781);
	TextDrawAlignment(CaseOther[18], 1);
	TextDrawColor(CaseOther[18], -25287937);
	TextDrawBackgroundColor(CaseOther[18], 255);
	TextDrawFont(CaseOther[18], 4);
	TextDrawSetProportional(CaseOther[18], 0);
	TextDrawSetShadow(CaseOther[18], 0);

	CaseOther[19] = TextDrawCreate(387.6589, 323.3200, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[19], 17.0000, 47.6781);
	TextDrawAlignment(CaseOther[19], 1);
	TextDrawColor(CaseOther[19], -25287937);
	TextDrawBackgroundColor(CaseOther[19], 255);
	TextDrawFont(CaseOther[19], 4);
	TextDrawSetProportional(CaseOther[19], 0);
	TextDrawSetShadow(CaseOther[19], 0);

	CaseOther[20] = TextDrawCreate(234.8161, 360.4075, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[20], 163.9761, 17.2201);
	TextDrawAlignment(CaseOther[20], 1);
	TextDrawColor(CaseOther[20], -25287937);
	TextDrawBackgroundColor(CaseOther[20], 255);
	TextDrawFont(CaseOther[20], 4);
	TextDrawSetProportional(CaseOther[20], 0);
	TextDrawSetShadow(CaseOther[20], 0);

	CaseOther[21] = TextDrawCreate(228.3488, 359.9627, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[21], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[21], 1);
	TextDrawColor(CaseOther[21], 336860415);
	TextDrawBackgroundColor(CaseOther[21], 255);
	TextDrawFont(CaseOther[21], 4);
	TextDrawSetProportional(CaseOther[21], 0);
	TextDrawSetShadow(CaseOther[21], 0);

	CaseOther[22] = TextDrawCreate(388.9588, 359.9627, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[22], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[22], 1);
	TextDrawColor(CaseOther[22], 336860415);
	TextDrawBackgroundColor(CaseOther[22], 255);
	TextDrawFont(CaseOther[22], 4);
	TextDrawSetProportional(CaseOther[22], 0);
	TextDrawSetShadow(CaseOther[22], 0);

	CaseOther[23] = TextDrawCreate(230.7496, 323.3016, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[23], 171.0000, 45.0000);
	TextDrawAlignment(CaseOther[23], 1);
	TextDrawColor(CaseOther[23], 336860415);
	TextDrawBackgroundColor(CaseOther[23], 255);
	TextDrawFont(CaseOther[23], 4);
	TextDrawSetProportional(CaseOther[23], 0);
	TextDrawSetShadow(CaseOther[23], 0);

	CaseOther[24] = TextDrawCreate(390.8593, 323.5198, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[24], 11.0000, 45.1511);
	TextDrawAlignment(CaseOther[24], 1);
	TextDrawColor(CaseOther[24], 336860415);
	TextDrawBackgroundColor(CaseOther[24], 255);
	TextDrawFont(CaseOther[24], 4);
	TextDrawSetProportional(CaseOther[24], 0);
	TextDrawSetShadow(CaseOther[24], 0);

	CaseOther[25] = TextDrawCreate(236.4329, 362.2188, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[25], 159.5090, 11.8198);
	TextDrawAlignment(CaseOther[25], 1);
	TextDrawColor(CaseOther[25], 336860415);
	TextDrawBackgroundColor(CaseOther[25], 255);
	TextDrawFont(CaseOther[25], 4);
	TextDrawSetProportional(CaseOther[25], 0);
	TextDrawSetShadow(CaseOther[25], 0);

	CaseOther[26] = TextDrawCreate(224.3992, 79.0195, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[26], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[26], 1);
	TextDrawColor(CaseOther[26], -25287937);
	TextDrawBackgroundColor(CaseOther[26], 255);
	TextDrawFont(CaseOther[26], 4);
	TextDrawSetProportional(CaseOther[26], 0);
	TextDrawSetShadow(CaseOther[26], 0);

	CaseOther[27] = TextDrawCreate(387.8092, 79.0195, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[27], 20.0000, 20.0000);
	TextDrawAlignment(CaseOther[27], 1);
	TextDrawColor(CaseOther[27], -25287937);
	TextDrawBackgroundColor(CaseOther[27], 255);
	TextDrawFont(CaseOther[27], 4);
	TextDrawSetProportional(CaseOther[27], 0);
	TextDrawSetShadow(CaseOther[27], 0);

	CaseOther[28] = TextDrawCreate(233.7330, 82.1230, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[28], 164.1837, 54.0000);
	TextDrawAlignment(CaseOther[28], 1);
	TextDrawColor(CaseOther[28], -25287937);
	TextDrawBackgroundColor(CaseOther[28], 255);
	TextDrawFont(CaseOther[28], 4);
	TextDrawSetProportional(CaseOther[28], 0);
	TextDrawSetShadow(CaseOther[28], 0);

	CaseOther[29] = TextDrawCreate(227.6493, 89.1893, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[29], 17.0000, 47.4981);
	TextDrawAlignment(CaseOther[29], 1);
	TextDrawColor(CaseOther[29], -25287937);
	TextDrawBackgroundColor(CaseOther[29], 255);
	TextDrawFont(CaseOther[29], 4);
	TextDrawSetProportional(CaseOther[29], 0);
	TextDrawSetShadow(CaseOther[29], 0);

	CaseOther[30] = TextDrawCreate(387.6589, 89.1893, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[30], 17.0000, 47.4981);
	TextDrawAlignment(CaseOther[30], 1);
	TextDrawColor(CaseOther[30], -25287937);
	TextDrawBackgroundColor(CaseOther[30], 255);
	TextDrawFont(CaseOther[30], 4);
	TextDrawSetProportional(CaseOther[30], 0);
	TextDrawSetShadow(CaseOther[30], 0);

	CaseOther[31] = TextDrawCreate(228.3488, 83.2304, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[31], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[31], 1);
	TextDrawColor(CaseOther[31], 336860415);
	TextDrawBackgroundColor(CaseOther[31], 255);
	TextDrawFont(CaseOther[31], 4);
	TextDrawSetProportional(CaseOther[31], 0);
	TextDrawSetShadow(CaseOther[31], 0);

	CaseOther[32] = TextDrawCreate(388.9588, 83.2304, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[32], 15.3399, 16.7800);
	TextDrawAlignment(CaseOther[32], 1);
	TextDrawColor(CaseOther[32], 336860415);
	TextDrawBackgroundColor(CaseOther[32], 255);
	TextDrawFont(CaseOther[32], 4);
	TextDrawSetProportional(CaseOther[32], 0);
	TextDrawSetShadow(CaseOther[32], 0);

	CaseOther[33] = TextDrawCreate(234.2003, 86.0752, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[33], 163.7411, 50.4999);
	TextDrawAlignment(CaseOther[33], 1);
	TextDrawColor(CaseOther[33], 336860415);
	TextDrawBackgroundColor(CaseOther[33], 255);
	TextDrawFont(CaseOther[33], 4);
	TextDrawSetProportional(CaseOther[33], 0);
	TextDrawSetShadow(CaseOther[33], 0);

	CaseOther[34] = TextDrawCreate(230.7496, 91.5708, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[34], 11.0000, 45.1511);
	TextDrawAlignment(CaseOther[34], 1);
	TextDrawColor(CaseOther[34], 336860415);
	TextDrawBackgroundColor(CaseOther[34], 255);
	TextDrawFont(CaseOther[34], 4);
	TextDrawSetProportional(CaseOther[34], 0);
	TextDrawSetShadow(CaseOther[34], 0);

	CaseOther[35] = TextDrawCreate(390.8593, 91.3899, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[35], 11.0000, 45.1511);
	TextDrawAlignment(CaseOther[35], 1);
	TextDrawColor(CaseOther[35], 336860415);
	TextDrawBackgroundColor(CaseOther[35], 255);
	TextDrawFont(CaseOther[35], 4);
	TextDrawSetProportional(CaseOther[35], 0);
	TextDrawSetShadow(CaseOther[35], 0);

	CaseOther[36] = TextDrawCreate(444.4317, 211.1053, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[36], 42.0000, 40.0000);
	TextDrawAlignment(CaseOther[36], 1);
	TextDrawColor(CaseOther[36], -25287937);
	TextDrawBackgroundColor(CaseOther[36], 255);
	TextDrawFont(CaseOther[36], 4);
	TextDrawSetProportional(CaseOther[36], 0);
	TextDrawSetShadow(CaseOther[36], 0);

	CaseOther[37] = TextDrawCreate(447.9981, 214.7165, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[37], 35.0000, 33.0000);
	TextDrawAlignment(CaseOther[37], 1);
	TextDrawColor(CaseOther[37], 336860415);
	TextDrawBackgroundColor(CaseOther[37], 255);
	TextDrawFont(CaseOther[37], 4);
	TextDrawSetProportional(CaseOther[37], 0);
	TextDrawSetShadow(CaseOther[37], 0);

	CaseOther[38] = TextDrawCreate(231.4667, 333.8504, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[38], 30.0000, 30.0000);
	TextDrawAlignment(CaseOther[38], 1);
	TextDrawColor(CaseOther[38], -25287937);
	TextDrawBackgroundColor(CaseOther[38], 255);
	TextDrawFont(CaseOther[38], 4);
	TextDrawSetProportional(CaseOther[38], 0);
	TextDrawSetShadow(CaseOther[38], 0);

	CaseOther[39] = TextDrawCreate(246.0668, 341.9505, "FM");
	TextDrawLetterSize(CaseOther[39], 0.2953, 1.2058);
	TextDrawAlignment(CaseOther[39], 2);
	TextDrawColor(CaseOther[39], -1);
	TextDrawBackgroundColor(CaseOther[39], 255);
	TextDrawFont(CaseOther[39], 0);
	TextDrawSetProportional(CaseOther[39], 1);
	TextDrawSetShadow(CaseOther[39], 0);

	CaseOther[40] = TextDrawCreate(371.1752, 333.8504, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[40], 30.0000, 30.0000);
	TextDrawAlignment(CaseOther[40], 1);
	TextDrawColor(CaseOther[40], -25287937);
	TextDrawBackgroundColor(CaseOther[40], 255);
	TextDrawFont(CaseOther[40], 4);
	TextDrawSetProportional(CaseOther[40], 0);
	TextDrawSetShadow(CaseOther[40], 0);

	CaseOther[41] = TextDrawCreate(232.9651, 112.0615, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[41], 16.0000, 17.0599);
	TextDrawAlignment(CaseOther[41], 1);
	TextDrawColor(CaseOther[41], -25287937);
	TextDrawBackgroundColor(CaseOther[41], 255);
	TextDrawFont(CaseOther[41], 4);
	TextDrawSetProportional(CaseOther[41], 0);
	TextDrawSetShadow(CaseOther[41], 0);

	CaseOther[42] = TextDrawCreate(242.0160, 114.8675, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[42], 34.0000, 21.8299);
	TextDrawAlignment(CaseOther[42], 1);
	TextDrawColor(CaseOther[42], -25287937);
	TextDrawBackgroundColor(CaseOther[42], 255);
	TextDrawFont(CaseOther[42], 4);
	TextDrawSetProportional(CaseOther[42], 0);
	TextDrawSetShadow(CaseOther[42], 0);

	CaseOther[43] = TextDrawCreate(268.6675, 112.0615, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[43], 16.0000, 17.0599);
	TextDrawAlignment(CaseOther[43], 1);
	TextDrawColor(CaseOther[43], -25287937);
	TextDrawBackgroundColor(CaseOther[43], 255);
	TextDrawFont(CaseOther[43], 4);
	TextDrawSetProportional(CaseOther[43], 0);
	TextDrawSetShadow(CaseOther[43], 0);

	CaseOther[44] = TextDrawCreate(235.6320, 119.6940, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[44], 46.4095, 17.0200);
	TextDrawAlignment(CaseOther[44], 1);
	TextDrawColor(CaseOther[44], -25287937);
	TextDrawBackgroundColor(CaseOther[44], 255);
	TextDrawFont(CaseOther[44], 4);
	TextDrawSetProportional(CaseOther[44], 0);
	TextDrawSetShadow(CaseOther[44], 0);

	CaseOther[45] = TextDrawCreate(348.0721, 112.0615, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[45], 16.0000, 17.0599);
	TextDrawAlignment(CaseOther[45], 1);
	TextDrawColor(CaseOther[45], -25287937);
	TextDrawBackgroundColor(CaseOther[45], 255);
	TextDrawFont(CaseOther[45], 4);
	TextDrawSetProportional(CaseOther[45], 0);
	TextDrawSetShadow(CaseOther[45], 0);

	CaseOther[46] = TextDrawCreate(357.1228, 114.8675, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[46], 34.0000, 21.8299);
	TextDrawAlignment(CaseOther[46], 1);
	TextDrawColor(CaseOther[46], -25287937);
	TextDrawBackgroundColor(CaseOther[46], 255);
	TextDrawFont(CaseOther[46], 4);
	TextDrawSetProportional(CaseOther[46], 0);
	TextDrawSetShadow(CaseOther[46], 0);

	CaseOther[47] = TextDrawCreate(383.7744, 112.0615, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[47], 16.0000, 17.0599);
	TextDrawAlignment(CaseOther[47], 1);
	TextDrawColor(CaseOther[47], -25287937);
	TextDrawBackgroundColor(CaseOther[47], 255);
	TextDrawFont(CaseOther[47], 4);
	TextDrawSetProportional(CaseOther[47], 0);
	TextDrawSetShadow(CaseOther[47], 0);

	CaseOther[48] = TextDrawCreate(350.7390, 119.6940, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[48], 46.4095, 17.0200);
	TextDrawAlignment(CaseOther[48], 1);
	TextDrawColor(CaseOther[48], -25287937);
	TextDrawBackgroundColor(CaseOther[48], 255);
	TextDrawFont(CaseOther[48], 4);
	TextDrawSetProportional(CaseOther[48], 0);
	TextDrawSetShadow(CaseOther[48], 0);

	CaseOther[49] = TextDrawCreate(290.0686, 330.9747, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[49], 16.0000, 17.0599);
	TextDrawAlignment(CaseOther[49], 1);
	TextDrawColor(CaseOther[49], -25287937);
	TextDrawBackgroundColor(CaseOther[49], 255);
	TextDrawFont(CaseOther[49], 4);
	TextDrawSetProportional(CaseOther[49], 0);
	TextDrawSetShadow(CaseOther[49], 0);

	CaseOther[50] = TextDrawCreate(299.1195, 323.3612, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[50], 34.0000, 21.8299);
	TextDrawAlignment(CaseOther[50], 1);
	TextDrawColor(CaseOther[50], -25287937);
	TextDrawBackgroundColor(CaseOther[50], 255);
	TextDrawFont(CaseOther[50], 4);
	TextDrawSetProportional(CaseOther[50], 0);
	TextDrawSetShadow(CaseOther[50], 0);

	CaseOther[51] = TextDrawCreate(325.7709, 330.9747, "LD_BEAT:chit");
	TextDrawTextSize(CaseOther[51], 16.0000, 17.0599);
	TextDrawAlignment(CaseOther[51], 1);
	TextDrawColor(CaseOther[51], -25287937);
	TextDrawBackgroundColor(CaseOther[51], 255);
	TextDrawFont(CaseOther[51], 4);
	TextDrawSetProportional(CaseOther[51], 0);
	TextDrawSetShadow(CaseOther[51], 0);

	CaseOther[52] = TextDrawCreate(292.7355, 323.2875, "LD_SPAC:white");
	TextDrawTextSize(CaseOther[52], 46.4095, 17.0200);
	TextDrawAlignment(CaseOther[52], 1);
	TextDrawColor(CaseOther[52], -25287937);
	TextDrawBackgroundColor(CaseOther[52], 255);
	TextDrawFont(CaseOther[52], 4);
	TextDrawSetProportional(CaseOther[52], 0);
	TextDrawSetShadow(CaseOther[52], 0);

	CaseOther[53] = TextDrawCreate(316.7861, 94.3095, "CASE");
	TextDrawLetterSize(CaseOther[53], 0.2581, 1.6000);
	TextDrawAlignment(CaseOther[53], 2);
	TextDrawColor(CaseOther[53], -1);
	TextDrawBackgroundColor(CaseOther[53], 255);
	TextDrawFont(CaseOther[53], 2);
	TextDrawSetProportional(CaseOther[53], 1);
	TextDrawSetShadow(CaseOther[53], 0);

	CaseOther[54] = TextDrawCreate(294.8843, 93.7096, "0");
	TextDrawLetterSize(CaseOther[54], 0.5981, 1.7143);
	TextDrawAlignment(CaseOther[54], 2);
	TextDrawColor(CaseOther[54], -1);
	TextDrawBackgroundColor(CaseOther[54], 255);
	TextDrawFont(CaseOther[54], 2);
	TextDrawSetProportional(CaseOther[54], 1);
	TextDrawSetShadow(CaseOther[54], 0);

	CaseOther[55] = TextDrawCreate(294.4674, 94.2574, "0");
	TextDrawLetterSize(CaseOther[55], 0.3567, 0.7135);
	TextDrawAlignment(CaseOther[55], 2);
	TextDrawColor(CaseOther[55], -1);
	TextDrawBackgroundColor(CaseOther[55], 255);
	TextDrawFont(CaseOther[55], 2);
	TextDrawSetProportional(CaseOther[55], 1);
	TextDrawSetShadow(CaseOther[55], 0);

	CaseOther[56] = TextDrawCreate(339.2702, 94.2574, "0");
	TextDrawLetterSize(CaseOther[56], 0.3567, 0.7135);
	TextDrawAlignment(CaseOther[56], 2);
	TextDrawColor(CaseOther[56], -1);
	TextDrawBackgroundColor(CaseOther[56], 255);
	TextDrawFont(CaseOther[56], 2);
	TextDrawSetProportional(CaseOther[56], 1);
	TextDrawSetShadow(CaseOther[56], 0);

	CaseOther[57] = TextDrawCreate(339.5870, 93.7096, "0");
	TextDrawLetterSize(CaseOther[57], 0.5981, 1.7143);
	TextDrawAlignment(CaseOther[57], 2);
	TextDrawColor(CaseOther[57], -1);
	TextDrawBackgroundColor(CaseOther[57], 255);
	TextDrawFont(CaseOther[57], 2);
	TextDrawSetProportional(CaseOther[57], 1);
	TextDrawSetShadow(CaseOther[57], 0);

	CaseButton[0] = TextDrawCreate(259.0527, 118.1977, "BACK"); // Back;
	TextDrawLetterSize(CaseButton[0], 0.2581, 1.6000);
	TextDrawTextSize(CaseButton[0], 15.0000, 47.0000);
	TextDrawAlignment(CaseButton[0], 2);
	TextDrawColor(CaseButton[0], -1);
	TextDrawBackgroundColor(CaseButton[0], 255);
	TextDrawFont(CaseButton[0], 2);
	TextDrawSetProportional(CaseButton[0], 1);
	TextDrawSetShadow(CaseButton[0], 0);
	TextDrawSetSelectable(CaseButton[0], true);

	CaseButton[1] = TextDrawCreate(374.4761, 118.1977, "NEXT"); // Next;
	TextDrawLetterSize(CaseButton[1], 0.2581, 1.6000);
	TextDrawTextSize(CaseButton[1], 15.0000, 47.0000);
	TextDrawAlignment(CaseButton[1], 2);
	TextDrawColor(CaseButton[1], -1);
	TextDrawBackgroundColor(CaseButton[1], 255);
	TextDrawFont(CaseButton[1], 2);
	TextDrawSetProportional(CaseButton[1], 1);
	TextDrawSetShadow(CaseButton[1], 0);
	TextDrawSetSelectable(CaseButton[1], true);

	CaseButton[2] = TextDrawCreate(316.4525, 325.4396, "BUY"); // Buy;
	TextDrawLetterSize(CaseButton[2], 0.2581, 1.6000);
	TextDrawTextSize(CaseButton[2], 15.0000, 47.0000);
	TextDrawAlignment(CaseButton[2], 2);
	TextDrawColor(CaseButton[2], -1);
	TextDrawBackgroundColor(CaseButton[2], 255);
	TextDrawFont(CaseButton[2], 2);
	TextDrawSetProportional(CaseButton[2], 1);
	TextDrawSetShadow(CaseButton[2], 0);
	TextDrawSetSelectable(CaseButton[2], true);

	CaseButton[3] = TextDrawCreate(352.2666, 313.5914, ""); // Start;
	TextDrawTextSize(CaseButton[3], 70.0000, 70.0000);
	TextDrawAlignment(CaseButton[3], 1);
	TextDrawColor(CaseButton[3], -1);
	TextDrawBackgroundColor(CaseButton[3], -256);
	TextDrawFont(CaseButton[3], 5);
	TextDrawSetProportional(CaseButton[3], 0);
	TextDrawSetShadow(CaseButton[3], 0);
	TextDrawSetSelectable(CaseButton[3], true);
	TextDrawSetPreviewModel(CaseButton[3], 19177);
	TextDrawSetPreviewRot(CaseButton[3], 0.0000, -90.0000, 0.0000, 1.0000);

	CaseButton[4] = TextDrawCreate(455.5733, 222.1425, "LD_BEAT:cross"); // Exit;
	TextDrawTextSize(CaseButton[4], 20.0000, 18.0000);
	TextDrawAlignment(CaseButton[4], 1);
	TextDrawColor(CaseButton[4], -1);
	TextDrawBackgroundColor(CaseButton[4], 255);
	TextDrawFont(CaseButton[4], 4);
	TextDrawSetProportional(CaseButton[4], 0);
	TextDrawSetShadow(CaseButton[4], 0);
	TextDrawSetSelectable(CaseButton[4], true);
	return 1;
}

LoadPlayerTextDrawCase(playerid)
{
	CaseItems[playerid][0] = CreatePlayerTextDraw(playerid, 235.1497, 148.7548, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][0], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][0], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][0], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][0], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][0], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][1] = CreatePlayerTextDraw(playerid, 275.8522, 148.7548, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][1], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][1], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][1], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][1], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][1], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][2] = CreatePlayerTextDraw(playerid, 316.5545, 148.7548, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][2], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][2], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][2], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][2], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][2], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][3] = CreatePlayerTextDraw(playerid, 357.2572, 148.7548, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][3], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][3], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][3], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][3], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][3], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][3], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][4] = CreatePlayerTextDraw(playerid, 235.1497, 189.4622, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][4], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][4], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][4], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][4], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][4], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][5] = CreatePlayerTextDraw(playerid, 275.8522, 189.4622, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][5], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][5], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][5], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][5], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][5], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][5], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][6] = CreatePlayerTextDraw(playerid, 316.5545, 189.4622, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][6], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][6], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][6], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][6], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][6], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][6], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][7] = CreatePlayerTextDraw(playerid, 357.2572, 189.4622, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][7], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][7], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][7], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][7], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][7], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][7], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][8] = CreatePlayerTextDraw(playerid, 235.1497, 230.1694, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][8], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][8], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][8], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][8], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][8], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][8], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][9] = CreatePlayerTextDraw(playerid, 275.8522, 230.1694, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][9], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][9], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][9], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][9], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][9], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][9], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][10] = CreatePlayerTextDraw(playerid, 316.5545, 230.1694, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][10], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][10], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][10], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][10], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][10], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][10], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][10], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][11] = CreatePlayerTextDraw(playerid, 357.2572, 230.1694, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][11], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][11], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][11], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][11], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][11], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][11], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][11], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][12] = CreatePlayerTextDraw(playerid, 235.1497, 270.8771, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][12], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][12], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][12], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][12], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][12], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][12], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][12], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][13] = CreatePlayerTextDraw(playerid, 275.8522, 270.8771, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][13], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][13], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][13], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][13], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][13], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][13], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][13], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][14] = CreatePlayerTextDraw(playerid, 316.5545, 270.8771, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][14], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][14], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][14], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][14], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][14], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][14], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][14], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][14], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItems[playerid][15] = CreatePlayerTextDraw(playerid, 357.2572, 270.8771, "");
	PlayerTextDrawTextSize(playerid, CaseItems[playerid][15], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, CaseItems[playerid][15], 1);
	PlayerTextDrawColor(playerid, CaseItems[playerid][15], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItems[playerid][15], 168430335);
	PlayerTextDrawFont(playerid, CaseItems[playerid][15], 5);
	PlayerTextDrawSetProportional(playerid, CaseItems[playerid][15], 0);
	PlayerTextDrawSetShadow(playerid, CaseItems[playerid][15], 0);
	PlayerTextDrawSetPreviewModel(playerid, CaseItems[playerid][15], 18631);
	PlayerTextDrawSetPreviewRot(playerid, CaseItems[playerid][15], 0.0000, 0.0000, 0.0000, 1.0000);

	CaseItemsCount[playerid][0] = CreatePlayerTextDraw(playerid, 255.9833, 180.3816, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][0], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][0], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][0], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][0], 0);

	CaseItemsCount[playerid][1] = CreatePlayerTextDraw(playerid, 296.8858, 180.3816, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][1], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][1], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][1], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][1], 0);

	CaseItemsCount[playerid][2] = CreatePlayerTextDraw(playerid, 337.7882, 180.3816, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][2], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][2], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][2], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][2], 0);

	CaseItemsCount[playerid][3] = CreatePlayerTextDraw(playerid, 378.6907, 180.3816, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][3], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][3], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][3], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][3], 0);

	CaseItemsCount[playerid][4] = CreatePlayerTextDraw(playerid, 255.9833, 220.9151, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][4], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][4], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][4], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][4], 0);

	CaseItemsCount[playerid][5] = CreatePlayerTextDraw(playerid, 296.8858, 220.9151, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][5], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][5], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][5], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][5], 0);

	CaseItemsCount[playerid][6] = CreatePlayerTextDraw(playerid, 337.7882, 220.9151, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][6], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][6], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][6], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][6], 0);

	CaseItemsCount[playerid][7] = CreatePlayerTextDraw(playerid, 378.6907, 220.9151, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][7], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][7], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][7], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][7], 0);

	CaseItemsCount[playerid][8] = CreatePlayerTextDraw(playerid, 255.9833, 261.4486, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][8], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][8], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][8], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][8], 0);

	CaseItemsCount[playerid][9] = CreatePlayerTextDraw(playerid, 296.8858, 261.4486, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][9], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][9], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][9], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][9], 0);

	CaseItemsCount[playerid][10] = CreatePlayerTextDraw(playerid, 337.7882, 261.4486, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][10], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][10], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][10], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][10], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][10], 0);

	CaseItemsCount[playerid][11] = CreatePlayerTextDraw(playerid, 378.6907, 261.4486, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][11], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][11], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][11], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][11], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][11], 0);

	CaseItemsCount[playerid][12] = CreatePlayerTextDraw(playerid, 255.9833, 301.9819, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][12], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][12], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][12], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][12], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][12], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][12], 0);

	CaseItemsCount[playerid][13] = CreatePlayerTextDraw(playerid, 296.8858, 301.9819, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][13], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][13], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][13], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][13], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][13], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][13], 0);

	CaseItemsCount[playerid][14] = CreatePlayerTextDraw(playerid, 337.7882, 301.9819, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][14], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][14], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][14], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][14], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][14], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][14], 0);

	CaseItemsCount[playerid][15] = CreatePlayerTextDraw(playerid, 378.6907, 301.9819, "_");
	PlayerTextDrawLetterSize(playerid, CaseItemsCount[playerid][15], 0.1782, 0.9570);
	PlayerTextDrawAlignment(playerid, CaseItemsCount[playerid][15], 2);
	PlayerTextDrawColor(playerid, CaseItemsCount[playerid][15], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseItemsCount[playerid][15], 255);
	PlayerTextDrawFont(playerid, CaseItemsCount[playerid][15], 2);
	PlayerTextDrawSetProportional(playerid, CaseItemsCount[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, CaseItemsCount[playerid][15], 0);

	CaseInfo[playerid][0] = CreatePlayerTextDraw(playerid, 316.7861, 118.3087, "TEST"); // Тип Case;
	PlayerTextDrawLetterSize(playerid, CaseInfo[playerid][0], 0.2581, 1.6000);
	PlayerTextDrawAlignment(playerid, CaseInfo[playerid][0], 2);
	PlayerTextDrawColor(playerid, CaseInfo[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseInfo[playerid][0], 255);
	PlayerTextDrawFont(playerid, CaseInfo[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, CaseInfo[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, CaseInfo[playerid][0], 0);

	CaseInfo[playerid][1] = CreatePlayerTextDraw(playerid, 259.0197, 342.1705, "15000"); // Кол-во Flin Money;
	PlayerTextDrawLetterSize(playerid, CaseInfo[playerid][1], 0.1720, 1.3099);
	PlayerTextDrawAlignment(playerid, CaseInfo[playerid][1], 1);
	PlayerTextDrawColor(playerid, CaseInfo[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseInfo[playerid][1], 255);
	PlayerTextDrawFont(playerid, CaseInfo[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, CaseInfo[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, CaseInfo[playerid][1], 0);

	CaseInfo[playerid][2] = CreatePlayerTextDraw(playerid, 373.2265, 342.1705, "30000"); // Кол-во Case;
	PlayerTextDrawLetterSize(playerid, CaseInfo[playerid][2], 0.1720, 1.3099);
	PlayerTextDrawAlignment(playerid, CaseInfo[playerid][2], 3);
	PlayerTextDrawColor(playerid, CaseInfo[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseInfo[playerid][2], 255);
	PlayerTextDrawFont(playerid, CaseInfo[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, CaseInfo[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, CaseInfo[playerid][2], 0);

	CaseInfo[playerid][3] = CreatePlayerTextDraw(playerid, 316.4525, 352.6416, "100_FLIN_MONEY"); // Стоимость Case;
	PlayerTextDrawLetterSize(playerid, CaseInfo[playerid][3], 0.1720, 1.3099);
	PlayerTextDrawAlignment(playerid, CaseInfo[playerid][3], 2);
	PlayerTextDrawColor(playerid, CaseInfo[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, CaseInfo[playerid][3], 255);
	PlayerTextDrawFont(playerid, CaseInfo[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, CaseInfo[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, CaseInfo[playerid][3], 0);
	return 1;
}

CMD:case_stats(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
	if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /case_stats [type]");

	STRING_GLOBAL = "[#] Название\tКоличество\n", STRING_MIN[0] = EOS;

	for(new i = 1; i < sizeof(TypeGiveItemName); i++)
	{
		format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s:\t%d\n", i, TypeGiveItemName[i], CaseStats[params[0]][i]);
		strcat(STRING_GLOBAL, STRING_MIN);
	}

	/*
		Стоимость:
			Уникальный аксессуар, скин и уникальный скин: 25 процентов от стоимости;
			Транспортное средство и уникальное транспортное средство: 50 процентов от стоимости.
	*/

	new
		spent_donate = CaseOpenCount[params[0]] * Case[params[0]][CasePrice],
		received_donate = (CaseStats[params[0]][2] / 2000) + (CaseStats[params[0]][3] / 2000) + CaseStats[params[0]][4] + CaseStats[params[0]][5] + (CaseStats[params[0]][7] / 2000) + (CaseStats[params[0]][8] / 2000) + (CaseStats[params[0]][9] / 2000) + (CaseStats[params[0]][10] / 2000) + (CaseStats[params[0]][11] / 2000);

	format(STRING_MIN, sizeof(STRING_MIN), "\
	Открытий:\t%d\n\
	Потрачено игроком:\t%d Flin Money\n\
	Получено игроком, если все перевести в Flin Money:\t%d Flin Money\n\
	Чистая прибыль:\t%d Flin Money",
	CaseOpenCount[params[0]],
	spent_donate,
	received_donate,
	spent_donate - received_donate);
	strcat(STRING_GLOBAL, STRING_MIN);

	ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Статистика кейсов", STRING_GLOBAL, "ОК", "");
	return 1;
}

CMD:case_system(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7)
        return 1;

    ServerInfo[CaseSystem] = !ServerInfo[CaseSystem];

    SendInfo(playerid, "Вы %s систему кейсов.", (!ServerInfo[CaseSystem]) ? ("отключили") : ("включили"));
    return 1;
}
