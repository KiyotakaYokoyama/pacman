#include "EnemyBlunder.h"
#include "Game.h"
#include "SceneStage.h"
#include "Pacman.h"

static const int WAIT_ANIM_TIME = 5;

EnemyBlunder::EnemyBlunder( const Vector& pos ) :
Enemy( pos ) {
}

EnemyBlunder::~EnemyBlunder( ) {
}

void EnemyBlunder::moving( ) {
	GamePtr game = Game::getTask( );
	Vector self_pos = getPos( );
	PacmanConstPtr pacman = game->getStage( )->getPacman( self_pos );
	if ( pacman ) {
		Vector vec = ( pacman->getPos( ) - self_pos ) * -1;
		moveGoal( self_pos + vec );
	}
}

IMGAE_DATA EnemyBlunder::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * SPRITE_SIZE;
	result.ty  = SPRITE_SIZE * 4;

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

SCORE EnemyBlunder::getScore( ) const {
	return SCORE_BLUNDER;
}
