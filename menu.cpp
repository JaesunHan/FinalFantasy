#include "stdafx.h"
#include "menu.h"


menu::menu()
{
}
menu::~menu()
{
}


HRESULT menu::init()
{

	return S_OK;
}

void menu::release()
{

}

void menu::update()	
{

}

void menu::render()	
{
	_bgImage->render(getMemDC());
	cursorRender();
}


//============================== cursor ==============================

//                     커서형태(L,R)     커서위치X     커서위치Y
void  menu::cursorInit(CURSOR_TYPE type, float startX, float startY)
{
	_cursorType = type;

	_cursor.img = IMAGEMANAGER->findImage("선택커서");
	_cursor.x = startX;
	_cursor.y = startY;
	_cursor.speed = 1.0f;
	_cursor.fForce = 0.01f;
	_cursor.startX = _cursor.x;
	_cursor.startY = _cursor.y;
	_cursor.minX = 0;
	_cursor.maxX = 0;
	_cursor.currentXNum = 0;
	_cursor.currentYNum = 0;
	_cursor.cursorOn = false;
	_cursor.cursorReset = false;

	switch (_cursorType)
	{
		case CUSOR_LEFT:		
			_cursor.img->setFrameX(1);
		break;
		case CUSOR_RIGHT:
			_cursor.img->setFrameX(0);
		break;
	}
}

void  menu::cursorUpdate()
{
	switch (_cursorType)
	{
		case CUSOR_LEFT:
			//처음 위치로
			if (_cursor.x > _cursor.startX)
			{
				_cursor.x = _cursor.startX;
				_cursor.fForce = 0.01f;
				_cursor.speed = 1.0f;
			}
			
			//커서 움직임
			_cursor.fForce += 0.001f;
			_cursor.speed -= _cursor.fForce;
			_cursor.x -= _cursor.speed;
		break;
		case CUSOR_RIGHT:
			//처음 위치로
			if (_cursor.x < _cursor.startX)
			{
				_cursor.x = _cursor.startX;
				_cursor.fForce = 0.01f;
				_cursor.speed = 1.0f;
			}

			//커서 움직임
			_cursor.fForce += 0.001f;
			_cursor.speed -= _cursor.fForce;
			_cursor.x += _cursor.speed;
		break;
	}
}

//                           커서X축 이동값    이동횟수
void menu::cursorKeyControlX(float moveValueX, int moveNumber)
{
	if (!_cursor.cursorOn)
	{
		_cursor.minX = _cursor.x;
		_cursor.maxX = _cursor.x + (moveValueX * (moveNumber - 1));

		_cursor.currentXNum = 0;
		_cursor.cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_cursor.x += moveValueX;
		_cursor.startX += moveValueX;
		_cursor.currentXNum++;

		//예외처리: 커서가 선택항목을 벗어나면 다시 처음 선택지로~~
		if (_cursor.currentXNum > (moveNumber - 1))
		{
			_cursor.x = _cursor.minX;
			_cursor.startX = _cursor.minX;
			_cursor.currentXNum = 0;
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_cursor.x -= moveValueX;
		_cursor.startX -= moveValueX;
		_cursor.currentXNum--;

		//예외처리: 커서가 선택항목을 벗어나면 마지막 선택지로~~
		if (_cursor.x < _cursor.minX)
		{
			_cursor.x = _cursor.maxX;
			_cursor.startX = _cursor.maxX;
			_cursor.currentXNum = (moveNumber - 1);
		}
	}


	//예외처리: 커서 선택위치 반환을 위한...
	if (_cursor.currentXNum <= 0)					_cursor.currentXNum = 0;
	if (_cursor.currentXNum >= (moveNumber))		_cursor.currentXNum = (moveNumber - 1);
}

//                          커서Y축 이동값    이동횟수
void menu::cursorKeyControlY(float moveValueY, int downNumber)
{
	if (!_cursor.cursorOn)
	{
		_cursor.currentYNum = 0;
		_cursor.cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_cursor.y += moveValueY;
		_cursor.currentYNum++;

		//예외처리: 커서가 선택항목을 벗어나면 다시 처음 선택지로~~
		if (_cursor.y > _cursor.startY + (moveValueY * (downNumber - 1)))
		{
			_cursor.y = _cursor.startY;
			_cursor.currentYNum = 0;
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_cursor.y -= moveValueY;
		_cursor.currentYNum--;

		//예외처리: 커서가 선택항목을 벗어나면 마지막 선택지로~~
		if (_cursor.y < _cursor.startY)
		{
			_cursor.y = _cursor.startY + (moveValueY * (downNumber - 1));
			_cursor.currentYNum = downNumber - 1;
		}
	}


	//예외처리: 커서 선택위치 반환을 위한...
	if (_cursor.currentYNum <= 0)				 _cursor.currentYNum = 0;
	if (_cursor.currentYNum >= (downNumber - 1)) _cursor.currentYNum = (downNumber - 1);
}

void  menu::cursorRender()
{
	_cursor.img->frameRender(getMemDC(), _cursor.x, _cursor.y);
}

void menu::cursorResetXY(float cursorX, float cursorY)
{
	_cursor.cursorReset = true;

	_cursor.x = _cursor.startX = cursorX;
	_cursor.y = _cursor.startY = cursorY;
}
//============================== cursor ==============================





//============================== player ==============================

//                        이미지키값      이미지위치XY      레벨	   직업	       체력    최대체력   마력    최대마력
void menu::playerSlotInit(string keyName, float x, float y, int level, char* job, int hp, int maxHp, int mp, int maxMp)
{
	tagPlayer player;
	ZeroMemory(&player, sizeof(player));

	player.img = IMAGEMANAGER->findImage(keyName);
	wsprintf(player.name, "%s", keyName.c_str());
	player.x = x;
	player.y = y;
	player.level = level;
	player.hp = hp;
	player.maxHp = maxHp;
	player.mp = mp;
	player.maxMp = maxMp;
	wsprintf(player.job, "%s", job);

	_vPlayer.push_back(player);
}

void menu::playerSlotUpdate()
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		
	}
}

