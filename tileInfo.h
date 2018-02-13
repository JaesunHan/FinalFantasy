#pragma once

/********************************************************/
/* Ÿ�� ���� ����											*/
/* �۾��� : ��ȣ��										*/
/********************************************************/

#define TILE_SIZEX		32
#define TILE_SIZEY		32


// ���� �Ӽ�
enum TERRAIN
{
	TR_GRASS, TR_DESERT, TR_WATER, TR_ROAD, TR_DIRT, TR_STUMP,
	TR_NONE
};

enum OBJECT
{
	OBJ_MOUNTAIN, OBJ_CAVE, OBJ_TOWN, OBJ_CASTLE, OBJ_NPC, OBJ_ENEMY,
	OBJ_NONE
};

enum ATTRIBUTE
{
	ATTR_UNMOVE, ATTR_SLOW, ATTR_FAST,
	ATTR_MOVE
};
