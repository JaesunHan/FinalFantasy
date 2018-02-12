#pragma once
#include "menu.h"


class saveLoadMenu : public menu
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();


	saveLoadMenu();
	~saveLoadMenu();
};

