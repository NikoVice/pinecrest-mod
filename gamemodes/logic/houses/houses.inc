//Дома
forward load_house();
public load_house()
{
    new time = GetTickCount(),
        rows,
        data[166], temp_id;

    cache_get_row_count(rows);
    if(rows)
    {
        for(new idx; idx < rows; idx++)
        {
            cache_get_value_name_int(idx, "h_mysql_id", temp_id);
            h_info[temp_id][h_mysql_id] = temp_id;

            cache_get_value_name_int(idx, "h_user_id",h_info[temp_id][h_user_id]);
            cache_get_value_name_float(idx, "h_enterx",h_info[temp_id][h_enter][0]);
            cache_get_value_name_float(idx, "h_entery",h_info[temp_id][h_enter][1]);
            cache_get_value_name_float(idx, "h_enterz",h_info[temp_id][h_enter][2]);

            cache_get_value_name_float(idx, "h_entera",h_info[temp_id][h_enter][3]);
            cache_get_value_name_int(idx, "h_rent",h_info[temp_id][h_rent]);
            cache_get_value_name(idx,"h_owner",h_info[temp_id][h_owner],MAX_PLAYER_NAME);
            cache_get_value_name_int(idx, "h_value",h_info[temp_id][h_value]);
            cache_get_value_name_int(idx, "h_lock",h_info[temp_id][h_lock]);
            cache_get_value_name_int(idx, "h_int",h_info[temp_id][h_int]);
            cache_get_value_name_int(idx, "h_squar",h_info[temp_id][h_squar]);
            if(h_info[temp_id][h_int] < 0) h_info[temp_id][h_int] = 0;
            if(h_info[temp_id][h_squar] < 1) h_info[temp_id][h_squar] = 1;

            cache_get_value_name_int(idx, "h_g_lock",h_info[temp_id][h_garage_lock]);
            // cache_get_value_name_int(idx, "h_g_count",h_info[temp_id][h_garage_count]);
            cache_get_value_name_float(idx, "h_g_enterx",h_info[temp_id][h_garage_enter][0]);
            cache_get_value_name_float(idx, "h_g_entery",h_info[temp_id][h_garage_enter][1]);
            cache_get_value_name_float(idx, "h_g_enterz",h_info[temp_id][h_garage_enter][2]);
            cache_get_value_name_float(idx, "h_g_enterr",h_info[temp_id][h_garage_enter][3]);

            cache_get_value_name_int(idx, "h_improve_0", h_info[temp_id][h_improve][SUBSIDY]);
            cache_get_value_name_int(idx, "h_improve_1", h_info[temp_id][h_improve][RENTERS]);
            cache_get_value_name_int(idx, "h_improve_2", h_info[temp_id][h_improve][BASEMENT]);
            cache_get_value_name_int(idx, "h_improve_3", h_info[temp_id][h_improve][UNDERGROUND]);

            cache_get_value_name_int(idx, "h_r_user_id_0", h_info[temp_id][h_r_user_id][0]);
            cache_get_value_name_int(idx, "h_r_user_id_1", h_info[temp_id][h_r_user_id][1]);
            cache_get_value_name_int(idx, "h_r_user_id_2", h_info[temp_id][h_r_user_id][2]);
            cache_get_value_name_int(idx, "h_r_user_id_3", h_info[temp_id][h_r_user_id][3]);
            cache_get_value_name_int(idx, "h_r_user_id_4", h_info[temp_id][h_r_user_id][4]);

            cache_get_value_name_int(idx, "h_r_price_0", h_info[temp_id][h_r_price][0]);
            cache_get_value_name_int(idx, "h_r_price_1", h_info[temp_id][h_r_price][1]);
            cache_get_value_name_int(idx, "h_r_price_2", h_info[temp_id][h_r_price][2]);
            cache_get_value_name_int(idx, "h_r_price_3", h_info[temp_id][h_r_price][3]);
            cache_get_value_name_int(idx, "h_r_price_4", h_info[temp_id][h_r_price][4]);

            cache_get_value_name_int(idx, "h_r_days_0", h_info[temp_id][h_r_days][0]);
            cache_get_value_name_int(idx, "h_r_days_1", h_info[temp_id][h_r_days][1]);
            cache_get_value_name_int(idx, "h_r_days_2", h_info[temp_id][h_r_days][2]);
            cache_get_value_name_int(idx, "h_r_days_3", h_info[temp_id][h_r_days][3]);
            cache_get_value_name_int(idx, "h_r_days_4", h_info[temp_id][h_r_days][4]);

            cache_get_value_name_int(idx, "h_family_id", h_info[temp_id][h_family_id]);
            cache_get_value_name_int(idx, "h_attic_lock", h_info[temp_id][h_attic_lock]);
            cache_get_value_name_int(idx, "h_underground_lock", h_info[temp_id][h_underground_lock]);

            cache_get_value_name_int(idx, "h_auction_bet", h_info[temp_id][h_auction_bet]);
            cache_get_value_name_int(idx, "h_auction_time", h_info[temp_id][h_auction_time]);
            cache_get_value_name_int(idx, "h_auction_user_id", h_info[temp_id][h_auction_user_id]);

            cache_get_value_name_int(idx, "h_owned_at", h_info[temp_id][h_owned_at]);
            cache_get_value_name_int(idx, "h_paydays_received", h_info[temp_id][h_paydays_received]);

            cache_get_value_name_int(idx, "h_delete", h_info[temp_id][h_delete]);
            cache_get_value_name_int(idx, "h_delete_time", h_info[temp_id][h_delete_time]);

            cache_get_value_name_int(idx, "h_panel_items", h_info[temp_id][h_panel_items]);

            cache_get_value_name(idx, "h_garden_items", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
            sscanf(data, "p<|>a<i>[28]", h_info[temp_id][h_garden_items]);

            cache_get_value_name(idx, "h_mapping_id", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
            sscanf(data, "p<|>a<i>[27]", h_info[temp_id][h_mapping_id]);

            cache_get_value_name(idx, "h_garage_id", data); // 0|0|0
            sscanf(data, "p<|>a<i>[3]", h_info[temp_id][h_garage_id]);

            cache_get_value_name(idx, "h_gate_pos", data); // 0.0|0.0|0.0|0.0
            sscanf(data, "p<|>a<f>[4]", h_info[temp_id][h_gate_pos]);
            cache_get_value_name(idx, "h_air_pos", data); // 0.0|0.0|0.0|0.0
            sscanf(data, "p<|>a<f>[4]", h_info[temp_id][h_air_pos]);

            cache_get_value_name_int(idx, "h_boat_status", h_info[temp_id][h_boat_status]);

            if(h_ints[h_info[temp_id][h_squar]-1][h_info[temp_id][h_int]][i_int] == HOUSE_INT_ID_REPAIR) House_Repair(temp_id);
            if(h_info[temp_id][h_squar] > 1) Garage_Repair(temp_id);

            if(h_info[temp_id][h_gate_pos][0] != 0.0 || h_info[temp_id][h_gate_pos][1] != 0.0)
            {
                h_info[temp_id][h_gate] = CreateDynamicObject(19912, h_info[temp_id][h_gate_pos][0], h_info[temp_id][h_gate_pos][1], h_info[temp_id][h_gate_pos][2], 0.0, 0.0, h_info[temp_id][h_gate_pos][3], -1, -1, -1, 120.0, 120.0);
                gate_house_idx[totalgatehouse] = temp_id;
                totalgatehouse++;
            }
            else h_info[temp_id][h_gate] = INVALID_OBJECT_ID;

            h_info[temp_id][h_robbery] = 0;
            h_info[temp_id][h_robbery_count] = 10;
            h_info[temp_id][h_rob_house] = 0;
            h_info[temp_id][h_rob_house_block] = 0;
            h_info[temp_id][h_rob_house_signaling] = random(2);
            //h_info[temp_id][h_inventory_use] = INVALID_PLAYER_ID;
            
            /*
            if(h_info[temp_id][h_owned_at]+2419200 < timestamp && h_info[temp_id][h_user_id] != INVALID_MYSQL_ID)
            {
                h_info[temp_id][h_owned_at] = timestamp;
                if(h_info[temp_id][h_paydays_received] < 15) h_info[idx][h_paydays_received] = -1;
            }
            */

            h_info[temp_id][h_underground_player_use][0] =
            h_info[temp_id][h_underground_player_use][1] =
            h_info[temp_id][h_underground_player_use][2] =
            h_info[temp_id][h_underground_player_use][3] =
            h_info[temp_id][h_underground_player_use][4] = INVALID_PLAYER_ID;

            if(h_info[temp_id][h_delete] == 0) update_house(temp_id);
            totalhouses = temp_id+1;
        }
    }
    create_house_data();
    printf("Домов загружено: %d за %i мс", rows,GetTickCount()-time);
    return true;
}


save_house(houseid)
{
    if(houseid == -1) return 1;

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `house` SET" \
    "`h_enterx`= '%f',"\
    "`h_entery`= '%f',"\
    "`h_enterz`= '%f',"\
    "`h_entera`= '%f',"\
    "`h_rent`= %d,"\
    "`h_owner`='%s',"\
    "`h_value`= %d ,"\
    "`h_int`= %d ,"\
    "`h_lock`= %d ,"\
    "`h_user_id`= %d,"\
    "`h_squar`= %d,"\
    "`h_g_lock`= %d,"\
    "`h_g_enterx`= '%f',"\
    "`h_g_entery`= '%f',"\
    "`h_g_enterz`= '%f',"\
    "`h_g_enterr`= '%f',"\
    "`h_improve_0` = %d,"\
    "`h_improve_1` = %d,"\
    "`h_improve_2` = %d,"\
    "`h_improve_3` = %d,"\
    "`h_r_user_id_0` = %d,"\
    "`h_r_user_id_1` = %d,"\
    "`h_r_user_id_2` = %d,"\
    "`h_r_user_id_3` = %d,"\
    "`h_r_user_id_4` = %d,"\
    "`h_r_price_0` = %d,"\
    "`h_r_price_1` = %d,"\
    "`h_r_price_2` = %d,"\
    "`h_r_price_3` = %d,"\
    "`h_r_price_4` = %d,"\
    "`h_r_days_0` = %d,"\
    "`h_r_days_1` = %d,"\
    "`h_r_days_2` = %d,"\
    "`h_r_days_3` = %d,"\
    "`h_r_days_4` = %d,"\
    "`h_family_id` = %d,"\
    "`h_attic_lock` = %d,"\
    "`h_underground_lock` = %d,"\
    "`h_auction_bet` = %d,"\
    "`h_auction_time` = %d,"\
    "`h_auction_user_id` = %d,"\
    "`h_owned_at` = %d,"\
    "`h_paydays_received` = %d,"\
    "`h_delete` = %d,"\
    "`h_delete_time` = %d,"\
    "`h_gate_pos` = '%f|%f|%f|%f',"\
    "`h_air_pos` = '%f|%f|%f|%f',"\
    "`h_boat_status` = %d,"\
    "`h_garden_items` = '%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d',"\
    "`h_panel_items` = %d"\
    " WHERE `h_mysql_id` = %d",
    h_info[houseid][h_enter][0],
    h_info[houseid][h_enter][1],
    h_info[houseid][h_enter][2],
    h_info[houseid][h_enter][3],
    h_info[houseid][h_rent],
    h_info[houseid][h_owner],
    h_info[houseid][h_value],
    h_info[houseid][h_int],
    h_info[houseid][h_lock],
    h_info[houseid][h_user_id],
    h_info[houseid][h_squar],
    h_info[houseid][h_garage_lock],
    h_info[houseid][h_garage_enter][0],
    h_info[houseid][h_garage_enter][1],
    h_info[houseid][h_garage_enter][2],
    h_info[houseid][h_garage_enter][3],
    h_info[houseid][h_improve][SUBSIDY],
    h_info[houseid][h_improve][RENTERS],
    h_info[houseid][h_improve][BASEMENT],
    h_info[houseid][h_improve][UNDERGROUND],

    h_info[houseid][h_r_user_id][0],
    h_info[houseid][h_r_user_id][1],
    h_info[houseid][h_r_user_id][2],
    h_info[houseid][h_r_user_id][3],
    h_info[houseid][h_r_user_id][4],
    h_info[houseid][h_r_price][0],
    h_info[houseid][h_r_price][1],
    h_info[houseid][h_r_price][2],
    h_info[houseid][h_r_price][3],
    h_info[houseid][h_r_price][4],
    h_info[houseid][h_r_days][0],
    h_info[houseid][h_r_days][1],
    h_info[houseid][h_r_days][2],
    h_info[houseid][h_r_days][3],
    h_info[houseid][h_r_days][4],
    h_info[houseid][h_family_id],
    h_info[houseid][h_attic_lock],
    h_info[houseid][h_underground_lock],
    h_info[houseid][h_auction_bet],
    h_info[houseid][h_auction_time],
    h_info[houseid][h_auction_user_id],
    h_info[houseid][h_owned_at],
    h_info[houseid][h_paydays_received],
    h_info[houseid][h_delete],
    h_info[houseid][h_delete_time],
    h_info[houseid][h_gate_pos][0],
    h_info[houseid][h_gate_pos][1],
    h_info[houseid][h_gate_pos][2],
    h_info[houseid][h_gate_pos][3],
    h_info[houseid][h_air_pos][0],
    h_info[houseid][h_air_pos][1],
    h_info[houseid][h_air_pos][2],
    h_info[houseid][h_air_pos][3],
    h_info[houseid][h_boat_status],
    h_info[houseid][h_garden_items][0],
    h_info[houseid][h_garden_items][1],
    h_info[houseid][h_garden_items][2],
    h_info[houseid][h_garden_items][3],
    h_info[houseid][h_garden_items][4],
    h_info[houseid][h_garden_items][5],
    h_info[houseid][h_garden_items][6],
    h_info[houseid][h_garden_items][7],
    h_info[houseid][h_garden_items][8],
    h_info[houseid][h_garden_items][9],
    h_info[houseid][h_garden_items][10],
    h_info[houseid][h_garden_items][11],
    h_info[houseid][h_garden_items][12],
    h_info[houseid][h_garden_items][13],
    h_info[houseid][h_garden_items][14],
    h_info[houseid][h_garden_items][15],
    h_info[houseid][h_garden_items][16],
    h_info[houseid][h_garden_items][17],
    h_info[houseid][h_garden_items][18],
    h_info[houseid][h_garden_items][19],
    h_info[houseid][h_garden_items][20],
    h_info[houseid][h_garden_items][21],
    h_info[houseid][h_garden_items][22],
    h_info[houseid][h_garden_items][23],
    h_info[houseid][h_garden_items][24],
    h_info[houseid][h_garden_items][25],
    h_info[houseid][h_garden_items][26],
    h_info[houseid][h_garden_items][27],
    h_info[houseid][h_panel_items],
    h_info[houseid][h_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return true;
}

create_house_data()
{
    new temp_count;
    for(new i; i < sizeof h_ints; i++)
    {
        for(new j; j < MAX_HOUSE_INT; j++)
        {
            house_door_exit_pickup[temp_count] = CreateDynamicPickup(HOUSE_PICKUP_DEFAULT_ID, 23, h_ints[i][j][i_spawn_pos][0],h_ints[i][j][i_spawn_pos][1], h_ints[i][j][i_spawn_pos][2]+0.1, -1, h_ints[i][j][i_int], -1);
            UpdatePickupInfo(house_door_exit_pickup[temp_count], TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_EXIT, -1);
            temp_count++;
        }
        if(i < sizeof g_info)
        {
            house_garage_exit_pickup[i] = CreateDynamicPickup(HOUSE_PICKUP_DEFAULT_ID, 23, g_info[i][g_pX], g_info[i][g_pY], g_info[i][g_pZ]+0.1, -1, -1, -1);
            UpdatePickupInfo(house_garage_exit_pickup[i], TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_G_DOOR, -1);

            house_garage_exit_area[i] = CreateDynamicSphere(g_info[i][g_vX], g_info[i][g_vY], g_info[i][g_vZ], 2.5, -1, -1, -1);
            UpdateAreaInfo(house_garage_exit_area[i], TYPE_HOUSE, AREA_SUBTYPE_HOUSE_G_EXIT, -1);
        }
    }

    new pickupid;

    //помещение с видеокартами: Подвал
    pickupid = CreateDynamicPickup(HOUSE_PICKUP_DEFAULT_ID, 23, 1837.7548,1567.0378,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_B_DOOR, -1);

    // рабы: Подпольное помещение
    pickupid = CreateDynamicPickup(HOUSE_PICKUP_DEFAULT_ID, 23, 329.6453,1859.1782,1013.0838, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_DOOR, -1);

    pickupid = CreateDynamicPickup(HOUSE_PICKUP_DEFAULT_ID, 23, 1832.8040,1572.3094,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_BASEMENT, -1);

    pickupid = CreateDynamicPickup(1239, 23, 1831.9258,1568.3647,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_VC_ALL, -1);

    pickupid = CreateDynamicPickup(1239, 23, 1833.4314,1565.6085,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_VC_ONE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 1831.7726,1565.6085,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_VC_TWO, -1);

    pickupid = CreateDynamicPickup(1239, 23, 1829.4767,1565.6085,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_VC_THREE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 1827.7792,1565.6085,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_VC_FOUR, -1);

    pickupid = CreateDynamicPickup(1239, 23, 1825.4254,1565.6085,1010.9188, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_VC_FIVE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 332.1813,1864.4664,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_ALL, -1);

    pickupid = CreateDynamicPickup(1239, 23, 328.2488,1867.9495,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_ONE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 328.2488,1870.4464,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_TWO, -1);

    pickupid = CreateDynamicPickup(1239, 23, 328.2488,1872.9445,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_THREE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 328.2488,1875.4513,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_FOUR, -1);

    pickupid = CreateDynamicPickup(1239, 23, 328.2488,1877.9257,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_FIVE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 334.3436,1867.9495,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_SIX, -1);

    pickupid = CreateDynamicPickup(1239, 23, 334.3436,1870.4464,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_SEVEN, -1);

    pickupid = CreateDynamicPickup(1239, 23, 334.3436,1872.9445,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_EIGHT, -1);

    pickupid = CreateDynamicPickup(1239, 23, 334.3436,1875.4513,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_NINE, -1);

    pickupid = CreateDynamicPickup(1239, 23, 334.3436,1877.9257,1010.9078, -1, -1, -1);
    UpdatePickupInfo(pickupid, TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_U_TEN, -1);
    return 1;
}

update_house(h)
{
    if(h_info[h][h_delete] == 1) return 1;

    if(h == INVALID_HOUSE_ID)
    {
        printf("ERROR UPDATE HOUSE: %d", h);
        return 1;
    }

    if(IsValidDynamicMapIcon(h_info[h][h_icon])) DestroyDynamicMapIcon(h_info[h][h_icon]);
    if(IsValidDynamic3DTextLabel(h_info[h][h_text])) DestroyDynamic3DTextLabel(h_info[h][h_text]);
    /////////////////////////////////////////////////
    new need_pickup, house_pickup;
    need_pickup = (h_info[h][h_user_id] == INVALID_MYSQL_ID ? (1273) : (19522));
    if(IsValidDynamicPickup(h_info[h][h_pickup_enter]))
    {
        house_pickup = Streamer_GetIntData(STREAMER_TYPE_PICKUP, h_info[h][h_pickup_enter], E_STREAMER_MODEL_ID);
        if(house_pickup != need_pickup)
            Streamer_SetIntData(STREAMER_TYPE_PICKUP, h_info[h][h_pickup_enter], E_STREAMER_MODEL_ID, need_pickup);
    }
    else
    {
        h_info[h][h_pickup_enter] = CreateDynamicPickup(need_pickup, 23, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2], -1, -1, -1, 50.0);
        UpdatePickupInfo(h_info[h][h_pickup_enter], TYPE_HOUSE, PICKUP_SUBTYPE_HOUSE_ENTER, h);
    }
    foreach(new i: Player)
    {
        if(IsPlayerInRangeOfPoint(i, 50.0, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2]))
            Streamer_UpdateEx(i, h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2], 0, 0);
    }
    //////////////////////////////////
    STRING_GLOBAL[0] = EOS;
    if(h_info[h][h_user_id] == INVALID_MYSQL_ID)
    {
        h_info[h][h_garage_lock] = 1;
        f(STRING_GLOBAL,"Дом"I" №%d\n"W"Цена:"I" %d$"W"\nГараж: "I"%s",h,h_info[h][h_value], h_info[h][h_squar] > 1 ? "Есть":"Нет");
    }
    else
        f(STRING_GLOBAL,"Дом"I" №%d\n"W"Владелец:"I" %s"W"\nГараж: "I"%s",h,h_info[h][h_owner], h_info[h][h_squar] > 1 ? "Есть":"Нет");

    new family_idx = GetFamilyIDFromHouseID(h);
    if(family_idx != -1) f(STRING_GLOBAL, "%s\n"W"Дом объединения: "I"%s", STRING_GLOBAL, FamilyData[family_idx][fName]);

    h_info[h][h_text] = CreateDynamic3DTextLabel(STRING_GLOBAL,0xFFFFFFFF,h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2],5.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL);
    //////////////////////////////////////
    h_info[h][h_icon] = CreateDynamicMapIcon(h_info[h][h_enter][0], h_info[h][h_enter][1], h_info[h][h_enter][2], h_info[h][h_user_id] == INVALID_MYSQL_ID ? 31 : 32, -1, 0, -1, -1, 100.0);
    //////////////////////////////////////
    new h_class = h_info[h][h_squar] - 1, int_id = h_info[h][h_int];

    new Float:streamer_pos_x;

    if(h_class > 0)
    {
        if(h_info[h][h_improve][BASEMENT] == 1)
        {
            if(!IsValidDynamic3DTextLabel(h_info[h][h_attic_text])) h_info[h][h_attic_text] = CreateDynamic3DTextLabel("<< Оружейный стол >>",COLOR_MAIN,718.2767,-1.2356,1000.6981+0.4,15.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID, streamer_TESTLOL, h+50, h_ints[h_class][int_id][i_int], -1);
        }
        else
        {
            if(IsValidDynamic3DTextLabel(h_info[h][h_attic_text])) DestroyDynamic3DTextLabel(h_info[h][h_attic_text]);
        }

        h_class--;

        if(IsValidDynamicArea(h_info[h][h_garage_area][0])) Streamer_GetFloatData(STREAMER_TYPE_AREA, h_info[h][h_garage_area][0], E_STREAMER_X, streamer_pos_x);
        if(!IsValidDynamicArea(h_info[h][h_garage_area][0]) || streamer_pos_x != h_info[h][h_garage_enter][0])
        {
            if(IsValidDynamicArea(h_info[h][h_garage_area][0])) DestroyDynamicArea(h_info[h][h_garage_area][0]);
            h_info[h][h_garage_area][0] = CreateDynamicSphere(h_info[h][h_garage_enter][0], h_info[h][h_garage_enter][1], h_info[h][h_garage_enter][2], 4.5, -1, -1, -1);
            UpdateAreaInfo(h_info[h][h_garage_area][0], TYPE_HOUSE, AREA_SUBTYPE_HOUSE_G_ENTER, h);
        }

        if(IsValidDynamic3DTextLabel(h_info[h][h_garage_text])) Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, h_info[h][h_garage_text], E_STREAMER_X, streamer_pos_x);
        if(!IsValidDynamic3DTextLabel(h_info[h][h_garage_text]) || streamer_pos_x != h_info[h][h_garage_enter][0])
        {
            if(IsValidDynamic3DTextLabel(h_info[h][h_garage_text])) DestroyDynamic3DTextLabel(h_info[h][h_garage_text]);
            f(STRING_GLOBAL, "<< Заезд в гараж >>\n\nДом: "W"#%d"I"\n\nИспользуйте "W"ALT"I" чтобы заехать в гараж",h);
            h_info[h][h_garage_text] = CreateDynamic3DTextLabel(STRING_GLOBAL,COLOR_MAIN,h_info[h][h_garage_enter][0], h_info[h][h_garage_enter][1], h_info[h][h_garage_enter][2],10.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,1);
        }
    }
    return 1;
}

