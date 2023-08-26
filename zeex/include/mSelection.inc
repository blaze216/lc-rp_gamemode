//
// Model Selection using previews. For SA-MP 0.3x and above.
// - D0erfler 2013
// - Kye 2013
//
// Version 1.1 R2

/*Functions to be used

LoadModelSelectionMenu(f_name[])
HideModelSelectionMenu(playerid)
ShowModelSelectionMenu(playerid, ListID, header_text[], dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x888888FF, tdSelectionColor = 0x88888899)
ShowModelSelectionMenuEx(playerid, items_array[], item_amount, header_text[], extraid, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x4A5A6BBB, previewBGcolor = 0x888888FF, tdSelectionColor = 0x88888899)

*/
// Callbacks
forward OnPlayerModelSelection(playerid, response, listid, modelid, index);
forward OnPlayerModelSelectionEx(playerid, response, extraid, modelid, index);

new BuyingVeh[MAX_PLAYERS];

new VehicleNames2[212][] = {
   "Landstalker",  "Bravura",  "Buffalo", "Linerunner", "Perennial", "Sentinel",
   "Dumper",  "Firetruck" ,  "Trashmaster" ,  "Stretch",  "Manana",  "Infernus",
   "Voodoo", "Pony",  "Mule", "Cheetah", "Ambulance",  "Leviathan",  "Moonbeam",
   "Esperanto", "Taxi",  "Washington",  "Bobcat",  "Mr Whoopee", "BF Injection",
   "Hunter", "Premier",  "Enforcer",  "Securicar", "Banshee", "Predator", "Bus",
   "Rhino",  "Barracks",  "Hotknife",  "Trailer",  "Previon", "Coach", "Cabbie",
   "Stallion", "Rumpo", "RC Bandit",  "Romero", "Packer", "Monster",  "Admiral",
   "Squalo", "Seasparrow", "Pizzaboy", "Tram", "Trailer",  "Turismo", "Speeder",
   "Reefer", "Tropic", "Flatbed","Yankee", "Caddy", "Solair","Berkley's RC Van",
   "Skimmer", "PCJ-600", "Faggio", "Freeway", "RC Baron","RC Raider","Glendale",
   "Oceanic", "Sanchez", "Sparrow",  "Patriot", "Quad",  "Coastguard", "Dinghy",
   "Hermes", "Sabre", "Rustler", "ZR-350", "Walton",  "Regina",  "Comet", "BMX",
   "Burrito", "Camper", "Marquis", "Baggage", "Dozer","Maverick","News Chopper",
   "Rancher", "FBI Rancher", "Virgo", "Greenwood","Jetmax","Hotring","Sandking",
   "Blista Compact", "Police Maverick", "Boxville", "Benson","Mesa","RC Goblin",
   "Hotring Racer", "Hotring Racer", "Bloodring Banger", "Rancher",  "Super GT",
   "Elegant", "Journey", "Bike", "Mountain Bike", "Beagle", "Cropdust", "Stunt",
   "Tanker", "RoadTrain", "Nebula", "Majestic", "Buccaneer", "Shamal",  "Hydra",
   "FCR-900","NRG-500","HPV1000","Cement Truck","Tow Truck","Fortune","Cadrona",
   "FBI Truck", "Willard", "Forklift","Tractor","Combine","Feltzer","Remington",
   "Slamvan", "Blade", "Freight", "Streak","Vortex","Vincent","Bullet","Clover",
   "Sadler",  "Firetruck", "Hustler", "Intruder", "Primo", "Cargobob",  "Tampa",
   "Sunrise", "Merit",  "Utility Truck",  "Nevada", "Yosemite", "Windsor",  "Monster",
   "Monster","Uranus","Jester","Sultan","Stratum","Elegy","Raindance","RCTiger",
   "Flash","Tahoma","Savanna", "Bandito", "Freight", "Trailer", "Kart", "Mower",
   "Dune", "Sweeper", "Broadway", "Tornado", "AT-400",  "DFT-30", "Huntley",
   "Stafford", "BF-400", "Newsvan","Tug","Trailer","Emperor","Wayfarer","Euros",
   "Hotdog", "Club", "Trailer", "Trailer","Andromada","Dodo","RC Cam", "Launch",
   "Police Car (LSPD)", "Police Car (SFPD)","Police Car (LVPD)","Police Ranger",
   "Picador",   "S.W.A.T. Van",  "Alpha",   "Phoenix",   "Glendale",   "Sadler",
   "Luggage Trailer","Luggage Trailer","Stair Trailer", "Boxville", "Farm Plow",
   "Utility Trailer"
};

enum DEALERSHIP
{
	cCarModel,
	cCarPrice
}
new DonateVehicles[] = 
	{424, 568, 495, 541, 411, 522, 490};

