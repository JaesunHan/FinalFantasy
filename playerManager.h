#pragma once
#include "gameNode.h"
#include "celes.h"
#include "Locke.h"
#include "shadow.h"
#include "Tina.h"

#define MAXPLAYERNUMBER 4

class BattleScene;
class battleCeles;
class battleLocke;
class battleShadow;
class battleTina;
class weaponItem;
class newGame;
class loadGame;
class playerManager : public gameNode
{
private:
	//각 플레이어들의 정보를 담고 있을 변수들
	celes* _celes;
	Locke* _locke;
	shadow* _shadow;
	Tina* _tina;

	vector<playerMother*> _vPlayer;
	vector<playerMother*>::iterator _viPlayer;

	BattleScene* _battleScene;

	bool _isNewGame;
public:
	playerManager();
	~playerManager();

	HRESULT init();
	void update();
	void render();
	void draw();
	void release();
	//새 게임을 시작하면 기본 캐릭터 정보를 파일에 저장
	void saveNewGameData();
	//로드 게임이면 캐릭터 정볼르 불러온다.
	void loadNewGameData();

	//========================== 배틀씬으로 전환되면 플레이어 매니저의 이 함수를 호출하여 배틀플레이어의 정보를 전달한다 ==================
	void setPlayerInfoToBattlePlayer();

	

};