void menu::playerSlotKeyControl(float slotValueY, int slotNum)
{
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		for (int i = 0; i < _vPlayer.size(); ++i)
		{
			_vPlayer[i].y += slotValueY * slotNum;
		}
	}
}

void menu::playerSlotRender()	 
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		//이미지 출력
		_vPlayer[i].img->render(getMemDC(), _vPlayer[i].x, _vPlayer[i].y);

		//int -> string 형변환
		char strLevel[128];
		sprintf(strLevel, "%d", _vPlayer[i].level);	
		char strHp[128];
		sprintf(strHp, "%d / %d", _vPlayer[i].hp, _vPlayer[i].maxHp);
		char strMp[128];
		sprintf(strMp, "%d / %d", _vPlayer[i].mp, _vPlayer[i].maxMp);

		//텍스트 출력
		textPrint(getMemDC(), _vPlayer[i].name, _vPlayer[i].x + 150, _vPlayer[i].y,      30, 30, "Stencil",  COLOR_BLACK, false);	//이름
		textPrint(getMemDC(), _vPlayer[i].job,  _vPlayer[i].x + 300, _vPlayer[i].y,      25, 25, "Roboto",  COLOR_BLACK, false);	//직업
		textPrint(getMemDC(), "LV",			    _vPlayer[i].x + 150, _vPlayer[i].y + 30, 15, 15, "HY견고딕", COLOR_BLUE,  false);	//"LV"
		textPrint(getMemDC(), strLevel,         _vPlayer[i].x + 200, _vPlayer[i].y + 30, 15, 15, "HY견고딕", COLOR_BLACK, false);	//레벨
		textPrint(getMemDC(), "HP",				_vPlayer[i].x + 150, _vPlayer[i].y + 50, 15, 15, "HY견고딕", COLOR_BLUE, false);	//"HP"
		textPrint(getMemDC(), strHp,			_vPlayer[i].x + 200, _vPlayer[i].y + 50, 15, 15, "HY견고딕", COLOR_BLACK, false);	//체력
		if (_vPlayer[i].mp == -1) continue;  //예외처리: MP가 없으면 건너띄기
		textPrint(getMemDC(), "MP",				_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);	//"MP"
		textPrint(getMemDC(), strMp,			_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);	//마력
	}

	if (_vPlayer.size() == 0)
	{
		textPrint(getMemDC(), "EMPTY", 440, 140, 30, 30, "HY견고딕", COLOR_BLACK);
	}
}

void menu::playerSlotRemove()
{
	if (_vPlayer.size() != 0)
	{
		for (int i = 0; i < _vPlayer.size(); ++i)
		{
			_vPlayer[i].img = NULL;
			_vPlayer.erase(_vPlayer.begin() + i);
		}
	}

	_vPlayer.clear();
}

