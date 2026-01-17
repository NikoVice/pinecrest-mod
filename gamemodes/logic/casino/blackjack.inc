// BlackJack settings
#define MAX_BLACKJACK_TABLES (3)
#define MAX_BLACKJACK_TABLE_PLAYERS (3)
#define MAX_BLACKJACK_BUTTONS (5)
#define MAX_BLACKJACK_INFO_TEXTDRAWS (3)
#define MAX_BLACKJACK_SUITS_CARDS (4)
#define MAX_BLACKJACK_CARDS_TEXTDRAWS (11)
#define MAX_BLACKJACK_CARDS (13)

enum
{
    BJ_StateNone,
    BJ_StateWaitBets,
    BJ_StateGame,
    BJ_StateFinish
};

enum
{
    BJ_ButtonStayOrBet,
    BJ_ButtonExit,
    BJ_ButtonDouble,
    BJ_ButtonHit,
    BJ_ButtonSplit
};

// Main variables
enum E_BLACKJACK_TABLE_DATA
{
    BJ_TableObjectID, // Streamer object id

    Float:BJ_TablePosX, // Table position
    Float:BJ_TablePosY,
    Float:BJ_TablePosZ,

    BJ_TableInteriorID,
    BJ_TableVirtualWorldID,

    Float:BJ_TableRotX, // Table rotation
    Float:BJ_TableRotY,
    Float:BJ_TableRotZ,

    BJ_DealerActorID, // Streamer actor id

    Text3D:BJ_TableInfo, // Streamer text id

    BJ_TablePlayersCount,
    BJ_TablePlayers[MAX_BLACKJACK_TABLE_PLAYERS],

    BJ_CurrentTableState,

    Text:BJ_DealerTextdraws[MAX_BLACKJACK_INFO_TEXTDRAWS],

    BJ_TableGameTimer,
    BJ_TableGameCounter,

    BJ_TableCurrentPlayer,
    BJ_TableCurrentRound,

    Text:BJ_DealerCardsTextdraws[MAX_BLACKJACK_CARDS_TEXTDRAWS],

    BJ_DealerPoints,

    BJ_DealerCardData[2],

    BJ_TableCustomID
};
new blackjackTableData[MAX_BLACKJACK_TABLES][E_BLACKJACK_TABLE_DATA];

enum E_BLACKJACK_PLAYER_DATA
{
    BJ_CurrentTableID,
    BJ_CurrentTableSlotID,

    PlayerText:BJ_Buttons[MAX_BLACKJACK_BUTTONS],
    bool:BJ_ButtonsState[MAX_BLACKJACK_BUTTONS],

    BJ_SetBet[2],

    PlayerText:BJ_PlayerTextdraws[MAX_BLACKJACK_INFO_TEXTDRAWS],

    BJ_OtherPlayers[MAX_BLACKJACK_TABLE_PLAYERS - 1],

    PlayerText:BJ_PlayerCardsTextdraws[MAX_BLACKJACK_CARDS_TEXTDRAWS * 2],

    BJ_IsMapSplitted,

    BJ_PlayerPoints[2]
};
new blackjackPlayerData[MAX_PLAYERS][E_BLACKJACK_PLAYER_DATA];

enum E_BLACKJACK_BUTTON_DATA
{
    Float:BJ_ButtonPosX,
    Float:BJ_ButtonPosY,

    BJ_ButtonName[7]
};
new blackjackButtonData[MAX_BLACKJACK_BUTTONS][E_BLACKJACK_BUTTON_DATA] = {
    {426.0, 420.0, "BET"},
    {529.0, 420.0, "EXIT"},
    {323.0, 420.0, "DOUBLE"},
    {220.0, 420.0, "HIT"},
    {117.0, 420.0, "SPLIT"}
};

enum E_BLACKJACK_MAP_DATA
{
    Float:BJ_MapPosX,
    Float:BJ_MapPosY,

    Float:BJ_MapCardPosX,
    Float:BJ_MapCardPosY,

    Float:BJ_MapSplitPosX,
    Float:BJ_MapSplitPosY,

    Float:BJ_MapSplitCardPosX,
    Float:BJ_MapSplitCardPosY,

    Float:BJ_MapInfoPosX,
    Float:BJ_MapInfoPosY
};
new blackjackMapData[MAX_BLACKJACK_TABLE_PLAYERS - 1][E_BLACKJACK_MAP_DATA] = {
    {160.0, 165.0, 97.0, 166.0, 160.0, 235.0, 97.0, 236.0, 160.0, 133.0},
    {480.0, 165.0, 417.0, 166.0, 480.0, 235.0, 417.0, 236.0, 480.0, 133.0}
};

new blackjackCardsData[MAX_BLACKJACK_CARDS][MAX_BLACKJACK_SUITS_CARDS + 1][] = {
    {"2", "LD_CARD:cd2h", "LD_CARD:cd2d", "LD_CARD:cd2c", "LD_CARD:cd2s"},
    {"3", "LD_CARD:cd3h", "LD_CARD:cd3d", "LD_CARD:cd3c", "LD_CARD:cd3s"},
    {"4", "LD_CARD:cd4h", "LD_CARD:cd4d", "LD_CARD:cd4c", "LD_CARD:cd4s"},
    {"5", "LD_CARD:cd5h", "LD_CARD:cd5d", "LD_CARD:cd5c", "LD_CARD:cd5s"},
    {"6", "LD_CARD:cd6h", "LD_CARD:cd6d", "LD_CARD:cd6c", "LD_CARD:cd6s"},
    {"7", "LD_CARD:cd7h", "LD_CARD:cd7d", "LD_CARD:cd7c", "LD_CARD:cd7s"},
    {"8", "LD_CARD:cd8h", "LD_CARD:cd8d", "LD_CARD:cd8c", "LD_CARD:cd8s"},
    {"9", "LD_CARD:cd9h", "LD_CARD:cd9d", "LD_CARD:cd9c", "LD_CARD:cd9s"},
    {"10", "LD_CARD:cd10h", "LD_CARD:cd10d", "LD_CARD:cd10c", "LD_CARD:cd10s"},
    {"Валет", "LD_CARD:cd11h", "LD_CARD:cd11d", "LD_CARD:cd11c", "LD_CARD:cd11s"},
    {"Дама", "LD_CARD:cd12h", "LD_CARD:cd12d", "LD_CARD:cd12c", "LD_CARD:cd12s"},
    {"Король", "LD_CARD:cd13h", "LD_CARD:cd13d", "LD_CARD:cd13c", "LD_CARD:cd13s"},
    {"Туз", "LD_CARD:cd1h", "LD_CARD:cd1d", "LD_CARD:cd1c", "LD_CARD:cd1s"}
};

new blackjackTableCardsCount[MAX_BLACKJACK_TABLES][MAX_BLACKJACK_SUITS_CARDS][MAX_BLACKJACK_CARDS];

new PlayerText:blackjackOtherPData[MAX_PLAYERS][MAX_BLACKJACK_TABLE_PLAYERS - 1][MAX_BLACKJACK_INFO_TEXTDRAWS];
new PlayerText:blackjackOtherPCardsData[MAX_PLAYERS][MAX_BLACKJACK_TABLE_PLAYERS - 1][MAX_BLACKJACK_CARDS_TEXTDRAWS * 2];

new blackjackPlayerCardsData[MAX_PLAYERS][2][MAX_BLACKJACK_CARDS_TEXTDRAWS * 2];

// Timers
forward BlackjackGameTableUpdater(tableID);
public BlackjackGameTableUpdater(tableID)
{
    new tmp, id;
    switch(blackjackTableData[tableID][BJ_CurrentTableState])
    {
        case BJ_StateNone:
        {
            for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
            {
                id = blackjackTableData[tableID][BJ_TablePlayers][i];

                if(id == -1 || blackjackPlayerData[id][BJ_SetBet][0] <= 0)
                    continue;

                tmp = true;
                break;
            }
            if(tmp)
            {
                blackjackTableData[tableID][BJ_TableGameCounter] = 8;

                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "~r~WAIT BETS: %d SECONDS", blackjackTableData[tableID][BJ_TableGameCounter]);
                UpdateBJGameCounterTextdraw(tableID, STRING_GLOBAL);

                blackjackTableData[tableID][BJ_CurrentTableState] = BJ_StateWaitBets;
            }
        }
        case BJ_StateWaitBets:
        {
            blackjackTableData[tableID][BJ_TableGameCounter]--;

            if(blackjackTableData[tableID][BJ_TableGameCounter] <= 0)
            {
                HideBJGameCounterTextdrawForAll(tableID);

                blackjackTableData[tableID][BJ_CurrentTableState] = BJ_StateGame;

                for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
                {
                    id = blackjackTableData[tableID][BJ_TablePlayers][i];

                    if(id == -1)
                        continue;

                    SetActiveBlackjackButtons(id, tableID);
                }
            }
            else
            {
                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "~r~WAIT BETS: %d SECONDS", blackjackTableData[tableID][BJ_TableGameCounter]);
                UpdateBJGameCounterTextdraw(tableID, STRING_GLOBAL);
            }
        }
        case BJ_StateGame:
        {
            new
                id = GetBJNextPlayerIDForGame(tableID);

            if(blackjackTableData[tableID][BJ_TableCurrentRound] >= 2)
            {
                if(blackjackTableData[tableID][BJ_TableGameCounter] <= 0)
                {
                    tmp = blackjackTableData[tableID][BJ_TableCurrentPlayer];

                    blackjackTableData[tableID][BJ_TableCurrentPlayer] = id;

                    if(tmp != -1 && blackjackTableData[tableID][BJ_TablePlayers][tmp] != -1)
                        SetActiveBlackjackButtons(blackjackTableData[tableID][BJ_TablePlayers][tmp], tableID);

                    if(id == -1)
                    {
                        blackjackTableData[tableID][BJ_TableCurrentRound]++;

                        HideBJGameCounterTextdrawForAll(tableID);
                        ShowBJDealerCardForAll(tableID);

                        while(blackjackTableData[tableID][BJ_DealerPoints] < 17)
                            AddBJCardToPlayerOrDealer(tableID, id);

                        blackjackTableData[tableID][BJ_CurrentTableState] = BJ_StateFinish;
                        return;
                    }

                    blackjackTableData[tableID][BJ_TableGameCounter] = 30;

                    tmp = blackjackTableData[tableID][BJ_TablePlayers][id];

                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "~b~%s (%d)~n~~g~%d SECONDS LEFT", get_name(tmp), tmp, blackjackTableData[tableID][BJ_TableGameCounter]);
                    UpdateBJGameCounterTextdraw(tableID, STRING_GLOBAL);

                    SetActiveBlackjackButtons(tmp, tableID);
                }
                else
                {
                    blackjackTableData[tableID][BJ_TableGameCounter]--;

                    tmp = blackjackTableData[tableID][BJ_TablePlayers][blackjackTableData[tableID][BJ_TableCurrentPlayer]];

                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "~b~%s (%d)~n~~g~%d SECONDS LEFT", get_name(tmp), tmp, blackjackTableData[tableID][BJ_TableGameCounter]);
                    UpdateBJGameCounterTextdraw(tableID, STRING_GLOBAL);
                }

                return;
            }
            else if((blackjackTableData[tableID][BJ_TableCurrentPlayer] = id) == -1)
                blackjackTableData[tableID][BJ_TableCurrentRound]++;

            AddBJCardToPlayerOrDealer(tableID, id);
        }
        case BJ_StateFinish:
        {
            if(blackjackTableData[tableID][BJ_TableCurrentRound] == 3)
            {
                blackjackTableData[tableID][BJ_TableCurrentRound]++;
                blackjackTableData[tableID][BJ_TableGameCounter] = 3;

                for(new i, player, sum, dealer = blackjackTableData[tableID][BJ_DealerPoints]; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
                {
                    if((player = blackjackTableData[tableID][BJ_TablePlayers][i]) == -1 || blackjackPlayerData[player][BJ_SetBet][0] <= 0)
                        continue;

                    sum = 0;

                    for(new j, points; j < 2; j++)
                    {
                        if(blackjackPlayerData[player][BJ_SetBet][j] <= 0)
                            continue;

                        points = blackjackPlayerData[player][BJ_PlayerPoints][j];

                        if((points > dealer && points <= 21) || (dealer > points && dealer > 21 && points <= 21))
                            sum += floatround(float(blackjackPlayerData[player][BJ_SetBet][j]) * 1.7);
                        else if(dealer == points && points <= 21)
                            sum += blackjackPlayerData[player][BJ_SetBet][j];
                        else
                            sum -= blackjackPlayerData[player][BJ_SetBet][j];
                    }

                    if(blackjackPlayerData[player][BJ_SetBet][0] + blackjackPlayerData[player][BJ_SetBet][1] == sum)
                    {
                        SendInfo(player, "К сожалению, Вы сыграли в ничью. Ставка в размере $%d возвращена.", sum);
                        SetPlayerMoney(player, sum, true, "ничья в blackjack");
                    }
                    else if(sum > 0)
                    {
                        SendInfo(player, "Поздравляем, Вы выиграли $%d.", sum);
                        SetPlayerMoney(player, sum, true, "выиграш в blackjack");
                    }
                    else 
                        SendInfo(player, "К сожалению, Вы проиграли $%d.", (sum *= -1));
                }

                STRING_GLOBAL[0] = EOS;
                f(STRING_GLOBAL, "~p~%d SECONDS TO RESTART", blackjackTableData[tableID][BJ_TableGameCounter]);
                UpdateBJGameCounterTextdraw(tableID, STRING_GLOBAL);

                UpdateBJDealerInfoTextdraw(tableID);
            }
            else
            {
                blackjackTableData[tableID][BJ_TableGameCounter]--;

                if(blackjackTableData[tableID][BJ_TableGameCounter] <= 0)
                {
                    HideBJGameCounterTextdrawForAll(tableID);
                    ClearTableDataAfterGame(tableID, true);
                    UpdateBJDealerInfoTextdraw(tableID);

                    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
                    {
                        if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
                            continue;

                        ClearPlayerDataAfterGame(blackjackTableData[tableID][BJ_TablePlayers][i], true);
                        SetActiveBlackjackButtons(blackjackTableData[tableID][BJ_TablePlayers][i], tableID);
                    }
                }
                else
                {
                    f(STRING_GLOBAL, "~p~%d SECONDS TO RESTART", blackjackTableData[tableID][BJ_TableGameCounter]);
                    UpdateBJGameCounterTextdraw(tableID, STRING_GLOBAL);
                }
            }
        }
    }
}

