# Pathfinder Visualizer

A visualization tool for popular pathfinding algorithms including A*, Dijkstra, and BFS.

## Features

- Interactive grid-based visualization
- Multiple pathfinding algorithms:
  - A* (A-Star) algorithm
  - Breadth-First Search (BFS)
  - Dijkstra's algorithm
- Wall placement to create obstacles
- Reset functionality

## Prerequisites

None! This project includes all necessary libraries (SDL2 and SDL2_image) pre-compiled and ready to use.

## Building the Project

```bash
git clone https://github.com/yourusername/pathfinder.git
cd pathfinder

make

./pathfinder
```

## Usage

To set the START node hover over a Tile and press <kbd>s</kbd>.

To set the END node hover over a Tile and press <kbd>e</kbd>.

To set the WALL node hover over a Tile and click **Left Mouse Button**.

## Project Structure

```
pathfinder/
├── include/       # SDL2 and SDL2_image headers
├── lib/           # Pre-compiled static libraries
└── src/           # Source code
    ├── Algo/      # Pathfinding algorithms
    │   ├── Astar/
    │   ├── BFS/
    │   └── Dijkstra/
    ├── Buttons/   # UI button resources
    ├── Map/       # Grid and map representation
    ├── Screen/    # Rendering and UI
    └── main.cpp   # Main entry point
```

## How It Works

The visualization shows how different pathfinding algorithms traverse a grid to find the shortest path:

- **A*** - Uses a heuristic to find the shortest path efficiently
- **Dijkstra** - Explores all possible paths to find the shortest one
- **BFS** - Explores the grid level by level

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/AmineMaila/Path-Finder-Visualizer/tree/master?tab=MIT-1-ov-file) file for details

## Acknowledgments

- SDL2 and SDL2_image libraries
