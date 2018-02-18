#include "stdafx.h"
#include "battleTina.h"


battleTina::battleTina()
{
	//일단은 0번째 파티원이라고 초기화한다.
	_partyIdx = 0;
	//얼굴 이미지 
	_faceImg = IMAGEMANAGER->addImage("tinaFace", "./image/playerImg/tina/tina_face.bmp", 56, 38, true, RGB(255, 0, 255));

	//================================ Start 각 상태에 따른 이미지와 애니메이션을 기본값으로 초기화 ===========================================
	_idleImg = IMAGEMANAGER->addFrameImage("tinaIdle", "./image/playerImg/tina/tina_idle.bmp", 153, 210, 3, 3, true, RGB(255, 0, 255));
	_idleAnim = new animation;
	_idleAnim->init(_idleImg->getWidth(), _idleImg->getHeight(), _idleImg->getFrameWidth(), _idleImg->getFrameHeight());
	int idleArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_idleAnim->setPlayFrame(idleArr, 8, true);
	_idleAnim->setFPS(1);
	
	//공격 이미지, 애니메이션
	_atkImg = IMAGEMANAGER->addFrameImage("tinaAttack", "./image/playerImg/tina/tina_atk.bmp", 534, 340, 3, 5, true, RGB(255, 0, 255));
	_atkAnim = new animation;
	_atkAnim->init(_atkImg->getWidth(), _atkImg->getHeight(), _atkImg->getFrameWidth(), _atkImg->getFrameHeight());
	int atkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	_atkAnim->setPlayFrame(atkArr, 13, false);
	_atkAnim->setFPS(1);
	//공격 대기 이미지, 애니메이션
	_atkStandbyImg = IMAGEMANAGER->addFrameImage("tinaAttackStandby", "./image/playerImg/tina/tina_atk_standby.bmp", 150, 136, 3, 2, true, RGB(255, 0, 255));
	_atkStandbyAnim = new animation;
	_atkStandbyAnim->init(_atkStandbyImg->getWidth(), _atkStandbyImg->getHeight(), _atkStandbyImg->getFrameWidth(), _atkStandbyImg->getFrameHeight());
	int atkStandbyArr[] = { 0, 1, 2, 3 };
	_atkStandbyAnim->setPlayFrame(atkStandbyArr, 4, true);
	_atkStandbyAnim->setFPS(1);

	//마법 공격 이미지, 애니메이션
	_magicAtkImg = IMAGEMANAGER->addFrameImage("tinaMagicAttack", "./image/playerImg/tina/tina_magic_atk.bmp", 195, 140, 3, 2, true, RGB(255, 0, 255));
	_magicAtkAnim = new animation;
	_magicAtkAnim->init(_magicAtkImg->getWidth(), _magicAtkImg->getHeight(), _magicAtkImg->getFrameWidth(), _magicAtkImg->getFrameHeight());
	int magicAtkArr[] = { 0, 1, 2, 3 };
	_magicAtkAnim->setPlayFrame(magicAtkArr, 4, false);
	_magicAtkAnim->setFPS(1);
	//마법 공격 대기 이미지, 애니메이션
	_magicAtkStandbyImg = IMAGEMANAGER->addFrameImage("tinaMagicAttackStandby", "./image/playerImg/tina/tina_magic_atk_standby.bmp", 174, 210, 3, 3, true, RGB(255, 0, 255));
	_magicAtkStandbyAnim = new animation;
	_magicAtkStandbyAnim->init(_magicAtkStandbyImg->getWidth(), _magicAtkStandbyImg->getHeight(), _magicAtkStandbyImg->getFrameWidth(), _magicAtkStandbyImg->getFrameHeight());
	int magicAtkStandbyArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_magicAtkStandbyAnim->setPlayFrame(magicAtkStandbyArr, 8, true);
	_magicAtkStandbyAnim->setFPS(1);


	_deadImg = IMAGEMANAGER->addFrameImage("tinaDead", "./image/playerImg/tina/tina_dead.bmp", 152, 54, 2, 1, true, RGB(255, 0, 255));
	_deadAnim = new animation;
	_deadAnim->init(_deadImg->getWidth(), _deadImg->getHeight(), _deadImg->getFrameWidth(), _deadImg->getFrameHeight());
	int deadArr[] = { 0,1 };
	_deadAnim->setPlayFrame(deadArr, 2, false);
	_deadAnim->setFPS(1);
	
	_winImg = IMAGEMANAGER->addFrameImage("tinaWin", "./image/playerImg/tina/tina_win.bmp", 153, 138, 3, 2, true, RGB(255, 0, 255));
	_winAnim = new animation;
	_winAnim->init(_winImg->getWidth(), _winImg->getHeight(), _winImg->getFrameWidth(), _winImg->getFrameHeight());
	int winArr[] = { 0, 1, 2, 3 };
	_winAnim->setPlayFrame(winArr, 4, true);
	_winAnim->setFPS(1);
	
	_winBeforeImg = IMAGEMANAGER->addFrameImage("tinaWinBefore", "./image/playerImg/tina/tina_win_before.bmp", 153, 138, 3, 2, true, RGB(255, 0, 255));
	_winBeforeAnim = new animation;
	_winBeforeAnim->init(_winBeforeImg->getWidth(), _winBeforeImg->getHeight(), _winBeforeImg->getFrameWidth(), _winBeforeImg->getFrameHeight());
	int winBeforeArr[] = { 0, 1, 2, 3, 4 };
	_winBeforeAnim->setPlayFrame(winBeforeArr, 5, false);
	_winBeforeAnim->setFPS(1);

	_jumpImg = IMAGEMANAGER->addImage("tinaJump", "./image/playerImg/tina/tina_jump.bmp", 40, 50, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addImage("tinaMove", "./image/playerImg/tina/tina_move.bmp", 40, 54, true, RGB(255, 0, 255));
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
	
	//티나 공격할 때 에너미 한테 가서 공격한다.
	_atkDistance = false;
	for (int i = 0; i < MAXATKMOTION; ++i)
	{
		_atkMotionList[i] = false;
	}
	_strength = 31, _speed = 33.0f, _stamina = 28;
	_attack = 12, _magic = 39, _a_Def = 42;
	_m_Def = 33, _evasion = 5, _m_evasion = 7;

	_angle = 0.0f;
	_hitRate = 200;
	
	_atkAnimPlaySPD = 15;
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
	_count++;
	battlePlayerMother::update();
	if (_count % 120==0)
	{
		//티나의 turnEnd 를 true 로 반환
		_count = 0;
		_turnEnd = true;
		setPlayerDefaultPosition();
	}
	
	
}

void battleTina::draw()	  
{
	battlePlayerMother::draw();
}
void battleTina::release()
{

}
