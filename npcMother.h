#pragma once
#include "gameNode.h"
#include "worldMap.h"

class npcMother : public gameNode
{
public:

	//����� Ŭ����
	worldMap* _worldMap;


	//NPC�̹��� �����
	image* _image;
	int _npcCurrentFrameX;
	int _npcCurrentFrameY;
	int _count;

	//NPC ��ǥ
	POINT _npc;
	RECT _rc;

	//�浹�����
	float _moveSpeed;
	bool _isCollision;

public:
	npcMother();
	~npcMother();

	HRESULT init(int npcX, int npcY);
	void release();
	void update();
	void render();

	//����NPC �̹��� ������ ��Ʈ��
	void worldNpcImageFrameControl();

	//����NPC �̹��� ��Ʈ��
	void worldNpcImageControl();

	//����NPC Ű ��Ʈ��
	void worldNpcKeyControl();

	//Ÿ�� �ε��� ����ϴ� �Լ�
	int tileNum(float x, float y);
};

