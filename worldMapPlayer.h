#pragma once
#include "gameNode.h"
#include "tile.h"
#include "worldMap.h"

//======월드맵 플레이어=======//
//		제작자 : 한재환		//
//		2월 12일				//
//==========================//

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
	
	//타일맵 클래스
	tile* _tile;

	//월드맵클래스
	worldMap* _worldMap;

	//플레이어 좌표
	POINT _player;
	RECT _rc;

	//플레이어 이미지용
	image* _image;
	int _currentFrameX;
	int	_currentFrameY;
	int _count;
	bool _checkRc;
	bool _isEscapeSuccess;

	//충돌검출용
	float _moveSpeed;
	bool _isCollision;

	worldMapPlayer();
	~worldMapPlayer();

	//init에서 좌표값을 받는 이유는 씬이 바뀔때 해당씬에서 위치를 지정할수 있기 위함이다.
	HRESULT init(int playerX, int PlayerY);
	void release();
	void update();
	void render(HDC hdc, POINT movePt);

	//월드플레이어 이미지 프레임 컨트롤
	void worldPlayerImageFrameControl();
	
	//월드플레이어 이미지 컨트롤
	void worldPlayerImageControl(HDC hdc, POINT movePt);

	//월드플에이어 키 컨트롤
	void worldPlayerKeyControl();

	//타일 인덱스 계산하는 함수
	int tileNum(float x, float y);

	//속성체크용 변수
	void checkAttribute();

	//도망 성공시
	void successEscape();


	//========겟셋 모음==================================/
	RECT getWorldMapPlayerRect() { return _rc; }
	void setWorldMapPlayerRect(RECT rc) { _rc = rc; }

	POINT getWorldMapPlayerPoint() { return _player; }
	void setWorldMapPlayerPoint(POINT player) { _player = player; }
	
	bool getWorldMapPlayerCollision() { return _isCollision; }
	void setWorldMapPlayerCollision(bool collision) { _isCollision = collision; }

};

