#include "EnemySpeedy.h"
#include "SceneStage.h"
#include "Pacman.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 3;


EnemySpeedy::EnemySpeedy( const Vector& pos ) :
Enemy( pos ) {
}
EnemySpeedy::~EnemySpeedy( ) {
}

void EnemySpeedy::moving( ) {
	SceneStagePtr scene_stage = SceneStage::getTask( );
	Vector self_pos = getPos( ) + getCharaSize( );
	Vector pacman_pos = scene_stage->getPacman( self_pos )->getPos( ) + getCharaSize( );
	moveGoal( pacman_pos + Vector( scene_stage->getChipSize( ) * -1 * 3, 0 ) );
}

IMGAE_DATA EnemySpeedy::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	const int CHARA_SIZE = SceneStage::getTask( )->getCharaSize( );
	Vector pos = getPos( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 64 * 2;
	
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
