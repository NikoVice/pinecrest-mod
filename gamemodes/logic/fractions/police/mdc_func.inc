MDC_Hide(playerid)
{
    MdcInfo[playerid][mdcCreated] = 0;
    MdcInfo[playerid][mdcPage] = PAGE_NONE;

    for(new i = 17; i != -1; i--)
    {
        PlayerTextDrawDestroy(playerid, MDC_TD_MENU[playerid][i]);
        //MDC_TD_MENU[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        if(i < 16) {
            PlayerTextDrawDestroy(playerid, MDC_LIST[playerid][i]);
            //MDC_LIST[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            PlayerTextDrawDestroy(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][i]);
            //MDC_LOOKUP_VEHICLES_LIST[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            if(i < 15) {
                PlayerTextDrawDestroy(playerid, MDC_UI[playerid][i]);
                //MDC_UI[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                if(i < 12) {
                    PlayerTextDrawDestroy(playerid, MDC_LOOKUP_PERSON[playerid][i]);
                    //MDC_LOOKUP_PERSON[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    if(i < 7) {
                        PlayerTextDrawDestroy(playerid, MDC_MAINSCREEN[playerid][i]);
                        //MDC_MAINSCREEN[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                        if(i < 6) {
                            PlayerTextDrawDestroy(playerid, MDC_LOOKUP_VEHICLE[playerid][i]);
                            //MDC_LOOKUP_VEHICLE[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                            PlayerTextDrawDestroy(playerid, MDC_OTHER_ADDRESS[playerid][i]);
                            //MDC_OTHER_ADDRESS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                            if(i < 5) {
                                PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][i]);
                                //MDC_ADDRESS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                if(i < 4) {
                                    PlayerTextDrawDestroy(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
                                    //MDC_LOOKUP_SEARCH[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                    PlayerTextDrawDestroy(playerid, MDC_VEH_LIST_CLICK[playerid][i]);
                                    //MDC_VEH_LIST_CLICK[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                    if(i < 3) {
                                        PlayerTextDrawDestroy(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][i]);
                                        //MDC_LOOKUP_VEHICLES_ARROWS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                        PlayerTextDrawDestroy(playerid, MDC_LIST_INFO[playerid][i]);
                                        //MDC_LIST_INFO[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                        PlayerTextDrawDestroy(playerid, MDC_TD_LEFT_PANEL[playerid][i]);
                                        //MDC_TD_LEFT_PANEL[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                        if(i < 2) {
                                            PlayerTextDrawDestroy(playerid, MDC_LOOKUP_AVATAR[playerid][i]);
                                            //MDC_LOOKUP_AVATAR[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    PlayerTextDrawDestroy(playerid, MDC_LOOKUP_ERROR[playerid]);
    //MDC_LOOKUP_ERROR[playerid] = PlayerText:INVALID_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, MDC_ERROR_CALLS[playerid]);
    //MDC_ERROR_CALLS[playerid] = PlayerText:INVALID_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, MDC_BACK[playerid]);
    //MDC_BACK[playerid] = PlayerText:INVALID_TEXT_DRAW;

    CancelSelectTextDraw(playerid);

    DeletePVar(playerid, #MDC_OWNER_ID);
    DeletePVar(playerid, #MDC_ID);
    DeletePVar(playerid, #MDC_VEHICLE_NUM);
    DeletePVar(playerid, #MDC_SEARCH_VEHICLE_NUM);
    DeletePVar(playerid, #MDC_MAX_PAGE);

    DeletePVar(playerid, #MDC_APB_S);
    DeletePVar(playerid, #MDC_APB_TEXT);

    p_temp[playerid][MDC_BODYCAM] = INVALID_PLAYER_ID;

    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !GetPVarInt(playerid, #CCTV_MDC_USE))
        ShowTextDraw_Speedometr(playerid, true);
    return 1;
}

MDC_Show(playerid)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) HideTextDraw_Speedometr(playerid, true);
    #include "logic/fractions/police/mdc_txd.inc"

    new string[124];
    format(string, sizeof(string), "~n~-_MOBILE DATA COMPUTER_-~n~%s", get_name(playerid));
    PlayerTextDrawSetString(playerid, MDC_UI[playerid][9], string);

    MdcInfo[playerid][mdcCreated] = 1;
    MdcInfo[playerid][mdcSearch] = 0;

    return MDC_PAGE(playerid);
}

MDC_PAGE(playerid, page = PAGE_MAIN)
{
    if(p_info[playerid][rang] < 1 || p_info[playerid][member] < 1)
        return SendError(playerid, "Ошибка MDC-2912: Обратитесь на форум в раздел багов.");
    Update_MDC(playerid, page);
    switch(page)
    {
        case PAGE_MAIN:
        {
            PlayerTextDrawSetPreviewModel(playerid, MDC_MAINSCREEN[playerid][0], GetPlayerSkin(playerid));
            PlayerTextDrawShow(playerid, MDC_MAINSCREEN[playerid][0]);

            new string[124];
            format(string, sizeof(string), "%s %s", GetPlayerFractionRangName(playerid), get_name(playerid));
            PlayerTextDrawSetString(playerid, MDC_MAINSCREEN[playerid][2], string);

            //                             "СОТРУДНИКОВ НА СЛУЖБЕ:~n~ОРДЕРЫ:~n~В РОЗЫСКЕ:");
            format(string, sizeof(string), "%i~n~TBA~n~TBA", GetFractionOnline(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_MAINSCREEN[playerid][4], string);

            //                            "ПРИНЯТО ВЫЗОВОВ:~n~АРЕСТОВАНО:~n~ВЫПИСАНО ШТРАФОВ:");
            format(string, sizeof(string), "%i~n~%i~n~%i", p_temp[playerid][pPoliceCalls], p_temp[playerid][pPoliceJails], p_temp[playerid][pPoliceFines]);
            PlayerTextDrawSetString(playerid, MDC_MAINSCREEN[playerid][6], string);

            format(string, sizeof(string), "%s MDC >> Main Screen", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_CCTV:
        {
            new query[255];
            mysql_format(con_bd, query, sizeof(query), "SELECT * FROM `cctvs` ORDER BY `id` LIMIT 16");
            mysql_tquery(con_bd, query, "MDC_ShowCCTVMenu", "ii", playerid, 0);

            MdcInfo[playerid][mdcListPage] = 0;
            //MdcInfo[playerid][mdcMenu] = PAGE_CCTV;

            new Float:countcctvs = MDC_CountCCTVS();
            countcctvs = countcctvs/16;
            SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countcctvs, floatround_ceil));
        }
        case PAGE_ROSTER:
        {
            MdcInfo[playerid][mdcListPage] = 0;
            MdcInfo[playerid][mdcMenu] = PAGE_ROSTER;

            new Float:countRoster = MDC_CountRoster();
            countRoster = countRoster/18;
            SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countRoster, floatround_ceil));

            MDC_ShowRosterMenu(playerid);
        }
        case PAGE_MEMBERS:
        {
            MdcInfo[playerid][mdcListPage] = 0;
            MdcInfo[playerid][mdcMenu] = PAGE_MEMBERS;

            new Float:countMembers = GetFractionOnline(p_info[playerid][member]);
            countMembers = countMembers/18;
            SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countMembers, floatround_ceil));

            MDC_ShowMembersMenu(playerid);
        }
    }
    return 1;
}

Update_MDC(playerid, page)
{
    new oldpage = MdcInfo[playerid][mdcPage];

    if(oldpage == page) return 1;

    if((oldpage == PAGE_LOOKUP_PERSON || oldpage == PAGE_LOOKUP_VEHICLE || oldpage == PAGE_LOOKUP || oldpage == PAGE_LOOKUP_VEHICLES_LIST) && page == PAGE_LOOKUP)
        return 1;

    MdcInfo[playerid][mdcPage] = page;

    for(new z = 2; z < 11; z++)
    {
        PlayerTextDrawColor(playerid, MDC_UI[playerid][z], 0x494949FF);
        PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][z], 0xa7a7a7FF);
        //f(STRING_GLOBAL, "ID_TD: %d", z);
        //PlayerTextDrawSetString(playerid, MDC_UI[playerid][z], STRING_GLOBAL);
        PlayerTextDrawShow(playerid, MDC_UI[playerid][z]);
    }

    switch(oldpage)
    {
        case PAGE_MAIN:
        {
            for(new y = 0; y < 7; y++)  PlayerTextDrawHide(playerid, MDC_MAINSCREEN[playerid][y]);
        }
        case PAGE_LOOKUP:
        {
            if(page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLE && page != PAGE_LOOKUP_VEHICLES_LIST)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
                PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
            }
        }
        case PAGE_LOOKUP_PERSON:
        {
            if(page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLE && page != PAGE_LOOKUP_VEHICLES_LIST)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }

            for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
            for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_LOOKUP_VEHICLE:
        {
            if(page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLE && page != PAGE_LOOKUP_VEHICLES_LIST)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }
            else
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }

            for(new a = 0; a < 6; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLE[playerid][a]);

            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_LOOKUP_VEHICLES_LIST:
        {
            if(page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLES_LIST && page != PAGE_LOOKUP_VEHICLE)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }

            for(new a = 0; a < 16; a++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
            for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
            for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_MENU:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LIST[playerid][a]);

            if(GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
        }
        case PAGE_INFO:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            for(new a = 0; a < 3; a++)  PlayerTextDrawHide(playerid, MDC_LIST_INFO[playerid][a]);
        }
        case PAGE_MAP:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);

            for(new j = 0; j < 6; j++) PlayerTextDrawHide(playerid, MDC_OTHER_ADDRESS[playerid][j]);
            for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, MDC_ADDRESS[playerid][i]);
        }
        case PAGE_MEMBERS_MAP:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);

            for(new j = 0; j < 6; j++) PlayerTextDrawHide(playerid, MDC_OTHER_ADDRESS[playerid][j]);
            for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, MDC_ADDRESS[playerid][i]);
            for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][i]);
            for(new a = 0; a < 2; a++) PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);

            PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][4], ">> WRITE ARREST RECORD");
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][3], "~l~AVAILABLE FUNCTIONS:");
            //PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][3], true);
            //PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][3], true);

            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            p_temp[playerid][MDC_BODYCAM] = INVALID_PLAYER_ID;
        }

        case PAGE_CCTV:
        {
            PlayerTextDrawHide(playerid, MDC_ERROR_CALLS[playerid]);

            for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LIST[playerid][a]);

            if(GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
        }

        case PAGE_ROSTER, PAGE_MEMBERS:
        {
            for(new j = 0; j < 3; j++)   PlayerTextDrawHide(playerid, MDC_TD_LEFT_PANEL[playerid][j]);
            for(new i = 0; i < 18; i++)  PlayerTextDrawHide(playerid, MDC_TD_MENU[playerid][i]);
        }
    }

    switch(page)
    {
        case PAGE_MAIN:
        {
            for(new y = 0; y < 7; y++)  PlayerTextDrawShow(playerid, MDC_MAINSCREEN[playerid][y]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][2], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][2], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][2]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Main Screen", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_LOOKUP:
        {
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

            new string[128];
            format(string, sizeof(string), "%s MDC >> Search", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);

            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][0], "NAME");
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "VEHICLE");

            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF); // ИМЯ

            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
            PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF); // ТС

            for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            MdcInfo[playerid][mdcSearch] = 0;
            //PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_LOOKUP_PERSON:
        {
            for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            for(new b = 0; b < 12; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][10]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            //PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
            new string[128];
            format(string, sizeof(string), "%s MDC >> Search", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_LOOKUP_VEHICLE:
        {
            for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            for(new i = 0; i < 6; i++) PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLE[playerid][i]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Search", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_LOOKUP_VEHICLES_LIST:
        {
            for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            //for(new a = 0; a < 16; a++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
            //for(new b = 0; b < 4; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Search", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_MENU:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            if(GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            //for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LIST[playerid][a]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> List", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_INFO:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            for(new a = 0; a < 3; a++)  PlayerTextDrawShow(playerid, MDC_LIST_INFO[playerid][a]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Search", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }

        case PAGE_MAP:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            for(new i = 0; i < 5; i++) if(i != 2) PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][i]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Addresses", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }

        case PAGE_MEMBERS_MAP:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][5], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][5], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][5]);

            for(new i = 0; i < 2; i++) PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][i]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Members", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);
        }
        case PAGE_ROSTER:
        {
            PlayerTextDrawColor(playerid, MDC_UI[playerid][7], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][7], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][7]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Roster", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);

            for(new j = 0; j < 3; j++)  PlayerTextDrawShow(playerid, MDC_TD_LEFT_PANEL[playerid][j]);
        }
        case PAGE_MEMBERS:
        {
            PlayerTextDrawColor(playerid, MDC_UI[playerid][5], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][5], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][5]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> Members", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);

            for(new j = 0; j < 3; j++)  PlayerTextDrawShow(playerid, MDC_TD_LEFT_PANEL[playerid][j]);
        }
        case PAGE_CCTV:
        {
            PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "LIST OF ALL AVAILABLE CCTV:");
            PlayerTextDrawShow(playerid, MDC_ERROR_CALLS[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][8], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][8], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][8]);

            new string[128];
            format(string, sizeof(string), "%s MDC >> CCTV", GetFractionName(p_info[playerid][member]));
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);

            if(GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
        }
    }

    return 1;
}

