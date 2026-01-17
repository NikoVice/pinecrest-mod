/*
    Pizda
*/

#define INVALID_OBJECTS_VERSION    0x3

#if defined _invalidobjects_included
    #endinput
#endif
#define _invalidobjects_included

#if !defined PAWNCMD_INC_
    #error "not connected include Pawn.RakNet"
#endif

#if defined RPC_CREATE_OBJECT
    #undef RPC_CREATE_OBJECT
    #define RPC_CREATE_OBJECT 44
#else
    #define RPC_CREATE_OBJECT 44
#endif

#if defined RPC_WORLDVEHICLE_ADD
    #undef RPC_WORLDVEHICLE_ADD
    #define RPC_WORLDVEHICLE_ADD 164
#else
    #define RPC_WORLDVEHICLE_ADD 164
#endif

#if defined RPC_SET_PLAYER_SKIN
    #undef RPC_SET_PLAYER_SKIN
    #define RPC_SET_PLAYER_SKIN 153
#else
    #define RPC_SET_PLAYER_SKIN 153
#endif

#if defined RPC_CLIENT_JOIN
    #undef RPC_CLIENT_JOIN
    #define RPC_CLIENT_JOIN 25
#else
    #define RPC_CLIENT_JOIN 25
#endif

#if defined RPC_CREATE_PICKUP
    #undef RPC_CREATE_PICKUP
    #define RPC_CREATE_PICKUP 95
#else
    #define RPC_CREATE_PICKUP 95
#endif

#define PICKUP_REPLACE_MODEL 1239

#define PLAYER_DEVICE_PC 0
#define PLAYER_DEVICE_ANDROID 1

enum E_PICKUP_STRUCT
{
    dPickupID,       // UINT32
    dModelID,           // UINT32
    dSpawnType,       // UINT32
    Float:pickupX,   // FLOAT
    Float:pickupY,   // FLOAT
    Float:pickupZ    // FLOAT
};

enum E_OBJECT_STRUCT
{
    e_wObjectID,             // INT16
    e_ModelID,                // UINT32
    Float:e_objectX,        // FLOAT
    Float:e_objectY,        // FLOAT
    Float:e_objectZ,        // FLOAT
    Float:e_rotx,            // FLOAT
    Float:e_roty,            // FLOAT
    Float:e_rotz,            // FLOAT
    float:e_DrawDistance,    // FLOAT
    e_NoCameraCol,            // UINT8
    e_attachedObject,        // UINT16
    e_attachedVehicle,        // UINT16
    float:e_AttachOffsetX,    // FLOAT
    float:e_AttachOffsetY,    // FLOAT
    float:e_AttachOffsetZ,    // FLOAT
    float:e_AttachRotX,        // FLOAT
    float:e_AttachRotY,        // FLOAT
    float:e_AttachRotZ,        // FLOAT
    e_SyncRotation             // UINT8

};

enum E_VEHICLE_STRUCT
{
    e_vVehicleID,             // INT16
    e_vModelID,                // UINT32
    Float:e_posX,
    Float:e_posY,
    Float:e_posZ,
    Float:e_rot,
    e_vColor1,
    e_vColor2,
    Float:e_vHealth,
    e_vInterior,
    e_vDoorDamageStatus,
    e_vPanelDamageStatus,
    e_vByteLightDamageStatus,
    e_vByteTimeDamageStatus,
    e_vByteAddSiren
};

enum E_PLAYER_STRUCT
{
    e_usPlayerID,
    e_bTeam,
    e_uiSkin,
    e_pfPosX,
    e_pfPosY,
    e_pfPosZ,
    e_pfRot,
    e_uiColor,
    e_bFighting,
    e_boolVisible
};

static dataObject[E_OBJECT_STRUCT];
static vehicleData[E_VEHICLE_STRUCT];
static playerData[E_PLAYER_STRUCT];

