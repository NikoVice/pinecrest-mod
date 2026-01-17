stock InfoEvent(number)
{
    switch(number)
    {
        case 0:
        {
            SendMesAll(0xFFD700FF, "Внимание! "W"Началась регистрация на гонки! ( /gps > [12] Развлечения > [1] Центр мероприятий )");
            RaceStarted = true;
            EventTime = 300;
            EventMap = random(2);
        }
        case 1:
        {
            SendMesAll(0xFFD700FF, "Внимание! "W"Началась регистрация на дерби! ( /gps > [12] Развлечения > [1] Центр мероприятий )");
            DerbyStarted = true;
            EventTime = 300;
            EventMap = random(2);
        }
        case 2:
        {
            SendMesAll(0xFFD700FF, "Внимание! "W"Началась регистрация на пейнтбол! ( /gps > [12] Развлечения > [1] Центр мероприятий )");
            PaintBallStarted = true;
            EventTime = 300;
            EventMap = random(3);
        }
        case 3:
        {
            SendMesAll(0xFFD700FF, "Внимание! "W"Началась регистрация на Казаки-разбойники! ( /gps > [12] Развлечения > [1] Центр мероприятий )");
            CossackRobbersStart = true;
            EventTime = 300;
            CossackRobbersMap = random(2);
            CossackRobbersWeapon = RandomEx(22, 32);
            CossackRobbersSkin[0] = random(312);
            CossackRobbersSkin[1] = random(312);
        }
    }
    return 1;
}

stock ClearEventPlayers(number)
{
    switch(number)
    {
        case 0:
        {
            for(new i = 0; i < MAX_RACE_PLAYERS; i ++)
            {
                if(RacePlayers[i] != INVALID_PLAYER_ID)
                {
                    RegisterRace[RacePlayers[i]] = 0;
                    RacePlayers[i] = INVALID_PLAYER_ID;
                    if(RaceVehicles[i] != INVALID_VEHICLE_ID) DestroyVehicleVEx(RaceVehicles[i]);
                    RaceVehicles[i] = INVALID_VEHICLE_ID;
                }
            }
        }
        case 1:
        {
            for(new i = 0; i < MAX_DERBY_PLAYERS; i ++)
            {
                if(DerbyPlayers[i] != INVALID_PLAYER_ID)
                {
                    RegisterDerby[DerbyPlayers[i]] = 0;
                    DerbyPlayers[i] = INVALID_PLAYER_ID;
                    if(DerbyVehicles[i] != INVALID_VEHICLE_ID) DestroyVehicleVEx(DerbyVehicles[i]);
                    DerbyVehicles[i] = INVALID_VEHICLE_ID;
                }
            }
        }
        case 2:
        {
            for(new i = 0; i < MAX_PAINTBALL_PLAYERS; i ++)
            {
                if(PaintBallPlayers[i] != INVALID_PLAYER_ID)
                {
                    RegisterPaintBall[PaintBallPlayers[i]] = 0;
                    PaintBallPlayers[i] = INVALID_PLAYER_ID;
                }
            }
        }
    }
    return 1;
}

stock EventPlayersCount(number)
{
    switch(number)
    {
        case 0:
        {
            new count;
            for(new i = 0; i < MAX_RACE_PLAYERS; i++)
            {
                if(RacePlayers[i] != INVALID_PLAYER_ID) count++;
            }
            return count;
        }
        case 1:
        {
            new count;
            for(new i = 0; i < MAX_DERBY_PLAYERS; i++)
            {
                if(DerbyPlayers[i] != INVALID_PLAYER_ID) count++;
            }
            return count;
        }
        case 2:
        {
            new count;
            for(new i = 0; i < MAX_PAINTBALL_PLAYERS; i++)
            {
                if(PaintBallPlayers[i] != INVALID_PLAYER_ID) count++;
            }
            return count;
        }
    }
    return 1;
}

