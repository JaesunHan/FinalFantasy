#pragma once
#include "gameNode.h"
#include "tile.h"
#include "worldMap.h"

//======����� �÷��̾�=======//
//		������ : ����ȯ		//
//		2�� 12��				//
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
	
	//Ÿ�ϸ� Ŭ����
	tile* _tile;

	//�����Ŭ����
	worldMap* _worldMap;

	//�÷��̾� ��ǥ
	POINT _player;
	RECT _rc;

	//�÷��̾� �̹�����
	image* _image;
	int _currentFrameX;
	int	_currentFrameY;
	int _count;
	bool _checkRc;
	bool _isEscapeSuccess;

	//�浹�����
	float _moveSpeed;
	bool _isCollision;

	worldMapPlayer();
	~worldMapPlayer();

	//init���� ��ǥ���� �޴� ������ ���� �ٲ� �ش������ ��ġ�� �����Ҽ� �ֱ� �����̴�.
	HRESULT init(int playerX, int PlayerY);
	void release();
	void update();
	void render(HDC hdc, POINT movePt);

	//�����÷��̾� �̹��� ������ ��Ʈ��
	void worldPlayerImageFrameControl();
	
	//�����÷��̾� �̹��� ��Ʈ��
	void worldPlayerImageControl(HDC hdc, POINT movePt);

	//�����ÿ��̾� Ű ��Ʈ��
	void worldPlayerKeyControl();

	//Ÿ�� �ε��� ����ϴ� �Լ�
	int tileNum(float x, float y);

	//�Ӽ�üũ�� ����
	void checkAttribute();

	//���� ������
	void successEscape();


	//========�ټ� ����==================================/
	RECT getWorldMapPlayerRect() { return _rc; }
	void setWorldMapPlayerRect(RECT rc) { _rc = rc; }

	POINT getWorldMapPlayerPoint() { return _player; }
	void setWorldMapPlayerPoint(POINT player) { _player = player; }
	
	bool getWorldMapPlayerCollision() { return _isCollision; }
	void setWorldMapPlayerCollision(bool collision) { _isCollision = collision; }

};