/*
static playerDevice[MAX_PLAYERS char];

stock setDeviceInfo(playerId, deviceType)
{
    playerDevice{playerId} = deviceType;
    return 1;
}

stock isInvalidObject(modelId)
{
    if(modelId < 11000)
        return -1;
    new returnval = -1;
    for(new it; it < sizeof(m_szSampModels); it++)
    {
        if(m_szSampModels[it] == modelId)
        {
            returnval = modelId;
            break;
        }
    }
    return returnval;
}
*/

enum e_customVeh
{
    CustomID,
    ModelID,
    ModelName[40],
    ModelPrice,
    Float:ModelMaxSpeed
}

#define MAX_VEH_MODELS_REPLACE (54+14)
new customVehModels[MAX_VEH_MODELS_REPLACE][e_customVeh] = {
    {3215, 411, "Bugatti Chiron",                               12500, 210.0},
    {3610, 579, "Mercedes G63 AMG 6x6 [Бронированный]",         15000, 169.0},
    {4546, 580, "Rolls-Royce Phantom",                          10000, 180.0},
    {3222, 541, "Ferrari Pista 488",                            9500,  193.0},
    {3248, 451, "McLaren 720s",                                 9500,  184.0},
    {3349, 560, "Porsche Panamero Turbo",                       8000,  180.0},
    {3219, 451, "McLaren 600LT",                                8000,  189.0},
    {3201, 411, "Bentley Continental",                          7500,  210.0},
    {3200, 579, "Bentley Bentayga",                             7500,  174.0},
    {3194, 411, "Aston Martin Vantage",                         7500,  209.0},
    {3870, 579, "Mercedes G63",                                 7000,  179.0},
    {3239, 561, "Mercedes-Maybach",                             7000,  185.0},
    {3210, 415, "BMW M8",                                       6500,  189.0},
    {3429, 579, "Range Rover SVR",                              6000,  173.0},
    {3233, 415, "Lexus LC",                                     5500,  188.0},

    {3245, 560, "Tesla Model S",                5000,  176.0},
    {3974, 541, "Nissan GTR",                   4500,  195.0},
    {3217, 579, "Cadillac Escalade",            3500,  174.0},
    {3247, 560, "Mercedes E63 AMG S",           3000,  176.0},
    {3235, 580, "Lexus LX570",                  2750,  173.0},
    {3205, 560, "Mercedes AMG GT63",            2750,  176.0},
    {3231, 579, "Land Cruiser 200",             2500,  174.0},
    {3211, 579, "BMW X5M",                      2500,  173.0},
    {3208, 560, "BMW M5 F90",                   2500,  176.0},
    {3197, 411, "Audi R8",                      2250,  210.0},
    {3204, 402, "BMW M4 F82",                   2000,  188.0},
    {3227, 400, "Jeep Grand Cherokee",          1750,  173.0},
    {3206, 560, "BMW M5 E60",                   1500,  175.0},

    {3199, 560, "Audi RS7",                     1500,  176.0},
    {3202, 550, "BMW E39",                      1250,  176.0},
    {3254, 560, "Mercedes C63 AMG",             1250,  177.0},
    {3234, 560, "Lexus IS",                     1250,  188.0},
    {3218, 560, "Camry XV 70",                  1250,  176.0},
    {4763, 579, "Tesla Cybertruck",             1000,  173.0},
    {3195, 507, "Audi 3",                       750,   196.0},
    {3883, 421, "Mercedes W124",                500,   182.0},
    {3784, 551, "Mercedes 230",                 400,   172.0},
    {3611, 551, "Mercedes 190E",                350,   181.0},
    {4766, 541, "Toyota Celica",                300,   182.0},
    {4764, 426, "Toyota Chaser",                250,   196.0},
    {3236, 551, "Toyota Mark II",               200,   182.0},

    {3196, 561, "ВАЗ 2109",                     2000,  141.0},
    {3207, 560, "Subaru Impreza WRX STI",       2500,  177.0},
    {3416, 550, "Honda Accord",                 3000,  185.0},
    {3251, 562, "Nissan 370Z",                  3500,  200.0},
    {3198, 463, "Harley-Davidson",              4000,  148.0},
    {3224, 475, "Opel GT",                      4500,  210.0},
    {3209, 560, "KIA K5",                       5000,  192.0},
    {3871, 541, "Dodge Challenger SRT 8",       7500,  190.0},
    {3220, 579, "Infiniti QX80",                7500,  170.0},
    {3240, 579, "Hummer H2",                    7500,  190.0},
    {4765, 522, "Suzuki Hayabusa",              10000, 195.0},
    {4545, 541, "Porsche 911",                  12500, 225.0},
    {3212, 541, "Lamborghini Veneno Roadster",  15000, 225.0},
    //Новые от 03.02.2023
    {4785, 541, "Pegassi Lampo CG22",           7500, 225.0},
    {4786, 541, "Benefactor SM-722",            6500, 215.0},
    {4787, 541, "Emperor Vectre",               6000, 215.0},
    {4788, 541, "Imponte Ruiner ZZ",            6500, 210.0},
    {4789, 579, "Mammoth Patriot",              7500, 170.0},
    {4790, 541, "Overflod Zeno",                6500, 225.0},
    {4791, 541, "Pegassi Torero",               6500, 225.0},
    {4794, 579, "BMW X6M",                      2800, 180.0},
    {5090, 405, "VAZ 2102",                     800, 110.0},
    {5092, 504, "Vapid Peyote",                 800, 130.0},
    {5095, 479, "УАЗ",                          800, 110.0},
    {5096, 467, "Волга",                        1000, 160.0},
    {5097, 500, "Нива",                         1000, 145.0},
    {5101, 467, "Ferrari F50",                  4500, 180.0}
};

