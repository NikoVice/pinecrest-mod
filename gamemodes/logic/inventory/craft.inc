#define MAX_CRAFT							61

enum E_CRAFT
{
	cType, // Тип (CRAFT_TYPE_ACCESSORIES, CRAFT_TYPE_CLOTHES, CRAFT_TYPE_CHEMISTRY и CRAFT_TYPE_OTHER);
	cItemsIDx, // ID предмета (значения берем из массива ItemsInfo);
	cResources[5], // ID ресурсов (значения берм из массива ItemsInfo, если нет, то -1);
	cResourcesCount[5], // Количество ресурсов;
	cPrice, // Стоимость 1 попытки;
	cSuccessChance // Шанс успеха;
};

/*

	Ресурсы:
	647 - хлопок
	648 - лен
	649 - металл
	650 - древесина
	651 - камень
	682 - адреналин
*/

new CraftInfo[MAX_CRAFT][E_CRAFT] = {
	{CRAFT_TYPE_ACCESSORIES, 438, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Чемодан Rockstar;
	{CRAFT_TYPE_ACCESSORIES, 445, {647, 648, 649, -1, -1}, {40, 40, 20, -1, -1}, 5000, 1}, // Аксессуар: Бронежилет S. W. A. T;
	{CRAFT_TYPE_ACCESSORIES, 454, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Шляпа волшебника;
	{CRAFT_TYPE_ACCESSORIES, 458, {647, 648, 649, -1, -1}, {40, 40, 20, -1, -1}, 5000, 5}, // Аксессуар: Белый шлем S. W. A. T;
	{CRAFT_TYPE_ACCESSORIES, 459, {647, 648, 649, -1, -1}, {40, 40, 20, -1, -1}, 5000, 5}, // Аксессуар: Черный шлем S. W. A. T;
	{CRAFT_TYPE_ACCESSORIES, 464, {647, 648, -1, -1, -1}, {40, 40, -1, -1, -1}, 5000, 1}, // Аксессуар: Попугай;
	{CRAFT_TYPE_ACCESSORIES, 498, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Маска петуха;
	{CRAFT_TYPE_ACCESSORIES, 501, {647, 648, 649, 650, -1}, {20, 20, 10, 10, -1}, 2500, 1}, // Аксессуар: Тотем;
	{CRAFT_TYPE_ACCESSORIES, 505, {647, 648, 649, 650, -1}, {20, 20, 10, 10, -1}, 2500, 1}, // Аксессуар: Jetpack;
	{CRAFT_TYPE_ACCESSORIES, 525, {647, 648, 649, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Бензочлен;
	{CRAFT_TYPE_ACCESSORIES, 529, {647, 648, -1, -1, -1}, {20, 20, -1, -1, -1}, 2500, 1}, // Аксессуар: Сигара;
	{CRAFT_TYPE_ACCESSORIES, 540, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Корова;
	{CRAFT_TYPE_ACCESSORIES, 555, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Голова CJ;
	{CRAFT_TYPE_ACCESSORIES, 558, {647, 648, 649, -1, -1}, {20, 20, 40, -1, -1}, 10000, 1}, // Аксессуар: Очки ночного видения #1;
	{CRAFT_TYPE_ACCESSORIES, 559, {647, 648, 649, -1, -1}, {20, 20, 40, -1, -1}, 10000, 1}, // Аксессуар: Очки ночного видения #2;
	{CRAFT_TYPE_ACCESSORIES, 576, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Петух;
	{CRAFT_TYPE_ACCESSORIES, 586, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 10000, 1}, // Аксессуар: Нимб;
	{CRAFT_TYPE_ACCESSORIES, 587, {647, 648, 650, -1, -1}, {40, 40, 20, -1, -1}, 10000, 1}, // Аксессуар: Крылья;
	{CRAFT_TYPE_ACCESSORIES, 588, {649, 650, 651, -1, -1}, {20, 10, 10, -1, -1}, 2500, 1}, // Аксессуар: Котелок волшебника;
	{CRAFT_TYPE_ACCESSORIES, 618, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 10000, 1}, // Аксессуар: Костюм бегемота;
	{CRAFT_TYPE_ACCESSORIES, 541, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Красный воздушный шар;
	{CRAFT_TYPE_ACCESSORIES, 542, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Синий воздушный шар;
	{CRAFT_TYPE_ACCESSORIES, 543, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Белый воздушный шар;
	{CRAFT_TYPE_ACCESSORIES, 544, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Разноцветный воздушный шар #1;
	{CRAFT_TYPE_ACCESSORIES, 545, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Разноцветный воздушный шар #2;
	{CRAFT_TYPE_ACCESSORIES, 546, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Разноцветный воздушный шар #3;
	{CRAFT_TYPE_ACCESSORIES, 547, {647, 648, 649, 650, -1}, {40, 40, 20, 20, -1}, 25000, 1}, // Аксессуар: Разноцветный воздушный шар #4;
	{CRAFT_TYPE_ACCESSORIES, 620, {647, 648, 650, -1, -1}, {20, 20, 10, -1, -1}, 2500, 1}, // Аксессуар: Шаурма;
	{CRAFT_TYPE_ACCESSORIES, 508, {649, 650, -1, -1, -1}, {20, 20, -1, -1, -1}, 2500, 10}, // Аксессуар: Квадратная лопата;

	{CRAFT_TYPE_CLOTHES, 27, {647, 648, 649, -1, -1}, {50, 50, 10, -1, -1}, 5000, 1}, // Скин: Construction Worker [ID: 27];
	{CRAFT_TYPE_CLOTHES, 49, {647, 648, -1, -1, -1}, {100, 100, -1, -1, -1}, 25000, 1}, // Скин: Snakehead (Da Nang) [ID: 49];
	{CRAFT_TYPE_CLOTHES, 51, {647, 648, 649, -1, -1}, {50, 50, 10, -1, -1}, 5000, 1}, // Скин: Mountain Biker [ID: 51];
	{CRAFT_TYPE_CLOTHES, 52, {647, 648, 649, -1, -1}, {50, 50, 10, -1, -1}, 5000, 1}, // Скин: Mountain Biker [ID: 52];
	{CRAFT_TYPE_CLOTHES, 62, {647, 648, -1, -1, -1}, {100, 100, -1, -1, -1}, 25000, 1}, // Скин: Colonel Fuhrberger [ID: 62];
	{CRAFT_TYPE_CLOTHES, 74, {647, 648, -1, -1, -1}, {500, 500, -1, -1, -1}, 100000, 1}, // Скин Carl Johnson [ID: 74];
	{CRAFT_TYPE_CLOTHES, 86, {647, 648, -1, -1, -1}, {100, 100, -1, -1, -1}, 25000, 1}, // Скин: Ryder with robbery mask [ID: 86];
	{CRAFT_TYPE_CLOTHES, 103, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 10000, 5}, // Скин: Balla [ID: 103];
	{CRAFT_TYPE_CLOTHES, 105, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 10000, 5}, // Скин: Grove Street Families [ID: 105];
	{CRAFT_TYPE_CLOTHES, 108, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 10000, 5}, // Скин: Los Santos Vagos [ID: 108];
	{CRAFT_TYPE_CLOTHES, 114, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 10000, 5}, // Скин: Varios Los Aztecas [ID: 114];
	{CRAFT_TYPE_CLOTHES, 149, {647, 648, 649, -1, -1}, {100, 100, 10, -1, -1}, 25000, 1}, // Скин: Big Smoke Armored [ID: 149];
	{CRAFT_TYPE_CLOTHES, 153, {647, 648, 649, -1, -1}, {100, 100, 20, -1, -1}, 5000, 1}, // Скин: Construction Worker [ID: 153];
	{CRAFT_TYPE_CLOTHES, 167, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 5000, 1}, // Скин: Cluckin Bell Worker [ID: 167];
	{CRAFT_TYPE_CLOTHES, 168, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 5000, 1}, // Скин: Hotdog/Chilli Dog Vendor [ID: 168];
	{CRAFT_TYPE_CLOTHES, 175, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 10000, 5}, // Скин: San Fierro Rifa [ID: 175];
	{CRAFT_TYPE_CLOTHES, 205, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 5000, 1}, // Скин: Burger Shot Cashier [ID: 205];
	{CRAFT_TYPE_CLOTHES, 209, {647, 648, -1, -1, -1}, {50, 50, -1, -1, -1}, 5000, 1}, // Скин: Oriental Noodle stand vendor [ID: 209];
	{CRAFT_TYPE_CLOTHES, 260, {647, 648, 649, -1, -1}, {50, 50, 10, -1, -1}, 5000, 1}, // Скин: Construction Worker [ID: 260];

	{CRAFT_TYPE_CHEMISTRY, 630, {649, 650, 651, -1, -1}, {10, 10, 10, -1, -1}, 500, 50}, // Канистра;
	{CRAFT_TYPE_CHEMISTRY, 632, {647, 648, 650, -1, -1}, {10, 10, 10, -1, -1}, 500, 50}, // Аптечка;
	{CRAFT_TYPE_CHEMISTRY, 683, {650, 682, -1, -1, -1}, {10, 10, -1, -1, -1}, 1000, 50}, // Укол адреналина;
	{CRAFT_TYPE_CHEMISTRY, 708, {649, 650, 651, -1, -1}, {20, 20, 10, -1, -1}, 5000, 25}, // Смазка для разгона видеокарты;
	{CRAFT_TYPE_CHEMISTRY, 709, {647, 648, 695, -1, -1}, {20, 20, 10, -1, -1}, 2500, 50}, // Охлаждающая жидкость для видеокарты;

	{CRAFT_TYPE_CHEMISTRY, 710, {649, 650, 651, -1, -1}, {20, 20, 10, -1, -1}, 5000, 25}, // Микросхема для станка;
	{CRAFT_TYPE_CHEMISTRY, 711, {647, 648, 695, -1, -1}, {10, 10, 10, -1, -1}, 2500, 50}, // Балончик со сжатым воздухом;
	{CRAFT_TYPE_CHEMISTRY, 712, {647, 648, 695, -1, -1}, {10, 10, 10, -1, -1}, 2500, 50}, // Смазка для станка;
	{CRAFT_TYPE_CHEMISTRY, 713, {638, 639, 695, -1, -1}, {2, 2, 2, -1, -1}, 1000, 50}, // Бизнес-ланч;

	{CRAFT_TYPE_OTHER, 631, {649, 650, 651, -1, -1}, {10, 10, 10, -1, -1}, 500, 50}, // Рем. комплект;
	{CRAFT_TYPE_OTHER, 633, {647, 648, -1, -1, -1}, {10, 10, -1, -1, -1}, 500, 50}, // Маска;
	{CRAFT_TYPE_OTHER, 636, {647, 648, -1, -1, -1}, {10, 10, -1, -1, -1}, 500, 50}, // Веревка;
	{CRAFT_TYPE_OTHER, 637, {649, 650, 651, -1, -1}, {10, 10, 10, -1, -1}, 1000, 10} // Отмычка;
};

GetMaxCraftList()
{
	for(new i = 0; i < MAX_CRAFT; i++) MAX_CRAFT_LIST[CraftInfo[i][cType]]++;
	for(new i = 0; i < CRAFT_TYPE_ALL; i++) MAX_CRAFT_LIST[i] = floatround(MAX_CRAFT_LIST[i] / 8, floatround_ceil);
	return 1;
}

ShowPlayerCraft(playerid, idx, items_idx = 0)
{
	new count, type = p_temp[playerid][craft_type];
	switch(idx)
	{
		case CRAFT_TYPE_SHOW_BUTTON:
		{
			p_temp[playerid][craft_items_list][p_temp[playerid][craft_list]] = p_temp[playerid][craft_last_idx];
			for(new i = p_temp[playerid][craft_last_idx]; i < MAX_CRAFT; i++)
			{
				if(CraftInfo[i][cType] != type) continue;
				PlayerTextDrawShow(playerid, PTD_CraftButtonItems[playerid][count]);
				PlayerTextDrawShow(playerid, PTD_CraftButtonItemsName[playerid][count]);
				PlayerTextDrawSetString(playerid, PTD_CraftButtonItemsName[playerid][count], ItemsInfo[CraftInfo[i][cItemsIDx]][iName]);
				p_temp[playerid][p_listitem][count] = i;
				p_temp[playerid][craft_last_idx] = i + 1;
				count++;
				if(count == 8) break;
			}
		}
		case CRAFT_TYPE_SHOW_RESOURCES:
		{
			new listitem = p_temp[playerid][craft_idx];
			if(listitem == -1)
			{
				for(new i = 0; i < 5; i++)
				{
					PlayerTextDrawSetPreviewModel(playerid, PTD_CraftResources[playerid][i], 18631);
					PlayerTextDrawShow(playerid, PTD_CraftResources[playerid][i]);
					PlayerTextDrawShow(playerid, PTD_CraftResourcesInfo[playerid][i]);
					PlayerTextDrawSetString(playerid, PTD_CraftResourcesInfo[playerid][i], "0/0");
				}
			}
			else
			{
				new res_idx, res_count;
				for(new i = 0; i < 5; i++)
				{
					res_idx = CraftInfo[listitem][cResources][i];
					res_count = CraftInfo[listitem][cResourcesCount][i];
					if(res_idx == -1 || res_count == -1) continue;
					PlayerTextDrawSetPreviewModel(playerid, PTD_CraftResources[playerid][i], ItemsInfo[CraftInfo[listitem][cResources][i]][iModel]);
					PlayerTextDrawShow(playerid, PTD_CraftResources[playerid][i]);
					PlayerTextDrawShow(playerid, PTD_CraftResourcesInfo[playerid][i]);
					STRING_GLOBAL[0] = EOS;
					f(STRING_GLOBAL, "%d/%d", GetInventoryAmount(playerid, res_idx), res_count * p_temp[playerid][craft_count]);
					PlayerTextDrawSetString(playerid, PTD_CraftResourcesInfo[playerid][i], STRING_GLOBAL);
				}
			}
		}
		case CRAFT_TYPE_SHOW_ITEMS:
		{
			PlayerTextDrawHide(playerid, PTD_CraftMain[playerid][18]);
			if(items_idx == 0)
			{
				PlayerTextDrawSetPreviewModel(playerid, PTD_CraftMain[playerid][18], 18631);
				PlayerTextDrawSetPreviewRot(playerid, PTD_CraftMain[playerid][18], 0.0000, 0.0000, 0.0000, 1.0000);
				UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_MAIN);
			}
			else
			{
				PlayerTextDrawSetPreviewModel(playerid, PTD_CraftMain[playerid][18], ItemsInfo[items_idx][iModel]);
				PlayerTextDrawSetPreviewRot(playerid, PTD_CraftMain[playerid][18], ItemsInfo[items_idx][iObjectPos][0], ItemsInfo[items_idx][iObjectPos][1], ItemsInfo[items_idx][iObjectPos][2], ItemsInfo[items_idx][iObjectPos][3]);
				UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_MAIN, items_idx);
			}
			PlayerTextDrawShow(playerid, PTD_CraftMain[playerid][18]);
		}
	}
	return 1;
}

UpdatePlayerCraft(playerid, idx, items_idx = 0)
{
	if(p_temp[playerid][TextDrawCraft] == false) return 1;
	switch(idx)
	{
		case CRAFT_TYPE_UPDATE_LIST:
		{
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, "%d/%d", p_temp[playerid][craft_list] + 1, MAX_CRAFT_LIST[p_temp[playerid][craft_type]] + 1);
			PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][0], STRING_GLOBAL);
		}
		case CRAFT_TYPE_UPDATE_COUNT:
		{
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, "%d", p_temp[playerid][craft_count]);
			PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][4], STRING_GLOBAL);

			new items_idx = p_temp[playerid][craft_idx], res_idx, res_count;
			if(items_idx != -1)
			{
				for(new i = 0; i < 5; i++)
				{
					res_idx = CraftInfo[items_idx][cResources][i];
					res_count = CraftInfo[items_idx][cResourcesCount][i];
					if(res_idx == -1 || res_count == -1) continue;
					STRING_GLOBAL[0] = EOS;
					f(STRING_GLOBAL, "%d/%d", GetInventoryAmount(playerid, res_idx), res_count * p_temp[playerid][craft_count]);
					PlayerTextDrawSetString(playerid, PTD_CraftResourcesInfo[playerid][i], STRING_GLOBAL);
				}
			}
		}
		case CRAFT_TYPE_UPDATE_MAIN:
		{
			if(items_idx == 0)
			{
				PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][1], "Нет");
				PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][3], "ШАНС УСПЕХА:_~y~0%");
				PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][2], "Стоимость:_~r~0$");
			}
			else
			{
				PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][1], ItemsInfo[items_idx][iName]);
				items_idx = p_temp[playerid][craft_idx];
				new max_value = CraftInfo[items_idx][cSuccessChance];
				STRING_GLOBAL[0] = EOS;
				if(p_info[playerid][p_vip] == 3) f(STRING_GLOBAL, "ШАНС УСПЕХА:_~y~%d%%~r~ (+%d%% BY GOLD VIP)", max_value, max_value);
				else f(STRING_GLOBAL, "ШАНС УСПЕХА:_~y~%d%", max_value);
				PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][3], STRING_GLOBAL);
				new price = CraftInfo[items_idx][cPrice];
				if(p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) price = price / 2;
				STRING_GLOBAL[0] = EOS;
				f(STRING_GLOBAL, "Стоимость:_~r~%d$", p_temp[playerid][craft_count] * price);
				PlayerTextDrawSetString(playerid, PTD_CraftInfo[playerid][2], STRING_GLOBAL);
			}
		}
	}
	return 1;
}

