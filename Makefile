NAME		= fractol

SRC		= src/main.c src/mandelbrot.c src/colors.c src/utils.c \
		  src/julia.c src/utils2.c src/utils3.c src/init.c src/checkerrors.c \
		  src/checkerrors2.c

OBJS		= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g

MLX			= -Lminilibx-linux -lmlx -lX11 -lXext

LIBFT_DIR	= libft

LIBFT		= $(LIBFT_DIR)/libft.a

LIBFT_OBJS	= $(LIBFT_DIR)/*.o

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re