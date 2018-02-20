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
void menu::cursorKeyControlX(float moveValueX, int moveNumber, bool leftMove)
{
	if (!_cursor.cursorOn)
	{
		if (!leftMove)
		{
			_cursor.minX = _cursor.x;
			_cursor.maxX = _cursor.x + (moveValueX * (moveNumber - 1));
		}
		else
		{
			_cursor.minX = _cursor.x - (moveValueX * (moveNumber - 1));
			_cursor.maxX = _cursor.x;
		}

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

//------------------------------  slot  ------------------------------ 
//slot                    이미지키값      이미지위치XY      레벨	   직업	       체력    최대체력   마력    최대마력
void menu::playerSlotInit(string keyName, float x, float y, int level, char* job, int hp, int maxHp, int mp, int maxMp, int exp, int maxExp, int partyIdx)
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
	player.exp = exp;
	player.maxExp = maxExp;
	player.partyIdx = partyIdx;
	wsprintf(player.job, "%s", job);

	_vPlayer.push_back(player);
}

void menu::playerSlotUpdate()
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		//_vPlayer[i].partyIdx
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
		char strLevel[INTCHARBUFF];
		sprintf(strLevel, "%d", _vPlayer[i].level);	
		char strHp[INTCHARBUFF];
		sprintf(strHp, "%d / %d", _vPlayer[i].hp, _vPlayer[i].maxHp);
		char strMp[INTCHARBUFF];
		sprintf(strMp, "%d / %d", _vPlayer[i].mp, _vPlayer[i].maxMp);
		//다음레벨까지 남은 경험치 계산
		char strExp[INTCHARBUFF];
		sprintf(strExp, "%d", (maxExpValue[_vPlayer[i].level + 1] - _vPlayer[i].exp));

		//텍스트 출력
		textPrint(getMemDC(), _vPlayer[i].name, _vPlayer[i].x + 150, _vPlayer[i].y,      30, 30, "Stencil",  COLOR_BLACK, false);		//이름
		textPrint(getMemDC(), _vPlayer[i].job,  _vPlayer[i].x + 300, _vPlayer[i].y,      25, 25, "Roboto",  COLOR_BLACK, false);		//직업
		textPrint(getMemDC(), "LV",			    _vPlayer[i].x + 150, _vPlayer[i].y + 30, 15, 15, "HY견고딕", COLOR_BLUE,  false);		//"LV"
		textPrint(getMemDC(), strLevel,         _vPlayer[i].x + 200, _vPlayer[i].y + 30, 15, 15, "HY견고딕", COLOR_BLACK, false);		//레벨
		textPrint(getMemDC(), "HP",				_vPlayer[i].x + 150, _vPlayer[i].y + 50, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"HP"
		textPrint(getMemDC(), strHp,			_vPlayer[i].x + 200, _vPlayer[i].y + 50, 15, 15, "HY견고딕", COLOR_BLACK, false);		//체력
		textPrint(getMemDC(), "MP",				_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"MP"
		textPrint(getMemDC(), strMp,			_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//마력
		textPrint(getMemDC(), "For Next Level",		_vPlayer[i].x + 150, _vPlayer[i].y + 90, 15, 15, "HY견고딕", COLOR_BLUE, false);	//"레벨업 남은 경험치"
		textPrint(getMemDC(), strExp,				_vPlayer[i].x + 300, _vPlayer[i].y + 90, 15, 15, "HY견고딕", COLOR_BLACK, false);	//다음레벨 경험치 - 현재 경험치
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
//------------------------------  slot  ------------------------------ 


//-----------------------------  status  ----------------------------- 
           
void menu::playerStatusInit(int strength, int speed, int stamina, int magic, int attack,
	int attackDefence, int magicDefence, int evation, int magicEvation, int partyIdx)
{
	tagPlayer player;
	ZeroMemory(&player, sizeof(player));

	player.strength = strength;
	player.speed = speed;
	player.stamina = stamina;
	player.magic = magic;
	player.attack = attack;
	player.attackDefence = attackDefence;
	player.magicDefence = magicDefence;
	player.evation = evation;
	player.magicEvation = magicEvation;
	player.partyIdx = partyIdx;

	_vPlayerStatus.push_back(player);
}

void menu::playerStatusRender()
{
	for (int i = 0; i < _vPlayerStatus.size(); ++i)
	{
		//int -> string 형변환
		char strStrength[INTCHARBUFF];
		sprintf(strStrength, "%d", _vPlayerStatus[i].strength);
		char strSpeed[INTCHARBUFF];
		sprintf(strSpeed, "%d", _vPlayerStatus[i].speed);
		char strStamina[INTCHARBUFF];
		sprintf(strStamina, "%d", _vPlayerStatus[i].stamina);
		char strMagic[INTCHARBUFF];
		sprintf(strMagic, "%d", _vPlayerStatus[i].magic);
		char strAttack[INTCHARBUFF];
		sprintf(strAttack, "%d", _vPlayerStatus[i].attack);
		char strAttackD[INTCHARBUFF];
		sprintf(strAttackD, "%d", _vPlayerStatus[i].attackDefence);
		char strMagicD[INTCHARBUFF];
		sprintf(strMagicD, "%d", _vPlayerStatus[i].magicDefence);
		char strEvation[INTCHARBUFF];
		sprintf(strEvation, "%d", _vPlayerStatus[i].evation);
		char strMagicE[INTCHARBUFF];
		sprintf(strMagicE, "%d", _vPlayerStatus[i].magicEvation);


		//텍스트 출력
		textPrint(getMemDC(), "Strength",		_vPlayer[i].x + 150, _vPlayer[i].y + 30, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"Strength"
		textPrint(getMemDC(), strStrength,		_vPlayer[i].x + 200, _vPlayer[i].y + 30, 15, 15, "HY견고딕", COLOR_BLACK, false);		//힘
		textPrint(getMemDC(), "Speed",			_vPlayer[i].x + 150, _vPlayer[i].y + 50, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"Speed"
		textPrint(getMemDC(), strSpeed,			_vPlayer[i].x + 200, _vPlayer[i].y + 50, 15, 15, "HY견고딕", COLOR_BLACK, false);		//스피드
		textPrint(getMemDC(), "Stamina",		_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"Stamina"
		textPrint(getMemDC(), strStamina,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//내구력
		textPrint(getMemDC(), "Magic",			_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"Magic"
		textPrint(getMemDC(), strMagic,			_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//마법
		textPrint(getMemDC(), "Attack",			_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"Attack"
		textPrint(getMemDC(), strAttack,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//공격력
		textPrint(getMemDC(), "AttackDefence",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"AttackDefence"
		textPrint(getMemDC(), strAttackD,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//공격디펜스
		textPrint(getMemDC(), "MagicDefence",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"MagicDefence"
		textPrint(getMemDC(), strMagicD,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//마법디펜스
		textPrint(getMemDC(), "Evation",		_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"Evation"
		textPrint(getMemDC(), strEvation,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//공격회피
		textPrint(getMemDC(), "MagicEvation",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLUE, false);		//"MagicEvation"
		textPrint(getMemDC(), strMagicE,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY견고딕", COLOR_BLACK, false);		//마법회피
	}

}

void menu::playerStatusRemove()
{
	if (_vPlayerStatus.size() != 0)
	{
		for (int i = 0; i < _vPlayerStatus.size(); ++i)
		{
			_vPlayerStatus.erase(_vPlayer.begin() + i);
		}
	}

	_vPlayerStatus.clear();
}
//-----------------------------  status  ----------------------------- 


//----------------------------  fileLoad  ---------------------------- 
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

		//플레이어 정보담기
		ZeroMemory(&_playerSlot, sizeof(_playerSlot));

		if (playerNumber != -1)  //특정 캐릭터 슬롯 선택시
		{
			wsprintf(playerNum, "player%d", playerNumber);
			i = 0;
		}
		else
		{
			wsprintf(playerNum, "player%d", i);
		}

		wsprintf(_playerSlot.name, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "name"));			//이름
		_playerSlot.img = IMAGEMANAGER->findImage(_playerSlot.name);

		//------------------------------------------- playerNumber 입력 -------------------------------------------
		//if (playerNumber == -1)
		//{
		//	if		(_playerSlot.name == "TINA")	i = 0;
		//	else if (_playerSlot.name == "LOCKE")	i = 1;
		//	else if (_playerSlot.name == "CELES")	i = 2;
		//	else if (_playerSlot.name == "SHADOW")  i = 3;
		//}
		//------------------------------------------- playerNumber 입력 -------------------------------------------
	
		wsprintf(_playerSlot.job, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "job"));			//직업
		_playerSlot.level = INIDATA->loadDataInterger(saveFileNum, playerNum, "level");						//레벨
		if (_playerSlot.level == -1) continue; //예외처리: 정보가 없으면 다음으로...
		_playerSlot.hp = INIDATA->loadDataInterger(saveFileNum, playerNum, "hp");							//체력
		_playerSlot.maxHp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxHp");						//최대 체력
		_playerSlot.mp = INIDATA->loadDataInterger(saveFileNum, playerNum, "mp");							//마력
		_playerSlot.maxMp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxMp");						//최대 마력
		_playerSlot.exp = INIDATA->loadDataInterger(saveFileNum, playerNum, "exp");							//경험치
		_playerSlot.maxExp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxExp");					//최대 경험치

		_playerSlot.strength = INIDATA->loadDataInterger(saveFileNum, playerNum, "strength");				//힘
		_playerSlot.speed = INIDATA->loadDataInterger(saveFileNum, playerNum, "speed");						//스피드
		_playerSlot.stamina = INIDATA->loadDataInterger(saveFileNum, playerNum, "stamina");					//내구력
		_playerSlot.magic = INIDATA->loadDataInterger(saveFileNum, playerNum, "magic");						//마법력
		_playerSlot.attack = INIDATA->loadDataInterger(saveFileNum, playerNum, "attack");					//공격력
		_playerSlot.attackDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "attackDefence");		//공격디펜스
		_playerSlot.magicDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicDefence");       //마법디펜스
		_playerSlot.evation = INIDATA->loadDataInterger(saveFileNum, playerNum, "evation");					//공격회피
		_playerSlot.magicEvation = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicEvation");       //마법회피
		_playerSlot.partyIdx = INIDATA->loadDataInterger(saveFileNum, playerNum, "partyIdx");				//파티원넘버

		//-------------------------------------------- playerSlot 위치 --------------------------------------------
		if (playerNumber != -1)  //특정 캐릭터 슬롯 선택시
		{
			_playerSlot.y = 102;
		}
		else
		{
			_playerSlot.y = 102 + (_playerSlot.partyIdx * 137);
		}
		//-------------------------------------------- playerSlot 위치 --------------------------------------------


		//플레이어 슬롯 출력정보 담기
		playerSlotInit(_playerSlot.name, 65, _playerSlot.y, _playerSlot.level, _playerSlot.job, _playerSlot.hp,
			_playerSlot.maxHp, _playerSlot.mp, _playerSlot.maxMp, _playerSlot.exp, _playerSlot.maxExp, _playerSlot.partyIdx);

		//플레이어 상태 출력정보 담기
		playerStatusInit(_playerSlot.strength, _playerSlot.speed, _playerSlot.stamina, _playerSlot.magic, _playerSlot.attack,
			_playerSlot.attackDefence, _playerSlot.magicDefence, _playerSlot.evation, _playerSlot.magicEvation, _playerSlot.partyIdx);

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


void menu::saveIniPlayerData(int fileNum, int playerNum, string cName, string job, int level, int hp, int maxHp, int mp, int maxMp,
	int exp, int maxExp, int strength, int speed, int stamina, int magic, int attack, int attackDefence, int magicDefence, int evation,
	int magicEvation, int partyIdx, string myWeapon, string myArmor, string myHelmet, string mySubWeapon, bool tmpSave, bool saveFile)
{
	//템프파일 저장시
	int saveNum;
	if (tmpSave)
	{
		saveNum = 2;
	}
	else
	{
		saveNum = 1;
	}

	//파일정보 넘버
	TCHAR tmp[4];
	ZeroMemory(&tmp, sizeof(tmp));
	wsprintf(tmp, "%d", fileNum);
	INIDATA->addData("fileInfo", "fileNum",  tmp);

	for (int i = 0; i < saveNum; ++i)
	{
		//플레이어 넘버
		TCHAR subjectNum[12];
		ZeroMemory(&subjectNum, sizeof(subjectNum));
		wsprintf(subjectNum, "player%d", playerNum);
		//플레이어 이름 & 직업
		INIDATA->addData(subjectNum, "name", cName.c_str());
		INIDATA->addData(subjectNum, "job", job.c_str());
		//플레이어 레벨
		TCHAR tmp1[4];
		ZeroMemory(&tmp1, sizeof(tmp1));
		wsprintf(tmp1, "%d", level);
		INIDATA->addData(subjectNum, "level", tmp1);
		//플레이어 체력
		TCHAR tmp2[4];
		ZeroMemory(&tmp2, sizeof(tmp2));
		wsprintf(tmp2, "%d", hp);
		INIDATA->addData(subjectNum, "hp", tmp2);
		//플레이어 최대체력
		TCHAR tmp3[4];
		ZeroMemory(&tmp3, sizeof(tmp3));
		wsprintf(tmp3, "%d", maxHp);
		INIDATA->addData(subjectNum, "maxHp", tmp3);
		//플레이어 마력
		TCHAR tmp4[4];
		ZeroMemory(&tmp4, sizeof(tmp4));
		wsprintf(tmp4, "%d", mp);
		INIDATA->addData(subjectNum, "mp", tmp4);
		//플레이어 최대마력
		TCHAR tmp5[4];
		ZeroMemory(&tmp5, sizeof(tmp5));
		wsprintf(tmp5, "%d", maxMp);
		INIDATA->addData(subjectNum, "maxMp", tmp5);
		//플레이어 경험치
		TCHAR tmp6[4];
		ZeroMemory(&tmp6, sizeof(tmp6));
		wsprintf(tmp6, "%d", exp);
		INIDATA->addData(subjectNum, "exp", tmp6);
		//플레이어 최대경험치
		TCHAR tmp7[4];
		ZeroMemory(&tmp7, sizeof(tmp7));
		wsprintf(tmp7, "%d", maxExp);
		INIDATA->addData(subjectNum, "maxExp", tmp7);
		//플레이어 힘
		TCHAR tmp8[4];
		ZeroMemory(&tmp8, sizeof(tmp8));
		wsprintf(tmp8, "%d", strength);
		INIDATA->addData(subjectNum, "strength", tmp8);
		//플레이어 스피드
		TCHAR tmp9[4];
		ZeroMemory(&tmp9, sizeof(tmp9));
		wsprintf(tmp9, "%d", speed);
		INIDATA->addData(subjectNum, "speed", tmp9);
		//플레이어 내구력
		TCHAR tmp10[4];
		ZeroMemory(&tmp10, sizeof(tmp10));
		wsprintf(tmp10, "%d", stamina);
		INIDATA->addData(subjectNum, "stamina", tmp10);
		//플레이어 마법
		TCHAR tmp11[4];
		ZeroMemory(&tmp11, sizeof(tmp11));
		wsprintf(tmp11, "%d", magic);
		INIDATA->addData(subjectNum, "magic", tmp11);
		//플레이어 공격력
		TCHAR tmp12[4];
		ZeroMemory(&tmp12, sizeof(tmp12));
		wsprintf(tmp12, "%d", attack);
		INIDATA->addData(subjectNum, "attack", tmp12);
		//플레이어 공격방어력
		TCHAR tmp13[4];
		ZeroMemory(&tmp13, sizeof(tmp13));
		wsprintf(tmp13, "%d", attackDefence);
		INIDATA->addData(subjectNum, "attackDefence", tmp13);
		//플레이어 마법방어력
		TCHAR tmp14[4];
		ZeroMemory(&tmp14, sizeof(tmp14));
		wsprintf(tmp14, "%d", magicDefence);
		INIDATA->addData(subjectNum, "magicDefence", tmp14);
		//플레이어 공격회피
		TCHAR tmp15[4];
		ZeroMemory(&tmp15, sizeof(tmp15));
		wsprintf(tmp15, "%d", evation);
		INIDATA->addData(subjectNum, "evation", tmp15);
		//플레이어 마법회피
		TCHAR tmp16[4];
		ZeroMemory(&tmp16, sizeof(tmp16));
		wsprintf(tmp16, "%d", magicEvation);
		INIDATA->addData(subjectNum, "magicEvation", tmp16);
		//플레이어 파티원 넘버
		TCHAR tmp17[4];
		ZeroMemory(&tmp17, sizeof(tmp17));
		wsprintf(tmp17, "%d", partyIdx);
		INIDATA->addData(subjectNum, "partyIdx", tmp17);
		//플레이어 무기
		INIDATA->addData(subjectNum, "myWeapon", myWeapon.c_str());
		//플레이어 아머
		INIDATA->addData(subjectNum, "myArmor", myArmor.c_str());
		//플레이어 헬멧
		INIDATA->addData(subjectNum, "myHelmet", myHelmet.c_str());
		//플레이어 서브무기
		INIDATA->addData(subjectNum, "mySubWeapon", mySubWeapon.c_str());

		if (i == 0)
		{
			if (!saveFile)
			{
				//파일저장: saveFile
				TCHAR saveFileName[16];
				wsprintf(saveFileName, "saveFile%d", fileNum);
				INIDATA->iniSave(saveFileName);
			}
		}
		if (i == 1)
		{
			//파일저장: tmpFile
			INIDATA->iniSave("skgFile");
		}
	}
}

void menu::saveIniSlotGameData(int fileNum, string stage, int gil, int playTime, bool tmpSave)
{
	int saveFileNum;
	if (tmpSave)
	{
		saveFileNum = 2;
	}
	else
	{
		saveFileNum = 1;
	}

	for (int i = 0; i < saveFileNum; ++i)
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


		//파일저장
		if (i == 0)
		{
			TCHAR saveFileName[16];
			wsprintf(saveFileName, "saveFile%d", fileNum);
			INIDATA->iniSave(saveFileName);
		}
		if (i == 1)
		{
			INIDATA->iniSave("skgFile");
		}

	}
}

void menu::fileCopyTmpFile(int fileNum)
{
	//플레이어 정보로드
	tagSaveData tmpPlayrInfo;

	for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&tmpPlayrInfo, sizeof(tmpPlayrInfo));
		tmpPlayrInfo = loadIniPlayerData(fileNum, i);

		saveIniPlayerData(tmpPlayrInfo.fileNum, i, tmpPlayrInfo.playerInfo.name, tmpPlayrInfo.playerInfo.job, tmpPlayrInfo.playerInfo.level,
			tmpPlayrInfo.playerInfo.hp, tmpPlayrInfo.playerInfo.maxHp, tmpPlayrInfo.playerInfo.mp, tmpPlayrInfo.playerInfo.maxMp,
			tmpPlayrInfo.playerInfo.exp, tmpPlayrInfo.playerInfo.maxExp, tmpPlayrInfo.playerInfo.strength, tmpPlayrInfo.playerInfo.speed,
			tmpPlayrInfo.playerInfo.stamina, tmpPlayrInfo.playerInfo.magic, tmpPlayrInfo.playerInfo.attack, tmpPlayrInfo.playerInfo.attackDefence,
			tmpPlayrInfo.playerInfo.magicDefence, tmpPlayrInfo.playerInfo.evation, tmpPlayrInfo.playerInfo.magicEvation, tmpPlayrInfo.playerInfo.partyIdx,
			tmpPlayrInfo.playerInfo.weapon, tmpPlayrInfo.playerInfo.armor, tmpPlayrInfo.playerInfo.helmet, tmpPlayrInfo.playerInfo.subWeapon,
			true, true);

		INIDATA->iniSave("skgFile");

		if (i == 3)
		{
			char tmpGil[16];
			ZeroMemory(&tmpGil, sizeof(tmpGil));
			sprintf(tmpGil, "%d", tmpPlayrInfo.gil);

			char tmpTime[16];
			ZeroMemory(&tmpTime, sizeof(tmpTime));
			sprintf(tmpTime, "%d", tmpPlayrInfo.playTime);

			INIDATA->addData("gameData", "stage", tmpPlayrInfo.stage);
			INIDATA->addData("gameData", "gil", tmpGil);
			INIDATA->addData("gameData", "playTime", tmpTime);

			INIDATA->iniSave("skgFile");
		}
	}
}

tagSaveData menu::loadIniPlayerData(int fileNum, int playerNumber)
{
	//세이브파일 넘버
	char saveFileNum[32];
	ZeroMemory(&saveFileNum, sizeof(saveFileNum));
	wsprintf(saveFileNum, "saveFile%d", fileNum);

	//플레이어 번호 담을 변수
	char playerNum[16];
	ZeroMemory(&playerNum, sizeof(playerNum));
	wsprintf(playerNum, "player%d", playerNumber);

	//플레이어 정보로드
	tagSaveData tmpPlayrInfo;
	ZeroMemory(&tmpPlayrInfo, sizeof(tmpPlayrInfo));

	tmpPlayrInfo.fileNum = INIDATA->loadDataInterger(saveFileNum, "fileInfo", "fileNum");                               //파일넘버   
	
	wsprintf(tmpPlayrInfo.playerInfo.name, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "name"));				//이름
	wsprintf(tmpPlayrInfo.playerInfo.job, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "job"));				//직업
	tmpPlayrInfo.playerInfo.level = INIDATA->loadDataInterger(saveFileNum, playerNum, "level");							//레벨   
	tmpPlayrInfo.playerInfo.hp = INIDATA->loadDataInterger(saveFileNum, playerNum, "hp");								//체력     
	tmpPlayrInfo.playerInfo.maxHp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxHp");							//최대체력         
	tmpPlayrInfo.playerInfo.mp = INIDATA->loadDataInterger(saveFileNum, playerNum, "mp");								//마력    
	tmpPlayrInfo.playerInfo.maxMp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxMp");							//최대마력             
	tmpPlayrInfo.playerInfo.exp = INIDATA->loadDataInterger(saveFileNum, playerNum, "exp");								//경험치        
	tmpPlayrInfo.playerInfo.maxExp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxExp");						//다음레벨 경험치         
	tmpPlayrInfo.playerInfo.strength = INIDATA->loadDataInterger(saveFileNum, playerNum, "strength");					//힘             
	tmpPlayrInfo.playerInfo.speed = INIDATA->loadDataInterger(saveFileNum, playerNum, "speed");							//스피드      
	tmpPlayrInfo.playerInfo.stamina = INIDATA->loadDataInterger(saveFileNum, playerNum, "stamina");						//내구력         
	tmpPlayrInfo.playerInfo.magic = INIDATA->loadDataInterger(saveFileNum, playerNum, "magic");							//마법력    
	tmpPlayrInfo.playerInfo.attack = INIDATA->loadDataInterger(saveFileNum, playerNum, "attack");						//공격력            
	tmpPlayrInfo.playerInfo.attackDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "attackDefence");			//공격방어력               
	tmpPlayrInfo.playerInfo.magicDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicDefence");			//마법방어력       
	tmpPlayrInfo.playerInfo.evation = INIDATA->loadDataInterger(saveFileNum, playerNum, "evation");						//공격회피           
	tmpPlayrInfo.playerInfo.magicEvation = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicEvation");			//마법회피               
	tmpPlayrInfo.playerInfo.partyIdx = INIDATA->loadDataInterger(saveFileNum, playerNum, "partyIdx");					//파티원넘버
	wsprintf(tmpPlayrInfo.playerInfo.weapon, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myWeapon"));		//무기
	wsprintf(tmpPlayrInfo.playerInfo.armor, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myArmor"));			//갑옷 
	wsprintf(tmpPlayrInfo.playerInfo.helmet, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myHelmet"));		//투구  
	wsprintf(tmpPlayrInfo.playerInfo.subWeapon, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "mySubWeapon"));	//보조무기 

	wsprintf(tmpPlayrInfo.stage, "%s", INIDATA->loadDataString(saveFileNum, "gameData", "stage"));                      //스테이지  
	tmpPlayrInfo.gil = INIDATA->loadDataInterger(saveFileNum, "gameData", "gil");										//돈  
	tmpPlayrInfo.playTime = INIDATA->loadDataInterger(saveFileNum, "gameData", "playTime");								//플레이시간  

	return tmpPlayrInfo;
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

	//현재 플레이어 위치
	if (currentScene != "") INIDATA->addData("gameData", "currentScene", currentScene.c_str());

	//게임스타트 불값 초기화
	INIDATA->addData("gameData", "gameStart", "0");

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
		textPrint(getMemDC(), itoa(tmpGD.gil, tmpBuff, 10),    1080, 516, 20, 20, "Stencil", COLOR_WHITE, true);
	}
}

//============================== gameData ============================

