#pragma once
#include "Task.h"
#include <string>
#include <array>
#include "mathmatics.h"
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
	void draw( ) const;
	int getChipSize( ) const;
	int getCharaSize( ) const;
	MapPtr getMap( );
	PacmanConstPtr getPacman( PLAYER idx );
	PacmanConstPtr getPacman( Vector pos );
private:
	void initialize( );
	void update( );
	void updateBattle( );
	void drawStageing( ) const;
private:
	int _chip_size;
	MapPtr _map;
	std::array< PacmanPtr, MAX_PLAYER > _player;
	MilitaryPtr _military;
};

