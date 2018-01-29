#include "SceneResult.h"
#include "Application.h"
#include "Drawer.h"
#include "Image.h"
#include "Keyboard.h"
#include "Game.h"
#include "define.h"
#include "Sound.h"

#if DEVICE
#include "Device.h"
#endif

const int ANIM_WAIT_TIME = 3;
const int CRACKER_NUM = 45;
const int MAX_COUNT = ANIM_WAIT_TIME * CRACKER_NUM;
const int MAX_LOOP_NUM = 5;

SceneResult::SceneResult( RESULT result ) :
_count( 0 ),
_loop_num( 0 ),
_winner( result ) {
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
	_result = drawer->createImage( "string.png" );
	switch ( result ) {
	case RESULT_DRAW:
		_result->setRect( 0, 128, 150, 64 );
		_result->setPos( WIDTH / 2 - 300, HEIGHT / 2 - 256, WIDTH / 2 + 300, HEIGHT / 2 );
		break;
	case RESULT_PLAYER1:
	{
		_win_player = drawer->createImage( "pacman.png" );
		_win_player->setRect( SPRITE_SIZE * 2, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE );
		int sx = ( int )( SCREEN_WIDTH * 0.25 );
		int sy = ( int )( SCREEN_HEIGHT * 0.1 );
		_win_player->setPos( sx, sy, sx + ( int )( SPRITE_SIZE * RATIO ), sy + ( int )( SPRITE_SIZE * RATIO ) );
		_result->setRect( 0, 64, 320, 64 );
		_result->setPos( WIDTH / 2 - 128, 64 );
	}
		break;
	case RESULT_PLAYER2:
	{
		_win_player = drawer->createImage( "pacwoman.png" );
		_win_player->setRect( SPRITE_SIZE * 2, SPRITE_SIZE * 1, SPRITE_SIZE, SPRITE_SIZE );
		int sx = ( int )( SCREEN_WIDTH * 0.25 );
		int sy = ( int )( SCREEN_HEIGHT * 0.1 );
		_win_player->setPos( sx, sy, sx + ( int )( SPRITE_SIZE * RATIO ), sy + ( int )( SPRITE_SIZE * RATIO ) );
		_result->setRect( 0, 64, 320, 64 );
		_result->setPos( WIDTH / 2 - 128, 64 );
	}
		break;
	}
	Sound::getTask( )->playBGM( "pac_music_coffeebreak.mp3" );
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
	if ( _winner == RESULT_DRAW ) {
		_cracker[ 0 ]->draw( );
	} else {
		_cracker[ _count / ANIM_WAIT_TIME ]->draw( );
	}
	_result->draw( );
	if ( _win_player ) {
		_win_player->draw( );
	}
}

bool SceneResult::checkKey( ) {
#if DEVICE
	DevicePtr device = Device::getTask( );
	if ( device->getButton( PLAYER_1 ) ||
		 device->getButton( PLAYER_2 ) ) {
		return true;
	}
#else
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "SPACE" ) ) {
		return true;
	}
#endif
	return false;
}
