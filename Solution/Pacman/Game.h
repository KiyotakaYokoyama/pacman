#pragma once
#include "Task.h"
#include <string>
#include <array>
#include <vector>
#include "define.h"

PTR( Game );
PTR( Image );

class Game : public Task {
public:
	static std::string getTag( ) { return "GAME"; };
	static GamePtr getTask( );
public:
	Game( );
	virtual ~Game( );
public:
	enum SCENE {
		SCENE_TITLE,
		SCENE_STAGE,
		SCENE_RESULT,
	};
public:
	void draw( ) const;
	void setNextScene( SCENE scene );
	void addScore( PLAYER idx, SCORE score );
	int getGameTime( ) const;
	int getStageingTime( ) const;
	int getMaxStageingTime( ) const;
	bool isStaging( ) const;
	SCENE getNowScene( ) const;
private:
	struct SCORE_EFFECT {
		int time;
		PLAYER player;
		SCORE score;

		SCORE_EFFECT( );
		SCORE_EFFECT( int time_, PLAYER player_, SCORE score_ );
	};
private:
	void initialize( );
	void update( );
	void drawScoreEffet( ) const;
private:
	int _battle_time;
	int _staging_time;
	std::array< int, MAX_PLAYER > _score;
	std::vector< SCORE_EFFECT > _s_effects;
	SCENE _scene;
	ImagePtr _number;
	ImagePtr _player_name;
};

