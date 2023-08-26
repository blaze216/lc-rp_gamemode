enum PLAYER_BOOMBOX_ENUM
{
	bUsed,
	bArea,
	bUrl[156],
	Float:bPosX,
	Float:bPosY,
	Float:bPosZ,
	bInt,
	bVW,
	bObject
}
new BoomboxInfo[MAX_PLAYERS][PLAYER_BOOMBOX_ENUM],
    Iterator:boomboxIter<MAX_PLAYERS>;

enum BOOMBOX_ENUM
{
	boomboxName[64],
	boomboxUrl[156]
}
new RADIO_STATIONS[3][15][BOOMBOX_ENUM] =
{
	{
		{"Easy Hits Florida", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://us1.internet-radio.com:8180/listen.pls&t=.m3u"},
		{"RADIO 24", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk2.internet-radio.com:8080/listen.pls&t=.m3u"},
		{"Dance UK Radio", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk2.internet-radio.com:30252/listen.pls&t=.m3u"},
		{"EDM CLUB MUSIC FLORIDA", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://us1.internet-radio.com:8273/listen.pls&t=.m3u"},
		{"Psy FM", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://81.88.36.42:8030/listen.pls&t=.m3u"},
		{"181.FM Good Time Oldies", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8046/listen.pls&t=.m3u"},
		{"PONdENDS", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://s7.voscast.com:7000/listen.pls&t=.m3u"},
		{"DnBHeaven", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://dnbheaven.com:8000/listen.pls&t=.m3u"},
		{"Bassjunkees","https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://space.ducks.invasion.started.at.bassjunkees.com:8442/listen.pls&t=.m3u"},
		{"1.FM ABSOLUTE TOP 40", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://69.46.90.245:8078/listen.pls&t=.m3u"},
		{"ChartHits", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://95.141.24.3:80/listen.pls&t=.m3u"},
		{"181.FM Energy 98", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8800/listen.pls&t=.m3u"},
		{"DRUMSTEP", "http://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://95.141.24.54:80/listen.pls&t=.m3u"},
		{"Sub FM", "http://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://radio.sub.fm:8529/listen.pls?sid=1&t=.m3u"},
		{"Ambient FM", "http://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk2.internet-radio.com:31491/listen.pls&t=.m3u"}
	},
	{
		{"Smooth Jazz Florida", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://us1.internet-radio.com:8105/listen.pls&t=.m3u"},
		{"Smooth Jazz CD101.9", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://us1.internet-radio.com:8144/listen.pls&t=.m3u"},
		{"Highway 181", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://108.61.73.120:8018/listen.pls&t=.m3u"},
		{"100hitz New Country", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://173.244.215.162:9210/listen.pls&t=.m3u"},
		{"Classic Rock Florida", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://us1.internet-radio.com:8105/listen.pls&t=.m3u"},
		{"Fleetwood Mac", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://stn2.streamthenet.com:6050/listen.pls&t=.m3u"},
		{"Arrow Classic Rock", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://91.221.151.237:8109/listen.pls?sid=1&t=.m3u"},
		{"181.fm Rock", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8008/listen.pls&t=.m3u"},
		{"181.FM 80s Hairband", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8014/listen.pls&t=.m3u"},
		{"Soft Rock FM", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://173.236.21.250:8032/listen.pls&t=.m3u"},
		{"181.FM 90s Country", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8050/listen.pls&t=.m3u"},
		{"idobi Howl", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://69.46.88.29:80/listen.pls&t=.m3u"},
		{"KNAC", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://s5.voscast.com:7346/listen.pls&t=.m3u"},
		{"2000FM Hard Rock", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://107.155.111.170:18110/listen.pls&t=.m3u"},
		{"SmoothJazz Global", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://sj128.hnux.com/listen.pls&t=.m3u"}
	},
	{
		{"Pigpen Radio", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk4.internet-radio.com:30884/listen.pls&t=.m3u"},
		{"Smash FM", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk1.internet-radio.com:8106/listen.pls&t=.m3u"},
		{"BlazeRadio", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk2.internet-radio.com:8106/listen.pls&t=.m3u"},
		{"PARTY VIBE RADIO", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://www.partyviberadio.com:8004/listen.pls?sid=1&t=.m3u"},
		{"GOOD COMPANY RADIO ", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uk4.internet-radio.com:10104/listen.pls&t=.m3u"},
		{"181.FM Old School", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8068/listen.pls&t=.m3u"},
		{"LadyLinQRadio", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://us1.internet-radio.com:8336/listen.pls&t=.m3u"},
		{"DEFJAY", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://212.45.104.39:8008/listen.pls&t=.m3u"},
		{"HOT 108 JAMZ", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://108.61.30.179:4020/listen.pls&t=.m3u"},
		{"181.FM The BEAT - The BEAT", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8054/listen.pls&t=.m3u"},
		{"POWERHITZ", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://108.61.30.179:5040/listen.pls&t=.m3u"},
		{"100hitz", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://206.217.213.236:8170/listen.pls&t=.m3u"},
		{"181.FM The BOX", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://uplink.duplexfx.com:8024/listen.pls&t=.m3u"},
		{"ReggaeWorld", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://67.212.189.122:8042/listen.pls&t=.m3u"},
		{"Radio Tequila Necenzurat", "https://www.internet-radio.com/servers/tools/playlistgenerator/?u=http://necenzurat.radiotequila.ro:7000/listen.pls&t=.m3u"}
	}
};