this::MDCSearchPersonInfo(playerid)
{
    if(!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

        for(new a = 0; a < 2; a++) PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
        for(new b = 0; b < 12; b++) PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);
        for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
        for(new d = 0; d < 16; d++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

        MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
        return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }
    MdcInfo[playerid][mdcMenu] = PAGE_LOOKUP_PERSON;

    Update_MDC(playerid, PAGE_LOOKUP_PERSON);
    PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

    new ownername[MAX_PLAYER_NAME],
        strhouse[128],
        strlic[128],
        str[10 + 24 + 128 + 64 + 24 + 24],
        count = 0;

    cache_get_value_name(0, "name", ownername);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], ownername);

    new Licenses[8];
    cache_get_value_name(0, "Lic", strlic);
    sscanf(strlic, "p<|>a<i>[9]", Licenses);

    if(Licenses[LIC_CAR] == 1)
    {
        count++;
        format(strlic, sizeof(strlic), "Driver");
    }
    if(Licenses[LIC_MOTO] == 1)
    {
        if(count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
        format(strlic, sizeof(strlic), "%sMoto", strlic);
        count++;
    }
    if(Licenses[LIC_WEAPON] == 1)
    {
        if(count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
        format(strlic, sizeof(strlic), "%sWeapon", strlic);
        count++;
    }
    if(Licenses[LIC_PLANE] == 1)
    {
        if(count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
        format(strlic, sizeof(strlic), "%sPilot", strlic);
        count++;
    }
    if(Licenses[LIC_BOAT] == 1)
    {
        if(count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
        format(strlic, sizeof(strlic), "%sBoat", strlic);
        count++;
    }
    if(Licenses[LIC_FISHING] == 1)
    {
        if(count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
        format(strlic, sizeof(strlic), "%sFishing", strlic);
        count++;
    }
    if(Licenses[LIC_TAXI] == 1)
    {
        if(count > 0 && count < 6) format(strlic, sizeof(strlic), "%s, ", strlic);
        if(count < 6) format(strlic, sizeof(strlic), "%sTaxi", strlic);
        count++;
    }
    if(Licenses[LIC_HUNTER] == 1)
    {
        if(count > 0 && count < 6) format(strlic, sizeof(strlic), "%s, ", strlic);
        if(count < 6) format(strlic, sizeof(strlic), "%sHunter", strlic);
        count++;
    }
    if(count > 6) format(strlic, sizeof(strlic), "%s, ...", strlic);
    if(!count) format(strlic, sizeof(strlic), "None");

    new jailID;
    cache_get_value_name_int(0, "jail", jailID);

    if(1<= jailID <= 4 || count > 0)
    {
        new user_skin_id;
        cache_get_value_name_int(0, "item_id", user_skin_id);

        PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], user_skin_id);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][1]);

        PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][0]);
    }
    else
    {
        PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][0]);
        PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][1]);
    }


    new player_db_id, active_house;
    cache_get_value_name_int(0, "id", player_db_id);
    cache_get_value_name_int(0, "active_house_id", active_house);

    count = 0;
    new city, area;
    for(new i = totalhouses-1; i != -1; i--)
    {
        if(h_info[i][h_mysql_id] == INVALID_MYSQL_ID) continue;
        if(h_info[i][h_delete] == 1) continue;
        if( h_info[i][h_r_user_id][0] == player_db_id ||
            h_info[i][h_r_user_id][1] == player_db_id ||
            h_info[i][h_r_user_id][2] == player_db_id ||
            h_info[i][h_r_user_id][3] == player_db_id)
        {
            city = GetCityName(h_info[i][h_enter][0], h_info[i][h_enter][1]),
            area = GetZonaName(h_info[i][h_enter][0], h_info[i][h_enter][1]);
            format(strhouse, sizeof(strhouse), "%s, %s %d", gSAZonesCity[city][SAZONE_NAME],gSAZones[area][SAZONE_NAME], i);
            count++;
            break;
        }
        if(h_info[i][h_user_id] != player_db_id) continue;
        if(count == active_house)
        {
            city = GetCityName(h_info[i][h_enter][0], h_info[i][h_enter][1]),
            area = GetZonaName(h_info[i][h_enter][0], h_info[i][h_enter][1]);
            format(strhouse, sizeof(strhouse), "%s, %s %d", gSAZonesCity[city][SAZONE_NAME],gSAZones[area][SAZONE_NAME], i);
            count++;
            break;
        }
        count++;
    }

    if(!count)
    {
        format(strhouse, sizeof(strhouse), "Not found");
        PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][10]);
    }
    else
    {
        if(count > 1) PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][10], "]_THIS PERSON HAS MULTIPLE ADDRESSES; CLICK HERE FOR A LIST.");
        else PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][10], "]_CLICK HERE TO VIEW HOUSE LOCATION ON MAP;");

        PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][10]);
    }
    new player_phone_number;
    cache_get_value_name_int(0, "phone_number", player_phone_number);
    format(str, sizeof(str), "%s~n~%i~n~%i prison sentences~n~%s~n~%s",
        ownername, player_phone_number, jailID, strlic, strhouse);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][2], str);

    new tickets = CountPlayerTicketsID(player_db_id);
    if(tickets > 0) {
        format(str, sizeof(str), "~y~%i~w~~n~Unpaid fines!", tickets);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][11], str);
    }
    else PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][11]);

    SetPVarInt(playerid, #MDC_ID, player_db_id);

    new query[128];
    mysql_format(con_bd, query, sizeof(query), "SELECT * FROM `criminalrecords` WHERE `userid` = %i", player_db_id);
    mysql_tquery(con_bd, query, "MDCPersonCriminalHistory", "i", playerid);
    return 1;
}

