#include "Character.h"

Character::Character( Vector pos ) :
_pos( pos ) {
}

Character::~Character( ) {
}

void Character::update( ) {
	act( );

	_pos += _vec;
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
