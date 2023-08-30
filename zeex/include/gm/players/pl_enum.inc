enum PLAYER_DATA_ENUM
{
	pUsername[MAX_PLAYER_NAME+1],
	pUsername_[MAX_PLAYER_NAME+1],
    pMaskname[32],
	pID,
	pAccID,
	pAccname[MAX_PLAYER_NAME+1],
	pCash,
	pBank,
	pSkin,
	pSex,
	pOrigin,
	pAge,
	pRace,	
	pBirthdate[24],
	pLevel,
	pExp,
	pHours,
	pMinutes,
	pAdmin,
	pMapper,
	pEbc,
	pSkinYetki,
	pRdscripter,
	pAdminHide,
	pHelper,
	pHelperLead,
	pFMAdmin,
	pInt,
	pWorld,

	pDrugLabAccess,

	pAJailed,
	pAJailTime,

	pJailed,
	pIsolateTime,
	pJailTime,
	pWarns,

	pPremium,
	pPremiumTime,
	pDonate,
	pNameChanges,
	pNumberChanges,
	
	pCarLic,
	pWepLic,
	pFlyLic,
	pTaxiLic,
	pPrescribe,
	pGanjaTime,
	pFightStyle,
	pHud,
	pPayCheckMoney,
	pPayDayTime,
	pPunctePremium,
	pSavings,
	pRentKey,
	pRentPrice,
	pChannel,
	pOwnedChannel,
	Float:pHealth,
	Float:pArmour,
	pAuthed,
	pCarKey,
	pSpareKey,
	pWorkOn,
	pWalk,
	pFaction,
	pRank,
	pBadgeNumber,
	pDriveWarns,
	pWepWarns,
	pWepCount,
	pArrested,
	pTalk,
	pAuthwep,
	pSwat,
	pSwatDuty,
	pLawyer,
	pSlot,
	pJob,
	pCareer,
	pSideJob,
	pPrisoned,
	pInjured,
	pDeathReason,
	pOnDuty,
	pChar,
	
	//pWeap[MAX_WEAP],
	//pAmmo[MAX_WEAP],
	//pAmmoType[MAX_WEAP],
    pHideWeap[MAX_WEAP-1],

	pFishCount,
	pWeaponBone[3],
	Float:pWeaponX[3],
    Float:pWeaponY[3],
    Float:pWeaponZ[3],
    Float:pWeaponRX[3],
    Float:pWeaponRY[3],
    Float:pWeaponRZ[3],
	pMutedTime,
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ,
	Float:pPosA,
	Float:pLocationPos[3],
	pTog[3],
	
	pNumber,
	pPhoneAirplane,
	pPhoneSound,
	pPhoneStyle,
	pPhoneOff,
	pPhoneModel,
	pPhoneRingtone,

	pLastPrim,
	pLastSec,
	pLastMelee,

	pPlayerSerial,
    pReportAbout[120],
    pReportMute,
	pReportTime,
	bool: pReport,

	InMission,
	MissionTime,
	MissionTarget[2],
	MissionReward,
	
	pForbid,

	pRaporSayi,
	pTalepSayi,

	pDescribe[PAME_MAX_LEN],
	pDescribe2[PAME_MAX_LEN],

	pOlusumDivision[5],

	pCicek,
	pKamera,
	pBoombox,
	pMaske,
	pKalem,
	pOyunKarti,
	pSigara,
	pCakmak,
	pZar,
	pBenzinBidonu,
	pTelsiz,
	pCalintiRadyo,
	pCalintiEvEsya,
	pBurnerTelefon,
	SafeObject[2],

	pScriptedGun[12],
	pScriptedAmmo[12],
	pWeapons[12],
	pAmmo[12],	
	pSilahSistemi,
	SilahTick,
	SilahVerDialogID,
	pBitcoin,
	pEtherium,
	pSilahTick,
	pAtesTick,
	pUzerindekiSilah,
	pSettings,
	pDependence,
	pDemolition,
	pFishTime,
	pMark[MAX_PLAYER_MARKS],
	pBagimlilikEXP, // Default: 0, 3 olunca baðýmlý olur.
	pBagimlilikSeviye, // Baðýmlý Deðil: 0 - Baðýmlý: 1
	pUTedaviEXP, // Default: 0, 10 olunca tedavi sonlanýr - baðýmlýlýk biter. Uyuþturucu kullanýrsa tedavi sýfýrlanýr.
	pUTedaviSure, // Default: 0, 4 olunca tedavi olunabilir.
	pKrizSure, // Default: 0 & Baðýmlýyken 240
	UyusKullan,
	pHammadde,
	PaketVer[2]
}
new PlayerInfo[MAX_PLAYERS][PLAYER_DATA_ENUM];
new Float:PlayerHealth[MAX_PLAYERS];


enum ENUM_INVENTORY
{
	//pInvID,
	//pInvType,
	pInvItem,
	pInvQ,
	pInvEx,
	pInvS,
	Float:pInvQFloat,
	pInvName[16]
}
new Inventory[MAX_PLAYERS][MAX_INV_SLOTS][ENUM_INVENTORY];
new CarInventory[MAX_VEHICLES][MAX_CAR_INVENTORY][ENUM_INVENTORY];
new TrunkInventory[MAX_VEHICLES][MAX_TRUNK_INVENTORY][ENUM_INVENTORY];
new HouseInventory[MAX_HOUSES][MAX_HOUSE_INVENTORY][ENUM_INVENTORY];

