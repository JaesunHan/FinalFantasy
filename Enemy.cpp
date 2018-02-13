#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

//	     ���͸� �ѷ��� x,     y
HRESULT Enemy::init(int x, int y)
{
	//============================================== ��Ÿ��� ���� ==============================================
	
	SOUNDMANAGER->addSound("monsterDie", ".\\sound\\sfx\\2DMonsterDeath.wav", true, false);
	SOUNDMANAGER->addSound("attackMissSound", ".\\sound\\sfx\\0DMiss.wav", true, false);

	//============================================================================================================

	//============================================== �⺻���� ���� ==============================================

	SOUNDMANAGER->addSound("bear�⺻����sound", ".\\sound\\sfx\\8BClawSlash.wav", true, false);
	SOUNDMANAGER->addSound("tornadoShark�⺻����sound", ".\\sound\\sfx\\8BClawSlash.wav", true, false);
	SOUNDMANAGER->addSound("vectorPup�⺻����sound", ".\\sound\\sfx\\8BClawSlash.wav", true, false);
	SOUNDMANAGER->addSound("samurai�⺻����sound", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);
	SOUNDMANAGER->addSound("covert�⺻����sound", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);
	SOUNDMANAGER->addSound("guard�⺻����sound", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma�⺻����sound", ".\\sound\\sfx\\16Fire1.wav", true, false);
	SOUNDMANAGER->addSound("gobbler�⺻����sound", ".\\sound\\sfx\\91Idk.wav", true, false);
	SOUNDMANAGER->addSound("darkWind�⺻����sound", ".\\sound\\sfx\\C0Bird.wav", true, false);
	SOUNDMANAGER->addSound("siren�⺻����sound", ".\\sound\\sfx\\BFBuyingSelling.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================

	SOUNDMANAGER->addSound("gobbler��ų����sound", ".\\sound\\sfx\\73NarsheWind.wav", true, false);
	SOUNDMANAGER->addSound("tornadoShark��ų����sound", ".\\sound\\sfx\\73NarsheWind.wav", true, false);
	SOUNDMANAGER->addSound("samurai��ų����sound", ".\\sound\\sfx\\7FMechDispatch.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma��ų����1sound", ".\\sound\\sfx\\13Explosion.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma��ų����2sound", ".\\sound\\sfx\\15Bolt3.wav", true, false);
	SOUNDMANAGER->addSound("siren��ų����sound", ".\\sound\\sfx\\BBBigClose.wav", true, false);
	SOUNDMANAGER->addSound("darkWind��ų����sound", ".\\sound\\sfx\\40CyanSwdtechActivation.wav", true, false);
	SOUNDMANAGER->addSound("bear��ų����sound", ".\\sound\\sfx\\37Ice2Part2.wav", true, false);
	SOUNDMANAGER->addSound("guard��ų����sound", ".\\sound\\sfx\\BEDeathToll.wav", true, false);
	SOUNDMANAGER->addSound("covert��ų����sound", ".\\sound\\sfx\\4BDrill.wav", true, false);

	//============================================================================================================
	
	_x = x;
	_y = y;
	_alpha = 255;
	_frameX = 0;
	_glitterCount = 0;
	_rndNum = 0;

	_state = ENEMY_NULL;

	_turnEnd = false;
	_effectFire = true;

	return S_OK;
}

void Enemy::update()
{
	
}

void Enemy::render() 
{
	
}

//���� ���� �Ǹ�
void Enemy::enemyTurn(int damage)
{
	if (_state == RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL));
	{
		//���� ������ ����
		//���� = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 ������
		int _2Lv;
		_2Lv = _Lv * _Lv;
		
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256; 
		
		//��ų ������ ����
		_spellDamage = _damage * RND->getFromFloatTo(1.2f, 2.5f);
	}
}

//���ʹ� ���϶� � ���ʹ��� ������ �˱����� �Լ� (��¦�Ÿ�)
void Enemy::glitter()
{
	_glitterCount++;

	if (_glitterCount % 3 == 0)
	{
		_frameX = 1;
		_glitterCount = 0;
	}
	else
	{
		_frameX = 0;
	}
}
