new rocket[50];
new rocket_space[50];
new rocket_status;
new rocket_timer[2];
new rocket_timer_status[2];
new Text3D:rocket_text[3];

enum SF_INFO
{
	sfStatus,
	sfObject,
	Float:sfPos[3]
};

new SpaceFossilsInfo[][SF_INFO] = {
	{0, -1, {942.458923, 1223.004028, 1056.677124}},
	{0, -1, {885.088684, 1295.546264, 1056.375610}},
	{0, -1, {885.546264, 1151.512573, 1056.448730}},
	{0, -1, {794.497131, 1178.424804, 1056.985107}},
	{0, -1, {772.539428, 1226.665283, 1056.839843}},
	{0, -1, {835.552185, 1250.438110, 1055.366821}},
	{0, -1, {791.156311, 1287.596313, 1056.297607}},
	{0, -1, {968.266784, 1305.586669, 1057.477661}},
	{0, -1, {1029.866699, 1219.956665, 1057.607666}},
	{0, -1, {999.401000, 1164.415283, 1056.657104}},
	{0, -1, {959.592285, 1170.845458, 1056.356933}},
	{0, -1, {974.991088, 1268.698852, 1057.457031}},
	{0, -1, {896.911010, 1261.960815, 1047.347534}},
	{0, -1, {919.472412, 1336.642456, 1049.098388}},
	{0, -1, {955.470153, 1335.699829, 1057.137695}},
	{0, -1, {925.126831, 1402.058471, 1056.647338}},
	{0, -1, {865.976745, 1407.058715, 1056.647338}},
	{0, -1, {885.821594, 1356.902221, 1056.104736}},
	{0, -1, {885.821594, 1320.122070, 1057.005004}},
	{0, -1, {885.821594, 1234.181640, 1056.934936}},
	{0, -1, {928.121459, 1261.651611, 1056.714721}},
	{0, -1, {972.791748, 1221.611572, 1057.244995}},
	{0, -1, {1038.707397, 1271.005493, 1056.994750}},
	{0, -1, {1017.205444, 1346.979125, 1057.875244}},
	{0, -1, {976.128906, 1382.186035, 1057.404907}},
	{0, -1, {869.506286, 1268.480346, 1057.274780}},
	{0, -1, {829.971191, 1218.955078, 1057.814819}},
	{0, -1, {850.265014, 1170.484130, 1058.495361}}
};

