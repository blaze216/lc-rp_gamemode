#define GetDynamicObjectModel(%0) Streamer_GetIntData(STREAMER_TYPE_OBJECT, %0, E_STREAMER_MODEL_ID)

#define this::%0(%1) \
	forward %0(%1);\
	public %0(%1)

#define DIALOG_CONFIRM_SYS 7020

//////////////////////////////// MISC ////////////////////////////////
#define SetInterior(%0,%1) \
	SetPlayerInterior(%0,%1)

#define GetInterior(%0) \
	GetPlayerInterior(%0)

#define SetWorld(%0,%1) \
	SetPlayerVirtualWorld(%0,%1)

#define GetWorld(%0) \
	GetPlayerVirtualWorld(%0)

#define PlayerToPoint(%0,%1,%2,%3,%4) \
	IsPlayerInRangeOfPoint(%1,%0,%2,%3,%4)

#define GetName(%0) \
	PlayerInfo[%0][pUsername]

#define GetNameEx(%0) \
	PlayerInfo[%0][pUsername_]

#define GetNameWithMask(%0) \
	PlayerInfo[%0][pMaskname]

#define GetAccName(%0) \
	PlayerInfo[%0][pAccname]

stock GetPlayerNameEx(playerid, underscore = 0)
{
	new name[MAX_PLAYER_NAME + 1];
	GetPlayerName(playerid, name, sizeof(name));
	if(!underscore)
    {
        for (new i = 0, len = strlen(name); i < len; i ++) {
            if(name[i] == '_') name[i] = ' ';
        }
    }
    return name;
}
//////////////////////////////////////////////////////////////////////
//////////////////////////////// TEXT DEFINES ////////////////////////

#define SCM \
	SendClientMessage

#define SCMALL \
	SendClientMessageToAll

#define SendServerMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_SERVER2, "Liberty:{FFFFFF} "%1)

#define SendSyntaxMessage(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TURQUOISE, "Bilgi:{FFFFFF} "%1)

#define SendMedicMessage(%0,%1) \
	SendClientMessageEx(%0, 0xFF8282AA, "Liberty:{FFFFFF} "%1)

#define SendHelpMessage(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TURQUOISE, "Kullaným:{FFFFFF} "%1)

#define SendSpecialMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_YELLOWMY, "--> "%1)

#define SendErrorMessage(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TOMATO, "Hata:{FFFFFF} "%1)
	
#define SendWarningMessage(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TOMATO, "Uyarý:{FFFFFF} "%1)

#define SM1(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TOMATO, "Liberty:{FFFFFF} "%1)	
	
#define SM2(%0,%1) \
	SendClientMessageEx(%0, COLOR_SERVER2, "Liberty:{FFFFFF} "%1)	
	
#define SM3(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TOMATO, "Liberty: "%1)

#define SM4(%0,%1) \
	SendClientMessageEx(%0, COLOR_WHITE, "Liberty: "%1)	

#define SendBlackMarketMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_SERVER2, "KARA BORSA >> "%1)	
///PHONE && PAYPHONE && RADIO///
#define SendCellMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_GRAD2, "[ ! ] "%1)

#define SendPhoneMessage(%0,%1) \
	SendClientMessageEx(%0, COLOR_YELLOWG, "Operatör (telefon): "%1)

#define SendRadioMsg(%0,%1) \
	SendClientMessageEx(%0, COLOR_YELLOWMY, "Telsiz: "%1)

//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ADM CMD //////////////////

#define SendAdmMessage(%0) \          
	AMSG(COLOUR_TOMATO, "AdmCmd: "%0) 

#define SAM \
	SendAdmMessage

#define SendAdmMessageToAll(%0) \
	SendClientMessageToAllEx(COLOUR_TOMATO, "[Yönetim] "%0)
	// Âñåì èãðîêàì

#define SAMALL \
	SendAdmMessageToAll

#define SendAdmMessageToPlayer(%0,%1) \
	SendClientMessageEx(%0, COLOUR_TOMATO, "[Yönetim] "%1)
	// Èãðîêó

#define SAMPL\
	SendAdmMessageToPlayer

//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// ERRORS ///////////////////
#define SendCuffedMessage(%0)	SendClientMessageEx(%0, COLOUR_TOMATO, "Bilgi:{FFFFFF} Kelepçelisiniz.")
#define SendNotConnected(%0)	SendClientMessageEx(%0, COLOUR_TOMATO, "Bilgi:{FFFFFF} Kiþi oyunda deðil.")
#define SendNotNearPlayer(%0)	SendClientMessageEx(%0, COLOUR_TOMATO, "Bilgi:{FFFFFF} Kiþi sizden çok uzak.")
#define SendNotInVehicle(%0)	SendClientMessageEx(%0, COLOUR_TOMATO, "Bilgi:{FFFFFF} Araçta olmalýsýnýz.")
#define SendNotCash(%0)			SendClientMessageEx(%0, COLOUR_TOMATO, "Bilgi:{FFFFFF} Yeterli paranýz yok.")
#define SendNotAdmin(%0)		SendClientMessageEx(%0, COLOUR_TOMATO, "Bilgi:{FFFFFF} Yetkisiz komut kullandýnýz.")
///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////// OTHER ///////////////////

#define SendNoteMessage(%0,%1) \
	SendClientMessageEx(%0, -1, "Not: "%1)

#define SendErrorRadioMessage(%0,%1) \
	SendClientMessageEx(%0, 0xAFAFAFFF, "[Telsiz]:{DADADA} "%1)

#define SendFishMessage(%0,%1) \
	SendClientMessageEx(%0, -1, "Balýkçýlýk: "%1)

#define PRESSING(%0,%1) \
	(%0 & (%1))

#define HOLDING(%0) \
	((newkeys & (%0)) == (%0))

#define PRESSED(%0) \
	(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define RELEASED(%0) \
	(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))