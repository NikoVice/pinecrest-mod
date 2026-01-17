/*

	About: custom packets
	Author: Noname

*/
///////////////////////////////////////////////////////////////////////
//new
//11AE1522D623B5CB1C119FDD8D31128765C3BD896B9
new m_szClientVersions[][] = {
    {"14DB9BDE5A38450042D3D72C65952846E2C6826946B"},// flin romanov no actual
    {"39FB2DEEDB49ACFB8D4EECE6953D2507988CCCF4410"}, // sobeit kota 0.03
    {"10EF38095514DBF164C8FD10438A3C9BCB4DA4A9E15"}, //71
    {"15121F6F18550C00AC4B4F8A167D0379BB0ACA99043"}, //70
    {"161186A32578A6E62CBD2BB46D56F7F061EDB3A15B0"}, //69
    {"1031CA8429843C9B8C178B65F3C73602578440D17F8"},// 47
    {"C4B408C3A1C34E2E544EF21678A53108B2B8AE2518"},
    {"1034FEB5335C789FDC51EC085C9C0B2A91DA79E696B"},
    {"10B3D2B1317ADD02CC1F680BC500A8BC0FD7AD42CE7"},
    {"149C15C7E69314B147D55069C245763C07DD8AB4429"}
};
const ClientJoin = 25;
const ID_RPC = 20;
const RPC_CustomHash = 202;
const RPC_CustomUIP = 221;
const RPC_CustomUID = 222;

#define MAX_SUSPICIOUS_IP 10


new suspiciousIp[MAX_SUSPICIOUS_IP][16];

forward LoadIPCheckedCallback(playerid);
public LoadIPCheckedCallback(playerid)
{
    new rows = cache_num_rows();
    if(!rows) return SendError(playerid, "Список IP пустой.");
    for(new i; i < rows; i++)
    {
        if(i >= MAX_SUSPICIOUS_IP) return SendError(playerid, "IP больше лимита - %d, загружено первых %d", MAX_SUSPICIOUS_IP, MAX_SUSPICIOUS_IP);
        cache_get_value_name(i, "ip", suspiciousIp[i], 16);
    }
    SendAccess(playerid, "Загружено %d IP's.", rows);
    return 1;
}

CMD:reloadips(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    mysql_pquery(con_bd, "SELECT * FROM `ip_logs_list` WHERE 1", "LoadIPCheckedCallback", "i", playerid);
    return 1;
}

const ID_CUSTOM_MODELS = 244;

IRawPacket:ID_CUSTOM_MODELS(playerid, BitStream:bs)
{
    static version, string[32 + 1], len;

    BS_ReadValue(bs,
    PR_IGNORE_BITS, 8,
    PR_UINT8, version,
    PR_UINT8, len,
    PR_STRING, string, len
    );

    if(!SRV_ID) print(string); // Раскоментируй для получения нового хеш-суммы

    if(strequals(string, "b036abb531e0ba732b863d3d26c04c14"))
    {
        p_temp[playerid][mobile_version] = CLIENT_VERSION_022023;
        p_info[playerid][p_settings][INTERFACE] = 1;
        p_info[playerid][p_settings][LOGO_ID] = 1;

        Logotype_Show(playerid);
        Logotype_Time(playerid);
    }
    else if(strequals(string, "9648a7795fb81931a44bfbff0613d112"))
    {
        p_temp[playerid][mobile_version] = CLIENT_VERSION_20022023;
        p_info[playerid][p_settings][INTERFACE] = 1;
        p_info[playerid][p_settings][LOGO_ID] = 1;

        Logotype_Show(playerid);
        Logotype_Time(playerid);
    }
    else
    {
        p_temp[playerid][mobile_version] = CLIENT_VERSION_112022;
        SendError(playerid, "У вас не последняя версия кэша игры, обновитесь. Скачать: flin-rp.com/pc");
    }
    p_temp[playerid][is_mobile] = false;
    return 1;
}

CMD:setmobilestatus(playerid, params[])
{
    if(p_info[playerid][admin] < 10) return 1;
    p_temp[playerid][is_mobile] = true;
    p_temp[playerid][mobile_version] = CLIENT_VERSION_20022023;

    new nick_name[MAX_PLAYER_NAME];
    f(nick_name, "%s%s", get_name(playerid), "[PC:L]");
    SetPlayerName(playerid, nick_name);
    return 1;
}

