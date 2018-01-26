#pragma once
#include "Scene.h"
#include <array>
#include "mathmatics.h"
#include "smart_ptr.h"
#include "define.h"

PTR( Map );
PTR( Pacman );
PTR( Military );
PTR( Score );
PTR( Image );

class SceneStage : public Scene {
public:
	SceneStage( ImagePtr number, ImagePtr player_name, int stage_num = 0 );
	virtual ~SceneStage( );
public:
	MapPtr getMap( );
	PacmanPtr getPacman( PLAYER idx ) const;
	PacmanPtr getPacman( Vector pos ) const;
	RESULT getWinner( ) const;
	void addScore( PLAYER idx, SCORE score );
private:
	SCENE update( );
	void draw( ) const;
	void updateBattle( );
	void drawStageing( ) const;
	bool isStaging( ) const;
private:
	int _staging_time;
	MapPtr _map;
	MilitaryPtr _military;
	ScorePtr _score;
	std::array< PacmanPtr, MAX_PLAYER > _player;
};

