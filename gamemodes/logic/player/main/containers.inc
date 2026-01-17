#define MAX_CONTAINERS			6
#define MAX_CONTAINERS_TYPE		3
#define MAX_CONTAINERS_ITEMS	6
#define MAX_CONTAINERS_PRIZE	6

enum
{
	CONTAINERS_STATUS_EMPTY,
	CONTAINERS_STATUS_CREATED,
	CONTAINERS_STATUS_AUCTION,
	CONTAINERS_STATUS_PRIZE
}

enum
{
	CONTAINERS_TYPE_NONE,
	CONTAINERS_TYPE_BRONZE,
	CONTAINERS_TYPE_SILVER,
	CONTAINERS_TYPE_GOLD
}

enum E_CONTAINERS_TYPE_INFO
{
	ctName[64],
	ctPrice,
	ctColor
}

new ContainersTypeInfo[MAX_CONTAINERS_TYPE][E_CONTAINERS_TYPE_INFO] = {
	{"Bronze", 500000, 0xFFCD7F32},
	{"Silver", 2000000, 0xFFC0C0C0},
	{"Gold", 5000000, 0xFFFFD700}
};

enum E_CONTAINERS_INFO
{
	cStatus,
	cType,
	cItems[MAX_CONTAINERS_ITEMS],
	cItemsCount[MAX_CONTAINERS_ITEMS],
	cItemsIDx[MAX_CONTAINERS_ITEMS],
	cTime,
	cPrice,
	cBet,
	cPlayerID,
	cPlayerName[32],
	cObject[4],
	Text3D:cText[2],
	cPickup,
	cArea,
	cCreatedTime
}

new ContainersInfo[MAX_CONTAINERS][E_CONTAINERS_INFO];

new Float:ContainersPos[MAX_CONTAINERS][24] = {
	{1013.419006, -1940.053344, 13.643099, 0.000000, 0.000000, 90.000000,	1016.937011, -1941.598022, 13.583103, 0.000000, 0.000000, 90.000000,	1016.936401, -1938.472534, 13.693103, 0.000000, 180.000000, 90.000000, 1016.989501, -1940.053344, 13.643098, 0.000007, -0.000007, 179.999923},
	{1013.419006, -1946.053344, 13.643099, 0.000000, 0.000000, 90.000000,	1016.937011, -1947.598022, 13.583103, 0.000000, 0.000000, 90.000000,	1016.936401, -1944.472534, 13.693103, 0.000000, 180.000000, 90.000000, 1016.989501, -1946.053344, 13.643098, 0.000007, -0.000007, 179.999923},
	{1013.419006, -1952.053344, 13.643099, 0.000000, 0.000000, 90.000000,	1016.937011, -1953.598022, 13.583103, 0.000000, 0.000000, 90.000000,	1016.936401, -1950.472534, 13.693103, 0.000000, 180.000000, 90.000000, 1016.989501, -1952.053344, 13.643098, 0.000007, -0.000007, 179.999923},
	{1013.419006, -1958.053344, 13.643099, 0.000000, 0.000000, 90.000000,	1016.937011, -1959.598022, 13.583103, 0.000000, 0.000000, 90.000000,	1016.936401, -1956.472534, 13.693103, 0.000000, 180.000000, 90.000000, 1016.989501, -1958.053344, 13.643098, 0.000007, -0.000007, 179.999923},
	{1013.419006, -1964.053344, 13.643099, 0.000000, 0.000000, 90.000000,	1016.937011, -1965.598022, 13.583103, 0.000000, 0.000000, 90.000000,	1016.936401, -1962.472534, 13.693103, 0.000000, 180.000000, 90.000000, 1016.989501, -1964.053344, 13.643098, 0.000007, -0.000007, 179.999923},
	{1013.419006, -1970.053344, 13.643099, 0.000000, 0.000000, 90.000000,	1016.937011, -1971.598022, 13.583103, 0.000000, 0.000000, 90.000000,	1016.936401, -1968.472534, 13.693103, 0.000000, 180.000000, 90.000000, 1016.989501, -1970.053344, 13.643098, 0.000007, -0.000007, 179.999923}
};