HidePlayerCraft(playerid, idx)
{
	if(p_temp[playerid][TextDrawCraft] == false) return 1;
	switch(idx)
	{
		case CRAFT_TYPE_HIDE_BUTTON:
		{
			for(new i = 0; i < 100; i++)
			{
				p_temp[playerid][p_listitem][i] = -1;
				if(i < 8)
				{
					PlayerTextDrawHide(playerid, PTD_CraftButtonItems[playerid][i]);
					PlayerTextDrawHide(playerid, PTD_CraftButtonItemsName[playerid][i]);
				}
			}
		}
		case CRAFT_TYPE_HIDE_RESOURCES:
		{
			for(new i = 0; i < 5; i++)
			{
				PlayerTextDrawHide(playerid, PTD_CraftResources[playerid][i]);
				PlayerTextDrawHide(playerid, PTD_CraftResourcesInfo[playerid][i]);
			}
		}
	}
	return 1;
}

StartPlayerCraft(playerid, idx)
{
	if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы уже изготавливаете предмет.");
	new items_idx, items_count, items_price;
	for(new i = 0; i < 5; i++)
	{
		if(CraftInfo[idx][cResources][i] != -1)
		{
			items_idx = CraftInfo[idx][cResources][i], items_count = CraftInfo[idx][cResourcesCount][i], items_price = CraftInfo[idx][cPrice];
			if(GetInventoryAmount(playerid, items_idx) < items_count) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"У Вас нет столько \"%s\".", ItemsInfo[items_idx][iName]);
		}
	}
	if(p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1) items_price = items_price / 2;
	if(p_info[playerid][cash] < items_price) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"У Вас нет столько денег. Используйте /donate");
	if(GetInventoryFreeItems(playerid, items_idx) == 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"В инвентаре нет свободного места.");
	for(new i = 0; i < 5; i++)
	{
		if(CraftInfo[idx][cResources][i] != -1)
		{
			items_idx = CraftInfo[idx][cResources][i], items_count = CraftInfo[idx][cResourcesCount][i];
			GivePlayerInventory(playerid, items_idx, -items_count);
		}
	}
	items_idx = CraftInfo[idx][cItemsIDx];
	SetPlayerMoney(playerid, -items_price, true, "начал создание <%s> <%d>", ItemsInfo[items_idx][iName], items_idx);
	SendMes(playerid, COLOR_GREEN, "[КРАФТ]: "W"Вы начали создание \"%s\". Количество: %d. Стоимость: %d$.", ItemsInfo[items_idx][iName], p_temp[playerid][craft_count], items_price);
	Fix_TogglePlayerControllable(playerid, false);
	p_temp[playerid][craft_timer] = 15;
	return 1;
}

