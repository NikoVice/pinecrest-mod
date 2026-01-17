new limit_mayor_transfer_money = 500000; // Лимит перевода денежных средств в день;

CMD:unarrest(playerid, params[])
{
    if(p_info[playerid][member] != MAYOR_LS && p_info[playerid][Lic][LIC_LAWYER] == 0) return SendError(playerid, "Вы не работаете в мэрии, либо у Вас нет лицензии на адвокатские услуги.");
    else if(p_info[playerid][member] == MAYOR_LS && p_info[playerid][Lic][LIC_LAWYER] == 0 && p_info[playerid][rang] != 3) return SendError(playerid, "Вы не адвокат.");
    else if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /unarrest [id игрока]");
    else if(!IsPlayerStream(5.0, playerid, params[0]) || pSpectateId[params[0]] != INVALID_PLAYER_ID) return SendError(playerid, "Игрок слишком далеко от Вас.");
    else if(p_info[params[0]][jail] == 0) return SendError(playerid, "Игрок не находится в тюрьме.");
    else if(p_info[params[0]][jail] == 5 || p_info[params[0]][jail] == 6) return SendError(playerid, "Этого игрока нельзя выпустить.");
    else if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");

    new price;
    switch(p_info[params[0]][level])
    {
        case 1 .. 5: price = 10000;
        case 6 .. 15: price = 25000;
        case 16 .. 30: price = 50000;
        default: price = 100000;
    }

    SendAccess(playerid, "Вы предложили %s [%d] выйти из тюрьмы за %d$.", get_name(params[0]), params[0], price);
    SendInfo(params[0], "%s [%d] предложил Вам выйти из тюрьмы за %d$.", get_name(playerid), playerid, price);

    SetFreeSlotOffer(params[0], playerid, OFFER_ID_UN_ARREST, price);
    return 1;
}

