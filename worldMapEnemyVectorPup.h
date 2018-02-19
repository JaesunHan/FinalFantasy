#pragma once
#include "worldMapEnemy.h"
class worldMapEnemyVectorPup :
	public worldMapEnemy
{
public:
	worldMapEnemyVectorPup();
	~worldMapEnemyVectorPup();

	int _vectorPupCount;
	

	//init���� ��ǥ���� �޴� ������ ���� �ٲ� �ش������ ��ġ�� �����Ҽ� �ֱ� �����̴�.
	virtual HRESULT init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc, POINT movePt);
	virtual void move();

	//���忡�ʹ� �̹��� ������ ��Ʈ��
	void worldEnemyImageFrameControl();

	//�����÷��̾� �̹��� ��Ʈ��
	void worldEnemyImageControl(HDC hdc, POINT movePt);

};

