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
	unsigned int ATBcounter;	//배틀 카운터
	Enemy* enemy;				//에너미 주소
	battlePlayerMother* player;	//플레이어 주소
	bool turnStart = false;		//카운터가 꽉 찼을때 큐에 푸시하는걸 방지하는 변수
};

class BattleScene : public gameNode
{
private:
	queue<int> _battleTurn;							//턴이 돌아올 캐릭터들을 담아둘 큐
	vector<tagBattleCharacters> _battleCharacters;	//캐릭터들을 생성할 구조체 벡터
	int _maxMonster;								//최대 몬스터 수
	int _currentTurn;								//현재 턴이 누구턴인가 저장... 하려고 했으나 아직 안씀
	int _menuNum;									//메뉴 선택 번호(1번 공격, 2번 스킬, 3번 아이템, 4번 방어)
	bool _counterRoll = true;						//참일때만 카운터 증가
	bool _playerTurn = false;
public:
	BattleScene();
	~BattleScene();

	HRESULT init();
	void release();
	void update();
	void render();

	void ATBGauzeTimer();
	void updateWhenCharacterTurn();
	void playerMenuSelect();
	void characterDraw();
	void drawUI();

	inline battlePlayerMother* getTinaAddress() { return _battleCharacters[0].player; }
	inline battlePlayerMother* getLockeAddress() { return _battleCharacters[1].player; }
	inline battlePlayerMother* getCelesAddress() { return _battleCharacters[2].player; }
	inline battlePlayerMother* getShadowAddress() { return _battleCharacters[3].player; }
};

