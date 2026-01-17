ShowVideoCards(playerid, type, idx = -1)
{
    new houseId;
    if(type < VIDEO_CARDS_TYPE_BANK)
    {
        houseId = p_temp[playerid][p_house_id] = GetHouseGameID(playerid);
        if(houseId == INVALID_HOUSE_ID)
            return SendError(playerid, "Код ошибки: 1009 (Обратитесь к администрации)");
        if(h_info[houseId][h_user_id] != p_info[playerid][ID])
            return SendError(playerid, "Вы не владелец дома.");
        if(houseId+50 != GetPlayerVirtualWorld(playerid))
            return SendError(playerid, "Управлять видеокартами и просматривать их можно только находясь в подвале.");
        if(h_info[houseId][h_improve][BASEMENT] == 0) return SendError(playerid, "В доме нет подвала, приобретите его в меню улучшений дома.");
        if(p_info[playerid][key_h_rent] != -1) return SendError(playerid, "Управлять видеокартами и просматривать их может только владелец дома.");
    }

    switch(type)
    {
        case VIDEO_CARDS_TYPE_ALL: // Обзор всех видеокарт;
        {
            new count[4];
            STRING_GLOBAL = "Стойка | Полка | Состояние\tПрибыль BTC | Налог\tУровень\tОхлаждение\n";
            for(new i = 1; i <= totalvideocards; i++)
            {
                if(VideoCardsInfo[i][vcHouseIDx] != houseId) continue;
                f(STRING_GLOBAL, "%sС: %d | П: %d | %s\t%f BTC | %d$\t%d\t%.2f%%\n", STRING_GLOBAL,
                count[0] + 1, count[1] + 1, VideoCardsInfo[i][vcStatus] == 0 ? "{"#cLIGHTRED"}На паузе"W"": "{"#cGREEN"}Работает"W"",
                VideoCardsInfo[i][vcBitcoin], VideoCardsInfo[i][vcTax], VideoCardsInfo[i][vcLevel], VideoCardsInfo[i][vcCoolant]);
                count[1]++, count[3]++;
                if(count[1] == 4) count[0]++, count[1] = 0;
            }
            if(count[3] == 0) return SendError(playerid, "Ничего не найдено.");
            ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Обзор всех видеокарт", STRING_GLOBAL, "ОК", "");
        }
        case VIDEO_CARDS_TYPE_RACK: // Стойка;
        {
            new count[4], Float:vc_level;
            STRING_GLOBAL = "Стойка | Полка | Состояние\tПрибыль BTC | Налог\tУровень\tОхлаждение\n";
            for(new i = 1; i <= totalvideocards; i++)
            {
                if(VideoCardsInfo[i][vcHouseIDx] != houseId) continue;
                if(count[0] == idx)
                {
                    vc_level = VideoCardsInfo[i][vcLevel];
                    f(STRING_GLOBAL, "%sС: %d | П: %d | %s\t%f BTC | %d$\t%.0f ({"#cGREEN"}+%.3f BTC/час"W")\t%.2f%%\n", STRING_GLOBAL,
                    count[0] + 1, count[1] + 1, VideoCardsInfo[i][vcStatus] == 0 ? "{"#cLIGHTRED"}На паузе"W"": "{"#cGREEN"}Работает"W"",
                    VideoCardsInfo[i][vcBitcoin], VideoCardsInfo[i][vcTax], vc_level, vc_level * 0.03, VideoCardsInfo[i][vcCoolant]);
                    p_temp[playerid][p_listitem][count[3]] = i;
                    count[3]++;
                }
                count[1]++;
                if(count[1] == 4) count[0]++, count[1] = 0;
            }
            if(!count[3]) return SendError(playerid, "Ничего не найдено.");

            p_temp[playerid][p_listitem][count[3]] = -1;
            p_temp[playerid][p_listitem_int] = count[3];

            new iTax;
            for(new i = p_temp[playerid][p_listitem_int]-1; i != -1; i--)
                iTax += VideoCardsInfo[p_temp[playerid][p_listitem][i]][vcTax];
            f(STRING_GLOBAL, "%s"I"[-] "W"Оплатить все налоги на видеокарты: "I"%d$\n", STRING_GLOBAL, iTax);

            new iBTC;
            for(new i = p_temp[playerid][p_listitem_int]-1; i != -1; i--)
                iBTC += floatround(VideoCardsInfo[p_temp[playerid][p_listitem][i]][vcBitcoin], floatround_floor);
            f(STRING_GLOBAL, "%s"I"[-] "W"Вывести все биткоины: "I"%d BTC", STRING_GLOBAL, iBTC);

            ShowPlayerDialog(playerid, D_VC_RACK, DIALOG_STYLE_TABLIST_HEADERS, ""I"Управление стойкой", STRING_GLOBAL, "Далее", "Отмена");
            p_temp[playerid][vc_rack] = idx;
        }
        case VIDEO_CARDS_TYPE_CONTROL: // Управление видеокартой;
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "\
            "I"[1]"W" %s\n\
            "I"[2]"W" Забрать прибыль (%f BTC)\n\
            "I"[3]"W" Оплатить налог (%d$)\n\
            "I"[4]"W" Договор с электростанцией (%d$ в час)\n\
            "I"[5]"W" Залить охлаждающую жидкость\n\
            "I"[6]"W" Улучшить видеокарту\n\
            "I"[7]"W" Информация о майнинге",
            VideoCardsInfo[idx][vcStatus] == 0 ? "Запустить видеокарту" : "Остановить видеокарту",
            VideoCardsInfo[idx][vcBitcoin],
            VideoCardsInfo[idx][vcTax],
            (b_info[VideoCardsInfo[idx][vcBizIDx]][_till] * POWER_STATION_PRICE) * VideoCardsInfo[idx][vcLevel]);
            ShowPlayerDialog(playerid, D_VC_CONTROL, DIALOG_STYLE_LIST, ""I"Управление видеокартой", STRING_GLOBAL, "Далее", "Отмена");
            p_temp[playerid][vc_idx] = idx;
        }
        case VIDEO_CARDS_TYPE_BITCOIN: // Снять Bitcoin;
        {
            if(VideoCardsInfo[idx][vcTax] != 0) return ShowVideoCards(playerid, VIDEO_CARDS_TYPE_CONTROL, idx), SendError(playerid, "На выбранной видеокарте есть неоплаченный налог.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"На выборанной видеокарте сейчас добыто: "I"%f BTC."W"\n\n\
            Выводить можно только целую часть прибыли, сейчас можно\n\
            вывести: "I"%d BTC."W"\n\n\
            Вы действительно хотите вывести BTC?", VideoCardsInfo[idx][vcBitcoin], floatround(VideoCardsInfo[idx][vcBitcoin], floatround_floor));
            ShowPlayerDialog(playerid, D_VC_BITCOIN, DIALOG_STYLE_MSGBOX, ""I"Забрать прибыль", STRING_GLOBAL, "Да", "Нет");
        }
        case VIDEO_CARDS_TYPE_TAX: // Оплатить налог;
        {
            if(VideoCardsInfo[idx][vcTax] == 0) return ShowVideoCards(playerid, VIDEO_CARDS_TYPE_CONTROL, idx), SendError(playerid, "На выбранной видеокарте нет неоплаченого налога.");
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"На выборанной видеокарте сейчас налог: "I"%d$."W"\n\n\
            Вы действительно хотите оплатить налог?", VideoCardsInfo[idx][vcTax]);
            ShowPlayerDialog(playerid, D_VC_TAX, DIALOG_STYLE_MSGBOX, ""I"Оплатить налог", STRING_GLOBAL, "Да", "Нет");
        }
        case VIDEO_CARDS_TYPE_POWER_STATION:
        {
            if(VideoCardsInfo[idx][vcTax] != 0) return ShowVideoCards(playerid, VIDEO_CARDS_TYPE_CONTROL, idx), SendError(playerid, "На данной видеокарте есть налог, оплатите его.");
            new count;
            STRING_GLOBAL[0] = EOS;
            for(new i; i < totalbizz; i++)
            {
                if(b_info[i][b_mysql_id] == INVALID_MYSQL_ID) continue;
                if(b_info[i][_tip] != B_POWER_STATION) continue;
                f(STRING_GLOBAL, "%s"I"[%d]"W" %s (%d$ в час)\n", STRING_GLOBAL, count + 1, b_info[i][_name], b_info[i][_till] * POWER_STATION_PRICE * VideoCardsInfo[idx][vcLevel]);
                p_temp[playerid][p_listitem][count] = i;
                count++;
            }
            ShowPlayerDialog(playerid, D_VC_POWER_STATION, DIALOG_STYLE_LIST, ""I"Выбор электростанции", STRING_GLOBAL, "Далее", "Отмена");
        }
        case VIDEO_CARDS_TYPE_UPGRADE:
        {
            if(VideoCardsInfo[idx][vcLevel] == 10) return ShowVideoCards(playerid, VIDEO_CARDS_TYPE_CONTROL, idx), SendError(playerid, "Данная видеокарта максимального уровня.");
            new Float:vc_btc = VideoCardsInfo[idx][vcLevel] * 0.03;
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            На данный момент уровень видеокарты: "I"%d"W"\n\
            За один час работы приносит: "I"%f BTC."W"\n\n\
            Чем выше уровень производительности, тем больше BTC поступает в час.\n\
            Для повышения производительности требуется смазка для разгона видеокарты,\n\
            её можно приобрести на центральном рынке или скрафтить в подвале дома.\n\n\
            Шанс вероятности улучшения видеокарты:\n\
            На 1-ом уровне: 90%%\n\
            На 2-ом уровне: 70%%\n\
            На 3-ом уровне: 60%%\n\
            На 4-ом уровне: 50%%\n\
            На 5-ом уровне: 40%%\n\
            На 6-ом уровне: 30%%\n\
            На 7-ом уровне: 20%%\n\
            На 8-ом уровне: 10%%\n\
            На 9-ом уровне: 5%%\n\n\
            У Вас "I"%d"W" смазок для разгона видеокарты.\n\n\
            Вы хотите улучшить видеокарту?", VideoCardsInfo[idx][vcLevel], vc_btc, GetInventoryAmount(playerid, 708));
            ShowPlayerDialog(playerid, D_VC_UPGRADE, DIALOG_STYLE_MSGBOX, ""I"Улучшение видеокарты", STRING_GLOBAL, "Да", "Нет");
        }
        case VIDEO_CARDS_TYPE_HELP:
        {
            STRING_GLOBAL[0] = EOS;
            for(new i; i < sizeof(VideoCardsInfoList); i++) strcat(STRING_GLOBAL, VideoCardsInfoList[i]);
            ShowPlayerDialog(playerid, D_VC_HELP, DIALOG_STYLE_MSGBOX, ""I"Майнинг ферма", STRING_GLOBAL, "Далее", "Отмена");
            return 1;
        }
        case VIDEO_CARDS_TYPE_BANK:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Банк продает 1 BTC за {"#cLIGHTRED"}%d$."W"\n\
            Банк покупает 1 BTC за {"#cGREEN"}%d$."W"\n\
            У Вас: {"#cYELLOW"}%d BTC."W"\n\
            "I"[1]"W" Приобрести BTC\n\
            "I"[2]"W" Продать BTC\n\
            "I"[3]"W" Информация о BTC", curs_btc, floatround(curs_btc * 0.95, floatround_ceil), p_info[playerid][bitcoin]);
            ShowPlayerDialog(playerid, D_VC_BANK, DIALOG_STYLE_LIST, ""I"Bitcoin", STRING_GLOBAL, "Далее", "Отмена");
        }
        case VIDEO_CARDS_TYPE_BANK_SELL:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Введите количество BTC от 1 до %d, которое хотите продать:\n\n\
            Банк покупает 1 BTC за {"#cGREEN"}%d$.", p_info[playerid][bitcoin], floatround(curs_btc * 0.95, floatround_ceil));
            ShowPlayerDialog(playerid, D_VC_BANK_SELL, DIALOG_STYLE_INPUT, ""I"Продать BTC", STRING_GLOBAL, "Далее", "Отмена");
        }
        case VIDEO_CARDS_TYPE_BANK_BUY:
        {
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, ""W"\
            Введите количество BTC, которое хотите приобрести:\n\n\
            Банк продает 1 BTC за {"#cGREEN"}%d$.", curs_btc);
            ShowPlayerDialog(playerid, D_VC_BANK_BUY, DIALOG_STYLE_INPUT, ""I"Приобрести BTC", STRING_GLOBAL, "Далее", "Отмена");
        }
    }
    return 1;
}

