NAME = libbytebuffer.a
INC_DIR = incs
SRC_DIR = srcs
OBJ_DIR = objs

FILES = bytebuffer.c 

# Liste des fichiers
SRCS = $(addprefix $(SRC_DIR)/,$(FILES))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Arborescence de fichier
SRC_ALL_DIR = $(dir $(SRCS))
OBJ_ALL_DIR = $(SRC_ALL_DIR:$(SRC_DIR)%=$(OBJ_DIR)%)

IFLAGS = -I $(INC_DIR)

CC = gcc
RM = /bin/rm -f

all: build $(NAME)

build:
	@mkdir -p $(OBJ_ALL_DIR)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)
	@echo "Make $(NAME) :\033[1;32m DONE!\033[m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(IFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean : clean
	@$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re build
