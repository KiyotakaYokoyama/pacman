#pragma once
#include "Task.h"
#include <string>
#include "define.h"
#include "Scene.h"

PTR( Game );
PTR( Scene );
PTR( SceneStage );
PTR( Image );

class Game : public Task {
public:
	static std::string getTag( ) { return "GAME"; };
	static GamePtr getTask( );
public:
	Game( );
	virtual ~Game( );
public:
	int getChipSize( ) const;
	int getCharaSize( ) const;
	SceneStagePtr getStage( ) const;
private:
	void initialize( );
	void update( );
	void chengeScene( );
	void drawFade( ) const;
private:
	int _chip_size;
	int _fade_count;
	ScenePtr _scene;
	Scene::SCENE _next;
	ImagePtr _number;
	ImagePtr _player_name;
	ImagePtr _fade;
	ImagePtr _push_key;
};

