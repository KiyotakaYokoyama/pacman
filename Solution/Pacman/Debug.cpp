#include "Debug.h"
#include "Game.h"
#include "Map.h"
#include "define.h"
#include "Pacman.h"
#include "Application.h"
#include "Keyboard.h"
#include "Drawer.h"
#include "Image.h"

DebugPtr Debug::getTask( ) {
	return std::dynamic_pointer_cast< Debug >( Application::getInstance( )->getTask( getTag( ) ) );
}

Debug::Debug( ) :
_active( false ) {
}

Debug::~Debug( ) {
}

void Debug::initialize( ) {
	_block_chip = Drawer::getTask( )->createImage( "chip.png" );
	_block_chip->setRect( 0, 0, 64, 64 );
}

void Debug::update( ) {
	if ( Keyboard::getTask( )->isPushKey( "SPACE" ) ) {
		_active = !_active;
	}
	if ( _new_stage ) {
		_new_stage = false;
	}

	if ( _active ) {
		MapPtr map = Game::getTask( )->getMap( );
		KeyboardPtr key = Keyboard::getTask( );
		bool succese = false;
		if ( key->isPushKey( "0" ) ) {
			_new_stage = map->loadStage( 0 );
		}
		if ( key->isPushKey( "1" ) ) {
			_new_stage = map->loadStage( 1 );
		}
		if ( key->isPushKey( "2" ) ) {
			_new_stage = map->loadStage( 2 );
		}
		if ( key->isPushKey( "3" ) ) {
			_new_stage = map->loadStage( 3 );
		}
		if ( key->isPushKey( "4" ) ) {
			_new_stage = map->loadStage( 4 );
		}
		if ( key->isPushKey( "5" ) ) {
			_new_stage = map->loadStage( 5 );
		}
		if ( key->isPushKey( "6" ) ) {
			_new_stage = map->loadStage( 6 );
		}
		if ( key->isPushKey( "7" ) ) {
			_new_stage = map->loadStage( 7 );
		}
		if ( key->isPushKey( "8" ) ) {
			_new_stage = map->loadStage( 8 );
		}
		if ( key->isPushKey( "9" ) ) {
			_new_stage = map->loadStage( 9 );
		}
	}
}

void Debug::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i <= MAP_HEIGHT_CHIP_NUM; i++ ) {
		drawer->drawLine( 0, i * CHIP_SIZE, CHIP_SIZE * MAP_WIDTH_CHIP_NUM, i * CHIP_SIZE );
	}
	for ( int i = 0; i <= MAP_WIDTH_CHIP_NUM; i++ ) {
		drawer->drawLine( i * CHIP_SIZE, 0, i * CHIP_SIZE, CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	}

	MapPtr map = Game::getTask( )->getMap( );
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		int ox = i % MAP_WIDTH_CHIP_NUM;
		int oy = i / MAP_WIDTH_CHIP_NUM;
		if ( map->getObject( ox, oy ) == OBJECT_WALL ) {
			int sx = ox * CHIP_SIZE;
			int sy = oy * CHIP_SIZE;

			_block_chip->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_block_chip->draw( );
		}
	}
}

bool Debug::isActive( ) const {
	return _active;
}

bool Debug::isNewStage( ) const {
	return _new_stage;
}
