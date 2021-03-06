#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init(RND->getInt(5));

	//메뉴 이미지
	_loading->loadImage("능력메뉴", ".//prevProjectResource//SceneImage//menu_abilities.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터능력메뉴", ".//prevProjectResource//SceneImage//menu_abilitiCharacter.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("장비메뉴", ".//prevProjectResource//SceneImage//menu_equips.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터장비메뉴", ".//prevProjectResource//SceneImage//menu_equipsCharacter.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이템메뉴", ".//prevProjectResource//SceneImage//menu_item.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//_loading->loadImage("메인메뉴", ".//prevProjectResource//SceneImage//mainMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("상태메뉴", ".//prevProjectResource//SceneImage//menu_status.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("캐릭터상태메뉴", ".//prevProjectResource//SceneImage//menu_statusCharacter.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀메뉴", ".//prevProjectResource//SceneImage//tilteMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("뉴게임메뉴", ".//prevProjectResource//SceneImage//menu_newGame.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("옵션메뉴", ".//prevProjectResource//SceneImage//menu_option.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("로드게임메뉴", ".//prevProjectResource//SceneImage//menu_continueGame.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("세이브메뉴", ".//prevProjectResource//SceneImage//menu_save.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("로드메뉴", ".//prevProjectResource//SceneImage//menu_load.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("컨피그메뉴", ".//image//configMenu//config_backgroundImg.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//버튼 이미지
	_loading->loadFrameImage("선택커서", ".//prevProjectResource//SceneImage//selectCursor.bmp",54, 27, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼예스", ".//prevProjectResource//SceneImage//button_yes.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼노", ".//prevProjectResource//SceneImage//button_no.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼", ".//prevProjectResource//SceneImage//button_empty.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼판타지", ".//prevProjectResource//SceneImage//button_fantasy.bmp", 338, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼파일", ".//prevProjectResource//SceneImage//button_saveFile.bmp", 344, 49, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼네임", ".//prevProjectResource//SceneImage//button_name.bmp", 352, 63, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("버튼아이템힐", ".//prevProjectResource//SceneImage//button_items_heal.bmp", 384, 48, 2, 1, true, RGB(255, 0, 255));

	//아이콘 이미지
	_loading->loadFrameImage("아이콘힐", ".//prevProjectResource//SceneImage//icon_menu_ability_heal.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘공격", ".//prevProjectResource//SceneImage//icon_menu_ability_attack.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘방어", ".//prevProjectResource//SceneImage//icon_menu_ability_defence.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘아이템사용", ".//prevProjectResource//SceneImage//icon_items_use.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘아이템정리", ".//prevProjectResource//SceneImage//icon_items_sort.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘아이템레어", ".//prevProjectResource//SceneImage//icon_items_rare.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘장비장착", ".//prevProjectResource//SceneImage//icon_equips_equips.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘장비최적화", ".//prevProjectResource//SceneImage//icon_equips_optimize.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이콘장비리셋", ".//prevProjectResource//SceneImage//icon_equips_remove.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));


	//플레이어 이미지
	_loading->loadFrameImage("TINA", ".//prevProjectResource//SceneImage//player_tina.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CELES", ".//prevProjectResource//SceneImage//player_celes.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("LOCKE", ".//prevProjectResource//SceneImage//player_locke.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SHADOW", ".//prevProjectResource//SceneImage//player_shadow.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	//플레이어 이미지: 사이즈 재조정      
	_loading->loadFrameImage("miniTINA", ".//prevProjectResource//SceneImage//player_tina.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("miniCELES", ".//prevProjectResource//SceneImage//player_celes.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("miniLOCKE", ".//prevProjectResource//SceneImage//player_locke.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("miniSHADOW", ".//prevProjectResource//SceneImage//player_shadow.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));

	//사운드
	SOUNDMANAGER->addSound("battleMenuOpen", ".\\sound\\sfx\\battleMenuOpen.wav", false, false);
	SOUNDMANAGER->addSound("menuSelectLow", ".\\sound\\sfx\\menuSelectLow.wav", false, false);

	
	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()	
{
	_loading->update();

	if (_loading->loadingDone(3))
	{
		SCENEMANAGER->changeScene("타이틀");
	}
}

void loadingScene::render()	
{
	_loading->render();
}
