#pragma once
#include "gameNode.h"
//=======���� ����===========//

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

