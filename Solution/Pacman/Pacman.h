#pragma once
#include "Character.h"
#include "smart_ptr.h"
#include <array>

PTR( Image );

class Pacman : public Character {
public:
	Pacman( Vector pos );
	virtual ~Pacman( );
public:
	void draw( ) const;
private:
	void act( );
	void actOnMove( );
	void actOnEat( );
protected:
	enum KEY {
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
	};
protected:
	void setKey( KEY key );
private:
	virtual void updateKey( ) = 0;
private:
	bool _turnaround;
	ImagePtr _sprite;
	static const int KEY_NUM = 4;
	std::array< bool, KEY_NUM > _key;
};

