#include "stdafx.h"
#include "menu.h"
#include "itemManager.h"

menu::menu()
{
	_slotNum = 0;

}
menu::~menu()
{
}


HRESULT menu::init()
{
	//���̺�����Ʈ ���޽�
	_isSavePoint = false;

	//����
	SOUNDMANAGER->addSound("battleMenuOpen", ".\\sound\\sfx\\battleMenuOpen.wav", false, false);
	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);

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
		if (!leftMove)
		{
			if (_cursor.x < _cursor.minX)
			{
				_cursor.x = _cursor.maxX;
				_cursor.startX = _cursor.maxX;
				_cursor.currentXNum = (moveNumber - 1);
			}
		}
		else
		{
			if (_cursor.currentXNum < 0)
			{
				_cursor.x = _cursor.minX;
				_cursor.startX = _cursor.minX;
				_cursor.currentXNum = (moveNumber - 1);
			}
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

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		char tmp[4];
		ZeroMemory(&tmp, sizeof(tmp));
		TextOut(getMemDC(), _cursor.x - 20, _cursor.y - 30, itoa(_cursor.x, tmp, 10), sizeof(tmp));
		TextOut(getMemDC(), _cursor.x + 20, _cursor.y - 30, itoa(_cursor.y, tmp, 10), sizeof(tmp));
		TextOut(getMemDC(), _cursor.x, _cursor.y + 30, itoa(_cursor.currentXNum, tmp, 10), sizeof(tmp));
	}
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
void menu::playerSlotInit(string keyName, float x, float y, int level, char* job, int hp, int maxHp, int mp, int maxMp, int exp, int maxExp, int partyIdx)
{
	tagPlayer player;
	ZeroMemory(&player, sizeof(player));

	//-------------------------------------------- animationKeyName
	char aniTemp[32];
	ZeroMemory(&aniTemp, sizeof(aniTemp));
	sprintf(aniTemp, "%s%d", "���Խ���", partyIdx);
	//--------------------------------------------

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

	//���ϸ��̼�
	player.ani = new animation;
	int arrAniSlot[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation(aniTemp, player.name, arrAniSlot, 2, 1, true);
	player.ani = KEYANIMANAGER->findAnimation(aniTemp);

	//���Ժ���
	player.slotSelect = false;

	_vPlayer.push_back(player);

	_slotNum++;

}

void menu::playerSlotUpdate()
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		if (_vPlayer[i].aniStart)
		{
			if (!_vPlayer[i].ani->isPlay()) _vPlayer[i].ani->start();
		}
		else
		{
			if (_vPlayer[i].ani->isPlay()) _vPlayer[i].ani->stop();
		}
	}

	KEYANIMANAGER->update();
}

void menu::playerSlotKeyControl(float slotValueY, int slotNum)
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		//����ó��
		if (slotNum < 0 || slotNum > 3) continue;

		_vPlayer[i].y += slotValueY * slotNum;
		_vPlayer[i].partyIdx = slotNum;
	}
}

