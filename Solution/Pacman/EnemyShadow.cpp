#include "EnemyShadow.h"
#include "Game.h"
#include "Pacman.h"
#include "Map.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 5;
static const int MAX_SPEED = 6;

EnemyShadow::EnemyShadow( const Vector& pos ) :
Enemy( pos ) {
}


EnemyShadow::~EnemyShadow( ) {
}

void EnemyShadow::act( ) {
	MapPtr map = Game::getTask( )->getMap( );
	PacmanConstPtr pacman = Game::getTask( )->getPacman( );
	Vector pacman_pos = pacman->getPos( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	Vector self_pos = getPos( ) + Vector( 0, -CHARA_SIZE / 2 );

	//Vector vec = AStar( self_pos, pacman_pos ) * MOVE_SPEED;
	//if ( ( pacman_pos - self_pos ).getLength2( ) < MOVE_SPEED * MOVE_SPEED ) {
	//	vec = pacman_pos - self_pos;
	//}
	//setVec( vec );
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
