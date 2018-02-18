#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "aStar.h"
#include "tile.h"
#include "worldMapPlayer.h"

#define MAX_FIND_COUNTER 200
#define ENEMY_MOVE_SPEED 3.0f

//==============월드맵 에너미=====================//
//1. a*적용되는 아이
//2. 좌표값에 따라 보이는 이미지가 바뀌어야 함 
//2-1 플레이어보다 좌측에 있으면 우향, 플레이어보다 우측에 있으면 좌향, 플레이어보다 아래에 있으면 상향, 플레이어보다 상단에 있으면 하향 
//3. 고유의 감지범위를 가진다. 
//4. 충돌시 배틀씬으로 전환한다.
//////////////////////////////////////////////////



//월드맵에 돌아다니는 에너미 타입지정용
//부딪쳤을때 타입 확인을 하려 넣었는데
//크게 필요하진 않을것 같다.
//혹시라도 모를 확장성을 위해서
enum ENEMYTYPE
{
	ENEMY_BEAR,
	ENEMY_SKELETON,
	ENEMY_VECTORPUP,
	ENEMY_END
};

enum ENEMYDIRECTION
{
	ENEMYDIRECTION_RIGHT,
	ENEMYDIRECTION_LEFT,
	ENEMYDIRECTION_END
};

enum ENEMYMOVEPATTERN
{
	ENEMYPATTERN_ONE,
	ENEMYPATTERN_TWO,
	ENEMYPATTERN_THREE,
	ENEMYPATTERN_END
};

class worldMapEnemy : public gameNode
{
public:

	ENEMYTYPE _enemyType;
	ENEMYDIRECTION _enemyDirection;
	ENEMYMOVEPATTERN _enemyMovePattern;


	//월드맵 클래스
	worldMap* _worldMap;

	//월드맵 플레이어 정보 
	worldMapPlayer* _wp;

	//에너미 이미지 제어용
	image* _image;
	int _enemyCurrentFrameX;
	int _enemyCurrentFrameY;
	int _count;

	//에너미 좌표
	POINT _enemy;
	RECT _rc;

	//충돌검출용
	float _moveSpeed;
	bool _isCollision;


	//a*
	aStar* _ast;
	vector<tile> _vCloseList;
	bool _isDetect;
	
	char str[128];
	char str1[128];


	worldMapEnemy();
	~worldMapEnemy();

	//init에서 좌표값을 받는 이유는 씬이 바뀔때 해당씬에서 위치를 지정할수 있기 위함이다.
	HRESULT init();
	virtual HRESULT init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern);
	void release();
	void update();
	void render();
	//a*용
	void move();

	//월드에너미 이미지 프레임 컨트롤
	void worldEnemyImageFrameControl();

	//월드에너미 이미지 컨트롤
	virtual void worldEnemyImageControl();

	//타일 인덱스 계산하는 함수
	int tileNum(float x, float y);

	//에너미 디텍트
	void worldEnemyDetect();

	//에너미 충돌
	void worldEnemyCollision();



	//========겟셋 모음==================================/
	RECT getWorldMapEnemyRect() { return _rc; }
	void setWorldMapEnemyRect(RECT rc) { _rc = rc; }

	POINT getWorldMapEnemyPoint() { return _enemy; }
	void setWorldMapEnemyPoint(POINT enemy) { _enemy = enemy; }

	bool getWorldMapEnemyCollision() { return _isCollision; }
	void setWorldMapEnemyCollision(bool collision) { _isCollision = collision; }

	void setEnemyAddressLinkWithWM(worldMap* wm) { _worldMap = wm; }
	void setEnemyAddressLinkWihtPlayer(worldMapPlayer* wp) { _wp = wp; }

	//콜리전 겟함수
	bool getIsCollision() { return _isCollision; }


};