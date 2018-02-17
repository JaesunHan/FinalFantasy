#include "stdafx.h"
#include "newGame.h"


newGame::newGame()
{
}


newGame::~newGame()
{
}


HRESULT newGame::init()
{
	_bgImage = IMAGEMANAGER->findImage("뉴게임메뉴");
	cursorInit(CUSOR_RIGHT, 950, 190);

	_button = new fButton;
	_button->buttonSet("버튼예스", 1000, 187);
	_button->buttonSet("버튼노", 1000, 238);

	_saveFileNum = SAVEFILENUM;  //세이브파일 갯수

	fileLoad(0);


	return S_OK;
}

void newGame::release()
{

}

void newGame::update()
{
	cursorUpdate();
	_button->update();

	cursorKeyControlY(51, 2);

	//선택
	switch (_cursor.currentYNum)
	{
	case 0:
		//버튼 에니메이션 활성화
		_button->setVButtonAniStart(0, true);
		_button->setVButtonAniStart(1, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{

			//세이브파일이 없다면 saveFile0.ini && 파일이 있다면 saveFile1 ~ 3.ini 순차적 생성 
			for (int i = SAVEFILENUM; i >= 0; --i)
			{
				char numTemp[12];
				sprintf(numTemp, "saveFile%d", i);
				_saveFileNum = INIDATA->loadDataInterger(numTemp, "fileInfo", "num");

				if (_saveFileNum != -1)
				{
					_saveFileNum = _saveFileNum + 1;
					break;
				}
				else
				{
					_saveFileNum = 0;
				}
			}

			//저장파일 생성
			char saveFileNum[4];
			sprintf(saveFileNum, "%d", _saveFileNum);
			INIDATA->addData("fileInfo", "num", saveFileNum);
			INIDATA->addData("player0", "name", "TINA");
			INIDATA->addData("player0", "job", "Magician");
			INIDATA->addData("player0", "level", "3");
			INIDATA->addData("player0", "hp", "63");
			INIDATA->addData("player0", "maxHp", "63");
			INIDATA->addData("player0", "mp", "27");
			INIDATA->addData("player0", "maxMp", "27");

			char saveFileName[16];
			sprintf(saveFileName, "saveFile%d", _saveFileNum);
			INIDATA->iniSave(saveFileName);

			//버튼삭제 
			_button->buttonRemove();
			delete _button;
			//씬이동
			SCENEMANAGER->changeScene("월드맵씬");
		}
		break;
	case 1:
		//버튼 에니메이션 활성화
		_button->setVButtonAniStart(1, true);
		_button->setVButtonAniStart(0, false);

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			//버튼삭제 
			_button->buttonRemove();
			delete _button;
			//씬이동
			SCENEMANAGER->changeScene("타이틀");
		}
		break;
	}
}

void newGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	if (_fileLoadOk[0]) playerSlotRender();
}


