#pragma once
#include "worldMapEnemy.h"

class worldEnemyBear :
	public worldMapEnemy
{
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

};

