#include "stdafx.h"
#include "npcManager.h"


npcManager::npcManager()
{
}


npcManager::~npcManager()
{
}

HRESULT npcManager::init()
{
	for (int i = 0; i < 5; ++i)
	{
		npcMother* npc;

		switch (i)
		{
		case NPC_POTION:
			npc = new npc1;
			npc->init(320, 370);
			break;

		case NPC_WEAPON:
			npc = new npc2;
			npc->init(320, 750);
			break;

		case NPC_MAGIC:
			npc = new npc3;
			npc->init(750, 370);
			break;

		case NPC_DEFENCE:
			npc = new npc4;
			npc->init(730, 750);
			break;

		case NPC_INN:
			npc = new npc5;
			npc->init(200, 200);
			break;
		}
		_vNpc.push_back(npc);
	}
	return S_OK;
}

void npcManager::release()
{

	
}

void npcManager::update()
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->update();
	}

	
}

void npcManager::render(HDC hdc, POINT movePt)
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		_vNpc[i]->render(hdc, movePt);
	}



}

void npcManager::beforeRender(HDC hdc, POINT movePt)
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		if (_vNpc[i]->getNpcPoint().y <= _playerPos.y)
		{
			_vNpc[i]->render(hdc, movePt);
		}
	}
}

void npcManager::afterRender(HDC hdc, POINT movePt)
{
	for (int i = 0; i < _vNpc.size(); i++)
	{
		if (_vNpc[i]->getNpcPoint().y > _playerPos.y)
		{
			_vNpc[i]->render(hdc, movePt);
		}
	}
}
