// Hunting;
    for(new i; i < sizeof(HuntingInfo); i++)
    {
        if(HuntingInfo[i][hObject] == INVALID_OBJECT_ID)
        {
            HuntingInfo[i][hObject] = CreateObject(19315, HuntingInfo[i][hPos][0], HuntingInfo[i][hPos][1], HuntingInfo[i][hPos][2], HuntingInfo[i][hPos][3], HuntingInfo[i][hPos][4], HuntingInfo[i][hPos][5]);
        }
    }

    
        for(new idx = 0; idx < sizeof(HuntingInfo); idx++)
        {
            if(HuntingInfo[idx][hRespawn] > 0)
            {
                HuntingInfo[idx][hRespawn]--;
                if(HuntingInfo[idx][hRespawn] <= 0)
                {
                    if(HuntingInfo[idx][hObject] == INVALID_OBJECT_ID)
                    {
                        HuntingInfo[idx][hObject] = CreateObject(19315, HuntingInfo[idx][hPos][0], HuntingInfo[idx][hPos][1], HuntingInfo[idx][hPos][2], HuntingInfo[idx][hPos][3], HuntingInfo[idx][hPos][4], HuntingInfo[idx][hPos][5]);
                        HuntingInfo[idx][hStatus] = 0;
                    }
                }
            }
        }