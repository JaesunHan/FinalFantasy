#pragma once
#include "menu.h"


class configMenu : public menu
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();



	configMenu();
	~configMenu();
};

