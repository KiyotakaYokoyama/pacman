#include "Game.h"
#include "Application.h"

GamePtr Game::getTask( ) {
	return std::dynamic_pointer_cast< Game >( Application::getInstance( )->getTask( getTag( ) ) );
}

Game::Game( ) :
_scene( SCENE_STAGE ) {
}

Game::~Game( ) {
}

void Game::initialize( ) {
}

void Game::update( ) {
}

void Game::setNextScene( SCENE scene ) {
	_scene = scene;
}

Game::SCENE Game::getNowScene( ) const {
	return _scene;
}
