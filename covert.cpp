#include "stdafx.h"
#include "covert.h"
#include "battlePlayerMother.h"

covert::covert()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	_img = IMAGEMANAGER->addFrameImage("covert", ".\\image\\enemyImg\\covert.bmp", 260, 91, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("covert�⺻�����̹���", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("covert��ų�����̹���", ".\\image\\enemyEffect\\effect8.bmp", 378, 107, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("covert�⺻�����̹���"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("covert��ų�����̹���"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("covert�⺻��������Ʈ", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("covert��ų��������Ʈ", ".\\image\\enemyEffect\\effect8.bmp", 378, 107, 54, 107, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 44;										//����
	_maxEXP = RND->getFromIntTo(1600, 1900);		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(1600, 1900);			//��

	_curHP = _maxHP = 4530;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 240;							//���� ����, �ִ� ����

	_attack = 25;									//���� ���ݷ�
	_magic = 11;									//���� ���ݷ�

	_m_Def = 150;									//���� ����
	_a_Def = 100;									//���� ����

	_speed = 35;									//���� Ÿ�̸�

	_evasion = 50;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


covert::~covert()
{

}

void covert::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("covert�⺻��������Ʈ", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("covert��ų��������Ʈ", 800, 320);
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

void covert::render()
{
	IMAGEMANAGER->findImage("covert")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("covert")->frameRender(getMemDC(), _x, _y);
}


void covert::bearSkill()
{

}
