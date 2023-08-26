this::LoadStreet()
{
	new rows = cache_num_rows(), time = GetTickCount(), total;

	if (!rows)
	{
	    print("[Streets] Kayit bulunamadi.");
	    return 1;
	}

	for(new i; i < rows; i++)
	{
        cache_get_value_int(i, "id", street_data[i][street_id]);
        cache_get_value_float(i, "stX", street_data[i][sSign][0]);
        cache_get_value_float(i, "stY", street_data[i][sSign][1]);
        cache_get_value_float(i, "stZ", street_data[i][sSign][2]);
        cache_get_value_float(i, "stRX", street_data[i][sSign][3]);
        cache_get_value_float(i, "stRY", street_data[i][sSign][4]);
        cache_get_value_float(i, "stRZ", street_data[i][sSign][5]);
        cache_get_value_float(i, "dX", street_data[i][sDirection][0]);
        cache_get_value_float(i, "dY", street_data[i][sDirection][1]);
        cache_get_value_float(i, "dZ", street_data[i][sDirection][2]);
        cache_get_value_float(i, "drX", street_data[i][sDirection][3]);
        cache_get_value_float(i, "drY", street_data[i][sDirection][4]);
        cache_get_value_float(i, "drZ", street_data[i][sDirection][5]);
        cache_get_value_float(i, "nX", street_data[i][sName][0]);
        cache_get_value_float(i, "nY", street_data[i][sName][1]);
        cache_get_value_float(i, "nZ", street_data[i][sName][2]);
        cache_get_value_float(i, "nrX", street_data[i][sName][3]);
        cache_get_value_float(i, "nrY", street_data[i][sName][4]);
        cache_get_value_float(i, "nrZ", street_data[i][sName][5]);

		cache_get_value(i, "street", street_data[i][street_name], 32);
		cache_get_value(i, "dir", street_data[i][street_direction], 20);

		SetUpSignCords(i, street_data[i][sSign][0], street_data[i][sSign][1], street_data[i][sSign][2], street_data[i][sSign][3], street_data[i][sSign][4], street_data[i][sSign][5]);
		//Final_StreetLoad(i);
		total++;
	}

    printf("[Streets] Satir - %i. Yuklenen - %i. Sure: %i ms.", rows, total, GetTickCount()-time);
	return true;
}

Direction(Float: angle, dest[], size = sizeof dest) {
    while(angle >= 348.75) angle -= 360.0;
    while(angle < -11.25) angle += 360.0;

    static const direction[][] = {
        "CENTRAL   ",
        "NORTH WEST",
        "WEST NORTH",
        "WEST      ",
        "CENTRAL   ",
        "SOUTH WEST",
        "SOUTH WEST",
        "SOUTH     ",
        "CENTRAL   ",
        "SOUTH EAST",
        "EAST SOUTH",
        "EAST      ",
        "CENTRAL   ",
        "EAST NORTH",
        "NORTH EAST",
        "NORTH     "
    };
    return strcat((dest[0] = EOS, dest), direction[floatround((angle + 11.25) / 22.5, floatround_floor)], size);
}

Float: GetZAngle(Float: X1, Float: Y1, Float: X2, Float: Y2) {
    return -atan2(X2 - X1, Y2 - Y1); // From Point 1 to Point 2
}

returnAngel(playerid, Float:x, Float:y, dest[], size = sizeof dest) {
    new
        Float: player_x,
        Float: player_y,
        Float: z;

    if (GetPlayerPos(playerid, player_x, player_y, z)) return Direction(GetZAngle(player_x, player_y, x, y), dest, size);
    
    return 0;
} 

stock street_free_slot() {
	for(new S = 0; S < MAX_STREET; S++) if (street_data[S][street_id] == 0) return S;
	return -1;
}

