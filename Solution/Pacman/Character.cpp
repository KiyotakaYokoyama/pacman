#include "Character.h"
#include "Map.h"
#include "define.h"

static const int MAX_ACT_TIME = 0xffffff;

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
	MapPtr map = Map::getTask( );
	//è„
	if ( _vec.y < 0 ) {
		unsigned char obj = map->getObject( _pos + Vector( 0, _vec.y - CHIP_SIZE ) );
		if ( obj == OBJECT_WALL ) {
			_pos.y = ( ( int )( _pos.y + _vec.y - CHIP_SIZE ) / CHIP_SIZE + 1 ) * CHIP_SIZE + CHIP_SIZE;
			_vec.y = 0;
		}
	}
	//â∫
	if ( _vec.y > 0 ) {
		unsigned char obj = map->getObject( _pos + Vector( 0, _vec.y ) );
		if ( obj == OBJECT_WALL ) {
			_pos.y = ( ( int )( _pos.y + _vec.y ) / CHIP_SIZE ) * CHIP_SIZE - 1;
			_vec.y = 0;
		}
	}
	//ç∂ë§
	if ( _vec.x < 0 ) {
		if ( map->getObject( _pos + Vector( _vec.x, 0 ) ) == OBJECT_WALL ) {
			_pos.x = ( ( int )( ( _pos.x + _vec.x ) / CHIP_SIZE ) + 1 ) * CHIP_SIZE + CHIP_SIZE / 2 + 1;
			_vec.x = 0;
		}
	}
	//âEë§
	if ( _vec.x > 0 ) {
		if ( map->getObject( _pos + Vector( _vec.x, 0 ) ) == OBJECT_WALL ) {
			_pos.x = ( ( int )( _pos.x + _vec.x ) / CHIP_SIZE ) * CHIP_SIZE - 1;
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
