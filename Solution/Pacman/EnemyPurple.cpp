#include "EnemyPurple.h"
#include "Game.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_LENGTH = 7;

EnemyPurple::EnemyPurple( const Vector& pos ) :
Enemy( pos ),
_move_count( 0 ),
_dir( ( DIR )( rand( ) % 4 ) ) {
}


EnemyPurple::~EnemyPurple( ) {
}

void EnemyPurple::moving( ) {
	const int CHIP = Game::getTask( )->getChipSize( );
	if ( _dir == DIR_UP ) {
		Vector goal = getPos( ) + Vector( 0, -1 ) * CHIP;
		moveGoal( goal );
		if ( _move_count == MOVE_LENGTH ) {
			_dir = DIR_RIGHT;
			_move_count = 0;
		} else {
			_move_count++;
		}
	}

	if ( _dir == DIR_DOWN ) {
		Vector goal = getPos( ) + Vector( 0,  1 ) * CHIP;
		moveGoal( goal );
		if ( _move_count == MOVE_LENGTH ) {
			_dir = DIR_LEFT;
			_move_count = 0;
		} else {
			_move_count++;
		}
	}

	if ( _dir == DIR_RIGHT ) {
		Vector goal = getPos( ) + Vector(  1, 0 ) * CHIP;
		moveGoal( goal );
		if ( _move_count == MOVE_LENGTH ) {
			_dir = DIR_DOWN;
			_move_count = 0;
		} else {
			_move_count++;
		}
	}

	if ( _dir == DIR_LEFT ) {
		Vector goal = getPos( ) + Vector( -1, 0 ) * CHIP;
		moveGoal( goal );
		if ( _move_count == MOVE_LENGTH ) {
			_dir = DIR_UP;
			_move_count = 0;
		} else {
			_move_count++;
		}
	}
}

IMGAE_DATA EnemyPurple::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	Vector pos = getPos( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * SPRITE_SIZE;
	result.ty  = SPRITE_SIZE * 6;
	
	if ( getDir( ) == DIR_LEFT ) {
		result.tx += SPRITE_SIZE * 4;
	}
	if ( getDir( ) == DIR_UP ) {
		result.tx += SPRITE_SIZE * 6;
	}
	if ( getDir( ) == DIR_DOWN ) {
		result.tx += SPRITE_SIZE * 2;
	}

	result.tw  = SPRITE_SIZE;
	result.th  = SPRITE_SIZE;
	result.sx2 = ( int )( pos.x + CHARA_SIZE / 2 );
	result.sy2 = ( int )pos.y;
	
	return result;
}

SCORE EnemyPurple::getScore( ) const {
	return SCORE_PURPLE;
}
