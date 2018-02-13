#include "stdafx.h"
#include "VectorPup.h"
#include "battlePlayerMother.h"

VectorPup::VectorPup()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	_img = IMAGEMANAGER->addFrameImage("vectorPup", ".\\image\\enemyImg\\VectorPup.bmp", 184, 46, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("vectorPup�⺻�����̹���", ".\\image\\enemyEffect\\effect13.bmp", 376, 92, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("vectorPup��ų�����̹���", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("vectorPup�⺻�����̹���"), 94, 92, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("vectorPup��ų�����̹���"), 137, 134, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("vectorPup�⺻��������Ʈ", ".\\image\\enemyEffect\\effect13.bmp", 376, 92, 94, 92, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("vectorPup��ų��������Ʈ", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 11;										//����
	_maxEXP = RND->getFromIntTo(125, 135);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(75, 90);				//��

	_curHP = _maxHP = 166;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 10;							//���� ����, �ִ� ����

	_attack = 14;									//�⺻ ������
	_magic = 10;									//���� ������

	_m_Def = 150;									//���� ����
	_a_Def = 80;									//���� ����

	_speed = 25;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}

VectorPup::~VectorPup()
{

}

//HRESULT VectorPup::init()
//{
//	
//
//	return S_OK;
//}

void VectorPup::update()
{
	if (_turnEnd == false)
	{
		//ī��Ʈ �ܻ�
		_count++;

		//_count�� 21���� ������ ��¦��¦
		if (_count < 21) glitter();

		//���ʹ��� ���°� ���� �Ǵ� ��ų���� ���¸� �������� ���� 
		if (_state == ENEMY_NULL)
		{
			//_state = ENEMY_HIT;
			_state = RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL);				//���� or ���� ����
			_rndNum = RND->getFromIntTo(0, 10);								//��ųȮ���� �����ϱ� ���� ������
		}

		//���ʹ� ���� ���¸�
		if ((_state == ENEMY_HIT && _rndNum <= 7) || (_state == ENEMY_SPELL && _rndNum <= 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play("vectorPup�⺻��������Ʈ", 800, 320);
				SOUNDMANAGER->play("vectorPup��ų����sound", CH_EFFECT03, 1.0f);

				_effectFire = false;
			}
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play("vectorPup��ų��������Ʈ", 800, 320);
				SOUNDMANAGER->play("vectorPup��ų����sound", CH_EFFECT03, 1.0f);

				_effectFire = false;

			}
		}

		//_count�� 150���� ũ�� ���� �÷��̾�� �ѱ��
		if (_count > 150)
		{
			_turnEnd = true;
			_effectFire = true;
			_state = ENEMY_NULL;
			_glitterCount = 0;
			_count = 0;
		}
	}
}

void VectorPup::render() 
{
	IMAGEMANAGER->findImage("vectorPup")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("vectorPup")->frameRender(getMemDC(), _x, _y);
}

void VectorPup::vectorPupAttack()
{
	

}

void VectorPup::vectorPupSkill()
{

}