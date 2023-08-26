TDraw_OnGameModeInit()
{

    ServerTextdraws[std_DarkScreen] = TextDrawCreate(-0.500000, -2.062500, "box");
    TextDrawLetterSize(ServerTextdraws[std_DarkScreen], 0.000000, 59.150035);
    TextDrawTextSize(ServerTextdraws[std_DarkScreen], 846.000000, 0.000000);
    TextDrawAlignment(ServerTextdraws[std_DarkScreen], 1);
    TextDrawColor(ServerTextdraws[std_DarkScreen], -1);
    TextDrawUseBox(ServerTextdraws[std_DarkScreen], 1);
    TextDrawBoxColor(ServerTextdraws[std_DarkScreen], 255);
    TextDrawSetShadow(ServerTextdraws[std_DarkScreen], 0);
    TextDrawBackgroundColor(ServerTextdraws[std_DarkScreen], 255);
    TextDrawFont(ServerTextdraws[std_DarkScreen], 1);
    TextDrawSetProportional(ServerTextdraws[std_DarkScreen], 1);

	//admin
	Developer = TextDrawCreate(300.000000, 6.000000, "~r~~h~93~g~~h~ 25~b~~h~~h~~h~ 35");
	TextDrawFont(Developer, 1);
	TextDrawLetterSize(Developer, 0.183333, 1.650001);
	TextDrawTextSize(Developer, 400.000000, 17.000000);
	TextDrawSetOutline(Developer, 1);
	TextDrawSetShadow(Developer, 0);
	TextDrawAlignment(Developer, 1);
	TextDrawColor(Developer, -1);
	TextDrawBackgroundColor(Developer, 255);
	TextDrawBoxColor(Developer, 50);
	TextDrawUseBox(Developer, 0);
	TextDrawSetProportional(Developer, 1);
	TextDrawSetSelectable(Developer, 0);

	Admin = TextDrawCreate(502.000000, -1.000000, "~p~~h~ADMIN-MODU");
	TextDrawFont(Admin, 1);
	TextDrawLetterSize(Admin, 0.170833, 1.250000);
	TextDrawTextSize(Admin, 400.000000, 17.000000);
	TextDrawSetOutline(Admin, 1);
	TextDrawSetShadow(Admin, 0);
	TextDrawAlignment(Admin, 1);
	TextDrawColor(Admin, -1);
	TextDrawBackgroundColor(Admin, 255);
	TextDrawBoxColor(Admin, 50);
	TextDrawUseBox(Admin, 0);
	TextDrawSetProportional(Admin, 1);
	TextDrawSetSelectable(Admin, 0);

    //ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	zond_cam[0] = TextDrawCreate(200.600006, 183.000000, "box");
	TextDrawLetterSize(zond_cam[0], 0.000000, -0.354317);
	TextDrawTextSize(zond_cam[0], 0.000000, 37.000000);
	TextDrawAlignment(zond_cam[0], 2);
	TextDrawColor(zond_cam[0], -1);
	TextDrawUseBox(zond_cam[0], 1);
	TextDrawBoxColor(zond_cam[0], -1);
	TextDrawSetShadow(zond_cam[0], 0);
	TextDrawSetOutline(zond_cam[0], 0);
	TextDrawBackgroundColor(zond_cam[0], 255);
	TextDrawFont(zond_cam[0], 1);
	TextDrawSetProportional(zond_cam[0], 1);
	TextDrawSetShadow(zond_cam[0], 0);

	zond_cam[1] = TextDrawCreate(200.100006, 320.000000, "box");
	TextDrawLetterSize(zond_cam[1], 0.000000, -0.354317);
	TextDrawTextSize(zond_cam[1], 0.000000, 37.000000);
	TextDrawAlignment(zond_cam[1], 2);
	TextDrawColor(zond_cam[1], -1);
	TextDrawUseBox(zond_cam[1], 1);
	TextDrawBoxColor(zond_cam[1], -1);
	TextDrawSetShadow(zond_cam[1], 0);
	TextDrawSetOutline(zond_cam[1], 0);
	TextDrawBackgroundColor(zond_cam[1], 255);
	TextDrawFont(zond_cam[1], 1);
	TextDrawSetProportional(zond_cam[1], 1);
	TextDrawSetShadow(zond_cam[1], 0);

	zond_cam[2] = TextDrawCreate(460.000000, 320.000000, "box");
	TextDrawLetterSize(zond_cam[2], 0.000000, -0.354317);
	TextDrawTextSize(zond_cam[2], 0.000000, 37.000000);
	TextDrawAlignment(zond_cam[2], 2);
	TextDrawColor(zond_cam[2], -1);
	TextDrawUseBox(zond_cam[2], 1);
	TextDrawBoxColor(zond_cam[2], -1);
	TextDrawSetShadow(zond_cam[2], 0);
	TextDrawSetOutline(zond_cam[2], 0);
	TextDrawBackgroundColor(zond_cam[2], 255);
	TextDrawFont(zond_cam[2], 1);
	TextDrawSetProportional(zond_cam[2], 1);
	TextDrawSetShadow(zond_cam[2], 0);

	zond_cam[3] = TextDrawCreate(460.000000, 183.000000, "box");
	TextDrawLetterSize(zond_cam[3], 0.000000, -0.354317);
	TextDrawTextSize(zond_cam[3], 0.000000, 37.000000);
	TextDrawAlignment(zond_cam[3], 2);
	TextDrawColor(zond_cam[3], -1);
	TextDrawUseBox(zond_cam[3], 1);
	TextDrawBoxColor(zond_cam[3], -1);
	TextDrawSetShadow(zond_cam[3], 0);
	TextDrawSetOutline(zond_cam[3], 0);
	TextDrawBackgroundColor(zond_cam[3], 255);
	TextDrawFont(zond_cam[3], 1);
	TextDrawSetProportional(zond_cam[3], 1);
	TextDrawSetShadow(zond_cam[3], 0);

	zond_cam[4] = TextDrawCreate(180.365997, 183.000015, "box");
	TextDrawLetterSize(zond_cam[4], 0.000000, 3.206443);
	TextDrawTextSize(zond_cam[4], 0.000000, -5.000000);
	TextDrawAlignment(zond_cam[4], 2);
	TextDrawColor(zond_cam[4], -1);
	TextDrawUseBox(zond_cam[4], 1);
	TextDrawBoxColor(zond_cam[4], -1);
	TextDrawSetShadow(zond_cam[4], 0);
	TextDrawSetOutline(zond_cam[4], 0);
	TextDrawBackgroundColor(zond_cam[4], 255);
	TextDrawFont(zond_cam[4], 1);
	TextDrawSetProportional(zond_cam[4], 1);
	TextDrawSetShadow(zond_cam[4], 0);

	zond_cam[5] = TextDrawCreate(180.365997, 286.833435, "box");
	TextDrawLetterSize(zond_cam[5], 0.000000, 3.206443);
	TextDrawTextSize(zond_cam[5], 0.000000, -5.000000);
	TextDrawAlignment(zond_cam[5], 2);
	TextDrawColor(zond_cam[5], -1);
	TextDrawUseBox(zond_cam[5], 1);
	TextDrawBoxColor(zond_cam[5], -1);
	TextDrawSetShadow(zond_cam[5], 0);
	TextDrawSetOutline(zond_cam[5], 0);
	TextDrawBackgroundColor(zond_cam[5], 255);
	TextDrawFont(zond_cam[5], 1);
	TextDrawSetProportional(zond_cam[5], 1);
	TextDrawSetShadow(zond_cam[5], 0);

	zond_cam[6] = TextDrawCreate(480.219818, 288.000122, "box");
	TextDrawLetterSize(zond_cam[6], 0.000000, 3.206443);
	TextDrawTextSize(zond_cam[6], 0.000000, -5.000000);
	TextDrawAlignment(zond_cam[6], 2);
	TextDrawColor(zond_cam[6], -1);
	TextDrawUseBox(zond_cam[6], 1);
	TextDrawBoxColor(zond_cam[6], -1);
	TextDrawSetShadow(zond_cam[6], 0);
	TextDrawSetOutline(zond_cam[6], 0);
	TextDrawBackgroundColor(zond_cam[6], 255);
	TextDrawFont(zond_cam[6], 1);
	TextDrawSetProportional(zond_cam[6], 1);
	TextDrawSetShadow(zond_cam[6], 0);

	zond_cam[7] = TextDrawCreate(479.751220, 183.000106, "box");
	TextDrawLetterSize(zond_cam[7], 0.000000, 3.206443);
	TextDrawTextSize(zond_cam[7], 0.000000, -5.000000);
	TextDrawAlignment(zond_cam[7], 2);
	TextDrawColor(zond_cam[7], -1);
	TextDrawUseBox(zond_cam[7], 1);
	TextDrawBoxColor(zond_cam[7], -1);
	TextDrawSetShadow(zond_cam[7], 0);
	TextDrawSetOutline(zond_cam[7], 0);
	TextDrawBackgroundColor(zond_cam[7], 255);
	TextDrawFont(zond_cam[7], 1);
	TextDrawSetProportional(zond_cam[7], 1);
	TextDrawSetShadow(zond_cam[7], 0);

	zond_cam[8] = TextDrawCreate(468.506805, 164.333358, "box");
	TextDrawLetterSize(zond_cam[8], 0.000000, 0.442169);
	TextDrawTextSize(zond_cam[8], 0.000000, 18.000000);
	TextDrawAlignment(zond_cam[8], 2);
	TextDrawColor(zond_cam[8], -1);
	TextDrawUseBox(zond_cam[8], 1);
	TextDrawBoxColor(zond_cam[8], -176);
	TextDrawSetShadow(zond_cam[8], 0);
	TextDrawSetOutline(zond_cam[8], 0);
	TextDrawBackgroundColor(zond_cam[8], 255);
	TextDrawFont(zond_cam[8], 1);
	TextDrawSetProportional(zond_cam[8], 1);
	TextDrawSetShadow(zond_cam[8], 0);

	zond_cam[9] = TextDrawCreate(481.656890, 164.133316, "box");
	TextDrawLetterSize(zond_cam[9], 0.000000, 0.489021);
	TextDrawTextSize(zond_cam[9], 469.500030, 0.000000);
	TextDrawAlignment(zond_cam[9], 1);
	TextDrawColor(zond_cam[9], -1);
	TextDrawUseBox(zond_cam[9], 1);
	TextDrawBoxColor(zond_cam[9], -1523963137);
	TextDrawSetShadow(zond_cam[9], 0);
	TextDrawSetOutline(zond_cam[9], 0);
	TextDrawBackgroundColor(zond_cam[9], 255);
	TextDrawFont(zond_cam[9], 1);
	TextDrawSetProportional(zond_cam[9], 1);
	TextDrawSetShadow(zond_cam[9], 0);

	zond_cam[10] = TextDrawCreate(456.593719, 167.250015, "box");
	TextDrawLetterSize(zond_cam[10], 0.000000, -0.166905);
	TextDrawTextSize(zond_cam[10], 0.000000, -2.000000);
	TextDrawAlignment(zond_cam[10], 2);
	TextDrawColor(zond_cam[10], -1);
	TextDrawUseBox(zond_cam[10], 1);
	TextDrawBoxColor(zond_cam[10], -176);
	TextDrawSetShadow(zond_cam[10], 0);
	TextDrawSetOutline(zond_cam[10], 0);
	TextDrawBackgroundColor(zond_cam[10], 255);
	TextDrawFont(zond_cam[10], 1);
	TextDrawSetProportional(zond_cam[10], 1);
	TextDrawSetShadow(zond_cam[10], 0);

    TD_vehicle_info[0] = TextDrawCreate(429.000000, 409.000000, ".");
	TextDrawBackgroundColor(TD_vehicle_info[0], 255);
	TextDrawFont(TD_vehicle_info[0], 2);
	TextDrawLetterSize(TD_vehicle_info[0], 36.150016, -0.500000);
	TextDrawColor(TD_vehicle_info[0], -1);
	TextDrawSetOutline(TD_vehicle_info[0], 0);
	TextDrawSetProportional(TD_vehicle_info[0], 1);
	TextDrawSetShadow(TD_vehicle_info[0], 1);
	TextDrawSetSelectable(TD_vehicle_info[0], 0);

	TD_vehicle_info[1] = TextDrawCreate(485.000000, 395.000000, "vehicle");
	TextDrawBackgroundColor(TD_vehicle_info[1], 255);
	TextDrawFont(TD_vehicle_info[1], 3);
	TextDrawLetterSize(TD_vehicle_info[1], 0.400000, 0.899999);
	TextDrawColor(TD_vehicle_info[1], -1);
	TextDrawSetOutline(TD_vehicle_info[1], 0);
	TextDrawSetProportional(TD_vehicle_info[1], 1);
	TextDrawSetShadow(TD_vehicle_info[1], 1);
	TextDrawSetSelectable(TD_vehicle_info[1], 0);

	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	TD_restaurant[0] = TextDrawCreate(487.599975, 139.384429, "usebox");
	TextDrawLetterSize(TD_restaurant[0], 0.000000, 20.258150);
	TextDrawTextSize(TD_restaurant[0], 133.600006, 0.000000);
	TextDrawAlignment(TD_restaurant[0], 1);
	TextDrawColor(TD_restaurant[0], 0);
	TextDrawUseBox(TD_restaurant[0], true);
	TextDrawBoxColor(TD_restaurant[0], 255);
	TextDrawSetShadow(TD_restaurant[0], 0);
	TextDrawSetOutline(TD_restaurant[0], 0);
	TextDrawFont(TD_restaurant[0], 0);
	TextDrawSetProportional(TD_restaurant[0], 1);

	TD_restaurant[1] = TextDrawCreate(148.600006, 165.884429, "Bu restoran birden fazla secenek sunuyor.");
	TextDrawLetterSize(TD_restaurant[1], 0.209995, 1.086665);
	TextDrawTextSize(TD_restaurant[1], 1010.000000, -9.333333);
	TextDrawAlignment(TD_restaurant[1], 1);
	TextDrawColor(TD_restaurant[1], -1);
	TextDrawUseBox(TD_restaurant[1], true);
	TextDrawBoxColor(TD_restaurant[1], 0);
	TextDrawSetShadow(TD_restaurant[1], 0);
	TextDrawSetOutline(TD_restaurant[1], 1);
	TextDrawBackgroundColor(TD_restaurant[1], 51);
	TextDrawFont(TD_restaurant[1], 1);
	TextDrawSetProportional(TD_restaurant[1], 1);

	TD_restaurant[2] = TextDrawCreate(148.600006, 176.217773, "Menuden bir tanesini secerek satin alin.");
	TextDrawLetterSize(TD_restaurant[2], 0.209995, 1.086665);
	TextDrawTextSize(TD_restaurant[2], 1010.000000, -9.333333);
	TextDrawAlignment(TD_restaurant[2], 1);
	TextDrawColor(TD_restaurant[2], -1);
	TextDrawUseBox(TD_restaurant[2], true);
	TextDrawBoxColor(TD_restaurant[2], 0);
	TextDrawSetShadow(TD_restaurant[2], 0);
	TextDrawSetOutline(TD_restaurant[2], 1);
	TextDrawBackgroundColor(TD_restaurant[2], 51);
	TextDrawFont(TD_restaurant[2], 1);
	TextDrawSetProportional(TD_restaurant[2], 1);

	TD_restaurant[3] = TextDrawCreate(468.000000, 146.222290, "X");
	TextDrawLetterSize(TD_restaurant[3], 0.449598, 1.241600);
	TextDrawTextSize(TD_restaurant[3], 482.000000, 9.955554);
	TextDrawAlignment(TD_restaurant[3], 1);
	TextDrawColor(TD_restaurant[3], -1061109505);
	TextDrawSetShadow(TD_restaurant[3], 0);
	TextDrawSetOutline(TD_restaurant[3], 1);
	TextDrawBackgroundColor(TD_restaurant[3], 51);
	TextDrawFont(TD_restaurant[3], 1);
	TextDrawSetProportional(TD_restaurant[3], 1);
	TextDrawSetSelectable(TD_restaurant[3], true);
}

