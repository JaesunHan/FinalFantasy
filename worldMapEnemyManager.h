#pragma once
#include "gameNode.h"
#include "worldEnemyBear.h"
#include "worldMapEnemySamurai.h"
#include <vector>

//============���忡�ʹ� �Ŵ���===============//
// ������ ���� ���� -by ��ȯ
//==========================================//
#define WORLDMAPENEMY 2

class worldMapEnemyManager : public gameNode
{
private:

	//���忡�ʹ̿� �����ϱ� ����
	typedef vector<worldMapEnemy*> vWME;
	typedef vector<worldMapEnemy*>::iterator viWME;

	vWME _vWME;
	viWME _viWME;

	//zorder�� ���� �ΰ� ����
	vWME _vTopWME;
	vWME _vBottomWME;

	//�÷��̾� ����Ʈ ���� ����.
	POINT _playerPos;

public:

	

	worldMapEnemyManager();
	~worldMapEnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

//zorder�� ���� ���� �ΰ� �߰� 
	void beforeRender();
	void afterRender();

	void setPlayerPos(POINT pt) { _playerPos = pt; }

	//========���Լ�======= 
	vector <worldMapEnemy*> getVNpc() { return _vWME; }
	vector <worldMapEnemy*>::iterator getViNpc() { return _viWME; }


};
