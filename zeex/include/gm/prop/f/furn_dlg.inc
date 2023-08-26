Dialog:FurnitureDialog(playerid, response, listitem, inputtext[])
{
	if (!response)	return pTemp[playerid][pFurniture] = -1;
	 
	switch(listitem)
	{
	    case 0: return ShowFurnitureCategories(playerid);
	    case 1: return Dialog_Show(playerid, CategoryEditFurniture, DIALOG_STYLE_LIST, "{FFFFFF}Mobilya Düzenle", "Fare ile düzenle\nMobilya Listesi", "Seç", "Geri Dön");
		case 2:
		{
            if (!GetFurnitures(playerid)) return SendErrorMessage(playerid, "Mobilya satýn alýnmamýþ.");
			Dialog_Show(playerid, HandleSellFurnitures, DIALOG_STYLE_MSGBOX, "{FFFFFF}Tüm mobilyalarý sat", "{ffffff}Tüm mobilyalarý satmak istediðinize emin misiniz?", "Sat", "Ýptal");
		}
	}
	return 1;
}

Dialog:FurnitureCategories(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_dekorasyon(playerid, "");
	if (listitem == 28 && GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) == -1)		return SendErrorMessage(playerid, "Bu mobilyayý satýn almak için dýþarýda olmalýsýnýz. ");
    else if (listitem != 28 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) == -1)	return SendErrorMessage(playerid, "Bu mobilyayý satýn almak için içeride olmalýsýnýz. ");
	    
	FurnBuingDialog(playerid, listitem);
 	return 1;
}


Dialog:CategoryEditFurniture(playerid, response, listitem, inputtext[])
{
	if (!response)   return pc_cmd_dekorasyon(playerid, "");
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;

	new furnitures = GetFurnitures(playerid);

	if (!furnitures) return SendErrorMessage(playerid, "Mobilyanýz yok.");

	if (!listitem)
	{
	    SelectObject(playerid);
     	SendErrorMessage(playerid, "Fare ile týklayarak mobilyalardan birini seçiniz.");
	    return 1;
	}

    ShowFurnitureList(playerid);
	return 1;
}

Dialog:FurnitureList(playerid, response, listitem, inputtext[])
{
	if (!response)	return pc_cmd_dekorasyon(playerid, "");
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;

	new building = pTemp[playerid][pFurniture],
	    count,
		FName[64],
	    list = pTemp[playerid][pDialogList];

	if (!listitem && list)																		 return ShowFurnitureList(playerid, list-1);
	if ((listitem == MAX_FURNITURE_LIST && !list) || (listitem == MAX_FURNITURE_LIST+1 && list)) return ShowFurnitureList(playerid, list+1);
	if (list)																					 listitem -= 1;
	
	new start_itter = MAX_FURNITURE_LIST * list;
	
	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!HFurn[building][i][fOn] || !IsValidDynamicObject(HFurn[building][i][fObject])) continue;
					
				if (count == listitem + start_itter)
				{
					count = i;
					break;
				}
				count++;
			}

			if (HFurn[building][count][fVirtualWorld] != GetWorld(playerid) || HFurn[building][count][fInterior] != GetInterior(playerid)) 
			{
				return SendErrorMessage(playerid, "Bu mobilya dýþarýda, düzenlemek için dýþarýya çýkýnýz.");
			}

			SetPVarInt(playerid, "chose_slot", count);
			format(FName, sizeof(FName), "%s", HFurn[building][count][fName]);
		} case 1: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!BFurn[building][i][fOn] || !IsValidDynamicObject(BFurn[building][i][fObject])) continue;
					
				if (count == listitem + start_itter)
				{
					count = i;
					break;
				}
				count++;
			}

			if (BFurn[building][count][fVirtualWorld] != GetWorld(playerid) || BFurn[building][count][fInterior] != GetInterior(playerid)) 
			{
				return SendErrorMessage(playerid, "Bu mobilya dýþarýda, düzenlemek için dýþarýya çýkýnýz.");
			}

			SetPVarInt(playerid, "chose_slot", count);
			format(FName, sizeof(FName), "%s", BFurn[building][count][fName]);
		} case 2: {
			for(new i; i < MAX_FURNITURE; i++)
			{
				if (!GFurn[building][i][fOn] || !IsValidDynamicObject(GFurn[building][i][fObject])) continue;
					
				if (count == listitem + start_itter)
				{
					count = i;
					break;
				}
				count++;
			}

			if (GFurn[building][count][fVirtualWorld] != GetWorld(playerid) || GFurn[building][count][fInterior] != GetInterior(playerid)) 
			{
				return SendErrorMessage(playerid, "Bu mobilya dýþarýda, düzenlemek için dýþarýya çýkýnýz.");
			}

			SetPVarInt(playerid, "chose_slot", count);
			format(FName, sizeof(FName), "%s", GFurn[building][count][fName]);
		}
	}

 	Dialog_Show(playerid, EditFurniture, DIALOG_STYLE_LIST, FName, "Bilgi\nPozisyon deðiþtir\nTexture düzenle\nSat\nÝsim deðiþtir\nKopyala", "Seç", "Geri Dön");
	return 1;
}

