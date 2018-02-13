#include "stdafx.h"
#include "samurai.h"
#include "battlePlayerMother.h"

samurai::samurai()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	_img = IMAGEMANAGER->addFrameImage("samurai", ".\\image\\enemyImg\\samurai.bmp", 108, 103, 2, 1, true, RGB(255, 0, 255), true);
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	IMAGEMANAGER->addImage("samurai�⺻�����̹���", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("samurai��ų�����̹���", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("samurai�⺻�����̹���"), 150, 130, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("samurai��ų�����̹���"), 100, 50, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("samurai�⺻��������Ʈ", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 1000);
	EFFECTMANAGER->addEffect("samurai��ų��������Ʈ", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, 100, 50, 1.0f, 1.0f, 1000);
	//===========================================================================================================================

	_Lv = 40;										//����
	_maxEXP = RND->getFromIntTo(1500, 1600);		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(750, 850);			//��

	_curHP = _maxHP = 3000;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 500;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 20;									//���� ����
	_a_Def = 10;									//���� ����

	_speed = 20;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����
}


samurai::~samurai()
{

}

void samurai::update()
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
				EFFECTMANAGER->play("samurai�⺻��������Ʈ", 800, 320);
				SOUNDMANAGER->play("samurai�⺻����sound", CH_EFFECT03, 1.0f);

				_effectFire = false;
			}
		}
		if ((_state == ENEMY_HIT && _rndNum > 7) || (_state == ENEMY_SPELL && _rndNum > 7))
		{
			//_count�� 80���� Ŀ���� ���� ����Ʈ�� �׷���
			if (_count > 80 && _effectFire == true)
			{
				EFFECTMANAGER->play("samurai��ų��������Ʈ", 800, 320);
				SOUNDMANAGER->play("samurai��ų����sound", CH_EFFECT03, 1.0f);

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

void samurai::render()
{
	IMAGEMANAGER->findImage("samurai")->alphaFrameRender(getMemDC(), _x - _img->getWidth() / 2, _y - _img->getHeight() / 2, _frameX, 0, _alpha);
	//IMAGEMANAGER->findImage("samurai")->frameRender(getMemDC(), _x, _y);
}


void samurai::bearSkill()
{

}
