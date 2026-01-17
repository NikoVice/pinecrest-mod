// ~~~~~~~~~~ [ Offer - Start ] ~~~~~~~~~~ //
// Offer System by Vip_Uzer
#define MAX_OFFER_PLAYER 10
enum e_offer
{
    key_offer[MAX_OFFER_PLAYER],
    price_offer[MAX_OFFER_PLAYER],
    id_offer[MAX_OFFER_PLAYER],
    count_one_offer[MAX_OFFER_PLAYER],
    count_two_offer[MAX_OFFER_PLAYER],
    timer_offer[MAX_OFFER_PLAYER]
}
new OfferInfo[MAX_PLAYERS][e_offer];
#define ALL_BUSY_SLOT_OFFER -1
#define ALL_FREE_SLOT_OFFER -2

GetPlayerOfferID(playerid, offer_idx)
{
    if(offer_idx == -1) return INVALID_PLAYER_ID;
    return OfferInfo[playerid][key_offer][offer_idx];
}
SetPlayerOfferID(playerid, offer_id, offer_idx)
    return OfferInfo[playerid][key_offer][offer_idx] = offer_id;

ClearOwnerOffer(playerid, offer_idx)
{
    for(new i; i < MAX_OFFER_PLAYER; i++)
    {
        if(offer_idx == GetPlayerOfferID(playerid, i))
        {
            SetPlayerOfferID(playerid, INVALID_PLAYER_ID, i);
            OfferInfo[playerid][price_offer][i] =
            OfferInfo[playerid][id_offer][i] =
            OfferInfo[playerid][count_one_offer][i] =
            OfferInfo[playerid][count_two_offer][i] = -1;
            OfferInfo[playerid][timer_offer][i] = -1;
            break;
        }
    }
}

GetFreeSlotOffer(playerid)
{
    new count_offer, offer_idx;
    for(new i; i < MAX_OFFER_PLAYER; i++)
    {
        offer_idx = GetPlayerOfferID(playerid, i);
        if(offer_idx != INVALID_PLAYER_ID && OfferInfo[playerid][timer_offer][i] < timestamp)
            ClearOwnerOffer(playerid, offer_idx);
        if(offer_idx == INVALID_PLAYER_ID)
            count_offer++;
    }
    if(count_offer == MAX_OFFER_PLAYER)
        return ALL_FREE_SLOT_OFFER;
    if(count_offer == 0) return ALL_BUSY_SLOT_OFFER;
    return count_offer;
}

SetFreeSlotOffer(playerid, offer_target, idx_offer, price = -1, count_one = -1, count_two = -1)
{
    if(GetFreeSlotOffer(playerid) == ALL_BUSY_SLOT_OFFER)
        return SendError(offer_target, "У игрока нет возможности принять предложение, повторите позже.");
    new offer_idx;
    for(new i = MAX_OFFER_PLAYER-1; i != -1; i--)
    {
        offer_idx = GetPlayerOfferID(playerid, i);
        if(offer_idx == offer_target)
            return SendError(offer_target, "Вы уже отправляли предложение этому игроку.");
    }

    for(new i; i < MAX_OFFER_PLAYER; i++)
    {
        if(GetPlayerOfferID(playerid, i) == INVALID_PLAYER_ID)
        {
            SetPlayerOfferID(playerid, offer_target, i);
            OfferInfo[playerid][price_offer][i] = price;
            OfferInfo[playerid][id_offer][i] = idx_offer;
            OfferInfo[playerid][count_one_offer][i] = count_one;
            OfferInfo[playerid][count_two_offer][i] = count_two;
            OfferInfo[playerid][timer_offer][i] = timestamp+60;
            SendInfo(playerid, "Вам поступило новое предложение: /offer");
            return 1;
        }
    }
    return 1;
}

SetOfferData(playerid, offer_target, idx_offer, price = -1, count = 0, idx = 0)
{
    p_temp[playerid][offer_info][0] = offer_target;
    p_temp[playerid][offer_info][1] = price;
    p_temp[playerid][offer_info][2] = idx_offer;
    p_temp[playerid][offer_info][3] = count;
    p_temp[playerid][offer_info][4] = idx;
}

// ~~~~~~~~~~ [ Offer - The end ] ~~~~~~~~~~ //

