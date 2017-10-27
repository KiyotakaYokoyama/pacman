#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"

PTR( Game );
PTR( Map );
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
	MapPtr getMap( );
	PacmanConstPtr getPacman( );
private:
	MapPtr _map;
	std::array< PacmanPtr, PLAYER_NUM > _player;
	MilitaryPtr _military;
};

