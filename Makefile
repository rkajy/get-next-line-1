# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: radandri <radandri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/23 17:29:15 by radandri          #+#    #+#              #
#    Updated: 2025/08/23 19:47:59 by radandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = get_next_line.a

TEST = test

SRCS = get_next_line.c \
       get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
# create the archive libftprint.a
	ar rcs $(NAME) $(OBJS)

# compile the test program
$(TEST): $(OBJS) main.o
	$(CC) $(CFLAGS) -o $(TEST) main.o $(NAME) $(LIBFT)
	./$(TEST)

clean:
	rm -f $(OBJS)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
