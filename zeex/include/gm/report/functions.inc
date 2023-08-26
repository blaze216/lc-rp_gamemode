this::OnPlayerReport(playerid, reportid, const text[])
{
	if(ReportInfo[reportid][rReportExists] == true)
	{
		for (new i = 1; i < sizeof(ReportInfo); i ++)
		{
			if(ReportInfo[i][rReportExists] == false)
			{
				reportid = i;
				break;
			}
		}
	}

	ReportInfo[reportid][rReportExists] = true;
	ReportInfo[reportid][rReportTime] = gettime();

	format(ReportInfo[reportid][rReportDetails], 90, "%s", text);
	ReportInfo[reportid][rReportBy] = playerid;

	pTemp[playerid][pSendReport] = true;
	SendClientMessageEx(playerid, 0x33AA33FF, "Raporunuz online yöneticilere ulaþtýrýlmýþtýr! Rapor ID: %d", reportid);
	SetPVarInt(playerid, "reportidm", reportid);

	if(strlen(text) > 67)
	{
		SendReportMessage(0xFFFF91FF, 1, "[Rapor: %d] %s (%d): %.75s", reportid, GetNameEx(playerid), playerid, text);
		SendReportMessage(0xFFFF91FF, 1, "[Rapor: %d] ...%s", reportid, text[75]);
	}
	else SendReportMessage(0xFFFF91FF, 1, "[Rapor: %d] %s (%d): %s", reportid, GetNameEx(playerid), playerid, text);

	if(!strcmp(text, "bug", true) || !strcmp(text, "hile", true) || !strcmp(text, "aim", true) || !strcmp(text, "troll", true))
	{
		foreach(new i : Player)
		{
			if(PlayerInfo[i][pAdmin]) GameTextForPlayer(i, "~y~~h~Oncelikli rapor", 4000, 1);
		}
	}
	return 1;
}
	
this::OnPlayerQuest(playerid, questid, const text[])
{
	if(QuestInfo[questid][qQuestExists] == true)
	{
		for (new i = 1; i < sizeof(QuestInfo); i ++)
		{
			if(QuestInfo[i][qQuestExists] == false)
			{
				questid = i;
				break;
			}
		}
	}

	QuestInfo[questid][qQuestExists] = true;
	QuestInfo[questid][qQuestTime] = gettime();

	format(QuestInfo[questid][qQuestDetails], 90, "%s", text);
	QuestInfo[questid][qQuestBy] = playerid;

	pTemp[playerid][pSendQuest] = true;
	SendClientMessageEx(playerid, 0x33AA33FF, "Sorunuz online helperlara ulaþtýrýlmýþtýr! Soru ID: %d", questid);
	SetPVarInt(playerid, "questidm", questid);

	if(strlen(text) > 67)
	{
		SendQuestMessage(0xFFFF91FF, 1, "[Soru: %d] %s (%d): %.75s", questid, GetNameEx(playerid), playerid, text);
		SendQuestMessage(0xFFFF91FF, 1, "[Soru: %d] ...%s", questid, text[75]);
	}
	else SendQuestMessage(0xFFFF91FF, 1, "[Soru: %d] %s (%d): %s", questid, GetNameEx(playerid), playerid, text);

	if(strfind(text, "nedir?", true) != -1 || strfind(text, "?", true) != -1 || strfind(text, "nasýl", true) && pTemp[playerid][pTesterDuty])
	{
		foreach(new i : Player)
		{
			if(pTemp[i][pTesterDuty]) GameTextForPlayer(i, "~y~~h~Oncelikli soru", 4000, 1);
		}
	}
	return 1;
}

stock SendReportMessage(color, level, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (PlayerInfo[i][pAdmin] >= level && !(PlayerInfo[i][pSettings] & togAdmCmds)) {
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (PlayerInfo[i][pAdmin] >= level && !(PlayerInfo[i][pSettings] & togAdmCmds)) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SQLCharFix(text[512])
{
	strreplace(text, "'", " ");
	return text;
}

stock SQL_ReturnEscaped(const string[])
{
	new entry[256];
	mysql_escape_string(string, entry);
	return entry;
}

stock TimeConvertEx(sec, &days, &hours, &minutes, &seconds)
{
    days = floatround(sec / 86400);
    hours = floatround((sec - (days * 86400)) / 3600);
    minutes = floatround((sec - (days * 86400) - (hours * 3600)) / 60);
    seconds = sec % 60;
    return 1;
}

stock SendQuestMessage(color, level, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 8); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit ADD.C 4
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (PlayerInfo[i][pHelper] >= level && pTemp[i][pTesterDuty]) {
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (PlayerInfo[i][pHelper] >= level && pTemp[i][pTesterDuty]) {
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

Report_GetCount(playerid)
{
	new count;
    for (new i = 0; i != MAX_REPORTS; i ++) if(ReportData[i][rExists] && ReportData[i][rPlayer] == playerid) count++;
	return count;
}

/*Report_Clear(playerid)
{
    for (new i = 0; i != MAX_REPORTS; i ++) if(ReportData[i][rExists] && ReportData[i][rPlayer] == playerid) Report_Remove(i);
	return 1;
}*/

Report_Add(playerid, const text[], type = 1)
{
	for (new i = 0; i != MAX_REPORTS; i ++) if(!ReportData[i][rExists])
	{
        ReportData[i][rExists] = true;
        ReportData[i][rType] = type;
        ReportData[i][rPlayer] = playerid;
        ReportData[i][rYetkili] = INVALID_PLAYER_ID;

        strpack(ReportData[i][rText], text, 128 char);
		return i;
	}
	return -1;
}
Report_Remove(reportid)
{
	if(reportid != -1 && ReportData[reportid][rExists])
	{
	    ReportData[reportid][rExists] = false;
	    ReportData[reportid][rPlayer] = ReportData[reportid][rYetkili] = INVALID_PLAYER_ID;
	}
	return 1;
}