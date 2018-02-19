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
	//NPC�� �����ϱ� ���ؼ� ���͸� npc����Ŭ���������ͷ� �����.
	typedef vector<npcMother*> vNpcMother;
	typedef vector<npcMother*>::iterator viNpcMother;



private:
	vNpcMother _vNpc;
	
	//��Ʈ������ ���� �ΰ�
	vNpcMother _vTopNpc;
	vNpcMother _vBottomNpc;
	
	viNpcMother _viNpc;


	//�÷��̾� ��ǥ�� �ޱ� ���� ����Ʈ ����
	POINT _playerPos;


public:
	npcManager();
	~npcManager();

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc, POINT movePt);
	
	//zorder�� ���� ���� �ΰ� �߰� 
	void beforeRender(HDC hdc, POINT movePt);
	void afterRender(HDC hdc, POINT movePt);

	void setPlayerPos(POINT pt) { _playerPos = pt; }

	//========���Լ�======= 
	vector <npcMother*> getVNpc() { return _vNpc; }
	vector <npcMother*>::iterator getViNpc() { return _viNpc; }


};