GetSlotVehicleModelSync(modelid)
{
    for(new i = MAX_VEH_MODELS_REPLACE-1; i != -1; i--)
    {
        if(customVehModels[i][CustomID] == modelid)
            return i;
    }
    return -1;
}

#define MAX_SKIN_MODELS_REPLACE 22
static skinModels[MAX_SKIN_MODELS_REPLACE][] = {
    {793, 287},
    {794, 5},
    {795, 83},
    {796, 283},
    {797, 285},
    {798, 86},
    {799, 103},
    {907, 175},
    {908, 73},
    {909, 81},
    {965, 22},
    {999, 80},
    {1194, 29},
    {1195, 2},
    {1196, 108},
    {1197, 114},
    {1198, 37},
    {1199, 270},
    {1200, 279},
    {1201, 269},
    {1202, 280},
    {1203, 107}
};

stock getDefaultSkinModel(modelId)
{
    for(new i = 0; i < MAX_SKIN_MODELS_REPLACE; i++)
    {
        if(skinModels[i][0] == modelId)
        {
            return skinModels[i][1];
        }
    }
    return -1;
}

/*
#define MAX_OBJECT_MODELS_REPLACE  3
static objModels[MAX_OBJECT_MODELS_REPLACE] = { 1241, 13182, 9183 };

stock isInvalidObjectModel(modelId)
{
    for(new i = 0; i < MAX_OBJECT_MODELS_REPLACE; i++)
    {
        if(objModels[i] == modelId)
        {
            return 1;
        }
    }
    return 0;
}

stock getReplacableObjectModel(modelId)
{
    for(new i = 0; i < MAX_OBJECT_MODELS_REPLACE; i++)
    {
        if(objModels[i][0] == modelId)
        {
            return skinModels[i][1];
        }
    }
    return -1;
}
*/
#if defined _inc_y_hooks || defined _INC_y_hooks
    hook OnIncomingRPC(playerid, rpcid, BitStream:bs)
#else
    public OnIncomingRPC(playerid, rpcid, BitStream:bs)
#endif
    {
        #if defined INCLUDE_OnIncomingRPC
            return INCLUDE_OnIncomingRPC(playerid, rpcid, BitStream:bs);
        #else
            return 1;
        #endif
    }

