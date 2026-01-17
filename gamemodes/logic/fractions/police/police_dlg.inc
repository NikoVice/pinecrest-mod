Dialog:LSPDElevator(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;
    if (!IsPlayerInRangeOfPoint(playerid, 2.0, 2268.0640,2448.2449,3.5313) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2781.0559,-1056.2823,1028.4969) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2874.6665,-940.6707,1035.9259) && !IsPlayerInRangeOfPoint(playerid, 2.0, 2872.8813,-1072.9934,1037.1782)) return 1;

	new world_list[] = {2, 1, 2, 3};

	switch(listitem)
	{
	    case 0: SetPlayerPosEx(playerid, 2268.0640,2448.2449,3.5313), SetPlayerFacingAngle(playerid, 181.2476);
	    case 1: SetPlayerPosEx(playerid, 2780.9036,-1056.2358,1028.4969), SetPlayerFacingAngle(playerid, 87.9492);
	    case 2: SetPlayerPosEx(playerid, 2873.9063,-940.8126,1035.9259), SetPlayerFacingAngle(playerid, 84.3340);
	    case 3: SetPlayerPosEx(playerid, 2872.7168,-1072.2004,1037.1770), SetPlayerFacingAngle(playerid, 0.2384);
	}

	SetPlayerVirtualWorld(playerid, world_list[listitem]);
	SetPlayerInterior(playerid, (listitem == 0)?(0):(1));
	return 1;
}

Dialog:MPCarVoice(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

    MegaphoneSoundVoice(playerid, listitem + 1);
	return 1;
}

Dialog:MDCRecord(playerid, response, listitem, inputtext[])
{
	if (!response)											return 1;
	if (sscanf(inputtext, "u", p_temp[playerid][pMDCPlayer]))	return SendError(playerid, "Игрок не найден.");
	if (!IsPlayerLogged(p_temp[playerid][pMDCPlayer]))		return SendError(playerid, "Игрок не авторизован.");

	new mes[256];
	format(mes, sizeof(mes), ""W"ПРЕДЪЯВЛЕНИЕ ОБВИНЕНИЙ\n\nОбвиняемый: %s\n\nnВведите текст обвинения: (( Преступление / 128 символов))", get_name(p_temp[playerid][pMDCPlayer]));
	ShowPlayerDialog(playerid, MDCRecord2, DIALOG_STYLE_INPUT, ""I"MDC - Предъявление обвинения", mes, "Ввод", "Отмена");
	return 1;
}

Dialog:MDCRecord2(playerid, response, listitem, inputtext[])
{
	if (!response)										return 1;
    if (!IsPlayerLogged(p_temp[playerid][pMDCPlayer]))	return 1;

	if (strlen(inputtext) < 1 || strlen(inputtext) > 127)
	{
	    new mes[256];
		format(mes, sizeof(mes), ""W"ПРЕДЪЯВЛЕНИЕ ОБВИНЕНИЙ\n\nОбвиняемый: %s\n\nnВведите текст обвинения: (( Преступление / 128 символов))", get_name(p_temp[playerid][pMDCPlayer]));
		ShowPlayerDialog(playerid, MDCRecord2, DIALOG_STYLE_INPUT, ""I"MDC - Предъявление обвинения", mes, "Ввод", "Отмена");
		return 1;
	}

    AddCriminalRecord(p_temp[playerid][pMDCPlayer], inputtext, get_name(playerid), PlayerInfo[playerid][pFaction]);

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "[WANTED] Обвиняемый: %s, Обвинитель: %s Преступление: %s.", get_name(p_temp[playerid][pMDCPlayer]), get_name(playerid), inputtext);
    SendFractionMessage(POLICE_LS, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(POLICE_SF, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(POLICE_LV, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(POLICE_RC, 0x33CC66FF, STRING_GLOBAL);
    SendFractionMessage(FBI_TEAM, 0x33CC66FF, STRING_GLOBAL);

    SendAccess(playerid, "Обвиняемый успешно добавлен в розыск.");
	p_temp[playerid][pMDCPlayer] = INVALID_PLAYER_ID;
	return 1;
}

Dialog:D_SHOW_TRACE(playerid, response, listitem, inputtext[])
{
	if (p_temp[playerid][pTraceStage] < 7)
	{
		ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Система отслеживания", ""W"Вы вышли из системы отслеживания.", "Принять", "");

		if (p_temp[playerid][pTraceGZ] != -1)	GangZoneDestroy(p_temp[playerid][pTraceGZ]);

		p_temp[playerid][pTraceGZ] = -1;
		p_temp[playerid][pTracePlayer] = INVALID_PLAYER_ID;
 		p_temp[playerid][pTraceStage] = 0;
	}
	return 1;
}
