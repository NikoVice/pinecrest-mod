/*new phone_warehouse[4] = {1, 1, 1, 1};*/

new PlayerText:PhoneMain[MAX_PLAYERS][45];

this::ShowPlayerPhone(playerid, phone_id)
{
    if(IsTDVisible(playerid) != -1) return 1;
    /*if(p_info[playerid][phone_number] < 1) return SendError(playerid, "У Вас нет номера телефона.");*/
    if(p_temp[playerid][calling] != INVALID_PLAYER_ID || p_temp[playerid][phone_talk] != 0) return SendError(playerid, "Вы разговариваете по телефону.");

    MeAction(playerid, "достал(-а) телефон");
    SetPlayerChatBubble(playerid, "достал(-а) телефон", COLOR_MAIN, 20.0, 10000);

    p_info[playerid][active_phone_id] = phone_id;
	MysqlUpdatePlayerInt(playerid, "active_phone_id", p_info[playerid][active_phone_id]);
    switch(phone_id)
    {
        case 674:
        {
            new year, month,day, name_dialog[64];
            getdate(year, month, day);
            format(name_dialog,sizeof(name_dialog),""I"%.02d:%s%.02d %02d/%02d/%d | Phone", timestamp_hour, (timestamp_minute < 10) ? ("0") : (""), timestamp_minute, day, month, year);
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
            "I"[1]"W" Позвонить\n\
            "I"[2]"W" Сообщения\n\
            "I"[3]"W" Контакты\n\
            "I"[4]"W" %s телефон\n\
            "I"[5]"W" Убрать телефон", p_temp[playerid][offphone] ? "{"#cGREEN"}Включить"W"" : "{"#cLIGHTRED"}Выключить"W"");
            ShowPlayerDialog(playerid, D_PHONE, DIALOG_STYLE_LIST, name_dialog, STRING_GLOBAL, "Далее", "Отмена");
        }
        default:
        {
            if(p_info[playerid][p_settings][INTERFACE]) return ShowTextDrawForPlayer(playerid, TD_ID_PHONE);
            LoadPlayerTextDrawPhone(playerid);

            new phone_color_main[4] = {608062463, -68430849, 1061042943, -488382721};
            new phone_color_other[4][9] = {
                {608062357, 608062352, 608062341, 608062336, 608062325, 608062320, 608062309, 608062304, 608062293},
                {-85208171, -85208176, -85208187, -85208192, -85208203, -85208208, -85208219, -85208224, -85208235},
                {1061042837, 1061042832, 1061042821, 1061042816, 1061042805, 1061042800, 1061042789, 1061042784, 1061042773},
                {-488382827, -488382832, -488382843, -488382848, -488382859, -488382864, -488382875, -488382880, -488382891}
            };
            new type = phone_id-675;
            for(new i = 0; i < 45; i++)
            {
                if(i < 6) PlayerTextDrawColor(playerid, PhoneMain[playerid][i], phone_color_main[type]);
                if(i > 11 && i < 16) PlayerTextDrawColor(playerid, PhoneMain[playerid][i], phone_color_main[type]);
                if(i > 15 && i < 25) PlayerTextDrawColor(playerid, PhoneMain[playerid][i], phone_color_other[type][i - 16]);
                if(i > 30 && i < 37) PlayerTextDrawColor(playerid, PhoneMain[playerid][i], phone_color_main[type]);

                PlayerTextDrawShow(playerid, PhoneMain[playerid][i]);
            }

            p_temp[playerid][TextDrawPhone] = true;

            UpdatePlayerPhoneInfo(playerid);

            SelectTextDraw(playerid, -1);
        }
    }
    return 1;
}

HidePlayerPhone(playerid)
{
    if(p_info[playerid][p_settings][INTERFACE]) return HideTextDrawForPlayer(playerid, TD_ID_PHONE);
	for(new i = 0; i < 45; i++)
	{
		if(PhoneMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PhoneMain[playerid][i]);
			PhoneMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}

	p_temp[playerid][TextDrawPhone] = false;

	CancelSelectTextDraw(playerid);
	return 1;
}

