Dialog:SelectGPS(playerid, response, listitem, inputtext[])
{
	listitem = GetPVarInt(playerid, #select_gps);

	if(!response)
	    return 1;

   	Waypoint_Set(playerid, gps_location[listitem][gpsX], gps_location[listitem][gpsY], gps_location[listitem][gpsZ]);
	SendClientMessageEx(playerid, COLOR_GREEN, "%s lokasyonu haritada belirlendi.", gps_location[listitem][gpsName]);
	PlayerPlaySound(playerid, 21001, 0.0, 0.0, 0.0);
	return 1;
}

Dialog:DeleteSMS(playerid, response, listitem, inputtext[])
{
    if(!response)
    	return 1;

    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `sms` WHERE `id` = %i", GetPVarInt(playerid, #select_sms));
	mysql_tquery(dbHandle, query);

	Phone_SMS_Info(playerid);
    Phone_SMS(playerid, 0);
	return 1;
}

Dialog:SendSMS(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return 1;

	if(strlen(inputtext) < 1 || strlen(inputtext) > 24)
 		return Dialog_Show(playerid, SendSMS, DIALOG_STYLE_INPUT, "Mesaj", "Mesajý girin:", "Gönder", "Geri");

    SetPVarString(playerid, #sms_number, inputtext);
    new mes[24];
    format(mes, sizeof(mes), "[%s]", inputtext);
	Dialog_Show(playerid, SendSMS2, DIALOG_STYLE_INPUT, mes, "Mesajý girin:", "Gönder", "Geri");
	return 1;
}

Dialog:SendSMS2(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return 1;

	if(strlen(inputtext) < 1 || strlen(inputtext) > 127)
	{
	    new mes[32];
	    GetPVarString(playerid, #sms_number, mes, 32);
	    Dialog_Show(playerid, SendSMS2, DIALOG_STYLE_INPUT, mes, "Mesajý girin:", "Gönder", "Geri");
	    return 1;
	}

	new mes[128 + 32],
	    name[32];

    GetPVarString(playerid, #sms_number, name, 32);

	format(mes, sizeof(mes), "%s %s", name, inputtext);
	pc_cmd_sms(playerid, mes);
	return 1;
}

Dialog:SendSMS3(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return 1;

	new contact = GetPVarInt(playerid, #select_contact);

	if(contact < 0 || contact >= MAX_PLAYER_CONTACTS || PlayerContacts[playerid][contact][contactOn] == 0)
	    return 1;

	if(strlen(inputtext) < 1 || strlen(inputtext) > 127)
	{
	    new mes[128];
	    format(mes, sizeof(mes), "[%s]", PlayerContacts[playerid][contact][contactName]);
	    Dialog_Show(playerid, SendSMS3, DIALOG_STYLE_INPUT, mes, "Mesajý girin:", "Gönder", "Geri");
	    return 1;
	}

	new mes[128 + 12];
	format(mes, sizeof(mes), "%i %s", PlayerContacts[playerid][contact][contactNumber], inputtext);
	pc_cmd_sms(playerid, mes);
	return 1;
}

Dialog:DeleteContact(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return 1;

	new contact = GetPVarInt(playerid, #select_contact);

	if(contact < 0 || contact >= MAX_PLAYER_CONTACTS || PlayerContacts[playerid][contact][contactOn] == 0)
	    return 1;

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "DELETE FROM `player_contacts` WHERE `id` = %i", PlayerContacts[playerid][contact][contactID]);
	mysql_tquery(dbHandle, query);

	mysql_format(dbHandle, query, sizeof(query), "UPDATE `sms` SET `from_name` = `from_number` WHERE `to_number` = '%i' AND `from_number`='%i'", PlayerInfo[playerid][pNumber], PlayerContacts[playerid][contact][contactNumber]);
	mysql_tquery(dbHandle, query);

    mysql_format(dbHandle, query, sizeof(query), "UPDATE `history_calls` SET `from_name` = `from_number` WHERE `to_number` = '%i' AND `from_number`='%i'", PlayerInfo[playerid][pNumber], PlayerContacts[playerid][contact][contactNumber]);
	mysql_tquery(dbHandle, query);

	SendClientMessageEx(playerid, COLOR_GREEN, "%s (%i) kiþisi rehberden silindi.", PlayerContacts[playerid][contact][contactName], PlayerContacts[playerid][contact][contactNumber]);
	PlayerContacts[playerid][contact][contactNumber] = 0;
	PlayerContacts[playerid][contact][contactOn] = 0;
	PlayerContacts[playerid][contact][contactID] = 0;

	Phone_Contact_Info(playerid);
	Phone_Contacts(playerid, 0);

	DeletePVar(playerid, #select_contact);
	return 1;
}

Dialog:AddContact(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return 1;

	new
		number = strval(inputtext);

	if(number < 1 || number > 999999999)
	    return SendErrorMessage(playerid, "Geçersiz numara girdiniz.");

	SetPVarInt(playerid, #contact_number, number);

	new mes[128];
	format(mes, sizeof(mes), "Numara: %i.\nÝsim girin:", number);
	Dialog_Show(playerid, AddContact2, DIALOG_STYLE_INPUT, "Rehber", mes, "Ýlerle", "Geri");
	return 1;
}

Dialog:AddContact2(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return 1;

	if(strlen(inputtext) < 1 || strlen(inputtext) > 23)
	{
	    new mes[128];
		format(mes, sizeof(mes), "Numara: %i.\nÝsim girin:", GetPVarInt(playerid, #contact_number));
		Dialog_Show(playerid, AddContact2, DIALOG_STYLE_INPUT, "Rehber", mes, "Ýlerle", "Geri");
		return SendErrorMessage(playerid, "Ýsim 23 karakterden uzun 1 karakterden kýsa olamaz.");
	}

	new contact = -1,
	    count;
	    
	for(new i = 0; i != MAX_PLAYER_CONTACTS; i++)
    {
        if(PlayerContacts[playerid][i][contactOn] != 0)
            count++;

        if(PlayerContacts[playerid][i][contactOn] == 0 && contact == -1)
        	contact = i;
    }

	if(count >= GetMaxPlayerContacts(playerid) || contact == -1)
	    return SendErrorMessage(playerid, "Rehberine daha fazla kiþi ekleyemezsin.");

	PlayerContacts[playerid][contact][contactNumber] = GetPVarInt(playerid, #contact_number);
	format(PlayerContacts[playerid][contact][contactName], 32, "%s", inputtext);
	PlayerContacts[playerid][contact][contactOn] = 1;

	new query[256];
	mysql_format(dbHandle, query, sizeof(query), "UPDATE `sms` SET `from_name` = '%e' WHERE `to_number` = '%i' AND `from_number`='%i'", inputtext, PlayerInfo[playerid][pNumber], PlayerContacts[playerid][contact][contactNumber]);
	mysql_tquery(dbHandle, query);

    mysql_format(dbHandle, query, sizeof(query), "UPDATE `history_calls` SET `from_name` = '%e' WHERE `to_number` = '%i' AND `from_number`='%i'", inputtext, PlayerInfo[playerid][pNumber], PlayerContacts[playerid][contact][contactNumber]);
	mysql_tquery(dbHandle, query);

	PlacePlayerContact(playerid, contact, inputtext, GetPVarInt(playerid, #contact_number));

	Phone_Contacts(playerid, GetPVarInt(playerid, #contacts_list));
	return 1;
}