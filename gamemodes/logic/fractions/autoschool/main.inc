new VehicleSchoolHelp[][256] = {
	{""W"ДТП - это дорожно-транспортное происшествие."},
	{"Первым делом при ДТП необходимо вызывать сотрудников МВД.\n"},
	{"Максимальные скорости:"},
	{"- В городе - 60 KM/H."},
	{"- В пригороде - 90 KM/H."},
	{"- На автомагистрали - 110 KM/H.\n"},
	{"Панель спидометра:"},
	{"- ENGINE - информация о состоянии двигателя."},
	{"- DOORS - информация о состоянии дверей."},
	{"- LIGHTS - информация о состоянии фар.\n"},
	{"Дополнительно:"},
	{"- Пересекать сплошную линию можно только для предотвращения ДТП."},
	{"- При виде транспорта с включенным спецсигналом необходимо сбавить скорость."},
	{"- Пристегивать ремень безопасности необходимо при начале движения."},
	{"- Припарковать транспортное средство можно на специально отведенных местах."},
	{"- В случае неисправности транспортного средства водитель обязан съехать на обочину и вызвать автомеханика.\n"},
	{"Вы желаете перейти к теоретической части?"}
};

new VehicleSchoolQuest[15][96] = {
	"Что такое ДТП?",
	"Что первым делом необходимо сделать при ДТП?",
	"Какая макс. скорость при движении по городу?",
	"Какая макс. скорость при движении по пригороду?",
	"Какая макс. скорость при движении по автомагистрали?",
	"Что означает ENGINE на панели спидометра?",
	"Что означает DOORS на панели спидометра?",
	"Что означает LIGHTS на панели спидометра?",
	"С помощью какой клавиши завести или заглушить двигатель?",
	"С помощью какой команды включить или выключить фары?",
	"В какой ситуации водитель может пересечь сплошную линию?",
	"Что нужно сделать при виде транспорта с включенным спецсигналом?",
	"В каком случае необходимо пристегивать ремень безопасности?",
	"Где можно припарковать транспортное средство?",
	"В случае неисправности транспортного средства водитель обязан?"
};

new VehicleSchoolAnswer[15][3][64] = {
	{"Дорожно-транспортное происшествие;","Дорожно-транспортая проверка;","Дорожно-торговое предприятие;"},
	{"Скрыться с места ДТП;", "Вызвать сотрудников МВД;", "Вызвать сотрудников МЗ;"},
	{"50 KM/H;", "60 KM/H;", "70 KM/H;"},
	{"80 KM/H;", "90 KM/H;", "100 KM/H;"},
	{"110 KM/H;", "120 KM/H;", "130 KM/H;"},
	{"Информация о состоянии двигателя;", "Информация о состоянии дверей;", "Информация о состоянии фар;"},
	{"Информация о состоянии двигателя;", "Информация о состоянии дверей;", "Информация о состоянии фар;"},
	{"Информация о состоянии двигателя;", "Информация о состоянии дверей;", "Информация о состоянии фар;"},
	{"2;", "ALT;", "CTRL;"},
	{"/limit;", "/light;", "/lock;"},
	{"Для обгона;", "Для предотвращения ДТП;", "В обоих случаях;"},
	{"Продолжить движение;", "Остановиться;", "Сбавить скорость;"},
	{"Перед началом движения;", "При виде транспорт с включенным спец. сигналом;", "Никогда;"},
	{"На тротуаре;", "На дороге;", "В специально отведенных местах;"},
	{"Продолжить движение;", "Доехать до ближейшего СТО;", "Съехать на обочину и вызвать автомеханика;"}
};

new VehicleSchoolTrueAnswer[15] = {1, 2, 2, 2, 1, 1, 2, 3, 2, 2, 2, 3, 1, 3, 3};

VehicleSchoolExam(playerid, one, two, dialogid, qid)
{
	if(GetPVarInt(playerid, "VehicleSchoolQuestID")) qid = GetPVarInt(playerid, "VehicleSchoolQuestID");
	else
	{
		if(qid == -1) qid = RandomEx(one, two);
		SetPVarInt(playerid, "VehicleSchoolQuestID", qid);
	}
	STRING_GLOBAL[0] = EOS;
	format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s\n"I"[1]"W" %s\n"I"[2]"W" %s\n"I"[3]"W" %s", VehicleSchoolQuest[qid], VehicleSchoolAnswer[qid][0], VehicleSchoolAnswer[qid][1], VehicleSchoolAnswer[qid][2]);
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, ""I"Теоретическая часть", STRING_GLOBAL, "Далее", "Отмена");
	return 1;
}

