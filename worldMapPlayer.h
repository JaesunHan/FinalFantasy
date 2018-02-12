#pragma once
#include "gameNode.h"

enum WORLDPLAYERDIRECTION
{
	WPRIGHT,
	WPLEFT,
	WPUP,
	WPDOWN,
	WPEND
};


class worldMapPlayer : public gameNode
{
public:

	WORLDPLAYERDIRECTION _worldPlayerDirection;

	//플레이어 좌표
	POINT _player;
	RECT _rc;

	//플레이어 이미지용
	image* _image;
	int _currentFrameX;
	int	_currentFrameY;
	int _count;

	//충돌검출용
	float _moveSpeed;
	bool _isCollision;

	worldMapPlayer();
	~worldMapPlayer();

	HRESULT init(int playerX, int PlayerY);
	void release();
	void update();
	void render();

	//월드플레이어 이미지 프레임 컨트롤
	void worldPlayerImageFrameControl();
	
	//월드플레이어 이미지 컨트롤
	void worldPlayerImageControl();

	//월드플에이어 키 컨트롤
	void worldPlayerKeyControl();

	//========겟셋 모음==================================/
	RECT getWorldMapPlayerRect() { return _rc; }
	void setWorldMapPlayerRect(RECT rc) { _rc = rc; }

	POINT getWorldMapPlayerPoint() { return _player; }
	void setWorldMapPlayerPoint(POINT player) { _player = player; }
	
	bool getWorldMapPlayerCollision() { return _isCollision; }
	void setWorldMapPlayerCollision(bool collision) { _isCollision = collision; }

};

