#pragma once
#include "Enemy.h"

class EnemyYellow : public Enemy {
public:
	EnemyYellow( const Vector& pos );
	virtual ~EnemyYellow( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
};

