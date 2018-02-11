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
	_loading->init(0);

	//메뉴 이미지
	_loading->loadImage("능력메뉴", ".//prevProjectResource//SceneImage//abilitiesMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("옵션메뉴", ".//prevProjectResource//SceneImage//configMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("장비메뉴", ".//prevProjectResource//SceneImage//equipMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이템메뉴", ".//prevProjectResource//SceneImage//itemMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("메인메뉴", ".//prevProjectResource//SceneImage//mainMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("세이브로드메뉴", ".//prevProjectResource//SceneImage//saveLoadMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("상태메뉴", ".//prevProjectResource//SceneImage//statusMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀메뉴", ".//prevProjectResource//SceneImage//tilteMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("뉴게임", ".//prevProjectResource//SceneImage//menu_newGame.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("옵션메뉴", ".//prevProjectResource//SceneImage//menu_option.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//버튼 이미지
	_loading->loadImage("옵션버튼", ".//prevProjectResource//SceneImage//button.bmp", 0, 0, 273, 59, true, RGB(255, 0, 255));
	_loading->loadImage("옵션버튼롱", ".//prevProjectResource//SceneImage//button1.bmp", 0, 0, 205, 44, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터얼굴뒷배경", ".//prevProjectResource//SceneImage//faceBackground.bmp", 0, 0, 108, 108, true, RGB(255, 0, 255));
	_loading->loadImage("사운드볼륨상", ".//prevProjectResource//SceneImage//soundVolume_high.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadImage("사운드볼륨중", ".//prevProjectResource//SceneImage//soundVolume_medium.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadImage("사운드볼륨하", ".//prevProjectResource//SceneImage//soundVolume_low.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadImage("사운드볼륨끔", ".//prevProjectResource//SceneImage//soundVolume_off.bmp", 0, 0, 552, 61, true, RGB(255, 0, 255));
	_loading->loadFrameImage("선택커서", ".//prevProjectResource//SceneImage//selectCursor.bmp",54, 27, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼예스", ".//prevProjectResource//SceneImage//button_yes.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼노", ".//prevProjectResource//SceneImage//button_no.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));

	//플레이어 이미지
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
		SCENEMANAGER->changeScene("타이틀");
	}
}

void loadingScene::render()	
{
	_loading->render();
}
