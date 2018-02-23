#pragma once
#include "gameNode.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "generalMap.h"
#include "townMap.h"
#include "storeScene.h"


class townScene : public gameNode
{
public:

	//����� �÷��̾� �����
	worldMapPlayer* _worldMapPlayer;

	//NPC�����
	npcManager* _npcManager;

	//Ÿ��ʿ�
	generalMap* _townMap;
	
	//��������
	storeScene* _store;


	townScene();
	~townScene();

	HRESULT init();
	void release();
	void update();
	void render();

	//��������� �Ѿ�� �Լ�
	void enterWorldMap();

	//�������� �Ѿ�� �Լ�
	void entershop();


	//����� �÷��̾� ���� �����´�.
	worldMapPlayer* getWorldMapPlayer() { return _worldMapPlayer; }

};

