#include "stdafx.h"
#include "saveLoadMenu.h"
#include "itemManager.h"
#include "worldMapScene.h"


saveLoadMenu::saveLoadMenu()
{
}
saveLoadMenu::~saveLoadMenu()
{
}


HRESULT saveLoadMenu::init()
{
	_bgImage = IMAGEMANAGER->findImage("세이브메뉴");
	cursorInit(CUSOR_RIGHT, 50, 38);

	_cursorXNum = 4;
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("버튼파일", 65, 25, "FILE 1", 30);
	_button->buttonSet("버튼파일", 255, 25, "FILE 2", 30);
	_button->buttonSet("버튼파일", 445, 25, "FILE 3", 30);
	_button->buttonSet("버튼파일", 635, 25, "FILE 4", 30);
	_button->buttonSet("버튼예스", 1000, 187);
	_button->buttonSet("버튼노", 1000, 238);

	for (int i = 0; i < 4; ++i) _fileLoadOk[i] = false;
	_selectFileCount = 2;

	_saveFileSelect = false;
	_tmpLoasdSaveFileNum = 0;
	_resetCount = false;
	_resetCountSlotNum = -1;


	return S_OK;
}

void saveLoadMenu::release()
{

}

void saveLoadMenu::update()	
{
	cursorUpdate();
	_button->update();


	if (!_saveFileSelect)
	{
		//커서위치 리셋
		if (!_cursor.cursorReset)
		{
			cursorResetXY(50, 38);
			_cursor.currentXNum = 0;
		}

		//커서 컨트롤X  
		cursorKeyControlX(190, _cursorXNum);

		//선택
		switch (_cursor.currentXNum)
		{
		case 0:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//선택버튼으로 이동
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//선택카운트 초기화
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
					_resetCountSlotNum = _cursor.currentXNum;
				}

				//게임데이터: 데이터베이스에 저장
				saveIniGameData(0);

				//세이브파일 출력
				_fileLoadOk[0] = true;
				fileLoad(0);
			
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}
			}
			break;
		case 1:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//선택버튼으로 이동
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//선택카운트 초기화
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
					_resetCountSlotNum = _cursor.currentXNum;
				}

				//게임데이터: 데이터베이스에 저장
				saveIniGameData(1);

				//세이브파일 출력
				_fileLoadOk[1] = true;
				fileLoad(1);
	
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}

			}
			break;
		case 2:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//선택버튼으로 이동
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//선택카운트 초기화
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
					_resetCountSlotNum = _cursor.currentXNum;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
				}

				//게임데이터: 데이터베이스에 저장
				saveIniGameData(2);

				//세이브파일 출력
				_fileLoadOk[2] = true;
				fileLoad(2);
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}
			}
			break;
		case 3:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentXNum, true);
			for (int i = 0; i < _cursorXNum; ++i)
			{
				if (i == _cursor.currentXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//선택버튼으로 이동
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				//선택카운트 초기화
				if (!_resetCount)
				{
					_selectFileCount = 2;
					_resetCount = true;
					_resetCountSlotNum = _cursor.currentXNum;
				}
				if (_resetCountSlotNum != _cursor.currentXNum)
				{
					_selectFileCount = 2;
				}

				//게임데이터: 데이터베이스에 저장
				saveIniGameData(3);

				//세이브파일 출력
				_fileLoadOk[3] = true;
				fileLoad(3);
				_selectFileCount--;


				if (_selectFileCount <= 0)
				{
					_saveFileSelect = true;
					_cursor.cursorReset = false;
					_selectFileCount = 2;

					_tmpLoasdSaveFileNum = _cursor.currentXNum;
					_resetCount = false;
				}

			}
			break;
		}
	}
	else //YES&NO 버튼 선택
	{
		//커서위치 리셋
		if (!_cursor.cursorReset)
		{
			cursorResetXY(950, 190);
			_cursor.currentYNum = 0;
		}

		//커서 컨트롤Y
		cursorKeyControlY(51, _cursorYNum);

		//선택
		switch (_cursor.currentYNum)
		{
		case 0:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum + _cursorXNum, true);
			for (int i = _cursorXNum; i < _cursorXNum + _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum + _cursorXNum) continue;
				_button->setVButtonAniStart(i, false);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_saveFileSelect = false;

				//플레이시간 저장
				char tmpTime[16];
				ZeroMemory(&tmpTime, sizeof(tmpTime));
				sprintf(tmpTime, "%f", _gameTotalTime);
				INIDATA->addData("gameData", "playTime", tmpTime);
				INIDATA->iniSave("skgFile");

				//tmpFile -> saveFile copy
				fileCopySaveFile(_cursor.currentXNum);


				_saveFileSelect = false;
				_cursor.cursorReset = false;
				_button->setVButtonAniStart(4, false);
				_button->setVButtonAniStart(5, false);	

				//옵션창으로...
				_button->buttonRemove();
				delete _button;
				playerSlotRemove();
				SCENEMANAGER->changeSceneType0("옵션");
			}
			break;
		case 1:
			//버튼 에니메이션 활성화
			_button->setVButtonAniStart(_cursor.currentYNum + _cursorXNum, true);
			for (int i = _cursorXNum; i < _cursorXNum + _cursorYNum; ++i)
			{
				if (i == _cursor.currentYNum + _cursorXNum) continue;
				_button->setVButtonAniStart(i, false);
			}
			//파일선택 버튼으로 이동
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
			{
				_saveFileSelect = false;
				_cursor.cursorReset = false;
				_button->setVButtonAniStart(4, false);
				_button->setVButtonAniStart(5, false);
			}
			break;
		}
	}


	//옵션메뉴 나가기
	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		_button->buttonRemove();
		delete _button;
		playerSlotRemove();
		SCENEMANAGER->changeSceneType0("옵션");
	}
}

void saveLoadMenu::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	playerSlotRender();
	gameDataRender(false);  //게임 데이터(플레이장소/플레이시간/돈)
}


