//3DMenu.
/*Natives
native Create3DMenu(playerid,Float:x,Float:y,Float:z,Float:rotation,boxes);
native SetBoxMaterial(MenuID,box,index,model,txd[],texture[], selectcolor, unselectcolor);
native Select3DMenu(playerid,MenuID);
native CancelSelect3DMenu(playerid);
native Destroy3DMenu(MenuID);*/

#define INVALID_3DMENU  (0xFFFF)

#define MAX_3DMENUS (MAX_PLAYERS)
#define MAX_BOXES (16)

#define GetTextureName(%0) ObjectTextures[%0][txName]

#define MAX_TEXTURES 	112
#define MAX_LISTS	 6

enum TEXTUREDEF 
{ 
	TModel, 
	TXDName[32], 
	TextureName[32], 
	MaterialColor, 
	txName[64] 
};

new ObjectTextures[MAX_TEXTURES][TEXTUREDEF] =
{
	{16008, "des_n", "des_ripplsand", 0,"Desert 1"},
 	{4242, "seabed", "sw_sand", 0,"Desert 2"},
 	{16475, "des_stownmots1", "des_motelwall3", 0,"Desert 3"},
	{3942, "bistro", "ahoodfence2", 0,"Stone tiles 1"},
	{13734, "hillcliff_lahills", "cobbles_kb_256", 0,"Stone tiles 2"},
	{16021, "des_geyser", "shingles1", 0,"Stone tiles 3"},
	{16005, "des_stownmain2","sanruf", 0,"Stone tiles 4"},
	{5016, "ground3_las", "ws_bigstones", 0,"Stone tiles 5"},
	{15046, "svcunthoose", "sl_gallerywall1", 0,"Stone tiles 6"},
	{14526, "sweetsmain", "ab_tile1", 0,"Stone tiles 7"},
	{14709, "lamidint2", "mp_apt1_bathfloor1", 0,"Stone tiles 8"},
	{15031, "lasmallsave", "ab_marble_checks", 0,"Stone tiles 9"},
	{4014, "civic01_lan", "sl_laglasswall2", 0,"Stone tiles 10"},
	{14534, "ab_wooziea", "ab_tileDiamond", 0,"Stone tiles 11"},
	{4011, "lanblokb", "sl_rotnbrik", 0,"Brick 1"},
	{12931, "sw_brewery", "sw_brewbrick01", 0,"Brick 2"},
	{12951, "ce_bankalley2", "sw_brick04", 0,"Brick 3"},
	{3908, "libertyfar", "Grass_128HV", 0,"Grass 1"},
	{3903, "libertyhi", "Grass", 0,"Grass 2"},
	{3933, "weemap", "rocktb128", 0,"Rock 1"},
	{16503, "desert", "des_redrock1", 0,"Rock 2"},
	{16407, "des_airfieldhus", "btdeck256", 0,"Wood 1"},
	{6295, "lawland2","boardwalk2_la", 0,"Wood 2"},
	{16005, "des_stownmain2","des_redslats", 0,"Wood 3"},
	{16005, "des_stownmain2","des_ghotwood1", 0,"Wood 4"},
	{18282, "cw_truckstopcs_t", "cw2_logwall", 0,"Wood 5"},
	{14771, "int_brothelint3", "GB_nastybar12", 0,"Wood 6"},
	{14777, "int_casinoint3", "GB_midbar05", 0,"Wood 7"},
	{14709, "lamidint2", "mp_apt1_roomfloor", 0,"Wood 8"},
	{14789, "ab_sfgymmain", "gym_floor6", 0,"Wood 9"},
	{18030, "gap", "mp_furn_floor", 0,"Wood 10"},
	{1823, "cj_tables", "CJ_WOOD6", 0,"Wood 11"},
	{964, "cj_crate_will","CJ_FLIGHT_CASE", 0,"Metal 1"},
	{16005, "des_stownmain2","alleydoor3", 0,"Metal 2"},
	{1775, "cj_commercial", "cj_sheetmetal2",0,"Metal 3"},
	{3440, "airportpillar", "metalic_64", 0,"Metal 4"},
	{8136, "vgsbikeschool", "ws_carparknew2", 0,"Carpet (dark)"},
	{14672, "genintintsex", "la_carp3", 0,"Carpet (light)"},
	{14847, "mp_policesf", "mp_cop_carpet", 0,"Carpet (blue)"},
	{14707, "labig3int2", "HS2_3Wall9", 0,"Carpet (red)"},
	{3953, "rczero_track", "waterclear256", 0,"Water"},
	{18752, "Volcano","lavalake", 0,"Ejection"},
	{16571, "des_se1","des_crackeddirt1", 0,"Marble"},
	{6866, "vgncnstrct1","Circus_gls_05", 0,"Purple boxes"},
	{5016, "ground3_las", "mural01_LA", 0,"Jesus"},
	{14526, "sweetsmain", "ab_kitchunit2", 0,"White panel"},
	{14444, "carter_block_2", "cd_wall1", 0,"Obsidian"},
	{15058, "svvgmid", "ah_wpaper3", 0,"Floral wallpaper"},
	{18018, "genintintbarb", "GB_midbar07", 0,"Green wallpaper"},
	{14533, "pleas_dome", "ab_velvor", 0,"Leather"},
	{3925, "weemap", "skyclouds", 0,"Clouds"},
	{19893, "LaptopSAMP1", "LaptopScreen1", 0,"Map San Andreas"},
	{18646, "matcolours","white", 0,"White"},
	{16005, "des_stownmain2", "black32", 0,"Black"},
	{18646, "matcolours","red", 0,"Red"},
	{18646, "matcolours", "blue", 0,"Dark Blue"},
	{14417, "dr_gsnew", "mp_cloth_subwall", 0,"Blue"},
	{18646, "matcolours","orange", 0,"Orange"},
	{18996, "mattextures","sampblack",0,"Black"},
	{3942, "bistro", "mp_snow", 0,"Snow"},
	{16005, "des_stownmain2","duskyred_64", 0,"Pink"},
	{16102, "des_cen", "sm_conc_hatch", 0,"Yellow-White 1"},
	{7980, "vegasairprtland","chevron64HVa", 0,"Yellow-White 2"},
	{5033, "union_las", "ws_carparkwall2", 0,"Yellow-White 3"},
	{16004, "des_teepee","des_dustconc", 0,"Grey 1"},
	{14593, "papaerchaseoffice", "ab_hosWallUpr", 0,"Grey 2"},
	{4014, "civic01_lan", "parking1plain", 0,"Grey 3"},
	{18646, "matcolours","green", 0,"Green 1"},
	{16005, "des_stownmain2","ws_green_wall1", 0,"Green 2"},
	{10086, "slapart01sfe", "sl_hirisergrnconc", 0,"Green 3"},
	{19128, "dancefloors","dancefloor1", 0,"Motley"},
	{8839, "vgsecarshow", "sw_wallbrick_06", 0, "Wall brick"},
	{8486, "ballys02", "walltiles_128", 0,"Wall tiles"},
	{10388, "scum2_sfs", "ws_cobrasign_small", 0, "Cobra Gym"},
	{10838, "airwelcomesign_sfse", "ws_airwelcome1", 0, "Air welcome"},
	{17566, "contachou1_lae2", "mp_apt1_woodpanel", 0, "Wood panel"},
	{5870, "sunst18_lawn", "tiledwall01_LA", 0, "Titled Wall"},
	{5727, "sunrise04_lawn", "fredwall3_LAwN", 0, "Fred Wall"},
	{11010, "crackfact_sfse", "ws_altz_wall4", 0, "Altz Wall"},
	{13131, "cunte_blockammo", "dt_ammu_wall2", 0, "Ammo Wall"},
	{17505, "lae2roads", "comptwall15", 0, "Comp Wall"},
	{18028,"cj_bar2","gb_nastybar04", 0,"Old wood"},
	{18028,"cj_bar2","gb_nastybar01", 0,"Wood (grav)"},
	{18028,"cj_bar2","cj_nastybar_d5", 0,"Sun"},
	{18028,"cj_bar2","cj_nastybar_d6", 0,"S.W.A.T."},
	{18028,"cj_bar2","cj_nastybar_d", 0,"Girl"},
	{18028,"cj_bar2","cj_nastybar_d3", 0,"Diablo"},
	{18028,"cj_bar2","cj_nastybar_d2", 0,"Girl and 2 mask"},
	{18028,"cj_bar2","cj_nastybar_d4", 0,"Jesus Saves"},
	{18028,"cj_bar2","gb_nastybar09", 0,"Torn skin"},
	{18028,"cj_bar2","gb_nastybar13", 0,"Window from bar"},
	{18028,"cj_bar2","gb_nastybar15", 0,"Door Staff Only"},
	{18028,"cj_bar2","gb_nastybar08", 0,"Light board"},
	{1730,"cj_furniture","cj_wood5", 0,"Dark wood"},
	{3853,"gay_xref","ws_gayflag1", 0,"Rainbow"},
	{18018,"genintintbarb","gb_midbar01", 0,"Brick wall"},
	{2635,"pizza_furn","cj_tart_table", 0,"Cloth"},
	{14771,"int_brothelint3","gb_midbar15", 0,"Asphalt"} ,
	{14771,"int_brothelint3","gb_midbar10", 0,"Outerspace"},
	{14777,"int_casinoint3","gb_midbar11", 0,"Grunge Bamboo"},
	{13675,"lahillsgrounds","bevpool", 0,"Pool equipment"},
	{13761,"lahills_whisky","discharger", 0,"Poster Discharger"},
	{2817,"gb_bedrmrugs01","gb_rugbedroom01", 0,"Carpet"},
	{14802,"lee_bdupsflat","usaflag", 0,"Flag USA"},
	{14808,"lee_strip2","strip_ceiling", 0,"Marble tiles"},
	{14832,"lee_stripclub","cl_floornew_256", 0,"Dancefloor"},
	{14832,"lee_stripclub","mirror_ref1", 0,"Purple curtains"},
	{14832,"lee_stripclub","strip_bar_wall1", 0,"Purple walls"},
	{14832,"lee_stripclub","strip_ladydoor", 0,"Curtains Do Not Enter"},
	{14832,"lee_stripclub","strip_neon4", 0,"Fire outbreak"},
	{14832,"lee_stripclub","strip_plant", 0,"Palm leaf"},
	{14407,"carter_block","zebra_skin", 0,"Zebra skin"}
};

