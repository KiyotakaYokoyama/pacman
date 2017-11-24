#include "SceneStage.h"
#include "Application.h"
#include "Drawer.h"
#include <assert.h>

#include "Map.h"
#include "Pacman.h"
#include "Military.h"
#include "Debug.h"
#include "Game.h"

SceneStagePtr SceneStage::getTask( ) {
	return std::dynamic_pointer_cast< SceneStage >( Application::getInstance( )->getTask( getTag( ) ) );
}

SceneStage::SceneStage( ) {
	ApplicationPtr app = Application::getInstance( );
	_chip_size = app->getWindowWidth( ) / MAP_WIDTH_CHIP_NUM;
}

SceneStage::~SceneStage( ) {
}

void SceneStage::initialize( ) {
	_map = MapPtr( new Map );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_player[ i ] = PacmanPtr( new Pacman( i, _map->getPlayerPos( i ) ) );
	}
	_military = MilitaryPtr( new Military );
	_map->generateEnemy( _military );
}

void SceneStage::update( ) {
	if ( Game::getTask( )->getNowScene( ) != Game::SCENE_STAGE ) {
		return;
	}

	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_player[ i ]->update( );
	}
	_military->update( );

	
	_map->draw( );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_player[ i ]->draw( );
	}
	_military->draw( );
	
	DebugPtr debug = Debug::getTask( );
	if ( debug->isActive( ) ) {
		if ( debug->isNewStage( ) ) {
			for ( int i = 0; i < PLAYER_NUM; i++ ) {
				_player[ i ]->entryStage( _map->getPlayerPos( i ) );
			}
		}
		debug->draw( );
	}
}

MapPtr SceneStage::getMap( ) {
	return _map;
}

PacmanConstPtr SceneStage::getPacman( int idx ) {
	assert( idx == 0 || idx == 1 );
	return _player[ idx ];
}

PacmanConstPtr SceneStage::getPacman( Vector pos ) {
	Vector dis1 = _player[ 0 ]->getPos( ) - pos;
	Vector dis2 = _player[ 1 ]->getPos( ) - pos;
	int idx = 0;
	if ( dis1.getLength2( ) > dis2.getLength2( ) ) {
		idx = 1;
	}
	return _player[ idx ];
}

int SceneStage::getChipSize( ) const {
	return _chip_size;
}

int SceneStage::getCharaSize( ) const {
	return _chip_size - 3;
}
