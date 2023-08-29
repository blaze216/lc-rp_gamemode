//native IsValidVehicle(vehicleid);
/*Internal*/
static BWH_memset(variable[], cells, value) // Slice - http://forum.sa-mp.com/showpost.php?p=1974747
{
	new address;

	#emit LOAD.S.pri  variable
	#emit STOR.S.pri  address

	BWH_raw_memset(address, cells, value);
}

static BWH_raw_memset(address, cells, value) // Slice - http://forum.sa-mp.com/showpost.php?p=1974747
{
	new param_adr;

	#emit LCTRL       6
	#emit MOVE.alt
	#emit LCTRL       0
	#emit ADD
	#emit MOVE.alt
	#emit LCTRL       1
	#emit SUB.alt
	#emit ADD.C       92
	#emit STOR.S.pri  param_adr
	#emit LOAD.S.pri  cells
	#emit SHL.C.pri   2
	#emit SREF.S.pri  param_adr

	#emit LOAD.S.alt  address
	#emit LOAD.S.pri  value
	#emit FILL        0
}

stock DebugMessage(playerid, message[])
{
    if(pTemp[playerid][pDebugMode] == 0)
        return false;

    if(strlen(message) > 96)
    {
        SendClientMessageEx(playerid, COLOUR_BRIGHTRED, sprintf("[DEBUG]" EMBED_ALTO " %.96s", message));
        SendClientMessageEx(playerid, COLOUR_ALTO, sprintf("... %s", message[96]));
    }

    else
    {
        SendClientMessageEx(playerid, COLOUR_BRIGHTRED, sprintf("[DEBUG]" EMBED_ALTO " %s", message));
    }

    return true;
}

stock Log_Kaydet(const path[], const str[], {Float,_}:...)
{
	static args, start, end, File:file, string[1024];
	if((start = strfind(path, "/")) != -1) {
		strmid(string, path, 0, start + 1);

		if(!fexist(string)) return printf("Girilen log klasörü geçersiz. (%s)", string);
	}
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	file = fopen(path, io_append);

	if(!file)
		return 0;

	if(args > 8)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

		for (end = start + (args - 8); end > start; end -= 4)
		{
        #emit LREF.pri end
        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 1024
		#emit PUSH.C string
		#emit PUSH.C args
		#emit SYSREQ.C format

		fwrite(file, string);
		fwrite(file, "\r\n");
		fclose(file);

		#emit LCTRL 5
		#emit SCTRL 4
		#emit RETN
	}
	fwrite(file, str);
	fwrite(file, "\r\n");
	fclose(file);	
	return 1;
}

stock ConfirmDialog(playerid, caption[], info[], callback[], ...)
{
	new n = numargs(), 		// number of arguments, static + optional
		szParamHash[64];	// variable where the passed arguments will be stored
	for(new arg = 4; arg < n; arg++){	// loop all additional arguments
		format(szParamHash, sizeof(szParamHash), "%s%d|", szParamHash, getarg(arg)); // store them in szParamHash
	}
	SetPVarInt(playerid, "confDialogArgs", n -4);			// store the amount of additional arguments
	SetPVarString(playerid, "confDialCallback", callback);	// store the callback that needs to be called after response
	SetPVarString(playerid, "confDialog_arg", szParamHash);	// store the additional arguments
	
	ShowPlayerDialog(playerid, DIALOG_CONFIRM_SYS, DIALOG_STYLE_MSGBOX, caption, info, ">>>", "Ýptal"); // display the dialog message itself
	
	return 1;
}

stock ConfirmDialog_Response(playerid, response)
{
	new szCallback[33],		// variable to fetch our callback to
		szParamHash[64], 	// variable to check raw compressed argument string
		n,					// variable to fetch the amount of additional arguments
		szForm[12];			// variable to generate the CallLocalFunction() "format" argument
		
	n = GetPVarInt(playerid, "confDialogArgs");	// Fetch the amount of additional arguments
	GetPVarString(playerid, "confDialCallback", szCallback, sizeof(szCallback));	// fetch the callback
	GetPVarString(playerid, "confDialog_arg", szParamHash, sizeof(szParamHash));	// fetch the raw compressed additional arguments
	
	new hashDecoded[12];	// variable to store extracted additional arguments from the ConfirmDialog() generated string
	
	sscanf(szParamHash, "p<|>A<d>(0)[12]", hashDecoded);	// extraction of the additional arguments
	
	new args, 	// amount of cells passed to CallLocalFunction
		addr, 	// pointer address variable for later use
		i;		// i
		
	format(szForm, sizeof(szForm), "dd");	// static parameters for the callback, "playerid" and "response"
	
	#emit ADDR.pri hashDecoded	// get pointer address of the extracted additional arguments
	#emit STOR.S.pri addr		// store the pointer address in variable 'addr'
	if (n){	// if there's any additional arguments
		for(i = addr + ((n-1) * 4); i >= addr; i-=4){ // loops all additional arguments by their addresses
			format(szForm, sizeof(szForm), "%sd", szForm); // adds an aditional specifier to the "format" parameter of CallLocalFunction
			#emit load.s.pri i	// load the argument at the current address
			#emit push.pri		// push it to the CallLocalFunction argument list
			args+=4;			// increase used cell number by 4
		}
	}
	
	
	args+=16;	// preserve 4 more arguments for CallLocalFunction (16 cause 4 args by 4 cells (4*4))
	
	#emit ADDR.pri response				// fetch "response" pointer address to the primary buffer
	#emit push.pri						// push it to the argument list
	
	#emit ADDR.pri playerid				// fetch "playerid" pointer address to the primary buffer
	#emit push.pri						// push it to the argument list
	
	#emit push.adr szForm				// push the szForm ("format") to the argument list by its referenced address
	#emit push.adr szCallback			// push the szCallback (custom callback) to the argument list by its referenced address
	#emit push.s args					// push the amount of arguments
	#emit sysreq.c CallLocalFunction	// call the function
	
	// Clear used data
	#emit LCTRL 4
	#emit LOAD.S.ALT args
	#emit ADD.C 4
	#emit ADD
	#emit SCTRL 4
	
	// Clear used PVars
	DeletePVar(playerid, "confDialCallback");
	DeletePVar(playerid, "confDialog_arg");
	DeletePVar(playerid, "confDialogArgs");
	
	return 1;
}

this::Float:GetDistanceBetweenPoints(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2)
{
    return VectorSize(x1-x2, y1-y2, z1-z2);
}

