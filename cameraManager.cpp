#include "stdafx.h"
#include "cameraManager.h"
#include "tile.h"

cameraManager::cameraManager()
{
}


cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init(HDC hdc)
{
	_memBuffer = NULL;

	_mapTotalSize = PointMake(0, 0);
	_tileSize = PointMake(0, 0);
	_dcTileNum = PointMake(0, 0);
	_move = PointMake(0, 0);
	_hdc = hdc;

	return S_OK;
}

void cameraManager::release(void)
{
	delete _memBuffer;
}

void cameraManager::update(void)
{

}

void cameraManager::render(HDC hdc)
{
	//PatBlt(_memBuffer->getMemDC(), 0, 0, _memBuffer->getWidth(), _memBuffer->getHeight(), BLACKNESS);
	//================== 이 위는 손대지 마시오 =========================

	

	this->_memBuffer->render(hdc, 0, 0, 0, 0, _tileSize.x * _dcTileNum.x, _tileSize.y * _dcTileNum.y);//hdc영역에 그려준다 

}

void cameraManager::createDC(POINT tileSize, POINT tileNum)
{
	//if (_memBuffer != NULL) delete _memBuffer;

	this->release();

	_tileSize = tileSize;
	_dcTileNum = tileNum;

	_memBuffer = new image;
	_memBuffer->init(_tileSize.x * (_dcTileNum.x + 2), _tileSize.y * (_dcTileNum.y + 2));

}