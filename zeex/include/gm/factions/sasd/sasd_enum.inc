enum EMERGENCY_ENUM
{
	callExists,
	callType,
	callName[MAX_PLAYER_NAME],
	callPhone,
	callText[128],
	callLocation[128],
	callDate[32],
	Float: callPosX,
	Float: callPosY,
	Float: callPosZ,
	callAccept,
	callAcceptBy[65],
	callDelete
}
new CallInfo[MAX_CALLS_AND_ARREST][EMERGENCY_ENUM];

enum E_FACTION_WEAPONS
{
	weaponID,
	weaponAmmo,
	weaponAllowed,
	weaponFaction
}

new CarFactionWeaponsInfo[MAX_CAR_WEAPONS][E_FACTION_WEAPONS] =
{
	{25, 40, 1, FACTION_POLICE},
	{29, 180, 1, FACTION_POLICE},
	{31, 300, 1, FACTION_POLICE},
	{24, 70, 1, FACTION_POLICE},
	{43, 1000, 1, FACTION_POLICE},
	{41, 1000, 1, FACTION_POLICE}
};

enum APB_ENUM
{
	apbID,
	apbCharge[128],
	apbSuspect[MAX_PLAYER_NAME],
	apbOfficer[MAX_PLAYER_NAME],
	apbDate[32],
	apbOn,
	apbFaction
}
new ApbInfo[MAX_APBS][APB_ENUM];

enum ARREST_ENUM
{
	arrestSuspect[MAX_PLAYER_NAME],
	arrestOfficer[MAX_PLAYER_NAME],
	arrestDate[32],
	arrestTime,
	arrestExists,
	arrestDelete
}
new ArrestInfo[MAX_CALLS_AND_ARREST][ARREST_ENUM];

enum PATROL_ENUM
{
	patrulExists,
	patrulName[32],
	patrulOfficer[2]
}
new PatrolInfo[2][MAX_PATROL][PATROL_ENUM];
/*new PatrolInfo[][][PATROL_ENUM] = 
{
	{
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, INVALID_PLAYER_ID}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, INVALID_PLAYER_ID}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, 0}},
		{1,"LINCOLN-1",{0, INVALID_PLAYER_ID}},
		{1,"ADAM-2",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, 0}},
		{1,"LINCOLN-1",{0, INVALID_PLAYER_ID}},
		{1,"ADAM-2",{0, 0}}
	},
	{
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"LINCOLN-1",{0, 0}},
		{1,"ADAM-2",{0, 0}},
		{1,"RACHEL-1",{0, 0}},
		{1,"LINCOLN-1",{0, INVALID_PLAYER_ID}},
		{1,"ADAM-2",{0, 0}}
	}
};*/

enum SPIKE_ENUM
{
	sCreated,
    Float:sX,
    Float:sY,
    Float:sZ,
    sObject,
};
new SpikeInfo[MAX_SPIKE][SPIKE_ENUM];

#define MAX_ROPE_LENGTH (70)
#define ROPEOFFSETZ		(12)
#define ROPETIME		(250)
new RopesInfo[MAX_PLAYERS][MAX_ROPE_LENGTH];