SetPlayerHousePos(playerid, h, h_class, int_id)
{
    if(h_class < 0) h_class = 0;
    SetPlayerInterior(playerid,h_ints[h_class][int_id][i_int]);
    SetPlayerPos(playerid, h_ints[h_class][int_id][i_spawn_pos][0], h_ints[h_class][int_id][i_spawn_pos][1], h_ints[h_class][int_id][i_spawn_pos][2]+0.3);
    SetPlayerVirtualWorld(playerid, h+50);
    TogglePlayerControllable(playerid, 0);

    p_temp[playerid][UnFreezeFix] = 1;
    p_temp[playerid][UnFreezeTimerFix] = timestamp + 2;
}

IsKeyHouseDoor(playerid, house_id)
{
    if(h_info[house_id][h_family_id] != -1 && h_info[house_id][h_family_id] == p_info[playerid][family_id])
        return 1;

    if(p_info[playerid][key_h_rent] == house_id)
        return 1;

    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        if(GetPlayerHouseID(playerid, i) == house_id)
            return 1;
    }
    return 0;
}
SetPlayerHouseActive(playerid, house_id)
{
    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        if(GetPlayerHouseID(playerid, i) == house_id)
        {
            p_info[playerid][active_house_id] = i;
            break;
        }
    }
}

GetHouseGameID(playerid)
{
    new houseId = GetPlayerVirtualWorld(playerid)-50;
    if(houseId < 0 || houseId > MAX_HOUSE) return INVALID_HOUSE_ID;

    if(houseId == p_info[playerid][key_h_rent])
        return houseId; //если арендатор - сразу понимаем что это его дом!

    new h_class = h_info[houseId][h_squar]-1, // если в каком-то доме то проверяем точно ли
        int_id = h_info[houseId][h_int];

    if(h_class >= 0 && int_id >= 0 && GetPlayerInterior(playerid) == h_ints[h_class][int_id][i_int])
        return houseId;

    if(PlayerToPoint(50.0, playerid, h_ints[h_class][int_id][i_spawn_pos][0], h_ints[h_class][int_id][i_spawn_pos][1], h_ints[h_class][int_id][i_spawn_pos][2]))
        return houseId;

    h_class--; // если в каком-то гараже то проверяем точно ли
    if(h_class >= 0)
    {
        if(PlayerToPoint(75.0, playerid, g_info[h_class][g_pX], g_info[h_class][g_pY], g_info[h_class][g_pZ]))
        return houseId;
    }

    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        if(GetPlayerHouseID(playerid, i) == houseId)//если владелец
            return houseId;
    }
    return INVALID_HOUSE_ID;
}
/*
GetGameIDHouseFromDB(database_id)
{ ГОВНО
    new id_h = -1;
    for(new h = database_id+30; h != database_id-30; h--)
    {
        if(h_info[h][h_mysql_id] == INVALID_MYSQL_ID) continue;
        if(h < 0 || h > totalhouses) continue;
        if(database_id == h_info[h][h_mysql_id])
        {
            id_h = h;
            break;
        }
    }
    if(id_h == -1)
    {
        for(new h = totalhouses-1; h != -1; h--)
        {
            if(database_id == h_info[h][h_mysql_id])
            {
                id_h = h;
                break;
            }
        }
    }
    return id_h;
}
*/
/////////////////////////////
menu_house_settings(playerid)
{
    STRING_GLOBAL[0] = EOS;
    new h = GetPlayerHouseID(playerid);
    if(h == INVALID_HOUSE_ID) return 1;
    if(h == p_info[playerid][key_h_rent]) f(STRING_GLOBAL, ""I"[1]"W" Выселиться из дома\n"I"[2]"W" Информация по аренде");
    else
    {
        new sLockStatus[][] = {"Закрыть", "Открыть"};
        if(h_info[h][h_squar] > 1) format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""I"[1]"W" %s входную дверь\n"I"[2]"W" %s двери подвала\n"I"[3]"W" %s двери подпольного помещения\n"I"[4]"W" %s двери гаража\n"I"[5]"W" Инвентарь дома\n"I"[6]"W" Улучшения для дома/гаража\n"I"[7]"W" Меню подселения\n"I"[8]"W" Продать дом (государству/аукцион/игрок)",
            sLockStatus[h_info[h][h_lock]], sLockStatus[h_info[h][h_attic_lock]], sLockStatus[h_info[h][h_underground_lock]], sLockStatus[h_info[h][h_garage_lock]]);

        else format(STRING_GLOBAL, sizeof STRING_GLOBAL, ""I"[1]"W" %s входную дверь\n"I"[2]"W" %s двери подвала\n"I"[3]"W" %s двери подпольного помещения\n"I"[4]"W" Инвентарь дома\n"I"[5]"W" Улучшения для дома/гаража\n"I"[6]"W" Меню подселения\n"I"[7]"W" Продать дом (государству/аукцион/игрок)",
            sLockStatus[h_info[h][h_lock]], sLockStatus[h_info[h][h_attic_lock]], sLockStatus[h_info[h][h_underground_lock]]);
    }
    return ShowPlayerDialog(playerid, D_HOUSE_SETTINGS, DIALOG_STYLE_LIST, ""I"Управление домом", STRING_GLOBAL, "Выбрать", "Отмена");
}

// ремонт в доме
#define TEXTURE_HOUSE_PRICE 25000
#define HOUSE_MAPPING_TIME 180000

enum e_FornitureTexture
{
    ft_Price,
    ft_ObjectID,
    ft_TxdName[36],
    ft_TextureName[36]
}
static const FornitureTexture_Foor[][e_FornitureTexture] = {
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "la_flair1"},  // 1 class
    {TEXTURE_HOUSE_PRICE, 14479, "skuzzy_motelmain", "mp_CJ_Laminate1"},
    {TEXTURE_HOUSE_PRICE, 4558, "lanlacmab_lan2", "sl_gallerywall1"}, // end 1 class
    {TEXTURE_HOUSE_PRICE, 18031, "cj_exp", "mp_furn_floor"},// 2 class
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS1_Kwall"},
    {TEXTURE_HOUSE_PRICE, 4101, "stapl", "sl_laexpowall1"}, //5/ end 2 class
    {TEXTURE_HOUSE_PRICE, 14777, "int_casinoint3", "GB_midbar05"}, //6/ 3 class
    {TEXTURE_HOUSE_PRICE, 14537, "pdomebar", "club_floor2_sfwTEST"},//7/
    {TEXTURE_HOUSE_PRICE, 14582, "casmafbar", "ab_CasRomTile1"},//8/
    {TEXTURE_HOUSE_PRICE, 17555, "eastbeach3c_lae2", "decobuild2d_LAn"},//9/
    {TEXTURE_HOUSE_PRICE, 15055, "svlamid", "AH_flroortile3"},//10/ 4 class
    {TEXTURE_HOUSE_PRICE, 14506, "imy_motel", "ab_tile1"},//11/
    {TEXTURE_HOUSE_PRICE, 11301, "carshow_sfse", "ws_officy_ceiling"},//12/
    {TEXTURE_HOUSE_PRICE, 6869, "vegastemp1", "vgnbarb_wall_128"},//13/
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "sl_laglasswall1"},//14/
    {TEXTURE_HOUSE_PRICE, 3984, "lanbloki", "greytile_LA"},//15/garage1
    {TEXTURE_HOUSE_PRICE, 6064, "law_beach1", "musk1"},//16/garage2
    //new by Vlad
    {TEXTURE_HOUSE_PRICE, 16639, "a51_labs", "dam_terazzo"},
    {TEXTURE_HOUSE_PRICE, 14581, "ab_mafiasuitea", "cof_wood2"},
    {TEXTURE_HOUSE_PRICE, 14581, "ab_mafiasuitea", "walp45S"},
    {TEXTURE_HOUSE_PRICE, 14581, "ab_mafiasuitea", "wood02S"},
    {TEXTURE_HOUSE_PRICE, 3603, "bevmans01_la", "sjmlahus29"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "AH_flrdiamonds"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "AH_flroortile5"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "AH_flroortile9"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "mp_carter_tilewall"},
    {TEXTURE_HOUSE_PRICE, 14383, "burg_1", "carpet4kb"},
    {TEXTURE_HOUSE_PRICE, 3741, "cehillhse14", "swimpoolbtm1_128"},
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "crazy paving"},
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "sl_laglasswall2"},
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "sl_laglasswall1"},
    {TEXTURE_HOUSE_PRICE, 14674, "civic02cj", "ab_hosWallUpr"},
    {TEXTURE_HOUSE_PRICE, 18028, "cj_bar2", "GB_nastybar07"},
    {TEXTURE_HOUSE_PRICE, 2127, "cj_kitchen", "marble2"},
    {TEXTURE_HOUSE_PRICE, 2423, "cj_ff_counters", "shop_floor1"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "mp_gs_kitchfloor"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "mp_gs_pooltiles"},
    {TEXTURE_HOUSE_PRICE, 18008, "intclothesa", "mp_cloth_vicfloor"},
    {TEXTURE_HOUSE_PRICE, 14506, "imy_motel", "ab_tile1"},
    {TEXTURE_HOUSE_PRICE, 14853, "gen_pol_vegas", "office_wallnu1"},
    {TEXTURE_HOUSE_PRICE, 18029, "genintintsmallrest", "GB_restaursmll07"},
    {TEXTURE_HOUSE_PRICE, 18029, "genintintsmallrest", "GB_restaursmll03"},
    {TEXTURE_HOUSE_PRICE, 18022, "genintintfasta", "CJ_TILE1"},
    {TEXTURE_HOUSE_PRICE, 17555, "eastbeach3c_lae2", "decobuild2d_LAn"},
    {TEXTURE_HOUSE_PRICE, 14530, "estate2", "man_parquet"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "AH_flroortile12"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "la_flair1"},
    {TEXTURE_HOUSE_PRICE, 14708, "labig1int2", "HS2_floor4"},
    {TEXTURE_HOUSE_PRICE, 14706, "labig2int2", "wood14S"},
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS1_Kwall"},
    {TEXTURE_HOUSE_PRICE, 4558, "lanlacmab_lan2", "sl_gallerywall1"},
    {TEXTURE_HOUSE_PRICE, 4558, "lanlacmab_lan2", "sl_galleryplaza1"},
    {TEXTURE_HOUSE_PRICE, 4558, "lanlacmab_lan2", "sl_plazatile02"},
    {TEXTURE_HOUSE_PRICE, 14801, "lee_bdupsmain", "Bdup_KitchFloor"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "mp_carter_tilewall"},
    {TEXTURE_HOUSE_PRICE, 14832, "lee_stripclub", "Strip_ceiling"},
    {TEXTURE_HOUSE_PRICE, 14623, "mafcasmain", "ab_tileStar"},
    {TEXTURE_HOUSE_PRICE, 14389, "madpoolbit", "AH_flroortile4"},
    {TEXTURE_HOUSE_PRICE, 14425, "madbedrooms", "ah_wallstyle2"},
    {TEXTURE_HOUSE_PRICE, 14590, "mafcastopfoor", "ab_carpet01"},
    {TEXTURE_HOUSE_PRICE, 14847, "mp_policesf", "mp_cop_vinyl"},
    {TEXTURE_HOUSE_PRICE, 14847, "mp_policesf", "mp_cop_tile"},
    {TEXTURE_HOUSE_PRICE, 15054, "savesfmid", "AH_walltile5"},
    {TEXTURE_HOUSE_PRICE, 15054, "savesfmid", "AH_flroortile8"},
    {TEXTURE_HOUSE_PRICE, 14760, "sfhosemed2", "ah_poshwdflr1"},
    {TEXTURE_HOUSE_PRICE, 14748, "sfhsm1", "AH_bigwoodthing"},
    {TEXTURE_HOUSE_PRICE, 14750, "sfhsm2", "ston09S"},
    {TEXTURE_HOUSE_PRICE, 14758, "sfmansion1", "AH_flroortile6"},
    {TEXTURE_HOUSE_PRICE, 9220, "sfn_apart02sfn", "concreteslab"},
    {TEXTURE_HOUSE_PRICE, 4550, "skyscr1_lan2", "sl_skyscrpr02wall1"},
    {TEXTURE_HOUSE_PRICE, 14756, "smallsfhs", "AH_flroortiledirt1"},
    {TEXTURE_HOUSE_PRICE, 15058, "svvgmid", "AH_flroortile11"},
    {TEXTURE_HOUSE_PRICE, 6869, "vegastemp1", "vgnbarb_wall_128"},
    {TEXTURE_HOUSE_PRICE, 15033, "vegassavesmal", "ah_corn2"},
    {TEXTURE_HOUSE_PRICE, 14710, "vgshm3int2", "HSV_3carpet2"}
};

