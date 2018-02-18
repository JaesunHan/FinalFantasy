#pragma once
#include "gameNode.h"
#include "worldEnemyBear.h"
#include "worldMapEnemySamurai.h"
#include "worldMapEnemyVectorPup.h"
#include <vector>

//============월드에너미 매니저===============//
// 터지지 마라 제발 -by 재환
//==========================================//
//충돌전에는 그냥 일반 무브 패트롤 
//충돌은 겟디스턴스로 타일 한칸정도 길이에 충돌하면 배틀씬으로 넘어가게
//에너미는 플레이어 추적할때 일정거리(디스턴스)를 넘어가면 그냥 다시 일반 패트롤로 가게 

#define WORLDMAPENEMY 3

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

	//에너미 삭제
	void worldEmenyDelete(int arrNum);


	void setPlayerPos(POINT pt) { _playerPos = pt; }

	//========겟함수======= 
	vector <worldMapEnemy*> getVWME() { return _vWME; }
	vector <worldMapEnemy*>::iterator getViWME() { return _viWME; }


};