this::Create_Street(playerid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{	
	new areas[5], street_area[2], j = GetNumberDynamicAreasForPoint(x,y,z);
	GetDynamicAreasForPoint(x, y, z, areas, sizeof(areas));
	if (!GetStreet(areas, j, street_area)) return SendErrorMessage(playerid, "Bu bölgede belirlenmiþ sokak yok!");
	
	pTemp[playerid][editPos][0] = x;
	pTemp[playerid][editPos][1] = y;
	pTemp[playerid][editPos][2] = z;
	pTemp[playerid][editPos][3] = rx;
	pTemp[playerid][editPos][4] = ry;
	pTemp[playerid][editPos][5] = rz;

	new dlg[80];
	if (street_area[0] != -1) format(dlg, sizeof(dlg), "1. %s\n", street_names[street_area[0]]);
	if (street_area[1] != -1) format(dlg, sizeof(dlg), "%s2. %s", dlg, street_names[street_area[1]]);
	
	Dialog_Show(playerid, Select_Street, DIALOG_STYLE_LIST,"{FFFFFF}Sokak seçimi", dlg, ">>>", "");
	return 1;
} //î

Dialog:Select_Street(playerid, response, listitem, inputtext[])
{
	new Float:x = pTemp[playerid][editPos][0], 
		Float:y = pTemp[playerid][editPos][1], 
		Float:z = pTemp[playerid][editPos][2], 
		Float:rx = pTemp[playerid][editPos][3], 
		Float:ry = pTemp[playerid][editPos][4], 
		Float:rz = pTemp[playerid][editPos][5];

	for(new i; i<6; i++) pTemp[playerid][editPos][i] = 0.0;

	new areas[10], street_area[2], j = GetNumberDynamicAreasForPoint(x,y,z);
	GetDynamicAreasForPoint(x, y, z, areas, sizeof(areas));
	if (!GetStreet(areas, j, street_area)) return SendErrorMessage(playerid, "Bu bölgede belirlenmiþ sokak yok!");

	new id = street_free_slot();
	if (id == -1) return SendErrorMessage(playerid, "Sokak tabelalarýnýn sýnýrý aþýldý!");

	new direction[12];
	returnAngel(playerid, x, y, direction, sizeof(direction));

	format(street_data[id][street_direction], 20, "%d %s", 1000+id, direction);
	format(street_data[id][street_name], 32, "%s", street_names[street_area[listitem]]);

	SetUpSignCords(id, x, y, z, rx, ry, rz);
	
	new query[526];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `streets` (street,dir,stX,stY,stZ,stRX,stRY,stRZ,nX,nY,nZ,nrX,nrY,nrZ,dX,dY,dZ,drX,drY,drZ) VALUES ('%e','%e',%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f)", 
		street_names[street_area[listitem]], street_data[id][street_direction], 
		x, y, z, rx, ry, rz,
		street_data[id][sName][0],street_data[id][sName][1],street_data[id][sName][2],street_data[id][sName][3],street_data[id][sName][4],street_data[id][sName][5],
		street_data[id][sDirection][0],street_data[id][sDirection][1],street_data[id][sDirection][2],street_data[id][sDirection][3],street_data[id][sDirection][4],street_data[id][sDirection][5]
	);
	mysql_tquery(dbHandle, query, "OnStreetInsert", "d", id);

	SendHelpMessage(playerid, "Baþarýyla bir sign oluþturuldu, düzenlemek için: /stname %i ve /stdir %i", id, id);
	return 1;
}

this::OnStreetInsert(id)
{
	return street_data[id][street_id] = cache_insert_id(); 
}

this::Save_Street(id)
{
	new query[156];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `streets` SET stX=%f,stY=%f,stZ=%f,stRX=%f,stRY=%f,stRZ=%f WHERE id=%i", 
		street_data[id][sSign][0],street_data[id][sSign][1],street_data[id][sSign][2],
		street_data[id][sSign][3],street_data[id][sSign][4],street_data[id][sSign][5],
		street_data[id][street_id]
	);
    mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `streets` SET nX=%f,nY=%f,nZ=%f,nrX=%f,nrY=%f,nrZ=%f WHERE id=%i", 
		street_data[id][sName][0],street_data[id][sName][1],street_data[id][sName][2],
		street_data[id][sName][3],street_data[id][sName][4],street_data[id][sName][5],
		street_data[id][street_id]
	);
    mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `streets` SET dX=%f,dY=%f,dZ=%f,drX=%f,drY=%f,drZ=%f WHERE id=%i", 
		street_data[id][sDirection][0],street_data[id][sDirection][1],street_data[id][sDirection][2],
		street_data[id][sDirection][3],street_data[id][sDirection][4],street_data[id][sDirection][5],
		street_data[id][street_id]
	);
    mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `streets` SET dir='%e' WHERE id=%i", street_data[id][street_direction], street_data[id][street_id]);
    mysql_tquery(dbHandle, query);
	return 1;
}