// Public' hook
stock BJ_OnGameModeInit() // Clear all table data on mode init
{
    for(new i; i < MAX_BLACKJACK_TABLES; i++)
        ClearAllBlackjackTableData(i);

    CreateBlackjackTable(INVALID_PLAYER_ID, 1969.5, 1009.658142, 1992.5, 0.000000, 0.000000, 90.0, 1, 1, 0);
    CreateBlackjackTable(INVALID_PLAYER_ID, 1969.5, 1017.767395, 1992.5, 0.000000, 0.000000, 90.0, 1, 1, 1);
    CreateBlackjackTable(INVALID_PLAYER_ID, 1969.5, 1026.074218, 1992.5, 0.000000, 0.000000, 90.0, 1, 1, 0);
    return 1;
}

stock BJ_OnPlayerEditDynObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz) // Change table data if this create by player
{
    if(GetPVarInt(playerid, "BLACKJACK_CREATE_TABLE_OBJECT_ID") == objectid && response != EDIT_RESPONSE_UPDATE)
    {
        new tableID = GetPVarInt(playerid, "BLACKJACK_CREATE_TABLE_ARRAY_ID");

        SetDynamicObjectPos(blackjackTableData[tableID][BJ_TableObjectID], x, y, z);
        SetDynamicObjectRot(blackjackTableData[tableID][BJ_TableObjectID], rx, ry, rz);

        CreateDealerToBlackjackTable(tableID, x, y, z, rz);

        blackjackTableData[tableID][BJ_TablePosX] = x;
        blackjackTableData[tableID][BJ_TablePosY] = y;
        blackjackTableData[tableID][BJ_TablePosZ] = z;

        blackjackTableData[tableID][BJ_TableRotX] = rx;
        blackjackTableData[tableID][BJ_TableRotY] = ry;
        blackjackTableData[tableID][BJ_TableRotZ] = rz;

        x -= (0.5 * floatsin(-rz, degrees));
        y -= (0.5 * floatcos(-rz, degrees));

        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, blackjackTableData[tableID][BJ_TableInfo], E_STREAMER_X, x);
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, blackjackTableData[tableID][BJ_TableInfo], E_STREAMER_Y, y);
        Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, blackjackTableData[tableID][BJ_TableInfo], E_STREAMER_Z, z);

        CreateBlackjackTableInfo(tableID, false);

        DeletePVar(playerid, "BLACKJACK_CREATE_TABLE_OBJECT_ID");
        DeletePVar(playerid, "BLACKJACK_CREATE_TABLE_ARRAY_ID");

        printf("%d, %f, %f, %f, %f, %f, %f", tableID, x, y, z, rx, ry, rz);

        Streamer_Update(playerid);
		return 1;
    }
    return 1;
}

stock BJ_OnPlayerClickTD(playerid, Text:clickedid)
{
    if(clickedid == INVALID_TEXT_DRAW && blackjackPlayerData[playerid][BJ_CurrentTableID] != -1)
    {
        ShowBlackjackButtonsForPlayer(playerid);
        return 1;
    }
    return 0;
}

stock BJ_OnPlayerClickPlayerTD(playerid, PlayerText:playertextid)
{
    new tableID = blackjackPlayerData[playerid][BJ_CurrentTableID];
    if(tableID == -1)
        return 0;

    new pressedButton = -1;
    for(new i; i < MAX_BLACKJACK_BUTTONS; i++)
    {
        if(blackjackPlayerData[playerid][BJ_Buttons][i] == playertextid)
        {
            pressedButton = i;
            break;
        }
    }

    if(pressedButton == -1 || !blackjackPlayerData[playerid][BJ_ButtonsState][pressedButton] || blackjackTableData[tableID][BJ_TableGameCounter] <= 0 &&
        blackjackTableData[tableID][BJ_CurrentTableState] == BJ_StateGame)
        return 0;

    switch(pressedButton)
    {
        case BJ_ButtonStayOrBet:
        {
            if(blackjackPlayerData[playerid][BJ_SetBet][0] <= 0 && (blackjackTableData[tableID][BJ_CurrentTableState] == BJ_StateNone || blackjackTableData[tableID][BJ_CurrentTableState] == BJ_StateWaitBets))
            {
                ShowPlayerDialog(playerid, D_BLACKJACK_SET_BET, DIALOG_STYLE_INPUT, "Ставка", ""W"Введите сумму которую желаете поставить:", "Поставить", "Закрыть");
            }
            else
                SetBJNextPlayerOrHand(tableID, playerid);
        }
        case BJ_ButtonExit:
        {
            ExitPlayerFromBlackjackTable(playerid, tableID);
            return 1;
        }
        case BJ_ButtonDouble:
        {
            pressedButton = blackjackPlayerData[playerid][BJ_IsMapSplitted] == -1 ? (0) : (blackjackPlayerData[playerid][BJ_IsMapSplitted]);

            if(blackjackPlayerData[playerid][BJ_SetBet][pressedButton] > p_info[playerid][cash])
            {
                SetActiveBlackjackButtons(playerid, tableID);
                return SendError(playerid, "Недостаточно денег чтобы сделать ставку.");
            }
            SetPlayerMoney(playerid, -blackjackPlayerData[playerid][BJ_SetBet][pressedButton], true, "ставка в blackjack");

            blackjackPlayerData[playerid][BJ_SetBet][pressedButton] *= 2;

            AddBJCardToPlayerOrDealer(tableID, blackjackPlayerData[playerid][BJ_CurrentTableSlotID], pressedButton);
            SetBJNextPlayerOrHand(tableID, playerid);
        }
        case BJ_ButtonHit:
        {
            AddBJCardToPlayerOrDealer(tableID, blackjackPlayerData[playerid][BJ_CurrentTableSlotID],
                blackjackPlayerData[playerid][BJ_IsMapSplitted] == -1 ? (0) : (blackjackPlayerData[playerid][BJ_IsMapSplitted]));
        }
        case BJ_ButtonSplit:
        {
            if(blackjackPlayerData[playerid][BJ_SetBet][0] > p_info[playerid][cash])
            {
                SetActiveBlackjackButtons(playerid, tableID);
                SendError(playerid, "Недостаточно денег чтобы сделать ставку.");
                return 1;
            }
            SetPlayerMoney(playerid, -blackjackPlayerData[playerid][BJ_SetBet][0], true, "ставка в blackjack");

            blackjackPlayerData[playerid][BJ_IsMapSplitted] = 0;
            blackjackPlayerData[playerid][BJ_SetBet][1] = blackjackPlayerData[playerid][BJ_SetBet][0];

            if(blackjackPlayerCardsData[playerid][1][0] == 12)
                blackjackPlayerData[playerid][BJ_PlayerPoints][0] = (blackjackPlayerData[playerid][BJ_PlayerPoints][1] = 11);
            else
                blackjackPlayerData[playerid][BJ_PlayerPoints][1] = (blackjackPlayerData[playerid][BJ_PlayerPoints][0] /= 2);

            SplitBJPlayerCardForAll(playerid);

            SendInfo(playerid, "Вы разделили руки. В данный момент играет первая рука.");
        }
    }
    SetActiveBlackjackButtons(playerid, tableID);
    return 1;
}

BJ_OnPlayerDisconnect(playerid)
{
    new tableID = blackjackPlayerData[playerid][BJ_CurrentTableID];
    if(tableID == -1) return 1;
    ExitPlayerFromBlackjackTable(playerid, tableID);
    return 1;
}