insert_log(const string[], type, subtype, playerid = 0, secondid = 0)
{
    new query[1524];
	mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `logs` (userid,secondid,text,data,type,subtype) VALUES (%i,%i,'%s','%s',%i,%i)", 
	playerid, secondid, string, GetFullDate(), type, subtype);
	mysql_tquery(dbHandle, query);
	return 1;
}

isNumeric(const string[])
{
	new length = strlen(string);
	
	if (length == 0) return 0;

  	for (new i = 0; i < length; i++)
  	{
    	if ((string[i] > '9' || string[i] < '0' && string[i] != '-' && string[i] != '+') || (string[i] == '-' && i != 0) || (string[i] == '+' && i != 0)) return false;
	}
  	
	if (length==1 && (string[0]=='-' || string[0]=='+')) return false;

  	return true;
}

IsAnIP(str[])
{
	if (!str[0] || str[0] == '\1')	return 0;

	for (new i = 0, l = strlen(str); i != l; i ++)
	{
	    if ((str[i] < '0' || str[i] > '9') && str[i] != '.') 				return 0;
	    if (0 < ((i == 0) ? (strval(str)) : (strval(str[i + 1]))) > 255)	return 0;
	}
	return 1;
}

place_color(string[])
{
	for(new i=0; string[i]; i++)
	{
		if (string[i] != '~') continue;

        if (string[i + 7] == '~')
		{
			string[i + 7] = '}';
            string[i] = '{';
		}

		if (string[i + 1] == 'n' && string[i + 2] == '~')
        {
            strdel(string, i, i + 2);
            strins(string, "\n", i, 3);
            strdel(string, i + 1, i + 2);
            strins(string, "", i + 1, 1);
		}
	}
	return 1;
}

strreplace(string[], find, replace)
{
	for(new i=0; string[i]; i++)
	{
		if (string[i] != find) continue;

		string[i] = replace;
	}
	return 1;
}

GetMonthName(month)
{
	new name[32];
	switch(month)
	{
		case 1: format(name,32,"Ocak");
		case 2: format(name,32,"Þubat");
		case 3: format(name,32,"Mart");
		case 4: format(name,32,"Nisan");
		case 5: format(name,32,"Mayýs");
		case 6: format(name,32,"Haziran");
		case 7: format(name,32,"Temmuz");
		case 8: format(name,32,"Aðustos");
		case 9: format(name,32,"Eylül");
		case 10: format(name,32,"Ekim");
		case 11: format(name,32,"Kasým");
		case 12: format(name,32,"Aralýk");
	}
	return name;
}

GetInitials(const string[])
{
	new ret[64], index = 0;

	for (new i = 0, l = strlen(string); i != l; i ++)
	{
	    if (('A' <= string[i] <= 'Z') && (i == 0 || string[i - 1] == ' '))	ret[index++] = string[i];
	}
	return ret;
}

StringHasSymbols(string[])
{
	for(new i = 0; i < strlen(string); i++)
	{
		switch(string[i])
		{
			case '!', '@', '#', '$','%','^','&','*','(',')','_','+','=','|','[',']','{','}','-','.','`','~','<','>','?',',','/': return 1;
			default: continue;
		}
	}
	return 0;
}

CompareStrings(string[], string2[])
{
	return (!strcmp(string, string2, true))?(1):(0);
}

ConvertSecond(time)
{
	new mes[9];

	if (time < 60) format(mes, sizeof(mes), "00:%02i", time);
	else if (time == 60) mes = "01:00";
	else if (time > 60 && time < 3600)
	{
		new Float: minutes = time / 60, seconds = time % 60;

		format(mes, sizeof(mes), "%02.0f:%02i", minutes, seconds);
	}
	else if (time == 3600) mes = "01:00:00";
	else if (time > 3600)
	{
		new Float: hours = time / 3600, minutes_int = time % 3600, Float: minutes = minutes_int / 60, seconds = minutes_int % 60;

		format(mes, sizeof(mes), "%02.0f:%02.0f:%02i", hours, minutes, seconds);
	}
	return mes;
}

FormatNumber(number)
{
	new value[32], length;

	format(value, sizeof(value), "%i", (number < 0) ? (-number) : (number));

	if ((length = strlen(value)) > 3)
	{
		for (new i = length, l = 0; --i >= 0; l ++) 
		{
		    if ((l > 0) && (l % 3 == 0)) strins(value, ",", i + 1);
		}
	}

	if (number < 0)	strins(value, "-", 0);

	return value;
}

GetFullDate()
{
	new date[56], year, month, day, hour, minute, second;

	getdate(year, month, day);
	gettime(hour, minute, second);
	format(date, sizeof(date), "%02d/%02d/%i, %02d:%02d:%02d", day, month, year, hour, minute, second);
	return date;
}

SetCurrentTime()
{
	gettime(server_hour);
	SetWorldTime(server_hour);
	return 1;
}

randomEx(min, max)
{
	new rand = random(max-min)+min;
	return rand;
}

RemoveAlpha(color)
{
    return (color & ~0xFF);
}

ClearChatbox(playerid, lines)
{
	for(new i=0; i<lines; i++)
	{
		SCM(playerid, COLOR_GREY, " ");
	}
	return 1;
}

ClearChatboxForAll(lines)
{
	for(new i=0; i<lines; i++)
	{
		SCMALL(COLOR_GREY, " ");
	}
	return 1;
}

/*
SaveAllPlayers() //ñîõðàíåíèå âñåõ
{
	foreach(new i : Player)
	{
		KickEx(i);
	}
	return 1;
}*/

stock ReplaceText(string[], const search[], const replacement[], bool:ignorecase = false, pos = 0, limit = -1, maxlength = 256)
{
    if(!limit)return 0;

    new sublen = strlen(search),
        replen = strlen(replacement),
        bool:packed = ispacked(string),
        maxlen = maxlength,
        len = strlen(string),
        count = 0;

    if(packed)maxlen *= 4;
    if(!sublen)return 0;

    while(-1 != (pos = strfind(string, search, ignorecase, pos)))
    {
        strdel(string, pos, pos + sublen);
 
        len -= sublen;
 
        if(replen && len + replen < maxlen)
        {
            strins(string, replacement, pos, maxlength);
 
            pos += replen;
            len += replen;
       }
 
        if(limit != -1 && ++count >= limit)break;
   }

    return count;
}

stock TurkishCharFix(info[])
{
    new namefix[256];
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
    format(namefix, sizeof(namefix), info);
    return namefix;
}

