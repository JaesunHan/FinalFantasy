#include "stdafx.h"
#include "guard.h"
#include "battlePlayerMother.h"

guard::guard()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("guard", ".\\image\\enemyImg\\guard.bmp", 132, 62, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	
	IMAGEMANAGER->addImage("guard�⺻�����̹���", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("guard��ų�����̹���", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("guard�⺻�����̹���"), 150, 130, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("guard��ų�����̹���"), 192, 192, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("guard�⺻����", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("guard��ų����", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("guard�⺻����", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("guard��ų����", ".\\sound\\sfx\\BEDeathToll.wav", true, false);

	//============================================================================================================

	_Lv = 5;										//����
	_maxEXP = RND->getFromIntTo(45, 50) * 2; 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(45, 50);				//��

	_curHP = _maxHP = 40;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 15;							//���� ����, �ִ� ����

	_attack = 16;									//���� ���ݷ�
	_magic = 6;										//���� ���ݷ�

	_m_Def = 140;									//���� ����
	_a_Def = 100;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
	
	_spellPower = _Lv - 2;							//������

	setItemDropRate(01, 02, 30, 30, 15, 12, 06, 03, 01, 00, 00);
	setItemString();
}


guard::~guard()
{

}

void guard::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "guard�⺻����");
	wsprintf(_skillAttack, "guard��ų����");
}

void guard::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("guard")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void guard::bearSkill()
{

}