CheckPlayerCraft(playerid)
{
	new idx = p_temp[playerid][craft_idx];
	if(idx == -1) return 1;
	new items_idx = CraftInfo[idx][cItemsIDx], max_value = CraftInfo[idx][cSuccessChance];
	if(p_info[playerid][p_vip] == 3) max_value = max_value * 2;
	if(random(100) + 1 <= max_value)
	{
		if(GetInventoryFreeItems(playerid, items_idx) == 0) return SendError(playerid, "В инвентаре нет свободного места.");
		SendMes(playerid, COLOR_YELLOW, "[КРАФТ]: "W"Вы создали \"%s\". Шанс успеха: %d процент(-а/-ов).", ItemsInfo[items_idx][iName], max_value);
		GivePlayerInventory(playerid, items_idx);
	}
	else SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"У Вас не получилось создать \"%s\". Шанс успеха: %d процент(-а/-ов).", ItemsInfo[items_idx][iName], max_value);
	p_temp[playerid][craft_count]--;
	if(p_temp[playerid][craft_count] > 0) StartPlayerCraft(playerid, idx);
	else p_temp[playerid][craft_count] = 1;
	UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_COUNT);
	Fix_TogglePlayerControllable(playerid, true);
	return 1;
}

Craft_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(p_temp[playerid][TextDrawCraft] == false) return 1;

	new type = p_temp[playerid][craft_type];

	if(playertextid == PTD_CraftMain[playerid][1]) // Закрыть;
	{
		if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы не можете закрыть крафт пока изготавливаете предмет.");
		HideTextDrawForPlayer(playerid, TD_ID_CRAFT);
		return 1;
	}
	else if(playertextid == PTD_CraftMain[playerid][14]) // Предыдущая страница;
	{
		if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы не можете перейти на другую страницу пока изготавливаете предмет.");
		if(p_temp[playerid][craft_list] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы находитесь на первой странице.");
		p_temp[playerid][craft_list]--;
		p_temp[playerid][craft_idx] = -1;
		p_temp[playerid][craft_last_idx] = p_temp[playerid][craft_items_list][p_temp[playerid][craft_list]];

		HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_BUTTON);
		HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_RESOURCES);
		ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_BUTTON);
		ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_RESOURCES);
		ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_ITEMS);
		UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_LIST);
		return 1;
	}
	else if(playertextid == PTD_CraftMain[playerid][15]) // Следующая страница;
	{
		if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы не можете перейти на другую страницу пока изготавливаете предмет.");
		if(p_temp[playerid][craft_list] == MAX_CRAFT_LIST[type]) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы находитесь на последней странице.");
		p_temp[playerid][craft_list]++;
		p_temp[playerid][craft_idx] = -1;
		HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_BUTTON);
		HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_RESOURCES);
		ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_BUTTON);
		ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_RESOURCES);
		ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_ITEMS);
		UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_LIST);
		return 1;
	}
	else if(playertextid == PTD_CraftMain[playerid][18]) // Предмет;
	{
		new idx = p_temp[playerid][craft_idx];
		if(idx == -1) return 1;
		new items_idx = CraftInfo[idx][cItemsIDx];
		STRING_GLOBAL[0] = EOS;
		f(STRING_GLOBAL, ""W"\
		Название: %s\n\n\
		Описание:\n\n\
		%s", ItemsInfo[items_idx][iName], ItemsInfo[items_idx][iInfo]);
		ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"#cLIGHTRED"}[КРАФТ]:"W" Информация о предмете", STRING_GLOBAL, "ОК", "");
		return 1;
	}
	else if(playertextid == PTD_CraftMain[playerid][21]) // Количество;
	{
		if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы не можете изменить количество пока изготавливаете предмет.");
		ShowPlayerDialog(playerid, D_CRAFT_COUNT, DIALOG_STYLE_INPUT, "{"#cLIGHTRED"}[КРАФТ]:"W" Количество", ""W"Введите количество предмета, которое хотите изготовить:", "Далее", "Отмена");
		return 1;
	}
	else if(playertextid == PTD_CraftMain[playerid][22]) // Изготовить;
	{
		if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы уже изготавливаете предмет.");
		new items_idx = p_temp[playerid][craft_idx];
		if(items_idx == -1) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы ничего не выбрали.");
		StartPlayerCraft(playerid, items_idx);
		return 1;
	}

	for(new i = 0; i < 8; i++)
	{
		if(playertextid == PTD_CraftButtonItems[playerid][i])
		{
			if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы не можете выбрать другой предмет пока изготавливаете предмет.");
			new idx = p_temp[playerid][p_listitem][i];
			if(idx == -1) return 1;
			p_temp[playerid][craft_idx] = idx;
			HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_RESOURCES);
			ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_RESOURCES);
			ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_ITEMS, CraftInfo[idx][cItemsIDx]);
			return 1;
		}
		if(i < 5 && playertextid == PTD_CraftResources[playerid][i])
		{
			new idx = p_temp[playerid][craft_idx];
            if(idx == -1) return 1;
            new res_idx = CraftInfo[idx][cResources][i];
			if(res_idx == -1) return 1;
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, ""W"\
			Название: %s\n\n\
			Описание:\n\n\
			%s", ItemsInfo[res_idx][iName], ItemsInfo[res_idx][iInfo]);
			ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"#cLIGHTRED"}[КРАФТ]:"W" Информация о предмете", STRING_GLOBAL, "ОК", "");
			return 1;
		}
		if(i > 3 && playertextid == PTD_CraftMain[playerid][i])
		{
			if(p_temp[playerid][craft_timer] > 0) return SendMes(playerid, COLOR_DARKORANGE, "[КРАФТ]: "W"Вы не можете изменить тип предмета пока изготавливаете его.");
			p_temp[playerid][craft_type] = i - 4;
			p_temp[playerid][craft_idx] = -1; // ID из массива CraftInfo;
			p_temp[playerid][craft_last_idx] = 0; // Последняя стройка, которая вывелась в списке из массива CraftInfo;
			p_temp[playerid][craft_list] = 0; // Номер страницы;
			HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_BUTTON);
			HidePlayerCraft(playerid, CRAFT_TYPE_HIDE_RESOURCES);
			ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_BUTTON);
			ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_RESOURCES);
			ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_ITEMS);
			UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_LIST);
			return 1;
		}
	}
	return 1;
}

CMD:craft_new(playerid, params[])
{
	if(SRV_ID) return 1;
	ShowTextDrawForPlayer(playerid, TD_ID_CRAFT);
	return 1;
}
