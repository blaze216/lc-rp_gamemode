CMD:dekorasyon(playerid, params[])
{
	if (!PlayerInfo[playerid][pAdmin]) return SendErrorMessage(playerid, "Beta d�neminde bu sistem pasiftir.");
	
    if (GetPVarInt(playerid, "buy_furniture"))	return SendErrorMessage (playerid, "Zaten �u an dekorasyon sistemindesin.");
        
	new type = GetNearBuilding(playerid);
	if (type == -1) return SendErrorMessage(playerid, "M�lke yak�n olmal�s�n.");

	switch(type)
	{
		case 0: HouseFurn(playerid);
		case 1: BizFurn(playerid);
		case 2: GarageFurn(playerid);
	}

	Check3DMenu(playerid);
	return 1;
}