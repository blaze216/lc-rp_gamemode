//iPhone
new PlayerText: TD_iphone[MAX_PLAYERS][24],
	PlayerText: TD_iphone_block[MAX_PLAYERS][6],
	PlayerText: TD_iphone_button[MAX_PLAYERS][6],
	PlayerText: TD_iphone_name[MAX_PLAYERS],
	PlayerText: TD_iphone_menu[MAX_PLAYERS][12],
	PlayerText: TD_iphone_setting[MAX_PLAYERS][11],
	PlayerText: TD_iphone_list[MAX_PLAYERS][16],
	PlayerText: TD_iphone_contact[MAX_PLAYERS][5],
	PlayerText: TD_iphone_keypad[MAX_PLAYERS][34];

new phone_window[3] = {
    -1061109505,
    0xFFCC66FF,
    0x66B3FFFF
};

new phone_panel[3] = {
    -2139062017,
    0xE69900FF,
    0x1A8CFFFF
};

new phone_ringtons[4] = {
    23000,
    20804,
    20600,
    19600
};

new phone_model[5] = {
	18868,
	18866,
	18870,
	18871,
	18874
};

new phone_model_color[5] = {
	0x000000FF,
 	0x0F00A2FF,
 	0xBF0101FF,
 	0x006400FF,
 	0xFFFFFFFF
};

enum GPS_ENUM
{
	Float: gpsX,
	Float: gpsY,
	Float: gpsZ,
	gpsName[24]
};


new gps_location[20][GPS_ENUM] =
{
	{801.7869,-851.1774,35.0552, "LCPD HQ"},
	{752.3782,-253.4924,27.6200, "LCFD HQ"},
	{1047.2061,-628.4166,70.9264, "Sunset Motel"},
	{802.8581,-795.1089,35.1146, "Hastane"},
	{629.3817,-879.1384,35.0672, "Chinatown"},
	{1017.8837,-1015.4042,34.8716, "Portland Dock"},
	{1002.2199,-652.7724,70.0909, "Marcos Bistro"},
	{871.9237,-321.0379,35.1535, "Easy Credit Autos"},
	{718.4399,-479.8222,28.8841, "Bank of Liberty"},
	{689.4516,-897.9470,35.0684, "Central Bank of LC"},
	{2866.9553,-1406.7509,11.0105, "East Beach Bank LS"},
	{659.2625,-247.5327,27.5380, "Head News"},
    {810.4021,-295.0788,27.7434, "AM Gas Station"},
	{842.6060,-1074.6405,35.0684, "Joey Auto Painting"},
	{578.6635,-557.1876,30.9440,"Pay N Spray"},
	{935.5494,-301.8194,34.8817, "Eightballs Autoyard"},
	{945.8408,-1160.1608,35.0105, "Trucker Meslegi"},
	{922.3558,-1305.5118,32.0877, "Mekanik Meslegi"},
	{911.2131,-936.9932,35.2651, "Taksi Duragi"},
	{892.9114,-1323.0898,31.9593, "Industrial Market"}
};

enum PHONE_ENUM
{
	phoneCreated,
	phoneBlock,
	phoneContact,
	phoneSMS,
	phoneHistory,
	phoneKeypad,
	phoneGPS,
    phoneSetting,
	phoneListed[9],
	phoneBlockSMS[3]
};

new PhoneInfo[MAX_PLAYERS][PHONE_ENUM];

#define IsPlayerPhoneCreated(%0) PhoneInfo[%0][phoneCreated]

enum CONTACTS_ENUM
{
	contactID,
	contactName[24],
	contactNumber,
	contactOn
}
new PlayerContacts[MAX_PLAYERS][MAX_PLAYER_CONTACTS][CONTACTS_ENUM];
