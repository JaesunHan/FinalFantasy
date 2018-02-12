#include "stdafx.h"
#include "gobbler.h"
#include "battlePlayerMother.h"

gobbler::gobbler()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	_img = IMAGEMANAGER->addFrameImage("gobbler", ".\\image\\enemyImg\\gobbler.bmp", 334, 171, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("gobbler�⺻�����̹���", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("gobbler��ų�����̹���", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("gobbler�⺻�����̹���"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("gobbler��ų�����̹���"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("gobbler�⺻��������Ʈ", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, 94, 117, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("gobbler��ų��������Ʈ", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, 120, 80, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 19;										//����
	_maxEXP = RND->getFromIntTo(400, 450);			//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(230, 270);			//��

	_curHP = _maxHP = 470;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 63;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 8;										//���� ���ݷ�

	_m_Def = 120;									//���� ����
	_a_Def = 170;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


gobbler::~gobbler()
{

}

void gobbler::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("gobbler�⺻��������Ʈ", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("gobbler��ų��������Ʈ", 800, 320);
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

void gobbler::render()
{
	IMAGEMANAGER->findImage("gobbler")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("gobbler")->frameRender(getMemDC(), _x, _y);
}


void gobbler::bearSkill()
{

}