CreateRocket(idx)
{
    switch(idx)
    {
        case 0:
        {
            rocket[0] = CreateDynamicObject(19731, 1089.180786, 1074.834594, 66.067726, 0.000000, -103.999954, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[0], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[1] = CreateDynamicObject(19732, 1087.756225, 1074.834594, 66.066947, 0.000000, -103.900154, 179.999404, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[1], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[2] = CreateDynamicObject(19690, 1089.905029, 1074.834594, 58.569099, 0.000000, -103.999984, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[2], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket[3] = CreateDynamicObject(19691, 1087.070922, 1074.863891, 58.582176, 0.000000, -103.900123, 179.999588, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[3], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[4] = CreateDynamicObject(19646, 1091.039062, 1074.828735, 49.399105, 0.000000, -89.999977, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[4], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket[5] = CreateDynamicObject(19646, 1085.866699, 1074.881469, 49.403102, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[5], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[6] = CreateDynamicObject(1683, 1093.355957, 1072.849121, 34.324974, 0.000000, -90.700012, -179.999862, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[6], 0, 19480, "signsurf", "sign", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[6], 1, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket[6], 2, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket[6], 3, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket[6], 4, 2749, "cj_hair", "cj_spec", 0x00000000);
            rocket[7] = CreateDynamicObject(19316, 1088.456542, 1074.869384, 66.665817, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[7], 0, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket[7], 3, 1948, "kbslotnu", "slot_black", 0x00000000);
            rocket[8] = CreateDynamicObject(19646, 1091.037109, 1074.836547, 39.499107, 0.000000, -89.999969, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[8], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket[9] = CreateDynamicObject(19697, 1091.197998, 1074.400756, 22.320028, -0.699051, 81.299728, 89.963218, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[9], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[10] = CreateDynamicObject(19646, 1085.868652, 1074.883422, 39.503105, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[10], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[11] = CreateDynamicObject(19698, 1091.198486, 1076.210083, 22.380800, 0.699056, 83.500228, -90.036491, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[11], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[12] = CreateDynamicObject(19697, 1087.438964, 1071.973999, 22.278287, -0.699065, 79.199783, -0.036704, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[12], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[13] = CreateDynamicObject(19646, 1091.052734, 1074.848266, 29.549102, 0.000000, -89.999954, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[13], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket[14] = CreateDynamicObject(19646, 1085.884277, 1074.895141, 29.553104, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[14], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[15] = CreateDynamicObject(19698, 1089.344238, 1071.973022, 22.325777, 0.699072, 82.100196, 179.963226, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[15], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[16] = CreateDynamicObject(19697, 1089.452026, 1077.703002, 22.373529, -0.699057, 79.899772, 179.963119, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[16], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[17] = CreateDynamicObject(19698, 1087.518432, 1077.734252, 22.412321, 0.699064, 82.300155, -0.036766, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[17], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[18] = CreateDynamicObject(19699, 1092.154418, 1078.592773, 31.870395, 0.000004, -89.999992, 43.699939, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[18], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[19] = CreateDynamicObject(19731, 1091.688842, 1078.146850, 46.446071, 0.000009, -103.999946, 44.299976, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[19], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[20] = CreateDynamicObject(19699, 1092.321289, 1071.191284, 31.870395, -0.000009, -89.999984, -46.000091, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[20], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[21] = CreateDynamicObject(19646, 1091.044921, 1074.842407, 24.379068, 0.000000, -89.999946, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[21], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket[22] = CreateDynamicObject(19646, 1085.876464, 1074.889282, 24.387069, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[22], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket[23] = CreateDynamicObject(19731, 1091.872924, 1071.654418, 46.446071, -0.000004, -103.999938, -45.400005, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[23], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket[24] = CreateDynamicObject(2643, 1090.467163, 1069.916015, 51.821605, 0.000000, 0.000000, 21.199993, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[24], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket[25] = CreateDynamicObject(2643, 1093.168090, 1070.198242, 20.661619, 0.000004, 0.000004, 42.699977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[25], 0, 7103, "vgnplantgen", "metalwheel3_128", 0xFFFFFFFF);
            rocket[26] = CreateDynamicObject(2643, 1092.809570, 1079.742309, 20.661619, 0.000003, -0.000006, 143.199935, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[26], 0, 7103, "vgnplantgen", "metalwheel3_128", 0xFFFFFFFF);
            rocket[27] = CreateDynamicObject(2643, 1083.161987, 1074.873413, 32.931583, 0.000000, 0.000000, -90.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[27], 0, 1809, "cj_hi_fi", "cj_speaker_s", 0xFFFFFFFF);
            rocket[28] = CreateDynamicObject(2643, 1092.488159, 1071.392456, 51.821605, 0.000000, 0.000000, 48.699989, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[28], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket[29] = CreateDynamicObject(2643, 1092.567749, 1078.169799, 51.821605, 0.000000, 0.000000, 125.999969, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[29], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket[30] = CreateDynamicObject(2643, 1090.782470, 1079.619262, 51.821605, 0.000000, 0.000000, 156.299972, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[30], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket[31] = CreateDynamicObject(2643, 1091.591796, 1070.568725, 53.631626, 0.000000, 0.000000, 40.999984, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[31], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket[32] = CreateDynamicObject(2643, 1091.704101, 1078.997436, 53.621585, 0.000000, 0.000000, 139.699920, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[32], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket[33] = CreateDynamicObject(2643, 1093.726440, 1075.093261, 28.871589, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[33], 0, 12853, "cunte_gas01", "starspangban1_256", 0xFFFFFFFF);
            rocket[34] = CreateDynamicObject(13649, 1091.472900, 1072.101562, 18.871910, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[34], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[34], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket[35] = CreateDynamicObject(13649, 1091.332763, 1077.821655, 18.871910, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[35], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[35], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket[36] = CreateDynamicObject(19756, 1087.459716, 1073.551025, 19.246540, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[36], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            rocket[37] = CreateDynamicObject(19756, 1087.529785, 1076.251831, 19.226541, 0.000000, 0.000000, 270.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[37], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            rocket[38] = CreateDynamicObject(19756, 1089.939697, 1074.860717, 19.238534, 0.000000, 0.000000, 180.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[38], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            rocket[39] = CreateDynamicObject(13649, 1087.222534, 1074.941284, 18.871910, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[39], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[39], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket[40] = CreateDynamicObject(3504, 1093.296508, 1075.048095, 48.110359, 0.000000, 0.000000, 90.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[40], 0, 1982, "new_cabinets", "cabinet_hi1b", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[40], 1, 1948, "kbslotnu", "slot_black", 0x00000000);
            rocket[41] = CreateDynamicObject(18846, 1091.487426, 1077.856689, 18.703886, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[41], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[41], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket[42] = CreateDynamicObject(18846, 1091.487426, 1072.126098, 18.703886, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[42], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[42], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket[43] = CreateDynamicObject(18846, 1087.117065, 1074.996459, 18.703886, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket[43], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket[43], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket[44] = CreateDynamicObject(18694, 1086.649780, 1073.401611, 17.843692, -90.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            rocket[45] = CreateDynamicObject(18694, 1087.590698, 1073.401611, 17.843692, -90.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            rocket[46] = CreateDynamicObject(18694, 1091.050415, 1070.420166, 17.633687, -89.999992, 89.999992, 89.999992, -1, -1, -1, 120.00, 120.00);
            rocket[47] = CreateDynamicObject(18694, 1091.991333, 1070.420166, 17.633687, -89.999992, 89.999992, 89.999992, -1, -1, -1, 120.00, 120.00);
            rocket[48] = CreateDynamicObject(18694, 1091.050415, 1076.129394, 17.633687, -89.999992, 89.999992, 89.999977, -1, -1, -1, 120.00, 120.00);
            rocket[49] = CreateDynamicObject(18694, 1091.991333, 1076.129394, 17.633687, -89.999992, 89.999992, 89.999977, -1, -1, -1, 120.00, 120.00);

            rocket_text[0] = CreateDynamic3DTextLabel("", COLOR_MAIN, 1088.5585, 1074.9478, 10.8451, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
        }
        case 1:
        {
            rocket_space[0] = CreateDynamicObject(19731, 814.818725, 1353.782592, 1113.977905+250.000000, 0.000000, -103.999946, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[0], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[1] = CreateDynamicObject(19732, 813.394165, 1353.782592, 1113.977172+250.000000, 0.000000, -103.900161, 179.999359, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[1], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[2] = CreateDynamicObject(19690, 815.542968, 1353.782592, 1106.479370+250.000000, 0.000000, -103.999977, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[2], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[3] = CreateDynamicObject(19691, 812.708862, 1353.811889, 1106.492431+250.000000, 0.000000, -103.900131, 179.999542, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[3], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[4] = CreateDynamicObject(19646, 816.677001, 1353.776733, 1097.309326+250.000000, 0.000000, -89.999969, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[4], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[5] = CreateDynamicObject(19646, 811.504638, 1353.829467, 1097.313354+250.000000, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[5], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[6] = CreateDynamicObject(1683, 818.993896, 1351.797119, 1082.235229+250.000000, 0.000000, -90.700019, -179.999816, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[6], 0, 19480, "signsurf", "sign", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[6], 1, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket_space[6], 2, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket_space[6], 3, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket_space[6], 4, 2749, "cj_hair", "cj_spec", 0x00000000);
            rocket_space[7] = CreateDynamicObject(19316, 814.094482, 1353.817382, 1114.576049+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[7], 0, 19480, "signsurf", "sign", 0x00000000);
            SetDynamicObjectMaterial(rocket_space[7], 3, 1948, "kbslotnu", "slot_black", 0x00000000);
            rocket_space[8] = CreateDynamicObject(19646, 816.675048, 1353.784545, 1087.409301+250.000000, 0.000000, -89.999961, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[8], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[9] = CreateDynamicObject(19697, 816.835937, 1353.348754, 1070.230224+250.000000, -0.699042, 81.299728, 89.963195, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[9], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket_space[10] = CreateDynamicObject(19646, 811.506591, 1353.831420, 1087.413330+250.000000, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[10], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[11] = CreateDynamicObject(19698, 816.836425, 1355.158081, 1070.291015+250.000000, 0.699047, 83.500228, -90.036468, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[11], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket_space[12] = CreateDynamicObject(19697, 813.076904, 1350.921997, 1070.188476+250.000000, -0.699064, 79.199790, -0.036703, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[12], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[13] = CreateDynamicObject(19646, 816.690673, 1353.796264, 1077.459350+250.000000, 0.000000, -89.999946, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[13], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[14] = CreateDynamicObject(19646, 811.522216, 1353.843139, 1077.463378+250.000000, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[14], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[15] = CreateDynamicObject(19698, 814.982177, 1350.921020, 1070.235961+250.000000, 0.699070, 82.100189, 179.963180, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[15], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket_space[16] = CreateDynamicObject(19697, 815.089965, 1356.651000, 1070.283691+250.000000, -0.699056, 79.899765, 179.963073, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[16], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket_space[17] = CreateDynamicObject(19698, 813.156372, 1356.682250, 1070.322509+250.000000, 0.699063, 82.300163, -0.036766, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[17], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[18] = CreateDynamicObject(19699, 817.792358, 1357.540771, 1079.780639+250.000000, 0.000009, -89.999984, 43.699939, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[18], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[19] = CreateDynamicObject(19731, 817.326782, 1357.094848, 1094.356323+250.000000, 0.000014, -103.999938, 44.299976, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[19], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket_space[20] = CreateDynamicObject(19699, 817.959228, 1350.139282, 1079.780639+250.000000, -0.000014, -89.999977, -46.000091, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[20], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[21] = CreateDynamicObject(19646, 816.682861, 1353.790405, 1072.289306+250.000000, 0.000000, -89.999938, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[21], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            rocket_space[22] = CreateDynamicObject(19646, 811.514404, 1353.837280, 1072.297241+250.000000, 0.000000, -270.000000, -0.000029, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[22], 0, 1948, "kbslotnu", "slot_black", 0xFFFFFFFF);
            rocket_space[23] = CreateDynamicObject(19731, 817.510864, 1350.602416, 1094.356323+250.000000, -0.000009, -103.999931, -45.400005, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[23], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFDCDCDC);
            rocket_space[24] = CreateDynamicObject(2643, 816.105102, 1348.864013, 1099.731811+250.000000, 0.000001, 0.000007, 21.199987, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[24], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket_space[25] = CreateDynamicObject(2643, 818.806030, 1349.146240, 1068.571899+250.000000, 0.000009, 0.000009, 42.699977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[25], 0, 7103, "vgnplantgen", "metalwheel3_128", 0xFFFFFFFF);
            rocket_space[26] = CreateDynamicObject(2643, 818.447509, 1358.690307, 1068.571899+250.000000, 0.000007, -0.000012, 143.199935, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[26], 0, 7103, "vgnplantgen", "metalwheel3_128", 0xFFFFFFFF);
            rocket_space[27] = CreateDynamicObject(2643, 808.799926, 1353.821411, 1080.841796+250.000000, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[27], 0, 1809, "cj_hi_fi", "cj_speaker_s", 0xFFFFFFFF);
            rocket_space[28] = CreateDynamicObject(2643, 818.126098, 1350.340454, 1099.731811+250.000000, 0.000004, 0.000004, 48.699977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[28], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket_space[29] = CreateDynamicObject(2643, 818.205688, 1357.117797, 1099.731811+250.000000, 0.000006, -0.000003, 125.999946, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[29], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket_space[30] = CreateDynamicObject(2643, 816.420410, 1358.567260, 1099.731811+250.000000, 0.000003, -0.000006, 156.299926, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[30], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket_space[31] = CreateDynamicObject(2643, 817.229736, 1349.516723, 1101.541870+250.000000, 0.000004, 0.000004, 40.999980, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[31], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket_space[32] = CreateDynamicObject(2643, 817.342041, 1357.945434, 1101.531860+250.000000, 0.000003, -0.000004, 139.699874, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[32], 0, 2749, "cj_hair", "cj_spec", 0xFFFFFFFF);
            rocket_space[33] = CreateDynamicObject(2643, 819.364379, 1354.041259, 1076.781860+250.000000, 0.000007, 0.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[33], 0, 12853, "cunte_gas01", "starspangban1_256", 0xFFFFFFFF);
            rocket_space[34] = CreateDynamicObject(13649, 817.110839, 1351.049560, 1066.782104+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[34], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[34], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket_space[35] = CreateDynamicObject(13649, 816.970703, 1356.769653, 1066.782104+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[35], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[35], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket_space[36] = CreateDynamicObject(19756, 813.097656, 1352.499023, 1067.156738+250.000000, 0.000007, 0.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[36], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            rocket_space[37] = CreateDynamicObject(19756, 813.167724, 1355.199829, 1067.136718+250.000000, -0.000007, 0.000000, -89.999977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[37], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            rocket_space[38] = CreateDynamicObject(19756, 815.577636, 1353.808715, 1067.148803+250.000000, 0.000000, -0.000007, 179.999954, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[38], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            rocket_space[39] = CreateDynamicObject(13649, 812.860473, 1353.889282, 1066.782104+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[39], 0, 3629, "arprtxxref_las", "ws_corrugateddoor1", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[39], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket_space[40] = CreateDynamicObject(3504, 818.934448, 1353.996093, 1096.020629+250.000000, 0.000007, 0.000000, 89.999977, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[40], 0, 1982, "new_cabinets", "cabinet_hi1b", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[40], 1, 1948, "kbslotnu", "slot_black", 0x00000000);
            rocket_space[41] = CreateDynamicObject(18846, 817.125366, 1356.804687, 1066.614135+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[41], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[41], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket_space[42] = CreateDynamicObject(18846, 817.125366, 1351.074096, 1066.614135+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[42], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[42], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket_space[43] = CreateDynamicObject(18846, 812.755004, 1353.944458, 1066.614135+250.000000, 0.000000, 180.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            SetDynamicObjectMaterial(rocket_space[43], 0, 15040, "cuntcuts", "CsCrackpipe01", 0xFFFFFFFF);
            SetDynamicObjectMaterial(rocket_space[43], 1, 3922, "bistro", "vent_64", 0x00000000);
            rocket_space[44] = CreateDynamicObject(18694, 817.437011, 1349.471069, 1065.126953+250.000000, -90.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            rocket_space[45] = CreateDynamicObject(18694, 816.906555, 1349.471069, 1065.126953+250.000000, -90.000000, 0.000000, 0.000000, -1, -1, -1, 120.00, 120.00);
            rocket_space[46] = CreateDynamicObject(18694, 817.437011, 1355.100585, 1065.126953+250.000000, -89.999992, 89.999992, 89.999977, -1, -1, -1, 120.00, 120.00);
            rocket_space[47] = CreateDynamicObject(18694, 816.906555, 1355.100585, 1065.126953+250.000000, -89.999992, 89.999992, 89.999977, -1, -1, -1, 120.00, 120.00);
            rocket_space[48] = CreateDynamicObject(18694, 812.997070, 1352.348876, 1065.126953+250.000000, -89.999992, 90.000000, 89.999969, -1, -1, -1, 120.00, 120.00);
            rocket_space[49] = CreateDynamicObject(18694, 812.466613, 1352.348876, 1065.126953+250.000000, -89.999992, 90.000000, 89.999969, -1, -1, -1, 120.00, 120.00);

            rocket_text[1] = CreateDynamic3DTextLabel("", COLOR_MAIN, 814.1629, 1353.9165, 1058.7552, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
        }
    }
    rocket_text[2] = CreateDynamic3DTextLabel("", COLOR_MAIN, 1114.2740,1111.6119,1086.5599, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL);
    return 1;
}

UpdateRocket()
{
    new Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;

    switch(rocket_status)
    {
        case 0:
        {
            if(timestamp_minute == 0 && timestamp_second == 0 || 
                timestamp_minute == 10 && timestamp_second == 0 ||
                timestamp_minute == 20 && timestamp_second == 0 || 
                timestamp_minute == 30 && timestamp_second == 0 || 
                timestamp_minute == 40 && timestamp_second == 0 || 
                timestamp_minute == 50 && timestamp_second == 0)
            {
                for(new i = 0; i < sizeof(rocket); i++)
                {
                    GetDynamicObjectPos(rocket[i], x, y, z);
                    GetDynamicObjectRot(rocket[i], rx, ry, rz);
                    MoveDynamicObject(rocket[i], x, y, z+250, 7.5, rx, ry, rz);
                }
                for(new i = 0; i < sizeof(rocket_space); i++)
                {
                    GetDynamicObjectPos(rocket_space[i], x, y, z);
                    GetDynamicObjectRot(rocket_space[i], rx, ry, rz);
                    MoveDynamicObject(rocket_space[i], x, y, z-250, 1.69, rx, ry, rz);
                }
                /*SendMesAll(0xFFD700FF, "Новости космодрома: "W"Ракета отправляется в космос.");*/
                rocket_timer[0] = 450;
                rocket_timer[1] = 150;
                rocket_timer_status[0] = 1;
                rocket_timer_status[1] = 1;
                rocket_status = 1;
            }
        }
        case 1:
        {
            if(timestamp_minute == 5 && timestamp_second == 0 ||
                timestamp_minute == 15 && timestamp_second == 0 ||
                timestamp_minute == 25 && timestamp_second == 0 ||
                timestamp_minute == 35 && timestamp_second == 0 ||
                timestamp_minute == 45 && timestamp_second == 0 ||
                timestamp_minute == 55 && timestamp_second == 0)
            {
                for(new i = 0; i < sizeof(rocket); i++)
                {
                    GetDynamicObjectPos(rocket[i], x, y, z);
                    GetDynamicObjectRot(rocket[i], rx, ry, rz);
                    MoveDynamicObject(rocket[i], x, y, z-250, 1.69, rx, ry, rz);
                }
                for(new i = 0; i < sizeof(rocket_space); i++)
                {
                    GetDynamicObjectPos(rocket_space[i], x, y, z);
                    GetDynamicObjectRot(rocket_space[i], rx, ry, rz);
                    MoveDynamicObject(rocket_space[i], x, y, z+250, 7.5, rx, ry, rz);
                }
                /*SendMesAll(0xFFD700FF, "Новости космодрома: "W"Ракета отправляется на землю.");*/
                rocket_timer[0] = 150;
                rocket_timer[1] = 450;
                rocket_timer_status[0] = 1;
                rocket_timer_status[1] = 1;
                rocket_status = 0;
            }
        }
    }
    return 1;
}

CreateSpaceFossils(playerid)
{
    new rand = random(sizeof(SpaceFossilsInfo)), index = -1;
    for(new i = 0, idx = -1; i < sizeof(SpaceFossilsInfo) * 2; i++)
    {
        idx++;
        if(idx >= sizeof(SpaceFossilsInfo)) idx = 0;
        if(SpaceFossilsInfo[idx][sfStatus] == 1) continue;
        rand--;
        if(rand <= 0)
        {
            SpaceFossilsInfo[idx][sfStatus] = 1;
            if(SpaceFossilsInfo[idx][sfObject] != -1)
            {
                DestroyDynamicObject(SpaceFossilsInfo[idx][sfObject]);
                SpaceFossilsInfo[idx][sfObject] = -1;
            }
            if(SpaceFossilsInfo[idx][sfPos] == 0.0) continue;
            SpaceFossilsInfo[idx][sfObject] = CreateDynamicObject(1631, SpaceFossilsInfo[idx][sfPos][0], SpaceFossilsInfo[idx][sfPos][1], SpaceFossilsInfo[idx][sfPos][2], 0.0, 0.0, 0.0);
            SetDynamicObjectMaterial(SpaceFossilsInfo[idx][sfObject], 0, 2922, "kmb_keypadx", "keypad_light", 0xFFFFFFFF);
            SetDynamicObjectMaterial(SpaceFossilsInfo[idx][sfObject], 1, 2922, "kmb_keypadx", "keypad_light", 0x00000000);
            SetDynamicObjectMaterial(SpaceFossilsInfo[idx][sfObject], 2, 19480, "signsurf", "sign", 0x00000000);
            index = idx;
            break;
        }
    }
    if(index == -1)
    {
        p_temp[playerid][SpaceIDx] = 0;
        p_temp[playerid][SpaceTimer] = 10;
        return 1;
    }
    p_temp[playerid][SpaceIDx] = index + 1;
    p_temp[playerid][SpaceTimer] = 180;

    new Float:distance = GetPlayerDistanceFromPoint(playerid, SpaceFossilsInfo[index][sfPos][0], SpaceFossilsInfo[index][sfPos][1], SpaceFossilsInfo[index][sfPos][2]);

    SetPlayerCheckpoint(playerid, SpaceFossilsInfo[index][sfPos][0], SpaceFossilsInfo[index][sfPos][1], SpaceFossilsInfo[index][sfPos][2], 5.0);
    SendMes(playerid, COLOR_BLUE, "На территории космоса обнаружены ископаемые. Расстояние: "W"%.0f{"#cBLUE"} метров.", distance);
    SendMes(playerid, COLOR_LIME, "Местоположение ископаемые отмечено на Вашем GPS навигаторе.");
    SendMes(playerid, COLOR_SEA_WAVE, "У Вас есть 3 минуты чтобы добраться до местоположения ископаемые и добыть их.");
    return 1;
}

DestroySpaceFossils(playerid)
{
    if(p_temp[playerid][Work_ID] != SPACE_WORK || p_temp[playerid][SpaceIDx] == 0) return 1;
    new idx = p_temp[playerid][SpaceIDx] - 1;
    SpaceFossilsInfo[idx][sfStatus] = 0;
    if(SpaceFossilsInfo[idx][sfObject] != -1) DestroyDynamicObject(SpaceFossilsInfo[idx][sfObject]);
    SpaceFossilsInfo[idx][sfObject] = -1;
    return 1;
}

SetPlayerSpaceCostume(playerid)
{
    for(new i = 0; i < 10; i++) if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
    SetPlayerAttachedObject(playerid, 0, 19063, 2, 0.0850, 0.0390, 0.0000, 0.0000, -96.5999, 0.0000, 0.3470, 0.3689, 0.3970, 0, -16777216);
    SetPlayerAttachedObject(playerid, 1, 19200, 2, 0.1289, -0.0329, 0.0030, 2.4000, -5.9999, -82.8999, 1.4609, 1.5759, 1.7020, 0, 0);
    SetPlayerAttachedObject(playerid, 2, 2186, 1, -0.3109, -0.1409, 0.0080, -0.2999, 89.0000, -92.5000, 0.2010, 0.5339, 0.5859, -1, 0);
    SetPlayerAttachedObject(playerid, 3, 19280, 2, 0.3389, 0.0430, 0.0359, 0.0000, 82.0999, 0.0000, 0.3639, 0.5609, 0.3529, 0, 0);
    SetPlayerAttachedObject(playerid, 4, 3675, 1, 0.4619, -0.1650, -0.0099, 0.0000, 90.6000, 0.0000, 0.0399, 0.0480, 0.0489, -1, 0);
    SetPlayerAttachedObject(playerid, 5, 1654, 1, 0.1819, -0.2980, -0.2150, 0.0000, 94.3999, 80.0999, 1.0000, 1.0000, 1.0000, 318767103, 0);
    SetPlayerAttachedObject(playerid, 6, 3384, 1, -0.0540, -0.4599, -0.0099, 0.0000, 89.1999, 85.3000, 0.2300, 0.2630, 0.1870, -1, 0);
    SetPlayerAttachedObject(playerid, 7, 1279, 1, -0.5029, -0.3149, -0.0149, 0.0000, 89.4999, 0.0000, 0.6150, 0.9409, 0.9809, -1, 0);
    SetPlayerAttachedObject(playerid, 8, 2711, 1, 0.5529, -0.1939, 0.2689, 0.0000, 87.3999, 0.0000, 1.1739, 1.1319, 2.4909, -1, 0);
    SetPlayerAttachedObject(playerid, 9, 2711, 1, 0.5709, -0.2039, -0.2469, 0.0000, 87.3999, 178.1999, 1.1739, 1.1319, 2.4909, 0, 0);
    return 1;
}

RemovePlayerSpaceCostume(playerid)
{
    for(new i = 0; i < 10; i++) if(IsPlayerAttachedObjectSlotUsed(playerid, i)) RemovePlayerAttachedObject(playerid, i);
    return 1;
}
