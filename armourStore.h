#pragma once
#include "gameNode.h"
//=======�� ����===========//

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

