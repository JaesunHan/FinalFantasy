#pragma once
#include "menu.h"
#include <vector>

class loadGame : public menu
{
private:


public:
	HRESULT init();
	void release();
	void update();
	void render();


	void setItemManagerAddressLink(itemManager* im) { _iM = im; }
	void setWorldMapAddressLink(worldMapScene* wm) { _wM = wm; }

	loadGame();
	~loadGame();
};

