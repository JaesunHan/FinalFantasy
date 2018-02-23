#include "stdafx.h"
#include "siren.h"
#include "battlePlayerMother.h"

siren::siren()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("siren", ".\\image\\enemyImg\\siren.bmp", 368, 148, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	
	IMAGEMANAGER->addImage("siren�⺻�����̹���", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("siren��ų�����̹���", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("siren�⺻�����̹���"), 76, 76, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("siren��ų�����̹���"), 80, 59, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("siren�⺻����", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, 76, 76, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("siren��ų����", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, 80, 59, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("siren�⺻����", ".\\sound\\sfx\\BFBuyingSelling.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("siren��ų����", ".\\sound\\sfx\\BBBigClose.wav", true, false);

	//============================================================================================================

	_Lv = 50;										//����
	_maxEXP = RND->getFromIntTo(2800, 3200);		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(1100, 1300);			//��

	_curHP = _maxHP = 10050;						//���� ü��, �ִ� ü��
	_curMP = _maxMP = 12850;						//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 15;									//���� ���ݷ�

	_m_Def = 170;									//���� ����
	_a_Def = 70;									//���� ����

	_speed = 35;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����

	_spellPower = (_Lv / 3) * 2;					//������

	setItemDropRate(03, 06, 22, 22, 15, 10, 05, 05, 05, 05, 02);
	setItemString();
}


siren::~siren()
{

}

void siren::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "siren�⺻����");
	wsprintf(_skillAttack, "siren��ų����");
}

void siren::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("siren")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void siren::bearSkill()
{

}
