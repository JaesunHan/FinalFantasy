#pragma once
#include "menu.h"


class itemMenu : public menu
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();




	itemMenu();
	~itemMenu();
};

