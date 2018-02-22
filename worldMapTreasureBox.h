#pragma once
#include "worldMapEnemy.h"
class worldMapTreasureBox :
	public worldMapEnemy
{
public:
	worldMapTreasureBox();
	~worldMapTreasureBox();



	int _treasureCount;



	//init에서 좌표값을 받는 이유는 씬이 바뀔때 해당씬에서 위치를 지정할수 있기 위함이다.
	virtual HRESULT init(int enemyX, int enemyY, ENEMYMOVEPATTERN enemyPattern);
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc, POINT movePt);
	virtual void move();

	//월드에너미 이미지 프레임 컨트롤
	void worldEnemyImageFrameControl();

	//월드에너미 이미지 컨트롤
	void worldEnemyImageControl(HDC hdc, POINT movePt);

	//월드에너미 충돌
	void worldEnemyCollision();

	//에너미 디텍트
	void worldEnemyDetect();

	//미믹인지 체크함수
	void isMimic();

	//=======================겟셋 추가 ===================

	
};

