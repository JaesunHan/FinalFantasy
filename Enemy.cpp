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
	
	//SOUNDMANAGER->addSound("monsterDie", ".\\sound\\FF6SfxPart1\\2DMonsterDeath.wav", true, false);
	//SOUNDMANAGER->addSound("attackMissSound", ".\\sound\\FF6SfxPart1\\0DMiss.wav", true, false);

	//============================================================================================================

	//============================================== �⺻���� ���� ==============================================
	
	SOUNDMANAGER->addSound("bear�⺻����sound", ".\\sound\\FF6SfxPart1\\8BClawSlash.wav", true, false);
	//SOUNDMANAGER->addSound("samurai�⺻����sound", ".\\sound\\FF6SfxPart1\\2ESwordSlashLong.wav", true, false);
	//SOUNDMANAGER->addSound("bossAtma�⺻����sound", ".\\sound\\FF6SfxPart1\\16Fire1.wav", true, false);
	//SOUNDMANAGER->addSound("gobbler�⺻����sound", ".\\sound\\FF6SfxPart2\\91Idk.wav", true, false);
	//SOUNDMANAGER->addSound("darkWind�⺻����sound", ".\\sound\\FF6SfxPart2\\C0Bird.wav", true, false);

	//============================================================================================================

	//============================================== ��ų���� ���� ==============================================
	
	//SOUNDMANAGER->addSound("gobbler��ų����sound", ".\\sound\\FF6SfxPart1\\6EWind.wav", true, false);
	//SOUNDMANAGER->addSound("samurai��ų����sound", ".\\sound\\FF6SfxPart1\\7FMechDispatch.wav", true, false);
	//SOUNDMANAGER->addSound("bossAtma��ų����1sound", ".\\sound\\FF6SfxPart1\\13Explosion.wav", true, false);
	//SOUNDMANAGER->addSound("bossAtma��ų����2sound", ".\\sound\\FF6SfxPart1\\15Bolt3.wav", true, false);
	//SOUNDMANAGER->addSound("siren��ų����sound", ".\\sound\\FF6SfxPart2\\BBBigClose.wav", true, false);

	//============================================================================================================

	//SOUNDMANAGER->addSound("samurai�⺻����sound", ".\\sound\\FF6SfxPart1\\2ESwordSlashLong.wav", true, false);
	//SOUNDMANAGER->addSound("samurai�⺻����sound", ".\\sound\\FF6SfxPart1\\2ESwordSlashLong.wav", true, false);
	//SOUNDMANAGER->addSound("samurai�⺻����sound", ".\\sound\\FF6SfxPart1\\2ESwordSlashLong.wav", true, false);
	//SOUNDMANAGER->addSound("samurai�⺻����sound", ".\\sound\\FF6SfxPart1\\2ESwordSlashLong.wav", true, false);

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
