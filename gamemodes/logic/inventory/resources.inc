#define MAX_CHANGE_RESOURCES				5
#define MAX_MINE_RESOURCES					23
#define MAX_FARM_RESOURCES					21
#define MAX_FARM_RESOURCES_COUNT			10

new resources_area[2];

enum
{
	RESOURCES_TYPE_MINE,
	RESOURCES_TYPE_FARM,
	RESOURCES_TYPE_H_COTTON,
	RESOURCES_TYPE_H_LINEN
}

enum E_CHANGE_RESOURCES
{
	cType,
	cItemsIDx
}
new ChangeResourcesInfo[MAX_CHANGE_RESOURCES][E_CHANGE_RESOURCES] = {
	{RESOURCES_TYPE_MINE, 649},
	{RESOURCES_TYPE_MINE, 650},
	{RESOURCES_TYPE_MINE, 651},
	{RESOURCES_TYPE_FARM, 647},
	{RESOURCES_TYPE_FARM, 648}
};

enum
{
	TYPE_CHANGE_RESOURCES_MENU = 1,
	TYPE_CHANGE_RESOURCES_SELL,
	TYPE_CHANGE_RESOURCES_HELP
}

ShowChangeResourcesDialog(playerid, type_dialog, type_res, first_parameter = 0)
{
	switch(type_dialog)
	{
		case TYPE_CHANGE_RESOURCES_MENU:
		{
			new items_idx, count;
			STRING_GLOBAL = "[#] Название\tСтоимость\tДоступно для продажи\n", STRING_MIN[0] = EOS;
			for(new i = 0; i < MAX_CHANGE_RESOURCES; i++)
			{
				if(ChangeResourcesInfo[i][cType] != type_res) continue;
				items_idx = ChangeResourcesInfo[i][cItemsIDx];
				format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$ за ед.\t%d ед.\n", count + 1, ItemsInfo[items_idx][iName], ItemsInfo[items_idx][iPrice], GetInventoryAmount(playerid, items_idx));
				strcat(STRING_GLOBAL, STRING_MIN);
				p_temp[playerid][p_listitem][count] = i;
				count++;
			}
			ShowPlayerDialog(playerid, D_CHANGE_RESOURCES_LIST, DIALOG_STYLE_TABLIST_HEADERS, ""I"Продажа ресурсов", STRING_GLOBAL, "Далее", "Отмена");
		}
		case TYPE_CHANGE_RESOURCES_SELL:
		{
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, ""W"Введите количество \"%s\":\nСтоимость "I"%d$"W" за "I"единицу."W"\n\nДоступно для продажи: "I"%d ед.", ItemsInfo[first_parameter][iName], ItemsInfo[first_parameter][iPrice], GetInventoryAmount(playerid, first_parameter));
			ShowPlayerDialog(playerid, D_CHANGE_RESOURCES_INPUT, DIALOG_STYLE_INPUT, ""I"Продажа ресурсов", STRING_GLOBAL, "Далее", "Отмена");
			p_temp[playerid][change_res_items] = first_parameter;
		}
		case TYPE_CHANGE_RESOURCES_HELP:
		{
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, ""W"\
			Привет, это "I"\"%s\","W" здесь ты можешь добывать "I"%s."W"\n\n\
			Для добычы ресурсов, тебе необходимо подойти к местоположению ресурса и добыть его.\n\n\
			Стандартное время добычи ресурса - "I"20 сек."W" Чтобы сократить его, тебе понадобится "I"\"%s\""W",\n\
			изготовить её можно с помощью крафта в подвале дома или на верстаке общего пользования на\n\
			центральном рынке.\n\n\
			Хочешь добывать в несколько раз больше ресурсов, добывай их в "I"\"%s\"."W"\n\n\
			Время появления ресурсов: "I"примерно каждые 5 мин."W"\n\n\
			При нажатии "I"\"Далее\""W" откроется диалог с продажей ресурсов, но цены в нем намного ниже, чем на\n\
			центральном рынке.", type_res == RESOURCES_TYPE_MINE ? "Шахта" : "Ферма", type_res == RESOURCES_TYPE_MINE ? "металл, древесину и камень" : "хлопок и лён", ItemsInfo[508][iName], ItemsInfo[74][iName]);
			ShowPlayerDialog(playerid, D_CHANGE_RESOURCES_INFO, DIALOG_STYLE_MSGBOX, ""I"Добыча ресурсов", STRING_GLOBAL, "Далее", "Отмена");
		}
	}
	return 1;
}

