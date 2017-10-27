#pragma once
#include "mathmatics.h"

class Character {
public:
	Character( Vector pos );
	virtual ~Character( );
public:
	void update( );
	Vector getPos( ) const;
protected:
	void setVec( const Vector& vec );
	int getActTime( ) const;
	Vector getVec( ) const;
private:
	virtual void act( ) = 0;
	void updateColl( );
private:
	int _act_time;
	Vector _pos;
	Vector _vec;
};

