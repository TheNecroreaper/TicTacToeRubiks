#include "Common.h"
#include <Node2D.hpp>
#include <array>
#include <Array.hpp>
#include <ImageTexture.hpp>

class Face : public Node2D
{
	GODOT_CLASS(Face, Node2D)

private:
	std::array<bool, 9> spaceValues;
	ImageTexture xTexture;
	ImageTexture oTexture;
	

public:
	static void _register_methods();
	void _init();

	void setSpaces(std::array<bool, 9> spaceValues);
};

