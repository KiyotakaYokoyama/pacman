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
	virtual SCORE getScore( ) const = 0;
protected:
	void moveGoal( const Vector goal );
	Vector getCharaSize( ) const;
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
	virtual void moving( ) = 0;
	void adjustVec( );
	void decisionMoveDir( );
	Vector toStraight( const Vector& start, const Vector& goal );
	Vector AStar(  const Vector& goal );
};

