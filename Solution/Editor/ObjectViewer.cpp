#include "ObjectViewer.h"
#include "Object.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"
#include "ImageTarget.h"

ObjectViewer::ObjectViewer( ObjectConstPtr object ) :
_object( object ) {
	_image = Drawer::getTask( )->createImage( "object.png" );
	_wall = Drawer::getTask( )->createImage( "stage_chip.png" );
	_guide = Drawer::getTask( )->createImage( "guide_stage.png" );
	int tw = 0;
	int th = 0;
	_guide->getImageSize( tw, th );
	_guide->setRect( 0, 0, tw, th );
	_guide->setPos( DRAW_X, DRAW_Y, DRAW_X + EDITOR_CHIP_SIZE * MAP_WIDTH_CHIP_NUM, DRAW_Y + EDITOR_CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
}

ObjectViewer::~ObjectViewer( ) {
}

void ObjectViewer::draw( ) const {
	_guide->draw( );
	drawObjects( );
}

void ObjectViewer::drawObjects( ) const {
	for ( int i = 0; i < MAP_HEIGHT_CHIP_NUM; i++ ) {
		for ( int j = 0; j < MAP_WIDTH_CHIP_NUM; j++ ) {
			switch ( _object->getChip( j, i ) ) {
			case OBJECT_NONE:
				continue;
			case OBJECT_PLAYER1:
				_image->setRect( 0 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_PLAYER2:
				_image->setRect( 1 * SPRITE_SIZE, 1 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_WALL:
				setWallImageRect( j, i );
				{
					int sx = DRAW_X + j * EDITOR_CHIP_SIZE;
					int sy = DRAW_Y + i * EDITOR_CHIP_SIZE;
					_wall->setPos( sx, sy, sx + EDITOR_CHIP_SIZE, sy + EDITOR_CHIP_SIZE );
					_wall->draw( );
				}
				continue;
			case OBJECT_FEED:
				_image->setRect( 1 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_ENHANCE_FEED:
				_image->setRect( 0 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_SHADOW:
				_image->setRect( 0 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_SPEEDY:
				_image->setRect( 2 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_BASHFUL:
				_image->setRect( 3 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_POKEY:
				_image->setRect( 1 * SPRITE_SIZE, 2 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_STAGE_WARP:
				_image->setRect( 2 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			case OBJECT_REVIVAL_FEED:
				_image->setRect( 3 * SPRITE_SIZE, 0 * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE );
				break;
			default:
				continue;
			}
			int sx = DRAW_X + j * EDITOR_CHIP_SIZE;
			int sy = DRAW_Y + i * EDITOR_CHIP_SIZE;
			_image->setPos( sx, sy, sx + EDITOR_CHIP_SIZE, sy + EDITOR_CHIP_SIZE );
			_image->draw( );
		}
	}
}

void ObjectViewer::setWallImageRect( int ox, int oy ) const {
	char flag = 0b0000;
	//上
	if ( _object->getChip( ox, oy - 1 ) == OBJECT_WALL ) {
		flag |= 1 << 0;
	}
	//右
	if ( _object->getChip( ox + 1, oy ) == OBJECT_WALL ) {
		flag |= 1 << 1;
	}
	//下
	if ( _object->getChip( ox, oy + 1 ) == OBJECT_WALL ) {
		flag |= 1 << 2;
	}
	//左
	if ( _object->getChip( ox - 1, oy ) == OBJECT_WALL ) {
		flag |= 1 << 3;
	}
	//マップ端
	if ( ox % MAP_WIDTH_CHIP_NUM == 0 ) {
		if ( flag & 0b1000 ) {
			flag &= 0b0111;
		}
	}
	if ( ox % MAP_WIDTH_CHIP_NUM == MAP_WIDTH_CHIP_NUM - 1 ) {
		if ( flag & 0b0010 ) {
			flag &= 0b1101;
		}
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
	int ix = SPRITE_SIZE * MAP_WIDTH_CHIP_NUM;
	int iy = SPRITE_SIZE * MAP_HEIGHT_CHIP_NUM;
	result->create( ix, iy );

	DrawerPtr drawer = Drawer::getTask( );
	drawer->setImageTarget( result );
	
	for ( int i = 0; i < MAP_HEIGHT_CHIP_NUM; i++ ) {
		for ( int j = 0; j < MAP_WIDTH_CHIP_NUM; j++ ) {
			if ( _object->getChip( j, i ) == OBJECT_WALL ) {
				setWallImageRect( j, i );
				int sx = j * SPRITE_SIZE;
				int sy = i * SPRITE_SIZE;
				_wall->setPos( sx, sy, sx + SPRITE_SIZE, sy + SPRITE_SIZE );
				_wall->draw( );
			}
		}
	}

	drawer->setImageTarget( ImageTargetPtr( ) );
	return result;
}
