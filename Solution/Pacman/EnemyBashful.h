#pragma once
#include "Enemy.h"

class EnemyBashful : public Enemy {
public:
	EnemyBashful( const Vector& pos );
	virtual ~EnemyBashful( );
private:
	void act( );
};