stock AddPlayerToEvent(number, playerid)
{
    switch(number)
    {
        case 0:
        {
            for(new i = 0; i < MAX_RACE_PLAYERS; i++)
            {
                if(RacePlayers[i] == playerid) break;
                if(RacePlayers[i] == INVALID_PLAYER_ID)
                {
                    if(p_info[playerid][level] < 2) return SendError(playerid, "Участвовать на мероприятиях можно со 2-ого уровня.");
                    if(p_info[playerid][Lic][LIC_CAR] != 1) return SendError(playerid, "У Вас нет водительского удостоверения.");
                    RacePlayers[i] = playerid;
                    RegisterRace[playerid] = 1;
                    SendAccess(playerid, "Вы зарегистрировались на участие в гонке. Пожалуйста ожидайте.");
                    CheckEvent(0);
                    break;
                }
            }
        }
        case 1:
        {
            for(new i = 0; i < MAX_DERBY_PLAYERS; i++)
            {
                if(DerbyPlayers[i] == playerid) break;
                if(DerbyPlayers[i] == INVALID_PLAYER_ID)
                {
                    if(p_info[playerid][level] < 2) return SendError(playerid, "Участвовать на мероприятиях можно со 2-ого уровня.");
                    if(p_info[playerid][Lic][LIC_CAR] != 1) return SendError(playerid, "У Вас нет водительского удостоверения.");
                    DerbyPlayers[i] = playerid;
                    RegisterDerby[playerid] = 1;
                    SendAccess(playerid, "Вы зарегистрировались на участие в дерби. Пожалуйста ожидайте.");
                    CheckEvent(1);
                    break;
                }
            }
        }
        case 2:
        {
            for(new i = 0; i < MAX_PAINTBALL_PLAYERS; i++)
            {
                if(PaintBallPlayers[i] == playerid) break;
                if(PaintBallPlayers[i] == INVALID_PLAYER_ID)
                {
                    if(!FD(playerid) && !IsPlayerMobile(playerid)) return SendError(playerid, "Участвовать на пейнтболе можно только с Android-устройства.");
                    if(p_info[playerid][level] < 2) return SendError(playerid, "Участвовать на мероприятиях можно со 2-ого уровня.");
                    PaintBallPlayers[i] = playerid;
                    RegisterPaintBall[playerid] = 1;
                    SendAccess(playerid, "Вы зарегистрировались на участие в пейнтболе. Пожалуйста ожидайте.");
                    CheckEvent(2);
                    break;
                }
            }
        }
    }
    return 1;
}

stock CheckEvent(number)
{
    switch(number)
    {
        case 0:
        {
            new count;
            for(new i = 0; i < MAX_RACE_PLAYERS; i++)
            {
                if(RacePlayers[i] == INVALID_PLAYER_ID) count++;
            }
            if(!count) EventTime = 0, EventStart(0);
        }
        case 1:
        {
            new count;
            for(new i = 0; i < MAX_DERBY_PLAYERS; i++)
            {
                if(DerbyPlayers[i] == INVALID_PLAYER_ID) count++;
            }
            if(!count) EventTime = 0, EventStart(1);
        }
        case 2:
        {
            new count;
            for(new i = 0; i < MAX_PAINTBALL_PLAYERS; i++)
            {
                if(PaintBallPlayers[i] == INVALID_PLAYER_ID) count++;
            }
            if(!count) EventTime = 0, EventStart(2);
        }
    }
    return 1;
}