#if !defined _inc_y_hooks && !defined _INC_y_hooks
    #if defined _ALS_OnIncomingRPC
        #undef OnIncomingRPC
    #else
        #define _ALS_OnIncomingRPC
    #endif

    #define OnIncomingRPC INCLUDE_OnIncomingRPC
    #if defined INCLUDE_OnIncomingRPC
        forward INCLUDE_OnIncomingRPC(playerid, rpcid, BitStream:bs);
    #endif
#endif

#define RPC_ScrGivePlayerWeapon 22
#define RPC_ScrSetPlayerAttachedObject 113
#define RPC_WorldPlayerAdd 32

stock ReplaceSkinToDefault(playerid, BitStream:bs)
{
    new player, skinid;
    BS_ReadValue(
        bs,
        PR_UINT32, player,
        PR_UINT32, skinid);

    if(skinid > 311 &&
        (!ServerInfo[RealSkinsStatus] ||
        GetPlayerGameVersion(playerid) < CLIENT_VERSION_20022023 ||
        !p_info[playerid][p_settings][REAL_SKINS]))
    {
        skinid = getDefaultSkinModel(skinid);
        if(skinid == -1) skinid = 0;
        new BitStream:bitstream = BS_New();
        BS_WriteValue( bitstream, PR_UINT32, player, PR_UINT32, skinid);
        PR_SendRPC(bitstream, playerid, RPC_SET_PLAYER_SKIN, PR_HIGH_PRIORITY, PR_RELIABLE_SEQUENCED);
        BS_Delete(bitstream);
        return 1;
    }
    return 0;
}

stock ReplaceSkinToDefaultAdd(playerid, BitStream:bs)
{
    static clearPlayerData[E_PLAYER_STRUCT];
    playerData = clearPlayerData;

    BS_ReadValue(
        bs,
        PR_INT16, playerData[e_usPlayerID],
        PR_UINT8, playerData[e_bTeam],
        PR_UINT32, playerData[e_uiSkin],
        PR_FLOAT, playerData[e_pfPosX],
        PR_FLOAT, playerData[e_pfPosY],
        PR_FLOAT, playerData[e_pfPosZ],
        PR_FLOAT, playerData[e_pfRot],
        PR_UINT32, playerData[e_uiColor],
        PR_UINT8, playerData[e_bFighting],
        PR_BOOL, playerData[e_boolVisible]);

    if(playerData[e_uiSkin] > 311 &&
        (!ServerInfo[RealSkinsStatus] ||
        GetPlayerGameVersion(playerid) < CLIENT_VERSION_20022023 ||
        !p_info[playerid][p_settings][REAL_SKINS]))
    {
        playerData[e_uiSkin] = getDefaultSkinModel(playerData[e_uiSkin]);
        if(playerData[e_uiSkin] == -1) playerData[e_uiSkin] = 0;
        new BitStream:bitstream = BS_New();
        BS_WriteValue(
            bitstream,
            PR_INT16, playerData[e_usPlayerID],
            PR_UINT8, playerData[e_bTeam],
            PR_UINT32, playerData[e_uiSkin],
            PR_FLOAT, playerData[e_pfPosX],
            PR_FLOAT, playerData[e_pfPosY],
            PR_FLOAT, playerData[e_pfPosZ],
            PR_FLOAT, playerData[e_pfRot],
            PR_UINT32, playerData[e_uiColor],
            PR_UINT8, playerData[e_bFighting],
            PR_BOOL, playerData[e_boolVisible]);

        PR_SendRPC(bitstream, playerid, RPC_WorldPlayerAdd, PR_HIGH_PRIORITY, PR_RELIABLE_SEQUENCED);
        BS_Delete(bitstream);
        return 1;
    }
    return 0;
}

