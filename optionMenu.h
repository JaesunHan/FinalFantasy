#pragma once
#include "menu.h"


class optionMenu : public menu
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	optionMenu();
	~optionMenu();
};

