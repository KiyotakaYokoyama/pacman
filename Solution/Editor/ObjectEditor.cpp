#include "ObjectEditor.h"
#include "Object.h"
#include "define.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Drawer.h"
#include "Image.h"

const Vector IGNORE_MOUSE_POS = Vector( -1, -1 );

ObjectEditor::ObjectEditor( ObjectPtr object ) :
_object( object ),
_mode( MODE_NONE ),
_cursor( IGNORE_MOUSE_POS ) {
	_cursor_sprite = Drawer::getTask( )->createImage( "cursor.png" );
	_cursor_sprite->setRect( 0, 0, 64, 64 );
}

ObjectEditor::~ObjectEditor( ) {
}

void ObjectEditor::update( ) {
	updateMode( );
	updateCursor( );
	edit( );
}

void ObjectEditor::updateMode( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "1" ) ) {
		_mode = MODE_NONE;
	}	
	if ( key->isPushKey( "2" ) ) {
		_mode = MODE_WALL;
	}
	if ( key->isPushKey( "3" ) ) {
		_mode = MODE_FEED;
	}
	if ( key->isPushKey( "4" ) ) {
		_mode = MODE_ENHANCE_FEET;
	}
	if ( key->isPushKey( "5" ) ) {
		_mode = MODE_STAGE_WARP;
	}
	if ( key->isPushKey( "Q" ) ) {
		_mode = MODE_PLAYER1;
	}
	if ( key->isPushKey( "W" ) ) {
		_mode = MODE_PLAYER2;
	}
	if ( key->isPushKey( "E" ) ) {
		_mode = MODE_SAHDOW;
	}
	if ( key->isPushKey( "R" ) ) {
		_mode = MODE_SPEEDY;
	}
	if ( key->isPushKey( "T" ) ) {
		_mode = MODE_BASHFUL;
	}
	if ( key->isPushKey( "Y" ) ) {
		_mode = MODE_POKEY;
	}
}

void ObjectEditor::updateCursor( ) {
	_cursor = Mouse::getTask( )->getPos( ) * ( 1.0 / CHIP_SIZE );
	_cursor.x -= DRAW_X / CHIP_SIZE + 0.5;
	_cursor.y -= DRAW_Y / CHIP_SIZE;

	if ( _cursor.x < 0 || _cursor.x >= MAP_WIDTH_CHIP_NUM ||
		 _cursor.y < 0 || _cursor.y >= MAP_HEIGHT_CHIP_NUM ) {
		_cursor = IGNORE_MOUSE_POS;
	}
}

void ObjectEditor::edit( ) {
	if ( _cursor == IGNORE_MOUSE_POS ) {
		return;
	}

	unsigned char chip = OBJECT_NONE;
	switch ( _mode ) {
	case MODE_NONE:
		chip = OBJECT_NONE;
		break;
	case MODE_WALL:
		chip = OBJECT_WALL;
		break;
	case MODE_FEED:
		chip = OBJECT_FEED;
		break;
	case MODE_ENHANCE_FEET:
		chip = OBJECT_ENHANCE_FEED;
		break;
	case MODE_PLAYER1:
		chip = OBJECT_PLAYER1;
		break;
	case MODE_PLAYER2:
		chip = OBJECT_PLAYER2;
		break;
	case MODE_SAHDOW:
		chip = OBJECT_SHADOW;
		break;
	case MODE_SPEEDY:
		chip = OBJECT_SPEEDY;
		break;
	case MODE_BASHFUL:
		chip = OBJECT_BASHFUL;
		break;
	case MODE_POKEY:
		chip = OBJECT_POKEY;
		break;
	case MODE_STAGE_WARP:
		chip = OBJECT_STAGE_WARP;
		break;
	}
	if ( Mouse::getTask( )->isHoldLeftButton( ) ) {
		if ( chip == OBJECT_PLAYER1 || chip == OBJECT_PLAYER2 ) {
			checkAndEditChip( chip );
		}
		_object->setChip( ( int )_cursor.x, ( int )_cursor.y, chip );
	}
}

ObjectEditor::MODE ObjectEditor::getMode( ) const {
	return _mode;
}

Vector ObjectEditor::getCursor( ) const {
	return _cursor;
}

void ObjectEditor::drawCursor( ) const {
	if ( _cursor != IGNORE_MOUSE_POS ) {
		int sx = DRAW_X + ( int )_cursor.x * CHIP_SIZE;
		int sy = DRAW_Y + ( int )_cursor.y * CHIP_SIZE;
		_cursor_sprite->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
		_cursor_sprite->draw( );
	}
}

void ObjectEditor::checkAndEditChip( unsigned int chip ) {
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM;i++ ) {
		for ( int j = 0; j < MAP_HEIGHT_CHIP_NUM; j++ ) {
			if ( _object->getChip( i, j ) == chip ) {
				_object->setChip( i, j, OBJECT_NONE );
				break;
			}
		}
	}
}

void ObjectEditor::initData( ) const {
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM;i++ ) {
		for ( int j = 0; j < MAP_HEIGHT_CHIP_NUM; j++ ) {
			_object->setChip( i, j, OBJECT_NONE );
		}
	}
}
