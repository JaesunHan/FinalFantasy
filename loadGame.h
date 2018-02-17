#pragma once
#include "menu.h"
#include <vector>

class loadGame : public menu
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();


	loadGame();
	~loadGame();
};

