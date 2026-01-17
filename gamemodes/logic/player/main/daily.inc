GetPlayerDailyRewardModel(playerid, idx, i)
{
	switch(p_info[playerid][daily_reward_type][i])
	{
		case DAILY_TYPE_EXP:
		{
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], 1277);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], 0.0000, 0.0000, 180.0000, 1.0000);
		}
		case DAILY_TYPE_MONEY:
		{
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], 1212);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], 90.0000, 0.0000, 0.0000, 1.0000);
		}
		case DAILY_TYPE_DONATE:
		{
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], 1274);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], 0.0000, 0.0000, 0.0000, 1.5000);
		}
		case DAILY_TYPE_VIP:
		{
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], 1247);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], 0.0000, 0.0000, 0.0000, 1.5000);
		}
		case DAILY_TYPE_SKIN:
		{
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], ItemsInfo[p_info[playerid][daily_reward_idx][i]][iModel]);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], 0.0000, 0.0000, 0.0000, 1.5500);
		}
		case DAILY_TYPE_ACC, DAILY_TYPE_INVENTORY:
		{
			new temp_idx = p_info[playerid][daily_reward_idx][i];
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], ItemsInfo[temp_idx][iModel]);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], ItemsInfo[temp_idx][iObjectPos][0], ItemsInfo[temp_idx][iObjectPos][1], ItemsInfo[temp_idx][iObjectPos][2], ItemsInfo[temp_idx][iObjectPos][3] + 0.60);
		}
		case DAILY_TYPE_VEHICLE:
		{
			PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][idx], p_info[playerid][daily_reward_idx][i]);
			PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][idx], -25.0000, 0.0000, 45.0000, 1.2500);
		}
	}
	return 1;
}

GetPlayerDailyRewardInfo(playerid, idx)
{
	new str[64];
	switch(p_info[playerid][daily_reward_type][idx])
	{
		case DAILY_TYPE_EXP: f(str, "%d EXP", p_info[playerid][daily_reward_idx][idx]);
		case DAILY_TYPE_MONEY: f(str, "%d$", p_info[playerid][daily_reward_idx][idx]);
		case DAILY_TYPE_DONATE: f(str, "%d Flin Money", p_info[playerid][daily_reward_idx][idx]);
		case DAILY_TYPE_VIP: f(str, "VIP: %s, Дней: %d", TypeVIPName[p_info[playerid][daily_reward_idx][idx]], p_info[playerid][daily_reward_idx_count][idx]);
		case DAILY_TYPE_SKIN, DAILY_TYPE_ACC, DAILY_TYPE_INVENTORY: f(str, "%s", ItemsInfo[p_info[playerid][daily_reward_idx][idx]][iName]);
		case DAILY_TYPE_VEHICLE: f(str, "%s", GetVehicleName(INVALID_VEHICLE_ID, p_info[playerid][daily_reward_idx][idx]));
	}
	return str;
}

GivePlayerDailyReward(playerid, idx, i)
{
	if(p_info[playerid][daily_reward][idx] == 1) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]:"W" Вы уже забрали эту награду.");
	if(p_info[playerid][daily_days] != idx + 1) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]:"W" Данная награда доступна на %d дне.", idx + 1);
	if(p_info[playerid][daily_days] == idx + 1 && p_info[playerid][daily_today] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]:"W" Время на получение награды истекло.");

	new daily_reward_type_list[8] = {TYPE_GIVE_ITEM_EXP, TYPE_GIVE_ITEM_MONEY, TYPE_GIVE_ITEM_DONATE, TYPE_GIVE_ITEM_VIP, TYPE_GIVE_ITEM_SKIN, TYPE_GIVE_ITEM_ACCESSORIES, TYPE_GIVE_ITEM_VEHICLE, TYPE_GIVE_ITEM_INVENTORY}, type = daily_reward_type_list[p_info[playerid][daily_reward_type][idx] - 1];

	if(type == TYPE_GIVE_ITEM_INVENTORY) SetPlayerItem(playerid, 10, p_info[playerid][ID], type, p_info[playerid][daily_reward_idx_count][idx], p_info[playerid][daily_reward_idx][idx]);
	else SetPlayerItem(playerid, 10, p_info[playerid][ID], type, p_info[playerid][daily_reward_idx][idx], p_info[playerid][daily_reward_idx_count][idx]);

	p_info[playerid][daily_reward][idx] = 1;
	p_info[playerid][daily_today] = 2;
	MysqlUpdatePlayerInt(playerid, "daily_today", p_info[playerid][daily_today]);

	PlayerTextDrawSetString(playerid, PTD_DailyRewardText[playerid][i], p_info[playerid][daily_reward][idx] == 0 ? "ЗАБРАТЬ" : "ЗАБРАНА");

	UpdatePlayerDaily(playerid, DAILY_TYPE_UPDATE_TIME);

	SavePlayerDaily(playerid, DAILY_TYPE_REWARD, idx);
	return 1;
}

