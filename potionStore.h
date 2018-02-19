#pragma once
#include "gameNode.h"
//=======포션 상점===========//

class potionStore :public gameNode
{
public:
	potionStore();
	~potionStore();

	HRESULT init();
	void release();
	void update();
	void render();

};

