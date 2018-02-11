#include "stdafx.h"
#include "Bear.h"
#include "battlePlayerMother.h"

Bear::Bear()
{
	//���ʹ� �̹���
	IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 180, 106, 2, 1, true, RGB(255, 0, 255), true);

	//���ʹ� ����Ʈ �̹���
	IMAGEMANAGER->addImage("����Ʈ", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, true, RGB(255, 0, 255), true);
	
	_test = new effect;
	_test->init(IMAGEMANAGER->findImage("����Ʈ"), 117, 85, 1.0f, 0.5f);
	
	EFFECTMANAGER->addEffect("����", ".\\image\\enemyEffect\\effect4.bmp", 585, 85, 117, 85, 1.0f, 1.0f, 1000); 

	_Lv = 5;										//����
	_maxEXP = RND->getFromIntTo(150, 170);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(172, 196);			//��

	_curHP = _maxHP = 275;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 0;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 140;									//���� ����
	_a_Def = 40;									//���� ����

	_speed = 25;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}

Bear::~Bear()
{

}

//HRESULT Bear::init()
//{
//
//
//	return S_OK;
//}

void Bear::update()
{
	if (_effectFire == true)
	{
		EFFECTMANAGER->play("����", 800, 320);

		_effectFire = false;
	}

	if (_turnEnd == false)
	{
		_count++;
		
		if (_count > 100)
		{
			_turnEnd = true;
			_effectFire = true;

			_count = 0;
		}
	}
}

void Bear::render()
{
	IMAGEMANAGER->findImage("bear")->frameRender(getMemDC(), _x, _y);
}

void Bear::bearSkill()
{

}