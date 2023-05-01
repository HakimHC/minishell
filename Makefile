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

# LDFLAGS += -fsanitize=address

#source files and stuff
SRCDIR = src

MAINDIR = main

MAINSRC = main.c \
	  utils.c

MAIN_DBSRC = db_main.c \
	     utils.c

MAIN = $(addprefix $(MAINDIR)/,$(MAINSRC))

MAIN_DB = $(addprefix $(MAINDIR)/,$(MAIN_DBSRC))

LXDIR = lexer

LXSRC = tokenize_line.c

PSDIR = parser

PSSRC = cmdtab.c \
	error_handling.c \
	error_handling_utils.c \
	cmdtab_utils.c

EXECDIR = executor

EXECSRC = executor.c \
	  envparser.c \
	  utils.c

BIDIR = builtins

BISRC = env.c \
	export.c \
	unset.c \

BI = $(addprefix $(BIDIR)/,$(BISRC))

EXEC= $(addprefix $(EXECDIR)/,$(EXECSRC))

PS = $(addprefix $(PSDIR)/,$(PSSRC))

SRC = $(addprefix $(SRCDIR)/,$(LXDIR)/$(LXSRC)) \
      $(addprefix $(SRCDIR)/,$(PS)) \
      $(addprefix $(SRCDIR)/,$(EXEC)) \
      $(addprefix $(SRCDIR)/,$(BI)) \

SRC_NORMAL = $(SRC) $(addprefix $(SRCDIR)/,$(MAIN))
SRC_DEBUG = $(SRC) $(addprefix $(SRCDIR)/,$(MAIN_DB))

LIB = libft/libft.a

#objects and stuff


OBJ_NORMAL = $(SRC_NORMAL:.c=.o)
OBJ_DEBUG = $(SRC_DEBUG:.c=.o)

#rules and stuff


all: $(NAME)

$(LIB):
	make bonus -C libft

%.o: %.c $(LIB)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_NORMAL)
	$(CC) $(CFLAGS) $(OBJ_NORMAL) $(LDFLAGS) -o $(NAME)

debug: $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(OBJ_DEBUG) $(LDFLAGS) -o db_minishell

clean:
	make fclean -C libft
	rm -f $(OBJ_NORMAL)
	rm -f $(OBJ_DEBUG)

fclean: clean
	rm -f $(NAME)

re: fclean all

asan: $(LDFLAGS) += -fsanitize=address
asan: $(CFLAGS) += -g3 -fsanitize=address
asan: $(NAME) 

leak: $(LDFLAGS) += -fsanitize=leak
leak: $(CFLAGS) += -g3
leak: $(NAME)

.PHONY: all fclean clean re
