#pragma once
#include "worldMapEnemy.h"
#include "worldMap.h"
#include "aStar.h"
#include "worldMapPlayer.h"

#define MAX_FIND_COUNTER 200
#define ENEMY_MOVE_SPEED 3.0f

enum BEAR_DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_END
};

class worldEnemyBear :
	public worldMapEnemy
{

private:
	aStar * _ast;
	worldMapPlayer* _wp;

	BEAR_DIRECTION _direction;

	int _count;
public:
	worldEnemyBear();
	~worldEnemyBear();

	//init에서 좌표값을 받는 이유는 씬이 바뀔때 해당씬에서 위치를 지정할수 있기 위함이다.
	virtual HRESULT init(int enemyX, int enemyY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();

	//월드에너미 이미지 프레임 컨트롤
	void worldEnemyImageFrameControl();

	//월드플레이어 이미지 컨트롤
	void worldEnemyImageControl();

	void setEnemyAddressLinkWithWM(worldMap* wm) { _worldMap = wm; }
	void setEnemyAddressLinkWihtPlayer(worldMapPlayer* wp) { _wp = wp; }

};

