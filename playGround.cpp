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
	_pm->setItemManagerAddressLink(_item);

	SCENEMANAGER->addScene("mapToolScene", new mapTool);
	SCENEMANAGER->addScene("��Ʋ��", _bts);
	SCENEMANAGER->addScene("����ʾ�", new worldMapScene);
	SCENEMANAGER->addScene("Ÿ��ʾ�", new townScene);
	SCENEMANAGER->addScene("���ӿ���", new gameOverScene);
	
	//SCENEMANAGER->changeScene("mapToolScene");
	
	((mapTool*)SCENEMANAGER->findScene("mapToolScene"))->createDefaultMap(PointMake(20, 20));

	//=========================== �޴��� =========================== by won
	SCENEMANAGER->addScene("�ε�", new loadingScene);
	SCENEMANAGER->addScene("Ÿ��Ʋ", new titleScene);
	SCENEMANAGER->addScene("���̺�ε�", new saveLoadMenu);
	SCENEMANAGER->addScene("�ɼ�", new optionMenu);
	SCENEMANAGER->addScene("������", new newGame);
	SCENEMANAGER->addScene("�ε����", new loadGame);
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
		SCENEMANAGER->changeScene("�ɼ�");
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
		SCENEMANAGER->changeScene("Ÿ��ʾ�");
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


