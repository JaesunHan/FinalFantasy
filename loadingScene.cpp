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
	_loading->init();

	char image[256];
	char sound[256];

	//���⿡ �ε�ó���� �ϸ� �ȴ�
	//������ ������ �̹����� �� ���̹Ƿ�, Ű ���� �ٸ��� �ؼ�
	//������ �ε��� �ϴ� ������ ��!

	for (int i = 0; i < 50; i++)
	{
		ZeroMemory(image, sizeof(image));
		sprintf(image, "�������÷���0%d", i);
		_loading->loadImage(image, "�������÷���.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
		
	}
	for (int i = 0; i < 20; i++)
	{
		ZeroMemory(image, sizeof(image));
		sprintf(image, "�������÷���1%d", i);
		_loading->loadImage(image, "background2.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}
	for (int i = 0; i < 30; i++)
	{
		ZeroMemory(image, sizeof(image));
		sprintf(image, "�������÷���2%d", i);
		_loading->loadImage(image, "guilmon.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	}
	for (int i = 0; i < 10; ++i)
	{
		ZeroMemory(sound, sizeof(sound));
		sprintf(sound, "����0%d", i);
		_loading->loadSound(sound, "Hello, world!.mp3", true, false);
	}
	for (int i = 0; i < 10; ++i)
	{
		ZeroMemory(sound, sizeof(sound));
		sprintf(sound, "����1%d", i);
		_loading->loadSound(sound, "Haikyuu!!+I��M A BELIEVER.mp3", true, false);
	}
	for (int i = 0; i < 10; ++i)
	{
		ZeroMemory(sound, sizeof(sound));
		sprintf(sound, "����2%d", i);
		_loading->loadSound(sound, "Sugar Song&Bitter Step.mp3", true, false);
	}
	
	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone())
	{
		SCENEMANAGER->changeScene("�÷��̾�");
	}
}

void loadingScene::render()	
{
	_loading->render();
}
