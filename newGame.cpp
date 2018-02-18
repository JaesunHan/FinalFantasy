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

				if (_saveFileNum != -1)  //세이브 데이터가 있으면
				{
					_saveFileNum = _saveFileNum + 1;
					break;
				}
				else  //세이브 데이터가 없으면
				{
					_saveFileNum = 0;
				}
			}

			//================================== 저장파일 생성 ================================== 
			saveIniPlayerData(_saveFileNum, 0, "TINA",   "Magician",        3, 63, 63, 27, 27);
			saveIniPlayerData(_saveFileNum, 1, "CELES",  "Rune Knight",     2, 56, 56, 21, 21);
			saveIniPlayerData(_saveFileNum, 2, "LOCK",   "Treasure Hunter", 2, 68, 68, 0, 0);
			saveIniPlayerData(_saveFileNum, 3, "SHADOW", "Assassin",        3, 72, 72, 0, 0);

			saveIniSlotGameData(_saveFileNum, "OVER WORLD",3000 , 0, 0);  //게임데이터: 세이브파일에 저장
			saveIniGameData(_saveFileNum, "OVER WORLD");                  //게임데이터: 데이터베이스에 저장
			//================================== 저장파일 생성 ================================== 

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

	if (_fileLoadOk[0]) playerSlotRender();  //플레이어 슬롯
	gameDataRender(true);  //게임 데이터(플레이장소/플레이시간/돈)

	textPrint(getMemDC(), SCENEMANAGER->getCurrentSceneName().c_str(), 100, 100);
}