ShowPlayerDaily(playerid)
{
	new count;
	p_temp[playerid][daily_items_list_reward][p_temp[playerid][daily_list]] = p_temp[playerid][daily_last_idx];
	for(new i = p_temp[playerid][daily_last_idx]; i < MAX_DAILY_REWARD; i++)
	{
		PlayerTextDrawShow(playerid, PTD_DailyRewardMain[playerid][count]);
		PlayerTextDrawShow(playerid, PTD_DailyRewardButton[playerid][count]);
		PlayerTextDrawShow(playerid, PTD_DailyRewardText[playerid][count]);
		PlayerTextDrawSetString(playerid, PTD_DailyRewardText[playerid][count], p_info[playerid][daily_reward][i] == 0 ? "ЗАБРАТЬ" : "ЗАБРАНА");
		GetPlayerDailyRewardModel(playerid, count, i);
		PlayerTextDrawShow(playerid, PTD_DailyRewardModel[playerid][count]);
		PlayerTextDrawShow(playerid, PTD_DailyRewardInfo[playerid][count]);
		STRING_GLOBAL[0] = EOS;
		f(STRING_GLOBAL, "%d день~n~~g~%s", i + 1, GetPlayerDailyRewardInfo(playerid, i));
		PlayerTextDrawSetString(playerid, PTD_DailyRewardInfo[playerid][count], STRING_GLOBAL);
		p_temp[playerid][p_listitem][count] = i;
		p_temp[playerid][daily_last_idx] = i + 1;
		count++;
		if(count == 3) break;
	}
	return 1;
}

UpdatePlayerDaily(playerid, idx)
{
	if(p_temp[playerid][TextDrawDaily] == false) return 1;
	switch(idx)
	{
		case DAILY_TYPE_UPDATE_TIME:
		{
			PlayerTextDrawSetString(playerid, PTD_DailyInfo[playerid][0], GetPlayerDailyTime(playerid));
		}
		case DAILY_TYPE_UPDATE_LIST:
		{
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, "%d/%d", p_temp[playerid][daily_list] + 1, MAX_DAILY_LIST_REWARD);
			PlayerTextDrawSetString(playerid, PTD_DailyInfo[playerid][1], STRING_GLOBAL);
		}
	}
	return 1;
}

GetPlayerDailyTime(playerid)
{
	new str[128], time = p_info[playerid][daily_time];
	if(time < MAX_DAILY_PLAYER_TIME) format(str, sizeof(str), "ДО ПОЛУЧЕНИЯ НАГРАДЫ ЗА %d ДЕНЬ: ~g~%s", p_info[playerid][daily_days] + 1, ConvertTime(MAX_DAILY_PLAYER_TIME - time));
	else if(p_info[playerid][daily_today] == 1) format(str, sizeof(str), "МОЖНО ЗАБРАТЬ НАГРАДУ ЗА ~g~%d ДЕНЬ", p_info[playerid][daily_days]);
	else format(str, sizeof(str), "ЗА ~g~%d ДЕНЬ~w~ УЖЕ ЗАБРАНЫ НАГРАДЫ", p_info[playerid][daily_days]);
	return str;
}

