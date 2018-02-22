#include "stdafx.h"
#include "battleCeles.h"


battleCeles::battleCeles()
{
	//�ϴ��� 0��° ��Ƽ���̶�� �ʱ�ȭ�Ѵ�.
	_partyIdx = 0;
	//�� �̹��� 
	_faceImg = IMAGEMANAGER->addImage("celesFace", "./image/playerImg/celes/celes_face.bmp", 56, 38, true, RGB(255, 0, 255));

	//================================ Start �� ���¿� ���� �̹����� �ִϸ��̼��� �⺻������ �ʱ�ȭ ===========================================
	_idleImg = IMAGEMANAGER->addFrameImage("celesIdle", "./image/playerImg/celes/celes_idle.bmp", 183, 142, 3, 2, true, RGB(255, 255, 0));
	_idleAnim = new animation;
	_idleAnim->init(_idleImg->getWidth(), _idleImg->getHeight(), _idleImg->getFrameWidth(), _idleImg->getFrameHeight());
	int idleArr[] = { 0, 1, 2, 3 };
	_idleAnim->setPlayFrame(idleArr, 4, true);
	_idleAnim->setFPS(1);

	//���� �̹���, �ִϸ��̼�
	_atkImg = IMAGEMANAGER->addFrameImage("celesAttack", "./image/playerImg/celes/celes_atk.bmp", 423, 490, 3, 5, true, RGB(255, 255, 0));
	_atkAnim = new animation;
	_atkAnim->init(_atkImg->getWidth(), _atkImg->getHeight(), _atkImg->getFrameWidth(), _atkImg->getFrameHeight());
	int atkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	_atkAnim->setPlayFrame(atkArr, 13, false);
	_atkAnim->setFPS(1);

	//���� ��� �̹���, �ִϸ��̼�
	_atkStandbyImg = IMAGEMANAGER->addFrameImage("celesAttackStandby", "./image/playerImg/celes/celes_atk_standby.bmp", 156, 136, 3, 2, true, RGB(255, 255, 0));
	_atkStandbyAnim = new animation;
	_atkStandbyAnim->init(_atkStandbyImg->getWidth(), _atkStandbyImg->getHeight(), _atkStandbyImg->getFrameWidth(), _atkStandbyImg->getFrameHeight());
	int atkStandbyArr[] = { 0, 1, 2, 3 };
	_atkStandbyAnim->setPlayFrame(atkStandbyArr, 4, true);
	_atkStandbyAnim->setFPS(1);

	//���� ���� �̹���, �ִϸ��̼�
	_magicAtkImg = IMAGEMANAGER->addFrameImage("celesMagicAttack", "./image/playerImg/celes/celes_magic_atk.bmp", 249, 140, 3, 2, true, RGB(255, 255, 0));
	_magicAtkAnim = new animation;
	_magicAtkAnim->init(_magicAtkImg->getWidth(), _magicAtkImg->getHeight(), _magicAtkImg->getFrameWidth(), _magicAtkImg->getFrameHeight());
	int magicAtkArr[] = { 0, 1, 2, 3 };
	_magicAtkAnim->setPlayFrame(magicAtkArr, 4, false);
	_magicAtkAnim->setFPS(1);
	//���� ���� ��� �̹���, �ִϸ��̼�
	_magicAtkStandbyImg = IMAGEMANAGER->addFrameImage("celesMagicAttackStandby", "./image/playerImg/celes/celes_magic_atk_standby.bmp", 195, 140, 3, 2, true, RGB(255, 255, 0));
	_magicAtkStandbyAnim = new animation;
	_magicAtkStandbyAnim->init(_magicAtkStandbyImg->getWidth(), _magicAtkStandbyImg->getHeight(), _magicAtkStandbyImg->getFrameWidth(), _magicAtkStandbyImg->getFrameHeight());
	int magicAtkStandbyArr[] = { 0, 1, 2, 3};
	_magicAtkStandbyAnim->setPlayFrame(magicAtkStandbyArr, 4, true);
	_magicAtkStandbyAnim->setFPS(1);


	_deadImg = IMAGEMANAGER->addFrameImage("celesDead", "./image/playerImg/celes/celes_dead.bmp", 108, 54, 2, 1, true, RGB(255, 255, 0));
	_deadAnim = new animation;
	_deadAnim->init(_deadImg->getWidth(), _deadImg->getHeight(), _deadImg->getFrameWidth(), _deadImg->getFrameHeight());
	int deadArr[] = { 0,1 };
	_deadAnim->setPlayFrame(deadArr, 2, false);
	_deadAnim->setFPS(1);

	_winImg = IMAGEMANAGER->addFrameImage("celesWin", "./image/playerImg/celes/celes_win.bmp", 207, 140, 3, 2, true, RGB(255, 255, 0));
	_winAnim = new animation;
	_winAnim->init(_winImg->getWidth(), _winImg->getHeight(), _winImg->getFrameWidth(), _winImg->getFrameHeight());
	int winArr[] = { 0, 1, 2, 3 };
	_winAnim->setPlayFrame(winArr, 4, true);
	_winAnim->setFPS(1);

	_winBeforeImg = IMAGEMANAGER->addFrameImage("celesWinBefore", "./image/playerImg/celes/celes_win_before.bmp", 219, 375, 3, 5, true, RGB(255, 255, 0));
	_winBeforeAnim = new animation;
	_winBeforeAnim->init(_winBeforeImg->getWidth(), _winBeforeImg->getHeight(), _winBeforeImg->getFrameWidth(), _winBeforeImg->getFrameHeight());
	int winBeforeArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	_winBeforeAnim->setPlayFrame(winBeforeArr, 13, false);
	_winBeforeAnim->setFPS(1);


	_jumpImg = IMAGEMANAGER->addImage("lockeJump", "./image/playerImg/locke/locke_jump.bmp", 51, 59, true, RGB(0, 0, 255));
	_moveImg = IMAGEMANAGER->addImage("lockeMove", "./image/playerImg/locke/locke_move.bmp", 59, 68, true, RGB(0, 0, 255));
	//================================ End �� ���¿� ���� �̹����� �ִϸ��̼��� �⺻������ �ʱ�ȭ ===========================================

	//�⺻������ IDLE �����̴�
	_status = BATTLE_PLAYER_IDLE;
	_idleAnim->start();
	//�ٸ� ���¿� ���� �� ������ false�� �ʱ�ȭ �Ѵ�.
	_playAnimList[0] = true;
	for (int i = 1; i < MAXANIMATIONNUM; ++i)
	{
		_playAnimList[i] = false;
	}

	//������ ������ �� ���ʹ� ���� ���� �����Ѵ�.
	_atkDistance = true;

	for (int i = 0; i < MAXATKMOTION; ++i)
	{
		_atkMotionList[i] = false;
	}
	_atkMotion = false;	_angle = 0.0f, _speed = 0.0f;
	
	_hitRate = 200;

	_strength = 34, _speed = 34.0f, _stamina = 31;
	_attack = 16, _magic = 36, _a_Def = 44;
	_m_Def = 31, _evasion = 7, _m_evasion = 9;

	_atkAnimPlaySPD = 20;

	//������ �� ���� ���� ����Ʈ
	_atkEffectSoundKey = "CelesAttackSound";
	_atkEffectSoundFile = "./sound/sfx/65SwordSlash.wav";
	SOUNDMANAGER->addSound(_atkEffectSoundKey, _atkEffectSoundFile, false, false);

}


battleCeles::~battleCeles()
{

}

HRESULT battleCeles::init()
{

	return S_OK;
}
void battleCeles::update() 
{
	battlePlayerMother::update();
	//���� �����ϸ� ó���� ��������� true �� �ٲ۴�.
	
}
void battleCeles::draw()   
{
	battlePlayerMother::draw();
}
void battleCeles::release()
{

}