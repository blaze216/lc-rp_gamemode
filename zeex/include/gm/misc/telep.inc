enum OR_TELEPORTS_DATA
{
	tele_id,
	tele_name[32],
	Float:tele_x,
	Float:tele_y,
	Float:tele_z,
	tele_int,
}
new OrTeleports[110][OR_TELEPORTS_DATA] = 
{
	{0, "24/7 1", -25.884498, -185.868988, 1003.546875, 17},
	{1, "24/7 2", 6.091179, -29.271898, 1003.549438, 10},
	{2, "24/7 3", -30.946699, -89.609596, 1003.546875, 18},
	{3, "24/7 4", -25.132598, -139.066986, 1003.546875, 16},
	{4, "24/7 5", -27.312299, -29.277599, 1003.557250, 4},
	{5, "24/7 6", -26.691598, -55.714897, 1003.546875, 6},
	{6, "Airport Ticket Desk", -1827.147338, 7.207417, 1061.143554, 14},
	{7, "Airport Baggage Reclaim", -1861.936889, 54.908092, 1061.143554, 14},
	{8, "Shamal", 1.808619, 32.384357, 1199.593750, 1},
	{9, "Andromada", 315.745086, 984.969299, 1958.919067, 9},
	{10, "Ammunation 1", 286.148986, -40.644397, 1001.515625, 1},
	{11, "Ammunation 2", 286.800994, -82.547599, 1001.515625, 4},
	{12, "Ammunation 3", 296.919982, -108.071998, 1001.515625, 6},
	{13, "Ammunation 4", 314.820983, -141.431991, 999.601562, 7},
	{14, "Ammunation 5", 316.524993, -167.706985, 999.593750, 6},
	{15, "Ammunation Booths", 302.292877, -143.139099, 1004.062500, 7},
	{16, "Ammunation Range", 298.507934, -141.647048, 1004.054748, 7},
	{17, "Blastin Fools Hallway", 1038.531372, 0.111030, 1001.284484, 3},
	{18, "Budget Inn Motel Room", 444.646911, 508.239044, 1001.419494, 12},
	{19, "Jefferson Motel", 2215.454833, -1147.475585, 1025.796875, 15},
	{20, "Off Track Betting Shop", 833.269775, 10.588416, 1004.179687, 3},
	{21, "Sex Shop", -103.559165, -24.225606, 1000.718750, 3},
	{22, "Meat Factory", 963.418762, 2108.292480, 1011.030273, 1},
	{23, "Zero's RC Shop", -2240.468505, 137.060440, 1035.414062, 6},
	{24, "Dillimore Gas Station", 663.836242, -575.605407, 16.343263, 0},
	{25, "Caligula's Basement", 2169.461181, 1618.798339, 999.976562, 1},
	{26, "FDC Janitors Room", 1889.953369, 1017.438293, 31.882812, 10},
	{27, "Woozie's Office", -2159.122802, 641.517517, 1052.381713, 1},
	{28, "Binco", 207.737991, -109.019996, 1005.132812, 15},
	{29, "Didier Sachs", 204.332992, -166.694992, 1000.523437, 14},
	{30, "Prolaps", 207.054992, -138.804992, 1003.507812, 3},
	{31, "Suburban", 203.777999, -48.492397, 1001.804687, 1},
	{32, "Victim", 226.293991, -7.431529, 1002.210937, 5},
	{33, "ZIP", 161.391006, -93.159156, 1001.804687, 18},
	{34, "Alhambra", 493.390991, -22.722799, 1000.679687, 17},
	{35, "Ten Green Bottles", 501.980987, -69.150199, 998.757812, 11},
	{36, "Lil' Probe Inn", -227.027999, 1401.229980, 27.765625, 18},
	{37, "Jay's Dinner", 457.304748, -88.428497, 999.554687, 4},
	{38, "Gant Bridge Dinner", 454.973937, -110.104995, 1000.077209, 5},
	{39, "Secret Valley Dinner", 435.271331, -80.958938, 999.554687, 4},
	{40, "World of Coq", 452.489990, -18.179698, 1001.132812, 1},
	{41, "Welcome Pump", 681.557861, -455.680053, -25.609874, 1},
	{42, "Burger Shot", 375.962463, -65.816848, 1001.507812, 10},
	{43, "Cluckin' Bell", 369.579528, -4.487294, 1001.858886, 9},
	{44, "Well Stacked Pizza", 373.825653, -117.270904, 1001.499511, 5},
	{45, "Jimmy's Sticky Ring", 381.169189, -188.803024, 1000.632812, 17},
	{46, "Denise Room", 244.411987, 305.032989, 999.148437, 1},
	{47, "Katie Room", 271.884979, 306.631988, 999.148437, 2},
	{48, "Helena Room", 291.282989, 310.031982, 999.148437, 3},
	{49, "Michelle Room", 302.180999, 300.722991, 999.148437, 4},
	{50, "Barbara Room", 322.197998, 302.497985, 999.148437, 5},
	{51, "Millie Room", 346.870025, 309.259033, 999.155700, 6},
	{52, "Sherman Dam", -959.564392, 1848.576782, 9.000000, 17},
	{53, "Planning Dept.", 384.808624, 173.804992, 1008.382812, 3},
	{54, "Area 51", 223.431976, 1872.400268, 13.734375, 0},
	{55, "LS Gym", 772.111999, -3.898649, 1000.728820, 5},
	{56, "SF Gym", 774.213989, -48.924297, 1000.585937, 6},
	{57, "LV Gym", 773.579956, -77.096694, 1000.655029, 7},
	{58, "B Dup's House", 1527.229980, -11.574499, 1002.097106, 3},
	{59, "B Dup's Crack Pad", 1523.509887, -47.821197, 1002.130981, 2},
	{60, "CJ's House", 2496.049804, -1695.238159, 1014.742187, 3},
	{61, "Madd Dogg's Mansion", 1267.663208, -781.323242, 1091.906250, 5},
	{62, "OG Loc's House", 513.882507, -11.269994, 1001.565307, 3},
	{63, "Ryder's House", 2454.717041, -1700.871582, 1013.515197, 2},
	{64, "Sweet's House", 2527.654052, -1679.388305, 1015.498596, 1},
	{65, "Crack Factory", 2543.462646, -1308.379882, 1026.728393, 2},
	{66, "Big Spread Ranch", 1212.019897, -28.663099, 1000.953125, 3},
	{67, "Fanny Batters", 761.412963, 1440.191650, 1102.703125, 6},
	{68, "Strip Club", 1204.809936, -11.586799, 1000.921875, 2},
	{69, "Strip Club Private Room", 1204.809936, 13.897239, 1000.921875, 2},
	{70, "Unnamed Brothel", 942.171997, -16.542755, 1000.929687, 3},
	{71, "Tiger Skin Brothel", 964.106994, -53.205497, 1001.124572, 3},
	{72, "Pleasure Domes", -2640.762939, 1406.682006, 906.460937, 3},
	{73, "Liberty City Outside", -729.276000, 503.086944, 1371.971801, 1},
	{74, "Liberty City Inside", -794.806396, 497.738037, 1376.195312, 1},
	{75, "Gang House", 2350.339843, -1181.649902, 1027.976562, 5},
	{76, "Colonel Furhberger's House", 2807.619873, -1171.899902, 1025.570312, 8},
	{77, "Crack Den", 318.564971, 1118.209960, 1083.882812, 5},
	{78, "Warehouse 1", 1412.639892, -1.787510, 1000.924377, 1},
	{79, "Warehouse 2", 1302.519897, -1.787510, 1001.028259, 18},
	{80, "Sweet's Garage", 2522.000000, -1673.383911, 14.866223, 0},
	{81, "Lil' Probe Inn Toilet", -221.059051, 1408.984008, 27.773437, 18},
	{82, "Unused Safe House", 2324.419921, -1145.568359, 1050.710083, 12},
	{83, "RC Battlefield", -975.975708, 1060.983032, 1345.671875, 10},
	{84, "Barber 1", 411.625976, -21.433298, 1001.804687, 2},
	{85, "Barber 2", 418.652984, -82.639793, 1001.804687, 3},
	{86, "Barber 3", 412.021972, -52.649898, 1001.898437, 12},
	{87, "Tatoo Parlour 1", -204.439987, -26.453998, 1002.273437, 16},
	{88, "Tatoo Parlour 2", -204.439987, -8.469599, 1002.273437, 17},
	{89, "Tatoo Parlour 3", -204.439987, -43.652496, 1002.273437, 3},
	{90, "LS Police HQ", 246.783996, 63.900199, 1003.640625, 6},
	{91, "SF Police HQ", 246.375991, 109.245994, 1003.218750, 10},
	{92, "LV Police HQ", 288.745971, 169.350997, 1007.171875, 3},
	{93, "Car School", -2029.798339, -106.675910, 1035.171875, 3},
	{94, "8-Track", -1398.065307, -217.028900, 1051.115844, 7},
	{95, "Bloodbowl", -1398.103515, 937.631164, 1036.479125, 15},
	{96, "Dirt Track", -1444.645507, -664.526000, 1053.572998,  4},
	{97, "Kickstart", -1465.268676, 1557.868286, 1052.531250, 14},
	{98, "Vice Stadium", -1401.829956, 107.051300, 1032.273437, 1},
	{99, "SF Garage", -1790.378295, 1436.949829, 7.187500, 0},
	{100, "LS Garage", 1643.839843, -1514.819580, 13.566620, 0},
	{101, "SF Bomb Shop", -1685.636474, 1035.476196, 45.210937, 0},
	{102, "Blueberry Warehouse", 76.632553, -301.156829, 1.578125, 0},
	{103, "LV Warehouse 1", 1059.895996, 2081.685791, 10.820312, 0},
	{104, "LV Warehouse 2", 1059.180175, 2148.938720, 10.820312, 0},
	{105, "Caligula's Hidden Room", 2131.507812, 1600.818481, 1008.359375, 1},
	{106, "Bank", 2315.952880, -1.618174, 26.742187, 0},
	{107, "Bank - Behind Desk", 2319.714843, -14.838361, 26.749565, 0},
	{108, "LS Atrium", 1710.433715, -1669.379272, 20.225049, 18},
	{109, "Bike School", 1494.325195, 1304.942871, 1093.289062, 3}
};

