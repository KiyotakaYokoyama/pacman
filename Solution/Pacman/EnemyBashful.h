#pragma once
#include "Enemy.h"
#include "smart_ptr.h"

PTR( EnemyShadow );

class EnemyBashful : public Enemy {
public:
	EnemyBashful( const Vector& pos, EnemyShadowPtr shadow );
	virtual ~EnemyBashful( );
private:
	void moving( );
	SCORE getScore( ) const;
	IMGAE_DATA getImageData( ) const;
private:
	EnemyShadowPtr _shadow;
};