new VehiclePrices[][DEALERSHIP] = {
	{409, 75500},//A-Class
	{421, 22100},
	{426, 24200},
	{434, 35900},
	{480, 36900},
	{507, 26900},
	{533, 29800},
	{545, 32100},
	{551, 19900},
	{555, 38500},
	{560, 59800},
	{580, 42500},//A-Class
	{401, 9700},//B-Class
	{405, 15200},
	{410, 7900},
	{419, 8700},
	{436, 8200},
	{439, 9900},
	{445, 14700},
	{458, 9100},
	{466, 8600},
	{467, 8800},
	{482, 13300},
	{491, 10300},
	{492, 13900},
	{496, 14200},
	{516, 10800},
	{517, 11300},
	{518, 9800},
	{526, 9100},
	{527, 8800},
	{529, 11500},
	{534, 9800},
	{535, 12500},
	{536, 10400},
	{540, 14700},
	{546, 9900},
	{547, 8400},
	{550, 14500},
	{561, 11100},
	{566, 12500},
	{567, 14800},
	{575, 10200},
	{585, 13500},
	{589, 11600},//B-Class
	{404, 5800},//С-Class
	{412, 7000},
	{418, 7400},
	{474, 6900},
	{475, 7700},
	{479, 7400},
	{542, 5500},
	{543, 5800},
	{549, 5300},
	{576, 7200},
	{600, 6500},
	{605, 3000},
	{604, 3000},//С-Class
	{402, 73200},//Sport
	{411, 170700},
	{429, 119900},
	{451, 112500},
	{477, 86500},
	{506, 109900},
	{541, 117700},
	{558, 48800},
	{559, 79500},
	{562, 82800},
	{565, 49500},
	{587, 46200},
	{602, 45800},
	{415, 141000},
	{603, 72900},//Sport
	{400, 17900},//Off-Road
	{470, 52900},
	{489, 16700},
	{490, 72800},
	{495, 54200},
	{500, 14800},
	{554, 12900},
	{579, 25200},//Off-Road
	{461, 10900},//MotoBike
	{462, 4600},
	{463, 8100},
	{468, 10200},
	{471, 9900},
	{521, 12500},
	{522, 65900},
	{581, 9700},
	{586, 8300},
	{423, 11000},//Industrial
	{408, 14900},
	{413, 8200},
	{414, 11800},
	{420, 10900},
	{422, 8100},
	{423, 11000},
	{431, 15200},
	{437, 15500},
	{438, 6900},
	{440, 10400},
	{455, 33800},
	{456, 14800},
	{478, 6700},
	{498, 14400},
	{499, 13000},
	{524, 34800},
	{525, 6900},
	{531, 5400},
	{552, 14500},
	{572, 4900},
	{578, 32900},
	{406, 35000},
	{588, 11000},//Industrial
	{424, 45800},//Other
	{442, 11800},
	{457, 8400},
	{483, 12500},
	{508, 13800},
	{568, 61500},//Other
	{446, 34900},//Boats
	{453, 10700},
	{454, 78500},
	{473, 5500},
	{484, 39500},
	{493, 69900},//Boats
	{469, 112500},//Air transport
	{487, 144900},
	{460, 164800},
	{512, 114900},
	{519, 199900},
	{593, 147500}//Air transport
};


// settings static lists
#define mS_TOTAL_ITEMS         	1000 // Max amount of items from all lists
#define mS_TOTAL_LISTS			20 // Max amount of lists
#define mS_TOTAL_ROT_ZOOM		100 // Max amount of items using extra information like zoom or rotations

// settings dynamic per player lists
#define mS_CUSTOM_MAX_ITEMS		179
new gCustomList[MAX_PLAYERS][mS_CUSTOM_MAX_ITEMS];

#define mS_INVALID_LISTID		mS_TOTAL_LISTS
#define mS_CUSTOM_LISTID		(mS_TOTAL_LISTS+1)

#define mS_NEXT_TEXT   "Next"
#define mS_PREV_TEXT   "Prev"
#define mS_CANCEL_TEXT   "Cancel"

#define mS_SELECTION_ITEMS 		21
#define mS_ITEMS_PER_LINE  		7


#define mS_DIALOG_BASE_X   	75.0//75 ПОЗИЦИЯ ОКОО
#define mS_DIALOG_BASE_Y   	130.0//130

#define mS_DIALOG_WIDTH    	550.0//550 РОЗМЕР ОКОО
#define mS_DIALOG_HEIGHT   	180.0//180

#define mS_SPRITE_DIM_X    	60.0//60
#define mS_SPRITE_DIM_Y    	70.0//70


#define VEHmS_DIALOG_BASE_X   	110.0//75 ПОЗИЦИЯ ОКОО
#define VEHmS_DIALOG_BASE_Y   	90.0//130

#define VEHmS_DIALOG_WIDTH    	522.5//550 РОЗМЕР ОКОО
#define VEHmS_DIALOG_HEIGHT   	180.0//180

#define VEHmS_SPRITE_DIM_X    	120//80.0//60
#define VEHmS_SPRITE_DIM_Y    	92//83.0//70

new PlayerText:gCurrentPageTextDrawId[MAX_PLAYERS];
new PlayerText:gHeaderTextDrawId[MAX_PLAYERS];
new PlayerText:gBackgroundTextDrawId[MAX_PLAYERS];
new PlayerText:gNextButtonTextDrawId[MAX_PLAYERS];
new PlayerText:gPrevButtonTextDrawId[MAX_PLAYERS];
new PlayerText:gCancelButtonTextDrawId[MAX_PLAYERS];
new PlayerText:gVehicleName[MAX_PLAYERS][mS_SELECTION_ITEMS];
new PlayerText:gSelectionItems[MAX_PLAYERS][mS_SELECTION_ITEMS];
new gSelectionItemsTag[MAX_PLAYERS][mS_SELECTION_ITEMS];
new gItemAt[MAX_PLAYERS];

#define mS_LIST_START			0
#define mS_LIST_END				1
new gLists[mS_TOTAL_LISTS][2]; // list information start/end index

#define mS_ITEM_MODEL			0
#define mS_ITEM_ROT_ZOOM_ID 	1
new gItemList[mS_TOTAL_ITEMS][2];

new Float:gRotZoom[mS_TOTAL_ROT_ZOOM][4]; // Array for saving rotation and zoom info
new gItemAmount = 0; // Amount of items used
new gListAmount = 0; // Amount of lists used
new gRotZoomAmount = 0; // Amount of Rotation/Zoom informations used

//------------------------------------------------

stock mS_GetNumberOfPages(ListID)
{
	new ItemAmount = mS_GetAmountOfListItems(ListID);
	if((ItemAmount >= mS_SELECTION_ITEMS) && (ItemAmount % mS_SELECTION_ITEMS) == 0)
	{
		return (ItemAmount / mS_SELECTION_ITEMS);
	}
	else return (ItemAmount / mS_SELECTION_ITEMS) + 1;
}

//------------------------------------------------

stock mS_GetNumberOfPagesEx(playerid)
{
	new ItemAmount = mS_GetAmountOfListItemsEx(playerid);
	if((ItemAmount >= mS_SELECTION_ITEMS) && (ItemAmount % mS_SELECTION_ITEMS) == 0)
	{
		return (ItemAmount / mS_SELECTION_ITEMS);
	}
	else return (ItemAmount / mS_SELECTION_ITEMS) + 1;
}

//------------------------------------------------

stock mS_GetAmountOfListItems(ListID)
{
	return (gLists[ListID][mS_LIST_END] - gLists[ListID][mS_LIST_START])+1;
}