// ~~~~~~~~~~ [ Bizz - Start ] ~~~~~~~~~~ //

BizzPlayerList(playerid, bizz_type_idx)
{
    if(GetFreeSlotBizz(playerid) == p_info[playerid][bizz_slots])
        return SendError(playerid, "У Вас нет бизнесов.");

    STRING_GLOBAL[0] = EOS;
    new string[144], bizz_id;
    for(new i; i < p_info[playerid][bizz_slots]; i++)
    {
        string[0] = EOS;
        bizz_id = GetPlayerBizzID(playerid, i);
        if(bizz_id != INVALID_BIZZ_ID) f(string, "%s [ID: %d]", b_info[bizz_id][_name], bizz_id);
        else strcat(string, "Слот свободный");
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i+1, string);
    }
    if(p_info[playerid][bizz_slots] < MAX_BIZZ_PLAYER)
    {
        for(new i = p_info[playerid][bizz_slots]; i < MAX_BIZZ_PLAYER; i++)
        {
            f(STRING_GLOBAL, "%s"I"[%d]"W" Купить дополнительный слот\n", STRING_GLOBAL, i+1);
        }
    }
    p_temp[playerid][p_listitem_int] = bizz_type_idx;
    ShowPlayerDialog(playerid, D_BIZZ_PLAYER_LIST, DIALOG_STYLE_LIST, ""I"Бизнесы", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;
}

stock GetPlayerBizzID(playerid, idx = -1)
{
    if(idx == -1) return p_info[playerid][key_bizz][p_info[playerid][active_bizz_id]];
    return p_info[playerid][key_bizz][idx];
}

stock SetPlayerBizzID(playerid, bizz_idx, idx = -1)
{
    if(idx == -1) return p_info[playerid][key_bizz][p_info[playerid][active_bizz_id]] = bizz_idx;
    return p_info[playerid][key_bizz][idx] = bizz_idx;
}

ClearOwnerBizz(playerid, bizz_idx)
{
    for(new i; i < p_info[playerid][bizz_slots]; i++)
    {
        if(bizz_idx == GetPlayerBizzID(playerid, i))
        {
            SetPlayerBizzID(playerid, INVALID_BIZZ_ID, i);
            break;
        }
    }
}

GetFreeSlotBizz(playerid)
{
    new count_bizz;
    for(new i; i < p_info[playerid][bizz_slots]; i++)
    {
        if(GetPlayerBizzID(playerid, i) == INVALID_BIZZ_ID)
            count_bizz++;
    }
    if(count_bizz == p_info[playerid][bizz_slots])
        return p_info[playerid][bizz_slots];
    if(count_bizz == 0) return ALL_BUSY_SLOT_BIZZ;
    return count_bizz;
}

SetFreeSlotBizz(playerid, bizz_idx)
{
    for(new i; i < p_info[playerid][bizz_slots]; i++)
    {
        if(GetPlayerBizzID(playerid, i) == INVALID_BIZZ_ID)
        {
            SetPlayerBizzID(playerid, bizz_idx, i);
            break;
        }
    }
}

// ~~~~~~~~~~ [ Bizz - The end ] ~~~~~~~~~~ //

// ~~~~~~~~~~ [ House - Start ] ~~~~~~~~~~ //

HousePlayerList(playerid, house_type_idx)
{
    if(GetFreeSlotHouse(playerid) == p_info[playerid][house_slots])
        return SendError(playerid, "У Вас нет домов.");
    if(p_info[playerid][key_h_rent] != INVALID_HOUSE_ID)
        return SendError(playerid, "Вы где-то подселены.");

    STRING_GLOBAL[0] = EOS;
    new string[144], house_id;
    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        string[0] = EOS;
        house_id = GetPlayerHouseID(playerid, i);
        if(house_id != INVALID_HOUSE_ID) f(string, "Дом [ID: %d]", house_id);
        else strcat(string, "Слот свободный");
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i+1, string);
    }
    if(p_info[playerid][house_slots] < MAX_HOUSE_PLAYER)
    {
        for(new i = p_info[playerid][house_slots]; i < MAX_HOUSE_PLAYER; i++)
        {
            f(STRING_GLOBAL, "%s"I"[%d]"W" Купить дополнительный слот\n", STRING_GLOBAL, i+1);
        }
    }
    p_temp[playerid][p_listitem_int] = house_type_idx;
    ShowPlayerDialog(playerid, D_HOUSE_PLAYER_LIST, DIALOG_STYLE_LIST, ""I"Дома", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;
}

