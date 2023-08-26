Ap_OnPlayerPickUpDynamicPickup(playerid, pickupid)
{
    if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        for(new i = 0; i != MAX_APART; i++)
		{
			if (ApartInfo[i][aApartOn] == 0 || pickupid != ApartInfo[i][aPickup]) continue;

			if (pTemp[playerid][pPizzaBoy] && pTemp[playerid][pPizzaBoy]-1 == i && IsPlayerAttachedObjectSlotUsed(playerid, ATTACH_HANDS))
			{
			    pTemp[playerid][pPizzaBoy] = 0;
				#define PIZZABOY_COST 30
				new bahsis = randomEx(1, 30), ucret = bahsis + PIZZABOY_COST;
			    SendSyntaxMessage(playerid, "Pizza teslim edildi. Paket ücreti olarak %d$ bahþiþ olarak %d$ kazandýn.", PIZZABOY_COST, bahsis);
                SendServerMessage(playerid, "Tekrar /kurye yazarak yeni teslimat noktasý belirleyebilirsin.");
			    GiveCash(playerid, ucret);
                RemovePlayerAttachedObject(playerid, ATTACH_HANDS);
			    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
				return 1;
			}

            new string[128];
            format(string, sizeof(string),"~h~~p~Apartman~n~~y~%s", GetApartmentZone(i, 2)); 
            CreateLableText(playerid, string, "~h~~y~~h~'Y' ~w~ tusune basarak veya~n~~y~~h~/giris~h~~w~ yazarak girebilirsiniz");
			return 1;
		}
    }
    return 1;
}

Apart_OnGameModeInit()
{
    mysql_tquery(dbHandle, "SELECT * FROM `apartment`", "LoadDynamicApartment");
    return 1;
}