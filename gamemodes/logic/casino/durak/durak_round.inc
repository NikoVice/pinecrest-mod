Durak_OnPlayerPlay(const playerid)
{
    new table = p_info[playerid][durak_table];
    new index = p_info[playerid][durak_index];

    p_info[playerid][durak_beaten] = false;
    p_info[playerid][durak_allowTake] = false;

    if(p_info[playerid][durak_deckSize] == 0)
    {
        new turnId = gDurakTable[table][dtPlayerId][gDurakTable[table][dtTurnIndex]];
        new defenderId = gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]];

        new tableCardCount = DURAK_DECK_SIZE - gDurakTable[table][dtDeckIndex];
        new addedCount[MAX_DURAK_PLAYERS];

        addedCount[gDurakTable[table][dtTurnIndex]] = Durak_CalculateAddedCount(tableCardCount, p_info[turnId][durak_deckSize]);
        //printf("Turn %d", addedCount[gDurakTable[table][dtTurnIndex]]);

        for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
        {
            new checkedId = gDurakTable[table][dtPlayerId][g];

            if(checkedId == INVALID_PLAYER_ID || checkedId == turnId || checkedId == defenderId)
                continue;

            addedCount[g] = Durak_CalculateAddedCount(tableCardCount, p_info[checkedId][durak_deckSize]);
            //printf("%d", addedCount[g]);
        }

        addedCount[gDurakTable[table][dtDefenderIndex]] = Durak_CalculateAddedCount(tableCardCount, p_info[defenderId][durak_deckSize]);
        //printf("Defender %d", addedCount[gDurakTable[table][dtDefenderIndex]]);

        if(addedCount[index] == 0)
        {
            Durak_Win(playerid);
            return;
        }
    }

    Durak_UpdateRound(table);
}

Durak_CalculateAddedCount(&tableCardCount, const playerCardCount)
{
    new requested = (playerCardCount >= 6) ? 0 : 6 - playerCardCount;
    new added = (tableCardCount < requested) ? tableCardCount : requested;

    tableCardCount -= added;
    return added;
}

Durak_Win(const playerid)
{
	new table = p_info[playerid][durak_table];

	gDurakTable[table][dtEndType] = DurakEnd_Win;

	gDurakTable[table][dtWinnerIndex] = p_info[playerid][durak_index];


	new tax = gDurakTable[table][dtPrize]/10;
	gDurakTable[table][dtPrize] -= tax;

	SendMes(playerid, 0xFF1493FF, "[Дурак]: {FFFFFF}Вы выиграли %d$. Налог %d$", gDurakTable[table][dtPrize], tax);

	SetPlayerMoney(playerid, gDurakTable[table][dtPrize], true, "победа в карты");

	Durak_EndRound(table);
}

Durak_CleanRound(const table)
{
	gDurakTable[table][dtEndType] = DurakEnd_None;

	gDurakTable[table][dtBeatenCount] = 0;
	gDurakTable[table][dtAllowTakeCount] = 0;

	gDurakTable[table][dtBoardCount][0] = 0;
	gDurakTable[table][dtBoardCount][1] = 0;

	for(new card = 0; card < DURAK_BOARD_SIZE; card++)
	{
		for(new row = 0; row < 2; row++)
		{
			gDurakBoard[table][card][row] = -1;
		}
	}

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		p_info[gDurakTable[table][dtPlayerId][g]][durak_selectIndex] = -1;
		p_info[gDurakTable[table][dtPlayerId][g]][durak_beaten] = false;
		p_info[gDurakTable[table][dtPlayerId][g]][durak_allowTake] = false;
	}

	gDurakTable[table][dtUntilNextRound] = 0;
	gDurakTable[table][dtUntilForcedEnd] = 0;
}

