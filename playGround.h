#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "BattleScene.h"
#include "playerManager.h"
#include "loadingScene.h"
#include "titleScene.h"
#include "saveLoadMenu.h"

class playGround : public gameNode
{
private:
	playerManager * _pm;
	BattleScene * _bts;
	bool _isBattle;
public:
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�


	playGround();
	~playGround();
};

