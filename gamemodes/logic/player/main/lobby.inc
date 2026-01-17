CreateDefaultLobby(type, capacity, time, subject, map, device, pass)
{
    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1)
        {
            LobbyInfo[i][LobbyCreateID] = -1;
            LobbyInfo[i][LobbyType] = type;
            LobbyInfo[i][LobbyCapacity] = capacity;
            LobbyInfo[i][LobbyTime] = time;
            LobbyInfo[i][LobbySubject] = subject;
            LobbyInfo[i][LobbyMap] = map;
            LobbyInfo[i][LobbyDevice] = device;
            LobbyInfo[i][LobbyPassword] = pass;

            for(new idx = 0; idx < MAX_PLAYERS_LOBBY; idx++)
            {
                LobbyInfo[i][LobbyPlayers][idx] = INVALID_PLAYER_ID;
                LobbyInfo[i][LobbyKills][idx] = 0;
                LobbyInfo[i][LobbyDeaths][idx] = 0;
                LobbyInfo[i][LobbyVehicles][idx] = INVALID_VEHICLE_ID;
            }
            return 1;
        }
    }
    return 1;
}

CreateLobby(playerid, type, capacity, time, subject, map, device, pass)
{
    if(p_info[playerid][level] < MIN_LEVEL_ENTER_LOBBY) return SendError(playerid, "У Вас нет %d-го уровня.", MIN_LEVEL_CREATE_LOBBY);

    if(player_lobby_status[playerid] != false || player_lobby_idx[playerid] != -1) return SendError(playerid, "Вы уже находитесь в лобби.");

    if(device == 0 && !IsPlayerMobile(playerid)) return SendError(playerid, "Вы не можете создать лобби для игроков с мобильных устройств.");
    if(device == 1 && IsPlayerMobile(playerid)) return SendError(playerid, "Вы не можете создать лобби для игроков с персонального компьютера.");

    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1)
        {
            LobbyInfo[i][LobbyCreateID] = playerid;
            LobbyInfo[i][LobbyType] = type;
            LobbyInfo[i][LobbyCapacity] = capacity;
            LobbyInfo[i][LobbyTime] = time;
            LobbyInfo[i][LobbySubject] = subject;
            LobbyInfo[i][LobbyMap] = map;
            LobbyInfo[i][LobbyDevice] = device;
            LobbyInfo[i][LobbyPassword] = pass;

            for(new idx = 0; idx < MAX_PLAYERS_LOBBY; idx++)
            {
                LobbyInfo[i][LobbyPlayers][idx] = INVALID_PLAYER_ID;
                LobbyInfo[i][LobbyKills][idx] = 0;
                LobbyInfo[i][LobbyDeaths][idx] = 0;
                LobbyInfo[i][LobbyVehicles][idx] = INVALID_VEHICLE_ID;
            }

            SendAccess(playerid, "Вы создали лобби.");
            SendInfo(playerid, "Тип: %s, Вместимость: %d, Время: %s, Параметр: %d, Карта: %s, Устройство: %s, Пароль: %d", LobbyTypeName[type - 1], capacity, ConvertTime(time, 1), subject, LobbyMapName[type - 1][map], LobbyDeviceName[device], pass);

            SetPlayerFreeSlotLobby(playerid, i);
            return 1;
        }
    }
    SendError(playerid, "В данный момент нет свободных мест для создания лобби.");
    return 1;
}

