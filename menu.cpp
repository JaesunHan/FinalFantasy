#include "stdafx.h"
#include "menu.h"
#include "itemManager.h"
#include "worldMapScene.h"
#include "townScene.h"

menu::menu()
{
	_slotNum = 0;
	_isSavePoint = false;
}
menu::~menu()
{
}


HRESULT menu::init()
{
	//���̺�����Ʈ ���޽�


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
		char tmp[CHARBUFFSHORT];
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
	char aniTemp[CHARBUFFSHORT];
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

void menu::playerSlotRender(bool textOut)
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

		if (textOut)
		{
			//�ؽ�Ʈ ���
			textPrint(getMemDC(), _vPlayer[i].name, _vPlayer[i].x + 150, _vPlayer[i].y - 10, 30, 30, "Stencil", COLOR_BLACK, false);		//�̸�
			textPrint(getMemDC(), _vPlayer[i].job, _vPlayer[i].x + 300, _vPlayer[i].y - 10, 25, 25, "Roboto", COLOR_BLACK, false);			//����
			textPrint(getMemDC(), "LV", _vPlayer[i].x + 150, _vPlayer[i].y + 20, 15, 15, "HY�߰��", COLOR_BLUE, false);					//"LV"
			textPrint(getMemDC(), strLevel, _vPlayer[i].x + 200, _vPlayer[i].y + 20, 15, 15, "HY�߰��", COLOR_BLACK, false);				//����
			textPrint(getMemDC(), "HP", _vPlayer[i].x + 150, _vPlayer[i].y + 40, 15, 15, "HY�߰��", COLOR_BLUE, false);					//"HP"
			textPrint(getMemDC(), strHp, _vPlayer[i].x + 200, _vPlayer[i].y + 40, 15, 15, "HY�߰��", COLOR_BLACK, false);					//ü��
			textPrint(getMemDC(), "MP", _vPlayer[i].x + 150, _vPlayer[i].y + 60, 15, 15, "HY�߰��", COLOR_BLUE, false);					//"MP"
			textPrint(getMemDC(), strMp, _vPlayer[i].x + 200, _vPlayer[i].y + 60, 15, 15, "HY�߰��", COLOR_BLACK, false);					//����
			textPrint(getMemDC(), "For Next Level", _vPlayer[i].x + 150, _vPlayer[i].y + 100, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"������ ���� ����ġ"
			textPrint(getMemDC(), strNextExp, _vPlayer[i].x + 300, _vPlayer[i].y + 100, 15, 15, "HY�߰��", COLOR_BLACK, false);			//�������� ����ġ - ���� ����ġ

			if (SCENEMANAGER->getCurrentSceneName() == "ĳ���ͻ���")
			{
				textPrint(getMemDC(), "Current EXP", _vPlayer[i].x + 150, _vPlayer[i].y + 80, 15, 15, "HY�߰��", COLOR_BLUE, false);		//"���� ����ġ"
				textPrint(getMemDC(), strExp, _vPlayer[i].x + 300, _vPlayer[i].y + 80, 15, 15, "HY�߰��", COLOR_BLACK, false);				//���� ����ġ
			}
		}
		else
		{
			textPrint(getMemDC(), _vPlayer[i].name, _vPlayer[i].x + 57, _vPlayer[i].y + 110, 30, 30, "Stencil", COLOR_BLACK, true);		//�̸�
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

//���Ͽ� ����� �ش� ĳ���� ��Ƽ���ѹ� ��ȯ
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
	int weapon, int armor, int helmet, int subWeapon, int command1, int command2,
	int command3, int command4, int command5, int command6, int command7, int command8)
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

	player.weapon = weapon;
	player.armor = armor;
	player.helmet = helmet;
	player.subWeapon = subWeapon;

	player.command[0] = command1;
	player.command[1] = command2;
	player.command[2] = command3;
	player.command[3] = command4;
	player.command[4] = command5;
	player.command[5] = command6;
	player.command[6] = command7;
	player.command[7] = command8;

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
		sprintf(strWeapon, "%s", _iM->getVItem()[itemGetNum(_vPlayerStatus[i].weapon)]->getItemName());
		char strArmor[INTCHARBUFF];
		sprintf(strArmor, "%s", _iM->getVItem()[itemGetNum(_vPlayerStatus[i].armor)]->getItemName());
		char strHelmet[INTCHARBUFF];
		sprintf(strHelmet, "%s", _iM->getVItem()[itemGetNum(_vPlayerStatus[i].helmet)]->getItemName());
		char strSubweapon[INTCHARBUFF];
		sprintf(strSubweapon, "%s", _iM->getVItem()[itemGetNum(_vPlayerStatus[i].subWeapon)]->getItemName());

		char strCommand0[INTCHARBUFF];
		sprintf(strCommand0, "%s", playerCommandReturn(_vPlayerStatus[i].command[0]).c_str());
		char strCommand1[INTCHARBUFF];
		sprintf(strCommand1, "%s", playerCommandReturn(_vPlayerStatus[i].command[1]).c_str());
		char strCommand2[INTCHARBUFF];
		sprintf(strCommand2, "%s", playerCommandReturn(_vPlayerStatus[i].command[2]).c_str());
		char strCommand3[INTCHARBUFF];
		sprintf(strCommand3, "%s", playerCommandReturn(_vPlayerStatus[i].command[3]).c_str());
		char strCommand4[INTCHARBUFF];
		sprintf(strCommand4, "%s", playerCommandReturn(_vPlayerStatus[i].command[4]).c_str());
		char strCommand5[INTCHARBUFF];
		sprintf(strCommand5, "%s", playerCommandReturn(_vPlayerStatus[i].command[5]).c_str());
		char strCommand6[32];
		sprintf(strCommand6, "%s", playerCommandReturn(_vPlayerStatus[i].command[6]).c_str());
		char strCommand7[INTCHARBUFF];
		sprintf(strCommand7, "%s", playerCommandReturn(_vPlayerStatus[i].command[7]).c_str());




		//�ؽ�Ʈ ��¿� ��ġ����
		int textX0 = 0;
		textX0 = _vPlayer[i].x - 30;
		int textX = 0;
		textX = _vPlayer[i].x + 250;
		int textX1 = 0;
		textX1 = textX + 350;
		int textY = 0;
		textY = _vPlayer[i].y + 160;
		int textInterY[9] = { NULL };
		for (int i = 0; i < 9; ++i)
		{
			textInterY[i] = 40 * i;
		}

		//--------------------------------------------------------- �ؽ�Ʈ ��� ---------------------------------------------------------
		//�÷��̾� �⺻ �ɷ�
		textPrint(getMemDC(), "Strength",		textX0,		 textY + textInterY[0], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Strength"
		textPrint(getMemDC(), strStrength,		textX0 + 200, textY + textInterY[0], 20, 15, "HY�߰��", COLOR_BLACK, false);	//��
		textPrint(getMemDC(), "Speed",			textX0,		 textY + textInterY[1], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Speed"
		textPrint(getMemDC(), strSpeed,			textX0 + 200, textY + textInterY[1], 20, 15, "HY�߰��", COLOR_BLACK, false);	//���ǵ�
		textPrint(getMemDC(), "Stamina",		textX0,		 textY + textInterY[2], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Stamina"
		textPrint(getMemDC(), strStamina,		textX0 + 200, textY + textInterY[2], 20, 15, "HY�߰��", COLOR_BLACK, false);	//������
		textPrint(getMemDC(), "Magic",			textX0,		 textY + textInterY[3], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Magic"
		textPrint(getMemDC(), strMagic,			textX0 + 200, textY + textInterY[3], 20, 15, "HY�߰��", COLOR_BLACK, false);	//����
		textPrint(getMemDC(), "Attack",			textX0,       textY + textInterY[4], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Attack"
		textPrint(getMemDC(), strAttack,		textX0 + 200, textY + textInterY[4], 20, 15, "HY�߰��", COLOR_BLACK, false);	//���ݷ�
		textPrint(getMemDC(), "AttackDefence",  textX0,		 textY + textInterY[5], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"AttackDefence"
		textPrint(getMemDC(), strAttackD,		textX0 + 200, textY + textInterY[5], 20, 15, "HY�߰��", COLOR_BLACK, false);	//���ݵ��潺
		textPrint(getMemDC(), "MagicDefence",   textX0,		 textY + textInterY[6], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"MagicDefence"
		textPrint(getMemDC(), strMagicD,		textX0 + 200, textY + textInterY[6], 20, 15, "HY�߰��", COLOR_BLACK, false);	//�������潺
		textPrint(getMemDC(), "Evation",		textX0,		 textY + textInterY[7], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Evation"
		textPrint(getMemDC(), strEvation,		textX0 + 200, textY + textInterY[7], 20, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��
		textPrint(getMemDC(), "MagicEvation",	textX0,		 textY + textInterY[8], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"MagicEvation"
		textPrint(getMemDC(), strMagicE,		textX0 + 200, textY + textInterY[8], 20, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��
		
		//�÷��̾� ���� ������
		textPrint(getMemDC(), "Right Hand",		textX0 + textX,		 textY + textInterY[0], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Right Hand"
		textPrint(getMemDC(), strWeapon,		textX0 + textX + 150, textY + textInterY[0], 20, 15, "HY�߰��", COLOR_BLACK, false);	//�ֹ���
		textPrint(getMemDC(), "Left Hand",		textX0 + textX,		 textY + textInterY[1], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Left Hand"
		textPrint(getMemDC(), strSubweapon,		textX0 + textX + 150, textY + textInterY[1], 20, 15, "HY�߰��", COLOR_BLACK, false);	//��������
		textPrint(getMemDC(), "Head",			textX0 + textX,		 textY + textInterY[2], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Head"
		textPrint(getMemDC(), strHelmet,		textX0 + textX + 150, textY + textInterY[2], 20, 15, "HY�߰��", COLOR_BLACK, false);	//���
		textPrint(getMemDC(), "Body",			textX0 + textX,		 textY + textInterY[3], 20, 15, "HY�߰��", COLOR_BLUE, false);		//"Body"
		textPrint(getMemDC(), strArmor,			textX0 + textX + 150, textY + textInterY[3], 20, 15, "HY�߰��", COLOR_BLACK, false);	//����

	     //�÷��̾� ���� Ŀ�ǵ�
		textPrint(getMemDC(), "Command",		textX0 + textX1, textY + textInterY[0], 20, 15, "HY�߰��", COLOR_BLUE, false);			//"command"
		textPrint(getMemDC(), strCommand0,		textX0 + textX1, textY + textInterY[1], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand1,	    textX0 + textX1, textY + textInterY[2], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand2,	    textX0 + textX1, textY + textInterY[3], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand3,	    textX0 + textX1, textY + textInterY[4], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand4,	    textX0 + textX1, textY + textInterY[5], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand5,	    textX0 + textX1, textY + textInterY[6], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand6,	    textX0 + textX1, textY + textInterY[7], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
		textPrint(getMemDC(), strCommand7,		textX0 + textX1, textY + textInterY[8], 20, 15, "HY�߰��", COLOR_BLACK, false);			//����Ŀ�ǵ�
	}
}

void menu::playerStatusEquipsRender(string playerNum, bool equipSet, int myWeaponVNum, int mySubWeaponNum, int myHelmetNum, int myArmorNum)
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		//================== int -> string ����ȯ ==================
		//------------------------- �⺻�ɷ� -----------------------
		int equipStrength0 = 0, equipSpeed0 = 0, equipStamina0 = 0, equipMagic0 = 0;
		int equipAttack0 = 0, equipAttackD0 = 0, equipMagicD0 = 0;
		int equipEvation0 = 0, equipMagicE0 = 0;

		//tmp���Ͽ��� ��� �����۳ѹ� ��������
		int myWeaponVNum0 = INIDATA->loadDataInterger("skgFile", playerNum.c_str(), "myWeapon");
		int mySubWeaponNum0 = INIDATA->loadDataInterger("skgFile", playerNum.c_str(), "mySubWeapon");
		int myHelmetNum0 = INIDATA->loadDataInterger("skgFile", playerNum.c_str(), "myHelmet");
		int myArmorNum0 = INIDATA->loadDataInterger("skgFile", playerNum.c_str(), "myArmor");

		//----------------------------------------------------------
		//+�ɷ�ġ
		int strengthPlus = 0, speedPlus = 0, staminaPlus = 0, magicPlus = 0, attackPlus = 0, attackDPlus = 0, magicDPlus = 0, evationPlus = 0, magicEPlus = 0;
		int getMWAttack = 0, getSWAttack = 0, getMYHADefen = 0, getMAADefen = 0, getMHMDefen = 0, getMAMDefen = 0;

		//�����۸޴���->���� �ɷ�ġ ��������
		if (myWeaponVNum0 != 0)   getMWAttack  = ((weaponItem*)_iM->getVItem()[myWeaponVNum0])->getAttack();
		if (mySubWeaponNum0 != 0) getSWAttack  = ((weaponItem*)_iM->getVItem()[mySubWeaponNum0])->getAttack();
		if (myHelmetNum0 != 0)    getMYHADefen = ((armorItem*)_iM->getVItem()[myHelmetNum0])->getAttackDefRestored();
		if (myArmorNum0 != 0)     getMAADefen  = ((armorItem*)_iM->getVItem()[myArmorNum0])->getAttackDefRestored();
		if (myHelmetNum0 != 0)    getMHMDefen  = ((armorItem*)_iM->getVItem()[myHelmetNum0])->getMagicDefRestored();
		if (myArmorNum0 != 0)     getMAMDefen  = ((armorItem*)_iM->getVItem()[myArmorNum0])->getMagicDefRestored();

		strengthPlus = 0;
		speedPlus	 = 0;
		staminaPlus	 = 0;
		magicPlus	 = 0;
		attackPlus	 = getMWAttack + getSWAttack;
		attackDPlus  = getMYHADefen + getMAADefen;
		magicDPlus	 = getMHMDefen + getMAMDefen;
		evationPlus	 = 0;
		magicEPlus	 = 0;


		//�⺻+�ɷ�ġ
		equipStrength0 = _vPlayerStatus[i].strength;	 + strengthPlus;
		equipSpeed0	   = _vPlayerStatus[i].speed;		 + speedPlus;
		equipStamina0  = _vPlayerStatus[i].stamina;		 + staminaPlus;
		equipMagic0    = _vPlayerStatus[i].magic;		 + magicPlus;
		equipAttack0   = _vPlayerStatus[i].attack		 + attackPlus;
		equipAttackD0  = _vPlayerStatus[i].attackDefence + attackDPlus;
		equipMagicD0   = _vPlayerStatus[i].magicDefence  + magicDPlus;
		equipEvation0  = _vPlayerStatus[i].evation;		 + evationPlus;
		equipMagicE0   = _vPlayerStatus[i].magicEvation; + magicEPlus;

		//----------------------------------------------------------
		char strStrength[INTCHARBUFF];
		sprintf(strStrength, "%d", equipStrength0);
		char strSpeed[INTCHARBUFF];
		sprintf(strSpeed, "%d", equipSpeed0);
		char strStamina[INTCHARBUFF];
		sprintf(strStamina, "%d", equipStamina0);
		char strMagic[INTCHARBUFF];
		sprintf(strMagic, "%d", equipMagic0);
		char strAttack[INTCHARBUFF];
		sprintf(strAttack, "%d", equipAttack0);
		char strAttackD[INTCHARBUFF];
		sprintf(strAttackD, "%d", equipAttackD0);
		char strMagicD[INTCHARBUFF];
		sprintf(strMagicD, "%d", equipMagicD0);
		char strEvation[INTCHARBUFF];
		sprintf(strEvation, "%d%%", equipEvation0);
		char strMagicE[INTCHARBUFF];
		sprintf(strMagicE, "%d%%", equipMagicE0);
		//------------------------- �߰��ɷ� -----------------------
		int equipStrength = 0, equipSpeed = 0,   equipStamina = 0, equipMagic = 0;
		int equipAttack = 0,   equipAttackD = 0, equipMagicD = 0;
		int equipEvation = 0,  equipMagicE = 0;

		//----------------------------------------------------------
		//+�ɷ�ġ
		int strengthPlus1 = 0, speedPlus1 = 0, staminaPlus1 = 0, magicPlus1 = 0, attackPlus1 = 0, attackDPlus1 = 0, magicDPlus1 = 0, evationPlus1 = 0, magicEPlus1 = 0;
		int getMWAttack1 = 0, getSWAttack1 = 0, getMYHADefen1 = 0, getMAADefen1 = 0, getMHMDefen1 = 0, getMAMDefen1 = 0;

		//�����۸޴���->���� �ɷ�ġ ��������
		if (myWeaponVNum != -1)   getMWAttack1  = ((weaponItem*)_iM->getVItem()[myWeaponVNum])->getAttack();
		if (mySubWeaponNum != -1) getSWAttack1  = ((weaponItem*)_iM->getVItem()[mySubWeaponNum])->getAttack();
		if (myHelmetNum != -1)    getMYHADefen1 = ((armorItem*)_iM->getVItem()[myHelmetNum])->getAttackDefRestored();
		if (myArmorNum != -1)     getMAADefen1  = ((armorItem*)_iM->getVItem()[myArmorNum])->getAttackDefRestored();
		if (myHelmetNum != -1)    getMHMDefen1  = ((armorItem*)_iM->getVItem()[myHelmetNum])->getMagicDefRestored();
		if (myArmorNum != -1)     getMAMDefen1  = ((armorItem*)_iM->getVItem()[myArmorNum])->getMagicDefRestored();

		strengthPlus1 = 0;
		speedPlus1    = 0;
		staminaPlus1  = 0;
		magicPlus1    = 0;
		attackPlus1   = getMWAttack1 + getSWAttack1;
		attackDPlus1  = getMYHADefen1 + getMAADefen1;
		magicDPlus1   = getMHMDefen1 + getMAMDefen1;
		evationPlus1  = 0;
		magicEPlus1   = 0;

		//----------------------------------------------------------
		equipStrength = _vPlayerStatus[i].strength + strengthPlus1;
		equipSpeed	  = _vPlayerStatus[i].speed + speedPlus1;
		equipStamina  = _vPlayerStatus[i].stamina + staminaPlus1;
		equipMagic    = _vPlayerStatus[i].magic + magicPlus1;
		equipAttack   = _vPlayerStatus[i].attack + attackPlus1;
		equipAttackD  = _vPlayerStatus[i].attackDefence + attackDPlus1;
		equipMagicD   = _vPlayerStatus[i].magicDefence + magicDPlus1;
		equipEvation  = _vPlayerStatus[i].evation + evationPlus1;
		equipMagicE   = _vPlayerStatus[i].magicEvation + magicEPlus1;

		//----------------------------------------------------------
		char strStrength1[INTCHARBUFF];
		sprintf(strStrength1, "%d", equipStrength);
		char strSpeed1[INTCHARBUFF];
		sprintf(strSpeed1, "%d", equipSpeed);
		char strStamina1[INTCHARBUFF];
		sprintf(strStamina1, "%d",equipStamina);
		char strMagic1[INTCHARBUFF];
		sprintf(strMagic1, "%d", equipMagic);
		char strAttack1[INTCHARBUFF];
		sprintf(strAttack1, "%d",equipAttack);
		char strAttackD1[INTCHARBUFF];
		sprintf(strAttackD1, "%d", equipAttackD);
		char strMagicD1[INTCHARBUFF];
		sprintf(strMagicD1, "%d", equipMagicD);
		char strEvation1[INTCHARBUFF];
		sprintf(strEvation1, "%d%%", equipEvation);
		char strMagicE1[INTCHARBUFF];
		sprintf(strMagicE1, "%d%%", equipMagicE);
		//===========================================================

		//������ ������ ������ ����
		if (equipSet)
		{
			INIDATA->addData(playerNum.c_str(), "strength", strStrength1);
			INIDATA->addData(playerNum.c_str(), "speed", strSpeed1);
			INIDATA->addData(playerNum.c_str(), "stamina", strStamina1);
			INIDATA->addData(playerNum.c_str(), "magic", strMagic1);
			INIDATA->addData(playerNum.c_str(), "attack", strAttack1);
			INIDATA->addData(playerNum.c_str(), "attackDefence", strAttackD1);
			INIDATA->addData(playerNum.c_str(), "magicDefence", strMagicD1);
			INIDATA->addData(playerNum.c_str(), "evation", strEvation1);
			INIDATA->addData(playerNum.c_str(), "magicEvation", strMagicE1);

			INIDATA->iniSave("skgFile");
		}

		//--------------------------- �ؽ�Ʈ ��¿� ��ġ����
		int textX0 = _vPlayer[i].x - 25;

		int textX = 0;
		textX = textX0 + 200;
		int textY = 0;
		textY = _vPlayer[i].y + 260;
		int textInterY[9] = { NULL };
		for (int i = 0; i < 9; ++i)
		{
			textInterY[i] = 25 * i;
		}
		//---------------------------


		//--------------------------------------------------------- �ؽ�Ʈ ��� ---------------------------------------------------------
		//�÷��̾� �⺻ �ɷ�
		textPrint(getMemDC(), "Strength",		textX0,		  textY + textInterY[0], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"Strength"
		textPrint(getMemDC(), strStrength,		textX0 + 150, textY + textInterY[0], 17, 15, "HY�߰��", COLOR_BLACK, false);	//��
		textPrint(getMemDC(), "Speed",			textX0,		  textY + textInterY[1], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"Speed"
		textPrint(getMemDC(), strSpeed,			textX0 + 150, textY + textInterY[1], 17, 15, "HY�߰��", COLOR_BLACK, false);	//���ǵ�
		textPrint(getMemDC(), "Stamina",		textX0,		  textY + textInterY[2], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"Stamina"
		textPrint(getMemDC(), strStamina,		textX0 + 150, textY + textInterY[2], 17, 15, "HY�߰��", COLOR_BLACK, false);	//������
		textPrint(getMemDC(), "Magic",			textX0,		  textY + textInterY[3], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"Magic"
		textPrint(getMemDC(), strMagic,			textX0 + 150, textY + textInterY[3], 17, 15, "HY�߰��", COLOR_BLACK, false);	//����
		textPrint(getMemDC(), "Attack",			textX0,		  textY + textInterY[4], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"Attack"
		textPrint(getMemDC(), strAttack,		textX0 + 150, textY + textInterY[4], 17, 15, "HY�߰��", COLOR_BLACK, false);	//���ݷ�
		textPrint(getMemDC(), "AttackDefence",	textX0,		  textY + textInterY[5], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"AttackDefence"
		textPrint(getMemDC(), strAttackD,		textX0 + 150, textY + textInterY[5], 17, 15, "HY�߰��", COLOR_BLACK, false);	//���ݵ��潺
		textPrint(getMemDC(), "MagicDefence",	textX0,		  textY + textInterY[6], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"MagicDefence"
		textPrint(getMemDC(), strMagicD,		textX0 + 150, textY + textInterY[6], 17, 15, "HY�߰��", COLOR_BLACK, false);	//�������潺
		textPrint(getMemDC(), "Evation",		textX0,		  textY + textInterY[7], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"Evation"
		textPrint(getMemDC(), strEvation,		textX0 + 150, textY + textInterY[7], 17, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��
		textPrint(getMemDC(), "MagicEvation",	textX0,		  textY + textInterY[8], 17, 15, "HY�߰��", COLOR_BLUE, false);	//"MagicEvation"
		textPrint(getMemDC(), strMagicE,		textX0 + 150, textY + textInterY[8], 17, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��



			//������ ����� �ɷ�ġ		
			textPrint(getMemDC(), "->", textX, textY + textInterY[0], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strStrength1, textX + 50, textY + textInterY[0], 17, 15, "HY�߰��", COLOR_BLACK, false);	//��
			textPrint(getMemDC(), "->", textX, textY + textInterY[1], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strSpeed1, textX + 50, textY + textInterY[1], 17, 15, "HY�߰��", COLOR_BLACK, false);	//���ǵ�
			textPrint(getMemDC(), "->", textX, textY + textInterY[2], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strStamina1, textX + 50, textY + textInterY[2], 17, 15, "HY�߰��", COLOR_BLACK, false);	//������
			textPrint(getMemDC(), "->", textX, textY + textInterY[3], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strMagic1, textX + 50, textY + textInterY[3], 17, 15, "HY�߰��", COLOR_BLACK, false);	//����
			textPrint(getMemDC(), "->", textX, textY + textInterY[4], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strAttack1, textX + 50, textY + textInterY[4], 17, 15, "HY�߰��", COLOR_BLACK, false);	//���ݷ�
			textPrint(getMemDC(), "->", textX, textY + textInterY[5], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strAttackD1, textX + 50, textY + textInterY[5], 17, 15, "HY�߰��", COLOR_BLACK, false);	//���ݵ��潺
			textPrint(getMemDC(), "->", textX, textY + textInterY[6], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strMagicD1, textX + 50, textY + textInterY[6], 17, 15, "HY�߰��", COLOR_BLACK, false);	//�������潺
			textPrint(getMemDC(), "->", textX, textY + textInterY[7], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strEvation1, textX + 50, textY + textInterY[7], 17, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��
			textPrint(getMemDC(), "->", textX, textY + textInterY[8], 17, 15, "HY�߰��", COLOR_BLUE, false);		//"->"
			textPrint(getMemDC(), strMagicE1, textX + 50, textY + textInterY[8], 17, 15, "HY�߰��", COLOR_BLACK, false);	//����ȸ��
	
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

string menu::playerCommandReturn(int num)
{
	char tmpCom[32] = "";
	if (num < 0) return tmpCom;


	switch (num)
	{
		case 0:
			char tmpCom0[CHARBUFFSHORT];
			ZeroMemory(&tmpCom0, sizeof(tmpCom0));
			sprintf(tmpCom0, "%s", "Attack");

			return tmpCom0;
		break;
		case 1:
			char tmpCom1[CHARBUFFSHORT];
			ZeroMemory(&tmpCom1, sizeof(tmpCom1));
			sprintf(tmpCom1, "%s", "Magic");

			return tmpCom1;
		break;
		case 2:
			char tmpCom2[CHARBUFFSHORT];
			ZeroMemory(&tmpCom2, sizeof(tmpCom2));
			sprintf(tmpCom2, "%s", "Items");

			return tmpCom2;
		break;
		case 3:
			char tmpCom3[CHARBUFFSHORT];
			ZeroMemory(&tmpCom3, sizeof(tmpCom3));
			sprintf(tmpCom3, "%s", "Escape");

			return tmpCom3;
		break;
		case 4:
			char tmpCom4[CHARBUFFSHORT];
			ZeroMemory(&tmpCom4, sizeof(tmpCom4));
			sprintf(tmpCom4, "%s", "Transform");

			return tmpCom4;
		break;
		case 5:
			char tmpCom5[CHARBUFFSHORT];
			ZeroMemory(&tmpCom5, sizeof(tmpCom5));
			sprintf(tmpCom5, "%s", "Steal");

			return tmpCom5;
		break;
		case 6:
			char tmpCom6[CHARBUFFSHORT];
			ZeroMemory(&tmpCom6, sizeof(tmpCom6));
			sprintf(tmpCom6, "%s", "Magic Absorption");

			return tmpCom6;
		break;
		case 7:
			char tmpCom7[CHARBUFFSHORT];
			ZeroMemory(&tmpCom7, sizeof(tmpCom7));
			sprintf(tmpCom7, "%s", "Pelt");

			return tmpCom7;
		break;
	}

	return tmpCom;
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
	char saveFileNum[CHARBUFFSHORT];
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
	
		wsprintf(_playerSlot.job, "%s", INIDATA->loadDataString(saveFileNum, playerNum, "job"));					//����
		_playerSlot.level = INIDATA->loadDataInterger(saveFileNum, playerNum, "level");								//����
		if (_playerSlot.level == -1) continue; //����ó��: ������ ������ ��������...
		_playerSlot.hp = INIDATA->loadDataInterger(saveFileNum, playerNum, "hp");									//ü��
		_playerSlot.maxHp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxHp");								//�ִ� ü��
		_playerSlot.mp = INIDATA->loadDataInterger(saveFileNum, playerNum, "mp");									//����
		_playerSlot.maxMp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxMp");								//�ִ� ����
		_playerSlot.exp = INIDATA->loadDataInterger(saveFileNum, playerNum, "exp");									//����ġ
		_playerSlot.maxExp = INIDATA->loadDataInterger(saveFileNum, playerNum, "maxExp");							//�ִ� ����ġ

		_playerSlot.strength = INIDATA->loadDataInterger(saveFileNum, playerNum, "strength");						//��
		_playerSlot.speed = INIDATA->loadDataInterger(saveFileNum, playerNum, "speed");								//���ǵ�
		_playerSlot.stamina = INIDATA->loadDataInterger(saveFileNum, playerNum, "stamina");							//������
		_playerSlot.magic = INIDATA->loadDataInterger(saveFileNum, playerNum, "magic");								//������
		_playerSlot.attack = INIDATA->loadDataInterger(saveFileNum, playerNum, "attack");							//���ݷ�
		_playerSlot.attackDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "attackDefence");				//���ݵ��潺
		_playerSlot.magicDefence = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicDefence");				//�������潺
		_playerSlot.evation = INIDATA->loadDataInterger(saveFileNum, playerNum, "evation");							//����ȸ��
		_playerSlot.magicEvation = INIDATA->loadDataInterger(saveFileNum, playerNum, "magicEvation");				//����ȸ��
		_playerSlot.partyIdx = INIDATA->loadDataInterger(saveFileNum, playerNum, "partyIdx");						//��Ƽ���ѹ�

		_playerSlot.weapon    = INIDATA->loadDataInterger(saveFileNum, playerNum, "myWeapon");						//��������
		_playerSlot.armor     = INIDATA->loadDataInterger(saveFileNum, playerNum, "myArmor");						//��������
		_playerSlot.helmet    = INIDATA->loadDataInterger(saveFileNum, playerNum, "myHelmet");						//��������
		_playerSlot.subWeapon = INIDATA->loadDataInterger(saveFileNum, playerNum, "mySubWeapon");					//������������

		_playerSlot.command[0] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command0");                     //����Ŀ�ǵ�
		_playerSlot.command[1] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command1");                     //����Ŀ�ǵ�
		_playerSlot.command[2] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command2");                     //����Ŀ�ǵ�
		_playerSlot.command[3] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command3");                     //����Ŀ�ǵ�
		_playerSlot.command[4] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command4");                     //����Ŀ�ǵ�
		_playerSlot.command[5] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command5");                     //����Ŀ�ǵ�
		_playerSlot.command[6] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command6");                     //����Ŀ�ǵ�
		_playerSlot.command[7] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command7");                     //����Ŀ�ǵ�


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
			_playerSlot.weapon, _playerSlot.armor, _playerSlot.helmet, _playerSlot.subWeapon,
			_playerSlot.command[0], _playerSlot.command[1], _playerSlot.command[2], _playerSlot.command[3], _playerSlot.command[4],
			_playerSlot.command[5], _playerSlot.command[6], _playerSlot.command[7]);

		//������ ���������...
		_fileLoadOk[fileNum] = true;

		if (playerNumber != -1) break;
	}

}

//============================== player ==============================


//============================ save & load ===========================
                   
tagElements menu::saveTxtData(int fileNum, string cStage)
{
	char tmp[CHARBUFFSHORT];
	ZeroMemory(&tmp, sizeof(tmp));
	sprintf(tmp, "saveFile%d", fileNum);

	_playerElements.currentFile = tmp;
	_playerElements.currentScene = cStage;

	return _playerElements;
}


void menu::saveIniPlayerData(int fileNum, int playerNum, string cName, string job, int level, int hp, int maxHp, int mp, int maxMp,
	int exp, int maxExp, int strength, int speed, int stamina, int magic, int attack, int attackDefence, int magicDefence, int evation,
	int magicEvation, int partyIdx, int myWeapon, int myArmor, int myHelmet, int mySubWeapon, 
	int command1, int command2, int command3, int command4, int command5, int command6, int command7, int command8, 
	bool tmpSave, bool saveFile)
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
		TCHAR tmp[CHARBUFFSHORT];
		ZeroMemory(&tmp, sizeof(tmp));
		wsprintf(tmp, "%d", fileNum);
		INIDATA->addData("fileInfo", "fileNum", tmp);

		//�÷��̾� �ѹ�
		TCHAR subjectNum[CHARBUFFSHORT];
		ZeroMemory(&subjectNum, sizeof(subjectNum));
		wsprintf(subjectNum, "player%d", playerNum);
		//�÷��̾� �̸� & ����
		INIDATA->addData(subjectNum, "name", cName.c_str());
		INIDATA->addData(subjectNum, "job", job.c_str());
		//�÷��̾� ����
		TCHAR tmp1[CHARBUFFSHORT];
		ZeroMemory(&tmp1, sizeof(tmp1));
		wsprintf(tmp1, "%d", level);
		INIDATA->addData(subjectNum, "level", tmp1);
		//�÷��̾� ü��
		TCHAR tmp2[CHARBUFFSHORT];
		ZeroMemory(&tmp2, sizeof(tmp2));
		wsprintf(tmp2, "%d", hp);
		INIDATA->addData(subjectNum, "hp", tmp2);
		//�÷��̾� �ִ�ü��
		TCHAR tmp3[CHARBUFFSHORT];
		ZeroMemory(&tmp3, sizeof(tmp3));
		wsprintf(tmp3, "%d", maxHp);
		INIDATA->addData(subjectNum, "maxHp", tmp3);
		//�÷��̾� ����
		TCHAR tmp4[CHARBUFFSHORT];
		ZeroMemory(&tmp4, sizeof(tmp4));
		wsprintf(tmp4, "%d", mp);
		INIDATA->addData(subjectNum, "mp", tmp4);
		//�÷��̾� �ִ븶��
		TCHAR tmp5[CHARBUFFSHORT];
		ZeroMemory(&tmp5, sizeof(tmp5));
		wsprintf(tmp5, "%d", maxMp);
		INIDATA->addData(subjectNum, "maxMp", tmp5);
		//�÷��̾� ����ġ
		TCHAR tmp6[CHARBUFFSHORT];
		ZeroMemory(&tmp6, sizeof(tmp6));
		wsprintf(tmp6, "%d", exp);
		INIDATA->addData(subjectNum, "exp", tmp6);
		//�÷��̾� �ִ����ġ
		TCHAR tmp7[CHARBUFFSHORT];
		ZeroMemory(&tmp7, sizeof(tmp7));
		wsprintf(tmp7, "%d", maxExp);
		INIDATA->addData(subjectNum, "maxExp", tmp7);
		//�÷��̾� ��
		TCHAR tmp8[CHARBUFFSHORT];
		ZeroMemory(&tmp8, sizeof(tmp8));
		wsprintf(tmp8, "%d", strength);
		INIDATA->addData(subjectNum, "strength", tmp8);
		//�÷��̾� ���ǵ�
		TCHAR tmp9[CHARBUFFSHORT];
		ZeroMemory(&tmp9, sizeof(tmp9));
		wsprintf(tmp9, "%d", speed);
		INIDATA->addData(subjectNum, "speed", tmp9);
		//�÷��̾� ������
		TCHAR tmp10[CHARBUFFSHORT];
		ZeroMemory(&tmp10, sizeof(tmp10));
		wsprintf(tmp10, "%d", stamina);
		INIDATA->addData(subjectNum, "stamina", tmp10);
		//�÷��̾� ����
		TCHAR tmp11[CHARBUFFSHORT];
		ZeroMemory(&tmp11, sizeof(tmp11));
		wsprintf(tmp11, "%d", magic);
		INIDATA->addData(subjectNum, "magic", tmp11);
		//�÷��̾� ���ݷ�
		TCHAR tmp12[CHARBUFFSHORT];
		ZeroMemory(&tmp12, sizeof(tmp12));
		wsprintf(tmp12, "%d", attack);
		INIDATA->addData(subjectNum, "attack", tmp12);
		//�÷��̾� ���ݹ���
		TCHAR tmp13[CHARBUFFSHORT];
		ZeroMemory(&tmp13, sizeof(tmp13));
		wsprintf(tmp13, "%d", attackDefence);
		INIDATA->addData(subjectNum, "attackDefence", tmp13);
		//�÷��̾� ��������
		TCHAR tmp14[CHARBUFFSHORT];
		ZeroMemory(&tmp14, sizeof(tmp14));
		wsprintf(tmp14, "%d", magicDefence);
		INIDATA->addData(subjectNum, "magicDefence", tmp14);
		//�÷��̾� ����ȸ��
		TCHAR tmp15[CHARBUFFSHORT];
		ZeroMemory(&tmp15, sizeof(tmp15));
		wsprintf(tmp15, "%d", evation);
		INIDATA->addData(subjectNum, "evation", tmp15);
		//�÷��̾� ����ȸ��
		TCHAR tmp16[CHARBUFFSHORT];
		ZeroMemory(&tmp16, sizeof(tmp16));
		wsprintf(tmp16, "%d", magicEvation);
		INIDATA->addData(subjectNum, "magicEvation", tmp16);
		//�÷��̾� ��Ƽ�� �ѹ�
		TCHAR tmp17[CHARBUFFSHORT];
		ZeroMemory(&tmp17, sizeof(tmp17));
		wsprintf(tmp17, "%d", partyIdx);
		INIDATA->addData(subjectNum, "partyIdx", tmp17);

		//�÷��̾� ����
		TCHAR tmp18[CHARBUFFSHORT];
		ZeroMemory(&tmp18, sizeof(tmp18));
		wsprintf(tmp18, "%d", myWeapon);
		INIDATA->addData(subjectNum, "myWeapon", tmp18);
		//�÷��̾� �Ƹ�
		TCHAR tmp19[CHARBUFFSHORT];
		ZeroMemory(&tmp19, sizeof(tmp19));
		wsprintf(tmp19, "%d", myArmor);
		INIDATA->addData(subjectNum, "myArmor", tmp19);
		//�÷��̾� ���
		TCHAR tmp20[CHARBUFFSHORT];
		ZeroMemory(&tmp20, sizeof(tmp20));
		wsprintf(tmp20, "%d", myHelmet);
		INIDATA->addData(subjectNum, "myHelmet", tmp20);
		//�÷��̾� ���깫��
		TCHAR tmp21[CHARBUFFSHORT];
		ZeroMemory(&tmp21, sizeof(tmp21));
		wsprintf(tmp21, "%d", mySubWeapon);
		INIDATA->addData(subjectNum, "mySubWeapon", tmp21);

		//---------------- �÷��̾� Ŀ�ǵ� ----------------
		TCHAR tmp22[CHARBUFFSHORT];
		ZeroMemory(&tmp22, sizeof(tmp22));
		wsprintf(tmp22, "%d", command1);
		INIDATA->addData(subjectNum, "command0", tmp22);
		TCHAR tmp23[CHARBUFFSHORT];
		ZeroMemory(&tmp23, sizeof(tmp23));
		wsprintf(tmp23, "%d", command2);
		INIDATA->addData(subjectNum, "command1", tmp23);
		TCHAR tmp24[CHARBUFFSHORT];
		ZeroMemory(&tmp24, sizeof(tmp24));
		wsprintf(tmp24, "%d", command3);
		INIDATA->addData(subjectNum, "command2", tmp24);
		TCHAR tmp25[CHARBUFFSHORT];
		ZeroMemory(&tmp25, sizeof(tmp25));
		wsprintf(tmp25, "%d", command4);
		INIDATA->addData(subjectNum, "command3", tmp25);
		TCHAR tmp26[CHARBUFFSHORT];
		ZeroMemory(&tmp26, sizeof(tmp26));
		wsprintf(tmp26, "%d", command5);
		INIDATA->addData(subjectNum, "command4", tmp26);
		TCHAR tmp27[CHARBUFFSHORT];
		ZeroMemory(&tmp27, sizeof(tmp27));
		wsprintf(tmp27, "%d", command6);
		INIDATA->addData(subjectNum, "command5", tmp27);
		TCHAR tmp28[CHARBUFFSHORT];
		ZeroMemory(&tmp28, sizeof(tmp28));
		wsprintf(tmp28, "%d", command7);
		INIDATA->addData(subjectNum, "command6", tmp28);
		TCHAR tmp29[CHARBUFFSHORT];
		ZeroMemory(&tmp29, sizeof(tmp29));
		wsprintf(tmp29, "%d", command8);
		INIDATA->addData(subjectNum, "command7", tmp29);
		//------------------------------------------------

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
			TCHAR tmp2[CHARBUFFSHORT];
			ZeroMemory(&tmp2, sizeof(tmp2));
			wsprintf(tmp2, "%d", gil);
			INIDATA->addData("Inventory", "Gil", tmp2);

			char tmpPlayerX[CHARBUFFSHORT];
			ZeroMemory(&tmpPlayerX, sizeof(tmpPlayerX));
			sprintf(tmpPlayerX, "%ld", _wM->getworldMapPlayer()->getWorldMapPlayerPoint().x);    //�÷��̾�X
			INIDATA->addData("gameData", "playerX", tmpPlayerX);

			char tmpPlayerY[CHARBUFFSHORT];
			ZeroMemory(&tmpPlayerY, sizeof(tmpPlayerY));
			sprintf(tmpPlayerY, "%ld", _wM->getworldMapPlayer()->getWorldMapPlayerPoint().y);    //�÷��̾�Y
			INIDATA->addData("gameData", "playerY", tmpPlayerY);

			char tmpSaveScene[CHARBUFFSHORT];
			ZeroMemory(&tmpSaveScene, sizeof(tmpSaveScene));
			sprintf(tmpSaveScene, "%s", _currentSceneName.c_str());								 //���̺�����Ʈ��
			INIDATA->addData("gameData", "saveScene", tmpSaveScene);
		}

		//�÷��� �ð�
		TCHAR tmp3[CHARBUFFSHORT];
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
			tmpPlayrInfo.playerInfo.command[0], tmpPlayrInfo.playerInfo.command[1], tmpPlayrInfo.playerInfo.command[2], tmpPlayrInfo.playerInfo.command[3],
			tmpPlayrInfo.playerInfo.command[4], tmpPlayrInfo.playerInfo.command[5], tmpPlayrInfo.playerInfo.command[6], tmpPlayrInfo.playerInfo.command[7],
			true, false);


		if (i == 3)
		{
			char tmpGil[CHARBUFFSHORT];
			ZeroMemory(&tmpGil, sizeof(tmpGil));
			sprintf(tmpGil, "%d", tmpPlayrInfo.gil);

			char tmpTime[CHARBUFFSHORT];
			ZeroMemory(&tmpTime, sizeof(tmpTime));
			sprintf(tmpTime, "%f", _gameTotalTime);

			INIDATA->addData("gameData", "stage", tmpPlayrInfo.stage);
			INIDATA->addData("Inventory", "Gil", tmpGil);
			INIDATA->addData("gameData", "playTime", tmpTime);

			char tmpPlayerX[CHARBUFFSHORT];
			ZeroMemory(&tmpPlayerX, sizeof(tmpPlayerX));
			sprintf(tmpPlayerX, "%ld", tmpPlayrInfo.playerXY.x);							//�÷��̾�X
			INIDATA->addData("gameData", "playerX", tmpPlayerX);

			char tmpPlayerY[CHARBUFFSHORT];
			ZeroMemory(&tmpPlayerY, sizeof(tmpPlayerY));
			sprintf(tmpPlayerY, "%ld", tmpPlayrInfo.playerXY.y);							//�÷��̾�Y
			INIDATA->addData("gameData", "playerY", tmpPlayerY);

			char tmpSaveScene[CHARBUFFSHORT];
			ZeroMemory(&tmpSaveScene, sizeof(tmpSaveScene));
			sprintf(tmpSaveScene, "%s", tmpPlayrInfo.saveScene);							//���̺�����Ʈ��
			INIDATA->addData("gameData", "saveScene", tmpSaveScene);

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
			tmpPlayrInfo.playerInfo.command[0], tmpPlayrInfo.playerInfo.command[1], tmpPlayrInfo.playerInfo.command[2], tmpPlayrInfo.playerInfo.command[3],
			tmpPlayrInfo.playerInfo.command[4], tmpPlayrInfo.playerInfo.command[5], tmpPlayrInfo.playerInfo.command[6], tmpPlayrInfo.playerInfo.command[7],
			false, false);


		char saveFileNum[CHARBUFFSHORT];
		ZeroMemory(&saveFileNum, sizeof(saveFileNum));
		sprintf(saveFileNum, "saveFile%d", fileNum);
		//INIDATA->iniSave(saveFileNum);

		if (i == 3)
		{
			//���ӵ�����
			char tmpGil[CHARBUFFSHORT];
			ZeroMemory(&tmpGil, sizeof(tmpGil));
			sprintf(tmpGil, "%d", tmpPlayrInfo.gil);

			char tmpTime[CHARBUFFSHORT];
			ZeroMemory(&tmpTime, sizeof(tmpTime));
			sprintf(tmpTime, "%d", tmpPlayrInfo.playTime);

			INIDATA->addData("gameData", "stage", tmpPlayrInfo.stage);
			INIDATA->addData("Inventory", "Gil", tmpGil);
			INIDATA->addData("gameData", "playTime", tmpTime);

			char tmpPlayerX[CHARBUFFSHORT];
			ZeroMemory(&tmpPlayerX, sizeof(tmpPlayerX));
			sprintf(tmpPlayerX, "%ld", tmpPlayrInfo.playerXY.x);			//�÷��̾�X
			INIDATA->addData("gameData", "playerX", tmpPlayerX);

			char tmpPlayerY[CHARBUFFSHORT];
			ZeroMemory(&tmpPlayerY, sizeof(tmpPlayerY));
			sprintf(tmpPlayerY, "%ld", tmpPlayrInfo.playerXY.y);			//�÷��̾�Y
			INIDATA->addData("gameData", "playerY", tmpPlayerY);

			char tmpSaveScene[CHARBUFFSHORT];
			ZeroMemory(&tmpSaveScene, sizeof(tmpSaveScene));
			sprintf(tmpSaveScene, "%s", tmpPlayrInfo.saveScene);			//���̺�����Ʈ��
			INIDATA->addData("gameData", "saveScene", tmpSaveScene);

			INIDATA->iniSave(saveFileNum);

			//������
			itemDataLoad(fileNum);
		}
	}
}

tagSaveData menu::loadIniPlayerData(int fileNum, int playerNumber, bool tmpFile)
{
	//���̺����� �ѹ�
	char saveFileNum[CHARBUFFSHORT];
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
	char playerNum[CHARBUFFSHORT];
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
	tmpPlayrInfo.playerInfo.weapon	  = INIDATA->loadDataInterger(saveFileNum, playerNum, "myWeapon");					//����
	tmpPlayrInfo.playerInfo.armor	  = INIDATA->loadDataInterger(saveFileNum, playerNum, "myArmor");					//���� 
	tmpPlayrInfo.playerInfo.helmet	  = INIDATA->loadDataInterger(saveFileNum, playerNum, "myHelmet");					//����  
	tmpPlayrInfo.playerInfo.subWeapon = INIDATA->loadDataInterger(saveFileNum, playerNum, "mySubWeapon");				//�������� 

	tmpPlayrInfo.playerInfo.command[0] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command0");					//Ŀ�ǵ�
	tmpPlayrInfo.playerInfo.command[1] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command1");					//Ŀ�ǵ�
	tmpPlayrInfo.playerInfo.command[2] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command2");					//Ŀ�ǵ� 
	tmpPlayrInfo.playerInfo.command[3] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command3");					//Ŀ�ǵ� 
	tmpPlayrInfo.playerInfo.command[4] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command4");					//Ŀ�ǵ� 
	tmpPlayrInfo.playerInfo.command[5] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command5");					//Ŀ�ǵ� 
	tmpPlayrInfo.playerInfo.command[6] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command6");					//Ŀ�ǵ� 
	tmpPlayrInfo.playerInfo.command[7] = INIDATA->loadDataInterger(saveFileNum, playerNum, "command7");					//Ŀ�ǵ� 

	wsprintf(tmpPlayrInfo.stage, "%s", INIDATA->loadDataString(saveFileNum, "gameData", "stage"));                      //��������  
	tmpPlayrInfo.gil = INIDATA->loadDataInterger(saveFileNum, "Inventory", "Gil");										//��  
	tmpPlayrInfo.playTime = INIDATA->loadDataInterger(saveFileNum, "gameData", "playTime");								//�÷��̽ð�  

	tmpPlayrInfo.playerXY.x = INIDATA->loadDataInterger(saveFileNum, "gameData", "playerX");							//�÷��̾� ��ġX
	tmpPlayrInfo.playerXY.y = INIDATA->loadDataInterger(saveFileNum, "gameData", "playerY");							//�÷��̾� ��ġY
	wsprintf(tmpPlayrInfo.saveScene, "%s", INIDATA->loadDataString(saveFileNum, "gameData", "saveScene"));              //�����  

	return tmpPlayrInfo;
}

//============================ save & load ===========================


//============================== gameData ============================

void menu::saveIniGameData(int fileNum, string currentScene)
{
	//���̺� ���ϳѹ�
	TCHAR tmp1[CHARBUFFSHORT];
	ZeroMemory(&tmp1, sizeof(tmp1));
	wsprintf(tmp1, "%d", fileNum);
	INIDATA->addData("gameData", "fileNum", tmp1);

	//���������̸�
	TCHAR saveFileName[CHARBUFFSHORT];
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
				char tmpSaveFileNum[CHARBUFFSHORT];
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
		char tmpBuff[CHARBUFFSHORT];
		textPrint(getMemDC(), tmpGD.stage,					     1050, 392, 30, 30, "Stencil", COLOR_WHITE, true);
		textPrint(getMemDC(), itoa(tmpGD.gil, tmpBuff, 10),		 1080, 516, 20, 20, "Stencil", COLOR_WHITE, true);
		if (SCENEMANAGER->getCurrentSceneName() != "�ɼ�" && SCENEMANAGER->getCurrentSceneName() != "������" &&
			SCENEMANAGER->getCurrentSceneName() != "���")
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
					char saveFile[CHARBUFFSHORT];
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
					char saveFile[CHARBUFFSHORT];
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
					char saveFile[CHARBUFFSHORT];
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
	char saveFileNum[CHARBUFFSHORT];
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

int menu::itemGetNum(int num)
{
	for (int i = 0; i < _iM->getVItem().size(); ++i)
	{
		if (_iM->getVItem()[i]->getItemNumber() == num)
		{
			return i;
		}
	}

	return NULL;
}

//================================ item ==============================


//================================ timer =============================

void menu::gamePlayTime(float getSaveTime, bool fileLoadTime)
{

	TCHAR str[CHARBUFFSHORT];
	if (fileLoadTime)
	{
		sprintf_s(str, "%f", getSaveTime);
	}
	else
	{
		sprintf_s(str, "%f", _gameTotalTime);
	}

	//Ÿ�̸� �����ġ
	int timerX = 1070;
	int timerY = 462;

	if (fileLoadTime)
	{
		//1��
		sprintf_s(str, "%d", (int)(getSaveTime / 60) % 10);
		textPrint(getMemDC(), str, timerX, timerY, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)getSaveTime / 600);
		textPrint(getMemDC(), str, timerX - 10, timerY, 20, 20, "Stencil", COLOR_WHITE, true);

		//1��
		sprintf_s(str, "%d", (int)getSaveTime % 10);
		textPrint(getMemDC(), str, timerX + 30, timerY, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)(getSaveTime / 10) % 6);
		textPrint(getMemDC(), str, timerX + 20, timerY, 20, 20, "Stencil", COLOR_WHITE, true);

		sprintf_s(str, ":", str);
		textPrint(getMemDC(), str, timerX + 10, timerY - 1, 20, 20, "Stencil", COLOR_WHITE, true);
	}
	else
	{
		//1��
		sprintf_s(str, "%d", (int)(_gameTotalTime / 60) % 10);
		textPrint(getMemDC(), str, timerX, timerY, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)_gameTotalTime / 600);
		textPrint(getMemDC(), str, timerX - 10, timerY, 20, 20, "Stencil", COLOR_WHITE, true);

		//1��
		sprintf_s(str, "%d", (int)_gameTotalTime % 10);
		textPrint(getMemDC(), str, timerX + 30, timerY, 20, 20, "Stencil", COLOR_WHITE, true);
		//10��
		sprintf_s(str, "%d", (int)(_gameTotalTime / 10) % 6);
		textPrint(getMemDC(), str, timerX + 20, timerY, 20, 20, "Stencil", COLOR_WHITE, true);

		sprintf_s(str, ":", str);
		textPrint(getMemDC(), str, timerX + 10, timerY - 1, 20, 20, "Stencil", COLOR_WHITE, true);
	}

}

//================================ timer =============================