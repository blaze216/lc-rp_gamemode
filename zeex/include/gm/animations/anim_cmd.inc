alias:stopanim("animdur", "/animstop", "/animiptal", "/animasyondur", "/animdurdur", "/animasyondurdur", "/sa");
CMD:stopanim(playerid, params[])
{
	if (OnAnim{playerid}) StopPlayerAnims(playerid);
	return 1;
}

alias:animlist("animasyonlar", "/anim", "/anims");
CMD:animlist(playerid, params[])
{
	SendClientMessage(playerid,COLOR_SERVER2,"____________Animasyon Listesi____________");
	SendClientMessage(playerid,COLOR_WHITE,"/elkaldir /otur /nisanal /cellin /cellout /drunk /kicking /bomb /bar /stoptaxi");
	SendClientMessage(playerid,COLOR_WHITE,"/taxicall /gul /crossarms /kus /yemekye /ic /yuru");
	SendClientMessage(playerid,COLOR_WHITE,"/slapass /chat /fucku /taichi /yarali2 /hayir /evet /crawl /ittir /tekme");
	SendClientMessage(playerid,COLOR_WHITE,"/facepalm /kasi /vucutittir /sprey /ilkyardim /yumrukye /yereyigil /ise");
	SendClientMessage(playerid,COLOR_WHITE,"/lifejump /yuvarlan /hoodfrisked /flip /hasta /box /chant /finger /gpunch /gog");
	SendClientMessage(playerid,COLOR_WHITE,"/gkick /lowthrow /riot /bp /agla /taxiR /taxiL /gro /seat /tatto /striptiz");
	SendClientMessage(playerid,COLOR_WHITE,"/joy /dans /sigaraic /bat /basket /yaslan /uzan /gsign /yurumetarzi /elsalla /police");
	SendClientMessage(playerid,COLOR_WHITE,"/yarali /waimL /waimR /lookback /caim /creep /sroll /gesture");
	SendClientMessage(playerid,COLOR_WHITE,"/lookout /agreement /bend /cmouth /nfall /hsit /rod /swingback");
	SendClientMessage(playerid,COLOR_WHITE,"/csit /bracing /pool /search /daim /rhandL /rhandR /hstand /nlean /shelter");
	SendClientMessage(playerid,COLOR_WHITE,"/wsit /waim /hangon /polwalk /wallow /nflip /cover /durus /bagir");
	SendClientMessage(playerid,COLOR_WHITE,"/csdead /follow /grnd /copa /cmon /lose /win /gunthreat /givecash /robr");
	SendClientMessage(playerid,COLOR_WHITE,"/serend /heist /beckon /pompali /colt /climb /pushup /protection");
	SendClientMessage(playerid,COLOR_WHITE,"/tlean /swallow /stand /pullhand /nlook /extend");
	SendClientMessage(playerid,COLOR_WHITE,"/rap /car /repcar /onehand /backwalk /mirro /hips /pullo /rtake");
	SendClientMessage(playerid,COLOR_WHITE,"/obalance /wobalance /taction /catch /despair /rooting /spyglass /looksky");
	SendClientMessage(playerid,COLOR_WHITE,"/show /sh /crossfingers /delight /showtable /tfacepalm");
	SendClientMessage(playerid,COLOR_WHITE,"/tpull /fail /wear /fsit /crushjump /scatch /lookfloor /tramplefloor /tgro");
	SendClientMessage(playerid,COLOR_WHITE,"/swing /nbp /takehead /readtable /squat /sprawl /throwmoney /faim");
	SendClientMessage(playerid,COLOR_WHITE,"/greet /hands /yerdenkaldir /tezahurat /idle");
	SendClientMessage(playerid,COLOR_WHITE,"/sarjordoldur /beyzbol /tapcig /dusme /uyu");
	SendClientMessage(playerid,COLOR_SERVER2,"_____________________________________________");

	return 1;
}
alias:strip("striptiz");
CMD:strip(playerid, params[])
{
	new type;

	if (sscanf(params,"d", type)) return SendHelpMessage(playerid, "/striptiz [1-14]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1 );
		case 2: OnPlayAnim(playerid,"STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1 );
		case 3: OnPlayAnim(playerid,"STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1 );
		case 4: OnPlayAnim(playerid,"STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1 );
		case 5: OnPlayAnim(playerid,"STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1 );
		case 6: OnPlayAnim(playerid,"STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1 );
		case 7: OnPlayAnim(playerid,"STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1 );
		case 8: OnPlayAnim(playerid,"STRIP","STR_A2B",4.1,1,1,1,1,1);
		case 9: OnPlayAnim(playerid,"STRIP","STR_B2C",4.1,1,1,1,1,1);
		case 10: OnPlayAnim(playerid,"STRIP","STR_C1",4.1,1,1,1,1,1);
		case 11: OnPlayAnim(playerid,"STRIP","STR_C2",4.1,1,1,1,1,1);
		case 12: OnPlayAnim(playerid,"STRIP","STR_Loop_A",4.1,1,1,1,1,1);
		case 13: OnPlayAnim(playerid,"STRIP","STR_Loop_B",4.1,1,1,1,1,1);
		case 14: OnPlayAnim(playerid,"STRIP","STR_Loop_C",4.1,1,1,1,1,1);
		default: SendHelpMessage(playerid, "/striptiz [1-14]");
	}
	return 1;
}

alias:liftup("yerdenkaldir");
CMD:liftup(playerid, params[])
{
	return OnPlayAnim(playerid, "CARRY", "liftup", 3.0, 0, 0, 0, 0, 0);
}

CMD:putdown(playerid, params[])
{
	return OnPlayAnim(playerid, "CARRY", "putdwn", 3.0, 0, 0, 0, 0, 0);
}

alias:stretch("tezahurat");
CMD:stretch(playerid, params[])
{
	return OnPlayAnim(playerid,"STRIP","PUN_HOLLER",4.1,1,0,0,1,0);
}

alias:idle("aylak");
CMD:idle(playerid, params[])
{
	return OnPlayAnim(playerid,"STRIP","PUN_LOOP",4.1,1,0,0,1,0);
}

alias:batidle("beyzbol");
CMD:batidle(playerid, params[])
{
	return OnPlayAnim(playerid,"BASEBALL","Bat_IDLE",4.1,1,0,0,1,0);
}

alias:aim("nisanal");
CMD:aim(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/nisanal [1-2]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 1, 0, 0, 0, 0);
		case 2: OnPlayAnim(playerid,"PED","gang_gunstand",3.0,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/nisanal [1-2]");
	}
	return 1;
}

alias:lay("uzan");
CMD:lay(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/uzan [1-5]");

	switch(type)
	{
		case 1:	OnPlayAnim(playerid,"BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
		case 2:	OnPlayAnim(playerid,"SUNBATHE","Lay_Bac_in",3.0,0,1,1,1,0);
		case 3:	OnPlayAnim(playerid,"BEACH","ParkSit_W_loop",3.0,0,1,1,1,0);
		case 4:	OnPlayAnim(playerid,"BEACH","SitnWait_loop_W",4.0, 1, 0, 0, 0, 0);
		case 5:	OnPlayAnim(playerid,"SUNBATHE","SBATHE_F_LieB2Sit",3.0,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/uzan [1-5]");
	}
	return 1;
}

alias:crack("yarali");
CMD:crack(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/yarali [1-7]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"CRACK","crckdeth2",3.0,1,1,1,1,0);
		case 2: OnPlayAnim(playerid,"CRACK","crckdeth4",3.0,0,1,1,1,0);
		case 3: OnPlayAnim(playerid,"CRACK","crckidle1",3.0,0,1,1,1,0);
		case 4: OnPlayAnim(playerid,"CRACK","crckidle2",3.0,0,1,1,1,0);
		case 5: OnPlayAnim(playerid,"CRACK","crckidle3",3.0,0,1,1,1,0);
		case 6: OnPlayAnim(playerid,"CRACK","crckdeth1",3.0,0,1,1,1,0);
		case 7: OnPlayAnim(playerid,"CRACK","crckdeth3",3.0,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/yarali [1-7]");
	}
	return 1;
}

alias:areload("sarjordoldur");
CMD:areload(playerid, params[])
{
	return OnPlayAnim(playerid,"TEC","TEC_reload",4.0,0,0,0,0,0);
}

CMD:bat(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/bat [1-2]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"CRACK","Bbalbat_Idle_02",4.0, 1, 0, 0, 0, 0);
		case 2: OnPlayAnim(playerid,"CRACK","Bbalbat_Idle_01",4.0, 1, 0, 0, 0, 0);
		default: SendHelpMessage(playerid, "/bat [1-2]");
	}
	return 1;
}

CMD:tapcig(playerid, params[])
{
	return OnPlayAnim(playerid,"SMOKING","M_smk_tap",3.0,0,0,0,0,0);
}

alias:fall("dusme");
CMD:fall(playerid, params[])
{
	return OnPlayAnim(playerid,"PARACHUTE","FALL_skyDive_DIE",3.5,0,0,0,1,0);
}

alias:laugh("gul");
CMD:laugh(playerid, params[])
{
	return OnPlayAnim(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
}

alias:vomit("kus");
CMD:vomit(playerid, params[])
{
	return OnPlayAnim(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
}

CMD:uyu(playerid, params[])
{
	new type;

	if (sscanf(params, "d", type)) return SendHelpMessage(playerid, "/uyu [1-4]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"INT_HOUSE","BED_Loop_L",4.0,1,0,0,0,0);
		case 2: OnPlayAnim(playerid,"INT_HOUSE","BED_Loop_R",4.0,1,0,0,0,0);
		case 3: OnPlayAnim(playerid,"INT_HOUSE","BED_In_L",4.0,0,0,1,1,0);
		case 4: OnPlayAnim(playerid,"INT_HOUSE","BED_In_R",4.0,0,0,1,1,0);
		default: SendHelpMessage(playerid, "/uyu [1-4]");
	}
	return 1;
}
CMD:inbedleft(playerid, params[])
{
	return OnPlayAnim(playerid,"INT_HOUSE","BED_Loop_L",4.0,1,0,0,0,0);
}

CMD:inbedright(playerid, params[])
{
	return OnPlayAnim(playerid,"INT_HOUSE","BED_Loop_R",4.0,1,0,0,0,0);
}

CMD:taxicall(playerid, params[])
{
	return OnPlayAnim(playerid,"PED","IDLE_taxi",4.0,0,0,0,0,0);
}

alias:cry("agla");
CMD:cry(playerid, params[])
{
	return OnPlayAnim(playerid,"GRAVEYARD","mrnf_loop",4.0,1,0,0,0,0);
}

CMD:sleepl(playerid)
{
	return OnPlayAnim(playerid,"INT_HOUSE","BED_In_L",4.0,0,0,1,1,0);
}

CMD:sleepr(playerid)
{
	return OnPlayAnim(playerid,"INT_HOUSE","BED_In_R",4.0,0,0,1,1,0);
}

CMD:cover(playerid, params[])
{
	return OnPlayAnim(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
}

alias:stance("durus");
CMD:stance(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/durus [1-13]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"PED","WOMAN_IDLESTANCE",4.0,1,0,0,0,0);
		case 2: OnPlayAnim(playerid,"PED","CAR_HOOKERTALK",4.0,1,0,0,0,0);
		case 3: OnPlayAnim(playerid,"FAT","FatIdle",4.0,1,0,0,0,0);
		case 4: OnPlayAnim(playerid,"WUZI","Wuzi_Stand_Loop",4.0,1,0,0,0,0);
		case 5: OnPlayAnim(playerid,"GRAVEYARD","mrnm_loop",4.0,1,0,0,0,0);
		case 6: OnPlayAnim(playerid,"GRAVEYARD","prst_loopa",4.0,1,0,0,0,0);
		case 7: OnPlayAnim(playerid,"PED","idlestance_fat",4.0,1,0,0,0,0);
		case 8: OnPlayAnim(playerid,"PED","idlestance_old",4.0,1,0,0,0,0);
		case 9: OnPlayAnim(playerid,"PED","turn_l",4.0,1,0,0,0,0);
		case 10: OnPlayAnim(playerid,"BAR","Barcustom_loop",4.0,1,0,0,0,0);
		case 11: OnPlayAnim(playerid,"BAR","Barserve_loop",4.0,1,0,0,0,0);
		case 12: OnPlayAnim(playerid,"DEALER","DEALER_IDLE",4.0,1,0,0,0,0);
		case 13: OnPlayAnim(playerid, "DEALER", "DEALER_IDLE", 3.0,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/durus [1-13]");
	}
	return 1;
}

alias:yell("bagirma");
CMD:yell(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/bagirma [1-3]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"ON_LOOKERS","shout_loop",3.0,1,0,0,0,0);
		case 2: OnPlayAnim(playerid,"ON_LOOKERS","shout_01",3.0,1,0,0,0,0);
		case 3: OnPlayAnim(playerid,"ON_LOOKERS","shout_02",3.0,1,0,0,0,0);
		default: SendHelpMessage(playerid, "/bagirma [1-3]");
	}
	return 1;
}

CMD:gsign(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type))	return SendHelpMessage(playerid, "/gsign [1-10]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"GHANDS","gsign1",4.1,0,1,1,1,1);
		case 2: OnPlayAnim(playerid,"GHANDS","gsign1LH",4.1,0,1,1,1,1);
		case 3: OnPlayAnim(playerid,"GHANDS","gsign2",4.1,0,1,1,1,1);
		case 4: OnPlayAnim(playerid,"GHANDS","gsign2LH",4.1,0,1,1,1,1);
		case 5: OnPlayAnim(playerid,"GHANDS","gsign3",4.1,0,1,1,1,1);
		case 6: OnPlayAnim(playerid,"GHANDS","gsign3LH",4.1,0,1,1,1,1);
		case 7: OnPlayAnim(playerid,"GHANDS","gsign4",4.1,0,1,1,1,1);
		case 8: OnPlayAnim(playerid,"GHANDS","gsign4LH",4.1,0,1,1,1,1);
		case 9: OnPlayAnim(playerid,"GHANDS","gsign5",4.1,0,1,1,1,1);
		case 10: OnPlayAnim(playerid,"GHANDS","gsign5LH",4.1,0,1,1,1,1);
		default: SendHelpMessage(playerid, "/gsign [1-10]");
	}
	return 1;
}

CMD:rap(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/rap [1-9]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"RAPPING","RAP_A_Loop",4.0,1,0,0,0,0);
		case 2: OnPlayAnim(playerid,"RAPPING","RAP_C_Loop",4.0,1,0,0,0,0);
		case 3: OnPlayAnim(playerid,"GANGS","prtial_gngtlkD",4.0,1,0,0,1,1);
		case 4: OnPlayAnim(playerid,"GANGS","prtial_gngtlkH",4.0,1,0,0,1,1);
		case 5: OnPlayAnim(playerid,"GANGS","prtial_gngtlkF",4.0,1,0,0,1,1);
		case 6: OnPlayAnim(playerid,"GANGS","prtial_gngtlkG",4.0,1,0,0,1,1);
		case 7: OnPlayAnim(playerid,"PED","ATM",4.0,0,0,0,0,0);
		case 8: OnPlayAnim(playerid,"RAPPING","RAP_B_IN",3.0,0,1,1,1,0);
		case 9: OnPlayAnim(playerid,"GYMNASIUM","gym_tread_celebrate",4.1,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/rap [1-9]");
	}
	return 1;
}

alias:tired("hasta");
CMD:tired(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/hasta [1-2]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"PED","IDLE_tired",3.0,1,0,0,0,0);
		case 2: OnPlayAnim(playerid,"FAT","IDLE_tired",4.0,0,0,1,1,0);
		default: SendHelpMessage(playerid, "/hasta [1-2]");
	}
	return 1;
}

