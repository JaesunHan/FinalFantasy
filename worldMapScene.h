#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "worldMapPlayer.h"
#include "npc1.h"
#include "npc2.h"
#include "npc3.h"
#include "npc4.h"
#include "npc5.h"

//======����� ��	 =======//
//		������ : ����ȯ		//
//		2�� 12��				//
//==========================//



class worldMapScene : public gameNode
{
public:

	worldMap* _worldMap;
	worldMapPlayer* _worldMapPlayer;
	
	//NPC�����
	npc1* _npc1;
	npc2* _npc2;
	npc3* _npc3;
	npc4* _npc4;
	npc5* _npc5;

	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

