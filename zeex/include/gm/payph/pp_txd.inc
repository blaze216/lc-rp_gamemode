new	
    Text:PP_Framework[11],
    PlayerText:PP_Btn[MAX_PLAYERS][11],
	PlayerText:NumberLetters[MAX_PLAYERS][4]
;	

stock LoadPayPhoneTD()
{
	PP_Framework[0] = TextDrawCreate(484.436248, 207.500045, "box");
	TextDrawLetterSize(PP_Framework[0], 0.000000, 22.228401);
	TextDrawTextSize(PP_Framework[0], 612.000000, 0.000000);
	TextDrawAlignment(PP_Framework[0], 1);
	TextDrawColor(PP_Framework[0], -1);
	TextDrawUseBox(PP_Framework[0], 1);
	TextDrawBoxColor(PP_Framework[0], -2139062017);
	TextDrawSetShadow(PP_Framework[0], 0);
	TextDrawSetOutline(PP_Framework[0], 0);
	TextDrawBackgroundColor(PP_Framework[0], -2004317953);
	TextDrawFont(PP_Framework[0], 1);
	TextDrawSetProportional(PP_Framework[0], 1);
	TextDrawSetShadow(PP_Framework[0], 0);

	PP_Framework[1] = TextDrawCreate(492.401275, 218.000061, "box");
	TextDrawLetterSize(PP_Framework[1], 0.000000, 2.456809);
	TextDrawTextSize(PP_Framework[1], 587.000000, 0.000000);
	TextDrawAlignment(PP_Framework[1], 1);
	TextDrawColor(PP_Framework[1], -1);
	TextDrawUseBox(PP_Framework[1], 1);
	TextDrawBoxColor(PP_Framework[1], -858993409);
	TextDrawSetShadow(PP_Framework[1], 0);
	TextDrawSetOutline(PP_Framework[1], 0);
	TextDrawBackgroundColor(PP_Framework[1], 255);
	TextDrawFont(PP_Framework[1], 1);
	TextDrawSetProportional(PP_Framework[1], 1);
	TextDrawSetShadow(PP_Framework[1], 0);

	PP_Framework[2] = TextDrawCreate(588.748046, 215.666687, "_");
	TextDrawLetterSize(PP_Framework[2], 0.000000, 0.000000);
	TextDrawTextSize(PP_Framework[2], 16.000000, 27.000000);
	TextDrawAlignment(PP_Framework[2], 1);
	TextDrawColor(PP_Framework[2], -1);
	TextDrawSetShadow(PP_Framework[2], 0);
	TextDrawSetOutline(PP_Framework[2], 0);
	TextDrawBackgroundColor(PP_Framework[2], 1431655935);
	TextDrawFont(PP_Framework[2], 5);
	TextDrawSetProportional(PP_Framework[2], 0);
	TextDrawSetShadow(PP_Framework[2], 0);
	TextDrawSetSelectable(PP_Framework[2], true);
	TextDrawSetPreviewModel(PP_Framework[2], 298);
	TextDrawSetPreviewRot(PP_Framework[2], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Framework[3] = TextDrawCreate(591.259521, 216.833312, "<");
	TextDrawLetterSize(PP_Framework[3], 0.301610, 2.515832);
	TextDrawAlignment(PP_Framework[3], 1);
	TextDrawColor(PP_Framework[3], -1);
	TextDrawSetShadow(PP_Framework[3], 0);
	TextDrawSetOutline(PP_Framework[3], 0);
	TextDrawBackgroundColor(PP_Framework[3], 255);
	TextDrawFont(PP_Framework[3], 2);
	TextDrawSetProportional(PP_Framework[3], 1);
	TextDrawSetShadow(PP_Framework[3], 0);

	PP_Framework[4] = TextDrawCreate(482.093994, 248.333358, "box");
	TextDrawLetterSize(PP_Framework[4], 0.000000, 2.175696);
	TextDrawTextSize(PP_Framework[4], 616.000000, 0.000000);
	TextDrawAlignment(PP_Framework[4], 1);
	TextDrawColor(PP_Framework[4], -1);
	TextDrawUseBox(PP_Framework[4], 1);
	TextDrawBoxColor(PP_Framework[4], 479182822);
	TextDrawSetShadow(PP_Framework[4], 0);
	TextDrawSetOutline(PP_Framework[4], 0);
	TextDrawBackgroundColor(PP_Framework[4], 255);
	TextDrawFont(PP_Framework[4], 1);
	TextDrawSetProportional(PP_Framework[4], 1);
	TextDrawSetShadow(PP_Framework[4], 0);

	PP_Framework[5] = TextDrawCreate(485.841827, 247.750030, "Want_to_advertise_here?_Call~n~1-800-Advertise_with_a_phone!");
															  //".Объявление");
	TextDrawLetterSize(PP_Framework[5], 0.235080, 1.063332);
	TextDrawAlignment(PP_Framework[5], 1);
	TextDrawColor(PP_Framework[5], -1);
	TextDrawSetShadow(PP_Framework[5], 0);
	TextDrawSetOutline(PP_Framework[5], 0);
	TextDrawBackgroundColor(PP_Framework[5], 255);
	TextDrawFont(PP_Framework[5], 1);
	TextDrawSetProportional(PP_Framework[5], 1);
	TextDrawSetShadow(PP_Framework[5], 0);

	PP_Framework[6] = TextDrawCreate(495.212249, 276.916717, "box");
	TextDrawLetterSize(PP_Framework[6], 0.000000, 12.811126);
	TextDrawTextSize(PP_Framework[6], 598.000000, 0.000000);
	TextDrawAlignment(PP_Framework[6], 1);
	TextDrawColor(PP_Framework[6], -1);
	TextDrawUseBox(PP_Framework[6], 1);
	TextDrawBoxColor(PP_Framework[6], -858993409);
	TextDrawSetShadow(PP_Framework[6], 0);
	TextDrawSetOutline(PP_Framework[6], 0);
	TextDrawBackgroundColor(PP_Framework[6], 255);
	TextDrawFont(PP_Framework[6], 1);
	TextDrawSetProportional(PP_Framework[6], 1);
	TextDrawSetShadow(PP_Framework[6], 0);

	PP_Framework[7] = TextDrawCreate(524.092285, 365.000000, "_");
	TextDrawLetterSize(PP_Framework[7], 0.000000, 0.000000);
	TextDrawTextSize(PP_Framework[7], 72.000000, 22.000000);
	TextDrawAlignment(PP_Framework[7], 1);
	TextDrawColor(PP_Framework[7], -1);
	TextDrawSetShadow(PP_Framework[7], 0);
	TextDrawSetOutline(PP_Framework[7], 0);
	TextDrawBackgroundColor(PP_Framework[7], 762659839);
	TextDrawFont(PP_Framework[7], 5);
	TextDrawSetProportional(PP_Framework[7], 0);
	TextDrawSetShadow(PP_Framework[7], 0);
	TextDrawSetSelectable(PP_Framework[7], true);
	TextDrawSetPreviewModel(PP_Framework[7], 0);
	TextDrawSetPreviewRot(PP_Framework[7], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Framework[8] = TextDrawCreate(575.161193, 282.749908, "_");
	TextDrawLetterSize(PP_Framework[8], 0.000000, 0.000000);
	TextDrawTextSize(PP_Framework[8], 21.000000, 77.000000);
	TextDrawAlignment(PP_Framework[8], 1);
	TextDrawColor(PP_Framework[8], -1);
	TextDrawSetShadow(PP_Framework[8], 0);
	TextDrawSetOutline(PP_Framework[8], 0);
	TextDrawBackgroundColor(PP_Framework[8], 255);
	TextDrawFont(PP_Framework[8], 5);
	TextDrawSetProportional(PP_Framework[8], 0);
	TextDrawSetShadow(PP_Framework[8], 0);
	TextDrawSetSelectable(PP_Framework[8], true);
	TextDrawSetPreviewModel(PP_Framework[8], 299);
	TextDrawSetPreviewRot(PP_Framework[8], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Framework[9] = TextDrawCreate(561.742492, 366.750000, "CALL");
	TextDrawLetterSize(PP_Framework[9], 0.462313, 1.792500);
	TextDrawAlignment(PP_Framework[9], 2);
	TextDrawColor(PP_Framework[9], -1);
	TextDrawSetShadow(PP_Framework[9], 0);
	TextDrawSetOutline(PP_Framework[9], 0);
	TextDrawBackgroundColor(PP_Framework[9], 255);
	TextDrawFont(PP_Framework[9], 2);
	TextDrawSetProportional(PP_Framework[9], 1);
	TextDrawSetShadow(PP_Framework[9], 0);

	PP_Framework[10] = TextDrawCreate(525.197937, 395.916442, "____LIBERTY_TELEKOM");
															//"Provided_by_LS_Telefonica");
	TextDrawLetterSize(PP_Framework[10], 0.195724, 1.226665);
	TextDrawAlignment(PP_Framework[10], 1);
	TextDrawColor(PP_Framework[10], -1482184705);
	TextDrawSetShadow(PP_Framework[10], 0);
	TextDrawSetOutline(PP_Framework[10], 0);
	TextDrawBackgroundColor(PP_Framework[10], 255);
	TextDrawFont(PP_Framework[10], 1);
	TextDrawSetProportional(PP_Framework[10], 1);
	TextDrawSetShadow(PP_Framework[10], 0);

	return 1;
}
stock LoadPayPhoneBtnTD(playerid)
{
	PP_Btn[playerid][0] = CreatePlayerTextDraw(playerid, 497.554870, 219.749984, "00:00");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][0], 0.494641, 1.932500);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][0], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][0], 255);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][0], 0);

	PP_Btn[playerid][1] = CreatePlayerTextDraw(playerid, 498.323608, 283.333190, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][1], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][1], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][1], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][1], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][1], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][1], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][2] = CreatePlayerTextDraw(playerid, 524.092468, 283.333221, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][2], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][2], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][2], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][2], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][2], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][2], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][2], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][2], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][3] = CreatePlayerTextDraw(playerid, 550.329467, 283.333190, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][3], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][3], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][3], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][3], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][3], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][3], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][3], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][3], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][4] = CreatePlayerTextDraw(playerid, 498.791992, 311.916625, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][4], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][4], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][4], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][4], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][4], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][4], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][5] = CreatePlayerTextDraw(playerid, 524.560607, 311.333282, "Btn");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][5], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][5], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][5], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][5], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][5], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][5], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][5], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][5], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][6] = CreatePlayerTextDraw(playerid, 550.328979, 310.749938, "Btn");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][6], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][6], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][6], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][6], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][6], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][6], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][6], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][6], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][6], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][7] = CreatePlayerTextDraw(playerid, 498.791534, 338.749969, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][7], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][7], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][7], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][7], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][7], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][7], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][7], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][7], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][7], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][8] = CreatePlayerTextDraw(playerid, 525.028747, 338.749969, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][8], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][8], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][8], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][8], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][8], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][8], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][9] = CreatePlayerTextDraw(playerid, 550.329162, 338.749938, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][9], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][9], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][9], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][9], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][9], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][9], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][9], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][9], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][9], 0.000000, 0.000000, 0.000000, -1.000000);

	PP_Btn[playerid][10] = CreatePlayerTextDraw(playerid, 498.791595, 365.583282, "_");
	PlayerTextDrawLetterSize(playerid, PP_Btn[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, PP_Btn[playerid][10], 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, PP_Btn[playerid][10], 1);
	PlayerTextDrawColor(playerid, PP_Btn[playerid][10], -1);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, PP_Btn[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, PP_Btn[playerid][10], 1431655935);
	PlayerTextDrawFont(playerid, PP_Btn[playerid][10], 5);
	PlayerTextDrawSetProportional(playerid, PP_Btn[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, PP_Btn[playerid][10], 0);
	PlayerTextDrawSetSelectable(playerid, PP_Btn[playerid][10], true);
	PlayerTextDrawSetPreviewModel(playerid, PP_Btn[playerid][10], 0);
	PlayerTextDrawSetPreviewRot(playerid, PP_Btn[playerid][10], 0.000000, 0.000000, 0.000000, -1.000000);

	return 1;
}
stock LoadNumPayPhoneTD(playerid)
{
	NumberLetters[playerid][0] = CreatePlayerTextDraw(playerid, 505.550048, 283.014862, "1____2____3");
	PlayerTextDrawLetterSize(playerid, NumberLetters[playerid][0], 0.484582, 2.325924);
	PlayerTextDrawAlignment(playerid, NumberLetters[playerid][0], 1);
	PlayerTextDrawColor(playerid, NumberLetters[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, NumberLetters[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, NumberLetters[playerid][0], 255);
	PlayerTextDrawFont(playerid, NumberLetters[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, NumberLetters[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][0], 0);

	NumberLetters[playerid][1] = CreatePlayerTextDraw(playerid, 503.716644, 311.153564, "4____5____6");
	PlayerTextDrawLetterSize(playerid, NumberLetters[playerid][1], 0.477915, 2.280369);
	PlayerTextDrawAlignment(playerid, NumberLetters[playerid][1], 1);
	PlayerTextDrawColor(playerid, NumberLetters[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, NumberLetters[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, NumberLetters[playerid][1], 255);
	PlayerTextDrawFont(playerid, NumberLetters[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, NumberLetters[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][1], 0);

	NumberLetters[playerid][2] = CreatePlayerTextDraw(playerid, 504.533355, 338.518249, "7____8____9");
	PlayerTextDrawLetterSize(playerid, NumberLetters[playerid][2], 0.469999, 2.254814);
	PlayerTextDrawAlignment(playerid, NumberLetters[playerid][2], 1);
	PlayerTextDrawColor(playerid, NumberLetters[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, NumberLetters[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, NumberLetters[playerid][2], 255);
	PlayerTextDrawFont(playerid, NumberLetters[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, NumberLetters[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][2], 0);

	NumberLetters[playerid][3] = CreatePlayerTextDraw(playerid, 504.533355, 364.619842, "0");
	PlayerTextDrawLetterSize(playerid, NumberLetters[playerid][3], 0.469999, 2.254814);
	PlayerTextDrawAlignment(playerid, NumberLetters[playerid][3], 1);
	PlayerTextDrawColor(playerid, NumberLetters[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, NumberLetters[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, NumberLetters[playerid][3], 255);
	PlayerTextDrawFont(playerid, NumberLetters[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, NumberLetters[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, NumberLetters[playerid][3], 0);
	
	return 1;
}
