# program name
NAME = minishell

#compiler stuff
CC = gcc

CFLAGS = -Wall -Werror -Wextra


#include headers
INCDIR = inc

LFTDIR = libft

CFLAGS += -I $(INCDIR)

CFLAGS += -I $(LFTDIR)/$(INCDIR)

#linker

LDFLAGS = -Llibft -lft -lreadline


#source files and stuff
SRCDIR = src

MAINDIR = main

MAINFILES = main.c 

LXDIR = lexer

LXSRC = tokenize_line.c

SRC = $(addprefix $(SRCDIR)/,$(MAINDIR)/$(MAINFILES)) \
      $(addprefix $(SRCDIR)/,$(LXDIR)/$(LXSRC))


#objects and stuff

OBJ = $(SRC:.c=.o)

#rules and stuff

%.o: %.c
	make bonus -C libft
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	make fclean -C libft
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

asan: $(LDFLAGS) += -fsanitize=address
asan: $(CFLAGS) += -g3
asan: re

leak: $(LDFLAGS) += -fsanitize=leak
leak: $(CFLAGS) += -g3
leak: re

.PHONY: all fclean clean re
