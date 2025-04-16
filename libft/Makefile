# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfaure <lfaure@student.42lausanne.ch>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 16:03:02 by lfaure            #+#    #+#              #
#    Updated: 2025/04/16 18:56:04 by lfaure           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PATH_SRCS = ./libft_src
GNL_PATH = ./gnl_src
PRINTF_PATH = ./printf_src
HEADER = ./includes
OBJ_PATH = ./obj

FLAG = -Wall -Wextra -Werror
OPTION = -c -I $(HEADER)

SRCS = \
		$(PATH_SRCS)/ft_isalpha.c $(PATH_SRCS)/ft_isdigit.c $(PATH_SRCS)/ft_isalnum.c $(PATH_SRCS)/ft_isascii.c \
		$(PATH_SRCS)/ft_isprint.c $(PATH_SRCS)/ft_strlen.c $(PATH_SRCS)/ft_memset.c $(PATH_SRCS)/ft_bzero.c \
		$(PATH_SRCS)/ft_memcpy.c $(PATH_SRCS)/ft_strlcpy.c $(PATH_SRCS)/ft_memmove.c $(PATH_SRCS)/ft_strlcat.c \
		$(PATH_SRCS)/ft_toupper.c $(PATH_SRCS)/ft_tolower.c $(PATH_SRCS)/ft_strchr.c $(PATH_SRCS)/ft_strrchr.c \
		$(PATH_SRCS)/ft_strncmp.c $(PATH_SRCS)/ft_memchr.c $(PATH_SRCS)/ft_memcmp.c $(PATH_SRCS)/ft_strnstr.c \
		$(PATH_SRCS)/ft_atoi.c $(PATH_SRCS)/ft_calloc.c $(PATH_SRCS)/ft_strdup.c $(PATH_SRCS)/ft_substr.c  \
		$(PATH_SRCS)/ft_strjoin.c $(PATH_SRCS)/ft_strtrim.c $(PATH_SRCS)/ft_split.c $(PATH_SRCS)/ft_itoa.c \
		$(PATH_SRCS)/ft_strmapi.c $(PATH_SRCS)/ft_striteri.c $(PATH_SRCS)/ft_putchar_fd.c \
		$(PATH_SRCS)/ft_putstr_fd.c $(PATH_SRCS)/ft_putendl_fd.c $(PATH_SRCS)/ft_putnbr_fd.c

SRCSB = \
		$(PATH_SRCS)/ft_lstnew_bonus.c $(PATH_SRCS)/ft_lstadd_front_bonus.c $(PATH_SRCS)/ft_lstsize_bonus.c \
		$(PATH_SRCS)/ft_lstlast_bonus.c $(PATH_SRCS)/ft_lstadd_back_bonus.c $(PATH_SRCS)/ft_lstdelone_bonus.c \
		$(PATH_SRCS)/ft_lstclear_bonus.c $(PATH_SRCS)/ft_lstiter_bonus.c $(PATH_SRCS)/ft_lstmap_bonus.c

GNL_SRCS = \
		$(GNL_PATH)/get_next_line_bonus.c \
		$(GNL_PATH)/get_next_line_utils_bonus.c

PRINTF_SRCS = \
		$(PRINTF_PATH)/ft_printf.c \
		$(PRINTF_PATH)/ft_putchar_c.c \
		$(PRINTF_PATH)/ft_putlonghex_c.c \
		$(PRINTF_PATH)/ft_putnbr_c.c \
		$(PRINTF_PATH)/ft_putstr_c.c \
		$(PRINTF_PATH)/ft_putunsigned_c.c \
		$(PRINTF_PATH)/ft_putunsignedhex_c.c

ALL_SRCS = $(SRCS) $(SRCSB) $(GNL_SRCS) $(PRINTF_SRCS)
OBJS = $(ALL_SRCS:%.c=$(OBJ_PATH)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAG) $(OPTION) $< -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all

