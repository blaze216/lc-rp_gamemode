ReturnDate()
{
    new sendString[90], MonthStr[40], month, day, year;
    new hour, minute, second;

    gettime(hour, minute, second);
    getdate(year, month, day);
    switch(month)
    {
        case 1:  MonthStr = "01";
        case 2:  MonthStr = "02";
        case 3:  MonthStr = "03";
        case 4:  MonthStr = "04";
        case 5:  MonthStr = "05";
        case 6:  MonthStr = "06";
        case 7:  MonthStr = "07";
        case 8:  MonthStr = "08";
        case 9:  MonthStr = "09";
        case 10: MonthStr = "10";
        case 11: MonthStr = "11";
        case 12: MonthStr = "12";
    }

    format(sendString, 90, "%02d/%s/%d, %02d:%02d:%02d", day, MonthStr, year, hour, minute, second);
    return sendString;
}

strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}

CMD:rapor(playerid, params[])
{
	if(isnull(params) || strlen(params) < 3)
		return SendSyntaxMessage(playerid, "/rapor [yazý]");

	if(pTemp[playerid][pSendReport])
		return SendErrorMessage(playerid, "Zaten soru gönderdiniz.");

	new
		showString[380]
	;

	format(showString, sizeof(showString), "Sunucu içerisinde ki online yöneticileri þu anda rapor gönderiyorsunuz. Soru: %s\n\nBu raporu göndermek istediðinizden emin misiniz? Sorunun gereksiz ya da spam olup olmadýðýnana emin olun.\nDüþünnceleriniz hakkýnda soru göndermeyin, forum üzerinden düþünncelerinizi yazýn.", params);
	Dialog_Show(playerid, REPORT, DIALOG_STYLE_MSGBOX, "Uyarý, þu anda rapor gönderiyorsunuz", showString, "Devam", "Gönderme");

	format(playerReport[playerid], 128, "%s", params);
	return 1;
}

alias:soru("sorusor");
CMD:soru(playerid, params[])
{
	if(isnull(params) || strlen(params) < 3) return SendSyntaxMessage(playerid, "/soru [yazž]");

	if(pTemp[playerid][pSendQuest] == true)
		return SendErrorMessage(playerid, "Zaten soru gönderdiniz.");

	new showString[350];

	format(showString, sizeof(showString), "Sunucu içerisinde ki online supportlara þu anda soru gönderiyorsunuz. Soru: %s\n\nBu soruyu göndermek istediðinizden emin misiniz? Sorunun gereksiz ya da spam olup olmadýðýna emin olun.\nDüþünceleriniz hakkýnda soru göndermeyin, forum üzerinden düþüncelerinizi yazýn.", params);
	Dialog_Show(playerid, QUEST, DIALOG_STYLE_MSGBOX, "Uyarý, þu anda soru gönderiyorsunuz", showString, "Devam", "Gönderme");
	format(playerQuest[playerid], 128, "%s", params);
	return 1;
}



CMD:raporlar(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1)
		return 0;

	SendClientMessage(playerid, COLOR_DARKGREEN, "____________________RAPORLAR____________________");

	for (new i = 0; i < sizeof(ReportInfo); i ++)
	{
		if(ReportInfo[i][rReportExists] == true)
		{
			if(strlen(ReportInfo[i][rReportDetails]) > 65)
			{
				SendClientMessageEx(playerid, 0xFFFF91FF, "%s (ID: %d) | RID: %d | Rapor: %.65s", GetNameEx(ReportInfo[i][rReportBy]), ReportInfo[i][rReportBy], i, ReportInfo[i][rReportDetails]);
				SendClientMessageEx(playerid, 0xFFFF91FF, "...%s | Bekliyor: %d saniyedir.", ReportInfo[i][rReportDetails][65], gettime() - ReportInfo[i][rReportTime]);
			}
			else SendClientMessageEx(playerid, 0xFFFF91FF, "%s (ID: %d) | RID: %d | Rapor: %s | Bekliyor: %d saniyedir.", GetNameEx(ReportInfo[i][rReportBy]), ReportInfo[i][rReportBy], i, ReportInfo[i][rReportDetails], gettime() - ReportInfo[i][rReportTime]);
		}
	}
	return 1;
}

