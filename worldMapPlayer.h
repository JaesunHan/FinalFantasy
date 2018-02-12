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

	//�÷��̾� ��ǥ
	POINT _player;
	RECT _rc;

	//�÷��̾� �̹�����
	image* _image;
	int _currentFrameX;
	int	_currentFrameY;
	int _count;

	//�浹�����
	float _moveSpeed;
	bool _isCollision;

	worldMapPlayer();
	~worldMapPlayer();

	HRESULT init(int playerX, int PlayerY);
	void release();
	void update();
	void render();

	//�����÷��̾� �̹��� ������ ��Ʈ��
	void worldPlayerImageFrameControl();
	
	//�����÷��̾� �̹��� ��Ʈ��
	void worldPlayerImageControl();

	//�����ÿ��̾� Ű ��Ʈ��
	void worldPlayerKeyControl();

	//========�ټ� ����==================================/
	RECT getWorldMapPlayerRect() { return _rc; }
	void setWorldMapPlayerRect(RECT rc) { _rc = rc; }

	POINT getWorldMapPlayerPoint() { return _player; }
	void setWorldMapPlayerPoint(POINT player) { _player = player; }
	
	bool getWorldMapPlayerCollision() { return _isCollision; }
	void setWorldMapPlayerCollision(bool collision) { _isCollision = collision; }

};