static const FornitureTexture_Wall[][e_FornitureTexture] = {
    {TEXTURE_HOUSE_PRICE, 14661, "int_tatoo", "tattoo_wall1"}, // 1 class
    {TEXTURE_HOUSE_PRICE, 14526, "sweetsmain", "ah_wpaper12"},
    {TEXTURE_HOUSE_PRICE, 3741, "cehillhse14", "swimpoolbtm1_128"},
    {TEXTURE_HOUSE_PRICE, 6095, "shops01_law", "GB_chatwall03b"},// end 1 class
    {TEXTURE_HOUSE_PRICE, 14674, "civic02cj", "sl_hotelwall1"}, //4/ 2 class
    {TEXTURE_HOUSE_PRICE, 18008, "intclothesa", "mp_cloth_vicfloor"},//5/
    {TEXTURE_HOUSE_PRICE, 17511, "stadium_lae2", "forum1"}, //6/ // end 2 class
    {TEXTURE_HOUSE_PRICE, 1355, "break_s_bins", "marble1"}, //7/ 3 class
    {TEXTURE_HOUSE_PRICE, 18028, "cj_bar2", "GB_nastybar07"},//8/
    {TEXTURE_HOUSE_PRICE, 2423, "cj_ff_counters", "shop_floor1"},//9/
    {TEXTURE_HOUSE_PRICE, 18029, "genintintsmallrest", "GB_restaursmll09"},//10/
    {TEXTURE_HOUSE_PRICE, 2423, "cj_ff_counters", "CJ_worktop"},//11/
    {TEXTURE_HOUSE_PRICE, 14674, "civic02cj", "ab_hosWallUpr"},//12/
    {TEXTURE_HOUSE_PRICE, 14569, "traidman", "walpaper_dragn"},//13/ 4 class
    {TEXTURE_HOUSE_PRICE, 4833, "airprtrunway_las", "tuntest1las"},//14/
    {TEXTURE_HOUSE_PRICE, 2215, "chick_tray", "plaincup_cb"},//15/
    {TEXTURE_HOUSE_PRICE, 14533, "pleas_dome", "club_zeb_SFW1"},//16/
    {TEXTURE_HOUSE_PRICE, 17146, "cuntwroad", "Tar_blenddrtwhiteline"},//17/
    {TEXTURE_HOUSE_PRICE, 18047, "gen_mun_counter", "mp_gun_metal"},//18/garage1
    {TEXTURE_HOUSE_PRICE, 14537, "pdomebar", "club_floor2_sfwTEST"},//19/garage2
    {TEXTURE_HOUSE_PRICE, 9583, "bigshap_sfw", "bridge_walls2_sfw"},//20/garage3
    //new by Vlad
    {TEXTURE_HOUSE_PRICE, 18029, "genintintsmallrest", "GB_restaursmll09"},
    {TEXTURE_HOUSE_PRICE, 18009, "genintrestrest1", "rest_wall5"},
    {TEXTURE_HOUSE_PRICE, 14853, "gen_pol_vegas", "mp_cop_panel"},
    {TEXTURE_HOUSE_PRICE, 5461, "glenpark6d_lae", "tiledwall01_LA"},
    {TEXTURE_HOUSE_PRICE, 14708, "labig1int2", "ab_mottleGrey"},
    {TEXTURE_HOUSE_PRICE, 1929, "kbroul2", "oliveash_256"},
    {TEXTURE_HOUSE_PRICE, 14707, "labig3int2", "WH_walls"},
    {TEXTURE_HOUSE_PRICE, 14707, "labig3int2", "HS2_3Wall9"},
    {TEXTURE_HOUSE_PRICE, 14707, "labig3int2", "HS2_3Wall7"},
    {TEXTURE_HOUSE_PRICE, 14707, "labig3int2", "HS2_3Wall10"},
    {TEXTURE_HOUSE_PRICE, 5444, "chicano10_lae", "gm_labuld2_d"},
    {TEXTURE_HOUSE_PRICE, 1809, "cj_hi_fi", "CJ_speaker_6"},
    {TEXTURE_HOUSE_PRICE, 1716, "cj_seating", "CJ_SHINYWOOD"},
    {TEXTURE_HOUSE_PRICE, 10398, "countryclub_sfs", "hc_wall2"},
    {TEXTURE_HOUSE_PRICE, 17146, "cuntwroad", "Tar_blenddrtwhiteline"},
    {TEXTURE_HOUSE_PRICE, 16338, "dam_genroom", "dam_terazzoedge"},
    {TEXTURE_HOUSE_PRICE, 4887, "downtown_las", "pershing1_LAn"},
    {TEXTURE_HOUSE_PRICE, 8498, "excalibur", "excaliburwall03_128"},
    {TEXTURE_HOUSE_PRICE, 18029, "genintintsmallrest", "GB_restaursmll03"},
    {TEXTURE_HOUSE_PRICE, 14652, "ab_trukstpa", "CJ_CORD"},
    {TEXTURE_HOUSE_PRICE, 4833, "airprtrunway_las", "tuntest1las"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "ah_wpaper7"},
    {TEXTURE_HOUSE_PRICE, 4593, "buildblk55", "sl_plazatile01"},
    {TEXTURE_HOUSE_PRICE, 14383, "burg_1", "wallpapkb1"},
    {TEXTURE_HOUSE_PRICE, 14415, "carter_block_2", "walp29S"},
    {TEXTURE_HOUSE_PRICE, 2176, "casino_props", "marblebox"},
    {TEXTURE_HOUSE_PRICE, 3314, "ce_burbhouse", "sw_wallbrick_06"},
    {TEXTURE_HOUSE_PRICE, 14707, "labig3int2", "HS2_3Carpet1"},
    {TEXTURE_HOUSE_PRICE, 14707, "labig3int2", "burglry_wall6"},
    {TEXTURE_HOUSE_PRICE, 15048, "labigsave", "ah_carpet2kb"},
    {TEXTURE_HOUSE_PRICE, 14706, "labig2int2", "HS2_3Wall6"},
    {TEXTURE_HOUSE_PRICE, 14706, "labig2int2", "mp_apt1_kitchwallpaper"},
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS2_Artex3"},
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS1_wall1"},
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS1_Kwall2"},
    {TEXTURE_HOUSE_PRICE, 5267, "lashops91_las2", "laspowrec2"},
    {TEXTURE_HOUSE_PRICE, 6064, "law_beach1", "musk1"},
    {TEXTURE_HOUSE_PRICE, 3676, "lawnxref", "lasthoose4"},
    {TEXTURE_HOUSE_PRICE, 14832, "lee_stripclub", "Strip_sofa2"},
    {TEXTURE_HOUSE_PRICE, 14839, "lee_strippriv", "WH_Sofa"},
    {TEXTURE_HOUSE_PRICE, 14389, "madpoolbit", "AH_flroortile4"},
    {TEXTURE_HOUSE_PRICE, 14425, "madbedrooms", "ah_wallstyle2"},
    {TEXTURE_HOUSE_PRICE, 14623, "mafcasmain", "marble_wall"},
    {TEXTURE_HOUSE_PRICE, 14590, "mafcastopfoor", "ab_carpet01"},
    {TEXTURE_HOUSE_PRICE, 14590, "mafcastopfoor", "donut_wall1"},
    {TEXTURE_HOUSE_PRICE, 10973, "mall_sfse", "ws_trainstationwin2"},
    {TEXTURE_HOUSE_PRICE, 14702, "masmall3int2", "HS3_wall6"},
    {TEXTURE_HOUSE_PRICE, 14847, "mp_policesf", "mp_cop_marble"},
    {TEXTURE_HOUSE_PRICE, 14593, "papaerchaseoffice", "wall_stone6_256"},
    {TEXTURE_HOUSE_PRICE, 2702, "pick_up", "cj_fambly2"},
    {TEXTURE_HOUSE_PRICE, 18036, "range_main", "gun_galss1"},
    {TEXTURE_HOUSE_PRICE, 14533, "pleas_dome", "club_zeb_SFW1"},
    {TEXTURE_HOUSE_PRICE, 15054, "savesfmid", "ah_pnwainscot"},
    {TEXTURE_HOUSE_PRICE, 5040, "shopliquor_las", "lasjmliq1"},
    {TEXTURE_HOUSE_PRICE, 6095, "shops01_law", "GB_chatwall03b"},
    {TEXTURE_HOUSE_PRICE, 14526, "sweetsmain", "ah_whitpanelceil"},
    {TEXTURE_HOUSE_PRICE, 14569, "traidman", "walpaper_dragn"},
    {TEXTURE_HOUSE_PRICE, 14569, "traidman", "pagodaroof4"},
    {TEXTURE_HOUSE_PRICE, 14385, "trailerkb", "tr_kit_1a"},
    {TEXTURE_HOUSE_PRICE, 14385, "trailerkb", "tr_wall2"},
    {TEXTURE_HOUSE_PRICE, 14385, "trailerkb", "tr_wood1"},
    {TEXTURE_HOUSE_PRICE, 8663, "triadcasino", "imperial03_128"},
    {TEXTURE_HOUSE_PRICE, 14560, "triad_bar", "triad_decor1"},
    {TEXTURE_HOUSE_PRICE, 6988, "vgnfremnt1", "casinowall1_256"},
    {TEXTURE_HOUSE_PRICE, 8463, "vgseland", "triadcarpet2"},
    {TEXTURE_HOUSE_PRICE, 7489, "vgntamotel", "vgncoctart1_256"},
    //my custom
    {TEXTURE_HOUSE_PRICE, 18265, "w_town3cs_t", "ws_redbrickold"},
    {TEXTURE_HOUSE_PRICE, 18202, "w_towncs_t", "ahoodfence2"},
    {TEXTURE_HOUSE_PRICE, 18265, "w_town3cs_t", "woodroof01_128"},
    {TEXTURE_HOUSE_PRICE, 5134, "wasteland_las2", "ws_bigstones"},
    {TEXTURE_HOUSE_PRICE, 8412, "wddngchpl", "vgsn_chplroof"},
    {TEXTURE_HOUSE_PRICE, 14415, "carter_block_2", "mp_gs_woodpanel"}, //
    {TEXTURE_HOUSE_PRICE, 14415, "carter_block_2", "mp_gs_woodpanel1"} //
};

static const FornitureTexture_Roof[][e_FornitureTexture] = {
    {TEXTURE_HOUSE_PRICE, 14674, "civic02cj", "ab_hosWallUpr"}, // 1 class
    {TEXTURE_HOUSE_PRICE, 9220, "sfn_apart02sfn", "concreteslab"},// end 1 class
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS2_Artex3"}, // 2 class
    {TEXTURE_HOUSE_PRICE, 8396, "sphinx01", "luxorceiling02_128"}, //3/ end 2 class
    {TEXTURE_HOUSE_PRICE, 3967, "cj_airprt", "ceiling_256"}, //4/ 3 class
    {TEXTURE_HOUSE_PRICE, 14708, "labig1int2", "ab_mottleGrey"},//5/
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "sl_laglasswall1"},//6/
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "ah_ceilpan1"},//7/
    {TEXTURE_HOUSE_PRICE, 10398, "countryclub_sfs", "hc_wall2"},//8/
    {TEXTURE_HOUSE_PRICE, 14708, "labig1int2", "ab_mottleGrey"},//9/ end 3 class
    {TEXTURE_HOUSE_PRICE, 19595, "lsappartments1", "carpet4-256x256"},//10/ 4 class
    {TEXTURE_HOUSE_PRICE, 18047, "gen_mun_counter", "mp_gun_metal"},//11/garage1
    {TEXTURE_HOUSE_PRICE, 19800, "lsacarpark1", "dt_officewall1"},//12/garage2
    {TEXTURE_HOUSE_PRICE, 1355, "break_s_bins", "marble1"},//13/garage3
    //new by Vlad
    {TEXTURE_HOUSE_PRICE, 14526, "sweetsmain", "ah_whitpanelceil"},
    {TEXTURE_HOUSE_PRICE, 14526, "sweetsmain", "ab_kitchunit2"},
    {TEXTURE_HOUSE_PRICE, 14560, "triad_bar", "triad_decor1"},
    {TEXTURE_HOUSE_PRICE, 19595, "lsappartments1", "carpet4-256x256"},
    {TEXTURE_HOUSE_PRICE, 18641, "flashlight1", "torch-glass-64x64"},
    {TEXTURE_HOUSE_PRICE, 16639, "a51_labs", "ws_trainstationwin1"},
    {TEXTURE_HOUSE_PRICE, 4828, "airport3_las", "gnhotelwall02_128"},
    {TEXTURE_HOUSE_PRICE, 10023, "bigwhitesfe", "archgrnd3_SFE"},
    {TEXTURE_HOUSE_PRICE, 9525, "boigas_sfw", "GEwhite1_64"},
    {TEXTURE_HOUSE_PRICE, 14888, "gf6", "mp_vicgrill"},
    {TEXTURE_HOUSE_PRICE, 8710, "nuhotel01", "nuhotel01_128"},
    {TEXTURE_HOUSE_PRICE, 14593, "papaerchaseoffice", "wall_stone6_256"},
    {TEXTURE_HOUSE_PRICE, 14760, "sfhosemed2", "AH_walltile2"},
    {TEXTURE_HOUSE_PRICE, 14748, "sfhsm1", "carpet3kb"},
    {TEXTURE_HOUSE_PRICE, 14750, "sfhsm2", "wallpnice06"},
    {TEXTURE_HOUSE_PRICE, 14758, "sfmansion1", "AH_flroortile6"},
    {TEXTURE_HOUSE_PRICE, 9220, "sfn_apart02sfn", "concreteslab"},
    {TEXTURE_HOUSE_PRICE, 2423, "cj_ff_counters", "shop_floor1"},
    {TEXTURE_HOUSE_PRICE, 4550, "skyscr1_lan2", "sl_skyscrpr02wall1"},
    {TEXTURE_HOUSE_PRICE, 14756, "smallsfhs", "AH_flroortiledirt1"},
    {TEXTURE_HOUSE_PRICE, 18008, "intclothesa", "mp_cloth_vicfloor"},
    {TEXTURE_HOUSE_PRICE, 18008, "intclothesa", "mp_cloth_vicfloor"},
    {TEXTURE_HOUSE_PRICE, 14708, "labig1int2", "ab_mottleGrey"},
    {TEXTURE_HOUSE_PRICE, 14701, "lahss2int2", "HS2_Artex3"},
    {TEXTURE_HOUSE_PRICE, 15048, "labigsave", "AH_flroortile1"},
    {TEXTURE_HOUSE_PRICE, 15048, "labigsave", "AH_fancyceil"},
    {TEXTURE_HOUSE_PRICE, 4558, "lanlacmab_lan2", "sl_plazatile02"},
    {TEXTURE_HOUSE_PRICE, 6064, "law_beach1", "musk1"},
    {TEXTURE_HOUSE_PRICE, 14623, "mafcasmain", "ab_tileStar"},
    {TEXTURE_HOUSE_PRICE, 10973, "mall_sfse", "ws_trainstationwin2"},
    {TEXTURE_HOUSE_PRICE, 14708, "labig1int2", "HS2_floor4"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "mp_gs_border1"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "mp_gs_pooltiles"},
    {TEXTURE_HOUSE_PRICE, 14420, "dr_gsbits", "mp_shop_window"},
    {TEXTURE_HOUSE_PRICE, 8498, "excalibur", "excaliburwall03_128"},
    {TEXTURE_HOUSE_PRICE, 2823, "gb_kitchtake", "GB_pizzabox01"},
    {TEXTURE_HOUSE_PRICE, 18022, "genintintfasta", "ceilingtile1_128"},
    {TEXTURE_HOUSE_PRICE, 18029, "genintintsmallrest", "GB_restaursmll03"},
    {TEXTURE_HOUSE_PRICE, 18021, "genintintfastd", "barbers_wall1"},
    {TEXTURE_HOUSE_PRICE, 14506, "imy_motel", "ab_tile1"},
    {TEXTURE_HOUSE_PRICE, 10398, "countryclub_sfs", "hc_wall2"},
    {TEXTURE_HOUSE_PRICE, 14389, "madpoolbit", "AH_flroortile4"},
    {TEXTURE_HOUSE_PRICE, 14425, "madbedrooms", "ah_wallstyle2"},
    {TEXTURE_HOUSE_PRICE, 16338, "dam_genroom", "dam_terazzoedge"},
    {TEXTURE_HOUSE_PRICE, 14847, "mp_policesf", "mp_cop_vinyl"},
    {TEXTURE_HOUSE_PRICE, 14847, "mp_policesf", "mp_cop_tile"},
    {TEXTURE_HOUSE_PRICE, 14537, "pdomebar", "club_floor2_sfwTEST"},
    {TEXTURE_HOUSE_PRICE, 16023, "des_trainstuff", "ws_stoneblock"},
    {TEXTURE_HOUSE_PRICE, 14420, "dr_gsbits", "mp_gs_border"},
    {TEXTURE_HOUSE_PRICE, 14387, "dr_gsnew", "AH_flroortile12"},
    {TEXTURE_HOUSE_PRICE, 15041, "bigsfsave", "ah_ceilpan1"},
    {TEXTURE_HOUSE_PRICE, 14582, "casmafbar", "ab_CasRomTile1"},
    {TEXTURE_HOUSE_PRICE, 14674, "civic02cj", "ab_hosWallUpr"},
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "sl_laglasswall2"},
    {TEXTURE_HOUSE_PRICE, 3979, "civic01_lan", "sl_laglasswall1"},
    {TEXTURE_HOUSE_PRICE, 14674, "civic02cj", "sl_hotelwallplain1"},
    {TEXTURE_HOUSE_PRICE, 3967, "cj_airprt", "ceiling_256"},
    {TEXTURE_HOUSE_PRICE, 18028, "cj_bar2", "GB_nastybar07"},
    {TEXTURE_HOUSE_PRICE, 15033, "vegassavesmal", "ah_corn2"},
    {TEXTURE_HOUSE_PRICE, 2127, "cj_kitchen", "marble2"},
    // my custom
    {TEXTURE_HOUSE_PRICE, 3922, "bistro", "rest_wall4"}

};

