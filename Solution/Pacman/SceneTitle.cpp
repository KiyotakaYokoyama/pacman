#include "SceneTitle.h"
#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Image.h"
#include "Game.h"
#include "define.h"

SceneTitlePtr SceneTitle::getTask( ) {
	return std::dynamic_pointer_cast< SceneTitle >( Application::getInstance( )->getTask( getTag( ) ) );
}

SceneTitle::SceneTitle( ) {
}

SceneTitle::~SceneTitle( ) {
}

void SceneTitle::initialize( ) {
	_title = Drawer::getTask( )->createImage( "title.png" );
	int w;
	int h;
	_title->getImageSize( w, h );
	_title->setRect( 0, 0, w, h );
	_title->setPos( 0, 0, WIDTH, HEIGHT );
}

void SceneTitle::update( ) {
	if ( Game::getTask( )->getNowScene( ) != Game::SCENE_TITLE ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	checkKey( );

	_title->draw( );
}

void SceneTitle::checkKey( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "SPACE" ) ) {
		Game::getTask( )->setNextScene( Game::SCENE_STAGE );
	}
}
