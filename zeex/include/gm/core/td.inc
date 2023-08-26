TD_OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if (pTemp[playerid][p3DMenu] != -1 && clickedid == Text:INVALID_TEXT_DRAW)
	{
    	Destroy3DMenu(pTemp[playerid][p3DMenu]);
		pTemp[playerid][p3DMenu] = -1;
		pc_cmd_dekorasyon(playerid, "");
		return 1;
	}

	if (GetPVarInt(playerid, #restaurant) == 1 && clickedid == Text:INVALID_TEXT_DRAW)	return RestaurantMenuHide(playerid);
    if (clickedid == TD_restaurant[3])													return RestaurantMenuHide(playerid);
	return 1;
}