UpdatePlayerPhoneInfo(playerid)
{
	new str[64];

	format(str, sizeof(str), "%02d:%02d", timestamp_hour, timestamp_minute);
	PlayerTextDrawSetString(playerid, PhoneMain[playerid][25], str), PlayerTextDrawSetString(playerid, PhoneMain[playerid][29], str);

	new month_name[12][12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	new day_name[7][12] = {"Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday"};

	new year, month, day;
	getdate(year, month, day);

	format(str, sizeof(str), "%s, %d %s", day_name[getDayEx()], day, month_name[month-1]);
	PlayerTextDrawSetString(playerid, PhoneMain[playerid][26], str);
	return 1;
}

LoadPlayerTextDrawPhone(playerid)
{
	PhoneMain[playerid][0] = CreatePlayerTextDraw(playerid, 500.5509, 368.5205, "LD_BEAT:chit"); // Фон;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][0], 50.0000, 50.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][0], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][0], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][0], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][0], 0);

	PhoneMain[playerid][1] = CreatePlayerTextDraw(playerid, 590.5324, 368.5205, "LD_BEAT:chit"); // Фон;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][1], 50.0000, 50.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][1], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][1], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][1], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][1], 0);

	PhoneMain[playerid][2] = CreatePlayerTextDraw(playerid, 500.5509, 143.2066, "LD_BEAT:chit"); // Фон;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][2], 50.0000, 50.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][2], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][2], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][2], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][2], 0);

	PhoneMain[playerid][3] = CreatePlayerTextDraw(playerid, 590.5324, 143.2066, "LD_BEAT:chit"); // Фон;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][3], 50.0000, 50.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][3], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][3], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][3], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][3], 0);

	PhoneMain[playerid][4] = CreatePlayerTextDraw(playerid, 524.3496, 151.4333, "LD_SPAC:white"); // Фон;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][4], 93.0792, 258.8197);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][4], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][4], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][4], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][4], 0);

	PhoneMain[playerid][5] = CreatePlayerTextDraw(playerid, 508.6499, 167.9889, "LD_SPAC:white"); // Фон;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][5], 123.5792, 227.6510);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][5], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][5], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][5], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][5], 0);

	PhoneMain[playerid][6] = CreatePlayerTextDraw(playerid, 504.5830, 369.1357, "LD_BEAT:chit");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][6], 45.0000, 45.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][6], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][6], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][6], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][6], 0);

	PhoneMain[playerid][7] = CreatePlayerTextDraw(playerid, 591.5642, 369.1357, "LD_BEAT:chit");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][7], 45.0000, 45.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][7], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][7], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][7], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][7], 0);

	PhoneMain[playerid][8] = CreatePlayerTextDraw(playerid, 504.5830, 147.2221, "LD_BEAT:chit");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][8], 45.0000, 45.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][8], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][8], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][8], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][8], 0);

	PhoneMain[playerid][9] = CreatePlayerTextDraw(playerid, 591.5642, 147.2221, "LD_BEAT:chit");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][9], 45.0000, 45.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][9], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][9], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][9], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][9], 0);

	PhoneMain[playerid][10] = CreatePlayerTextDraw(playerid, 526.9995, 154.6813, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][10], 87.5895, 251.7794);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][10], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][10], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][10], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][10], 0);

	PhoneMain[playerid][11] = CreatePlayerTextDraw(playerid, 512.1831, 168.6813, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][11], 116.5298, 221.6806);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][11], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][11], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][11], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][11], 0);

	PhoneMain[playerid][12] = CreatePlayerTextDraw(playerid, 544.2163, 151.7519, "LD_BEAT:chit"); // Чёлка;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][12], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][12], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][12], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][12], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][12], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][12], 0);

	PhoneMain[playerid][13] = CreatePlayerTextDraw(playerid, 576.9085, 151.7519, "LD_BEAT:chit"); // Чёлка;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][13], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][13], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][13], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][13], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][13], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][13], 0);

	PhoneMain[playerid][14] = CreatePlayerTextDraw(playerid, 547.5501, 154.6183, "LD_SPAC:white"); // Чёлка;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][14], 45.8501, 7.5099);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][14], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][14], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][14], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][14], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][14], 0);

	PhoneMain[playerid][15] = CreatePlayerTextDraw(playerid, 553.6491, 154.7183, "LD_SPAC:white"); // Чёлка;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][15], 33.5699, 13.6099);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][15], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][15], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][15], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][15], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][15], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][15], 0);

	PhoneMain[playerid][16] = CreatePlayerTextDraw(playerid, 515.8331, 170.0368, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][16], 50.0000, 50.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][16], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][16], 608062357);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][16], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][16], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][16], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][16], 0);

	PhoneMain[playerid][17] = CreatePlayerTextDraw(playerid, 560.0006, 228.1109, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][17], 45.0000, 45.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][17], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][17], 608062352);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][17], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][17], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][17], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][17], 0);

	PhoneMain[playerid][18] = CreatePlayerTextDraw(playerid, 519.1671, 319.8887, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][18], 40.0000, 40.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][18], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][18], 608062341);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][18], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][18], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][18], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][18], 0);

	PhoneMain[playerid][19] = CreatePlayerTextDraw(playerid, 573.3333, 301.2221, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][19], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][19], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][19], 608062336);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][19], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][19], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][19], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][19], 0);

	PhoneMain[playerid][20] = CreatePlayerTextDraw(playerid, 531.6666, 275.2958, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][20], 29.0000, 30.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][20], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][20], 608062325);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][20], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][20], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][20], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][20], 0);

	PhoneMain[playerid][21] = CreatePlayerTextDraw(playerid, 599.5833, 167.9627, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][21], 25.0000, 25.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][21], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][21], 608062320);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][21], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][21], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][21], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][21], 0);

	PhoneMain[playerid][22] = CreatePlayerTextDraw(playerid, 525.4160, 233.2960, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][22], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][22], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][22], 608062309);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][22], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][22], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][22], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][22], 0);

	PhoneMain[playerid][23] = CreatePlayerTextDraw(playerid, 584.5827, 210.4812, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][23], 15.0000, 15.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][23], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][23], 608062304);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][23], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][23], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][23], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][23], 0);

	PhoneMain[playerid][24] = CreatePlayerTextDraw(playerid, 601.6660, 281.5184, "LD_BEAT:chit"); // Изображение;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][24], 10.0000, 10.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][24], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][24], 608062293);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][24], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][24], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][24], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][24], 0);

	PhoneMain[playerid][25] = CreatePlayerTextDraw(playerid, 571.7504, 169.0330, "20:00"); // Время;
	PlayerTextDrawLetterSize(playerid, PhoneMain[playerid][25], 0.4499, 2.5176);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][25], 2);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][25], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][25], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][25], 2);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][25], 1);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][25], 0);

	PhoneMain[playerid][26] = CreatePlayerTextDraw(playerid, 571.3167, 192.3108, "Wednesday,_10_February"); // Дата;
	PlayerTextDrawLetterSize(playerid, PhoneMain[playerid][26], 0.1870, 1.5427);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][26], 2);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][26], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][26], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][26], 2);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][26], 1);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][26], 0);

	PhoneMain[playerid][27] = CreatePlayerTextDraw(playerid, 562.0493, 159.3925, "LD_SPAC:white");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][27], 17.0000, 3.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][27], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][27], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][27], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][27], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][27], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][27], 0);

	PhoneMain[playerid][28] = CreatePlayerTextDraw(playerid, 580.9666, 155.8815, "LD_BEAT:chit");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][28], 10.0000, 10.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][28], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][28], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][28], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][28], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][28], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][28], 0);

	PhoneMain[playerid][29] = CreatePlayerTextDraw(playerid, 545.4439, 154.4776, "20:00"); // Время;
	PlayerTextDrawLetterSize(playerid, PhoneMain[playerid][29], 0.1861, 1.1955);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][29], 3);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][29], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][29], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][29], 2);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][29], 1);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][29], 0);

	PhoneMain[playerid][30] = CreatePlayerTextDraw(playerid, 596.6984, 154.4776, "100_%"); // Зарядка;
	PlayerTextDrawLetterSize(playerid, PhoneMain[playerid][30], 0.1861, 1.1955);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][30], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][30], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][30], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][30], 2);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][30], 1);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][30], 0);

	PhoneMain[playerid][31] = CreatePlayerTextDraw(playerid, 509.7000, 363.1065, "LD_BEAT:chit"); // Фон под кнопками;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][31], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][31], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][31], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][31], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][31], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][31], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][31], 0);

	PhoneMain[playerid][32] = CreatePlayerTextDraw(playerid, 596.3795, 363.1065, "LD_BEAT:chit"); // Фон под кнопками;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][32], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][32], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][32], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][32], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][32], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][32], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][32], 0);

	PhoneMain[playerid][33] = CreatePlayerTextDraw(playerid, 509.7000, 373.3070, "LD_BEAT:chit"); // Фон под кнопками;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][33], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][33], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][33], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][33], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][33], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][33], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][33], 0);

	PhoneMain[playerid][34] = CreatePlayerTextDraw(playerid, 596.3795, 373.3070, "LD_BEAT:chit"); // Фон под кнопками;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][34], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][34], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][34], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][34], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][34], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][34], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][34], 0);

	PhoneMain[playerid][35] = CreatePlayerTextDraw(playerid, 527.0670, 369.1220, "LD_SPAC:white"); // Фон под кнопками;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][35], 86.2200, 33.2000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][35], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][35], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][35], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][35], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][35], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][35], 0);

	PhoneMain[playerid][36] = CreatePlayerTextDraw(playerid, 515.5001, 380.8294, "LD_SPAC:white"); // Фон под кнопками;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][36], 110.0000, 10.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][36], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][36], 608062463);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][36], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][36], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][36], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][36], 0);

	PhoneMain[playerid][37] = CreatePlayerTextDraw(playerid, 514.5833, 368.3926, "LD_BEAT:chit"); // Звонок;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][37], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][37], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][37], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][37], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][37], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][37], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][37], 0);
	PlayerTextDrawSetSelectable(playerid, PhoneMain[playerid][37], true);

	PhoneMain[playerid][38] = CreatePlayerTextDraw(playerid, 540.3770, 368.3926, "LD_BEAT:chit"); // Сообщения;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][38], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][38], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][38], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][38], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][38], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][38], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][38], 0);
	PlayerTextDrawSetSelectable(playerid, PhoneMain[playerid][38], true);

	PhoneMain[playerid][39] = CreatePlayerTextDraw(playerid, 566.2874, 368.3926, "LD_BEAT:chit"); // Контакты;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][39], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][39], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][39], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][39], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][39], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][39], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][39], 0);
	PlayerTextDrawSetSelectable(playerid, PhoneMain[playerid][39], true);

	PhoneMain[playerid][40] = CreatePlayerTextDraw(playerid, 592.1644, 368.3926, "LD_BEAT:chit"); // Настройки;
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][40], 35.0000, 35.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][40], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][40], 336860415);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][40], 255);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][40], 4);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][40], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][40], 0);
	PlayerTextDrawSetSelectable(playerid, PhoneMain[playerid][40], true);

	PhoneMain[playerid][41] = CreatePlayerTextDraw(playerid, 523.5227, 374.3887, "");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][41], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][41], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][41], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][41], -256);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][41], 5);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][41], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][41], 0);
	PlayerTextDrawSetPreviewModel(playerid, PhoneMain[playerid][41], 11705);
	PlayerTextDrawSetPreviewRot(playerid, PhoneMain[playerid][41], -45.0000, 0.0000, 180.0000, 1.0000);

	PhoneMain[playerid][42] = CreatePlayerTextDraw(playerid, 548.0167, 375.4888, "");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][42], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][42], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][42], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][42], -256);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][42], 5);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][42], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][42], 0);
	PlayerTextDrawSetPreviewModel(playerid, PhoneMain[playerid][42], 1239);
	PlayerTextDrawSetPreviewRot(playerid, PhoneMain[playerid][42], 0.0000, 0.0000, 0.0000, 1.0000);

	PhoneMain[playerid][43] = CreatePlayerTextDraw(playerid, 573.6104, 375.4888, "");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][43], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][43], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][43], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][43], -256);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][43], 5);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][43], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][43], 0);
	PlayerTextDrawSetPreviewModel(playerid, PhoneMain[playerid][43], 1314);
	PlayerTextDrawSetPreviewRot(playerid, PhoneMain[playerid][43], 0.0000, 0.0000, 0.0000, 1.0000);

	PhoneMain[playerid][44] = CreatePlayerTextDraw(playerid, 599.7041, 375.4888, "");
	PlayerTextDrawTextSize(playerid, PhoneMain[playerid][44], 20.0000, 20.0000);
	PlayerTextDrawAlignment(playerid, PhoneMain[playerid][44], 1);
	PlayerTextDrawColor(playerid, PhoneMain[playerid][44], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneMain[playerid][44], -256);
	PlayerTextDrawFont(playerid, PhoneMain[playerid][44], 5);
	PlayerTextDrawSetProportional(playerid, PhoneMain[playerid][44], 0);
	PlayerTextDrawSetShadow(playerid, PhoneMain[playerid][44], 0);
	PlayerTextDrawSetPreviewModel(playerid, PhoneMain[playerid][44], 19804);
	PlayerTextDrawSetPreviewRot(playerid, PhoneMain[playerid][44], 0.0000, 0.0000, 0.0000, 1.0000);
	return 1;
}

