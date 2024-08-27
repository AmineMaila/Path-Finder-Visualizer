CPP= g++

FLAGS= -Wall -Werror -Wextra -std=c++11 -g -g3

INCLUDES= ./Screen.hpp ./Map.hpp InputManager.hpp Dijkstra.hpp BFS.hpp Algo.hpp AlgoManager.hpp Astar.hpp

SDL_LINKER= -framework SDL2

SDL= -F/Users/mmaila/Library/Frameworks

SRCS= main.cpp Screen.cpp Map.cpp InputManager.cpp BFS.cpp Dijkstra.cpp Astar.cpp

OBJSDIR= objects

OBJS= $(SRCS:%.cpp=$(OBJSDIR)/%.o)

NAME= PFV

all : $(NAME)

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) $(SDL) $(SDL_LINKER) $(OBJS) -o $(NAME)

$(OBJSDIR)/%.o : %.cpp $(INCLUDES)
	@mkdir -p $(OBJSDIR)
	$(CPP) $(FLAGS) $(SDL) -c $< -o $@

clean : 
	rm -rf  $(OBJS) $(OBJSDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all