forward OnTeleportInsert(playerid, teleid);

this::LoadDynamicTeles()
{
    new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows)
	{
	    print("[Isinlanma] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
	    cache_get_value_int(i, "id", AdminTeles[i][aID]);
		cache_get_value(i, "mapname", AdminTeles[i][telesMapName], 32);
		cache_get_value_float(i, "posx", AdminTeles[i][telesPosX]);
		cache_get_value_float(i, "posy", AdminTeles[i][telesPosY]);
		cache_get_value_float(i, "posz", AdminTeles[i][telesPosZ]);
		cache_get_value_int(i, "interior", AdminTeles[i][telesInt]);
		cache_get_value_int(i, "type", AdminTeles[i][telesType]);

		AdminTeles[i][telesOn] = 1;
        total++;
	}
	printf("[Isinlanma] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return 1;
}

public OnTeleportInsert(playerid, teleid)
{
	AdminTeles[teleid][aID] = cache_insert_id();
	return 1;
}

AddTeleToFile(playerid, teleid, mapname[], interior, Float:x, Float:y, Float:z, type)
{
    new query[128 + 128];
	mysql_format(dbHandle,query, sizeof(query), "INSERT INTO `ateles` (mapname, posx, posy, posz, interior, type) VALUES ('%e', %f, %f, %f, %i, %i)", mapname, x, y, z, interior, type);
	mysql_tquery(dbHandle, query, "OnTeleportInsert", "dd", playerid, teleid);
	return 1;
}

Dialog:Teles(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	SetPlayerPosEx(playerid, OrTeleports[listitem][tele_x], OrTeleports[listitem][tele_y], OrTeleports[listitem][tele_z]);
	SetInterior(playerid, OrTeleports[listitem][tele_int]);
	SendSyntaxMessage(playerid, "Iþýnlandýnýz -> {FFFFFF}%s", OrTeleports[listitem][tele_name]);
	return 1;
}

Dialog:AdminTeles(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new	min_tp = pTemp[playerid][pDialogList] * MAX_ADMIN_TELES,
		max_tp = (pTemp[playerid][pDialogList]+1) * MAX_ADMIN_TELES;
		
	if (pTemp[playerid][pDialogList] && listitem == 0) 	pTemp[playerid][pDialogList]--;
	else if (AdminTeles[max_tp][telesOn] && (
			(listitem == MAX_ADMIN_TELES+1 && pTemp[playerid][pDialogList]) || 
			(listitem == MAX_ADMIN_TELES && !pTemp[playerid][pDialogList])
	))													pTemp[playerid][pDialogList]++;
	
	else {
		listitem = listitem + pTemp[playerid][pDialogList] * MAX_ADMIN_TELES;
		if (pTemp[playerid][pDialogList]) listitem--;

		SetPlayerPosEx(playerid, AdminTeles[listitem][telesPosX], AdminTeles[listitem][telesPosY], AdminTeles[listitem][telesPosZ]);
		SetInterior(playerid, AdminTeles[listitem][telesInt]);
	}

	min_tp = pTemp[playerid][pDialogList] * MAX_ADMIN_TELES;
	max_tp = (pTemp[playerid][pDialogList]+1) * MAX_ADMIN_TELES;

	new string[4096];
	if (pTemp[playerid][pDialogList]) string="{bccd32}Önceki sayfa{FFFFFF}";

	for(new i = min_tp; i < max_tp; i++)
	{
		if (!AdminTeles[i][telesOn]) continue;
		format(string, sizeof(string), "%s\n<%i>{66FF66}%s", string, i, AdminTeles[i][telesMapName]);
	}

	if (AdminTeles[max_tp][telesOn]) format(string, sizeof(string), "%s\n{bccd32}Ýlerle", string);

	Dialog_Show(playerid, AdminTeles, DIALOG_STYLE_LIST,"{FFFFFF}Iþýnlanma", string, ">>>", "Kapat");

	
	return 1;
}

Tele_OnGameModeInit()
{
	return mysql_tquery(dbHandle, "SELECT * FROM `ateles`", "LoadDynamicTeles");
}