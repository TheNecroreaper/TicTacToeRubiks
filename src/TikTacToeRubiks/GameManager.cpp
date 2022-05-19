#include "GameManager.h"
#include "Face.h"

void GameManager::_register_methods()
{
}

void GameManager::_init()
{
	renderFaces();
}

void GameManager::renderFaces()
{
	Array faces = get_children();
	for (int face = 0; face < 6; face++) {
		Face* faceRef = Object::cast_to<Face>(faces[face]);
		faceRef->setSpaces(cube.getFace(face));
	}
}
