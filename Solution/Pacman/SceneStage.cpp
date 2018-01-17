#include "SceneStage.h"
#include "Application.h"
#include <assert.h>

#include "Map.h"
#include "Pacman.h"
#include "Military.h"
#include "Score.h"
#include "Debug.h"
#include "Game.h"

const int FPS = 30;
const int MAX_STAGEING_TIME = 1 * FPS;

SceneStage::SceneStage( ImagePtr number, ImagePtr player_name ) :
_staging_time( 0 ) {
	_score = ScorePtr( new Score( number, player_name ) );
	_map = MapPtr( new Map );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ] = PacmanPtr( new Pacman( i, _map->getPlayerPos( i ) ) );
	}
	_military = MilitaryPtr( new Military );
	_map->generateEnemy( _military );
}

SceneStage::~SceneStage( ) {
}

Scene::SCENE SceneStage::update( ) {
	if ( isStaging( ) ) {
		_staging_time++;
	} else {
		updateBattle( );
		_score->update( );
	}

	return SCENE_CONTINUE;
}

void SceneStage::updateBattle( ) {
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player[ i ]->update( );
	}
	_military->update( );
	_map->update( );	
	
	DebugPtr debug = Debug::getTask( );
	if ( debug->isActive( ) && debug->isNewStage( ) ) {
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			_player[ i ]->entryStage( _map->getPlayerPos( i ) );
		}
		_military->clearEnemy( );
		_map->generateEnemy( _military );
		_score->initialize( );
	}
}

void SceneStage::draw( ) const {
	_map->draw( );
	_military->draw( );
	if ( isStaging( ) ) {
		drawStageing( );
	} else {
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			_player[ i ]->draw( );
		}
	}
	_score->draw( );
}

void SceneStage::drawStageing( ) const {
	GamePtr game = Game::getTask( );
	if ( _staging_time < MAX_STAGEING_TIME / 2 ) {
		_player[ PLAYER_1 ]->drawStageing( _staging_time, MAX_STAGEING_TIME / 2 );
	} else {
		_player[ PLAYER_1 ]->draw( );
		_player[ PLAYER_2 ]->drawStageing( _staging_time - MAX_STAGEING_TIME / 2, MAX_STAGEING_TIME / 2 );
	}
}

MapPtr SceneStage::getMap( ) {
	return _map;
}

PacmanPtr SceneStage::getPacman( PLAYER idx ) const {
	assert( idx == PLAYER_1 || idx == PLAYER_2 );
	return _player[ idx ];
}

PacmanPtr SceneStage::getPacman( Vector pos ) const {
	Vector dis1 = _player[ PLAYER_1 ]->getPos( ) - pos;
	Vector dis2 = _player[ PLAYER_2 ]->getPos( ) - pos;

	int idx = ( int )PLAYER_1;
	if ( dis1.getLength2( ) > dis2.getLength2( ) ) {
		idx = ( int )PLAYER_2;
	}

	if ( _player[ PLAYER_1 ]->isDamaging( ) ) {
		idx = ( int )PLAYER_2;
	}

	if ( _player[ PLAYER_2 ]->isDamaging( ) ) {
		idx = ( int )PLAYER_1;
	}

	if ( _player[ PLAYER_1 ]->isDamaging( ) &&
		 _player[ PLAYER_2 ]->isDamaging( ) ) {
		return PacmanPtr( );
	}

	return _player[ idx ];
}

bool SceneStage::isStaging( ) const {
	return _staging_time < MAX_STAGEING_TIME;
}

void SceneStage::addScore( PLAYER idx, SCORE score ) {
	_score->addScore( idx, score );
}

RESULT SceneStage::getWinner( ) const {
	RESULT result = RESULT_DRAW;
	int player1 = _score->getScore( PLAYER_1 );
	int player2 = _score->getScore( PLAYER_2 );
	if ( player1 > player2 ) {
		result = RESULT_PLAYER1;
	}
	if ( player2 > player1 ) {
		result = RESULT_PLAYER2;
	}
	return result;
}
