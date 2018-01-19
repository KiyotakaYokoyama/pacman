#include "Game.h"
#include "Application.h"
#include "Drawer.h"
#include "Image.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "SceneStage.h"
#include "SceneResult.h"
#include "Debug.h"
#include "Sound.h"

const int MAX_FADE_COUNT = 90;
const int FADE_WAIT_TIME = 2;

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) :
_next( Scene::SCENE_STAGE ),
_fade_count( MAX_FADE_COUNT ) {
	ApplicationPtr app = Application::getInstance( );
	_chip_size = app->getWindowWidth( ) / MAP_WIDTH_CHIP_NUM;
}

Game::~Game( ) {
}

void Game::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_number = drawer->createImage( "number.png" );
	_player_name = drawer->createImage( "playerName.png" );
	_fade = drawer->createImage( "fade.png" );

	chengeScene( );
}

void Game::chengeScene( ) {
	if ( _next == Scene::SCENE_CONTINUE ) {
		return;
	}

	if ( _fade_count < MAX_FADE_COUNT ) {
		_fade_count++;
		return;
	} else {
		_fade_count = 0;
	}

	RESULT winner = RESULT_DRAW;
	if ( getStage( ) ) {
		Sound::getTask( )->stopAllSE( );
		winner = getStage( )->getWinner( );
	}

	_scene.reset( );

	switch ( _next ) {
		case Scene::SCENE_TITLE:
			_scene = ScenePtr( new SceneTitle );
			break;
		case Scene::SCENE_STAGE:
			_scene = ScenePtr( new SceneStage( _number, _player_name ) );
			break;
		case Scene::SCENE_RESULT:
			_scene = ScenePtr( new SceneResult( winner ) );
			break;
		default:
			break;
	}
}

void Game::update( ) {
	if ( _fade_count == 0 ) {
		_next = _scene->update( );
	}

	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	_scene->draw( );
	if ( _fade_count > 0 ) {
		drawFade( );
	}
	if ( Debug::getTask( )->isActive( ) ) Debug::getTask( )->draw( );

	chengeScene( );
}

void Game::drawFade( ) const {
	const double ratio = ( double )HEIGHT / SPRITE_SIZE;
	//•
	_fade->setRect( SPRITE_SIZE * 5, 0, SPRITE_SIZE, SPRITE_SIZE );
	_fade->setPos( ( int )( -( SPRITE_SIZE / 2 ) * ratio ), 0, ( int )( WIDTH * ( ( double )_fade_count / MAX_FADE_COUNT ) - ( SPRITE_SIZE / 2 * ratio ) ), HEIGHT );
	_fade->draw( );
	//pacman
	const int ANIM[ ] = { 0, 1, 2, 3, 4, 3, 2, 1 };
	const int ANIM_NUM = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	int tx = SPRITE_SIZE * ANIM[ ( _fade_count / FADE_WAIT_TIME ) % ANIM_NUM ];
	int ty = 0;
	_fade->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
	int sx = ( int )( -( SPRITE_SIZE / 2 ) * ratio + WIDTH * ( ( double )_fade_count / MAX_FADE_COUNT ) );
	int sy = 0;
	_fade->setPos( sx, sy, ( int )( sx + SPRITE_SIZE * ratio ), ( int )( SPRITE_SIZE * ratio ) );
	_fade->draw( );
}

int Game::getChipSize( ) const {
	return _chip_size;
}

int Game::getCharaSize( ) const {
	return _chip_size - 3;
}

SceneStagePtr Game::getStage( ) const {
	return std::dynamic_pointer_cast< SceneStage >( _scene );
}
