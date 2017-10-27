#pragma once
#include "smart_ptr.h"
#include <list>

PTR( Image );
PTR( Military );
PTR( Enemy );

class Military {
public:
	Military( );
	virtual ~Military( );
public:
	void update( );
	void draw( ) const;
	void addEnemy( EnemyPtr enemy );
private:
	ImagePtr _image;
	std::list< EnemyPtr > _enemies;
};

