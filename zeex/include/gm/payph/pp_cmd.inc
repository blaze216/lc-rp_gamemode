alias:ankesorlutelefon("paypyhone");
CMD:ankesorlutelefon(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
		return SendErrorMessage(playerid, "Bu i�lemi �u an kullanamazs�n�z.");

	new id = -1;
	if ((id = Payphone_Nearest(playerid)) == -1)
	    return SendErrorMessage(playerid, "Yak�n�n�zda ankes�rl� telefon bulunmuyor.");
	    
	if (PayphoneInfo[id][phUsed] != INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Ankes�rl� telefon zaten kullan�mda.");
	    
	if (IsPlayerPhoneCreated(playerid))
	    return SendErrorMessage(playerid, "Telefonunuzu zaten kullan�yorsunuz.");
	
	if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
	    return SendErrorMessage(playerid, "Devam eden bir �a�r�n�z var. Kapatmak i�in: /tkapat");

	pTemp[playerid][pPayphone] = id;
	PayphoneInfo[id][phUsed] = playerid;

	new info[128];
	format(info, sizeof(info), "Imleci kullanmak icin '~y~/fare~w~' komutunu ~y~kullanin~w~.~n~Ankesorlu telefonun numarasi:~y~ %i", PayphoneInfo[id][phNumber]);
	InfoMSG(playerid, info, 5);

	SetPlayerFacingAngle(playerid, PayphoneInfo[id][phRZ]); 
	SetCameraBehindPlayer(playerid);
	
	if (PayphoneInfo[id][phState] == PAYPHONE_STATE_RINGING) 
	{
		PayphoneInfo[id][phState] = PAYPHONE_STATE_INCALL;

		new targetid = PayphoneInfo[id][phCaller];

		pTemp[playerid][pCallLine] = targetid;
		pTemp[targetid][pCallLine] = playerid;

		pTemp[playerid][pCallStatus] = 2;
		pTemp[playerid][pCallTime] = 0;

		pTemp[targetid][pCallStatus] = 2;
		pTemp[targetid][pCallTime] = 0;
		
		Update_Payphone(id);

		if (0 == IsPlayerPhoneCreated(targetid))
	    	Phone_Create(targetid);
		else
		{
			Update_Phone(targetid);
		}

		SM2(playerid,"Aramay� cevaplad�n�z.");
		SM2(targetid,"Kar�� taraf aramay� cevaplad�.");
	}
	
	PlayerOnPayphone(playerid);
	return 1;
}
