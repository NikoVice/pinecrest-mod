#define DURAK_NUM_BTN 6

enum
{
	DurakBtn_Left,
	DurakBtn_Right,
	DurakBtn_Mid,
	DurakBtn_LargeInfo,
	DurakBtn_Leave,
	DurakBtn_PassTurn
};

const Float:DURAK_BTN_HEIGHT = 20.0;
const Float:DURAK_BTN_Y = 320.0;
const Float:DURAK_BTN_GAP = 1.0;

const Float:DURAK_LEFT_BTN_WIDTH = 160.0;
const Float:DURAK_RIGHT_BTN_WIDTH = 60.0;
const Float:DURAK_MID_BTN_WIDTH = 60.0;

#define DURAK_LEFT_BTN_X ((640.0 - (DURAK_LEFT_BTN_WIDTH + DURAK_BTN_GAP + DURAK_RIGHT_BTN_WIDTH)) / 2.0)
#define DURAK_RIGHT_BTN_X ((640.0 + DURAK_LEFT_BTN_WIDTH + DURAK_BTN_GAP + DURAK_RIGHT_BTN_WIDTH) / 2.0 - DURAK_RIGHT_BTN_WIDTH + DURAK_BTN_GAP)
#define DURAK_MID_BTN_X ((640.0 - DURAK_MID_BTN_WIDTH) / 2.0)

const Float:DURAK_LARGE_INFO_BTN_WIDTH = 120.0;
const Float:DURAK_LARGE_INFO_BTN_HEIGHT = 60.0;

#define DURAK_LARGE_INFO_BTN_X (640.0 - DURAK_LARGE_INFO_BTN_WIDTH) / 2.0
#define DURAK_LARGE_INFO_BTN_Y (480.0 - DURAK_LARGE_INFO_BTN_HEIGHT) / 2.0

#define DURAK_NUM_BTN_ELEM 2

const DurakBtnElem_Body = 0;
const DurakBtnElem_Text = 1;

new PlayerText:PTD_DurakBtn[MAX_DURAK_TABLES + 1][MAX_DURAK_PLAYERS][DURAK_NUM_BTN][DURAK_NUM_BTN_ELEM];

Durak_ShowButton(const playerid, const btn,
	const text[],
	const bodyColor = DURAK_BTN_COLOR,
	const textColor = DURAK_BTN_TEXT_COLOR,
	const bool:selectable = true,
	const bool:enabled = true)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	PlayerTextDrawSetSelectable(playerid, PTD_DurakBtn[table][index][btn][DurakBtnElem_Body],
		enabled ? selectable : false);
	PlayerTextDrawColor(playerid, PTD_DurakBtn[table][index][btn][DurakBtnElem_Body],
		enabled ? bodyColor : DURAK_BTN_DISABLED_COLOR);
	PlayerTextDrawShow(playerid, PTD_DurakBtn[table][index][btn][DurakBtnElem_Body]);

	PlayerTextDrawSetString(playerid, PTD_DurakBtn[table][index][btn][DurakBtnElem_Text], text);
	PlayerTextDrawColor(playerid, PTD_DurakBtn[table][index][btn][DurakBtnElem_Text],
		enabled ? textColor : DURAK_BTN_TEXT_DISABLED_COLOR);
	PlayerTextDrawShow(playerid, PTD_DurakBtn[table][index][btn][DurakBtnElem_Text]);
}

Durak_HideButton(const playerid, const btn)
{
	for(new elem = 0; elem < DURAK_NUM_BTN_ELEM; elem++)
	{
		PlayerTextDrawHide(playerid,
			PTD_DurakBtn[p_info[playerid][durak_table]][p_info[playerid][durak_index]][btn][elem]);
	}
}

Durak_HideButtonForAll(const table, const btn)
{
	for(new g = 0; g < MAX_DURAK_PLAYERS; g++)
	{
		if(gDurakTable[table][dtPlayerId][g] == INVALID_PLAYER_ID)
			continue;
		
		Durak_HideButton(gDurakTable[table][dtPlayerId][g], btn);
	}
}

Durak_CreateButtons(const playerid, const table, const index)
{
	Durak_CreateButton(playerid,
		PTD_DurakBtn[table][index][DurakBtn_Left],
		DURAK_LEFT_BTN_X,
		DURAK_BTN_Y,
		DURAK_LEFT_BTN_WIDTH,
		DURAK_BTN_HEIGHT);
	
	Durak_CreateButton(playerid,
		PTD_DurakBtn[table][index][DurakBtn_Right],
		DURAK_RIGHT_BTN_X,
		DURAK_BTN_Y,
		DURAK_RIGHT_BTN_WIDTH,
		DURAK_BTN_HEIGHT);
	
	Durak_CreateButton(playerid,
		PTD_DurakBtn[table][index][DurakBtn_Mid],
		DURAK_MID_BTN_X,
		DURAK_BTN_Y,
		DURAK_MID_BTN_WIDTH,
		DURAK_BTN_HEIGHT);
	
	Durak_CreateButton(playerid,
		PTD_DurakBtn[table][index][DurakBtn_LargeInfo],
		DURAK_LARGE_INFO_BTN_X,
		DURAK_LARGE_INFO_BTN_Y,
		DURAK_LARGE_INFO_BTN_WIDTH,
		DURAK_LARGE_INFO_BTN_HEIGHT);
	
	Durak_CreateButton(playerid,
		PTD_DurakBtn[table][index][DurakBtn_Leave],
		640.0 - 60.0 - 40.0,
		40.0,
		60.0,
		DURAK_BTN_HEIGHT);
	
	Durak_CreateButton(playerid,
		PTD_DurakBtn[table][index][DurakBtn_PassTurn],
		0.0, 0.0, 0.0, 0.0);
}

Durak_DestroyButton(const playerid, const table, const index, const btn)
{
	for(new elem = 0; elem < DURAK_NUM_BTN_ELEM; elem++)
	{
		PlayerTextDrawDestroy(playerid, PTD_DurakBtn[table][index][btn][elem]);
	}
}

Durak_DestroyButtons(const playerid, const table, const index)
{
	for(new btn = 0; btn < DURAK_NUM_BTN; btn++)
	{
		Durak_DestroyButton(playerid, table, index, btn);
	}
}

Durak_CreateButton(const playerid, PlayerText:btn[DURAK_NUM_BTN_ELEM],
	const Float:x, const Float:y,
	const Float:w, const Float:h)
{
	btn[DurakBtnElem_Body] = CreatePlayerTextDraw(playerid, x, y, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, btn[DurakBtnElem_Body], w, h);
	PlayerTextDrawFont(playerid, btn[DurakBtnElem_Body], 4);
	PlayerTextDrawSetShadow(playerid, btn[DurakBtnElem_Body], 0);

	btn[DurakBtnElem_Text] = CreatePlayerTextDraw(playerid,
		x + w / 2.0,
		y + h / 4.0,
		" ");
	PlayerTextDrawLetterSize(playerid, btn[DurakBtnElem_Text], 0.2, 1.0);
	PlayerTextDrawAlignment(playerid, btn[DurakBtnElem_Text], 2);
	PlayerTextDrawFont(playerid, btn[DurakBtnElem_Text], 2);
	PlayerTextDrawSetProportional(playerid, btn[DurakBtnElem_Text], 1);
	PlayerTextDrawSetShadow(playerid, btn[DurakBtnElem_Text], 0);
}