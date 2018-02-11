#include "stdafx.h"
#include "battleTina.h"


battleTina::battleTina()
{
	//일단은 0번째 파티원이라고 초기화한다.
	_partyIdx = 0;
	//얼굴 이미지 
	_faceImg = IMAGEMANAGER->addImage("tinaJump", "./image/playerImg/tina/tina_face.bmp", 56, 38, true, RGB(255, 0, 255));

	//================================ Start 각 상태에 따른 이미지와 애니메이션을 기본값으로 초기화 ===========================================
	_idleImg = IMAGEMANAGER->addFrameImage("tinaIdle", "./image/playerImg/tina/tina_idle.bmp", 336, 58, 8, 1, true, RGB(255, 0, 255));
	_idleAnim = new animation;
	_idleAnim->init(_idleImg->getWidth(), _idleImg->getHeight(), _idleImg->getFrameWidth(), _idleImg->getFrameHeight());
	int idleArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_idleAnim->setPlayFrame(idleArr, 8);
	_idleAnim->setFPS(1);

	_atkImg = IMAGEMANAGER->addFrameImage("tinaAttack", "./image/playerImg/tina/tina_atk.bmp", 3026, 60, 17, 1, true, RGB(255, 0, 255));
	_atkAnim = new animation;
	_atkAnim->init(_atkImg->getWidth(), _atkImg->getHeight(), _atkImg->getFrameWidth(), _atkImg->getFrameHeight());
	int atkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	_atkAnim->setPlayFrame(atkArr, 17);
	_atkAnim->setFPS(1);

	_magicAtkImg = IMAGEMANAGER->addFrameImage("tinaMagicAttack", "./image/playerImg/tina/tina_magic_atk.bmp", 792, 60, 12, 1, true, RGB(255, 0, 255));
	_magicAtkAnim = new animation;
	_magicAtkAnim->init(_magicAtkImg->getWidth(), _magicAtkImg->getHeight(), _magicAtkImg->getFrameWidth(), _magicAtkImg->getFrameHeight());
	int magicAtkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	_magicAtkAnim->setPlayFrame(magicAtkArr, 12);
	_magicAtkAnim->setFPS(1);

	_deadImg = IMAGEMANAGER->addFrameImage("tinaDead", "./image/playerImg/tina/tina_dead.bmp", 152, 54, 2, 1, true, RGB(255, 0, 255));
	_deadAnim = new animation;
	int deadArr[] = { 0,1 };
	_deadAnim->setPlayFrame(deadArr, 2);
	_deadAnim->setFPS(1);

	_winImg = IMAGEMANAGER->addFrameImage("tinaWin", "./image/playerImg/tina/tina_win.bmp", 360, 60, 9, 1, true, RGB(255, 0, 255));
	_winAnim = new animation;
	_winAnim->init(_winImg->getWidth(), _winImg->getHeight(), _winImg->getFrameWidth(), _winImg->getFrameHeight());
	int winArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	_winAnim->setPlayFrame(winArr, 9);
	_winAnim->setFPS(1);

	_jumpImg = IMAGEMANAGER->addImage("tinaJump", "./image/playerImg/tina/tina_jump.bmp", 40, 50, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addImage("tinaMove", "./image/playerImg/tina/tina_move.bmp", 40, 54, true, RGB(255, 0, 255));
	//================================ End 각 상태에 따른 이미지와 애니메이션을 기본값으로 초기화 ===========================================
	
	//기본적으로 IDLE 상태이다
	_status = BATTLE_PLAYER_IDLE;

}


battleTina::~battleTina()
{

}

HRESULT battleTina::init()
{


	return S_OK;
}
void battleTina::update() 
{
	battlePlayerMother::update();
	
}

void battleTina::draw()	  
{
	battlePlayerMother::draw();
}
void battleTina::release()
{

}