enum E_MINE_RESOURCES_INFO
{
	mStatus, // 0 - нет, 1 - есть;
	mItemsIDx, // ID ресурса из массива ItemsInfo;
	mCount, // Количество ресурса;
	mObject, // Обеъект;
	mArea, // Зона;
	Text3D:mText, // 3D текст;
	Float:mPos[4] // Координаты;
}
new MineResourcesInfo[MAX_MINE_RESOURCES][E_MINE_RESOURCES_INFO] = {
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1879.47034, -1683.24292, 21.02750, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1884.11401, -1654.34021, 21.03000, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1840.47815, -1661.00415, 21.02610, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1820.02405, -1653.07849, 21.02640, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1776.46997, -1615.23242, 21.10310, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1751.36389, -1622.18518, 21.14320, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1809.21399, -1588.25525, 21.04680, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1821.58521, -1577.45276, 21.02640, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1836.92078, -1561.53162, 21.02390, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1844.37598, -1578.18433, 21.02560, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1868.22681, -1542.20544, 21.02310, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1891.49805, -1528.99634, 21.03990, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1898.05322, -1556.71436, 21.01820, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1884.76355, -1577.26062, 21.03550, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1897.63245, -1615.31433, 21.04170, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1932.91064, -1649.40674, 21.04260, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1920.66638, -1692.76965, 21.02410, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1862.81482, -1666.73816, 21.03100, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1830.24255, -1695.15222, 21.02890, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1803.41187, -1684.49023, 21.54210, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1744.65039, -1652.63904, 21.12640, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1834.84741, -1644.62366, 21.03220, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-1839.35400, -1611.03931, 21.02780, 0.00000}}
};

enum E_FARM_RESOURCES_INFO
{
	fStatus, // 0 - нет, 1 - лен, 2 - хлопок;
	fItemsIDx, // ID ресурса из массива ItemsInfo;
	fCount, // Количество ресурса;
	fObject, // Обеъект;
	fArea, // Зона;
	Text3D:fText, // 3D текст;
	Float:fPos[4] // Координаты;
}
new FarmResourcesInfo[MAX_FARM_RESOURCES][E_FARM_RESOURCES_INFO] = {
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-227.05200, -70.40900, 5.53900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-197.51840, -58.27380, 5.43900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-172.41811, -39.09140, 5.43900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-211.08960, -28.02000, 5.51900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-243.94540, -42.59820, 5.51900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-256.33261, -11.28570, 4.61900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-225.36478, 5.45631, 5.49900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-241.27690, 35.92800, 4.57900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-179.83490, -9.89400, 5.43900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-153.85471, 9.33030, 5.43900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-191.79120, 25.66280, 5.47900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-208.30940, 55.93610, 5.47900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-223.77209, 85.77260, 4.47900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-176.23720, 71.81140, 5.49900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-162.02280, 40.00020, 5.47900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-136.07100, 55.05260, 5.49900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-124.56650, 112.19470, 5.30000, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-159.53481, 124.77450, 5.78000, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-129.40359, 147.32730, 5.60000, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-171.53999, 165.42101, 8.19900, 0.00000}},
	{0, 0, 10, INVALID_OBJECT_ID, -1, Text3D:INVALID_3DTEXT_ID, {-198.72951, 144.03580, 6.01900, 0.00000}}
};