Garage_Repair(idx)
{
    new txd_id;
    switch(h_info[idx][h_squar])
    {
        case 2:
        {
            /*
            15|18|11
            h_info[idx][h_garage_id][G_FOOR] = 15;
            h_info[idx][h_garage_id][G_WALL] = 18;
            h_info[idx][h_garage_id][G_ROOF] = 11;
            */
            // Пол
            txd_id = h_info[idx][h_garage_id][G_FOOR];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][1])) h_info[idx][h_garage_map][1] = CreateDynamicObject(19377, 1329.209594, 1568.288208, 1009.820312, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][1], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][2])) h_info[idx][h_garage_map][2] = CreateDynamicObject(19377, 1339.709594, 1568.288208, 1009.820312, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][2], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][3])) h_info[idx][h_garage_map][3] = CreateDynamicObject(19377, 1339.709594, 1558.654174, 1009.820312, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][3], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][4])) h_info[idx][h_garage_map][4] = CreateDynamicObject(19377, 1329.209594, 1558.654174, 1009.820312, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][4], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            // Стены
            txd_id = h_info[idx][h_garage_id][G_WALL];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][5])) h_info[idx][h_garage_map][5] = CreateDynamicObject(19353, 1328.923583, 1568.426513, 1011.616455, 0.000029, 170.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][5], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][6])) h_info[idx][h_garage_map][6] = CreateDynamicObject(19353, 1328.923583, 1568.426513, 1015.031738, 0.000037, 370.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][6], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][7])) h_info[idx][h_garage_map][7] = CreateDynamicObject(19353, 1332.133544, 1569.027099, 1011.616455, -0.000029, 170.000000, -89.999877, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][7], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][8])) h_info[idx][h_garage_map][8] = CreateDynamicObject(19353, 1332.133544, 1569.027099, 1015.031738, -0.000022, 370.000000, -89.999900, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][8], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][9])) h_info[idx][h_garage_map][9] = CreateDynamicObject(19353, 1335.343505, 1568.426513, 1011.616455, 0.000029, 170.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][9], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][10])) h_info[idx][h_garage_map][10] = CreateDynamicObject(19353, 1335.343505, 1568.426513, 1015.031738, 0.000037, 370.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][10], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][11])) h_info[idx][h_garage_map][11] = CreateDynamicObject(19353, 1338.553466, 1569.027099, 1011.616455, -0.000029, 170.000000, -89.999877, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][11], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][12])) h_info[idx][h_garage_map][12] = CreateDynamicObject(19353, 1338.553466, 1569.027099, 1015.031738, -0.000022, 370.000000, -89.999900, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][12], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][13])) h_info[idx][h_garage_map][13] = CreateDynamicObject(19353, 1341.763427, 1568.426513, 1011.616455, 0.000029, 170.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][13], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][14])) h_info[idx][h_garage_map][14] = CreateDynamicObject(19353, 1341.763427, 1568.426513, 1015.031738, 0.000037, 370.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][14], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][15])) h_info[idx][h_garage_map][15] = CreateDynamicObject(19353, 1341.763427, 1555.291625, 1011.616455, -0.000014, 170.000000, -89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][16])) h_info[idx][h_garage_map][16] = CreateDynamicObject(19353, 1341.763427, 1555.291625, 1015.031738, -0.000007, 370.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][17])) h_info[idx][h_garage_map][17] = CreateDynamicObject(19353, 1338.553466, 1554.691040, 1011.616455, 0.000014, 170.000000, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][18])) h_info[idx][h_garage_map][18] = CreateDynamicObject(19353, 1338.553466, 1554.691040, 1015.031738, 0.000022, 370.000000, 89.999900, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][19])) h_info[idx][h_garage_map][19] = CreateDynamicObject(19353, 1335.343505, 1555.291625, 1011.616455, -0.000014, 170.000000, -89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][20])) h_info[idx][h_garage_map][20] = CreateDynamicObject(19353, 1335.343505, 1555.291625, 1015.031738, -0.000007, 370.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][21])) h_info[idx][h_garage_map][21] = CreateDynamicObject(19353, 1332.133544, 1554.691040, 1011.616455, 0.000014, 170.000000, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][22])) h_info[idx][h_garage_map][22] = CreateDynamicObject(19353, 1332.133544, 1554.691040, 1015.031738, 0.000022, 370.000000, 89.999900, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][23])) h_info[idx][h_garage_map][23] = CreateDynamicObject(19353, 1328.923583, 1555.291625, 1011.616455, -0.000014, 170.000000, -89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][24])) h_info[idx][h_garage_map][24] = CreateDynamicObject(19353, 1328.923583, 1555.291625, 1015.031738, -0.000007, 370.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][25])) h_info[idx][h_garage_map][25] = CreateDynamicObject(19446, 1327.241943, 1557.038330, 1015.069458, 0.000000, 0.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][26])) h_info[idx][h_garage_map][26] = CreateDynamicObject(19446, 1327.241943, 1566.672363, 1015.069458, 0.000000, 0.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][27])) h_info[idx][h_garage_map][27] = CreateDynamicObject(19446, 1327.241943, 1553.828369, 1011.569458, 0.000000, 180.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][27], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][28])) h_info[idx][h_garage_map][28] = CreateDynamicObject(19446, 1327.241943, 1569.882324, 1011.569458, 0.000000, 180.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][28], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][29])) h_info[idx][h_garage_map][29] = CreateDynamicObject(19446, 1343.448974, 1557.019653, 1015.077270, 0.000014, 0.000029, -179.999832, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][29], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][30])) h_info[idx][h_garage_map][30] = CreateDynamicObject(19446, 1343.448974, 1566.653686, 1015.077270, 0.000014, 0.000029, -179.999832, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][30], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][31])) h_info[idx][h_garage_map][31] = CreateDynamicObject(19446, 1343.448974, 1569.863647, 1011.577270, 0.000014, -179.999969, -179.999832, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][31], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][32])) h_info[idx][h_garage_map][32] = CreateDynamicObject(19446, 1343.448852, 1553.809814, 1011.577270, 0.000014, -179.999969, 0.000105, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][32], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            // Потолок
            txd_id = h_info[idx][h_garage_id][G_ROOF];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][33])) h_info[idx][h_garage_map][33] = CreateDynamicObject(19353, 1328.923583, 1566.973876, 1016.254882, 0.000037, 70.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][33], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][34])) h_info[idx][h_garage_map][34] = CreateDynamicObject(19353, 1328.923583, 1563.609008, 1015.661132, 0.000037, 270.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][34], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][35])) h_info[idx][h_garage_map][35] = CreateDynamicObject(19353, 1335.343505, 1566.973876, 1016.254882, 0.000037, 70.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][35], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][36])) h_info[idx][h_garage_map][36] = CreateDynamicObject(19353, 1335.343505, 1563.609008, 1015.661132, 0.000037, 270.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][36], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][37])) h_info[idx][h_garage_map][37] = CreateDynamicObject(19353, 1341.763427, 1566.973876, 1016.254882, 0.000037, 70.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][37], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][38])) h_info[idx][h_garage_map][38] = CreateDynamicObject(19353, 1341.763427, 1563.609008, 1015.661132, 0.000037, 270.000000, 89.999885, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][38], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][39])) h_info[idx][h_garage_map][39] = CreateDynamicObject(19353, 1341.763427, 1556.744262, 1016.254882, -0.000007, 70.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][39], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][40])) h_info[idx][h_garage_map][40] = CreateDynamicObject(19353, 1341.763427, 1560.109130, 1015.661132, -0.000007, 270.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][40], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][41])) h_info[idx][h_garage_map][41] = CreateDynamicObject(19353, 1335.343505, 1556.744262, 1016.254882, -0.000007, 70.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][41], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][42])) h_info[idx][h_garage_map][42] = CreateDynamicObject(19353, 1335.343505, 1560.109130, 1015.661132, -0.000007, 270.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][42], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][43])) h_info[idx][h_garage_map][43] = CreateDynamicObject(19353, 1328.923583, 1556.744262, 1016.254882, -0.000007, 70.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][43], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][44])) h_info[idx][h_garage_map][44] = CreateDynamicObject(19353, 1328.923583, 1560.109130, 1015.661132, -0.000007, 270.000000, -89.999946, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][44], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
        }
        case 3:
        {
            /*
            16|19|12
            h_info[idx][h_garage_id][G_FOOR] = 16;
            h_info[idx][h_garage_id][G_WALL] = 19;
            h_info[idx][h_garage_id][G_ROOF] = 12;
            */
            //пол
            txd_id = h_info[idx][h_garage_id][G_FOOR];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][0])) h_info[idx][h_garage_map][0] = CreateDynamicObject(8661, 1384.421997, -26.875000, 1999.918945, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xF0FFFFFF);
            //стены
            txd_id = h_info[idx][h_garage_id][G_WALL];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][1])) h_info[idx][h_garage_map][1] = CreateDynamicObject(19353, 1400.347290, -18.149694, 2001.669189, -89.999992, 360.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][1], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][2])) h_info[idx][h_garage_map][2] = CreateDynamicObject(19353, 1396.847290, -18.149694, 2001.669189, -89.999992, 179.999984, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][2], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][3])) h_info[idx][h_garage_map][3] = CreateDynamicObject(19353, 1391.446044, -18.149694, 2001.669189, -89.999992, 360.000000, 89.999961, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][3], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][4])) h_info[idx][h_garage_map][4] = CreateDynamicObject(19353, 1387.946044, -18.149694, 2001.669189, -89.999992, 180.000000, 89.999961, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][4], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][5])) h_info[idx][h_garage_map][5] = CreateDynamicObject(19353, 1402.328247, -20.139719, 2001.669189, -89.999992, 224.999984, 44.999984, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][5], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][6])) h_info[idx][h_garage_map][6] = CreateDynamicObject(19353, 1402.328247, -23.639719, 2001.669189, -89.999992, 405.000000, 44.999984, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][6], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][7])) h_info[idx][h_garage_map][7] = CreateDynamicObject(19353, 1402.328247, -27.139719, 2001.669189, -89.999992, 224.999984, 44.999984, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][7], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][8])) h_info[idx][h_garage_map][8] = CreateDynamicObject(19353, 1382.544067, -18.149694, 2001.669189, -89.999992, 360.000030, 89.999961, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][8], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][9])) h_info[idx][h_garage_map][9] = CreateDynamicObject(19353, 1379.044067, -18.149694, 2001.669189, -89.999992, 180.000015, 89.999961, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][9], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][10])) h_info[idx][h_garage_map][10] = CreateDynamicObject(19353, 1377.090454, -23.639720, 2001.669189, -89.999992, 872.742614, 152.742630, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][10], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][11])) h_info[idx][h_garage_map][11] = CreateDynamicObject(19353, 1377.090454, -17.769725, 2001.669189, -89.999992, 872.742614, 152.742630, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][11], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][12])) h_info[idx][h_garage_map][12] = CreateDynamicObject(19353, 1379.053100, -32.398883, 2001.669189, -89.999992, 514.437255, 64.437301, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][12], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][13])) h_info[idx][h_garage_map][13] = CreateDynamicObject(19353, 1402.324218, -30.429714, 2001.669189, -89.999992, 765.000000, 44.999996, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][13], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][14])) h_info[idx][h_garage_map][14] = CreateDynamicObject(19353, 1382.553100, -32.398883, 2001.669189, -89.999992, 334.437255, 64.437301, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][14], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][15])) h_info[idx][h_garage_map][15] = CreateDynamicObject(19353, 1387.954345, -32.398883, 2001.669189, -89.999992, 193.445846, 103.445861, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][16])) h_info[idx][h_garage_map][16] = CreateDynamicObject(19353, 1391.454345, -32.398883, 2001.669189, -89.999992, 13.445844, 103.445861, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][17])) h_info[idx][h_garage_map][17] = CreateDynamicObject(19353, 1396.856323, -32.398883, 2001.669189, -89.999992, 193.407135, 103.407119, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][18])) h_info[idx][h_garage_map][18] = CreateDynamicObject(19353, 1400.356323, -32.398883, 2001.669189, -89.999992, 13.407135, 103.407119, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][19])) h_info[idx][h_garage_map][19] = CreateDynamicObject(19353, 1376.469848, -23.639720, 2001.669189, -89.999992, 831.106872, 111.106842, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][20])) h_info[idx][h_garage_map][20] = CreateDynamicObject(19353, 1376.469848, -27.139720, 2001.669189, -89.999992, 651.106872, 111.106842, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][21])) h_info[idx][h_garage_map][21] = CreateDynamicObject(19353, 1370.276245, -17.769725, 2001.669189, -89.999992, 820.899902, 200.899848, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][22])) h_info[idx][h_garage_map][22] = CreateDynamicObject(19353, 1370.279418, -23.639720, 2001.669189, -89.999992, 815.498840, 95.498771, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][23])) h_info[idx][h_garage_map][23] = CreateDynamicObject(19353, 1370.279418, -27.139720, 2001.669189, -89.999992, 635.498840, 95.498771, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][24])) h_info[idx][h_garage_map][24] = CreateDynamicObject(19353, 1377.094482, -30.429716, 2001.669189, -89.999992, 154.471221, 154.471237, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][25])) h_info[idx][h_garage_map][25] = CreateDynamicObject(19353, 1377.090454, -27.139720, 2001.669189, -89.999992, 692.742614, 152.742630, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][26])) h_info[idx][h_garage_map][26] = CreateDynamicObject(19353, 1374.549804, -29.121728, 2001.669189, -89.999992, 651.106872, 201.106842, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][27])) h_info[idx][h_garage_map][27] = CreateDynamicObject(19353, 1371.049804, -29.121728, 2001.669189, -89.999992, 651.106872, 201.106842, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][27], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][28])) h_info[idx][h_garage_map][28] = CreateDynamicObject(19353, 1374.549804, -18.147714, 2001.669189, -89.999992, 608.094787, 158.094757, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][28], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][29])) h_info[idx][h_garage_map][29] = CreateDynamicObject(19353, 1371.049804, -18.147714, 2001.669189, -89.999992, 608.094787, 158.094757, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][29], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][30])) h_info[idx][h_garage_map][30] = CreateDynamicObject(19353, 1376.473876, -17.769725, 2001.669189, -89.999992, 872.742614, 152.742630, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][30], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            //потолок
            txd_id = h_info[idx][h_garage_id][G_ROOF];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][31])) h_info[idx][h_garage_map][31] = CreateDynamicObject(19445, 1398.405639, -21.999694, 2004.796752, -0.000073, 79.999984, -89.999832, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][31], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFE0E0E0);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][32])) h_info[idx][h_garage_map][32] = CreateDynamicObject(19445, 1388.771606, -21.999694, 2004.796752, -0.000073, 79.999984, -89.999832, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][32], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFE0E0E0);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][33])) h_info[idx][h_garage_map][33] = CreateDynamicObject(19445, 1379.137573, -21.999679, 2004.796813, -0.000061, 79.999984, -89.999862, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][33], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFE0E0E0);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][34])) h_info[idx][h_garage_map][34] = CreateDynamicObject(19445, 1379.137573, -28.549694, 2004.796752, -0.000057, 79.999984, 90.000061, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][34], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFE0E0E0);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][35])) h_info[idx][h_garage_map][35] = CreateDynamicObject(19445, 1388.771606, -28.549694, 2004.796752, -0.000057, 79.999984, 90.000061, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][35], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFE0E0E0);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][36])) h_info[idx][h_garage_map][36] = CreateDynamicObject(19445, 1398.405639, -28.549711, 2004.796813, -0.000046, 79.999984, 90.000030, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][36], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFE0E0E0);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][37])) h_info[idx][h_garage_map][37] = CreateDynamicObject(19445, 1374.933959, -23.010040, 2003.451965, 0.000000, 270.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][37], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][38])) h_info[idx][h_garage_map][38] = CreateDynamicObject(19445, 1374.933959, -32.644039, 2003.451965, 0.000000, 270.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][38], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][39])) h_info[idx][h_garage_map][39] = CreateDynamicObject(19445, 1371.815063, -23.010040, 2003.451965, 0.000014, 449.999969, -0.000014, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][39], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][40])) h_info[idx][h_garage_map][40] = CreateDynamicObject(19445, 1371.815063, -32.644039, 2003.451965, 0.000014, 449.999969, -0.000014, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][40], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
        }
        case 4:
        {
            /*
            7|20|12
            h_info[idx][h_garage_id][G_FOOR] = 7;
            h_info[idx][h_garage_id][G_WALL] = 20;
            h_info[idx][h_garage_id][G_ROOF] = 12;
            */
            //пол
            txd_id = h_info[idx][h_garage_id][G_FOOR];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][0])) h_info[idx][h_garage_map][0] = CreateDynamicObject(8661, 1384.431274, -6.885999, 999.916931, 0.000000, 0.000000, 360.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xF0FFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][1])) h_info[idx][h_garage_map][1] = CreateDynamicObject(8661, 1384.442016, -26.875000, 999.918945, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][1], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xF0FFFFFF);

            //стены
            txd_id = h_info[idx][h_garage_id][G_WALL];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][2])) h_info[idx][h_garage_map][2] = CreateDynamicObject(19353, 1378.594726, -15.980695, 1001.802490, 89.999992, 1035.414916, -115.414825, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][2], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][3])) h_info[idx][h_garage_map][3] = CreateDynamicObject(19353, 1370.657470, -30.196474, 1001.802490, 89.999992, 807.503906, -67.503944, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][3], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][4])) h_info[idx][h_garage_map][4] = CreateDynamicObject(19353, 1391.313354, -15.980695, 1001.802490, 89.999992, 1023.303649, -103.303688, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][4], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][5])) h_info[idx][h_garage_map][5] = CreateDynamicObject(19353, 1378.089477, -14.580554, 1001.802490, 89.999992, 495.414825, -115.414825, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][5], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][6])) h_info[idx][h_garage_map][6] = CreateDynamicObject(19353, 1375.368286, -12.236783, 1001.802490, 89.999992, 358.326202, -88.326164, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][6], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][7])) h_info[idx][h_garage_map][7] = CreateDynamicObject(19353, 1373.878540, -12.232466, 1001.802490, 89.999992, 538.326232, -88.326164, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][7], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][8])) h_info[idx][h_garage_map][8] = CreateDynamicObject(19353, 1371.163452, -14.591017, 1001.802490, 89.999992, 419.089935, -79.089927, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][8], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][9])) h_info[idx][h_garage_map][9] = CreateDynamicObject(19353, 1370.649658, -15.990932, 1001.802490, 89.999992, 599.089904, -79.089927, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][9], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][10])) h_info[idx][h_garage_map][10] = CreateDynamicObject(19353, 1395.437500, -16.446229, 1001.802490, 89.999992, 270.000000, -89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][10], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][11])) h_info[idx][h_garage_map][11] = CreateDynamicObject(19353, 1390.808105, -14.580554, 1001.802490, 89.999992, 123.303726, -103.303688, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][11], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][12])) h_info[idx][h_garage_map][12] = CreateDynamicObject(19353, 1388.086914, -12.236783, 1001.802490, 89.999992, 359.162963, -89.162879, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][12], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][13])) h_info[idx][h_garage_map][13] = CreateDynamicObject(19353, 1386.597167, -12.232467, 1001.802490, 89.999992, 179.162963, -89.162879, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][13], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][14])) h_info[idx][h_garage_map][14] = CreateDynamicObject(19353, 1383.882080, -14.591017, 1001.802490, 89.999992, 1144.495849, -84.495941, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][14], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][15])) h_info[idx][h_garage_map][15] = CreateDynamicObject(19353, 1383.368286, -15.990932, 1001.802490, 89.999992, 604.495910, -84.495941, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][16])) h_info[idx][h_garage_map][16] = CreateDynamicObject(19353, 1371.162719, -31.596620, 1001.802490, 89.999992, 267.503936, -67.503944, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][17])) h_info[idx][h_garage_map][17] = CreateDynamicObject(19353, 1373.883911, -33.940399, 1001.802490, 89.999992, 583.338439, -133.338409, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][18])) h_info[idx][h_garage_map][18] = CreateDynamicObject(19353, 1375.373657, -33.944713, 1001.802490, -89.999992, 0.000014, 90.000007, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][19])) h_info[idx][h_garage_map][19] = CreateDynamicObject(19353, 1378.088745, -31.586154, 1001.802490, 89.999992, 284.612457, -124.612434, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][20])) h_info[idx][h_garage_map][20] = CreateDynamicObject(19353, 1378.602539, -30.186243, 1001.802490, 89.999992, 464.612457, -124.612434, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][21])) h_info[idx][h_garage_map][21] = CreateDynamicObject(19353, 1383.374267, -30.196474, 1001.802490, 89.999992, 818.334289, -78.334320, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][22])) h_info[idx][h_garage_map][22] = CreateDynamicObject(19353, 1383.879516, -31.596620, 1001.802490, 89.999992, 278.334320, -78.334320, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][23])) h_info[idx][h_garage_map][23] = CreateDynamicObject(19353, 1386.600708, -33.940399, 1001.802490, 89.999992, 204.398651, -114.398559, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][24])) h_info[idx][h_garage_map][24] = CreateDynamicObject(19353, 1388.090454, -33.944713, 1001.802490, 89.999992, 0.000000, -89.999977, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][25])) h_info[idx][h_garage_map][25] = CreateDynamicObject(19353, 1390.805541, -31.586154, 1001.802490, 89.999992, 268.757293, -108.757270, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][26])) h_info[idx][h_garage_map][26] = CreateDynamicObject(19353, 1391.319335, -30.186243, 1001.802490, 89.999992, 88.757301, -108.757270, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][27])) h_info[idx][h_garage_map][27] = CreateDynamicObject(19353, 1395.437500, -29.736240, 1001.802490, 89.999992, 90.000000, -89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][27], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][28])) h_info[idx][h_garage_map][28] = CreateDynamicObject(19353, 1397.935424, -13.942485, 1001.802490, 89.999992, 183.398895, -93.398750, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][28], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][29])) h_info[idx][h_garage_map][29] = CreateDynamicObject(19353, 1401.435424, -13.942485, 1001.802490, 89.999992, 363.398895, -93.398750, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][29], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][30])) h_info[idx][h_garage_map][30] = CreateDynamicObject(19353, 1401.429321, -32.257957, 1001.802490, 89.999992, 351.096923, -81.096900, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][30], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][31])) h_info[idx][h_garage_map][31] = CreateDynamicObject(19353, 1397.929321, -32.257957, 1001.802490, 89.999992, 531.096984, -81.096900, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][31], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][32])) h_info[idx][h_garage_map][32] = CreateDynamicObject(19353, 1403.950439, -26.274017, 1001.802490, 89.999992, 447.757476, -87.757431, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][32], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][33])) h_info[idx][h_garage_map][33] = CreateDynamicObject(19353, 1403.950439, -29.774017, 1001.802490, 89.999992, 627.757385, -87.757431, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][33], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][34])) h_info[idx][h_garage_map][34] = CreateDynamicObject(19353, 1403.950439, -16.454008, 1001.802490, 89.999992, 448.878326, -88.878265, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][34], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][35])) h_info[idx][h_garage_map][35] = CreateDynamicObject(19353, 1403.950439, -19.954008, 1001.802490, 89.999992, 628.878234, -88.878265, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][35], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][36])) h_info[idx][h_garage_map][36] = CreateDynamicObject(19426, 1403.950439, -23.124002, 1001.802490, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][36], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFFFFFFF);

            //потолок
            txd_id = h_info[idx][h_garage_id][G_ROOF];
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][37])) h_info[idx][h_garage_map][37] = CreateDynamicObject(19445, 1374.642700, -18.817255, 1005.442749, 0.000020, 0.000000, 89.999931, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][37], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][38])) h_info[idx][h_garage_map][38] = CreateDynamicObject(19445, 1374.642700, -27.357267, 1005.442749, 0.000022, 0.000000, 89.999931, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][38], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][39])) h_info[idx][h_garage_map][39] = CreateDynamicObject(19445, 1387.361328, -18.817255, 1005.442749, 0.000029, 0.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][39], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][40])) h_info[idx][h_garage_map][40] = CreateDynamicObject(19445, 1387.393676, -25.537256, 1005.422363, 0.000020, 90.000000, 89.999931, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][40], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][41])) h_info[idx][h_garage_map][41] = CreateDynamicObject(19445, 1387.393676, -20.627248, 1005.422363, 0.000020, 270.000000, 89.999931, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][41], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][42])) h_info[idx][h_garage_map][42] = CreateDynamicObject(19445, 1387.326293, -27.359920, 1005.442749, 0.000000, 0.000000, -89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][42], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][43])) h_info[idx][h_garage_map][43] = CreateDynamicObject(19445, 1387.393676, -23.157249, 1005.428344, 0.000020, 270.000000, 89.999931, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][43], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][44])) h_info[idx][h_garage_map][44] = CreateDynamicObject(19445, 1374.662841, -25.537256, 1005.422363, 0.000029, 90.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][44], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][45])) h_info[idx][h_garage_map][45] = CreateDynamicObject(19445, 1374.662841, -20.627248, 1005.422363, 0.000029, 270.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][45], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            if(!IsValidDynamicObject(h_info[idx][h_garage_map][46])) h_info[idx][h_garage_map][46] = CreateDynamicObject(19445, 1374.662841, -23.157249, 1005.428344, 0.000029, 270.000000, 89.999908, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_garage_map][46], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
        }
    }
}