//------------------------------------------------

stock mS_GetAmountOfListItemsEx(playerid)
{
	return GetPVarInt(playerid, "mS_custom_item_amount");
}

//------------------------------------------------

stock mS_GetPlayerCurrentListID(playerid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 1) return GetPVarInt(playerid, "mS_list_id");
	else return mS_INVALID_LISTID;
}

//------------------------------------------------

stock PlayerText:mS_CreateCurrentPageTextDraw(playerid, Float:Xpos, Float:Ypos)
{
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, "0/0");
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------
// Creates a button textdraw and returns the textdraw ID.

stock PlayerText:mS_CreatePlayerDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, button_text[])
{
 	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, button_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 1);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x00000050);
   	PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000FF);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.4, 1.1);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}
 stock PlayerText:mS_CreateVehCatDialogButton(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, button_text[])
{
 	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, button_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 1);
   	PlayerTextDrawBoxColor(playerid, txtInit, 0x00000000);
   	PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000AA);
	PlayerTextDrawLetterSize(playerid, txtInit, 1.1, 1.5);
	PlayerTextDrawFont(playerid, txtInit, 3);
	PlayerTextDrawSetShadow(playerid, txtInit, 0); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xD8030CFF);
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

stock PlayerText:mS_CreatePlayerDialogTextureVEH(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, texture[])
{
 	new PlayerText:txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, texture);
	PlayerTextDrawFont(playerid, txtInit, 4);
    PlayerTextDrawAlignment(playerid, txtInit, 2);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawSetSelectable(playerid, txtInit, 1);
    PlayerTextDrawShow(playerid, txtInit);
	
	PlayerTextDrawColor(playerid, txtInit, 0xF01000FF);
	
	
	
    return txtInit;
}
 //------------------------------------------------
forward IsADonateModel(model);
public IsADonateModel(model)
{
	for(new i = 0; i < sizeof(DonateVehicles); i++)
		if(DonateVehicles[i] == model)
			return true;
	return false;
}
 
stock PlayerText:CreateVehicleName(playerid, model, Float:Xpos, Float:Ypos, Float:Width, Float:Height, vehiclename[], vehicleprice[])
{
 	new PlayerText:txtInit;
	new str[128];
	if(IsADonateModel(model))
		format(str, sizeof(str), "%s~n~~g~$%s~n~~n~~n~~n~~n~~n~~y~[DONATE]", vehiclename, vehicleprice);
	else
		format(str, sizeof(str), "%s~n~~g~$%s", vehiclename, vehicleprice);
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, str);
   	PlayerTextDrawBackgroundColor(playerid, txtInit, 0x000000FF);
	PlayerTextDrawLetterSize(playerid, txtInit, 0.3, 1.0);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 1); // no shadow
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xC0C0C0FF);
    PlayerTextDrawTextSize(playerid, txtInit, Height, Width); // The width and height are reversed for centering.. something the game does <g>
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}
 
 
//------------------------------------------------

stock PlayerText:mS_CreatePlayerHeaderTextDraw(playerid, Float:Xpos, Float:Ypos, header_text[])
{
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos, header_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 1.25, 1.25);
	PlayerTextDrawFont(playerid, txtInit, 1);
	PlayerTextDrawSetShadow(playerid, txtInit, 0);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

stock PlayerText:CreateHeaderBuyableText(playerid, Float:Xpos, Float:Ypos, header_text[])
{
	new PlayerText:txtInit;
   	txtInit = CreatePlayerTextDraw(playerid, Xpos, Ypos-8.5, header_text);
   	PlayerTextDrawUseBox(playerid, txtInit, 0);
	PlayerTextDrawLetterSize(playerid, txtInit, 1.0, 3.5);
	PlayerTextDrawFont(playerid, txtInit, 0);
	PlayerTextDrawSetShadow(playerid, txtInit, 1);
    PlayerTextDrawSetOutline(playerid, txtInit, 1);
    PlayerTextDrawColor(playerid, txtInit, 0xFFFFFFFF);
    PlayerTextDrawShow(playerid, txtInit);
    return txtInit;
}

//------------------------------------------------

stock PlayerText:mS_CreatePlayerBGTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, bgcolor)
{
	new PlayerText:txtBackground;
	
	txtBackground = CreatePlayerTextDraw(playerid, Xpos, Ypos,"                                            ~n~");
	PlayerTextDrawUseBox(playerid, txtBackground, 1);
    PlayerTextDrawBoxColor(playerid, txtBackground, bgcolor);
	PlayerTextDrawLetterSize(playerid, txtBackground, 5.0, 5.0);
	PlayerTextDrawFont(playerid, txtBackground, 0);
	PlayerTextDrawSetShadow(playerid, txtBackground, 0);
    PlayerTextDrawSetOutline(playerid, txtBackground, 0);
    PlayerTextDrawColor(playerid, txtBackground,0x000000FF);
    PlayerTextDrawTextSize(playerid, txtBackground, Width, Height);
   	PlayerTextDrawBackgroundColor(playerid, txtBackground, bgcolor);
    PlayerTextDrawShow(playerid, txtBackground);
    return txtBackground;
}

stock PlayerText:mSVeh_CreatePlayerBGTextDraw(playerid, Float:Xpos, Float:Ypos, Float:Width, Float:Height, bgcolor)
{
	new PlayerText:txtBackground;
	
	txtBackground = CreatePlayerTextDraw(playerid, Xpos, Ypos,"~n~~n~~n~~n~~n~"); // enough space for everyone
	PlayerTextDrawUseBox(playerid, txtBackground, 1);
    PlayerTextDrawBoxColor(playerid, txtBackground, bgcolor);
	PlayerTextDrawLetterSize(playerid, txtBackground, 5.0, 5.0);
	PlayerTextDrawFont(playerid, txtBackground, 0);
	PlayerTextDrawSetShadow(playerid, txtBackground, 0);
    PlayerTextDrawSetOutline(playerid, txtBackground, 0);
    PlayerTextDrawColor(playerid, txtBackground,0x000000FF);
    PlayerTextDrawTextSize(playerid, txtBackground, Width, Height);
   	PlayerTextDrawBackgroundColor(playerid, txtBackground, bgcolor);
    PlayerTextDrawShow(playerid, txtBackground);
    return txtBackground;
}
//------------------------------------------------
// Creates a model preview sprite

