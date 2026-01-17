/*

	About: Supports SAMP 0.3.7 sync custom models v2.3
	Author: Noname

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before m_custom-sync"
#endif

#if !defined PAWNRAKNET_INC_
	#error "You must have Pawn.RakNet include in order to use this one."
#endif

#if defined _custom_sync_included_
	#endinput
#endif
#define _custom_sync_included_

/*
	Define const
*/
/*
#if !defined M_LAUNCHER_VERSION
	#error Please define launcher version to check. Example: #define M_LAUNCHER_VERSION "Launcher version"
#endif
*/
#if !defined SAMP_VERSION_037
	#define SAMP_VERSION_037 4057
#endif

#if !defined MAX_CUSTOM_VEHICLES
	#define MAX_CUSTOM_VEHICLES 20000
#endif

#if !defined MAX_CUSTOM_PEDS
	#define MAX_CUSTOM_PEDS 20000
#endif

#define M_CUSTOM_CustomForVehicles 1
#define M_CUSTOM_CustomForPeds 0
/*
#if !defined M_CUSTOM_CustomForPeds
	#define M_CUSTOM_CustomForPeds 1
#else
	#undef M_CUSTOM_CustomForPeds
	#define M_CUSTOM_CustomForPeds 0
#endif

#if !defined M_CUSTOM_CustomForVehicles
	#define M_CUSTOM_CustomForVehicles 1
#else
	#undef M_CUSTOM_CustomForVehicles
	#define M_CUSTOM_CustomForVehicles 0
#endif
*/
/*
	Consts
*/

const RPC_ClientJoin = 25;
#if M_CUSTOM_CustomForPeds
const RPC_WorldPlayerAdd = 32;
const RPC_SetSpawnInfo = 68;
const RPC_RequestClass = 128;
const RPC_SetPlayerSkin = 153;
const RPC_ShowActor = 171;
#endif
#if M_CUSTOM_CustomForVehicles
const RPC_WorldVehicleAdd = 164;
#endif

/*
	Vars
*/
/*
static
	bool:c_player_launcher[MAX_PLAYERS char];
*/
#if M_CUSTOM_CustomForPeds
static
	c_ped_models[MAX_CUSTOM_PEDS] = {-1, ...};
#endif

#if M_CUSTOM_CustomForVehicles
new
	c_vehicle_models[MAX_VEHICLES] = {-1, ...};
#endif

#if M_CUSTOM_CustomForPeds

/*
	AddPedSyncModel
*/

stock AddPedSyncModel(baseid, newid)
{
	if (!(312 <= newid <= MAX_CUSTOM_PEDS)) {
		return 0;
	}
	c_ped_models[newid] = baseid;
	return 1;
}

/*
	GetPedSyncModel
*/

stock GetPedSyncModel(modelid)
{
	if (!(312 <= modelid <= MAX_CUSTOM_PEDS)) {
		return modelid;
	}
	return c_ped_models[modelid];
}
#endif

#if M_CUSTOM_CustomForVehicles

/*
	AddVehicleSyncModel
*/

stock AddVehicleSyncModel(baseid, newid)
{
	if (!(612 <= newid <= MAX_CUSTOM_VEHICLES)) {
		return 0;
	}
	c_vehicle_models[newid] = baseid;
	return 1;
}

/*
	GetVehicleSyncModel
*/

stock GetVehicleSyncModel(modelid)
{
	if (!(612 <= modelid <= MAX_CUSTOM_VEHICLES)) {
		return modelid;
	}
	return c_vehicle_models[modelid];
}
#endif

