#include "stdafx.h"
#include "battleLocke.h"


battleLocke::battleLocke()
{
	//일단은 0번째 파티원이라고 초기화한다.
	_partyIdx = 0;
	//얼굴 이미지 
	_faceImg = IMAGEMANAGER->addImage("lockeFace", "./image/playerImg/locke/locke_face.bmp", 56, 38, true, RGB(255, 0, 255));

	//================================ Start 각 상태에 따른 이미지와 애니메이션을 기본값으로 초기화 ===========================================
	_idleImg = IMAGEMANAGER->addFrameImage("lockeIdle", "./image/playerImg/locke/locke_idle.bmp", 186, 192, 3, 3, true, RGB(255, 0, 255));
	_idleAnim = new animation;
	_idleAnim->init(_idleImg->getWidth(), _idleImg->getHeight(), _idleImg->getFrameWidth(), _idleImg->getFrameHeight());
	int idleArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_idleAnim->setPlayFrame(idleArr, 8, true);
	_idleAnim->setFPS(1);

	//공격 이미지, 애니메이션
	_atkImg = IMAGEMANAGER->addFrameImage("lockeAttack", "./image/playerImg/locke/locke_atk.bmp", 459, 828, 3, 9, true, RGB(255, 0, 255));
	_atkAnim = new animation;
	_atkAnim->init(_atkImg->getWidth(), _atkImg->getHeight(), _atkImg->getFrameWidth(), _atkImg->getFrameHeight());
	int atkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	_atkAnim->setPlayFrame(atkArr, 27, false);
	_atkAnim->setFPS(1);
	//공격 대기 이미지, 애니메이션
	_atkStandbyImg = IMAGEMANAGER->addFrameImage("lockeAttackStandby", "./image/playerImg/locke/locke_atk_standby.bmp", 198, 171, 3, 3, true, RGB(255, 0, 255));
	_atkStandbyAnim = new animation;
	_atkStandbyAnim->init(_atkStandbyImg->getWidth(), _atkStandbyImg->getHeight(), _atkStandbyImg->getFrameWidth(), _atkStandbyImg->getFrameHeight());
	int atkStandbyArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_atkStandbyAnim->setPlayFrame(atkStandbyArr, 8, true);
	_atkStandbyAnim->setFPS(1);

	//마법 공격 이미지, 애니메이션
	_magicAtkImg = IMAGEMANAGER->addFrameImage("lockeMagicAttack", "./image/playerImg/locke/locke_magic_atk.bmp", 204, 252, 3, 3, true, RGB(255, 0, 255));
	_magicAtkAnim = new animation;
	_magicAtkAnim->init(_magicAtkImg->getWidth(), _magicAtkImg->getHeight(), _magicAtkImg->getFrameWidth(), _magicAtkImg->getFrameHeight());
	int magicAtkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_magicAtkAnim->setPlayFrame(magicAtkArr, 8, false);
	_magicAtkAnim->setFPS(1);
	//마법 공격 대기 이미지, 애니메이션
	_magicAtkStandbyImg = IMAGEMANAGER->addFrameImage("lockeMagicAttackStandby", "./image/playerImg/locke/locke_magic_atk_standby.bmp", 186, 213, 3, 3, true, RGB(255, 0, 255));
	_magicAtkStandbyAnim = new animation;
	_magicAtkStandbyAnim->init(_magicAtkStandbyImg->getWidth(), _magicAtkStandbyImg->getHeight(), _magicAtkStandbyImg->getFrameWidth(), _magicAtkStandbyImg->getFrameHeight());
	int magicAtkStandbyArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_magicAtkStandbyAnim->setPlayFrame(magicAtkStandbyArr, 8, false);
	_magicAtkStandbyAnim->setFPS(1);


	_deadImg = IMAGEMANAGER->addFrameImage("lockeDead", "./image/playerImg/locke/locke_dead.bmp", 118, 54, 2, 1, true, RGB(255, 0, 255));
	_deadAnim = new animation;
	_deadAnim->init(_deadImg->getWidth(), _deadImg->getHeight(), _deadImg->getFrameWidth(), _deadImg->getFrameHeight());
	int deadArr[] = { 0,1 };
	_deadAnim->setPlayFrame(deadArr, 2, false);
	_deadAnim->setFPS(1);

	_winImg = IMAGEMANAGER->addFrameImage("lockeWin", "./image/playerImg/locke/locke_win.bmp", 174, 201, 3, 3, true, RGB(255, 0, 255));
	_winAnim = new animation;
	_winAnim->init(_winImg->getWidth(), _winImg->getHeight(), _winImg->getFrameWidth(), _winImg->getFrameHeight());
	int winArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_winAnim->setPlayFrame(winArr,8, true);
	_winAnim->setFPS(1);

	_winBeforeImg = IMAGEMANAGER->addFrameImage("lockeWinBefore", "./image/playerImg/locke/locke_win_before.bmp", 228, 480, 3, 6, true, RGB(255, 0, 255));
	_winBeforeAnim = new animation;
	_winBeforeAnim->init(_winBeforeImg->getWidth(), _winBeforeImg->getHeight(), _winBeforeImg->getFrameWidth(), _winBeforeImg->getFrameHeight());
	int winBeforeArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	_winBeforeAnim->setPlayFrame(winBeforeArr, 18, true);
	_winBeforeAnim->setFPS(1);


	_jumpImg = IMAGEMANAGER->addImage("lockeJump", "./image/playerImg/locke/locke_jump.bmp", 51, 59, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addImage("lockeMove", "./image/playerImg/locke/locke_move.bmp", 59, 68, true, RGB(255, 0, 255));
	//================================ End 각 상태에 따른 이미지와 애니메이션을 기본값으로 초기화 ===========================================

	//기본적으로 IDLE 상태이다
	_status = BATTLE_PLAYER_IDLE;
	_idleAnim->start();
	//다른 상태에 대한 불 변수는 false로 초기화 한다.
	_playAnimList[0] = true;
	for (int i = 1; i < MAXANIMATIONNUM; ++i)
	{
		_playAnimList[i] = false;
	}

	//로키는 공격할 때 에너미한테 가서 공격한다.
	_atkDistance = true;
	for (int i = 0; i < MAXATKMOTION; ++i)
	{
		_atkMotionList[i] = false;
	}
	_angle = 0.0f, _speed = 0.0f;
	
	_hitRate = 200;
	_evasion = 0.0f;
	_m_evasion = 0.0f;

	_atkAnimPlaySPD = 35;
}


battleLocke::~battleLocke()
{
	

}

HRESULT battleLocke::init()
{

	return S_OK;
}
void battleLocke::update() 
{
	battlePlayerMother::update();
}
void battleLocke::draw()   
{
	battlePlayerMother::draw();
}
void battleLocke::release()
{

}
