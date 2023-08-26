//LIST OF VEHICLE SELLS
new a_class_model[] = { //4-х дверные и Роскошные машины
	445,507,585,466,492,546,
	551,516,467,426,547,405,580,
	409,550,566,540,421,529,402,
	603
};

new b_class_model[] = { //2-х дверные и Компактные машины
	475,542,602,496,401,518,527,
	589,419,587,533,526,474,
	517,410,600,436,439,549,491
};

new lowride_class_model[] = { // Лоурайдеры
	536, 575, 534, 567, 535, 576, 412
};

new pickups_class_model[] = { //Пикапы и Фургоны
	422,482,/*530,*/418,/*572,*/
	413,440,543,/*583,*/478,554
};

new offroad_model[] = //Внедорожники и Универсалы
	{579, 400, 404, 489, 479, 442, 458};
	
new sport_model[] = { // Спортивные
	429, 415, 480, 562, 565, 559, 561,
	560, 506, 558, 555, 602, 603
};

new industrial_model[] = 
	{413, 414, 420, 
	423, 431, 437, 438, 
	455, 456, 498, 499, 
	525, 588, 514, 515};

new motobike_model[] = 
	{461, 462, 463, 468, 471, 521, 581, 
	586};
	
new boat_model[] =
	{446, 453, 454, 473, 484, 493};

new fly_model[] =
	{469, 487, 460, 512, 519, 593};

new other_model[] =
	{457, 483, 508, 500};

new donate_model[] = 
	{568, 495, 541, 411, 522,
	451, 477};


//OTHER
enum DEALERSHIP
{
	cCarModel,
	cCarPrice,
	Float:cCarCompFuel,
	Float:cCarFuelUsage
}

