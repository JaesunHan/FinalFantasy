#pragma once
#include "menu.h"


class newGame : public menu
{
private:
	int _saveFileNum;


public:
	HRESULT init();
	void release();
	void update();
	void render();


	newGame();
	~newGame();
};

