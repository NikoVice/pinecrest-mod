
OnPlayerUpdateVehicleSpeed(playerid)
{
    new vehicleid = GetPlayerVehicleID(playerid);
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && p_temp[playerid][TextDrawSpeedometr])
    {
        new str[128], car_speed = GetVehicleSpeed(vehicleid);
        // Скорость;
        if(p_info[playerid][p_carlimit] != 0 && car_speed > p_info[playerid][p_carlimit]) format(str, sizeof(str), "%d", p_info[playerid][p_carlimit]);
        else format(str, sizeof(str), "%d", car_speed);
        // Топливо;
        if(p_info[playerid][p_settings][INTERFACE] == 1) PlayerTextDrawSetString(playerid, PTD_NewSpeedometer[playerid][6], str);
        else PlayerTextDrawSetString(playerid, PTD_SpeedometerInfo[playerid][1], str);

        if(p_info[playerid][p_settings][INTERFACE] == 1)
        {
            format(str, sizeof(str), "%0.1f L.", veh_info[vehicleid][v_fuel]);
            PlayerTextDrawSetString(playerid, PTD_NewSpeedometer[playerid][7], str);

            new Float:veh_health;
            GetVehicleHealth(vehicleid, veh_health);
            format(str, sizeof(str), "%0.1f%", veh_health/10);
            PlayerTextDrawSetString(playerid, PTD_NewSpeedometer[playerid][8], str);
            /*
            5 = speed
            9 = fuel
            10 = health
            */
            if(PTD_NewSpeedometer[playerid][5] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][5]);
            if(PTD_NewSpeedometer[playerid][9] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][9]);
            if(PTD_NewSpeedometer[playerid][10] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][10]);
            ///////////////////////////////////////////////////////////////////////
            if(car_speed >= 1 && car_speed <= 20) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s1");
            else if(car_speed >= 21 && car_speed <= 40) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s2");
            else if(car_speed >= 41 && car_speed <= 55) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s3");
            else if(car_speed >= 56 && car_speed <= 70) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s4");
            else if(car_speed >= 71 && car_speed <= 85) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s5");
            else if(car_speed >= 86 && car_speed <= 100) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s6");
            else if(car_speed >= 101 && car_speed <= 120) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s7");
            else if(car_speed >= 121 && car_speed <= 140) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s8");
            else if(car_speed >= 141 && car_speed <= 180) PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s9");
            else PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s10");

            PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][5], 90.669960, 116.840034);
            PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][5], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][5], 4);
            PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][5], 0);

            if(car_speed >= 1) PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][5]);
            ////////////////////////////////////////////////////////////////////////////////
            new veh_fuel = floatround(veh_info[vehicleid][v_fuel]);
            if(veh_fuel > 0) veh_fuel = (veh_fuel*100)/GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_MAX_FUEL);
            if(veh_fuel >= 1 && veh_fuel <= 10) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f1");
            else if(veh_fuel >= 11 && veh_fuel <= 25) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f2");
            else if(veh_fuel >= 26 && veh_fuel <= 39) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f3");
            else if(veh_fuel >= 40 && veh_fuel <= 49) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f4");
            else if(veh_fuel >= 50 && veh_fuel <= 59) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f5");
            else if(veh_fuel >= 60 && veh_fuel <= 69) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f6");
            else if(veh_fuel >= 70 && veh_fuel <= 79) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f7");
            else if(veh_fuel >= 80 && veh_fuel <= 89) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f8");
            else if(veh_fuel >= 90 && veh_fuel <= 99) PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f9");
            else PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f10");

            PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][9], 102.150024, 131.000000);
            PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][9], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][9], 255);
            PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][9], 4);
            PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][9], 0);

            if(veh_fuel > 1) PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][9]);
            /////////////////////////////////////////////////////////////////////////////////
            new iVeh_Health = floatround(veh_health/10);
            if(iVeh_Health >= 20 && iVeh_Health <= 35) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h1");
            else if(iVeh_Health >= 36 && iVeh_Health <= 45) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h2");
            else if(iVeh_Health >= 46 && iVeh_Health <= 55) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h3");
            else if(iVeh_Health >= 56 && iVeh_Health <= 65) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h4");
            else if(iVeh_Health >= 66 && iVeh_Health <= 75) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h5");
            else if(iVeh_Health >= 76 && iVeh_Health <= 85) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h6");
            else if(iVeh_Health >= 86 && iVeh_Health <= 89) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h7");
            else if(iVeh_Health >= 90 && iVeh_Health <= 95) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h8");
            else if(iVeh_Health >= 96 && iVeh_Health <= 99) PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h9");
            else PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h10");

            PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][10], 102.150024, 131.000000);
            PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][10], 1);
            PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][10], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][10], 255);
            PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][10], 4);
            PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][10], 0);

            if(iVeh_Health >= 31) PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][10]);
        }
        else
        {
            format(str, sizeof(str), "%0.1f", veh_info[vehicleid][v_fuel]);
            PlayerTextDrawSetString(playerid, PTD_SpeedometerInfo[playerid][15], str);
        }
    }
}

