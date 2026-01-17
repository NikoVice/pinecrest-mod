/*
    Author: Vip_Uzer
    2.11.2022
    Exlusive for Flin Mobile
*/
#define MAX_SITDOWN 500
#define MAX_SITDOWN_PLACES 6

enum
{
    SD_TYPE_CHAIRS,
    SD_TYPE_BED,
    SD_TYPE_SOFA
}
static SitDown_Name[][] = {"сесть", "лечь", "сесть"};

/*
enum E_OFFSET_SEAT
{
    OFFSET_SEAT_NONE = 0,
    OFFSET_SEAT_LEFT = 1,
    OFFSET_SEAT_RIGHT = 2,
    OFFSET_SEAT_LEFT_AROUND = 3,
    OFFSET_SEAT_RIGHT_AROUND = 4
}
*/
enum e_SitDown_Init
{
    sd_ModelID,
    sd_Type,

    Float:sd_SitDown_Bias_UD, // смещение X и Y вперед/Назад
    Float:sd_SitDown_Bias_LR, // смещение X и Y вправо/влево
    Float:sd_SitDown_Bias_Z, // При посадке смещение Z
    Float:sd_SitDown_RZ, // Фикс куда смотрит обьект
    Float:sd_Radius, // радиус зоны посадки

    sd_Places,//Количество мест на
    //0 - нет смещения | 1 - напрвао | 2 - налево | 3 - по кругу налево | 4 - по кругу направо
    Float:sd_Seats_Distance,//Дистанция  на которую сдвигаются последующие места
    Float:sd_Fix_Z,//Фиксация оси Z. Необходимо чтобы проверить, стоит ли стул на позиции такой же или  меньше. Чтобы не проваливаться и садиться нормально
}