Dialog:HandleEditTexture(playerid, response, listitem, inputtext[])
{
	if (!response) return CallRemoteFunction("ShowEditFurniture", "i", playerid);

    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;

	new building = pTemp[playerid][pFurniture], slot = GetPVarInt(playerid, "chose_slot");

	if (listitem < 5)
	{
		new title[32];

		format(title, 32, "Texture (%i)", listitem+1);
 		Dialog_Show(playerid, HandleEditTexture2, DIALOG_STYLE_LIST, title, "Texture deðiþtir\nTexture kaldýr", "Seç", "Geri Dön");
        SetPVarInt(playerid, "chose_texture", listitem);
		return 1;
	}

	new name[64], furnid;

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			format(name, sizeof(name), "%s", HFurn[building][GetPVarInt(playerid, "chose_slot")][fName]);
			furnid = HFurn[building][slot][fID];
			for(new i; i < 5; i++)
			{
				HFurn[building][slot][fTexture][i] = -1;
				SetDynamicObjectMaterial(HFurn[building][slot][fObject], i, -1, "none", "none", 0);
			}
		} case 1: { 
			format(name, sizeof(name), "%s", BFurn[building][GetPVarInt(playerid, "chose_slot")][fName]);
			furnid = BFurn[building][slot][fID];
			for(new i; i < 5; i++)
			{
				BFurn[building][slot][fTexture][i] = -1;
				SetDynamicObjectMaterial(BFurn[building][slot][fObject], i, -1, "none", "none", 0);
			}
		} case 2: {
			format(name, sizeof(name), "%s", GFurn[building][GetPVarInt(playerid, "chose_slot")][fName]);
			furnid = GFurn[building][slot][fID];

			for(new i; i < 5; i++)
			{
				GFurn[building][slot][fTexture][i] = -1;
				SetDynamicObjectMaterial(GFurn[building][slot][fObject], i, -1, "none", "none", 0);
			}
		}
	}

 	SendSyntaxMessage(playerid, "%s adlý eþyanýn tüm dokularý sýfýrlandý.", name);

	new query[256];

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_0`=-1,`texture_1`=-1,`texture_2`=-1,`texture_3`=-1,`texture_4`=-1 WHERE `id`=%i",furnid);
	mysql_tquery(dbHandle, query);

	return 1;
}

Dialog:HandleEditTexture2(playerid, response, listitem, inputtext[])
{
	if (!response)	return CallRemoteFunction("ShowEditFurniture", "i", playerid);

    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1)) return 1;

	new building = pTemp[playerid][pFurniture], slot = GetPVarInt(playerid, "chose_slot"), texture = GetPVarInt(playerid, "chose_texture");

	switch(listitem)
	{
	    case 0:
		{
		    new Float:x, Float:y, Float:z, Float:facing, Float:distance = 3.0;

		    GetPlayerPos(playerid, x, y, z);
		    GetPlayerFacingAngle(playerid, facing);

		    SCM(playerid, COLOR_SERVER2, "* Texture Menüsü Hakkýnda Bilgi");
	        SCM(playerid, COLOUR_ALTO, "Y ve N tuþlarý ile tasarýmlar arasýnda geçiþ yapabilirsin.");
	        SCM(playerid, COLOUR_ALTO, "H tuþuna basarak texture slotlarý arasýnda geçiþ yaparsýn.");
	        SCM(playerid, COLOUR_ALTO, "Seçmek istediðiniz tasarýmý SPACE tuþu ile seçebilirsiniz.");
            SCM(playerid, COLOUR_ALTO, "Menüden çýkmak için ENTER tuþuna basmanýz yeterlidir.");		

		  	x += (distance * floatsin(-facing, degrees));
		    y += (distance * floatcos(-facing, degrees));
            InfoMSG(playerid, "~w~\" ~y~Y ~w~\" ve \" ~y~N ~w~\" tuslari ile texture menusunde gezebilirsiniz. ~n~\" ~y~H ~w~\" - tusu ile slot degistirebilir, ~n~\" ~y~SPACE~w~ \" - tusuyla texture secebilir ~n~\" ~y~ENTER ~w~\" tusuyla iptal edebilirsiniz.", 20);
			pTemp[playerid][p3DMenu] = Create3DMenu(playerid, x, y, z, facing, 16);
		    Select3DMenu(playerid, pTemp[playerid][p3DMenu]);
			return 1;
		}
		case 1:
	    {
			switch(pTemp[playerid][pFurnitureB])
			{
				case 0: {
					if (HFurn[building][slot][fTexture][texture] == -1)	return SendErrorMessage(playerid,"Bu texture kullanýlamaz.");
					SendSyntaxMessage(playerid, "%s adlý mobilyanýn texturesi [ID: %i] silindi.", HFurn[building][slot][fName], texture+1);

					new query[256];
					mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_%i` = -1 WHERE `id` = %i", texture, HFurn[building][slot][fID]);
					mysql_tquery(dbHandle, query);

					HFurn[building][slot][fTexture][texture] = -1;
					SetDynamicObjectMaterial(HFurn[building][slot][fObject], texture, -1, "none", "none", 0);
				} case 1: {
					if (BFurn[building][slot][fTexture][texture] == -1)	return SendErrorMessage(playerid, "Bu texture kullanýlamaz.");
					SendSyntaxMessage(playerid, "%s adlý mobilyanýn texturesi [ID: %i] silindi.", BFurn[building][slot][fName], texture+1);

					new query[256];
					mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_%i` = -1 WHERE `id` = %i", texture, BFurn[building][slot][fID]);
					mysql_tquery(dbHandle, query);

					BFurn[building][slot][fTexture][texture] = -1;
					SetDynamicObjectMaterial(BFurn[building][slot][fObject], texture, -1, "none", "none", 0);
				} case 2: {
					if (GFurn[building][slot][fTexture][texture] == -1)	return SendErrorMessage(playerid, "Bu texture kullanýlamaz.");
					SendSyntaxMessage(playerid, "%s adlý mobilyanýn texturesi [ID: %i] silindi.", GFurn[building][slot][fName], texture+1);

					new query[256];
					mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `texture_%i` = -1 WHERE `id` = %i", texture, GFurn[building][slot][fID]);
					mysql_tquery(dbHandle, query);

					GFurn[building][slot][fTexture][texture] = -1;
					SetDynamicObjectMaterial(GFurn[building][slot][fObject], texture, -1, "none", "none", 0);
				}
			}
	        return 1;
	    }
	}
	return 1;
}

Dialog:InformationFurniture(playerid, response, listitem, inputtext[])
{
    return CallRemoteFunction("ShowEditFurniture", "i", playerid);
}

Dialog:EditFurniture(playerid, response, listitem, inputtext[])
{
	if (!response)   return pc_cmd_dekorasyon(playerid, "");
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;

	new building = pTemp[playerid][pFurniture], 
        slot = GetPVarInt(playerid, "chose_slot");

	new FCat, name[64], f_price, f_obj, f_vw, f_int;

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			format(name, sizeof(name), "%s", HFurn[building][slot][fName]);
			FCat = HFurn[building][slot][fCategory];
			f_price = HFurn[building][slot][fMarketPrice]; 
			f_obj = HFurn[building][slot][fObject];
			f_vw = HFurn[building][slot][fVirtualWorld];
			f_int = HFurn[building][slot][fInterior];
		} case 1: { 
			format(name, sizeof(name), "%s", BFurn[building][slot][fName]);
			FCat = BFurn[building][slot][fCategory];
			f_price = BFurn[building][slot][fMarketPrice]; 
			f_obj = BFurn[building][slot][fObject];
			f_vw = BFurn[building][slot][fVirtualWorld];
			f_int = BFurn[building][slot][fInterior];
		} case 2: { 
			format(name, sizeof(name), "%s", GFurn[building][slot][fName]);
			FCat = GFurn[building][slot][fCategory];
			f_price = GFurn[building][slot][fMarketPrice]; 
			f_obj = GFurn[building][slot][fObject];
			f_vw = GFurn[building][slot][fVirtualWorld];
			f_int = GFurn[building][slot][fInterior];
		}
	}

    if (f_vw != GetWorld(playerid) || f_int != GetInterior(playerid)) return SendErrorMessage(playerid, "Bu mobilya dýþarýda, düzenlemek için dýþarýya çýkýnýz.");
	    		
	switch(listitem)
	{
	    case 0:
	    {
	        new mes[228];

			format(mes, sizeof(mes), "{C3C3C3}Kategori:\t{ffffff}%s\n{C3C3C3}Ýsim:\t{ffffff}%s\n{C3C3C3}Fiyat:\t{ffffff}$%s", furniture_title[FCat], name, FormatNumber(f_price));
			Dialog_Show(playerid, InformationFurniture, DIALOG_STYLE_MSGBOX, "{FFFFFF}Bilgi", mes, "Geri Dön", "");
	        return 1;
	    }
	    case 1:
	    {
            InfoMSG(playerid, "Mobilyayi kendinize yaklastirmak icin \" ~y~SPACE ~w~\" ve \" ~y~MMB ~w~\" tuslarina basin. ~n~Islemi geri almak icin \" ~r~ESC ~w~\" tusuna basin", 5);
	        SetPVarInt(playerid, "edit_furniture", 1);
			EditDynamicObject(playerid, f_obj);
	        return 1;
	    }
	    case 2:
	    {
	        new str_tex[256], tex_name[5][32] = {"Boþ", "Boþ", "Boþ", "Boþ", "Boþ"}; //Ïóñòî

			switch(pTemp[playerid][pFurnitureB])
			{
				case 0: for(new i; i != 5; i++) if (HFurn[building][slot][fTexture][i] != -1) format(tex_name[i], 32, "%s", GetTextureName(HFurn[building][slot][fTexture][i]));
				case 1: for(new i; i != 5; i++) if (BFurn[building][slot][fTexture][i] != -1) format(tex_name[i], 32, "%s", GetTextureName(BFurn[building][slot][fTexture][i]));
				case 2: for(new i; i != 5; i++) if (GFurn[building][slot][fTexture][i] != -1) format(tex_name[i], 32, "%s", GetTextureName(GFurn[building][slot][fTexture][i]));
			}			

			format(str_tex, sizeof(str_tex), "{FFFFFF}Texture 1: {C3C3C3}%s\n{FFFFFF}Texture 2: {C3C3C3}%s\n{FFFFFF}Texture 3: {C3C3C3}%s\n{FFFFFF}Texture 4: {C3C3C3}%s\n{FFFFFF}Texture 5: {C3C3C3}%s\n{FF6347}> Texture kaldýr", tex_name[0], tex_name[1], tex_name[2], tex_name[3], tex_name[4]);
	        Dialog_Show(playerid, HandleEditTexture, DIALOG_STYLE_LIST, "{FFFFFF}Texture deðiþtir", str_tex, "Seç", "Geri Dön");
			return 1;
	    }
	    case 3:
	    {
            new mes[268], sellprice = (f_price - (f_price & 2))  / 2;

			format(mes, sizeof(mes), "{C3C3C3}Kategori:\t{ffffff}%s\n{C3C3C3}Ýsim:\t{ffffff}%s\n{C3C3C3}Fiyat:\t{ffffff}$%s\n\n{FF6347}Geri ödeme miktarý: $%s", furniture_title[FCat], name, FormatNumber(f_price), FormatNumber(sellprice));
			Dialog_Show(playerid, HandleSellFurniture, DIALOG_STYLE_MSGBOX, "{FFFFFF}Sat", mes, "Sat", "Geri Dön");
	        return 1;
	    }
		case 4:
		{
		    Dialog_Show(playerid, FurnitureRename, DIALOG_STYLE_INPUT, name, "\t{ffffff}Mobilyaya yeni bir isim giriniz:\t\n\t- Minimum 1 karakter.\t\n\t- Maksimum 32 karakter.\t", "Düzenle", "Geri Dön");
			return 1;
		}
		case 5:
		{
		    new mes[228];
			format(mes, sizeof(mes), "{C3C3C3}Kategori:\t{ffffff}%s\n{C3C3C3}Ýsim:\t{ffffff}%s\n{C3C3C3}Fiyat:\t{ffffff}$%s\n{ffffff}", furniture_title[FCat], name, FormatNumber(f_price));
		    Dialog_Show(playerid, CopyFurniture, DIALOG_STYLE_MSGBOX, "{FFFFFF}Kopyala", mes, "Satýn al", "Geri Dön");
		}
	}
	return 1;
}

Dialog:FurnitureRename(playerid, response, listitem, inputtext[])
{
	if (!response)																																												return 1;
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;

	new building = pTemp[playerid][pFurniture], slot = GetPVarInt(playerid, "chose_slot"), f_id, name[64];

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			format(name, sizeof(name), "%s", HFurn[building][slot][fName]);
			f_id = HFurn[building][slot][fID];
		} case 1: { 
			format(name, sizeof(name), "%s", BFurn[building][slot][fName]);
			f_id = BFurn[building][slot][fID];
		} case 2: { 
			format(name, sizeof(name), "%s", GFurn[building][slot][fName]);
			f_id = GFurn[building][slot][fID];
		}
	}

	if (strlen(inputtext) < 1 || strlen(inputtext) > 32)
	{
	    Dialog_Show(playerid, FurnitureRename, DIALOG_STYLE_INPUT, name, "\t\t{ffffff}Mobilyaya yeni bir isim giriniz:\t\t\n\t\t\t - Minimum 1 karakter.\t\t\n\t\t\t - Maksimum 32 karakter.\t\t", "Düzenle", "Geri Dön");
		return SendErrorMessage(playerid, "Ýsim minimum 1, maksimum 32 karakter olmalýdýr.");
	}

	SendSyntaxMessage(playerid, "Mobilyanýn ismi deðiþtirildi, eski: %s{ffffff} yeni: %s.", name, inputtext);
    format(name, 32, "%s", inputtext);

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			format(HFurn[building][slot][fName], 32, name);
		} case 1: { 
			format(BFurn[building][slot][fName], 32, name);
		} case 2: { 
			format(GFurn[building][slot][fName], 32, name);
		}
	}
    
	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `furnitures` SET `name` = '%e' WHERE `id` = %i", name, f_id);
	mysql_tquery(dbHandle, query);
	return 1;
}
	
Dialog:BuyFurniture(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
        FurnBuingDialog(playerid, GetPVarInt(playerid, "category_furniture"));
	    return 1;
	}

    if (pTemp[playerid][pFurniture] == -1) return 1;

    new building = pTemp[playerid][pFurniture], 
        index = GetPVarInt(playerid, "furniture_index");

    listitem = GetPVarInt(playerid, "category_furniture");

    if (GetCash(playerid) < furniture_list[listitem][index][frPrice]) 								  return SendNotCash(playerid);
    if (listitem == 28 && GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) == -1)	     	  return SendErrorMessage(playerid, "Bu mobilyayý satýn almak için dýþarýda olmalýsýnýz.");
    else if (listitem != 28 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) == -1)		  return SendErrorMessage(playerid, "Bu mobilyayý satýn almak için içeride olmalýsýnýz.");
    if (GetFurnitures(playerid) >= GetMaxPlayerFurniture(playerid))   								  return SendErrorMessage(playerid, "Maksimum mobilya sýnýrýna ulaþtýnýz.");
    if (listitem == 28 && GetOutsideFurnitures(playerid) >= 9 && GetOutsideFurnitures(playerid) <= 0) return SendErrorMessage(playerid, "Dýþarýya maksimum 10 adet mobilya koyabilirsiniz.");
		
    new i = -1;

	switch(pTemp[playerid][pFurnitureB]) {
		case 0: {
			for(new a; a < MAX_FURNITURE; a++)
			{
				if (HFurn[building][a][fOn]) continue;
				
				i = a;
				break;
			}
		} case 1: {
			for(new a; a < MAX_FURNITURE; a++)
			{
				if (BFurn[building][a][fOn]) continue;
				
				i = a;
				break;
			}
		} case 2: {
			for(new a; a < MAX_FURNITURE; a++)
			{
				if (GFurn[building][a][fOn]) continue;
				
				i = a;
				break;
			}
		}
	}

	if (i == -1) return 1;

	SetPVarInt(playerid, "buy_furniture", 1);

	new Float:x, Float:y, Float:z;
    GetXYInFrontOfPlayer(playerid, x, y, z, 3.0);
	
	switch(pTemp[playerid][pFurnitureB]) {
		case 0: OnPlayerCallBuyFurniture(playerid, building, 0, i, furniture_list[listitem][index][frModel], listitem, index, x, y, z-1.0);
		case 1: OnPlayerCallBuyFurniture(playerid, building, 1, i, furniture_list[listitem][index][frModel], listitem, index, x, y, z-1.0);
		case 2: OnPlayerCallBuyFurniture(playerid, building, 2, i, furniture_list[listitem][index][frModel], listitem, index, x, y, z-1.0);
	}
	return 1;
}

Dialog:CopyFurniture(playerid, response, listitem, inputtext[])
{
	if (!response)
		return CallRemoteFunction("ShowEditFurniture", "i", playerid);

    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))
		return 1;

	if (GetFurnitures(playerid) >= GetMaxPlayerFurniture(playerid))
		return SendErrorMessage(playerid, "Maksimum mobilya sýnýrýna ulaþtýnýz.");

    new building = pTemp[playerid][pFurniture], slot = GetPVarInt(playerid, "chose_slot");

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: HouseFurnCopy(playerid, building, slot);
		case 1: BizFurnCopy(playerid, building, slot);
		case 2: GarageFurnCopy(playerid, building, slot);
	}	
	
	return 1;
}

Dialog:HandleSellFurnitures(playerid, response, listitem, inputtext[])
{
	if (!response)																																												return pc_cmd_dekorasyon(playerid, "");
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;
    	
	new building = pTemp[playerid][pFurniture];

	if (HouseInfo[building][hOwnerID] != PlayerInfo[playerid][pID] && pTemp[playerid][pBuildHouse] != HouseInfo[building][hID])	return SendErrorMessage (playerid, "Evin kendi mobilyalarýný deðiþtiremezsiniz.");
    if (GetPVarInt(playerid, "buy_furniture"))																					return SendErrorMessage (playerid, "Bu iþlemi þu an yapýyorsunuz.");
        
	switch(pTemp[playerid][pFurnitureB]) {
		case 0: HouseHandleSellFurn(playerid, building);
		case 1: BizHandleSellFurn(playerid, building);
		case 2: GarageHandleSellFurn(playerid, building);
	}	
	return 1;
}

Dialog:HandleSellFurniture(playerid, response, listitem, inputtext[])
{
    if (!response)	return CallRemoteFunction("ShowEditFurniture", "i", playerid);
    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1))	return 1;
    	
	new building = pTemp[playerid][pFurniture], name[64], f_price, slot = GetPVarInt(playerid, "chose_slot");

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			if (!HFurn[building][slot][fOn])	return SendErrorMessage(playerid, "Bu slotta satýn alýnmýþ bir þey yok, boþ.");
			if (HouseInfo[building][hOwnerID] != PlayerInfo[playerid][pID] && pTemp[playerid][pBuildHouse] != HouseInfo[building][hID])	return SendErrorMessage(playerid, "Evin kendi mobilyalarýný deðiþtiremezsiniz.");
			
			f_price = HFurn[building][slot][fMarketPrice];
			format(name, sizeof(name), "%s", HFurn[building][slot][fName]);
		} case 1: {
			if (!BFurn[building][slot][fOn])	return SendErrorMessage(playerid, "Bu slotta satýn alýnmýþ bir þey yok, boþ.");
			if (BizInfo[building][bizOwnerID] != PlayerInfo[playerid][pID] && pTemp[playerid][pBuildHouse] != BizInfo[building][bizID])	return SendErrorMessage(playerid, "Mekanýn kendi mobilyalarýný deðiþtiremezsiniz.");

			f_price = BFurn[building][slot][fMarketPrice];
			format(name, sizeof(name), "%s", BFurn[building][slot][fName]);
		} case 2: {
			if (!GFurn[building][slot][fOn])	return SendErrorMessage(playerid, "Bu slotta satýn alýnmýþ bir þey yok, boþ.");
			if (GarageInfo[building][garageOwner] != PlayerInfo[playerid][pID] && pTemp[playerid][pBuildHouse] != GarageInfo[building][garageID])	return SendErrorMessage(playerid, "Garajýn kendi mobilyalarýný deðiþtiremezsiniz.");

			f_price = GFurn[building][slot][fMarketPrice];
			format(name, sizeof(name), "%s", GFurn[building][slot][fName]);
		}
	}
        
	new sellprice = (f_price - (f_price & 2)) / 2;
	SendSyntaxMessage(playerid, "%s adlý mobilya $%s tutarýna geri satýldý.", name, FormatNumber(sellprice));

    if (!GetPVarInt(playerid, "buy_furniture")) GiveCash(playerid, sellprice);
		
	OnPlayerSellFurniture(pTemp[playerid][pFurnitureB], building, slot);
	return 1;
}


Dialog:MODEL_SEL_FURNITURE(playerid, response, listitem, inputtext[])
{
	if (!response)
	{
	    if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1)) return 1;
    	
	    ShowFurnitureCategories(playerid);
	    return 1;
	}

	if (pTemp[playerid][pFurniture] == -1 || (GetNearOutBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1 && GetNearInBuilding(playerid, pTemp[playerid][pFurnitureB]) != -1)) return 1;
    	
	new building = pTemp[playerid][pFurniture], 
        list = GetPVarInt(playerid, "category_furniture");

	if (GetFurnitures(playerid) >= GetMaxPlayerFurniture(playerid))	return SendErrorMessage(playerid, "Maksimum mobilya sýnýrýna ulaþtýnýz.");
	if (list == 28 && GetOutsideFurnitures(playerid) >= 9 && GetOutsideFurnitures(playerid) <= 0) return SendErrorMessage(playerid, "Dýþarýya maksimum 10 mobilya koyabilirsiniz.");
	
	new model = furniture_list[list][listitem][frModel];
/*	if (list == 29 && (model == REACTOR_OBJECT || model == DRYER_OBJECT || model == MIXER_OBJECT)) {
		if (GetClosestFurniture(playerid, 30.0, model, DRUG_LAB) != -1) return SendErrorMessage(playerid, "%s zaten bulunuyor.", furniture_list[list][listitem][frName]);
	}*/

	new i = -1;

	switch(pTemp[playerid][pFurnitureB])
	{
		case 0: {
			for(new a; a < MAX_FURNITURE; a++)
			{
				if (!HFurn[building][a][fOn])
				{
					i = a;
					break;
				}		        
			}
			if (i == -1) return 1;
		} case 1: {
			for(new a; a < MAX_FURNITURE; a++)
			{
				if (!BFurn[building][a][fOn])
				{
					i = a;
					break;
				}		        
			}
			if (i == -1) return 1;
		} case 2: {
			for(new a; a < MAX_FURNITURE; a++)
			{
				if (!GFurn[building][a][fOn])
				{
					i = a;
					break;
				}		        
			}
			if (i == -1) return 1;
		}
	}	

	static const str_size[] = "{C3C3C3}Kategori:\t{ffffff}%s\n{C3C3C3}Ýsim:\t{ffffff}%s\n{C3C3C3}Fiyat:\t{ffffff}$%s\n{ffffff}";
	new mes[sizeof(str_size) - 6 + 11 + 32 + 64];

	format(mes, sizeof(mes), str_size, furniture_title[list], furniture_list[list][listitem][frName], FormatNumber(furniture_list[list][listitem][frPrice]));
	SetPVarInt(playerid, "furniture_index", listitem);

	Dialog_Show(playerid, BuyFurniture, DIALOG_STYLE_MSGBOX, "Mobilya satýn al", mes, "Satýn Al", "Geri Dön");
	return 1;
}

FurnBuingDialog(playerid, listitem)
{
    SetPVarInt(playerid, "category_furniture", listitem);
    
    new objects = furniture_objects[listitem], object_names[153], object_amounts[153];

	for(new i; i < objects; i++)
	{
		object_names[i] = furniture_list[listitem][i][frModel];
	    object_amounts[i] = furniture_list[listitem][i][frPrice];
	}

	new mes[sizeof(object_names)*16];
	for(new i = 0; i < sizeof(object_names); i++)
	{
		if (object_names[i]) format(mes, sizeof(mes), "%s%i\t~g~$%i\n", mes, object_names[i], object_amounts[i]); 
	}
	
	new title[64];
	format(title, sizeof(title), "MOBILYA SATIN ALINIYOR > %s", furniture_title[listitem]);
	Dialog_Show(playerid, MODEL_SEL_FURNITURE, DIALOG_STYLE_PREVIEW_MODEL, title, mes, "Sec", "Kapat");
}