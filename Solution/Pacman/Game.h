#pragma once
#include "Task.h"
#include <string>
#include <array>
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
	void addScore( PLAYER idx, int score );
	int getGameTime( ) const;
	SCENE getNowScene( ) const;
private:
	void initialize( );
	void update( );
private:
	int _time;
	std::array< int, MAX_PLAYER > _score;
	SCENE _scene;
	ImagePtr _number;
	ImagePtr _player_name;
};