stock ProcessReplaceVehicle(playerid, BitStream:bs)
{
    static clearVehicleData[E_VEHICLE_STRUCT];
    vehicleData = clearVehicleData;
    new modSlots[14];
    new bytePaintJob;
    new color1, color2;

    BS_ReadValue(bs,
        PR_INT16, vehicleData[e_vVehicleID],
        PR_UINT32, vehicleData[e_vModelID],
        PR_FLOAT, vehicleData[e_posX],
        PR_FLOAT, vehicleData[e_posY],
        PR_FLOAT, vehicleData[e_posZ],
        PR_FLOAT, vehicleData[e_rot],
        PR_UINT8, vehicleData[e_vColor1],
        PR_UINT8, vehicleData[e_vColor2],
        PR_FLOAT, vehicleData[e_vHealth],
        PR_UINT8, vehicleData[e_vInterior],
        PR_UINT32, vehicleData[e_vDoorDamageStatus],
        PR_UINT32, vehicleData[e_vPanelDamageStatus],
        PR_UINT8, vehicleData[e_vByteLightDamageStatus],
        PR_UINT8, vehicleData[e_vByteTimeDamageStatus],
        PR_UINT8, vehicleData[e_vByteAddSiren]);
    for(new i = 0; i < 14; i++)
    {
        BS_ReadValue(bs, PR_UINT8, modSlots[i]);
    }
    BS_ReadValue(bs, PR_UINT8, bytePaintJob);
    BS_ReadValue(bs, PR_UINT32, color1, PR_UINT32, color2);

    new custom_model = veh_info[vehicleData[e_vVehicleID]][v_model];

    if(!(400 <= custom_model <= 611))
    {
        new BitStream:bitstream = BS_New();

        BS_WriteValue(
            bitstream,
            PR_INT16, vehicleData[e_vVehicleID],
            PR_UINT32, custom_model,
            PR_FLOAT, vehicleData[e_posX],
            PR_FLOAT, vehicleData[e_posY],
            PR_FLOAT, vehicleData[e_posZ],
            PR_FLOAT, vehicleData[e_rot],
            PR_UINT8, vehicleData[e_vColor1],
            PR_UINT8, vehicleData[e_vColor2],
            PR_FLOAT, vehicleData[e_vHealth],
            PR_UINT8, vehicleData[e_vInterior],
            PR_UINT32, vehicleData[e_vDoorDamageStatus],
            PR_UINT32, vehicleData[e_vPanelDamageStatus],
            PR_UINT8, vehicleData[e_vByteLightDamageStatus],
            PR_UINT8, vehicleData[e_vByteTimeDamageStatus],
            PR_UINT8, vehicleData[e_vByteAddSiren]);

        for(new i = 0; i < 14; i++)
        {
            BS_WriteValue(bitstream, PR_UINT8, modSlots[i]);
        }
        BS_WriteValue(bitstream, PR_UINT8, bytePaintJob);
        BS_WriteValue(bitstream, PR_UINT32, color1, PR_UINT32, color2);

        PR_SendRPC(bitstream, playerid, RPC_WORLDVEHICLE_ADD, PR_HIGH_PRIORITY, PR_RELIABLE_SEQUENCED);
        BS_Delete(bitstream);
        return 1;
    }
    return 0;
}
stock IsShouldSendCreateObject(playerid, BitStream:bs)
{
    static clearDataObject[E_OBJECT_STRUCT];
    dataObject = clearDataObject;

    BS_ReadValue(
        bs,
        PR_INT16, dataObject[e_wObjectID],
        PR_UINT32, dataObject[e_ModelID],
        PR_FLOAT, dataObject[e_objectX],
        PR_FLOAT, dataObject[e_objectY],
        PR_FLOAT, dataObject[e_objectZ],
        PR_FLOAT, dataObject[e_rotx],
        PR_FLOAT, dataObject[e_roty],
        PR_FLOAT, dataObject[e_rotz],
        PR_FLOAT, dataObject[e_DrawDistance],
        PR_UINT8, dataObject[e_NoCameraCol],
        PR_UINT16, dataObject[e_attachedObject],
        PR_UINT16, dataObject[e_attachedVehicle],
        PR_FLOAT, dataObject[e_AttachOffsetX],
        PR_FLOAT, dataObject[e_AttachOffsetY],
        PR_FLOAT, dataObject[e_AttachOffsetZ],
        PR_FLOAT, dataObject[e_AttachRotX],
        PR_FLOAT, dataObject[e_AttachRotY],
        PR_FLOAT, dataObject[e_AttachRotZ],
        PR_UINT8, dataObject[e_SyncRotation]);

    if(isInvalidObjectModel(dataObject[e_ModelID]))
    {
        return 0;
    }
    return 1;
}

