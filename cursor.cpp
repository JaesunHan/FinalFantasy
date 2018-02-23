#include "stdafx.h"
#include "cursor.h"


cursor::cursor()
{
}


cursor::~cursor()
{
}

//============================== cursor ==============================

//                     커서형태(L,R)     커서위치X     커서위치Y
void cursor::init(CURSOR_DIRECTION type, float startX, float startY)
{
	_type = type;

	_img = IMAGEMANAGER->findImage("선택커서");
	_x = startX;
	_y = startY;
	_speed = 1.0f;
	_fForce = 0.01f;
	_startX = _x;
	_startY = _y;
	_minX = 0;
	_maxX = 0;
	_currentXNum = 0;
	_currentYNum = 0;
	_currentPos = 0;
	_cursorOn = false;
	_cursorReset = false;

	switch (_type)
	{
	case CURSOR_LEFT:
		_img->setFrameX(1);
		break;
	case CURSOR_RIGHT:
		_img->setFrameX(0);
		break;
	}
}

void cursor::update()
{
	switch (_type)
	{
	case CURSOR_LEFT:
		//처음 위치로
		if (_x > _startX)
		{
			_x = _startX;
			_fForce = 0.01f;
			_speed = 1.0f;
		}

		//커서 움직임
		_fForce += 0.001f;
		_speed -= _fForce;
		_x -= _speed;
		break;
	case CURSOR_RIGHT:
		//처음 위치로
		if (_x < _startX)
		{
			_x = _startX;
			_fForce = 0.01f;
			_speed = 1.0f;
		}

		//커서 움직임
		_fForce += 0.001f;
		_speed -= _fForce;
		_x += _speed;
		break;
	}
}

//                           커서X축 이동값    이동횟수
void cursor::keyControlX(float moveValueX, int moveNumber, bool leftMove)
{
	if (!_cursorOn)
	{
		if (!leftMove)
		{
			_minX = _x;
			_maxX = _x + (moveValueX * (moveNumber - 1));
		}
		else
		{
			_minX = _x - (moveValueX * (moveNumber - 1));
			_maxX = _x;
		}

		_currentXNum = 0;
		_cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_x += moveValueX;
		_startX += moveValueX;
		_currentXNum++;

		//예외처리: 커서가 선택항목을 벗어나면 다시 처음 선택지로~~
		if (_currentXNum > (moveNumber - 1))
		{
			_x = _minX;
			_startX = _minX;
			_currentXNum = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_x -= moveValueX;
		_startX -= moveValueX;
		_currentXNum--;

		//예외처리: 커서가 선택항목을 벗어나면 마지막 선택지로~~
		if (_x < _minX)
		{
			_x = _maxX;
			_startX = _maxX;
			_currentXNum = (moveNumber - 1);
		}

	}


	//예외처리: 커서 선택위치 반환을 위한...
	if (_currentXNum <= 0)					_currentXNum = 0;
	if (_currentXNum >= (moveNumber))		_currentXNum = (moveNumber - 1);
}

//                          커서Y축 이동값    이동횟수
void cursor::keyControlY(float moveValueY, int downNumber)
{
	if (!_cursorOn)
	{
		_currentYNum = 0;
		_cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_y += moveValueY;
		_currentYNum++;

		//예외처리: 커서가 선택항목을 벗어나면 다시 처음 선택지로~~
		if (_y > _startY + (moveValueY * (downNumber - 1)))
		{
			_y = _startY;
			_currentYNum = 0;
		}

	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		_y -= moveValueY;
		_currentYNum--;

		//예외처리: 커서가 선택항목을 벗어나면 마지막 선택지로~~
		if (_y < _startY)
		{
			_y = _startY + (moveValueY * (downNumber - 1));
			_currentYNum = downNumber - 1;
		}
	}


	//예외처리: 커서 선택위치 반환을 위한...
	if (_currentYNum <= 0)				 _currentYNum = 0;
	if (_currentYNum >= (downNumber - 1)) _currentYNum = (downNumber - 1);
}

void cursor::keyControlXY(float moveValueX, float moveValueY, int maxNumX, int maxListNum, bool leftMove)
{
	if (maxNumX > maxListNum) maxNumX = maxListNum;
	if (maxListNum <= 0) return;

	if (!_cursorOn)
	{
		if (!leftMove)
		{
			_minX = _x;
			_maxX = _x + (moveValueX * (maxNumX - 1));
		}
		else
		{
			_minX = _x - (moveValueX * (maxNumX - 1));
			_maxX = _x;
		}

		_currentPos = 0;
		_cursorOn = true;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		if (_currentPos % maxNumX == (maxNumX - 1) || _currentPos == maxListNum - 1) _currentPos = (_currentPos / maxNumX) * maxNumX;
		else _currentPos++;
	
		_x = _minX + moveValueX * (_currentPos % maxNumX);
		_startX = _x;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		if (_currentPos % maxNumX == 0)
		{
			_currentPos += (maxNumX - 1);
			if (_currentPos > maxListNum - 1) _currentPos = maxListNum - 1;
		}
		else _currentPos--;

		_x = _minX + moveValueX * (_currentPos % maxNumX);
		_startX = _x;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		if (_currentPos + maxNumX > maxListNum - 1) _currentPos %= maxNumX;
		else _currentPos += maxNumX;

		_y = _startY + moveValueY * (_currentPos / maxNumX);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		SOUNDMANAGER->play("menuSelectLow", CH_MENUSCENE, EFFECTVOLUME);

		//예외처리: 커서가 선택항목을 벗어나면 마지막 선택지로~~
		if (_currentPos - maxNumX < 0)
		{
			_currentPos += (maxListNum / maxNumX) * maxNumX;
			if (_currentPos > maxListNum - 1) _currentPos -= maxNumX;
		}
		else _currentPos -= maxNumX;

		_y = _startY + moveValueY * (_currentPos / maxNumX);
	}
}

void cursor::render()
{
	_img->frameRender(getMemDC(), _x, _y);
}

void cursor::resetXY(float cursorX, float cursorY)
{
	_cursorReset = true;

	_x = _startX = cursorX;
	_y = _startY = cursorY;
}
void cursor::resetCursorPos()
{
	_currentPos = 0;
	
	_x = _minX;
	_startX = _x;
	_y = _startY;
}
//============================== cursor ==============================
