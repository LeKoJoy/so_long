# Paths
LIBFT_DIR = ./ft_libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

# Minilibx flags
MLX = -lmlx -lXext -lX11 -lm

# Source files
SRCS = so_long.c checkmap.c check_flood_fill.c mlx_init.c hooks.c
OBJS = $(SRCS:.c=.o)

# Executable name
NAME = so_long

# Compilation settings
CC = cc
CFLAGS = -Wall -Wextra -Werror $(LIBFT_INC)

# Default target
all: $(LIBFT) $(NAME)

# Compile .c files to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile so_long and link with libft + minilibx
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

# Compile libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

.PHONY: all clean fclean re