alias:sit("otur");
CMD:sit(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/otur [1-7]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"PED","SEAT_down",4.0,0,0,1,1,0);
		case 2: OnPlayAnim(playerid,"MISC","seat_lr",2.0,1,0,0,0,0);
		case 3: OnPlayAnim(playerid,"MISC","seat_talk_01",2.0,1,0,0,0,0);
		case 4: OnPlayAnim(playerid,"MISC","seat_talk_02",2.0,1,0,0,0,0);
		case 5: OnPlayAnim(playerid,"INT_OFFICE","OFF_Sit_Crash",4.0,1,0,1,1,0);
		case 6: OnPlayAnim(playerid,"INT_OFFICE","OFF_Sit_Drink",4.0,1,0,1,1,0);
		case 7: OnPlayAnim(playerid,"INT_OFFICE","OFF_Sit_Watch",4.0,0,0,1,1,0);
		default: SendHelpMessage(playerid, "/otur [1-7]");
	}
	return 1;
}

alias:dance("dans");
CMD:dance(playerid, params[])
{
	new type;

	if (PlayerInfo[playerid][pInjured] || IsPlayerInAnyVehicle(playerid) || JackingEngine[playerid] != 0 || JackingLock[playerid] != 0) return 1;
	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/dans [1-12]");

	switch(type)
	{
		case 1:	SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE1);
		case 2: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE2);
		case 3: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE3);
		case 4: SetPlayerSpecialAction(playerid,SPECIAL_ACTION_DANCE4);
		case 5: OnPlayAnim(playerid,"DANCING","bd_clap",4.1,1,1,1,1,1);
		case 6: OnPlayAnim(playerid,"DANCING","bd_clap1",4.1,1,1,1,1,1);
		case 7: OnPlayAnim(playerid,"DANCING","DAN_Down_A",4.1,1,1,1,1,1);
		case 8: OnPlayAnim(playerid,"DANCING","DAN_Left_A",4.1,1,1,1,1,1);
		case 9: OnPlayAnim(playerid,"DANCING","DAN_Loop_A",4.1,1,1,1,1,1);
		case 10: OnPlayAnim(playerid,"DANCING","DAN_Right_A",4.1,1,1,1,1,1);
		case 11: OnPlayAnim(playerid,"DANCING","DAN_Up_A",4.1,1,1,1,1,1);
		case 12: OnPlayAnim(playerid,"DANCING","dnce_M_a",4.1,1,1,1,1,1);
		default: SendHelpMessage(playerid, "/dans [1-12]");
	}
	return 1;
}

