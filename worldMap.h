#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>



class worldMap :public gameNode
{
public: 

	POINT _worldMap;					//����� x,y
	tile* _worldMapTiles;				//����� Ÿ��

	worldMap();
	~worldMap();

	HRESULT init();
	void release();
	void update();
	void render();

	//�� �ε�� �Լ�
	void mapLoad(void);
};

