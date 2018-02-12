#pragma once
#include "gameNode.h"

class titleScene;
class saveLoadMenu;

class GameMenuManager : public gameNode
{
private:
	titleScene * _tS;
	saveLoadMenu* _sM;



public:
	HRESULT init();
	void release();
	void update();
	void render();


	void getTitleAddress(titleScene* tS) { _tS = tS; }
	void getSaveLoadAddress(saveLoadMenu* sM) { _sM = sM; }


	GameMenuManager();
	~GameMenuManager();
};

