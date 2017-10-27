#pragma once
#include "Pacman.h"

class Player1 : public Pacman {
public:
	Player1( const Vector& pos );
	virtual ~Player1( );
private:
	void updateKey( );
};

