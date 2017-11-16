#pragma once
#include "Enemy.h"

class EnemySpeedy : public Enemy {
public:
	EnemySpeedy( const Vector& pos );
	virtual ~EnemySpeedy( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
};

