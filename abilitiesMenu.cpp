#include "stdafx.h"
#include "abilitiesMenu.h"


abilitiesMenu::abilitiesMenu()
{
}


abilitiesMenu::~abilitiesMenu()
{
}



HRESULT abilitiesMenu::init()
{
	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("능력메뉴");

	//선택한 세이브 파일 가져오기 
	fileLoad(INIDATA->loadDataInterger("gameData", "gameData", "fileNum"));

	//커서
	cursorInit(CUSOR_RIGHT, 950, 60);
	_cursorYNum = 6;


	return S_OK;
}

void abilitiesMenu::release()
{

}

void abilitiesMenu::update()
{

	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//_button->buttonRemove();
		//delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void abilitiesMenu::render()
{
	_bgImage->render(getMemDC());  //백그라운드 이미지

	playerSlotRender();            //슬롯 데이터
	gameDataRender(false);		   //게임 데이터(플레이장소/플레이시간/돈)

}


