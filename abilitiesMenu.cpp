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
	int saveFileNum = INIDATA->loadDataInterger("gameData", "gameData", "fileNum");
	fileLoad(saveFileNum);
	int playerNum = INIDATA->loadDataBodyNum(saveFileNum);

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
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "LOCK"))
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "LOCK", 30);
		else if (!strcmp(INIDATA->loadDataString(fileName, playerNum, "name"), "SHADOW"))
			_button->buttonSet("버튼네임", buttonX, buttonY + (i * 65), "SHADOW", 30);
	}



	//커서
	_cursorYNum = playerNum;
	cursorInit(CUSOR_RIGHT, buttonX - 50, buttonY + 20);





	return S_OK;
}

void abilitiesMenu::release()
{

}

void abilitiesMenu::update()
{
	//커서
	cursorUpdate();
	cursorKeyControlY(65, _cursorYNum);

	//버튼
	_button->update();






	//옵션 메뉴가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		//버튼 벡터에서 삭제
		_button->buttonRemove();
		delete _button;
		SCENEMANAGER->changeScene("옵션");
	}
}

void abilitiesMenu::render()
{
	_bgImage->render(getMemDC());  //백그라운드 이미지
	cursorRender();                //커서
	_button->render();             //버튼

	playerSlotRender();            //슬롯 데이터
	gameDataRender(false);		   //게임 데이터(플레이장소/플레이시간/돈)
}


