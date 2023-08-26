/*Dialog:BuyDrugs(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	new drug_list_name[][] = {"Marijuana yapraklarý "," LSD "," Eroin "," Kokain "," Efedrin"}, drug_list_price[] = {50, 150, 100, 200, 50};
	
	static const str_size[] = "{FFFFFF}You want to purchase %s $%i for 1 gram.\nAvailable quantity for purchase: 1 - 1000:";
	new mes[sizeof(str_size) - 4 + 7 + 3 + 1];

	format(mes, sizeof(mes), str_size, drug_list_name[listitem], drug_list_price[listitem]);
    Dialog_Show(playerid, BuyDrugsAccept, DIALOG_STYLE_INPUT, "{FFFFFF}Uyuþturucu Satýn Al", mes, "Seç", "Ýptal");
    SetPVarInt(playerid, #select_law, listitem);
	return 1;
}

Dialog:BuyDrugsAccept(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_buydrugs(playerid, "");

	new amount = strval(inputtext);

	listitem = GetPVarInt(playerid, #select_law);

	if (amount < 0 || amount > 1000)	return SendErrorMessage(playerid, "Yanlýþ uyuþturucu miktarý: 1 - 1000.");
	
    new faction = PlayerInfo[playerid][pFaction];

	if (!PlayerInfo[playerid][pFaction])														return SendErrorMessage(playerid, "Onaylý bir birlikte deðilsiniz. ");
	if (PlayerInfo[playerid][pSideJob] != JOB_DRUGDEALER)										return SendErrorMessage(playerid, "Uyuþturucu satýn almaya eriþimin yok.");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;
    if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "Rýhtýmda olmalýsýnýz.");
	}

	new drug_list[] = {INV_SEED_GANJA, INV_LSD, INV_HEROIN, INV_COCAINE, INV_EPHEDRINE}, drug_price[] = {50, 150, 100, 200, 50};

	if (GetCash(playerid) < drug_price[listitem] * amount)			return SendNotCash(playerid);
	if (GiveInvItem(playerid, drug_list[listitem], amount) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

	SendSyntaxMessage(playerid, "$%i karþýlýðýnda %i gram %s satýn aldýnýz.", amount, inventory_items[drug_list[listitem]][itemName], drug_price[listitem] * amount);
	GiveCash(playerid, -drug_price[listitem] * amount);
	return 1;
}

Dialog:BuyAmmoLaw(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_buygun(playerid, "");

    new faction = PlayerInfo[playerid][pFaction], ammo = 1;

	new gun_list[][20] = {"M1911","M1911","Desert Eagle","Desert Eagle","Shotgun","Shotgun","Shotgun","Tec-9 / MP5 / Uzi", "Tec-9 / MP5 / Uzi","Country Rifle"},
		ammo_list[] = {82, 83, 84, 85, 86, 87, 88, 90, 91, 96},
		ammo_pr[] = {35, 80, 60, 130, 300, 200, 100, 200, 450, 400};

	if (!PlayerInfo[playerid][pFaction])															return SendErrorMessage(playerid, "Onaylý bir birlikte deðilsiniz. ");
	if (PlayerInfo[playerid][pSideJob] != JOB_GUNDEALER)											return SendErrorMessage(playerid, "Silah satýn almak için eriþiminiz yok. ");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)		return 1;
    if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "Rýhtýmda olmalýsýnýz.");
	}

	if (!CheckInv(playerid)) 					return SendErrorMessage(playerid, "Envanterinizde yeterli alan yok.");
	if (GetCash(playerid) < ammo_pr[listitem])	return SendNotCash(playerid);
	if (Factions[faction][fPoint]- ammo < 0)	return SendErrorMessage(playerid, "Birliðinizin satýn almak için yeterli puaný yok.");
    
	GiveCash(playerid, -ammo_pr[listitem]);
	GiveInvItem(playerid, ammo_list[listitem], CheckAmmo(ammo_list[listitem])); 

	Factions[faction][fPoint] -= 1;
	SQL_SetInteger("factions", "point", Factions[faction][fPoint], Factions[faction][fID]);

	SendBlackMarketMessage(playerid, "$%i ve 1 exp karþýlýðýnda %s için bir maðaza %s [%i mermi] satýn aldýnýz.", inventory_items[ammo_list[listitem]][itemName], CheckAmmo(ammo_list[listitem]), gun_list[listitem], ammo_pr[listitem]);
	return 1;
}

Dialog:BuyGunLaw(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_buygun(playerid, "");

    new faction = PlayerInfo[playerid][pFaction];

	if (!PlayerInfo[playerid][pFaction])														return SendErrorMessage(playerid, "Onaylý bir birlikte deðilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_GUNDEALER)										return SendErrorMessage(playerid, "Silah satýn almak için eriþiminiz yok.");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;

	if (Factions[faction][fType] == FACTION_MAFIA)
	{
		new gun_list[] = {24, 22, 23, 25, 26, 27, 28, 32, 29, 30, 31, 33, 16, 18, INV_OPTICS, INV_SILENCER, INV_TOOLS}, 
			gun_point[] = {3, 3, 3, 4, 4, 4, 5, 5, 5, 7, 7, 10, 10, 4, 2, 2, 1}, 
			gun_price[] = {1800, 1000, 1500, 2400, 2100, 4000, 2000, 2500, 2800, 3500, 4300, 3800, 1000, 300, 1700, 500, 300}, 
			gun_ammo[] = {50, 50, 50, 30, 30, 30, 120, 120, 120, 150, 150, 15, 1, 1, 1, 1, 1};

        if (Factions[faction][fPoint]-gun_point[listitem] < 0)																	return SendErrorMessage(playerid, "Birliðinizin satýn almak için yeterli puaný yok.");
        //if (ValidWeaponForInventory(gun_list[listitem]) && PlayerInfo[playerid][pWeap][GetWeapSlot(gun_list[listitem])] != 0)	return SendErrorMessage(playerid, "Ó âàñ óæå åñòü îðóæèå â äàííîì ñëîòå.");
		    
		new mes[256];
		if (ValidWeaponForInventory(gun_list[listitem]))
		{
			format(mes, sizeof(mes), "{FFFFFF}Are you sure you want to buy %s and %i ammo for %i exp and $%i?\nYour faction will have %i exp.",
			inventory_items[gun_list[listitem]][itemName], gun_ammo[listitem], gun_point[listitem], gun_price[listitem], Factions[faction][fPoint]-gun_point[listitem]);
		}
		else
		{
			format(mes, sizeof(mes), "{FFFFFF}Are you sure you want to buy %s for %i exp and $%i?\nYour faction will have %i exp.",
			inventory_items[gun_list[listitem]][itemName], gun_point[listitem], gun_price[listitem], Factions[faction][fPoint]-gun_point[listitem]);
		}
    	Dialog_Show(playerid, BuyGunAccept, DIALOG_STYLE_MSGBOX, "{FFFFFF}Silah Satýn Al", mes, "Satýn Al", "Geri");
	}

	else if (Factions[faction][fType] == FACTION_GANG)
	{
		new gun_list[] = {24, 22, 25, 26, 28, 32, 18, INV_TOOLS}, gun_point[] = {3, 3, 4, 4, 5, 5, 4, 1}, gun_price[] = {1800, 1000, 2400, 2100, 2000, 2500, 300, 300}, gun_ammo[] = {50, 50, 30, 30, 120, 120, 1, 1};

        if (Factions[faction][fPoint]-gun_point[listitem] < 0)																	return SendErrorMessage(playerid, "Birliðinizin satýn almak için yeterli puaný yok.");
        //if (ValidWeaponForInventory(gun_list[listitem]) && PlayerInfo[playerid][pWeap][GetWeapSlot(gun_list[listitem])] != 0)	return SendErrorMessage(playerid, "Ó Âàñ óæå åñòü îðóæèå â äàííîì ñëîòå.");
		    
		new mes[256];

		if (ValidWeaponForInventory(gun_list[listitem]))
		{
			format(mes, sizeof(mes), "{FFFFFF}Are you sure you want to buy %s and %i rounds for %i exp and $%i?\nYour faction will have %i exp.",
			inventory_items[gun_list[listitem]][itemName], gun_ammo[listitem], gun_point[listitem], gun_price[listitem], Factions[faction][fPoint]-gun_point[listitem]);
		}
		else
		{
			format(mes, sizeof(mes), "{FFFFFF}Are you sure you want to buy %s for %i exp and $%i?\nYour faction will have %i exp.",
			inventory_items[gun_list[listitem]][itemName], gun_point[listitem], gun_price[listitem], Factions[faction][fPoint]-gun_point[listitem]);
		}
    	Dialog_Show(playerid, BuyGunAccept, DIALOG_STYLE_MSGBOX, "Silah Satýn Al", mes, "Satýn Al", "Geri");
	}
	SetPVarInt(playerid, #select_law, listitem);
	return 1;
}

Dialog:BuyGunAccept(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_buygun(playerid, "");

	listitem = GetPVarInt(playerid, #select_law);

    new faction = PlayerInfo[playerid][pFaction];

	if (!PlayerInfo[playerid][pFaction])															return SendErrorMessage(playerid, "Onaylý bir birlikte deðilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_GUNDEALER)											return SendErrorMessage(playerid, "Silah satýn almak için eriþiminiz yok.");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;
    if (!PlayerToPoint(2.0, playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z))
	{
	    Waypoint_Set(playerid, BLACKMARKET_X, BLACKMARKET_Y, BLACKMARKET_Z);
	    return SendErrorMessage(playerid, "Rýhtýmda olmalýsýnýz.");
	}

	if (Factions[faction][fType] == FACTION_MAFIA)
	{
		new gun_list[] = {24, 22, 23, 25, 26, 27, 28, 32, 29, 30, 31, 33, 16, 18, INV_OPTICS, INV_SILENCER, INV_TOOLS}, gun_point[] = {3, 3, 3, 4, 4, 4, 5, 5, 5, 7, 7, 10, 10, 4, 2, 2, 1},
	    	gun_price[] = {1800, 1000, 1500, 2400, 2100, 4000, 2000, 2500, 2800, 3500, 4300, 3800, 1000, 300, 1700, 500, 300}, gun_ammo[] = {50, 50, 50, 30, 30, 30, 120, 120, 120, 150, 150, 15, 1, 1, 1, 1, 1};

		if (Factions[faction][fPoint]-gun_point[listitem] < 0)																	return SendErrorMessage(playerid, "Birliðinizin satýn almak için yeterli puaný yok.");
		if (GetCash(playerid) < gun_price[listitem])																				return SendNotCash(playerid);
        //if (ValidWeaponForInventory(gun_list[listitem]) && PlayerInfo[playerid][pWeap][GetWeapSlot(gun_list[listitem])] != 0)	return SendErrorMessage(playerid, "Ó Âàñ óæå åñòü îðóæèå â äàííîì ñëîòå.");
		    
		if (ValidWeaponForInventory(gun_list[listitem]))
		{
		    GivePlayerWeaponEx(playerid, gun_list[listitem], gun_ammo[listitem]);
		    SendSyntaxMessage(playerid, "%s ve %i mermi satýn aldýnýz.", inventory_items[gun_list[listitem]][itemName], gun_ammo[listitem]);
		}
		else
		{
        	if (GiveInvItem(playerid, gun_list[listitem], gun_ammo[listitem]) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");
				
			SendSyntaxMessage(playerid, "%s satýn aldýnýz.", inventory_items[gun_list[listitem]][itemName], gun_ammo[listitem]);
		}
		
        Factions[faction][fPoint] -= gun_point[listitem];
        SQL_SetInteger("factions", "point", Factions[faction][fPoint], Factions[faction][fID]);
		GiveCash(playerid, -gun_price[listitem]);
	}

	else if (Factions[faction][fType] == FACTION_GANG)
	{
  		new gun_list[] = {24, 22, 25, 26, 28, 32, 18, INV_TOOLS}, gun_point[] = {3, 3, 4, 4, 5, 5, 4, 1}, gun_price[] = {1800, 1000, 2400, 2100, 2000, 2500, 300, 300}, gun_ammo[] = {50, 50, 30, 30, 120, 120, 1, 1};

		if (Factions[faction][fPoint]-gun_point[listitem] < 0)	return SendErrorMessage(playerid, "Birliðinizin satýn almak için yeterli puaný yok");
		if (GetCash(playerid) < gun_price[listitem])	return SendNotCash(playerid);
        //if (ValidWeaponForInventory(gun_list[listitem]) && PlayerInfo[playerid][pWeap][GetWeapSlot(gun_list[listitem])] != 0)	return SendErrorMessage(playerid, "Ó Âàñ óæå åñòü îðóæèå â äàííîì ñëîòå.");

		if (ValidWeaponForInventory(gun_list[listitem]))
		{
		    GivePlayerWeaponEx(playerid, gun_list[listitem], gun_ammo[listitem]);
		    SendSyntaxMessage(playerid, "%s ve %i mermi satýn aldýnýz.", inventory_items[gun_list[listitem]][itemName], gun_ammo[listitem]);
		}
		else
		{
        	if (GiveInvItem(playerid, gun_list[listitem], gun_ammo[listitem]) == -1)	return SendErrorMessage(playerid, "Envanteriniz tamamen dolu.");

			SendSyntaxMessage(playerid, "%s satýn aldýnýz.", inventory_items[gun_list[listitem]][itemName], gun_ammo[listitem]);
		}

        Factions[faction][fPoint] -= gun_point[listitem];
		SQL_SetInteger("factions", "point", Factions[faction][fPoint], Factions[faction][fID]);
		GiveCash(playerid, -gun_price[listitem]);
	}
	return 1;
}

Dialog:BuyGunMain(playerid, response, listitem, inputtext[])
{
	if (!response)	return 1;

    new faction = PlayerInfo[playerid][pFaction];

	if (!PlayerInfo[playerid][pFaction])	return SendErrorMessage(playerid, "Onaylý bir birlikte deðilsiniz.");
	if (PlayerInfo[playerid][pSideJob] != JOB_GUNDEALER)	return SendErrorMessage(playerid, "Silah satýn almak için eriþiminiz yok.");
	if (Factions[faction][fType] != FACTION_GANG && Factions[faction][fType] != FACTION_MAFIA)	return 1;

    new title[56];

	format(title, sizeof(title), "{FFFFFF}On the account of your faction - %i exp.", Factions[faction][fPoint]);

	if (listitem == 0)
	{
	    if (Factions[faction][fType] == FACTION_MAFIA)
		{
			new mes[1024] = "Desert Eagle\t-3 exp\t$1.800\n\
							COLT45\t-3 exp\t$1.000\n\
							COLT45(silencer)\t-3 exp\t$1.500\n\
							Shotgun\t-4 exp\t$2.400\n\
							Sawn-off Shotgun\t-4 exp\t$2.100\n\
							Combat Shotgun\t-4 exp\t$4.000\n\
							UZI\t-5 exp\t$2.000\n\
							Tec-9\t-5 exp\t$2.500\n\
							MP5\t-5 exp\t$2.800\n\
							M4\t-7 exp\t$4.300\n\
							Rifle\t-10 exp\t$3.800\n\
							Grenade\t-10 exp\t$1000\n\
							Molotov cocktail\t-4 exp\t$300\n\
							Optical sight\t-2 exp\t$1700\n\
							Ûilencer\t-2 exp\t$500\n\
							Lock pick\t-1 exp\t$300";
			
			Dialog_Show(playerid, BuyGunLaw, DIALOG_STYLE_TABLIST, title, mes, "Satýn Al", "Ýptal");
		}
		else
		{
		    Dialog_Show(playerid, BuyGunLaw, DIALOG_STYLE_TABLIST, title, "Desert Eagle\t-3 exp\t$1.800\n\
																			COLT45\t-3 exp\t$1.000\n\
																			Shotgun\t-4 exp\t$2.400\n\
																			Sawn-off Shotgun\t-4 exp\t$2.100\n\
																			UZI\t-5 exp\t$2.000\n\
																			Tec-9\t-5 exp\t$2.500\n\
																			Molotov cocktail\t-4 exp\t$300\n\
																			Lock pick\t-1 exp\t$300", "Buy", "Ýptal");
		}
	}

	else if (listitem == 1)
	{
	    Dialog_Show(playerid, BuyAmmoLaw, DIALOG_STYLE_TABLIST, title, "100 units.\t-1 exp\t$400\n200 units.\t-2 exp\t$800\n300 units.\t-3 exp\t$1.200\n400 units.\t-4 exp\t$1.600\n500 units.\t-5 exp\t$2.000\n600 units.\t-6 exp\t$2.400", "Buy", "Ýptal");
	}
	return 1;
}*/

