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

//                     Ŀ������(L,R)     Ŀ����ġX     Ŀ����ġY
void  menu::cursorInit(CURSOR_TYPE type, float startX, float startY)
{
	_cursorType = type;

	_cursor.img = IMAGEMANAGER->findImage("����Ŀ��");
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
			//ó�� ��ġ��
			if (_cursor.x > _cursor.startX)
			{
				_cursor.x = _cursor.startX;
				_cursor.fForce = 0.01f;
				_cursor.speed = 1.0f;
			}
			
			//Ŀ�� ������
			_cursor.fForce += 0.001f;
			_cursor.speed -= _cursor.fForce;
			_cursor.x -= _cursor.speed;
		break;
		case CUSOR_RIGHT:
			//ó�� ��ġ��
			if (_cursor.x < _cursor.startX)
			{
				_cursor.x = _cursor.startX;
				_cursor.fForce = 0.01f;
				_cursor.speed = 1.0f;
			}

			//Ŀ�� ������
			_cursor.fForce += 0.001f;
			_cursor.speed -= _cursor.fForce;
			_cursor.x += _cursor.speed;
		break;
	}
}

//                           Ŀ��X�� �̵���    �̵�Ƚ��
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

		//����ó��: Ŀ���� �����׸��� ����� �ٽ� ó�� ��������~~
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

		//����ó��: Ŀ���� �����׸��� ����� ������ ��������~~
		if (_cursor.x < _cursor.minX)
		{
			_cursor.x = _cursor.maxX;
			_cursor.startX = _cursor.maxX;
			_cursor.currentXNum = (moveNumber - 1);
		}
	}


	//����ó��: Ŀ�� ������ġ ��ȯ�� ����...
	if (_cursor.currentXNum <= 0)					_cursor.currentXNum = 0;
	if (_cursor.currentXNum >= (moveNumber))		_cursor.currentXNum = (moveNumber - 1);
}