alias:injured("yarali2");
CMD:injured(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/yarali2 [1-2]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid, "SWEET", "Sweet_injuredloop", 4.0,0,0,1,1,0);
		case 2: OnPlayAnim(playerid, "WUZI", "CS_Dead_Guy", 4.0, 1, 1, 1, 1, 0);
		default: SendHelpMessage(playerid, "/yarali2 [1-2]");
	}
	return 1;
}

alias:handsup("elkaldir");
CMD:handsup(playerid, params[])
{
	if (pTemp[playerid][pTaserTime] || PlayerInfo[playerid][pInjured] || IsPlayerInAnyVehicle(playerid) || JackingEngine[playerid] != 0)	return 1;

	return OnPlayAnim(playerid, "ROB_BANK","SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
}

alias:deal("alisveris");
CMD:deal(playerid, params[])
{
	return OnPlayAnim(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
}

alias:piss("ise");
CMD:piss(playerid, params[])
{
	return OnPlayAnim(playerid,"PAULNMAC","Piss_in",4.1,0,1,1,1,0);
}

CMD:riot(playerid, params[])
{
	return OnPlayAnim(playerid,"RIOT","RIOT_ANGRY",4.0,0,0,0,0,0);
}

CMD:slapass(playerid, params[])
{
	return OnPlayAnim(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
}

alias:wave("elsalla");
CMD:wave(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/elsalla [1-4]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid, "KISSING","gfwave2", 4.1,0,1,1,0,0);
		case 2: OnPlayAnim(playerid, "ON_LOOKERS","wave_loop", 4.1,1,1,1,0,0);
		case 3: OnPlayAnim(playerid,"CAMERA","camstnd_cmon",4.0,0,0,0,0,0);
		case 4: OnPlayAnim(playerid,"PED","endchat_01",4.1,0,1,1,0,0);
		default: SendHelpMessage(playerid, "/elsalla [1-4]");
	}
	return 1;
}

CMD:crossarms(playerid, params[])
{
	return OnPlayAnim(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
}

alias:lean("yaslan");
CMD:lean(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/yaslan [1-3]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"GANGS","leanIDLE",4.0,0,0,1,1,0);
		case 2: OnPlayAnim(playerid,"MISC","Plyrlean_loop",4.0,0,1,1,1,0);
		case 3: OnPlayAnim(playerid,"CAR_CHAT","car_talkm_loop",4.0,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/yaslan [1-3]");
	}
	return 1;
}

CMD:basket(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/basket [1-7]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"BSKTBALL","BBALL_idleloop",4.0,1,0,0,0,0);
		case 2: OnPlayAnim(playerid,"BSKTBALL","BBALL_Jump_Shot",4.0,0,0,0,0,0);
		case 3: OnPlayAnim(playerid,"BSKTBALL","BBALL_pickup",4.0,0,0,0,0,0);
		case 4: OnPlayAnim(playerid,"BSKTBALL","BBALL_run",4.1,1,1,1,1,1);
		case 5: OnPlayAnim(playerid,"BSKTBALL","BBALL_def_loop",4.0,1,0,0,0,0);
		case 6: OnPlayAnim(playerid,"BSKTBALL","BBALL_Dnk",4.0,0,0,0,0,0);
		case 7: OnPlayAnim(playerid,"BSKTBALL","BBALL_walk",4.1,1,1,1,1,1);
		default: SendHelpMessage(playerid, "/basket [1-6]");
	}
	return 1;
}

