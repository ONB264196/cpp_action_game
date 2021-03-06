#include"framework.h"
#include"graphic.h"
#include"window.h"
#include"CONTAINER.h"
#include"TITLE.h"
#include"STAGE.h"
#include"FADE.h"
#include"MAP.h"
#include"CHARACTER_MANAGER.h"
#include"GAME.h"

GAME::GAME()
{
	Container = new CONTAINER();
	Title = new TITLE(this);
	Stage = new STAGE(this);
	Fade = new FADE(this);
	Map = new MAP(this);
	CharacterManager = new CHARACTER_MANAGER(this);
}

GAME::~GAME()
{
	delete CharacterManager;
	delete Map;
	delete Fade;
	delete Stage;
	delete Title;
	delete Container;
}

void GAME::run()
{
	window(1050, 590, 1);
	hideCursor();

	Container->load();
	
	Title->create();
	Stage->create();
	Fade->create();
	Map->create();
	CharacterManager->create();

	CurScene = Title;
	CurScene->init();
	initDeltaTime();
	while (notQuit) {
		setDeltaTime();
		CurScene->proc();
	}
}
void GAME::setCurScene(SCENE* scene) {
	CurScene = scene;
	CurScene->init();
}