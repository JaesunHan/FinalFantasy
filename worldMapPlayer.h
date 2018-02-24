#pragma once
#include "gameNode.h"
#include "tile.h"
#include "worldMap.h"

//======����� �÷��̾�=======//
//		������ : ����ȯ		//
//		2�� 12��				//
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


//���漱��
class generalMap;

class worldMapPlayer : public gameNode
{
public:

	WORLDPLAYERDIRECTION _worldPlayerDirection;
	
	//Ÿ�ϸ� Ŭ����
	tile* _tile;

	//�����Ŭ����
	generalMap* _curMap;
	


	//�÷��̾� ��ǥ
	POINT _player;
	RECT _rc;

	//�÷��̾� ����ȯ�� ����� �ӽ� ������ǥ
	POINT _playerTemp;

	//�÷��̾� �̹�����
	image* _image;
	int _currentFrameX;
	int	_currentFrameY;
	int _count;

	//��Ʋ��ī���Ϳ� ����
	int _battleCount;
	bool _isEncount;
	
	bool _checkRc;
	bool _isEscapeSuccess;

	//���̺�����Ʈ�� ����
	bool _isSavePoint;


	//���� �����
	bool _isEnter;

	//����� �����
	bool _isWorldMapEnter;

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

