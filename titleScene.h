#pragma once
#include "menu.h"


class titleScene : public menu
{
private:
	int _saveType;

public:
	HRESULT init();
	void release();
	void update();




	titleScene();
	~titleScene();

};

