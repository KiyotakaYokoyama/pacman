#include "EnemyShadow.h"
#include "Game.h"
#include "Pacman.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 5;

EnemyShadow::EnemyShadow( const Vector& pos ) :
Enemy( pos ) {
}


EnemyShadow::~EnemyShadow( ) {
}

void EnemyShadow::act( ) {
	PacmanConstPtr pacman = Game::getTask( )->getPacman( );
	Vector pacman_pos = pacman->getPos( );

	Vector distance = pacman_pos - getPos( );
	Vector dir = distance.normalize( );
	if ( fabs( distance.y ) > fabs( distance.x ) ) {
		Vector vec = getVec( );
		vec.y += dir.y * MOVE_SPEED;

	} else {
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
