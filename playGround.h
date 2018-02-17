#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "BattleScene.h"
#include "playerManager.h"
#include "loadingScene.h"
#include "titleScene.h"
#include "saveLoadMenu.h"
#include "optionMenu.h"
#include "worldMapScene.h"
#include "newGame.h"
#include "loadGame.h"
#include "abilitiesMenu.h"
#include "configMenu.h"
#include "equipMenu.h"
#include "itemMenu.h"
#include "statusMenu.h"
#include "itemManager.h"


class playGround : public gameNode
{
private:
	playerManager* _pm;
	itemManager* _item;
	


	bool _isBattle;
public:
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�


	playGround();
	~playGround();
};

