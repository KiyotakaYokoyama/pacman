#include "ObjectViewer.h"
#include "Object.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"
#include "ImageTarget.h"

const int SPRITE_SIZE = 64;

ObjectViewer::ObjectViewer( ObjectConstPtr object ) :
_object( object ) {
	_image = Drawer::getTask( )->createImage( "object.png" );
	_wall = Drawer::getTask( )->createImage( "stage_chip.png" );
}

ObjectViewer::~ObjectViewer( ) {
}

void ObjectViewer::draw( ) const {
	drawBoxTable( );
	drawObjects( );
}

void ObjectViewer::drawBoxTable( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i <= MAP_HEIGHT_CHIP_NUM; i++ ) {
		drawer->drawLine( DRAW_X, DRAW_Y + i * CHIP_SIZE, DRAW_X + CHIP_SIZE * MAP_WIDTH_CHIP_NUM, DRAW_Y + i * CHIP_SIZE );
	}
	for ( int i = 0; i <= MAP_WIDTH_CHIP_NUM; i++ ) {
		drawer->drawLine( DRAW_X + i * CHIP_SIZE, DRAW_Y, DRAW_X + i * CHIP_SIZE, DRAW_Y + CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	}
}

void ObjectViewer::drawObjects( ) const {
	for ( int i = 0; i < MAP_HEIGHT_CHIP_NUM; i++ ) {
		for ( int j = 0; j < MAP_WIDTH_CHIP_NUM; j++ ) {
			switch ( _object->getChip( j, i ) ) {
			case OBJECT_NONE:
				continue;
			case OBJECT_WALL:
				setWallImageRect( j, i );
				{
					int sx = DRAW_X + j * CHIP_SIZE;
					int sy = DRAW_Y + i * CHIP_SIZE;
					_wall->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
					_wall->draw( );
				}
				continue;
			case OBJECT_FEED:
				_image->setRect( 1 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_ENHANCE_FEED:
				_image->setRect( 0 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
				default:;
				//continue;
			}
			int sx = DRAW_X + j * CHIP_SIZE;
			int sy = DRAW_Y + i * CHIP_SIZE;
			_image->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_image->draw( );
		}
	}
}

void ObjectViewer::setWallImageRect( int ox, int oy ) const {
	char flag = 0b0000;
	//ã
	if ( _object->getChip( ox, oy - 1 ) == OBJECT_WALL ) {
		flag |= 1 << 0;
	}
	//‰E
	if ( _object->getChip( ox + 1, oy ) == OBJECT_WALL ) {
		flag |= 1 << 1;
	}
	//‰º
	if ( _object->getChip( ox, oy + 1 ) == OBJECT_WALL ) {
		flag |= 1 << 2;
	}
	//¶
	if ( _object->getChip( ox - 1, oy ) == OBJECT_WALL ) {
		flag |= 1 << 3;
	}

	int tx = 0;
	int ty = 0;
	if ( flag & 0b0001 ) {
		tx += SPRITE_SIZE;
	}
	if ( flag & 0b0010 ) {
		tx += SPRITE_SIZE * 2;
	}
	if ( flag & 0b0100 ) {
		ty += SPRITE_SIZE;
	}
	if ( flag & 0b1000 ) {
		ty += SPRITE_SIZE * 2;
	}
	_wall->setRect( tx, ty, SPRITE_SIZE, SPRITE_SIZE );
}

ImageTargetPtr ObjectViewer::getStageSprite( ) {
	ImageTargetPtr result = ImageTargetPtr( new ImageTarget );
	int ix = CHIP_SIZE * MAP_WIDTH_CHIP_NUM;
	int iy = CHIP_SIZE * MAP_HEIGHT_CHIP_NUM;
	result->create( ix, iy );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->setImageTarget( result );
	
	for ( int i = 0; i < MAP_HEIGHT_CHIP_NUM; i++ ) {
		for ( int j = 0; j < MAP_WIDTH_CHIP_NUM; j++ ) {
			if ( _object->getChip( j, i ) == OBJECT_WALL ) {
				setWallImageRect( j, i );
				int sx = j * CHIP_SIZE;
				int sy = i * CHIP_SIZE;
				_wall->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
				_wall->draw( );
			}
		}
	}

	drawer->setImageTarget( ImageTargetPtr( ) );
	return result;
}
