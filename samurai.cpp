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

	EFFECTMANAGER->addEffect("samurai�⺻����", ".\\image\\enemyEffect\\effect1.bmp", 1800, 130, 150, 130, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("samurai��ų����", ".\\image\\enemyEffect\\effect3.bmp", 800, 50, 100, 50, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("samurai�⺻����", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("samurai��ų����", ".\\sound\\sfx\\7FMechDispatch.wav", true, false);

	//============================================================================================================

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

	_spellPower = _Lv - 10;							//������
}


samurai::~samurai()
{

}

void samurai::update()
{
	Enemy::update();
	wsprintf(_basicAttack, "samurai�⺻����");
	wsprintf(_skillAttack, "samurai��ų����");

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

void samurai::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("samurai")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void samurai::bearSkill()
{

}