IRawPacket:ID_RPC(playerid, BitStream:bs)
{
    new rpcid, numberOfBitsOfData;

    BS_ReadValue(bs,
        PR_IGNORE_BITS, 8, // packet id
        PR_UINT8, rpcid,
        PR_CUINT32, numberOfBitsOfData
    );

    switch(rpcid)
    {
        case RPC_CustomHash:
        {
            new i_bit;
            BS_ReadValue(bs, PR_UINT32, i_bit);
            p_temp[playerid][is_mobile] = true;
            if(i_bit != 0)
            {
                p_temp[playerid][mobile_version] = i_bit;

                p_info[playerid][p_settings][INTERFACE] = 1;
                p_info[playerid][p_settings][LOGO_ID] = 1;

                Logotype_Show(playerid);
                Logotype_Time(playerid);
            }
            if(strequals(get_name(playerid), FD1)) SendInfo(playerid, "%d", i_bit);
        }
        /*
        case RPC_CustomUIP:
        {
            new numberLenString, customUIP[MAX_IP_LENGTH];
            BS_ReadValue(bs, PR_UINT32, numberLenString);
            BS_ReadValue(bs, PR_STRING, customUIP, numberLenString);

            if(!strequals(customUIP, "none"))
            {
                p_temp[playerid][session_IP][0] = EOS;
                strcat(p_temp[playerid][session_IP], customUIP);
            }

            if(!SRV_ID) 
            {
                f(STRING_GLOBAL, "[RPC customUIP] ID: %d | UIP: %s", playerid, p_temp[playerid][session_IP]);
                printf(STRING_GLOBAL);
                SendDebug(playerid, STRING_GLOBAL);
            }
        }
        case RPC_CustomUID:
        {
            new numberLenString;
            BS_ReadValue(bs, PR_UINT32, numberLenString);
            BS_ReadValue(bs, PR_STRING, p_temp[playerid][session_UID], numberLenString);

            if(strequals(p_temp[playerid][session_UID], "none"))
            {
                printf("pizda error");
                SendDebug(playerid, "pizda UID");
            }

            if(!SRV_ID) 
            {
                f(STRING_GLOBAL, "[RPC CustomUID] ID: %d | UID: %s", playerid, p_temp[playerid][session_UID]);
                printf(STRING_GLOBAL);
                SendDebug(playerid, STRING_GLOBAL);
            }
        }
        */
    }
    return 1;
}

public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
    if(LOG_PACKETS_IN && p_temp[playerid][is_doss_attack])
    {
        Log(LOG_Incoming, INFO, "ID: <%d> IP: <%s> | RPC: <%s> ",
                playerid, p_temp[playerid][session_IP], rpcid);
    }
    return 1;
}

const ID_PLAYER_SYNC = 207;
public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
    if(LOG_PACKETS_IN && p_temp[playerid][is_doss_attack])
    {
        Log(LOG_Incoming, INFO, "ID: <%d> | IP: <%s> | PKT: <%d>",
                playerid, p_temp[playerid][session_IP], packetid);
    }
    if(packetid == ID_PLAYER_SYNC)
    {
        new onFootData[PR_OnFootSync];
        BS_IgnoreBits(bs, 8);
        BS_ReadOnFootSync(bs, onFootData);
        if(onFootData[PR_specialAction] == SPECIAL_ACTION_ENTER_VEHICLE)
        {
            if(onFootData[PR_keys] & KEY_SPRINT)
            {
                onFootData[PR_keys] = onFootData[PR_keys] & ~KEY_SPRINT;
                BS_SetWriteOffset(bs, 8);
                BS_WriteOnFootSync(bs, onFootData);
            }
        }
    }
    return 1;
}

public OnOutcomingPacket(playerid, packetid, BitStream:bs)
{
    if(LOG_PACKETS_OUT && p_temp[playerid][is_doss_attack])
    {
        Log(LOG_Outcoming, INFO, "ID: <%d> | IP: <%s> | PKT: <%d>",
                playerid, p_temp[playerid][session_IP], packetid);
    }
    return 1;
}

CMD:getver(playerid, params[])
{
    SendInfo(playerid, "version: %d", p_temp[playerid][mobile_version]);
    return 1;
}

