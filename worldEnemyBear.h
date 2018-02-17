#pragma once
#include "worldMapEnemy.h"
#include "worldMap.h"
#include "aStar.h"
#include "worldMapPlayer.h"



class worldEnemyBear :
	public worldMapEnemy
{

private:
	aStar * _ast;
	worldMapPlayer* _wp;

	int _count;
public:
	worldEnemyBear();
	~worldEnemyBear();

	//init���� ��ǥ���� �޴� ������ ���� �ٲ� �ش������ ��ġ�� �����Ҽ� �ֱ� �����̴�.
	virtual HRESULT init(int enemyX, int enemyY);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();

	//���忡�ʹ� �̹��� ������ ��Ʈ��
	void worldEnemyImageFrameControl();

	//�����÷��̾� �̹��� ��Ʈ��
	void worldEnemyImageControl();

	void setEnemyAddressLinkWithWM(worldMap* wm) { _worldMap = wm; }
	void setEnemyAddressLinkWihtPlayer(worldMapPlayer* wp) { _wp = wp; }

};
