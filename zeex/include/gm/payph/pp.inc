PP_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (clickedid == PP_Framework[2])
	{
	    new hour, minute, second, str[64];
		gettime(hour, minute, second);
		format(str, sizeof(str), "%02d:%02d", hour, minute);

	    PlayerTextDrawSetString(playerid, PP_Btn[playerid][0], str);
  		pTemp[playerid][pPayphoneNumStr] = EOS;
		
		//PlayerTextDrawHide(playerid, PP_Btn[playerid][0]);
		//PlayerTextDrawShow(playerid, PP_Btn[playerid][0]);
  		return 1;
	}
	if (clickedid == PP_Framework[8])
	{		
		return cancelPayphone(playerid);
	}
	if (clickedid == PP_Framework[7])
	{
	    if (GetCash(playerid) < 2) return SendErrorMessage(playerid, "Yeterli paran�z yok, �zerinizde 2 dolar�n�z olmal�.");
		if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
	    	return SendCellMessage(playerid, "Devam eden bir �a�r�n�z mevcut. Sonland�rmak i�in /tkapat");

	    PlayerTextDrawSetString(playerid, PP_Btn[playerid][0], "Aran�yor ..");
		
		pc_cmd_server_ame(playerid, "ankes�rl� telefona bozuk para att�.");
		GiveCash(playerid,-2);
		GameTextForPlayer(playerid, "~r~-$2.", 3000, 1);

		pc_cmd_ara(playerid, sprintf("%s", pTemp[playerid][pPayphoneNumStr]));
		pTemp[playerid][pPayphoneNumStr] = EOS;
	    return 1;
	}
	return 1;
}

PP_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	new qustr[128];

	for(new i = 1; i < 10; i ++)
    {
    	if (playertextid == PP_Btn[playerid][i])
    	{
			if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
	    		return SendCellMessage(playerid, "Devam eden bir �a�r�n�z mevcut. Sonland�rmak i�in /tkapat");

			if (strlen(pTemp[playerid][pPayphoneNumStr]) >= 8) return 1;
    	    format(pTemp[playerid][pPayphoneNumStr], 64, "%s%d", pTemp[playerid][pPayphoneNumStr], i);
			format(qustr, sizeof(qustr), "%s", pTemp[playerid][pPayphoneNumStr]);
		    PlayerTextDrawSetString(playerid, PP_Btn[playerid][0], qustr);
				
			//PlayerTextDrawHide(playerid, PP_Btn[playerid][0]);
			//PlayerTextDrawShow(playerid, PP_Btn[playerid][0]);
    	}
    }
   	if (playertextid == PP_Btn[playerid][10])
   	{
		if (pTemp[playerid][pCallLine] != INVALID_PLAYER_ID || pTemp[playerid][pEmergency])
			return SendCellMessage(playerid, "Devam eden bir �a�r�n�z mevcut. Sonland�rmak i�in /tkapat");
		
		if (strlen(pTemp[playerid][pPayphoneNumStr]) >= 8) return 1;
   	    format(pTemp[playerid][pPayphoneNumStr], 64, "%s0", pTemp[playerid][pPayphoneNumStr]);
		format(qustr, sizeof(qustr), "%s", pTemp[playerid][pPayphoneNumStr]);
	    PlayerTextDrawSetString(playerid, PP_Btn[playerid][0], qustr);
			
		//PlayerTextDrawHide(playerid, PP_Btn[playerid][0]);
		//PlayerTextDrawShow(playerid, PP_Btn[playerid][0]); // �� ��
   	}
	return 1;
}	

PP_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rz)
{
    if (GetPVarInt(playerid, #edit_pp) != 0 && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL))
	{
		new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;

		GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
		GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		
	    new id = GetPVarInt(playerid, #edit_pp)-1;
	    
		DeletePVar(playerid, #edit_pp);
	    if (id < 0 || id >= MAX_PAYPHONES || !PayphoneInfo[id][phID]) 	return SendErrorMessage(playerid, "Ankes�rl� telefon bulunamad�.");
	    if (objectid != PayphoneInfo[id][phObj])						return SendErrorMessage(playerid, "Ankes�rl� telefon d�zenlenirken hata olu�tu");

		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, 0.0, 0.0, rz);

        GetDynamicObjectPos(objectid, PayphoneInfo[id][phX], PayphoneInfo[id][phY], PayphoneInfo[id][phZ]);
       	PayphoneInfo[id][phRZ] = rz;

		Update_Payphone(id);
        
		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "UPDATE `payphones` SET `x`=%f,`y`=%f,`z`=%f,`rz`=%f WHERE `id`=%i", x, y, z, rz, PayphoneInfo[id][phID]);
		mysql_tquery(dbHandle, query);

		SendAdmMessageToPlayer(playerid, "Ankes�rl� telefon pozisyonu g�ncellendi: [ID: %i]", id);
	}
    return 1;
}
