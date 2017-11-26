#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"

#include "Game.h"
#include "SceneTitle.h"
#include "SceneStage.h"
#include "SceneResult.h"
#include "Viewer.h"
#include "Debug.h"
#include "define.h"

void main( ) {
	ApplicationPtr app = Application::getInstance( );

	app->setWindowSize( WIDTH, HEIGHT );

	TaskPtr drawer = DrawerPtr( new Drawer( "Resource" ) );
	TaskPtr keyboard = KeyboardPtr( new Keyboard );

	TaskPtr game   = GamePtr( new Game );
	TaskPtr title  = SceneTitlePtr ( new SceneTitle );
	TaskPtr stage  = SceneStagePtr ( new SceneStage );
	TaskPtr result = SceneResultPtr ( new SceneResult );
	TaskPtr viewer = ViewerPtr ( new Viewer );
	TaskPtr debug  = DebugPtr( new Debug );

	app->addTask( Drawer::getTag( )     , drawer   );
	app->addTask( Keyboard::getTag( )   , keyboard );
	app->addTask( Game::getTag( )       , game     );
	app->addTask( SceneTitle::getTag( ) , title    );
	app->addTask( SceneStage::getTag( ) , stage    );
	app->addTask( SceneResult::getTag( ), result    );
	app->addTask( Viewer::getTag( )     , viewer   );
	app->addTask( Debug::getTag( )      , debug    );
}
