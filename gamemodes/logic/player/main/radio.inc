/*GetMaxRadioList()
{
	for(new i = 0; i < MAX_RADIO_LIST_TRACK; i++) MAX_RADIO_LIST[RadioList[i][rType]]++;
	for(new i = 0; i < MAX_RADIO_LIST_TYPE; i++) MAX_RADIO_LIST[i] = floatround(MAX_RADIO_LIST[i] / 7, floatround_ceil), printf("%d", MAX_RADIO_LIST[i]);
	return 1;
}*/

ShowPlayerRadioList(playerid)
{
	new count, type = p_temp[playerid][radio_type], str[52];
	p_temp[playerid][radio_items_list][p_temp[playerid][radio_list]] = p_temp[playerid][radio_last_idx];
	for(new i = p_temp[playerid][radio_last_idx]; i < MAX_RADIO_LIST_TRACK; i++)
	{
		if(RadioList[i][rType] != type) continue;
		PlayerTextDrawShow(playerid, PTD_Radio[playerid][count + 5]);
		PlayerTextDrawShow(playerid, PTD_Radio[playerid][count + 12]);
		format(str, sizeof(str), "%s", RadioList[i][rName]);
		PlayerTextDrawSetString(playerid, PTD_Radio[playerid][count + 12], str);
		p_temp[playerid][p_listitem][count] = i;
		p_temp[playerid][radio_last_idx] = i + 1;
		count++;
		if(count == 7) break;
	}
	return 1;
}

UpdatePlayerRadioList(playerid)
{
	if(p_temp[playerid][TextDrawRadio] == false) return 1;
	STRING_GLOBAL[0] = EOS;
	f(STRING_GLOBAL, "%d/%d", p_temp[playerid][radio_list] + 1, MAX_RADIO_LIST[p_temp[playerid][radio_type]] + 1);
	PlayerTextDrawSetString(playerid, PTD_Radio[playerid][27], STRING_GLOBAL);
	return 1;
}

HidePlayerRadioList(playerid)
{
	if(p_temp[playerid][TextDrawRadio] == false) return 1;
	for(new i = 0; i < 100; i++)
	{
		p_temp[playerid][p_listitem][i] = -1;
		if(i >= 5 && i <= 11) PlayerTextDrawHide(playerid, PTD_Radio[playerid][i]);
		if(i >= 12 && i <= 18) PlayerTextDrawHide(playerid, PTD_Radio[playerid][i]);
	}
	return 1;
}

