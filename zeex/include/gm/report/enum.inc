enum REPORT_INFO
{
	bool:rReportExists,
	rReportDetails[90],
	rReportTime,
	rReportBy[32]
}

enum reportData {
	rExists,
	rType,
	rPlayer,
	rYetkili,
	rText[128 char]
};

new ReportData[MAX_REPORTS][reportData];

new ReportInfo[100][REPORT_INFO];
new playerReport[MAX_PLAYERS][128];

enum QUEST_INFO
{
	bool:qQuestExists,
	qQuestDetails[90],
	qQuestTime,
	qQuestBy[32]
}

new QuestInfo[100][QUEST_INFO];
new playerQuest[MAX_PLAYERS][128];