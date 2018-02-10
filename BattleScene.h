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
	int characterType;			//배틀 캐릭터
	unsigned int ATBcounter;				//배틀 카운터
	Enemy* enemy;				//에너미 주소
	battlePlayerMother* player;	//플레이어 주소
	bool turnStart = false;		//턴이 돌아오면 
	bool turnEnd = false;
};

class BattleScene : public gameNode
{
private:
	queue<int> _battleTurn;				//턴이 돌아올 캐릭터들을 담아둘 큐
	vector<tagBattleCharacters> _battleCharacters;
	int _maxMonster;
	int _currentTurn;
	bool _counterRoll = true;
public:
	BattleScene();
	~BattleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void ATBGauzeTimer();

	inline battlePlayerMother* getTinaAddress() { return _battleCharacters[0].player; }
	inline battlePlayerMother* getLockeAddress() { return _battleCharacters[1].player; }
	inline battlePlayerMother* getCelesAddress() { return _battleCharacters[2].player; }
	inline battlePlayerMother* getShadowAddress() { return _battleCharacters[3].player; }
};