CheckVideoCards()
{
    new Float:count, price;
    for(new i = 1; i <= totalvideocards; i++)
    {
        if(VideoCardsInfo[i][vcMySQLIDx] == 0) continue;
        if(VideoCardsInfo[i][vcStatus] == 0) continue;

        count = 0.03 * VideoCardsInfo[i][vcLevel];
        price = (b_info[VideoCardsInfo[i][vcBizIDx]][_till] * POWER_STATION_PRICE) * VideoCardsInfo[i][vcLevel];

        if(VideoCardsInfo[i][vcCoolant] - 0.3 > 0 && VideoCardsInfo[i][vcBitcoin] < MAX_VIDEO_CARDS_BITCOIN && VideoCardsInfo[i][vcTax] < MAX_VIDEO_CARDS_TAX && price > 0)
        {
            VideoCardsInfo[i][vcCoolant] -= 0.3;
            VideoCardsInfo[i][vcBitcoin] += count;
            VideoCardsInfo[i][vcTax] += price;

            if(VideoCardsInfo[i][vcBitcoin] > MAX_VIDEO_CARDS_BITCOIN)
            {
                VideoCardsInfo[i][vcStatus] = 0;
                VideoCardsInfo[i][vcBitcoin] = 9.0;
            }
            if(VideoCardsInfo[i][vcTax] > MAX_VIDEO_CARDS_TAX)
            {
                VideoCardsInfo[i][vcStatus] = 0;
                VideoCardsInfo[i][vcTax] = MAX_VIDEO_CARDS_TAX;
            }

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `videocards` SET `coolant` = '%f', `bitcoin` = '%f', `tax` = %d, `status` = %d WHERE `id` = %d",
            VideoCardsInfo[i][vcCoolant], VideoCardsInfo[i][vcBitcoin], VideoCardsInfo[i][vcTax], VideoCardsInfo[i][vcStatus], VideoCardsInfo[i][vcMySQLIDx]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        else
        {
            VideoCardsInfo[i][vcStatus] = 0;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `videocards` SET `status` = 0 WHERE `id` = %d",
            VideoCardsInfo[i][vcMySQLIDx]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

GetHouseVideoCards(houseid)
{
    new count = 0;
    for(new idx = 1; idx <= totalvideocards; idx++)
    {
        if(VideoCardsInfo[idx][vcHouseIDx] == houseid) count++;
    }
    return count;
}

GetMaxHouseVideoCards(houseid)
{
    new squar = h_info[houseid][h_squar], idx = 1;
    switch(squar)
    {
        case 1: return 8;
        case 2: return 12;
        case 3: return 16;
        case 4: return 20;
    }
    return idx;
}

forward load_videocards();
public load_videocards()
{
    new time = GetTickCount(), str[512], biz_idx[] = {100, 101, 102};
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iiififii",
            VideoCardsInfo[idx][vcMySQLIDx],
            VideoCardsInfo[idx][vcStatus],
            VideoCardsInfo[idx][vcLevel],
            VideoCardsInfo[idx][vcCoolant],
            VideoCardsInfo[idx][vcTax],
            VideoCardsInfo[idx][vcBitcoin],
            VideoCardsInfo[idx][vcHouseIDx],
            VideoCardsInfo[idx][vcBizIDx]);
            if((b_info[VideoCardsInfo[totalvideocards][vcBizIDx]][_till] * POWER_STATION_PRICE) * VideoCardsInfo[idx][vcLevel] <= 0)
            {
                VideoCardsInfo[totalvideocards][vcBizIDx] = biz_idx[random(2)];
                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `videocards` SET `biz` = %d WHERE `id` = %d",
                VideoCardsInfo[totalvideocards][vcBizIDx], VideoCardsInfo[totalvideocards][vcMySQLIDx]);
                mysql_tquery(con_bd, STRING_GLOBAL);
            }
            totalvideocards++;
        }
    }
    printf("Видеокарты в домах загружено: %d за %d мс", totalvideocards, GetTickCount() - time);
}

