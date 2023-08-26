new PlayerText:spectate_TD[MAX_PLAYERS][2];

new PlayerText: playerhud[MAX_PLAYERS][5];

enum E_ServerTD {
    Text:std_DarkScreen
}
new ServerTextdraws[E_ServerTD];

//new PlayerText:cWspeedo[MAX_PLAYERS][10];

new PlayerText: carsexhud[MAX_PLAYERS][14];
/////////////////////////////////////////////////


new bool:HUD_Created[MAX_PLAYERS];
//new bool:HudStatus[MAX_PLAYERS];
//new PlayerText:HudTextDraw[MAX_PLAYERS];

//new PlayerText: drug_effect[MAX_PLAYERS];

new Text: TD_vehicle_info[2];
//new PlayerText: TD_vehicle_name[MAX_PLAYERS];

new Text: TD_restaurant[4];
new PlayerText: TD_restaurant_prod[MAX_PLAYERS][8]; //0-3 - �������� ����, 4 - 7 - ��������

new Text: Developer;
new Text: Admin;

/* LABELS */
new PlayerText: mulkbilgi[MAX_PLAYERS];
new PlayerText: mulktext[MAX_PLAYERS][2];

//new Text:errormsg[MAX_PLAYERS];
new PlayerText: TD_job_message[MAX_PLAYERS][1];
new Text: infotxt[MAX_PLAYERS];

new Text: zond_cam[11];

enum SPEEDOMETR_DATA
{
	speedFont,
	Float:speedX,
    Float:speedY,
	Float:speedLX,
    Float:speedLY
};


new const speedSettings[4][SPEEDOMETR_DATA] =
{
// FONT         CORDS                   LetterSize      
    {1,     497.9165, 105.4813,     0.3199, 1.2999}, //������ 1 ����
    {1,     497.9165, 387.4053,     0.3199, 1.2999}, //����� 1 ����
    {2,     497.9165, 105.4813,     0.2899, 1.3500},
    {2,     497.9165, 387.4053,     0.2899, 1.3500}
};

new PlayerText:SpeedText[MAX_PLAYERS];

enum E_PlayerTD 
{
    PlayerText:LoginCharacterTD[5],
    PlayerText:HudTD,
    PlayerText:SpectatingInfo[6]
}
new PlayerTextdraws[MAX_PLAYERS][E_PlayerTD];

enum E_Character_Selection 
{
    bool:sIsSelecting,
    sCharactersCount,
    sCurrentSlotID,
    sActorID
}
new CharacterSelection[MAX_PLAYERS][E_Character_Selection];

new PlayerText:FuelText[MAX_PLAYERS];    