NAME = cub3D

CC = cc

UNAME_S := $(shell uname -s)
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
	srcs/mlx/init_frames.c \
	srcs/mlx/texture_loader.c \
	srcs/parsing/parse_elements.c \
	srcs/parsing/parse_grid.c \
	srcs/parsing/parsing.c \
	srcs/parsing/validate_map.c \
	srcs/player/init_player.c \
	srcs/player/keypress.c \
	srcs/player/handle_movement.c \
	srcs/player/player_move.c \
	srcs/render/render.c \
	srcs/render/render_sky.c \
	srcs/render/render_draw.c \
	srcs/render/draw_shapes.c \
	srcs/render/render_minimap.c \
	srcs/render/render_texture.c \
	srcs/render/math.c \
	srcs/render/cast_ray.c \
	srcs/render/cast_ray1.c \
	srcs/render/render_tools.c \
	srcs/render/draw_line_from_texture.c \
	srcs/tools/utils.c \
	srcs/tools/error_handling.c \
	srcs/tools/error.c \
	srcs/render/render_walls.c \

SRC_OBJS = $(SRC_FILES:.c=.o)

all: $(NAME)

bonus: $(NAME)

$(NAME): $(MLX42LIB) $(SRC_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC_OBJS) -o $(NAME) -L$(DLIBFT) -l$(FT) \
		-L$(BUILD_DIR) -lmlx42 $(EXT_LIBS) $(LDFLAGS)

$(LIBFT):
	@if [ ! -d $(DLIBFT) ]; then \
		git clone https://github.com/luchic/mylibft.git $(DLIBFT); \
	fi
	@$(MAKE) -C $(DLIBFT) all


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

	@if [ -d $(DLIBFT) ]; then $(MAKE) -C $(DLIBFT) clean; fi

fclean: clean
	rm -f $(NAME)
	@if [ -d $(DLIBFT) ]; then $(MAKE) -C $(DLIBFT) fclean; fi

re: fclean all

.PHONY: all bonus clean fclean re
