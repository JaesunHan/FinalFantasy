#pragma once
#include "singletonBase.h"

class tile;

class cameraManager : public singletonBase<cameraManager>
{
private:
	image* _memBuffer;

	POINT _mapTotalSize;

	POINT _tileSize;
	POINT _dcTileNum;
	POINT _move;

	HDC _hdc;

public:
	cameraManager();
	~cameraManager();

	HRESULT init(HDC hdc);
	void release(void);
	void update(void);
	void render(HDC hdc);

	void createDC(POINT tileSize, POINT tileNum);
	
	inline void setMovePt(POINT pt) { _move = pt; }
	inline POINT getMovePt(void) { return _move; }

	inline int getDcWidth(void) { return _tileSize.x * _dcTileNum.x; }
	inline int getDcHeight(void) { return _tileSize.y * _dcTileNum.y; }

	inline HDC getCameraDC(void) { return _memBuffer->getMemDC(); }

	inline void setMapTotalSize(POINT totalSize) { _mapTotalSize = totalSize; }
	inline POINT getMapTotalSize(void) { return _mapTotalSize; }
};

