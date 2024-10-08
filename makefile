# hello
### https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html ###

CC := g++
CFLAGS :=  -Wall -Wextra -g
INCLUDES := -I/opt/homebrew/Cellar/sfml/2.6.1/include/
LFLAGS := -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system
MAIN := demo

VPATH := src:src/*.cpp

OBJ_DIR := obj
_OBJS := main.o
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(_OBJS) )

.PHONY:	depend clean

all: $(MAIN)
	@echo \`$(MAIN)\' hath compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(MAIN) $(LFLAGS)

$(OBJ_DIR)/%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) $(OBJ_DIR)/*.o *~
