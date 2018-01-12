#pragma once
#include "smart_ptr.h"
#include <list>

PTR( Image );
PTR( Enemy );

class Military {
public:
	Military( );
	virtual ~Military( );
public:
	void update( );
	void draw( ) const;
	void addEnemy( EnemyPtr enemy );
	void clearEnemy( );
private:
	ImagePtr _image;
	std::list< EnemyPtr > _enemies;
};