// model, price, fuel capacity, fuel usage
//static const 
new Float:vehicles_info[][DEALERSHIP] = {
	{409, 200000, 100.0, 6.0}, // Stretch					//A-Class 
	{421, 30000, 80.0, 6.0}, // Washington
	{426, 35000, 70.0, 5.0}, // Premier
	{480, 160000, 60.0, 5.0}, // Comet
	{507, 25000, 85.0, 6.0}, // Elegant
	{533, 60000, 60.0, 7.0}, // Feltzer
	{551, 20000, 80.0, 5.0}, // Merit
	{555, 58000, 80.0, 6.0}, // Windsor
	{560, 100000, 60.0, 9.0}, // Sultan
	{580, 90000, 80.0, 5.0}, // Stafford  					//A-Class
	{401, 10000, 60.0, 5.0}, // Bravura						//B-Class
	{405, 40000, 80.0, 5.0}, // Sentinel
	{410, 5000, 50.0, 5.0}, // Manana
	{419, 18000, 60.0, 5.0}, // Esperanto
	{436, 12000, 50.0, 5.0}, // Previon
	{439, 30000, 60.0, 5.0}, // Stallion
	{445, 28000, 80.0, 5.0}, // Admiral
	{458, 15000, 80.0, 5.0}, // Solair
	{466, 20000, 70.0, 6.0}, // Glendale
	{467, 17500, 70.0, 5.0}, // Oceanic
	{482, 26500, 130.0, 8.0}, // Burrito
	{491, 11500, 80.0, 6.0}, // Virgo
	{492, 9000, 70.0, 6.0}, // Greenwood
	{496, 65000, 80.0, 5.0}, // Blista Compact
	{516, 11500, 70.0, 5.0}, // Nebula
	{517, 17000, 70.0, 5.0}, // Majestic
	{518, 26000, 60.0, 5.0}, // Buccaneer
	{526, 20000, 70.0, 5.0}, // Fortune
	{527, 12500, 60.0, 5.0}, // Cadrona
	{529, 15000, 80.0, 6.0}, // Willard
	{534, 32000, 60.0, 5.0}, // Remington
	{535, 30500, 80.0, 8.0}, // Slamvan
	{536, 36000, 60.0, 5.0}, // Blade
	{540, 11000, 70.0, 5.0}, // Vincent
	{546, 9500, 60.0, 5.0}, // Intruder
	{547, 8500, 70.0, 5.0}, // Primo
	{550, 10000, 80.0, 5.0}, // Sunrise
	{561, 15000, 60.0, 8.0}, // Stratum
	{566, 17750, 80.0, 5.0}, // Tahoma
	{567, 33000, 60.0, 5.0}, // Savanna
	{575, 18000, 60.0, 5.0}, // Broadway
	{585, 20000, 80.0, 7.0}, // Emperor
	{589, 30000, 60.0, 6.0}, // Club 				//B-Class
	{404, 9000, 60.0, 5.0}, // Perennial				//С-Class
	{412, 28000, 60.0, 5.0}, // Voodoo
	{418, 5500, 90.0, 5.0}, // Moonbeam
	{474, 19750, 60.0, 5.0}, // Hermes
	{475, 35000, 80.0, 6.0}, // Sabre
	{479, 10000, 80.0, 5.0}, // Regina
	{542, 24000, 70.0, 5.0}, // Clover
	{543, 7500, 90.0, 5.0}, // Sadler
	{549, 15000, 80.0, 5.0}, // Tampa
	{576, 22500, 65.0, 5.0}, // Tornado
	{600, 8500, 90.0, 5.0}, // Picador
	{402, 75000, 60.0, 7.0}, // Buffalo 					//Sport
	{411, 1000000, 60.0, 10.0}, // Infernus
	{429, 200000, 55.0, 9.0}, // Banshee
	{451, 700000, 60.0, 9.0}, // Turismo
	{477, 120000, 60.0, 8.0}, // ZR-350
	{506, 300000, 55.0, 8.0}, // Super GT
	{541, 600000, 50.0, 10.0}, // Bullet
	{558, 50000, 60.0, 5.0}, // Uranus
	{559, 55000, 60.0, 7.0}, // Jester
	{562, 150000, 60.0, 9.0}, // Elegy
	{565, 50000, 60.0, 6.0}, // Flash
	{587, 30000, 60.0, 7.0}, // Euros
	{602, 40000, 60.0, 8.0}, // Alpha
	{415, 650000, 60.0, 9.0}, // Cheetah
	{603, 90000, 60.0, 8.0}, // Phoenix 				//Sport
	{400, 32500, 100.0, 7.0}, // Landstalker 			//Off-Road
	{489, 60000, 110.0, 7.0}, // Rancher
	{495, 60000, 110.0, 7.0}, // Sandking
	{500, 26000, 100.0, 6.0}, // Mesa
	{554, 30000, 100.0, 5.0}, // Yosemite
	{579, 80000, 100.0, 8.0}, // Huntley				//Off-Road
	{461, 18000, 50.0, 8.0}, // PCJ-600					//MotoBike
	{462, 2000, 50.0, 4.0}, // Faggio
	{463, 13500, 60.0, 6.0}, // Freeway
	{468, 8000, 50.0, 5.0}, // Sanchez
	{471, 5000, 40.0, 4.0}, // Quad
	{521, 35000, 55.0, 8.0}, // FCR-900
	{522, 300000, 50.0, 10.0}, // NRG-500
	{581, 16000, 50.0, 8.0}, // BF-400
	{586, 14000, 60.0, 5.0}, // Wayfarer
	{423, 8500, 80.0, 5.0}, // Mr. Whoopee				//Industrial
	{413, 22500, 130.0, 6.0}, // Pony
	{414, 20000, 100.0, 6.0}, // Mule
	{420, 12000, 70.0, 5.0}, // Taxi
	{422, 10000, 105.0, 6.0}, // Bobcat
	{431, 27000, 160.0, 9.0}, // Bus
	{437, 32500, 165.0, 8.0}, // Coach
	{438, 6500, 70.0, 5.0}, // Cabbie
	{440, 20000, 135.0, 7.0}, // Rumpo
	{455, 40000, 165.0, 8.0}, // Flatbed
	{456, 35000, 165.0, 8.0}, // Yankee
	{478, 10700, 105.0, 5.0}, // Walton
	{498, 19400, 165.0, 7.0}, // Boxville
	{499, 19900, 165.0, 7.0}, // Benson
	{525, 15000, 60.0, 5.0}, // Towtruck
	{406, 350000, 300.0, 20.0}, // Dumper
	{514, 48000, 170.0, 10.0}, // Tanker
	{515, 38000, 170.0, 10.0}, // Roadtrain
	{588, 6000, 60.0, 5.0}, // Hotdog			//Industrial
	{442, 12000, 90.0, 5.0}, // Romero
	{457, 8400, 30.0, 4.0}, // Caddy
	{483, 9500, 60.0, 6.0}, // Camper
	{508, 15000, 80.0, 8.0}, // Journey
	{568, 61500, 50.0, 9.0}, // Bandito			//Other
	{446, 100000, 170.0, 5.0}, // Squallo			//Boats
	{453, 30000, 200.0, 6.0}, // Reefer
	{454, 150000, 190.0, 8.0}, // Tropic
	{473, 5500, 150.0, 5.0}, // Dinghy
	{484, 180000, 170.0, 5.0}, // Marquis
	{493, 120000, 180.0, 10.0}, // Jetmax			//Boats
	{487, 300000, 230.0, 8.0}, // Maverick
	{460, 250000, 400.0, 10.0}, // Skimmer
	{519, 2000000, 350.0, 9.0}, // Shamal
	{593, 280000, 260.0, 7.0} //Dodo 			//Air vehicle

	//Beagle
	//Stuntplane
	//Dune
	//=====
	//Kart
};
	
stock GetVehiclePrice(model)
{
	for(new i = 0; i < sizeof(vehicles_info); i++)
	{
		if (model == vehicles_info[i][cCarModel])
			return vehicles_info[i][cCarPrice];
	}
	return 0;
}

stock Float:GetVehicleFuelCapacity(model)
{
	for(new i = 0; i < sizeof(vehicles_info); i++)
	{
		if (model == vehicles_info[i][cCarModel])
			return vehicles_info[i][cCarCompFuel];
	}
	
	return 60.0;
}

stock Float:GetVehicleFuelUsage(model)
{
	for(new i = 0; i < sizeof(vehicles_info); i++)
	{
		if (model == vehicles_info[i][cCarModel])
			return vehicles_info[i][cCarFuelUsage];
	}
	return 6.0;
}

stock Float:GetVehicleMaxHealth(modelid)
{
	new Float:vvalue = 0.0;

	switch(modelid)
	{
		case 462, 463, 521, 522, 581, 586, 461: vvalue = 750.0;
		case 468, 471: vvalue = 700.0;
		case 481, 509, 510: vvalue = 1000.0;
		case 439, 480, 533, 555: vvalue = 650.0;
		case 549, 604, 605: vvalue = 600.0;
		default: vvalue = 750.0;
	}

	return vvalue;
}

stock IsADonateModel(model)
{
	for(new i = 0; i < sizeof(donate_model); i++)
		if (donate_model[i] == model)
			return true;
	return false;
}