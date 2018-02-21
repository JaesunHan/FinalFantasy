#pragma once
#include "gameNode.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "generalMap.h"
#include "townMap.h"


class townScene : public gameNode
{
public:

	//����� �÷��̾� �����
	worldMapPlayer* _worldMapPlayer;

	//NPC�����
	npcManager* _npcManager;

	//Ÿ��ʿ�
	generalMap* _townMap;


	townScene();
	~townScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//��������� �Ѿ�� �Լ�
	void enterWorldMap();

};

