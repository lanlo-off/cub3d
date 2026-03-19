SRCS = src/main.c\
	src/free.c\
	src/free2.c\
	src/error.c\
	src/init_utils.c

SRCS += src/init/init.c\
	src/init/error_init.c\
	src/init/init_utils.c

SRCS +=	src/game/print_img.c\
	src/game/render.c\
	src/game/render_utils.c\
	src/game/dda.c\
	src/game/hook.c\
	src/game/hook_utils.c

SRCS +=	src/parsing/parser.c\
	src/parsing/check_file.c\
	src/parsing/map_utils/check_utils.c\
	src/parsing/map_utils/check_utils2.c\
	src/parsing/map_utils/get_dimensions.c\
	src/parsing/map_utils/pad_map.c \
	src/parsing/check/check_closemap.c\
	src/parsing/check/check_player.c\
	src/parsing/check/check_textures.c\
	src/parsing/check/findmap.c\
	src/parsing/check/findmap_elements.c

OBJS_DIR = obj

OBJS = $(SRCS:src/%/%.c=$(OBJS_DIR)/%.o)

NAME = cub3d

HEADER = includes/cub3d.h\
	includes/struct.h\
	includes/keycode.h

LIBFT = libft/libft.a

MLX_FLAGS = -L/usr/lib/X11 -lXext -lX11 #-L/opt/X11/lib

MLX = mlx/libmlx.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3 #-I/opt/X11/include

all: $(NAME)

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(NAME): $(LIBFT) $(OBJS) $(MLX) $(HEADER)
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