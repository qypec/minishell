# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 21:16:45 by yquaro            #+#    #+#              #
#    Updated: 2019/08/13 15:21:05 by yquaro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../includes/minishell.mk

DIR_O = ../lib
SOURCES = main.c environment.c prompt.c envpath.c bust.c cmd_cd.c \
			cmd_exit.c cmd_env.c manage_expansions.c cmd_unsetenv.c \
			cmd_setenv.c cmd_echo.c screening.c additional_input.c \
			screening_loop.c gitdir_search.c init.c signal.c
OBJECTS = $(addprefix $(DIR_O)/,$(patsubst %.c,%.o,$(SOURCES)))

all: print $(OBJECTS)

print:
	@echo \*\*\* Compiling minishell

$(DIR_O)/%.o: %.c
	$(COMPILING) $< -o $@
