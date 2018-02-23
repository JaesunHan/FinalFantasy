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

	//�޴� �̹���
	_loading->loadImage("�ɷ¸޴�", ".//prevProjectResource//SceneImage//menu_abilities.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ���ʹɷ¸޴�", ".//prevProjectResource//SceneImage//menu_abilitiCharacter.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//_loading->loadImage("���޴�", ".//prevProjectResource//SceneImage//equipMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����۸޴�", ".//prevProjectResource//SceneImage//menu_item.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//_loading->loadImage("���θ޴�", ".//prevProjectResource//SceneImage//mainMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���¸޴�", ".//prevProjectResource//SceneImage//menu_status.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ĳ���ͻ��¸޴�", ".//prevProjectResource//SceneImage//menu_statusCharacter.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("Ÿ��Ʋ�޴�", ".//prevProjectResource//SceneImage//tilteMenu.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����Ӹ޴�", ".//prevProjectResource//SceneImage//menu_newGame.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�ɼǸ޴�", ".//prevProjectResource//SceneImage//menu_option.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�ε���Ӹ޴�", ".//prevProjectResource//SceneImage//menu_continueGame.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���̺�޴�", ".//prevProjectResource//SceneImage//menu_save.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�ε�޴�", ".//prevProjectResource//SceneImage//menu_load.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("���Ǳ׸޴�", ".//image//configMenu//config_backgroundImg.bmp", 0, 0, WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//��ư �̹���
	_loading->loadFrameImage("����Ŀ��", ".//prevProjectResource//SceneImage//selectCursor.bmp",54, 27, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư����", ".//prevProjectResource//SceneImage//button_yes.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư��", ".//prevProjectResource//SceneImage//button_no.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư", ".//prevProjectResource//SceneImage//button_empty.bmp", 317, 32, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư��Ÿ��", ".//prevProjectResource//SceneImage//button_fantasy.bmp", 338, 41, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư����", ".//prevProjectResource//SceneImage//button_saveFile.bmp", 344, 49, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư����", ".//prevProjectResource//SceneImage//button_name.bmp", 352, 63, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ư��������", ".//prevProjectResource//SceneImage//button_items_heal.bmp", 384, 48, 2, 1, true, RGB(255, 0, 255));

	//������ �̹���
	_loading->loadFrameImage("��������", ".//prevProjectResource//SceneImage//icon_menu_ability_heal.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ܰ���", ".//prevProjectResource//SceneImage//icon_menu_ability_attack.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ܹ��", ".//prevProjectResource//SceneImage//icon_menu_ability_defence.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ܾ����ۻ��", ".//prevProjectResource//SceneImage//icon_items_use.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ܾ���������", ".//prevProjectResource//SceneImage//icon_items_sort.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ܾ����۷���", ".//prevProjectResource//SceneImage//icon_items_rare.bmp", 400, 74, 2, 1, true, RGB(255, 0, 255));


	//�÷��̾� �̹���
	_loading->loadFrameImage("TINA", ".//prevProjectResource//SceneImage//player_tina.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CELES", ".//prevProjectResource//SceneImage//player_celes.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("LOCKE", ".//prevProjectResource//SceneImage//player_locke.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SHADOW", ".//prevProjectResource//SceneImage//player_shadow.bmp", 224, 111, 2, 1, true, RGB(255, 0, 255));
	//�÷��̾� �̹���: ������ ������      
	_loading->loadFrameImage("miniTINA", ".//prevProjectResource//SceneImage//player_tina.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("miniCELES", ".//prevProjectResource//SceneImage//player_celes.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("miniLOCKE", ".//prevProjectResource//SceneImage//player_locke.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("miniSHADOW", ".//prevProjectResource//SceneImage//player_shadow.bmp", 61, 30, 2, 1, true, RGB(255, 0, 255));

	//����
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
		SCENEMANAGER->changeScene("Ÿ��Ʋ");
	}
}

void loadingScene::render()	
{
	_loading->render();
}