ClearLobby(idx, text[])
{
    for(new i = 0; i < MAX_PLAYERS_LOBBY; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] != INVALID_PLAYER_ID)
        {
            switch(LobbyInfo[idx][LobbyType])
            {
                case LOBBY_TYPE_DEATHMATCH, LOBBY_TYPE_RACE, LOBBY_TYPE_DERBY, LOBBY_TYPE_STUNT, LOBBY_TYPE_PARKOUR:
                {
                    ResetPlayerWeapons(LobbyInfo[idx][LobbyPlayers][i]);
                    for(new a = 0; a < MAX_WEAPONS; a++) GivePlayerWeapon(LobbyInfo[idx][LobbyPlayers][i], p_info[LobbyInfo[idx][LobbyPlayers][i]][Weapon][a], p_info[LobbyInfo[idx][LobbyPlayers][i]][Ammo][a]);
                    SetPlayerArmedWeapon(LobbyInfo[idx][LobbyPlayers][i], 0);
                }
            }
            SendInfo(LobbyInfo[idx][LobbyPlayers][i], "Лобби удалено. Причина: %s", text);

            if(LobbyInfo[idx][LobbyType] == LOBBY_TYPE_PARKOUR) SetPlayerSkinEx(LobbyInfo[idx][LobbyPlayers][i]);
            SetPlayerInterior(LobbyInfo[idx][LobbyPlayers][i], 0);
            SetPlayerVirtualWorld(LobbyInfo[idx][LobbyPlayers][i], 0);
            SetPlayerPos(LobbyInfo[idx][LobbyPlayers][i], 1421.7180,-1623.7816,13.5469);
            SetPlayerFacingAngle(LobbyInfo[idx][LobbyPlayers][i], 270.0);
            SetCameraBehindPlayer(LobbyInfo[idx][LobbyPlayers][i]);
            if((p_info[LobbyInfo[idx][LobbyPlayers][i]][member] != 0 && p_info[LobbyInfo[idx][LobbyPlayers][i]][fwork] == true)) SetPlayerColor(LobbyInfo[idx][LobbyPlayers][i], fraction_color[p_info[LobbyInfo[idx][LobbyPlayers][i]][member]]);
            else SetPlayerColor(LobbyInfo[idx][LobbyPlayers][i],  fraction_color[0]);
            if(p_info[LobbyInfo[idx][LobbyPlayers][i]][admin] > 0) SetPlayerColor(LobbyInfo[idx][LobbyPlayers][i], 0xFFFFFF00);
            ClearDeathMessage(LobbyInfo[idx][LobbyPlayers][i]);

            player_lobby_status[LobbyInfo[idx][LobbyPlayers][i]] = false;
            player_lobby_type[LobbyInfo[idx][LobbyPlayers][i]] = -1;
            player_lobby_idx[LobbyInfo[idx][LobbyPlayers][i]] = -1;
        }

        if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID) DestroyVehicleVEx(LobbyInfo[idx][LobbyVehicles][i]);

        LobbyInfo[idx][LobbyPlayers][i] = INVALID_PLAYER_ID;
        LobbyInfo[idx][LobbyKills][i] = 0;
        LobbyInfo[idx][LobbyDeaths][i] = 0;
        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
    }

    LobbyInfo[idx][LobbyCreateID] = INVALID_PLAYER_ID;
    LobbyInfo[idx][LobbyType] = 0;
    LobbyInfo[idx][LobbyCapacity] = 0;
    LobbyInfo[idx][LobbyTime] = 0;
    LobbyInfo[idx][LobbySubject] = 0;
    LobbyInfo[idx][LobbyMap] = 0;
    LobbyInfo[idx][LobbyDevice] = 0;
    LobbyInfo[idx][LobbyPassword] = 0;
    return 1;
}

CheckLobby()
{
    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1) continue;

        if(LobbyInfo[i][LobbyTime] > 0) LobbyInfo[i][LobbyTime]--;
        if(LobbyInfo[i][LobbyTime] == 0) ClearLobby(i, "Закончилось время лобби.");
    }
    return 1;
}

GetFreeSlotLobby(idx)
{
    new slot = 0;
    for(new i = 0; i < LobbyInfo[idx][LobbyCapacity]; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] == INVALID_PLAYER_ID)
        {
            slot++;
        }
    }
    return slot;
}

