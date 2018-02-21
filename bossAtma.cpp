#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	
	IMAGEMANAGER->addImage("bossAtma�⺻�����̹���", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma��ų�����̹���1", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma��ų�����̹���2", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bossAtma�⺻�����̹���"), 76, 64, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bossAtma��ų�����̹���1"), 53, 102, 1.0f, 0.5f);

	_spellEffect2 = new effect;
	_spellEffect2->init(IMAGEMANAGER->findImage("bossAtma��ų�����̹���2"), 100, 100, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("bossAtma�⺻��������Ʈ", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, 76, 64, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma��ų��������Ʈ", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, 53, 102, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma��ų��������Ʈ2", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, 100, 100, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("bossAtma�⺻����sound", ".\\sound\\sfx\\16Fire1.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("bossAtma��ų����1sound", ".\\sound\\sfx\\13Explosion.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma��ų����2sound", ".\\sound\\sfx\\15Bolt3.wav", true, false);

	//============================================================================================================

	_Lv = 67;										//����
	_maxEXP = 0;	 								//���� ����ġ, �ִ� ����ġ
	_gold = 0;										//��

	_curHP = _maxHP = 55000;						//���� ü��, �ִ� ü��
	_curMP = _maxMP = 19000;						//���� ����, �ִ� ����

	_attack = 20;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 70;									//���� ����
	_a_Def = 75;									//���� ����

	_speed = 63;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����

	_spellPower = (_Lv / 3) * 2;					//������
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "bossAtma�⺻����");
	wsprintf(_skillAttack, "bossAtma��ų����");
}

void bossAtma::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("bossAtma")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void bossAtma::bearSkill()
{

}
