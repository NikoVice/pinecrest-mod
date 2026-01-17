new const gDurakCardTxd[][] =
{
	"LD_POKE:cd6c",
	"LD_POKE:cd6d",
	"LD_POKE:cd6h",
	"LD_POKE:cd6s",
	"LD_POKE:cd7c",
	"LD_POKE:cd7d",
	"LD_POKE:cd7h",
	"LD_POKE:cd7s",
	"LD_POKE:cd8c",
	"LD_POKE:cd8d",
	"LD_POKE:cd8h",
	"LD_POKE:cd8s",
	"LD_POKE:cd9c",
	"LD_POKE:cd9d",
	"LD_POKE:cd9h",
	"LD_POKE:cd9s",
	"LD_POKE:cd10c",
	"LD_POKE:cd10d",
	"LD_POKE:cd10h",
	"LD_POKE:cd10s",
	"LD_POKE:cd11c",
	"LD_POKE:cd11d",
	"LD_POKE:cd11h",
	"LD_POKE:cd11s",
	"LD_POKE:cd12c",
	"LD_POKE:cd12d",
	"LD_POKE:cd12h",
	"LD_POKE:cd12s",
	"LD_POKE:cd13c",
	"LD_POKE:cd13d",
	"LD_POKE:cd13h",
	"LD_POKE:cd13s",
	"LD_POKE:cd1c",
	"LD_POKE:cd1d",
	"LD_POKE:cd1h",
	"LD_POKE:cd1s"
};

const Float:DURAK_CARD_WIDTH = 40.0;
const Float:DURAK_CARD_HEIGHT = 60.0;

Durak_CreateCard(const playerid, &PlayerText:td, const txd[], const Float:x, const Float:y)
{
	td = CreatePlayerTextDraw(playerid, x, y, txd);
	PlayerTextDrawTextSize(playerid, td, DURAK_CARD_WIDTH, DURAK_CARD_HEIGHT);
	PlayerTextDrawFont(playerid, td, 4);
	PlayerTextDrawSetShadow(playerid, td, 0);
}