#include "logic/casino/durak/durak_const.inc"

enum E_DURAK_TABLE
{
    dtLobbyState,

    dtPlayerCount,
    dtPlayerId[MAX_DURAK_PLAYERS],
    dtPlayerNumber[MAX_DURAK_PLAYERS],

    dtBet,
    dtMode,
    dtReadyCount,
    dtUntilGame,

    dtPrize,

    dtDeck[DURAK_DECK_SIZE],
    dtDeckIndex,

    dtTurnIndex,
    dtDefenderIndex,
    dtWinnerIndex,

    dtAct,
    dtEndType,
    dtBeatenCount,
    dtAllowTakeCount,
    dtBoardCount[2],
    dtUntilNextRound,
    dtUntilForcedEnd
};

new gDurakTable[MAX_DURAK_TABLES + 1][E_DURAK_TABLE];
new gDurakBoard[MAX_DURAK_TABLES + 1][DURAK_BOARD_SIZE][2];

#include "logic/casino/durak/durak_td/durak_td.inc"
#include "logic/casino/durak/durak_td/durak_td_btn.inc"
#include "logic/casino/durak/durak_td/durak_td_status.inc"
#include "logic/casino/durak/durak_td/durak_td_card.inc"
#include "logic/casino/durak/durak_td/durak_td_board.inc"
#include "logic/casino/durak/durak_td/durak_td_trump.inc"
#include "logic/casino/durak/durak_td/durak_td_deck.inc"

Durak_CleanTable(const table)
{
    gDurakTable[table][dtLobbyState] = DurakLobby_NotReady;
    gDurakTable[table][dtPlayerCount] = 0;

    gDurakTable[table][dtPrize] = 0;

    for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
    {
        gDurakTable[table][dtPlayerId][i] = INVALID_PLAYER_ID;
        gDurakTable[table][dtPlayerNumber][i] = -1;
    }

    gDurakTable[table][dtMode] = DurakMode_Simple;
    gDurakTable[table][dtBet] = 0;
    gDurakTable[table][dtReadyCount] = 0;
    gDurakTable[table][dtUntilGame] = 0;
}

Durak_JoinTable(const playerid, const table)
{
    if(p_info[playerid][durak_table])
        return;

    if(gDurakTable[table][dtPlayerCount] == MAX_DURAK_PLAYERS)
    {
        SendError(playerid, "За столом нет свободных мест.");
        return;
    }

    if(gDurakTable[table][dtLobbyState] == DurakLobby_InGame)
    {
        SendError(playerid, "За столом уже началась игра.");
        return;
    }

    gDurakTable[table][dtPlayerCount]++;
    p_info[playerid][durak_table] = table;

    p_info[playerid][durak_ready] = false;

    for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
    {
        if(gDurakTable[table][dtPlayerId][i] == INVALID_PLAYER_ID)
        {
            gDurakTable[table][dtPlayerId][i] = playerid;
            p_info[playerid][durak_index] = i;
            break;
        }
    }

    Durak_Enumerate(table);

    SelectTextDraw(playerid, DURAK_BTN_HOVER_COLOR);
    TextDrawShowForPlayer(playerid, TD_DurakTable);
    Durak_CreatePTD(playerid, table, p_info[playerid][durak_index]);

    Durak_ShowButton(playerid, DurakBtn_Leave,
        "Leave",
        .bodyColor = 0xe74c3cff);

    Durak_UpdateLobbyBtn(playerid);

    Durak_UpdateStatus(table);
}

Durak_LeaveTable(const playerid)
{
    if(!p_info[playerid][durak_table])
    {
        return;
    }

    new table = p_info[playerid][durak_table];

    switch(gDurakTable[table][dtLobbyState])
    {
    case DurakLobby_InGame:
    {
        Durak_OnPlayerLeaveGame(playerid);
    }
    default:
    {
        if(p_info[playerid][durak_ready])
        {
            Durak_ReturnBet(playerid);

            gDurakTable[table][dtReadyCount]--;

            Durak_CheckReadyCount(table);
        }
    }
    }

    Durak_Kick(playerid);
    Durak_Enumerate(table);
    Durak_UpdateStatus(table);
/*
    switch(gDurakTable[table][dtEndType])
    {
    case DurakEnd_AllowTake:
    {
        if(gDurakTable[table][dtAllowTakeCount] == (gDurakTable[table][dtPlayerCount] - 1))
            Durak_DoAllowTake(table);
    }
    case DurakEnd_Beaten:
    {
        if(gDurakTable[table][dtBeatenCount] == (gDurakTable[table][dtPlayerCount] - 1))
            Durak_EndRound(table);
    }
    }
*/
}

