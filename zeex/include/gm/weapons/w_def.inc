#define INJURED_LEG_TIME        (30)        
//How many seconds after receiving a wound in the leg the character will not be able to jump

#define WEAPON_TYPE_NONE        0
#define WEAPON_TYPE_PRIMARY 	1
#define WEAPON_TYPE_SECONDARY 	2
#define WEAPON_TYPE_MELEE 		3
//î

new aWeaponNames[][] = 
{
    {"Fist"},
    {"Brass Knuckless"},
    {"Golf Club"},
    {"Nightstick"},
    {"Knife"},
    {"Baseball Bat"},
    {"Shovel"},
    {"Pool Cue"},
    {"Katana"},
    {"Chainsaw"},
    {"Purple Dildo"},
    {"Dildo"},
    {"Vibrator"},
    {"Silver Vibrator"},
    {"Flowers"},
    {"Cane"},
    {"Grenade"},
    {"Tear Gas"},
    {"Molotof Kokteyli"},
    {"Unknown"},
    {"Unknown"},
    {"Unknown"},
    {"Colt 45"},
    {"Silenced 9mm"},
    {"Desert Eagle"},
    {"Shotgun"},
    {"Sawnoff Shotgun"},
    {"40MM Grenade Launcher"},
    {"Micro SMG"},
    {"MP5"},
    {"AK-47"},
    {"M4"},
    {"Tec-9"},
    {"Country Rifle"},
    {"Sniper Rifle"},
    {"RPG"},
    {"HS Rocket"},
    {"Flamethrower"},
    {"Minigun"},
    {"Satchel Charge"},
    {"Detonator"},
    {"Spray Can"},
    {"Fire Extinguisher"},
    {"Camera"},
    {"Night Goggles"},
    {"Thermal Goggles"},
    {"Parachute"}
};

GetWeaponNameEx(weaponid, bool:disassembledName = false)
{
    new name[55];
        
    format(name, sizeof(name), aWeaponNames[weaponid]);
    
    if(!weaponid)name = "Yok";
    if(strlen(name) == 0)name = "Yok";
    if(disassembledName == true) format(name, sizeof(name), "%s - mermi yok", name);

    return name;
}