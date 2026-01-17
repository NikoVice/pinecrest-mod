new bool:FishStart[MAX_PLAYERS];
new FishTimer[MAX_PLAYERS];
new FishPress[MAX_PLAYERS];
new FishPressCount[MAX_PLAYERS];

new pickup_fish;

new fish_type[4] = {689, 690, 691, 635};
new fish_price[4] = {2000, 3000, 1000, 1000};

new Float:FishVehiclePos[8][4] = {
    {-2746.4280, 1338.3589, -0.0741, 0.0000},
    {-2752.4280, 1338.3589, -0.0741, 0.0000},
    {-2758.4280, 1338.3589, -0.0741, 0.0000},
    {-2764.4280, 1338.3589, -0.0741, 0.0000},
    {-2770.4280, 1338.3589, -0.0741, 0.0000},
    {-2776.4280, 1338.3589, -0.0741, 0.0000},
    {-2782.4280, 1338.3589, -0.0741, 0.0000},
    {-2788.4280, 1338.3589, -0.0741, 0.0000}
};

enum
{
    TYPE_FISH_END,
    TYPE_FISH_AWAY,
    TYPE_FISH_DESTROY_LINE,
    TYPE_FISH_DESTROY_COIL,
    TYPE_FISH_DESTROY_HOOK,
    TYPE_FISH_CAUGHT
}

#define MAX_FISHING_POSITION 22

new fPlayer_Areaid[MAX_PLAYERS] = {-1, ...},
    fPlayer_Timerid[MAX_PLAYERS] = {-1, ...};
new
    Text3D:fFishing_Label[MAX_FISHING_POSITION],
    fFishing_Sphere[MAX_FISHING_POSITION],
    bool:fFishing_Status[MAX_FISHING_POSITION char];

static const
    Float:fFishing_Position[MAX_FISHING_POSITION][] = {
    {-2831.9653,1327.5165,7.1016,45.0000},
    {-2834.0325,1325.4535,7.1016,45.0000},
    {-2836.1084,1323.3783,7.1016,45.0000},
    {-2838.1565,1321.3303,7.1016,45.0000},
    {-2840.2302,1319.2528,7.1016,45.0000},
    {-2842.2712,1317.2151,7.1016,45.0000},
    {-2844.3616,1315.1244,7.1016,45.0000},
    {-2846.4309,1313.0553,7.1016,45.0000},
    {-2847.3708,1310.5890,7.1016,90.0000},
    {-2847.3708,1307.6613,7.1016,90.0000},
    {-2847.3708,1304.7496,7.1016,90.0000},
    {-2847.3708,1301.8511,7.1016,90.0000},
    {-2847.3704,1298.9187,7.1016,90.0000},
    {-2847.3704,1295.6150,7.1016,90.0000},
    {-2847.3708,1292.3386,7.1016,90.0000},
    {-2847.3708,1289.0477,7.1016,90.0000},
    {-2847.3708,1285.7540,7.1016,90.0000},
    {-2847.3708,1282.4269,7.1016,90.0000},
    {-2847.3706,1279.1959,7.1016,90.0000},
    {-2847.3706,1276.2460,7.1016,90.0000},
    {-2847.3708,1273.3873,7.1016,90.0000},
    {-2847.3708,1270.4264,7.1016,90.0000}
};

#define MAX_NETWORK         500
#define MAX_PLAYER_NETWORK  5
enum E_NETWORK_INFO
{
    niID,
    niOwnerID,
    niName[MAX_PLAYER_NAME],
    Float:niPosX,
    Float:niPosY,
    Float:niPosZ,
    Float:niPosRX,
    Float:niPosRY,
    Float:niPosRZ,
    niInterior,
    niWorld,
    niProg,
    niPlanted,
    niObject,
    Text3D:niText
};
new NetworkInfo[MAX_NETWORK][E_NETWORK_INFO];

