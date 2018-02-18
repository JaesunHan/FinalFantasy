#pragma once
#include "gameNode.h"

class gameOverScene : public gameNode
{
private:

public:
	gameOverScene();
	~gameOverScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