stock GetPlayerHouseID(playerid, idx = -1)
{
    if(p_info[playerid][key_h_rent] != INVALID_HOUSE_ID) return p_info[playerid][key_h_rent];
    if(idx == -1){
        if(p_info[playerid][active_house_id] == -1)
        {
            SendError(playerid, "Упс, что-то сломалось: [B044]. Напишите на форум, указав как так получилось.");
            return -1;
        }
        return p_info[playerid][key_house][p_info[playerid][active_house_id]];
    }
    return p_info[playerid][key_house][idx];
}

stock SetPlayerHouseID(playerid, house_idx, idx = -1)
{
    if(idx == -1) return p_info[playerid][key_house][p_info[playerid][active_house_id]] = house_idx;
    return p_info[playerid][key_house][idx] = house_idx;
}

ClearOwnerHouse(playerid, house_idx)
{
    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        if(house_idx == GetPlayerHouseID(playerid, i))
        {
            SetPlayerHouseID(playerid, INVALID_HOUSE_ID, i);
            break;
        }
    }
}

GetFreeSlotHouse(playerid)
{
    new count_house;
    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        if(GetPlayerHouseID(playerid, i) == INVALID_HOUSE_ID)
            count_house++;
    }
    if(count_house == p_info[playerid][house_slots])
        return p_info[playerid][house_slots];
    if(count_house == 0) return ALL_BUSY_SLOT_HOUSE;
    return count_house;
}

SetFreeSlotHouse(playerid, house_idx)
{
    for(new i; i < p_info[playerid][house_slots]; i++)
    {
        if(GetPlayerHouseID(playerid, i) == INVALID_HOUSE_ID)
        {
            SetPlayerHouseID(playerid, house_idx, i);
            break;
        }
    }
}

// ~~~~~~~~~~ [ House - The end ] ~~~~~~~~~~ //

// ~~~~~~~~~~ [ Accessories - Start ] ~~~~~~~~~~ //

AccessoriesPlayerList(playerid, acc_dialog_id)
{
    if(p_temp[playerid][BeingInSpace] == true || p_temp[playerid][SpaceFlightStatus] == true) return SendError(playerid, "В космосе нельзя пользоваться аксессуарами.");
    ShowPlayerList(playerid, LIST_ID_PLAYER_ACCESSORIES);
    SetPVarInt(playerid, "ACCESSORIES_LIST:ID", acc_dialog_id);
    return 1;
}

// ~~~~~~~~~~ [ Accessories - The End ] ~~~~~~~~~~ //

// ~~~~~~~~~~ [ Skins - Start ] ~~~~~~~~~~ //

SkinsPlayerList(playerid, skin_dialog_id)
{
    ShowPlayerList(playerid, LIST_ID_PLAYER_SKINS);
    SetPVarInt(playerid, "SKINS_LIST:ID", skin_dialog_id);
    return 1;
}

// ~~~~~~~~~~ [ Skins - The End ] ~~~~~~~~~~ //

// ~~~~~~~~~~ [ Vehicle - Start ] ~~~~~~~~~~ //
#define ALL_BUSY_SLOT_VEHICLE -1

enum
{
    VEHICLE_ID_SELECT = 1,
    VEHICLE_ID_FIND,
    VEHICLE_ID_DELIVERY,
    VEHICLE_ID_MARKET_UNBET
}

VehiclePlayerList(playerid, veh_type_idx)
{
    new max_count = p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1 ? MAX_PLAYER_VEHICLES : 2;
    if(GetFreeSlotVehicle(playerid) == max_count)
    {
        SendError(playerid, "У Вас нет загруженого транспорта.");
        return SendInfo(playerid, "Чтобы загрузить транспорт используйте: /cars.");
    }

    STRING_GLOBAL[0] = EOS;
    new string[144], vehicle_id;
    for(new i; i < max_count; i++)
    {
        string[0] = EOS;
        vehicle_id = GetPlayerVehicleIDEx(playerid, i);
        if(vehicle_id == INVALID_VEHICLE_ID) strcat(string, "Слот свободный");
        else f(string, "%s [ID: %d]", GetVehicleName(vehicle_id), GetVehicleModelEx(vehicle_id));
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i+1, string);
    }
    p_temp[playerid][p_listitem_int] = veh_type_idx;
    ShowPlayerDialog(playerid, D_VEHICLE_PLAYER_LIST, DIALOG_STYLE_LIST, ""I"Загруженный транспорт", STRING_GLOBAL, "Выбрать", "Отмена");
    return 1;
}

