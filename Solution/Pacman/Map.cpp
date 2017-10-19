#include "Map.h"
#include "define.h"
#include "Drawer.h"
#include "Image.h"

Map::Map( ) {
	_stage = Drawer::getTask( )->createImage( "map.png" );
}

Map::~Map( ) {
}

void Map::update( ) {
	_stage->setRect( 0, 0, 672, 256 );
	_stage->setPos( 0, 0, WIDTH, HEIGHT );
	_stage->draw( );
}