// Functions
CreateBlackjackTable(playerid = INVALID_PLAYER_ID, Float:x = 0.0, Float:y = 0.0, Float:z = 0.0, Float:rx = 0.0, Float:ry = 0.0, Float:rz = 0.0, interiorID = 0, virtualWorldID = 0, type = 0, customID = -1)
{
    new tableID = GetFreeBlackjackTableID();
    if(tableID == -1)
        return -1;

    blackjackTableData[tableID][BJ_TableObjectID] = CreateDynamicObject(2188, x, y, z, rx, ry, rz, virtualWorldID, interiorID);
    blackjackTableData[tableID][BJ_TableCustomID] = customID;

    switch(type)
    {
        case 1:
        {
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 0, 2176, "casino_props", "marblebox", 0x00000000);
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 2, 2176, "casino_props", "marblebox", 0x00000000);
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 4, 2176, "casino_props", "marblebox", 0x00000000);
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 5, 18646, "matcolours", "grey-93-percent", 0x00000000);
        }
        case 2:
        {
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 0, 14652, "ab_trukstpa", "wood01", 0x00000000);
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 2, 14652, "ab_trukstpa", "wood01", 0x00000000);
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 4, 14652, "ab_trukstpa", "wood01", 0x00000000);
            SetDynamicObjectMaterial(blackjackTableData[tableID][BJ_TableObjectID], 5, 8391, "ballys01", "CJ_blackplastic", 0x00000000);
        }
    }

    if(playerid != INVALID_PLAYER_ID)
    {
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, rz);

        x += (2.5 * floatsin(-rz, degrees));
        y += (2.5 * floatcos(-rz, degrees));

        interiorID = GetPlayerInterior(playerid);
        virtualWorldID = GetPlayerVirtualWorld(playerid);

        Streamer_SetFloatData(STREAMER_TYPE_OBJECT, blackjackTableData[tableID][BJ_TableObjectID], E_STREAMER_R_Z, rz);

        SetPVarInt(playerid, "BLACKJACK_CREATE_TABLE_OBJECT_ID", blackjackTableData[tableID][BJ_TableObjectID]);
        SetPVarInt(playerid, "BLACKJACK_CREATE_TABLE_ARRAY_ID", tableID);
    }

    blackjackTableData[tableID][BJ_TablePosX] = x;
    blackjackTableData[tableID][BJ_TablePosY] = y;
    blackjackTableData[tableID][BJ_TablePosZ] = z;

    blackjackTableData[tableID][BJ_TableRotX] = rx;
    blackjackTableData[tableID][BJ_TableRotY] = ry;
    blackjackTableData[tableID][BJ_TableRotZ] = rz;

	blackjackTableData[tableID][BJ_TableInteriorID] = interiorID;
	blackjackTableData[tableID][BJ_TableVirtualWorldID] = virtualWorldID;

    SetDynamicObjectPos(blackjackTableData[tableID][BJ_TableObjectID], x, y, z);
    SetDynamicObjectRot(blackjackTableData[tableID][BJ_TableObjectID], rx, ry, rz);

    Streamer_SetIntData(STREAMER_TYPE_OBJECT, blackjackTableData[tableID][BJ_TableObjectID], E_STREAMER_INTERIOR_ID, interiorID);
    Streamer_SetIntData(STREAMER_TYPE_OBJECT, blackjackTableData[tableID][BJ_TableObjectID], E_STREAMER_WORLD_ID, virtualWorldID);

    CreateDealerToBlackjackTable(tableID, x, y, z, rz);
    CreateBlackjackTableInfo(tableID);

    if(playerid != INVALID_PLAYER_ID)
        EditDynamicObject(playerid, blackjackTableData[tableID][BJ_TableObjectID]);

    return tableID;
}

GetFreeBlackjackTableID()
{
    for(new i; i < MAX_BLACKJACK_TABLES; i++)
    {
        if(blackjackTableData[i][BJ_TableObjectID] == -1)
            return i;
	}

	return -1;
}

ClearAllBlackjackTableData(tableID)
{
    blackjackTableData[tableID][BJ_TableCustomID] =
    blackjackTableData[tableID][BJ_TableObjectID] =
    blackjackTableData[tableID][BJ_DealerActorID] =
    blackjackTableData[tableID][BJ_TableCurrentPlayer] =
    blackjackTableData[tableID][BJ_DealerCardData][0] =
    blackjackTableData[tableID][BJ_DealerCardData][1] = -1;

    blackjackTableData[tableID][BJ_TablePosX] =
    blackjackTableData[tableID][BJ_TablePosY] =
    blackjackTableData[tableID][BJ_TablePosZ] =
    blackjackTableData[tableID][BJ_TableRotX] =
    blackjackTableData[tableID][BJ_TableRotY] =
    blackjackTableData[tableID][BJ_TableRotZ] = 0.0;

    blackjackTableData[tableID][BJ_TableInteriorID] =
    blackjackTableData[tableID][BJ_TableVirtualWorldID] =
    blackjackTableData[tableID][BJ_TablePlayersCount] =
    blackjackTableData[tableID][BJ_TableGameCounter] =
    blackjackTableData[tableID][BJ_TableCurrentRound] =
    blackjackTableData[tableID][BJ_DealerPoints] = 0;

    blackjackTableData[tableID][BJ_TableInfo] = Text3D:INVALID_3DTEXT_ID;

    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
        blackjackTableData[tableID][BJ_TablePlayers][i] = -1;

    blackjackTableData[tableID][BJ_CurrentTableState] = BJ_StateNone;

    for(new i; i < MAX_BLACKJACK_INFO_TEXTDRAWS; i++)
        blackjackTableData[tableID][BJ_DealerTextdraws][i] = INVALID_TEXT_DRAW;

    blackjackTableData[tableID][BJ_TableGameTimer] = -1;

    for(new i; i < MAX_BLACKJACK_SUITS_CARDS; i++)
    {
        for(new j; j < MAX_BLACKJACK_CARDS; j++)
            blackjackTableCardsCount[tableID][i][j] = 6;
    }

    for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS; i++)
        blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] = INVALID_TEXT_DRAW;
}

CreateDealerToBlackjackTable(tableID, Float:x, Float:y, Float:z, Float:rz)
{
    x += (0.5 * floatsin(-rz, degrees));
    y += (0.5 * floatcos(-rz, degrees));

    if(IsValidDynamicActor(blackjackTableData[tableID][BJ_DealerActorID]))
        DestroyDynamicActor(blackjackTableData[tableID][BJ_DealerActorID]);

    blackjackTableData[tableID][BJ_DealerActorID] = CreateDynamicActor(171, x, y, z, rz - 180.0, .worldid = blackjackTableData[tableID][BJ_TableVirtualWorldID], .interiorid = blackjackTableData[tableID][BJ_TableInteriorID]);
}

CreateBlackjackTableInfo(tableID, bool:create = true)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "{FFFFFF}Игровой стол {FFFF00}#%d\n{FFFFFF}Доступно для игры: {FFFF00}%d из %d {FFFFFF}мест\n{FFFFFF}Нажмите {FFFF00}ALT {FFFFFF}для игры",
        blackjackTableData[tableID][BJ_TableCustomID] == -1 ? (tableID + 1) : (blackjackTableData[tableID][BJ_TableCustomID]), MAX_BLACKJACK_TABLE_PLAYERS - blackjackTableData[tableID][BJ_TablePlayersCount], MAX_BLACKJACK_TABLE_PLAYERS);

    if(create)
    {
        new
            Float:x = blackjackTableData[tableID][BJ_TablePosX],
            Float:y = blackjackTableData[tableID][BJ_TablePosY];

        x -= (0.5 * floatsin(-blackjackTableData[tableID][BJ_TableRotZ], degrees));
        y -= (0.5 * floatcos(-blackjackTableData[tableID][BJ_TableRotZ], degrees));

        blackjackTableData[tableID][BJ_TableInfo] = CreateDynamic3DTextLabel(STRING_GLOBAL, 0xFFFFFFFF, x, y, blackjackTableData[tableID][BJ_TablePosZ], 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, false,
            blackjackTableData[tableID][BJ_TableVirtualWorldID], blackjackTableData[tableID][BJ_TableInteriorID]);
    }
    else
        UpdateDynamic3DTextLabelText(blackjackTableData[tableID][BJ_TableInfo], 0xFFFFFFFF, STRING_GLOBAL);
}

GetNearestPlayerBlackjackTable(playerid)
{
    new
        virtualWorldID = GetPlayerVirtualWorld(playerid),
        interiorID = GetPlayerInterior(playerid);

    for(new i; i < MAX_BLACKJACK_TABLES; i++)
    {
        if(IsPlayerInRangeOfPoint(playerid, 2.5, blackjackTableData[i][BJ_TablePosX], blackjackTableData[i][BJ_TablePosY], blackjackTableData[i][BJ_TablePosZ]) &&
        virtualWorldID == blackjackTableData[i][BJ_TableVirtualWorldID] && interiorID == blackjackTableData[i][BJ_TableInteriorID] && blackjackTableData[i][BJ_TableObjectID] != -1)
            return i;
    }

    return -1;
}

AttachPlayerToBlackjackTable(playerid, tableID)
{
    if(blackjackPlayerData[playerid][BJ_CurrentTableID] != -1)
        return SendError(playerid, "Вы уже находитесь за игровым столом.");

    if(blackjackTableData[tableID][BJ_TablePlayersCount] >= MAX_BLACKJACK_TABLE_PLAYERS)
        return SendError(playerid, "За данным столом нет свободных мест.");

    new
        slotID = GetFreeBlackjackTableSlotID(tableID);

    if(slotID == -1)
        return SendError(playerid, "За данным столом нет свободных мест.");

    blackjackPlayerData[playerid][BJ_CurrentTableID] = tableID;
    blackjackPlayerData[playerid][BJ_CurrentTableSlotID] = slotID;

    blackjackTableData[tableID][BJ_TablePlayersCount]++;
    blackjackTableData[tableID][BJ_TablePlayers][slotID] = playerid;

    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    {
        if((slotID = blackjackTableData[tableID][BJ_TablePlayers][i]) == -1 || slotID == playerid)
            continue;

        AddBlackjackPlayerToPlayer(playerid, slotID);
        AddBlackjackPlayerToPlayer(slotID, playerid);
    }

    if(blackjackTableData[tableID][BJ_TableGameTimer] == -1)
        blackjackTableData[tableID][BJ_TableGameTimer] = SetTimerEx("BlackjackGameTableUpdater", 1000, true, "i", tableID);

    Fix_TogglePlayerControllable(playerid, false);

    new
        Float:x = blackjackTableData[tableID][BJ_TablePosX],
        Float:y = blackjackTableData[tableID][BJ_TablePosY];

    x -= (2.5 * floatsin(-blackjackTableData[tableID][BJ_TableRotZ], degrees));
    y -= (2.5 * floatcos(-blackjackTableData[tableID][BJ_TableRotZ], degrees));

    SetPlayerCameraPos(playerid, x, y, blackjackTableData[tableID][BJ_TablePosZ] + 1.5);
    SetPlayerCameraLookAt(playerid, blackjackTableData[tableID][BJ_TablePosX], blackjackTableData[tableID][BJ_TablePosY], blackjackTableData[tableID][BJ_TablePosZ] + 0.3, CAMERA_MOVE);

    CreateBlackjackTableInfo(tableID, false);

    Streamer_ToggleItem(playerid, STREAMER_TYPE_3D_TEXT_LABEL, blackjackTableData[tableID][BJ_TableInfo], false);

    CreateBlackjackButtonsForPlayer(playerid);
    SetActiveBlackjackButtons(playerid, tableID);

    CreateAndShowBlackjackDealerTD(playerid, tableID);

    CreateAndShowBlackjackPlayerTD(playerid);

    Streamer_Update(playerid);
    return 1;
}