//플레이어 세이브 파일 로드      ↓플레이어 슬롯넘버(특정 캐릭터 슬롯 하나만 띄울경우)
void menu::fileLoad(int fileNum, int playerNumber)
{
	//슬롯 초기화
	playerSlotRemove();
	if (!_fileLoadOk[fileNum]) _selectFileCount = 2;  //버튼선택 초기화

	//세이브파일 넘버
	char saveFileNum[32];
	ZeroMemory(&saveFileNum, sizeof(saveFileNum));
	wsprintf(saveFileNum, "saveFile%d", fileNum);


	for (int i = 0; i < 4; ++i)
	{
		//플레이어 번호 담을 변수
		char playerNum[16];
		ZeroMemory(&playerNum, sizeof(playerNum));

		if (playerNumber != -1)  //특정 캐릭터 슬롯 선택시
		{
			wsprintf(playerNum, "player%d", playerNumber);
			i = 0;
		}
		else
		{
			wsprintf(playerNum, "player%d", i);
		}

		//플레이어 정보담기
		ZeroMemory(&_playerSlot, sizeof(_playerSlot));
		wsprintf(_playerSlot.name, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "name"));
		_playerSlot.img = IMAGEMANAGER->findImage(_playerSlot.name);
		wsprintf(_playerSlot.job, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "job"));
		_playerSlot.level = INIDATA->loadDataInterger(saveFileNum, playerNum, "level");
		if (_playerSlot.level == -1) continue; //예외처리: 정보가 없으면 다음으로...
		_playerSlot.hp = INIDATA->loadDataInterger(saveFileNum, playerNum, "hp");
		_playerSlot.maxHp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxHp");
		_playerSlot.mp = INIDATA->loadDataInterger(saveFileNum, playerNum, "mp");
		_playerSlot.maxMp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxMp");

		//플레이어 출력정보 담기
		playerSlotInit(_playerSlot.name, 65, 102 + (i * 137), _playerSlot.level, _playerSlot.job, _playerSlot.hp,
			_playerSlot.maxHp, _playerSlot.mp, _playerSlot.maxMp);


		//정보가 담겨있으면...
		_fileLoadOk[fileNum] = true;

		if (playerNumber != -1) break;
	}

}

//============================== player ==============================


//============================ save & load ===========================
                   
tagElements menu::saveTxtData(int fileNum, string cStage)
{
	char tmp[36];
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf(tmp, "saveFile%d", fileNum);

	_playerElements.currentFile = tmp;
	_playerElements.currentScene = cStage;

	return _playerElements;
}


void menu::saveIniPlayerData(int fileNum, int playerNum, string cName, string job, int level, int hp, int maxHp, int mp, int maxMp)
{
	//파일정보 넘버
	TCHAR tmp[4];
	ZeroMemory(&tmp, sizeof(tmp));
	wsprintf(tmp, "%d", fileNum);
	INIDATA->addData("fileInfo", "fileNum",  tmp);

	//플레이어 넘버
	TCHAR subjectNum[12];
	ZeroMemory(&subjectNum, sizeof(subjectNum));
	wsprintf(subjectNum, "player%d", playerNum);
	//플레이어 이름 & 직업
	INIDATA->addData(subjectNum,  "name",  cName.c_str());
	INIDATA->addData(subjectNum,  "job",   job.c_str());
	//플레이어 레벨
	TCHAR tmp1[4];
	ZeroMemory(&tmp1, sizeof(tmp1));
	wsprintf(tmp1, "%d", level);
	INIDATA->addData(subjectNum,  "level", tmp1);
	//플레이어 체력
	TCHAR tmp2[4];
	ZeroMemory(&tmp2, sizeof(tmp2));
	wsprintf(tmp2, "%d", hp);
	INIDATA->addData(subjectNum,  "hp", tmp2);
	//플레이어 최대체력
	TCHAR tmp3[4];
	ZeroMemory(&tmp3, sizeof(tmp3));
	wsprintf(tmp3, "%d", maxHp);
	INIDATA->addData(subjectNum,  "maxHp", tmp3);
	//플레이어 마력
	TCHAR tmp4[4];
	ZeroMemory(&tmp4, sizeof(tmp4));
	wsprintf(tmp4, "%d", mp);
	INIDATA->addData(subjectNum,  "mp", tmp4);
	//플레이어 최대마력
	TCHAR tmp5[4];
	ZeroMemory(&tmp5, sizeof(tmp5));
	wsprintf(tmp5, "%d", maxMp);
	INIDATA->addData(subjectNum,  "maxMp", tmp5);

	//파일저장
	TCHAR saveFileName[16];
	wsprintf(saveFileName, "saveFile%d", fileNum);
	INIDATA->iniSave(saveFileName);
}

