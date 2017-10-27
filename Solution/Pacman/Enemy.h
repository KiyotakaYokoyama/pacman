#pragma once
#include "Character.h"
#include "define.h"

class Enemy : public Character {
public:
	Enemy( const Vector& pos );
	virtual ~Enemy( );
public:
	virtual IMGAE_DATA getImageData( ) const = 0;
};

