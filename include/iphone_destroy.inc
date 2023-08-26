	// iPhone - C-RP
	// By Dema

	//TD_iphone - 24
	//TD_iphone_block - 6
	//TD_iphone_name - 1
	//TD_iphone_button - 6
	//TD_iphone_menu - 7
	//TD_iphone_setting - 11
	//TD_iphone_list - 16
	//TD_iphone_contact - 5
	//TD_iphone_keypad - 34

	PlayerTextDrawDestroy(playerid, TD_iphone_name[playerid]);
	TD_iphone_name[playerid] = PlayerText:INVALID_TEXT_DRAW;

	for(new i; i != 34; i++)
	{
		PlayerTextDrawDestroy(playerid, TD_iphone_keypad[playerid][i]);
		TD_iphone_keypad[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

		if(i < 24)
		{
			PlayerTextDrawDestroy(playerid, TD_iphone[playerid][i]);
			TD_iphone[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(i < 6)
		{
			PlayerTextDrawDestroy(playerid, TD_iphone_block[playerid][i]);
			TD_iphone_block[playerid][i] = PlayerText:INVALID_TEXT_DRAW;

			PlayerTextDrawDestroy(playerid, TD_iphone_button[playerid][i]);
			TD_iphone_button[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(i < 12)
		{
			PlayerTextDrawDestroy(playerid, TD_iphone_menu[playerid][i]);
			TD_iphone_menu[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(i < 11)
		{
			PlayerTextDrawDestroy(playerid, TD_iphone_setting[playerid][i]);
			TD_iphone_setting[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(i < 16)
		{
			PlayerTextDrawDestroy(playerid, TD_iphone_list[playerid][i]);
			TD_iphone_list[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}

		if(i < 5)
		{
			PlayerTextDrawDestroy(playerid, TD_iphone_contact[playerid][i]);
			TD_iphone_contact[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
		}
	}
	CancelSelectTextDraw(playerid);
