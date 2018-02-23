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
//�׽�Ʈ��
//class configMenu;


class playerManager : public gameNode
{
private:
	//�� �÷��̾���� ������ ��� ���� ������
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
	//�� ������ �����ϸ� �⺻ ĳ���� ������ ���Ͽ� ����
	//void saveNewGameData();
	//�ε� �����̸� ĳ���� ������ �ҷ��´�.
	void loadGameData();
	void searchPlayerItem(int weaponNum, int armorNum, int helmetNum, int subWeapon, playerMother* tempPlayer);
	//�÷��̾� ���� ��ȯ
	vector<playerMother*> getVPlayer() { return _vPlayer; }


	//========================== ��Ʋ������ ��ȯ�Ǹ� �÷��̾� �Ŵ����� �� �Լ��� ȣ���Ͽ� ��Ʋ�÷��̾��� ������ �����Ѵ� ==================
	void setPlayerInfoToBattlePlayer();

	inline void setItemManagerAddressLink(itemManager* im) { _itemManager = im; }

	//��Ʋ���� �����ϸ� �� �Լ��� ȣ���ؼ� ������ ó���Ѵ�.
	void playerLevelUp();
};

