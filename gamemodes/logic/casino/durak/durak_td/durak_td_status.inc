Durak_CreateStatus(const playerid, &PlayerText:status, const Float:x, const Float:y)
{
	status = CreatePlayerTextDraw(playerid, x, y, " ");
	PlayerTextDrawLetterSize(playerid, status, 0.175, 1.4);
	PlayerTextDrawAlignment(playerid, status, 2);
	PlayerTextDrawColor(playerid, status, -1);
	PlayerTextDrawSetShadow(playerid, status, 0);
	PlayerTextDrawFont(playerid, status, 2);
	PlayerTextDrawSetProportional(playerid, status, 1);
}

const Float:DURAK_STATUS_WIDTH = 60.0;
const Float:DURAK_STATUS_GAP = 15.0;

new PlayerText:PTD_DurakStatus[MAX_DURAK_TABLES + 1][MAX_DURAK_PLAYERS][MAX_DURAK_PLAYERS];

Durak_InitStatuses(const playerid, const table, const index, const from = 0)
{
	for(new i = from; i < MAX_DURAK_PLAYERS; i++)
	{
		Durak_CreateStatus(playerid, PTD_DurakStatus[table][index][i],
			0.0, 0.0);
	}
}

Durak_DestroyStatuses(const playerid, const table, const index)
{
	for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
	{
		PlayerTextDrawDestroy(playerid, PTD_DurakStatus[table][index][i]);
	}
}

Durak_CreateStatuses(const playerid, const count)
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	Durak_DestroyStatuses(playerid, table, index);

	new Float:offset = (640.0 - (count - 1) * (DURAK_STATUS_WIDTH + DURAK_STATUS_GAP)) / 2.0;

	for(new i = 0; i < count; i++)
	{
		Durak_CreateStatus(playerid, PTD_DurakStatus[table][index][i],
			offset + (DURAK_STATUS_WIDTH + DURAK_STATUS_GAP) * i,
			120.0);
	}

	Durak_InitStatuses(playerid, table, index, .from = count);
}

Durak_ShowStatus(const playerid, const number, const text[])
{
	new table = p_info[playerid][durak_table];
	new index = p_info[playerid][durak_index];

	PlayerTextDrawSetString(playerid, PTD_DurakStatus[table][index][number], text);
	PlayerTextDrawShow(playerid, PTD_DurakStatus[table][index][number]);
}