new SelectedMenu[MAX_PLAYERS],
	SelectedBox[MAX_PLAYERS],
	SelectedList[MAX_PLAYERS];

enum MenuParams
{
	Float:MenuRotation,
	Boxes,
	bool:IsExist,
	Objects[MAX_BOXES],
	Float:OrigPosX[MAX_BOXES],
	Float:OrigPosY[MAX_BOXES],
	Float:OrigPosZ[MAX_BOXES],
	Float:AddingX,
	Float:AddingY,
	SelectColor[MAX_BOXES],
	UnselectColor[MAX_BOXES],
	menuPlayer,
	Lists
}

new MenuInfo[MAX_3DMENUS][MenuParams];

//Callbacks
forward OnPlayerSelect3DMenuBox(playerid,MenuID,boxid,list,boxes);
forward OnPlayerChange3DMenuBox(playerid,MenuID,boxid,list,boxes);

// Create a new menu
stock Create3DMenu(playerid,Float:x,Float:y,Float:z,Float:rotation,boxes)
{
	// Make sure box is in range
	if(boxes > MAX_BOXES || boxes <= 0) return -1;

	// Create 3D Menu
	for(new i = 0; i < MAX_3DMENUS; i++)
	{
		// Menu exists continue
	    if(MenuInfo[i][IsExist]) continue;

     	new Float:NextLineX,Float:NextLineY;
      	new lineindx,binc;

       	MenuInfo[i][MenuRotation] = rotation;
		MenuInfo[i][Boxes] = boxes;
		MenuInfo[i][AddingX] = 0.25*floatsin(rotation,degrees);
		MenuInfo[i][AddingY] = -floatcos(rotation,degrees)*0.25;
		
		MenuInfo[i][Lists] = MAX_LISTS;
		
		NextLineX = floatcos(rotation,degrees)+0.05*floatcos(rotation,degrees);
		NextLineY = floatsin(rotation,degrees)+0.05*floatsin(rotation,degrees);
		
		MenuInfo[i][IsExist] = true;
		MenuInfo[i][menuPlayer] = playerid;
		
		// Create menu objects
		for(new b = 0; b < boxes; b++)
		{
  			if(b%4 == 0 && b != 0) lineindx++,binc+=4;
   			MenuInfo[i][Objects][b] = CreateDynamicObject(2661,x+NextLineX*lineindx,y+NextLineY*lineindx,z+1.65-0.55*(b-binc),0,0,rotation,-1,-1,playerid,100.0);
      		GetDynamicObjectPos(MenuInfo[i][Objects][b],MenuInfo[i][OrigPosX][b],MenuInfo[i][OrigPosY][b],MenuInfo[i][OrigPosZ][b]);
			SetBoxMaterial(i, b, 0, ObjectTextures[b][TModel], ObjectTextures[b][TXDName], ObjectTextures[b][TextureName], 0, 0);
		}
		Streamer_Update(playerid);
		return i;
	}
	return -1;
}

