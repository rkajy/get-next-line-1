# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: radandri <radandri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/23 17:29:15 by radandri          #+#    #+#              #
#    Updated: 2025/08/30 23:17:59 by radandri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
VALGRIND_ARGS = --leak-check=full --show-leak-kinds=all --track-origins=yes -s

NORM = norminette
NORM_FLAGS = -R CheckForbiddenSourceHeader -R checkDefine

NAME = libgnl.a

OBJ_DIR = obj

TEST_BINARY = test_main.out

SRC_FILES = get_next_line.c \
       get_next_line_utils.c \

HEADER_FILES = get_next_line.h \

OBJ_FILES = $(SRC_FILES:.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_FILES)
# create the archive libftprint.a
	ar rcs $(NAME) $(OBJ_FILES)

all: $(NAME)

clean:
	rm -f $(OBJ_FILES)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

# compile the test program
build: $(NAME)
	$(CC) Manual_test_gnl/main.c $(NAME) -o $(TEST_BINARY)

run: build
	@echo "Running the app ..."
	./$(TEST_BINARY)

debug: fclean
	@(MAKE) all
	@echo "Running debugging using lldb"
	@(CC) -I $(INC_DIR) -g Manual_test_gnl/main.c $(NAME) -o $(TEST_BINARY)
	lldb ./$(TEST_BINARY)

norm:
	@echo "Running norminette..."
	$(NORM) $(NORM_FLAGS) $(SRC_FILES) $(HEADER_FILES)

valgrind:
	@echo "Running valgrind..."
	make -s fclean
	make -s build
	valgrind $(VALGRIND_ARGS) ./$(BINARY)

.PHONY: all clean fclean re build run debug norm valgrind
