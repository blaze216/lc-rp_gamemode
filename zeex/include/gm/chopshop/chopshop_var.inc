#define MAX_CHOPSHOP 15
#define CHOPSHOP_PRICE (25000)

enum CHOPSHOP_DATA
{
	chopshop_id,
	chopshop_wanted[10],
    Float: chopshop_pos[6],
    chopshop_faction, // can run by a faction, they can
    chopshop_object[2],
    chopshop_money,
    chopshop_vehs,
    chopshop_procent,
    chopshop_timer,
    bool:chopshop_exist
}
new chopshop_data[MAX_CHOPSHOP][CHOPSHOP_DATA];