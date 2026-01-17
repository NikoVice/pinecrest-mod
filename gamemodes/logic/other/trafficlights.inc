/*
    TrafficLights v1 by Vip_Uzer

*/

#if defined _trafficlights_included
    #endinput
#endif
#define _trafficlights_included

#define TL_USE_STREAMER

// ================================== [DEFINITIONS] ================================== //
#define INVALID_TL_ID                    -1

#define MAX_TRAFFIC_LIGHTS_TYPES        8            // Amount of different posts.
#define MAX_TRAFFIC_LIGHTS                50            // Max. amount of controllable traffic lights. Increase if you wish.


#define TLC_GREEN                    19297        // Green light model id.
#define TLC_AMBER                    19295        // Amber light model id.
#define TLC_RED                      19296        // Red light model id.
#define TLC_OFF                     -1

// ================================== [VARIABLES] ================================== //
enum E_TL_DATA
{
    tl_mysql_id,
    tl_object_id[11],
    Float:tl_object_pos[4],
    tl_area,
    Float:tl_area_pos[4],
    tl_color,
    tl_light_object,
    Text3D:tl_3dtext
}
new TL_Data[MAX_TRAFFIC_LIGHTS][E_TL_DATA],
    totaltl;


cmd:tlz(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    //if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /tlz [1-2]");
    //if(!(1 <= params[0] <= 2)) return SendInfo(playerid, "Используйте: /tlz [1-2]");
    new idx = totaltl-1,
        Float:coord[3];
    GetPlayerPos(playerid, coord[0], coord[1], coord[2]);

    if(TL_Data[idx][tl_area_pos][0] == 0.0 && TL_Data[idx][tl_area_pos][1] == 0.0)
        return SendError(playerid, "Вначале настройте тип 1.");

    TL_Data[idx][tl_area_pos][2] = coord[0];
    TL_Data[idx][tl_area_pos][3] = coord[1];

    new Float:tmp_coord;
    if(TL_Data[idx][tl_area_pos][0] > TL_Data[idx][tl_area_pos][2])
    {
        tmp_coord = TL_Data[idx][tl_area_pos][0];
        TL_Data[idx][tl_area_pos][0] = TL_Data[idx][tl_area_pos][2];
        TL_Data[idx][tl_area_pos][2] = tmp_coord;
    }
    if(TL_Data[idx][tl_area_pos][1] > TL_Data[idx][tl_area_pos][3])
    {
        tmp_coord = TL_Data[idx][tl_area_pos][1];
        TL_Data[idx][tl_area_pos][1] = TL_Data[idx][tl_area_pos][3];
        TL_Data[idx][tl_area_pos][3] = tmp_coord;
    }

    TL_Data[idx][tl_area] = CreateDynamicRectangle(TL_Data[idx][tl_area_pos][0], TL_Data[idx][tl_area_pos][1], TL_Data[idx][tl_area_pos][2], TL_Data[idx][tl_area_pos][3]);
    UpdateAreaInfo(TL_Data[idx][tl_area], TYPE_TRAFFICLIGHTS, AREA_SUBTYPE_INVALID_ID, idx);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `trafficlights` \
        (`tl_object_pos_X`, `tl_object_pos_Y`, `tl_object_pos_Z`, `tl_object_pos_RZ`, `tl_area_pos_X1`, `tl_area_pos_Y1`, `tl_area_pos_X2`, `tl_area_pos_Y2`) \
         VALUES ('%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f')",
         TL_Data[idx][tl_object_pos][0], TL_Data[idx][tl_object_pos][1], TL_Data[idx][tl_object_pos][2], TL_Data[idx][tl_object_pos][3],
        TL_Data[idx][tl_area_pos][0], TL_Data[idx][tl_area_pos][1], TL_Data[idx][tl_area_pos][2], TL_Data[idx][tl_area_pos][3]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_trafficlights","i", idx);

    //if(SRV_ID == 0) WriteLog("update", STRING_GLOBAL);

    SendInfo(playerid, "Настройка светофора закончена.");

    if(!SRV_ID) // test zona - тестовый сервер
    {
        new gang_zone_test = GangZoneCreate(TL_Data[idx][tl_area_pos][0], TL_Data[idx][tl_area_pos][1], TL_Data[idx][tl_area_pos][2], TL_Data[idx][tl_area_pos][3]);
        GangZoneShowForAll(gang_zone_test, COLOR_RED);
    }
    return 1;
}

