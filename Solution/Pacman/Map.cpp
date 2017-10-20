#include "Map.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"
#include "Application.h"
#include "Binary.h"
#include <assert.h>

const std::string FILE_PATH = "Resource/MapData/test.objs";

MapPtr Map::getTask( ) {
	return std::dynamic_pointer_cast< Map >( Application::getInstance( )->getTask( getTag( ) ) );
}

Map::Map( ) {
}

Map::~Map( ) {
}

void Map::initialize( ) {
	_stage = Drawer::getTask( )->createImage( "MapData/test_stage.png" );
	_chip = Drawer::getTask( )->createImage( "chip.png" );
	_chip->setRect( 0, 0, 64, 64 );

	ApplicationPtr app = Application::getInstance( );
	BinaryPtr binary = BinaryPtr( new Binary );
	app->loadBinary( FILE_PATH, binary );

	_objects.resize( MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM );

	unsigned char object;
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		binary->read( (void*)&object, sizeof( unsigned char ) );
		_objects[ i ] = object;
	}
}

void Map::update( ) {
}

void Map::draw( ) const {
	
	DrawerPtr drawer = Drawer::getTask( );
	for ( int i = 0; i <= MAP_HEIGHT_CHIP_NUM; i++ ) {
		drawer->drawLine( 0, i * CHIP_SIZE, CHIP_SIZE * MAP_WIDTH_CHIP_NUM, i * CHIP_SIZE );
	}
	for ( int i = 0; i <= MAP_WIDTH_CHIP_NUM; i++ ) {
		drawer->drawLine( i * CHIP_SIZE, 0, i * CHIP_SIZE, CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	}

	//_stage->setRect( 0, 0, 1200, 480 );
	_stage->setPos( 0, 0, WIDTH, HEIGHT );
	_stage->draw( );
		
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		if ( _objects[ i ] == OBJECT_WALL ) {
			int sx = ( i % MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
			int sy = ( i / MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;

			_chip->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_chip->draw( );
		}
	}
}

unsigned char Map::getObject( const Vector& pos ) const {
	int ox = ( int )( pos.x / CHIP_SIZE );
	int oy = ( int )( pos.y / CHIP_SIZE );
	return getObject( ox, oy );
}

unsigned char Map::getObject( int ox, int oy ) const {
	//assert( ox >= 0 && ox <= MAP_WIDTH_CHIP_NUM && oy >= 0 && oy <= MAP_HEIGHT_CHIP_NUM );
	if ( ox < 0 || ox >= MAP_WIDTH_CHIP_NUM || oy < 0 || oy >= MAP_HEIGHT_CHIP_NUM ) {
		return OBJECT_WALL;
	}

	int idx = ox + oy * MAP_WIDTH_CHIP_NUM;
	unsigned char obj = _objects[ idx ];
	return obj;
}