void menu::playerSlotRender()	 
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		//�̹��� ���
		_vPlayer[i].img->aniRender(getMemDC(), _vPlayer[i].x, _vPlayer[i].y, _vPlayer[i].ani);

		//int -> string ����ȯ
		char strLevel[INTCHARBUFF];
		sprintf(strLevel, "%d", _vPlayer[i].level);	
		char strHp[INTCHARBUFF];
		sprintf(strHp, "%d / %d", _vPlayer[i].hp, _vPlayer[i].maxHp);
		char strMp[INTCHARBUFF];
		sprintf(strMp, "%d / %d", _vPlayer[i].mp, _vPlayer[i].maxMp);
		char strExp[INTCHARBUFF];
		sprintf(strExp, "%d / %d", _vPlayer[i].exp, _vPlayer[i].exp);
		//������������ ���� ����ġ ���
		char strNextExp[INTCHARBUFF];
		sprintf(strNextExp, "%d", (maxExpValue[_vPlayer[i].level + 1] - _vPlayer[i].exp));

		//�ؽ�Ʈ ���
		textPrint(getMemDC(), _vPlayer[i].name,	 _vPlayer[i].x + 150, _vPlayer[i].y - 10, 30, 30, "Stencil",  COLOR_BLACK, false);		//�̸�
		textPrint(getMemDC(), _vPlayer[i].job,	 _vPlayer[i].x + 300, _vPlayer[i].y - 10, 25, 25, "Roboto",  COLOR_BLACK, false);		//����
		textPrint(getMemDC(), "LV",				 _vPlayer[i].x + 150, _vPlayer[i].y + 20, 15, 15, "HY�߰��", COLOR_BLUE,  false);		//"LV"
		textPrint(getMemDC(), strLevel,			 _vPlayer[i].x + 200, _vPlayer[i].y + 20, 15, 15, "HY�߰��", COLOR_BLACK, false);		//����
		textPrint(getMemDC(), "HP",				 _vPlayer[i].x + 150, _vPlayer[i].y + 40, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"HP"
		textPrint(getMemDC(), strHp,			 _vPlayer[i].x + 200, _vPlayer[i].y + 40, 15, 15, "HY�߰��", COLOR_BLACK, false);		//ü��
		textPrint(getMemDC(), "MP",				 _vPlayer[i].x + 150, _vPlayer[i].y + 60, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"MP"
		textPrint(getMemDC(), strMp,			 _vPlayer[i].x + 200, _vPlayer[i].y + 60, 15, 15, "HY�߰��", COLOR_BLACK, false);		//����
		textPrint(getMemDC(), "For Next Level",	 _vPlayer[i].x + 150, _vPlayer[i].y + 100, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"������ ���� ����ġ"
		textPrint(getMemDC(), strNextExp,		 _vPlayer[i].x + 300, _vPlayer[i].y + 100, 15, 15, "HY�߰��", COLOR_BLACK, false);		//�������� ����ġ - ���� ����ġ

		if (SCENEMANAGER->getCurrentSceneName() == "ĳ���ͻ���")
		{
			textPrint(getMemDC(), "Current EXP", _vPlayer[i].x + 150, _vPlayer[i].y + 80, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"���� ����ġ"
			textPrint(getMemDC(), strExp,		 _vPlayer[i].x + 300, _vPlayer[i].y + 80, 15, 15, "HY�߰��", COLOR_BLACK, false);		//���� ����ġ
		}
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

void menu::playerSlotAniStart(int slotNum, bool aniStart)
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		if (_vPlayer[i].partyIdx == slotNum)
		{
			_vPlayer[i].aniStart = aniStart;
		}
	}
}

//�÷��̾� ���Ժ���
//                   ���潽�Գѹ�        ���罽�Գѹ�  
void menu::slotChange(int changeSlotNum, int selectSlotNum)
{
	//������ ���� �ٲٱ�
	for (int i = 0; i < 4; ++i)
	{
		if (_vPlayer[i].partyIdx == selectSlotNum)
		{
			//�÷��̾� ��Ƽ���ѹ� ����
			char strPlayerNum[16];
			ZeroMemory(&strPlayerNum, sizeof(strPlayerNum));
			sprintf(strPlayerNum, "player%d", getPlayerNum(selectSlotNum));

			//�÷��̾� ��Ƽ���ѹ� ����
			char strPlayerIdx[16];
			ZeroMemory(&strPlayerIdx, sizeof(strPlayerIdx));
			sprintf(strPlayerIdx, "%d", changeSlotNum);

			INIDATA->addData(strPlayerNum, "partyIdx", strPlayerIdx);
			INIDATA->iniSave("skgFile");
		}
		else
		{
			if (_vPlayer[i].partyIdx == changeSlotNum)
			{
				//�÷��̾� ��Ƽ���ѹ� ����
				char strPlayerNum[16];
				ZeroMemory(&strPlayerNum, sizeof(strPlayerNum));
				sprintf(strPlayerNum, "player%d", getPlayerNum(changeSlotNum));

				//�÷��̾� ��Ƽ���ѹ� ����
				char strPlayerIdx[16];
				ZeroMemory(&strPlayerIdx, sizeof(strPlayerIdx));
				sprintf(strPlayerIdx, "%d", selectSlotNum);

				INIDATA->addData(strPlayerNum, "partyIdx", strPlayerIdx);
				INIDATA->iniSave("skgFile");
			}
		}

	}


	//���� �̼��� �̹�����...
	for (int i = 0; i < 4; ++i)
	{
		_vPlayer[i].ani->setFrameIndex(0);
		_vPlayer[i].slotSelect = false;
	}
}

//���Լ���
int menu::slotSelect(int selectSlotNum)
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		if (_vPlayer[i].partyIdx == selectSlotNum)
		{
			_vPlayer[i].ani->stop();
			_vPlayer[i].ani->setFrameIndex(1);
			_vPlayer[i].aniStart = false;
			_vPlayer[i].slotSelect = true;
		
			return getPlayerNum(i);
		}
	}
}


