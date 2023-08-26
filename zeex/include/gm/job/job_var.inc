enum JOBS_ENUM
{
	jobID,
	jobType,
	Float:jobX,
	Float:jobY,
	Float:jobZ,
	jobInt,
	jobVW,
	jobPickUp,
	jobOn
}
new JobsInfo[MAX_JOBS][JOBS_ENUM];

//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
#define MAX_JOBS_TYPES 5
new jobs_names[MAX_JOBS_TYPES][32] = {
	"Yok",
    "Lojistik Firmasý",
    "Mekanik",
    "Taksi Þoförü",
    "Pizzacý"
};