void menu::saveIniSlotGameData(int fileNum, string stage, int gil, int playTime, int steps)
{
	//스테이지
	INIDATA->addData("gameData", "stage", stage.c_str());

	//플레이어 돈
	TCHAR tmp2[8];
	ZeroMemory(&tmp2, sizeof(tmp2));
	wsprintf(tmp2, "%d", gil);
	INIDATA->addData("gameData", "gil", tmp2);

	//플레이 시간
	TCHAR tmp3[32];
	ZeroMemory(&tmp3, sizeof(tmp3));
	wsprintf(tmp3, "%d", playTime);
	INIDATA->addData("gameData", "playTime", tmp3);

	//플레이 스텝
	TCHAR tmp4[32];
	ZeroMemory(&tmp4, sizeof(tmp4));
	wsprintf(tmp4, "%d", steps);
	INIDATA->addData("gameData", "steps", tmp4);

	//파일저장
	TCHAR saveFileName[16];
	wsprintf(saveFileName, "saveFile%d", fileNum);
	INIDATA->iniSave(saveFileName);

}

//============================ save & load ===========================


//============================== gameData ============================

void menu::saveIniGameData(int fileNum, string currentScene)
{
	//세이브 파일넘버
	TCHAR tmp1[8];
	ZeroMemory(&tmp1, sizeof(tmp1));
	wsprintf(tmp1, "%d", fileNum);
	INIDATA->addData("gameData", "fileNum", tmp1);

	//저장파일이름
	TCHAR saveFileName[16];
	wsprintf(saveFileName, "saveFile%d", fileNum);;
	INIDATA->addData("gameData", "saveFileName", saveFileName);

	if (currentScene != "") INIDATA->addData("gameData", "currentScene", currentScene.c_str());

	//파일저장
	INIDATA->iniSave("gameData");
}

void menu::gameDataRender(bool isNewGame)
{
	//현재 선택한 세이브파일 정보 로드
	tagCurrentGameData tmpGD;  
	wsprintf(tmpGD.saveFileName, "%s", INIDATA->loadDataString("gameData", "gameData", "saveFileName"));

	wsprintf(tmpGD.stage, "%s", INIDATA->loadDataString(tmpGD.saveFileName, "gameData", "stage"));
	tmpGD.playTime = INIDATA->loadDataInterger(tmpGD.saveFileName, "gameData", "playTime");
	tmpGD.gil = INIDATA->loadDataInterger(tmpGD.saveFileName, "gameData", "gil");
	tmpGD.steps = INIDATA->loadDataInterger(tmpGD.saveFileName, "gameData", "steps");

	
	if (isNewGame)
	{
		//NEWGAME: 해당파일이 없으면 첫번째 파일부터 탐색해서 로드
		if (tmpGD.playTime == -1)
		{
			for (int i = 0; i < 4; ++i)
			{
				char tmpSaveFileNum[16];
				ZeroMemory(&tmpSaveFileNum, sizeof(tmpSaveFileNum));
				sprintf(tmpSaveFileNum, "saveFile%d", i);

				wsprintf(tmpGD.stage, "%s", INIDATA->loadDataString(tmpSaveFileNum, "gameData", "stage"));
				tmpGD.playTime = INIDATA->loadDataInterger(tmpSaveFileNum, "gameData", "playTime");
				tmpGD.gil = INIDATA->loadDataInterger(tmpSaveFileNum, "gameData", "gil");
				tmpGD.steps = INIDATA->loadDataInterger(tmpSaveFileNum, "gameData", "steps");

				if (tmpGD.playTime != -1) break;
			}
		}
	}
    

	//텍스트 출력
	if (tmpGD.playTime != -1)
	{
		char tmpBuff[32];
		textPrint(getMemDC(), tmpGD.stage,					     1050, 392, 30, 30, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.playTime, tmpBuff, 10), 1080, 462, 20, 20, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.steps, tmpBuff, 10),    1080, 516, 20, 20, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.gil, tmpBuff, 10),      1080, 570, 20, 20, "Stencil", COLOR_WHITE, true);
	}
}

//============================== gameData ============================