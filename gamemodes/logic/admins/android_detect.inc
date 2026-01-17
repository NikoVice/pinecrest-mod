//Android-detection by Nexius

#if defined _adetect_included
	#endinput
#endif
#define _adetect_included

#include <a_samp>

static
	LastUpDown[MAX_PLAYERS],
	LastLeftRight[MAX_PLAYERS],
	bool:DefinitelyJoypad[MAX_PLAYERS char],
	NoJoypadWarnings[MAX_PLAYERS];

public OnPlayerSpawn(playerid)
{
	LastUpDown[playerid] = 0;
	LastLeftRight[playerid] = 0;
	DefinitelyJoypad{playerid} = false;
	NoJoypadWarnings[playerid] = 0;
	#if defined adetect_OnPlayerSpawn
		return adetect_OnPlayerSpawn(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn adetect_OnPlayerSpawn
#if defined adetect_OnPlayerSpawn
	forward adetect_OnPlayerSpawn(playerid);
#endif

public OnPlayerUpdate(playerid)
{
	if(!DefinitelyJoypad{playerid} && IsPlayerMobile(playerid)) //Детекта джойстика/стиков ещё не было и игрок вроде бы с телефона
	{
		new keys, ud, lr;
		GetPlayerKeys(playerid, keys, ud, lr);
		if(LastUpDown[playerid] != ud || LastLeftRight[playerid] != lr) //Это важная проверка, она нужна как раз для избежания ложных с простоем на месте
		{
			if(ud != 128 && ud != 0 && ud != -128 || lr != 128 && lr != 0 && lr != -128) //Это джойпад/андроид стики
			{
				DefinitelyJoypad{playerid} = true; //Забываем его для всех последующих проверок
			}
			else if(++NoJoypadWarnings[playerid] >= 3) //Три и более раза нажал на стрелки с поведением ПК клавиатуры
			{
				ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_MSGBOX, ""I"Античит", ""W"Вы пытаетесь зайти с персонального компьютера под видом телефона,\n\если срабатывание ложное, рекомендуем Вам перезайти.", "ОК", "");
				Kick(playerid);
			}
		}
		LastUpDown[playerid] = ud;
		LastLeftRight[playerid] = lr;
	}
	#if defined adetect_OnPlayerUpdate
		return adetect_OnPlayerUpdate(playerid);
	#else
		return 1;
	#endif
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif
#define OnPlayerUpdate adetect_OnPlayerUpdate
#if defined adetect_OnPlayerUpdate
	forward adetect_OnPlayerUpdate(playerid);
#endif
