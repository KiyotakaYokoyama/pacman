#pragma once
#include "Enemy.h"

class EnemyShadow : public Enemy {
public:
	EnemyShadow( const Vector& pos );
	virtual ~EnemyShadow( );
private:
	void moving( );
	SCORE getScore( ) const;
	IMGAE_DATA getImageData( ) const;
};

