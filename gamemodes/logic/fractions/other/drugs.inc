#define MAX_DRUGS           250

enum E_DRUGS_INFO
{
    diID,
    diOwnerID,
    Float:diPosX,
    Float:diPosY,
    Float:diPosZ,
    Float:diPosRX,
    Float:diPosRY,
    Float:diPosRZ,
    diInterior,
    diWorld,
    diProg,
    diPlanted,
    diObject,
    Text3D:diText
};
new DrugsInfo[MAX_DRUGS][E_DRUGS_INFO];

CheckDrugs()
{
    for(new i = 1; i < MAX_DRUGS; i++)
    {
        if(DrugsInfo[i][diPlanted] == 0) continue;
        DrugsInfo[i][diProg]++;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `drugs` SET `prog` = '%d' WHERE `id` = %d LIMIT 1",
        DrugsInfo[i][diProg], DrugsInfo[i][diID]);
        mysql_tquery(con_bd, STRING_GLOBAL);

        if(DrugsInfo[i][diProg] == 2)
        {
            DrugsInfo[i][diPlanted] = 2;

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `drugs` SET `planted` = %d WHERE `id` = %d LIMIT 1",
            DrugsInfo[i][diPlanted], DrugsInfo[i][diID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
        else if(DrugsInfo[i][diProg] == 27)
        {
            DrugsInfo[i][diPlanted] = 0;
            DrugsInfo[i][diProg] = 0;
            DrugsInfo[i][diOwnerID] = 0;
            if(IsValidDynamicObject(DrugsInfo[i][diObject])) DestroyDynamicObject(DrugsInfo[i][diObject]);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `drugs` WHERE `id` = %d",
            DrugsInfo[i][diID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
        }
    }
    return 1;
}

GetFreeDrugs()
{
    new idx = -1;
    for(new i = 1; i < MAX_DRUGS; i++)
    {
        if(DrugsInfo[i][diPlanted] == 0) return i;
    }
    return idx;
}

forward load_drugs();
public load_drugs()
{
    new str[256], time = GetTickCount(), totaldrugs;
    if(cache_num_rows())
    {
        for(new idx = 1; idx < 1 + cache_num_rows(); idx++)
        {
            if(totaldrugs == MAX_DRUGS - 1) break;
            f_mysql_fetch_row_format(idx-1, str, cache_num_fields());
            sscanf(str, "p<|>iifffiiii",
            DrugsInfo[idx][diID],
            DrugsInfo[idx][diOwnerID],
            DrugsInfo[idx][diPosX],
            DrugsInfo[idx][diPosY],
            DrugsInfo[idx][diPosZ],
            DrugsInfo[idx][diWorld],
            DrugsInfo[idx][diInterior],
            DrugsInfo[idx][diProg],
            DrugsInfo[idx][diPlanted]);
            totaldrugs++;
            if(DrugsInfo[idx][diPlanted])
            {
                DrugsInfo[idx][diObject] = CreateDynamicObject(3409, DrugsInfo[idx][diPosX], DrugsInfo[idx][diPosY], DrugsInfo[idx][diPosZ]-1.2, 0.0, 0.0, 0.0, DrugsInfo[idx][diWorld], DrugsInfo[idx][diInterior], -1, 120);
            }
        }
    }
    printf("Данные кустов загружены за %d мс", GetTickCount()-time);
    return 1;
}

forward create_drugs(idx);
public create_drugs(idx)
{
    DrugsInfo[idx][diID] = cache_insert_id();
    return 1;
}

CMD:cdrugs(playerid, params[])
{
    if(gang(playerid) == 0) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    new gangzone = GetGangZoneID(playerid);
    if(gangzone == INVALID_CRIMINAL_ZONE_ID) return SendError(playerid, "Вы не на территории гетто");
    if(GangZone_Info[gangzone][g_Fraction] != p_info[playerid][member]) return SendError(playerid, "Данная территория не принадлежит Вашей фракции.");
    if(IsGangRespawn(gangzone)) return SendError(playerid, "Эта территория является респауном банды.");

    new idx = GetFreeDrugs();
    if(idx == -1) return SendError(playerid, "В данный момент Вы не можете посадить семена.");

    new total = 0;
    for(new i = 1; i < MAX_DRUGS; i++)
    {
        if(DrugsInfo[i][diOwnerID] != p_info[playerid][ID]) continue;
        total++;
    }
    if(total >= 5) return SendError(playerid, "Вы не можете установить более 5 семян одновременно.");

    if(GetInventoryAmount(playerid, 692) == 0) return SendError(playerid, "У Вас нет грунта.");
    if(GetInventoryAmount(playerid, 693) == 0) return SendError(playerid, "У Вас нет удобрений.");
    if(GetInventoryAmount(playerid, 646) == 0) return SendError(playerid, "У Вас нет семян.");

    new Float:pPos[3];
    GetPlayerPos(playerid, pPos[0], pPos[1], pPos[2]);

    DrugsInfo[idx][diPosX] = pPos[0];
    DrugsInfo[idx][diPosY] = pPos[1];
    DrugsInfo[idx][diPosZ] = pPos[2];
    DrugsInfo[idx][diInterior] = GetPlayerInterior(playerid);
    DrugsInfo[idx][diWorld] = GetPlayerVirtualWorld(playerid);
    DrugsInfo[idx][diPlanted] = 1;
    DrugsInfo[idx][diProg] = 0;

    GivePlayerInventory(playerid, 692, -1);
    GivePlayerInventory(playerid, 693, -1);
    GivePlayerInventory(playerid, 629, -1);

    DrugsInfo[idx][diOwnerID] = p_info[playerid][ID];

    DrugsInfo[idx][diObject] = CreateDynamicObject(3409, DrugsInfo[idx][diPosX], DrugsInfo[idx][diPosY], DrugsInfo[idx][diPosZ]-1.2, 0.0, 0.0, 0.0, DrugsInfo[idx][diWorld], DrugsInfo[idx][diInterior], -1, 120);
    ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0, 1);

    MeAction(playerid, "раскопал(-а) землю и посадил(-а) семена марихуаны");

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "INSERT INTO `drugs` (`ownerid`, `x`, `y`, `z`, `world`, `interior`, `prog`, `planted`) VALUES (%d, '%f', '%f', '%f', %d, %d, %d, %d)",
    DrugsInfo[idx][diOwnerID], DrugsInfo[idx][diPosX], DrugsInfo[idx][diPosY], DrugsInfo[idx][diPosZ], DrugsInfo[idx][diWorld], DrugsInfo[idx][diInterior], DrugsInfo[idx][diProg], DrugsInfo[idx][diPlanted]);
    mysql_tquery(con_bd, STRING_GLOBAL, "create_drugs", "i", idx);
    return 1;
}