House_Repair(idx)
{
    new txd_id;
    switch(h_info[idx][h_squar])
    {
        case 1:
        {
            /* class = 1
            0|-1|0|1|2|-1|-1|-1|-1|0|1|2|3|-1|-1|-1|-1|-1|0|0|-1|1|-1|-1|-1|-1|-1

            h_info[idx][h_mapping_id][H_FOOR_HALLWAY] = 0;
            h_info[idx][h_mapping_id][H_FOOR_HALLWAY2] = -1;
            h_info[idx][h_mapping_id][H_FOOR_LIVING_ROOM] = 0;
            h_info[idx][h_mapping_id][H_FOOR_KITCHEN] = 1;
            h_info[idx][h_mapping_id][H_FOOR_BATHROOM] = 2;

            h_info[idx][h_mapping_id][H_WALL_HALLWAY] = 0;
            h_info[idx][h_mapping_id][H_WALL_LIVING_ROOM] = 1;
            h_info[idx][h_mapping_id][H_WALL_KITCHEN] = 2;
            h_info[idx][h_mapping_id][H_WALL_BATHROOM] = 3;

            h_info[idx][h_mapping_id][H_ROOF_HALLWAY] = 0;
            h_info[idx][h_mapping_id][H_ROOF_LIVING_ROOM] = 0;
            h_info[idx][h_mapping_id][H_ROOF_KITCHEN] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BATHROOM] = 1;
            */
            //___________________________________________________________________________________________
            //Пол прихожая[0] и гостинная[1]
            txd_id = h_info[idx][h_mapping_id][H_FOOR_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][0])) h_info[idx][h_mapping][0] = CreateDynamicObject(19377, 2215.271972, 736.643188, 1022.159729, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            txd_id = h_info[idx][h_mapping_id][H_FOOR_LIVING_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][1])) h_info[idx][h_mapping][1] = CreateDynamicObject(19377, 2225.772460, 736.643188, 1022.159729, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][1], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            //___________________________________________________________________________________________
            //Пол кухня
            txd_id = h_info[idx][h_mapping_id][H_FOOR_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][2])) h_info[idx][h_mapping][2] = CreateDynamicObject(19368, 2223.974853, 733.456237, 1022.162414, 0.000000, 90.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][2], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][3])) h_info[idx][h_mapping][3] = CreateDynamicObject(19368, 2221.156494, 733.458251, 1022.166442, 0.000000, 90.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][3], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFE6E6E6);
            //___________________________________________________________________________________________
            //Пол ванная
            txd_id = h_info[idx][h_mapping_id][H_FOOR_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][4])) h_info[idx][h_mapping][4] = CreateDynamicObject(19375, 2215.271972, 731.863281, 1022.149658, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][4], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            //______________________________________
            //Стены прихожая
            txd_id = h_info[idx][h_mapping_id][H_WALL_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][5])) h_info[idx][h_mapping][5] = CreateDynamicObject(19458, 2231.001953, 736.636535, 1023.980102, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][5], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][6])) h_info[idx][h_mapping][6] = CreateDynamicObject(19458, 2230.431396, 731.806213, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][6], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][7])) h_info[idx][h_mapping][7] = CreateDynamicObject(19458, 2226.171142, 741.486145, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][7], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][8])) h_info[idx][h_mapping][8] = CreateDynamicObject(19458, 2225.695312, 730.376464, 1023.980102, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][8], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][9])) h_info[idx][h_mapping][9] = CreateDynamicObject(19458, 2225.691162, 736.636535, 1026.699951, 0.000000, 180.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][9], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            //___________________________________________________________________________________________
            //Стены гостинная (комната)
            txd_id = h_info[idx][h_mapping_id][H_WALL_LIVING_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][10])) h_info[idx][h_mapping][10] = CreateDynamicObject(19456, 2216.541259, 741.486145, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][10], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][11])) h_info[idx][h_mapping][11] = CreateDynamicObject(19456, 2211.681152, 736.636535, 1023.980102, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][11], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][12])) h_info[idx][h_mapping][12] = CreateDynamicObject(19456, 2220.790039, 741.478088, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][12], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][13])) h_info[idx][h_mapping][13] = CreateDynamicObject(19456, 2225.607177, 736.640563, 1026.741943, 0.000000, 180.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][13], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][14])) h_info[idx][h_mapping][14] = CreateDynamicObject(19456, 2210.251220, 731.768066, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][14], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][15])) h_info[idx][h_mapping][15] = CreateDynamicObject(19456, 2212.557617, 731.764038, 1026.586303, -180.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][16])) h_info[idx][h_mapping][16] = CreateDynamicObject(19456, 2222.201416, 742.416748, 1023.980102, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][17])) h_info[idx][h_mapping][17] = CreateDynamicObject(19354, 2218.384765, 731.800048, 1024.059570, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            //___________________________________________________________________________________________
            //Стены кухня
            txd_id = h_info[idx][h_mapping_id][H_WALL_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][18])) h_info[idx][h_mapping][18] = CreateDynamicObject(19459, 2225.591552, 730.370422, 1024.211303, 0.000000, 0.000007, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][19])) h_info[idx][h_mapping][19] = CreateDynamicObject(19367, 2223.932128, 731.808105, 1024.213012, -0.000014, 0.000000, -89.999954, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][20])) h_info[idx][h_mapping][20] = CreateDynamicObject(19367, 2221.162353, 731.816162, 1024.214965, -0.000014, 0.000000, -89.999954, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            //___________________________________________________________________________________________
            //Стены ванная
            txd_id = h_info[idx][h_mapping_id][H_WALL_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][21])) h_info[idx][h_mapping][21] = CreateDynamicObject(19460, 2215.441894, 727.758117, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][22])) h_info[idx][h_mapping][22] = CreateDynamicObject(19460, 2213.412841, 726.936828, 1023.980102, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][23])) h_info[idx][h_mapping][23] = CreateDynamicObject(19460, 2210.251220, 731.708007, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][24])) h_info[idx][h_mapping][24] = CreateDynamicObject(19460, 2221.600830, 731.728027, 1023.980102, 0.000000, 0.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][25])) h_info[idx][h_mapping][25] = CreateDynamicObject(19460, 2216.670654, 731.734069, 1026.580566, 0.000000, 180.000000, -90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][26])) h_info[idx][h_mapping][26] = CreateDynamicObject(19460, 2217.982421, 726.898193, 1023.980102, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);

            //________________________________________
            //Потолок прихожая и гостинная
            txd_id = h_info[idx][h_mapping_id][H_ROOF_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][27])) h_info[idx][h_mapping][27] = CreateDynamicObject(19376, 2216.952392, 736.643188, 1025.779663, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][27], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            txd_id = h_info[idx][h_mapping_id][H_ROOF_LIVING_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][28])) h_info[idx][h_mapping][28] = CreateDynamicObject(19376, 2227.451904, 736.643188, 1025.779663, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][28], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);

            //___________________________________________________________________________________________
            //Потолок ванная
            txd_id = h_info[idx][h_mapping_id][H_ROOF_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][29])) h_info[idx][h_mapping][29] = CreateDynamicObject(19381, 2215.271972, 731.863281, 1025.800292, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][29], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
        }
        case 2:
        {
            /*  class = 2
            3|-1|-1|4|5|-1|-1|-1|-1|4|-1|5|6|-1|-1|-1|-1|-1|2|-1|-1|3|-1|-1|-1|-1|-1

            h_info[idx][h_mapping_id][H_FOOR_HALLWAY] = 3;
            h_info[idx][h_mapping_id][H_FOOR_HALLWAY2] = -1;
            h_info[idx][h_mapping_id][H_FOOR_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_FOOR_KITCHEN] = 4;
            h_info[idx][h_mapping_id][H_FOOR_BATHROOM] = 5;
            h_info[idx][h_mapping_id][H_FOOR_CABINET] = -1;
            h_info[idx][h_mapping_id][H_FOOR_ROOM] = -1;
            h_info[idx][h_mapping_id][H_FOOR_BAR] = -1;
            h_info[idx][h_mapping_id][H_FOOR_GYM] = -1;

            h_info[idx][h_mapping_id][H_WALL_HALLWAY] = 4;
            h_info[idx][h_mapping_id][H_WALL_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_WALL_KITCHEN] = 5;
            h_info[idx][h_mapping_id][H_WALL_BATHROOM] = 6;
            h_info[idx][h_mapping_id][H_WALL_CABINET] = -1;
            h_info[idx][h_mapping_id][H_WALL_BED] = -1;
            h_info[idx][h_mapping_id][H_WALL_ROOM] = -1;
            h_info[idx][h_mapping_id][H_WALL_BAR] = -1;
            h_info[idx][h_mapping_id][H_WALL_GYM] = -1;

            h_info[idx][h_mapping_id][H_ROOF_HALLWAY] = 2;
            h_info[idx][h_mapping_id][H_ROOF_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_ROOF_KITCHEN] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BATHROOM] = 3;
            h_info[idx][h_mapping_id][H_ROOF_CABINET] = -1;
            h_info[idx][h_mapping_id][H_ROOF_ROOM] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BALCONY] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BAR] = -1;
            h_info[idx][h_mapping_id][H_ROOF_GYM] = -1;

            */
            //___________________________________________________________________________________________
            //Пол прихожая и гостинная
            txd_id = h_info[idx][h_mapping_id][H_FOOR_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][0])) h_info[idx][h_mapping][0] = CreateDynamicObject(19377, 980.632080, 1237.096557, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][1]))h_info[idx][h_mapping][1] = CreateDynamicObject(19377, 980.632080, 1246.726440, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][1], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][2]))h_info[idx][h_mapping][2] = CreateDynamicObject(19377, 970.131958, 1237.096557, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][2], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            //___________________________________________________________________________________________
            //Пол кухня
            txd_id = h_info[idx][h_mapping_id][H_FOOR_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][3])) h_info[idx][h_mapping][3] = CreateDynamicObject(19376, 968.571716, 1243.527832, 1023.458129, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][3], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            //___________________________________________________________________________________________
            //Пол ванная
            txd_id = h_info[idx][h_mapping_id][H_FOOR_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][4])) h_info[idx][h_mapping][4] = CreateDynamicObject(19375, 980.632080, 1233.716918, 1023.442016, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][4], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            //___________________________________________________________________________________________
            //Стены гостинная прихожая (комната)
            txd_id = h_info[idx][h_mapping_id][H_WALL_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][5])) h_info[idx][h_mapping][5] = CreateDynamicObject(19456, 985.910095, 1246.709594, 1025.272583, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][5], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][6])) h_info[idx][h_mapping][6] = CreateDynamicObject(19456, 987.460083, 1251.289184, 1025.272583, 0.000007, 0.000000, 89.999977, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][6], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][7])) h_info[idx][h_mapping][7] = CreateDynamicObject(19456, 985.912109, 1243.501342, 1025.274536, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][7], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][8])) h_info[idx][h_mapping][8] = CreateDynamicObject(19456, 987.450317, 1238.759399, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][8], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][9])) h_info[idx][h_mapping][9] = CreateDynamicObject(19427, 982.711791, 1238.040893, 1025.274536, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][9], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][10])) h_info[idx][h_mapping][10] = CreateDynamicObject(19456, 987.450317, 1237.308959, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][10], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][11])) h_info[idx][h_mapping][11] = CreateDynamicObject(19456, 985.912109, 1232.981567, 1025.274536, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][11], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][12])) h_info[idx][h_mapping][12] = CreateDynamicObject(19456, 983.040100, 1232.275390, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][12], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][13])) h_info[idx][h_mapping][13] = CreateDynamicObject(19456, 971.665588, 1232.275390, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][13], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][14])) h_info[idx][h_mapping][14] = CreateDynamicObject(19354, 977.171813, 1232.267578, 1027.902954, 0.000000, 180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][14], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][15])) h_info[idx][h_mapping][15] = CreateDynamicObject(19354, 975.558105, 1251.283935, 1025.274536, 0.000014, 0.000000, 89.999954, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][16])) h_info[idx][h_mapping][16] = CreateDynamicObject(19456, 975.329711, 1246.709594, 1025.272583, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][17])) h_info[idx][h_mapping][17] = CreateDynamicObject(19456, 975.323669, 1243.524536, 1025.272583, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][18])) h_info[idx][h_mapping][18] = CreateDynamicObject(19427, 974.601745, 1238.791748, 1025.274536, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][19])) h_info[idx][h_mapping][19] = CreateDynamicObject(19456, 964.803222, 1237.113647, 1025.272583, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][20])) h_info[idx][h_mapping][20] = CreateDynamicObject(19456, 969.041503, 1232.269531, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][21])) h_info[idx][h_mapping][21] = CreateDynamicObject(19456, 981.066162, 1251.288696, 1028.194580, 0.000000, 180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][22])) h_info[idx][h_mapping][22] = CreateDynamicObject(19354, 965.418090, 1238.784301, 1025.274536, 0.000014, 0.000000, 89.999954, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            //___________________________________________________________________________________________
            //Стены кухня
            txd_id = h_info[idx][h_mapping_id][H_WALL_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][23])) h_info[idx][h_mapping][23] = CreateDynamicObject(19459, 973.883605, 1243.524536, 1025.272583, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][24])) h_info[idx][h_mapping][24] = CreateDynamicObject(19459, 969.000366, 1241.970092, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][25])) h_info[idx][h_mapping][25] = CreateDynamicObject(19459, 966.943359, 1243.524536, 1025.272583, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            //___________________________________________________________________________________________
            //Стены ванная
            txd_id = h_info[idx][h_mapping_id][H_WALL_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][26])) h_info[idx][h_mapping][26] = CreateDynamicObject(19458, 983.040100, 1232.215332, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][27])) h_info[idx][h_mapping][27] = CreateDynamicObject(19458, 971.710266, 1232.215332, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][27], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][28])) h_info[idx][h_mapping][28] = CreateDynamicObject(19458, 977.930419, 1232.225097, 1027.892944, 180.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][28], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][29])) h_info[idx][h_mapping][29] = CreateDynamicObject(19458, 981.621948, 1227.381713, 1025.274536, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][29], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][30])) h_info[idx][h_mapping][30] = CreateDynamicObject(19458, 979.330078, 1228.835449, 1025.272583, 0.000000, 0.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][30], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][31])) h_info[idx][h_mapping][31] = CreateDynamicObject(19458, 975.302185, 1227.381713, 1025.274536, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][31], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            //____________________________________________________________________________________________
            //Потолок прихожая и гостинная
            txd_id = h_info[idx][h_mapping_id][H_ROOF_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][32])) h_info[idx][h_mapping][32] = CreateDynamicObject(19376, 980.658691, 1246.426391, 1027.093750, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][32], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][33])) h_info[idx][h_mapping][33] = CreateDynamicObject(19376, 980.658691, 1236.797119, 1027.093750, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][33], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][34])) h_info[idx][h_mapping][34] = CreateDynamicObject(19376, 970.159240, 1236.797119, 1027.093750, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][34], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            //___________________________________________________________________________________________
            //Потолок ванная
            txd_id = h_info[idx][h_mapping_id][H_ROOF_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][35])) h_info[idx][h_mapping][35] = CreateDynamicObject(19381, 978.929321, 1227.307861, 1027.073730, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][35], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
        }
        case 3:
        {
            /*  class = 3 MySQL:

            0|6|-1|7|8|0|0|-1|-1|12|12|7|8|10|11|12|-1|-1|0|4|5|6|7|8|9|-1|-1

            h_info[idx][h_mapping_id][H_FOOR_HALLWAY] = 0;
            h_info[idx][h_mapping_id][H_FOOR_HALLWAY2] = 6;
            h_info[idx][h_mapping_id][H_FOOR_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_FOOR_KITCHEN] = 7;
            h_info[idx][h_mapping_id][H_FOOR_BATHROOM] = 8;
            h_info[idx][h_mapping_id][H_FOOR_CABINET] = 0;
            h_info[idx][h_mapping_id][H_FOOR_ROOM] = 0;
            h_info[idx][h_mapping_id][H_FOOR_BAR] = -1;
            h_info[idx][h_mapping_id][H_FOOR_GYM] = -1;

            h_info[idx][h_mapping_id][H_WALL_HALLWAY] = 12;
            h_info[idx][h_mapping_id][H_WALL_LIVING_ROOM] = 12;
            h_info[idx][h_mapping_id][H_WALL_KITCHEN] = 7;
            h_info[idx][h_mapping_id][H_WALL_BATHROOM] = 8;
            h_info[idx][h_mapping_id][H_WALL_CABINET] = 10;
            h_info[idx][h_mapping_id][H_WALL_BED] = 11;
            h_info[idx][h_mapping_id][H_WALL_ROOM] = 12;
            h_info[idx][h_mapping_id][H_WALL_BAR] = -1;
            h_info[idx][h_mapping_id][H_WALL_GYM] = -1;

            h_info[idx][h_mapping_id][H_ROOF_HALLWAY] = 0;
            h_info[idx][h_mapping_id][H_ROOF_LIVING_ROOM] = 4;
            h_info[idx][h_mapping_id][H_ROOF_KITCHEN] = 5;
            h_info[idx][h_mapping_id][H_ROOF_BATHROOM] = 6;
            h_info[idx][h_mapping_id][H_ROOF_CABINET] = 7;
            h_info[idx][h_mapping_id][H_ROOF_ROOM] = 8;
            h_info[idx][h_mapping_id][H_ROOF_BALCONY] = 9;
            h_info[idx][h_mapping_id][H_ROOF_BAR] = -1;
            h_info[idx][h_mapping_id][H_ROOF_GYM] = -1;

            */
            //______________________________________________________________________________
            //Гостинная, прихожая и часть кухни первый этаж пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][0])) h_info[idx][h_mapping][0] = CreateDynamicObject(19377, -119.367919, 1269.416503, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][1])) h_info[idx][h_mapping][1] = CreateDynamicObject(19377, -108.868164, 1259.786743, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][1], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][2])) h_info[idx][h_mapping][2] = CreateDynamicObject(19377, -119.367919, 1259.796508, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][2], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][3])) h_info[idx][h_mapping][3] = CreateDynamicObject(19377, -108.868164, 1269.416503, 1023.450073, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][3], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            //______________________________________________________________________________
            //Гостинная второй этаж пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_HALLWAY2];
            if(txd_id != -1)
            {
                if(!IsValidDynamicObject(h_info[idx][h_mapping][4])) h_info[idx][h_mapping][4] = CreateDynamicObject(19460, -113.189575, 1269.539428, 1026.991699, 0.000007, 90.000000, 179.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
                SetDynamicObjectMaterial(h_info[idx][h_mapping][4], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFF0F0F0);
                if(!IsValidDynamicObject(h_info[idx][h_mapping][5])) h_info[idx][h_mapping][5] = CreateDynamicObject(19460, -116.238281, 1265.929443, 1026.987792, 0.000007, 90.000000, 134.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
                SetDynamicObjectMaterial(h_info[idx][h_mapping][5], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFF0F0F0);
                if(!IsValidDynamicObject(h_info[idx][h_mapping][6])) h_info[idx][h_mapping][6] = CreateDynamicObject(19460, -116.318847, 1262.975830, 1026.991699, 0.000007, 90.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
                SetDynamicObjectMaterial(h_info[idx][h_mapping][6], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFF0F0F0);
                if(!IsValidDynamicObject(h_info[idx][h_mapping][7])) h_info[idx][h_mapping][7] = CreateDynamicObject(19460, -119.809082, 1262.975830, 1026.995605, 0.000007, 90.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
                SetDynamicObjectMaterial(h_info[idx][h_mapping][7], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFF0F0F0);
            }
            //__________________________________________________________________________________________________
            //Пол кухня
            txd_id = h_info[idx][h_mapping_id][H_FOOR_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][8])) h_info[idx][h_mapping][8] = CreateDynamicObject(19382, -115.707763, 1255.925292, 1023.460083, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][8], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            //__________________________________________________________________________________________________
            //Пол ванная
            txd_id = h_info[idx][h_mapping_id][H_FOOR_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][9])) h_info[idx][h_mapping][9] = CreateDynamicObject(18765, -104.252563, 1257.278564, 1021.064819, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][9], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFFFFFFF);
            //__________________________________________________________________________________________________
            /*//Пол в ванной где джакузи
            txd_id = h_info[idx][h_mapping_id][H_FOOR_BATHROOM2];
            h_info[idx][h_mapping][0] = CreateDynamicObject(19372, -103.579345, 1257.210083, 1023.493896, 0.000007, 90.000015, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFF0F0F0);
            h_info[idx][h_mapping][0] = CreateDynamicObject(19372, -105.200195, 1257.210083, 1023.483947, 0.000007, 90.000015, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0xFFF0F0F0);
            *///__________________________________________________________________________________________________
            //Комната пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][10])) h_info[idx][h_mapping][10] = CreateDynamicObject(19376, -106.308105, 1268.995605, 1027.001220, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][10], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Кабинет пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_CABINET];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][11])) h_info[idx][h_mapping][11] = CreateDynamicObject(19379, -116.687988, 1256.646972, 1027.001220, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][11], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            //__________________________________________________________________________________________________
            //Стена лестницы и прихожей
            txd_id = h_info[idx][h_mapping_id][H_WALL_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][12])) h_info[idx][h_mapping][12] = CreateDynamicObject(19447, -107.309326, 1274.190185, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][12], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][13])) h_info[idx][h_mapping][13] = CreateDynamicObject(19357, -102.578857, 1262.289794, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][13], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][14])) h_info[idx][h_mapping][14] = CreateDynamicObject(19357, -105.005004, 1262.283935, 1027.914062, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][14], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][15])) h_info[idx][h_mapping][15] = CreateDynamicObject(19447, -103.659423, 1269.319580, 1025.273803, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][16])) h_info[idx][h_mapping][16] = CreateDynamicObject(19447, -103.667480, 1267.112060, 1025.273803, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][17])) h_info[idx][h_mapping][17] = CreateDynamicObject(19447, -106.769287, 1262.287841, 1028.754516, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][18])) h_info[idx][h_mapping][18] = CreateDynamicObject(19430, -112.038452, 1273.360107, 1025.274536, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            //______________________________________________________________________________
            //Гостинная стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_LIVING_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][19])) h_info[idx][h_mapping][19] = CreateDynamicObject(19456, -119.790039, 1274.159423, 1025.272583, 0.000007, 0.000000, 89.999977, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][20])) h_info[idx][h_mapping][20] = CreateDynamicObject(19427, -124.188232, 1256.469970, 1025.274536, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][21])) h_info[idx][h_mapping][21] = CreateDynamicObject(19354, -125.708984, 1257.209716, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][22])) h_info[idx][h_mapping][22] = CreateDynamicObject(19354, -122.588867, 1255.638916, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][23])) h_info[idx][h_mapping][23] = CreateDynamicObject(19427, -121.068115, 1254.919921, 1025.274536, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][24])) h_info[idx][h_mapping][24] = CreateDynamicObject(19354, -114.018554, 1260.848999, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][25])) h_info[idx][h_mapping][25] = CreateDynamicObject(19427, -115.548095, 1261.570556, 1025.274536, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][26])) h_info[idx][h_mapping][26] = CreateDynamicObject(19456, -110.799072, 1262.289794, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][27])) h_info[idx][h_mapping][27] = CreateDynamicObject(19427, -111.497802, 1261.570556, 1028.804077, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][27], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][28])) h_info[idx][h_mapping][28] = CreateDynamicObject(19354, -113.148437, 1261.409179, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][28], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][29])) h_info[idx][h_mapping][29] = CreateDynamicObject(19354, -113.144287, 1272.623291, 1028.758178, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][29], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][30])) h_info[idx][h_mapping][30] = CreateDynamicObject(19456, -111.551269, 1273.910034, 1028.773681, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][30], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][31])) h_info[idx][h_mapping][31] = CreateDynamicObject(19354, -111.548583, 1265.759521, 1028.754272, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][31], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][32])) h_info[idx][h_mapping][32] = CreateDynamicObject(19456, -106.769287, 1264.238037, 1028.754516, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][32], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][33])) h_info[idx][h_mapping][33] = CreateDynamicObject(19354, -103.658935, 1262.708984, 1028.754272, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][33], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][34])) h_info[idx][h_mapping][34] = CreateDynamicObject(19354, -111.544555, 1268.380004, 1031.435058, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][34], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][35])) h_info[idx][h_mapping][35] = CreateDynamicObject(19456, -119.336059, 1261.405273, 1031.434570, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][35], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][36])) h_info[idx][h_mapping][36] = CreateDynamicObject(19427, -115.098388, 1273.360107, 1025.274536, 0.000000, 0.000007, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][36], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][37])) h_info[idx][h_mapping][37] = CreateDynamicObject(19456, -119.790039, 1274.159423, 1028.771850, 0.000007, 0.000000, 89.999977, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][37], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][38])) h_info[idx][h_mapping][38] = CreateDynamicObject(19354, -113.572143, 1272.643310, 1025.274536, 0.000019, 0.000000, 89.999931, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][38], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][39])) h_info[idx][h_mapping][39] = CreateDynamicObject(19456, -122.689453, 1267.780151, 1031.774047, 0.000000, 0.000007, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][39], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][40])) h_info[idx][h_mapping][40] = CreateDynamicObject(19427, -123.698486, 1273.340087, 1025.274536, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][40], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][41])) h_info[idx][h_mapping][41] = CreateDynamicObject(19427, -124.378662, 1273.340087, 1027.084594, 0.000007, 90.000015, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][41], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][42])) h_info[idx][h_mapping][42] = CreateDynamicObject(19427, -122.708129, 1273.340087, 1028.754272, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][42], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][43])) h_info[idx][h_mapping][43] = CreateDynamicObject(19456, -124.369750, 1267.759399, 1030.102783, 0.000007, 90.000000, 179.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][43], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][44])) h_info[idx][h_mapping][44] = CreateDynamicObject(19427, -122.688476, 1262.279174, 1028.805786, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][44], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][45])) h_info[idx][h_mapping][45] = CreateDynamicObject(19456, -121.298339, 1261.409179, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][45], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][46])) h_info[idx][h_mapping][46] = CreateDynamicObject(19456, -119.769775, 1274.290161, 1029.442138, 0.000007, 90.000000, 269.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][46], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][47])) h_info[idx][h_mapping][47] = CreateDynamicObject(19456, -119.781982, 1272.622314, 1031.109985, 0.000007, 0.000000, 89.999977, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][47], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][48])) h_info[idx][h_mapping][48] = CreateDynamicObject(19427, -114.708740, 1273.340087, 1027.084594, 0.000007, 90.000015, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][48], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][49])) h_info[idx][h_mapping][49] = CreateDynamicObject(19427, -116.387695, 1273.340087, 1028.754272, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][49], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][50])) h_info[idx][h_mapping][50] = CreateDynamicObject(19354, -124.228393, 1272.619384, 1028.754272, 180.000000, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][50], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][51])) h_info[idx][h_mapping][51] = CreateDynamicObject(19354, -125.218505, 1272.619384, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][51], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][52])) h_info[idx][h_mapping][52] = CreateDynamicObject(19354, -124.217895, 1263.009399, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][52], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][53])) h_info[idx][h_mapping][53] = CreateDynamicObject(19354, -114.858520, 1272.619384, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][53], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            //__________________________________________________________________________________________________
            //Стенка кухня
            txd_id = h_info[idx][h_mapping_id][H_WALL_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][54])) h_info[idx][h_mapping][54] = CreateDynamicObject(19448, -118.889892, 1254.939697, 1025.272583, 0.000007, 0.000000, 89.999977, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][54], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][55])) h_info[idx][h_mapping][55] = CreateDynamicObject(19448, -114.159423, 1255.957885, 1025.273803, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][55], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Ванная стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][56])) h_info[idx][h_mapping][56] = CreateDynamicObject(19449, -101.937500, 1263.761474, 1025.273803, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][56], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][57])) h_info[idx][h_mapping][57] = CreateDynamicObject(19449, -109.215332, 1257.346557, 1025.249877, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][57], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][58])) h_info[idx][h_mapping][58] = CreateDynamicObject(19371, -104.666870, 1262.255615, 1027.904052, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][58], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][59])) h_info[idx][h_mapping][59] = CreateDynamicObject(19371, -107.558715, 1262.249755, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][59], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][60])) h_info[idx][h_mapping][60] = CreateDynamicObject(19371, -108.408691, 1255.659423, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][60], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);

            /*txd_id = h_info[idx][h_mapping_id][H_WALL_BATHROOM2];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][])) h_info[idx][h_mapping][50] = CreateDynamicObject(19449, -101.917480, 1260.541015, 1025.269897, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][50], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][])) h_info[idx][h_mapping][54] = CreateDynamicObject(19371, -103.579101, 1255.649780, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][54], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][])) h_info[idx][h_mapping][55] = CreateDynamicObject(19371, -106.779174, 1255.649780, 1025.254150, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][55], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            *///__________________________________________________________________________________________________
            //Кабинет стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_CABINET];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][61])) h_info[idx][h_mapping][61] = CreateDynamicObject(19459, -111.551269, 1256.550903, 1028.773681, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][61], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][62])) h_info[idx][h_mapping][62] = CreateDynamicObject(19459, -122.000976, 1256.550903, 1028.773681, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][62], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][63])) h_info[idx][h_mapping][63] = CreateDynamicObject(19459, -121.298339, 1261.389160, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][63], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][64])) h_info[idx][h_mapping][64] = CreateDynamicObject(19459, -116.828369, 1251.768920, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][64], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][65])) h_info[idx][h_mapping][65] = CreateDynamicObject(19367, -115.334442, 1261.401123, 1031.424682, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][65], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][66])) h_info[idx][h_mapping][66] = CreateDynamicObject(19367, -113.148437, 1261.399169, 1028.754272, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][66], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][67])) h_info[idx][h_mapping][67] = CreateDynamicObject(19367, -120.961425, 1252.892456, 1028.754272, 0.000007, 0.000014, 44.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][67], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFC8C8C8);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][68])) h_info[idx][h_mapping][68] = CreateDynamicObject(19367, -112.631713, 1252.808593, 1028.754272, 0.000007, 0.000014, 134.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][68], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFC8C8C8);
            //___________________________________________________________________________________________________
            // Стена кровать
            txd_id = h_info[idx][h_mapping_id][H_WALL_BED];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][69])) h_info[idx][h_mapping][69] = CreateDynamicObject(19455, -101.990966, 1269.039794, 1028.553466, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][69], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Комната стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][70])) h_info[idx][h_mapping][70] = CreateDynamicObject(19457, -106.769287, 1273.838500, 1028.754516, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][70], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][71])) h_info[idx][h_mapping][71] = CreateDynamicObject(19457, -102.599121, 1269.319580, 1031.443969, 180.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][71], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][72])) h_info[idx][h_mapping][72] = CreateDynamicObject(19457, -100.908447, 1269.399658, 1029.773681, 180.000000, 90.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][72], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFD2D2D2);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][73])) h_info[idx][h_mapping][73] = CreateDynamicObject(19457, -106.767333, 1264.255615, 1028.754516, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][73], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][74])) h_info[idx][h_mapping][74] = CreateDynamicObject(19457, -111.521240, 1273.910034, 1028.773681, 0.000000, 0.000007, 180.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][74], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][75])) h_info[idx][h_mapping][75] = CreateDynamicObject(19365, -101.078125, 1265.799682, 1028.794311, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][75], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][76])) h_info[idx][h_mapping][76] = CreateDynamicObject(19365, -101.078125, 1272.310302, 1028.794311, 0.000007, 0.000014, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][76], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][77])) h_info[idx][h_mapping][77] = CreateDynamicObject(19365, -111.518554, 1265.759521, 1028.754272, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][77], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][78])) h_info[idx][h_mapping][78] = CreateDynamicObject(19365, -111.524536, 1268.380004, 1031.435058, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][78], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][79])) h_info[idx][h_mapping][79] = CreateDynamicObject(19438, -102.598266, 1265.058837, 1028.805786, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][79], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][80])) h_info[idx][h_mapping][80] = CreateDynamicObject(19438, -102.598266, 1273.029907, 1028.805786, 0.000007, 0.000014, 179.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][80], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            //__________________________________________________________________________________________________
            //Потолок лестница и прихожая
            txd_id = h_info[idx][h_mapping_id][H_ROOF_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][81])) h_info[idx][h_mapping][81] = CreateDynamicObject(19463, -107.096191, 1262.467773, 1028.797729, 21.500005, 90.000015, 89.999923, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][81], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFD2D2D2);
            //__________________________________________________________________________________________________
            //Гостинная потолок
            txd_id = h_info[idx][h_mapping_id][H_ROOF_LIVING_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][82])) h_info[idx][h_mapping][82] = CreateDynamicObject(19380, -117.417846, 1267.755981, 1030.551391, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][82], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][83])) h_info[idx][h_mapping][83] = CreateDynamicObject(19380, -116.847412, 1267.755981, 1030.559204, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][83], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][84])) h_info[idx][h_mapping][84] = CreateDynamicObject(19380, -116.847412, 1266.294555, 1030.563110, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][84], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][85])) h_info[idx][h_mapping][85] = CreateDynamicObject(19380, -117.417846, 1266.294799, 1030.555297, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][85], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Потолок прихожая и кухня
            txd_id = h_info[idx][h_mapping_id][H_ROOF_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][86])) h_info[idx][h_mapping][86] = CreateDynamicObject(19381, -119.447753, 1256.646972, 1026.961181, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][86], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][87])) h_info[idx][h_mapping][87] = CreateDynamicObject(19381, -106.308105, 1268.991699, 1026.960937, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][87], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][88])) h_info[idx][h_mapping][88] = CreateDynamicObject(19381, -106.308105, 1269.522216, 1026.964843, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][88], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Потолок ванная
            txd_id = h_info[idx][h_mapping_id][H_ROOF_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][89])) h_info[idx][h_mapping][89] = CreateDynamicObject(18765, -104.252563, 1257.278564, 1029.474609, 0.000000, 0.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][89], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFFFFFFF);
            //__________________________________________________________________________________________________
            //Кабинет потолок
            txd_id = h_info[idx][h_mapping_id][H_ROOF_CABINET];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][90])) h_info[idx][h_mapping][90] = CreateDynamicObject(19378, -116.687988, 1256.646972, 1030.561157, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][90], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Комната потолок
            txd_id = h_info[idx][h_mapping_id][H_ROOF_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][91])) h_info[idx][h_mapping][91] = CreateDynamicObject(19375, -106.308105, 1269.131835, 1030.445190, 0.000000, 90.000000, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][91], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            //__________________________________________________________________________________________________
            //Потолок прихожая балкон
            txd_id = h_info[idx][h_mapping_id][H_ROOF_BALCONY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][92])) h_info[idx][h_mapping][92] = CreateDynamicObject(19453, -113.243652, 1269.571655, 1026.973876, 0.000007, 90.000000, 179.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][92], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][93])) h_info[idx][h_mapping][93] = CreateDynamicObject(19453, -116.293457, 1263.041381, 1026.973876, 0.000007, 90.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][93], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][94])) h_info[idx][h_mapping][94] = CreateDynamicObject(19453, -119.807861, 1263.037475, 1026.969970, 0.000007, 90.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][94], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][95])) h_info[idx][h_mapping][95] = CreateDynamicObject(19453, -116.158691, 1266.134643, 1026.966064, 0.000007, 90.000000, 134.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 100.00, 100.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][95], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0xFFF0F0F0);
        }
        case 4:
        {
            /*  class = 4
            10|-1|-1|11|12|-1|13|10|14|13|-1|8|14|-1|-1|15|16|17|10|-1|11|12|-1|13|-1|10|0

            h_info[idx][h_mapping_id][H_FOOR_HALLWAY] = 10;
            h_info[idx][h_mapping_id][H_FOOR_HALLWAY2] = -1;
            h_info[idx][h_mapping_id][H_FOOR_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_FOOR_KITCHEN] = 11;
            h_info[idx][h_mapping_id][H_FOOR_BATHROOM] = 12;
            h_info[idx][h_mapping_id][H_FOOR_CABINET] = -1;
            h_info[idx][h_mapping_id][H_FOOR_ROOM] = 13;
            h_info[idx][h_mapping_id][H_FOOR_BAR] = 10;
            h_info[idx][h_mapping_id][H_FOOR_GYM] = 14;

            h_info[idx][h_mapping_id][H_WALL_HALLWAY] = 13;
            h_info[idx][h_mapping_id][H_WALL_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_WALL_KITCHEN] = 8;
            h_info[idx][h_mapping_id][H_WALL_BATHROOM] = 14;
            h_info[idx][h_mapping_id][H_WALL_CABINET] = -1;
            h_info[idx][h_mapping_id][H_WALL_BED] = -1;
            h_info[idx][h_mapping_id][H_WALL_ROOM] = 15;
            h_info[idx][h_mapping_id][H_WALL_BAR] = 16;
            h_info[idx][h_mapping_id][H_WALL_GYM] = 17;

            h_info[idx][h_mapping_id][H_ROOF_HALLWAY] = -1;
            h_info[idx][h_mapping_id][H_ROOF_LIVING_ROOM] = -1;
            h_info[idx][h_mapping_id][H_ROOF_KITCHEN] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BATHROOM] = -1;
            h_info[idx][h_mapping_id][H_ROOF_CABINET] = -1;
            h_info[idx][h_mapping_id][H_ROOF_ROOM] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BALCONY] = -1;
            h_info[idx][h_mapping_id][H_ROOF_BAR] = 10;
            h_info[idx][h_mapping_id][H_ROOF_GYM] = 0;
            */
            //___________________________________________________________
            // Прихожая Пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][0]))  h_info[idx][h_mapping][0] = CreateDynamicObject(19377, 311.522460, -426.098480, 999.824645, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][0], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][1]))  h_info[idx][h_mapping][1] = CreateDynamicObject(19377, 311.522460, -435.718536, 999.826660, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][1], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][2]))  h_info[idx][h_mapping][2] = CreateDynamicObject(19377, 311.522460, -440.128601, 999.822631, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][2], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][3]))  h_info[idx][h_mapping][3] = CreateDynamicObject(19377, 322.020599, -426.098480, 999.822631, 0.000000, 90.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][3], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][4]))  h_info[idx][h_mapping][4] = CreateDynamicObject(19377, 322.020599, -435.718536, 999.824645, 0.000000, 90.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][4], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][5]))  h_info[idx][h_mapping][5] = CreateDynamicObject(19377, 322.020599, -440.128601, 999.820617, 0.000000, 90.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][5], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            /// Пол кухня
            txd_id = h_info[idx][h_mapping_id][H_FOOR_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][6]))  h_info[idx][h_mapping][6] = CreateDynamicObject(19376, 317.172546, -449.528625, 999.826660, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][6], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][7]))  h_info[idx][h_mapping][7] = CreateDynamicObject(19376, 317.172546, -451.288543, 999.818603, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][7], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][8]))  h_info[idx][h_mapping][8] = CreateDynamicObject(19376, 322.222503, -449.528625, 999.820617, 0.000000, 90.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][8], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][9]))  h_info[idx][h_mapping][9] = CreateDynamicObject(19376, 322.222503, -451.288543, 999.812561, 0.000000, 90.000022, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][9], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            // Ванная Пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][10]))  h_info[idx][h_mapping][10] = CreateDynamicObject(19382, 306.101806, -408.088562, 1003.344970, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][10], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            // Комната Пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][11]))  h_info[idx][h_mapping][11] = CreateDynamicObject(19381, 306.332031, -417.708587, 1003.346984, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][11], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            // Пол бар
            txd_id = h_info[idx][h_mapping_id][H_FOOR_BAR];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][12]))  h_info[idx][h_mapping][12] = CreateDynamicObject(19375, 311.522460, -416.468566, 999.824645, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][12], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][13]))  h_info[idx][h_mapping][13] = CreateDynamicObject(19375, 313.522430, -416.468566, 999.818603, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][13], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            // Спорт зал Пол
            txd_id = h_info[idx][h_mapping_id][H_FOOR_GYM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][14]))  h_info[idx][h_mapping][14] = CreateDynamicObject(19379, 305.516723, -448.232543, 1003.347106, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][14], 0, FornitureTexture_Foor[txd_id][ft_ObjectID], FornitureTexture_Foor[txd_id][ft_TxdName], FornitureTexture_Foor[txd_id][ft_TextureName], 0x00000000);

            //=========================================================================================
            //Холл прихожая:
            //Стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_HALLWAY];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][15]))  h_info[idx][h_mapping][15] = CreateDynamicObject(19431, 314.045776, -421.213989, 1003.161254, 89.999992, -180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][15], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][16]))  h_info[idx][h_mapping][16] = CreateDynamicObject(19431, 314.047729, -421.209960, 1003.461425, 89.999992, -180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][16], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][17]))  h_info[idx][h_mapping][17] = CreateDynamicObject(19431, 310.406250, -421.213989, 1001.461181, 89.999992, -180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][17], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][18]))  h_info[idx][h_mapping][18] = CreateDynamicObject(19456, 325.608398, -426.017028, 1002.414611, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][18], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][19]))  h_info[idx][h_mapping][19] = CreateDynamicObject(19431, 306.906127, -421.213989, 1001.461181, 89.999992, -180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][19], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][20]))  h_info[idx][h_mapping][20] = CreateDynamicObject(19456, 306.738403, -439.593505, 1002.414611, 0.000037, -0.000023, -179.999603, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][20], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][21]))  h_info[idx][h_mapping][21] = CreateDynamicObject(19456, 320.766235, -421.213989, 1002.421325, 0.000022, -0.000022, -89.999984, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][21], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][22]))  h_info[idx][h_mapping][22] = CreateDynamicObject(19456, 320.768676, -444.643981, 1002.421325, 0.000045, -0.000014, 89.999961, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][22], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][23]))  h_info[idx][h_mapping][23] = CreateDynamicObject(19456, 325.608398, -439.939025, 1002.414611, 0.000029, 0.000007, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][23], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][24]))  h_info[idx][h_mapping][24] = CreateDynamicObject(19456, 306.730590, -429.967529, 1002.414611, 0.000037, -0.000037, -179.999511, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][24], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][25]))  h_info[idx][h_mapping][25] = CreateDynamicObject(19431, 310.404296, -421.217956, 1002.601623, 89.999992, -180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][25], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][26]))  h_info[idx][h_mapping][26] = CreateDynamicObject(19431, 306.904541, -421.217956, 1002.601623, 89.999992, -180.000000, 90.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][26], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][27]))  h_info[idx][h_mapping][27] = CreateDynamicObject(19456, 306.736450, -426.243530, 1002.414611, 0.000037, -0.000037, -179.999511, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][27], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][28]))  h_info[idx][h_mapping][28] = CreateDynamicObject(19456, 306.728637, -427.435546, 1005.344543, 0.000037, -0.000046, -179.999465, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][28], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][29]))  h_info[idx][h_mapping][29] = CreateDynamicObject(19431, 314.047729, -444.673980, 1003.461425, 89.999992, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][29], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][30]))  h_info[idx][h_mapping][30] = CreateDynamicObject(19431, 314.047729, -444.677978, 1003.171264, 89.999992, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][30], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][31]))  h_info[idx][h_mapping][31] = CreateDynamicObject(19431, 310.406250, -444.647949, 1001.461181, 89.999992, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][31], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][32]))  h_info[idx][h_mapping][32] = CreateDynamicObject(19431, 306.906616, -444.647949, 1001.461181, 89.999992, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][32], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][33]))  h_info[idx][h_mapping][33] = CreateDynamicObject(19431, 306.906616, -444.651947, 1002.471679, 89.999992, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][33], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][34]))  h_info[idx][h_mapping][34] = CreateDynamicObject(19431, 310.404296, -444.651947, 1002.451660, 89.999992, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][34], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][35]))  h_info[idx][h_mapping][35] = CreateDynamicObject(19456, 306.728637, -437.067565, 1005.344543, 0.000037, -0.000046, -179.999465, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][35], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][36]))  h_info[idx][h_mapping][36] = CreateDynamicObject(19456, 306.720825, -438.561523, 1005.344543, 0.000037, -0.000046, -179.999465, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][36], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][37]))  h_info[idx][h_mapping][37] = CreateDynamicObject(19431, 311.326904, -443.395996, 1005.339477, -0.000037, 179.999984, -90.000152, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][37], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][38]))  h_info[idx][h_mapping][38] = CreateDynamicObject(19431, 311.328613, -422.550018, 1005.339477, -0.000022, 179.999984, 89.999740, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][38], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][39]))  h_info[idx][h_mapping][39] = CreateDynamicObject(19354, 307.205200, -422.550018, 1005.339477, -0.000006, 179.999984, 89.999694, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][39], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][40]))  h_info[idx][h_mapping][40] = CreateDynamicObject(19354, 307.207153, -443.405944, 1005.339477, -0.000029, 179.999984, -90.000251, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][40], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][41]))  h_info[idx][h_mapping][41] = CreateDynamicObject(19354, 309.387573, -443.397949, 1007.789733, -0.000022, 179.999984, -90.000274, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][41], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][42]))  h_info[idx][h_mapping][42] = CreateDynamicObject(19354, 309.387573, -422.547973, 1007.789733, -0.000022, 179.999984, -90.000274, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][42], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            //Кухня:
            //Стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_KITCHEN];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][43]))  h_info[idx][h_mapping][43] = CreateDynamicObject(19457, 312.079467, -449.597961, 1001.661499, 180.000000, 179.999984, 179.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][43], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][44]))  h_info[idx][h_mapping][44] = CreateDynamicObject(19428, 316.049804, -445.567962, 1001.661499, 180.000000, 179.999984, 179.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][44], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][45]))  h_info[idx][h_mapping][45] = CreateDynamicObject(19457, 320.778686, -446.283966, 1001.660827, 0.000045, -0.000014, 89.999961, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][45], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][46]))  h_info[idx][h_mapping][46] = CreateDynamicObject(19457, 320.778686, -455.983978, 1001.660827, 0.000050, -0.000012, 89.999938, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][46], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][47]))  h_info[idx][h_mapping][47] = CreateDynamicObject(19457, 314.377807, -455.993957, 1001.660827, 0.000050, -0.000012, 89.999938, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][47], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][48]))  h_info[idx][h_mapping][48] = CreateDynamicObject(19457, 312.069458, -455.977966, 1001.661499, 180.000000, 179.999984, 179.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][48], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFF0F0F0);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][49]))  h_info[idx][h_mapping][49] = CreateDynamicObject(19457, 315.986206, -444.717956, 1004.091064, 360.000000, -180.000000, 89.999969, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][49], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            // Ванная Стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_BATHROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][50]))  h_info[idx][h_mapping][50] = CreateDynamicObject(19443, 305.326171, -412.799987, 1005.169311, 179.999969, 179.999984, 89.999740, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][50], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][51]))  h_info[idx][h_mapping][51] = CreateDynamicObject(19462, 306.197998, -408.067077, 1005.154235, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][51], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][52]))  h_info[idx][h_mapping][52] = CreateDynamicObject(19462, 300.958007, -408.067108, 1005.154235, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][52], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][53]))  h_info[idx][h_mapping][53] = CreateDynamicObject(19462, 301.928588, -403.217102, 1005.154235, 0.000029, 0.000014, 90.000167, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][53], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);

            // Комната Стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_ROOM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][54]))  h_info[idx][h_mapping][54] = CreateDynamicObject(19427, 311.326660, -422.520019, 1005.169311, -0.000022, 179.999984, 89.999740, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][54], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][55]))  h_info[idx][h_mapping][55] = CreateDynamicObject(19427, 307.966308, -422.520019, 1005.169311, 179.999969, 179.999984, 89.999740, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][55], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][56]))  h_info[idx][h_mapping][56] = CreateDynamicObject(19427, 307.125122, -421.650024, 1005.169250, -0.000006, 179.999984, 179.999694, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][56], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][57]))  h_info[idx][h_mapping][57] = CreateDynamicObject(19460, 311.598388, -417.667053, 1005.154235, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][57], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][58]))  h_info[idx][h_mapping][58] = CreateDynamicObject(19460, 309.348266, -412.847045, 1005.154235, 0.000029, 0.000014, 90.000167, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][58], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][59]))  h_info[idx][h_mapping][59] = CreateDynamicObject(19460, 302.249023, -420.817077, 1007.074462, 0.000029, 0.000014, 90.000167, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][59], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][60]))  h_info[idx][h_mapping][60] = CreateDynamicObject(19460, 301.008056, -417.677093, 1005.154235, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][60], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][61]))  h_info[idx][h_mapping][61] = CreateDynamicObject(19359, 309.395751, -422.530029, 1007.779724, -0.000006, 179.999984, 89.999694, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][61], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);

            //Бар:
            //Стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_BAR];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][62]))  h_info[idx][h_mapping][62] = CreateDynamicObject(19458, 320.768676, -421.176025, 1001.640380, 0.000000, 360.000000, 89.999847, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][62], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][63]))  h_info[idx][h_mapping][63] = CreateDynamicObject(19356, 310.539062, -419.679962, 1001.662536, 0.000000, 360.000000, 89.999847, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][63], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][64]))  h_info[idx][h_mapping][64] = CreateDynamicObject(19458, 318.798583, -416.337036, 1001.644348, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][64], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][65]))  h_info[idx][h_mapping][65] = CreateDynamicObject(19458, 306.769165, -416.337036, 1001.644348, 0.000029, 0.000014, 0.000165, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][65], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][66]))  h_info[idx][h_mapping][66] = CreateDynamicObject(19429, 312.069335, -420.407958, 1001.661499, 180.000000, 179.999984, 179.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][66], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][67]))  h_info[idx][h_mapping][67] = CreateDynamicObject(19458, 316.917724, -421.179992, 1004.122436, 180.000000, 360.000000, 89.999847, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][67], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][68]))  h_info[idx][h_mapping][68] = CreateDynamicObject(19356, 308.416870, -419.683959, 1001.662536, 0.000000, 360.000000, 89.999847, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][68], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            // Спорт зал Стены
            txd_id = h_info[idx][h_mapping_id][H_WALL_GYM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][69])) h_info[idx][h_mapping][69] = CreateDynamicObject(19459, 310.619506, -448.277954, 1005.171752, 180.000000, 179.999984, 179.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][69], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][70])) h_info[idx][h_mapping][70] = CreateDynamicObject(19357, 307.207153, -443.445922, 1005.189392, -0.000029, 179.999984, -90.000251, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][70], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][71])) h_info[idx][h_mapping][71] = CreateDynamicObject(19430, 306.760620, -444.325988, 1005.179382, -0.000037, 179.999984, -0.000151, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][71], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][72])) h_info[idx][h_mapping][72] = CreateDynamicObject(19459, 300.319213, -448.277893, 1005.171752, 180.000000, 179.999984, 179.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][72], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0xFFE6E6E6);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][73])) h_info[idx][h_mapping][73] = CreateDynamicObject(19459, 305.749877, -453.087921, 1005.171752, 180.000000, 179.999984, 269.999633, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][73], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][74])) h_info[idx][h_mapping][74] = CreateDynamicObject(19459, 305.073120, -453.083923, 1005.173767, 180.000000, 179.999984, 269.999633, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][74], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][75])) h_info[idx][h_mapping][75] = CreateDynamicObject(19357, 309.053222, -443.441955, 1007.759460, -0.000029, 179.999984, -90.000251, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][75], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][76])) h_info[idx][h_mapping][76] = CreateDynamicObject(19458, 302.029296, -445.097930, 1005.171752, 180.000000, 179.999984, 89.999649, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][76], 0, FornitureTexture_Wall[txd_id][ft_ObjectID], FornitureTexture_Wall[txd_id][ft_TxdName], FornitureTexture_Wall[txd_id][ft_TextureName], 0x00000000);

            //_____________________________________________________________________________
            // Потолок Бар
            txd_id = h_info[idx][h_mapping_id][H_ROOF_BAR];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][77])) h_info[idx][h_mapping][77] = CreateDynamicObject(19378, 311.522460, -416.468597, 1003.198669, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][77], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
            if(!IsValidDynamicObject(h_info[idx][h_mapping][78])) h_info[idx][h_mapping][78] = CreateDynamicObject(19378, 313.745483, -416.464599, 1003.202697, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][78], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);

            //Потолок Спорт зал
            txd_id = h_info[idx][h_mapping_id][H_ROOF_GYM];
            if(!IsValidDynamicObject(h_info[idx][h_mapping][79])) h_info[idx][h_mapping][79] = CreateDynamicObject(19380, 305.516723, -448.232543, 1006.997375, 0.000000, 90.000015, 0.000000, idx+50, HOUSE_INT_ID_REPAIR, -1, 300.00, 300.00);
            SetDynamicObjectMaterial(h_info[idx][h_mapping][79], 0, FornitureTexture_Roof[txd_id][ft_ObjectID], FornitureTexture_Roof[txd_id][ft_TxdName], FornitureTexture_Roof[txd_id][ft_TextureName], 0x00000000);
        }
    }
}

