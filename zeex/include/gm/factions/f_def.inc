#define FACTION_CITY    (1)
#define FACTION_POLICE  (2)
#define FACTION_MEDICS  (3)
#define FACTION_FIRE    (4)
#define FACTION_DOCS    (5)
#define FACTION_SAN     (6)
#define FACTION_GANG    (7)
#define FACTION_MAFIA   (8)
#define FACTION_CIVIL   (9)
#define FACTION_SANOFF  (10)
#define FACTION_STATEBAR (11)

new OlusumTipleri[12][30] =
{
	"Boþ",
	"LCGOV",
	"LCPD",
	"LCMD",
	"LCFD",
	"DoC",
	"Haber Kanalý",
	"Çete",
	"Mafya",
	"Sivil",
	"Haberci",
	"State Bar"
};

new OyuncuOlusumlar[] = // Oyuncularýn yaratabileceði oluþum tipleri
{
	6,
	7,
	8,
	9
};

#define IsFactionLegal(%0)          (Factions[%0][fType] > 0 && Factions[%0][fType] < 6 || Factions[%0][fType] == 11)
#define PlayerFactionType(%0)       Factions[PlayerInfo[%0][pFaction]][fType]

#define IsPlayerFactionPolice(%0)   (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_POLICE)
#define IsPlayerFactionMedic(%0)    (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_MEDICS)
#define IsPlayerFactionFire(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_FIRE)
#define IsPlayerFactionNews(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_SAN)
#define IsPlayerFactionNewsOff(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_SANOFF)
#define IsPlayerFactionCity(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_CITY)
#define IsPlayerFactionDocs(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_DOCS)
#define IsPlayerFactionStateBar(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_StateBar)
#define IsPlayerFactionMafia(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_GANG)
#define IsPlayerFactionGang(%0)     (Factions[PlayerInfo[%0][pFaction]][fType] == FACTION_MAFIA)


#define IsFactionPolice(%0)     (Factions[%0][fType] == FACTION_POLICE)
#define IsFactionMedic(%0)      (Factions[%0][fType] == FACTION_MEDICS)
#define IsFactionFire(%0)       (Factions[%0][fType] == FACTION_FIRE)
#define IsFactionNews(%0)       (Factions[%0][fType] == FACTION_SAN)
#define IsFactionNewsOff(%0)       (Factions[%0][fType] == FACTION_SANOFF)
#define IsFactionCity(%0)       (Factions[%0][fType] == FACTION_CITY)
#define IsFactionDocs(%0)       (Factions[%0][fType] == FACTION_DOCS)
#define IsFactionStateBar(%0)       (Factions[%0][fType] == FACTION_STATEBAR)

#define GetRankName(%0)         FactionRanks[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1]

#define GetInviteRight(%0)      FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rInvite]
#define GetUninviteRight(%0)    FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rUninvite]
#define GetRankRight(%0)        FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rRank]
#define GetRankNameRight(%0)    FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][r_eRank]
#define GetSpawnRight(%0)       FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rSpawn]
#define GetChatRight(%0)        FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rChat]
#define GetTowRight(%0)         FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rTow]
#define GetBodyCamRight(%0)     FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][rBodyCam]
#define GetRightsRight(%0)      FRank[PlayerInfo[%0][pFaction]][PlayerInfo[%0][pRank]-1][r_eRights]

#define RIGHT_YES       "{00B200}Evet"
#define RIGHT_NO        "{CC0000}Hayýr"

#define MAX_FACTION_LENGHT					(90)

#define OLUSUM_BIRLIK_KUR_SEVIYE 	1
#define OLUSUM_BIRLIK_KUR_PARA 		2500
#define MAX_OLUSUM_ADI 				40 // string uzunluðu
#define MAX_OLUSUM_KISADI 			5 // string uzunluðu

new OlusumDialog[MAX_PLAYERS][5];
