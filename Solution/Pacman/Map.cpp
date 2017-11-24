#include "Map.h"
#include "define.h"
#include "SceneStage.h"
#include "Military.h"
#include "EnemyBashful.h"
#include "EnemyPokey.h"
#include "EnemyShadow.h"
#include "EnemySpeedy.h"
#include "Drawer.h"
#include "Image.h"
#include "Application.h"
#include "Binary.h"
#include "LoadCSV.h"
#include <assert.h>

const std::string FILE_DIRECTORY = "Resource/MapData/";
const int STAGE_NUM = 10;

Map::Map( ) {
	DrawerPtr drawer = Drawer::getTask( );
	_feeds = drawer->createImage( "feeds.png" );

	std::string filename = FILE_DIRECTORY + "stage";
	LoadCSV csv = LoadCSV( filename.c_str( ), STAGE_NUM );

	int size = csv.getSize( );
	for ( int i = 0; i < size; i++ ) {
		std::string str = csv.getData( i );
		_stages.push_back( str );
	}

	loadStage( _stages[ 0 ] );
}

Map::~Map( ) {
}

bool Map::loadStage( int idx ) {
	bool result = false;
	assert( idx < STAGE_NUM );
	if ( idx < _stages.size( ) ) {
		loadStage( _stages[ idx ] );
		result = true;
	}
	return result;
}

void Map::loadStage( std::string stage_name ) {
	{
		DrawerPtr drawer = Drawer::getTask( );
		std::string file_path = "MapData/" + stage_name + "_stage.png";
		_stage = drawer->createImage( file_path.c_str( ) );
		const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
		_stage->setRect( 0, 0, 4800, 1920 );
		_stage->setPos( 0, 0, CHIP_SIZE * MAP_WIDTH_CHIP_NUM, CHIP_SIZE * MAP_HEIGHT_CHIP_NUM );
	}

	ApplicationPtr app = Application::getInstance( );
	BinaryPtr binary = BinaryPtr( new Binary );
	std::string file_path = FILE_DIRECTORY + stage_name;
	file_path += ".objs";
	app->loadBinary( file_path, binary );

	_objects.clear( );
	_objects.resize( MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM );

	for ( int i = 0; i < PLAYER_NUM; i++ ) {
		_player_pos[ i ] = Vector( 32 + i * 868, 32 + i * 268 );
	}

	_feed_pos.clear( );
	_enemy_pos.clear( );
	const int CHIP_SIZE = SceneStage::getTask()->getChipSize();
	unsigned char object;
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		binary->read( (void*)&object, sizeof( unsigned char ) );
		_objects[ i ] = object;
		const double X = ( i % MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE + CHIP_SIZE / 2;
		const double Y = ( i / MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE + CHIP_SIZE;
		if ( object == OBJECT_PLAYER1 ) {
			_player_pos[ 0 ] = Vector( X, Y );
			_objects[ i ] = OBJECT_NONE;
		}
		if ( object == OBJECT_PLAYER2 ) {
			_player_pos[ 1 ] = Vector( X, Y );
			_objects[ i ] = OBJECT_NONE;
		}

		if ( object == OBJECT_ENHANCE_FEED ) {
			Vector pos( i % MAP_WIDTH_CHIP_NUM, i / MAP_WIDTH_CHIP_NUM );
			_feed_pos.push_back( pos );
		}
		if ( object == OBJECT_SHADOW || object == OBJECT_BASHFUL ||
			 object == OBJECT_POKEY  || object == OBJECT_SPEEDY ) {
			ENEMY enemy;
			enemy.index = object;
			enemy.pos = Vector( X, Y );
			_enemy_pos.push_back( enemy );
			_objects[ i ] = OBJECT_NONE;
		}
	}
}

void Map::update( ) {
}

void Map::draw( ) const {
	_stage->draw( );
	
	drawFeed( );
}

void Map::drawFeed( ) const {
	const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
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
	const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
	int ox = ( int )( pos.x / CHIP_SIZE );
	int oy = ( int )( pos.y / CHIP_SIZE );
	return getObject( ox, oy );
}

unsigned char Map::getObject( int ox, int oy ) const {
//	assert( ox >= 0 && ox <= MAP_WIDTH_CHIP_NUM && oy >= 0 && oy <= MAP_HEIGHT_CHIP_NUM );
	if ( ox < 0 || ox >= MAP_WIDTH_CHIP_NUM || oy < 0 || oy >= MAP_HEIGHT_CHIP_NUM ) {
		return OBJECT_WALL;
	}

	int idx = ox + oy * MAP_WIDTH_CHIP_NUM;
	unsigned char obj = _objects[ idx ];
	return obj;
}

void Map::eatFeed( const Vector& pos ) {
	const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
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

Vector Map::getPlayerPos( int id ) {
	return _player_pos[ id ];
}

Vector Map::getMapPos( const Vector& pos ) const {
	const int CHIP_SIZE = SceneStage::getTask( )->getChipSize( );
	Vector result;
	result.x = ( int )( pos.x / CHIP_SIZE );
	result.y = ( int )( pos.y / CHIP_SIZE );
	return result;
}

void Map::generateEnemy( MilitaryPtr military ) const {
	const int SIZE = ( int )_enemy_pos.size( );
	EnemyShadowPtr shadow = EnemyShadowPtr( );
	for ( int i = 0; i < SIZE; i++ ) {
		ENEMY enemy = _enemy_pos[ i ];
		switch ( enemy.index ) {
		case OBJECT_SHADOW:
			if ( !shadow ) {
				shadow = EnemyShadowPtr( new EnemyShadow( enemy.pos ) );
				military->addEnemy( shadow );
			} else {
				military->addEnemy( EnemyPtr( new EnemyShadow( enemy.pos ) ) );
			}
			continue;
		case OBJECT_SPEEDY:
			military->addEnemy( EnemyPtr( new EnemySpeedy( enemy.pos ) ) );
			continue;
		case OBJECT_BASHFUL:
			military->addEnemy( EnemyPtr( new EnemyBashful( enemy.pos, shadow ) ) );
			shadow = EnemyShadowPtr( );
			continue;
		case OBJECT_POKEY:
			military->addEnemy( EnemyPtr( new EnemyPokey( enemy.pos ) ) );
			continue;
		default:
			continue;
		}
	}
}
