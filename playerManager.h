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
	//�� �÷��̾���� ������ ��� ���� ������
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
	//�� ������ �����ϸ� �⺻ ĳ���� ������ ���Ͽ� ����
	void saveNewGameData();
	//�ε� �����̸� ĳ���� ������ �ҷ��´�.
	void loadNewGameData();

	//========================== ��Ʋ������ ��ȯ�Ǹ� �÷��̾� �Ŵ����� �� �Լ��� ȣ���Ͽ� ��Ʋ�÷��̾��� ������ �����Ѵ� ==================
	void setPlayerInfoToBattlePlayer();

	

};

