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

	virtual HRESULT init(int npcX, int npcY);
	void release();
	void update();
	virtual void render(HDC hdc, POINT movePt);

	//����NPC �̹��� ������ ��Ʈ��
	void worldNpcImageFrameControl();

	//����NPC �̹��� ��Ʈ��
	void worldNpcImageControl();

	//����NPC Ű ��Ʈ��
	void worldNpcKeyControl();

	//Ÿ�� �ε��� ����ϴ� �Լ�
	int tileNum(float x, float y);


	//zorder�� ���� y��ġ ����
	POINT getNpcPoint() { return _npc; }

};

