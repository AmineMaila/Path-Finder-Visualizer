#include "Includes/Button.hpp"
#include "Includes/Screen.hpp"
#include "Includes/Map.hpp"

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