stock GetPlayerVehicleIDEx(playerid, idx = -1)
{
    if(idx == -1) idx = p_info[playerid][active_vehicle_id];
    if(p_info[playerid][key_vehicle][idx] != INVALID_VEHICLE_ID &&
        !IsPlayerOwnerVehicle(playerid, p_info[playerid][key_vehicle][idx]))
    {
        veh_info[p_info[playerid][key_vehicle][idx]][v_created_ID] = INVALID_PLAYER_ID;
        p_info[playerid][key_vehicle][idx] = INVALID_VEHICLE_ID;
    }
    return p_info[playerid][key_vehicle][idx];
}

stock SetPlayerVehicleIDEx(playerid, vehicle_idx, idx = -1)
{
    if(idx == -1) idx = p_info[playerid][active_vehicle_id];
    if(vehicle_idx != INVALID_VEHICLE_ID) veh_info[vehicle_idx][v_created_ID] = playerid;
    else
    {
        if(p_info[playerid][key_vehicle][idx] != INVALID_VEHICLE_ID)
            veh_info[p_info[playerid][key_vehicle][idx]][v_created_ID] = INVALID_PLAYER_ID;
    }
    return p_info[playerid][key_vehicle][idx] = vehicle_idx;
}

DestroyPlayerVehicle(playerid, vehicle_idx)
{
    for(new i; i < MAX_PLAYER_VEHICLES; i++)
    {
        if(vehicle_idx == GetPlayerVehicleIDEx(playerid, i))
        {
            SaveVehicle(vehicle_idx);
            SaveVehicleDetails(vehicle_idx);
            DestroyVehicleVEx(vehicle_idx);

            SetPlayerVehicleIDEx(playerid, INVALID_VEHICLE_ID, i);
            break;
        }
    }
}

GetFreeSlotVehicle(playerid)
{
    new count_vehicle, max_count = p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1 ? MAX_PLAYER_VEHICLES : 2;
    for(new i; i < max_count; i++)
    {
        if(GetPlayerVehicleIDEx(playerid, i) == INVALID_VEHICLE_ID)
            count_vehicle++;
    }
    if(count_vehicle == 0) return ALL_BUSY_SLOT_VEHICLE;
    return count_vehicle;
}

SetFreeSlotVehicle(playerid, vehicle_idx)
{
    new max_count = p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1 ? MAX_PLAYER_VEHICLES : 2;
    for(new i; i < max_count; i++)
    {
        if(GetPlayerVehicleIDEx(playerid, i) == INVALID_VEHICLE_ID)
        {
            SetPlayerVehicleIDEx(playerid, vehicle_idx, i);
            break;
        }
    }
}

IsPlayerOwnerVehicle(playerid, vehicleid)
{
    if(vehicleid < 1 || vehicleid == INVALID_VEHICLE_ID || veh_info[vehicleid][v_mysql_id] == INVALID_MYSQL_ID) return false;
    return veh_info[vehicleid][v_owner_id] == p_info[playerid][ID];
}

GetPlayerOwnerNearestVehicleID(playerid, Float:radius = 12.0)
{
    new max_count = p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1 ? MAX_PLAYER_VEHICLES : 2, vehicleid = INVALID_VEHICLE_ID;
    if(GetFreeSlotVehicle(playerid) == max_count) return vehicleid;

    new Float:distance_min = 999.0, Float:w_distance, Float:w_pos_x, Float:w_pos_y, Float:w_pos_z;
    foreach (new v: PlayerVehiclesStream[playerid])
    {
        if( veh_info[v][v_mysql_id] != INVALID_MYSQL_ID &&
            IsPlayerOwnerVehicle(playerid, v) &&
            veh_info[v][v_npoType] == NPO_PLAYERCAR &&
            GetSlotVehicleMarket(veh_info[v][v_mysql_id]) == -1)
        {
            GetVehiclePos(v, w_pos_x, w_pos_y, w_pos_z);
            w_distance = GetPlayerDistanceFromPoint(playerid, w_pos_x, w_pos_y, w_pos_z);
            if(w_distance > radius || w_distance > distance_min) continue;
            vehicleid = v;
            distance_min = w_distance;
        }
    }
    return vehicleid;
}

