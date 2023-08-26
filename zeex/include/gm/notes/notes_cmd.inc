CMD:not(playerid, params[])
{
	new option[10], secoption[128];
	if (sscanf(params, "s[8]s[128]", option, secoption)) return SendHelpMessage(playerid, "/not [goster / olustur / sil / duzenle / ver]");

	if (CompareStrings(option, "goster"))
	{
		new count = 0;

		for(new i = 0; i < MAX_PLAYER_NOTES; i++)
		{
			if (PlayerNotes[playerid][i][noteOn] != 1) continue;

			SendClientMessageEx(playerid, COLOR_HELPS, "[Not Defteri] [ID: %d]: %s", i+1, PlayerNotes[playerid][i][noteText]);

			count++;
		}

		if (count == 0) return SendErrorMessage(playerid, "Hiç notun yok.");

		pc_cmd_server_ame(playerid, "cebinden defteri çýkarýp bakar.");
		return 1;
	}
	else if (CompareStrings(option, "duzenle"))
	{
		new slot, text[128];

		if (sscanf(params, "s[8]ds[128]", slot, text)) return SendHelpMessage(playerid, "/not duzenle [slot] [yeni metin]");
		if (!PlayerInfo[playerid][pKalem]) 	return SendErrorMessage(playerid, "Kalemin yok.");
		if (slot < 1 || slot > MAX_PLAYER_NOTES) 		return SendErrorMessage(playerid, "Slot 1 ile 10 arasýnda olmalýdýr.");
		if (strlen(text) < 1 || strlen(text) > 127)		return SendErrorMessage(playerid, "Metin minimum 1, maksimum 127 karakter olmalýdýr.");

		slot = slot - 1;

		if (PlayerNotes[playerid][slot][noteOn] != 1) 	return SendSyntaxMessage(playerid, "Belirtilen slotta not yok.");
	
		format(PlayerNotes[playerid][slot][noteText], 128, "%s", text);
		SQL_SetString("player_notes", "text", text, PlayerNotes[playerid][slot][noteID]);
		pc_cmd_server_ame(playerid, "cebinden bir not defteri çýkardý ve içine bir þeyler yazdý.");
		SendSyntaxMessage(playerid, "Notu baþarýyla deðiþtirdiniz: [ID: %i] Not: %s", slot+1, text);
		return 1;
	}
	else if (CompareStrings(option, "olustur"))
	{
		new text[128];

		if (sscanf(params, "s[8]s[128]", text)) 		return SendHelpMessage(playerid, "/not olustur [metin]");
		if (!PlayerInfo[playerid][pKalem]) 		return SendErrorMessage(playerid,"Kalemin yok.");
		if (strlen(text) < 1 || strlen(text) > 127)		return SendErrorMessage(playerid, "Metin minimum 1, maksimum 127 karakter olmalýdýr.");
    
		new noteid = -1;

		for(new i = 0; i < MAX_PLAYER_NOTES; i++)
		{
			if (PlayerNotes[playerid][i][noteOn] == 1) continue;

			noteid = i;
			break;
		}

		if (noteid == -1) return SendErrorMessage(playerid, "Defterde yazacak yer yok.");

		format(PlayerNotes[playerid][noteid][noteText], 128, "%s", text);
        PlayerNotes[playerid][noteid][noteOn] = 1;

		new query[128 + 128];
		mysql_format(dbHandle, query, sizeof(query), "INSERT INTO `player_notes` (userid, text) VALUES (%i, '%e')", PlayerInfo[playerid][pID], text);
		mysql_tquery(dbHandle, query, "OnNoteInsert", "ii", playerid, noteid);
		
        pc_cmd_server_ame(playerid, "cebinden bir not defteri çýkardý ve içine bir þeyler yazdý.");
		SendSyntaxMessage(playerid, "Baþarýyla not oluþturuldu: [ID: %i]", noteid+1);

		return 1;
	}
	else if (CompareStrings(option, "sil"))
	{
		new slot;

		if (sscanf(params, "s[8]d", slot)) 			return SendHelpMessage(playerid, "/not sil [slot]");
		if (slot < 1 || slot > MAX_PLAYER_NOTES)			return SendErrorMessage(playerid, "Geçerli slot giriniz: 1 - %i.", MAX_PLAYER_NOTES);

		slot = slot - 1;

		if (PlayerNotes[playerid][slot][noteOn] != 1)	return SendSyntaxMessage(playerid, "Belirtilen slotta not yok.");
		PlayerNotes[playerid][slot][noteOn] = 0;
		PlayerNotes[playerid][slot][noteID] = 0;
		format(PlayerNotes[playerid][slot][noteText], 128, "");

		new query[256];
		mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `player_notes` WHERE `id` = %i", PlayerNotes[playerid][slot][noteID]);
		mysql_tquery(dbHandle, query);

		pc_cmd_server_ame(playerid, "cebinden bir not defteri çýkardý, sonra içinden bir sayfa yýrttý ve yere attý.");
		SendSyntaxMessage(playerid, "Not baþarýyla silindi: [ID: %i]", slot+1);
		return 1;
	}
	else if (CompareStrings(option, "ver"))
	{
		new targetid, slot;

		if (sscanf(params, "s[8]du", slot, targetid)) 	return SendHelpMessage(playerid, "/not ver [slot] [ID / isim]");
		if (slot < 1 || slot > MAX_PLAYER_NOTES)			return SendErrorMessage(playerid, "Slot 1 ile 10 arasýnda olmalýdýr.", MAX_PLAYER_NOTES);

		slot = slot - 1;

		if (PlayerNotes[playerid][slot][noteOn] != 1) 	return SendSyntaxMessage(playerid, "Belirtilen slotta not yok.");
		if (targetid == playerid) 						return SendErrorMessage(playerid, "Kendinize not veremezsiniz.");
		if (!IsPlayerLogged(targetid)) 					return SendNotConnected(playerid);
		if (!PlayerNearPlayer(3.0, playerid, targetid))	return SendNotNearPlayer(playerid);

        new noteid = -1;

		for(new i = 0; i < MAX_PLAYER_NOTES; i++)
		{
			if (PlayerNotes[targetid][i][noteOn] == 1) continue;

			noteid = i;
			break;
		}

		if (noteid == -1) 								return SendErrorMessage(playerid, "Oyuncunun defterinde yazmak için yer yok.");

		PlayerNotes[targetid][noteid][noteID] = PlayerNotes[playerid][slot][noteID];
		format(PlayerNotes[targetid][noteid][noteText], 128, "%s", PlayerNotes[playerid][slot][noteText]);
		PlayerNotes[targetid][noteid][noteOn] = 1;
		PlayerNotes[playerid][slot][noteID] = 0;
		PlayerNotes[playerid][slot][noteOn] = 0;

		SQL_SetInteger("player_notes", "userid", PlayerInfo[targetid][pID], PlayerNotes[playerid][slot][noteID]);
		SendSyntaxMessage(playerid, "Notunuzu [ID: %i] %s [ID: %i] adlý oyuncuya verdiniz.", slot+1, GetNameWithMask(targetid), targetid);
		SendSyntaxMessage(targetid, "Size bir not geldi: [ID: %i] Gönderen: %s [ID: %i].", noteid+1, GetNameWithMask(playerid), playerid);
		
		new mes[128];
		format(mes, sizeof(mes), "cebinden bir not defteri çýkardý, sonra sayfayý yýrttý ve %s adlý kiþiye verdi.", GetNameWithMask(targetid));
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
		return 1;
	}
	SendHelpMessage(playerid, "/not [goster / olustur / sil / duzenle / ver]");
	return 1;
}