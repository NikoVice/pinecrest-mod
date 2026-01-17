/*
    Author: Vip Uzer
    Flin RolePlay
    (c) 2021
*/
#define MAX_SPARRING 10

enum e_sparring
{
    sPlayerID[2], // игроки
    sBet, // ставка
    //sFightingStyle, // стиль которым будут биться
    sCountRound, // количество раундов
    sRound,
    sCount[2], // Статус боя / round
    sAccessType, // закрытый бой без зрителями или без
    sRoomID // ид зала
}
new SparringData[MAX_SPARRING][e_sparring];

/*
    Тренажёрный зал ЛС 5       772.111999,-3.898649,1000.728820
    Тренажёрный зал СФ 6       774.213989,-48.92429,1000.585937
    Тренажёрный зал ЛВ 7       773.579956,-77.09664,1000.655029
*/
new Float:sparring_pos[3][2][4] =
{
    { // room 1
        {762.7335,12.9444,1001.1639,130.6506},
        {759.3808,9.4737,1001.1639,314.5791}
    },
    { // room 2
        {773.6328,-42.0509,1000.6865,34.1901},
        {762.9823,-31.8013,1000.6865,225.6387}
    },
    { // room 3
        {768.7329,-70.5119,1001.5692,41.3969},
        {764.5529,-66.7192,1001.5692,225.0120}
    }
};

