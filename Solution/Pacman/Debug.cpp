#include "Debug.h"
#include "Game.h"
#include "SceneStage.h"
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
#ifdef _DEBUG
	if ( Keyboard::getTask( )->isPushKey( "F1" ) ) {
		_active = !_active;
	}
#endif // _DEBUG

	if ( _new_stage ) {
		_new_stage = false;
	}

	if ( _active ) {
		reloadStage( );
	}
}

void Debug::reloadStage( ) {
	SceneStagePtr stage = Game::getTask( )->getStage( );
	if ( stage ) {
		MapPtr map = stage->getMap( );
		KeyboardPtr key = Keyboard::getTask( );
		for ( int i = 0; i < 10; i++ ) {
			if ( key->isPushKey( std::to_string( i ) ) ) {
				_new_stage = map->loadStage( i );
				break;
			}
		}
	}
}

void Debug::draw( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
	for ( int i = 0; i <= MAP_HEIGHT_CHIP_NUM; i++ ) {
		drawer->drawLine( 0, i * CHIP_SIZE, CHIP_SIZE * MAP_WIDTH_CHIP_NUM, i * CHIP_SIZE );
	}
	for ( int i = 0; i <= MAP_WIDTH_CHIP_NUM; i++ ) {
		drawer->drawLine( i * CHIP_SIZE, 0, i * CHIP_SIZE, CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	}

	MapPtr map = Game::getTask( )->getStage( )->getMap( );
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