stock PlayerText:mS_CreateMPTextDraw(playerid, modelindex, Float:Xpos, Float:Ypos, Float:Xrot, Float:Yrot, Float:Zrot, Float:mZoom, Float:width, Float:height, bgcolor)
{
    new PlayerText:txtPlayerSprite = CreatePlayerTextDraw(playerid, Xpos, Ypos, ""); // it has to be set with SetText later
    PlayerTextDrawFont(playerid, txtPlayerSprite, TEXT_DRAW_FONT_MODEL_PREVIEW);
    PlayerTextDrawColor(playerid, txtPlayerSprite, 0xFFFFFFFF);
    PlayerTextDrawBackgroundColor(playerid, txtPlayerSprite, bgcolor);
    PlayerTextDrawTextSize(playerid, txtPlayerSprite, width, height); // Text size is the Width:Height
    PlayerTextDrawSetPreviewModel(playerid, txtPlayerSprite, modelindex);
    PlayerTextDrawSetPreviewRot(playerid,txtPlayerSprite, Xrot, Yrot, Zrot, mZoom);
    PlayerTextDrawSetSelectable(playerid, txtPlayerSprite, 1);
    PlayerTextDrawShow(playerid,txtPlayerSprite);
    return txtPlayerSprite;
}

//------------------------------------------------

stock mS_DestroyPlayerMPs(playerid)
{
	new x=0;
	while(x != mS_SELECTION_ITEMS) {
	    if(gSelectionItems[playerid][x] != PlayerText:INVALID_TEXT_DRAW) {
			PlayerTextDrawDestroy(playerid, gSelectionItems[playerid][x]);
			gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
			if(BuyingVeh[playerid] == 1)
			{
				if(gVehicleName[playerid][x] != PlayerText:INVALID_TEXT_DRAW) 
				{
					PlayerTextDrawDestroy(playerid, gVehicleName[playerid][x]);
					gVehicleName[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
				}
			}
		}
		x++;
	}
}

//------------------------------------------------

stock mS_ShowPlayerMPs(playerid)
{
	new bgcolor = GetPVarInt(playerid, "mS_previewBGcolor");
    new x=0;
	new Float:BaseX = mS_DIALOG_BASE_X;
	new Float:BaseY = mS_DIALOG_BASE_Y - (mS_SPRITE_DIM_Y * 0.33); // down a bit
	new linetracker = 0;
	
	new mS_listID = mS_GetPlayerCurrentListID(playerid);
	if(mS_listID == mS_CUSTOM_LISTID)
	{
		new itemat = (GetPVarInt(playerid, "mS_list_page") * mS_SELECTION_ITEMS);
		new Float:rotzoom[4];
		rotzoom[0] = GetPVarFloat(playerid, "mS_custom_Xrot");
		rotzoom[1] = GetPVarFloat(playerid, "mS_custom_Yrot");
		rotzoom[2] = GetPVarFloat(playerid, "mS_custom_Zrot");
		rotzoom[3] = GetPVarFloat(playerid, "mS_custom_Zoom");
		new itemamount = mS_GetAmountOfListItemsEx(playerid);
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);

		while(x != mS_SELECTION_ITEMS && itemat < (itemamount)) {
			if(linetracker == 0) {
				BaseX = mS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += mS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gCustomList[playerid][itemat], BaseX, BaseY, rotzoom[0], rotzoom[1], rotzoom[2], rotzoom[3], mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgcolor);
			gSelectionItemsTag[playerid][x] = gCustomList[playerid][itemat];
			BaseX += mS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == mS_ITEMS_PER_LINE) linetracker = 0;
			itemat++;
			x++;
		}
	}
	else
	{
		new itemat = (gLists[mS_listID][mS_LIST_START] + (GetPVarInt(playerid, "mS_list_page") * mS_SELECTION_ITEMS));
		
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);

		while(x != mS_SELECTION_ITEMS && itemat < (gLists[mS_listID][mS_LIST_END]+1)) {
			if(linetracker == 0) {
				BaseX = mS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += mS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			new rzID = gItemList[itemat][mS_ITEM_ROT_ZOOM_ID]; // avoid long line
			if(rzID > -1) gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, gRotZoom[rzID][0], gRotZoom[rzID][1], gRotZoom[rzID][2], gRotZoom[rzID][3], mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgcolor);
			else gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, 0.0, 0.0, 0.0, 1.0, mS_SPRITE_DIM_X, mS_SPRITE_DIM_Y, bgcolor);
			gSelectionItemsTag[playerid][x] = gItemList[itemat][mS_ITEM_MODEL];
			BaseX += mS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == mS_ITEMS_PER_LINE) linetracker = 0;
			itemat++;
			x++;
		}
	}
}

