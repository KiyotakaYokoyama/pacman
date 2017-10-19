#include "Application.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "MapEditor.h"

void main( ) {
	ApplicationPtr app = Application::getInstance( );
	app->setWindowSize( 1280, 720 );
	
	TaskPtr drawer     = TaskPtr     ( new Drawer( "Resource" ) );
	TaskPtr keyboard   = KeyboardPtr ( new Keyboard );
	TaskPtr mouse      = MousePtr    ( new Mouse );
	TaskPtr map_editor = MapEditorPtr( new MapEditor );

	app->addTask( Drawer::getTag( ),    drawer );
	app->addTask( Keyboard::getTag( ),  keyboard );
	app->addTask( Mouse::getTag( ),     mouse );
	app->addTask( MapEditor::getTag( ), map_editor );
}