CMD:lookout(playerid, params[])
{
	new type;

	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/lookout [1-2]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"SWAT","swt_wllpk_L",4.0,0,0,1,1,0);
		case 2: OnPlayAnim(playerid,"SWAT","swt_wllpk_R",4.0,0,0,1,1,0);
		default: SendHelpMessage(playerid, "/lookout [1-2]");
	}
	return 1;
}

CMD:dunk(playerid, params[])
{
	return OnPlayAnim(playerid,"BSKTBALL","BBALL_Dnk",4.0,0,0,0,0,0);
}

CMD:win(playerid, params[])
{
	return OnPlayAnim(playerid,"OTB","wtchrace_win",4.1,0,1,1,1,0);
}

alias:walking("yuru");
CMD:walking(playerid, params[])
{
	new type;
	if (sscanf(params,"d",type)) return SendHelpMessage(playerid, "/yuru [1-17]");
	    
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"PED","WALK_civi",4.1,1,1,1,1,1);
		case 2: OnPlayAnim(playerid,"PED","WALK_gang1",4.1,1,1,1,1,1);
		case 3: OnPlayAnim(playerid,"PED","WOMAN_walksexy",4.1,1,1,1,1,1);
		case 4: OnPlayAnim(playerid,"PED","WALK_armed",4.1,1,1,1,1,1);
		case 5: OnPlayAnim(playerid,"PED","WALK_csaw",4.1,1,1,1,1,1);
		case 6: OnPlayAnim(playerid,"PED","WALK_gang2",4.1,1,1,1,1,1);
		case 7: OnPlayAnim(playerid,"PED","WALK_drunk",4.1,1,1,1,1,1);
		case 8: OnPlayAnim(playerid,"PED","WALK_fat",4.1,1,1,1,1,1);
		case 9: OnPlayAnim(playerid,"PED","WALK_fatold",4.1,1,1,1,1,1);
		case 10: OnPlayAnim(playerid,"PED","WALK_old",4.1,1,1,1,1,1);
		case 11: OnPlayAnim(playerid,"PED","WALK_rocket",4.1,1,1,1,1,1);
		case 12: OnPlayAnim(playerid,"PED","WALK_shuffle",4.1,1,1,1,1,1);
		case 13: OnPlayAnim(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
		case 14: OnPlayAnim(playerid,"PED","WOMAN_walkpro",4.1,1,1,1,1,1);
		case 15: OnPlayAnim(playerid,"PED","WOMAN_walkbusy",4.1,1,1,1,1,1);
		case 16: OnPlayAnim(playerid,"PED","WOMAN_walknorm",4.1,1,1,1,1,1);
		case 17: OnPlayAnim(playerid,"PED","Walk_Wuzi",4.1,1,1,1,1,1);
		default: SendHelpMessage(playerid, "/yuru [1-17]");
	}
	return 1;
}

