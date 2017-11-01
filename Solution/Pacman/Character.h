#pragma once
#include "mathmatics.h"

class Character {
public:
	Character( Vector pos, bool coll = true );
	virtual ~Character( );
public:
	void update( );
	Vector getPos( ) const;
protected:
	void setPos( const Vector& pos );
	void setVec( const Vector& vec );
	void setColl( bool coll );
	int getActTime( ) const;
	Vector getVec( ) const;
private:
	virtual void act( ) = 0;
	void updateColl( );
private:
	int _act_time;
	bool _coll;
	Vector _pos;
	Vector _vec;
};

