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
class itemManager;
//class weaponItem;
//class newGame;
//class loadGame;
//테스트용
//class configMenu;


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
	itemManager* _itemManager;

	
public:
	playerManager();
	~playerManager();

	HRESULT init();
	void update();
	void render();
	void draw();
	void release();
	//새 게임을 시작하면 기본 캐릭터 정보를 파일에 저장
	//void saveNewGameData();
	//로드 게임이면 캐릭터 정볼르 불러온다.
	void loadGameData();
	void searchPlayerItem(int weaponNum, int armorNum, int helmetNum, int subWeapon, playerMother* tempPlayer);
	//플레이어 벡터 반환
	vector<playerMother*> getVPlayer() { return _vPlayer; }


	//========================== 배틀씬으로 전환되면 플레이어 매니저의 이 함수를 호출하여 배틀플레이어의 정보를 전달한다 ==================
	void setPlayerInfoToBattlePlayer();

	inline void setItemManagerAddressLink(itemManager* im) { _itemManager = im; }

	//배틀에서 렙업하면 이 함수를 호출해서 렙업을 처리한다.
	void playerLevelUp();
};