stock SetBoxMaterial(MenuID,box,index,model,const txd[],const texture[], selectcolor = 0, unselectcolor = 0)
{
	if(!MenuInfo[MenuID][IsExist]) return -1;
	if(box == MenuInfo[MenuID][Boxes] || box < 0) return -1;
	if(MenuInfo[MenuID][Objects][box] == INVALID_OBJECT_ID) return -1;
	MenuInfo[MenuID][SelectColor][box] = selectcolor;
	MenuInfo[MenuID][UnselectColor][box] = unselectcolor;
	if(SelectedBox[MenuInfo[MenuID][menuPlayer]] == box) SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][box], index, model, txd, texture, selectcolor);
	else SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][box], index, model, txd, texture, unselectcolor);
	return 1;
}

stock Select3DMenu(playerid,MenuID)
{
	if(!IsPlayerConnected(playerid)) return -1;
	if(!MenuInfo[MenuID][IsExist]) return -1;
	if(MenuInfo[MenuID][menuPlayer] != playerid) return -1;
	if(SelectedMenu[playerid] != -1) CancelSelect3DMenu(playerid);

	SelectedMenu[playerid] = MenuID;
	
	new model,txd[32],texture[32], color;
	GetDynamicObjectMaterial(MenuInfo[MenuID][Objects][0],0,model, txd, texture, color);
 	SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][0],0, model, txd, texture, MenuInfo[MenuID][SelectColor][0]);

 	MoveDynamicObject(MenuInfo[MenuID][Objects][0],MenuInfo[MenuID][OrigPosX][0]+MenuInfo[MenuID][AddingX],MenuInfo[MenuID][OrigPosY][0]+MenuInfo[MenuID][AddingY],MenuInfo[MenuID][OrigPosZ][0],1.0);
	return 1;
}

