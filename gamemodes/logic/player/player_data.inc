/*
    Author: Vip_Uzer
    Flin RolePlay
    (c) 2021
*/
LoadPlayerAccount(playerid)
{
    Fix_TogglePlayerControllable(playerid, true);
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `accounts` WHERE `id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "LoadPlayerAccountCallback","ii", playerid, p_info[playerid][ID]);
}

forward LoadPlayerAccountCallback(playerid, mysql_ID);
public LoadPlayerAccountCallback(playerid, mysql_ID)
{
    new rows = cache_num_rows();
    if(!rows || mysql_ID != p_info[playerid][ID])
    {
        SendError(playerid, "Что-то пошло не так, попробуйте заново или обновите версию клиента.");
        Kick(playerid);
        return 1;
    }
    foreach(new i: Player)
    {
        if(i == playerid) continue;
        if(p_info[i][ID] == p_info[playerid][ID] && p_info[i][loggedIn] != 0)
        {
            SendError(playerid, "Игрок с таким ником уже есть на сервере.");
            Kick(playerid);
            return 1;
        }
    }

    new isPlayerMobile = IsPlayerMobile(playerid);

    cache_get_value_name_int(0,"referral",p_info[playerid][referral]);
    cache_get_value_name_int(0,"referralmoney",p_info[playerid][referralmoney]);
    cache_get_value_name_int(0,"referralcount",p_info[playerid][referralcount]);

    cache_get_value_name(0, "regip",p_info[playerid][regIP],MAX_IP_LENGTH);
    cache_get_value_name(0, "mail",p_info[playerid][mail],64);
    cache_get_value_name_int(0,"email_confirmed",p_info[playerid][email_confirmed]);
    //cache_get_value_name(0, "datareg",p_info[playerid][reg_data],16);
    cache_get_value_name_int(0,"sex",p_info[playerid][sex]);
    cache_get_value_name_int(0,"money",p_info[playerid][cash]);
    cache_get_value_name_int(0,"passport",p_info[playerid][passport]);
    cache_get_value_name_int(0,"passport_time",p_info[playerid][passport_time]);
    cache_get_value_name_int(0,"level",p_info[playerid][level]);
    cache_get_value_name_int(0,"exp",p_info[playerid][exp]);
    cache_get_value_name_int(0,"admin",p_info[playerid][admin]);
    cache_get_value_name_int(0,"helper",p_info[playerid][helper]);
    cache_get_value_name_int(0,"youtube_adm",p_info[playerid][youtube_adm]);
    cache_get_value_name_int(0,"admin_pass",p_info[playerid][admin_pass]);
    cache_get_value_name_int(0,"flinmoney",p_info[playerid][flinmoney]);
    cache_get_value_name_int(0,"donate_all_new",p_info[playerid][donate_all_new]);
    cache_get_value_name_int(0,"med_card",p_info[playerid][med_card]);
    cache_get_value_name_int(0,"med_card_time",p_info[playerid][med_card_time]);
    cache_get_value_name_int(0,"leader",p_info[playerid][leader]);
    cache_get_value_name_int(0,"member",p_info[playerid][member]);

    if(p_info[playerid][member] != 0)
    {
        if(!(0 <= p_info[playerid][member] < MAX_FRACTIONS))
        {
            p_info[playerid][member] = 0;
            Iter_Remove(gFactionPlayers[p_info[playerid][member]], playerid);
        }
        else Iter_Add(gFactionPlayers[p_info[playerid][member]], playerid);
    }
    cache_get_value_name_int(0,"rang",p_info[playerid][rang]);
    if(p_info[playerid][member] && p_info[playerid][rang] < 1) p_info[playerid][rang] = 1;
    cache_get_value_name_int(0,"fskin",p_info[playerid][fskin]);
    cache_get_value_name_int(0,"bank",p_info[playerid][bank]);
    cache_get_value_name_int(0,"bank_deposit",p_info[playerid][bank_deposit]);
    cache_get_value_name_int(0,"bank_deposit_limit_take",p_info[playerid][bank_deposit_limit_take]);
    cache_get_value_name_int(0,"bank_pension",p_info[playerid][bank_pension]);
    cache_get_value_name_int(0,"bank_pension_status",p_info[playerid][bank_pension_status]);
    cache_get_value_name_int(0,"spawn",p_info[playerid][spawn]);
    cache_get_value_name_int(0,"job",p_info[playerid][job]);

    if(p_info[playerid][job] != 0)
    {
        if(!(0 <= p_info[playerid][job] < MAX_JOBS)) p_info[playerid][job] = 0;
        Iter_Add(gJobPlayers[p_info[playerid][job]], playerid);
    }

    cache_get_value_name_int(0,"active_phone_id",p_info[playerid][active_phone_id]);
    cache_get_value_name_int(0,"phone_number",p_info[playerid][phone_number]);
    cache_get_value_name_int(0,"phone_balance",p_info[playerid][phone_balance]);
    cache_get_value_name_int(0,"ban",p_info[playerid][ban]);
    cache_get_value_name_int(0,"mute",p_info[playerid][mute]);
    if(p_info[playerid][mute] > 0) // VoiceChat_MutePlayer(playerid);

    cache_get_value_name_int(0,"rmute",p_info[playerid][rmute]);
    cache_get_value_name_int(0,"warn",p_info[playerid][warn]);
    cache_get_value_name_int(0,"jail_time",p_info[playerid][jail_time]);
    cache_get_value_name_int(0,"jail",p_info[playerid][jail]);

    //cache_get_value_name_float(0,"armour",p_info[playerid][pArmour]);
    //if(p_info[playerid][pArmour] > 0) SetPlayerArmour(playerid, p_info[playerid][pArmour]);
    cache_get_value_name_int(0,"wanted",p_info[playerid][wanted]);

    cache_get_value_name_int(0,"free_change_nick",p_info[playerid][free_change_nick]);
    cache_get_value_name_int(0,"d_demolition",p_info[playerid][d_demolition]);
    cache_get_value_name_int(0,"d_addiction",p_info[playerid][d_addiction]);
    cache_get_value_name_int(0,"p_game_time",p_info[playerid][p_game_time]);
    cache_get_value_name_int(0,"p_time_payday",p_info[playerid][p_time_payday]);
    cache_get_value_name_int(0,"p_time_today",p_info[playerid][p_time_today]);
    cache_get_value_name_int(0,"p_time_yesterday",p_info[playerid][p_time_yesterday]);
    cache_get_value_name_int(0,"p_afk_today",p_info[playerid][p_afk_today]);
    cache_get_value_name_int(0,"p_afk_yesterday",p_info[playerid][p_afk_yesterday]);

    cache_get_value_name_int(0,"check_active_time",p_info[playerid][check_active_time]);

    cache_get_value_name_int(0,"free_roulette_time",p_info[playerid][free_roulette_time]);

    cache_get_value_name_int(0,"gift_promocode_status",p_info[playerid][gift_promocode_status]);
    cache_get_value_name_int(0,"gift_promocode_time",p_info[playerid][gift_promocode_time]);

    #if EVENT_HALLOWEEN == 1
        cache_get_value_name_int(0, "halloween_id", p_info[playerid][halloween_id]);
        cache_get_value_name_int(0, "halloween_progress", p_info[playerid][halloween_progress]);
    #endif

    #if NEWYEAR_STATUS == 1
        cache_get_value_name_int(0, "event_quest_id", p_info[playerid][event_quest_id]);
        cache_get_value_name_int(0, "event_quest_stage", p_info[playerid][event_quest_stage]);
    #endif

    #if EASTER_STATUS == 1
        cache_get_value_name_int(0, "event_quest_id", p_info[playerid][event_quest_id]);
        cache_get_value_name_int(0, "event_quest_stage", p_info[playerid][event_quest_stage]);
    #endif

    cache_get_value_name_int(0,"ftop_unarrest",p_info[playerid][ftop_unarrest]);
    cache_get_value_name_int(0,"ftop_givepass",p_info[playerid][ftop_givepass]);
    cache_get_value_name_int(0,"ftop_selllawyerlic",p_info[playerid][ftop_selllawyerlic]);

    cache_get_value_name_int(0,"ftop_arrest",p_info[playerid][ftop_arrest]);
    cache_get_value_name_int(0,"ftop_unkpz",p_info[playerid][ftop_unkpz]);
    cache_get_value_name_int(0,"ftop_su",p_info[playerid][ftop_su]);
    cache_get_value_name_int(0,"ftop_unsu",p_info[playerid][ftop_unsu]);
    cache_get_value_name_int(0,"ftop_ticket",p_info[playerid][ftop_ticket]);
    cache_get_value_name_int(0,"ftop_frisk",p_info[playerid][ftop_frisk]);
    cache_get_value_name_int(0,"ftop_take",p_info[playerid][ftop_take]);
    cache_get_value_name_int(0,"ftop_sellgunlic",p_info[playerid][ftop_sellgunlic]);
    cache_get_value_name_int(0,"ftop_pkills",p_info[playerid][ftop_pkills]);

    cache_get_value_name_int(0,"ftop_aload_materials",p_info[playerid][ftop_aload_materials]);
    cache_get_value_name_int(0,"ftop_aunload_materials",p_info[playerid][ftop_aunload_materials]);
    cache_get_value_name_int(0,"ftop_akills",p_info[playerid][ftop_akills]);

    cache_get_value_name_int(0,"ftop_heal",p_info[playerid][ftop_heal]);
    cache_get_value_name_int(0,"ftop_heal_drugs",p_info[playerid][ftop_heal_drugs]);
    cache_get_value_name_int(0,"ftop_sex",p_info[playerid][ftop_sex]);
    cache_get_value_name_int(0,"ftop_medcard",p_info[playerid][ftop_medcard]);
    cache_get_value_name_int(0,"ftop_hload_medicines",p_info[playerid][ftop_hload_medicines]);
    cache_get_value_name_int(0,"ftop_hunload_medicines",p_info[playerid][ftop_hunload_medicines]);

    cache_get_value_name_int(0,"ftop_edit",p_info[playerid][ftop_edit]);

    cache_get_value_name_int(0,"ftop_rob_shop",p_info[playerid][ftop_rob_shop]);
    cache_get_value_name_int(0,"ftop_gload_drugs",p_info[playerid][ftop_gload_drugs]);
    cache_get_value_name_int(0,"ftop_gunload_drugs",p_info[playerid][ftop_gunload_drugs]);
    cache_get_value_name_int(0,"ftop_gload_materials",p_info[playerid][ftop_gload_materials]);
    cache_get_value_name_int(0,"ftop_gunload_materials",p_info[playerid][ftop_gunload_materials]);
    cache_get_value_name_int(0,"ftop_gkills",p_info[playerid][ftop_gkills]);
    cache_get_value_name_int(0,"ftop_gdeaths",p_info[playerid][ftop_gdeaths]);

    cache_get_value_name_int(0,"ftop_gkills_week",p_info[playerid][ftop_gkills_week]);
    cache_get_value_name_int(0,"ftop_gdeaths_week",p_info[playerid][ftop_gdeaths_week]);
    cache_get_value_name_float(0,"ftop_gdamagegive_week",p_info[playerid][ftop_gdamagegive_week]);
    cache_get_value_name_float(0,"ftop_gdamagetake_week",p_info[playerid][ftop_gdamagetake_week]);

    cache_get_value_name_int(0,"ftop_rob_bank",p_info[playerid][ftop_rob_bank]);
    cache_get_value_name_int(0,"ftop_mload_drugs",p_info[playerid][ftop_mload_drugs]);
    cache_get_value_name_int(0,"ftop_munload_drugs",p_info[playerid][ftop_munload_drugs]);
    cache_get_value_name_int(0,"ftop_mload_materials",p_info[playerid][ftop_mload_materials]);
    cache_get_value_name_int(0,"ftop_munload_materials",p_info[playerid][ftop_munload_materials]);
    cache_get_value_name_int(0,"ftop_mbkills",p_info[playerid][ftop_mbkills]);
    cache_get_value_name_int(0,"ftop_mbdeaths",p_info[playerid][ftop_mbdeaths]);

    cache_get_value_name_int(0,"ftop_selllic",p_info[playerid][ftop_selllic]);
    cache_get_value_name_int(0,"ftop_sellinsurance",p_info[playerid][ftop_sellinsurance]);

    cache_get_value_name_int(0,"ftop_bload_drugs",p_info[playerid][ftop_bload_drugs]);
    cache_get_value_name_int(0,"ftop_bunload_drugs",p_info[playerid][ftop_bunload_drugs]);
    cache_get_value_name_int(0,"ftop_bload_materials",p_info[playerid][ftop_bload_materials]);
    cache_get_value_name_int(0,"ftop_bunload_materials",p_info[playerid][ftop_bunload_materials]);

    cache_get_value_name_int(0,"p_limite_bank_count",p_info[playerid][p_limite_bank_count]);

    cache_get_value_name_float(0,"satiety",p_info[playerid][satiety]);
    cache_get_value_name_float(0,"thirst",p_info[playerid][thirst]);
    if(p_info[playerid][thirst] > 100.0) p_info[playerid][thirst] = 100.0;

    cache_get_value_name_int(0,"style_styde", p_info[playerid][style_styde]);
    cache_get_value_name_int(0,"style_progress", p_info[playerid][style_progress]);

    cache_get_value_name_int(0,"pick",p_info[playerid][pick]);

    cache_get_value_name_int(0,"active_skin_id",p_info[playerid][active_skin_id]); // TEMP
    cache_get_value_name_int(0,"gift_check",p_info[playerid][gift_check]);
    cache_get_value_name_int(0,"gift_idx",p_info[playerid][gift_idx]);
    cache_get_value_name_int(0,"gift",p_info[playerid][gift]);

    cache_get_value_name_int(0,"payday_oil_count",p_info[playerid][payday_oil_count]);

    new data[256];

    cache_get_value_name(0, "skins", data); // 0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[10]", p_info[playerid][skins]);

    cache_get_value_name(0, "Style", data); // 0|0|0|0
    sscanf(data, "p<|>a<i>[4]", p_info[playerid][pstyle]);

    cache_get_value_name(0, "Lic", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", p_info[playerid][Lic]);

    cache_get_value_name(0, "Lic_Warn", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", p_info[playerid][Lic_Warn]);

    cache_get_value_name(0, "Lic_Time", data); // 0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[9]", p_info[playerid][Lic_Time]);

    cache_get_value_name(0, "h_r_settings", data); // 0|0|0|0|0
    sscanf(data, "p<|>a<i>[2]", p_info[playerid][h_r_settings]);

    cache_get_value_name(0, "Weapon", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[13]", p_info[playerid][Weapon]);

    cache_get_value_name(0, "Ammo", data);   // 0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[13]", p_info[playerid][Ammo]);

    cache_get_value_name_bool(0, "fwork", p_info[playerid][fwork]);

    if(p_info[playerid][fwork] == true)
    {
        if( GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_PD ||
            GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_FBI)
            p_temp[playerid][StatusOnDuty] = 1;
    }

    cache_get_value_name_int(0, "paintball", p_info[playerid][paintball]);

    cache_get_value_name_int(0, "family_id", p_info[playerid][family_id]);
    //cache_get_value_name(0, "family_enter", p_info[playerid][family_enter], 16);
    cache_get_value_name_int(0, "family_rang", p_info[playerid][family_rang]);
    if(p_info[playerid][family_id] != -1 && p_info[playerid][family_rang] < 1) p_info[playerid][family_rang] = 1;

    cache_get_value_name_int(0, "family_mute", p_info[playerid][family_mute]);
    cache_get_value_name_int(0, "family_warn", p_info[playerid][family_warn]);
    cache_get_value_name_int(0, "family_exp", p_info[playerid][family_exp]);

    cache_get_value_name_int(0, "p_vip", p_info[playerid][p_vip]);
    cache_get_value_name_int(0, "p_vip_time", p_info[playerid][p_vip_time]);

    cache_get_value_name_int(0, "p_add_vip", p_info[playerid][p_add_vip]);
    cache_get_value_name_int(0, "p_add_vip_time", p_info[playerid][p_add_vip_time]);

    cache_get_value_name_int(0, "p_flin_music_free", p_info[playerid][p_flin_music_free]);
    cache_get_value_name_int(0, "p_flin_music", p_info[playerid][p_flin_music]);
    cache_get_value_name_int(0, "p_flin_music_time", p_info[playerid][p_flin_music_time]);

    cache_get_value_name_int(0, "checkdrug", p_info[playerid][checkdrug]);
    cache_get_value_name_int(0, "rob_time", p_info[playerid][rob_time]);

    cache_get_value_name_int(0, "news", p_info[playerid][news]);
    cache_get_value_name_int(0, "fwarn", p_info[playerid][fwarn]);
    cache_get_value_name_int(0, "warn_time", p_info[playerid][warn_time]);

    if(p_info[playerid][warn_time] != 0 && p_info[playerid][warn_time] < timestamp)
    {
        SendInfo(playerid, "Срок предупреждения на аккаунте истек.");
        p_info[playerid][warn] = 0;
        p_info[playerid][warn_time] = 0;
    }

    cache_get_value_name_int(0, "time_exit_game", p_info[playerid][time_exit_game]);
    cache_get_value_name_float(0, "spawn_x", p_info[playerid][spawn_pos_x]);
    cache_get_value_name_float(0, "spawn_y", p_info[playerid][spawn_pos_y]);
    cache_get_value_name_float(0, "spawn_z", p_info[playerid][spawn_pos_z]);
    cache_get_value_name_float(0, "spawn_r", p_info[playerid][spawn_pos_r]);
    cache_get_value_name_int(0, "lotto", p_info[playerid][lotto]);
    cache_get_value_name_int(0, "TaxiTime", p_info[playerid][TaxiTime]);
    cache_get_value_name(0, "partner", p_info[playerid][Partner], MAX_PLAYER_NAME);

    //cache_get_value_name_int(0,"taxi",p_info[playerid][]);
    cache_get_value_name_int(0,"taxi_idx",p_info[playerid][taxi_idx]);
    cache_get_value_name_int(0,"taxi_rank",p_info[playerid][taxi_rank]);
    cache_get_value_name_int(0,"taxi_percent",p_info[playerid][taxi_percent]);
    cache_get_value_name_int(0,"taxi_salary",p_info[playerid][taxi_salary]);
    cache_get_value_name_int(0,"taxi_salary_all",p_info[playerid][taxi_salary_all]);

    //cache_get_value_name_int(0,"tc",p_info[playerid][]);
    cache_get_value_name_int(0,"tc_idx",p_info[playerid][tc_idx]);
    cache_get_value_name_int(0,"tc_rank",p_info[playerid][tc_rank]);
    cache_get_value_name_int(0,"tc_percent",p_info[playerid][tc_percent]);
    cache_get_value_name_int(0,"tc_salary",p_info[playerid][tc_salary]);
    cache_get_value_name_int(0,"tc_salary_all",p_info[playerid][tc_salary_all]);

    cache_get_value_name_int(0,"mission_exp",p_info[playerid][mission_exp]);
    cache_get_value_name_int(0,"mission_days",p_info[playerid][mission_days]);

    cache_get_value_name_int(0,"freelance_lvl",p_info[playerid][freelance_lvl]);
    cache_get_value_name_int(0,"freelance_success",p_info[playerid][freelance_success]);
    cache_get_value_name_int(0,"freelance_money",p_info[playerid][freelance_money]);
    cache_get_value_name_int(0,"freelance_fm",p_info[playerid][freelance_fm]);

    cache_get_value_name_int(0,"battle_lvl",p_info[playerid][battle_lvl]);
    cache_get_value_name_int(0,"battle_lvl_task",p_info[playerid][battle_lvl_task]);

    cache_get_value_name(0, "battle_info", data); // 0|0|0|0|0
    sscanf(data, "p<|>a<i>[5]", p_info[playerid][battle_info]);
    cache_get_value_name(0, "battle_task", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[25]", p_info[playerid][battle_task]);
    cache_get_value_name(0, "battle_task_active", data); // 0|0|0|0|0
    sscanf(data, "p<|>a<i>[5]", p_info[playerid][battle_task_active]);

    cache_get_value_name_int(0,"daily_days",p_info[playerid][daily_days]);
    cache_get_value_name_int(0,"daily_time",p_info[playerid][daily_time]);
    cache_get_value_name_int(0,"daily_today",p_info[playerid][daily_today]);
    cache_get_value_name_int(0,"daily_update_reward",p_info[playerid][daily_update_reward]);

    cache_get_value_name(0, "p_settings", data);
    sscanf(data, "p<|>a<i>[32]", p_info[playerid][p_settings]);

    if(p_info[playerid][p_settings][STATUS_DAMAGE] != 0)
    {
        p_info[playerid][p_settings][STATUS_DAMAGE] = 0;
        UpdatePlayerSetting(playerid);
    }

    if(isPlayerMobile && p_info[playerid][p_settings][CROSSHAIR_ID] != 0)
    {
        STRING_GLOBAL[0] = EOS;
        f(STRING_GLOBAL, "crosshair_%d", p_info[playerid][p_settings][CROSSHAIR_ID]);
        SendChangeAim(playerid, STRING_GLOBAL);
    }


    if(GetPlayerGameVersion(playerid) >= CLIENT_VERSION_20022023) // УБРАТЬ 05.03
    {
        p_info[playerid][p_settings][REAL_SKINS] = 1;
        UpdatePlayerSetting(playerid);
    }
    
    cache_get_value_name(0, "Update", data); // 0|0|0|0
    sscanf(data, "p<|>a<i>[5]", p_info[playerid][Update]);

    cache_get_value_name(0, "DonateUpdate", data); // 0|0|0|0
    sscanf(data, "p<|>a<i>[4]", p_info[playerid][DonateUpdate]);

    cache_get_value_name(0, "quest", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[33]", p_info[playerid][quest]);

    cache_get_value_name(0, "mission", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[69]", p_info[playerid][mission]);

    cache_get_value_name(0, "achievement", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[31]", p_info[playerid][achievement]);

    cache_get_value_name(0, "achievement_progress", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[31]", p_info[playerid][achievement_progress]);

    cache_get_value_name(0, "fracdata", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[42]", p_info[playerid][fracdata]);

    cache_get_value_name(0, "job_skill_new", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[23]", p_info[playerid][job_skill]);

    cache_get_value_name(0, "job_skill_count_new", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[23]", p_info[playerid][job_skill_count]);

    cache_get_value_name(0, "job_skill_salary_new", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[23]", p_info[playerid][job_skill_salary]);

    cache_get_value_name(0, "costume", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[23]", p_info[playerid][costume]);

    cache_get_value_name(0, "costume_use", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[23]", p_info[playerid][costume_use]);

    cache_get_value_name(0, "disease", data); // 0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[6]", p_info[playerid][Disease]);

    cache_get_value_name(0, "veh_slots", data); // 0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[6]", p_info[playerid][veh_slots]);

    cache_get_value_name(0, "Weapon", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<|>a<i>[13]", p_info[playerid][Weapon]);

    cache_get_value_name(0, "roulette_items_bronze", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItems[playerid][0]);

    cache_get_value_name(0, "roulette_items_count_bronze", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItemsCount[playerid][0]);

    cache_get_value_name(0, "roulette_items_idx_bronze", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItemsIDx[playerid][0]);

    cache_get_value_name(0, "roulette_items_silver", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItems[playerid][1]);

    cache_get_value_name(0, "roulette_items_count_silver", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItemsCount[playerid][1]);

    cache_get_value_name(0, "roulette_items_idx_silver", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItemsIDx[playerid][1]);

    cache_get_value_name(0, "roulette_items_gold", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItems[playerid][2]);

    cache_get_value_name(0, "roulette_items_count_gold", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItemsCount[playerid][2]);

    cache_get_value_name(0, "roulette_items_idx_gold", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    sscanf(data, "p<,>a<i>[16]", RoulettePlayerItemsIDx[playerid][2]);

    cache_get_value_name_int(0, "bizz_slots", p_info[playerid][bizz_slots]);
    cache_get_value_name_int(0, "active_bizz_id", p_info[playerid][active_bizz_id]);

    cache_get_value_name_int(0, "house_slots", p_info[playerid][house_slots]);
    cache_get_value_name_int(0, "active_house_id", p_info[playerid][active_house_id]);
    cache_get_value_name_int(0, "spawn_house_id", p_info[playerid][spawn_house_id]);

    //cache_get_value_name_int(0, "skin_slots", p_info[playerid][skin_slots]);

    cache_get_value_name_int(0, "inv_slots", p_info[playerid][inv_slots]);

    cache_get_value_name_int(0, "med_insurance", p_info[playerid][med_insurance]);
    cache_get_value_name_int(0, "med_insurance_time", p_info[playerid][med_insurance_time]);

    cache_get_value_name_int(0, "billet_army", p_info[playerid][billet_army]);
    cache_get_value_name_int(0, "billet_cop", p_info[playerid][billet_cop]);
    cache_get_value_name_int(0, "billet_exp", p_info[playerid][billet_exp]);
    cache_get_value_name_int(0, "escape_limit", p_info[playerid][escape_limit]);
    cache_get_value_name_int(0, "commit_a_robbery", p_info[playerid][commit_a_robbery]);
    cache_get_value_name_int(0, "robbed", p_info[playerid][robbed]);

    cache_get_value_name(0, "pame_text", p_info[playerid][pame_text]);
    cache_get_value_name(0, "pame_time", p_info[playerid][pame_time]);

    cache_get_value_name_int(0, "casino_block", p_info[playerid][casino_block]);
    cache_get_value_name_int(0, "job_block", p_info[playerid][job_block]);

    cache_get_value_name_int(0, "block_theft_car_acc", p_info[playerid][block_theft_car_acc]);

    cache_get_value_name_int(0, "promocode_use", p_info[playerid][promocode_use]);
    cache_get_value_name_int(0, "promocode_create", p_info[playerid][promocode_create]);
    cache_get_value_name_int(0, "promocode_donate", p_info[playerid][promocode_donate]);
    cache_get_value_name_int(0, "promocode_prize", p_info[playerid][promocode_prize]);

    cache_get_value_name_int(0, "bitcoin", p_info[playerid][bitcoin]);

    for(new i; i < 6; i++)
    {
        if(p_info[playerid][Disease][i] > 3) p_info[playerid][Disease][i] = 3;
    }

    p_temp[playerid][LoggedTime] = -1;

    p_info[playerid][loggedIn] = 1;

    if(isPlayerMobile)
    {
        if(p_info[playerid][level] < 5)
        {
            // VoiceChat_MutePlayer(playerid);
            SendInfo(playerid, "У Вас уровень меньше 5, голосовой чат для Вас отключен.");
        }
        p_info[playerid][online] = 1;
    }
    else p_info[playerid][online] = 2;

    new year,month,day;
    getdate(year, month, day);
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `online` = %d, `lastenter` = '%02d/%02d/%04d', `lastip` = '%e', `lastUID` = '%e' WHERE `id` = %d",
        p_info[playerid][online], day, month, year, p_temp[playerid][session_IP], p_temp[playerid][session_UID], p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL);

    if(p_info[playerid][referralmoney] != 0)
    {
        SetPlayerMoney(playerid, p_info[playerid][referralmoney], true, "пригласил друга");
        SendInfo(playerid, "Вы получили %d$ за приглашение друзей. Приглашений за всё время: %d.", p_info[playerid][referralmoney], p_info[playerid][referralcount]);
        p_info[playerid][referralmoney] = 0;
        MysqlUpdatePlayerInt(playerid, "referralmoney", p_info[playerid][referralmoney]);
    }

    CheckPlayerRouletteItems(playerid);

    if(p_info[playerid][Update][4] == 1)
    {
        p_info[playerid][Update][4] = 0;
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%i|%i|%i|%i|%i",
        p_info[playerid][Update][0], p_info[playerid][Update][1], p_info[playerid][Update][2], p_info[playerid][Update][3], p_info[playerid][Update][4]);
        MysqlUpdatePlayerStr(playerid, "Update", STRING_GLOBAL);
    }

    if(p_info[playerid][Update][1] == 1 || p_info[playerid][Update][1] == 2)
    {
        p_info[playerid][Update][1] = 0;
        STRING_GLOBAL[0] = EOS;
        format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%i|%i|%i|%i|%i",
        p_info[playerid][Update][0], p_info[playerid][Update][1], p_info[playerid][Update][2], p_info[playerid][Update][3], p_info[playerid][Update][4]);
        MysqlUpdatePlayerStr(playerid, "Update", STRING_GLOBAL);
    }
    /*
    if(p_info[playerid][skin_slots] > 3)
    {
        p_info[playerid][skin_slots] = 3;
        MysqlUpdatePlayerInt(playerid, "skin_slots", p_info[playerid][skin_slots]);
    }
    */
    if(p_info[playerid][active_phone_id] != 0 && p_info[playerid][active_phone_id] < 674)
    {
        p_info[playerid][active_phone_id] = p_info[playerid][active_phone_id] + 674;
        MysqlUpdatePlayerInt(playerid, "active_phone_id", p_info[playerid][active_phone_id]);
    }

    if(p_temp[playerid][premiumgamer] == PREMIUM_GAME) SetPlayerName(playerid, get_name(playerid));

    if(p_info[playerid][member] == 0 && p_info[playerid][fwork] != false) p_info[playerid][fwork] = false;

    if(GetFactionCategory(p_info[playerid][member]) == FACTION_CATEGORY_ARMY && p_info[playerid][rang] < 3)
    {
        p_info[playerid][fwork] = true;
        p_info[playerid][spawn] = SPAWN_FRACTION;
    }
    if(gang(playerid) || mafia(playerid) || biker(playerid)) p_info[playerid][fwork] = true;
    MysqlUpdatePlayerInt(playerid, "fwork", _:p_info[playerid][fwork]);

    if(strlen(p_info[playerid][google_code]) < 5)
        SendMes(playerid, COLOR_DARKORANGE, "Для безопасности рекомендуем настроить Google Authenticator. Подробнее: "W"/mm > Настройки > Настройки аккаунта > Google Authenticator");
    
    //if(vk_confirmed(playerid))
    //    SendMes(playerid, COLOR_DARKORANGE, "Для безопасности рекомендуем настроить Google Authenticator. Подробнее: "W"/mm > Настройки > Настройки аккаунта > Google Authenticator");
    
    if(p_info[playerid][p_vip] != 0 && p_info[playerid][p_vip_time] < timestamp)
    {
        SendInfo(playerid, "Срок использования VIP-аккаунта истек.");
        p_info[playerid][p_vip] = 0;
        p_info[playerid][p_vip_time] = 0;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `p_vip` = %d, `p_vip_time` = %d WHERE `id` = %d",
        p_info[playerid][p_vip], p_info[playerid][p_vip_time], p_info[playerid][ID]);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }

    if(p_info[playerid][p_add_vip] != 0 && p_info[playerid][p_add_vip_time] < timestamp)
    {
        SendInfo(playerid, "Срок использования ADD VIP истек.");
        p_info[playerid][p_add_vip] = 0;
        p_info[playerid][p_add_vip_time] = 0;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `p_add_vip` = %d, `p_add_vip_time` = %d WHERE `id` = %d",
        p_info[playerid][p_add_vip], p_info[playerid][p_add_vip_time], p_info[playerid][ID]);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }

    if(p_info[playerid][p_flin_music] != 0 && p_info[playerid][p_flin_music_time] < timestamp)
    {
        SendInfo(playerid, "Срок использования музыкальной подписки истек.");
        p_info[playerid][p_flin_music] = 0;
        p_info[playerid][p_flin_music_time] = 0;

        STRING_GLOBAL[0] = EOS;
        mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "UPDATE `accounts` SET `p_flin_music` = %d, `p_flin_music_time` = %d WHERE `id` = %d",
        p_info[playerid][p_flin_music], p_info[playerid][p_flin_music_time], p_info[playerid][ID]);
        mysql_tquery(con_bd, STRING_GLOBAL);
    }

    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `fraction_blacklist` WHERE `f_bl_target_id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "load_fraction_blacklist", "i", playerid);

    if(p_info[playerid][level] <= 0) p_info[playerid][level] = 1;
    if(p_temp[playerid][LoginFix] == 1)
    {
        p_temp[playerid][LoginFix] = 0;
        p_temp[playerid][LoginTimerFix] = 0;
    }

    if(p_info[playerid][ban] > timestamp)
    {
        SendInfo(playerid, "Ваш аккаунт заблокирован.");
        SendInfo(playerid, "Разблокировка через %d дней.", (p_info[playerid][ban]-timestamp)/84600);
        Kick(playerid);
        return 1;
    }
    SetPlayerScore(playerid,p_info[playerid][level]);

    SendMes(playerid, COLOR_BLUE, "Вы авторизовались.");
    p_info[playerid][pHealth] = 99.0;
    SetPlayerHealth(playerid, p_info[playerid][pHealth]);

    SetPlayerWantedLevel(playerid, p_info[playerid][wanted]);
    SendMes(playerid, COLOR_LIME, "Загрузить или выгрузить транспортное средство: {"#cLYELLOW"}/cars");
    SendMes(playerid, COLOR_LIME, "Меню персонажа, квесты, награды, мероприятия и достижения: {"#cLYELLOW"}/menu");

    if( p_info[playerid][battle_task_active][0] == 0 &&
        p_info[playerid][battle_task_active][1] == 0 &&
        p_info[playerid][battle_task_active][2] == 0 &&
        p_info[playerid][battle_task_active][3] == 0 &&
        p_info[playerid][battle_task_active][4] == 0) UpdatePlayerBattlePassTask(playerid);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `battlepass_reward` WHERE `user_id` = '%d'",
    p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerLoadBattlePass", "i", playerid);

    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT * FROM `daily_reward` WHERE `user_id` = '%d'",
    p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerLoadDaily", "i", playerid);

    if(p_info[playerid][level] <= 3 && ServerInfo[Experian] < 2)
    {
        SendMes(playerid, COLOR_GREEN, "На сервере включена акция для новичков:");
        SendMes(playerid, COLOR_GREEN, "За один час игры на сервере выдается "W"2{"#cGREEN"} очка опыта.");
    }

    GetPlayerAllHouse(playerid);
    GetPlayerAllBizz(playerid);
    GetPlayerHouseRent(playerid);
    GetPlayerHotel(playerid);

    if(p_info[playerid][time_exit_game]+600 > timestamp &&
        (p_info[playerid][spawn_pos_x] != 0.0 &&
        p_info[playerid][spawn_pos_y] != 0.0) &&
        p_info[playerid][spawn_pos_z] < 500.0)
    {
        ShowPlayerDialog(playerid, D_EXIT_SPAWN, DIALOG_STYLE_MSGBOX, ""I"Где появиться?",
            ""W"Перерыв с момента Вашей последней игровой сессией менее "I"10 "W"минут!\n\n"W"Хотите появиться где вышли(вылетело) ?", "Да", "Нет");
    }
    else 
        SpawnPlayer(playerid);
    
    if(isPlayerMobile && GetPlayerGameVersion(playerid) < CLIENT_VERSION_022023)
    {
        SendMes(playerid, COLOR_LIGHTRED, "На сервере "W"обновлён клиент{"#cLIGHTRED"}, скачать последнию версию вы можете на сайте: "W""SITE_URL"");
        SendMes(playerid, COLOR_LIGHTRED, "Для полной работоспособности всех новых возможностей необходимо обновить клиент, но вначале ЛАУНЧЕР.");
    }
    if(!isPlayerMobile && GetPlayerGameVersion(playerid) < CLIENT_VERSION_112022 && p_info[playerid][p_settings][INTERFACE])
    {
        p_info[playerid][p_settings][INTERFACE] = 0;
        p_info[playerid][p_settings][LOGO_ID] = 0;
        UpdatePlayerSetting(playerid);
    }

     #if OFF_HUD_PC == 0
    Logotype_Show(playerid);
    Logotype_Time(playerid);
    #endif

    GetPlayerFreelance(playerid);
    GetPlayerRobberyHouse(playerid);
    GetPlayerRobberyBank(playerid);
    GetPlayerRobberyFuel(playerid);

    new family_idx = GetPlayerFamilyID(playerid);
    if(family_idx != -1)
    {
        if(FamilyData[family_idx][fOwnerID] == p_info[playerid][ID] && p_info[playerid][family_rang] != MAX_FAMILY_RANG)
            p_info[playerid][family_rang] = MAX_FAMILY_RANG;
        UpdateFamilyLabel(playerid, true);

        new i = GetSlotFamilyCapture(family_idx, -1);
        if(i != -1)
        {
            new family_zoneid = fCapture_Info[i][fFamilyZoneID];
            if(family_zoneid != INVALID_CRIMINAL_ZONE_ID)
            {
                new idx = fCapture_Info[i][fFamilyID][0];

                GangZoneFlashForPlayer(playerid, FamilyZone_Info[family_zoneid][fID], (FAMILY_COLORS[FamilyData[idx][fColorID]] & 0xFFFFFF00 | 0x65));
                ShowTextDrawForPlayer(playerid, TD_ID_CAPTURE);
                CaptureInfoUpdate(playerid, CAPTURE_ID_FAMILY, i);
                SetPlayerColor(playerid, FAMILY_COLORS[FamilyData[family_idx][fColorID]]);
            }
        }
    }
    if(strlen(p_info[playerid][pame_text])) PlayerPame_Update(playerid, true);

    new string[144];
    format(string,144,"~b~WELCOME~n~~w~%s",get_name(playerid));
    GameTextForPlayer(playerid,string,3000,1);

    //p_temp[playerid][session_IP][0] = EOS;
    //GetPlayerIp(playerid, p_temp[playerid][session_IP], 16);

    for(new i; i < 6; i++)
    {
        if(p_info[playerid][Disease][i] > 3) p_info[playerid][Disease][i] = 3;
    }

    PreloadAllAnims(playerid); // Загружаем анимации;
    if(gang(playerid))
    {
        if(Capture_Info[0][gGangZoneID] != INVALID_CRIMINAL_ZONE_ID || Capture_Info[1][gGangZoneID] != INVALID_CRIMINAL_ZONE_ID)
        {
            if(Capture_Info[0][gFaction][0] == p_info[playerid][member] || Capture_Info[0][gFaction][1] == p_info[playerid][member])
            {
                GangZoneFlashForPlayer(playerid, GangZone_Info[Capture_Info[0][gGangZoneID]][gID], fraction_color[Capture_Info[0][gFaction][0]]);
                PlayerFixZone[playerid] = 1;
            }
            if(Capture_Info[1][gFaction][0] == p_info[playerid][member] || Capture_Info[1][gFaction][1] == p_info[playerid][member])
            {
                GangZoneFlashForPlayer(playerid, GangZone_Info[Capture_Info[1][gGangZoneID]][gID], fraction_color[Capture_Info[1][gFaction][0]]);
                PlayerFixZone[playerid] = 2;
            }
            if(PlayerFixZone[playerid] != 0)
            {
                ShowTextDrawForPlayer(playerid, TD_ID_CAPTURE);
                CaptureInfoUpdate(playerid, CAPTURE_ID_GANG, PlayerFixZone[playerid]-1);
            }
        }
    }
    if(mafia(playerid) || biker(playerid))
    {
        if(BizWar_Info[bWarTime] > 0)
        {
            if(BizWar_Info[bMafia][0] == p_info[playerid][member] || BizWar_Info[bMafia][1] == p_info[playerid][member])
            {
                ShowTextDrawForPlayer(playerid, TD_ID_CAPTURE);
                CaptureInfoUpdate(playerid, CAPTURE_ID_MAFIA);
            }
        }
    }

    if(gang(playerid) || mafia(playerid) || biker(playerid))
    {
        if(AirDropIDx != -1 && AirDropZone != -1)
        {
            GangZoneShowForPlayer(playerid, AirDropZone, 0xFFFFFF65);
            GangZoneFlashForPlayer(playerid, AirDropZone, COLOR_RED);
        }
    }

    if(gang(playerid) || mafia(playerid) || biker(playerid) || army(playerid))
    {
        if(WarPlaneIDx != -1 && WarPlaneZone != -1)
        {
            GangZoneShowForPlayer(playerid, WarPlaneZone, 0xFFFFFF65);
            GangZoneFlashForPlayer(playerid, WarPlaneZone, COLOR_RED);
        }
    }

    LoadPlayerBinder(playerid);
    LoadPlayerNotification(playerid);
    /*
    SendMes(playerid, COLOR_LIGHTRED, "За каждые 3 часа игры выдается "W"Bronze{"#cLIGHTRED"} рулетка, но есть вероятность выдачи "W"Silver{"#cLIGHTRED"} и "W"Gold{"#cLIGHTRED"} рулетки.");
    SendMes(playerid, COLOR_LIGHTRED, "Чтобы приобрести рулетку или воспользоваться ей, используйте: "W"/mn > [15] Рулетка");
    */

    /*
    SendMes(playerid, COLOR_LIGHTRED, "Для Вас доступны квесты, задания, достижения и награды. Подробнее: "W"/mission");
    SendMes(playerid, COLOR_LIGHTRED, "Зарабатывайте до "W"100 Flin Money{"#cLIGHTRED"} и "W"500.000${"#cLIGHTRED"} за выполнение ежедневных заданий.");
    SendMes(playerid, COLOR_LIGHTRED, "Зарабатывайте до "W"21000 Flin Money{"#cLIGHTRED"} и "W"5.000.000${"#cLIGHTRED"} за выполнение достижений.");
    */

    if(ServerInfo[Experian] > 1) Action_Show(playerid);

    for(new i = 6; i != -1; i--)
    {
        if(i == 5) TogglePlayerHudElement(playerid, i+1, p_info[playerid][p_settings][i+18]);
        else TogglePlayerHudElement(playerid, i, p_info[playerid][p_settings][i+18]);
    }
    SetTimeoutChatDissappearTime(playerid, p_info[playerid][p_settings][ELEMENT_CHAT_OUTTIME], p_info[playerid][p_settings][ELEMENT_CHAT_OUTTIME]);

    new nick_name[MAX_PLAYER_NAME];
    f(nick_name, "%s%s%s", get_name(playerid), isPlayerMobile ? "" : "[PC]");
    SetPlayerName(playerid, nick_name);

    SetTimerEx("WarningErrorFiles", 5000, false, "i", playerid);

    if(!p_info[playerid][p_settings][PACIFIST_MODE])
    {
        if(!p_info[playerid][member] && p_info[playerid][level] < 3) {
            PacifistModeToggle(playerid, 1);
            SendInfo(playerid, "Вам автоматически включен пацифист режим. Подробней: /pacifistinfo.");
        }
        else SendInfo(playerid, "У вас выключен пацифист режим. Подробней: /pacifistinfo.");
    }
    else
    {
        if(GetFactionType(p_info[playerid][member]) == FACTION_TYPE_CRIMINAL)
            PacifistModeToggle(playerid, 0);
    }

    if(p_info[playerid][p_flin_music] == 0)
    {
        SendMes(playerid, COLOR_LIGHTRED, "[ПОДПИСКА НА МУЗЫКУ]: "W"Flin Music дает вам мгновенный доступ к тысячам песен — от старых фаворитов до последних хитов.");
        SendMes(playerid, COLOR_LIGHTRED, "[ПОДПИСКА НА МУЗЫКУ]: "W"Подробнее: {"#cLIGHTRED"}/play & /music & /radio");
    }

    /*
    SendMes(playerid, COLOR_LIGHTRED, "[ОБНОВЛЕНИЕ]: "W"На сервере вышло обновление за 19.09.2022. Подробнее: {"#cLIGHTRED"}"VK_URL"");
    SendMes(playerid, COLOR_LIGHTRED, "[BATTLE PASS]: "W"Стартовал осенний сезон Battle Pass. Подробнее: {"#cLIGHTRED"}/bp");
    SendMes(playerid, COLOR_LIGHTRED, "[ОБНОВЛЕНИЕ]: "W"На сервере вышла вторая часть летнего обновления. Подробнее: {"#cLIGHTRED"}vk.com/flin_rp");
    SendMes(playerid, COLOR_LIGHTRED, "[НОВЫЙ BATTLE PASS]: "W"Мы обновили Battle Pass. Подробнее: {"#cLIGHTRED"}/bp");
    SendMes(playerid, COLOR_LIGHTRED, "[НОВЫЕ ЕЖЕДНЕВНЫЕ НАГРАДЫ]: "W"Мы обновили ежедневные награды. Подробнее: {"#cLIGHTRED"}/daily");
    SendMes(playerid, COLOR_LIGHTRED, "[АКЦИЯ]: "W"50%% скидка на Battle Pass Premium. Приобрести: {"#cLIGHTRED"}/bp");
    SendMes(playerid, COLOR_LIGHTRED, "[АКЦИЯ]: "W"Стоимость некоторых товаров снижена в два раза. Подробнее: {"#cLIGHTRED"}/donate");
    */
    #if NEWYEAR_STATUS == 1
        SendMes(playerid, COLOR_LIGHTRED, "[НОВЫЙ ГОД]: "W"До 15 января на серверах проходит празднование {"#cLIGHTRED"}Нового года."W" Подробнее: {"#cLIGHTRED"}/gift");
        if(p_info[playerid][event_quest_stage] != 9)
        {
            SendMes(playerid, COLOR_LIGHTRED, "[КВЕСТ]: "W"На {"#cLIGHTRED"}праздничной площади"W" можно пройти {"#cLIGHTRED"}тематический квест.");
            SendMes(playerid, COLOR_LIGHTRED, "[КВЕСТ]: "W"Награда за прохождение тематического квеста: {"#cLIGHTRED"}300.000$, 300 Flin Money и уникальный аксессуар \"Новогодняя шапка\".");
        }
    #endif

    #if EVENT_HALLOWEEN == 1
        if(p_info[playerid][halloween_id] != MAX_HALLOWEEN_QUEST_ID + 1)
        {
            SendMes(playerid, COLOR_LIGHTRED, "[КВЕСТ]: "W"На {"#cLIGHTRED"}праздничной площади"W" можно пройти {"#cLIGHTRED"}тематический квест.");
            SendMes(playerid, COLOR_LIGHTRED, "[КВЕСТ]: "W"Награда за прохождение тематического квеста: {"#cLIGHTRED"}350.000$, 150 Flin Money и уникальный аксессуар \"Маска демона\".");
        }
    #endif

    #if EASTER_STATUS == 1
        if(p_info[playerid][event_quest_stage] != MAX_EVENT_QUEST)
        {
            SendMes(playerid, COLOR_LIGHTRED, "[КВЕСТ]: "W"На {"#cLIGHTRED"}праздничной площади"W" можно пройти {"#cLIGHTRED"}тематический квест."); // 580 - 584 item_Id
            SendMes(playerid, COLOR_LIGHTRED, "[КВЕСТ]: "W"Награда за прохождение тематического квеста: {"#cLIGHTRED"}1.500.000$, 700 Flin Money и уникальный аксессуар \"Пасхальное яйцо\".");
        }
        SendMes(playerid, COLOR_LIGHTRED, "[ПАСХА]: Уникальная возможность поиграть в битьё яиц  с другими игроками (( /eggs ))."); // 580 - 584 item_Id
    #endif

    #if ACTION_100_HOUR == 1
    if(p_info[playerid][level] >= 5 && p_info[playerid][gift_promocode_status] == 0 && p_info[playerid][gift_promocode_time] < 360000)
    {
        SendMes(playerid, COLOR_LIGHTRED, "За 100 часов игры выдается "W"Silver VIP на 14 дней и Nissan 370Z (RealCars){"#cLIGHTRED"} Отыграно: "W"%s.", ConvertTime(p_info[playerid][gift_promocode_time]));
    }
    #endif

    new idx = ServerInfo[DonationMultiplier];
    if(idx != 1)
    {
        SendMes(playerid, COLOR_LIGHTRED, "[X%d ДОНАТ]: "W"Действует {"#cLIGHTRED"}« Акция X%d »."W" Все зачисления {"#cLIGHTRED"}%s.", idx, idx, idx == 2 ? "удваиваются" : idx == 3 ? "утраиваются" : "умножаются на четыре");
        //SendMes(playerid, COLOR_LIGHTRED, "[АКЦИИ]: "W"Успей воспользоваться данным предложением. Приобрести: {"#cLIGHTRED"}/donate");
        //SendMes(playerid, COLOR_LIGHTRED, "[ВЕСЕННЯЯ РАСПРОДАЖА]:"W" До конца понедельника на все товары из магазина {"#cLIGHTRED"}« Скидка 25%% ».");
    }

    SendMes(playerid, COLOR_LIGHTRED, "Теперь новости проекта напрямую в игре. Подробнее: "W"/snews");

    Log(LOG_player, INFO, "%s[%d](%s %s) авторизовался на сервере", get_name(playerid), p_info[playerid][ID], p_temp[playerid][session_IP], isPlayerMobile ? "Mobile": "PC");

    if(p_temp[playerid][premiumgamer] == PREMIUM_GAME && p_info[playerid][phone_number] == 0 && p_info[playerid][level] >= 2)
    {
        if(!GivePlayerInventory(playerid, 674, 1)) return 1;
        p_info[playerid][phone_number] = RandomEx(100000,999999);
        MysqlUpdatePlayerInt(playerid, "phone_number", p_info[playerid][phone_number]);
        p_info[playerid][active_phone_id] = 674;
        MysqlUpdatePlayerInt(playerid, "active_phone_id", p_info[playerid][active_phone_id]);
    }
    return 1;
}

forward FindPlayerAccount(playerid, player_port, player_IP[]);
public FindPlayerAccount(playerid, player_port, player_IP[])
{
    if(player_port != p_temp[playerid][session_PORT] || !strequals(p_temp[playerid][session_IP], player_IP))
        return 1;

    new rows = cache_num_rows();
    if(!rows) return dialog_reg(playerid,2);
    else
    {
        new nick_name[MAX_PLAYER_NAME];
        f(nick_name, "LOGIN_USER_ID_%d", playerid);
        SetPlayerName(playerid, nick_name);

        cache_get_value_name_int(0, "id",           p_info[playerid][ID]);
        cache_get_value_name(0, "password",         p_info[playerid][password], 128);
        cache_get_value_name(0, "google_code",      p_info[playerid][google_code], 30);
        cache_get_value_name_int(0, "google_auth",  p_info[playerid][google_auth]);
        cache_get_value_name_int(0, "vk_userid",    p_info[playerid][vk_userid]);
        cache_get_value_name_int(0, "vk_confirmed", p_info[playerid][vk_confirmed]);
        cache_get_value_name_int(0, "vk_auth",      p_info[playerid][vk_auth]);
        cache_get_value_name_int(0, "tg_userid",    p_info[playerid][tg_userid]);
        cache_get_value_name_int(0, "tg_confirmed", p_info[playerid][tg_confirmed]);
        cache_get_value_name_int(0, "tg_auth",      p_info[playerid][tg_auth]);
        cache_get_value_name(0, "lastip",           p_info[playerid][lastIP], MAX_IP_LENGTH);
        cache_get_value_name_int(0, "usepassword",  p_info[playerid][user_active]);
        cache_get_value_name_int(0, "sex",          p_info[playerid][sex]);
        cache_get_value_name_int(0,"member",        p_info[playerid][member]);
        cache_get_value_name_bool(0, "fwork",       p_info[playerid][fwork]);
        cache_get_value_name_int(0,"fskin",         p_info[playerid][fskin]);
        cache_get_value_name_int(0, "inv_slots",    p_info[playerid][inv_slots]);
        cache_get_value_name_int(0, "family_id",    p_info[playerid][family_id]);
        cache_get_value_name_int(0, "family_rang",  p_info[playerid][family_rang]);
        cache_get_value_name(0, "lastUID",          p_info[playerid][lastUID], 64);
        
        new data[256];
        cache_get_value_name(0, "costume", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
        sscanf(data, "p<|>a<i>[23]", p_info[playerid][costume]);

        cache_get_value_name(0, "costume_use", data); // 0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
        sscanf(data, "p<|>a<i>[23]", p_info[playerid][costume_use]);

        if(strequals(p_info[playerid][lastUID], p_temp[playerid][session_UID]) && 
            strequals(p_info[playerid][lastIP], p_temp[playerid][session_IP]) &&
            ServerInfo[AutoLoginUID])
        {
            LoadPlayerAccount(playerid);
            SendInfo(playerid, "Авторизаци произошла автоматически, последнее авторизированное устройство совпадает с текущем.");
        }
        else
        {
            p_temp[playerid][LoggedTime] = timestamp + 120;
            p_info[playerid][loggedIn] = 0;
            dialog_reg(playerid,1); //диалог входа
        }

        LoadPlayerFamilyID(playerid);
        LoadPlayerInventory(playerid);
    }
    return 1;
}

SetPlayerValuesToDefault(playerid)
{
    p_temp[playerid][GM_MODE_Time] = 0;

    DI_OnPlayerConnect(playerid);

    p_temp[playerid][Work_ID] = NONE_WORK;
    p_temp[playerid][session_UID][0] = EOS;

    p_temp[playerid][pos_X] =
    p_temp[playerid][pos_Y] =
    p_temp[playerid][pos_Z] = 0.0;

    p_temp[playerid][sitdown_id] =
    p_temp[playerid][sitdown_place] = -1;
    p_temp[playerid][gm_mode] = false;

    ClearAllPlayerBlackjackData(playerid);
    playerDialogID[playerid] = -1;
    MdcInfo[playerid][mdcCreated] = 0;

    for(new i = 0; i < 2; i++) p_temp[playerid][donate_parameter][i] = -1;

    ClearInfoPlayerAirBalloon(playerid);

    //p_temp[playerid][donate_antiflood] = false;
    p_temp[playerid][city_id] = 0;
    p_temp[playerid][dead_status] = false;
    p_temp[playerid][dead_acc_wear] = 0;
    p_temp[playerid][dead_skin_wear] = 0;

    p_temp[playerid][CriminalZoneID] = INVALID_CRIMINAL_ZONE_ID;
    p_temp[playerid][pacifist_time] = 0;
    p_temp[playerid][bonfire_label] = INVALID_3DTEXT_ID;
    p_temp[playerid][bonfire_object] = INVALID_OBJECT_ID;
    p_temp[playerid][bonfire_timer] = 0;

    p_temp[playerid][camera_id] = 0;
    p_temp[playerid][camera_angle] = 0.0;
    p_temp[playerid][InterfaceID] = INTARFACE_ID_NONE;
    p_temp[playerid][InterfacePage] = 0;
    p_temp[playerid][SparringID] = -1;
    //p_temp[playerid][TruckTrailer] = INVALID_VEHICLE_ID;

    p_temp[playerid][tc_call_idx] = 0;
    p_temp[playerid][tc_call_type] = 0;

    p_temp[playerid][anti_dm_oldtargetid] = INVALID_PLAYER_ID;
    p_temp[playerid][anti_dm_count] = 0;
    p_temp[playerid][avto_dm_check] = true;

    p_temp[playerid][AntiFloodCMD] =
    p_temp[playerid][random_code] = 0;
    //if(IsPlayerMobile(playerid)) SendClientCheck(playerid, 0x48, 0, 0, 2);

    ClearPlayerDamage(playerid);

    p_temp[playerid][OldPickupID] =
    p_temp[playerid][EventPickupID] = -1;
    p_temp[playerid][PickupPosX] =
    p_temp[playerid][PickupPosY] =
    p_temp[playerid][PickupPosZ] = 0.0;
    p_temp[playerid][TickPickup] = 0;

    p_temp[playerid][MDC_BODYCAM] = INVALID_PLAYER_ID;
    p_temp[playerid][pCCTV] =
    p_temp[playerid][StatusOnDuty] =
    p_temp[playerid][pPatrol] =
    p_temp[playerid][pPoliceCalls] =
    p_temp[playerid][pPoliceJails] =
    p_temp[playerid][pPoliceFines] = 0;

    p_temp[playerid][chase_followerId] =
    p_temp[playerid][chase_targetId] = INVALID_PLAYER_ID;

    p_temp[playerid][TextDrawCaptcha] = 0;
    p_temp[playerid][ATM_STATUS] = false;
    p_temp[playerid][market_vehicle_id] = -1;
    p_info[playerid][billet_exp] =
    p_info[playerid][billet_army] =
    p_info[playerid][billet_cop] = 0;

    for(new i = MAX_PLAYER_VEHICLES-1; i != -1; i--) p_info[playerid][key_vehicle][i] = INVALID_VEHICLE_ID;

    p_info[playerid][pfreeze] = 0;

    p_temp[playerid][death_status] = 0;
    p_temp[playerid][death_timer] = 0;
    p_temp[playerid][death_anim] = 0;
    for(new i = 0; i < 4; i++) p_temp[playerid][death_pos][i] = 0.0;

    SetPVarInt(playerid,"Ved", INVALID_PLAYER_ID);
    p_temp[playerid][music_object] = INVALID_OBJECT_ID;
    p_temp[playerid][music_area] = -1;
    p_temp[playerid][music_label] = INVALID_3DTEXT_ID;

    p_temp[playerid][army_post] = -1;
    p_temp[playerid][army_time] = 0;

    //p_temp[playerid][rappelling] =
    p_temp[playerid][green_zone] = -1;

    p_info[playerid][durak_table] =
    p_info[playerid][durak_index] =
    p_info[playerid][durak_bet] =
    p_info[playerid][durak_deckSize] =
    p_info[playerid][durak_selectIndex] = 0;
    p_info[playerid][durak_ready] =
    p_info[playerid][durak_beaten] =
    p_info[playerid][durak_allowTake] = false;
    p_info[playerid][durak_deck][0] = EOS;

    p_info[playerid][p_settings][STATUS_WALK_STYLE] =
    p_info[playerid][p_settings][WALK_STYLE_ID] = 0;
    p_temp[playerid][walk_time] = -1;
    ///////////////////////////
    //p_temp[playerid][tl_id] = -1;
    //
    for(new i = 99; i != -1; i--) p_temp[playerid][p_listitem][i] = -1;

    for(new i = MAX_SERVER_WORK-1; i != -1; i--)
    {
        p_info[playerid][job_skill][i] = 1;
        p_info[playerid][job_skill_count][i] = 0;
    }

    for(new i; i != MAX_COSTUME; i++)
    {
        p_info[playerid][costume][i] = 0;
        p_info[playerid][costume_use][i] = 0;
    }
    p_info[playerid][med_insurance_time] =
    p_info[playerid][med_insurance] = 0;

    if(RouletteTimerIDx[playerid] != 0 || IsValidTimer(RouletteTimerIDx[playerid])) KillTimer(RouletteTimerIDx[playerid]);
    if(CaseTimerIDx[playerid] != 0 || IsValidTimer(CaseTimerIDx[playerid])) KillTimer(CaseTimerIDx[playerid]);

    for(new i; i < 6; i++) p_info[playerid][Disease][i] = 0;
    for(new i; i < MAX_OFFER_PLAYER; i++) ClearOwnerOffer(playerid, GetPlayerOfferID(playerid, i));
    p_temp[playerid][offer_info][0] = INVALID_PLAYER_ID;
    p_temp[playerid][offer_info][1] =
    p_temp[playerid][offer_info][2] =
    p_temp[playerid][offer_info][3] =
    p_temp[playerid][offer_info][4] = 0;

    p_temp[playerid][is_check_mobile] = 0;

    DriveAuto[playerid] = INVALID_VEHICLE_ID;
    DriveTime[playerid] = -1;

    p_temp[playerid][dice_targetid] = INVALID_PLAYER_ID;
    p_temp[playerid][dice_response] =
    p_temp[playerid][dice_money] =
    p_temp[playerid][dice_timer] = 0;

    p_temp[playerid][aggs_targetid] = INVALID_PLAYER_ID;
    p_temp[playerid][aggs_response] =
    p_temp[playerid][aggs_count] = 0;

    p_temp[playerid][fix_flood] = INVALID_PLAYER_ID;
    p_temp[playerid][taxi_zp] = 0.0;
    p_temp[playerid][taxi_enter] = 0;
    p_temp[playerid][calling] = INVALID_PLAYER_ID;
    p_temp[playerid][offphone] =
    p_temp[playerid][tune_default] =
    p_temp[playerid][tazer_dest] =
    p_temp[playerid][load_anims] = false;
    p_temp[playerid][h_buy_int] = -1;

    for(new i = MAX_FRACTIONS-1; i != -1; i--) p_temp[playerid][bl_fraction][i] = false;

    p_info[playerid][TaxiTime] = 0;
    p_temp[playerid][phone_talk] =
    p_temp[playerid][p_listitem_int] =
    p_temp[playerid][prison_escape] =
    p_temp[playerid][prison_escape_time] = 0;

    p_temp[playerid][mini_games_type] = 0;

    p_temp[playerid][pos_Y] =
    p_temp[playerid][pos_Z] = 0.0;
    p_temp[playerid][pos_VW] =
    p_temp[playerid][pos_INT] = -1;

    p_temp[playerid][h_repair_txtid] =
    p_temp[playerid][h_repair_old] =
    p_temp[playerid][h_repair_list] =
    p_temp[playerid][hospital_bed_id] =
    p_temp[playerid][parking_id] = -1;

    p_temp[playerid][tipster_family] = - 1;
    p_temp[playerid][tipster_frac] =
    p_temp[playerid][PlayerBook] =
    p_temp[playerid][shop_id] = 0;
    PlayerFixZone[playerid] = 0;
    p_temp[playerid][TaxiCard] =
    p_temp[playerid][ExitCarTimer] =
    p_temp[playerid][TaxiGPS] = false;
    p_temp[playerid][TaxiArea] = -1;

    DisablePlayerCheckpoint(playerid);
    DisablePlayerRaceCheckpoint(playerid);
    /*
    g_curWeaponShotStats[playerid][FixKillerid] = INVALID_PLAYER_ID;
    g_curWeaponShotStats[playerid][FixReason] = 255;
    */
    for(new i = 0; i < 66; i++)
    {
        if(i < 28)
        {
            p_info[playerid][achievement][i] = 0;
            p_info[playerid][achievement_progress][i] = 0;
        }
        p_info[playerid][mission][i] = 0;
    }

    p_info[playerid][DonateUpdate][0] =
    p_info[playerid][DonateUpdate][1] =
    p_info[playerid][DonateUpdate][2] =
    p_info[playerid][DonateUpdate][3] =
    p_info[playerid][Update][0] =
    p_info[playerid][Update][1] =
    p_info[playerid][Update][2] =
    p_info[playerid][Update][3] =
    p_info[playerid][Update][4] = 0;
    p_temp[playerid][SpyStatus] = -1;
    p_temp[playerid][SpyRang] = 0;
    p_info[playerid][youtube_adm] = 0;
    DuelData[playerid][dCommand1] = INVALID_PLAYER_ID;
    DuelData[playerid][dCommand2] = INVALID_PLAYER_ID;
    DuelData[playerid][dBank] = 1000;
    DuelData[playerid][dRound] = 3;
    DuelData[playerid][dGun] = 24;
    p_temp[playerid][FixLSA] = 0;
    p_temp[playerid][WorkCheckDrug] = -1;
    p_temp[playerid][WorkCountDrug] = 0;
    p_temp[playerid][PlayerHistory][0] = EOS;
    p_info[playerid][warn_time] = 0;
    p_temp[playerid][LoggedTime] = -1;
    p_info[playerid][time_exit_game] =
    p_temp[playerid][keys_door] =  0;
    p_temp[playerid][DuelID] = INVALID_PLAYER_ID;

    pSpectateId[playerid] = INVALID_PLAYER_ID;
    pSpectatorId[playerid] = INVALID_PLAYER_ID;
    p_temp[playerid][dSpectateId] = INVALID_PLAYER_ID;
    p_temp[playerid][veh_id_buy] =
    p_temp[playerid][in_enter_vehicle] = INVALID_VEHICLE_ID;

    playerBizLoadTimer[playerid] = -1;

    p_info[playerid][exchangeText] = INVALID_3DTEXT_ID;
    p_info[playerid][exchangePartner] = INVALID_PLAYER_ID;

    Iter_Remove(gFactionPlayers[p_info[playerid][member]], playerid);
    Iter_Remove(gJobPlayers[p_info[playerid][job]], playerid);
    Iter_Remove(gAdmins, playerid);

    a_info[playerid][a_ans] =
    a_info[playerid][a_kick] =
    a_info[playerid][a_jail] =
    a_info[playerid][a_warn] =
    a_info[playerid][a_mute] =
    a_info[playerid][a_ban] =
    a_info[playerid][a_offban] =
    a_info[playerid][a_offjail] =
    a_info[playerid][a_offwarn] =
    a_info[playerid][a_offmute] =
    a_info[playerid][a_day_on] =
    a_info[playerid][a_afk] =
    a_info[playerid][a_rep] = 0;

    p_temp[playerid][FirstReferal] =
    p_temp[playerid][car_damage] = 0;

    p_info[playerid][ID] = INVALID_MYSQL_ID;
    p_info[playerid][admin] =
    p_info[playerid][cash] =
    p_info[playerid][leader] =
    p_info[playerid][member] =
    p_info[playerid][rang] =
    p_info[playerid][fskin] =
    p_info[playerid][bank] =
    p_info[playerid][bank_deposit] =
    p_info[playerid][bank_deposit_limit_take] =
    p_info[playerid][bank_pension] =
    p_info[playerid][bank_pension_status] =
    p_info[playerid][spawn] =
    p_info[playerid][job] =
    p_info[playerid][phone_number] =
    p_info[playerid][wanted] =
    p_info[playerid][jail] =
    //PlayerAutoMoney[playerid] =
    p_info[playerid][mute] =
    p_info[playerid][warn] =
    p_info[playerid][news] =
    p_info[playerid][fwarn] =
    p_info[playerid][free_change_nick] =
    p_info[playerid][loggedIn] =//temp
    p_info[playerid][p_afkTick] =
    p_info[playerid][p_afkCheck] =
    p_info[playerid][p_afkTime] =
    //p_info[playerid][p_countUseCheat] =
    p_info[playerid][p_busTime] =
    p_info[playerid][tipsterlisten] =
    p_info[playerid][tipster] =
    p_info[playerid][p_carlimit] =
    p_info[playerid][p_radar] =
    p_info[playerid][d_addiction] =
    p_info[playerid][d_start_addiction] =
    p_info[playerid][d_demolition] =
    p_info[playerid][army_skin] =
    p_info[playerid][Lic][LIC_WEAPON] =
    p_info[playerid][Lic][LIC_FISHING] =
    p_info[playerid][Lic][LIC_CAR] =
    p_info[playerid][Lic][LIC_MOTO] =
    p_info[playerid][Lic][LIC_PLANE] =
    p_info[playerid][Lic][LIC_BOAT] =
    p_info[playerid][Lic][LIC_HUNTER] =
    p_info[playerid][Lic][LIC_TAXI] =
    p_info[playerid][Lic][LIC_LAWYER] =
    p_info[playerid][h_r_settings][R_GARAGE] =
    p_info[playerid][h_r_settings][R_BASEMENT] =
    p_info[playerid][h_r_settings][R_UNDERGROUND] =
    p_info[playerid][p_game_time] =
    p_info[playerid][p_limite_bank_count] =
    p_info[playerid][user_active] =
    p_temp[playerid][tTied] =
    p_temp[playerid][tGagTime] =
    p_info[playerid][p_settings][CHAT_JOB] =
    p_info[playerid][p_settings][CHAT_ADVERT] =
    p_info[playerid][p_settings][CHAT_ADMIN_ACT] =
    p_info[playerid][p_settings][CHAT_VIP] =
    p_info[playerid][p_settings][CHAT_FRACTION] =
    p_info[playerid][p_settings][CHAT_FAMILY] =
    p_info[playerid][checkdrug] =
    p_info[playerid][paintball] =
    p_info[playerid][p_time_payday] =
    p_info[playerid][p_time_today] =
    p_info[playerid][p_time_yesterday] =
    p_info[playerid][p_afk_today] =
    p_info[playerid][p_afk_yesterday] =
    p_info[playerid][daily_days] =
    p_info[playerid][daily_time] =
    p_info[playerid][daily_today] =
    p_info[playerid][gift_promocode_status] =
    p_info[playerid][gift_promocode_time] =
    p_info[playerid][rob_time] =
    p_info[playerid][paintball] =
    p_info[playerid][family_mute] =
    p_info[playerid][family_warn] =
    p_info[playerid][lotto] =
    p_info[playerid][family_exp] =
    p_info[playerid][bizz_slots] =
    p_info[playerid][house_slots] =
    p_info[playerid][inv_slots] = 0;

    for(new i = MAX_BIZZ_PLAYER-1; i != -1; i--)
        p_info[playerid][key_bizz][i] = INVALID_BIZZ_ID;
    for(new i = MAX_HOUSE_PLAYER-1; i != -1; i--)
        p_info[playerid][key_house][i] = INVALID_HOUSE_ID;
    for(new i = MAX_PLAYER_SKINS-1; i != -1; i--)
        p_info[playerid][skins][i] = INVALID_SKIN_ID;
    for(new i; i < 6; i++)
        p_info[playerid][veh_slots][i] = 0;
    for(new i = MAX_ALL_EQUIPMENT-1; i != -1; i--)
        Equipment_ClearSlot(playerid, i);

    p_info[playerid][active_phone_id] =
    p_info[playerid][active_bizz_id] =
    p_info[playerid][active_house_id] =
    p_info[playerid][active_vehicle_id] =
    p_info[playerid][spawn_house_id] = 0;

    p_info[playerid][spawn_pos_x] =
    p_info[playerid][spawn_pos_y] =
    p_info[playerid][spawn_pos_z] =
    p_info[playerid][spawn_pos_r] = 0.0;

    p_temp[playerid][show_killlist] = true;
    p_temp[playerid][tGag] =
    p_temp[playerid][spawn_exit] =
    p_temp[playerid][biz_war_map] = false;

    p_info[playerid][loggedIn] = 0;

    p_temp[playerid][PizzaboyIDx] = -1;
    p_temp[playerid][PizzaboySalary] = 0;

    p_temp[playerid][FireStatus] = 0;
    p_temp[playerid][FireTimer] = 0;
    p_temp[playerid][FireExting] = 0;
    p_temp[playerid][FireExtingCount] = 0;
    p_temp[playerid][FireAmmo] = 0;

    p_temp[playerid][TruckerLoad] = 0;
    p_temp[playerid][TruckerSalary] = 0;
    p_temp[playerid][TruckerTrailer] = INVALID_VEHICLE_ID;

    p_temp[playerid][TrainVehicleIDx] = INVALID_VEHICLE_ID;
    p_temp[playerid][TrainTimer] = 0;
    p_temp[playerid][TrainStop] = false;
    p_temp[playerid][TrainStopIDx] = 0;
    p_temp[playerid][TrainSpeedWarning] = 0;
    p_temp[playerid][TrainCheckpoint] = 0;

    p_temp[playerid][TramVehicleIDx] = INVALID_VEHICLE_ID;
    p_temp[playerid][TramTimer] = 0;
    p_temp[playerid][TramStop] = false;
    p_temp[playerid][TramStopIDx] = 0;
    p_temp[playerid][TramSpeedWarning] = 0;

    p_temp[playerid][LaboratoryTimer] = 0;
    p_temp[playerid][LaboratoryCount] = 0;
    p_temp[playerid][LaboratorySalary] = 0;
    p_temp[playerid][LaboratoryCheck] = 0;

    p_temp[playerid][SpaceIDx] = 0;
    p_temp[playerid][SpaceTimer] = 0;
    p_temp[playerid][SpaceProgress] = 0;
    p_temp[playerid][SpaceCount] = 0;
    p_temp[playerid][SpaceSalary] = 0;

    p_temp[playerid][SpaceFlightStatus] = false;
    p_temp[playerid][SpaceFlightType] = 0;
    p_temp[playerid][SpaceFlightCheck] = 0;
    p_temp[playerid][SpaceFlightTimer] = 0;

    p_temp[playerid][BeingInSpace] = false;

    p_temp[playerid][GraffitiID] = -1;
    p_temp[playerid][GraffitiExtingCount] =
    p_temp[playerid][GraffitiAmmo] = 0;

    p_temp[playerid][DiseaseTime] = 0;

    p_temp[playerid][ConstructionType] = 0;
    p_temp[playerid][ConstructionCheck] = 0;
    p_temp[playerid][ConstructionCount] = 0;
    p_temp[playerid][ConstructionSalary] = 0;
    p_temp[playerid][ConstructionObject] = INVALID_OBJECT_ID;
    p_temp[playerid][ConstructionIDx] = -1;

    p_temp[playerid][GunFactoryCheck] = 0;
    p_temp[playerid][GunFactoryIDx] = 0;
    p_temp[playerid][GunFactoryCount] = 0;
    p_temp[playerid][GunFactorySalary] = 0;
    p_temp[playerid][GunFactoryLocat] = 0;

    p_temp[playerid][RailwayType] = 0;
    p_temp[playerid][RailwayCheck] = 0;
    p_temp[playerid][RailwayIDx] = 0;
    p_temp[playerid][RailwayCount][0] = 0;
    p_temp[playerid][RailwayCount][1] = 0;
    p_temp[playerid][RailwayObject] = INVALID_OBJECT_ID;
    p_temp[playerid][RailwaySalary] = 0;
    p_temp[playerid][RailwayLocat] = 0;

    p_temp[playerid][FarmType] = 0;
    p_temp[playerid][FarmTrailer] = INVALID_VEHICLE_ID;
    p_temp[playerid][FarmTrailerTimer] = 0;
    p_temp[playerid][FarmTreeIDx] = -1;
    p_temp[playerid][FarmMilkerIDx] = -1;
    p_temp[playerid][FarmCheck] = 0;
    p_temp[playerid][FarmBucket] = 0;
    p_temp[playerid][FarmCount] = 0;
    p_temp[playerid][FarmSalary] = 0;
    p_temp[playerid][FarmBizIDx] = -1;
    for(new i = 0; i < 5; i++) p_temp[playerid][FarmObject][i] = INVALID_OBJECT_ID;
    p_temp[playerid][farm_use_idx] = -1;
    p_temp[playerid][farm_use_type] = -1;
    p_temp[playerid][farm_extraction_timer] = 0;

    CollectorIDx[playerid] = -1;
    CollectorVehicleIDx[playerid] = INVALID_VEHICLE_ID;
    CollectorAttachedObject[playerid] = 0;
    for(new i = 0; i < 3; i++) CollectorMembersParty[playerid][i] = INVALID_PLAYER_ID;
    CollectorParty[playerid] = INVALID_PLAYER_ID;

    p_temp[playerid][PanelIDx] = -1;
    p_temp[playerid][PanelSalary] = 0;
    for(new i = 0; i < 16; i++)
    {
        if(i < 2) p_temp[playerid][PanelObject][i] = INVALID_OBJECT_ID;
        p_temp[playerid][PanelButton][i] = 0;
    }

    p_temp[playerid][GreenHousesIDx] = -1;
    p_temp[playerid][GreenHousesSalary] = 0;
    p_temp[playerid][GreenHousesTimer] = 0;
    p_temp[playerid][GreenHousesCheck] = 0;

    RobberIDx[playerid] = -1;
    RobberVehicleIDx[playerid] = INVALID_VEHICLE_ID;
    RobberAttachedObject[playerid] = 0;
    for(new i = 0; i < 3; i++) RobberMembersParty[playerid][i] = INVALID_PLAYER_ID;
    RobberParty[playerid] = INVALID_PLAYER_ID;

    CarFactoryIDx[playerid] = -1;
    CarFactoryType[playerid] = -1;
    CarFactoryCarParts[playerid] = -1;
    CarFactorySalary[playerid] = 0;

    FishStart[playerid] = false;
    FishTimer[playerid] = 0;
    FishPress[playerid] = 0;
    FishPressCount[playerid] = 0;

    AirDropUse[playerid] = -1;
    AirDropUseItems[playerid] = -1;

    WarPlaneUse[playerid] = -1;
    WarPlaneUseItems[playerid] = -1;

    p_temp[playerid][dm_zone_timer] = 0;

    p_temp[playerid][hints_idx] = random(MAX_HINTS);
    p_temp[playerid][hints_timer] = 300;

    p_temp[playerid][underground_use] = -1;

    p_temp[playerid][fix_logged_house] = 0;
    p_temp[playerid][fix_logged_house_check] = 0;

    p_temp[playerid][antibot_check] = false;
    p_temp[playerid][antibot_idx] = 0;
    p_temp[playerid][antibot_number] = 0;
    p_temp[playerid][antibot_time] = 0;

    p_temp[playerid][trash_box_use] = -1;

    p_temp[playerid][offer_code] = 0;

    p_temp[playerid][t_hunter_status] = false;
    p_temp[playerid][t_hunter_x] = 0.0;
    p_temp[playerid][t_hunter_y] = 0.0;
    p_temp[playerid][t_hunter_z] = 0.0;
    ClearTHunterButton(playerid);
    p_temp[playerid][t_hunter_game] = -1;

    ClearPlayerRouletteTextDraw(playerid, 1);
    ClearPlayerTextDrawCase(playerid, 1);

    p_temp[playerid][LastDriverVehicleIDx] = INVALID_VEHICLE_ID;

    p_temp[playerid][TextDrawInventory] =
    p_temp[playerid][TextDrawCraft] =
    p_temp[playerid][TextDrawBattlePass] =
    p_temp[playerid][TextDrawDaily] =
    p_temp[playerid][TextDrawMarket] =
    p_temp[playerid][TextDrawCase] =
    p_temp[playerid][TextDrawPhone] =
    p_temp[playerid][TextDrawCarFactory] =
    p_temp[playerid][TextDrawCasinoUse] =
    p_temp[playerid][TextDrawPinCode] =
    p_temp[playerid][TextDrawReconUse] =
    p_temp[playerid][TextDrawListUse] =
    p_temp[playerid][TextDrawShopUse] =
    p_temp[playerid][TextDrawCapture] = 
    p_temp[playerid][TextDrawServiceTune] =
    p_temp[playerid][TextDrawEditor] =
    p_temp[playerid][TextDrawFarm] =
    p_temp[playerid][TextDrawPlayerMenu] =
    p_temp[playerid][TextDrawRoulette] =
    p_temp[playerid][TextDrawTrade] =
    p_temp[playerid][TextDrawEquipment] =
    p_temp[playerid][TextDrawEquipmentMenu] =
    p_temp[playerid][Equipment_Settings] =
    p_temp[playerid][TextDrawRobberyRobbing] =
    p_temp[playerid][TextDrawElectric] =
    p_temp[playerid][TextDrawRadio] =
    p_temp[playerid][TextDrawTHunterGPS] =
    p_temp[playerid][TextDrawTHunterGame] =
    p_temp[playerid][SlotMachineTextDraw] = false;

    p_temp[playerid][slot_machine_use] = -1;

    p_temp[playerid][time_save_player] = 0;

    for(new i; i < 3; i++) AntiCheatWarningTime[playerid][i] = 0;
    for(new i; i < 3; i++) AntiCheatPlayerPos[playerid][i] = 0.0;
    /*for(new i; i < 6; i++) p_temp[playerid][check_active_pos][i] = 0.0;*/

    p_temp[playerid][VipFix] = 0;

    ChoosenAdvert[playerid] = -1;

    p_info[playerid][email_confirmed] = 0;

    p_info[playerid][referral] =
    p_info[playerid][referralmoney] =
    p_info[playerid][referralcount] =

    p_temp[playerid][prison_work] =

    p_temp[playerid][LoginFix] =
    p_temp[playerid][JobChatFix] =
    p_temp[playerid][HelpDialog] =
    p_temp[playerid][UseMaskFix] =
    p_temp[playerid][UnFreezeFix] =
    p_temp[playerid][AddictionFix] =
    p_temp[playerid][ClearAnimFix] =
    p_temp[playerid][SaveDonateCar] =
    p_temp[playerid][LoginTimerFix] =
    p_temp[playerid][UseMaskTimerFix] =
    p_temp[playerid][UnFreezeTimerFix] =
    p_temp[playerid][ClearAnimTimerFix] =
    p_temp[playerid][AddictionTimerFix] = 0;

    p_info[playerid][google_code] = EOS;
    p_info[playerid][pfreeze] = 1;

    p_info[playerid][key_h_rent] =
    p_info[playerid][key_hotel] =
    p_info[playerid][key_hotel_room] =
    p_info[playerid][p_radar_id] =
    p_info[playerid][family_id] =
    p_info[playerid][family_rang] =
    p_temp[playerid][family_game_id] =

    p_temp[playerid][p_listitem_int] =
    p_temp[playerid][invite_duel] =

    p_temp[playerid][market_arend] =
    p_temp[playerid][market_buy_idx] =
    p_temp[playerid][market_buy_items][0] = 
    p_temp[playerid][market_buy_items][1] = -1;

    p_temp[playerid][family_car_select] = 0;
    p_temp[playerid][family_car_id] = INVALID_VEHICLE_ID;

    p_temp[playerid][family_label] = Text3D:-1;
    p_temp[playerid][pame_label] = Text3D:-1;

    p_temp[playerid][CaptureBizWarInfoInt][0] = 0;
    p_temp[playerid][CaptureBizWarInfoInt][1] = 0;
    p_temp[playerid][CaptureBizWarInfoFloat][0] = 0.0;
    p_temp[playerid][CaptureBizWarInfoFloat][1] = 0.0;

    p_temp[playerid][gps_admin] = INVALID_PLAYER_ID;

    p_info[playerid][fwork] =
    p_temp[playerid][p_garage_use] =
    admin_acces[playerid] =
    p_info[playerid][in_hospital] =
    p_temp[playerid][p_GPS] = false;

    p_info[playerid][ID] = INVALID_MYSQL_ID;

    p_info[playerid][pHealth] =
    p_info[playerid][satiety] =
    p_info[playerid][thirst] = 100.0;

    p_temp[playerid][rented_veh] = INVALID_VEHICLE_ID;

    p_temp[playerid][p_listitem] =
    p_temp[playerid][recon_antiflood] =
    p_temp[playerid][twinturbo_on] =
    p_temp[playerid][twinturbo_break] =
    p_temp[playerid][paint_veh_go] =
    p_temp[playerid][p_in_pickup] = 0;
    p_temp[playerid][p_listitem_cars] = -1;

    GangZoneHideForPlayer(playerid, Zone_Drive);

    p_temp[playerid][p_house_id] = INVALID_HOUSE_ID;
    p_temp[playerid][p_biz_id] =
    p_temp[playerid][p_tc_id] =
    p_temp[playerid][p_house_area] =
    p_temp[playerid][e_tListComponents] =
    p_temp[playerid][dissconect_id] = -1;

    SetPVarInt(playerid, "id_gang", INVALID_PLAYER_ID);

    for (new i; i < MAX_WEAPONS; i++) {
        p_info[playerid][Weapon][i] =
        p_info[playerid][Ammo][i] = 0;
    }

    for(new i = 0; i < 2; i++) p_info[playerid][cigarette_status][i] = 0;

    /*
    noclipdata[playerid][cameramode]     = CAMERA_MODE_NONE;
    noclipdata[playerid][lrold]                = 0;
    noclipdata[playerid][udold]           = 0;
    noclipdata[playerid][mode]           = 0;
    noclipdata[playerid][lastmove]       = 0;
    noclipdata[playerid][accelmul]       = 0.0;
    */
    player_lobby_status[playerid] = false;
    player_lobby_type[playerid] = -1;
    player_lobby_idx[playerid] = -1;
    for(new i = 0; i < 7; i++) player_lobby_settings[playerid][i] = 0;

    GangZoneHideForPlayer(playerid, TheftCarZone[playerid]);
    ClearTheftCar(playerid);
    ClearObjectInfo(playerid);
    ClearHookah(playerid);
    ClearTent(playerid);
    ClearPlayerHunting(playerid);

    p_temp[playerid][billboard_status] = false;
    p_temp[playerid][billboard_timer] = 0;

    p_temp[playerid][trash_id] = 
    p_temp[playerid][container_id] = -1;

    p_temp[playerid][craft_type] = CRAFT_TYPE_ACCESSORIES;
    p_temp[playerid][craft_idx] = -1;
    p_temp[playerid][craft_last_idx] = -1;
    p_temp[playerid][craft_items_list][0] =
    p_temp[playerid][craft_items_list][1] =
    p_temp[playerid][craft_items_list][2] =
    p_temp[playerid][craft_items_list][3] =
    p_temp[playerid][craft_items_list][4] = 0;
    p_temp[playerid][craft_list] = 0;
    p_temp[playerid][craft_count] = 1;
    p_temp[playerid][craft_timer] = 0;

    p_temp[playerid][radio_use_type] = -1;
    p_temp[playerid][radio_type] = TYPE_RADIO_LIST;
    p_temp[playerid][radio_idx] = -1;
    p_temp[playerid][radio_last_idx] = 0;
    for(new i = 0; i < MAX_PLAYER_RADIO_LIST; i++) p_temp[playerid][radio_items_list][i] = 0;
    p_temp[playerid][radio_list] = 0;

    p_temp[playerid][battle_last_idx][0] =
    p_temp[playerid][battle_last_idx][1] = 0;

    for(new i = 0; i < 34; i++) p_temp[playerid][battle_items_list_reward][i] = 0;

    p_temp[playerid][battle_items_list_task][0] =
    p_temp[playerid][battle_items_list_task][1] = 0;

    p_temp[playerid][battle_list][0] =
    p_temp[playerid][battle_list][1] = 0;

    p_temp[playerid][daily_last_idx] = 0;

    p_temp[playerid][daily_items_list_reward][0] =
    p_temp[playerid][daily_items_list_reward][1] =
    p_temp[playerid][daily_items_list_reward][2] =
    p_temp[playerid][daily_items_list_reward][3] =
    p_temp[playerid][daily_items_list_reward][4] =
    p_temp[playerid][daily_items_list_reward][5] =
    p_temp[playerid][daily_items_list_reward][6] = 0;

    p_temp[playerid][daily_list] = 0;

    p_temp[playerid][res_use_idx] =
    p_temp[playerid][res_use_type] = -1;

    p_temp[playerid][res_extraction_timer] = 0;

    p_temp[playerid][change_res_items] = 0;
    p_temp[playerid][change_res_type] = 0;

    p_temp[playerid][vc_idx] = -1;
    p_temp[playerid][vc_rack] = -1;

    p_temp[playerid][underground_idx] = -1;
    p_temp[playerid][underground_actor] = -1;

    p_temp[playerid][service_idx] = -1;

    p_temp[playerid][fix_bug_biz_tc_salary] = 0;
    p_temp[playerid][change_skin_idx] = 0;

    p_temp[playerid][mechanic_idx] = 0;
    p_temp[playerid][mechanic_timer] = 0;
    p_temp[playerid][mechanic_salary] = 0;
    p_temp[playerid][mechanic_exting] = 0;
    p_temp[playerid][mechanic_exting_count] = 0;
    p_temp[playerid][mechanic_ammo] = 0;

    p_temp[playerid][repair_timer] = 0;
    p_temp[playerid][panic_target_id] = INVALID_PLAYER_ID;

    p_temp[playerid][taxi_bots_idx] = 0;
    p_temp[playerid][taxi_bots_timer] = 0;
    p_temp[playerid][taxi_bots_salary] = 0;
    p_temp[playerid][taxi_bots_gps_idx] = 0;

    p_temp[playerid][oil_check] = 0;
    p_temp[playerid][oil_object][0] =
    p_temp[playerid][oil_object][1] =
    p_temp[playerid][oil_object][2] =
    p_temp[playerid][oil_object][3] =
    p_temp[playerid][oil_object][4] =
    p_temp[playerid][oil_object][5] =
    p_temp[playerid][oil_object][6] =
    p_temp[playerid][oil_object][7] =
    p_temp[playerid][oil_object][8] =
    p_temp[playerid][oil_object][9] =
    p_temp[playerid][oil_object][10] =
    p_temp[playerid][oil_object][11] =
    p_temp[playerid][oil_object][12] =
    p_temp[playerid][oil_object][13] =
    p_temp[playerid][oil_object][14] =
    p_temp[playerid][oil_object][15] =
    p_temp[playerid][oil_object][16] =
    p_temp[playerid][oil_object][17] =
    p_temp[playerid][oil_object][18] =
    p_temp[playerid][oil_object][19] =
    p_temp[playerid][oil_object][20] =
    p_temp[playerid][oil_object][21] =
    p_temp[playerid][oil_object][22] =
    p_temp[playerid][oil_object][23] =
    p_temp[playerid][oil_object][24] = INVALID_OBJECT_ID;

    p_temp[playerid][roadman_check] = 0;
    p_temp[playerid][roadman_use_idx] = -1;
    p_temp[playerid][roadman_hash_idx] = -1;
    p_temp[playerid][roadman_extraction_timer] = 0;
    p_temp[playerid][roadman_object][0] =
    p_temp[playerid][roadman_object][1] =
    p_temp[playerid][roadman_object][2] =
    p_temp[playerid][roadman_object][3] =
    p_temp[playerid][roadman_object][4] = INVALID_OBJECT_ID;

    p_temp[playerid][show_info_gps] = 0;
    p_temp[playerid][show_info_donate] = 0;

    p_temp[playerid][cossack_robbers_register] = 0;
    p_temp[playerid][cossack_robbers_team] = 0;
    p_temp[playerid][cossack_robbers_kills] = 0;
    p_temp[playerid][cossack_robbers_deaths] = 0;
    p_temp[playerid][cossack_robbers_give] = 0.0;
    p_temp[playerid][cossack_robbers_take] = 0.0;

    ClearRobberyBank(playerid);
    ClearRobberyHouse(playerid);
    ClearRobberyHouseBackup(playerid);
    ClearPlayerFreelance(playerid);
    ClearRobberyBankBackup(playerid);
    ClearRobberyFuel(playerid);
    ClearRobberyFuelBackup(playerid);
    ClearRobbingMiniGame(playerid);
    ClearElectricMiniGame(playerid);

    for(new i = 0; i < 9; i++)
    {
        if(i < 4) p_temp[playerid][CreateBoxCoords][i] = 0.0;
        p_temp[playerid][CreateBoxObject][i] = INVALID_OBJECT_ID;
    }

    // for(new i = 52; i != -1; --i) EnableAntiCheatForPlayer(playerid, i, 1);
}

GetPlayerAllHouse(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `h_mysql_id` FROM `house` WHERE `h_user_id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerLoadHouse", "i", playerid);
}

forward OnPlayerLoadHouse(playerid);
public OnPlayerLoadHouse(playerid)
{
    new rows, houseID;
    cache_get_row_count(rows);
    if(!rows) return 1;
    for(new i; i < rows; i++)
    {
        if(i >= p_info[playerid][house_slots]) break;
        cache_get_value_index_int(i, 0, p_info[playerid][key_house][i]);
        if(h_info[p_info[playerid][key_house][i]][h_rent] < 5) SendInfo(playerid, "Аренда дома закончится менее чем через 5 часов.");
        houseID = p_info[playerid][key_house][i];
        save_house(houseID);
    }
    if(p_info[playerid][loggedIn] && p_info[playerid][spawn] == SPAWN_HOUSE)
    {
        SpawnPlayer(playerid);
        p_temp[playerid][fix_logged_house] = 1;
        p_temp[playerid][fix_logged_house_check] = 0;
    }
    return 1;
}

GetPlayerHouseRent(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `h_mysql_id` FROM `house` WHERE `h_r_user_id_0` = %d OR `h_r_user_id_1` = %d OR `h_r_user_id_2` = %d OR `h_r_user_id_3` = %d OR `h_r_user_id_4` = %d",
        p_info[playerid][ID], p_info[playerid][ID], p_info[playerid][ID], p_info[playerid][ID], p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerLoadRentHouse","i", playerid);
}

forward OnPlayerLoadRentHouse(playerid);
public OnPlayerLoadRentHouse(playerid)
{
    new house_id, rows;
    cache_get_row_count(rows);
    p_info[playerid][key_h_rent] = -1;
    if(rows)
    {
        cache_get_value_int(0, "h_mysql_id", house_id);
        if(GetFreeSlotHouse(playerid) != p_info[playerid][house_slots])
        {
            for(new idx; idx <= h_info[house_id][h_squar]; idx++)
            {
                if(p_info[playerid][ID] == h_info[house_id][h_r_user_id][idx])
                    house_rent_leave(house_id, idx);
            }
        }
        else p_info[playerid][key_h_rent] = house_id;
    }
    return 1;
}

GetPlayerAllBizz(playerid)
{
    STRING_GLOBAL[0] = EOS;
    mysql_format(con_bd, STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `b_mysql_id` FROM `biz` WHERE `b_user_id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerLoadBizz", "i", playerid);
    return 1;
}

forward OnPlayerLoadBizz(playerid);
public OnPlayerLoadBizz(playerid)
{
    new rows;
    cache_get_row_count(rows);
    if(!rows) return 1;
    for(new i, bizz_id; i < rows; i++)
    {
        if(i >= p_info[playerid][bizz_slots]) break;
        cache_get_value_index_int(i, 0, bizz_id);
        p_info[playerid][key_bizz][i] = bizz_id;
        if(b_info[bizz_id][b_rent] < 5) SendInfo(playerid, "Аренда Вашего бизнеса %s закончится менее чем через 5 часов.", b_info[p_info[playerid][key_bizz][i]][_name]);
        if(b_info[bizz_id][_tip] == B_TAXI && p_info[playerid][taxi_idx] != bizz_id)
        {
            printf("BUG: TAXI_IDX != bizz_id | %s[%d]", get_name(playerid), p_info[playerid][ID]);
            p_info[playerid][taxi_idx] = bizz_id;
            p_info[playerid][taxi_rank] = 3;
        }
        if(b_info[bizz_id][_tip] == B_TRUCKER && p_info[playerid][tc_idx] != bizz_id)
        {
            printf("BUG: TC_IDX != bizz_id %d == %d | %s[%d]", p_info[playerid][tc_idx],  get_name(playerid), p_info[playerid][ID]);
            p_info[playerid][tc_idx] = bizz_id;
            p_info[playerid][tc_rank] = 3;
        }
    }
    return 1;
}

IsPlayerOwnerBizzType(playerid, type)
{
    new count;
    for(new i, bizz_id; i < p_info[playerid][bizz_slots]; i++)
    {
        bizz_id = GetPlayerBizzID(playerid, i);
        if(bizz_id != INVALID_BIZZ_ID && type == b_info[bizz_id][_tip])
            count++;
    }
    return count;
}

GetPlayerBizzIDType(playerid, type)
{
    new value = INVALID_BIZZ_ID;
    for(new i, bizz_id; i < p_info[playerid][bizz_slots]; i++)
    {
        bizz_id = GetPlayerBizzID(playerid, i);
        if(bizz_id != INVALID_BIZZ_ID && b_info[bizz_id][_tip] == type)
        {
            value = bizz_id;
            break;
        }
    }
    return value;
}



LoadPlayerNotification(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "SELECT `id` FROM `player_notification` WHERE `user_id` = %d", p_info[playerid][ID]);
    mysql_tquery(con_bd, STRING_GLOBAL, "OnPlayerNotification", "i", playerid);
}

forward OnPlayerNotification(playerid);
public  OnPlayerNotification(playerid)
{
    if(cache_num_rows() != 0)
    {
        SendMes(playerid, COLOR_DARKORANGE, "У Вас есть новые оповещения. Подробнее: "W"/notify");
    }
    return 1;
}


