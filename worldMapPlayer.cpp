#include "stdafx.h"
#include "worldMapPlayer.h"


worldMapPlayer::worldMapPlayer()
{
}


worldMapPlayer::~worldMapPlayer()
{
}

HRESULT worldMapPlayer::init(int playerX, int playerY)
{
	_image = IMAGEMANAGER->addFrameImage("월드맵플레이어", ".//image//playerImg//player1Move.bmp", 84, 184, 3, 4, true, RGB(255, 0, 255));
	
	_player.x = playerX;
	_player.y = playerY;

	_rc = RectMakeCenter(_player.x, _player.y, _image->getFrameWidth(), _image->getFrameHeight());

	_currentFrameX = 0;
	_currentFrameY = 0;

	_moveSpeed = 2.0f;

	_worldPlayerDirection = WPDOWN;

	return S_OK;
}

void worldMapPlayer::release()
{
}

void worldMapPlayer::update()
{
	worldPlayerImageFrameControl();
	worldPlayerKeyControl();

}

void worldMapPlayer::render()
{
	worldPlayerImageControl();
	//IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(),_player.x, _player.y, _currentFrameX, _currentFrameY);
}

void worldMapPlayer::worldPlayerImageFrameControl()
{

	_count++;

	if (_count % 10 == 0)
	{
		_currentFrameX += 1;
		
		if (_currentFrameX == _image->getMaxFrameX())
		{
			_currentFrameX = 0;
		}
	}
}

void worldMapPlayer::worldPlayerImageControl()
{
	switch (_worldPlayerDirection)
	{
		case WPRIGHT: _currentFrameY = 3;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;

		case WPLEFT: _currentFrameY = 2;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;

		case WPUP: _currentFrameY = 1;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;
				
		case WPDOWN: _currentFrameY = 0;
			IMAGEMANAGER->findImage("월드맵플레이어")->frameRender(getMemDC(), _player.x, _player.y, _currentFrameX, _currentFrameY);
		break;
	}


}

void worldMapPlayer::worldPlayerKeyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_worldPlayerDirection = WPLEFT;
		_player.x -= _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_worldPlayerDirection = WPRIGHT;
		_player.x += _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_worldPlayerDirection = WPUP;
		_player.y -= _moveSpeed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_worldPlayerDirection = WPDOWN;
		_player.y += _moveSpeed;
	}

}