ClearAllPlayerBlackjackData(playerid)
{
    blackjackPlayerData[playerid][BJ_CurrentTableID] =
    blackjackPlayerData[playerid][BJ_CurrentTableSlotID] =
    blackjackPlayerData[playerid][BJ_IsMapSplitted] = -1;

    for(new i; i < MAX_BLACKJACK_BUTTONS; i++)
    {
        blackjackPlayerData[playerid][BJ_Buttons][i] = PlayerText:INVALID_TEXT_DRAW;
        blackjackPlayerData[playerid][BJ_ButtonsState][i] = false;
    }

    blackjackPlayerData[playerid][BJ_SetBet][0] =
    blackjackPlayerData[playerid][BJ_SetBet][1] =
    blackjackPlayerData[playerid][BJ_PlayerPoints][0] =
    blackjackPlayerData[playerid][BJ_PlayerPoints][1] = 0;

    for(new i; i < MAX_BLACKJACK_INFO_TEXTDRAWS; i++)
        blackjackPlayerData[playerid][BJ_PlayerTextdraws][i] = PlayerText:INVALID_TEXT_DRAW;

    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        blackjackPlayerData[playerid][BJ_OtherPlayers][i] = -1;

        for(new j; j < MAX_BLACKJACK_INFO_TEXTDRAWS; j++)
            blackjackOtherPData[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;

        for(new j; j < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; j++)
            blackjackOtherPCardsData[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;
    }

    for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; i++)
    {
        blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i] = PlayerText:INVALID_TEXT_DRAW;

        for(new j; j < 2; j++)
            blackjackPlayerCardsData[playerid][j][i] = -1;
    }
}

GetFreeBlackjackTableSlotID(tableID)
{
    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    {
        if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
            return i;
    }

    return -1;
}

SetActiveBlackjackButtons(playerid, tableID)
{
    blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonExit] = true;

    switch(blackjackTableData[tableID][BJ_CurrentTableState])
    {
        case BJ_StateNone, BJ_StateWaitBets:
        {
            if(blackjackPlayerData[playerid][BJ_SetBet][0] > 0)
                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonStayOrBet] = false;
            else
            {
                PlayerTextDrawSetString(playerid, blackjackPlayerData[playerid][BJ_Buttons][0], "BET");

                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonStayOrBet] = true;
            }

            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonDouble] = false;
            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonHit] = false;
            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonSplit] = false;
        }
        case BJ_StateGame:
        {
            if(blackjackTableData[tableID][BJ_TableCurrentPlayer] != -1 && blackjackTableData[tableID][BJ_TablePlayers][blackjackTableData[tableID][BJ_TableCurrentPlayer]] == playerid)
            {
                PlayerTextDrawSetString(playerid, blackjackPlayerData[playerid][BJ_Buttons][0], "STAY");

                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonStayOrBet] = true;

                new
                    double = blackjackPlayerData[playerid][BJ_IsMapSplitted] == -1 ? (2) : (2 + (blackjackPlayerData[playerid][BJ_IsMapSplitted] * MAX_BLACKJACK_CARDS_TEXTDRAWS));

                if(blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][double] == PlayerText:INVALID_TEXT_DRAW)
                    blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonDouble] = true;
                else
                    blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonDouble] = false;

                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonHit] = true;

                if(blackjackPlayerData[playerid][BJ_IsMapSplitted] == -1 && blackjackPlayerCardsData[playerid][1][0] == blackjackPlayerCardsData[playerid][1][1])
                    blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonSplit] = true;
                else
                    blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonSplit] = false;
            }
            else
            {
                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonStayOrBet] = false;
                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonDouble] = false;
                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonHit] = false;
                blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonSplit] = false;
            }
        }
        case BJ_StateFinish:
        {
            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonStayOrBet] = false;
            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonDouble] = false;
            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonHit] = false;
            blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonSplit] = false;
        }
    }

    ShowBlackjackButtonsForPlayer(playerid);
}

ExitPlayerFromBlackjackTable(playerid, tableID)
{
    blackjackTableData[tableID][BJ_TablePlayersCount]--;

    CreateBlackjackTableInfo(tableID, false);

    if(blackjackPlayerData[playerid][BJ_SetBet][0] > 0 && (blackjackTableData[tableID][BJ_CurrentTableState] == BJ_StateNone || blackjackTableData[tableID][BJ_CurrentTableState] == BJ_StateWaitBets))
        SetPlayerMoney(playerid, blackjackPlayerData[playerid][BJ_SetBet][0], true, "возврат ставки в blackjack");
        
    if(blackjackTableData[tableID][BJ_TablePlayersCount] <= 0)
        ExitLastPlayerFromBJTable(tableID);

    new
        slotID = blackjackPlayerData[playerid][BJ_CurrentTableSlotID];

    blackjackTableData[tableID][BJ_TablePlayers][slotID] =
    blackjackPlayerData[playerid][BJ_CurrentTableID] =
    blackjackPlayerData[playerid][BJ_CurrentTableSlotID] = -1;

    if(blackjackTableData[tableID][BJ_TableCurrentPlayer] == slotID)
        blackjackTableData[tableID][BJ_TableGameCounter] = 0;

    DestroyBJButtonsForPlayer(playerid);
    HideOrDestroyBlackjackDealerTD(playerid, tableID);
    DestroyBlackjackPlayerTD(playerid);

    TogglePlayerControllable(playerid, true);
    SetCameraBehindPlayer(playerid);

    Streamer_ToggleItem(playerid, STREAMER_TYPE_3D_TEXT_LABEL, blackjackTableData[tableID][BJ_TableInfo], true);

    Streamer_Update(playerid);

    ClearPlayerDataAfterGame(playerid);
}

ExitLastPlayerFromBJTable(tableID)
{
    if(blackjackTableData[tableID][BJ_TableGameTimer] != -1)
    {
        KillTimer(blackjackTableData[tableID][BJ_TableGameTimer]);
        blackjackTableData[tableID][BJ_TableGameTimer] = -1;
    }

    ClearTableDataAfterGame(tableID);
}

AddBlackjackPlayerToPlayer(playerid, who)
{
    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if(blackjackPlayerData[playerid][BJ_OtherPlayers][i] != -1)
            continue;

        blackjackPlayerData[playerid][BJ_OtherPlayers][i] = who;

        break;
    }
}

GetMySlotIDInOtherPlayer(playerid, who)
{
    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if(blackjackPlayerData[who][BJ_OtherPlayers][i] == playerid)
            return i;
    }

    return -1;
}

GetBJNextPlayerIDForGame(tableID)
{
    new
        id = blackjackTableData[tableID][BJ_TableCurrentPlayer],
        player;

    if(id == -1)
    {
        for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
        {
            if((player = blackjackTableData[tableID][BJ_TablePlayers][i]) != -1 && blackjackPlayerData[player][BJ_SetBet][0] > 0 && blackjackPlayerData[player][BJ_PlayerPoints][0] < 21)
                return i;
        }
    }
    else
    {
        while(id != MAX_BLACKJACK_TABLE_PLAYERS)
        {
            id++;

            if(id == MAX_BLACKJACK_TABLE_PLAYERS)
                return -1;

            if((player = blackjackTableData[tableID][BJ_TablePlayers][id]) != -1 && blackjackPlayerData[player][BJ_SetBet][0] > 0 && blackjackPlayerData[player][BJ_PlayerPoints][0] < 21)
                return id;
        }
    }

    return -1;
}

AddBJCardToPlayerOrDealer(tableID, playerid, slot = 0)
{
    new
        suit,
        card,
        id;

    GenerateRandomBlackjackCard(tableID, playerid, suit, card);

    if(playerid == -1)
    {
        new amount;
        if(card <= 8) amount += card + 2;
        else if(card <= 11) amount += 10;
        else amount += 11;

        if(random(3) == 1 && (12 <= blackjackTableData[tableID][BJ_DealerPoints] <= 19) && blackjackTableData[tableID][BJ_DealerPoints]+amount>21)
        {
            //SendDebug(0, "%d+%d = 21", blackjackTableData[tableID][BJ_DealerPoints]+amount, blackjackTableData[tableID][BJ_DealerPoints], amount);
            card = 21-blackjackTableData[tableID][BJ_DealerPoints]-2;
            //SendDebug(0, "random ON: card: %d", card);
        }

        for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS; i++)
        {
            if(blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] != INVALID_TEXT_DRAW)
                continue;

            id = i;

            break;
        }

        blackjackTableData[tableID][BJ_DealerCardsTextdraws][id] = TextDrawCreate(257.0 + float(id * 8), 81.0,
            blackjackTableData[tableID][BJ_TableCurrentRound] == 2 ? ("LD_CARD:cdback") : (blackjackCardsData[card][suit + 1]));
        TextDrawBackgroundColor(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 0);
        TextDrawFont(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 4);
        TextDrawLetterSize(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 0.5, 1.0);
        TextDrawColor(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], -1);
        TextDrawSetOutline(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 0);
        TextDrawSetProportional(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 1);
        TextDrawSetShadow(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 1);
        TextDrawUseBox(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 1);
        TextDrawBoxColor(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 255);
        TextDrawTextSize(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 35.0, 60.0);
        TextDrawSetSelectable(blackjackTableData[tableID][BJ_DealerCardsTextdraws][id], 0);

        ShowAllBJDealerCardsToPlayer(playerid, tableID);

        if(blackjackTableData[tableID][BJ_TableCurrentRound] == 2)
        {
            blackjackTableData[tableID][BJ_DealerCardData][0] = suit;
            blackjackTableData[tableID][BJ_DealerCardData][1] = card;
        }
    }
    else
    {
        playerid = blackjackTableData[tableID][BJ_TablePlayers][playerid];

        for(new i = slot * MAX_BLACKJACK_CARDS_TEXTDRAWS; i < MAX_BLACKJACK_CARDS_TEXTDRAWS + (slot * MAX_BLACKJACK_CARDS_TEXTDRAWS); i++)
        {
            if(blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i] != PlayerText:INVALID_TEXT_DRAW)
                continue;

            id = i;

            break;
        }

        new
            Float:x = 257.0 + float((slot ? ((id - MAX_BLACKJACK_CARDS_TEXTDRAWS)) : (id)) * 8),
            Float:y = slot ? (321.0) : (251.0);

        blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id] = CreatePlayerTextDraw(playerid, x, y, blackjackCardsData[card][suit + 1]);
        PlayerTextDrawBackgroundColor(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 0);
        PlayerTextDrawFont(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 4);
        PlayerTextDrawLetterSize(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 0.5, 1.0);
        PlayerTextDrawColor(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], -1);
        PlayerTextDrawSetOutline(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 0);
        PlayerTextDrawSetProportional(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 1);
        PlayerTextDrawSetShadow(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 1);
        PlayerTextDrawUseBox(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 1);
        PlayerTextDrawBoxColor(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 255);
        PlayerTextDrawTextSize(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 35.0, 60.0);
        PlayerTextDrawSetSelectable(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id], 0);

        PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][id]);

        for(new i, index, player; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
        {
            if((player = blackjackPlayerData[playerid][BJ_OtherPlayers][i]) == -1)
                continue;

            index = GetMySlotIDInOtherPlayer(playerid, player);

            x = slot ? (blackjackMapData[index][BJ_MapSplitCardPosX] + float((id - MAX_BLACKJACK_CARDS_TEXTDRAWS) * 8)) : (blackjackMapData[index][BJ_MapCardPosX] + float(id * 8));
            y = slot ? (blackjackMapData[index][BJ_MapSplitCardPosY]) : (blackjackMapData[index][BJ_MapCardPosY]);

            blackjackOtherPCardsData[player][index][id] = CreatePlayerTextDraw(player, x, y, blackjackCardsData[card][suit + 1]);
            PlayerTextDrawBackgroundColor(player, blackjackOtherPCardsData[player][index][id], 0);
            PlayerTextDrawFont(player, blackjackOtherPCardsData[player][index][id], 4);
            PlayerTextDrawLetterSize(player, blackjackOtherPCardsData[player][index][id], 0.5, 1.0);
            PlayerTextDrawColor(player, blackjackOtherPCardsData[player][index][id], -1);
            PlayerTextDrawSetOutline(player, blackjackOtherPCardsData[player][index][id], 0);
            PlayerTextDrawSetProportional(player, blackjackOtherPCardsData[player][index][id], 1);
            PlayerTextDrawSetShadow(player, blackjackOtherPCardsData[player][index][id], 1);
            PlayerTextDrawUseBox(player, blackjackOtherPCardsData[player][index][id], 1);
            PlayerTextDrawBoxColor(player, blackjackOtherPCardsData[player][index][id], 255);
            PlayerTextDrawTextSize(player, blackjackOtherPCardsData[player][index][id], 35.0, 60.0);
            PlayerTextDrawSetSelectable(player, blackjackOtherPCardsData[player][index][id], 0);

            PlayerTextDrawShow(player, blackjackOtherPCardsData[player][index][id]);
        }

        blackjackPlayerCardsData[playerid][0][id] = suit;
        blackjackPlayerCardsData[playerid][1][id] = card;
    }

    SetPointsToPlayerOrBJDealer(tableID, playerid, card, slot);

    if(blackjackTableData[tableID][BJ_DealerPoints] >= 21)
    {
        ShowBJDealerCardForAll(tableID);
        HideBJGameCounterTextdrawForAll(tableID);

        blackjackTableData[tableID][BJ_TableCurrentRound] = 3;
        blackjackTableData[tableID][BJ_CurrentTableState] = BJ_StateFinish;
    }

    UpdateBJPInfoTextdrawForAll(playerid);

    ApplyDynamicActorAnimation(blackjackTableData[tableID][BJ_DealerActorID], "CASINO", "CARDS_PICK_02", 4.0, 0, 0, 0, 0, -1);
}