this::MDCPersonCriminalHistory(playerid)
{
    if(!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][8], "- Criminal history is clear.");
        PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][9]);
        return 1;
    }

    new count = 0;

    if(cache_num_rows() > 5) count = 5;
    else count = cache_num_rows();

    new arrest_status;
    cache_get_value_name_int(count-1, "arrest", arrest_status);
    /*for(new i; i < count; i++)
    {
        cache_get_value_name_int(i, "arrest", arrest_status);
        if(arrest_status == 1)
        {
            new strtemp[124];
            cache_get_value_name(i, "charge", strtemp);

            if(strlen(strtemp) > 36)
                format(str, sizeof(str), "%s-_%s~n~", str, TextTab(strtemp, 30, 36, 0));
            else
                format(str, sizeof(str), "%s-_%s~n~", str, strtemp);

            newcount++;
        }
    }*/

    if(arrest_status == 1) PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][9]);
    else PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][9]);

    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][8], "- Criminal history (Click for more details).");
    return 1;
}
/*
IsPlayerWanted(playerid)
{
    new query[128];
    mysql_format(con_bd, query, sizeof(query), "SELECT `arrest` FROM `criminalrecords` WHERE `userid` = %i ORDER BY `id` DESC LIMIT 1", playerid);
    new Cache:cache = mysql_query(con_bd, query);
    if(!cache_num_rows()) return 0;
    new    arrest;
    cache_get_value_name_int(0, "arrest", arrest);
    cache_delete(cache);
    if(arrest != 1) return 1;
    else            return 0;
}
*/

