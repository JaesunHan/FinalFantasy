#pragma once
#include "gameNode.h"
#include "tile.h"
#include <vector>
#include <string>
//tile클래스에 게터 세터 추가하는거 잊지 말자 

//=========A* 시작일===========//
//==	   2018.2.10	    ==//
//==       한재환           ==//
//===========================//

//타일 크기 정의
#define TILEWIDTH 32
#define TILEHEIGHT 32

//타일 깔리는 갯수 정의
#define TILENUMX (WINSIZEX / TILEWIDTH)
#define TILENUMY (WINSIZEY / TILEHEIGHT)

class aStar : public gameNode
{
private:
	//전체 담고
	vector<tile> _vTotalList;
	vector<tile>::iterator _viTotalList;

	//갈수 있는 타일을 담고 
	vector<tile> _vOpenList;
	vector<tile>::iterator _viOpenList;

	//가장 가까운 경로를 담고
	vector<tile> _vCloseList;
	vector<tile>::iterator _viCloseList;



	tile _startTile;			//시작타일
	tile _endTile;				//끝타일
	tile _currentTile;			//계속 갱신될 현재타일

	int _tileX;
	int _tileY;

	int _count;
	bool _start;

public:
	aStar();
	~aStar();

	//처음 시작할때 에너미 x,y좌표, 플레이어 x,y 좌표 받도록 세팅
	HRESULT init(tile* map, int numX, int numY, tile start, tile end);

	//갈수있는 길을 찾아 담아줄 함수
	vector<tile> addOpenList(tile currentTile);
	vector<tile> pathFinder(tile current);

	void release();


};
