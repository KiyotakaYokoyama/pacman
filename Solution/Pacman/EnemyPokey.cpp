#include "EnemyPokey.h"
#include "Game.h"

static const int WAIT_ANIM_TIME = 5;


EnemyPokey::EnemyPokey( const Vector& pos ) :
Enemy( pos ) {
}

EnemyPokey::~EnemyPokey( ) {
}

void EnemyPokey::moving( ) {
}

IMGAE_DATA EnemyPokey::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 64 * 1;
	
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

SCORE EnemyPokey::getScore( ) const {
	return SCORE_POKEY;
}
