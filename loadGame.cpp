#include "stdafx.h"
#include "loadGame.h"
#include "itemManager.h"
#include "worldMapScene.h"


loadGame::loadGame()
{
}


loadGame::~loadGame()
{
}


HRESULT loadGame::init()
{
	_bgImage = IMAGEMANAGER->findImage("로드메뉴");
	cursorInit(CUSOR_RIGHT, 50, 38);

	_cursorXNum = 4;
	_cursorYNum = 2;

	_button = new fButton;
	_button->buttonSet("버튼파일", 65, 25,  "FILE 1", 30);
	_button->buttonSet("버튼파일", 255, 25, "FILE 2", 30);
	_button->buttonSet("버튼파일", 445, 25, "FILE 3", 30);
	_button->buttonSet("버튼파일", 635, 25, "FILE 4", 30);
	_button->buttonSet("버튼예스", 1000, 187);
	_button->buttonSet("버튼노", 1000, 238);

	for(int i = 0; i < 4; ++i) 	_fileLoadOk[i] = false;
	_selectFileCount = 2;

	_saveFileSelect = false;



	return S_OK;
}

void loadGame::release()
{

}

void loadGame::update()
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
					//게임데이터: 데이터베이스에 저장
					saveIniGameData(0);                

					//세이브파일 출력
					fileLoad(0);
					_selectFileCount--;

					//세이브파일이 없으면...
					if (!_fileLoadOk[0])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					//게임데이터: 데이터베이스에 저장
					saveIniGameData(1);

					//세이브파일 출력
					fileLoad(1);
					_selectFileCount--;

					//세이브파일이 없으면...
					if (!_fileLoadOk[1])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					//게임데이터: 데이터베이스에 저장
					saveIniGameData(2);

					//세이브파일 출력
					fileLoad(2);
					_selectFileCount--;

					//세이브파일이 없으면...
					if (!_fileLoadOk[2])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					//게임데이터: 데이터베이스에 저장
					saveIniGameData(3);

					//세이브파일 출력
					fileLoad(3);
					_selectFileCount--;

					//세이브파일이 없으면...
					if (!_fileLoadOk[3])
					{
						_selectFileCount = 2;
						_saveFileSelect = false;
						playerSlotRemove();
					}
					else
					{
						if (_selectFileCount <= 0)
						{
							_saveFileSelect = true;
							_cursor.cursorReset = false;
							_selectFileCount = 2;
						}
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
					_button->buttonRemove();
					delete _button;

					_saveFileSelect = false;

					//플레이어 세이브파일 로드를 위한 신호값 
					INIDATA->addData("gameData", "gameStart", "1");
					INIDATA->iniSave("gameData");

					//템프파일에 로드된 파일 복사
					fileCopyTmpFile(_cursor.currentXNum);

					SCENEMANAGER->changeScene("월드맵씬");
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
		SCENEMANAGER->changeScene("타이틀", false);
	}
}

void loadGame::render()
{
	_bgImage->render(getMemDC());
	_button->render();
	cursorRender();

	playerSlotRender();
	gameDataRender(false);  //게임 데이터(플레이장소/플레이시간/돈)
}


