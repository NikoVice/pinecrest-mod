CMD:snews(playerid)
{
    ShowPlayerList(playerid, LIST_ID_SERVER_FORUM);
    return 1;
}

this::OnUpdateSFNewsCallback(playerid, mysqlID, newsid)
{
    if(p_info[playerid][ID] != mysqlID) return 1;
    OnLoadSFNews(playerid, newsid);
    return 1;
}

OnLoadSFNews(playerid, newsid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT  `type`, `text`, `date` FROM `server_forum` WHERE `id` = %d", newsid);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnLoadSFNewsCallback", "ii", playerid, p_info[playerid][ID]); 
}

this::OnLoadSFNewsCallback(playerid, mysqlID)
{
    if(mysqlID != p_info[playerid][ID])
        return 1;
    if(!cache_num_rows())
        return SendError(playerid, "Ничего не найдено.");

    new fs_type, fs_date[24];

    STRING_GLOBAL[0] = EOS;
    STRING_MIN[0] = EOS;

    cache_get_value_name_int(0, "type", fs_type);
    cache_get_value_name(0, "text", STRING_MIN);
    cache_get_value_name(0, "date", fs_date);

    f(STRING_GLOBAL, "%s", STRING_MIN);

    STRING_MIN[0] = EOS;
    f(STRING_MIN, "%s от %s", !fs_type ? "Новость" : "Опрос", fs_date);

    if(!fs_type) ShowPlayerDialog(playerid, D_SF_TEXT_NEWS, DIALOG_STYLE_MSGBOX, STRING_MIN, STRING_GLOBAL, "Оценить", "Закрыть");
    else SendError(playerid, "Опросы в разработке.. ");
    return 1;
}

