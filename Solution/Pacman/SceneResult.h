#pragma once
#include "Task.h"
#include <string>
#include <array>

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
	void initialize( );
	void update( );
private:
	int _count;
	ImagePtr _number;
	std::array< ImagePtr, 45 > _cracker;
};

