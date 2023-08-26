enum CARFIX_ENUM
{
	Float: fixX,
	Float: fixY,
	Float: fixZ,
	fixVW,
	fixInt,
	fixPickUp
}

enum FACTION_ENUM
{
	fID,
	fPickUp,
	fName[32],
	fShortName[8],
	Float:fPosX,
	Float:fPosY,
	Float:fPosZ,
	fSpawnInt,
	fSpawnVW,
	fJoinRank,
	fType,
	fRanks,
	fChatON,
	fColor,
	Float:fUniformX,
	Float:fUniformY,
	Float:fUniformZ,
	fUniformInt,
	fUniformVW,
	Carfix[CARFIX_ENUM],
	
	fPoint,
	fPointTime,
	fON
};
new Factions[MAX_FACTIONS][FACTION_ENUM];
new FactionRanks[MAX_FACTIONS][20][32];

enum RANK_ENUM
{
	rInvite,
	rUninvite,
	rRank,
	r_eRank,
	rSpawn,
	rChat,
	rTow,
	rBodyCam,
	r_eRights,
};
new FRank[MAX_FACTIONS][20][RANK_ENUM];

enum RANK_SETTINGS_DATA
{
	right_id,
	right_name[64],
	right_cmd[32]
};

new RS[9][RANK_SETTINGS_DATA] = {
	{0, "{FFFFFF}Birlik davet yetkisi ", "/birlikdavet"},
	{1, "{FFFFFF}Birlikten çýkarma yetkisi", "/birliktenat"},
	{2, "{FFFFFF}Rütbe deðiþtirme yetkisi", "/rozetgoster"},
	{3, "{FFFFFF}Rütbe adý deðiþtirme yetkisi", "/rutbedegistir"},
	{4, "{FFFFFF}Spawn noktasýný deðiþtirme yetkisi", "/spawndegistir"},
	{5, "{FFFFFF}Birlik sohbet kanalýný düzenleme", "/fchat"},
	{6, "{FFFFFF}Birlik araçlarýný spawnlama", "/birlikrespawn"},
	{7, "{FFFFFF}Bodycam eriþimi", "/mdc"},
	{8, "{FFFFFF}Rütbe izinlerini düzenleme", "/birlikizinleri"}
};

enum BORT_ENUM
{
    bortOn,
	bortName[32],
	bortObject,
	bortUsing
}
new BortInfo[MAX_PLAYERS][MAX_BORTES][BORT_ENUM];
