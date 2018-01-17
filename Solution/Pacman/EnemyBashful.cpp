#include "EnemyBashful.h"
#include "Game.h"
#include "SceneStage.h"
#include "Pacman.h"
#include "EnemyShadow.h"

static const int WAIT_ANIM_TIME = 5;
static const int MOVE_SPEED = 5;
static const int MAX_SPEED = 6;


EnemyBashful::EnemyBashful( const Vector& pos, EnemyShadowPtr shadow ) :
Enemy( pos ), 
_shadow( shadow ) {
}

EnemyBashful::~EnemyBashful( ) {
}

void EnemyBashful::moving( ) {
	GamePtr game = Game::getTask( );
	const int CHARA_SIZE = game->getCharaSize( );
	const int CHIP_SIZE = game->getChipSize( );
	Vector self_pos = getPos( ) + Vector( 0, -CHARA_SIZE / 2 );
	SceneStagePtr stage = game->getStage( );
	Vector symmetry_pos = ( stage->getPacman( PLAYER_1 )->getPos( ) + stage->getPacman( PLAYER_2 )->getPos( ) ) * 0.5;
	Vector shadow_pos = _shadow ? _shadow->getPos( ) : Vector( MAP_WIDTH_CHIP_NUM * CHIP_SIZE / 2, MAP_HEIGHT_CHIP_NUM * CHIP_SIZE / 2 );

	Vector distance = ( shadow_pos - symmetry_pos ) * -1;
	Vector goal_pos = symmetry_pos + distance;
	moveGoal( goal_pos );
}

IMGAE_DATA EnemyBashful::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * SPRITE_SIZE;
	result.ty  = SPRITE_SIZE * 2;
	
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

SCORE EnemyBashful::getScore( ) const {
	return SCORE_BASHFUL;
}
