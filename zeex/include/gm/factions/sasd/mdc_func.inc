
MDC_Hide(playerid)
{
    MdcInfo[playerid][mdcCreated] = 0;
    MdcInfo[playerid][mdcPage] = PAGE_NONE;

    SetPVarInt(playerid, #pDelay, 1);

    for(new i = 0; i < 32; i++)
    {
        PlayerTextDrawDestroy(playerid, MDC_LIC[playerid][i]);
        MDC_LIC[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
        if (i < 20) {
            PlayerTextDrawDestroy(playerid, MDC_APB_TD[playerid][i]);
            MDC_APB_TD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            PlayerTextDrawDestroy(playerid, MDC_CALLS_TD[playerid][i]);
            MDC_CALLS_TD[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
            if (i < 18) {
                PlayerTextDrawDestroy(playerid, MDC_TD_MENU[playerid][i]);
                MDC_TD_MENU[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                if (i < 17) {
                    PlayerTextDrawDestroy(playerid, MDC_UI[playerid][i]);
                    MDC_UI[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                    if (i < 16) {
                        PlayerTextDrawDestroy(playerid, MDC_LIST[playerid][i]);
                        MDC_LIST[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                        if (i < 12) {
                            PlayerTextDrawDestroy(playerid, MDC_LOOKUP_PERSON[playerid][i]);
                            MDC_LOOKUP_PERSON[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                            PlayerTextDrawDestroy(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][i]);
                            MDC_LOOKUP_VEHICLES_LIST[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                            if (i < 8) {
                                PlayerTextDrawDestroy(playerid, MDC_LOOKUP_VEHICLE[playerid][i]);
                                MDC_LOOKUP_VEHICLE[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                if (i < 7) {
                                    PlayerTextDrawDestroy(playerid, MDC_MAINSCREEN[playerid][i]);
                                    MDC_MAINSCREEN[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                    if (i < 6) {
                                        PlayerTextDrawDestroy(playerid, MDC_OTHER_ADDRESS[playerid][i]);
                                        MDC_OTHER_ADDRESS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                        if (i < 5) {
                                            PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][i]);
                                            MDC_ADDRESS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                            if (i < 4) {
                                                PlayerTextDrawDestroy(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
                                                MDC_LOOKUP_SEARCH[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                                if (i < 3) {
                                                    PlayerTextDrawDestroy(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][i]);
                                                    MDC_LOOKUP_VEHICLES_ARROWS[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                                    PlayerTextDrawDestroy(playerid, MDC_VEH_LIST_CLICK[playerid][i]);
                                                    MDC_VEH_LIST_CLICK[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                                    PlayerTextDrawDestroy(playerid, MDC_LIST_INFO[playerid][i]);
                                                    MDC_LIST_INFO[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                                    PlayerTextDrawDestroy(playerid, MDC_TD_LEFT_PANEL[playerid][i]);
                                                    MDC_TD_LEFT_PANEL[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                                    if (i < 2) {
                                                        PlayerTextDrawDestroy(playerid, MDC_LOOKUP_AVATAR[playerid][i]);
                                                        MDC_LOOKUP_AVATAR[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    PlayerTextDrawDestroy(playerid, MDC_LOOKUP_ERROR[playerid]);
    MDC_LOOKUP_ERROR[playerid] = PlayerText:INVALID_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, MDC_ERROR_CALLS[playerid]);
    MDC_ERROR_CALLS[playerid] = PlayerText:INVALID_TEXT_DRAW;

    PlayerTextDrawDestroy(playerid, MDC_BACK[playerid]);
    MDC_BACK[playerid] = PlayerText:INVALID_TEXT_DRAW;

    CancelSelectTextDraw(playerid);
    SetPVarInt(playerid, #pDelay, 0);

    // PVARS:
    // MDC_OWNER_ID
    // MDC_ID
    // MDC_VEHICLE_NUM
    // MDC_VEH_BACK
    // MDC_MAX_PAGE
    // MDC_FINE
    // MDC_APB_S
    // MDC_APB_TEXT
    // BODYCAM
    return 1;
}

MDC_Show(playerid, page = PAGE_MAIN)
{
    if (GetPVarInt(playerid, #pDelay)) return MDC_Show(playerid, page);

    Create_MDC(playerid);

    for(new i = 0; i < 17; i++) PlayerTextDrawShow(playerid, MDC_UI[playerid][i]);

    new string[124];
    format(string, sizeof(string), "~n~-_MOBIL VERI BILGISAYARI_-~n~%s", GetNameEx(playerid));
    PlayerTextDrawSetString(playerid, MDC_UI[playerid][11], string);

    MdcInfo[playerid][mdcCreated] = 1;
    MdcInfo[playerid][mdcSearch] = 0;

    return MDC_PAGE(playerid, page);
}
Create_MDC(playerid)
{
	new Float: x, Float: y, Float: d;

	MDC_UI[playerid][0] = CreatePlayerTextDraw(playerid, 153.383316, 135.783706, "display");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][0], 0.000000, 33.833335);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][0], 482.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][0], 1);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][0], -1061109505);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][0], 0);

	MDC_UI[playerid][1] = CreatePlayerTextDraw(playerid, 154.883392, 137.129501, "header-display");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][1], 0.000000, 1.416666);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][1], 480.799987, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][1], Factions[PlayerInfo[playerid][pFaction]][fColor]); //GREEN
	//PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][1], 8388863); //GREEN
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][1], 0);

	MDC_UI[playerid][13] = CreatePlayerTextDraw(playerid, 167.499984, 138.529678,"Los Santos Polis Departmani ~>~ Ana Panel");
																				//"RED COUNTY SHERIFF'S DEPARTMENT MDC ~>~ MAIN SCREEN"); //ÒÈÒÓË MDC
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][13], 0.213330, 1.050369);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][13], 1);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][13], -1061109505);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][13], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][13], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][13], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][13], 1);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][13], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][13], 0);

	MDC_UI[playerid][14] = CreatePlayerTextDraw(playerid, 155.300003, 136.592605, "]");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][14], 0.297500, 1.454815);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][14], 1);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][14], -1061109505);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][14], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][14], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][14], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][14], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][14], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][14], 0);
	
	MDC_UI[playerid][15] = CreatePlayerTextDraw(playerid, 447.182891, 137.066452, "_-_");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][15], 0.460832, 1.423702);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][15], 10.000000, 15.000000);//0.969999, 15.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][15], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][15], -1);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][15], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][15], 0x3e80f2FF);//0x9189EFFF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][15], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][15], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][15], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][15], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][15], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][15], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][15], true);

	MDC_UI[playerid][16] = CreatePlayerTextDraw(playerid, 468.532928, 137.184951, "_X_");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][16], 0.227082, 1.402961);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][16], 10.000000, 15.000000);//0.969999, 15.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][16], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][16], -1);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][16], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][16], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][16], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][16], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][16], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][16], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][16], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][16], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][16], true);

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- MAINMENU -------------------------

	*/

	MDC_MAINSCREEN[playerid][0] = CreatePlayerTextDraw(playerid, 229.583328, 156.070693, ""); // ÀÂÀÒÀÐ ÈÃÐÎÊÀ
	PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, MDC_MAINSCREEN[playerid][0], 251.000000, 258.000000);
	PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][0], 1);
	PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][0], -1061109505);
	PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, MDC_MAINSCREEN[playerid][0], 282);
	PlayerTextDrawSetPreviewRot(playerid, MDC_MAINSCREEN[playerid][0], 0.000000, 0.000000, 0.000000, 0.850000);

	MDC_MAINSCREEN[playerid][1] = CreatePlayerTextDraw(playerid, 257.083435, 238.222213, "prewiew-front");
	PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][1], 0.000000, 21.749986);
	PlayerTextDrawTextSize(playerid, MDC_MAINSCREEN[playerid][1], 481.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][1], -1);
	PlayerTextDrawUseBox(playerid, MDC_MAINSCREEN[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, MDC_MAINSCREEN[playerid][1], -1061109505);
	PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][1], 0);

	MDC_MAINSCREEN[playerid][2] = CreatePlayerTextDraw(playerid, 355.816650, 238.333114, "Police Officer II  Blaze Test");
	PlayerTextDrawLetterSize(playerid, MDC_MAINSCREEN[playerid][2], 0.234999, 0.972591);
	PlayerTextDrawTextSize(playerid, MDC_MAINSCREEN[playerid][2], 0.000000, 234.000000);
	PlayerTextDrawAlignment(playerid, MDC_MAINSCREEN[playerid][2], 2);
	PlayerTextDrawColor(playerid, MDC_MAINSCREEN[playerid][2], 255);
	PlayerTextDrawUseBox(playerid, MDC_MAINSCREEN[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_MAINSCREEN[playerid][2], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_MAINSCREEN[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_MAINSCREEN[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_MAINSCREEN[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, MDC_MAINSCREEN[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_MAINSCREEN[playerid][2], 0);

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- LOOK UP --------------------------

	*/

	MDC_LOOKUP_SEARCH[playerid][0] = CreatePlayerTextDraw(playerid, 249.765502, 157.156112, "ISIM");//249.965469, 156.956069, "ÈÌß");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][0], 10.000000, 36.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][0], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][0], true);

	MDC_LOOKUP_SEARCH[playerid][1] = CreatePlayerTextDraw(playerid, 290.482147, 157.056076, "PLAKA");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][1], 10.000000, 36.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][1], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][1], true);

	MDC_LOOKUP_SEARCH[playerid][2] = CreatePlayerTextDraw(playerid, 313.932128, 157.656158, "_____");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0.199579, 0.962221);//0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][2], 429.000000, 8.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][2], 255);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][2], true);

	MDC_LOOKUP_SEARCH[playerid][3] = CreatePlayerTextDraw(playerid, 455.849273, 156.756057, "YENILE");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_SEARCH[playerid][3], 10.000000, 44.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_SEARCH[playerid][3], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_SEARCH[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_SEARCH[playerid][3], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_SEARCH[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_SEARCH[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_SEARCH[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_SEARCH[playerid][3], true);

	MDC_LOOKUP_ERROR[playerid] = CreatePlayerTextDraw(playerid, 232.682266, 173.793121, "]__HATA: BIR SEY BULUNAMADI!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_ERROR[playerid], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_ERROR[playerid], 478.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_ERROR[playerid], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_ERROR[playerid], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_ERROR[playerid], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_ERROR[playerid], -2147483393);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_ERROR[playerid], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_ERROR[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_ERROR[playerid], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_ERROR[playerid], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_ERROR[playerid], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_ERROR[playerid], 0);
	
	MDC_ERROR_CALLS[playerid] = CreatePlayerTextDraw(playerid, 232.682266, 158.646331, "]__HATA: BIR SEY BULUNAMADI!");
	PlayerTextDrawLetterSize(playerid, MDC_ERROR_CALLS[playerid], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_ERROR_CALLS[playerid], 478.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_ERROR_CALLS[playerid], 1);
	PlayerTextDrawColor(playerid, MDC_ERROR_CALLS[playerid], 0xa7a7a7FF);
	PlayerTextDrawUseBox(playerid, MDC_ERROR_CALLS[playerid], 1);
	PlayerTextDrawBoxColor(playerid, MDC_ERROR_CALLS[playerid], 0x494949FF);
	PlayerTextDrawSetShadow(playerid, MDC_ERROR_CALLS[playerid], 0);
	PlayerTextDrawSetOutline(playerid, MDC_ERROR_CALLS[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_ERROR_CALLS[playerid], 255);
	PlayerTextDrawFont(playerid, MDC_ERROR_CALLS[playerid], 2);
	PlayerTextDrawSetProportional(playerid, MDC_ERROR_CALLS[playerid], 1);
	PlayerTextDrawSetShadow(playerid, MDC_ERROR_CALLS[playerid], 0);


	/*

		----------------------------- MDC- -----------------------------
		----------------------------- LOOKUP_PERSON --------------------

	*/

	MDC_LOOKUP_AVATAR[playerid][0] = CreatePlayerTextDraw(playerid, 270.000122, 177.941299, "~n~resim~n~~n~bulunamadi~n~__");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0.400000, 1.600000);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0.000000, 77.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_AVATAR[playerid][0], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_AVATAR[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_AVATAR[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_AVATAR[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_AVATAR[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_AVATAR[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_AVATAR[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][0], 0);

	MDC_LOOKUP_AVATAR[playerid][1] = CreatePlayerTextDraw(playerid, 168.016494, 175.959106, "");	// AVATAR
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_AVATAR[playerid][1], 204.000000, 202.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_AVATAR[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_AVATAR[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_AVATAR[playerid][1], -1061109505);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_AVATAR[playerid][1], 5);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0);
	PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], 282);
	PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_AVATAR[playerid][1], 0.000000, 0.000000, 20.000000, 0.850000);

	MDC_LOOKUP_PERSON[playerid][0] = CreatePlayerTextDraw(playerid, 229.999923, 253.240768, "prewiew-front");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][0], 0.000000, 16.916669);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][0], 444.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][0], -1061109505);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][0], 0);

	MDC_LOOKUP_PERSON[playerid][1] = CreatePlayerTextDraw(playerid, 314.166656, 179.629623, "ISIM:~n~NUMARA:~n~HAKLAR:~n~LISANSLAR:~n~ADRES:");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][1], 0.154999, 1.081480);//0.226250, 1.008889);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][1], 0);

	MDC_LOOKUP_PERSON[playerid][2] = CreatePlayerTextDraw(playerid, 365.267486, 179.629623, "Blaze Test~n~811000~n~Yok~n~Surucu~n~Bulunmuyor");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][2], 0.154999, 1.081480);//0.226250, 1.008889);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][2], -2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][2], 0);

	MDC_LOOKUP_PERSON[playerid][3] = CreatePlayerTextDraw(playerid, 231.632064, 259.104095, "~l~KULLANILABILIR FONKSIYONLAR:"); //~>~ ÁÎËÜØÅ ÍÅ Â ÐÎÇÛÑÊÅ
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][3], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][3], 356.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][3], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][3], 0x494949FF);
	//PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][3], 1);
	//PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][3], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][3], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
	//PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][3], true);

	MDC_LOOKUP_PERSON[playerid][4] = CreatePlayerTextDraw(playerid, 231.632064, 274.767272, "~>~ TUTUKLAMA KAYDI YAZ");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][4], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][4], 356.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][4], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][4], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][4], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][4], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][4], true);

	MDC_LOOKUP_PERSON[playerid][5] = CreatePlayerTextDraw(playerid, 231.632064, 291.068267, "~>~ LISANSLARI YONET");//WRITE ARREST RECORD
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][5], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][5], 356.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][5], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][5], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][5], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][5], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][5], true);

	MDC_LOOKUP_PERSON[playerid][6] = CreatePlayerTextDraw(playerid, 231.365325, 307.244842, "~>~ CEZALARA BAK");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][6], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][6], 355.899932, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][6], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][6], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][6], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][6], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][6], true);

	MDC_LOOKUP_PERSON[playerid][7] = CreatePlayerTextDraw(playerid, 420.048706, 259.104095, "~y~]~w~__SUC_KAYITLARI__~y~]");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][7], 0.154999, 1.081480);//0.202914, 1.154072);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][7], 10.000000, 120.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][7], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][7], 255);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][7], 0x494949FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][7], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][7], true);

	MDC_LOOKUP_PERSON[playerid][8] = CreatePlayerTextDraw(playerid, 360.566833, 274.000030, "Belirsiz!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][8], 0.188333, 0.905185);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][8], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][8], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][8], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][8], 0);

	MDC_LOOKUP_PERSON[playerid][9] = CreatePlayerTextDraw(playerid, 269.999969, 242.159362, "~w~]_ARANIYOR!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][9], 0.129166, 0.874075);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][9], 0.000000, 77.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][9], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][9], 255);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][9], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][9], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][9], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][9], true);

	MDC_LOOKUP_PERSON[playerid][10] = CreatePlayerTextDraw(playerid, 314.583251, 231.270523, "] ADRESLER ICIN TIKLA");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][10], 0.202500, 1.024446);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][10], 480.000000, 20.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][10], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][10], 255);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][10], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][10], -5963521);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][10], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][10], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][10], true);

	MDC_LOOKUP_PERSON[playerid][11] = CreatePlayerTextDraw(playerid, 293.599700, 323.755554, "~y~0~w~~n~Odenmemis cezalar!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_PERSON[playerid][11], 0.129166, 0.874073);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_PERSON[playerid][11], 0.000000, 124.140029);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_PERSON[playerid][11], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_PERSON[playerid][11], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][11], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_PERSON[playerid][11], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_PERSON[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_PERSON[playerid][11], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_PERSON[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_PERSON[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_PERSON[playerid][11], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][11], true);

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- LOOKUP_VEHICLE_LIST --------------

	*/
	
	
	MDC_LOOKUP_VEHICLES_LIST[playerid][0] = CreatePlayerTextDraw(playerid, 230.416564, 174.185256, "");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 90.000000, 90.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], -1061109505);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 439);
	PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 0.000000, 0.000000, 90.000000, 0.879999);
	PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0], 1, 1);

	MDC_LOOKUP_VEHICLES_LIST[playerid][1] = CreatePlayerTextDraw(playerid, 383.933441, 188.444534, "SULTAN~n~1LASD1~n~Blaze Test~n~LEVEL 2~n~Hayir");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 0x8B8A8AFF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1], 0);

	MDC_LOOKUP_VEHICLES_LIST[playerid][2] = CreatePlayerTextDraw(playerid, 325.416625, 187.925994, "MODEL:~n~PLAKA:~n~SAHIP:~n~SIGORTA:~n~BAGLANMIS:");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2], 0);

	MDC_LOOKUP_VEHICLES_LIST[playerid][3] = CreatePlayerTextDraw(playerid, 237.183029, 190.800094, "!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0.179165, 0.962221);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0.000000, 9.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0);

	/*MDC_LOOKUP_VEHICLES_LIST[playerid][3] = CreatePlayerTextDraw(playerid, 277.299682, 192.337203, "]_Â ÐÎÇÛÑÊÅ!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0.129166, 0.874073);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3], true);*/

	MDC_LOOKUP_VEHICLES_LIST[playerid][4] = CreatePlayerTextDraw(playerid, 230.416564, 236.388870, "");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 90.000000, 90.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], -1061109505);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 5);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 0);
	PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 439);
	PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 0.000000, 0.000000, 90.000000, 0.879999);
	PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][4], 1, 1);

	MDC_LOOKUP_VEHICLES_LIST[playerid][5] = CreatePlayerTextDraw(playerid, 384.053527, 249.540466, "blaze");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 0x8B8A8AFF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][5], 0);

	MDC_LOOKUP_VEHICLES_LIST[playerid][6] = CreatePlayerTextDraw(playerid, 325.349945, 249.540466, "MODEL:~n~PLAKA:~n~SAHIP:~n~SIGORTA:~n~BAGLANMIS:");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][6], 0);

	MDC_LOOKUP_VEHICLES_LIST[playerid][7] = CreatePlayerTextDraw(playerid, 236.982955, 250.137298, "!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0.179165, 0.962221);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0.000000, 9.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0);

	/*MDC_LOOKUP_VEHICLES_LIST[playerid][7] = CreatePlayerTextDraw(playerid, 276.766235, 252.911254, "]_Â ÐÎÇÛÑÊÅ!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0.129166, 0.874073);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][7], true);*/

	MDC_LOOKUP_VEHICLES_LIST[playerid][8] = CreatePlayerTextDraw(playerid, 230.416564, 296.792480, "");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 90.000000, 90.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], -1061109505);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 5);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 0);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 0);
	PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 439);
	PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 0.000000, 0.000000, 90.000000, 0.879999);
	PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][8], 1, 1);

	MDC_LOOKUP_VEHICLES_LIST[playerid][9] = CreatePlayerTextDraw(playerid, 384.103698, 310.125671, "blaze");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 0x8B8A8AFF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][9], 0);

	MDC_LOOKUP_VEHICLES_LIST[playerid][10] = CreatePlayerTextDraw(playerid, 325.333190, 310.003814, "MODEL:~n~PLAKA:~n~SAHIP:~n~SIGORTA:~n~BAGLANMIS:");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][10], 0);

	/*MDC_LOOKUP_VEHICLES_LIST[playerid][11] = CreatePlayerTextDraw(playerid, 276.866363, 314.414978, "]_Â ÐÎÇÛÑÊÅ!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0.129166, 0.874073);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0.000000, 86.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], true);*/

	MDC_LOOKUP_VEHICLES_LIST[playerid][11] = CreatePlayerTextDraw(playerid, 237.249862, 310.840728, "!");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0.179165, 0.962221);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0.000000, 9.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], -1523963137);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][11], 0);

	MDC_VEH_LIST_CLICK[playerid][0] = CreatePlayerTextDraw(playerid, 468.351776, 192.081573, "_~n~_~n~_~n~>~n~_~n~_~n~_");
	PlayerTextDrawLetterSize(playerid, MDC_VEH_LIST_CLICK[playerid][0], 0.133748, 0.651109);
	PlayerTextDrawTextSize(playerid, MDC_VEH_LIST_CLICK[playerid][0], 30.000000, 12.000000);
	PlayerTextDrawAlignment(playerid, MDC_VEH_LIST_CLICK[playerid][0], 2);
	PlayerTextDrawColor(playerid, MDC_VEH_LIST_CLICK[playerid][0], 0x494949FF);//-1);
	PlayerTextDrawUseBox(playerid, MDC_VEH_LIST_CLICK[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, MDC_VEH_LIST_CLICK[playerid][0], 0xa7a7a7FF);//-2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_VEH_LIST_CLICK[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_VEH_LIST_CLICK[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_VEH_LIST_CLICK[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, MDC_VEH_LIST_CLICK[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_VEH_LIST_CLICK[playerid][0], true);

	MDC_VEH_LIST_CLICK[playerid][1] = CreatePlayerTextDraw(playerid, 468.418670, 250.882522, "_~n~_~n~_~n~>~n~_~n~_~n~_");
	PlayerTextDrawLetterSize(playerid, MDC_VEH_LIST_CLICK[playerid][1], 0.133748, 0.651109);
	PlayerTextDrawTextSize(playerid, MDC_VEH_LIST_CLICK[playerid][1], 30.000000, 12.000000);
	PlayerTextDrawAlignment(playerid, MDC_VEH_LIST_CLICK[playerid][1], 2);
	PlayerTextDrawColor(playerid, MDC_VEH_LIST_CLICK[playerid][1], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_VEH_LIST_CLICK[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, MDC_VEH_LIST_CLICK[playerid][1], 0xa7a7a7FF);//-2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_VEH_LIST_CLICK[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_VEH_LIST_CLICK[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_VEH_LIST_CLICK[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, MDC_VEH_LIST_CLICK[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_VEH_LIST_CLICK[playerid][1], true);

	MDC_VEH_LIST_CLICK[playerid][2] = CreatePlayerTextDraw(playerid, 468.501495, 311.212097, "_~n~_~n~_~n~>~n~_~n~_~n~_");
	PlayerTextDrawLetterSize(playerid, MDC_VEH_LIST_CLICK[playerid][2], 0.133748, 0.651109);
	PlayerTextDrawTextSize(playerid, MDC_VEH_LIST_CLICK[playerid][2], 30.000000, 12.000000);
	PlayerTextDrawAlignment(playerid, MDC_VEH_LIST_CLICK[playerid][2], 2);
	PlayerTextDrawColor(playerid, MDC_VEH_LIST_CLICK[playerid][2], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_VEH_LIST_CLICK[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_VEH_LIST_CLICK[playerid][2], 0xa7a7a7FF);//-2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_VEH_LIST_CLICK[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_VEH_LIST_CLICK[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_VEH_LIST_CLICK[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, MDC_VEH_LIST_CLICK[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_VEH_LIST_CLICK[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_VEH_LIST_CLICK[playerid][2], true);
		
	MDC_LOOKUP_VEHICLES_ARROWS[playerid][0] = CreatePlayerTextDraw(playerid, 356.816711, 424.493133, "1_/_2");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], 0);

	MDC_LOOKUP_VEHICLES_ARROWS[playerid][1] = CreatePlayerTextDraw(playerid, 424.404205, 424.493133, "~>~");
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 10.000000, 112.000000);
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 255);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][1], true);

	MDC_LOOKUP_VEHICLES_ARROWS[playerid][2] = CreatePlayerTextDraw(playerid, 289.212585, 424.493133, "~<~");
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 10.000000, 113.000000);
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0.228330, 0.889629);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 2);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 255);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][2], true);

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- LOOKUP_VEHICLE -------------------

	*/

	MDC_LOOKUP_VEHICLE[playerid][0] = CreatePlayerTextDraw(playerid, 230.416564, 174.185256, "");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 90.000000, 91.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][0], -1061109505);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 5);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0);
	PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 439);
	PlayerTextDrawSetPreviewRot(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 0.000000, 0.000000, 90.000000, 0.879998);
	PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLE[playerid][0], 1, 1);

	MDC_LOOKUP_VEHICLE[playerid][1] = CreatePlayerTextDraw(playerid, 383.933441, 188.444534, "SULTAN~n~1LASD1~n~Blaze Test~n~LEVEL 2~n~Hayir");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0x8B8A8AFF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][1], 0);

	MDC_LOOKUP_VEHICLE[playerid][2] = CreatePlayerTextDraw(playerid, 325.416625, 187.925994, "MODEL:~n~PLAKA:~n~SAHIP:~n~SIGORTA:~n~BAGLANMIS:~n~ALIM TARIHI:");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0.154999, 1.081480); //0.226248, 1.008888);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][2], 0);

	MDC_LOOKUP_VEHICLE[playerid][3] = CreatePlayerTextDraw(playerid, 233.082260, 284.141998, "NOTLAR:~n~- Bu arac calinmis 27/01/19~n~- Bu arac calinmis 17/02/19");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 479.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][3], -2147483393);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][3], true);

	MDC_LOOKUP_VEHICLE[playerid][4] = CreatePlayerTextDraw(playerid, 233.165451, 254.156051, "]_CEZALARA BAK__(ODENMEYEN CEZALAR:__14)");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 479.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][4], -5963521);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][4], true);

	MDC_LOOKUP_VEHICLE[playerid][5] = CreatePlayerTextDraw(playerid, 233.165451, 269.256958, "~dn~ NOT EKLE");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 349.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][5], true);

	MDC_LOOKUP_VEHICLE[playerid][6] = CreatePlayerTextDraw(playerid, 352.848785, 269.257019, "~up~ NOTU KALDIR");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 478.938964, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][6], true);

	MDC_LOOKUP_VEHICLE[playerid][7] = CreatePlayerTextDraw(playerid, 231.932281, 173.793121, "~>~ ARAC ARANMA, DURUM: ~g~ARANMIYOR");
	PlayerTextDrawLetterSize(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 478.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 1);
	PlayerTextDrawColor(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 255);
	PlayerTextDrawFont(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LOOKUP_VEHICLE[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_VEHICLE[playerid][7], true);

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- BACK -----------------------------

	*/

	MDC_BACK[playerid] = CreatePlayerTextDraw(playerid, 231.499237, 156.939529, "~<~ GERI DON");
	PlayerTextDrawLetterSize(playerid, MDC_BACK[playerid], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_BACK[playerid], 334.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_BACK[playerid], 1);
	PlayerTextDrawColor(playerid, MDC_BACK[playerid], 255);
	PlayerTextDrawSetShadow(playerid, MDC_BACK[playerid], 0);
	PlayerTextDrawSetOutline(playerid, MDC_BACK[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_BACK[playerid], 255);
	PlayerTextDrawFont(playerid, MDC_BACK[playerid], 2);
	PlayerTextDrawSetProportional(playerid, MDC_BACK[playerid], 1);
	PlayerTextDrawSetShadow(playerid, MDC_BACK[playerid], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_BACK[playerid], true);


	/*

		----------------------------- MDC- -----------------------------
		----------------------------- LIST INFO ------------------------

	*/

	/*MDC_LIST_INFO[playerid][0] = CreatePlayerTextDraw(playerid, 273.682678, 179.642364, "ID øòðàôà~n~Íàðóøèòåëü:~n~Îøòðàôîâàë~n~Ñóììà:~n~Äàòà~n~Ñòàòóñ:~n~~n~Îïèñàíèå:");
	PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][0], 0.208748, 1.226665);
	PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][0], 3);
	PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][0], 0);

	MDC_LIST_INFO[playerid][1] = CreatePlayerTextDraw(playerid, 281.983184, 179.642364, "#1012441~n~Jewking_Test~n~Rey_Test~n~$500~n~17/02/2019, 16:30:25~n~~r~NOT PAID");
	PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][1], 0.208748, 1.226665);
	PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][1], -2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][1], 0);

	MDC_LIST_INFO[playerid][2] = CreatePlayerTextDraw(playerid, 243.250045, 275.594299, "Way to way~n~ so glad to see you");
	PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][2], 0.208748, 1.226665);
	PlayerTextDrawTextSize(playerid, MDC_LIST_INFO[playerid][2], 467.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][2], -2139062017);
	PlayerTextDrawUseBox(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_LIST_INFO[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][2], 0);*/

	MDC_LIST_INFO[playerid][0] = CreatePlayerTextDraw(playerid, 274.365875, 179.772827, "ID:~n~test:~n~test:~n~test:~n~test:~n~test:~n~~n~test:");
	PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][0], 0.154999, 1.081480);
	PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][0], 3);
	PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][0], 255);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][0], 0);

	MDC_LIST_INFO[playerid][1] = CreatePlayerTextDraw(playerid, 282.399841, 179.642364, "#1012441~n~Jewking_Test~n~Rey_Test~n~$500~n~17/02/2019, 16:30:25~n~~r~ODENMEMIS");
	PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][1], 0.183748, 1.081479);
	PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][1], -2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][1], 0);

	MDC_LIST_INFO[playerid][2] = CreatePlayerTextDraw(playerid, 243.232818, 258.457458, "- Yanlis konuma park edilmis.");
	PlayerTextDrawLetterSize(playerid, MDC_LIST_INFO[playerid][2], 0.183748, 1.081479);
	PlayerTextDrawAlignment(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_LIST_INFO[playerid][2], -2139062017);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_LIST_INFO[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_LIST_INFO[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, MDC_LIST_INFO[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_LIST_INFO[playerid][2], 0);

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- MENU INFO ------------------------

	*/


    MDC_LIC[playerid][0] = CreatePlayerTextDraw(playerid, 233.849990, 173.925918, "box");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][0], 0.000000, 6.250006);
    PlayerTextDrawTextSize(playerid, MDC_LIC[playerid][0], 352.000000, 0.000000);
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][0], 1);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][0], -1);
    PlayerTextDrawUseBox(playerid, MDC_LIC[playerid][0], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LIC[playerid][0], -1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][0], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][0], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][0], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][0], 0);

    MDC_LIC[playerid][1] = CreatePlayerTextDraw(playerid, 292.916809, 174.207412, "SURUCU LISANSI");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][1], 0.154999, 1.081480);//0.207083, 1.185184);
    PlayerTextDrawTextSize(playerid, MDC_LIC[playerid][1], 0.000000, 117.840393); 
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][1], 2);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][1], -1);
    PlayerTextDrawUseBox(playerid, MDC_LIC[playerid][1], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LIC[playerid][1], 339643903);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][1], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][1], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][1], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][1], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][1], 0);

    MDC_LIC[playerid][2] = CreatePlayerTextDraw(playerid, 232.766403, 169.074020, "hud:radar_impound");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][2], 0.000000, 0.000000);
    PlayerTextDrawTextSize(playerid, MDC_LIC[playerid][2], 15.000000, 17.000000);
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][2], 1);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][2], -1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][2], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][2], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][2], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][2], 4);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][2], 0);

    MDC_LIC[playerid][3] = CreatePlayerTextDraw(playerid, 298.232727, 190.286605, "Durum:_~n~Uyarilar:");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][3], 0.154999, 1.081480);
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][3], 3);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][3], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][3], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][3], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][3], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][3], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][3], 0);

    MDC_LIC[playerid][4] = CreatePlayerTextDraw(playerid, 302.933013, 190.286605, "~g~BULUNUYOR~n~~r~3");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][4], 0.154999, 1.081480);
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][4], 1);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][4], 255);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][4], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][4], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][4], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][4], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LIC[playerid][4], true);

    MDC_LIC[playerid][5] = CreatePlayerTextDraw(playerid, 236.332046, 217.074813, "__EL KOY");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][5], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LIC[playerid][5], 266.200012, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][5], 1);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][5], -1);//0xabababFF);
    PlayerTextDrawUseBox(playerid, MDC_LIC[playerid][5], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LIC[playerid][5], 0xdd1717FF);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][5], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][5], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][5], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][5], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][5], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LIC[playerid][5], true);

    MDC_LIC[playerid][6] = CreatePlayerTextDraw(playerid, 270.098724, 217.074798, "~>~_UYARI EKLE");
    PlayerTextDrawLetterSize(playerid, MDC_LIC[playerid][6], 0.154999, 1.081480);
    PlayerTextDrawTextSize(playerid, MDC_LIC[playerid][6], 349.000000, 10.000000);
    PlayerTextDrawAlignment(playerid, MDC_LIC[playerid][6], 1);
    PlayerTextDrawColor(playerid, MDC_LIC[playerid][6], 0x494949FF);
    PlayerTextDrawUseBox(playerid, MDC_LIC[playerid][6], 1);
    PlayerTextDrawBoxColor(playerid, MDC_LIC[playerid][6], 0xa7a7a7FF);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][6], 0);
    PlayerTextDrawSetOutline(playerid, MDC_LIC[playerid][6], 0);
    PlayerTextDrawBackgroundColor(playerid, MDC_LIC[playerid][6], 255);
    PlayerTextDrawFont(playerid, MDC_LIC[playerid][6], 2);
    PlayerTextDrawSetProportional(playerid, MDC_LIC[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, MDC_LIC[playerid][6], 0);
    PlayerTextDrawSetSelectable(playerid, MDC_LIC[playerid][6], true);


	/*

		----------------------------- MDC- -----------------------------
		----------------------------- APB INFO ------------------------

	*/

	for (new i; i < 5; i++)
	{
		x = 284.999938, y = 175.220901, d = (224.223892 - y)*i;
		MDC_APB_TD[playerid][4*i] = CreatePlayerTextDraw(playerid, x, y+d, "SUPHELI:_~n~BILGI:_~n~EKLEYEN:");
		PlayerTextDrawTextSize(playerid, MDC_APB_TD[playerid][4*i], -200.799865, 0.000000);
		PlayerTextDrawLetterSize(playerid, MDC_APB_TD[playerid][4*i], 0.154999, 1.081480);
		PlayerTextDrawAlignment(playerid, MDC_APB_TD[playerid][4*i], 3);
		PlayerTextDrawColor(playerid, MDC_APB_TD[playerid][4*i], 255);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i], 0);
		PlayerTextDrawSetOutline(playerid, MDC_APB_TD[playerid][4*i], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_APB_TD[playerid][4*i], 255);
		PlayerTextDrawFont(playerid, MDC_APB_TD[playerid][4*i], 1);//2);
		PlayerTextDrawSetProportional(playerid, MDC_APB_TD[playerid][4*i], 1);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i], 0);

		x = 290.483642, y = 175.220901, d = (224.223892 - y)*i;
		MDC_APB_TD[playerid][4*i+1] = CreatePlayerTextDraw(playerid, x, y+d, "text");
		PlayerTextDrawLetterSize(playerid, MDC_APB_TD[playerid][4*i+1], 0.1549, 1.0814);
		PlayerTextDrawTextSize(playerid, MDC_APB_TD[playerid][4*i+1], 478.0000, 0.0000);
		PlayerTextDrawAlignment(playerid, MDC_APB_TD[playerid][4*i+1], 1);
		PlayerTextDrawColor(playerid, MDC_APB_TD[playerid][4*i+1], -2139062017);
		PlayerTextDrawUseBox(playerid, MDC_APB_TD[playerid][4*i+1], 1);
		PlayerTextDrawBoxColor(playerid, MDC_APB_TD[playerid][4*i+1], -1);
		PlayerTextDrawBackgroundColor(playerid, MDC_APB_TD[playerid][4*i+1], -1);
		PlayerTextDrawFont(playerid, MDC_APB_TD[playerid][4*i+1], 1);
		PlayerTextDrawSetProportional(playerid, MDC_APB_TD[playerid][4*i+1], 1);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i+1], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_APB_TD[playerid][4*i+1], true);

		x = 291.933532, y = 206.661392, d = (256.664382 - y)*i;
		MDC_APB_TD[playerid][4*i+2] = CreatePlayerTextDraw(playerid, x, y+d, "~>~ Detaylar");
		PlayerTextDrawLetterSize(playerid, MDC_APB_TD[playerid][4*i+2], 0.154999, 1.081480);
		PlayerTextDrawTextSize(playerid, MDC_APB_TD[playerid][4*i+2], 386.899871, 10.000000);
		PlayerTextDrawAlignment(playerid, MDC_APB_TD[playerid][4*i+2], 1);
		PlayerTextDrawColor(playerid, MDC_APB_TD[playerid][4*i+2], -1061109505);
		PlayerTextDrawUseBox(playerid, MDC_APB_TD[playerid][4*i+2], 1);
		PlayerTextDrawBoxColor(playerid, MDC_APB_TD[playerid][4*i+2], 0x494949FF);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i+2], 0);
		PlayerTextDrawSetOutline(playerid, MDC_APB_TD[playerid][4*i+2], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_APB_TD[playerid][4*i+2], 255);
		PlayerTextDrawFont(playerid, MDC_APB_TD[playerid][4*i+2], 1);
		PlayerTextDrawSetProportional(playerid, MDC_APB_TD[playerid][4*i+2], 1);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i+2], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_APB_TD[playerid][4*i+2], true);
		
		x = 392.950042, y = 206.661392, d = (256.664382 - y)*i;
		
		MDC_APB_TD[playerid][4*i+3] = CreatePlayerTextDraw(playerid, x, y+d, "~>~ Kaldir");
		PlayerTextDrawLetterSize(playerid, MDC_APB_TD[playerid][4*i+3], 0.154999, 1.081480);
		PlayerTextDrawTextSize(playerid, MDC_APB_TD[playerid][4*i+3], 477.799865, 10.000000);
		PlayerTextDrawAlignment(playerid, MDC_APB_TD[playerid][4*i+3], 1);
		PlayerTextDrawColor(playerid, MDC_APB_TD[playerid][4*i+3], -1061109505);
		PlayerTextDrawUseBox(playerid, MDC_APB_TD[playerid][4*i+3], 1);
		PlayerTextDrawBoxColor(playerid, MDC_APB_TD[playerid][4*i+3], 0x494949FF);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i+3], 0);
		PlayerTextDrawSetOutline(playerid, MDC_APB_TD[playerid][4*i+3], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_APB_TD[playerid][4*i+3], 255);
		PlayerTextDrawFont(playerid, MDC_APB_TD[playerid][4*i+3], 1);
		PlayerTextDrawSetProportional(playerid, MDC_APB_TD[playerid][4*i+3], 1);
		PlayerTextDrawSetShadow(playerid, MDC_APB_TD[playerid][4*i+3], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_APB_TD[playerid][4*i+3], true);
	}

	/*

		----------------------------- MDC- -----------------------------
		----------------------------- MDC CALLS TD ------------------------

	*/
	for (new i; i < 5; i++)
	{
		x = 233.333267, y = 156.957977, d = (209.361175 - y)*i;
		MDC_CALLS_TD[playerid][4*i] = CreatePlayerTextDraw(playerid, x, y+d, "Arayan:~n~Servis:~n~Lokasyon:~n~Durum:~n~Zaman:~n~Durum:");
		PlayerTextDrawLetterSize(playerid, MDC_CALLS_TD[playerid][4*i], 0.162082, 0.879257);
		PlayerTextDrawTextSize(playerid, MDC_CALLS_TD[playerid][4*i], 481.000000, 0.000000);
		PlayerTextDrawAlignment(playerid, MDC_CALLS_TD[playerid][4*i], 1);
		PlayerTextDrawColor(playerid, MDC_CALLS_TD[playerid][4*i], 255);
		PlayerTextDrawUseBox(playerid, MDC_CALLS_TD[playerid][4*i], 1);
		PlayerTextDrawBoxColor(playerid, MDC_CALLS_TD[playerid][4*i], -1);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i], 0);
		PlayerTextDrawSetOutline(playerid, MDC_CALLS_TD[playerid][4*i], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_CALLS_TD[playerid][4*i], 255);
		PlayerTextDrawFont(playerid, MDC_CALLS_TD[playerid][4*i], 1);
		PlayerTextDrawSetProportional(playerid, MDC_CALLS_TD[playerid][4*i], 1);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i], 0);

		x = 266.035247, y = 156.957977, d = (209.361175 - y)*i;
		MDC_CALLS_TD[playerid][4*i+1] = CreatePlayerTextDraw(playerid, x, y+d, "Blaze_Test~n~SASD, SAFD~n~Palomino Creek, Gross Street, 16~n~YARDIM!! BENI OLDURECEKLER ..~n~15.02.19 12:01~n~~r~NOT HANDLED");
		PlayerTextDrawLetterSize(playerid, MDC_CALLS_TD[playerid][4*i+1], 0.162082, 0.879257);
		PlayerTextDrawAlignment(playerid, MDC_CALLS_TD[playerid][4*i+1], 1);
		PlayerTextDrawColor(playerid, MDC_CALLS_TD[playerid][4*i+1], 0x494949FF);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i+1], 0);
		PlayerTextDrawSetOutline(playerid, MDC_CALLS_TD[playerid][4*i+1], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_CALLS_TD[playerid][4*i+1], 255);
		PlayerTextDrawFont(playerid, MDC_CALLS_TD[playerid][4*i+1], 1);
		PlayerTextDrawSetProportional(playerid, MDC_CALLS_TD[playerid][4*i+1], 1);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i+1], 0);

		x = 370.032806, y = 194.902206, d = (247.305404 - y)*i; 
		MDC_CALLS_TD[playerid][4*i+2] = CreatePlayerTextDraw(playerid, x, y+d, " ~>~ KABUL ET");
		PlayerTextDrawLetterSize(playerid, MDC_CALLS_TD[playerid][4*i+2], 0.154999, 1.081480);
		PlayerTextDrawTextSize(playerid, MDC_CALLS_TD[playerid][4*i+2], 427.000000, 10.000000);
		PlayerTextDrawAlignment(playerid, MDC_CALLS_TD[playerid][4*i+2], 1);
		PlayerTextDrawColor(playerid, MDC_CALLS_TD[playerid][4*i+2], -1);//0xa7a7a7FF);
		PlayerTextDrawUseBox(playerid, MDC_CALLS_TD[playerid][4*i+2], 1);
		PlayerTextDrawBoxColor(playerid, MDC_CALLS_TD[playerid][4*i+2], -1523963137);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i+2], 0);
		PlayerTextDrawSetOutline(playerid, MDC_CALLS_TD[playerid][4*i+2], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_CALLS_TD[playerid][4*i+2], 255);
		PlayerTextDrawFont(playerid, MDC_CALLS_TD[playerid][4*i+2], 1);
		PlayerTextDrawSetProportional(playerid, MDC_CALLS_TD[playerid][4*i+2], 1);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i+2], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_CALLS_TD[playerid][4*i+2], true);

		x = 428.850189, y = 194.902206, d = (247.305404 - y)*i; 
		MDC_CALLS_TD[playerid][4*i+3] = CreatePlayerTextDraw(playerid, x, y+d, " ~>~ DETAYLAR");
		PlayerTextDrawLetterSize(playerid, MDC_CALLS_TD[playerid][4*i+3], 0.154999, 1.081480);
		PlayerTextDrawTextSize(playerid, MDC_CALLS_TD[playerid][4*i+3], 481.000000, 10.000000);
		PlayerTextDrawAlignment(playerid, MDC_CALLS_TD[playerid][4*i+3], 1);
		PlayerTextDrawColor(playerid, MDC_CALLS_TD[playerid][4*i+3], -1);//0xa7a7a7FF);
		PlayerTextDrawUseBox(playerid, MDC_CALLS_TD[playerid][4*i+3], 1);
		PlayerTextDrawBoxColor(playerid, MDC_CALLS_TD[playerid][4*i+3], 255);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i+3], 0);
		PlayerTextDrawSetOutline(playerid, MDC_CALLS_TD[playerid][4*i+3], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_CALLS_TD[playerid][4*i+3], 255);
		PlayerTextDrawFont(playerid, MDC_CALLS_TD[playerid][4*i+3], 1);
		PlayerTextDrawSetProportional(playerid, MDC_CALLS_TD[playerid][4*i+3], 1);
		PlayerTextDrawSetShadow(playerid, MDC_CALLS_TD[playerid][4*i+3], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_CALLS_TD[playerid][4*i+3], true);
	}
	
	/*

		----------------------------- MDC- -----------------------------
		----------------------------- LIST -----------------------------

	*/

	x = 232.799331, y = 172.383117, d = 185.783935 - y;
	for (new i = 0; i < 16; i++) 
	{
		MDC_LIST[playerid][i] = CreatePlayerTextDraw(playerid, x, y, "list");
		PlayerTextDrawLetterSize(playerid, MDC_LIST[playerid][i], 0.154999, 1.081480);
		PlayerTextDrawTextSize(playerid, MDC_LIST[playerid][i], 479.100006, 9.900000);
		PlayerTextDrawAlignment(playerid, MDC_LIST[playerid][i], 1);
		PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], -1);
		PlayerTextDrawUseBox(playerid, MDC_LIST[playerid][i], 1);
		PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], -1523963137);
		PlayerTextDrawSetShadow(playerid, MDC_LIST[playerid][i], 0);
		PlayerTextDrawSetOutline(playerid, MDC_LIST[playerid][i], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_LIST[playerid][i], 255);
		PlayerTextDrawFont(playerid, MDC_LIST[playerid][i], 1);
		PlayerTextDrawSetProportional(playerid, MDC_LIST[playerid][i], 1);
		PlayerTextDrawSetShadow(playerid, MDC_LIST[playerid][i], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_LIST[playerid][i], true);
		
		y += d;
	}

	/*
		
		============================= MDC- =============================
		============================= ROSTER ==========================

	*/

	x = 232.799331, y = 171.983093, d = 185.383911 - y;
	for (new i = 0; i < MAX_TD_MENU_SIZE; i++) 
	{
		MDC_TD_MENU[playerid][i] = CreatePlayerTextDraw(playerid, x, y, "list");
		PlayerTextDrawLetterSize(playerid, MDC_TD_MENU[playerid][i], 0.154999, 1.081480);
		PlayerTextDrawTextSize(playerid, MDC_TD_MENU[playerid][i], 408.000000, 10.000000);
		PlayerTextDrawAlignment(playerid, MDC_TD_MENU[playerid][i], 1);
		PlayerTextDrawColor(playerid, MDC_TD_MENU[playerid][i], 0x494949FF);
		PlayerTextDrawUseBox(playerid, MDC_TD_MENU[playerid][i], 1);
		PlayerTextDrawBoxColor(playerid, MDC_TD_MENU[playerid][i], 0xa7a7a7FF);
		PlayerTextDrawSetShadow(playerid, MDC_TD_MENU[playerid][i], 0);
		PlayerTextDrawSetOutline(playerid, MDC_TD_MENU[playerid][i], 0);
		PlayerTextDrawBackgroundColor(playerid, MDC_TD_MENU[playerid][i], 255);
		PlayerTextDrawFont(playerid, MDC_TD_MENU[playerid][i], 1);
		PlayerTextDrawSetProportional(playerid, MDC_TD_MENU[playerid][i], 1);
		PlayerTextDrawSetShadow(playerid, MDC_TD_MENU[playerid][i], 0);
		PlayerTextDrawSetSelectable(playerid, MDC_TD_MENU[playerid][i], true);
		
		y += d;
	}

	MDC_TD_LEFT_PANEL[playerid][0] = CreatePlayerTextDraw(playerid, 232.682266, 158.646331, "Aktif birimler:");
	PlayerTextDrawLetterSize(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_TD_LEFT_PANEL[playerid][0], 408.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_TD_LEFT_PANEL[playerid][0], 1);
	PlayerTextDrawColor(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0xa7a7a7FF);
	PlayerTextDrawUseBox(playerid, MDC_TD_LEFT_PANEL[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0x494949FF);
	PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_TD_LEFT_PANEL[playerid][0], 255);
	PlayerTextDrawFont(playerid, MDC_TD_LEFT_PANEL[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, MDC_TD_LEFT_PANEL[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][0], 0);

	MDC_TD_LEFT_PANEL[playerid][1] = CreatePlayerTextDraw(playerid, 413.582427, 158.543823, "Birim belirle");
	PlayerTextDrawLetterSize(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_TD_LEFT_PANEL[playerid][1], 481.000000, 10.000000);
	PlayerTextDrawAlignment(playerid, MDC_TD_LEFT_PANEL[playerid][1], 1);
	PlayerTextDrawColor(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0xa7a7a7FF);
	PlayerTextDrawUseBox(playerid, MDC_TD_LEFT_PANEL[playerid][1], 1);
	PlayerTextDrawBoxColor(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0x494949FF);
	PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_TD_LEFT_PANEL[playerid][1], 255);
	PlayerTextDrawFont(playerid, MDC_TD_LEFT_PANEL[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, MDC_TD_LEFT_PANEL[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_TD_LEFT_PANEL[playerid][1], true);

	MDC_TD_LEFT_PANEL[playerid][2] = CreatePlayerTextDraw(playerid, 413.582427, 172.144653, "LINCOLN-1");
	PlayerTextDrawLetterSize(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_TD_LEFT_PANEL[playerid][2], 481.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_TD_LEFT_PANEL[playerid][2], 1);
	PlayerTextDrawColor(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_TD_LEFT_PANEL[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_TD_LEFT_PANEL[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_TD_LEFT_PANEL[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_TD_LEFT_PANEL[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, MDC_TD_LEFT_PANEL[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_TD_LEFT_PANEL[playerid][2], 0);

 	MDC_UI[playerid][2] = CreatePlayerTextDraw(playerid, 189.965499, 156.437500, "ANA PANEL");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][2], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][2], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][2], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][2], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][2], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][2], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][2], true);

	MDC_UI[playerid][3] = CreatePlayerTextDraw(playerid, 189.965499, 172.393096, "ARAMA YAP");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][3], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][3], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][3], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][3], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][3], true);

	MDC_UI[playerid][4] = CreatePlayerTextDraw(playerid, 189.965499, 188.467193, "CAGRILAR");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][4], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][4], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][4], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][4], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][4], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][4], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][4], true);

	MDC_UI[playerid][5] = CreatePlayerTextDraw(playerid, 189.948852, 204.422760, "MEMURLAR");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][5], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][5], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][5], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][5], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][5], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][5], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][5], true);

	MDC_UI[playerid][6] = CreatePlayerTextDraw(playerid, 189.965484, 220.733901, "APB");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][6], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][6], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][6], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][6], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][6], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][6], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][6], true);

	MDC_UI[playerid][7] = CreatePlayerTextDraw(playerid, 189.848831, 253.346023, "BIRIMLER");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][7], 0.154999, 1.081480); 
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][7], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][7], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][7], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][7], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][7], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][7], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][7], true);

	MDC_UI[playerid][8] = CreatePlayerTextDraw(playerid, 189.865478, 269.675598, "CCTV");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][8], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][8], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][8], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][8], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][8], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][8], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][8], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][8], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][8], true);

	MDC_UI[playerid][10] = CreatePlayerTextDraw(playerid, 189.865478, 286.212646, "");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][10], 0.154999, 1.081480);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][10], 10.000000, 66.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][10], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][10], 0x494949FF);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][10], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][10], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][10], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][10], 2);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][10], 0);
	PlayerTextDrawSetSelectable(playerid, MDC_UI[playerid][10], true);

	MDC_UI[playerid][11] = CreatePlayerTextDraw(playerid, 189.866012, 414.188751, "MDC V1.0~n~ERISIM:~n~Blaze Test");
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][11], 0.162082, 0.796296);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][11], 2);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][11], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][11], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][11], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][11], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][11], 1);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][11], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][11], 0);

	MDC_UI[playerid][12] = CreatePlayerTextDraw(playerid, 228.099792, 154.585281, "line"); // 
	PlayerTextDrawLetterSize(playerid, MDC_UI[playerid][12], 0.000000, 31.291673);
	PlayerTextDrawTextSize(playerid, MDC_UI[playerid][12], 226.799926, 0.000000);
	PlayerTextDrawAlignment(playerid, MDC_UI[playerid][12], 1);
	PlayerTextDrawColor(playerid, MDC_UI[playerid][12], -1);
	PlayerTextDrawUseBox(playerid, MDC_UI[playerid][12], 1);
	PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][12], 0xa7a7a7FF);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][12], 0);
	PlayerTextDrawSetOutline(playerid, MDC_UI[playerid][12], 0);
	PlayerTextDrawBackgroundColor(playerid, MDC_UI[playerid][12], 255);
	PlayerTextDrawFont(playerid, MDC_UI[playerid][12], 1);
	PlayerTextDrawSetProportional(playerid, MDC_UI[playerid][12], 1);
	PlayerTextDrawSetShadow(playerid, MDC_UI[playerid][12], 0);
   

    return 1;
}

