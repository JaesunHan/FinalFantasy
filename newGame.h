#pragma once
#include "menu.h"


class newGame : public menu
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();


	newGame();
	~newGame();
};