stock IsShouldSendCreateAttached(playerid, BitStream:bs)
{
    new sPlayerID, iSlot, bCreate;
       BS_ReadValue(
        bs,
        PR_UINT16, sPlayerID,
        PR_UINT32, iSlot,
        PR_BOOL,   bCreate);
    if(bCreate)
    {
         new modelid;
           BS_ReadValue(bs, PR_UINT32, modelid);
        if(isInvalidObjectModel(modelid))
        {
            return 0;
           }
    }
    return 1;
}

#define WEAPON_SECURE 0x100
#define WEAPON_SECURE_KEY    0x15

#if defined _inc_y_hooks || defined _INC_y_hooks
    hook OnOutcomingRPC(playerid, rpcid, BitStream:bs)
#else
    public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
#endif
    {
        if(playerid == -1) return 1;
/*
        if(rpcid == RPC_CREATE_OBJECT)
        {
            if(IsPlayerMobile(playerid)) // если игрок с ведра
            {
                //if(getPlayerAndroidVers(playerid) < server_invalid_client) // если у игрока версия, которая ниже версии клиента с лимитом и модпаком
                {
                    if(!IsShouldSendCreateObject(playerid, bs)) // если модель невалидная, то не отсылаем
                    {
                        new _frmtsrt[50];
                        format(_frmtsrt, sizeof(_frmtsrt), "[Warning] Bad object model: 32");
                        SendClientMessage(playerid, 0xa9c4e4FF, _frmtsrt);
                        return 0;
                    }
                }
            }
            else // иначе игрок с ПК
            {
                if(!IsShouldSendCreateObject(playerid, bs)) // если модель невалидная, то не отсылаем
                {
                    new _frmtsrt[50];
                    format(_frmtsrt, sizeof(_frmtsrt), "[Warning] Bad object model: 32");
                    SendClientMessage(playerid, 0xa9c4e4FF, _frmtsrt);
                    return 0;
                }
            }
        }
        else if(rpcid == RPC_ScrGivePlayerWeapon) // серверная защита
        {
            new val1, val2;
            BS_ReadValue(
                 bs,
                   PR_UINT32, val1,
                PR_UINT32, val2);

            new BitStream:bitstream = BS_New();
            BS_WriteValue(
                  bitstream,
                PR_UINT32, val1,     //id
                PR_UINT32, val2,        //model
                PR_UINT32, WEAPON_SECURE ^ WEAPON_SECURE_KEY
            );
            PR_SendRPC(bitstream, playerid, RPC_ScrGivePlayerWeapon, PR_HIGH_PRIORITY, PR_RELIABLE_SEQUENCED);
            BS_Delete(bitstream);
            return 0;
        }
        else if(rpcid == RPC_ScrSetPlayerAttachedObject)
        {
            if(IsPlayerMobile(playerid)) // если игрок с ведра
            {
                //if(getPlayerAndroidVers(playerid) < server_invalid_client) // если у игрока версия, которая ниже версии клиента с лимитом и модпаком
                {
                    if(!IsShouldSendCreateAttached(playerid, bs)) // если модель невалидная, то не отсылаем
                    {
                        new _frmtsrt[50];
                        format(_frmtsrt, sizeof(_frmtsrt), "[Warning] Bad object mode1: 33");
                        SendClientMessage(playerid, 0xa9c4e4FF, _frmtsrt);
                        return 0;
                    }
                }
            }
            else // иначе игрок с ПК
            {
                if(!IsShouldSendCreateAttached(playerid, bs)) // если модель невалидная, то не отсылаем
                {
                       new _frmtsrt[50];
                    format(_frmtsrt, sizeof(_frmtsrt), "[Warning] Bad object model: 33");
                    SendClientMessage(playerid, 0xa9c4e4FF, _frmtsrt);
                    return 0;
                }
            }
        }
        */

        if(rpcid == RPC_WORLDVEHICLE_ADD)
        {
            if(ServerInfo[RealCarsStatus] && GetPlayerGameVersion(playerid) >= CLIENT_VERSION_022023 && p_info[playerid][p_settings][REAL_CARS]) // если у игрока версия, которая нужна для работы реал карс
            {
                if(ProcessReplaceVehicle(playerid, bs)) // если модель была заменена успешно, то оригинальный пакет не отсылаем
                    return 0;
            }
        }
        else if(rpcid == RPC_SET_PLAYER_SKIN)
        {
            if(ReplaceSkinToDefault(playerid, bs)) // если модель заменена на дефолтную то пакет не отправляем
                return 0;
        }
        else if(rpcid == RPC_WorldPlayerAdd)
        {
            if(ReplaceSkinToDefaultAdd(playerid, bs)) // если модель заменена на дефолтную то пакет не отправляем
                return 0;
        }
        /*
        else if(rpcid == RPC_CREATE_PICKUP)
        {
            if(IsPlayerMobile(playerid))
            {
                if(getPlayerAndroidVers(playerid) < server_invalid_client)
                {
                    new dataPickup[E_PICKUP_STRUCT];
                    BS_ReadValue(
                        bs,
                        PR_UINT32, dataPickup[dPickupID],
                        PR_UINT32, dataPickup[dModelID],
                        PR_UINT32, dataPickup[dSpawnType],
                        PR_FLOAT, dataPickup[pickupX],
                        PR_FLOAT, dataPickup[pickupY],
                        PR_FLOAT, dataPickup[pickupZ]
                        );

                    if(isInvalidObject(dataPickup[dModelID]) != -1)
                    {
                        new _frmtsrt[50];
                        format(_frmtsrt, sizeof(_frmtsrt), "[Warning] Bad pickup model: %d(%d)", dataPickup[dModelID], dataPickup[dPickupID]);
                        SendClientMessage(playerid, 0xa9c4e4FF, _frmtsrt);
                        // переписать модель
                        new BitStream:bitstream = BS_New();
                        BS_WriteValue(
                            bitstream,
                            PR_UINT32, dataPickup[dPickupID],     //id
                            PR_UINT32, PICKUP_REPLACE_MODEL,    //model
                            PR_UINT32, dataPickup[dSpawnType],  //type.
                            PR_FLOAT, dataPickup[pickupX],         //x.
                            PR_FLOAT, dataPickup[pickupY],         //y.
                            PR_FLOAT, dataPickup[pickupZ]         //z.
                        );
                        PR_SendRPC(bitstream, playerid, RPC_CREATE_PICKUP, PR_HIGH_PRIORITY, PR_RELIABLE_SEQUENCED);
                        BS_Delete(bitstream);
                        return 0;
                    }
                }
            }
        }
*/
        if(LOG_PACKETS_OUT && p_temp[playerid][is_doss_attack])
        {
            Log(LOG_Outcoming, INFO, "ID: <%d> | IP: <%s> | RPC: <%d>",
                    playerid, p_temp[playerid][session_IP], rpcid);
        }
        #if defined INCLUDE_OnOutcomingRPC
            return INCLUDE_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
        #else
            return 1;
        #endif
    }