alias:smoking("sigaraic");
CMD:smoking(playerid,params[])
{
	new type; 

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/sigaraic [1-4]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		case 2: OnPlayAnim(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		case 3: OnPlayAnim(playerid, "SMOKING","M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0);
		case 4: OnPlayAnim(playerid, "SMOKING","M_smk_out", 4.0, 0, 0, 0, 0, 0);
		default: SendHelpMessage(playerid, "/sigaraic [1-4]");
	}
	return 1;
}

alias:eating("yemekye");
CMD:eating(playerid)
{
	return OnPlayAnim(playerid, "FOOD", "EAT_Burger", 4.1,1,1,1,1,1);
}

alias:sipdrink("ic");
CMD:sipdrink(playerid)
{
	return OnPlayAnim(playerid, "GANGS", "drnkbr_prtl", 4.1,1,1,1,1,1);
}

CMD:chat(playerid)
{
	return OnPlayAnim(playerid,"PED","IDLE_CHAT",4.0,1,0,0,1,1);
}

CMD:fucku(playerid)
{
	return OnPlayAnim(playerid,"PED","fucku",4.0,0,0,0,0,0);
}

CMD:taichi(playerid)
{
	return OnPlayAnim(playerid,"PARK","Tai_Chi_Loop",4.0,1,0,0,0,0);
}

alias:no("hayir");
CMD:no(playerid)
{
	return OnPlayAnim(playerid,"GANGS","Invite_No",4.0,0,0,0,0,0);
}

alias:yes("evet");
CMD:yes(playerid)
{
	return OnPlayAnim(playerid,"GANGS","Invite_Yes",4.0,0,0,0,0,0);
}

CMD:crawl(playerid)
{
	return OnPlayAnim(playerid,"PED","CAR_crawloutRHS",4.0,0,0,0,0,0);
}

alias:push("ittir");
CMD:push(playerid)
{
	return OnPlayAnim(playerid,"GANGS","shake_cara",4.0,0,0,0,0,0);
}

alias:superkick("tekme");
CMD:superkick(playerid)
{
	return OnPlayAnim(playerid,"POLICE","Door_Kick",4.0,0,0,0,0,0);
}

CMD:facepalm(playerid)
{
	return OnPlayAnim(playerid,"MISC","plyr_shkhead",4.0,0,0,0,0,0);
}

alias:balls("kasi");
CMD:balls(playerid)
{
	return OnPlayAnim(playerid,"MISC","scratchballs_01",4.0,0,0,0,0,0);
}

alias:lowbodypush("vucutittir");
CMD:lowbodypush(playerid)
{
	return OnPlayAnim(playerid,"GANGS","shake_carSH",4.0,0,0,0,0,0);
}

alias:spraying("sprey");
CMD:spraying(playerid)
{
	return OnPlayAnim(playerid,"SPRAYCAN","spraycan_full",4.0,0,0,0,0,0);
}

alias:medic("ilkyardim");
CMD:medic(playerid)
{
	return OnPlayAnim(playerid,"MEDIC","CPR",4.0,0,0,0,0,0);
}
alias:koface("yumrukye");
CMD:koface(playerid)
{
	return OnPlayAnim(playerid,"PED","KO_shot_face",4.0,0,1,1,1,0);
}

alias:kostomach("yereyigil");
CMD:kostomach(playerid)
{
	return OnPlayAnim(playerid,"PED","KO_shot_stom",4.0,0,1,1,1,0);
}

CMD:lifejump(playerid)
{
	return OnPlayAnim(playerid,"PED","EV_dive",4.0,0,1,1,1,0);
}

alias:rollfall("yuvarlan");
CMD:rollfall(playerid)
{
	return OnPlayAnim(playerid,"PED","BIKE_fallR",4.0,0,1,1,1,0);
}

alias:hoodfrisked("frisked");
CMD:hoodfrisked(playerid)
{
	return OnPlayAnim(playerid,"POLICE","crm_drgbst_01",1.0,0,1,1,1,0);
}

CMD:flip(playerid)
{
	return OnPlayAnim(playerid,"PED","KD_left",4.1,0,1,1,1,0);
}

CMD:frontfall(playerid)
{
	return OnPlayAnim(playerid,"PED","FLOOR_hit_f",4.1,0,1,1,1,0);
}

CMD:box(playerid)
{
	return OnPlayAnim(playerid,"GYMNASIUM","GYMshadowbox",4.0,1,1,1,1,0);
}

CMD:chant(playerid)
{
	return OnPlayAnim(playerid,"RIOT","RIOT_CHANT",4.0,1,1,1,1,0);
}

CMD:finger(playerid)
{
	return OnPlayAnim(playerid,"RIOT","RIOT_FUKU",2.0,0,0,0,0,0);
}

CMD:gpunch(playerid)
{
	return OnPlayAnim(playerid,"FIGHT_B","FightB_G",4.0,0,0,0,0,0);
}

CMD:gkick(playerid)
{
	return OnPlayAnim(playerid,"FIGHT_D","FightD_G",4.0,0,0,0,0,0);
}

CMD:lowthrow(playerid)
{
	return OnPlayAnim(playerid,"GRENADE","WEAPON_throwu",3.0,0,0,0,0,0);
}

CMD:bp(playerid)
{
	return OnPlayAnim(playerid,"benchpress","gym_bp_celebrate",4.0,0,0,0,0,0);
}

CMD:taxir(playerid)
{
	return OnPlayAnim(playerid,"MISC","Hiker_Pose",4.0,0,1,1,1,0);
}

CMD:taxil(playerid)
{
	return OnPlayAnim(playerid,"MISC","Hiker_Pose_L",4.0,0,1,1,1,0);
}

CMD:gro(playerid)
{
	return OnPlayAnim(playerid,"BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
}

CMD:seat(playerid)
{
	return OnPlayAnim(playerid,"INT_HOUSE","LOU_In",4.0,0,0,1,1,0);
}

CMD:tatto(playerid)
{
	return OnPlayAnim(playerid,"TATTOOS", "TAT_ArmR_Pose_P", 4.1, 0, 1, 1, 1, 0 );
}
CMD:bar(playerid)
{
	return OnPlayAnim(playerid,"BAR","Barserve_bottle",4.0,0,1,1,1,0);
}
CMD:stoptaxi(playerid)
{
	return OnPlayAnim(playerid,"PED","IDLE_taxi",4.0,0,0,0,0,0);
}
CMD:police(playerid,params[])
{
	new type;

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/police [1-4]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"POLICE","CopTraf_Away",3.0,1,0,0,1,0);
		case 2: OnPlayAnim(playerid,"POLICE","CopTraf_Come",3.0,1,0,0,1,0);
		case 3: OnPlayAnim(playerid,"POLICE","CopTraf_Left",3.0,1,0,0,1,0);
		case 4: OnPlayAnim(playerid,"POLICE","CopTraf_Stop",3.0,1,0,0,1,0);
		default: SendHelpMessage(playerid, "/police [1-4]");
	}
	return 1;
}

CMD:waiml(playerid)
{
	return OnPlayAnim(playerid,"PED","Driveby_L",4.1,0,1,1,1,1);
}

CMD:waimr(playerid)
{
	return OnPlayAnim(playerid,"PED","Driveby_R",4.1,0,1,1,1,1);
}

CMD:lookback(playerid)
{
	return OnPlayAnim(playerid,"PED","flee_lkaround_01",4.0,0,0,0,0,0);
}

CMD:caim(playerid)
{
	return OnPlayAnim(playerid,"PED","IDLE_ROCKET",4.0,0,1,1,1,0);
}

