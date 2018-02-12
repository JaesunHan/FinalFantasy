#pragma once
#include "gameNode.h"
#include "worldMap.h"
#include "worldMapPlayer.h"

//======월드맵 씬	 =======//
//		제작자 : 한재환		//
//		2월 12일				//
//==========================//



class worldMapScene : public gameNode
{
public:

	worldMap* _worldMap;
	worldMapPlayer* _worldMapPlayer;

	worldMapScene();
	~worldMapScene();


	HRESULT init();
	void release();
	void update();
	void render();
};

