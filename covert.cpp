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
	_maxEXP = RND->getFromIntTo(1600, 1900);		//���� ����ġ, �ִ� ����ġ
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
}


covert::~covert()
{

}

void covert::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "covert�⺻����");
	wsprintf(_skillAttack, "covert��ų����");

	switch (_enemyItemNum)
	{
		case 1:
			if (_enemyItemNum <= 2)
			{
				wsprintf(_itemString, "�ް�������");
			}
		break;

		case 2:
			if (_enemyItemNum >= 3 && _enemyItemNum <= 6)
			{
				wsprintf(_itemString, "������");
			}
		break;

		case 3:
			if (_enemyItemNum >= 7 && _enemyItemNum <= 31)
			{
				wsprintf(_itemString, "���׸�");
			}
		break;

		case 4:
			if (_enemyItemNum >= 32 && _enemyItemNum <= 56)
			{
				wsprintf(_itemString, "����");
			}
		break;

		case 5:
			if (_enemyItemNum >= 57 && _enemyItemNum <= 71)
			{
				wsprintf(_itemString, "���");
			}
		break;

		case 6:
			if (_enemyItemNum >= 72 && _enemyItemNum <= 81)
			{
				wsprintf(_itemString, "����");
			}
		break;

		case 7:
			if (_enemyItemNum >= 82 && _enemyItemNum <= 86)
			{
				wsprintf(_itemString, "ħ��");
			}
		break;

		case 8:
			if (_enemyItemNum >= 87 && _enemyItemNum <= 92)
			{
				wsprintf(_itemString, "Thief Knife");
			}
		break;

		case 9:
			if (_enemyItemNum >= 93 && _enemyItemNum <= 97)
			{
				wsprintf(_itemString, "Striker");
			}
		break;

		case 10:
			if (_enemyItemNum >= 98 && _enemyItemNum <= 99)
			{
				wsprintf(_itemString, "Wing Edge");
			}
		break;
		
		case 11:
			if (_enemyItemNum == 100)
			{
				wsprintf(_itemString, "Illumina");
			}
		break;
	}
}

void covert::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("covert")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void covert::bearSkill()
{

}
