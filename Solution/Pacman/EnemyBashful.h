#pragma once
#include "Enemy.h"

class EnemyBashful : public Enemy {
public:
	EnemyBashful( const Vector& pos );
	virtual ~EnemyBashful( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
};