enum PLAYER_TEMP_ENUM
{
	pLogged,
	pLoggedTime,
	pLoggedTry,
	pPMPlayer,
	pHealPlayer,
	pFactionPlayer,
	pInterview,
	pInterviewPlayer,
	pRentPlayer,
	pRentPrice,
	pWepPlayer,
	pWepPrice,
	pHouseHouse,
	pHousePrice,
	pHousePlayer,
	pBizPlayer,
	pBizPrice,
	pBizID,
	pFriskPlayer,
	pSpecPlayer,
	pHirePlayer,
	pBeanbag,
	pLTL,
	pTaser,
	pTaserTime,
	pFreezeTime,
	Float:pInvulnerable,
	pEditBort,
	pCCTV,
	pZond,
	pZondActor,
	pZondObj,
	Text3D:pZondLabel,
	pDarkAFK,
	pFlashTime,
	pCarPrice,
	pCarPlayer,
	pFurniture,
	pFurnitureB,
	p3DMenu,
	pHealTime,
	pBuildHouse,
	pRamType,
    pRamTime,
    pRamHouse,
	pRamGarage,
	pRamVeh,
    pRamBiz,
    pRamObj,
    pInjuredLegTime,
    pInjuredTime,
	pHelpUp3dText,
    pDamagesCount,
    pCallLine,
    pCallStatus,
    pCallIncoming,
	pCallTime,
	pCallName[24],
	pCallKeypad[24],

	pJob,
	pJobTime,

	pSpawned,

	pUnscrambleID,
	pScrambleFailed,
	pScrambleSuccess,

	//JackingTime,
	//JackingVehID,
	//JackingCP,

	JackingType,
	JackingWarnings,
	
	pEmergency,
    pTracePlayer,
    pTraceGZ,
    pTraceStage,
    Float:pTraceDist[3],
    pDialogList,
    pDriver,
    pCargoID,
	pCargoListed[MAX_TRUCK_PRODUCT],
	pWeaponListed[30],
	pListed[5],
	pWaypoint,
	pPDAListed[MAX_TRUCK_CARGO],
	pMDCPlayer,
	pPatrol,

	pPoliceCalls,
	pPoliceJails,
	pPoliceFines,

	pCallOn,
	Float:pCallPosX,
	Float:pCallPosY,
	Float:pCallPosZ,
    pFishTime,
    
	Float:editPos[6],

	pPlantTime,
	pPlantType,

	pFireTime,

    pCuffed,
	pNews,
	pHouseEntered,
	pBizEntered,
	pApartEntered,
	pDMLog,

	pGreetPlayer,
	pGreetType,
	pFoodStand,
	pReportTime,
	pServePlayer,
	pServeType,
	pAdminDuty,
	pTesterDuty,
	pBoombox,
	pBoombox_house,
	pBoombox_biz,
	pRentveh,
	pLicenseExam,
	pMDCWepPlayer,
	pMDCWepName[MAX_PLAYER_NAME+1],
	
	pDrugUse,
	pDrugTime,
	pDrugChgWeather,
    pDemolitionTime,
    pChangeNick[MAX_PLAYER_NAME+1],
	pPizzaBoy,
	pInteriorObj,
	pInteriorID,
	pInteriorHouse,
	pInteriorBiz,

	MyCarSpawn[16],
	MyCars[16],
	
	pPayphoneNumStr[10],
	pPayphone,

	tempItem,
	tempEx,
	tempQ,

	tempStatus,

	UsingCorpse,
	UsingBort,

    pGozAlti,
	pInjureText,

	pCarWarpTime,
	pCarWarpVehicleID,
	pCarTick,
	OlumSayisi,
	OlumSuresi,
	HileKontrol,
	AntiHileSistemi,	

	pAdvertTime,
	pColorPage,
	bool:pTackleMode,
	pLastLogin,

	pBanTime,
	pDebugMode,
    pTruckerOn,
	pTruckerPrice,
	pTruckerTime,

	pDestekTakip,

	bool:pSendReport,
	bool:pSendQuest,
	bool:pSanDuty,
	bool:pMicPerm,
	pFactionInvite,
	pFactionInvitedBy
}

new pTemp[MAX_PLAYERS][PLAYER_TEMP_ENUM];


new RefuelTimer[MAX_PLAYERS] = {-1, ...},
	Text3D:status_upd[MAX_PLAYERS];


enum (<<= 1)
{
	togName = 1, // +
	togOOC, // +
	togJoin, // +
	togAdv, // +
	togGov, // +
	togPM, // +
	togAdmCmds, // +
	togAdmChat, // +
	togHelperChat,
	togNews, // +
	togAFK, // +
	togHUD, // +
	yesMHUD, // +
	togFaction, // +
	togTester, 
	togEnter,
	togService,
	togCustomBar,
	togDoSetting	
}
new sandalyeobje[MAX_PLAYERS];
new teksandalyeobje[MAX_PLAYERS];
new Text3D:SandalyeLabel[MAX_PLAYERS];
new Text3D:TekSandalyeLabel[MAX_PLAYERS];