OnPlayerUpdateVehicleInfo(playerid, type)
{
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && p_temp[playerid][TextDrawSpeedometr])
    {
        new vehicleid = GetPlayerVehicleID(playerid);
        if(vehicleid < 0 || vehicleid >= MAX_VEHICLES) return 1;
        if(GetVehicleModelEx(vehicleid) == 0) return 1;
        if(GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_CAR ||
            GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_MOTO ||
            GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_TYPE) == VEHICLE_STATE_TRAIN ||
            veh_info[vehicleid][v_model] == 462 ||
            veh_info[vehicleid][v_model] == 448)
        {
            switch(type)
            {
                case SPEEDO_LIGHT:
                {
                    if(p_info[playerid][p_settings][INTERFACE] == 1)
                    {
                        if(PTD_NewSpeedometer[playerid][2] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][2]);
                        if(veh_info[vehicleid][v_light]) PTD_NewSpeedometer[playerid][2] = CreatePlayerTextDraw(playerid, 310.000000, 427.000000, "flinspeed:flin_lighton");
                        else PTD_NewSpeedometer[playerid][2] = CreatePlayerTextDraw(playerid, 310.000000, 427.000000, "flinspeed:flin_lightoff");
                        PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][2], 14.319993, 18.640005);
                        PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][2], 1);
                        PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][2], -1);
                        PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][2], 255);
                        PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][2], 4);
                        PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][2], 0);

                        PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][2]);
                    }
                    else
                    {
                        for(new i = 2; i <= 4; i++)
                        {
                            PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                            PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], veh_info[vehicleid][v_light] ? 1018626047 : -1);
                            PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                        }
                    }
                }
                case SPEEDO_DOORS:
                {
                    if(p_info[playerid][p_settings][INTERFACE] == 1)
                    {
                        if(PTD_NewSpeedometer[playerid][3] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][3]);
                        if(veh_info[vehicleid][v_lock]) PTD_NewSpeedometer[playerid][3] = CreatePlayerTextDraw(playerid, 334.000000, 427.000000, "flinspeed:flin_lock");
                        else PTD_NewSpeedometer[playerid][3] = CreatePlayerTextDraw(playerid, 334.000000, 427.000000, "flinspeed:flin_unlock");
                        PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][3], 14.319993, 18.640005);
                        PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][3], 1);
                        PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][3], -1);
                        PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][3], 255);
                        PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][3], 4);
                        PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][3], 0);

                        PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][3]);
                    }
                    else
                    {
                        for(new i = 5; i <= 6; i++)
                        {
                            PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                            PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], veh_info[vehicleid][v_lock] ? -1523963137 : -1);
                            PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                        }
                    }
                }
                case SPEEDO_LIMITE:
                {
                    if(p_info[playerid][p_settings][INTERFACE] == 1)
                    {
                        if(PTD_NewSpeedometer[playerid][1] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][1]);
                        if(p_info[playerid][p_carlimit]) PTD_NewSpeedometer[playerid][1] = CreatePlayerTextDraw(playerid, 286.000000, 427.000000, "flinspeed:flin_limiton");
                        else PTD_NewSpeedometer[playerid][1] = CreatePlayerTextDraw(playerid, 286.000000, 427.000000, "flinspeed:flin_limitoff");

                        PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][1], 14.319993, 18.640005);
                        PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][1], 1);
                        PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][1], -1);
                        PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][1], 255);
                        PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][1], 4);
                        PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][1], 0);

                        PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][1]);
                    }
                    else
                    {
                        for(new i = 7; i <= 8; i++)
                        {
                            PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                            PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], p_info[playerid][p_carlimit] != 0 ? -65281 : -1);
                            PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                        }
                    }
                }
                case SPEEDO_ENGINE:
                {
                    if(p_info[playerid][p_settings][INTERFACE] == 1)
                    {
                        if(PTD_NewSpeedometer[playerid][0] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][0]);
                        if(veh_info[vehicleid][v_engine]) PTD_NewSpeedometer[playerid][0] = CreatePlayerTextDraw(playerid, 260.000000, 427.000000, "flinspeed:flin_dashboardon");
                        else PTD_NewSpeedometer[playerid][0] = CreatePlayerTextDraw(playerid, 260.000000, 427.000000, "flinspeed:flin_dashboardoff");

                        PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][0], 14.319993, 18.640005);
                        PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][0], 1);
                        PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][0], -1);
                        PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][0], 255);
                        PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][0], 4);
                        PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][0], 0);

                        PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][0]);
                    }
                    else
                    {
                        for(new i = 9; i <= 11; i++)
                        {
                            PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                            PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], veh_info[vehicleid][v_engine] ? 8388863 : -1);
                            PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                        }
                    }
                }
                case SPEEDO_TWINTURBO:
                {
                    if(p_info[playerid][p_settings][INTERFACE] == 1)
                    {
                        if(PTD_NewSpeedometer[playerid][4] != PlayerText:INVALID_TEXT_DRAW) PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][4]);
                        if(p_temp[playerid][twinturbo_on]) PTD_NewSpeedometer[playerid][4] =  CreatePlayerTextDraw(playerid, 361.000000, 427.000000, "flinspeed:flin_turboon");
                        else PTD_NewSpeedometer[playerid][4] =  CreatePlayerTextDraw(playerid, 361.000000, 427.000000, "flinspeed:flin_turbooff");

                        PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][4], 14.319993, 18.640005);
                        PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][4], 1);
                        PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][4], -1);
                        PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][4], 255);
                        PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][4], 4);
                        PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][4], 0);

                        PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][4]);
                    }
                    else
                    {
                        for(new i = 12; i <= 14; i++)
                        {
                            PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
                            PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][i], p_temp[playerid][twinturbo_on] ? 8388863 : -1);
                            PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                        }
                    }
                }
            }
        }
    }
    return 1;
}
