new attach_police_model[] = {19904, 18637, 19142, 19515, 18636, 19161, 19162, 19521, 19098, 19200, 19141, 19514, 11745, 11738, 19096, -1581, -1582, -1583};

new attach_police_name[][] =
{
	"Turuncu Yelek",
	"Polis Kalkaný",
	"Siyah Zýrh",
	"Gri Kurþun Geçirmez Yelek",
	"Þapka 1",
	"Þapka 2",
	"Þapka 3",
	"Þapka 4",
	"Þapka",
	"Motosiklet Kaský",
	"Siyah SWAT kaský",
	"Gri SWAT kaský",
	/*"Balaklava",
	"Ribon No. 1",
	"Ribon P-III",
	"Detective I Ribon",
	"SLO P-III + 1",
	"Sergeant I Ribon",
	"Sergeant II Ribon",
	"Detective II Ribon",
	"Detective III Ribon",
	"Detective's Token",
	"Policeman's Token",*/
	"Ekipman Çantasý",
	"BLS çanta",
	"Siyah Þapka",
	"SGT Ribon",
	"Lietunant Ribon",
	"Captain Ribon"
};

new bort_list[20] = {978, 979, 3091, 19972, 19970, 19971, 18728, 18725, 18690, 1425, 19944, 19995, 19834, 19836, 1238, 1228, 1459, 1423, 1237, 19425};

new bort_names[20][32] =
{
	"Uzun Parlak Çit",
	"Uzun Parlak Çit 2",
	"Çit 'Hat Kapalý'",
	"Çit 'Yol Kapalý'",
	"Çit 'Tek Yön - Sað'",
	"Çit 'Tek Yön - Sol'",
	"Sinyal Meþalesi",
	"Duman parçacýklarý",
	"Ateþ parçacýklarý",
	"Servis Yolu Bariyeri",
	"Bodybag",
	"Score",
	"Bant",
	"Kan Lekesi",
	"Koni",
	"Bariyer",
	"Bariyer 2",
	"Bariyer 3",
	"Bariyer 4",
	"Kasis"
};

new Float: prison_palomino[2][3] =
{
	{1010.0032,-803.0173,1999.5859},
	{1011.0032,-803.0173,1999.5859}
};

new Float: prison_sadoc[20][3] =
{
	{529.2821,-462.5329,919.3973},
	{533.9864,-462.7558,919.3973},
	{538.7690,-462.5498,919.3973},
	{543.5073,-462.6223,919.3973},
	{548.3173,-462.2971,919.3973},
	{553.0486,-462.5840,919.3973},
	{529.3326,-481.8497,919.4027},
	{534.1647,-482.1199,919.4027},
	{538.8668,-482.2083,919.4027},
	{543.5774,-482.1175,919.4027},
	{548.4084,-482.4462,919.4027},
	{553.0802,-482.2829,919.4027},
	{538.6510,-461.6799,915.6733},
	{543.4929,-462.0461,915.6733},
	{548.2507,-461.4220,915.6733},
	{552.9613,-461.2717,915.6733},
	{538.8630,-483.5457,915.6733},
	{543.5722,-483.2266,915.6733},
	{548.3820,-483.2058,915.6733},
	{553.1059,-482.8833,915.6733}
};

new Float: prison_isolate[10][3] =
{
	{-1765.3180,-497.4885,621.1163},
	{-1769.2893,-497.9387,621.1163},
	{-1773.2601,-497.4489,621.1163},
	{-1777.2761,-497.9054,621.1163},
	{-1781.2529,-497.7102,621.1163},
	{-1765.5096,-497.7450,624.7874},
	{-1769.3136,-497.8934,624.7874},
	{-1773.2543,-497.4081,624.7874},
	{-1777.1084,-497.5620,624.7874},
	{-1781.1655,-498.0222,624.7874}
};

new Text3D:PrisonLabel[MAX_PLAYERS];