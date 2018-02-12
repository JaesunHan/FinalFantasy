#pragma once
#include "menu.h"


class abilitiesMenu : public menu
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();



	abilitiesMenu();
	~abilitiesMenu();
};

