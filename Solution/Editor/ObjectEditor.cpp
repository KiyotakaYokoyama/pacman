#include "ObjectEditor.h"
#include "Object.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "define.h"

const Vector IGNORE_MOUSE_POS = Vector( -1, -1 );

ObjectEditor::ObjectEditor( ObjectPtr object ) :
_object( object ),
_mode( MODE_NONE ),
_cursor( IGNORE_MOUSE_POS ) {
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
}

void ObjectEditor::updateCursor( ) {
	_cursor = Mouse::getTask( )->getPos( ) * ( 1.0 / CHIP_SIZE );
	_cursor.x -= DRAW_X / CHIP_SIZE + 1;
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
	}
	if ( Mouse::getTask( )->isHoldLeftButton( ) ) {
		_object->setChip( ( int )_cursor.x, ( int )_cursor.y, chip );
	}
}

ObjectEditor::MODE ObjectEditor::getMode( ) const {
	return _mode;
}

Vector ObjectEditor::getCursor( ) const {
	return _cursor;
}
