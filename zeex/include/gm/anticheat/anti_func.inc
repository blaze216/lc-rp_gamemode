stock UploadAntiCheatSettings()  
{  
    mysql_tquery(dbHandle, "SELECT * FROM `anticheat_settings`", "UploadAntiCheat");
}

this::UploadAntiCheat()
{
    new rows = cache_num_rows(), tick = GetTickCount();

	if (!rows) {  
        print("[MySQL]: Anti-cheat ayarlari veritabaninda bulunamadi. Modun yüklenmesi durduruldu, lütfen anti-cheati yapilandirin.");
        return GameModeExit();  
    }  

    for(new i = 0; i < AC_MAX_CODES; i++)
    {
        cache_get_value_int(i, "ac_code_trigger_type", AC_CODE_TRIGGER_TYPE[i]);

        if (AC_CODE_TRIGGER_TYPE[i] == AC_CODE_TRIGGER_TYPE_DISABLED) {
            EnableAntiCheat(i, 0);
        }
    }

    new mes[128];
    format(mes, sizeof(mes), "[AntiCheat] Anti-cheat ayarlari basarili sekilde yüklendi. (yuklenen: %i). Sure: %i ms.", rows, GetTickCount() - tick);  
    print(mes);

    return 1;  
}

stock Anticheat_OnPlayerConnect(playerid)
{

    for(new i = 0; i < AC_MAX_CODES; i++)
        pAntiCheatLastCodeTriggerTime[playerid][i] = -1;

    pAntiCheatSettingsPage{playerid} = 0;
    pAntiCheatSettingsEditCodeId[playerid] = -1;
    return 1;
} 

this::OnCheatDetected(playerid, ip_address[], type, code, code2)
{
    if (PlayerInfo[playerid][pAdmin] >= 1) return 0;
    
    if (type == AC_GLOBAL_TRIGGER_TYPE_PLAYER)
    {
        switch(code)
        {
            case 5, 6, 11, 22: 
            {
                return 1;
            }
            case 32: // CarJack
            {
                new 
                    Float:x, 
                    Float:y, 
                    Float:z;

                AntiCheatGetPos(playerid, x, y, z);
                return SetPlayerPos(playerid, x, y, z);
            }
            case 40: // Sandbox
            {
                SendClientMessage(playerid, -1, MAX_CONNECTS_MSG);
                return AntiCheatKickWithDesync(playerid, code);
            }
            case 41: // Invalid Version
            {
                SendClientMessage(playerid, -1, UNKNOWN_CLIENT_MSG);
                return AntiCheatKickWithDesync(playerid, code);
            }
            default:
            {
                if (gettime() - pAntiCheatLastCodeTriggerTime[playerid][code] < AC_TRIGGER_ANTIFLOOD_TIME)
                    return 1;

                pAntiCheatLastCodeTriggerTime[playerid][code] = gettime();
                AC_CODE_TRIGGERED_COUNT[code]++;

                new
                    string[88 - 10 + MAX_PLAYER_NAME + 5 + AC_MAX_CODE_NAME_LENGTH + AC_MAX_CODE_LENGTH],
                    trigger_type = AC_CODE_TRIGGER_TYPE[code];

                switch(trigger_type)
                {
                    case AC_CODE_TRIGGER_TYPE_DISABLED: return 1;
                    case AC_CODE_TRIGGER_TYPE_WARNING:  SendAdmMessage("%s [%d] adlý oyuncunun hile olduðundan þüpheleniliyor: %s [KOD: %03d].", GetNameEx(playerid), playerid, AC_CODE_NAME[code], code);
                    case AC_CODE_TRIGGER_TYPE_KICK: {
                        SendAdmMessage("%s [%d] adlý oyuncu hile programlarý kullandýðý þüphesiyle sunucudan atýldý: %s [KOD: %03d].", GetNameEx(playerid), playerid, AC_CODE_NAME[code], code);

                        format(string, sizeof(string), "Hile programlarý kullandýðýnýz þüphesiyle sunucudan atýldýnýz: %s [KOD: %03d].", AC_CODE_NAME[code], code);
                        SendClientMessage(playerid, COLOUR_TOMATO, string);

                        AntiCheatKickWithDesync(playerid, code);
                    }
                } 
            }
        }
    }
    else // AC_GLOBAL_TRIGGER_TYPE_IP
    {
        AC_CODE_TRIGGERED_COUNT[code]++;

        SendAdmMessage("[LG-BAN-IP] IP adresiniz (%s) engellendi: %s [KOD: %03d].", ip_address, AC_CODE_NAME[code], code);

        BlockIpAddress(ip_address, 0);
    }
    return 1;
} 

