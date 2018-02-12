#pragma once
#include "menu.h"
#include "titleScene.h"


class saveLoadMenu : public menu
{
private:
	titleScene * _title;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	saveLoadMenu();
	~saveLoadMenu();
};

