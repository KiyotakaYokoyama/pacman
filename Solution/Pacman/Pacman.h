#pragma once
#include "Character.h"
#include "smart_ptr.h"

PTR( Image );

class Pacman : public Character {
public:
	Pacman( Vector pos );
	virtual ~Pacman( );
private:
	void act( );
	void actOnMove( );
	void draw( ) const;
private:
	ImagePtr _sprite;
};

