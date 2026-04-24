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

MACOS_GLFW_LIB_DIR =
ifeq ($(UNAME_S),Darwin)
ifneq ($(wildcard /opt/homebrew/lib/libglfw.dylib),)
MACOS_GLFW_LIB_DIR = -L/opt/homebrew/lib
else ifneq ($(wildcard /usr/local/lib/libglfw.dylib),)
MACOS_GLFW_LIB_DIR = -L/usr/local/lib
endif
endif

EXT_LIBS = $(MACOS_GLFW_LIB_DIR) -ldl -lglfw -pthread -lm


SRC_FILES = \
	srcs/main.c \
	srcs/mlx/graphics.c \
	srcs/mlx/setup_hooks.c \
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
	srcs/render/render_frame.c \
	srcs/render/math.c \
	srcs/render/cast_ray.c \
	srcs/tools/element_handler_utils.c \
	srcs/tools/utils.c \
	srcs/tools/error_handling.c \
	srcs/validate/check_walls.c \
	srcs/validate/validate_map.c \
	srcs/render/render_walls.c \
	srcs/tools/utils.c \
	srcs/tools/error_handling.c \

SRC_OBJS = $(SRC_FILES:.c=.o)

all: $(NAME)

bonus: $(NAME)

debug: CFLAGS += -g3 -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: re

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

.PHONY: all bonus debug clean fclean re
