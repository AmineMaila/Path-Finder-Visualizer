CPP= g++

FLAGS= -Wall -Werror -Wextra -std=c++11 -O3

INCLUDES= Screen/Screen.hpp \
			Screen/Button.hpp \
			Map/Map.hpp \
			Algo/Dijkstra/Dijkstra.hpp \
			Algo/BFS/BFS.hpp \
			Algo/Astar/Astar.hpp \
			Algo/Algo.hpp \
			Utils.hpp

SRCS= main.cpp \
		Screen/Screen.cpp \
		Map/Map.cpp \
		Algo/BFS/BFS.cpp \
		Algo/Dijkstra/Dijkstra.cpp \
		Algo/Astar/Astar.cpp

SDL_INCLUDE= -I$(HOME)/local/include -I$(HOME)/local/include/SDL2
SDL_LINKER= -L$(HOME)/local/lib -lSDL2 -lSDL2_image

OBJSDIR= objects
OBJS= $(SRCS:%.cpp=$(OBJSDIR)/%.o)

NAME= PFV

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(FLAGS) $(OBJS) $(SDL_LINKER) -o $(NAME)

$(OBJSDIR)/%.o: %.cpp $(INCLUDES)
	@mkdir -p $(dir $@)
	$(CPP) $(FLAGS) $(SDL_INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJS) $(OBJSDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all