stock ShowPlayerBuyable(playerid)
{
	new bgcolor = GetPVarInt(playerid, "mS_previewBGcolor");
    new x=0;
	new Float:BaseX = VEHmS_DIALOG_BASE_X;
	new Float:BaseY = VEHmS_DIALOG_BASE_Y - (VEHmS_SPRITE_DIM_Y * 0.33); // down a bit
	new linetracker = 0;
	
	new mS_listID = mS_GetPlayerCurrentListID(playerid);
	if(mS_listID == mS_CUSTOM_LISTID)
	{
		new itemat = (GetPVarInt(playerid, "mS_list_page") * 6);
		new Float:rotzoom[4];
		rotzoom[0] = GetPVarFloat(playerid, "mS_custom_Xrot");
		rotzoom[1] = GetPVarFloat(playerid, "mS_custom_Yrot");
		rotzoom[2] = GetPVarFloat(playerid, "mS_custom_Zrot");
		rotzoom[3] = GetPVarFloat(playerid, "mS_custom_Zoom");
		new itemamount = mS_GetAmountOfListItemsEx(playerid);
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);

		while(x != 6 && itemat < (itemamount)) {
			if(linetracker == 0) {
				BaseX = VEHmS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += VEHmS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}	
			gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gCustomList[playerid][itemat], BaseX, BaseY, rotzoom[0], rotzoom[1], rotzoom[2], rotzoom[3], VEHmS_SPRITE_DIM_X, VEHmS_SPRITE_DIM_Y, bgcolor);
			gSelectionItemsTag[playerid][x] = gCustomList[playerid][itemat];
			BaseX += VEHmS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == 3) linetracker = 0;
			itemat++;
			x++;
		}
	}
	else
	{
		new itemat = (gLists[mS_listID][mS_LIST_START] + (GetPVarInt(playerid, "mS_list_page") * 6));
		
		// Destroy any previous ones created
		mS_DestroyPlayerMPs(playerid);
		while(x != 6 && itemat < (gLists[mS_listID][mS_LIST_END]+1)) {
			if(linetracker == 0) {
				BaseX = VEHmS_DIALOG_BASE_X + 25.0; // in a bit from the box
				BaseY += VEHmS_SPRITE_DIM_Y + 1.0; // move on the Y for the next line
			}
			new rzID = gItemList[itemat][mS_ITEM_ROT_ZOOM_ID]; // avoid long line
			if(rzID > -1) gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, gRotZoom[rzID][0], gRotZoom[rzID][1], gRotZoom[rzID][2], gRotZoom[rzID][3], VEHmS_SPRITE_DIM_X, VEHmS_SPRITE_DIM_Y, bgcolor);
			else gSelectionItems[playerid][x] = mS_CreateMPTextDraw(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, 0.0, 0.0, 0.0, 1.0, VEHmS_SPRITE_DIM_X, VEHmS_SPRITE_DIM_Y, bgcolor);
			
			gVehicleName[playerid][x] = CreateVehicleName(playerid, gItemList[itemat][mS_ITEM_MODEL], BaseX, BaseY, VEHmS_SPRITE_DIM_X, VEHmS_SPRITE_DIM_Y, VehicleNames2[gItemList[itemat][mS_ITEM_MODEL]-400], GetAmount2(GetVehiclePrice(gItemList[itemat][mS_ITEM_MODEL])));
			
			gSelectionItemsTag[playerid][x] = gItemList[itemat][mS_ITEM_MODEL];
			BaseX += VEHmS_SPRITE_DIM_X + 1.0; // move on the X for the next sprite
			linetracker++;
			if(linetracker == 3) linetracker = 0;
			itemat++;
			x++;
		}
	}
}

stock GetVehiclePrice(model)
{
	for(new i = 0; i < sizeof(VehiclePrices); i++)
	{
		if(model == VehiclePrices[i][cCarModel])
			return VehiclePrices[i][cCarPrice];
	}
	return 0;
}

