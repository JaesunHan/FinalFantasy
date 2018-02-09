#pragma once

/********************************************************/
/* 타일 정보 정의											*/
/* 작업자 : 이호형										*/
/* 최종 수정 : 2018. 02. 08								*/
/********************************************************/

#define TILE_SIZEX		32
#define TILE_SIZEY		32


// 지형 속성
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