#if !defined _inc_y_hooks && !defined _INC_y_hooks
    #if defined _ALS_OnOutcomingRPC
        #undef OnOutcomingRPC
    #else
        #define _ALS_OnOutcomingRPC
    #endif

    #define OnOutcomingRPC INCLUDE_OnOutcomingRPC
    #if defined INCLUDE_OnOutcomingRPC
        forward INCLUDE_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
    #endif
#endif

CMD:skintags(playerid)
{
    if(GetPlayerVirtualWorld(playerid) == playerid+1000 || p_info[playerid][pfreeze] == 0) return 1;
    Fix_TogglePlayerControllable(playerid, false);
    p_info[playerid][p_settings][REAL_SKINS] ^= 1;
    SetTimerEx("ToggleVisibleSync", 2500, false, "ii", playerid, GetPlayerVirtualWorld(playerid));
    SetPlayerVirtualWorld(playerid, playerid+1000);
    SendAccess(playerid, "Вы %s отображение новых скинов.", p_info[playerid][p_settings][REAL_SKINS] == 0 ? "выключили" : "включили");
    UpdatePlayerSetting(playerid);
    return 1;
}


CMD:vehicletags(playerid)
{
    if(GetPlayerVirtualWorld(playerid) == playerid+1000 || p_info[playerid][pfreeze] == 0) return 1;
    Fix_TogglePlayerControllable(playerid, false);
    p_info[playerid][p_settings][REAL_CARS] ^= 1;
    SetTimerEx("ToggleVisibleSync", 2500, false, "ii", playerid, GetPlayerVirtualWorld(playerid));
    SetPlayerVirtualWorld(playerid, playerid+1000);
    SendAccess(playerid, "Вы %s отображение новых моделей т/с.", p_info[playerid][p_settings][REAL_CARS] == 0 ? "выключили" : "включили");
    UpdatePlayerSetting(playerid);
    return 1;
}