alias:raporkabul("rk", "ar");
CMD:raporkabul(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1)
		return 0;

	new reportid;

	if (sscanf(params, "d", reportid))
		return SendSyntaxMessage(playerid, "/raporkabul [rapor id]");

	if(ReportInfo[reportid][rReportExists] == false)
		return SendErrorMessage(playerid, "Belirttiðiniz rapor ID'i mevcut deðil.");

    new playerb = ReportInfo[reportid][rReportBy];

	SendReportMessage(COLOR_LIGHTRED, 1, "[RAPOR]: %s, %d ID'li raporu kabul etti.", GetAccName(playerid), reportid);
	pTemp[ReportInfo[reportid][rReportBy]][pSendReport] = false;
	DeletePVar(ReportInfo[reportid][rReportBy], "reportidm");
	

	SendClientMessageEx(ReportInfo[reportid][rReportBy], 0x33AA33FF, "%s (%d) rapor talebinize cevap verdi, lütfen sizinle irtibata geçmesini bekleyin. [Rapor ID: %d]", GetNameEx(playerid), playerid, reportid);
	SendClientMessageEx(ReportInfo[reportid][rReportBy], 0xFF6347FF, "Raporunuz:");
	SendClientMessageEx(ReportInfo[reportid][rReportBy], 0xAFAFAFFF, "%s", ReportInfo[reportid][rReportDetails]);
	
	PlayerInfo[playerid][pRaporSayi]++;
	SQL_SetIntegerAcc("accounts", "raporsayi", PlayerInfo[playerid][pRaporSayi], PlayerInfo[playerid][pAccID]);

    SendServerMessage(playerid, "%s adlý kiþinin %d numaralý raporunu kabul ettin..", GetNameEx(playerb), reportid);	

	ReportInfo[reportid][rReportExists] = false;
	ReportInfo[reportid][rReportBy] = INVALID_PLAYER_ID;

	return 1;
}

alias:raporred("raporreddet", "dr");
CMD:raporred(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1)
		return 0;

	new reportid;

	if (sscanf(params, "d", reportid))
		return SendSyntaxMessage(playerid, "/raporreddet [rapor id]");

	if(ReportInfo[reportid][rReportExists] == false)
		return SendErrorMessage(playerid, "Belirttiðiniz rapor ID'i mevcut deðil.");

    new playerb = ReportInfo[reportid][rReportBy];

	SendReportMessage(COLOR_LIGHTRED, 1, "[RAPOR]: %s, %d ID'li raporu sildi.", GetAccName(playerid), reportid);
	pTemp[ReportInfo[reportid][rReportBy]][pSendReport] = false;
	DeletePVar(ReportInfo[reportid][rReportBy], "reportidm");

	SendClientMessageEx(ReportInfo[reportid][rReportBy], 0xFF6347FF, "%s (%d) rapor talebinizi reddetti. [Rapor ID: %d]", GetNameEx(playerid), playerid, reportid);
	SendClientMessageEx(ReportInfo[reportid][rReportBy], 0xFF6347FF, "Raporunuz:");
	SendClientMessageEx(ReportInfo[reportid][rReportBy], 0xAFAFAFFF, "%s", ReportInfo[reportid][rReportDetails]);

    SendServerMessage(playerid, "%s adlý kiþinin %d numaralý raporunu red ettin.", GetNameEx(playerb), reportid);

	ReportInfo[reportid][rReportExists] = false;
	ReportInfo[reportid][rReportBy] = INVALID_PLAYER_ID;

	return 1;
}

CMD:raporiptal(playerid)
{
	new reportid;
	reportid = GetPVarInt(playerid, "reportidm");

	if(pTemp[playerid][pSendReport]){
		SendClientMessageEx(playerid, 0xFF6347FF, "Raporu baþarýyla iptal ettiniz.");
		pTemp[playerid][pSendReport] = false;
        ReportInfo[reportid][rReportExists] = false;
	    ReportInfo[reportid][rReportBy] = INVALID_PLAYER_ID;
		DeletePVar(playerid, "reportidm");
	} else {
		SendClientMessageEx(playerid, 0xFF6347FF, "Gönderilmiþ raporunuz bulunmamakta.");
	}
return 1;
}

CMD:soruiptal(playerid)
{
	new reportid;
	reportid = GetPVarInt(playerid, "questidm");

	if(pTemp[playerid][pSendQuest]){
		SendClientMessageEx(playerid, 0xFF6347FF, "Sorunuzu baþarýyla iptal ettiniz.");
		pTemp[playerid][pSendQuest] = false;
	    QuestInfo[reportid][qQuestExists] = false;
	    QuestInfo[reportid][qQuestBy] = INVALID_PLAYER_ID;
		DeletePVar(playerid, "questidm");
	} else {
		SendClientMessageEx(playerid, 0xFF6347FF, "Sorunuz bulunmamakta.");
	}
return 1;
}

