Biz_OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
    for(new i = 0; i < MAX_BIZ; i++)
	{
	    if (pickupid != BizInfo[i][bizPickUp] || 0 == BizInfo[i][bizID]) continue;

		if (pTemp[playerid][pTruckerOn] && pTemp[playerid][pTruckerOn]-1 == i && IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))
		{
			if(gettime() - pTemp[playerid][pTruckerTime] < 5) return KickLine(playerid, "Þüpheli teslimattan dolayý oyundan atýldýnýz. Kod: 101");

			new ucret = pTemp[playerid][pTruckerPrice];
			new bahsis = randomEx(1, 30);
			new kariyer = PlayerInfo[playerid][pCareer];
			new verilecek = ucret + bahsis + kariyer;

			SendSyntaxMessage(playerid, "Teslimat ücreti olarak %d$, bahþiþ olarak %d$, kariyer bonusu olarak %d$ kazandýn.", pTemp[playerid][pTruckerPrice], bahsis, kariyer);
            SendServerMessage(playerid, "Tekrar /tasimacilik yazarak yeni teslimat noktasý belirleyebilirsin.");
			GiveCash(playerid, verilecek);
            RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);

			pTemp[playerid][pTruckerOn] = 0;
			pTemp[playerid][pTruckerPrice] = 0;
			pTemp[playerid][pTruckerTime] = 0;			
			return 1;
		}

		new 
			title[128],
			mes[128]
		;

	    if (BizInfo[i][bizFreeze] == 1) //èíôî
	    {
	        format(title, sizeof(title), "~h~~p~%s (%i)~n~~y~Liberty City", TurkishCharFix(BizInfo[i][bizName]), i);
			format(mes, sizeof(mes), "~w~Giris ucreti: ~g~$%i~n~~w~~y~/giris~w~ veya ~y~~h~Y tusuna basarak girebilirsin", BizInfo[i][bizEntrance]);

			CreateLableText(playerid, title, mes);
			return 1;
	    }
	    else
	    {
	        if (BizInfo[i][bizOwnerID] == 0)
			{
				format(title, sizeof(title), "~h~~p~SATILIK MEKAN!~n~~w~%s (%i)", TurkishCharFix(BizInfo[i][bizName]), i);
				format(mes, sizeof(mes), "~w~Ucret: ~g~$%i~n~~w~~y~~h~Y~w~ tusuna basin veya ~y~/mekan satinal", BizInfo[i][bizPrice]);

				CreateLableText(playerid, title, mes);
			}
			else
			{
				format(title, sizeof(title), "~h~~p~%s (%i)~n~~w~~y~%s", TurkishCharFix(BizInfo[i][bizName]), i, BizInfo[i][bizOwner]);
				format(mes, sizeof(mes), "~w~Giris ucreti: ~g~$%i~n~~w~~y~/giris~w~ veya ~y~~h~Y tusuna basarak girebilirsin", BizInfo[i][bizEntrance]);
				
				CreateLableText(playerid, title, mes);
			}
			return 1;
	    }
	}
    return 1;
}

Biz_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT *, (SELECT name FROM users WHERE id = business.owner) as ownername, (SELECT last_login FROM users WHERE id = business.owner) as last_login FROM `business`", "LoadDynamicBiz");
}

Fo_OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid) 
{
    for(new i; i != 4; i++)
	{
	    if (playertextid != TD_restaurant_prod[playerid][i + 4])	continue;

        RestaurantMenuHide(playerid);

        if (pTemp[playerid][pFoodStand] != 0 || IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))	return SendWarningMessage(playerid, "Elleriniz dolu.");

		new bizid;

		if ((bizid = GetNearInsideBiz(playerid)) == -1)	return SendErrorMessage(playerid, "Mekanýn içerisinde olmalýsýnýz.");

		if (BizInfo[bizid][bizType] != BIZ_PIZZA && BizInfo[bizid][bizType] != BIZ_CLUCKIN && BizInfo[bizid][bizType] != BIZ_BURGER && BizInfo[bizid][bizType] != BIZ_DONUT)
		{
			return SendErrorMessage(playerid, "Restoranda deðilsiniz.");
		}

		new type = BizInfo[bizid][bizType] - BIZ_PIZZA;

		if (GetCash(playerid) < BizInfo[bizid][bizProductPrice][i])			return SendNotCash(playerid);
		if (BizInfo[bizid][bizOwnerID] != 0 && !BizInfo[bizid][bizProduct])	return SendErrorMessage(playerid, "Bu mekanda yeterince ürün yok.");
		    
        pc_cmd_server_ame(playerid, "yemek sipariþi verir.");

        SendSyntaxMessage(playerid, "{FF6347}%s{FFFFFF} adlý yemeði sipariþ verdiniz ve {FF6347}$%s{FFFFFF} ödediniz.", name_order[type][i], FormatNumber(BizInfo[bizid][bizProductPrice][i]));
		SendSyntaxMessage(playerid, "{FF6347}/yemek tepsiyerlestir{FFFFFF} ile yemeði masaya koyabilir veya {FF6347}/yemek cop{FFFFFF} ile çöpe atabilirsiniz.");

		GiveCash(playerid, - BizInfo[bizid][bizProductPrice][i]);

		if (BizInfo[bizid][bizOwnerID] != 0)
		{
			BizInfo[bizid][bizProduct]--;
			GiveBizCash(bizid, BizInfo[bizid][bizProductPrice][i]);
		}
		
		OnPlayAnim(playerid,"CARRY","crry_prtial",4.1,1,1,1,1,1);
		SetPlayerAttachedObject(playerid, ATTACH_HANDS, model_order[type][i], 5, 0.091998, 0.021999, 0.409, -104.9, 27.6, 0, 1, 1, 1);
		pTemp[playerid][pFoodStand] = model_order[type][i];

		new Float: health;

		if (AntiCheatGetHealth(playerid, health))	PlayerInfo[playerid][pHealth] = health + 30.0 + (i * 10.0);
		if (health + 30.0 + (i * 10.0) > 150.0)		PlayerInfo[playerid][pHealth] = 150.0;

		return 1;
	}
    return 1;
}

Food_OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	new Float:oldX, Float:oldY, Float:oldZ, Float:oldRotX, Float:oldRotY, Float:oldRotZ;
	
	GetDynamicObjectPos(objectid, oldX, oldY, oldZ);
	GetDynamicObjectRot(objectid, oldRotX, oldRotY, oldRotZ);

    if (GetPVarInt(playerid, #edit_food) != 0 && (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL))
	{
	    new id = GetPVarInt(playerid, #edit_food)-1;
		
	    DeletePVar(playerid, #edit_food);

	    if (GetDistanceBetweenPoints(x, y, z, FoodDrop[id][foodPosX], FoodDrop[id][foodPosY], FoodDrop[id][foodPosZ]) > 10.0)
	    {
     		SetDynamicObjectPos(objectid, FoodDrop[id][foodPosX], FoodDrop[id][foodPosY], FoodDrop[id][foodPosZ]);
	        return SendErrorMessage(playerid, "Düzenlediðiniz pozisyon sizden çok uzakta.");
	    }

	    if (objectid != FoodDrop[id][foodObject])	return SendErrorMessage(playerid, "Objeyi düzenlerken hata oluþtu.");
		SetDynamicObjectPos(objectid, x, y, z);
		SetDynamicObjectRot(objectid, rx, ry, rz);

        GetDynamicObjectPos(objectid, FoodDrop[id][foodPosX], FoodDrop[id][foodPosY], FoodDrop[id][foodPosZ]);
	    return 1;
	}
	return 1;
}