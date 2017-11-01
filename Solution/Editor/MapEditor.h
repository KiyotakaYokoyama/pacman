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
		MODE_LOAD,
		MODE_INIT
	};
private:
	void updateMode( );
	void modeEditing( );
	void modeSaveing( );
	void modeLoading( );
	void modeInitialize( );
	void drawInfo( ) const;
private:
	bool _init;
	MODE _mode;
	ObjectPtr _object;
	ObjectEditorPtr _editor;
	ObjectViewerPtr _viewer;
};

