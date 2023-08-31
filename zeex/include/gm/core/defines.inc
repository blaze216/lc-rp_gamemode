#define MAX_JOBS                (15)
#define MAX_RADIOS 		        (500)
#define MAX_INV_SLOTS 	        (15)
#define MAX_LABELS 				(100)
#define MAX_ENTRANCE 			(200)
#define MAX_INTERIORS 			(300)
#define MAX_ATMS 				(80)
#define MAX_BORSA               (10)
#define MAX_HOUSES 				(500)
#define MAX_REKLAM              (200)
#define MAX_REPORTS             (20)
#define MAX_GARAGES 			(150)
#define MAX_APART 				(200)
#define MAX_BIZ 				(500)

#define MAX_ADMIN_TELES 		(10)

#define PAME_MAX_LEN (80)

#define MAX_HOUSE_INVENTORY 	(10)

#define MAX_TRUNK_INVENTORY 	(10)
#define MAX_CAR_INVENTORY 		(5)

#define MAX_FOOD_STAND 			(50)
#define MAX_ITEM_DROPS 			(100)
#define MAX_FOOD_DROPS 			(100)
#define MAX_TRUCK_CARGO 		(80)
#define MAX_TRUCK_PACK 			(25)
#define MAX_CARGO_OBJ 			(100)
#define MAX_TRUCK_PRODUCT 		(25)
#define MAX_APBS 				(100)
#define MAX_FACTIONS 			(100)
#define MAX_CCTV    			(50)
#define MAX_TOWERS  			(50)
#define MAX_GATES 				(100)
#define MAX_PLANTS 				(75)
#define MAX_BORTES   			(25)
#define MAX_PAYPHONES   		(50)
#define MAX_FIRES               (100)
#define CROSSFIRE_TIMER			(1)
#define MAX_SPIKE               (20)
#define MAX_PLAYER_CONTACTS     (40)
#define MAX_PLAYER_NOTES        (10)
#define MAX_PLAYER_ATTACH       (5)
#define MAX_PLAYER_MUSIC        (10)
#define MAX_PLAYER_MARKS		(3)
#define MAX_LOCKER 				(50)
#define MAX_RENTAL 				(50)

#define MAX_SPEEDCAMS			(100)
#define MAX_MARKS				(650)
#define MAX_GRAFFITIES			(75)

#define MAX_WEAP                (4)

#define MIN_EMOTE_SECONDS		(0)
#define MAX_EMOTE_SECONDS		(300)
#define Range_VShort            (3.5)
#define Range_Short             (10.0)
#define Range_Normal            (20.0)
#define Range_Long              (30.0)
#define Range_VLong             (100.0)

#define LEVEL_EXP               (4)

#define MONEY_LOG   	        (1)
#define PROPERTY_LOG            (2)
#define ADMIN_LOG               (3)
// [/ban] - 1
// [/offban] - 1
// [/banip] - 1
// [/unban] - 12
// [/unbanip] - 12
// [/kick] - 2
// [/skick] - 2
// [/warn] - 4
// [/ajail] - 5
// [/offjail] - 51
// [/asetplate] - 6
// [/givegunex] - 7
// [/getgun] - 7
// [/givemoney] - 8
#define RAM_LOG                 (4)
#define VEHICLE_LOG             (5)
#define WEAPON_LOG              (6)
#define ITEM_LOG                (7)
#define DONATE_LOG              (8)

Dialog:None(playerid, response, listitem, inputtext[])
{
	return 1;
}

#define SIGNADSPRICE 3000
#define MOBILEMODELPRICE 1000

#define INVALID_WEAPON_SLOT_ID -1
#define MAX_ZONE_NAME 28
#define MAXLEN 80

#define UpdateIntVar(%0,%1,%2) SetPVarInt(%0, %1, (GetPVarInt(%0, %1) + %2))
#define UpdateFloatVar(%0,%1,%2) SetPVarFloat(%0, %1, (GetPVarFloat(%0, %1) + %2))

#define MODEL_SELECTION_COLOR       (8)
#define MODEL_BUING_COLOR      		(9)
#define MODEL_SELECTION_BB     		(10)

#define MAX_HASH_LENGTH				(65)
#define ADMIN_HASH					"s0ZpdLk7c"

#define CHARACTER_UNACTIVE                     (0)
#define CHARACTER_ACTIVE                     (1)

#define PVAR_LISTCHARS_CDETAILS_CID     "p_ls_dc_characterid"
#define PVAR_LASTENTEREDVEH_ID          "p_lastEnteredVehicle_ID"
#define PVAR_LASTENTEREDVEH_SEAT          "p_lastEnteredVehicle_SEAT"
#define PVAR_LASTPM_ISACTIVE            "p_LastPM_IsActive"
#define PVAR_LASTPM_ID                  "p_LastPM_ID"
#define PVAR_DARKSCREEN_ISACTIVE        "p_DarkScreen_IsActive"

// Server data
enum E_Server {
    sHostName[32],
    sWebUrl[32],
    sLanguage[64],
    sMap[32],
    sVersion[32],
    sMaintenance,
    sPassword[64],
    sWeather,
    sPricePayday,
    sPricePark,
    sPriceFuel,
    Float:sLocaleSalePercent,
    Float:sDealershipPercent,
    sSpawnInterior,
    sSpawnWorld,
    Float:sSpawnX,
    Float:sSpawnY,
    Float:sSpawnZ,
    Float:sSpawnA,
    lMinSalary,
    lMaxSalary,
    sPriceTaxiLicense,
    sPriceTaxiAd,
    sPriceDriverLicense,
    sPriceColour,
    sPriceInsurance,
    Float:sPriceVehRegisterPercent,
    Float:sPriceVehWeeklyTaxPercent,
    sDoublePayday
}

new ServerInfo[E_Server];