IRPC:ClientJoin(playerid, BitStream:bs)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    p_temp[playerid][time_auth] = timestamp;

    new tmplen, auth_key[65];
    BS_ReadValue(bs, PR_IGNORE_BITS, 40, PR_UINT8, tmplen);
    BS_ReadValue(bs, PR_IGNORE_BITS, (tmplen * 8) + 32, PR_STRING8, auth_key, sizeof(auth_key));
    //printf( "auth_key: %s ", auth_key);

    p_temp[playerid][no_valid_client] =
    p_temp[playerid][is_mobile] = false;
    p_temp[playerid][mobile_version] = 0;

    if(ServerInfo[BlockInvalidClient])
    {
        for(new i; i < sizeof(m_szClientVersions); i++)
        {
            if(strequals(auth_key, m_szClientVersions[i]))
            {
                p_temp[playerid][no_valid_client] = true;
                break;
            }
        }
    }
    if(!SRV_ID) printf(auth_key);
    if(p_temp[playerid][mobile_version] != -1)
    {
        if( strequals(auth_key, "C4B408C3A1C34E2E544EF21678A53108B2B8AE2518") ||
            strequals(auth_key, "1034FEB5335C789FDC51EC085C9C0B2A91DA79E696B") ||
            strequals(auth_key, "10B3D2B1317ADD02CC1F680BC500A8BC0FD7AD42CE7") ||
            strequals(auth_key, "149C15C7E69314B147D55069C245763C07DD8AB4429") ||
            strequals(auth_key, "13DEF05D2240620D328DC8918F763063038AFE16D88") ||
            strequals(auth_key, "D09E46CD6ECDD87BCE275DD1ADE2F001D64C8126B0") ||
            strequals(auth_key, "39FB2DEEDB49ACFB8D4EECE6953D2507988CCCF4410"))
        {
            SendInfo(playerid, "На сервере обновлен клиент, скачать его можно через новый лаунчер "SITE_URL".");
            //SendInfo(playerid, "Нам выдана приставка PC из-за старого клиента.");
            p_temp[playerid][mobile_version] = 145;
            p_temp[playerid][is_mobile] = true;
        }
        if(strequals(auth_key, "E02262CF28BC542486C558D4BE9EFB716592AFAF8B"))
        {
            p_temp[playerid][mobile_version] = 200;
            p_temp[playerid][is_mobile] = true;
        }
    }
    return 1;
}


#define RPC_CUSTOM_AIM 0x30

stock SendChangeAim(playerid, texture_name[])
{
	new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_CUSTOM_AIM);

    BS_WriteValue(bitstream, PR_UINT8, strlen(texture_name));
    BS_WriteValue(bitstream, PR_STRING, texture_name);

    PR_SendPacket(bitstream, playerid);

    BS_Delete(bitstream);
}

#define RPC_SET_SKY_SPEED 0x23

CMD:setskyboxspeed(playerid, params[])
{
    if(SRV_ID) return 1;
    if(sscanf(params, "i", params[0])) return SendInfo(playerid, "Используйте: /setskyboxspeed [speed]");
    SetSkySpeed(playerid, params[0]);
    return 1;
}

stock SetSkySpeed(playerid, speed)
{
    new BitStream:bitstream = BS_New();

    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_SET_SKY_SPEED);
    BS_WriteValue(bitstream, PR_UINT8, speed);

    PR_SendPacket(bitstream, playerid);
    BS_Delete(bitstream);
}

#define RPC_SET_SKYBOX 0x24

CMD:setskybox(playerid, params[])
{
    if(SRV_ID) return 1;
    SendChangeSkybox(params);
    return 1;
}

stock SendChangeSkybox(texture_name[])
{
	new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_SET_SKYBOX);

    BS_WriteValue(bitstream, PR_UINT8, strlen(texture_name));
    BS_WriteValue(bitstream, PR_STRING, texture_name);

    PR_SendPacket(bitstream, -1);

    BS_Delete(bitstream);
}

#define RPC_SET_RADARLINE 0x25

stock SendChangeRadarLine(playerid, type, texture_name[]) // type 0 - круг, type 1 - квадрат
{
    new BitStream:bitstream = BS_New();

    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_SET_RADARLINE);

    BS_WriteValue(bitstream, PR_UINT8, type);
    BS_WriteValue(bitstream, PR_UINT8, strlen(texture_name));
    BS_WriteValue(bitstream, PR_STRING, texture_name);

    PR_SendPacket(bitstream, playerid);
    BS_Delete(bitstream);
}
/*
IPacket:214(playerid, BitStream:bs)
{
    BS_IgnoreBits(bs, 8);
    new hash1, hash2, hash3, hash4, undreadedBits;
    BS_GetNumberOfUnreadBits(bs, undreadedBits);
    while (undreadedBits > 0) {
        BS_ReadValue(bs, PR_UINT32, hash1);
        BS_ReadValue(bs, PR_UINT32, hash2);
        BS_ReadValue(bs, PR_UINT32, hash3);
        BS_ReadValue(bs, PR_UINT32, hash4);

        BS_GetNumberOfUnreadBits(bs, undreadedBits);

        if(!SRV_ID)
        {
            printf("1: 0x%08x 2: 0x%08x 3: 0x%08x 4: 0x%08x", hash1, hash2, hash3, hash4);
            //printf("1: %d 2: %d 3: %d 4: %d", hash1, hash2, hash3, hash4);
        }
    }
    return 0;
}
*/
#define RPC_CHECK_CASH 0x26

