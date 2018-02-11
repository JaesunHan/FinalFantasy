#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init(3);

	//�޴� �̹���
	_loading->loadImage("�ɷ¸޴�", ".//prevProjectResource//SceneImage//abilitiesMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�ɼǸ޴�", ".//prevProjectResource//SceneImage//configMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���޴�", ".//prevProjectResource//SceneImage//equipMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����۸޴�", ".//prevProjectResource//SceneImage//itemMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���θ޴�", ".//prevProjectResource//SceneImage//mainMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���̺�ε�޴�", ".//prevProjectResource//SceneImage//saveLoadMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���¸޴�", ".//prevProjectResource//SceneImage//statusMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ��Ʋ�޴�", ".//prevProjectResource//SceneImage//tilteMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("������", ".//prevProjectResource//SceneImage//menu_newGame.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));


	//��ư �̹���
	_loading->loadImage("�ɼǹ�ư", ".//prevProjectResource//SceneImage//button.bmp", 0, 0, 273, 59, true, RGB(255, 0, 255));
	_loading->loadImage("�ɼǹ�ư��", ".//prevProjectResource//SceneImage//button1.bmp", 0, 0, 205, 44, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ���;󱼵޹��", ".//prevProjectResource//SceneImage//faceBackground.bmp", 0, 0, 108, 108, true, RGB(255, 0, 255));
	_loading->loadImage("���庼����", ".//prevProjectResource//SceneImage//soundVolume_high.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadImage("���庼����", ".//prevProjectResource//SceneImage//soundVolume_medium.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadImage("���庼����", ".//prevProjectResource//SceneImage//soundVolume_low.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadImage("���庼����", ".//prevProjectResource//SceneImage//soundVolume_off.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadFrameImage("����Ŀ��", ".//prevProjectResource//SceneImage//selectCursor.bmp",54, 27, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư����", ".//prevProjectResource//SceneImage//button_yes.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư��", ".//prevProjectResource//SceneImage//button_no.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));

	//�÷��̾� �̹���
	_loading->loadImage("TINA", ".//prevProjectResource//SceneImage//player_tina.bmp", 112, 111, true, RGB(255, 0, 255));
	_loading->loadImage("CELES", ".//prevProjectResource//SceneImage//player_celes.bmp", 112, 111, true, RGB(255, 0, 255));
	_loading->loadImage("LOCK", ".//prevProjectResource//SceneImage//player_lock.bmp", 112, 111, true, RGB(255, 0, 255));
	_loading->loadImage("SHADOW", ".//prevProjectResource//SceneImage//player_shadow.bmp", 112, 111, true, RGB(255, 0, 255));

	
	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone(10))
	{
		SCENEMANAGER->changeScene("Ÿ��Ʋ");
	}
}

void loadingScene::render()	
{
	_loading->render();
}
