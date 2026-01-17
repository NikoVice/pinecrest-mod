/*
    Author: Vip_Uzer
*/

CMD:fractionvehspawn(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    new fraction_id = strval(params);
    if(!(1 <= fraction_id < MAX_FRACTIONS)) return 1;
    SetFractionVehSpawnPos(playerid, fraction_id);
    return 1;
}
alias:fractionvehspawn("fvs");

CMD:fractionvehadd(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "dddd", params[0], params[1], params[2], params[3]))
        return SendInfo(playerid, "Используйте: /fractionvehicleadd [Fraction ID] [SLOT_ID] [MODEL_ID] [COUNT]");
    if(!(1 <= params[0] < MAX_FRACTIONS)) return 1;
    params[1]--;
    if(!(1 <= params[1] <= MAX_FRACTIONS_VEHICLES)) return SendInfo(playerid, "Используйте: /fractionvehicleadd [Fraction ID] [SLOT_ID] [MODEL_ID] [COUNT]");
    new idx = GetSlotFractionVehicle(params[0], params[2]);
    if(idx != -1 && idx != params[1])
        return SendError(playerid, "Данная модель уже есть в автопарке фракции под другим слотом #%d.", idx+1);

    FractionsData[params[0]][fVehModelsID][params[1]] = params[2];
    FractionsData[params[0]][fVehModelMaxCount][params[1]] = params[3];

    if(idx == -1) FractionsData[params[0]][fVehModelUseCount][params[1]] = params[3];
    SaveFractionVehParkings(params[0]);
    return 1;
}
alias:fractionvehadd("fvam", "fva");

GetSlotFractionVehicle(fraction_id, modelid) // защита от дебилов
{
    for(new i = MAX_FRACTIONS_VEHICLES-1; i != -1; i--)
    {
        if(FractionsData[fraction_id][fVehModelsID][i] == modelid)
        {
            return i;
        }
    }
    return -1;
}

CMD:fractionvehdel(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "dd", params[0], params[1]))
        return SendInfo(playerid, "Используйте: /fractionvehicledel [Fraction ID] [SLOT_ID]");
    if(!(1 <= params[0] < MAX_FRACTIONS)) return 1;
    if(!(1 <= params[1] <= MAX_FRACTIONS_VEHICLES)) return SendInfo(playerid, "Используйте: /fractionvehicledelmodel [Fraction ID] [SLOT_ID]");
    //params[0]--;
    params[1]--;
    if(FractionsData[params[0]][fVehModelsID][params[1]] == 0)
        return SendError(playerid, "В данном слоте нет моделей.");
    FractionsData[params[0]][fVehModelsID][params[1]] = 0;
    FractionsData[params[0]][fVehModelMaxCount][params[1]] = 0;

    SaveFractionVehParkings(params[0]);
    return 1;
}
alias:fractionvehdel("fvdm", "fvd");

SaveFractionVehParkings(fraction_id)
{
    new strFVPModels[128], strFVPMaxModels[128], strFVPRank[128];
    for(new i; i < MAX_FRACTIONS_VEHICLES; i++)
    {
        f(strFVPModels, "%s%d%s", strFVPModels, FractionsData[fraction_id][fVehModelsID][i], i == MAX_FRACTIONS_VEHICLES-1 ? "":"|");
        f(strFVPMaxModels, "%s%d%s", strFVPMaxModels, FractionsData[fraction_id][fVehModelMaxCount][i], i == MAX_FRACTIONS_VEHICLES-1 ? "":"|");
        f(strFVPRank, "%s%d%s", strFVPRank, FractionsData[fraction_id][fVehAccessRank][i], i == MAX_FRACTIONS_VEHICLES-1 ? "":"|");
    }

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `fractions_data` SET `veh_models_id` = '%s', `veh_model_max_count` = '%s', `veh_access_rank` = '%s' WHERE `id` = %d",
        strFVPModels, strFVPMaxModels, strFVPRank, fraction_id);
    mysql_tquery(con_bd, STRING_GLOBAL);
    return 1;
}

CMD:fractionvehrank(playerid, params[])
{
    if(p_info[playerid][admin] < 7) return 1;
    if(sscanf(params, "ddd", params[0], params[1], params[2]))
        return SendInfo(playerid, "Используйте: /fractionvehrank [Fraction ID] [SLOT_ID] [RANG]");
    if(!(1 <= params[0] < MAX_FRACTIONS) ||
        !(1 <= params[1] <= 10) ||
        !(1 <= params[2] <= 10)) return 1;
    //params[0]--;
    params[1]--;
    new idx = GetSlotFractionVehicle(params[0], FractionsData[params[1]][fVehModelsID][params[1]]);
    if(idx == -1)
        return SendError(playerid, "В данном слоте модели нет");

    FractionsData[params[0]][fVehAccessRank][params[1]] = params[2];
    SaveFractionVehParkings(params[0]);
    return 1;
}
alias:fractionvehrank("fvr");
