#include "Map.h"
#include "define.h"
#include "Game.h"
#include "SceneStage.h"
#include "Pacman.h"
#include "Military.h"
#include "EnemyBashful.h"
#include "EnemyPokey.h"
#include "EnemyShadow.h"
#include "EnemySpeedy.h"
#include "EnemyPurple.h"
#include "EnemyYellow.h"
#include "EnemyGreen.h"
#include "EnemyBlunder.h"
#include "Drawer.h"
#include "Image.h"
#include "Application.h"
#include "Binary.h"
#include "LoadCSV.h"
#include <assert.h>

const std::string FILE_DIRECTORY = "Resource/MapData/";
const int STAGE_NUM = 10;
const int MAX_COUNT = 0xfffffff;
const int MAX_FADE_COUNT = 150;
const double FADE_SPEED = 1.0 / ( MAX_FADE_COUNT / 2 );

Map::Map( ) :
_count( 0 ),
_eaten_feeds( 0 ) {
	DrawerPtr drawer = Drawer::getTask( );
	_feeds = drawer->createImage( "feed.png" );
	_revival_area = drawer->createImage( "revival_area.png" );
	_revival_area->setRect( 0, 0, 64, 64 );
	
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
	if ( idx < ( int )_stages.size( ) ) {
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
		const int CHIP_SIZE = Game::getTask( )->getChipSize( );
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

	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		_player_pos[ i ] = Vector( 32 + i * 868, 32 + i * 268 );
	}

	_feed_pos.clear( );
	_revival_feed_pos.clear( );
	_enemy_pos.clear( );
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
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
		if ( object == OBJECT_REVIVAL_FEED ) {
			Vector pos( i % MAP_WIDTH_CHIP_NUM, i / MAP_WIDTH_CHIP_NUM );
			_revival_feed_pos.push_back( pos );
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
	checkRevivalFeed( );
	_count = ( _count + 1 ) % MAX_COUNT;
}

void Map::drawRevivalArea( ) const {
	GamePtr game = Game::getTask( );
	const int CHIP_SIZE = game->getChipSize( );
	if ( _eaten_feeds == _feed_pos.size( ) ) {
		double ratio = FADE_SPEED * ( _count % MAX_FADE_COUNT );
		if ( ratio > 1.0 ) {
			ratio = 2.0 - ratio;
		}
		int size = ( int )_revival_feed_pos.size( );
		for ( int i = 0; i < size; i++ ) {
			_revival_area->setBlend( Image::BLEND_ALPHA, ratio );
			Vector pos = _revival_feed_pos[ i ] * CHIP_SIZE;
			_revival_area->setPos( ( int )pos.x, ( int )pos.y, ( int )pos.x + CHIP_SIZE, ( int )pos.y + CHIP_SIZE );
			_revival_area->draw( );
		}
	}
}

void Map::checkRevivalFeed( ) {
	SceneStagePtr master = Game::getTask( )->getStage( );
	Vector p1_pos = getMapPos( master->getPacman( PLAYER_1 )->getPos( ) );
	Vector p2_pos = getMapPos( master->getPacman( PLAYER_2 )->getPos( ) );

	bool revival = false;
	int size = ( int )_revival_feed_pos.size( );
	for ( int i = 0; i < size; i++ ) {
		if ( _revival_feed_pos[ i ] == p1_pos ||
			 _revival_feed_pos[ i ] == p2_pos ) {
			revival = true;
			break;
		}
	}

	if ( revival ) {
		int size = ( int )_feed_pos.size( );
		for ( int i = 0; i < size; i++ ) {
			if ( getObject( ( int )_feed_pos[ i ].x, ( int )_feed_pos[ i ].y ) == OBJECT_ENHANCE_FEED ) {
				return;
			}
		}
		for ( int i = 0; i < size; i++ ) {
			int idx = ( int )( _feed_pos[ i ].x + _feed_pos[ i ].y * MAP_WIDTH_CHIP_NUM );
			_objects[ idx ] = OBJECT_ENHANCE_FEED;
		}
		_eaten_feeds = 0;
	}
}

void Map::draw( ) const {
	_stage->draw( );
	drawRevivalArea( );
	drawFeed( );
}

void Map::drawFeed( ) const {
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
	for ( int i = 0; i < MAP_WIDTH_CHIP_NUM * MAP_HEIGHT_CHIP_NUM; i++ ) {
		int sx = ( i % MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
		int sy = ( i / MAP_WIDTH_CHIP_NUM ) * CHIP_SIZE;
		if ( _objects[ i ] == OBJECT_FEED ) {
			_feeds->setRect( 0, 0, 64, 64 );
			_feeds->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_feeds->draw( );
		}
		if ( _objects[ i ] == OBJECT_ENHANCE_FEED ) {
			_feeds->setRect( 64, 0, 64, 64 );
			_feeds->setPos( sx, sy, sx + CHIP_SIZE, sy + CHIP_SIZE );
			_feeds->draw( );
		}
	}
}

unsigned char Map::getObject( const Vector& pos ) const {
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
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
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
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
	if ( _objects[ idx ] == OBJECT_ENHANCE_FEED ) {
		_eaten_feeds++;
	}
	_objects[ idx ] = OBJECT_NONE;
}

Vector Map::getPlayerPos( int id ) {
	return _player_pos[ id ];
}

Vector Map::getMapPos( const Vector& pos ) const {
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
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
		case OBJECT_BLUNDER:
			military->addEnemy( EnemyPtr( new EnemyBlunder( enemy.pos ) ) );
			continue;
		case OBJECT_GREEN:
			military->addEnemy( EnemyPtr( new EnemyGreen( enemy.pos ) ) );
			continue;
		case OBJECT_PURPLE:
			military->addEnemy( EnemyPtr( new EnemyPurple( enemy.pos ) ) );
			continue;
		case OBJECT_YELLOW:
			military->addEnemy( EnemyPtr( new EnemyYellow( enemy.pos ) ) );
			continue;
		default:
			continue;
		}
	}
}

bool Map::isInMap( const Vector& pos ) const {
	const int CHIP_SIZE = Game::getTask( )->getChipSize( );
	return pos.x >= 0 && pos.x < CHIP_SIZE * MAP_WIDTH_CHIP_NUM &&
		   pos.y >= 0 && pos.y < CHIP_SIZE * MAP_HEIGHT_CHIP_NUM;
}

std::vector< Vector > Map::getEnhanceFeedChipPos( ) const {
	std::vector< Vector > result;
	int size = ( int )_feed_pos.size( );
	for ( int i = 0; i < size; i++ ) {
		if ( getObject( ( int )_feed_pos[ i ].x, ( int )_feed_pos[ i ].y ) == OBJECT_ENHANCE_FEED ) {
			result.push_back( _feed_pos[ i ] );
		}
	}
	return result;
}
