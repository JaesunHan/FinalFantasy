#include "stdafx.h"
#include "oPeningMovie.h"



oPeningMovie::oPeningMovie()
{
}


oPeningMovie::~oPeningMovie()
{
}

HRESULT oPeningMovie::init()
{
	RECT         rt;
	char szAVIFilename[] = "opening.wmv";
	if (hWndAVI)
	{
		MCIWndClose(hWndAVI);
		MCIWndDestroy(hWndAVI);
		hWndAVI = 0;
	}

	hWndAVI = MCIWndCreate(_hWnd, _hInstance,
		MCIWNDF_NOTIFYANSI | MCIWNDF_NOMENU |
		MCIWNDF_NOTIFYALL | MCIWNDF_NOPLAYBAR,
		szAVIFilename);

	if (hWndAVI)
	{
		GetClientRect(_hWnd, &rt);
		SetWindowPos(hWndAVI, NULL, 0, 0, rt.right, rt.bottom, SWP_NOZORDER | SWP_NOMOVE);
		MCIWndPlay(hWndAVI);
	}

	return S_OK;
}
void oPeningMovie::release()
{
	DestroyWindow(hWndAVI);
	KillTimer(_hWnd, 1);
}

void oPeningMovie::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->changeScene("·Îµù");
		this->release();
	}
}
void oPeningMovie::render()
{
}