CMD:addtl(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    new idx = totaltl;
    new Float:pX, Float:pY, Float:pZ;
    GetPlayerPos(playerid, pX, pY, pZ);
    TL_Data[idx][tl_object_id] = 1290;
    new obj = CreateObject(1290, pX+1, pY+1, pZ, 0.0,0.0,0.0);
    EditObject(playerid, obj);
    p_temp[playerid][tl_id] = idx;
    return 1;
}

new Float:E_TL_OFFSETS[4][6][2] =
{
    { //0
        {0.0, -0.373774},
        {0.0, -0.366192},
        {0.0, -0.358126},
        {0.0, 0.280000},
        {0.0, 0.270000},
        {0.0, 0.270000}
    },//90
    {
        {-0.280000, 0.0},
        {-0.270000, 0.0},
        {-0.270000, 0.0},
        {0.373774, 0.0},
        {0.366192, 0.0},
        {0.358126, 0.0}
    },//180
    {
        {0.0, 0.373774},
        {0.0, 0.366192},
        {0.0, 0.358126},
        {0.0, -0.280000},
        {0.0, -0.270000},
        {0.0, -0.270000}
    },//270
    {
        {0.280000, 0.0},
        {0.270000, 0.0},
        {0.270000, 0.0},
        {-0.373774, 0.0},
        {-0.366192, 0.0},
        {-0.358126, 0.0}
    }
};

stock CreateTrafficLight(Float:x, Float:y, Float:z, Float:rz)
{
    new idx = totaltl, ofs_idx = -1, init_color;
    if(rz == 360.0) ofs_idx = 0, init_color = TLC_GREEN;
    if(rz == 90.0) ofs_idx = 1, init_color = TLC_RED;
    if(rz == 180.0) ofs_idx = 2, init_color = TLC_GREEN;
    if(rz == 270.0) ofs_idx = 3, init_color = TLC_RED;
    if(ofs_idx == -1) return 1;

    TL_Data[idx][tl_object_id][0] = CreateDynamicObject(1339, x+0.000000, y+0.000000, z+1.000000, 0.000000, 0.000000, rz, -1, -1, -1, 300.00, 300.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][0], 0, 10837, "airroadsigns_sfse", "CJ_LAMPPOST1", 0x00000000);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][0], 1, 19480, "signsurf", "sign", 0x00000000);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][0], 2, 10837, "airroadsigns_sfse", "CJ_LAMPPOST1", 0x00000000);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][0], 3, 10837, "airroadsigns_sfse", "CJ_LAMPPOST1", 0x00000000);

    TL_Data[idx][tl_object_id][1] = CreateDynamicObject(1254, x+E_TL_OFFSETS[ofs_idx][0][0], y+E_TL_OFFSETS[ofs_idx][0][1], z+1.336896, 0.000000, 0.000000, rz, -1, -1, -1, 50.00, 50.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][1], 0, 19119, "plainhelmets", "plainhelmet2", 0x00000000);
    TL_Data[idx][tl_object_id][2] = CreateDynamicObject(1254, x+E_TL_OFFSETS[ofs_idx][1][0], y+E_TL_OFFSETS[ofs_idx][1][1], z+1.027026, 0.000000, 0.000000, rz, -1, -1, -1, 50.00, 50.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][2], 0, 19119, "plainhelmets", "plainhelmet5", 0x00000000);
    TL_Data[idx][tl_object_id][3] = CreateDynamicObject(1254, x+E_TL_OFFSETS[ofs_idx][2][0], y+E_TL_OFFSETS[ofs_idx][2][1], z+0.697163, 0.000000, 0.000000, rz, -1, -1, -1, 50.00, 50.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][3], 0, 19119, "plainhelmets", "plainhelmet3", 0x00000000);
    TL_Data[idx][tl_object_id][4] = CreateDynamicObject(1254, x+E_TL_OFFSETS[ofs_idx][3][0], y+E_TL_OFFSETS[ofs_idx][3][1], z+1.336896, 0.000000, 0.000000, rz, -1, -1, -1, 50.00, 50.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][4], 0, 19119, "plainhelmets", "plainhelmet2", 0x00000000);
    TL_Data[idx][tl_object_id][5] = CreateDynamicObject(1254, x+E_TL_OFFSETS[ofs_idx][4][0], y+E_TL_OFFSETS[ofs_idx][4][1], z+1.027026, 0.000000, 0.000000, rz, -1, -1, -1, 50.00, 50.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][5], 0, 19119, "plainhelmets", "plainhelmet5", 0x00000000);
    TL_Data[idx][tl_object_id][6] = CreateDynamicObject(1254, x+E_TL_OFFSETS[ofs_idx][5][0], y+E_TL_OFFSETS[ofs_idx][5][1], z+0.697163, 0.000000, 0.000000, rz, -1, -1, -1, 50.00, 50.00);
    SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][6], 0, 19119, "plainhelmets", "plainhelmet3", 0x00000000);

    TL_Data[idx][tl_object_id][7] = CreateDynamicObject(1290, x, y, z, 0.000000, 0.000007, rz, -1, -1, -1, 50.0, 50.0);
    SetTrafficLightColor(idx, init_color);
    return idx;
}

