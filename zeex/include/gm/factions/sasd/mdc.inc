MD_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
    if (playertextid == MDC_UI[playerid][16]) // X
    {
        MDC_Hide(playerid);
        return 1;
    }
    
    if (playertextid == MDC_BACK[playerid])
    {
        if (MdcInfo[playerid][mdcBack] == PAGE_LOOKUP_VEHICLES_LIST)
        {
            new query[164];
            mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `owner` = %i AND `registered`=1 LIMIT 3", GetPVarInt(playerid, #MDC_OWNER_ID));
            mysql_tquery(dbHandle, query, "MDCSearchVehiclesList", "i", playerid);
            MdcInfo[playerid][mdcListPage] = 0;
        }
        else if (MdcInfo[playerid][mdcBack] == PAGE_LOOKUP_VEHICLE)
        {
            new query[164];
            mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `id` = %i AND `registered`=1 LIMIT 1", GetPVarInt(playerid, #MDC_ID));
            mysql_tquery(dbHandle, query, "MDCSearchVehicle", "i", playerid);
        }
        else if (MdcInfo[playerid][mdcBack] == PAGE_LOOKUP_PERSON)
        {
            new query[64];
            mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i", GetPVarInt(playerid, #MDC_ID));
	        mysql_tquery(dbHandle, query, "MDCSearchPersonInfo", "i", playerid);
            MdcInfo[playerid][mdcListPage] = 0;

            DeletePVar(playerid, #MDC_FINE);
        }
        else if (MdcInfo[playerid][mdcBack] == PAGE_MENU)
        {
            Update_MDC(playerid, PAGE_MENU);

            for(new j = 0; j < 16; j++) 
            {
                if (MdcInfo[playerid][mdcList][j] != -1)
                    PlayerTextDrawShow(playerid, MDC_LIST[playerid][j]);
            }
            
            //MdcInfo[playerid][mdcPage] = PAGE_MENU;

            if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
                MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_PERSON;
            else 
                MdcInfo[playerid][mdcBack] = PAGE_LOOKUP_VEHICLE;
        }
        else if (MdcInfo[playerid][mdcBack] == PAGE_MEMBERS)
        {
            Update_MDC(playerid, PAGE_MEMBERS);
            MDC_ShowMembersMenu(playerid);            
        }
        return 1;
    }

	if (playertextid == MDC_UI[playerid][2]) // "ÃËÀÂÍÀß");
	{
		MDC_PAGE(playerid, PAGE_MAIN);
		return 1;
   	}

	if (playertextid == MDC_UI[playerid][3]) // "ÏÎÈÑÊ");
   	{
		MDC_PAGE(playerid, PAGE_LOOKUP);
		return 1;
   	}

	if (playertextid == MDC_UI[playerid][4]) // "ÂÛÇÎÂÛ");
	{
        MDC_PAGE(playerid, PAGE_CALLS);
		return 1;
   	}

    if (playertextid == MDC_UI[playerid][5]) // "ÑÎÒÐÓÄÍÈÊÈ");
	{
        MDC_PAGE(playerid, PAGE_MEMBERS);
        //Dialog_Show(playerid, None, DIALOG_STYLE_MSGBOX, "{3D62A8}ÑÎÒÐÓÄÍÈÊÈ", "{ffffff}Mobile Data Computer âñ¸ åù¸ íàõîäèòñÿ â ðàçðàáîòêå.\nÌû ïðîñèì ó âàñ òåðïåíèÿ è ïîíèìàíèÿ.\n\nÑ óâàæåíèåì,\n{a9c4e4}SASD Tech. Department", "Close", "");
		return 1;
   	}
    
    if (playertextid == MDC_UI[playerid][6]) // "APB");
   	{
        MDC_PAGE(playerid, PAGE_APB);
        return 1;    
   	}
    
    if (playertextid == MDC_UI[playerid][7]) // "ÞÍÈÒÛ");
   	{
        MDC_PAGE(playerid, PAGE_ROSTER);
		return 1;    
   	}
    
    if (playertextid == MDC_UI[playerid][8]) // "CCTV");
   	{
        MDC_PAGE(playerid, PAGE_CCTV);
		return 1; 
   	}

    if (playertextid == MDC_LOOKUP_SEARCH[playerid][0]) // "ÈÌß");
   	{
        if (MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            new apb = -1;

            for(new i = MAX_APBS-1; i >= 0; i--)
            {
                if (ApbInfo[i][apbOn] != 0) continue;

                apb = i;
                break;
            }

            if (apb == -1)	return SendErrorMessage(playerid,"APB bildirimi yazmak için yer kalmamýþ.");
            
            SetPVarInt(playerid, #MDC_ID, apb);
            Dialog_Show(playerid, APB_CREATE_FIRST, DIALOG_STYLE_INPUT, "{098d18}APB oluþturma ", "{B4B5B7}Þüphelinin adýný soyadýný giriniz:\n- Maksimum 24 karakter desteklemektedir.", ">>>", "Kapat");
        }
        else
        {
            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF); // ÈÌß

            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
            PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF); // ÒÑ

            for(new i = 0; i < 2; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);

            MdcInfo[playerid][mdcSearch] = 0;
        }
        return 1; 
   	}

    if (playertextid == MDC_LOOKUP_SEARCH[playerid][1]) // "ÒÑ");
    {
        if (MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            if (MdcInfo[playerid][mdcSearch])
            {
                PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "ISIM");
                MdcInfo[playerid][mdcSearch] = 0;

                PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF);
                PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF); // ÒÑ
            }
            else
            {                                                                     
                PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][1], "YAZI");
                MdcInfo[playerid][mdcSearch] = 1;

                PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF);
                PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF); // ÒÑ
            }
        }
        else
        {
            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0x494949FF);
            PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][0], 0xa7a7a7FF); // ÈÌß

            PlayerTextDrawColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0xa7a7a7FF);
            PlayerTextDrawBoxColor(playerid, MDC_LOOKUP_SEARCH[playerid][1], 0x494949FF); // ÒÑ

            for(new i = 0; i < 2; i++)  PlayerTextDrawShow(playerid, MDC_LOOKUP_SEARCH[playerid][i]);

            MdcInfo[playerid][mdcSearch] = 1;
        }
        return 1; 
   	}

    if (playertextid == MDC_LOOKUP_SEARCH[playerid][2]) // "Done");
   	{
        if (MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            if (!MdcInfo[playerid][mdcSearch]) 
                Dialog_Show(playerid, MDC_APB_SEARCH_NAME, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ýsim ile ara", "Aradýðýnýz kiþinin ismini kutucuða girin:", "Arat", "Geri Dön");
            else 
                Dialog_Show(playerid, MDC_APB_SEARCH_CHARGE, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Eþgal belirterek ara", "Aratmak istediðiniz bir kelimeyi yazabilirsin:", "Arat", "Geri Dön");
        }
        else
        {
            if (!MdcInfo[playerid][mdcSearch]) 
                Dialog_Show(playerid, MDCSearchPerson, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ýsim ile ara", "{B4B5B7}Ýsim ile ara\n\nAd soyad giriniz:\n\nFormat Ad_Soyad þeklinde olmalý ((veya oyuncu ID))", "Arat", "Geri Dön");
            else 
                Dialog_Show(playerid, MDCSearchVehicleType, DIALOG_STYLE_TABLIST, "{8D8DFF}MDC  - Araç arama", "Sahip adý ile ara\nPlaka ile ara", "Seç", "Geri Dön");
        }

        return 1; 
    }

    if (playertextid == MDC_LOOKUP_SEARCH[playerid][3]) // "Hang up");
    {
        PlayerTextDrawSetString(playerid, MDC_LOOKUP_SEARCH[playerid][2], "______________");
        PlayerTextDrawHide(playerid, MDC_LOOKUP_ERROR[playerid]);

        SetPVarInt(playerid, #MDC_APB_S, 0);

        /*
        new page = MdcInfo[playerid][mdcPage];
        
        switch(page)
        {
			case PAGE_LOOKUP_PERSON:
			{

			}
			case PAGE_LOOKUP_VEHICLE:
			{

			}
			case PAGE_LOOKUP_VEHICLES_LIST:
			{

			}
        }*/

        if (MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            MDC_PAGE(playerid, PAGE_APB);
        }
        else
        {
            for(new h = 0; h < 8; h++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLE[playerid][h]);

            for(new a = 0; a < 12; a++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_LIST[playerid][a]);
            for(new b = 0; b < 3; b++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][b]);
            for(new g = 0; g < 3; g++)  PlayerTextDrawHide(playerid, MDC_VEH_LIST_CLICK[playerid][g]);

            for(new j = 0; j < 2; j++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_AVATAR[playerid][j]);
            for(new k = 0; k < 12; k++)  PlayerTextDrawHide(playerid, MDC_LOOKUP_PERSON[playerid][k]);

            MdcInfo[playerid][mdcPage] = PAGE_LOOKUP;
        }

        MdcInfo[playerid][mdcListPage] = 0;

        return 1; 
    }

    if (playertextid == MDC_LOOKUP_PERSON[playerid][4])
    {
        if(MdcInfo[playerid][mdcPage] == PAGE_MEMBERS_MAP) {
            if (pTemp[playerid][pSpecPlayer] == INVALID_PLAYER_ID) SavePlayerPos(playerid);	
            new userid = GetPVarInt(playerid, #BODYCAM);
            pTemp[playerid][pSpecPlayer] = userid;
            TogglePlayerSpectating(playerid, 1);

            if (IsPlayerInAnyVehicle(userid)) 	PlayerSpectateVehicle(playerid, GetPlayerVehicleID(userid));
            else 								PlayerSpectatePlayer(playerid, userid);
            
            SetInterior(playerid, GetInterior(userid));
            SetWorld(playerid, GetWorld(userid));

            MDC_Hide(playerid);

            SendSyntaxMessage(playerid, "/izlemeyibirak yazarak kiþiyi izlemeyi býrakabilirsin.");
        } else {
            Dialog_Show(playerid, MDCRecord, DIALOG_STYLE_INPUT, "{8D8DFF}MDC  - Ýddianame", "{B4B5B7}SUÇLAMA\n\nOnaylamak için kiþi adý girin:\n\nFormat Ad_Soyad þeklinde olmalýdýr ((veya oyuncu ID))", "Arat", "Geri Dön");
        }
        
        //**new mes[256];
        //format(mes, sizeof(mes), "{B4B5B7}ÏÐÅÄÚßÂËÅÍÈÅ ÎÁÂÈÍÅÍÈÉ\n\nÎáâèíÿåìûé: %s\n\nnÂâåäèòå òåêñò îáâèíåíèÿ: (( Ïðåñòóïëåíèå / 128 ñèìâîëîâ))", GetNameEx(pTemp[playerid][pMDCPlayer]));
        //Dialog_Show(playerid, MDCRecord2, DIALOG_STYLE_INPUT, "{8D8DFF}MDC - Ïðåäúÿâëåíèå îáâèíåíèÿ", mes, "Done", "Ýptal");
        return 1;
    }

    if (playertextid == MDC_LOOKUP_PERSON[playerid][5])
    {
        new query[255];
        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i LIMIT 1", GetPVarInt(playerid, #MDC_ID));
	    mysql_tquery(dbHandle, query, "MDC_LICENSE", "i", playerid);

        return 1;
    }

    if (playertextid == MDC_LOOKUP_PERSON[playerid][6]) // Ïðîñìîòð øòðàôîâ
    {
        new query[255];
        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `userid`=%i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 0);

        MdcInfo[playerid][mdcListPage] = 0;

        new Float:countticket = CountPlayerTicketsID(GetPVarInt(playerid, #MDC_ID));
        countticket = countticket/16;
        SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countticket, floatround_ceil));

        SetPVarInt(playerid, #MDC_FINE, 1);

        return 1;
    }

    if (playertextid == MDC_LOOKUP_PERSON[playerid][7]) // ÑÓÄÈÌÎÑÒÈ
    {
        new query[255];
        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `criminalrecords` WHERE `userid`=%i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 0);

        MdcInfo[playerid][mdcListPage] = 0;

        new Float:countticket = CountPlayerRecords(GetPVarInt(playerid, #MDC_ID));
        countticket = countticket/16;
        SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countticket, floatround_ceil));

        DeletePVar(playerid, #MDC_FINE);
        return 1;
    }

    if (playertextid == MDC_LOOKUP_PERSON[playerid][10]) // ÍÅÄÂÈÆÈÌÎÑÒÜ
    {
        if (GetPVarInt(playerid, "pDelay"))  return 1;

        new query[255];
        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `users` WHERE `id` = %i", GetPVarInt(playerid, #MDC_ID));
	    mysql_tquery(dbHandle, query, "MDC_MAP", "i", playerid);

        return 1;
    }
    
    for(new k = 1; k < 6; k++)
    {
        if (playertextid == MDC_OTHER_ADDRESS[playerid][k])
        {
            new h_id = MdcInfo[playerid][mdcList][0],
                strhouse[80],

                Float:map_kY = -0.04795376,
                Float:map_kX = 0.0469,

                Float:map_sX = 333.999420,
                Float:map_sY = 295.181152,

                Float:corX, Float:corY
            ;

            MdcInfo[playerid][mdcList][0] = MdcInfo[playerid][mdcList][k];
            MdcInfo[playerid][mdcList][k] = h_id;

            new dot = MdcInfo[playerid][mdcList][0];
            
            if (HouseInfo[dot][hPosX] >= 0.000000)
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit2");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit4");
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][0]);
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][1]);

                map_kX = 0.0469;
                map_sX = 333.999420;

                corX = HouseInfo[dot][hPosX] * map_kX + map_sX;
                corY = HouseInfo[dot][hPosY] * map_kY + map_sY;
            }
            else
            {
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][0], "samaps:gtasamapbit1");
                PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][1], "samaps:gtasamapbit3");
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][0]);
                PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][1]);

                map_kX = -0.0469;
                map_sX = 480.066314;

                corX = map_sX - HouseInfo[dot][hPosX] * map_kX;
                corY = HouseInfo[dot][hPosY] * map_kY + map_sY;
            }

            format(strhouse, sizeof(strhouse), "%s,~n~San Andreas", (!HouseInfo[MdcInfo[playerid][mdcList][0]][hApart])?(GetHouseZone(MdcInfo[playerid][mdcList][0], 1)):(GetApartmentZone(HouseInfo[MdcInfo[playerid][mdcList][0]][hApart], 1)));
            PlayerTextDrawSetString(playerid, MDC_ADDRESS[playerid][4], strhouse);
            
            PlayerTextDrawDestroy(playerid, MDC_ADDRESS[playerid][2]);
            MDC_ADDRESS[playerid][2] = PlayerText:INVALID_TEXT_DRAW;
            
            MDC_ADDRESS[playerid][2] = CreatePlayerTextDraw(playerid, corX, corY, "hud:radar_propertyG");
            PlayerTextDrawTextSize(playerid, MDC_ADDRESS[playerid][2], 5.000000, 6.000000);
            PlayerTextDrawFont(playerid, MDC_ADDRESS[playerid][2], 4);
            PlayerTextDrawShow(playerid, MDC_ADDRESS[playerid][2]);

            format(strhouse, sizeof(strhouse), "- %.35s", (!HouseInfo[h_id][hApart])?(GetHouseZone(h_id, 2)):(GetApartmentZone(HouseInfo[h_id][hApart], 2)));
            PlayerTextDrawSetString(playerid, MDC_OTHER_ADDRESS[playerid][k], strhouse);
        }
    }

    for(new i = 0; i < 3; i++)
    {
        if (playertextid == MDC_VEH_LIST_CLICK[playerid][i])
        {
            new query[156];
            mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `id` = %i AND `registered`=1 LIMIT 1", MdcInfo[playerid][mdcList][i]);
            mysql_tquery(dbHandle, query, "MDCSearchVehicle", "i", playerid);

            Update_MDC(playerid, PAGE_LOOKUP_VEHICLE);
            return 1;
        }
    }

    if (playertextid == MDC_LOOKUP_VEHICLES_ARROWS[playerid][1]) //+
    {
        new query[164];

        if (MdcInfo[playerid][mdcPage] == PAGE_MENU)
        {
            if (MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) 
               return 1;

            if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
            {
                if (GetPVarInt(playerid, #MDC_FINE)) {
                    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `userid`=%i AND `id` < %i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID), MdcInfo[playerid][mdcList][15]);
                    mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 0);
                    MdcInfo[playerid][mdcListPage]++;     
                } else {
                    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `criminalrecords` WHERE `userid`=%i AND `id` < %i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID), MdcInfo[playerid][mdcList][15]);
                    mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 0);
                    MdcInfo[playerid][mdcListPage]++;     
                }       
            }
            else if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_VEHICLE)
            {
                mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `id` < %i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID), MdcInfo[playerid][mdcList][15]);
                mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 0);
                MdcInfo[playerid][mdcListPage]++; 
            }
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_LOOKUP_VEHICLES_LIST)
        {
            if (MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;

            mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `owner` = %i AND `registered`=1 AND `id` > %i LIMIT 3", GetPVarInt(playerid, #MDC_OWNER_ID), MdcInfo[playerid][mdcList][2]);
            mysql_tquery(dbHandle, query, "MDCSearchVehiclesList", "i", playerid);
            
            MdcInfo[playerid][mdcListPage]++;
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            if (MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][apb]);

            new count,
                string[256],
                text[128]
            ;

            GetPVarString(playerid, #MDC_APB_TEXT, text, 128);           

            for(new i = MdcInfo[4][mdcList]-1; i >= 0; i--)
            {
                if (ApbInfo[i][apbOn] == 0) continue;
                
                if (count < 5)
                {
                    if (GetPVarInt(playerid, #MDC_APB_S))
                        if (strfind(ApbInfo[i][apbCharge], text, true) != -1) continue;

                    format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
                    PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][count*4+1], string);

                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
                }
                else break;
                count++;
            }
            
            MdcInfo[playerid][mdcListPage]++;
            
            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_CALLS)
        {
            if (MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][apb]);

            new 
                count,
                string[256]
            ;           

            for(new i = MdcInfo[4][mdcList]-1; i >= 0; i--)
            {
                if (CallInfo[i][callExists] == 0) continue;
                
                if (count < 5)
                {
                    new statusmes[65];
                    if (CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
                    else format(statusmes, sizeof(statusmes), "~r~CAGRI KABUL EDILMEMIS ");

                    switch(CallInfo[i][callType])
                    {
                        case 1: format(string, sizeof(string), "LSPD");
                        case 2: format(string, sizeof(string), "LSFD");
                        case 3: format(string, sizeof(string), "LSPD, LSFD");
                    }

                    format(string, sizeof(string), "%s (No: %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s", 
                        CallInfo[i][callName],
                        CallInfo[i][callPhone],
                        string,
                        CallInfo[i][callLocation],
                        CallInfo[i][callText],
                        (strlen(CallInfo[i][callText]) > 60)?(".."):(""),
                        CallInfo[i][callDate],
                        statusmes
                    );
                    PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][count*4+1], string);
                
                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_CALLS_TD[playerid][j]);
                    if (CallInfo[i][callAccept]) PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][count*4+2]);
                }
                else break;
                count++;
            }
            
            MdcInfo[playerid][mdcListPage]++;
            
            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_CCTV)
        {
            if (MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            MdcInfo[playerid][mdcListPage]++; 

            mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cctvs` WHERE `id` > %i ORDER BY `id` DESC LIMIT 16", MdcInfo[playerid][mdcList][15]);
            mysql_tquery(dbHandle, query, "MDC_ShowCCTVMenu", "ii", playerid, 0);
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_ROSTER)
        {
            if (MdcInfo[playerid][mdcListPage] == GetPVarInt(playerid, #MAX_MDC_PAGE)-1) return 1;
            MdcInfo[playerid][mdcListPage]++; 

            MDC_ShowRosterMenu(playerid);
            return 1;
        }
    }
    if (playertextid == MDC_LOOKUP_VEHICLES_ARROWS[playerid][2]) //--
    {
        if (!MdcInfo[playerid][mdcListPage]) return 1;

        new query[164];

        if (MdcInfo[playerid][mdcPage] == PAGE_MENU)
        {
            if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
            {
                if (GetPVarInt(playerid, #MDC_FINE)) {
                    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `userid`=%i AND `id` > %i LIMIT 16", GetPVarInt(playerid, #MDC_ID), MdcInfo[playerid][mdcList][0]);
                    mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 1);
                    MdcInfo[playerid][mdcListPage]--;
                } else {
                    mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `criminalrecords` WHERE `userid`=%i AND `id` > %i LIMIT 16", GetPVarInt(playerid, #MDC_ID), MdcInfo[playerid][mdcList][0]);
                    mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 1);
                    MdcInfo[playerid][mdcListPage]--;  
                }       
            }
            else if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_VEHICLE)
            {
                mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i AND `id` > %i LIMIT 16", GetPVarInt(playerid, #MDC_ID), MdcInfo[playerid][mdcList][0]);
                mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 1);
                MdcInfo[playerid][mdcListPage]--;
            }
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_LOOKUP_VEHICLES_LIST)
        {
            mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = cars.owner) as ownername FROM `cars` WHERE `owner` = %i AND `registered`=1 AND `id` < %i LIMIT 3", GetPVarInt(playerid, #MDC_OWNER_ID), MdcInfo[playerid][mdcList][0]);
            mysql_tquery(dbHandle, query, "MDCSearchVehiclesList", "i", playerid);
            MdcInfo[playerid][mdcListPage]--;
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_APB)
        {
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_APB_TD[playerid][apb]);

            new count,
                string[256],
                text[128]
            ;

            GetPVarString(playerid, #MDC_APB_TEXT, text, 128);

            for(new i = MdcInfo[0][mdcList]+1; i != MAX_APBS; i++)
            {
                if (ApbInfo[i][apbOn] == 0) continue;
                
                if (count < 5)
                {
                    if (GetPVarInt(playerid, #MDC_APB_S))
                        if (strfind(ApbInfo[i][apbCharge], text, true) != -1) continue;
                        
                    format(string, sizeof(string), "%s, #%i~n~%.60s%s~n~%s, %s", ApbInfo[i][apbSuspect], ApbInfo[i][apbID]+90214, ApbInfo[i][apbCharge], (strlen(ApbInfo[i][apbCharge]) > 60)?("_.."):("_"), ApbInfo[i][apbOfficer], ApbInfo[i][apbDate]);
                    PlayerTextDrawSetString(playerid, MDC_APB_TD[playerid][17 - count*4], string);

                    MdcInfo[4-count][mdcList] = i;
                    
                    for(new j = 19 - count*4; j > 19 - (count+1)*4; j--) PlayerTextDrawShow(playerid, MDC_APB_TD[playerid][j]);
                }
                else break;

                count++;
            }
            
            MdcInfo[playerid][mdcListPage]--;
            
            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        
        else if (MdcInfo[playerid][mdcPage] == PAGE_CALLS)
        {
            for(new apb = 0; apb < 20; apb++)  PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][apb]);

            new 
                count,
                string[256]
            ;           

            for(new i = MdcInfo[0][mdcList]+5; i != MAX_CALLS_AND_ARREST; i--)
            {
                if (CallInfo[i][callExists] == 0) continue;
                
                new statusmes[65];
                if (CallInfo[i][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[i][callAcceptBy]);
                else format(statusmes, sizeof(statusmes), "~r~CAGRI KABUL EDILMEMIS ");

                switch(CallInfo[i][callType])
                {
                    case 1: format(string, sizeof(string), "LSPD");
                    case 2: format(string, sizeof(string), "LSFD");
                    case 3: format(string, sizeof(string), "LSPD, LSFD");
                }

                if (count < 5)
                {
                    format(string, sizeof(string), "%s (No: %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s", 
                        CallInfo[i][callName],
                        CallInfo[i][callPhone],
                        string,
                        CallInfo[i][callLocation],
                        CallInfo[i][callText],
                        (strlen(CallInfo[i][callText]) > 60)?(".."):(""),
                        CallInfo[i][callDate],
                        statusmes
                    );
                    PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][count*4+1], string);

                    MdcInfo[count][mdcList] = i;

                    for(new j = count*4; j < count*4+4; j++) PlayerTextDrawShow(playerid, MDC_CALLS_TD[playerid][j]);
                    if (CallInfo[i][callAccept]) PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][count*4+2]);
                }
                else break;
                count++;
            }
            
            MdcInfo[playerid][mdcListPage]--;
            
            new strpage[7];
            format(strpage, sizeof(strpage), "%i_/_%i", MdcInfo[playerid][mdcListPage]+1, GetPVarInt(playerid, #MAX_MDC_PAGE));
            PlayerTextDrawSetString(playerid, MDC_LOOKUP_VEHICLES_ARROWS[playerid][0], strpage);
            return 1;
        }
        else if (MdcInfo[playerid][mdcPage] == PAGE_CCTV)
        {
            MdcInfo[playerid][mdcListPage]--;

            mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cctvs` WHERE `id` < %i LIMIT 16", MdcInfo[playerid][mdcList][0]);
            mysql_tquery(dbHandle, query, "MDC_ShowCCTVMenu", "ii", playerid, 1);
            return 1;
        }
         else if (MdcInfo[playerid][mdcPage] == PAGE_ROSTER)
            {
                MdcInfo[playerid][mdcListPage]--; 
                MDC_ShowRosterMenu(playerid);
                return 1;
            }
    }

    if (playertextid == MDC_LOOKUP_VEHICLE[playerid][7]) // ÎÁÜßÂÈÒÜ ÒÑ Â ÐÎÇÛÑÊ
    {
        new plates[24], query[156];
        GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `plate` = '%e' LIMIT 1", plates);
        mysql_tquery(dbHandle, query, "MDC_Veh_Wanted", "i", playerid);
        return 1;
    }

    if (playertextid == MDC_LOOKUP_VEHICLE[playerid][6]) //ÓÄÀËÈÒÜ ÇÀÌÅÒÊÓ");
    {
        new plates[24], query[156];
        GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `plate` = '%e' LIMIT 1", plates);
        mysql_tquery(dbHandle, query, "MDC_DELETE_NOTE", "i", playerid);
        return 1;
    }

    if (playertextid == MDC_LOOKUP_VEHICLE[playerid][5]) //ÄÎÁÀÂÈÒÜ ÇÀÌÅÒÊÓ");
    {
        new plates[24], query[156];
        GetPVarString(playerid, #MDC_VEHICLE_NUM, plates, 24);

        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `cars` WHERE `plate` = '%e' LIMIT 1", plates);
        mysql_tquery(dbHandle, query, "MDC_NEW_NOTE", "i", playerid);
        return 1;
    }

    if (playertextid == MDC_LOOKUP_VEHICLE[playerid][4]) // Ïðîñìîòð øòðàôîâ
    {
        new query[255];
        mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `tickets` WHERE `vehicle`=%i ORDER BY `id` DESC LIMIT 16", GetPVarInt(playerid, #MDC_ID));
        mysql_tquery(dbHandle, query, "MDC_ShowMenu", "ii", playerid, 0);

        MdcInfo[playerid][mdcListPage] = 0;

        new Float:countticket = CountVehicleTickets(GetPVarInt(playerid, #MDC_ID));
        countticket = countticket/16;
        SetPVarInt(playerid, #MAX_MDC_PAGE, floatround(countticket, floatround_ceil));

        SetPVarInt(playerid, #MDC_FINE, 1);
        
        return 1;
    }    

    for(new j = 0; j < 16; j++)
    {
        if (playertextid == MDC_LIST[playerid][j])
        {
            new query[156];

            if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_PERSON)
            {
                if (GetPVarInt(playerid, #MDC_FINE))
                {
                    mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = tickets.userid) as ownername FROM `tickets` WHERE `userid`=%i AND `id`=%i LIMIT 1", 
                        GetPVarInt(playerid, #MDC_ID), 
                        MdcInfo[playerid][mdcList][j]
                    );
                    return mysql_tquery(dbHandle, query, "MDC_ShowInfo", "i", playerid);
                }
                else 
                {
                    mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `name` FROM `users` WHERE id = criminalrecords.userid) as ownername FROM `criminalrecords` WHERE `userid`=%i AND `id`=%i LIMIT 1", 
                        GetPVarInt(playerid, #MDC_ID), 
                        MdcInfo[playerid][mdcList][j]
                    );
                    return mysql_tquery(dbHandle, query, "MDC_ShowInfo", "i", playerid);
                }
                
            }
            else if (MdcInfo[playerid][mdcMenu] == PAGE_LOOKUP_VEHICLE)
            {
                mysql_format(dbHandle, query, sizeof(query), "SELECT *, (SELECT `model` FROM `cars` WHERE id = tickets.vehicle) as vehiclemodel FROM `tickets` WHERE `vehicle`=%i AND `id`=%i LIMIT 1", 
                    GetPVarInt(playerid, #MDC_ID), 
                    MdcInfo[playerid][mdcList][j]);
                return mysql_tquery(dbHandle, query, "MDC_ShowInfo", "i", playerid);
            } 
            else if (MdcInfo[playerid][mdcPage] == PAGE_CCTV)
            {
                new factionid = PlayerInfo[playerid][pFaction];
                if (!IsPlayerInRangeOfPoint(playerid, 30.0, Factions[factionid][fPosX], Factions[factionid][fPosY], Factions[factionid][fPosZ])) {	
			        return SendErrorMessage(playerid, "Bu özelliði sadece departman içinde kullanabilirsin.");
                }

                new command[10], id;
                for(new cam = 0; cam < MAX_CCTV; cam++)
                {
                    if (CCTVInfo[cam][tvID] == MdcInfo[playerid][mdcList][j])
                    {
                        id = cam;
                        break;
                    }
                }
                if (id < 0 || id > MAX_CCTV-1 || !CCTVInfo[id][tvObjectOn]) return SendErrorMessage(playerid, "CCTV bulunamadý.");
		        if (CCTVInfo[id][tvBreak]) {
                    Waypoint_Set(playerid, CCTVInfo[id][tvPosX],CCTVInfo[id][tvPosY],CCTVInfo[id][tvPosZ], 3.0);
                    return SendErrorMessage(playerid, "Kamera kýrýlmýþ.");
                }
                
                format(command, sizeof(command), "goruntule %i", id);
                pc_cmd_cctv(playerid, command);
            }

            return 1;
        }
    }

    for(new r = 0; r < 18; r++)
    {
        if (playertextid == MDC_TD_MENU[playerid][r])
        {
            if (MdcInfo[playerid][mdcPage] == PAGE_ROSTER)
            {
                new count = -1;
                for(new i = 0; i != MAX_PATROL; i++)
                {
                    if (!PatrolInfo[GetPatrolID(playerid)][i][patrulExists]) continue;
                    
                    count++;
                    if (r == count)         break;
                    if(i == MAX_PATROL-1)   return 1;
                }

                if (count == -1) return 1;

                if (pTemp[playerid][pPatrol])
                {
                    pc_cmd_ekip(playerid, "");
                    return MDC_PAGE(playerid, PAGE_ROSTER);
                }

                new roster = MdcInfo[playerid][mdcList][count];
                if(roster > 18) return SendErrorMessage(playerid, "Sayfayý yenileyin!");

                if (PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] == INVALID_PLAYER_ID && 
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][1] == INVALID_PLAYER_ID)	{
                        return 1;
                }

                if (PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] != INVALID_PLAYER_ID && 
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][1] != INVALID_PLAYER_ID)	{
                        return SendErrorMessage(playerid, "Bu devriye sonlandýrýlmýþ.");
                }

                if (PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] == INVALID_PLAYER_ID) {
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][0] = playerid;
                } else {
                    PatrolInfo[GetPatrolID(playerid)][roster][patrulOfficer][1] = playerid;
                }

                pTemp[playerid][pPatrol] = roster+1;
                SendFactionMessageF(FACTION_POLICE, COLOR_POLICECHAT, "[Departman] %s %s isimli memur %s etiketi ile devriyeye katýldý.", GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][roster][patrulName]);

                MDC_PAGE(playerid, PAGE_ROSTER);
            } else if (MdcInfo[playerid][mdcPage] == PAGE_MEMBERS) {
                if(!GetBodyCamRight(playerid)) return SendErrorMessage(playerid, "Bu sayfayý görüntüleme yetkiniz yok. (( /izinlerim ))");

                new count = -1;
                foreach(new i : Player) {
                    if (IsPlayerLogged(i) == 0 || PlayerInfo[i][pFaction] != PlayerInfo[playerid][pFaction])	continue;
                    count++;
                    if (i == MdcInfo[playerid][mdcList][count]) break;
                }

                if(count == -1) return 1;
                if(pTemp[MdcInfo[playerid][mdcList][count]][tempStatus] == 1) MEMBERS_MAP(playerid, MdcInfo[playerid][mdcList][count]);
            }
            return 1;
        }
    }

    if (playertextid == MDC_TD_LEFT_PANEL[playerid][1])
    {
        if (MdcInfo[playerid][mdcMenu] == PAGE_ROSTER) {
            if (pTemp[playerid][pPatrol])
            {
                pc_cmd_ekip(playerid, "");
                MDC_PAGE(playerid, PAGE_ROSTER);
            }
            else Dialog_Show(playerid, MDC_ROSTER_CHANGE, DIALOG_STYLE_INPUT,"Callsign", "{FFFFFF}Yeni bir ekip kodu giriþi yapýn:", "Ekle", "Ýptal");
        } else if (MdcInfo[playerid][mdcMenu] == PAGE_MEMBERS) {
            if (pTemp[playerid][tempStatus] == 1) {
                pTemp[playerid][tempStatus] = 2;
                foreach(new p : Player) { if(pTemp[p][pSpecPlayer] == playerid) TogglePlayerSpectating(p, 0); }

                MDC_ShowMembersMenu(playerid);
            } else if (pTemp[playerid][tempStatus] == 2) {
                pTemp[playerid][tempStatus] = 1;
                
                MDC_ShowMembersMenu(playerid);
            }
        }
        return 1;
    }
    
    for(new apb = 0; apb < 5; apb++)
    {
        if (playertextid == MDC_APB_TD[playerid][2+4*apb]) // Äåòàëè
        {
            new
                mes[256],
                i_apb = MdcInfo[apb][mdcList]
            ;

            SetPVarInt(playerid, #MDC_ID, apb);

            format(mes, sizeof(mes), 
            "{a9c4e4}#%i\n\n\
            {a9c4e4}Þüpheli:{ffffff}\t %s\n\
            {a9c4e4}Açýklama:{ffffff}\t %s\n\n\
            {a9c4e4}Ekleyen memur:{ffffff}\t %s\n\
            {a9c4e4}Tarih:{ffffff}\t\t %s\n",
            ApbInfo[i_apb][apbID]+90214, 
            ApbInfo[i_apb][apbSuspect], 
            ApbInfo[i_apb][apbCharge], 
            ApbInfo[i_apb][apbOfficer], 
            ApbInfo[i_apb][apbDate]);

            Dialog_Show(playerid, MDC_APB_DETAIL, DIALOG_STYLE_MSGBOX, "{098d18}APB", mes, "Düzenle", "Ýptal");
        }
        else if (playertextid == MDC_APB_TD[playerid][3+4*apb]) // Óäàëèòü
        {
            SetPVarInt(playerid, #MDC_ID, MdcInfo[apb][mdcList]);
            ConfirmDialog(playerid, "Doðrulama", "{FFFFFF}APB kaydýný silmek istediðinize emin misiniz?", "MDC_DELETE_APB");
        }
        else if (playertextid == MDC_CALLS_TD[playerid][2+4*apb]) // handle
        {
            new 
                string[512],
                id = MdcInfo[apb][mdcList]
            ;
            
            if (pTemp[playerid][pPatrol])	SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* [%s] %s %s [%s] 911 hattýna düþen acil çaðrýyý yanýtladý. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetRankName(playerid), GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName], id+1);
            else							SendFactionMessageF(FACTION_POLICE, COLOR_LSPD, "* [%s] %s %s 911 hattýna düþen acil çaðrýyý yanýtladý. #%i.", GetInitials(Factions[PlayerInfo[playerid][pFaction]][fName]), GetRankName(playerid), GetNameEx(playerid), id+1);
            
            Waypoint_Set(playerid, CallInfo[id][callPosX],CallInfo[id][callPosY],CallInfo[id][callPosZ], 3.0);

            CallInfo[id][callAccept]++;
            pTemp[playerid][pPoliceCalls]++;

            switch(CallInfo[playerid][callType])
            {
                case 1: format(string, sizeof(string), "LSPD");
                case 2: format(string, sizeof(string), "LSFD");
                case 3: format(string, sizeof(string), "LSPD, LSFD");
            }

            if (pTemp[playerid][pPatrol]) format(CallInfo[id][callAcceptBy], 64, "Yonlendirilen: %s (%s)", GetNameEx(playerid), PatrolInfo[GetPatrolID(playerid)][pTemp[playerid][pPatrol]-1][patrulName]);
            else                          format(CallInfo[id][callAcceptBy], 64, "Yonlendirilen: %s", GetNameEx(playerid));
            
            format(string, sizeof(string), "%s (No: %i)~n~%s~n~%s~n~%.60s%s~n~%s~n~%s", CallInfo[id][callName], CallInfo[id][callPhone], string, CallInfo[id][callLocation], CallInfo[id][callText], (strlen(CallInfo[id][callText]) > 60)?(".."):(""), CallInfo[id][callDate], CallInfo[id][callAcceptBy]);
            PlayerTextDrawSetString(playerid, MDC_CALLS_TD[playerid][apb*4+1], string);

            PlayerTextDrawHide(playerid, MDC_CALLS_TD[playerid][apb*4 + 2]);
        }
        else if (playertextid == MDC_CALLS_TD[playerid][3+4*apb]) // details
        {
            new 
                mes[512], 
                id = MdcInfo[apb][mdcList]//, type = (PlayerInfo[playerid][pFaction] == LSFD)?(2):(1)
            ;

            new statusmes[65];
			if (CallInfo[id][callAccept]) format(statusmes, sizeof(statusmes), "%s", CallInfo[id][callAcceptBy]);
			else format(statusmes, sizeof(statusmes), "{A9C4E4}Çaðrý Kabul edilemedi{B4B5B7}");

            format(mes, sizeof(mes), "{B4B5B7}911-ÇAÐRI BÝLGÝLERÝ - #%i\n\n\
            						Arayan Bilgisi:\t\t%s\n\
            						Telefon numarasý:\t%i\n\
           							Olay:\t\t%s\n\
            						Lokasyon:\t%s\n\
            						Tarih:\t\t\t%s\n\n\
									Durum:\t\t\t%s\n\
            						Çaðrý %i saniyede kabul edildi",
            id+1, CallInfo[id][callName], CallInfo[id][callPhone], CallInfo[id][callText], CallInfo[id][callLocation], CallInfo[id][callDate], statusmes, CallInfo[id][callAccept]);
            
            Dialog_Show(playerid, MDCCall2, DIALOG_STYLE_MSGBOX, "{8D8DFF}MDC - çaðrý bilgileri", mes, "Ayarlar", "Geri");
            SetPVarInt(playerid, #last_call, id);
        }
    }
    
    for(new f = 0; f < 4; f++)
    {
        if (playertextid == MDC_LIC[playerid][5+7*f]) // ÈÇÚßÒÜ
        {
            SetPVarInt(playerid, #MDC_LIC, f);
            switch(f)
            {
                case 0: return ConfirmDialog(playerid, "Doðrulama", "{FFFFFF}Ehliyetinizi iptal etmek istediðinizden emin misiniz? ","MDC_LIC_LOADING");
                case 1: 
                {
                    if (PlayerInfo[playerid][pAuthwep] != 1) return SendErrorMessage(playerid, "Silah ruhsatýný iptal etme yetkin yok. ");
                    else    return ConfirmDialog(playerid, "Doðrulama", "{FFFFFF}Silah ruhsatýnýzý iptal etmek istediðinizden emin misiniz? ","MDC_LIC_LOADING");
                }
            }
            
        }
        
        if (playertextid == MDC_LIC[playerid][6+7*f]) // ÏÐÅÄÓÏÐÅÆÄÅÍÈÅ / ×ÅÐÍÛÉ ÑÏÈÑÎÊ
        {
            SetPVarInt(playerid, #MDC_LIC, f+4); 
            switch(f)
            {
                case 0: return ConfirmDialog(playerid, "Doðrulama", "{FFFFFF}\n Kiþiye ehliyet ceza puaný eklemek istediðinize emin misiniz? ","MDC_LIC_LOADING");
                case 1: return ConfirmDialog(playerid, "Doðrulama", "{FFFFFF}\n Kiþinin ruhsatýna uyarý eklemek ister misiniz? ","MDC_LIC_LOADING");
            }
        }
    }
    return 1;
}
