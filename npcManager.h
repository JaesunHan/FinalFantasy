#pragma once
#include "gameNode.h"
#include "npc1.h"
#include "npc2.h"
#include "npc3.h"
#include "npc4.h"
#include "npc5.h"
#include "armourStore.h"
#include "potionStore.h"
#include "weaponStore.h"
#include <vector>

class npcManager : public gameNode
{
private :
	//NPC에 접근하기 위해서 벡터를 npc마더클래스포인터로 만든다.
	typedef vector<npcMother*> vNpcMother;
	typedef vector<npcMother*>::iterator viNpcMother;



private:
	vNpcMother _vNpc;
	
	//제트오더용 벡터 두개
	vNpcMother _vTopNpc;
	vNpcMother _vBottomNpc;
	
	viNpcMother _viNpc;


	//플레이어 좌표를 받기 위한 포인트 변수
	POINT _playerPos;


public:
	npcManager();
	~npcManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, POINT movePt);
	
	//zorder를 위한 렌더 두개 추가 
	void beforeRender(HDC hdc, POINT movePt);
	void afterRender(HDC hdc, POINT movePt);

	void setPlayerPos(POINT pt) { _playerPos = pt; }

	//========겟함수======= 
	vector <npcMother*> getVNpc() { return _vNpc; }
	vector <npcMother*>::iterator getViNpc() { return _viNpc; }


};

