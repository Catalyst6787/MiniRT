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
# MLX = ./minilibx-linux/libmlx.a

SRC_DIR = ./src
OBJ_DIR = ./objects

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# vpath %.c $(SRC_DIR):$(SRC_DIR)/parsing

PURPLE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@printf "$(PURPLE)Linking $(NAME)...$(RESET)\n"
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
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
