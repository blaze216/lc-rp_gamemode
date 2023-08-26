Street_OnGameModeInit()
{
	street_zones[0] = CreateDynamicPolygon(zones_points_0);
	street_zones[1] = CreateDynamicPolygon(zones_points_1);
	street_zones[2] = CreateDynamicPolygon(zones_points_2);
	street_zones[3] = CreateDynamicPolygon(zones_points_3);
	street_zones[4] = CreateDynamicPolygon(zones_points_4);
	street_zones[5] = CreateDynamicPolygon(zones_points_5);
	street_zones[6] = CreateDynamicPolygon(zones_points_6);
	street_zones[7] = CreateDynamicPolygon(zones_points_7);
	street_zones[8] = CreateDynamicPolygon(zones_points_8);
	street_zones[9] = CreateDynamicPolygon(zones_points_9);
	street_zones[10] = CreateDynamicPolygon(zones_points_10);
	street_zones[11] = CreateDynamicPolygon(zones_points_11);
	street_zones[12] = CreateDynamicPolygon(zones_points_12);
	street_zones[13] = CreateDynamicPolygon(zones_points_13);
	street_zones[14] = CreateDynamicPolygon(zones_points_14);
	street_zones[15] = CreateDynamicPolygon(zones_points_15);
	street_zones[16] = CreateDynamicPolygon(zones_points_16);
	street_zones[17] = CreateDynamicPolygon(zones_points_17);
	street_zones[18] = CreateDynamicPolygon(zones_points_18);
	street_zones[19] = CreateDynamicPolygon(zones_points_19);
	street_zones[20] = CreateDynamicPolygon(zones_points_20);
	street_zones[21] = CreateDynamicPolygon(zones_points_21);
	street_zones[22] = CreateDynamicPolygon(zones_points_22);
	street_zones[23] = CreateDynamicPolygon(zones_points_23);
	street_zones[24] = CreateDynamicPolygon(zones_points_24);
	street_zones[25] = CreateDynamicPolygon(zones_points_25);
	street_zones[26] = CreateDynamicPolygon(zones_points_26);
	street_zones[27] = CreateDynamicPolygon(zones_points_27);
	street_zones[28] = CreateDynamicPolygon(zones_points_28);
	street_zones[29] = CreateDynamicPolygon(zones_points_29);
	street_zones[30] = CreateDynamicPolygon(zones_points_30);
	street_zones[31] = CreateDynamicPolygon(zones_points_31);
	street_zones[32] = CreateDynamicPolygon(zones_points_32);
	street_zones[33] = CreateDynamicPolygon(zones_points_33);
	street_zones[34] = CreateDynamicPolygon(zones_points_34);
	street_zones[35] = CreateDynamicPolygon(zones_points_35);
	street_zones[36] = CreateDynamicPolygon(zones_points_36);
	street_zones[37] = CreateDynamicPolygon(zones_points_37);
	street_zones[38] = CreateDynamicPolygon(zones_points_38);
	street_zones[39] = CreateDynamicPolygon(zones_points_39);
	street_zones[40] = CreateDynamicPolygon(zones_points_40);
	street_zones[41] = CreateDynamicPolygon(zones_points_41);
	street_zones[42] = CreateDynamicPolygon(zones_points_42);
	street_zones[43] = CreateDynamicPolygon(zones_points_43);
	street_zones[44] = CreateDynamicPolygon(zones_points_44);
	street_zones[45] = CreateDynamicPolygon(zones_points_45);
	street_zones[46] = CreateDynamicPolygon(zones_points_46);
	street_zones[47] = CreateDynamicPolygon(zones_points_47);
	street_zones[48] = CreateDynamicPolygon(zones_points_48);
	street_zones[49] = CreateDynamicPolygon(zones_points_49);
	street_zones[50] = CreateDynamicPolygon(zones_points_50);
	street_zones[51] = CreateDynamicPolygon(zones_points_51);
	street_zones[52] = CreateDynamicPolygon(zones_points_52);
	street_zones[53] = CreateDynamicPolygon(zones_points_53);
	street_zones[54] = CreateDynamicPolygon(zones_points_54);
	street_zones[55] = CreateDynamicPolygon(zones_points_55);
	street_zones[56] = CreateDynamicPolygon(zones_points_56);
	street_zones[57] = CreateDynamicPolygon(zones_points_57);
	street_zones[58] = CreateDynamicPolygon(zones_points_58);

	mysql_tquery(dbHandle, "SELECT * FROM `streets`", "LoadStreet");
}

St_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (response == EDIT_RESPONSE_FINAL)
	{
		if (GetPVarInt(playerid, #edit_street) == 1) 		DestroyDynamicObject(objectid);
		else if (GetPVarInt(playerid, #edit_street) == 2) 	DeleteStreet(playerid, GetPVarInt(playerid, #id_street));
		else if (GetPVarInt(playerid, #edit_street) == 3) 
		{
			SetDynamicObjectPos(objectid, x, y, z);
			SetDynamicObjectRot(objectid, rx, ry, rz);

			Save_Street(GetPVarInt(playerid, #id_street));
			DeletePVar(playerid, #id_street);
			return 1;
		}

		DeletePVar(playerid, #id_street);
		DeletePVar(playerid, #edit_street);

		Create_Street(playerid, x, y, z, rx, ry, rz);
	}
	if (response == EDIT_RESPONSE_CANCEL)
	{
		if (GetPVarInt(playerid, #edit_street) == 1) {
			DestroyDynamicObject(objectid);
		}
		else if (GetPVarInt(playerid, #edit_street) > 1) {		
			new Float:oldX, Float:oldY, Float:oldZ,
				Float:oldRotX, Float:oldRotY, Float:oldRotZ;
				
			GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
				
			SetDynamicObjectPos(objectid, oldX, oldY, oldZ);
			SetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);
		}

		DeletePVar(playerid, #id_street);
		DeletePVar(playerid, #edit_street);
	}
	return 1;
}