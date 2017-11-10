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
	void entryStage( const Vector& pos );
private:
	void act( );
	void actOnMove( );
	void actOnEat( );
	void actOnWarp( );
	void actOnAutoMove( );
private:
	int _id;
	bool _turnaround;
	bool _auto_move;
	Vector _auto_vec;
	ImagePtr _sprite;
};

