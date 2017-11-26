#pragma once
#include "Task.h"
#include <string>

PTR( SceneResult );
PTR( Image );

class SceneResult : public Task {
public:
	static std::string getTag( ) { return "SCENERESULT"; };
	static SceneResultPtr getTask( );
public:
	SceneResult( );
	virtual ~SceneResult( );
public:
	void draw( ) const;
	void setNumberImage( ImagePtr image );
private:
	void update( );
private:
	ImagePtr _number;
};

