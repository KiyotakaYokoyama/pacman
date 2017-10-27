#include "Character.h"
#include "Game.h"
#include "Map.h"
#include "define.h"

static const int MAX_ACT_TIME = 0xfffffff;

Character::Character( Vector pos ) :
_pos( pos ),
_act_time( 0 ) {
}

Character::~Character( ) {
}

void Character::update( ) {
	act( );
	_act_time = ( _act_time++ ) % MAX_ACT_TIME;

	updateColl( );

	_pos += _vec;
}

void Character::updateColl( ) {
	MapPtr map = Game::getTask( )->getMap( );
	const int HARF_CHARA_SIZE = CHARA_SIZE / 2;
	//上
	if ( _vec.y < 0 ) {
		if ( ( _pos.y + _vec.y ) - CHARA_SIZE < 0 ) {
			_pos.y = CHIP_SIZE;
			_vec.y = 0;
		} else {
			//左上
			unsigned char left_obj = map->getObject( _pos + Vector( -HARF_CHARA_SIZE, _vec.y - CHARA_SIZE ) );
			//右上
			unsigned char light_obj = map->getObject( _pos + Vector( HARF_CHARA_SIZE, _vec.y - CHARA_SIZE ) );
			if ( left_obj == OBJECT_WALL || light_obj == OBJECT_WALL ) {
				_pos.y = ( ( int )( _pos.y + _vec.y - CHARA_SIZE ) / CHIP_SIZE + 1 ) * CHIP_SIZE + CHARA_SIZE;
				_vec.y = 0;
			}
		}
	}
	//下
	if ( _vec.y > 0 ) {
		//左下
		unsigned char left_obj = map->getObject( _pos + Vector( -HARF_CHARA_SIZE, _vec.y ) );
		//右下
		unsigned char light_obj = map->getObject( _pos + Vector( HARF_CHARA_SIZE, _vec.y ) );
		if ( left_obj == OBJECT_WALL || light_obj == OBJECT_WALL ) {
			_pos.y = ( ( int )( _pos.y + _vec.y ) / CHIP_SIZE ) * CHIP_SIZE - 1;
			_vec.y = 0;
		}
	}
	//左側
	if ( _vec.x < 0 ) {
		Vector f_pos = _pos + Vector( _vec.x - HARF_CHARA_SIZE, 0 );
		if ( f_pos.x < 0 ) {
			_pos.x = HARF_CHARA_SIZE;
			_vec.x = 0;
		} else {
			//左上
			unsigned char up_obj = map->getObject( f_pos + Vector( 0, -CHARA_SIZE ) );
			//左下
			unsigned char down_obj = map->getObject( f_pos + Vector( 0, 0 ) );
			if ( up_obj == OBJECT_WALL || down_obj == OBJECT_WALL ) {
				_pos.x = ( ( ( int )f_pos.x / CHIP_SIZE ) + 1 ) * CHIP_SIZE + HARF_CHARA_SIZE;
				_vec.x = 0;
			}
		}
	}
	//右側
	if ( _vec.x > 0 ) {
		Vector f_pos = _pos + Vector( _vec.x + HARF_CHARA_SIZE, 0 );
		//右上
		unsigned char up_obj = map->getObject( f_pos + Vector( 0, -CHARA_SIZE ) );
		//右下
		unsigned char down_obj = map->getObject( f_pos + Vector( 0, 0 ) );
		if ( up_obj == OBJECT_WALL || down_obj == OBJECT_WALL ) {
			_pos.x = ( ( int )f_pos.x / CHIP_SIZE ) * CHIP_SIZE - HARF_CHARA_SIZE - 1;
			_vec.x = 0;
		}
	}
}

int Character::getActTime( ) const {
	return _act_time;
}

Vector Character::getPos( ) const {
	return _pos;
}

Vector Character::getVec( ) const {
	return _vec;
}

void Character::setVec( const Vector& vec ) {
	_vec = vec;
}
