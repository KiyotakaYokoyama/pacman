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
	void drawStageing( const int time, const int max_time ) const;
	void entryStage( const Vector& pos );
	void damage( );
	bool isTurnaround( ) const;
	bool isDamaging( ) const;
private:
	void act( );
	void actOnMove( );
	void actOnEat( );
	void actOnWarp( );
	void actOnAutoMove( );
private:
	int _id;
	int _damage;
	bool _turnaround;
	bool _auto_move;
	Vector _auto_vec;
	ImagePtr _sprite;
};