Durak_UpdateRound(const table)
{
	static const durak_fCount[] = "Cards ~y~%d";
	new durak_sCount[sizeof durak_fCount];
	format(durak_sCount, sizeof durak_sCount, durak_fCount,
		DURAK_DECK_SIZE - gDurakTable[table][dtDeckIndex]);

	gDurakTable[table][dtUntilForcedEnd] = DURAK_UNTIL_FORCED_END;

	if(gDurakTable[table][dtAct] == DurakAct_Defence)
	{
		if(gDurakTable[table][dtBoardCount][0] == gDurakTable[table][dtBoardCount][1])
		{
			gDurakTable[table][dtEndType] = DurakEnd_Beaten;

			if(p_info[gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]]][durak_deckSize] == 0)
			{
				Durak_EndRoundWithoutUpdate(table);
			}
		}
		else
		{
			if(gDurakTable[table][dtEndType] != DurakEnd_AllowTake)
				gDurakTable[table][dtEndType] = DurakEnd_WannaTake;
		}
	}

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		Durak_ShowDeck(gDurakTable[table][dtPlayerId][g]);
		Durak_ShowBoard(gDurakTable[table][dtPlayerId][g]);
		Durak_ShowTrump(gDurakTable[table][dtPlayerId][g], durak_sCount);
		Durak_ShowEndBtn(gDurakTable[table][dtPlayerId][g]);
		Durak_ShowForcedEndBtn(gDurakTable[table][dtPlayerId][g]);
	}

	Durak_UpdateStatus(table);
}

Durak_UntilForcedEnd(const table)
{
	if(gDurakTable[table][dtAct] == DurakAct_End || gDurakTable[table][dtUntilForcedEnd] == 0)
		return;

	gDurakTable[table][dtUntilForcedEnd]--;

	if(gDurakTable[table][dtUntilForcedEnd] == 0)
	{
		if(gDurakTable[table][dtAct] == DurakAct_TurnOpen)
			gDurakTable[table][dtEndType] = DurakEnd_Beaten;

		if(gDurakTable[table][dtEndType] == DurakEnd_WannaTake || gDurakTable[table][dtEndType] == DurakEnd_AllowTake)
		{
			Durak_DoAllowTake(table);
		}
		else
		{
			Durak_EndRound(table);
		}
	}
	else
	{
		for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
		{
			if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
				continue;

			Durak_ShowForcedEndBtn(gDurakTable[table][dtPlayerId][g]);
		}
	}
}

Durak_EndRound(const table)
{
	Durak_EndRoundWithoutUpdate(table);
	Durak_UpdateRound(table);
}

Durak_EndRoundWithoutUpdate(const table)
{
	static const endTypeText[][] =
	{
		"",
		"~r~~h~~h~~h~Took All Cards",
		"~r~~h~~h~~h~Took All Cards",
		"~g~~h~~h~~h~Beaten All Cards",
		"~r~~h~~h~~h~Left the Game",
		"~r~~h~~h~~h~Left the Game",
		"~g~~h~~h~~h~Won the Game"
	};

	new playerid = INVALID_PLAYER_ID;

	switch(gDurakTable[table][dtEndType])
	{
	case DurakEnd_WannaTake, DurakEnd_AllowTake, DurakEnd_Beaten, DurakEnd_DefenderLeft:
		playerid = gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]];
	case DurakEnd_TurnLeft:
		playerid = gDurakTable[table][dtPlayerId][gDurakTable[table][dtTurnIndex]];
	case DurakEnd_Win:
		playerid = gDurakTable[table][dtPlayerId][gDurakTable[table][dtWinnerIndex]];
	}

	new text[128];
	format(text, sizeof text,
		"%s~y~(%d)~n~%s",
		p_info[playerid][name],
		playerid,
		endTypeText[gDurakTable[table][dtEndType]]);

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		Durak_ShowButton(gDurakTable[table][dtPlayerId][g],
			DurakBtn_LargeInfo,
			text,
			.selectable = false);
	}

	Durak_RestoreDeck(table);
	Durak_DetermineTurn(table, gDurakTable[table][dtEndType]);

	Durak_CleanRound(table);

	gDurakTable[table][dtAct] = DurakAct_End;
	gDurakTable[table][dtUntilNextRound] = DURAK_UNTIL_NEXT_ROUND;
}

