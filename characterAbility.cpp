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
	buttonX = 150;
	buttonY = 10;
	_button = new fButton;
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0) _button->buttonSet("아이콘힐", buttonX + (i * 210), buttonY);
		if (i == 1) _button->buttonSet("아이콘공격", buttonX + (i * 210), buttonY);
		if (i == 2) _button->buttonSet("아이콘방어", buttonX + (i * 210), buttonY);
	}


	//커서
	_cursorXNum = 3;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);



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
	cursorKeyControlX(210, _cursorXNum);

	//선택
	switch (_cursor.currentXNum)
	{
		case 0:
			buttonOnActive();
		break;
		case 1:
			buttonOnActive();
		break;
		case 2:
			buttonOnActive();
		break;
	}



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
	_button->render();             //버튼
	cursorRender();                //커서

	playerSlotRender();            //슬롯 데이터
}

//버튼 에니메이션 시작
void characterAbility::buttonOnActive()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursor.currentXNum, true);
	for (int i = 0; i < _cursorXNum; ++i)
	{
		if (i == _cursor.currentXNum) continue;
		_button->setVButtonAniStart(i, false);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{

	}
}

//캐릭터별 스킬버튼 생성
void characterAbility::skillButtonSet()
{

}