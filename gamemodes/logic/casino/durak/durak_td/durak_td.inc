new Text:TD_DurakTable;

Durak_CreateTD()
{
	TD_DurakTable = TextDrawCreate(-160.0, -620.0, "");
	TextDrawTextSize(TD_DurakTable, 960.0, 1280.0);
	TextDrawAlignment(TD_DurakTable, 1);
	TextDrawColor(TD_DurakTable, 0xc7e1fbff);
	TextDrawBackgroundColor(TD_DurakTable, 0);
	TextDrawFont(TD_DurakTable, 5);
	TextDrawSetProportional(TD_DurakTable, 0);
	TextDrawSetPreviewModel(TD_DurakTable, 11691);
	TextDrawSetPreviewRot(TD_DurakTable, -90.000000, 0.000000, 0.000000, 1.000000);
}

Durak_HideTD(const playerid)
{
	TextDrawHideForPlayer(playerid, TD_DurakTable);
}

Durak_CreatePTD(const playerid, const table, const index)
{
	Durak_InitBoard(playerid, table, index);
	Durak_InitDeck(playerid, table, index);
	Durak_InitStatuses(playerid, table, index);
	Durak_CreateButtons(playerid, table, index);
	Durak_CreateTrump(playerid, table, index);
}

Durak_DestroyPTD(const playerid, const table, const index)
{
	Durak_DestroyBoard(playerid, table, index);
	Durak_DestroyDeck(playerid, table, index);
	Durak_DestroyStatuses(playerid, table, index);
	Durak_DestroyButtons(playerid, table, index);
	Durak_DestroyTrump(playerid, table, index);
}