HidePlayerDaily(playerid)
{
	if(p_temp[playerid][TextDrawDaily] == false) return 1;
	for(new i = 0; i < 100; i++)
	{
		p_temp[playerid][p_listitem][i] = -1;
		if(i < 3)
		{
			PlayerTextDrawHide(playerid, PTD_DailyRewardMain[playerid][i]);
			PlayerTextDrawHide(playerid, PTD_DailyRewardButton[playerid][i]);
			PlayerTextDrawHide(playerid, PTD_DailyRewardText[playerid][i]);
			PlayerTextDrawHide(playerid, PTD_DailyRewardModel[playerid][i]);
			PlayerTextDrawHide(playerid, PTD_DailyRewardInfo[playerid][i]);
		}
	}
	return 1;
}

SavePlayerDaily(playerid, type, first_parameter = -1)
{
	switch(type)
	{
		case DAILY_TYPE_INFO:
		{
			STRING_GLOBAL[0] = EOS;
			format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `battle_lvl` = %d, `battle_lvl_task` = %d, `battle_info` = '%d|%d|%d|%d|%d' WHERE `id` = %d",
			p_info[playerid][battle_lvl], p_info[playerid][battle_lvl_task], p_info[playerid][battle_info][0], p_info[playerid][battle_info][1], p_info[playerid][battle_info][2],
			p_info[playerid][battle_info][3], p_info[playerid][battle_info][4], p_info[playerid][ID]);
			mysql_tquery(con_bd, STRING_GLOBAL);
		}
		case DAILY_TYPE_REWARD:
		{
			STRING_GLOBAL[0] = EOS;
			format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `daily_reward` SET `reward_type` = %d, `reward_idx` = %d, `reward_idx_count` = %d, `status` = %d WHERE `user_id` = %d AND `reward_id` = %d",
			p_info[playerid][daily_reward_type][first_parameter], p_info[playerid][daily_reward_idx][first_parameter], p_info[playerid][daily_reward_idx_count][first_parameter], p_info[playerid][daily_reward][first_parameter], p_info[playerid][ID], first_parameter);
			mysql_tquery(con_bd, STRING_GLOBAL);
		}
	}
	return 1;
}

forward OnPlayerLoadDaily(playerid);
public OnPlayerLoadDaily(playerid)
{
	new rows;
	cache_get_row_count(rows);
	if(rows)
	{
		for(new i; i < MAX_DAILY_REWARD; i++)
		{
			cache_get_value_name_int(i, "reward_type", p_info[playerid][daily_reward_type][i]);
			cache_get_value_name_int(i, "reward_idx", p_info[playerid][daily_reward_idx][i]);
			cache_get_value_name_int(i, "reward_idx_count", p_info[playerid][daily_reward_idx_count][i]);
			cache_get_value_name_int(i, "status", p_info[playerid][daily_reward][i]);
		}
	}
	if(rows < MAX_DAILY_REWARD)
	{
		new scdplayerid = p_info[playerid][ID], neededRewardCount = MAX_DAILY_REWARD - rows;
		for(new i = 0; i < neededRewardCount; i++)
		{
			STRING_GLOBAL[0] = EOS;
			format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `daily_reward` (`user_id`, `reward_id`, `reward_type`, `reward_idx`, `reward_idx_count`, `status`) VALUES (%d, %d, 0, 0, 0, 0)",
			scdplayerid, rows);
			mysql_tquery(con_bd, STRING_GLOBAL);
			p_info[playerid][daily_reward_type][i] = 0;
			p_info[playerid][daily_reward_idx][i] = 0;
			p_info[playerid][daily_reward_idx_count][i] = 0;
			p_info[playerid][daily_reward][i] = 0;
			rows++;
		}
	}
	if(p_info[playerid][daily_update_reward] == 1)
	{
		for(new i = 0; i < MAX_DAILY_REWARD; i++) GetPlayerDailyReward(playerid, i);
		p_info[playerid][daily_update_reward] = 0;
		STRING_GLOBAL[0] = EOS;
		mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `daily_update_reward` = %d WHERE `id` = %d",
		p_info[playerid][daily_update_reward], p_info[playerid][ID]);
		mysql_tquery(con_bd, STRING_GLOBAL);
	}
	else
	{
		for(new i = 0; i < MAX_DAILY_REWARD; i++) if(p_info[playerid][daily_reward_type][i] == 0) GetPlayerDailyReward(playerid, i);
	}
	return 1;
}

