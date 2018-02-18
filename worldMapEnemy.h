#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "aStar.h"
#include "tile.h"
#include "worldMapPlayer.h"

#define MAX_FIND_COUNTER 200
#define ENEMY_MOVE_SPEED 3.0f

//==============����� ���ʹ�=====================//
//1. a*����Ǵ� ����
//2. ��ǥ���� ���� ���̴� �̹����� �ٲ��� �� 
//2-1 �÷��̾�� ������ ������ ����, �÷��̾�� ������ ������ ����, �÷��̾�� �Ʒ��� ������ ����, �÷��̾�� ��ܿ� ������ ���� 
//3. ������ ���������� ������. 
//4. �浹�� ��Ʋ������ ��ȯ�Ѵ�.
//////////////////////////////////////////////////



//����ʿ� ���ƴٴϴ� ���ʹ� Ÿ��������
//�ε������� Ÿ�� Ȯ���� �Ϸ� �־��µ�
//ũ�� �ʿ����� ������ ����.
//Ȥ�ö� �� Ȯ�强�� ���ؼ�
enum ENEMYTYPE
{
	ENEMY_BEAR,
	ENEMY_SKELETON,
	ENEMY_VECTORPUP,
	ENEMY_END
};

enum ENEMYDIRECTION
{
	ENEMYDIRECTION_RIGHT,
	ENEMYDIRECTION_LEFT,
	ENEMYDIRECTION_END
};

enum ENEMYMOVEPATTERN
{
	ENEMYPATTERN_ONE,
	ENEMYPATTERN_TWO,
	ENEMYPATTERN_THREE,
	ENEMYPATTERN_END
};

class worldMapEnemy : public gameNode
{
public:

	ENEMYTYPE _enemyType;
	ENEMYDIRECTION _enemyDirection;
	ENEMYMOVEPATTERN _enemyMovePattern;


	//����� Ŭ����
	worldMap* _worldMap;

	//����� �÷��̾� ���� 
	worldMapPlayer* _wp;

	//���ʹ� �̹��� �����
	image* _image;
	int _enemyCurrentFrameX;
	int _enemyCurrentFrameY;
	int _count;

	//���ʹ� ��ǥ
	POINT _enemy;
	RECT _rc;

	//�浹�����
	float _moveSpeed;
	bool _isCollision;


	//a*
	aStar* _ast;
	vector<tile> _vCloseList;
	bool _isDetect;
	
	char str[128];
	char str1[128];


	worldMapEnemy();
	~worldMapEnemy();

	//init���� ��ǥ���� �޴� ������ ���� �ٲ� �ش������ ��ġ�� �����Ҽ� �ֱ� �����̴�.
	HRESULT init();
	virtual HRESULT init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern);
	void release();
	void update();
	void render();
	//a*��
	void move();

	//���忡�ʹ� �̹��� ������ ��Ʈ��
	void worldEnemyImageFrameControl();

	//���忡�ʹ� �̹��� ��Ʈ��
	virtual void worldEnemyImageControl();

	//Ÿ�� �ε��� ����ϴ� �Լ�
	int tileNum(float x, float y);

	//���ʹ� ����Ʈ
	void worldEnemyDetect();

	//���ʹ� �浹
	void worldEnemyCollision();



	//========�ټ� ����==================================/
	RECT getWorldMapEnemyRect() { return _rc; }
	void setWorldMapEnemyRect(RECT rc) { _rc = rc; }

	POINT getWorldMapEnemyPoint() { return _enemy; }
	void setWorldMapEnemyPoint(POINT enemy) { _enemy = enemy; }

	bool getWorldMapEnemyCollision() { return _isCollision; }
	void setWorldMapEnemyCollision(bool collision) { _isCollision = collision; }

	void setEnemyAddressLinkWithWM(worldMap* wm) { _worldMap = wm; }
	void setEnemyAddressLinkWihtPlayer(worldMapPlayer* wp) { _wp = wp; }

	//�ݸ��� ���Լ�
	bool getIsCollision() { return _isCollision; }


};