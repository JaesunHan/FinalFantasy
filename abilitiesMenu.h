#pragma once
#include "menu.h"


class abilitiesMenu : public menu
{
private:
	fButton * _button1;


public:
	HRESULT init();
	void release();
	void update();
	void render();



	abilitiesMenu();
	~abilitiesMenu();
};

