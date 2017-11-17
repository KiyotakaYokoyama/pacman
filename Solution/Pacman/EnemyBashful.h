#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( EnemyShadow );

class EnemyBashful : public Enemy {
public:
	EnemyBashful( const Vector& pos, EnemyShadowPtr shadow );
	virtual ~EnemyBashful( );
public:
	IMGAE_DATA getImageData( ) const;
private:
	void moving( );
	EnemyShadowPtr _shadow;
};

