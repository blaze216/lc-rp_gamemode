forward OnNoteInsert(playerid, noteid);
forward OnPlayerLoadNotes(playerid);

public OnPlayerLoadNotes(playerid)
{
	new rows = cache_num_rows();

	if (!rows) return 1;

	for(new i; i < rows; i++)
	{
	    if (i >= MAX_PLAYER_NOTES) break;

		cache_get_value_int(i, "id", PlayerNotes[playerid][i][noteID]);
		cache_get_value(i, "text", PlayerNotes[playerid][i][noteText], 128);
		PlayerNotes[playerid][i][noteOn] = 1;
	}
	return 1;
}

public OnNoteInsert(playerid, noteid)
{
	return PlayerNotes[playerid][noteid][noteID] = cache_insert_id();
}

LoadPlayerNotes(playerid)
{
    new query[256];
	mysql_format(dbHandle, query, sizeof(query), "SELECT * FROM `player_notes` WHERE `userid` = %i", PlayerInfo[playerid][pID]);
	mysql_tquery(dbHandle, query, "OnPlayerLoadNotes", "i", playerid);
	return 1;
}