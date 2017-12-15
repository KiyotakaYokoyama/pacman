#pragma once
#include "Enemy.h"

class EnemyGreen : public Enemy {
public:
	EnemyGreen( const Vector& pos );
	virtual ~EnemyGreen( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
};