Durak_UntilNextRound(const table)
{
	if(gDurakTable[table][dtUntilNextRound] == 0)
		return;

	gDurakTable[table][dtUntilNextRound]--;

	if(gDurakTable[table][dtUntilNextRound] == 0)
	{
		Durak_NextRound(table);
	}
}

Durak_NextRound(const table)
{
	if(gDurakTable[table][dtWinnerIndex] != -1)
	{
		Durak_EndGame(table);
		return;
	}

	gDurakTable[table][dtAct] = DurakAct_TurnOpen;
	Durak_UpdateRound(table);
	Durak_HideButtonForAll(table, DurakBtn_LargeInfo);
}

Durak_ShowForcedEndBtn(const playerid)
{
	new table = p_info[playerid][durak_table];

	if(gDurakTable[table][dtAct] == DurakAct_End)
	{
		Durak_HideButtonForAll(table, DurakBtn_Right);
		return;
	}

	static const durakTime[] = "%d";
	new string_durakTime[sizeof durakTime];
	format(string_durakTime, sizeof string_durakTime, durakTime, gDurakTable[table][dtUntilForcedEnd]);
	Durak_ShowButton(playerid, DurakBtn_Right, string_durakTime, .selectable = false);
}

Durak_ShowEndBtn(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(gDurakTable[table][dtAct] != DurakAct_Defence)
	{
		Durak_HideButton(playerid, DurakBtn_Left);
		return;
	}

	switch(gDurakTable[table][dtEndType])
	{
	case DurakEnd_Beaten:
	{
		if(index == gDurakTable[table][dtDefenderIndex])
			Durak_HideButton(playerid, DurakBtn_Left);
		else
			Durak_ShowButton(playerid, DurakBtn_Left, "Beaten");
	}
	case DurakEnd_WannaTake:
	{
		if(index == gDurakTable[table][dtDefenderIndex])
			Durak_ShowButton(playerid, DurakBtn_Left, "Wanna Take");
		else
			Durak_HideButton(playerid, DurakBtn_Left);
	}
	case DurakEnd_AllowTake:
	{
		if(index == gDurakTable[table][dtDefenderIndex])
			Durak_HideButton(playerid, DurakBtn_Left);
		else
			Durak_ShowButton(playerid, DurakBtn_Left, "Allow Take");
	}
	default:
	{
		Durak_HideButton(playerid, DurakBtn_Left);
	}
	}

}

Durak_OnEndBtnClick(const playerid)
{
	new table = p_info[playerid][durak_table];

	if(gDurakTable[table][dtAct] != DurakAct_Defence)
		return;

	switch(gDurakTable[table][dtEndType])
	{
	case DurakEnd_Beaten:
		Durak_Beaten(playerid);
	case DurakEnd_WannaTake:
		Durak_WannaTake(playerid);
	case DurakEnd_AllowTake:
		Durak_AllowTake(playerid);
	}

	Durak_HideButton(playerid, DurakBtn_Left);
}

Durak_AllowTake(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(index == gDurakTable[table][dtDefenderIndex])
		return;

	if(!p_info[playerid][durak_allowTake])
	{
		p_info[playerid][durak_allowTake] = true;

		gDurakTable[table][dtAllowTakeCount]++;

		Durak_UpdateStatus(table);

		if(gDurakTable[table][dtAllowTakeCount] == (gDurakTable[table][dtPlayerCount] - 1))
			Durak_DoAllowTake(table);
	}
}

Durak_DoAllowTake(const table)
{
	new index = gDurakTable[table][dtDefenderIndex];

	new defenderId = gDurakTable[table][dtPlayerId][index];

	for(new i = 0; i < DURAK_BOARD_SIZE; i++)
	{
		for(new row = 0; row < 2; row++)
		{
			if(gDurakBoard[table][i][row] != -1)
			{
				Durak_AddPlayerCard(defenderId, gDurakBoard[table][i][row]);
			}
		}
	}

	Durak_EndRound(table);
}

