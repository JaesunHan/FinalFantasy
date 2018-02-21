#include "stdafx.h"
#include "battleShadow.h"


battleShadow::battleShadow()
{
	//�ϴ��� 0��° ��Ƽ���̶�� �ʱ�ȭ�Ѵ�.
	_partyIdx = 0;
	//�� �̹��� 
	_faceImg = IMAGEMANAGER->addImage("shadowFace", "./image/playerImg/shadow/shadow_face.bmp", 56, 38, true, RGB(255, 0, 255));

	//================================ Start �� ���¿� ���� �̹����� �ִϸ��̼��� �⺻������ �ʱ�ȭ ===========================================
	_idleImg = IMAGEMANAGER->addFrameImage("shadowIdle", "./image/playerImg/shadow/shadow_idle.bmp", 273, 228, 3, 3, true, RGB(255, 0, 255));
	_idleAnim = new animation;
	_idleAnim->init(_idleImg->getWidth(), _idleImg->getHeight(), _idleImg->getFrameWidth(), _idleImg->getFrameHeight());
	int idleArr[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	_idleAnim->setPlayFrame(idleArr, 8, true);
	_idleAnim->setFPS(1);

	//���� �̹���, �ִϸ��̼�
	_atkImg = IMAGEMANAGER->addFrameImage("shadowAttack", "./image/playerImg/shadow/shodow_attack.bmp", 1771, 80, 11, 1, true, RGB(255, 0, 255));
	_atkAnim = new animation;
	_atkAnim->init(_atkImg->getWidth(), _atkImg->getHeight(), _atkImg->getFrameWidth(), _atkImg->getFrameHeight());
	int atkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	_atkAnim->setPlayFrame(atkArr, 11, false);
	_atkAnim->setFPS(1);

	//���� ��� �̹���, �ִϸ��̼�
	_atkStandbyImg = IMAGEMANAGER->addFrameImage("shadowAttackStandby", "./image/playerImg/shadow/shadow_standby.bmp", 279, 144, 3, 2, true, RGB(255, 0, 255));
	_atkStandbyAnim = new animation;
	_atkStandbyAnim->init(_atkStandbyImg->getWidth(), _atkStandbyImg->getHeight(), _atkStandbyImg->getFrameWidth(), _atkStandbyImg->getFrameHeight());
	int atkStandbyArr[] = { 0, 1, 2, 3 };
	_atkStandbyAnim->setPlayFrame(atkStandbyArr, 4, true);
	_atkStandbyAnim->setFPS(1);

	//���� ���� �̹���, �ִϸ��̼�
	_magicAtkImg = IMAGEMANAGER->addFrameImage("shadowMagicAttack", "./image/playerImg/shadow/shadow_magic_attack.bmp", 285, 168, 3, 2, true, RGB(255, 0, 255));
	_magicAtkAnim = new animation;
	_magicAtkAnim->init(_magicAtkImg->getWidth(), _magicAtkImg->getHeight(), _magicAtkImg->getFrameWidth(), _magicAtkImg->getFrameHeight());
	int magicAtkArr[] = { 0, 1, 2, 3 };
	_magicAtkAnim->setPlayFrame(magicAtkArr, 4, false);
	_magicAtkAnim->setFPS(1);
	//���� ���� ��� �̹���, �ִϸ��̼�
	_magicAtkStandbyImg = IMAGEMANAGER->addFrameImage("shadowMagicAttackStandby", "./image/playerImg/shadow/shadow_magic_standby.bmp", 273, 162, 3, 2, true, RGB(255, 0, 255));
	_magicAtkStandbyAnim = new animation;
	_magicAtkStandbyAnim->init(_magicAtkStandbyImg->getWidth(), _magicAtkStandbyImg->getHeight(), _magicAtkStandbyImg->getFrameWidth(), _magicAtkStandbyImg->getFrameHeight());
	int magicAtkStandbyArr[] = { 0, 1, 2, 3 };
	_magicAtkStandbyAnim->setPlayFrame(magicAtkStandbyArr, 4, false);
	_magicAtkStandbyAnim->setFPS(1);


	_deadImg = IMAGEMANAGER->addFrameImage("shadowDead", "./image/playerImg/shadow/shadow_die.bmp", 186, 75, 2, 1, true, RGB(255, 0, 255));
	_deadAnim = new animation;
	_deadAnim->init(_deadImg->getWidth(), _deadImg->getHeight(), _deadImg->getFrameWidth(), _deadImg->getFrameHeight());
	int deadArr[] = { 1,0 };
	_deadAnim->setPlayFrame(deadArr, 2, false);
	_deadAnim->setFPS(1);

	_winImg = IMAGEMANAGER->addFrameImage("shadowWin", "./image/playerImg/shadow/shadow_win.bmp", 678, 1650, 3, 15, true, RGB(255, 0, 255));
	_winAnim = new animation;
	_winAnim->init(_winImg->getWidth(), _winImg->getHeight(), _winImg->getFrameWidth(), _winImg->getFrameHeight());
	int winArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
					21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
					41, 42 };
	_winAnim->setPlayFrame(winArr, 43, true);
	_winAnim->setFPS(1);

	_winBeforeImg = IMAGEMANAGER->addFrameImage("shadowWinBefore", "./image/playerImg/shadow/shadow_win_before.bmp", 276, 420, 3, 5, true, RGB(255, 0, 255));
	_winBeforeAnim = new animation;
	_winBeforeAnim->init(_winBeforeImg->getWidth(), _winBeforeImg->getHeight(), _winBeforeImg->getFrameWidth(), _winBeforeImg->getFrameHeight());
	int winBeforeArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
	_winBeforeAnim->setPlayFrame(winBeforeArr, 15, false);
	_winBeforeAnim->setFPS(1);


	_jumpImg = IMAGEMANAGER->addImage("shadowJump", "./image/playerImg/shadow/shadow_jump.bmp", 104, 58, true, RGB(255, 0, 255));
	_moveImg = IMAGEMANAGER->addImage("shadowMove", "./image/playerImg/shadow/shadow_move.bmp", 110, 64, true, RGB(255, 0, 255));
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

	//������� ������ �� ���ʹ� ���� ���� �����Ѵ�.
	_atkDistance = true;
	for (int i = 0; i < MAXATKMOTION; ++i)
	{
		_atkMotionList[i] = false;
	}
	_angle = 0.0f, _speed = 0.0f;
	_hitRate = 200;

	_strength = 39, _speed = 38.0f, _stamina = 30;
	_attack = 23, _magic = 33, _a_Def = 47;
	_m_Def = 25, _evasion = 28, _m_evasion = 9;

	_atkAnimPlaySPD = 25;

	//������ �� ���� ���� ����Ʈ
	_atkEffectSoundKey = "ShadowAttackSound";
	_atkEffectSoundFile = "./sound/sfx/8BClawSlash.wav";
	SOUNDMANAGER->addSound(_atkEffectSoundKey, _atkEffectSoundFile, false, false);

	//������ �� ���� ����Ʈ
	magic* tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Shadow Magic", "./image/playerImg/playerEffectImage/playerSkill7.bmp", 960, 1152, 5, 6, true, RGB(255, 0, 255));
	tmpMagic->init("Shadow Magic", "./image/playerImg/playerEffectImage/playerSkill7.bmp", "�׸��ڰ���!", 100, 4, 100, 0, 0);
	_myUsableMagic.push_back(tmpMagic);
}


battleShadow::~battleShadow()
{

}

HRESULT battleShadow::init()
{

	return S_OK;
}

void battleShadow::update()	
{
	battlePlayerMother::update();
	
}

void battleShadow::draw()	
{
	//�̰��� �� ��ġ �����ؾߵ�(�������� ����ũ�Ⱑ �ٸ��� �����̴�.)
	if (_status == BATTLE_PLAYER_WIN)
	{
		_posY = 150 + _partyIdx * 100 -26;
	}
	battlePlayerMother::draw();
	
}

void battleShadow::release()
{

}
