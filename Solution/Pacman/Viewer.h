#pragma once
#include "Task.h"
#include <string>

PTR( Viewer );

class Viewer : public Task {
public:
public:
	Viewer( );
	virtual ~Viewer( );
private:
	void update( );
};

