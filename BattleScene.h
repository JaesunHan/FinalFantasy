#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "battleShadow.h"
#include "battleTina.h"
#include "battleLocke.h"
#include "battleCeles.h"
#include "Bear.h"
#include "bossAtma.h"
#include "covert.h"
#include "DarkWind.h"
#include "gobbler.h"
#include "guard.h"
#include "samurai.h"
#include "siren.h"
#include "tornadoShark.h"
#include "VectorPup.h"
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
	BATTLE_ESCAPE,
	BATTLE_NULL
};

struct tagBattleCharacters
{
	int characterType;			//��Ʋ ĳ����
	int menuSelect;				//�޴� ���� ��ȣ
	unsigned int ATBcounter;	//��Ʋ ī����
	Enemy* enemy;				//���ʹ� �ּ�
	battlePlayerMother* player;	//�÷��̾� �ּ�
	bool turnStart = false;		//ī���Ͱ� �� á���� ť�� Ǫ���ϴ°� �����ϴ� ����
	bool selectAction = false;	//ī���Ͱ� á���� �޴��� �����ߴ��� ���θ� �˷��ִ� ����
	bool attackReady = false;	//���� ť�� �������� �����غ�
	bool isDead = false;		//�׾���?
};

class playerManager;

class BattleScene : public gameNode
{
private:
	queue<tagBattleCharacters*> _battleTurn;		//���� ���ƿ� ĳ���͵��� ��Ƶ� ť
	vector<tagBattleCharacters> _battleCharacters;	//ĳ���͵��� ������ ����ü ����
	int _maxMonster;								//�ִ� ���� ��
	int _currentTurn;								//���� ���� �������ΰ� ����
	int _menuNum = 0;								//�޴� ���� ��ȣ(1�� ����, 2�� ����, 3�� ��ų, 4�� ������, 5�� ����)
	int _enemyNum = 4;								//�� ���� ��ȣ (4���� ù��° ��)
	int _itemSelectNum = 0;								//������ ���� ��ȣ
	int _messageCounter = 0;						//�޽��� ǥ�� ī����
	int _victoryCounter = 0;						//�¸� ī����
	int _dialogueCounter = 0;						//���̾�α� ī����
	int _gameOver = 0;								//���� ������?
	float _damage = 0;								//��ȣ �ְ� �޴� �������� �Է¹޴� ����
	unsigned int _position;							//���� ������			
	bool _counterRoll = true;						//���϶��� ī���� ����
	bool _playerTurn = false;						//�÷��̾� ���϶� ��
	bool _enemySelect = false;						//���ʹ� ����â ����
	bool _itemSelect = false;						//������ ����â ����
	bool _magicSelect = false;						//���� ����
	bool _sfx01 = true;								//����Ʈ ���� 1��
	bool _sfx02 = false;							//����Ʈ ���� 2��
	bool _isDamaged = false;						//������ �� �� ��
	bool _victory = false;							//�¸������� ��
	bool _hit = false;								//���߽� ��
	bool _dialogue = false;							//���̾�α� ���ư��� ��
	bool _changeScene = false;						//�� ��ȯ�� ��
	char _message0[256];							//�޽��� ����� 0��
	char _message1[256];							//�޽��� ����� 1��
	char _message2[256];							//�޽��� ����� 2��
	HFONT newFont, oldFont;							//��Ʈ
	RECT _damageRC;									//������ ��Ʈ
	playerManager* _pm;
	itemManager* _im;
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
	void renderDamage(int endPoint);
	void temporaryMessage();
	void playerAttack();
	void victoryCondition();
	void gameOverCondition();
	void sceneChange();

	inline battlePlayerMother* getTinaAddress() { return _battleCharacters[0].player; }
	inline battlePlayerMother* getLockeAddress() { return _battleCharacters[1].player; }
	inline battlePlayerMother* getCelesAddress() { return _battleCharacters[2].player; }
	inline battlePlayerMother* getShadowAddress() { return _battleCharacters[3].player; }
	inline void setPlayerManagerMemoryAddressLink(playerManager* pm) { _pm = pm; }
};