stock IsEngineVehicle(vehicleid)
{
    new const g_aengineStatus[] = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
    };
    new modelid;
    modelid = GetVehicleModel(vehicleid);
    if(modelid < 400 || modelid > 611)
        return 0;

    return (g_aengineStatus[modelid - 400]);
}

stock GetPhoneSexName(playerid)
{
    new gender[32] = "", sex = PlayerInfo[playerid][pSex];
	switch(sex)
	{
		case 1: gender = "[E]";
		case 2: gender = "[K]";
	}
	return gender;
}

stock GetSQLHealth(id){
	new Float:health, query[43 + MAX_PLAYER_NAME + 1], Cache:search;

	mysql_format(dbHandle, query, sizeof(query), "SELECT health FROM users WHERE id = '%i'", PlayerInfo[id][pID]);
	search = mysql_query(dbHandle, query);

	if(cache_num_rows()){
		cache_get_value_float(0, "health", health);
	}

	cache_delete(search);
	search = MYSQL_INVALID_CACHE;
	return floatround(health);
}

stock GetSQLArmor(id){
	new Float:armour, query[43 + MAX_PLAYER_NAME + 1], Cache:search;

	mysql_format(dbHandle, query, sizeof(query), "SELECT armour FROM users WHERE id = '%i'", PlayerInfo[id][pID]);
	search = mysql_query(dbHandle, query);

	if(cache_num_rows()){
		cache_get_value_float(0, "armour", armour);
	}

	cache_delete(search);
	search = MYSQL_INVALID_CACHE;
	return floatround(armour);
}

stock GetOriginName(id){
	new originName[32], query[43 + MAX_PLAYER_NAME + 1], Cache:search;

	mysql_format(dbHandle, query, sizeof(query), "SELECT origin FROM origins WHERE id = '%i'", id);
	search = mysql_query(dbHandle, query);

	if(cache_num_rows()){
		cache_get_value(0, "origin", originName, 32);
	}

	cache_delete(search);
	search = MYSQL_INVALID_CACHE;
	return originName;
}

stock GetOriginLangName(id){
	new langoriginName[32], query[43 + MAX_PLAYER_NAME + 1], Cache:search;

	mysql_format(dbHandle, query, sizeof(query), "SELECT langname FROM origins WHERE id = '%i'", id);
	search = mysql_query(dbHandle, query);

	if(cache_num_rows()){
		cache_get_value(0, "langname", langoriginName, 32);
	}

	cache_delete(search);
	search = MYSQL_INVALID_CACHE;
	return langoriginName;
}

public OnOutgoingRPC(playerid, rpcid, BitStream:bs)
{
	switch(rpcid)
	{
		case ORPC_ResetPlayerWeapons: // ResetPlayerWeapons
		{
			BWH_memset(Silah_Bilgi[playerid][sSilahID], 13, 0);
			BWH_memset(Silah_Bilgi[playerid][sMermi], 13, 0);
		}
		case ORPC_GivePlayerWeapon: // GivePlayerWeapon
		{
			new BWH_weaponid, BWH_ammo;

			BS_ReadValue(
				bs,
				PR_UINT32, BWH_weaponid,
				PR_UINT32, BWH_ammo
			);

			if((BWH_weaponid == Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[BWH_weaponid]]) || (SilahSlotuBul[BWH_weaponid] < 6 && SilahSlotuBul[BWH_weaponid] > 2)) // We sum the ammo if weapon is the same or if slot is 3, 4 & 5.
			{
				if(Silah_Bilgi[playerid][sMermi][SilahSlotuBul[BWH_weaponid]] > 0) // If ammo in that slot is above 0, we sum it (Take into account that empty weapons remain in weapon data, so this is actually needed).
				{
					BWH_ammo += Silah_Bilgi[playerid][sMermi][SilahSlotuBul[BWH_weaponid]];
				}
			}

			Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[BWH_weaponid]] = BWH_weaponid;
			Silah_Bilgi[playerid][sMermi][SilahSlotuBul[BWH_weaponid]] = BWH_ammo;

			BS_ResetReadPointer(bs);

			if((BWH_weaponid > 21 && BWH_weaponid < 35) || BWH_weaponid == 38) // Weapons that fire bullets only.
			{
				BS_SetWriteOffset(bs, 32);

				BS_WriteValue(
					bs,
					PR_UINT32, 8000000 // The client ammo doesn't matter. As long as it is not visible in the HUD and doesn't run out, that is good.
				);
			}
		}
		case ORPC_SetPlayerAmmo: // SetPlayerAmmo
		{
			new BWH_weaponid, BWH_ammo;

			BS_ReadValue(
				bs,
				PR_UINT8, BWH_weaponid,
				PR_INT16, BWH_ammo
			);

			if(BWH_ammo > 0 && ((BWH_weaponid > 21 && BWH_weaponid < 35) || BWH_weaponid == 38))
			{
				Silah_Bilgi[playerid][sMermi][SilahSlotuBul[BWH_weaponid]] = BWH_ammo;
				return 0; // Don't allow it to be sent.
			}
			else
			{
				if(BWH_weaponid > 15) // Melee weaps can't be removed by setting their ammo to 0.
				{
					Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[BWH_weaponid]] = 0;
				}
			}

			BS_ResetReadPointer(bs);
		}
	}

	#if defined BWH_OnOutgoingRPC
		return BWH_OnOutgoingRPC(playerid, rpcid, BitStream:bs);
	#else
		return 1;
	#endif
}

