#include "Object.h"
#include "define.h"
#include "Application.h"
#include "Binary.h"
#include <direct.h>

const int CHIP_NUM = MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM;
const std::string EXTENSION = ".objs";

Object::Object( ) {
	_chips.resize( CHIP_NUM );
	for ( int i = 0; i < CHIP_NUM; i++ ) {
		_chips[ i ] = OBJECT_NONE;
		//_chips[ i ] = i % 4;
	}
}

Object::~Object( ) {
}

unsigned char Object::getChip( int ox, int oy ) const {
	int idx = ox + oy * MAP_WIDTH_CHIP_NUM;
	if ( idx < 0 || idx >= CHIP_NUM ) {
		return OBJECT_NONE;
	}
	return _chips[ idx ];
}

void Object::setChip( int ox, int oy, unsigned char chip ) {
	_chips[ ox + oy * MAP_WIDTH_CHIP_NUM ] = chip;
}

void Object::save( std::string directory, std::string filename ) const {
	_mkdir( directory.c_str( ) );

	BinaryPtr binary = BinaryPtr( new Binary );
	
	int size = ( int )( sizeof( unsigned char ) * CHIP_NUM );
	binary->ensure( size );
	binary->write( (void*)_chips.data( ), size );
	
	if ( filename.find( EXTENSION ) == std::string::npos ) {
		filename += EXTENSION;
	}
	filename = directory + filename;
	ApplicationPtr app = Application::getInstance( );
	app->saveBinary( filename, binary );
}

void Object::load( std::string directory, std::string filename ) const {
	if ( filename.find( EXTENSION ) == std::string::npos ) {
		filename += EXTENSION;
	}
	filename = directory + filename;

	BinaryPtr binary( new Binary );

	ApplicationPtr app( Application::getInstance( ) );
	if ( !app->loadBinary( filename, binary ) ) {
		return;
	}
	
	int size = ( int )( sizeof( unsigned char ) * CHIP_NUM );
	binary->read( (void*)_chips.data( ), size );
}
