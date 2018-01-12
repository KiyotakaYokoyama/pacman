#pragma once
#include "Enemy.h"

class EnemyPurple : public Enemy {
public:
	EnemyPurple( const Vector& pos );
	virtual ~EnemyPurple( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
	SCORE getScore( ) const;
private:
	int _move_count;
	DIR _dir;
};

