#include "stdafx.h"
#include "loading.h"

loadItem::loadItem(){}
loadItem::~loadItem(){}

HRESULT loadItem::initForImage(string keyName, int width, int height)
{
	_kind = LOAD_KIND_IMAGE_0;

	_imageResource.keyName = keyName;
	_imageResource.width = width;
	_imageResource.height = height;
	
	return S_OK;
}

HRESULT loadItem::initForImage(string keyName, const char* fileName, int width, int height, BOOL trans,
	COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_1;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;


	return S_OK;
}
HRESULT loadItem::initForImage(string keyName, const char* fileName, float x, float y, int width, int height,
	BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_IMAGE_2;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}
HRESULT loadItem::initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	_imageResource.keyName = keyName;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.trans = trans;
	_imageResource.transColor = transColor;

	return S_OK;
}

HRESULT loadItem::initForSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_soundResource.keyName = keyName;
	_soundResource.fileName = fileName;
	_soundResource.bgm = bgm;
	_soundResource.loop = loop;

	return S_OK;
}

loading::loading()
{
}


loading::~loading()
{

}

HRESULT loading::init()
{
	_background = IMAGEMANAGER->addImage("로딩백그라운드", ".//prevProjectResource//SceneImage//loading_sqgEnix.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_loadingBar = new progressBar;
	_loadingBar->init("loading_frontBar", "loading_backBar", "SceneImage",  WINSIZEX / 2, WINSIZEY - 50, 700, 25);
	_loadingBar->setGauge(0, 0);

	_currentGauge = 0;

	//로딩할때 띄울 움직이는 프레임 이미지
	_loadChacracter = new image;
	_loadChacracter = IMAGEMANAGER->addFrameImage("loadingFish", ".//prevProjectResource//SceneImage//loading_fish.bmp", _loadingBar->getRcProgress().left, _loadingBar->getRcProgress().top, 201, 24, 3, 1, true, RGB(255, 0, 255));
	
	_loadCharAnim = new animation;
	int animArr[] = { 0, 1, 2 }; 
	KEYANIMANAGER->addArrayFrameAnimation("로딩꽁치", "loadingFish", animArr, 3, 5, true);
	_loadCharAnim = KEYANIMANAGER->findAnimation("로딩꽁치");
	_loadCharAnim->start();

	return S_OK;
}

void loading::release()
{
	SAFE_DELETE(_loadingBar);
}

void loading::update() 
{
	_loadingBar->update();
	KEYANIMANAGER->update();
}

void loading::render() 
{
	_background->render(getMemDC());
	_loadingBar->render();

	_loadChacracter->aniRender(getMemDC(), _loadingBar->getWidth(), _loadingBar->getRcProgress().top + 10, _loadCharAnim);
	//TextOut(getMemDC(), 100, WINSIZEY / 2, _filePathName, strlen(_filePathName));
}


void loading::loadImage(string keyName, int width, int height)
{
	//로딩할 이미지 타입에 맞게 초기화하여, 벡터에 담아준다
	loadItem* item = new loadItem;
	item->initForImage(keyName, width, height);

	_vLoadItem.push_back(item);
}


void loading::loadImage(string keyName, const char* fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForImage(keyName, fileName, x, y, width, height, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	loadItem* item = new loadItem;
	item->initForFrameImage(keyName, fileName, x, y, width, height, frameX, frameY, trans, transColor);

	_vLoadItem.push_back(item);
}

void loading::loadSound(string keyName, const char* fileName, bool bgm, bool loop)
{
	loadItem* item = new loadItem;
	item->initForSound(keyName, fileName, bgm, loop);

	_vLoadItem.push_back(item);
}

BOOL loading::loadingDone()
{
	//현재 로딩게이지가 벡터의 사이즈보다 크다 (로딩이 끝났다)
	if (_currentGauge >= _vLoadItem.size())
	{
		return TRUE;
	}


	loadItem* item = _vLoadItem[_currentGauge];
	
	switch (item->getLoadingKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
			wsprintf(_filePathName, "%s", item->getImageFileName());

		}
		break;
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.trans, img.transColor);
			wsprintf(_filePathName, "%s", item->getImageFileName());

		}
		break;
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.trans, img.transColor);
			wsprintf(_filePathName, "%s", item->getImageFileName());

		}
		break;
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.trans, img.transColor);
			wsprintf(_filePathName, "%s", item->getImageFileName());

		}
		break;
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.x, img.y, img.frameX, img.frameY, img.trans, img.transColor);
			wsprintf(_filePathName, "%s", item->getImageFileName());

		}
		break;
		case LOAD_KIND_SOUND:
		{
			tagSoundResource snd = item->getSoundResource();
			SOUNDMANAGER->addSound(snd.keyName, snd.fileName, snd.bgm, snd.loop);
			wsprintf(_filePathName, "%s", item->geSoundFileName());

		}
		break;
	}

	_loadingBar->setGauge(_currentGauge, _vLoadItem.size());
	_currentGauge++;

	return FALSE;
}
