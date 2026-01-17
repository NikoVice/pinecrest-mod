enum
{
    PICKUP_SUBTYPE_INVALID_ID,
    PICKUP_SUBTYPE_HOUSE_ENTER,
    PICKUP_SUBTYPE_HOUSE_EXIT,
    PICKUP_SUBTYPE_HOUSE_G_DOOR,
    PICKUP_SUBTYPE_HOUSE_B_DOOR,
    PICKUP_SUBTYPE_HOUSE_U_DOOR,
    PICKUP_SUBTYPE_HOUSE_BASEMENT,
    PICKUP_SUBTYPE_HOUSE_VC_ALL,
    PICKUP_SUBTYPE_HOUSE_VC_ONE,
    PICKUP_SUBTYPE_HOUSE_VC_TWO,
    PICKUP_SUBTYPE_HOUSE_VC_THREE,
    PICKUP_SUBTYPE_HOUSE_VC_FOUR,
    PICKUP_SUBTYPE_HOUSE_VC_FIVE,
    PICKUP_SUBTYPE_HOUSE_U_ALL,
    PICKUP_SUBTYPE_HOUSE_U_ONE,
    PICKUP_SUBTYPE_HOUSE_U_TWO,
    PICKUP_SUBTYPE_HOUSE_U_THREE,
    PICKUP_SUBTYPE_HOUSE_U_FOUR,
    PICKUP_SUBTYPE_HOUSE_U_FIVE,
    PICKUP_SUBTYPE_HOUSE_U_SIX,
    PICKUP_SUBTYPE_HOUSE_U_SEVEN,
    PICKUP_SUBTYPE_HOUSE_U_EIGHT,
    PICKUP_SUBTYPE_HOUSE_U_NINE,
    PICKUP_SUBTYPE_HOUSE_U_TEN, // WARNING: ¬€ÿ≈ Õ≈ “–Œ√¿“‹!!!
    PICKUP_SUBTYPE_BUSINESS_ENTER,
    PICKUP_SUBTYPE_BUSINESS_EXIT,
    PICKUP_SUBTYPE_BUSINESS_HOTEL,
    PICKUP_SUBTYPE_BUSINESS_ROOM,
    PICKUP_SUBTYPE_BANK_ENTER,
    PICKUP_SUBTYPE_BANK_EXIT,
    PICKUP_SUBTYPE_BANK_MENU,
    PICKUP_SUBTYPE_COS_ROB_A,
    PICKUP_SUBTYPE_COS_ROB_H
}

enum e_PICKUP_INFO
{
    pickup_type,
    pickup_subtype,
    pickup_object_id
}
new gPickupInfo[MAX_SERVER_PICKUPS][e_PICKUP_INFO];

stock area_DestroyDynamicPickup(pickupid)
{
    new
        ok_return = DestroyDynamicPickup(pickupid);
    gPickupInfo[pickupid][pickup_type] = PICKUP_SUBTYPE_INVALID_ID;
    gPickupInfo[pickupid][pickup_subtype] = PICKUP_SUBTYPE_INVALID_ID;
    gPickupInfo[pickupid][pickup_object_id] = PICKUP_SUBTYPE_INVALID_ID;
    return ok_return;
}

#if defined _ALS_DestroyDynamicPickup
    #undef DestroyDynamicPickup
#else
    #define _ALS_DestroyDynamicPickup
#endif
#define DestroyDynamicPickup area_DestroyDynamicPickup
