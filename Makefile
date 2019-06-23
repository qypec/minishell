# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/13 21:16:45 by yquaro            #+#    #+#              #
#    Updated: 2019/06/23 20:25:48 by yquaro           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# (ar rc)
# The c option makes you create a library if it is not available,
# and the r (replace) option replaces old object files with new versions.

# (ranlib)
# Adds a character index to the archive

CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = environment.c main.c prompt.c envpath.c builtin.c bust.c cmd_cd.c cmd_exit.c
OBJECTS = environment.o main.o prompt.o envpath.o builtin.o bust.o cmd_cd.o cmd_exit.o
EXECUTABLE = minishell

LIBNAME = libft.a

all:
	@make -C libft/ all
	$(CC) -g $(SOURCES) -L. -lft -o $(EXECUTABLE) # НЕ ЗАБЫТЬ ФЛАГИ!!!!
	
clean: fclean

fclean:
	@make -C libft/ fclean
	@rm $(EXECUTABLE)
	@rm $(LIBNAME)

re: fclean all