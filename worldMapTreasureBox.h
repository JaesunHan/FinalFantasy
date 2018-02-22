#pragma once
#include "worldMapEnemy.h"
class worldMapTreasureBox :
	public worldMapEnemy
{
public:
	worldMapTreasureBox();
	~worldMapTreasureBox();



	int _treasureCount;



	//init���� ��ǥ���� �޴� ������ ���� �ٲ� �ش������ ��ġ�� �����Ҽ� �ֱ� �����̴�.
	virtual HRESULT init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc, POINT movePt);
	virtual void move();

	//���忡�ʹ� �̹��� ������ ��Ʈ��
	void worldEnemyImageFrameControl();

	//���忡�ʹ� �̹��� ��Ʈ��
	void worldEnemyImageControl(HDC hdc, POINT movePt);

	//���忡�ʹ� �浹
	void worldEnemyCollision();

	//���ʹ� ����Ʈ
	void worldEnemyDetect();

	//�̹����� üũ�Լ�
	void isMimic();

	//=======================�ټ� �߰� ===================

	
};

