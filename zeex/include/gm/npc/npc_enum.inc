enum ACTOR_DATA
{
    aID,
    aType,
    Float:aPosX,
    Float:aPosY,
    Float:aPosZ,
    Float:aPosR,
    aInterior,
    aWorld,
    aSkin,
    aSex,
    aName[32],
    aAnimation,
    aPosUsed,
    
    Text3D:aLabel,
    aON,
};
new E_ACTOR[MAX_SERVER_ACTORS][ACTOR_DATA];

enum ACTOR_MNAMES_DATA
{
    dID,
    dName[12]
}
new ACTOR_MNAMES[26][ACTOR_MNAMES_DATA] = 
{
    {0, "Bob"},
    {1, "Mark"},
    {2, "John"},
    {3, "Anthony"},
    {4, "William"},
    {5, "Dwayne"},
    {6, "Ray"},
    {7, "Vernon"},
    {8, "Harry"},
    {9, "Daniel"},
    {10, "Bruce"},
    {11, "Christopher"},
    {12, "Melvyn"},
    {13, "Kristian"},
    {14, "Howard"},
    {15, "Michael"},
    {16, "Steven"},
    {17, "Gregory"},
    {18, "Frank"},
    {19, "Cody"},
    {20, "Toby"},
    {21, "Tyler"},
    {22, "Jacob"},
    {23, "Homer"},
    {24, "Peter"},
    {25, "Pierce"}
};

enum ACTOR_FNAMES_DATA 
{
    dID,
    dName[12]

}  
new ACTOR_FNAMES[25][ACTOR_FNAMES_DATA] = 
{
    {0, "Sophia"},
    {1, "Lynette"},
    {2, "Suzan"},
    {3, "Sarah"},
    {4, "Carol"},
    {5, "Ruth"},
    {6, "Christal"},
    {7, "Ryth"},
    {8, "Lindsey"},
    {9, "Mary"},
    {10, "Betty"},
    {11, "Alexia"},
    {12, "Susan"},
    {13, "Nancy"},
    {14, "Candice"},
    {15, "Rachel"},
    {16, "Mary"},
    {17, "Linda"},
    {18, "Jennifer"},
    {19, "Shauna"},
    {20, "Grace"},
    {21, "Charleen"},
    {22, "Angel"},
    {23, "Britney"},
    {24, "Eleanore"}
};


enum ACTOR_SURNAMES_DATA
{
    dID,
    dSurname[12]
}
new ACTOR_SURNAMES[47][ACTOR_SURNAMES_DATA] = 
{
    {0, "Marley"},
    {1, "West"},
    {2, "Page"},
    {3, "Cage"},
    {4, "Smith"},
    {5, "Forester"},
    {6, "Baksley"},
    {7, "Ashton"},
    {8, "Tucker"},
    {9, "Wishp"},
    {10, "Nichols"},
    {11, "Walsh"},
    {12, "Shaw"},
    {13, "Gordon"},
    {14, "Nelson"},
    {15, "Baker"},
    {16, "Davidson"},
    {17, "Bryant"},
    {18, "Hart"},
    {19, "Todd"},
    {20, "York"},
    {21, "Crawford"},
    {22, "Willis"},
    {23, "Reeves"},
    {24, "Morgan"},
    {25, "Parks"},
    {26, "McLaughlin"},
    {27, "Hampton"},
    {28, "Farmer"},
    {29, "Bates"},
    {30, "Black"},
    {31, "Flinn"},
    {32, "Drake"},
    {33, "Houston"},
    {34, "Jacobs"},
    {35, "Weaver"},
    {36, "Walker"},
    {37, "Stafford"},
    {38, "Bond"},
    {39, "Stevens"},
    {40, "Phillips"},
    {41, "Garrett"},
    {42, "Cain"},
    {43, "Johnson"},
    {44, "Clarke"},
    {45, "Booth"},
    {46, "Benson"}
};