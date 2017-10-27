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
	Vector self_pos = getPos( );

	Vector distance = pacman_pos - self_pos;
	Vector dir = distance.normalize( );
	if ( fabs( distance.y ) > fabs( distance.x ) ) {
		Vector vec = getVec( );
		vec.y += dir.y * MOVE_SPEED;
		if ( map->getObject( self_pos + Vector( 0, vec.y + dir.y > 0 ? CHARA_SIZE : 0 ) ) == OBJECT_WALL ) {
			vec.y -= dir.y * MOVE_SPEED;
			vec.x += dir.x * MOVE_SPEED;
		}
		setVec( vec );
	} else {
		Vector vec = getVec( );
		vec.x += dir.x * MOVE_SPEED;
		if ( map->getObject( self_pos + Vector( vec.x + dir.x > 0 ? CHARA_SIZE : -CHARA_SIZE, 0 ) ) == OBJECT_WALL ) {
			vec.x -= dir.x * MOVE_SPEED;
			vec.y += dir.y * MOVE_SPEED;
		}
		setVec( vec );
	}
	{
		Vector vec = getVec( );
		if ( vec.getLength2( ) > MAX_SPEED * MAX_SPEED ) {
			setVec( vec.normalize( ) * MAX_SPEED );
		}
	}
}

IMGAE_DATA EnemyShadow::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 0;
	result.tw  = 64;
	result.th  = 64;
	result.sx2 = ( int )( pos.x + CHARA_SIZE / 2 );
	result.sy2 = ( int )pos.y;
	return result;
}
