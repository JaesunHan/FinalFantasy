#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	_pm->init();
	_bts = new BattleScene;
	SCENEMANAGER->addScene("mapToolScene", new mapTool);
	SCENEMANAGER->addScene("배틀씬", _bts);
	//배틀씬으로 전환할 거면 _isBattle 이라는 bool 변수의 값도 true로 저장해주세요
	SCENEMANAGER->changeScene("배틀씬");			_isBattle = true;
	//SCENEMANAGER->changeScene("mapToolScene");
	
	((mapTool*)SCENEMANAGER->findScene("mapToolScene"))->createDefaultMap(PointMake(20, 20));

	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();

}

//연산
void playGround::update(void)
{
	gameNode::update();

	if (_isBattle)
	{
		_pm->setPlayerInfoToBattlePlayer();
		_isBattle = false;
	}

	SCENEMANAGER->update();
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================

	SCENEMANAGER->render();

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}


