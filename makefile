# hello
### https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html ###

CC := gcc
CFLAGS := -Wall -Wextra -g
MAIN := demo

VPATH := src:src/*.c

OBJ_DIR := obj
_OBJS := main.o
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(_OBJS) )

.PHONY:	depend clean

all: $(MAIN)
	@echo \`$(MAIN)\' hath compiled

$(MAIN): $(OBJS)
	eval $(CC) $(CFLAGS) $$(pkg-config --libs --cflags raylib) $(OBJS) -o $(MAIN)

#eval cc yourgame.c $(pkg-config --libs --cflags raylib) -o YourGame

$(OBJ_DIR)/%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@


clean:
	$(RM) $(OBJ_DIR)/*.o *~
