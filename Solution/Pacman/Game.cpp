#include "Game.h"
#include "Application.h"
#include "Drawer.h"

#include "Map.h"
#include "Pacman.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) {
}

Game::~Game( ) {
}

void Game::initialize( ) {
	_pacman = PacmanPtr( new Pacman( Vector( 50, 50 ) ) );
}

void Game::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	Map::getTask( )->draw( );
	_pacman->update( );
}
