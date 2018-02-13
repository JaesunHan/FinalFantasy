#include "stdafx.h"
#include "npc2.h"


npc2::npc2()
{
}


npc2::~npc2()
{
}

HRESULT npc2::init(int npcX, int npcY)
{
	//npc2번 이미지 추가
	_image = IMAGEMANAGER->addFrameImage("2번npc", ".\\image\\NPC\\npc2_front.bmp", 90, 48, 3, 1, true, RGB(255, 0, 255));

	_npc.x = npcX;
	_npc.y = npcY;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;


	return S_OK;
}

void npc2::release()
{
}

void npc2::update()
{
	worldNpcImageFrameControl();
}

void npc2::render()
{
	IMAGEMANAGER->findImage("2번npc")->frameRender(getMemDC(), _npc.x, _npc.y, _npcCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void npc2::worldNpcImageFrameControl()
{
	_count++;

	if (_count % 50 == 0)
	{
		_npcCurrentFrameX++;

		if (_npcCurrentFrameX == _image->getMaxFrameX())
		{
			_npcCurrentFrameX = 0;
		}
	}
}
