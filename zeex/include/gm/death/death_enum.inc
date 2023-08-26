enum DAMAGE_ENUM
{
	damageOn,
	damageWeapon,
	damageBodypart,
	Float:damageAmount,
	damageArmour,
	damageTime,
	damageBy[MAX_PLAYER_NAME]
};
new DamageInfo[MAX_PLAYERS][MAX_DAMAGES][DAMAGE_ENUM];