CheckNetwork()
{
    for(new i = 1; i < MAX_NETWORK; i++)
    {
        if(NetworkInfo[i][niPlanted] == 0) continue;
        NetworkInfo[i][niProg]++;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `network` SET `prog` = '%d' WHERE `id` = %d LIMIT 1",
        NetworkInfo[i][niProg], NetworkInfo[i][niID]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        if(NetworkInfo[i][niProg] == 3)
        {
            NetworkInfo[i][niPlanted] = 2;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `network` SET `planted` = %d WHERE `id` = %d LIMIT 1",
            NetworkInfo[i][niPlanted], NetworkInfo[i][niID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        else if(NetworkInfo[i][niProg] == 27)
        {
            NetworkInfo[i][niPlanted] = 0;
            NetworkInfo[i][niProg] = 0;
            NetworkInfo[i][niOwnerID] = 0;
            strmid(NetworkInfo[i][niName], "None", 0, strlen("None"), 32);
            if(IsValidDynamicObject(NetworkInfo[i][niObject])) DestroyDynamicObject(NetworkInfo[i][niObject]);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `network` WHERE `id` = %d",
            NetworkInfo[i][niID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

GetFreeNetwork()
{
    new idx = -1;
    for(new i = 1; i < MAX_NETWORK; i++)
    {
        if(NetworkInfo[i][niPlanted] == 0) return i;
    }
    return idx;
}

LoadFish()
{
    pickup_fish = CreatePickup(1239, 23, -2822.5354,1324.0649,7.2846);
    CreateDynamic3DTextLabel("<< Аренда лодки >>\n\n<< Продажа рыбы >>", COLOR_MAIN, -2822.5354,1324.0649,7.2846, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, streamer_TESTLOL, -1, -1, -1);

    for(new i = 0; i < MAX_FISHING_POSITION; i++)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "Место для рыбалки "W"#%d{"#cMAIN"}\nАрендатор: "W"Нет{"#cMAIN"}\n\nДля начала рыбалки введите /fish", i);
        fFishing_Label[i] = CreateDynamic3DTextLabel(STRING_GLOBAL, COLOR_MAIN, fFishing_Position[i][0], fFishing_Position[i][1], fFishing_Position[i][2], 3.0, INVALID_PLAYER_ID,INVALID_VEHICLE_ID,streamer_TESTLOL);
        fFishing_Sphere[i] = CreateDynamicSphere(fFishing_Position[i][0], fFishing_Position[i][1], fFishing_Position[i][2], 1.0, 0, 0);
        UpdateAreaInfo(fFishing_Sphere[i], TYPE_FISHING, AREA_SUBTYPE_INVALID_ID, i);
    }
    return 1;
}

ShowFish(playerid)
{
    FishTimer[playerid] = 5;
    if(random(2) == 1) FishPress[playerid] = 1;
    else FishPress[playerid] = 2;
    SendMes(playerid, COLOR_SEA_WAVE, "Рыба на крючке, быстрее подсекай, жми что показано на экране.");
    new str[32];
    format(str, sizeof(str), "~w~PRESS: ~g~%s", FishPress[playerid] == 1 ? "Y" : "N");
    GameTextForPlayer(playerid, str, 2500, 3);
    return 1;
}

ClearFish(playerid)
{
    if(fPlayer_Areaid[playerid] != -1)
    {
        new index = fPlayer_Areaid[playerid];

        if(fFishing_Status{index} == false) return 1;

        if(fPlayer_Timerid[playerid] != -1)
        {
            KillTimer(fPlayer_Timerid[playerid]);
            fPlayer_Timerid[playerid] = -1;
        }

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Место для рыбалки "W"#%d{"#cMAIN"}\nАрендатор: "W"Нет{"#cMAIN"}\n\nДля начала рыбалки введите /fish", index);
        UpdateDynamic3DTextLabelText(fFishing_Label[index], COLOR_MAIN, STRING_GLOBAL);

        fPlayer_Areaid[playerid] = -1;
        fFishing_Status{index} = false;
    }
    return 1;
}

enum
{
    MENU_FISH_MAIN,
    MENU_FISH_SELL,
    MENU_FISH_SELL_INPUT,
    MENU_FISH_AREND,
    MENU_FISH_HELP
}

ShowFishMenu(playerid, type, first_parameter = 0)
{
    switch(type)
    {
        case MENU_FISH_MAIN:
        {
            ShowPlayerDialog(playerid, D_FISH_MENU, DIALOG_STYLE_LIST, ""I"Рыболовный пирс", ""I"[1]"W" Продажа рыбы\n"I"[2]"W" Аренда лодки\n"I"[3]"W" Помощь по рыбалке", "Далее", "Отмена");
        }
        case MENU_FISH_SELL:
        {
            new type;
            STRING_GLOBAL = "[#] Название\tСтоимость\tДоступно для продажи\n", STRING_MIN[0] = EOS;
            for(new i = 0; i < sizeof(fish_type); i++)
            {
                type = fish_type[i];
                format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s\t%d$\t%d кг.\n", i + 1, ItemsInfo[type][iName], fish_price[i], GetInventoryAmount(playerid, type));
                strcat(STRING_GLOBAL, STRING_MIN);
            }
            ShowPlayerDialog(playerid, D_FISH_MENU_SELL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Продажа рыбы", STRING_GLOBAL, "Далее", "Отмена");
        }
        case MENU_FISH_SELL_INPUT:
        {
            new type = fish_type[first_parameter];
            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите количество \"%s\", которое хотите продать:\n\nУ Вас есть %d ед.", ItemsInfo[type][iName], GetInventoryAmount(playerid, type));
            ShowPlayerDialog(playerid, D_FISH_MENU_SELL_INPUT, DIALOG_STYLE_INPUT, ""I"Продажа рыбы", STRING_GLOBAL, "Далее", "Отмена");
            SetPVarInt(playerid, "FishIDx", first_parameter);
        }
        case MENU_FISH_AREND:
        {
            ShowPlayerDialog(playerid, D_FISH_MENU_AREND, DIALOG_STYLE_MSGBOX, ""I"Аренда лодки", ""W"Вы желаете арендовать "I"\"Reefer\""W" за "I"2500$?"W"\n\nДанная возможность предоставлена для установки и сбора сетей.", "Да", "Нет");
            return 1;
        }
        case MENU_FISH_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i; i < sizeof(FishInfoList); i++) strcat(STRING_GLOBAL, FishInfoList[i]);
            ShowPlayerDialog(playerid, D_FISH_MENU_BACK, DIALOG_STYLE_MSGBOX, ""I"Помощь по рыбалке", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
    }
    return 1;
}

StartFish(playerid)
{
    if(fPlayer_Areaid[playerid] != -1)
    {
        if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;

        if(GetInventoryAmount(playerid, 684) == 0) return SendError(playerid, "У Вас нет удочки.");
        if(GetInventoryAmount(playerid, 685) == 0) return SendError(playerid, "У Вас нет лески.");
        if(GetInventoryAmount(playerid, 686) == 0) return SendError(playerid, "У Вас нет катушки.");
        if(GetInventoryAmount(playerid, 687) == 0) return SendError(playerid, "У Вас нет крючка.");
        if(GetInventoryAmount(playerid, 634) == 0) return SendError(playerid, "У Вас нет червяка.");

        if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
        SetPlayerAttachedObject(playerid, 1, 18632, 6, 0.079376, 0.037070, 0.007706, 181.482910, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000);

        if(fPlayer_Timerid[playerid] != -1) return 1;

        new index = fPlayer_Areaid[playerid];

        if(!IsPlayerInDynamicArea(playerid, fFishing_Sphere[index])) return 1;

        SetPlayerPos(playerid, fFishing_Position[index][0], fFishing_Position[index][1], fFishing_Position[index][2]);
        SetPlayerFacingAngle(playerid, fFishing_Position[index][3]);

        GivePlayerInventory(playerid, 634, -1);

        FishStart[playerid] = true;
        FishTimer[playerid] = RandomEx(15,30);

        if(p_info[playerid][p_settings][ROLEPLAY] == 1)
        {
            DoAction(playerid, "Удочка в руке.");
            MeAction(playerid, "встал в стойку, затем закинул удочку в воду, после чего стал ожидать клева");
        }
    } else SendError(playerid, "Вы далеко от места рыбалки! Найти место для рыбалки можно в GPS навигаторе!");
    return 1;
}

StopFish(playerid, type)
{
    if(FishStart[playerid] == false) return 1;
    FishStart[playerid] = false;
    FishTimer[playerid] = 0;
    FishPress[playerid] = 0;
    FishPressCount[playerid] = 0;
    if(IsPlayerAttachedObjectSlotUsed(playerid, 1)) RemovePlayerAttachedObject(playerid, 1);
    switch(type)
    {
        case TYPE_FISH_END: SendMes(playerid, COLOR_BLUE, "Вы закончили рыбачить.");
        case TYPE_FISH_AWAY: SendMes(playerid, COLOR_DARKORANGE, "Вы отошли далеко от места рыбалки.");
        case TYPE_FISH_DESTROY_LINE:
        {
            SendInfo(playerid, "О нет, леска лопнула! Надо было осторожнее подсекать.");
            GivePlayerInventory(playerid, 685, -1);
        }
        case TYPE_FISH_DESTROY_COIL:
        {
            SendInfo(playerid, "Вот так, на тебе! Катушка треснула! Нужна новая.");
            GivePlayerInventory(playerid, 686, -1);
        }
        case TYPE_FISH_DESTROY_HOOK:
        {
            SendInfo(playerid, "Эхх, крючок плохой, погнулся! Ни на что не годен, нужен новый.");
            GivePlayerInventory(playerid, 687, -1);
        }
        case TYPE_FISH_CAUGHT:
        {
            new fishrandom = random(475);
            switch(fishrandom)
            {
                case 0 .. 49:
                {
                    new fishweight;
                    if(random(8) == 0) fishweight = RandomEx(1, 3);
                    else fishweight = RandomEx(1, 2);

                    if(!GivePlayerInventory(playerid, 689, fishweight))
                        return 1;
                    SendAccess(playerid, "Ты поймал(-а) \"%s\" весом в %d кг, закидывай снова, может, опять повезет!", ItemsInfo[689][iName], fishweight);

                    CheckPlayerMission(playerid, START_FISH);
                    CheckPlayerMission(playerid, DAILY_FISH);
                    CheckPlayerMission(playerid, ACHIEVEMENT_FISH);

                    CheckPlayerFreelance(playerid, FREELANCE_FISH);
                    CheckPlayerBattlePass(playerid, BATTLEPASS_FISH);

                    UpdateFamilyLevel(playerid);
                    UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_FISH); // Контракты: Рыбалка
                }
                case 50 .. 74:
                {
                    new fishweight;
                    if(random(16) == 0) fishweight = RandomEx(1, 3);
                    else fishweight = RandomEx(1, 2);

                    if(!GivePlayerInventory(playerid, 690, fishweight))
                        return 1;

                    SendAccess(playerid, "Ты поймал(-а) \"%s\" весом в %d кг, закидывай снова, может, опять повезет!", ItemsInfo[690][iName], fishweight);

                    CheckPlayerMission(playerid, START_FISH);
                    CheckPlayerMission(playerid, DAILY_FISH);
                    CheckPlayerMission(playerid, ACHIEVEMENT_FISH);

                    CheckPlayerFreelance(playerid, FREELANCE_FISH);
                    CheckPlayerBattlePass(playerid, BATTLEPASS_FISH);

                    UpdateFamilyLevel(playerid);
                    UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_FISH); // Контракты: Рыбалка
                }
                case 75 .. 274:
                {
                    new fishweight;
                    if(random(4) == 0) fishweight = RandomEx(1, 3);
                    else fishweight = RandomEx(1, 2);

                    if(!GivePlayerInventory(playerid, 691, fishweight))
                        return 1;

                    SendAccess(playerid, "Ты поймал(-а) \"%s\" весом в %d кг, закидывай снова, может, опять повезет!", ItemsInfo[691][iName], fishweight);

                    CheckPlayerMission(playerid, START_FISH);
                    CheckPlayerMission(playerid, DAILY_FISH);
                    CheckPlayerMission(playerid, ACHIEVEMENT_FISH);

                    CheckPlayerFreelance(playerid, FREELANCE_FISH);
                    CheckPlayerBattlePass(playerid, BATTLEPASS_FISH);

                    UpdateFamilyLevel(playerid);
                    UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_FISH); // Контракты: Рыбалка
                }
                case 275 .. 474:
                {
                    new fishweight;
                    if(random(4) == 0) fishweight = RandomEx(1, 3);
                    else fishweight = RandomEx(1, 2);

                    if(!GivePlayerInventory(playerid, 635, fishweight))
                        return 1;
                    SendAccess(playerid, "Ты поймал(-а) \"%s\" весом в %d кг, закидывай снова, может, опять повезет!", ItemsInfo[635][iName], fishweight);

                    CheckPlayerMission(playerid, START_FISH);
                    CheckPlayerMission(playerid, DAILY_FISH);
                    CheckPlayerMission(playerid, ACHIEVEMENT_FISH);

                    CheckPlayerFreelance(playerid, FREELANCE_FISH);
                    CheckPlayerBattlePass(playerid, BATTLEPASS_FISH);

                    UpdateFamilyLevel(playerid);
                    UpdateFamilyContract(playerid, CONTRACT_FAMILY_ID_FISH); // Контракты: Рыбалка
                }
                default: SendMes(playerid, COLOR_DARKORANGE, "Рыба сорвалась, закинь еще раз, на этот раз может повезти.");
            }
        }
    }
    return 1;
}

CMD:fish(playerid, params[])
{
    if(FishStart[playerid] == false) StartFish(playerid);
    else StopFish(playerid, TYPE_FISH_END);
    return 1;
}

forward create_network(idx);
public create_network(idx)
{
    NetworkInfo[idx][niID] = cache_insert_id();
    return 1;
}

forward load_network();
public load_network()
{
    new str[256], time = GetTickCount(), totalnetwork;
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            if(totalnetwork == MAX_NETWORK - 1) break;
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iis[32]ffffffiiii",
            NetworkInfo[idx][niID],
            NetworkInfo[idx][niOwnerID],
            NetworkInfo[idx][niName],
            NetworkInfo[idx][niPosX],
            NetworkInfo[idx][niPosY],
            NetworkInfo[idx][niPosZ],
            NetworkInfo[idx][niPosRX],
            NetworkInfo[idx][niPosRY],
            NetworkInfo[idx][niPosRZ],
            NetworkInfo[idx][niWorld],
            NetworkInfo[idx][niInterior],
            NetworkInfo[idx][niProg],
            NetworkInfo[idx][niPlanted]);
            totalnetwork++;
            if(NetworkInfo[idx][niPlanted])
            {
                NetworkInfo[idx][niObject] = CreateDynamicObject(2068, NetworkInfo[idx][niPosX], NetworkInfo[idx][niPosY], NetworkInfo[idx][niPosZ], NetworkInfo[idx][niPosRX], NetworkInfo[idx][niPosRY], NetworkInfo[idx][niPosRZ], NetworkInfo[idx][niWorld], NetworkInfo[idx][niInterior], -1, 120);
            }
        }
    }
    printf("Данные сетей загружены за %d мс", GetTickCount()-time);
    return 1;
}

