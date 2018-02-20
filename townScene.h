#pragma once
#include "gameNode.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "townMap.h"


class townScene : public gameNode
{
public:

	//����� �÷��̾� �����
	worldMapPlayer* _worldMapPlayer;

	//NPC�����
	npcManager* _npcManager;

	//Ÿ��ʿ�
	townMap * _townMap;


	townScene();
	~townScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