//                          Ŀ��Y�� �̵���    �̵�Ƚ��
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

		//����ó��: Ŀ���� �����׸��� ����� �ٽ� ó�� ��������~~
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

		//����ó��: Ŀ���� �����׸��� ����� ������ ��������~~
		if (_cursor.y < _cursor.startY)
		{
			_cursor.y = _cursor.startY + (moveValueY * (downNumber - 1));
			_cursor.currentYNum = downNumber - 1;
		}
	}


	//����ó��: Ŀ�� ������ġ ��ȯ�� ����...
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
//slot                    �̹���Ű��      �̹�����ġXY      ����	   ����	       ü��    �ִ�ü��   ����    �ִ븶��
void menu::playerSlotInit(string keyName, float x, float y, int level, char* job, int hp, int maxHp, int mp, int maxMp, int exp, int maxExp)
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
		//�̹��� ���
		_vPlayer[i].img->render(getMemDC(), _vPlayer[i].x, _vPlayer[i].y);

		//int -> string ����ȯ
		char strLevel[INTCHARBUFF];
		sprintf(strLevel, "%d", _vPlayer[i].level);	
		char strHp[INTCHARBUFF];
		sprintf(strHp, "%d / %d", _vPlayer[i].hp, _vPlayer[i].maxHp);
		char strMp[INTCHARBUFF];
		sprintf(strMp, "%d / %d", _vPlayer[i].mp, _vPlayer[i].maxMp);

		//�ؽ�Ʈ ���
		textPrint(getMemDC(), _vPlayer[i].name, _vPlayer[i].x + 150, _vPlayer[i].y,      30, 30, "Stencil",  COLOR_BLACK, false);	//�̸�
		textPrint(getMemDC(), _vPlayer[i].job,  _vPlayer[i].x + 300, _vPlayer[i].y,      25, 25, "Roboto",  COLOR_BLACK, false);	//����
		textPrint(getMemDC(), "LV",			    _vPlayer[i].x + 150, _vPlayer[i].y + 30, 15, 15, "HY�߰��", COLOR_BLUE,  false);	//"LV"
		textPrint(getMemDC(), strLevel,         _vPlayer[i].x + 200, _vPlayer[i].y + 30, 15, 15, "HY�߰��", COLOR_BLACK, false);	//����
		textPrint(getMemDC(), "HP",				_vPlayer[i].x + 150, _vPlayer[i].y + 50, 15, 15, "HY�߰��", COLOR_BLUE, false);	//"HP"
		textPrint(getMemDC(), strHp,			_vPlayer[i].x + 200, _vPlayer[i].y + 50, 15, 15, "HY�߰��", COLOR_BLACK, false);	//ü��
		if (_vPlayer[i].mp == -1) continue;  //����ó��: MP�� ������ �ǳʶ��
		textPrint(getMemDC(), "MP",				_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);	//"MP"
		textPrint(getMemDC(), strMp,			_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);	//����

		//textPrint(getMemDC(), "MP",				_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);	//"exp"
		//textPrint(getMemDC(), strMp,				_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);	//����ġ
		//textPrint(getMemDC(), "for Next Level",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);	//"������ ���� ����ġ"
		//textPrint(getMemDC(), strMp,				_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);	//�������� ����ġ - ���� ����ġ
	}

	if (_vPlayer.size() == 0)
	{
		textPrint(getMemDC(), "EMPTY", 440, 140, 30, 30, "HY�߰��", COLOR_BLACK);
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
		//int -> string ����ȯ
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


		//�ؽ�Ʈ ���
		textPrint(getMemDC(), "Strength",		_vPlayer[i].x + 150, _vPlayer[i].y + 30, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Strength"
		textPrint(getMemDC(), strStrength,		_vPlayer[i].x + 200, _vPlayer[i].y + 30, 15, 15, "HY�߰��", COLOR_BLACK, false);		//��
		textPrint(getMemDC(), "Speed",			_vPlayer[i].x + 150, _vPlayer[i].y + 50, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Speed"
		textPrint(getMemDC(), strSpeed,			_vPlayer[i].x + 200, _vPlayer[i].y + 50, 15, 15, "HY�߰��", COLOR_BLACK, false);		//���ǵ�
		textPrint(getMemDC(), "Stamina",		_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Stamina"
		textPrint(getMemDC(), strStamina,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//������
		textPrint(getMemDC(), "Magic",			_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Magic"
		textPrint(getMemDC(), strMagic,			_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//����
		textPrint(getMemDC(), "Attack",			_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Attack"
		textPrint(getMemDC(), strAttack,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//���ݷ�
		textPrint(getMemDC(), "AttackDefence",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"AttackDefence"
		textPrint(getMemDC(), strAttackD,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//���ݵ��潺
		textPrint(getMemDC(), "MagicDefence",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"MagicDefence"
		textPrint(getMemDC(), strMagicD,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//�������潺
		textPrint(getMemDC(), "Evation",		_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Evation"
		textPrint(getMemDC(), strEvation,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//����ȸ��
		textPrint(getMemDC(), "MagicEvation",	_vPlayer[i].x + 150, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"MagicEvation"
		textPrint(getMemDC(), strMagicE,		_vPlayer[i].x + 200, _vPlayer[i].y + 70, 15, 15, "HY�߰��", COLOR_BLACK, false);		//����ȸ��
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
//�÷��̾� ���̺� ���� �ε�      ���÷��̾� ���Գѹ�(Ư�� ĳ���� ���� �ϳ��� �����)
void menu::fileLoad(int fileNum, int playerNumber)
{
	//���� �ʱ�ȭ
	playerSlotRemove();
	if (!_fileLoadOk[fileNum]) _selectFileCount = 2;  //��ư���� �ʱ�ȭ

	//���̺����� �ѹ�
	char saveFileNum[32];
	ZeroMemory(&saveFileNum, sizeof(saveFileNum));
	wsprintf(saveFileNum, "saveFile%d", fileNum);


	for (int i = 0; i < 4; ++i)
	{
		//�÷��̾� ��ȣ ���� ����
		char playerNum[16];
		ZeroMemory(&playerNum, sizeof(playerNum));

		if (playerNumber != -1)  //Ư�� ĳ���� ���� ���ý�
		{
			wsprintf(playerNum, "player%d", playerNumber);
			i = 0;
		}
		else
		{
			wsprintf(playerNum, "player%d", i);
		}

		//�÷��̾� �������
		ZeroMemory(&_playerSlot, sizeof(_playerSlot));

		wsprintf(_playerSlot.name, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "name"));			//�̸�
		_playerSlot.img = IMAGEMANAGER->findImage(_playerSlot.name);
		wsprintf(_playerSlot.job, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "job"));			//����
		_playerSlot.level = INIDATA->loadDataInterger(saveFileNum, playerNum, "level");						//����
		if (_playerSlot.level == -1) continue; //����ó��: ������ ������ ��������...
		_playerSlot.hp = INIDATA->loadDataInterger(saveFileNum, playerNum, "hp");							//ü��
		_playerSlot.maxHp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxHp");						//�ִ� ü��
		_playerSlot.mp = INIDATA->loadDataInterger(saveFileNum, playerNum, "mp");							//����
		_playerSlot.maxMp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxMp");						//�ִ� ����
		_playerSlot.exp = INIDATA->loadDataInterger(saveFileNum, playerNum, "exp");							//����ġ
		_playerSlot.maxExp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxExp");					//�ִ� ����ġ

		_playerSlot.strength = INIDATA->loadDataInterger(saveFileNum, playerNum, "strength");				//��
		_playerSlot.speed = INIDATA->loadDataInterger(saveFileNum, playerNum, "speed");						//���ǵ�
		_playerSlot.stamina = INIDATA->loadDataInterger(saveFileNum, playerNum, "stamina");					//������
		_playerSlot.magic = INIDATA->loadDataInterger(saveFileNum, playerNum, "magic");						//������
		_playerSlot.attack = INIDATA->loadDataInterger(saveFileNum, playerNum, "attack");					//���ݷ�
		_playerSlot.attackDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "attackDefence");		//���ݵ��潺
		_playerSlot.magicDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicDefence");       //�������潺
		_playerSlot.evation = INIDATA->loadDataInterger(saveFileNum, playerNum, "evation");					//����ȸ��
		_playerSlot.magicEvation = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicEvation");       //����ȸ��
		_playerSlot.partyIdx = INIDATA->loadDataInterger(saveFileNum, playerNum, "partyIdx");				//��Ƽ���ѹ�



		//�÷��̾� ���� ������� ���
		playerSlotInit(_playerSlot.name, 65, 102 + (i * 137), _playerSlot.level, _playerSlot.job, _playerSlot.hp,
			_playerSlot.maxHp, _playerSlot.mp, _playerSlot.maxMp, _playerSlot.exp, _playerSlot.maxExp);

		//�÷��̾� ���� ������� ���
		playerStatusInit(_playerSlot.strength, _playerSlot.speed, _playerSlot.stamina, _playerSlot.magic, _playerSlot.attack,
			_playerSlot.attackDefence, _playerSlot.magicDefence, _playerSlot.evation, _playerSlot.magicEvation, _playerSlot.partyIdx);

		//������ ���������...
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
	int magicEvation, int partyIdx, string myWeapon, bool tmpSave)
{
	//�������� �����
	int saveNum;
	if (tmpSave)
	{
		saveNum = 2;
	}
	else
	{
		saveNum = 1;
	}

	//�������� �ѹ�
	TCHAR tmp[4];
	ZeroMemory(&tmp, sizeof(tmp));
	wsprintf(tmp, "%d", fileNum);
	INIDATA->addData("fileInfo", "fileNum",  tmp);

	for (int i = 0; i < saveNum; ++i)
	{
		//�÷��̾� �ѹ�
		TCHAR subjectNum[12];
		ZeroMemory(&subjectNum, sizeof(subjectNum));
		wsprintf(subjectNum, "player%d", playerNum);
		//�÷��̾� �̸� & ����
		INIDATA->addData(subjectNum, "name", cName.c_str());
		INIDATA->addData(subjectNum, "job", job.c_str());
		//�÷��̾� ����
		TCHAR tmp1[4];
		ZeroMemory(&tmp1, sizeof(tmp1));
		wsprintf(tmp1, "%d", level);
		INIDATA->addData(subjectNum, "level", tmp1);
		//�÷��̾� ü��
		TCHAR tmp2[4];
		ZeroMemory(&tmp2, sizeof(tmp2));
		wsprintf(tmp2, "%d", hp);
		INIDATA->addData(subjectNum, "hp", tmp2);
		//�÷��̾� �ִ�ü��
		TCHAR tmp3[4];
		ZeroMemory(&tmp3, sizeof(tmp3));
		wsprintf(tmp3, "%d", maxHp);
		INIDATA->addData(subjectNum, "maxHp", tmp3);
		//�÷��̾� ����
		TCHAR tmp4[4];
		ZeroMemory(&tmp4, sizeof(tmp4));
		wsprintf(tmp4, "%d", mp);
		INIDATA->addData(subjectNum, "mp", tmp4);
		//�÷��̾� �ִ븶��
		TCHAR tmp5[4];
		ZeroMemory(&tmp5, sizeof(tmp5));
		wsprintf(tmp5, "%d", maxMp);
		INIDATA->addData(subjectNum, "maxMp", tmp5);
		//�÷��̾� ����ġ
		TCHAR tmp6[4];
		ZeroMemory(&tmp6, sizeof(tmp6));
		wsprintf(tmp6, "%d", exp);
		INIDATA->addData(subjectNum, "exp", tmp6);
		//�÷��̾� �ִ����ġ
		TCHAR tmp7[4];
		ZeroMemory(&tmp7, sizeof(tmp7));
		wsprintf(tmp7, "%d", maxExp);
		INIDATA->addData(subjectNum, "maxExp", tmp7);
		//�÷��̾� ��
		TCHAR tmp8[4];
		ZeroMemory(&tmp8, sizeof(tmp8));
		wsprintf(tmp8, "%d", strength);
		INIDATA->addData(subjectNum, "strength", tmp8);
		//�÷��̾� ���ǵ�
		TCHAR tmp9[4];
		ZeroMemory(&tmp9, sizeof(tmp9));
		wsprintf(tmp9, "%d", speed);
		INIDATA->addData(subjectNum, "speed", tmp9);
		//�÷��̾� ������
		TCHAR tmp10[4];
		ZeroMemory(&tmp10, sizeof(tmp10));
		wsprintf(tmp10, "%d", stamina);
		INIDATA->addData(subjectNum, "stamina", tmp10);
		//�÷��̾� ����
		TCHAR tmp11[4];
		ZeroMemory(&tmp11, sizeof(tmp11));
		wsprintf(tmp11, "%d", magic);
		INIDATA->addData(subjectNum, "magic", tmp11);
		//�÷��̾� ���ݷ�
		TCHAR tmp12[4];
		ZeroMemory(&tmp12, sizeof(tmp12));
		wsprintf(tmp12, "%d", attack);
		INIDATA->addData(subjectNum, "attack", tmp12);
		//�÷��̾� ���ݹ���
		TCHAR tmp13[4];
		ZeroMemory(&tmp13, sizeof(tmp13));
		wsprintf(tmp13, "%d", attackDefence);
		INIDATA->addData(subjectNum, "attackDefence", tmp13);
		//�÷��̾� ��������
		TCHAR tmp14[4];
		ZeroMemory(&tmp14, sizeof(tmp14));
		wsprintf(tmp14, "%d", magicDefence);
		INIDATA->addData(subjectNum, "magicDefence", tmp14);
		//�÷��̾� ����ȸ��
		TCHAR tmp15[4];
		ZeroMemory(&tmp15, sizeof(tmp15));
		wsprintf(tmp15, "%d", evation);
		INIDATA->addData(subjectNum, "evation", tmp15);
		//�÷��̾� ����ȸ��
		TCHAR tmp16[4];
		ZeroMemory(&tmp16, sizeof(tmp16));
		wsprintf(tmp16, "%d", magicEvation);
		INIDATA->addData(subjectNum, "magicEvation", tmp16);
		//�÷��̾� ��Ƽ�� �ѹ�
		TCHAR tmp17[4];
		ZeroMemory(&tmp17, sizeof(tmp17));
		wsprintf(tmp17, "%d", partyIdx);
		INIDATA->addData(subjectNum, "partyIdx", tmp17);
		//�÷��̾� ��ų
		INIDATA->addData(subjectNum, "myWeapon", myWeapon.c_str());

		if (i == 0)
		{
			//��������: saveFile
			TCHAR saveFileName[16];
			wsprintf(saveFileName, "saveFile%d", fileNum);
			INIDATA->iniSave(saveFileName);
		}
		if (i == 1)
		{
			//��������: tmpFile
			INIDATA->iniSave("skgFile");
		}
	}
}

void menu::saveIniSlotGameData(int fileNum, string stage, int gil, int playTime)
{
	//��������
	INIDATA->addData("gameData", "stage", stage.c_str());
	//�÷��̾� ��
	TCHAR tmp2[8];
	ZeroMemory(&tmp2, sizeof(tmp2));
	wsprintf(tmp2, "%d", gil);
	INIDATA->addData("gameData", "gil", tmp2);
	//�÷��� �ð�
	TCHAR tmp3[32];
	ZeroMemory(&tmp3, sizeof(tmp3));
	wsprintf(tmp3, "%d", playTime);
	INIDATA->addData("gameData", "playTime", tmp3);


	//��������
	TCHAR saveFileName[16];
	wsprintf(saveFileName, "saveFile%d", fileNum);
	INIDATA->iniSave(saveFileName);
}

//============================ save & load ===========================


//============================== gameData ============================

void menu::saveIniGameData(int fileNum, string currentScene)
{
	//���̺� ���ϳѹ�
	TCHAR tmp1[8];
	ZeroMemory(&tmp1, sizeof(tmp1));
	wsprintf(tmp1, "%d", fileNum);
	INIDATA->addData("gameData", "fileNum", tmp1);

	//���������̸�
	TCHAR saveFileName[16];
	wsprintf(saveFileName, "saveFile%d", fileNum);;
	INIDATA->addData("gameData", "saveFileName", saveFileName);

	//���� �÷��̾� ��ġ
	if (currentScene != "") INIDATA->addData("gameData", "currentScene", currentScene.c_str());

	//���ӽ�ŸƮ �Ұ� �ʱ�ȭ
	INIDATA->addData("gameData", "gameStart", "0");

	//��������
	INIDATA->iniSave("gameData");
}

void menu::gameDataRender(bool isNewGame)
{
	//���� ������ ���̺����� ���� �ε�
	tagCurrentGameData tmpGD;  
	wsprintf(tmpGD.saveFileName, "%s", INIDATA->loadDataString("gameData", "gameData", "saveFileName"));

	wsprintf(tmpGD.stage, "%s", INIDATA->loadDataString(tmpGD.saveFileName, "gameData", "stage"));
	tmpGD.playTime = INIDATA->loadDataInterger(tmpGD.saveFileName, "gameData", "playTime");
	tmpGD.gil = INIDATA->loadDataInterger(tmpGD.saveFileName, "gameData", "gil");

	
	if (isNewGame)
	{
		//NEWGAME: �ش������� ������ ù��° ���Ϻ��� Ž���ؼ� �ε�
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
    

	//�ؽ�Ʈ ���
	if (tmpGD.playTime != -1)
	{
		char tmpBuff[32];
		textPrint(getMemDC(), tmpGD.stage,					     1050, 392, 30, 30, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.playTime, tmpBuff, 10), 1080, 462, 20, 20, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.gil, tmpBuff, 10),    1080, 516, 20, 20, "Stencil", COLOR_WHITE, true);
	}
}

//============================== gameData ============================