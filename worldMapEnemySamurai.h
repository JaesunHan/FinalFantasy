#pragma once
#include "worldMapEnemy.h"


class worldMapEnemySamurai :
	public worldMapEnemy
{

public:
	int _samuraiCount;
	worldMapEnemySamurai();
	~worldMapEnemySamurai();

	//init���� ��ǥ���� �޴� ������ ���� �ٲ� �ش������ ��ġ�� �����Ҽ� �ֱ� �����̴�.
	virtual HRESULT init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void move();

	//���忡�ʹ� �̹��� ������ ��Ʈ��
	void worldEnemyImageFrameControl();

	//���忡�ʹ� �̹��� ��Ʈ��
	void worldEnemyImageControl();

	//���忡�ʹ� �浹
	void worldEnemyCollision();

};

