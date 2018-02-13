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
		_cursor.maxX = _cursor.x + (moveValueX * (moveNumber));

		_cursor.currentXNum = 0;
		_cursor.cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_cursor.x += moveValueX;
		_cursor.startX += moveValueX;
		_cursor.currentXNum++;

		//����ó��: Ŀ���� �����׸��� ����� �ٽ� ó�� ��������~~
		if (_cursor.x > _cursor.maxX)
		{
			_cursor.x = _cursor.minX;
			_cursor.startX = _cursor.minX;
			_cursor.currentXNum = 0;
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_cursor.x -= moveValueX;
		_cursor.startX -= moveValueX;
		_cursor.currentXNum--;

		//����ó��: Ŀ���� �����׸��� ����� ������ ��������~~
		if (_cursor.x < _cursor.minX)
		{
			_cursor.x = _cursor.maxX;
			_cursor.startX = _cursor.maxX;
			_cursor.currentXNum = moveNumber;
		}
	}


	//����ó��: Ŀ�� ������ġ ��ȯ�� ����...
	if (_cursor.currentXNum <= 0)					_cursor.currentXNum = 0;
	if (_cursor.currentXNum >= (moveNumber))		_cursor.currentXNum = (moveNumber);
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

//                        �̹���Ű��      �̹�����ġXY      ����	   ����	       ü��    �ִ�ü��   ����    �ִ븶��
void menu::playerSlotInit(string keyName, float x, float y, int level, string job, int hp, int maxHp, int mp, int maxMp)
{
	tagPlayer player;
	ZeroMemory(&player, sizeof(player));

	player.img = IMAGEMANAGER->findImage(keyName);
	player.name = keyName;
	player.x = x;
	player.y = y;
	player.level = level;
	player.hp = hp;
	player.maxHp = maxHp;
	player.mp = mp;
	player.maxMp = maxMp;
	player.job = job;

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
		_vPlayer[i].img->render(getMemDC(), _vPlayer[i].x, _vPlayer[i].y);

		textPrint(getMemDC(), s2c(_vPlayer[i].name), _vPlayer[i].x + 100, _vPlayer[i].y - 50);				//�̸�
		textPrint(getMemDC(), s2c(_vPlayer[i].job), _vPlayer[i].x + 200, _vPlayer[i].y - 50);				//����
		textPrint(getMemDC(), "LV", _vPlayer[i].x + 100, _vPlayer[i].y - 40, COLOR_BLUE);					//"LV"
		textPrint(getMemDC(), i2c(_vPlayer[i].level), _vPlayer[i].x + 100, _vPlayer[i].y - 40, COLOR_BLUE);	//����
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

//============================== player ==============================


