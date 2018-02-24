#pragma once
#include "gameNode.h"
#include "tile.h"
#include "worldMap.h"

//======월드맵 플레이어=======//
//		제작자 : 한재환		//
//		2월 12일				//
//==========================//


#define MAXENCOUNT 1000
#define INCRESECOUNTRANGE RND->getFromIntTo(1,5)

enum WORLDPLAYERDIRECTION
{
	WPRIGHT,
	WPLEFT,
	WPUP,
	WPDOWN,
	WPEND
};


//전방선언
class generalMap;

class worldMapPlayer : public gameNode
{
public:

	WORLDPLAYERDIRECTION _worldPlayerDirection;
	
	//타일맵 클래스
	tile* _tile;

	//월드맵클래스
	generalMap* _curMap;
	


	//플레이어 좌표
	POINT _player;
	RECT _rc;

	//플레이어 씬전환시 사용할 임시 저장좌표
	POINT _playerTemp;

	//플레이어 이미지용
	image* _image;
	int _currentFrameX;
	int	_currentFrameY;
	int _count;

	//배틀엔카운터용 변수
	int _battleCount;
	bool _isEncount;
	
	bool _checkRc;
	bool _isEscapeSuccess;

	//세이브포인트용 변수
	bool _isSavePoint;


	//마을 입장용
	bool _isEnter;

	//월드맵 입장용
	bool _isWorldMapEnter;

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

	void setCurMapAddressLink(generalMap* curMap) { _curMap = curMap; }

	POINT getWorldMapPlayerTempPoint() { return _playerTemp; }
	void setWorldMapPlayerTempPoint(POINT playerTemp) { _playerTemp = playerTemp; }


	bool getIsEnter() { return _isEnter; }
	void setIsEnter(bool isEnter) { _isEnter = isEnter; }

	bool getIsWorldMapEnter() { return _isWorldMapEnter; }
	void setIsWorldMapeEnter(bool isWorldMapEnter) { _isWorldMapEnter = isWorldMapEnter; }

	bool getIsEncount() { return _isEncount; }
	void setIsEncount(bool isEncount) { _isEncount = isEncount; }


	bool getIsSavePoint() { return _isSavePoint; }
	void setIsSavePoint(bool isSavePoint) { _isSavePoint = isSavePoint; }
};

