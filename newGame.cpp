#include "stdafx.h"
#include "newGame.h"
#include "itemManager.h"


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


	//============================================================== 세이브 파일 로드
	int tmpSaveFileNum = 0;
	for (int i = 0; i < SAVEFILENUM; ++i)
	{
		char tmp[32];
		ZeroMemory(&tmp, sizeof(tmp));
		wsprintf(tmp, "saveFile%d", i);
		if (INIDATA->loadDataInterger(tmp, "fileInfo", "fileNum") != -1)
		{
			tmpSaveFileNum = i;
			break;
		}
	}
	
	switch (tmpSaveFileNum)  //파일이 있는 최소 세이브 파일 로딩
	{
		case 0:
			fileLoad(tmpSaveFileNum);
		break;
		case 1:
			fileLoad(tmpSaveFileNum);
		break;
		case 2:
			fileLoad(tmpSaveFileNum);
		break;
		case 3:
			fileLoad(tmpSaveFileNum);
		break;
	}
	//==============================================================



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
				_saveFileNum = INIDATA->loadDataInterger(numTemp, "fileInfo", "fileNum");

				//예외처리: 세이브파일이 4개일 경우 -> file0번에 저장
				if (_saveFileNum >= 3)
				{
					_saveFileNum = 0;
					break;  
				}
				if (_saveFileNum != -1)  //세이브 데이터가 있으면
				{
					_saveFileNum = _saveFileNum + 1;
					break;
				}
				else  //세이브 데이터가 없으면 || 세이브 데이터가 Full이면
				{
					_saveFileNum = 0;
				}
			}

			//================================== 저장파일 생성 ================================== 
			saveIniPlayerData(_saveFileNum, 0, "TINA",   "Magician",         3, 63, 63, 27, 27, maxExpValue[2],
				maxExpValue[3], 31, 33, 28, 39, 12, 42, 33, 5, 7, 0, "0", "-1", "-2", "-3", true);
			saveIniPlayerData(_saveFileNum, 1, "LOCKE", "Treasure Hunter",   3, 71, 71, 18, 18, maxExpValue[2],
				maxExpValue[3], 37, 40, 31, 28, 14, 46, 23, 15, 2, 1, "0", "-1", "-2", "-3", true);
			saveIniPlayerData(_saveFileNum, 2, "CELES",  "Rune Knight",      3, 67, 67, 26, 26, maxExpValue[2],
				maxExpValue[3], 34, 34, 31, 36, 16, 44, 31, 7, 9, 2, "0", "-1", "-2", "-3", true);
			saveIniPlayerData(_saveFileNum, 3, "SHADOW", "Assassin",         3, 74, 74, 17, 17, maxExpValue[2],
				maxExpValue[3], 39, 38, 30, 33, 23, 47, 25, 28, 9, 3, "0", "-1", "-2", "-3", true);

			saveIniSlotGameData(_saveFileNum, "OVER WORLD",3000 , 0, true);			//게임데이터: 세이브파일에 저장
			saveIniGameData(_saveFileNum, "OVER WORLD");							//게임데이터: 데이터베이스에 저장

			//아이템 저장
			itemSave(MENUITEM_ITEM, 1, 2, true, _saveFileNum);
			itemSave(MENUITEM_ITEM, 2, 2, true, _saveFileNum);
			itemSave(MENUITEM_ARMOR, 2, 2, true, _saveFileNum);
			itemSave(MENUITEM_WEAPON, 2, 2, true, _saveFileNum);
			//================================== 저장파일 생성 ================================== 

			//버튼삭제 
			_button->buttonRemove();
			delete _button;

			//플레이어 세이브파일 로드를 위한 신호값
			INIDATA->addData("gameData", "gameStart", "1");
			INIDATA->iniSave("gameData");

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

	if (_fileLoadOk[0]) playerSlotRender();  //플레이어 슬롯
	gameDataRender(true);  //게임 데이터(플레이장소/플레이시간/돈)
}


