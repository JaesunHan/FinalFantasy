#pragma once
#include "gameNode.h"
#include "worldMap.h"

enum NPCTYPE
{
	NPC_POTION,
	NPC_WEAPON,
	NPC_DEFENCE,
	NPC_INN,
	NPC_MAGIC,
	NPC_END
};

class npcMother : public gameNode
{
public:

	NPCTYPE _npctype;

	//월드맵 클래스
	worldMap* _worldMap;


	//NPC이미지 제어용
	image* _image;
	int _npcCurrentFrameX;
	int _npcCurrentFrameY;
	int _count;

	//NPC 좌표
	POINT _npc;
	RECT _rc;

	//충돌검출용
	float _moveSpeed;
	bool _isCollision;

public:
	npcMother();
	~npcMother();

	virtual HRESULT init(int npcX, int npcY);
	void release();
	void update();
	virtual void render(HDC hdc, POINT movePt);

	//월드NPC 이미지 프레임 컨트롤
	void worldNpcImageFrameControl();

	//월드NPC 이미지 컨트롤
	void worldNpcImageControl();

	//월드NPC 키 컨트롤
	void worldNpcKeyControl();

	//타일 인덱스 계산하는 함수
	int tileNum(float x, float y);


	//zorder를 위한 y위치 게터
	POINT getNpcPoint() { return _npc; }

};