LoadContainers()
{
	new tmpobjid;

	tmpobjid = CreateDynamicObject(19791, 1033.136596, -1940.531738, 12.101092, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1032.857788, -1950.527832, 12.101086, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1032.578369, -1960.523925, 12.101094, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1032.298950, -1970.520019, 12.101091, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1023.140625, -1940.252563, 12.101082, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1022.861389, -1950.248657, 12.101092, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(11292, 1013.410827, -1946.343627, 10.593071, 0.000006, 0.000023, -0.000059, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 3621, "dockcargo1_las", "lasdkcrtgr11", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 18029, "genintintsmallrest", "GB_restaursmll03", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751220, -1947.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751342, -1944.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1022.582275, -1960.244750, 12.101086, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1022.302917, -1970.240844, 12.101092, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1013.144531, -1939.973388, 12.101086, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1012.865295, -1949.969604, 12.101094, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1012.586181, -1959.965698, 12.101087, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1012.306823, -1969.961669, 12.101084, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 4562, "plaza1_lan2", "sl_blokpave1", 0x00000000);
	tmpobjid = CreateDynamicObject(9339, 1025.226074, -1935.427734, 12.464825, -0.000009, 0.000000, -91.599853, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 630, "gta_potplants", "greekurn", 0x00000000);
	tmpobjid = CreateDynamicObject(9339, 1021.327209, -1935.320678, 12.462817, -0.000009, 0.000000, -91.599853, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 630, "gta_potplants", "greekurn", 0x00000000);
	tmpobjid = CreateDynamicObject(9339, 1008.045043, -1947.888671, 12.464818, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 630, "gta_potplants", "greekurn", 0x00000000);
	tmpobjid = CreateDynamicObject(9339, 1007.655151, -1961.776123, 12.466826, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 630, "gta_potplants", "greekurn", 0x00000000);
	tmpobjid = CreateDynamicObject(9339, 1024.115600, -1975.177978, 12.464823, -0.000017, 0.000000, -91.599853, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 630, "gta_potplants", "greekurn", 0x00000000);
	tmpobjid = CreateDynamicObject(9339, 1020.217163, -1975.065063, 12.462817, -0.000017, 0.000000, -91.599853, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 630, "gta_potplants", "greekurn", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751220, -1947.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751342, -1944.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(11292, 1013.410827, -1952.343627, 10.593071, 0.000006, 0.000023, -0.000059, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 3621, "dockcargo1_las", "lasdkcrtgr11", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 18029, "genintintsmallrest", "GB_restaursmll03", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751220, -1953.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751342, -1950.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751220, -1953.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751342, -1950.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(11292, 1013.410827, -1958.343627, 10.593071, 0.000006, 0.000023, -0.000059, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 3621, "dockcargo1_las", "lasdkcrtgr11", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 18029, "genintintsmallrest", "GB_restaursmll03", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751220, -1959.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751342, -1956.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(13646, 1026.865722, -1944.440673, 11.591078, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 5704, "melrose07_lawn", "ws_conc_step1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 5462, "glenpark6_lae", "dirty256", 0x00000000);
	tmpobjid = CreateDynamicObject(984, 1037.307250, -1969.026000, 12.511774, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 7, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 8, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 9, 18878, "ferriswheel", "railing3", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(984, 1038.053100, -1942.323608, 12.511770, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 7, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 8, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 9, 18878, "ferriswheel", "railing3", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(3785, 1017.751220, -1959.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751342, -1956.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(13646, 1026.865722, -1955.440673, 11.591078, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 5704, "melrose07_lawn", "ws_conc_step1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 5462, "glenpark6_lae", "dirty256", 0x00000000);
	tmpobjid = CreateDynamicObject(19740, 1026.184814, -1955.421752, 6.271060, -0.000000, 90.000030, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 3906, "libertyhi5", "walldirtynewa256128", 0x00000000);
	tmpobjid = CreateDynamicObject(19740, 1027.558715, -1955.459960, 6.271055, -0.000000, 270.000000, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 3906, "libertyhi5", "walldirtynewa256128", 0x00000000);
	tmpobjid = CreateDynamicObject(984, 1037.398315, -1965.835083, 12.511769, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 7, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 8, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 9, 18878, "ferriswheel", "railing3", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(984, 1037.965942, -1945.515258, 12.511762, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 7, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 8, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 9, 18878, "ferriswheel", "railing3", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(11292, 1013.410827, -1964.343627, 10.593071, 0.000006, 0.000023, -0.000059, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 3621, "dockcargo1_las", "lasdkcrtgr11", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 18029, "genintintsmallrest", "GB_restaursmll03", 0x00000000);
	tmpobjid = CreateDynamicObject(2791, 1036.443603, -1933.819580, 10.201054, -0.000018, 0.000019, -19.999937, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 2, 1560, "7_11_door", "CJ_CHROME2", 0x00000000);
	tmpobjid = CreateDynamicObject(975, 1036.321289, -1933.775146, 11.971062, -0.000018, 90.000022, -19.999937, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 10763, "airport1_sfse", "ws_yelloscaff", 0xFF2F4F4F);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(13646, 1036.443603, -1933.819580, 17.711076, -89.999992, 123.163085, 103.163063, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19800, "lsacarpark1", "dt_officewall1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14846, "genintintpoliceb", "p_floor3", 0x00000000);
	tmpobjid = CreateDynamicObject(13646, 1036.443603, -1933.819580, 17.709075, -89.999992, -56.836883, 103.163063, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19800, "lsacarpark1", "dt_officewall1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14846, "genintintpoliceb", "p_floor3", 0x00000000);
	tmpobjid = CreateDynamicObject(3078, 1036.220581, -1934.430908, 17.711076, 89.999992, 51.628791, -71.628791, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterialText(tmpobjid, 0, "CONTAINER AUCTION", 120, "Arial Narrow", 40, 1, 0xFFFFFFFF, 0x00000000, 1);
	tmpobjid = CreateDynamicObject(19866, 1036.261840, -1934.317749, 17.331068, -0.000019, -0.000018, -109.999809, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19800, "lsacarpark1", "dt_officewall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19759, 1036.292846, -1934.233520, 17.081056, -0.000019, 89.999984, -109.999809, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19800, "lsacarpark1", "dt_officewall1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_fluorescent2", 0x00000000);
	tmpobjid = CreateDynamicObject(3078, 1036.666137, -1933.208374, 17.711076, 89.999992, -123.163093, -76.836898, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterialText(tmpobjid, 0, "CONTAINER AUCTION", 120, "Arial Narrow", 40, 1, 0xFFFFFFFF, 0x00000000, 1);
	tmpobjid = CreateDynamicObject(19866, 1036.624877, -1933.321533, 17.331068, 0.000019, 0.000018, 69.999984, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19800, "lsacarpark1", "dt_officewall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19759, 1036.593872, -1933.405761, 17.081056, 0.000019, 90.000015, 69.999984, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19800, "lsacarpark1", "dt_officewall1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_fluorescent2", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1029.464599, -1955.513305, 12.771091, 0.000029, 0.000000, 88.399780, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1024.267456, -1955.348144, 12.771087, -0.000031, -0.000000, -91.599784, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1026.948852, -1952.822143, 12.771092, 0.000000, -0.000029, 178.399566, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1026.784057, -1958.019409, 12.771088, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(760, 1026.869995, -1955.362915, 12.261079, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush4", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751220, -1965.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751342, -1962.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751220, -1965.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751342, -1962.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(11292, 1013.410827, -1970.343627, 10.593071, 0.000006, 0.000023, -0.000059, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 3621, "dockcargo1_las", "lasdkcrtgr11", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 18029, "genintintsmallrest", "GB_restaursmll03", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751220, -1971.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751342, -1968.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(11292, 1013.410827, -1940.343627, 10.593071, 0.000006, 0.000023, -0.000059, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 3621, "dockcargo1_las", "lasdkcrtgr11", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 6, 18029, "genintintsmallrest", "GB_restaursmll03", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751220, -1941.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1017.751342, -1938.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 1, 18757, "vcinteriors", "metalplate9", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751220, -1941.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751342, -1938.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(19740, 1026.184814, -1944.421752, 6.271060, -0.000000, 90.000030, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 3906, "libertyhi5", "walldirtynewa256128", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751220, -1971.930541, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(19740, 1027.558715, -1944.459960, 6.271055, -0.000000, 270.000000, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 3906, "libertyhi5", "walldirtynewa256128", 0x00000000);
	tmpobjid = CreateDynamicObject(3785, 1017.751342, -1968.128295, 12.191089, 0.000023, 180.000000, 89.999763, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1029.464599, -1944.513305, 12.771091, 0.000029, 0.000000, 88.399780, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1012.286804, -1969.981689, 11.761077, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10755, "airportrminl_sfse", "ws_airportconc1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1012.566101, -1959.985351, 11.761077, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10755, "airportrminl_sfse", "ws_airportconc1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1012.845581, -1949.990234, 11.761077, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10755, "airportrminl_sfse", "ws_airportconc1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1013.125732, -1939.962158, 11.761077, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10755, "airportrminl_sfse", "ws_airportconc1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1023.121704, -1940.241943, 11.761077, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10755, "airportrminl_sfse", "ws_airportconc1", 0x00000000);
	tmpobjid = CreateDynamicObject(19791, 1013.067321, -1942.411865, 11.761077, 0.000000, 180.000000, -1.600005, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10755, "airportrminl_sfse", "ws_airportconc1", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1024.267456, -1944.348144, 12.771087, -0.000031, -0.000000, -91.599784, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1026.948852, -1941.822143, 12.771092, 0.000000, -0.000029, 178.399566, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1026.784057, -1947.019409, 12.771088, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(760, 1026.869995, -1944.362915, 12.261079, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush4", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);
	tmpobjid = CreateDynamicObject(13646, 1026.865722, -1966.440673, 11.591078, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 5704, "melrose07_lawn", "ws_conc_step1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 5462, "glenpark6_lae", "dirty256", 0x00000000);
	tmpobjid = CreateDynamicObject(19740, 1026.184814, -1966.421752, 6.271060, -0.000000, 90.000030, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 3906, "libertyhi5", "walldirtynewa256128", 0x00000000);
	tmpobjid = CreateDynamicObject(19740, 1027.558715, -1966.459960, 6.271055, -0.000000, 270.000000, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 3906, "libertyhi5", "walldirtynewa256128", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1029.464599, -1966.513305, 12.771091, 0.000029, 0.000000, 88.399780, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1024.267456, -1966.348144, 12.771087, -0.000031, -0.000000, -91.599784, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(1368, 1026.948852, -1963.822143, 12.771092, 0.000000, -0.000029, 178.399566, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 1355, "break_s_bins", "CJ_WOOD_DARK", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 14653, "ab_trukstpb", "met_supp", 0x00000000);
	tmpobjid = CreateDynamicObject(760, 1026.869995, -1966.362915, 12.261079, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 825, "gta_proc_bigbush", "veg_bush4", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 825, "gta_proc_bigbush", "veg_bush1", 0x00000000);

	tmpobjid = CreateDynamicObject(1231, 1015.164367, -1967.073974, 14.811098, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1231, 1015.164367, -1943.083862, 14.811098, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1216, 1033.023071, -1936.361938, 12.771102, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1216, 1034.022949, -1936.389770, 12.771100, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1216, 1035.022583, -1936.417724, 12.771100, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1285, 1037.592651, -1945.135986, 12.631085, 0.000007, 0.000000, 88.399848, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1286, 1037.606567, -1944.636230, 12.631089, 0.000007, 0.000000, 88.399848, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1289, 1037.620605, -1944.136474, 12.631081, 0.000007, 0.000000, 88.399848, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(792, 1034.504272, -1939.473999, 12.271087, 0.000000, 0.000014, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(792, 1033.604125, -1971.641845, 12.271086, 0.000000, 0.000014, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1359, 1037.311645, -1950.585449, 12.731095, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(19121, 1037.455200, -1959.095458, 12.622982, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(19121, 1037.503173, -1957.386108, 12.622982, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(19121, 1037.550903, -1955.677001, 12.622989, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(19121, 1037.598754, -1953.967529, 12.622984, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(19121, 1037.646484, -1952.258300, 12.622982, 0.000000, 0.000007, -1.600005, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(737, 1026.865722, -1955.440673, 12.211072, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(1231, 1015.164367, -1955.082885, 14.811098, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(737, 1026.865722, -1944.440673, 12.211072, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);
	tmpobjid = CreateDynamicObject(737, 1026.865722, -1966.440673, 12.211072, -0.000000, 0.000029, -1.600004, -1, -1, -1, 120.00, 120.00);

	for(new i = 0; i < MAX_CONTAINERS; i++)
	{
		ContainersInfo[i][cObject][0] = INVALID_OBJECT_ID;
		ContainersInfo[i][cObject][1] = INVALID_OBJECT_ID;
		ContainersInfo[i][cObject][2] = INVALID_OBJECT_ID;
		ContainersInfo[i][cObject][3] = INVALID_OBJECT_ID;
		ContainersInfo[i][cText][1] = INVALID_3DTEXT_ID;
		ContainersInfo[i][cArea] = -1;
		ContainersInfo[i][cItems][0] =
		ContainersInfo[i][cItems][1] =
		ContainersInfo[i][cItems][2] =
		ContainersInfo[i][cItems][3] =
		ContainersInfo[i][cItems][4] =
		ContainersInfo[i][cItems][5] = 0;
		ContainersInfo[i][cItemsCount][0] =
		ContainersInfo[i][cItemsCount][1] =
		ContainersInfo[i][cItemsCount][2] =
		ContainersInfo[i][cItemsCount][3] =
		ContainersInfo[i][cItemsCount][4] =
		ContainersInfo[i][cItemsCount][5] = 0;
		ContainersInfo[i][cItemsIDx][0] =
		ContainersInfo[i][cItemsIDx][1] =
		ContainersInfo[i][cItemsIDx][2] =
		ContainersInfo[i][cItemsIDx][3] =
		ContainersInfo[i][cItemsIDx][4] =
		ContainersInfo[i][cItemsIDx][5] = 0;
		ContainersInfo[i][cPickup] = -1;

		ContainersInfo[i][cText][0] = CreateDynamic3DTextLabel("На этом месте проходит аукцион контейнеров", COLOR_MAIN, ContainersPos[i][0], ContainersPos[i][1], ContainersPos[i][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);
	}
	return 1;
}

CreateContainers(idx)
{
	if(ContainersInfo[idx][cStatus] != CONTAINERS_STATUS_EMPTY) return 1;

	new type = 0;
	switch(random(100))
	{
		case 0..45: type = 0;
		case 46..75: type = 1;
		case 76..99: type = 2;
	}

	ContainersInfo[idx][cStatus] = CONTAINERS_STATUS_CREATED;
	ContainersInfo[idx][cType] = type+1;
	ContainersInfo[idx][cItems][0] =
	ContainersInfo[idx][cItems][1] =
	ContainersInfo[idx][cItems][2] =
	ContainersInfo[idx][cItems][3] =
	ContainersInfo[idx][cItems][4] =
	ContainersInfo[idx][cItems][5] = 0;
	ContainersInfo[idx][cItemsCount][0] =
	ContainersInfo[idx][cItemsCount][1] =
	ContainersInfo[idx][cItemsCount][2] =
	ContainersInfo[idx][cItemsCount][3] =
	ContainersInfo[idx][cItemsCount][4] =
	ContainersInfo[idx][cItemsCount][5] = 0;
	ContainersInfo[idx][cItemsIDx][0] =
	ContainersInfo[idx][cItemsIDx][1] =
	ContainersInfo[idx][cItemsIDx][2] =
	ContainersInfo[idx][cItemsIDx][3] =
	ContainersInfo[idx][cItemsIDx][4] =
	ContainersInfo[idx][cItemsIDx][5] = 0;
	ContainersInfo[idx][cTime] = 600;
	ContainersInfo[idx][cPrice] = ContainersTypeInfo[type][ctPrice];
	ContainersInfo[idx][cBet] = 0;
	ContainersInfo[idx][cPlayerID] = 0;
	strmid(ContainersInfo[idx][cPlayerName], "None", 0, strlen("None"), MAX_PLAYER_NAME);
	if(ContainersInfo[idx][cPickup] != -1) DestroyDynamicPickup(ContainersInfo[idx][cPickup]);
	ContainersInfo[idx][cPickup] = -1;
	ContainersInfo[idx][cCreatedTime] = timestamp + idx;

	if(ContainersInfo[idx][cObject][0] != INVALID_OBJECT_ID) DestroyDynamicObject(ContainersInfo[idx][cObject][0]);
	ContainersInfo[idx][cObject][0] = CreateDynamicObject(19321, ContainersPos[idx][0], ContainersPos[idx][1], ContainersPos[idx][2], ContainersPos[idx][3], ContainersPos[idx][4], ContainersPos[idx][5], -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(ContainersInfo[idx][cObject][0], 0, 3621, "dockcargo1_las", "sjmpostback", ContainersTypeInfo[type][ctColor]);
	SetDynamicObjectMaterial(ContainersInfo[idx][cObject][0], 1, 3564, "dockcargo2_las", "lastrk5", ContainersTypeInfo[type][ctColor]);

	if(ContainersInfo[idx][cObject][1] != INVALID_OBJECT_ID) DestroyDynamicObject(ContainersInfo[idx][cObject][1]);
	ContainersInfo[idx][cObject][1] = CreateDynamicObject(3062, ContainersPos[idx][6], ContainersPos[idx][7], ContainersPos[idx][8], ContainersPos[idx][9], ContainersPos[idx][10], ContainersPos[idx][11], -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(ContainersInfo[idx][cObject][1], 0, 3564, "dockcargo2_las", "lastrk5", ContainersTypeInfo[type][ctColor]);

	if(ContainersInfo[idx][cObject][2] != INVALID_OBJECT_ID) DestroyDynamicObject(ContainersInfo[idx][cObject][2]);
	ContainersInfo[idx][cObject][2] = CreateDynamicObject(3062, ContainersPos[idx][12], ContainersPos[idx][13], ContainersPos[idx][14], ContainersPos[idx][15], ContainersPos[idx][16], ContainersPos[idx][17], -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(ContainersInfo[idx][cObject][2], 0, 3564, "dockcargo2_las", "lastrk5", ContainersTypeInfo[type][ctColor]);

	if(ContainersInfo[idx][cObject][3] != INVALID_OBJECT_ID) DestroyDynamicObject(ContainersInfo[idx][cObject][3]);
	ContainersInfo[idx][cObject][3] = CreateDynamicObject(19353, ContainersPos[idx][18], ContainersPos[idx][19], ContainersPos[idx][20], ContainersPos[idx][21], ContainersPos[idx][22], ContainersPos[idx][23], -1, -1, -1, 120.00, 120.00);
	SetDynamicObjectMaterial(ContainersInfo[idx][cObject][3], 0, 19962, "samproadsigns", "materialtext1", 0xFFFFFFFF);
	SetDynamicObjectMaterial(ContainersInfo[idx][cObject][3], 1, 3564, "dockcargo2_las", "lastrk5", 0xFFFFFFFF);

	STRING_GLOBAL[0] = EOS;
	format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Аукцион контейнеров\n\n"W"Номер: "I"%d"W"\nТип: "I"%s"W"\nГос. стоимость: "I"%d$"W"\nСтавка: "I"%d$"W"\n\n%s: "I"%s\n\n"W"Установить ставку: "I"ALT или /auction",
		idx+1, ContainersTypeInfo[type][ctName], ContainersInfo[idx][cPrice], ContainersInfo[idx][cBet], (ContainersInfo[idx][cStatus] == CONTAINERS_STATUS_AUCTION) ? ("Время до окончания аукциона") : ("Время до исчезновения контейнера"), ConvertTime(ContainersInfo[idx][cTime], 1));

	if(ContainersInfo[idx][cText][0] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(ContainersInfo[idx][cText][0]);
	ContainersInfo[idx][cText][0] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, ContainersPos[idx][0], ContainersPos[idx][1], ContainersPos[idx][2] + 2.5, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);

	if(ContainersInfo[idx][cArea] != -1) DestroyDynamicArea(ContainersInfo[idx][cArea]);
	ContainersInfo[idx][cArea] = CreateDynamicSphere(ContainersPos[idx][0], ContainersPos[idx][1], ContainersPos[idx][2], 5.0);
	UpdateAreaInfo(ContainersInfo[idx][cArea], TYPE_CONTAINERS, AREA_SUBTYPE_INVALID_ID, idx);

	if(ContainersInfo[idx][cText][1] != INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(ContainersInfo[idx][cText][1]);
		ContainersInfo[idx][cText][1] = INVALID_3DTEXT_ID;
	}
	return 1;
}

DestroyContainers(idx)
{
	if(ContainersInfo[idx][cStatus] == CONTAINERS_STATUS_EMPTY) return 1;
	ContainersInfo[idx][cStatus] = CONTAINERS_STATUS_EMPTY;
	if(ContainersInfo[idx][cObject][0] != INVALID_OBJECT_ID)
	{
		DestroyDynamicObject(ContainersInfo[idx][cObject][0]);
		ContainersInfo[idx][cObject][0] = INVALID_OBJECT_ID;
	}
	if(ContainersInfo[idx][cObject][1] != INVALID_OBJECT_ID)
	{
		DestroyDynamicObject(ContainersInfo[idx][cObject][1]);
		ContainersInfo[idx][cObject][1] = INVALID_OBJECT_ID;
	}
	if(ContainersInfo[idx][cObject][2] != INVALID_OBJECT_ID)
	{
		DestroyDynamicObject(ContainersInfo[idx][cObject][2]);
		ContainersInfo[idx][cObject][2] = INVALID_OBJECT_ID;
	}
	if(ContainersInfo[idx][cObject][3] != INVALID_OBJECT_ID)
	{
		DestroyDynamicObject(ContainersInfo[idx][cObject][3]);
		ContainersInfo[idx][cObject][3] = INVALID_OBJECT_ID;
	}
	if(ContainersInfo[idx][cArea] != -1)
	{
		DestroyDynamicArea(ContainersInfo[idx][cArea]);
		ContainersInfo[idx][cArea] = -1;
	}
	ContainersInfo[idx][cType] = 0;
	ContainersInfo[idx][cItems][0] =
	ContainersInfo[idx][cItems][1] =
	ContainersInfo[idx][cItems][2] =
	ContainersInfo[idx][cItems][3] =
	ContainersInfo[idx][cItems][4] =
	ContainersInfo[idx][cItems][5] = 0;
	ContainersInfo[idx][cItemsCount][0] =
	ContainersInfo[idx][cItemsCount][1] =
	ContainersInfo[idx][cItemsCount][2] =
	ContainersInfo[idx][cItemsCount][3] =
	ContainersInfo[idx][cItemsCount][4] =
	ContainersInfo[idx][cItemsCount][5] = 0;
	ContainersInfo[idx][cItemsIDx][0] =
	ContainersInfo[idx][cItemsIDx][1] =
	ContainersInfo[idx][cItemsIDx][2] =
	ContainersInfo[idx][cItemsIDx][3] =
	ContainersInfo[idx][cItemsIDx][4] =
	ContainersInfo[idx][cItemsIDx][5] = 0;
	ContainersInfo[idx][cTime] = 60;
	ContainersInfo[idx][cPrice] = 0;
	ContainersInfo[idx][cBet] = 0;
	ContainersInfo[idx][cPlayerID] = 0;
	strmid(ContainersInfo[idx][cPlayerName], "None", 0, strlen("None"), MAX_PLAYER_NAME);
	if(ContainersInfo[idx][cText][0] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(ContainersInfo[idx][cText][0]);
	ContainersInfo[idx][cText][0] = CreateDynamic3DTextLabel("На этом месте проходит аукцион контейнеров", COLOR_MAIN, ContainersPos[idx][0], ContainersPos[idx][1], ContainersPos[idx][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);
	if(ContainersInfo[idx][cText][1] != INVALID_3DTEXT_ID)
	{
		DestroyDynamic3DTextLabel(ContainersInfo[idx][cText][1]);
		ContainersInfo[idx][cText][1] = INVALID_3DTEXT_ID;
	}
	if(ContainersInfo[idx][cPickup] != -1)
	{
		DestroyDynamicPickup(ContainersInfo[idx][cPickup]);
		ContainersInfo[idx][cPickup] = -1;
	}
	ContainersInfo[idx][cCreatedTime] = 0;
	return 1;
}

CheckContainers(idx)
{
	switch(ContainersInfo[idx][cStatus])
	{
		case CONTAINERS_STATUS_EMPTY: 
		{
			if(ContainersInfo[idx][cTime] == 0) CreateContainers(idx);
			else
			{
				ContainersInfo[idx][cTime]--;
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Аукцион контейнеров\n\n"W"Время до появления контейнера: "I"%s"W"", ConvertTime(ContainersInfo[idx][cTime], 1));
				UpdateDynamic3DTextLabelText(ContainersInfo[idx][cText][0], COLOR_MAIN, STRING_GLOBAL);
			}
		}
		case CONTAINERS_STATUS_CREATED:
		{
			if(ContainersInfo[idx][cTime] == 0) DestroyContainers(idx);
			else
			{
				ContainersInfo[idx][cTime]--;
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Аукцион контейнеров\n\n"W"Номер: "I"%d"W"\nТип: "I"%s"W"\nГос. стоимость: "I"%d$"W"\nСтавка: "I"%d$"W"\n\n%s: "I"%s"W"\n\nУстановить ставку: "I"ALT или /auction",
				idx+1, ContainersTypeInfo[ContainersInfo[idx][cType] - 1][ctName], ContainersInfo[idx][cPrice], ContainersInfo[idx][cBet], (ContainersInfo[idx][cStatus] == CONTAINERS_STATUS_AUCTION) ? ("Время до окончания аукциона") : ("Время до исчезновения контейнера"), ConvertTime(ContainersInfo[idx][cTime], 1));
				UpdateDynamic3DTextLabelText(ContainersInfo[idx][cText][0], COLOR_MAIN, STRING_GLOBAL);
			}
		}
		case CONTAINERS_STATUS_AUCTION:
		{
			if(ContainersInfo[idx][cTime] == 0)
			{
				if(ContainersInfo[idx][cPlayerID] != 0)
				{
					GetContainersItem(idx, ContainersInfo[idx][cType]);
					if(GetPlayerUserID(ContainersInfo[idx][cPlayerID]) != INVALID_PLAYER_ID)
					{
						new scdplayerid = GetPlayerUserID(ContainersInfo[idx][cPlayerID]);
						SendAccess(scdplayerid, "Вы выиграли в аукционе контейнера #%d.", idx);
						SendInfo(scdplayerid, "У Вас есть 60 сек. чтобы забрать приз с контейнера.");
						SendInfo(scdplayerid, "Чтобы забрать приз нажмите ALT или введите /auction рядом с контейнером.");
						ContainersInfo[idx][cStatus] = CONTAINERS_STATUS_PRIZE;
						ContainersInfo[idx][cTime] = 60;
						if(ContainersInfo[idx][cObject][1] != INVALID_OBJECT_ID)
						{
							MoveDynamicObject(ContainersInfo[idx][cObject][1], ContainersPos[idx][6], ContainersPos[idx][7] - 1.55, ContainersPos[idx][8], 0.2, ContainersPos[idx][9], ContainersPos[idx][10], ContainersPos[idx][11]);
						}
						if(ContainersInfo[idx][cObject][2] != INVALID_OBJECT_ID)
						{
							MoveDynamicObject(ContainersInfo[idx][cObject][2], ContainersPos[idx][12], ContainersPos[idx][13] + 1.55, ContainersPos[idx][14], 0.2, ContainersPos[idx][15], ContainersPos[idx][16], ContainersPos[idx][17]);
						}
						if(ContainersInfo[idx][cPickup] != -1)
						{
							DestroyDynamicPickup(ContainersInfo[idx][cPickup]);
							ContainersInfo[idx][cPickup] = -1;
						}
						ContainersInfo[idx][cPickup] = CreateDynamicPickup(1239, 23, ContainersPos[idx][0], ContainersPos[idx][1], ContainersPos[idx][2]);
						if(ContainersInfo[idx][cText][1] != INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(ContainersInfo[idx][cText][1]);
						ContainersInfo[idx][cText][1] = CreateDynamic3DTextLabel(GetContainersPrize(idx), COLOR_WHITE, ContainersPos[idx][0], ContainersPos[idx][1], ContainersPos[idx][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID,streamer_TESTLOL, -1, -1, -1);
					}
					else
					{
						new items_idx, items_count;
						for(new i = 0; i < MAX_CONTAINERS_PRIZE; i++)
						{
							items_idx = ContainersInfo[idx][cItems][i];
							if(items_idx == 0) continue;
							items_count = ContainersInfo[idx][cItemsCount][i];
							SetPlayerItem(INVALID_PLAYER_ID, 8, ContainersInfo[idx][cPlayerID], items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]);
							Log(LOG_player, INFO, "%s[%d](OFFLINE) получил %s из контейнера за %d$ | #Containers",
							ContainersInfo[idx][cPlayerName], ContainersInfo[idx][cPlayerID], GetPrizeItemsName(items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]), ContainersInfo[idx][cBet]);
						}
						OnServerInfoForMoney[6] += ContainersInfo[idx][cBet];
						DestroyContainers(idx);
					}
				}
			}
			else
			{
				ContainersInfo[idx][cTime]--;
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Аукцион контейнеров\n\n"W"Номер: "I"%d"W"\nТип: "I"%s"W"\nГос. стоимость: "I"%d$"W"\nСтавка: "I"%d$"W"\n\n%s: "I"%s"W"\n\nУстановить ставку: "I"ALT или /auction",
				idx+1, ContainersTypeInfo[ContainersInfo[idx][cType] - 1][ctName], ContainersInfo[idx][cPrice], ContainersInfo[idx][cBet], (ContainersInfo[idx][cStatus] == CONTAINERS_STATUS_AUCTION) ? ("Время до окончания аукциона") : ("Время до исчезновения контейнера"), ConvertTime(ContainersInfo[idx][cTime], 1));
				UpdateDynamic3DTextLabelText(ContainersInfo[idx][cText][0], COLOR_MAIN, STRING_GLOBAL);
			}
		}
		case CONTAINERS_STATUS_PRIZE:
		{
			if(ContainersInfo[idx][cTime] == 0)
			{
				if(ContainersInfo[idx][cPlayerID] != 0)
				{
					if(GetPlayerUserID(ContainersInfo[idx][cPlayerID]) != INVALID_PLAYER_ID)
					{
						new scdplayerid = GetPlayerUserID(ContainersInfo[idx][cPlayerID]), items_idx, items_count;
						for(new i = 0; i < MAX_CONTAINERS_PRIZE; i++)
						{
							items_idx = ContainersInfo[idx][cItems][i];
							if(items_idx == 0) continue;
							items_count = ContainersInfo[idx][cItemsCount][i];
							SetPlayerItem(scdplayerid, 8, p_info[scdplayerid][ID], items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]);
							Log(LOG_player, INFO, "%s[%d] получил %s из контейнера за %d$ | #Containers",
							get_name(scdplayerid), p_info[scdplayerid][ID], GetPrizeItemsName(items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]), ContainersInfo[idx][cBet]);
						}
						OnServerInfoForMoney[6] += ContainersInfo[idx][cBet];
						DestroyContainers(idx);
					}
					else
					{
						new items_idx, items_count;
						for(new i = 0; i < MAX_CONTAINERS_PRIZE; i++)
						{
							items_idx = ContainersInfo[idx][cItems][i];
							if(items_idx == 0) continue;
							items_count = ContainersInfo[idx][cItemsCount][i];
							SetPlayerItem(INVALID_PLAYER_ID, 8, ContainersInfo[idx][cPlayerID], items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]);
							Log(LOG_player, INFO, "%s[%d](OFFLINE) получил %s из контейнера за %d$ | #Containers",
							ContainersInfo[idx][cPlayerName], ContainersInfo[idx][cPlayerID], GetPrizeItemsName(items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]), ContainersInfo[idx][cBet]);
						}
						OnServerInfoForMoney[6] += ContainersInfo[idx][cBet];
						DestroyContainers(idx);
					}
				}
			}
			else
			{
				ContainersInfo[idx][cTime]--;
				STRING_GLOBAL[0] = EOS;
				format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Аукцион контейнеров\n\n"W"Номер: "I"%d"W"\n"W"Тип: "I"%s"W"\nГос. стоимость: "I"%d$"W"\nСтавка: "I"%d$"W"\n\n%s: "I"%s"W"\n\nУстановить ставку: "I"ALT или /auction",
				idx+1, ContainersTypeInfo[ContainersInfo[idx][cType] - 1][ctName], ContainersInfo[idx][cPrice], ContainersInfo[idx][cBet], (ContainersInfo[idx][cStatus] == CONTAINERS_STATUS_AUCTION) ? ("Время до окончания аукциона") : ("Время до исчезновения контейнера"), ConvertTime(ContainersInfo[idx][cTime], 1));
				UpdateDynamic3DTextLabelText(ContainersInfo[idx][cText][0], COLOR_MAIN, STRING_GLOBAL);
			}
		}
	}
	return 1;	
}

GetContainersItem(idx, class)
{
	ContainersInfo[idx][cItems][0] = TYPE_GIVE_ITEM_EXP;
	ContainersInfo[idx][cItemsCount][0] = RandomEx(10, 15) * class;
	ContainersInfo[idx][cItems][1] = random(10) < 2 ? TYPE_GIVE_ITEM_DONATE : TYPE_GIVE_ITEM_MONEY;
	ContainersInfo[idx][cItems][2] = TYPE_GIVE_ITEM_VEHICLE;
	ContainersInfo[idx][cItems][3] = random(10) < class*4 ? TYPE_GIVE_ITEM_ACCESSORIES : 0;
	ContainersInfo[idx][cItems][4] = random(10) < class*4 ? TYPE_GIVE_ITEM_SKIN : 0;
	ContainersInfo[idx][cItems][5] = TYPE_GIVE_ITEM_INVENTORY;
	ContainersInfo[idx][cItemsCount][5] = 1;
	ContainersInfo[idx][cItemsIDx][5] = 643 + random(2);

	switch(class)
	{
		case CONTAINERS_TYPE_BRONZE:
		{
			if(ContainersInfo[idx][cItems][1] == TYPE_GIVE_ITEM_DONATE) ContainersInfo[idx][cItemsCount][1] = RandomEx(50, 100);
			else ContainersInfo[idx][cItemsCount][1] = RandomEx(200000, 400000);

			ContainersInfo[idx][cItemsCount][2] = GetContainersVehicle(VEHICLE_CLASS_NOPE);

			if(ContainersInfo[idx][cItems][3] != 0)
			{
				new accessories_containers_prize[29] = {476, 477, 478, 479, 480, 481, 482, 484, 485, 507, 516, 519, 520, 521, 523, 528, 530, 534, 537, 549, 585, 596, 598, 599, 600, 601, 602, 603, 607}; // 250000$;
				ContainersInfo[idx][cItemsCount][3] = accessories_containers_prize[random(sizeof(accessories_containers_prize))];
			}

			if(ContainersInfo[idx][cItems][4] != 0)
			{
				new skin_containers_prize[17] = {2, 7, 18, 24, 45, 67, 97, 101, 142, 144, 146, 154, 156, 176, 177, 220, 224}; // От 25000$ до 75000$;
				ContainersInfo[idx][cItemsCount][4] = skin_containers_prize[random(sizeof(skin_containers_prize))];
			}
		}
		case CONTAINERS_TYPE_SILVER:
		{
			if(ContainersInfo[idx][cItems][1] == TYPE_GIVE_ITEM_DONATE) ContainersInfo[idx][cItemsCount][1] = RandomEx(100, 200);
			else ContainersInfo[idx][cItemsCount][1] = RandomEx(400000, 800000);

			ContainersInfo[idx][cItemsCount][2] = GetContainersVehicle(random(10) < 5 ? VEHICLE_CLASS_C : VEHICLE_CLASS_B);

			if(ContainersInfo[idx][cItems][3] != 0)
			{
				new accessories_containers_prize[79] = {440, 441, 442, 446, 447, 448, 449, 450, 466, 467, 468, 469, 470, 471, 473, 474, 483, 487, 488, 494, 495, 496, 499, 502, 503, 514, 518, 522, 524, 526, 531, 532, 533, 535, 536, 538, 539, 550, 551, 552, 553, 554, 557, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572, 580, 581, 582, 583, 584, 589, 590, 591, 592, 593, 594, 595, 604, 608, 611, 612, 615, 617, 619, 621, 622, 623, 624}; // 500000$;
				ContainersInfo[idx][cItemsCount][3] = accessories_containers_prize[random(sizeof(accessories_containers_prize))];
			}

			if(ContainersInfo[idx][cItems][4] != 0)
			{
				new skin_containers_prize[8] = {28, 60, 170, 180, 183, 184, 273, 298}; // От 75000$ до 125000$;
				ContainersInfo[idx][cItemsCount][4] = skin_containers_prize[random(sizeof(skin_containers_prize))];
			}
		}
		case CONTAINERS_TYPE_GOLD:
		{
			if(ContainersInfo[idx][cItems][1] == TYPE_GIVE_ITEM_DONATE) ContainersInfo[idx][cItemsCount][1] = RandomEx(200, 400);
			else ContainersInfo[idx][cItemsCount][1] = RandomEx(800000, 1600000);

			if(random(10) == 0)
			{
				ContainersInfo[idx][cItems][2] = TYPE_GIVE_ITEM_U_VEHICLE;
				ContainersInfo[idx][cItemsCount][2] = GetContainersVehicle(VEHICLE_CLASS_UNIQUE);
			}
			else ContainersInfo[idx][cItemsCount][2] = GetContainersVehicle(VEHICLE_CLASS_A);

			if(ContainersInfo[idx][cItems][3] != 0)
			{
				new accessories_containers_prize[68] = {438, 439, 443, 444, 445, 451, 452, 453, 454, 455, 456, 457, 458, 459, 460, 461, 462, 463, 464, 465, 472, 475, 486, 497, 498, 500, 501, 504, 505, 506, 509, 510, 511, 512, 513, 515, 517, 525, 527, 529, 540, 548, 555, 556, 558, 559, 573, 574, 575, 576, 577, 578, 579, 586, 587, 588, 597, 605, 606, 609, 610, 613, 614, 616, 618, 620, 625, 626}; // От 500000$ до 2000000$;
				ContainersInfo[idx][cItemsCount][3] = accessories_containers_prize[random(sizeof(accessories_containers_prize))];
			}

			if(ContainersInfo[idx][cItems][4] != 0)
			{
				new skin_containers_prize[32] = {17, 19, 21, 22, 23, 29, 30, 33, 46, 47, 48, 76, 82, 83, 84, 91, 185, 214, 219, 228, 241, 242, 249, 289, 291, 292, 293, 294, 295, 296, 297, 299}; // От 125000$ до 645000$;
				ContainersInfo[idx][cItemsCount][4] = skin_containers_prize[random(sizeof(skin_containers_prize))];
			}

			if(random(10) == 1)
			{
				ContainersInfo[idx][cItems][5] = TYPE_GIVE_ITEM_U_SKIN;

				new skin_containers_prize[] = {11, 12, 16, 20, 26, 27, 32, 34, 35, 40, 43, 44, 50, 51, 52, 56, 57, 59, 61, 64, 65, 68, 69, 70, 71, 72, 73,
					80, 81, 86, 92, 93, 94, 98, 99, 100, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
					122, 123, 124, 125, 126, 127, 131, 141, 143, 147, 148, 149, 150, 153, 158, 161, 162, 163, 164, 165, 166, 167, 168, 169, 171, 172, 173, 174,
					175, 179, 181, 182, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 198, 203, 204, 205, 208, 209, 211, 216, 217, 221, 222, 223, 225, 227,
					229, 233, 235, 236, 240, 246, 247, 248, 250, 253, 254, 255, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 274,
					275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 290, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 
					742, 743, 744, 745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 761};
				ContainersInfo[idx][cItemsCount][5] = skin_containers_prize[random(sizeof(skin_containers_prize))];

				ContainersInfo[idx][cItemsIDx][5] = 0;
			}
		}
	}
	return 1;
}

GetContainersVehicle(class)
{
	new idx = 0;
	for(new i = 0; i < 212; i++)
	{
		idx = random(212);
		if(idx == 86) continue;
		if(GetVehicleData(idx, E_VD_PRICE) > 15000000 || GetVehicleData(idx, E_VD_CLASS) != class) continue;
		return GetVehicleData(idx, E_VD_ID);
	}
	return GetVehicleData(idx, E_VD_ID);
}

GetContainersPrize(idx)
{
	STRING_GLOBAL = "Содержимое контейнера:\n\n";
	for(new i = 0; i < MAX_CONTAINERS_PRIZE; i++)
	{
		f(STRING_GLOBAL, "%s%s\n", STRING_GLOBAL, GetPrizeItemsName(ContainersInfo[idx][cItems][i], ContainersInfo[idx][cItemsCount][i], ContainersInfo[idx][cItemsIDx][i]));
	}
	return STRING_GLOBAL;
}


CMD:auction(playerid, params[])
{
	for(new i = MAX_CONTAINERS-1; i != -1; i--)
	{
		if(IsPlayerInRangeOfPoint(playerid, 5.0, ContainersPos[i][0], ContainersPos[i][1], ContainersPos[i][2]))
		{
			ShowContainersDialog(playerid, i);
			break;
		}
	}
	SendError(playerid, "Вы далеко от контейнера.");
	return 1;
}

ShowContainersDialog(playerid, idx)
{
	switch(ContainersInfo[idx][cStatus])
	{
		case CONTAINERS_STATUS_EMPTY: return SendError(playerid, "Данный контейнер еще не создан.");
		case CONTAINERS_STATUS_CREATED, CONTAINERS_STATUS_AUCTION:
		{
			if(ContainersInfo[idx][cPlayerID] == p_info[playerid][ID]) 
				return SendError(playerid, "Вы уже установили ставку на данный контейнер.");
			STRING_GLOBAL[0] = EOS;
			format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
				Контейнер: "I"%d"W"\n\
				Тип: "I"%s"W"\n\n\
				Стоимость: "I"%d$"W"\n\
				Ставка: "I"%d$"W"\n\n\
				Введите кол-во денежных средств, которое хотите\n\
				поставить за этот контейнер, но не меньше тех,\n\
				которые сейчас установлены и не меньше стоимости:\n\n\
				Обратите внимание, если Ваша ставка будет перебита\n\
				Вам будут возвращены деньги. Если выйдете из игры\n\
				предметы зачислятся оффлайн.\n\n\
				Чтобы забрать свои призы, введите "I"/items", idx + 1, ContainersTypeInfo[ContainersInfo[idx][cType] - 1][ctName], ContainersInfo[idx][cPrice], ContainersInfo[idx][cBet]);
			ShowPlayerDialog(playerid, D_CONTAINERS, DIALOG_STYLE_INPUT, ""I"Аукцион контейнеров", STRING_GLOBAL, "Далее", "Отмена");
			SetPVarInt(playerid, "ContainersCreatedTime", ContainersInfo[idx][cCreatedTime]);
			return 1;
		}
		case CONTAINERS_STATUS_PRIZE:
		{
			if(ContainersInfo[idx][cPlayerID] != p_info[playerid][ID]) return SendError(playerid, "Данный контейнер не принадлежит Вам.");
			if(ContainersInfo[idx][cType] == CONTAINERS_TYPE_NONE) return SendError(playerid, "В контейнере ничего нет.");
			new scdplayerid = GetPlayerUserID(ContainersInfo[idx][cPlayerID]), items_idx, items_count;
			for(new i = 0; i < MAX_CONTAINERS_PRIZE; i++)
			{
				items_idx = ContainersInfo[idx][cItems][i];
				if(items_idx == 0) continue;
				items_count = ContainersInfo[idx][cItemsCount][i];
				SetPlayerItem(scdplayerid, 8, p_info[scdplayerid][ID], items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]);
				Log(LOG_player, INFO, "%s[%d] получил %s из контейнера за %d$ | #Containers",
				get_name(scdplayerid), p_info[scdplayerid][ID], GetPrizeItemsName(items_idx, items_count, ContainersInfo[idx][cItemsIDx][i]), ContainersInfo[idx][cBet]);
			}
			DestroyContainers(idx);
			return 1;
		}
	}
	return 1;
}

CMD:test_cnt(playerid, params[])
{
	if(SRV_ID) return 1;
	SendMesAll(COLOR_LIGHTRED, "[КОНТЕЙНЕРЫ]: "W"Начался аукцион контейнеров. Местоположение: {"#cLIGHTRED"}/gps > [1] Общественные места > [8] Аукцион контейнеров");
	for(new i = 0; i < MAX_CONTAINERS; i++) CreateContainers(i);
	return 1;
}