forward OnHouseMappingBack(playerid, houseId, txd_id, txd_value, id_notify);
public OnHouseMappingBack(playerid, houseId, txd_id, txd_value, id_notify)
{
    if(houseId < 0 || txd_value < 0 || txd_id < 0)
    {
        printf("[SYSTEM] CRASH DETECT LOG: | %d | %d | %d / %d", houseId, txd_id, txd_value, id_notify);
        return 1;
    }
    if(p_temp[playerid][h_repair_list] == GARAGE_REPAIR_ID)
    {
        h_info[houseId][h_garage_id][txd_id] = txd_value;
        Garage_Repair(houseId);
    }
    else
    {
        h_info[houseId][h_mapping_id][txd_id] = txd_value;
        House_Repair(houseId);
    }
    if(playerid != INVALID_PLAYER_ID)
    {
        if(id_notify == -1)
            SendInfo(playerid, "Время закончилилось. Ремонт отменен.");
        if(id_notify == 1)
            SendInfo(playerid, "Вы заспавнены. Ремонт отменен.");
        if(id_notify == 2)
            SendInfo(playerid, "Вы умерли. Ремонт отменен.");
        if(id_notify == 5)
            SendInfo(playerid, "Вы отменили ремонт.");

        p_temp[playerid][h_repair_old] =
        p_temp[playerid][h_repair_list] =
        p_temp[playerid][h_repair_txtid] = -1;

        p_temp[playerid][shop_id] = 0;
        HideTextDrawForPlayer(playerid, TD_ID_SHOP);
        if(IsValidTimer(h_info[houseId][h_mapping_timer])) KillTimer(h_info[houseId][h_mapping_timer]);
    }
    return 1;
}