ShowPlayerExamAutoschoolLicense(playerid)
{
	STRING_GLOBAL = "[#] Название\tСтоимость\n", STRING_MIN[0] = EOS;
	for(new i = 0; i < sizeof(type_license) - 7; i++)
	{
		format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$\n", i + 1, name_license[i], price_license[i] / 2);
		strcat(STRING_GLOBAL, STRING_MIN);
	}
	ShowPlayerDialog(playerid, D_AUTOSCHOOL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Получение лицензий", STRING_GLOBAL, "Далее", "Отмена");
	return 1;
}

ShowPlayerBuyAutoschoolLicense(playerid)
{
	STRING_GLOBAL = "[#] Название\tСтоимость\n", STRING_MIN[0] = EOS;
	for(new i = 0; i < sizeof(type_license) - 1; i++)
	{
		format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$\n", i + 1, name_license[i], price_license[i]);
		strcat(STRING_GLOBAL, STRING_MIN);
	}
	ShowPlayerDialog(playerid, D_AUTOSCHOOL_BUY_LICENSE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Приобретение лицензий", STRING_GLOBAL, "Далее", "Отмена");
	return 1;
}

CMD:selllic(playerid, params[])
{
	if(p_info[playerid][member] != LICENSE) return SendError(playerid, "Вы не можете пользоваться этой командой.");
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /selllic [id игрока]");
	if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
	if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
	if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
	p_temp[playerid][p_listitem_int] = params[0];
	STRING_GLOBAL = "[#] Название\tСтоимость\n", STRING_MIN[0] = EOS;
	for(new i = 0; i < sizeof(type_license) - 1; i++)
	{
		format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$\n", i + 1, name_license[i], price_license[i]);
		strcat(STRING_GLOBAL, STRING_MIN);
	}
	ShowPlayerDialog(playerid, D_SELL_LICENSE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Продажа лицензий", STRING_GLOBAL, "Далее", "Отмена");
	return 1;
}

CMD:sellinsurance(playerid, params[])
{
	if(p_info[playerid][member] != LICENSE && p_info[playerid][rang] < 7) return SendError(playerid, "Вы не можете пользоваться этой командой.");
	if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /sellinsurance [id игрока]");
	if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
	if(params[0] == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не найден.");
	if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
	if(!IsPlayerInAnyVehicle(params[0])) return SendError(playerid, "Игрок должен находиться в личном транспортном средстве.");
	new vehicleid = GetPlayerVehicleID(params[0]), vehicle_model = GetVehicleModelEx(vehicleid);
	if(!IsPlayerOwnerVehicle(params[0], vehicleid)) return SendError(playerid, "Игрок должен находиться в личном транспортном средстве.");
	if(GetVehicleData(vehicle_model, E_VD_TYPE) != VEHICLE_STATE_VELO_MOPED && GetVehicleData(vehicle_model, E_VD_TYPE) != VEHICLE_STATE_MOTO && GetVehicleData(vehicle_model, E_VD_TYPE) != VEHICLE_STATE_CAR) return SendError(playerid, "Игрок должен быть на велосипеде, мотоцикле или автомобиле.");
	if(veh_info[vehicleid][v_insurance] == 1) return SendError(playerid, "На транспортном средство в котором находится игрок уже есть страховка.");
	new price = GetPriceInsurance(vehicle_model);
	SendAccess(playerid, "Вы предложили %s [%d] приобрести страховку на транспортное средство за %d$.", get_name(params[0]), params[0], price);
	SendInfo(params[0], "%s [%d] предложил Вам приобрести страховку на транспортное средство за %d$.", get_name(playerid), playerid, price);

	SetFreeSlotOffer(params[0], playerid, OFFER_ID_BUY_INSURANCE, price);
	return 1;
}

CheckLicense(playerid)
{
	for(new idx; idx != LIC_ALL; idx++)
	{
		if(p_info[playerid][Lic][idx] != 0 && p_info[playerid][Lic_Time][idx] != 0)
		{
			p_info[playerid][Lic_Time][idx]--;

			if(p_info[playerid][Lic_Time][idx] == 0)
			{
				new str_name_lic[LIC_ALL][24] = {"оружие", "рыбалку", "наземный транспорт", "воздушный транспорт", "водный транспорт", "мото-транспорт", "частный извоз", "охоту", "адвокатские услуги"};

				SendInfo(playerid, "Срок действия Вашей лицензии на %s истек.", str_name_lic[idx]);

				p_info[playerid][Lic][idx] = 0;
				p_info[playerid][Lic_Time][idx] = 0;
				p_info[playerid][Lic_Warn][idx] = 0;
			}
		}
	}
	return 1;
}

CheckVehicleInsurance(vehicleid)
{
	if(veh_info[vehicleid][v_insurance] != 0 && veh_info[vehicleid][v_insurance_time] != 0)
	{
		veh_info[vehicleid][v_insurance_time]--;

		if(veh_info[vehicleid][v_insurance_time] == 0) veh_info[vehicleid][v_insurance] = 0;
		SaveVehicle(vehicleid);
	}
	return 1;
}

GetPriceInsurance(vehicle_model)
{
	new price = 2500;
	price = GetVehicleData(vehicle_model, E_VD_PRICE) / 50;
	return price;
}
