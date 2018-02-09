#pragma once

/********************************************************/
/* Ÿ�� ���� ����											*/
/* �۾��� : ��ȣ��										*/
/* ���� ���� : 2018. 02. 08								*/
/********************************************************/

#define TILE_SIZEX		32
#define TILE_SIZEY		32


// ���� �Ӽ�
enum TERRAIN
{
	TR_GRASS, TR_DESERT, TR_WATER,
	TR_NONE
};

enum OBJECT
{
	OBJ_MOUNTAIN, OBJ_TOWN, OBJ_NPC, OBJ_ENEMY,
	OBJ_NONE
};

enum ATTRIBUTE
{
	ATTR_UNMOVE, ATTR_SLOW,
	ATTR_MOVE
};
