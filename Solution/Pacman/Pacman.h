#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Image );

class Pacman : public Character {
public:
	Pacman( int id, const Vector& pos );
	virtual ~Pacman( );
public:
	void draw( ) const;
private:
	void act( );
	void actOnMove( );
	void actOnEat( );
private:
	int _id;
	bool _turnaround;
	ImagePtr _sprite;
};

