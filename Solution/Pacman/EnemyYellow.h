#pragma once
#include "Enemy.h"

class EnemyYellow : public Enemy {
public:
	EnemyYellow( const Vector& pos );
	virtual ~EnemyYellow( );
public:
private:
	void moving( );
	SCORE getScore( ) const;
	IMGAE_DATA getImageData( ) const;
};

