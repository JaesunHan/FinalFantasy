#include "stdafx.h"
#include "Bear.h"
#include "battlePlayerMother.h"

Bear::Bear()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("bear", ".\\image\\enemyImg\\bear.bmp", 180, 106, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================
	
	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	
	IMAGEMANAGER->addImage("bear�⺻�����̹���", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("bear��ų�����̹���", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, true, RGB(255, 0, 255), true);
	
	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("bear�⺻�����̹���"), 137, 134, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("bear��ų�����̹���"), 132, 123, 1.0f, 0.5f);
	
	EFFECTMANAGER->addEffect("bear�⺻����", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("bear��ų����", ".\\image\\enemyEffect\\effect15.bmp", 660, 123, 132, 123, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("bear�⺻����", ".\\sound\\sfx\\8BClawSlash.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("bear��ų����", ".\\sound\\sfx\\37Ice2Part2.wav", true, false);

	//============================================================================================================

	_Lv = 5;										//����
	_maxEXP = RND->getFromIntTo(150, 170);	 		//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(172, 196);			//��

	_curHP = _maxHP = 275;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 0;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 10;									//���� ���ݷ�

	_m_Def = 140;									//���� ����
	_a_Def = 40;					 				//���� ����

	_speed = 25;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����

	_spellPower = _Lv;								//������


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
	Enemy::update();
	wsprintf(basicAttack, "bear�⺻����");
	wsprintf(skillAttack, "bear��ų����");
}

void Bear::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("bear")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}

void Bear::bearSkill()
{

}