GenerateRandomBlackjackCard(tableID, playerid, &suit, &card)
{
blackjackRefreshCards:
    suit = random(MAX_BLACKJACK_SUITS_CARDS);
    card = random(MAX_BLACKJACK_CARDS);

    if(playerid == -1)
    {
        new amount = card + 2;
        if(11 <= amount <= 13) amount = 10;
        else if(amount > 13) amount = 11;

        if(!random(3) && (12 <= blackjackTableData[tableID][BJ_DealerPoints] <= 19) && blackjackTableData[tableID][BJ_DealerPoints] + amount > 21) card = 19 - blackjackTableData[tableID][BJ_DealerPoints];
    }

    while(blackjackTableCardsCount[tableID][suit][card] <= 0) goto blackjackRefreshCards;

    blackjackTableCardsCount[tableID][suit][card]--;
}

SplitBJPlayerCardForAll(playerid)
{
    PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2]);

    PlayerTextDrawDestroy(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][1]);

    blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][1] = PlayerText:INVALID_TEXT_DRAW;

    blackjackPlayerCardsData[playerid][0][11] = blackjackPlayerCardsData[playerid][0][1];
    blackjackPlayerCardsData[playerid][1][11] = blackjackPlayerCardsData[playerid][1][1];

    blackjackPlayerCardsData[playerid][0][1] = -1;
    blackjackPlayerCardsData[playerid][1][1] = -1;

    blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11] = CreatePlayerTextDraw(playerid, 257.0, 321.0, blackjackCardsData[blackjackPlayerCardsData[playerid][1][11]][blackjackPlayerCardsData[playerid][0][11] + 1]);
    PlayerTextDrawBackgroundColor(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 0);
    PlayerTextDrawFont(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 4);
    PlayerTextDrawLetterSize(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 0.5, 1.0);
    PlayerTextDrawColor(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], -1);
    PlayerTextDrawSetOutline(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 0);
    PlayerTextDrawSetProportional(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 1);
    PlayerTextDrawSetShadow(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 1);
    PlayerTextDrawUseBox(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 1);
    PlayerTextDrawBoxColor(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 255);
    PlayerTextDrawTextSize(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 35.0, 60.0);
    PlayerTextDrawSetSelectable(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11], 0);

    PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][11]);

    for(new i, slot, player; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if((player = blackjackPlayerData[playerid][BJ_OtherPlayers][i]) == -1)
            continue;

        slot = GetMySlotIDInOtherPlayer(playerid, player);

        PlayerTextDrawShow(player, blackjackOtherPData[player][slot][2]);

        PlayerTextDrawDestroy(player, blackjackOtherPCardsData[player][slot][1]);

        blackjackOtherPCardsData[player][slot][1] = PlayerText:INVALID_TEXT_DRAW;

        blackjackOtherPCardsData[player][slot][11] = CreatePlayerTextDraw(player, blackjackMapData[slot][BJ_MapSplitCardPosX], blackjackMapData[slot][BJ_MapSplitCardPosY],
            blackjackCardsData[blackjackPlayerCardsData[playerid][1][11]][blackjackPlayerCardsData[playerid][0][11] + 1]);
        PlayerTextDrawBackgroundColor(player, blackjackOtherPCardsData[player][slot][11], 0);
        PlayerTextDrawFont(player, blackjackOtherPCardsData[player][slot][11], 4);
        PlayerTextDrawLetterSize(player, blackjackOtherPCardsData[player][slot][11], 0.5, 1.0);
        PlayerTextDrawColor(player, blackjackOtherPCardsData[player][slot][11], -1);
        PlayerTextDrawSetOutline(player, blackjackOtherPCardsData[player][slot][11], 0);
        PlayerTextDrawSetProportional(player, blackjackOtherPCardsData[player][slot][11], 1);
        PlayerTextDrawSetShadow(player, blackjackOtherPCardsData[player][slot][11], 1);
        PlayerTextDrawUseBox(player, blackjackOtherPCardsData[player][slot][11], 1);
        PlayerTextDrawBoxColor(player, blackjackOtherPCardsData[player][slot][11], 255);
        PlayerTextDrawTextSize(player, blackjackOtherPCardsData[player][slot][11], 35.0, 60.0);
        PlayerTextDrawSetSelectable(player, blackjackOtherPCardsData[player][slot][11], 0);

        PlayerTextDrawShow(player, blackjackOtherPCardsData[player][slot][11]);
    }

    UpdateBJPInfoTextdrawForAll(playerid);
}

SetBJNextPlayerOrHand(tableID, playerid)
{
    if(blackjackPlayerData[playerid][BJ_IsMapSplitted] == 0)
    {
        blackjackPlayerData[playerid][BJ_IsMapSplitted] = 1;

        blackjackTableData[tableID][BJ_TableGameCounter] = 30;

        SendInfo(playerid, "Ваш ход перешёл ко второй руке.");
    }
    else
        blackjackTableData[tableID][BJ_TableGameCounter] = 0;
}

SetPointsToPlayerOrBJDealer(tableID, playerid, card, slot = 0)
{
    new
        amount;

    if(card <= 8)
        amount += card + 2;
    else if(card <= 11)
        amount += 10;
    else
        amount += 11;

    if(playerid == -1)
    {
        blackjackTableData[tableID][BJ_DealerPoints] += amount;

        if(blackjackTableData[tableID][BJ_DealerPoints] > 21 && card == 12)
            blackjackTableData[tableID][BJ_DealerPoints] -= 10;

        UpdateBJDealerInfoTextdraw(tableID);
    }
    else
    {
        blackjackPlayerData[playerid][BJ_PlayerPoints][slot] += amount;

        if(blackjackPlayerData[playerid][BJ_PlayerPoints][slot] > 21 && card == 12)
            blackjackPlayerData[playerid][BJ_PlayerPoints][slot] -= 10;

        if(blackjackPlayerData[playerid][BJ_PlayerPoints][slot] >= 21)
            SetBJNextPlayerOrHand(tableID, playerid);
    }
}

ClearTableDataAfterGame(tableID, bool:destroy = false)
{
    blackjackTableData[tableID][BJ_CurrentTableState] = BJ_StateNone;

    blackjackTableData[tableID][BJ_TableGameCounter] =
    blackjackTableData[tableID][BJ_TableCurrentRound] = 0;
    blackjackTableData[tableID][BJ_DealerPoints] = 0;

    blackjackTableData[tableID][BJ_TableCurrentPlayer] =
    blackjackTableData[tableID][BJ_DealerCardData][0] =
    blackjackTableData[tableID][BJ_DealerCardData][1] = -1;

    for(new i; i < MAX_BLACKJACK_SUITS_CARDS; i++)
    {
        for(new j; j < MAX_BLACKJACK_CARDS; j++)
            blackjackTableCardsCount[tableID][i][j] = 6;
    }

    if(destroy)
    {
        for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS; i++)
        {
            if(blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] == INVALID_TEXT_DRAW)
                continue;

            TextDrawDestroy(blackjackTableData[tableID][BJ_DealerCardsTextdraws][i]);

            blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] = INVALID_TEXT_DRAW;
        }
    }
}

ClearPlayerDataAfterGame(playerid, bool:destroy = false)
{
    blackjackPlayerData[playerid][BJ_SetBet][0] =
    blackjackPlayerData[playerid][BJ_SetBet][1] =
    blackjackPlayerData[playerid][BJ_PlayerPoints][0] =
    blackjackPlayerData[playerid][BJ_PlayerPoints][1] = 0;

    blackjackPlayerData[playerid][BJ_IsMapSplitted] = -1;

    for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; i++)
    {
        for(new j; j < 2; j++)
            blackjackPlayerCardsData[playerid][j][i] = -1;
    }

    if(destroy)
    {
        for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; i++)
        {
            if(blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i] == PlayerText:INVALID_TEXT_DRAW)
                continue;

            PlayerTextDrawDestroy(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i]);

            blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i] = PlayerText:INVALID_TEXT_DRAW;
        }

        PlayerTextDrawHide(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2]);

        for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
        {
            if(blackjackPlayerData[playerid][BJ_OtherPlayers][i] == -1)
                continue;

            PlayerTextDrawHide(playerid, blackjackOtherPData[playerid][i][2]);

            for(new j; j < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; j++)
            {
                if(blackjackOtherPCardsData[playerid][i][j] == PlayerText:INVALID_TEXT_DRAW)
                    continue;

                PlayerTextDrawDestroy(playerid, blackjackOtherPCardsData[playerid][i][j]);

                blackjackOtherPCardsData[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;
            }
        }

        UpdateBJPInfoTextdrawForAll(playerid);
    }
}

FullDestroyGameTable(tableID)
{
    if(tableID < 0 || tableID >= MAX_BLACKJACK_TABLES)
        return;

    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    {
        if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
            continue;

        ExitPlayerFromBlackjackTable(blackjackTableData[tableID][BJ_TablePlayers][i], tableID);
    }

    if(IsValidDynamicObject(blackjackTableData[tableID][BJ_TableObjectID]))
        DestroyDynamicObject(blackjackTableData[tableID][BJ_TableObjectID]);

    if(IsValidDynamicActor(blackjackTableData[tableID][BJ_DealerActorID]))
        DestroyDynamicActor(blackjackTableData[tableID][BJ_DealerActorID]);

    if(IsValidDynamic3DTextLabel(blackjackTableData[tableID][BJ_TableInfo]))
        DestroyDynamic3DTextLabel(blackjackTableData[tableID][BJ_TableInfo]);

    ClearAllBlackjackTableData(tableID);
}

