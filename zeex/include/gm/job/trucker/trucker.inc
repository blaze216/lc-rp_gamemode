Trucker_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT * FROM `truck_cargo`", "LoadDynamicTruckCargo");
}

Ship_Init()
{
    ship_docked = 1;
    ship_arrived = gettime();
	ship_depart = gettime() + 2400;
	ship_next = gettime() + 2400 + 340;

    obj_lamp[0] = CreateDynamicObject(19123, 2810.646240, -2390.074218, 13.175701, 0.000000, 0.000000, 0.000000, 0, 0);
	obj_lamp[1] = CreateDynamicObject(19123, 2810.652832, -2381.859375, 13.175693, 0.000000, 0.000000, 0.000000, 0, 0);
	obj_lamp[2] = CreateDynamicObject(19123, 2810.635986, -2394.476562, 13.195693, 0.000000, 0.000000, 0.000000, 0, 0);
	obj_lamp[3] = CreateDynamicObject(19123, 2810.634765, -2386.070800, 13.185685, 0.000000, 0.000000, 0.000000, 0, 0);
	obj_lamp[4] = CreateDynamicObject(19123, 2810.649414, -2431.452880, 13.195693, 0.000000, 0.000007, 0.000000, 0, 0);
	obj_lamp[5] = CreateDynamicObject(19123, 2810.649414, -2444.330322, 13.195693, 0.000000, 0.000007, 0.000000, 0, 0);
	obj_lamp[6] = CreateDynamicObject(19123, 2810.649414, -2439.667724, 13.195693, 0.000000, 0.000007, 0.000000, 0, 0);
	obj_lamp[7] = CreateDynamicObject(19123, 2810.649414, -2435.664306, 13.195693, 0.000000, 0.000007, 0.000000, 0, 0);
	
	obj_gate[0] = CreateDynamicObject(3069, 2811.04248, -2391.13989, 12.62090,   -15.00000, 0.00000, -90.00000, 0, 0);
	obj_gate[1] = CreateDynamicObject(3069, 2811.04248, -2385.13550, 12.62090,   -15.00000, 0.00000, -90.00000, 0, 0);
	obj_gate[2] = CreateDynamicObject(3069, 2811.04248, -2441.09058, 12.62090,   -15.00000, 0.00000, -90.00000, 0, 0);
	obj_gate[3] = CreateDynamicObject(3069, 2811.04248, -2435.13501, 12.62090,   -15.00000, 0.00000, -90.00000, 0, 0);


    obj_ship[0] = CreateDynamicObject(-21954, 1162.099975, -1135.086059, 40.820243, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    obj_ship[1]= CreateDynamicObject(2939, 1210.698730, -1099.750610, 30.940843, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    obj_ship[2] = CreateDynamicObject(2939, 1210.698730, -1105.350463, 33.412845, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    obj_ship[3] = CreateDynamicObject(2939, 1210.698730, -1110.950561, 35.852832, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 	
	obj_ship[4] = CreateDynamicObject(5155, 2838.02344, -2358.47656, 21.31250,   0.00000, 0.00000, 270.00000, 0, 0);
	obj_ship[5] = CreateDynamicObject(5158, 2837.77344, -2334.47656, 11.99220,   0.00000, 0.00000, 0.00000, 0, 0);
	obj_ship[6] = CreateDynamicObject(3724, 2838.19531, -2407.14063, 29.31250,   0.00000, 0.00000, 270.00000, 0, 0);
	obj_ship[7] = CreateDynamicObject(3724, 2838.19531, -2488.66406, 29.31250,   0.00000, 0.00000, 270.00000, 0, 0);
	obj_ship[8] = CreateDynamicObject(5336, 2829.95313, -2479.57031, 5.26560,   0.00000, 0.00000, 0.00000, 0, 0);
	obj_ship[9] = CreateDynamicObject(5156, 2838.03906, -2423.88281, 10.96094,   0.00000, 0.00000, 270.00000, 0, 0);
	obj_ship[10] = CreateDynamicObject(5154, 2838.14063, -2447.84375, 15.75000,   0.00000, 0.00000, 270.00000, 0, 0);

	time_truck = 3600;
	return 1;
}

Ship_OnDynamicObjectMoved(objectid)
{
	if (objectid == obj_ship[0] && ship_docked == 3)
    {
	    ship_docked = 1;
        
		new Float: ox, Float: oy, Float: oz;

		for(new i; i != MAX_TRUCK_CARGO; i++)
	    {
	        if (i < 8)	Streamer_SetIntData(STREAMER_TYPE_OBJECT, obj_lamp[i], E_STREAMER_MODEL_ID, 19123);
	            
	        if (i < 4)
	        {
	            GetDynamicObjectPos(obj_gate[i], ox, oy, oz);
	        	MoveDynamicObject(obj_gate[i], ox + 10.0, oy, oz, 1.5);
	        }

	        if (TruckCargo[i][tOn] == 0 || TruckCargo[i][tType] != 2) continue;

			Streamer_SetIntData(STREAMER_TYPE_3D_TEXT_LABEL, TruckCargo[i][tLabel], E_STREAMER_INTERIOR_ID, 0);
       		Streamer_SetIntData(STREAMER_TYPE_PICKUP, TruckCargo[i][tPickup], E_STREAMER_INTERIOR_ID, 0);
		}
	}

	if (objectid == obj_ship[0] && ship_docked == 2) ship_docked = 0;
		
	return 1;
}