/*
	[1] - Bronze рулетка | Деньги (10.000$ - 25.000$) | Донат (7 - 15) | Очки опыта (10 - 20);
	[2] - Bronze рулетка | Деньги (10.000$ - 25.000$) | Донат (7 - 15) | Очки опыта (10 - 20);
	[3] - Bronze рулетка | Деньги (10.000$ - 25.000$) | Донат (7 - 15) | Очки опыта (10 - 20);
	[4] - Деньги (25.000$ - 50.000$) | Донат (15 - 30) | Аксессуар из Bronze рулетки;
	[5] - Транспорт Nope класса | Одежда от 25.000$ до 125.000$ | VIP Bronze - 1 день;
	[6] - Аксессуар из Bronze рулетки | Silver рулетка | VIP Silver - 1 день;
	[7] - Аксессуар из Bronze рулетки | Gold рулетка | VIP Gold - 1 день;
*/

GetPlayerDailyReward(playerid, idx)
{
	switch(idx)
	{
		case 0, 1, 2: // День #1 | День #2 | День #3;
		{
			switch(random(100))
			{
				case 0 .. 29:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_INVENTORY;
					p_info[playerid][daily_reward_idx][idx] = 642;
					p_info[playerid][daily_reward_idx_count][idx] = 1;
				}
				case 30 .. 59:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_MONEY;
					p_info[playerid][daily_reward_idx][idx] = RandomEx(10000, 25000);
				}
				case 60 .. 89:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_EXP;
					p_info[playerid][daily_reward_idx][idx] = RandomEx(3, 5);
				}
				default:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_DONATE;
					p_info[playerid][daily_reward_idx][idx] = RandomEx(7, 15);
				}
			}
		}
		case 3: // День #4;
		{
			switch(random(100))
			{
				case 0 .. 39:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_MONEY;
					p_info[playerid][daily_reward_idx][idx] = RandomEx(25000, 50000);
				}
				case 40 .. 79:
				{
					new accessories_daily_prize[29] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585, 596, 598, 599, 600, 601, 602, 603, 607}; // 250000$;
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_ACC;
					p_info[playerid][daily_reward_idx][idx] = accessories_daily_prize[random(sizeof(accessories_daily_prize))];
				}
				default:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_DONATE;
					p_info[playerid][daily_reward_idx][idx] = RandomEx(15, 30);
				}
			}
		}
		case 4: // День #5;
		{
			switch(random(100))
			{
				case 0 .. 59:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_VIP;
					p_info[playerid][daily_reward_idx][idx] = 0;
					p_info[playerid][daily_reward_idx_count][idx] = 1;
				}
				case 60 .. 79:
				{
					new vehicle_daily_prize[40] = {401, 404, 410, 419, 422, 436, 439, 458, 462, 466, 471, 473, 474, 478, 479, 481, 491, 492, 500, 507, 509, 510, 516, 517, 518, 526, 527, 529, 540, 542, 543, 545, 546, 547, 549, 585, 600, 604, 605, 473}; // От 25000$ до 100000$;
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_VEHICLE;
					p_info[playerid][daily_reward_idx][idx] = vehicle_daily_prize[random(sizeof(vehicle_daily_prize))];
				}
				default:
				{
					new skin_daily_prize[17] = {2, 7, 18, 24, 45, 67, 97, 101, 142, 144, 146, 154, 156, 176, 177, 220, 224}; // От 25000$ до 75000$;
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_SKIN;
					p_info[playerid][daily_reward_idx][idx] = skin_daily_prize[random(sizeof(skin_daily_prize))];
				}
			}
		}
		case 5: // День #6;
		{
			switch(random(100))
			{
				case 0 .. 59:
				{
					new accessories_daily_prize[29] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585, 596, 598, 599, 600, 601, 602, 603, 607}; // 250000$;
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_ACC;
					p_info[playerid][daily_reward_idx][idx] = accessories_daily_prize[random(sizeof(accessories_daily_prize))];
				}
				case 60 .. 79:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_INVENTORY;
					p_info[playerid][daily_reward_idx][idx] = 643;
					p_info[playerid][daily_reward_idx_count][idx] = 1;
				}
				default:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_VIP;
					p_info[playerid][daily_reward_idx][idx] = 1;
					p_info[playerid][daily_reward_idx_count][idx] = 1;
				}
			}
		}
		case 6: // День #7;
		{
			switch(random(100))
			{
				case 0 .. 59:
				{
					new accessories_daily_prize[29] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585, 596, 598, 599, 600, 601, 602, 603, 607}; // 250000$;
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_ACC;
					p_info[playerid][daily_reward_idx][idx] = accessories_daily_prize[random(sizeof(accessories_daily_prize))];
				}
				case 60 .. 79:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_INVENTORY;
					p_info[playerid][daily_reward_idx][idx] = 644;
					p_info[playerid][daily_reward_idx_count][idx] = 1;
				}
				default:
				{
					p_info[playerid][daily_reward_type][idx] = DAILY_TYPE_VIP;
					p_info[playerid][daily_reward_idx][idx] = 2;
					p_info[playerid][daily_reward_idx_count][idx] = 1;
				}
			}
		}
	}
	p_info[playerid][daily_reward][idx] = 0;
	SavePlayerDaily(playerid, DAILY_TYPE_REWARD, idx);
	return 1;
}

