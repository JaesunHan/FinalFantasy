#pragma once
#include "gameNode.h"
#include <Vfw.h>
#pragma comment(lib,"vfw32.lib")

//class player;

class oPeningMovie : public gameNode
{
private:

	HDC _hdc;
	HWND hWndAVI = 0;



public:
	oPeningMovie();
	~oPeningMovie();

	HRESULT init();
	void release();
	void update();
	void render();

};

