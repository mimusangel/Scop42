NAME = Scop
INC_DIR = includes
SRC_DIR = sources
OBJ_DIR = objs

FILES = scop.c

# Liste des fichiers
SRCS = $(addprefix $(SRC_DIR)/,$(FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Arborescence de fichier
SRC_ALL_DIR = $(dir $(SRCS))
OBJ_ALL_DIR = $(SRC_ALL_DIR:$(SRC_DIR)%=$(OBJ_DIR)%)

IFLAGS = -I $(INC_DIR) -I./lib/fnl/incs/
LIBFLAGS = -lglfw -lGLEW -lm
LIBFLAGS += -L./lib/fnl/ -lfnl
LIBFLAGS += -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
CC = gcc
RM = /bin/rm -f

all: build lib-all $(NAME)

build:
	@mkdir -p $(OBJ_ALL_DIR)

lib-all:
	@$(MAKE) -C./lib/fnl/ all

lib-clean:
	@$(MAKE) -C./lib/fnl/ clean

lib-fclean:
	@$(MAKE) -C./lib/fnl/ fclean

lib-re:
	@$(MAKE) -C./lib/fnl/ re

install:
	@brew install glfw
	@brew switch glfw 3.2.1
	@brew install glew
	@brew switch glew 2.1.0
	@echo "Make install :\033[1;32m DONE!\033[m"

$(NAME) : $(OBJS)
	@echo "Make Objects :\033[1;32m DONE!\033[m"
	$(CC) -o $@ $^ $(LIBFLAGS)
	@echo "Make $(NAME) :\033[1;32m DONE!\033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(IFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)
	@echo "Make clean :\033[1;31m DONE!\033[m"

fclean : clean
	@$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	@echo "Make fclean :\033[1;31m DONE!\033[m"

re: fclean all

.PHONY: all clean fclean re build install lib