stock GetAmount2(amount)
{
	new text[15];
	format(text, sizeof(text), "%d", amount);
	if(strlen(text) > 14)
	{
		format(text, sizeof(text), "%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12], text[13], text[14]);
	}
	else if(strlen(text) > 13)
	{
		format(text, sizeof(text), "%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12], text[13]);
	}
	else if(strlen(text) > 12)
	{
		format(text, sizeof(text), "%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11], text[12]);
	}
	else if(strlen(text) > 11)
	{
		format(text, sizeof(text), "%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10], text[11]);
	}
	else if(strlen(text) > 10)
	{
		format(text, sizeof(text), "%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9], text[10]);
	}
	else if(strlen(text) > 9)
	{
		format(text, sizeof(text), "%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8], text[9]);
	}
	else if(strlen(text) > 8)
	{
		format(text, sizeof(text), "%.1s%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7], text[8]);
	}
	else if(strlen(text) > 7)
	{
		format(text, sizeof(text), "%.1s%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6], text[7]);
	}
	else if(strlen(text) > 6)
	{
		format(text, sizeof(text), "%.1s,%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5], text[6]);
	}
	else if(strlen(text) > 5)
	{
		format(text, sizeof(text), "%.1s%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4], text[5]);
	}
	else if(strlen(text) > 4)
	{
		format(text, sizeof(text), "%.1s%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3], text[4]);
	}
	else if(strlen(text) > 3)
	{
		format(text, sizeof(text), "%.1s,%.1s%.1s%.1s", text[0], text[1], text[2], text[3]);
	}
	return text;
}


//------------------------------------------------

stock mS_UpdatePageTextDraw(playerid)
{
	new PageText[64+1];
	new listID = mS_GetPlayerCurrentListID(playerid);
	if(listID == mS_CUSTOM_LISTID)
	{
		format(PageText, 64, "%d/%d", GetPVarInt(playerid,"mS_list_page") + 1, mS_GetNumberOfPagesEx(playerid));
		PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid], PageText);
	}
	else
	{
		format(PageText, 64, "%d/%d", GetPVarInt(playerid,"mS_list_page") + 1, mS_GetNumberOfPages(listID));
		PlayerTextDrawSetString(playerid, gCurrentPageTextDrawId[playerid], PageText);
	}
}

//------------------------------------------------

stock ShowModelSelectionMenu(playerid, ListID, header_text[], dialogBGcolor = 0x00000050, previewBGcolor = 0x888888FF , tdSelectionColor = 0x88888899)
{
	//if(!(0 <= ListID < mS_TOTAL_LISTS && gLists[ListID][mS_LIST_START] != gLists[ListID][mS_LIST_END])) return 0;
		
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_list_page", 0);
	SetPVarInt(playerid, "mS_list_id", ListID);
	SetPVarInt(playerid, "mS_list_active", 1);
	SetPVarInt(playerid, "mS_list_time", GetTickCount());

    gBackgroundTextDrawId[playerid] = mS_CreatePlayerBGTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y + 20.0, mS_DIALOG_WIDTH, mS_DIALOG_HEIGHT, dialogBGcolor);
    gHeaderTextDrawId[playerid] = mS_CreatePlayerHeaderTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y, header_text);
    gCurrentPageTextDrawId[playerid] = mS_CreateCurrentPageTextDraw(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y + 15.0);
    
	gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_NEXT_TEXT);
    gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 90.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_PREV_TEXT);
	
	gCancelButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 150.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_CANCEL_TEXT);
	
	SetPVarInt(playerid, "mS_previewBGcolor", previewBGcolor);
    mS_ShowPlayerMPs(playerid);
    mS_UpdatePageTextDraw(playerid);
	
	SelectTextDraw(playerid, tdSelectionColor);
	return 1;
}

stock ShowModelSelectionMenu2(playerid, ListID, header_text[], dialogBGcolor = 0xCDF9C770, previewBGcolor = 0xCDF9C780,  tdSelectionColor = 0xFFFF00AA)
{
	//if(!(0 <= ListID < mS_TOTAL_LISTS && gLists[ListID][mS_LIST_START] != gLists[ListID][mS_LIST_END])) return 0;
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_list_page", 0);
	SetPVarInt(playerid, "mS_list_id", ListID);
	SetPVarInt(playerid, "mS_list_active", 1);
	SetPVarInt(playerid, "mS_list_time", GetTickCount());
	
    gBackgroundTextDrawId[playerid] = mSVeh_CreatePlayerBGTextDraw(playerid, VEHmS_DIALOG_BASE_X, VEHmS_DIALOG_BASE_Y+40, VEHmS_DIALOG_WIDTH, VEHmS_DIALOG_HEIGHT, dialogBGcolor);

	gHeaderTextDrawId[playerid] = CreateHeaderBuyableText(playerid, VEHmS_DIALOG_BASE_X, VEHmS_DIALOG_BASE_Y+25.0, header_text);

	gCancelButtonTextDrawId[playerid] = mS_CreateVehCatDialogButton(playerid, VEHmS_DIALOG_WIDTH - 17.0, VEHmS_DIALOG_BASE_Y+VEHmS_DIALOG_HEIGHT-140.0, 50.0, 16.0, "X");
	
	gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogTextureVEH(playerid, VEHmS_DIALOG_BASE_X+VEHmS_DIALOG_WIDTH-120.0, VEHmS_DIALOG_BASE_Y+(VEHmS_DIALOG_HEIGHT/2)+50.0, 32.0, 32.0, "LD_BEAT:right");
	 
    gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogTextureVEH(playerid, VEHmS_DIALOG_BASE_X-20.0, VEHmS_DIALOG_BASE_Y+(VEHmS_DIALOG_HEIGHT/2)+49.0, 32.0, 32.0, "LD_BEAT:left");
	
	
	BuyingVeh[playerid] = 1;
	SetPVarInt(playerid, "mS_previewBGcolor", previewBGcolor);
    ShowPlayerBuyable(playerid);
    mS_UpdatePageTextDraw(playerid);
	
	SelectTextDraw(playerid, tdSelectionColor);
	return 1;
}

//------------------------------------------------------------

stock ShowModelSelectionMenuEx(playerid, items_array[], item_amount, header_text[], extraid, Float:Xrot = 0.0, Float:Yrot = 0.0, Float:Zrot = 0.0, Float:mZoom = 1.0, dialogBGcolor = 0x00000050, previewBGcolor = 0x888888FF, tdSelectionColor = 0x88888899)
{
		
	mS_DestroySelectionMenu(playerid);
	if(item_amount > mS_CUSTOM_MAX_ITEMS)
	{
		item_amount = mS_CUSTOM_MAX_ITEMS;
		print("-mSelection- WARNING: Too many items given to \"ShowModelSelectionMenuEx\", increase \"mS_CUSTOM_MAX_ITEMS\" to fix this");
	}
	if(item_amount > 0)
	{
		for(new i=0;i<item_amount;i++)
		{
			gCustomList[playerid][i] = items_array[i];
		}
		SetPVarInt(playerid, "mS_list_page", 0);
		SetPVarInt(playerid, "mS_list_id", mS_CUSTOM_LISTID);
		SetPVarInt(playerid, "mS_list_active", 1);
		SetPVarInt(playerid, "mS_list_time", GetTickCount());
	
		SetPVarInt(playerid, "mS_custom_item_amount", item_amount);
		SetPVarFloat(playerid, "mS_custom_Xrot", Xrot);
		SetPVarFloat(playerid, "mS_custom_Yrot", Yrot);
		SetPVarFloat(playerid, "mS_custom_Zrot", Zrot);
		SetPVarFloat(playerid, "mS_custom_Zoom", mZoom);
		SetPVarInt(playerid, "mS_custom_extraid", extraid);
		

		gBackgroundTextDrawId[playerid] = mS_CreatePlayerBGTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y + 20.0, mS_DIALOG_WIDTH, mS_DIALOG_HEIGHT, dialogBGcolor);
		gHeaderTextDrawId[playerid] = mS_CreatePlayerHeaderTextDraw(playerid, mS_DIALOG_BASE_X, mS_DIALOG_BASE_Y, header_text);
		gCurrentPageTextDrawId[playerid] = mS_CreateCurrentPageTextDraw(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y + 15.0);
		gNextButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 30.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_NEXT_TEXT);
		gPrevButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 90.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_PREV_TEXT);
		gCancelButtonTextDrawId[playerid] = mS_CreatePlayerDialogButton(playerid, mS_DIALOG_WIDTH - 150.0, mS_DIALOG_BASE_Y+mS_DIALOG_HEIGHT+100.0, 50.0, 16.0, mS_CANCEL_TEXT);

		SetPVarInt(playerid, "mS_previewBGcolor", previewBGcolor);
		mS_ShowPlayerMPs(playerid);
		mS_UpdatePageTextDraw(playerid);
		
		SelectTextDraw(playerid, tdSelectionColor);
		return 1;
	}
	return 0;
}

//------------------------------------------------

stock HideModelSelectionMenu(playerid)
{
	mS_DestroySelectionMenu(playerid);
	SetPVarInt(playerid, "mS_ignore_next_esc", 1);
	CancelSelectTextDraw(playerid);
	return 1;
}

//------------------------------------------------

stock mS_DestroySelectionMenu(playerid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 1)
	{
		if(mS_GetPlayerCurrentListID(playerid) == mS_CUSTOM_LISTID)
		{		
			DeletePVar(playerid, "mS_custom_Xrot");
			DeletePVar(playerid, "mS_custom_Yrot");
			DeletePVar(playerid, "mS_custom_Zrot");
			DeletePVar(playerid, "mS_custom_Zoom");
			DeletePVar(playerid, "mS_custom_extraid");
			DeletePVar(playerid, "mS_custom_item_amount");
		}
		DeletePVar(playerid, "mS_list_time");
		SetPVarInt(playerid, "mS_list_active", 0);
		mS_DestroyPlayerMPs(playerid);

		PlayerTextDrawDestroy(playerid, gHeaderTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gBackgroundTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gCurrentPageTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gNextButtonTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gPrevButtonTextDrawId[playerid]);
		PlayerTextDrawDestroy(playerid, gCancelButtonTextDrawId[playerid]);

		gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;	
		gCancelButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
		
		BuyingVeh[playerid] = 0;
	}
}

