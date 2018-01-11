#include "Game.h"
#include "Application.h"
#include "Drawer.h"
#include "Image.h"
#include "Scene.h"
#include "SceneTitle.h"
#include "SceneStage.h"
#include "SceneResult.h"
#include "Debug.h"


GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) :
_next( Scene::SCENE_RESULT ) {
	ApplicationPtr app = Application::getInstance( );
	_chip_size = app->getWindowWidth( ) / MAP_WIDTH_CHIP_NUM;
}

Game::~Game( ) {
}

void Game::initialize( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_number = drawer->createImage( "num.png" );
	_player_name = drawer->createImage( "playerName.png" );

	chengeScene( );
}

void Game::chengeScene( ) {
	if ( _next == Scene::SCENE_CONTINUE ) {
		return;
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
			_scene = ScenePtr( new SceneResult );
			break;
		default:
			break;
	}
}

void Game::update( ) {
	_next = _scene->update( );
	
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	_scene->draw( );
	if ( Debug::getTask( )->isActive( ) ) Debug::getTask( )->draw( );

	chengeScene( );
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
