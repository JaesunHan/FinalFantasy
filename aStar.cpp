#include "stdafx.h"
#include "aStar.h"


aStar::aStar()
{
}


aStar::~aStar()
{
}

HRESULT aStar::init(int enemyPosX, int enemyPosY, int playerPosX, int playerPosY)
{
	////셋타일로부터 좌표를 받아온다.
	//setTiles(enemyPosX, enemyPosY, playerPosX, playerPosY);


	return S_OK;
}

void aStar::setTiles(int enemyPosX, int enemyPosY, int playerPosX, int playerPosY)
{
	//각 벡터 초기화
	//에너미 마다 a*를 불러오게 될텐데 기존에 담긴것들은 초기화 해주어야 할거 같다.
	//..아마도
	_vTotalList.clear();
	_vOpenList.clear();
	_vCloseList.clear();

	//에너미 입장에서 쫒아오는것이니 스타트 타일의 좌표는 에너미로부터 받아오는것. 


	_startTile = new tile;
	_startTile->init(PointMake(enemyPosX / TILEWIDTH, enemyPosY / TILEHEIGHT)); //좌표를 받아서 X타일 크기로 나눠주면 현재 타일의 위치가 나옴
	_startTile->setAttribute("start");


	_endTile = new tile;
	_endTile->init(PointMake(playerPosX / TILEWIDTH, playerPosY / TILEHEIGHT)); //플레이어 좌표 받아서 Y타일 크기로 나눠주어 현재 타일의 위치를 받아온다.
	_endTile->setAttribute("end");


	_currentTile = _startTile;

	for (int i = 0; i < TILENUMY; ++i)
	{
		for (int j = 0; j < TILENUMX; ++j)
		{	//ij를 돌아서 나온 타일의 인덱스가 스타트타일일때
			if (j == _startTile->getIndex().x && i == _startTile->getIndex().y)
			{
				_vTotalList.push_back(_startTile);
			}
			continue;
			//포문 돌려서 나온 타일의 인덱스가 엔드타일일때
			if (j == _endTile->getIndex().x && i == _endTile->getIndex().y)
			{
				_vTotalList.push_back(_endTile);
			}
			continue;

			//그외 타일들은 node라 하자.
			tile* _node = new tile;
			_node->init(PointMake(j, i));
			_vTotalList.push_back(_node);

		}
	}
}

vector<tile*> aStar::addOpenList(tile * currentTile)
{
	int startX = currentTile->getIndex().x - 1;
	int startY = currentTile->getIndex().y - 1;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			//1차원 배열에서의 특정 타일 인덱스를 구하는 공식
			tile* _node = _vTotalList[(startY * TILENUMX) + startX + j + (i * TILENUMX)];

			if (!_node->getIsOpen()) continue;
			//if(_node->getAttribute() == "벽이라니 벽!!") attribute 값 추가되면 추가할것
			if (startX + j < 0) continue;  //X가 0보다 작으면 재껴라
			if (startY + i < 0) continue;  //y가 0 보다 작으면 재껴라
			if (startX + j >= TILENUMX) continue; //X가 타일 X라인의 갯수보다 커지거나 같아지면 재껴라
			if (startY + i >= TILENUMY) continue; //y가 타일 Y라인의 갯수보다 커지거나 같아지면 재껴라


												  //현재 타일을 계속 갱신해준다.
			_node->setParentNode(_currentTile);

			//주변 타일을 검출하면서 체킇ㅆ는지 유무를 알수 있게 임의의 불값선언
			bool addObj = true;


			for (_viOpenList = _vOpenList.begin(); _viOpenList != _vOpenList.end(); ++_viOpenList)
			{
				if (*_viOpenList == _node)
				{
					addObj = false;
					break;
				}
			}

			if (!addObj) continue;

			_vOpenList.push_back(_node);
		}

	}

	return _vOpenList;
}

void aStar::pathFinder(tile * currentTile)
{
	//비교하기 쉽게 임의의 경로비용을 설정해둔다
	float tempTotalCost = 5000;
	tile* tempTile = NULL;

	for (int i = 0; i < addOpenList(currentTile).size(); ++i)
	{
		_vOpenList[i]->setCostToGoal(
			abs(_endTile->getIndex().x - _vOpenList[i]->getIndex().x +
				abs(_endTile->getIndex().y - _vOpenList[i]->getIndex().y)) * 10);


		//현재타일이 담겨있는 녀석
		POINT center1 = _vOpenList[i]->getParentNode()->getCenterPt();
		POINT center2 = _vOpenList[i]->getCenterPt();

		_vOpenList[i]->setCostFromStart((getDistance(center1.x, center1.y, center2.x, center2.y) > TILEWIDTH) ? 14 : 10);

		_vOpenList[i]->setTotalCost(_vOpenList[i]->getCostToGoal() + _vOpenList[i]->getCostFromStart());


	}
}

void aStar::release()
{
}

void aStar::update()
{
}

void aStar::render()
{
}
