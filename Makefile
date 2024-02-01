#MAKEFLAGS += --silent

CC = gcc
CFLAGS = -g#-Wall -Wextra -Werror -Wpedantic 
INC_DIR = inc/

EXE = ft_malloc

SRC_DIR = src/
SRC =	malloc.c\
		free.c

LIBRARY_DIR = ./

LIBFT_DIR = $(LIBRARY_DIR)libft/
LIBFT_INC_DIR = $(LIBFT_DIR)includes/
LIBFT_INC = -I $(LIBFT_INC_DIR) $(LIBFT_DIR)libft.a

OBJ_DIR = .obj/
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

.PHONY : all clean fclean re $(LIBFT_DIR) $(EXE) launch

all: $(LIBFT_DIR) $(EXE) launch

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_INC) -o $(EXE)

$(LIBFT_DIR):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(addprefix $(INC_DIR),$(INC))
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(LIBFT_INC_DIR) -I $(INC_DIR)

clean:
	/bin/rm -rf *.o
	$(MAKE) -C $(LIBFT_DIR) fclean

fclean: clean
	/bin/rm -f $(EXE)

re: 
	$(MAKE) fclean
	$(MAKE) all

launch:
	./$(EXE)