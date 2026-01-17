CMD:cctv(playerid, params[])
{
    new id;
    if(!IsPlayerFractionPolice(playerid))    return SendError(playerid, "Вы должны быть полицейским.");
    new option[64], secoption[144];

    if(sscanf(params, "s[64]S()[144]", option, secoption)) return SendInfo(playerid, "/cctv [show / exit / list]");

    if(strequals(option, "show"))
    {
        /*BUG:FIX
        new factionid = PlayerInfo[playerid][pFaction];
        if(!IsPlayerInRangeOfPoint(playerid, 30.0, Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ])) {
            return SendError(playerid, "Данная функция доступна только в HQ.");
        }
        */

        if(sscanf(secoption, "i", id)) return SendInfo(playerid, "/cctv show [ID камеры]");
        if(id < 0 || id > MAX_CCTV-1 || !CCTVInfo[id][tvObjectOn]) return SendError(playerid, "Камера не найдена.");
        if(CCTVInfo[id][tvBreak]) {
            SetPlayerGPS(playerid, CCTVInfo[id][tvPosX],CCTVInfo[id][tvPosY],CCTVInfo[id][tvPosZ], 3.0);
            return SendError(playerid, "Камера неисправна.");
        }

        if(!p_temp[playerid][pCCTV])
        {
            if(GetPlayerState(playerid) != PLAYER_STATE_SPECTATING)
            {
                GetPlayerPos(playerid, pPosBeforeSpectateX[playerid], pPosBeforeSpectateY[playerid], pPosBeforeSpectateZ[playerid]);
                pInteriorBeforeSpectate[playerid] = GetPlayerInterior(playerid);
                pVirtualWorldBeforeSpectate[playerid] = GetPlayerVirtualWorld(playerid);
                SetPVarInt(playerid, !"spawn_after_spectate_mode", 2);
            }
            p_temp[playerid][pCCTV] = 1;
            SetPVarInt(playerid, #CCTV_ID, id + 1);

            if(IsPlayerInAnyVehicle(playerid)) {
                SetPVarInt(playerid, #CCTV_VEH, GetPlayerVehicleID(playerid));
                SetPVarInt(playerid, #CCTV_VEH_SEAT, GetPlayerVehicleSeat(playerid));
                RemovePlayerFromVehicle(playerid);
            }
            SetPlayerInterior(playerid, CCTVInfo[id][tvInt]);
            SetPlayerVirtualWorld(playerid, CCTVInfo[id][tvVW]);

            if(MdcInfo[playerid][mdcPage] != PAGE_NONE) {
                SetPVarInt(playerid, #CCTV_MDC_USE, 1);
                MDC_Hide(playerid);
            }
            for(new i; i < 11;i++) TextDrawShowForPlayer(playerid, TD_ZondCam[i]);
            TogglePlayerSpectating(playerid, true);
            SetTimerEx("CCTV_PLA_TIMER", 1000, false, "ii", playerid, id);
        }
    }

    else if(strequals(option, "list"))
    {
        new dialog_header[96] = "[#] Камера\tID камеры\tСостояние\n", dialog_body[3072];

        format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

        new count;
        for(new i = 0; i < MAX_CCTV; i++)
        {
            if(CCTVInfo[i][tvObjectOn])
            {
                new break_str[24];
                count++;

                if(CCTVInfo[i][tvBreak])    format(break_str, sizeof(break_str), "{"#cLIGHTRED"}Не работает");
                else                        format(break_str, sizeof(break_str), "{"#cGREEN"}Работает");

                format(dialog_body, sizeof(dialog_body), "%s"I"[%d]"W" %s\t%i\t%s\n", dialog_body, i + 1, CCTVInfo[i][tvName], i, break_str);
            }
        }
        if(!count) dialog_body = "Нет доступных камер..";
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список камер", dialog_body, "Закрыть", "");
        return 1;
    }

    else if(strequals(option, "exit"))
    {
        if(!p_temp[playerid][pCCTV]) return SendError(playerid, "Вы не наблюдаете через камеру.");
        p_temp[playerid][pCCTV] = 0;
        CCTVInterface(playerid, false);
        TogglePlayerSpectating(playerid, false);
        Fix_TogglePlayerControllable(playerid, true);

        for(new i; i < 11; i++) TextDrawHideForPlayer(playerid, TD_ZondCam[i]);

        if(GetPVarInt(playerid, #CCTV_MDC_USE)) {
            MDC_Show(playerid);
            DeletePVar(playerid, #CCTV_MDC_USE);
        }
        else CancelSelectTextDraw(playerid);

        DeletePVar(playerid, #CCTV_ID);
        if(GetPVarInt(playerid, #CCTV_VEH)) SetTimerEx("CCTV_VEH_TIMER", 1000, false, "i", playerid);
    }
    else SendInfo(playerid, "/cctv [параметр - show|exit|list]");
    return 1;
}

this::CCTV_VEH_TIMER(playerid) {
    PutPlayerInVehicle(playerid, GetPVarInt(playerid, #CCTV_VEH), GetPVarInt(playerid, #CCTV_VEH_SEAT));
    DeletePVar(playerid, #CCTV_VEH);
    DeletePVar(playerid, #CCTV_VEH_SEAT);
    return 1;
}

this::CCTV_PLA_TIMER(playerid, id)
{
    SetPlayerPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);
    Fix_TogglePlayerControllable(playerid, false);

    new Float:posCamX = CCTVInfo[id][tvPosX] + 2.0 * floatsin(-CCTVInfo[id][tvPosRZ], degrees),
    	Float:posCamY = CCTVInfo[id][tvPosY] + 2.0 * floatcos(-CCTVInfo[id][tvPosRZ], degrees);

    SetPlayerCameraPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);
    SetPlayerCameraLookAt(playerid, posCamX, posCamY, CCTVInfo[id][tvPosZ]);

    SetPVarFloat(playerid, #CCTV_FLOAT, CCTVInfo[id][tvPosZ]);
    CCTVInterface(playerid);
    SendInfo(playerid, "Используйте кнопки для управления камерой, {DABB3E}/cctv exit {FFFFFF}для выхода из режима просмотра.");
    return 1;
}

CCTVInterface(playerid, bool:status = true)
{
    if(status == true) {
        CctvCreateArrows(playerid);
		for(new b = 0; b < 4; b++)  PlayerTextDrawShow(playerid, CamArrows[playerid][b]);
		SelectTextDraw(playerid, 255);
	}
    else {
		CctvDestroyArrows(playerid);
		for(new b = 0; b < 4; b++)  PlayerTextDrawHide(playerid, CamArrows[playerid][b]);
	}
    return 1;
}

#define CCTV_MOVE_SPEED  1.0
CC_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    new id = GetPVarInt(playerid, #CCTV_ID)-1, Float: oldPosRZ = CCTVInfo[id][tvPosRZ];
    if(IsDynamicObjectMoving(CCTVInfo[id][tvObject])) return 1;
    if(p_temp[playerid][p_listitem_int] == 100500) return 1;
    p_temp[playerid][p_listitem_int] = 100500;

	if(playertextid == CamArrows[playerid][0]) //++
    {
		CCTVInfo[id][tvPosRZ] -= 30.0;
		if(CCTVInfo[id][tvPosRZ] <= 0.0) {
			CCTVInfo[id][tvPosRZ] = 360.0;
		}
	}
	else if(playertextid == CamArrows[playerid][1]) //--
    {
        CCTVInfo[id][tvPosRZ] += 30.0;
		if(CCTVInfo[id][tvPosRZ] >= 360.0) {
			CCTVInfo[id][tvPosRZ] = 0.0;
		}
	}
	else if(playertextid == CamArrows[playerid][2]) //up
    {
        if(GetPVarFloat(playerid, #CCTV_FLOAT)-CCTVInfo[id][tvPosZ] < 2.0) SetPVarFloat(playerid, #CCTV_FLOAT, GetPVarFloat(playerid, #CCTV_FLOAT)+0.5);
	}
	else if(playertextid == CamArrows[playerid][3]) //down
    {
        if(GetPVarFloat(playerid, #CCTV_FLOAT)-CCTVInfo[id][tvPosZ] > -1.5) SetPVarFloat(playerid, #CCTV_FLOAT, GetPVarFloat(playerid, #CCTV_FLOAT)-0.5);
	}

	MoveDynamicObject( CCTVInfo[id][tvObject],
						CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], GetPVarFloat(playerid, #CCTV_FLOAT),
						CCTV_MOVE_SPEED,
						CCTVInfo[id][tvPosRX], CCTVInfo[id][tvPosRY], CCTVInfo[id][tvPosRZ] );

	new Float:posCam1X = CCTVInfo[id][tvPosX], Float:posCam1Y = CCTVInfo[id][tvPosY],
		Float:posCam2X = CCTVInfo[id][tvPosX], Float:posCam2Y = CCTVInfo[id][tvPosY];

    posCam1X += 2.0 * floatsin(-oldPosRZ, degrees);
    posCam1Y += 2.0 * floatcos(-oldPosRZ, degrees);
    posCam2X += 2.0 * floatsin(-CCTVInfo[id][tvPosRZ], degrees);
    posCam2Y += 2.0 * floatcos(-CCTVInfo[id][tvPosRZ], degrees);

    InterpolateCameraPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ], CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ], 700);
    InterpolateCameraLookAt(playerid, posCam1X, posCam1Y, GetPVarFloat(playerid, #CCTV_FLOAT), posCam2X, posCam2Y, GetPVarFloat(playerid, #CCTV_FLOAT), 700);
    SetTimerEx("CCTVFixCamera", 710, false, "iiff", playerid, id, posCam2X, posCam2Y);
    return 1;
}

this::CCTVFixCamera(playerid, id, Float:px2, Float:py2)
{
    SetPlayerCameraPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);
    SetPlayerCameraLookAt(playerid, px2, py2, GetPVarFloat(playerid, #CCTV_FLOAT));
    p_temp[playerid][p_listitem_int] = -1;
    return 1;
}


CctvCreateArrows(playerid)
{
	CamArrows[playerid][0] = CreatePlayerTextDraw(playerid, 424.404205, 380.493133, "~n~>>>~n~_");
	PlayerTextDrawTextSize(playerid, CamArrows[playerid][0], 30.000000, 112.000000);
	PlayerTextDrawLetterSize(playerid, CamArrows[playerid][0], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, CamArrows[playerid][0], 2);
	PlayerTextDrawColor(playerid, CamArrows[playerid][0], 255);
	PlayerTextDrawUseBox(playerid, CamArrows[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, CamArrows[playerid][0], 0xc7c7c7FF);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, CamArrows[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, CamArrows[playerid][0], 255);
	PlayerTextDrawFont(playerid, CamArrows[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, CamArrows[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, CamArrows[playerid][0], true);

	CamArrows[playerid][1] = CreatePlayerTextDraw(playerid, 236.100006, 380.493133, "~n~<<<~n~_");
	PlayerTextDrawTextSize(playerid, CamArrows[playerid][1], 30.000000, 112.000000);
	PlayerTextDrawLetterSize(playerid, CamArrows[playerid][1], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, CamArrows[playerid][1], 2);
	PlayerTextDrawColor(playerid, CamArrows[playerid][1], 255);
	PlayerTextDrawUseBox(playerid, CamArrows[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, CamArrows[playerid][1], 0xc7c7c7FF);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, CamArrows[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, CamArrows[playerid][1], 255);
	PlayerTextDrawFont(playerid, CamArrows[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, CamArrows[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, CamArrows[playerid][1], true);

    CamArrows[playerid][2] = CreatePlayerTextDraw(playerid, 330.2521055, 347.493133, "~n~up~n~_");
	PlayerTextDrawTextSize(playerid, CamArrows[playerid][2], 30.000000, 112.000000);
	PlayerTextDrawLetterSize(playerid, CamArrows[playerid][2], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, CamArrows[playerid][2], 2);
	PlayerTextDrawColor(playerid, CamArrows[playerid][2], 255);
	PlayerTextDrawUseBox(playerid, CamArrows[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, CamArrows[playerid][2], 0xc7c7c7FF);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, CamArrows[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, CamArrows[playerid][2], 255);
	PlayerTextDrawFont(playerid, CamArrows[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, CamArrows[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, CamArrows[playerid][2], true);

    CamArrows[playerid][3] = CreatePlayerTextDraw(playerid, 330.2521055, 413.493133, "~n~down~n~_");
	PlayerTextDrawTextSize(playerid, CamArrows[playerid][3], 30.000000, 112.000000);
	PlayerTextDrawLetterSize(playerid, CamArrows[playerid][3], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, CamArrows[playerid][3], 2);
	PlayerTextDrawColor(playerid, CamArrows[playerid][3], 255);
	PlayerTextDrawUseBox(playerid, CamArrows[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, CamArrows[playerid][3], 0xc7c7c7FF);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, CamArrows[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, CamArrows[playerid][3], 255);
	PlayerTextDrawFont(playerid, CamArrows[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, CamArrows[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, CamArrows[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, CamArrows[playerid][3], true);
    return 1;
}

CctvDestroyArrows(playerid)
{
    for (new i; i < 4; i++) {
        PlayerTextDrawDestroy(playerid, CamArrows[playerid][i]);
        CamArrows[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
    }
    return 1;
}

CMD:acctv(playerid, params[])
{
    if(p_info[playerid][admin] < 5) return 1;
    new option[64], secoption[144];
    if(sscanf(params, "s[64]S()[144]", option, secoption)) return SendInfo(playerid, "/acctv [create / remove / edit / list / repall / goto]");

    if(strequals(option, "create"))
    {
        new cctv_name[144];
        if(sscanf(secoption, "s[144]", cctv_name)) return SendInfo(playerid, "/acctv create [название]");
        if(strlen(cctv_name) < 4 || strlen(cctv_name) > 30) return SendError(playerid, "Название камеры от 4 до 30 символов.");
        if(!CheckCCTVEquals(cctv_name)) return SendError(playerid, "Такое название камеры уже существует.");

        new nearcam = GetNearestCamera(playerid, 40.0);
        if(nearcam != -1) return SendError(playerid, "В этом радиусе уже работает камера.");

        new id = -1;
        for(new i = 0; i < MAX_CCTV; i++)
        {
            if(CCTVInfo[i][tvObjectOn]) continue;
            id = i;
            break;
        }
        if(id == -1) return SendError(playerid, "Достигнуто максимальное кол-во камер CCTV.");

        format(CCTVInfo[id][tvName], 32, "%s", cctv_name);
        GetPlayerPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);

        CCTVInfo[id][tvPosRX] =
        CCTVInfo[id][tvPosRY] =
        CCTVInfo[id][tvPosRZ] = 0.0;
        CCTVInfo[id][tvInt] = GetPlayerInterior(playerid);
        CCTVInfo[id][tvVW] = GetPlayerVirtualWorld(playerid);
        CCTVInfo[id][tvObject] = CreateDynamicObject(1886, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ], 0.0, 0.0, 0.0, CCTVInfo[id][tvVW], CCTVInfo[id][tvInt]);
        CCTVInfo[id][tvCollision] = CreateDynamicObject(3800, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]-1.0, CCTVInfo[id][tvPosRX], CCTVInfo[id][tvPosRY], CCTVInfo[id][tvPosRZ], CCTVInfo[id][tvVW], CCTVInfo[id][tvInt]);
        SetDynamicObjectMaterial(CCTVInfo[id][tvCollision], 0, 16644, "a51_detailstuff", "roucghstonebrtb", 0x00000000);
        CCTVInfo[id][tvObjectOn] = 1;
        AddCameraToFile(id, CCTVInfo[id][tvInt], CCTVInfo[id][tvVW], CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ], 0.0, 0.0, 0.0, cctv_name);
        //BUG:FIX SendAdmMessageToPlayer(playerid, "Вы создали камеру %s [ID: %i].", CCTVInfo[id][tvName], id);
        return 1;
    }

    else if(strequals(option, "remove"))
    {
        new id;
        if(sscanf(secoption, "i", id)) return SendInfo(playerid, "/acctv remove [ID камеры]");
        if(id < 0 || id >= MAX_CCTV || !CCTVInfo[id][tvObjectOn]) return SendError(playerid, "Камера не найдена.");

        new query[128];
        mysql_format(con_bd, query, sizeof(query), "DELETE FROM `cctvs` WHERE `id` = %i", CCTVInfo[id][tvID]);
        mysql_tquery(con_bd, query);

        if(IsValidDynamicObject(CCTVInfo[id][tvObject]))
        {
            DestroyDynamicObject(CCTVInfo[id][tvObject]);
            DestroyDynamicObject(CCTVInfo[id][tvCollision]);
            CCTVInfo[id][tvObject] = INVALID_OBJECT_ID;
            CCTVInfo[id][tvCollision] = INVALID_OBJECT_ID;
        }

        CCTVInfo[id][tvID] =
        CCTVInfo[id][tvObjectOn] = 0;
        //BUG:fix SendAdmMessageToPlayer(playerid, "Вы удалили камеру [ID: %i].", id);
        return 1;
    }

    else if(strequals(option, "edit"))
    {
        new id, parameters[64], arg[144];
        if(sscanf(secoption, "is[64]S()[144]", id, parameters, arg)) return SendInfo(playerid, "/acctv edit [ID камеры] [pos / name]");
        if(id < 0 || id >= MAX_CCTV || !CCTVInfo[id][tvObjectOn] || !IsValidDynamicObject(CCTVInfo[id][tvObjectOn])) return SendError(playerid, "Камера не найдена.");
        if(strequals(parameters, "pos"))
        {
            if(GetPVarInt(playerid, #edit_cctv)) return SendError(playerid, "Вы уже редактируете камеру.");
            if(!IsPlayerInRangeOfPoint(playerid, 5.0, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ])) return SendError(playerid, "Вы должны быть рядом с камерой.");

            SetPVarInt(playerid, #edit_cctv, id + 1);
            EditDynamicObject(playerid, CCTVInfo[id][tvObject]);
            return 1;
        }
        //BUG:fix
        /*
        else if(strequals(parameters, "name"))
        {
            new cctv_name[32];

            if(sscanf(arg, "s[32]", cctv_name)) return SendInfo(playerid, "/acctv edit [ID камеры] name [название]");
            if(strlen(cctv_name) < 4 || strlen(cctv_name) > 30) return SendError(playerid, "Название камеры от 4 до 30 символов.");
            if(!CheckCCTVEquals(cctv_name)) return SendError(playerid, "Такое название камеры уже существует.");

            format(CCTVInfo[id][tvName], 32, "%s", cctv_name);
            SQL_SetString("cctvs", "info", CCTVInfo[id][tvName], CCTVInfo[id][tvID]);
            SendAdmMessageToPlayer(playerid, "Вы изменили название камеры [ID: %i] на %s.", id, CCTVInfo[id][tvName]);
            return 1;
        }
        */
    }

    else if(strequals(option, "list"))
    {
        new dialog_header[96] = "[#] Название камеры\tID\tСостояние\n", dialog_body[3072];

        format(dialog_body, sizeof(dialog_body), "%s", dialog_header);

        for(new i = 0; i < MAX_CCTV; i++)
        {
            if(!CCTVInfo[i][tvObjectOn]) continue;
            new break_str[24];
            if(CCTVInfo[i][tvBreak]) format(break_str, sizeof(break_str), "{"#cLIGHTRED"}Не работает");
            else format(break_str, sizeof(break_str), "{"#cGREEN"}Работает");
            format(dialog_body, sizeof(dialog_body), "%s"I"[%d]"W" %s\t%i\t%s\n", dialog_body, i + 1, CCTVInfo[i][tvName], i, break_str);
        }
        ShowPlayerDialog(playerid, D_NULL, DIALOG_STYLE_TABLIST_HEADERS, ""I"Список камер", dialog_body, "Закрыть", "");
        return 1;
    }

    else if(strequals(option, "repall"))
    {
        for(new i = 0; i < MAX_CCTV; i++)
        {
            if(!CCTVInfo[i][tvObjectOn]) continue;
            if(!IsValidDynamicObject(CCTVInfo[i][tvObject])) continue;
            if(!CCTVInfo[i][tvBreak]) continue;

            SetCameraBreakState(i, 0);
        }
        //BUG:FIX SendAdmMessageToPlayer(playerid, "Вы починили все камеры видеонаблюдения.");
    }

    else if(strequals(option, "goto"))
    {
        new id;
        if(sscanf(secoption, "i", id)) return SendInfo(playerid, "/acctv goto [ID cctv]");
        if(id < 0 || id > MAX_CCTV || !CCTVInfo[id][tvObjectOn]) return SendError(playerid, "CCTV не найден.");

        SetPlayerPos(playerid, CCTVInfo[id][tvPosX], CCTVInfo[id][tvPosY], CCTVInfo[id][tvPosZ]);
        SetPlayerVirtualWorld(playerid, CCTVInfo[id][tvVW]);
        SetPlayerInterior(playerid, CCTVInfo[id][tvInt]);
        return 1;
    }
    else SendInfo(playerid, "/acctv [create / remove / edit / list / repall / goto]");

    return 1;
}