DeleteStreet(playerid, id)
{
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `streets` WHERE `id`=%i", street_data[id][street_id]);
	mysql_tquery(dbHandle, query);

	street_data[id][street_id] = 0;

	if (IsValidDynamicObject(street_data[id][street_object][0])) DestroyDynamicObject(street_data[id][street_object][0]);
	if (IsValidDynamicObject(street_data[id][street_object][1])) DestroyDynamicObject(street_data[id][street_object][1]);
	if (IsValidDynamicObject(street_data[id][street_object][2])) DestroyDynamicObject(street_data[id][street_object][2]);

	for(new i; i < 6; i++) {
		street_data[id][sName][i] = 0.0;
		street_data[id][sSign][i] = 0.0;
		street_data[id][sDirection][i] = 0.0;
	}

	street_data[id][street_name] = EOS;
	street_data[id][street_direction] = EOS;


	SendSyntaxMessage(playerid, "Sokak etiketi baþarýyla silindi. [ID:%i]", id);
	return 1;
}

SetUpSignCords(id, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	// direction x-0.150833 y-0.035949 z+2.720012
	// street    x+0.002197 y-0.025947 z+2.630009

	street_data[id][sSign][0] = x;
	street_data[id][sSign][1] = y;
	street_data[id][sSign][2] = z;
	street_data[id][sSign][3] = rx;
	street_data[id][sSign][4] = ry;
	street_data[id][sSign][5] = rz;
	street_data[id][sDirection][0] = x-0.150833; //+0.64917  
	street_data[id][sDirection][1] = y-0.025947; //-0.03595  
	street_data[id][sDirection][2] = z+2.720012; //+1.750012
	street_data[id][sDirection][3] = rx;
	street_data[id][sDirection][4] = ry;
	street_data[id][sDirection][5] = rz+90;
	street_data[id][sName][0] = x+0.002197; //-0.647827
	street_data[id][sName][1] = y-0.025947; //-0.03595
	street_data[id][sName][2] = z+2.630009; //+1.690008
	street_data[id][sName][3] = rx;
	street_data[id][sName][4] = ry;
	street_data[id][sName][5] = rz+90;

	Final_StreetLoad(id);
	return 1;
}

Final_StreetLoad(id) {
	if (IsValidDynamicObject(street_data[id][street_object][0])) DestroyDynamicObject(street_data[id][street_object][0]);
	if (IsValidDynamicObject(street_data[id][street_object][1])) DestroyDynamicObject(street_data[id][street_object][1]);
	if (IsValidDynamicObject(street_data[id][street_object][2])) DestroyDynamicObject(street_data[id][street_object][2]);

	street_data[id][street_object][0] = CreateDynamicObject(19981, street_data[id][sSign][0], street_data[id][sSign][1], street_data[id][sSign][2], street_data[id][sSign][3], street_data[id][sSign][4], street_data[id][sSign][5], -1, -1, -1, 300.00, 300.00);
	street_data[id][street_object][2] = CreateDynamicObject(18659, street_data[id][sDirection][0], street_data[id][sDirection][1], street_data[id][sDirection][2], street_data[id][sDirection][3], street_data[id][sName][4], street_data[id][sDirection][5], -1, -1, -1, 300.00, 300.00);
	street_data[id][street_object][1] = CreateDynamicObject(18659, street_data[id][sName][0], street_data[id][sName][1], street_data[id][sName][2], street_data[id][sName][3], street_data[id][sName][4], street_data[id][sName][5], -1, -1, -1, 300.00, 300.00);

	SetDynamicObjectMaterialText(street_data[id][street_object][2], 0, street_data[id][street_direction], 140, "Calibri", 16, 1, 0xFFFFFFFF, 0x00000000,1);// 0);
	SetDynamicObjectMaterialText(street_data[id][street_object][1], 0, street_data[id][street_name], 140, "Calibri", 25, 1, 0xFFFFFFFF, 0x00000000, 1);//2);

	Save_Street(id);
}

