#pragma once
#include "menu.h"


class saveLoadMenu : public menu
{
private:
	int  _tmpLoasdSaveFileNum;
	bool _resetCount;
	int  _resetCountSlotNum;

public:
	HRESULT init();
	void release();
	void update();
	void render();


	void setItemManagerAddressLink(itemManager* im) { _iM = im; }
	void setWorldMapAddressLink(worldMapScene* wm) { _wM = wm; }
	void setWorldMapAddressLink(townScene* tm) { _tM = tm; }
	void setCurrentScene(string sceneName) { _currentSceneName = sceneName; }

	saveLoadMenu();
	~saveLoadMenu();
};

