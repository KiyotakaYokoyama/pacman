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
	_stage->setRect( 0, 0, 4800, 1920 );
	_stage->setPos( 0, 0, CHIP_SIZE * MAP_WIDTH_CHIP_NUM, CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	_stage->draw( );
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
