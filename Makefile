# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hpehliva <hpehliva@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/17 20:03:47 by hpehliva          #+#    #+#              #
#    Updated: 2025/12/18 15:00:03 by hpehliva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = 	algorithm/algorithm_movements_utils.c \
		algorithm/algorithm_movements.c \
		algorithm/algorithm_utils.c \
		algorithm/assign_stack.c \
		algorithm/assign_stack_utils.c \
		algorithm/small_sort.c \
		algorithm/sorting_advanced.c \
		operators/push_operators.c \
		operators/swap_operators.c \
		operators/reverse_operators.c \
		operators/rotate_operators.c \
		srcs/utils.c \
		srcs/parsing.c \
		srcs/parsing_utils.c \
		srcs/parsing_utils_01.c \
		main.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re