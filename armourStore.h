#pragma once
#include "gameNode.h"
//=======방어구 상점===========//

class armourStore : public gameNode
{
public:
	armourStore();
	~armourStore();

	HRESULT init();
	void release();
	void update();
	void render();

};

