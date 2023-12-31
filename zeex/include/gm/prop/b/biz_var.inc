new biz_prod_types[26] =
	{-1, 2, 23, 21, 3, -1, 0, 11, -1, 4, 4, 4, 12, 15, -1, 1, 1, 1, 1, 1, 22, -1, -1, -1, -1, -1};
	
new biz_prod_point[26] =
	{0, 5, 5, 10, 5, 0, 10, 3, 0, 3, 3, 3, 10, 20, 0, 5, 5, 5, 5, 5, 10, 0, 0, 0, 0, 0};

#define MAX_BIZ_TYPES 26
new biz_types[MAX_BIZ_TYPES][64] = {
    "Di�er",
    "Bar / Club",
    "Market",
    "Silah D�kkan�",
    "Giyim Ma�azas�",
    "Berber D�kkan�",
    "Benzinlik",
    "Tamirhane",
    "Banka",
    "Ara� Galerisi",
    "Gemi Sat�c�s�",
    "U�ak Sat�c�s�",
    "Modifiye D�kkan�",
    "Reklam Ajans�",
    "S�r�c� Kursu",
    "Pizza D�kkan�",
    "Tavuk D�kkan�",
    "Burger D�kkan�",
    "Donut D�kkan�",
    "Restorant",
    "Mimarl�k Ofisi",
    "Eczane",
    "Pawnshop",
    "Telefoncu",
    // "Warehouse",
    //"Laundry",
    "S�permarket",
    "Aksesuar D�kkan�"
};

new trucker_teslimat[MAX_BIZ_TYPES][64] = {
    "Di�er",
    "��ki Kolisi",
    "Market E�yalar�",
    "Silah D�kkan�",
    "Tekstil Par�alar�",
    "Yeni Tra� Makinesi",
    "Motor Ya�� LibOil",
    "Tamir Ara�/Gere�leri",
    "POS Ka��d�",
    "Kalem / Ka��t",
    "Gemi Sat�c�s�",
    "U�ak Sat�c�s�",
    "Tamirat Par�alar�",
    "Kalem / Ka��t",
    "Kalem / Ka��t",
    "Pizza Kutusu",
    "Donmu� Tavuk Par�ac�klar�",
    "Burger Ekmekleri",
    "Lezzetli �ikolatal� Sos",
    "S�v� Ya� Kolisi",
    "Kalem / Ka��t",
    "�la� Kutusu",
    "Ara� Gere�",
    "Yeni Telefon",
    // "Warehouse",
    //"Laundry",
    "S�permarket E�yalar�",
    "Yeni Sezon Saat"
};

#define LIMIT_MAX_PRODUCTS (12)
new const max_product[] =
	{4, 4, 4, 3, 12, 8, 12, 1};

new const name_order[][][32] =
{
    /*
    {1579, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"������������ �������",		0,1,1, 108},
    {1579, ITEM_TYPE_REACT, 				ITEM_SIZE_MEDIUM, 	"�������",        	   		0,1,1, 112},
    */
    {"Buster", "Double D-Luxe", "Full Rack", "Salad Meal", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�"},
    {"Clukin' Little Meal", "Clukin' Big Meal", "Clukin' Huge Meal", "Salata", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�"},
    {"�ocuk Men�s�", "Et Kulesi", "Et D�nyas�", "Etli Salata", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�"},
    {"K���k porsiyon", "Orta porsiyon", "B�y�k porsiyon", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�"},
    {"SIM kart�", "Telsiz", "Maske", "�akmak", "Sigara", "Zar", "Benzin Bidonu", "Kalem", "Oyun kart�", "Kamera", "Boombox", "�i�ek"},
    {"Bira", "Votka", "Kola", "Su", "Viski", "Brandy", "Soda", "�arap", "Bo�", "Bo�", "Bo�", "Bo�"},
    {"Medikal marijuana", "�lk yard�m kiti", "K�rm�z� fosfor", "Vinilbenzil alkol", "Metilamin", "Heliotropin", "Efedrin", "Potasyum permanganat", "Kloroform", "Eter", "Hidrojen klor�r", "Metanol"},
    {"Burner Telefon", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�", "Bo�"}
};

new const model_order[8][12] =
{
    {2218, 2219, 2220, 2355, 0, 0, 0, 0, 0, 0, 0, 0},
    {2215, 2216, 2217, 2353, 0, 0, 0, 0, 0, 0, 0, 0},
    {2213, 2214, 2212, 2354, 0, 0, 0, 0, 0, 0, 0, 0},
    {2221, 2223, 2222, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {19792, 19942, 19801, 19998, 19897, 1906, 1650, 338, 11748, 367, 2226, 325}, // -sim -���� -INV_CARSOUND -
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