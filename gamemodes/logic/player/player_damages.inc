#define MAX_DAMAGES 20
enum damages_data
{
    gdBody,
    gdTime[24],
    gdGun,
    Float:gdDamage,
    gdNameDamages[MAX_PLAYER_NAME],
    gdNameID
}
new gDamagesData[MAX_PLAYERS][MAX_DAMAGES][damages_data];

#if !defined BODY_PART_TORSO
enum
{
	BODY_PART_TORSO = 3,
	BODY_PART_GROIN,
	BODY_PART_LEFT_ARM,
	BODY_PART_RIGHT_ARM,
	BODY_PART_LEFT_LEG,
	BODY_PART_RIGHT_LEG,
	BODY_PART_HEAD
};

stock TakePlayerDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
    for(new i = MAX_DAMAGES-1; i != 0; i--)
    {
        if(gDamagesData[playerid][i-1][gdNameID] == INVALID_PLAYER_ID) continue;
        gDamagesData[playerid][i][gdBody] = gDamagesData[playerid][i-1][gdBody];
        format(gDamagesData[playerid][i][gdTime], 24, "%s", gDamagesData[playerid][i-1][gdTime]);
        gDamagesData[playerid][i][gdGun] = gDamagesData[playerid][i-1][gdGun];
        gDamagesData[playerid][i][gdDamage] = gDamagesData[playerid][i-1][gdDamage];
        format(gDamagesData[playerid][i][gdNameDamages], MAX_PLAYER_NAME, "%s", gDamagesData[playerid][i-1][gdNameDamages]);
        gDamagesData[playerid][i][gdNameID] = gDamagesData[playerid][i-1][gdNameID];
    }
    gDamagesData[playerid][0][gdBody] = bodypart;
    format(gDamagesData[playerid][0][gdTime], 24, "%s", GetFullDate());
    gDamagesData[playerid][0][gdGun] = weaponid;
    gDamagesData[playerid][0][gdDamage] = amount;
    strmid(gDamagesData[playerid][0][gdNameDamages], get_name(issuerid), 0, strlen(get_name(issuerid)), MAX_PLAYER_NAME);
    gDamagesData[playerid][0][gdNameID] = issuerid;
    return 1;
}

ClearPlayerDamage(playerid)
{
    for(new i = 0; i < MAX_DAMAGES; i++)
    {
        if(gDamagesData[playerid][i][gdBody] == -1) break;
        gDamagesData[playerid][i][gdBody] = -1;
        gDamagesData[playerid][i][gdGun] = 0;
        gDamagesData[playerid][i][gdDamage] = 0.0;
        gDamagesData[playerid][i][gdTime][0] = EOS;
        gDamagesData[playerid][i][gdNameDamages][0] = EOS;
        gDamagesData[playerid][i][gdNameID] = INVALID_PLAYER_ID;
    }
}

CMD:damages(playerid,params[])
{
    new id_damage;
    if(p_info[playerid][admin] > 0)
    {
        if(sscanf(params, "u", id_damage))
        {
            SendInfo(playerid, "Используйте: /damages [id игрока]");
            id_damage = playerid;
        }
        if(id_damage == INVALID_PLAYER_ID) return SendError(playerid, "Игрок не в сети.");
    }
    else id_damage = playerid;
    new count_damages_show = 1;
    STRING_GLOBAL = "[#] Время\tУрон\tОружие | Часть тела\tНападавший\n";
    for(new i = 0; i < MAX_DAMAGES; i++)
    {
        if(gDamagesData[id_damage][i][gdBody] == -1) continue;
        new to_part_body[32], name_damage_weapon[32];
        if(gDamagesData[id_damage][i][gdGun] < 0 || gDamagesData[id_damage][i][gdGun] > 50) name_damage_weapon = "Неизвестно";
        else if(gDamagesData[id_damage][i][gdGun] < 47) strmid(name_damage_weapon, WEAPON_Name[gDamagesData[id_damage][i][gdGun]], 0, strlen(WEAPON_Name[gDamagesData[id_damage][i][gdGun]]), 32);
        else if(gDamagesData[id_damage][i][gdGun] >= 48) name_damage_weapon="Автомобильные ранения";

        switch(gDamagesData[id_damage][i][gdBody])
        {
            case BODY_PART_TORSO: to_part_body = "Тело";
            case BODY_PART_GROIN: to_part_body = "Пах";
            case BODY_PART_LEFT_ARM: to_part_body = "Левая рука";
            case BODY_PART_RIGHT_ARM: to_part_body = "Правая рука";
            case BODY_PART_LEFT_LEG: to_part_body = "Левая нога";
            case BODY_PART_RIGHT_LEG: to_part_body = "Левая нога";
            case BODY_PART_HEAD: to_part_body = "Голова";
            default: to_part_body = "Неизвестно";
        }
        f(STRING_GLOBAL, "%s"I"[%d]"W" %s\t%.1f\t%s | %s\t%s(%d)\n",
            STRING_GLOBAL, count_damages_show,
            gDamagesData[id_damage][i][gdTime],
            gDamagesData[id_damage][i][gdDamage],
            name_damage_weapon, to_part_body,
            gDamagesData[id_damage][i][gdNameDamages],
            gDamagesData[id_damage][i][gdNameID]);
        count_damages_show++;
    }
    if(!count_damages_show) SendError(playerid, "У игрока нет повреждений.");
    else
    {
        STRING_MIN[0] = EOS;
        format(STRING_MIN, sizeof(STRING_MIN), ""I"%s", get_name(id_damage));
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, STRING_MIN, STRING_GLOBAL, "Закрыть", "");
    }
    return 1;
}
