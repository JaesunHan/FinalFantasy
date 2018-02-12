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
	int characterType;			//��Ʋ ĳ����
	unsigned int ATBcounter;	//��Ʋ ī����
	Enemy* enemy;				//���ʹ� �ּ�
	battlePlayerMother* player;	//�÷��̾� �ּ�
	bool turnStart = false;		//ī���Ͱ� �� á���� ť�� Ǫ���ϴ°� �����ϴ� ����
	bool selectAction = false;	//ī���Ͱ� á���� �޴��� �����ߴ��� ���θ� �˷��ִ� ����
};

class BattleScene : public gameNode
{
private:
	queue<tagBattleCharacters> _battleTurn;							//���� ���ƿ� ĳ���͵��� ��Ƶ� ť
	vector<tagBattleCharacters> _battleCharacters;	//ĳ���͵��� ������ ����ü ����
	int _maxMonster;								//�ִ� ���� ��
	int _currentTurn;								//���� ���� �������ΰ� ����... �Ϸ��� ������ ���� �Ⱦ�
	int _menuNum = 0;								//�޴� ���� ��ȣ(1�� ����, 2�� ����, 3�� ��ų, 4�� ������, 5�� ����)
	int _enemyNum = 4;
	unsigned int _position;
	bool _counterRoll = true;						//���϶��� ī���� ����
	bool _playerTurn = false;
	bool _enemySelect = false;
	bool _sfx01 = false;
	bool _sfx02 = false;
	HFONT newFont, oldFont;
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
	void playerFrameUpdate();
	void soundControl();

	inline battlePlayerMother* getTinaAddress() { return _battleCharacters[0].player; }
	inline battlePlayerMother* getLockeAddress() { return _battleCharacters[1].player; }
	inline battlePlayerMother* getCelesAddress() { return _battleCharacters[2].player; }
	inline battlePlayerMother* getShadowAddress() { return _battleCharacters[3].player; }
};