public OnIncomingPacket(playerid, packetid, BitStream:bs)
{
	switch(packetid)
	{
		case IPacket_OnFootSync:
		{
			new BWH_OnFootData[PR_OnFootSync];

			BS_IgnoreBits(bs, 8);

			BS_ReadOnFootSync(bs, BWH_OnFootData);
			BS_ResetReadPointer(bs);

			if(BWH_OnFootData[PR_weaponId] != 46 && BWH_OnFootData[PR_weaponId] != 40 && BWH_OnFootData[PR_weaponId] > 0 && Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[BWH_OnFootData[PR_weaponId]]] != BWH_OnFootData[PR_weaponId])
			{
				BS_SetWriteOffset(bs, 8);
				BWH_OnFootData[PR_weaponId] = 0;
				BS_WriteOnFootSync(bs, BWH_OnFootData);
			}

			new Float:OPTUD_w, Float:OPTUD_x, Float:OPTUD_y, Float:OPTUD_z;

			BS_SetReadOffset(bs, 0x98);
			BS_ReadValue(bs, PR_FLOAT, OPTUD_w, PR_FLOAT, OPTUD_x, PR_FLOAT, OPTUD_y, PR_FLOAT, OPTUD_z);
			BS_ResetReadPointer(bs);

			new const Float:OPTUD_angle = atan2(2 * ((OPTUD_y * OPTUD_z) + (OPTUD_w * OPTUD_x)), (OPTUD_w * OPTUD_w) - (OPTUD_x * OPTUD_x) - (OPTUD_y * OPTUD_y) + (OPTUD_z * OPTUD_z));

			if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_NONE)
			{
				if((OPTUD_angle > 85.0 || OPTUD_angle < -85.0) && OPTUD_angle == OPTUD_angle && PlayerInfo[playerid][pAdmin] < 1)
				{
					KickLine(playerid, "Geçersiz Oturum #1");
					return false;
				}
			}
		}
		case IPacket_PassengerSync:
		{
			new BWH_passengerData[PR_PassengerSync];

			BS_IgnoreBits(bs, 8);

			BS_ReadPassengerSync(bs, BWH_passengerData);
			BS_ResetReadPointer(bs);

			if(BWH_passengerData[PR_weaponId] != 46 && BWH_passengerData[PR_weaponId] != 40 && BWH_passengerData[PR_weaponId] > 0 && Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[BWH_passengerData[PR_weaponId]]] != BWH_passengerData[PR_weaponId])
			{
				BS_SetWriteOffset(bs, 8);
				BWH_passengerData[PR_weaponId] = 0;
				BS_WritePassengerSync(bs, BWH_passengerData);
			}
		}
		case IPacket_DriverSync:
		{
			new BWH_inCarData[PR_InCarSync];

			BS_IgnoreBits(bs, 8);

			BS_ReadInCarSync(bs, BWH_inCarData);
			BS_ResetReadPointer(bs);

			if(BWH_inCarData[PR_weaponId] != 46 && BWH_inCarData[PR_weaponId] != 40 && BWH_inCarData[PR_weaponId] > 0 && Silah_Bilgi[playerid][sSilahID][SilahSlotuBul[BWH_inCarData[PR_weaponId]]] != BWH_inCarData[PR_weaponId])
			{
				BS_SetWriteOffset(bs, 8);
				BWH_inCarData[PR_weaponId] = 0;
				BS_WriteInCarSync(bs, BWH_inCarData);
			}
		}		
		case UNOCCUPIED_SYNC:
		{
			new unoccupiedData[PR_UnoccupiedSync];

			BS_IgnoreBits(bs, 8);
			BS_ReadUnoccupiedSync(bs, unoccupiedData);

			if(floatcmp(floatabs(unoccupiedData[PR_roll][0]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_roll][1]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_roll][2]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_direction][0]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_direction][1]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_direction][2]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_position][0]), 20000.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_position][1]), 20000.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_position][2]), 20000.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_angularVelocity][0]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_angularVelocity][1]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_angularVelocity][2]), 1.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_velocity][0]), 100.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_velocity][1]), 100.00000) == 1
				|| floatcmp(floatabs(unoccupiedData[PR_velocity][2]), 100.00000) == 1
			) {
				return false;
			}
		}
		case 206:
		{
	        new bulletData[PR_BulletSync];
	        BS_IgnoreBits(bs, 8);
	        BS_ReadBulletSync(bs, bulletData);
 
	        if(bulletData[PR_hitType] == BULLET_HIT_TYPE_PLAYER)
	        { 
		        new Float: getPlayerX, Float: getPlayerY, Float: getPlayerZ, Float: getLastPlayerZ;
 
		        GetPlayerPos(playerid, getPlayerX, getPlayerY, getPlayerZ);
		        GetPlayerPos(bulletData[PR_hitId], getLastPlayerZ, getLastPlayerZ, getLastPlayerZ);
 
		        new Float:betweenDistance = floatabs(bulletData[PR_origin][0] - getPlayerX) + floatabs(bulletData[PR_origin][1] - getPlayerY);
 
		        if(bulletData[PR_offsets][0] == 0.0 && bulletData[PR_offsets][1] == 0.0 && bulletData[PR_offsets][2] == 0.0 || betweenDistance < 0.15 || floatabs(bulletData[PR_origin][2] - getPlayerZ) < 0.01 || floatabs(getLastPlayerZ - bulletData[PR_hitPos][2]) < 0.01) 
		        { 
			        SCM(playerid, COLOR_LIGHTRED, "(Uyarý): {FFFFFF}Silent Aimbot tespit edildi.");
			        Kick(playerid);
		        } 
	       } 			
		}
		case AIM_SYNC:
		{		
			new aimData[PR_AimSync];

			BS_IgnoreBits(bs, 8);
			BS_ReadAimSync(bs, aimData);

			if(aimData[PR_camMode] == 45 || aimData[PR_camMode] == 49 && PlayerInfo[playerid][pAdmin] < 5)
			{
				Kick(playerid);
				return false;
			}
		}
	}

	#if defined BWH_OnIncomingPacket
		return BWH_OnIncomingPacket(playerid, packetid, bs);
	#else
		return 1;
	#endif
}

public OnIncomingRPC(playerid, rpcid, BitStream:bs)
{
	if(rpcid == 26 && _:bs == 1702096) {
		new vehicleid, passanger;
		BS_ReadUint16(bs, vehicleid);
		BS_ReadUint8(bs, passanger);
		if(passanger == 1) {
			if(vehicleid == -1) return 1;
			if(VehicleInfo[vehicleid][carLocked]) {
				ClearAnimations(playerid, 1);
				SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				return false;
			}
			return 1;
		}
		if(GetVehicleModel(vehicleid) < 400) return 1;
		foreach(new i : Player) 
		    if(IsPlayerInVehicle(i, vehicleid) && !IsPlayerAFK(i) && GetPlayerVehicleSeat(i) == 0 && i != playerid && GetPlayerState(i) == PLAYER_STATE_DRIVER) {
			ClearAnimations(playerid, 1);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			// SetPVarInt(playerid, "AntiCarJack", GetPVarInt(playerid, "AntiCarJack")+1);
			// if(GetPVarInt(playerid, "AntiCarJack") >= 3) KickPlayer(playerid , "LIBERTY", "Carjack"), SendAdminAlert(false, COLOR_ERROR, "%s adlý kullanýcý, Car Jack sebebiyle kicklendi.", GetNameEx(playerid));
			if(PlayerInfo[playerid][pAdmin] > 0) SendServerMessage(playerid, "Aracýn sürücü koltuðunda %s(%d) oturuyor. CJ yapma.", GetNameEx(i), i);
			else SendErrorMessage(playerid, "Carjack yapmak yasak!");
			return false;
		}
	}
	return 1;
}

