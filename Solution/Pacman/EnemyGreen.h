#pragma once
#include "Enemy.h"

class EnemyGreen : public Enemy {
public:
	EnemyGreen( const Vector& pos );
	virtual ~EnemyGreen( );
private:
	void moving( );
	SCORE getScore( ) const;
	IMGAE_DATA getImageData( ) const;
};