Sparring_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid)
    {
        case D_SPARRING_LIST:
        {
            if(!response) return 1;
            ShowSparringInfo(playerid, listitem);
            return 1;
        }
        case D_SPARRING_SETTING:
        {
            if(!response) return 1;
            new idx = p_temp[playerid][SparringID];
            if(idx == -1) return SendError(playerid, "Произошла не известная ошибка, повторите попытку.");
            switch(listitem)
            {
                case 0: ShowSparringInfo(playerid, idx);
                case 1: ShowPlayerDialog(playerid, D_SPARRING_SETTING_BET, DIALOG_STYLE_INPUT, "Ставка", ""W"Введите ставку от 0$ до 100 000$.", "Выбрать", "Отмена");
                //case 2: ShowPlayerDialog(playerid, D_SPARRING_SETTING_STYLE, DIALOG_STYLE_LIST, "Стиль боя", ""I"[1]"W" Боксерский\n"I"[2]"W" Кунг-Фу\n"I"[3]"W" Тхеквондо\n"I"[4]"W" Обычный", "Выбрать", "Отмена");
                case 2: ShowPlayerDialog(playerid, D_SPARRING_SETTING_RAUNDS, DIALOG_STYLE_INPUT, "Количество раундов", ""W"Введите количество раундов от 1 до 5.", "Выбрать", "Отмена");
                case 3: ShowPlayerDialog(playerid, D_SPARRING_SETTING_ACCESS, DIALOG_STYLE_MSGBOX, "Ставка", ""W"Выберите тип боя с зрителями(открытый) или без(закрытый).", "Открытый", "Закрытый");
                case 4: ShowPlayerDialog(playerid, D_SPARRING_SETTING_ROOM, DIALOG_STYLE_LIST, "Номер зала", ""I"[1]"W" Зал #1\n"I"[2]"W" Зал #2\n"I"[3]"W" Зал #3", "Выбрать", "Отмена");
                case 5:
                {
                    new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
                    SetFreeSlotOffer(SparringData[idx][sPlayerID][i], playerid, OFFER_ID_START_SPARRING);
                }
            }
            return 1;
        }
        case D_SPARRING_SETTING_ROOM:
        {
            if(!response) return 1;
            new idx = p_temp[playerid][SparringID];
            if(idx == -1) return SendError(playerid, "Произошла не известная ошибка, повторите попытку.");
            SparringData[idx][sRoomID] = listitem;
            SendAccess(playerid, "Вы установили зал №%d.", listitem+1);
            new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
            SendInfo(SparringData[idx][sPlayerID][i], "%s установил зал №%d.", get_name(playerid), listitem+1);
            return 1;
        }
        case D_SPARRING_SETTING_ACCESS:
        {
            new idx = p_temp[playerid][SparringID];
            if(idx == -1) return SendError(playerid, "Произошла не известная ошибка, повторите попытку.");
            SparringData[idx][sAccessType] = response;
            SendAccess(playerid, "Вы установили тип боя %s.", SparringData[idx][sAccessType] ? "Открытый" : "Закрытый");
            new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
            SendInfo(SparringData[idx][sPlayerID][i], "%s установил тип боя %s.", get_name(playerid), SparringData[idx][sAccessType] ? "Открытый" : "Закрытый");
            return 1;
        }
        case D_SPARRING_SETTING_RAUNDS:
        {
            if(!response) return 1;
            new idx = p_temp[playerid][SparringID];
            if(idx == -1) return SendError(playerid, "Произошла не известная ошибка, повторите попытку.");
            new value = strval(inputtext);
            if(!(1 <= value <= 5) || !strlen(inputtext)) return ShowPlayerDialog(playerid, D_SPARRING_SETTING_RAUNDS, DIALOG_STYLE_INPUT, "Количество раундов", ""W"Введите количество раундов от 1 до 5.", "Выбрать", "Отмена");
            SparringData[idx][sCountRound] = value;
            SendAccess(playerid, "Вы установили количество раундов %d.", value);
            new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
            SendInfo(SparringData[idx][sPlayerID][i], "%s установил количество раундов %d.", get_name(playerid), value);
            return 1;
        }
        /*
        case D_SPARRING_SETTING_STYLE:
        {
            if(!response) return 1;
            new idx = p_temp[playerid][SparringID];
            if(idx == -1) return SendError(playerid, "Произошла не известная ошибка, повторите попытку.");
            new style_stye_name[][] = {"Обычный", "Боксерский", "Кунг-Фу", "Тхеквондо"};
            SparringData[idx][sFightingStyle] = listitem;
            SendAccess(playerid, "Вы установили стиль боя %s.", style_stye_name[listitem]);
            new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
            SendInfo(SparringData[idx][sPlayerID][i], "%s установил стиль боя %s.", get_name(playerid), style_stye_name[listitem]);
            return 1;
        }
        */
        case D_SPARRING_SETTING_BET:
        {
            if(!response) return 1;
            new idx = p_temp[playerid][SparringID];
            if(idx == -1) return SendError(playerid, "Произошла не известная ошибка, повторите попытку.");
            new value = strval(inputtext);
            if(!(0 <= value <= 100_000) || !strlen(inputtext)) return ShowPlayerDialog(playerid, D_SPARRING_SETTING_BET, DIALOG_STYLE_INPUT, "Ставка", ""W"Введите ставку от 0$ до 100 000$.", "Выбрать", "Отмена");
            SparringData[idx][sBet] = value;
            SendAccess(playerid, "Вы установили ставку %d$.", value);
            new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
            SendInfo(SparringData[idx][sPlayerID][i], "%s установил ставку %d$.", get_name(playerid), value);
            return 1;
        }
        case D_SPARRING_OFFER:
        {
            if(!response) return 1;
            new value = strval(inputtext);
            if(!(0 <= value < MAX_PLAYERS) || !strlen(inputtext)) return ShowPlayerDialog(playerid, D_SPARRING_OFFER, DIALOG_STYLE_LIST, "Предложить бой", ""W"ВВедите ID игрока которому хотите предложить бой.", "Выбрать", "Отмена");
            new tmp_str[7];
            format(tmp_str, 7, "%d", value);
            callcmd::sparring(playerid, tmp_str);
            return 1;
        }
        case D_SPARRING_WATCH:
        {
            if(!response) return 1;

            return 1;
        }
    }
    return 0;
}