stock EventStart(number)
{
    switch(number)
    {
        case 0:
        {
            RaceStarted = false;
            new vehicle_id[20] = {411, 415, 424, 429, 434, 451, 480, 494, 495, 502, 503, 506, 522, 541, 559, 560, 561, 562, 565, 579}, model_id = vehicle_id[random(19)];
            for(new i = 0; i < MAX_RACE_PLAYERS; i++)
            {
                if(RacePlayers[i] != INVALID_PLAYER_ID)
                {
                    p_temp[RacePlayers[i]][TickPickup] = GetTickCount();
                    if(IsPlayerInAnyVehicle(RegisterRace[i])) RemovePlayerFromVehicle(RegisterRace[i]);
                    RegisterRace[RacePlayers[i]] = 2;
                    SetCameraBehindPlayer(RacePlayers[i]);
                    TogglePlayerControllable(RacePlayers[i], 0);
                    RaceVehicles[i] = CreateVehicleVEx(NPO_EVENTCAR, NPO_NONE, model_id, RaceCarsCoord[EventMap][i][0], RaceCarsCoord[EventMap][i][1], RaceCarsCoord[EventMap][i][2], RaceCarsCoord[EventMap][i][3], random(255), random(255), -1);
                    SetPlayerInterior(RacePlayers[i], 0);
                    SetPlayerVirtualWorld(RacePlayers[i], 500);
                    SetVehicleVirtualWorld(RaceVehicles[i], 500);
                    SetVehicleParamsVEx(RaceVehicles[i], false, false, false, false, false, false, false);
                    veh_info[RaceVehicles[i]][v_fuel] = GetVehicleData(GetVehicleModelEx(RaceVehicles[i]), E_VD_MAX_FUEL);
                    RacePosition[i] = 0;
                    PutPlayerInVehicle(RacePlayers[i], RaceVehicles[i], 0);
                    SetPlayerRaceCheckpoint(RacePlayers[i], 0, RaceCPCoord[EventMap][RacePosition[i]][0], RaceCPCoord[EventMap][RacePosition[i]][1], RaceCPCoord[EventMap][RacePosition[i]][2], RaceCPCoord[EventMap][RacePosition[i] + 1][0], RaceCPCoord[EventMap][RacePosition[i] + 1][1], RaceCPCoord[EventMap][RacePosition[i] + 1][2], 10.0);
                    SendInfo(RacePlayers[i], "Гонки начались.");
                    /*SendInfo(RacePlayers[i], "Гонки начинается через 15 секунд.");*/

                    CheckPlayerMission(RacePlayers[i], DAILY_MP);
                    CheckPlayerMission(RacePlayers[i], ACHIEVEMENT_MP);

                    if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(RacePlayers[i], 722);

                    SetVehicleParamsVEx(RaceVehicles[i], true, true, false, false, false, false, false);
                    OnPlayerUpdateVehicleInfo(RacePlayers[i], SPEEDO_ENGINE);
                    TogglePlayerControllable(RacePlayers[i], 1);
                    GameTextForPlayer(RacePlayers[i], "~g~GO GO GO", 500, 3);
                }
            }
            for(new idx; idx < 3; idx++) RaceWinnerIDs[idx] = INVALID_PLAYER_ID;
            /*EventTimer = SetTimer("StartRace", 1000, true);
            EventTimerSec = 15;*/
            TeleportInMP = false;
        }
        case 1:
        {
            DerbyStarted = false, DerbyPasses = true;
            new vehicle_id[5] = {504, 568, 573, 604, 605}, model_id = vehicle_id[random(4)];
            for(new i = 0; i < MAX_DERBY_PLAYERS; i++)
            {
                if(DerbyPlayers[i] != INVALID_PLAYER_ID)
                {
                    p_temp[DerbyPlayers[i]][TickPickup] = GetTickCount();
                    if(IsPlayerInAnyVehicle(DerbyPlayers[i])) RemovePlayerFromVehicle(DerbyPlayers[i]);
                    RegisterDerby[DerbyPlayers[i]] = 2;
                    SetCameraBehindPlayer(DerbyPlayers[i]);
                    TogglePlayerControllable(DerbyPlayers[i], 0);
                    DerbyVehicles[i] = CreateVehicleVEx(NPO_EVENTCAR, NPO_NONE, model_id, DerbyCarsCoord[EventMap][i][0], DerbyCarsCoord[EventMap][i][1], DerbyCarsCoord[EventMap][i][2], DerbyCarsCoord[EventMap][i][3], random(255), random(255), -1);
                    LinkVehicleToInterior(DerbyVehicles[i], 15);
                    SetPlayerInterior(DerbyPlayers[i], 15);
                    SetPlayerVirtualWorld(DerbyPlayers[i], 500);
                    SetPlayerHealth(DerbyPlayers[i], 100.0);
                    SetVehicleVirtualWorld(DerbyVehicles[i], 500);
                    SetVehicleParamsVEx(DerbyVehicles[i], false, false, false, false, false, false, false);
                    veh_info[DerbyVehicles[i]][v_fuel] = GetVehicleData(GetVehicleModelEx(DerbyVehicles[i]), E_VD_MAX_FUEL);
                    PutPlayerInVehicle(DerbyPlayers[i], DerbyVehicles[i], 0);
                    OnPlayerUpdateVehicleInfo(DerbyPlayers[i], SPEEDO_ENGINE);
                    SendInfo(DerbyPlayers[i], "Дерби началось.");
                    /*SendInfo(PaintBallPlayers[i], "Дерби начинается через 15 секунд.");*/

                    CheckPlayerMission(DerbyPlayers[i], DAILY_MP);
                    CheckPlayerMission(DerbyPlayers[i], ACHIEVEMENT_MP);

                    if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(DerbyPlayers[i], 722);

                    SetVehicleParamsVEx(DerbyVehicles[i], true, true, false, false, false, false, false);
                    OnPlayerUpdateVehicleInfo(DerbyPlayers[i], SPEEDO_ENGINE);
                    TogglePlayerControllable(DerbyPlayers[i], 1);
                    GameTextForPlayer(DerbyPlayers[i], "~g~GO GO GO", 500, 3);
                }
            }
            /*EventTimer = SetTimer("StartDerby", 1000, true);
            EventTimerSec = 15;*/
            TeleportInMP = false;
        }
        case 2:
        {
            PaintBallStarted = false, PaintBallPasses = true;
            new idx;
            for(new i = 0; i < MAX_PAINTBALL_PLAYERS; i++)
            {
                if(PaintBallPlayers[i] != INVALID_PLAYER_ID)
                {
                    p_temp[PaintBallPlayers[i]][TickPickup] = GetTickCount();
                    PaintBallKills[PaintBallPlayers[i]] = 0;
                    PaintBallDeaths[PaintBallPlayers[i]] = 0;

                    TogglePlayerControllable(PaintBallPlayers[i], 0);
                    ResetPlayerWeapons(PaintBallPlayers[i]);
                    RegisterPaintBall[PaintBallPlayers[i]] = 2;
                    idx = random(35);
                    TogglePlayerControllable(PaintBallPlayers[i], 0);
                    SetPlayerPos(PaintBallPlayers[i], PaintBallPlayersCoord[EventMap][idx][0], PaintBallPlayersCoord[EventMap][idx][1], PaintBallPlayersCoord[EventMap][idx][2]+0.1);
                    SetPlayerFacingAngle(PaintBallPlayers[i], PaintBallPlayersCoord[EventMap][idx][3]);
                    if(EventMap == 0) SetPlayerInterior(PaintBallPlayers[i], 1);
                    else SetPlayerInterior(PaintBallPlayers[i], 0);
                    SetPlayerVirtualWorld(PaintBallPlayers[i], 500);
                    p_info[PaintBallPlayers[i]][pHealth] = 100.0;
                    SetPlayerHealth(PaintBallPlayers[i], 100.0);

                    p_info[PaintBallPlayers[i]][pHealth] = 100.0;
                    SetPlayerHealth(PaintBallPlayers[i], p_info[PaintBallPlayers[i]][pHealth]);
                    SetPlayerColor(PaintBallPlayers[i], 0xFF0000FF);
                    SendInfo(PaintBallPlayers[i], "Пейнтбол начался.");
                    /*SendInfo(PaintBallPlayers[i], "Пейнтбол начинается через 15 секунд. Длительность: 10 минут.");*/

                    CheckPlayerMission(PaintBallPlayers[i], DAILY_MP);
                    CheckPlayerMission(PaintBallPlayers[i], ACHIEVEMENT_MP);

                    if(GetPlayerGiveCasket(100, 5) != -1) GivePlayerCasket(PaintBallPlayers[i], 722);

                    new random_weapon = random(9);
                    PaintBallWeaponID[PaintBallPlayers[i]] = PaintBallWeapon[random_weapon];
                    GivePlayerWeapon(PaintBallPlayers[i], PaintBallWeaponID[PaintBallPlayers[i]], 9999);

                    TogglePlayerControllable(PaintBallPlayers[i], 1);
                    GameTextForPlayer(PaintBallPlayers[i], "~g~GO GO GO", 500, 3);
                    //KillTimer(EventTimer);
                    ShowTextDrawForPlayer(PaintBallPlayers[i], TD_ID_CAPTURE);
                    CaptureInfoUpdate(PaintBallPlayers[i], CAPTURE_ID_PAINTBALL);
                }
            }
            /*EventTimer = SetTimer("StartPaintBall", 1000, true);
            EventTimerSec = 15;*/
            PaintBallTimerSec = 600;
            TeleportInMP = false;
        }
    }
    return 1;
}

