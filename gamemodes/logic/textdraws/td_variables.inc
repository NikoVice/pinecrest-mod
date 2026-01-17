enum
{
    TD_ID_NONE,
    TD_ID_SALARY,
    TD_ID_SHOP,
    TD_ID_DICE,
    TD_ID_SPEEDOMETER,
    TD_ID_CAPTURE,
    TD_ID_RECON_INFO,
    TD_ID_RECON_PANEL,
    TD_ID_MINI_GAMES,
    TD_ID_GREEN_ZONE,
    TD_ID_LIST_PAGE,
    TD_ID_CAPTCHA,
    TD_ID_INVENTORY,
    TD_ID_PIN_CODE,
    TD_ID_SERVICE_TUNE,
    TD_ID_PLAYER_MENU,
    TD_ID_ROULETTE,
    TD_ID_CASE,
    TD_ID_PHONE,
    TD_ID_GPS,
    TD_ID_PRESS_ALT,
    TD_ID_LOGO,
    TD_ID_PANEL,
    TD_ID_DONATE_INFO,

    TD_ID_EQUIPMENT_RIGHT,
    TD_ID_EQUIPMENT_LEFT,
    TD_ID_EQUIPMENT_PERSON_INFO,

    TD_ID_INVENTORY_PLAYER,
    TD_ID_INVENTORY_OTHER,
    TD_ID_TRADE,
    TD_ID_CRAFT,
    TD_ID_MARKET,
    TD_ID_ROBBING,
    TD_ID_BATTLEPASS,
    TD_ID_DAILY,

    TD_ID_ELECTRIC,
    TD_ID_RADIO,

    TD_ID_T_HUNTER_GAME,
    TD_ID_T_HUNTER_GPS,

    TD_ID_ALL
}
//interface ID's
enum
{
    INTARFACE_ID_NONE,
    SERVICE_TUNE_INDEX,
    SERVICE_TUNE_EXTERNAL,
    SERVICE_TUNE_COMPONENTS,
    SERVICE_TUNE_ACCESSORIES,
    SERVICE_TUNE_SUSPENSION,
    SERVICE_TUNE_EXTERNAL_VIEW,
    SERVICE_TUNE_ACCESSORIES_VIEW,
    SERVICE_TUNE_COLOR_SELECT,
    SERVICE_TUNE_WHEEL_SIZE,
    SERVICE_TUNE_WHEEL_WIDTH,
    SERVICE_TUNE_WHEEL_OFFSET_X,
    SERVICE_TUNE_WHEEL_ANGLE,
    SERVICE_TUNE_COLOR_LIGHTS,
    SERVICE_TUNE_TONING,

    PLAYER_MENU_INDEX,
    PLAYER_MENU_PROPERTY,
    PLAYER_MENU_TARGET,
    PLAYER_MENU_VEHICLE,
    PLAYER_MENU_TARGET_ACTION,

    INVENTORY_INDEX,

    ROULETTE_INDEX,
    CASE_INDEX,

    PHONE_INDEX,

    //new equipment: inventory / trade
    EQUIPMENT_INVENTORY_PLAYER,
    EQUIPMENT_INVENTORY_HOUSE,
    EQUIPMENT_INVENTORY_BOOT,
    EQUIPMENT_INVENTORY_TRASHBOX,
    EQUIPMENT_INVENTORY_FAMILY,
    EQUIPMENT_INVENTORY_ALL,

    EQUIPMENT_TRADE,
    EQUIPMENT_TRADE_BET_CAR,
    EQUIPMENT_TRADE_BET_HOUSE,
    EQUIPMENT_TRADE_BET_BIZ,
    EQUIPMENT_TRADE_BET_INVENTORY,
    EQUIPMENT_TRADE_READY,

    MARKET_SELL,
    MARKET_BUY,

    INTARFACE_ID_ALL
}

new //Text:TD_Logo_Donate[16],
    Text:TD_Logo_Default[16],
    Text:TD_Logo_Two[2],
    Text:TD_Logo_One[3],
    Text:TD_SpeedometerLine[33],
    Text:TD_TradePreview[8],
    Text:TD_Recon[39],
    Text:TD_GreenZone[6],
    Text:TD_Capture[15],
    Text:TD_ListPage[28],
    Text:TD_ZondCam[11],
    Text:TD_PinCode[17],
    Text:TD_NewSpeedometer,
    Text:TD_ServiceTune[16],
    Text:TD_NewGreenZone,
    Text:TD_GPS,
    Text:TD_PressALT,
    Text:TD_DataTime[2],
    Text:TD_Actions[2],
    Text:TD_Captcha[10],
    Text:TD_BlindBackground;

