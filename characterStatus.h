#pragma once
#include "menu.h"


class characterStatus : public menu
{
private:
	int _selectPlayerNum;

public:
	HRESULT init();
	void release();
	void update();
	void render();



	characterStatus();
	~characterStatus();
};