GetStreetID(playerid, Float: radius = 2.0)
{
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
	
    for(new i = 0; i != MAX_STREET; i++)
    {
        if (IsPlayerInRangeOfPoint(playerid, radius, street_data[i][sSign][0], street_data[i][sSign][1], street_data[i][sSign][2]))
        {
			return i;
        }
    }
    return -1;
}

GetStreet(areas_id[], amount, streets[], size = sizeof(streets))
{
	for(new i; i < size; i++) streets[i] = -1;

	new count;
	for(new s; s < amount; s ++) {
		for(new i; i < sizeof(street_names); i++) {
			if (IsValidDynamicArea(areas_id[s]) && areas_id[s] == street_zones[i]) {
				streets[count] = i;
				count++;
				if (count == size) break;
			}
		}
	}

	if (count) 	return 1;
	else 		return 0;
}


	//GetGroupCenter(x, y, z);
	//x = pTemp[playerid][editPos][0] + (x - pTemp[playerid][editPos][3]);
	//y = pTemp[playerid][editPos][1] + (y - pTemp[playerid][editPos][4]);
	//z = pTemp[playerid][editPos][2] + (z - pTemp[playerid][editPos][5]);

 // 			x			y			z
	//SING: 1370.981323, 271.397369, 19.566932
	//DIRECTION: x+0.64917, y-0.03595, z+1.750012, 0.000000, 0.000000, 90
	//STREETNAME: x-0.647827, y-0.049591, z+1.690008, 0.000000, 0.000000, 90

/*GetGroupCenter(&Float:x, &Float:y, &Float:z)
{
	new Float:highX = -9999999.0;
	new Float:highY = -9999999.0;
	new Float:highZ = -9999999.0;

	new Float:lowX  = 9999999.0;
	new Float:lowY  = 9999999.0;
	new Float:lowZ  = 9999999.0;

	if (x > highX) 	highX = x;
	if (y > highY) 	highY = y;
	if (z > highZ) 	highZ = z;
	if (x < lowX) 	lowX = x;
	if (y < lowY) 	lowY = y;
	if (z < lowZ) 	lowZ = z;

	if (x-0.150833 > highX) 	highX = x-0.150833; //sDirection
	if (y-0.025947 > highY) 	highY = y-0.025947;
	if (z+2.720012 > highZ) 	highZ = z+2.720012;
	if (x-0.150833 < lowX) 	lowX = x-0.150833;
	if (y-0.025947 < lowY) 	lowY = y-0.025947;
	if (z+2.720012 < lowZ) 	lowZ = z+2.720012;

	if (x-0.647827 > highX) 	highX = x-0.647827; //sNAME
	if (y-0.025947 > highY) 	highY = y-0.025947;
	if (z+2.630009 > highZ) 	highZ = z+2.630009;
	if (x-0.647827 < lowX) 	lowX = x-0.647827;
	if (y-0.025947 < lowY) 	lowY = y-0.025947;
	if (z+2.630009 < lowZ) 	lowZ = z+2.630009;

	x = (highX + lowX) / 2;
	y = (highY + lowY) / 2;
	z = (highZ + lowZ) / 2;

	return 1;
}*/

//	street_data[id][sDirection][0] = x-0.150833; //+0.64917  
//	street_data[id][sDirection][1] = y-0.025947; //-0.03595  
//	street_data[id][sDirection][2] = z+2.720012; //+1.750012
//	street_data[id][sName][0] = x+0.002197; //-0.647827
//	street_data[id][sName][1] = y-0.025947; //-0.03595
//	street_data[id][sName][2] = z+2.630009; //+1.690008