CMD:selllawyerlic(playerid, params[])
{
    if(p_info[playerid][member] != MAYOR_LS || p_info[playerid][rang] < 9) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /selllawyerlic [id игрока]");
    if(!IsPlayerConnected(params[0])) return true;
    if(!IsPlayerStream(3.0, playerid, params[0])) return true;
    if(p_info[params[0]][Lic][LIC_LAWYER] == 2) return SendError(playerid, "У игрока ЧС лицензии на адвокатские услуги.");
    if(p_info[params[0]][Lic][LIC_LAWYER] == 1) return SendError(playerid, "У игрока уже есть лицензия на адвокатские услуги.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetPVarInt(params[0],"BoneStol_ID")) return 1;
    if(p_info[params[0]][level] < 15) return SendError(playerid, "У игрока нет 15 уровня.");

    SendAccess(playerid, "Вы предложили %s [%d] приобрести лицензию на адвокатские услуги за 250000$.", get_name(params[0]), params[0]);
    SendInfo(params[0], "%s [%d] предложил Вам приобрести лицензию на адвокатские услуги за 250000$.", get_name(playerid), playerid);

    SetFreeSlotOffer(params[0], playerid, OFFER_ID_BUY_LAWYER_LIC, 250_000);
    return 1;
}

CMD:atakelawyerlic(playerid, params[])
{
    if(p_info[playerid][admin] < 4) return 1;
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /atakelawyerlic [id игрока]");
    if(params[0] == INVALID_PLAYER_ID) return true;
    if(!IsPlayerStream(3.0, playerid, params[0])) return true;
    if(p_info[params[0]][Lic][LIC_LAWYER] == 2) return SendError(playerid, "У игрока ЧС лицензии на адвокатские услуги.");
    if(p_info[params[0]][Lic][LIC_LAWYER] == 0) return SendError(playerid, "У игрока уже есть лицензия на адвокатские услуги.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");

    SendAccess(playerid, "Вы изьяли у %s лицензию на адвокатские услуги.", get_name(params[0]));
    SendInfo(params[0], "%s изьял у Вас лицензию на адвокатские услуги.", get_name(playerid));

    p_info[params[0]][Lic][LIC_LAWYER] = 0;
    p_info[params[0]][Lic_Warn][LIC_LAWYER] = 0;
    p_info[params[0]][Lic_Time][LIC_LAWYER] = 0;
    OnPlayerUpdateLicData(params[0]);

    // Hardi_Devidson[1](192.168.1.1 M/0.0.1-patch1)[$112345] продал Jeffrey_Collinz[0](127.0.0.1 PC/0.3.7-R2)[$154321] лицензию на оружие за 130000$
    Log(LOG_player, INFO, "%s[%d](%s %s)[$%d] изьял у %s[%d](%s %s)[$%d] лицензию на адвокатские услуги | #ADMIN",
        get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", p_info[playerid][cash],
        get_name(params[0]), p_info[params[0]][ID], p_temp[params[0]][session_IP], IsPlayerMobile(params[0]) ? "Mobile": "PC", p_info[params[0]][cash]);
    return 1;
}

CMD:givepassport(playerid, params[])
{
    if(p_info[playerid][member] != MAYOR_LS || p_info[playerid][rang] != 4) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    if(sscanf(params, "u", params[0])) return SendInfo(playerid, "Используйте: /givepassport [id игрока]");
    if(!IsPlayerConnected(params[0])) return true;
    if(!IsPlayerStream(3.0, playerid, params[0])) return true;
    if(p_info[params[0]][passport] == 1) return CheckPlayerMission(params[0], START_PASS), SendError(playerid, "У игрока уже есть паспорт.");
    if(params[0] == playerid) return SendError(playerid, "Вы ввели свой ID.");
    if(GetPVarInt(params[0],"BoneStol_ID")) return 1;

    SendAccess(playerid, "Вы предложили %s [%d] получить паспорт.", get_name(params[0]), params[0]);
    SendInfo(params[0], "%s [%d] предложил Вам получить паспорт.", get_name(playerid), playerid);

    SetFreeSlotOffer(params[0], playerid, OFFER_ID_GIVE_PASSPORT);
    return 1;
}

/*CMD:fmembers(playerid, params[])
{
    if(p_info[playerid][member] == MAYOR_LS && (p_info[playerid][rang] >= 5 && p_info[playerid][rang] <= 8))
    {
        new frac_idx[4][5] = {
            {6, 18, 24, 0, 0}, // Министр кулютуры - Радиоцентры;
            {15, 16, 17, 0, 0}, // Министр здравоохранения - Больницы;
            {5, 20, 0, 0, 0}, // Министр обороны - Армии;
            {1, 2, 3, 4, 25} // Генеральный прокурор - Полиции и ФБР;
        };

        if(sscanf(params, "i", params[0]))
        {
            SendInfo(playerid, "Используйте: /fmembers [id фракции]");

            new str[128];
            for(new i = 0; i < 5; i++)
            {
                if(frac_idx[p_info[playerid][rang] - 5][i] == 0) continue;
                format(str, sizeof(str), "%s%d - %s ", str, frac_idx[p_info[playerid][rang] - 5][i], GetFractionName(frac_idx[p_info[playerid][rang]-5][i]));
            }
            SendInfo(playerid, str);
            return 1;
        }

        new idx = -1;
        for(new i = 0; i < 5; i++)
        {
            if(frac_idx[p_info[playerid][rang] - 5][i] == 0) continue;
            if(frac_idx[p_info[playerid][rang] - 5][i] == params[0])
            {
                idx = i;
                break;
            }
        }
        if(idx == -1) return SendError(playerid, "Вы ввели неверный ID фракции.");

        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Члены %s онлайн:\n", GetFractionName(params[0]));

        new status_work[16];
        foreach(new i: gFactionPlayers[params[0]])
        {
            if(p_info[i][admin] > 0 || params[0] != p_info[i][member]) continue;
            status_work[0] = EOS;
            if(p_info[i][fwork] == true && (gos(i) || GetFactionType(p_info[i][member]) == FACTION_TYPE_SNN)) status_work = "[На работе]";
            format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"%s%s [%d] ранг: %s [%d] | Пред.: %d/3 | %s\n", STRING_GLOBAL, get_name(i), i,  GetPlayerFractionRangName(i), p_info[i][rang], p_info[i][fwarn], status_work);
        }
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Состав онлайн", STRING_GLOBAL, "Закрыть", "");
    } else SendError(playerid, "Вы не можете пользоваться этой командой.");
    return 1;
}*/

ShowMayorTransferMoney(playerid)
{
    if(p_info[playerid][leader] != MAYOR_LS) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    STRING_GLOBAL[0] = EOS, STRING_MIN[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
    Состояние казны: "I"%d$."W"\n\
    Сегодня можно перевести: "I"%d$."W"\n\n", GetFractionWarehouse(p_info[playerid][member], fwMoney), limit_mayor_transfer_money);

    for(new i = 0; i < MAX_FRACTIONS; i++)
    {
        if(FractionsData[i][fType] != FACTION_TYPE_GOS && FractionsData[i][fType] != FACTION_TYPE_SNN) continue;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" %s. Состояние склада: %d$.\n", i, GetFractionName(i), GetFractionWarehouse(i, fwMoney));
        strcat(STRING_GLOBAL, STRING_MIN);
    }

    strcat(STRING_GLOBAL, "\nВведите ID организации и количество денежных средств через запятую:\n\n\
    Пример: "I"1, 100000");

    ShowPlayerDialog(playerid, D_MAYOR_TRANSFER_MONEY, DIALOG_STYLE_INPUT, ""I"Перевод денежных средств на склад организации", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
