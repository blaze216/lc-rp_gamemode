Garage_OnPlayerEnterDynamicCP(playerid, checkpointid) //÷åêïîèíò
{
    if (GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
    {
        for(new i = 0; i < MAX_GARAGES; i++)
		{
		    if (!GarageInfo[i][garageID] || GarageInfo[i][garageCP] != checkpointid) continue;

		    if (GarageInfo[i][garageOwner])
		    {
				SendSyntaxMessage(playerid, "Bu garaj %s kişisine ait.", GarageInfo[i][garageOwnerName]);
				SendHelpMessage(playerid, "/giris cikis (/g)araj bilgi");

				new mes[64];
				format(mes, sizeof(mes), "~h~~p~Garaj~n~%s", GarageInfo[i][garageOwnerName]);

				CreateLableText(playerid, mes, "~h~~y~~h~'Y' ~w~ tusuna basin~n~veya ~y~~h~/giris~h~~w~ yazarak giris yapin");
			}
			else if (!GarageInfo[i][garageOwner] && !GarageInfo[i][garageHouse] && !GarageInfo[i][garageBiz])
			{
				SendSyntaxMessage(playerid, "Bu garaj satılık. Ücret: $%i.", GarageInfo[i][garagePrice]);
				SendHelpMessage(playerid, "/giris (/g)araj bilgi (/g)araj satinal");

				new mes[64];
				format(mes, sizeof(mes), "~h~~p~SATILIK GARAJ!~n~~g~UCRET: ~g~$%i", GarageInfo[i][garagePrice]);

				CreateLableText(playerid, mes, "~h~~y~~h~'Y' ~w~ tusuna basarak~n~veya ~y~~h~/garaj satinal~h~~w~ yazarak satin alabilirsiniz");
			} else if (!GarageInfo[i][garageOwner] && GarageInfo[i][garageHouse]) {
			    SendSyntaxMessage(playerid, "Bu garaj bir ev ile bağlantılı ve ikisi beraber satılıyor.");
				SendHelpMessage(playerid, "/giris (/g)araj bilgi");

				new mes[64];
				format(mes, sizeof(mes), "~h~~p~SATILIK GARAJ!~n~~y~(%i numarali ev)", GarageInfo[i][garageHouse]);

				CreateLableText(playerid, mes, "~h~~y~~h~'Y' ~w~ tusuna basarak~n~veya ~y~~h~/garaj satinal~h~~w~ yazarak satin alabilirsiniz");
			}
			else if (!GarageInfo[i][garageOwner] && GarageInfo[i][garageBiz])
			{
				SendSyntaxMessage(playerid, "bu garaj mekan ile bağlantılı ve ikisi beraber satılıyor.");
				SendHelpMessage(playerid, "/giris (/g)araj bilgi");

				CreateLableText(playerid, "~h~~p~SATILIK GARAJ!~n~~y~(Mekana ait)", "~h~~y~~h~'Y' ~w~ tusuna basarak~n~veya ~y~~h~/garaj satinal~h~~w~ yazarak satin alabilirsiniz");
			}
			return 1;
		}
    }
    return 1;
}

Garage_OnGameModeInit()
{
    return mysql_tquery(dbHandle, "SELECT *, (SELECT name FROM users WHERE id = garage.owner) as ownername FROM `garage`", "LoadDynamicGarage");
}