// UI functions
CreateBlackjackButtonsForPlayer(playerid)
{
    for(new i; i < MAX_BLACKJACK_BUTTONS; i++)
    {
        blackjackPlayerData[playerid][BJ_Buttons][i] = CreatePlayerTextDraw(playerid, blackjackButtonData[i][BJ_ButtonPosX], blackjackButtonData[i][BJ_ButtonPosY], blackjackButtonData[i][BJ_ButtonName]);
        PlayerTextDrawLetterSize(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 0.304998, 1.442370);
        PlayerTextDrawTextSize(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 20.000000, 93.000000);
        PlayerTextDrawAlignment(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 2);
        PlayerTextDrawColor(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], -1);
        PlayerTextDrawUseBox(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 1);
        PlayerTextDrawBoxColor(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 96);
        PlayerTextDrawSetShadow(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 0);
        PlayerTextDrawBackgroundColor(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 32);
        PlayerTextDrawFont(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 2);
        PlayerTextDrawSetProportional(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 1);
        PlayerTextDrawSetOutline(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], 0);
        PlayerTextDrawSetSelectable(playerid, blackjackPlayerData[playerid][BJ_Buttons][i], true);
    }
}

ShowBlackjackButtonsForPlayer(playerid)
{
    for(new i; i < MAX_BLACKJACK_BUTTONS; i++)
    {
        if(blackjackPlayerData[playerid][BJ_ButtonsState][i])
            PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_Buttons][i]);
        else
            PlayerTextDrawHide(playerid, blackjackPlayerData[playerid][BJ_Buttons][i]);
    }

    SelectTextDraw(playerid, 0xFF4500FF);
}

DestroyBJButtonsForPlayer(playerid)
{
    for(new i; i < MAX_BLACKJACK_BUTTONS; i++)
    {
        PlayerTextDrawDestroy(playerid, blackjackPlayerData[playerid][BJ_Buttons][i]);

        blackjackPlayerData[playerid][BJ_Buttons][i] = PlayerText:INVALID_TEXT_DRAW;
        blackjackPlayerData[playerid][BJ_ButtonsState][i] = false;
    }
}

CreateAndShowBlackjackDealerTD(playerid, tableID)
{
    if(blackjackTableData[tableID][BJ_DealerTextdraws][0] == INVALID_TEXT_DRAW)
    {
        blackjackTableData[tableID][BJ_DealerTextdraws][0] = TextDrawCreate(320.0, 80.0, "_");
        TextDrawAlignment(blackjackTableData[tableID][BJ_DealerTextdraws][0], 2);
        TextDrawBackgroundColor(blackjackTableData[tableID][BJ_DealerTextdraws][0], 255);
        TextDrawFont(blackjackTableData[tableID][BJ_DealerTextdraws][0], 1);
        TextDrawLetterSize(blackjackTableData[tableID][BJ_DealerTextdraws][0], 0.5, 7.0);
        TextDrawColor(blackjackTableData[tableID][BJ_DealerTextdraws][0], -1);
        TextDrawSetOutline(blackjackTableData[tableID][BJ_DealerTextdraws][0], 0);
        TextDrawSetProportional(blackjackTableData[tableID][BJ_DealerTextdraws][0], 1);
        TextDrawSetShadow(blackjackTableData[tableID][BJ_DealerTextdraws][0], 1);
        TextDrawUseBox(blackjackTableData[tableID][BJ_DealerTextdraws][0], 1);
        TextDrawBoxColor(blackjackTableData[tableID][BJ_DealerTextdraws][0], 96);
        TextDrawTextSize(blackjackTableData[tableID][BJ_DealerTextdraws][0], 0.0, 130.0);
        TextDrawSetSelectable(blackjackTableData[tableID][BJ_DealerTextdraws][0], 0);
    }

    if(blackjackTableData[tableID][BJ_DealerTextdraws][1] == INVALID_TEXT_DRAW)
    {
        blackjackTableData[tableID][BJ_DealerTextdraws][1] = TextDrawCreate(320.0, 48.0, "DEALER");
        TextDrawAlignment(blackjackTableData[tableID][BJ_DealerTextdraws][1], 2);
        TextDrawBackgroundColor(blackjackTableData[tableID][BJ_DealerTextdraws][1], 32);
        TextDrawFont(blackjackTableData[tableID][BJ_DealerTextdraws][1], 2);
        TextDrawLetterSize(blackjackTableData[tableID][BJ_DealerTextdraws][1], 0.2, 1.0);
        TextDrawColor(blackjackTableData[tableID][BJ_DealerTextdraws][1], -1);
        TextDrawSetOutline(blackjackTableData[tableID][BJ_DealerTextdraws][1], 1);
        TextDrawSetProportional(blackjackTableData[tableID][BJ_DealerTextdraws][1], 1);
        TextDrawSetSelectable(blackjackTableData[tableID][BJ_DealerTextdraws][1], 0);
    }

    if(blackjackTableData[tableID][BJ_DealerTextdraws][2] == INVALID_TEXT_DRAW)
    {
        blackjackTableData[tableID][BJ_DealerTextdraws][2] = TextDrawCreate(320.0, 165.0, "");
        TextDrawAlignment(blackjackTableData[tableID][BJ_DealerTextdraws][2], 2);
        TextDrawBackgroundColor(blackjackTableData[tableID][BJ_DealerTextdraws][2], 32);
        TextDrawFont(blackjackTableData[tableID][BJ_DealerTextdraws][2], 2);
        TextDrawLetterSize(blackjackTableData[tableID][BJ_DealerTextdraws][2], 0.2, 1.0);
        TextDrawColor(blackjackTableData[tableID][BJ_DealerTextdraws][2], -1);
        TextDrawSetOutline(blackjackTableData[tableID][BJ_DealerTextdraws][2], 1);
        TextDrawSetProportional(blackjackTableData[tableID][BJ_DealerTextdraws][2], 1);
        TextDrawSetSelectable(blackjackTableData[tableID][BJ_DealerTextdraws][2], 0);
    }

    TextDrawShowForPlayer(playerid, blackjackTableData[tableID][BJ_DealerTextdraws][0]);
    TextDrawShowForPlayer(playerid, blackjackTableData[tableID][BJ_DealerTextdraws][1]);

    ShowAllBJDealerCardsToPlayer(playerid, tableID);
}

HideOrDestroyBlackjackDealerTD(playerid, tableID)
{
    if(blackjackTableData[tableID][BJ_TablePlayersCount] <= 0)
    {
        for(new i; i < MAX_BLACKJACK_INFO_TEXTDRAWS; i++)
        {
            TextDrawDestroy(blackjackTableData[tableID][BJ_DealerTextdraws][i]);

            blackjackTableData[tableID][BJ_DealerTextdraws][i] = INVALID_TEXT_DRAW;
        }

        for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS; i++)
        {
            if(blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] == INVALID_TEXT_DRAW)
                continue;

            TextDrawDestroy(blackjackTableData[tableID][BJ_DealerCardsTextdraws][i]);

            blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] = INVALID_TEXT_DRAW;
        }
    }
    else
    {
        for(new i; i < MAX_BLACKJACK_INFO_TEXTDRAWS; i++)
            TextDrawHideForPlayer(playerid, blackjackTableData[tableID][BJ_DealerTextdraws][i]);

        for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS; i++)
            TextDrawHideForPlayer(playerid, blackjackTableData[tableID][BJ_DealerCardsTextdraws][i]);
    }
}

