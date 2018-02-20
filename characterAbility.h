#pragma once
#include "menu.h"


class characterAbility : public menu
{
protected:



public:
	HRESULT init();
	void release();
	void update();
	void render();

	void buttonOnActive();
	void skillButtonSet();

	characterAbility();
	~characterAbility();
};

