#pragma once
#include "gameNode.h"
#include <queue>

enum BATTLECHARACTER
{
	TINA, LOCKE, CELES, SHADOW,
	MONSTER1, MONSTER2, MONSTER3, MONSTER4, MONSTER5, MONSTER6,
	NONE
};

class BattleScene : public gameNode
{
private:
	queue<BATTLECHARACTER> _battleTurn;

public:
	BattleScene();
	~BattleScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