GetMaxCountTextureHouse(txd_id)
{
    switch(txd_id)
    {
        case H_FOOR_HALLWAY..H_FOOR_GYM:
            return sizeof(FornitureTexture_Foor);
        case H_WALL_HALLWAY..H_WALL_GYM:
            return sizeof(FornitureTexture_Wall);
        case H_ROOF_HALLWAY..H_ROOF_GYM:
            return sizeof(FornitureTexture_Roof);
    }
    return -1;
}

GetMaxCountTextureGarage(txd_id)
{
    switch(txd_id)
    {
        case G_FOOR: return sizeof(FornitureTexture_Foor);
        case G_WALL: return sizeof(FornitureTexture_Wall);
        case G_ROOF: return sizeof(FornitureTexture_Roof);
    }
    return -1;
}

save_house_interior(houseId, ft_idx = -1, ft_value = -1)
{
    if(ft_idx == -1 && ft_value == -1)
    {
        static const int_setting_init[4][H_ALL_MAPPING] =
        {
            {0,-1,0,1,2,-1,-1,-1,-1,0,1,2,3,-1,-1,-1,-1,-1,0,0,-1,1,-1,-1,-1,-1,-1},
            {3,-1,-1,4,5,-1,-1,-1,-1,4,-1,5,6,-1,-1,-1,-1,-1,2,-1,-1,3,-1,-1,-1,-1,-1},
            {0,6,-1,7,8,0,0,-1,-1,12,12,7,8,10,11,12,-1,-1,0,4,5,6,7,8,9,-1,-1},
            {10,-1,-1,11,12,-1,13,10,14,13,-1,8,14,-1,-1,15,16,17,-1,-1,-1,-1,-1,-1,-1,10,0}
        };
        STRING_GLOBAL[0] = EOS;
        for(new i; i < H_ALL_MAPPING; i++)
        {
            h_info[houseId][h_mapping_id][i] = int_setting_init[h_info[houseId][h_squar]-1][i];
            f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, h_info[houseId][h_mapping_id][i], i == H_ALL_MAPPING-1 ? "":"|");
        }

        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `house` SET `h_mapping_id` = '%s' WHERE `h_mysql_id` = %d",
        STRING_GLOBAL, h_info[houseId][h_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        House_Repair(houseId);
        return 1;
    }
    if(ft_idx == -1 || ft_value == -1) return 1;
    h_info[houseId][h_mapping_id][ft_idx] = ft_value;

    STRING_GLOBAL[0] = EOS;
    for(new i; i < H_ALL_MAPPING; i++)
    {
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, h_info[houseId][h_mapping_id][i], i == H_ALL_MAPPING-1 ? "":"|");
    }
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `house` SET `h_mapping_id` = '%s' WHERE `h_mysql_id` = %d",
    STRING_GLOBAL, h_info[houseId][h_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

save_garage_interior(houseId, ft_idx = -1, ft_value = -1)
{
    if(h_info[houseId][h_squar] == 1) return 1;
    if(ft_idx == -1 && ft_value == -1)
    {
        static const int_setting_init[3][G_ALL_MAPPING] =
        {
            {15,18,11},
            {16,19,12},
            {7,20,12}
        };
        STRING_GLOBAL[0] = EOS;
        new h_class = h_info[houseId][h_squar]-2;
        for(new i; i < G_ALL_MAPPING; i++)
        {
            h_info[houseId][h_garage_id][i] = int_setting_init[h_class][i];
            f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, h_info[houseId][h_garage_id][i], i == G_ALL_MAPPING-1 ? "":"|");
        }

        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `house` SET `h_garage_id` = '%s' WHERE `h_mysql_id` = %d",
        STRING_GLOBAL, h_info[houseId][h_mysql_id]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        Garage_Repair(houseId);
        return 1;
    }
    if(ft_idx == -1 || ft_value == -1) return 1;
    h_info[houseId][h_garage_id][ft_idx] = ft_value;

    STRING_GLOBAL[0] = EOS;
    for(new i; i < G_ALL_MAPPING; i++)
    {
        f(STRING_GLOBAL, "%s%i%s", STRING_GLOBAL, h_info[houseId][h_garage_id][i], i == G_ALL_MAPPING-1 ? "":"|");
    }
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `house` SET `h_garage_id` = '%s' WHERE `h_mysql_id` = %d",
    STRING_GLOBAL, h_info[houseId][h_mysql_id]);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}
