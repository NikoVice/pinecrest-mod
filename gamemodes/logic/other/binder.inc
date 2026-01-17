#define MAX_BINDER  30
new arrayBinderCMD[MAX_PLAYERS][MAX_BINDER][32],
    arrayBinderTEXT[MAX_PLAYERS][MAX_BINDER][128];

public OnPlayerConnect(playerid)
{
    for(new i = MAX_BINDER-1; i != -1; i--)
    {
        arrayBinderCMD[playerid][i] = "";
        arrayBinderTEXT[playerid][i] = "";
    }
    p_temp[playerid][BinderNoCommand] = 0;
    #if defined bind_OnPlayerConnect
        return bind_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#if defined bind_OnPlayerConnect
    forward bind_OnPlayerConnect(playerid);
#endif
#define    OnPlayerConnect bind_OnPlayerConnect


LoadPlayerBinder(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id`, `enb`, `cmd`, `text` FROM `binder` WHERE `user_id` = %d LIMIT %d",
    p_info[playerid][ID], MAX_BINDER);
    mysql_tquery(con_bd, STRING_GLOBAL, "LoadPlayerBinderCallBack", "i", playerid);
}
forward LoadPlayerBinderCallBack(playerid);
public LoadPlayerBinderCallBack(playerid)
{
    new rows = cache_num_rows();
    if(!rows) return 1;
    new id;
    for(new i; i < rows; i++)
    {
        cache_get_value_name_int(i, "id", id);
        cache_get_value_name_int(i, "enb", p_info[playerid][BinderStatus][id]);
        cache_get_value_name(i, "cmd", arrayBinderCMD[playerid][id]);
        cache_get_value_name(i, "text", arrayBinderTEXT[playerid][id]);
    }
    return 1;
}
CMD:bind(playerid, params[])
{
    p_temp[playerid][BinderList] = 0;
    return ShowBinderList(playerid);
}
alias:bind("binder");

ShowBinderList(playerid)
{
    STRING_GLOBAL = "[#] Статус\tКоманда\tТекст\n";
    strcat(STRING_GLOBAL, ""I""W"Следующая страница\t»\t»\n");
    strcat(STRING_GLOBAL, ""I"<< "W"Предыдущая страница\t«\t«\n");
    strcat(STRING_GLOBAL, ""I"- "W"Добавить команду\t+\t+\n");
    strcat(STRING_GLOBAL, "-----------------\t-\t-\n");

    STRING_MIN[0] = EOS;
    new tmp, page = p_temp[playerid][BinderList];
    for(new i = ((page + 1) * 20) - 1; i >= (page * 20); i--) if(i < MAX_BINDER && arrayBinderCMD[playerid][i][0])
    {
        if(tmp >= 20) break;
        p_temp[playerid][BufferBinderID][tmp++] = i;
        format(STRING_MIN, sizeof(STRING_MIN), arrayBinderTEXT[playerid][i]);
        if(strlen(STRING_MIN) > 30)
        {
            strdel(STRING_MIN, 28, strlen(STRING_MIN));
            strcat(STRING_MIN, "...");
        }
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%s\t%s\n", STRING_GLOBAL,
            i,
            p_info[playerid][BinderStatus][i] ? ("{"#cGREEN"}Активно") : ("{"#cLIGHTRED"}Отключено"),
            arrayBinderCMD[playerid][i], STRING_MIN);
    }

    if(!tmp && page) {
        for(new i = ((page) * 20) - 1; i >= (page * 20); i--) if(i < MAX_BINDER && arrayBinderCMD[playerid][i][0])
        {
            if(tmp >= 20) break;
            p_temp[playerid][BufferBinderID][tmp++] = i;
            format(STRING_MIN, sizeof(STRING_MIN), arrayBinderTEXT[playerid][i]);
            if(strlen(STRING_MIN) > 30)
            {
                strdel(STRING_MIN, 28, strlen(STRING_MIN));
                strcat(STRING_MIN, "...");
            }
            f(STRING_GLOBAL, "%s%s"I"\t"W"%s\t"W"%s\n", STRING_GLOBAL,
            p_info[playerid][BinderStatus][i] ? ("{"#cGREEN"}Активно") : ("{"#cLIGHTRED"}Отключено"),
            arrayBinderCMD[playerid][i], STRING_MIN);
        }
    }
    new count = !tmp && page ? 0 : 1;
    format(STRING_MIN, sizeof(STRING_MIN), ""I"Биндер, страница: %i", page + count);

    return ShowPlayerDialog(playerid, D_BINDER_SHOW, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Далее", "Отмена");
}

CheckBinderCommand(playerid, cmd[], type = 1)
{
    if(p_temp[playerid][BinderNoCommand]) return 0;
    new ecmd[32];
    strcat(ecmd, cmd);
    if(type) strins(ecmd, "/", 0);
    for(new i; i < MAX_BINDER; i++) if(arrayBinderCMD[playerid][i][0] && p_info[playerid][BinderStatus][i] && !strcmp(ecmd, arrayBinderCMD[playerid][i]))
    {
        p_temp[playerid][BinderNoCommand] = 1;
        SetTimerEx("CheckBinderCommandText", 0, false, "ii", playerid, i);
        return 1;
    }
    return 0;
}
forward CheckBinderCommandText(playerid, slot);
public CheckBinderCommandText(playerid, slot)
{
    new text[8][144];
    sscanf(arrayBinderTEXT[playerid][slot], "p<>>a<s[144]>[8]", text);
    for(new i; i < 8; i++) if(text[i][0])
    {
        DeletePVar(playerid, "Flood:CMD");
        if(text[i][0] == '/') //PC_EmulateCommand(playerid, text[i]);
        {
            new cmd_text[2][144];
            sscanf(text[i], "s[144]s[144]", cmd_text[0], cmd_text[1]);
            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "pc_cmd_%s", cmd_text[0][1]);
            CallRemoteFunction(STRING_GLOBAL, "is", playerid, isnull(cmd_text[1]) ? ("\1") : cmd_text[1]);
        }
        else OnPlayerText(playerid, text[i]);
    }
    SetPVarInt(playerid, "Flood:CMD", timestamp+1);
    p_temp[playerid][BinderNoCommand] = 0;
}