public OnGameModeInit()
{
	for(new i = 0; i < MAX_3DMENUS; i++)
	{
	    for(new b = 0; b < MAX_BOXES; b++) MenuInfo[i][Objects][b] = INVALID_OBJECT_ID;
	    MenuInfo[i][Boxes] = 0;
	    MenuInfo[i][IsExist] = false;
	    MenuInfo[i][AddingX] = 0.0;
 	    MenuInfo[i][AddingY] = 0.0;
 	    MenuInfo[i][menuPlayer] = -1;
	}
	#if defined hook_OnGameModeInit
        hook_OnGameModeInit();
    	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
#undef OnGameModeInit  
#else 
#define _ALS_OnGameModeInit 
#endif 
#define OnGameModeInit hook_OnGameModeInit

#if defined hook_OnGameModeInit
    forward hook_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
	SelectedList[playerid] = 0;
    SelectedMenu[playerid] = -1;
	SelectedBox[playerid] = 0;
	#if defined hook_OnPlayerConnect
        hook_OnPlayerConnect(playerid);
    	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
#undef OnPlayerConnect  
#else 
#define _ALS_OnPlayerConnect 
#endif 
#define OnPlayerConnect hook_OnPlayerConnect

#if defined hook_OnPlayerConnect
    forward hook_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid,reason)
{
    if(SelectedMenu[playerid] != -1) CancelSelect3DMenu(playerid);
#if defined hook_OnPlayerDisconnect
    hook_OnPlayerDisconnect(playerid,reason);
#endif
    return 1;
}

