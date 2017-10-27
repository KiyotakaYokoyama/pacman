#include "Map.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"
#include "Application.h"
#include "Binary.h"
#include <assert.h>

const std::string FILE_PATH = "Resource/MapData/test.objs";

Map::Map( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_stage = drawer->createImage( "MapData/test_stage.png" );
	_feeds = drawer->createImage( "feeds.png" );

	ApplicationPtr app = Application::getInstance( );
	BinaryPtr binary = BinaryPtr( new Binary );
	app->loadBinary( FILE_PATH, binary );

	_objects.resize( MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM );

	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_player_pos[ i ] = Vector( 32 + i * 868, 32 + i * 268 );
	}

	unsigned char object;
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		binary->read( (void*)&object, sizeof( unsigned char ) );
		_objects[ i ] = object;
		if ( object == OBJECT_PLAYER1 ) {
			_player_pos[ 0 ].x = ( i % MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
			_player_pos[ 0 ].y = ( i / MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
			_objects[ i ] = OBJECT_NONE;
		}
		if ( object == OBJECT_PLAYER2 ) {
			_player_pos[ 1 ].x = ( i % MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
			_player_pos[ 1 ].y = ( i / MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
			_objects[ i ] = OBJECT_NONE;
		}
	}
}

Map::~Map( ) {
}

void Map::update( ) {
}

void Map::draw( ) const {
	_stage->setRect( 0, 0, 4800, 1920 );
	_stage->setPos( 0, 0, CHIP_SIZE * MAP_WIDTH_CHIP_NUM, CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	_stage->draw( );
	
	drawFeed( );
}

void Map::drawFeed( ) const {
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		int sx = ( i % MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
		int sy = ( i / MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
		if ( _objects[ i ] == OBJECT_FEED ) {
			_feeds->setRect( 64, 0, 64, 64 );
			_feeds->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_feeds->draw( );
		}
		if ( _objects[ i ] == OBJECT_ENHANCE_FEED ) {
			_feeds->setRect( 0, 0, 64, 64 );
			_feeds->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_feeds->draw( );
		}
	}
}

unsigned char Map::getObject( const Vector& pos ) const {
	int ox = ( int )( pos.x / CHIP_SIZE );
	int oy = ( int )( pos.y / CHIP_SIZE );
	return getObject( ox, oy );
}

unsigned char Map::getObject( int ox, int oy ) const {
	assert( ox >= 0 && ox <= MAP_WIDTH_CHIP_NUM && oy >= 0 && oy <= MAP_HEIGHT_CHIP_NUM );
	if ( ox < 0 || ox >= MAP_WIDTH_CHIP_NUM || oy < 0 || oy >= MAP_HEIGHT_CHIP_NUM ) {
		return OBJECT_WALL;
	}

	int idx = ox + oy * MAP_WIDTH_CHIP_NUM;
	unsigned char obj = _objects[ idx ];
	return obj;
}

void Map::eatFeed( const Vector& pos ) {
	int ox = ( int )( pos.x / CHIP_SIZE );
	int oy = ( int )( pos.y / CHIP_SIZE );
	eatFeed( ox, oy );
}

void Map::eatFeed( int ox, int oy ) {
	assert( ox >= 0 && ox <= MAP_WIDTH_CHIP_NUM && oy >= 0 && oy <= MAP_HEIGHT_CHIP_NUM );
#if !_DEBUG
	if ( ox < 0 || ox >= MAP_WIDTH_CHIP_NUM || oy < 0 || oy >= MAP_HEIGHT_CHIP_NUM ) {
		return;
	}
#endif
	int idx = ox + oy * MAP_WIDTH_CHIP_NUM;
	_objects[ idx ] = OBJECT_NONE;
}

Vector Map::getPlayerPos( int  id ) {
	return _player_pos[ id ];
}
