#include "EnemyShadow.h"
#include "Game.h"
#include "Pacman.h"
#include "Map.h"

static const int WAIT_ANIM_TIME = 5;
static const Vector UP   (  0, -1 );
static const Vector DOWN (  0,  1 );
static const Vector LEFT ( -1,  0 );
static const Vector RIGHT(  1,  0 );

EnemyShadow::EnemyShadow( const Vector& pos ) :
Enemy( pos ) {
}


EnemyShadow::~EnemyShadow( ) {
}

void EnemyShadow::moving( ) {
	GamePtr game = Game::getTask( );
	MapPtr map = game->getMap( );
	const int CHARA_SIZE = game->getCharaSize( );
	const int CHIP_SIZE = game->getChipSize( );
	Vector pacman_pos = game->getPacman( )->getPos( ) + Vector( 0, -CHARA_SIZE / 2 );
	Vector self_pos = getPos( ) + Vector( 0, -CHARA_SIZE / 2 );
	Vector distance = pacman_pos - self_pos;
	if ( fabs( distance.x ) > 3 * CHIP_SIZE ||
		 fabs( distance.y ) > 3 * CHIP_SIZE ) {
		distance = distance.normalize( ) * ( 3 * CHIP_SIZE );
	}

	Vector goal = self_pos + distance;
	if ( map->getObject( goal ) == OBJECT_WALL ) {
		while ( true ) {
			if ( map->getObject( goal + UP * CHIP_SIZE ) != OBJECT_WALL ) {
				goal += UP * CHIP_SIZE;
				break;
			}
			if ( map->getObject( goal + DOWN * CHIP_SIZE ) != OBJECT_WALL ) {
				goal += DOWN * CHIP_SIZE;
				break;
			}
			if ( map->getObject( goal + LEFT * CHIP_SIZE ) != OBJECT_WALL ) {
				goal += LEFT * CHIP_SIZE;
				break;
			}
			if ( map->getObject( goal + RIGHT * CHIP_SIZE ) != OBJECT_WALL ) {
				goal += RIGHT * CHIP_SIZE;
				break;
			}

			goal += goal.x < goal.y ?
						( goal.x < 0 ? LEFT * CHIP_SIZE : RIGHT * CHIP_SIZE ) :
						( goal.y < 0 ? UP   * CHIP_SIZE : DOWN  * CHIP_SIZE );
		}
	}

	Vector vec = getVec( ) + AStar( goal ) * 5;
	if ( vec.getLength2( ) > 6 * 6 ) {
		vec = vec.normalize( ) * 6;
	}
	if ( ( pacman_pos - self_pos ).getLength2( ) < 5 * 5 ) {
		vec = pacman_pos - self_pos;
	}
	setVec( vec );
}

IMGAE_DATA EnemyShadow::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 64 * 0;

	if ( getDir( ) == DIR_UP ) {
		result.tx += 64 * 4;
	}
	if ( getDir( ) == DIR_DOWN ) {
		result.tx += 64 * 2;
	}

	result.tw  = 64;
	result.th  = 64;
	result.sx2 = ( int )( pos.x + CHARA_SIZE / 2 );
	result.sy2 = ( int )pos.y;

	if ( getDir( ) == DIR_LEFT ) {
		int tmp = result.sx1;
		result.sx1 = result.sx2;
		result.sx2 = tmp;
	}

	return result;
}