///////////////////////////////////////////////////////////
CMD:shg(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    new house_id, new_price, new_class, Float:pX, Float:pY, Float:pZ, Float:pAng;
    if(sscanf(params, "iii", house_id, new_class, new_price)) return SendInfo(playerid, "Используйте: /sethousegarage [id дома] [класс: -1] [стоимость: -1]");
    if(house_id < 0 || house_id > totalhouses) return 1;
    if(h_info[house_id][h_mysql_id] == INVALID_MYSQL_ID) return SendError(playerid, "Дом не задействован.");
    GetPlayerPos(playerid,pX,pY,pZ);
    GetPlayerFacingAngle(playerid, pAng);

    h_info[house_id][h_garage_enter][0] = pX;
    h_info[house_id][h_garage_enter][1] = pY;
    h_info[house_id][h_garage_enter][2] = pZ;
    h_info[house_id][h_garage_enter][3] = pAng;

    if(new_class != -1) h_info[house_id][h_squar] = new_class;
    if(new_price != -1) h_info[house_id][h_value] = new_price;

    save_house(house_id);
    update_house(house_id);

    SendAccess(playerid, "Вы изменили настройки гаража.");
    return 1;
}

//////////////////////////////////////////////////////////////////////////////////
// gate house system
CheckHouseGate()
{
    new idx;
    for(new i = totalgatehouse-1; i != -1; i--)
    {
        idx = gate_house_idx[i];
        if(h_info[idx][h_gate] == INVALID_OBJECT_ID || h_info[idx][h_gate_timer] < 1) continue;
        h_info[idx][h_gate_timer]--;
        if(h_info[idx][h_gate_timer] < 1) MoveDynamicObject(h_info[idx][h_gate], h_info[idx][h_gate_pos][0], h_info[idx][h_gate_pos][1], h_info[idx][h_gate_pos][2], 0.6, 0.00, 0.00, h_info[idx][h_gate_pos][3]);
    }
}

SearchHouseGate(playerid)
{
	new idx;
    for(new i = totalgatehouse-1; i != -1; i--)
    {
        idx = gate_house_idx[i];
		if(IsPlayerInRangeOfPoint(playerid, 7.5, h_info[idx][h_gate_pos][0], h_info[idx][h_gate_pos][1], h_info[idx][h_gate_pos][2]))
		{
			if(IsKeyHouseDoor(playerid, idx) == 1)
			{
				if(h_info[idx][h_gate_timer] > 0) return SendError(playerid, "ворота уже открыты.");
				MoveDynamicObject(h_info[idx][h_gate], h_info[idx][h_gate_pos][0], h_info[idx][h_gate_pos][1], h_info[idx][h_gate_pos][2]-3.0, 0.6, 0.00, 0.00, h_info[idx][h_gate_pos][3]);
				h_info[idx][h_gate_timer] = 10;
				SendAccess(playerid, "Вы открыли ворота, они закроются через 10 сек.", h_info[idx][h_gate_timer]);
				break;
			}
			else return SendError(playerid, "У Вас нет возможности открыть эти ворота.");
		}
	}
	return 1;
}

CMD:hgate(playerid, params[])
{
    SearchHouseGate(playerid);
    return 1;
}

CMD:faminv(playerid)
{
    if(IsTDVisible(playerid) != -1) return 1;
    new family_idx = GetPlayerFamilyID(playerid);
    if(p_info[playerid][family_id] == -1 || family_idx == -1)
        return SendError(playerid, "Вы не состоите в семьи.");
    if(FamilyData[family_idx][fHouseID] == INVALID_HOUSE_ID || FamilyData[family_idx][fHouseID]+50 != GetPlayerVirtualWorld(playerid))
        return SendError(playerid, "Инвентарь можно использовать только в доме семьи.");

    new houseId = p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
    if(houseId == INVALID_HOUSE_ID)
        return SendError(playerid, "Код ошибки: 0999 (Обратитесь к администрации)");

    if(houseId+50 != GetPlayerVirtualWorld(playerid))
        return SendError(playerid, "Инвентарь можно использовать только в доме семьи.");

    if(GetFamilyRang(playerid) < FamilyData[family_idx][fSettingRang][F_INVENTORY])
        return SendError(playerid, "Инвентарь доступен с %d ранга.", FamilyData[family_idx][fSettingRang][F_INVENTORY]);

    ShowTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
    Interface_Show(playerid, EQUIPMENT_INVENTORY_FAMILY);
    return 1;
}
alias:faminv("finv", "familyinv", "invfamily", "invfam");

CMD:invhouse(playerid)
{
    if(IsTDVisible(playerid) != -1) return 1;
    new houseId = p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
    if(houseId == INVALID_HOUSE_ID)
        return SendError(playerid, "Код ошибки: 0998 (Обратитесь к администрации)");
    if(h_info[houseId][h_user_id] != p_info[playerid][ID])
        return SendError(playerid, "Вы не владелец дома.");
    if(houseId+50 != GetPlayerVirtualWorld(playerid))
        return SendError(playerid, "Пользоваться инвентарем дома можно только находясь в нём.");
    if(p_info[playerid][key_h_rent] != -1)
        return SendError(playerid, "Пользоваться инвентарем дома может только его владелец и семья.");
    
    ShowTextDrawForPlayer(playerid, TD_ID_INVENTORY_OTHER);
    Interface_Show(playerid, EQUIPMENT_INVENTORY_HOUSE);
    return 1;
}

CMD:returnhouse(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 7) return 1;

    if(isnull(params))
        return SendInfo(playerid, "Используйте: /returnhouse [id дома]");

    new
        houseId = strval(params);

    if(!(0 <= houseId < totalhouses) || h_info[houseId][h_mysql_id] == INVALID_MYSQL_ID || h_info[houseId][h_delete] == 0)
        return SendError(playerid, "Неверный ID дома.");

    h_info[houseId][h_delete] = 0;
    h_info[houseId][h_delete_time] = 0;
    update_house(houseId);

    SendAccess(playerid, "Вы вернули дом.");
    return 1;
}