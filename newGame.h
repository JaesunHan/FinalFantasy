#pragma once
#include "menu.h"


class newGame : public menu
{
private:



public:
	HRESULT init();
	void release();
	void update();
	void render();


	void setItemManagerAddressLink(itemManager* im) { _iM = im; }
	void setPlayerManagerAddressLink(playerManager* pm) { _pM = pm; }

	newGame();
	~newGame();
};

