#include "stdafx.h"
#include "DarkWind.h"
#include "battlePlayerMother.h"

DarkWind::DarkWind()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	_img = IMAGEMANAGER->addFrameImage("darkWind", ".\\image\\enemyImg\\DarkWind.bmp", 132, 81, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("darkWind�⺻�����̹���", ".\\image\\enemyEffect\\effect12.bmp", 310, 62, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("darkWind��ų�����̹���", ".\\image\\enemyEffect\\effect10.bmp", 679, 109, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("darkWind�⺻�����̹���"), 117, 85, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("darkWind��ų�����̹���"), 117, 85, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("darkWind�⺻��������Ʈ", ".\\image\\enemyEffect\\effect12.bmp", 310, 62, 62, 62, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("darkWind��ų��������Ʈ", ".\\image\\enemyEffect\\effect10.bmp", 679, 109, 97, 109, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 5;										//����
	_maxEXP = RND->getFromIntTo(25, 30);			//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(38, 42);				//��

	_curHP = _maxHP = 34;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 0;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 140;									//���� ����
	_a_Def = 55;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


DarkWind::~DarkWind()
{

}

//HRESULT DarkWind::init()
//{
//
//
//	return S_OK;
//}

void DarkWind::update()
{
	if (_turnEnd == false)
	{
		_count++;
		if (_count < 50) glitter();

		if (_effectFire == true)
		{
			EFFECTMANAGER->play("darkWind�⺻��������Ʈ", 800, 320);

			_effectFire = false;
		}
		//if (_effectFire == true)
		//{
		//	EFFECTMANAGER->play("darkWind��ų��������Ʈ", 800, 320);
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

void DarkWind::render()
{
	IMAGEMANAGER->findImage("darkWind")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("darkWind")->frameRender(getMemDC(), _x, _y);
}

void DarkWind::darkWindSkill()
{

}