#include "stdafx.h"
#include "Locke.h"
#include "weaponItem.h"

Locke::Locke()
{
	playerMother::playerMother();
	wsprintf(_name, "LOCKE");
	wsprintf(_job, "Treasure Hunter");
	_Lv = 3, _curEXP =96; _maxEXP = 208;
	_curHP = 48 + 23, _maxHP = 48 + 23, _curMP = 7 + 11, _maxMP = 7 + 11;
	_strength = 37, _speed = 40, _stamina = 31;
	_magic = 28, _attack = 14, _a_Def = 46;
	_evasion = 15, _m_evasion = 2, _m_Def = 23;
	_partyIdx = 1;

	_spellPower = _Lv;


	//========================== 마법 공격 세팅=========================
	//마법 공격 1 - 불 공격
	magic* tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Locke::fire Magic1", "./image/playerImg/playerEffectImage/playerSkill4.bmp", 2944, 108, 23, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Locke::fire Magic1", "./image/playerImg/playerEffectImage/playerSkill4.bmp", "파이어 볼!", 21, 4, 150, 0, 0);
	_myUsableMagic.push_back(tmpMagic);

	//마법공격 2 - 불 공격
	tmpMagic = new magic;
	IMAGEMANAGER->addFrameImage("Locke::fire Magic2", "./image/playerImg/playerEffectImage/playerSkill3.bmp", 3720, 245, 15, 1, true, RGB(255, 0, 255));
	tmpMagic->init("Locke::fire Magic2", "./image/playerImg/playerEffectImage/playerSkill3.bmp", "화염 폭발!", 60, 45, 150, 0, 0);
	_myUsableMagic.push_back(tmpMagic);
}

Locke::~Locke()
{
}
