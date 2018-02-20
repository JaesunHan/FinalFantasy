#pragma once
#include "gameNode.h"
#include "tile.h"

enum MAPTYPE
{
	MAP_WORLD,
	MAP_TOWN,
	MAP_END
};

class generalMap : public gameNode
{
protected:
	POINT _mapTileNum;					//����� x,y
	tile* _mapTile;				//����� Ÿ��

public:

	//��Ÿ�� ������ ���� �̳ѹ�
	MAPTYPE _mapType;

	generalMap();
	~generalMap();

	HRESULT init(string mapFilePath);
	void release();
	void update();
	void render(HDC hdc);
	void afterRenderObject(HDC hdc);

	//�� �ε�� �Լ�
	void mapLoad(string mapFilePath);

	//===============�ټ� ����==================

	//��ũ�� x,y�� �Լ�
	POINT getMapTileNum() { return _mapTileNum; }

	//�ε�� ����� Ÿ�� ���Լ� 
	tile* getMapTile() { return _mapTile; }
};

