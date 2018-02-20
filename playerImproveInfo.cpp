#include "stdafx.h"
#include "playerImproveInfo.h"

namespace PLAYER_IMPROVE_INFO
{
	int maxExpValue[MAXLV] = {
		0, 32, 96, 208, 400,
		672, 1056, 1552, 2184, 2976,					//lv.10
		3936, 5080, 6432, 7992, 9784,
		11840, 14152, 16736, 19616, 22832,				//lv.20
		26360, 30232, 34456, 39056, 44072,
		49464, 55288, 61568, 68304, 75496,				//lv.30
		83184, 91384, 100088, 109344, 119136,
		129504, 140464, 152008, 164184, 176976,			//lv.40
		190416, 204520, 219320, 234808, 251000,
		267936, 285600, 304040, 323248, 343248,			// lv.50
		364064, 385696, 408160, 431488, 455680,
		480776, 506760, 533680, 561528, 590320,			//lv.60
		620096, 650840, 682600, 715368, 749160,
		784016, 819920, 856920, 895016, 934208,			//lv.70
		974536, 1016000, 1058640, 1102456, 1147456,
		1193648, 1241080, 1289744, 1339672, 1390872,	//lv.80
		1443368, 1497160, 1552264, 1608712, 1666512,	//lv.85
		1725688, 1786240, 1848184, 1911552, 1976352,	//lv.90
		2042608, 2110320, 2179504, 2250192, 2322392,	//lv.95
		2396128, 2471400, 2548224, 2637112				//lv.99
	};

	int improveHPValue[MAXLV] = {
		0, 11, 12, 14, 17,
		20, 22, 24, 26, 27,				//lv.10
		28, 30, 35, 39, 44,
		50, 54, 57, 61, 65,				//lv.20
		67, 69, 72, 76, 79,
		82, 86, 90, 95, 99,				//lv.30
		100, 101, 102, 102, 103,
		104, 106, 107, 108, 110,			//lv.40
		111, 113, 114, 116, 117,
		119, 120, 122, 125, 128,			//lv.50
		130, 131, 133, 134, 136,
		137, 139, 142, 144, 145,			//lv.60
		147, 148, 150, 152, 153,
		155, 156, 158, 160, 162,			//lv.70
		160, 155, 151, 145, 140,
		136, 132, 126, 120, 117,			//lv.80
		113, 110, 108, 105, 102,
		100, 98, 95, 92, 90,			//lv.90
		88, 87, 85, 83, 82,
		80, 83, 86, 88					//lv.99
	};

	int improveMPValue[MAXLV] = {
		0, 5, 6, 7, 8,
		9, 10, 11, 12, 13,				//lv.10
		14, 15, 16, 17, 17,
		17, 17, 16, 16, 16,				//lv.20
		15, 15, 15, 14, 14,
		14, 14, 13, 13, 13,				//lv.30
		13, 12, 12, 12, 12,
		11, 11, 11, 11, 11,				//lv.40
		11, 10, 10, 10, 10,
		10, 10, 10, 10, 9,				//lv.50
		9, 9, 9, 9, 9,
		9, 9, 9, 9, 10,					//lv.60
		8, 8, 8, 8, 8,
		8, 8, 8, 8, 8,						//lv.70
		10, 10, 7, 6, 5,
		4, 5, 6, 7, 8,						//lv.80
		9, 8, 7, 6, 5,
		6, 7, 5, 6, 7,						//lv.90
		8, 9, 10, 8, 8,
		9, 10, 11, 13						//lv.99
	};
}