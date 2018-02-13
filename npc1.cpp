#include "stdafx.h"
#include "npc1.h"


npc1::npc1()
{
}


npc1::~npc1()
{
}

HRESULT npc1::init(int npcX, int npcY)
{
	//npc1번 이미지 추가
	_image = IMAGEMANAGER->addFrameImage("1번npc", ".\\image\\NPC\\npc1_front.bmp", 96, 48, 3, 1, true, RGB(255, 0, 255));

	_npc.x = npcX;
	_npc.y = npcY;

	_rc = RectMake(_npc.x, _npc.y+30, TILE_SIZEX, TILE_SIZEY/2);

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;

	_npctype = NPC_POTION;

	return S_OK;
}

void npc1::release()
{
}

void npc1::update()
{
	worldNpcImageFrameControl();
}

void npc1::render()
{
	_image->frameRender(getMemDC(), _npc.x, _npc.y, _npcCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void npc1::worldNpcImageFrameControl()
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
