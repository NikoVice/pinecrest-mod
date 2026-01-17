CheckPlayerBot(playerid, idx)
{
	if(GetPlayerGameVersion(playerid) >= CLIENT_VERSION_022023 && IsPlayerMobile(playerid)) return 1;
	if(p_temp[playerid][antibot_check] == true) return 1;
	p_temp[playerid][antibot_idx]++;
	if(p_temp[playerid][antibot_idx] == idx)
	{
		new number = random(9), random_symbol = random(100), random_pos = random(100), random_float = random(100);
		switch(number)
		{
			case 0:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 276.0, 232.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 293.0, 199.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 320.0, 171.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 322.0, 200.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 322.0, 234.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 322.0, 267.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 322.0, 298.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 207.0, 270.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 206.0, 234.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 204.0, 200.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 451.0, 232.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 421.0, 232.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 390.0, 233.0);

				for(new i = 0; i < 13; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 7 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 1:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 260.0, 174.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 290.0, 153.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 323.0, 153.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 346.0, 182.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 336.0, 222.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 314.0, 256.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 290.0, 282.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 261.0, 313.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 296.0, 312.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 328.0, 311.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 361.0, 309.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 364.0, 76.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 384.0, 105.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 407.0, 137.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 175.0, 244.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 175.0, 278.0);
				CreateBotTextDraw(playerid, 16, random_symbol, random_pos, random_float, 175.0, 313.0);

				for(new i = 0; i < 17; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 11 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 2:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 274.0, 144.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 298.0, 135.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 324.0, 137.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 344.0, 158.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 346.0, 192.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 340.0, 228.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 309.0, 231.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 278.0, 233.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 352.0, 257.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 352.0, 292.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 338.0, 320.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 311.0, 331.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 279.0, 327.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 440.0, 82.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 440.0, 116.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 440.0, 151.0);
				CreateBotTextDraw(playerid, 16, random_symbol, random_pos, random_float, 119.0, 241.0);
				CreateBotTextDraw(playerid, 17, random_symbol, random_pos, random_float, 148.0, 241.0);
				CreateBotTextDraw(playerid, 18, random_symbol, random_pos, random_float, 178.0, 240.0);

				for(new i = 0; i < 19; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 13 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 3:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 271.0, 146.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 272.0, 182.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 272.0, 221.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 307.0, 223.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 342.0, 221.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 341.0, 181.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 341.0, 149.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 343.0, 257.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 345.0, 291.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 346.0, 325.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 387.0, 71.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 407.0, 93.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 429.0, 117.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 179.0, 261.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 179.0, 294.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 178.0, 327.0);

				for(new i = 0; i < 16; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 10 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 4:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 302.0, 128.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 272.0, 129.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 273.0, 160.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 274.0, 193.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 275.0, 230.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 305.0, 231.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 334.0, 244.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 356.0, 266.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 355.0, 302.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 338.0, 333.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 309.0, 346.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 281.0, 351.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 330.0, 127.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 356.0, 128.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 455.0, 132.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 455.0, 164.0);
				CreateBotTextDraw(playerid, 16, random_symbol, random_pos, random_float, 456.0, 198.0);
				CreateBotTextDraw(playerid, 17, random_symbol, random_pos, random_float, 148.0, 291.0);
				CreateBotTextDraw(playerid, 18, random_symbol, random_pos, random_float, 173.0, 292.0);
				CreateBotTextDraw(playerid, 19, random_symbol, random_pos, random_float, 200.0, 292.0);

				for(new i = 0; i < 20; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 14 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 5:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 351.0, 148.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 331.0, 124.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 302.0, 121.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 277.0, 141.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 270.0, 174.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 271.0, 213.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 272.0, 250.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 282.0, 290.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 315.0, 306.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 347.0, 288.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 355.0, 248.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 333.0, 220.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 299.0, 222.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 434.0, 212.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 460.0, 212.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 488.0, 210.0);
				CreateBotTextDraw(playerid, 16, random_symbol, random_pos, random_float, 172.0, 198.0);
				CreateBotTextDraw(playerid, 17, random_symbol, random_pos, random_float, 172.0, 229.0);
				CreateBotTextDraw(playerid, 18, random_symbol, random_pos, random_float, 172.0, 261.0);

				for(new i = 0; i < 19; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 13 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 6:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 273.0, 147.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 301.0, 146.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 354.0, 147.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 344.0, 177.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 327.0, 208.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 313.0, 236.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 297.0, 263.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 329.0, 145.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 279.0, 293.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 444.0, 114.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 444.0, 145.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 445.0, 174.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 213.0, 219.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 186.0, 219.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 158.0, 220.0);

				for(new i = 0; i < 15; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 9 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 7:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 309.0, 119.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 309.0, 217.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 312.0, 317.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 267.0, 273.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 267.0, 163.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 348.0, 165.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 351.0, 272.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 336.0, 240.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 340.0, 303.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 284.0, 306.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 284.0, 241.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 282.0, 196.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 282.0, 133.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 337.0, 134.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 334.0, 196.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 439.0, 185.0);
				CreateBotTextDraw(playerid, 16, random_symbol, random_pos, random_float, 439.0, 215.0);
				CreateBotTextDraw(playerid, 17, random_symbol, random_pos, random_float, 439.0, 245.0);
				CreateBotTextDraw(playerid, 18, random_symbol, random_pos, random_float, 172.0, 195.0);
				CreateBotTextDraw(playerid, 19, random_symbol, random_pos, random_float, 172.0, 223.0);
				CreateBotTextDraw(playerid, 20, random_symbol, random_pos, random_float, 172.0, 255.0);

				for(new i = 0; i < 21; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 15 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
			case 8:
			{
				CreateBotTextDraw(playerid, 0, random_symbol, random_pos, random_float, 270.0, 284.0);
				CreateBotTextDraw(playerid, 1, random_symbol, random_pos, random_float, 291.0, 310.0);
				CreateBotTextDraw(playerid, 2, random_symbol, random_pos, random_float, 321.0, 310.0);
				CreateBotTextDraw(playerid, 3, random_symbol, random_pos, random_float, 342.0, 282.0);
				CreateBotTextDraw(playerid, 4, random_symbol, random_pos, random_float, 341.0, 249.0);
				CreateBotTextDraw(playerid, 5, random_symbol, random_pos, random_float, 341.0, 216.0);
				CreateBotTextDraw(playerid, 6, random_symbol, random_pos, random_float, 343.0, 182.0);
				CreateBotTextDraw(playerid, 7, random_symbol, random_pos, random_float, 339.0, 154.0);
				CreateBotTextDraw(playerid, 8, random_symbol, random_pos, random_float, 312.0, 139.0);
				CreateBotTextDraw(playerid, 9, random_symbol, random_pos, random_float, 282.0, 145.0);
				CreateBotTextDraw(playerid, 10, random_symbol, random_pos, random_float, 271.0, 177.0);
				CreateBotTextDraw(playerid, 11, random_symbol, random_pos, random_float, 279.0, 211.0);
				CreateBotTextDraw(playerid, 12, random_symbol, random_pos, random_float, 310.0, 221.0);
				CreateBotTextDraw(playerid, 13, random_symbol, random_pos, random_float, 361.0, 73.0);
				CreateBotTextDraw(playerid, 14, random_symbol, random_pos, random_float, 382.0, 93.0);
				CreateBotTextDraw(playerid, 15, random_symbol, random_pos, random_float, 402.0, 116.0);
				CreateBotTextDraw(playerid, 16, random_symbol, random_pos, random_float, 197.0, 186.0);
				CreateBotTextDraw(playerid, 17, random_symbol, random_pos, random_float, 198.0, 217.0);
				CreateBotTextDraw(playerid, 18, random_symbol, random_pos, random_float, 198.0, 250.0);

				for(new i = 0; i < 19; i++)
				{
					PlayerTextDrawTextSize(playerid, PTD_AntiBot[playerid][i], 25.0000, 25.0000);
					PlayerTextDrawAlignment(playerid, PTD_AntiBot[playerid][i], 1);
					PlayerTextDrawColor(playerid, PTD_AntiBot[playerid][i], -1);
					PlayerTextDrawBackgroundColor(playerid, PTD_AntiBot[playerid][i], 255);
					PlayerTextDrawFont(playerid, PTD_AntiBot[playerid][i], 4);
					PlayerTextDrawSetProportional(playerid, PTD_AntiBot[playerid][i], 0);
					PlayerTextDrawSetShadow(playerid, PTD_AntiBot[playerid][i], 0);
				}

				for(new i = 0; i < 13 + random(6); i++) PlayerTextDrawShow(playerid, PTD_AntiBot[playerid][i]);
			}
		}
		SendMes(playerid, COLOR_LIME, "Для продолжения работы необходимо ответить на вопрос.");
		SendMes(playerid, COLOR_LYELLOW, "Какая цифра отображена на экране? Время на ответ: 15 сек.");
		SendMes(playerid, COLOR_BLUE, "Если на экране ничего не видно, возможно это из-за сборки.");
		p_temp[playerid][antibot_check] = true;
		p_temp[playerid][antibot_idx] = 0;
		p_temp[playerid][antibot_number] = number + 1;
		p_temp[playerid][antibot_time] = 15;
		Fix_TogglePlayerControllable(playerid, false);
	}
	return 1;
}