Dialog:TakeJobMenu(playerid, response, listitem, inputtext[])
{
	if (!response) return 1;

	switch(listitem) {
		case 0: {
			new i = Job_Nearest(playerid);
			if (i == -1) return 1;

			if (JobsInfo[i][jobType] == JOB_PIZZA)
			{
				//if (PlayerInfo[playerid][pSideJob] != JOBLESS) return SendSyntaxMessage(playerid, "Zaten ikinci bir iþiniz var. Çýkmak için /istencik komutunu kullanabilirsiniz..");
				
				PlayerInfo[playerid][pSideJob] = JobsInfo[i][jobType];
				SQL_SetInteger("users", "sidejob", JobsInfo[i][jobType], PlayerInfo[playerid][pID]);
				
				if (JobsInfo[i][jobType] == JOB_PIZZA) 		SendSyntaxMessage(playerid, "Pizza kuryesi olarak iþe baþladýn. Pizza daðýtmak için -> /kurye");
				return 1;
			}
				
			if (PlayerInfo[playerid][pJob] != JOBLESS)									return SendErrorMessage(playerid, "Zaten bir iþiniz var. Ýþten çýkmak için /istenayril komutunu kullanabilirsiniz. ");
			if (JobsInfo[i][jobType] == JOB_TAXI && !PlayerInfo[playerid][pTaxiLic])	return SendErrorMessage(playerid, "Taksi lisansýnýz yok, lisansý almak için bir sürücü kursuna baþvurun. ");

			PlayerInfo[playerid][pJob] = JobsInfo[i][jobType];
			PlayerInfo[playerid][pCareer] = 0;

			SQL_SetInteger("users", "job", JobsInfo[i][jobType], PlayerInfo[playerid][pID]);

			SendSyntaxMessage(playerid, "'%s' mesleðinde çalýþýyorsunuz. Ýþ hakkýnda bilgi almak için- /meslekyardim", jobs_names[JobsInfo[i][jobType]]);
			return 1;
		}
		case 1: {
			new i = Job_Nearest(playerid);
			if (i == -1) return 1;

			return pc_cmd_meslekyardim(playerid, "");
		}
		case 2: pc_cmd_isegir(playerid, "");
		case 3: pc_cmd_istencik(playerid, "");
	}

	return 1;
}
