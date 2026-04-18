NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I. -I$(MLX42)/include/MLX42 -Ilibft/includes

DLIBFT = libft
LIBFT = $(DLIBFT)/libft.a
FT = ft

MLX42 = mlx42
BUILD_DIR = $(MLX42)/build
MLX42LIB = $(BUILD_DIR)/libmlx42.a

EXT_LIBS = -ldl -lglfw -pthread -lm

SRC_FILES = \
	srcs/main.c \
	srcs/mlx/graphics.c \
	srcs/mlx/setup_hooks.c \
	srcs/mlx/texture_loader.c \
	srcs/parse/pad_map_grid.c \
	srcs/parse/pad_map_grid_utils.c \
	srcs/parse/parse_colors.c \
	srcs/parse/parse_colors_utils.c \
	srcs/parse/parse_element_utils.c \
	srcs/parse/parse_file.c \
	srcs/parse/parse_file_line.c \
	srcs/parse/parse_file_utils.c \
	srcs/parse/parse_file_utils_helpers.c \
	srcs/parse/parse_textures.c \
	srcs/parse/parsing.c \
	srcs/player/init_player.c \
	srcs/player/keypress.c \
	srcs/player/handle_movement.c \
	srcs/player/player_move.c \
	srcs/render/dda_init.c \
	srcs/render/render.c \
	srcs/render/handle_rays.c \
	srcs/render/render_dda.c \
	srcs/render/render_ceiling.c \
	srcs/render/render_draw.c \
	srcs/render/draw_shapes.c \
	srcs/render/render_floor.c \
	srcs/render/render_minimap.c \
	srcs/render/render_texture.c \
	srcs/render/render_walls.c \
	srcs/render/render_frame.c \
	srcs/render/math.c \
	srcs/render/cast_ray.c \
	srcs/tools/element_handler_utils.c \
	srcs/tools/utils.c \
	srcs/tools/error_handling.c \
	srcs/validate/check_walls.c \
	srcs/validate/validate_map.c

SRC_OBJS = $(SRC_FILES:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX42LIB) $(SRC_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $(NAME) -L$(DLIBFT) -l$(FT) \
		-L$(BUILD_DIR) -lmlx42 $(EXT_LIBS)

$(LIBFT):
	$(MAKE) -C $(DLIBFT) all

$(MLX42LIB):
	if [ ! -d $(MLX42) ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42); \
	fi
	if [ ! -f $(BUILD_DIR)/libmlx42.a ]; then \
		cmake $(MLX42) -B $(BUILD_DIR) && \
		cmake --build $(BUILD_DIR) -j4; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_OBJS)
	$(MAKE) -C $(DLIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(DLIBFT) fclean

re: fclean all

.PHONY: all bonus clean fclean re