CMD:creep(playerid)
{
	return OnPlayAnim(playerid,"PED","Player_Sneak",4.1,1,1,1,1,1);
}

CMD:sroll(playerid)
{
	return OnPlayAnim(playerid,"SWAT","JMP_Wall1m_180",4.1,0,1,1,1,0);
}

CMD:gesture(playerid)
{
	return OnPlayAnim(playerid,"SWAT","swt_lkt",4.0,0,0,0,0,0);
}

CMD:agreement(playerid)
{
	return OnPlayAnim(playerid,"COP_AMBIENT","Coplook_think",4.0,1,0,0,0,0);
}

CMD:bend(playerid)
{
	return OnPlayAnim(playerid,"BAR","Barserve_order",4.0,0,0,0,0,0);
}

CMD:rod(playerid)
{
	return OnPlayAnim(playerid,"benchpress","gym_bp_up_A",4.0,0,0,1,1,0);
}

CMD:tgro(playerid)
{
	return OnPlayAnim(playerid,"CAMERA","camcrch_cmon",4.0,0,0,1,1,0);
}

CMD:cmouth(playerid)
{
	return OnPlayAnim(playerid,"ON_LOOKERS","panic_in",4.0,0,0,1,1,0);
}

CMD:gog(playerid)
{
	return OnPlayAnim(playerid,"goggles","goggles_put_on",4.1,0,1,1,1,1);
}

CMD:nfall(playerid)
{
	return OnPlayAnim(playerid,"HEIST9","CAS_G2_GasKO",4.1,0,1,1,1,0);
}

CMD:hsit(playerid)
{
	return OnPlayAnim(playerid,"INT_OFFICE","OFF_Sit_Bored_Loop",4.0,1,0,1,1,0);
}

CMD:csit(playerid)
{
	return OnPlayAnim(playerid,"INT_OFFICE","OFF_Sit_Type_Loop",4.0,1,0,1,1,0);
}

CMD:bracing(playerid)
{
	return OnPlayAnim(playerid,"PLAYIDLES","stretch",4.0,0,0,0,0,0);
}

CMD:pool(playerid)
{
	return OnPlayAnim(playerid,"POOL","POOL_Long_Start",4.1,0,1,1,1,0);
}

CMD:search(playerid)
{
	return OnPlayAnim(playerid,"ROB_BANK","CAT_Safe_Rob",4.0,1,0,0,0,0);
}

CMD:daim(playerid)
{
	return OnPlayAnim(playerid,"RYDER","Van_Stand_Crate",3.0,0,1,1,1,0);
}

CMD:rhandl(playerid)
{
	return OnPlayAnim(playerid,"SCRATCHING","scdlulp",4.0,0,0,1,1,0);
}

CMD:rhandr(playerid)
{
	return OnPlayAnim(playerid,"SCRATCHING","scdrulp",4.0,0,0,1,1,0);
}

CMD:hstand(playerid)
{
	return OnPlayAnim(playerid,"SCRATCHING","scdrdlp",4.0,0,0,1,1,0);
}

CMD:nlean(playerid)
{
	return OnPlayAnim(playerid,"SHAMAL","SHAMAL_align",4.1,0,1,1,1,0);
}

CMD:shelter(playerid)
{
	return OnPlayAnim(playerid,"SHOP","SHP_Duck_Fire",4.0,0,0,1,1,0);
}

CMD:wsit(playerid)
{
	return OnPlayAnim(playerid,"SHOP","SHP_Gun_Duck",4.0,0,0,1,1,0);
}

CMD:waim(playerid)
{
	return OnPlayAnim(playerid,"TEC","TEC_reload",4.1,0,1,1,1,1);
}

CMD:hangon(playerid)
{
	return OnPlayAnim(playerid,"TRAIN","tran_ouch",4.0,0,0,1,1,0);
}

CMD:polwalk(playerid)
{
	return OnPlayAnim(playerid,"POLICE","Cop_move_FWD",3.0,1,1,1,1,1);
}

CMD:wallow(playerid,params[])
{
	new type;

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/wallow [1-2]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll",4.1,0,1,1,1,0);
		case 2: OnPlayAnim(playerid,"MD_CHASE","MD_BIKE_Lnd_Roll_F",4.1,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/wallow [1-2]");
	}
	return 1;
}

CMD:nflip(playerid)
{
	return OnPlayAnim(playerid,"PED","BIKE_fall_off",4.1,0,1,1,1,0);
}

CMD:csdead(playerid)
{
	return OnPlayAnim(playerid,"WUZI","CS_Dead_Guy",4.1,1,1,1,1,0);
}

CMD:follow(playerid)
{
	return OnPlayAnim(playerid,"WUZI","Wuzi_follow",4.1,0,1,1,1,1);
}

CMD:grnd(playerid)
{
	return OnPlayAnim(playerid,"WUZI","Wuzi_grnd_chk",4.0,0,0,0,0,0);
}

CMD:copa(playerid)
{
	return OnPlayAnim(playerid,"COP_AMBIENT","Copbrowse_in",4.1,0,1,1,1,0);
}

CMD:cmon(playerid)
{
	return OnPlayAnim(playerid,"OTB","wtchrace_cmon",4.1,0,1,1,1,0);
}

CMD:lose(playerid)
{
	return OnPlayAnim(playerid,"OTB","wtchrace_lose",4.1,0,1,1,1,0);
}

CMD:gunthreat(playerid)
{
	return OnPlayAnim(playerid,"SHOP","SHP_Gun_Threat",4.1,0,1,1,1,0);
}

CMD:givecash(playerid)
{
	return OnPlayAnim(playerid,"SHOP","SHP_Rob_GiveCash",4.1,0,1,1,1,0);
}

CMD:robr(playerid)
{
	return OnPlayAnim(playerid,"SHOP","SHP_Rob_React",4.1,0,1,1,1,0);
}

CMD:serend(playerid)
{
	return OnPlayAnim(playerid,"SHOP","SHP_Serve_End",4.1,0,1,1,1,0);
}

CMD:heist(playerid)
{
	return OnPlayAnim(playerid,"HEIST9","Use_SwipeCard",4.0,0,0,0,0,0);
}

CMD:beckon(playerid,params[])
{
	new type;
	
	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/beckon [1-3]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"RYDER","RYD_Beckon_01",4.1,0,1,1,1,1);
		case 2: OnPlayAnim(playerid,"RYDER","RYD_Beckon_02",4.1,0,1,1,1,1);
		case 3: OnPlayAnim(playerid,"RYDER","RYD_Beckon_03",4.1,0,1,1,1,1);
		default: SendHelpMessage(playerid, "/beckon [1-3]");
	}
	return 1;
}

