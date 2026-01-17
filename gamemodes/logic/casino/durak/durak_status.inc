Durak_UpdateStatus(const table)
{
	for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
	{
		if(gDurakTable[table][dtPlayerId][i] == INVALID_PLAYER_ID)
			continue;
		
		Durak_CreateStatuses(gDurakTable[table][dtPlayerId][i], gDurakTable[table][dtPlayerCount]);
	}

	for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
	{
		if(gDurakTable[table][dtPlayerId][i] == INVALID_PLAYER_ID)
			continue;

		Durak_UpdatePlayerStatus(table, i);
	}
}

Durak_UpdatePlayerStatus(const table, const updatedIndex)
{
	new updatedId = gDurakTable[table][dtPlayerId][updatedIndex];
	new updatedNum = gDurakTable[table][dtPlayerNumber][updatedIndex];

	new status[128];

	format(status, sizeof status,
		"~y~%d. ~w~%s~y~(%d)",

		updatedNum + 1,
		p_info[updatedId][name],
		updatedId);
	
	switch(gDurakTable[table][dtLobbyState])
	{
	case DurakLobby_InGame:
	{
		if(updatedIndex == gDurakTable[table][dtTurnIndex])
			strcat(status, "~n~~g~~h~~h~~h~Turn");
		else if(updatedIndex == gDurakTable[table][dtDefenderIndex])
			strcat(status, "~n~~r~~h~~h~~h~Defender");
		
		format(status, sizeof status, "%s~n~~w~Cards ~y~%d",
			status,
			p_info[updatedId][durak_deckSize]);
		
		if(p_info[updatedId][durak_beaten])
			strcat(status, "~n~Beaten");
		if(p_info[updatedId][durak_allowTake])
			strcat(status, "~n~Allow Take");
	}
	default:
	{
		if(p_info[updatedId][durak_ready])
		{
			format(status, sizeof status, "%s~n~~w~Bet ~g~~h~~h~$%d~n~%s",
				status,
				gDurakTable[table][dtBet],
				(gDurakTable[table][dtMode] == DurakMode_PassTurn) ? ("Pass") : ("Simple"));
		}
		else
		{
			strcat(status, "~n~~r~~h~~h~Not Ready");
		}
	}
	}

	new yourStatus[sizeof status];
	strcat(yourStatus, status);
	strcat(yourStatus, "~n~~y~You");
	
	for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
	{
		if(gDurakTable[table][dtPlayerId][i] == INVALID_PLAYER_ID)
			continue;
		
		Durak_ShowStatus(gDurakTable[table][dtPlayerId][i],
			updatedNum,
			(i == updatedIndex) ? yourStatus : status);
	}
}