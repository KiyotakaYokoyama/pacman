#include "EnemyShadow.h"
#include "SceneStage.h"
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
	SceneStagePtr scene_stage = SceneStage::getTask( );
	Vector self_pos = getPos( ) + getCharaSize( );
	PacmanConstPtr pacman = scene_stage->getPacman( self_pos );
	Vector pacman_pos = getPos( ) + ( Vector( WIDTH / 2, MAP_HEIGHT_CHIP_NUM * scene_stage->getChipSize( ) / 2 ) - getPos( ) ).normalize( ) * 5;
	if ( pacman ) {
		pacman_pos = pacman->getPos( ) + getCharaSize( );
	}
	moveGoal( pacman_pos );
}

IMGAE_DATA EnemyShadow::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	const int CHARA_SIZE = SceneStage::getTask( )->getCharaSize( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * SPRITE_SIZE;
	result.ty  = SPRITE_SIZE * 0;

	if ( getDir( ) == DIR_UP ) {
		result.tx += SPRITE_SIZE * 4;
	}
	if ( getDir( ) == DIR_DOWN ) {
		result.tx += SPRITE_SIZE * 2;
	}

	result.tw  = SPRITE_SIZE;
	result.th  = SPRITE_SIZE;
	result.sx2 = ( int )( pos.x + CHARA_SIZE / 2 );
	result.sy2 = ( int )pos.y;

	if ( getDir( ) == DIR_LEFT ) {
		int tmp = result.sx1;
		result.sx1 = result.sx2;
		result.sx2 = tmp;
	}

	return result;
}

SCORE EnemyShadow::getScore( ) const {
	return SCORE_SHADOW;
}
