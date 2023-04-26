# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/07 19:15:07 by hakahmed          #+#    #+#              #
#    Updated: 2023/04/11 21:14:54 by hakahmed         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ==== ==== COMPILER ==== ==== #

CC = gcc

CFLAGS = -Wall -Wextra -Werror

# CFLAGS += -fsanitize=address -g3

# ==== END OF COMPILER ==== ==== #

# ==== ==== LIB ==== ==== #

NAME = libft.a

LIB = ar -rcs

# ==== END OF LIB ==== ==== #

# ==== ==== SRC DIRS ==== ==== #

P1DIR = part1

P2DIR = part2

BONUSDIR = bonus

ADTDIR = additional

PRINTFDIR = ft_printf

GNLDIR = get_next_line

# ==== ==== END ==== ==== #

# ==== ==== SRC FILES ==== ==== #
#
SRC_P1 = ft_isalpha.c \
	 ft_isdigit.c \
	 ft_isalnum.c \
	 ft_isascii.c \
	 ft_isprint.c \
	 ft_strlen.c \
	 ft_memset.c \
	 ft_bzero.c \
	 ft_memcpy.c \
	 ft_memmove.c \
	 ft_strlcpy.c \
	 ft_strlcat.c \
	 ft_toupper.c \
	 ft_tolower.c \
	 ft_strchr.c \
	 ft_strrchr.c \
	 ft_strncmp.c \
	 ft_memchr.c \
	 ft_memcmp.c \
	 ft_strnstr.c \
	 ft_atoi.c \
	 ft_calloc.c \
	 ft_strdup.c \

SRC_P2 = ft_substr.c \
	 ft_strjoin.c \
	 ft_strtrim.c \
	 ft_split.c \
	 ft_itoa.c \
	 ft_strmapi.c \
	 ft_striteri.c \
	 ft_putchar_fd.c \
	 ft_putstr_fd.c \
	 ft_putendl_fd.c \
	 ft_putnbr_fd.c \

SRC_BONUS = ft_lstnew_bonus.c \
	    ft_lstadd_front_bonus.c \
	    ft_lstsize_bonus.c \
	    ft_lstlast_bonus.c \
	    ft_lstadd_back_bonus.c \
	    ft_lstdelone_bonus.c \
	    ft_lstclear_bonus.c \
	    ft_lstiter_bonus.c \
	    ft_lstmap_bonus.c \

SRC_PRINTF = ft_printf.c \
	     str_utils.c \
	     nb_utils.c \

SRC_GNL = get_next_line.c \
	  get_next_line_utils.c \

SRC_ADT = ft_atol.c \
	  ft_free_strarr.c \
	  ft_isspace.c \
	  ft_strcmp.c \


SRC = $(addprefix $(P1DIR)/,$(SRC_P1)) \
      $(addprefix $(P2DIR)/,$(SRC_P2)) \
      $(addprefix $(ADTDIR)/,$(SRC_ADT)) \
      $(addprefix $(PRINTFDIR)/,$(SRC_PRINTF)) \
      $(addprefix $(GNLDIR)/,$(SRC_GNL)) \

# ==== ==== END SRC FILES ==== ==== #

# ==== ==== INCLUDES ==== ==== #

INCDIR = inc
IFLAGS = -I $(INCDIR)

# ==== ==== ENDINC ==== ==== #

# ==== ==== OBJS ==== ==== #

OBJDIR = .obj

OBJ = $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

BNS = $(addprefix $(BONUSDIR)/,$(SRC_BONUS))

BONUSOBJ = $(addprefix $(OBJDIR)/,$(BNS:.c=.o))

# ==== ==== COLORS ==== ==== #

bold := $(shell tput bold)
reset := $(shell tput sgr0)

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

# ==== ===== END ==== ===== #

# ==== ===== MISC ==== ==== #

RM = rm -rf 

# ==== ===== END ==== ==== #

# ===== ==== RULES ==== ==== #

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIB) $(NAME) $(OBJ)
	@echo ""
	@echo "$(COLOUR_GREEN)$(bold)Everything compiled successfully!$(COLOUR_END)$(reset)🎉"

bonus: $(OBJ) $(BONUSOBJ) 
	@$(LIB) $(NAME) $(BONUSOBJ) $(OBJ)
	@echo ""
	@echo "$(COLOUR_GREEN)$(bold)Everything compiled successfully!$(COLOUR_END)$(reset)🎉"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(IFLAGS) $(CCFLAGS) -c -o $@ $<
	@echo "$(COLOUR_BLUE)$(bold)Compiling $(COLOUR_END)$(reset)" $<

clean:
	@$(RM) $(OBJDIR)
	@echo "$(COLOUR_GREEN)$(bold)Cleaned!$(COLOUR_END)$(reset)🧪"

fclean: clean
	@$(RM) $(NAME)

re: fclean all

rebonus: fclean bonus

prt:
	@curl parrot.live

.PHONY: all clean fclean bonus re rebonus prt
