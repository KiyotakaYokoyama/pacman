#pragma once
#include "Enemy.h"

class EnemySpeedy : public Enemy {
public:
	EnemySpeedy( const Vector& pos );
	virtual ~EnemySpeedy( );
private:
	void act( );
};

