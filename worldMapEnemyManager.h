#pragma once
#include "gameNode.h"
#include "worldEnemyBear.h"
#include "worldMapEnemySamurai.h"
#include <vector>

//============월드에너미 매니저===============//
// 터지지 마라 제발 -by 재환
//==========================================//
#define WORLDMAPENEMY 2

class worldMapEnemyManager : public gameNode
{
private:

	//월드에너미에 접근하기 위함
	typedef vector<worldMapEnemy*> vWME;
	typedef vector<worldMapEnemy*>::iterator viWME;

	vWME _vWME;
	viWME _viWME;

	//zorder용 벡터 두개 선언
	vWME _vTopWME;
	vWME _vBottomWME;

	//플레이어 포인트 변수 받자.
	POINT _playerPos;

public:

	

	worldMapEnemyManager();
	~worldMapEnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

//zorder를 위한 렌더 두개 추가 
	void beforeRender();
	void afterRender();

	void setPlayerPos(POINT pt) { _playerPos = pt; }

	//========겟함수======= 
	vector <worldMapEnemy*> getVNpc() { return _vWME; }
	vector <worldMapEnemy*>::iterator getViNpc() { return _viWME; }


};

