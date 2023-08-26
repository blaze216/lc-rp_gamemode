Dialog:DIALOG_GPS(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	switch(listitem) {
		case 0: { // lîcations
			new substr[48],
                str[sizeof(substr)*20 + 20] = "Lokasyon\t Mesafe";

			for(new i; i < MAX_INTERIORS; i++) {
				if (!AdminTeles[i][telesOn] || GPS_TELE_TYPE != AdminTeles[i][telesType]) continue;

				format(substr, sizeof(substr), "%.32s\t{33CC33}%i m", AdminTeles[i][telesMapName], GetPlayerDistanceToPointEx(playerid, AdminTeles[i][telesPosX], AdminTeles[i][telesPosY], AdminTeles[i][telesPosZ]));
                format(str, sizeof(str), "%s\n%s", str, substr);
            }
			
            if (isempty(substr)) format(str, sizeof(str), "%s\n{FF6347}BULUNMUYOR", str);

			Dialog_Show(playerid, DIALOG_GPS_LOCATION, DIALOG_STYLE_TABLIST_HEADERS, "GPS > Lokasyonlar", str, "Seç", "Geri");
		}
		case 1: { // biz
			new substr[80],
                str[sizeof(substr)*MAX_BIZ_TYPES+30] = "Tip\tAd\t Mesafe", 
				id, 
				Float:radius;

			for(new i; i < MAX_BIZ_TYPES; i++) {
				if ((id = GetClosestTypeBiz(playerid, i, radius)) == -1)	{
					format(substr, sizeof(substr), "%s\t{FF6347}BULUNMUYOR", biz_types[i]);
				} else {
					format(substr, sizeof(substr), "%s\t%s\t{33CC33}%.0f m", biz_types[i], BizInfo[id][bizName], radius);
				}
                format(str, sizeof(str), "%s\n%s", str, substr);
			}

            if (isempty(substr)) format(str, sizeof(str), "%s\n{FF6347}BULUNMUYOR", str);

			Dialog_Show(playerid, DIALOG_GPS_BIZ, DIALOG_STYLE_TABLIST_HEADERS, "GPS > Ýþ Yerleri", str, "Seç", "Geri");
		}
		case 2: { // Jobs
			new substr[64],
                str[sizeof(substr)*MAX_BIZ_TYPES+20] = "Meslekler\tMesafe", 
				Float:radius;

			for(new i = 1; i < MAX_JOBS_TYPES; i++) {
				if (GetClosestTypeJob(playerid, i, radius) == -1) {
					format(substr, sizeof(substr), "%s\t{FF6347}BULUNMUYOR", jobs_names[i]);
				} else {
					format(substr, sizeof(substr), "%s\t{33CC33}%.0f m", jobs_names[i], radius);
				}
                format(str, sizeof(str), "%s\n%s", str, substr);
			}

            if (isempty(substr)) format(str, sizeof(str), "%s\n{FF6347}BULUNMUYOR", str);

			Dialog_Show(playerid, DIALOG_GPS_JOBS, DIALOG_STYLE_TABLIST_HEADERS, "GPS > Meslek", str, "Seç", "Geri");
		} 
		case 3: Dialog_Show(playerid, DIALOG_GPS_ISYERI, DIALOG_STYLE_INPUT, "GPS > Ýþyeri Bul", "Bulacaðýnýz iþ yerinin ID'sini yazýnýz:", "Bul", "Geri");
		case 4: Dialog_Show(playerid, DIALOG_GPS_EV, DIALOG_STYLE_INPUT, "GPS > Ev Bul", "Bulacaðýnýz Ev ID'sini yazýnýz:", "Bul", "Geri");
	}
	return 1;
}

