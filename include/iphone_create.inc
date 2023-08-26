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

	new model = PlayerInfo[playerid][pPhoneModel];
	//Оўновнаў панель
	TD_iphone[playerid][0] = CreatePlayerTextDraw(playerid, 507.000183, 195.792556, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][0], 16.000000, 16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][0], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][0], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][0], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][0]);

	TD_iphone[playerid][1] = CreatePlayerTextDraw(playerid, 506.666839, 404.199951, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][1], 16.000000, -16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][1], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][1], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][1], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][1]);

	TD_iphone[playerid][2] = CreatePlayerTextDraw(playerid, 578.666870, 404.199951, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][2], 16.000000, -16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][2], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][2], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][2], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][2]);

	TD_iphone[playerid][3] = CreatePlayerTextDraw(playerid, 578.666870, 195.792541, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][3], 16.000000, 16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][3], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][3], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][3], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][3]);

	TD_iphone[playerid][4] = CreatePlayerTextDraw(playerid, 507.000061, 202.844375, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][4], 87.666656, 194.962951);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][4], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][4], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][4], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][4]);

	TD_iphone[playerid][5] = CreatePlayerTextDraw(playerid, 513.666564, 195.548095, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][5], 74.666641, 208.651809);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][5], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][5], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][5], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][5], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][5]);

	TD_iphone[playerid][6] = CreatePlayerTextDraw(playerid, 507.333496, 196.377746, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][6], 16.000000, 16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][6], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][6], phone_model_color[model]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][6], phone_model_color[model]);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][6], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][6]);

	TD_iphone[playerid][7] = CreatePlayerTextDraw(playerid, 507.333496, 403.540649, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][7], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][7], 16.000000, -16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][7], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][7], phone_model_color[model]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][7], phone_model_color[model]);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][7], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][7]);

	TD_iphone[playerid][8] = CreatePlayerTextDraw(playerid, 578.000244, 403.540649, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][8], 16.000000, -16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][8], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][8], phone_model_color[model]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][8], phone_model_color[model]);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][8], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][8]);

	TD_iphone[playerid][9] = CreatePlayerTextDraw(playerid, 578.000305, 196.377746, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][9], 16.000000, 16.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][9], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][9], phone_model_color[model]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][9], phone_model_color[model]);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][9], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][9]);

	TD_iphone[playerid][10] = CreatePlayerTextDraw(playerid, 514.666809, 196.622222, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][10], 72.000022, 206.992568);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][10], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][10], phone_model_color[model]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][10], phone_model_color[model]);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][10], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][10]);

	TD_iphone[playerid][11] = CreatePlayerTextDraw(playerid, 507.566650, 204.674133, "LD_SPAC:white");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][11], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][11], 86.333419, 191.229660);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][11], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][11], phone_model_color[model]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][11], phone_model_color[model]);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][11], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][11]);

	TD_iphone[playerid][12] = CreatePlayerTextDraw(playerid, 514.122497, 222.566604, "window");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][12], 0.000000, 17.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][12], 587.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][12], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][12], 16777215);
	PlayerTextDrawUseBox(playerid, TD_iphone[playerid][12], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][12], (PlayerInfo[playerid][pPhoneOff] == 1)?(0x000000FF):(phone_window[PlayerInfo[playerid][pPhoneStyle]]));
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][12], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][12], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][12]);

	TD_iphone[playerid][13] = CreatePlayerTextDraw(playerid, 548.966979, 202.900024, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][13], 3.333292, 4.148138);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][13], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][13], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][13], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][13], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][13], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][13]);

	TD_iphone[playerid][14] = CreatePlayerTextDraw(playerid, 544.999877, 209.896240, "ld_poke:cd1d");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][14], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][14], 12.333331, 2.074084);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][14], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][14], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][14], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][14], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][14], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][14]);

	TD_iphone[playerid][15] = CreatePlayerTextDraw(playerid, 541.000366, 210.066589, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][15], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][15], 1.333292, 1.244433);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][15], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][15], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][15], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][15], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][15], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][15], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][15]);

	TD_iphone[playerid][16] = CreatePlayerTextDraw(playerid, 543.333618, 381.711090, "ld_pool:ball");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][16], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][16], 16.333269, 18.251844);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][16], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][16], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][16], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][16], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][16], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][16], 0);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][16]);

	TD_iphone[playerid][17] = CreatePlayerTextDraw(playerid, 514.437011, 222.350006, "panel");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][17], 0.000000, 0.750001);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][17], 587.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][17], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][17], 16777215);
	PlayerTextDrawUseBox(playerid, TD_iphone[playerid][17], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][17], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][17], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][17], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][17], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][17], 0);

	if(PlayerInfo[playerid][pPhoneOff] == 0)
		PlayerTextDrawShow(playerid, TD_iphone[playerid][17]);

	new hours,
		minutes,
		str_time[16];

	gettime(hours, minutes);

	format(str_time, 6, "%02i:%02i", hours, minutes);

	TD_iphone[playerid][18] = CreatePlayerTextDraw(playerid, 543.806396, 222.599914, str_time); // центральнаў дата
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][18], 0.168999, 0.754166);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][18], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][18], 255);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][18], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][18], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][18], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][18], 0);

	if(PlayerInfo[playerid][pPhoneOff] == 0)
		PlayerTextDrawShow(playerid, TD_iphone[playerid][18]);

	TD_iphone[playerid][19] = CreatePlayerTextDraw(playerid, 587.400756, 230.716644, "battery_main");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][19], 0.000000, -1.100000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][19], 573.900756, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][19], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][19], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone[playerid][19], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][19], -176);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][19], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][19], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][19], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][19], 0);
	if(PlayerInfo[playerid][pPhoneOff] == 0)
		PlayerTextDrawShow(playerid, TD_iphone[playerid][19]);

	TD_iphone[playerid][20] = CreatePlayerTextDraw(playerid, 587.103149, 227.033355, "battery_small");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][20], 0.000000, -0.300000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][20], 585.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][20], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][20], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone[playerid][20], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][20], -176);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][20], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][20], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][20], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][20], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][20], 0);
	if(PlayerInfo[playerid][pPhoneOff] == 0)
		PlayerTextDrawShow(playerid, TD_iphone[playerid][20]);

	TD_iphone[playerid][21] = CreatePlayerTextDraw(playerid, 582.102050, 230.716644, "battery_green");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][21], 0.000000, -1.100000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][21], 573.701293, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][21], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][21], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone[playerid][21], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone[playerid][21], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][21], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][21], 13959423);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][21], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][21], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][21], 0);
	if(PlayerInfo[playerid][pPhoneOff] == 0)
		PlayerTextDrawShow(playerid, TD_iphone[playerid][21]);

	//544.333374
	TD_iphone[playerid][22] = CreatePlayerTextDraw(playerid, 540.934204, 379.810974, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][22], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone[playerid][22], 21.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][22], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][22], -1061109505);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][22], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][22], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][22], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][22], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][22], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][22], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone[playerid][22], true);
	PlayerTextDrawShow(playerid, TD_iphone[playerid][22]);

	TD_iphone[playerid][23] = CreatePlayerTextDraw(playerid, 514.713500, 222.399902, "ooooo");
	PlayerTextDrawLetterSize(playerid, TD_iphone[playerid][23], 0.127997, 0.724999);
	PlayerTextDrawAlignment(playerid, TD_iphone[playerid][23], 1);
	PlayerTextDrawColor(playerid, TD_iphone[playerid][23], 255);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][23], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone[playerid][23], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone[playerid][23], 255);
	PlayerTextDrawFont(playerid, TD_iphone[playerid][23], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone[playerid][23], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone[playerid][23], 0);
	if(PlayerInfo[playerid][pPhoneOff] == 0)
		PlayerTextDrawShow(playerid, TD_iphone[playerid][23]);


	//Блокировка
	TD_iphone_block[playerid][0] = CreatePlayerTextDraw(playerid, 550.895629, 237.815246, str_time); //большаў дата (блокировка)
	PlayerTextDrawLetterSize(playerid, TD_iphone_block[playerid][0], 0.308499, 2.778331);
	PlayerTextDrawAlignment(playerid, TD_iphone_block[playerid][0], 2);
	PlayerTextDrawColor(playerid, TD_iphone_block[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_block[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_block[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_block[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_block[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][0], 0);

	new month,
		day;

	new month_name[12][12] = {"Ocak","Subat","Mart","Nisan","Mayis","Haziran","Temmuz","Agustos","Eylul","Ekim","Kasim","Aralik"};
	getdate(_, month, day);
	format(str_time, 16, "%02i %s", day, month_name[month-1]);

	TD_iphone_block[playerid][1] = CreatePlayerTextDraw(playerid, 550.499145, 261.881805, str_time);// дата (блокировка)
	PlayerTextDrawLetterSize(playerid, TD_iphone_block[playerid][1], 0.164498, 1.127500);
	PlayerTextDrawAlignment(playerid, TD_iphone_block[playerid][1], 2);
	PlayerTextDrawColor(playerid, TD_iphone_block[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_block[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_block[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_block[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_block[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][1], 0);

	TD_iphone_block[playerid][2] = CreatePlayerTextDraw(playerid, 551.000000, 363.250061, "Acmak icin dokunun"); // текўт (блокировка)
	PlayerTextDrawLetterSize(playerid, TD_iphone_block[playerid][2], 0.176998, 1.022497);
	PlayerTextDrawAlignment(playerid, TD_iphone_block[playerid][2], 2);
	PlayerTextDrawColor(playerid, TD_iphone_block[playerid][2], 255);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_block[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_block[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_block[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_block[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][2], 0);

	TD_iphone_block[playerid][3] = CreatePlayerTextDraw(playerid, 550.500000, 282.332489, "iMesaj~n~~l~8506236"); // ўообщение 1(блокировка)
	PlayerTextDrawLetterSize(playerid, TD_iphone_block[playerid][3], 0.177496, 0.783333);
	PlayerTextDrawTextSize(playerid, TD_iphone_block[playerid][3], 10.000000, 65.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_block[playerid][3], 2);
	PlayerTextDrawColor(playerid, TD_iphone_block[playerid][3], -2139062017);
	PlayerTextDrawUseBox(playerid, TD_iphone_block[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_block[playerid][3], -134744752);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_block[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_block[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_block[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_block[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_block[playerid][3], true);

	TD_iphone_block[playerid][4] = CreatePlayerTextDraw(playerid, 550.500000, 303.933807, "iMesaj~n~~l~Amanda Morrison");// ўообщение 2(блокировка)
	PlayerTextDrawLetterSize(playerid, TD_iphone_block[playerid][4], 0.177496, 0.783333);
	PlayerTextDrawTextSize(playerid, TD_iphone_block[playerid][4], 10.000000, 65.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_block[playerid][4], 2);
	PlayerTextDrawColor(playerid, TD_iphone_block[playerid][4], -2139062017);
	PlayerTextDrawUseBox(playerid, TD_iphone_block[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_block[playerid][4], -134744752);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_block[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_block[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_block[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_block[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_block[playerid][4], true);

	TD_iphone_block[playerid][5] = CreatePlayerTextDraw(playerid, 550.500000, 326.135162, "iMesaj~n~~l~Morgan Cole"); // ўообщение 3(блокировка)
	PlayerTextDrawLetterSize(playerid, TD_iphone_block[playerid][5], 0.177496, 0.783333);
	PlayerTextDrawTextSize(playerid, TD_iphone_block[playerid][5], 10.000000, 65.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_block[playerid][5], 2);
	PlayerTextDrawColor(playerid, TD_iphone_block[playerid][5], -2139062017);
	PlayerTextDrawUseBox(playerid, TD_iphone_block[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_block[playerid][5], -134744752);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_block[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_block[playerid][5], 255);
	PlayerTextDrawFont(playerid, TD_iphone_block[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_block[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_block[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_block[playerid][5], true);

	//Оазвание контакта, кому звонишь, кто звонит и т.д.
	TD_iphone_name[playerid] = CreatePlayerTextDraw(playerid, 550.500000, 248.916687, "Mesaj~n~00:23");
	PlayerTextDrawLetterSize(playerid, TD_iphone_name[playerid], 0.165500, 0.859165);
	PlayerTextDrawAlignment(playerid, TD_iphone_name[playerid], 2);
	PlayerTextDrawColor(playerid, TD_iphone_name[playerid], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_name[playerid], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_name[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_name[playerid], 255);
	PlayerTextDrawFont(playerid, TD_iphone_name[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_name[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_name[playerid], 0);

	//Когда звонишь ты, либо уже поднўл трубку
	TD_iphone_button[playerid][0] = CreatePlayerTextDraw(playerid, 537.699951, 344.833404, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_button[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_button[playerid][0], 26.000000, 26.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_button[playerid][0], 1);
	PlayerTextDrawColor(playerid, TD_iphone_button[playerid][0], -12898049);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_button[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_button[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_button[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_button[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_button[playerid][0], true);

	TD_iphone_button[playerid][1] = CreatePlayerTextDraw(playerid, 547.999755, 351.783264, "c");
	PlayerTextDrawLetterSize(playerid, TD_iphone_button[playerid][1], 0.240997, 1.191665);
	PlayerTextDrawAlignment(playerid, TD_iphone_button[playerid][1], 1);
	PlayerTextDrawColor(playerid, TD_iphone_button[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_button[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_button[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_button[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_button[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][1], 0);

	//Входўщий вызов
	TD_iphone_button[playerid][2] = CreatePlayerTextDraw(playerid, 517.804809, 344.833404, "LD_BEAT:chit"); //Краўнаў кнопка
	PlayerTextDrawLetterSize(playerid, TD_iphone_button[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_button[playerid][2], 26.000000, 26.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_button[playerid][2], 1);
	PlayerTextDrawColor(playerid, TD_iphone_button[playerid][2], -12898049);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_button[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_button[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_button[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_button[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_button[playerid][2], true);

	TD_iphone_button[playerid][3] = CreatePlayerTextDraw(playerid, 527.904663, 351.783264, "c");
	PlayerTextDrawLetterSize(playerid, TD_iphone_button[playerid][3], 0.240997, 1.191665);
	PlayerTextDrawAlignment(playerid, TD_iphone_button[playerid][3], 1);
	PlayerTextDrawColor(playerid, TD_iphone_button[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_button[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_button[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_button[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_button[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][3], 0);

	TD_iphone_button[playerid][4] = CreatePlayerTextDraw(playerid, 557.795043, 344.833404, "LD_BEAT:chit");//Зеленаў кнопка
	PlayerTextDrawLetterSize(playerid, TD_iphone_button[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_button[playerid][4], 26.000000, 26.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_button[playerid][4], 1);
	PlayerTextDrawColor(playerid, TD_iphone_button[playerid][4], 1289381119);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_button[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_button[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_button[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_button[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_button[playerid][4], true);

	TD_iphone_button[playerid][5] = CreatePlayerTextDraw(playerid, 573.093627, 351.883270, "c");
	PlayerTextDrawLetterSize(playerid, TD_iphone_button[playerid][5], -0.239999, 1.191665);
	PlayerTextDrawAlignment(playerid, TD_iphone_button[playerid][5], 1);
	PlayerTextDrawColor(playerid, TD_iphone_button[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_button[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_button[playerid][5], 255);
	PlayerTextDrawFont(playerid, TD_iphone_button[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_button[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_button[playerid][5], 0);

	//Менў
	TD_iphone_menu[playerid][0] = CreatePlayerTextDraw(playerid, 515.500, 237.966, "~n~~n~~n~Rehber");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][0], 0.184, 0.882);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][0], 550.749, 30.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][0], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][0], 8388863);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][0], 1);

	TD_iphone_menu[playerid][1] = CreatePlayerTextDraw(playerid, 570.599, 237.983, "~n~~n~~n~~n~~n~  Ayarlar");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][1], 0.184, 0.882);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][1], 60.000, 30.118);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][1], 2);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][1], 1768516095);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][1], 1);

	TD_iphone_menu[playerid][2] = CreatePlayerTextDraw(playerid, 515.500, 275.851, "~n~SMS");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][2], 0.182, 0.995);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][2], 551.000, 20.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][2], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][2], -5963521);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][2], 1);

	TD_iphone_menu[playerid][3] = CreatePlayerTextDraw(playerid, 550.591, 299.053, "~n~Arama kayitlari~n~~n~");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][3], 0.184, 0.941);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][3], 23.000, 70.750);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][3], 2);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][3], -2147483393);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][3], 1);

	TD_iphone_menu[playerid][4] = CreatePlayerTextDraw(playerid, 554.896, 329.934, "~n~~n~   Kamera");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][4], 0.184, 0.882);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][4], 585.927, 20.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][4], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][4], 780883967);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][4], 1);

	TD_iphone_menu[playerid][5] = CreatePlayerTextDraw(playerid, 515.106, 329.851, "~n~~n~GPS");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][5], 0.184, 0.882);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][5], 550.000, 20.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][5], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][5], 512819199);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][5], 16711935);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][5], 1);

	TD_iphone_menu[playerid][6] = CreatePlayerTextDraw(playerid, 550.299, 358.782, ". . .~n~. . .~n~. . .");
	PlayerTextDrawLetterSize(playerid, TD_iphone_menu[playerid][6], 0.192, 0.564);
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][6], 12.000, 70.569);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][6], 2);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][6], -1061109505);
	PlayerTextDrawUseBox(playerid, TD_iphone_menu[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_menu[playerid][6], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][6], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_menu[playerid][6], 1);

	TD_iphone_menu[playerid][7] = CreatePlayerTextDraw(playerid, 535.000, 248.000, "HUD:radar_gangG");
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][7], 14.000, 20.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][7], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][7], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][7], 1);

	TD_iphone_menu[playerid][8] = CreatePlayerTextDraw(playerid, 535.000, 340.000, "HUD:radar_north");
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][8], 14.000, 14.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][8], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][8], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][8], 1);

	TD_iphone_menu[playerid][9] = CreatePlayerTextDraw(playerid, 535.000, 279.000, "LD_CHAT:goodcha");
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][9], 14.000, 14.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][9], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][9], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][9], 1);

	TD_iphone_menu[playerid][10] = CreatePlayerTextDraw(playerid, 552.000, 264.000, "HUD:radardisc");
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][10], 36.000, 24.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][10], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][10], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][10], 1);

	TD_iphone_menu[playerid][11] = CreatePlayerTextDraw(playerid, 552.000, 343.000, "HUD:radardisc");
	PlayerTextDrawTextSize(playerid, TD_iphone_menu[playerid][11], 36.000, -16.000);
	PlayerTextDrawAlignment(playerid, TD_iphone_menu[playerid][11], 1);
	PlayerTextDrawColor(playerid, TD_iphone_menu[playerid][11], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_menu[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_menu[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_menu[playerid][11], 255);
	PlayerTextDrawFont(playerid, TD_iphone_menu[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_menu[playerid][11], 1);

	//Оаўтройки
	TD_iphone_setting[playerid][0] = CreatePlayerTextDraw(playerid, 550.499877, 240.166717, "Cihazi kapat");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][0], 0.152499, 1.010831);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][0], 10.000000, 71.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][0], 2);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_setting[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][0], -1523963137);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][0], true);

	TD_iphone_setting[playerid][1] = CreatePlayerTextDraw(playerid, 550.499877, 254.767608, "Ucak Modu: Kapali");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][1], 0.152499, 1.010831);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][1], 10.000000, 71.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][1], 2);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_setting[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][1], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][1], true);

	TD_iphone_setting[playerid][2] = CreatePlayerTextDraw(playerid, 550.499877, 269.168487, "Ses: Acik");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][2], 0.152499, 1.010831);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][2], 10.000000, 71.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][2], 2);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_setting[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][2], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][2], true);

	TD_iphone_setting[playerid][3] = CreatePlayerTextDraw(playerid, 549.922485, 290.016357, "Tema Rengi:");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][3], 0.162499, 1.010831);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][3], 2);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][3], 0);

	TD_iphone_setting[playerid][4] = CreatePlayerTextDraw(playerid, 529.300048, 303.182952, "theme_box");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][4], 0.000000, 3.799999);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][4], 570.800048, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][4], 1);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_setting[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_setting[playerid][4], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][4], 0);

	TD_iphone_setting[playerid][5] = CreatePlayerTextDraw(playerid, 514.000000, 317.166656, "LD_BEAT:left");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][5], 11.000000, 14.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][5], 1);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][5], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][5], true);

	TD_iphone_setting[playerid][6] = CreatePlayerTextDraw(playerid, 575.000000, 317.166656, "LD_BEAT:right");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][6], 11.000000, 14.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][6], 1);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][6], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][6], true);

	TD_iphone_setting[playerid][7] = CreatePlayerTextDraw(playerid, 549.922485, 346.519805, "SES:");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][7], 0.162499, 1.010831);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][7], 2);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][7], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][7], 0);

	TD_iphone_setting[playerid][8] = CreatePlayerTextDraw(playerid, 514.000000, 355.168975, "LD_BEAT:left");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][8], 11.000000, 14.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][8], 1);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][8], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][8], true);

	TD_iphone_setting[playerid][9] = CreatePlayerTextDraw(playerid, 575.000000, 355.168975, "LD_BEAT:right");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_setting[playerid][9], 11.000000, 14.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][9], 1);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][9], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_setting[playerid][9], true);

	TD_iphone_setting[playerid][10] = CreatePlayerTextDraw(playerid, 549.722534, 358.220520, "sarki.mp3");
	PlayerTextDrawLetterSize(playerid, TD_iphone_setting[playerid][10], 0.128999, 0.835833);
	PlayerTextDrawAlignment(playerid, TD_iphone_setting[playerid][10], 2);
	PlayerTextDrawColor(playerid, TD_iphone_setting[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_setting[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_setting[playerid][10], 255);
	PlayerTextDrawFont(playerid, TD_iphone_setting[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_setting[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_setting[playerid][10], 0);
	//Спиўок
	TD_iphone_list[playerid][0] = CreatePlayerTextDraw(playerid, 578.899414, 238.416641, "scroll");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][0], 0.000000, 14.934082);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][0], 585.099487, 0.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][0], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][0], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][0], 0);

	TD_iphone_list[playerid][2] = CreatePlayerTextDraw(playerid, 576.099975, 363.833404, "LD_BEAT:down");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][2], 12.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][2], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][2], true);

	TD_iphone_list[playerid][1] = CreatePlayerTextDraw(playerid, 576.099975, 238.733489, "LD_BEAT:up");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][1], 12.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][1], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][1], true);

	TD_iphone_list[playerid][3] = CreatePlayerTextDraw(playerid, 517.000000, 238.416641, "Kisi ekle");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][3], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][3], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][3], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][3], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][3], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][3], true);

	TD_iphone_list[playerid][4] = CreatePlayerTextDraw(playerid, 517.000000, 252.517501, "2. Andy");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][4], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][4], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][4], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][4], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][4], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][4], true);

	TD_iphone_list[playerid][5] = CreatePlayerTextDraw(playerid, 517.000000, 266.418334, "3. Polis");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][5], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][5], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][5], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][5], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][5], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][5], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][5], true);

	TD_iphone_list[playerid][6] = CreatePlayerTextDraw(playerid, 517.000000, 280.219177, "4. Job");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][6], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][6], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][6], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][6], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][6], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][6], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][6], true);

	TD_iphone_list[playerid][7] = CreatePlayerTextDraw(playerid, 517.000000, 294.320037, "5. Clark");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][7], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][7], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][7], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][7], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][7], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][7], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][7], true);

	TD_iphone_list[playerid][8] = CreatePlayerTextDraw(playerid, 517.000000, 308.220886, "6. Bank");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][8], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][8], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][8], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][8], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][8], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][8], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][8], true);

	TD_iphone_list[playerid][9] = CreatePlayerTextDraw(playerid, 517.000000, 322.521759, "7. Luis Cook");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][9], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][9], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][9], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][9], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][9], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][9], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][9], true);

	TD_iphone_list[playerid][10] = CreatePlayerTextDraw(playerid, 517.000000, 336.222595, "8. 327890");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][10], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][10], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][10], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][10], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][10], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][10], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][10], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][10], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][10], true);

	TD_iphone_list[playerid][11] = CreatePlayerTextDraw(playerid, 517.000000, 350.223449, "9. Jeremy Wood");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][11], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][11], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][11], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][11], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][11], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][11], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][11], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][11], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][11], true);

	TD_iphone_list[playerid][12] = CreatePlayerTextDraw(playerid, 517.000000, 364.124298, "10. Boss");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][12], 0.143999, 0.975831);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][12], 574.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][12], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][12], 255);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][12], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][12], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][12], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][12], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][12], true);

	//Иўториў вызовов
	TD_iphone_list[playerid][13] = CreatePlayerTextDraw(playerid, 515.000000, 237.833389, "Time: 22:05      12/05/2016~n~Incoming~n~~n~123456789012345678901234~n~Missed call");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][13], 0.119500, 0.912499);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][13], 574.449462, 40.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][13], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][13], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][13], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][13], -1523963137);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][13], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][13], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][13], true);

	TD_iphone_list[playerid][14] = CreatePlayerTextDraw(playerid, 515.000000, 285.183746, "Time: 22:05      Sept 15 2016~n~Outcoming~n~~n~123456789012345678901234~n~Time call: 00:24");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][14], 0.119500, 0.912499);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][14], 574.000000, 40.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][14], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][14], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][14], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][14], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][14], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][14], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][14], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][14], true);

	TD_iphone_list[playerid][15] = CreatePlayerTextDraw(playerid, 515.000000, 332.317047, "Time: 22:05      12/05/2016~n~Incoming~n~~n~123456789012345678901234~n~Time call: 00:24");
	PlayerTextDrawLetterSize(playerid, TD_iphone_list[playerid][15], 0.119500, 0.912499);
	PlayerTextDrawTextSize(playerid, TD_iphone_list[playerid][15], 574.399414, 40.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_list[playerid][15], 1);
	PlayerTextDrawColor(playerid, TD_iphone_list[playerid][15], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_list[playerid][15], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_list[playerid][15], 8388863);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_list[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_list[playerid][15], 255);
	PlayerTextDrawFont(playerid, TD_iphone_list[playerid][15], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_list[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_list[playerid][15], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_list[playerid][15], true);
	//Контакт инфо
	TD_iphone_contact[playerid][0] = CreatePlayerTextDraw(playerid, 550.500000, 248.916687, "Amanda Morrison~n~(8915450)");
	PlayerTextDrawLetterSize(playerid, TD_iphone_contact[playerid][0], 0.165500, 0.859165);
	PlayerTextDrawAlignment(playerid, TD_iphone_contact[playerid][0], 2);
	PlayerTextDrawColor(playerid, TD_iphone_contact[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_contact[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_contact[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_contact[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_contact[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][0], 0);

	TD_iphone_contact[playerid][1] = CreatePlayerTextDraw(playerid, 550.699951, 280.133911, "Ara");
	PlayerTextDrawLetterSize(playerid, TD_iphone_contact[playerid][1], 0.200999, 1.034165);
	PlayerTextDrawTextSize(playerid, TD_iphone_contact[playerid][1], 10.000000, 68.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_contact[playerid][1], 2);
	PlayerTextDrawColor(playerid, TD_iphone_contact[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_contact[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][1], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_contact[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_contact[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_contact[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_contact[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_contact[playerid][1], true);

	TD_iphone_contact[playerid][2] = CreatePlayerTextDraw(playerid, 550.699951, 294.634796, "Mesaj at");
	PlayerTextDrawLetterSize(playerid, TD_iphone_contact[playerid][2], 0.200999, 1.034165);
	PlayerTextDrawTextSize(playerid, TD_iphone_contact[playerid][2], 10.000000, 68.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_contact[playerid][2], 2);
	PlayerTextDrawColor(playerid, TD_iphone_contact[playerid][2], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_contact[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][2], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_contact[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_contact[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_contact[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_contact[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_contact[playerid][2], true);

	TD_iphone_contact[playerid][3] = CreatePlayerTextDraw(playerid, 550.699951, 309.435699, "Sil");
	PlayerTextDrawLetterSize(playerid, TD_iphone_contact[playerid][3], 0.200999, 1.034165);
	PlayerTextDrawTextSize(playerid, TD_iphone_contact[playerid][3], 10.000000, 68.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_contact[playerid][3], 2);
	PlayerTextDrawColor(playerid, TD_iphone_contact[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_contact[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][3], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_contact[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_contact[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_contact[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_contact[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_contact[playerid][3], true);

	TD_iphone_contact[playerid][4] = CreatePlayerTextDraw(playerid, 550.699951, 324.236602, "Geri");
	PlayerTextDrawLetterSize(playerid, TD_iphone_contact[playerid][4], 0.200999, 1.034165);
	PlayerTextDrawTextSize(playerid, TD_iphone_contact[playerid][4], 10.000000, 68.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_contact[playerid][4], 2);
	PlayerTextDrawColor(playerid, TD_iphone_contact[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, TD_iphone_contact[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, TD_iphone_contact[playerid][4], -2139062017);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_contact[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_contact[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_contact[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, TD_iphone_contact[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_contact[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_contact[playerid][4], true);

	//Клавиатура
	TD_iphone_keypad[playerid][0] = CreatePlayerTextDraw(playerid, 512.200073, 270.366973, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][0], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][0], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][0], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][0], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][0], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][0], 0);

	TD_iphone_keypad[playerid][1] = CreatePlayerTextDraw(playerid, 535.994262, 270.366973, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][1], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][1], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][1], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][1], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][1], 0);

	TD_iphone_keypad[playerid][2] = CreatePlayerTextDraw(playerid, 560.388305, 270.366973, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][2], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][2], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][2], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][2], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][2], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][2], 0);

	TD_iphone_keypad[playerid][3] = CreatePlayerTextDraw(playerid, 512.200073, 295.068481, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][3], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][3], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][3], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][3], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][3], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][3], 0);

	TD_iphone_keypad[playerid][4] = CreatePlayerTextDraw(playerid, 535.994262, 295.068481, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][4], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][4], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][4], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][4], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][4], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][4], 0);

	TD_iphone_keypad[playerid][5] = CreatePlayerTextDraw(playerid, 560.388305, 295.068481, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][5], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][5], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][5], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][5], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][5], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][5], 0);

	TD_iphone_keypad[playerid][6] = CreatePlayerTextDraw(playerid, 512.200073, 319.569976, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][6], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][6], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][6], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][6], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][6], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][6], 0);

	TD_iphone_keypad[playerid][7] = CreatePlayerTextDraw(playerid, 535.994262, 319.669982, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][7], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][7], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][7], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][7], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][7], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][7], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][7], 0);

	TD_iphone_keypad[playerid][8] = CreatePlayerTextDraw(playerid, 560.388305, 319.669982, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][8], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][8], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][8], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][8], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][8], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][8], 0);

	TD_iphone_keypad[playerid][9] = CreatePlayerTextDraw(playerid, 512.300048, 343.488128, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][9], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][9], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][9], 8388863);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][9], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][9], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][9], true);

	TD_iphone_keypad[playerid][10] = CreatePlayerTextDraw(playerid, 535.994262, 344.471496, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][10], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][10], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][10], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][10], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][10], 0);

	TD_iphone_keypad[playerid][11] = CreatePlayerTextDraw(playerid, 560.188354, 344.571502, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][11], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][11], 30.000000, 31.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][11], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][11], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][11], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][11], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][11], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][11], 0);

	TD_iphone_keypad[playerid][12] = CreatePlayerTextDraw(playerid, 513.288208, 272.254882, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][12], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][12], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][12], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][12], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][12], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][12], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][12], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][12], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][12], true);

	TD_iphone_keypad[playerid][13] = CreatePlayerTextDraw(playerid, 536.988037, 272.288269, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][13], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][13], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][13], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][13], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][13], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][13], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][13], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][13], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][13], true);

	TD_iphone_keypad[playerid][14] = CreatePlayerTextDraw(playerid, 561.182128, 272.288269, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][14], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][14], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][14], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][14], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][14], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][14], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][14], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][14], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][14], true);

	TD_iphone_keypad[playerid][15] = CreatePlayerTextDraw(playerid, 513.081909, 297.105041, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][15], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][15], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][15], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][15], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][15], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][15], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][15], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][15], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][15], true);

	TD_iphone_keypad[playerid][16] = CreatePlayerTextDraw(playerid, 536.876098, 297.105041, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][16], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][16], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][16], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][16], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][16], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][16], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][16], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][16], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][16], true);

	TD_iphone_keypad[playerid][17] = CreatePlayerTextDraw(playerid, 561.170166, 297.105041, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][17], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][17], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][17], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][17], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][17], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][17], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][17], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][17], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][17], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][17], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][17], true);

	TD_iphone_keypad[playerid][18] = CreatePlayerTextDraw(playerid, 513.170166, 321.605072, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][18], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][18], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][18], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][18], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][18], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][18], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][18], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][18], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][18], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][18], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][18], true);

	TD_iphone_keypad[playerid][19] = CreatePlayerTextDraw(playerid, 536.864379, 321.705078, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][19], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][19], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][19], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][19], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][19], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][19], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][19], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][19], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][19], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][19], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][19], true);

	TD_iphone_keypad[playerid][20] = CreatePlayerTextDraw(playerid, 561.058471, 321.705078, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][20], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][20], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][20], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][20], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][20], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][20], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][20], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][20], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][20], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][20], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][20], true);

	TD_iphone_keypad[playerid][21] = CreatePlayerTextDraw(playerid, 536.858398, 346.505035, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][21], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][21], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][21], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][21], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][21], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][21], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][21], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][21], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][21], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][21], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][21], true);

	TD_iphone_keypad[playerid][22] = CreatePlayerTextDraw(playerid, 561.252441, 346.505035, "LD_BEAT:chit");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][22], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, TD_iphone_keypad[playerid][22], 28.000000, 27.000000);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][22], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][22], phone_window[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][22], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][22], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][22], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][22], 4);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][22], 0);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][22], 0);
	PlayerTextDrawSetSelectable(playerid, TD_iphone_keypad[playerid][22], true);

	TD_iphone_keypad[playerid][23] = CreatePlayerTextDraw(playerid, 572.000122, 353.916534, "X");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][23], 0.278500, 1.279166);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][23], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][23], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][23], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][23], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][23], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][23], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][23], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][23], 0);

	TD_iphone_keypad[playerid][24] = CreatePlayerTextDraw(playerid, 524.200073, 279.216430, "1");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][24], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][24], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][24], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][24], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][24], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][24], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][24], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][24], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][24], 0);

	TD_iphone_keypad[playerid][25] = CreatePlayerTextDraw(playerid, 546.294677, 279.216430, "2");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][25], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][25], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][25], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][25], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][25], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][25], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][25], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][25], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][25], 0);

	TD_iphone_keypad[playerid][26] = CreatePlayerTextDraw(playerid, 570.488769, 279.216430, "3");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][26], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][26], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][26], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][26], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][26], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][26], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][26], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][26], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][26], 0);

	TD_iphone_keypad[playerid][27] = CreatePlayerTextDraw(playerid, 521.600708, 304.117950, "4");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][27], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][27], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][27], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][27], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][27], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][27], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][27], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][27], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][27], 0);

	TD_iphone_keypad[playerid][28] = CreatePlayerTextDraw(playerid, 546.294677, 304.117950, "5");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][28], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][28], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][28], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][28], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][28], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][28], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][28], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][28], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][28], 0);

	TD_iphone_keypad[playerid][29] = CreatePlayerTextDraw(playerid, 570.288818, 304.117950, "6");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][29], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][29], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][29], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][29], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][29], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][29], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][29], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][29], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][29], 0);

	TD_iphone_keypad[playerid][30] = CreatePlayerTextDraw(playerid, 521.600708, 328.619445, "7");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][30], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][30], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][30], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][30], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][30], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][30], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][30], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][30], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][30], 0);

	TD_iphone_keypad[playerid][31] = CreatePlayerTextDraw(playerid, 546.194702, 328.619445, "8");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][31], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][31], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][31], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][31], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][31], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][31], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][31], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][31], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][31], 0);

	TD_iphone_keypad[playerid][32] = CreatePlayerTextDraw(playerid, 570.188842, 328.619445, "9");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][32], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][32], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][32], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][32], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][32], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][32], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][32], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][32], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][32], 0);

	TD_iphone_keypad[playerid][33] = CreatePlayerTextDraw(playerid, 546.694702, 352.637603, "0");
	PlayerTextDrawLetterSize(playerid, TD_iphone_keypad[playerid][33], 0.401999, 1.343332);
	PlayerTextDrawAlignment(playerid, TD_iphone_keypad[playerid][33], 1);
	PlayerTextDrawColor(playerid, TD_iphone_keypad[playerid][33], phone_panel[PlayerInfo[playerid][pPhoneStyle]]);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][33], 0);
	PlayerTextDrawSetOutline(playerid, TD_iphone_keypad[playerid][33], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_iphone_keypad[playerid][33], 255);
	PlayerTextDrawFont(playerid, TD_iphone_keypad[playerid][33], 2);
	PlayerTextDrawSetProportional(playerid, TD_iphone_keypad[playerid][33], 1);
	PlayerTextDrawSetShadow(playerid, TD_iphone_keypad[playerid][33], 0);
