#pragma once
#include "Character.h"
#include "define.h"
#include <vector>

class Enemy : public Character {
public:
	Enemy( const Vector& pos );
	virtual ~Enemy( );
public:
	virtual IMGAE_DATA getImageData( ) const = 0;
protected:
	void moveGoal( const Vector goal );
	Vector AStar(  const Vector& goal );
private:
	enum STATE {
		STATE_NONE,
		STATE_OPEN,
		STATE_COLSE
	};
	struct PROCEED {
		Vector pos;
		STATE state;
		int cost;
		int heristic;
		int score;

		PROCEED( ) :
		pos( Vector( ) ),
		state( STATE_NONE ),
		cost( -1 ),
		heristic( -1 ) {
		};

		inline void setScore( ) {
			score = cost + heristic;
		}
	};
private:
	void act( );
	void checkGoal( );
	virtual void moving( ) = 0;
private:
	bool _auto_move;
	Vector _goal_pos;
};

