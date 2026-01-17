
// The max number of entries in the damage feeds
#define WC_FEED_HEIGHT 5
#define WC_FEED_GIVEN_COLOR 0x30FF50FF // light green
#define WC_FEED_TAKEN_COLOR 0xff3636FF // light red

static PlayerText:s_DamageFeedTaken[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};
static PlayerText:s_DamageFeedGiven[MAX_PLAYERS] = {PlayerText:INVALID_TEXT_DRAW, ...};

// Hits displayed in the damage feeds
enum E_DAMAGE_FEED_HIT {
	      e_Issuer,
	      e_Name[MAX_PLAYER_NAME],
	Float:e_Amount,
	      e_Weapon,
	      e_Tick
}
static s_DamageFeedHitsGiven[MAX_PLAYERS][WC_FEED_HEIGHT][E_DAMAGE_FEED_HIT];
static s_DamageFeedHitsTaken[MAX_PLAYERS][WC_FEED_HEIGHT][E_DAMAGE_FEED_HIT];

static s_DamageFeedTimer[MAX_PLAYERS] = {-1, ...};
static s_DamageFeedLastUpdate[MAX_PLAYERS];
static s_DamageFeed = true;
static s_DamageFeedHideDelay = 3000;
static s_DamageFeedMaxUpdateRate = 250;

static s_DamageTakenSound = 1190;
static s_DamageGivenSound = 17802;

//weaponshot
DamageInformer(playerid, damagerid, Float:amount, weapon)
{
	if(damagerid != INVALID_PLAYER_ID) 
	{
		DamageFeedAddHitGiven(damagerid, playerid, amount, weapon);
		PlayerPlaySound(damagerid, s_DamageGivenSound, 0.0, 0.0, 0.0);
	}
	DamageFeedAddHitTaken(playerid, damagerid, amount, weapon);
	PlayerPlaySound(playerid, s_DamageTakenSound, 0.0, 0.0, 0.0);
}

forward WC_DamageFeedUpdate(playerid);
public WC_DamageFeedUpdate(playerid)
{
	s_DamageFeedTimer[playerid] = -1;

	if (IsPlayerConnected(playerid) && IsDamageFeedActive(playerid))
	{
		DamageFeedUpdate(playerid, true);
	}
}

