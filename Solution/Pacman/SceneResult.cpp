#include "SceneResult.h"
#include "Application.h"
#include "Drawer.h"
#include "Image.h"
#include "Keyboard.h"
#include "Game.h"
#include "define.h"

const int ANIM_WAIT_TIME = 3;
const int CRACKER_NUM = 45;
const int MAX_COUNT = ANIM_WAIT_TIME * CRACKER_NUM;

SceneResult::SceneResult( ) :
_count( 0 ) {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < CRACKER_NUM; i++ ) {
		std::string path = "cracker/cracker-" + std::to_string( i + 1 ) + ".png";
		_cracker[ i ] = drawer->createImage( path.c_str( ) );
		_cracker[ i ]->setRect( 0, 0, 1280, 720 );
		_cracker[ i ]->setPos( 0, 0, WIDTH, HEIGHT );
	}
}

SceneResult::~SceneResult( ) {
}

Scene::SCENE SceneResult::update( ) {
	_count++;
	if ( _count == MAX_COUNT ) {
		_count = ANIM_WAIT_TIME * 6;
	}

	if ( checkKey( ) ) {
 		return SCENE_TITLE;
	}

	return SCENE_CONTINUE;
}

void SceneResult::draw( ) const {
	_cracker[ _count / ANIM_WAIT_TIME ]->draw( );
}

bool SceneResult::checkKey( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "SPACE" ) ) {
		return true;
	}
	return false;
}