stock GetPosBehindVehicle(vehicleid, &Float:x, &Float:y, &Float:z, Float:offset=0.5)
{
    new Float:vehicleSize[3], Float:vehiclePos[3];
    GetVehiclePos(vehicleid, vehiclePos[0], vehiclePos[1], vehiclePos[2]);
    GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, vehicleSize[0], vehicleSize[1], vehicleSize[2]);
    GetXYBehindVehicle(vehicleid, vehiclePos[0], vehiclePos[1], (vehicleSize[1]/2)+offset);
    x = vehiclePos[0];
    y = vehiclePos[1];
    z = vehiclePos[2];
    return 1;
}

GetXYBehindVehicle(vehicleid, &Float:q, &Float:w, Float:distance)
{
    new Float:a;
    GetVehiclePos(vehicleid, q, w, a);
    GetVehicleZAngle(vehicleid, a);
    q += (distance * -floatsin(-a, degrees));
    w += (distance * -floatcos(-a, degrees));
}

SilahYapabilirMi(playerid, gunid) {
	new found = 1;
	if(gunid >= 25 && gunid <= 27) {
		for(new i = 30; i < 34; i++) {
			if(AC_PlayerHasWeapon(playerid, i) && AC_PlayerHasAmmo(playerid, i) && i != 32 && i != gunid && GetPVarInt(playerid, "pBeanBag") == 0) {
				found = 0;
				break;
			}
		}
	}
	else if(gunid >= 28 && gunid <= 29 || gunid == 32) {
		for(new i = 30; i < 34; i++) {
			if(AC_PlayerHasWeapon(playerid, i) && AC_PlayerHasAmmo(playerid, i) && i != 32 && i != gunid) {
				found = 0;
				break;
			}
		}
	}
	else if(gunid >= 30 && gunid <= 31) {
		for(new i = 30; i < 34; i++) {
			if(AC_PlayerHasWeapon(playerid, i) && AC_PlayerHasAmmo(playerid, i) && i != 32 && i != gunid) {
				found = 0;
				break;
			}
		}
	}
	else if(gunid >= 33 && gunid <= 34) {
		for(new i = 30; i < 34; i++) {
			if(AC_PlayerHasWeapon(playerid, i) && AC_PlayerHasAmmo(playerid, i) && i != 32 && i != gunid) {
				found = 0;
				break;
			}
		}
	}
	return found;
}

BWH_GetPlayerWeaponData(playerid, slot, &weapon, &ammo)
{
	if(!IsPlayerConnected(playerid) || (slot < 0 || slot > 12))
	{
		return 0;
	}

	GetPlayerWeaponData(playerid, slot, weapon, ammo);

	if(weapon != 46 && weapon != 40)
	{
		weapon = Silah_Bilgi[playerid][sSilahID][slot];
	}

	if((weapon > 21 && weapon < 35) || weapon == 38)
	{
		ammo = Silah_Bilgi[playerid][sMermi][slot];
	}
	return 1;
}

BWH_GetPlayerAmmo(playerid)
{
	if(!IsPlayerConnected(playerid))
	{
		return 0;
	}

	new BWH_weapon = GetPlayerWeapon(playerid);

	if(BWH_weapon) // GetPlayerWeapon will return 0 if the weapon is not given by the server or if it's fists.
	{
		if((BWH_weapon > 21 && BWH_weapon < 35) || BWH_weapon == 38)
		{
			return Silah_Bilgi[playerid][sMermi][SilahSlotuBul[BWH_weapon]];
		}
		else
		{
			return GetPlayerAmmo(playerid);
		}
	}
	return 0;
}

stock AracSilahLimiti(model)
{
	new limit;
	switch(model) 
	{
		case 424, 473, 531: limit = 1;
		case 513, 487, 519: limit = 3;
		case 602, 429, 402, 415, 480, 587, 603, 506, 451, 477, 541, 411, 555, 500: limit = 4;
		case 422, 579, 400, 470, 600, 489, 505, 478, 554, 543, 560, 561, 507, 585, 466, 445, 492, 546, 516, 551, 467, 404, 426, 405, 458, 580, 550, 540, 421, 529, 438, 420: limit = 10;
		case 418: limit = 12;
		case 508, 483: limit = 15;
		case 459, 482, 413, 440, 499, 498, 456, 414, 453, 454, 484: limit = 18;	
		default: limit = 6;
	}
	if(Arac_Model(model) == VEHICLE_TYPE_BIKE) return 0;
	if(Arac_Model(model) == VEHICLE_TYPE_MBIKE) return 1;
	return limit;
}

stock Arac_Sahip(playerid, vehicleid, bool:sahip)
{
	if(!IsValidVehicle(vehicleid)) return 0;
	if(VehicleInfo[vehicleid][carOwnerID] == PlayerInfo[playerid][pID] || pTemp[playerid][pAdminDuty]) return 1;
	if(sahip == false) {
		if(PlayerInfo[playerid][pFaction] == VehicleInfo[vehicleid][carFaction] && VehicleInfo[vehicleid][carFaction] != -1) return 1;
		if(PlayerInfo[playerid][pCarKey] == vehicleid) return 1;
		if(VehicleInfo[vehicleid][carRent] >= 0 && VehicleInfo[vehicleid][carRent] == PlayerInfo[playerid][pID]) return 1;
	}
	return 0;
}

stock Arac_Yakin(playerid, Float:radius = 2.0)
{
	new Float:fX, Float:fY, Float:fZ;
	foreach(new i : Vehicle) if(GetVehicleVirtualWorld(i) == GetPlayerVirtualWorld(playerid)) {
		GetVehiclePos(i, fX, fY, fZ);
		if(!IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ)) continue;
		return i;
	}
	return -1;
}

stock Arac_Model(vehiclemodel)
{
	if(!(0x18F > vehiclemodel < 0x264)) {
		switch(vehiclemodel) {
			case 460,476,511,512,513,519,520,553,577,592,593: return VEHICLE_TYPE_PLANE;
			case 417,425,447,469,487,488,497,548,563: return VEHICLE_TYPE_HELI;
			case 481, 509, 510: return VEHICLE_TYPE_BIKE;
			case 448,461,462,463,468,471,521,522,523,581,586: return VEHICLE_TYPE_MBIKE;
			case 430,446,452,453,454,472,473,484,493,495: return VEHICLE_TYPE_BOAT;
			case 435,450,569,570,584,590,591,606,607,608,610,611: return VEHICLE_TYPE_TRAILER;
			default: return VEHICLE_TYPE_VEHICLE;
		}
	}
	return 0;
}

