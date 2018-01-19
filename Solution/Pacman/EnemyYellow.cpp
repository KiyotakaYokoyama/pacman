#include "EnemyYellow.h"
#include "Game.h"
#include "SceneStage.h"
#include "Map.h"

static const int WAIT_ANIM_TIME = 5;

EnemyYellow::EnemyYellow( const Vector& pos ) :
Enemy( pos ) {
}


EnemyYellow::~EnemyYellow( ) {
}

void EnemyYellow::moving( ) {
	MapPtr map = Game::getTask( )->getStage( )->getMap( );
	std::vector< Vector > feeds = map->getEnhanceFeedChipPos( );
	int feed_num = ( int )feeds.size( );
	if ( feed_num > 0 ) {
		Vector self_chip = map->getMapPos( getPos( ) );
		Vector distance = feeds[ 0 ] - self_chip;
		//一番近いエサを探す
		for ( int i = 0; i < feed_num; i++ ) { 
			Vector tmp = feeds[ i ] - self_chip;
			if ( distance.getLength2( ) > tmp.getLength2( ) ) {
				distance = tmp;
			}
		}

		//移動ポジションをA*の範囲内にする
		//MAX_CEARCH_LENGTH = 10;
		if ( fabs( distance.x ) + fabs( distance.y ) > 10 ) {
			distance = distance.normalize( ) * 14;
			distance.x = ( int )distance.x;
			distance.y = ( int )distance.y;
		}

		int chip_size = Game::getTask( )->getChipSize( );
		moveGoal( getPos( ) + distance * chip_size );
	}

	//エサを食べる
	if ( map->getObject( getPos( ) ) == OBJECT_ENHANCE_FEED ) {
		map->eatFeed( getPos( ) );
	}

}

IMGAE_DATA EnemyYellow::getImageData( ) const {
	IMGAE_DATA result = IMGAE_DATA( );
	const int CHARA_SIZE = Game::getTask( )->getCharaSize( );
	Vector pos = getPos( );
	result.sx1 = ( int )( pos.x - CHARA_SIZE / 2 );
	result.sy1 = ( int )( pos.y - CHARA_SIZE );
	
	result.tx  = ( ( getActTime( ) / WAIT_ANIM_TIME ) % 2 ) * 64;
	result.ty  = 64 * 5;

	if ( getDir( ) == DIR_LEFT ) {
		result.tx += SPRITE_SIZE * 4;
	}
	if ( getDir( ) == DIR_UP ) {
		result.tx += SPRITE_SIZE * 6;
	}
	if ( getDir( ) == DIR_DOWN ) {
		result.tx += SPRITE_SIZE * 2;
	}

	result.tw = SPRITE_SIZE;
	result.th = SPRITE_SIZE;
	result.sx2 = ( int )( pos.x + CHARA_SIZE / 2 );
	result.sy2 = ( int )pos.y;

	return result;
}

SCORE EnemyYellow::getScore( ) const {
	return SCORE_YELLOW;
}
