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
	int characterType;			//배틀 캐릭터
	int menuSelect;				//메뉴 선택 번호
	unsigned int ATBcounter;	//배틀 카운터
	Enemy* enemy;				//에너미 주소
	battlePlayerMother* player;	//플레이어 주소
	bool turnStart = false;		//카운터가 꽉 찼을때 큐에 푸시하는걸 방지하는 변수
	bool selectAction = false;	//카운터가 찼을때 메뉴를 선택했는지 여부를 알려주는 변수
	bool attackReady = false;	//공격 큐가 들어왔을때 사전준비
	bool isDead = false;		//죽었니?
};

class playerManager;

class BattleScene : public gameNode
{
private:
	queue<tagBattleCharacters*> _battleTurn;		//턴이 돌아올 캐릭터들을 담아둘 큐
	vector<tagBattleCharacters> _battleCharacters;	//캐릭터들을 생성할 구조체 벡터
	int _maxMonster;								//최대 몬스터 수
	int _currentTurn;								//현재 턴이 누구턴인가 저장
	int _menuNum = 0;								//메뉴 선택 번호(1번 공격, 2번 마법, 3번 스킬, 4번 아이템, 5번 도망)
	int _enemyNum = 4;								//적 선택 번호 (4번이 첫번째 적)
	int _itemSelectNum = 0;								//아이템 선택 번호
	int _messageCounter = 0;						//메시지 표시 카운터
	int _victoryCounter = 0;						//승리 카운터
	int _dialogueCounter = 0;						//다이얼로그 카운터
	int _gameOver = 0;								//게임 오버니?
	float _damage = 0;								//상호 주고 받는 데미지를 입력받는 변수
	unsigned int _position;							//사운드 포지션			
	bool _counterRoll = true;						//참일때만 카운터 증가
	bool _playerTurn = false;						//플레이어 턴일때 참
	bool _enemySelect = false;						//에너미 선택창 띄운다
	bool _itemSelect = false;						//아이템 선택창 띄운다
	bool _magicSelect = false;						//마법 선택
	bool _sfx01 = true;								//이펙트 사운드 1번
	bool _sfx02 = false;							//이펙트 사운드 2번
	bool _isDamaged = false;						//데미지 들어갈 때 참
	bool _victory = false;							//승리했을때 참
	bool _hit = false;								//명중시 참
	bool _dialogue = false;							//다이얼로그 돌아갈때 참
	bool _changeScene = false;						//씬 변환시 참
	char _message0[256];							//메시지 저장소 0번
	char _message1[256];							//메시지 저장소 1번
	char _message2[256];							//메시지 저장소 2번
	HFONT newFont, oldFont;							//폰트
	RECT _damageRC;									//데미지 렉트
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