Radio_OnClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(p_temp[playerid][TextDrawRadio] == false) return 1;

	new type = p_temp[playerid][radio_type];

	if(playertextid == PTD_Radio[playerid][28]) // Закрыть;
	{
		if(p_temp[playerid][radio_type] == TYPE_RADIO_LIST) HideTextDrawForPlayer(playerid, TD_ID_RADIO);
		else
		{
			PlayerTextDrawSetString(playerid, PTD_Radio[playerid][29], "3AKP‘Џ’");
			p_temp[playerid][radio_type] = TYPE_RADIO_LIST;
			p_temp[playerid][radio_last_idx] = 0; // Последняя строка, которая вывелась в списке из массива RadioList;
			p_temp[playerid][radio_list] = 0; // Номер страницы;

			HidePlayerRadioList(playerid);
			ShowPlayerRadioList(playerid);
			UpdatePlayerRadioList(playerid);
		}
	}
	else if(playertextid == PTD_Radio[playerid][23]) // Влево;
	{
		if(p_temp[playerid][radio_list] == 0) return SendMes(playerid, COLOR_DARKORANGE, "[%s]: "W"Вы находитесь на первой странице.", radio_type_name[p_temp[playerid][radio_use_type]]);
		p_temp[playerid][radio_list]--;
		p_temp[playerid][radio_last_idx] = p_temp[playerid][radio_items_list][p_temp[playerid][radio_list]];

		HidePlayerRadioList(playerid);
		ShowPlayerRadioList(playerid);
		UpdatePlayerRadioList(playerid);
	}
	else if(playertextid == PTD_Radio[playerid][24]) // Вправо;
	{
		if(p_temp[playerid][radio_list] == MAX_RADIO_LIST[type]) return SendMes(playerid, COLOR_DARKORANGE, "[%s]: "W"Вы находитесь на последней странице.", radio_type_name[p_temp[playerid][radio_use_type]]);
		p_temp[playerid][radio_list]++;

		HidePlayerRadioList(playerid);
		ShowPlayerRadioList(playerid);
		UpdatePlayerRadioList(playerid);
	}
	else if(playertextid == PTD_Radio[playerid][20]) // Пауза;
	{
		switch(p_temp[playerid][radio_use_type])
		{
			case RADIO_TYPE_AIR_PODS:
			{
				if(GetPVarInt(playerid, "UseMusic") != 0)
				{
					DeletePVar(playerid, "UseMusic");
					StopAudioStreamForPlayer(playerid);
				}
			}
			case RADIO_TYPE_CAR:
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				format(veh_info[vehicleid][v_radio_url], 128, "");
				veh_info[vehicleid][v_radio] = 0;
				for(new i = 0, idx; i < 8; i++)
				{
					idx = veh_info[vehicleid][v_passenger][i];
					if(!IsPlayerConnected(idx)) continue;
					if(!IsPlayerInAnyVehicle(idx)) continue;
					if(GetPlayerVehicleID(idx) != vehicleid) continue;
					if(p_info[idx][p_settings][STATUS_RADIO] != 0) continue;
					if(GetPVarInt(idx, "UseMusic") != 0) continue;
					if(GetPVarInt(idx, "pAudioStream") != 0) continue;
					DeletePVar(idx, "UseMusicVehicle");
					StopAudioStreamForPlayer(idx);
				}
			}
			case RADIO_TYPE_BOOMBOX:
			{
				if(p_temp[playerid][music_area] != -1)
				{
					foreach(new i:Player) if(IsPlayerInDynamicArea(i, p_temp[playerid][music_area])) StopStream(i);
					DeletePVar(playerid, "BBStation");
				}
			}
		}
		p_temp[playerid][radio_type] = TYPE_RADIO_LIST; // ID из массива RadioList;
		p_temp[playerid][radio_type_track] = TYPE_RADIO_LIST; // ID из массива RadioList;
		p_temp[playerid][radio_idx] = -1; // ID из массива RadioList;
		p_temp[playerid][radio_type_idx] = -1; // ID из папки;
		p_temp[playerid][radio_timer] = 0; // Время до окончания таймера;
		if(p_temp[playerid][TextDrawRadio] == true) UpdateRadio(playerid);
		SendMes(playerid, COLOR_GREEN, "[%s]:"W" Действие выполнено.", radio_type_name[p_temp[playerid][radio_use_type]]);
	}
	else if(playertextid == PTD_Radio[playerid][30]) // Пред. трек;
	{
		if(p_temp[playerid][radio_type_idx] == -1) return SendError(playerid, "У Вас не включен трек.");
		if(p_temp[playerid][radio_idx] == 1) return SendError(playerid, "У Вас включен первый трек в этой категории.");
		if(p_temp[playerid][radio_check_button] > timestamp) return SendError(playerid, "Вы не можете так часто изменять трек, подождите %d сек.", p_temp[playerid][radio_check_button] - timestamp);
		p_temp[playerid][radio_type_idx]--; // ID из папки;
		p_temp[playerid][radio_idx]--; // ID из массива;
		STRING_GLOBAL[0] = EOS;
		f(STRING_GLOBAL, "http://cdn.flin-rp.com/gm/music/%s/%d.mp3", radio_list_type_name[p_temp[playerid][radio_type_track]], p_temp[playerid][radio_type_idx]);
		p_temp[playerid][radio_timer] = RadioList[p_temp[playerid][radio_idx]][rTime];
		PlayRadio(playerid, p_temp[playerid][radio_use_type], STRING_GLOBAL);
	}
	else if(playertextid == PTD_Radio[playerid][31]) // След. трек;
	{
		if(p_temp[playerid][radio_type_idx] == -1) return SendError(playerid, "У Вас не включен трек.");
		if(p_temp[playerid][radio_idx] == MAX_RADIO_LIST_TRACK || RadioList[p_temp[playerid][radio_idx] + 1][rType] != p_temp[playerid][radio_type_track]) return SendError(playerid, "У Вас включен последний трек в этой категории.");
		if(p_temp[playerid][radio_check_button] > timestamp) return SendError(playerid, "Вы не можете так часто изменять трек, подождите %d сек.", p_temp[playerid][radio_check_button] - timestamp);
		p_temp[playerid][radio_type_idx]++; // ID из папки;
		p_temp[playerid][radio_idx]++; // ID из массива;
		STRING_GLOBAL[0] = EOS;
		f(STRING_GLOBAL, "http://cdn.flin-rp.com/gm/music/%s/%d.mp3", radio_list_type_name[p_temp[playerid][radio_type_track]], p_temp[playerid][radio_type_idx]);
		p_temp[playerid][radio_timer] = RadioList[p_temp[playerid][radio_idx]][rTime];
		PlayRadio(playerid, p_temp[playerid][radio_use_type], STRING_GLOBAL);
	}

	for(new i = 5; i < 12; i++)
	{
		if(playertextid == PTD_Radio[playerid][i])
		{
			if(p_temp[playerid][radio_type] == TYPE_RADIO_LIST)
			{
				new idx = (i - 4) + (p_temp[playerid][radio_list] * 7);
				if(idx != TYPE_RADIO_STATION && p_info[playerid][p_flin_music] == 0)
				{
					STRING_GLOBAL[0] = EOS;
					f(STRING_GLOBAL, "\
					"I"Flin Music"W" дает вам мгновенный доступ к тысячам песен — от старых фаворитов до последних хитов.\n\
					Просто нажмите кнопку воспроизведения, чтобы транслировать все, что вам нравится.\n\n\
					Рэп, хип-хоп, рок, фонк, поп-музыка, эстрадная музыка, классическая музыка, панк и джаз, все это есть\n\
					в подписке за "I"%d"W" Flin Money в месяц.\n\n\
					%s", RADIO_PRICE, p_info[playerid][p_flin_music_free] == 0 ? "Хотите попробовать 3 дня подписки бесплатно?" : "Хотите перейти к оформлению подписки?");
					ShowPlayerDialog(playerid, D_FLIN_MUSIC, DIALOG_STYLE_MSGBOX, ""I"Подписка Flin Music", STRING_GLOBAL, "Да", "Нет");
					return 1;
				}

				PlayerTextDrawSetString(playerid, PTD_Radio[playerid][29], "HA3Aѓ");

				p_temp[playerid][radio_type] = idx;

				HidePlayerRadioList(playerid);
				ShowPlayerRadioList(playerid);
				UpdatePlayerRadioList(playerid);
				return 1;
			}
			new type = p_temp[playerid][radio_type];
			if(type == TYPE_RADIO_STATION)
			{
				STRING_GLOBAL[0] = EOS;
				f(STRING_GLOBAL, "%s", radio_url[(i - 5) + (p_temp[playerid][radio_list] * 7)]);
				p_temp[playerid][radio_idx] = -1; // ID из массива RadioList;
				p_temp[playerid][radio_type_track] = TYPE_RADIO_LIST; // ID из массива;
				p_temp[playerid][radio_type_idx] = -1; // ID из папки;
				p_temp[playerid][radio_timer] = 0; // Время до окончания таймера;
			}
			else if(type > TYPE_RADIO_STATION)
			{
				if(p_temp[playerid][radio_check_button] > timestamp) return SendError(playerid, "Вы не можете так часто изменять трек, подождите %d сек.", p_temp[playerid][radio_check_button] - timestamp);
				new idx_list = (i - 4) + (p_temp[playerid][radio_list] * 7); // ID из папки;
				STRING_GLOBAL[0] = EOS;
				f(STRING_GLOBAL, "http://cdn.flin-rp.com/gm/music/%s/%d.mp3", radio_list_type_name[type], idx_list);
				new idx = p_temp[playerid][p_listitem][i - 5]; // ID из массива;
				p_temp[playerid][radio_idx] = idx; // ID из массива RadioList;
				p_temp[playerid][radio_type_track] = type; // ID из массива;
				p_temp[playerid][radio_type_idx] = idx_list; // ID из папки;
				p_temp[playerid][radio_timer] = RadioList[idx][rTime]; // Время до окончания таймера;
			}
			PlayRadio(playerid, p_temp[playerid][radio_use_type], STRING_GLOBAL);
			SendMes(playerid, COLOR_GREEN, "[%s]:"W" Действие выполнено.", radio_type_name[p_temp[playerid][radio_use_type]]);
			return 1;
		}
	}
	return 1;
}

