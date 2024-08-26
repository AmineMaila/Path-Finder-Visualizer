#include "AlgoManager.hpp"
#include "InputManager.hpp"
#include "Screen.hpp"
#include "Map.hpp"

int main()
{
	Screen			screen;
	InputManager	in;
	Map				map;
	AlgoManager		algoManager;

	while (true)
	{
		if (algoManager.simulate)
			algoManager.execute(map);
		map.drawGrid(screen);
		screen.draw();
		in.input(map, algoManager);
	}
}