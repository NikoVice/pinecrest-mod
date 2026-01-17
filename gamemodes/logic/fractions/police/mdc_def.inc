#define IsPlayerUseMDC(%0) MdcInfo[%0][mdcCreated]

enum
{
    PAGE_NONE,
    PAGE_MAIN,

    PAGE_LOOKUP,

    PAGE_LOOKUP_PERSON,
    PAGE_LOOKUP_VEHICLE,
    PAGE_LOOKUP_VEHICLES_LIST,

    PAGE_MENU,
    PAGE_INFO,

    PAGE_MAP,
    //PAGE_LIC,

    //PAGE_APB,
    //PAGE_CALLS,

    PAGE_CCTV,
    PAGE_ROSTER,

    PAGE_MEMBERS,
    PAGE_MEMBERS_MAP
}

enum MDC_ENUM
{
    mdcCreated,
    mdcPage,

    mdcBack,
    mdcMenu,

    mdcSearch,

    mdcList[18],
    mdcListPage
};
new MdcInfo[MAX_PLAYERS][MDC_ENUM];

#define MAX_TD_MENU_SIZE (18)
new PlayerText:MDC_TD_MENU[MAX_PLAYERS][MAX_TD_MENU_SIZE]; //+

new PlayerText:MDC_LIST[MAX_PLAYERS][16]; //+
new PlayerText:MDC_LOOKUP_VEHICLES_LIST[MAX_PLAYERS][16];
new PlayerText:MDC_UI[MAX_PLAYERS][15];
new PlayerText:MDC_LOOKUP_PERSON[MAX_PLAYERS][12];

new PlayerText:MDC_MAINSCREEN[MAX_PLAYERS][7];
new PlayerText:MDC_LOOKUP_VEHICLE[MAX_PLAYERS][6];
new PlayerText:MDC_OTHER_ADDRESS[MAX_PLAYERS][6];
new PlayerText:MDC_ADDRESS[MAX_PLAYERS][5];
new PlayerText:MDC_VEH_LIST_CLICK[MAX_PLAYERS][4];
new PlayerText:MDC_LOOKUP_SEARCH[MAX_PLAYERS][4];
new PlayerText:MDC_LOOKUP_VEHICLES_ARROWS[MAX_PLAYERS][3];
new PlayerText:MDC_TD_LEFT_PANEL[MAX_PLAYERS][3]; //+
new PlayerText:MDC_LIST_INFO[MAX_PLAYERS][3];
new PlayerText:MDC_LOOKUP_AVATAR[MAX_PLAYERS][2];

new PlayerText:MDC_BACK[MAX_PLAYERS];
new PlayerText:MDC_ERROR_CALLS[MAX_PLAYERS];
new PlayerText:MDC_LOOKUP_ERROR[MAX_PLAYERS];