//ïîêåð

#define LEAR_HEARTS 1
#define LEAR_DIAMONDS 2
#define LEAR_CLUBS 3
#define LEAR_SPADES 4

#define MAX_TYPE_CARDS 14
#define MAX_CARDS_FOR_LEAR 4
#define MAX_PLAYER_CURRENT_CARDS 6

new exicards[0][13] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A"};

new PackCards[MAX_PLAYERS][MAX_TYPE_CARDS];
new PackCardsLears[MAX_PLAYERS][14][MAX_CARDS_FOR_LEAR];

new PlayerSumm[MAX_PLAYERS];
new PlayerSummLear[MAX_PLAYERS][14];
new PlayerCurrentCards[MAX_PLAYERS][MAX_PLAYER_CURRENT_CARDS][2];

ClearPackCards(playerid)
{
	for(new i = 0; i < MAX_PLAYER_CURRENT_CARDS; i++)
	{
		PlayerCurrentCards[playerid][i][0] = 0;
		PlayerCurrentCards[playerid][i][1] = 0;
	}

	DeletePVar(playerid, "SummCards");
	InsertPackCards(playerid);
	return 1;
}
InsertPackCards(playerid)
{
	for(new i = 0; i < MAX_TYPE_CARDS; i++)
	{
		PackCards[playerid][i] = i;

		for(new c = 0; c < MAX_CARDS_FOR_LEAR; c++)
		{
			PackCardsLears[playerid][i][c] = c+1;
		}
	}
	return 1;
}
GetPlayerSummCard(playerid)
{
	PlayerSumm[playerid] = 0;

	for(new i = 0; i < MAX_TYPE_CARDS; i++)
	{
		if (PackCards[playerid][i] == -1) continue;

		PlayerSumm[playerid]++;
		PlayerSummLear[playerid][i] = 0;

		for(new c = 0; c < MAX_CARDS_FOR_LEAR; c++)
		{
			if (PackCardsLears[playerid][i][c] == -1) continue;

			PlayerSummLear[playerid][i]++;
		}
	}
}
GivePlayerCard(playerid, &newcard, &newcardlear)
{
	new SummEx[2];
	new returnresult[2];

	returnresult[0] = random(PlayerSumm[playerid]);
	returnresult[1] = random(PlayerSummLear[playerid][returnresult[0]]);

	if (returnresult[0] == 0)	returnresult[0] += 1;
	if (returnresult[1] == 0) 	returnresult[1] += 1;

	for(new i = 0; i < MAX_TYPE_CARDS; i++)
	{
		if (PackCards[playerid][i] == -1) continue; 

		SummEx[0]++;

		if (SummEx[0] == returnresult[0])
		{
			for(new c = 0; c < MAX_CARDS_FOR_LEAR; c++)
			{
				if (PackCardsLears[playerid][i][c] == -1) continue;

				SummEx[1]++;

				if (SummEx[1] == returnresult[1])
				{
					PackCardsLears[playerid][i][c] = -1;

					if (PlayerSummLear[playerid][i] == 1) PackCards[playerid][i] = -1;

					newcard = i; newcardlear = c+1;
					return 1;
				}
			}
		}
	}
	return 0;
}
ShowPlayerCards(playerid)
{
	new cardname[156], cardslist[186];

	for(new i = 0; i < GetPVarInt(playerid, "SummCards"); i++)
	{
		format(cardname, sizeof(cardname), "%s%s ", exicards[PlayerCurrentCards[playerid][i][0]][0], GetTypeCard(PlayerCurrentCards[playerid][i][1]));
		strcat(cardslist, cardname, sizeof(cardslist));
	}

	SendClientMessageEx(playerid, COLOR_YELLOW, "Elinizdeki kartlar: %s. Kartý göstermek için: /kartlarigoster", cardslist);
	return 1;
}
ShowPlayerCardsToAll(playerid)
{
	new cardname[156], cardslist[186];

	for(new i = 0; i < GetPVarInt(playerid, "SummCards"); i++)
	{
		format(cardname, sizeof(cardname), "%s%s ", exicards[PlayerCurrentCards[playerid][i][0]][0], GetTypeCard(PlayerCurrentCards[playerid][i][1]));
		strcat(cardslist, cardname, sizeof(cardslist));
	}

	SendNearbyMessage(Range_Normal, playerid, COLOR_WHITE, "* %s kartýný açar: %s", GetNameWithMask(playerid), cardslist);
	ClearPackCards(playerid);
	return 1;
}

GetTypeCard(learid)
{
	new leartext[15];

	if (learid == LEAR_HEARTS) { leartext = "[Kupa]"; }
	if (learid == LEAR_DIAMONDS) { leartext = "[Karo]"; }
	if (learid == LEAR_CLUBS) { leartext = "[Sinek]"; }
	if (learid == LEAR_SPADES) { leartext = "[Maça]"; }

	return leartext;
}

CMD:kartlarigoster(playerid, params[])
{
	if (GetPVarInt(playerid, "SummCards") < 1) return SendErrorMessage(playerid, "Kartýnýz yok.");
	ShowPlayerCardsToAll(playerid);
	ClearPackCards(playerid);
	return 1;
}

CMD:kartver(playerid, params[])
{
	new id;
	if (sscanf(params,"u",id))						return SendHelpMessage(playerid, "/kartver [ID / isim]");
	if (!PlayerInfo[playerid][pOyunKarti])		return SendErrorMessage(playerid,"Hiç oyun kartýn yok.");
	if (!IsPlayerLogged(id))						return SendNotConnected(playerid);
	if (!PlayerNearPlayer(5.0, playerid, id))		return SendNotNearPlayer(playerid);
	if (GetPVarInt(id, "SummCards") > 5)			return SendErrorMessage(playerid, "Bu oyuncunun yeterli kartý var.");

	new newcarid, newcaridlear;

	GetPlayerSummCard(playerid);

	if (PlayerSumm[playerid] < 1) return SendErrorMessage(playerid,"Destede baþka kart yok.");

	GivePlayerCard(playerid, newcarid, newcaridlear);
	PlayerCurrentCards[id][GetPVarInt(id, "SummCards")][0] = newcarid;
	PlayerCurrentCards[id][GetPVarInt(id, "SummCards")][1] = newcaridlear;
	SetPVarInt(id, "SummCards", GetPVarInt(id, "SummCards")+1);

	SendSyntaxMessage(id, "Kartý aldýnýz: %s%s", exicards[newcarid][0], GetTypeCard(newcaridlear));
	ShowPlayerCards(id);

	SendServerMessage(playerid, "%s adlý kiþiye kartý verdiniz.", GetNameEx(id));

	if (id == playerid) pc_cmd_server_ame(playerid, "kendisi için ters bir kart çýkardý.");
	else
	{
	    new mes[128];
	    format(mes, sizeof(mes), "kapalý kartý geçer %s.", GetNameWithMask(id));
		SetPlayerChatBubble(playerid, mes, COLOR_PURPLE, 20.0, 4000);
	}
	return 1;
}
