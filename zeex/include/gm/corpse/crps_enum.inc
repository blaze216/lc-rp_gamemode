#define MAX_CORPS 50

enum cpInfo
{
	cUsed,
	cType,
	cName[MAX_PLAYER_NAME],
	cTime,
	Float:cX,
	Float:cY,
	Float:cZ,
	Text3D:cText,
	cVeh,
	cNote[170],
	cSkin,
	cBody
};
new CorpInfo[MAX_CORPS][cpInfo];