#define IsPlayerUseMDC(%0) MdcInfo[%0][mdcCreated]


#define PAGE_NONE						-1
#define PAGE_MAIN						0

#define PAGE_LOOKUP     				1

#define PAGE_LOOKUP_PERSON				2
#define PAGE_LOOKUP_VEHICLE				3
#define PAGE_LOOKUP_VEHICLES_LIST   	4

#define PAGE_MENU                      	5
#define PAGE_INFO                      	6

#define PAGE_MAP                      	7
#define PAGE_LIC                      	8

#define PAGE_APB                      	9
#define PAGE_CALLS                      10

#define PAGE_CCTV                       11
#define PAGE_ROSTER                     12

#define PAGE_MEMBERS                    13
#define PAGE_MEMBERS_MAP               	14


enum MDC_ENUM
{
    mdcCreated,
    mdcPage,
    
    mdcBack,
    mdcMenu,

    mdcSearch,

    mdcList[18],
    mdcListPage
};
new MdcInfo[MAX_PLAYERS][MDC_ENUM];

new PlayerText:MDC_UI[MAX_PLAYERS][17];
new PlayerText:MDC_MAINSCREEN[MAX_PLAYERS][7];
new PlayerText:MDC_LOOKUP_SEARCH[MAX_PLAYERS][4];

new PlayerText:MDC_BACK[MAX_PLAYERS];

new PlayerText:MDC_LIST[MAX_PLAYERS][16];
new PlayerText:MDC_LIST_INFO[MAX_PLAYERS][3];

new PlayerText:MDC_ERROR_CALLS[MAX_PLAYERS];

new PlayerText:MDC_LOOKUP_ERROR[MAX_PLAYERS];
new PlayerText:MDC_LOOKUP_AVATAR[MAX_PLAYERS][2];
new PlayerText:MDC_LOOKUP_PERSON[MAX_PLAYERS][12];

new PlayerText:MDC_LOOKUP_VEHICLE[MAX_PLAYERS][8];
new PlayerText:MDC_LOOKUP_VEHICLES_LIST[MAX_PLAYERS][12];
new PlayerText:MDC_VEH_LIST_CLICK[MAX_PLAYERS][3];
new PlayerText:MDC_LOOKUP_VEHICLES_ARROWS[MAX_PLAYERS][3];

new PlayerText:MDC_ADDRESS[MAX_PLAYERS][5];
new PlayerText:MDC_OTHER_ADDRESS[MAX_PLAYERS][6];

new PlayerText:MDC_LIC[MAX_PLAYERS][32];

new PlayerText:MDC_APB_TD[MAX_PLAYERS][20];
new PlayerText:MDC_CALLS_TD[MAX_PLAYERS][20];

new PlayerText:MDC_TD_LEFT_PANEL[MAX_PLAYERS][3];

#define MAX_TD_MENU_SIZE (18)
new PlayerText:MDC_TD_MENU[MAX_PLAYERS][MAX_TD_MENU_SIZE];