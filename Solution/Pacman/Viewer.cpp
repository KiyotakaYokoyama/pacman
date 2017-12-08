#include "Viewer.h"
#include "Application.h"
#include "Drawer.h"
#include "Game.h"
#include "Debug.h"
#include "SceneTitle.h"
#include "SceneStage.h"
#include "SceneResult.h"

ViewerPtr Viewer::getTask( ) {
	return std::dynamic_pointer_cast< Viewer >( Application::getInstance( )->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->waitForSync( );
	drawer->flip( );

	GamePtr game = Game::getTask( );
	switch ( game->getNowScene( ) ) {
	case Game::SCENE_TITLE:
		SceneTitle::getTask( )->draw( );
		break;
	case Game::SCENE_STAGE:
		SceneStage::getTask( )->draw( );
		game->draw( );
		if ( Debug::getTask( )->isActive( ) ) Debug::getTask( )->draw( );
		break;
	case Game::SCENE_RESULT:
		SceneResult::getTask( )->draw( );
		break;
	}
}
