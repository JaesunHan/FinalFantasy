#pragma once
#include "gameNode.h"


class GameMenuManager : public gameNode
{
private:




public:
	HRESULT init();
	void release();
	void update();
	void render();




	GameMenuManager();
	~GameMenuManager();
};

