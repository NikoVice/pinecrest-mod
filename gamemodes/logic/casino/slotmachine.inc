#define MAX_SLOT_MACHINES           20

enum SM_DATA
{
    sm_Objects[4],
    Float:sm_Pos[4], //X Y Z RZ
    sm_objStop, //кол-во объектов, которые остановлены
    sm_comb, //выигрышная комбинация
    sm_userID,
    sm_bet,
    sm_looser //TEMP
};
new SlotMachine[MAX_SLOT_MACHINES][SM_DATA];
new totalsmachines;

new PlayerText: SlotMScoreTD[MAX_PLAYERS];

new Float: swiftData[20][2] = {
    {0.0000, 0.0000},  //0
    {0.0000, -0.0016}, //1
    {0.0044, -0.0056}, //2
    {0.0119, -0.0056}, //3
    {0.0174, -0.0056}, //4
    {0.0214, -0.0026}, //5
    {0.0244, 0.0021},  //6
    {0.0264, 0.0059},  //7
    {0.0264, 0.0099},  //8
    {0.0264, 0.0146},  //9
    {0.0234, 0.0179},  //10
    {0.0204, 0.0224},  //11
    {0.0164, 0.0244},  //12
    {0.0114, 0.0254},  //13
    {0.0074, 0.0234},  //14
    {0.0024, 0.0204},  //15
    {0.0016, 0.0190},  //16
    {-0.0006, 0.0134}, //17
    {-0.0026, 0.0094}, //18
    {-0.0026, 0.0044}  //19
};

new slotCombs[9][3][3] = {
    //1X:
    {{4, 9, 17}, {7, 14, 16}, {0, 2, 12}},
    //2X:
    {{1, 8, 14}, {1, 4, 18}, {3, 7, 15}},
    {{0, 6, 15}, {10, 15, 17}, {5, 9, 18}},
    //3X:
    {{5, 19, 19}, {0, 13, 13}, {4, 14, 14}},
    {{7, 18, 18}, {9, 11, 11}, {6, 17, 17}},
    //4X:
    {{3, 11, 11}, {3, 8, 8}, {8, 19, 19}},
    {{2, 13, 13}, {12, 19, 19}, {1, 16, 16}},
    //5X:
    {{16, 16, 16}, {6, 6, 6}, {11, 11, 11}},
    //10X:
    {{10, 10, 10}, {5, 5, 5}, {13, 13, 13}}
};

new Text: SlotMachineTD[5];

