#pragma once
#include "gameNode.h"
//=======���� ����===========//

class weaponStore : public gameNode
{
public:
	weaponStore();
	~weaponStore();

	HRESULT init();
	void release();
	void update();
	void render();

};

