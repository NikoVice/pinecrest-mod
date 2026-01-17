new bool:bExtraLogs = false;

CMD:logs(playerid, params[])
{
    if(p_info[playerid][admin] < 6) return 1;
    bExtraLogs ^= true;
    SendAccess(playerid, "Вы %s новую систему логов.", bExtraLogs ? "включили" : "выключили");
    return 1;
}
