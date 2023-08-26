ShowProperty(playerid, id)
{
	new count, year, month, day, hour, minute, second;
	
	getdate(year, month, day);
	gettime(hour, minute, second);
	
    SendClientMessageEx(playerid, COLOR_SERVER2,"|____________________Mülkleriniz %s [%02d %s %i, %02d:%02d:%02d]____________________|", GetName(id), day, GetMonthName(month), year, hour, minute, second); //èìóùåñòâî
    
	for(new i; i != MAX_HOUSES; i++)
	{
	    if (HouseInfo[i][hID] == 0 || (HouseInfo[i][hOwnerID] != PlayerInfo[id][pID] && PlayerInfo[id][pRentKey] != HouseInfo[i][hID]))				continue;

        if (HouseInfo[i][hPosInt] == 0)												SendClientMessageEx(playerid, COLOR_STATS1, "> Ev [ID: %i] | Adres: %s", i, (!HouseInfo[i][hApart])?(GetHouseZone(i)):(GetApartmentZone(HouseInfo[i][hApart])));
		else																		SendClientMessageEx(playerid, COLOR_STATS1, "> Ev [ID: %i]", i);
        
		count++;
	}
	
	for(new i; i != MAX_BIZ; i++)
	{
	    if (BizInfo[i][bizID] == 0 || BizInfo[i][bizOwnerID] != PlayerInfo[id][pID])				continue;

        SendClientMessageEx(playerid, COLOR_STATS1, "> Mekan [ID: %i]", i);

        count++;
	}
	
	for(new i; i != MAX_GARAGES; i++)
	{
	    if (GarageInfo[i][garageID] == 0 || GarageInfo[i][garageOwner] != PlayerInfo[id][pID])	continue;

        SendClientMessageEx(playerid, COLOR_STATS1, "> Garaj [ID: %i]", i);

        count++;
	}
	
	if (count == 0 && playerid == id)	SendErrorMessage(playerid, "Herhangi bir mülkünüz yok.");
    if (count == 0 && playerid != id)	SendSyntaxMessage(playerid, "Kiþinin herhangi bir mülkü yok.");
    	
	return 1;
}

stock CreateLableText(playerid,lable[], text[])
{
    //if (GetPlayerState(playerid) != PLAYER_STATE_ONFOOT) return 1;
	if (GetPVarInt(playerid, #LableText) > 0)
	{
		PlayerTextDrawSetString(playerid, PlayerText:mulktext[playerid][0], lable);
		PlayerTextDrawSetString(playerid, PlayerText:mulktext[playerid][1], text);
		return 1;
	}

	//PlayerPlaySound(playerid,1054, 0.0, 0.0, 0.0);

	PlayerTextDrawSetString(playerid, PlayerText:mulktext[playerid][0], lable);
	PlayerTextDrawSetString(playerid, PlayerText:mulktext[playerid][1], text);

	PlayerTextDrawShow(playerid, PlayerText:mulkbilgi[playerid]);
	PlayerTextDrawShow(playerid, PlayerText:mulktext[playerid][0]);
	PlayerTextDrawShow(playerid, PlayerText:mulktext[playerid][1]);

	SetPVarInt(playerid, #LableText, 4);
    return 1;
}
