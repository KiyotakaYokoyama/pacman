#include "SceneStage.h"
#include "Application.h"
#include "Drawer.h"

#include "Map.h"
#include "Pacman.h"
#include "Military.h"
#include "Debug.h"

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

PacmanConstPtr SceneStage::getPacman( ) {
	return _player[ 0 ];
}

int SceneStage::getChipSize( ) const {
	return _chip_size;
}

int SceneStage::getCharaSize( ) const {
	return _chip_size - 3;
}
