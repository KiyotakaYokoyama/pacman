#pragma once
#include "Character.h"
#include "define.h"

class Enemy : public Character {
public:
	Enemy( const Vector& pos );
	virtual ~Enemy( );
public:
	virtual IMGAE_DATA getImageData( ) const = 0;
protected:
	Vector getVecToGoal( const Vector& start, const Vector& goal );
private:
	enum DIRECTION {
		DIRECTION_UP,
		DIRECTION_DOWN,
		DIRECTION_LEFT,
		DIRECTION_RIGHT,
		DIRECTION_START
	};
	struct PROCEED {
		bool up;
		bool down;
		bool left;
		bool right;
		DIRECTION dir;
		Vector pos;
		PROCEED( ) :
		up( true ),
		down( true ),
		left( true ),
		right( true ),
		dir( DIRECTION_UP ),
		pos( Vector( ) ) {
		};
	};
};