SetPlayerFreeSlotLobby(playerid, idx)
{
    if(p_info[playerid][level] < MIN_LEVEL_ENTER_LOBBY) return SendError(playerid, "У Вас нет %d-го уровня.", MIN_LEVEL_ENTER_LOBBY);

    if(player_lobby_status[playerid] != false || player_lobby_idx[playerid] != -1) return SendError(playerid, "Вы уже находитесь в лобби.");

    if(LobbyInfo[idx][LobbyDevice] == 0 && !IsPlayerMobile(playerid)) return SendError(playerid, "Данное лобби доступно только для игроков с мобильных устройств.");
    if(LobbyInfo[idx][LobbyDevice] == 1 && IsPlayerMobile(playerid)) return SendError(playerid, "Данное лобби доступно только для игроков с персонального компьютера.");

    for(new i = 0; i < LobbyInfo[idx][LobbyCapacity]; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] == INVALID_PLAYER_ID)
        {
            p_temp[playerid][TickPickup] = GetTickCount();
            switch(LobbyInfo[idx][LobbyType])
            {
                case LOBBY_TYPE_DEATHMATCH:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Вы вошли в лобби %s [%d].", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Вы вошли в стандартное лобби.");
                    SendInfo(playerid, "Тип: %s, Вместимость: %d, Время: %s, Параметр: %d, Карта: %s, Устройство: %s, Пароль: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Для просмотра статистики используйте: /lobbystats");
                    SendInfo(playerid, "Для выхода из лобби используйте: /lobbyexit");

                    ResetPlayerWeapons(playerid);
                    new sidx = random(20), type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[5] = {1, 1, 0, 0, 0};
                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx + 1);
                    SetPlayerPos(playerid, LobbyPos[type][map][sidx][0], LobbyPos[type][map][sidx][1], LobbyPos[type][map][sidx][2]);
                    SetPlayerFacingAngle(playerid, LobbyPos[type][map][sidx][3]);
                    SetCameraBehindPlayer(playerid);
                    p_info[playerid][pHealth] = 100.0;
                    SetPlayerHealth(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);
                    GivePlayerWeapon(playerid, LobbyInfo[idx][LobbySubject], 9999);

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_DEATHMATCH;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_RACE:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID)
                    {
                        DestroyVehicleVEx(LobbyInfo[idx][LobbyVehicles][i]);
                        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
                    }

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Вы вошли в лобби %s [%d].", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Вы вошли в стандартное лобби.");
                    SendInfo(playerid, "Тип: %s, Вместимость: %d, Время: %s, Параметр: %d, Карта: %s, Устройство: %s, Пароль: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Для выхода из лобби используйте: /lobbyexit");

                    new type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[3] = {7, 4, 1};

                    new vehicleid = CreateVehicleVEx(NPO_LOBBY, NPO_NONE, LobbyInfo[idx][LobbySubject], LobbyPos[type][map][i][0], LobbyPos[type][map][i][1], LobbyPos[type][map][i][2], LobbyPos[type][map][i][3], 1, 1, 120);

                    ResetPlayerWeapons(playerid);
                    p_info[playerid][pHealth] = 100.0;
                    SetPlayerHealth(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    LinkVehicleToInterior(vehicleid, interior_map[map]);
                    SetVehicleVirtualWorld(vehicleid, idx);

                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx);

                    veh_info[vehicleid][v_lock] = 1;
                    veh_info[vehicleid][v_color] = 1;
                    veh_info[vehicleid][v_model] = LobbyInfo[idx][LobbySubject];
                    veh_info[vehicleid][v_fuel] = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_MAX_FUEL);
                    for(new sidx; sidx < 5; sidx++) veh_info[vehicleid][v_details][sidx] = 100.0;
                    format(veh_info[vehicleid][v_number], 16, "NULL");
                    veh_info[vehicleid][v_int] =
                    veh_info[vehicleid][v_virt] =
                    veh_info[vehicleid][v_insurance] = 0;
                    veh_info[vehicleid][v_rented_ID] = p_info[playerid][ID];
                    veh_info[vehicleid][v_used_key_ID] = playerid;

                    PutPlayerInVehicle(playerid, vehicleid, 0);

                    veh_info[vehicleid][v_engine] = 1;
                    OnPlayerUpdateVehicleInfo(playerid, SPEEDO_ENGINE);

                    LobbyInfo[idx][LobbyVehicles][i] = vehicleid;

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_RACE;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_DERBY:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID)
                    {
                        DestroyVehicleVEx(LobbyInfo[idx][LobbyVehicles][i]);
                        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
                    }

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Вы вошли в лобби %s [%d].", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Вы вошли в стандартное лобби.");
                    SendInfo(playerid, "Тип: %s, Вместимость: %d, Время: %s, Параметр: %d, Карта: %s, Устройство: %s, Пароль: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Для выхода из лобби используйте: /lobbyexit");

                    new type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[3] = {15, 0, 0};

                    new vehicleid = CreateVehicleVEx(NPO_LOBBY, NPO_NONE, LobbyInfo[idx][LobbySubject], LobbyPos[type][map][i][0], LobbyPos[type][map][i][1], LobbyPos[type][map][i][2], LobbyPos[type][map][i][3], 1, 1, 120);

                    ResetPlayerWeapons(playerid);
                    p_info[playerid][pHealth] = 100.0;
                    SetPlayerHealth(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    LinkVehicleToInterior(vehicleid, interior_map[map]);
                    SetVehicleVirtualWorld(vehicleid, idx);

                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx);

                    veh_info[vehicleid][v_lock] = 1;
                    veh_info[vehicleid][v_color] = 1;
                    veh_info[vehicleid][v_model] = LobbyInfo[idx][LobbySubject];
                    veh_info[vehicleid][v_fuel] = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_MAX_FUEL);
                    for(new sidx; sidx < 5; sidx++) veh_info[vehicleid][v_details][sidx] = 100.0;
                    format(veh_info[vehicleid][v_number], 16, "NULL");
                    veh_info[vehicleid][v_int] =
                    veh_info[vehicleid][v_virt] =
                    veh_info[vehicleid][v_insurance] = 0;
                    veh_info[vehicleid][v_rented_ID] = p_info[playerid][ID];
                    veh_info[vehicleid][v_used_key_ID] = playerid;

                    PutPlayerInVehicle(playerid, vehicleid, 0);

                    veh_info[vehicleid][v_engine] = 1;
                    OnPlayerUpdateVehicleInfo(playerid, SPEEDO_ENGINE);

                    LobbyInfo[idx][LobbyVehicles][i] = vehicleid;

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_DERBY;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_STUNT:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID)
                    {
                        DestroyVehicleVEx(LobbyInfo[idx][LobbyVehicles][i]);
                        LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
                    }

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Вы вошли в лобби %s [%d].", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Вы вошли в стандартное лобби.");
                    SendInfo(playerid, "Тип: %s, Вместимость: %d, Время: %s, Параметр: %d, Карта: %s, Устройство: %s, Пароль: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Для выхода из лобби используйте: /lobbyexit");

                    new type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap], interior_map[3] = {14, 0, 0};

                    new vehicleid = CreateVehicleVEx(NPO_LOBBY, NPO_NONE, LobbyInfo[idx][LobbySubject], LobbyPos[type][map][i][0], LobbyPos[type][map][i][1], LobbyPos[type][map][i][2], LobbyPos[type][map][i][3], 1, 1, 120);

                    ResetPlayerWeapons(playerid);
                    p_info[playerid][pHealth] = 100.0;
                    SetPlayerHealth(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    LinkVehicleToInterior(vehicleid, interior_map[map]);
                    SetVehicleVirtualWorld(vehicleid, idx);

                    SetPlayerInterior(playerid, interior_map[map]);
                    SetPlayerVirtualWorld(playerid, idx);

                    veh_info[vehicleid][v_lock] = 1;
                    veh_info[vehicleid][v_color] = 1;
                    veh_info[vehicleid][v_model] = LobbyInfo[idx][LobbySubject];
                    veh_info[vehicleid][v_fuel] = GetVehicleData(GetVehicleModelEx(vehicleid), E_VD_MAX_FUEL);
                    for(new sidx; sidx < 5; sidx++) veh_info[vehicleid][v_details][sidx] = 100.0;
                    format(veh_info[vehicleid][v_number], 16, "NULL");
                    veh_info[vehicleid][v_int] =
                    veh_info[vehicleid][v_virt] =
                    veh_info[vehicleid][v_insurance] = 0;
                    veh_info[vehicleid][v_rented_ID] = p_info[playerid][ID];
                    veh_info[vehicleid][v_used_key_ID] = playerid;

                    PutPlayerInVehicle(playerid, vehicleid, 0);

                    veh_info[vehicleid][v_engine] = 1;
                    OnPlayerUpdateVehicleInfo(playerid, SPEEDO_ENGINE);

                    LobbyInfo[idx][LobbyVehicles][i] = vehicleid;

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_STUNT;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                case LOBBY_TYPE_PARKOUR:
                {
                    LobbyInfo[idx][LobbyPlayers][i] = playerid;

                    if(LobbyInfo[idx][LobbyCreateID] != -1) SendAccess(playerid, "Вы вошли в лобби %s [%d].", get_name(LobbyInfo[idx][LobbyCreateID]), LobbyInfo[idx][LobbyCreateID]);
                    else SendAccess(playerid, "Вы вошли в стандартное лобби.");
                    SendInfo(playerid, "Тип: %s, Вместимость: %d, Время: %s, Параметр: %d, Карта: %s, Устройство: %s, Пароль: %d", LobbyTypeName[LobbyInfo[idx][LobbyType] - 1], LobbyInfo[idx][LobbyCapacity], ConvertTime(LobbyInfo[idx][LobbyTime], 1), LobbyInfo[idx][LobbySubject], LobbyMapName[LobbyInfo[idx][LobbyType] - 1][LobbyInfo[idx][LobbyMap]], LobbyDeviceName[LobbyInfo[idx][LobbyDevice]], LobbyInfo[idx][LobbyPassword]);
                    SendInfo(playerid, "Для выхода из лобби используйте: /lobbyexit");

                    ResetPlayerWeapons(playerid);
                    new sidx = random(20), type = LobbyInfo[idx][LobbyType] - 1, map = LobbyInfo[idx][LobbyMap];
                    SetPlayerSkin(playerid, LobbyInfo[idx][LobbySubject]);
                    SetPlayerInterior(playerid, 0);
                    SetPlayerVirtualWorld(playerid, idx);
                    SetPlayerPos(playerid, LobbyPos[type][map][sidx][0], LobbyPos[type][map][sidx][1], LobbyPos[type][map][sidx][2]);
                    SetPlayerFacingAngle(playerid, LobbyPos[type][map][sidx][3]);
                    SetCameraBehindPlayer(playerid);
                    p_info[playerid][pHealth] = 100.0;
                    SetPlayerHealth(playerid, 100.0);
                    SetPlayerColor(playerid, 0xFF0000FF);

                    player_lobby_status[playerid] = true;
                    player_lobby_type[playerid] = LOBBY_TYPE_PARKOUR;
                    player_lobby_idx[playerid] = idx;
                    return 1;
                }
                default: return 1;
            }
        }
    }
    SendError(playerid, "В данном лобби нет свободных мест.");
    return 1;
}

