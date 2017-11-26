#include "SceneResult.h"
#include "Application.h"
#include "Image.h"

SceneResultPtr SceneResult::getTask( ) {
	return std::dynamic_pointer_cast< SceneResult >( Application::getInstance( )->getTask( getTag( ) ) );
}

SceneResult::SceneResult( ) {
}

SceneResult::~SceneResult( ) {
}

void SceneResult::update( ) {
}

void SceneResult::draw( ) const {
}

void SceneResult::setNumberImage( ImagePtr image ) {
	_number = image;
}
