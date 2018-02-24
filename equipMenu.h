#pragma once
#include "menu.h"


class equipMenu : public menu
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();


	void buttonOnActive();


	equipMenu();
	~equipMenu();
};

