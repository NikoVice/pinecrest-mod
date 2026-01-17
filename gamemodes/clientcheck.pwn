// SendClientCheck example script by evgen1137
// thanks to MTA devs for structs
#include <a_samp>

public OnFilterScriptInit()
{

}

public OnFilterScriptExit()
{

}

public OnPlayerConnect(playerid)
{
	SendClientCheck(playerid, 0x46, 1598, 0, 28); // 1598 - beachball
	SendClientCheck(playerid, 0x47, 1598, 0, 48); // 1598 - beachball
	return 1;
}

public OnClientCheckResponse(playerid, type, arg, response)
{
	CallRemoteFunction("CheckedIsPC", "i", playerid);
	return 1;
}

