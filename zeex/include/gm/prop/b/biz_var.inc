new biz_prod_types[26] =
	{-1, 2, 23, 21, 3, -1, 0, 11, -1, 4, 4, 4, 12, 15, -1, 1, 1, 1, 1, 1, 22, -1, -1, -1, -1, -1};
	
new biz_prod_point[26] =
	{0, 5, 5, 10, 5, 0, 10, 3, 0, 3, 3, 3, 10, 20, 0, 5, 5, 5, 5, 5, 10, 0, 0, 0, 0, 0};

#define MAX_BIZ_TYPES 26
new biz_types[MAX_BIZ_TYPES][64] = {
    "Diðer",
    "Bar / Club",
    "Market",
    "Silah Dükkaný",
    "Giyim Maðazasý",
    "Berber Dükkaný",
    "Benzinlik",
    "Tamirhane",
    "Banka",
    "Araç Galerisi",
    "Gemi Satýcýsý",
    "Uçak Satýcýsý",
    "Modifiye Dükkaný",
    "Reklam Ajansý",
    "Sürücü Kursu",
    "Pizza Dükkaný",
    "Tavuk Dükkaný",
    "Burger Dükkaný",
    "Donut Dükkaný",
    "Restorant",
    "Mimarlýk Ofisi",
    "Eczane",
    "Pawnshop",
    "Telefoncu",
    // "Warehouse",
    //"Laundry",
    "Süpermarket",
    "Aksesuar Dükkaný"
};

new trucker_teslimat[MAX_BIZ_TYPES][64] = {
    "Diðer",
    "Ýçki Kolisi",
    "Market Eþyalarý",
    "Silah Dükkaný",
    "Tekstil Parçalarý",
    "Yeni Traþ Makinesi",
    "Motor Yaðý LibOil",
    "Tamir Araç/Gereçleri",
    "POS Kaðýdý",
    "Kalem / Kaðýt",
    "Gemi Satýcýsý",
    "Uçak Satýcýsý",
    "Tamirat Parçalarý",
    "Kalem / Kaðýt",
    "Kalem / Kaðýt",
    "Pizza Kutusu",
    "Donmuþ Tavuk Parçacýklarý",
    "Burger Ekmekleri",
    "Lezzetli Çikolatalý Sos",
    "Sývý Yað Kolisi",
    "Kalem / Kaðýt",
    "Ýlaç Kutusu",
    "Araç Gereç",
    "Yeni Telefon",
    // "Warehouse",
    //"Laundry",
    "Süpermarket Eþyalarý",
    "Yeni Sezon Saat"
};

#define LIMIT_MAX_PRODUCTS (12)
new const max_product[] =
	{4, 4, 4, 3, 12, 8, 12, 1};

new const name_order[][][32] =
{
    /*
    {1579, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½",		0,1,1, 108},
    {1579, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½",        	   		0,1,1, 112},
    */
    {"Buster", "Double D-Luxe", "Full Rack", "Salad Meal", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ"},
    {"Clukin' Little Meal", "Clukin' Big Meal", "Clukin' Huge Meal", "Salata", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ"},
    {"Çocuk Menüsü", "Et Kulesi", "Et Dünyasý", "Etli Salata", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ"},
    {"Küçük porsiyon", "Orta porsiyon", "Büyük porsiyon", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ"},
    {"SIM kartý", "Telsiz", "Maske", "Çakmak", "Sigara", "Zar", "Benzin Bidonu", "Kalem", "Oyun kartý", "Kamera", "Boombox", "Çiçek"},
    {"Bira", "Votka", "Kola", "Su", "Viski", "Brandy", "Soda", "Þarap", "Boþ", "Boþ", "Boþ", "Boþ"},
    {"Medikal marijuana", "Ýlk yardým kiti", "Kýrmýzý fosfor", "Vinilbenzil alkol", "Metilamin", "Heliotropin", "Efedrin", "Potasyum permanganat", "Kloroform", "Eter", "Hidrojen klorür", "Metanol"},
    {"Burner Telefon", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ", "Boþ"}
};

new const model_order[8][12] =
{
    {2218, 2219, 2220, 2355, 0, 0, 0, 0, 0, 0, 0, 0},
    {2215, 2216, 2217, 2353, 0, 0, 0, 0, 0, 0, 0, 0},
    {2213, 2214, 2212, 2354, 0, 0, 0, 0, 0, 0, 0, 0},
    {2221, 2223, 2222, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {19792, 19942, 19801, 19998, 19897, 1906, 1650, 338, 11748, 367, 2226, 325}, // -sim -ï¿½ï¿½ï¿½ï¿½ -INV_CARSOUND -
    {2958, 1668, 1546, 1455, 1520, 19820, 19346, 1664, 0, 0, 0, 0},
    {1578, 11736, 2709, 2709, 2709, 2709, 2709, 2709, 2709, 2709, 2709, 2709},
    {18866, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

new const biz_prices[8][12] =
{
    {100, 100, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0},
    {100, 100, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0},
    {100, 100, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0},
    {100, 100, 200, 300, 0, 0, 0, 0, 0, 0, 0, 0},
    {300, 500, 1500, 50, 100, 100, 1000, 50, 100, 1500, 1000, 150},
    {100, 200, 100, 50, 300, 500, 100, 300, 0, 0, 0, 0},
    {1000, 1500, 1000, 1000, 1500, 1000, 1500, 1000, 1000, 1000, 2000, 1500},
    {700, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};