this::MDCSearchVehiclesList_GetID(playerid)
{
    if(!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

        for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
        for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

        for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
        for(new d = 0; d < 16; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

        MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
        return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }
    new player_db_id;
    cache_get_value_name_int(0, "id", player_db_id);
    new query[256];
    mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_owner_id` = %i AND `v_number` != 'NULL'", player_db_id);
    mysql_tquery(con_bd, query, "MDCSearchVehiclesList", "ii", playerid, 1);
    return 1;
}

this::MDCSearchVehiclesList(playerid, types)
{
    new rows = cache_num_rows();
    if(!rows)
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

        for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
        for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

        for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
        for(new d = 0; d < 16; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

        MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
        return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }
    new ownername[MAX_PLAYER_NAME];
    if(types)
    {
        cache_get_value_name(0, "ownername", ownername);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], ownername);

        new temp_v_owner_id;
        cache_get_value_name_int(0, "v_owner_id", temp_v_owner_id);
        SetPVarInt(playerid, #MDC_OWNER_ID, temp_v_owner_id);
    }
    else
    {
        new numbers[24];
        GetPVarString(playerid, #MDC_SEARCH_VEHICLE_NUM, numbers, 24);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], numbers);
        DeletePVar(playerid, #MDC_OWNER_ID);
    }
    if(rows == 1 && MdcInfo[playerid][mdcListPage] == 0)
    {
        new temp_v_mysql_id;
        cache_get_value_name_int(0, "v_mysql_id", temp_v_mysql_id);
        new query[186];
        mysql_format(con_bd, query, sizeof(query), "SELECT *, (SELECT `name` FROM `accounts` WHERE id = vehicle.v_owner_id) as ownername FROM `vehicle` WHERE `v_mysql_id` = %i AND `v_number` != 'NULL'", temp_v_mysql_id);
        mysql_tquery(con_bd, query, "MDCSearchVehicle", "ii", playerid, 1);
        return 1;
    }
    PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

    for(new j = 0; j < 16; j++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][j]);
    for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);

    new model, number[24], insurances[11], impounded[7],
        temp_v_wanted, temp_v_insurence, temp_v_impounded, temp_v_color[2];

    static const str_size[] = "%s~n~%s~n~%s~n~%s~n~%s";
    new mes[sizeof(str_size) + 32 + MAX_PLAYER_NAME + 24 + 24 + 11 + 7];

    for(new i; i < rows; i++)
    {
        if(i > 3) break;
        PlayerTextDrawShow(playerid, MDC_VEH_LIST_CLICK[playerid][i]);

        if(!types) cache_get_value_name(i, "ownername", ownername);
        cache_get_value_name_int(i, "v_mysql_id", MdcInfo[playerid][mdcList][i]);
        cache_get_value_name(i, "v_number", number);
        cache_get_value_name_int(i, "v_model", model);
        cache_get_value_name_int(i, "v_wanted", temp_v_wanted);

        if(temp_v_wanted) PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3+i*4]);
        else PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3+i*4]);

        cache_get_value_name_int(i, "v_insurance", temp_v_insurence);
        cache_get_value_name_int(i, "v_impound", temp_v_impounded);

        format(insurances, sizeof(insurances), "%s", !temp_v_insurence ? "~l~NO" : "~g~YES");
        format(impounded, sizeof(impounded), "%s", !temp_v_impounded ? "~l~NO":"~r~YES");

        format(mes, sizeof(mes), str_size, GetVehicleName(INVALID_VEHICLE_ID, model), number, ownername, insurances, impounded);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1+i*4], mes);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1+i*4]);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2+i*4]);

        cache_get_value_name_int(i, "v_color_0", temp_v_color[0]);
        cache_get_value_name_int(i, "v_color_1", temp_v_color[1]);

        PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0+i*4], model);
        PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0+i*4], temp_v_color[0], temp_v_color[1]);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0+i*4]);
    }
    new max_page = GetPVarInt(playerid, #MAX_MDC_PAGE);
    if(!max_page)
    {
        max_page = floatround(rows/4.0, floatround_ceil);
        SetPVarInt(playerid, #MAX_MDC_PAGE, max_page);
    }
    if(max_page > 1)
    {
        new str[8];
        format(str, sizeof(str), "%i/%i", MdcInfo[playerid][mdcListPage]+1, max_page);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], str);
        for(new i = 0; i < 3; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][i]);
    }
    else
    {
        for(new i = 0; i < 3; i++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][i]);
    }

    Update_MDC(playerid, PAGE_LOOKUP_VEHICLES_LIST);
    return 1;
}

this::MDCSearchVehicle(playerid, types)
{
    if(!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

        for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
        for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

        for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 4; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
        for(new d = 0; d < 16; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

        MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
        return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }
    PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

    new ownername[MAX_PLAYER_NAME], model, number[24], insurances[8], impounded[4],
        temp_v_wanted, temp_v_mysql_id;

    cache_get_value_name_int(0, "v_mysql_id", temp_v_mysql_id);
    SetPVarInt(playerid, #MDC_ID, temp_v_mysql_id);

    cache_get_value_name(0, "ownername", ownername);
    cache_get_value_name(0, "v_number", number);
    cache_get_value_name_int(0, "v_model", model);
    cache_get_value_name_int(0, "v_wanted", temp_v_wanted);

    if(temp_v_wanted)
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][5], ">> REMOVE TRANSPORT WANTED, STATUS: ~r~ WANTED");
    else
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][5], ">> DECLARE CAR IN WANTED, STATUS: ~g~ NOT WANTED");

    new temp_v_insurence, temp_v_impounded;
    cache_get_value_name_int(0, "v_insurance", temp_v_insurence);
    cache_get_value_name_int(0, "v_impound", temp_v_impounded);

    format(insurances, sizeof(insurances), "%s", !temp_v_insurence ? "No" : "Yes");
    format(impounded, sizeof(impounded), "%s", !temp_v_impounded ? "No":"Yes");

    static const str_size[] = "%s~n~%s~n~%s~n~%s~n~%s"; // ~n~%s
    new mes[sizeof(str_size) + 32 + MAX_PLAYER_NAME + 24 + 24 + 8 + 4];

    format(mes, sizeof(mes), str_size, GetVehicleName(INVALID_VEHICLE_ID, model), number, ownername, insurances, impounded);//, date);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][1], mes);

    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLE[playerid][0], model);

    new temp_v_color[2];
    cache_get_value_name_int(0, "v_color_0", temp_v_color[0]);
    cache_get_value_name_int(0, "v_color_1", temp_v_color[1]);

    PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLE[playerid][0], temp_v_color[0], temp_v_color[1]);
    PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLE[playerid][0]);

    new string[128];
    format(string, sizeof(string), "]__VIEW_FINES__(UNPAID_FINES:__%i)", CountVehicleTicketsID(temp_v_mysql_id));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][3], string);

    PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], number);

    MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_VEHICLES_LIST;
    MdcInfo[playerid][mdcMenu] = PAGE_LOOKUP_VEHICLE;
    Update_MDC(playerid, PAGE_LOOKUP_VEHICLE);

    if(types)
    {
        PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
        for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
    }
    return 1;
}

this::MDC_Veh_Wanted(playerid) // ОШИБКА!
{
    new temp_v_mysql_id = GetPVarInt(playerid, #MDC_ID);
    if(!temp_v_mysql_id) return SendError(playerid, "BUG: MDC0001");

    new veh_wanted, query[156], numbers[24], model;
    cache_get_value_name_int(0, "v_wanted", veh_wanted);
    cache_get_value_name(0, "v_number", numbers);
    cache_get_value_name_int(0, "v_model", model);

    if(veh_wanted)
    {
        mysql_format(con_bd, query, sizeof(query), "UPDATE `vehicle` SET `v_wanted` = 0 WHERE `v_mysql_id` = %d", temp_v_mysql_id);
        mysql_tquery(con_bd, query);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][5], ">> DECLARE CAR IN WANTED, STATUS: ~g~ NOT WANTED");

        SendAccess(playerid, "Транспорт больше не в розыске.");

        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "[WANTED] Транcпорт: %s [%s] удален из розыска. Офицер: %s.", GetVehicleName(INVALID_VEHICLE_ID, model), numbers, get_name(playerid));
        SendFractionMessage(POLICE_LS, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(POLICE_SF, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(POLICE_LV, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(POLICE_RC, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(FBI_TEAM, 0x33CC66FF, STRING_GLOBAL);

        for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
        {
            if(veh_info[i][v_mysql_id] == temp_v_mysql_id)
            {
                veh_info[i][v_wanted] = 0;
                break;
            }
        }
    }
    else
    {
        mysql_format(con_bd, query, sizeof(query), "UPDATE `vehicle` SET `v_wanted` = 1 WHERE `v_mysql_id` = %d", temp_v_mysql_id);
        mysql_tquery(con_bd, query);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][5], ">> REMOVE TRANSPORT WANTED, STATUS: ~r~ WANTED");

        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "[WANTED] Транcпорт: %s [%s] обьявлен в розыск. Офицер: %s.", GetVehicleName(INVALID_VEHICLE_ID, model), numbers, get_name(playerid));
        SendFractionMessage(POLICE_LS, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(POLICE_SF, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(POLICE_LV, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(POLICE_RC, 0x33CC66FF, STRING_GLOBAL);
        SendFractionMessage(FBI_TEAM, 0x33CC66FF, STRING_GLOBAL);

        SendAccess(playerid, "Транспорт успешно обьявлен в розыск.");

        for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
        {
            if(veh_info[i][v_mysql_id] == temp_v_mysql_id)
            {
                veh_info[i][v_wanted] = 1;
                break;
            }
        }
    }
    return 1;
}

this::MDC_VEHICLE_NOTE_INFO(playerid)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "BUG: MDC00002");
    new ownername[MAX_PLAYER_NAME], officername[MAX_PLAYER_NAME], text[128], date[20];

    cache_get_value_name_int(0, "id", p_temp[playerid][p_listitem_int]);
    cache_get_value_name(0, "ownername",  ownername);
    cache_get_value_name(0, "officername",  officername);
    cache_get_value_name(0, "text", text);
    cache_get_value_name(0, "date", date);

    STRING_GLOBAL[0] = EOS;
    f(STRING_GLOBAL,
        ""W"Владелец: "I"%s\n\
        "W"Офицер: "I"%s\n\n\
        "W"Текст: "I"%s\n\n\
        "W"Дата: "I"%s", ownername, officername, text, date);
    ShowPlayerDialog(playerid, D_MDC_VEHICLE_NOTE, DIALOG_STYLE_MSGBOX, ""I"MDC - Запись о ТС", STRING_GLOBAL, "Закрыть", "Удалить");
    return 1;
}

CountVehicleNotesID(vehicle_mysql_id)
{
    new query[128], count;
    mysql_format(con_bd, query, sizeof(query), "SELECT COUNT(id) AS total FROM `vehicle_note` WHERE `vehicle_id` = %d", vehicle_mysql_id);
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

this::MDC_ShowCCTVMenu(playerid, back)
{
    new string[256], info[32], break_status, index[5];
    PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "LIST OF ALL AVAILABLE CCTV:");

    for(new j = 0; j < 16; j++)
    {
        PlayerTextDrawHide(playerid, MDC_LIST[playerid][j]);
        MdcInfo[playerid][mdcList][j] = -1;
    }

    if(cache_num_rows())
    {
        if(!back)
        {
            for(new i = 0; i < cache_num_rows(); i++)
            {
                cache_get_value_name(i, "info", info);
                cache_get_value_name_int(i, "id", MdcInfo[playerid][mdcList][i]);
                cache_get_value_name_int(i, "break", break_status);
                format(string, sizeof(string), "%s", break_status ? "~r~OFFLINE":"~g~ONLINE_");

                if(MdcInfo[playerid][mdcList][i] > 99) format(index, sizeof(index), "0%i", MdcInfo[playerid][mdcList][i]);
                else if(MdcInfo[playerid][mdcList][i] > 9) format(index, sizeof(index), "00%i", MdcInfo[playerid][mdcList][i]);
                else format(index, sizeof(index), "000%i", MdcInfo[playerid][mdcList][i]);

                format(string, sizeof(string), "__STATUS:_%s~l~_____________ID:_%s______________%s", string, index, info);
                PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], string);

                PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], 0x494949FF);
                PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], 0xa7a7a7FF);

                PlayerTextDrawShow(playerid, MDC_LIST[playerid][i]);
            }
        }
        else
        {
            for(new i = cache_num_rows()-1; i >= 0; i--)
            {
                cache_get_value_name(i, "info", info);
                cache_get_value_name_int(i, "id", MdcInfo[playerid][mdcList][i]);
                cache_get_value_name_int(i, "break", break_status);
                format(string, sizeof(string), "%s", break_status ? "~r~OFFLINE":"~g~ONLINE_");
                new index[5];
                if(i > 99) format(index, sizeof(index), "0%i", i);
                else if(i > 9) format(index, sizeof(index), "00%i", i);
                else format(index, sizeof(index), "000%i", i);

                format(string, sizeof(string), "__STATUS:_%s~l~_____________ID:_%s______________%s", string, index, info);

                PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], string);
                PlayerTextDrawShow(playerid, MDC_LIST[playerid][i]);
            }
        }
    }
    else return PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "]__ERROR: FOUND NOTHING!");
    Update_MDC(playerid, PAGE_CCTV);

    new strpage[7];
    format(strpage, sizeof(strpage), "%i/%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if(GetPVarInt(playerid, #MAX_MDC_PAGE) == 1) for(new k = 0; k < 3; k++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    else for(new k = 0; k < 3; k++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    return 1;
}

MDC_ShowRosterMenu(playerid)
{
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][0], "List of active units:");
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][1], "Change callsign");

    new string[128], count, pageCount, f = GetPatrolID(playerid);

    for(new j = 0; j < 18; j++) PlayerTextDrawHide(playerid, MDC_TD_MENU[playerid][j]);
    for(new j = 0; j < 18; j++) MdcInfo[playerid][mdcList][j] = 0;

    for(new i = 0; i != MAX_PATROL; i++)
    {
        if(!PatrolInfo[f][i][patrulExists]) continue;
        if(pageCount++ < 18*(MdcInfo[playerid][mdcListPage])) continue;

        format(string, sizeof(string), "__%s:__", PatrolInfo[f][i][patrulName]);

        if(PatrolInfo[f][i][patrulOfficer][0] != INVALID_PLAYER_ID)
            format(string, sizeof(string), "%s%s", string, GetSurnameNick(PatrolInfo[f][i][patrulOfficer][0]));
        if(PatrolInfo[f][i][patrulOfficer][1] != INVALID_PLAYER_ID)
        {
            if(PatrolInfo[f][i][patrulOfficer][0] != INVALID_PLAYER_ID)
                format(string, sizeof(string), "%s__,__%s", string, GetSurnameNick(PatrolInfo[f][i][patrulOfficer][1]));
            else
                format(string, sizeof(string), "%s%s", string, GetSurnameNick(PatrolInfo[f][i][patrulOfficer][1]));
        }

        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][count], string);
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][count]);

        MdcInfo[playerid][mdcList][count] = i;

        count++;
        if(count == 18*(MdcInfo[playerid][mdcListPage]+1)) break;
    }

    if(!count)
    {
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][0], "_There are no active patrols at the moment..");
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][0]);
    }

    if(p_temp[playerid][pPatrol])
    {
        new callsignstr[32];
        format(callsignstr, sizeof(callsignstr), "_%s", PatrolInfo[1][p_temp[playerid][pPatrol]-1][patrulName]);
        PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][2], callsignstr);
    }
    else PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][2], "_Unit not set..");

    new strpage[7];
    format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if(GetPVarInt(playerid, #MAX_MDC_PAGE) < 2) {
        for(new k = 0; k < 3; k++)
            PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    } else {
        for(new k = 0; k < 3; k++)
            PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    }
    return 1;
}

MDC_ShowMembersMenu(playerid)
{
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][0], "List of all members:");
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][1], ">> Change status");

    for(new j = 0; j < 18; j++) PlayerTextDrawHide(playerid, MDC_TD_MENU[playerid][j]);
    for(new j = 0; j < 18; j++) MdcInfo[playerid][mdcList][j] = 0;

    new string[128], count, status[22], listStatus[20], mainstatus[128], pageCount;
    format(mainstatus, sizeof(mainstatus), "%s~n~~n~~r~LEGEND:~l~~n~- 10-8 (DUTY)~n~- 10-7 (OFF DUTY)~n~- CODE 7 (LUNCH)", status);
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][2], mainstatus);

    foreach(new i : Player) {
        if(!p_info[i][loggedIn] || p_info[i][member] != p_info[playerid][member]) continue;
        if(pageCount++ < 18*(MdcInfo[playerid][mdcListPage])) continue;

        switch(p_temp[i][StatusOnDuty])
        {
            case 0: format(status, sizeof(status), "__10-7 ~r~(OFF DUTY)"), format(listStatus, sizeof(listStatus), "~r~OFF DUTY");
            case 1: format(status, sizeof(status), "__10-8 ~g~(DUTY)"), format(listStatus, sizeof(listStatus), "~g~DUTY");
            case 2: format(status, sizeof(status), "__CODE 7 ~y~(LUNCH)"), format(listStatus, sizeof(listStatus), "~y~LUNCH");
        }

        format(string, sizeof(string), "%i._~l~[%s~l~] ~b~%s", count+1, listStatus, GetSurnameNick(i));
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][count], string);
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][count]);

        MdcInfo[playerid][mdcList][count] = i;
        count++;
        if(count == 18*(MdcInfo[playerid][mdcListPage]+1)) break;
    }

    if(!count)
    {
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][0], "_Page loading error..");
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][0]);
    }

    new strpage[7];
    format(strpage, sizeof(strpage), "%i/%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if(GetPVarInt(playerid, #MAX_MDC_PAGE) < 2)
        for(new k = 0; k < 3; k++)
            PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    else
        for(new k = 0; k < 3; k++)
            PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);

    return 1;
}

CountPlayerRecordsID(userid)
{
    new query[128], count;
    mysql_format(con_bd, query, sizeof(query), "SELECT COUNT(id) AS total FROM `criminalrecords` WHERE `userid` = %d", userid);
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

this::MDC_MAP(playerid)
{
    if(!cache_num_rows())
        return 1;
    new
        Float:map_kY = -0.04795376,
        Float:map_kX = 0.0469,

        Float:map_sX = 333.999420,
        Float:map_sY = 295.181152,

        Float:corX, Float:corY,
        count = 0,
        strhouse[80];

    new player_db_id, area;
    cache_get_value_name_int(0, "id", player_db_id);

    for(new i = totalhouses-1; i != -1; i--)
    {
        if(h_info[i][h_mysql_id] == INVALID_MYSQL_ID) continue;
        if(h_info[i][h_delete] == 1) continue;
        if( h_info[i][h_user_id] != player_db_id &&
            h_info[i][h_r_user_id][0] != player_db_id &&
            h_info[i][h_r_user_id][1] != player_db_id &&
            h_info[i][h_r_user_id][2] != player_db_id &&
            h_info[i][h_r_user_id][3] != player_db_id) continue;

        if(count > 5) break;
        if(count == 0)
        {
            area = GetZonaName(h_info[i][h_enter][0], h_info[i][h_enter][1]);
            format(strhouse, sizeof(strhouse), "%s %d~n~San Andreas", gSAZones[area][SAZONE_NAME], i);
            PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][4], strhouse);

            if(h_info[i][h_enter][0] > 0)
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit2");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit4");
                map_kX = 0.0469;
                map_sX = 333.999420;

                corX = h_info[i][h_enter][0] * map_kX + map_sX;
                corY = h_info[i][h_enter][1] * map_kY + map_sY;
            }
            else
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit1");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit3");
                map_kX = -0.0469;
                map_sX = 480.066314;

                corX = map_sX - h_info[i][h_enter][0] * map_kX;
                corY = h_info[i][h_enter][1] * map_kY + map_sY;
            }
            PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][2]);
            MDC_ADDRESS[playerid][2] = PlayerText:INVALID_TEXT_DRAW;

            MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, corX, corY, "hud:radar_propertyG");
            PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 5.000000, 6.000000);
            PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
            PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][2]);

            area = GetZonaName(h_info[i][h_enter][0], h_info[i][h_enter][1]);
            format(strhouse, sizeof(strhouse), "- %.33s %d", gSAZones[area][SAZONE_NAME], i);
            PlayerTextDrawSetString(playerid, MDC_OTHER_ADDRESS[playerid][count+1], strhouse);
        }
        else
        {
            if(count == 1) PlayerTextDrawShow(playerid, MDC_OTHER_ADDRESS[playerid][1]);
            area = GetZonaName(h_info[i][h_enter][0], h_info[i][h_enter][1]);
            format(strhouse, sizeof(strhouse), "- %.33s %d", gSAZones[area][SAZONE_NAME], i);
            PlayerTextDrawSetString(playerid, MDC_OTHER_ADDRESS[playerid][count+1], strhouse);
            PlayerTextDrawShow(playerid, MDC_OTHER_ADDRESS[playerid][count+1]);
        }
        MdcInfo[playerid][mdcList][count] = i;
        count++;
    }
    if(count > 1) PlayerTextDrawShow(playerid, MDC_OTHER_ADDRESS[playerid][0]);

    MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
    Update_MDC(playerid, PAGE_MAP);
    return 1;
}

MEMBERS_MAP(playerid, userid)
{
    if(!p_info[userid][loggedIn]) return MDC_PAGE(playerid, PAGE_MAIN);

    new Float:map_kY = -0.04795376,
        Float:map_kX = 0.0469,

        Float:map_sX = 333.999420,
        Float:map_sY = 295.181152,

        Float:corX, Float:corY,

        Float:posX,
        Float:posY,
        Float:posZ,

        string[64];
    GetPlayerPos(userid, posX, posY, posZ);

    if(posX > 0)
    {
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit2");
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit4");
        map_kX = 0.0469;
        map_sX = 333.999420;

        corX = posX * map_kX + map_sX;
        corY = posY * map_kY + map_sY;
    }
    else
    {
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit1");
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit3");
        map_kX = -0.0469;
        map_sX = 480.066314;

        corX = map_sX - posX * map_kX;
        corY = posY * map_kY + map_sY;
    }
    PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][2]);
    MDC_ADDRESS[playerid][2] = PlayerText:INVALID_TEXT_DRAW;

    MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, corX, corY, "hud:radar_gangN");
    PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 7.000000, 8.000000);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
    PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][2]);

    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], GetPlayerSkin(userid));
    PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][1]);

    PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][0]);

    format(string, sizeof(string), "%s__~b~__Oficer(%d)", GetSurnameNick(userid), p_info[userid][rang]);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][3], string);
    PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][3]);

    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][4], ">> CHECK BODY-CAM G-0");
    PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][4]);

    MdcInfo[playerid][mdcBack] = PAGE_MEMBERS;
    Update_MDC(playerid, PAGE_MEMBERS_MAP);

    p_temp[playerid][MDC_BODYCAM] = userid;
    return 1;
}

this::MDC_LICENSES_LIST(playerid)
{
    if(!cache_num_rows()) return SendError(playerid, "У игрока нет лицензий.");
    CancelSelectTextDraw(playerid);
    STRING_GLOBAL[0] = EOS;
    STRING_GLOBAL = "[#] Лицензия\tСтатус\tПредупреждения\n";
    new lic_id, Lics[LIC_ALL], Lic_Warns[LIC_ALL];

    new data[24];
    cache_get_value_name(0, "Lic", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", Lics);

    cache_get_value_name(0, "Lic_Warn", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", Lic_Warns);
    for(new i; i < LIC_ALL; i++)
    {
        lic_id = type_license[i];
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%d\n", STRING_GLOBAL, i+1, name_license[i],
            !Lics[lic_id] ? "{"#cLIGHTRED"}Нет": Lics[lic_id] == 1 ? "{"#cGREEN"}Активная":"{"#cBLUE"}Черный список",
            Lic_Warns[lic_id]);
    }
    ShowPlayerDialog(playerid, D_MDC_LICENSES, DIALOG_STYLE_TABLIST_HEADERS, ""I"Меню выбора", STRING_GLOBAL, "Выбрать", "Назад" );
    /*
    MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
    Update_MDC(playerid, PAGE_LIC);
    */
    return 1;
}
this::MDC_LICENSES_INFO(playerid)
{
    SelectTextDraw(playerid, 255);
    if(!cache_num_rows())
        return 1;

    new player_db_id = GetPVarInt(playerid, #MDC_ID),
        user_online,
        nickname[MAX_PLAYER_NAME],
        type_id = p_temp[playerid][p_listitem][0],
        lic_id = type_license[p_temp[playerid][p_listitem_int]],
        lic_id_name = p_temp[playerid][p_listitem_int],
        targetid = GetPlayerUserID(player_db_id),
        data[24];

    if(targetid != INVALID_PLAYER_ID) user_online = 1;
    else user_online = 0;
    cache_get_value_name(0, "name", nickname);

    new Lics[LIC_ALL], Lic_Warns[LIC_ALL];
    cache_get_value_name(0, "Lic", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", Lics);
    cache_get_value_name(0, "Lic_Warn", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", Lic_Warns);

    if(!Lics[lic_id]) return SendError(playerid, "У %s нет лицензии на %s.", nickname, name_license[lic_id_name]);
    switch(type_id)
    {
        case 0: //АННУЛИРОВАЛ
        {
            if(user_online)
            {
                SendAccess(targetid, "%s %s аннулировал Вашу лицензию на %s.", GetPlayerFractionRangName(playerid), get_name(playerid), name_license[lic_id_name]);
                p_info[targetid][Lic][lic_id] =
                p_info[targetid][Lic_Warn][lic_id] =
                p_info[targetid][Lic_Time][lic_id] = 0;
            }
            else
            {
                Lics[lic_id] =
                Lic_Warns[lic_id] = 0;
            }
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] аннулировал %s лицензию на %s.", get_name(playerid), playerid, nickname, name_license[lic_id_name]);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

            SendAccess(playerid, "Вы аннулировали %s лицензию на %s.", nickname, name_license[lic_id_name]);
        }
        case 1: //ВЫДАТЬ ПРЕДУПРЕЖДЕНИЕ
        {
            SendAccess(playerid, "Вы выписали предупреждение %s на %s.", nickname, name_license[lic_id_name]);
            if(++Lic_Warns[lic_id] < 3)
            {
                if(user_online)
                {
                    p_info[targetid][Lic_Warn][lic_id] = Lic_Warns[lic_id];
                    SendAccess(targetid, "%s %s выписал Вам предупреждение на лицензию %s.", GetPlayerFractionRangName(playerid), get_name(playerid), name_license[lic_id_name]);
                }

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] выписал предупреждение %s на %s.", get_name(playerid), playerid, nickname, name_license[lic_id_name]);
                SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
            }
            else
            {
                SendInfo(playerid, "Поскольку на %s %s было 3 предупреждения, оно аннулировано автоматически.", name_license[lic_id_name], nickname);
                if(user_online)
                {
                    SendAccess(targetid, "%s %s аннулировал Вашу лицензию на %s.", GetPlayerFractionRangName(playerid), get_name(playerid), name_license[lic_id_name]);
                    p_info[targetid][Lic][lic_id] =
                    p_info[targetid][Lic_Warn][lic_id] =
                    p_info[targetid][Lic_Time][lic_id] = 0;
                }
                else
                {
                    Lics[lic_id] =
                    Lic_Warns[lic_id] = 0;
                }
                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] аннулировал %s лицензию на %s по причине 3/3 предупреждений.", get_name(playerid), playerid, nickname, name_license[lic_id_name]);
                SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);

                SendAccess(playerid, "Вы аннулировали %s лицензию на %s.", nickname, name_license[lic_id_name]);
            }
        }
        case 2:
        {
            Lic_Warns[lic_id]--;
            if(Lic_Warns[lic_id] < 0) return SendError(playerid, "Предупреждений не найдено.");
            SendAccess(playerid, "Вы сняли предупреждение %s на %s.", nickname, name_license[lic_id_name]);
            if(user_online)
            {
                SendAccess(targetid, "%s %s снял Вам предупреждение на лицензию %s.", GetPlayerFractionRangName(playerid), get_name(playerid), name_license[lic_id_name]);
                p_info[targetid][Lic_Warn][lic_id] = Lic_Warns[lic_id];
            }
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] снял предупреждение %s с лицензии на %s.", get_name(playerid), playerid, nickname, name_license[lic_id_name]);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
        }
        case 3:
        {
            return SendError(playerid, "Функция временно не доступна.");
            /*
            if(Lics[lic_id] == 2) return SendError(playerid, "%s уже в черным списком.", nickname);
            Lics[lic_id] = 2;
            Lic_Warns[lic_id] = 0;
            if(user_online)
            {
                SendAccess(targetid, "%s %s внёс Вас в черный список владельцев лицензии %s.", GetPlayerFractionRangName(playerid), get_name(playerid), name_license[lic_id_name]);
                p_info[targetid][Lic][lic_id] = Lics[lic_id];
                p_info[targetid][Lic_Warn][lic_id] = Lic_Warns[lic_id];
                p_info[targetid][Lic_Time][lic_id] = 0;
            }
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] внёс %s в черный список владельцев лицензии %s.", get_name(playerid), playerid, nickname, name_license[lic_id_name]);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
            SendAccess(playerid, "Вы внёсли %s в черный список владельцев лицензии %s.", nickname, name_license[lic_id_name]);
            */
        }
        case 4:
        {
            if(Lics[lic_id] != 2) return SendError(playerid, "%s не в черным списке.", nickname);
            Lics[lic_id] =
            Lic_Warns[lic_id] = 0;
            if(user_online)
            {
                SendAccess(targetid, "%s %s убрал Вас из черного списка владельцев лицензии %s.", GetPlayerFractionRangName(playerid), get_name(playerid), name_license[lic_id_name]);
                p_info[targetid][Lic][lic_id] = Lics[lic_id];
                p_info[targetid][Lic_Warn][lic_id] = Lic_Warns[lic_id];
                p_info[targetid][Lic_Time][lic_id] = 0;
            }
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "[F] %s[%d] убрал %s из черного списка владельцев лицензии %s.", get_name(playerid), playerid, nickname, name_license[lic_id_name]);
            SendFractionMessage(p_info[playerid][member], 0x33CC66FF, STRING_GLOBAL);
            SendAccess(playerid, "Вы убрал %s из черного списка владельцев лицензии %s.", nickname, name_license[lic_id_name]);
        }
    }
    if(!user_online)
    {
        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `Lic` = '%i|%i|%i|%i|%i|%i|%i|%i', `Lic_Warn` = '%i|%i|%i|%i|%i|%i|%i|%i' WHERE `id` = %d",
            Lics[LIC_WEAPON],       Lics[LIC_FISHING],
            Lics[LIC_CAR],          Lics[LIC_PLANE],
            Lics[LIC_BOAT],         Lics[LIC_MOTO],
            Lics[LIC_TAXI],         Lics[LIC_HUNTER],
            Lic_Warns[LIC_WEAPON],  Lic_Warns[LIC_FISHING],
            Lic_Warns[LIC_CAR],     Lic_Warns[LIC_PLANE],
            Lic_Warns[LIC_BOAT],    Lic_Warns[LIC_MOTO],
            Lic_Warns[LIC_TAXI],    Lic_Warns[LIC_HUNTER], player_db_id);
    }
    else OnPlayerUpdateLicData(targetid);
    return 1;
}

CheckTextDrawString(string[])
{
    new l = strlen(string), c;
    for(new i; i < l; i++)
    {
        switch(string[i])
        {
            case 'A'..'Z', 'a'..'z', '0'..'9', '-': c++;
        }
    }
    if(l == c) return 0;
    return 1;
}

MDC_CountCCTVS()
{
    new query[64], count;
    mysql_format(con_bd, query, sizeof(query), "SELECT COUNT(id) AS total FROM `cctvs`");
    new Cache:cache = mysql_query(con_bd, query);
    cache_get_value_name_int(0, "total", count);
    cache_delete(cache);
    return count;
}

MDC_CountRoster()
{
    new count = 0;
    for(new i = 0; i != MAX_PATROL; i++)
    {
        if(!PatrolInfo[1][i][patrulExists]) continue;
        count++;
    }
    return count;
}


APB_Menu(playerid)
{
    p_temp[playerid][list_page] = 0;
    ShowPlayerDialog(playerid, D_APB_MENU, DIALOG_STYLE_LIST, ""I"APB", ""I"[1]"W" Просмотр всех APB\n"I"[2]"W" Создать новую APB\n"I"[3]"W" Поиск по имени\n"I"[4]"W" Поиск по описанию", "Далее", "Выйти");
    return 1;
}

APB_List(playerid)
{
    new maxpages = floatround(MAX_APBS/MAX_DIALOG_LIST,floatround_ceil);
    if(p_temp[playerid][list_page] < 0 || (maxpages < p_temp[playerid][list_page]+1)) return 1;

    new start_itter = MAX_DIALOG_LIST * p_temp[playerid][list_page],
        end_itter = (maxpages == p_temp[playerid][list_page]+1) ? (MAX_APBS) : (start_itter+MAX_DIALOG_LIST+1),
        count;

    STRING_GLOBAL = "[#] Дата\tОфицер\tПодозреваемый\tОписание\n";
    if(p_temp[playerid][list_page]) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s{bccd32}Предыдущая страница{FFFFFF}\t-\t-\t-\n", STRING_GLOBAL);
    for(new i = start_itter; i < end_itter; i++)
    {
        if(!ApbInfo[i][apbOn]) continue;
        if(count == MAX_DIALOG_LIST) {
            strcat(STRING_GLOBAL, "{bccd32}Следующая страница\t-\t-\t-");
            break;
        } else {
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%s\t%s\t%s\t%.30s\n", STRING_GLOBAL, i,
                ApbInfo[i][apbDate], ApbInfo[i][apbOfficer], ApbInfo[i][apbSuspect], ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 30)?(".."):(""));
            count++;
        }
    }
    if(!count) return ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_LIST, ""I"APB", ""W"Нет APB для отображения...", ">>>", "");
    ShowPlayerDialog(playerid, D_APB_LIST_ACTIONS, DIALOG_STYLE_TABLIST_HEADERS, ""I"APB", STRING_GLOBAL, ">>>", "Назад");
    return 1;
}


this::ShowPlayersRecords(playerid, back)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "У игрока нет криминальной истории.");
    new arrest_status, status[24];
    STRING_GLOBAL = "[#] Офицер\tСтатус\tОписание\tДата";
    if(p_temp[playerid][list_type]) f(STRING_GLOBAL, "%s\n{bccd32}<<{FFFFFF}\t-\t-\t-", STRING_GLOBAL);
    new reason[12], date[24], officername[MAX_PLAYER_NAME];
    if(!back)
    {
        for(new i; i < rows; i++)
        {
            cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][i]);
            cache_get_value_name(i, "charge", reason);
            cache_get_value_name_int(i, "arrest", arrest_status);
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "officer", officername);

            if(!arrest_status) format(status, sizeof(status), "{c5c5c5}Обвинение");
            else format(status, sizeof(status), "{ff0000}Арестован");

            f(STRING_GLOBAL, "%s\n"I"[%d]"W" %s\t%s\t%.30s...\t%s", STRING_GLOBAL, i+1+p_temp[playerid][list_type]*MAX_TICKETS,
                officername, status, reason, date);
        }
    }
    else
    {
        for(new i = rows-1; i >= 0; i--)
        {
            cache_get_value_name_int(i, "id", p_temp[playerid][p_listitem][rows-1-i]);
            cache_get_value_name(i, "charge", reason);
            cache_get_value_name_int(i, "arrest", arrest_status);
            cache_get_value_name(i, "date", date);
            cache_get_value_name(i, "officer", officername);

            if(!arrest_status) format(status, sizeof(status), "{c5c5c5}Обвинение");
            else format(status, sizeof(status), "{ff0000}Арестован");

            f(STRING_GLOBAL, "%s\n"I"[%d]"W" %s\t%s\t%.30s...\t%s", STRING_GLOBAL, rows-i+p_temp[playerid][list_type]*MAX_TICKETS,
                officername, status, reason, date);
        }
    }
    if(CountPlayerRecordsID(GetPVarInt(playerid, #MDC_ID)) > MAX_TICKETS*(p_temp[playerid][list_type]+1)) f(STRING_GLOBAL, "%s\n{bccd32}>>\t-\t-\t-", STRING_GLOBAL);
    ShowPlayerDialog(playerid, D_MDC_RECORD_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Криминальная история", STRING_GLOBAL, "Выбрать", "Закрыть");
    return 1;
}

this::ShowPlayerRecord(playerid)
{
    if(!cache_num_rows()) return 1;
    new date[24], officername[MAX_PLAYER_NAME], ownername[MAX_PLAYER_NAME],
        player_db_id, reason[64], arrest_status, status[24], player_member;

    cache_get_value_name_int(0, "id", player_db_id);
    cache_get_value_name_int(0, "faction", player_member);
    cache_get_value_name_int(0, "arrest", arrest_status);
    cache_get_value_name(0, "ownername", ownername);
    cache_get_value_name(0, "officer", officername);
    cache_get_value_name(0, "date", date);
    cache_get_value_name(0, "charge", reason);

    if(!arrest_status) format(status, sizeof(status), "{c5c5c5}Обвинение");
    else format(status, sizeof(status), "{ff0000}Арестован");

    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        ""W"ID:          "I"#%i\n\
        "W"Обвиняемый:   "I"%s\n\
        "W"Офицер:       "I"%s(%s)\n\n\
        "W"Дата:         "I"%s\n\
        "W"Cтатус:       "I"%s\n\n\
        "W"Описание:\n\
        "W"- %s",
        199999+player_db_id, ownername, officername,
        GetFractionName(player_member), date, status, reason);
    ShowPlayerDialog(playerid, D_MDC_RECORD_INFO, DIALOG_STYLE_MSGBOX, ""I"Поиск", STRING_GLOBAL, "Понял", "");
    return 1;
}
