/*
    Author: Vip_Uzer
    Flin RolePlay
    (c) 2021
*/
#define MAX_TOP_LIST 10
#define MAX_PLAYER_TOP 5
enum e_toplist
{
    WarID[2],
    WarType,
    WarStatsTime,
    WarStatsTimeEnd,

    KillsOne[MAX_PLAYER_TOP],
    DeathsOne[MAX_PLAYER_TOP],
    Float:GiveDamageOne[MAX_PLAYER_TOP],
    Float:TakeDamageOne[MAX_PLAYER_TOP],

    KillsTwo[MAX_PLAYER_TOP],
    DeathsTwo[MAX_PLAYER_TOP],
    Float:GiveDamageTwo[MAX_PLAYER_TOP],
    Float:TakeDamageTwo[MAX_PLAYER_TOP],

}
new TopList[MAX_TOP_LIST][e_toplist],
    TopListNickOne[MAX_TOP_LIST][MAX_PLAYER_TOP][MAX_PLAYER_NAME],
    TopListNickTwo[MAX_TOP_LIST][MAX_PLAYER_TOP][MAX_PLAYER_NAME];
CMD:statswar(playerid, params[])
{
    if(!gang(playerid) && !mafia(playerid) && !biker(playerid)) return SendError(playerid, "Вы не состоите в нелегальной организации.");

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"\
    Статистика захвата за последнюю битву:\n\n\
    \tУбийств: "I"%d"W"\n\
    \tСмертей: "I"%d"W"\n\
    \tНанесенного урона: "I"%0.2f"W"\n\
    \tПолученного урона: "I"%0.2f"W"\n\n\
    {"#cLIGHTRED"}Статистика обнуляется каждый час или при перезаходе.", p_temp[playerid][CaptureBizWarInfoInt][0], p_temp[playerid][CaptureBizWarInfoInt][1], p_temp[playerid][CaptureBizWarInfoFloat][0], p_temp[playerid][CaptureBizWarInfoFloat][1]);
    ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Статистика захвата", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
alias:statswar("getkills");

CMD:captstats(playerid, params[])
{
    STRING_GLOBAL[0] = EOS;
    for(new i; i < MAX_TOP_LIST; i++)
    {
        switch(TopList[i][WarType])
        {
            case CAPTURE_ID_GANG, CAPTURE_ID_MAFIA: f(STRING_GLOBAL, "%s"I"[%d] "W"%s VS %s\n", STRING_GLOBAL, i+1, GetFractionName(TopList[i][WarID][0]), GetFractionName(TopList[i][WarID][1]));
            case CAPTURE_ID_FAMILY: f(STRING_GLOBAL, "%s"I"[%d] "W"%s VS %s\n", STRING_GLOBAL, i+1,FamilyData[TopList[i][WarID][0]][fName], FamilyData[TopList[i][WarID][1]][fName]);
            default: f(STRING_GLOBAL, "%s"I"[%d] "W"Информации нет\n", STRING_GLOBAL, i+1);
        }
    }
    ShowPlayerDialog(playerid, D_TOPWAR, DIALOG_STYLE_LIST, "Статистика захватов за последний час", STRING_GLOBAL, "Выбрать", "Закрыть");
    return 1;
}
alias:captstats("topwar", "fcaptstats", "topcapt", "capttop");

CMD:gangtop(playerid)
{
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `admin` = 0 AND `member` > 0 AND `ftop_gkills_week` != 0 ORDER BY `ftop_gkills_week` DESC LIMIT 10");
    mysql_tquery(con_bd, STRING_GLOBAL, "ShowPlayerDialogTop", "ddd", playerid, 5, 8);
    return 1;
}
alias:gangtop("gangwar", "weektop", "topweek");

//============= new ================================
GetSlotTopList(playerid)
{
    new family_idx = GetPlayerFamilyID(playerid);
    for(new i = MAX_TOP_LIST-1; i != -1; i--)
    {
        if(TopList[i][WarStatsTime] < timestamp) continue;
        if(TopList[i][WarID][0] == p_info[playerid][member] || TopList[i][WarID][1] == p_info[playerid][member] ||
            TopList[i][WarID][0] == family_idx || TopList[i][WarID][1] == family_idx)
            return i;
    }
    return -1;
}

AddTopList(playerid)
{
    new idx = GetSlotTopList(playerid);
    if(idx == -1) return 1;
    new bool:status_write = false;
    if(TopList[idx][WarID][0] == p_info[playerid][member] || TopList[idx][WarID][0] == GetPlayerFamilyID(playerid))
    {
        for(new i; i < MAX_PLAYER_TOP; i++)
        {
            if(strequals(TopListNickOne[idx][i], get_name(playerid))) TopList[idx][KillsOne] = -1;
            if(p_temp[playerid][CaptureBizWarInfoInt][0] > TopList[idx][KillsOne] && status_write == false)
            {
                if((i+1) < MAX_PLAYER_TOP && !strequals(TopListNickOne[idx][i], get_name(playerid)))
                {
                    strmid(TopListNickOne[idx][i+1], TopListNickOne[idx][i], 0, strlen(TopListNickOne[idx][i]), MAX_PLAYER_NAME);
                    TopList[idx][KillsOne][i+1] = TopList[idx][KillsOne][i];
                    TopList[idx][DeathsOne][i+1] = TopList[idx][DeathsOne][i];
                    TopList[idx][GiveDamageOne][i+1] = TopList[idx][GiveDamageOne][i];
                    TopList[idx][TakeDamageOne][i+1] = TopList[idx][TakeDamageOne][i];
                }
                strmid(TopListNickOne[idx][i], get_name(playerid), 0, strlen(get_name(playerid)), MAX_PLAYER_NAME);
                TopList[idx][KillsOne][i] = p_temp[playerid][CaptureBizWarInfoInt][0];
                TopList[idx][DeathsOne][i] = p_temp[playerid][CaptureBizWarInfoInt][1];
                TopList[idx][GiveDamageOne][i] = p_temp[playerid][CaptureBizWarInfoFloat][0];
                TopList[idx][TakeDamageOne][i] = p_temp[playerid][CaptureBizWarInfoFloat][1];
                status_write = true;
            }
        }
    }
    else
    {
        for(new i; i < MAX_PLAYER_TOP; i++)
        {
            if(strequals(TopListNickTwo[idx][i], get_name(playerid))) TopList[idx][KillsTwo] = -1;
            if(p_temp[playerid][CaptureBizWarInfoInt][0] > TopList[idx][KillsTwo] && status_write == false)
            {
                if((i+1) < MAX_PLAYER_TOP && !strequals(TopListNickTwo[idx][i], get_name(playerid)))
                {
                    strmid(TopListNickTwo[idx][i+1], TopListNickTwo[idx][i], 0, strlen(TopListNickTwo[idx][i]), MAX_PLAYER_NAME);
                    TopList[idx][KillsTwo][i+1] = TopList[idx][KillsTwo][i];
                    TopList[idx][DeathsTwo][i+1] = TopList[idx][DeathsTwo][i];
                    TopList[idx][GiveDamageTwo][i+1] = TopList[idx][GiveDamageTwo][i];
                    TopList[idx][TakeDamageTwo][i+1] = TopList[idx][TakeDamageTwo][i];
                }
                strmid(TopListNickTwo[idx][i], get_name(playerid), 0, strlen(get_name(playerid)), MAX_PLAYER_NAME);
                TopList[idx][KillsTwo][i] = p_temp[playerid][CaptureBizWarInfoInt][0];
                TopList[idx][DeathsTwo][i] = p_temp[playerid][CaptureBizWarInfoInt][1];
                TopList[idx][GiveDamageTwo][i] = p_temp[playerid][CaptureBizWarInfoFloat][0];
                TopList[idx][TakeDamageTwo][i] = p_temp[playerid][CaptureBizWarInfoFloat][1];
                status_write = true;
            }
        }
    }
    return 1;
}

InitTopList(war_id_one, war_id_two, war_type, war_time)
{
    new slot_id = GetFreeSlotTopList();
    if(slot_id == -1) return 1;
    TopList[slot_id][WarID][0] = war_id_one;
    TopList[slot_id][WarID][1] = war_id_two;
    TopList[slot_id][WarType] = war_type;
    TopList[slot_id][WarStatsTime] = timestamp+war_time;
    return 1;
}

GetFreeSlotTopList()
{
    for(new i = MAX_TOP_LIST-1; i != -1; i--)
    {
        if(TopList[i][WarID][0] == 0 && TopList[i][WarID][1] == 0 || timestamp > TopList[i][WarStatsTime]+2700)
        {
            ClearTopList(i);
            return i;
        }
    }
    return -1;
}

ClearTopList(slot_id)
{
    for(new i; i < MAX_PLAYER_TOP; i++)
    {
        TopListNickOne[slot_id][i] = "";
        TopListNickTwo[slot_id][i] = "";

        TopList[slot_id][WarID][0] =
        TopList[slot_id][WarID][1] = 0;
        TopList[slot_id][WarType] = CAPTURE_ID_NONE;

        TopList[slot_id][KillsOne][i] =
        TopList[slot_id][DeathsOne][i] =
        TopList[slot_id][KillsTwo][i] =
        TopList[slot_id][DeathsTwo][i] = 0;

        TopList[slot_id][GiveDamageOne][i] =
        TopList[slot_id][TakeDamageOne][i] =
        TopList[slot_id][GiveDamageTwo][i] =
        TopList[slot_id][TakeDamageTwo][i] = 0.0;
    }
}
/*
SaveTopList(slot_id)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL),
        "INSERT INTO `wartops` (`war_id_1`, `war_id_2`, `war_type`, \
            `data_top_0`, `data_top_0`, ``) VALUES ('Flin_Bot', '>> Новый рекорд онлайна: %d',
    2000000005, 0, CURRENT_DATE(), CURRENT_TIME())", max_online);
}
*/