Durak_Beaten(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(index == gDurakTable[table][dtDefenderIndex])
		return;

	if(!p_info[playerid][durak_beaten])
	{
		p_info[playerid][durak_beaten] = true;

		gDurakTable[table][dtBeatenCount]++;

		Durak_UpdateStatus(table);

		if(gDurakTable[table][dtBeatenCount] == (gDurakTable[table][dtPlayerCount] - 1))
			Durak_EndRound(table);
	}
}

Durak_WannaTake(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(index != gDurakTable[table][dtDefenderIndex])
		return;

	gDurakTable[table][dtEndType] = DurakEnd_AllowTake;
	Durak_UpdateRound(table);
}

Durak_AddPlayerCard(const playerid, const card)
{
	p_info[playerid][durak_deck][p_info[playerid][durak_deckSize]] = card;

	p_info[playerid][durak_deckSize]++;
}

Durak_OnDeckClick(const playerid, const deckIndex)
{
	if(!Durak_CanPlay(playerid))
		return;

	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(index == gDurakTable[table][dtDefenderIndex])
	{
		p_info[playerid][durak_selectIndex] = deckIndex;

		Durak_ShowDeck(playerid);
		Durak_ShowBoard(playerid);
	}
	else
	{
		Durak_Attack(playerid, deckIndex);
	}
}

Durak_CanPlay(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	return gDurakTable[table][dtAct] == DurakAct_Defence ||
		(gDurakTable[table][dtAct] == DurakAct_TurnOpen && index == gDurakTable[table][dtTurnIndex]);
}

Durak_CanAttack(const playerid, const deckIndex)
{
	new table = p_info[playerid][durak_table];

	if(gDurakTable[table][dtAct] == DurakAct_TurnOpen)
		return 1;

	new cardValue = DURAK_VALUE(p_info[playerid][durak_deck][deckIndex]);

	for(new i = 0; i < DURAK_BOARD_SIZE; i++)
	{
		for(new row = 0; row < 2; row++)
		{
			if(gDurakBoard[table][i][row] != -1 && DURAK_VALUE(gDurakBoard[table][i][row]) == cardValue)
				return 1;
		}
	}

	return 0;
}

Durak_Attack(const playerid, const deckIndex)
{
	if(!Durak_CanPlay(playerid))
		return;
	if(!Durak_CanAttack(playerid, deckIndex))
		return;

	new table = p_info[playerid][durak_table];

	if(gDurakTable[table][dtBoardCount][0] == p_info[gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]]][durak_deckSize] + gDurakTable[table][dtBoardCount][1])
		return;

	for(new i = 0; i < DURAK_BOARD_SIZE; i++)
	{
		if(gDurakBoard[table][i][0] == -1)
		{
			gDurakBoard[table][i][0] = p_info[playerid][durak_deck][deckIndex];

			gDurakTable[table][dtBoardCount][0]++;

			Durak_RemovePlayerCard(playerid, deckIndex);

			SendMes(gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]], 0xFF1493FF, "[Дурак]: {FFFFFF}На Вас походил(-а) %s [%d]. Отбивайтесь.", p_info[playerid][name], playerid);

			gDurakTable[table][dtAct] = DurakAct_Defence;

			Durak_OnPlayerPlay(playerid);
			return;
		}
	}
}

Durak_RemovePlayerCard(const playerid, const deckIndex)
{
	if(p_info[playerid][durak_deck][deckIndex] == -1)
		return;

	p_info[playerid][durak_deck][deckIndex] = -1;

	for(new i = deckIndex;
		i < p_info[playerid][durak_deckSize] && i < (DURAK_DECK_SIZE - 1);
		i++)
	{
		p_info[playerid][durak_deck][i] = p_info[playerid][durak_deck][i + 1];
	}

	p_info[playerid][durak_deck][DURAK_DECK_SIZE - 1] = -1;

	p_info[playerid][durak_deckSize]--;

	p_info[playerid][durak_selectIndex] = -1;
}

