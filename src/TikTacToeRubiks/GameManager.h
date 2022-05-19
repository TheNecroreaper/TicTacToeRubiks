#include "Common.h"
#include "RubiksCube.h"
#include <Node.hpp>

class GameManager : public Node
{
	GODOT_CLASS(GameManager, Node);

private:
	RubiksCubeTTT cube;

public:
	static void _register_methods();
	void _init();

	void renderFaces();
};

