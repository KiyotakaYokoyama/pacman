#pragma once
#include "Task.h"
#include <string>

PTR( Game );
PTR( Pacman );
PTR( Military );

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
	PacmanConstPtr getPacman( );
private:
	PacmanPtr _pacman;
	MilitaryPtr _military;
};