int menu::getPlayerNum(int partyIdX)
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		if (_vPlayer[i].partyIdx == partyIdX)
		{
			if (!strcmp(_vPlayer[i].name, "TINA"))
			{
				return 0;
			}
			if (!strcmp(_vPlayer[i].name, "LOCKE"))
			{
				return 1;
			}
			if (!strcmp(_vPlayer[i].name, "CELES"))
			{
				return 2;
			}
			if (!strcmp(_vPlayer[i].name, "SHADOW"))
			{
				return 3;
			}
		
		}
	}
}

//------------------------------  slot  ------------------------------ 


//-----------------------------  status  ----------------------------- 
           
void menu::playerStatusInit(int strength, int speed, int stamina, int magic, int attack,
	int attackDefence, int magicDefence, int evation, int magicEvation, int partyIdx,
	string weapon, string armor, string helmet, string subWeapon)
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

	sprintf(player.weapon, "%s", weapon);
	sprintf(player.armor, "%s", armor);
	sprintf(player.helmet, "%s", helmet);
	sprintf(player.subWeapon, "%s", subWeapon);

	_vPlayerStatus.push_back(player);
}

void menu::playerStatusRender(int SlotNum)
{
	for (int i = 0; i < _vPlayer.size(); ++i)
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
		sprintf(strEvation, "%d%%", _vPlayerStatus[i].evation);
		char strMagicE[INTCHARBUFF];
		sprintf(strMagicE, "%d%%", _vPlayerStatus[i].magicEvation);

		char strWeapon[INTCHARBUFF];
		sprintf(strWeapon, "%s", _vPlayerStatus[i].weapon);
		char strArmor[INTCHARBUFF];
		sprintf(strArmor, "%s", _vPlayerStatus[i].armor);
		char strHelmet[INTCHARBUFF];
		sprintf(strHelmet, "%s", _vPlayerStatus[i].helmet);
		char strSubweapon[INTCHARBUFF];
		sprintf(strSubweapon, "%s", _vPlayerStatus[i].subWeapon);


		//�ؽ�Ʈ ��¿� ��ġ����
		int textX = 0;
		textX = _vPlayer[i].x + 200;
		int textY = 0;
		textY = _vPlayer[i].y + 150;
		int textInterY[9] = { NULL };
		for (int i = 0; i < 9; ++i)
		{
			textInterY[i] = 30 * i;
		}

		//--------------------------------------------------------- �ؽ�Ʈ ��� ---------------------------------------------------------
		//�÷��̾� �⺻ �ɷ�
		textPrint(getMemDC(), "Strength",		_vPlayer[i].x,		 textY + textInterY[0], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Strength"
		textPrint(getMemDC(), strStrength,		_vPlayer[i].x + 150, textY + textInterY[0], 15, 15, "HY�߰��", COLOR_BLACK, false);	//��
		textPrint(getMemDC(), "Speed",			_vPlayer[i].x,		 textY + textInterY[1], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Speed"
		textPrint(getMemDC(), strSpeed,			_vPlayer[i].x + 150, textY + textInterY[1], 15, 15, "HY�߰��", COLOR_BLACK, false);	//���ǵ�
		textPrint(getMemDC(), "Stamina",		_vPlayer[i].x,		 textY + textInterY[2], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Stamina"
		textPrint(getMemDC(), strStamina,		_vPlayer[i].x + 150, textY + textInterY[2], 15, 15, "HY�߰��", COLOR_BLACK, false);	//������
		textPrint(getMemDC(), "Magic",			_vPlayer[i].x,		 textY + textInterY[3], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Magic"
		textPrint(getMemDC(), strMagic,			_vPlayer[i].x + 150, textY + textInterY[3], 15, 15, "HY�߰��", COLOR_BLACK, false);	//����
		textPrint(getMemDC(), "Attack",			_vPlayer[i].x,       textY + textInterY[4], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Attack"
		textPrint(getMemDC(), strAttack,		_vPlayer[i].x + 150, textY + textInterY[4], 15, 15, "HY�߰��", COLOR_BLACK, false);	//���ݷ�
		textPrint(getMemDC(), "AttackDefence",  _vPlayer[i].x,		 textY + textInterY[5], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"AttackDefence"
		textPrint(getMemDC(), strAttackD,		_vPlayer[i].x + 150, textY + textInterY[5], 15, 15, "HY�߰��", COLOR_BLACK, false);	//���ݵ��潺
		textPrint(getMemDC(), "MagicDefence",   _vPlayer[i].x,		 textY + textInterY[6], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"MagicDefence"
		textPrint(getMemDC(), strMagicD,		_vPlayer[i].x + 150, textY + textInterY[6], 15, 15, "HY�߰��", COLOR_BLACK, false);	//�������潺
		textPrint(getMemDC(), "Evation",		_vPlayer[i].x,		 textY + textInterY[7], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Evation"
		textPrint(getMemDC(), strEvation,		_vPlayer[i].x + 150, textY + textInterY[7], 15, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��
		textPrint(getMemDC(), "MagicEvation",	_vPlayer[i].x,		 textY + textInterY[8], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"MagicEvation"
		textPrint(getMemDC(), strMagicE,		_vPlayer[i].x + 150, textY + textInterY[8], 15, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��

		//�÷��̾� ���� ������
		textPrint(getMemDC(), "Right Hand",		_vPlayer[i].x + textX,		 textY + textInterY[0], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Right Hand"
		textPrint(getMemDC(), strWeapon,		_vPlayer[i].x + textX + 150, textY + textInterY[0], 15, 15, "HY�߰��", COLOR_BLACK, false);	//�ֹ���
		textPrint(getMemDC(), "Left Hand",		_vPlayer[i].x + textX,		 textY + textInterY[1], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Left Hand"
		textPrint(getMemDC(), strArmor,			_vPlayer[i].x + textX + 150, textY + textInterY[1], 15, 15, "HY�߰��", COLOR_BLACK, false);	//��������
		textPrint(getMemDC(), "Head",			_vPlayer[i].x + textX,		 textY + textInterY[2], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Head"
		textPrint(getMemDC(), strHelmet,		_vPlayer[i].x + textX + 150, textY + textInterY[2], 15, 15, "HY�߰��", COLOR_BLACK, false);	//���
		textPrint(getMemDC(), "Body",			_vPlayer[i].x + textX,		 textY + textInterY[3], 15, 15, "HY�߰��", COLOR_BLUE, false);		//"Body"
		textPrint(getMemDC(), strSubweapon,		_vPlayer[i].x + textX + 150, textY + textInterY[3], 15, 15, "HY�߰��", COLOR_BLACK, false);	//����

	}
}

void menu::playerStatusRemove()
{
	if (_vPlayerStatus.size() != 0)
	{
		for (int i = 0; i < _vPlayer.size(); ++i)
		{
			_vPlayerStatus.erase(_vPlayer.begin() + i);
		}
	}

	_vPlayerStatus.clear();
}
//-----------------------------  status  ----------------------------- 


//----------------------------  fileLoad  ---------------------------- 
//�÷��̾� ���̺� ���� �ε�      ���÷��̾� ���Գѹ�(Ư�� ĳ���� ���� �ϳ��� �����)
void menu::fileLoad(int fileNum, int playerNumber, bool tmpFile)
{
	//���� �ʱ�ȭ
	playerSlotRemove();
	if (!_fileLoadOk[fileNum]) _selectFileCount = 2;  //��ư���� �ʱ�ȭ

	//���̺����� 
	char saveFileNum[32];
	ZeroMemory(&saveFileNum, sizeof(saveFileNum));
	if (tmpFile)
	{
		wsprintf(saveFileNum, "skgFile");
	}
	else
	{
		wsprintf(saveFileNum, "saveFile%d", fileNum);
	}



	for (int i = 0; i < 4; ++i)
	{
		//�÷��̾� ��ȣ ���� ����
		char playerNum[16];
		ZeroMemory(&playerNum, sizeof(playerNum));

		//�÷��̾� �������
		ZeroMemory(&_playerSlot, sizeof(_playerSlot));

		if (playerNumber != -1)  //Ư�� ĳ���� ���� ���ý�
		{
			wsprintf(playerNum, "player%d", playerNumber);
			i = 0;
		}
		else
		{
			wsprintf(playerNum, "player%d", i);
		}

		wsprintf(_playerSlot.name, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "name"));			//�̸�
		_playerSlot.img = IMAGEMANAGER->findImage(_playerSlot.name);

		//------------------------------------------- playerNumber �Է� -------------------------------------------
		//if (playerNumber == -1)
		//{
		//	if		(_playerSlot.name == "TINA")	i = 0;
		//	else if (_playerSlot.name == "LOCKE")	i = 1;
		//	else if (_playerSlot.name == "CELES")	i = 2;
		//	else if (_playerSlot.name == "SHADOW")  i = 3;
		//}
		//------------------------------------------- playerNumber �Է� -------------------------------------------
	
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

		wsprintf(_playerSlot.weapon, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myWeapon"));		//��������
		wsprintf(_playerSlot.armor, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myArmor"));			//��������
		wsprintf(_playerSlot.helmet, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myHelmet"));		//��������
		wsprintf(_playerSlot.subWeapon, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "mySubWeapon"));	//������������


		//-------------------------------------------- playerSlot ��ġ --------------------------------------------
		if (playerNumber != -1)  //Ư�� ĳ���� ���� ���ý�
		{
			_playerSlot.y = 102;
		}
		else
		{
			_playerSlot.y = 102 + (_playerSlot.partyIdx * 137);
		}
		//-------------------------------------------- playerSlot ��ġ --------------------------------------------


		//�÷��̾� ���� ������� ���
		playerSlotInit(_playerSlot.name, 65, _playerSlot.y, _playerSlot.level, _playerSlot.job, _playerSlot.hp,
			_playerSlot.maxHp, _playerSlot.mp, _playerSlot.maxMp, _playerSlot.exp, _playerSlot.maxExp, _playerSlot.partyIdx);

		//�÷��̾� ���� ������� ���
		playerStatusInit(_playerSlot.strength, _playerSlot.speed, _playerSlot.stamina, _playerSlot.magic, _playerSlot.attack,
			_playerSlot.attackDefence, _playerSlot.magicDefence, _playerSlot.evation, _playerSlot.magicEvation, _playerSlot.partyIdx,
			_playerSlot.weapon, _playerSlot.armor, _playerSlot.helmet, _playerSlot.subWeapon);

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
	int magicEvation, int partyIdx, string myWeapon, string myArmor, string myHelmet, string mySubWeapon, bool tmpSave, bool saveFile)
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



	for (int i = 0; i < saveNum; ++i)
	{
		//�������� �ѹ�
		TCHAR tmp[4];
		ZeroMemory(&tmp, sizeof(tmp));
		wsprintf(tmp, "%d", fileNum);
		INIDATA->addData("fileInfo", "fileNum", tmp);

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
		//�÷��̾� ����
		INIDATA->addData(subjectNum, "myWeapon", myWeapon.c_str());
		//�÷��̾� �Ƹ�
		INIDATA->addData(subjectNum, "myArmor", myArmor.c_str());
		//�÷��̾� ���
		INIDATA->addData(subjectNum, "myHelmet", myHelmet.c_str());
		//�÷��̾� ���깫��
		INIDATA->addData(subjectNum, "mySubWeapon", mySubWeapon.c_str());

		if (i == 0)
		{
			if (!saveFile)
			{
				//��������: saveFile
				TCHAR saveFileName[16];
				wsprintf(saveFileName, "saveFile%d", fileNum);
				INIDATA->iniSave(saveFileName);
			}
		}
		if (i == 1)
		{
			//��������: tmpFile
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
		//��������
		INIDATA->addData("gameData", "stage", stage.c_str());

		//�÷��̾� ��
		if (SCENEMANAGER->getCurrentSceneName() == "������")
		{
			//�� �ʱ�ȭ
			_iM->setMoney(30000);
		}
		else
		{
			TCHAR tmp2[8];
			ZeroMemory(&tmp2, sizeof(tmp2));
			wsprintf(tmp2, "%d", gil);
			INIDATA->addData("Inventory", "Gil", tmp2);
		}

		//�÷��� �ð�
		TCHAR tmp3[32];
		ZeroMemory(&tmp3, sizeof(tmp3));
		wsprintf(tmp3, "%d", _gameTotalTime);
		INIDATA->addData("gameData", "playTime", tmp3);


		//��������
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

//saveFile -> tmpFile copy
void menu::fileCopyTmpFile(int fileNum)
{
	//�÷��̾� �����ε�
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
			true, false);


		if (i == 3)
		{
			char tmpGil[16];
			ZeroMemory(&tmpGil, sizeof(tmpGil));
			sprintf(tmpGil, "%d", tmpPlayrInfo.gil);

			char tmpTime[16];
			ZeroMemory(&tmpTime, sizeof(tmpTime));
			sprintf(tmpTime, "%f", _gameTotalTime);

			INIDATA->addData("gameData", "stage", tmpPlayrInfo.stage);
			INIDATA->addData("Inventory", "Gil", tmpGil);
			INIDATA->addData("gameData", "playTime", tmpTime);

			INIDATA->iniSave("skgFile");

			//������ 
			itemDataLoad(fileNum, true);
		}
	}
}

//tmpFile -> saveFile copy
void menu::fileCopySaveFile(int fileNum)
{
		//�÷��̾� �����ε�
	tagSaveData tmpPlayrInfo;

	for (int i = 0; i < 4; ++i)
	{
		ZeroMemory(&tmpPlayrInfo, sizeof(tmpPlayrInfo));
		tmpPlayrInfo = loadIniPlayerData(fileNum, i, true);

		saveIniPlayerData(tmpPlayrInfo.fileNum, i, tmpPlayrInfo.playerInfo.name, tmpPlayrInfo.playerInfo.job, tmpPlayrInfo.playerInfo.level,
			tmpPlayrInfo.playerInfo.hp, tmpPlayrInfo.playerInfo.maxHp, tmpPlayrInfo.playerInfo.mp, tmpPlayrInfo.playerInfo.maxMp,
			tmpPlayrInfo.playerInfo.exp, tmpPlayrInfo.playerInfo.maxExp, tmpPlayrInfo.playerInfo.strength, tmpPlayrInfo.playerInfo.speed,
			tmpPlayrInfo.playerInfo.stamina, tmpPlayrInfo.playerInfo.magic, tmpPlayrInfo.playerInfo.attack, tmpPlayrInfo.playerInfo.attackDefence,
			tmpPlayrInfo.playerInfo.magicDefence, tmpPlayrInfo.playerInfo.evation, tmpPlayrInfo.playerInfo.magicEvation, tmpPlayrInfo.playerInfo.partyIdx,
			tmpPlayrInfo.playerInfo.weapon, tmpPlayrInfo.playerInfo.armor, tmpPlayrInfo.playerInfo.helmet, tmpPlayrInfo.playerInfo.subWeapon,
			false, false);


		char saveFileNum[32];
		ZeroMemory(&saveFileNum, sizeof(saveFileNum));
		sprintf(saveFileNum, "saveFile%d", fileNum);
		//INIDATA->iniSave(saveFileNum);

		if (i == 3)
		{
			//���ӵ�����
			char tmpGil[16];
			ZeroMemory(&tmpGil, sizeof(tmpGil));
			sprintf(tmpGil, "%d", tmpPlayrInfo.gil);

			char tmpTime[16];
			ZeroMemory(&tmpTime, sizeof(tmpTime));
			sprintf(tmpTime, "%d", tmpPlayrInfo.playTime);

			INIDATA->addData("gameData", "stage", tmpPlayrInfo.stage);
			INIDATA->addData("Inventory", "Gil", tmpGil);
			INIDATA->addData("gameData", "playTime", tmpTime);

			INIDATA->iniSave(saveFileNum);

			//������
			itemDataLoad(fileNum);
		}
	}
}

tagSaveData menu::loadIniPlayerData(int fileNum, int playerNumber, bool tmpFile)
{
	//���̺����� �ѹ�
	char saveFileNum[32];
	ZeroMemory(&saveFileNum, sizeof(saveFileNum));
	if (!tmpFile)
	{
		wsprintf(saveFileNum, "saveFile%d", fileNum);
	}
	else
	{
		wsprintf(saveFileNum, "skgFile");
	}


	//�÷��̾� ��ȣ ���� ����
	char playerNum[16];
	ZeroMemory(&playerNum, sizeof(playerNum));
	wsprintf(playerNum, "player%d", playerNumber);

	//�÷��̾� �����ε�
	tagSaveData tmpPlayrInfo;
	ZeroMemory(&tmpPlayrInfo, sizeof(tmpPlayrInfo));

	if (!tmpFile)
	{
		tmpPlayrInfo.fileNum = INIDATA->loadDataInterger(saveFileNum, "fileInfo", "fileNum");                           //���ϳѹ� 
	}
	else
	{
		tmpPlayrInfo.fileNum = fileNum;
	}
	
	wsprintf(tmpPlayrInfo.playerInfo.name, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "name"));				//�̸�
	wsprintf(tmpPlayrInfo.playerInfo.job, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "job"));				//����
	tmpPlayrInfo.playerInfo.level = INIDATA->loadDataInterger(saveFileNum, playerNum, "level");							//����   
	tmpPlayrInfo.playerInfo.hp = INIDATA->loadDataInterger(saveFileNum, playerNum, "hp");								//ü��     
	tmpPlayrInfo.playerInfo.maxHp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxHp");							//�ִ�ü��         
	tmpPlayrInfo.playerInfo.mp = INIDATA->loadDataInterger(saveFileNum, playerNum, "mp");								//����    
	tmpPlayrInfo.playerInfo.maxMp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxMp");							//�ִ븶��             
	tmpPlayrInfo.playerInfo.exp = INIDATA->loadDataInterger(saveFileNum, playerNum, "exp");								//����ġ        
	tmpPlayrInfo.playerInfo.maxExp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxExp");						//�������� ����ġ         
	tmpPlayrInfo.playerInfo.strength = INIDATA->loadDataInterger(saveFileNum, playerNum, "strength");					//��             
	tmpPlayrInfo.playerInfo.speed = INIDATA->loadDataInterger(saveFileNum, playerNum, "speed");							//���ǵ�      
	tmpPlayrInfo.playerInfo.stamina = INIDATA->loadDataInterger(saveFileNum, playerNum, "stamina");						//������         
	tmpPlayrInfo.playerInfo.magic = INIDATA->loadDataInterger(saveFileNum, playerNum, "magic");							//������    
	tmpPlayrInfo.playerInfo.attack = INIDATA->loadDataInterger(saveFileNum, playerNum, "attack");						//���ݷ�            
	tmpPlayrInfo.playerInfo.attackDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "attackDefence");			//���ݹ���               
	tmpPlayrInfo.playerInfo.magicDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicDefence");			//��������       
	tmpPlayrInfo.playerInfo.evation = INIDATA->loadDataInterger(saveFileNum, playerNum, "evation");						//����ȸ��           
	tmpPlayrInfo.playerInfo.magicEvation = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicEvation");			//����ȸ��               
	tmpPlayrInfo.playerInfo.partyIdx = INIDATA->loadDataInterger(saveFileNum, playerNum, "partyIdx");					//��Ƽ���ѹ�
	wsprintf(tmpPlayrInfo.playerInfo.weapon, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myWeapon"));		//����
	wsprintf(tmpPlayrInfo.playerInfo.armor, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myArmor"));			//���� 
	wsprintf(tmpPlayrInfo.playerInfo.helmet, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "myHelmet"));		//����  
	wsprintf(tmpPlayrInfo.playerInfo.subWeapon, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "mySubWeapon"));	//�������� 

	wsprintf(tmpPlayrInfo.stage, "%s", INIDATA->loadDataString(saveFileNum, "gameData", "stage"));                      //��������  
	tmpPlayrInfo.gil = INIDATA->loadDataInterger(saveFileNum, "Inventory", "Gil");										//��  
	tmpPlayrInfo.playTime = INIDATA->loadDataInterger(saveFileNum, "gameData", "playTime");								//�÷��̽ð�  

	return tmpPlayrInfo;
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
	tmpGD.gil = INIDATA->loadDataInterger(tmpGD.saveFileName, "Inventory", "Gil");
	
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
				tmpGD.gil = INIDATA->loadDataInterger(tmpSaveFileNum, "Inventory", "Gil");

				if (tmpGD.playTime != -1) break;
			}
		}
	}
    

	//�ؽ�Ʈ ���
	if (tmpGD.playTime != -1)
	{
		char tmpBuff[32];
		textPrint(getMemDC(), tmpGD.stage,					     1050, 392, 30, 30, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.gil, tmpBuff, 10),		 1080, 516, 20, 20, "Stencil", COLOR_WHITE, true);
		if (SCENEMANAGER->getCurrentSceneName() != "�ɼ�")
		{
			gamePlayTime(tmpGD.playTime, true);
		}
	}
}

//============================== gameData ============================


//================================ item ==============================

void menu::itemSave(int itemKind, int itemName, int itemNum, bool saveFile, int saveFileNum)
{
	int saveNum = 0;
	if (saveFile) saveNum = 2;  
	else saveNum = 1;  //tmpFile���� ������ ���

	switch (itemKind)
	{
		case MENUITEM_ITEM:
			for (int i = 0; i < saveNum; ++i)
			{
				_iM->setItemInventory(itemName, itemNum);
				if (i == 0) _iM->saveInventory("skgFile");
				if (i == 1)
				{
					char saveFile[32];
					ZeroMemory(&saveFile, sizeof(saveFile));
					sprintf(saveFile, "saveFile%d", saveFileNum);
					_iM->saveInventory(saveFile);
				}
			}
		break;
		case MENUITEM_ARMOR:
			for (int i = 0; i < saveNum; ++i)
			{
				_iM->setArmorInventory(itemName, itemNum);
				if (i == 0) _iM->saveInventory("skgFile");
				if (i == 1)
				{
					char saveFile[32];
					ZeroMemory(&saveFile, sizeof(saveFile));
					sprintf(saveFile, "saveFile%d", saveFileNum);
					_iM->saveInventory(saveFile);
				}
			}
		break;
		case MENUITEM_WEAPON:
			for (int i = 0; i < saveNum; ++i)
			{
				_iM->setWeaponInventory(itemName, itemNum);
				if (i == 0) _iM->saveInventory("skgFile");
				if (i == 1)
				{
					char saveFile[32];
					ZeroMemory(&saveFile, sizeof(saveFile));
					sprintf(saveFile, "saveFile%d", saveFileNum);
					_iM->saveInventory(saveFile);
				}
			}
		break;
	}
}

void menu::itemDataLoad(int fileNum, bool tmpFile)
{
	//���̺����� �ѹ�
	char saveFileNum[32];
	ZeroMemory(&saveFileNum, sizeof(saveFileNum));

	//���庯��
	char itemList[1024];
	char weaponList[1024];
	char armorList[1024];
	ZeroMemory(&itemList, sizeof(itemList));
	ZeroMemory(&weaponList, sizeof(weaponList));
	ZeroMemory(&armorList, sizeof(armorList));

	if (!tmpFile)  //tmp���� -> save����
	{
		wsprintf(itemList, "%s", INIDATA->loadDataString("skgFile", "Inventory", "ItemList"));
		wsprintf(weaponList, "%s", INIDATA->loadDataString("skgFile", "Inventory", "WeaponList"));
		wsprintf(armorList, "%s", INIDATA->loadDataString("skgFile", "Inventory", "ArmorList"));

		//���̺����� ����
		wsprintf(saveFileNum, "saveFile%d", fileNum);
	}
	else  //save���� -> tmp����
	{
		//�ε����� ����
		wsprintf(saveFileNum, "saveFile%d", fileNum);
		wsprintf(itemList, "%s", INIDATA->loadDataString(saveFileNum, "Inventory", "ItemList"));
		wsprintf(weaponList, "%s", INIDATA->loadDataString(saveFileNum, "Inventory", "WeaponList"));
		wsprintf(armorList, "%s", INIDATA->loadDataString(saveFileNum, "Inventory", "ArmorList"));

		//���̺����� ����
		wsprintf(saveFileNum, "skgFile");
	}

	//������ ����
	INIDATA->addData("Inventory", "ItemList", itemList);
	INIDATA->addData("Inventory", "WeaponList", weaponList);
	INIDATA->addData("Inventory", "ArmorList", armorList);

	INIDATA->iniSave(saveFileNum);
}

//================================ item ==============================


//================================ timer =============================

void menu::gamePlayTime(float getSaveTime, bool fileLoadTime)
{

	TCHAR str[128];
	if (fileLoadTime)
	{
		sprintf_s(str, "%f", getSaveTime);
	}
	else
	{
		sprintf_s(str, "%f", _gameTotalTime);
	}

	if (fileLoadTime)
	{
		//1��
		sprintf_s(str, "%d", (int)(getSaveTime / 60) % 10);
		textPrint(getMemDC(), str, 1060, 462, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)getSaveTime / 600);
		textPrint(getMemDC(), str, 1050, 462, 20, 20, "Stencil", COLOR_WHITE, true);

		//1��
		sprintf_s(str, "%d", (int)getSaveTime % 10);
		textPrint(getMemDC(), str, 1090, 462, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)(getSaveTime / 10) % 6);
		textPrint(getMemDC(), str, 1080, 462, 20, 20, "Stencil", COLOR_WHITE, true);

		sprintf_s(str, ":", str);
		textPrint(getMemDC(), str, 1070, 461, 20, 20, "Stencil", COLOR_WHITE, true);
	}
	else
	{
		//1��
		sprintf_s(str, "%d", (int)(_gameTotalTime / 60) % 10);
		textPrint(getMemDC(), str, 1060, 462, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)_gameTotalTime / 600);
		textPrint(getMemDC(), str, 1050, 462, 20, 20, "Stencil", COLOR_WHITE, true);

		//1��
		sprintf_s(str, "%d", (int)_gameTotalTime % 10);
		textPrint(getMemDC(), str, 1090, 462, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)(_gameTotalTime / 10) % 6);
		textPrint(getMemDC(), str, 1080, 462, 20, 20, "Stencil", COLOR_WHITE, true);

		sprintf_s(str, ":", str);
		textPrint(getMemDC(), str, 1070, 461, 20, 20, "Stencil", COLOR_WHITE, true);
	}

}

//================================ timer =============================