#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("bossAtma�⺻�����̹���", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma��ų�����̹���", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bossAtma��ų�����̹���2", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bossAtma�⺻�����̹���"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bossAtma��ų�����̹���"), 117, 85, 1.0f, 0.5f);

	_spellEffect2 = new effect;
	_spellEffect2->init(IMAGEMANAGER->findImage("bossAtma��ų�����̹���2"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("bossAtma�⺻��������Ʈ", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, 76, 64, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("bossAtma��ų��������Ʈ", ".\\image\\enemyEffect\\effect6.bmp", 583, 102, 53, 102, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("bossAtma��ų��������Ʈ2", ".\\image\\enemyEffect\\effect11.bmp", 2100, 100, 100, 100, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

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
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("bossAtma�⺻��������Ʈ", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("bossAtma��ų��������Ʈ", 800, 320);
		//
		//	_effectFire = false;
		//}

		if (_count > 150)
		{
			_turnEnd = true;
			_effectFire = true;

			_count = 0;
		}
	}
}

void bossAtma::render()
{
	IMAGEMANAGER->findImage("bossAtma")->alphaFrameRender(getMemDC(), _x, _y, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("bossAtma")->frameRender(getMemDC(), _x, _y);
}


void bossAtma::bearSkill()
{

}
