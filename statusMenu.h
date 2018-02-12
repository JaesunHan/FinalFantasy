#pragma once
#include "menu.h"


class statusMenu : public menu
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();



	statusMenu();
	~statusMenu();
};

