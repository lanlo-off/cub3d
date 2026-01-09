SRCS = src/main.c\
	src/error_init.c\
	src/free.c\
	src/init.c\
	src/player.c\
	src/print_img.c\
	src/wip.c\
	src/ray.c
	
OBJS_DIR = obj

OBJS = $(SRCS:src/%.c=$(OBJS_DIR)/%.o)

NAME = cub3d

HEADER = includes/cub3d.h\
	includes/struct.h

LIBFT = libft/libft.a

MLX_FLAGS = -L/usr/lib/X11 -lXext -lX11

MLX = mlx/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(LIBFT) $(OBJS) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) $(MLX_FLAGS) $(LIBFT) -lm -o $(NAME)

$(OBJS_DIR)/%.o: src/%.c $(HEADER) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

clean:
	@make clean -C libft
	@make clean -C minilibx-linux
	rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all