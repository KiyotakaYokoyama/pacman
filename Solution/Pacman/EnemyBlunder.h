#pragma once
#include "Enemy.h"

class EnemyBlunder : public Enemy {
public:
	EnemyBlunder( const Vector& pos );
	virtual ~EnemyBlunder( );
private:
	void moving( );
	SCORE getScore( ) const;
	IMGAE_DATA getImageData( ) const;
};

