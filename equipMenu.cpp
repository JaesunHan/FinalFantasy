#include "stdafx.h"
#include "equipMenu.h"


equipMenu::equipMenu()
{
}


equipMenu::~equipMenu()
{
}

HRESULT equipMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("장비메뉴");

	//tmp 파일 가져오기 (skgFile)
	fileLoad(0, -1, true);


	//플레이어 인원수
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	int playerNum = INIDATA->loadDataBodyNum(saveFileNum);  //플레이어 인원수

	//버튼
	int buttonX, buttonY;
	buttonX = 1000;
	buttonY = 100;
	_button = new fButton;
	for (int i = 0; i < playerNum; ++i)
	{
		//세이브파일 이름
		TCHAR fileName[32];
		ZeroMemory(&fileName, sizeof(fileName));
		wsprintf(fileName, "saveFile%d", saveFileNum);

		//캐릭터 넘버
		TCHAR playerNum[32];
		ZeroMemory(&playerNum, sizeof(playerNum));
		wsprintf(playerNum, "player%d", i);

		//해당 캐릭터 버튼생성
		if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "TINA"))
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "TINA", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "CELES"))
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "CELES", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "LOCKE"))
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "LOCKE", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "SHADOW"))
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "SHADOW", 30);
	}

	//커서
	_cursorYNum = playerNum;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);


	return S_OK;
}

void equipMenu::release()
{

}

void equipMenu::update()
{
	//타이머 
	_gameTotalTime += TIMEMANAGER->getElapsedTime();

	//커서
	cursorUpdate();
	cursorKeyControlY(65, _cursorYNum);

	//버튼
	_button->update();

	//선택
	switch (_cursor.currentYNum)
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
		case 3:
			buttonOnActive();
		break;
	}




	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void equipMenu::render()
{
	_bgImage->render(getMemDC());  //백그라운드 이미지
	cursorRender();                //커서
	_button->render();             //버튼

	playerSlotRender();            //슬롯 데이터

	gameDataRender(false);  //게임 데이터(플레이장소/플레이시간/돈)
	gamePlayTime();			//게임 플레이 타임
}


void equipMenu::buttonOnActive()
{
	//버튼 에니메이션 활성화
	_button->setVButtonAniStart(_cursor.currentYNum, true);
	for (int i = 0; i < _cursorYNum; ++i)
	{
		if (i == _cursor.currentYNum) continue;
		_button->setVButtonAniStart(i, false);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		char charBuff[4];
		//내부 데이터베이스에 저장: 선택한 캐릭터 정보 
		INIDATA->addData("inventory", "selectChar", itoa(_cursor.currentYNum, charBuff, 10));
		INIDATA->iniSave("gameData");

		//버튼 벡터에서 삭제
		_button->buttonRemove();
		delete _button;

		//씬전환
		SCENEMANAGER->changeScene("캐릭터장비");
	}
}