PlayerAME(playerid, message[])
{
    new string[256];

    format(string,sizeof(string),"> %s %s", GetNameWithMask(playerid), message);
    SendClientMessageEx(playerid, 0xD0AEEBFF,string);
    
    SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);

    return 1;
}

PlayerAME2(playerid, message[])
{
    new string[256];

    format(string,sizeof(string),"> %s %s", GetNameWithMask(playerid), message);
    
    SetPlayerChatBubble(playerid, string, 0xD0AEEBFF, 15.0, 10000);

    return 1;
}

PlayerME(playerid, message[])
{
    pc_cmd_me(playerid, message);
    return 1;
}

SilahSlotBul(weaponid)
{
	new slot = 0;
	switch(weaponid)
	{
		case 2..9: slot = 1;
		case 22..24: slot = 2;
		case 25..27: slot = 3;
		case 28..29: slot = 4;
		case 30..31: slot = 5;
		case 32: slot = 4;
		case 33..34: slot = 6;
	}
	return slot;
}

GetWeaponObjectSlot(weaponid)
{
	new objectslot;

	switch (weaponid)
	{
		case 25..27: objectslot = 6;
		case 28, 29, 32: objectslot = 7;
		case 30, 31: objectslot = 8;
		case 33, 34: objectslot = 9;
	}
	return objectslot;
}

GetWeaponModelEx(weaponid) //Will only return the model of wearable weapons (22-38)
{
	new model;

	switch(weaponid)
	{
		case 22..29: model = 324 + weaponid;
		case 30: model = 355;
		case 31: model = 356;
		case 32: model = 372;
		case 33..38: model = 324 + weaponid;
	}
	return model;
}

forward OnLoadWeapons(playerid);
public OnLoadWeapons(playerid)
{
	new rows, weaponid, index;
	cache_get_row_count(rows);

	if(!rows) return 1;

	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "WeaponID", weaponid);
		index = weaponid - 22;

		cache_get_value_name_float(i, "PosX", WeaponSettings[playerid][index][Position][0]);
		cache_get_value_name_float(i, "PosY", WeaponSettings[playerid][index][Position][1]);
		cache_get_value_name_float(i, "PosZ", WeaponSettings[playerid][index][Position][2]);

		cache_get_value_name_float(i, "RotX", WeaponSettings[playerid][index][Position][3]);
		cache_get_value_name_float(i, "RotY", WeaponSettings[playerid][index][Position][4]);
		cache_get_value_name_float(i, "RotZ", WeaponSettings[playerid][index][Position][5]);

		cache_get_value_name_int(i, "Bone", WeaponSettings[playerid][index][Bone]);
		cache_get_value_name_int(i, "Hidden", WeaponSettings[playerid][index][Hidden]);
		cache_get_value_name_int(i, "duzenlendi", WeaponSettings[playerid][index][duzenlendi]);
	}
	return 1;
}

IsWeaponWearable(weaponid) return (weaponid >= 22 && weaponid <= 38);
IsWeaponHideable(weaponid) return (weaponid >= 22 && weaponid <= 24 || weaponid == 28 || weaponid == 32);

stock vericek_int(row, const field_name[])
{
	static str;
	cache_get_value_name_int(row, field_name, str);
	return str;
}

stock vericek_bool(row, const field_name[])
{
	static bool:test, bool:test2;
	cache_get_value_name_bool(row, field_name, test);
	switch(test) {
		case 1: test2 = true;
		default: test2 = false;
	}
	return test2;
}

stock vericek_varchar(row, const field_name[])
{
	static bilgi[1024];
	cache_get_value_name(row, field_name, bilgi);
	return bilgi;
}

SilahKontrolEt(playerid, targetid, type)
{
	if(PlayerInfo[playerid][pAdmin] || PlayerInfo[playerid][pOnDuty])
	{
		mysql_format(dbHandle, queryx, sizeof(queryx), "SELECT * FROM weapons WHERE owner = '%d'", PlayerInfo[targetid][pID]);
		new Cache:veri = mysql_query(dbHandle, queryx, true);
		new rows;
		cache_get_row_count(rows);

		if(!rows)
		{
			SendErrorMessage(playerid, "%s adlý karaktere kayýtlý ateþli silah bulunamadý. (%s)", GetNameEx(targetid), GetFullDate());
		}
		else
		{
			if(type == 0)
				SendClientMessageEx(playerid, COLOR_GREEN, "__________________________[%s (%s) | %s]__________________________", GetNameEx(targetid), PlayerInfo[targetid][pAccname], GetFullDate());

			new id, weaponid, ammo, status, house, vehicle, biz, olusumid, idstr[6], statusstr[24], omur;

			for(new j; j < rows; j++)
			{
				cache_get_value_int(j, "id", id);
				cache_get_value_int(j, "weaponid", weaponid);
				cache_get_value_int(j, "ammo", ammo);
				cache_get_value_int(j, "status", status);
				cache_get_value_int(j, "house", house);
				cache_get_value_int(j, "vehicle", vehicle);
				cache_get_value_int(j, "biz", biz);
				cache_get_value_int(j, "faction_id", olusumid);
				cache_get_value_int(j, "omur", omur);
				format(idstr, 6, "%d", id);

				format(idstr, 6, "0%03d", id);

				switch(status)
				{
					case 0: {
						if(type == 0) format(statusstr, 24, "Üzerinizde");
						else format(statusstr, 24, "Üzerinde");
					}
					case 1: format(statusstr, 24, "Evde (%d)", house);
					case 2: format(statusstr, 24, "Araçta (%d)", vehicle);
					case 3: format(statusstr, 24, "Ýþletmede (%d)", biz);
					case 4: format(statusstr, 24, "Polis Zimmeti");
					case 5: format(statusstr, 24, "Yönetici Müdahalesi");
					case 6: format(statusstr, 24, "Geri Ödeme Yapýldý");
					case 7: format(statusstr, 24, "Oluþum kasasý (%d)", olusumid);
					case 8: format(statusstr, 24, "Vergili Evde Silindi (%d)", house);
					case 9: format(statusstr, 24, "Vergili Araçta Silindi (%d)", vehicle);
					case 10: format(statusstr, 24, "Bozuldu");
				}

				if(type == 1 && status != 0)continue;
				SendServerMessage(playerid, "Slot[%d] - ID[%s] - Silah[%s] - Mermi[%d] - Ömür[%d] - Durum[%s]", j+1, idstr, GetWeaponNameEx(weaponid), ammo, omur, statusstr);
			}
		}
		cache_delete(veri);
	}
	return 1;
}



