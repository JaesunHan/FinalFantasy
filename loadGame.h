#pragma once
#include "menu.h"


class loadGame : public menu
{
private:
	fButton* _button1;


public:
	HRESULT init();
	void release();
	void update();
	void render();




	loadGame();
	~loadGame();
};

