const MAX_DURAK_TABLES = 6;

const MAX_DURAK_PLAYERS = 6;
const MIN_DURAK_PLAYERS = 2;

const DURAK_DECK_SIZE = 36;
const DURAK_BOARD_SIZE = 6;

const DURAK_UNTIL_GAME = 10;
const DURAK_UNTIL_NEXT_ROUND = 3;
const DURAK_UNTIL_FORCED_END = 45;

#define DURAK_MIN_BET 1000
#define DURAK_MAX_BET 1000000

#define DURAK_SUIT(%0) ((%0) % 4)
#define DURAK_VALUE(%0) ((%0) / 4)

enum
{
	DurakMode_Simple,
	DurakMode_PassTurn
};

enum
{
	DurakLobby_NotReady,
	DurakLobby_Ready,
	DurakLobby_InGame
};

enum
{
	DurakAct_TurnOpen,
	DurakAct_Defence,
	DurakAct_End
};

enum
{
	DurakEnd_None,
	DurakEnd_WannaTake,
	DurakEnd_AllowTake,
	DurakEnd_Beaten,
	DurakEnd_TurnLeft,
	DurakEnd_DefenderLeft,
	DurakEnd_Win
};

const DURAK_BTN_COLOR = 0x2b2b2bff;
const DURAK_BTN_TEXT_COLOR = 0xffffffff;

const DURAK_BTN_HOVER_COLOR = 0x121212ff;

const DURAK_BTN_DISABLED_COLOR = 0x787878ff;
const DURAK_BTN_TEXT_DISABLED_COLOR = 0xabababff;