SilahlariKaydet(playerid)
{
	if(!PlayerInfo[playerid][pOnDuty] && PlayerInfo[playerid][pLevel] >= 3 && PlayerInfo[playerid][pSilahSistemi])
	{
		new weapons[12], ammo[12];

		for(new a; a < 12; a++)
		{
			new query[250];
			BWH_GetPlayerWeaponData(playerid, a, weapons[a], ammo[a]);

			if(!weapons[a] || !ammo[a])continue;
			if(SilahSlotBul(weapons[a]) == 0)continue;

			if(AC_PlayerHasWeapon(playerid, weapons[a]) <= 0)
			{
				mysql_format(dbHandle, query, sizeof(query), "UPDATE weapons SET ammo = '%d' WHERE owner = '%d' AND weaponid = '%d' AND status = '0'", ammo[a], PlayerInfo[playerid][pID], weapons[a]);
				mysql_tquery(dbHandle, query);
			}
			else
			{
				mysql_format(dbHandle, query, sizeof(query), "UPDATE weapons SET ammo = '%d' WHERE owner = '%d' AND weaponid = '%d' AND status = '0'", ammo[a], PlayerInfo[playerid][pID], weapons[a]);
				mysql_tquery(dbHandle, query);
			}
		}
	}
	return 1;
}

SilahElkoyFonksiyon(playerid, targetid, type)
{
    if(type == 1)
    {
	    if(IsPlayerConnected(targetid) && pTemp[targetid][pLogged] && !PlayerInfo[targetid][pOnDuty])
	    {
			if(!PlayerInfo[playerid][pOnDuty])
		        return SendErrorMessage(playerid, "Bunu yapamazsýnýz.");

	        if(!PlayerNearPlayer(3.0, playerid, targetid))
	            return SendErrorMessage(playerid, "Belirtilen oyuncuya yakýn deðilsiniz.");

	        mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '4' WHERE owner = '%d' and status = '0'", PlayerInfo[targetid][pID]);
	        mysql_query(dbHandle, queryx, false);

	        AC_ResetPlayerWeapons(targetid);
	        PlayerInfo[targetid][pKamera] = 0;
	        PlayerInfo[targetid][pCicek] = 0;		
			PlayerInfo[targetid][pMaske] = 0;	
			PlayerInfo[targetid][pBoombox] = 0;
			PlayerInfo[targetid][pBurnerTelefon] = 0;

	        SendServerMessage(targetid, "%s adlý polis memuru silahlarýna el koydu. (%s)", GetNameEx(playerid), GetFullDate());

	        mysql_format(dbHandle, queryx, sizeof(queryx), "INSERT INTO weapon_logs (sqlid, playerid, targetid, log, created_at) VALUES ('%d', '%d', '%d', '%e', NOW())", -1, PlayerInfo[playerid][pID], PlayerInfo[targetid][pID], "silahlara el koyuldu");
	        mysql_tquery(dbHandle, queryx);
	        SendAdmMessage("AdmCmd: %s adlý polis %s kiþisinin tüm silahlarýný el koydu.", GetNameEx(playerid), GetNameEx(targetid));
	        Log_Kaydet("resmibirlikLog.txt", "[/ustundenal silah] %s adli polis, %s adli oyuncunun tum silahlarina el koydu. [Tarih: %s]", GetNameEx(playerid), GetNameEx(targetid), GetFullDate());
	    }
	    else SendErrorMessage(playerid, "Bu iþlemi yapamazsýn.");
	}
	else if(type == 2)
	{
	        mysql_format(dbHandle, queryx, sizeof(queryx), "UPDATE weapons SET status = '5' WHERE owner = '%d' and status = '0'", PlayerInfo[targetid][pID]);
	        mysql_query(dbHandle, queryx);

	        AC_ResetPlayerWeapons(targetid);
	        PlayerInfo[targetid][pKamera] = 0;
	        PlayerInfo[targetid][pCicek] = 0;
						
	        SendServerMessage(targetid, "%s adlý yetkili, üzerindeki tüm silahlara el koydu. (%s)", PlayerInfo[playerid][pAccname], GetFullDate());
	        if(!pTemp[playerid][pAdminDuty]) SendServerMessage(playerid, "%s adlý kiþinin üzerindeki tüm silahlara el koydun.", GetNameEx(targetid));
	        SendAdmMessage("AdmCmd: %s, %s adlý kullanýcýnýn üzerindeki silahlarýna el koydu.", PlayerInfo[playerid][pAccname], GetNameEx(targetid));
	        Log_Kaydet("admin/silah.txt", "[%s] %s, %s (%d) adli oyuncunun uzerindeki silahlarina el koydu.", GetFullDate(), PlayerInfo[playerid][pAccname], GetNameEx(targetid), PlayerInfo[targetid][pID]);
	}
	else SendClientMessageEx(playerid, -1, "Bu komutta bir hata oluþtu, hata kodu SEF#3. Bu hata kodunu blaze'e bildirin.");
    return 1;
}