CreateAndShowBlackjackPlayerTD(playerid)
{
    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL, "~y~%s (%d)~n~~w~BET: $%d", get_name(playerid), playerid, blackjackPlayerData[playerid][BJ_SetBet][0]);

    blackjackPlayerData[playerid][BJ_PlayerTextdraws][0] = CreatePlayerTextDraw(playerid, 320.0, 218.0, STRING_GLOBAL);
    PlayerTextDrawAlignment(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 2);
    PlayerTextDrawBackgroundColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 32);
    PlayerTextDrawFont(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 2);
    PlayerTextDrawLetterSize(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 0.2, 1.0);
    PlayerTextDrawColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], -1);
    PlayerTextDrawSetOutline(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 1);
    PlayerTextDrawSetProportional(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 1);
    PlayerTextDrawSetSelectable(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], 0);

    blackjackPlayerData[playerid][BJ_PlayerTextdraws][1] = CreatePlayerTextDraw(playerid, 320.0, 250.0, "_");
    PlayerTextDrawAlignment(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 2);
    PlayerTextDrawBackgroundColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 255);
    PlayerTextDrawFont(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 1);
    PlayerTextDrawLetterSize(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 0.5, 7.0);
    PlayerTextDrawColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], -1);
    PlayerTextDrawSetOutline(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 0);
    PlayerTextDrawSetProportional(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 1);
    PlayerTextDrawSetShadow(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 1);
    PlayerTextDrawUseBox(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 1);
    PlayerTextDrawBoxColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 96);
    PlayerTextDrawTextSize(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 0.0, 130.0);
    PlayerTextDrawSetSelectable(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1], 0);

    blackjackPlayerData[playerid][BJ_PlayerTextdraws][2] = CreatePlayerTextDraw(playerid, 320.0, 320.0, "_");
    PlayerTextDrawAlignment(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 2);
    PlayerTextDrawBackgroundColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 255);
    PlayerTextDrawFont(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 1);
    PlayerTextDrawLetterSize(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 0.5, 7.0);
    PlayerTextDrawColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], -1);
    PlayerTextDrawSetOutline(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 0);
    PlayerTextDrawSetProportional(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 1);
    PlayerTextDrawSetShadow(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 1);
    PlayerTextDrawUseBox(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 1);
    PlayerTextDrawBoxColor(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 96);
    PlayerTextDrawTextSize(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 0.0, 130.0);
    PlayerTextDrawSetSelectable(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][2], 0);

    PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0]);
    PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][1]);

    CreateAndShowBJPTDToOtherPlayer(playerid, STRING_GLOBAL);

    for(new i, player; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if((player = blackjackPlayerData[playerid][BJ_OtherPlayers][i]) == -1)
            continue;

        if(blackjackPlayerData[player][BJ_PlayerPoints][0] <= 0)
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~y~%s (%d)~n~~w~BET: $%d", get_name(player), player, blackjackPlayerData[player][BJ_SetBet][0]);
        else
        {
            if(blackjackPlayerData[player][BJ_PlayerPoints][1] <= 0)
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~y~%s (%d)~n~~w~BET: $%d~n~~y~%d", get_name(player), player, blackjackPlayerData[player][BJ_SetBet][0], blackjackPlayerData[player][BJ_PlayerPoints][0]);
            else
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~y~%s (%d)~n~~w~BET: $%d / %d~n~~y~%d / %d", get_name(player), player,
                    blackjackPlayerData[player][BJ_SetBet][0], blackjackPlayerData[player][BJ_SetBet][1], blackjackPlayerData[player][BJ_PlayerPoints][0], blackjackPlayerData[player][BJ_PlayerPoints][1]);
        }

        blackjackOtherPData[playerid][i][0] = CreatePlayerTextDraw(playerid, blackjackMapData[i][BJ_MapInfoPosX], blackjackMapData[i][BJ_MapInfoPosY], STRING_GLOBAL);
        PlayerTextDrawAlignment(playerid, blackjackOtherPData[playerid][i][0], 2);
        PlayerTextDrawBackgroundColor(playerid, blackjackOtherPData[playerid][i][0], 32);
        PlayerTextDrawFont(playerid, blackjackOtherPData[playerid][i][0], 2);
        PlayerTextDrawLetterSize(playerid, blackjackOtherPData[playerid][i][0], 0.2, 1.0);
        PlayerTextDrawColor(playerid, blackjackOtherPData[playerid][i][0], -1);
        PlayerTextDrawSetOutline(playerid, blackjackOtherPData[playerid][i][0], 1);
        PlayerTextDrawSetProportional(playerid, blackjackOtherPData[playerid][i][0], 1);
        PlayerTextDrawSetSelectable(playerid, blackjackOtherPData[playerid][i][0], 0);

        blackjackOtherPData[playerid][i][1] = CreatePlayerTextDraw(playerid, blackjackMapData[i][BJ_MapPosX], blackjackMapData[i][BJ_MapPosY], "_");
        PlayerTextDrawAlignment(playerid, blackjackOtherPData[playerid][i][1], 2);
        PlayerTextDrawBackgroundColor(playerid, blackjackOtherPData[playerid][i][1], 255);
        PlayerTextDrawFont(playerid, blackjackOtherPData[playerid][i][1], 1);
        PlayerTextDrawLetterSize(playerid, blackjackOtherPData[playerid][i][1], 0.5, 7.0);
        PlayerTextDrawColor(playerid, blackjackOtherPData[playerid][i][1], -1);
        PlayerTextDrawSetOutline(playerid, blackjackOtherPData[playerid][i][1], 0);
        PlayerTextDrawSetProportional(playerid, blackjackOtherPData[playerid][i][1], 1);
        PlayerTextDrawSetShadow(playerid, blackjackOtherPData[playerid][i][1], 1);
        PlayerTextDrawUseBox(playerid, blackjackOtherPData[playerid][i][1], 1);
        PlayerTextDrawBoxColor(playerid, blackjackOtherPData[playerid][i][1], 96);
        PlayerTextDrawTextSize(playerid, blackjackOtherPData[playerid][i][1], 0.0, 130.0);
        PlayerTextDrawSetSelectable(playerid, blackjackOtherPData[playerid][i][1], 0);

        blackjackOtherPData[playerid][i][2] = CreatePlayerTextDraw(playerid, blackjackMapData[i][BJ_MapSplitPosX], blackjackMapData[i][BJ_MapSplitPosY], "_");
        PlayerTextDrawAlignment(playerid, blackjackOtherPData[playerid][i][2], 2);
        PlayerTextDrawBackgroundColor(playerid, blackjackOtherPData[playerid][i][2], 255);
        PlayerTextDrawFont(playerid, blackjackOtherPData[playerid][i][2], 1);
        PlayerTextDrawLetterSize(playerid, blackjackOtherPData[playerid][i][2], 0.5, 7.0);
        PlayerTextDrawColor(playerid, blackjackOtherPData[playerid][i][2], -1);
        PlayerTextDrawSetOutline(playerid, blackjackOtherPData[playerid][i][2], 0);
        PlayerTextDrawSetProportional(playerid, blackjackOtherPData[playerid][i][2], 1);
        PlayerTextDrawSetShadow(playerid, blackjackOtherPData[playerid][i][2], 1);
        PlayerTextDrawUseBox(playerid, blackjackOtherPData[playerid][i][2], 1);
        PlayerTextDrawBoxColor(playerid, blackjackOtherPData[playerid][i][2], 96);
        PlayerTextDrawTextSize(playerid, blackjackOtherPData[playerid][i][2], 0.0, 130.0);
        PlayerTextDrawSetSelectable(playerid, blackjackOtherPData[playerid][i][2], 0);

        PlayerTextDrawShow(playerid, blackjackOtherPData[playerid][i][0]);
        PlayerTextDrawShow(playerid, blackjackOtherPData[playerid][i][1]);

        if(blackjackPlayerData[player][BJ_IsMapSplitted] != -1)
            PlayerTextDrawShow(playerid, blackjackOtherPData[playerid][i][2]);

        for(new j, card, suit, Float:x, Float:y; j < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; j++)
        {
            if(blackjackPlayerData[player][BJ_PlayerCardsTextdraws][j] == PlayerText:INVALID_TEXT_DRAW)
                continue;

            suit = blackjackPlayerCardsData[player][0][j];
            card = blackjackPlayerCardsData[player][1][j];

            x = j >= 11 ? (blackjackMapData[i][BJ_MapSplitCardPosX] + float((j - MAX_BLACKJACK_CARDS_TEXTDRAWS) * 8)) : (blackjackMapData[i][BJ_MapCardPosX] + float(j * 8));
            y = j >= 11 ? (blackjackMapData[i][BJ_MapSplitCardPosY]) : (blackjackMapData[i][BJ_MapCardPosY]);

            blackjackOtherPCardsData[playerid][i][j] = CreatePlayerTextDraw(playerid, x, y, blackjackCardsData[card][suit + 1]);
            PlayerTextDrawBackgroundColor(playerid, blackjackOtherPCardsData[playerid][i][j], 0);
            PlayerTextDrawFont(playerid, blackjackOtherPCardsData[playerid][i][j], 4);
            PlayerTextDrawLetterSize(playerid, blackjackOtherPCardsData[playerid][i][j], 0.5, 1.0);
            PlayerTextDrawColor(playerid, blackjackOtherPCardsData[playerid][i][j], -1);
            PlayerTextDrawSetOutline(playerid, blackjackOtherPCardsData[playerid][i][j], 0);
            PlayerTextDrawSetProportional(playerid, blackjackOtherPCardsData[playerid][i][j], 1);
            PlayerTextDrawSetShadow(playerid, blackjackOtherPCardsData[playerid][i][j], 1);
            PlayerTextDrawUseBox(playerid, blackjackOtherPCardsData[playerid][i][j], 1);
            PlayerTextDrawBoxColor(playerid, blackjackOtherPCardsData[playerid][i][j], 255);
            PlayerTextDrawTextSize(playerid, blackjackOtherPCardsData[playerid][i][j], 35.0, 60.0);
            PlayerTextDrawSetSelectable(playerid, blackjackOtherPCardsData[playerid][i][j], 0);

            PlayerTextDrawShow(playerid, blackjackOtherPCardsData[playerid][i][j]);
        }
    }
}

DestroyBlackjackPlayerTD(playerid)
{
    for(new i; i < MAX_BLACKJACK_INFO_TEXTDRAWS; i++)
    {
        PlayerTextDrawDestroy(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][i]);

        blackjackPlayerData[playerid][BJ_PlayerTextdraws][i] = PlayerText:INVALID_TEXT_DRAW;
    }

    for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; i++)
    {
        if(blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i] == PlayerText:INVALID_TEXT_DRAW)
            continue;

        PlayerTextDrawDestroy(playerid, blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i]);

        blackjackPlayerData[playerid][BJ_PlayerCardsTextdraws][i] = PlayerText:INVALID_TEXT_DRAW;
    }

    DestroyBJPTDForOtherPlayer(playerid);

    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if(blackjackPlayerData[playerid][BJ_OtherPlayers][i] == -1)
            continue;

        for(new j; j < MAX_BLACKJACK_INFO_TEXTDRAWS; j++)
        {
            PlayerTextDrawDestroy(playerid, blackjackOtherPData[playerid][i][j]);

            blackjackOtherPData[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;
        }

        for(new j; j < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; j++)
        {
            if(blackjackOtherPCardsData[playerid][i][j] == PlayerText:INVALID_TEXT_DRAW)
                continue;

            PlayerTextDrawDestroy(playerid, blackjackOtherPCardsData[playerid][i][j]);

            blackjackOtherPCardsData[playerid][i][j] = PlayerText:INVALID_TEXT_DRAW;
        }

        blackjackPlayerData[playerid][BJ_OtherPlayers][i] = -1;
    }

    CancelSelectTextDraw(playerid);
}

CreateAndShowBJPTDToOtherPlayer(playerid, info[])
{
    for(new i, id, player; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if((player = blackjackPlayerData[playerid][BJ_OtherPlayers][i]) == -1)
            continue;

        id = GetMySlotIDInOtherPlayer(playerid, player);

        blackjackOtherPData[player][id][0] = CreatePlayerTextDraw(player, blackjackMapData[id][BJ_MapInfoPosX], blackjackMapData[id][BJ_MapInfoPosY], info);
        PlayerTextDrawAlignment(player, blackjackOtherPData[player][id][0], 2);
        PlayerTextDrawBackgroundColor(player, blackjackOtherPData[player][id][0], 32);
        PlayerTextDrawFont(player, blackjackOtherPData[player][id][0], 2);
        PlayerTextDrawLetterSize(player, blackjackOtherPData[player][id][0], 0.2, 1.0);
        PlayerTextDrawColor(player, blackjackOtherPData[player][id][0], -1);
        PlayerTextDrawSetOutline(player, blackjackOtherPData[player][id][0], 1);
        PlayerTextDrawSetProportional(player, blackjackOtherPData[player][id][0], 1);
        PlayerTextDrawSetSelectable(player, blackjackOtherPData[player][id][0], 0);

        blackjackOtherPData[player][id][1] = CreatePlayerTextDraw(player, blackjackMapData[id][BJ_MapPosX], blackjackMapData[id][BJ_MapPosY], "_");
        PlayerTextDrawAlignment(player, blackjackOtherPData[player][id][1], 2);
        PlayerTextDrawBackgroundColor(player, blackjackOtherPData[player][id][1], 255);
        PlayerTextDrawFont(player, blackjackOtherPData[player][id][1], 1);
        PlayerTextDrawLetterSize(player, blackjackOtherPData[player][id][1], 0.5, 7.0);
        PlayerTextDrawColor(player, blackjackOtherPData[player][id][1], -1);
        PlayerTextDrawSetOutline(player, blackjackOtherPData[player][id][1], 0);
        PlayerTextDrawSetProportional(player, blackjackOtherPData[player][id][1], 1);
        PlayerTextDrawSetShadow(player, blackjackOtherPData[player][id][1], 1);
        PlayerTextDrawUseBox(player, blackjackOtherPData[player][id][1], 1);
        PlayerTextDrawBoxColor(player, blackjackOtherPData[player][id][1], 96);
        PlayerTextDrawTextSize(player, blackjackOtherPData[player][id][1], 0.0, 130.0);
        PlayerTextDrawSetSelectable(player, blackjackOtherPData[player][id][1], 0);

        blackjackOtherPData[player][id][2] = CreatePlayerTextDraw(player, blackjackMapData[id][BJ_MapSplitPosX], blackjackMapData[id][BJ_MapSplitPosY], "_");
        PlayerTextDrawAlignment(player, blackjackOtherPData[player][id][2], 2);
        PlayerTextDrawBackgroundColor(player, blackjackOtherPData[player][id][2], 255);
        PlayerTextDrawFont(player, blackjackOtherPData[player][id][2], 1);
        PlayerTextDrawLetterSize(player, blackjackOtherPData[player][id][2], 0.5, 7.0);
        PlayerTextDrawColor(player, blackjackOtherPData[player][id][2], -1);
        PlayerTextDrawSetOutline(player, blackjackOtherPData[player][id][2], 0);
        PlayerTextDrawSetProportional(player, blackjackOtherPData[player][id][2], 1);
        PlayerTextDrawSetShadow(player, blackjackOtherPData[player][id][2], 1);
        PlayerTextDrawUseBox(player, blackjackOtherPData[player][id][2], 1);
        PlayerTextDrawBoxColor(player, blackjackOtherPData[player][id][2], 96);
        PlayerTextDrawTextSize(player, blackjackOtherPData[player][id][2], 0.0, 130.0);
        PlayerTextDrawSetSelectable(player, blackjackOtherPData[player][id][2], 0);

        PlayerTextDrawShow(player, blackjackOtherPData[player][id][0]);
        PlayerTextDrawShow(player, blackjackOtherPData[player][id][1]);
    }
}