Durak_Kick(const playerid)
{
    new table = p_info[playerid][durak_table];
    new index = p_info[playerid][durak_index];

    Durak_DestroyPTD(playerid, table, index);
    Durak_HideTD(playerid);

    gDurakTable[table][dtPlayerCount]--;
    p_info[playerid][durak_table] = 0;
    gDurakTable[table][dtPlayerId][index] = INVALID_PLAYER_ID;

    CancelSelectTextDraw(playerid);
}

Durak_Enumerate(const table)
{
    new n = 0;

    for(new i = 0; i < MAX_DURAK_PLAYERS; i++)
    {
        if(gDurakTable[table][dtPlayerId][i] == INVALID_PLAYER_ID)
        {
            gDurakTable[table][dtPlayerNumber][i] = -1;
        }
        else
        {
            gDurakTable[table][dtPlayerNumber][i] = n;
            n++;
        }
    }
}

Durak_HandlePTDClick(const playerid, const PlayerText:clickedid)
{
    new table = p_info[playerid][durak_table];
    new index = p_info[playerid][durak_index];

    for(new i = 0; i < DURAK_NUM_BTN; i++)
    {
        if(clickedid == PTD_DurakBtn[table][index][i][DurakBtnElem_Body])
        {
            Durak_OnBtnClick(playerid, i);
            return 1;
        }
    }

    if(gDurakTable[table][dtLobbyState] == DurakLobby_InGame)
    {
        for(new i = 0; i < DURAK_DECK_SIZE; i++)
        {
            if(clickedid == PTD_DurakDeck[table][index][i])
            {
                Durak_OnDeckClick(playerid, i);
                return 1;
            }
        }

        for(new i = 0; i < DURAK_BOARD_SIZE; i++)
        {
            if(clickedid == PTD_DurakBoard[table][index][i][0])
            {
                Durak_OnBoardClick(playerid, i);
                return 1;
            }
        }
    }
    return 1;
}

Durak_OnBtnClick(const playerid, const btn)
{
    new table = p_info[playerid][durak_table];

    if(btn == DurakBtn_Leave)
        return ShowPlayerDialog(playerid, D_DURAK_LEAVE, DIALOG_STYLE_MSGBOX, ""I"Выход", ""W"Если Вы сделали ставку и игра уже началась, то деньги Вам не вернутся!\nВы точно хотите покинуть стол?", "Да", "Нет");

    switch(gDurakTable[table][dtLobbyState])
    {
        case DurakLobby_InGame:
        {
            switch(btn)
            {
            case DurakBtn_Left:
                Durak_OnEndBtnClick(playerid);
            case DurakBtn_PassTurn:
                Durak_OnPassTurnClick(playerid);
            }
        }
        default:
        {
            switch(btn)
            {
                case DurakBtn_Left:
                    Durak_PlayerParam(playerid);
                case DurakBtn_Right:
                    Durak_PlayerReady(playerid);
            }
        }
    }
    return 1;
}

Durak_Second()
{
    for(new table = 1; table <= MAX_DURAK_TABLES; table++)
    {
        switch(gDurakTable[table][dtLobbyState])
        {
        case DurakLobby_Ready:
        {
            Durak_UntilGame(table);
        }
        case DurakLobby_InGame:
        {
            Durak_UntilNextRound(table);
            Durak_UntilForcedEnd(table);
        }
        }
    }
}

#include "logic/casino/durak/durak_status.inc"
#include "logic/casino/durak/durak_lobby.inc"
#include "logic/casino/durak/durak_game.inc"
#include "logic/casino/durak/durak_round.inc"