#define MAX_NEW_SPEEDOMER 11
#define MAX_TD_PLAYER_MENU 32
#define PLAYER_MENU_TYPE_ICON        0
#define PLAYER_MENU_TYPE_ICON_AND_TEXT 1

new PlayerText:PTD_SpeedometerInfo[MAX_PLAYERS][16],
    PlayerText:PTD_Shop[MAX_PLAYERS][11],
    PlayerText:PTD_Dice[MAX_PLAYERS][15],
    PlayerText:PTD_Salary[MAX_PLAYERS][7],
    PlayerText:PTD_Capture[MAX_PLAYERS][10],
    PlayerText:PTD_Recon[MAX_PLAYERS][10],
    PlayerText:PTD_MiniGames[MAX_PLAYERS],
    PlayerText:PTD_ListPage[MAX_PLAYERS][31],
    PlayerText:PTD_Captcha[MAX_PLAYERS][6],
    PlayerText:PTD_PinCode[MAX_PLAYERS][11],
    PlayerText:PTD_NewSpeedometer[MAX_PLAYERS][MAX_NEW_SPEEDOMER],
    PlayerText:PTD_ServiceTune[MAX_PLAYERS][20],
    PlayerText:PTD_ServiceTune_Color[MAX_PLAYERS][12],
    PlayerText:PTD_PlayerMenu[MAX_PLAYERS][MAX_TD_PLAYER_MENU],
    PlayerText:PTD_Roulette[MAX_PLAYERS][58],
    PlayerText:PTD_Case[MAX_PLAYERS][58],
    PlayerText:PTD_Phone[MAX_PLAYERS][7],
    PlayerText:PTD_NewSalary[MAX_PLAYERS][3],
    PlayerText:PTD_EquipmentRight[MAX_PLAYERS][56],
    PlayerText:PTD_EquipmentLeft[MAX_PLAYERS][54],
    PlayerText:PTD_EquipmentPersonInfo[MAX_PLAYERS][30],
    PlayerText:PTD_EquipmentMenu[MAX_PLAYERS][11],

    PlayerText:PTD_Panel[MAX_PLAYERS][19],
    PlayerText:PTD_DonateInfo[MAX_PLAYERS][39],

    PlayerText:PTD_CraftMain[MAX_PLAYERS][26],
    PlayerText:PTD_CraftButtonItems[MAX_PLAYERS][8],
    PlayerText:PTD_CraftButtonItemsName[MAX_PLAYERS][8],
    PlayerText:PTD_CraftInfo[MAX_PLAYERS][5],
    PlayerText:PTD_CraftResources[MAX_PLAYERS][5],
    PlayerText:PTD_CraftResourcesInfo[MAX_PLAYERS][5],

    PlayerText:PTD_Robbing[MAX_PLAYERS][14],

    PlayerText:PTD_BattlePassMain[MAX_PLAYERS][18],
    PlayerText:PTD_BattlePassInfo[MAX_PLAYERS][5],
    PlayerText:PTD_BattlePassButton[MAX_PLAYERS][8],
    PlayerText:PTD_BattlePassRewardMain[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassRewardButton[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassRewardText[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassRewardModel[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassRewardInfo[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassTaskMain[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassTaskName[MAX_PLAYERS][3],
    PlayerText:PTD_BattlePassTaskInfo[MAX_PLAYERS][3],
    PlayerText:PTD_DailyMain[MAX_PLAYERS][3],
    PlayerText:PTD_DailyButton[MAX_PLAYERS][8],
    PlayerText:PTD_DailyInfo[MAX_PLAYERS][2],
    PlayerText:PTD_DailyRewardMain[MAX_PLAYERS][3],
    PlayerText:PTD_DailyRewardButton[MAX_PLAYERS][3],
    PlayerText:PTD_DailyRewardText[MAX_PLAYERS][3],
    PlayerText:PTD_DailyRewardModel[MAX_PLAYERS][3],
    PlayerText:PTD_DailyRewardInfo[MAX_PLAYERS][3],
    PlayerText:PTD_Electric[MAX_PLAYERS][14],
    PlayerText:PTD_Radio[MAX_PLAYERS][36],
    PlayerText:PTD_THunterGame[MAX_PLAYERS][36],
    PlayerText:PTD_THunterGPS[MAX_PLAYERS][9]
;