ShowPlayerRadio(playerid, idx)
{
	if(p_temp[playerid][TextDrawRadio]) return 1;

	ShowTextDrawForPlayer(playerid, TD_ID_RADIO);

	new year, month, day, hour, minute, second;
	gmtime(p_info[playerid][p_flin_music_time] - timestamp, year, month, day, hour, minute, second);

	STRING_GLOBAL[0] = EOS;
	if(p_info[playerid][p_flin_music_time]) f(STRING_GLOBAL, "%s, до окончания %dм. %dд. %dч. %dм. %dс.", radio_type_name[idx], month-1, day-1, hour, minute, second);
	else f(STRING_GLOBAL, "%s, подписки нет", radio_type_name[idx]);
	PlayerTextDrawSetString(playerid, PTD_Radio[playerid][3], STRING_GLOBAL);

	p_temp[playerid][radio_use_type] = idx;
	p_temp[playerid][radio_type] = TYPE_RADIO_LIST;
	p_temp[playerid][radio_last_idx] = 0; // Последняя строка, которая вывелась в списке из массива RadioList;
	p_temp[playerid][radio_list] = 0; // Номер страницы;

	PlayerTextDrawSetString(playerid, PTD_Radio[playerid][29], "3AKP‘Џ’");

	HidePlayerRadioList(playerid);
	ShowPlayerRadioList(playerid);
	UpdatePlayerRadioList(playerid);

	UpdateRadio(playerid);

	p_temp[playerid][TextDrawRadio] = true;

	SelectTextDraw(playerid, -4632577);
	Fix_TogglePlayerControllable(playerid, false);
	return 1;
}