CMD:sorular(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
		return 0;

	new count = 0;

	SendClientMessage(playerid, COLOR_DARKGREEN, "____________________SORULAR____________________");

	for (new i = 0; i < sizeof(QuestInfo); i ++)
	{
		if(!QuestInfo[i][qQuestExists])
            continue;

		if(strlen(QuestInfo[i][qQuestDetails]) > 65)
		{
			SendClientMessageEx(playerid, 0xFFFF91FF, "%s (ID: %d) | SID: %d | Soru: %.65s", GetNameEx(QuestInfo[i][qQuestBy]), QuestInfo[i][qQuestBy], i, QuestInfo[i][qQuestDetails]);
			SendClientMessageEx(playerid, 0xFFFF91FF, "...%s | Bekliyor: %d saniyedir.", QuestInfo[i][qQuestDetails][65], gettime() - QuestInfo[i][qQuestTime]);
		}
		else SendClientMessageEx(playerid, 0xFFFF91FF, "%s (ID: %d) | SID: %d | Soru: %s | Bekliyor: %d saniyedir.", GetNameEx(QuestInfo[i][qQuestBy]), QuestInfo[i][qQuestBy], i, QuestInfo[i][qQuestDetails], gettime() - QuestInfo[i][qQuestTime]);
		count++;
	}
	if(!count) return SendErrorMessage(playerid, "Bekleyen soru yok.");
	return 1;
}

alias:sorukabul("sk");
CMD:sorukabul(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
		return 0;

	new questid;

	if (sscanf(params, "d", questid))
		return SendSyntaxMessage(playerid, "/sorukabul [soru id]");

	if(QuestInfo[questid][qQuestExists] == false)
		return SendErrorMessage(playerid, "Belirttiðiniz soru ID'i mevcut deðil.");
    
	new playerb = QuestInfo[questid][qQuestBy];

	SendReportMessage(COLOR_LIGHTRED, 1, "[RAPOR]: %d ID'li soruyu %s isimli support kabul etti.", questid, GetAccName(playerid));
	pTemp[QuestInfo[questid][qQuestBy]][pSendQuest] = false;
	DeletePVar(QuestInfo[questid][qQuestBy], "questidm");

	SendClientMessageEx(QuestInfo[questid][qQuestBy], 0x33AA33FF, "%s (%d) soru talebinize cevap verdi, lütfen sizinle irtibata geçmesini bekleyin. [Soru ID: %d]", GetAccName(playerid), playerid, questid);
	SendClientMessageEx(QuestInfo[questid][qQuestBy], 0xAFAFAFFF, "Soru: %s", QuestInfo[questid][qQuestDetails]);

	PlayerInfo[playerid][pTalepSayi]++;
	SQL_SetIntegerAcc("accounts", "talepsayi", PlayerInfo[playerid][pTalepSayi], PlayerInfo[playerid][pAccID]);

	SendServerMessage(playerid, "%s adlý kiþinin %d numaralý talebini kabul ettin.", GetNameEx(playerb), questid);

	QuestInfo[questid][qQuestExists] = false;
	QuestInfo[questid][qQuestBy] = INVALID_PLAYER_ID;

	return 1;
}

alias:sorured("sr");
CMD:sorured(playerid, params[])
{
	if(PlayerInfo[playerid][pAdmin] < 1 && PlayerInfo[playerid][pHelper] < 1)
		return 0;

	new questid;

	if (sscanf(params, "d", questid))
		return SendSyntaxMessage(playerid, "/sorureddet [soru id]");

	if(QuestInfo[questid][qQuestExists] == false)
		return SendErrorMessage(playerid, "Belirttiðiniz soru ID'i mevcut deðil.");

    new playerb = QuestInfo[questid][qQuestBy];

	SendReportMessage(0xFFFFFF, 1, "AdmCmd: %s, %d idli soruyu sildi.", GetNameEx(playerid), questid);
	pTemp[QuestInfo[questid][qQuestBy]][pSendQuest] = false;
	DeletePVar(QuestInfo[questid][qQuestBy], "questidm");

	SendClientMessageEx(QuestInfo[questid][qQuestBy], 0xFF6347FF, "%s (%d) soru talebinizi reddetti. [Soru ID: %d]", GetNameEx(playerid), playerid, questid);
	SendClientMessageEx(QuestInfo[questid][qQuestBy], 0xFF6347FF, "Sorunuz:");
	SendClientMessageEx(QuestInfo[questid][qQuestBy], 0xAFAFAFFF, "%s", QuestInfo[questid][qQuestDetails]);

	SendServerMessage(playerid, "%s adlý kiþinin %d numaralo talebini red ettin.", GetNameEx(playerb), questid);

	QuestInfo[questid][qQuestExists] = false;
	QuestInfo[questid][qQuestBy] = INVALID_PLAYER_ID;

	return 1;
}