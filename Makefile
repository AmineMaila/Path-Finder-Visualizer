CPP= g++

FLAGS= -Wall -Werror -Wextra -std=c++11

INCLUDES= ./Includes/Screen.hpp ./Includes/Map.hpp ./Includes/Dijkstra.hpp ./Includes/BFS.hpp ./Includes/Algo.hpp ./Includes/Astar.hpp ./Includes/Button.hpp ./Includes/utils.hpp

SDL_LINKER= -framework SDL2 -framework SDL2_image

SDL= -F/Users/mmaila/Library/Frameworks

SRCS= main.cpp Screen.cpp Map.cpp BFS.cpp Dijkstra.cpp Astar.cpp

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