GetPlayerNearestVehicleID(playerid, Float:radius = 12.0)
{
    new vehicleid = INVALID_VEHICLE_ID;

    new Float:distance_min = 999.0, Float:w_distance, Float:w_pos_x, Float:w_pos_y, Float:w_pos_z;
    foreach (new v: PlayerVehiclesStream[playerid])
    {
        GetVehiclePos(v, w_pos_x, w_pos_y, w_pos_z);
        w_distance = GetPlayerDistanceFromPoint(playerid, w_pos_x, w_pos_y, w_pos_z);
        if(w_distance > radius || w_distance > distance_min) continue;
        vehicleid = v;
        distance_min = w_distance;
    }
    return vehicleid;
}


enum E_PLAYER_VEHICLES_VALUE
{
    E_SLOT_ID,
    E_VEHICLIE_ID
}

GetPlayerVehicleMySQLID(playerid, mysql_id, E_PLAYER_VEHICLES_VALUE:return_value = E_SLOT_ID) // ПРИНИМАЕТ ТОЛЬКО playerid, MYSQL ID автомобиля(!)
{
    //new max_count = p_info[playerid][p_vip] == 3 && p_info[playerid][p_add_vip] == 1 ? MAX_PLAYER_VEHICLES : 2;
    for(new i = MAX_PLAYER_VEHICLES-1; i != -1; i--)
    {
        new vehicleid = GetPlayerVehicleIDEx(playerid, i);
        if(vehicleid != INVALID_VEHICLE_ID && veh_info[vehicleid][v_mysql_id] == mysql_id)
        {
            if(return_value == E_SLOT_ID) return i;
            if(return_value == E_VEHICLIE_ID) return vehicleid;
        }
    }
    return -1;
}

UnLoadPlayerVehicle(playerid, vehicleid = INVALID_VEHICLE_ID)
{
    if(vehicleid == INVALID_VEHICLE_ID)
    {
        for(new i; i < MAX_PLAYER_VEHICLES; i++)
        {
            vehicleid = GetPlayerVehicleIDEx(playerid, i);
            if(vehicleid != INVALID_VEHICLE_ID)
                DestroyPlayerVehicle(playerid, vehicleid);
        }
    }
    else
    {
        DestroyPlayerVehicle(playerid, vehicleid);
        SendAccess(playerid, "Ваше транспортное средство выгружено.");
    }
    return 1;
}

// ~~~~~~~~~~ [ Vehicle - The end ] ~~~~~~~~~~ //

// ==============================================  //
cmd:offer(playerid, params[])
{
    if(GetFreeSlotOffer(playerid) == ALL_FREE_SLOT_OFFER)
        return SendError(playerid, "У Вас нет предложений.");

    STRING_GLOBAL[0] = EOS;
    new string[144], offer_id;
    for(new i; i < MAX_OFFER_PLAYER; i++)
    {
        string[0] = EOS;
        offer_id = GetPlayerOfferID(playerid, i);
        if(offer_id != INVALID_PLAYER_ID && OfferInfo[playerid][timer_offer][i] < timestamp)
        {
            ClearOwnerOffer(playerid, offer_id);
            offer_id = INVALID_PLAYER_ID;
        }
        if(offer_id != INVALID_PLAYER_ID) f(string, "%s [%d]", get_name(offer_id), offer_id);
        else strcat(string, "Слот свободный");
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i+1, string, offer_id);
    }
    ShowPlayerDialog(playerid, D_OFFER_PLAYER_LIST, DIALOG_STYLE_LIST, ""I"Список предложений", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
/*
cmd:biz(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    BizzPlayerList(playerid, BIZZ_ID_SELECT);
    return 1;
}

cmd:houses(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    HousePlayerList(playerid, HOUSE_ID_SELECT);
    return 1;
}*/