Dialog:DIALOG_GPS_EV(playerid, response, listitem, inputtext[])
{
	if(!response) return pc_cmd_gps(playerid, "");

	new houseid = strval(inputtext);
	if (houseid < 0 || houseid >= MAX_HOUSES)	return SendErrorMessage(playerid,"Geçersiz Ev ID.");
	if (!HouseInfo[houseid][hID])				return SendErrorMessage(playerid, "Böyle bir adres bulunamadý.");
	if (HouseInfo[houseid][hApart] && ApartInfo[HouseInfo[houseid][hApart]][aID] > 0 )	Waypoint_Set(playerid, ApartInfo[HouseInfo[houseid][hApart]][aPosX], ApartInfo[HouseInfo[houseid][hApart]][aPosY], ApartInfo[HouseInfo[houseid][hApart]][aPosZ]);
	else 							Waypoint_Set(playerid, HouseInfo[houseid][hPosX], HouseInfo[houseid][hPosY], HouseInfo[houseid][hPosZ]);
	SendSyntaxMessage(playerid, "Ev (%s) GPS'te iþaretlendi. (/cpsifirla)", (!HouseInfo[houseid][hApart])?(GetHouseZone(houseid)):(GetApartmentZone(HouseInfo[houseid][hApart])));
	return 1;
}

Dialog:DIALOG_GPS_ISYERI(playerid, response, listitem, inputtext[])
{
	if(!response) return pc_cmd_gps(playerid, "");
	new bizid = strval(inputtext);
	if(bizid < 0 || bizid >= MAX_BIZ)			return SendErrorMessage(playerid, "Geçersiz iþyeri/mekan ID'si.");
	if(!BizInfo[bizid][bizID])					return SendErrorMessage(playerid, "Böyle bir iþletme/mekan bulunamadý.");
	Waypoint_Set(playerid, BizInfo[bizid][bizPosX], BizInfo[bizid][bizPosY], BizInfo[bizid][bizPosZ]);
	PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
	SendSyntaxMessage(playerid, "Belirtilen iþletme/mekan GPS'te iþaretlendi. (/cpsifirla)");
	return 1;
}

Dialog:DIALOG_GPS_LOCATION(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_gps(playerid, "");

	new id;
	for(new i; i < MAX_INTERIORS; i++) {
		if (!AdminTeles[i][telesOn] || GPS_TELE_TYPE != AdminTeles[i][telesType]) continue;
		
		if (listitem == id) {
			id = i;
			break;
		} else id++;
	}

	Waypoint_Set(playerid, AdminTeles[id][telesPosX], AdminTeles[id][telesPosY], AdminTeles[id][telesPosZ]);
	SendClientMessageEx(playerid, COLOR_SERVER2, "'%s' adlý lokasyon haritada iþaretlendi. (/cpsifirla komutunu checkpoint sýfýrlamak için kullanabilirsiniz.)", AdminTeles[id][telesMapName]);
	PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:DIALOG_GPS_BIZ(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_gps(playerid, "");

	new id, Float:radius;
	if ((id = GetClosestTypeBiz(playerid, listitem, radius)) == -1) return pc_cmd_gps(playerid, "");

	Waypoint_Set(playerid, BizInfo[id][bizPosX], BizInfo[id][bizPosY], BizInfo[id][bizPosZ]);
	SendClientMessageEx(playerid, COLOR_SERVER2, "[%s] %s adlý iþyeri haritanýzda iþaretlendi. (/cpsifirla komutunu checkpoint sýfýrlamak için kullanabilirsiniz.)", biz_types[listitem], BizInfo[id][bizName]);
	PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:DIALOG_GPS_JOBS(playerid, response, listitem, inputtext[])
{
	if (!response) return pc_cmd_gps(playerid, "");
	
	listitem++;

	new id, Float:radius;
	if ((id = GetClosestTypeJob(playerid, listitem, radius)) == -1) return pc_cmd_gps(playerid, "");

	Waypoint_Set(playerid, JobsInfo[id][jobX], JobsInfo[id][jobY], JobsInfo[id][jobZ]);
	SendClientMessageEx(playerid, COLOR_SERVER2, "'%s' adlý meslek haritanýzda iþaretlendi. (/cpsifirla komutunu checkpoint sýfýrlamak için kullanabilirsiniz.)", jobs_names[listitem]);
	PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
	return 1;
}