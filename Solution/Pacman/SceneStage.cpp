#include "SceneStage.h"
#include "Application.h"
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
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ] = PacmanPtr( new Pacman( i, _map->getPlayerPos( i ) ) );
	}
	_military = MilitaryPtr( new Military );
	_map->generateEnemy( _military );
}

void SceneStage::update( ) {
	if ( Game::getTask( )->getNowScene( ) != Game::SCENE_STAGE ) {
		return;
	}

	if ( !Game::getTask( )->isStaging( ) ) {
		updateBattle( );
	}

}

void SceneStage::updateBattle( ) {
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ]->update( );
	}
	_military->update( );
	_map->update( );	
	
	DebugPtr debug = Debug::getTask( );
	if ( debug->isActive( ) ) {
		if ( debug->isNewStage( ) ) {
			for ( int i = 0; i < MAX_PLAYER; i++ ) {
				_player[ i ]->entryStage( _map->getPlayerPos( i ) );
			}
		}
	}
}

void SceneStage::draw( ) const {
	_map->draw( );
	_military->draw( );
	if ( Game::getTask( )->isStaging( ) ) {
		drawStageing( );
	} else {
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			_player[ i ]->draw( );
		}
	}
}

void SceneStage::drawStageing( ) const {
	GamePtr game = Game::getTask( );
	const int STAGE_TIME = game->getStageingTime( );
	const int MAX_STAGE_TIME = game->getMaxStageingTime( );
	if ( STAGE_TIME < MAX_STAGE_TIME / 2 ) {
		_player[ PLAYER_1 ]->drawStageing( STAGE_TIME, MAX_STAGE_TIME / 2 );
	} else {
		_player[ PLAYER_1 ]->draw( );
		_player[ PLAYER_2 ]->drawStageing( STAGE_TIME - MAX_STAGE_TIME / 2, MAX_STAGE_TIME / 2 );
	}
}

MapPtr SceneStage::getMap( ) {
	return _map;
}

PacmanConstPtr SceneStage::getPacman( PLAYER idx ) {
	assert( idx == PLAYER_1 || idx == PLAYER_2 );
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
