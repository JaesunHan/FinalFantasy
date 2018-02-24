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
	_atkEffect->init(IMAGEMANAGER->findImage("covert�⺻�����̹���"), 192, 192, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("covert��ų�����̹���"), 54, 107, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("covert�⺻����", ".\\image\\enemyEffect\\effect2.bmp", 1536, 192, 192, 192, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("covert��ų����", ".\\image\\enemyEffect\\effect8.bmp", 378, 107, 54, 107, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("covert�⺻����", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("covert��ų����", ".\\sound\\sfx\\4BDrill.wav", true, false);

	//============================================================================================================

	_Lv = 44;										//����
	_maxEXP = RND->getFromIntTo(1600, 1900) * 8;	//���� ����ġ, �ִ� ����ġ
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

	_spellPower = _Lv;								//������

	setItemDropRate(02, 04, 25, 25, 15, 10, 05, 06, 05, 02, 01);
	setItemString();
}


covert::~covert()
{

}

void covert::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "covert�⺻����");
	wsprintf(_skillAttack, "covert��ų����");
}

void covert::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("covert")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void covert::bearSkill()
{

}
