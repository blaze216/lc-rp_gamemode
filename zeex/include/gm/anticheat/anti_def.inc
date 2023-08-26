/*
    Database related settings (MySQL)
*/
#define AC_TABLE_SETTINGS "anticheat_settings" // Name of the table in the database with anti-cheat settings
#define AC_TABLE_FIELD_CODE "ac_code" // Name of the field with the anti-cheat code in the table
#define AC_TABLE_FIELD_TRIGGER "ac_code_trigger_type" // Name of the field with the value of the anti-cheat code trigger in the table

/*
    General anti-cheat settings
*/
#define AC_MAX_CODES 54 // The number of anti-cheat codes (currently there are 53)
#define AC_MAX_CODE_LENGTH (3 + 1) // Maximum Characters in the anti-cheat "code" (001/002/003, etc.)
#define AC_MAX_CODE_NAME_LENGTH (33 + 1) // Maximum Characters in the full name of the cheat, for which any code is responsible
    
#define AC_MAX_TRIGGER_TYPES 3 // The number of anti-cheat trigger (punishment) types. As you add types of triggers (punishments), increase this value.
#define AC_MAX_TRIGGER_TYPE_NAME_LENGTH (8 + 1) // Maximum Characters in the name of the anti-cheat trigger (punishment) type

#define AC_GLOBAL_TRIGGER_TYPE_PLAYER 0
#define AC_GLOBAL_TRIGGER_TYPE_IP 1

// Types of triggers are declared by macros to make it easier to navigate in OnCheatDetected.
#define AC_CODE_TRIGGER_TYPE_DISABLED 0 // AC_CODE_TRIGGER_TYPE_DISABLED - Punishment type: Disabled
#define AC_CODE_TRIGGER_TYPE_WARNING 1 // AC_CODE_TRIGGER_TYPE_WARNING - Punishment type: Warning
#define AC_CODE_TRIGGER_TYPE_KICK 2 // AC_CODE_TRIGGER_TYPE_KICK - Punishment type: Kick

#define AC_TRIGGER_ANTIFLOOD_TIME 20 // Time for anti-flood triggers (in seconds)

/*
    Settings of the visual part of the system (dialogs)
*/
#define AC_MAX_CODES_ON_PAGE 15 // Maximum number of items on the anti-cheat settings page
#define AC_DIALOG_NEXT_PAGE_TEXT ">>> Next page" // Text of the button that will display the next page of the list
#define AC_DIALOG_PREVIOUS_PAGE_TEXT "<<< Previous page" // Text of the button that will display the previous page of the list
