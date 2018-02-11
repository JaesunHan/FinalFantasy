#pragma once
#include "gameNode.h"


class townScene : public gameNode
{
public:
	townScene();
	~townScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