forward load_curs_btc(type);
public load_curs_btc(type)
{
    if(cache_num_rows())
    {
        cache_get_value_name_int(0, "sum", curs_btc);
        if(curs_btc < 10000 || curs_btc > 50000) curs_btc = 0;
    }
    else curs_btc = 0;
    if(!type) printf("[Bitcoin]: Curse BTC: %d", curs_btc);
    return 1;
}

CMD:btc(playerid, params[])
{
    if(!FD(playerid) || p_info[playerid][admin] < 10) return 1;
    if(sscanf(params, "d", params[0]))
        return SendInfo(playerid, "Используйте: /btc [value]");
    curs_btc = params[0];
    SendAccess(playerid, "Новый курс BTC: %d$", curs_btc);
    return 1;
}

forward create_videocards(idx);
public create_videocards(idx)
{
    VideoCardsInfo[idx][vcMySQLIDx] = cache_insert_id();
    return 1;
}

DestroyVideoCards(idx)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `videocards` WHERE `id` = %d",
    VideoCardsInfo[idx][vcMySQLIDx]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    VideoCardsInfo[idx][vcMySQLIDx] = 0;
    VideoCardsInfo[idx][vcStatus] = 0;
    VideoCardsInfo[idx][vcLevel] = 1;
    VideoCardsInfo[idx][vcCoolant] = 0.0;
    VideoCardsInfo[idx][vcTax] = 0;
    VideoCardsInfo[idx][vcBitcoin] = 0.0;
    VideoCardsInfo[idx][vcHouseIDx] = 0;
    VideoCardsInfo[idx][vcBizIDx] = 0;
    return 1;
}

CMD:test_vc(playerid, params[])
{
    if(SRV_ID) return 1;
    CheckVideoCards();
    return 1;
}
