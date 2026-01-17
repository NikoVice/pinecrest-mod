#define DURAK_NUM_TRUMP_ELEM 3

const DurakTrumpElem_Body = 0;
const DurakTrumpElem_Card = 1;
const DurakTrumpElem_Text = 2;

new PlayerText:PTD_DurakTrump[MAX_DURAK_TABLES + 1][MAX_DURAK_PLAYERS][DURAK_NUM_TRUMP_ELEM];

#define DURAK_TRUMP_BORDER 2.0
#define DURAK_TRUMP_TEXT_HEIGHT 20.0

#define DURAK_TRUMP_WIDTH (DURAK_TRUMP_BORDER + DURAK_CARD_WIDTH + DURAK_TRUMP_BORDER)
#define DURAK_TRUMP_HEIGHT (DURAK_TRUMP_BORDER + DURAK_CARD_HEIGHT + DURAK_TRUMP_TEXT_HEIGHT)

#define DURAK_TRUMP_X 10.0
#define DURAK_TRUMP_Y (DURAK_BOARD_Y - DURAK_TRUMP_WIDTH / 2.0)

Durak_ShowTrump(const playerid, const text[])
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];
	
	PlayerTextDrawShow(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Body]);
	
	PlayerTextDrawSetString(playerid,
		PTD_DurakTrump[table][index][DurakTrumpElem_Card],
		gDurakCardTxd[gDurakTable[table][dtDeck][DURAK_DECK_SIZE - 1]]);
	PlayerTextDrawShow(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Card]);

	PlayerTextDrawSetString(playerid,
		PTD_DurakTrump[table][index][DurakTrumpElem_Text],
		text);
	PlayerTextDrawShow(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text]);
}

Durak_CreateTrump(const playerid, const table, const index)
{
	PTD_DurakTrump[table][index][DurakTrumpElem_Body] = CreatePlayerTextDraw(playerid, DURAK_TRUMP_X, DURAK_TRUMP_Y, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Body], DURAK_TRUMP_WIDTH, DURAK_TRUMP_HEIGHT);
	PlayerTextDrawFont(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Body], 4);
	PlayerTextDrawSetShadow(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Body], 0);
	PlayerTextDrawColor(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Body], DURAK_BTN_COLOR);

	Durak_CreateCard(playerid,
		PTD_DurakTrump[table][index][DurakTrumpElem_Card],
		gDurakCardTxd[0],
		DURAK_TRUMP_X + DURAK_TRUMP_BORDER,
		DURAK_TRUMP_Y + DURAK_TRUMP_BORDER);
	
	PTD_DurakTrump[table][index][DurakTrumpElem_Text] = CreatePlayerTextDraw(playerid,
		DURAK_TRUMP_X + DURAK_TRUMP_WIDTH / 2.0,
		DURAK_TRUMP_Y + DURAK_TRUMP_BORDER + DURAK_CARD_HEIGHT + DURAK_TRUMP_TEXT_HEIGHT / 4.0,
		" ");
	PlayerTextDrawLetterSize(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text], 0.2, 1.0);
	PlayerTextDrawAlignment(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text], 2);
	PlayerTextDrawFont(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text], 2);
	PlayerTextDrawSetProportional(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text], 1);
	PlayerTextDrawSetShadow(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text], 0);
	PlayerTextDrawColor(playerid, PTD_DurakTrump[table][index][DurakTrumpElem_Text], -1);
}

Durak_DestroyTrump(const playerid, const table, const index)
{
	for(new i = 0; i < DURAK_NUM_TRUMP_ELEM; i++)
	{
		PlayerTextDrawDestroy(playerid, PTD_DurakTrump[table][index][i]);
	}
}