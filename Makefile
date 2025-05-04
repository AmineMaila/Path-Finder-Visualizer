CC := g++
CFLAGS := -Wall -Werror -Wextra -O3 -I./include -std=c++11
LDFLAGS := -L./lib

ifeq ($(OS),Windows_NT) # Windows
    LDLIBS := -lSDL2_image -lSDL2main -lSDL2 -lm -luser32 -lgdi32 -lwinmm -ldxguid
    NAME := pathfinder.exe
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux) # Linux
        LDLIBS := -lSDL2_image -lSDL2 -lm -ldl -pthread
        NAME := pathfinder
    endif
    ifeq ($(UNAME_S),Darwin) # MacOS
        LDLIBS := -lSDL2_image -lSDL2 -lm -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
        NAME := pathfinder
    endif
endif

SRC := $(shell find src -name "*.cpp")
INCLUDE := $(shell find src -name "*.hpp")
OBJ_DIR := src/objects
OBJ := $(patsubst src/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

$(shell mkdir -p $(dir $(OBJ)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(OBJ_DIR)/%.o: src/%.cpp $(INCLUDE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re