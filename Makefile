SRC = mapmap.c ft_cheminvalide.c mapverif1.c so_long.c utils.c verification.c mapverif2.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = so_long

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lbsd -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm -o $(NAME)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all