CMD:pompali(playerid,params[])
{
	new type;

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/pompali [1-3]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"SHOTGUN","shotgun_crouchfire",4.1,0,1,1,1,1);
		case 2: OnPlayAnim(playerid,"SHOTGUN","shotgun_fire",4.1,0,1,1,1,1);
		case 3: OnPlayAnim(playerid,"SHOTGUN","shotgun_fire_poor",4.1,0,1,1,1,1);
		default: SendHelpMessage(playerid, "/pompali [1-3]");
	}
	return 1;
}

CMD:colt(playerid,params[])
{
	new type;

	if (sscanf(params,"i", type))	return SendHelpMessage(playerid, "/colt [1-3]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"COLT45","colt45_fire_2hands",4.1,0,1,1,1,1);
		case 2: OnPlayAnim(playerid,"COLT45","colt45_reload",4.1,0,1,1,1,1);
		case 3: OnPlayAnim(playerid,"COLT45","sawnoff_reload",4.1,0,1,1,1,1);
		default: SendHelpMessage(playerid, "/colt [1-3]");
	}
	return 1;
}

CMD:climb(playerid)
{
	return OnPlayAnim(playerid,"PED","CLIMB_jump",4.0,0,0,1,1,0);
}

CMD:tlean(playerid)
{
	return OnPlayAnim(playerid,"PED","DRIVE_BOAT",4.0,0,0,1,1,0);
}

CMD:pushup(playerid)
{
	return OnPlayAnim(playerid,"PED","getup_front",4.0,1,0,1,1,0);
}

CMD:protection(playerid)
{
	return OnPlayAnim(playerid,"PED","FightShB",4.0,0,1,1,1,1);
}

CMD:swallow(playerid)
{
	return OnPlayAnim(playerid,"PED","gum_eat",4.0,0,0,0,0,0);
}

CMD:stand(playerid)
{
	return OnPlayAnim(playerid,"PED","IDLE_HBHB",3.0,0,1,1,1,0);
}

CMD:pullhand(playerid)
{
	return OnPlayAnim(playerid,"PED","Jetpack_Idle",3.0,0,1,1,1,0);
}

CMD:nlook(playerid)
{
	return OnPlayAnim(playerid,"PED","roadcross_gang",4.0,0,0,0,0,0);
}

CMD:extend(playerid)
{
	return OnPlayAnim(playerid,"PED","Shove_Partial",4.1,0,1,1,1,1);	
}

CMD:car(playerid,params[])
{
	new type;

	if (!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "Araçta olmalýsýnýz.");
	if (IsDriver(playerid))				return SendErrorMessage(playerid, "Sürücü koltuðundaki kiþiler animasyon yapamaz.");
	if (sscanf(params,"d", type))		return SendHelpMessage(playerid, "/car [1-11]");
	
	switch(type)
	{
		case 1: ApplyAnimation(playerid,"LOWRIDER","lrgirl_bdbnce",4.1,0,1,1,1,0,1);
		case 2: ApplyAnimation(playerid,"LOWRIDER","lrgirl_hair",4.1,0,1,1,1,0,1);
		case 3: ApplyAnimation(playerid,"LOWRIDER","lrgirl_idle_to_l0",4.1,0,1,1,1,0,1);
		case 4: ApplyAnimation(playerid,"PED","Tap_hand",4.1,0,1,1,1,0,1);
		case 5: ApplyAnimation(playerid,"PED","Tap_handP",4.1,0,1,1,1,0,1);
		case 6: ApplyAnimation(playerid,"LOWRIDER","lrgirl_l12_to_l0",4.1,0,1,1,1,0,1);
		case 7: ApplyAnimation(playerid,"LOWRIDER","lrgirl_l2_to_l3",4.1,0,1,1,1,0,1);
		case 8: ApplyAnimation(playerid,"PED","CAR_LB",4.1,0,1,1,1,0,1);
		case 9: ApplyAnimation(playerid,"PED","CAR_sitp",4.1,0,1,1,1,0,1);
		case 10: ApplyAnimation(playerid,"PED","CAR_sitpLO",4.1,0,1,1,1,0,1);
		case 11: ApplyAnimation(playerid,"CAR_CHAT","carfone_loopA",4.1,1,1,1,1,0,1);
		default: SendHelpMessage(playerid, "/car [1-11]");
	}
	return 1;
}

CMD:repcar(playerid,params[])
{
	new type;

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/repcar [1-2]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"CAR","Fixn_Car_Loop",3.0,0,1,1,1,0);
		case 2: OnPlayAnim(playerid,"CAR","Fixn_Car_Out",3.0,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/repcar [1-2]");
	}
	return 1;
}

CMD:onehand(playerid)
{
	return OnPlayAnim(playerid,"PED","CLIMB_jump2fall",4.1,0,1,1,1,0);
}

CMD:backwalk(playerid)
{
	return OnPlayAnim(playerid,"PED","gas_cwr",4.1,1,1,1,1,1);
}

CMD:mirro(playerid)
{
	return OnPlayAnim(playerid,"CLOTHES","CLO_Pose_Hat",4.1,0,1,1,1,0);
}

CMD:hips(playerid)
{
	return OnPlayAnim(playerid,"COP_AMBIENT","Coplook_shake",4.1,0,1,1,1,0);
}

CMD:pullo(playerid)
{
	return OnPlayAnim(playerid,"AIRPORT","thrw_barl_thrw",4.1,0,1,1,1,0);
}

CMD:rtake(playerid)
{
	return OnPlayAnim(playerid,"BAR","Barserve_give",4.0,0,0,0,0,0);
}

CMD:obalance(playerid)
{
	return OnPlayAnim(playerid,"BD_FIRE","BD_Panic_02",4.1,0,1,1,1,0);
}

CMD:wobalance(playerid)
{
	return OnPlayAnim(playerid,"BD_FIRE","BD_Panic_03",4.1,0,1,1,1,0);
}

CMD:taction(playerid)
{
	return OnPlayAnim(playerid,"BD_FIRE","wash_up",4.0,0,0,0,0,0);
}

CMD:catch(playerid)
{
	return OnPlayAnim(playerid,"MD_CHASE","MD_HANG_Loop",4.1,0,1,1,1,0);
}

CMD:despair(playerid)
{
	return OnPlayAnim(playerid,"BSKTBALL","BBALL_react_miss",4.0,0,0,0,0,0);
}

