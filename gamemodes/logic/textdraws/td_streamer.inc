ShowTextDrawForPlayer(playerid, TD_ID)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    CreateTextDrawForPlayer(playerid, TD_ID);
    switch(TD_ID)
    {
        case TD_ID_T_HUNTER_GAME:
        {
            p_temp[playerid][TextDrawTHunterGame] = true;

            for(new i = 0; i < 36; i++) PlayerTextDrawShow(playerid, PTD_THunterGame[playerid][i]);

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_T_HUNTER_GPS:
        {
            p_temp[playerid][TextDrawTHunterGPS] = true;

            for(new i = 0; i < 9; i++) PlayerTextDrawShow(playerid, PTD_THunterGPS[playerid][i]);
        }
        case TD_ID_ROBBING:
        {
            for(new i = 0; i < 14; i++) PlayerTextDrawShow(playerid, PTD_Robbing[playerid][i]);

            p_temp[playerid][TextDrawRobberyRobbing] = true;

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "HAДMЕПE:_%s", robbing_mini_game[p_temp[playerid][robbing_mini_game_button]]);
            PlayerTextDrawSetString(playerid, PTD_Robbing[playerid][4], STRING_GLOBAL);

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_CRAFT:
        {
            if(p_temp[playerid][TextDrawCraft]) return 1;
            for(new i = 0; i < 26; i++) PlayerTextDrawShow(playerid, PTD_CraftMain[playerid][i]);
            p_temp[playerid][craft_type] = CRAFT_TYPE_ACCESSORIES;
            p_temp[playerid][craft_idx] = -1; // ID из массива CraftInfo;
            p_temp[playerid][craft_last_idx] = 0; // ѕоследн€€ строка, котора€ вывелась в списке из массива CraftInfo;
            p_temp[playerid][craft_list] = 0; // Ќомер страницы;
            p_temp[playerid][craft_count] = 1; //  оличество;
            p_temp[playerid][craft_timer] = 0;
            ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_BUTTON);
            ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_RESOURCES);
            for(new i = 0; i < 5; i++) PlayerTextDrawShow(playerid, PTD_CraftInfo[playerid][i]);

            p_temp[playerid][TextDrawCraft] = true;

            ShowPlayerCraft(playerid, CRAFT_TYPE_SHOW_ITEMS);
            UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_LIST);
            UpdatePlayerCraft(playerid, CRAFT_TYPE_UPDATE_COUNT);

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_BATTLEPASS:
        {
            if(p_temp[playerid][TextDrawBattlePass]) return 1;
            for(new i = 0; i < 18; i++) PlayerTextDrawShow(playerid, PTD_BattlePassMain[playerid][i]);
            p_temp[playerid][battle_last_idx][0] = 0; // ѕоследн€€ строка, котора€ вывелась в списке из массива BattlePassReward;
            p_temp[playerid][battle_last_idx][1] = 0; // ѕоследн€€ строка, котора€ вывелась в списке из массива BattlePassTask;
            p_temp[playerid][battle_list][0] = 0; // Ќомер страницы наград;
            p_temp[playerid][battle_list][1] = 0; // Ќомер страницы заданий;
            ShowPlayerBattlePass(playerid, BATTLEPASS_TYPE_SHOW_REWARD);
            ShowPlayerBattlePass(playerid, BATTLEPASS_TYPE_SHOW_TASK);
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassInfo[playerid][0], BattlePassSeasonModel[BattlePassSeason]); // ћодель сезона;
            for(new i = 0; i < 8; i++)
            {
                PlayerTextDrawShow(playerid, PTD_BattlePassButton[playerid][i]);
                if(i < 5) PlayerTextDrawShow(playerid, PTD_BattlePassInfo[playerid][i]);
            }

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "BATTLE PASS~n~%s~n~ƒЌ≈… ƒќ  ќЌ÷ј: ~r~%d", BattlePassSeasonName[BattlePassSeason], BattlePassTime);
            PlayerTextDrawSetString(playerid, PTD_BattlePassInfo[playerid][1], STRING_GLOBAL);

            p_temp[playerid][TextDrawBattlePass] = true;

            UpdatePlayerBattlePass(playerid, BATTLEPASS_TYPE_UPDATE_STATS);
            UpdatePlayerBattlePass(playerid, BATTLEPASS_TYPE_UPDATE_LIST);

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_DAILY:
        {
            if(p_temp[playerid][TextDrawDaily]) return 1;
            for(new i = 0; i < 8; i++)
            {
                if(i < 3) PlayerTextDrawShow(playerid, PTD_DailyMain[playerid][i]);
                if(i < 2) PlayerTextDrawShow(playerid, PTD_DailyInfo[playerid][i]);
                PlayerTextDrawShow(playerid, PTD_DailyButton[playerid][i]);
            }
            p_temp[playerid][daily_last_idx] = 0; // ѕоследн€€ строка, котора€ вывелась в списке из списка наград;
            p_temp[playerid][daily_list] = 0; // Ќомер страницы наград;
            ShowPlayerDaily(playerid);

            p_temp[playerid][TextDrawDaily] = true;

            UpdatePlayerDaily(playerid, DAILY_TYPE_UPDATE_TIME);
            UpdatePlayerDaily(playerid, DAILY_TYPE_UPDATE_LIST);

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_ELECTRIC:
        {
            if(p_temp[playerid][TextDrawElectric]) return 1;
            for(new i = 0; i < 14; i++) PlayerTextDrawShow(playerid, PTD_Electric[playerid][i]);

            p_temp[playerid][TextDrawElectric] = true;

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "%s", ElectricType[playerid] == 0 ? "–≈ћќЌ“ ЋЁѕ" : "ќ√–јЅЋ≈Ќ»≈ ЋЁѕ");
            PlayerTextDrawSetString(playerid, PTD_Electric[playerid][3], STRING_GLOBAL);

            STRING_GLOBAL[0] = EOS;
            f(STRING_GLOBAL, "Ќј∆ћ»“≈ Ќј %s ѕ–ќ¬ќƒ", p_temp[playerid][electric_mini_game_button] == 0 ? "~r~ –ј—Ќџ…~w~" : "~b~—»Ќ»…~w~");
            PlayerTextDrawSetString(playerid, PTD_Electric[playerid][6], STRING_GLOBAL);

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_RADIO:
        {
            if(p_temp[playerid][TextDrawRadio]) return 1;
            for(new i = 0; i < 35; i++) PlayerTextDrawShow(playerid, PTD_Radio[playerid][i]);

            p_temp[playerid][TextDrawRadio] = true;

            SelectTextDraw(playerid, -4632577);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_INVENTORY_PLAYER:
        {
            if(p_temp[playerid][TextDrawEquipment]) return 1;
            for(new i = 55; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][i]);
            for(new i = 29; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentPersonInfo[playerid][i]);

            p_temp[playerid][TextDrawInventory] =
            p_temp[playerid][TextDrawEquipment] = true;

            p_temp[playerid][TextDrawMarket] =
            p_temp[playerid][TextDrawTrade] =
            p_temp[playerid][TextDrawEquipmentMenu] =
            p_temp[playerid][Equipment_Settings] = false;

            SelectTextDraw(playerid, 0xFFFFFF95);
            Fix_TogglePlayerControllable(playerid, false);

            Interface_Show(playerid, EQUIPMENT_INVENTORY_PLAYER);
        }
        case TD_ID_TRADE:
        {
            if(p_temp[playerid][TextDrawEquipment]) return 1;
            for(new i = 55; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][i]);
            for(new i = 53; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][i]);

            p_temp[playerid][TextDrawTrade] =
            p_temp[playerid][TextDrawEquipment] = true;

            p_temp[playerid][TextDrawInventory] =
            p_temp[playerid][TextDrawEquipmentMenu] =
            p_temp[playerid][Equipment_Settings] = false;

            SelectTextDraw(playerid, 0xFFFFFF95);
            Fix_TogglePlayerControllable(playerid, false);

            Interface_Show(playerid, EQUIPMENT_TRADE);
        }
        case TD_ID_MARKET:
        {
            if(p_temp[playerid][TextDrawEquipment]) return 1;
            for(new i = 55; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][i]);
            for(new i = 53; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][i]);

            p_temp[playerid][TextDrawMarket] =
            p_temp[playerid][TextDrawEquipment] = true;

            p_temp[playerid][TextDrawInventory] =
            p_temp[playerid][TextDrawTrade] =
            p_temp[playerid][TextDrawEquipmentMenu] =
            p_temp[playerid][Equipment_Settings] = false;

            SelectTextDraw(playerid, 0xFFFFFF95);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_INVENTORY_OTHER:
        {
            if(p_temp[playerid][TextDrawEquipment]) return 1;
            for(new i = 55; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentRight[playerid][i]);
            for(new i = 53; i != -1; i--) PlayerTextDrawShow(playerid, PTD_EquipmentLeft[playerid][i]);

            p_temp[playerid][TextDrawInventory] =
            p_temp[playerid][TextDrawEquipment] = true;

            p_temp[playerid][TextDrawMarket] =
            p_temp[playerid][TextDrawTrade] =
            p_temp[playerid][TextDrawEquipmentMenu] =
            p_temp[playerid][Equipment_Settings] = false;

            SelectTextDraw(playerid, 0xFFFFFF95);
            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_DONATE_INFO:
        {
            if(p_temp[playerid][TextDrawDonateInfo]) return 1;
            for(new i = 38; i != -1; i--) PlayerTextDrawShow(playerid, PTD_DonateInfo[playerid][i]);
            SelectTextDraw(playerid, 0xFFFFFF95);
            p_temp[playerid][TextDrawDonateInfo] = true;
        }
        case TD_ID_PANEL:
        {
            if(p_temp[playerid][TextDrawPanel]) return 1;
            for(new i = 18; i != -1; i--) PlayerTextDrawShow(playerid, PTD_Panel[playerid][i]);
            SelectTextDraw(playerid, 0xFFFFFF95);
            p_temp[playerid][TextDrawPanel] = true;
        }
        case TD_ID_LOGO:
        {
            for(new i = 0; i < 16; i++)
            {
                //TextDrawShowForPlayer(playerid, TD_Logo_Donate[i]);
                if(i < 15) TextDrawShowForPlayer(playerid, TD_Logo_Default[i]);
            }
        }
        case TD_ID_PHONE:
        {
            if(p_temp[playerid][TextDrawPhone]) return 1;
            p_temp[playerid][TextDrawPhone] = true;
            Interface_Show(playerid, PHONE_INDEX);
            SelectTextDraw(playerid, -1);

            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_CASE:
        {
            if(p_temp[playerid][TextDrawCase]) return 1;
            p_temp[playerid][TextDrawCase] = true;
            Interface_Show(playerid, CASE_INDEX);
            SelectTextDraw(playerid, -1);

            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_ROULETTE:
        {
            if(p_temp[playerid][TextDrawRoulette]) return 1;
            p_temp[playerid][TextDrawRoulette] = true;
            Interface_Show(playerid, ROULETTE_INDEX);
            SelectTextDraw(playerid, -1);

            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_PLAYER_MENU:
        {
            if(p_temp[playerid][TextDrawPlayerMenu]) return 1;
            p_temp[playerid][TextDrawPlayerMenu] = true;
            Interface_Show(playerid, PLAYER_MENU_INDEX);
            SelectTextDraw(playerid, 0xFFFFFF95);

            Fix_TogglePlayerControllable(playerid, false);
        }
        case TD_ID_SERVICE_TUNE:
        {
            if(p_temp[playerid][TextDrawServiceTune]) return 1;
            HideTextDraw_Speedometr(playerid, true);
            Interface_Show(playerid, SERVICE_TUNE_INDEX);
            SelectTextDraw(playerid, 0xFFFFFF95);

            Fix_TogglePlayerControllable(playerid, false);
            p_temp[playerid][TextDrawServiceTune] = true;
        }
        case TD_ID_PIN_CODE:
        {
            if(p_temp[playerid][TextDrawPinCode]) return 1;
            Captcha_UpdateNumber(playerid);
            for(new i = 16; i != -1; i--)
            {
                TextDrawShowForPlayer(playerid, TD_PinCode[i]);
                if(i < 11) PlayerTextDrawShow(playerid, PTD_PinCode[playerid][i]);
            }
            SelectTextDraw(playerid, -8708097);
            p_temp[playerid][TextDrawPinCode] = true;
        }
        case TD_ID_SALARY:
        {
            if(p_info[playerid][p_settings][INTERFACE])
            {
                for(new i = 2; i != -1; i--) PlayerTextDrawShow(playerid, PTD_NewSalary[playerid][i]);
            }
            else
            {
                for(new i = 6; i != -1; i--) PlayerTextDrawShow(playerid, PTD_Salary[playerid][i]);
                PlayerTextDrawSetString(playerid, PTD_Salary[playerid][5], "Progress: 0");
                PlayerTextDrawSetString(playerid, PTD_Salary[playerid][6], "0$");
            }
        }
        case TD_ID_DICE:
        {
            for(new i; i < 15; i++) PlayerTextDrawShow(playerid, PTD_Dice[playerid][i]);
            SelectTextDraw(playerid, -389325313);
            p_temp[playerid][TextDrawCasinoUse] = true;
        }
        case TD_ID_SHOP:
        {
            //if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) HideTextDraw_Speedometr(playerid, true);
            for(new i; i < 11; i++) PlayerTextDrawShow(playerid, PTD_Shop[playerid][i]);
            SelectTextDraw(playerid, -389325313);

            Fix_TogglePlayerControllable(playerid, 0);
            p_temp[playerid][TextDrawShopUse] = true;
        }
        case TD_ID_SPEEDOMETER:
        {
            ShowTextDraw_Speedometr(playerid, true);
        }
        case TD_ID_CAPTURE:
        {
            if(p_temp[playerid][TextDrawCapture]) return 1;
            p_temp[playerid][TextDrawCapture] = true;
            for(new i; i < 15; i++)
            {
                if(i < 10) PlayerTextDrawShow(playerid, PTD_Capture[playerid][i]);
                TextDrawShowForPlayer(playerid, TD_Capture[i]);
            }
        }
        case TD_ID_RECON_INFO:
        {
            for(new i = 9; i != -1; i--) PlayerTextDrawShow(playerid, PTD_Recon[playerid][i]);
            for(new i = 38; i != 25; i--) TextDrawShowForPlayer(playerid, TD_Recon[i]);
        }
        case TD_ID_RECON_PANEL:
        {
            for(new i = 25; i != -1; i--) TextDrawShowForPlayer(playerid, TD_Recon[i]);
            SelectTextDraw(playerid, -8708097);
            p_temp[playerid][TextDrawReconUse] = true;
        }
        case TD_ID_MINI_GAMES:
        {
            CreateMiniGamesTD(playerid, 220+random(220), 120+random(120));
            SelectTextDraw(playerid, -8708097);
        }
        case TD_ID_PRESS_ALT:
        {
            TextDrawShowForPlayer(playerid, TD_PressALT);
        }
        case TD_ID_GPS:
        {
            TextDrawShowForPlayer(playerid, TD_GPS);
        }
        case TD_ID_GREEN_ZONE:
        {
            if(p_info[playerid][p_settings][INTERFACE]) TextDrawShowForPlayer(playerid, TD_NewGreenZone);
            else for(new i = 0; i < 3; i++) TextDrawShowForPlayer(playerid, TD_GreenZone[i]);
        }
        case TD_ID_LIST_PAGE:
        {
            new list_id = p_temp[playerid][list_type], count = GetMaxCountTDList(playerid, list_id);
            if(count == -1) return SendError(playerid, "Ќеизвестна€ ошибка: BUG-TDL003! ѕопробуйте еще раз.");
            for(new i = 27; i != -1; i--)
            {
                if(count < 10 && i >= 20) continue;
                TextDrawShowForPlayer(playerid, TD_ListPage[i]);
            }
            SelectTextDraw(playerid, 0x00000090);
            PlayerTextDrawShow(playerid, PTD_ListPage[playerid][20]);
            p_temp[playerid][TextDrawListUse] = true;
        }
        case TD_ID_CAPTCHA:
        {
            for(new i = 9; i != -1; i--) TextDrawShowForPlayer(playerid, TD_Captcha[i]);
            CreateCaptchaForPlayer(playerid);
        }
    }
    return 1;
}

HideTextDrawForPlayer(playerid, TD_ID)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    if(TD_ID != TD_ID_GREEN_ZONE && TD_ID != TD_ID_PRESS_ALT) Fix_TogglePlayerControllable(playerid, 1);
    switch(TD_ID)
    {
        case TD_ID_T_HUNTER_GAME:
        {
            if(!p_temp[playerid][TextDrawTHunterGame]) return 1;
            for(new i = 35; i != -1; i--)
            {
                PlayerTextDrawDestroy(playerid, PTD_THunterGame[playerid][i]);
                PTD_THunterGame[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
            CancelSelectTextDraw(playerid);
            ClearTHunterButton(playerid);
            p_temp[playerid][TextDrawTHunterGame] = false;
        }
        case TD_ID_T_HUNTER_GPS:
        {
            if(!p_temp[playerid][TextDrawTHunterGPS]) return 1;
            for(new i = 8; i != -1; i--)
            {
                PlayerTextDrawDestroy(playerid, PTD_THunterGPS[playerid][i]);
                PTD_THunterGPS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            }
            p_temp[playerid][TextDrawTHunterGPS] = false;
        }
        case TD_ID_ROBBING:
        {
            if(p_temp[playerid][TextDrawRobberyRobbing] == false) return 1;
            for(new i = 13; i != -1; i--)
            {
                if(PTD_Robbing[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Robbing[playerid][i]);
                    PTD_Robbing[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            ClearRobbingMiniGame(playerid);
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawRobberyRobbing] = false;
        }
        case TD_ID_CRAFT:
        {
            if(p_temp[playerid][TextDrawCraft] == false) return 1;
            for(new i = 25; i != -1; i--)
            {
                if(PTD_CraftMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_CraftMain[playerid][i]);
                    PTD_CraftMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                if(i < 8)
                {
                    if(PTD_CraftButtonItems[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_CraftButtonItems[playerid][i]);
                        PTD_CraftButtonItems[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_CraftButtonItemsName[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_CraftButtonItemsName[playerid][i]);
                        PTD_CraftButtonItemsName[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
                if(i < 5)
                {
                    if(PTD_CraftResources[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_CraftResources[playerid][i]);
                        PTD_CraftResources[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_CraftResourcesInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_CraftResourcesInfo[playerid][i]);
                        PTD_CraftResourcesInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_CraftInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_CraftInfo[playerid][i]);
                        PTD_CraftInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawCraft] = false;
        }
        case TD_ID_BATTLEPASS:
        {
            if(p_temp[playerid][TextDrawBattlePass] == false) return 1;
            for(new i = 17; i != -1; i--)
            {
                if(PTD_BattlePassMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_BattlePassMain[playerid][i]);
                    PTD_BattlePassMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                if(i < 8)
                {
                    if(PTD_BattlePassButton[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassButton[playerid][i]);
                        PTD_BattlePassButton[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
                if(i < 5)
                {
                    if(PTD_BattlePassInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassInfo[playerid][i]);
                        PTD_BattlePassInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
                if(i < 3)
                {
                    if(PTD_BattlePassRewardMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassRewardMain[playerid][i]);
                        PTD_BattlePassRewardMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassRewardButton[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassRewardButton[playerid][i]);
                        PTD_BattlePassRewardButton[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassRewardText[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassRewardText[playerid][i]);
                        PTD_BattlePassRewardText[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassRewardModel[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassRewardModel[playerid][i]);
                        PTD_BattlePassRewardModel[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassRewardInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassRewardInfo[playerid][i]);
                        PTD_BattlePassRewardInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassTaskMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassTaskMain[playerid][i]);
                        PTD_BattlePassTaskMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassTaskName[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassTaskName[playerid][i]);
                        PTD_BattlePassTaskName[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_BattlePassTaskInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_BattlePassTaskInfo[playerid][i]);
                        PTD_BattlePassTaskInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawBattlePass] = false;
        }
        case TD_ID_DAILY:
        {
            if(p_temp[playerid][TextDrawDaily] == false) return 1;
            for(new i = 7; i != -1; i--)
            {
                if(PTD_DailyButton[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_DailyButton[playerid][i]);
                    PTD_DailyButton[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                if(i < 3)
                {
                    if(PTD_DailyMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyMain[playerid][i]);
                        PTD_DailyMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_DailyRewardMain[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyRewardMain[playerid][i]);
                        PTD_DailyRewardMain[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_DailyRewardButton[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyRewardButton[playerid][i]);
                        PTD_DailyRewardButton[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_DailyRewardText[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyRewardText[playerid][i]);
                        PTD_DailyRewardText[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_DailyRewardModel[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyRewardModel[playerid][i]);
                        PTD_DailyRewardModel[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                    if(PTD_DailyRewardInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyRewardInfo[playerid][i]);
                        PTD_DailyRewardInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
                if(i < 2)
                {
                    if(PTD_DailyInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_DailyInfo[playerid][i]);
                        PTD_DailyInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawDaily] = false;
        }
        case TD_ID_ELECTRIC:
        {
            if(p_temp[playerid][TextDrawElectric] == false) return 1;
            for(new i = 13; i != -1; i--)
            {
                if(PTD_Electric[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Electric[playerid][i]);
                    PTD_Electric[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            ClearElectricMiniGame(playerid);
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawElectric] = false;
        }
        case TD_ID_RADIO:
        {
            if(p_temp[playerid][TextDrawRadio] == false) return 1;
            for(new i = 34; i != -1; i--)
            {
                if(PTD_Radio[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Radio[playerid][i]);
                    PTD_Radio[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            //ClearElectricMiniGame(playerid);
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawRadio] = false;
        }
        case TD_ID_INVENTORY_PLAYER:
        {
            if(p_temp[playerid][TextDrawInventory] == false) return 1;
            for(new i = 55; i != -1; i--)
            {
                if(PTD_EquipmentRight[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_EquipmentRight[playerid][i]);
                    PTD_EquipmentRight[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }

            for(new i = 29; i != -1; i--)
            {
                if(PTD_EquipmentPersonInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_EquipmentPersonInfo[playerid][i]);
                    PTD_EquipmentPersonInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            Equipment_DestroyMenu(playerid);
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawInventory] =
            p_temp[playerid][TextDrawTrade] =
            p_temp[playerid][TextDrawEquipment] =
            p_temp[playerid][Equipment_Settings] = false;

            DeletePVar(playerid, #VEHICLEID_ACCESSORIES);
        }
        case TD_ID_TRADE, TD_ID_MARKET, TD_ID_INVENTORY_OTHER:
        {
            if( p_temp[playerid][TextDrawEquipment] == false) return 1;

            for(new i = 55; i != -1; i--)
            {
                if(PTD_EquipmentRight[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_EquipmentRight[playerid][i]);
                    PTD_EquipmentRight[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }

            for(new i = 53; i != -1; i--)
            {
                if(PTD_EquipmentLeft[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_EquipmentLeft[playerid][i]);
                    PTD_EquipmentLeft[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            Equipment_DestroyMenu(playerid);
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawInventory] =
            p_temp[playerid][TextDrawTrade] =
            p_temp[playerid][TextDrawMarket] =
            p_temp[playerid][TextDrawEquipment] =
            p_temp[playerid][Equipment_Settings] = false;

            if(EQUIPMENT_INVENTORY_PLAYER < p_temp[playerid][InterfaceID] < EQUIPMENT_INVENTORY_ALL ||
                p_temp[playerid][InterfaceID] == MARKET_SELL ||
                p_temp[playerid][InterfaceID] == MARKET_BUY)
            {
                ClearPlayerMarketUse(playerid);
                p_temp[playerid][InterfaceID] = INTARFACE_ID_NONE;
            }
            DeletePVar(playerid, #VEHICLEID_BOOT);
        }
        case TD_ID_DONATE_INFO:
        {
            if(p_temp[playerid][TextDrawDonateInfo] == false) return 1;
            for(new i = 38; i != -1; i--)
            {
                if(PTD_DonateInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_DonateInfo[playerid][i]);
                    PTD_DonateInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawDonateInfo] = false;
        }
        case TD_ID_PANEL:
        {
            if(p_temp[playerid][TextDrawPanel] == false) return 1;
            for(new i = 18; i != -1; i--)
            {
                if(PTD_Panel[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Panel[playerid][i]);
                    PTD_Panel[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawPanel] = false;
        }
        case TD_ID_LOGO:
        {
            for(new i = 0; i < 16; i++)
            {
                //TextDrawHideForPlayer(playerid, TD_Logo_Donate[i]);
                if(i < 15) TextDrawHideForPlayer(playerid, TD_Logo_Default[i]);
            }
        }
        case TD_ID_PHONE:
        {
            if(p_temp[playerid][TextDrawPhone] == false) return 1;
            for(new i = 6; i != -1; i--)
            {
                if(PTD_Phone[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Phone[playerid][i]);
                    PTD_Phone[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawPhone] = false;
        }
        case TD_ID_CASE:
        {
            if(p_temp[playerid][TextDrawCase] == false) return 1;
            for(new i = 57; i != -1; i--)
            {
                if(PTD_Case[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Case[playerid][i]);
                    PTD_Case[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawCase] = false;
        }
        case TD_ID_ROULETTE:
        {
            if(p_temp[playerid][TextDrawRoulette] == false) return 1;
            for(new i = 57; i != -1; i--)
            {
                if(PTD_Roulette[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Roulette[playerid][i]);
                    PTD_Roulette[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawRoulette] = false;
        }
        case TD_ID_PLAYER_MENU:
        {
            if(p_temp[playerid][TextDrawPlayerMenu] == false) return 1;
            for(new i = MAX_TD_PLAYER_MENU-1; i != -1; i--)
            {
                if(PTD_PlayerMenu[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_PlayerMenu[playerid][i]);
                    PTD_PlayerMenu[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawPlayerMenu] = false;
        }
        case TD_ID_SERVICE_TUNE:
        {
            if(!p_temp[playerid][TextDrawServiceTune]) return 1;
            for(new i = 19; i != -1; i--)
            {
                if(PTD_ServiceTune[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_ServiceTune[playerid][i]);
                    PTD_ServiceTune[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                if(i < 16) TextDrawHideForPlayer(playerid, TD_ServiceTune[i]);
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawServiceTune] = false;

            ShowTextDraw_Speedometr(playerid, true);
        }
        case TD_ID_PIN_CODE:
        {
            if(!p_temp[playerid][TextDrawPinCode]) return 1;
            for(new i = 16; i != -1; i--)
            {
                TextDrawHideForPlayer(playerid, TD_PinCode[i]);
                if(i < 11 && PTD_PinCode[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_PinCode[playerid][i]);
                    PTD_PinCode[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            p_temp[playerid][TextDrawPinCode] = false;
            CancelSelectTextDraw(playerid);
        }
        case TD_ID_SALARY:
        {
            if(p_info[playerid][p_settings][INTERFACE])
            {
                for(new i = 2; i != -1; i--)
                {
                    if(PTD_NewSalary[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_NewSalary[playerid][i]);
                        PTD_NewSalary[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
            }
            else
            {
                for(new i = 6; i != -1; i--)
                {
                    if(PTD_Salary[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                    {
                        PlayerTextDrawDestroy(playerid, PTD_Salary[playerid][i]);
                        PTD_Salary[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    }
                }
            }
        }
        case TD_ID_DICE:
        {
            if(p_temp[playerid][TextDrawCasinoUse] == false) return 1;
            for(new i; i < 15; i++)
            {
                if(PTD_Dice[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Dice[playerid][i]);
                    PTD_Dice[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawCasinoUse] = false;
        }
        case TD_ID_SHOP:
        {
            if(!p_temp[playerid][TextDrawShopUse]) return 1;
            //if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) ShowTextDraw_Speedometr(playerid, true);
            for(new i; i < 11; i++)
            {
                if(PTD_Shop[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Shop[playerid][i]);
                    PTD_Shop[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawShopUse] = false;
        }
        case TD_ID_SPEEDOMETER:
        {
            HideTextDraw_Speedometr(playerid, true);
        }
        case TD_ID_CAPTURE:
        {
            if(!p_temp[playerid][TextDrawCapture]) return 1;
            for(new i = 14; i != -1; i--)
            {
                if(i < 10 && PTD_Capture[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Capture[playerid][i]);
                    PTD_Capture[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                TextDrawHideForPlayer(playerid, TD_Capture[i]);
            }
            p_temp[playerid][TextDrawCapture] = false;
        }
        case TD_ID_RECON_INFO:
        {
            for(new i = 9; i != -1; i--)
            {
                if(PTD_Recon[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_Recon[playerid][i]);
                    PTD_Recon[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
            }
            for(new i = 38; i != 25; i--) TextDrawHideForPlayer(playerid, TD_Recon[i]);
        }
        case TD_ID_RECON_PANEL:
        {
            if(p_temp[playerid][TextDrawReconUse] == false) return 1;
            for(new i = 25; i != -1; i--) TextDrawHideForPlayer(playerid, TD_Recon[i]);
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawReconUse] = false;
        }
        case TD_ID_MINI_GAMES:
        {
            if(PTD_MiniGames[playerid] != PlayerText:INVALID_TEXT_DRAW)
            {
                PlayerTextDrawDestroy(playerid, PTD_MiniGames[playerid]);
                PTD_MiniGames[playerid] = PlayerText:INVALID_TEXT_DRAW;
            }
            CancelSelectTextDraw(playerid);
        }
        case TD_ID_PRESS_ALT:
        {
            TextDrawHideForPlayer(playerid, TD_PressALT);
        }
        case TD_ID_GPS:
        {
            TextDrawHideForPlayer(playerid, TD_GPS);
        }
        case TD_ID_GREEN_ZONE:
        {
            if(p_info[playerid][p_settings][INTERFACE]) TextDrawHideForPlayer(playerid, TD_NewGreenZone);
            else for(new i = 0; i < 3; i++) TextDrawHideForPlayer(playerid, TD_GreenZone[i]);
        }
        case TD_ID_LIST_PAGE:
        {
            if(p_temp[playerid][TextDrawListUse] == false) return 1;
            for(new i= 30; i != -1; i--)
            {
                if(PTD_ListPage[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
                {
                    PlayerTextDrawDestroy(playerid, PTD_ListPage[playerid][i]);
                    PTD_ListPage[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                if(i < 28) TextDrawHideForPlayer(playerid, TD_ListPage[i]);
            }
            CancelSelectTextDraw(playerid);
            p_temp[playerid][TextDrawListUse] = false;
        }
        case TD_ID_CAPTCHA:
        {
            if(!p_temp[playerid][TextDrawCaptcha]) return 1;
            for(new i = 9; i != -1; i--) 
            {
                if(i <= 5) PlayerTextDrawDestroy(playerid, PTD_Captcha[playerid][i]);
                TextDrawHideForPlayer(playerid, TD_Captcha[i]);
            }
            p_temp[playerid][TextDrawCaptcha] = 0;
        }
    }
    return 1;
}

CreateTextDrawForPlayer(playerid, TD_ID)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    switch(TD_ID)
    {
        case TD_ID_T_HUNTER_GAME:
        {
            if(p_temp[playerid][TextDrawTHunterGame]) return 1;
            PTD_THunterGame[playerid][0] = CreatePlayerTextDraw(playerid, 201.1006, 74.5465, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][0], 235.2180, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][0], -3073537);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][0], 0);

            PTD_THunterGame[playerid][1] = CreatePlayerTextDraw(playerid, 201.1006, 80.5465, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][1], 235.2180, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][1], -2739457);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][1], 0);

            PTD_THunterGame[playerid][2] = CreatePlayerTextDraw(playerid, 201.1006, 86.5471, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][2], 235.2180, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][2], -2405377);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][2], 0);

            PTD_THunterGame[playerid][3] = CreatePlayerTextDraw(playerid, 318.8663, 79.0545, "MEПAЗЗOЕCKAПEЗТ");
            PlayerTextDrawLetterSize(playerid, PTD_THunterGame[playerid][3], 0.2150, 1.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][3], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][3], 2);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][3], 1);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][3], 0);

            PTD_THunterGame[playerid][4] = CreatePlayerTextDraw(playerid, 201.1006, 92.6547, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][4], 235.2180, 281.9363);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][4], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][4], 0);

            PTD_THunterGame[playerid][5] = CreatePlayerTextDraw(playerid, 203.0502, 103.4220, "LD_SPAC:white");
            PTD_THunterGame[playerid][6] = CreatePlayerTextDraw(playerid, 249.6528, 103.4220, "LD_SPAC:white");
            PTD_THunterGame[playerid][7] = CreatePlayerTextDraw(playerid, 296.2557, 103.4220, "LD_SPAC:white");
            PTD_THunterGame[playerid][8] = CreatePlayerTextDraw(playerid, 342.8586, 103.4220, "LD_SPAC:white");
            PTD_THunterGame[playerid][9] = CreatePlayerTextDraw(playerid, 389.4613, 103.4220, "LD_SPAC:white");
            PTD_THunterGame[playerid][10] = CreatePlayerTextDraw(playerid, 203.0502, 150.0232, "LD_SPAC:white");
            PTD_THunterGame[playerid][11] = CreatePlayerTextDraw(playerid, 249.6528, 150.0232, "LD_SPAC:white");
            PTD_THunterGame[playerid][12] = CreatePlayerTextDraw(playerid, 296.2557, 150.0232, "LD_SPAC:white");
            PTD_THunterGame[playerid][13] = CreatePlayerTextDraw(playerid, 342.8586, 150.0232, "LD_SPAC:white");
            PTD_THunterGame[playerid][14] = CreatePlayerTextDraw(playerid, 389.4613, 150.0232, "LD_SPAC:white");
            PTD_THunterGame[playerid][15] = CreatePlayerTextDraw(playerid, 203.0502, 196.6260, "LD_SPAC:white");
            PTD_THunterGame[playerid][16] = CreatePlayerTextDraw(playerid, 249.6528, 196.6260, "LD_SPAC:white");
            PTD_THunterGame[playerid][17] = CreatePlayerTextDraw(playerid, 296.2557, 196.6260, "LD_SPAC:white");
            PTD_THunterGame[playerid][18] = CreatePlayerTextDraw(playerid, 342.8586, 196.6260, "LD_SPAC:white");
            PTD_THunterGame[playerid][19] = CreatePlayerTextDraw(playerid, 389.4613, 196.6260, "LD_SPAC:white");
            PTD_THunterGame[playerid][20] = CreatePlayerTextDraw(playerid, 203.0502, 243.2291, "LD_SPAC:white");
            PTD_THunterGame[playerid][21] = CreatePlayerTextDraw(playerid, 249.6528, 243.2291, "LD_SPAC:white");
            PTD_THunterGame[playerid][22] = CreatePlayerTextDraw(playerid, 296.2557, 243.2291, "LD_SPAC:white");
            PTD_THunterGame[playerid][23] = CreatePlayerTextDraw(playerid, 342.8586, 243.2291, "LD_SPAC:white");
            PTD_THunterGame[playerid][24] = CreatePlayerTextDraw(playerid, 389.4613, 243.2291, "LD_SPAC:white");
            PTD_THunterGame[playerid][25] = CreatePlayerTextDraw(playerid, 203.0502, 289.8317, "LD_SPAC:white");
            PTD_THunterGame[playerid][26] = CreatePlayerTextDraw(playerid, 249.6528, 289.8317, "LD_SPAC:white");
            PTD_THunterGame[playerid][27] = CreatePlayerTextDraw(playerid, 296.2557, 289.8317, "LD_SPAC:white");
            PTD_THunterGame[playerid][28] = CreatePlayerTextDraw(playerid, 342.8586, 289.8317, "LD_SPAC:white");
            PTD_THunterGame[playerid][29] = CreatePlayerTextDraw(playerid, 389.4613, 289.8317, "LD_SPAC:white");

            for(new i = 5; i < 30; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][i], 45.0000, 45.0000);
                PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][i], 454761471);
                PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][i], true);
            }

            PTD_THunterGame[playerid][30] = CreatePlayerTextDraw(playerid, 203.0829, 345.3932, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][30], 46.8693, 27.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][30], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][30], -715897601);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][30], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][30], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][30], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][30], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][30], true);

            PTD_THunterGame[playerid][31] = CreatePlayerTextDraw(playerid, 226.7610, 351.9636, "ЕHБO");
            PlayerTextDrawLetterSize(playerid, PTD_THunterGame[playerid][31], 0.3000, 1.3947);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][31], 2);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][31], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][31], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][31], 2);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][31], 1);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][31], 0);

            PTD_THunterGame[playerid][32] = CreatePlayerTextDraw(playerid, 387.6947, 345.3932, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][32], 46.8693, 27.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][32], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][32], -715897601);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][32], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][32], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][32], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][32], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_THunterGame[playerid][32], true);

            PTD_THunterGame[playerid][33] = CreatePlayerTextDraw(playerid, 411.3728, 351.7635, "ЛСXOГ");
            PlayerTextDrawLetterSize(playerid, PTD_THunterGame[playerid][33], 0.3000, 1.3947);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][33], 2);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][33], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][33], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][33], 2);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][33], 1);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][33], 0);

            PTD_THunterGame[playerid][34] = CreatePlayerTextDraw(playerid, 201.1504, 95.0990, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][34], 235.2248, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][34], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][34], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][34], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][34], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][34], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][34], 0);

            PTD_THunterGame[playerid][35] = CreatePlayerTextDraw(playerid, 201.1504, 337.2133, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGame[playerid][35], 235.2248, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGame[playerid][35], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGame[playerid][35], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGame[playerid][35], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGame[playerid][35], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGame[playerid][35], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGame[playerid][35], 0);
            return 1;
        }
        case TD_ID_T_HUNTER_GPS:
        {
            if(p_temp[playerid][TextDrawTHunterGPS]) return 1;
            PTD_THunterGPS[playerid][0] = CreatePlayerTextDraw(playerid, 540.7005, 151.0686, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][0], 95.0000, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][0], -3073537);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][0], 0);

            PTD_THunterGPS[playerid][1] = CreatePlayerTextDraw(playerid, 540.7005, 157.0691, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][1], 95.0000, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][1], -2739457);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][1], 0);

            PTD_THunterGPS[playerid][2] = CreatePlayerTextDraw(playerid, 540.7005, 163.0693, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][2], 95.0000, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][2], -2405377);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][2], 0);

            PTD_THunterGPS[playerid][3] = CreatePlayerTextDraw(playerid, 588.1618, 155.5767, "MEПAЗЗOЕCKAПEЗТ");
            PlayerTextDrawLetterSize(playerid, PTD_THunterGPS[playerid][3], 0.2150, 1.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][3], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][3], 2);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][3], 1);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][3], 0);

            PTD_THunterGPS[playerid][4] = CreatePlayerTextDraw(playerid, 540.7005, 169.1770, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][4], 95.0000, 45.4880);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][4], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][4], 0);

            PTD_THunterGPS[playerid][5] = CreatePlayerTextDraw(playerid, 542.7495, 179.9445, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][5], 90.9794, 24.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][5], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][5], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][5], 0);

            PTD_THunterGPS[playerid][6] = CreatePlayerTextDraw(playerid, 589.4154, 185.5962, "Distance:_0.0");
            PlayerTextDrawLetterSize(playerid, PTD_THunterGPS[playerid][6], 0.1800, 1.2201);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][6], 2);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][6], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][6], 2);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][6], 1);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][6], 0);

            PTD_THunterGPS[playerid][7] = CreatePlayerTextDraw(playerid, 540.7009, 171.4544, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][7], 95.0000, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][7], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][7], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][7], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][7], 0);

            PTD_THunterGPS[playerid][8] = CreatePlayerTextDraw(playerid, 540.7009, 206.1690, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_THunterGPS[playerid][8], 95.0000, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_THunterGPS[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_THunterGPS[playerid][8], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_THunterGPS[playerid][8], 255);
            PlayerTextDrawFont(playerid, PTD_THunterGPS[playerid][8], 4);
            PlayerTextDrawSetProportional(playerid, PTD_THunterGPS[playerid][8], 0);
            PlayerTextDrawSetShadow(playerid, PTD_THunterGPS[playerid][8], 0);
        }
        case TD_ID_ROBBING:
        {
            if(p_temp[playerid][TextDrawRobberyRobbing]) return 1;
            PTD_Robbing[playerid][0] = CreatePlayerTextDraw(playerid, 209.5361, 181.1322, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Robbing[playerid][0], 200.0000, 200.0000);
            PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Robbing[playerid][0], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Robbing[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][0], 0);

            PTD_Robbing[playerid][1] = CreatePlayerTextDraw(playerid, 399.5793, 151.6369, "LD_BEAT:chit");
            PlayerTextDrawTextSize(playerid, PTD_Robbing[playerid][1], 35.0000, 35.0000);
            PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Robbing[playerid][1], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Robbing[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][1], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Robbing[playerid][1], true);

            PTD_Robbing[playerid][2] = CreatePlayerTextDraw(playerid, 417.4963, 160.2781, "X");
            PlayerTextDrawLetterSize(playerid, PTD_Robbing[playerid][2], 0.3853, 1.7108);
            PlayerTextDrawTextSize(playerid, PTD_Robbing[playerid][2], 0.0000, 79.0000);
            PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][2], 2);
            PlayerTextDrawColor(playerid, PTD_Robbing[playerid][2], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Robbing[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][2], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][2], 0);

            PTD_Robbing[playerid][3] = CreatePlayerTextDraw(playerid, 209.5361, 206.5370, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Robbing[playerid][3], 200.0000, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_Robbing[playerid][3], -2139062240);
            PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Robbing[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][3], 0);

            PTD_Robbing[playerid][4] = CreatePlayerTextDraw(playerid, 311.4331, 212.8961, "HAДMЕПE:_W");
            PlayerTextDrawLetterSize(playerid, PTD_Robbing[playerid][4], 0.2169, 1.4752);
            PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_Robbing[playerid][4], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Robbing[playerid][4], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][4], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][4], 0);

            PTD_Robbing[playerid][5] = CreatePlayerTextDraw(playerid, 272.0822, 162.8591, "");
            PlayerTextDrawTextSize(playerid, PTD_Robbing[playerid][5], 76.0000, 61.0000);
            PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Robbing[playerid][5], -4632577);
            PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][5], -256);
            PlayerTextDrawFont(playerid, PTD_Robbing[playerid][5], 5);
            PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][5], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_Robbing[playerid][5], 19804);
            PlayerTextDrawSetPreviewRot(playerid, PTD_Robbing[playerid][5], 0.0000, 0.0000, 0.0000, 1.7000);

            PTD_Robbing[playerid][6] = CreatePlayerTextDraw(playerid, 249.2698, 245.2174, "LD_SPAC:white");
            PTD_Robbing[playerid][7] = CreatePlayerTextDraw(playerid, 322.2742, 245.2174, "LD_SPAC:white");
            PTD_Robbing[playerid][8] = CreatePlayerTextDraw(playerid, 249.2698, 320.5220, "LD_SPAC:white");
            PTD_Robbing[playerid][9] = CreatePlayerTextDraw(playerid, 322.2742, 320.5220, "LD_SPAC:white");

            for(new i = 6; i < 10; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_Robbing[playerid][i], 50.0000, 50.0000);
                PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_Robbing[playerid][i], -2139062240);
                PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_Robbing[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_Robbing[playerid][i], true);
            }

            PTD_Robbing[playerid][10] = CreatePlayerTextDraw(playerid, 274.7502, 248.8554, "W");
            PTD_Robbing[playerid][11] = CreatePlayerTextDraw(playerid, 348.3547, 248.8554, "A");
            PTD_Robbing[playerid][12] = CreatePlayerTextDraw(playerid, 274.7502, 324.1600, "S");
            PTD_Robbing[playerid][13] = CreatePlayerTextDraw(playerid, 348.3547, 324.1600, "D");

            for(new i = 10; i < 14; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_Robbing[playerid][i], 0.8884, 4.2232);
                PlayerTextDrawAlignment(playerid, PTD_Robbing[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_Robbing[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_Robbing[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_Robbing[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_Robbing[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_Robbing[playerid][i], 0);
            }
        }
        case TD_ID_CRAFT:
        {
            if(p_temp[playerid][TextDrawCraft]) return 1;
            PTD_CraftMain[playerid][0] = CreatePlayerTextDraw(playerid, 174.2173, 85.7667, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][0], 285.0000, 285.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][0], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][0], 0);

            PTD_CraftMain[playerid][1] = CreatePlayerTextDraw(playerid, 450.6659, 56.7923, "LD_BEAT:chit"); // «акрыть;
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][1], 35.0000, 35.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][1], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][1], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][1], true);

            PTD_CraftMain[playerid][2] = CreatePlayerTextDraw(playerid, 468.5830, 65.4328, "X");
            PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][2], 0.3854, 1.7108);
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][2], 0.0000, 79.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][2], 2);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][2], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][2], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][2], 0);

            PTD_CraftMain[playerid][3] = CreatePlayerTextDraw(playerid, 174.0832, 111.1697, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][3], 285.2502, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][3], -2139062240);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][3], 0);

            PTD_CraftMain[playerid][4] = CreatePlayerTextDraw(playerid, 176.9167, 114.3627, "LD_SPAC:white"); // јксессуары;
            PTD_CraftMain[playerid][5] = CreatePlayerTextDraw(playerid, 247.0209, 114.3627, "LD_SPAC:white"); // ќдежда;
            PTD_CraftMain[playerid][6] = CreatePlayerTextDraw(playerid, 317.1253, 114.3627, "LD_SPAC:white"); // ’ими€;
            PTD_CraftMain[playerid][7] = CreatePlayerTextDraw(playerid, 387.2296, 114.3627, "LD_SPAC:white"); // ќстальное;

            for(new i = 4; i < 8; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][i], 69.0000, 22.0000);
                PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][i], -1061109728);
                PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][i], true);
            }

            PTD_CraftMain[playerid][8] = CreatePlayerTextDraw(playerid, 211.7167, 118.2443, "AKCECCYAPС");
            PTD_CraftMain[playerid][9] = CreatePlayerTextDraw(playerid, 282.0209, 118.2443, "OГEДГA");
            PTD_CraftMain[playerid][10] = CreatePlayerTextDraw(playerid, 352.3251, 118.2443, "XЕMЕХ");
            PTD_CraftMain[playerid][11] = CreatePlayerTextDraw(playerid, 422.6296, 118.2443, "OCПAЗТHOE");

            for(new i = 8; i < 12; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][i], 0.2169, 1.4752);
                PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][i], 0);
            }

            PTD_CraftMain[playerid][12] = CreatePlayerTextDraw(playerid, 177.7332, 142.8739, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][12], 120.0000, 223.0498);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][12], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][12], -256);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][12], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][12], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][12], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][12], 0);

            PTD_CraftMain[playerid][13] = CreatePlayerTextDraw(playerid, 301.5407, 142.7924, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][13], 154.2409, 223.1703);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][13], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][13], -256);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][13], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][13], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][13], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][13], 0);

            PTD_CraftMain[playerid][14] = CreatePlayerTextDraw(playerid, 200.7297, 336.8835, "LD_SPAC:white"); // ѕредыдуща€ страница;
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][14], 25.0000, 25.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][14], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][14], -1061109728);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][14], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][14], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][14], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][14], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][14], true);

            PTD_CraftMain[playerid][15] = CreatePlayerTextDraw(playerid, 249.9328, 336.8835, "LD_SPAC:white"); // —ледующа€ страница;
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][15], 25.0000, 25.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][15], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][15], -1061109728);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][15], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][15], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][15], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][15], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][15], true);

            PTD_CraftMain[playerid][16] = CreatePlayerTextDraw(playerid, 206.4333, 340.3887, "<<");
            PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][16], 0.2433, 1.9629);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][16], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][16], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][16], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][16], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][16], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][16], 0);

            PTD_CraftMain[playerid][17] = CreatePlayerTextDraw(playerid, 257.4530, 340.3887, ">>");
            PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][17], 0.2433, 1.9629);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][17], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][17], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][17], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][17], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][17], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][17], 0);

            PTD_CraftMain[playerid][18] = CreatePlayerTextDraw(playerid, 342.7698, 146.5220, "");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][18], 70.0000, 70.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][18], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][18], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][18], -2139062240);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][18], 5);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][18], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][18], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_CraftMain[playerid][18], 18631);
            PlayerTextDrawSetPreviewRot(playerid, PTD_CraftMain[playerid][18], 0.0000, 0.0000, 0.0000, 1.0000);
            PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][18], true);

            PTD_CraftMain[playerid][19] = CreatePlayerTextDraw(playerid, 306.1875, 230.2904, "ПPEАOЛAHЕE:");
            PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][19], 0.1985, 1.4493);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][19], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][19], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][19], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][19], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][19], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][19], 0);

            PTD_CraftMain[playerid][20] = CreatePlayerTextDraw(playerid, 306.6040, 319.0957, "KOЗЕНECПЛO:");
            PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][20], 0.1985, 1.4493);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][20], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][20], -3394561);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][20], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][20], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][20], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][20], 0);

            PTD_CraftMain[playerid][21] = CreatePlayerTextDraw(playerid, 363.8800, 315.7814, "LD_SPAC:white"); //  оличество - кнопка;
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][21], 89.0000, 22.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][21], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][21], -1061109728);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][21], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][21], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][21], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][21], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][21], true);

            PTD_CraftMain[playerid][22] = CreatePlayerTextDraw(playerid, 305.1794, 340.5014, "LD_SPAC:white"); // »зготовить;
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][22], 147.6201, 22.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][22], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][22], -1061109728);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][22], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][22], 4);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][22], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][22], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_CraftMain[playerid][22], true);

            PTD_CraftMain[playerid][23] = CreatePlayerTextDraw(playerid, 380.1163, 343.2813, "ЕИВOПOЛЕПТ");
            PlayerTextDrawLetterSize(playerid, PTD_CraftMain[playerid][23], 0.4000, 1.6000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][23], 2);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][23], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][23], 255);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][23], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][23], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][23], 0);

            PTD_CraftMain[playerid][24] = CreatePlayerTextDraw(playerid, 271.7500, 53.4701, "");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][24], 90.0000, 90.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][24], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][24], -4632577);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][24], -256);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][24], 5);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][24], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][24], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_CraftMain[playerid][24], 19627);
            PlayerTextDrawSetPreviewRot(playerid, PTD_CraftMain[playerid][24], 90.0000, 0.0000, -25.0000, 1.7000);

            PTD_CraftMain[playerid][25] = CreatePlayerTextDraw(playerid, 271.7500, 53.4701, "");
            PlayerTextDrawTextSize(playerid, PTD_CraftMain[playerid][25], 90.0000, 90.0000);
            PlayerTextDrawAlignment(playerid, PTD_CraftMain[playerid][25], 1);
            PlayerTextDrawColor(playerid, PTD_CraftMain[playerid][25], -4632577);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftMain[playerid][25], -256);
            PlayerTextDrawFont(playerid, PTD_CraftMain[playerid][25], 5);
            PlayerTextDrawSetProportional(playerid, PTD_CraftMain[playerid][25], 0);
            PlayerTextDrawSetShadow(playerid, PTD_CraftMain[playerid][25], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_CraftMain[playerid][25], 19627);
            PlayerTextDrawSetPreviewRot(playerid, PTD_CraftMain[playerid][25], 90.0000, 0.0000, 25.0000, 1.7000);

            PTD_CraftButtonItems[playerid][0] = CreatePlayerTextDraw(playerid, 180.7796, 146.5294, "LD_SPAC:white"); // ѕредмет #1;
            PTD_CraftButtonItems[playerid][1] = CreatePlayerTextDraw(playerid, 180.7796, 169.9308, "LD_SPAC:white"); // ѕредмет #2;
            PTD_CraftButtonItems[playerid][2] = CreatePlayerTextDraw(playerid, 180.7796, 193.3321, "LD_SPAC:white"); // ѕредмет #3;
            PTD_CraftButtonItems[playerid][3] = CreatePlayerTextDraw(playerid, 180.7796, 216.7335, "LD_SPAC:white"); // ѕредмет #4;
            PTD_CraftButtonItems[playerid][4] = CreatePlayerTextDraw(playerid, 180.7796, 240.1349, "LD_SPAC:white"); // ѕредмет #5;
            PTD_CraftButtonItems[playerid][5] = CreatePlayerTextDraw(playerid, 180.7796, 263.5364, "LD_SPAC:white"); // ѕредмет #6;
            PTD_CraftButtonItems[playerid][6] = CreatePlayerTextDraw(playerid, 180.7796, 286.9378, "LD_SPAC:white"); // ѕредмет #7;
            PTD_CraftButtonItems[playerid][7] = CreatePlayerTextDraw(playerid, 180.7796, 310.3392, "LD_SPAC:white"); // ѕредмет #8;

            for(new i = 0; i < 8; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_CraftButtonItems[playerid][i], 114.0102, 22.0000);
                PlayerTextDrawAlignment(playerid, PTD_CraftButtonItems[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_CraftButtonItems[playerid][i], -1061109728);
                PlayerTextDrawBackgroundColor(playerid, PTD_CraftButtonItems[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_CraftButtonItems[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_CraftButtonItems[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_CraftButtonItems[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_CraftButtonItems[playerid][i], true);
            }

            PTD_CraftButtonItemsName[playerid][0] = CreatePlayerTextDraw(playerid, 183.7498, 149.9371, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #1;
            PTD_CraftButtonItemsName[playerid][1] = CreatePlayerTextDraw(playerid, 183.7498, 173.2384, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #2;
            PTD_CraftButtonItemsName[playerid][2] = CreatePlayerTextDraw(playerid, 183.7498, 196.5399, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #3;
            PTD_CraftButtonItemsName[playerid][3] = CreatePlayerTextDraw(playerid, 183.7498, 219.8412, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #4;
            PTD_CraftButtonItemsName[playerid][4] = CreatePlayerTextDraw(playerid, 183.7498, 243.1427, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #5;
            PTD_CraftButtonItemsName[playerid][5] = CreatePlayerTextDraw(playerid, 183.7498, 266.4440, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #6;
            PTD_CraftButtonItemsName[playerid][6] = CreatePlayerTextDraw(playerid, 183.7498, 289.7455, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #7;
            PTD_CraftButtonItemsName[playerid][7] = CreatePlayerTextDraw(playerid, 183.7498, 313.0469, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета #8;

            for(new i = 0; i < 8; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_CraftButtonItemsName[playerid][i], 0.1465, 1.4792);
                PlayerTextDrawAlignment(playerid, PTD_CraftButtonItemsName[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_CraftButtonItemsName[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_CraftButtonItemsName[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_CraftButtonItemsName[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_CraftButtonItemsName[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_CraftButtonItemsName[playerid][i], 0);
            }

            PTD_CraftInfo[playerid][0] = CreatePlayerTextDraw(playerid, 238.1333, 342.2073, "1/1"); // Ќомер страницы;
            PlayerTextDrawLetterSize(playerid, PTD_CraftInfo[playerid][0], 0.2987, 1.3614);
            PlayerTextDrawAlignment(playerid, PTD_CraftInfo[playerid][0], 2);
            PlayerTextDrawColor(playerid, PTD_CraftInfo[playerid][0], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftInfo[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_CraftInfo[playerid][0], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftInfo[playerid][0], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftInfo[playerid][0], 0);

            PTD_CraftInfo[playerid][1] = CreatePlayerTextDraw(playerid, 378.7500, 217.4812, "CMAИKA_ГЗХ_PAИВOHA_ЛЕГEOKAPПС"); // Ќазвание предмета, который изготавливаетс€;
            PlayerTextDrawLetterSize(playerid, PTD_CraftInfo[playerid][1], 0.1985, 1.4493);
            PlayerTextDrawAlignment(playerid, PTD_CraftInfo[playerid][1], 2);
            PlayerTextDrawColor(playerid, PTD_CraftInfo[playerid][1], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftInfo[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_CraftInfo[playerid][1], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftInfo[playerid][1], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftInfo[playerid][1], 0);

            PTD_CraftInfo[playerid][2] = CreatePlayerTextDraw(playerid, 306.1875, 279.5932, "CПOЕMOCПТ:_2500$"); // —тоимость;
            PlayerTextDrawLetterSize(playerid, PTD_CraftInfo[playerid][2], 0.1985, 1.4493);
            PlayerTextDrawAlignment(playerid, PTD_CraftInfo[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_CraftInfo[playerid][2], 1724645631);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftInfo[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_CraftInfo[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftInfo[playerid][2], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftInfo[playerid][2], 0);

            PTD_CraftInfo[playerid][3] = CreatePlayerTextDraw(playerid, 378.7500, 296.1860, "ОAHC_YCМEXA:_20%_(+40%)"); // Ўанс успеха;
            PlayerTextDrawLetterSize(playerid, PTD_CraftInfo[playerid][3], 0.1985, 1.4493);
            PlayerTextDrawAlignment(playerid, PTD_CraftInfo[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_CraftInfo[playerid][3], 10092543);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftInfo[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_CraftInfo[playerid][3], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftInfo[playerid][3], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftInfo[playerid][3], 0);

            PTD_CraftInfo[playerid][4] = CreatePlayerTextDraw(playerid, 368.6245, 319.0957, "1000"); //  оличество;
            PlayerTextDrawLetterSize(playerid, PTD_CraftInfo[playerid][4], 0.1985, 1.4493);
            PlayerTextDrawAlignment(playerid, PTD_CraftInfo[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_CraftInfo[playerid][4], 1724645631);
            PlayerTextDrawBackgroundColor(playerid, PTD_CraftInfo[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_CraftInfo[playerid][4], 2);
            PlayerTextDrawSetProportional(playerid, PTD_CraftInfo[playerid][4], 1);
            PlayerTextDrawSetShadow(playerid, PTD_CraftInfo[playerid][4], 0);

            PTD_CraftResources[playerid][0] = CreatePlayerTextDraw(playerid, 305.2828, 247.1996, ""); // –есурс #1;
            PTD_CraftResources[playerid][1] = CreatePlayerTextDraw(playerid, 334.9848, 247.1996, ""); // –есурс #2;
            PTD_CraftResources[playerid][2] = CreatePlayerTextDraw(playerid, 364.6867, 247.1996, ""); // –есурс #3;
            PTD_CraftResources[playerid][3] = CreatePlayerTextDraw(playerid, 394.3886, 247.1996, ""); // –есурс #4;
            PTD_CraftResources[playerid][4] = CreatePlayerTextDraw(playerid, 424.0905, 247.1996, ""); // –есурс #5;

            for(new i = 0; i < 5; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_CraftResources[playerid][i], 28.0000, 28.0000);
                PlayerTextDrawAlignment(playerid, PTD_CraftResources[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_CraftResources[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_CraftResources[playerid][i], -2139062240);
                PlayerTextDrawFont(playerid, PTD_CraftResources[playerid][i], 5);
                PlayerTextDrawSetProportional(playerid, PTD_CraftResources[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_CraftResources[playerid][i], 0);
                PlayerTextDrawSetPreviewModel(playerid, PTD_CraftResources[playerid][i], 18631);
                PlayerTextDrawSetPreviewRot(playerid, PTD_CraftResources[playerid][i], 0.0000, 0.0000, 0.0000, 1.0000);
                PlayerTextDrawSetSelectable(playerid, PTD_CraftResources[playerid][i], true);
            }

            PTD_CraftResourcesInfo[playerid][0] = CreatePlayerTextDraw(playerid, 319.4833, 264.8034, "100/100"); //  оличество ресурса #1;
            PTD_CraftResourcesInfo[playerid][1] = CreatePlayerTextDraw(playerid, 349.1852, 264.8034, "100/100"); //  оличество ресурса #2;
            PTD_CraftResourcesInfo[playerid][2] = CreatePlayerTextDraw(playerid, 378.8869, 264.8034, "100/100"); //  оличество ресурса #3;
            PTD_CraftResourcesInfo[playerid][3] = CreatePlayerTextDraw(playerid, 408.5888, 264.8034, "100/100"); //  оличество ресурса #4;
            PTD_CraftResourcesInfo[playerid][4] = CreatePlayerTextDraw(playerid, 438.2904, 264.8034, "100/100"); //  оличество ресурса #5;

            for(new i = 0; i < 5; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_CraftResourcesInfo[playerid][i], 0.1533, 0.9829);
                PlayerTextDrawAlignment(playerid, PTD_CraftResourcesInfo[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_CraftResourcesInfo[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_CraftResourcesInfo[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_CraftResourcesInfo[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_CraftResourcesInfo[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_CraftResourcesInfo[playerid][i], 0);
            }
        }
        case TD_ID_BATTLEPASS:
        {
            if(p_temp[playerid][TextDrawBattlePass]) return 1;
            PTD_BattlePassMain[playerid][0] = CreatePlayerTextDraw(playerid, 107.7994, 87.6333, "LD_SPAC:white"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][0], 425.3793, 345.7395);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][0], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][0], 0);

            PTD_BattlePassMain[playerid][1] = CreatePlayerTextDraw(playerid, 107.6996, 117.0333, "LD_SPAC:white"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][1], 425.3793, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][1], -2139062240);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][1], 0);

            PTD_BattlePassMain[playerid][2] = CreatePlayerTextDraw(playerid, 110.7322, 148.6808, "LD_SPAC:white"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][2], 119.3619, 280.7796);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][2], -2139062240);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][2], 0);

            PTD_BattlePassMain[playerid][3] = CreatePlayerTextDraw(playerid, 275.5667, 65.6958, ""); // пусто
            PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][3], 90.0000, 74.0000);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][3], -4632577);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][3], -256);
            PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][3], 5);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][3], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassMain[playerid][3], 19785);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassMain[playerid][3], 90.0000, 0.0000, 180.0000, 1.7000);

            PTD_BattlePassMain[playerid][4] = CreatePlayerTextDraw(playerid, 110.7658, 120.1442, "LD_SPAC:white"); // ћагазин;
            PTD_BattlePassMain[playerid][5] = CreatePlayerTextDraw(playerid, 180.8715, 120.1442, "LD_SPAC:white"); // ¬се награды;
            PTD_BattlePassMain[playerid][6] = CreatePlayerTextDraw(playerid, 250.9759, 120.1442, "LD_SPAC:white"); // ќбмен FC;
            PTD_BattlePassMain[playerid][7] = CreatePlayerTextDraw(playerid, 321.0805, 120.1442, "LD_SPAC:white"); // –ейтинг;
            PTD_BattlePassMain[playerid][8] = CreatePlayerTextDraw(playerid, 391.1849, 120.1442, "LD_SPAC:white"); // —татистика;
            PTD_BattlePassMain[playerid][9] = CreatePlayerTextDraw(playerid, 461.2893, 120.1442, "LD_SPAC:white"); // »нформаци€;

            for(new i = 4; i < 10; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][i], 69.0000, 22.0000);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][i], -240);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_BattlePassMain[playerid][i], true);
            }

            PTD_BattlePassMain[playerid][10] = CreatePlayerTextDraw(playerid, 145.4669, 124.0251, "MAВA3ЕH"); // ћагазин;
            PTD_BattlePassMain[playerid][11] = CreatePlayerTextDraw(playerid, 215.8715, 124.0251, "ЛCE HAВPAГС"); // ¬се награды;
            PTD_BattlePassMain[playerid][12] = CreatePlayerTextDraw(playerid, 286.1759, 124.0251, "OАMEH COIN"); // ќбмен FC;
            PTD_BattlePassMain[playerid][13] = CreatePlayerTextDraw(playerid, 356.4804, 124.0251, "PEЖПЕHВ"); // –ейтинг;
            PTD_BattlePassMain[playerid][14] = CreatePlayerTextDraw(playerid, 426.7850, 124.0251, "CПAПЕCПЕKA"); // —татистика;
            PTD_BattlePassMain[playerid][15] = CreatePlayerTextDraw(playerid, 496.8894, 124.0251, "ЕHБOPMAЙЕХ"); // »нформаци€;

            for(new i = 10; i < 16; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_BattlePassMain[playerid][i], 0.2010, 1.4594);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][i], 0);
            }

            PTD_BattlePassMain[playerid][16] = CreatePlayerTextDraw(playerid, 524.7321, 59.3404, "LD_BEAT:chit"); // «акрыть;
            PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][16], 35.0000, 35.0000);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][16], 1);
            PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][16], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][16], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][16], 4);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][16], 0);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][16], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_BattlePassMain[playerid][16], true);

            PTD_BattlePassMain[playerid][17] = CreatePlayerTextDraw(playerid, 542.8488, 68.0809, "X");
            PlayerTextDrawLetterSize(playerid, PTD_BattlePassMain[playerid][17], 0.3853, 1.7108);
            PlayerTextDrawTextSize(playerid, PTD_BattlePassMain[playerid][17], 0.0000, 79.0000);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassMain[playerid][17], 2);
            PlayerTextDrawColor(playerid, PTD_BattlePassMain[playerid][17], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassMain[playerid][17], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassMain[playerid][17], 2);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassMain[playerid][17], 1);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassMain[playerid][17], 0);

            PTD_BattlePassInfo[playerid][0] = CreatePlayerTextDraw(playerid, 77.0500, 190.9272, ""); // ќбъект дерева;
            PlayerTextDrawTextSize(playerid, PTD_BattlePassInfo[playerid][0], 181.0000, 159.0000);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassInfo[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_BattlePassInfo[playerid][0], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassInfo[playerid][0], -256);
            PlayerTextDrawFont(playerid, PTD_BattlePassInfo[playerid][0], 5);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassInfo[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassInfo[playerid][0], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassInfo[playerid][0], 3507);
            PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassInfo[playerid][0], 0.0000, 0.0000, 0.0000, 1.0000);

            PTD_BattlePassInfo[playerid][1] = CreatePlayerTextDraw(playerid, 171.3509, 156.1994, "_"); // Battle Pass, название сезона, до конца;
            PlayerTextDrawLetterSize(playerid, PTD_BattlePassInfo[playerid][1], 0.2502, 1.7539);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassInfo[playerid][1], 2);
            PlayerTextDrawColor(playerid, PTD_BattlePassInfo[playerid][1], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassInfo[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassInfo[playerid][1], 2);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassInfo[playerid][1], 1);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassInfo[playerid][1], 0);

            PTD_BattlePassInfo[playerid][2] = CreatePlayerTextDraw(playerid, 171.3509, 343.3109, "_"); // ”ровень, опыт;
            PlayerTextDrawLetterSize(playerid, PTD_BattlePassInfo[playerid][2], 0.2502, 1.7539);
            PlayerTextDrawAlignment(playerid, PTD_BattlePassInfo[playerid][2], 2);
            PlayerTextDrawColor(playerid, PTD_BattlePassInfo[playerid][2], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassInfo[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_BattlePassInfo[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_BattlePassInfo[playerid][2], 1);
            PlayerTextDrawSetShadow(playerid, PTD_BattlePassInfo[playerid][2], 0);

            PTD_BattlePassInfo[playerid][3] = CreatePlayerTextDraw(playerid, 381.4671, 268.3471, "1/1"); // —траница наград;
            PTD_BattlePassInfo[playerid][4] = CreatePlayerTextDraw(playerid, 381.4671, 410.7557, "1/1"); // —траница заданий;

            for(new i = 3; i < 5; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_BattlePassInfo[playerid][i], 0.2987, 1.3614);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassInfo[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_BattlePassInfo[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassInfo[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassInfo[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassInfo[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassInfo[playerid][i], 0);
            }

            PTD_BattlePassButton[playerid][0] = CreatePlayerTextDraw(playerid, 234.3314, 404.6687, "LD_SPAC:white"); // ¬лево задани€;
            PTD_BattlePassButton[playerid][1] = CreatePlayerTextDraw(playerid, 504.9010, 404.6687, "LD_SPAC:white"); // ¬право задани€;

            for(new i = 0; i < 2; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_BattlePassButton[playerid][i], 25.0000, 25.0000);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassButton[playerid][i], -240);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassButton[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassButton[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassButton[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_BattlePassButton[playerid][i], true);
            }

            PTD_BattlePassButton[playerid][2] = CreatePlayerTextDraw(playerid, 240.0350, 408.1737, "<<");
            PTD_BattlePassButton[playerid][3] = CreatePlayerTextDraw(playerid, 512.4210, 408.1737, ">>");

            for(new i = 2; i < 4; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_BattlePassButton[playerid][i], 0.2433, 1.9629);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassButton[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassButton[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassButton[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassButton[playerid][i], 0);
            }

            PTD_BattlePassButton[playerid][4] = CreatePlayerTextDraw(playerid, 234.3314, 262.7603, "LD_SPAC:white"); // ¬лево награды;
            PTD_BattlePassButton[playerid][5] = CreatePlayerTextDraw(playerid, 504.9010, 262.7603, "LD_SPAC:white"); // ¬право награды;

            for(new i = 4; i < 6; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_BattlePassButton[playerid][i], 25.0000, 25.0000);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassButton[playerid][i], -240);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassButton[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassButton[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassButton[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_BattlePassButton[playerid][i], true);
            }

            PTD_BattlePassButton[playerid][6] = CreatePlayerTextDraw(playerid, 240.0350, 266.2651, "<<");
            PTD_BattlePassButton[playerid][7] = CreatePlayerTextDraw(playerid, 512.4210, 266.2651, ">>");

            for(new i = 6; i < 8; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_BattlePassButton[playerid][i], 0.2433, 1.9629);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassButton[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassButton[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassButton[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassButton[playerid][i], 0);
            }

            PTD_BattlePassRewardMain[playerid][0] = CreatePlayerTextDraw(playerid, 234.2014, 148.6622, "LD_SPAC:white"); // Ќаграда #1 - фон;
            PTD_BattlePassRewardMain[playerid][1] = CreatePlayerTextDraw(playerid, 333.6076, 148.6622, "LD_SPAC:white"); // Ќаграда #2 - фон;
            PTD_BattlePassRewardMain[playerid][2] = CreatePlayerTextDraw(playerid, 433.0137, 148.6622, "LD_SPAC:white"); // Ќаграда #3 - фон;

            PTD_BattlePassRewardButton[playerid][0] = CreatePlayerTextDraw(playerid, 248.8354, 231.5146, "LD_SPAC:white"); // Ќаграда #1 - кнопка;
            PTD_BattlePassRewardButton[playerid][1] = CreatePlayerTextDraw(playerid, 348.2413, 231.5146, "LD_SPAC:white"); // Ќаграда #2 - кнопка;
            PTD_BattlePassRewardButton[playerid][2] = CreatePlayerTextDraw(playerid, 447.6473, 231.5146, "LD_SPAC:white"); // Ќаграда #3 - кнопка;

            PTD_BattlePassRewardText[playerid][0] = CreatePlayerTextDraw(playerid, 283.9190, 235.0914, "_"); // Ќаграда #1 - забрать;
            PTD_BattlePassRewardText[playerid][1] = CreatePlayerTextDraw(playerid, 383.3251, 235.0914, "_"); // Ќаграда #2 - забрать;
            PTD_BattlePassRewardText[playerid][2] = CreatePlayerTextDraw(playerid, 482.7312, 235.0914, "_"); // Ќаграда #3 - забрать;

            PTD_BattlePassRewardModel[playerid][0] = CreatePlayerTextDraw(playerid, 237.6345, 158.9217, ""); // Ќаграда #1 - модель;
            PTD_BattlePassRewardModel[playerid][1] = CreatePlayerTextDraw(playerid, 337.0408, 158.9217, ""); // Ќаграда #2 - модель;
            PTD_BattlePassRewardModel[playerid][2] = CreatePlayerTextDraw(playerid, 436.4468, 158.9217, ""); // Ќаграда #3 - модель;

            PTD_BattlePassRewardInfo[playerid][0] = CreatePlayerTextDraw(playerid, 283.5350, 148.7200, "_"); // Ќаграда #1 - информаци€;
            PTD_BattlePassRewardInfo[playerid][1] = CreatePlayerTextDraw(playerid, 382.9411, 148.7200, "_"); // Ќаграда #2 - информаци€;
            PTD_BattlePassRewardInfo[playerid][2] = CreatePlayerTextDraw(playerid, 482.3471, 148.7200, "_"); // Ќаграда #3 - информаци€;

            PTD_BattlePassTaskMain[playerid][0] = CreatePlayerTextDraw(playerid, 234.2014, 290.7708, "LD_SPAC:white"); // «адание #1 - фон;
            PTD_BattlePassTaskMain[playerid][1] = CreatePlayerTextDraw(playerid, 333.6076, 290.7708, "LD_SPAC:white"); // «адание #2 - фон;
            PTD_BattlePassTaskMain[playerid][2] = CreatePlayerTextDraw(playerid, 433.0137, 290.7708, "LD_SPAC:white"); // «адание #3 - фон;

            PTD_BattlePassTaskName[playerid][0] = CreatePlayerTextDraw(playerid, 238.0171, 292.2296, "_"); // «адание #1 - название и награда;
            PTD_BattlePassTaskName[playerid][1] = CreatePlayerTextDraw(playerid, 337.4234, 292.2296, "_"); // «адание #2 - название и награда;
            PTD_BattlePassTaskName[playerid][2] = CreatePlayerTextDraw(playerid, 436.8294, 292.2296, "_"); // «адание #3 - название и награда;

            PTD_BattlePassTaskInfo[playerid][0] = CreatePlayerTextDraw(playerid, 238.0171, 358.4335, "_"); // «адание #1 - информаци€;
            PTD_BattlePassTaskInfo[playerid][1] = CreatePlayerTextDraw(playerid, 337.4234, 358.4335, "_"); // «адани€ #2 - информаци€;
            PTD_BattlePassTaskInfo[playerid][2] = CreatePlayerTextDraw(playerid, 436.8294, 358.4335, "_"); // «адание #3 - информаци€;

            for(new i = 0; i < 3; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_BattlePassRewardMain[playerid][i], 97.0000, 111.0500);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassRewardMain[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassRewardMain[playerid][i], -2139062240);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassRewardMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassRewardMain[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassRewardMain[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassRewardMain[playerid][i], 0);

                PlayerTextDrawTextSize(playerid, PTD_BattlePassRewardButton[playerid][i], 69.0000, 22.0000);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassRewardButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassRewardButton[playerid][i], -240);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassRewardButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassRewardButton[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassRewardButton[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassRewardButton[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_BattlePassRewardButton[playerid][i], true);

                PlayerTextDrawLetterSize(playerid, PTD_BattlePassRewardText[playerid][i], 0.2010, 1.4594);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassRewardText[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_BattlePassRewardText[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassRewardText[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassRewardText[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassRewardText[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassRewardText[playerid][i], 0);

                PlayerTextDrawTextSize(playerid, PTD_BattlePassRewardModel[playerid][i], 90.0000, 90.0000);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassRewardModel[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassRewardModel[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassRewardModel[playerid][i], -256);
                PlayerTextDrawFont(playerid, PTD_BattlePassRewardModel[playerid][i], 5);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassRewardModel[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassRewardModel[playerid][i], 0);
                PlayerTextDrawSetPreviewModel(playerid, PTD_BattlePassRewardModel[playerid][i], 1212);
                PlayerTextDrawSetPreviewRot(playerid, PTD_BattlePassRewardModel[playerid][i], 90.0000, 0.0000, 0.0000, 1.0000);

                PlayerTextDrawLetterSize(playerid, PTD_BattlePassRewardInfo[playerid][i], 0.1817, 1.3351);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassRewardInfo[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_BattlePassRewardInfo[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassRewardInfo[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassRewardInfo[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassRewardInfo[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassRewardInfo[playerid][i], 0);

                PlayerTextDrawTextSize(playerid, PTD_BattlePassTaskMain[playerid][i], 97.0000, 111.0500);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassTaskMain[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassTaskMain[playerid][i], -2139062240);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassTaskMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassTaskMain[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassTaskMain[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassTaskMain[playerid][i], 0);

                PlayerTextDrawLetterSize(playerid, PTD_BattlePassTaskName[playerid][i], 0.2307, 1.0656);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassTaskName[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassTaskName[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassTaskName[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassTaskName[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassTaskName[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassTaskName[playerid][i], 0);

                PlayerTextDrawLetterSize(playerid, PTD_BattlePassTaskInfo[playerid][i], 0.1650, 1.1437);
                PlayerTextDrawAlignment(playerid, PTD_BattlePassTaskInfo[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_BattlePassTaskInfo[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_BattlePassTaskInfo[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_BattlePassTaskInfo[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_BattlePassTaskInfo[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_BattlePassTaskInfo[playerid][i], 0);
            }
        }
        case TD_ID_DAILY:
        {
            if(p_temp[playerid][TextDrawDaily]) return 1;
            PTD_DailyMain[playerid][0] = CreatePlayerTextDraw(playerid, 169.2015, 128.5325, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_DailyMain[playerid][0], 303.3200, 204.1179);
            PlayerTextDrawAlignment(playerid, PTD_DailyMain[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_DailyMain[playerid][0], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_DailyMain[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_DailyMain[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DailyMain[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DailyMain[playerid][0], 0);

            PTD_DailyMain[playerid][1] = CreatePlayerTextDraw(playerid, 169.1015, 157.9349, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_DailyMain[playerid][1], 303.3200, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_DailyMain[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_DailyMain[playerid][1], -2139062240);
            PlayerTextDrawBackgroundColor(playerid, PTD_DailyMain[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_DailyMain[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DailyMain[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DailyMain[playerid][1], 0);

            PTD_DailyMain[playerid][2] = CreatePlayerTextDraw(playerid, 275.5667, 106.5951, "");
            PlayerTextDrawTextSize(playerid, PTD_DailyMain[playerid][2], 90.0000, 74.0000);
            PlayerTextDrawAlignment(playerid, PTD_DailyMain[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_DailyMain[playerid][2], -4632577);
            PlayerTextDrawBackgroundColor(playerid, PTD_DailyMain[playerid][2], -256);
            PlayerTextDrawFont(playerid, PTD_DailyMain[playerid][2], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DailyMain[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DailyMain[playerid][2], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DailyMain[playerid][2], 954);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DailyMain[playerid][2], 0.0000, 0.0000, 180.0000, 2.0000);

            PTD_DailyButton[playerid][0] = CreatePlayerTextDraw(playerid, 173.1275, 303.6628, "LD_SPAC:white"); // ¬лево награды;
            PTD_DailyButton[playerid][1] = CreatePlayerTextDraw(playerid, 443.6972, 303.6628, "LD_SPAC:white"); // ¬право награды;

            for(new i = 0; i < 2; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_DailyButton[playerid][i], 25.0000, 25.0000);
                PlayerTextDrawAlignment(playerid, PTD_DailyButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_DailyButton[playerid][i], -240);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyButton[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_DailyButton[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_DailyButton[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_DailyButton[playerid][i], true);
            }

            PTD_DailyButton[playerid][2] = CreatePlayerTextDraw(playerid, 178.8312, 307.1675, "<<");
            PTD_DailyButton[playerid][3] = CreatePlayerTextDraw(playerid, 451.2174, 307.1675, ">>");

            for(new i = 2; i < 4; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_DailyButton[playerid][i], 0.2433, 1.9629);
                PlayerTextDrawAlignment(playerid, PTD_DailyButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_DailyButton[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyButton[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_DailyButton[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_DailyButton[playerid][i], 0);
            }

            PTD_DailyButton[playerid][4] = CreatePlayerTextDraw(playerid, 142.3291, 100.7581, "LD_BEAT:chit"); //  нопка - помощь;
            PTD_DailyButton[playerid][5] = CreatePlayerTextDraw(playerid, 464.3323, 100.7581, "LD_BEAT:chit"); //  нопка - закрыть;

            for(new i = 4; i < 6; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_DailyButton[playerid][i], 35.0000, 35.0000);
                PlayerTextDrawAlignment(playerid, PTD_DailyButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_DailyButton[playerid][i], 336860415);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyButton[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_DailyButton[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_DailyButton[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_DailyButton[playerid][i], true);
            }

            PTD_DailyButton[playerid][6] = CreatePlayerTextDraw(playerid, 160.4512, 109.4987, "H"); // ѕомощь;
            PTD_DailyButton[playerid][7] = CreatePlayerTextDraw(playerid, 482.4544, 109.4987, "X"); // «акрыть;

            for(new i = 6; i < 8; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_DailyButton[playerid][i], 0.3853, 1.7108);
                PlayerTextDrawTextSize(playerid, PTD_DailyButton[playerid][i], 0.0000, 79.0000);
                PlayerTextDrawAlignment(playerid, PTD_DailyButton[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_DailyButton[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyButton[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_DailyButton[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_DailyButton[playerid][i], 0);
            }

            PTD_DailyInfo[playerid][0] = CreatePlayerTextDraw(playerid, 320.7774, 164.9272, "_"); // ƒо получени€ награды;
            PlayerTextDrawLetterSize(playerid, PTD_DailyInfo[playerid][0], 0.2010, 1.4594);
            PlayerTextDrawAlignment(playerid, PTD_DailyInfo[playerid][0], 2);
            PlayerTextDrawColor(playerid, PTD_DailyInfo[playerid][0], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_DailyInfo[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_DailyInfo[playerid][0], 2);
            PlayerTextDrawSetProportional(playerid, PTD_DailyInfo[playerid][0], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DailyInfo[playerid][0], 0);

            PTD_DailyInfo[playerid][1] = CreatePlayerTextDraw(playerid, 320.2633, 309.2495, "1/1"); // —траница наград;
            PlayerTextDrawLetterSize(playerid, PTD_DailyInfo[playerid][1], 0.2987, 1.3614);
            PlayerTextDrawAlignment(playerid, PTD_DailyInfo[playerid][1], 2);
            PlayerTextDrawColor(playerid, PTD_DailyInfo[playerid][1], -328961);
            PlayerTextDrawBackgroundColor(playerid, PTD_DailyInfo[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_DailyInfo[playerid][1], 2);
            PlayerTextDrawSetProportional(playerid, PTD_DailyInfo[playerid][1], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DailyInfo[playerid][1], 0);

            PTD_DailyRewardMain[playerid][0] = CreatePlayerTextDraw(playerid, 172.9976, 189.5646, "LD_SPAC:white"); // Ќаграда #1 - фон;
            PTD_DailyRewardMain[playerid][1] = CreatePlayerTextDraw(playerid, 272.4038, 189.5646, "LD_SPAC:white"); // Ќаграда #2 - фон;
            PTD_DailyRewardMain[playerid][2] = CreatePlayerTextDraw(playerid, 371.8099, 189.5646, "LD_SPAC:white"); // Ќаграда #3 - фон;

            PTD_DailyRewardButton[playerid][0] = CreatePlayerTextDraw(playerid, 187.6316, 272.4169, "LD_SPAC:white"); // Ќаграда #1 - кнопка;
            PTD_DailyRewardButton[playerid][1] = CreatePlayerTextDraw(playerid, 287.0375, 272.4169, "LD_SPAC:white"); // Ќаграда #2 - кнопка;
            PTD_DailyRewardButton[playerid][2] = CreatePlayerTextDraw(playerid, 386.4435, 272.4169, "LD_SPAC:white"); // Ќаграда #3 - кнопка;

            PTD_DailyRewardText[playerid][0] = CreatePlayerTextDraw(playerid, 222.7151, 275.9938, "_"); // Ќаграда #1 - забрать;
            PTD_DailyRewardText[playerid][1] = CreatePlayerTextDraw(playerid, 322.1213, 275.9938, "_"); // Ќаграда #2 - забрать;
            PTD_DailyRewardText[playerid][2] = CreatePlayerTextDraw(playerid, 421.5274, 275.9938, "_"); // Ќаграда #3 - забрать;

            PTD_DailyRewardModel[playerid][0] = CreatePlayerTextDraw(playerid, 176.4306, 199.8240, ""); // Ќаграда #1 - модель;
            PTD_DailyRewardModel[playerid][1] = CreatePlayerTextDraw(playerid, 275.8370, 199.8240, ""); // Ќаграда #2 - модель;
            PTD_DailyRewardModel[playerid][2] = CreatePlayerTextDraw(playerid, 375.2430, 199.8240, ""); // Ќаграда #3 - модель;

            PTD_DailyRewardInfo[playerid][0] = CreatePlayerTextDraw(playerid, 222.3312, 189.6224, "_"); // Ќаграда #1 - день и награда;
            PTD_DailyRewardInfo[playerid][1] = CreatePlayerTextDraw(playerid, 321.7373, 189.6224, "_"); // Ќаграда #2 - день и награда;
            PTD_DailyRewardInfo[playerid][2] = CreatePlayerTextDraw(playerid, 421.1433, 189.6224, "_"); // Ќаграда #3 - день и награда;

            for(new i = 0; i < 3; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_DailyRewardMain[playerid][i], 97.0000, 111.0500);
                PlayerTextDrawAlignment(playerid, PTD_DailyRewardMain[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_DailyRewardMain[playerid][i], -2139062240);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyRewardMain[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyRewardMain[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_DailyRewardMain[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_DailyRewardMain[playerid][i], 0);

                PlayerTextDrawTextSize(playerid, PTD_DailyRewardButton[playerid][i], 69.0000, 22.0000);
                PlayerTextDrawAlignment(playerid, PTD_DailyRewardButton[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_DailyRewardButton[playerid][i], -240);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyRewardButton[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyRewardButton[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_DailyRewardButton[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_DailyRewardButton[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_DailyRewardButton[playerid][i], true);

                PlayerTextDrawLetterSize(playerid, PTD_DailyRewardText[playerid][i], 0.2010, 1.4594);
                PlayerTextDrawAlignment(playerid, PTD_DailyRewardText[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_DailyRewardText[playerid][i], -328961);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyRewardText[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyRewardText[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_DailyRewardText[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_DailyRewardText[playerid][i], 0);

                PlayerTextDrawTextSize(playerid, PTD_DailyRewardModel[playerid][i], 90.0000, 90.0000);
                PlayerTextDrawAlignment(playerid, PTD_DailyRewardModel[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_DailyRewardModel[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyRewardModel[playerid][i], -256);
                PlayerTextDrawFont(playerid, PTD_DailyRewardModel[playerid][i], 5);
                PlayerTextDrawSetProportional(playerid, PTD_DailyRewardModel[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_DailyRewardModel[playerid][i], 0);
                PlayerTextDrawSetPreviewModel(playerid, PTD_DailyRewardModel[playerid][i], 1212);
                PlayerTextDrawSetPreviewRot(playerid, PTD_DailyRewardModel[playerid][i], 90.0000, 0.0000, 0.0000, 1.0000);

                PlayerTextDrawLetterSize(playerid, PTD_DailyRewardInfo[playerid][i], 0.1817, 1.3351);
                PlayerTextDrawAlignment(playerid, PTD_DailyRewardInfo[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_DailyRewardInfo[playerid][i], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_DailyRewardInfo[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_DailyRewardInfo[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_DailyRewardInfo[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_DailyRewardInfo[playerid][i], 0);
            }
        }
        case TD_ID_ELECTRIC:
        {
            if(p_temp[playerid][TextDrawElectric]) return 1;
            PTD_Electric[playerid][0] = CreatePlayerTextDraw(playerid, 178.1174, 130.1398, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][0], 276.8640, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][0], -22740481);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][0], 0);

            PTD_Electric[playerid][1] = CreatePlayerTextDraw(playerid, 178.1174, 136.1403, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][1], 276.8640, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][1], -5500673);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][1], 0);

            PTD_Electric[playerid][2] = CreatePlayerTextDraw(playerid, 178.1174, 142.1407, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][2], 276.8640, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][2], -5103105);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][2], 0);

            PTD_Electric[playerid][3] = CreatePlayerTextDraw(playerid, 316.6824, 134.6477, "PEMOHѕ_«”ћ");
            PlayerTextDrawLetterSize(playerid, PTD_Electric[playerid][3], 0.2150, 1.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][3], 1295122687);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][3], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][3], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][3], 0);

            PTD_Electric[playerid][4] = CreatePlayerTextDraw(playerid, 178.1174, 148.2485, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][4], 276.8640, 178.8721);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][4], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][4], 0);

            PTD_Electric[playerid][5] = CreatePlayerTextDraw(playerid, 178.1174, 153.7852, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][5], 276.8640, 20.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][5], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][5], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][5], 0);

            PTD_Electric[playerid][6] = CreatePlayerTextDraw(playerid, 317.0989, 158.4306, "HAƒM≈ѕE_HA_KPACH—∆_ћPOЋO√");
            PlayerTextDrawLetterSize(playerid, PTD_Electric[playerid][6], 0.2150, 1.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][6], 2);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][6], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][6], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][6], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][6], 0);

            PTD_Electric[playerid][7] = CreatePlayerTextDraw(playerid, 178.1174, 288.3233, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][7], 276.8640, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][7], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][7], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][7], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][7], 0);

            PTD_Electric[playerid][8] = CreatePlayerTextDraw(playerid, 405.4135, 297.3081, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][8], 46.8693, 27.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][8], -715897601);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][8], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][8], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][8], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][8], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Electric[playerid][8], true);

            PTD_Electric[playerid][9] = CreatePlayerTextDraw(playerid, 429.0917, 303.8786, "3AKPСПТ");
            PlayerTextDrawLetterSize(playerid, PTD_Electric[playerid][9], 0.3000, 1.3947);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][9], 2);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][9], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][9], -1);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][9], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][9], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][9], 0);

            PTD_Electric[playerid][10] = CreatePlayerTextDraw(playerid, 202.5000, 183.0630, "");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][10], 90.0000, 90.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][10], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][10], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][10], 536870656);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][10], 5);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][10], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][10], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_Electric[playerid][10], 934);
            PlayerTextDrawSetPreviewRot(playerid, PTD_Electric[playerid][10], 0.0000, 0.0000, -90.0000, 1.0000);

            PTD_Electric[playerid][11] = CreatePlayerTextDraw(playerid, 359.9598, 183.0630, "");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][11], 90.0000, 90.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][11], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][11], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][11], 536870656);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][11], 5);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][11], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][11], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_Electric[playerid][11], 3244);
            PlayerTextDrawSetPreviewRot(playerid, PTD_Electric[playerid][11], 0.0000, 0.0000, -90.0000, 1.0000);

            PTD_Electric[playerid][12] = CreatePlayerTextDraw(playerid, 271.1834, 217.6482, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][12], 125.0000, 7.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][12], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][12], -10270721);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][12], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][12], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][12], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][12], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Electric[playerid][12], true);

            PTD_Electric[playerid][13] = CreatePlayerTextDraw(playerid, 286.5512, 238.6495, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Electric[playerid][13], 109.5901, 7.0000);
            PlayerTextDrawAlignment(playerid, PTD_Electric[playerid][13], 1);
            PlayerTextDrawColor(playerid, PTD_Electric[playerid][13], 10092543);
            PlayerTextDrawBackgroundColor(playerid, PTD_Electric[playerid][13], 255);
            PlayerTextDrawFont(playerid, PTD_Electric[playerid][13], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Electric[playerid][13], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Electric[playerid][13], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Electric[playerid][13], true);
        }
        case TD_ID_RADIO:
        {
            if(p_temp[playerid][TextDrawRadio]) return 1;
            PTD_Radio[playerid][0] = CreatePlayerTextDraw(playerid, 398.2005, 120.2690, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][0], 237.7436, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][0], -3073537);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][0], 0);

            PTD_Radio[playerid][1] = CreatePlayerTextDraw(playerid, 398.2005, 126.2692, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][1], 237.7436, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][1], -2739457);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][1], 0);

            PTD_Radio[playerid][2] = CreatePlayerTextDraw(playerid, 398.2005, 132.2693, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][2], 237.7436, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][2], -2405377);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][2], 0);

            PTD_Radio[playerid][3] = CreatePlayerTextDraw(playerid, 518.3645, 124.7767, "MP-3 МЗEEP");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][3], 0.2150, 1.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][3], 1295122687);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][3], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][3], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][3], 0);

            PTD_Radio[playerid][4] = CreatePlayerTextDraw(playerid, 398.2005, 138.3772, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][4], 237.7436, 234.3914);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][4], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][4], 0);

            PTD_Radio[playerid][5] = CreatePlayerTextDraw(playerid, 398.2005, 149.6140, "LD_SPAC:white"); //  нопка #1;
            PTD_Radio[playerid][6] = CreatePlayerTextDraw(playerid, 398.2005, 172.0155, "LD_SPAC:white"); //  нопка #2;
            PTD_Radio[playerid][7] = CreatePlayerTextDraw(playerid, 398.2005, 194.4169, "LD_SPAC:white"); //  нопка #3;
            PTD_Radio[playerid][8] = CreatePlayerTextDraw(playerid, 398.2005, 216.8183, "LD_SPAC:white"); //  нопка #4;
            PTD_Radio[playerid][9] = CreatePlayerTextDraw(playerid, 398.2005, 239.2195, "LD_SPAC:white"); //  нопка #5;
            PTD_Radio[playerid][10] = CreatePlayerTextDraw(playerid, 398.2005, 261.6208, "LD_SPAC:white"); //  нопка #6;
            PTD_Radio[playerid][11] = CreatePlayerTextDraw(playerid, 398.2005, 284.0222, "LD_SPAC:white"); //  нопка #7;

            for(new i = 5; i < 12; i++)
            {
                PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][i], 237.7436, 20.0000);
                PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_Radio[playerid][i], 454761471);
                PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_Radio[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][i], 0);
                PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][i], 0);
                PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][i], true);
            }

            PTD_Radio[playerid][12] = CreatePlayerTextDraw(playerid, 403.0154, 154.2628, "_"); // “екст #1;
            PTD_Radio[playerid][13] = CreatePlayerTextDraw(playerid, 403.0154, 176.6642, "_"); // “екст #2;
            PTD_Radio[playerid][14] = CreatePlayerTextDraw(playerid, 403.0154, 199.0656, "_"); // “екст #3;
            PTD_Radio[playerid][15] = CreatePlayerTextDraw(playerid, 403.0154, 221.4669, "_"); // “екст #4;
            PTD_Radio[playerid][16] = CreatePlayerTextDraw(playerid, 403.0154, 243.8684, "_"); // “екст #5;
            PTD_Radio[playerid][17] = CreatePlayerTextDraw(playerid, 403.0154, 266.2697, "_"); // “екст #6;
            PTD_Radio[playerid][18] = CreatePlayerTextDraw(playerid, 403.0154, 288.6711, "_"); // “екст #7;

            for(new i = 12; i < 19; i++)
            {
                PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][i], 0.2486, 1.0463);
                PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][i], 1);
                PlayerTextDrawColor(playerid, PTD_Radio[playerid][i], -56);
                PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_Radio[playerid][i], 1);
                PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][i], 1);
                PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][i], 0);
            }

            PTD_Radio[playerid][19] = CreatePlayerTextDraw(playerid, 398.2005, 306.9536, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][19], 237.7436, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][19], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][19], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][19], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][19], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][19], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][19], 0);

            PTD_Radio[playerid][20] = CreatePlayerTextDraw(playerid, 400.0830, 328.8389, "LD_SPAC:white"); // ѕауза;
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][20], 46.8693, 27.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][20], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][20], -715897601);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][20], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][20], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][20], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][20], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][20], true);

            PTD_Radio[playerid][21] = CreatePlayerTextDraw(playerid, 423.7611, 335.4093, "CПOМ");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][21], 0.3000, 1.3947);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][21], 2);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][21], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][21], -1);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][21], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][21], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][21], 0);

            PTD_Radio[playerid][22] = CreatePlayerTextDraw(playerid, 398.2005, 141.0435, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][22], 237.7436, 6.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][22], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][22], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][22], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][22], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][22], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][22], 0);

            PTD_Radio[playerid][23] = CreatePlayerTextDraw(playerid, 471.1535, 316.6199, "LD_SPAC:white"); // ¬лево;
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][23], 25.0000, 25.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][23], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][23], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][23], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][23], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][23], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][23], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][23], true);

            PTD_Radio[playerid][24] = CreatePlayerTextDraw(playerid, 536.9553, 316.6199, "LD_SPAC:white"); // ¬право;
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][24], 25.0000, 25.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][24], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][24], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][24], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][24], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][24], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][24], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][24], true);

            PTD_Radio[playerid][25] = CreatePlayerTextDraw(playerid, 476.8572, 320.1250, "<<");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][25], 0.2433, 1.9629);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][25], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][25], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][25], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][25], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][25], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][25], 0);

            PTD_Radio[playerid][26] = CreatePlayerTextDraw(playerid, 544.4755, 320.1250, ">>");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][26], 0.2433, 1.9629);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][26], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][26], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][26], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][26], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][26], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][26], 0);

            PTD_Radio[playerid][27] = CreatePlayerTextDraw(playerid, 516.8577, 322.1622, "1/1"); // —траница;
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][27], 0.2987, 1.3614);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][27], 2);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][27], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][27], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][27], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][27], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][27], 0);

            PTD_Radio[playerid][28] = CreatePlayerTextDraw(playerid, 587.0947, 328.8389, "LD_SPAC:white"); // «акрыть;
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][28], 46.8693, 27.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][28], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][28], -715897601);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][28], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][28], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][28], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][28], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][28], true);

            PTD_Radio[playerid][29] = CreatePlayerTextDraw(playerid, 610.7728, 335.4093, "3AKPСПТ");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][29], 0.3000, 1.3947);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][29], 2);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][29], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][29], -1);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][29], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][29], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][29], 0);

            PTD_Radio[playerid][30] = CreatePlayerTextDraw(playerid, 471.1535, 344.4216, "LD_SPAC:white"); // ѕред. трек;
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][30], 25.0000, 25.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][30], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][30], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][30], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][30], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][30], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][30], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][30], true);

            PTD_Radio[playerid][31] = CreatePlayerTextDraw(playerid, 536.9553, 344.4216, "LD_SPAC:white"); // —лед. трек;
            PlayerTextDrawTextSize(playerid, PTD_Radio[playerid][31], 25.0000, 25.0000);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][31], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][31], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][31], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][31], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][31], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][31], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Radio[playerid][31], true);

            PTD_Radio[playerid][32] = CreatePlayerTextDraw(playerid, 476.8572, 347.9266, "<<");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][32], 0.2433, 1.9629);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][32], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][32], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][32], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][32], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][32], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][32], 0);

            PTD_Radio[playerid][33] = CreatePlayerTextDraw(playerid, 544.4755, 347.9266, ">>");
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][33], 0.2433, 1.9629);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][33], 1);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][33], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][33], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][33], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][33], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][33], 0);

            PTD_Radio[playerid][34] = CreatePlayerTextDraw(playerid, 516.8577, 349.9638, "00:00"); // ¬рем€ до окончани€ трека;
            PlayerTextDrawLetterSize(playerid, PTD_Radio[playerid][34], 0.2987, 1.3614);
            PlayerTextDrawAlignment(playerid, PTD_Radio[playerid][34], 2);
            PlayerTextDrawColor(playerid, PTD_Radio[playerid][34], -56);
            PlayerTextDrawBackgroundColor(playerid, PTD_Radio[playerid][34], 255);
            PlayerTextDrawFont(playerid, PTD_Radio[playerid][34], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Radio[playerid][34], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Radio[playerid][34], 0);
        }
        case TD_ID_INVENTORY_PLAYER:
        {
            if(p_temp[playerid][TextDrawInventory]) return 1;
            CreateTextDrawEquipment(playerid, TD_ID_EQUIPMENT_RIGHT);
            CreateTextDrawEquipment(playerid, TD_ID_EQUIPMENT_PERSON_INFO);
        }
        case TD_ID_TRADE, TD_ID_MARKET, TD_ID_INVENTORY_OTHER:
        {
            if(p_temp[playerid][TextDrawEquipment]) return 1;
            CreateTextDrawEquipment(playerid, TD_ID_EQUIPMENT_RIGHT);
            CreateTextDrawEquipment(playerid, TD_ID_EQUIPMENT_LEFT);
        }
        case TD_ID_DONATE_INFO:
        {
            if(p_temp[playerid][TextDrawDonateInfo]) return 1;
            PTD_DonateInfo[playerid][0] = CreatePlayerTextDraw(playerid, 214.033004, 139.236602, "LD_SPAC:white");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][0], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][0], 213.940002, 10.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][0], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][0], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][0], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][0], 0);

            PTD_DonateInfo[playerid][1] = CreatePlayerTextDraw(playerid, 220.366302, 131.869903, "LD_SPAC:white");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][1], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][1], 201.000000, 14.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][1], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][1], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][1], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][1], 0);

            PTD_DonateInfo[playerid][2] = CreatePlayerTextDraw(playerid, 412.866302, 128.451507, "LD_BEAT:chit");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][2], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][2], 18.000000, 21.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][2], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][2], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][2], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][2], 0);

            PTD_DonateInfo[playerid][3] = CreatePlayerTextDraw(playerid, 211.033004, 128.451507, "LD_BEAT:chit");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][3], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][3], 18.000000, 21.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][3], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][3], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][3], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][3], 0);

            PTD_DonateInfo[playerid][4] = CreatePlayerTextDraw(playerid, 215.198806, 149.320602, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][4], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][4], 212.000000, -5.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][4], 255);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][4], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][4], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][4], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][4], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][4], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][4], 1317);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][4], 16.000000, 0.000000, 299.000000, 0.213400);

            PTD_DonateInfo[playerid][5] = CreatePlayerTextDraw(playerid, 213.832901, 153.602905, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][5], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][5], 214.000000, 136.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][5], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][5], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][5], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][5], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][5], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][5], 19063);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][5], 0.000000, 224.000000, 64.000000, 0.234500);

            PTD_DonateInfo[playerid][6] = CreatePlayerTextDraw(playerid, 213.832901, 157.172805, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][6], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][6], 214.000000, 128.830001);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][6], -73517057);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][6], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][6], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][6], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][6], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][6], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][6], 19063);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][6], 0.000000, 224.000000, 64.000000, 0.234500);

            PTD_DonateInfo[playerid][7] = CreatePlayerTextDraw(playerid, 213.865402, 161.765106, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][7], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][7], 214.000000, -5.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][7], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][7], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][7], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][7], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][7], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][7], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][7], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][7], 1317);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][7], 16.000000, 0.000000, 299.000000, 0.213400);

            PTD_DonateInfo[playerid][8] = CreatePlayerTextDraw(playerid, 213.865402, 279.987701, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][8], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][8], 214.000000, 6.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][8], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][8], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][8], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][8], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][8], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][8], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][8], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][8], 1317);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][8], 16.000000, 0.000000, 299.000000, 0.213400);

            PTD_DonateInfo[playerid][9] = CreatePlayerTextDraw(playerid, 213.666503, 138.021804, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][9], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][9], 214.450302, 7.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][9], -16776961);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][9], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][9], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][9], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][9], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][9], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][9], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][9], 954);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][9], 0.000000, 90.000000, 91.000000, 0.286700);

            PTD_DonateInfo[playerid][10] = CreatePlayerTextDraw(playerid, 322.133209, 116.451400, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][10], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][10], 16.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][10], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][10], -16776961);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][10], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][10], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][10], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][10], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][10], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][10], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][10], 954);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][10], 105.000000, 90.000000, 0.000000, 0.641200);

            PTD_DonateInfo[playerid][11] = CreatePlayerTextDraw(playerid, 316.133209, 116.451400, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][11], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][11], -16.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][11], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][11], -16776961);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][11], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][11], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][11], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][11], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][11], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][11], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][11], 954);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][11], 105.000000, 90.000000, 0.000000, 0.641200);

            PTD_DonateInfo[playerid][12] = CreatePlayerTextDraw(playerid, 309.132995, 128.066192, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][12], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][12], 20.000000, 44.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][12], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][12], -16776961);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][12], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][12], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][12], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][12], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][12], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][12], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][12], 954);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][12], 250.000000, 0.000000, 0.000000, 0.589100);

            PTD_DonateInfo[playerid][13] = CreatePlayerTextDraw(playerid, 274.132995, 125.162597, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][13], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][13], 89.000000, 32.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][13], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][13], -16776961);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][13], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][13], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][13], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][13], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][13], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][13], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][13], 954);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][13], 88.000000, 0.000000, 90.000000, 1.042700);

            PTD_DonateInfo[playerid][14] = CreatePlayerTextDraw(playerid, 319.266296, 172.162704, "EДEГHEЛHAХ AKЙЕХ");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][14], 0.348300, 1.496000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][14], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][14], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][14], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][14], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][14], 6);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][14], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][14], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][14], 0);

            PTD_DonateInfo[playerid][15] = CreatePlayerTextDraw(playerid, 319.266296, 188.755401, "ГaҐЃo xo¶eЮ £pЬoЧpec¶Ь peЪkЬЭ ckЬЃ ЬЮЬ kpy¶oЭ aҐ¶oѓoЧЬЮ©?~n~CeЩoЪЃђ - Юy§•ЬЭ •aЃc!");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][15], 0.178000, 0.898800);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][15], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][15], -28929);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][15], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][15], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][15], 6);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][15], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][15], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][15], 0);

            PTD_DonateInfo[playerid][16] = CreatePlayerTextDraw(playerid, 321.599700, 204.933105, "EЫeЪЃeҐЃo Ѓa cepҐepe ЪeЭc¶ҐyЂ¶ ckЬЪkЬ Ѓa ѓЃoЫec¶Ґo ¶oҐapoҐ!");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][16], 0.178000, 0.898800);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][16], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][16], -28929);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][16], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][16], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][16], 6);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][16], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][16], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][16], 0);

            PTD_DonateInfo[playerid][17] = CreatePlayerTextDraw(playerid, 319.966400, 219.451705, "ГO KOHЙA AKЙЕЕ OCПAЗOCТ:");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][17], 0.165900, 0.708000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][17], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][17], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][17], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][17], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][17], 6);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][17], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][17], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][17], 0);

            PTD_DonateInfo[playerid][18] = CreatePlayerTextDraw(playerid, 275.033203, 229.251602, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][18], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][18], 29.000000, 32.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][18], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][18], 128);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][18], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][18], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][18], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][18], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][18], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][18], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][18], 2729);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][18], 0.000000, 0.000000, 0.000000, 0.651700);

            PTD_DonateInfo[playerid][19] = CreatePlayerTextDraw(playerid, 305.366607, 229.251602, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][19], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][19], 29.000000, 32.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][19], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][19], 128);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][19], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][19], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][19], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][19], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][19], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][19], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][19], 2729);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][19], 0.000000, 0.000000, 0.000000, 0.651700);

            PTD_DonateInfo[playerid][20] = CreatePlayerTextDraw(playerid, 335.799804, 229.251602, "");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][20], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][20], 29.000000, 32.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][20], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][20], 128);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][20], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][20], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][20], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][20], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][20], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][20], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][20], 2729);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][20], 0.000000, 0.000000, 0.000000, 0.651700);

            PTD_DonateInfo[playerid][21] = CreatePlayerTextDraw(playerid, 363.333404, 199.800003, ""); // Donate;
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][21], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][21], 77.000000, 86.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][21], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][21], -652148481);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][21], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][21], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][21], 0);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][21], 5);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][21], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][21], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_DonateInfo[playerid][21], 2720);
            PlayerTextDrawSetPreviewRot(playerid, PTD_DonateInfo[playerid][21], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_DonateInfo[playerid][22] = CreatePlayerTextDraw(playerid, 290.033294, 261.762695, "НACOЛ");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][22], 0.150099, 0.695500);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][22], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][22], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][22], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][22], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][22], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][22], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][22], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][22], 0);

            PTD_DonateInfo[playerid][23] = CreatePlayerTextDraw(playerid, 320.366699, 261.762695, "MЕH");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][23], 0.150099, 0.695500);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][23], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][23], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][23], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][23], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][23], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][23], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][23], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][23], 0);

            PTD_DonateInfo[playerid][24] = CreatePlayerTextDraw(playerid, 351.033508, 261.762695, "CEK");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][24], 0.150099, 0.695500);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][24], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][24], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][24], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][24], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][24], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][24], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][24], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][24], 0);

            PTD_DonateInfo[playerid][25] = CreatePlayerTextDraw(playerid, 290.433502, 233.140502, "6");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][25], 0.337300, 2.338200);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][25], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][25], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][25], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][25], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][25], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][25], 2);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][25], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][25], 0);

            PTD_DonateInfo[playerid][26] = CreatePlayerTextDraw(playerid, 320.766815, 233.140502, "00");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][26], 0.337300, 2.338200);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][26], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][26], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][26], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][26], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][26], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][26], 2);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][26], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][26], 0);

            PTD_DonateInfo[playerid][27] = CreatePlayerTextDraw(playerid, 350.533508, 233.140502, "00");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][27], 0.337300, 2.338200);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][27], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][27], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][27], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][27], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][27], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][27], 2);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][27], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][27], 0);

            PTD_DonateInfo[playerid][28] = CreatePlayerTextDraw(playerid, 321.599700, 270.473999, "Пopo£Ьc©, ckЬЪkЬ £oc¶oђЃЃo oЧЃoҐЮђЂ¶cђ!");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][28], 0.178000, 0.898800);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][28], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][28], -28929);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][28], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][28], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][28], 6);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][28], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][28], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][28], 0);

            PTD_DonateInfo[playerid][29] = CreatePlayerTextDraw(playerid, 280.533111, 288.570098, "LD_BEAT:chit");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][29], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][29], 29.000000, 33.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][29], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][29], -1275063553);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][29], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][29], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][29], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][29], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][29], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][29], 0);

            PTD_DonateInfo[playerid][30] = CreatePlayerTextDraw(playerid, 330.199798, 288.570098, "LD_BEAT:chit");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][30], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][30], 29.000000, 33.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][30], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][30], -1275063553);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][30], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][30], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][30], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][30], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][30], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][30], 0);

            PTD_DonateInfo[playerid][31] = CreatePlayerTextDraw(playerid, 295.366302, 294.062713, "LD_SPAC:white");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][31], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][31], 50.000000, 21.959800);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][31], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][31], -1275063553);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][31], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][31], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][31], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][31], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][31], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][31], 0);

            PTD_DonateInfo[playerid][32] = CreatePlayerTextDraw(playerid, 320.699707, 299.081512, "МOЗYНЕПТ");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][32], 0.235400, 1.072900);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][32], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][32], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][32], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][32], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][32], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][32], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][32], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][32], 0);

            PTD_DonateInfo[playerid][33] = CreatePlayerTextDraw(playerid, 288.366607, 290.644195, "particle:lamp_shad_64");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][33], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][33], 64.000000, 25.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][33], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][33], -167);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][33], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][33], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][33], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][33], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][33], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][33], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_DonateInfo[playerid][33], true);

            PTD_DonateInfo[playerid][34] = CreatePlayerTextDraw(playerid, 427.866302, 128.866500, "LD_BEAT:chit");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][34], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][34], 18.000000, 21.000000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][34], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][34], 336860415);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][34], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][34], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][34], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][34], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][34], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][34], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_DonateInfo[playerid][34], true);

            PTD_DonateInfo[playerid][35] = CreatePlayerTextDraw(playerid, 437.233093, 134.314804, "X");
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][35], 0.205500, 0.990100);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][35], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][35], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][35], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][35], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][35], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][35], 2);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][35], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][35], 0);

            PTD_DonateInfo[playerid][36] = CreatePlayerTextDraw(playerid, 386.499908, 234.100006, "LD_SPAC:white"); // Donate;
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][36], 0.000000, 0.000000);
            PlayerTextDrawTextSize(playerid, PTD_DonateInfo[playerid][36], 29.690000, 17.090000);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][36], 1);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][36], -836697857);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][36], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][36], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][36], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][36], 4);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][36], 0);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][36], 0);

            PTD_DonateInfo[playerid][37] = CreatePlayerTextDraw(playerid, 402.666503, 238.948104, "X3"); // Donate;
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][37], 0.384600, 1.836400);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][37], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][37], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][37], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][37], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][37], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][37], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][37], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][37], 0);

            PTD_DonateInfo[playerid][38] = CreatePlayerTextDraw(playerid, 402.666503, 231.481292, "ГOHAП"); // Donate;
            PlayerTextDrawLetterSize(playerid, PTD_DonateInfo[playerid][38], 0.195800, 0.894800);
            PlayerTextDrawAlignment(playerid, PTD_DonateInfo[playerid][38], 2);
            PlayerTextDrawColor(playerid, PTD_DonateInfo[playerid][38], -1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][38], 0);
            PlayerTextDrawSetOutline(playerid, PTD_DonateInfo[playerid][38], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_DonateInfo[playerid][38], 255);
            PlayerTextDrawFont(playerid, PTD_DonateInfo[playerid][38], 1);
            PlayerTextDrawSetProportional(playerid, PTD_DonateInfo[playerid][38], 1);
            PlayerTextDrawSetShadow(playerid, PTD_DonateInfo[playerid][38], 0);
        }
        case TD_ID_PANEL:
        {
            if(p_temp[playerid][TextDrawPanel]) return 1;
            PTD_Panel[playerid][0] = CreatePlayerTextDraw(playerid, 203.3000, 117.5701, "Box");
            PlayerTextDrawLetterSize(playerid, PTD_Panel[playerid][0], 0.0000, 24.1707);
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][0], 418.0000, 0.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][0], -1);
            PlayerTextDrawUseBox(playerid, PTD_Panel[playerid][0], 1);
            PlayerTextDrawBoxColor(playerid, PTD_Panel[playerid][0], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][0], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][0], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][0], 0);

            PTD_Panel[playerid][1] = CreatePlayerTextDraw(playerid, 208.3000, 123.0145, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][1], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][1], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][1], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][1], true);

            PTD_Panel[playerid][2] = CreatePlayerTextDraw(playerid, 259.9866, 123.0145, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][2], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][2], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][2], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][2], true);

            PTD_Panel[playerid][3] = CreatePlayerTextDraw(playerid, 311.6733, 123.0145, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][3], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][3], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][3], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][3], true);

            PTD_Panel[playerid][4] = CreatePlayerTextDraw(playerid, 363.3598, 123.0145, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][4], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][4], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][4], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][4], true);

            PTD_Panel[playerid][5] = CreatePlayerTextDraw(playerid, 208.3000, 175.2174, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][5], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][5], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][5], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][5], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][5], true);

            PTD_Panel[playerid][6] = CreatePlayerTextDraw(playerid, 259.9866, 175.2174, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][6], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][6], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][6], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][6], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][6], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][6], true);

            PTD_Panel[playerid][7] = CreatePlayerTextDraw(playerid, 311.6733, 175.2174, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][7], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][7], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][7], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][7], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][7], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][7], true);

            PTD_Panel[playerid][8] = CreatePlayerTextDraw(playerid, 363.3598, 175.2174, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][8], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][8], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][8], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][8], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][8], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][8], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][8], true);

            PTD_Panel[playerid][9] = CreatePlayerTextDraw(playerid, 208.3000, 227.4201, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][9], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][9], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][9], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][9], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][9], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][9], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][9], true);

            PTD_Panel[playerid][10] = CreatePlayerTextDraw(playerid, 259.9866, 227.4201, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][10], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][10], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][10], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][10], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][10], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][10], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][10], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][10], true);

            PTD_Panel[playerid][11] = CreatePlayerTextDraw(playerid, 311.6733, 227.4201, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][11], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][11], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][11], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][11], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][11], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][11], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][11], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][11], true);

            PTD_Panel[playerid][12] = CreatePlayerTextDraw(playerid, 363.3598, 227.4201, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][12], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][12], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][12], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][12], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][12], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][12], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][12], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][12], true);

            PTD_Panel[playerid][13] = CreatePlayerTextDraw(playerid, 208.3000, 279.6229, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][13], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][13], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][13], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][13], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][13], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][13], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][13], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][13], true);

            PTD_Panel[playerid][14] = CreatePlayerTextDraw(playerid, 259.9866, 279.6229, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][14], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][14], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][14], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][14], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][14], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][14], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][14], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][14], true);

            PTD_Panel[playerid][15] = CreatePlayerTextDraw(playerid, 311.6733, 279.6229, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][15], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][15], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][15], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][15], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][15], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][15], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][15], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][15], true);

            PTD_Panel[playerid][16] = CreatePlayerTextDraw(playerid, 363.3598, 279.6229, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][16], 50.0000, 50.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][16], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][16], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][16], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][16], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][16], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][16], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][16], true);

            PTD_Panel[playerid][17] = CreatePlayerTextDraw(playerid, 414.1665, 337.0000, "ld_chat:thumbup");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][17], 30.0000, 30.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][17], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][17], 1768516095);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][17], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][17], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][17], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][17], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][17], true);

            PTD_Panel[playerid][18] = CreatePlayerTextDraw(playerid, 414.1665, 83.1878, "ld_chat:thumbdn");
            PlayerTextDrawTextSize(playerid, PTD_Panel[playerid][18], 30.0000, 30.0000);
            PlayerTextDrawAlignment(playerid, PTD_Panel[playerid][18], 1);
            PlayerTextDrawColor(playerid, PTD_Panel[playerid][18], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Panel[playerid][18], 255);
            PlayerTextDrawFont(playerid, PTD_Panel[playerid][18], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Panel[playerid][18], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Panel[playerid][18], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Panel[playerid][18], true);
        }
        case TD_ID_PHONE:
        {
            if(p_temp[playerid][TextDrawPhone]) return 1;
            PTD_Phone[playerid][0] = CreatePlayerTextDraw(playerid, 481.0000, 133.5955, "flin_mobile:flin_mobile_type4"); // пусто

            PTD_Phone[playerid][1] = CreatePlayerTextDraw(playerid, 509.3998, 378.9999, "flin_mobile:flin_mobile_iconcall"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_Phone[playerid][1], 19.0000, 21.0000);
            PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Phone[playerid][1], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Phone[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][1], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Phone[playerid][1], true);

            PTD_Phone[playerid][2] = CreatePlayerTextDraw(playerid, 532.6004, 378.9999, "flin_mobile:flin_mobile_iconcontact"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_Phone[playerid][2], 19.0000, 21.0000);
            PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Phone[playerid][2], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Phone[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][2], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Phone[playerid][2], true);

            PTD_Phone[playerid][3] = CreatePlayerTextDraw(playerid, 556.2006, 378.9999, "flin_mobile:flin_mobile_iconmessages"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_Phone[playerid][3], 19.0000, 21.0000);
            PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_Phone[playerid][3], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Phone[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][3], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Phone[playerid][3], true);

            PTD_Phone[playerid][4] = CreatePlayerTextDraw(playerid, 579.8009, 378.9999, "flin_mobile:flin_mobile_iconhouse"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_Phone[playerid][4], 19.0000, 21.0000);
            PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Phone[playerid][4], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Phone[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][4], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Phone[playerid][4], true);

            PTD_Phone[playerid][5] = CreatePlayerTextDraw(playerid, 554.8001, 207.9201, "00:00"); // пусто
            PlayerTextDrawLetterSize(playerid, PTD_Phone[playerid][5], 0.5163, 3.3819);
            PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][5], 2);
            PlayerTextDrawColor(playerid, PTD_Phone[playerid][5], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Phone[playerid][5], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][5], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][5], 0);

            PTD_Phone[playerid][6] = CreatePlayerTextDraw(playerid, 554.4000, 238.2845, "CЧ,_27_ѓap¶a"); // пусто
            PlayerTextDrawLetterSize(playerid, PTD_Phone[playerid][6], 0.1871, 1.4903);
            PlayerTextDrawAlignment(playerid, PTD_Phone[playerid][6], 2);
            PlayerTextDrawColor(playerid, PTD_Phone[playerid][6], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Phone[playerid][6], 187);
            PlayerTextDrawFont(playerid, PTD_Phone[playerid][6], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Phone[playerid][6], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Phone[playerid][6], 1);
        }
        case TD_ID_CASE:
        {
            if(p_temp[playerid][TextDrawCase]) return 1;
            PTD_Case[playerid][0] = CreatePlayerTextDraw(playerid, 149.0000, 11.1422, "flin_case:flin_case_bg"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_Case[playerid][0], 342.0000, 424.0000);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][0], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][0], 0);

            PTD_Case[playerid][1] = CreatePlayerTextDraw(playerid, 262.1997, 359.5866, "flin_case:flin_case_openbutton"); // кнопка открыть
            PlayerTextDrawTextSize(playerid, PTD_Case[playerid][1], 87.0000, 31.0000);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][1], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][1], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Case[playerid][1], true);

            PTD_Case[playerid][2] = CreatePlayerTextDraw(playerid, 392.3999, 372.6842, "10"); // кол-во доступно
            PlayerTextDrawLetterSize(playerid, PTD_Case[playerid][2], 0.2396, 1.3710);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][2], 2);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][2], -5963521);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][2], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][2], 0);

            PTD_Case[playerid][3] = CreatePlayerTextDraw(playerid, 249.1996, 373.1820, "10000"); // кол-во монет
            PlayerTextDrawLetterSize(playerid, PTD_Case[playerid][3], 0.2284, 1.3559);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][3], -5963521);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][3], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][3], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][3], 0);

            PTD_Case[playerid][4] = CreatePlayerTextDraw(playerid, 366.1997, 72.3684, "flin_case:flin_case_rightarrow"); // стрелка вправо
            PlayerTextDrawTextSize(playerid, PTD_Case[playerid][4], 49.0000, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][4], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][4], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Case[playerid][4], true);

            PTD_Case[playerid][5] = CreatePlayerTextDraw(playerid, 224.5997, 71.8711, "flin_case:flin_case_leftarrow"); // стрелка влево
            PlayerTextDrawTextSize(playerid, PTD_Case[playerid][5], 49.0000, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][5], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][5], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][5], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Case[playerid][5], true);

            PTD_Case[playerid][6] = CreatePlayerTextDraw(playerid, 319.9995, 75.5107, "МpaҐЬ¶eЮ©c¶ҐeЃЃ®Э"); // название кейса
            PlayerTextDrawLetterSize(playerid, PTD_Case[playerid][6], 0.2101, 1.6447);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][6], 2);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][6], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][6], 57);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][6], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][6], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][6], 1);

            PTD_Case[playerid][7] = CreatePlayerTextDraw(playerid, 344.9999, 344.6531, "flin_case:flin_case_buybutton"); // покупка
            PlayerTextDrawTextSize(playerid, PTD_Case[playerid][7], 26.0000, 67.0000);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][7], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][7], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][7], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][7], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Case[playerid][7], true);

            PTD_Case[playerid][8] = CreatePlayerTextDraw(playerid, 358.3998, 384.6310, "9999"); // покупка
            PlayerTextDrawLetterSize(playerid, PTD_Case[playerid][8], 0.1852, 1.1368);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][8], 2);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][8], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][8], 48);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][8], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][8], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][8], 1);

            PTD_Case[playerid][9] = CreatePlayerTextDraw(playerid, 423.7996, 36.0311, "flin_equipment:flin_equipment_closebutton"); // пусто
            PlayerTextDrawTextSize(playerid, PTD_Case[playerid][9], 32.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_Case[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_Case[playerid][9], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][9], 255);
            PlayerTextDrawFont(playerid, PTD_Case[playerid][9], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][9], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][9], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Case[playerid][9], true);

            // slots backgraund
            PTD_Case[playerid][10] = CreatePlayerTextDraw(playerid, 229.8000, 119.6576, "flin_case:flin_case_slot"); // слот 1
            PTD_Case[playerid][11] = CreatePlayerTextDraw(playerid, 274.6000, 119.6576, "flin_case:flin_case_slot"); // слот 2
            PTD_Case[playerid][12] = CreatePlayerTextDraw(playerid, 319.4996, 119.6576, "flin_case:flin_case_slot"); // слот 3
            PTD_Case[playerid][13] = CreatePlayerTextDraw(playerid, 364.5996, 119.6576, "flin_case:flin_case_slot"); // слот 4
            PTD_Case[playerid][14] = CreatePlayerTextDraw(playerid, 229.6996, 175.5066, "flin_case:flin_case_slot"); // слот 5
            PTD_Case[playerid][15] = CreatePlayerTextDraw(playerid, 274.4992, 175.5066, "flin_case:flin_case_slot"); // слот 6
            PTD_Case[playerid][16] = CreatePlayerTextDraw(playerid, 319.2994, 175.5066, "flin_case:flin_case_slot"); // слот 7
            PTD_Case[playerid][17] = CreatePlayerTextDraw(playerid, 364.2994, 175.5066, "flin_case:flin_case_slot"); // слот 8
            PTD_Case[playerid][18] = CreatePlayerTextDraw(playerid, 229.8995, 231.7554, "flin_case:flin_case_slot"); // слот 9
            PTD_Case[playerid][19] = CreatePlayerTextDraw(playerid, 274.9992, 231.7554, "flin_case:flin_case_slot"); // слот 10
            PTD_Case[playerid][20] = CreatePlayerTextDraw(playerid, 319.6990, 231.7554, "flin_case:flin_case_slot"); // слот 11
            PTD_Case[playerid][21] = CreatePlayerTextDraw(playerid, 364.4989, 231.7554, "flin_case:flin_case_slot"); // слот 12
            PTD_Case[playerid][22] = CreatePlayerTextDraw(playerid, 229.6988, 288.0043, "flin_case:flin_case_slot"); // слот 13
            PTD_Case[playerid][23] = CreatePlayerTextDraw(playerid, 274.4988, 288.0043, "flin_case:flin_case_slot"); // слот 14
            PTD_Case[playerid][24] = CreatePlayerTextDraw(playerid, 319.2987, 288.0043, "flin_case:flin_case_slot"); // слот 15
            PTD_Case[playerid][25] = CreatePlayerTextDraw(playerid, 364.3988, 288.0043, "flin_case:flin_case_slot"); // слот 16

            // preview models
            PTD_Case[playerid][26] = CreatePlayerTextDraw(playerid, 229.8000, 119.6576, ""); // 1
            PTD_Case[playerid][27] = CreatePlayerTextDraw(playerid, 274.5999, 119.6576, ""); // 2
            PTD_Case[playerid][28] = CreatePlayerTextDraw(playerid, 319.3995, 119.6576, ""); // 3
            PTD_Case[playerid][29] = CreatePlayerTextDraw(playerid, 364.1997, 119.6576, ""); // 4
            PTD_Case[playerid][30] = CreatePlayerTextDraw(playerid, 229.8000, 175.4089, ""); // 5
            PTD_Case[playerid][31] = CreatePlayerTextDraw(playerid, 274.5999, 175.4089, ""); // 6
            PTD_Case[playerid][32] = CreatePlayerTextDraw(playerid, 319.3995, 175.4089, ""); // 7
            PTD_Case[playerid][33] = CreatePlayerTextDraw(playerid, 364.1997, 175.4089, ""); // 8
            PTD_Case[playerid][34] = CreatePlayerTextDraw(playerid, 229.8000, 231.1600, ""); // 9
            PTD_Case[playerid][35] = CreatePlayerTextDraw(playerid, 274.5999, 231.1600, ""); // 10
            PTD_Case[playerid][36] = CreatePlayerTextDraw(playerid, 319.3995, 231.1600, ""); // 11
            PTD_Case[playerid][37] = CreatePlayerTextDraw(playerid, 364.1997, 231.1600, ""); // 12
            PTD_Case[playerid][38] = CreatePlayerTextDraw(playerid, 229.8000, 286.9111, ""); // 13
            PTD_Case[playerid][39] = CreatePlayerTextDraw(playerid, 274.5999, 286.9111, ""); // 14
            PTD_Case[playerid][40] = CreatePlayerTextDraw(playerid, 319.3995, 286.9111, ""); // 15
            PTD_Case[playerid][41] = CreatePlayerTextDraw(playerid, 364.1997, 286.9111, ""); // 16

            // text slots
            PTD_Case[playerid][42] = CreatePlayerTextDraw(playerid, 252.3999, 158.6398, "10000000"); // кол-во слота 1
            PTD_Case[playerid][43] = CreatePlayerTextDraw(playerid, 296.7998, 158.6398, "10000000"); // кол-во слота 2
            PTD_Case[playerid][44] = CreatePlayerTextDraw(playerid, 341.9999, 158.6398, "10000000"); // кол-во слота 3
            PTD_Case[playerid][45] = CreatePlayerTextDraw(playerid, 386.3995, 158.6398, "10000000"); // кол-во слота 4
            PTD_Case[playerid][46] = CreatePlayerTextDraw(playerid, 252.3999, 214.3907, "10000000"); // кол-во слота 5
            PTD_Case[playerid][47] = CreatePlayerTextDraw(playerid, 296.7998, 214.3907, "10000000"); // кол-во слота 6
            PTD_Case[playerid][48] = CreatePlayerTextDraw(playerid, 341.9999, 214.3907, "10000000"); // кол-во слота 7
            PTD_Case[playerid][49] = CreatePlayerTextDraw(playerid, 386.3995, 214.3907, "10000000"); // кол-во слота 8
            PTD_Case[playerid][50] = CreatePlayerTextDraw(playerid, 252.3999, 270.1416, "10000000"); // кол-во слота 9
            PTD_Case[playerid][51] = CreatePlayerTextDraw(playerid, 296.7998, 270.1416, "10000000"); // кол-во слота 10
            PTD_Case[playerid][52] = CreatePlayerTextDraw(playerid, 341.9999, 270.1416, "10000000"); // кол-во слота 11
            PTD_Case[playerid][53] = CreatePlayerTextDraw(playerid, 386.3995, 270.1416, "10000000"); // кол-во слота 12
            PTD_Case[playerid][54] = CreatePlayerTextDraw(playerid, 252.3999, 325.8919, "10000000"); // кол-во слота 13
            PTD_Case[playerid][55] = CreatePlayerTextDraw(playerid, 296.7998, 325.8919, "10000000"); // кол-во слота 14
            PTD_Case[playerid][56] = CreatePlayerTextDraw(playerid, 341.9999, 325.8919, "10000000"); // кол-во слота 15
            PTD_Case[playerid][57] = CreatePlayerTextDraw(playerid, 386.3995, 325.8919, "10000000"); // кол-во слота 16

            for(new i = 57; i != 9; i--)
            {
                if(10 <= i <= 25)
                { // slots backgraund
                    PlayerTextDrawTextSize(playerid, PTD_Case[playerid][i], 45.0000, 56.0000);
                    PlayerTextDrawAlignment(playerid, PTD_Case[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_Case[playerid][i], -2);
                    PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_Case[playerid][i], 4);
                    PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][i], 0);
                }
                if(26 <= i <= 41)
                { // preview models
                    PlayerTextDrawTextSize(playerid, PTD_Case[playerid][i], 45.0000, 56.0000);
                    PlayerTextDrawAlignment(playerid, PTD_Case[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_Case[playerid][i], -1);
                    PlayerTextDrawFont(playerid, PTD_Case[playerid][i], 5);
                    PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][i], 0);
                    PlayerTextDrawSetPreviewModel(playerid, PTD_Case[playerid][i], 0);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_Case[playerid][i], 0.0000, 0.0000, 0.0000, 1.0000);
                    PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][i], 0xFFFFFF00);
                }
                if(42 <= i <= 57)
                {// text slots
                    PlayerTextDrawLetterSize(playerid, PTD_Case[playerid][i], 0.2055, 1.4055);
                    PlayerTextDrawAlignment(playerid, PTD_Case[playerid][i], 2);
                    PlayerTextDrawColor(playerid, PTD_Case[playerid][i], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_Case[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_Case[playerid][i], 2);
                    PlayerTextDrawSetProportional(playerid, PTD_Case[playerid][i], 1);
                    PlayerTextDrawSetShadow(playerid, PTD_Case[playerid][i], 1);
                }
            }
        }
        case TD_ID_ROULETTE:
        {
            if(p_temp[playerid][TextDrawRoulette]) return 1;
            PTD_Roulette[playerid][0] = CreatePlayerTextDraw(playerid, -23.3999, 4.1732, "flin_roulette:flin_roulette_bg"); // bg roulette
            PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][0], 688.0000, 438.0000);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][0], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][0], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][0], 0);

            PTD_Roulette[playerid][1] = CreatePlayerTextDraw(playerid, 393.5993, 307.4754, "10"); // количество рулеток
            PlayerTextDrawLetterSize(playerid, PTD_Roulette[playerid][1], 0.2140, 1.4105);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][1], 2);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][1], -5963521);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][1], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][1], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][1], 0);

            PTD_Roulette[playerid][2] = CreatePlayerTextDraw(playerid, 284.1997, 325.2398, "flin_roulette:flin_roulette_rollbutton"); // кнопка крутить
            PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][2], 80.0000, 98.0000);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][2], -2);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][2], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Roulette[playerid][2], true);

            PTD_Roulette[playerid][3] = CreatePlayerTextDraw(playerid, 280.9996, 297.3641, "flin_roulette:flin_roulette_buybutton"); // кнопка купить
            PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][3], 84.0000, 28.0000);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][3], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][3], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Roulette[playerid][3], true);

            PTD_Roulette[playerid][4] = CreatePlayerTextDraw(playerid, 249.5994, 307.4754, "10000"); // количество ‘ћ
            PlayerTextDrawLetterSize(playerid, PTD_Roulette[playerid][4], 0.2140, 1.4105);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][4], -5963521);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][4], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][4], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][4], 0);

            PTD_Roulette[playerid][5] = CreatePlayerTextDraw(playerid, 322.7998, 303.9909, "ќЅЌќ¬»“№ «ј 10_FM"); // текст кнопки купить
            PlayerTextDrawLetterSize(playerid, PTD_Roulette[playerid][5], 0.1957, 1.4357);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][5], 2);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][5], 255);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][5], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][5], 1);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][5], 0);

            PTD_Roulette[playerid][6] = CreatePlayerTextDraw(playerid, 430.2001, 67.3910, "flin_equipment:flin_equipment_closebutton"); // close
            PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][6], 34.0000, 35.0000);
            PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_Roulette[playerid][6], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_Roulette[playerid][6], 4);
            PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][6], 0);
            PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][6], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_Roulette[playerid][6], true);

            PTD_Roulette[playerid][7] = CreatePlayerTextDraw(playerid, 240.9998, 127.1242, "flin_roulette:flin_roulette_bronze"); // серебрена€ рулетка
            PTD_Roulette[playerid][8] = CreatePlayerTextDraw(playerid, 293.7998, 127.1242, "flin_roulette:flin_roulette_silver_use"); // бронзво€ рулетка юз
            PTD_Roulette[playerid][9] = CreatePlayerTextDraw(playerid, 346.1997, 127.1242, "flin_roulette:flin_roulette_gold"); // золота€ рулетка

            //slots backgraund
            PTD_Roulette[playerid][10] = CreatePlayerTextDraw(playerid, 139.8000, 166.4488, "flin_roulette:flin_roulette_slot"); // 1 slot
            PTD_Roulette[playerid][11] = CreatePlayerTextDraw(playerid, 185.3999, 166.4488, "flin_roulette:flin_roulette_slot"); // 2 slot
            PTD_Roulette[playerid][12] = CreatePlayerTextDraw(playerid, 230.1999, 166.4488, "flin_roulette:flin_roulette_slot"); // 3 slot
            PTD_Roulette[playerid][13] = CreatePlayerTextDraw(playerid, 275.7998, 166.4488, "flin_roulette:flin_roulette_slot"); // 4 slot
            PTD_Roulette[playerid][14] = CreatePlayerTextDraw(playerid, 320.9996, 166.4488, "flin_roulette:flin_roulette_slot"); // 5 slot
            PTD_Roulette[playerid][15] = CreatePlayerTextDraw(playerid, 366.1997, 166.4488, "flin_roulette:flin_roulette_slot"); // 6 slot
            PTD_Roulette[playerid][16] = CreatePlayerTextDraw(playerid, 410.9996, 166.4488, "flin_roulette:flin_roulette_slot"); // 7 slot use
            PTD_Roulette[playerid][17] = CreatePlayerTextDraw(playerid, 456.5999, 166.4488, "flin_roulette:flin_roulette_slot"); // 8 slot
            PTD_Roulette[playerid][18] = CreatePlayerTextDraw(playerid, 139.7998, 227.1777, "flin_roulette:flin_roulette_slot"); // 9 slot
            PTD_Roulette[playerid][19] = CreatePlayerTextDraw(playerid, 185.3999, 227.1777, "flin_roulette:flin_roulette_slot"); // 10 slot
            PTD_Roulette[playerid][20] = CreatePlayerTextDraw(playerid, 230.5997, 227.1777, "flin_roulette:flin_roulette_slot"); // 11 slot
            PTD_Roulette[playerid][21] = CreatePlayerTextDraw(playerid, 275.7998, 227.1777, "flin_roulette:flin_roulette_slot"); // 12 slot
            PTD_Roulette[playerid][22] = CreatePlayerTextDraw(playerid, 320.5997, 227.1777, "flin_roulette:flin_roulette_slot"); // 13 slot
            PTD_Roulette[playerid][23] = CreatePlayerTextDraw(playerid, 366.1994, 227.1777, "flin_roulette:flin_roulette_slot"); // 14 slot
            PTD_Roulette[playerid][24] = CreatePlayerTextDraw(playerid, 411.3995, 227.1777, "flin_roulette:flin_roulette_slot"); // 15 slot
            PTD_Roulette[playerid][25] = CreatePlayerTextDraw(playerid, 456.1994, 227.1777, "flin_roulette:flin_roulette_slot"); // 16 slot

            // slots previews
            PTD_Roulette[playerid][26] = CreatePlayerTextDraw(playerid, 141.0000, 166.9467, ""); // лот 1
            PTD_Roulette[playerid][27] = CreatePlayerTextDraw(playerid, 186.6000, 166.9467, ""); // лот 2
            PTD_Roulette[playerid][28] = CreatePlayerTextDraw(playerid, 231.3999, 166.9467, ""); // лот 3
            PTD_Roulette[playerid][29] = CreatePlayerTextDraw(playerid, 276.5999, 166.9467, ""); // лот 4
            PTD_Roulette[playerid][30] = CreatePlayerTextDraw(playerid, 321.7998, 166.9467, ""); // лот 5
            PTD_Roulette[playerid][31] = CreatePlayerTextDraw(playerid, 367.3999, 166.9467, ""); // лот 6
            PTD_Roulette[playerid][32] = CreatePlayerTextDraw(playerid, 411.7998, 166.9467, ""); // лот 7
            PTD_Roulette[playerid][33] = CreatePlayerTextDraw(playerid, 457.3998, 166.9467, ""); // лот 8
            PTD_Roulette[playerid][34] = CreatePlayerTextDraw(playerid, 140.5997, 227.6755, ""); // лот 9
            PTD_Roulette[playerid][35] = CreatePlayerTextDraw(playerid, 186.1999, 227.6755, ""); // лот 10
            PTD_Roulette[playerid][36] = CreatePlayerTextDraw(playerid, 231.8000, 227.6755, ""); // лот 11
            PTD_Roulette[playerid][37] = CreatePlayerTextDraw(playerid, 277.0000, 227.6755, ""); // лот 12
            PTD_Roulette[playerid][38] = CreatePlayerTextDraw(playerid, 321.7998, 227.6755, ""); // лот 13
            PTD_Roulette[playerid][39] = CreatePlayerTextDraw(playerid, 367.0000, 227.6755, ""); // лот 14
            PTD_Roulette[playerid][40] = CreatePlayerTextDraw(playerid, 412.1997, 227.6755, ""); // лот 15
            PTD_Roulette[playerid][41] = CreatePlayerTextDraw(playerid, 457.3998, 227.6755, ""); // лот 16

            // slots texts
            PTD_Roulette[playerid][42] = CreatePlayerTextDraw(playerid, 160.7998, 200.9510, "10000000"); // кол-во лота 1
            PTD_Roulette[playerid][43] = CreatePlayerTextDraw(playerid, 206.3997, 200.9510, "10000000"); // кол-во слота 2
            PTD_Roulette[playerid][44] = CreatePlayerTextDraw(playerid, 251.5997, 200.9510, "10000000"); // кол-во слота 3
            PTD_Roulette[playerid][45] = CreatePlayerTextDraw(playerid, 297.1997, 200.9510, "10000000"); // кол-во слота 4
            PTD_Roulette[playerid][46] = CreatePlayerTextDraw(playerid, 341.9996, 200.9510, "10000000"); // кол-во слота 5
            PTD_Roulette[playerid][47] = CreatePlayerTextDraw(playerid, 387.5993, 200.9510, "10000000"); // кол-во слота 6
            PTD_Roulette[playerid][48] = CreatePlayerTextDraw(playerid, 431.9992, 200.9510, "10000000"); // кол-во слота 7
            PTD_Roulette[playerid][49] = CreatePlayerTextDraw(playerid, 477.5993, 200.9510, "10000000"); // кол-во слота 8
            PTD_Roulette[playerid][50] = CreatePlayerTextDraw(playerid, 161.1992, 261.6799, "10000000"); // кол-во слота 9
            PTD_Roulette[playerid][51] = CreatePlayerTextDraw(playerid, 206.7991, 261.6799, "10000000"); // кол-во слота 10
            PTD_Roulette[playerid][52] = CreatePlayerTextDraw(playerid, 251.9989, 261.6799, "10000000"); // кол-во слота 11
            PTD_Roulette[playerid][53] = CreatePlayerTextDraw(playerid, 297.1986, 261.6799, "10000000"); // кол-во слота 12
            PTD_Roulette[playerid][54] = CreatePlayerTextDraw(playerid, 341.9985, 261.6799, "10000000"); // кол-во слота 13
            PTD_Roulette[playerid][55] = CreatePlayerTextDraw(playerid, 387.5982, 261.6799, "10000000"); // кол-во слота 14
            PTD_Roulette[playerid][56] = CreatePlayerTextDraw(playerid, 432.7984, 261.6799, "10000000"); // кол-во слота 15
            PTD_Roulette[playerid][57] = CreatePlayerTextDraw(playerid, 477.5982, 261.6799, "10000000"); // кол-во слота 16

            for(new i = 57; i != 9; i--)
            {
                if(42 <= i <= 57)
                {// slots texts
                    PlayerTextDrawLetterSize(playerid, PTD_Roulette[playerid][i], 0.1808, 1.4306);
                    PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][i], 2);
                    PlayerTextDrawColor(playerid, PTD_Roulette[playerid][i], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_Roulette[playerid][i], 2);
                    PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][i], 1);
                    PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][i], 1);
                }
                if(26 <= i <= 41)
                {// slots previews
                    PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][i], 41.0000, 51.0000);
                    PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_Roulette[playerid][i], -1);
                    PlayerTextDrawFont(playerid, PTD_Roulette[playerid][i], 5);
                    PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][i], 0);
                    PlayerTextDrawSetPreviewModel(playerid, PTD_Roulette[playerid][i], 1274);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_Roulette[playerid][i], 0.0000, 0.0000, 0.0000, 1.0000);
                    PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][i], 0xFFFFFF00);
                }
                if(10 <= i <= 25)
                {//slots backgraund
                    PlayerTextDrawTextSize(playerid, PTD_Roulette[playerid][i], 43.0000, 53.0000);
                    PlayerTextDrawAlignment(playerid, PTD_Roulette[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_Roulette[playerid][i], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_Roulette[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_Roulette[playerid][i], 4);
                    PlayerTextDrawSetProportional(playerid, PTD_Roulette[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_Roulette[playerid][i], 0);
                }
            }
        }
        case TD_ID_PLAYER_MENU:
        {   // фон круга
            PTD_PlayerMenu[playerid][0] = CreatePlayerTextDraw(playerid, 195.3995, 71.3731, "flin_menu:flin_menu_background"); // background целый
            PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][0], 246.0000, 306.0000);

            PTD_PlayerMenu[playerid][1] = CreatePlayerTextDraw(playerid, 299.7001, 199.2088, "flin_menu:flin_menu_exiticon_11"); // закрыть
            PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][1], 39.0000, 48.0000);
            PlayerTextDrawSetSelectable(playerid, PTD_PlayerMenu[playerid][1], true);

            // иконки круга
            PTD_PlayerMenu[playerid][2] = CreatePlayerTextDraw(playerid, 295.3999, 81.82640, "flin_menu:flin_menu_houseicon_1"); // icon1
            PTD_PlayerMenu[playerid][3] = CreatePlayerTextDraw(playerid, 348.2000, 105.2220, "flin_menu:flin_menu_assistanceicon_2"); // icon2
            PTD_PlayerMenu[playerid][4] = CreatePlayerTextDraw(playerid, 243.7998, 105.2220, "flin_menu:flin_menu_caricon_3"); // icon3
            PTD_PlayerMenu[playerid][5] = CreatePlayerTextDraw(playerid, 379.3998, 164.9552, "flin_menu:flin_menu_orgranizationicon_4"); // icon4
            PTD_PlayerMenu[playerid][6] = CreatePlayerTextDraw(playerid, 210.5998, 163.4618, "flin_menu:flin_menu_offericon_5"); // icon5
            PTD_PlayerMenu[playerid][7] = CreatePlayerTextDraw(playerid, 378.1998, 230.1640, "flin_menu:flin_menu_familyicon_6"); // icon6
            PTD_PlayerMenu[playerid][8] = CreatePlayerTextDraw(playerid, 209.3999, 229.6663, "flin_menu:flin_menu_inventoryicon_7"); // icon7
            PTD_PlayerMenu[playerid][9] = CreatePlayerTextDraw(playerid, 348.9999, 283.4263, "flin_menu:flin_menu_animicon_8"); // icon8
            PTD_PlayerMenu[playerid][10] = CreatePlayerTextDraw(playerid, 242.1999, 282.9285, "flin_menu:flin_menu_bindericon_9"); // icon9
            PTD_PlayerMenu[playerid][11] = CreatePlayerTextDraw(playerid, 296.6000, 310.8039, "flin_menu:flin_menu_donaticon_10"); // icon10

            // ники на круге
            PTD_PlayerMenu[playerid][12] = CreatePlayerTextDraw(playerid, 318.7998, 103.8844, "V.Testovichev"); // 1 слот
            PTD_PlayerMenu[playerid][13] = CreatePlayerTextDraw(playerid, 374.3996, 131.7599, "P.Krugliy~n~(ID:0)"); // 2 слот
            PTD_PlayerMenu[playerid][14] = CreatePlayerTextDraw(playerid, 261.9997, 130.7644, "V.Uzer~n~(ID:0)"); // 3 слот
            PTD_PlayerMenu[playerid][15] = CreatePlayerTextDraw(playerid, 401.5999, 188.0086, "V.Stasenko~n~(ID:0)"); // 4 слот
            PTD_PlayerMenu[playerid][16] = CreatePlayerTextDraw(playerid, 233.5998, 187.0130, "T.Test~n~(ID:0)"); // 5 слот
            PTD_PlayerMenu[playerid][17] = CreatePlayerTextDraw(playerid, 401.1998, 256.7019, "A.Damian~n~(ID:0)"); // 6 слот
            PTD_PlayerMenu[playerid][18] = CreatePlayerTextDraw(playerid, 233.4996, 256.2041, "F.RolePlay~n~(ID:0)"); // 7 слот
            PTD_PlayerMenu[playerid][19] = CreatePlayerTextDraw(playerid, 373.5997, 309.9641, "V.Kravchuk~n~(ID:0)"); // 8 слот
            PTD_PlayerMenu[playerid][20] = CreatePlayerTextDraw(playerid, 263.8995, 309.4664, "F.RolePlay~n~(ID:0)"); // 9 слот
            PTD_PlayerMenu[playerid][21] = CreatePlayerTextDraw(playerid, 318.8002, 338.3370, "D.Costello~n~(ID:0)"); // 10 слот

            PTD_PlayerMenu[playerid][22] = CreatePlayerTextDraw(playerid, 313.2000, 88.2974, "flin_menu:flin_menu_usericon"); // 1 слот
            PTD_PlayerMenu[playerid][23] = CreatePlayerTextDraw(playerid, 370.1998, 115.6752, "flin_menu:flin_menu_usericon"); // 2 слот
            PTD_PlayerMenu[playerid][24] = CreatePlayerTextDraw(playerid, 257.3996, 115.6752, "flin_menu:flin_menu_usericon"); // 3 слот
            PTD_PlayerMenu[playerid][25] = CreatePlayerTextDraw(playerid, 396.5994, 171.4264, "flin_menu:flin_menu_usericon"); // 4 слот
            PTD_PlayerMenu[playerid][26] = CreatePlayerTextDraw(playerid, 228.9996, 170.9286, "flin_menu:flin_menu_usericon"); // 5 слот
            PTD_PlayerMenu[playerid][27] = CreatePlayerTextDraw(playerid, 396.5994, 240.1197, "flin_menu:flin_menu_usericon"); // 6 слот
            PTD_PlayerMenu[playerid][28] = CreatePlayerTextDraw(playerid, 227.7996, 239.6217, "flin_menu:flin_menu_usericon"); // 7 слот
            PTD_PlayerMenu[playerid][29] = CreatePlayerTextDraw(playerid, 367.3992, 292.8841, "flin_menu:flin_menu_usericon"); // 8 слот
            PTD_PlayerMenu[playerid][30] = CreatePlayerTextDraw(playerid, 258.1994, 292.8840, "flin_menu:flin_menu_usericon"); // 9 слот
            PTD_PlayerMenu[playerid][31] = CreatePlayerTextDraw(playerid, 314.9996, 321.2575, "flin_menu:flin_menu_usericon"); // 10 слот

            for(new i = 31; i != -1; i--)
            {
                if(i <= 1)
                {
                    PlayerTextDrawAlignment(playerid, PTD_PlayerMenu[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_PlayerMenu[playerid][i], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_PlayerMenu[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_PlayerMenu[playerid][i], 4);
                    PlayerTextDrawSetProportional(playerid, PTD_PlayerMenu[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_PlayerMenu[playerid][i], 0);
                }
                if(2 <= i <= 11)
                {
                    PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][i], 47.0000, 55.0000);
                    PlayerTextDrawAlignment(playerid, PTD_PlayerMenu[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_PlayerMenu[playerid][i], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_PlayerMenu[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_PlayerMenu[playerid][i], 4);
                    PlayerTextDrawSetProportional(playerid, PTD_PlayerMenu[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_PlayerMenu[playerid][i], 0);
                    PlayerTextDrawSetSelectable(playerid, PTD_PlayerMenu[playerid][i], true);
                }
                if(12 <= i <= 21)
                {
                    PlayerTextDrawLetterSize(playerid, PTD_PlayerMenu[playerid][i], 0.1678, 1.2015);
                    PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][i], 35.0000, 50.0000);
                    PlayerTextDrawAlignment(playerid, PTD_PlayerMenu[playerid][i], 2);
                    PlayerTextDrawColor(playerid, PTD_PlayerMenu[playerid][i], -1);
                    PlayerTextDrawUseBox(playerid, PTD_PlayerMenu[playerid][i], 1);
                    PlayerTextDrawBoxColor(playerid, PTD_PlayerMenu[playerid][i], 0);
                    PlayerTextDrawBackgroundColor(playerid, PTD_PlayerMenu[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_PlayerMenu[playerid][i], 2);
                    PlayerTextDrawSetProportional(playerid, PTD_PlayerMenu[playerid][i], 1);
                    PlayerTextDrawSetShadow(playerid, PTD_PlayerMenu[playerid][i], 0);
                    PlayerTextDrawSetSelectable(playerid, PTD_PlayerMenu[playerid][i], true);
                }
                if(22 <= i <= 31)
                {
                    PlayerTextDrawTextSize(playerid, PTD_PlayerMenu[playerid][i], 9.0000, 11.0000);
                    PlayerTextDrawAlignment(playerid, PTD_PlayerMenu[playerid][i], 1);
                    PlayerTextDrawColor(playerid, PTD_PlayerMenu[playerid][i], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_PlayerMenu[playerid][i], 255);
                    PlayerTextDrawFont(playerid, PTD_PlayerMenu[playerid][i], 4);
                    PlayerTextDrawSetProportional(playerid, PTD_PlayerMenu[playerid][i], 0);
                    PlayerTextDrawSetShadow(playerid, PTD_PlayerMenu[playerid][i], 0);
                }
            }
        }
        case TD_ID_SERVICE_TUNE:
        {
            PTD_ServiceTune[playerid][0] = CreatePlayerTextDraw(playerid, 67.9999, 404.0440, "1/2"); // номераци€ страниц
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][0], 0.2476, 1.7790);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][0], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][0], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][0], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][0], 0);

            PTD_ServiceTune[playerid][1] = CreatePlayerTextDraw(playerid, 28.2000, 353.1152, "flin_sto:flin_sto_rozval_shozdenie"); // иконка 4 слота
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][1], 26.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][1], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][1], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][1], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][1], 0);

            PTD_ServiceTune[playerid][2] = CreatePlayerTextDraw(playerid, 28.2000, 308.8132, "flin_sto:flin_sto_prostavki_stupicu"); // иконка 3 слота
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][2], 26.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][2], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][2], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][2], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][2], 0);

            PTD_ServiceTune[playerid][3] = CreatePlayerTextDraw(playerid, 28.2000, 264.5108, "flin_sto:flin_sto_wheel_width"); // иконка 2 слота
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][3], 26.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][3], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][3], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][3], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][3], 0);

            PTD_ServiceTune[playerid][4] = CreatePlayerTextDraw(playerid, 28.6000, 220.2088, "flin_sto:flin_sto_wheel_height"); // иконка первого слота
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][4], 26.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][4], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][4], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][4], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][4], 0);

            PTD_ServiceTune[playerid][5] = CreatePlayerTextDraw(playerid, 562.5999, 229.6661, "flin_sto:flin_sto_podveska_down"); // нижн€€ ось
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][5], 51.0000, 29.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][5], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][5], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][5], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][5], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][5], true);

            PTD_ServiceTune[playerid][6] = CreatePlayerTextDraw(playerid, 562.5999, 189.8441, "flin_sto:flin_sto_podveska_up_choose"); // верхн€€ ось
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][6], 51.0000, 29.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][6], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][6], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][6], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][6], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][6], true);

            PTD_ServiceTune[playerid][7] = CreatePlayerTextDraw(playerid, 573.7993, 298.8572, "flin_sto:flin_sto_close"); // закрыт тд
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][7], 50.0000, 63.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][7], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][7], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][7], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][7], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][7], true);

            PTD_ServiceTune[playerid][8] = CreatePlayerTextDraw(playerid, 528.8004, 366.2127, "100_000"); // цена
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][8], 0.4047, 2.1524);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][8], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][8], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][8], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][8], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][8], 0);

            PTD_ServiceTune[playerid][9] = CreatePlayerTextDraw(playerid, 67.7997, 178.5111, "flin_sto:flin_sto_suspension"); // иконка заглавной
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][9], 26.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][9], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][9], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][9], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][9], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][9], 0);

            PTD_ServiceTune[playerid][10] = CreatePlayerTextDraw(playerid, 103.5992, 186.1332, "МoЪҐecka"); // текст заглавного слота
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][10], 0.3084, 1.5900);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][10], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][10], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][10], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][10], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][10], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][10], 0);

            PTD_ServiceTune[playerid][11] = CreatePlayerTextDraw(playerid, 65.1996, 227.8309, "Hac¶poЭka_paЯѓepa_ЪЬcka"); // текст 1 слота
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][11], 0.3084, 1.5900);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][11], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][11], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][11], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][11], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][11], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][11], 0);

            PTD_ServiceTune[playerid][12] = CreatePlayerTextDraw(playerid, 65.1996, 272.6307, "Hac¶poЭka_•ЬpЬЃ®_ЪЬcka"); // текст 2 слота
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][12], 0.3084, 1.5900);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][12], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][12], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][12], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][12], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][12], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][12], 0);

            PTD_ServiceTune[playerid][13] = CreatePlayerTextDraw(playerid, 65.1996, 315.9375, "Мpoc¶aҐkЬ_Ѓa_c¶y£Ь†y"); // текст 3 слота
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][13], 0.3084, 1.5900);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][13], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][13], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][13], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][13], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][13], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][13], 0);

            PTD_ServiceTune[playerid][14] = CreatePlayerTextDraw(playerid, 65.1996, 360.2395, "PoЯЪҐeЫeЃЬe-cxoЫЪeЃЬe"); // текст 4 слота
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][14], 0.3084, 1.5900);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][14], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][14], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][14], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][14], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][14], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][14], 0);

            PTD_ServiceTune[playerid][15] = CreatePlayerTextDraw(playerid, 321.1996, 405.0394, "123"); // пусто
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][15], 0.4000, 1.6000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][15], 2);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][15], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][15], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][15], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][15], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][15], 0);

            PTD_ServiceTune[playerid][16] = CreatePlayerTextDraw(playerid, 367.3998, 381.4884, "flin_sto:flin_sto_plus"); // плюс
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][16], 55.0000, 64.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][16], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][16], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][16], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][16], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][16], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][16], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][16], true);

            PTD_ServiceTune[playerid][17] = CreatePlayerTextDraw(playerid, 218.9996, 381.4887, "flin_sto:flin_sto_minus"); // плюс
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][17], 55.0000, 64.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][17], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][17], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][17], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][17], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][17], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][17], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_ServiceTune[playerid][17], true);

            PTD_ServiceTune[playerid][18] = CreatePlayerTextDraw(playerid, 28.2000, 179.5066, "flin_sto:flin_sto_icon_balon"); // иконка слота 1 1
            PlayerTextDrawTextSize(playerid, PTD_ServiceTune[playerid][18], 26.0000, 32.0000);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][18], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][18], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][18], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][18], 4);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][18], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][18], 0);

            PTD_ServiceTune[playerid][19] = CreatePlayerTextDraw(playerid, 64.3992, 187.1289, "Л®Чop_†Ґe¶a"); // текст слота 1 1
            PlayerTextDrawLetterSize(playerid, PTD_ServiceTune[playerid][19], 0.3084, 1.5900);
            PlayerTextDrawAlignment(playerid, PTD_ServiceTune[playerid][19], 1);
            PlayerTextDrawColor(playerid, PTD_ServiceTune[playerid][19], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ServiceTune[playerid][19], 255);
            PlayerTextDrawFont(playerid, PTD_ServiceTune[playerid][19], 1);
            PlayerTextDrawSetProportional(playerid, PTD_ServiceTune[playerid][19], 1);
            PlayerTextDrawSetShadow(playerid, PTD_ServiceTune[playerid][19], 0);
        }
        case TD_ID_PIN_CODE:
        {
            if(p_temp[playerid][TextDrawPinCode]) return 1;
            PTD_PinCode[playerid][0] = CreatePlayerTextDraw(playerid, 153.599975, 211.000000, "0");
            PTD_PinCode[playerid][1] = CreatePlayerTextDraw(playerid, 190.599975, 211.000000, "4");
            PTD_PinCode[playerid][2] = CreatePlayerTextDraw(playerid, 227.599975, 211.000000, "1");
            PTD_PinCode[playerid][3] = CreatePlayerTextDraw(playerid, 264.599975, 211.000000, "8");
            PTD_PinCode[playerid][4] = CreatePlayerTextDraw(playerid, 301.599975, 211.000000, "3");
            PTD_PinCode[playerid][5] = CreatePlayerTextDraw(playerid, 338.599975, 211.000000, "6");
            PTD_PinCode[playerid][6] = CreatePlayerTextDraw(playerid, 375.599975, 211.000000, "7");
            PTD_PinCode[playerid][7] = CreatePlayerTextDraw(playerid, 412.599975, 211.000000, "2");
            PTD_PinCode[playerid][8] = CreatePlayerTextDraw(playerid, 449.599975, 211.000000, "5");
            PTD_PinCode[playerid][9] = CreatePlayerTextDraw(playerid, 486.599975, 211.000000, "9");

            PTD_PinCode[playerid][10] = CreatePlayerTextDraw(playerid, 319.399932, 186.684692, "");
            PlayerTextDrawLetterSize(playerid, PTD_PinCode[playerid][10], 0.346666, 2.400593);
            PlayerTextDrawTextSize(playerid, PTD_PinCode[playerid][10], 0.000000, 372.050048);
            PlayerTextDrawAlignment(playerid, PTD_PinCode[playerid][10], 2);
            PlayerTextDrawColor(playerid, PTD_PinCode[playerid][10], -1);
            PlayerTextDrawSetShadow(playerid, PTD_PinCode[playerid][10], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_PinCode[playerid][10], 255);
            PlayerTextDrawFont(playerid, PTD_PinCode[playerid][10], 2);
            PlayerTextDrawSetProportional(playerid, PTD_PinCode[playerid][10], 1);

            for(new i = 9; i != -1; i--)
            {
                PlayerTextDrawLetterSize(playerid, PTD_PinCode[playerid][i], 0.616330, 4.296294);
                PlayerTextDrawTextSize(playerid, PTD_PinCode[playerid][i], 0.000000, 31.000000);
                PlayerTextDrawAlignment(playerid, PTD_PinCode[playerid][i], 2);
                PlayerTextDrawColor(playerid, PTD_PinCode[playerid][i], -1);
                PlayerTextDrawSetShadow(playerid, PTD_PinCode[playerid][i], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_PinCode[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_PinCode[playerid][i], 2);
                PlayerTextDrawSetProportional(playerid, PTD_PinCode[playerid][i], 1);
            }
        }
        case TD_ID_LIST_PAGE:
        {
            if(p_temp[playerid][TextDrawListUse] == true) return 1;
            PTD_ListPage[playerid][0] = CreatePlayerTextDraw(playerid, 167.599975, 127.799926, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][0], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][0], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][0], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][0], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][0], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][0], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][0], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][1] = CreatePlayerTextDraw(playerid, 229.000000, 127.799926, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][1], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][1], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][1], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][1], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][1], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][1], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][1], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][2] = CreatePlayerTextDraw(playerid, 288.699981, 127.799926, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][2], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][2], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][2], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][2], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][2], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][2], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][2], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][3] = CreatePlayerTextDraw(playerid, 350.199951, 127.799926, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][3], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][3], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][3], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][3], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][3], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][3], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][3], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][4] = CreatePlayerTextDraw(playerid, 412.499908, 127.799926, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][4], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][4], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][4], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][4], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][4], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][4], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][4], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][5] = CreatePlayerTextDraw(playerid, 167.600036, 196.500030, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][5], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][5], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][5], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][5], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][5], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][5], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][5], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][6] = CreatePlayerTextDraw(playerid, 229.000000, 196.500030, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][6], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][6], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][6], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][6], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][6], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][6], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][6], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][7] = CreatePlayerTextDraw(playerid, 288.599975, 196.500030, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][7], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][7], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][7], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][7], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][7], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][7], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][7], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][8] = CreatePlayerTextDraw(playerid, 350.000000, 196.500030, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][8], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][8], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][8], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][8], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][8], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][8], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][8], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][9] = CreatePlayerTextDraw(playerid, 412.499908, 196.500030, "");
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][9], 60.000000, 54.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][9], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][9], 0);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][9], 5);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][9], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_ListPage[playerid][9], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_ListPage[playerid][9], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_ListPage[playerid][10] = CreatePlayerTextDraw(playerid, 197.900009, 175.277954, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][10], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][10], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][10], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][10], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][10], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][10], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][10], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][10], 1);

            PTD_ListPage[playerid][11] = CreatePlayerTextDraw(playerid, 259.000427, 175.277954, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][11], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][11], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][11], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][11], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][11], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][11], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][11], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][11], 1);

            PTD_ListPage[playerid][12] = CreatePlayerTextDraw(playerid, 319.101135, 175.277954, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][12], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][12], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][12], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][12], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][12], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][12], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][12], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][12], 1);

            PTD_ListPage[playerid][13] = CreatePlayerTextDraw(playerid, 381.000640, 175.277954, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][13], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][13], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][13], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][13], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][13], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][13], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][13], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][13], 1);

            PTD_ListPage[playerid][14] = CreatePlayerTextDraw(playerid, 443.000823, 175.277954, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][14], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][14], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][14], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][14], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][14], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][14], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][14], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][14], 1);

            PTD_ListPage[playerid][15] = CreatePlayerTextDraw(playerid, 197.900009, 244.177749, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][15], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][15], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][15], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][15], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][15], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][15], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][15], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][15], 1);

            PTD_ListPage[playerid][16] = CreatePlayerTextDraw(playerid, 259.000427, 244.177749, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][16], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][16], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][16], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][16], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][16], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][16], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][16], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][16], 1);

            PTD_ListPage[playerid][17] = CreatePlayerTextDraw(playerid, 319.101135, 244.177749, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][17], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][17], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][17], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][17], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][17], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][17], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][17], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][17], 1);

            PTD_ListPage[playerid][18] = CreatePlayerTextDraw(playerid, 381.000640, 244.177749, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][18], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][18], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][18], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][18], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][18], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][18], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][18], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][18], 1);

            PTD_ListPage[playerid][19] = CreatePlayerTextDraw(playerid, 443.000823, 244.177749, "1000000$");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][19], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][19], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][19], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][19], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][19], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][19], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][19], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][19], 1);

            PTD_ListPage[playerid][20] = CreatePlayerTextDraw(playerid, 317.000000, 279.399963, "CANCEL");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][20], 0.161329, 1.131257);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][20], 7.000000, 73.000000);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][20], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][20], -1);
            PlayerTextDrawUseBox(playerid, PTD_ListPage[playerid][20], 1);
            PlayerTextDrawBoxColor(playerid, PTD_ListPage[playerid][20], 0);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][20], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][20], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][20], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][20], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_ListPage[playerid][20], true);

            PTD_ListPage[playerid][21] = CreatePlayerTextDraw(playerid, 197.900009, 124.177764, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][21], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][21], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][21], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][21], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][21], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][21], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][21], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][21], 1);

            PTD_ListPage[playerid][22] = CreatePlayerTextDraw(playerid, 259.000427, 124.177764, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][22], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][22], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][22], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][22], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][22], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][22], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][22], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][22], 1);

            PTD_ListPage[playerid][23] = CreatePlayerTextDraw(playerid, 319.101135, 124.177764, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][23], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][23], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][23], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][23], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][23], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][23], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][23], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][23], 1);

            PTD_ListPage[playerid][24] = CreatePlayerTextDraw(playerid, 381.000640, 124.177764, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][24], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][24], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][24], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][24], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][24], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][24], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][24], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][24], 1);

            PTD_ListPage[playerid][25] = CreatePlayerTextDraw(playerid, 443.000823, 124.177764, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][25], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][25], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][25], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][25], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][25], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][25], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][25], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][25], 1);

            PTD_ListPage[playerid][26] = CreatePlayerTextDraw(playerid, 197.900009, 193.077560, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][26], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][26], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][26], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][26], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][26], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][26], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][26], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][26], 1);

            PTD_ListPage[playerid][27] = CreatePlayerTextDraw(playerid, 259.000427, 193.077560, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][27], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][27], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][27], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][27], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][27], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][27], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][27], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][27], 1);

            PTD_ListPage[playerid][28] = CreatePlayerTextDraw(playerid, 319.101135, 193.077560, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][28], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][28], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][28], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][28], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][28], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][28], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][28], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][28], 1);

            PTD_ListPage[playerid][29] = CreatePlayerTextDraw(playerid, 381.000640, 193.077560, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][29], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][29], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][29], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][29], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][29], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][29], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][29], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][29], 1);

            PTD_ListPage[playerid][30] = CreatePlayerTextDraw(playerid, 443.000823, 193.077560, "INFO");
            PlayerTextDrawLetterSize(playerid, PTD_ListPage[playerid][30], 0.1324995, 0.820443);
            PlayerTextDrawTextSize(playerid, PTD_ListPage[playerid][30], 0.000000, 52.899986);
            PlayerTextDrawAlignment(playerid, PTD_ListPage[playerid][30], 2);
            PlayerTextDrawColor(playerid, PTD_ListPage[playerid][30], -1);
            PlayerTextDrawSetShadow(playerid, PTD_ListPage[playerid][30], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_ListPage[playerid][30], 255);
            PlayerTextDrawFont(playerid, PTD_ListPage[playerid][30], 2);
            PlayerTextDrawSetProportional(playerid, PTD_ListPage[playerid][30], 1);

        }
        case TD_ID_CAPTURE:
        {
            if(p_temp[playerid][TextDrawCapture]) return 1;
            PTD_Capture[playerid][0] = CreatePlayerTextDraw(playerid, 41.533279, 210.585159, "");
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][0], 15.930001, 17.559997);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][0], 8388863);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][0], 0);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][0], 5);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][0], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_Capture[playerid][0], 1254);
            PlayerTextDrawSetPreviewRot(playerid, PTD_Capture[playerid][0], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_Capture[playerid][1] = CreatePlayerTextDraw(playerid, 74.933189, 210.585159, "");
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][1], 15.930001, 17.559997);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][1], -2147450625);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][1], 0);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][1], 5);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][1], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_Capture[playerid][1], 1254);
            PlayerTextDrawSetPreviewRot(playerid, PTD_Capture[playerid][1], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_Capture[playerid][2] = CreatePlayerTextDraw(playerid, 65.999992, 213.300018, "9:26");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][2], 0.158996, 1.131257);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][2], 0.000000, 86.999984);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][2], 2);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][2], -1);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][2], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][2], 1);

            PTD_Capture[playerid][3] = CreatePlayerTextDraw(playerid, 32.299995, 213.629531, "23");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][3], 0.249329, 1.006814);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][3], 0.000000, 13.599998);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][3], -1061109505);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][3], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][3], -16776961);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][3], 3);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][3], 1);

            PTD_Capture[playerid][4] = CreatePlayerTextDraw(playerid, 99.799797, 213.629531, "98");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][4], 0.249329, 1.006814);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][4], 0.000000, 13.599998);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][4], -1061109505);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][4], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][4], -16776961);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][4], 3);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][4], 1);

            PTD_Capture[playerid][5] = CreatePlayerTextDraw(playerid, 24.400180, 240.885437, "KILLS:_~s~53");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][5], 0.131999, 0.977777);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][5], 2000.000000, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][5], 1010580735);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][5], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][5], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][5], 1);

            PTD_Capture[playerid][6] = CreatePlayerTextDraw(playerid, 108.100585, 240.885437, "DEATH:_~s~20");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][6], 0.131999, 0.977777);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][6], 87.199981, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][6], 3);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][6], 1010580735);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][6], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][6], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][6], 1);

            PTD_Capture[playerid][7] = CreatePlayerTextDraw(playerid, 24.400180, 258.885559, "GIVE:_~s~17312");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][7], 0.131999, 0.977777);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][7], 2000.000000, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][7], 1010580735);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][7], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][7], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][7], 1);

            PTD_Capture[playerid][8] = CreatePlayerTextDraw(playerid, 108.100585, 259.185546, "TAKE:_~s~31758");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][8], 0.131999, 0.977777);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][8], 87.199981, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][8], 3);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][8], 1010580735);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][8], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][8], 255);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][8], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][8], 1);

            PTD_Capture[playerid][9] = CreatePlayerTextDraw(playerid, 65.966804, 278.171478, "KROUMBERG_KROUMBERG");
            PlayerTextDrawLetterSize(playerid, PTD_Capture[playerid][9], 0.140998, 0.923847);
            PlayerTextDrawTextSize(playerid, PTD_Capture[playerid][9], 0.000000, 87.249839);
            PlayerTextDrawAlignment(playerid, PTD_Capture[playerid][9], 2);
            PlayerTextDrawColor(playerid, PTD_Capture[playerid][9], 1010580735);
            PlayerTextDrawSetShadow(playerid, PTD_Capture[playerid][9], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Capture[playerid][9], 255);
            PlayerTextDrawFont(playerid, PTD_Capture[playerid][9], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Capture[playerid][9], 1);
        }
        case TD_ID_RECON_INFO:
        {
            PTD_Recon[playerid][0] = CreatePlayerTextDraw(playerid, 550.602172, 143.000000, "Stanley_Parker");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][0], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][0], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][0], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][0], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][0], 1);

            PTD_Recon[playerid][1] = CreatePlayerTextDraw(playerid, 550.602172, 152.900604, "3");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][1], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][1], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][1], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][1], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][1], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][1], 1);

            PTD_Recon[playerid][2] = CreatePlayerTextDraw(playerid, 550.602172, 162.901214, "57");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][2], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][2], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][2], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][2], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][2], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][2], 1);

            PTD_Recon[playerid][3] = CreatePlayerTextDraw(playerid, 550.602172, 172.601806, "100");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][3], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][3], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][3], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][3], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][3], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][3], 1);

            PTD_Recon[playerid][4] = CreatePlayerTextDraw(playerid, 550.602172, 182.702423, "100");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][4], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][4], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][4], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][4], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][4], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][4], 1);

            PTD_Recon[playerid][5] = CreatePlayerTextDraw(playerid, 550.602172, 192.503021, "Shotgun");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][5], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][5], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][5], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][5], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][5], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][5], 1);

            PTD_Recon[playerid][6] = CreatePlayerTextDraw(playerid, 550.602172, 202.403625, "300");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][6], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][6], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][6], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][6], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][6], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][6], 1);

            PTD_Recon[playerid][7] = CreatePlayerTextDraw(playerid, 550.602172, 212.104217, "200.200.200.200");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][7], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][7], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][7], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][7], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][7], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][7], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][7], 1);

            PTD_Recon[playerid][8] = CreatePlayerTextDraw(playerid, 550.602172, 222.504852, "0");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][8], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][8], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][8], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][8], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][8], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][8], 1);

            PTD_Recon[playerid][9] = CreatePlayerTextDraw(playerid, 550.602172, 232.305450, "10000000$");
            PlayerTextDrawLetterSize(playerid, PTD_Recon[playerid][9], 0.213666, 1.102221);
            PlayerTextDrawAlignment(playerid, PTD_Recon[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_Recon[playerid][9], -158909953);
            PlayerTextDrawSetShadow(playerid, PTD_Recon[playerid][9], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_Recon[playerid][9], 255);
            PlayerTextDrawFont(playerid, PTD_Recon[playerid][9], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Recon[playerid][9], 1);
        }
        case TD_ID_SPEEDOMETER:
        {
            //if(p_temp[playerid][TextDrawSpeedometr] == true) return 1;
            if(p_info[playerid][p_settings][INTERFACE] == 1)
            {
                PTD_NewSpeedometer[playerid][0] = CreatePlayerTextDraw(playerid, 260.000000, 427.000000, "flinspeed:flin_dashboardoff"); //+
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][0], 14.319993, 18.640005);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][0], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][0], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][0], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][0], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][0], 0);

                PTD_NewSpeedometer[playerid][1] = CreatePlayerTextDraw(playerid, 286.000000, 427.000000, "flinspeed:flin_limitoff"); // +
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][1], 14.319993, 18.640005);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][1], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][1], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][1], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][1], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][1], 0);

                PTD_NewSpeedometer[playerid][2] = CreatePlayerTextDraw(playerid, 310.000000, 427.000000, "flinspeed:flin_lighton"); //+
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][2], 14.319993, 18.640005);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][2], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][2], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][2], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][2], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][2], 0);

                PTD_NewSpeedometer[playerid][3] = CreatePlayerTextDraw(playerid, 334.000000, 427.000000, "flinspeed:flin_unlock"); //+
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][3], 14.319993, 18.640005);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][3], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][3], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][3], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][3], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][3], 0);

                PTD_NewSpeedometer[playerid][4] = CreatePlayerTextDraw(playerid, 361.000000, 427.000000, "flinspeed:flin_turbooff"); // +
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][4], 14.319993, 18.640005);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][4], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][4], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][4], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][4], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][4], 0);

                PTD_NewSpeedometer[playerid][5] = CreatePlayerTextDraw(playerid, 272.766540, 354.900177, "flinspeed:flin_s1");
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][5], 90.669960, 116.840034);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][5], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][5], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][5], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][5], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][5], 0);

                PTD_NewSpeedometer[playerid][6] = CreatePlayerTextDraw(playerid, 319.000000, 375.000000, "0");
                PlayerTextDrawLetterSize(playerid, PTD_NewSpeedometer[playerid][6], 0.787333, 3.574517);
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][6], 0.000000, 48.519989);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][6], 2);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][6], -1);
                PlayerTextDrawSetShadow(playerid, PTD_NewSpeedometer[playerid][6], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][6], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][6], 1);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][6], 1);

                PTD_NewSpeedometer[playerid][7] = CreatePlayerTextDraw(playerid, 254.000244, 415.800048, "100_L.");
                PlayerTextDrawLetterSize(playerid, PTD_NewSpeedometer[playerid][7], 0.268664, 1.102221);
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][7], 0.000000, 10.000000);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][7], 2);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][7], -1);
                PlayerTextDrawSetShadow(playerid, PTD_NewSpeedometer[playerid][7], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][7], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][7], 1);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][7], 1);

                PTD_NewSpeedometer[playerid][8] = CreatePlayerTextDraw(playerid, 381.899688, 415.800048, "100%");
                PlayerTextDrawLetterSize(playerid, PTD_NewSpeedometer[playerid][8], 0.268664, 1.102221);
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][8], 0.000000, 10.000000);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][8], 2);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][8], -1);
                PlayerTextDrawSetShadow(playerid, PTD_NewSpeedometer[playerid][8], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][8], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][8], 1);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][8], 1);

                PTD_NewSpeedometer[playerid][9] = CreatePlayerTextDraw(playerid, 266.733123, 347.907409, "flinspeed:flin_f1");
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][9], 102.150024, 131.000000);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][9], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][9], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][9], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][9], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][9], 0);

                PTD_NewSpeedometer[playerid][10] = CreatePlayerTextDraw(playerid, 267.333160, 347.907409, "flinspeed:flin_h1");
                PlayerTextDrawTextSize(playerid, PTD_NewSpeedometer[playerid][10], 102.150024, 131.000000);
                PlayerTextDrawAlignment(playerid, PTD_NewSpeedometer[playerid][10], 1);
                PlayerTextDrawColor(playerid, PTD_NewSpeedometer[playerid][10], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSpeedometer[playerid][10], 255);
                PlayerTextDrawFont(playerid, PTD_NewSpeedometer[playerid][10], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSpeedometer[playerid][10], 0);
            }
            else
            {
                PTD_SpeedometerInfo[playerid][0] = CreatePlayerTextDraw(playerid, 320.000152, 377.081787, "Infernus");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][0], 0.273665, 1.317924);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][0], 2);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][0], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][0], 0);
                PlayerTextDrawSetOutline(playerid, PTD_SpeedometerInfo[playerid][0], 1);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][0], 521869567);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][0], 1);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][0], 1);

                PTD_SpeedometerInfo[playerid][1] = CreatePlayerTextDraw(playerid, 319.733581, 392.429779, "0");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][1], 0.253331, 1.749330);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][1], 2);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][1], -5963521);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][1], 0);
                PlayerTextDrawSetOutline(playerid, PTD_SpeedometerInfo[playerid][1], 1);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][1], -5963763);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][1], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][1], 1);

                PTD_SpeedometerInfo[playerid][2] = CreatePlayerTextDraw(playerid, 361.833404, 395.048309, "D");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][2], -0.307332, 1.725630);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][2], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][2], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][2], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][2], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][2], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][2], 1);

                PTD_SpeedometerInfo[playerid][3] = CreatePlayerTextDraw(playerid, 361.633422, 393.803833, "=");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][3], 0.236662, 1.787852);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][3], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][3], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][3], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][3], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][3], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][3], 1);

                PTD_SpeedometerInfo[playerid][4] = CreatePlayerTextDraw(playerid, 368.366668, 400.189392, "-");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][4], -0.615631, 1.341462);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][4], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][4], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][4], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][4], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][4], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][4], 1);

                PTD_SpeedometerInfo[playerid][5] = CreatePlayerTextDraw(playerid, 380.800659, 398.233154, "0");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][5], 0.384665, 1.337406);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][5], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][5], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][5], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][5], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][5], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][5], 1);

                PTD_SpeedometerInfo[playerid][6] = CreatePlayerTextDraw(playerid, 382.000732, 401.681274, "U");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][6], 0.281331, -0.371627);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][6], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][6], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][6], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][6], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][6], 1);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][6], 1);

                PTD_SpeedometerInfo[playerid][7] = CreatePlayerTextDraw(playerid, 251.999954, 393.933532, "0");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][7], 0.461665, 1.966222);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][7], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][7], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][7], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][7], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][7], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][7], 1);

                PTD_SpeedometerInfo[playerid][8] = CreatePlayerTextDraw(playerid, 256.833343, 401.685363, "/");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][8], 0.163000, 0.438517);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][8], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][8], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][8], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][8], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][8], 1);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][8], 1);

                PTD_SpeedometerInfo[playerid][9] = CreatePlayerTextDraw(playerid, 278.299926, 398.337280, "U");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][9], 0.266000, 1.479701);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][9], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][9], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][9], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][9], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][9], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][9], 1);

                PTD_SpeedometerInfo[playerid][10] = CreatePlayerTextDraw(playerid, 276.333374, 409.766845, "J");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][10], 0.230599, -1.481734);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][10], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][10], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][10], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][10], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][10], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][10], 1);

                PTD_SpeedometerInfo[playerid][11] = CreatePlayerTextDraw(playerid, 287.234039, 409.766845, "J");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][11], -0.237397, -1.481734);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][11], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][11], -1);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][11], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][11], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][11], 2);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][11], 1);

                PTD_SpeedometerInfo[playerid][12] = CreatePlayerTextDraw(playerid, 317.166900, 433.522460, "(");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][12], 0.382299, 0.844964);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][12], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][12], -5963521);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][12], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][12], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][12], 1);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][12], 1);

                PTD_SpeedometerInfo[playerid][13] = CreatePlayerTextDraw(playerid, 319.266479, 430.892639, "o");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][13], 0.212999, 1.061926);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][13], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][13], -2147483393);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][13], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][13], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][13], 0);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][13], 1);

                PTD_SpeedometerInfo[playerid][14] = CreatePlayerTextDraw(playerid, 318.566864, 432.207702, ")");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][14], 0.333299, 0.898890);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][14], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][14], -9174785);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][14], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][14], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][14], 1);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][14], 1);

                PTD_SpeedometerInfo[playerid][15] = CreatePlayerTextDraw(playerid, 392.399902, 424.970275, "123.3");
                PlayerTextDrawLetterSize(playerid, PTD_SpeedometerInfo[playerid][15], 0.200332, 1.002665);
                PlayerTextDrawAlignment(playerid, PTD_SpeedometerInfo[playerid][15], 1);
                PlayerTextDrawColor(playerid, PTD_SpeedometerInfo[playerid][15], -5701377);
                PlayerTextDrawSetShadow(playerid, PTD_SpeedometerInfo[playerid][15], 0);
                PlayerTextDrawBackgroundColor(playerid, PTD_SpeedometerInfo[playerid][15], 255);
                PlayerTextDrawFont(playerid, PTD_SpeedometerInfo[playerid][15], 1);
                PlayerTextDrawSetProportional(playerid, PTD_SpeedometerInfo[playerid][15], 1);
            }
        }
        case TD_ID_SALARY:
        {
            if(p_info[playerid][p_settings][INTERFACE])
            {
                PTD_NewSalary[playerid][0] = CreatePlayerTextDraw(playerid, 545.3994, 165.5509, "flin_txd:flin_jobinfo"); // прогресс работы
                PlayerTextDrawTextSize(playerid, PTD_NewSalary[playerid][0], 85.0000, 107.0000);
                PlayerTextDrawAlignment(playerid, PTD_NewSalary[playerid][0], 1);
                PlayerTextDrawColor(playerid, PTD_NewSalary[playerid][0], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSalary[playerid][0], 255);
                PlayerTextDrawFont(playerid, PTD_NewSalary[playerid][0], 4);
                PlayerTextDrawSetProportional(playerid, PTD_NewSalary[playerid][0], 0);
                PlayerTextDrawSetShadow(playerid, PTD_NewSalary[playerid][0], 0);

                PTD_NewSalary[playerid][1] = CreatePlayerTextDraw(playerid, 607.6008, 218.3730, "0$"); // кол-во заработано
                PlayerTextDrawLetterSize(playerid, PTD_NewSalary[playerid][1], 0.1835, 1.1813);
                PlayerTextDrawAlignment(playerid, PTD_NewSalary[playerid][1], 2);
                PlayerTextDrawColor(playerid, PTD_NewSalary[playerid][1], -5963521);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSalary[playerid][1], 255);
                PlayerTextDrawFont(playerid, PTD_NewSalary[playerid][1], 2);
                PlayerTextDrawSetProportional(playerid, PTD_NewSalary[playerid][1], 1);
                PlayerTextDrawSetShadow(playerid, PTD_NewSalary[playerid][1], 0);

                PTD_NewSalary[playerid][2] = CreatePlayerTextDraw(playerid, 569.2012, 219.2730, "0"); // кол-во выполнено
                PlayerTextDrawLetterSize(playerid, PTD_NewSalary[playerid][2], 0.1835, 1.1813);
                PlayerTextDrawAlignment(playerid, PTD_NewSalary[playerid][2], 2);
                PlayerTextDrawColor(playerid, PTD_NewSalary[playerid][2], -1);
                PlayerTextDrawBackgroundColor(playerid, PTD_NewSalary[playerid][2], 255);
                PlayerTextDrawFont(playerid, PTD_NewSalary[playerid][2], 2);
                PlayerTextDrawSetProportional(playerid, PTD_NewSalary[playerid][2], 1);
                PlayerTextDrawSetShadow(playerid, PTD_NewSalary[playerid][2], 0);
            }
            else
            {
                PTD_Salary[playerid][0] = CreatePlayerTextDraw(playerid, 636.823425, 203.916671, "usebox");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][0], 0.000000, 4.104028);
                PlayerTextDrawTextSize(playerid, PTD_Salary[playerid][0], 533.529296, 0.000000);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][0], 1);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][0], 0);
                PlayerTextDrawUseBox(playerid, PTD_Salary[playerid][0], true);
                PlayerTextDrawBoxColor(playerid, PTD_Salary[playerid][0], 102);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][0], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][0], 0);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][0], 0);

                PTD_Salary[playerid][1] = CreatePlayerTextDraw(playerid, 636.823486, 184.666702, "usebox");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][1], 0.000000, 1.191830);
                PlayerTextDrawTextSize(playerid, PTD_Salary[playerid][1], 533.529479, 0.000000);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][1], 1);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][1], 0);
                PlayerTextDrawUseBox(playerid, PTD_Salary[playerid][1], true);
                PlayerTextDrawBoxColor(playerid, PTD_Salary[playerid][1], 102);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][1], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][1], 0);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][1], 0);

                PTD_Salary[playerid][2] = CreatePlayerTextDraw(playerid, 585.882324, 182.000030, "Work Info");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][2], 0.325764, 1.605833);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][2], 2);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][2], -5963521);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][2], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][2], 1);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][2], 2);
                PlayerTextDrawSetProportional(playerid, PTD_Salary[playerid][2], 1);

                PTD_Salary[playerid][3] = CreatePlayerTextDraw(playerid, 633.058837, 208.000015, "usebox");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][3], 0.000000, 1.109258);
                PlayerTextDrawTextSize(playerid, PTD_Salary[playerid][3], 537.294128, 0.000000);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][3], 1);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][3], 0);
                PlayerTextDrawUseBox(playerid, PTD_Salary[playerid][3], true);
                PlayerTextDrawBoxColor(playerid, PTD_Salary[playerid][3], 102);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][3], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][3], 0);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][3], 0);

                PTD_Salary[playerid][4] = CreatePlayerTextDraw(playerid, 633.117980, 226.499969, "usebox");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][4], 0.000000, 1.109258);
                PlayerTextDrawTextSize(playerid, PTD_Salary[playerid][4], 537.294433, 0.000000);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][4], 1);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][4], 0);
                PlayerTextDrawUseBox(playerid, PTD_Salary[playerid][4], true);
                PlayerTextDrawBoxColor(playerid, PTD_Salary[playerid][4], 102);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][4], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][4], 0);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][4], 0);

                PTD_Salary[playerid][5] = CreatePlayerTextDraw(playerid, 585.881835, 205.333389, "Progress: 10");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][5], 0.259411, 1.512498);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][5], 2);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][5], -1);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][5], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][5], 1);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][5], 2);
                PlayerTextDrawSetProportional(playerid, PTD_Salary[playerid][5], 1);

                PTD_Salary[playerid][6] = CreatePlayerTextDraw(playerid, 584.999511, 223.833358, "SALARY: 500");
                PlayerTextDrawLetterSize(playerid, PTD_Salary[playerid][6], 0.270705, 1.430832);
                PlayerTextDrawAlignment(playerid, PTD_Salary[playerid][6], 2);
                PlayerTextDrawColor(playerid, PTD_Salary[playerid][6], -1);
                PlayerTextDrawSetShadow(playerid, PTD_Salary[playerid][6], 0);
                PlayerTextDrawSetOutline(playerid, PTD_Salary[playerid][6], 1);
                PlayerTextDrawFont(playerid, PTD_Salary[playerid][6], 2);
                PlayerTextDrawSetProportional(playerid, PTD_Salary[playerid][6], 1);
            }
        }
        case TD_ID_DICE:
        {
            PTD_Dice[playerid][0] = CreatePlayerTextDraw(playerid, 638.705627, 156.666671, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][0], 0.000000, 18.603046);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][0], 541.058715, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][0], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][0], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][0], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][0], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][0], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][0], 0);

            PTD_Dice[playerid][1] = CreatePlayerTextDraw(playerid, 634.941162, 160.749984, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][1], 0.000000, 1.174076);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][1], 544.823547, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][1], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][1], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][1], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][1], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][1], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][1], 0);

            PTD_Dice[playerid][2] = CreatePlayerTextDraw(playerid, 590.117492, 158.666610, "TABLE 1");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][2], 0.311646, 1.372499);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][2], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][2], 2);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][2], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][2], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][2], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][2], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][2], 1);

            PTD_Dice[playerid][3] = CreatePlayerTextDraw(playerid, 634.941162, 180.000000, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][3], 0.000000, 4.538235);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][3], 544.823547, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][3], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][3], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][3], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][3], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][3], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][3], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][3], 0);

            PTD_Dice[playerid][4] = CreatePlayerTextDraw(playerid, 550.235656, 179.916595, "Enrique_Black~n~Enrique_Black~n~Enrique_Black~n~Enrique_Black~n~Enrique_Black");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][4], 0.156823, 0.882500);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][4], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][4], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][4], -1);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][4], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][4], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][4], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][4], 1);

            PTD_Dice[playerid][5] = CreatePlayerTextDraw(playerid, 629.353332, 179.166702, "--_~n~--_~n~--_~n~--_~n~--");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][5], 0.212352, 0.923333);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][5], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][5], 3);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][5], -1);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][5], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][5], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][5], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][5], 1);

            PTD_Dice[playerid][6] = CreatePlayerTextDraw(playerid, 634.941223, 229.583404, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][6], 0.000000, 2.829955);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][6], 544.823547, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][6], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][6], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][6], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][6], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][6], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][6], 0);

            PTD_Dice[playerid][7] = CreatePlayerTextDraw(playerid, 590.117614, 229.250030, "Bet: 1000~n~Bank: 5000~n~Money: 10000000");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][7], 0.225058, 0.888333);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][7], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][7], 2);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][7], -1);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][7], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][7], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][7], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][7], 1);

            PTD_Dice[playerid][8] = CreatePlayerTextDraw(playerid, 634.941162, 263.416687, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][8], 0.000000, 6.306977);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][8], 544.823547, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][8], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][8], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][8], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][8], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][8], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][8], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][8], 0);

            PTD_Dice[playerid][9] = CreatePlayerTextDraw(playerid, 631.647094, 266.916687, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][9], 0.000000, 1.221128);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][9], 548.117675, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][9], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][9], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][9], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][9], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][9], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][9], 0);

            PTD_Dice[playerid][10] = CreatePlayerTextDraw(playerid, 631.706176, 285.999969, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][10], 0.000000, 1.221128);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][10], 548.117919, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][10], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][10], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][10], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][10], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][10], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][10], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][10], 0);

            PTD_Dice[playerid][11] = CreatePlayerTextDraw(playerid, 631.765014, 305.083099, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][11], 0.000000, 1.268187);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][11], 548.117919, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][11], 1);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][11], 0);
            PlayerTextDrawUseBox(playerid, PTD_Dice[playerid][11], true);
            PlayerTextDrawBoxColor(playerid, PTD_Dice[playerid][11], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][11], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][11], 0);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][11], 0);

            PTD_Dice[playerid][12] = CreatePlayerTextDraw(playerid, 590.587951, 264.250000, "Set_Bet");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][12], 0.449999, 1.600000);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][12], 15.00000, 80.00000);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][12], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][12], 2);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][12], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][12], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][12], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][12], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][12], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Dice[playerid][12], true);

            PTD_Dice[playerid][13] = CreatePlayerTextDraw(playerid, 589.705627, 283.333435, "Dice");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][13], 0.449999, 1.600000);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][13], 15.00000, 80.00000);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][13], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][13], 2);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][13], -5963521);//-5963521
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][13], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][13], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][13], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][13], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Dice[playerid][13], true);

            PTD_Dice[playerid][14] = CreatePlayerTextDraw(playerid, 589.764465, 303.000213, "Exit");
            PlayerTextDrawLetterSize(playerid, PTD_Dice[playerid][14], 0.449999, 1.600000);
            PlayerTextDrawTextSize(playerid, PTD_Dice[playerid][14], 15.00000, 80.00000);
            PlayerTextDrawBackgroundColor(playerid, PTD_Dice[playerid][14], 0x00000000);
            PlayerTextDrawAlignment(playerid, PTD_Dice[playerid][14], 2);
            PlayerTextDrawColor(playerid, PTD_Dice[playerid][14], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_Dice[playerid][14], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Dice[playerid][14], 1);
            PlayerTextDrawFont(playerid, PTD_Dice[playerid][14], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Dice[playerid][14], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Dice[playerid][14], true);
        }
        case TD_ID_SHOP:
        {
            PTD_Shop[playerid][0] = CreatePlayerTextDraw(playerid, 399.647094, 339.249969, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][0], 0.000000, 6.215463);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][0], 241.294281, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][0], 0);
            PlayerTextDrawUseBox(playerid, PTD_Shop[playerid][0], true);
            PlayerTextDrawBoxColor(playerid, PTD_Shop[playerid][0], 48);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][0], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][0], 0);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][0], 0);

            PTD_Shop[playerid][1] = CreatePlayerTextDraw(playerid, 278.705841, 361.999969, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][1], 0.000000, 3.260564);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][1], 244.588211, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][1], 1);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][1], 0);
            PlayerTextDrawUseBox(playerid, PTD_Shop[playerid][1], true);
            PlayerTextDrawBoxColor(playerid, PTD_Shop[playerid][1], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][1], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][1], 0);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][1], 0);

            PTD_Shop[playerid][2] = CreatePlayerTextDraw(playerid, 396.411804, 361.833374, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][2], 0.000000, 3.260562);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][2], 361.764739, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][2], 1);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][2], 0);
            PlayerTextDrawUseBox(playerid, PTD_Shop[playerid][2], true);
            PlayerTextDrawBoxColor(playerid, PTD_Shop[playerid][2], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][2], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][2], 0);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][2], 0);

            PTD_Shop[playerid][3] = CreatePlayerTextDraw(playerid, 261.646881, 358.750030, "<<");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][3], 0.471646, 3.822499);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][3], 30.000000, 30.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][3], 2);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][3], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][3], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][3], 1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Shop[playerid][3], 51);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][3], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Shop[playerid][3], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Shop[playerid][3], true);

            PTD_Shop[playerid][4] = CreatePlayerTextDraw(playerid, 381.235046, 358.600006, ">>");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][4], 0.471646, 3.822499);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][4], 30.000000, 30.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][4], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][4], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][4], 1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Shop[playerid][4], 51);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][4], 3);
            PlayerTextDrawSetProportional(playerid, PTD_Shop[playerid][4], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Shop[playerid][4], true);

            PTD_Shop[playerid][5] = CreatePlayerTextDraw(playerid, 362.941162, 362.100067, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][5], 0.000000, 1.156314);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][5], 277.529388, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][5], 1);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][5], 0);
            PlayerTextDrawUseBox(playerid, PTD_Shop[playerid][5], true);
            PlayerTextDrawBoxColor(playerid, PTD_Shop[playerid][5], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][5], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][5], 0);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][5], 0);

            PTD_Shop[playerid][6] = CreatePlayerTextDraw(playerid, 363.000000, 380.500000, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][6], 0.000000, 1.156314);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][6], 277.529388, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][6], 1);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][6], 0);
            PlayerTextDrawUseBox(playerid, PTD_Shop[playerid][6], true);
            PlayerTextDrawBoxColor(playerid, PTD_Shop[playerid][6], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][6], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][6], 0);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][6], 0);

            PTD_Shop[playerid][7] = CreatePlayerTextDraw(playerid, 320.899993, 359.916717, "SELECT");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][7], 0.478704, 1.459998);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][7], 10.000000, 80.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][7], 2);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][7], -1);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][7], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][7], 1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Shop[playerid][7], 51);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][7], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Shop[playerid][7], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Shop[playerid][7], true);

            PTD_Shop[playerid][8] = CreatePlayerTextDraw(playerid, 320.899993, 378.416748, "CANCEL");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][8], 0.478704, 1.459998);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][8], 10.000000, 80.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][8], 2);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][8], -1);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][8], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][8], 1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Shop[playerid][8], 51);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][8], 1);
            PlayerTextDrawSetProportional(playerid, PTD_Shop[playerid][8], 1);
            PlayerTextDrawSetSelectable(playerid, PTD_Shop[playerid][8], true);

            PTD_Shop[playerid][9] = CreatePlayerTextDraw(playerid, 396.941314, 342.999969, "usebox");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][9], 0.000000, 1.203372);
            PlayerTextDrawTextSize(playerid, PTD_Shop[playerid][9], 244.588516, 0.000000);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][9], 1);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][9], 0);
            PlayerTextDrawUseBox(playerid, PTD_Shop[playerid][9], true);
            PlayerTextDrawBoxColor(playerid, PTD_Shop[playerid][9], 102);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][9], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][9], 0);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][9], 0);

            PTD_Shop[playerid][10] = CreatePlayerTextDraw(playerid, 321.411712, 340.083404, "50000$");
            PlayerTextDrawLetterSize(playerid, PTD_Shop[playerid][10], 0.380823, 1.564999);
            PlayerTextDrawAlignment(playerid, PTD_Shop[playerid][10], 2);
            PlayerTextDrawColor(playerid, PTD_Shop[playerid][10], -5963521);
            PlayerTextDrawSetShadow(playerid, PTD_Shop[playerid][10], 0);
            PlayerTextDrawSetOutline(playerid, PTD_Shop[playerid][10], 1);
            PlayerTextDrawBackgroundColor(playerid, PTD_Shop[playerid][10], 51);
            PlayerTextDrawFont(playerid, PTD_Shop[playerid][10], 2);
            PlayerTextDrawSetProportional(playerid, PTD_Shop[playerid][10], 1);
        }
    }
    return 1;
}

CreateTextDrawEquipment(playerid, type_id)
{
    new Float:header = 19.0,
        Float:item_width = 36.0, Float:item_height = 43.0, Float:distance_between_items = 1.0, Float:borders_inv = 2.0, items_inv_rows = 4, items_inv_columns = 5,
        Float:bottom_height = 34.0, Float:inventory_width = 188.0, Float:button_height = 28.0, Float:button_width = 39.0,
        Float:inventory_height = header+(borders_inv*2)+(item_height*items_inv_rows)+(distance_between_items*(items_inv_rows-1))+3+bottom_height;

    switch(type_id)
    {
        case TD_ID_EQUIPMENT_RIGHT:
        {
            if(p_temp[playerid][TextDrawInventory] || p_temp[playerid][TextDrawTrade] || p_temp[playerid][TextDrawMarket]) return 1;
            new Float:start_x = 640.0/2-(inventory_width*2+3)/2+inventory_width+3, Float:start_y = 448.0/2-inventory_height/2+45;
            PTD_EquipmentRight[playerid][0] = CreatePlayerTextDraw(playerid, start_x, start_y, "LD_SPAC:white"); // «адний фон
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][0], inventory_width, inventory_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][0], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][0], 0);

            for(new i = 1; i < 4; i++)
            {
                PTD_EquipmentRight[playerid][i] = CreatePlayerTextDraw(playerid, start_x, start_y+(i-1)*6.0, "LD_SPAC:white"); // шапка
                PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][i], inventory_width, 6.0*(4-i));
                PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][i], 1);
                if(i == 1) PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][i], -22740481);
                else if(i == 2) PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][i], -5500673);
                else PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][i], -5103105);
                PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][i], 0);
            }

            PTD_EquipmentRight[playerid][4] = CreatePlayerTextDraw(playerid, start_x+94.0, start_y+4.0, "INVENTORY");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][4], 0.215000, 1.000000);
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][4], 0.000000, 184.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][4], 1295122687);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][4], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][4], -1065484138);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][4], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][4], 1);

            new count;
            for (new i; i < items_inv_rows; i++){
                for (new j; j < items_inv_columns; j++){
                    PTD_EquipmentRight[playerid][5+count] = CreatePlayerTextDraw(playerid,
                    start_x+borders_inv+j*(item_width+distance_between_items),
                    start_y+header+borders_inv+i*(item_height+distance_between_items), "");
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][5+count], item_width, item_height);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][5+count], 1);
                    PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][5+count], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][5+count], 454761471);
                    PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][5+count], 5);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][5+count], 0);
                    PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][5+count], true);
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentRight[playerid][5+count], 0);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentRight[playerid][5+count], 0.000000, 0.000000, 0.000000, 50.000000);

                    PTD_EquipmentRight[playerid][25+count] = CreatePlayerTextDraw(playerid,
                    start_x+borders_inv+(item_width-1)+j*((item_width)+distance_between_items),
                    start_y+header+borders_inv+(item_height-10)+i*((item_height)+distance_between_items), "_");
                    PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][25+count], 0.210000, 0.900000);
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][25+count], 454.000000, 0.000000);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][25+count], 3);
                    PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][25+count], -56);
                    PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][25+count], 0);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][25+count], 255);
                    PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][25+count], 1);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][25+count], 1);
                    count++;
                }
            }

            PTD_EquipmentRight[playerid][45] = CreatePlayerTextDraw(playerid, start_x,
                start_y+header+(borders_inv*2)+(item_height*items_inv_rows)+(distance_between_items*(items_inv_rows-1)), "LD_SPAC:white"); // лини€ котора€ отдел€ет инвентарь от кнопок ниже
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][45], inventory_width, 3.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][45], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][45], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][45], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][45], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][45], 0);

            PTD_EquipmentRight[playerid][46] = CreatePlayerTextDraw(playerid, start_x+borders_inv+54,
                start_y+inventory_height-borders_inv-30, "LD_SPAC:white"); // фон стрелок
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][46], 76.000000, 30.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][46], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][46], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][46], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][46], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][46], 0);

            PTD_EquipmentRight[playerid][47] = CreatePlayerTextDraw(playerid, start_x+borders_inv+54+distance_between_items,
                start_y+inventory_height-borders_inv-30+distance_between_items, "LD_SPAC:white"); // стрелка лево
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][47], 23.000000, 28.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][47], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][47], 505290495);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][47], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][47], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][47], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][47], true);

            PTD_EquipmentRight[playerid][48] = CreatePlayerTextDraw(playerid, start_x+borders_inv+54+distance_between_items+23+28,
                start_y+inventory_height-borders_inv-30+distance_between_items, "LD_SPAC:white"); // стрелка право
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][48], 23.000000, 28.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][48], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][48], 505290495);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][48], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][48], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][48], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][48], true);

            PTD_EquipmentRight[playerid][49] = CreatePlayerTextDraw(playerid, start_x+borders_inv+54+distance_between_items+12,
                start_y+inventory_height-borders_inv-30+distance_between_items+8, "<<");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][49], 0.200000, 1.327000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][49], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][49], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][49], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][49], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][49], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][49], 1);

            PTD_EquipmentRight[playerid][50] = CreatePlayerTextDraw(playerid, start_x+borders_inv+54+distance_between_items+23+28+12,
                start_y+inventory_height-borders_inv-30+distance_between_items+8, ">>");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][50], 0.200000, 1.327000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][50], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][50], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][50], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][50], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][50], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][50], 1);

            PTD_EquipmentRight[playerid][51] = CreatePlayerTextDraw(playerid, start_x+borders_inv+54+distance_between_items+12+26,
                start_y+inventory_height-borders_inv-30+distance_between_items+6, "1");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][51], 0.260000, 1.620000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][51], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][51], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][51], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][51], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][51], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][51], 1);

            PTD_EquipmentRight[playerid][52] = CreatePlayerTextDraw(playerid, start_x+borders_inv,
                start_y+inventory_height-borders_inv-button_height-distance_between_items, "LD_SPAC:white"); // кнопка setting
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][52], button_width+8, button_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][52], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][52], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][52], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][52], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][52], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][52], true);

            PTD_EquipmentRight[playerid][53] = CreatePlayerTextDraw(playerid, start_x+21+4,
                start_y+inventory_height-borders_inv-button_height-distance_between_items+7.5, "SETTING");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][53], 1.5*0.200000, 1.5*0.930000);
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][53], 0.000000, 37.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][53], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][53], -56);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][53], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][53], -22740481);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][53], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][53], 1);

            PTD_EquipmentRight[playerid][54] = CreatePlayerTextDraw(playerid, start_x+inventory_width-borders_inv-button_width,
            start_y+inventory_height-borders_inv-button_height-distance_between_items, "LD_SPAC:white"); // кнопка close
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][54], button_width, button_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][54], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][54], 0xd55444FF);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][54], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][54], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][54], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentRight[playerid][54], true);

            PTD_EquipmentRight[playerid][55] = CreatePlayerTextDraw(playerid, start_x+inventory_width-borders_inv-button_width+19,
            start_y+inventory_height-borders_inv-button_height-distance_between_items+7.5, "CLOSE");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentRight[playerid][55], 1.5*0.200000, 1.5*0.930000);
            PlayerTextDrawTextSize(playerid, PTD_EquipmentRight[playerid][55], 0.000000, 37.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentRight[playerid][55], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentRight[playerid][55], -56);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentRight[playerid][55], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentRight[playerid][55], -1065484138);
            PlayerTextDrawFont(playerid, PTD_EquipmentRight[playerid][55], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentRight[playerid][55], 1);
        }
        case TD_ID_EQUIPMENT_LEFT:
        {
            new
                Float:start_x = 640.0/2-(inventory_width*2+3)/2+inventory_width+3, Float:start_y = 448.0/2-inventory_height/2+45,
                Float:start_x_left = start_x - inventory_width - 3;

            PTD_EquipmentLeft[playerid][0] = CreatePlayerTextDraw(playerid, start_x_left, start_y, "LD_SPAC:white"); // «адний фон
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][0], inventory_width, inventory_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][0], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][0], 0);

            for(new i = 1; i < 4; i++)
            {
                PTD_EquipmentLeft[playerid][i] = CreatePlayerTextDraw(playerid, start_x_left, start_y+(i-1)*6.0, "LD_SPAC:white"); // шапка
                PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][i], inventory_width, 6.0*(4-i));
                PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][i], 1);
                if(i == 1) PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][i], -22740481);
                else if(i == 2) PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][i], -5500673);
                else PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][i], -5103105);
                PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][i], 0);
            }

            PTD_EquipmentLeft[playerid][4] = CreatePlayerTextDraw(playerid, start_x_left+94.0, start_y+4.0, "INVENTORY");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentLeft[playerid][4], 0.215000, 1.000000);
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][4], 0.000000, 184.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][4], 1295122687);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentLeft[playerid][4], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][4], -1065484138);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][4], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][4], 1);

            new count = 0;
            for (new i; i < items_inv_rows; i++){
                for (new j; j < items_inv_columns; j++){
                    PTD_EquipmentLeft[playerid][5+count] = CreatePlayerTextDraw(playerid,
                        start_x_left+borders_inv+j*(item_width+distance_between_items),
                        start_y+header+borders_inv+i*(item_height+distance_between_items), ""); // 1 р€д 1 €чейка
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][5+count], item_width, item_height);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][5+count], 1);
                    PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][5+count], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][5+count], 454761471);
                    PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][5+count], 5);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][5+count], 0);
                    PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][5+count], true);
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentLeft[playerid][5+count], 0);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentLeft[playerid][5+count], 0.000000, 0.000000, 0.000000, 50.000000);

                    PTD_EquipmentLeft[playerid][25+count] = CreatePlayerTextDraw(playerid,
                    start_x_left+borders_inv+(item_width-1)+j*((item_width)+distance_between_items),
                    start_y+header+borders_inv+(item_height-10)+i*((item_height)+distance_between_items), "_"); // 1 р€д 1 €чейка
                    PlayerTextDrawLetterSize(playerid, PTD_EquipmentLeft[playerid][25+count], 0.210000, 0.900000);
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][25+count], 454.000000, 0.000000);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][25+count], 3);
                    PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][25+count], -56);
                    PlayerTextDrawSetShadow(playerid, PTD_EquipmentLeft[playerid][25+count], 0);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][25+count], 255);
                    PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][25+count], 1);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][25+count], 1);
                    count++;
                }
            }

            PTD_EquipmentLeft[playerid][45] = CreatePlayerTextDraw(playerid, start_x_left,
                start_y+header+(borders_inv*2)+(item_height*items_inv_rows)+(distance_between_items*(items_inv_rows-1)), "LD_SPAC:white"); // лини€ котора€ отдел€ет инвентарь от кнопок ниже
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][45], inventory_width, 3.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][45], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][45], 454761471);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][45], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][45], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][45], 0);

            PTD_EquipmentLeft[playerid][46] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv+54,
                start_y+inventory_height-borders_inv-30, "LD_SPAC:white"); // фон стрелок
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][46], 76.000000, 30.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][46], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][46], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][46], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][46], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][46], 0);

            PTD_EquipmentLeft[playerid][47] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv+54+distance_between_items,
                start_y+inventory_height-borders_inv-30+distance_between_items, "LD_SPAC:white"); // стрелка лево
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][47], 23.000000, 28.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][47], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][47], 505290495);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][47], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][47], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][47], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][47], true);

            PTD_EquipmentLeft[playerid][48] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv+54+distance_between_items+23+28,
                start_y+inventory_height-borders_inv-30+distance_between_items, "LD_SPAC:white"); // стрелка право
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][48], 23.000000, 28.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][48], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][48], 505290495);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][48], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][48], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][48], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][48], true);

            PTD_EquipmentLeft[playerid][49] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv+54+distance_between_items+12,
                start_y+inventory_height-borders_inv-30+distance_between_items+8, "<<");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentLeft[playerid][49], 0.200000, 1.327000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][49], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][49], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentLeft[playerid][49], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][49], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][49], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][49], 1);

            PTD_EquipmentLeft[playerid][50] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv+54+distance_between_items+23+28+12,
                start_y+inventory_height-borders_inv-30+distance_between_items+8, ">>");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentLeft[playerid][50], 0.200000, 1.327000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][50], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][50], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentLeft[playerid][50], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][50], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][50], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][50], 1);

            PTD_EquipmentLeft[playerid][51] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv+54+distance_between_items+12+26,
                start_y+inventory_height-borders_inv-30+distance_between_items+6, "1");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentLeft[playerid][51], 0.260000, 1.620000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][51], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][51], -1);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentLeft[playerid][51], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][51], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][51], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][51], 1);

            PTD_EquipmentLeft[playerid][52] = CreatePlayerTextDraw(playerid, start_x_left+borders_inv,
                start_y+inventory_height-borders_inv-button_height-distance_between_items, "LD_SPAC:white"); // кнопка ready
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][52], button_width, button_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][52], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][52], -5500673);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][52], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][52], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][52], 0);
            PlayerTextDrawSetSelectable(playerid, PTD_EquipmentLeft[playerid][52], true);

            PTD_EquipmentLeft[playerid][53] = CreatePlayerTextDraw(playerid, start_x_left+21,
                start_y+inventory_height-borders_inv-button_height-distance_between_items+7.5, "READY");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentLeft[playerid][53], 1.5*0.200000, 1.5*0.930000);
            PlayerTextDrawTextSize(playerid, PTD_EquipmentLeft[playerid][53], 0.000000, 37.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentLeft[playerid][53], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentLeft[playerid][53], -56);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentLeft[playerid][53], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentLeft[playerid][53], -22740481);
            PlayerTextDrawFont(playerid, PTD_EquipmentLeft[playerid][53], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentLeft[playerid][53], 1);
        }
        case TD_ID_EQUIPMENT_PERSON_INFO:
        {
            new
                count,
                Float:acc_item_width = 25.0, Float:acc_item_height = 33.0,
                Float:person_info_width = borders_inv*2+acc_item_width*4+3*distance_between_items, items_inv_rows = 4, Float:bottom_height = 34.0,
                Float:start_x = 640.0/2-(inventory_width*2+3)/2+inventory_width+3, Float:start_y = 448.0/2-inventory_height/2+45,
                Float:info_start_x = start_x-3-person_info_width, Float:person_info_button_width = 51.0, Float:person_info_button_height =24.33,
                Float:inventory_height = header+(borders_inv*2)+(item_height*items_inv_rows)+(distance_between_items*(items_inv_rows-1))+3+bottom_height;

            // person info
            PTD_EquipmentPersonInfo[playerid][0] = CreatePlayerTextDraw(playerid, info_start_x, start_y, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][0], person_info_width, inventory_height);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][0], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][0], 252645375);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][0], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][0], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][0], 0);

            for(new i = 1; i < 4; i++)
            {
                PTD_EquipmentPersonInfo[playerid][i] = CreatePlayerTextDraw(playerid, info_start_x, start_y, "LD_SPAC:white");
                PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][i], person_info_width, 6.0*(4-i));
                PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][i], 1);
                if(i == 3) PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][i], -22740481);
                else if(i == 2) PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][i], -5500673);
                else PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][i], -5103105);
                PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][i], 255);
                PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][i], 4);
                PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][i], 0);
            }

            PTD_EquipmentPersonInfo[playerid][4] = CreatePlayerTextDraw(playerid, info_start_x+54, start_y+4, "CHARACTER");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentPersonInfo[playerid][4], 0.215000, 1.000000);
            PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][4], 0.000000, 106.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][4], 2);
            PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][4], 1295122687);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentPersonInfo[playerid][4], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][4], -1065484138);
            PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][4], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][4], 1);

            count = 0;
            for(new i = 3; i != -1; i--){
                for(new j = 3; j != -1; j--){
                    if(0 <= i <= 2 && 1 <= j <= 2) continue;
                    PTD_EquipmentPersonInfo[playerid][5+count] = CreatePlayerTextDraw(playerid, info_start_x+borders_inv+j*(acc_item_width+distance_between_items),
                        start_y+header+borders_inv+i*(acc_item_height+distance_between_items), "_"); // буквой U получаетс€. 1 €чейка слева сверху и вниз по букве
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][5+count], acc_item_width, acc_item_height);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][5+count], 1);
                    PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][5+count], -1);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][5+count], 454761471);
                    PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][5+count], 5);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][5+count], 0);
                    PlayerTextDrawSetSelectable(playerid, PTD_EquipmentPersonInfo[playerid][5+count], true);
                    PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][5+count], 0);
                    PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][5+count], 0.000000, 0.000000, 0.000000, -1.000000);
                    count++;
                }
            }

            PTD_EquipmentPersonInfo[playerid][15] = CreatePlayerTextDraw(playerid, info_start_x+borders_inv+acc_item_width+distance_between_items,
                start_y+header+borders_inv, "LD_SPAC:white");
            PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][15], acc_item_width*2+distance_between_items, acc_item_height*3+distance_between_items*2);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][15], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][15], 336860415);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][15], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][15], 4);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][15], 0);

            PTD_EquipmentPersonInfo[playerid][16] = CreatePlayerTextDraw(playerid, info_start_x+borders_inv+acc_item_width+distance_between_items-24,
                start_y+header+borders_inv-2, ""); // скин
            PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][16], 99.0, 103.000000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][16], 1);
            PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][16], -1);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][16], 0);
            PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][16], 5);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][16], 0);
            PlayerTextDrawSetPreviewModel(playerid, PTD_EquipmentPersonInfo[playerid][16], 23);
            PlayerTextDrawSetPreviewRot(playerid, PTD_EquipmentPersonInfo[playerid][16], 0.000000, 0.000000, 0.000000, 1.000000);

            PTD_EquipmentPersonInfo[playerid][17] = CreatePlayerTextDraw(playerid, info_start_x+borders_inv+acc_item_width+distance_between_items+49,
                start_y+header+borders_inv+4, "ID:_1");
            PlayerTextDrawLetterSize(playerid, PTD_EquipmentPersonInfo[playerid][17], 0.165000, 0.770000);
            PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][17], 3);
            PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][17], -56);
            PlayerTextDrawSetShadow(playerid, PTD_EquipmentPersonInfo[playerid][17], 0);
            PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][17], 255);
            PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][17], 1);
            PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][17], 1);

            new ButtonCenter[][] = {"MENU", "GPS", "CARS", "PHONE", "DONATE", "FAMILY"};
            count = 0;
            for(new i; i < 3; i++){
                for(new j; j < 2; j++){
                    PTD_EquipmentPersonInfo[playerid][18+count] = CreatePlayerTextDraw(playerid, info_start_x+borders_inv+j*(person_info_button_width+distance_between_items),
                        start_y+header+2*borders_inv+4*acc_item_height+3*distance_between_items+i*(person_info_button_height+distance_between_items), "LD_SPAC:white"); // 1 кнопки идут сперва слева, сверху вниз. ѕотом справа, сверху вниз
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][18+count], person_info_button_width, person_info_button_height);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][18+count], 1);
                    PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][18+count], -4325121-i*1966080);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][18+count], 255);
                    PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][18+count], 4);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][18+count], 0);
                    PlayerTextDrawSetSelectable(playerid, PTD_EquipmentPersonInfo[playerid][18+count], true);

                    PTD_EquipmentPersonInfo[playerid][24+count] = CreatePlayerTextDraw(playerid, info_start_x+borders_inv+j*(person_info_button_width+distance_between_items)+25,
                        start_y+header+2*borders_inv+4*acc_item_height+3*distance_between_items+i*(person_info_button_height+distance_between_items)+7, ButtonCenter[count]); // 1
                    PlayerTextDrawLetterSize(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 0.216000, 0.960000);
                    PlayerTextDrawTextSize(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 0.000000, 50.000000);
                    PlayerTextDrawAlignment(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 2);
                    PlayerTextDrawColor(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 790495487);
                    PlayerTextDrawSetShadow(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 0);
                    PlayerTextDrawBackgroundColor(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 255);
                    PlayerTextDrawFont(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 1);
                    PlayerTextDrawSetProportional(playerid, PTD_EquipmentPersonInfo[playerid][24+count], 1);
                    count++;
                }
            }
        }
    }
    return 1;
}

CreateMiniGamesTD(playerid, td_x, td_y)
{
    if(playerid == INVALID_PLAYER_ID) return 1;
    PTD_MiniGames[playerid] = CreatePlayerTextDraw(playerid, td_x, td_y, "_");
    PlayerTextDrawTextSize(playerid, PTD_MiniGames[playerid], 66.000000, 63.000000);
    PlayerTextDrawAlignment(playerid, PTD_MiniGames[playerid], 1);
    PlayerTextDrawColor(playerid, PTD_MiniGames[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, PTD_MiniGames[playerid], 0);
    PlayerTextDrawFont(playerid, PTD_MiniGames[playerid], 5);
    PlayerTextDrawSetPreviewModel(playerid, PTD_MiniGames[playerid], 11746);
    PlayerTextDrawSetPreviewRot(playerid, PTD_MiniGames[playerid], 0.000000, 0.000000, 180.000000, 0.500000);
    PlayerTextDrawSetProportional(playerid, PTD_MiniGames[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, PTD_MiniGames[playerid], true);

    PlayerTextDrawShow(playerid, PTD_MiniGames[playerid]);
    return 1;
}

HideTextDraw_Speedometr(playerid, bool:isDestroy)
{
    if(p_info[playerid][p_settings][INTERFACE] == 0)
    {
        for(new i = 32; i != -1; i--)
        {
            if(i < 16 && PTD_SpeedometerInfo[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                if(isDestroy) {
                    PlayerTextDrawDestroy(playerid, PTD_SpeedometerInfo[playerid][i]);
                    PTD_SpeedometerInfo[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                else PlayerTextDrawHide(playerid, PTD_SpeedometerInfo[playerid][i]);
            }
            TextDrawHideForPlayer(playerid, TD_SpeedometerLine[i]);
        }
    }
    else
    {
        TextDrawHideForPlayer(playerid, TD_NewSpeedometer);
        for(new i = MAX_NEW_SPEEDOMER-1; i != -1; i--)
        {
            if(PTD_NewSpeedometer[playerid][i] != PlayerText:INVALID_TEXT_DRAW)
            {
                if(isDestroy) {
                    PlayerTextDrawDestroy(playerid, PTD_NewSpeedometer[playerid][i]);
                    PTD_NewSpeedometer[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                }
                else PlayerTextDrawHide(playerid, PTD_NewSpeedometer[playerid][i]);
            }
        }
    }
    p_temp[playerid][TextDrawSpeedometr] = false;
}

ShowTextDraw_Captcha(playerid, captcha_id)
{
    if(captcha_id != CAPTCHA_PIN_CODE)
        ShowTextDrawForPlayer(playerid, TD_ID_CAPTCHA);
    ShowTextDrawForPlayer(playerid, TD_ID_PIN_CODE);

    p_temp[playerid][TextDrawCaptcha] = captcha_id;
    p_temp[playerid][captcha_text][0] = EOS;
    PlayerTextDrawSetString(playerid, PTD_PinCode[playerid][10], "");
    return 1;
}

HideTextDraw_Captcha(playerid)
{
    HideTextDrawForPlayer(playerid, TD_ID_CAPTCHA);
    HideTextDrawForPlayer(playerid, TD_ID_PIN_CODE);
    return 1;
}

ShowTextDraw_Speedometr(playerid, bool:isCreate)
{
    if(IsPlayerUseMDC(playerid)) return 1;
    new vehicleid = GetPlayerVehicleID(playerid),
    modelid = veh_info[vehicleid][v_model];
    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && vehicleid != 0)
    {
        if( GetVehicleData(modelid, E_VD_TYPE) == VEHICLE_STATE_CAR ||
            GetVehicleData(modelid, E_VD_TYPE) == VEHICLE_STATE_MOTO ||
            GetVehicleData(modelid, E_VD_TYPE) == VEHICLE_STATE_TRAIN ||
            modelid == 462 || modelid == 448)
        {
            p_temp[playerid][TextDrawSpeedometr] = true;
            if(isCreate) CreateTextDrawForPlayer(playerid, TD_ID_SPEEDOMETER);
            if(p_info[playerid][p_settings][INTERFACE] == 0)
            {
                for(new i = 32; i != -1; i--)
                {
                    if(i < 16) PlayerTextDrawShow(playerid, PTD_SpeedometerInfo[playerid][i]);
                    TextDrawShowForPlayer(playerid, TD_SpeedometerLine[i]);
                }
                PlayerTextDrawSetString(playerid, PTD_SpeedometerInfo[playerid][0], GetVehicleName(vehicleid));
            }
            else
            {
                TextDrawShowForPlayer(playerid, TD_NewSpeedometer);
                for(new i = MAX_NEW_SPEEDOMER-1; i != -1; i--) PlayerTextDrawShow(playerid, PTD_NewSpeedometer[playerid][i]);
            }
            for(new i = SPEEDO_NONE+1; i < SPEEDO_ALL; i++) OnPlayerUpdateVehicleInfo(playerid, i);
        }
    }
    return 1;
}
//
TD_LoadGlobal()
{
    TD_BlindBackground = TextDrawCreate(641.199951, 1.500000, "usebox");
    TextDrawLetterSize( TD_BlindBackground, 0.000000, 49.378147);
    TextDrawTextSize( TD_BlindBackground, -2.000000, 0.000000);
    TextDrawAlignment( TD_BlindBackground, 3);
    TextDrawColor( TD_BlindBackground, -1);
    TextDrawUseBox( TD_BlindBackground, true);
    TextDrawBoxColor( TD_BlindBackground, 255);
    TextDrawSetShadow( TD_BlindBackground, 0);
    TextDrawSetOutline( TD_BlindBackground, 0);
    TextDrawBackgroundColor( TD_BlindBackground, 255);
    TextDrawFont( TD_BlindBackground, 1);

    TD_Captcha[0] = TextDrawCreate(260.4997, 112.2000, "LD_SPAC:white"); // фон
    TextDrawTextSize(TD_Captcha[0], 121.0000, 65.0000);
    TextDrawAlignment(TD_Captcha[0], 1);
    TextDrawColor(TD_Captcha[0], 572662527);
    TextDrawBackgroundColor(TD_Captcha[0], 255);
    TextDrawFont(TD_Captcha[0], 4);
    TextDrawSetProportional(TD_Captcha[0], 0);
    TextDrawSetShadow(TD_Captcha[0], 0);
 
    TD_Captcha[1] = TextDrawCreate(262.2999, 115.0999, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[1], 1.0000, 13.0000);
    TextDrawAlignment(TD_Captcha[1], 1);
    TextDrawColor(TD_Captcha[1], -5963521);
    TextDrawBackgroundColor(TD_Captcha[1], 255);
    TextDrawFont(TD_Captcha[1], 4);
    TextDrawSetProportional(TD_Captcha[1], 0);
    TextDrawSetShadow(TD_Captcha[1], 0);
 
    TD_Captcha[2] = TextDrawCreate(262.2999, 115.0999, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[2], 13.0000, 1.0000);
    TextDrawAlignment(TD_Captcha[2], 1);
    TextDrawColor(TD_Captcha[2], -5963521);
    TextDrawBackgroundColor(TD_Captcha[2], 255);
    TextDrawFont(TD_Captcha[2], 4);
    TextDrawSetProportional(TD_Captcha[2], 0);
    TextDrawSetShadow(TD_Captcha[2], 0);
 
    TD_Captcha[3] = TextDrawCreate(377.9070, 115.0999, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[3], 1.0000, 13.0000);
    TextDrawAlignment(TD_Captcha[3], 1);
    TextDrawColor(TD_Captcha[3], -5963521);
    TextDrawBackgroundColor(TD_Captcha[3], 255);
    TextDrawFont(TD_Captcha[3], 4);
    TextDrawSetProportional(TD_Captcha[3], 0);
    TextDrawSetShadow(TD_Captcha[3], 0);
 
    TD_Captcha[4] = TextDrawCreate(377.9070, 115.0999, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[4], -13.0000, 1.0000);
    TextDrawAlignment(TD_Captcha[4], 1);
    TextDrawColor(TD_Captcha[4], -5963521);
    TextDrawBackgroundColor(TD_Captcha[4], 255);
    TextDrawFont(TD_Captcha[4], 4);
    TextDrawSetProportional(TD_Captcha[4], 0);
    TextDrawSetShadow(TD_Captcha[4], 0);
 
    TD_Captcha[5] = TextDrawCreate(262.2999, 174.3026, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[5], 1.0000, -13.0000);
    TextDrawAlignment(TD_Captcha[5], 1);
    TextDrawColor(TD_Captcha[5], -5963521);
    TextDrawBackgroundColor(TD_Captcha[5], 255);
    TextDrawFont(TD_Captcha[5], 4);
    TextDrawSetProportional(TD_Captcha[5], 0);
    TextDrawSetShadow(TD_Captcha[5], 0);
 
    TD_Captcha[6] = TextDrawCreate(262.2999, 173.3025, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[6], 13.0000, 1.0000);
    TextDrawAlignment(TD_Captcha[6], 1);
    TextDrawColor(TD_Captcha[6], -5963521);
    TextDrawBackgroundColor(TD_Captcha[6], 255);
    TextDrawFont(TD_Captcha[6], 4);
    TextDrawSetProportional(TD_Captcha[6], 0);
    TextDrawSetShadow(TD_Captcha[6], 0);
 
    TD_Captcha[7] = TextDrawCreate(377.9070, 174.5026, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[7], 1.0000, -13.0000);
    TextDrawAlignment(TD_Captcha[7], 1);
    TextDrawColor(TD_Captcha[7], -5963521);
    TextDrawBackgroundColor(TD_Captcha[7], 255);
    TextDrawFont(TD_Captcha[7], 4);
    TextDrawSetProportional(TD_Captcha[7], 0);
    TextDrawSetShadow(TD_Captcha[7], 0);
 
    TD_Captcha[8] = TextDrawCreate(377.9070, 173.3025, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[8], -13.0000, 1.0000);
    TextDrawAlignment(TD_Captcha[8], 1);
    TextDrawColor(TD_Captcha[8], -5963521);
    TextDrawBackgroundColor(TD_Captcha[8], 255);
    TextDrawFont(TD_Captcha[8], 4);
    TextDrawSetProportional(TD_Captcha[8], 0);
    TextDrawSetShadow(TD_Captcha[8], 0);
 
    TD_Captcha[9] = TextDrawCreate(312.2030, 173.3025, "LD_SPAC:white");
    TextDrawTextSize(TD_Captcha[9], 15.0000, 1.0000);
    TextDrawAlignment(TD_Captcha[9], 1);
    TextDrawColor(TD_Captcha[9], -5963521);
    TextDrawBackgroundColor(TD_Captcha[9], 255);
    TextDrawFont(TD_Captcha[9], 4);
    TextDrawSetProportional(TD_Captcha[9], 0);
    TextDrawSetShadow(TD_Captcha[9], 0);

    TD_DataTime[0] = TextDrawCreate(545.0001, 382.4843, "flin_txd:flin_times"); // bg time
    TextDrawTextSize(TD_DataTime[0], 88.0000, 103.0000);
    TextDrawAlignment(TD_DataTime[0], 1);
    TextDrawColor(TD_DataTime[0], -1);
    TextDrawBackgroundColor(TD_DataTime[0], 255);
    TextDrawFont(TD_DataTime[0], 4);
    TextDrawSetProportional(TD_DataTime[0], 0);
    TextDrawSetShadow(TD_DataTime[0], 0);

    TD_DataTime[1] = TextDrawCreate(595.6011, 428.4354, "13.04.2020_/_16:47"); // data + time
    TextDrawLetterSize(TD_DataTime[1], 0.1555, 1.1818);
    TextDrawAlignment(TD_DataTime[1], 2);
    TextDrawColor(TD_DataTime[1], -1);
    TextDrawBackgroundColor(TD_DataTime[1], 255);
    TextDrawFont(TD_DataTime[1], 2);
    TextDrawSetProportional(TD_DataTime[1], 1);
    TextDrawSetShadow(TD_DataTime[1], 0);

    /*
    TD_Logo_One[0] = TextDrawCreate(6.1999, 383.4797, "flin_txd:flin_logotype_1"); // лого без акции
    TextDrawTextSize(TD_Logo_One[0], 85.0000, 92.0000);
    TextDrawAlignment(TD_Logo_One[0], 1);
    TextDrawColor(TD_Logo_One[0], -1);
    TextDrawBackgroundColor(TD_Logo_One[0], 255);
    TextDrawFont(TD_Logo_One[0], 4);
    TextDrawSetProportional(TD_Logo_One[0], 0);
    TextDrawSetShadow(TD_Logo_One[0], 0);
    */
    TD_Logo_One[1] = TextDrawCreate(76.7996, 423.9555, "1000"); // кол-во игр. без акции
    TextDrawLetterSize(TD_Logo_One[1], 0.1568, 0.9976);
    TextDrawAlignment(TD_Logo_One[1], 1);
    TextDrawColor(TD_Logo_One[1], -1);
    TextDrawBackgroundColor(TD_Logo_One[1], 255);
    TextDrawFont(TD_Logo_One[1], 2);
    TextDrawSetProportional(TD_Logo_One[1], 1);
    TextDrawSetShadow(TD_Logo_One[1], 0);

    TD_Logo_One[2] = TextDrawCreate(5.4000, 415.8355, "flin_txd:flin_logotype_x2"); // иконка х2
    TextDrawTextSize(TD_Logo_One[2], 25.0000, 27.0000);
    TextDrawAlignment(TD_Logo_One[2], 1);
    TextDrawColor(TD_Logo_One[2], -1);
    TextDrawBackgroundColor(TD_Logo_One[2], 255);
    TextDrawFont(TD_Logo_One[2], 4);
    TextDrawSetProportional(TD_Logo_One[2], 0);
    TextDrawSetShadow(TD_Logo_One[2], 0);

    // Logotype 1
    /*
    TD_Logo_Two[0] = TextDrawCreate(6.1999, 384.9733, "flin_txd:flin_serv_logo2[x3]"); // 2 тип лого
    TextDrawTextSize(TD_Logo_Two[0], 79.0000, 89.0000);
    TextDrawAlignment(TD_Logo_Two[0], 1);
    TextDrawColor(TD_Logo_Two[0], -1);
    TextDrawBackgroundColor(TD_Logo_Two[0], 255);
    TextDrawFont(TD_Logo_Two[0], 4);
    TextDrawSetProportional(TD_Logo_Two[0], 0);
    TextDrawSetShadow(TD_Logo_Two[0], 0);
    */
    TD_Logo_Two[1] = TextDrawCreate(50.0000, 434.4089, "1000"); // кол-во онлайна 2 тип
    TextDrawLetterSize(TD_Logo_Two[1], 0.1567, 0.9080);
    TextDrawAlignment(TD_Logo_Two[1], 1);
    TextDrawColor(TD_Logo_Two[1], -1);
    TextDrawBackgroundColor(TD_Logo_Two[1], 255);
    TextDrawFont(TD_Logo_Two[1], 2);
    TextDrawSetProportional(TD_Logo_Two[1], 1);
    TextDrawSetShadow(TD_Logo_Two[1], 0);
    // Hud
    TD_NewGreenZone = TextDrawCreate(-27.5997, 173.4176, "flin_txd:flin_greenzone"); // зелена€ зона
    TextDrawTextSize(TD_NewGreenZone, 170.0000, 53.0000);
    TextDrawAlignment(TD_NewGreenZone, 1);
    TextDrawColor(TD_NewGreenZone, -1);
    TextDrawBackgroundColor(TD_NewGreenZone, 255);
    TextDrawFont(TD_NewGreenZone, 4);
    TextDrawSetProportional(TD_NewGreenZone, 0);
    TextDrawSetShadow(TD_NewGreenZone, 0);

    TD_GPS = TextDrawCreate(-27.5997, 213.2398, "flin_txd:flin_gps"); // гпс
    TextDrawTextSize(TD_GPS, 170.0000, 53.0000);
    TextDrawAlignment(TD_GPS, 1);
    TextDrawColor(TD_GPS, -1);
    TextDrawBackgroundColor(TD_GPS, 255);
    TextDrawFont(TD_GPS, 4);
    TextDrawSetProportional(TD_GPS, 0);
    TextDrawSetShadow(TD_GPS, 0);

    TD_PressALT = TextDrawCreate(239.7998, 390.4479, "flin_txd:flin_alt"); // alt
    TextDrawTextSize(TD_PressALT, 154.0000, 43.0000);
    TextDrawAlignment(TD_PressALT, 1);
    TextDrawColor(TD_PressALT, -1);
    TextDrawBackgroundColor(TD_PressALT, 255);
    TextDrawFont(TD_PressALT, 4);
    TextDrawSetProportional(TD_PressALT, 0);
    TextDrawSetShadow(TD_PressALT, 0);
    // Service
    TD_ServiceTune[0] = TextDrawCreate(222.5997, 23.0888, "flin_sto:flin_sto_logotuning"); // Ћого
    TextDrawTextSize(TD_ServiceTune[0], 203.0000, 125.0000);
    TextDrawAlignment(TD_ServiceTune[0], 1);
    TextDrawColor(TD_ServiceTune[0], -1);
    TextDrawBackgroundColor(TD_ServiceTune[0], 255);
    TextDrawFont(TD_ServiceTune[0], 4);
    TextDrawSetProportional(TD_ServiceTune[0], 0);
    TextDrawSetShadow(TD_ServiceTune[0], 0);

    TD_ServiceTune[1] = TextDrawCreate(23.0000, 205.2752, "flin_sto:flin_sto_bgslot"); // —лот 1
    TextDrawTextSize(TD_ServiceTune[1], 205.0000, 62.0000);
    TextDrawAlignment(TD_ServiceTune[1], 1);
    TextDrawColor(TD_ServiceTune[1], -1);
    TextDrawBackgroundColor(TD_ServiceTune[1], 255);
    TextDrawFont(TD_ServiceTune[1], 4);
    TextDrawSetProportional(TD_ServiceTune[1], 0);
    TextDrawSetShadow(TD_ServiceTune[1], 0);
    TextDrawSetSelectable(TD_ServiceTune[1], true);

    TD_ServiceTune[2] = TextDrawCreate(23.0000, 249.5773, "flin_sto:flin_sto_bgslot"); // —лот 2
    TextDrawTextSize(TD_ServiceTune[2], 205.0000, 62.0000);
    TextDrawAlignment(TD_ServiceTune[2], 1);
    TextDrawColor(TD_ServiceTune[2], -1);
    TextDrawBackgroundColor(TD_ServiceTune[2], 255);
    TextDrawFont(TD_ServiceTune[2], 4);
    TextDrawSetProportional(TD_ServiceTune[2], 0);
    TextDrawSetShadow(TD_ServiceTune[2], 0);
    TextDrawSetSelectable(TD_ServiceTune[2], true);

    TD_ServiceTune[3] = TextDrawCreate(22.6000, 293.8796, "flin_sto:flin_sto_bgslot"); // —лот 3
    TextDrawTextSize(TD_ServiceTune[3], 205.0000, 62.0000);
    TextDrawAlignment(TD_ServiceTune[3], 1);
    TextDrawColor(TD_ServiceTune[3], -1);
    TextDrawBackgroundColor(TD_ServiceTune[3], 255);
    TextDrawFont(TD_ServiceTune[3], 4);
    TextDrawSetProportional(TD_ServiceTune[3], 0);
    TextDrawSetShadow(TD_ServiceTune[3], 0);
    TextDrawSetSelectable(TD_ServiceTune[3], true);

    TD_ServiceTune[4] = TextDrawCreate(23.0000, 338.1820, "flin_sto:flin_sto_bgslot"); // —лот 4
    TextDrawTextSize(TD_ServiceTune[4], 205.0000, 62.0000);
    TextDrawAlignment(TD_ServiceTune[4], 1);
    TextDrawColor(TD_ServiceTune[4], -1);
    TextDrawBackgroundColor(TD_ServiceTune[4], 255);
    TextDrawFont(TD_ServiceTune[4], 4);
    TextDrawSetProportional(TD_ServiceTune[4], 0);
    TextDrawSetShadow(TD_ServiceTune[4], 0);
    TextDrawSetSelectable(TD_ServiceTune[4], true);

    TD_ServiceTune[5] = TextDrawCreate(81.7994, 380.9909, "flin_sto:flin_sto_right"); // стрелка вправо
    TextDrawTextSize(TD_ServiceTune[5], 54.0000, 64.0000);
    TextDrawAlignment(TD_ServiceTune[5], 1);
    TextDrawColor(TD_ServiceTune[5], -1);
    TextDrawBackgroundColor(TD_ServiceTune[5], 255);
    TextDrawFont(TD_ServiceTune[5], 4);
    TextDrawSetProportional(TD_ServiceTune[5], 0);
    TextDrawSetShadow(TD_ServiceTune[5], 0);
    TextDrawSetSelectable(TD_ServiceTune[5], true);

    TD_ServiceTune[6] = TextDrawCreate(13.3999, 380.9909, "flin_sto:flin_sto_left"); // стрелка влево
    TextDrawTextSize(TD_ServiceTune[6], 54.0000, 64.0000);
    TextDrawAlignment(TD_ServiceTune[6], 1);
    TextDrawColor(TD_ServiceTune[6], -1);
    TextDrawBackgroundColor(TD_ServiceTune[6], 255);
    TextDrawFont(TD_ServiceTune[6], 4);
    TextDrawSetProportional(TD_ServiceTune[6], 0);
    TextDrawSetShadow(TD_ServiceTune[6], 0);
    TextDrawSetSelectable(TD_ServiceTune[6], true);

    TD_ServiceTune[7] = TextDrawCreate(562.2000, 147.5328, "flin_sto:flin_sto_osi"); // выбрать ось
    TextDrawTextSize(TD_ServiceTune[7], 52.0000, 134.0000);
    TextDrawAlignment(TD_ServiceTune[7], 1);
    TextDrawColor(TD_ServiceTune[7], -1);
    TextDrawBackgroundColor(TD_ServiceTune[7], 255);
    TextDrawFont(TD_ServiceTune[7], 4);
    TextDrawSetProportional(TD_ServiceTune[7], 0);
    TextDrawSetShadow(TD_ServiceTune[7], 0);

    TD_ServiceTune[8] = TextDrawCreate(573.7996, 255.0531, "flin_sto:flin_sto_camera"); // кнопка камеры
    TextDrawTextSize(TD_ServiceTune[8], 50.0000, 63.0000);
    TextDrawAlignment(TD_ServiceTune[8], 1);
    TextDrawColor(TD_ServiceTune[8], -1);
    TextDrawBackgroundColor(TD_ServiceTune[8], 255);
    TextDrawFont(TD_ServiceTune[8], 4);
    TextDrawSetProportional(TD_ServiceTune[8], 0);
    TextDrawSetShadow(TD_ServiceTune[8], 0);
    TextDrawSetSelectable(TD_ServiceTune[8], true);

    TD_ServiceTune[9] = TextDrawCreate(522.0000, 357.2528, "Е¶oЩoҐaђ_c¶oЬѓoc¶©:"); // пусто
    TextDrawLetterSize(TD_ServiceTune[9], 0.2718, 1.2316);
    TextDrawAlignment(TD_ServiceTune[9], 1);
    TextDrawColor(TD_ServiceTune[9], -2139062017);
    TextDrawBackgroundColor(TD_ServiceTune[9], 255);
    TextDrawFont(TD_ServiceTune[9], 1);
    TextDrawSetProportional(TD_ServiceTune[9], 1);
    TextDrawSetShadow(TD_ServiceTune[9], 0);

    TD_ServiceTune[10] = TextDrawCreate(520.7999, 367.2084, "$"); // пусто
    TextDrawLetterSize(TD_ServiceTune[10], 0.4611, 2.0578);
    TextDrawAlignment(TD_ServiceTune[10], 1);
    TextDrawColor(TD_ServiceTune[10], 8388863);
    TextDrawBackgroundColor(TD_ServiceTune[10], 255);
    TextDrawFont(TD_ServiceTune[10], 1);
    TextDrawSetProportional(TD_ServiceTune[10], 1);
    TextDrawSetShadow(TD_ServiceTune[10], 0);

    TD_ServiceTune[11] = TextDrawCreate(515.3994, 381.9862, "flin_sto:flin_sto_buy"); // приобрести
    TextDrawTextSize(TD_ServiceTune[11], 103.0000, 63.0000);
    TextDrawAlignment(TD_ServiceTune[11], 1);
    TextDrawColor(TD_ServiceTune[11], -1);
    TextDrawBackgroundColor(TD_ServiceTune[11], 255);
    TextDrawFont(TD_ServiceTune[11], 4);
    TextDrawSetProportional(TD_ServiceTune[11], 0);
    TextDrawSetShadow(TD_ServiceTune[11], 0);
    TextDrawSetSelectable(TD_ServiceTune[11], true);

    TD_ServiceTune[12] = TextDrawCreate(14.5997, 162.9800, "flin_sto:flin_sto_exit"); // назад
    TextDrawTextSize(TD_ServiceTune[12], 54.0000, 64.0000);
    TextDrawAlignment(TD_ServiceTune[12], 1);
    TextDrawColor(TD_ServiceTune[12], -1);
    TextDrawBackgroundColor(TD_ServiceTune[12], 255);
    TextDrawFont(TD_ServiceTune[12], 4);
    TextDrawSetProportional(TD_ServiceTune[12], 0);
    TextDrawSetShadow(TD_ServiceTune[12], 0);
    TextDrawSetSelectable(TD_ServiceTune[12], true);

    TD_ServiceTune[13] = TextDrawCreate(62.5997, 163.5775, "flin_sto:flin_sto_bgslot"); // заглавный слот
    TextDrawTextSize(TD_ServiceTune[13], 202.0000, 62.0000);
    TextDrawAlignment(TD_ServiceTune[13], 1);
    TextDrawColor(TD_ServiceTune[13], -1);
    TextDrawBackgroundColor(TD_ServiceTune[13], 255);
    TextDrawFont(TD_ServiceTune[13], 4);
    TextDrawSetProportional(TD_ServiceTune[13], 0);
    TextDrawSetShadow(TD_ServiceTune[13], 0);

    TD_ServiceTune[14] = TextDrawCreate(217.7996, 380.8905, "flin_sto:flin_sto_bg_center"); // пусто
    TextDrawTextSize(TD_ServiceTune[14], 207.0000, 64.0000);
    TextDrawAlignment(TD_ServiceTune[14], 1);
    TextDrawColor(TD_ServiceTune[14], -1);
    TextDrawBackgroundColor(TD_ServiceTune[14], 255);
    TextDrawFont(TD_ServiceTune[14], 4);
    TextDrawSetProportional(TD_ServiceTune[14], 0);
    TextDrawSetShadow(TD_ServiceTune[14], 0);

    TD_ServiceTune[15] = TextDrawCreate(22.2000, 164.0756, "flin_sto:flin_sto_bgslot"); // слот 1 1
    TextDrawTextSize(TD_ServiceTune[15], 205.0000, 62.0000);
    TextDrawAlignment(TD_ServiceTune[15], 1);
    TextDrawColor(TD_ServiceTune[15], -1);
    TextDrawBackgroundColor(TD_ServiceTune[15], 255);
    TextDrawFont(TD_ServiceTune[15], 4);
    TextDrawSetProportional(TD_ServiceTune[15], 0);
    TextDrawSetShadow(TD_ServiceTune[15], 0);
    TextDrawSetSelectable(TD_ServiceTune[15], true);

    //new Speedometer
    TD_NewSpeedometer = TextDrawCreate(221.899627, 323.800659, "flinspeed:flin_osnova");
    TextDrawTextSize(TD_NewSpeedometer, 192.469909, 123.970336);
    TextDrawAlignment(TD_NewSpeedometer, 1);
    TextDrawColor(TD_NewSpeedometer, -1);
    TextDrawBackgroundColor(TD_NewSpeedometer, 255);
    TextDrawFont(TD_NewSpeedometer, 4);
    TextDrawSetProportional(TD_NewSpeedometer, 0);

    // Pin Code
    TD_PinCode[0] = TextDrawCreate(132.333389, 206.258789, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[0], 374.180358, 52.000000);
    TextDrawAlignment(TD_PinCode[0], 1);
    TextDrawColor(TD_PinCode[0], -25026817);
    TextDrawBackgroundColor(TD_PinCode[0], 255);
    TextDrawFont(TD_PinCode[0], 4);
    TextDrawSetProportional(TD_PinCode[0], 0);

    TD_PinCode[1] = TextDrawCreate(132.233337, 256.518341, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[1], 374.180358, 2.260000);
    TextDrawAlignment(TD_PinCode[1], 1);
    TextDrawColor(TD_PinCode[1], 370546431);
    TextDrawBackgroundColor(TD_PinCode[1], 255);
    TextDrawFont(TD_PinCode[1], 4);
    TextDrawSetProportional(TD_PinCode[1], 0);

    TD_PinCode[2] = TextDrawCreate(132.233261, 188.658798, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[2], 374.180358, 21.000000);
    TextDrawAlignment(TD_PinCode[2], 1);
    TextDrawColor(TD_PinCode[2], 370546431);
    TextDrawBackgroundColor(TD_PinCode[2], 255);
    TextDrawFont(TD_PinCode[2], 4);
    TextDrawSetProportional(TD_PinCode[2], 0);

    TD_PinCode[3] = TextDrawCreate(135.733230, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[3], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[3], 1);
    TextDrawColor(TD_PinCode[3], 370546431);
    TextDrawBackgroundColor(TD_PinCode[3], 255);
    TextDrawFont(TD_PinCode[3], 4);
    TextDrawSetProportional(TD_PinCode[3], 0);
    TextDrawSetSelectable(TD_PinCode[3], true);

    TD_PinCode[4] = TextDrawCreate(172.733230, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[4], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[4], 1);
    TextDrawColor(TD_PinCode[4], 370546431);
    TextDrawBackgroundColor(TD_PinCode[4], 255);
    TextDrawFont(TD_PinCode[4], 4);
    TextDrawSetProportional(TD_PinCode[4], 0);
    TextDrawSetSelectable(TD_PinCode[4], true);

    TD_PinCode[5] = TextDrawCreate(209.733230, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[5], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[5], 1);
    TextDrawColor(TD_PinCode[5], 370546431);
    TextDrawBackgroundColor(TD_PinCode[5], 255);
    TextDrawFont(TD_PinCode[5], 4);
    TextDrawSetProportional(TD_PinCode[5], 0);
    TextDrawSetSelectable(TD_PinCode[5], true);

    TD_PinCode[6] = TextDrawCreate(246.733230, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[6], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[6], 1);
    TextDrawColor(TD_PinCode[6], 370546431);
    TextDrawBackgroundColor(TD_PinCode[6], 255);
    TextDrawFont(TD_PinCode[6], 4);
    TextDrawSetProportional(TD_PinCode[6], 0);
    TextDrawSetSelectable(TD_PinCode[6], true);

    TD_PinCode[7] = TextDrawCreate(283.733245, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[7], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[7], 1);
    TextDrawColor(TD_PinCode[7], 370546431);
    TextDrawBackgroundColor(TD_PinCode[7], 255);
    TextDrawFont(TD_PinCode[7], 4);
    TextDrawSetProportional(TD_PinCode[7], 0);
    TextDrawSetSelectable(TD_PinCode[7], true);

    TD_PinCode[8] = TextDrawCreate(320.733245, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[8], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[8], 1);
    TextDrawColor(TD_PinCode[8], 370546431);
    TextDrawBackgroundColor(TD_PinCode[8], 255);
    TextDrawFont(TD_PinCode[8], 4);
    TextDrawSetProportional(TD_PinCode[8], 0);
    TextDrawSetSelectable(TD_PinCode[8], true);

    TD_PinCode[9] = TextDrawCreate(357.733245, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[9], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[9], 1);
    TextDrawColor(TD_PinCode[9], 370546431);
    TextDrawBackgroundColor(TD_PinCode[9], 255);
    TextDrawFont(TD_PinCode[9], 4);
    TextDrawSetProportional(TD_PinCode[9], 0);
    TextDrawSetSelectable(TD_PinCode[9], true);

    TD_PinCode[10] = TextDrawCreate(394.733245, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[10], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[10], 1);
    TextDrawColor(TD_PinCode[10], 370546431);
    TextDrawBackgroundColor(TD_PinCode[10], 255);
    TextDrawFont(TD_PinCode[10], 4);
    TextDrawSetProportional(TD_PinCode[10], 0);
    TextDrawSetSelectable(TD_PinCode[10], true);

    TD_PinCode[11] = TextDrawCreate(431.733245, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[11], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[11], 1);
    TextDrawColor(TD_PinCode[11], 370546431);
    TextDrawBackgroundColor(TD_PinCode[11], 255);
    TextDrawFont(TD_PinCode[11], 4);
    TextDrawSetProportional(TD_PinCode[11], 0);
    TextDrawSetSelectable(TD_PinCode[11], true);

    TD_PinCode[12] = TextDrawCreate(468.733245, 213.373626, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[12], 34.000000, 39.000000);
    TextDrawAlignment(TD_PinCode[12], 1);
    TextDrawColor(TD_PinCode[12], 370546431);
    TextDrawBackgroundColor(TD_PinCode[12], 255);
    TextDrawFont(TD_PinCode[12], 4);
    TextDrawSetProportional(TD_PinCode[12], 0);
    TextDrawSetSelectable(TD_PinCode[12], true);

    TD_PinCode[13] = TextDrawCreate(246.833374, 268.192474, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[13], 58.000000, 34.000000);
    TextDrawAlignment(TD_PinCode[13], 1);
    TextDrawColor(TD_PinCode[13], 370546431);
    TextDrawBackgroundColor(TD_PinCode[13], 255);
    TextDrawFont(TD_PinCode[13], 4);
    TextDrawSetProportional(TD_PinCode[13], 0);
    TextDrawSetSelectable(TD_PinCode[13], true);

    TD_PinCode[14] = TextDrawCreate(333.933563, 268.192474, "LD_SPAC:white");
    TextDrawTextSize(TD_PinCode[14], 58.000000, 34.000000);
    TextDrawAlignment(TD_PinCode[14], 1);
    TextDrawColor(TD_PinCode[14], 370546431);
    TextDrawBackgroundColor(TD_PinCode[14], 255);
    TextDrawFont(TD_PinCode[14], 4);
    TextDrawSetProportional(TD_PinCode[14], 0);
    TextDrawSetSelectable(TD_PinCode[14], true);

    TD_PinCode[15] = TextDrawCreate(363.000000, 276.000000, "<");
    TextDrawLetterSize(TD_PinCode[15], 0.368665, 2.151704);
    TextDrawTextSize(TD_PinCode[15], 0.000000, 55.000000);
    TextDrawAlignment(TD_PinCode[15], 2);
    TextDrawColor(TD_PinCode[15], -1);
    TextDrawSetShadow(TD_PinCode[15], 0);
    TextDrawBackgroundColor(TD_PinCode[15], 255);
    TextDrawFont(TD_PinCode[15], 2);
    TextDrawSetProportional(TD_PinCode[15], 1);

    TD_PinCode[16] = TextDrawCreate(276.133178, 275.992523, "OK");
    TextDrawLetterSize(TD_PinCode[16], 0.281331, 1.919407);
    TextDrawTextSize(TD_PinCode[16], 0.000000, 54.089984);
    TextDrawAlignment(TD_PinCode[16], 2);
    TextDrawColor(TD_PinCode[16], -1);
    TextDrawSetShadow(TD_PinCode[16], 0);
    TextDrawBackgroundColor(TD_PinCode[16], 255);
    TextDrawFont(TD_PinCode[16], 2);
    TextDrawSetProportional(TD_PinCode[16], 1);

    //«онд камера
    TD_ZondCam[0] = TextDrawCreate(200.600006, 183.000000, "box");
    TextDrawLetterSize(TD_ZondCam[0], 0.000000, -0.354317);
    TextDrawTextSize(TD_ZondCam[0], 0.000000, 37.000000);
    TextDrawAlignment(TD_ZondCam[0], 2);
    TextDrawColor(TD_ZondCam[0], -1);
    TextDrawUseBox(TD_ZondCam[0], 1);
    TextDrawBoxColor(TD_ZondCam[0], -1);
    TextDrawSetShadow(TD_ZondCam[0], 0);
    TextDrawSetOutline(TD_ZondCam[0], 0);
    TextDrawBackgroundColor(TD_ZondCam[0], 255);
    TextDrawFont(TD_ZondCam[0], 1);
    TextDrawSetProportional(TD_ZondCam[0], 1);
    TextDrawSetShadow(TD_ZondCam[0], 0);

    TD_ZondCam[1] = TextDrawCreate(200.100006, 320.000000, "box");
    TextDrawLetterSize(TD_ZondCam[1], 0.000000, -0.354317);
    TextDrawTextSize(TD_ZondCam[1], 0.000000, 37.000000);
    TextDrawAlignment(TD_ZondCam[1], 2);
    TextDrawColor(TD_ZondCam[1], -1);
    TextDrawUseBox(TD_ZondCam[1], 1);
    TextDrawBoxColor(TD_ZondCam[1], -1);
    TextDrawSetShadow(TD_ZondCam[1], 0);
    TextDrawSetOutline(TD_ZondCam[1], 0);
    TextDrawBackgroundColor(TD_ZondCam[1], 255);
    TextDrawFont(TD_ZondCam[1], 1);
    TextDrawSetProportional(TD_ZondCam[1], 1);
    TextDrawSetShadow(TD_ZondCam[1], 0);

    TD_ZondCam[2] = TextDrawCreate(460.000000, 320.000000, "box");
    TextDrawLetterSize(TD_ZondCam[2], 0.000000, -0.354317);
    TextDrawTextSize(TD_ZondCam[2], 0.000000, 37.000000);
    TextDrawAlignment(TD_ZondCam[2], 2);
    TextDrawColor(TD_ZondCam[2], -1);
    TextDrawUseBox(TD_ZondCam[2], 1);
    TextDrawBoxColor(TD_ZondCam[2], -1);
    TextDrawSetShadow(TD_ZondCam[2], 0);
    TextDrawSetOutline(TD_ZondCam[2], 0);
    TextDrawBackgroundColor(TD_ZondCam[2], 255);
    TextDrawFont(TD_ZondCam[2], 1);
    TextDrawSetProportional(TD_ZondCam[2], 1);
    TextDrawSetShadow(TD_ZondCam[2], 0);

    TD_ZondCam[3] = TextDrawCreate(460.000000, 183.000000, "box");
    TextDrawLetterSize(TD_ZondCam[3], 0.000000, -0.354317);
    TextDrawTextSize(TD_ZondCam[3], 0.000000, 37.000000);
    TextDrawAlignment(TD_ZondCam[3], 2);
    TextDrawColor(TD_ZondCam[3], -1);
    TextDrawUseBox(TD_ZondCam[3], 1);
    TextDrawBoxColor(TD_ZondCam[3], -1);
    TextDrawSetShadow(TD_ZondCam[3], 0);
    TextDrawSetOutline(TD_ZondCam[3], 0);
    TextDrawBackgroundColor(TD_ZondCam[3], 255);
    TextDrawFont(TD_ZondCam[3], 1);
    TextDrawSetProportional(TD_ZondCam[3], 1);
    TextDrawSetShadow(TD_ZondCam[3], 0);

    TD_ZondCam[4] = TextDrawCreate(180.365997, 183.000015, "box");
    TextDrawLetterSize(TD_ZondCam[4], 0.000000, 3.206443);
    TextDrawTextSize(TD_ZondCam[4], 0.000000, -5.000000);
    TextDrawAlignment(TD_ZondCam[4], 2);
    TextDrawColor(TD_ZondCam[4], -1);
    TextDrawUseBox(TD_ZondCam[4], 1);
    TextDrawBoxColor(TD_ZondCam[4], -1);
    TextDrawSetShadow(TD_ZondCam[4], 0);
    TextDrawSetOutline(TD_ZondCam[4], 0);
    TextDrawBackgroundColor(TD_ZondCam[4], 255);
    TextDrawFont(TD_ZondCam[4], 1);
    TextDrawSetProportional(TD_ZondCam[4], 1);
    TextDrawSetShadow(TD_ZondCam[4], 0);

    TD_ZondCam[5] = TextDrawCreate(180.365997, 286.833435, "box");
    TextDrawLetterSize(TD_ZondCam[5], 0.000000, 3.206443);
    TextDrawTextSize(TD_ZondCam[5], 0.000000, -5.000000);
    TextDrawAlignment(TD_ZondCam[5], 2);
    TextDrawColor(TD_ZondCam[5], -1);
    TextDrawUseBox(TD_ZondCam[5], 1);
    TextDrawBoxColor(TD_ZondCam[5], -1);
    TextDrawSetShadow(TD_ZondCam[5], 0);
    TextDrawSetOutline(TD_ZondCam[5], 0);
    TextDrawBackgroundColor(TD_ZondCam[5], 255);
    TextDrawFont(TD_ZondCam[5], 1);
    TextDrawSetProportional(TD_ZondCam[5], 1);
    TextDrawSetShadow(TD_ZondCam[5], 0);

    TD_ZondCam[6] = TextDrawCreate(480.219818, 288.000122, "box");
    TextDrawLetterSize(TD_ZondCam[6], 0.000000, 3.206443);
    TextDrawTextSize(TD_ZondCam[6], 0.000000, -5.000000);
    TextDrawAlignment(TD_ZondCam[6], 2);
    TextDrawColor(TD_ZondCam[6], -1);
    TextDrawUseBox(TD_ZondCam[6], 1);
    TextDrawBoxColor(TD_ZondCam[6], -1);
    TextDrawSetShadow(TD_ZondCam[6], 0);
    TextDrawSetOutline(TD_ZondCam[6], 0);
    TextDrawBackgroundColor(TD_ZondCam[6], 255);
    TextDrawFont(TD_ZondCam[6], 1);
    TextDrawSetProportional(TD_ZondCam[6], 1);
    TextDrawSetShadow(TD_ZondCam[6], 0);

    TD_ZondCam[7] = TextDrawCreate(479.751220, 183.000106, "box");
    TextDrawLetterSize(TD_ZondCam[7], 0.000000, 3.206443);
    TextDrawTextSize(TD_ZondCam[7], 0.000000, -5.000000);
    TextDrawAlignment(TD_ZondCam[7], 2);
    TextDrawColor(TD_ZondCam[7], -1);
    TextDrawUseBox(TD_ZondCam[7], 1);
    TextDrawBoxColor(TD_ZondCam[7], -1);
    TextDrawSetShadow(TD_ZondCam[7], 0);
    TextDrawSetOutline(TD_ZondCam[7], 0);
    TextDrawBackgroundColor(TD_ZondCam[7], 255);
    TextDrawFont(TD_ZondCam[7], 1);
    TextDrawSetProportional(TD_ZondCam[7], 1);
    TextDrawSetShadow(TD_ZondCam[7], 0);

    TD_ZondCam[8] = TextDrawCreate(468.506805, 164.333358, "box");
    TextDrawLetterSize(TD_ZondCam[8], 0.000000, 0.442169);
    TextDrawTextSize(TD_ZondCam[8], 0.000000, 18.000000);
    TextDrawAlignment(TD_ZondCam[8], 2);
    TextDrawColor(TD_ZondCam[8], -1);
    TextDrawUseBox(TD_ZondCam[8], 1);
    TextDrawBoxColor(TD_ZondCam[8], -176);
    TextDrawSetShadow(TD_ZondCam[8], 0);
    TextDrawSetOutline(TD_ZondCam[8], 0);
    TextDrawBackgroundColor(TD_ZondCam[8], 255);
    TextDrawFont(TD_ZondCam[8], 1);
    TextDrawSetProportional(TD_ZondCam[8], 1);
    TextDrawSetShadow(TD_ZondCam[8], 0);

    TD_ZondCam[9] = TextDrawCreate(481.656890, 164.133316, "box");
    TextDrawLetterSize(TD_ZondCam[9], 0.000000, 0.489021);
    TextDrawTextSize(TD_ZondCam[9], 469.500030, 0.000000);
    TextDrawAlignment(TD_ZondCam[9], 1);
    TextDrawColor(TD_ZondCam[9], -1);
    TextDrawUseBox(TD_ZondCam[9], 1);
    TextDrawBoxColor(TD_ZondCam[9], -1523963137);
    TextDrawSetShadow(TD_ZondCam[9], 0);
    TextDrawSetOutline(TD_ZondCam[9], 0);
    TextDrawBackgroundColor(TD_ZondCam[9], 255);
    TextDrawFont(TD_ZondCam[9], 1);
    TextDrawSetProportional(TD_ZondCam[9], 1);
    TextDrawSetShadow(TD_ZondCam[9], 0);

    TD_ZondCam[10] = TextDrawCreate(456.593719, 167.250015, "box");
    TextDrawLetterSize(TD_ZondCam[10], 0.000000, -0.166905);
    TextDrawTextSize(TD_ZondCam[10], 0.000000, -2.000000);
    TextDrawAlignment(TD_ZondCam[10], 2);
    TextDrawColor(TD_ZondCam[10], -1);
    TextDrawUseBox(TD_ZondCam[10], 1);
    TextDrawBoxColor(TD_ZondCam[10], -176);
    TextDrawSetShadow(TD_ZondCam[10], 0);
    TextDrawSetOutline(TD_ZondCam[10], 0);
    TextDrawBackgroundColor(TD_ZondCam[10], 255);
    TextDrawFont(TD_ZondCam[10], 1);
    TextDrawSetProportional(TD_ZondCam[10], 1);
    TextDrawSetShadow(TD_ZondCam[10], 0);

    /*
    TD_vehicle_info[0] = TextDrawCreate(429.000000, 409.000000, ".");
    TextDrawBackgroundColor(TD_vehicle_info[0], 255);
    TextDrawFont(TD_vehicle_info[0], 2);
    TextDrawLetterSize(TD_vehicle_info[0], 36.150016, -0.500000);
    TextDrawColor(TD_vehicle_info[0], -1);
    TextDrawSetOutline(TD_vehicle_info[0], 0);
    TextDrawSetProportional(TD_vehicle_info[0], 1);
    TextDrawSetShadow(TD_vehicle_info[0], 1);
    TextDrawSetSelectable(TD_vehicle_info[0], 0);

    TD_vehicle_info[1] = TextDrawCreate(485.000000, 395.000000, "vehicle");
    TextDrawBackgroundColor(TD_vehicle_info[1], 255);
    TextDrawFont(TD_vehicle_info[1], 3);
    TextDrawLetterSize(TD_vehicle_info[1], 0.400000, 0.899999);
    TextDrawColor(TD_vehicle_info[1], -1);
    TextDrawSetOutline(TD_vehicle_info[1], 0);
    TextDrawSetProportional(TD_vehicle_info[1], 1);
    TextDrawSetShadow(TD_vehicle_info[1], 1);
    TextDrawSetSelectable(TD_vehicle_info[1], 0);
    */

    // List Page
    TD_ListPage[0] = TextDrawCreate(164.000000, 116.800033, "LD_SPAC:white");
    TextDrawTextSize(TD_ListPage[0], 313.489074, 145.390151);
    TextDrawAlignment(TD_ListPage[0], 1);
    TextDrawColor(TD_ListPage[0], 370546431);
    TextDrawBackgroundColor(TD_ListPage[0], 255);
    TextDrawFont(TD_ListPage[0], 4);
    TextDrawSetProportional(TD_ListPage[0], 0);

    TD_ListPage[1] = TextDrawCreate(139.000000, 84.200027, "");
    TextDrawTextSize(TD_ListPage[1], 58.000000, 60.000000);
    TextDrawAlignment(TD_ListPage[1], 1);
    TextDrawColor(TD_ListPage[1], -25026817);
    TextDrawBackgroundColor(TD_ListPage[1], 0);
    TextDrawFont(TD_ListPage[1], 5);
    TextDrawSetProportional(TD_ListPage[1], 0);
    TextDrawSetPreviewModel(TD_ListPage[1], 19177);
    TextDrawSetPreviewRot(TD_ListPage[1], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_ListPage[2] = TextDrawCreate(444.200500, 84.400024, "");
    TextDrawTextSize(TD_ListPage[2], 58.000000, 60.000000);
    TextDrawAlignment(TD_ListPage[2], 1);
    TextDrawColor(TD_ListPage[2], -25026817);
    TextDrawBackgroundColor(TD_ListPage[2], 0);
    TextDrawFont(TD_ListPage[2], 5);
    TextDrawSetProportional(TD_ListPage[2], 0);
    TextDrawSetPreviewModel(TD_ListPage[2], 19177);
    TextDrawSetPreviewRot(TD_ListPage[2], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_ListPage[3] = TextDrawCreate(168.000015, 111.800033, "LD_SPAC:white");
    TextDrawTextSize(TD_ListPage[3], 305.039520, 5.260004);
    TextDrawAlignment(TD_ListPage[3], 1);
    TextDrawColor(TD_ListPage[3], -25026817);
    TextDrawBackgroundColor(TD_ListPage[3], 255);
    TextDrawFont(TD_ListPage[3], 4);
    TextDrawSetProportional(TD_ListPage[3], 0);

    TD_ListPage[4] = TextDrawCreate(138.800003, 295.299865, "");
    TextDrawTextSize(TD_ListPage[4], 58.000000, -60.000000);
    TextDrawAlignment(TD_ListPage[4], 1);
    TextDrawColor(TD_ListPage[4], -25026817);
    TextDrawBackgroundColor(TD_ListPage[4], 0);
    TextDrawFont(TD_ListPage[4], 5);
    TextDrawSetProportional(TD_ListPage[4], 0);
    TextDrawSetPreviewModel(TD_ListPage[4], 19177);
    TextDrawSetPreviewRot(TD_ListPage[4], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_ListPage[5] = TextDrawCreate(444.150970, 295.199859, "");
    TextDrawTextSize(TD_ListPage[5], 58.000000, -60.000000);
    TextDrawAlignment(TD_ListPage[5], 1);
    TextDrawColor(TD_ListPage[5], -25026817);
    TextDrawBackgroundColor(TD_ListPage[5], 0);
    TextDrawFont(TD_ListPage[5], 5);
    TextDrawSetProportional(TD_ListPage[5], 0);
    TextDrawSetPreviewModel(TD_ListPage[5], 19177);
    TextDrawSetPreviewRot(TD_ListPage[5], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_ListPage[6] = TextDrawCreate(168.000000, 262.499877, "LD_SPAC:white");
    TextDrawTextSize(TD_ListPage[6], 305.501342, 5.260004);
    TextDrawAlignment(TD_ListPage[6], 1);
    TextDrawColor(TD_ListPage[6], -25026817);
    TextDrawBackgroundColor(TD_ListPage[6], 255);
    TextDrawFont(TD_ListPage[6], 4);
    TextDrawSetProportional(TD_ListPage[6], 0);

    TD_ListPage[7] = TextDrawCreate(169.000000, 122.800033, "");
    TextDrawTextSize(TD_ListPage[7], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[7], 1);
    TextDrawColor(TD_ListPage[7], 100);
    TextDrawBackgroundColor(TD_ListPage[7], 0);
    TextDrawFont(TD_ListPage[7], 5);
    TextDrawSetProportional(TD_ListPage[7], 0);
    TextDrawSetSelectable(TD_ListPage[7], true);
    TextDrawSetPreviewModel(TD_ListPage[7], 2729);
    TextDrawSetPreviewRot(TD_ListPage[7], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[8] = TextDrawCreate(230.000000, 122.800033, "");
    TextDrawTextSize(TD_ListPage[8], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[8], 1);
    TextDrawColor(TD_ListPage[8], 100);
    TextDrawBackgroundColor(TD_ListPage[8], 0);
    TextDrawFont(TD_ListPage[8], 5);
    TextDrawSetProportional(TD_ListPage[8], 0);
    TextDrawSetSelectable(TD_ListPage[8], true);
    TextDrawSetPreviewModel(TD_ListPage[8], 2729);
    TextDrawSetPreviewRot(TD_ListPage[8], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[9] = TextDrawCreate(290.000000, 122.800033, "");
    TextDrawTextSize(TD_ListPage[9], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[9], 1);
    TextDrawColor(TD_ListPage[9], 100);
    TextDrawBackgroundColor(TD_ListPage[9], 0);
    TextDrawFont(TD_ListPage[9], 5);
    TextDrawSetProportional(TD_ListPage[9], 0);
    TextDrawSetSelectable(TD_ListPage[9], true);
    TextDrawSetPreviewModel(TD_ListPage[9], 2729);
    TextDrawSetPreviewRot(TD_ListPage[9], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[10] = TextDrawCreate(352.000000, 122.800033, "");
    TextDrawTextSize(TD_ListPage[10], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[10], 1);
    TextDrawColor(TD_ListPage[10], 100);
    TextDrawBackgroundColor(TD_ListPage[10], 0);
    TextDrawFont(TD_ListPage[10], 5);
    TextDrawSetProportional(TD_ListPage[10], 0);
    TextDrawSetSelectable(TD_ListPage[10], true);
    TextDrawSetPreviewModel(TD_ListPage[10], 2729);
    TextDrawSetPreviewRot(TD_ListPage[10], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[11] = TextDrawCreate(414.000000, 122.800033, "");
    TextDrawTextSize(TD_ListPage[11], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[11], 1);
    TextDrawColor(TD_ListPage[11], 100);
    TextDrawBackgroundColor(TD_ListPage[11], 0);
    TextDrawFont(TD_ListPage[11], 5);
    TextDrawSetProportional(TD_ListPage[11], 0);
    TextDrawSetSelectable(TD_ListPage[11], true);
    TextDrawSetPreviewModel(TD_ListPage[11], 2729);
    TextDrawSetPreviewRot(TD_ListPage[11], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[12] = TextDrawCreate(169.000000, 191.799926, "");
    TextDrawTextSize(TD_ListPage[12], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[12], 1);
    TextDrawColor(TD_ListPage[12], 100);
    TextDrawBackgroundColor(TD_ListPage[12], 0);
    TextDrawFont(TD_ListPage[12], 5);
    TextDrawSetProportional(TD_ListPage[12], 0);
    TextDrawSetSelectable(TD_ListPage[12], true);
    TextDrawSetPreviewModel(TD_ListPage[12], 2729);
    TextDrawSetPreviewRot(TD_ListPage[12], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[13] = TextDrawCreate(230.000000, 191.799926, "");
    TextDrawTextSize(TD_ListPage[13], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[13], 1);
    TextDrawColor(TD_ListPage[13], 100);
    TextDrawBackgroundColor(TD_ListPage[13], 0);
    TextDrawFont(TD_ListPage[13], 5);
    TextDrawSetProportional(TD_ListPage[13], 0);
    TextDrawSetSelectable(TD_ListPage[13], true);
    TextDrawSetPreviewModel(TD_ListPage[13], 2729);
    TextDrawSetPreviewRot(TD_ListPage[13], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[14] = TextDrawCreate(290.000000, 191.799926, "");
    TextDrawTextSize(TD_ListPage[14], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[14], 1);
    TextDrawColor(TD_ListPage[14], 100);
    TextDrawBackgroundColor(TD_ListPage[14], 0);
    TextDrawFont(TD_ListPage[14], 5);
    TextDrawSetProportional(TD_ListPage[14], 0);
    TextDrawSetSelectable(TD_ListPage[14], true);
    TextDrawSetPreviewModel(TD_ListPage[14], 2729);
    TextDrawSetPreviewRot(TD_ListPage[14], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[15] = TextDrawCreate(352.000000, 191.799926, "");
    TextDrawTextSize(TD_ListPage[15], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[15], 1);
    TextDrawColor(TD_ListPage[15], 100);
    TextDrawBackgroundColor(TD_ListPage[15], 0);
    TextDrawFont(TD_ListPage[15], 5);
    TextDrawSetProportional(TD_ListPage[15], 0);
    TextDrawSetSelectable(TD_ListPage[15], true);
    TextDrawSetPreviewModel(TD_ListPage[15], 2729);
    TextDrawSetPreviewRot(TD_ListPage[15], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[16] = TextDrawCreate(414.000000, 191.799926, "");
    TextDrawTextSize(TD_ListPage[16], 57.799942, 64.000000);
    TextDrawAlignment(TD_ListPage[16], 1);
    TextDrawColor(TD_ListPage[16], 100);
    TextDrawBackgroundColor(TD_ListPage[16], 0);
    TextDrawFont(TD_ListPage[16], 5);
    TextDrawSetProportional(TD_ListPage[16], 0);
    TextDrawSetSelectable(TD_ListPage[16], true);
    TextDrawSetPreviewModel(TD_ListPage[16], 2729);
    TextDrawSetPreviewRot(TD_ListPage[16], 0.000000, 0.000000, 0.000000, 0.600000);

    TD_ListPage[17] = TextDrawCreate(286.000000, 276.399963, "LD_SPAC:white");
    TextDrawTextSize(TD_ListPage[17], 59.999710, 16.699998);
    TextDrawAlignment(TD_ListPage[17], 1);
    TextDrawColor(TD_ListPage[17], -25026817);
    TextDrawBackgroundColor(TD_ListPage[17], 255);
    TextDrawFont(TD_ListPage[17], 4);
    TextDrawSetProportional(TD_ListPage[17], 0);

    TD_ListPage[18] = TextDrawCreate(276.000000, 272.399963, "LD_BEAT:сhit");
    TextDrawTextSize(TD_ListPage[18], 21.000000, 24.900003);
    TextDrawAlignment(TD_ListPage[18], 1);
    TextDrawColor(TD_ListPage[18], -25026817);
    TextDrawBackgroundColor(TD_ListPage[18], 255);
    TextDrawFont(TD_ListPage[18], 4);
    TextDrawSetProportional(TD_ListPage[18], 0);

    TD_ListPage[19] = TextDrawCreate(336.000000, 272.399963, "LD_BEAT:сhit");
    TextDrawTextSize(TD_ListPage[19], 21.000000, 24.900003);
    TextDrawAlignment(TD_ListPage[19], 1);
    TextDrawColor(TD_ListPage[19], -25026817);
    TextDrawBackgroundColor(TD_ListPage[19], 255);
    TextDrawFont(TD_ListPage[19], 4);
    TextDrawSetProportional(TD_ListPage[19], 0);

    TD_ListPage[20] = TextDrawCreate(243.399993, 276.399963, "LD_SPAC:white");
    TextDrawTextSize(TD_ListPage[20], 12.379808, 16.699998);
    TextDrawAlignment(TD_ListPage[20], 1);
    TextDrawColor(TD_ListPage[20], -25026817);
    TextDrawBackgroundColor(TD_ListPage[20], 255);
    TextDrawFont(TD_ListPage[20], 4);
    TextDrawSetProportional(TD_ListPage[20], 0);

    TD_ListPage[21] = TextDrawCreate(232.399932, 272.599975, "LD_BEAT:сhit");
    TextDrawTextSize(TD_ListPage[21], 21.000000, 24.390003);
    TextDrawAlignment(TD_ListPage[21], 1);
    TextDrawColor(TD_ListPage[21], -25026817);
    TextDrawBackgroundColor(TD_ListPage[21], 255);
    TextDrawFont(TD_ListPage[21], 4);
    TextDrawSetProportional(TD_ListPage[21], 0);

    TD_ListPage[22] = TextDrawCreate(245.800018, 272.599975, "LD_BEAT:сhit");
    TextDrawTextSize(TD_ListPage[22], 21.000000, 24.390003);
    TextDrawAlignment(TD_ListPage[22], 1);
    TextDrawColor(TD_ListPage[22], -25026817);
    TextDrawBackgroundColor(TD_ListPage[22], 255);
    TextDrawFont(TD_ListPage[22], 4);
    TextDrawSetProportional(TD_ListPage[22], 0);

    TD_ListPage[23] = TextDrawCreate(249.333221, 279.399963, "<<");
    TextDrawLetterSize(TD_ListPage[23], 0.161329, 1.131257);
    TextDrawTextSize(TD_ListPage[23], 7.000000, 25.020000);
    TextDrawAlignment(TD_ListPage[23], 2);
    TextDrawColor(TD_ListPage[23], -1);
    TextDrawUseBox(TD_ListPage[23], 1);
    TextDrawBoxColor(TD_ListPage[23], 0);
    TextDrawSetShadow(TD_ListPage[23], 0);
    TextDrawBackgroundColor(TD_ListPage[23], 255);
    TextDrawFont(TD_ListPage[23], 2);
    TextDrawSetProportional(TD_ListPage[23], 1);
    TextDrawSetSelectable(TD_ListPage[23], true);

    TD_ListPage[24] = TextDrawCreate(377.399993, 276.399963, "LD_SPAC:white");
    TextDrawTextSize(TD_ListPage[24], 12.379808, 16.699998);
    TextDrawAlignment(TD_ListPage[24], 1);
    TextDrawColor(TD_ListPage[24], -25026817);
    TextDrawBackgroundColor(TD_ListPage[24], 255);
    TextDrawFont(TD_ListPage[24], 4);
    TextDrawSetProportional(TD_ListPage[24], 0);

    TD_ListPage[25] = TextDrawCreate(366.399932, 272.599975, "LD_BEAT:сhit");
    TextDrawTextSize(TD_ListPage[25], 21.000000, 24.390003);
    TextDrawAlignment(TD_ListPage[25], 1);
    TextDrawColor(TD_ListPage[25], -25026817);
    TextDrawBackgroundColor(TD_ListPage[25], 255);
    TextDrawFont(TD_ListPage[25], 4);
    TextDrawSetProportional(TD_ListPage[25], 0);

    TD_ListPage[26] = TextDrawCreate(379.800018, 272.599975, "LD_BEAT:сhit");
    TextDrawTextSize(TD_ListPage[26], 21.000000, 24.390003);
    TextDrawAlignment(TD_ListPage[26], 1);
    TextDrawColor(TD_ListPage[26], -25026817);
    TextDrawBackgroundColor(TD_ListPage[26], 255);
    TextDrawFont(TD_ListPage[26], 4);
    TextDrawSetProportional(TD_ListPage[26], 0);

    TD_ListPage[27] = TextDrawCreate(383.933197, 279.399963, ">>");
    TextDrawLetterSize(TD_ListPage[27], 0.161329, 1.131257);
    TextDrawTextSize(TD_ListPage[27], 7.000000, 25.000000);
    TextDrawAlignment(TD_ListPage[27], 2);
    TextDrawColor(TD_ListPage[27], -1);
    TextDrawUseBox(TD_ListPage[27], 1);
    TextDrawBoxColor(TD_ListPage[27], 0);
    TextDrawSetShadow(TD_ListPage[27], 0);
    TextDrawBackgroundColor(TD_ListPage[27], 255);
    TextDrawFont(TD_ListPage[27], 2);
    TextDrawSetProportional(TD_ListPage[27], 1);
    TextDrawSetSelectable(TD_ListPage[27], true);

    //capture
    TD_Capture[0] = TextDrawCreate(-4.399981, 175.103195, "");
    TextDrawTextSize(TD_Capture[0], 60.000000, 54.600040);
    TextDrawAlignment(TD_Capture[0], 1);
    TextDrawColor(TD_Capture[0], -25026817);
    TextDrawBackgroundColor(TD_Capture[0], 0);
    TextDrawFont(TD_Capture[0], 5);
    TextDrawSetProportional(TD_Capture[0], 0);
    TextDrawSetPreviewModel(TD_Capture[0], 19177);
    TextDrawSetPreviewRot(TD_Capture[0], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_Capture[1] = TextDrawCreate(76.599983, 175.103195, "");
    TextDrawTextSize(TD_Capture[1], 60.000000, 54.600040);
    TextDrawAlignment(TD_Capture[1], 1);
    TextDrawColor(TD_Capture[1], -25026817);
    TextDrawBackgroundColor(TD_Capture[1], 0);
    TextDrawFont(TD_Capture[1], 5);
    TextDrawSetProportional(TD_Capture[1], 0);
    TextDrawSetPreviewModel(TD_Capture[1], 19177);
    TextDrawSetPreviewRot(TD_Capture[1], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_Capture[2] = TextDrawCreate(21.333330, 205.192489, "LD_SPAC:white");
    TextDrawTextSize(TD_Capture[2], 89.369918, 26.800041);
    TextDrawAlignment(TD_Capture[2], 1);
    TextDrawColor(TD_Capture[2], 336860415);
    TextDrawBackgroundColor(TD_Capture[2], 255);
    TextDrawFont(TD_Capture[2], 4);
    TextDrawSetProportional(TD_Capture[2], 0);

    TD_Capture[3] = TextDrawCreate(25.699991, 199.959030, "LD_SPAC:white");
    TextDrawTextSize(TD_Capture[3], 80.799911, 5.199995);
    TextDrawAlignment(TD_Capture[3], 1);
    TextDrawColor(TD_Capture[3], -25026817);
    TextDrawBackgroundColor(TD_Capture[3], 255);
    TextDrawFont(TD_Capture[3], 4);
    TextDrawSetProportional(TD_Capture[3], 0);

    TD_Capture[4] = TextDrawCreate(17.466644, 201.459167, "");
    TextDrawTextSize(TD_Capture[4], 29.200012, 34.200016);
    TextDrawAlignment(TD_Capture[4], 1);
    TextDrawColor(TD_Capture[4], 150);
    TextDrawBackgroundColor(TD_Capture[4], 0);
    TextDrawFont(TD_Capture[4], 5);
    TextDrawSetProportional(TD_Capture[4], 0);
    TextDrawSetPreviewModel(TD_Capture[4], 2729);
    TextDrawSetPreviewRot(TD_Capture[4], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_Capture[5] = TextDrawCreate(84.966659, 201.459167, "");
    TextDrawTextSize(TD_Capture[5], 29.200012, 34.200016);
    TextDrawAlignment(TD_Capture[5], 1);
    TextDrawColor(TD_Capture[5], 150);
    TextDrawBackgroundColor(TD_Capture[5], 0);
    TextDrawFont(TD_Capture[5], 5);
    TextDrawSetProportional(TD_Capture[5], 0);
    TextDrawSetPreviewModel(TD_Capture[5], 2729);
    TextDrawSetPreviewRot(TD_Capture[5], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_Capture[6] = TextDrawCreate(21.333330, 232.592819, "LD_SPAC:white");
    TextDrawTextSize(TD_Capture[6], 89.369918, 18.400009);
    TextDrawAlignment(TD_Capture[6], 1);
    TextDrawColor(TD_Capture[6], 336860415);
    TextDrawBackgroundColor(TD_Capture[6], 255);
    TextDrawFont(TD_Capture[6], 4);
    TextDrawSetProportional(TD_Capture[6], 0);

    TD_Capture[7] = TextDrawCreate(65.999984, 232.885559, "-_MY_PERSONAL_SCORE_-");
    TextDrawLetterSize(TD_Capture[7], 0.131328, 0.882368);
    TextDrawTextSize(TD_Capture[7], 0.000000, 87.199981);
    TextDrawAlignment(TD_Capture[7], 2);
    TextDrawColor(TD_Capture[7], -926365441);
    TextDrawSetShadow(TD_Capture[7], 0);
    TextDrawBackgroundColor(TD_Capture[7], 255);
    TextDrawFont(TD_Capture[7], 2);
    TextDrawSetProportional(TD_Capture[7], 1);

    TD_Capture[8] = TextDrawCreate(21.333330, 251.493011, "LD_SPAC:white");
    TextDrawTextSize(TD_Capture[8], 89.369918, 18.400009);
    TextDrawAlignment(TD_Capture[8], 1);
    TextDrawColor(TD_Capture[8], 336860415);
    TextDrawBackgroundColor(TD_Capture[8], 255);
    TextDrawFont(TD_Capture[8], 4);
    TextDrawSetProportional(TD_Capture[8], 0);

    TD_Capture[9] = TextDrawCreate(65.999984, 251.785781, "-_DAMAGE_INFO_-");
    TextDrawLetterSize(TD_Capture[9], 0.131328, 0.882368);
    TextDrawTextSize(TD_Capture[9], 0.000000, 87.199981);
    TextDrawAlignment(TD_Capture[9], 2);
    TextDrawColor(TD_Capture[9], -926365441);
    TextDrawSetShadow(TD_Capture[9], 0);
    TextDrawBackgroundColor(TD_Capture[9], 255);
    TextDrawFont(TD_Capture[9], 2);
    TextDrawSetProportional(TD_Capture[9], 1);

    TD_Capture[10] = TextDrawCreate(21.333330, 270.392761, "LD_SPAC:white");
    TextDrawTextSize(TD_Capture[10], 89.369918, 18.400009);
    TextDrawAlignment(TD_Capture[10], 1);
    TextDrawColor(TD_Capture[10], 336860415);
    TextDrawBackgroundColor(TD_Capture[10], 255);
    TextDrawFont(TD_Capture[10], 4);
    TextDrawSetProportional(TD_Capture[10], 0);

    TD_Capture[11] = TextDrawCreate(65.999984, 270.585937, "-_TOP_-");
    TextDrawLetterSize(TD_Capture[11], 0.131328, 0.882368);
    TextDrawTextSize(TD_Capture[11], 0.000000, 87.199981);
    TextDrawAlignment(TD_Capture[11], 2);
    TextDrawColor(TD_Capture[11], -926365441);
    TextDrawSetShadow(TD_Capture[11], 0);
    TextDrawBackgroundColor(TD_Capture[11], 255);
    TextDrawFont(TD_Capture[11], 2);
    TextDrawSetProportional(TD_Capture[11], 1);

    TD_Capture[12] = TextDrawCreate(-4.399981, 318.903839, "");
    TextDrawTextSize(TD_Capture[12], 60.000000, -54.599998);
    TextDrawAlignment(TD_Capture[12], 1);
    TextDrawColor(TD_Capture[12], -25026817);
    TextDrawBackgroundColor(TD_Capture[12], 0);
    TextDrawFont(TD_Capture[12], 5);
    TextDrawSetProportional(TD_Capture[12], 0);
    TextDrawSetPreviewModel(TD_Capture[12], 19177);
    TextDrawSetPreviewRot(TD_Capture[12], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_Capture[13] = TextDrawCreate(76.600044, 318.903839, "");
    TextDrawTextSize(TD_Capture[13], 60.000000, -54.599998);
    TextDrawAlignment(TD_Capture[13], 1);
    TextDrawColor(TD_Capture[13], -25026817);
    TextDrawBackgroundColor(TD_Capture[13], 0);
    TextDrawFont(TD_Capture[13], 5);
    TextDrawSetProportional(TD_Capture[13], 0);
    TextDrawSetPreviewModel(TD_Capture[13], 19177);
    TextDrawSetPreviewRot(TD_Capture[13], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_Capture[14] = TextDrawCreate(25.733327, 288.900238, "LD_SPAC:white");
    TextDrawTextSize(TD_Capture[14], 80.799911, 5.199995);
    TextDrawAlignment(TD_Capture[14], 1);
    TextDrawColor(TD_Capture[14], -25026817);
    TextDrawBackgroundColor(TD_Capture[14], 255);
    TextDrawFont(TD_Capture[14], 4);
    TextDrawSetProportional(TD_Capture[14], 0);

    //Green Zone
    TD_GreenZone[0] = TextDrawCreate(3.000333, 427.118682, "LD_SPAC:white");
    TextDrawTextSize(TD_GreenZone[0], 45.000000, 17.000000);
    TextDrawAlignment(TD_GreenZone[0], 1);
    TextDrawBackgroundColor(TD_GreenZone[0], 255);
    TextDrawFont(TD_GreenZone[0], 4);
    TextDrawSetProportional(TD_GreenZone[0], 0);

    TD_GreenZone[1] = TextDrawCreate(3.600363, 427.918670, "LD_SPAC:white");
    TextDrawTextSize(TD_GreenZone[1], 43.699989, 15.400005);
    TextDrawAlignment(TD_GreenZone[1], 1);
    TextDrawColor(TD_GreenZone[1], -22740737);
    TextDrawBackgroundColor(TD_GreenZone[1], 255);
    TextDrawFont(TD_GreenZone[1], 4);
    TextDrawSetProportional(TD_GreenZone[1], 0);

    TD_GreenZone[2] = TextDrawCreate(25.633304, 430.622375, "GREEN_ZONE");
    TextDrawLetterSize(TD_GreenZone[2], 0.149994, 1.010962);
    TextDrawTextSize(TD_GreenZone[2], 0.000000, 40.999893);
    TextDrawAlignment(TD_GreenZone[2], 2);
    TextDrawColor(TD_GreenZone[2], -1);
    TextDrawSetShadow(TD_GreenZone[2], 0);
    TextDrawBackgroundColor(TD_GreenZone[2], 255);
    TextDrawFont(TD_GreenZone[2], 2);
    TextDrawSetProportional(TD_GreenZone[2], 1);

    //recon
    TD_Recon[0] = TextDrawCreate(8.499998, 159.700042, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[0], 124.899955, 247.800231);
    TextDrawAlignment(TD_Recon[0], 1);
    TextDrawColor(TD_Recon[0], -916383489);
    TextDrawBackgroundColor(TD_Recon[0], 255);
    TextDrawFont(TD_Recon[0], 4);
    TextDrawSetProportional(TD_Recon[0], 0);

    TD_Recon[1] = TextDrawCreate(9.999979, 161.637039, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[1], 122.000000, 244.000000);
    TextDrawAlignment(TD_Recon[1], 1);
    TextDrawColor(TD_Recon[1], -697820161);
    TextDrawBackgroundColor(TD_Recon[1], 255);
    TextDrawFont(TD_Recon[1], 4);
    TextDrawSetProportional(TD_Recon[1], 0);

    TD_Recon[2] = TextDrawCreate(11.666646, 164.125946, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[2], 118.229995, 239.240112);
    TextDrawAlignment(TD_Recon[2], 1);
    TextDrawColor(TD_Recon[2], 336860415);
    TextDrawBackgroundColor(TD_Recon[2], 255);
    TextDrawFont(TD_Recon[2], 4);
    TextDrawSetProportional(TD_Recon[2], 0);

    TD_Recon[3] = TextDrawCreate(18.000000, 172.000000, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[3], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[3], 1);
    TextDrawColor(TD_Recon[3], 1179010815);
    TextDrawBackgroundColor(TD_Recon[3], 255);
    TextDrawFont(TD_Recon[3], 4);
    TextDrawSetProportional(TD_Recon[3], 0);
    TextDrawSetSelectable(TD_Recon[3], true);

    TD_Recon[4] = TextDrawCreate(18.000000, 192.100006, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[4], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[4], 1);
    TextDrawColor(TD_Recon[4], 1179010815); //
    TextDrawBackgroundColor(TD_Recon[4], 255);
    TextDrawFont(TD_Recon[4], 4);
    TextDrawSetProportional(TD_Recon[4], 0);
    TextDrawSetSelectable(TD_Recon[4], true);

    TD_Recon[5] = TextDrawCreate(18.000000, 212.000000, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[5], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[5], 1);
    TextDrawColor(TD_Recon[5], 1179010815);
    TextDrawBackgroundColor(TD_Recon[5], 255);
    TextDrawFont(TD_Recon[5], 4);
    TextDrawSetProportional(TD_Recon[5], 0);
    TextDrawSetSelectable(TD_Recon[5], true);

    TD_Recon[6] = TextDrawCreate(18.000000, 231.899993, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[6], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[6], 1);
    TextDrawColor(TD_Recon[6], 1179010815);
    TextDrawBackgroundColor(TD_Recon[6], 255);
    TextDrawFont(TD_Recon[6], 4);
    TextDrawSetProportional(TD_Recon[6], 0);
    TextDrawSetSelectable(TD_Recon[6], true);

    TD_Recon[7] = TextDrawCreate(18.000000, 252.099945, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[7], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[7], 1);
    TextDrawColor(TD_Recon[7], 1179010815);
    TextDrawBackgroundColor(TD_Recon[7], 255);
    TextDrawFont(TD_Recon[7], 4);
    TextDrawSetProportional(TD_Recon[7], 0);
    TextDrawSetSelectable(TD_Recon[7], true);

    TD_Recon[8] = TextDrawCreate(18.000000, 272.499969, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[8], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[8], 1);
    TextDrawColor(TD_Recon[8], 1179010815);
    TextDrawBackgroundColor(TD_Recon[8], 255);
    TextDrawFont(TD_Recon[8], 4);
    TextDrawSetProportional(TD_Recon[8], 0);
    TextDrawSetSelectable(TD_Recon[8], true);

    TD_Recon[9] = TextDrawCreate(18.000000, 292.799987, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[9], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[9], 1);
    TextDrawColor(TD_Recon[9], 1179010815);
    TextDrawBackgroundColor(TD_Recon[9], 255);
    TextDrawFont(TD_Recon[9], 4);
    TextDrawSetProportional(TD_Recon[9], 0);
    TextDrawSetSelectable(TD_Recon[9], true);

    TD_Recon[10] = TextDrawCreate(18.000000, 313.000000, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[10], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[10], 1);
    TextDrawColor(TD_Recon[10], 1179010815);
    TextDrawBackgroundColor(TD_Recon[10], 255);
    TextDrawFont(TD_Recon[10], 4);
    TextDrawSetProportional(TD_Recon[10], 0);
    TextDrawSetSelectable(TD_Recon[10], true);

    TD_Recon[11] = TextDrawCreate(18.000000, 333.000000, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[11], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[11], 1);
    TextDrawColor(TD_Recon[11], 1179010815);
    TextDrawBackgroundColor(TD_Recon[11], 255);
    TextDrawFont(TD_Recon[11], 4);
    TextDrawSetProportional(TD_Recon[11], 0);
    TextDrawSetSelectable(TD_Recon[11], true);

    TD_Recon[12] = TextDrawCreate(18.000000, 353.200012, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[12], 105.200141, 17.600004);
    TextDrawAlignment(TD_Recon[12], 1);
    TextDrawColor(TD_Recon[12], 1179010815);
    TextDrawBackgroundColor(TD_Recon[12], 255);
    TextDrawFont(TD_Recon[12], 4);
    TextDrawSetProportional(TD_Recon[12], 0);
    TextDrawSetSelectable(TD_Recon[12], true);

    TD_Recon[13] = TextDrawCreate(70.499977, 174.799987, "STATS");
    TextDrawLetterSize(TD_Recon[13], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[13], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[13], 2);
    TextDrawColor(TD_Recon[13], -421075201);
    TextDrawSetShadow(TD_Recon[13], 0);
    TextDrawBackgroundColor(TD_Recon[13], 255);
    TextDrawFont(TD_Recon[13], 1);
    TextDrawSetProportional(TD_Recon[13], 1);

    TD_Recon[14] = TextDrawCreate(70.499977, 194.899993, "BAN");
    TextDrawLetterSize(TD_Recon[14], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[14], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[14], 2);
    TextDrawColor(TD_Recon[14], -421075201);
    TextDrawSetShadow(TD_Recon[14], 0);
    TextDrawBackgroundColor(TD_Recon[14], 255);
    TextDrawFont(TD_Recon[14], 1);
    TextDrawSetProportional(TD_Recon[14], 1);

    TD_Recon[15] = TextDrawCreate(70.499977, 214.400192, "WARN");
    TextDrawLetterSize(TD_Recon[15], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[15], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[15], 2);
    TextDrawColor(TD_Recon[15], -421075201);
    TextDrawSetShadow(TD_Recon[15], 0);
    TextDrawBackgroundColor(TD_Recon[15], 255);
    TextDrawFont(TD_Recon[15], 1);
    TextDrawSetProportional(TD_Recon[15], 1);

    TD_Recon[16] = TextDrawCreate(70.499977, 234.500396, "JAIL");
    TextDrawLetterSize(TD_Recon[16], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[16], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[16], 2);
    TextDrawColor(TD_Recon[16], -421075201);
    TextDrawSetShadow(TD_Recon[16], 0);
    TextDrawBackgroundColor(TD_Recon[16], 255);
    TextDrawFont(TD_Recon[16], 1);
    TextDrawSetProportional(TD_Recon[16], 1);

    TD_Recon[17] = TextDrawCreate(70.499977, 254.600601, "MUTE");
    TextDrawLetterSize(TD_Recon[17], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[17], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[17], 2);
    TextDrawColor(TD_Recon[17], -421075201);
    TextDrawSetShadow(TD_Recon[17], 0);
    TextDrawBackgroundColor(TD_Recon[17], 255);
    TextDrawFont(TD_Recon[17], 1);
    TextDrawSetProportional(TD_Recon[17], 1);

    TD_Recon[18] = TextDrawCreate(70.499977, 274.999847, "KICK");
    TextDrawLetterSize(TD_Recon[18], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[18], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[18], 2);
    TextDrawColor(TD_Recon[18], -421075201);
    TextDrawSetShadow(TD_Recon[18], 0);
    TextDrawBackgroundColor(TD_Recon[18], 255);
    TextDrawFont(TD_Recon[18], 1);
    TextDrawSetProportional(TD_Recon[18], 1);

    TD_Recon[19] = TextDrawCreate(70.499977, 295.399017, "(Un)Freeze");
    TextDrawLetterSize(TD_Recon[19], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[19], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[19], 2);
    TextDrawColor(TD_Recon[19], -421075201);
    TextDrawSetShadow(TD_Recon[19], 0);
    TextDrawBackgroundColor(TD_Recon[19], 255);
    TextDrawFont(TD_Recon[19], 1);
    TextDrawSetProportional(TD_Recon[19], 1);

    TD_Recon[20] = TextDrawCreate(70.499977, 315.198211, "SPAWN PLAYER");
    TextDrawLetterSize(TD_Recon[20], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[20], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[20], 2);
    TextDrawColor(TD_Recon[20], -421075201);
    TextDrawSetShadow(TD_Recon[20], 0);
    TextDrawBackgroundColor(TD_Recon[20], 255);
    TextDrawFont(TD_Recon[20], 1);
    TextDrawSetProportional(TD_Recon[20], 1);

    TD_Recon[21] = TextDrawCreate(70.499977, 335.297393, "HIDE MENU");
    TextDrawLetterSize(TD_Recon[21], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[21], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[21], 2);
    TextDrawColor(TD_Recon[21], -421075201);
    TextDrawSetShadow(TD_Recon[21], 0);
    TextDrawBackgroundColor(TD_Recon[21], 255);
    TextDrawFont(TD_Recon[21], 1);
    TextDrawSetProportional(TD_Recon[21], 1);

    TD_Recon[22] = TextDrawCreate(70.499977, 355.696563, "EXIT RECON");
    TextDrawLetterSize(TD_Recon[22], 0.293998, 1.330368);
    TextDrawTextSize(TD_Recon[22], 0.000000, 102.599990);
    TextDrawAlignment(TD_Recon[22], 2);
    TextDrawColor(TD_Recon[22], -421075201);
    TextDrawSetShadow(TD_Recon[22], 0);
    TextDrawBackgroundColor(TD_Recon[22], 255);
    TextDrawFont(TD_Recon[22], 1);
    TextDrawSetProportional(TD_Recon[22], 1);

    TD_Recon[23] = TextDrawCreate(105.900016, 381.000000, "NEXT_>>");
    TextDrawLetterSize(TD_Recon[23], 0.226998, 1.483850);
    TextDrawTextSize(TD_Recon[23], 10.000000, 40.000000);
    TextDrawAlignment(TD_Recon[23], 2);
    TextDrawColor(TD_Recon[23], -1);
    TextDrawUseBox(TD_Recon[23], 1);
    TextDrawBoxColor(TD_Recon[23], 0);
    TextDrawSetShadow(TD_Recon[23], 0);
    TextDrawBackgroundColor(TD_Recon[23], 255);
    TextDrawFont(TD_Recon[23], 2);
    TextDrawSetProportional(TD_Recon[23], 1);
    TextDrawSetSelectable(TD_Recon[23], true);

    TD_Recon[24] = TextDrawCreate(35.799789, 381.000000, "<<_BACK");
    TextDrawLetterSize(TD_Recon[24], 0.226998, 1.483850);
    TextDrawTextSize(TD_Recon[24], 10.000000, 40.000000);
    TextDrawAlignment(TD_Recon[24], 2);
    TextDrawColor(TD_Recon[24], -1);
    TextDrawUseBox(TD_Recon[24], 1);
    TextDrawBoxColor(TD_Recon[24], 0);
    TextDrawSetShadow(TD_Recon[24], 0);
    TextDrawBackgroundColor(TD_Recon[24], 255);
    TextDrawFont(TD_Recon[24], 2);
    TextDrawSetProportional(TD_Recon[24], 1);
    TextDrawSetSelectable(TD_Recon[24], true);

    TD_Recon[25] = TextDrawCreate(2.799998, 164.199890, "");
    TextDrawTextSize(TD_Recon[25], 126.899841, 252.100067);
    TextDrawAlignment(TD_Recon[25], 1);
    TextDrawColor(TD_Recon[25], -249);
    TextDrawBackgroundColor(TD_Recon[25], 0);
    TextDrawFont(TD_Recon[25], 5);
    TextDrawSetProportional(TD_Recon[25], 0);
    TextDrawSetPreviewModel(TD_Recon[25], 19177);
    TextDrawSetPreviewRot(TD_Recon[25], 0.000000, 112.000000, 0.000000, 0.098800);

    TD_Recon[26] = TextDrawCreate(507.799865, 137.299957, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[26], 128.830108, 111.099899);
    TextDrawAlignment(TD_Recon[26], 1);
    TextDrawColor(TD_Recon[26], -697820161);
    TextDrawBackgroundColor(TD_Recon[26], 255);
    TextDrawFont(TD_Recon[26], 4);
    TextDrawSetProportional(TD_Recon[26], 0);

    TD_Recon[27] = TextDrawCreate(509.600036, 139.100006, "LD_SPAC:white");
    TextDrawTextSize(TD_Recon[27], 125.200134, 107.299774);
    TextDrawAlignment(TD_Recon[27], 1);
    TextDrawColor(TD_Recon[27], 336860415);
    TextDrawBackgroundColor(TD_Recon[27], 255);
    TextDrawFont(TD_Recon[27], 4);
    TextDrawSetProportional(TD_Recon[27], 0);

    TD_Recon[28] = TextDrawCreate(515.000000, 143.000000, "Name:");
    TextDrawLetterSize(TD_Recon[28], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[28], 1);
    TextDrawColor(TD_Recon[28], -421075201);
    TextDrawSetShadow(TD_Recon[28], 0);
    TextDrawBackgroundColor(TD_Recon[28], 255);
    TextDrawFont(TD_Recon[28], 1);
    TextDrawSetProportional(TD_Recon[28], 1);

    TD_Recon[29] = TextDrawCreate(515.000000, 153.000610, "Level:");
    TextDrawLetterSize(TD_Recon[29], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[29], 1);
    TextDrawColor(TD_Recon[29], -421075201);
    TextDrawSetShadow(TD_Recon[29], 0);
    TextDrawBackgroundColor(TD_Recon[29], 255);
    TextDrawFont(TD_Recon[29], 1);
    TextDrawSetProportional(TD_Recon[29], 1);

    TD_Recon[30] = TextDrawCreate(515.000000, 162.801208, "Ping:");
    TextDrawLetterSize(TD_Recon[30], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[30], 1);
    TextDrawColor(TD_Recon[30], -421075201);
    TextDrawSetShadow(TD_Recon[30], 0);
    TextDrawBackgroundColor(TD_Recon[30], 255);
    TextDrawFont(TD_Recon[30], 1);
    TextDrawSetProportional(TD_Recon[30], 1);

    TD_Recon[31] = TextDrawCreate(515.000000, 172.701812, "HP/Arm.:");
    TextDrawLetterSize(TD_Recon[31], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[31], 1);
    TextDrawColor(TD_Recon[31], -421075201);
    TextDrawSetShadow(TD_Recon[31], 0);
    TextDrawBackgroundColor(TD_Recon[31], 255);
    TextDrawFont(TD_Recon[31], 1);
    TextDrawSetProportional(TD_Recon[31], 1);

    TD_Recon[32] = TextDrawCreate(515.000000, 182.702423, "Gun:");
    TextDrawLetterSize(TD_Recon[32], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[32], 1);
    TextDrawColor(TD_Recon[32], -421075201);
    TextDrawSetShadow(TD_Recon[32], 0);
    TextDrawBackgroundColor(TD_Recon[32], 255);
    TextDrawFont(TD_Recon[32], 1);
    TextDrawSetProportional(TD_Recon[32], 1);

    TD_Recon[33] = TextDrawCreate(515.000000, 192.403015, "Speed:");
    TextDrawLetterSize(TD_Recon[33], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[33], 1);
    TextDrawColor(TD_Recon[33], -421075201);
    TextDrawSetShadow(TD_Recon[33], 0);
    TextDrawBackgroundColor(TD_Recon[33], 255);
    TextDrawFont(TD_Recon[33], 1);
    TextDrawSetProportional(TD_Recon[33], 1);

    TD_Recon[34] = TextDrawCreate(515.000000, 202.503631, "Reg.IP:");
    TextDrawLetterSize(TD_Recon[34], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[34], 1);
    TextDrawColor(TD_Recon[34], -421075201);
    TextDrawSetShadow(TD_Recon[34], 0);
    TextDrawBackgroundColor(TD_Recon[34], 255);
    TextDrawFont(TD_Recon[34], 1);
    TextDrawSetProportional(TD_Recon[34], 1);

    TD_Recon[35] = TextDrawCreate(515.000000, 212.604248, "IP:");
    TextDrawLetterSize(TD_Recon[35], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[35], 1);
    TextDrawColor(TD_Recon[35], -421075201);
    TextDrawSetShadow(TD_Recon[35], 0);
    TextDrawBackgroundColor(TD_Recon[35], 255);
    TextDrawFont(TD_Recon[35], 1);
    TextDrawSetProportional(TD_Recon[35], 1);

    TD_Recon[36] = TextDrawCreate(515.000000, 222.104827, "Warn:");
    TextDrawLetterSize(TD_Recon[36], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[36], 1);
    TextDrawColor(TD_Recon[36], -421075201);
    TextDrawSetShadow(TD_Recon[36], 0);
    TextDrawBackgroundColor(TD_Recon[36], 255);
    TextDrawFont(TD_Recon[36], 1);
    TextDrawSetProportional(TD_Recon[36], 1);

    TD_Recon[37] = TextDrawCreate(515.000000, 232.105438, "Money:");
    TextDrawLetterSize(TD_Recon[37], 0.213666, 1.102221);
    TextDrawAlignment(TD_Recon[37], 1);
    TextDrawColor(TD_Recon[37], -421075201);
    TextDrawSetShadow(TD_Recon[37], 0);
    TextDrawBackgroundColor(TD_Recon[37], 255);
    TextDrawFont(TD_Recon[37], 1);
    TextDrawSetProportional(TD_Recon[37], 1);

    TD_Recon[38] = TextDrawCreate(533.198730, 139.100128, "");
    TextDrawTextSize(TD_Recon[38], 101.100074, 112.999938);
    TextDrawAlignment(TD_Recon[38], 1);
    TextDrawColor(TD_Recon[38], -249);
    TextDrawBackgroundColor(TD_Recon[38], 0);
    TextDrawFont(TD_Recon[38], 5);
    TextDrawSetProportional(TD_Recon[38], 0);
    TextDrawSetPreviewModel(TD_Recon[38], 19177);
    TextDrawSetPreviewRot(TD_Recon[38], 0.000000, 112.000000, 0.000000, 0.098800);

    //trade preview
    TD_TradePreview[0] = TextDrawCreate(-24.466684, 134.233474, "");
    TextDrawTextSize(TD_TradePreview[0], 81.000000, 52.000000);
    TextDrawAlignment(TD_TradePreview[0], 1);
    TextDrawColor(TD_TradePreview[0], -25026817);
    TextDrawBackgroundColor(TD_TradePreview[0], 0);
    TextDrawFont(TD_TradePreview[0], 5);
    TextDrawSetProportional(TD_TradePreview[0], 0);
    TextDrawSetPreviewModel(TD_TradePreview[0], 19177);
    TextDrawSetPreviewRot(TD_TradePreview[0], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_TradePreview[1] = TextDrawCreate(93.466705, 134.377838, "");
    TextDrawTextSize(TD_TradePreview[1], 81.000000, 52.000000);
    TextDrawAlignment(TD_TradePreview[1], 1);
    TextDrawColor(TD_TradePreview[1], -25026817);
    TextDrawBackgroundColor(TD_TradePreview[1], 0);
    TextDrawFont(TD_TradePreview[1], 5);
    TextDrawSetProportional(TD_TradePreview[1], 0);
    TextDrawSetPreviewModel(TD_TradePreview[1], 19177);
    TextDrawSetPreviewRot(TD_TradePreview[1], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_TradePreview[2] = TextDrawCreate(-24.266683, 345.197326, "");
    TextDrawTextSize(TD_TradePreview[2], 81.000000, -52.000000);
    TextDrawAlignment(TD_TradePreview[2], 1);
    TextDrawColor(TD_TradePreview[2], -25026817);
    TextDrawBackgroundColor(TD_TradePreview[2], 0);
    TextDrawFont(TD_TradePreview[2], 5);
    TextDrawSetProportional(TD_TradePreview[2], 0);
    TextDrawSetPreviewModel(TD_TradePreview[2], 19177);
    TextDrawSetPreviewRot(TD_TradePreview[2], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_TradePreview[3] = TextDrawCreate(93.900032, 345.297393, "");
    TextDrawTextSize(TD_TradePreview[3], 81.000000, -52.000000);
    TextDrawAlignment(TD_TradePreview[3], 1);
    TextDrawColor(TD_TradePreview[3], -25026817);
    TextDrawBackgroundColor(TD_TradePreview[3], 0);
    TextDrawFont(TD_TradePreview[3], 5);
    TextDrawSetProportional(TD_TradePreview[3], 0);
    TextDrawSetPreviewModel(TD_TradePreview[3], 19177);
    TextDrawSetPreviewRot(TD_TradePreview[3], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_TradePreview[4] = TextDrawCreate(16.333309, 157.903564, "LD_SPAC:white");
    TextDrawTextSize(TD_TradePreview[4], 117.440002, 163.349990);
    TextDrawAlignment(TD_TradePreview[4], 1);
    TextDrawColor(TD_TradePreview[4], -25026817);
    TextDrawBackgroundColor(TD_TradePreview[4], 255);
    TextDrawFont(TD_TradePreview[4], 4);
    TextDrawSetProportional(TD_TradePreview[4], 0);

    TD_TradePreview[5] = TextDrawCreate(10.333331, 162.881301, "LD_SPAC:white");
    TextDrawTextSize(TD_TradePreview[5], 130.000000, 154.000000);
    TextDrawAlignment(TD_TradePreview[5], 1);
    TextDrawColor(TD_TradePreview[5], 370546431);
    TextDrawBackgroundColor(TD_TradePreview[5], 255);
    TextDrawFont(TD_TradePreview[5], 4);
    TextDrawSetProportional(TD_TradePreview[5], 0);

    TD_TradePreview[6] = TextDrawCreate(-19.633333, 124.677970, "");
    TextDrawTextSize(TD_TradePreview[6], 189.000000, 230.000000);
    TextDrawAlignment(TD_TradePreview[6], 1);
    TextDrawColor(TD_TradePreview[6], 100);
    TextDrawBackgroundColor(TD_TradePreview[6], 0);
    TextDrawFont(TD_TradePreview[6], 5);
    TextDrawSetProportional(TD_TradePreview[6], 0);
    TextDrawSetPreviewModel(TD_TradePreview[6], 2729);
    TextDrawSetPreviewRot(TD_TradePreview[6], 0.000000, 0.000000, 0.000000, 1.000000);

    TD_TradePreview[7] = TextDrawCreate(10.233321, 162.932678, "PARTICLE:lamp_shad_64");
    TextDrawTextSize(TD_TradePreview[7], 131.359985, 153.779998);
    TextDrawAlignment(TD_TradePreview[7], 1);
    TextDrawColor(TD_TradePreview[7], -226);
    TextDrawBackgroundColor(TD_TradePreview[7], 255);
    TextDrawFont(TD_TradePreview[7], 4);
    TextDrawSetProportional(TD_TradePreview[7], 0);
    ///////
    TD_SpeedometerLine[0] = TextDrawCreate(384.599731, 379.897186, "");
    TextDrawTextSize(TD_SpeedometerLine[0], 25.000000, 56.000030);
    TextDrawAlignment(TD_SpeedometerLine[0], 1);
    TextDrawColor(TD_SpeedometerLine[0], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[0], 0);
    TextDrawFont(TD_SpeedometerLine[0], 5);
    TextDrawSetProportional(TD_SpeedometerLine[0], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[0], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[0], 15.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[1] = TextDrawCreate(232.299758, 379.897186, "");
    TextDrawTextSize(TD_SpeedometerLine[1], 25.000000, 56.000030);
    TextDrawAlignment(TD_SpeedometerLine[1], 1);
    TextDrawColor(TD_SpeedometerLine[1], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[1], 0);
    TextDrawFont(TD_SpeedometerLine[1], 5);
    TextDrawSetProportional(TD_SpeedometerLine[1], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[1], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[1], 15.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[2] = TextDrawCreate(241.299636, 387.037872, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[2], 18.000000, 22.000000);
    TextDrawAlignment(TD_SpeedometerLine[2], 1);
    TextDrawColor(TD_SpeedometerLine[2], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[2], 255);
    TextDrawFont(TD_SpeedometerLine[2], 4);
    TextDrawSetProportional(TD_SpeedometerLine[2], 0);

    TD_SpeedometerLine[3] = TextDrawCreate(250.966461, 390.656372, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[3], 141.450378, 33.039989);
    TextDrawAlignment(TD_SpeedometerLine[3], 1);
    TextDrawColor(TD_SpeedometerLine[3], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[3], 255);
    TextDrawFont(TD_SpeedometerLine[3], 4);
    TextDrawSetProportional(TD_SpeedometerLine[3], 0);

    TD_SpeedometerLine[4] = TextDrawCreate(246.299804, 398.123046, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[4], 148.139984, 16.000000);
    TextDrawAlignment(TD_SpeedometerLine[4], 1);
    TextDrawColor(TD_SpeedometerLine[4], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[4], 255);
    TextDrawFont(TD_SpeedometerLine[4], 4);
    TextDrawSetProportional(TD_SpeedometerLine[4], 0);

    TD_SpeedometerLine[5] = TextDrawCreate(291.766632, 377.419189, "");
    TextDrawTextSize(TD_SpeedometerLine[5], 25.000000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[5], 1);
    TextDrawColor(TD_SpeedometerLine[5], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[5], 0);
    TextDrawFont(TD_SpeedometerLine[5], 5);
    TextDrawSetProportional(TD_SpeedometerLine[5], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[5], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[5], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[6] = TextDrawCreate(294.066711, 381.519439, "");
    TextDrawTextSize(TD_SpeedometerLine[6], 23.500000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[6], 1);
    TextDrawColor(TD_SpeedometerLine[6], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[6], 0);
    TextDrawFont(TD_SpeedometerLine[6], 5);
    TextDrawSetProportional(TD_SpeedometerLine[6], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[6], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[6], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[7] = TextDrawCreate(321.368408, 381.604644, "");
    TextDrawTextSize(TD_SpeedometerLine[7], 23.500000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[7], 1);
    TextDrawColor(TD_SpeedometerLine[7], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[7], 0);
    TextDrawFont(TD_SpeedometerLine[7], 5);
    TextDrawSetProportional(TD_SpeedometerLine[7], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[7], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[7], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[8] = TextDrawCreate(322.168487, 377.504394, "");
    TextDrawTextSize(TD_SpeedometerLine[8], 25.000000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[8], 1);
    TextDrawColor(TD_SpeedometerLine[8], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[8], 0);

    TextDrawFont(TD_SpeedometerLine[8], 5);
    TextDrawSetProportional(TD_SpeedometerLine[8], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[8], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[8], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[9] = TextDrawCreate(322.168487, 377.504394, "");
    TextDrawTextSize(TD_SpeedometerLine[9], 25.000000, 57.499725);
    TextDrawAlignment(TD_SpeedometerLine[9], 1);
    TextDrawColor(TD_SpeedometerLine[9], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[9], 0);
    TextDrawFont(TD_SpeedometerLine[9], 5);
    TextDrawSetProportional(TD_SpeedometerLine[9], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[9], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[9], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[10] = TextDrawCreate(306.133392, 389.970886, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[10], 27.000007, 33.699989);
    TextDrawAlignment(TD_SpeedometerLine[10], 1);
    TextDrawColor(TD_SpeedometerLine[10], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[10], 255);
    TextDrawFont(TD_SpeedometerLine[10], 4);
    TextDrawSetProportional(TD_SpeedometerLine[10], 0);

    TD_SpeedometerLine[11] = TextDrawCreate(382.664642, 387.037872, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[11], 18.000000, 22.000000);
    TextDrawAlignment(TD_SpeedometerLine[11], 1);
    TextDrawColor(TD_SpeedometerLine[11], -5963521);
    TextDrawBackgroundColor(TD_SpeedometerLine[11], 255);
    TextDrawFont(TD_SpeedometerLine[11], 4);
    TextDrawSetProportional(TD_SpeedometerLine[11], 0);

    TD_SpeedometerLine[12] = TextDrawCreate(242.866790, 388.793365, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[12], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[12], 1);
    TextDrawColor(TD_SpeedometerLine[12], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[12], 255);
    TextDrawFont(TD_SpeedometerLine[12], 4);
    TextDrawSetProportional(TD_SpeedometerLine[12], 0);

    TD_SpeedometerLine[13] = TextDrawCreate(267.466430, 388.793365, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[13], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[13], 1);
    TextDrawColor(TD_SpeedometerLine[13], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[13], 255);
    TextDrawFont(TD_SpeedometerLine[13], 4);
    TextDrawSetProportional(TD_SpeedometerLine[13], 0);

    TD_SpeedometerLine[14] = TextDrawCreate(307.700134, 423.141052, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[14], 25.000000, 27.000000);
    TextDrawAlignment(TD_SpeedometerLine[14], 1);
    TextDrawColor(TD_SpeedometerLine[14], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[14], 255);
    TextDrawFont(TD_SpeedometerLine[14], 4);
    TextDrawSetProportional(TD_SpeedometerLine[14], 0);

    TD_SpeedometerLine[15] = TextDrawCreate(403.700225, 442.878601, "");
    TextDrawTextSize(TD_SpeedometerLine[15], 11.000000, -26.000000);
    TextDrawAlignment(TD_SpeedometerLine[15], 1);
    TextDrawColor(TD_SpeedometerLine[15], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[15], 0);
    TextDrawFont(TD_SpeedometerLine[15], 5);
    TextDrawSetProportional(TD_SpeedometerLine[15], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[15], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[15], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[16] = TextDrawCreate(227.597991, 442.878601, "");
    TextDrawTextSize(TD_SpeedometerLine[16], 11.000000, -26.000000);
    TextDrawAlignment(TD_SpeedometerLine[16], 1);
    TextDrawColor(TD_SpeedometerLine[16], 505290495);
    TextDrawBackgroundColor(TD_SpeedometerLine[16], 0);
    TextDrawFont(TD_SpeedometerLine[16], 5);
    TextDrawSetProportional(TD_SpeedometerLine[16], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[16], 19177);
    TextDrawSetPreviewRot(TD_SpeedometerLine[16], 165.000000, 0.000000, 0.000000, 0.172000);

    TD_SpeedometerLine[17] = TextDrawCreate(233.066650, 423.715026, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[17], 176.000305, 13.499998);
    TextDrawAlignment(TD_SpeedometerLine[17], 1);
    TextDrawColor(TD_SpeedometerLine[17], 505290495);

    TextDrawBackgroundColor(TD_SpeedometerLine[17], 255);
    TextDrawFont(TD_SpeedometerLine[17], 4);
    TextDrawSetProportional(TD_SpeedometerLine[17], 0);

    TD_SpeedometerLine[18] = TextDrawCreate(242.832870, 427.130004, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[18], 149.099868, 5.399980);
    TextDrawAlignment(TD_SpeedometerLine[18], 1);
    TextDrawColor(TD_SpeedometerLine[18], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[18], 255);
    TextDrawFont(TD_SpeedometerLine[18], 4);
    TextDrawSetProportional(TD_SpeedometerLine[18], 0);

    TD_SpeedometerLine[19] = TextDrawCreate(244.033325, 428.388946, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[19], 146.899932, 3.000000);
    TextDrawAlignment(TD_SpeedometerLine[19], 1);
    TextDrawColor(TD_SpeedometerLine[19], -1111638529);
    TextDrawBackgroundColor(TD_SpeedometerLine[19], 255);
    TextDrawFont(TD_SpeedometerLine[19], 4);
    TextDrawSetProportional(TD_SpeedometerLine[19], 0);

    TD_SpeedometerLine[20] = TextDrawCreate(243.666625, 427.540893, "//////////");
    TextDrawLetterSize(TD_SpeedometerLine[20], 0.968330, 0.416592);
    TextDrawAlignment(TD_SpeedometerLine[20], 1);
    TextDrawColor(TD_SpeedometerLine[20], 255);
    TextDrawSetShadow(TD_SpeedometerLine[20], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[20], 255);
    TextDrawFont(TD_SpeedometerLine[20], 1);
    TextDrawSetProportional(TD_SpeedometerLine[20], 1);

    TD_SpeedometerLine[21] = TextDrawCreate(235.166702, 424.985626, "o");
    TextDrawLetterSize(TD_SpeedometerLine[21], 0.107230, 0.599816);
    TextDrawTextSize(TD_SpeedometerLine[21], -4.000000, 0.000000);
    TextDrawAlignment(TD_SpeedometerLine[21], 1);
    TextDrawColor(TD_SpeedometerLine[21], -6029057);
    TextDrawSetShadow(TD_SpeedometerLine[21], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[21], 255);
    TextDrawFont(TD_SpeedometerLine[21], 2);
    TextDrawSetProportional(TD_SpeedometerLine[21], 1);

    TD_SpeedometerLine[22] = TextDrawCreate(235.500091, 430.492950, "LD_SPAC:white");
    TextDrawTextSize(TD_SpeedometerLine[22], 2.299998, 3.699995);
    TextDrawAlignment(TD_SpeedometerLine[22], 1);
    TextDrawColor(TD_SpeedometerLine[22], -6029057);
    TextDrawBackgroundColor(TD_SpeedometerLine[22], 255);
    TextDrawFont(TD_SpeedometerLine[22], 4);
    TextDrawSetProportional(TD_SpeedometerLine[22], 0);

    TD_SpeedometerLine[23] = TextDrawCreate(233.400039, 426.030090, "C");
    TextDrawLetterSize(TD_SpeedometerLine[23], 0.066932, 0.915484);
    TextDrawTextSize(TD_SpeedometerLine[23], 0.092600, 1.330299);
    TextDrawAlignment(TD_SpeedometerLine[23], 1);
    TextDrawColor(TD_SpeedometerLine[23], -6029057);
    TextDrawSetShadow(TD_SpeedometerLine[23], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[23], 255);
    TextDrawFont(TD_SpeedometerLine[23], 1);
    TextDrawSetProportional(TD_SpeedometerLine[23], 1);

    TD_SpeedometerLine[24] = TextDrawCreate(311.633422, 429.730072, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[24], 17.000005, 17.000003);
    TextDrawAlignment(TD_SpeedometerLine[24], 1);
    TextDrawColor(TD_SpeedometerLine[24], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[24], 255);
    TextDrawFont(TD_SpeedometerLine[24], 4);
    TextDrawSetProportional(TD_SpeedometerLine[24], 0);

    TD_SpeedometerLine[25] = TextDrawCreate(346.467712, 388.793365, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[25], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[25], 1);
    TextDrawColor(TD_SpeedometerLine[25], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[25], 255);
    TextDrawFont(TD_SpeedometerLine[25], 4);
    TextDrawSetProportional(TD_SpeedometerLine[25], 0);

    TD_SpeedometerLine[26] = TextDrawCreate(303.200195, 391.500732, "");
    TextDrawTextSize(TD_SpeedometerLine[26], 32.399997, 35.000000);
    TextDrawAlignment(TD_SpeedometerLine[26], 1);
    TextDrawColor(TD_SpeedometerLine[26], 67);
    TextDrawBackgroundColor(TD_SpeedometerLine[26], 0);
    TextDrawFont(TD_SpeedometerLine[26], 5);
    TextDrawSetProportional(TD_SpeedometerLine[26], 0);
    TextDrawSetPreviewModel(TD_SpeedometerLine[26], 2729);
    TextDrawSetPreviewRot(TD_SpeedometerLine[26], 151.000000, 0.000000, 0.000000, 0.698598);

    TD_SpeedometerLine[27] = TextDrawCreate(319.366760, 408.322387, "km/h");
    TextDrawLetterSize(TD_SpeedometerLine[27], 0.163662, 0.824293);
    TextDrawAlignment(TD_SpeedometerLine[27], 2);
    TextDrawColor(TD_SpeedometerLine[27], 977026047);
    TextDrawSetShadow(TD_SpeedometerLine[27], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[27], 255);
    TextDrawFont(TD_SpeedometerLine[27], 1);
    TextDrawSetProportional(TD_SpeedometerLine[27], 1);

    TD_SpeedometerLine[28] = TextDrawCreate(257.000000, 414.185455, "LIMIT");
    TextDrawLetterSize(TD_SpeedometerLine[28], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[28], 2);
    TextDrawColor(TD_SpeedometerLine[28], 255);
    TextDrawSetShadow(TD_SpeedometerLine[28], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[28], 255);
    TextDrawFont(TD_SpeedometerLine[28], 1);
    TextDrawSetProportional(TD_SpeedometerLine[28], 1);

    TD_SpeedometerLine[29] = TextDrawCreate(281.000244, 414.185455, "ENGINE");
    TextDrawLetterSize(TD_SpeedometerLine[29], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[29], 2);
    TextDrawColor(TD_SpeedometerLine[29], 255);
    TextDrawSetShadow(TD_SpeedometerLine[29], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[29], 255);
    TextDrawFont(TD_SpeedometerLine[29], 1);
    TextDrawSetProportional(TD_SpeedometerLine[29], 1);

    TD_SpeedometerLine[30] = TextDrawCreate(360.201049, 414.185455, "LIGHT");
    TextDrawLetterSize(TD_SpeedometerLine[30], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[30], 2);
    TextDrawColor(TD_SpeedometerLine[30], 255);
    TextDrawSetShadow(TD_SpeedometerLine[30], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[30], 255);
    TextDrawFont(TD_SpeedometerLine[30], 1);
    TextDrawSetProportional(TD_SpeedometerLine[30], 1);

    TD_SpeedometerLine[31] = TextDrawCreate(385.401306, 414.185455, "DOORS");
    TextDrawLetterSize(TD_SpeedometerLine[31], 0.194000, 0.869925);
    TextDrawAlignment(TD_SpeedometerLine[31], 2);
    TextDrawColor(TD_SpeedometerLine[31], 255);
    TextDrawSetShadow(TD_SpeedometerLine[31], 0);
    TextDrawBackgroundColor(TD_SpeedometerLine[31], 255);
    TextDrawFont(TD_SpeedometerLine[31], 1);
    TextDrawSetProportional(TD_SpeedometerLine[31], 1);

    TD_SpeedometerLine[32] = TextDrawCreate(371.066711, 388.793365, "LD_BEAT:сhit");
    TextDrawTextSize(TD_SpeedometerLine[32], 28.600006, 30.200004);
    TextDrawAlignment(TD_SpeedometerLine[32], 1);
    TextDrawColor(TD_SpeedometerLine[32], 336859903);
    TextDrawBackgroundColor(TD_SpeedometerLine[32], 255);
    TextDrawFont(TD_SpeedometerLine[32], 4);
    TextDrawSetProportional(TD_SpeedometerLine[32], 0);
    /*
    //logo donate
    TD_Logo_Donate[0] = TextDrawCreate(7.3015, 417.1632, "LD_SPAC:white");
    TextDrawTextSize(TD_Logo_Donate[0], 54.0000, 24.0000);
    TextDrawAlignment(TD_Logo_Donate[0], 1);
    TextDrawColor(TD_Logo_Donate[0], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[0], 255);
    TextDrawFont(TD_Logo_Donate[0], 4);
    TextDrawSetProportional(TD_Logo_Donate[0], 0);
    TextDrawSetShadow(TD_Logo_Donate[0], 0);

    TD_Logo_Donate[1] = TextDrawCreate(4.4331, 415.9187, "LD_BEAT:chit");
    TextDrawTextSize(TD_Logo_Donate[1], 7.0000, 8.0000);
    TextDrawAlignment(TD_Logo_Donate[1], 1);
    TextDrawColor(TD_Logo_Donate[1], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[1], 255);
    TextDrawFont(TD_Logo_Donate[1], 4);
    TextDrawSetProportional(TD_Logo_Donate[1], 0);
    TextDrawSetShadow(TD_Logo_Donate[1], 0);

    TD_Logo_Donate[2] = TextDrawCreate(4.3331, 434.4523, "LD_BEAT:chit");
    TextDrawTextSize(TD_Logo_Donate[2], 7.0000, 8.0000);
    TextDrawAlignment(TD_Logo_Donate[2], 1);
    TextDrawColor(TD_Logo_Donate[2], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[2], 255);
    TextDrawFont(TD_Logo_Donate[2], 4);
    TextDrawSetProportional(TD_Logo_Donate[2], 0);
    TextDrawSetShadow(TD_Logo_Donate[2], 0);

    TD_Logo_Donate[3] = TextDrawCreate(5.6350, 420.4816, "LD_SPAC:white");
    TextDrawTextSize(TD_Logo_Donate[3], 54.0000, 19.0000);
    TextDrawAlignment(TD_Logo_Donate[3], 1);
    TextDrawColor(TD_Logo_Donate[3], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[3], 255);
    TextDrawFont(TD_Logo_Donate[3], 4);
    TextDrawSetProportional(TD_Logo_Donate[3], 0);
    TextDrawSetShadow(TD_Logo_Donate[3], 0);

    TD_Logo_Donate[4] = TextDrawCreate(30.6998, 423.5408, "DONATE");
    TextDrawLetterSize(TD_Logo_Donate[4], 0.2462, 1.1850);
    TextDrawAlignment(TD_Logo_Donate[4], 2);
    TextDrawColor(TD_Logo_Donate[4], -1);
    TextDrawBackgroundColor(TD_Logo_Donate[4], 255);
    TextDrawFont(TD_Logo_Donate[4], 1);
    TextDrawSetProportional(TD_Logo_Donate[4], 1);
    TextDrawSetShadow(TD_Logo_Donate[4], 0);

    TD_Logo_Donate[5] = TextDrawCreate(67.0332, 423.5408, "X4");
    TextDrawLetterSize(TD_Logo_Donate[5], 0.2462, 1.1850);
    TextDrawAlignment(TD_Logo_Donate[5], 2);
    TextDrawColor(TD_Logo_Donate[5], -1);
    TextDrawBackgroundColor(TD_Logo_Donate[5], 255);
    TextDrawFont(TD_Logo_Donate[5], 1);
    TextDrawSetProportional(TD_Logo_Donate[5], 1);
    TextDrawSetShadow(TD_Logo_Donate[5], 0);

    TD_Logo_Donate[6] = TextDrawCreate(27.6665, 404.1893, "");
    TextDrawTextSize(TD_Logo_Donate[6], 78.0000, 49.5499);
    TextDrawAlignment(TD_Logo_Donate[6], 1);
    TextDrawColor(TD_Logo_Donate[6], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[6], 0x00000000);
    TextDrawFont(TD_Logo_Donate[6], 5);
    TextDrawSetProportional(TD_Logo_Donate[6], 0);
    TextDrawSetShadow(TD_Logo_Donate[6], 0);
    TextDrawSetPreviewModel(TD_Logo_Donate[6], 3090);
    TextDrawSetPreviewRot(TD_Logo_Donate[6], 0.0000, 0.0000, 0.0000, 1.0000);

    TD_Logo_Donate[7] = TextDrawCreate(106.1328, 454.4114, "");
    TextDrawTextSize(TD_Logo_Donate[7], -78.0000, -50.0000);
    TextDrawAlignment(TD_Logo_Donate[7], 1);
    TextDrawColor(TD_Logo_Donate[7], -5963521);
    TextDrawBackgroundColor(TD_Logo_Donate[7], 0x00000000);
    TextDrawFont(TD_Logo_Donate[7], 5);
    TextDrawSetProportional(TD_Logo_Donate[7], 0);
    TextDrawSetShadow(TD_Logo_Donate[7], 0);
    TextDrawSetPreviewModel(TD_Logo_Donate[7], 3090);
    TextDrawSetPreviewRot(TD_Logo_Donate[7], 0.0000, 0.0000, 0.0000, 1.0000);

    TD_Logo_Donate[8] = TextDrawCreate(57.4665, 417.1632, "LD_SPAC:white");
    TextDrawTextSize(TD_Logo_Donate[8], 3.0000, 24.0699);
    TextDrawAlignment(TD_Logo_Donate[8], 1);
    TextDrawColor(TD_Logo_Donate[8], -5963521);
    TextDrawBackgroundColor(TD_Logo_Donate[8], 255);
    TextDrawFont(TD_Logo_Donate[8], 4);
    TextDrawSetProportional(TD_Logo_Donate[8], 0);
    TextDrawSetShadow(TD_Logo_Donate[8], 0);

    TD_Logo_Donate[9] = TextDrawCreate(75.4664, 419.6521, "LD_SPAC:white");
    TextDrawTextSize(TD_Logo_Donate[9], 3.0000, 18.0000);
    TextDrawAlignment(TD_Logo_Donate[9], 1);
    TextDrawColor(TD_Logo_Donate[9], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[9], 255);
    TextDrawFont(TD_Logo_Donate[9], 4);
    TextDrawSetProportional(TD_Logo_Donate[9], 0);
    TextDrawSetShadow(TD_Logo_Donate[9], 0);

    TD_Logo_Donate[10] = TextDrawCreate(72.6997, 415.8187, "LD_BEAT:chit");
    TextDrawTextSize(TD_Logo_Donate[10], 7.0000, 8.0000);
    TextDrawAlignment(TD_Logo_Donate[10], 1);
    TextDrawColor(TD_Logo_Donate[10], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[10], 255);
    TextDrawFont(TD_Logo_Donate[10], 4);
    TextDrawSetProportional(TD_Logo_Donate[10], 0);
    TextDrawSetShadow(TD_Logo_Donate[10], 0);

    TD_Logo_Donate[11] = TextDrawCreate(72.6995, 434.4671, "LD_BEAT:chit");
    TextDrawTextSize(TD_Logo_Donate[11], 7.0000, 8.0000);
    TextDrawAlignment(TD_Logo_Donate[11], 1);
    TextDrawColor(TD_Logo_Donate[11], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[11], 255);
    TextDrawFont(TD_Logo_Donate[11], 4);
    TextDrawSetProportional(TD_Logo_Donate[11], 0);
    TextDrawSetShadow(TD_Logo_Donate[11], 0);

    TD_Logo_Donate[12] = TextDrawCreate(54.0998, 415.9187, "LD_BEAT:chit");
    TextDrawTextSize(TD_Logo_Donate[12], 7.0000, 8.0000);
    TextDrawAlignment(TD_Logo_Donate[12], 1);
    TextDrawColor(TD_Logo_Donate[12], -5963521);
    TextDrawBackgroundColor(TD_Logo_Donate[12], 255);
    TextDrawFont(TD_Logo_Donate[12], 4);
    TextDrawSetProportional(TD_Logo_Donate[12], 0);
    TextDrawSetShadow(TD_Logo_Donate[12], 0);

    TD_Logo_Donate[13] = TextDrawCreate(53.9999, 434.5523, "LD_BEAT:chit");
    TextDrawTextSize(TD_Logo_Donate[13], 7.0000, 8.0000);
    TextDrawAlignment(TD_Logo_Donate[13], 1);
    TextDrawColor(TD_Logo_Donate[13], -5963521);
    TextDrawBackgroundColor(TD_Logo_Donate[13], 255);
    TextDrawFont(TD_Logo_Donate[13], 4);
    TextDrawSetProportional(TD_Logo_Donate[13], 0);
    TextDrawSetShadow(TD_Logo_Donate[13], 0);

    TD_Logo_Donate[14] = TextDrawCreate(55.2332, 419.6521, "LD_SPAC:white");
    TextDrawTextSize(TD_Logo_Donate[14], 3.0000, 19.0000);
    TextDrawAlignment(TD_Logo_Donate[14], 1);
    TextDrawColor(TD_Logo_Donate[14], -5963521);
    TextDrawBackgroundColor(TD_Logo_Donate[14], 255);
    TextDrawFont(TD_Logo_Donate[14], 4);
    TextDrawSetProportional(TD_Logo_Donate[14], 0);
    TextDrawSetShadow(TD_Logo_Donate[14], 0);

    TD_Logo_Donate[15] = TextDrawCreate(73.1331, 417.1632, "LD_SPAC:white");
    TextDrawTextSize(TD_Logo_Donate[15], 3.0000, 24.0799);
    TextDrawAlignment(TD_Logo_Donate[15], 1);
    TextDrawColor(TD_Logo_Donate[15], -7601921);
    TextDrawBackgroundColor(TD_Logo_Donate[15], 255);
    TextDrawFont(TD_Logo_Donate[15], 4);
    TextDrawSetProportional(TD_Logo_Donate[15], 0);
    TextDrawSetShadow(TD_Logo_Donate[15], 0);
    */
    //logo td
    TD_Logo_Default[0] = TextDrawCreate(553.632995, -3.144500, "");
    TextDrawLetterSize(TD_Logo_Default[0], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[0], 15.000000, 20.100000);
    TextDrawAlignment(TD_Logo_Default[0], 1);
    TextDrawColor(TD_Logo_Default[0], -5963521);
    TextDrawSetShadow(TD_Logo_Default[0], 0);
    TextDrawSetOutline(TD_Logo_Default[0], 0);
    TextDrawBackgroundColor(TD_Logo_Default[0], 0);
    TextDrawFont(TD_Logo_Default[0], 5);
    TextDrawSetProportional(TD_Logo_Default[0], 0);
    TextDrawSetShadow(TD_Logo_Default[0], 0);
    TextDrawSetPreviewModel(TD_Logo_Default[0], 19310);
    TextDrawSetPreviewRot(TD_Logo_Default[0], 0.000000, 0.000000, 86.000000, 0.875800);

    TD_Logo_Default[1] = TextDrawCreate(557.333129, 17.022300, "");
    TextDrawLetterSize(TD_Logo_Default[1], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[1], 14.000000, -19.000000);
    TextDrawAlignment(TD_Logo_Default[1], 1);
    TextDrawColor(TD_Logo_Default[1], -5963521);
    TextDrawSetShadow(TD_Logo_Default[1], 0);
    TextDrawSetOutline(TD_Logo_Default[1], 0);
    TextDrawBackgroundColor(TD_Logo_Default[1], 0);
    TextDrawFont(TD_Logo_Default[1], 5);
    TextDrawSetProportional(TD_Logo_Default[1], 0);
    TextDrawSetShadow(TD_Logo_Default[1], 0);
    TextDrawSetPreviewModel(TD_Logo_Default[1], 19310);
    TextDrawSetPreviewRot(TD_Logo_Default[1], 0.000000, 0.000000, 86.000000, 0.875800);

    TD_Logo_Default[2] = TextDrawCreate(555.666320, 5.881299, "LD_SPAC:white");
    TextDrawLetterSize(TD_Logo_Default[2], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[2], 11.000000, 3.519900);
    TextDrawAlignment(TD_Logo_Default[2], 1);
    TextDrawColor(TD_Logo_Default[2], -5963521);
    TextDrawSetShadow(TD_Logo_Default[2], 0);
    TextDrawSetOutline(TD_Logo_Default[2], 0);
    TextDrawBackgroundColor(TD_Logo_Default[2], 255);
    TextDrawFont(TD_Logo_Default[2], 4);
    TextDrawSetProportional(TD_Logo_Default[2], 0);
    TextDrawSetShadow(TD_Logo_Default[2], 0);

    TD_Logo_Default[3] = TextDrawCreate(558.666320, 5.036900, "LD_SPAC:white");
    TextDrawLetterSize(TD_Logo_Default[3], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[3], 10.489800, 3.519900);
    TextDrawAlignment(TD_Logo_Default[3], 1);
    TextDrawColor(TD_Logo_Default[3], -5963521);
    TextDrawSetShadow(TD_Logo_Default[3], 0);
    TextDrawSetOutline(TD_Logo_Default[3], 0);
    TextDrawBackgroundColor(TD_Logo_Default[3], 255);
    TextDrawFont(TD_Logo_Default[3], 4);
    TextDrawSetProportional(TD_Logo_Default[3], 0);
    TextDrawSetShadow(TD_Logo_Default[3], 0);

    TD_Logo_Default[4] = TextDrawCreate(555.299682, 24.489000, "");
    TextDrawLetterSize(TD_Logo_Default[4], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[4], 12.000000, -19.889900);
    TextDrawAlignment(TD_Logo_Default[4], 1);
    TextDrawColor(TD_Logo_Default[4], -5963521);
    TextDrawSetShadow(TD_Logo_Default[4], 0);
    TextDrawSetOutline(TD_Logo_Default[4], 0);
    TextDrawBackgroundColor(TD_Logo_Default[4], 0);
    TextDrawFont(TD_Logo_Default[4], 5);
    TextDrawSetProportional(TD_Logo_Default[4], 0);
    TextDrawSetShadow(TD_Logo_Default[4], 0);
    TextDrawSetPreviewModel(TD_Logo_Default[4], 19310);
    TextDrawSetPreviewRot(TD_Logo_Default[4], 0.000000, 0.000000, 86.000000, 0.875800);

    TD_Logo_Default[5] = TextDrawCreate(553.432983, 3.533400, "");
    TextDrawLetterSize(TD_Logo_Default[5], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[5], 12.000000, 21.039899);
    TextDrawAlignment(TD_Logo_Default[5], 1);
    TextDrawColor(TD_Logo_Default[5], -5963521);
    TextDrawSetShadow(TD_Logo_Default[5], 0);
    TextDrawSetOutline(TD_Logo_Default[5], 0);
    TextDrawBackgroundColor(TD_Logo_Default[5], 0);
    TextDrawFont(TD_Logo_Default[5], 5);
    TextDrawSetProportional(TD_Logo_Default[5], 0);
    TextDrawSetShadow(TD_Logo_Default[5], 0);
    TextDrawSetPreviewModel(TD_Logo_Default[5], 19310);
    TextDrawSetPreviewRot(TD_Logo_Default[5], 0.000000, 0.000000, 86.000000, 0.875800);

    TD_Logo_Default[6] = TextDrawCreate(555.333007, 13.333200, "LD_SPAC:white");
    TextDrawLetterSize(TD_Logo_Default[6], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[6], 9.000000, 2.979899);
    TextDrawAlignment(TD_Logo_Default[6], 1);
    TextDrawColor(TD_Logo_Default[6], -5963521);
    TextDrawSetShadow(TD_Logo_Default[6], 0);
    TextDrawSetOutline(TD_Logo_Default[6], 0);
    TextDrawBackgroundColor(TD_Logo_Default[6], 255);
    TextDrawFont(TD_Logo_Default[6], 4);
    TextDrawSetProportional(TD_Logo_Default[6], 0);
    TextDrawSetShadow(TD_Logo_Default[6], 0);

    TD_Logo_Default[7] = TextDrawCreate(558.199707, 12.088800, "LD_SPAC:white");
    TextDrawLetterSize(TD_Logo_Default[7], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[7], 7.000000, 3.000000);
    TextDrawAlignment(TD_Logo_Default[7], 1);
    TextDrawColor(TD_Logo_Default[7], -5963521);
    TextDrawSetShadow(TD_Logo_Default[7], 0);
    TextDrawSetOutline(TD_Logo_Default[7], 0);
    TextDrawBackgroundColor(TD_Logo_Default[7], 255);
    TextDrawFont(TD_Logo_Default[7], 4);
    TextDrawSetProportional(TD_Logo_Default[7], 0);
    TextDrawSetShadow(TD_Logo_Default[7], 0);

    TD_Logo_Default[8] = TextDrawCreate(554.833007, 30.296300, "");
    TextDrawLetterSize(TD_Logo_Default[8], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[8], 8.000000, -18.000000);
    TextDrawAlignment(TD_Logo_Default[8], 1);
    TextDrawColor(TD_Logo_Default[8], -5963521);
    TextDrawSetShadow(TD_Logo_Default[8], 0);
    TextDrawSetOutline(TD_Logo_Default[8], 0);
    TextDrawBackgroundColor(TD_Logo_Default[8], 0);
    TextDrawFont(TD_Logo_Default[8], 5);
    TextDrawSetProportional(TD_Logo_Default[8], 0);
    TextDrawSetShadow(TD_Logo_Default[8], 0);
    TextDrawSetPreviewModel(TD_Logo_Default[8], 19310);
    TextDrawSetPreviewRot(TD_Logo_Default[8], 0.000000, 0.000000, 86.000000, 0.875800);

    TD_Logo_Default[9] = TextDrawCreate(553.699707, 11.114899, "");
    TextDrawLetterSize(TD_Logo_Default[9], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[9], 7.489900, 19.579900);
    TextDrawAlignment(TD_Logo_Default[9], 1);
    TextDrawColor(TD_Logo_Default[9], -5963521);
    TextDrawSetShadow(TD_Logo_Default[9], 0);
    TextDrawSetOutline(TD_Logo_Default[9], 0);
    TextDrawBackgroundColor(TD_Logo_Default[9], 0);
    TextDrawFont(TD_Logo_Default[9], 5);
    TextDrawSetProportional(TD_Logo_Default[9], 0);
    TextDrawSetShadow(TD_Logo_Default[9], 0);
    TextDrawSetPreviewModel(TD_Logo_Default[9], 19310);
    TextDrawSetPreviewRot(TD_Logo_Default[9], 0.000000, 0.000000, 86.000000, 0.875800);

    TD_Logo_Default[10] = TextDrawCreate(554.533020, 19.970300, "LD_SPAC:white");
    TextDrawLetterSize(TD_Logo_Default[10], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[10], 6.189899, 3.000000);
    TextDrawAlignment(TD_Logo_Default[10], 1);
    TextDrawColor(TD_Logo_Default[10], -5963521);
    TextDrawSetShadow(TD_Logo_Default[10], 0);
    TextDrawSetOutline(TD_Logo_Default[10], 0);
    TextDrawBackgroundColor(TD_Logo_Default[10], 255);
    TextDrawFont(TD_Logo_Default[10], 4);
    TextDrawSetProportional(TD_Logo_Default[10], 0);
    TextDrawSetShadow(TD_Logo_Default[10], 0);

    TD_Logo_Default[11] = TextDrawCreate(555.333007, 19.070199, "LD_SPAC:white");
    TextDrawLetterSize(TD_Logo_Default[11], 0.000000, 0.000000);
    TextDrawTextSize(TD_Logo_Default[11], 6.189899, 3.000000);
    TextDrawAlignment(TD_Logo_Default[11], 1);
    TextDrawColor(TD_Logo_Default[11], -5963521);
    TextDrawSetShadow(TD_Logo_Default[11], 0);
    TextDrawSetOutline(TD_Logo_Default[11], 0);
    TextDrawBackgroundColor(TD_Logo_Default[11], 255);
    TextDrawFont(TD_Logo_Default[11], 4);
    TextDrawSetProportional(TD_Logo_Default[11], 0);
    TextDrawSetShadow(TD_Logo_Default[11], 0);

    TD_Logo_Default[12] = TextDrawCreate(572.766479, 4.877799, "FLIN");
    TextDrawLetterSize(TD_Logo_Default[12], 0.409299, 1.521100);
    TextDrawAlignment(TD_Logo_Default[12], 1);
    TextDrawColor(TD_Logo_Default[12], -1);
    TextDrawSetShadow(TD_Logo_Default[12], 0);
    TextDrawSetOutline(TD_Logo_Default[12], 0);
    TextDrawBackgroundColor(TD_Logo_Default[12], 255);
    TextDrawFont(TD_Logo_Default[12], 1);
    TextDrawSetProportional(TD_Logo_Default[12], 1);
    TextDrawSetShadow(TD_Logo_Default[12], 0);

    TD_Logo_Default[13] = TextDrawCreate(572.799804, 15.248200, "MOBILE");
    TextDrawLetterSize(TD_Logo_Default[13], 0.143600, 0.923799);
    TextDrawAlignment(TD_Logo_Default[13], 1);
    TextDrawColor(TD_Logo_Default[13], -1);
    TextDrawSetShadow(TD_Logo_Default[13], 0);
    TextDrawSetOutline(TD_Logo_Default[13], 0);
    TextDrawBackgroundColor(TD_Logo_Default[13], 255);
    TextDrawFont(TD_Logo_Default[13], 2);
    TextDrawSetProportional(TD_Logo_Default[13], 1);
    TextDrawSetShadow(TD_Logo_Default[13], 0);
    TD_Logo_Default[14] = TextDrawCreate(567.833312, 14.418499, "2");
    TextDrawLetterSize(TD_Logo_Default[14], 0.234300, 1.168499);
    TextDrawAlignment(TD_Logo_Default[14], 2);
    TextDrawColor(TD_Logo_Default[14], -5963521);
    TextDrawSetShadow(TD_Logo_Default[14], 0);
    TextDrawSetOutline(TD_Logo_Default[14], 0);
    TextDrawBackgroundColor(TD_Logo_Default[14], 255);
    TextDrawFont(TD_Logo_Default[14], 1);
    TextDrawSetProportional(TD_Logo_Default[14], 1);
    TextDrawSetShadow(TD_Logo_Default[14], 0);
    //time td
    TD_Logo_Default[15] = TextDrawCreate(635.4169, 431.6295, "_");
    TextDrawLetterSize(TD_Logo_Default[15], 0.3383, 1.1903);
    TextDrawAlignment(TD_Logo_Default[15], 3);
    TextDrawColor(TD_Logo_Default[15], -5963521);
    TextDrawSetShadow(TD_Logo_Default[15], 0);
    TextDrawSetOutline(TD_Logo_Default[15], 1);
    TextDrawBackgroundColor(TD_Logo_Default[15], 15);
    TextDrawFont(TD_Logo_Default[15], 2);
    TextDrawSetProportional(TD_Logo_Default[15], 1);

    TD_Actions[0] = TextDrawCreate(235.7998, 311.3019, "flin_txd:flin_stock"); // бг акции
    TextDrawTextSize(TD_Actions[0], 164.0000, 200.0000);
    TextDrawAlignment(TD_Actions[0], 1);
    TextDrawColor(TD_Actions[0], -1);
    TextDrawBackgroundColor(TD_Actions[0], 255);
    TextDrawFont(TD_Actions[0], 4);
    TextDrawSetProportional(TD_Actions[0], 0);
    TextDrawSetShadow(TD_Actions[0], 0);

    TD_Actions[1] = TextDrawCreate(317.9998, 413.0043, "Ak†Ьђ~n~x2_ИМ_Ь_x2_ГoЃa¶"); // текст акции
    TextDrawLetterSize(TD_Actions[1], 0.1776, 1.0922);
    TextDrawAlignment(TD_Actions[1], 2);
    TextDrawColor(TD_Actions[1], -1);
    TextDrawBackgroundColor(TD_Actions[1], 255);
    TextDrawFont(TD_Actions[1], 2);
    TextDrawSetProportional(TD_Actions[1], 1);
    TextDrawSetShadow(TD_Actions[1], 0);
}

IsTDVisible(playerid)
{
    if(p_info[playerid][exchangePartner] != INVALID_PLAYER_ID) return SendError(playerid, "” ¬ас начат трейд, возможность не доступна.");
    if(p_temp[playerid][TextDrawCaptcha]) return SendError(playerid, "” ¬ас открыта капча, закройте ее.");
    if(p_temp[playerid][TextDrawInventory]) return SendError(playerid, "” ¬ас открыт инвентарь, закройте его.");
    if(p_temp[playerid][TextDrawCraft]) return SendError(playerid, "” ¬ас открыт крафт, закройте его.");
    if(p_temp[playerid][TextDrawBattlePass]) return SendError(playerid, "” ¬ас открыт Battle Pass, закройте его.");
    if(p_temp[playerid][TextDrawDaily]) return SendError(playerid, "” ¬ас открыты ежедневные награды, закройте их.");
    if(p_temp[playerid][TextDrawMarket]) return SendError(playerid, "” ¬ас открыт меню магазина, закройте его.");
    if(p_temp[playerid][TextDrawCase]) return SendError(playerid, "” ¬ас открыто открытие кейсов, закройте его.");
    if(p_temp[playerid][TextDrawPhone]) return SendError(playerid, "” ¬ас открыт телефон, закройте его.");
    if(p_temp[playerid][TextDrawCarFactory]) return SendError(playerid, "” ¬ас открыта информаци€ на автомобильном заводе, закройте еЄ.");
    if(p_temp[playerid][TextDrawRoulette]) return SendError(playerid, "” ¬ас уже открыта рулетка, закройте еЄ.");
    if(p_temp[playerid][TextDrawRobberyRobbing]) return SendError(playerid, "” ¬ас открыта мини-игра ограблени€ дома, закройте еЄ.");
    if(p_temp[playerid][TextDrawRadio]) return SendError(playerid, "” ¬ас открыт проигрыватель, закройте его.");
    if(p_temp[playerid][TextDrawPlayerMenu]) return SendError(playerid, "” ¬ас открыто уже меню игрока, закройте его.");
    if(p_temp[playerid][TextDrawListUse]) return SendError(playerid, "” ¬ас уже открыто меню выбора, закройте его.");
    if(p_temp[playerid][TextDrawServiceTune]) return SendError(playerid, "” ¬ас уже открыто меню —“ќ, закройте его.");
    if(IsPlayerUseMDC(playerid)) return SendError(playerid, "” ¬ас уже открыто MDC, закройте его.");
    if(p_temp[playerid][TextDrawEditor]) return SendError(playerid, "” ¬ас уже открыт редактор, закройте его.");
    if(p_temp[playerid][TextDrawFarm]) return SendError(playerid, "” ¬ас уже открыта мини-игра на ферме, закройте еЄ.");
    if(p_temp[playerid][market_arend] != -1) return SendError(playerid, "Ќе доступно в палатке.");

    if(p_info[playerid][durak_table]) return SendError(playerid, "Ќе ¬ас уже открыта игра дурак.");
    if(p_temp[playerid][SlotMachineTextDraw]) return SendError(playerid, "¬ы играете в игральные слоты, закройте их.");
    if(blackjackPlayerData[playerid][BJ_CurrentTableID] != -1) return SendError(playerid, "¬ы играете в BlackJack, закончите игру.");

    return -1;
}


Logotype_SetServer()
{
    new str[24];
    if(SRV_ID == 0) str = "";
    else format(str, sizeof(str), "%d", SRV_ID);
    TextDrawSetString(TD_Logo_Default[14], str);

    TD_Logo_One[0] = TextDrawCreate(6.1999, 383.4797, SRV_ID == 2 ? "flin_txd:flin_logotype_2" : "flin_txd:flin_logotype_1"); // лого без акции
    TextDrawTextSize(TD_Logo_One[0], 85.0000, 92.0000);
    TextDrawAlignment(TD_Logo_One[0], 1);
    TextDrawColor(TD_Logo_One[0], -1);
    TextDrawBackgroundColor(TD_Logo_One[0], 255);
    TextDrawFont(TD_Logo_One[0], 4);
    TextDrawSetProportional(TD_Logo_One[0], 0);
    TextDrawSetShadow(TD_Logo_One[0], 0);

    TD_Logo_Two[0] = TextDrawCreate(6.1999, 384.9733, SRV_ID == 2 ? "flin_txd:flin_serv_logo2" : "flin_txd:flin_serv_logo1"); // 2 тип лого
    TextDrawTextSize(TD_Logo_Two[0], 79.0000, 89.0000);
    TextDrawAlignment(TD_Logo_Two[0], 1);
    TextDrawColor(TD_Logo_Two[0], -1);
    TextDrawBackgroundColor(TD_Logo_Two[0], 255);
    TextDrawFont(TD_Logo_Two[0], 4);
    TextDrawSetProportional(TD_Logo_Two[0], 0);
    TextDrawSetShadow(TD_Logo_Two[0], 0);
}

Logotype_Show(playerid = INVALID_PLAYER_ID)
{
    if(playerid == INVALID_PLAYER_ID)
    {
        foreach(new i: Player)
        {
            for(new idx = 0; idx < 16; idx++)
            {
                if(p_info[i][p_settings][LOGO_ID] != 0)
                {
                    //TextDrawHideForPlayer(i, TD_Logo_Donate[idx]);
                    if(i < 15) TextDrawHideForPlayer(i, TD_Logo_Default[idx]);
                }
                else
                {
                    //TextDrawShowForPlayer(i, TD_Logo_Donate[idx]);
                    if(i < 15) TextDrawShowForPlayer(i, TD_Logo_Default[idx]);
                }

                if(idx < 2)
                {
                    if(p_info[i][p_settings][LOGO_ID] != 2) TextDrawHideForPlayer(i, TD_Logo_Two[idx]);
                    else TextDrawShowForPlayer(i, TD_Logo_Two[idx]);
                }

                if(idx < 3)
                {
                    if(p_info[i][p_settings][LOGO_ID] != 1) TextDrawHideForPlayer(i, TD_Logo_One[idx]);
                    else
                    {
                        TextDrawShowForPlayer(i, TD_Logo_One[idx]);
                        if(idx == 2 && ServerInfo[DonationMultiplier] < 2) TextDrawHideForPlayer(i, TD_Logo_One[2]);
                    }
                }
            }
        }
    }
    else
    {
        for(new idx = 0; idx < 16; idx++)
        {
            if(p_info[playerid][p_settings][LOGO_ID] != 0)
            {
                //TextDrawHideForPlayer(playerid, TD_Logo_Donate[idx]);
                if(idx < 15) TextDrawHideForPlayer(playerid, TD_Logo_Default[idx]);
            }
            else
            {
                //TextDrawShowForPlayer(playerid, TD_Logo_Donate[idx]);
                if(idx < 15) TextDrawShowForPlayer(playerid, TD_Logo_Default[idx]);
            }

            if(idx < 2)
            {
                if(p_info[playerid][p_settings][LOGO_ID] != 2) TextDrawHideForPlayer(playerid, TD_Logo_Two[idx]);
                else TextDrawShowForPlayer(playerid, TD_Logo_Two[idx]);
            }

            if(idx < 3)
            {
                if(p_info[playerid][p_settings][LOGO_ID] != 1) TextDrawHideForPlayer(playerid, TD_Logo_One[idx]);
                else
                {
                    TextDrawShowForPlayer(playerid, TD_Logo_One[idx]);
                    if(idx == 2 && ServerInfo[DonationMultiplier] < 2) TextDrawHideForPlayer(playerid, TD_Logo_One[2]);
                }
            }
        }
    }
}

Logotype_SetOnline()
{
    new str[32];
    f(str, "%d", count_player);
    TextDrawSetString(TD_Logo_Two[1], "_");//str);
    TextDrawSetString(TD_Logo_One[1], "_");//str);
}

Logotype_Update()
{
    TextDrawDestroy(TD_Logo_Two[0]);
    TextDrawDestroy(TD_Logo_One[0]);
    TextDrawDestroy(TD_Logo_One[1]);
    TextDrawDestroy(TD_Logo_One[2]);

    new str[64];
    /*
    #if OFF_HUD_PC == 0
    format(str, sizeof(str), "X%d", ServerInfo[DonationMultiplier]);
    TextDrawSetString(TD_Logo_Donate[5], str);
    #endif
    */

    //LOGO: 1
    if(ServerInfo[DonationMultiplier] > 1) TD_Logo_One[0] = TextDrawCreate(35.4000, 383.4797, SRV_ID == 2 ? "flin_txd:flin_logotype_2" : "flin_txd:flin_logotype_1"); // лого c акци€ми
    else TD_Logo_One[0] = TextDrawCreate(6.1999, 383.4797, SRV_ID == 2 ? "flin_txd:flin_logotype_2" : "flin_txd:flin_logotype_1"); // лого без акции
    TextDrawTextSize(TD_Logo_One[0], 85.0000, 92.0000);
    TextDrawAlignment(TD_Logo_One[0], 1);
    TextDrawColor(TD_Logo_One[0], -1);
    TextDrawBackgroundColor(TD_Logo_One[0], 255);
    TextDrawFont(TD_Logo_One[0], 4);
    TextDrawSetProportional(TD_Logo_One[0], 0);
    TextDrawSetShadow(TD_Logo_One[0], 0);

    format(str, sizeof(str), "%d", count_player);

    if(ServerInfo[DonationMultiplier] > 1) TD_Logo_One[1] = TextDrawCreate(106.8000, 423.9555, str); // кол-во игроков с акцией
    else TD_Logo_One[1] = TextDrawCreate(76.7996, 423.9555, str);

    TextDrawLetterSize(TD_Logo_One[1], 0.1568, 0.9976);
    TextDrawAlignment(TD_Logo_One[1], 1);
    TextDrawColor(TD_Logo_One[1], -1);
    TextDrawBackgroundColor(TD_Logo_One[1], 255);
    TextDrawFont(TD_Logo_One[1], 2);
    TextDrawSetProportional(TD_Logo_One[1], 1);
    TextDrawSetShadow(TD_Logo_One[1], 0);

    if(ServerInfo[DonationMultiplier] >= 3) TD_Logo_One[2] = TextDrawCreate(5.4000, 415.8355, "flin_txd:flin_logotype_x3"); // иконка х3
    else TD_Logo_One[2] = TextDrawCreate(5.4000, 415.8355, "flin_txd:flin_logotype_x2"); // иконка х2
    TextDrawTextSize(TD_Logo_One[2], 25.0000, 27.0000);
    TextDrawAlignment(TD_Logo_One[2], 1);
    TextDrawColor(TD_Logo_One[2], -1);
    TextDrawBackgroundColor(TD_Logo_One[2], 255);
    TextDrawFont(TD_Logo_One[2], 4);
    TextDrawSetProportional(TD_Logo_One[2], 0);
    TextDrawSetShadow(TD_Logo_One[2], 0);

    //LOGO 2:
    f(str, "flin_txd:flin_serv_logo%d%s", !SRV_ID ? 1 : SRV_ID, ServerInfo[DonationMultiplier] == 2 ? "[x2]" : ServerInfo[DonationMultiplier] >= 3 ? "[x3]" : "");
    TD_Logo_Two[0] = TextDrawCreate(6.1999, 384.9733, str); // 2 тип лого

    TextDrawTextSize(TD_Logo_Two[0], 79.0000, 89.0000);
    TextDrawAlignment(TD_Logo_Two[0], 1);
    TextDrawColor(TD_Logo_Two[0], -1);
    TextDrawBackgroundColor(TD_Logo_Two[0], 255);
    TextDrawFont(TD_Logo_Two[0], 4);
    TextDrawSetProportional(TD_Logo_Two[0], 0);
    TextDrawSetShadow(TD_Logo_Two[0], 0);

    Logotype_Show();
}

Logotype_Time(playerid)
{
    if(p_info[playerid][p_settings][INTERFACE])
    {
        TextDrawShowForPlayer(playerid, TD_DataTime[0]);
        TextDrawShowForPlayer(playerid, TD_DataTime[1]);
        TextDrawHideForPlayer(playerid, TD_Logo_Default[15]);
    }
    else
    {
        TextDrawHideForPlayer(playerid, TD_DataTime[0]);
        TextDrawHideForPlayer(playerid, TD_DataTime[1]);
        TextDrawShowForPlayer(playerid, TD_Logo_Default[15]);
    }
}

Action_Show(playerid)
{
    TextDrawShowForPlayer(playerid, TD_Actions[0]);
    TextDrawShowForPlayer(playerid, TD_Actions[1]);
    SetTimerEx("Action_Hide", 7500, false, "i", playerid);
}

forward Action_Hide(playerid);
public Action_Hide(playerid)
{
    TextDrawHideForPlayer(playerid, TD_Actions[0]);
    TextDrawHideForPlayer(playerid, TD_Actions[1]);
    return 1;
}
