#pragma once
#include "smart_ptr.h"

PTR( Image );

class Map {
public:
	Map( );
	virtual ~Map( );
public:
	void update( );
private:
	ImagePtr _stage;
};

