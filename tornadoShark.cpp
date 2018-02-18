#include "stdafx.h"
#include "tornadoShark.h"
#include "battlePlayerMother.h"

tornadoShark::tornadoShark()
{
	//=================================================== 에너미 이미지 ==========================================================
	
	_img = IMAGEMANAGER->addFrameImage("tornadoShack", ".\\image\\enemyImg\\tornadoShack.bmp", 262, 118, 2, 1, true, RGB(255, 0, 255), true);
	
	//===========================================================================================================================

	//================================================= 에너미 이펙트 이미지 =====================================================
	
	IMAGEMANAGER->addImage("tornadoShark기본공격이미지", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("tornadoShark스킬공격이미지", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, true, RGB(255, 0, 255), true);

	_atkEffect = new effect;
	_atkEffect->init(IMAGEMANAGER->findImage("tornadoShark기본공격이미지"), 137, 134, 1.0f, 0.5f);

	_spellEffect = new effect;
	_spellEffect->init(IMAGEMANAGER->findImage("tornadoShark스킬공격이미지"), 120, 80, 1.0f, 0.5f);

	EFFECTMANAGER->addEffect("tornadoShark기본공격", ".\\image\\enemyEffect\\effect16.bmp", 411, 134, 137, 134, 1.0f, 1.0f, 2);
	EFFECTMANAGER->addEffect("tornadoShark스킬공격", ".\\image\\enemyEffect\\effect7.bmp", 1320, 80, 120, 80, 1.0f, 1.0f, 2);
	
	//===========================================================================================================================
	
	//============================================== 기본공격 사운드 ==============================================

	SOUNDMANAGER->addSound("tornadoShark기본공격", ".\\sound\\sfx\\8BClawSlash.wav", true, false);

	//============================================================================================================

	//============================================== 스킬공격 사운드 ==============================================

	SOUNDMANAGER->addSound("tornadoShark스킬공격", ".\\sound\\sfx\\73NarsheWind.wav", true, false);

	//============================================================================================================

	_Lv = 29;										//레벨
	_maxEXP = RND->getFromIntTo(500, 550);	 		//현재 경험치, 최대 경험치
	_gold = RND->getFromIntTo(1100, 1300);			//돈

	_curHP = _maxHP = 1318;							//현재 체력, 최대 체력
	_curMP = _maxMP = 100;							//현재 마력, 최대 마력

	_attack = 15;									//물리 공격력
	_magic = 10;									//마법 공격력

	_m_Def = 153;									//마법 방어력
	_a_Def = 102;									//물리 방어력

	_speed = 30;									//공격 타이머

	_evasion = 0;									//회피율
	_hitRate = 100;									//명중률
	_block = 0;										//방어율

	_spellPower = _Lv;								//마법력
}


tornadoShark::~tornadoShark()
{

}

void tornadoShark::update()
{
	Enemy::update();
	wsprintf(basicAttack, "tornadoShark기본공격");
	wsprintf(skillAttack, "tornadoShark스킬공격");
}

void tornadoShark::render()
{
	Enemy::render();
	IMAGEMANAGER->findImage("tornadoShack")->alphaFrameRender(getMemDC(), _x - _img->getFrameWidth() / 2, _y - _img->getFrameHeight() / 2, _frameX, 0, _alpha);
}


void tornadoShark::bearSkill()
{

}
