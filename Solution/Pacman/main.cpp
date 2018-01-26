#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Sound.h"

#include "Game.h"
#include "Debug.h"
#include "define.h"

#if DEVICE
#include "Device.h"
#endif

void main( ) {
	ApplicationPtr app = Application::getInstance( );

	app->setWindowSize( WIDTH, HEIGHT );

	TaskPtr drawer   = DrawerPtr( new Drawer( "Resource" ) );
	TaskPtr keyboard = KeyboardPtr( new Keyboard );
	TaskPtr sound    = SoundPtr( new Sound( "Resource/sound" ) );

	TaskPtr game   = GamePtr( new Game );
	TaskPtr debug  = DebugPtr( new Debug );

	app->addTask( Drawer::getTag( )     , drawer   );
	app->addTask( Keyboard::getTag( )   , keyboard );
	app->addTask( Sound::getTag( )      , sound    );
	app->addTask( Game::getTag( )       , game     );
	app->addTask( Debug::getTag( )      , debug    );

#if DEVICE
	TaskPtr device   = DevicePtr( new Device );
	app->addTask( Device::getTag( )     , device   );
#endif
}
