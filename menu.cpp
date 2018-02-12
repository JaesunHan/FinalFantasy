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
			_cursor.currentNum = 0;
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
			_cursor.currentNum = downNumber - 1;
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




//=============================== text ===============================

//                   폰트SIZE       폰트굵기       폰트명          입력할텍스트     텍스트위치 XY		  텍스트색상(기본흰색)  텍스트 중앙정렬 
void menu::textPrint(int fontWidth, int fontThick, char* fontName, char* textInput, int textX, int textY, COLORREF RGB, BOOL textCenter)
{
	//----------------------------------- 폰트셋팅
	HFONT font, oldFont;
	SetBkMode(getMemDC(), TRANSPARENT);                  //문자 투명배경
	if (textCenter) SetTextAlign(getMemDC(), TA_CENTER); //문자 중앙정렬
	SetTextColor(getMemDC(), RGB);                       //문자 색상변경
	font = CreateFont(fontWidth, 0, 0, 0, fontThick, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, TEXT(fontName));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	//----------------------------------- 문자출력
	char str[256];
	ZeroMemory(&str, sizeof(str));
	sprintf(str, "%s", textInput);
	TextOut(getMemDC(), textX, textY, str, strlen(str));
	//----------------------------------- 이전 설정으로 복구
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
	SetTextColor(getMemDC(), COLOR_BLACK);
	SetTextAlign(getMemDC(), TA_LEFT);
}

//string_to_char
char* menu::s2c(string str)
{
	char tempName[256];
	ZeroMemory(tempName, sizeof(tempName));
	sprintf(tempName, "%s", str);

	return tempName;
}

//int_to_char
char* menu::i2c(int i)
{
	char tempNum[256];
	ZeroMemory(tempNum, sizeof(tempNum));
	sprintf(tempNum, "%d", i);

	return tempNum;
}

//=============================== text ===============================

//============================== player ==============================

//                        이미지키값      이미지위치XY      레벨	   직업	       체력    최대체력   마력    최대마력
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

	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		_vPlayer[i].y += slotValueY * slotNum;
	}
}

void menu::playerSlotRender()	 
{
	for (int i = 0; i < _vPlayer.size(); ++i)
	{
		_vPlayer[i].img->render(getMemDC(), _vPlayer[i].x, _vPlayer[i].y);

		textPrint(20, 20, "HY견고딕", s2c(_vPlayer[i].name), _vPlayer[i].x + 100, _vPlayer[i].y - 50, COLOR_WHITE);				//이름
		textPrint(20, 20, "HY견고딕", s2c(_vPlayer[i].job), _vPlayer[i].x + 200, _vPlayer[i].y - 50, COLOR_WHITE);				//직업
		textPrint(20, 20, "HY견고딕", "LV", _vPlayer[i].x + 100, _vPlayer[i].y - 40, COLOR_BLUE);								//"LV"
		textPrint(20, 20, "HY견고딕", i2c(_vPlayer[i].level), _vPlayer[i].x + 100, _vPlayer[i].y - 40, COLOR_BLUE);				//레벨
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


