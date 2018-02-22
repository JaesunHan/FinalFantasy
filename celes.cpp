#include "stdafx.h"
#include "celes.h"
#include "weaponItem.h"

celes::celes()
{
	playerMother::playerMother();
	wsprintf(_name, "CELES");
	wsprintf(_job, "Rune Knight");
	_Lv = 3, _curEXP = 96; _maxEXP = 208;
	_curHP = 44 + 23, _maxHP = 44 + 23, _curMP = 15 + 11, _maxMP = 15 + 11;
	_strength = 34, _speed = 34, _stamina = 31;
	_magic = 36, _attack = 16, _a_Def = 44;
	_evasion = 7, _m_Def = 31, _m_evasion = 9;
	_partyIdx = 2;

	_spellPower = _Lv;

	//==============================마법 공격 세팅
	//마법 공격 1 - 아군 힐
	magic* tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Celes::Heal Magic", "./image/playerImg/playerEffectImage/playerSkill2.bmp", 445, 45, 5, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Celes::Heal Magic", "./image/playerImg/playerEffectImage/playerSkill2.bmp", "힐!", 10, 5, 0, 1, 0);
	_myUsableMagic.push_back(tmpMagic);

	//마법공격 2 - 번개 공격
	tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Celes::Thunder Magic", "./image/playerImg/playerEffectImage/playerSkill5.bmp", 472, 126, 8, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Celes::Thunder Magic", "./image/playerImg/playerEffectImage/playerSkill5.bmp", "뇌신!", 62, 21, 150, 0, 0);
	_myUsableMagic.push_back(tmpMagic);
}


celes::~celes()
{
}
