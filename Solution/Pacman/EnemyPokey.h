#pragma once
#include "Enemy.h"

class EnemyPokey : public Enemy {
public:
	EnemyPokey( const Vector& pos );
	virtual ~EnemyPokey( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
};

