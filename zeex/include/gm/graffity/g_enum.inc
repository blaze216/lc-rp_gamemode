enum GRAFFITY_DATA
{
    gID,
    gText[MAX_GRAFFITY_TEXT],
    gColor,
    gBackColor,
    gFont[16],
    gFontSize,
    gBold,
    gCreator[32],
    gCreateDate[64],
    Float:gPosX,
    Float:gPosY,
    Float:gPosZ,
    Float:gRotX,
    Float:gRotY,
    Float:gRotZ,
    Float:gGotoX,
    Float:gGotoY,
    Float:gGotoZ,
    gInterior,
    gVW,
    gAccepted,
    gAcceptor[32],
    gAcceptDate[64],
    gON,
    gObject,
    gEditing
}
new E_GRAFFITY[MAX_GRAFFITIES][GRAFFITY_DATA];

enum GRAFFITY_COLOR_DATA
{
    color_id,
    color_name[16],
    color_data,
    color_dlg[16],
};
new GRAFFITY_COLOR[MAX_GRAFFITY_COLORS][GRAFFITY_COLOR_DATA] = //öâåòà
{
    {0, "Beyaz",    0xFFFFFFFF, "{FFFFFF}"},
    {1, "Kýrmýzý",      0xFFFF0000, "{FF0000}"},
    {2, "Sarý",   0xFFFFFF00, "{FFFF00}"},
    {3, "Yeþil",    0xFF33CC33, "{33CC33}"},
    {4, "Mavi",     0xFF33CCFF, "{33CCFF}"},
    {5, "Turuncu",   0xFFFFA500, "{FFA500}"},
    {6, "Mavi",     0xFF1394BF, "{1394BF}"}
};

enum GRAFFITY_BACK_DATA
{
    color_id,
    color_name[16],
    color_data,
    color_dlg[16],
};
new GRAFFITY_BACK[MAX_GRAFFITY_BACKS][GRAFFITY_BACK_DATA] = 
{
    {0, "Yok",       0,          "{CC0000}"},
    {1, "White",    0xFFFFFFFF, "{FFFFFF}"},
    {2, "Kýrmýzý",      0xFFFF0000, "{FF0000}"},
    {3, "Sarý",   0xFFFFFF00, "{FFFF00}"},
    {4, "Yeþil",    0xFF33CC33, "{33CC33}"},
    {5, "Mavi",     0xFF33CCFF, "{33CCFF}"},
    {6, "Turuncu",   0xFFFFA500, "{FFA500}"},
    {7, "Mavi",     0xFF1394BF, "{1394BF}"}
};

enum GRAFFITY_FONT_DATA
{
    font_id,
    font_name[16],
};
new GRAFFITY_FONT[MAX_GRAFFITY_FONTS][GRAFFITY_FONT_DATA] =
{
    {0, "Arial"},
    {1, "Calibri"},
    {2, "Courier New"},
    {3, "Georgia"},
    {4, "Impact"},
    {5, "Tahoma"},
    {6, "Times New Roman"},
    {7, "Verdana"},
    {8, "Segoe Print"},
    {9, "Segoe Script"},
    {10, "Segoe UI"}
};