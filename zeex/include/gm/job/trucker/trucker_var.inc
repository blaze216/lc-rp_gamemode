new truckcargo_product[MAX_TRUCK_PRODUCT][32] = {
	"Yakýt",
	"Yiyecek",
	"Ýçecekler",
	"Giyim",
	"Nakliye",
	"Mobilya",
	"Et",
	"Yumurta",
	"Süt",
	"Mýsýr",
	"Pamuk",
	"Boya",
	"Yedek Parça",
	"Malt",
	"Para",
	"Kaðýt",
	"Kýrýlmýþ Taþ",
	"Odun",
	"Pudra",
	"Metal",
	"Demir",
	"Silah Parçalarý",
	"Tuðla",
	"Teknik",
	"Meyve"
};
	
new truckcargo_type[3][32] = {"hammadde", "üretim", "satýn alým"};

new Float: dft_attach[4] = {-0.04656, -4.26884, 0.81490, 3.54000};

new Float: dft_attach_brick[3][3] =
{
    {0.04380, 1.17068, 0.46367},
	{0.04380, -1.35450, 0.46370},
	{0.04380, -3.79490, 0.4637}
};

new Float: paker_attach[2][4] =
{
	{0.00000, 0.40200, 1.85540, 15.18000},
	{-0.00730, -6.36940, 0.00000, 15.18000}
};

new Float: picador_attach[2][3] =
{
	{0.13280, -1.10310, -0.17710},
	{0.01329, -1.86198, -0.17710}
};

new Float: sadler_attach[2][3] =
{
	{0.13280, -1.10310, -0.21710},
	{0.01330, -1.86200, -0.21710}
};

new Float: bobcat_attach[3][3] =
{
	{-0.31250, -0.80650, -0.31710},
	{0.42700, -0.80650, -0.31710},
	{0.04260, -1.84000, -0.31710}
};

new Float: walton_attach[4][3] =
{
	{-0.44386, -1.00283, -0.07710},
	{0.51337, -1.10535, -0.07710},
	{0.46038, -1.85669, -0.07710},
	{-0.36452, -1.87622, -0.07710}
};

new Float: yosemite_attach[6][3] =
{
	{-0.31250, -1.00700, -0.23710},
	{0.42700, -1.00650, -0.23710},
	{0.06740, -1.70740, -0.23710},
	{0.06560, -2.40020, -0.23710},
	{0.06553, -0.99522, 0.46057},
	{0.07971, -1.69164, 0.46057}
};

new Float: yosemite_attach_brick[3] = {0.00995, -1.59382, 0.26984};
new obj_ship[11], obj_gate[4], obj_lamp[8], ship_arrived, ship_depart, ship_next, ship_docked, time_truck;
