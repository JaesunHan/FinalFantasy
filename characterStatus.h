#pragma once
#include "menu.h"


class characterStatus : public menu
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();



	characterStatus();
	~characterStatus();
};

