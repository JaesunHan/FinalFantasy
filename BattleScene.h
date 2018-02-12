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
};

class BattleScene : public gameNode
{
private:
	queue<int> _battleTurn;							//���� ���ƿ� ĳ���͵��� ��Ƶ� ť
	vector<tagBattleCharacters> _battleCharacters;	//ĳ���͵��� ������ ����ü ����
	int _maxMonster;								//�ִ� ���� ��
	int _currentTurn;								//���� ���� �������ΰ� ����... �Ϸ��� ������ ���� �Ⱦ�
	int _menuNum;									//�޴� ���� ��ȣ(1�� ����, 2�� ��ų, 3�� ������, 4�� ���)
	bool _counterRoll = true;						//���϶��� ī���� ����
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