//------------------------------------------------

public OnPlayerConnect(playerid)
{
	// Init all of the textdraw related globals
    gHeaderTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gBackgroundTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCurrentPageTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gNextButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gPrevButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;
    gCancelButtonTextDrawId[playerid] = PlayerText:INVALID_TEXT_DRAW;

    for(new x=0; x < mS_SELECTION_ITEMS; x++) {
        gSelectionItems[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
	}
	
	for(new x=0; x < mS_SELECTION_ITEMS; x++) {
        gVehicleName[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
	}
	
	gItemAt[playerid] = 0;
	
	return CallLocalFunction("MP_OPC", "i", playerid);
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect MP_OPC

forward MP_OPC(playerid);

//-------------------------------------------
// Even though only Player* textdraws are used in this script,
// OnPlayerClickTextDraw is still required to handle ESC

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
   	if(GetPVarInt(playerid, "mS_ignore_next_esc") == 1) {
		SetPVarInt(playerid, "mS_ignore_next_esc", 0);
		return CallLocalFunction("MP_OPCTD", "ii", playerid, _:clickedid);
	}
   	if(GetPVarInt(playerid, "mS_list_active") == 0) return CallLocalFunction("MP_OPCTD", "ii", playerid, _:clickedid);

	// Handle: They cancelled (with ESC)
	if(clickedid == Text:INVALID_TEXT_DRAW) {
		new listid = mS_GetPlayerCurrentListID(playerid);
		if(listid == mS_CUSTOM_LISTID)
		{
			new extraid = GetPVarInt(playerid, "mS_custom_extraid");
			mS_DestroySelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelectionEx", "ddddd", playerid, 0, extraid, -1, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		else
		{
			mS_DestroySelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelection", "ddddd", playerid, 0, listid, -1, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
        return 1;
	}
	
	return CallLocalFunction("MP_OPCTD", "ii", playerid, _:clickedid);
}

#if defined _ALS_OnPlayerClickTextDraw
	#undef OnPlayerClickTextDraw
#else
	#define _ALS_OnPlayerClickTextDraw
#endif
#define OnPlayerClickTextDraw MP_OPCTD

forward MP_OPCTD(playerid, Text:clickedid);

//------------------------------------------------

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	if(GetPVarInt(playerid, "mS_list_active") == 0 || (GetTickCount()-GetPVarInt(playerid, "mS_list_time")) < 200 /* Disable instant selection */) return CallLocalFunction("MP_OPCPTD", "ii", playerid, _:playertextid);

	new curpage = GetPVarInt(playerid, "mS_list_page");
	
	// Handle: cancel button
	if(playertextid == gCancelButtonTextDrawId[playerid]) {
		new listID = mS_GetPlayerCurrentListID(playerid);
		if(listID == mS_CUSTOM_LISTID)
		{
			new extraid = GetPVarInt(playerid, "mS_custom_extraid");
			HideModelSelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelectionEx", "ddddd", playerid, 0, extraid, -1, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		else
		{
			HideModelSelectionMenu(playerid);
			CallLocalFunction("OnPlayerModelSelection", "ddddd", playerid, 0, listID, -1, -1);
			PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}
		
	// Handle: next button
	if(playertextid == gNextButtonTextDrawId[playerid]) {
		new listID = mS_GetPlayerCurrentListID(playerid);
		if(listID == mS_CUSTOM_LISTID)
		{			
			if(curpage < (mS_GetNumberOfPagesEx(playerid) - 1)) {
				SetPVarInt(playerid, "mS_list_page", curpage + 1);
				if(BuyingVeh[playerid] == 1)
				{
					for(new x=0; x < mS_SELECTION_ITEMS; x++) 
					{
						PlayerTextDrawDestroy(playerid, gVehicleName[playerid][x]);
					}
					ShowPlayerBuyable(playerid);
				}
				else
				{
					mS_ShowPlayerMPs(playerid);
				}
				mS_UpdatePageTextDraw(playerid);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			} else {
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			}
		}
		else
		{
			if(curpage < (mS_GetNumberOfPages(listID) - 1)) {
				SetPVarInt(playerid, "mS_list_page", curpage + 1);
				if(BuyingVeh[playerid] == 1)
				{
					for(new x=0; x < mS_SELECTION_ITEMS; x++) 
					{
						PlayerTextDrawDestroy(playerid, gVehicleName[playerid][x]);
					}
					ShowPlayerBuyable(playerid);
				}
				else
				{
					mS_ShowPlayerMPs(playerid);
				}
				mS_UpdatePageTextDraw(playerid);
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
			} else {
				PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
			}
		}
		return 1;
	}
	
	// Handle: previous button
	if(playertextid == gPrevButtonTextDrawId[playerid]) {
	    if(curpage > 0) {
	    	SetPVarInt(playerid, "mS_list_page", curpage - 1);
			if(BuyingVeh[playerid] == 1)
			{
				for(new x=0; x < mS_SELECTION_ITEMS; x++) 
				{
					PlayerTextDrawDestroy(playerid, gVehicleName[playerid][x]);
				}
				ShowPlayerBuyable(playerid);	
			}
	    	else
			{
				mS_ShowPlayerMPs(playerid);
			}
	    	mS_UpdatePageTextDraw(playerid);
	    	PlayerPlaySound(playerid, 1084, 0.0, 0.0, 0.0);
		} else {
		    PlayerPlaySound(playerid, 1085, 0.0, 0.0, 0.0);
		}
		return 1;
	}
	
	// Search in the array of textdraws used for the items
	new x=0;
	while(x != mS_SELECTION_ITEMS) {
	    if(playertextid == gSelectionItems[playerid][x]) {
			new listID = mS_GetPlayerCurrentListID(playerid);
			if(listID == mS_CUSTOM_LISTID)
			{
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				new item_id = gSelectionItemsTag[playerid][x];
				new extraid = GetPVarInt(playerid, "mS_custom_extraid");
				HideModelSelectionMenu(playerid);
				
				if(BuyingVeh[playerid] == 1)
				{
					BuyingVeh[playerid] = 0;
				}
	
				CallLocalFunction("OnPlayerModelSelectionEx", "ddddd", playerid, 1, extraid, item_id, (GetPVarInt(playerid,"mS_list_page") * mS_SELECTION_ITEMS) + x);
				return 1;
			}
			else
			{
				PlayerPlaySound(playerid, 1083, 0.0, 0.0, 0.0);
				new item_id = gSelectionItemsTag[playerid][x];
				HideModelSelectionMenu(playerid);
				if(BuyingVeh[playerid] == 1)
				{
					BuyingVeh[playerid] = 0;
				}
				CallLocalFunction("OnPlayerModelSelection", "ddddd", playerid, 1, listID, item_id, (GetPVarInt(playerid,"mS_list_page") * mS_SELECTION_ITEMS) + x);
				return 1;
			}
		}
		x++;
	}
	
	return CallLocalFunction("MP_OPCPTD", "ii", playerid, _:playertextid);
}

#if defined _ALS_OnPlayerClickPlayerTD
	#undef OnPlayerClickPlayerTextDraw
#else
	#define _ALS_OnPlayerClickPlayerTD
#endif
#define OnPlayerClickPlayerTextDraw MP_OPCPTD

forward MP_OPCPTD(playerid, PlayerText:playertextid);

//------------------------------------------------------------------


stock LoadModelSelectionMenu(f_name[])
{
	new File:f, str[75];
	format(str, sizeof(str), "%s", f_name);
	f = fopen(str, io_read);
	if( !f ) {
		printf("-mSelection- WARNING: Failed to load list: \"%s\"", f_name);
		return mS_INVALID_LISTID;
	}
	
	if(gListAmount >= mS_TOTAL_LISTS)
	{
		printf("-mSelection- WARNING: Reached maximum amount of lists, increase \"mS_TOTAL_LISTS\"", f_name);
		return mS_INVALID_LISTID;
	}
	new tmp_ItemAmount = gItemAmount; // copy value if loading fails
	
	
	new line[128], idxx;
	while(fread(f,line,sizeof(line),false))
	{
		if(tmp_ItemAmount >= mS_TOTAL_ITEMS)
		{
			printf("-mSelection- WARNING: Reached maximum amount of items, increase \"mS_TOTAL_ITEMS\"", f_name);
			break;
		}
		idxx = 0;
		if(!line[0]) continue;
		new mID = strval( mS_strtok(line,idxx) );
		if(0 <= mID < 20000)
		{
			gItemList[tmp_ItemAmount][mS_ITEM_MODEL] = mID;
		
			new tmp_mS_strtok[20];
			new Float:mRotation[3], Float:mZoom = 1.0;
			new bool:useRotation = false;
			
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mRotation[0] = floatstr(tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mRotation[1] = floatstr(tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mRotation[2] = floatstr(tmp_mS_strtok);
			}
			tmp_mS_strtok = mS_strtok(line,idxx);
			if(tmp_mS_strtok[0]) {
				useRotation = true;
				mZoom = floatstr(tmp_mS_strtok);
			}
			if(useRotation)
			{
				new bool:foundRotZoom = false;
				for(new i=0; i < gRotZoomAmount; i++)
				{
					if(gRotZoom[i][0] == mRotation[0] && gRotZoom[i][1] == mRotation[1] && gRotZoom[i][2] == mRotation[2] && gRotZoom[i][3] == mZoom)
					{
						foundRotZoom = true;
						gItemList[tmp_ItemAmount][mS_ITEM_ROT_ZOOM_ID] = i;
						break;
					}
				}
				if(gRotZoomAmount < mS_TOTAL_ROT_ZOOM)
				{
					if(!foundRotZoom)
					{
						gRotZoom[gRotZoomAmount][0] = mRotation[0];
						gRotZoom[gRotZoomAmount][1] = mRotation[1];
						gRotZoom[gRotZoomAmount][2] = mRotation[2];
						gRotZoom[gRotZoomAmount][3] = mZoom;
						gItemList[tmp_ItemAmount][mS_ITEM_ROT_ZOOM_ID] = gRotZoomAmount;
						gRotZoomAmount++;
					}
				}
				else print("-mSelection- WARNING: Not able to save rotation/zoom information. Reached maximum rotation/zoom information count. Increase '#define mS_TOTAL_ROT_ZOOM' to fix the issue"); 
			}
			else gItemList[tmp_ItemAmount][mS_ITEM_ROT_ZOOM_ID] = -1;
			tmp_ItemAmount++;
		}
	}
	if(tmp_ItemAmount > gItemAmount) // any models loaded ?
	{
		gLists[gListAmount][mS_LIST_START] = gItemAmount;
		gItemAmount = tmp_ItemAmount; // copy back
		gLists[gListAmount][mS_LIST_END] = (gItemAmount-1);
		
		gListAmount++;
		return (gListAmount-1);
	}
	printf("-mSelection- WARNING: No Items found in file: %s", f_name);
	return mS_INVALID_LISTID;
}
			
	
	
stock mS_strtok(const string[], &index)
{
	new length = strlen(string);
	while ((index < length) && (string[index] <= ' '))
	{
		index++;
	}

	new offset = index;
	new result[20];
	while ((index < length) && (string[index] > ' ') && ((index - offset) < (sizeof(result) - 1)))
	{
		result[index - offset] = string[index];
		index++;
	}
	result[index - offset] = EOS;
	return result;
}