DestroyBJPTDForOtherPlayer(playerid)
{
    for(new i, id, player; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if((player = blackjackPlayerData[playerid][BJ_OtherPlayers][i]) == -1)
            continue;

        id = GetMySlotIDInOtherPlayer(playerid, player);

        for(new j; j < MAX_BLACKJACK_INFO_TEXTDRAWS; j++)
        {
            PlayerTextDrawDestroy(player, blackjackOtherPData[player][id][j]);

            blackjackOtherPData[player][id][j] = PlayerText:INVALID_TEXT_DRAW;
        }

        for(new j; j < MAX_BLACKJACK_CARDS_TEXTDRAWS * 2; j++)
        {
            if(blackjackOtherPCardsData[player][id][j] == PlayerText:INVALID_TEXT_DRAW)
                continue;

            PlayerTextDrawDestroy(player, blackjackOtherPCardsData[player][id][j]);

            blackjackOtherPCardsData[player][id][j] = PlayerText:INVALID_TEXT_DRAW;
        }

        blackjackPlayerData[player][BJ_OtherPlayers][id] = -1;
    }
}

UpdateBJPInfoTextdrawForAll(playerid)
{
    if(playerid == -1)
        return;

    if(blackjackPlayerData[playerid][BJ_PlayerPoints][0] <= 0)
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~y~%s (%d)~n~~w~BET: $%d", get_name(playerid), playerid, blackjackPlayerData[playerid][BJ_SetBet][0]);
    else
    {
        if(blackjackPlayerData[playerid][BJ_PlayerPoints][1] <= 0)
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~y~%s (%d)~n~~w~BET: $%d~n~y~%d", get_name(playerid), playerid, blackjackPlayerData[playerid][BJ_SetBet][0], blackjackPlayerData[playerid][BJ_PlayerPoints][0]);
        else
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~y~%s (%d)~n~~w~BET: $%d / %d~n~y~%d / %d", get_name(playerid), playerid,
                blackjackPlayerData[playerid][BJ_SetBet][0], blackjackPlayerData[playerid][BJ_SetBet][1], blackjackPlayerData[playerid][BJ_PlayerPoints][0], blackjackPlayerData[playerid][BJ_PlayerPoints][1]);
    }

    PlayerTextDrawSetString(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0], STRING_GLOBAL);

    // PlayerTextDrawHide(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0]);
    // PlayerTextDrawShow(playerid, blackjackPlayerData[playerid][BJ_PlayerTextdraws][0]);

    for(new i, id, player; i < MAX_BLACKJACK_TABLE_PLAYERS - 1; i++)
    {
        if((player = blackjackPlayerData[playerid][BJ_OtherPlayers][i]) == -1)
            continue;

        id = GetMySlotIDInOtherPlayer(playerid, player);

        PlayerTextDrawSetString(player, blackjackOtherPData[player][id][0], STRING_GLOBAL);

        // PlayerTextDrawHide(player, blackjackOtherPData[player][id][0]);
        // PlayerTextDrawShow(player, blackjackOtherPData[player][id][0]);
    }
}

UpdateBJGameCounterTextdraw(tableID, info[])
{
    TextDrawSetString(blackjackTableData[tableID][BJ_DealerTextdraws][2], info);

    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    {
        if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
            continue;
        TextDrawShowForPlayer(blackjackTableData[tableID][BJ_TablePlayers][i], blackjackTableData[tableID][BJ_DealerTextdraws][2]);
    }
}

HideBJGameCounterTextdrawForAll(tableID)
{
    for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    {
        if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
            continue;

        TextDrawHideForPlayer(blackjackTableData[tableID][BJ_TablePlayers][i], blackjackTableData[tableID][BJ_DealerTextdraws][2]);
    }
}

ShowAllBJDealerCardsToPlayer(playerid, tableID)
{
    if(playerid == -1)
    {
        for(new i, player; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
        {
            if((player = blackjackTableData[tableID][BJ_TablePlayers][i]) == -1)
                continue;

            for(new j; j < MAX_BLACKJACK_CARDS_TEXTDRAWS; j++)
            {
                if(blackjackTableData[tableID][BJ_DealerCardsTextdraws][j] == INVALID_TEXT_DRAW)
                    break;

                TextDrawShowForPlayer(player, blackjackTableData[tableID][BJ_DealerCardsTextdraws][j]);
            }
        }
    }
    else
    {
        for(new i; i < MAX_BLACKJACK_CARDS_TEXTDRAWS; i++)
        {
            if(blackjackTableData[tableID][BJ_DealerCardsTextdraws][i] == INVALID_TEXT_DRAW)
                break;

            TextDrawShowForPlayer(playerid, blackjackTableData[tableID][BJ_DealerCardsTextdraws][i]);
        }
    }
}

ShowBJDealerCardForAll(tableID)
{
    TextDrawSetString(blackjackTableData[tableID][BJ_DealerCardsTextdraws][1],
        blackjackCardsData[blackjackTableData[tableID][BJ_DealerCardData][1]][blackjackTableData[tableID][BJ_DealerCardData][0] + 1]);

    // for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    // {
    //     if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
    //         continue;

    //     TextDrawHideForPlayer(blackjackTableData[tableID][BJ_TablePlayers][i], blackjackTableData[tableID][BJ_DealerCardsTextdraws][1]);
    //     TextDrawShowForPlayer(blackjackTableData[tableID][BJ_TablePlayers][i], blackjackTableData[tableID][BJ_DealerCardsTextdraws][1]);
    // }
}

UpdateBJDealerInfoTextdraw(tableID)
{
    if(blackjackTableData[tableID][BJ_TableCurrentRound] != 2 && blackjackTableData[tableID][BJ_DealerPoints] > 0)
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DEALER~n~~y~%d", blackjackTableData[tableID][BJ_DealerPoints]);
    else
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "DEALER");

    TextDrawSetString(blackjackTableData[tableID][BJ_DealerTextdraws][1], STRING_GLOBAL);

    // for(new i; i < MAX_BLACKJACK_TABLE_PLAYERS; i++)
    // {
    //     if(blackjackTableData[tableID][BJ_TablePlayers][i] == -1)
    //         continue;

    //     TextDrawHideForPlayer(blackjackTableData[tableID][BJ_TablePlayers][i], blackjackTableData[tableID][BJ_DealerTextdraws][1]);
    //     TextDrawShowForPlayer(blackjackTableData[tableID][BJ_TablePlayers][i], blackjackTableData[tableID][BJ_DealerTextdraws][1]);
    // }
}


CMD:bj_create(playerid, params[])
{
    if(SRV_ID)
        return 1;

    sscanf(params, "D(0)", params[0]);

    if(params[0] < 0 || params[0] > 2)
        return 1;

    //CreateBlackjackTable(playerid, .type = params[0]);
    return 1;
}

CMD:bj_delete(playerid)
{
    if(SRV_ID)
        return 1;

    new tableID = GetNearestPlayerBlackjackTable(playerid);
    if(tableID == -1)
        return 1;
	FullDestroyGameTable(tableID);
    return 1;
}


/*DialogCreate:BLACKJACK_SET_BET(playerid)
{
    ShowPlayerDialog(playerid, D_BLACKJACK_SET_BET, DIALOG_STYLE_INPUT, "Ставка", ""W"Введите сумму которую желаете поставить:", "Поставить", "Закрыть");

}

DialogResponse:D_BLACKJACK_SET_BET(playerid, response, listitem, inputtext[])
{
    new tableID = blackjackPlayerData[playerid][BJ_CurrentTableID];
    if(!response || tableID == -1 || (blackjackTableData[tableID][BJ_CurrentTableState] != BJ_StateNone && blackjackTableData[tableID][BJ_CurrentTableState] != BJ_StateWaitBets))
        return 1;


    if(isnull(inputtext))
        return Dialog_Show(playerid, Dialog:BLACKJACK_SET_BET);

    new
        bj_bet = strval(inputtext);

    if(!(10000 <= bj_bet <= 2000000))
    {
        Dialog_Show(playerid, Dialog:BLACKJACK_SET_BET);
        return SendError(playerid, "Сумма ставки должна быть от "I"$10000 "W"до "I"$2000000"W".");
    }

    if(bj_bet > p_info[playerid][cash])
    {
        Dialog_Show(playerid, Dialog:BLACKJACK_SET_BET);
        return SendError(playerid, "Недостаточно денег чтобы сделать ставку.");
    }

    blackjackPlayerData[playerid][BJ_SetBet][0] = bj_bet;
    SetPlayerMoney(playerid, -blackjackPlayerData[playerid][BJ_SetBet][0], true, "ставка в blackjack");

    SendAccess(playerid, "Вы поставили $%d. Ожидайте начала игры.", bj_bet);

    UpdateBJPInfoTextdrawForAll(playerid);
    blackjackPlayerData[playerid][BJ_ButtonsState][BJ_ButtonStayOrBet] = false;
    ShowBlackjackButtonsForPlayer(playerid);
    return 1;
} 

DialogCreate:BLACKJACK_HELP_INFO(playerid)
{
    Dialog_Open(playerid, Dialog:GBF_NULL, DIALOG_STYLE_MSGBOX, ""I"Игра BlackJack", "\
        "I"BlackJack (БлэкДжек) "W"- это карточная игра, в которую могут играть одновременно до 3х человек и дилер.\n\
        Цель игры - набрать сумму очков карт, не превышающую 21, а также победить дилера.\n\
        Карты от двойки до десятки стоят столько очков, сколько на них написано.\n\
        Карты с лицами (валет, дама, король) приносят по 10 очков, а туз 11 очков.\n\
        \n\
        Игра начинается с того, что каждый игрок делает свою ставку, после чего дилер раздает две карты каждому игроку,\n\
        включая себя. Одна из карт дилера остается скрытой. Затем игроки по очереди принимают решение о том,\n\
        нужно ли им брать дополнительные карты (тянуть) или остановиться. Если сумма очков карт игрока превышает 21,\n\
        он проигрывает и дилер забирает его ставку.\n\
        \n\
        После того как все игроки сделали свой выбор, дилер открывает свою скрытую карту и продолжает игру.\n\
        Дилер обязан брать дополнительные карты, пока его сумма очков не достигнет 17 или более.\n\
        Если у дилера сумма очков больше 21, все оставшиеся игроки выигрывают.\n\
        \n\
        Выигрыш игрока равен его ставке в случае, если его сумма очков больше, чем у дилера, или если дилер перебрал.\n\
        Если суммы очков равны, ставка возвращается игроку. Если у дилера больше очков, чем у игрока,\n\
        игрок проигрывает ставку.\n\
        \n\
        Игра заканчивается, когда все игроки сыграют все свои партии, или когда дилер закончит свою.", "Далее", "Отмена");
}

CMD:bjhelp(playerid)
{
    Dialog_Show(playerid, Dialog:BLACKJACK_HELP_INFO);
    return 1;
} */
