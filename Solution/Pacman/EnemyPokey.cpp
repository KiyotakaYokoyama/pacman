#include "EnemyPokey.h"
#include "Game.h"
#include "SceneStage.h"
#include "Map.h"

static const int WAIT_ANIM_TIME = 5;
const int DIR_NUM = 4;
const Vector DIRECTION[ DIR_NUM ] = {
	Vector(  0, -1 ),
	Vector(  0,  1 ),
	Vector(  1,  0 ),
	Vector( -1,  0 )
};

EnemyPokey::EnemyPokey( const Vector& pos ) :
Enemy( pos ) {
}

EnemyPokey::~EnemyPokey( ) {
}

void EnemyPokey::moving( ) {
	if ( _move_count == _move_lenght ) {
		//別の方向に変える
		//方向を決める
		setMoveDir( );
		//何マス進むか決める
		_move_lenght = rand( ) % 7;
		if ( _move_lenght % 2 == 0 ) {
			_move_lenght++;
		}
		_move_count = 0;
	} else {
		//いままでの方向に進む
		_move_count++;
	}

	const int CHIP = Game::getTask( )->getChipSize( );
	moveGoal( getPos( ) + DIRECTION[ _dir ] * CHIP );
}

void EnemyPokey::setMoveDir( ) {
	const int CHIP = Game::getTask( )->getChipSize( );
	MapPtr map = Game::getTask( )->getStage( )->getMap( );
	Vector pos = getPos( );

	int dir = rand( ) % DIR_NUM;

	for ( int i = 0; i < DIR_NUM; i++ ) {
		if ( map->getObject( pos + DIRECTION[ dir ] * CHIP ) != OBJECT_WALL ) {
			_dir = ( DIR )dir;
			return;
		}
		dir = ( dir + 1 ) % DIR_NUM;
	}
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
