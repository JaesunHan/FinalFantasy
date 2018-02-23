#include "stdafx.h"
#include "gobbler.h"
#include "battlePlayerMother.h"

gobbler::gobbler()
{
	//=================================================== ���ʹ� �̹��� ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("gobbler", ".\\image\\enemyImg\\gobbler.bmp", 334, 171, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= ���ʹ� ����Ʈ �̹��� =====================================================
	
	IMAGEMANAGER->addImage("gobbler�⺻�����̹���", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("gobbler��ų�����̹���", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("gobbler�⺻�����̹���"), 94, 117, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("gobbler��ų�����̹���"), 120, 80, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("gobbler�⺻����", ".\\image\\enemyEffect\\effect5.bmp", 846, 117, 94, 117, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("gobbler��ų����", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, 120, 80, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("gobbler�⺻����", ".\\sound\\sfx\\91Idk.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("gobbler��ų����", ".\\sound\\sfx\\73NarsheWind.wav", true, false);

	//============================================================================================================

	_Lv = 19;										//����
	_maxEXP = RND->getFromIntTo(400, 450);			//���� ����ġ, �ִ� ����ġ
	_gold = RND->getFromIntTo(230, 270);			//��

	_curHP = _maxHP = 470;							//���� ü��, �ִ� ü��
	_curMP = _maxMP = 63;							//���� ����, �ִ� ����

	_attack = 13;									//���� ���ݷ�
	_magic = 8;										//���� ���ݷ�

	_m_Def = 120;									//���� ����
	_a_Def = 170;									//���� ����

	_speed = 30;									//���� Ÿ�̸�

	_evasion = 0;									//ȸ����
	_hitRate = 100;									//���߷�
	_block = 0;										//�����

	_spellPower = _Lv;								//������
}


gobbler::~gobbler()
{

}

void gobbler::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "gobbler�⺻����");
	wsprintf(_skillAttack, "gobbler��ų����");

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

void gobbler::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("gobbler")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void gobbler::bearSkill()
{

}