ShowLobby(playerid)
{
    ShowPlayerDialog(playerid, D_LOBBY, DIALOG_STYLE_LIST, ""I"Лобби", ""I"[1]"W" Список лобби\n"I"[2]"W" Создать лобби", "Далее", "Отмена");
    return 1;
}

ShowLobbyList(playerid)
{
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    for(new i = 0; i < sizeof(LobbyTypeName); i++)
    {
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\n", i + 1, LobbyTypeName[i]);
        strcat(STRING_GLOBAL, STRING_MIN);
    }
    ShowPlayerDialog(playerid, D_LOBBY_LIST, DIALOG_STYLE_LIST, ""I"Список лобби", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

ShowLobbyCreatedList(playerid, type)
{
    new count;
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    for(new i = 0; i < MAX_LOBBY; i++)
    {
        if(LobbyInfo[i][LobbyCreateID] == INVALID_PLAYER_ID && LobbyInfo[i][LobbyCreateID] != -1) continue;
        if(LobbyInfo[i][LobbyType] != type) continue;

        switch(type)
        {
            case LOBBY_TYPE_DEATHMATCH:
            {
                if(count == 0) STRING_GLOBAL = "[#] Creator [ID] - Map\tWeapon Name\tFree Slot\tTime\n";
                if(LobbyInfo[i][LobbyCreateID] != -1) format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [%d] - %s\t%s\t%d\t%s\n", count + 1, get_name(LobbyInfo[i][LobbyCreateID]), LobbyInfo[i][LobbyCreateID], LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], WEAPON_Name[LobbyInfo[i][LobbySubject]], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                else format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" Server - %s\t%s\t%d\t%s\n", count + 1, LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], WEAPON_Name[LobbyInfo[i][LobbySubject]], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            case LOBBY_TYPE_RACE, LOBBY_TYPE_DERBY, LOBBY_TYPE_STUNT:
            {
                if(count == 0) STRING_GLOBAL = "[#] Creator [ID] - Map\tVehicle Name\tFree Slot\tTime\n";
                if(LobbyInfo[i][LobbyCreateID] != -1) format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [%d] - %s\t%s\t%d\t%s\n", count + 1, get_name(LobbyInfo[i][LobbyCreateID]), LobbyInfo[i][LobbyCreateID], LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], GetVehicleName(INVALID_VEHICLE_ID, LobbyInfo[i][LobbySubject]), GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                else format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" Server - %s\t%s\t%d\t%s\n", count + 1, LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], GetVehicleName(INVALID_VEHICLE_ID, LobbyInfo[i][LobbySubject]), GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            case LOBBY_TYPE_PARKOUR:
            {
                if(count == 0) STRING_GLOBAL = "[#] Creator [ID] - Map]\tSkin\tFree Slot\tTime\n";
                if(LobbyInfo[i][LobbyCreateID] != -1) format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [%d] - %s\t%d\t%d\t%s\n", count + 1, get_name(LobbyInfo[i][LobbyCreateID]), LobbyInfo[i][LobbyCreateID], LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], LobbyInfo[i][LobbySubject], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                else format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" Server - %s\t%d\t%d\t%s\n", count + 1, LobbyMapName[type - 1][LobbyInfo[i][LobbyMap]], LobbyInfo[i][LobbySubject], GetFreeSlotLobby(i), ConvertTime(LobbyInfo[i][LobbyTime], 1));
                strcat(STRING_GLOBAL, STRING_MIN);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
        }
    }
    if(!count) return ShowLobbyList(playerid), SendError(playerid, "Не найдено созданных лобби данного типа.");
    STRING_MIN[0] = EOS;
    format(STRING_MIN, sizeof(STRING_MIN), ""I"%s", LobbyTypeName[type - 1]);
    ShowPlayerDialog(playerid, D_LOBBY_CREATED_LIST, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

ShowLobbyCreate(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "\
    "I"[1]"W" Тип:\t%s\n\
    "I"[2]"W" Вместимость:\t%d\n\
    "I"[3]"W" Время:\t%s\n\
    "I"[4]"W" Параметр:\t%d\n\
    "I"[5]"W" Карта:\t%s\n\
    "I"[6]"W" Устройство:\t%s\n\
    "I"[7]"W" Пароль:\t%d\n\
    "I"[8]"W" Создать",
    LobbyTypeName[player_lobby_settings[playerid][0]],
    player_lobby_settings[playerid][1],
    ConvertTime(player_lobby_settings[playerid][2], 1),
    player_lobby_settings[playerid][3],
    LobbyMapName[player_lobby_settings[playerid][0]][player_lobby_settings[playerid][4]],
    LobbyDeviceName[player_lobby_settings[playerid][5]],
    player_lobby_settings[playerid][6]);
    ShowPlayerDialog(playerid, D_LOBBY_CREATE, DIALOG_STYLE_TABLIST, ""I"Создание лобби", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

OnPlayerLeaveLobby(playerid, idx, text[])
{
    if(LobbyInfo[idx][LobbyCreateID] == playerid) ClearLobby(idx, "Создатель лобби вышел из него.");
    else
    {
        for(new i = 0; i < MAX_PLAYERS_LOBBY; i++)
        {
            if(LobbyInfo[idx][LobbyPlayers][i] == playerid)
            {
                LobbyInfo[idx][LobbyPlayers][i] = INVALID_PLAYER_ID;
                LobbyInfo[idx][LobbyKills][i] = 0;
                LobbyInfo[idx][LobbyDeaths][i] = 0;
                if(LobbyInfo[idx][LobbyVehicles][i] != INVALID_VEHICLE_ID) DestroyVehicleVEx(LobbyInfo[idx][LobbyVehicles][i]);
                LobbyInfo[idx][LobbyVehicles][i] = INVALID_VEHICLE_ID;
            }
        }
    }

    if(LobbyInfo[idx][LobbyType] == LOBBY_TYPE_PARKOUR) SetPlayerSkinEx(playerid);
    SetPlayerInterior(playerid, 0);
    SetPlayerVirtualWorld(playerid, 0);
    SetPlayerPos(playerid, 1421.7180,-1623.7816,13.5469);
    SetPlayerFacingAngle(playerid, 270.0);
    SetCameraBehindPlayer(playerid);
    if((p_info[playerid][member] != 0 && p_info[playerid][fwork] == true)) SetPlayerColor(playerid, fraction_color[p_info[playerid][member]]);
    else SetPlayerColor(playerid,  fraction_color[0]);
    if(p_info[playerid][admin] > 0) SetPlayerColor(playerid, 0xFFFFFF00);
    ClearDeathMessage(playerid);

    SendInfo(playerid, "Вы вышли из лобби. Причина: %s", text);

    player_lobby_status[playerid] = false;
    player_lobby_type[playerid] = -1;
    player_lobby_idx[playerid] = -1;

    ResetPlayerWeapons(playerid);
    for (new i; i < MAX_WEAPONS; i++) GivePlayerWeapon(playerid, p_info[playerid][Weapon][i], p_info[playerid][Ammo][i]);
    SetPlayerArmedWeapon(playerid, 0);

    SetPlayerHealth(playerid, 100.0);
    //SetPlayerArmour(playerid, p_info[playerid][pArmour]);
    return 1;
}

CMD:lobby(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    ShowLobby(playerid);
    return 1;
}

CMD:lobbystats(playerid, params[])
{
    if(player_lobby_status[playerid] == false || player_lobby_idx[playerid] == -1) return SendError(playerid, "Вы не в лобби.");
    new idx = player_lobby_idx[playerid], count;
    if(player_lobby_type[playerid] != LOBBY_TYPE_DEATHMATCH) return SendError(playerid, "Статистика доступна только на Deathmatch.");
    STRING_GLOBAL = "[#] Nickname [ID]\tKills\tDeaths\n", STRING_MIN[0] = EOS;
    for(new i = 0; i < MAX_PLAYERS_LOBBY; i++)
    {
        if(LobbyInfo[idx][LobbyPlayers][i] != INVALID_PLAYER_ID)
        {
            format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s [%d]\t%d\t%d\n",
            count + 1, get_name(LobbyInfo[idx][LobbyPlayers][i]), LobbyInfo[idx][LobbyPlayers][i], LobbyInfo[idx][LobbyKills][i], LobbyInfo[idx][LobbyDeaths][i]);
            strcat(STRING_GLOBAL, STRING_MIN);
            count++;
        }
    }
    if(count == 0) return SendError(playerid, "В лобби нет игроков.");
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Статистика лобби", STRING_GLOBAL, "Отмена", "");
    return 1;
}

CMD:lobbyexit(playerid, params[])
{
    if(player_lobby_status[playerid] == false || player_lobby_idx[playerid] == -1) return SendError(playerid, "Вы не в лобби.");
    OnPlayerLeaveLobby(playerid, player_lobby_idx[playerid], "/lobbyexit");
    return 1;
}

ClearDeathMessage(playerid)
{
    for(new j = 0; j < 5; j++) SendDeathMessageToPlayer(playerid, 1001, 1001, 200);
}
