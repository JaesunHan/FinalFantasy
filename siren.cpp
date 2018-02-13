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

	EFFECTMANAGER->addEffect("siren�⺻��������Ʈ", ".\\image\\enemyEffect\\effect14.bmp", 608, 76, 76, 76, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("siren��ų��������Ʈ", ".\\image\\enemyEffect\\effect9.bmp", 480, 59, 80, 59, 1.0f, 1.0f, 1000);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("siren�⺻����sound", ".\\sound\\sfx\\BFBuyingSelling.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("siren��ų����sound", ".\\sound\\sfx\\BBBigClose.wav", true, false);

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
}


siren::~siren()
{

}

void siren::update()
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
				EFFECTMANAGER->play("siren�⺻��������Ʈ", 800, 320);
				SOUNDMANAGER->play("siren�⺻����sound", CH_EFFECT03, 1.0f);

				_effectFire = false;
			}
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play("siren��ų��������Ʈ", 800, 320);
				SOUNDMANAGER->play("siren��ų����sound", CH_EFFECT03, 1.0f);

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

void siren::render()
{
	IMAGEMANAGER->findImage("siren")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth(), _y - _img->getFrameHeight(), _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("siren")->frameRender(getMemDC(), _x, _y);
}


void siren::bearSkill()
{

}
