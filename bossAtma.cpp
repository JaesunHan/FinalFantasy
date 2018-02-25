#include "stdafx.h"
#include "bossAtma.h"
#include "battlePlayerMother.h"

bossAtma::bossAtma()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("bossAtma", ".\\image\\enemyImg\\bossAtma.bmp", 1000, 500, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	
	EFFECTMANAGER->addEffect("bossAtma�⺻����", ".\\image\\enemyEffect\\effect4.bmp", 304, 64, 76, 64, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma��ų����1", ".\\image\\enemyEffect\\effect11.bmp", 583, 102, 53, 102, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bossAtma��ų����2", ".\\image\\enemyEffect\\effect6.bmp", 2100, 100, 100, 100, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("bossAtma�⺻����", ".\\sound\\sfx\\16Fire1.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("bossAtma��ų����1", ".\\sound\\sfx\\13Explosion.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma��ų����2", ".\\sound\\sfx\\15Bolt3.wav", true, false);

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

	_spellPower = _Lv;								//������
	_spellPower2 = _Lv * 1.2f;						//������2
}


bossAtma::~bossAtma()
{

}

void bossAtma::update()
{
	if (_turnEnd == false)
	{
		if (_count == 0)
		{
			damageAlgorithm();													//���ʹ� ���� �Ǹ� ������ ���� �Լ��� ����
			_rndNum = RND->getFromIntTo(1, 10);									//��ųȮ���� �����ϱ� ���� ������
		}
		_count++;															//ī��Ʈ �ܻ�

		//_count�� 21���� ������ ��¦��¦
		if (_count < 21) glitter();


		wsprintf(_basicAttack, "bossAtma�⺻����");
		wsprintf(_skillAttack, "bossAtma��ų����1");
		wsprintf(_skillAttack2, "bossAtma��ų����2");
	
		//���ʹ� �⺻ ���� ����
		if (_rndNum <= 3)
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 50 && _effectFire == true)
			{
				EFFECTMANAGER->play(_basicAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(_basicAttack, CH_EFFECT05, 1.0f);
				_target->setCurHP(_target->getCurHP() - _damage);

				if (_target->getCurHP() <= 0)
				{
					_target->setCurHP(0);
				}

				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_damage);
		}
		else if (_rndNum <= 7)
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 50 && _effectFire == true)
			{
				EFFECTMANAGER->play(_skillAttack, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(_skillAttack, CH_EFFECT05, 1.0f);
				_target->setCurHP(_target->getCurHP() - _spellDamage);

				if (_target->getCurHP() <= 0)
				{
					_target->setCurHP(0);
				}

				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_spellDamage);
		}//���ʹ� ��ų2 ���� ����
		else
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 50 && _effectFire == true)
			{
				EFFECTMANAGER->play(_skillAttack2, _target->getPosX() + _target->getWidth() / 2, _target->getPosY() + _target->getHeight() / 2);
				SOUNDMANAGER->play(_skillAttack2, CH_EFFECT05, 1.0f);
				_target->setCurHP(_target->getCurHP() - _spellDamage2);

				if (_target->getCurHP() <= 0)
				{
					_target->setCurHP(0);
				}

				_effectFire = false;
			}
			wsprintf(_damageNum, "%d", (int)_spellDamage2);
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

void bossAtma::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("bossAtma")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void bossAtma::bearSkill()
{

}
