SRCS = src/main.c\
	src/free.c

SRCS += src/init/init.c\
	src/init/error_init.c\
	src/init/init_utils.c

SRCS +=	src/game/print_img.c\
	src/game/render.c\
	src/game/render_utils.c\
	src/game/dda.c\
	src/game/hook.c\
	src/game/hook_utils.c

SRCS += src/minimap/minimap.c\
	src/minimap/mm_ray.c\
	src/minimap/mm_ray_utils.c

SRCS += src/tmp_utils.c
	
OBJS_DIR = obj

OBJS = $(SRCS:src/%/%.c=$(OBJS_DIR)/%.o)

NAME = cub3d

HEADER = includes/cub3d.h\
	includes/struct.h\
	includes/keycode.h

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
	@make clean -C mlx
	rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C libft
	rm -f $(NAME)

re: fclean all