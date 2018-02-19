#include "stdafx.h"
#include "characterAbility.h"


characterAbility::characterAbility()
{
}


characterAbility::~characterAbility()
{
}


HRESULT characterAbility::init()
{
	//백그라운드 이미지
	_bgImage = IMAGEMANAGER->findImage("캐릭터능력메뉴");

	//선택한 세이브 파일 가져오기 
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	int selectPlayerNum = INIDATA->loadDataInterger("gameData", "inventory", "selectChar");
	fileLoad(saveFileNum, selectPlayerNum);

	//버튼
	int buttonX, buttonY;
	buttonX = 100;
	buttonY = 25;
	_button = new fButton;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("아이콘힐", buttonX + (i * 150), buttonY);
		if (i == 1) _button->buttonSet("아이콘매직", buttonX + (i * 150), buttonY);
		if (i == 2) _button->buttonSet("아이콘레어", buttonX + (i * 150), buttonY);
	}


	//커서
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 10);



	return S_OK;
}

void characterAbility::release()
{

}

void characterAbility::update()	
{
	//커서
	cursorUpdate();

	//커서 컨트롤X  
	cursorKeyControlX(150, 3);



	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//버튼 벡터에서 삭제
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("능력치");
	}
}

void characterAbility::render()	
{
	_bgImage->render(getMemDC());  //백그라운드 이미지
	cursorRender();                //커서
	_button->render();             //버튼

	playerSlotRender();            //슬롯 데이터
}
