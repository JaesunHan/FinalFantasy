#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>
//tileŬ������ ���� ���� �߰��ϴ°� ���� ���� 

//=========A* ������===========//
//==	   2018.2.10	    ==//
//==       ����ȯ           ==//
//===========================//

//Ÿ�� ũ�� ����
#define TILEWIDTH 32
#define TILEHEIGHT 32

//Ÿ�� �򸮴� ���� ����
#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class aStar : public gameNode
{
private:
	//��ü ���
	vector<tile> _vTotalList;
	vector<tile>::iterator _viTotalList;

	//���� �ִ� Ÿ���� ��� 
	vector<tile> _vOpenList;
	vector<tile>::iterator _viOpenList;

	//���� ����� ��θ� ���
	vector<tile> _vCloseList;
	vector<tile>::iterator _viCloseList;



	tile _startTile;			//����Ÿ��
	tile _endTile;				//��Ÿ��
	tile _currentTile;			//��� ���ŵ� ����Ÿ��

	int _tileX;
	int _tileY;

	int _count;
	bool _start;

public:
	aStar();
	~aStar();

	//ó�� �����Ҷ� ���ʹ� x,y��ǥ, �÷��̾� x,y ��ǥ �޵��� ����
	HRESULT init(tile* map, int numX, int numY, tile start, tile end);

	//�����ִ� ���� ã�� ����� �Լ�
	vector<tile> addOpenList(tile currentTile);
	vector<tile> pathFinder(tile current);

	void release();


};
