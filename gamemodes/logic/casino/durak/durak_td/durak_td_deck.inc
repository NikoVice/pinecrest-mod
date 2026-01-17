new PlayerText:PTD_DurakDeck[MAX_DURAK_TABLES + 1][MAX_DURAK_PLAYERS][DURAK_DECK_SIZE];

const Float:DURAK_DECK_Y = 400.0;

Durak_InitDeck(const playerid, const table, const index, const from = 0)
{
	for(new card = from; card < DURAK_DECK_SIZE; card++)
	{
		Durak_CreateCard(playerid,
			PTD_DurakDeck[table][index][card],
			" ", 0.0, 0.0);
	}
}

Durak_DestroyDeck(const playerid, const table, const index)
{
	for(new card = 0; card < DURAK_DECK_SIZE; card++)
	{
		PlayerTextDrawDestroy(playerid, PTD_DurakDeck[table][index][card]);
	}
}

Durak_ShowDeck(const playerid)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];
	new count = p_info[playerid][durak_deckSize];

	Durak_DestroyDeck(playerid, table, index);

	new Float:gap = (count > 8) ? count * 0.8 : 0.0;
	new Float:offset = (640.0 - (count - 1) * (DURAK_CARD_WIDTH - gap)) / 2.0;

	new selectable = Durak_CanPlay(playerid);

	for(new card = 0; card < count; card++)
	{
		new Float:selectOffset = (p_info[playerid][durak_selectIndex] == card) ? 10.0 : 0.0;

		Durak_CreateCard(playerid,
			PTD_DurakDeck[table][index][card],
			
			gDurakCardTxd[p_info[playerid][durak_deck][card]],
			
			offset + card * (DURAK_CARD_WIDTH - gap) - DURAK_CARD_WIDTH / 2.0,
			
			DURAK_DECK_Y - DURAK_CARD_HEIGHT / 2.0 - selectOffset);
		
		PlayerTextDrawSetSelectable(playerid, PTD_DurakDeck[table][index][card], selectable);
		PlayerTextDrawShow(playerid, PTD_DurakDeck[table][index][card]);
	}

	Durak_InitDeck(playerid, table, index, .from = count);
}