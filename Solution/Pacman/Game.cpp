#include "Game.h"
#include "Application.h"
#include "Drawer.h"

#include "Pacman.h"
#include "Map.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) {
}

Game::~Game( ) {
}

void Game::initialize( ) {
	_pacman = PacmanPtr( new Pacman( Vector( 50, 50 ) ) );
	_map = MapPtr( new Map );
}

void Game::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	_map->update( );
	_pacman->update( );
}
