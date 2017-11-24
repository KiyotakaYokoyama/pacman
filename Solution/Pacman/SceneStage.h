#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "define.h"

PTR( SceneStage );
PTR( Map );
PTR( Pacman );
PTR( Military );

class SceneStage : public Task {
public:
	static std::string getTag( ) { return "SCENESTAGE"; };
	static SceneStagePtr getTask( );
public:
	SceneStage( );
	virtual ~SceneStage( );
public:
	void initialize( );
	void update( );
	int getChipSize( ) const;
	int getCharaSize( ) const;
	MapPtr getMap( );
	PacmanConstPtr getPacman( );
private:
	int _chip_size;
	MapPtr _map;
	std::array< PacmanPtr, PLAYER_NUM > _player;
	MilitaryPtr _military;
};

