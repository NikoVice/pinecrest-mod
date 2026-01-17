const Float:DURAK_BOARD_Y = 240.0;
const Float:DURAK_BOARD_GAP = 15.0;
const Float:DURAK_BOARD_ROW_OFFSET = 10.0;

new PlayerText:PTD_DurakBoard[MAX_DURAK_TABLES + 1][MAX_DURAK_PLAYERS][DURAK_BOARD_SIZE][2];

Durak_InitBoard(const playerid, const table, const index, const from = 0)
{
	for(new card = from; card < DURAK_BOARD_SIZE; card++)
	{
		for(new row = 0; row < 2; row++)
		{
			Durak_CreateCard(playerid,
				PTD_DurakBoard[table][index][card][row],
				" ", 0.0, 0.0);
		}
	}
}

Durak_DestroyBoard(const playerid, const table, const index)
{
	for(new card = 0; card < DURAK_BOARD_SIZE; card++)
	{
		for(new row = 0; row < 2; row++)
		{
			PlayerTextDrawDestroy(playerid, PTD_DurakBoard[table][index][card][row]);
		}
	}
}

Durak_ShowBoard(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	new count = gDurakTable[table][dtBoardCount][0];
	new passTurn = Durak_CanPassTurn(playerid);

	Durak_DestroyBoard(playerid, table, index);
	Durak_DestroyButton(playerid, table, index, DurakBtn_PassTurn);

	new Float:offset = (640.0 - (count + passTurn - 1) * (DURAK_CARD_WIDTH + DURAK_BOARD_GAP)) / 2.0;

	new selectable =
		Durak_CanPlay(playerid) &&
		index == gDurakTable[table][dtDefenderIndex] &&
		p_info[playerid][durak_selectIndex] != -1;

	for(new card = 0; card < count; card++)
	{
		for(new row = 0; row < 2; row++)
		{
			if(gDurakBoard[table][card][row] == -1)
			{
				Durak_CreateCard(playerid,
					PTD_DurakBoard[table][index][card][row],
					" ", 0.0, 0.0);
				continue;
			}

			Durak_CreateCard(playerid,
				PTD_DurakBoard[table][index][card][row],
				
				gDurakCardTxd[gDurakBoard[table][card][row]],
				
				offset + card * (DURAK_CARD_WIDTH + DURAK_BOARD_GAP) - DURAK_CARD_WIDTH / 2.0 + row * DURAK_BOARD_ROW_OFFSET,
				
				DURAK_BOARD_Y - DURAK_CARD_HEIGHT / 2.0 - row * DURAK_BOARD_ROW_OFFSET);
			
			if(row == 0)
			{
				PlayerTextDrawSetSelectable(playerid,
					PTD_DurakBoard[table][index][card][row],
					selectable);
			}

			PlayerTextDrawShow(playerid, PTD_DurakBoard[table][index][card][row]);
		}
	}

	if(passTurn)
	{
		Durak_CreateButton(playerid,
			PTD_DurakBtn[table][index][DurakBtn_PassTurn],
			offset + count * (DURAK_CARD_WIDTH + DURAK_BOARD_GAP) - DURAK_CARD_WIDTH / 2.0,
			DURAK_BOARD_Y - DURAK_CARD_HEIGHT / 2.0,
			DURAK_CARD_WIDTH,
			DURAK_CARD_HEIGHT);
		
		Durak_ShowButton(playerid, DurakBtn_PassTurn, "Pass~n~Turn");
	}
	else
	{
		Durak_CreateButton(playerid,
			PTD_DurakBtn[table][index][DurakBtn_PassTurn],
			0.0, 0.0, 0.0, 0.0);
	}

	Durak_InitBoard(playerid, table, index, .from = count);
}