Durak_CanBeat(const trump, const lo, const hi)
{
	if(DURAK_SUIT(lo) == DURAK_SUIT(hi))
		return DURAK_VALUE(hi) > DURAK_VALUE(lo);

	if(DURAK_SUIT(hi) == DURAK_SUIT(trump))
		return 1;

	return 0;
}

Durak_OnBoardClick(const playerid, const boardIndex)
{
	if(!Durak_CanPlay(playerid))
		return;

	new table = p_info[playerid][durak_table];

	if(p_info[playerid][durak_selectIndex] == -1)
		return;
	if(gDurakBoard[table][boardIndex][0] == -1)
		return;
	if(gDurakBoard[table][boardIndex][1] != -1)
		return;

	new deckIndex = p_info[playerid][durak_selectIndex];

	if(!Durak_CanBeat(gDurakTable[table][dtDeck][DURAK_DECK_SIZE - 1],
		gDurakBoard[table][boardIndex][0],
		p_info[playerid][durak_deck][deckIndex]))
	{
		return;
	}

	gDurakBoard[table][boardIndex][1] = p_info[playerid][durak_deck][deckIndex];

	gDurakTable[table][dtBoardCount][1]++;

	Durak_RemovePlayerCard(playerid, deckIndex);

	Durak_OnPlayerPlay(playerid);
}

Durak_CanPassTurn(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	if(index != gDurakTable[table][dtDefenderIndex])
		return false;
	if(gDurakTable[table][dtMode] != DurakMode_PassTurn)
		return false;
	if(gDurakTable[table][dtBoardCount][0] == 0)
		return false;
	if(gDurakTable[table][dtBoardCount][1] != 0)
		return false;

	new nextIndex = Durak_GetNextIndex(table, gDurakTable[table][dtDefenderIndex]);
	new nextId = gDurakTable[table][dtPlayerId][nextIndex];

	if(gDurakTable[table][dtBoardCount][0] >= p_info[nextId][durak_deckSize])
		return false;

	new prevCard = gDurakBoard[table][0][0];

	for(new i = 0; i < DURAK_BOARD_SIZE; i++)
	{
		if(gDurakBoard[table][i][0] != -1)
		{
			if(DURAK_VALUE(prevCard) != DURAK_VALUE(gDurakBoard[table][i][0]))
				return false;

			prevCard = gDurakBoard[table][i][0];
		}
	}

	for(new i = 0; i < p_info[playerid][durak_deckSize]; i++)
	{
		if(DURAK_VALUE(prevCard) == DURAK_VALUE(p_info[playerid][durak_deck][i]))
			return true;
	}

	return false;
}

Durak_OnPassTurnClick(const playerid)
{
	if(!Durak_CanPlay(playerid))
		return;

	new selectIndex = p_info[playerid][durak_selectIndex];

	if(selectIndex == -1)
		return;

	if(!Durak_CanPassTurn(playerid))
		return;

	if(!Durak_CanAttack(playerid, selectIndex))
		return;

	new table = p_info[playerid][durak_table];

	gDurakTable[table][dtTurnIndex] = gDurakTable[table][dtDefenderIndex];
	gDurakTable[table][dtDefenderIndex] = Durak_GetNextIndex(table, gDurakTable[table][dtTurnIndex]);

	new defenderId = gDurakTable[table][dtPlayerId][gDurakTable[table][dtDefenderIndex]];

	gDurakTable[table][dtEndType] = DurakEnd_None;

	gDurakTable[table][dtBeatenCount] = 0;
	gDurakTable[table][dtAllowTakeCount] = 0;

	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;

		SendMes(gDurakTable[table][dtPlayerId][g], 0xFF1493FF, "[Дурак]: {FFFFFF}%s [%d] перевел(-а) на %s [%d].", p_info[playerid][name], playerid, p_info[defenderId][name], defenderId);

		p_info[gDurakTable[table][dtPlayerId][g]][durak_selectIndex] = -1;
		p_info[gDurakTable[table][dtPlayerId][g]][durak_beaten] = false;
		p_info[gDurakTable[table][dtPlayerId][g]][durak_allowTake] = false;
	}

	Durak_Attack(playerid, selectIndex);
}
