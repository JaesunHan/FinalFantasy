#include "stdafx.h"
#include "npc4.h"


npc4::npc4()
{
}


npc4::~npc4()
{
}

HRESULT npc4::init(int npcX, int npcY)
{
	//npc4번 이미지 추가
	_image = IMAGEMANAGER->addFrameImage("4번npc", ".\\image\\NPC\\npc4_front.bmp", 96, 48, 3, 1, true, RGB(255, 0, 255));

	_npc.x = npcX;
	_npc.y = npcY;

	_rc = RectMake(_npc.x, _npc.y + 30, TILE_SIZEX, TILE_SIZEY / 2);

	_npcCurrentFrameX = 0;
	_npcCurrentFrameY = 0;


	return S_OK;
}

void npc4::release()
{
}

void npc4::update()
{
	worldNpcImageFrameControl();
}

void npc4::render()
{
	IMAGEMANAGER->findImage("4번npc")->frameRender(getMemDC(), _npc.x, _npc.y, _npcCurrentFrameX, 0);
	if (_isDebug)
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}
void npc4::worldNpcImageFrameControl()
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