stock SendCheckHash(playerid, texture_name[], cash_name[], cash_version)
{
    new BitStream:bitstream = BS_New();

    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_CHECK_CASH);

    BS_WriteValue(bitstream, PR_UINT8, strlen(texture_name));
    BS_WriteValue(bitstream, PR_STRING, texture_name);

    BS_WriteValue(bitstream, PR_UINT8, strlen(cash_name));
    BS_WriteValue(bitstream, PR_STRING, cash_name);

    BS_WriteValue(bitstream, PR_UINT32, cash_version);

    PR_SendPacket(bitstream, playerid);
    BS_Delete(bitstream);
}


#define RPC_SHOW_DONATE 0x27

stock SendShowDonate(playerid)
{
    new BitStream:bitstream = BS_New();

    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_SHOW_DONATE);

    PR_SendPacket(bitstream, playerid);
    BS_Delete(bitstream);
}

cmd:donateclient(playerid, params[])
{
    SendShowDonate(playerid);
    return 1;
}

enum {
    SKIN_ID, // Скин персонажа (Собественный айди)
    CLOTH_TORSO_PART, // Одежда на торс (Собественный айди) (Чтобы снять используется 0)
    CLOTH_HEAD_PART, // Одежда на голову (Не используется, следует оставить ради смещения числ в enum) (Чтобы снять используется 0)
    CLOTH_LEGS_PART, // Одежда на ноги (Собественный айди) (Чтобы снять используется 0)
    CLOTH_FEET_PART // Обувь (Собественный айди) (Чтобы снять используется 0)
}

#define RPC_SET_CLOTHES 0x28

stock SetPlayerClothes(playerid, forplayerid)
{
    new BitStream:bitstream = BS_New();

    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_SET_CLOTHES);
	BS_WriteValue(bitstream, PR_UINT16, forplayerid);

    BS_WriteValue(bitstream,
        PR_UINT8, p_info[forplayerid][chothes_part][SKIN_ID],
        PR_UINT8, p_info[forplayerid][chothes_part][CLOTH_TORSO_PART],
        //PR_UINT8, p_info[forplayerid][chothes_part][CLOTH_HEAD_PART],
        PR_UINT8, p_info[forplayerid][chothes_part][CLOTH_LEGS_PART],
        PR_UINT8, p_info[forplayerid][chothes_part][CLOTH_FEET_PART]);

    PR_SendPacket(bitstream, playerid);
    BS_Delete(bitstream);
}
/*
CMD:skintest(playerid, params[])
{
    if(SRV_ID) return 1;
    SetPlayerSkin(playerid, 360);
    //p_info[playerid][chothes_part][SKIN_ID] = 360;
    SendInfo(playerid, "SET SKIN ID: %d", GetPlayerSkin(playerid));
    return 1;
}

CMD:setchothes(playerid, params[])
{
    if(SRV_ID) return 1;
    if(GetPlayerSkin(playerid) != 360)
        return SendError(playerid, "У Вас не 360 скин.");
    if(sscanf(params, "iiii", params[0], params[1], params[2], params[3]))
        return SendInfo(playerid, "Используйте: /setchothes [skin ID] [torso ID] [legs ID] [feet ID]");
    if( !(0 <= params[0] <= 1) ||
        !(0 <= params[1] <= 11) ||
        !(0 <= params[2] <= 11) ||
        !(0 <= params[3] <= 5))
        return SendError(playerid, "Используйте: /setchothes [skin ID] [torso ID] [legs ID] [feet ID]");

    p_info[playerid][chothes_part][SKIN_ID] = params[0];
    p_info[playerid][chothes_part][CLOTH_TORSO_PART] = params[1];
    p_info[playerid][chothes_part][CLOTH_LEGS_PART] = params[2];
    p_info[playerid][chothes_part][CLOTH_FEET_PART] = params[3];

    foreach(new targetid: PlayerPlayersStream[playerid])
        SetPlayerClothes(targetid, playerid);
    SetPlayerClothes(playerid, playerid);
    return 1;
}
*/