#if defined _ALS_OnPlayerDisconnect
#undef OnPlayerDisconnect
#else 
#define _ALS_OnPlayerDisconnect 
#endif 
#define OnPlayerDisconnect hook_OnPlayerDisconnect

#if defined hook_OnPlayerDisconnect
    forward hook_OnPlayerDisconnect(playerid,reason);
#endif

public OnPlayerKeyStateChange(playerid,newkeys,oldkeys)
{
	if(SelectedMenu[playerid] != -1)
	{
		new MenuID = SelectedMenu[playerid];

		/*if(OnPlayerKeyStateChangeMenu(playerid,newkeys,oldkeys)) return 1;*/


	    if(newkeys == KEY_NO)
	    {
			new model,txd[32],texture[32], color;
			GetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0,model, txd, texture, color);
		 	SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0, model, txd, texture, MenuInfo[MenuID][UnselectColor][SelectedBox[playerid]]);

			MoveDynamicObject(MenuInfo[MenuID][Objects][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosX][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosY][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosZ][SelectedBox[playerid]],1.0);
			SelectedBox[playerid]++;

			if(SelectedBox[playerid] == MenuInfo[MenuID][Boxes])
			{
				SelectedList[playerid] ++;
				if(SelectedList[playerid] > MenuInfo[MenuID][Lists]) SelectedList[playerid] = 0;
				new tid = SelectedList[playerid] * MenuInfo[MenuID][Boxes];
				
				SelectedBox[playerid] = 0;
				for(new b = 0; b < MenuInfo[MenuID][Boxes]; b++)
				{
					SetBoxMaterial(MenuID, b, 0, ObjectTextures[tid + b][TModel], ObjectTextures[tid + b][TXDName], ObjectTextures[tid +b][TextureName], 0, 0);
				}
			}
						
			GetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0,model, txd, texture, color);
		 	SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0, model, txd, texture, MenuInfo[MenuID][SelectColor][SelectedBox[playerid]]);

			MoveDynamicObject(MenuInfo[MenuID][Objects][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosX][SelectedBox[playerid]]+MenuInfo[MenuID][AddingX],MenuInfo[MenuID][OrigPosY][SelectedBox[playerid]]+MenuInfo[MenuID][AddingY],MenuInfo[MenuID][OrigPosZ][SelectedBox[playerid]],1.0);

		}
		if(newkeys == KEY_YES)
	    {
			new model,txd[32],texture[32], color;
			GetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0,model, txd, texture, color);
		 	SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0, model, txd, texture, MenuInfo[MenuID][UnselectColor][SelectedBox[playerid]]);

	        MoveDynamicObject(MenuInfo[MenuID][Objects][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosX][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosY][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosZ][SelectedBox[playerid]],1.0);
			SelectedBox[playerid]--;
			if(SelectedBox[playerid] < 0) 
			{
				SelectedList[playerid] --;
				if(SelectedList[playerid] < 0) SelectedList[playerid] = MenuInfo[MenuID][Lists];
				new tid = SelectedList[playerid] * MenuInfo[MenuID][Boxes];
				
				SelectedBox[playerid] = MenuInfo[MenuID][Boxes]-1;
				for(new b = 0; b < MenuInfo[MenuID][Boxes]; b++)
				{
					SetBoxMaterial(MenuID, b, 0, ObjectTextures[tid + b][TModel], ObjectTextures[tid + b][TXDName], ObjectTextures[tid +b][TextureName], 0, 0);
				}
			}
			
			GetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0,model, txd, texture, color);
		 	SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0, model, txd, texture, MenuInfo[MenuID][SelectColor][SelectedBox[playerid]]);

			MoveDynamicObject(MenuInfo[MenuID][Objects][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosX][SelectedBox[playerid]]+MenuInfo[MenuID][AddingX],MenuInfo[MenuID][OrigPosY][SelectedBox[playerid]]+MenuInfo[MenuID][AddingY],MenuInfo[MenuID][OrigPosZ][SelectedBox[playerid]],1.0);
		}
		

		if(newkeys == KEY_NO || newkeys == KEY_YES) if(funcidx("OnPlayerChange3DMenuBox") != -1) CallRemoteFunction("OnPlayerChange3DMenuBox","ddddd",playerid,MenuID,SelectedBox[playerid],SelectedList[playerid],MenuInfo[MenuID][Boxes]);
		if(newkeys == KEY_SPRINT) if(funcidx("OnPlayerSelect3DMenuBox") != -1) CallRemoteFunction("OnPlayerSelect3DMenuBox","ddddd",playerid,MenuID,SelectedBox[playerid],SelectedList[playerid],MenuInfo[MenuID][Boxes]);
	}
	#if defined hook_OnPlayerKeyStateChange
        hook_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
    	#endif
	return 1;
}

