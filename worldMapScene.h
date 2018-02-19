#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "worldMapEnemyManager.h"

//======����� ��	 =======//
//		������ : ����ȯ		//
//		2�� 12��				//
//==========================//



class worldMapScene : public gameNode
{
public:
	//��������
	bool _isEscape;

	worldMap * _worldMap;
	worldMapPlayer* _worldMapPlayer;

	//NPC�����
	npcManager* _npcManager;

	//���ʹ� �����
	worldMapEnemyManager* _wMEM;

	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();

	//�ݸ����� ������ �� ��Ʋ������ ü����
	void getCollision();


	//��Ʋ������ ����� ���� �Ұ� ���ͼ���
	bool getIsEscape() { return _isEscape; }
	void setIsEscape(bool isEscape) { _isEscape = isEscape; }


};
