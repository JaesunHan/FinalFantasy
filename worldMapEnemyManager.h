#pragma once
#include "gameNode.h"
#include "worldEnemyBear.h"
#include "worldMapEnemySamurai.h"
#include "worldMapEnemyVectorPup.h"
#include <vector>

//============���忡�ʹ� �Ŵ���===============//
// ������ ���� ���� -by ��ȯ
//==========================================//
//�浹������ �׳� �Ϲ� ���� ��Ʈ�� 
//�浹�� �ٵ��Ͻ��� Ÿ�� ��ĭ���� ���̿� �浹�ϸ� ��Ʋ������ �Ѿ��
//���ʹ̴� �÷��̾� �����Ҷ� �����Ÿ�(���Ͻ�)�� �Ѿ�� �׳� �ٽ� �Ϲ� ��Ʈ�ѷ� ���� 

#define WORLDMAPENEMY 3

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

	//���ʹ� ����
	void worldEmenyDelete(int arrNum);


	void setPlayerPos(POINT pt) { _playerPos = pt; }

	//========���Լ�======= 
	vector <worldMapEnemy*> getVWME() { return _vWME; }
	vector <worldMapEnemy*>::iterator getViWME() { return _viWME; }


};