#if defined _ALS_OnPlayerKeyStateChange 
#undef OnPlayerKeyStateChange  
#else 
#define _ALS_OnPlayerKeyStateChange 
#endif 
#define OnPlayerKeyStateChange hook_OnPlayerKeyStateChange

#if defined hook_OnPlayerKeyStateChange
    forward hook_OnPlayerKeyStateChange(playerid,newkeys,oldkeys);
#endif

stock CancelSelect3DMenu(playerid)
{
	if(!IsPlayerConnected(playerid)) return -1;
	if(SelectedMenu[playerid] == -1) return -1;
	new MenuID = SelectedMenu[playerid];

	new model,txd[32],texture[32], color;
	GetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0,model, txd, texture, color);
 	SetDynamicObjectMaterial(MenuInfo[MenuID][Objects][SelectedBox[playerid]],0, model, txd, texture, MenuInfo[MenuID][UnselectColor][SelectedBox[playerid]]);


	MoveDynamicObject(MenuInfo[MenuID][Objects][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosX][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosY][SelectedBox[playerid]],MenuInfo[MenuID][OrigPosZ][SelectedBox[playerid]],1.0);
	SelectedMenu[playerid] = -1;
	return 1;
}

stock Destroy3DMenu(MenuID)
{
    if(!MenuInfo[MenuID][IsExist]) return -1;
    if(SelectedMenu[MenuInfo[MenuID][menuPlayer]] == MenuID) CancelSelect3DMenu(MenuInfo[MenuID][menuPlayer]);
    for(new i = 0; i < MenuInfo[MenuID][Boxes]; i++)
    {
		DestroyDynamicObject(MenuInfo[MenuID][Objects][i]);
		MenuInfo[MenuID][Objects][i] = INVALID_OBJECT_ID;
	}
 	MenuInfo[MenuID][Boxes] = 0;
	MenuInfo[MenuID][Lists] = 0;
 	MenuInfo[MenuID][IsExist] = false;
 	MenuInfo[MenuID][AddingX] = 0.0;
 	MenuInfo[MenuID][AddingY] = 0.0;
 	MenuInfo[MenuID][menuPlayer] = -1;
	return 1;
}