static SitDown_Init[][e_SitDown_Init] =
{
    /*0*/{1805,  SD_TYPE_CHAIRS,       0.4, 0.0,         0.25,    0.0,      1.0,    1,  0.0,        -0.8},
    /*1*/{2350,  SD_TYPE_CHAIRS,       0.4, 0.0,         0.25,    0.0,      1.0,    1,  0.0,        -1.0},
    /*2*/{2636,  SD_TYPE_CHAIRS,       0.45, 0.0,         0.25,    90.0,     1.0,   1,  0.0,        -0.45},
    /*3*/{1811,  SD_TYPE_CHAIRS,       0.40, 0.0,         0.25,    90.0,     1.0,    1,  0.0,        -0.5},
    /*4*/{2292,  SD_TYPE_CHAIRS,       0.7, 0.0,         0.25,    225.0,    1.0,   1,  0.0,        -1.0},
    /*5*/{1721,  SD_TYPE_CHAIRS,       0.6, 0.0,         0.3,     0.0,      1.0,    1,  0.0,        -1.0},
    /*6*/{2356,  SD_TYPE_CHAIRS,       0.6, 0.0,         0.5,     0.0,      1.0,    1,  0.0,        -1.0},
    /*7*/{1810,  SD_TYPE_CHAIRS,      0.40, 0.2,         0.5,      180.0,      1.0,    1,  0.0,       -1.0},
    /*8*/{19996,  SD_TYPE_CHAIRS,     0.6, 0.0,         0.5,      180.0,      1.0,    1,  0.0,        -1.0},
    /*9*/{19994,  SD_TYPE_CHAIRS,     0.5, 0.0,         0.5,      180.0,      1.0,    1,  0.0,        -1.0},
    /*10*/{1663,  SD_TYPE_CHAIRS,      0.5, -0.05,         0.5,     180.0,      1.0,    1,  0.0,       -0.55},
    /*11*/{1671,  SD_TYPE_CHAIRS,      0.5, -0.05,         0.5,     180.0,      1.0,    1,  0.0,       -0.55},
    /*12*/{1720,  SD_TYPE_CHAIRS,      0.30, -0.05,         0.5,     180.0,      1.0,    1,  0.0,       -1.0},
    /*13*/{2096,  SD_TYPE_CHAIRS,      0.4, 0.0,         0.5,     180.0,      1.0,    1,  0.0,       -1.0},
    /*14*/{2121,  SD_TYPE_CHAIRS,      0.6, 0.0,         0.5,     180.0,      1.0,    1,  0.0,       -0.6},
    /*15*/{2310,  SD_TYPE_CHAIRS,      0.45, 0.0,         0.5,     90.0,      1.0,    1,  0.0,       -0.55},
    /*16*/{2776,  SD_TYPE_CHAIRS,      0.4, -0.05,       0.5,     180.0,      1.0,    1,  0.0,      -0.6},
    /*17*/{2777,  SD_TYPE_CHAIRS,      0.4, -0.05,       0.5,     180.0,      1.0,    1,  0.0,      -0.6},
    /*18*/{1722,  SD_TYPE_CHAIRS,      0.7, 0.0,         0.5,     0.0,      1.0,    1,  0.0,        -1.0},
    /*19*/{2788,  SD_TYPE_CHAIRS,      0.45, 0.0,         0.5,     90.0,      1.0,    1,  0.0,        -0.5},
    /*20*/{2807,  SD_TYPE_CHAIRS,      0.45, 0.0,         0.5,     90.0,      1.0,    1,  0.0,        -0.5},
    /*21*/{2079,  SD_TYPE_CHAIRS,      0.45, 0.0,         0.5,     90.0,      1.0,    1,  0.0,        -0.5},
    /*22*/{1806,  SD_TYPE_CHAIRS,      0.6, 0.0,         0.5,     0.0,      1.0,    1,  0.0,        -1.0},
    /*23*/{2123,  SD_TYPE_CHAIRS,      0.45, 0.0,         0.5,     90.0,      1.0,    1,  0.0,        -0.5},
    /*24*/{1715,  SD_TYPE_CHAIRS,      0.6, 0.0,         0.5,     180.0,      1.0,    1,  0.0,        -1.0},
    /*25*/{2120,  SD_TYPE_CHAIRS,      0.5, 0.0,         0.5,     90.0,      1.0,    1,  0.0,        -0.5},
    /*26*/{2724,  SD_TYPE_CHAIRS,      0.40, 0.0,         0.5,     180.0,      1.0,    1,  0.0,        -0.5},
    /*27*/{2309,  SD_TYPE_CHAIRS,      0.6, 0.0,         0.5,     0.0,      1.0,    1,  0.0,        -1.0},
    /*28*/{1714,  SD_TYPE_CHAIRS,      0.6, 0.0,         0.5,     180.0,      1.0,    1,  0.0,        -1.0},
    /*29*/{11734,  SD_TYPE_CHAIRS,     0.55, 0.0,         0.5,    180.0,      1.0,    1,  0.0,     -1.1},
    /*30*/{1735,  SD_TYPE_CHAIRS,      0.6, 0.0,         0.5,     180.0,      1.0,    1,  0.0,        -1.0},
    /*31*/{2124,  SD_TYPE_CHAIRS,      0.4, 0.0,         0.5,     90.0,      1.0,    1,  0.0,        -0.25},
    /*32*/{2343,  SD_TYPE_CHAIRS,      0.45, 0.0,         0.5,     270.0,      1.0,    1,  0.0,        -0.5},
    /*33*/{19999,  SD_TYPE_CHAIRS,     0.5, 0.0,         0.5,    180.0,      1.0,    1,  0.0,     -1.0},
    //////////////////////////////////////////////////////
    /*34*/{11720 , SD_TYPE_BED,      -0.35, -0.4,          0.5,     180.0,      1.5,    2,  -0.75,    -1.0},
    /*35*/{2090 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.75,        -1.0},
    /*36*/{1796 ,  SD_TYPE_BED,      -2.5, -0.1,          0.5,     180.0,      1.0,    1,  0.0,       -1.0},
    /*37*/{2300 ,  SD_TYPE_BED,      -2.5, -1.0,          0.5,     180.0,      1.0,    2,  0.75,         -1.0},
    /*38*/{2563 ,  SD_TYPE_BED,      -1.25, -1.1,          0.5,     180.0,      1.0,    2,  0.75,         -1.0},
    /*39*/{1795 ,  SD_TYPE_BED,      -2.5, -0.25,          0.5,     180.0,      1.0,    2,  0.75,        -1.0},
    /*40*/{1799 ,  SD_TYPE_BED,      -2.5, 0.0,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*41*/{1797 ,  SD_TYPE_BED,      -2.5, -0.15,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*42*/{1801 ,  SD_TYPE_BED,      -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*43*/{1802 ,  SD_TYPE_BED,      -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*44*/{1725 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,       -1.0},
    /*45*/{2299 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*46*/{14446 ,  SD_TYPE_BED,    -0.5, 1.25,          0.5,     180.0,      1.0,    4,  0.85,        -0.5},
    /*47*/{2298 ,  SD_TYPE_BED,     -2.6, -0.9,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*48*/{2302 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*49*/{1798 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*50*/{1745 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*51*/{1701 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*52*/{2566 ,  SD_TYPE_BED,     -1.5, -1.1,          0.5,     180.0,      1.0,    2,  0.85,        -0.5},
    /*53*/{1794 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*54*/{1700 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /*55*/{2575 ,  SD_TYPE_BED,     -1.5, -1.1,          0.5,     180.0,      1.0,    2,  0.85,        -0.5},
    /*56*/{2301 ,  SD_TYPE_BED,     -2.5, -0.1,          0.5,     180.0,      1.0,    2,  0.85,        -1.0},
    /////////////////////////////////////////////
    /////////////////////////////////////////////
    /*57*/{1764  ,  SD_TYPE_SOFA,      0.55, -0.3,       0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*58*/{1707  ,  SD_TYPE_SOFA,      0.55, -0.4,         0.5,     180.0,      1.0,    2,  0.75,        -1.0},
    /*59*/{1763  ,  SD_TYPE_SOFA,      0.45, -0.3,         0.5,     180.0,      1.0,    2,  0.75,        -1.0},
    /*60*/{1712  ,  SD_TYPE_SOFA,      0.6, -0.05,         0.5,     180.0,      1.0,    3,  0.7,        -1.0},
    /*61*/{1702  ,  SD_TYPE_SOFA,      0.55, -0.65,         0.5,     180.0,      1.0,    2,  0.75,        -1.0},
    /*62*/{1706  ,  SD_TYPE_SOFA,      0.6, 0.0,         0.5,     180.0,      1.0,    2,  1.0,        -1.0},
    /*63*/{1768  ,  SD_TYPE_SOFA,      0.6, -0.3,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*64*/{1766  ,  SD_TYPE_SOFA,      0.6, -0.3,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*65*/{1757  ,  SD_TYPE_SOFA,       0.55, -0.3,         0.5,     180.0,      1.0,    3,   0.75,        -1.0},
    /*66*/{1713  ,  SD_TYPE_SOFA,       0.6, -0.2,         0.5,     180.0,      1.0,    3,   0.75,        -1.0},
    /*67*/{1703  ,  SD_TYPE_SOFA,      0.6, -0.5,         0.5,     180.0,      1.0,    2,  1.0,        -1.0},
    /*68*/{1761  ,  SD_TYPE_SOFA,      0.55, -0.3,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*69*/{1760  ,  SD_TYPE_SOFA,      0.6, -0.3,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*70*/{1756  ,  SD_TYPE_SOFA,      0.6, -0.2,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*71*/{1753  ,  SD_TYPE_SOFA,      0.6, -0.3,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*72*/{2290  ,  SD_TYPE_SOFA,      0.6, -0.3,         0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*73*/{1723 ,  SD_TYPE_SOFA,       0.7, -0.3,          0.5,     180.0,      1.0,    3,  0.75,        -1.0},
    /*74*/{1710  ,  SD_TYPE_SOFA,      0.65, -0.3,         0.5,     180.0,      1.0,    5,  0.75,        -1.0},
    /*75*/{11717 ,  SD_TYPE_SOFA,      0.6, 0.3,         0.5,     180.0,      1.0,    2,  0.75,        -1.0}
    //
    /*76*///{11689 ,  SD_TYPE_RADIUS,      0.6, 0.0,         0.5,     180.0,      1.0,    4,  0.0,        -1.0}//сложный объект
};

enum e_SitDown_Data
{
    sd_ID, // server ID
    Text3D:sd_Label[MAX_SITDOWN_PLACES],
    sd_ObjectZone[MAX_SITDOWN_PLACES], // зона конкретного объекта мебели
    sd_Type, // тип мебели
    sd_Places, // количество мест конкретного объекта мебели
    sd_Status[MAX_SITDOWN_PLACES],

    Float:f_X[MAX_SITDOWN_PLACES],
    Float:f_Y[MAX_SITDOWN_PLACES],
    Float:f_Z[MAX_SITDOWN_PLACES],

    Float:f_RZ
}
new SitDown_Data[MAX_SITDOWN][e_SitDown_Data],
    totalsitdown;

new Float:SitDown_Areas[][3] =
{
    {1030.1195,1868.2897,1515.8578},
    {2616.5723,2112.9021,1048.2277,},
    {2595.1536,2273.1731,1050.5717},
    {707.9974,-1302.4293,1102.0035},
    {-1322.5077,1772.9557,1075.0792},
    {202.9419,-1690.0531,1007.4592},
    {1212.6555,2063.6177,1009.4866},
    {-2107.9995,-114.7223,1055.1475},
    {-302.5667,1452.0350,2059.8870},
    {2237.8608,681.0781,1017.9205},
    {1257.1434,1978.5011,1024.4484},
    {693.7870,1725.1226,1024.2701}
};

stock sitdown_CreateDynamicObject(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1, interiorid = -1, playerid = -1, Float:streamdistance = STREAMER_OBJECT_SD, Float:drawdistance = STREAMER_OBJECT_DD, STREAMER_TAG_AREA:areaid = STREAMER_TAG_AREA:-1, priority = 0)
{
    new ok_return = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, interiorid, playerid, streamdistance, drawdistance, areaid, priority);

    if(totalsitdown < MAX_SITDOWN)
    {
        for(new i = sizeof(SitDown_Init)-1; i != -1; i--)
        {
            if(modelid == SitDown_Init[i][sd_ModelID])
            {
                for(new j = sizeof(SitDown_Areas)-1; j != -1; j--)
                {
                    if(VectorSize(x-SitDown_Areas[j][0], y-SitDown_Areas[j][1], z-SitDown_Areas[j][2]) < 150.0)
                    {
                        SitDown_Add(ok_return, i, worldid, interiorid);
                        break;
                    }
                }
                break;
            }
        }
    }
    return ok_return;
}

#if defined _ALS_CreateDynamicObject
        #undef CreateDynamicObject
#else
        #define _ALS_CreateDynamicObject
#endif
#define CreateDynamicObject sitdown_CreateDynamicObject

stock sitdown_DestroyDynamicObject(objectid)
{
    new modelid = GetDynamicObjectModelID(objectid),
        ok_return = DestroyDynamicObject(objectid);
    for(new i = sizeof(SitDown_Init)-1; i != -1; i--)
    {
        if(modelid == SitDown_Init[i][sd_ModelID])
        {
            SitDown_Remove(i);
            break;
        }
    }
    return ok_return;
}

#if defined _ALS_DestroyDynamicObject
        #undef DestroyDynamicObject
#else
        #define _ALS_DestroyDynamicObject
#endif
#define DestroyDynamicObject sitdown_DestroyDynamicObject

SitDown_Add(objectid, id, worldid, interiorid)
{
    SitDown_Data[totalsitdown][sd_ID] = id;

    new count_place = SitDown_Init[id][sd_Places];

    SitDown_Data[totalsitdown][sd_Places] = count_place;
    SitDown_Data[totalsitdown][sd_Type] = SitDown_Init[id][sd_Type];

    new Float:_null;
    GetDynamicObjectRot(objectid, _null, _null, SitDown_Data[totalsitdown][f_RZ]);
    new Float:bias_X, Float:bias_Y;
    for(new i = 0; i < count_place; i++)
    {
        GetDynamicObjectPos(objectid, SitDown_Data[totalsitdown][f_X][i],SitDown_Data[totalsitdown][f_Y][i],SitDown_Data[totalsitdown][f_Z][i]);

        SitDown_Data[totalsitdown][sd_Status][i] = INVALID_PLAYER_ID;

        if(i == 0)
        {
            new Float:angle = -(SitDown_Data[totalsitdown][f_RZ]+SitDown_Init[id][sd_SitDown_RZ]);
            bias_X = bias_X + floatsin(angle,degrees) * SitDown_Init[id][sd_SitDown_Bias_UD] +
            floatcos(angle,degrees) * SitDown_Init[id][sd_SitDown_Bias_LR];

            bias_Y = bias_Y + floatcos(angle,degrees) * SitDown_Init[id][sd_SitDown_Bias_UD] -
            floatsin(angle,degrees) * SitDown_Init[id][sd_SitDown_Bias_LR];
        }
        else
        {
            new Float:angle = -(SitDown_Data[totalsitdown][f_RZ]+SitDown_Init[id][sd_SitDown_RZ]);
            bias_X = bias_X + floatsin(angle,degrees) * 0.0 +
            floatcos(angle,degrees) * (-SitDown_Init[id][sd_Seats_Distance]);

            bias_Y = bias_Y + floatcos(angle,degrees) * 0.0 -
            floatsin(angle,degrees) * (-SitDown_Init[id][sd_Seats_Distance]);
        }
        SitDown_Data[totalsitdown][f_X][i] += bias_X;
        SitDown_Data[totalsitdown][f_Y][i] += bias_Y;

        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "Чтобы %s\nНажмите 'ALT'", SitDown_Name[SitDown_Data[totalsitdown][sd_Type]]);
        SitDown_Data[totalsitdown][sd_Label][i] = CreateDynamic3DTextLabel(STRING_GLOBAL, -1,
            SitDown_Data[totalsitdown][f_X][i],
            SitDown_Data[totalsitdown][f_Y][i],
            SitDown_Data[totalsitdown][f_Z][i] + 1.0, 3.0, INVALID_PLAYER_ID,INVALID_PLAYER_ID, 0, worldid, interiorid);

        SitDown_Data[totalsitdown][sd_ObjectZone][i] = CreateDynamicSphere(
            SitDown_Data[totalsitdown][f_X][i],
            SitDown_Data[totalsitdown][f_Y][i],
            SitDown_Data[totalsitdown][f_Z][i] + 1.0, SitDown_Init[id][sd_Radius], worldid, interiorid);

        UpdateAreaInfo(SitDown_Data[totalsitdown][sd_ObjectZone][i], TYPE_SITDOWN, AREA_SUBTYPE_INVALID_ID, totalsitdown, i);
    }
    totalsitdown++;
}

SitDown_Remove(id)
{
    new init_id = INVALID_OBJECT_ID;
    for(new i = totalsitdown; i != -1; i--)
    {
        if(id == SitDown_Data[i][sd_ID])
        {
            init_id = i;
            break;
        }
    }
    if(init_id == INVALID_OBJECT_ID) return 1;

    for(new i = SitDown_Data[init_id][sd_Places]-1; i != -1; i--)
    {
        SitDown_Data[init_id][f_X][i] =
        SitDown_Data[init_id][f_Y][i] =
        SitDown_Data[init_id][f_Z][i] = 0.0;

        SitDown_Data[init_id][sd_Status][i] = INVALID_PLAYER_ID;

        DestroyDynamic3DTextLabel(SitDown_Data[init_id][sd_Label][i]);
        DestroyDynamicArea(SitDown_Data[init_id][sd_ObjectZone][i]);
        SitDown_Data[init_id][sd_ObjectZone][i] = -1;
    }

    SitDown_Data[init_id][f_RZ]= 0.0;

    SitDown_Data[init_id][sd_ID] =
    SitDown_Data[init_id][sd_Type] =
    SitDown_Data[init_id][sd_Places] = 0;
    return 1;
}

SitDown_UpdatePlace(playerid)
{
    new id = p_temp[playerid][sitdown_id],
        place_id = p_temp[playerid][sitdown_place];
    if(place_id == -1 || id == -1)
        return 1;
    if(SitDown_Data[id][sd_Status][place_id] != INVALID_PLAYER_ID &&
        SitDown_Data[id][sd_Status][place_id] != playerid)
        return SendError(playerid, "Место занято %s.", get_name(SitDown_Data[id][sd_Status][place_id]));
    STRING_GLOBAL[0] = EOS;
    if(SitDown_Data[id][sd_Status][place_id] == INVALID_PLAYER_ID)
    {
        format(STRING_GLOBAL,sizeof STRING_GLOBAL, "Место занято\n%s", get_name(playerid));
        SitDown_Data[id][sd_Status][place_id] = playerid;
        UpdateDynamic3DTextLabelText(SitDown_Data[id][sd_Label][place_id], -1, STRING_GLOBAL);

        new init_id = SitDown_Data[id][sd_ID],
            Float:sd_angle = SitDown_Data[id][f_RZ]+SitDown_Init[init_id][sd_SitDown_RZ];

        SetPlayerPos(playerid,
            SitDown_Data[id][f_X][place_id],
            SitDown_Data[id][f_Y][place_id],
            SitDown_Data[id][f_Z][place_id] + SitDown_Init[init_id][sd_SitDown_Bias_Z]);
        SetPlayerFacingAngle(playerid, sd_angle);

        Fix_TogglePlayerControllable(playerid, false);

        if(SitDown_Init[init_id][sd_Type] == SD_TYPE_BED)
            LoopingAnim(playerid,"BEACH","BATHER", 4.0,0,0,1,1,0);
        else
            LoopingAnim(playerid,"PED","SEAT_down", 4.0,0,0,1,1,0);

        /*
            //Важная подсистема!:
            z+SitDown_Init[i][sd_Fix_Z] ---> это фикс Z позиции.
            Использование:
            //Если Позиция игрока минус фикс позиция Z объекта не равна текущей позиции объекта, то
            if((Z_Player_POS-SitDown_Init[i][sd_Fix_Z]) != SitDown_Data[id][f_Z][place_id])//Можно сделать n-й разброс например от -0.2 до 0.2
            {
                SitDown_Data[id][f_Z][place_id] = Z_Player_POS - Z_Player_POS-SitDown_Init[i][sd_Fix_Z];
                //затем перемещаешь объект
                //Примерно так.
                //Все условия уже сам юзаешь, как это будет работать.
            }
        */
    }
    else SitDown_Clear(playerid, id, place_id);
    return 1;
}

SitDown_Clear(playerid, id, place_id)
{
    if(id == -1 || place_id == -1) return 1;
    if(SitDown_Data[id][sd_Status][place_id] == playerid)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "Чтобы %s\nНажмите 'ALT'", SitDown_Name[SitDown_Data[id][sd_Type]]);
        SitDown_Data[id][sd_Status][place_id] = INVALID_PLAYER_ID;
        UpdateDynamic3DTextLabelText(SitDown_Data[id][sd_Label][place_id], -1, STRING_GLOBAL);

        ClearAnimations(playerid, 1);
        Fix_TogglePlayerControllable(playerid, true);
    }
    p_temp[playerid][sitdown_id] =
    p_temp[playerid][sitdown_place] = -1;
    return 1;
}

/*
cmd:asd(playerid, params[])
{
    if(SRV_ID) return 1;
    if(sscanf(params, "d", params[0])) return SendInfo(playerid, "Используйте: /asd ID");
    if(!(1 <= params[0] <= 9)) return SendInfo(playerid, "Используйте: /asd ID");
    switch(params[0])
    {
        case 1: LoopingAnim(playerid,"PED","SEAT_down", 4.0,0,0,1,1,0);
        case 2: LoopingAnim(playerid,"MISC","seat_lr",2.0,1,0,0,0,0);
        case 3: LoopingAnim(playerid,"MISC","seat_talk_01",2.0,1,0,0,0,0);
        case 4: LoopingAnim(playerid,"MISC","seat_talk_02",2.0,1,0,0,0,0);
        case 5: LoopingAnim(playerid,"BLOWJOBZ","BJ_Couch_Loop_P",4.0,1,0,1,1,0);
        case 6: LoopingAnim(playerid,"INT_OFFICE","OFF_Sit_Idle_Loop",4.0,1,0,1,1,0);
        case 7: LoopingAnim(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.0,1,0,1,1,0);
        case 8: LoopingAnim(playerid,"INT_OFFICE","OFF_Sit_Drink",4.0,1,0,1,1,0);
        case 9: LoopingAnim(playerid,"INT_OFFICE","OFF_Sit_Watch",4.0,0,0,1,1,0);
    }
    return 1;
}
*/
CMD:sdtest(playerid,params[])
{
    if(SRV_ID) return 1;
    new Float:x,Float:y,Float:z, Float:r;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, r);
    new Float:con = 8.0;
    for(new i = 0; i < sizeof SitDown_Init; i++)
    {
        CreateDynamicObject(SitDown_Init[i][sd_ModelID], x+(i*(floatsin(-r, degrees)*con)), y+(i*(floatcos(-r, degrees)*con)), z+SitDown_Init[i][sd_Fix_Z], 0.0, 0.0, random(360));
    }
    Streamer_Update(playerid);
    return 1;
}
