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
	void setActCount( int count );
	int getActTime( ) const;
	bool isBumped( ) const;
	Vector getVec( ) const;
	DIR getDir( ) const;
private:
	virtual void act( ) = 0;
	void updateColl( );
	void updateDir( );
private:
	int _act_count;
	bool _coll;
	bool _bumped;
	Vector _pos;
	Vector _vec;
	DIR _dir;
};