CMD:phone(playerid, params[])
{
    if(p_info[playerid][active_phone_id] < 670 || p_info[playerid][active_phone_id] == 0 || !GetInventoryAmount(playerid, p_info[playerid][active_phone_id]))
    {
        STRING_GLOBAL = "[#] Название\tНаличие\tАктивность\n", STRING_MIN[0] = EOS;
        for(new i = 674; i < 679; i++)
        {
            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%s\n", i-673, ItemsInfo[i][iName], GetInventoryAmount(playerid, i) == 1 ? "{"#cGREEN"}Есть"W"" : "{"#cLIGHTRED"}Нет"W"", p_info[playerid][active_phone_id] == i ? "{"#cGREEN"}Да"W"" : "{"#cLIGHTRED"}Нет"W"");
            strcat(STRING_GLOBAL, STRING_MIN);
        }
        ShowPlayerDialog(playerid, D_PHONE_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Телефоны", STRING_GLOBAL, "Далее", "Отмена");
    }
    else ShowPlayerPhone(playerid, p_info[playerid][active_phone_id]);
    return 1;
}

CMD:changephone(playerid, params[])
{
    STRING_GLOBAL = "[#] Название\tНаличие\tАктивность\n", STRING_MIN[0] = EOS;
    for(new i = 674; i < 679; i++)
    {
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%s\t%s\n", i-673, ItemsInfo[i][iName], GetInventoryAmount(playerid, i) == 1 ? "{"#cGREEN"}Есть"W"" : "{"#cLIGHTRED"}Нет"W"", p_info[playerid][active_phone_id] == i ? "{"#cGREEN"}Да"W"" : "{"#cLIGHTRED"}Нет"W"");
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_PHONE_SET_ACTIVE, DIALOG_STYLE_TABLIST_HEADERS, ""I"Телефоны", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

/*AddPhoneWarehouseInfo()
{
	new check;
	for(new i = 0; i < 4; i++)
	{
		if(phone_warehouse[i] >= 5) continue;
		check = random(2);
		if(phone_warehouse[i] + check > 5) check = 5 - phone_warehouse[i];
		phone_warehouse[i] += check;
	}
	STRING_MIN[0] = EOS;
	format(STRING_MIN, sizeof(STRING_MIN), "%d, %d, %d, %d", phone_warehouse[0], phone_warehouse[1], phone_warehouse[2], phone_warehouse[3]);
	MysqlUpdateOtherStr("phone_warehouse", STRING_MIN);
	return 1;
}*/