CreateBotTextDraw(playerid, idx, random_symbol, random_pos, random_float, Float:x, Float:y)
{
	switch(random_symbol)
	{
		case 0 .. 49:
		{
			switch(random_float)
			{
				case 0 .. 49: PTD_AntiBot[playerid][idx] = CreatePlayerTextDraw(playerid, x - random_pos, y, "ld_grav:timer");
				default: PTD_AntiBot[playerid][idx] = CreatePlayerTextDraw(playerid, x, y - random_pos, "ld_grav:timer");
			}
		}
		default:
		{
			switch(random_float)
			{
				case 0 .. 49: PTD_AntiBot[playerid][idx] = CreatePlayerTextDraw(playerid, x + random_pos, y, "ld_grav:timer");
				default: PTD_AntiBot[playerid][idx] = CreatePlayerTextDraw(playerid, x, y + random_pos, "ld_grav:timer");
			}
		}
	}
	return 1;
}

ClearBot(playerid, const text[])
{
	Fix_TogglePlayerControllable(playerid, true);
	p_temp[playerid][antibot_check] = false;
	p_temp[playerid][antibot_idx] = 0;
	p_temp[playerid][antibot_number] = 0;
	p_temp[playerid][antibot_time] = 0;
	p_info[playerid][job_block] = 60;
	MysqlUpdatePlayerInt(playerid, "job_block", p_info[playerid][job_block]);
	SendMes(playerid, COLOR_LIGHTRED, text);
	SendMes(playerid, COLOR_LIGHTRED, "Вам запрещено работать на некоторых работах и добывать ресурсы в течении 1 минуты.");
	SendMes(playerid, COLOR_LIGHTRED, "Причина: "W"подозрение в использовании запрещенных программ.");
	for(new i = 20; i != -1; i--)
	{
		if(PTD_AntiBot[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, PTD_AntiBot[playerid][i]);
			PTD_AntiBot[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	EndPlayerJob(playerid);
	return 1;
}

CMD:antibot(playerid)
{
	if(SRV_ID) return 1;
	CheckPlayerBot(playerid, 3);
	return 1;
}