TDraw_OnPlayerConnect(playerid)
{	
	/*cWspeedo[playerid][0] = CreatePlayerTextDraw(playerid, 525.111389, 394.088836, "box");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][0], 0.000000, -0.044444);
	PlayerTextDrawTextSize(playerid, cWspeedo[playerid][0], 623.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][0], 1);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, cWspeedo[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, cWspeedo[playerid][0], 0x000000AA);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][0], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][0], 0);

	cWspeedo[playerid][1] = CreatePlayerTextDraw(playerid, 627.777770, 365.715454, "box");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][1], 0.000000, 6.133327);
	PlayerTextDrawTextSize(playerid, cWspeedo[playerid][1], 621.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][1], 1);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, cWspeedo[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, cWspeedo[playerid][1], 0x000000AA);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][1], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][1], 0);

	cWspeedo[playerid][2] = CreatePlayerTextDraw(playerid, 565.889099, 341.168945, "");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, cWspeedo[playerid][2], 60.000000, 73.000000);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][2], 1);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][2], 0);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][2], 0);
	PlayerTextDrawSetPreviewModel(playerid, cWspeedo[playerid][2], 411);
	PlayerTextDrawSetPreviewRot(playerid, cWspeedo[playerid][2], 0.000000, 0.000000, -30.000000, 1.000000);
	PlayerTextDrawSetPreviewVehCol(playerid, cWspeedo[playerid][2], 1, 1);

	cWspeedo[playerid][3] = CreatePlayerTextDraw(playerid, 524.222167, 395.582153, "220");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][3], 0.342222, 1.316266);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][3], 1);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][3], 1);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][3], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][3], 3);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][3], 0);

	cWspeedo[playerid][4] = CreatePlayerTextDraw(playerid, 523.777770, 382.142395, "infernus");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][4], 0.172888, 0.903111);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][4], 1);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][4], 1);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][4], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][4], 0);

	cWspeedo[playerid][5] = CreatePlayerTextDraw(playerid, 526.000244, 408.026733, "KM/H");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][5], 0.175555, 0.669155);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][5], 1);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][5], -1378294017);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][5], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][5], 0);

	cWspeedo[playerid][6] = CreatePlayerTextDraw(playerid, 572.933105, 396.080047, "100");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][6], 0.301333, 1.171911);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][6], 2);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][6], 1);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][6], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][6], 3);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][6], 0);

	cWspeedo[playerid][7] = CreatePlayerTextDraw(playerid, 572.509460, 407.528869, "YAKIT");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][7], 0.151111, 0.689067);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][7], 2);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][7], -1378294017);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][7], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][7], 0);

	cWspeedo[playerid][8] = CreatePlayerTextDraw(playerid, 621.111633, 396.080108, "999.0");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][8], 0.231555, 1.052444);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][8], 3);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][8], 1);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][8], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][8], 3);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][8], 0);

	cWspeedo[playerid][9] = CreatePlayerTextDraw(playerid, 618.444335, 406.533325, "KILOMETRE");
	PlayerTextDrawLetterSize(playerid, cWspeedo[playerid][9], 0.145778, 0.699022);
	PlayerTextDrawAlignment(playerid, cWspeedo[playerid][9], 3);
	PlayerTextDrawColor(playerid, cWspeedo[playerid][9], -1378294017);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, cWspeedo[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, cWspeedo[playerid][9], 255);
	PlayerTextDrawFont(playerid, cWspeedo[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, cWspeedo[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, cWspeedo[playerid][9], 0);*/

	//info message

	TD_job_message[playerid][0] = CreatePlayerTextDraw(playerid, 608.000, 196.000, "Info_Message");
	PlayerTextDrawLetterSize(playerid, TD_job_message[playerid][0], 0.170, 1.099);
	PlayerTextDrawTextSize(playerid, TD_job_message[playerid][0], -10.000, -7.000);
	PlayerTextDrawAlignment(playerid, TD_job_message[playerid][0], 3);
	PlayerTextDrawColor(playerid, TD_job_message[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, TD_job_message[playerid][0], -1);
	PlayerTextDrawSetOutline(playerid, TD_job_message[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, TD_job_message[playerid][0], 150);
	PlayerTextDrawFont(playerid, TD_job_message[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TD_job_message[playerid][0], 1);


	SpeedText[playerid] = CreatePlayerTextDraw(playerid, 520.9165, 105.4813, "~b~FUEL_________~l~I~w~IIIIIIIIII~w~I~l~I~n~~b~SPEED______~w~0___km/h~n~~b~MILEAGE__~w~0.00_km~n~");
	PlayerTextDrawLetterSize(playerid, SpeedText[playerid], 0.2099, 1.0999);
	PlayerTextDrawTextSize(playerid, SpeedText[playerid], 629.0000, 0.0000);
	PlayerTextDrawAlignment(playerid, SpeedText[playerid], 1);
	PlayerTextDrawColor(playerid, SpeedText[playerid], -1);
	PlayerTextDrawSetOutline(playerid, SpeedText[playerid], 1);
	PlayerTextDrawBackgroundColor(playerid, SpeedText[playerid], 255);
	PlayerTextDrawFont(playerid, SpeedText[playerid], 2);
	PlayerTextDrawSetProportional(playerid, SpeedText[playerid], 1);

	//-------------------------------------------------------------------------//

	Silah_Bilgi[playerid][MermiTD] = CreatePlayerTextDraw(playerid, 520.850097, 63.333305, " ");
	PlayerTextDrawLetterSize(playerid, Silah_Bilgi[playerid][MermiTD], 0.363750, 1.360833);
	PlayerTextDrawAlignment(playerid, Silah_Bilgi[playerid][MermiTD], 2);
	PlayerTextDrawColor(playerid, Silah_Bilgi[playerid][MermiTD], -1378294017);
	PlayerTextDrawSetShadow(playerid, Silah_Bilgi[playerid][MermiTD], 0);
	PlayerTextDrawSetOutline(playerid, Silah_Bilgi[playerid][MermiTD], 1);
	PlayerTextDrawBackgroundColor(playerid, Silah_Bilgi[playerid][MermiTD], 255);
	PlayerTextDrawFont(playerid, Silah_Bilgi[playerid][MermiTD], 1);
	PlayerTextDrawSetProportional(playerid, Silah_Bilgi[playerid][MermiTD], 1);
	PlayerTextDrawSetShadow(playerid, Silah_Bilgi[playerid][MermiTD], 0);

	playerhud[playerid][0] = CreatePlayerTextDraw(playerid, 324.000, 434.000, "16.00_-_19/09/2023_LIBERTY_CITY_ROLEPLAY_BETA_VERSION_QUERASMA_FETO(31)");
	PlayerTextDrawLetterSize(playerid, playerhud[playerid][0], 0.187, 1.098);
	PlayerTextDrawTextSize(playerid, playerhud[playerid][0], 4.000, -13.000);
	PlayerTextDrawAlignment(playerid, playerhud[playerid][0], 2);
	PlayerTextDrawColor(playerid, playerhud[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, playerhud[playerid][0], 1);
	PlayerTextDrawSetOutline(playerid, playerhud[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, playerhud[playerid][0], 150);
	PlayerTextDrawFont(playerid, playerhud[playerid][0], 3);
	PlayerTextDrawSetProportional(playerid, playerhud[playerid][0], 1);

	playerhud[playerid][1] = CreatePlayerTextDraw(playerid, 591.000, 391.000, "mdl-2239:lc");
	PlayerTextDrawTextSize(playerid, playerhud[playerid][1], 55.000, 59.000);
	PlayerTextDrawAlignment(playerid, playerhud[playerid][1], 1);
	PlayerTextDrawColor(playerid, playerhud[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, playerhud[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, playerhud[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, playerhud[playerid][1], 255);
	PlayerTextDrawFont(playerid, playerhud[playerid][1], 4);
	PlayerTextDrawSetProportional(playerid, playerhud[playerid][1], 1);

	playerhud[playerid][2] = CreatePlayerTextDraw(playerid, 590.000, 413.000, "Querasma_Feto(031)");
	PlayerTextDrawLetterSize(playerid, playerhud[playerid][2], 0.200, 1.098);
	PlayerTextDrawAlignment(playerid, playerhud[playerid][2], 3);
	PlayerTextDrawColor(playerid, playerhud[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, playerhud[playerid][2], 1);
	PlayerTextDrawSetOutline(playerid, playerhud[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, playerhud[playerid][2], 150);
	PlayerTextDrawFont(playerid, playerhud[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, playerhud[playerid][2], 1);

	playerhud[playerid][3] = CreatePlayerTextDraw(playerid, 590.000, 425.000, "00.00 - 19/09/2023");
	PlayerTextDrawLetterSize(playerid, playerhud[playerid][3], 0.166, 0.898);
	PlayerTextDrawAlignment(playerid, playerhud[playerid][3], 3);
	PlayerTextDrawColor(playerid, playerhud[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, playerhud[playerid][3], 1);
	PlayerTextDrawSetOutline(playerid, playerhud[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, playerhud[playerid][3], 150);
	PlayerTextDrawFont(playerid, playerhud[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, playerhud[playerid][3], 1);

	playerhud[playerid][4] = CreatePlayerTextDraw(playerid, 590.000, 435.000, "BLAZE STREET");
	PlayerTextDrawLetterSize(playerid, playerhud[playerid][4], 0.166, 0.898);
	PlayerTextDrawAlignment(playerid, playerhud[playerid][4], 3);
	PlayerTextDrawColor(playerid, playerhud[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, playerhud[playerid][4], 1);
	PlayerTextDrawSetOutline(playerid, playerhud[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, playerhud[playerid][4], 150);
	PlayerTextDrawFont(playerid, playerhud[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, playerhud[playerid][4], 1);


	infotxt[playerid] = TextDrawCreate(325.000, 400.000, "~r~Bilgi Mesaji");
	TextDrawLetterSize(infotxt[playerid], 0.240, 1.099);
	TextDrawAlignment(infotxt[playerid], 2);
	TextDrawColor(infotxt[playerid], -1);
	TextDrawSetOutline(infotxt[playerid], 1);
	TextDrawBackgroundColor(infotxt[playerid], 255);
	TextDrawFont(infotxt[playerid], 3);
	TextDrawSetProportional(infotxt[playerid], 1);
	TextDrawSetShadow(infotxt[playerid], 1);

    /*TD_vehicle_name[playerid] = CreatePlayerTextDraw(playerid, 553.000000, 407.000000, "info");
	PlayerTextDrawBackgroundColor(playerid, TD_vehicle_name[playerid], 255);
	PlayerTextDrawFont(playerid, TD_vehicle_name[playerid], 2);
	PlayerTextDrawLetterSize(playerid, TD_vehicle_name[playerid], 0.200000, 0.699998);
	PlayerTextDrawColor(playerid, TD_vehicle_name[playerid], -1);
	PlayerTextDrawSetOutline(playerid, TD_vehicle_name[playerid], 0);
	PlayerTextDrawSetProportional(playerid, TD_vehicle_name[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TD_vehicle_name[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, TD_vehicle_name[playerid], 0);
	PlayerTextDrawHide(playerid, TD_vehicle_name[playerid]);*/

	/*drug_effect[playerid] = CreatePlayerTextDraw(playerid, 320.000000, 0.000000, "_");
	PlayerTextDrawAlignment(playerid, drug_effect[playerid], 2);
	PlayerTextDrawBackgroundColor(playerid, drug_effect[playerid], 255);
	PlayerTextDrawFont(playerid, drug_effect[playerid], 1);
	PlayerTextDrawLetterSize(playerid, drug_effect[playerid], 0.500000, 53.000000);
	PlayerTextDrawColor(playerid, drug_effect[playerid], -1);
	PlayerTextDrawSetOutline(playerid, drug_effect[playerid], 0);
	PlayerTextDrawSetProportional(playerid, drug_effect[playerid], 1);
	PlayerTextDrawSetShadow(playerid, drug_effect[playerid], 1);
	PlayerTextDrawUseBox(playerid, drug_effect[playerid], 1);
	PlayerTextDrawBoxColor(playerid, drug_effect[playerid], -14837680);
	PlayerTextDrawTextSize(playerid, drug_effect[playerid], 0.000000, 1215.000000);
	PlayerTextDrawSetSelectable(playerid, drug_effect[playerid], 0);*/

	spectate_TD[playerid][0] = CreatePlayerTextDraw(playerid, 1.000000, 1.000000, "Loading ...");
	PlayerTextDrawBackgroundColor(playerid, spectate_TD[playerid][0], 255);
	PlayerTextDrawFont(playerid, spectate_TD[playerid][0], 1);
	PlayerTextDrawLetterSize(playerid, spectate_TD[playerid][0], 0.230000, 0.899999);
	PlayerTextDrawColor(playerid, spectate_TD[playerid][0], -1);
	PlayerTextDrawSetOutline(playerid, spectate_TD[playerid][0], 0);
	PlayerTextDrawSetProportional(playerid, spectate_TD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, spectate_TD[playerid][0], 1);
	PlayerTextDrawUseBox(playerid, spectate_TD[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, spectate_TD[playerid][0], 255);
	PlayerTextDrawTextSize(playerid, spectate_TD[playerid][0], 638.000000, 0.000000);

	spectate_TD[playerid][1] = CreatePlayerTextDraw(playerid, 1.000000, 437.000000, "Loading ...");
	PlayerTextDrawBackgroundColor(playerid, spectate_TD[playerid][1], 255);
	PlayerTextDrawFont(playerid, spectate_TD[playerid][1], 1);
	PlayerTextDrawLetterSize(playerid, spectate_TD[playerid][1], 0.230000, 0.899999);
	PlayerTextDrawColor(playerid, spectate_TD[playerid][1], -1);
	PlayerTextDrawSetOutline(playerid, spectate_TD[playerid][1], 0);
	PlayerTextDrawSetProportional(playerid, spectate_TD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, spectate_TD[playerid][1], 1);
	PlayerTextDrawUseBox(playerid, spectate_TD[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, spectate_TD[playerid][1], 255);
	PlayerTextDrawTextSize(playerid, spectate_TD[playerid][1], 638.000000, 0.000000);

	mulkbilgi[playerid] = CreatePlayerTextDraw(playerid, 265.000, 355.000, "");
	PlayerTextDrawTextSize(playerid, mulkbilgi[playerid], 115.000, 45.000);
	PlayerTextDrawAlignment(playerid, mulkbilgi[playerid], 1);
	PlayerTextDrawColor(playerid, mulkbilgi[playerid], -1);
	PlayerTextDrawSetShadow(playerid, mulkbilgi[playerid], 0);
	PlayerTextDrawSetOutline(playerid, mulkbilgi[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, mulkbilgi[playerid], 255);
	PlayerTextDrawFont(playerid, mulkbilgi[playerid], 4);
	PlayerTextDrawSetProportional(playerid, mulkbilgi[playerid], 1);

	mulktext[playerid][0] = CreatePlayerTextDraw(playerid, 322.000, 348.000, "~h~~p~SATILIK EV!~n~~w~UCRET: ~g~$21000");
	PlayerTextDrawLetterSize(playerid, mulktext[playerid][0], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, mulktext[playerid][0], 2);
	PlayerTextDrawColor(playerid, mulktext[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, mulktext[playerid][0], 1);
	PlayerTextDrawSetOutline(playerid, mulktext[playerid][0], 1);
	PlayerTextDrawBackgroundColor(playerid, mulktext[playerid][0], 150);
	PlayerTextDrawFont(playerid, mulktext[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, mulktext[playerid][0], 1);

	mulktext[playerid][1] = CreatePlayerTextDraw(playerid, 322.000, 377.000, "");
	PlayerTextDrawLetterSize(playerid, mulktext[playerid][1], 0.200, 0.999);
	PlayerTextDrawAlignment(playerid, mulktext[playerid][1], 2);
	PlayerTextDrawColor(playerid, mulktext[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, mulktext[playerid][1], 1);
	PlayerTextDrawSetOutline(playerid, mulktext[playerid][1], 1);
	PlayerTextDrawBackgroundColor(playerid, mulktext[playerid][1], 150);
	PlayerTextDrawFont(playerid, mulktext[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, mulktext[playerid][1], 1);
	
	PlayerTextdraws[playerid][LoginCharacterTD][0] = CreatePlayerTextDraw(playerid, 354.733428, 166.433563, "~y~Matthew Harper (Level: ~w~16~y~)~n~Market~w~ bolgesinde geziyor.");
	PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 0.202996, 1.118813);
	PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 581.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 1);
	PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 255);
	PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][LoginCharacterTD][0], 1);

	PlayerTextdraws[playerid][LoginCharacterTD][1] = CreatePlayerTextDraw(playerid, 377.901916, 196.731704, "Giris Yap");
	PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 0.220998, 1.205927);
	PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 8.0, 46.0);
	PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 2);
	PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], -1);
	PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 255);
	PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 2);
	PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][1], true);

	PlayerTextdraws[playerid][LoginCharacterTD][2] = CreatePlayerTextDraw(playerid, 359.568450, 265.590988, "Geri");
	PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 0.285998, 1.529482);
	PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 8.0, 26.0);
	PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 2);
	PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], -19374593);
	PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 255);
	PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 2);
	PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][2], true);

	PlayerTextdraws[playerid][LoginCharacterTD][3] = CreatePlayerTextDraw(playerid, 393.901916, 265.590988, "Ileri");
	PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 0.285998, 1.529482);
	PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 9.0, 29.0);
	PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 2);
	PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], -19374593);
	PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 0);
	PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 255);
	PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 2);
	PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][LoginCharacterTD][3], true);

    PlayerTextdraws[playerid][LoginCharacterTD][4] = CreatePlayerTextDraw(playerid, 548.666809, 75.229618, "888/888");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 0.235333, 1.081481);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 0.000000, 32.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 2);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][LoginCharacterTD][4], 1);

    // Staff spectating panel.

    PlayerTextdraws[playerid][SpectatingInfo][0] = CreatePlayerTextDraw(playerid, 297.666656, 276.696350, "box");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 0.000000, 5.200002);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 0.000000, 695.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 2);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], -1);
    PlayerTextDrawUseBox(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 1);
    PlayerTextDrawBoxColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 75);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 0);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][SpectatingInfo][0], 1);

    PlayerTextdraws[playerid][SpectatingInfo][1] = CreatePlayerTextDraw(playerid, 302.133483, 275.281494, "~y~Matthew Harper (ID: 0) - Hesap: 10000 - Karakter: 10000 - IP: 255.255.255.255");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 0.132666, 0.874073);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 0.000000, 686.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 2);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][SpectatingInfo][1], 1);

    PlayerTextdraws[playerid][SpectatingInfo][2] = CreatePlayerTextDraw(playerid, 69.666786, 287.481567, "~y~Bilgi:~w~ Ileri gecmek icin ~y~SOL FARE~w~, geri gitmek icin ~y~SAG FARE~w~ ve yenilemek icin ~y~SPACE~w~ kullanabilirsiniz.");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 0.127999, 0.845036);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 0.000000, 127.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 2);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][SpectatingInfo][2], 1);

    PlayerTextdraws[playerid][SpectatingInfo][3] = CreatePlayerTextDraw(playerid, 146.532867, 284.577758, "Hiz: 999~n~Int/World: 999/999~n~Ping: 999 P/L: 99.99~n~Can CS/SS: 100.00/100.00~n~Zirh CS/SS: 100.00/100.00");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 0.150999, 0.791111);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 282.208435, 0.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][SpectatingInfo][3], 1);

    PlayerTextdraws[playerid][SpectatingInfo][4] = CreatePlayerTextDraw(playerid, 284.641296, 284.577758, "Landstalker (ID: 2000)~n~Benzin: 100~n~Motor: Acik~n~Sahip: 10000 - Birlik: 1 - Mekan: 1");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 0.150999, 0.791111);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 420.316864, 0.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][SpectatingInfo][4], 1);

    PlayerTextdraws[playerid][SpectatingInfo][5] = CreatePlayerTextDraw(playerid, 422.749725, 284.577758, "Desert Eagle (999 mermi)~n~Yarali: 0sn~n~Skin: 250~n~Anim: indexid");
    PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 0.150999, 0.791111);
    PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 558.411132, 0.000000);
    PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 1);
    PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], -1);
    PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 0);
    PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 1);
    PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 255);
    PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 1);
    PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][SpectatingInfo][5], 1);
		
	//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
	TD_restaurant_prod[playerid][0] = CreatePlayerTextDraw(playerid, 157.000000, 277.200042, "Product 1");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][0], 0.267998, 0.993332);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][0], 1);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][0], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][0], 1);

	TD_restaurant_prod[playerid][1] = CreatePlayerTextDraw(playerid, 239.000000, 277.200042, "Product 2");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][1], 0.267998, 0.993332);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][1], 1);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][1], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][1], 1);

	TD_restaurant_prod[playerid][2] = CreatePlayerTextDraw(playerid, 321.000000, 277.200042, "Product 3");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][2], 0.267998, 0.993332);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][2], 1);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][2], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][2], 1);

	TD_restaurant_prod[playerid][3] = CreatePlayerTextDraw(playerid, 403.000000, 277.200042, "Product 4");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][3], 0.267998, 0.993332);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][3], 1);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][3], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][3], 1);

	TD_restaurant_prod[playerid][4] = CreatePlayerTextDraw(playerid, 152.799987, 188.657760, "2218");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][4], 0.495200, 1.196799);
	PlayerTextDrawTextSize(playerid, TD_restaurant_prod[playerid][4], 59.999931, 68.195480);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][4], 2);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, TD_restaurant_prod[playerid][4], true);
	PlayerTextDrawBoxColor(playerid, TD_restaurant_prod[playerid][4], 255);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][4], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, TD_restaurant_prod[playerid][4], true);
	PlayerTextDrawSetPreviewModel(playerid, TD_restaurant_prod[playerid][4], 2218);
	PlayerTextDrawSetPreviewRot(playerid, TD_restaurant_prod[playerid][4], -220.000000, -200.000000, 200.000000, 1.000000);

	TD_restaurant_prod[playerid][5] = CreatePlayerTextDraw(playerid, 234.799987, 188.657760, "2219");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][5], 0.495200, 1.196799);
	PlayerTextDrawTextSize(playerid, TD_restaurant_prod[playerid][5], 59.999931, 68.195480);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][5], 2);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, TD_restaurant_prod[playerid][5], true);
	PlayerTextDrawBoxColor(playerid, TD_restaurant_prod[playerid][5], 255);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][5], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, TD_restaurant_prod[playerid][5], true);
	PlayerTextDrawSetPreviewModel(playerid, TD_restaurant_prod[playerid][5], 2219);
	PlayerTextDrawSetPreviewRot(playerid, TD_restaurant_prod[playerid][5], -220.000000, -200.000000, 200.000000, 1.000000);

	TD_restaurant_prod[playerid][6] = CreatePlayerTextDraw(playerid, 316.799987, 188.657760, "2220");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][6], 0.495200, 1.196799);
	PlayerTextDrawTextSize(playerid, TD_restaurant_prod[playerid][6], 59.999931, 68.195480);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][6], 2);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][6], -1);
	PlayerTextDrawUseBox(playerid, TD_restaurant_prod[playerid][6], true);
	PlayerTextDrawBoxColor(playerid, TD_restaurant_prod[playerid][6], 255);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][6], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, TD_restaurant_prod[playerid][6], true);
	PlayerTextDrawSetPreviewModel(playerid, TD_restaurant_prod[playerid][6], 2220);
	PlayerTextDrawSetPreviewRot(playerid, TD_restaurant_prod[playerid][6], -220.000000, -200.000000, 200.000000, 1.000000);

	TD_restaurant_prod[playerid][7] = CreatePlayerTextDraw(playerid, 398.799987, 188.657760, "2355");
	PlayerTextDrawLetterSize(playerid, TD_restaurant_prod[playerid][7], 0.495200, 1.196799);
	PlayerTextDrawTextSize(playerid, TD_restaurant_prod[playerid][7], 59.999931, 68.195480);
	PlayerTextDrawAlignment(playerid, TD_restaurant_prod[playerid][7], 2);
	PlayerTextDrawColor(playerid, TD_restaurant_prod[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, TD_restaurant_prod[playerid][7], true);
	PlayerTextDrawBoxColor(playerid, TD_restaurant_prod[playerid][7], 255);
	PlayerTextDrawSetShadow(playerid, TD_restaurant_prod[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, TD_restaurant_prod[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, TD_restaurant_prod[playerid][7], 51);
	PlayerTextDrawFont(playerid, TD_restaurant_prod[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, TD_restaurant_prod[playerid][7], 1);
	PlayerTextDrawSetSelectable(playerid, TD_restaurant_prod[playerid][7], true);
	PlayerTextDrawSetPreviewModel(playerid, TD_restaurant_prod[playerid][7], 2355);
	PlayerTextDrawSetPreviewRot(playerid, TD_restaurant_prod[playerid][7], -220.000000, -200.000000, 200.000000, 1.000000);

	FuelText[playerid] = CreatePlayerTextDraw(playerid, 40.000000, 305.000000, "~b~~h~Yakit dolduruluyor...~n~~n~~w~Ucret: ~g~~h~$0 ~y~~h~(0.00L)");
    PlayerTextDrawBackgroundColor(playerid, FuelText[playerid], 255);
    PlayerTextDrawFont(playerid, FuelText[playerid], 1);
    PlayerTextDrawLetterSize(playerid, FuelText[playerid], 0.240000, 1.100000);
    PlayerTextDrawColor(playerid, FuelText[playerid], -1);
    PlayerTextDrawSetOutline(playerid, FuelText[playerid], 1);
    PlayerTextDrawSetProportional(playerid, FuelText[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, FuelText[playerid], 0);

	for(new i = 0; i < 4; i++)
	{
		TextDrawHideForPlayer(playerid, TD_restaurant[i]);
	}

    for(new i; i < 11; i++)
	{
	    TextDrawHideForPlayer(playerid, zond_cam[i]);
	}
}

SyncHudTextDraw(playerid)
{
	new hour, minute, second, year, month, day;
	new mes[320];
	getdate(year, month, day);
	gettime(hour, minute, second);

	new location[MAX_ZONE_NAME],
		Float:x, Float:y, Float:z;
    
	if(GetPlayerVirtualWorld(playerid) > 0) location = "Mekan";
	else
	{
	    GetPlayerPos(playerid, x, y, z);
	    GetZone(x, y, location, MAX_ZONE_NAME);
	    strreplace(location, ' ', '_');
	}	

	format(mes, sizeof(mes), "%i/%i/%02d_%i:%i__%s__LIBERTY_CITY_BETA_%s(%d)", day, month, year, hour, minute, location, GetName(playerid), playerid);
   	PlayerTextDrawSetString(playerid, playerhud[playerid][0], mes);
}

SyncHudTextDrawModern(playerid)
{
	new hour, minute, second, year, month, day;
	new mes[256];
	getdate(year, month, day);
	gettime(hour, minute, second);
	format(mes, sizeof(mes), "%i:%i - %i/%i/%02d", hour, minute, day, month, year);
   	PlayerTextDrawSetString(playerid, playerhud[playerid][3], mes);
	format(mes, sizeof(mes), "%s(%i)", GetNameEx(playerid), playerid);
	PlayerTextDrawSetString(playerid, playerhud[playerid][2], mes);

	new location[MAX_ZONE_NAME],
		Float:x, Float:y, Float:z;

	if(GetPlayerVirtualWorld(playerid) > 0) location = "Mekan";
	else
	{
	    GetPlayerPos(playerid, x, y, z);
	    GetZone(x, y, location, MAX_ZONE_NAME);
	    strreplace(location, ' ', '_');
	}	

	format(mes, sizeof(mes), "%s", location);
	PlayerTextDrawSetString(playerid, playerhud[playerid][4], mes);
}

ShowHudTextDraw(playerid)
{
	new hour, minute, second, year, month, day;
	new mes[320];
	getdate(year, month, day);
	gettime(hour, minute, second);

	new location[MAX_ZONE_NAME],
		Float:x, Float:y, Float:z;
    
	if(GetPlayerVirtualWorld(playerid) > 0) location = "Mekan";
	else
	{
	    GetPlayerPos(playerid, x, y, z);
	    GetZone(x, y, location, MAX_ZONE_NAME);
	    strreplace(location, ' ', '_');
	}	

	format(mes, sizeof(mes), "%i/%i/%02d_%i:%i__%s__LIBERTY_CITY_BETA_%s(%d)", day, month, year, hour, minute, location, GetName(playerid), playerid);
   	PlayerTextDrawSetString(playerid, playerhud[playerid][0], mes);
	PlayerTextDrawShow(playerid, playerhud[playerid][0]);
	PlayerTextDrawHide(playerid, playerhud[playerid][1]);
	PlayerTextDrawHide(playerid, playerhud[playerid][2]);
	PlayerTextDrawHide(playerid, playerhud[playerid][3]);
	//PlayerTextDrawShow(playerid, playerhud[playerid][4]);
	return 1;
}

ShowHudTextDrawModern(playerid)
{
	new hour, minute, second, year, month, day;
	new mes[256];
	getdate(year, month, day);
	gettime(hour, minute, second);
	format(mes, sizeof(mes), "%i:%i - %i/%i/%02d", hour, minute, day, month, year);
   	PlayerTextDrawSetString(playerid, playerhud[playerid][3], mes);
	format(mes, sizeof(mes), "%s(%i)", GetNameEx(playerid), playerid);
	PlayerTextDrawSetString(playerid, playerhud[playerid][2], mes);

	new location[MAX_ZONE_NAME],
		Float:x, Float:y, Float:z;

	if(GetPlayerVirtualWorld(playerid) > 0) location = "Mekan";
	else
	{
	    GetPlayerPos(playerid, x, y, z);
	    GetZone(x, y, location, MAX_ZONE_NAME);
	    strreplace(location, ' ', '_');
	}	

	format(mes, sizeof(mes), "%s", location);
	PlayerTextDrawSetString(playerid, playerhud[playerid][4], mes);

	PlayerTextDrawHide(playerid, playerhud[playerid][0]);
	PlayerTextDrawShow(playerid, playerhud[playerid][1]);
	PlayerTextDrawShow(playerid, playerhud[playerid][2]);
	PlayerTextDrawShow(playerid, playerhud[playerid][3]);
	PlayerTextDrawShow(playerid, playerhud[playerid][4]);
	return 1;
}

HideHudTextDraw(playerid)
{
	PlayerTextDrawHide(playerid, playerhud[playerid][0]);
	PlayerTextDrawHide(playerid, playerhud[playerid][1]);
	PlayerTextDrawHide(playerid, playerhud[playerid][2]);
	PlayerTextDrawHide(playerid, playerhud[playerid][3]);	
	PlayerTextDrawHide(playerid, playerhud[playerid][4]);
	return 1;
}

HideHudTextDrawModern(playerid)
{
    PlayerTextDrawHide(playerid, playerhud[playerid][4]);	
	PlayerTextDrawHide(playerid, playerhud[playerid][3]);
	PlayerTextDrawHide(playerid, playerhud[playerid][2]);
	PlayerTextDrawHide(playerid, playerhud[playerid][1]);
	return 1;
}

InfoMSG(playerid, info[], delay)
{
	ReplaceText(info, "ð", "g");
	ReplaceText(info, "Ð", "G");
	ReplaceText(info, "ü", "u");
	ReplaceText(info, "Ü", "U");
	ReplaceText(info, "þ", "s");
	ReplaceText(info, "Þ", "S");
	ReplaceText(info, "ç", "c");
	ReplaceText(info, "Ç", "C");
	ReplaceText(info, "ö", "o");
	ReplaceText(info, "Ö", "O");
	ReplaceText(info, "ý", "i");
	ReplaceText(info, "Ý", "I");

	TextDrawSetString(infotxt[playerid], info);
	TextDrawShowForPlayer(playerid, infotxt[playerid]);
	infotxt_expire{playerid} = delay;
	return 1;
}

InfoMSG2(playerid, header[], info[], delay)
{
	ReplaceText(info, "ð", "g");
	ReplaceText(info, "Ð", "G");
	ReplaceText(info, "ü", "u");
	ReplaceText(info, "Ü", "U");
	ReplaceText(info, "þ", "s");
	ReplaceText(info, "Þ", "S");
	ReplaceText(info, "ç", "c");
	ReplaceText(info, "Ç", "C");
	ReplaceText(info, "ö", "o");
	ReplaceText(info, "Ö", "O");
	ReplaceText(info, "ý", "i");
	ReplaceText(info, "Ý", "I");

	TD_SendMessage(playerid, info, header, delay, 12840, 10.0000, 100.000000, 300.000000, strlen(info));
	return 1;
}

RestaurantMenuHide(playerid)
{
    CancelSelectTextDraw(playerid);
	for(new i; i != 8; i++)
	{
 		if (i < 4)
		 	TextDrawHideForPlayer(playerid, TD_restaurant[i]);

		PlayerTextDrawHide(playerid, TD_restaurant_prod[playerid][i]);
	}
	DeletePVar(playerid, #restaurant);
	return 1;
}

/*TextHud_Update(playerid, vehicleid = 0)
{
    if(!HudStatus{playerid}) 
	{
		ToggleHudTextdraw(playerid, true);
	}

    new slotnumara = PlayerInfo[playerid][pSlot], channelnumara, hudstring[256];

	if(slotnumara >= 1)
	{
		channelnumara = PlayerInfo[playerid][pChannel];
	}
	else channelnumara = 0;

	if(channelnumara == -1) slotnumara = 0;

    if(!vehicleid)
    {
		switch(PlayerInfo[playerid][pHud])
		{
		    case 0:
		    {
		        if(channelnumara > 99999)
		        {
		            format(hudstring, sizeof(hudstring), "~b~TELSIZ BILGILERI~n~~b~Kanal: ~g~~n~%d~n~~b~Slot: ~g~%d", channelnumara, slotnumara);
		            PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
		        }
		        else
		        {
		            format(hudstring, sizeof(hudstring), "~b~TELSIZ BILGILERI~n~~b~Kanal: ~g~%d~n~~b~Slot: ~g~%d", channelnumara, slotnumara);
		            PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
		        }
			}
            case 1:
            {
 				format(hudstring, sizeof(hudstring), "_~n~~w~TELSIZ BILGILERI: ~y~%d~n~~w~Slot: ~y~%d", channelnumara, slotnumara);
	            PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
            }
            case 2, 3:
			{
				if(HudStatus{playerid}) 
				{
					ToggleHudTextdraw(playerid, false);
				}
			}
            case 4:
            {
  				format(hudstring, sizeof(hudstring), "~w~TELSIZ BILGILERI:~n~%d ~n~slot: %d", channelnumara, slotnumara);
	            PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
            }
		}
    }
    else
    {
	    new aracmodel = GetVehicleModel(vehicleid), Float: kmh_speed = GetVehicleSpeed(vehicleid), Float: mph_speed = GetVehicleSpeed(vehicleid);

        switch(PlayerInfo[playerid][pHud])
        {
			case 0:
			{
		        if(!IsABicycle(vehicleid))
		        {
		            if(channelnumara > 99999)
		            {
		                format(hudstring, sizeof(hudstring), "~b~Km/h: ~g~%.0f~n~~b~Yakit: ~g~%d~n~ ~n~~b~TELSIZ BILGILERI~n~~b~Kanal: ~g~~n~%d~n~~b~Slot: ~g~%d", kmh_speed, floatround(VehicleInfo[vehicleid][carFuel]/GetVehicleFuelCapacity(GetVehicleModel(vehicleid)) * 100), channelnumara, slotnumara);
		                PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
		            }
		            else
		            {
		                format(hudstring, sizeof(hudstring), "~b~Km/h: ~g~%.0f~n~~b~Yakit: ~g~%d~n~ ~n~~b~TELSIZ BILGILERI~n~~b~Kanal: ~g~%d~n~~b~Slot: ~g~%d", kmh_speed, floatround(VehicleInfo[vehicleid][carFuel]/GetVehicleFuelCapacity(GetVehicleModel(vehicleid)) * 100), channelnumara, slotnumara);
		                PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
		            }
		        }
		        else
		        {
		            if(channelnumara > 99999)
		            {
		                format(hudstring, sizeof(hudstring), "~b~Km/h: ~g~%.0f~n~~b~Yakit: ~g~--~n~ ~n~~b~TELSIZ BILGILERI~n~~b~Kanal: ~g~~n~%d~n~~b~Slot: ~g~%d", kmh_speed, channelnumara, slotnumara);
		                PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
		            }
		            else
		            {
		                format(hudstring, sizeof(hudstring), "~b~Km/h: ~g~%.0f~n~~b~Yakit: ~g~--~n~ ~n~~b~TELSIZ BILGILERI~n~~b~Kanal: ~g~%d~n~~b~Slot: ~g~%d", kmh_speed, channelnumara, slotnumara);
		                PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
		            }
		        }
			}
			case 1:
			{
				if(!IsABicycle(vehicleid))
					format(hudstring, sizeof(hudstring), "~w~%s~r~ %d %.0f~y~KMH~w~/~y~%.0f~r~MPH", VehicleNames[aracmodel-400], floatround(VehicleInfo[vehicleid][carFuel]/GetVehicleFuelCapacity(GetVehicleModel(vehicleid)) * 100), kmh_speed, mph_speed);
				else
					format(hudstring, sizeof(hudstring), "~w~%s~r~ -- %.0f~y~KMH~w~/~y~%.0f~r~MPH", VehicleNames[aracmodel-400], kmh_speed, mph_speed);

				format(hudstring, sizeof(hudstring), "%s~n~~w~TELSIZ BILGILERI: ~y~%d~n~~w~Slot: ~y~%d", hudstring, channelnumara, slotnumara);

				PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
			}
			case 2:
			{
			    new Float:vehicleHealth;
			    GetVehicleHealth(vehicleid, vehicleHealth);

				if(!IsABicycle(vehicleid))
					format(hudstring, sizeof(hudstring), "~l~%s~n~ ~w~%.0f  ~l~%.0f ~w~%.0f ~l~%d", VehicleNames[aracmodel-400], mph_speed, kmh_speed, vehicleHealth, floatround(floatdiv(VehicleInfo[vehicleid][carFuel], GetVehicleFuelCapacity(aracmodel)) * 100, floatround_round));
				else
					format(hudstring, sizeof(hudstring), "~l~%s~n~ ~w~%.0f  ~l~%.0f ~w~%.0f ~l~--", VehicleNames[aracmodel-400], mph_speed, kmh_speed, vehicleHealth);

				PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
			}
			case 3:
			{
				if(!IsABicycle(vehicleid))
					format(hudstring, sizeof(hudstring), "~g~%d ~r~%d ~w~%d", floatround(VehicleInfo[vehicleid][carFuel]/GetVehicleFuelCapacity(GetVehicleModel(vehicleid)) * 100), floatround(mph_speed), floatround(kmh_speed));
				else
					format(hudstring, sizeof(hudstring), "~g~-- ~r~%d- ~w~%d", floatround(mph_speed), floatround(kmh_speed));

				PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
			}
			case 4:
			{
				new shortstr[128];

				if(!IsABicycle(vehicleid))
				{
					format(hudstring, sizeof(hudstring), "~w~TELSIZ BILGILERI:~n~%d ~n~slot: %d", channelnumara, slotnumara);

					switch(floatround(mph_speed))
					{
					    case 0..10: shortstr = "~n~~w~-";
					    case 11..20: shortstr = "~n~~w~--";
					    case 21..30: shortstr = "~n~~w~---";
					    case 31..40: shortstr = "~n~~w~---~g~-";
					    case 41..50: shortstr = "~n~~w~---~g~--";
					    case 51..60: shortstr = "~n~~w~---~g~---";
					    case 61..70: shortstr = "~n~~w~---~g~---~y~-";
					    case 71..80: shortstr = "~n~~w~---~g~---~y~--";
					    case 81..90: shortstr = "~n~~w~---~g~---~y~---";
					    case 91..100: shortstr = "~n~~w~---~g~---~y~---~r~-";
					    case 101..110: shortstr = "~n~~w~---~g~---~y~---~r~--";
					    case 111..400: shortstr = "~n~~w~---~g~---~y~---~r~---";
					}

					strcat(hudstring, shortstr);
				}
				else format(hudstring, sizeof(hudstring), "~w~TELSIZ BILGILERI:~n~%d ~n~slot: %d", channelnumara, slotnumara);

				PlayerTextDrawSetString(playerid, HudTextDraw[playerid], hudstring);
			}
		}
    }
    return true;
}

ToggleHudTextdraw(playerid, bool:status)
{
	HudStatus{playerid} = status;

	if(status) 
	{
		PlayerTextDrawShow(playerid, HudTextDraw[playerid]);
	}
	else 
	{
		PlayerTextDrawHide(playerid, HudTextDraw[playerid]);
	}

	return true;
}

CreatePlayerHUD(playerid)
{
    HUD_Created{playerid} = false;

    PlayerTextDrawDestroy(playerid, HudTextDraw[playerid]);

	switch(PlayerInfo[playerid][pHud])
	{
		case 0:
		{
			HudTextDraw[playerid] = CreatePlayerTextDraw(playerid, 545.000000, 110.000000, ""); //~b~RADIO INFO~n~~b~Kanal: ~g~0~n~~b~Slot: ~g~1
			PlayerTextDrawLetterSize(playerid, HudTextDraw[playerid], 0.480000, 1.120000);
			PlayerTextDrawTextSize(playerid, HudTextDraw[playerid], 60.000000, 100.000000);
			PlayerTextDrawAlignment(playerid, HudTextDraw[playerid], 2);
			PlayerTextDrawColor(playerid, HudTextDraw[playerid], -1);
			PlayerTextDrawSetShadow(playerid, HudTextDraw[playerid], 2);
			PlayerTextDrawSetOutline(playerid, HudTextDraw[playerid], 0);
			PlayerTextDrawBackgroundColor(playerid, HudTextDraw[playerid], 255);
			PlayerTextDrawFont(playerid, HudTextDraw[playerid], 3);
			PlayerTextDrawSetProportional(playerid, HudTextDraw[playerid], 1);
  		}
		case 1:
		{
			HudTextDraw[playerid] = CreatePlayerTextDraw(playerid, 12.999976, 125.288810, ""); //BMX -- 62KMH/39MPH~n~Radio Info: 0~n~Slot: 1
			PlayerTextDrawLetterSize(playerid, HudTextDraw[playerid], 0.297999, 1.550219);
			PlayerTextDrawTextSize(playerid, HudTextDraw[playerid], 1705.000000, 0.000000);
			PlayerTextDrawAlignment(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawColor(playerid, HudTextDraw[playerid], -1);
			PlayerTextDrawSetShadow(playerid, HudTextDraw[playerid], 0);
			PlayerTextDrawSetOutline(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawBackgroundColor(playerid, HudTextDraw[playerid], 0x000000AA);
			PlayerTextDrawFont(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawSetProportional(playerid, HudTextDraw[playerid], 1);
		}
		case 2:
		{
			HudTextDraw[playerid] = CreatePlayerTextDraw(playerid, 507.666748, 400.725708, "");
			PlayerTextDrawLetterSize(playerid, HudTextDraw[playerid], 0.601332, 2.392297);
			PlayerTextDrawTextSize(playerid, HudTextDraw[playerid], 0.000000, 2366.000000);
			PlayerTextDrawAlignment(playerid, HudTextDraw[playerid], 2);
			PlayerTextDrawColor(playerid, HudTextDraw[playerid], 255);
			PlayerTextDrawSetShadow(playerid, HudTextDraw[playerid], 0);
			PlayerTextDrawSetOutline(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawBackgroundColor(playerid, HudTextDraw[playerid], -1431655681);
			PlayerTextDrawFont(playerid, HudTextDraw[playerid], 2);
			PlayerTextDrawSetProportional(playerid, HudTextDraw[playerid], 1);
		}
		case 3:
		{
			HudTextDraw[playerid] = CreatePlayerTextDraw(playerid, 553.524169, 96.426689, ""); //~g~0 ~r~0 ~w~0
			PlayerTextDrawLetterSize(playerid, HudTextDraw[playerid], 0.571142, 2.406401);
			PlayerTextDrawAlignment(playerid, HudTextDraw[playerid], 2);
			PlayerTextDrawColor(playerid, HudTextDraw[playerid], -1);
			PlayerTextDrawSetShadow(playerid, HudTextDraw[playerid], 0);
			PlayerTextDrawSetOutline(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawBackgroundColor(playerid, HudTextDraw[playerid], 255);
			PlayerTextDrawFont(playerid, HudTextDraw[playerid], 3);
			PlayerTextDrawSetProportional(playerid, HudTextDraw[playerid], 1);
		}
		case 4:
		{
			HudTextDraw[playerid] = CreatePlayerTextDraw(playerid, 554.286499, 369.493011, ""); //~w~Radio Info:~n~911 ~n~slot: 1~n~~w~---~g~---~y~---~r~---
			PlayerTextDrawLetterSize(playerid, HudTextDraw[playerid], 0.366190, 1.190400);
			PlayerTextDrawAlignment(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawColor(playerid, HudTextDraw[playerid], -1);
			PlayerTextDrawSetShadow(playerid, HudTextDraw[playerid], 0);
			PlayerTextDrawSetOutline(playerid, HudTextDraw[playerid], 1);
			PlayerTextDrawBackgroundColor(playerid, HudTextDraw[playerid], 255);
			PlayerTextDrawFont(playerid, HudTextDraw[playerid], 3);
			PlayerTextDrawSetProportional(playerid, HudTextDraw[playerid], 1);
		}
	}

	HUD_Created{playerid} = true;
}*/