PlayRadio(playerid, type, text[])
{
	switch(type)
	{
		case RADIO_TYPE_AIR_PODS: PlayPlayerAirPods(playerid, text), p_temp[playerid][radio_check_button] = timestamp + 5;
		case RADIO_TYPE_CAR:
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			if(veh_info[vehicleid][v_radio] == 0)
			{
				veh_info[vehicleid][v_radio] = 1;
			}
			for(new i = 0, idx; i < 8; i++)
			{
				idx = veh_info[vehicleid][v_passenger][i];
				if(!IsPlayerConnected(idx)) continue;
				if(!IsPlayerInAnyVehicle(idx)) continue;
				if(GetPlayerVehicleID(idx) != vehicleid) continue;
				if(p_info[idx][p_settings][STATUS_RADIO] != 0) continue;
				if(GetPVarInt(idx, "UseMusic") != 0) continue;
				SetPVarInt(idx, "UseMusicVehicle", 1);
				PlayAudioStreamForPlayer(idx, text);
			}
			format(veh_info[vehicleid][v_radio_url], 128, text);
			veh_info[vehicleid][v_radio] = 1;
			p_temp[playerid][radio_check_button] = timestamp + 5;
		}
		case RADIO_TYPE_BOOMBOX:
		{
			if(p_temp[playerid][music_area] == -1) return 1;
			foreach(new i:Player)
			{
				if(!IsPlayerInDynamicArea(i, p_temp[playerid][music_area])) continue;
				PlayStream(i, text, GetPVarFloat(playerid, "BBX"), GetPVarFloat(playerid, "BBY"), GetPVarFloat(playerid, "BBZ"), 30.0, 1);
			}
			SetPVarString(playerid, "BBStation", text);
			p_temp[playerid][radio_check_button] = timestamp + 15;
		}
	}
	if(p_temp[playerid][TextDrawRadio] == true) UpdateRadio(playerid);
	return 1;
}

UpdateRadio(playerid)
{
	if(p_temp[playerid][TextDrawRadio] == false) return 1;
	if(p_temp[playerid][radio_idx] != -1)
	{
		STRING_GLOBAL[0] = EOS;
		f(STRING_GLOBAL, "%s", ConvertTime(RadioList[p_temp[playerid][radio_idx]][rTime] - p_temp[playerid][radio_timer], 1));
		PlayerTextDrawSetString(playerid, PTD_Radio[playerid][34], STRING_GLOBAL);
	} else PlayerTextDrawSetString(playerid, PTD_Radio[playerid][34], "00:00");
	return 1;
}
