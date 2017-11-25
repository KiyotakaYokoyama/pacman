#pragma once
#include "Task.h"
#include <string>

PTR( Viewer );

class Viewer : public Task {
public:
	static std::string getTag( ) { return "VIEWER"; };
	static ViewerPtr getTask( );
public:
	Viewer( );
	virtual ~Viewer( );
private:
	void update( );
};

