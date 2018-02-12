#include "stdafx.h"
#include "tornadoShark.h"
#include "battlePlayerMother.h"

tornadoShark::tornadoShark()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	_img = IMAGEMANAGER->addFrameImage("tornadoShack", ".\\image\\enemyImg\\tornadoShack.bmp", 262, 118, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("tornadoShark�⺻�����̹���", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("tornadoShark��ų�����̹���", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("tornadoShark�⺻�����̹���"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("tornadoShark��ų�����̹���"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("tornadoShark�⺻��������Ʈ", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("tornadoShark��ų��������Ʈ", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, 120, 80, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 29;										//����
	_maxEXP = RND->getFromIntTo(500, 550);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(1100, 1300);			//��

	_curHP = _maxHP = 1318;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 100;							//���� ����, �ִ� ����

	_attack = 15;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 153;									//���� ����
	_a_Def = 102;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


tornadoShark::~tornadoShark()
{

}

void tornadoShark::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("tornadoShark�⺻��������Ʈ", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("tornadoShark��ų��������Ʈ", 800, 320);
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

void tornadoShark::render()
{
	IMAGEMANAGER->findImage("tornadoShack")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("tornadoShack")->frameRender(getMemDC(), _x, _y);
}


void tornadoShark::bearSkill()
{

}
