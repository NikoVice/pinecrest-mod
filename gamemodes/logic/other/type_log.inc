enum
{
/* 1 */   TYPE_LOG_BAN = 1,
/* 2 */   TYPE_LOG_SBAN,
/* 3 */   TYPE_LOG_IBAN,
/* 4 */   TYPE_LOG_MUTE,
/* 5 */   TYPE_LOG_KICK,
/* 6 */   TYPE_LOG_WARN,
/* 7 */   TYPE_LOG_JAIL,
/* 8 */   TYPE_LOG_UVAL,
/* 9 */   TYPE_LOG_SKICK,
/* 10 */  TYPE_LOG_SETHP,
/* 11 */  TYPE_LOG_BANIP,
/* 12 */  TYPE_LOG_DELACC,
/* 13 */  TYPE_LOG_SETNICK,

/* 14 */  TYPE_LOG_UNBAN,
/* 15 */  TYPE_LOG_UNMUTE,
/* 16 */  TYPE_LOG_UNWARN,
/* 17 */  TYPE_LOG_UNJAIL,
/* 18 */  TYPE_LOG_UNBANIP,

/* 19 */  TYPE_LOG_OFFBAN,
/* 20 */  TYPE_LOG_OFFWARN,
/* 21 */  TYPE_LOG_OFFJAIL,
/* 22 */  TYPE_LOG_OFFUNWARN,
/* 23 */  TYPE_LOG_OFFMUTE,
/* 24 */  TYPE_LOG_SETSTATS,

/* 25 */ TYPE_LOG_FREEZE,
/* 26 */ TYPE_LOG_SLAP,
/* 27 */ TYPE_LOG_DPAME,
/* 28 */ TYPE_LOG_UNFREEZE,
/* 29 */ TYPE_LOG_TRANSFER,

    TYPE_LOG_ALL,
}

new NamePunishment[TYPE_LOG_ALL-1][] = {
    "забанил",
    "тихо забанил",
    "-",
    "выдал бан чата",
    "кикнул",
    "выдал варн",
    "посадил в тьюрьму",
    "уволил из фракции",
    "тихо кикнул",
    "изменил уровень хп",
    "забанил по IP",
    "удалил аккаунт",
    "изменил ник",
    "разблокировал",
    "снял бан чата",
    "снял варн",
    "выпустил из тюрьмы",
    "разблокировал IP",
    "[OFFLINE] забанил",
    "[OFFLINE] выдал варн",
    "[OFFLINE] посадил в тюрьму",
    "[OFFLINE] снял варн",
    "[OFFLINE] снял бан чата",
    "поменял статистику",
    "заморозил",
    "подкинул",
    "удалил pame",
    "разморозил",
    "перенес аккаунт"
};

new NameTypeHistoryPunishment[TYPE_LOG_ALL-1][] = {
    "Бан",
    "Тихий бан",
    "-",
    "Бан чата",
    "Кик",
    "Варн",
    "Деморган",
    "Увольнение из фракции",
    "Тихий кик",
    "Уровень HP",
    "Бан по IP",
    "Удалление аккаунта",
    "Изменения ника",
    "Разбан",
    "Снятие бан чата",
    "Снятие варна",
    "Освобождение из деморгана",
    "Разбан IP",
    "[OFFLINE] Бан",
    "[OFFLINE] Варн",
    "[OFFLINE] Деморган",
    "[OFFLINE] Снятие варна",
    "[OFFLINE] Снятие бан чата",
    "Смена статистики",
    "Заморожен",
    "Слап/Подкинут",
    "Удаление pame",
    "Разморожен",
    "Перенсо аккаунта"
};

stock WriteAdminLog(TYPE_LOG, playerid, const NameTargetid[], targetid, const ReasonLog[] = "")
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `admin_log` (`TYPE`, `ADMIN`, `PLAYER`, `REASON`) VALUES (%d, '%e', '%e', '%e')",
    TYPE_LOG, get_name(playerid), NameTargetid, ReasonLog);
    mysql_tquery(con_bd, STRING_GLOBAL);


    if(targetid != INVALID_PLAYER_ID)
    {
        Log(LOG_player, INFO, "%s[%d](%s %s) %s %s[%d](%s %s). Причина: %s | #AdminLogs",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", 
            NamePunishment[TYPE_LOG-1],
            get_name(targetid), p_info[targetid][ID], p_temp[targetid][session_IP], IsPlayerMobile(targetid) ? "Mobile": "PC",
            ReasonLog);
    }
    else 
    {

        if(TYPE_LOG == TYPE_LOG_BANIP || TYPE_LOG == TYPE_LOG_UNBANIP)
        {
            Log(LOG_player, INFO, "%s[%d](%s %s) %s IP адресс: %s. Причина: %s | #AdminLogs",
                get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", 
                NamePunishment[TYPE_LOG-1], NameTargetid, ReasonLog);
        }
        else
        {
            Log(LOG_player, INFO, "%s[%d](%s %s) %s %s(Offline). Причина: %s | #AdminLogs",
            get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], IsPlayerMobile(playerid) ? "Mobile": "PC", 
            NamePunishment[TYPE_LOG-1], NameTargetid, ReasonLog);
        }
    }
    return 1;
}