static DamageFeedUpdate(playerid, bool:modified = false)
{
	if (!IsDamageFeedActive(playerid)) 
	{
		if (s_DamageFeedGiven[playerid] != PlayerText:INVALID_TEXT_DRAW) 
		{
			PlayerTextDrawDestroy(playerid, s_DamageFeedGiven[playerid]);
			s_DamageFeedGiven[playerid] = PlayerText:INVALID_TEXT_DRAW;
		}

		if (s_DamageFeedTaken[playerid] != PlayerText:INVALID_TEXT_DRAW)
		{
			PlayerTextDrawDestroy(playerid, s_DamageFeedTaken[playerid]);
			s_DamageFeedTaken[playerid] = PlayerText:INVALID_TEXT_DRAW;
		}
		return;
	}

	if (s_DamageFeedGiven[playerid] == PlayerText:INVALID_TEXT_DRAW)
	{
		new PlayerText:td = CreatePlayerTextDraw(playerid, 200.0, 365.0, "_");

		if (td == PlayerText:INVALID_TEXT_DRAW)
		{
			printf("(wc) WARN: Unable to create damage feed textdraw");
		}
		else
		{
			PlayerTextDrawLetterSize(playerid, td, 0.2, 0.9);
			PlayerTextDrawColor(playerid, td, WC_FEED_GIVEN_COLOR);
			PlayerTextDrawFont(playerid, td, 1);
			PlayerTextDrawSetShadow(playerid, td, 0);
			PlayerTextDrawAlignment(playerid, td, 2);
			PlayerTextDrawSetOutline(playerid, td, 1);
			PlayerTextDrawBackgroundColor(playerid, td, 0x0000001A);

			s_DamageFeedGiven[playerid] = td;
		}
	}

	if (s_DamageFeedTaken[playerid] == PlayerText:INVALID_TEXT_DRAW)
	{
		new PlayerText:td = CreatePlayerTextDraw(playerid, 440.0, 365.0, "_");

		if (td == PlayerText:INVALID_TEXT_DRAW)
		{
			printf("(wc) WARN: Unable to create damage feed textdraw");
		} 
		else 
		{
			PlayerTextDrawLetterSize(playerid, td, 0.2, 0.9);
			PlayerTextDrawColor(playerid, td, WC_FEED_TAKEN_COLOR);
			PlayerTextDrawFont(playerid, td, 1);
			PlayerTextDrawSetShadow(playerid, td, 0);
			PlayerTextDrawAlignment(playerid, td, 2);
			PlayerTextDrawSetOutline(playerid, td, 1);
			PlayerTextDrawBackgroundColor(playerid, td, 0x0000001A);

			s_DamageFeedTaken[playerid] = td;
		}
	}

	new tick = GetTickCount();
	if (tick == 0) tick = 1;
	new lowest_tick = tick + 1;

	for (new i = 0, j = 0; i < sizeof(s_DamageFeedHitsGiven[]) - 1; i++)
	{
		if (!s_DamageFeedHitsGiven[playerid][i][e_Tick])
		{
			break;
		}

		if (tick - s_DamageFeedHitsGiven[playerid][i][e_Tick] >= s_DamageFeedHideDelay)
		{
			modified = true;

			for (j = i; j < sizeof(s_DamageFeedHitsGiven[]) - 1; j++)
			{
				s_DamageFeedHitsGiven[playerid][j][e_Tick] = 0;
			}

			break;
		}

		if (s_DamageFeedHitsGiven[playerid][i][e_Tick] < lowest_tick)
		{
			lowest_tick = s_DamageFeedHitsGiven[playerid][i][e_Tick];
		}
	}

	for (new i = 0, j = 0; i < sizeof(s_DamageFeedHitsTaken[]) - 1; i++)
	{
		if (!s_DamageFeedHitsTaken[playerid][i][e_Tick])
		{
			break;
		}

		if (tick - s_DamageFeedHitsTaken[playerid][i][e_Tick] >= s_DamageFeedHideDelay)
		{
			modified = true;

			for (j = i; j < sizeof(s_DamageFeedHitsTaken[]) - 1; j++)
			{
				s_DamageFeedHitsTaken[playerid][j][e_Tick] = 0;
			}

			break;
		}

		if (s_DamageFeedHitsTaken[playerid][i][e_Tick] < lowest_tick)
		{
			lowest_tick = s_DamageFeedHitsTaken[playerid][i][e_Tick];
		}
	}

	if (s_DamageFeedTimer[playerid] != -1)
	{
		KillTimer(s_DamageFeedTimer[playerid]);
	}

	if (tick - s_DamageFeedLastUpdate[playerid] < s_DamageFeedMaxUpdateRate && modified)
	{
		s_DamageFeedTimer[playerid] = SetTimerEx("WC_DamageFeedUpdate", s_DamageFeedMaxUpdateRate - (tick - s_DamageFeedLastUpdate[playerid]), false, "i", playerid);
	}
	else
	{
		if (lowest_tick == tick + 1)
		{
			s_DamageFeedTimer[playerid] = -1;
			modified = true;
		}
		else
		{
			s_DamageFeedTimer[playerid] = SetTimerEx("WC_DamageFeedUpdate", s_DamageFeedHideDelay - (tick - lowest_tick) + 10, false, "i", playerid);
		}

		if (modified)
		{
			DamageFeedUpdateText(playerid);
			s_DamageFeedLastUpdate[playerid] = tick;
		}
	}
}