CMD:cnetwork(playerid, params[])
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    if(p_temp[playerid][rented_veh] == INVALID_VEHICLE_ID) return SendError(playerid, "У Вас нет арендованного транспортного средства.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsPlayerRentedVehicle(playerid, vehicleid)) return SendError(playerid, "Вы должны находиться в своем арендованном транспортном средстве.");
    if(GetVehicleModelEx(vehicleid) != 453) return SendError(playerid, "Ваше арендованное транспортное средство не является \"Reefer\".");
    new Float:vPos[7];
    GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
    if(vPos[2] > 2.5) return SendError(playerid, "Вы должны находиться в морском пространстве.");
    if(GetInventoryAmount(playerid, 688) == 0) return SendError(playerid, "У Вас нет сетей.");
    new idx = GetFreeNetwork();
    if(idx == -1) return SendError(playerid, "На данный момент на сервере максимальное количество сетей, попробуйте позже.");

    new total = 0;
    for(new i = 1; i < MAX_NETWORK; i++)
    {
        if(NetworkInfo[i][niOwnerID] == p_info[playerid][ID] /*&& strcmp(get_name(playerid), NetworkInfo[i][niName], true)*/)
        {
            total++;
            if(total >= MAX_PLAYER_NETWORK) return SendError(playerid, "Вы не можете установить более %d сетей одновременно.", MAX_PLAYER_NETWORK);
        }
    }


    GetVehicleZAngle(vehicleid, vPos[3]);

    vPos[5] = vPos[0]+floatcos(vPos[3]+90, degrees);
    vPos[6] = vPos[1]+floatsin(vPos[3]+90, degrees);

    new Float: ox, Float: oy, Float: oz, Float: orx, Float: ory, Float: orz;
    GetObjectOffset(vPos[5], vPos[6], vPos[2], 0.000000, 0.000007, vPos[3] - 180.0, 0.00000, 0.00000, 0.00000, 0.00000, 180.0, 0.00000, ox, oy, oz, orx, ory, orz);

    NetworkInfo[idx][niOwnerID] = p_info[playerid][ID];

    NetworkInfo[idx][niPosX] = ox;
    NetworkInfo[idx][niPosY] = oy;
    NetworkInfo[idx][niPosZ] = oz;
    NetworkInfo[idx][niPosRX] = orx;
    NetworkInfo[idx][niPosRY] = ory;
    NetworkInfo[idx][niPosRZ] = orz;

    NetworkInfo[idx][niInterior] = GetPlayerInterior(playerid);
    NetworkInfo[idx][niWorld] = GetPlayerVirtualWorld(playerid);
    NetworkInfo[idx][niPlanted] = 1;
    NetworkInfo[idx][niProg] = 0;
    GivePlayerInventory(playerid, 688, -1);

    strmid(NetworkInfo[idx][niName], get_name(playerid), 0, strlen(get_name(playerid)), MAX_PLAYER_NAME);
    NetworkInfo[idx][niObject] = CreateDynamicObject(2068, NetworkInfo[idx][niPosX], NetworkInfo[idx][niPosY], NetworkInfo[idx][niPosZ], NetworkInfo[idx][niPosRX], NetworkInfo[idx][niPosRY], NetworkInfo[idx][niPosRZ], NetworkInfo[idx][niWorld], NetworkInfo[idx][niInterior], -1, 200);

    SendMes(playerid, COLOR_BLUE, "Вы установили сети.");
    SendMes(playerid, COLOR_LIME, "С помощью команды {"#cLYELLOW"}/snetwork{"#cLIME"} Вы можете узнать во сколько необходимо снять сети.");
    SendMes(playerid, COLOR_LIME, "После заполнения сетей у Вас будет 24 часа на то, чтобы собрать их.");

    MeAction(playerid, "установила(-а) сети");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `network` (`ownerid`, `x`, `y`, `z`, `rx`, `ry`, `rz`, `world`, `interior`, `prog`, `planted`) VALUES (%d, '%f', '%f', '%f', '%f', '%f', '%f', %d, %d, %d, %d)",
        p_info[playerid][ID], NetworkInfo[idx][niPosX], NetworkInfo[idx][niPosY], NetworkInfo[idx][niPosZ], NetworkInfo[idx][niPosRX], NetworkInfo[idx][niPosRY], NetworkInfo[idx][niPosRZ], NetworkInfo[idx][niWorld], NetworkInfo[idx][niInterior], NetworkInfo[idx][niProg], NetworkInfo[idx][niPlanted]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_network", "i", idx);
    return 1;
}

CMD:dnetwork(playerid, params[])
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    if(p_temp[playerid][rented_veh] == INVALID_VEHICLE_ID) return SendError(playerid, "У Вас нет арендованного транспортного средства.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsPlayerRentedVehicle(playerid, vehicleid)) return SendError(playerid, "Вы должны находиться в своем арендованном транспортном средстве.");
    if(GetVehicleModelEx(vehicleid) != 453) return SendError(playerid, "Ваше арендованное транспортное средство не является \"Reefer\".");
    new Float:vPos[3];
    GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
    if(vPos[2] > 2.5) return SendError(playerid, "Вы должны находиться в морском пространстве.");

    for(new i = 1; i < MAX_NETWORK; i++)
    {
        if(PlayerToPoint(2.5, playerid, NetworkInfo[i][niPosX], NetworkInfo[i][niPosY], NetworkInfo[i][niPosZ]))
        {
            if(NetworkInfo[i][niOwnerID] != p_info[playerid][ID]) continue; // && !strequals(NetworkInfo[i][niName], get_name(playerid))) return SendError(playerid, "Данная сеть Вам не принадлежит.");
            if(NetworkInfo[i][niPlanted] != 2) return SendError(playerid, "Данную сеть еще нельзя снять.");

            new fishrandom = random(100);
            switch(fishrandom)
            {
                case 0..69:
                {
                    new count[4];

                    if(random(8) == 0) count[0] = RandomEx(1, 3);
                    else count[0] = RandomEx(0, 2);

                    if(random(16) == 0) count[1] = RandomEx(1, 3);
                    else count[1] = RandomEx(0, 2);

                    if(random(4) == 0) count[2] = RandomEx(10, 15);
                    else count[2] = RandomEx(5, 10);

                    if(random(4) == 0) count[3] = RandomEx(10, 15);
                    else count[3] = RandomEx(5, 10);

                    SendMes(playerid, COLOR_BLUE, "Вы собрали сети.");
                    SendMes(playerid, COLOR_LIME, "Содержимое:");

                    new type;
                    for(new idx = 0; idx < sizeof(fish_type); idx++)
                    {
                        if(count[idx] == 0) continue;
                        type = fish_type[idx];
                        GivePlayerInventory(playerid, type, count[idx]);
                        SendInfo(playerid, "%s %d ед.", ItemsInfo[type][iName], count[idx]);
                    }
                }
                default:
                {
                    SendMes(playerid, COLOR_BLUE, "Вы собрали сети.");
                    SendMes(playerid, COLOR_DARKORANGE, "К сожалению, в сетях ничего нет.");
                }
            }

            NetworkInfo[i][niPlanted] = 0;
            NetworkInfo[i][niProg] = 0;
            NetworkInfo[i][niOwnerID] = 0;
            strmid(NetworkInfo[i][niName], "None", 0, strlen("None"), 32);
            if(IsValidDynamicObject(NetworkInfo[i][niObject])) DestroyDynamicObject(NetworkInfo[i][niObject]);

            MeAction(playerid, "собрал(-а) сети с рыбой");

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `network` WHERE `id` = %d", NetworkInfo[i][niID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            return 1;
        }
    }
    SendError(playerid, "Рядом с Вами нет Ваших сетей.");
    return 1;
}

CMD:snetwork(playerid, params[])
{
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return SendError(playerid, "Вы должны находиться в транспортном средстве.");
    if(p_temp[playerid][rented_veh] == INVALID_VEHICLE_ID) return SendError(playerid, "У Вас нет арендованного транспортного средства.");
    new vehicleid = GetPlayerVehicleID(playerid);
    if(!IsPlayerRentedVehicle(playerid, vehicleid)) return SendError(playerid, "Вы должны находиться в своем арендованном транспортном средстве.");
    if(GetVehicleModelEx(vehicleid) != 453) return SendError(playerid, "Ваше арендованное транспортное средство не является \"Reefer\".");
    new Float:vPos[3];
    GetVehiclePos(vehicleid, vPos[0], vPos[1], vPos[2]);
    if(vPos[2] > 2.5) return SendError(playerid, "Вы должны находиться в морском пространстве.");
    new count, str[32], newhour;

    if(timestamp_minute < 10)
    {
        timestamp_hour = timestamp_hour - 1;
        if(timestamp_hour == -1) timestamp_hour = 23;
    }
    STRING_GLOBAL = "[#] Номер сети\tСостояние\tМожно собрать\tРасстояние\n", STRING_MIN[0] = EOS;
    for(new i = 1; i < MAX_NETWORK; i++)
    {
        if(NetworkInfo[i][niOwnerID] != p_info[playerid][ID]) //&& !strequals(NetworkInfo[i][niName], get_name(playerid))
            continue;
        if(NetworkInfo[i][niProg] < 3)
        {
            newhour = (3 - NetworkInfo[i][niProg]) + timestamp_hour;
            if(timestamp_hour < 23 && newhour > 23) newhour = (NetworkInfo[i][niProg] + timestamp_hour) - 24;
            format(str, sizeof(str), "В %s%d:10:00", newhour < 10 ? "0" : "", newhour);
        }
        else str = "Сейчас";
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" Сеть #%d\t%s\t%s\t%.0f метров\n", count + 1, count + 1, NetworkInfo[i][niPlanted] == 1 ? "{"#cLIGHTRED"}Заполняется"W"" : "{"#cGREEN"}Переполнена"W"", str, GetPlayerDistanceFromPoint(playerid, NetworkInfo[i][niPosX], NetworkInfo[i][niPosY], NetworkInfo[i][niPosZ]));
        strcat(STRING_GLOBAL, STRING_MIN);
        p_temp[playerid][p_listitem][count] = i;
        count++;
        if(count >= MAX_PLAYER_NETWORK) break;
    }
    if(!count) return SendError(playerid, "Вы не устанавливали сети.");
    ShowPlayerDialog(playerid, D_FISH_SEARCH, DIALOG_STYLE_TABLIST_HEADERS, ""I"Мои сети", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
