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
		DIRECTION before_dir;
		Vector pos;
		PROCEED( ) :
		up( true ),
		down( true ),
		left( true ),
		right( true ),
		before_dir( DIRECTION_START ),
		pos( Vector( ) ) {
		};
	};
private:
	bool moveUp   ( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back );
	bool moveDown ( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back );
	bool moveLeft ( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back );
	bool moveRight( PROCEED * proceed, std::vector< PROCEED > * proceeds, DIRECTION * next_dir, Vector * next_pos, bool * back );
};