static DamageFeedUpdateText(playerid)
{
	new buf[64 * WC_FEED_HEIGHT] = "";

	for (new i = 0, weapon[32]; i < sizeof(s_DamageFeedHitsGiven[]) - 1; i++) {
		if (!s_DamageFeedHitsGiven[playerid][i][e_Tick]) 
			break;

		if (s_DamageFeedHitsGiven[playerid][i][e_Weapon] == -1) {
			weapon = "Multiple";
		} 
		else 
			WC_GetWeaponName(s_DamageFeedHitsGiven[playerid][i][e_Weapon], weapon);

		if (s_DamageFeedHitsGiven[playerid][i][e_Issuer] == INVALID_PLAYER_ID) {
			format(
				buf,
				sizeof(buf),
				"%s%s +%.2f~n~",
				buf,
				weapon,
				s_DamageFeedHitsGiven[playerid][i][e_Amount] + 0.009);
		} 
		else {
			format(
				buf,
				sizeof(buf),
				"%s%s - %s +%.2f (%.2f)~n~",
				buf,
				s_DamageFeedHitsGiven[playerid][i][e_Name],
				weapon,
				s_DamageFeedHitsGiven[playerid][i][e_Amount] + 0.009,
				playerHealth[s_DamageFeedHitsGiven[playerid][i][e_Issuer]]);
		}
	}

	if (s_DamageFeedGiven[playerid] == PlayerText:INVALID_TEXT_DRAW) {
		printf("(wc) WARN: Doesn't have feed textdraw when needed");
	}
	if (buf[0]) {
		PlayerTextDrawSetString(playerid, s_DamageFeedGiven[playerid], buf);
		PlayerTextDrawShow(playerid, s_DamageFeedGiven[playerid]);
	}
	else
		PlayerTextDrawHide(playerid, s_DamageFeedGiven[playerid]);

	buf = "";

	for (new i = 0, weapon[32]; i < sizeof(s_DamageFeedHitsTaken[]) - 1; i++) {
		if (!s_DamageFeedHitsTaken[playerid][i][e_Tick]) {
			break;
		}

		if (s_DamageFeedHitsTaken[playerid][i][e_Weapon] == -1) {
			weapon = "Multiple";
		}
		else
		{
			WC_GetWeaponName(s_DamageFeedHitsTaken[playerid][i][e_Weapon], weapon);
		}

		if (s_DamageFeedHitsTaken[playerid][i][e_Issuer] == INVALID_PLAYER_ID) {
			format(
				buf,
				sizeof(buf),
				"%s%s -%.2f (%.2f)~n~",
				buf,
				weapon,
				s_DamageFeedHitsTaken[playerid][i][e_Amount] + 0.009,
				playerHealth[playerid]);
		}
		else
		{
			format(
				buf,
				sizeof(buf),
				"%s%s - %s -%.2f (%.2f)~n~",
				buf,
				s_DamageFeedHitsTaken[playerid][i][e_Name],
				weapon,
				s_DamageFeedHitsTaken[playerid][i][e_Amount] + 0.009,
				playerHealth[s_DamageFeedHitsGiven[playerid][i][e_Issuer]]);
		}
	}

	if (s_DamageFeedTaken[playerid] == PlayerText:INVALID_TEXT_DRAW)
		printf("(wc) WARN: Doesn't have feed textdraw when needed");

	if (buf[0]) {
		PlayerTextDrawSetString(playerid, s_DamageFeedTaken[playerid], buf);
		PlayerTextDrawShow(playerid, s_DamageFeedTaken[playerid]);
	}
	else
		PlayerTextDrawHide(playerid, s_DamageFeedTaken[playerid]);
}

static DamageFeedAddHitGiven(playerid, issuerid, Float:amount, weapon)
{
	foreach (new i : Player)
	{
		if(pSpectateId[i] == playerid && i != playerid)
		{
			Text3D_DamageInformer(i, playerid, issuerid, amount);

			PlayerPlaySound(i, s_DamageGivenSound, 0.0, 0.0, 0.0);
			DamageFeedAddHit(s_DamageFeedHitsGiven[i], i, issuerid, amount, weapon);
		}
	}
	Text3D_DamageInformer(playerid, playerid, issuerid, amount);

	DamageFeedAddHit(s_DamageFeedHitsGiven[playerid], playerid, issuerid, amount, weapon);
}