EndSparring(idx, bool:check_count = true)
{
    new bizz_id, playerid;
    for(new i; i < 2; i++)
    {
        playerid = SparringData[idx][sPlayerID][i];
        if(playerid != INVALID_PLAYER_ID)
        {
            bizz_id = GetPVarInt(playerid, "bID");
            SetPlayerInterior(playerid, 5);
            SetPlayerVirtualWorld(playerid, b_info[bizz_id][_world]);
            SetPlayerPos(playerid, 770.1439,7.0372,1000.7120);
            SetPlayerFacingAngle(playerid, 144.1477);
            SetCameraBehindPlayer(playerid);
            SetPlayerSkinEx(playerid);
            if((p_info[playerid][member] != 0 && p_info[playerid][fwork] == true)) SetPlayerColor(playerid, fraction_color[p_info[playerid][member]]);
            else SetPlayerColor(playerid,  fraction_color[0]);
            if(p_info[playerid][admin] > 0) SetPlayerColor(playerid, 0xFFFFFF00);
            if(p_info[playerid][pstyle][0]) SetPlayerFightingStyle(playerid, p_info[playerid][pstyle][0]);
            else SetPlayerFightingStyle(playerid, 4);
        }
        p_temp[playerid][SparringID] = -1;
    }
    if(check_count == true)
    {
        if(SparringData[idx][sCount][0] > SparringData[idx][sCount][1])
        {
            SetPlayerMoney(SparringData[idx][sPlayerID][0], (SparringData[idx][sBet]*2)*9/10, true, "выиграл бой");
            SendAccess(SparringData[idx][sPlayerID][0], "Поздравляем, вы выиграли бой.");
            SendAccess(SparringData[idx][sPlayerID][1], "Сожалеем, вы проиграли бой.");
        }
        else if(SparringData[idx][sCount][1] > SparringData[idx][sCount][0])
        {
            SetPlayerMoney(SparringData[idx][sPlayerID][1], (SparringData[idx][sBet]*2)*9/10, true, "выиграл бой");
            SendAccess(SparringData[idx][sPlayerID][1], "Поздравляем, вы выиграли бой.");
            SendAccess(SparringData[idx][sPlayerID][0], "Сожалеем, вы проиграли бой.");
        }
        else
        {
            SetPlayerMoney(SparringData[idx][sPlayerID][0], SparringData[idx][sBet]*9/10, true, "ничья бой");
            SetPlayerMoney(SparringData[idx][sPlayerID][1], SparringData[idx][sBet]*9/10, true, "ничья бой");
            SendAccess(SparringData[idx][sPlayerID][1], "Ничья, бой закончен.");
            SendAccess(SparringData[idx][sPlayerID][0], "Ничья, бой закончен.");
        }
        if(b_info[bizz_id][_prod] >= 25)
        {
            b_info[bizz_id][_prod] -= 25;
            b_info[bizz_id][_bank] += SparringData[idx][sBet]*3/100;
            AddMafiaBank(bizz_id, SparringData[idx][sBet]*1/100);

            biz_finka[bizz_id] += SparringData[idx][sBet]*3/100;
            UpdateIntForFinanceBiz(bizz_id, SparringData[idx][sBet]*3/100);
        }
    }
    SparringData[idx][sPlayerID][0] =
    SparringData[idx][sPlayerID][1] = INVALID_PLAYER_ID;
}