/*
	IsPlayerLauncher
*/
/*
stock IsPlayerLauncher(playerid)
{
	return _:c_player_launcher{playerid};
}
*/
/*
	OnIncomingRPC
*/
/*
public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
	switch (rpcid) {
		case RPC_ClientJoin: {

			new
				iVersion,
				byteMod,
				byteNicknameLen,
				NickName[MAX_PLAYER_NAME + 1],
				uiClientChallengeResponse,
				byteAuthKeyLen,
				AuthKey[16 * 4],
				iClientVerLen,
				ClientVersion[12 + 1];

			BS_ReadValue(
				bs,
				PR_INT32, iVersion,
				PR_UINT8, byteMod,
				PR_UINT8, byteNicknameLen,
				PR_STRING, NickName, byteNicknameLen,
				PR_UINT32, uiClientChallengeResponse,
				PR_UINT8, byteAuthKeyLen,
				PR_STRING, AuthKey, byteAuthKeyLen,
				PR_UINT8, iClientVerLen,
				PR_STRING, ClientVersion, iClientVerLen
			);

			if (iVersion == SAMP_VERSION_037
				&& strcmp(ClientVersion, M_LAUNCHER_VERSION, false) == 0)
				c_player_launcher{playerid} = true;
			else
				c_player_launcher{playerid} = false;

			BS_ResetReadPointer(bs);
		}
	}

	#if defined m_custom_sync_OnIncomingRPC
		return m_custom_sync_OnIncomingRPC(playerid, rpcid, bs);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnIncomingRPC
	#undef OnIncomingRPC
#else
	#define _ALS_OnIncomingRPC
#endif
#define OnIncomingRPC m_custom_sync_OnIncomingRPC
#if defined m_custom_sync_OnIncomingRPC
	forward m_custom_sync_OnIncomingRPC(playerid, rpcid, BitStream:bs);
#endif
*/
/*
	OnOutcomingRPC
*/

