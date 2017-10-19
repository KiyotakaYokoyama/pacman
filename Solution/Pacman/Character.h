#pragma once
#include "mathmatics.h"

class Character {
public:
	Character( Vector pos );
	virtual ~Character( );
public:
	void update( );
protected:
	void setVec( const Vector& vec );
	Vector getPos( ) const;
	Vector getVec( ) const;
private:
	virtual void act( ) = 0;
private:
	Vector _pos;
	Vector _vec;
};

