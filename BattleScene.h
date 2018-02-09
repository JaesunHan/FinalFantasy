#pragma once
#include "gameNode.h"
#include "battleShadow.h"
#include "battleTina.h"
#include "battleLocke.h"
#include "battleCeles.h"
#include "Bear.h"
#include "DarkWind.h"
#include "VectorPup.h"
#include <queue>
#include <vector>

enum BATTLECHARACTER
{
	TINA, LOCKE, CELES, SHADOW,
	MONSTER1, MONSTER2, MONSTER3, MONSTER4, MONSTER5, MONSTER6,
	NONE
};


struct tagBattleCharacters
{
	int characterType;		//배틀 캐릭터
	int ABTcounter;				//배틀 카운터
	Enemy* enemy;
	battlePlayerMother* player;
};

class BattleScene : public gameNode
{
private:
	queue<BATTLECHARACTER> _battleTurn;				//턴이 돌아올 캐릭터들을 담아둘 큐
	vector<tagBattleCharacters> _battleCharacters;
	int _maxMonster;
	int _currentTurn;
	bool _turnStart = false;
	bool _turnEnd = false;
public:
	BattleScene();
	~BattleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void monsterAttack();
};

