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

//                          커서Y축 이동값    이동횟수
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

		//예외처리: 커서가 선택항목을 벗어나면 다시 처음 선택지로~~
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

		//예외처리: 커서가 선택항목을 벗어나면 마지막 선택지로~~
		if (_cursor.y < _cursor.startY)
		{
			_cursor.y = _cursor.startY + (downValueY * (downNumber - 1));
			_cursor.currentNum = 0;
		}
	}


	//예외처리: 커서 선택위치 반환을 위한...
	if (_cursor.currentNum <= 0)				_cursor.currentNum = 0;
	if (_cursor.currentNum >= (downNumber - 1)) _cursor.currentNum = (downNumber - 1);
}

void  menu::cursorRender()
{
	_cursor.img->frameRender(getMemDC(), _cursor.x, _cursor.y);
}

//============================== cursor ==============================


//============================== button ==============================

//                   버튼이미지 키값  위치XY
void menu::buttonInit(string keyName, float x, float y)
{
	//-------------------------------------------- keyName 형변환
	char temp[128];
	ZeroMemory(temp, sizeof(temp));
	sprintf(temp, "%s", keyName.c_str());
	//--------------------------------------------

	//-------------------------------------------- animationKeyName
	char aniTemp[32];
	ZeroMemory(aniTemp, sizeof(aniTemp));
	sprintf(aniTemp, "%s%d", "버튼시작", _buttonNum);
	//--------------------------------------------

	tagButton _button;
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
		if (_vButton[i].aniStart)  //에니메이션 Play
		{
			if (!_vButton[i].ani->isPlay()) _vButton[i].ani->start();
		}
		else  //에니메이션 Stop
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


//=============================== text ===============================

//                   폰트SIZE        폰트굵기       폰트명          입력할텍스트     텍스트위치 XY        텍스트색상(기본흰색)  
void menu::textPrint(int fontWidth, int fontThick, char* fontName, char* textInput, int textX, int textY, COLORREF RGB)
{
	//----------------------------------- 폰트셋팅
	char str[256];
	HFONT font, oldFont;
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB);
	font = CreateFont(fontWidth, 0, 0, 0, fontThick, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT(fontName));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	//----------------------------------- 문자출력
	sprintf(str, textInput);
	TextOut(getMemDC(), textX, textY, str, strlen(str));
	//----------------------------------- 이전 설정으로 복구
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetTextColor(getMemDC(), COLOR_BLACK);
}

//=============================== text ===============================

//============================== player ==============================

//void menu::playerInit()
//{
//	
//	tagPlayer player;
//	ZeroMemory(&player, sizeof(player));
//	player.hp = 0;
//
//}

//============================== player ==============================