Daily_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(p_temp[playerid][TextDrawDaily] == false) return 1;

	if(playertextid == PTD_DailyButton[playerid][0]) // Влево награды;
	{
		if(p_temp[playerid][daily_list] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]: "W"Вы находитесь на первой странице.");
		p_temp[playerid][daily_list]--;
		p_temp[playerid][daily_last_idx] = p_temp[playerid][daily_items_list_reward][p_temp[playerid][daily_list]];

		HidePlayerDaily(playerid);
		ShowPlayerDaily(playerid);
		UpdatePlayerDaily(playerid, DAILY_TYPE_UPDATE_LIST);
		return 1;
	}
	else if(playertextid == PTD_DailyButton[playerid][1]) // Вправо награды;
	{
		if(p_temp[playerid][daily_list] == MAX_DAILY_LIST_REWARD - 1) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]: "W"Вы находитесь на последней странице.");
		p_temp[playerid][daily_list]++;
		HidePlayerDaily(playerid);
		ShowPlayerDaily(playerid);
		UpdatePlayerDaily(playerid, DAILY_TYPE_UPDATE_LIST);
		return 1;
	}
	else if(playertextid == PTD_DailyButton[playerid][4]) // Информация;
	{
		STRING_GLOBAL[0] = EOS;
		for(new i; i < sizeof(DailyInfoList); i++) strcat(STRING_GLOBAL, DailyInfoList[i]);
		ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, "{"#cPINK"}Daily Rewards:"W" Информация", STRING_GLOBAL, "Закрыть", "");
		return 1;
	}
	else if(playertextid == PTD_DailyButton[playerid][5]) // Закрыть;
	{
		HideTextDrawForPlayer(playerid, TD_ID_DAILY);
		return 1;
	}
	for(new i = 0; i < 3; i++)
	{
		if(playertextid == PTD_DailyRewardButton[playerid][i])
		{
			new idx = p_temp[playerid][p_listitem][i];
			if(idx == -1) return 1;
			if(p_info[playerid][daily_reward][idx] == 1) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]:"W" Вы уже забрали эту награду.");
			if(p_info[playerid][daily_days] < idx + 1) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]:"W" Данная награда доступна на %d дне.", idx + 1);
			if(p_info[playerid][daily_days] == idx + 1 && p_info[playerid][daily_today] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[DAILY REWARDS]:"W" Время на получение награды истекло.");
			GivePlayerDailyReward(playerid, idx, i);
		}
	}
	return 1;
}

CMD:daily(playerid, params[])
{
	if(p_info[playerid][level] < 3) return SendError(playerid, "Ежедневные награды доступны с 3-го уровня.");
	ShowTextDrawForPlayer(playerid, TD_ID_DAILY);
	return 1;
}

CMD:daily_reward(playerid, params[])
{
	if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
	for(new i = 0; i < MAX_DAILY_REWARD; i++) GetPlayerDailyReward(playerid, i);
	return 1;
}