Durak_OnPlayerLeaveGame(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(gDurakTable[table][dtWinnerIndex] != -1)
		return;

	if(gDurakTable[table][dtPlayerCount] == 1)
	{
		Durak_EndGame(table);
		return;
	}
	else if(gDurakTable[table][dtPlayerCount] == 2)
	{
		for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
		{
			if(gDurakTable[table][dtPlayerId][g] != INVALID_PLAYER_ID && g != index)
			{
				Durak_Win(gDurakTable[table][dtPlayerId][g]);
				break;
			}
		}
		return;
	}
	else if(index == gDurakTable[table][dtDefenderIndex])
	{
		gDurakTable[table][dtEndType] = DurakEnd_DefenderLeft;
		Durak_EndRound(table);
		return;
	}
	else if(index == gDurakTable[table][dtTurnIndex])
	{
		gDurakTable[table][dtEndType] = DurakEnd_TurnLeft;
		Durak_EndRound(table);
		return;
	}

	switch(gDurakTable[table][dtEndType])
	{
	case DurakEnd_AllowTake:
	{
		if(p_info[playerid][durak_allowTake])
			gDurakTable[table][dtAllowTakeCount]--;
	}
	case DurakEnd_Beaten:
	{
		if(p_info[playerid][durak_beaten])
			gDurakTable[table][dtBeatenCount]--;
	}
	}
}

Durak_StartGame(const table)
{
	gDurakTable[table][dtLobbyState] = DurakLobby_InGame;

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		if(!p_info[gDurakTable[table][dtPlayerId][g]][durak_ready])
		{
			Durak_Kick(gDurakTable[table][dtPlayerId][g]);
			continue;
		}

		gDurakTable[table][dtPrize] += gDurakTable[table][dtBet];

		SelectTextDraw(gDurakTable[table][dtPlayerId][g], 0xe67e22ff);
	}

	Durak_Enumerate(table);

	Durak_HideButtonForAll(table, DurakBtn_Left);
	Durak_HideButtonForAll(table, DurakBtn_Right);
	Durak_HideButtonForAll(table, DurakBtn_LargeInfo);

	Durak_CleanRound(table);

	do Durak_Handout(table);
	while((gDurakTable[table][dtTurnIndex] = Durak_GetStartTurnIndex(table)) == -1);
	gDurakTable[table][dtDefenderIndex] = Durak_GetNextIndex(table, gDurakTable[table][dtTurnIndex]);

	gDurakTable[table][dtWinnerIndex] = -1;

	gDurakTable[table][dtAct] = DurakAct_TurnOpen;

	Durak_UpdateRound(table);
}

Durak_EndGame(const table)
{
	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		Durak_Kick(gDurakTable[table][dtPlayerId][g]);
	}

	Durak_CleanTable(table);
}

Durak_DetermineTurn(const table, const endType)
{
	switch(endType)
	{
	case DurakEnd_WannaTake, DurakEnd_AllowTake, DurakEnd_DefenderLeft:
		gDurakTable[table][dtTurnIndex] = Durak_GetNextIndex(table, gDurakTable[table][dtDefenderIndex]);
	case DurakEnd_Beaten, DurakEnd_TurnLeft:
		gDurakTable[table][dtTurnIndex] = gDurakTable[table][dtDefenderIndex];
	}

	gDurakTable[table][dtDefenderIndex] = Durak_GetNextIndex(table, gDurakTable[table][dtTurnIndex]);
}

Durak_Handout(const table)
{
	for(new i = 0; i < DURAK_DECK_SIZE; i++)
		gDurakTable[table][dtDeck][i] = i;
	shuffle(gDurakTable[table][dtDeck], DURAK_DECK_SIZE);

	gDurakTable[table][dtDeckIndex] = 0;

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		new playerid = gDurakTable[table][dtPlayerId][g];

		if(playerid == INVALID_PLAYER_ID)
			continue;

		for(new i = 0; i < 6; i++)
		{
			p_info[playerid][durak_deck][i] = gDurakTable[table][dtDeck][gDurakTable[table][dtDeckIndex]];

			gDurakTable[table][dtDeckIndex]++;
		}

		p_info[playerid][durak_deckSize] = 6;

		for(new i = 6; i < DURAK_DECK_SIZE; i++)
		{
			p_info[playerid][durak_deck][i] = -1;
		}
	}

	if(gDurakTable[table][dtDeckIndex] < DURAK_DECK_SIZE)
		swap(gDurakTable[table][dtDeck][gDurakTable[table][dtDeckIndex]], gDurakTable[table][dtDeck][DURAK_DECK_SIZE - 1]);
}

Durak_RestoreDeck(const table)
{
	new turnId = gDurakTable[table][dtPlayerId][gDurakTable[table][dtTurnIndex]];
	new defenderId = gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]];

	Durak_RestorePlayerDeck(table, turnId);

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		new playerid = gDurakTable[table][dtPlayerId][g];

		if(playerid == INVALID_PLAYER_ID || playerid == turnId || playerid == defenderId)
			continue;

		Durak_RestorePlayerDeck(table, playerid);
	}

	Durak_RestorePlayerDeck(table, defenderId);
}

Durak_RestorePlayerDeck(const table, const playerid)
{
	for(new i = p_info[playerid][durak_deckSize]; i < 6; i++)
	{
		if(gDurakTable[table][dtDeckIndex] == DURAK_DECK_SIZE)
			break;

		Durak_AddPlayerCard(playerid, gDurakTable[table][dtDeck][gDurakTable[table][dtDeckIndex]]);
		gDurakTable[table][dtDeckIndex]++;
	}
}

Durak_GetStartTurnIndex(const table)
{
	new trump = DURAK_SUIT(gDurakTable[table][dtDeck][DURAK_DECK_SIZE - 1]);

	new minvalue = cellmax;
	new index = -1;

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		for(new i = 0; i < 6; i++)
		{
			new card = p_info[gDurakTable[table][dtPlayerId][g]][durak_deck][i];

			if(DURAK_SUIT(card) == trump && DURAK_VALUE(card) < minvalue)
			{
				minvalue = DURAK_VALUE(card);
				index = g;
			}
		}
	}

	return index;
}

Durak_GetNextIndex(const table, const prev)
{
	for(new g = prev + 1; g < MAX_DURAK_PLAYERS; g++)
		if(gDurakTable[table][dtPlayerId][g] != INVALID_PLAYER_ID)
			return g;

	for(new g = 0; g < prev; g++)
		if(gDurakTable[table][dtPlayerId][g] != INVALID_PLAYER_ID)
			return g;

	return -1;
}

swap(&a, &b)
{
	new temp = a;
	a = b;
	b = temp;
}

shuffle(buf[], const len = sizeof buf)
{
	for(new i = len - 1; i != 0; i--)
	{
		new j = random(i + 1);
		swap(buf[i], buf[j]);
	}
}