#if M_CUSTOM_CustomForPeds || M_CUSTOM_CustomForVehicles
	public OnOutcomingRPC(playerid, rpcid, BitStream:bs)
	{
		if (playerid != -1 && IsPlayerMobile(playerid)) {
			switch (rpcid) {
			#if M_CUSTOM_CustomForPeds
				case RPC_SetPlayerSkin: {

					new
						wPlayerID,
						dSkinID;

					BS_ReadValue(
						bs,
						PR_UINT32, wPlayerID,
						PR_UINT32, dSkinID
					);

					BS_ResetReadPointer(bs);

					new
						BitStream:bsn = BS_New();

					BS_WriteValue(
						bsn,
						PR_UINT32, wPlayerID,
						PR_UINT32, (c_ped_models[dSkinID] != -1) ? (c_ped_models[dSkinID]) : (dSkinID)
					);

					PR_SendRPC(bsn, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);

					BS_ResetWritePointer(bsn);

					BS_Delete(bsn);
					return 0;
				}
				case RPC_WorldPlayerAdd: {

					new
						wPlayerID,
						team,
						dSkinID,
						Float:PosX,
						Float:PosY,
						Float:PosZ,
						Float:facing_angle,
						player_color,
						fighting_style;

					BS_ReadValue(
						bs,
						PR_UINT16, wPlayerID,
						PR_UINT8, team,
						PR_UINT32, dSkinID,
						PR_FLOAT, PosX,
						PR_FLOAT, PosY,
						PR_FLOAT, PosZ,
						PR_FLOAT, facing_angle,
						PR_UINT32, player_color,
						PR_UINT8, fighting_style
					);

					BS_ResetReadPointer(bs);

					new
						BitStream:bsn = BS_New();

					BS_WriteValue(
						bsn,
						PR_UINT16, wPlayerID,
						PR_UINT8, team,
						PR_UINT32, (c_ped_models[dSkinID] != -1) ? (c_ped_models[dSkinID]) : (dSkinID),
						PR_FLOAT, PosX,
						PR_FLOAT, PosY,
						PR_FLOAT, PosZ,
						PR_FLOAT, facing_angle,
						PR_UINT32, player_color,
						PR_UINT8, fighting_style
					);

					PR_SendRPC(bsn, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);

					BS_ResetWritePointer(bsn);

					BS_Delete(bsn);
					return 0;
				}
				case RPC_SetSpawnInfo: {

					new
						byteTeam,
						iSkin,
						unk,
						Float:X,
						Float:Y,
						Float:Z,
						Float:fRotation,
						iSpawnWeapons0,
						iSpawnWeapons1,
						iSpawnWeapons2,
						iSpawnWeaponsAmmo0,
						iSpawnWeaponsAmmo1,
						iSpawnWeaponsAmmo2;

					BS_ReadValue(
						bs,
						PR_UINT8, byteTeam,
						PR_INT32, iSkin,
						PR_UINT8, unk,
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, fRotation,
						PR_INT32, iSpawnWeapons0,
						PR_INT32, iSpawnWeapons1,
						PR_INT32, iSpawnWeapons2,
						PR_INT32, iSpawnWeaponsAmmo0,
						PR_INT32, iSpawnWeaponsAmmo1,
						PR_INT32, iSpawnWeaponsAmmo2
					);

					BS_ResetReadPointer(bs);

					new
						BitStream:bsn = BS_New();

					BS_WriteValue(
						bsn,
						PR_UINT8, byteTeam,
						PR_INT32, (c_ped_models[iSkin] != -1) ? (c_ped_models[iSkin]) : (iSkin),
						PR_UINT8, unk,
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, fRotation,
						PR_INT32, iSpawnWeapons0,
						PR_INT32, iSpawnWeapons1,
						PR_INT32, iSpawnWeapons2,
						PR_INT32, iSpawnWeaponsAmmo0,
						PR_INT32, iSpawnWeaponsAmmo1,
						PR_INT32, iSpawnWeaponsAmmo2
					);

					PR_SendRPC(bsn, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);

					BS_ResetWritePointer(bsn);

					BS_Delete(bsn);
					return 0;
				}
				case RPC_RequestClass: {

					new
						byteRequestOutcome,
						byteTeam,
						iSkin,
						unk,
						Float:X,
						Float:Y,
						Float:Z,
						Float:fRotation,
						iSpawnWeapons0,
						iSpawnWeapons1,
						iSpawnWeapons2,
						iSpawnWeaponsAmmo0,
						iSpawnWeaponsAmmo1,
						iSpawnWeaponsAmmo2;

					BS_ReadValue(
						bs,
						PR_UINT8, byteRequestOutcome,
						PR_UINT8, byteTeam,
						PR_INT32, iSkin,
						PR_UINT8, unk,
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, fRotation,
						PR_INT32, iSpawnWeapons0,
						PR_INT32, iSpawnWeapons1,
						PR_INT32, iSpawnWeapons2,
						PR_INT32, iSpawnWeaponsAmmo0,
						PR_INT32, iSpawnWeaponsAmmo1,
						PR_INT32, iSpawnWeaponsAmmo2
					);

					BS_ResetReadPointer(bs);

					new
						BitStream:bsn = BS_New();

					BS_WriteValue(
						bsn,
						PR_UINT8, byteRequestOutcome,
						PR_UINT8, byteTeam,
						PR_INT32, (c_ped_models[iSkin] != -1) ? (c_ped_models[iSkin]) : (iSkin),
						PR_UINT8, unk,
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, fRotation,
						PR_INT32, iSpawnWeapons0,
						PR_INT32, iSpawnWeapons1,
						PR_INT32, iSpawnWeapons2,
						PR_INT32, iSpawnWeaponsAmmo0,
						PR_INT32, iSpawnWeaponsAmmo1,
						PR_INT32, iSpawnWeaponsAmmo2
					);

					PR_SendRPC(bsn, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);

					BS_ResetWritePointer(bsn);

					BS_Delete(bsn);
					return 0;
				}
				case RPC_ShowActor: {

					new
						wActorID,
						SkinID,
						Float:X,
						Float:Y,
						Float:Z,
						Float:Angle,
						Float:Health,
						Invulnerable;

					BS_ReadValue(
						bs,
						PR_UINT16, wActorID,
						PR_UINT32, SkinID,
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, Angle,
						PR_FLOAT, Health,
						PR_BOOL, Invulnerable
					);

					BS_ResetReadPointer(bs);

					new
						BitStream:bsn = BS_New();

					BS_WriteValue(
						bsn,
						PR_UINT16, wActorID,
						PR_UINT32, (c_ped_models[SkinID] != -1) ? (c_ped_models[SkinID]) : (SkinID),
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, Angle,
						PR_FLOAT, Health,
						PR_BOOL, Invulnerable
					);

					PR_SendRPC(bsn, playerid, rpcid, PR_LOW_PRIORITY, PR_RELIABLE_ORDERED);

					BS_ResetWritePointer(bsn);

					BS_Delete(bsn);
					return 0;
				}
			#endif
			#if M_CUSTOM_CustomForVehicles
				case RPC_WorldVehicleAdd: {

					new
						wVehicleID,
						ModelID,
						Float:X,
						Float:Y,
						Float:Z,
						Float:Angle,
						InteriorColor1,
						InteriorColor2,
						Float:Health,
						Interior,
						DoorDamageStatus,
						PanelDamageStatus,
						LightDamageStatus,
						tireDamageStatus,
						addsiren,
						modslot0,
						modslot1,
						modslot2,
						modslot3,
						modslot4,
						modslot5,
						modslot6,
						modslot7,
						modslot8,
						modslot9,
						modslot10,
						modslot11,
						modslot12,
						modslot13,
						PaintJob,
						BodyColor1,
						BodyColor2;

					BS_ReadValue(
						bs,
						PR_INT16, wVehicleID,
						PR_INT32, ModelID,
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, Angle,
						PR_INT8, InteriorColor1,
						PR_INT8, InteriorColor2,
						PR_FLOAT, Health,
						PR_INT8, Interior,
						PR_INT32, DoorDamageStatus,
						PR_INT32, PanelDamageStatus,
						PR_INT8, LightDamageStatus,
						PR_INT8, tireDamageStatus,
						PR_INT8, addsiren,
						PR_INT8, modslot0,
						PR_INT8, modslot1,
						PR_INT8, modslot2,
						PR_INT8, modslot3,
						PR_INT8, modslot4,
						PR_INT8, modslot5,
						PR_INT8, modslot6,
						PR_INT8, modslot7,
						PR_INT8, modslot8,
						PR_INT8, modslot9,
						PR_INT8, modslot10,
						PR_INT8, modslot11,
						PR_INT8, modslot12,
						PR_INT8, modslot13,
						PR_INT8, PaintJob,
						PR_INT32, BodyColor1,
						PR_INT32, BodyColor2
					);

					BS_ResetReadPointer(bs);

					new
						BitStream:bsn = BS_New();

					BS_WriteValue(
						bsn,
						PR_INT16, wVehicleID,
						PR_INT32, (c_vehicle_models[ModelID] != -1) ? (c_vehicle_models[ModelID]) : (ModelID),
						PR_FLOAT, X,
						PR_FLOAT, Y,
						PR_FLOAT, Z,
						PR_FLOAT, Angle,
						PR_INT8, InteriorColor1,
						PR_INT8, InteriorColor2,
						PR_FLOAT, Health,
						PR_INT8, interior,
						PR_INT32, DoorDamageStatus,
						PR_INT32, PanelDamageStatus,
						PR_INT8, LightDamageStatus,
						PR_INT8, tireDamageStatus,
						PR_INT8, addsiren,
						PR_INT8, modslot0,
						PR_INT8, modslot1,
						PR_INT8, modslot2,
						PR_INT8, modslot3,
						PR_INT8, modslot4,
						PR_INT8, modslot5,
						PR_INT8, modslot6,
						PR_INT8, modslot7,
						PR_INT8, modslot8,
						PR_INT8, modslot9,
						PR_INT8, modslot10,
						PR_INT8, modslot11,
						PR_INT8, modslot12,
						PR_INT8, modslot13,
						PR_INT8, PaintJob,
						PR_INT32, BodyColor1,
						PR_INT32, BodyColor2
					);

					PR_SendRPC(bsn, playerid, rpcid, PR_HIGH_PRIORITY, PR_RELIABLE_ORDERED);

					BS_ResetWritePointer(bsn);

					BS_Delete(bsn);
					return 0;
				}
			#endif
			}
		}

		#if defined m_custom_sync_OnOutcomingRPC
			return m_custom_sync_OnOutcomingRPC(playerid, rpcid, bs);
		#else
			return 1;
		#endif
	}

	#if defined _ALS_OnOutcomingRPC
		#undef OnOutcomingRPC
	#else
		#define _ALS_OnOutcomingRPC
	#endif
	#define OnOutcomingRPC m_custom_sync_OnOutcomingRPC
	#if defined m_custom_sync_OnOutcomingRPC
		forward m_custom_sync_OnOutcomingRPC(playerid, rpcid, BitStream:bs);
	#endif
#endif