forward SilahlariYukle(playerid);
public SilahlariYukle(playerid)
{
	static rows, fields;
	cache_get_row_count(rows);
	cache_get_field_count(fields);

	if(!rows)return 1;

	new id, weaponid, ammo, status, house, vehicle, biz, lisans, omur, query[256];

	for(new j; j < rows; j++)
	{
		cache_get_value_int(j, "id", id);
		cache_get_value_int(j, "weaponid", weaponid);
		cache_get_value_int(j, "ammo", ammo);
		cache_get_value_int(j, "status", status);
		cache_get_value_int(j, "house", house);
		cache_get_value_int(j, "vehicle", vehicle);
		cache_get_value_int(j, "biz", biz);
		cache_get_value_int(j, "lisans", lisans);
		cache_get_value_int(j, "omur", omur);

		if(biz == -1 && vehicle == -1 && house == -1 && ammo > 0 && status == 0 && omur > 0)
		{
			if(PlayerInfo[playerid][pSilahSistemi] && AC_PlayerHasWeapon(playerid, weaponid))
			{
				SendServerMessage(playerid, "Üzerinizde ayný tip silah tespit edildi, %d nolu silah yönetici müdahalesi moduna girdi.", id);

				SendServerMessage(playerid, "Silaha iliþkin veriler: %s (SQLID: %d / Mermi: %d / Ruhsat: %s)", GetWeaponNameEx(weaponid), id, ammo, (lisans == 1) ? "Mevcut" : "Mevcut deðil");

				SendServerMessage(playerid, "Bu durumu lütfen Ticket > Bug Bildirimleri kanalýna /silah liste görüntüsüyle beraber gönderin.");

				mysql_format(dbHandle, query, sizeof(query), "UPDATE weapons SET status = '5' WHERE id = '%d' and owner = '%d' and status = '0'", id, PlayerInfo[playerid][pID]);
				mysql_query(dbHandle, query);

				//AC_GivePlayerWeapon(playerid, weaponid, ammo);
			}
			else
			{
				if(weaponid == 24 && ammo > 70 && lisans) ammo = 70;
				if(weaponid == 24 && ammo > 50 && !lisans) ammo = 50;

				AC_GivePlayerWeapon(playerid, weaponid, ammo);
				PlayerInfo[playerid][pSilahSistemi] = 1;
			}
		}
	}
	return 1;
}

GetWeaponSlot(weaponid)
{
    new slot;

    switch(weaponid)
    {
        case 0, 1: slot = 0;
        case 2 .. 9: slot = 1;
        case 10 .. 15: slot = 10;
        case 16 .. 18, 39: slot = 8;
        case 22 .. 24: slot =2;
        case 25 .. 27: slot = 3;
        case 28, 29, 32: slot = 4;
        case 30, 31: slot = 5;
        case 33, 34: slot = 6;
        case 35 .. 38: slot = 7;
        case 40: slot = 12;
        case 41 .. 43: slot = 9;
        case 44 .. 46: slot = 11;
   }

    return slot;
}
forward OnPlayerGetWeapon(playerid, slot, ammo);
My_GivePlayerWeapon(playerid, weaponid, ammo)
{
	new g_slot = GetWeaponSlot(weaponid),   strname[32];

	format(strname, sizeof(strname), "weapon%d", g_slot); SetPVarInt(playerid, strname, weaponid);
	format(strname, sizeof(strname), "weaponsecure%d", g_slot); SetPVarInt(playerid, strname, 5);
	format(strname, sizeof(strname), "ammo%d", g_slot);
	new tmp_ammo = GetPVarInt(playerid, strname);

	SetPVarInt(playerid, strname, tmp_ammo+ammo);
	CUSTOM_GivePlayerWeapon(playerid, weaponid, ammo);
	CallRemoteFunction("OnPlayerGetWeapon", "iii", playerid, g_slot, tmp_ammo+ammo);
}

My_ResetPlayerWeapons(playerid)
{
	new strname[32];

	for(new j; j < 12; j++)
	{
		format(strname, sizeof(strname), "weapon%d", j); SetPVarInt(playerid, strname, 0);
		format(strname, sizeof(strname), "weaponsecure%d", j); SetPVarInt(playerid, strname, 0);
		format(strname, sizeof(strname), "ammo%d", j); SetPVarInt(playerid, strname, 0);
	}

	CUSTOM_ResetPlayerWeapons(playerid);
}

stock DO_Emote(Float:radius, playerid, message[], exceptPlayer = false)
{
	new Float:fX, Float:fY, Float:fZ, Float:distance, VW, Int;
	GetPlayerPos(playerid, fX, fY, fZ);
	VW = GetPlayerVirtualWorld(playerid);
	Int = GetPlayerInterior(playerid);
	foreach(new i : Player)
	{
		if(GetPlayerInterior(i) != Int || GetPlayerVirtualWorld(i) != VW) continue;
		if(exceptPlayer && i == playerid) continue;

		distance = GetPlayerDistanceFromPoint(i, fX, fY, fZ);

		if (!(PlayerInfo[i][pSettings] & togDoSetting))
		{
			if(distance < radius/16) SendClientMessageEx(i, 0x79BFA3FF, message);
			else if(distance < radius/8) SendClientMessageEx(i, 0x79BFA3FF, message);
			else if(distance < radius/4) SendClientMessageEx(i, 0x79BFA3FF, message);
			else if(distance < radius/2) SendClientMessageEx(i, 0x79BFA3FF, message);
			else if(distance < radius) SendClientMessageEx(i, 0x79BFA3FF, message);
		}
		else
		{
			if(distance < radius/16) SendClientMessageEx(i, 0xC2A2DAFF, message);
			else if(distance < radius/8) SendClientMessageEx(i, 0xC2A2DAFF, message);
			else if(distance < radius/4) SendClientMessageEx(i, 0xC2A2DAFF, message);
			else if(distance < radius/2) SendClientMessageEx(i, 0xC2A2DAFF, message);
			else if(distance < radius) SendClientMessageEx(i, 0xC2A2DAFF, message);			
		}
	}
	return 1;
}

stock DestroyDynamicObjectEx(&objectid)
{
	// for(new j; j < 12; j++) SetDynamicObjectMaterial(objectid, j, 19341, "invalid", "invalid");
	if(IsValidDynamicObject(objectid)) DestroyDynamicObject(objectid);
	objectid = -1;
	return 1;
}

stock DestroyDynamic3DTextLabelEx(&Text3D:labelid)
{
	if(IsValidDynamic3DTextLabel(labelid)) DestroyDynamic3DTextLabel(labelid);
	labelid = Text3D:INVALID_3DTEXT_ID;
	return 1;
}

MulStringHandler(string[]) // text cut off for drugs effect
{
    new mulstr[160];
	strcat(mulstr, string);
	for(new charSet = 0; charSet < strlen(string); charSet += random(5) + 2) {
	   if (mulstr[charSet] != ' ') {
	      strins(mulstr, ".. ", charSet);
	   }
	}
	return mulstr;
}

stock Oyuncu_Isim(playerid)
{
    new name[MAX_PLAYER_NAME+1];
	GetPlayerName(playerid, name, MAX_PLAYER_NAME);
    return name;
}

GetCharacterName(databaseID)
{
	new query[90];
	new tmpName[MAX_PLAYER_NAME] = "Sahipsiz";
	if(databaseID)
	{
		mysql_format(dbHandle, query, sizeof(query), "SELECT name FROM users WHERE id = '%d'", databaseID);
		mysql_query(dbHandle, query);

		cache_get_value(0, "name", tmpName, MAX_PLAYER_NAME);
	}

	return tmpName;
}