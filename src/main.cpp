#include "Screen/Button.hpp"
#include "Screen/Screen.hpp"
#include "Map/Map.hpp"
#include "Utils.hpp"

int main()
{
	Screen			screen;
	Map				map;

	while (true)
	{
		if (screen.simulate)
			screen.run(map);
		map.drawGrid(screen);
		screen.draw();
		screen.input(map);
	}
}