static DamageFeedAddHitTaken(playerid, issuerid, Float:amount, weapon)
{
	foreach (new i : Player)
	{
		if(pSpectateId[i] == playerid && i != playerid)
		{
			PlayerPlaySound(i, s_DamageTakenSound, 0.0, 0.0, 0.0);
			DamageFeedAddHit(s_DamageFeedHitsTaken[i], i, issuerid, amount, weapon);
		}
	}
	DamageFeedAddHit(s_DamageFeedHitsTaken[playerid], playerid, issuerid, amount, weapon);
}

static DamageFeedAddHit(arr[WC_FEED_HEIGHT][E_DAMAGE_FEED_HIT], playerid, issuerid, Float:amount, weapon)
{
	if (!IsDamageFeedActive(playerid))
		return;

	new tick = GetTickCount();
	if (tick == 0) tick = 1;
	new idx = -1;

	for (new i = 0; i < sizeof(arr) - 1; i++)
	{
		if (!arr[i][e_Tick])
		{
			break;
		}

		if (tick - arr[i][e_Tick] >= s_DamageFeedHideDelay)
		{
			DamageFeedRemoveHit(arr, i);
			break;
		}

		// Remove it and add it on top below
		if (arr[i][e_Issuer] == issuerid)
		{
			// Multiple weapons
			if (arr[i][e_Weapon] != weapon)
			{
				//weapon = -1;
			}

			amount += arr[i][e_Amount];
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		idx = 0;

		// Insert it at the top
		for (new i = sizeof(arr) - 1; i >= 1; i--)
		{
			arr[i] = arr[i - 1];
		}
	}

	arr[idx][e_Tick] = tick;
	arr[idx][e_Amount] = amount;
	arr[idx][e_Issuer] = issuerid;
	arr[idx][e_Weapon] = weapon;

	GetPlayerName(issuerid, arr[idx][e_Name], MAX_PLAYER_NAME);

	DamageFeedUpdate(playerid, true);
}

static DamageFeedRemoveHit(arr[WC_FEED_HEIGHT][E_DAMAGE_FEED_HIT], idx)
{
	for (new i = 0; i < WC_FEED_HEIGHT; i++)
	{
		if (i >= idx)
		{
			arr[i][e_Tick] = 0;
		}
	}
}

stock IsDamageFeedActive(playerid = -1)
{
	if (playerid != -1)
	{
		return !p_info[playerid][p_settings][STATUS_DAMAGE] || s_DamageFeed && !p_info[playerid][p_settings][STATUS_DAMAGE];
	}
	return s_DamageFeed;
}

stock SetDamageFeed(bool:toggle)
{
	s_DamageFeed = toggle;
	foreach (new i : Player)
	{
		DamageFeedUpdate(i);
	}
}

stock DI_OnPlayerConnect(playerid)
{
	new tick = GetTickCount();

	s_DamageFeedTimer[playerid] = -1;
	s_DamageFeedLastUpdate[playerid] = tick;

	if (s_DamageFeedGiven[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, s_DamageFeedGiven[playerid]);
		s_DamageFeedGiven[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}

	if (s_DamageFeedTaken[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, s_DamageFeedTaken[playerid]);
		s_DamageFeedTaken[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}

	if (s_DamageFeedTimer[playerid] != -1)
	{
		KillTimer(s_DamageFeedTimer[playerid]);
		s_DamageFeedTimer[playerid] = -1;
	}

	for (new i = 0; i < sizeof(s_DamageFeedHitsGiven[]); i++)
	{
		s_DamageFeedHitsGiven[playerid][i][e_Tick] = 0;
		s_DamageFeedHitsTaken[playerid][i][e_Tick] = 0;
	}

	DamageFeedUpdate(playerid);
	return 1;
}


stock DI_OnPlayerDisconnect(playerid)
{
	if (s_DamageFeedGiven[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, s_DamageFeedGiven[playerid]);
		s_DamageFeedGiven[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}

	if (s_DamageFeedTaken[playerid] != PlayerText:INVALID_TEXT_DRAW)
	{
		PlayerTextDrawDestroy(playerid, s_DamageFeedTaken[playerid]);
		s_DamageFeedTaken[playerid] = PlayerText:INVALID_TEXT_DRAW;
	}

	if (s_DamageFeedTimer[playerid] != -1)
	{
		KillTimer(s_DamageFeedTimer[playerid]);
		s_DamageFeedTimer[playerid] = -1;
	}

	return 1;
}

//////////////////////////////// temp credits:
stock const g_WeaponName[57][21] = {
	{"Fist"             }, {"Brass knuckles"}, {"Golf club"           },
	{"Nightstick"       }, {"Knife"         }, {"Bat"                 },
	{"Shovel"           }, {"Pool cue"      }, {"Katana"              },
	{"Chainsaw"         }, {"Purple dildo"  }, {"Dildo"               },
	{"Vibrator"         }, {"Vibrator"      }, {"Flowers"             },
	{"Cane"             }, {"Grenade"       }, {"Tear gas"            },
	{"Molotov"          }, {"Vehicle gun"   }, {"Vehicle gun"         },
	{"Vehicle gun"      }, {"Colt 45"       }, {"Silenced pistol"     },
	{"Deagle"           }, {"Shotgun"       }, {"Sawn-off shotgun"    },
	{"Combat shotgun"   }, {"Mac-10"        }, {"MP5"                 },
	{"AK-47"            }, {"M4"            }, {"Tec-9"               },
	{"Cuntgun"          }, {"Sniper"        }, {"Rocket launcher"     },
	{"Heat seeking RPG" }, {"Flamethrower"  }, {"Minigun"             },
	{"Satchel"          }, {"Detonator"     }, {"Spraycan"            },
	{"Fire extinguisher"}, {"Camera"        }, {"Night vision goggles"},
	{"Infrared goggles" }, {"Parachute"     }, {"Fake pistol"         },
	{"Pistol whip"      }, {"Vehicle"       }, {"Helicopter blades"   },
	{"Explosion"        }, {"Car parking"   }, {"Drowning"            },
	{"Collision"        }, {"Splat"         }, {"Unknown"             }
};
stock WC_GetWeaponName(weaponid, weapon[], len = sizeof(weapon))
{
	if (!(0 <= weaponid < sizeof(g_WeaponName))) {
		format(weapon, len, "Weapon %d", weaponid);
	}
	else
	{
		strunpack(weapon, g_WeaponName[weaponid], len);
	}
	return 1;
}

Text3D_DamageInformer(playerid, damagerid, issuerid, Float:amount)
{
    new dmg_string[9],
		Float:pOrigPosX,
	    Float:pOrigPosY,
	    Float:pOrigPosZ,
        Float:pHitPosX,
	    Float:pHitPosY,
	    Float:pHitPosZ,
        PlayerText3D:DamageTextLabel;
	GetPlayerLastShotVectors(damagerid, pOrigPosX, pOrigPosY, pOrigPosZ, pHitPosX, pHitPosY, pHitPosZ);
	valstr(dmg_string, floatround(amount)); 
	DamageTextLabel = CreatePlayer3DTextLabel(playerid, dmg_string, playerRetardKill{issuerid} == 1 ? 0xFF0000FF : 0xFFFFFFFF, pHitPosX, pHitPosY, pHitPosZ, 50);
	SetTimerEx("HideDamageInformer", 1250, false, "dd", playerid, _:DamageTextLabel);
    return true;
}

this::HideDamageInformer(playerid, PlayerText3D:label) 
{
	return DeletePlayer3DTextLabel(playerid, label);
}