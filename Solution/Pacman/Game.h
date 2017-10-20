#pragma once
#include "Task.h"
#include <string>

PTR( Game );
PTR( Pacman );

class Game : public Task {
public:
	static std::string getTag( ) { return "GAME"; };
	static GamePtr getTask( );
public:
	Game( );
	virtual ~Game( );
public:
	void initialize( );
	void update( );
private:
	PacmanPtr _pacman;
};

