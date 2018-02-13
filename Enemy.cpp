#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{

}

//	     몬스터를 뿌려줄 x,     y
HRESULT Enemy::init(int x, int y)
{
	//============================================== 기타등등 사운드 ==============================================
	
	SOUNDMANAGER->addSound("monsterDie", ".\\sound\\sfx\\2DMonsterDeath.wav", true, false);
	SOUNDMANAGER->addSound("attackMissSound", ".\\sound\\sfx\\0DMiss.wav", true, false);

	//============================================================================================================

	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("bear기본공격sound", ".\\sound\\sfx\\8BClawSlash.wav", true, false);
	SOUNDMANAGER->addSound("tornadoShark기본공격sound", ".\\sound\\sfx\\8BClawSlash.wav", true, false);
	SOUNDMANAGER->addSound("vectorPup기본공격sound", ".\\sound\\sfx\\8BClawSlash.wav", true, false);
	SOUNDMANAGER->addSound("samurai기본공격sound", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);
	SOUNDMANAGER->addSound("covert기본공격sound", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);
	SOUNDMANAGER->addSound("guard기본공격sound", ".\\sound\\sfx\\2ESwordSlashLong.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma기본공격sound", ".\\sound\\sfx\\16Fire1.wav", true, false);
	SOUNDMANAGER->addSound("gobbler기본공격sound", ".\\sound\\sfx\\91Idk.wav", true, false);
	SOUNDMANAGER->addSound("darkWind기본공격sound", ".\\sound\\sfx\\C0Bird.wav", true, false);
	SOUNDMANAGER->addSound("siren기본공격sound", ".\\sound\\sfx\\BFBuyingSelling.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("gobbler스킬공격sound", ".\\sound\\sfx\\73NarsheWind.wav", true, false);
	SOUNDMANAGER->addSound("tornadoShark스킬공격sound", ".\\sound\\sfx\\73NarsheWind.wav", true, false);
	SOUNDMANAGER->addSound("samurai스킬공격sound", ".\\sound\\sfx\\7FMechDispatch.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma스킬공격1sound", ".\\sound\\sfx\\13Explosion.wav", true, false);
	SOUNDMANAGER->addSound("bossAtma스킬공격2sound", ".\\sound\\sfx\\15Bolt3.wav", true, false);
	SOUNDMANAGER->addSound("siren스킬공격sound", ".\\sound\\sfx\\BBBigClose.wav", true, false);
	SOUNDMANAGER->addSound("darkWind스킬공격sound", ".\\sound\\sfx\\40CyanSwdtechActivation.wav", true, false);
	SOUNDMANAGER->addSound("bear스킬공격sound", ".\\sound\\sfx\\37Ice2Part2.wav", true, false);
	SOUNDMANAGER->addSound("guard스킬공격sound", ".\\sound\\sfx\\BEDeathToll.wav", true, false);
	SOUNDMANAGER->addSound("covert스킬공격sound", ".\\sound\\sfx\\4BDrill.wav", true, false);

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

//몬스터 턴이 되면
void Enemy::enemyTurn(int damage)
{
	if (_state == RND->getFromIntTo(ENEMY_HIT, ENEMY_SPELL));
	{
		//물리 데미지 공식
		//공식 = Damage = Level * Level * (Battle Power * 4 + Vigor) / 256
		//Vigor = 56 ~ 63 랜덤수
		int _2Lv;
		_2Lv = _Lv * _Lv;
		
		_damage = _2Lv * (damage * 4 + (RND->getFromIntTo(56, 63))) / 256; 
		
		//스킬 데미지 공식
		_spellDamage = _damage * RND->getFromFloatTo(1.2f, 2.5f);
	}
}

//에너미 턴일때 어떤 에너미의 턴인지 알기위한 함수 (반짝거림)
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
