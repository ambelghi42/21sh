# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 14:50:28 by ambelghi          #+#    #+#              #
#    Updated: 2020/02/04 12:59:25 by ambelghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Reset
NC=\033[0m

# Regular Colors
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

CC = Clang
COMPILE = $(CC) -c

MKDIR = mkdir -p obj/line_edition
CLEANUP = rm -rf

WFLAGS = -Wall -Werror -Wextra
IFLAGS = -I$(IPATH) -I$(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)
DEBUG = $(CFLAGS) -g

PATHO = obj/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes
LIB = $(LPATH)libft.a

INCS += minishell.h

SRCS += main.c
SRCS += ft_which.c
SRCS += utils.c
SRCS += list.c
SRCS += params.c
SRCS += launch.c
SRCS += builtins.c
SRCS += setenv.c
SRCS += echo.c
SRCS += exit.c
SRCS += cd.c
SRCS += signal.c
SRCS += utils2.c

SRCS += line_edition/get_started.c
SRCS += line_edition/columns.c
SRCS += line_edition/keys.c
SRCS += line_edition/keys2.c
SRCS += line_edition/list.c
SRCS += line_edition/list2.c
SRCS += line_edition/print.c
SRCS += line_edition/signals.c
SRCS += line_edition/term_init.c
SRCS += line_edition/utils.c
SRCS += line_edition/cursor.c

OBJS = $(patsubst %.c, $(PATHO)%.o, $(SRCS))


all : $(NAME)

$(NAME) : $(LIB) $(PATHO) $(OBJS)
	$(CC) -g -fsanitize=address -lncurses -o $@ $< $(OBJS)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS) : $(PATHO)%.o : $(SPATH)%.c
	$(COMPILE) -g $(CFLAGS) $< -o $@

$(PATHO) :
	$(MKDIR) $@

$(LIB) :
	$(MAKE) -C $(LPATH)

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(PATHO)

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(PATHO)
	$(CLEANUP) $(NAME)

re : fclean all

norme:
	norminette srcs
	norminette includes
	norminette libft/srcs
	norminette libft/includes

.PHONY: all clean fclean norme re
