#pragma once
#include "gameNode.h"
#include "celes.h"
#include "Locke.h"
#include "shadow.h"
#include "Tina.h"

class BattleScene;
class battleCeles;
class battleLocke;
class battleShadow;
class battleTina;
class playerManager : public gameNode
{
private:
	//각 플레이어들의 정보를 담고 있을 변수들
	celes* _celes;
	Locke* _locke;
	shadow* _shadow;
	Tina* _tina;

	BattleScene* _battleScene;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void update();
	void render();
	void draw();
	void release();

	//========================== 배틀씬으로 전환되면 플레이어 매니저의 이 함수를 호출하여 배틀플레이어의 정보를 전달한다 ==================
	void setPlayerInfoToBattlePlayer();
};

