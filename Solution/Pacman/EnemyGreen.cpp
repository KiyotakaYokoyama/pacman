#include "EnemyGreen.h"
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
	SceneStagePtr scene_stage = SceneStage::getTask( );
	const int CHIP_SIZE = scene_stage->getChipSize( );
	Vector self_pos = getPos( ) + getCharaSize( );
	PacmanConstPtr pacman = scene_stage->getPacman( self_pos );
	Vector pacman_pos = pacman->getPos( ) + getCharaSize( );
	Vector pacman_vec = pacman->getVec( );

	Vector distance = pacman_pos - self_pos;
	int root_num = ( int )( ( distance.x + 0.5 ) / CHIP_SIZE + ( distance.y + 0.5 ) / CHIP_SIZE );
	if ( abs( root_num ) > 10 && abs( root_num ) < 15 ) {
		setVec( pacman_vec );
	} else {
		moveGoal( pacman_pos );
	}
}

IMGAE_DATA EnemyGreen::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	const int CHARA_SIZE = SceneStage::getTask( )->getCharaSize( );
	Vector pos = getPos( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 64 * 4;
	
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

SCORE EnemyGreen::getScore( ) const {
	return SCORE_GREEN;
}
