# program name
NAME = minishell

#compiler stuff
CC = gcc

CFLAGS = -Wall -Werror -Wextra

CFLAGS += -g3

CFLAGS += -O3

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
	  utils.c \
	  destroyer.c

MAIN = $(addprefix $(MAINDIR)/,$(MAINSRC))

LXDIR = lexer

LXSRC = tokenize_line.c \
	lexer_utils.c \
	tokenizer_utils.c

PSDIR = parser

PSSRC = cmdtab.c \
	error_handling.c \
	error_handling_utils.c \
	cmdtab_utils.c

EXECDIR = executor

EXECSRC = executor.c \
	  envparser.c \
	  utils.c \
	  heredoc.c \
	  open_files.c \
	  exec_utils.c \
	  p_syscalls.c

BIDIR = builtins

BISRC = env.c \
	export.c \
	unset.c \
	echo.c \
	pwd.c \
	cd.c \
	exit.c \
	envar_utils.c \
	utils.c

EXPDIR = expander

EXPSRC = expander.c

LX = $(addprefix $(LXDIR)/,$(LXSRC))

BI = $(addprefix $(BIDIR)/,$(BISRC))

EXEC= $(addprefix $(EXECDIR)/,$(EXECSRC))

PS = $(addprefix $(PSDIR)/,$(PSSRC))

EXP = $(addprefix $(EXPDIR)/,$(EXPSRC))

SRC = $(addprefix $(SRCDIR)/,$(LX)) \
      $(addprefix $(SRCDIR)/,$(PS)) \
      $(addprefix $(SRCDIR)/,$(EXEC)) \
      $(addprefix $(SRCDIR)/,$(BI)) \
      $(addprefix $(SRCDIR)/,$(EXP)) \

SRC_NORMAL = $(SRC) $(addprefix $(SRCDIR)/,$(MAIN))

LIB = libft/libft.a

#objects and stuff
OBJ_NORMAL = $(SRC_NORMAL:.c=.o)

#rules and stuff
all: $(NAME)

$(LIB):
	make bonus -C libft

%.o: %.c $(LIB)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_NORMAL)
	$(CC) $(CFLAGS) $(OBJ_NORMAL) $(LDFLAGS) -o $(NAME)

# debug: $(OBJ_DEBUG)
# 	$(CC) $(CFLAGS) $(OBJ_DEBUG) $(LDFLAGS) -o db_minishell

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

commit: fclean
	@read -p "Commit msg: " msg; \
	git add . ; \
	git commit -m "$$msg" ; \
	git push

.PHONY: all fclean clean re
