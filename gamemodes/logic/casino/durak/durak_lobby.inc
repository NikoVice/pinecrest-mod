Durak_UpdateLobbyBtn(const playerid)
{
	new table = p_info[playerid][durak_table];

	Durak_ShowParamBtn(playerid, .enabled = !p_info[playerid][durak_ready] && gDurakTable[table][dtReadyCount] <= 1);
	Durak_ShowReadyBtn(playerid, .enabled = gDurakTable[table][dtBet] != 0);
}

Durak_ShowParamBtn(const playerid, const bool:enabled = true)
{
    new table = p_info[playerid][durak_table];

    static const fdText[][] =
    {
        "~w~Bet ~g~~h~~h~$%d ~w~Mode ~g~~h~~h~%s",
        "~w~Bet ~g~~h~$%d ~w~Mode ~g~~h~%s"
    };

    new sText[64];
    format(sText, sizeof sText, fdText[enabled],
        gDurakTable[table][dtBet],
        (gDurakTable[table][dtMode] == DurakMode_PassTurn) ? ("Pass") : ("Simple"));

    Durak_ShowButton(playerid, DurakBtn_Left, sText, .enabled = enabled);
}

Durak_ReturnBet(const playerid)
{
	if(p_info[playerid][durak_ready])
	{
		SetPlayerMoney(playerid, gDurakTable[p_info[playerid][durak_table]][dtBet],  true, "Дурак: Возврат ставки");
		p_info[playerid][durak_ready] = false;
	}
}

Durak_PlayerParam(const playerid)
{
	if(p_info[playerid][durak_ready] || gDurakTable[p_info[playerid][durak_table]][dtReadyCount] > 1)
		return;

	ShowPlayerDialog(playerid, D_DURAK_MODE, DIALOG_STYLE_LIST, ""I"Тип игры",
		""I"[1]"W" Подкидной\n"I"[2]"W" Переводной",
		"Далее", "Отмена");
}

Durak_HandleModeDlg(const playerid, const listitem)
{
	SetPVarInt(playerid, "Durak:Mode", (listitem == 0) ? DurakMode_Simple : DurakMode_PassTurn);
	Durak_ShowBetDlg(playerid);
}

Durak_ShowBetDlg(const playerid, const comment[] = "")
{
	static const fdText[] =
		"{ffffff}Предложите ставку от {2ecc71}"#DURAK_MIN_BET"${ffffff} до {2ecc71}"#DURAK_MAX_BET"${ffffff}";

	new buf[sizeof fdText + 64];
	strcat(buf, fdText);
	if(!isnull(comment)) strcat(buf, comment);

	ShowPlayerDialog(playerid, D_DURAK_BET, DIALOG_STYLE_INPUT,
		""W"Предложить ставку:", buf,
		"Поставить", "Закрыть");
}

Durak_HandleBetDlg(const playerid, const response, const inputtext[])
{
	new table = p_info[playerid][durak_table];

	if(!response || p_info[playerid][durak_ready] || gDurakTable[table][dtReadyCount] > 1)
		return;

	new betAmount = 0;

	if(sscanf(inputtext, "i", betAmount) || !(DURAK_MIN_BET <= betAmount <= DURAK_MAX_BET))
	{
		Durak_ShowBetDlg(playerid, "\n\n{ff6347}Ошибка: Вы ввели неверное число.");
		return;
	}

	if(p_info[playerid][cash] < betAmount)
	{
		Durak_ShowBetDlg(playerid, "\n\n{ff6347}Ошибка: У Вас нет столько денег.");
		return;
	}

	new newMode = GetPVarInt(playerid, "Durak:Mode");

	if(gDurakTable[table][dtBet] != betAmount || gDurakTable[table][dtMode] != newMode)
	{
		for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
		{
			if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
				continue;

			if(p_info[gDurakTable[table][dtPlayerId][g]][durak_ready])
			{
				Durak_ReturnBet(gDurakTable[table][dtPlayerId][g]);
				p_info[gDurakTable[table][dtPlayerId][g]][durak_ready] = false;
				gDurakTable[table][dtReadyCount]--;
			}
		}
	}

	gDurakTable[table][dtMode] = newMode;
	gDurakTable[table][dtBet] = betAmount;
	Durak_PlayerReady(playerid);
}

Durak_ShowReadyBtn(const playerid, const bool:enabled = true)
{
	new bool:ready = p_info[playerid][durak_ready];

	static const text[][] = {"Ready", "Cancel"};
	static const bodyColor[] = {0x2ecc71ff, 0xe74c3cff};

	Durak_ShowButton(playerid, DurakBtn_Right,
		text[ready],
		.bodyColor = bodyColor[ready],
		.enabled = enabled);
}

Durak_PlayerReady(const playerid)
{
	new table = p_info[playerid][durak_table];

	if(gDurakTable[table][dtBet] == 0)
		return;

	if(!p_info[playerid][durak_ready])
	{
		if(p_info[playerid][cash] < gDurakTable[table][dtBet])
			return;

		SendMes(playerid, 0xFF1493FF, "[Дурак]: {FFFFFF}Вы сделали ставку %d$.", gDurakTable[table][dtBet]);

		SetPlayerMoney(playerid, -gDurakTable[table][dtBet], true, "Дурак: Ставка");

		p_info[playerid][durak_ready] = true;

		gDurakTable[table][dtReadyCount]++;
	}
	else
	{
		Durak_ReturnBet(playerid);

		p_info[playerid][durak_ready] = false;

		gDurakTable[table][dtReadyCount]--;
	}

	Durak_CheckReadyCount(table);
}

Durak_CheckReadyCount(const table)
{
	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		Durak_UpdateLobbyBtn(gDurakTable[table][dtPlayerId][g]);
	}

	Durak_UpdateStatus(table);

	switch(gDurakTable[table][dtLobbyState])
	{
	case DurakLobby_Ready:
	{
		if(gDurakTable[table][dtReadyCount] < MIN_DURAK_PLAYERS)
		{
			gDurakTable[table][dtLobbyState] = DurakLobby_NotReady;
			gDurakTable[table][dtUntilGame] = 0;

			Durak_HideButtonForAll(table, DurakBtn_LargeInfo);
		}
	}
	case DurakLobby_NotReady:
	{
		if(gDurakTable[table][dtReadyCount] >= MIN_DURAK_PLAYERS)
		{
			gDurakTable[table][dtLobbyState] = DurakLobby_Ready;
			gDurakTable[table][dtUntilGame] = DURAK_UNTIL_GAME;
		}
	}
	}
}

Durak_UntilGame(const table)
{
	if(gDurakTable[table][dtUntilGame] == 0)
		return;

	gDurakTable[table][dtUntilGame]--;

	if(gDurakTable[table][dtUntilGame] == 0)
	{
		Durak_StartGame(table);
	}
	else
	{
		static const durakTime[] = "Game Starts In~n~~y~%d";
		new string_durakTime[sizeof durakTime];
		format(string_durakTime, sizeof string_durakTime, durakTime, gDurakTable[table][dtUntilGame]);

		for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
		{
			if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
				continue;

			Durak_ShowButton(gDurakTable[table][dtPlayerId][g],
				DurakBtn_LargeInfo,
				string_durakTime,
				.selectable = false);
		}
	}
}
