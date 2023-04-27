# program name
NAME = minishell

#compiler stuff
CC = gcc

CFLAGS = -Wall -Werror -Wextra

CFLAGS +=  -g3

#include headers
INCDIR = inc

LFTDIR = libft

CFLAGS += -I $(INCDIR)

CFLAGS += -I $(LFTDIR)/$(INCDIR)

#linker

LDFLAGS = -Llibft -lft -lreadline

LDFLAGS += -fsanitize=address

#source files and stuff
SRCDIR = src

MAINDIR = main

MAINSRC = main.c \
	  utils.c

MAIN = $(addprefix $(MAINDIR)/,$(MAINSRC))

LXDIR = lexer

LXSRC = tokenize_line.c

PSDIR = parser

PSSRC = cmdtab.c \
	error_handling.c \
	cmdtab_utils.c

PS = $(addprefix $(PSDIR)/,$(PSSRC))

SRC = $(addprefix $(SRCDIR)/,$(MAIN)) \
      $(addprefix $(SRCDIR)/,$(LXDIR)/$(LXSRC)) \
      $(addprefix $(SRCDIR)/,$(PS)) \


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
asan: $(CFLAGS) += -g3 -fsanitize=address
asan: re

leak: $(LDFLAGS) += -fsanitize=leak
leak: $(CFLAGS) += -g3
leak: re

.PHONY: all fclean clean re
