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
const int MAX_LOOP_NUM = 5;

SceneResult::SceneResult( RESULT result ) :
_count( 0 ),
_loop_num( 0 ) {
	ApplicationPtr app = Application::getInstance( );
	const int SCREEN_WIDTH = app->getWindowWidth( );
	const int SCREEN_HEIGHT = app->getWindowHeight( );

	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i < CRACKER_NUM; i++ ) {
		std::string path = "cracker/cracker-" + std::to_string( i + 1 ) + ".png";
		_cracker[ i ] = drawer->createImage( path.c_str( ) );
		_cracker[ i ]->setRect( 0, 0, 1280, 720 );
		_cracker[ i ]->setPos( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
	}
	
	const double RATIO = ( SCREEN_WIDTH * 0.5 ) / SPRITE_SIZE;
	//_result = drawer->createImage( "result.png" );
	switch ( result ) {
	case RESULT_DRAW:
		//_result->setRect( );
		//_result->setPos( 0, 0 );
		break;
	case RESULT_PLAYER1:
	{
		_win_player = drawer->createImage( "pacman.png" );
		_win_player->setRect( SPRITE_SIZE * 2, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE );
		int sx = ( int )( SCREEN_WIDTH * 0.25 );
		int sy = ( int )( SCREEN_HEIGHT * 0.1 );
		_win_player->setPos( sx, sy, sx + ( int )( SPRITE_SIZE * RATIO ), sy + ( int )( SPRITE_SIZE * RATIO ) );
		//_result->setRect( );
		//_result->setPos( 0, 0 );
	}
		break;
	case RESULT_PLAYER2:
	{
		_win_player = drawer->createImage( "pacwoman.png" );
		_win_player->setRect( SPRITE_SIZE * 2, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE );
		int sx = ( int )( SCREEN_WIDTH * 0.25 );
		int sy = ( int )( SCREEN_HEIGHT * 0.1 );
		_win_player->setPos( sx, sy, sx + ( int )( SPRITE_SIZE * RATIO ), sy + ( int )( SPRITE_SIZE * RATIO ) );
		//_result->setRect( );
		//_result->setPos( 0, 0 );
	}
		break;
	}
}

SceneResult::~SceneResult( ) {
}

Scene::SCENE SceneResult::update( ) {
	_count++;
	if ( _count == MAX_COUNT ) {
		_loop_num++;
		_count = ANIM_WAIT_TIME * 6;
	}

	if ( checkKey( ) || _loop_num > MAX_LOOP_NUM ) {
 		return SCENE_TITLE;
	}

	return SCENE_CONTINUE;
}

void SceneResult::draw( ) const {
	_cracker[ _count / ANIM_WAIT_TIME ]->draw( );
	//_result->draw( );
	if ( _win_player ) {
		_win_player->draw( );
	}
}

bool SceneResult::checkKey( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "SPACE" ) ) {
		return true;
	}
	return false;
}
