#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( Image );

class EnemyShadow : public Enemy {
public:
	EnemyShadow( const Vector& pos );
	virtual ~EnemyShadow( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
	SCORE getScore( ) const;
};

