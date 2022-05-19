#include "Face.h"
#include <Sprite.hpp>

String xRef = "res://Assets/Sprites/X.png";
String oRef = "res://Assets/Sprites/O.png";


void Face::_register_methods()
{
}

void Face::_init()
{
	xTexture.load(xRef);
	oTexture.load(oRef);
}


void Face::setSpaces(std::array<bool, 9> spaceValues)
{
	Array spaces = get_children();
	for (int space = 0; space < 9; space++) {
		Sprite* spaceSprite = Object::cast_to<Sprite>(spaces[space]);
		spaceSprite->set_texture(&(spaceValues[space] ? xTexture: oTexture));
	}
}