CMD:vehnumtags(playerid)
{
    if(GetPlayerVirtualWorld(playerid) == playerid+1000 || p_info[playerid][pfreeze] == 0) return 1;
    Fix_TogglePlayerControllable(playerid, false);
    p_info[playerid][p_settings][NUMBER_VEHICLES] ^= 1;
    SetTimerEx("ToggleVisibleSync", 2500, false, "ii", playerid, GetPlayerVirtualWorld(playerid));
    SetPlayerVirtualWorld(playerid, playerid+1000);
    SendAccess(playerid, "Вы %s отображение номеров на т/с.", p_info[playerid][p_settings][NUMBER_VEHICLES] == 0 ? "выключили" : "включили");
    UpdatePlayerSetting(playerid);
    return 1;
}

forward ToggleVisibleSync(playerid, old_vw_id);
public ToggleVisibleSync(playerid, old_vw_id)
{
    SetPlayerVirtualWorld(playerid, old_vw_id);
    Fix_TogglePlayerControllable(playerid, true);
    return 1;
}
/*
CMD:testcar(playerid, params[])
{
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleMaxSpeed(vehicleid, 40.0);
    SetVehicleGear(vehicleid, 3.1);
    SetVehicleAcceleration(vehicleid, 25.0);
    SetVehicleMass(vehicleid, 10000.0);
    return 1;
}
*/
cmd:setmass(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleMass(vehicleid, fValue);
    return 1;
}

cmd:setacc(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleAcceleration(vehicleid, fValue);
    return 1;
}

cmd:setgear(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleGear(vehicleid, fValue);
    return 1;
}

cmd:setspeed(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleMaxSpeed(vehicleid, fValue);
    return 1;
}

cmd:settcoef(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleTractionCoef(vehicleid, fValue);
    return 1;
}

cmd:setbias(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleSuspensionBias(vehicleid, fValue);
    return 1;
}

cmd:setlower(playerid, params[])
{
    if(SRV_ID) return 1;
    new Float:fValue;
    if(sscanf(params, "f", fValue)) return SendError(playerid, "error");
    new vehicleid = GetPlayerVehicleID(playerid);
    SetVehicleSuspensionLower(vehicleid, fValue);
    return 1;
}
