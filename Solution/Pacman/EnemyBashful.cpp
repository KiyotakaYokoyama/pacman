#include "EnemyBashful.h"
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
	SceneStagePtr game = SceneStage::getTask( );
	const int CHARA_SIZE = game->getCharaSize( );
	const int CHIP_SIZE = game->getChipSize( );
	Vector self_pos = getPos( ) + Vector( 0, -CHARA_SIZE / 2 );
	Vector pacman_pos = game->getPacman( self_pos )->getPos( ) + Vector( 0, -CHARA_SIZE / 2 );
	Vector shadow_pos = _shadow ? _shadow->getPos( ) : pacman_pos;

	Vector distance = shadow_pos - pacman_pos;
	distance *= -1;
	Vector goal_pos = pacman_pos + distance;
	Vector to_goal = goal_pos - self_pos;
	Vector vec = to_goal.normalize( ) * MOVE_SPEED;
	if ( to_goal.getLength( ) < MOVE_SPEED ) {
		vec = to_goal;
	}
	setVec( vec );
}

IMGAE_DATA EnemyBashful::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	Vector pos = getPos( );
	const int CHARA_SIZE = SceneStage::getTask( )->getCharaSize( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 64 * 3;
	
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
