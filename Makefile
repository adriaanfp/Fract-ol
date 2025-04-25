NAME	= fractol

SRC	= src/main.c src/mandelbrot.c src/colors.c src/utils.c src/julia.c
OBJS	= $(SRC:.c=.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g
MLX		= -Lminilibx-linux -lmlx -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re