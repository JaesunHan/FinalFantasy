#pragma once
#include "gameNode.h"
#include "battleShadow.h"
#include "battleTina.h"
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
	BATTLECHARACTER characterType;		//��Ʋ ĳ����
	int ABTcounter;				//��Ʋ ī����
	Enemy* enemy;
	battlePlayerMother* player;
};

class BattleScene : public gameNode
{
private:
	queue<BATTLECHARACTER> _battleTurn;				//���� ���ƿ� ĳ���͵��� ��Ƶ� ť
	vector<tagBattleCharacters> _battleCharacters;
	bool _turnStart = false;
	bool _turnEnd = false;
public:
	BattleScene();
	~BattleScene();

	HRESULT init();
	void release();
	void update();
	void render();


};

