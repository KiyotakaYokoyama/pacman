#include "SceneTitle.h"
#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Sound.h"
#include "Image.h"
#include "Game.h"
#include "define.h"

const int NEXT_SCENE_TIME = 10 * 30;

SceneTitle::SceneTitle( ) {
	Sound::getTask( )->playBGM( "pac_music_coffeebreak.wav" );
	_title = Drawer::getTask( )->createImage( "title.png" );
	int w;
	int h;
	_title->getImageSize( w, h );
	_title->setRect( 0, 0, w, h );
	_title->setPos( 0, 0, WIDTH, HEIGHT );
}

SceneTitle::~SceneTitle( ) {
}

Scene::SCENE SceneTitle::update( ) {
	if ( checkKey( ) ) {
		return SCENE_STAGE;
	}
	return SCENE_CONTINUE;
}

void SceneTitle::draw( ) const {
	_title->draw( );
}

bool SceneTitle::checkKey( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "SPACE" ) ) {
		return true;
	}
	return false;
}
