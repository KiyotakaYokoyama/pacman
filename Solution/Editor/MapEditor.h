#pragma once
#include "Task.h"
#include <string>

PTR( MapEditor );
PTR( Object );
PTR( ObjectViewer );
PTR( ObjectEditor );

class MapEditor : public Task {
public:
	static std::string getTag( ) { return "MAPEDITOR"; };
	static MapEditorPtr getTask( );
public:
	MapEditor( );
	virtual ~MapEditor( );
public:
	void initialize( );
	void update( );
private:
	enum MODE {
		MODE_EDIT,
		MODE_SAVE,
		MODE_LOAD
	};
private:
	void updateMode( );
	void modeEditing( );
	void modeSaveing( );
	void modeLoading( );
	void drawInfo( ) const;
private:
	MODE _mode;
	ObjectPtr _object;
	ObjectEditorPtr _editor;
	ObjectViewerPtr _viewer;
};