CancelSparring(idx)
{
    new playerid;
    for(new i; i < 2; i++)
    {
        playerid = SparringData[idx][sPlayerID][i];
        if(IsPlayerConnected(playerid))
        {
            if(SparringData[idx][sRound] >= 1)
            {
                SetPlayerInterior(playerid, 5);
                SetPlayerVirtualWorld(playerid, b_info[GetPVarInt(playerid, "bID")][_world]);
                SetPlayerPos(playerid, 770.1439,7.0372,1000.7120);
                SetPlayerFacingAngle(playerid, 144.1477);
                SetCameraBehindPlayer(playerid);
                if((p_info[playerid][member] != 0 && p_info[playerid][fwork] == true)) SetPlayerColor(playerid, fraction_color[p_info[playerid][member]]);
                else SetPlayerColor(playerid,  fraction_color[0]);
                if(p_info[playerid][admin] > 0) SetPlayerColor(playerid, 0xFFFFFF00);
                if(p_info[playerid][pstyle][0]) SetPlayerFightingStyle(playerid, p_info[playerid][pstyle][0]);
                else SetPlayerFightingStyle(playerid, 4);
            }
            SendInfo(playerid, "Бой отменен по причине: один из игроков покинул центр мероприятий или игру.");
        }
        p_temp[playerid][SparringID] = -1;
        SparringData[idx][sPlayerID][i] = INVALID_PLAYER_ID;
    }
}

Sparring_OnGameModeInit()
{
    for(new i = MAX_SPARRING-1; i != -1; i--)
    {
        SparringData[i][sPlayerID][0] =
        SparringData[i][sPlayerID][1] = INVALID_PLAYER_ID;
        InitSparring(i);
    }
}

InitSparring(idx)
{
    SparringData[idx][sBet] = 1000;
    SparringData[idx][sCountRound] = 1;
    //SparringData[idx][sFightingStyle] = 0;
    SparringData[idx][sAccessType] =
    SparringData[idx][sRoomID] =
    SparringData[idx][sCount][0] =
    SparringData[idx][sCount][1] =
    SparringData[idx][sRound] = 0;
}

StartSparringRound(idx, round)
{
    SparringData[idx][sRound] = round;
    new playerid,
        map_id = SparringData[idx][sRoomID];
    for(new i; i < 2; i++)
    {
        playerid = SparringData[idx][sPlayerID][i];
        if(playerid != INVALID_PLAYER_ID)
        {
            SetPlayerPos(playerid, sparring_pos[map_id][i][0], sparring_pos[map_id][i][1], sparring_pos[map_id][i][2]+0.2);
            SetPlayerFacingAngle(playerid, sparring_pos[map_id][i][3]);
            SetPlayerVirtualWorld(playerid, SparringData[idx][sPlayerID][0]+1000);
            SetPlayerInterior(playerid, map_id+5);
            SetPlayerArmedWeapon(playerid, 0);
            ResetPlayerWeapons(playerid);
            //SetPlayerFightingStyle(playerid, SparringData[idx][sFightingStyle]+4);
            SetPlayerSkin(playerid, 80+i);
            SetPlayerHealth(playerid, 100.0);

            STRING_GLOBAL[0] = EOS;
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "~r~Round %d/%d", SparringData[idx][sRound], SparringData[idx][sCountRound]);
            GameTextForPlayer(playerid, STRING_GLOBAL, 1000, 3);
        }
    }
}

ShowSparrings(playerid)
{
    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_SPARRING; i++)
    {
        if(SparringData[i][sPlayerID][0] == INVALID_PLAYER_ID || SparringData[i][sPlayerID][1] == INVALID_PLAYER_ID)
            f(STRING_GLOBAL, "%s"I"[%d]"W" Слот свободен\n", STRING_GLOBAL, i+1);
        else
            f(STRING_GLOBAL, "%s"I"[%d]"W" %s VS %s\n", STRING_GLOBAL, i+1,
                get_name(SparringData[i][sPlayerID][0]), get_name(SparringData[i][sPlayerID][1]));
    }
    ShowPlayerDialog(playerid, D_SPARRING_LIST, DIALOG_STYLE_LIST, "Текущие бои", STRING_GLOBAL, "Выбрать", "Отмена");
}

