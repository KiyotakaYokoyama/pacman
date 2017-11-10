#include "Game.h"
#include "Application.h"
#include "Drawer.h"

#include "Map.h"
#include "Pacman.h"
#include "Military.h"
#include "EnemyBashful.h"
#include "EnemyPokey.h"
#include "EnemyShadow.h"
#include "EnemySpeedy.h"
#include "Debug.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) {
}

Game::~Game( ) {
}

void Game::initialize( ) {
	_map = MapPtr( new Map );
	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_player[ i ] = PacmanPtr( new Pacman( i, _map->getPlayerPos( i ) ) );
	}
	_military = MilitaryPtr( new Military );
	_military->addEnemy( EnemyPtr( new EnemyShadow( Vector( 480, 480 - 64 ) ) ) );
	_military->addEnemy( EnemyPtr( new EnemyBashful( Vector( 960, 480 - 64 ) ) ) );
	_military->addEnemy( EnemyPtr( new EnemySpeedy( Vector( 480, 120 - 64 ) ) ) );
	_military->addEnemy( EnemyPtr( new EnemyPokey( Vector( 960, 120 - 64 ) ) ) );
}

void Game::update( ) {
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

MapPtr Game::getMap( ) {
	return _map;
}

PacmanConstPtr Game::getPacman( ) {
	return _player[ 0 ];
}