stock SetTrafficLightColor(idx, color)
{
    switch(color)
    {
        case TLC_AMBER:
        {
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][1], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][2], 0, 19119, "plainhelmets", "plainhelmet5", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][3], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][4], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][5], 0, 19119, "plainhelmets", "plainhelmet5", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][6], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
        }
        case TLC_GREEN:
        {
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][1], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][2], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][3], 0, 19119, "plainhelmets", "plainhelmet3", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][4], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][5], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][6], 0, 18646, "plainhelmets", "plainhelmet3", 0x00000000);
        }
        case TLC_RED:
        {
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][1], 0, 19119, "plainhelmets", "plainhelmet2", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][2], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][3], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][4], 0, 19119, "plainhelmets", "plainhelmet2", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][5], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][6], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
        }
        case TLC_OFF:
        {
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][1], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][2], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][3], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][4], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][5], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
            SetDynamicObjectMaterial(TL_Data[idx][tl_object_id][6], 0, 18646, "matcolours", "grey-60-percent", 0x00000000);
        }
    }
    TL_Data[idx][tl_color] = color;
    return 1;
}


forward create_trafficlights(i);
public create_trafficlights(i)
{
    TL_Data[i][tl_mysql_id] = cache_insert_id();
    return 1;
}


forward load_trafficlights();
public load_trafficlights()
{
    new rows, time = GetTickCount();

    cache_get_row_count(rows);
    if(rows)
    {
        for(new idx; idx < rows; idx++)
        {
            cache_get_value_name_int(idx, "tl_mysql_id",TL_Data[idx][tl_mysql_id]);

            cache_get_value_name_float(idx, "tl_object_pos_X", TL_Data[idx][tl_object_pos][0]);
            cache_get_value_name_float(idx, "tl_object_pos_Y", TL_Data[idx][tl_object_pos][1]);
            cache_get_value_name_float(idx, "tl_object_pos_Z", TL_Data[idx][tl_object_pos][2]);
            cache_get_value_name_float(idx, "tl_object_pos_RZ",TL_Data[idx][tl_object_pos][3]);

            cache_get_value_name_float(idx, "tl_area_pos_X1", TL_Data[idx][tl_area_pos][0]);
            cache_get_value_name_float(idx, "tl_area_pos_Y1", TL_Data[idx][tl_area_pos][1]);
            cache_get_value_name_float(idx, "tl_area_pos_X2", TL_Data[idx][tl_area_pos][2]);
            cache_get_value_name_float(idx, "tl_area_pos_Y2", TL_Data[idx][tl_area_pos][3]);


            CreateTrafficLight(TL_Data[idx][tl_object_pos][0], TL_Data[idx][tl_object_pos][1], TL_Data[idx][tl_object_pos][2], TL_Data[idx][tl_object_pos][3]);

            TL_Data[idx][tl_area] = CreateDynamicRectangle(TL_Data[idx][tl_area_pos][0], TL_Data[idx][tl_area_pos][1], TL_Data[idx][tl_area_pos][2], TL_Data[idx][tl_area_pos][3]);
            UpdateAreaInfo(TL_Data[idx][tl_area], TYPE_TRAFFICLIGHTS, AREA_SUBTYPE_INVALID_ID, idx);
            totaltl++;
        }
    }
    printf("Светофоров загружено загружено: %i за %d мс",totaltl,GetTickCount()-time);
    return true;
}
