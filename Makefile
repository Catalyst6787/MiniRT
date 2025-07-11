# .SILENT:

NAME = miniRT
UNAME = $(shell uname -s)

CC = gcc

ifeq ($(UNAME), Linux)
	CFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -I ./libft/includes -I ./minilibx-linux -I ./includes -g # -O2 -march=native -ffast-math -funroll-loops
	LDFLAGS = -L ./libft -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm
	MLX = ./minilibx-linux/libmlx.a
endif
ifeq ($(UNAME), Darwin)
    CFLAGS = -Wall -Wextra -Werror -I ./libft/includes -I ./mlx_macos -I ./includes -g -fsanitize=address # Added -g for debugging, remove later
    LDFLAGS = -L ./libft -lft -L ./mlx_macos -lmlx -framework OpenGL -framework AppKit
	MLX = ./mlx_macos/libmlx.a
endif

RM = rm -f


LIBFT = ./libft/libft.a

SRC_DIR = ./src
OBJ_DIR = ./objects

SRC					=	main.c \
						parser.c parsing_scene_allocation.c parse_camera_light.c parse_shapes.c \
						set_buffer.c \
						checks_data.c checks_format1.c checks_format2.c parsing_utils.c \
						transform_objects.c set_objects_material.c create_objects_from_shapes.c \
						fill_intersection_table.c \
						debug.c \
						double_utils.c \
						events.c events_camera_light.c event_obj_positions.c events_fun.c \
						print_data.c \
						exit.c \
						get_debug_fd.c \
						init.c \
						print_debug.c \
						rays.c \
						render.c \
						display_image.c \
						normals.c \
						lighting.c \
						intersections.c \
						sort_inter.c \
						special_scenes.c \
						render_utils.c \
						shadows.c \
						create_shapes.c \
						material.c \
						new_elements.c \
						matrices_inversions.c  matrices_multiplications.c matrices_rotations.c matrices_scaling.c \
						matrices_translations.c matrices_transpositions.c  matrices_utils.c matrices_shearing.c \
						matrices_orientations.c \
						transformations.c \
						utils.c \
						color_operations.c \
						free_utils.c \
						vec3_basic_op.c vec3_complex_operations.c \
						tests.c tests_color.c tests_matrices.c tests_rays.c \
						test_intersections.c test_normals.c test_reflections.c \
						test_lighting.c test_world.c test_shadows.c test_camera.c \
						tests_planes.c tests_cylinders.c tests_cones.c \

SRC_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

vpath %.c $(SRC_DIR):$(SRC_DIR)/parsing
vpath %.c $(SRC_DIR):$(SRC_DIR)/vec3
vpath %.c $(SRC_DIR):$(SRC_DIR)/debug
vpath %.c $(SRC_DIR):$(SRC_DIR)/rays
vpath %.c $(SRC_DIR):$(SRC_DIR)/tests
vpath %.c $(SRC_DIR):$(SRC_DIR)/colors
vpath %.c $(SRC_DIR):$(SRC_DIR)/matrices

PURPLE = \033[0;34m
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)
	@printf "$(GREEN)Compilation OK!$(RESET)\n"

$(NAME): $(SRC_OBJ) $(LIBFT) $(MLX)
	@printf "$(PURPLE)Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) $(SRC_OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/parsing/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/vec3/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/debug/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/rays/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/tests/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/colors/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/matrices/%.c | $(OBJ_DIR)
	@printf "$(PURPLE)Compiling $<...$(RESET)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@$(MAKE) -C ./libft

$(MLX):
	@$(MAKE) -C ./minilibx-linux

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	$(RM) $(OBJ_DIR)/*.o
	@$(MAKE) -C ./libft clean
	@$(MAKE) -C ./minilibx-linux clean

fclean: clean
	@printf "$(RED)Removing executables and objects directory...$(RESET)\n"
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)
	@$(MAKE) -C ./libft fclean

re: fclean all

valgrind: all
	@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./$(NAME)

run: all
	@./$(NAME)

norm:
	@norminette ./src ./includes ./libft

.PHONY: all clean fclean re
