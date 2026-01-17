/*
    Family System 2020
    Author: Vip_Uzer
*/

ShowFamilyContracts(playerid)
{
    STRING_GLOBAL[0] = EOS;
    new id_cont,
        family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return 1;
    for(new i; i < MAX_FAMILY_CONTRACTS; i++)
    {
        id_cont = FamilyContractData[i][fID];
        if(FamilyContractData[i][fID] == CONTRACT_FAMILY_ID_NONE)
            f(STRING_GLOBAL, "%s"I"[%d]"W" Контракта нет | Появится через: "I"%d минут\n",
                STRING_GLOBAL, i+1, FamilyContractData[i][fTime]);
        else
        {
            f(STRING_GLOBAL, "%s"I"[%d]"A" %s "W" Прогресс: "I"[%d/%d] "W" Время: "I"[%d/%d]\n",
                STRING_GLOBAL, i+1,
                CONRACT_FAMILY_INIT[id_cont][fName],
                FamilyData[family_idx][fContractProgress][i],
                CONRACT_FAMILY_INIT[id_cont][fProgress],
                FamilyContractData[i][fTime],
                CONRACT_FAMILY_INIT[id_cont][fTime]);
        }
    }
    f(STRING_GLOBAL, "%s"W"Что такое "I"'Контракты'?", STRING_GLOBAL, FamilyData[family_idx][fMoney]);
    ShowPlayerDialog(playerid, D_FAMILY_CONTRACTS_LIST, DIALOG_STYLE_LIST, ""I"Контракты", STRING_GLOBAL, "Выбор", "Отмена");
    return 1;
}

UpdateFamilyContract(playerid, contract_id, count_progress = 1)
{
    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx == -1) return 1;
    if(FamilyData[family_idx][fOffice] != 1) return 1;

    for(new i; i < MAX_FAMILY_CONTRACTS; i++)
    {
        if(FamilyContractData[i][fID] == contract_id)
        {
            FamilyData[family_idx][fContractProgress][i] += count_progress;
            if(FamilyData[family_idx][fContractProgress][i] >= CONRACT_FAMILY_INIT[contract_id][fProgress])
            {
                UpdateFamilyLevel(playerid, CONRACT_FAMILY_INIT[contract_id][fExp]);

                STRING_GLOBAL[0] = EOS;
                format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "Ваша семья выполнила контракт '%s'. Награда: %d опыта и %d$",
                    CONRACT_FAMILY_INIT[contract_id][fName], CONRACT_FAMILY_INIT[contract_id][fExp], CONRACT_FAMILY_INIT[contract_id][fMoney]);
                SendFamilyMessage(family_idx, STRING_GLOBAL);

                FamilyData[family_idx][fMoney] += CONRACT_FAMILY_INIT[contract_id][fMoney];

                STRING_GLOBAL[0] = EOS;
                mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `money` = %d WHERE `id` = %d",
                    FamilyData[family_idx][fMoney], FamilyData[family_idx][fMysqlID]);
                mysql_tquery (con_bd, STRING_GLOBAL);

                FamilyData[family_idx][fContractProgress][i] = 0;
                FamilyDeleteContract(contract_id, family_idx);
            }
            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `contract_progress_%d` = %d WHERE `id` = %d",
                i, FamilyData[family_idx][fContractProgress][i], FamilyData[family_idx][fMysqlID]);
            mysql_tquery(con_bd, STRING_GLOBAL);
            break;
        }
    }
    return 1;
}

FamilyDeleteContract(contract_id, family_win = -1)
{
    for(new i; i < MAX_FAMILY_CONTRACTS; i++)
    {
        if(FamilyContractData[i][fID] == contract_id)
        {
            for(new idx_family = family_count-1; idx_family != -1; idx_family--)
            {
                if(idx_family == family_win && family_win != -1)
                {
                    FamilyData[i][fContractProgress][i] = 0;
                    continue;
                }
                if(FamilyData[idx_family][fContractProgress][i] > 0 && family_win != -1)
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "Ваша семья не выполнила контракт '%s'. Победители: '%s'.",
                        CONRACT_FAMILY_INIT[contract_id][fName], FamilyData[family_win][fName]);
                    SendFamilyMessage(idx_family, STRING_GLOBAL);
                }
                if(FamilyData[idx_family][fContractProgress][i] > 0 && FamilyContractData[i][fTime] <= 0)
                {
                    STRING_GLOBAL[0] = EOS;
                    f(STRING_GLOBAL, "Ваша семья не выполнила контракт '%s'. Причина: Время закончилось.", CONRACT_FAMILY_INIT[contract_id][fName]);
                    SendFamilyMessage(idx_family, STRING_GLOBAL);
                }
                FamilyData[idx_family][fContractProgress][i] = 0;
            }

            FamilyContractData[i][fID] = CONTRACT_FAMILY_ID_NONE;
            FamilyContractData[i][fTime] = RandomEx(15, 30);

            STRING_GLOBAL[0] = EOS;
            mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `family` SET `contract_progress_%d` = 0 WHERE 1", i);
            mysql_tquery (con_bd, STRING_GLOBAL);
            break;
        }
    }
}


forward TOP_Contract_Family(playerid, id_family, contr_id);
public TOP_Contract_Family(playerid, id_family, contr_id)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) {
        ShowFamilyContracts(playerid);
        SendError(playerid, "Никто не выполненяет этот контракт.");
        return 1;
    }
    new u_score, u_name[21];
    STRING_GLOBAL = "[#] Название\tПрогресс\n";
    for(new i; i < rows; i ++)
    {
        cache_get_value_index(i, 0, u_name);
        cache_get_value_index_int(i, 1, u_score);
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\t%d\n", STRING_GLOBAL, i+1, u_name,  u_score);
    }
    f(STRING_GLOBAL, "%s- %s\t%d\n", STRING_GLOBAL, FamilyData[id_family][fName], FamilyData[id_family][fContractProgress][contr_id]);
    ShowPlayerDialog(playerid, D_FAMILY_CONTRACTS_INFO, DIALOG_STYLE_TABLIST_HEADERS, ""I"Рейтинг по контракту", STRING_GLOBAL, "Понял", "");
    return 1;
}
