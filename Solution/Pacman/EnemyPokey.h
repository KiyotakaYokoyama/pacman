#pragma once
#include "Enemy.h"

class EnemyPokey : public Enemy {
public:
	EnemyPokey( const Vector& pos );
	virtual ~EnemyPokey( );
private:
	void act( );
};

