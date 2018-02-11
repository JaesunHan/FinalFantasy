#include "stdafx.h"
#include "menu.h"


menu::menu()
	: _buttonNum(0)
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
	buttonRender();
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
	_cursor.currentNum = 0;
	_cursor.cursorOn = false;

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

//                          Ŀ��Y�� �̵���    �̵�Ƚ��
void menu::cursorKeyControl(float downValueY, int downNumber)
{
	if (!_cursor.cursorOn)
	{
		_cursor.currentNum = 0;
		_cursor.cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_cursor.y += downValueY;
		_cursor.currentNum++;

		//����ó��: Ŀ���� �����׸��� ����� �ٽ� ó�� ��������~~
		if (_cursor.y > _cursor.startY + (downValueY * (downNumber - 1)))
		{
			_cursor.y = _cursor.startY;
			_cursor.currentNum = downNumber - 1;
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_cursor.y -= downValueY;
		_cursor.currentNum--;

		//����ó��: Ŀ���� �����׸��� ����� ������ ��������~~
		if (_cursor.y < _cursor.startY)
		{
			_cursor.y = _cursor.startY + (downValueY * (downNumber - 1));
			_cursor.currentNum = 0;
		}
	}


	//����ó��: Ŀ�� ������ġ ��ȯ�� ����...
	if (_cursor.currentNum <= 0)				_cursor.currentNum = 0;
	if (_cursor.currentNum >= (downNumber - 1)) _cursor.currentNum = (downNumber - 1);
}

void  menu::cursorRender()
{
	_cursor.img->frameRender(getMemDC(), _cursor.x, _cursor.y);
}
//============================== cursor ==============================


//============================== button ==============================
//                   ��ư�̹��� Ű��  ��ġXY
void menu::buttonInit(string keyName, float x, float y)
{
	//-------------------------------------------- keyName ����ȯ
	char temp[128];
	ZeroMemory(temp, sizeof(temp));
	sprintf(temp, "%s", keyName.c_str());
	//--------------------------------------------
	//-------------------------------------------- animationKeyName
	char aniTemp[32];
	ZeroMemory(aniTemp, sizeof(aniTemp));
	sprintf(aniTemp, "%s%d", "��ư����", _buttonNum);
	//--------------------------------------------

	ZeroMemory(&_button, sizeof(_button));
	_button.img = IMAGEMANAGER->findImage(keyName);
	_button.x = x;
	_button.y = y;
	_button.aniStart = false;
	_button.ani = new animation;
	int arrAni[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation(aniTemp, temp, arrAni, 2, 2, true);
	_button.ani = KEYANIMANAGER->findAnimation(aniTemp);

	_vButton.push_back(_button);

	_buttonNum++;
}

void menu::buttonUpdate()
{
	for (int i = 0; i < _vButton.size(); ++i)
	{
		if (_vButton[i].aniStart)  //���ϸ��̼� Play
		{
			if (!_vButton[i].ani->isPlay()) _vButton[i].ani->start();
		}
		else  //���ϸ��̼� Stop
		{
			if (_vButton[i].ani->isPlay()) _vButton[i].ani->stop();
		}
	}


	KEYANIMANAGER->update();
}

void menu::buttonRender()
{
	for (int i = 0; i < _vButton.size(); ++i)
	{
		_vButton[i].img->aniRender(getMemDC(), _vButton[i].x, _vButton[i].y, _vButton[i].ani);
	}
}

void menu::buttonRemove()
{
	if (_vButton.size() != 0)
	{
		for (int i = 0; i < _vButton.size(); ++i)
		{
			_vButton.erase(_vButton.begin() + i);
		}
	}

	_vButton.clear();
}
//============================== button ==============================