LoadSlotMachineTextDraw()
{
    SlotMachineTD[0] = TextDrawCreate(456.000000, 103.000000, "~n~");
    TextDrawBackgroundColor(SlotMachineTD[0], 255);
    TextDrawFont(SlotMachineTD[0], 1);
    TextDrawLetterSize(SlotMachineTD[0], 0.699999, 4.000000);
    TextDrawColor(SlotMachineTD[0], -1);
    TextDrawSetOutline(SlotMachineTD[0], 0);
    TextDrawSetProportional(SlotMachineTD[0], 1);
    TextDrawSetShadow(SlotMachineTD[0], 1);
    TextDrawUseBox(SlotMachineTD[0], 1);
    TextDrawBoxColor(SlotMachineTD[0], 70);
    TextDrawTextSize(SlotMachineTD[0], 213.000000, 20.000000);

    SlotMachineTD[1] = TextDrawCreate(246.000000, 302.000000, "START");
    TextDrawAlignment(SlotMachineTD[1], 2);
    TextDrawBackgroundColor(SlotMachineTD[1], 255);
    TextDrawFont(SlotMachineTD[1], 2);
    TextDrawLetterSize(SlotMachineTD[1], 0.409999, 2.499999);
    TextDrawColor(SlotMachineTD[1], -1);
    TextDrawSetOutline(SlotMachineTD[1], 0);
    TextDrawSetProportional(SlotMachineTD[1], 1);
    TextDrawSetShadow(SlotMachineTD[1], 0);
    TextDrawUseBox(SlotMachineTD[1], 1);
    TextDrawBoxColor(SlotMachineTD[1], 70);
    TextDrawTextSize(SlotMachineTD[1], 18.000000, 67.000000);
    TextDrawSetSelectable(SlotMachineTD[1], 1);

    SlotMachineTD[2] = TextDrawCreate(426.000000, 302.000000, "EXIT");
    TextDrawAlignment(SlotMachineTD[2], 2);
    TextDrawBackgroundColor(SlotMachineTD[2], 255);
    TextDrawFont(SlotMachineTD[2], 2);
    TextDrawLetterSize(SlotMachineTD[2], 0.409999, 2.499999);
    TextDrawColor(SlotMachineTD[2], -1);
    TextDrawSetOutline(SlotMachineTD[2], 0);
    TextDrawSetProportional(SlotMachineTD[2], 1);
    TextDrawSetShadow(SlotMachineTD[2], 0);
    TextDrawUseBox(SlotMachineTD[2], 1);
    TextDrawBoxColor(SlotMachineTD[2], 70);
    TextDrawTextSize(SlotMachineTD[2], 18.000000, 67.000000);
    TextDrawSetSelectable(SlotMachineTD[2], 1);

    SlotMachineTD[3] = TextDrawCreate(310.000000, 302.000000, "-");
    TextDrawAlignment(SlotMachineTD[3], 2);
    TextDrawBackgroundColor(SlotMachineTD[3], 255);
    TextDrawFont(SlotMachineTD[3], 2);
    TextDrawLetterSize(SlotMachineTD[3], 0.409999, 2.499999);
    TextDrawColor(SlotMachineTD[3], -1);
    TextDrawSetOutline(SlotMachineTD[3], 0);
    TextDrawSetProportional(SlotMachineTD[3], 1);
    TextDrawSetShadow(SlotMachineTD[3], 0);
    TextDrawUseBox(SlotMachineTD[3], 1);
    TextDrawBoxColor(SlotMachineTD[3], 70);
    TextDrawTextSize(SlotMachineTD[3], 19.000000, 33.000000);
    TextDrawSetSelectable(SlotMachineTD[3], 1);

    SlotMachineTD[4] = TextDrawCreate(358.000000, 302.000000, "+");
    TextDrawAlignment(SlotMachineTD[4], 2);
    TextDrawBackgroundColor(SlotMachineTD[4], 255);
    TextDrawFont(SlotMachineTD[4], 2);
    TextDrawLetterSize(SlotMachineTD[4], 0.409999, 2.499999);
    TextDrawColor(SlotMachineTD[4], -1);
    TextDrawSetOutline(SlotMachineTD[4], 0);
    TextDrawSetProportional(SlotMachineTD[4], 1);
    TextDrawSetShadow(SlotMachineTD[4], 0);
    TextDrawUseBox(SlotMachineTD[4], 1);
    TextDrawBoxColor(SlotMachineTD[4], 70);
    TextDrawTextSize(SlotMachineTD[4], 19.000000, 33.000000);
    TextDrawSetSelectable(SlotMachineTD[4], 1);
    return 1;
}

LoadSlotMachine()
{
    CreateSlotMachine(2254.74683, 1589.09241, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2254.76685, 1589.59241, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2254.74683, 1598.79236, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2254.76685, 1599.31238, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2269.72681, 1589.09241, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2269.72681, 1598.79236, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2269.74683, 1589.59241, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2269.74683, 1599.31238, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2255.30688, 1609.79236, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2255.32690, 1610.29236, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2255.30688, 1616.95239, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2255.32690, 1617.47241, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2271.81201, 1604.43372, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2271.83179, 1604.95300, 2006.77350,   0.00000, 0.00000, 180.00000);
    CreateSlotMachine(2271.83179, 1609.75916, 2006.77350,   0.00000, 0.00000, 0.00000);
    CreateSlotMachine(2271.87183, 1610.27075, 2006.77350,   0.00000, 0.00000, 180.00000);
    return 1;
}

