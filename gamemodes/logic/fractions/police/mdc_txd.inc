    new Float: x, Float: y, Float: d;

    MDC_UI[playerid][0] = CreatePlayerTextDraw(playerid, 153.383316, 135.783706, "display");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][0], 0.000000, 33.833335);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][0], 482.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][0], -1061109505);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][0], 0);

    MDC_UI[playerid][1] = CreatePlayerTextDraw(playerid, 154.883392, 137.129501, "header-display");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][1], 0.000000, 1.416666);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][1], 480.799987, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][1], fraction_color[p_info[playerid][member]]); //GREEN
    //PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][1], 8388863); //GREEN
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][1], 0);

    MDC_UI[playerid][2] = CreatePlayerTextDraw(playerid, 189.965499, 156.437500, "MAIN SCREEN");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][2], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][2], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][2], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][2], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][2], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][2], true);

    MDC_UI[playerid][3] = CreatePlayerTextDraw(playerid, 189.965499, 172.393096, "SEARCH");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][3], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][3], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][3], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][3], true);

    MDC_UI[playerid][4] = CreatePlayerTextDraw(playerid, 189.965499, 188.467193, "EMERGENCY");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][4], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][4], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][4], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][4], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][4], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][4], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][4], true);

    MDC_UI[playerid][5] = CreatePlayerTextDraw(playerid, 189.948852, 204.422760, "MEMBERS");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][5], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][5], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][5], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][5], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][5], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][5], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][5], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][5], true);

    MDC_UI[playerid][6] = CreatePlayerTextDraw(playerid, 189.965484, 220.733901, "APB");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][6], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][6], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][6], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][6], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][6], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][6], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][6], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][6], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][6], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][6], true);

    MDC_UI[playerid][7] = CreatePlayerTextDraw(playerid, 189.848831, 253.346023, "ROSTER");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][7], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][7], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][7], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][7], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][7], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][7], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][7], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][7], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][7], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][7], true);

    MDC_UI[playerid][8] = CreatePlayerTextDraw(playerid, 189.865478, 269.675598, "CCTV");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][8], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][8], 10.000000, 66.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][8], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][8], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][8], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][8], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][8], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][8], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][8], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][8], true);

    MDC_UI[playerid][9] = CreatePlayerTextDraw(playerid, 189.866012, 414.188751, "MDC V2.2~n~AUTORISATION AS:~n~Jewking Test");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][9], 0.162082, 0.796296);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][9], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][9], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][9], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][9], 0);

    MDC_UI[playerid][10] = CreatePlayerTextDraw(playerid, 228.099792, 154.585281, "line"); // ÐÀÇÄÅËÈÒÅËÜ ÌÅÍÞ È ÎÑÍÎÂÍÎÃÎ ÝÊÐÀÍÀ
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][10], 0.000000, 31.291673);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][10], 226.799926, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][10], 1);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][10], -1);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][10], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][10], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][10], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][10], 0);

    MDC_UI[playerid][11] = CreatePlayerTextDraw(playerid, 167.499984, 138.529678,"Red County Sheriff'S Department MDC >> Main Screen");
                                                                                //"RED COUNTY SHERIFF'S DEPARTMENT MDC >> MAIN SCREEN"); //ÒÈÒÓË MDC
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][11], 0.213330, 1.050369);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][11], 1);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][11], -1061109505);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][11], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][11], 0);

    MDC_UI[playerid][12] = CreatePlayerTextDraw(playerid, 155.300003, 136.592605, "]");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][12], 0.297500, 1.454815);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][12], 1);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][12], -1061109505);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][12], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][12], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][12], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][12], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][12], 0);

    MDC_UI[playerid][13] = CreatePlayerTextDraw(playerid, 447.182891, 137.066452, "_-_");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][13], 0.460832, 1.423702);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][13], 10.000000, 15.000000);//0.969999, 15.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][13], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][13], -1);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][13], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][13], 0x3e80f2FF);//0x9189EFFF);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][13], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][13], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][13], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][13], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][13], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][13], true);

    MDC_UI[playerid][14] = CreatePlayerTextDraw(playerid, 468.532928, 137.184951, "_X_");
    PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][14], 0.227082, 1.402961);
    PlayerTextDrawTextSize(playerid, MDC_UI[playerid][14], 10.000000, 15.000000);//0.969999, 15.000000);
    PlayerTextDrawAlignment(playerid, MDC_UI[playerid][14], 2);
    PlayerTextDrawColor(playerid, MDC_UI[playerid][14], -1);
    PlayerTextDrawUseBox(playerid, MDC_UI[playerid][14], 1);
    PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][14], -1523963137);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][14], 0);
    PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][14], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][14], 255);
    PlayerTextDrawFont(playerid, MDC_UI[playerid][14], 2);
    PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][14], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][14], true);


    for(new i = 0; i < 15; i++) PlayerTextDrawShow(playerid, MDC_UI[playerid][i]);
    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- MAINMENU -------------------------

    */

    MDC_MAINSCREEN[playerid][0] = CreatePlayerTextDraw(playerid, 229.583328, 156.070693, ""); // ÀÂÀÒÀÐ ÈÃÐÎÊÀ
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, MDC_MAINSCREEN[playerid][0], 251.000000, 258.000000);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][0], -1061109505);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, MDC_MAINSCREEN[playerid][0], 282);
    PlayerTextDrawSetPreviewRot(playerid, MDC_MAINSCREEN[playerid][0], 0.000000, 0.000000, 0.000000, 0.850000);

    MDC_MAINSCREEN[playerid][1] = CreatePlayerTextDraw(playerid, 257.083435, 238.222213, "prewiew-front");
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][1], 0.000000, 21.749986);
    PlayerTextDrawTextSize(playerid, MDC_MAINSCREEN[playerid][1], 481.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, MDC_MAINSCREEN[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, MDC_MAINSCREEN[playerid][1], -1061109505);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][1], 0);

    MDC_MAINSCREEN[playerid][2] = CreatePlayerTextDraw(playerid, 355.816650, 238.333114, "Police Officer II   Jewking Test");
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][2], 0.234999, 0.972591);
    PlayerTextDrawTextSize(playerid, MDC_MAINSCREEN[playerid][2], 0.000000, 234.000000);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][2], 2);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, MDC_MAINSCREEN[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, MDC_MAINSCREEN[playerid][2], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][2], 0);

    MDC_MAINSCREEN[playerid][3] = CreatePlayerTextDraw(playerid, 239.902481, 257.407348, "MEMBERS ON DUTY:~n~ACTIVE WARRANTS:~n~ACTIVE BOLOS:");
                                                                                        //"MEMBER'S ON DUTY~n~ACTIVE WARRANTS~n~ACTIVE BOLO'S");
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][3], 0.234999, 0.972591);//0.154999, 1.081480);//0.241666, 0.988147);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][3], 1);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][3], 255);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][3], 0);

    MDC_MAINSCREEN[playerid][4] = CreatePlayerTextDraw(playerid, 332.916503, 256.888916, "0~n~0~n~0");
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][4], 0.234999, 0.972591);//0.154999, 1.081480);//0.273333, 1.019258);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][4], 1);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][4], 0x8B8A8AFF);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][4], 255);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][4], 0);

    MDC_MAINSCREEN[playerid][5] = CreatePlayerTextDraw(playerid, 366.985870, 257.925842, "CALLS LAST HOUR:~n~ARRESTS LAST HOUR:~n~FINES LAST HOUR:");
                                                                                        //"CALLS LAST HOUR~n~ARRESTS LAST HOUR~n~FINES LAST HOUR");
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][5], 0.234999, 0.972591);//0.154999, 1.081480);//0.241666, 0.988147);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][5], 1);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][5], 255);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][5], 255);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][5], 0);

    MDC_MAINSCREEN[playerid][6] = CreatePlayerTextDraw(playerid, 465.833007, 255.851867, "0~n~0~n~0");
    PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][6], 0.234999, 0.972591);//0.154999, 1.081480);//0.259166, 1.091851);
    PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][6], 2);
    PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][6], 0x8B8A8AFF);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][6], 255);
    PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][6], 2);
    PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][6], 0);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- SEARCH --------------------------

    */

    MDC_LOOKUP_SEARCH[playerid][0] = CreatePlayerTextDraw(playerid, 249.765502, 157.156112, "NAME");//249.965469, 156.956069, "ÈÌß");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][0], 10.000000, 36.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][0], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][0], true);

    MDC_LOOKUP_SEARCH[playerid][1] = CreatePlayerTextDraw(playerid, 290.482147, 157.056076, "NUMBER");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][1], 10.000000, 36.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][1], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][1], true);

    MDC_LOOKUP_SEARCH[playerid][2] = CreatePlayerTextDraw(playerid, 313.932128, 157.656158, "_____");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0.199579, 0.962221);//0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][2], 429.000000, 8.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][2], true);

    MDC_LOOKUP_SEARCH[playerid][3] = CreatePlayerTextDraw(playerid, 455.849273, 156.756057, "REFRESH");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][3], 10.000000, 44.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][3], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][3], true);

    MDC_LOOKUP_ERROR[playerid] = CreatePlayerTextDraw(playerid, 232.682266, 173.793121, "]__ERROR: FOUND NOTHING!");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_ERROR[playerid], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_ERROR[playerid], 478.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_ERROR[playerid], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_ERROR[playerid], -1);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_ERROR[playerid], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_ERROR[playerid], -2147483393);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_ERROR[playerid], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_ERROR[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_ERROR[playerid], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_ERROR[playerid], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_ERROR[playerid], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_ERROR[playerid], 0);

    MDC_ERROR_CALLS[playerid] = CreatePlayerTextDraw(playerid, 232.682266, 158.646331, "]__ERROR: FOUND NOTHING!");
    PlayerTextDrawLetterSize(playerid, MDC_ERROR_CALLS[playerid], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_ERROR_CALLS[playerid], 478.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_ERROR_CALLS[playerid], 1);
    PlayerTextDrawColor(playerid, MDC_ERROR_CALLS[playerid], 0xa7a7a7FF);
    PlayerTextDrawUseBox(playerid, MDC_ERROR_CALLS[playerid], 1);
    PlayerTextDrawBoxColor(playerid, MDC_ERROR_CALLS[playerid], 0x494949FF);
    PlayerTextDrawSetShadow(playerid, MDC_ERROR_CALLS[playerid], 0);
    PlayerTextDrawSetOutline(playerid, MDC_ERROR_CALLS[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_ERROR_CALLS[playerid], 255);
    PlayerTextDrawFont(playerid, MDC_ERROR_CALLS[playerid], 2);
    PlayerTextDrawSetProportional(playerid, MDC_ERROR_CALLS[playerid], 1);
    PlayerTextDrawSetShadow(playerid, MDC_ERROR_CALLS[playerid], 0);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- LOOKUP_PERSON --------------------

    */

    MDC_LOOKUP_AVATAR[playerid][0] = CreatePlayerTextDraw(playerid, 270.000122, 177.941299, "~n~picture~n~not~n~available~n~__");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0.400000, 1.600000);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0.000000, 77.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_AVATAR[playerid][0], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_AVATAR[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_AVATAR[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_AVATAR[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_AVATAR[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_AVATAR[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_AVATAR[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0);

    MDC_LOOKUP_AVATAR[playerid][1] = CreatePlayerTextDraw(playerid, 168.016494, 175.959106, "");    // AVATAR
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_AVATAR[playerid][1], 204.000000, 202.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_AVATAR[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_AVATAR[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_AVATAR[playerid][1], -1061109505);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_AVATAR[playerid][1], 5);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], 282);
    PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0.000000, 0.000000, 20.000000, 0.850000);

    MDC_LOOKUP_PERSON[playerid][0] = CreatePlayerTextDraw(playerid, 229.999923, 253.240768, "prewiew-front");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][0], 0.000000, 16.916669);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][0], 444.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][0], -1061109505);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][0], 0);

    MDC_LOOKUP_PERSON[playerid][1] = CreatePlayerTextDraw(playerid, 314.166656, 179.629623, "NAME:~n~NUMBER:~n~PRIORS:~n~LICENSES:~n~ADDRESS:");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][1], 0.154999, 1.081480);//0.226250, 1.008889);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][1], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][1], 0);

    MDC_LOOKUP_PERSON[playerid][2] = CreatePlayerTextDraw(playerid, 365.267486, 179.629623, "Jewking Test~n~811000~n~None~n~Driver~n~Not Available");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][2], 0.154999, 1.081480);//0.226250, 1.008889);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][2], -2139062017);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][2], 0);

    MDC_LOOKUP_PERSON[playerid][3] = CreatePlayerTextDraw(playerid, 231.632064, 259.104095, "~l~AVAILABLE FUNCTIONS:"); //>> ÁÎËÜØÅ ÍÅ Â ÐÎÇÛÑÊÅ
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][3], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][3], 356.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][3], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][3], 0x494949FF);
    //PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][3], 1);
    //PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][3], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
    //PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][3], true);

    MDC_LOOKUP_PERSON[playerid][4] = CreatePlayerTextDraw(playerid, 231.632064, 274.767272, ">> WRITE ARREST RECORD");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][4], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][4], 356.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][4], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][4], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][4], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][4], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][4], true);

    MDC_LOOKUP_PERSON[playerid][5] = CreatePlayerTextDraw(playerid, 231.632064, 291.068267, ">> MANAGE LICENSE");//WRITE ARREST RECORD
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][5], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][5], 356.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][5], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][5], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][5], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][5], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][5], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][5], true);

    MDC_LOOKUP_PERSON[playerid][6] = CreatePlayerTextDraw(playerid, 231.365325, 307.244842, ">> VIEW FINES");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][6], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][6], 355.899932, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][6], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][6], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][6], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][6], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][6], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][6], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][6], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][6], true);

    MDC_LOOKUP_PERSON[playerid][7] = CreatePlayerTextDraw(playerid, 420.048706, 259.104095, "~y~]~w~__CRIMINAL_RECORDS__~y~]");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][7], 0.154999, 1.081480);//0.202914, 1.154072);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][7], 10.000000, 120.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][7], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][7], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][7], 0x494949FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][7], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][7], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][7], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][7], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][7], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][7], true);

    MDC_LOOKUP_PERSON[playerid][8] = CreatePlayerTextDraw(playerid, 360.566833, 274.000030, "Îòñóòñòâóþò!");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][8], 0.188333, 0.905185);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][8], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][8], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][8], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][8], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][8], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][8], 0);

    MDC_LOOKUP_PERSON[playerid][9] = CreatePlayerTextDraw(playerid, 269.999969, 242.159362, "~w~]_WANTED!");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][9], 0.129166, 0.874075);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][9], 0.000000, 77.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][9], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][9], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][9], -1523963137);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][9], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][9], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][9], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][9], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][9], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][9], true);

    MDC_LOOKUP_PERSON[playerid][10] = CreatePlayerTextDraw(playerid, 314.583251, 231.270523, "] CLICK TO VIEW ALL ADDRESSES");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][10], 0.202500, 1.024446);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][10], 480.000000, 20.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][10], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][10], 255);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][10], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][10], -5963521);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][10], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][10], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][10], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][10], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][10], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][10], true);

    MDC_LOOKUP_PERSON[playerid][11] = CreatePlayerTextDraw(playerid, 293.599700, 323.755554, "~y~0~w~~n~Unpaid fines!");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][11], 0.129166, 0.874073);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][11], 0.000000, 124.140029);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][11], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][11], -1);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][11], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][11], -1523963137);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][11], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][11], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][11], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][11], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][11], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][11], true);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- LOOKUP_VEHICLE_LIST --------------

    */

    for (new i = 0; i < 4; i++)
    {
        x = 230.416564, y = 167.185256, d = (229.388870 - y)*i;
        MDC_LOOKUP_VEHICLES_LIST[playerid][4*i] = CreatePlayerTextDraw(playerid, x, y+d, "");
        PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 0.000000, 0.000000);
        PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 90.000000, 90.000000);
        PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 1);
        PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], -1);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 0);
        PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], -1061109505);
        PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 5);
        PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 0);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 0);
        PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 439);
        PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 0.000000, 0.000000, 90.000000, 0.879999);
        PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i], 1, 1);

        x = 383.933441, y = 181.444534, d = (242.540466 - y)*i;
        MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1] = CreatePlayerTextDraw(playerid, x, y+d, "SULTAN~n~1LASD1~n~Jewking Test~n~LEVEL 2~n~No");
        PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 0.154999, 1.081480);
        PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 1);
        PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 0x8B8A8AFF);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 0);
        PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 255);
        PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 2);
        PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 1);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+1], 0);

        x = 325.416625, y = 181.444534, d = (242.540466 - y)*i;
        MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2] = CreatePlayerTextDraw(playerid, x, y+d, "MODEL:~n~NUMBER:~n~OWNER:~n~INSURENCE:~n~IMPOUND:");
        PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 0.154999, 1.081480);
        PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 1);
        PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 255);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 0);
        PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 255);
        PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 2);
        PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 1);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+2], 0);

        x = 237.183029, y = 183.800094, d = (243.137298 - y)*i;
        MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3] = CreatePlayerTextDraw(playerid, x, y+d, "!");
        PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 0.179165, 0.962221);
        PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 0.000000, 9.000000);
        PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 2);
        PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], -1);
        PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 1);
        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], -1523963137);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 0);
        PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 255);
        PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 2);
        PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 1);
        PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4*i+3], 0);
    }

    x = 468.351776, y = 185.081573, d = 243.882522 - y;
    for (new i = 0; i < 4; i++)
    {
        MDC_VEH_LIST_CLICK[playerid][i] = CreatePlayerTextDraw(playerid, x, y, "_~n~_~n~_~n~>~n~_~n~_~n~_");
        PlayerTextDrawLetterSize(playerid, MDC_VEH_LIST_CLICK[playerid][i], 0.133748, 0.651109);
        PlayerTextDrawTextSize(playerid, MDC_VEH_LIST_CLICK[playerid][i], 30.000000, 12.000000);
        PlayerTextDrawAlignment(playerid, MDC_VEH_LIST_CLICK[playerid][i], 2);
        PlayerTextDrawColor(playerid, MDC_VEH_LIST_CLICK[playerid][i], 0x494949FF);//-1);
        PlayerTextDrawUseBox(playerid, MDC_VEH_LIST_CLICK[playerid][i], 1);
        PlayerTextDrawBoxColor(playerid, MDC_VEH_LIST_CLICK[playerid][i], 0xa7a7a7FF);//-2139062017);
        PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, MDC_VEH_LIST_CLICK[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_VEH_LIST_CLICK[playerid][i], 255);
        PlayerTextDrawFont(playerid, MDC_VEH_LIST_CLICK[playerid][i], 2);
        PlayerTextDrawSetProportional(playerid, MDC_VEH_LIST_CLICK[playerid][i], 1);
        PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][i], 0);
        PlayerTextDrawSetSelectable(playerid, MDC_VEH_LIST_CLICK[playerid][i], true);

        y += d;
    }

    MDC_LOOKUP_VEHICLES_ARROWS[playerid][0] = CreatePlayerTextDraw(playerid, 356.816711, 424.493133, "1_/_2");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0.228330, 0.889629);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0);

    MDC_LOOKUP_VEHICLES_ARROWS[playerid][1] = CreatePlayerTextDraw(playerid, 424.404205, 424.493133, ">>");
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 10.000000, 112.000000);
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0.228330, 0.889629);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], true);

    MDC_LOOKUP_VEHICLES_ARROWS[playerid][2] = CreatePlayerTextDraw(playerid, 289.212585, 424.493133, "<<");
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 10.000000, 113.000000);
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0.228330, 0.889629);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 2);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 255);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], true);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- LOOKUP_VEHICLE -------------------

    */

    MDC_LOOKUP_VEHICLE[playerid][0] = CreatePlayerTextDraw(playerid, 230.416564, 174.185256, "");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 90.000000, 91.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][0], -1061109505);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 5);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 439);
    PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0.000000, 0.000000, 90.000000, 0.879998);
    PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 1, 1);

    MDC_LOOKUP_VEHICLE[playerid][1] = CreatePlayerTextDraw(playerid, 383.933441, 188.444534, "SULTAN~n~1LASD1~n~Jewking Test~n~LEVEL 2~n~No");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0.154999, 1.081480);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0x8B8A8AFF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0);

    MDC_LOOKUP_VEHICLE[playerid][2] = CreatePlayerTextDraw(playerid, 325.416625, 187.925994, "MODEL:~n~NUMBERS:~n~OWNER:~n~INSURANCE:~n~IMPOUNDED:~n~PURCHASE DATE:");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0.154999, 1.081480); //0.226248, 1.008888);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0);

    MDC_LOOKUP_VEHICLE[playerid][3] = CreatePlayerTextDraw(playerid, 233.165451, 254.156051, "]__CHECK FINES__(NOT PAID FINES:__14)");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 349.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][3], -1);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][3], -5963521);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][3], true);

    MDC_LOOKUP_VEHICLE[playerid][4] = CreatePlayerTextDraw(playerid, 352.848785, 254.156051, ">> VEHICLE NOTES");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 478.938964, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][4], true);

    MDC_LOOKUP_VEHICLE[playerid][5] = CreatePlayerTextDraw(playerid, 231.932281, 173.793121, ">> DECLARE CAR IN WANTED, STATUS: ~g~NOT WANTED");
    PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 478.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 1);
    PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 255);
    PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][5], true);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- BACK -----------------------------

    */

    MDC_BACK[playerid] = CreatePlayerTextDraw(playerid, 231.499237, 156.939529, "<< RETURN BACK");
    PlayerTextDrawLetterSize(playerid, MDC_BACK[playerid], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_BACK[playerid], 334.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_BACK[playerid], 1);
    PlayerTextDrawColor(playerid, MDC_BACK[playerid], 255);
    PlayerTextDrawSetShadow(playerid, MDC_BACK[playerid], 0);
    PlayerTextDrawSetOutline(playerid, MDC_BACK[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_BACK[playerid], 255);
    PlayerTextDrawFont(playerid, MDC_BACK[playerid], 2);
    PlayerTextDrawSetProportional(playerid, MDC_BACK[playerid], 1);
    PlayerTextDrawSetShadow(playerid, MDC_BACK[playerid], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_BACK[playerid], true);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- LIST INFO ------------------------

    */

    MDC_LIST_INFO[playerid][0] = CreatePlayerTextDraw(playerid, 274.365875, 179.772827, "ID øòðàôà:~n~Íàðóøèòåëü:~n~Îøòðàôîâàë:~n~Ñóììà:~n~Äàòà:~n~Ñòàòóñ:~n~~n~Îïèñàíèå:");
    PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][0], 0.154999, 1.081480);
    PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][0], 3);
    PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][0], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][0], 0);

    MDC_LIST_INFO[playerid][1] = CreatePlayerTextDraw(playerid, 282.399841, 179.642364, "#1012441~n~Jewking_Test~n~Rey_Test~n~$500~n~17/02/2019, 16:30:25~n~~r~NOT PAID");
    PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][1], 0.183748, 1.081479);
    PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][1], -2139062017);
    PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][1], 0);

    MDC_LIST_INFO[playerid][2] = CreatePlayerTextDraw(playerid, 243.232818, 258.457458, "- Parking in some place that was the bad. It's wrong place for parking but owner of the vehicle don't think about it.");
    PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][2], 0.183748, 1.081479);
    PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][2], -2139062017);
    PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][2], 0);

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- MAP  -----------------------------

    */

    MDC_ADDRESS[playerid][0] = CreatePlayerTextDraw(playerid, 336.200256, 154.977050, "samaps:gtasamapbit2"); //up map
    PlayerTextDrawLetterSize(playerid, MDC_ADDRESS[playerid][0], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][0], 146.000000, 143.000000);
    PlayerTextDrawAlignment(playerid, MDC_ADDRESS[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_ADDRESS[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_ADDRESS[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_ADDRESS[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][0], 4);
    PlayerTextDrawSetProportional(playerid, MDC_ADDRESS[playerid][0], 0);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][0], 0);

    MDC_ADDRESS[playerid][1] = CreatePlayerTextDraw(playerid, 336.133544, 297.854339, "samaps:gtasamapbit4");
    PlayerTextDrawLetterSize(playerid, MDC_ADDRESS[playerid][1], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][1], 146.000000, 143.000000);
    PlayerTextDrawAlignment(playerid, MDC_ADDRESS[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_ADDRESS[playerid][1], -1);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_ADDRESS[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_ADDRESS[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][1], 4);
    PlayerTextDrawSetProportional(playerid, MDC_ADDRESS[playerid][1], 0);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][1], 0);

    MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, 468.915710, 295.181152, "hud:radar_propertyG");
    PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 5.000000, 6.000000);
    PlayerTextDrawLetterSize(playerid, MDC_ADDRESS[playerid][2], 0.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_ADDRESS[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_ADDRESS[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_ADDRESS[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_ADDRESS[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, MDC_ADDRESS[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][2], 0);

    MDC_ADDRESS[playerid][3] = CreatePlayerTextDraw(playerid, 234.365844, 176.143203, "- SELECT ADDRESS:");
    PlayerTextDrawLetterSize(playerid, MDC_ADDRESS[playerid][3], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][3], 328.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_ADDRESS[playerid][3], 1);
    PlayerTextDrawColor(playerid, MDC_ADDRESS[playerid][3], 255);
    PlayerTextDrawUseBox(playerid, MDC_ADDRESS[playerid][3], 1);
    PlayerTextDrawBoxColor(playerid, MDC_ADDRESS[playerid][3], -1448499201);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_ADDRESS[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_ADDRESS[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, MDC_ADDRESS[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][3], 0);

    MDC_ADDRESS[playerid][4] = CreatePlayerTextDraw(playerid, 237.299301, 189.624694, "411, LITTLE DRIVE 12/24, PALOMINO CREEK, SAN ANDREAS");
    PlayerTextDrawLetterSize(playerid, MDC_ADDRESS[playerid][4], 0.154999, 1.081480);
    PlayerTextDrawAlignment(playerid, MDC_ADDRESS[playerid][4], 1);
    PlayerTextDrawColor(playerid, MDC_ADDRESS[playerid][4], 1229539839);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MDC_ADDRESS[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_ADDRESS[playerid][4], 255);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][4], 2);
    PlayerTextDrawSetProportional(playerid, MDC_ADDRESS[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MDC_ADDRESS[playerid][4], 0);

    MDC_OTHER_ADDRESS[playerid][0] = CreatePlayerTextDraw(playerid, 234.265838, 224.827682, "- OTHER ADDRESSES:");
    PlayerTextDrawLetterSize(playerid, MDC_OTHER_ADDRESS[playerid][0], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_OTHER_ADDRESS[playerid][0], 328.100006, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_OTHER_ADDRESS[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_OTHER_ADDRESS[playerid][0], 255);
    PlayerTextDrawUseBox(playerid, MDC_OTHER_ADDRESS[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_OTHER_ADDRESS[playerid][0], -1448499201);
    PlayerTextDrawSetShadow(playerid, MDC_OTHER_ADDRESS[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_OTHER_ADDRESS[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_OTHER_ADDRESS[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_OTHER_ADDRESS[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, MDC_OTHER_ADDRESS[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_OTHER_ADDRESS[playerid][0], 0);

    x = 234.365844, y = 240.447128, d = 254.748001 - y;
    for (new i = 1; i < 6; i++)
    {
        MDC_OTHER_ADDRESS[playerid][i] = CreatePlayerTextDraw(playerid, x, y, "> 412, LITTLE DRIVE 12,24 ..");
        PlayerTextDrawLetterSize(playerid, MDC_OTHER_ADDRESS[playerid][i], 0.154999, 1.081480);
        PlayerTextDrawTextSize(playerid, MDC_OTHER_ADDRESS[playerid][i], 328.000000, 10.000000);
        PlayerTextDrawAlignment(playerid, MDC_OTHER_ADDRESS[playerid][i], 1);
        PlayerTextDrawColor(playerid, MDC_OTHER_ADDRESS[playerid][i], 255);
        PlayerTextDrawUseBox(playerid, MDC_OTHER_ADDRESS[playerid][i], 1);
        PlayerTextDrawBoxColor(playerid, MDC_OTHER_ADDRESS[playerid][i], -1);
        PlayerTextDrawSetShadow(playerid, MDC_OTHER_ADDRESS[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, MDC_OTHER_ADDRESS[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_OTHER_ADDRESS[playerid][i], 255);
        PlayerTextDrawFont(playerid, MDC_OTHER_ADDRESS[playerid][i], 2);
        PlayerTextDrawSetProportional(playerid, MDC_OTHER_ADDRESS[playerid][i], 1);
        PlayerTextDrawSetShadow(playerid, MDC_OTHER_ADDRESS[playerid][i], 0);
        PlayerTextDrawSetSelectable(playerid, MDC_OTHER_ADDRESS[playerid][i], true);

        y += d;
    }

    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- LIST -----------------------------

    */

    x = 232.799331, y = 172.383117, d = 185.783935 - y;
    for (new i = 0; i < 16; i++)
    {
        MDC_LIST[playerid][i] = CreatePlayerTextDraw(playerid, x, y, "list");
        PlayerTextDrawLetterSize(playerid, MDC_LIST[playerid][i], 0.154999, 1.081480);
        PlayerTextDrawTextSize(playerid, MDC_LIST[playerid][i], 479.100006, 9.900000);
        PlayerTextDrawAlignment(playerid, MDC_LIST[playerid][i], 1);
        PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], -1);
        PlayerTextDrawUseBox(playerid, MDC_LIST[playerid][i], 1);
        PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], -1523963137);
        PlayerTextDrawSetShadow(playerid, MDC_LIST[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, MDC_LIST[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_LIST[playerid][i], 255);
        PlayerTextDrawFont(playerid, MDC_LIST[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, MDC_LIST[playerid][i], 1);
        PlayerTextDrawSetShadow(playerid, MDC_LIST[playerid][i], 0);
        PlayerTextDrawSetSelectable(playerid, MDC_LIST[playerid][i], true);

        y += d;
    }

    /*

        ============================= MDC- =============================
        ============================= ROSTER ==========================

    */

    x = 232.799331, y = 171.983093, d = 185.383911 - y;
    for (new i = 0; i < MAX_TD_MENU_SIZE; i++)
    {
        MDC_TD_MENU[playerid][i] = CreatePlayerTextDraw(playerid, x, y, "list");
        PlayerTextDrawLetterSize(playerid, MDC_TD_MENU[playerid][i], 0.154999, 1.081480);
        PlayerTextDrawTextSize(playerid, MDC_TD_MENU[playerid][i], 408.000000, 10.000000);
        PlayerTextDrawAlignment(playerid, MDC_TD_MENU[playerid][i], 1);
        PlayerTextDrawColor(playerid, MDC_TD_MENU[playerid][i], 0x494949FF);
        PlayerTextDrawUseBox(playerid, MDC_TD_MENU[playerid][i], 1);
        PlayerTextDrawBoxColor(playerid, MDC_TD_MENU[playerid][i], 0xa7a7a7FF);
        PlayerTextDrawSetShadow(playerid, MDC_TD_MENU[playerid][i], 0);
        PlayerTextDrawSetOutline(playerid, MDC_TD_MENU[playerid][i], 0);
        PlayerTextDrawBackgroundColor(playerid, MDC_TD_MENU[playerid][i], 255);
        PlayerTextDrawFont(playerid, MDC_TD_MENU[playerid][i], 1);
        PlayerTextDrawSetProportional(playerid, MDC_TD_MENU[playerid][i], 1);
        PlayerTextDrawSetShadow(playerid, MDC_TD_MENU[playerid][i], 0);
        PlayerTextDrawSetSelectable(playerid, MDC_TD_MENU[playerid][i], true);

        y += d;
    }

    MDC_TD_LEFT_PANEL[playerid][0] = CreatePlayerTextDraw(playerid, 232.682266, 158.646331, "List of active units:");
    PlayerTextDrawLetterSize(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_TD_LEFT_PANEL[playerid][0], 408.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_TD_LEFT_PANEL[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0xa7a7a7FF);
    PlayerTextDrawUseBox(playerid, MDC_TD_LEFT_PANEL[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0x494949FF);
    PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_TD_LEFT_PANEL[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_TD_LEFT_PANEL[playerid][0], 2);
    PlayerTextDrawSetProportional(playerid, MDC_TD_LEFT_PANEL[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0);

    MDC_TD_LEFT_PANEL[playerid][1] = CreatePlayerTextDraw(playerid, 413.582427, 158.543823, "Change callsign");
    PlayerTextDrawLetterSize(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_TD_LEFT_PANEL[playerid][1], 481.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_TD_LEFT_PANEL[playerid][1], 1);
    PlayerTextDrawColor(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0xa7a7a7FF);
    PlayerTextDrawUseBox(playerid, MDC_TD_LEFT_PANEL[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0x494949FF);
    PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_TD_LEFT_PANEL[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_TD_LEFT_PANEL[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, MDC_TD_LEFT_PANEL[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_TD_LEFT_PANEL[playerid][1], true);

    MDC_TD_LEFT_PANEL[playerid][2] = CreatePlayerTextDraw(playerid, 413.582427, 172.144653, "LINCOLN-1");
    PlayerTextDrawLetterSize(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_TD_LEFT_PANEL[playerid][2], 481.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_TD_LEFT_PANEL[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_TD_LEFT_PANEL[playerid][2], 1);
    PlayerTextDrawBoxColor(playerid, MDC_TD_LEFT_PANEL[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_TD_LEFT_PANEL[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_TD_LEFT_PANEL[playerid][2], 2);
    PlayerTextDrawSetProportional(playerid, MDC_TD_LEFT_PANEL[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0);



    /*

        ----------------------------- MDC- -----------------------------
        ----------------------------- MENU INFO ------------------------

    */