LoadResources()
{
	// Шахта;
	CreateActor(27, -1866.9058,-1632.0995,21.8328,180.2282);
	CreateDynamic3DTextLabel("NPC: "I"Владелец шахты", COLOR_WHITE, -1866.9058,-1632.0995,21.8328 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

	resources_area[0] = CreateDynamicSphere(-1866.8885,-1632.8000,21.7564, 2.5, -1, -1, -1);
	//UpdateAreaInfo(resources_area[0], TYPE_RESOURCES, AREA_SUBTYPE_RESOURCES_A_MINE);
	CreatePickup(18631, 23, -1866.8885,-1632.8000,21.7564);
	CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, -1866.8885,-1632.8000,21.7564, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

	// Ферма;
	CreateActor(34, -80.5917,82.8267,3.1096,64.2939);
	CreateDynamic3DTextLabel("NPC: "I"Владелец фермы", COLOR_WHITE, -80.5917,82.8267,3.1096 + 1.3, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

	resources_area[1] = CreateDynamicSphere(-81.2511,83.0683,3.1172, 2.5, -1, -1, -1);
	//UpdateAreaInfo(resources_area[1], TYPE_RESOURCES, AREA_SUBTYPE_RESOURCES_A_FARM);
	CreatePickup(18631, 23, -81.2511,83.0683,3.1172);
	CreateDynamic3DTextLabel("Нажмите \"ALT\"", COLOR_MAIN, -81.2511,83.0683,3.1172, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);

	// Остальное;
	CheckResources(RESOURCES_TYPE_MINE);
	CheckResources(RESOURCES_TYPE_FARM);

	// Грядки на ферме;
	CreateDynamicObject(16317, -136.07100, 55.05260, 1.99900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -162.02280, 40.00020, 1.97900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -153.85471, 9.33030, 1.93900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -179.83495, -9.89401, 1.93900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -172.41811, -39.09140, 1.93900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -197.51840, -58.27375, 1.93900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -211.08960, -28.01997, 2.01900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -191.79120, 25.66280, 1.97900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -176.23720, 71.81140, 1.99900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -208.30940, 55.93610, 1.97900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -225.38319, 5.44846, 1.99900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -243.94543, -42.59819, 2.01900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -227.05202, -70.40902, 2.03900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -223.77209, 85.77260, 0.97900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -241.27686, 35.92799, 1.07900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -256.33261, -11.28568, 1.11900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -124.56650, 112.19470, 1.80000, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -129.40361, 147.32735, 2.10000, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -159.53481, 124.77450, 2.28000, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -171.53999, 165.42101, 4.69900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	CreateDynamicObject(16317, -198.72951, 144.03580, 2.51900, 0.00000, 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
	return 1;
}

CreateResources(type, idx)
{
	switch(type)
	{
		case RESOURCES_TYPE_MINE:
		{
			if(MineResourcesInfo[idx][mStatus] == 1) return 1;
			new items_list[3] = {649, 650, 651}, items_idx = items_list[random(sizeof(items_list))];
			MineResourcesInfo[idx][mStatus] = 1;
			MineResourcesInfo[idx][mItemsIDx] = items_idx;
			MineResourcesInfo[idx][mCount] = 1;
			MineResourcesInfo[idx][mObject] = CreateDynamicObject(849, MineResourcesInfo[idx][mPos][0], MineResourcesInfo[idx][mPos][1], MineResourcesInfo[idx][mPos][2], MineResourcesInfo[idx][mPos][3], 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
			MineResourcesInfo[idx][mArea] = CreateDynamicSphere(MineResourcesInfo[idx][mPos][0], MineResourcesInfo[idx][mPos][1], MineResourcesInfo[idx][mPos][2], 2.5);
			UpdateAreaInfo(MineResourcesInfo[idx][mArea], TYPE_RESOURCES, AREA_SUBTYPE_RESOURCES_MINE, idx);
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, "%s\nДля добычи ископаемого\nНажмите "W"\"ALT\"", ItemsInfo[items_idx][iName]);
			MineResourcesInfo[idx][mText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, MineResourcesInfo[idx][mPos][0], MineResourcesInfo[idx][mPos][1], MineResourcesInfo[idx][mPos][2]+1, 4.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
		}
		case RESOURCES_TYPE_FARM:
		{
			if(FarmResourcesInfo[idx][fStatus] == 1) return 1;
			if(FarmResourcesInfo[idx][fObject] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmResourcesInfo[idx][fObject]);
			if(FarmResourcesInfo[idx][fArea] != -1) DestroyDynamicArea(FarmResourcesInfo[idx][fArea]);
			if(FarmResourcesInfo[idx][fText] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(FarmResourcesInfo[idx][fText]);
			new items_idx = random(2) == 0 ? 647 : 648;
			FarmResourcesInfo[idx][fStatus] = 1;
			FarmResourcesInfo[idx][fItemsIDx] = items_idx;
			FarmResourcesInfo[idx][fCount] = MAX_FARM_RESOURCES_COUNT;
			FarmResourcesInfo[idx][fObject] = CreateDynamicObject(ItemsInfo[items_idx][iModel], FarmResourcesInfo[idx][fPos][0], FarmResourcesInfo[idx][fPos][1], FarmResourcesInfo[idx][fPos][2], FarmResourcesInfo[idx][fPos][3], 0.00000, 0.00000, -1, -1, -1, 300.00, 300.00);
			FarmResourcesInfo[idx][fArea] = CreateDynamicSphere(FarmResourcesInfo[idx][fPos][0], FarmResourcesInfo[idx][fPos][1], FarmResourcesInfo[idx][fPos][2], 2.5, -1, -1, -1);
			UpdateAreaInfo(FarmResourcesInfo[idx][fArea], TYPE_RESOURCES, AREA_SUBTYPE_RESOURCES_FARM, idx);
			STRING_GLOBAL[0] = EOS;
			f(STRING_GLOBAL, "%s ("W"%d"I" из "W"%d"I")\nДля сбора урожая\nНажмите "W"\"ALT\"", ItemsInfo[items_idx][iName], FarmResourcesInfo[idx][fCount], MAX_FARM_RESOURCES_COUNT);
			FarmResourcesInfo[idx][fText] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, FarmResourcesInfo[idx][fPos][0], FarmResourcesInfo[idx][fPos][1], FarmResourcesInfo[idx][fPos][2]+1, 5.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);
		}
	}
	return 1;
}

DestroyResources(type, idx)
{
	switch(type)
	{
		case RESOURCES_TYPE_MINE:
		{
			if(MineResourcesInfo[idx][mStatus] == 0) return 1;
			DestroyDynamicObject(MineResourcesInfo[idx][mObject]);
			DestroyDynamicArea(MineResourcesInfo[idx][mArea]);
			DestroyDynamic3DTextLabel(MineResourcesInfo[idx][mText]);
			MineResourcesInfo[idx][mStatus] = 0;
			MineResourcesInfo[idx][mItemsIDx] = 0;
			MineResourcesInfo[idx][mObject] = INVALID_OBJECT_ID;
			MineResourcesInfo[idx][mArea] = -1;
			MineResourcesInfo[idx][mText] = INVALID_3DTEXT_ID;
		}
		case RESOURCES_TYPE_FARM:
		{
			if(FarmResourcesInfo[idx][fStatus] == 0) return 1;
			if(FarmResourcesInfo[idx][fObject] != INVALID_OBJECT_ID) DestroyDynamicObject(FarmResourcesInfo[idx][fObject]);
			if(FarmResourcesInfo[idx][fArea] != -1) DestroyDynamicArea(FarmResourcesInfo[idx][fArea]);
			if(FarmResourcesInfo[idx][fText] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(FarmResourcesInfo[idx][fText]);
			FarmResourcesInfo[idx][fStatus] = 0;
			FarmResourcesInfo[idx][fObject] = INVALID_OBJECT_ID;
			FarmResourcesInfo[idx][fArea] = -1;
			FarmResourcesInfo[idx][fText] = INVALID_3DTEXT_ID;
		}
	}
	return 1;
}

CheckResources(type)
{
	switch(type)
	{
		case RESOURCES_TYPE_MINE:
		{
			for(new i = 0; i < MAX_MINE_RESOURCES; i++)
			{
				if(MineResourcesInfo[i][mStatus] == 1) continue;
				if(random(4) == 1) continue;
				CreateResources(type, i);
			}
		}
		case RESOURCES_TYPE_FARM:
		{
			for(new i = 0; i < MAX_FARM_RESOURCES; i++)
			{
				if(FarmResourcesInfo[i][fStatus] == 1) continue;
				CreateResources(type, i);
			}
		}
	}
	return 1;
}

CheckResourcesShovel(playerid)
{
	for(new i = p_info[playerid][inv_slots]-1; i != -1; i--)
	{
		if(InventoryPlayer[playerid][i][inv_mysql_id] != INVALID_MYSQL_ID &&
			ItemsInfo[InventoryPlayer[playerid][i][inv_item_id]][iType] == TYPE_ITEMS_ACCESSORIES &&
			InventoryPlayer[playerid][i][inv_status_use] > 0 && InventoryPlayer[playerid][i][inv_item_id] == 508)
		{
			return InventoryPlayer[playerid][i][inv_item_id];
		}
	}
	return -1;
}