#include "stdafx.h"
#include "battleShadow.h"


battleShadow::battleShadow()
{
	////�ϴ��� 0��° ��Ƽ���̶�� �ʱ�ȭ�Ѵ�.
	//_partyIdx = 0;
	////�� �̹��� 
	//_faceImg = IMAGEMANAGER->addImage("shadowFace", "./image/playerImg/shadow/shadow_face.bmp", 56, 38, true, RGB(255, 0, 255));
	//
	////================================ Start �� ���¿� ���� �̹����� �ִϸ��̼��� �⺻������ �ʱ�ȭ ===========================================
	//_idleImg = IMAGEMANAGER->addFrameImage("shadowIdle", "./image/playerImg/shadow/shadow_idle.bmp", 183, 142, 3, 2, true, RGB(255, 255, 0));
	//_idleAnim = new animation;
	//_idleAnim->init(_idleImg->getWidth(), _idleImg->getHeight(), _idleImg->getFrameWidth(), _idleImg->getFrameHeight());
	//int idleArr[] = { 0, 1, 2, 3 };
	//_idleAnim->setPlayFrame(idleArr, 4, true);
	//_idleAnim->setFPS(1);
	//
	////���� �̹���, �ִϸ��̼�
	//_atkImg = IMAGEMANAGER->addFrameImage("shadowAttack", "./image/playerImg/shadow/shadow_atk.bmp", 423, 490, 3, 5, true, RGB(255, 255, 0));
	//_atkAnim = new animation;
	//_atkAnim->init(_atkImg->getWidth(), _atkImg->getHeight(), _atkImg->getFrameWidth(), _atkImg->getFrameHeight());
	//int atkArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	//_atkAnim->setPlayFrame(atkArr, 13, false);
	//_atkAnim->setFPS(1);
	//
	////���� ��� �̹���, �ִϸ��̼�
	//_atkStandbyImg = IMAGEMANAGER->addFrameImage("shadowAttackStandby", "./image/playerImg/shadow/shadow_atk_standby.bmp", 156, 136, 3, 2, true, RGB(255, 255, 0));
	//_atkStandbyAnim = new animation;
	//_atkStandbyAnim->init(_atkStandbyImg->getWidth(), _atkStandbyImg->getHeight(), _atkStandbyImg->getFrameWidth(), _atkStandbyImg->getFrameHeight());
	//int atkStandbyArr[] = { 0, 1, 2, 3 };
	//_atkStandbyAnim->setPlayFrame(atkStandbyArr, 4, true);
	//_atkStandbyAnim->setFPS(1);
	//
	////���� ���� �̹���, �ִϸ��̼�
	//_magicAtkImg = IMAGEMANAGER->addFrameImage("shadowMagicAttack", "./image/playerImg/shadow/shadow_magic_atk.bmp", 249, 140, 3, 2, true, RGB(255, 255, 0));
	//_magicAtkAnim = new animation;
	//_magicAtkAnim->init(_magicAtkImg->getWidth(), _magicAtkImg->getHeight(), _magicAtkImg->getFrameWidth(), _magicAtkImg->getFrameHeight());
	//int magicAtkArr[] = { 0, 1, 2, 3 };
	//_magicAtkAnim->setPlayFrame(magicAtkArr, 4, false);
	//_magicAtkAnim->setFPS(1);
	////���� ���� ��� �̹���, �ִϸ��̼�
	//_magicAtkStandbyImg = IMAGEMANAGER->addFrameImage("shadowMagicAttackStandby", "./image/playerImg/shadow/shadow_magic_atk_standby.bmp", 195, 140, 3, 2, true, RGB(255, 255, 0));
	//_magicAtkStandbyAnim = new animation;
	//_magicAtkStandbyAnim->init(_magicAtkStandbyImg->getWidth(), _magicAtkStandbyImg->getHeight(), _magicAtkStandbyImg->getFrameWidth(), _magicAtkStandbyImg->getFrameHeight());
	//int magicAtkStandbyArr[] = { 0, 1, 2, 3 };
	//_magicAtkStandbyAnim->setPlayFrame(magicAtkStandbyArr, 4, false);
	//_magicAtkStandbyAnim->setFPS(1);
	//
	//
	//_deadImg = IMAGEMANAGER->addFrameImage("shadowDead", "./image/playerImg/shadow/shadow_dead.bmp", 108, 54, 2, 1, true, RGB(255, 255, 0));
	//_deadAnim = new animation;
	//_deadAnim->init(_deadImg->getWidth(), _deadImg->getHeight(), _deadImg->getFrameWidth(), _deadImg->getFrameHeight());
	//int deadArr[] = { 0,1 };
	//_deadAnim->setPlayFrame(deadArr, 2, false);
	//_deadAnim->setFPS(1);
	//
	//_winImg = IMAGEMANAGER->addFrameImage("shadowWin", "./image/playerImg/shadow/shadow_win.bmp", 207, 140, 3, 2, true, RGB(255, 255, 0));
	//_winAnim = new animation;
	//_winAnim->init(_winImg->getWidth(), _winImg->getHeight(), _winImg->getFrameWidth(), _winImg->getFrameHeight());
	//int winArr[] = { 0, 1, 2, 3 };
	//_winAnim->setPlayFrame(winArr, 4, true);
	//_winAnim->setFPS(1);
	//
	//_winBeforeImg = IMAGEMANAGER->addFrameImage("shadowWinBefore", "./image/playerImg/shadow/shadow_win_before.bmp", 219, 375, 3, 5, true, RGB(255, 255, 0));
	//_winBeforeAnim = new animation;
	//_winBeforeAnim->init(_winBeforeImg->getWidth(), _winBeforeImg->getHeight(), _winBeforeImg->getFrameWidth(), _winBeforeImg->getFrameHeight());
	//int winBeforeArr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	//_winBeforeAnim->setPlayFrame(winArr, 13, true);
	//_winBeforeAnim->setFPS(1);
	//
	//
	//_jumpImg = IMAGEMANAGER->addImage("shadowJump", "./image/playerImg/shadow/shadow_jump.bmp", 51, 59, true, RGB(0, 0, 255));
	//_moveImg = IMAGEMANAGER->addImage("shadowMove", "./image/playerImg/shadow/shadow_move.bmp", 59, 68, true, RGB(0, 0, 255));
	////================================ End �� ���¿� ���� �̹����� �ִϸ��̼��� �⺻������ �ʱ�ȭ ===========================================
	//
	////�⺻������ IDLE �����̴�
	//_status = BATTLE_PLAYER_IDLE;
	//_idleAnim->start();
	////�ٸ� ���¿� ���� �� ������ false�� �ʱ�ȭ �Ѵ�.
	//_playAnimList[0] = true;
	//for (int i = 1; i < MAXANIMATIONNUM; ++i)
	//{
	//	_playAnimList[i] = false;
	//}
	//
	////������� ������ �� ���ʹ� ���� ���� �����Ѵ�.
	//_atkDistance = true;
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

}

void battleShadow::draw()	
{

}

void battleShadow::release()
{

}
