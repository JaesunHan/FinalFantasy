#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>


//======    월드맵	 =======//
//		제작자 : 한재환		//
//		2월 12일				//
//==========================//


class worldMap :public gameNode
{
public: 

	POINT _worldMap;					//월드맵 x,y
	tile* _worldMapTiles;				//월드맵 타일

	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	//맵 로드용 함수
	void mapLoad(void);


	//===============겟셋 모음==================

	//맵크기 x,y겟 함수
	POINT getWorldMapPOINT() { return _worldMap; }

	//로드된 월드맵 타일 겟함수 
	tile* getWorldMapTiles() { return _worldMapTiles; }




};