CMD:rooting(playerid)
{
	return OnPlayAnim(playerid,"BSKTBALL","BBALL_react_score",4.1,1,1,1,1,0);
}

CMD:spyglass(playerid)
{
	return OnPlayAnim(playerid,"CAMERA","picstnd_take",4.1,0,1,1,1,0);
}

CMD:looksky(playerid)
{
	return OnPlayAnim(playerid,"ON_LOOKERS","lkup_loop",4.1,0,1,1,1,0);
}

CMD:show(playerid,params[])
{
	new type;

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/show [1-3]");

	switch(type)
	{
		case 1: OnPlayAnim(playerid,"ON_LOOKERS","panic_point",4.1,0,1,1,1,0);
		case 2: OnPlayAnim(playerid,"ON_LOOKERS","panic_shout",4.1,0,1,1,1,0);
		case 3: OnPlayAnim(playerid,"ON_LOOKERS","point_loop",4.1,0,1,1,1,0);
		default: SendHelpMessage(playerid, "/show [1-3]");
	}
	return 1;
}

CMD:sh(playerid)
{
	return OnPlayAnim(playerid,"ON_LOOKERS","shout_in",4.0,0,0,0,0,0);
}

CMD:crossfingers(playerid)
{
	return OnPlayAnim(playerid,"CASINO","cards_loop",4.1,0,1,1,1,0);
}

CMD:delight(playerid)
{
	return OnPlayAnim(playerid,"CASINO","manwinb",4.0,0,0,0,0,0);
}

CMD:hdelight(playerid)
{
	return OnPlayAnim(playerid,"CASINO","manwind",4.0,0,0,0,0,0);
}

CMD:showtable(playerid)
{
	return OnPlayAnim(playerid,"CASINO","Roulette_bet",4.1,0,1,1,1,0);
}

CMD:tfacepalm(playerid)
{
	return OnPlayAnim(playerid,"CASINO","Roulette_lose",4.1,0,1,1,1,0);
}

CMD:tpull(playerid)
{
	return OnPlayAnim(playerid,"CASINO","Slot_in",4.1,0,1,1,1,0);
}

CMD:fail(playerid)
{
	return OnPlayAnim(playerid,"CASINO","Slot_lose_out",4.0,0,0,0,0,0);
}

CMD:joy(playerid)
{
	return OnPlayAnim(playerid,"CASINO","Slot_win_out",4.0,0,0,0,0,0);
}

CMD:wear(playerid)
{
	return OnPlayAnim(playerid,"CARRY","crry_prtial",4.1,0,1,1,1,1);
}

CMD:fsit(playerid)
{
	return OnPlayAnim(playerid,"JST_BUISNESS","girl_02",4.1,0,1,1,1,0);
}

CMD:crushjump(playerid)
{
	return OnPlayAnim(playerid,"DODGE","Crush_Jump",4.1,0,1,1,1,0);
}

CMD:scatch(playerid)
{
	return OnPlayAnim(playerid,"FINALE","FIN_LegsUp_Loop",4.1,0,1,1,1,0);
}

CMD:lookfloor(playerid)
{
	return OnPlayAnim(playerid,"FINALE","FIN_Cop1_Loop",4.1,0,1,1,1,0);
}

CMD:tramplefloor(playerid)
{
	return OnPlayAnim(playerid,"FINALE","FIN_Cop1_Stomp",4.1,1,1,1,1,0);
}

CMD:swing(playerid)
{
	return OnPlayAnim(playerid,"Freeweights","gym_free_B",4.1,0,1,1,1,0);
}

CMD:nbp(playerid)
{
	return OnPlayAnim(playerid,"Freeweights","gym_free_celebrate",4.0,0,0,0,0,0);
}

CMD:takehead(playerid)
{
	return OnPlayAnim(playerid,"HAIRCUTS","BRB_Cut",4.1,0,1,1,1,0);
}

CMD:readtable(playerid)
{
	return OnPlayAnim(playerid,"SCRATCHING","sclng_r",4.1,0,1,1,1,0);
}

CMD:squat(playerid)
{
	return OnPlayAnim(playerid,"TEC","TEC_crouchfire",4.1,0,1,1,1,0);
}

CMD:sprawl(playerid)
{
	return OnPlayAnim(playerid,"TATTOOS","TAT_Idle_Loop_T",4.1,0,1,1,1,0);
}

CMD:throwmoney(playerid)
{
	return OnPlayAnim(playerid,"STRIP","PUN_CASH",4.0,0,0,0,0,0);
}

CMD:faim(playerid)
{
	return OnPlayAnim(playerid,"SWORD","sword_IDLE",4.1,0,1,1,1,0);
}

CMD:swingback(playerid)
{
	return OnPlayAnim(playerid,"PED","getup",4.1, 0, 1, 1, 1, 0);
}

CMD:hands(playerid,params[])
{
	new type;

	if (sscanf(params,"d", type))	return SendHelpMessage(playerid, "/hands [1-7]");
	
	switch(type)
	{
		case 1: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkB",4.1,0,1,1,1,1);
		case 2: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkC",4.1,0,1,1,1,1);
		case 3: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkD",4.1,0,1,1,1,1);
		case 4: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkE",4.1,0,1,1,1,1);
		case 5: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkF",4.1,0,1,1,1,1);
		case 6: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkG",4.1,0,1,1,1,1);
		case 7: OnPlayAnim(playerid,"LOWRIDER","prtial_gngtlkH",4.1,0,1,1,1,1);
		default: SendHelpMessage(playerid, "/hands [1-7]");
	}
	return 1;
}

CMD:cellin(playerid)
{
	// TO DO
	return SetPlayerSpecialAction(playerid,SPECIAL_ACTION_USECELLPHONE);
}

CMD:cellout(playerid)
{
	// TO DO
	if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_USECELLPHONE) return SendErrorMessage(playerid, "/cellin kullanmadan bu animasyon çalýþmaz.");

	return SetPlayerSpecialAction(playerid,SPECIAL_ACTION_STOPUSECELLPHONE);
}

CMD:drunk(playerid)
{
	return OnPlayAnim(playerid,"PED","WALK_DRUNK",4.1,1,1,1,1,1);
}

CMD:kicking(playerid)
{
	return OnPlayAnim(playerid,"GANGS","shake_carK",4.0,0,0,0,0,0);
}

CMD:bomb(playerid)
{
	return OnPlayAnim(playerid, "BOMBER","BOM_Plant",4.0,0,0,0,0,0);
}