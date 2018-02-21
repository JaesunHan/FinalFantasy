#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	_pm = new playerManager;
	_pm->init();
	_item = new itemManager;
	_item->init();
	_bts = new BattleScene;
	_bts->setPlayerManagerMemoryAddressLink(_pm);
	_bts->setItemManagerMemoryAddressLink(_item);
	_pm->setItemManagerAddressLink(_item);


	SCENEMANAGER->addScene("mapToolScene", new mapTool);
	SCENEMANAGER->addScene("��Ʋ��", _bts);
	SCENEMANAGER->addScene("����ʾ�", new worldMapScene);
	SCENEMANAGER->addScene("Ÿ��ʾ�", new townScene);
	SCENEMANAGER->addScene("storeScene", new storeScene);
	SCENEMANAGER->addScene("���ӿ���", new gameOverScene);
	
	((storeScene*)(SCENEMANAGER->findScene("storeScene")))->setItemManagerAddressLink(_item);

	//SCENEMANAGER->changeScene("mapToolScene");
	
	((mapTool*)SCENEMANAGER->findScene("mapToolScene"))->createDefaultMap(PointMake(20, 20));

	//=========================== �޴��� =========================== by won
	SCENEMANAGER->addScene("�ε�", new loadingScene);
	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
	_saveMenu = (saveLoadMenu*)SCENEMANAGER->addScene("���̺�ε�", new saveLoadMenu);
	_saveMenu->setItemManagerAddressLink(_item);
	SCENEMANAGER->addScene("�ɼ�", new optionMenu);
	_nGame = (newGame*)SCENEMANAGER->addScene("������", new newGame);
	_nGame->setItemManagerAddressLink(_item);
	_loadGame = (loadGame*)SCENEMANAGER->addScene("�ε����", new loadGame);
	_loadGame->setItemManagerAddressLink(_item);
	SCENEMANAGER->addScene("�ɷ�ġ", new abilitiesMenu);
	SCENEMANAGER->addScene("����", new configMenu);
	SCENEMANAGER->addScene("���", new equipMenu);
	SCENEMANAGER->addScene("������", new itemMenu);
	SCENEMANAGER->addScene("����", new statusMenu);
	SCENEMANAGER->addScene("ĳ���ʹɷ�", new characterAbility);
	SCENEMANAGER->addScene("ĳ���ͻ���", new characterStatus);
	//=========================== �޴��� ===========================



	
	SCENEMANAGER->changeScene("�ε�");

	return S_OK;
}

//�޸� ���� ����
void playGround::release(void)
{
	gameNode::release();

}

//����
void playGround::update(void)
{
	gameNode::update();

	//if (_isBattle)
	//{
	//	_pm->setPlayerInfoToBattlePlayer();
	//	_isBattle = false;
	//}

	//================================ �޴��� ================================ by won
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("�ε�");
	}
	//�ɼǸ޴�
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && SCENEMANAGER->getCurrentSceneName() == "����ʾ�")
	{
		SCENEMANAGER->changeSceneType0("�ɼ�");
	}
	//================================ �޴��� ================================

	//================================ ������ ================================
	if (KEYMANAGER->isOnceKeyDown('M'))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("mapToolScene");
	}
	//================================ ������ ================================

	//================================ ��Ʋ�� ================================
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeSceneType0("��Ʋ��");			//_isBattle = true;
	}
	//================================ ��Ʋ�� ================================

	//================================ ����� ================================
	if (KEYMANAGER->isOnceKeyDown(VK_F1)) _isDebug = !_isDebug;
	//================================ ����� ================================

	//==============================����ʾ�===================================
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SCENEMANAGER->changeScene("����ʾ�");
	}
	//========================================================================

	//=============================Ÿ���======================================
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		SCENEMANAGER->changeSceneType0("Ÿ��ʾ�");
	}
	//=========================================================================

	//=============================Ÿ���======================================
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		((storeScene*)SCENEMANAGER->findScene("storeScene"))->setStoreKey("weaponStore");
		SCENEMANAGER->changeSceneType0("storeScene");
	}
	//=========================================================================
	_pm->update();

	SCENEMANAGER->update();
}

//�׸��°�.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== �� ���� �մ��� ���ÿ� =========================

	SetBkMode(getMemDC(), TRANSPARENT);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc������ �׷��ش� 
}