CMD:ddrugs(playerid, params[])
{
    if(gang(playerid) == 0) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    new gangzone = GetGangZoneID(playerid);
    if(gangzone == INVALID_CRIMINAL_ZONE_ID) return SendError(playerid, "Вы не на территории гетто");
    /*if(GangZone_Info[gangzone][g_Fraction] != p_info[playerid][member]) return SendError(playerid, "Данная территория не принадлежит Вашей фракции.");*/

    for(new i = 1; i < MAX_DRUGS; i++)
    {
        if(PlayerToPoint(5.0, playerid, DrugsInfo[i][diPosX], DrugsInfo[i][diPosY], DrugsInfo[i][diPosZ]))
        {
            if(DrugsInfo[i][diOwnerID] != p_info[playerid][ID]) return SendError(playerid, "Данный куст Вам не принадлежит.");
            if(DrugsInfo[i][diPlanted] != 2) return SendError(playerid, "Данный куст еще нельзя собрать.");

            new drugsrandom = random(100);
            switch(drugsrandom)
            {
                case 0 .. 89:
                {
                    new count = RandomEx(250, 500), free_amount = GetInventoryFreeItems(playerid, 629);
                    if(count > free_amount) count = free_amount;
                    GivePlayerInventory(playerid, 629, count);
                    SendAccess(playerid, "Вы собрали %d гр. наркотиков.", count);
                }
                default:
                {
                    SendAccess(playerid, "Вы сорвали куст.");
                    SendInfo(playerid, "К сожалению, куст не дал плодов.");
                }
            }

            DrugsInfo[i][diPlanted] = 0;
            DrugsInfo[i][diProg] = 0;
            DrugsInfo[i][diOwnerID] = 0;
            if(IsValidDynamicObject(DrugsInfo[i][diObject])) DestroyDynamicObject(DrugsInfo[i][diObject]);
            ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0, 1);

            MeAction(playerid, "сорвал(-а) куст марихуаны и собрал(-а) наркотики");

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "DELETE FROM `drugs` WHERE `id` = %d",
            DrugsInfo[i][diID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            return 1;
        }
    }
    SendError(playerid, "Рядом с Вами нет кустой с наркотиками.");
    return 1;
}

CMD:sdrugs(playerid, params[])
{
    if(gang(playerid) == 0) return SendError(playerid, "Вы не можете пользоваться этой командой.");
    new gangzone = GetGangZoneID(playerid);
    if(gangzone == INVALID_CRIMINAL_ZONE_ID) return SendError(playerid, "Вы не на территории гетто");
    if(GangZone_Info[gangzone][g_Fraction] != p_info[playerid][member]) return SendError(playerid, "Данная территория не принадлежит Вашей фракции.");
    new count, str[32], newhour;

    if(timestamp_minute < 10)
    {
        timestamp_hour = timestamp_hour - 1;
        if(timestamp_hour == -1) timestamp_hour = 23;
    }
    STRING_GLOBAL = "[#] Состояние\tМожно собрать\tРасстояние\n", STRING_MIN[0] = EOS;
    for(new i = 1; i < MAX_DRUGS; i++)
    {
        if(DrugsInfo[i][diOwnerID] != p_info[playerid][ID]) continue;
        if(DrugsInfo[i][diProg] < 3)
        {
            newhour = (3 - DrugsInfo[i][diProg]) + timestamp_hour;
            if(timestamp_hour < 23 && newhour > 23) newhour = (DrugsInfo[i][diProg] + timestamp_hour) - 24;
            format(str, sizeof(str), "В %s%d:10:00", newhour < 10 ? "0" : "", newhour);
        }
        else str = "Сейчас";
        format(STRING_MIN, sizeof(STRING_MIN), ""I"[%d]"W" s\t%s\t%.0f метров\n", count + 1, DrugsInfo[i][diPlanted] == 1 ? "{"#cLIGHTRED"}Растут"W"" : "{"#cGREEN"}Выросли"W"", str, GetPlayerDistanceFromPoint(playerid, DrugsInfo[i][diPosX], DrugsInfo[i][diPosY], DrugsInfo[i][diPosZ]));
        strcat(STRING_GLOBAL, STRING_MIN);
        p_temp[playerid][p_listitem][count] = i;
        count++;
    }
    if(!count) return SendError(playerid, "Вы не сажали кусты с наркотиками.");
    ShowPlayerDialog(playerid, D_DRUGS_SEARCH, DIALOG_STYLE_TABLIST_HEADERS, ""I"Мои кусты", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}