CreateSlotMachine(Float: X, Float: Y, Float: Z, Float: RX, Float: RY, Float: RZ)
{
    SlotMachine[totalsmachines][sm_userID] = -1;
    SlotMachine[totalsmachines][sm_Pos][0] = X;
    SlotMachine[totalsmachines][sm_Pos][1] = Y;
    SlotMachine[totalsmachines][sm_Pos][2] = Z;
    SlotMachine[totalsmachines][sm_Pos][3] = RZ;
    SlotMachine[totalsmachines][sm_Objects][0] = CreateDynamicObject(2980, X, Y, Z, RX, RY, RZ, -1, -1, -1, 120.0, 120.0);
    SlotMachine[totalsmachines][sm_Objects][1] = CreateDynamicObject(2979, X, Y, Z, random(20) * 18.0, RY, RZ, -1, -1, -1, 120.0, 120.0);
    SlotMachine[totalsmachines][sm_Objects][2] = CreateDynamicObject(2981, X, Y, Z, random(20) * 18.0, RY, RZ, -1, -1, -1, 120.0, 120.0);
    SlotMachine[totalsmachines][sm_Objects][3] = CreateDynamicObject(2982, X, Y, Z, random(20) * 18.0, RY, RZ, -1, -1, -1, 120.0, 120.0);
    SlotMachine[totalsmachines][sm_objStop] = 3;
    totalsmachines++;
    return 1;
}

SpinReel(sm_idx, reel_id, comb)
{
    new index = slotCombs[comb][reel_id - 1][random(3)];
    new Float: X, Float: Y, Float: Z;
    switch(SlotMachine[sm_idx][sm_Pos][3])
    {
        case 0.0:
        {
            X = SlotMachine[sm_idx][sm_Pos][0];
            Y = SlotMachine[sm_idx][sm_Pos][1] + swiftData[index][0];
            Z = SlotMachine[sm_idx][sm_Pos][2] + swiftData[index][1];
        }
        case 90.0:
        {
            X = SlotMachine[sm_idx][sm_Pos][0] - swiftData[index][0];
            Y = SlotMachine[sm_idx][sm_Pos][1];
            Z = SlotMachine[sm_idx][sm_Pos][2] + swiftData[index][1];
        }
        case 180.0:
        {
            X = SlotMachine[sm_idx][sm_Pos][0];
            Y = SlotMachine[sm_idx][sm_Pos][1] - swiftData[index][0];
            Z = SlotMachine[sm_idx][sm_Pos][2] + swiftData[index][1];
        }
        case 270.0:
        {
            X = SlotMachine[sm_idx][sm_Pos][0] + swiftData[index][0];
            Y = SlotMachine[sm_idx][sm_Pos][1];
            Z = SlotMachine[sm_idx][sm_Pos][2] + swiftData[index][1];
        }
    }
    MoveDynamicObject(SlotMachine[sm_idx][sm_Objects][reel_id], X, Y, Z, 0.01, index * 18.0, 0.0, SlotMachine[sm_idx][sm_Pos][3]);
}

ExitSlotMachine(playerid)
{
    if(p_temp[playerid][slot_machine_use] == -1) return 1;
    new i = p_temp[playerid][slot_machine_use];
    SlotMachine[i][sm_userID] = -1;
    p_temp[playerid][SlotMachineTextDraw] = false;
    p_temp[playerid][slot_machine_use] = -1;
    for(new f; f < 5; f++) TextDrawHideForPlayer(playerid, SlotMachineTD[f]);
    PlayerTextDrawDestroy(playerid, SlotMScoreTD[playerid]);
    SetCameraBehindPlayer(playerid);
    CancelSelectTextDraw(playerid);
    return 1;
}
