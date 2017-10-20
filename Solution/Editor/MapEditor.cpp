#include "MapEditor.h"
#include "Application.h"
#include "Keyboard.h"
#include "Drawer.h"
#include "Image.h"
#include "ImageTarget.h"

#include "define.h"
#include "Object.h"
#include "ObjectEditor.h"
#include "ObjectViewer.h"

const std::string DIRECTORY = "Resource/MapData/";

MapEditorPtr MapEditor::getTask( ) {
	return std::dynamic_pointer_cast< MapEditor >( Application::getInstance( )->getTask( getTag( ) ) );
}

MapEditor::MapEditor( ) :
_mode( MODE_EDIT ) {
}

MapEditor::~MapEditor( ) {
}

void MapEditor::initialize( ) {
	_object = ObjectPtr( new Object );
	_editor = ObjectEditorPtr( new ObjectEditor( _object ) );
	_viewer = ObjectViewerPtr( new ObjectViewer( _object ) );
}

void MapEditor::update( ) {
	Drawer::getTask( )->flip( );
	updateMode( );
	drawInfo( );
	switch ( _mode ) {
	case MODE_EDIT:
		modeEditing( );
		break;
	case MODE_SAVE:
		modeSaveing( );
		_mode = MODE_EDIT;
		break;
	case MODE_LOAD:
		modeLoading( );
		_mode = MODE_EDIT;
		break;
	}
}

void MapEditor::drawInfo( ) const {
	DrawerPtr drawer = Drawer::getTask( );
	switch ( _mode ) {
	case MODE_EDIT:
		{
			std::string str = "編集中：";
			switch ( _editor->getMode( ) ) {
			case ObjectEditor::MODE_NONE:		  str += "削除\n"; break;
			case ObjectEditor::MODE_WALL:		  str += "壁\n"; break;
			case ObjectEditor::MODE_FEED:		  str += "餌\n"; break;
			case ObjectEditor::MODE_ENHANCE_FEET: str += "パワーアップアイテム\n"; break;
			}
			str += "1:削除\n";
			str += "2:壁\n";
			str += "3:餌\n";
			str += "4:パワーアップアイテム";
			drawer->drawString( 0, 10, str.c_str( ) );
		}
		break;
	case MODE_SAVE:
		drawer->drawString( 0, 10, "セーブ\nfilename" );
		break;
	case MODE_LOAD:
		drawer->drawString( 0, 10, "ロード\nfilename" );
		break;
	}
}

void MapEditor::updateMode( ) {
	KeyboardPtr key = Keyboard::getTask( );
	if ( key->isPushKey( "F2" ) ) {
		_mode = MODE_SAVE;
	}
	if ( key->isPushKey( "F3" ) ) {
		_mode = MODE_LOAD;
	}
}

void MapEditor::modeEditing( ) {
	_editor->update( );
	_viewer->draw( );
	_editor->drawCursor( );
}

void MapEditor::modeSaveing( ) {
	std::string filename = Application::getInstance( )->inputString( 80, 30 );
	if ( filename.size( ) == 0 ) {
		return;
	}

	_object->save( DIRECTORY, filename );
	ImageTargetPtr stage = _viewer->getStageSprite( );
	std::string image_name = filename;
	int pos = image_name.find( "." );
	if ( pos != std::string::npos ) {
		image_name.erase( pos );
	}
	image_name += "_stage";
	stage->save( DIRECTORY + image_name );
}

void MapEditor::modeLoading( ) {
	std::string filename = Application::getInstance( )->inputString( 80, 30 );
	if ( filename.size( ) == 0 ) {
		return;
	}

	_object->load( DIRECTORY, filename );
}
