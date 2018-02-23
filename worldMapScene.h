#pragma once
#include "gameNode.h"
#include "generalMap.h"
#include "worldMap.h"
#include "worldMapPlayer.h"
#include "npcManager.h"
#include "worldMapEnemyManager.h"




//======����� ��	 =======//
//		������ : ����ȯ		//
//		2�� 12��				//
//==========================//

//�κ��丮 �������� ���� ���漱�� ����ʿ��� �κ��丮�� �ǵ帳�ϴ� ŗŗ!
class itemManager;
class optionMenu;

class worldMapScene : public gameNode
{
private:
	//�浹�� �༮ �ε��� ������
	int _enemyNum;



	//�浹�ߴ��� ����
	bool _isCollision;
	bool _isEncounter;
	bool _isNotEnemyVector;
	bool _isGetGongChi;

	//��������
	bool _isEscape;

	generalMap* _worldMap;
	worldMapPlayer* _worldMapPlayer;

	//NPC�����
	npcManager* _npcManager;

	//���ʹ� �����
	worldMapEnemyManager* _wMEM;

	//�κ��丮��
	itemManager* _im;

	//�޴�Ŭ���� 
	optionMenu* _optionMenu;

	POINT _curPlayerPos;
	POINT _curCameraPos;

	image* _openBox;
	image* _messageBox;
	bool _isOpenBox;
	bool _isMessageBox;

	POINT tempPoint;
public:
	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();

	//�ݸ����� ������ �� ��Ʋ������ ü����
	void getCollision();

	void successEscape();


	//Ÿ������ ����.
	void enterTownMap();



	//��Ʋ������ ����� ���� �Ұ� ���ͼ���
	bool getIsEscape() { return _isEscape; }
	void setIsEscape(bool isEscape) { _isEscape = isEscape; }

	void setPlayerPos(void);
	void resetIsEncounter(void) { _isEncounter = false; SOUNDMANAGER->stop(CH_ENCOUNTER); }

	void getGongChi();

	void battleEncount();

	void savePoint();

	//�ټ��߰�!!!!
	void setItemManagerAddressLink(itemManager* im) { _im = im; }
	void setMenuMemoryAddressLink(optionMenu* optionMenu) { _optionMenu = optionMenu; }
	
	//����� �÷��̾� ���� �����´�.
	worldMapPlayer* getworldMapPlayer() { return _worldMapPlayer; }

};
