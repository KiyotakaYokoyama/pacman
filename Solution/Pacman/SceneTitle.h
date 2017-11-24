#pragma once
#include "Task.h"
#include <string>

PTR( SceneTitle );
PTR( Image );

class SceneTitle : public Task {
public:
	static std::string getTag( ) { return "SCENETITLE"; };
	static SceneTitlePtr getTask( );
public:
	SceneTitle( );
	virtual ~SceneTitle( );
public:
	void initialize( );
	void update( );
private:
	void checkKey( );
private:
	ImagePtr _title;
};
