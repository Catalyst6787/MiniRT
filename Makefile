# .SILENT:

NAME = miniRT
UNAME = $(shell uname -s)

CC = gcc

ifeq ($(UNAME), Linux)
	CFLAGS = -Wall -Wextra -Werror -Wpedantic -pedantic-errors -I ./libft/includes -I ./minilibx-linux -I ./includes -g # remove -g when done debbuging
	LDFLAGS = -L ./libft -lft -L ./minilibx-linux -lmlx -lXext -lX11 -lm
	MLX = ./minilibx-linux/libmlx.a
endif
ifeq ($(UNAME), Darwin)
    CFLAGS = -Wall -Wextra -Werror -I ./libft/includes -I ./mlx_macos -I ./includes -g # Added -g for debugging, remove later
    LDFLAGS = -L ./libft -lft -L ./mlx_macos -lmlx -framework OpenGL -framework AppKit
	MLX = ./mlx_macos/libmlx.a
endif

RM = rm -f


LIBFT = ./libft/libft.a

SRC_DIR = ./src
OBJ_DIR = ./objects

SRC					=	main.c \
						parser.c parsing_scene_allocation.c parse_camera_light.c parse_shapes.c \
						checks_data.c checks_format1.c checks_format2.c parsing_utils.c \
						debug.c \
						double_utils.c \
						events.c \
						print_data.c \
						exit.c \
						get_debug_fd.c \
						init.c \
						print_debug.c \
						ray_stack.c \
						ray_operations.c \
						render.c \
						render_utils.c \
						sphere.c \
						matrices_utils.c matrices_multiplications.c \
						utils.c \
						color_operations.c \
						free_utils.c \
						vec3_basic_op.c vec3_complex_operations.c \
						vec3_utils.c \
						tests.c tests_color.c tests_matrices.c \

SRC_OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

vpath %.c $(SRC_DIR):$(SRC_DIR)/parsing
vpath %.c $(SRC_DIR):$(SRC_DIR)/vec3
vpath %.c $(SRC_DIR):$(SRC_DIR)/debug
vpath %.c $(SRC_DIR):$(SRC_DIR)/rays
vpath %.c $(SRC_DIR):$(SRC_DIR)/tests
vpath %.c $(SRC_DIR):$(SRC_DIR)/colors

PURPLE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

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
