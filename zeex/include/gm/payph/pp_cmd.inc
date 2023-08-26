alias:ankesorlutelefon("paypyhone");
CMD:ankesorlutelefon(playerid, params[])
{
    if (PlayerInfo[playerid][pInjured] != 0 || GetPVarInt(playerid, "Freeze") || pTemp[playerid][pTaserTime] || pTemp[playerid][pCuffed])
		return SendErrorMessage(playerid, "Bu iþlemi þu an kullanamazsýnýz.");

	new id = -1;
	if ((id = Payphone_Nearest(playerid)) == -1)
	    return SendErrorMessage(playerid, "Yakýnýnýzda ankesörlü telefon bulunmuyor.");
	    
	if (PayphoneInfo[id][phUsed] != INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Ankesörlü telefon zaten kullanýmda.");
	    
	if (IsPlayerPhoneCreated(playerid))
	    return SendErrorMessage(playerid, "Telefonunuzu zaten kullanýyorsunuz.");
	
	if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
	    return SendErrorMessage(playerid, "Devam eden bir çaðrýnýz var. Kapatmak için: /tkapat");

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

		SM2(playerid,"Aramayý cevapladýnýz.");
		SM2(targetid,"Karþý taraf aramayý cevapladý.");
	}
	
	PlayerOnPayphone(playerid);
	return 1;
}