public OnPlayerAirbreak(playerid) return KickLine(playerid, "Airbreak hilesi.");

stock Oyuncu_IP(playerid)
{
	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	return ip;
}

forward OnClientCheckResponseFix(playerid, actionid, memaddr, retndata);
public OnClientCheckResponseFix(playerid, actionid, memaddr, retndata)
{
	printf("Sobeit Kontrol = isim: %s(%d) data degeri: %d", GetNameEx(playerid), playerid, retndata);
	
	if(retndata != 192) 
	{
		SendAdmMessage("%s(%d) (IP: %s) adlý karakterden sobeit giriþi denemesi yapýldý. Oyuna girerse takibe alýn.", GetNameEx(playerid), playerid, Oyuncu_IP(playerid));
		ShowPlayerDialog(playerid, 0, DIALOG_STYLE_MSGBOX, "> Blaze Guard", "{B70000}[!] {FFFFFF}Hile tespit edildiði için oyundan atýldýnýz.\n\n{FF7E00}NOT: {FFFFFF}Hile kullanmamanýza raðmen atýlýyorsanýz eðer, oyun dosyalarýnýzý deðiþtirmeden panel üzerinden\n{FFFFFF}Bug Bildirimleri kategorisinde ticket oluþturun.", "Kapat", "");

		KickEx(playerid);
	}
	return 1;
}

/*
public OnPlayerSuspectedForAimbot(playerid,hitid,weaponid,warnings)
{
	new str[144],nme[MAX_PLAYER_NAME],wname[32],Float:Wstats[BUSTAIM_WSTATS_SHOTS];

	GetPlayerName(playerid,nme,sizeof(nme));
	GetWeaponName(weaponid,wname,sizeof(wname));
	if(warnings & WARNING_OUT_OF_RANGE_SHOT)
	{
	    format(str,256,"%s(%d) fired shots from a distance greater than the %s's fire range(Normal Range:%d)",nme,playerid,wname,BustAim::GetNormalWeaponRange(weaponid));
		SendClientMessageToAll(-1,str);
		BustAim::GetRangeStats(playerid,Wstats);
		format(str,256,"Shooter to Victim Distance(SA Units): 1)%f 2)%f 3)%f",Wstats[0],Wstats[1],Wstats[2]);
		SendClientMessageToAll(-1,str);
	}
	if(warnings & WARNING_PROAIM_TELEPORT)
	{
	    format(str,256,"%s(%d) is using proaim (Teleport Detected)",nme,playerid);
		SendClientMessageToAll(-1,str);
		BustAim::GetTeleportStats(playerid,Wstats);
		format(str,256,"Bullet to Victim Distance(SA Units): 1)%f 2)%f 3)%f",Wstats[0],Wstats[1],Wstats[2]);
		SendClientMessageToAll(-1,str);
	}
	if(warnings & WARNING_RANDOM_AIM)
	{
	    format(str,256,"%s(%d) is suspected to be using aimbot(Hit with Random Aim with %s)",nme,playerid,wname);
		SendClientMessageToAll(-1,str);
		BustAim::GetRandomAimStats(playerid,Wstats);
		format(str,256,"Random Aim Offsets: 1)%f 2)%f 3)%f",Wstats[0],Wstats[1],Wstats[2]);
		SendClientMessageToAll(-1,str);
	}
	if(warnings & WARNING_CONTINOUS_SHOTS)
	{
	    format(str,256,"%s(%d) has fired 10 shots continously with %s(%d)",nme,playerid,wname,weaponid);
		SendClientMessageToAll(-1,str);
	}
	return 0;
}*/