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
	_item->setPlayerManagerMemoryAddressLink(_pm);

	SCENEMANAGER->addScene("mapToolScene", new mapTool);
	SCENEMANAGER->addScene("��Ʋ��", _bts);
	SCENEMANAGER->addScene("����ʾ�", new worldMapScene);
	((worldMapScene*)SCENEMANAGER->findScene("����ʾ�"))->setItemManagerAddressLink(_item);
	SCENEMANAGER->addScene("Ÿ��ʾ�", new townScene);
	SCENEMANAGER->addScene("storeScene", new storeScene);
	SCENEMANAGER->addScene("���ӿ���", new gameOverScene);
	
	((storeScene*)(SCENEMANAGER->findScene("storeScene")))->setItemManagerAddressLink(_item);

	//SCENEMANAGER->changeScene("mapToolScene");
	
	((mapTool*)SCENEMANAGER->findScene("mapToolScene"))->createDefaultMap(PointMake(20, 20));

	//=========================== �޴��� =========================== by won
	SCENEMANAGER->addScene("�ε�", new loadingScene);
	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
    SCENEMANAGER->addScene("���̺�ε�", new saveLoadMenu);
	((saveLoadMenu*)SCENEMANAGER->findScene("���̺�ε�"))->setItemManagerAddressLink(_item);
	((saveLoadMenu*)SCENEMANAGER->findScene("���̺�ε�"))->setPlayerManagerAddressLink(_pm);
	SCENEMANAGER->addScene("�ɼ�", new optionMenu);
	SCENEMANAGER->addScene("������", new newGame);
	((newGame*)SCENEMANAGER->findScene("������"))->setItemManagerAddressLink(_item);
	((newGame*)SCENEMANAGER->findScene("������"))->setPlayerManagerAddressLink(_pm);
	SCENEMANAGER->addScene("�ε����", new loadGame);
	((loadGame*)SCENEMANAGER->findScene("�ε����"))->setItemManagerAddressLink(_item);
	((loadGame*)SCENEMANAGER->findScene("�ε����"))->setPlayerManagerAddressLink(_pm);
	SCENEMANAGER->addScene("�ɷ�ġ", new abilitiesMenu);
	SCENEMANAGER->addScene("����", new configMenu);
	SCENEMANAGER->addScene("���", new equipMenu);
	SCENEMANAGER->addScene("������", new itemMenu);
	((itemMenu*)SCENEMANAGER->findScene("������"))->setItemManagerAddressLink(_item);
	SCENEMANAGER->addScene("����", new statusMenu);
	SCENEMANAGER->addScene("ĳ���ʹɷ�", new characterAbility);
	((characterAbility*)SCENEMANAGER->findScene("ĳ���ʹɷ�"))->setItemManagerAddressLink(_item);
	SCENEMANAGER->addScene("ĳ���ͻ���", new characterStatus);
	((characterStatus*)SCENEMANAGER->findScene("ĳ���ͻ���"))->setItemManagerAddressLink(_item);
	_menu = new menu;
	_menu->setItemManagerAddressLink(_item);
	//=========================== �޴��� ===========================

	//======================������ ����� �߰�======================
	SCENEMANAGER->addScene("�����׹���", new oPeningMovie);

	
	SCENEMANAGER->changeScene("�����׹���");

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
		SCENEMANAGER->changeSceneType1("�ɼ�");
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
	if (SCENEMANAGER->getCurrentScene() == SCENEMANAGER->findScene("�����׹���"))return;
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== �� ���� �մ��� ���ÿ� =========================

	SetBkMode(getMemDC(), TRANSPARENT);
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	
	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc������ �׷��ش� 
}


