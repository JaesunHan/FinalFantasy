#pragma once
#include "gameNode.h"
#include "battleShadow.h"
#include "battleTina.h"
#include "battleLocke.h"
#include "battleCeles.h"
#include "Bear.h"
#include "DarkWind.h"
#include "VectorPup.h"
#include "siren.h"
#include "bossAtma.h"
#include <queue>
#include <vector>

enum BATTLECHARACTER
{
	TINA, LOCKE, CELES, SHADOW,
	MONSTER1, MONSTER2, MONSTER3, MONSTER4, MONSTER5, MONSTER6,
	NONE
};

enum BATTLEMENU
{
	BATTLE_ATTACK,
	BATTLE_MAGIC,
	BATTLE_SKILL,
	BATTLE_ITEM,
	BATTLE_ESCAPE
};

struct tagBattleCharacters
{
	int characterType;			//��Ʋ ĳ����
	unsigned int ATBcounter;	//��Ʋ ī����
	Enemy* enemy;				//���ʹ� �ּ�
	battlePlayerMother* player;	//�÷��̾� �ּ�
	bool turnStart = false;		//ī���Ͱ� �� á���� ť�� Ǫ���ϴ°� �����ϴ� ����
	bool selectAction = false;	//ī���Ͱ� á���� �޴��� �����ߴ��� ���θ� �˷��ִ� ����
	bool attackReady = false;	//���� ť�� �������� �����غ�
};

class BattleScene : public gameNode
{
private:
	queue<tagBattleCharacters*> _battleTurn;		//���� ���ƿ� ĳ���͵��� ��Ƶ� ť
	vector<tagBattleCharacters> _battleCharacters;	//ĳ���͵��� ������ ����ü ����
	int _maxMonster;								//�ִ� ���� ��
	int _currentTurn;								//���� ���� �������ΰ� ����
	int _menuNum = 0;								//�޴� ���� ��ȣ(1�� ����, 2�� ����, 3�� ��ų, 4�� ������, 5�� ����)
	int _enemyNum = 4;								//�� ���� ��ȣ (4���� ù��° ��)
	int _messageCounter = 0;						//�޽��� ǥ�� ī����
	float _damage = 0;								//��ȣ �ְ� �޴� �������� �Է¹޴� ����
	unsigned int _position;							//���� ������			
	bool _counterRoll = true;						//���϶��� ī���� ����
	bool _playerTurn = false;						//�÷��̾� ���϶� ��
	bool _enemySelect = false;						//���ʹ� �����Ҷ� ��
	bool _sfx01 = true;								//����Ʈ ���� 1��
	bool _sfx02 = false;							//����Ʈ ���� 2��
	bool _isDamaged = false;						//������ �� �� ��
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
	void drawText(int fontSize, char* str, RECT rc, int position, bool dialogue = false);
	void temporaryMessage(int endPoint);
	void playerAttack();

	inline battlePlayerMother* getTinaAddress() { return _battleCharacters[0].player; }
	inline battlePlayerMother* getLockeAddress() { return _battleCharacters[1].player; }
	inline battlePlayerMother* getCelesAddress() { return _battleCharacters[2].player; }
	inline battlePlayerMother* getShadowAddress() { return _battleCharacters[3].player; }
};

