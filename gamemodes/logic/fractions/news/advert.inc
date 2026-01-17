new ChoosenAdvert[MAX_PLAYERS];

new AdvertSendingInfo[3];

#define MAX_NEWS_ADS 						30
#define ADVERT_PRICE						2000

enum E_ADVERT
{
	aSender[MAX_PLAYER_NAME],
	aText[128],
	aPhone,
	aStatus,
	aAlreadyEdited,
	aEdited[MAX_PLAYER_NAME],
	aQueue,
	bool:aIsTooked,
    bool:aVIP
}
new AdvertInfo[MAX_NEWS_ADS][E_ADVERT];

SendAdvertDialog(playerid)
{
    STRING_GLOBAL[0] = EOS;
    format(STRING_GLOBAL, sizeof(STRING_GLOBAL), ""W"Введите текст для отправки в радиостацнию:\n\nСтоимость объявления: "I"%d$.", ADVERT_PRICE);
    ShowPlayerDialog(playerid, D_ADVERTISE, DIALOG_STYLE_INPUT, ""I"Объявление", STRING_GLOBAL, "Далее", "Отмена");
    return 1;
}

AdvertList(playerid)
{
	STRING_GLOBAL[0] = EOS;
	for(new i; i < MAX_NEWS_ADS; i++)
	{
		if(AdvertInfo[i][aStatus] == 1 && AdvertInfo[i][aAlreadyEdited] == 0) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s\n", STRING_GLOBAL, i+1, AdvertInfo[i][aSender]);
		else if(AdvertInfo[i][aStatus] == 1 && AdvertInfo[i][aAlreadyEdited] == 1) format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" %s [Отредактировал: %s]\n", STRING_GLOBAL, i+1, AdvertInfo[i][aSender], AdvertInfo[i][aEdited]);
		else format(STRING_GLOBAL, sizeof(STRING_GLOBAL), "%s"I"[%d]"W" -\n", STRING_GLOBAL, i+1);
	}
	ShowPlayerDialog(playerid, D_ADVERTISE_LIST, DIALOG_STYLE_LIST, ""I"Объявления", STRING_GLOBAL, "Далее", "Отмена");
	return 1;
}

ClearAdvert(idx)
{
	if(AdvertInfo[idx][aStatus] == 0) return 0;
	format(AdvertInfo[idx][aSender], MAX_PLAYER_NAME, "");
	format(AdvertInfo[idx][aText], 128, "");
	AdvertInfo[idx][aPhone] = 0;
	AdvertInfo[idx][aStatus] = 0;
	AdvertInfo[idx][aAlreadyEdited] = 0;
	AdvertInfo[idx][aQueue] = 0;
	AdvertInfo[idx][aIsTooked] = false;
	AdvertInfo[idx][aVIP] = false;
	return 1;
}

alias:advertise("ad");
CMD:advertise(playerid, params[])
{
    if(p_info[playerid][mute] > 0) return SendError(playerid, "У Вас блокировка чата.");
    if(p_info[playerid][level] < 3) return SendError(playerid, "У Вас нет 3-его уровня.");
    if(!p_info[playerid][phone_number]) return SendError(playerid, "У Вас нет номера телефона.");
    if(!p_info[playerid][news]) return SendError(playerid, "Вы не подключены в какой-либо радиостанции.");
    SendAdvertDialog(playerid);
    return 1;
}

CMD:edit(playerid, params[])
{
	if(p_info[playerid][member] == RADIO_LS || p_info[playerid][member] == RADIO_SF || p_info[playerid][member] == RADIO_LV || p_info[playerid][member] == MAYOR_LS && p_info[playerid][rang] == 5)
	{
		if(p_info[playerid][rang] < 2) return SendError(playerid, "Редактирование объявлений доступно с 2-ого ранга.");
		AdvertList(playerid);
	} else SendError(playerid, "Вы не можете пользоваться этой командой.");
    return 1;
}