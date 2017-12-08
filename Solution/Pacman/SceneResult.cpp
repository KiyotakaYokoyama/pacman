#include "SceneResult.h"
#include "Application.h"
#include "Drawer.h"
#include "Image.h"
#include "Game.h"
#include "define.h"

const int ANIM_WAIT_TIME = 3;
const int CRACKER_NUM = 45;
const int MAX_COUNT = ANIM_WAIT_TIME * CRACKER_NUM;

SceneResultPtr SceneResult::getTask( ) {
	return std::dynamic_pointer_cast< SceneResult >( Application::getInstance( )->getTask( getTag( ) ) );
}

SceneResult::SceneResult( ) {
}

SceneResult::~SceneResult( ) {
}

void SceneResult::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < CRACKER_NUM; i++ ) {
		std::string path = "cracker/cracker-" + std::to_string( i + 1 ) + ".png";
		_cracker[ i ] = drawer->createImage( path.c_str( ) );
		_cracker[ i ]->setRect( 0, 0, 1280, 720 );
		_cracker[ i ]->setPos( 0, 0, WIDTH, HEIGHT );
	}
}

void SceneResult::update( ) {
	if ( Game::getTask( )->getNowScene( ) != Game::SCENE_RESULT ) {
		_count = 0;
		return;
	}

	_count++;
	if ( _count == MAX_COUNT ) {
		_count = ANIM_WAIT_TIME * 6;
	}
}

void SceneResult::draw( ) const {
	_cracker[ _count / ANIM_WAIT_TIME ]->draw( );
}

void SceneResult::setNumberImage( ImagePtr image ) {
	_number = image;
}