stock EndPaintBall()
{
    if(PaintBallPasses == true)
    {
        if(PaintBallLeaderID == INVALID_PLAYER_ID) return SendMesAll(0xFFD700FF, "Внимание! "W"На пейнтболе не осталось игроков, победителя нет.");
        else
        {
            if(IsPlayerConnected(PaintBallLeaderID))
            {
                SetPlayerMoney(PaintBallLeaderID, PAINTBALL_PRIZ, true, "Победа на пейнтболе");
                SendMesAll(0xFFD700FF, "Внимание! "W"На пейнтболе победил(-а) %s с %d убийст(-ом/-ами). Приз: 15000$.", p_info[PaintBallLeaderID][name], PaintBallLeaderKills);
            }
        }
        for(new i = 0; i < MAX_PAINTBALL_PLAYERS; i++)
        {
            if(PaintBallPlayers[i] == INVALID_PLAYER_ID) continue;
            SetPlayerHealth(PaintBallPlayers[i], 100.0);
            //SetPlayerArmour(PaintBallPlayers[i], p_info[PaintBallPlayers[i]][pArmour]);
            SetPlayerInterior(PaintBallPlayers[i], 0);
            SetPlayerVirtualWorld(PaintBallPlayers[i], 0);
            SetPlayerPos(PaintBallPlayers[i], 1421.7180,-1623.7816,13.5469);
            SetPlayerFacingAngle(PaintBallPlayers[i], 270.0074);
            SetCameraBehindPlayer(PaintBallPlayers[i]);
            RegisterPaintBall[PaintBallPlayers[i]] = 0;
            ResetPlayerWeapons(PaintBallPlayers[i]);

            if((p_info[PaintBallPlayers[i]][member] != 0 && p_info[PaintBallPlayers[i]][fwork] == true)) SetPlayerColor(PaintBallPlayers[i], fraction_color[p_info[PaintBallPlayers[i]][member]]);
            else SetPlayerColor(PaintBallPlayers[i],  fraction_color[0]);
            if(p_info[PaintBallPlayers[i]][admin] > 0) SetPlayerColor(PaintBallPlayers[i], 0xFFFFFF00);

            HideTextDrawForPlayer(PaintBallPlayers[i], TD_ID_CAPTURE);
            PaintBallPlayers[i] = INVALID_PLAYER_ID;
        }
        PaintBallLeaderKills = 0, PaintBallLeaderID = INVALID_PLAYER_ID;
        PaintBallTimerSec = 0;
        PaintBallPasses = false;
    }
    return 1;
}

