#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>


//======    �����	 =======//
//		������ : ����ȯ		//
//		2�� 12��				//
//==========================//


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


	//===============�ټ� ����==================

	//��ũ�� x,y�� �Լ�
	POINT getWorldMapPOINT() { return _worldMap; }

	//�ε�� ����� Ÿ�� ���Լ� 
	tile* getWorldMapTiles() { return _worldMapTiles; }




};

