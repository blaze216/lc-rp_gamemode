Dialog:REPORT(playerid, response, listitem, inputtext[])
{
	if (!response) return 0;

	new idx;

	for (new i = 1; i < sizeof(ReportInfo); i ++)
	{
		if (ReportInfo[i][rReportExists] == false)
		{
			idx = i;
			break;
		}
	}

	OnPlayerReport(playerid, idx, playerReport[playerid]);
    
    return 1;
}

Dialog:QUEST(playerid, response, listitem, inputtext[])
{
	if (!response) return 0;

	new idx;

	for (new i = 1; i < sizeof(QuestInfo); i ++)
	{
		if (QuestInfo[i][qQuestExists] == false)
		{
			idx = i;
			break;
		}
	}

	OnPlayerQuest(playerid, idx, playerQuest[playerid]);

    return 1;
}