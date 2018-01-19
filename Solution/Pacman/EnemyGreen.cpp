#include "EnemyGreen.h"
#include "Game.h"
#include "SceneStage.h"
#include "Pacman.h"
#include "Map.h"

static const int WAIT_ANIM_TIME = 5;

EnemyGreen::EnemyGreen( const Vector& pos ) :
Enemy( pos ) {
}


EnemyGreen::~EnemyGreen( ) {
}

void EnemyGreen::moving( ) {
	GamePtr game = Game::getTask( );
	const int CHIP_SIZE = game->getChipSize( );
	Vector self_pos = getPos( ) + getCharaSize( );
	PacmanConstPtr pacman = game->getStage( )->getPacman( self_pos );
	Vector pacman_pos = getPos( ) + ( Vector( WIDTH / 2, MAP_HEIGHT_CHIP_NUM * CHIP_SIZE / 2 ) - getPos( ) ).normalize( ) * 5;
	if ( pacman ) {
		pacman_pos = pacman->getPos( ) + getCharaSize( );
	}
	Vector pacman_vec;
	if ( pacman ) {
		pacman_vec = pacman->getVec( );
	}

	Vector distance = pacman_pos - self_pos;
		//MAX_CEARCH_LENGTH = 10;
	int root_num = ( int )( ( distance.x + 0.5 ) / CHIP_SIZE + ( distance.y + 0.5 ) / CHIP_SIZE );
	if ( abs( root_num ) > 7 && abs( root_num ) < 10 ) {
		setVec( pacman_vec );
	} else {
		moveGoal( pacman_pos );
	}
}

IMGAE_DATA EnemyGreen::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	Vector pos = getPos( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * SPRITE_SIZE;
	result.ty  = SPRITE_SIZE * 5;
	
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

SCORE EnemyGreen::getScore( ) const {
	return SCORE_GREEN;
}
