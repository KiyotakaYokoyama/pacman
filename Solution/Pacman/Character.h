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
	enum DIR {
		DIR_UP,
		DIR_DOWN,
		DIR_RIGHT,
		DIR_LEFT
	};
protected:
	void setPos( const Vector& pos );
	void setVec( const Vector& vec );
	void setColl( bool coll );
	int getActTime( ) const;
	Vector getVec( ) const;
	DIR getDir( ) const;
private:
	virtual void act( ) = 0;
	void updateColl( );
	void updateDir( );
private:
	int _act_time;
	bool _coll;
	Vector _pos;
	Vector _vec;
	DIR _dir;
};