CMD:startrace(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    if(RaceStarted == true || DerbyStarted == true || PaintBallStarted == true || CossackRobbersStart == true) return SendError(playerid, "В данный момент идет регистрация на одно из мероприятий.");
    if(RaceStarted == true) return SendError(playerid, "Гонки уже начались.");
    InfoEvent(0);
    return 1;
}
CMD:startderby(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    if(RaceStarted == true || DerbyStarted == true || PaintBallStarted == true || CossackRobbersStart == true) return SendError(playerid, "В данный момент идет регистрация на одно из мероприятий.");
    if(DerbyStarted == true || DerbyPasses == true) return SendError(playerid, "Дерби уже началось.");
    InfoEvent(1);
    return 1;
}
CMD:startpaint(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    if(RaceStarted == true || DerbyStarted == true || PaintBallStarted == true || CossackRobbersStart == true) return SendError(playerid, "В данный момент идет регистрация на одно из мероприятий.");
    if(PaintBallStarted == true || PaintBallPasses == true) return SendError(playerid, "Пейнтбол уже начался.");
    InfoEvent(2);
    return 1;
}
CMD:startcr(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    if(RaceStarted == true || DerbyStarted == true || PaintBallStarted == true || CossackRobbersStart == true) return SendError(playerid, "В данный момент идет регистрация на одно из мероприятий.");
    if(CossackRobbersStart == true || CossackRobbersPasses == true) return SendError(playerid, "Казаки-разбойники уже начались.");
    InfoEvent(3);
    return 1;
}
CMD:stopevent(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    SendMesAll(0xFFD700FF, "Внимание! "W"Мероприятие отменено по тех. причинам.");
    RaceStarted = false, DerbyStarted = false, PaintBallStarted = false, CossackRobbersStart = false;
    EventTime = 0;
    EventMap = -1;
    /*EventTimerSec = 0;*/
    for(new i = 0; i < 3; i++) ClearEventPlayers(i);
    ClearPlayerCossackRobbers();
    SendAccess(playerid, "Вы отменили мероприятие.");
    return 1;
}
CMD:eventtime(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    if(RaceStarted == true || DerbyStarted == true || PaintBallStarted == true || CossackRobbersStart == true)
    {
        EventTime = 30;
        return SendAccess(playerid, "Вы сократили время до начала мероприятия на 30 сек.");
    }
    else SendError(playerid, "В данный момент нет регистраций на мероприятия.");
    return 1;
}

OnPlayerCheckEvent(playerid)
{
    if(RegisterRace[playerid] != 0 || RegisterDerby[playerid] != 0 || RegisterPaintBall[playerid] != 0 || p_temp[playerid][cossack_robbers_register] != 0) return SendError(playerid, "Находясь на мероприятии Вы не можете пользоваться данной командой.");
    return -1;
}
