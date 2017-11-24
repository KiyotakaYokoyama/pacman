#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"

#include "Game.h"
#include "SceneStage.h"
#include "Debug.h"
#include "define.h"

void main( ) {
	ApplicationPtr app = Application::getInstance( );

	app->setWindowSize( WIDTH, HEIGHT );

	TaskPtr drawer = DrawerPtr( new Drawer( "Resource" ) );
	TaskPtr keyboard = KeyboardPtr( new Keyboard );

	TaskPtr game  = GamePtr( new Game );
	TaskPtr stage = SceneStagePtr ( new SceneStage  );
	TaskPtr debug = DebugPtr( new Debug );

	app->addTask( Drawer::getTag( )    , drawer   );
	app->addTask( Keyboard::getTag( )  , keyboard );
	app->addTask( Game::getTag( )      , game     );
	app->addTask( SceneStage::getTag( ), stage    );
	app->addTask( Debug::getTag( )     , debug    );
}