MDC_PAGE(playerid, page)
{
    Update_MDC(playerid, page);
    
    switch(page)
    {
        case PAGE_MAIN:
        {
            PlayerTextDrawSetPreviewModel(playerid, MDC_MAINSCREEN[playerid][0], GetPlayerSkin(playerid));
            PlayerTextDrawShow(playerid, MDC_MAINSCREEN[playerid][0]);

            new string[124];
            format(string, sizeof(string), "%s %s", GetRankName(playerid), GetNameEx(playerid));
            PlayerTextDrawSetString(playerid, MDC_MAINSCREEN[playerid][2], TurkishCharFix(string));

            //                             "ÑÎÒÐÓÄÍÈÊÎÂ ÍÀ ÑËÓÆÁÅ:~n~ÎÐÄÅÐÛ:~n~Â ÐÎÇÛÑÊÅ:");
            format(string, sizeof(string), "%i~n~TBA~n~TBA", MembersOnline(playerid));
            PlayerTextDrawSetString(playerid, MDC_MAINSCREEN[playerid][4], string);

            //                            "ÏÐÈÍßÒÎ ÂÛÇÎÂÎÂ:~n~ÀÐÅÑÒÎÂÀÍÎ:~n~ÂÛÏÈÑÀÍÎ ØÒÐÀÔÎÂ:");
            format(string, sizeof(string), "%i~n~%i~n~%i", pTemp[playerid][pPoliceCalls], pTemp[playerid][pPoliceJails], pTemp[playerid][pPoliceFines]);
            PlayerTextDrawSetString(playerid, MDC_MAINSCREEN[playerid][6], string);

	        format(string, sizeof(string), "%s MDC ~>~ Ana Panel", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], TurkishCharFix(string));


            // PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
	        // PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF); // ÈÌß
        }
        case PAGE_APB:
        {
            new count,
                string[256]
            ;

            SetPVarInt(playerid, #MDC_APB_S, 0);

            for(new i = MAX_APBS-1; i >= 0; i--)
            {
                if (ApbInfo[i][apbOn] == 0) continue;

                if (count < 5)
                {
                    format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
                    PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][count*4+1], TurkishCharFix(string));

                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
                }
                count++;
            }

            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][0], "EKLE");
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "ISIM");
                                                                            // ÏÎ ÎÏÈÑ.
            MdcInfo[playerid][mdcSearch] = 0;

            if (!count) PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
            else
            {
                if (count > 5)
                {
                    for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

                    count = floatround(float(count)/5.0, floatround_ceil);
                    SetPVarInt(playerid, #MAX_MDC_PAGE, count);

                    MdcInfo[playerid][mdcListPage] = 0;

                    format(string, sizeof(string), "1_/_%i", count);
                    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], string);
                }
            }
        }
        case PAGE_CALLS:
        {
            PlayerTextDrawHide(playerid, MDC_ERROR_CALLS[playerid]);

            new
                string[512],
                count,
                type = (IsPlayerFactionMedic(playerid) || IsPlayerFactionFire(playerid))?(2):(1)
            ;

            for(new i = MAX_CALLS_AND_ARREST-1; i >= 0; i--)
            {
                if (CallInfo[i][callExists] == 0) continue;

                if (CallInfo[i][callType] != 3)
                    if (CallInfo[i][callType] != type) continue;

                switch(CallInfo[i][callType])
                {
                    case 1: format(string, sizeof(string), "LCPD");
                    case 2: format(string, sizeof(string), "YANGIN DEPARTMANI");
                    case 3: format(string, sizeof(string), "MEDIKAL DEPARTMAN");
                }

                if (count < 5)
                {
                    new statusmes[65];
                    if (CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
                    else format(statusmes, sizeof(statusmes), "~r~Isleme Alinmamis");

                    format(string, sizeof(string), "%s (No %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s",
                        CallInfo[i][callName],
                        CallInfo[i][callPhone],
                        string,
                        CallInfo[i][callLocation],
                        CallInfo[i][callText],
                        (strlen(CallInfo[i][callText]) > 60)?(" .."):(""),
                        CallInfo[i][callDate],
                        statusmes
                    );
                    PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][count*4+1], TurkishCharFix(string));
                    
                    MdcInfo[count][mdcList] = i;
                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_CALLS_TD[playerid][j]);
                    if (CallInfo[i][callAccept]) PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][count*4+2]);
                }
                count++;
            }

            if (!count) 
            {
                PlayerTextDrawShow(playerid, MDC_ERROR_CALLS[playerid]);
                PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "]__HATA: HICBIR SEY BULUNAMADI!");
            }

            else
            {
                if (count > 5)
                {
                    for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

                    count = floatround(float(count)/5.0, floatround_ceil);
                    SetPVarInt(playerid, #MAX_MDC_PAGE, count);

                    MdcInfo[playerid][mdcListPage] = 0;

                    format(string, sizeof(string), "1_/_%i", count);
                    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], string);
                }
            }
        }
        
        case PAGE_CCTV:
        {
            new query[255];
            mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cctvs` ORDER BY `id` LIMIT 16");
            mysql_tquery(dbHandle, query, "MDC_ShowCCTVMenu", "ii", playerid, 0);

            MdcInfo[playerid][mdcListPage] = 0;
            //MdcInfo[playerid][mdcMenu] = PAGE_CCTV;

            new Float:countcctvs = MDC_CountCCTVS();
            countcctvs = countcctvs/16;
            SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countcctvs, floatround_ceil));
        }
        case PAGE_ROSTER:
        {
            MdcInfo[playerid][mdcListPage] = 0;
            MdcInfo[playerid][mdcMenu] = PAGE_ROSTER;

            new Float:countRoster = MDC_CountRoster();
            countRoster = countRoster/18;
            SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countRoster, floatround_ceil));

            MDC_ShowRosterMenu(playerid);
        }
        case PAGE_MEMBERS:
        {
            MdcInfo[playerid][mdcListPage] = 0;
            MdcInfo[playerid][mdcMenu] = PAGE_MEMBERS;

            new Float:countMembers = MembersOnline(playerid);
            countMembers = countMembers/18;
            SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countMembers, floatround_ceil));

            MDC_ShowMembersMenu(playerid);
        }
    }
    return 1;
}

Update_MDC(playerid, page)
{
    new oldpage = MdcInfo[playerid][mdcPage];

    if (oldpage == page) return 1;

    if ((oldpage == PAGE_LOOKUP_PERSON || oldpage == PAGE_LOOKUP_VEHICLE || oldpage == PAGE_LOOKUP || oldpage == PAGE_LOOKUP_VEHICLES_LIST) && page == PAGE_LOOKUP)
        return 1;

    MdcInfo[playerid][mdcPage] = page;

    for(new z = 2; z < 13; z++)
    {
        PlayerTextDrawColor(playerid, MDC_UI[playerid][z], 0x494949FF);
        PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][z], 0xa7a7a7FF);
        PlayerTextDrawShow(playerid, MDC_UI[playerid][z]);
    }

    switch(oldpage)
    {
        case PAGE_MAIN:
        {
            for(new y = 0; y < 7; y++)  PlayerTextDrawHide(playerid, MDC_MAINSCREEN[playerid][y]);
        }
        case PAGE_LOOKUP:
        {
            if (page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLE && page != PAGE_LOOKUP_VEHICLES_LIST)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
                PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
            }
        }
        case PAGE_LOOKUP_PERSON:
        {
            if (page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLE && page != PAGE_LOOKUP_VEHICLES_LIST)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }

            for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
            for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_LOOKUP_VEHICLE:
        {
            if (page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLE && page != PAGE_LOOKUP_VEHICLES_LIST)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }
            else
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }

            for(new a = 0; a < 8; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLE[playerid][a]);

            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_LOOKUP_VEHICLES_LIST:
        {
            if (page != PAGE_LOOKUP && page != PAGE_LOOKUP_PERSON && page != PAGE_LOOKUP_VEHICLES_LIST && page != PAGE_LOOKUP_VEHICLE)
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            }
            //if (page == PAGE_LOOKUP_VEHICLE) PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            for(new a = 0; a < 12; a++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
            for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
            for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_MENU:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LIST[playerid][a]);

            if (GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
        }
        case PAGE_INFO:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            for(new a = 0; a < 3; a++)  PlayerTextDrawHide(playerid, MDC_LIST_INFO[playerid][a]);
        }
        case PAGE_MAP:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);

            for(new j = 0; j < 6; j++) PlayerTextDrawHide(playerid, MDC_OTHER_ADDRESS[playerid][j]);
            for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, MDC_ADDRESS[playerid][i]);

            PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][2]);
            MDC_ADDRESS[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
        }
        case PAGE_MEMBERS_MAP:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);

            for(new j = 0; j < 6; j++) PlayerTextDrawHide(playerid, MDC_OTHER_ADDRESS[playerid][j]);
            for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, MDC_ADDRESS[playerid][i]);
            for(new i = 0; i < 5; i++) PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][i]);
            for(new a = 0; a < 2; a++) PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
        
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][4], "~>~ TUTUKLUK KAYDI YAZIN");
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][3], "~l~MEVCUT FONKSÝYON:");
            //PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][3], true);
            //PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][3], true);

            PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][2]);
            MDC_ADDRESS[playerid][2] = PlayerText:INVALID_TEXT_DRAW;

            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);

            DeletePVar(playerid, #BODYCAM);
        }
        case PAGE_LIC:
        {
            PlayerTextDrawHide(playerid, MDC_BACK[playerid]);

            for(new i = 0; i < 32; i++) PlayerTextDrawHide(playerid, MDC_LIC[playerid][i]);
        }
        case PAGE_APB:
        {
            for(new a = 0; a < 4; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][a]);
            for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
            for(new i = 0; i < 20; i++) PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][i]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_CALLS:
        {
            for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
            for(new i = 0; i < 20; i++) PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][i]);
            PlayerTextDrawHide(playerid, MDC_ERROR_CALLS[playerid]);
        }

        case PAGE_CCTV:
        {
            PlayerTextDrawHide(playerid, MDC_ERROR_CALLS[playerid]);

            for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LIST[playerid][a]);

            if (GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
        }

        case PAGE_ROSTER, PAGE_MEMBERS:
        {
            for(new j = 0; j < 3; j++)   PlayerTextDrawHide(playerid, MDC_TD_LEFT_PANEL[playerid][j]);
            for(new i = 0; i < 18; i++)  PlayerTextDrawHide(playerid, MDC_TD_MENU[playerid][i]);
        }
    }

    switch(page)
    {
        case PAGE_MAIN:
        {
            for(new y = 0; y < 7; y++)  PlayerTextDrawShow(playerid, MDC_MAINSCREEN[playerid][y]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][2], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][2], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][2]);
            
            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Ana Menu", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }
        case PAGE_LOOKUP:
        {
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Arama Yap", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);

            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][0], "ISIM");
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "PLAKA");

            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
	        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF); // ÈÌß

            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
	        PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF); // ÒÑ

            for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            MdcInfo[playerid][mdcSearch] = 0;
            //PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
        }
        case PAGE_LOOKUP_PERSON:
        {
            for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            //for(new a = 0; a < 2; a++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
            for(new b = 0; b < 12; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][10]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            //PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Arama Yap", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }
        case PAGE_LOOKUP_VEHICLE:
        {
            //PlayerTextDrawSetString(playerid, MDC_BACK[playerid], "~<~ ÂÅÐÍÓÒÜÑß ÍÀÇÀÄ");

            if (GetPVarInt(playerid, #MDC_VEH_BACK))
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
                PlayerTextDrawShow(playerid, MDC_BACK[playerid]);
            }
            else
            {
                for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
                PlayerTextDrawHide(playerid, MDC_BACK[playerid]);
            }

            //for(new a = 0; a < 12; a++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
            //for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            for(new i = 0; i < 8; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLE[playerid][i]);
            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Arama Yap", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }
        case PAGE_LOOKUP_VEHICLES_LIST:
        {
            for(new i = 0; i < 4; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);
            //for(new a = 0; a < 12; a++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
            //for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Arama Yap", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }
        case PAGE_MENU:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            if (GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            //for(new a = 0; a < 16; a++)  PlayerTextDrawHide(playerid, MDC_LIST[playerid][a]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Liste", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }
        case PAGE_INFO:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            for(new a = 0; a < 3; a++)  PlayerTextDrawShow(playerid, MDC_LIST_INFO[playerid][a]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Arama Yap", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }

        case PAGE_MAP:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            for(new i = 0; i < 5; i++) if (i != 2) PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][i]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Adresler", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }

        case PAGE_MEMBERS_MAP:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][5], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][5], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][5]);

            for(new i = 0; i < 2; i++) PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][i]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Memurlar", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }

        case PAGE_LIC:
        {
            PlayerTextDrawShow(playerid, MDC_BACK[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][3], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][3], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][3]);

            for(new i = 0; i < 8; i++) PlayerTextDrawShow(playerid, MDC_LIC[playerid][i]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Ruhsatlar", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }

        case PAGE_CALLS:
        {
            PlayerTextDrawColor(playerid, MDC_UI[playerid][4], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][4], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][4]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Acil Durum", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
        }

        case PAGE_APB:
        {
            for(new a = 0; a < 4; a++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][a]);
            //for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][6], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][6], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][6]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ APB", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");
        }
        case PAGE_ROSTER:
        {
            PlayerTextDrawColor(playerid, MDC_UI[playerid][7], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][7], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][7]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Kadro", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);

            for(new j = 0; j < 3; j++)  PlayerTextDrawShow(playerid, MDC_TD_LEFT_PANEL[playerid][j]);
        }
        case PAGE_MEMBERS: 
        {
            PlayerTextDrawColor(playerid, MDC_UI[playerid][5], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][5], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][5]);

            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ Memurlar", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);

            for(new j = 0; j < 3; j++)  PlayerTextDrawShow(playerid, MDC_TD_LEFT_PANEL[playerid][j]);
        }
        case PAGE_CCTV:
        {
            PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "AKTIF CCTV:");
            PlayerTextDrawShow(playerid, MDC_ERROR_CALLS[playerid]);

            PlayerTextDrawColor(playerid, MDC_UI[playerid][8], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_UI[playerid][8], 0x494949FF);
            PlayerTextDrawShow(playerid, MDC_UI[playerid][8]);
            
            new string[128];
            format(string, sizeof(string), "%s MDC ~>~ CCTV", Factions[PlayerInfo[playerid][pFaction]][fName]);
            PlayerTextDrawSetString(playerid, MDC_UI[playerid][13], string);

            if (GetPVarInt(playerid, #MAX_MDC_PAGE) > 1)
                for(new b = 0; b < 3; b++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
        }
    }

    return 1;
}

MembersOnline(playerid)
{
    new count = 0;
    foreach(new i : Player)
    {
        if (IsPlayerLogged(i) == 0 || PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction])	continue;
        count++;
    }
    return count;
}

this::MDCSearchPersonInfo(playerid)
{
    if (!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

		for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
		for(new b = 0; b < 12; b++) PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

		for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
		for(new d = 0; d < 12; d++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

		MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
		return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }

    //MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
    MdcInfo[playerid][mdcMenu] = PAGE_LOOKUP_PERSON;

    Update_MDC(playerid, PAGE_LOOKUP_PERSON);
    PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

    new
        ownername[MAX_PLAYER_NAME],
        strhouse[128],
        strlic[64],
        birthdate[24],
        str[10 + 24 + 128 + 64 + 24 + 24],
        count = 0
    ;


    new skin, carlic, weplic, flylic, taxilic, arrested, id, number;
    cache_get_value_int(0, "id", id);
    cache_get_value_int(0, "skin", skin);
    cache_get_value_int(0, "number", number);
    cache_get_value_int(0, "carlic", carlic);
    cache_get_value_int(0, "weplic", weplic);
    cache_get_value_int(0, "flylic", flylic);
    cache_get_value_int(0, "taxilic", taxilic);
    cache_get_value_int(0, "arrested", arrested);
    cache_get_value(0, "name", ownername, 24);
	PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], ownername);

	if (carlic == 1)
	{
        count++;
	    format(strlic, sizeof(strlic), "Surucu Lisansi");
	}
	if (weplic == 1)
	{
        if (count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
	    format(strlic, sizeof(strlic), "%sSilah Ruhsati", strlic);
        count++;
	}
	if (flylic == 1)
	{
	    if (count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
	    format(strlic, sizeof(strlic), "%sUcus Lisansi", strlic);
        count++;
	}
	if (taxilic == 1)
	{
	    if (count > 0) format(strlic, sizeof(strlic), "%s, ", strlic);
	    format(strlic, sizeof(strlic), "%sTaksi Lisansi", strlic);
        count++;
	}
    if (!count) format(strlic, sizeof(strlic), "Bulunamadi");

	if (arrested || count > 0)
    {
        PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], skin);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][1]);

        PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][0]);
    }
    else
    {
        PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][0]);
        PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][1]);
    }

    count = 0;

    for(new i; i < MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID] || HouseInfo[i][hOwnerID] != id) continue;

        count++;
        if (count > 1) break;
        format(strhouse, sizeof(strhouse), "%s", (!HouseInfo[i][hApart])?(GetHouseZone(i)):(GetApartmentZone(HouseInfo[i][hApart])));
    }

	if (!count)
    {
        format(strhouse, sizeof(strhouse), "Bulunamadi");
        PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][10]);
    }
    else
    {
        if (count > 1) PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][10], "]_ADRESLER ICIN BURAYA TIKLAYIN.");
        else PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][10], "]_EV KONUMU ICIN TIKLAYIN;");

        PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][10]);
    }

    cache_get_value(0, "birthdate", birthdate, 24);
    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], skin);

    format(str, sizeof(str), "%s, %s~n~%i~n~%i hapis kaydi~n~%s~n~%s", ownername, birthdate, number, arrested, strlic, strhouse);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][2], TurkishCharFix(str));

    count = id;

    new tickets = CountPlayerTicketsID(count);
    if (tickets) {
        format(str, sizeof(str), "~y~%i~w~~n~Odenmemis cezalar!", tickets);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][11], str);
    } else {
        PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][11]);
    }

    SetPVarInt(playerid, #MDC_ID, count);

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `criminalrecords` WHERE `userid` = %i", count);
	mysql_tquery(dbHandle, query, "MDCPersonCriminalHistory", "i", playerid);

    return 1;
}

this::MDCPersonCriminalHistory(playerid)
{
	if (!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][8], "- SUC GECMISI TEMIZ.");
        PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][9]);
        return 1;
    }

    new
        count = 0,
        newcount = 0,
        arrest,
        arrest2,
        str[5*128]
    ;

    if (cache_num_rows() > 5) count = 5;
    else count = cache_num_rows();

	for(new i; i < count; i++)
	{
        cache_get_value_int(i, "arrest", arrest);
        if (arrest == 1)
        {
            new strtemp[124];
            cache_get_value(i, "charge", strtemp, 128);

            if (strlen(strtemp) > 36)
                format(str, sizeof(str), "%s-_%s~n~", str, TextTab(strtemp, 30, 36, 0));
            else
                format(str, sizeof(str), "%s-_%s~n~", str, strtemp);

            newcount++;
        }
	}
    
    cache_get_value_int(cache_num_rows()-1, "arrest", arrest2);

    if (arrest2 != 1) PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][9]);
    else                                                               PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][9]);

    if (count == 0) PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][8], "- SUC GECMISI TEMIZ.");
    else if (newcount == 0) PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][8], "- ARANIYOR (ayrintilar icin tiklayin ~up~).");

    else PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][8], TurkishCharFix(str));

	return 1;
}

IsPlayerWanted(playerid) 
{
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT `arrest` FROM `criminalrecords` WHERE `userid` = %i ORDER BY `id` DESC LIMIT 1", playerid);
	new Cache:cache = mysql_query(dbHandle, query);

    if (!cache_num_rows()) return 0;

	new	arrest;
    cache_get_value_int(0, "arrest", arrest);
	
    cache_delete(cache);
    cache = MYSQL_INVALID_CACHE;

    if (arrest != 1) return 1;
    else            return 0;
}

this::MDCSearchVehiclesList_GetID(playerid)
{
    if (!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

		for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
		for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

		for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
		for(new d = 0; d < 12; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

		MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
		return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }

    new id;
    cache_get_value_int(0, "id", id);

    new query[164];
	mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `owner` = %i AND `registered`=1 LIMIT 3", id);
	mysql_tquery(dbHandle, query, "MDCSearchVehiclesList", "i", playerid);

    return 1;
}


this::MDCSearchVehiclesList(playerid) ////// ÎØÈÁÊÀ
{
    
	if (!cache_num_rows())
	{
		PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

		for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
		for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

		for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
		for(new d = 0; d < 12; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

		MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
		return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
	}
 
    else if(MdcInfo[playerid][mdcListPage] == 0)
    {
        new aracid;
        cache_get_value_int(0, "id", aracid);   
        
        new query[156];
        mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `id` = %i AND `registered`=1", aracid);
        mysql_tquery(dbHandle, query, "MDCSearchVehicle", "i", playerid);
        return 1;
    }

    PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);
    new owner;
    cache_get_value_int(0, "owner", owner);

    SetPVarInt(playerid, #MDC_OWNER_ID, owner);

    new ownername[MAX_PLAYER_NAME];
    cache_get_value(0, "ownername", ownername);
    
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], ownername);

    for(new j = 0; j < 12; j++) PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][j]);
    for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);

    for(new i = 0; i < cache_num_rows(); i++)
    {
        PlayerTextDrawShow(playerid, MDC_VEH_LIST_CLICK[playerid][i]);

        cache_get_value_int(i, "id", MdcInfo[playerid][mdcList][i]);

        new model, plate[24], insurances[11], impounded[7], wanted, impound, insurance;

        cache_get_value(i, "plate", plate);
        cache_get_value_int(i, "model", model);
        cache_get_value_int(i, "wanted", wanted);
        cache_get_value_int(i, "insurances", insurance);
        cache_get_value_int(i, "impound", impound);

        new color1, color2;
        cache_get_value_int(0, "color1", color1);
        cache_get_value_int(0, "color2", color2);

        if (wanted) PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3+i*4]);
        else                                          PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][3+i*4]);

        switch(insurance)
        {
            case 0: format(insurances, sizeof(insurances), "~l~YOK");
            case 1: format(insurances, sizeof(insurances), "~g~SEVIYE 1");
            case 2: format(insurances, sizeof(insurances), "~g~SEVIYE 2");
            case 3: format(insurances, sizeof(insurances), "~g~SEVIYE 3");
        }

        switch(impound)
        {
            case 0: format(impounded, sizeof(impounded), "~l~HAYIR");
            case 1: format(impounded, sizeof(impounded), "~r~EVET");
        }

        static const str_size[] = "%s~n~%s~n~%s~n~%s~n~%s";
        new mes[sizeof(str_size) + 32 + MAX_PLAYER_NAME + 24 + 24 + 11 + 7];

        format(mes, sizeof(mes), str_size, VehicleNames[model-400], plate, ownername, insurances, impounded);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1+i*4], mes);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][1+i*4]);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][2+i*4]);

        PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0+i*4], model);
        PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0+i*4], color1, color2);
        PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][0+i*4]);
    }

    new max_page = floatround(MDC_VehicleCount(owner) / 3.0, floatround_ceil);

    if (max_page > 1)
    {
        for(new a = 0; a < 3; a++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][a]);

        new str[8];
        format(str, sizeof(str), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, max_page);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], str);
        SetPVarInt(playerid, #MAX_MDC_PAGE, max_page);
    } else {
        for(new a = 0; a < 3; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][a]);
    }

    Update_MDC(playerid, PAGE_LOOKUP_VEHICLES_LIST);
    return 1;
}

this::MDCSearchVehicle(playerid)
{
	if (!cache_num_rows())
	{
		PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

		for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
		for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

		for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
		for(new d = 0; d < 12; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

		MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
		return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
	}
    PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

    new id;
    cache_get_value_int(0, "id", id);

    SetPVarInt(playerid, #MDC_ID, id);

	new ownername[MAX_PLAYER_NAME], model, plate[24], date[24], wanted, insurance, impound, insurances[8], impounded[4], count;

	cache_get_value(0, "ownername", ownername);
    cache_get_value(0, "plate", plate);
    cache_get_value_int(0, "model", model);
    cache_get_value(0, "date", date);

    cache_get_value_int(0, "wanted", wanted);
    cache_get_value_int(0, "insurances", insurance);
    cache_get_value_int(0, "impound", impound);

    if (wanted)
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][7], "~>~ ARAC ARANMA KALDIR, DURUM: ~r~ ARANIYOR");
    else
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][7], "~>~ ARACI BILDIR, DURUM: ~g~ ARANMIYOR");

    switch(insurance)
    {
        case 0: format(insurances, sizeof(insurances), "HAYIR");
        case 1: format(insurances, sizeof(insurances), "LEVEL 1");
        case 2: format(insurances, sizeof(insurances), "LEVEL 2");
        case 3: format(insurances, sizeof(insurances), "LEVEL 3");
    }

    switch(impound)
    {
        case 0: format(impounded, sizeof(impounded), "Yok");
        case 1: format(impounded, sizeof(impounded), "Hacizli");
    }


	static const str_size[] = "%s~n~%s~n~%s~n~%s~n~%s~n~%s";
	new mes[sizeof(str_size) + 32 + MAX_PLAYER_NAME + 24 + 24 + 8 + 4];

 	format(mes, sizeof(mes), str_size, VehicleNames[model-400], plate, ownername, insurances, impounded, date);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][1], mes);

    new notes[5][128], string[640];
    format(string, sizeof(string), "NOTLAR:");

    for(new i = 0; i < 5; i++)
    {
        new notei[6];
        format(notei, sizeof(notei), "Note%i", i+1);
        cache_get_value_name(0, notei, notes[i]);

        if (!CompareStrings(notes[i], "None"))
        {
            format(string, sizeof(string), "%s~n~-_%s", TurkishCharFix(string), TextTab(notes[i], 60, 65, 0));
            count++;
        }
    }
    if (!count) format(string, sizeof(string), "NOT:~n~-_HENUZ NOT YOK.");
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][3], string);

    new color1, color2;
    cache_get_value_int(0, "color1", color1);
    cache_get_value_int(0, "color2", color2);

    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_VEHICLE[playerid][0], model);
    PlayerTextDrawSetPreviewVehCol(playerid, MDC_LOOKUP_VEHICLE[playerid][0], color1, color2);
    PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLE[playerid][0]);

    format(string, sizeof(string), "]__CEZALARA_BAK__(ODENMEYENLER:__%i)", CountVehicleIDTickets(id));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][4], string);

    SetPVarString(playerid, #MDC_VEHICLE_NUM, plate);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], plate);

    MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_VEHICLES_LIST;
    MdcInfo[playerid][mdcMenu] = PAGE_LOOKUP_VEHICLE;
    Update_MDC(playerid, PAGE_LOOKUP_VEHICLE);
	return 1;
}

this::MDC_Veh_Wanted(playerid) // ÎØÈÁÊÀ!
{
    new plates[24], query[156];
    GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

    new veh_wanted, id, model;
    cache_get_value_int(0, "wanted", veh_wanted);
    cache_get_value_int(0, "id", id);
    cache_get_value_int(0, "model", model);

    if (veh_wanted)
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `wanted` = '0' WHERE `plate` = '%e' AND `registered`=1", plates);
        mysql_tquery(dbHandle, query);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][7], "~>~ ARACI BILDIR, DURUM: ~g~ ARANMIYOR");

        SendWarningMessage(playerid, "Araç artýk aranmýyor.");
        
        for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
        {
            if (VehicleInfo[i][carID] == id) VehicleInfo[i][carWanted] = 0;
        }
    }
    else
    {
        mysql_format(dbHandle, query, sizeof(query), "UPDATE `cars` SET `wanted` = '1' WHERE `plate` = '%e' AND `registered`=1", plates);
        mysql_tquery(dbHandle, query);
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLE[playerid][7], "~>~ ARAC ARANMA KALDIR, DURUM: ~r~ ARANIYOR");

        SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[ARANIYOR] Araç: %s [%s] aranan, Memur: %s.", VehicleNames[model-400], plates, GetNameEx(playerid));
        SendWarningMessage(playerid, "Araç baþarýlý bir þekilde arananlar listesine alýndý.");

        
        for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
        {
            if (VehicleInfo[i][carID] == id) VehicleInfo[i][carWanted] = 1;
        }
    }

    return 1;
}


this::MDC_NEW_NOTE(playerid)
{
    new
        plates[24];

    GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

    SetPVarInt(playerid, #MDC_FREE_NOTE, -1);

    new notesadd[5][128];

    for(new i = 0; i < 5; i++)
    {
        new notei[6];
        format(notei, sizeof(notei), "Note%i", i+1);
        cache_get_value_name(0, notei, notesadd[i]);

        if (CompareStrings(notesadd[i], "None"))
        {
            SetPVarInt(playerid, #MDC_FREE_NOTE, i+1);
            break;
        }
    }

    if (GetPVarInt(playerid, #MDC_FREE_NOTE) == -1)
        Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{8D8DFF}MDC  - NOT EKLE", "{B4B5B7}ARAÇ KAYDI EKLEME\n\nDÝKKAT!\nTüm notlar alýnýr!", "X", "");
    else
        Dialog_Show(playerid, MDC_Add_Note, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - ARAÇ KAYDI EKLE", "{B4B5B7}ARAÇ KAYDI EKLEME\n\nNot Giriniz:", "Ekle", "Geri Dön");

    return 1;
}

this::MDC_DELETE_NOTE(playerid)
{
    new
        eplates[24];

    GetPVarString(playerid, #MDC_VEHICLE_NUM, eplates, 24);

    SetPVarInt(playerid, #MDC_FREE_NOTE, -1);

    new notes[5][128], string[35*5+10];
    format(string, sizeof(string), "#\tRecord");

    for(new i = 0; i < 5; i++)
    {
        new notei[6];
        format(notei, sizeof(notei), "Note%i", i+1);
        cache_get_value_name(0, notei, notes[i]);

        if (CompareStrings(notes[i], "None"))
            format(notes[i], 128, "Empty");
        else
            SetPVarInt(playerid, #MDC_FREE_NOTE, 1);

        format(string, sizeof(string), "%s\n%i.\t%0.30s", string, i+1, notes[i]);
    }

    if (GetPVarInt(playerid, #MDC_FREE_NOTE) == -1) Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{8D8DFF}MDC  -  Araç kaydýný sil", "{B4B5B7}ARAÇ HAKKINDA YAPILAN ÝÞLEMLER GERÝ ALINAMAZ\n\nDÝKKAT!\nBu araca bir not eklenmemiþ.", "X", "");
    else Dialog_Show(playerid, MDC_Del_Note, DIALOG_STYLE_TABLIST_HEADERS, "{8D8DFF}MDC  - Araç kaydýný sil", string, "Sil", "Ýptal");

    return 1;
}

/*SHOW_MDC_LIST(playerid)
{
    for(new i = 0; i < 16; i++)
        PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], MdcInfo[playerid][mdcList][i]);

    return 1;
}*/

this::MDC_ShowCCTVMenu(playerid, back)
{
	new
		string[256]
	;

    PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "AKTIF KAMERALARI LISTELE:");

    for(new j = 0; j < 16; j++)
    {
        PlayerTextDrawHide(playerid, MDC_LIST[playerid][j]);
        MdcInfo[playerid][mdcList][j] = -1;
    }

    if (cache_num_rows())
    {
		if (!back)
		{
            for(new i = 0; i < cache_num_rows(); i++)
            {
                new 
                    info[32],
                    id,
                    breakinfo
                ;

                cache_get_value(i, "info", info);
                cache_get_value_int(i, "break", breakinfo);
                cache_get_value_int(i, "id", id);
                cache_get_value_int(i, "id", MdcInfo[playerid][mdcList][i]);

                if (breakinfo) format(string, sizeof(string), "~r~CEVRIMDISI");
                else                                         format(string, sizeof(string), "~g~CEVRIMICI_");

                new index[5];

                if (id > 99) format(index, sizeof(index), "0%i", id);
                else if (id > 9) format(index, sizeof(index), "00%i", id);
                else format(index, sizeof(index), "000%i", id);

                format(string, sizeof(string), "__DURUM:_%s~l~_____________ID:_%s______________%s", string, index, info);

                PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], string);

                PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], 0x494949FF);
                PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], 0xa7a7a7FF);

                PlayerTextDrawShow(playerid, MDC_LIST[playerid][i]);
            }
        }
		else
		{
            for(new i = cache_num_rows()-1; i >= 0; i--)
            {
                new 
                    info[32],
                    breakinfo
                ;

                cache_get_value(i, "info", info);
                cache_get_value_int(i, "break", breakinfo);
                cache_get_value_int(i, "id", MdcInfo[playerid][mdcList][i]);

                if (breakinfo) format(string, sizeof(string), "~r~CEVRIMDISI");
                else                                         format(string, sizeof(string), "~g~CEVRIMICI_");

                new index[5];
                if (i > 99) format(index, sizeof(index), "0%i", i);
                else if (i > 9) format(index, sizeof(index), "00%i", i);
                else format(index, sizeof(index), "000%i", i);
                    
                format(string, sizeof(string), "__DURUM:_%s~l~_____________ID:_%s______________%s", string, index, info);

                PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], string);
                PlayerTextDrawShow(playerid, MDC_LIST[playerid][i]);
            }
		}
    }
    else return PlayerTextDrawSetString(playerid, MDC_ERROR_CALLS[playerid], "]__HATA: BIRSEY BULUNAMADI!");
    

    Update_MDC(playerid, PAGE_CCTV);

    new strpage[7];
    format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if (GetPVarInt(playerid, #MAX_MDC_PAGE) == 1) for(new k = 0; k < 3; k++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    else for(new k = 0; k < 3; k++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);

	return 1;
}

MDC_ShowRosterMenu(playerid)
{
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][0], "AKTIF BIRIMLER LISTESI:");
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][1], "CALLSIGN DEGISTIR");

    new string[128], count, pageCount, f = GetPatrolID(playerid);

    for(new j = 0; j < 18; j++) PlayerTextDrawHide(playerid, MDC_TD_MENU[playerid][j]);
    for(new j = 0; j < 18; j++) MdcInfo[playerid][mdcList][j] = 0;

    for(new i = 0; i != MAX_PATROL; i++)
    {
        if (!PatrolInfo[f][i][patrulExists])                    continue;
        if (pageCount++ < 18*(MdcInfo[playerid][mdcListPage]))  continue;

        format(string, sizeof(string), "__%s:__", PatrolInfo[f][i][patrulName]);

        if (IsPlayerLogged(PatrolInfo[f][i][patrulOfficer][0]))
        {
            format(string, sizeof(string), "%s%s", string, GetOfficerName(PatrolInfo[f][i][patrulOfficer][0]));
        }
        if (IsPlayerLogged(PatrolInfo[f][i][patrulOfficer][1]))
        {
            if (IsPlayerLogged(PatrolInfo[f][i][patrulOfficer][1])) {
                format(string, sizeof(string), "%s__,__%s", string, GetOfficerName(PatrolInfo[f][i][patrulOfficer][1]));
            } else {
                format(string, sizeof(string), "%s%s", string, GetOfficerName(PatrolInfo[f][i][patrulOfficer][1]));
            }
        }
                
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][count], string);
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][count]);
                
        MdcInfo[playerid][mdcList][count] = i;

        count++;
        if (count == 18*(MdcInfo[playerid][mdcListPage]+1)) break;
    }

    if (!count)
    {
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][0], "_SU ANDA AKTIF DEVRIYE BIRIMI YOK..");
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][0]);
    }

    if (pTemp[playerid][pPatrol])
    {
        new callsignstr[32];
        format(callsignstr, sizeof(callsignstr), "_%s", PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName]);
        PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][2], callsignstr);
    }
    else PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][2], "BIRIMINIZ BULUNMUYOR");

    new strpage[7];
    format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if (GetPVarInt(playerid, #MAX_MDC_PAGE) < 2) {
        for(new k = 0; k < 3; k++)  {
            PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
        }
    } else {
        for(new k = 0; k < 3; k++)  {
            PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
        }
    }
    return 1;
}

MDC_ShowMembersMenu(playerid)
{
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][0], "TUM UYELERIN LISTESI:");
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][1], "DURUM DEGISTIR");

    new string[128], count; //, f = GetPatrolID(playerid);

    for(new j = 0; j < 18; j++) PlayerTextDrawHide(playerid, MDC_TD_MENU[playerid][j]);
    for(new j = 0; j < 18; j++) MdcInfo[playerid][mdcList][j] = 0;

    new status[22], listStatus[3][20], mainstatus[128], pageCount;
    switch(pTemp[playerid][tempStatus])
    {
        case 0: format(status, sizeof(status), "__10-7 ~r~(GOREV DISI)");
        case 1: format(status, sizeof(status), "__10-8 ~g~(GOREVDE)");
        case 2: format(status, sizeof(status), "__CODE 7 ~y~(MOLADA)");
    }
    format(mainstatus, sizeof(mainstatus), "%s~n~~n~~r~KODLAR:~l~~n~~>~ 10-8 (GOREVDE)~n~~>~ 10-7 (GOREV DISI)~n~~>~ CODE 7 (MOLADA)", status);
    PlayerTextDrawSetString(playerid, MDC_TD_LEFT_PANEL[playerid][2], mainstatus);

    format(listStatus[0], 20, "~r~GOREV DISI");
    format(listStatus[1], 20, "~g~GOREVDE");
    format(listStatus[2], 20, "~y~MOLADA");

    foreach(new i : Player) {
        if (IsPlayerLogged(i) == 0 || PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction])	continue;
        if (pageCount++ < 18*(MdcInfo[playerid][mdcListPage]))  continue;
                
        format(string, sizeof(string), "%i_._~l~[%s~l~]_%s_~b~%s", count+1, listStatus[pTemp[i][tempStatus]], GetRankName(i), GetOfficerName(i));
                
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][count], TurkishCharFix(string));
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][count]);
                
        MdcInfo[playerid][mdcList][count] = i;
        
        count++;
        if (count == 18*(MdcInfo[playerid][mdcListPage]+1)) break;
    }

    if (!count)
    {
        PlayerTextDrawSetString(playerid, MDC_TD_MENU[playerid][0], "_HATA OLUSTU..");
        PlayerTextDrawShow(playerid, MDC_TD_MENU[playerid][0]);
    }

    new strpage[7];
    format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if (GetPVarInt(playerid, #MAX_MDC_PAGE) < 2) {
        for(new k = 0; k < 3; k++)  {
            PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
        }
    } else {
        for(new k = 0; k < 3; k++)  {
            PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
        }
    }
    return 1;
}            

this::MDC_ShowMenu(playerid, back)
{
	new
		string[256]
	;

    for(new j = 0; j < 16; j++)
    {
        PlayerTextDrawHide(playerid, MDC_LIST[playerid][j]);
        MdcInfo[playerid][mdcList][j] = -1;
    }

    if (cache_num_rows())
    {
		if (!back)
		{
            for(new i = 0; i < cache_num_rows(); i++)
            {
                new
                    date[24],
                    paid,
                    arrest,
                    reason[41]
                ;
                if (GetPVarInt(playerid, #MDC_FINE))
                    cache_get_value(i, "reason", reason);
                else
                    cache_get_value(i, "charge", reason);

                cache_get_value(i, "date", date);
                cache_get_value_int(i, "paid", paid);
                cache_get_value_int(i, "arrest", arrest);

                cache_get_value_int(i, "id", MdcInfo[playerid][mdcList][i]);

                if (strlen(reason) > 40)
                    format(string, sizeof(string), "%s_-_%.40s..", date, reason);
                else
                    format(string, sizeof(string), "%s_-_%.40s", date, reason);

                if (GetPVarInt(playerid, #MDC_FINE))
                {
                    if (!paid)
                    {
                        PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], -1); // Íå îïëà÷åííûå
                        PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], COLOR_LIGHTRED);
                    }
                    else
                    {
                        PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], 255); // Îïëà÷åííûå
                        PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], -1);
                    }
                }
                else
                {
                    if (arrest)
                    {
                        PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], -1); // Àðåñòîâàí
                        PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], COLOR_LIGHTRED);

                        format(string, sizeof(string), "%s_-_El Konulmus.", date);
                    }
                    else
                    {
                        PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], 255); // Îáâèíåíèå
                        PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], -1);
                    }
                }

                PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], string);
                PlayerTextDrawShow(playerid, MDC_LIST[playerid][i]);

            }
        }
		else
		{
            for(new i = cache_num_rows()-1; i >= 0; i--)
            {
            new
                date[24],
                paid,
                arrest,
                reason[41]
            ;

            if (GetPVarInt(playerid, #MDC_FINE))
                cache_get_value(i, "reason", reason);
            else
                cache_get_value(i, "charge", reason);

            cache_get_value(i, "date", date);
            cache_get_value_int(i, "paid", paid);
            cache_get_value_int(i, "arrest", arrest);

            cache_get_value_int(i, "id", MdcInfo[playerid][mdcList][cache_num_rows()-1-i]);

            if (strlen(reason) > 40)
                format(string, sizeof(string), "%s_-_%.40s..", date, reason);
            else
                format(string, sizeof(string), "%s_-_%.40s", date, reason);

            if (GetPVarInt(playerid, #MDC_FINE))
            {
                if (!paid)
                {
                    PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], -1); // Íå îïëà÷åííûå
                    PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], COLOR_LIGHTRED);
                    }
                else
                {
                    PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], 255); // Îïëà÷åííûå
                    PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], -1);
                }
            }
            else
            {
                if (arrest)
                {
                    PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], -1); // Àðåñòîâàí
                    PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], COLOR_LIGHTRED);

                    format(string, sizeof(string), "%s_-_El Konulmus", date);
                }
                else
                {
                    PlayerTextDrawColor(playerid, MDC_LIST[playerid][i], 255); // Îáâèíåíèå
                    PlayerTextDrawBoxColor(playerid, MDC_LIST[playerid][i], -1);
                }
            }

            PlayerTextDrawSetString(playerid, MDC_LIST[playerid][i], string);
            PlayerTextDrawShow(playerid, MDC_LIST[playerid][i]);
            }
		}
    }
    // DeletePVar(playerid, #MDC_FINE);
    else return SendWarningMessage(playerid, "Boþ!");

    if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
    {
        //new Float:countticket = MDC_CountPlayerTickets(GetPVarInt(playerid, #MDC_ID));
        //countticket = countticket/16;

        MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
        //SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countticket, floatround_ceil));
    }
    else if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_VEHICLE)
    {
        //new Float:countticket = MDC_CountVehicleTickets(GetPVarInt(playerid, #MDC_ID));
        //countticket = countticket/16;

        MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_VEHICLE;
        //SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countticket, floatround_ceil));
    }

    Update_MDC(playerid, PAGE_MENU);

    new strpage[7];
    format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);

    if (GetPVarInt(playerid, #MAX_MDC_PAGE) == 1) for(new k = 0; k < 3; k++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);
    else for(new k = 0; k < 3; k++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][k]);

	return 1;
}

this::MDC_ShowInfo(playerid)
{
    if (!cache_num_rows())
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "_________________");

		for(new a = 0; a < 2; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][a]);
		for(new b = 0; b < 12; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][b]);

		for(new c = 0; c < 3; c++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][c]);
        for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);
		for(new d = 0; d < 12; d++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][d]);

		MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
		return PlayerTextDrawShow(playerid, MDC_LOOKUP_ERROR[playerid]);
    }

    new
        reason[128],
		mes[256],
        date[24],
        status[20],
        vehiclemodel,
        id,
        paid,
        arrest,
        faction,
        amount,

        ownername[MAX_PLAYER_NAME],
        officername[MAX_PLAYER_NAME]
	;

    cache_get_value_int(0, "vehiclemodel", vehiclemodel);

    if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
	    cache_get_value(0, "ownername", ownername, 24);
    else
        format(ownername, sizeof(ownername), "%s", VehicleNames[vehiclemodel-400]);

    cache_get_value(0, "officer", officername);
    cache_get_value(0, "date", date);
    cache_get_value_int(0, "paid", paid);
    cache_get_value_int(0, "arrest", arrest);
    cache_get_value_int(0, "faction", faction);
    cache_get_value_int(0, "amount", amount);
    cache_get_value_int(0, "id", id);

    if (GetPVarInt(playerid, #MDC_FINE))
    {
        cache_get_value(0, "reason", reason);

        if (!paid)
            format(status, sizeof(status), "~r~Odenmemis");
        else
            format(status, sizeof(status), "~g~Odenmis");

        format(mes, sizeof(mes), "ID:~n~Isim:~n~Memur:~n~Ucret:~n~Tarih:~n~Durum:~n~~n~Aciklama:");
        PlayerTextDrawSetString(playerid, MDC_LIST_INFO[playerid][0], mes);

        format(mes, sizeof(mes), "#%i~n~%s~n~%s [%s]~n~$%i~n~%s~n~%s",
            1012441+id,
            ownername,
            officername,
            GetInitials(Factions[faction][fName]),
            amount,
            date,
            status
        );
        PlayerTextDrawSetString(playerid, MDC_LIST_INFO[playerid][1], mes);
    }
    else
    {
        cache_get_value(0, "charge", reason);

        if (!arrest)
            format(status, sizeof(status), "Suclama");
        else
            format(status, sizeof(status), "~r~Tutuklandi");

        format(mes, sizeof(mes), "ID:~n~Isim:~n~Memur:~n~_~n~Tarih:~n~Tip:~n~~n~Suclar:");
        PlayerTextDrawSetString(playerid, MDC_LIST_INFO[playerid][0], mes);

        format(mes, sizeof(mes), "#%i~n~%s~n~%s [%s]~n~_~n~%s~n~%s",
            912441+id,
            ownername,
            officername,
            GetInitials(Factions[faction][fName]),
            //cache_get_value_int(0, "amount"),
            date,
            status
        );
        PlayerTextDrawSetString(playerid, MDC_LIST_INFO[playerid][1], TurkishCharFix(mes));
    }


    format(reason, sizeof(reason), "- %s", TextTab(reason, 55, 60, 0));
    PlayerTextDrawSetString(playerid, MDC_LIST_INFO[playerid][2], reason);

    MdcInfo[playerid][mdcBack] = PAGE_MENU;
    Update_MDC(playerid, PAGE_INFO);

	return 1;
}

CountPlayerRecords(id)
{
	new
		query[188]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `criminalrecords` WHERE `userid` = %i", PlayerInfo[id][pID]);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
	
    cache_get_value_int(0, "total", count);
	cache_delete(cache);
    cache = MYSQL_INVALID_CACHE;
	return count;
}

MDC_VehicleCount(ownerid)
{
	new
		query[256]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `cars` WHERE `owner` = %i AND `registered`=1", PlayerInfo[ownerid][pID]);
	new Cache:cache = mysql_query(dbHandle, query),
		count;
	
    cache_get_value_int(0, "total", count);
	cache_delete(cache);
    cache = MYSQL_INVALID_CACHE;
	return count;
}

this::MDC_MAP(playerid)
{
    if (!cache_num_rows())
        return 1;
    new
        Float:map_kY = -0.04795376,
        Float:map_kX = 0.0469,

        Float:map_sX = 333.999420,
        Float:map_sY = 295.181152,

        Float:corX, Float:corY,

        count = 0,

        strhouse[80]
    ;

    //for(new j = 1; j < 6; j++) PlayerTextDrawHide(playerid, MDC_OTHER_ADDRESS[playerid][j]);

    new id;
    cache_get_value_int(0, "id", id);

    for(new i; i < MAX_HOUSES; i++)
	{
	    if (!HouseInfo[i][hID] || HouseInfo[i][hOwnerID] != id) continue;

        if (count == 0)
        {
            format(strhouse, sizeof(strhouse), "%s~n~San Andreas", (!HouseInfo[i][hApart])?(GetHouseZone(i, 1)):(GetApartmentZone(HouseInfo[i][hApart], 1)));
            PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][4], strhouse);

            if (HouseInfo[i][hPosX] > 0)
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit2");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit4");
                map_kX = 0.0469;
                map_sX = 333.999420;

                corX = HouseInfo[i][hPosX] * map_kX + map_sX;
                corY = HouseInfo[i][hPosY] * map_kY + map_sY;
            }
            else
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit1");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit3");
                map_kX = -0.0469;
                map_sX = 480.066314;

                corX = map_sX - HouseInfo[i][hPosX] * map_kX;
                corY = HouseInfo[i][hPosY] * map_kY + map_sY;
            }

            MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, corX, corY, "hud:radar_propertyG");
            PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 5.000000, 6.000000);
            PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
            PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][2]);
        }
        else
        {
            format(strhouse, sizeof(strhouse), "- %.35s", (!HouseInfo[i][hApart])?(GetHouseZone(i, 2)):(GetApartmentZone(HouseInfo[i][hApart], 2)));
            PlayerTextDrawSetString(playerid, MDC_OTHER_ADDRESS[playerid][count], strhouse);
            PlayerTextDrawShow(playerid, MDC_OTHER_ADDRESS[playerid][count]);
        }

        MdcInfo[playerid][mdcList][count] = i;
        count++;
	}
    if (count > 1) PlayerTextDrawShow(playerid, MDC_OTHER_ADDRESS[playerid][0]);

    MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
    Update_MDC(playerid, PAGE_MAP);
    return 1;
}

MEMBERS_MAP(playerid, userid)
{
    if (!IsPlayerLogged(userid))    return MDC_PAGE(playerid, PAGE_MAIN);

    new
        Float:map_kY = -0.04795376,
        Float:map_kX = 0.0469,

        Float:map_sX = 333.999420,
        Float:map_sY = 295.181152,

        Float:corX, Float:corY,

        Float:posX, 
        Float:posY,
        Float:posZ,

        string[64]
    ;

    GetPlayerPos(userid, posX, posY, posZ);

    if (posX > 0)
    {
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit2");
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit4");
        map_kX = 0.0469;
        map_sX = 333.999420;

        corX = posX * map_kX + map_sX;
        corY = posY * map_kY + map_sY;
    }
    else
    {
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit1");
        PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit3");
        map_kX = -0.0469;
        map_sX = 480.066314;

        corX = map_sX - posX * map_kX;
        corY = posY * map_kY + map_sY;
    }

    MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, corX, corY, "hud:radar_gangN");
    PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 7.000000, 8.000000);
    PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
    PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][2]);

    PlayerTextDrawSetPreviewModel(playerid, MDC_LOOKUP_AVATAR[playerid][1], GetPlayerSkin(userid));
    PlayerTextDrawShow(playerid, MDC_LOOKUP_AVATAR[playerid][1]);

    PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][0]);

    format(string, sizeof(string), "%s__~b~__%s", GetOfficerName(userid), GetRankName(userid));
    //format(string, sizeof(string), "%s___]_%i", GetOfficerName(userid), PlayerInfo[userid][pRank]);
    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][3], TurkishCharFix(string));
    //PlayerTextDrawUseBox(playerid, MDC_LOOKUP_PERSON[playerid][3], 0);
	//PlayerTextDrawSetSelectable(playerid, MDC_LOOKUP_PERSON[playerid][3], false);
    PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][3]);

    PlayerTextDrawSetString(playerid, MDC_LOOKUP_PERSON[playerid][4], "~>~ BODYCAM KONTROL G-0"); 
    PlayerTextDrawShow(playerid, MDC_LOOKUP_PERSON[playerid][4]);

    MdcInfo[playerid][mdcBack] = PAGE_MEMBERS;
    Update_MDC(playerid, PAGE_MEMBERS_MAP);

    SetPVarInt(playerid, #BODYCAM, userid);
    return 1;
}

this::MDC_LICENSE(playerid)
{
    if (!cache_num_rows())
        return 1;

    new
        string[128]
    ;

    new carlic, weplic, flylic, taxilic, warns;
    cache_get_value_int(0, "carlic", carlic);
    cache_get_value_int(0, "weplic", weplic);
    cache_get_value_int(0, "flylic", flylic);
    cache_get_value_int(0, "taxilic", taxilic);
    cache_get_value_int(0, "drivewarns", warns);

    switch(carlic)
	{
        case 0: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][4], "~r~HAYIR~n~-");
	    case 1:
        {
            format(string, sizeof(string), "~g~AKTIF~n~~r~%i", warns);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][4], string);
        }
	}

	switch(weplic)
	{
        case 0: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][11], "~r~-~n~-~n~-~n~-");
	    case 1:
        {
            new name[MAX_PLAYER_NAME+1], officer[MAX_PLAYER_NAME+1], data[24], price, drwarns;

            cache_get_value(0, "name", name);
            strreplace(name, '_', ' ');
            cache_get_value(0, "wep_officer", officer);
            cache_get_value(0, "wep_data", data);
            cache_get_value_int(0, "wep_price", price);
            cache_get_value_int(0, "wepwarns", drwarns);

            format(string, sizeof(string), "%i~n~%s~n~%s~n~~g~$%i", drwarns, name, data, price);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][11], string);
        }
	}
	switch(flylic)
	{
	    case 0: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][18], "~r~HAYIR");
	    case 1: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][18], "~g~AKTIF");
        case 2: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][18], "~l~KARALISTE");
	}
	switch(taxilic)
	{
	    case 0: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][25], "~r~HAYIR");
	    case 1: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][25], "~g~AKTIF");
        case 2: PlayerTextDrawSetString(playerid, MDC_LIC[playerid][25], "~l~KARALISTE");
	}

    MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
    Update_MDC(playerid, PAGE_LIC);

    return 1;
}

this::MDC_LIC_LOADING(playerid, response)
{
    if (!response)    return 1;

    new query[255];
    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i LIMIT 1", GetPVarInt(playerid, #MDC_ID));
    mysql_tquery(dbHandle, query, "MDC_LIC_DO", "ii", playerid, GetPVarInt(playerid, #MDC_LIC));

    DeletePVar(playerid, #MDC_LIC);
    return 1;
}

this::MDC_LIC_DO(playerid, func)
{
    if (!cache_num_rows())
        return 1;

    new
        userid,
        playeronline,
        id,
        carlic,
        weplic,
        flylic,
        taxilic,
        drivewarns,
        name[MAX_PLAYER_NAME+1]
    ;

    if ((userid = GetIDByID(GetPVarInt(playerid, #MDC_ID))) != INVALID_PLAYER_ID)
        playeronline = 1;
    else playeronline = 0;

    cache_get_value(0, "name", name);
    cache_get_value_int(0, "id", id);
    cache_get_value_int(0, "carlic", carlic);
    cache_get_value_int(0, "weplic", weplic);
    cache_get_value_int(0, "flylic", flylic);
    cache_get_value_int(0, "taxilic", taxilic);
    cache_get_value_int(0, "drivewarns", drivewarns);

    switch(func)
    {
        case 0: //ÈÇÚßÒÜ ÏÐÀÂÀ
        {
            if (!carlic)   return SendErrorMessage(playerid, " %s adlý kiþinin ehliyeti bulunmuyor.", name);

            if (playeronline)
            {
                SendSpecialMessage(userid, "%s %s adlý kiþi ehliyetini iptal etti.", GetRankName(playerid), GetNameEx(playerid));
                PlayerInfo[userid][pCarLic] = 0;
                PlayerInfo[userid][pDriveWarns] = 0;
            }

            new query[156];
            mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `carlic`='0',`drivewarns`='0' WHERE `id` = %i", GetPVarInt(playerid, #MDC_ID));
            mysql_tquery(dbHandle, query);

            SendSpecialMessage(playerid, "%s adlý kiþinin ehliyetini iptal ettiniz.", name);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][4], "~r~HAYIR~n~-");

            return 1;
        }

        case 1: //ÈÇÚßÒÜ ÎÐÓÆ
        {
            if (!weplic)   return SendErrorMessage(playerid, " %s adlý kiþinin silah ruhsatý bulunmuyor.", name);

            if (playeronline)
            {
                SendSpecialMessage(userid, "%s %s adlý kiþi silah ruhsatýný iptal etti.", GetRankName(playerid), GetNameEx(playerid));
                PlayerInfo[userid][pWepLic] = 0;
                PlayerInfo[userid][pWepWarns] = 0;
                PlayerInfo[userid][pWepCount] = 0;
            }
            new query[156];
            mysql_format(dbHandle, query, sizeof(query), "UPDATE `users` SET `weplic`='0',`wepwarns`='0',`wep_officer`='-',`wep_data`='-',`wep_price`='0',`wep_count`='0' WHERE `id` = %i", GetPVarInt(playerid, #MDC_ID));
            mysql_tquery(dbHandle, query);

            SendSpecialMessage(playerid, "%s adlý kiþinin silah ruhsatýný iptal ettiniz.", name);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][11], "~r~-~n~-~n~-~n~-");

            return 1;
        }

        case 2: //ÈÇÚßÒÜ ÏÎË¨ÒÛ
        {
            if (!flylic)       return SendErrorMessage(playerid, " %s adlý kiþinin pilot lisansý bulunmuyor.", name);
            if (flylic == 2)   return SendErrorMessage(playerid, "Pilot lisansý iptal edilemiyor çünkü %s adlý kiþi karalistede.", name);

            if (playeronline)
            {
                SendSpecialMessage(userid, "%s %s pilot lisansýnýzý geri aldýnýz.", GetRankName(playerid), GetNameEx(playerid));
                PlayerInfo[userid][pFlyLic] = 0;
            }

            SQL_SetInteger("users", "flylic", 0, id);

            SendSpecialMessage(playerid, "%s adlý kiþinin pilot lisansýný iptal ettiniz.", name);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][18], "~r~HAYIR");

            return 1;
        }

        case 3: //ÈÇÚßÒÜ ÒÀÊÑÈ
        {
            if (!taxilic)       return SendErrorMessage(playerid, "%s adlý kiþinin taksi sürücü belgesi bulunmuyor.", name);
            if (taxilic == 2)   return SendErrorMessage(playerid, "Taksi þoförünün ehliyeti iptal edilemiyor çünkü %s adlý kiþi karalistede.", name);

            if (playeronline)
            {
                SendSpecialMessage(userid, "%s %s adlý kiþi taksi sürücü belgenizi geri verdi.", GetRankName(playerid), GetNameEx(playerid));
                PlayerInfo[userid][pTaxiLic] = 0;
            }

            SQL_SetInteger("users", "taxilic", 0, id);

            SendSpecialMessage(playerid,"Taksi sürücü belgenizi geri aldýnýz %s.", name);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][25], "~r~HAYIR");

            return 1;
        }

        case 4: //ÏÐÅÄÓÏÐÅÆÄÅÍÈÅ ÏÐÀÂÀ
        {
            if (!carlic)   return SendErrorMessage(playerid, "%s adlý kiþinin sürücü belgesi bulunmuyor. ", name);

            SendSpecialMessage(playerid, "%s adlý kiþiye ehliyet uyarý puaný verdiniz.", name);

            new mes[128];
            format(mes, sizeof(mes), "%s adlý kiþinin ehliyetine uyarý puaný ekler.", name);
            pc_cmd_me(playerid, mes);

            if (drivewarns + 1 == 3)
            {
                SendWarningMessage(playerid, "%s adlý kiþinin uyarý puaný tamamlandýðý için ehliyeti iptal edildi. ", name);

                SQL_SetInteger("users", "drivewarns", 0, id);
		        SQL_SetInteger("users", "carlic", 0, id);

                if (playeronline)
                {
                    SendSpecialMessage(userid, "%s %s adlý kiþi ehliyetinize uyarý verdi.", GetRankName(playerid), GetNameEx(playerid));
                    PlayerInfo[userid][pDriveWarns] = 0;
		            PlayerInfo[userid][pCarLic] = 0;
                    SendWarningMessage(playerid, "Ehliyetinizde 3 uyarý puaný olduðu için otomatik olarak iptal edildi. ");
                }
                PlayerTextDrawSetString(playerid, MDC_LIC[playerid][4], "~r~HAYIR~n~-");

                return 1;
            }
            else
            {
                if (playeronline)
                {
                    PlayerInfo[userid][pDriveWarns]++;
                }

                new string[32];
                format(string, sizeof(string), "~g~AKTIF~n~~r~%i", drivewarns+1);
                PlayerTextDrawSetString(playerid, MDC_LIC[playerid][4], string);

                SQL_SetInteger("users", "drivewarns", drivewarns+1, id);
                return 1;
            }
        }

        case 5: //ÏÐÅÄÓÏÐÅÆÄÅÍÈÅ ÎÐÓÆ
        {
            if (!weplic)   return SendErrorMessage(playerid, "%s adlý kiþinin silah ruhsatý bulunmuyor.", name);

            if (playeronline)
            {
                SendSpecialMessage(userid, "%s %s adlý kiþi silah ruhsatýnýza uyarý verdi.", GetRankName(playerid), GetNameEx(playerid));
                PlayerInfo[userid][pWepWarns]++;
            }

            SendSpecialMessage(playerid, "%s adlý kiþinin silah ruhsatýna uyarý verdiniz.", name);

            new officer[MAX_PLAYER_NAME+1], data[24], price, wpwarns, warns;

            strreplace(name, '_', ' ');
            cache_get_value(0, "wep_officer", officer);
            cache_get_value(0, "wep_data", data);
            cache_get_value_int(0, "wep_price", price);
            cache_get_value_int(0, "wepwarns", wpwarns);
            warns = wpwarns + 1;

            new string[128];
            format(string, sizeof(string), "%i~n~%s~n~%s~n~~g~$%i", warns, name, data, price);
            PlayerTextDrawSetString(playerid, MDC_LIC[playerid][11], string);

            SQL_SetInteger("users", "wepwarns", wpwarns+1, id);
            return 1;
        }

        case 6: //×Ñ ÏÎË¨ÒÛ
        {
            if (flylic == 2) //  return SendErrorMessage(playerid, "%s óæå â ÷åðíîì ñïèñêå âëàäåëüöåâ ëèöåíçèè ïèëîòà.", name);
            {
                if (playeronline)
                {
                    SendSpecialMessage(userid, "%s %s adlý kiþi pilot lisansýnýzý karalisteden kaldýrdý.", GetRankName(playerid), GetNameEx(playerid));
                    PlayerInfo[userid][pFlyLic] = 0;
                }

                SQL_SetInteger("users", "flylic", 0, id);

                SendSpecialMessage(playerid, "%s adlý kiþinin blacklistini kaldýrdýnýz. ", name);
                PlayerTextDrawSetString(playerid, MDC_LIC[playerid][18], "~r~HAYIR");
            }
            else
            {
                if (playeronline)
                {
                    SendSpecialMessage(userid, "%s %s adlý kiþi pilot lisansýnýzý karalisteye ekledi.", GetRankName(playerid), GetNameEx(playerid));
                    PlayerInfo[userid][pFlyLic] = 2;
                }

                SQL_SetInteger("users", "flylic", 2, id);

                SendSpecialMessage(playerid, "%s adlý kiþinin pilot lisansýný karalisteye eklediniz.", name);
                PlayerTextDrawSetString(playerid, MDC_LIC[playerid][18], "~l~Karaliste");
            }

            return 1;
        }

        case 7: //×Ñ ÒÀÊÑÈ
        {
            if (taxilic == 2)//   return SendErrorMessage(playerid, "%s óæå â ÷åðíîì ñïèñêå âëàäåëüöåâ ëèöåíçèè òàêñèñòà.", name);
            {
                if (playeronline)
                {
                    SendSpecialMessage(userid, "%s %s adlý kiþi taksi sürücü lisansýnýzý karalisteden kaldýrdý", GetRankName(playerid), GetNameEx(playerid));
                    PlayerInfo[userid][pTaxiLic] = 0;
                }

                SQL_SetInteger("users", "taxilic", 0, id);

                SendSpecialMessage(playerid, "%s adlý kiþinin taksi sürücü lisansýný karalisteden kaldýrdýnýz.", name);
                PlayerTextDrawSetString(playerid, MDC_LIC[playerid][25], "~r~HAYIR");
            }
            else
            {
                if (playeronline)
                {
                    SendSpecialMessage(userid, "%s %s adlý kiþi taksi sürücü lisansýnýzý karalisteye ekledi", GetRankName(playerid), GetNameEx(playerid));
                    PlayerInfo[userid][pTaxiLic] = 2;
                }

                SQL_SetInteger("users", "taxilic", 2, id);

                SendSpecialMessage(playerid, "%s adlý kiþinin taksi sürücü lisansýný karalisteye eklediniz", name);
                PlayerTextDrawSetString(playerid, MDC_LIC[playerid][25], "~l~Karaliste");
            }

            return 1;
        }
    }
    return 1;
}

CheckTextDrawString(string[])
{
    if (strfind(string, "~", true) != -1)  return 1;

    return 0;
}

this::MDC_DELETE_APB(playerid, response)
{
    if (!response)    return 1;

    new number = GetPVarInt(playerid, #MDC_ID);

    if (!ApbInfo[number][apbOn])    return SendErrorMessage(playerid, "APB notu bulunamadý.");

    SendSyntaxMessage(playerid, "%i numaralý APB notunu temizlediniz.", number);
    SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "* HQ: %s %s %i numaralý APB notunu temizledi.", GetRankName(playerid), GetNameEx(playerid), number);

    new query[256];
    mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `apbs` WHERE `id` = %i", ApbInfo[number][apbID]);
    mysql_tquery(dbHandle, query);

    ApbInfo[number][apbOn] =
    ApbInfo[number][apbID] = 0;
    Update_MDC(playerid, PAGE_APB);
	MDC_PAGE(playerid, PAGE_APB);

    return 1;

}

MDC_CountCCTVS()
{
	new 
		query[64]
	;

 	mysql_format(dbHandle, query, sizeof(query), "SELECT COUNT(id) AS total FROM `cctvs`");
	new Cache:cache = mysql_query(dbHandle, query),
		count;
	
    cache_get_value_int(0, "total", count);

	cache_delete(cache);
    cache = MYSQL_INVALID_CACHE;
	return count;
}

MDC_CountRoster()
{
    new count = 0;
    for(new i = 0; i != MAX_PATROL; i++)
    {
        if (!PatrolInfo[1][i][patrulExists]) continue;
        count++;
    }
    return count;
}

GetOfficerName(playerid) {
    new officername[24];
    format(officername, sizeof(officername), "%s", GetNameEx(playerid));

    strdel(officername, 1, strfind(officername, " "));
    strins(officername, ".", 1);
    return officername;
}
