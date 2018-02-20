#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>


class townMap : public gameNode
{
public:
	POINT _townMap;					//Ÿ��� x,y
	tile* _townTiles;				//Ÿ��� Ÿ��

	townMap();
	~townMap();
	
	HRESULT init();
	void release();
	void update();
	void render();

	//�� �ε�� �Լ�
	void mapLoad(void);


	//===============�ټ� ����==================

	//��ũ�� x,y�� �Լ�
	POINT getTownMapPOINT() { return _townMap; }

	//�ε�� ����� Ÿ�� ���Լ� 
	tile* getTownMapTiles() { return _townTiles; }

};