ShowSparringInfo(playerid, idx)
{
    if(p_temp[playerid][SparringID] == idx)
    {
        new i = SparringData[idx][sPlayerID][0] == playerid ? 1 : 0;
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, //"W"Стиль боя: "I"%s\n
            ""W"Противник: "I"%s\n\
            "W"Ставка: "I"%d$\n\
            "W"Количество раундов: "I"%d\n\
            "W"Бой: "I"%s\n\
            "W"Зал: "I"№%d\n\
            "E"- Предложить начать бой -",
            get_name(SparringData[idx][sPlayerID][i]), SparringData[idx][sBet],// style_stye_name[SparringData[idx][sFightingStyle]],
            SparringData[idx][sCountRound], SparringData[idx][sAccessType] ? "Открытый" : "Закрытый", SparringData[idx][sRoomID]+1);
        ShowPlayerDialog(playerid, D_SPARRING_SETTING, DIALOG_STYLE_LIST, "Настройки боя", STRING_GLOBAL, "Выбрать", "Отмена");
    }
    else
    {
        if(SparringData[idx][sPlayerID][0] == INVALID_PLAYER_ID || SparringData[idx][sPlayerID][1] == INVALID_PLAYER_ID) return ShowPlayerDialog(playerid, D_SPARRING_OFFER, DIALOG_STYLE_INPUT, "Предложить бой", ""W"Введите ID игрока которому хотите предложить бой.", "Выбрать", "Отмена");
        if(!SparringData[idx][sAccessType])
        {
            ShowSparrings(playerid);
            return SendError(playerid, "Бой закрыт от зрителей.");
        }
        return SendError(playerid, "В доработке.");
        //ShowPlayerDialog(playerid, D_SPARRING_WATCH, DIALOG_STYLE_MSGBOX, "Бой", "Вы хотите посмотреть данный бой?", "Выбрать", "Отмена");
    }
    return 1;
}

GetFreeSlotSparring()
{
    for(new i = MAX_SPARRING-1; i != -1; i--)
    {
        if(SparringData[i][sPlayerID][0] == INVALID_PLAYER_ID)
            return i;
    }
    return -1;
}

CMD:sparring(playerid, params[])
{
    new bizz_id = GetPVarInt(playerid, "bID");
    if(GetPlayerInterior(playerid) != 5 ||
        GetPlayerVirtualWorld(playerid) != b_info[bizz_id][_world] ||
        b_info[bizz_id][_tip] != B_GYM)
        return SendError(playerid, "Доступно только в спортзале.");
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /sparring [id игрока]");
    if(params[0] == INVALID_PLAYER_ID || params[0] == playerid)
        return SendError(playerid, "Игрок не найден.");
    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return 1;
    if(GetPVarType(params[0],"BoneStol_ID") == PLAYER_VARTYPE_INT)
        return 1;

    SendAccess(playerid, "Вы предложили %s [%d] провести бой.", get_name(params[0]), params[0]);
    SendInfo(params[0], "%s [%d] предложил Вам провести бой.", get_name(playerid), playerid);

    SetFreeSlotOffer(params[0], playerid, OFFER_ID_SPARRING);
    return 1;
}

CMD:startsparring(playerid, params[])
{
    new bizz_id = GetPVarInt(playerid, "bID");
    if(GetPlayerInterior(playerid) != 5 ||
        GetPlayerVirtualWorld(playerid) != b_info[bizz_id][_world] ||
        b_info[bizz_id][_tip] != B_GYM)
        return SendError(playerid, "Доступно только в спортзале.");
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /startsparring [id игрока]");
    if(params[0] == INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок не найден.");
    if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return SendError(playerid, "Игрок слишком далеко от Вас.");
    if(pSpectateId[params[0]] != INVALID_PLAYER_ID)
        return 1;
    if(GetPVarType(params[0],"BoneStol_ID") == PLAYER_VARTYPE_INT)
        return 1;
    if(p_temp[playerid][SparringID] != p_temp[params[0]][SparringID] || p_temp[playerid][SparringID] == -1)
        return 1;
    SetFreeSlotOffer(params[0], playerid, OFFER_ID_START_SPARRING);
    return 1;
}
